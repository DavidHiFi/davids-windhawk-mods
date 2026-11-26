//! swo-clean: the "Clean up" page. Frees space and wipes traces.
//!
//! The cleaner list and its approach follow BleachBit (https://www.bleachbit.org),
//! Copyright (C) 2008-2026 Andrew Ziem and contributors, GPL-3.0-or-later,
//! ported to Rust for Seamless Windows Optimizer by DavidHiFi.
//!
//! Safety rules every cleaner follows:
//! - Never follow a junction or symbolic link, and never delete one.
//! - Never delete the folder a cleaner points at, only what is inside it.
//! - Files in use are skipped, never forced.
//! - Temp folders only lose files older than a day, so running installers keep theirs.
//! - Browser and app data is left alone while that program is open.
//! - `--dry-run` measures and deletes nothing.

use anyhow::{anyhow, bail, Result};
use std::os::windows::fs::MetadataExt;
use std::path::{Path, PathBuf};
use std::time::{Duration, SystemTime};
use swo_core::{proc, sys, Ctx, Done, Item, Kind, Provider, Risk, State};

const ATTR_READONLY: u32 = 0x1;
const ATTR_REPARSE: u32 = 0x400;
const MAX_DEPTH: u32 = 48;

/// Where a cleaner looks. Paths take %VARS% and `*` / `?` in any folder name.
#[derive(Clone)]
enum T {
    /// Everything inside these folders; the folders themselves stay.
    Inside(String),
    /// Files directly inside these folders whose names match one of the `|` patterns.
    Files(String, String),
}

#[derive(Clone, Copy, PartialEq)]
enum Special {
    None,
    RecycleBin,
    DeliveryOptimization,
}

struct Rule {
    id: String,
    group: &'static str,
    name: String,
    desc: String,
    risk: Risk,
    pick: bool,
    admin: bool,
    /// Only files at least this many days old.
    age_days: u64,
    /// (process name, what to call it) that must be closed first.
    closed: Vec<(&'static str, &'static str)>,
    warn: Option<String>,
    special: Special,
    targets: Vec<T>,
}

impl Rule {
    fn new(id: &str, group: &'static str, name: &str, desc: &str) -> Self {
        Rule {
            id: format!("clean.{id}"),
            group,
            name: name.into(),
            desc: desc.into(),
            risk: Risk::Safe,
            pick: false,
            admin: false,
            age_days: 0,
            closed: Vec::new(),
            warn: None,
            special: Special::None,
            targets: Vec::new(),
        }
    }
    fn inside(mut self, p: &str) -> Self {
        self.targets.push(T::Inside(p.into()));
        self
    }
    fn files(mut self, dir: &str, pat: &str) -> Self {
        self.targets.push(T::Files(dir.into(), pat.into()));
        self
    }
    fn pick(mut self) -> Self {
        self.pick = true;
        self
    }
    fn admin(mut self) -> Self {
        self.admin = true;
        self
    }
    fn risk(mut self, r: Risk) -> Self {
        self.risk = r;
        self
    }
    fn age(mut self, days: u64) -> Self {
        self.age_days = days;
        self
    }
    fn closed(mut self, exe: &'static str, label: &'static str) -> Self {
        self.closed.push((exe, label));
        self
    }
    fn warn(mut self, w: &str) -> Self {
        self.warn = Some(w.into());
        self
    }
    fn special(mut self, s: Special) -> Self {
        self.special = s;
        self
    }
}

struct Chromium {
    key: &'static str,
    label: &'static str,
    /// The "User Data" folder.
    data: &'static str,
    exe: &'static str,
}

