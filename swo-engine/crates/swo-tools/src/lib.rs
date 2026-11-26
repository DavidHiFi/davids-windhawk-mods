//! Repair jobs, registry leftovers, and the tools behind the mod's lists:
//! start-up apps, installed programs, hidden updates, folder sizes and PC facts.
//!
//! Built from Microsoft's documentation of each command (sfc, DISM, chkdsk,
//! w32tm, ipconfig), the Windows Update Agent API, and the documented layout
//! of the Run, StartupApproved, App Paths and Uninstall keys. WTools was only
//! looked at from the outside to see which jobs a PC tool should offer; none
//! of its code, data or wording is used.

use anyhow::{anyhow, bail, Context, Result};
use serde_json::{json, Value};
use std::collections::BinaryHeap;
use std::cmp::Reverse;
use std::os::windows::fs::MetadataExt;
use std::os::windows::process::CommandExt;
use std::path::{Path, PathBuf};
use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::Mutex;
use swo_core::{proc, reg, restore, svc, sys, Ctx, Done, Item, Kind, Provider, RegVal, Risk, State, Txn, Undo};

// ---------------------------------------------------------------- repair jobs

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Job {
    RestorePoint,
    Sfc,
    DismScan,
    DismRepair,
    ComponentCleanup,
    UpdateReset,
    FlushDns,
    IconCache,
    DiskScan,
    TimeSync,
}

fn repairs() -> Vec<(Job, Item)> {
    let r = |id: &str, group: &str, name: &str, desc: &str| Item::new(format!("repair.{id}"), "repair", group, name, desc, Kind::Action);
    vec![
        (Job::RestorePoint, r("restore-point", "Safety", "Make a restore point", "Saves a point you can roll Windows back to if something goes wrong.").admin()),
        (Job::Sfc, r("sfc", "Repair Windows", "Check and fix system files", "Finds damaged Windows files and puts good copies back. Takes about ten minutes.").admin()),
        (Job::DismScan, r("dism-scan", "Repair Windows", "Check the Windows repair store", "Checks the store Windows repairs itself from. Takes a few minutes.").admin()),
        (
            Job::DismRepair,
            r("dism-repair", "Repair Windows", "Repair the Windows repair store", "Downloads good copies of damaged parts from Windows Update. Run it before checking system files again.")
                .admin()
                .warn("Needs the internet and can take twenty minutes."),
        ),
        (Job::ComponentCleanup, r("component-cleanup", "Repair Windows", "Shrink the store of old Windows parts", "Removes old copies of Windows parts that updates replaced. Takes a few minutes.").admin()),
        (
            Job::UpdateReset,
            r("update-reset", "Repair Windows", "Fix stuck Windows updates", "Stops the update services, sets the download folders aside and starts them fresh.")
                .admin()
                .risk(Risk::Moderate)
                .warn("The update history list starts empty."),
        ),
        (Job::DiskScan, r("disk-scan", "Drives", "Check the C: drive for errors", "Scans the drive while you keep working and says if it found problems.").admin()),
        (Job::FlushDns, r("flush-dns", "Network", "Clear the saved website addresses", "Fixes sites that moved and still won't load.")),
        (Job::TimeSync, r("time-sync", "Network", "Set the clock from the internet", "Syncs the clock with the Windows time servers, which fixes sign-in and certificate errors.").admin()),
        (Job::IconCache, r("icon-cache", "Desktop", "Refresh icons", "Redraws icons that show blank or the wrong picture.")),
    ]
}

/// The last number before a % sign, for progress bars.
fn pct(line: &str) -> Option<u64> {
    let i = line.rfind('%')?;
    let head = line[..i].trim_end();
    let start = head.rfind(|c: char| !(c.is_ascii_digit() || c == '.')).map(|p| p + 1).unwrap_or(0);
    head[start..].parse::<f64>().ok().map(|f| f.clamp(0.0, 100.0) as u64)
}

/// Run a command, turning its percent lines into progress and keeping the rest.
fn stream(ctx: &Ctx, id: &str, exe: &str, args: &[&str]) -> Result<(i32, String)> {
    let mut last = u64::MAX;
    let mut tail: Vec<String> = Vec::new();
    let code = proc::run_lines(exe, args, |l| match pct(l) {
        Some(p) => {
            if p != last {
                last = p;
                ctx.emit.progress(id, p, 100, l);
            }
        }
        None => {
            tail.push(l.to_string());
            if tail.len() > 60 {
                tail.remove(0);
            }
        }
    })?;
    Ok((code, tail.join("\n")))
}

fn last_line(text: &str) -> String {
    text.lines().map(str::trim).filter(|l| !l.is_empty()).last().unwrap_or("no output").to_string()
}

fn free_on(root: &str) -> Option<u64> {
    disk(root).map(|(_, free)| free)
}

fn disk(root: &str) -> Option<(u64, u64)> {
    use windows_sys::Win32::Storage::FileSystem::GetDiskFreeSpaceExW;
    let w: Vec<u16> = root.encode_utf16().chain(Some(0)).collect();
    let (mut avail, mut total, mut free) = (0u64, 0u64, 0u64);
    let ok = unsafe { GetDiskFreeSpaceExW(w.as_ptr(), &mut avail, &mut total, &mut free) };
    let _ = avail;
    (ok != 0).then_some((total, free))
}

fn net(verb: &str, svc_name: &str) {
    let _ = proc::run("net.exe", &[verb, svc_name, "/y"]);
}

