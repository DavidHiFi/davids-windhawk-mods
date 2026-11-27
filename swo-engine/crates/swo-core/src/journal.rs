//! Undo journal: one JSON file per item under %ProgramData%\SeamlessOptimizer\journal.
//!
//! An apply opens a [`Txn`], every change pushes how to undo it, and `commit`
//! saves the list. When an item is applied twice, the first recorded old value
//! for each target wins, so a revert always returns to the state before the
//! first apply. Revert replays the list backwards and removes the file.

use crate::item::Done;
use crate::{proc, reg, svc, task};
use anyhow::{anyhow, Context, Result};
use serde::{Deserialize, Serialize};
use std::path::PathBuf;

#[derive(Serialize, Deserialize, Clone, Debug)]
#[serde(tag = "op")]
pub enum Undo {
    /// Put a registry value back (`prev: None` = delete it).
    Reg { key: String, name: String, prev: Option<reg::RegVal> },
    /// We created this key: delete it on undo if it is left empty.
    RegKeyCreated { key: String },
    /// Put a service's start type back (2 auto, 3 manual, 4 disabled).
    Service { name: String, start: u32 },
    /// Put a scheduled task's enabled state back.
    Task { path: String, enabled: bool },
    /// Run a hidden command to undo (powercfg, dism, bcdedit).
    Cmd { exe: String, args: Vec<String> },
    /// Copy a backed-up file back.
    File { path: String, backup: String },
}

impl Undo {
    /// Two entries touching the same target count as one.
    fn target(&self) -> String {
        match self {
            Undo::Reg { key, name, .. } => format!("reg:{}\\{}", key.to_ascii_lowercase(), name.to_ascii_lowercase()),
            Undo::RegKeyCreated { key } => format!("key:{}", key.to_ascii_lowercase()),
            Undo::Service { name, .. } => format!("svc:{}", name.to_ascii_lowercase()),
            Undo::Task { path, .. } => format!("task:{}", path.to_ascii_lowercase()),
            Undo::Cmd { exe, args } => format!("cmd:{} {}", exe, args.join(" ")),
            Undo::File { path, .. } => format!("file:{}", path.to_ascii_lowercase()),
        }
    }

    fn run(&self) -> Result<()> {
        match self {
            Undo::Reg { key, name, prev: Some(v) } => reg::set_raw(key, name, v),
            Undo::Reg { key, name, prev: None } => reg::del_raw(key, name),
            Undo::RegKeyCreated { key } => {
                if reg::subkeys(key).is_empty() && reg::values(key).is_empty() {
                    reg::del_tree_raw(key)
                } else {
                    Ok(())
                }
            }
            Undo::Service { name, start } => svc::set_start_raw(name, *start),
            Undo::Task { path, enabled } => task::set_enabled_raw(path, *enabled),
            Undo::Cmd { exe, args } => {
                let a: Vec<&str> = args.iter().map(|s| s.as_str()).collect();
                let o = proc::run(exe, &a)?;
                if o.code != 0 {
                    return Err(anyhow!("{exe} exited {}: {}", o.code, o.text().trim()));
                }
                Ok(())
            }
            Undo::File { path, backup } => {
                std::fs::copy(backup, path)?;
                Ok(())
            }
        }
    }
}

pub struct Journal {
    dir: PathBuf,
}

/// Collects undo steps for one apply.
pub struct Txn<'a> {
    j: &'a Journal,
    id: String,
    ops: Vec<Undo>,
    pub dry_run: bool,
}

impl<'a> Txn<'a> {
    pub fn push(&mut self, u: Undo) {
        self.ops.push(u);
    }

    /// Save the steps, merged with anything already recorded for this item.
    pub fn commit(self) -> Result<()> {
        if self.dry_run || self.ops.is_empty() {
            return Ok(());
        }
        let mut all = self.j.load(&self.id)?;
        let seen: std::collections::HashSet<String> = all.iter().map(|u| u.target()).collect();
        for u in self.ops {
            if !seen.contains(&u.target()) {
                all.push(u);
            }
        }
        self.j.save(&self.id, &all)
    }
}

fn safe_name(id: &str) -> String {
    id.chars().map(|c| if c.is_ascii_alphanumeric() || c == '.' || c == '-' || c == '_' { c } else { '_' }).collect()
}

