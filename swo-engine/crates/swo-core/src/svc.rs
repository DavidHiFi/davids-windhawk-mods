//! Windows services: read and change the start type, with undo.

use crate::journal::{Txn, Undo};
use crate::reg;
use anyhow::{anyhow, Result};
use windows_sys::Win32::System::Services::*;

pub const AUTO: u32 = 2;
pub const MANUAL: u32 = 3;
pub const DISABLED: u32 = 4;

fn key(name: &str) -> String {
    format!("HKLM\\SYSTEM\\CurrentControlSet\\Services\\{name}")
}

pub fn exists(name: &str) -> bool {
    reg::key_exists(&key(name))
}

/// 0 boot, 1 system, 2 auto, 3 manual, 4 disabled.
pub fn start_type(name: &str) -> Option<u32> {
    reg::get_u32(&key(name), "Start")
}

fn wide(s: &str) -> Vec<u16> {
    s.encode_utf16().chain(std::iter::once(0)).collect()
}

/// Change the start type through the service manager, falling back to the
/// registry for protected services that refuse it.
pub fn set_start_raw(name: &str, start: u32) -> Result<()> {
    unsafe {
        let scm = OpenSCManagerW(std::ptr::null(), std::ptr::null(), SC_MANAGER_CONNECT);
        if !scm.is_null() {
            let n = wide(name);
            let s = OpenServiceW(scm, n.as_ptr(), SERVICE_CHANGE_CONFIG);
            if !s.is_null() {
                let ok = ChangeServiceConfigW(
                    s,
                    SERVICE_NO_CHANGE,
                    start,
                    SERVICE_NO_CHANGE,
                    std::ptr::null(),
                    std::ptr::null(),
                    std::ptr::null_mut(),
                    std::ptr::null(),
                    std::ptr::null(),
                    std::ptr::null(),
                    std::ptr::null(),
                );
                CloseServiceHandle(s);
                CloseServiceHandle(scm);
                if ok != 0 {
                    return Ok(());
                }
            } else {
                CloseServiceHandle(scm);
            }
        }
    }
    if !exists(name) {
        return Err(anyhow!("service {name} not found"));
    }
    reg::set_raw(&key(name), "Start", &reg::RegVal::Dword(start))
}

/// Record the old start type, then change it.
pub fn set_start(tx: &mut Txn, name: &str, start: u32) -> Result<()> {
    let Some(prev) = start_type(name) else { return Ok(()) };
    if prev == start {
        return Ok(());
    }
    tx.push(Undo::Service { name: name.into(), start: prev });
    if tx.dry_run {
        return Ok(());
    }
    set_start_raw(name, start)
}

/// Ask a running service to stop. Errors are ignored: it may already be stopped.
pub fn stop(name: &str) {
    unsafe {
        let scm = OpenSCManagerW(std::ptr::null(), std::ptr::null(), SC_MANAGER_CONNECT);
        if scm.is_null() {
            return;
        }
        let n = wide(name);
        let s = OpenServiceW(scm, n.as_ptr(), SERVICE_STOP);
        if !s.is_null() {
            let mut st: SERVICE_STATUS = std::mem::zeroed();
            ControlService(s, SERVICE_CONTROL_STOP, &mut st);
            CloseServiceHandle(s);
        }
        CloseServiceHandle(scm);
    }
}

/// Start a service. Errors are ignored: it may already be running.
pub fn start(name: &str) {
    unsafe {
        let scm = OpenSCManagerW(std::ptr::null(), std::ptr::null(), SC_MANAGER_CONNECT);
        if scm.is_null() {
            return;
        }
        let n = wide(name);
        let s = OpenServiceW(scm, n.as_ptr(), SERVICE_START);
        if !s.is_null() {
            StartServiceW(s, 0, std::ptr::null());
            CloseServiceHandle(s);
        }
        CloseServiceHandle(scm);
    }
}