fn stamp() -> u64 {
    std::time::SystemTime::now().duration_since(std::time::UNIX_EPOCH).map(|d| d.as_secs()).unwrap_or(0)
}

fn run_job(ctx: &Ctx, id: &str, job: Job) -> Result<Done> {
    if ctx.dry_run {
        return Ok(Done::note("dry run"));
    }
    let sys32 = sys::expand("%SystemRoot%\\System32");
    match job {
        Job::RestorePoint => Ok(Done::note(restore::create("Seamless Windows Optimizer")?)),
        Job::Sfc => {
            let (code, text) = stream(ctx, id, &format!("{sys32}\\sfc.exe"), &["/scannow"])?;
            let low = text.to_ascii_lowercase();
            if low.contains("did not find any integrity violations") {
                Ok(Done::note("No damaged files found"))
            } else if low.contains("successfully repaired") {
                Ok(Done { reboot: true, note: Some("Fixed damaged files. Restart to finish.".into()), ..Default::default() })
            } else if low.contains("unable to fix") {
                bail!("Found damaged files it could not fix. Run Repair the Windows repair store, then check again.")
            } else if low.contains("repair pending") {
                bail!("A repair is waiting for a restart. Restart, then try again.")
            } else if low.contains("could not perform") {
                bail!("Windows could not run the check. Restart and try again.")
            } else if code != 0 {
                bail!("{}", last_line(&text))
            } else {
                Ok(Done::note(last_line(&text)))
            }
        }
        Job::DismScan => {
            let (code, text) = stream(ctx, id, &format!("{sys32}\\dism.exe"), &["/Online", "/Cleanup-Image", "/ScanHealth"])?;
            let low = text.to_ascii_lowercase();
            if code != 0 {
                bail!("{}", last_line(&text));
            }
            if low.contains("no component store corruption") {
                Ok(Done::note("No damage found"))
            } else if low.contains("is repairable") {
                Ok(Done::note("Damage found. Run Repair the Windows repair store."))
            } else if low.contains("cannot be repaired") {
                bail!("The repair store is damaged beyond repair. Windows needs a repair install.")
            } else {
                Ok(Done::note(last_line(&text)))
            }
        }
        Job::DismRepair => {
            let (code, text) = stream(ctx, id, &format!("{sys32}\\dism.exe"), &["/Online", "/Cleanup-Image", "/RestoreHealth"])?;
            if code != 0 {
                bail!("{}", last_line(&text));
            }
            Ok(Done::note("Repaired. Check system files again next."))
        }
        Job::ComponentCleanup => {
            let before = free_on("C:\\").unwrap_or(0);
            let (code, text) = stream(ctx, id, &format!("{sys32}\\dism.exe"), &["/Online", "/Cleanup-Image", "/StartComponentCleanup"])?;
            if code != 0 {
                bail!("{}", last_line(&text));
            }
            let after = free_on("C:\\").unwrap_or(0);
            Ok(Done::freed(after.saturating_sub(before), 0))
        }
        Job::UpdateReset => {
            let order = ["UsoSvc", "wuauserv", "bits", "cryptsvc"];
            for s in order {
                ctx.emit.progress(id, 10, 100, &format!("Stopping {s}"));
                net("stop", s);
            }
            let t = stamp();
            let mut moved = Vec::new();
            let mut err = None;
            for dir in [sys::expand("%SystemRoot%\\SoftwareDistribution"), format!("{sys32}\\catroot2")] {
                let from = PathBuf::from(&dir);
                if !from.exists() {
                    continue;
                }
                let to = PathBuf::from(format!("{dir}.old-{t}"));
                let mut ok = false;
                for _ in 0..10 {
                    if std::fs::rename(&from, &to).is_ok() {
                        ok = true;
                        break;
                    }
                    std::thread::sleep(std::time::Duration::from_millis(1000));
                }
                if ok {
                    moved.push(to);
                } else {
                    err = Some(format!("{dir} is still in use"));
                    break;
                }
            }
            for s in order.iter().rev() {
                ctx.emit.progress(id, 80, 100, &format!("Starting {s}"));
                net("start", s);
            }
            if let Some(e) = err {
                bail!("{e}. Restart Windows and try again.");
            }
            let names: Vec<String> = moved.iter().filter_map(|p| p.file_name().map(|n| n.to_string_lossy().into_owned())).collect();
            Ok(Done::note(format!("Done. The old folders are kept as {} until updates work again.", names.join(" and "))))
        }
        Job::FlushDns => {
            let o = proc::run("ipconfig.exe", &["/flushdns"])?;
            if o.code != 0 {
                bail!("{}", last_line(&o.text()));
            }
            Ok(Done::note("Cleared"))
        }
        Job::IconCache => {
            let _ = proc::run(&format!("{sys32}\\ie4uinit.exe"), &["-show"])?;
            Ok(Done::note("Icons refreshed"))
        }
        Job::DiskScan => {
            let (code, text) = stream(ctx, id, &format!("{sys32}\\chkdsk.exe"), &["C:", "/scan"])?;
            match code {
                0 => Ok(Done::note("No problems found")),
                1 => Ok(Done::note("Problems found and fixed")),
                2 => Ok(Done::note("No problems found; some clean-up waits for a restart")),
                _ => bail!("Found problems it could not fix online: {}", last_line(&text)),
            }
        }
        Job::TimeSync => {
            let mut o = proc::run("w32tm.exe", &["/resync"])?;
            if o.code != 0 {
                svc::start("W32Time");
                std::thread::sleep(std::time::Duration::from_secs(2));
                o = proc::run("w32tm.exe", &["/resync", "/rediscover"])?;
            }
            if o.code != 0 {
                bail!("{}", last_line(&o.text()));
            }
            Ok(Done::note("Clock synced"))
        }
    }
}