const CHROMIUM: &[Chromium] = &[
    Chromium { key: "edge", label: "Edge", data: r"%LOCALAPPDATA%\Microsoft\Edge\User Data", exe: "msedge.exe" },
    Chromium { key: "chrome", label: "Chrome", data: r"%LOCALAPPDATA%\Google\Chrome\User Data", exe: "chrome.exe" },
    Chromium { key: "brave", label: "Brave", data: r"%LOCALAPPDATA%\BraveSoftware\Brave-Browser\User Data", exe: "brave.exe" },
    Chromium { key: "vivaldi", label: "Vivaldi", data: r"%LOCALAPPDATA%\Vivaldi\User Data", exe: "vivaldi.exe" },
];

/// Chromium-based apps (Electron) keep the same cache folders in one data folder.
struct ElectronApp {
    key: &'static str,
    label: &'static str,
    data: &'static str,
    exe: &'static str,
}

const ELECTRON: &[ElectronApp] = &[
    ElectronApp { key: "discord", label: "Discord", data: r"%APPDATA%\discord", exe: "Discord.exe" },
    ElectronApp { key: "vscode", label: "VS Code", data: r"%APPDATA%\Code", exe: "Code.exe" },
    ElectronApp { key: "teams", label: "Teams (classic)", data: r"%APPDATA%\Microsoft\Teams", exe: "Teams.exe" },
];

const SHADER_WARN: &str = "Games rebuild these, so each game may stutter for a minute the first time you play it.";

