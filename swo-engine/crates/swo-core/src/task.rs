//! Scheduled tasks: read and change the enabled state, with undo.
//! Uses schtasks (hidden). The XML <Enabled> flag is read because it is not translated.

use crate::journal::{Txn, Undo};
use crate::proc;
use anyhow::{anyhow, Result};

/// None when the task does not exist.
pub fn enabled(path: &str) -> Option<bool> {
    let o = proc::run("schtasks.exe", &["/Query", "/TN", path, "/XML"]).ok()?;
    if o.code != 0 {
        return None;
    }
    let x = proc::decode(&o.stdout);
    // The task-level flag lives in <Settings>; a missing tag means enabled.
    let settings = x.split("<Settings>").nth(1).unwrap_or("");
    let settings = settings.split("</Settings>").next().unwrap_or("");
    Some(!settings.contains("<Enabled>false</Enabled>"))
}

pub fn set_enabled_raw(path: &str, on: bool) -> Result<()> {
    let o = proc::run("schtasks.exe", &["/Change", "/TN", path, if on { "/Enable" } else { "/Disable" }])?;
    if o.code != 0 {
        return Err(anyhow!("schtasks {path}: {}", o.text().trim()));
    }
    Ok(())
}

/// Record the old state, then change it. Missing tasks are skipped.
pub fn set_enabled(tx: &mut Txn, path: &str, on: bool) -> Result<()> {
    let Some(prev) = enabled(path) else { return Ok(()) };
    if prev == on {
        return Ok(());
    }
    tx.push(Undo::Task { path: path.into(), enabled: prev });
    if tx.dry_run {
        return Ok(());
    }
    set_enabled_raw(path, on)
}