// ---------------------------------------------------------------- registry leftovers

const RUN_KEYS: &[&str] = &[
    "HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
    "HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce",
    "HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
    "HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce",
    "HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Run",
    "HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\RunOnce",
];

const UNINSTALL: &[&str] = &[
    "HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
    "HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
    "HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
];

const APP_PATHS: &[&str] = &[
    "HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths",
    "HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\App Paths",
    "HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\App Paths",
];

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Leftovers {
    Startup,
    Uninstall,
    AppPaths,
}

const REG_CLEAN: &[(Leftovers, &str)] = &[
    (Leftovers::Startup, "clean.reg-startup"),
    (Leftovers::Uninstall, "clean.reg-uninstall"),
    (Leftovers::AppPaths, "clean.reg-app-paths"),
];

fn reg_items() -> Vec<Item> {
    let mk = |id: &str, name: &str, desc: &str| {
        let mut i = Item::new(id, "clean", "Registry", name, desc, Kind::Clean).admin();
        i.undo = true;
        i
    };
    vec![
        mk("clean.reg-startup", "Start-up entries for removed apps", "Removes start-up entries that point to apps that are gone."),
        mk("clean.reg-uninstall", "Installed apps entries for removed apps", "Removes entries from the installed apps list for apps whose files are gone.").risk(Risk::Moderate),
        mk("clean.reg-app-paths", "Run box shortcuts for removed apps", "Removes Run box shortcuts that point to apps that are gone."),
    ]
}

/// One dead entry: a value (`value: Some`) or a whole key.
#[derive(Debug, Clone)]
struct Dead {
    key: String,
    value: Option<String>,
    label: String,
}

/// The program a command line starts, when it is a full local path.
fn exe_of(cmd: &str) -> Option<PathBuf> {
    let s = sys::expand(cmd.trim());
    let path = if let Some(rest) = s.strip_prefix('"') {
        rest.split('"').next()?.to_string()
    } else {
        let low = s.to_ascii_lowercase();
        match low.find(".exe") {
            Some(i) => s[..i + 4].to_string(),
            None => s.split(' ').next()?.to_string(),
        }
    };
    let p = path.trim();
    let b = p.as_bytes();
    if b.len() < 4 || !b[0].is_ascii_alphabetic() || b[1] != b':' || !(b[2] == b'\\' || b[2] == b'/') {
        return None;
    }
    Some(PathBuf::from(p))
}

fn not_found(p: &Path) -> bool {
    matches!(std::fs::symlink_metadata(p), Err(e) if e.kind() == std::io::ErrorKind::NotFound)
}

/// True only when the file is surely gone: its drive is there, and neither the
/// path nor its 32-bit twin exists.
fn gone(p: &Path) -> bool {
    let s = p.to_string_lossy().into_owned();
    let root: String = s.chars().take(3).collect();
    if !Path::new(&root).exists() || !not_found(p) {
        return false;
    }
    let low = s.to_ascii_lowercase();
    for (from, to) in [("\\system32\\", "\\SysWOW64\\"), ("\\sysnative\\", "\\System32\\")] {
        if let Some(i) = low.find(from) {
            let twin = format!("{}{}{}", &s[..i], to, &s[i + from.len()..]);
            if !not_found(Path::new(&twin)) {
                return false;
            }
        }
    }
    true
}

fn find_dead(kind: Leftovers) -> Vec<Dead> {
    let mut out = Vec::new();
    match kind {
        Leftovers::Startup => {
            for key in RUN_KEYS {
                for name in reg::values(key) {
                    let Some(cmd) = reg::get_str(key, &name) else { continue };
                    if exe_of(&cmd).is_some_and(|p| gone(&p)) {
                        let label = if name.is_empty() { cmd.clone() } else { name.clone() };
                        out.push(Dead { key: key.to_string(), value: Some(name), label });
                    }
                }
            }
        }
        Leftovers::Uninstall => {
            for root in UNINSTALL {
                for sub in reg::subkeys(root) {
                    let k = format!("{root}\\{sub}");
                    if !reg::subkeys(&k).is_empty() || reg::get_u32(&k, "SystemComponent") == Some(1) || reg::get_u32(&k, "WindowsInstaller") == Some(1) {
                        continue;
                    }
                    let Some(un) = reg::get_str(&k, "UninstallString") else { continue };
                    if un.to_ascii_lowercase().contains("msiexec") {
                        continue;
                    }
                    if !exe_of(&un).is_some_and(|p| gone(&p)) {
                        continue;
                    }
                    if let Some(loc) = reg::get_str(&k, "InstallLocation") {
                        let loc = sys::expand(loc.trim().trim_matches('"'));
                        if !loc.is_empty() && !not_found(Path::new(&loc)) {
                            continue;
                        }
                    }
                    let label = reg::get_str(&k, "DisplayName").filter(|s| !s.trim().is_empty()).unwrap_or(sub);
                    out.push(Dead { key: k, value: None, label });
                }
            }
        }
        Leftovers::AppPaths => {
            for root in APP_PATHS {
                for sub in reg::subkeys(root) {
                    let k = format!("{root}\\{sub}");
                    if !reg::subkeys(&k).is_empty() {
                        continue;
                    }
                    let Some(target) = reg::get_str(&k, "") else { continue };
                    if exe_of(&target).is_some_and(|p| gone(&p)) {
                        out.push(Dead { key: k, value: None, label: sub });
                    }
                }
            }
        }
    }
    out
}