fn rules() -> Vec<Rule> {
    let mut v = vec![
        // Windows
        Rule::new("windows-temp", "Windows", "Windows temp files", "Leftovers from installers and updates in the Windows temp folder.")
            .inside(r"%WINDIR%\Temp")
            .age(1)
            .admin()
            .pick(),
        Rule::new("user-temp", "Windows", "Your temp files", "Leftovers programs put in your own temp folder.")
            .inside(r"%LOCALAPPDATA%\Temp")
            .age(1)
            .pick(),
        Rule::new("update-downloads", "Windows", "Windows Update downloads", "Update files Windows already installed and no longer needs.")
            .inside(r"%WINDIR%\SoftwareDistribution\Download")
            .age(1)
            .admin()
            .pick(),
        Rule::new("delivery-optimization", "Windows", "Update sharing cache", "Update pieces Windows kept to share with other PCs.")
            .inside(r"%WINDIR%\ServiceProfiles\NetworkService\AppData\Local\Microsoft\Windows\DeliveryOptimization\Cache")
            .special(Special::DeliveryOptimization)
            .admin()
            .pick(),
        Rule::new("error-reports", "Windows", "Error reports", "Problem reports Windows already sent or no longer needs.")
            .inside(r"%PROGRAMDATA%\Microsoft\Windows\WER\ReportArchive")
            .inside(r"%PROGRAMDATA%\Microsoft\Windows\WER\ReportQueue")
            .inside(r"%LOCALAPPDATA%\Microsoft\Windows\WER\ReportArchive")
            .inside(r"%LOCALAPPDATA%\Microsoft\Windows\WER\ReportQueue")
            .admin()
            .pick(),
        Rule::new("windows-logs", "Windows", "Old Windows logs", "Setup and repair logs older than a week.")
            .inside(r"%WINDIR%\Logs\CBS")
            .inside(r"%WINDIR%\Logs\DISM")
            .inside(r"%WINDIR%\Logs\MoSetup")
            .inside(r"%WINDIR%\Logs\WindowsUpdate")
            .age(7)
            .admin()
            .pick(),
        Rule::new("system-dumps", "Windows", "System crash dumps", "Memory dumps Windows saved after a blue screen. One can be many gigabytes.")
            .files(r"%WINDIR%", "MEMORY.DMP")
            .files(r"%WINDIR%\Minidump", "*.dmp")
            .inside(r"%WINDIR%\LiveKernelReports")
            .admin()
            .risk(Risk::Moderate)
            .warn("These explain a blue screen. Keep them while you are chasing one."),
        Rule::new("app-dumps", "Windows", "App crash dumps", "Dumps programs left when they crashed.")
            .inside(r"%LOCALAPPDATA%\CrashDumps")
            .risk(Risk::Moderate)
            .warn("These name the app or mod that crashed. Keep them while you are chasing a crash."),
        Rule::new("thumbnails", "Windows", "Picture previews", "Small previews of your pictures and videos. Explorer makes them again when needed.")
            .files(r"%LOCALAPPDATA%\Microsoft\Windows\Explorer", "thumbcache_*.db"),
        Rule::new("recycle-bin", "Windows", "Recycle Bin", "Everything in the Recycle Bin on every drive.")
            .special(Special::RecycleBin)
            .risk(Risk::Moderate)
            .pick()
            .warn("Files in the Recycle Bin are gone for good after this."),
        // Games
        Rule::new("directx-shaders", "Games", "DirectX shader cache", "Shaders Windows saved for games and apps.")
            .inside(r"%LOCALAPPDATA%\D3DSCache")
            .risk(Risk::Moderate)
            .warn(SHADER_WARN),
        Rule::new("nvidia-shaders", "Games", "NVIDIA shader cache", "Shaders the NVIDIA driver saved for games.")
            .inside(r"%LOCALAPPDATA%\NVIDIA\DXCache")
            .inside(r"%LOCALAPPDATA%\NVIDIA\GLCache")
            .risk(Risk::Moderate)
            .warn(SHADER_WARN),
        Rule::new("amd-shaders", "Games", "AMD shader cache", "Shaders the AMD driver saved for games.")
            .inside(r"%LOCALAPPDATA%\AMD\DxCache")
            .inside(r"%LOCALAPPDATA%\AMD\DxcCache")
            .inside(r"%LOCALAPPDATA%\AMD\VkCache")
            .risk(Risk::Moderate)
            .warn(SHADER_WARN),
        Rule::new("steam-web", "Games", "Steam web cache", "Store and community pages Steam saved.")
            .inside(r"%LOCALAPPDATA%\Steam\htmlcache")
            .closed("steamwebhelper.exe", "Steam")
            .pick(),
    ];

    for b in CHROMIUM {
        let prof = format!(r"{}\*", b.data);
        v.push(
            Rule::new(&format!("{}-cache", b.key), "Browsers", &format!("{} cache", b.label), &format!("Pages and pictures {} saved to load sites faster.", b.label))
                .inside(&format!(r"{prof}\Cache"))
                .inside(&format!(r"{prof}\Code Cache"))
                .inside(&format!(r"{prof}\GPUCache"))
                .inside(&format!(r"{prof}\Service Worker\CacheStorage"))
                .inside(&format!(r"{}\ShaderCache", b.data))
                .inside(&format!(r"{}\GrShaderCache", b.data))
                .closed(b.exe, b.label)
                .pick(),
        );
        v.push(
            Rule::new(&format!("{}-history", b.key), "Browsers", &format!("{} history", b.label), &format!("The list of sites you visited in {}.", b.label))
                .files(&prof, "History|History-journal|Visited Links|Top Sites|Top Sites-journal|Shortcuts|Shortcuts-journal")
                .closed(b.exe, b.label)
                .risk(Risk::Advanced),
        );
        v.push(
            Rule::new(&format!("{}-cookies", b.key), "Browsers", &format!("{} cookies", b.label), &format!("Site cookies {} keeps.", b.label))
                .files(&format!(r"{prof}\Network"), "Cookies|Cookies-journal")
                .files(&prof, "Cookies|Cookies-journal")
                .closed(b.exe, b.label)
                .risk(Risk::Advanced)
                .warn("Signs you out of every website."),
        );
    }

    v.push(
        Rule::new("firefox-cache", "Browsers", "Firefox cache", "Pages and pictures Firefox saved to load sites faster.")
            .inside(r"%LOCALAPPDATA%\Mozilla\Firefox\Profiles\*\cache2")
            .inside(r"%LOCALAPPDATA%\Mozilla\Firefox\Profiles\*\startupCache")
            .closed("firefox.exe", "Firefox")
            .pick(),
    );
    v.push(
        Rule::new("firefox-cookies", "Browsers", "Firefox cookies", "Site cookies Firefox keeps.")
            .files(r"%APPDATA%\Mozilla\Firefox\Profiles\*", "cookies.sqlite|cookies.sqlite-wal|cookies.sqlite-shm")
            .closed("firefox.exe", "Firefox")
            .risk(Risk::Advanced)
            .warn("Signs you out of every website."),
    );

    for a in ELECTRON {
        v.push(
            Rule::new(&format!("{}-cache", a.key), "Apps", &format!("{} cache", a.label), &format!("Pictures and code {} saved to start faster.", a.label))
                .inside(&format!(r"{}\Cache", a.data))
                .inside(&format!(r"{}\Code Cache", a.data))
                .inside(&format!(r"{}\GPUCache", a.data))
                .inside(&format!(r"{}\CachedData", a.data))
                .closed(a.exe, a.label)
                .pick(),
        );
    }
    v.push(
        Rule::new("spotify-cache", "Apps", "Spotify cache", "Songs Spotify saved while streaming.")
            .inside(r"%LOCALAPPDATA%\Spotify\Data")
            .inside(r"%LOCALAPPDATA%\Spotify\Browser\Cache")
            .closed("Spotify.exe", "Spotify")
            .pick(),
    );

    // Traces
    v.push(
        Rule::new("recent-files", "Traces", "Recent files list", "The list of files you opened lately, shown in Explorer and Start.")
            .files(r"%APPDATA%\Microsoft\Windows\Recent", "*.lnk")
            .risk(Risk::Moderate),
    );
    v.push(
        Rule::new("office-recent", "Traces", "Office recent files", "The list of documents you opened lately in Office.")
            .files(r"%APPDATA%\Microsoft\Office\Recent", "*.lnk|index.dat")
            .risk(Risk::Moderate),
    );
    v
}

