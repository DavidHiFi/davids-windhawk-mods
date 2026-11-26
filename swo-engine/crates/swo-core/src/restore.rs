//! System restore point before a batch of changes.

use crate::reg;
use anyhow::{anyhow, Result};
use windows_sys::Win32::System::Restore::*;

const SR_KEY: &str = r"HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\SystemRestore";

/// Make a restore point. Windows normally allows one per 24 hours; the limit is
/// lifted for this call and put back after. Returns a plain note on success.
pub fn create(desc: &str) -> Result<String> {
    if reg::get_u32(SR_KEY, "RPSessionInterval").unwrap_or(1) == 0 {
        return Err(anyhow!("System Restore is off on this PC"));
    }
    let prev = reg::get(SR_KEY, "SystemRestorePointCreationFrequency");
    let _ = reg::set_raw(SR_KEY, "SystemRestorePointCreationFrequency", &reg::RegVal::Dword(0));

    let mut info: RESTOREPOINTINFOW = unsafe { std::mem::zeroed() };
    info.dwEventType = BEGIN_SYSTEM_CHANGE;
    info.dwRestorePtType = MODIFY_SETTINGS;
    info.llSequenceNumber = 0;
    for (i, c) in desc.encode_utf16().take(255).enumerate() {
        info.szDescription[i] = c;
    }
    let mut st: STATEMGRSTATUS = unsafe { std::mem::zeroed() };
    let ok = unsafe { SRSetRestorePointW(&info, &mut st) };
    // Both structs are packed: copy the fields out before using them.
    let (n_status, seq) = (st.nStatus, st.llSequenceNumber);

    if ok != 0 {
        let mut end: RESTOREPOINTINFOW = unsafe { std::mem::zeroed() };
        end.dwEventType = END_SYSTEM_CHANGE;
        end.llSequenceNumber = seq;
        let mut st2: STATEMGRSTATUS = unsafe { std::mem::zeroed() };
        unsafe { SRSetRestorePointW(&end, &mut st2) };
    }

    match prev {
        Some(v) => {
            let _ = reg::set_raw(SR_KEY, "SystemRestorePointCreationFrequency", &v);
        }
        None => {
            let _ = reg::del_raw(SR_KEY, "SystemRestorePointCreationFrequency");
        }
    }

    if ok == 0 {
        return Err(anyhow!("restore point failed (status {n_status})"));
    }
    Ok(format!("restore point {seq} made"))
}
