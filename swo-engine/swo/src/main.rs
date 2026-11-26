//! swo.exe: the Seamless Windows Optimizer engine.
//!
//! Usage (all output is JSON lines, see swo_core::emit):
//!   swo version
//!   swo catalog
//!   swo scan    [--ids a,b] [--page p]
//!   swo apply   --ids a,b [--restore-point] [--dry-run]
//!   swo revert  --ids a,b [--dry-run]
//!   swo journal                      ids that can be undone
//!   swo tool <name> [args...]        free-form tools (see each provider)
//!
//! Exit codes: 0 all fine, 1 something failed, 2 bad arguments, 3 needs admin.

use serde_json::json;
use std::collections::HashMap;
use swo_core::{Ctx, Item, Provider};

struct Args {
    cmd: String,
    rest: Vec<String>,
    ids: Vec<String>,
    page: Option<String>,
    dry_run: bool,
    restore_point: bool,
}

fn parse() -> Args {
    let all: Vec<String> = std::env::args().skip(1).collect();
    let mut a = Args { cmd: all.first().cloned().unwrap_or_default(), rest: Vec::new(), ids: Vec::new(), page: None, dry_run: false, restore_point: false };
    let mut i = 1;
    while i < all.len() {
        match all[i].as_str() {
            "--ids" if i + 1 < all.len() => {
                a.ids = all[i + 1].split(',').map(|s| s.trim().to_string()).filter(|s| !s.is_empty()).collect();
                i += 1;
            }
            "--page" if i + 1 < all.len() => {
                a.page = Some(all[i + 1].clone());
                i += 1;
            }
            "--dry-run" => a.dry_run = true,
            "--restore-point" => a.restore_point = true,
            other => a.rest.push(other.to_string()),
        }
        i += 1;
    }
    a
}

fn providers() -> Vec<Box<dyn Provider>> {
    vec![swo_clean::provider(), swo_tweaks::provider(), swo_tools::provider()]
}

fn main() {
    let a = parse();
    let ps = providers();
    let ctx = Ctx::new(a.dry_run);

    // id -> (provider index, item)
    let mut owner: HashMap<String, (usize, Item)> = HashMap::new();
    let mut order: Vec<String> = Vec::new();
    for (pi, p) in ps.iter().enumerate() {
        for it in p.items() {
            order.push(it.id.clone());
            owner.insert(it.id.clone(), (pi, it));
        }
    }

    let code = match a.cmd.as_str() {
        "version" => {
            println!("{}", json!({"t": "version", "version": env!("CARGO_PKG_VERSION"), "elevated": ctx.elevated, "build": swo_core::sys::build()}));
            0
        }
        "catalog" => {
            for id in &order {
                ctx.emit.item(&owner[id].1);
            }
            ctx.emit.end(order.len() as u64, 0);
            0
        }
        "scan" => {
            let mut want: Vec<Vec<String>> = vec![Vec::new(); ps.len()];
            for id in &order {
                let (pi, it) = &owner[id];
                let by_id = a.ids.is_empty() || a.ids.contains(id);
                let by_page = a.page.as_deref().map_or(true, |p| p == it.page);
                if by_id && by_page {
                    want[*pi].push(id.clone());
                }
            }
            // Providers scan in parallel; each emits its own lines.
            std::thread::scope(|s| {
                for (pi, ids) in want.iter().enumerate() {
                    if ids.is_empty() {
                        continue;
                    }
                    let p = &ps[pi];
                    let ctx = &ctx;
                    s.spawn(move || {
                        for st in p.scan(ctx, ids) {
                            ctx.emit.state(&st);
                        }
                    });
                }
            });
            ctx.emit.end(want.iter().map(|v| v.len() as u64).sum(), 0);
            0
        }
        "apply" | "revert" => run_batch(&a, &ps, &owner, &ctx),
        "journal" => {
            for id in ctx.journal.ids() {
                ctx.emit.row("journal", json!({"id": id}));
            }
            ctx.emit.end(0, 0);
            0
        }
        "tool" => {
            let name = a.rest.first().cloned().unwrap_or_default();
            let targs: Vec<String> = a.rest.iter().skip(1).cloned().collect();
            let mut handled = None;
            for p in &ps {
                if let Some(r) = p.run_tool(&ctx, &name, &targs) {
                    handled = Some(r);
                    break;
                }
            }
            match handled {
                Some(Ok(())) => {
                    ctx.emit.end(1, 0);
                    0
                }
                Some(Err(e)) => {
                    ctx.emit.fail(&format!("tool.{name}"), &format!("{e:#}"));
                    ctx.emit.end(0, 1);
                    1
                }
                None => {
                    ctx.emit.fail(&format!("tool.{name}"), "unknown tool");
                    ctx.emit.end(0, 1);
                    2
                }
            }
        }
        _ => {
            eprintln!("swo: catalog | scan | apply | revert | journal | tool | version");
            2
        }
    };
    std::process::exit(code);
}

fn run_batch(a: &Args, ps: &[Box<dyn Provider>], owner: &HashMap<String, (usize, Item)>, ctx: &Ctx) -> i32 {
    let apply = a.cmd == "apply";
    if a.ids.is_empty() {
        eprintln!("swo {}: --ids is required", a.cmd);
        return 2;
    }
    if !ctx.elevated && a.ids.iter().any(|id| owner.get(id).map_or(false, |(_, it)| it.admin)) {
        for id in &a.ids {
            ctx.emit.fail(id, "needs admin");
        }
        ctx.emit.end(0, a.ids.len() as u64);
        return 3;
    }
    if apply && a.restore_point && !a.dry_run {
        ctx.emit.progress("restore-point", 0, 1, "Making a restore point");
        match swo_core::restore::create("Seamless Windows Optimizer") {
            Ok(n) => ctx.emit.log(&n),
            Err(e) => ctx.emit.log(&format!("No restore point: {e}")),
        }
    }
    let (mut ok, mut failed) = (0u64, 0u64);
    let total = a.ids.len() as u64;
    for (n, id) in a.ids.iter().enumerate() {
        let Some((pi, it)) = owner.get(id) else {
            ctx.emit.fail(id, "unknown id");
            failed += 1;
            continue;
        };
        ctx.emit.progress(id, n as u64, total, &it.name);
        let p = &ps[*pi];
        let r = if apply { p.apply(ctx, id) } else { p.revert(ctx, id) };
        match r {
            Ok(d) => {
                ctx.emit.ok(id, &d);
                ok += 1;
            }
            Err(e) => {
                ctx.emit.fail(id, &format!("{e:#}"));
                failed += 1;
            }
        }
    }
    ctx.emit.end(ok, failed);
    if failed > 0 {
        1
    } else {
        0
    }
}