// ---------------------------------------------------------------- paths

/// `*` and `?` wildcard match, ignoring case.
fn wild(pat: &str, name: &str) -> bool {
    let p: Vec<char> = pat.to_lowercase().chars().collect();
    let n: Vec<char> = name.to_lowercase().chars().collect();
    let (mut pi, mut ni) = (0usize, 0usize);
    let (mut star, mut mark) = (usize::MAX, 0usize);
    while ni < n.len() {
        if pi < p.len() && (p[pi] == '?' || p[pi] == n[ni]) {
            pi += 1;
            ni += 1;
        } else if pi < p.len() && p[pi] == '*' {
            star = pi;
            mark = ni;
            pi += 1;
        } else if star != usize::MAX {
            pi = star + 1;
            mark += 1;
            ni = mark;
        } else {
            return false;
        }
    }
    while pi < p.len() && p[pi] == '*' {
        pi += 1;
    }
    pi == p.len()
}

fn is_link(md: &std::fs::Metadata) -> bool {
    md.file_attributes() & ATTR_REPARSE != 0
}

/// Expand a pattern into the real folders it names. Links never count.
fn resolve(pat: &str) -> Vec<PathBuf> {
    let full = sys::expand(pat);
    if full.contains('%') {
        return Vec::new();
    }
    let mut segs = full.split('\\').filter(|s| !s.is_empty());
    let Some(drive) = segs.next() else { return Vec::new() };
    if !drive.ends_with(':') {
        return Vec::new();
    }
    let mut cur = vec![PathBuf::from(format!("{drive}\\"))];
    for seg in segs {
        let mut next = Vec::new();
        for base in &cur {
            if seg.contains(['*', '?']) {
                if let Ok(rd) = std::fs::read_dir(base) {
                    for e in rd.flatten() {
                        let name = e.file_name().to_string_lossy().to_string();
                        if !wild(seg, &name) {
                            continue;
                        }
                        if let Ok(md) = std::fs::symlink_metadata(e.path()) {
                            if md.is_dir() && !is_link(&md) {
                                next.push(e.path());
                            }
                        }
                    }
                }
            } else {
                let p = base.join(seg);
                if let Ok(md) = std::fs::symlink_metadata(&p) {
                    if md.is_dir() && !is_link(&md) {
                        next.push(p);
                    }
                }
            }
        }
        cur = next;
        if cur.is_empty() {
            break;
        }
    }
    cur
}