fn summary(dead: &[Dead]) -> String {
    let n = dead.len();
    let names: Vec<&str> = dead.iter().take(3).map(|d| d.label.as_str()).collect();
    let mut s = format!("{n} {}: {}", if n == 1 { "entry" } else { "entries" }, names.join(", "));
    if n > 3 {
        s.push_str(&format!(" and {} more", n - 3));
    }
    s
}

fn remove_dead(tx: &mut Txn, d: &Dead) -> Result<()> {
    match &d.value {
        Some(name) => reg::del(tx, &d.key, name),
        None => {
            for name in reg::values(&d.key) {
                let prev = reg::get(&d.key, &name);
                tx.push(Undo::Reg { key: d.key.clone(), name, prev });
            }
            if tx.dry_run {
                return Ok(());
            }
            reg::del_tree_raw(&d.key)
        }
    }
}

fn clean_leftovers(ctx: &Ctx, id: &str, kind: Leftovers) -> Result<Done> {
    let dead = find_dead(kind);
    if dead.is_empty() {
        return Ok(Done::note("nothing to remove"));
    }
    let mut tx = ctx.journal.begin(id, ctx.dry_run);
    let mut first_err = None;
    let mut n = 0u64;
    for d in &dead {
        match remove_dead(&mut tx, d) {
            Ok(()) => n += 1,
            Err(e) => {
                first_err.get_or_insert(e);
            }
        }
    }
    tx.commit()?;
    if let Some(e) = first_err {
        if n == 0 {
            return Err(e);
        }
        ctx.emit.log(&format!("{id}: {e:#}"));
    }
    let mut done = Done::freed(0, n);
    done.note = Some(if ctx.dry_run { format!("dry run: {}", summary(&dead)) } else { summary(&dead) });
    Ok(done)
}

// ---------------------------------------------------------------- start-up apps

const APPROVED: &str = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StartupApproved";

struct Source {
    scope: &'static str,
    key: Option<&'static str>,
    folder: Option<&'static str>,
    approved: &'static str,
}