impl Journal {
    pub fn open() -> Self {
        Journal { dir: crate::sys::data_dir().join("journal") }
    }

    pub fn at(dir: PathBuf) -> Self {
        Journal { dir }
    }

    fn path(&self, id: &str) -> PathBuf {
        self.dir.join(format!("{}.json", safe_name(id)))
    }

    pub fn begin(&self, id: &str, dry_run: bool) -> Txn<'_> {
        Txn { j: self, id: id.into(), ops: Vec::new(), dry_run }
    }

    pub fn has(&self, id: &str) -> Result<bool> {
        let path = self.path(id);
        path.try_exists().with_context(|| format!("check undo journal {}", path.display()))
    }

    pub fn load(&self, id: &str) -> Result<Vec<Undo>> {
        let path = self.path(id);
        match std::fs::read(&path) {
            Ok(bytes) => serde_json::from_slice(&bytes).with_context(|| format!("parse undo journal {}", path.display())),
            Err(e) if e.kind() == std::io::ErrorKind::NotFound => Ok(Vec::new()),
            Err(e) => Err(e).with_context(|| format!("read undo journal {}", path.display())),
        }
    }

    fn save(&self, id: &str, ops: &[Undo]) -> Result<()> {
        std::fs::create_dir_all(&self.dir)?;
        let tmp = self.path(id).with_extension("tmp");
        std::fs::write(&tmp, serde_json::to_vec_pretty(ops)?)?;
        std::fs::rename(&tmp, self.path(id))?;
        Ok(())
    }

    /// Replay the undo steps for an item, newest first, then forget them.
    pub fn undo(&self, id: &str, dry_run: bool) -> Result<Done> {
        let ops = self.load(id)?;
        if ops.is_empty() {
            return Ok(Done::note("nothing to undo"));
        }
        if dry_run {
            return Ok(Done::note(format!("{} steps to undo", ops.len())));
        }
        let mut errs = Vec::new();
        for u in ops.iter().rev() {
            if let Err(e) = u.run() {
                errs.push(e.to_string());
            }
        }
        if errs.is_empty() {
            let _ = std::fs::remove_file(self.path(id));
            Ok(Done::default())
        } else {
            Err(anyhow!("undo partly failed: {}", errs.join("; ")))
        }
    }

    /// Ids that have something recorded.
    pub fn ids(&self) -> Vec<String> {
        std::fs::read_dir(&self.dir)
            .map(|rd| {
                rd.filter_map(|e| e.ok())
                    .filter_map(|e| e.file_name().to_str().and_then(|n| n.strip_suffix(".json")).map(String::from))
                    .collect()
            })
            .unwrap_or_default()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::time::{SystemTime, UNIX_EPOCH};

    #[test]
    fn unreadable_journal_is_not_treated_as_absent() {
        let nonce = SystemTime::now().duration_since(UNIX_EPOCH).unwrap().as_nanos();
        let dir = std::env::temp_dir().join(format!("swo-journal-dir-{}-{nonce}", std::process::id()));
        let journal = Journal::at(dir.clone());
        std::fs::create_dir_all(&dir).unwrap();
        std::fs::create_dir(journal.path("sample")).unwrap();
        assert!(journal.has("sample").unwrap());
        assert!(journal.undo("sample", false).is_err());
        std::fs::remove_dir_all(dir).unwrap();
    }

    #[test]
    fn corrupt_journal_is_not_overwritten_by_a_new_commit() {
        let nonce = SystemTime::now().duration_since(UNIX_EPOCH).unwrap().as_nanos();
        let dir = std::env::temp_dir().join(format!("swo-journal-{}-{nonce}", std::process::id()));
        let journal = Journal::at(dir.clone());
        std::fs::create_dir_all(&dir).unwrap();
        assert!(!journal.has("sample").unwrap());
        let path = journal.path("sample");
        std::fs::write(&path, b"{").unwrap();
        assert!(journal.has("sample").unwrap());

        let mut tx = journal.begin("sample", false);
        tx.push(Undo::Reg { key: "HKCU\\Software\\Test".into(), name: "Value".into(), prev: None });
        assert!(tx.commit().is_err());
        assert_eq!(std::fs::read(&path).unwrap(), b"{");
        std::fs::remove_dir_all(dir).unwrap();
    }
}