// ---------------------------------------------------------------- walking

#[derive(Default)]
struct Tally {
    bytes: u64,
    files: u64,
    skipped: u64,
}

struct Walk {
    delete: bool,
    cutoff: Option<SystemTime>,
}

impl Walk {
    fn old_enough(&self, md: &std::fs::Metadata) -> bool {
        match self.cutoff {
            None => true,
            Some(c) => md.modified().map(|m| m <= c).unwrap_or(false),
        }
    }

    fn file(&self, p: &Path, md: &std::fs::Metadata, t: &mut Tally) {
        if !self.old_enough(md) {
            return;
        }
        let len = md.len();
        if !self.delete {
            t.bytes += len;
            t.files += 1;
            return;
        }
        let mut r = std::fs::remove_file(p);
        if r.is_err() && md.file_attributes() & ATTR_READONLY != 0 {
            let mut perm = md.permissions();
            #[allow(clippy::permissions_set_readonly_false)]
            perm.set_readonly(false);
            if std::fs::set_permissions(p, perm).is_ok() {
                r = std::fs::remove_file(p);
            }
        }
        match r {
            Ok(()) => {
                t.bytes += len;
                t.files += 1;
            }
            Err(_) => t.skipped += 1,
        }
    }

    /// Everything under `dir`. Sub-folders go once empty; `dir` itself stays.
    fn inside(&self, dir: &Path, t: &mut Tally, depth: u32) {
        if depth > MAX_DEPTH {
            return;
        }
        let Ok(rd) = std::fs::read_dir(dir) else { return };
        for e in rd.flatten() {
            let p = e.path();
            let Ok(md) = std::fs::symlink_metadata(&p) else { continue };
            if is_link(&md) {
                continue;
            }
            if md.is_dir() {
                self.inside(&p, t, depth + 1);
                if self.delete && self.old_enough(&md) {
                    let _ = std::fs::remove_dir(&p);
                }
            } else {
                self.file(&p, &md, t);
            }
        }
    }

    fn matching(&self, dir: &Path, pats: &str, t: &mut Tally) {
        let Ok(rd) = std::fs::read_dir(dir) else { return };
        for e in rd.flatten() {
            let name = e.file_name().to_string_lossy().to_string();
            if !pats.split('|').any(|p| wild(p, &name)) {
                continue;
            }
            let p = e.path();
            let Ok(md) = std::fs::symlink_metadata(&p) else { continue };
            if md.is_file() && !is_link(&md) {
                self.file(&p, &md, t);
            }
        }
    }
}

fn run_targets(rule: &Rule, delete: bool) -> (Tally, bool) {
    let cutoff = (rule.age_days > 0).then(|| SystemTime::now() - Duration::from_secs(rule.age_days * 86_400));
    let w = Walk { delete, cutoff };
    let mut t = Tally::default();
    let mut found = false;
    for target in &rule.targets {
        match target {
            T::Inside(p) => {
                for d in resolve(p) {
                    found = true;
                    w.inside(&d, &mut t, 0);
                }
            }
            T::Files(dir, pats) => {
                for d in resolve(dir) {
                    found = true;
                    w.matching(&d, pats, &mut t);
                }
            }
        }
    }
    (t, found)
}

// ---------------------------------------------------------------- recycle bin

mod bin {
    use windows_sys::Win32::UI::Shell::{SHEmptyRecycleBinW, SHQueryRecycleBinW, SHERB_NOCONFIRMATION, SHERB_NOPROGRESSUI, SHERB_NOSOUND, SHQUERYRBINFO};