const SOURCES: &[Source] = &[
    Source { scope: "user", key: Some("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"), folder: None, approved: "HKCU\\Run" },
    Source { scope: "machine", key: Some("HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), folder: None, approved: "HKLM\\Run" },
    Source { scope: "machine32", key: Some("HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Run"), folder: None, approved: "HKLM\\Run32" },
    Source { scope: "user-folder", key: None, folder: Some("%APPDATA%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup"), approved: "HKCU\\StartupFolder" },
    Source { scope: "machine-folder", key: None, folder: Some("%ProgramData%\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp"), approved: "HKLM\\StartupFolder" },
];

impl Source {
    /// Full StartupApproved key, e.g. HKCU\Software\...\StartupApproved\Run.
    fn approved_key(&self) -> String {
        let (hive, leaf) = self.approved.split_once('\\').unwrap_or((self.approved, ""));
        format!("{hive}\\{APPROVED}\\{leaf}")
    }
    fn admin(&self) -> bool {
        self.approved.starts_with("HKLM")
    }
    fn entries(&self) -> Vec<(String, String)> {
        if let Some(k) = self.key {
            return reg::values(k).into_iter().filter(|n| !n.is_empty()).map(|n| {
                let cmd = reg::get_str(k, &n).unwrap_or_default();
                (n, cmd)
            }).collect();
        }
        let dir = PathBuf::from(sys::expand(self.folder.unwrap_or_default()));
        let mut v: Vec<(String, String)> = std::fs::read_dir(&dir)
            .into_iter()
            .flatten()
            .flatten()
            .filter(|e| e.file_type().map(|t| t.is_file()).unwrap_or(false))
            .filter_map(|e| {
                let n = e.file_name().to_string_lossy().into_owned();
                (!n.eq_ignore_ascii_case("desktop.ini")).then(|| (n, e.path().to_string_lossy().into_owned()))
            })
            .collect();
        v.sort();
        v
    }
}

/// StartupApproved: an even first byte (or no value) means on.
fn approved_on(key: &str, name: &str) -> bool {
    match reg::get(key, name) {
        Some(RegVal::Binary(b)) | Some(RegVal::Raw(_, b)) => b.first().map_or(true, |x| x % 2 == 0),
        _ => true,
    }
}

fn startup_list(ctx: &Ctx) -> Result<()> {
    for s in SOURCES {
        let ak = s.approved_key();
        for (name, cmd) in s.entries() {
            let missing = if s.folder.is_some() { false } else { exe_of(&cmd).is_some_and(|p| gone(&p)) };
            ctx.emit.row(
                "startup",
                json!({"scope": s.scope, "name": name, "command": cmd, "enabled": approved_on(&ak, &name), "missing": missing, "admin": s.admin()}),
            );
        }
    }
    Ok(())
}

fn filetime_now() -> u64 {
    let d = std::time::SystemTime::now().duration_since(std::time::UNIX_EPOCH).unwrap_or_default();
    d.as_secs() * 10_000_000 + u64::from(d.subsec_nanos() / 100) + 116_444_736_000_000_000
}

fn startup_set(ctx: &Ctx, scope: &str, name: &str, state: &str) -> Result<()> {
    let s = SOURCES.iter().find(|s| s.scope == scope).ok_or_else(|| anyhow!("unknown start-up scope {scope}"))?;
    let on = match state {
        "on" => true,
        "off" => false,
        _ => bail!("say on or off"),
    };
    if !s.entries().iter().any(|(n, _)| n == name) {
        bail!("{name} is not in the start-up list");
    }
    if s.admin() && !ctx.elevated {
        bail!("needs admin");
    }
    let mut b = vec![if on { 2u8 } else { 3u8 }, 0, 0, 0];
    b.extend_from_slice(&if on { 0 } else { filetime_now() }.to_le_bytes());
    if !ctx.dry_run {
        reg::set_raw(&s.approved_key(), name, &RegVal::Binary(b))?;
    }
    ctx.emit.row("startup", json!({"scope": s.scope, "name": name, "enabled": on}));
    Ok(())
}

// ---------------------------------------------------------------- installed programs

fn programs_list(ctx: &Ctx) -> Result<()> {
    let mut rows = Vec::new();
    for (root, scope) in UNINSTALL.iter().zip(["machine", "machine32", "user"]) {
        for sub in reg::subkeys(root) {
            let k = format!("{root}\\{sub}");
            let Some(name) = reg::get_str(&k, "DisplayName").map(|s| s.trim().to_string()).filter(|s| !s.is_empty()) else { continue };
            if reg::get_u32(&k, "SystemComponent") == Some(1) || reg::get_str(&k, "ParentKeyName").is_some() {
                continue;
            }
            let release = reg::get_str(&k, "ReleaseType").unwrap_or_default().to_ascii_lowercase();
            if release.contains("update") || release.contains("hotfix") {
                continue;
            }
            let un = reg::get_str(&k, "UninstallString").filter(|s| !s.trim().is_empty());
            rows.push(json!({
                "key": k,
                "scope": scope,
                "name": name,
                "publisher": reg::get_str(&k, "Publisher").unwrap_or_default().trim(),
                "version": reg::get_str(&k, "DisplayVersion").unwrap_or_default().trim(),
                "bytes": u64::from(reg::get_u32(&k, "EstimatedSize").unwrap_or(0)) * 1024,
                "date": reg::get_str(&k, "InstallDate").unwrap_or_default(),
                "removable": un.is_some() && reg::get_u32(&k, "NoRemove") != Some(1),
            }));
        }
    }
    rows.sort_by_key(|r| r["name"].as_str().unwrap_or("").to_lowercase());
    for r in rows {
        ctx.emit.row("programs", r);
    }
    Ok(())
}

/// Split a command line into the program and the rest.
fn split_cmd(s: &str) -> Option<(String, String)> {
    let s = sys::expand(s.trim());
    if s.is_empty() {
        return None;
    }
    if let Some(rest) = s.strip_prefix('"') {
        let (exe, args) = rest.split_once('"')?;
        return Some((exe.to_string(), args.trim_start().to_string()));
    }
    let low = s.to_ascii_lowercase();
    if let Some(i) = low.find(".exe") {
        let end = i + 4;
        return Some((s[..end].to_string(), s[end..].trim_start().to_string()));
    }
    let (a, b) = s.split_once(' ').unwrap_or((&s, ""));
    Some((a.to_string(), b.trim_start().to_string()))
}

/// msiexec /I{guid} opens the installer's repair page; /X{guid} removes.
fn msi_remove_args(args: &str) -> String {
    let low = args.to_ascii_lowercase();
    match low.find("/i") {
        Some(i) if low[i + 2..].trim_start().starts_with('{') => format!("{}/X{}", &args[..i], &args[i + 2..]),
        _ => args.to_string(),
    }
}

fn programs_uninstall(ctx: &Ctx, key: &str) -> Result<()> {
    let ok_root = UNINSTALL.iter().any(|r| {
        key.len() > r.len() + 1 && key[..r.len()].eq_ignore_ascii_case(r) && key.as_bytes()[r.len()] == b'\\' && !key[r.len() + 1..].contains('\\')
    });
    if !ok_root {
        bail!("not an installed program entry");
    }
    let un = reg::get_str(key, "UninstallString").filter(|s| !s.trim().is_empty()).ok_or_else(|| anyhow!("this program has no uninstaller"))?;
    let (exe, mut args) = split_cmd(&un).ok_or_else(|| anyhow!("can't read the uninstaller"))?;
    if exe.to_ascii_lowercase().ends_with("msiexec.exe") || exe.eq_ignore_ascii_case("msiexec") {
        args = msi_remove_args(&args);
    }
    if key.starts_with("HKLM") && !ctx.elevated {
        bail!("needs admin");
    }
    if ctx.dry_run {
        ctx.emit.row("programs", json!({"key": key, "removed": false, "note": "dry run"}));
        return Ok(());
    }
    // The program's own uninstaller is meant to be seen, so it gets a window.
    let mut c = std::process::Command::new(&exe);
    if !args.is_empty() {
        c.raw_arg(&args);
    }
    let status = c.status().with_context(|| format!("start {exe}"))?;
    std::thread::sleep(std::time::Duration::from_millis(1500));
    let removed = !reg::key_exists(key);
    ctx.emit.row("programs", json!({"key": key, "removed": removed, "code": status.code()}));
    Ok(())
}

// ---------------------------------------------------------------- Windows Update

const PS_UTF8: &str = "[Console]::OutputEncoding=[Text.UTF8Encoding]::new($false); $ErrorActionPreference='Stop'; ";

fn is_guid(s: &str) -> bool {
    s.len() == 36 && s.bytes().enumerate().all(|(i, c)| if matches!(i, 8 | 13 | 18 | 23) { c == b'-' } else { c.is_ascii_hexdigit() })
}

fn updates_list(ctx: &Ctx) -> Result<()> {
    let script = format!(
        "{PS_UTF8}$s=New-Object -ComObject Microsoft.Update.Session; \
         $r=$s.CreateUpdateSearcher().Search('IsInstalled=0 and IsHidden=0 or IsInstalled=0 and IsHidden=1'); \
         $o=@(foreach($u in $r.Updates){{ [pscustomobject]@{{ id=$u.Identity.UpdateID; title=$u.Title; hidden=[bool]$u.IsHidden; \
         bytes=[int64]$u.MaxDownloadSize; kb=(@($u.KBArticleIDs) -join ','); driver=($u.Type -eq 2) }} }}); \
         ConvertTo-Json -InputObject $o -Compress -Depth 3"
    );
    let o = proc::powershell(&script)?;
    if o.code != 0 {
        bail!("Windows Update did not answer: {}", last_line(&o.text()));
    }
    let text = String::from_utf8_lossy(&o.stdout).trim().trim_start_matches('\u{feff}').to_string();
    let v: Value = serde_json::from_str(if text.is_empty() { "[]" } else { &text }).context("read the update list")?;
    let list = match v {
        Value::Array(a) => a,
        Value::Null => Vec::new(),
        other => vec![other],
    };
    for u in list {
        ctx.emit.row("updates", u);
    }
    Ok(())
}

fn updates_hide(ctx: &Ctx, id: &str, hide: bool) -> Result<()> {
    if !is_guid(id) {
        bail!("not an update id");
    }
    if !ctx.elevated {
        bail!("needs admin");
    }
    if ctx.dry_run {
        ctx.emit.row("updates", json!({"id": id, "hidden": !hide, "note": "dry run"}));
        return Ok(());
    }
    let flag = if hide { "$true" } else { "$false" };
    let script = format!(
        "{PS_UTF8}$s=New-Object -ComObject Microsoft.Update.Session; \
         $r=$s.CreateUpdateSearcher().Search(\"UpdateID='{id}' and IsHidden=0 or UpdateID='{id}' and IsHidden=1\"); \
         if($r.Updates.Count -eq 0){{ throw 'That update is no longer offered' }}; \
         foreach($u in $r.Updates){{ $u.IsHidden={flag} }}"
    );
    let o = proc::powershell(&script)?;
    if o.code != 0 {
        bail!("{}", last_line(&o.text()));
    }
    ctx.emit.row("updates", json!({"id": id, "hidden": hide}));
    Ok(())
}

// ---------------------------------------------------------------- folder sizes

const REPARSE: u32 = 0x400;

/// Size of a folder tree. Never follows links or junctions, skips what it can't read.
fn tree_size(root: &Path, top: &Mutex<BinaryHeap<Reverse<(u64, String)>>>, keep: usize) -> (u64, u64) {
    let (mut bytes, mut files) = (0u64, 0u64);
    let mut stack = vec![root.to_path_buf()];
    let mut local: Vec<(u64, String)> = Vec::new();
    let mut floor = 0u64;
    while let Some(dir) = stack.pop() {
        let Ok(rd) = std::fs::read_dir(&dir) else { continue };
        for e in rd.flatten() {
            let Ok(md) = e.metadata() else { continue };
            if md.file_attributes() & REPARSE != 0 && md.is_dir() {
                continue;
            }
            if md.is_dir() {
                stack.push(e.path());
            } else {
                let n = md.len();
                bytes += n;
                files += 1;
                if n > floor {
                    local.push((n, e.path().to_string_lossy().into_owned()));
                    if local.len() >= keep * 4 {
                        local.sort_unstable_by(|a, b| b.0.cmp(&a.0));
                        local.truncate(keep);
                        floor = local.last().map(|x| x.0).unwrap_or(0);
                    }
                }
            }
        }
    }
    let mut heap = top.lock().unwrap_or_else(|p| p.into_inner());
    for f in local {
        heap.push(Reverse(f));
        if heap.len() > keep {
            heap.pop();
        }
    }
    (bytes, files)
}

fn space(ctx: &Ctx, dir: &str, keep: usize) -> Result<()> {
    if dir.trim().is_empty() {
        bail!("say which folder");
    }
    let root = PathBuf::from(sys::expand(dir.trim()));
    let rd = std::fs::read_dir(&root).with_context(|| format!("open {}", root.display()))?;
    let keep = keep.clamp(1, 200);
    let top: Mutex<BinaryHeap<Reverse<(u64, String)>>> = Mutex::new(BinaryHeap::new());
    let mut kids = Vec::new();
    let (mut loose_bytes, mut loose_files) = (0u64, 0u64);
    for e in rd.flatten() {
        let Ok(md) = e.metadata() else { continue };
        if md.is_dir() {
            if md.file_attributes() & REPARSE == 0 {
                kids.push(e.path());
            }
        } else {
            loose_bytes += md.len();
            loose_files += 1;
            let mut h = top.lock().unwrap_or_else(|p| p.into_inner());
            h.push(Reverse((md.len(), e.path().to_string_lossy().into_owned())));
            if h.len() > keep {
                h.pop();
            }
        }
    }
    let total = kids.len() as u64;
    let next = AtomicUsize::new(0);
    let done = AtomicUsize::new(0);
    let sums = Mutex::new((loose_bytes, loose_files));
    let workers = std::thread::available_parallelism().map(|n| n.get()).unwrap_or(4).clamp(2, 4);
    std::thread::scope(|s| {
        for _ in 0..workers {
            s.spawn(|| loop {
                let i = next.fetch_add(1, Ordering::SeqCst);
                let Some(p) = kids.get(i) else { break };
                let (b, f) = tree_size(p, &top, keep);
                {
                    let mut t = sums.lock().unwrap_or_else(|p| p.into_inner());
                    t.0 += b;
                    t.1 += f;
                }
                let name = p.file_name().map(|n| n.to_string_lossy().into_owned()).unwrap_or_default();
                ctx.emit.row("space", json!({"kind": "folder", "path": p.to_string_lossy(), "name": name, "bytes": b, "files": f}));
                let d = done.fetch_add(1, Ordering::SeqCst) as u64 + 1;
                ctx.emit.progress("tool.space", d, total, &name);
            });
        }
    });
    let mut files: Vec<(u64, String)> = top.into_inner().unwrap_or_else(|p| p.into_inner()).into_iter().map(|Reverse(x)| x).collect();
    files.sort_unstable_by(|a, b| b.0.cmp(&a.0));
    for (b, p) in files {
        ctx.emit.row("space", json!({"kind": "file", "path": p, "bytes": b}));
    }
    let (b, f) = sums.into_inner().unwrap_or_else(|p| p.into_inner());
    ctx.emit.row("space", json!({"kind": "total", "path": root.to_string_lossy(), "bytes": b, "files": f, "loose": loose_bytes}));
    Ok(())
}

// ---------------------------------------------------------------- PC facts

#[link(name = "ntdll", kind = "raw-dylib")]
extern "system" {
    fn NtQueryTimerResolution(coarsest: *mut u32, finest: *mut u32, current: *mut u32) -> i32;
}

fn timer_ms() -> Option<f64> {
    let (mut a, mut b, mut c) = (0u32, 0u32, 0u32);
    let st = unsafe { NtQueryTimerResolution(&mut a, &mut b, &mut c) };
    (st >= 0 && c > 0).then(|| f64::from(c) / 10_000.0)
}

fn memory() -> (u64, u64) {
    use windows_sys::Win32::System::SystemInformation::{GlobalMemoryStatusEx, MEMORYSTATUSEX};
    let mut m: MEMORYSTATUSEX = unsafe { std::mem::zeroed() };
    m.dwLength = std::mem::size_of::<MEMORYSTATUSEX>() as u32;
    if unsafe { GlobalMemoryStatusEx(&mut m) } == 0 {
        return (0, 0);
    }
    (m.ullTotalPhys, m.ullAvailPhys)
}

fn fixed_drives() -> Vec<Value> {
    use windows_sys::Win32::Storage::FileSystem::{GetDriveTypeW, GetLogicalDrives};
    let mask = unsafe { GetLogicalDrives() };
    let mut out = Vec::new();
    for i in 0..26u32 {
        if mask & (1 << i) == 0 {
            continue;
        }
        let root = format!("{}:\\", (b'A' + i as u8) as char);
        let w: Vec<u16> = root.encode_utf16().chain(Some(0)).collect();
        if unsafe { GetDriveTypeW(w.as_ptr()) } != 3 {
            continue;
        }
        if let Some((total, free)) = disk(&root) {
            out.push(json!({"drive": &root[..2], "total": total, "free": free}));
        }
    }
    out
}

fn gpus() -> Vec<String> {
    let class = "HKLM\\SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}";
    let mut v: Vec<String> = Vec::new();
    for sub in reg::subkeys(class) {
        if sub.len() != 4 || !sub.bytes().all(|c| c.is_ascii_digit()) {
            continue;
        }
        if let Some(d) = reg::get_str(&format!("{class}\\{sub}"), "DriverDesc") {
            let d = d.trim().to_string();
            if !d.is_empty() && !v.contains(&d) {
                v.push(d);
            }
        }
    }
    v
}

fn info(ctx: &Ctx) -> Result<()> {
    let cv = "HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
    let build = sys::build();
    let mut name = reg::get_str(cv, "ProductName").unwrap_or_else(|| "Windows".into());
    if build >= 22000 {
        name = name.replace("Windows 10", "Windows 11");
    }
    let (ram_total, ram_free) = memory();
    let uptime = unsafe { windows_sys::Win32::System::SystemInformation::GetTickCount64() } / 1000;
    ctx.emit.row(
        "info",
        json!({
            "windows": name,
            "version": reg::get_str(cv, "DisplayVersion").unwrap_or_default(),
            "build": build,
            "revision": reg::get_u32(cv, "UBR").unwrap_or(0),
            "cpu": reg::get_str("HKLM\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", "ProcessorNameString").unwrap_or_default().trim(),
            "threads": std::thread::available_parallelism().map(|n| n.get()).unwrap_or(0),
            "gpus": gpus(),
            "ram_total": ram_total,
            "ram_free": ram_free,
            "uptime": uptime,
            "timer_ms": timer_ms(),
            "drives": fixed_drives(),
            "elevated": ctx.elevated,
            "undo_entries": ctx.journal.ids().len(),
        }),
    );
    Ok(())
}

// ---------------------------------------------------------------- provider

pub struct Tools {
    jobs: Vec<(Job, Item)>,
}

pub fn provider() -> Box<dyn Provider> {
    Box::new(Tools { jobs: repairs() })
}

impl Provider for Tools {
    fn name(&self) -> &'static str {
        "tools"
    }

    fn items(&self) -> Vec<Item> {
        reg_items().into_iter().chain(self.jobs.iter().map(|(_, i)| i.clone())).collect()
    }

    fn scan(&self, _ctx: &Ctx, ids: &[String]) -> Vec<State> {
        let want = |id: &str| ids.is_empty() || ids.iter().any(|i| i == id);
        let mut out: Vec<State> = std::thread::scope(|s| {
            let jobs: Vec<_> = REG_CLEAN
                .iter()
                .filter(|(_, id)| want(id))
                .map(|&(kind, id)| {
                    s.spawn(move || {
                        let dead = find_dead(kind);
                        let mut st = State::size(id, 0, dead.len() as u64);
                        if !dead.is_empty() {
                            st.note = Some(summary(&dead));
                        }
                        st
                    })
                })
                .collect();
            jobs.into_iter().filter_map(|j| j.join().ok()).collect()
        });
        for (job, it) in &self.jobs {
            if !want(&it.id) {
                continue;
            }
            let st = match job {
                Job::TimeSync if !svc::exists("W32Time") => State::missing(&it.id, "The time service is not on this PC"),
                Job::RestorePoint if reg::get_u32("HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\SystemRestore", "RPSessionInterval") == Some(0) => {
                    State::missing(&it.id, "System Restore is off on this PC")
                }
                _ => State { id: it.id.clone(), available: true, ..Default::default() },
            };
            out.push(st);
        }
        out
    }

    fn apply(&self, ctx: &Ctx, id: &str) -> Result<Done> {
        if let Some(&(kind, _)) = REG_CLEAN.iter().find(|(_, i)| *i == id) {
            return clean_leftovers(ctx, id, kind);
        }
        if let Some((job, _)) = self.jobs.iter().find(|(_, i)| i.id == id) {
            return run_job(ctx, id, *job);
        }
        bail!("unknown item {id}")
    }

    fn revert(&self, ctx: &Ctx, id: &str) -> Result<Done> {
        if REG_CLEAN.iter().any(|(_, i)| *i == id) {
            return ctx.journal.undo(id, ctx.dry_run);
        }
        bail!("A finished job can't be undone")
    }

    fn run_tool(&self, ctx: &Ctx, name: &str, args: &[String]) -> Option<Result<()>> {
        let a = |i: usize| args.get(i).map(String::as_str).unwrap_or("");
        Some(match name {
            "info" => info(ctx),
            "startup" => match a(0) {
                "list" => startup_list(ctx),
                "set" => startup_set(ctx, a(1), a(2), a(3)),
                _ => Err(anyhow!("startup list | startup set <scope> <name> on|off")),
            },
            "programs" => match a(0) {
                "list" => programs_list(ctx),
                "uninstall" => programs_uninstall(ctx, a(1)),
                _ => Err(anyhow!("programs list | programs uninstall <key>")),
            },
            "updates" => match a(0) {
                "list" => updates_list(ctx),
                "hide" => updates_hide(ctx, a(1), true),
                "unhide" => updates_hide(ctx, a(1), false),
                _ => Err(anyhow!("updates list | updates hide <id> | updates unhide <id>")),
            },
            "space" => space(ctx, a(0), a(1).parse().unwrap_or(25)),
            _ => return None,
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn reads_percent() {
        assert_eq!(pct("Verification 45% complete."), Some(45));
        assert_eq!(pct("[=====    23.4%    ]"), Some(23));
        assert_eq!(pct("no number here"), None);
    }

    #[test]
    fn finds_the_program() {
        assert_eq!(exe_of("\"C:\\Program Files\\App\\app.exe\" --min"), Some(PathBuf::from("C:\\Program Files\\App\\app.exe")));
        assert_eq!(exe_of("C:\\Program Files\\App\\app.exe /tray"), Some(PathBuf::from("C:\\Program Files\\App\\app.exe")));
        assert_eq!(exe_of("rundll32.exe shell32.dll,Foo"), None);
        assert_eq!(exe_of("\\\\server\\share\\x.exe"), None);
    }

    #[test]
    fn msi_removal() {
        let (exe, args) = split_cmd("MsiExec.exe /I{12345678-1234-1234-1234-123456789012}").unwrap();
        assert_eq!(exe, "MsiExec.exe");
        assert_eq!(msi_remove_args(&args), "/X{12345678-1234-1234-1234-123456789012}");
        assert_eq!(msi_remove_args("/X{1}"), "/X{1}");
    }

    #[test]
    fn guid_check() {
        assert!(is_guid("381b4222-f694-41f0-9685-ff5bb260df2e"));
        assert!(!is_guid("381b4222-f694-41f0-9685-ff5bb260df2e' or 1=1"));
    }

    #[test]
    fn a_missing_drive_is_never_gone() {
        assert!(!gone(Path::new("Q:\\nothing\\here.exe")) || Path::new("Q:\\").exists());
        assert!(gone(Path::new("C:\\swo-test-surely-missing\\x.exe")));
        assert!(!gone(Path::new("C:\\Windows\\System32\\cmd.exe")));
    }

    #[test]
    fn items_are_paged() {
        for i in provider().items() {
            assert!(i.id.starts_with(&format!("{}.", i.page)), "{}", i.id);
        }
    }
}