    /// (bytes, items) across every drive.
    pub fn size() -> Option<(u64, u64)> {
        let mut info: SHQUERYRBINFO = unsafe { std::mem::zeroed() };
        info.cbSize = std::mem::size_of::<SHQUERYRBINFO>() as u32;
        let hr = unsafe { SHQueryRecycleBinW(std::ptr::null(), &mut info) };
        if hr < 0 {
            return None;
        }
        let (b, n) = (info.i64Size, info.i64NumItems);
        Some((b.max(0) as u64, n.max(0) as u64))
    }

    pub fn empty() -> Result<(), i32> {
        let hr = unsafe { SHEmptyRecycleBinW(std::ptr::null_mut(), std::ptr::null(), SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND) };
        // E_UNEXPECTED comes back when the bin is already empty.
        if hr >= 0 || hr == 0x8000FFFFu32 as i32 {
            Ok(())
        } else {
            Err(hr)
        }
    }
}

// ---------------------------------------------------------------- provider

pub struct Clean {
    rules: Vec<Rule>,
}

pub fn provider() -> Box<dyn Provider> {
    Box::new(Clean { rules: rules() })
}

impl Clean {
    fn rule(&self, id: &str) -> Option<&Rule> {
        self.rules.iter().find(|r| r.id == id)
    }
}

fn open_app(rule: &Rule) -> Option<&'static str> {
    rule.closed.iter().find(|(exe, _)| sys::is_running(exe)).map(|(_, label)| *label)
}

fn measure(rule: &Rule) -> State {
    match rule.special {
        Special::RecycleBin => match bin::size() {
            Some((b, n)) => State::size(&rule.id, b, n),
            None => State::missing(&rule.id, "Could not read the Recycle Bin"),
        },
        _ => {
            let (t, found) = run_targets(rule, false);
            if !found {
                return State::missing(&rule.id, "Not on this PC");
            }
            let mut s = State::size(&rule.id, t.bytes, t.files);
            if let Some(app) = open_app(rule) {
                s.note = Some(format!("Close {app} first"));
            }
            s
        }
    }
}

impl Provider for Clean {
    fn name(&self) -> &'static str {
        "clean"
    }

    fn items(&self) -> Vec<Item> {
        self.rules
            .iter()
            .map(|r| {
                let mut it = Item::new(r.id.clone(), "clean", r.group, r.name.clone(), r.desc.clone(), Kind::Clean).risk(r.risk).no_undo();
                if r.pick {
                    it = it.pick();
                }
                if r.admin {
                    it = it.admin();
                }
                if let Some(w) = &r.warn {
                    it = it.warn(w.clone());
                }
                it
            })
            .collect()
    }

    fn scan(&self, _ctx: &Ctx, ids: &[String]) -> Vec<State> {
        let want: Vec<&Rule> = self.rules.iter().filter(|r| ids.is_empty() || ids.contains(&r.id)).collect();
        // Folders differ per rule, so measure them side by side.
        std::thread::scope(|s| {
            let hs: Vec<_> = want.iter().map(|r| s.spawn(move || measure(r))).collect();
            hs.into_iter().zip(want.iter()).map(|(h, r)| h.join().unwrap_or_else(|_| State::missing(&r.id, "scan failed"))).collect()
        })
    }

    fn apply(&self, ctx: &Ctx, id: &str) -> Result<Done> {
        let rule = self.rule(id).ok_or_else(|| anyhow!("unknown cleaner"))?;
        if let Some(app) = open_app(rule) {
            bail!("Close {app} first");
        }
        match rule.special {
            Special::RecycleBin => {
                let (b, n) = bin::size().unwrap_or((0, 0));
                if ctx.dry_run {
                    return Ok(Done { note: Some("dry run".into()), ..Done::freed(b, n) });
                }
                bin::empty().map_err(|hr| anyhow!("Recycle Bin would not empty (0x{hr:08X})"))?;
                Ok(Done::freed(b, n))
            }
            Special::DeliveryOptimization if !ctx.dry_run => {
                // Windows' own command stops and clears the cache safely.
                let (before, _) = run_targets(rule, false);
                let o = proc::powershell("Delete-DeliveryOptimizationCache -Force -ErrorAction Stop")?;
                if o.code != 0 {
                    // Fall back to removing the files the service is not holding.
                    let (t, _) = run_targets(rule, true);
                    return Ok(Done { note: Some("cleared what was not in use".into()), ..Done::freed(t.bytes, t.files) });
                }
                let (after, _) = run_targets(rule, false);
                Ok(Done::freed(before.bytes.saturating_sub(after.bytes), before.files.saturating_sub(after.files)))
            }
            _ => {
                let (t, found) = run_targets(rule, !ctx.dry_run);
                if !found {
                    return Ok(Done::note("Nothing to clean on this PC"));
                }
                let mut d = Done::freed(t.bytes, t.files);
                if ctx.dry_run {
                    d.note = Some("dry run".into());
                } else if t.skipped > 0 {
                    d.note = Some(format!("{} in use, left alone", t.skipped));
                }
                Ok(d)
            }
        }
    }

    fn revert(&self, _ctx: &Ctx, _id: &str) -> Result<Done> {
        bail!("Cleaned files can't be brought back")
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn wildcards() {
        assert!(wild("*.dmp", "Mini01.DMP"));
        assert!(wild("thumbcache_*.db", "thumbcache_256.db"));
        assert!(!wild("thumbcache_*.db", "iconcache_256.db"));
        assert!(wild("History", "history"));
        assert!(!wild("History", "History-journal"));
        assert!(wild("Profile ?", "Profile 1"));
    }

    #[test]
    fn ids_are_unique() {
        let r = rules();
        let mut ids: Vec<&str> = r.iter().map(|r| r.id.as_str()).collect();
        ids.sort();
        let n = ids.len();
        ids.dedup();
        assert_eq!(n, ids.len());
    }

    #[test]
    fn cleans_only_old_files_and_keeps_root() {
        let root = std::env::temp_dir().join(format!("swo-clean-test-{}", std::process::id()));
        let sub = root.join("a").join("b");
        std::fs::create_dir_all(&sub).unwrap();
        std::fs::write(sub.join("x.tmp"), b"12345").unwrap();
        std::fs::write(root.join("y.tmp"), b"123").unwrap();

        // Dry run measures, deletes nothing.
        let w = Walk { delete: false, cutoff: None };
        let mut t = Tally::default();
        w.inside(&root, &mut t, 0);
        assert_eq!((t.bytes, t.files), (8, 2));
        assert!(sub.join("x.tmp").exists());

        // A cutoff in the past keeps fresh files.
        let w = Walk { delete: true, cutoff: Some(SystemTime::now() - Duration::from_secs(86_400)) };
        let mut t = Tally::default();
        w.inside(&root, &mut t, 0);
        assert_eq!(t.files, 0);
        assert!(root.join("y.tmp").exists());

        // Real delete empties it but keeps the root folder.
        let w = Walk { delete: true, cutoff: None };
        let mut t = Tally::default();
        w.inside(&root, &mut t, 0);
        assert_eq!((t.bytes, t.files), (8, 2));
        assert!(root.exists());
        assert!(std::fs::read_dir(&root).unwrap().next().is_none());
        std::fs::remove_dir(&root).unwrap();
    }

    #[test]
    fn resolve_expands_wildcards() {
        let root = std::env::temp_dir().join(format!("swo-resolve-{}", std::process::id()));
        std::fs::create_dir_all(root.join("Default").join("Cache")).unwrap();
        std::fs::create_dir_all(root.join("Profile 1").join("Cache")).unwrap();
        std::fs::create_dir_all(root.join("Crashpad")).unwrap();
        let pat = format!(r"{}\*\Cache", root.display());
        let mut got = resolve(&pat);
        got.sort();
        assert_eq!(got.len(), 2);
        std::fs::remove_dir_all(&root).unwrap();
    }
}
