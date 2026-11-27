//! Registry access by full path ("HKLM\\SOFTWARE\\...") with exact undo.
//!
//! Always uses the 64-bit view. Values keep their exact type and bytes in the
//! journal, so a revert puts back precisely what was there (or deletes the value
//! when it did not exist).

use crate::journal::{Txn, Undo};
use anyhow::{anyhow, Context, Result};
use serde::{Deserialize, Serialize};
use winreg::enums::*;
use winreg::{RegKey, RegValue};

/// A value as stored, typed. Serialized into the journal.
#[derive(Serialize, Deserialize, Clone, Debug, PartialEq)]
#[serde(tag = "type", content = "data")]
pub enum RegVal {
    Dword(u32),
    Qword(u64),
    Sz(String),
    ExpandSz(String),
    MultiSz(Vec<String>),
    Binary(Vec<u8>),
    /// Any other type, raw.
    Raw(u32, Vec<u8>),
}

/// A value written in a tweak table. `Del` means "this value must not exist".
#[derive(Clone, Copy, Debug)]
pub enum V {
    D(u32),
    Q(u64),
    S(&'static str),
    X(&'static str),
    Del,
}

impl V {
    pub fn to_val(self) -> Option<RegVal> {
        match self {
            V::D(n) => Some(RegVal::Dword(n)),
            V::Q(n) => Some(RegVal::Qword(n)),
            V::S(s) => Some(RegVal::Sz(s.into())),
            V::X(s) => Some(RegVal::ExpandSz(s.into())),
            V::Del => None,
        }
    }
}

fn utf16z(s: &str) -> Vec<u8> {
    s.encode_utf16().chain(std::iter::once(0)).flat_map(|c| c.to_le_bytes()).collect()
}

fn from_utf16(b: &[u8]) -> String {
    let w: Vec<u16> = b.chunks_exact(2).map(|c| u16::from_le_bytes([c[0], c[1]])).collect();
    let end = w.iter().position(|&c| c == 0).unwrap_or(w.len());
    String::from_utf16_lossy(&w[..end])
}

impl RegVal {
    fn to_raw(&self) -> RegValue {
        match self {
            RegVal::Dword(n) => RegValue { bytes: n.to_le_bytes().to_vec(), vtype: REG_DWORD },
            RegVal::Qword(n) => RegValue { bytes: n.to_le_bytes().to_vec(), vtype: REG_QWORD },
            RegVal::Sz(s) => RegValue { bytes: utf16z(s), vtype: REG_SZ },
            RegVal::ExpandSz(s) => RegValue { bytes: utf16z(s), vtype: REG_EXPAND_SZ },
            RegVal::MultiSz(v) => {
                let mut b = Vec::new();
                for s in v {
                    b.extend(utf16z(s));
                }
                if b.is_empty() {
                    b.extend([0u8; 4]);
                } else {
                    b.extend([0u8, 0u8]);
                }
                RegValue { bytes: b, vtype: REG_MULTI_SZ }
            }
            RegVal::Binary(b) => RegValue { bytes: b.clone(), vtype: REG_BINARY },
            RegVal::Raw(t, b) => RegValue { bytes: b.clone(), vtype: raw_type(*t) },
        }
    }

    fn from_raw(r: &RegValue) -> RegVal {
        match r.vtype {
            REG_DWORD if r.bytes.len() >= 4 => RegVal::Dword(u32::from_le_bytes(r.bytes[..4].try_into().unwrap())),
            REG_QWORD if r.bytes.len() >= 8 => RegVal::Qword(u64::from_le_bytes(r.bytes[..8].try_into().unwrap())),
            REG_SZ => RegVal::Sz(from_utf16(&r.bytes)),
            REG_EXPAND_SZ => RegVal::ExpandSz(from_utf16(&r.bytes)),
            REG_MULTI_SZ => {
                let w: Vec<u16> = r.bytes.chunks_exact(2).map(|c| u16::from_le_bytes([c[0], c[1]])).collect();
                let v = w.split(|&c| c == 0).filter(|s| !s.is_empty()).map(String::from_utf16_lossy).collect();
                RegVal::MultiSz(v)
            }
            REG_BINARY => RegVal::Binary(r.bytes.clone()),
            ref t => RegVal::Raw(t.clone() as u32, r.bytes.clone()),
        }
    }

    pub fn as_u32(&self) -> Option<u32> {
        match self {
            RegVal::Dword(n) => Some(*n),
            RegVal::Qword(n) => Some(*n as u32),
            _ => None,
        }
    }

    pub fn as_str(&self) -> Option<&str> {
        match self {
            RegVal::Sz(s) | RegVal::ExpandSz(s) => Some(s),
            _ => None,
        }
    }
}

fn raw_type(t: u32) -> RegType {
    match t {
        0 => REG_NONE,
        1 => REG_SZ,
        2 => REG_EXPAND_SZ,
        3 => REG_BINARY,
        4 => REG_DWORD,
        5 => REG_DWORD_BIG_ENDIAN,
        6 => REG_LINK,
        7 => REG_MULTI_SZ,
        8 => REG_RESOURCE_LIST,
        9 => REG_FULL_RESOURCE_DESCRIPTOR,
        10 => REG_RESOURCE_REQUIREMENTS_LIST,
        11 => REG_QWORD,
        _ => REG_BINARY,
    }
}

/// Split "HKLM\\Software\\X" into a root key and the rest.
pub fn split(full: &str) -> Result<(RegKey, String)> {
    let full = full.trim_start_matches('\\');
    let (root, rest) = full.split_once('\\').unwrap_or((full, ""));
    let h = match root.to_ascii_uppercase().as_str() {
        "HKLM" | "HKEY_LOCAL_MACHINE" => HKEY_LOCAL_MACHINE,
        "HKCU" | "HKEY_CURRENT_USER" => HKEY_CURRENT_USER,
        "HKCR" | "HKEY_CLASSES_ROOT" => HKEY_CLASSES_ROOT,
        "HKU" | "HKEY_USERS" => HKEY_USERS,
        "HKCC" | "HKEY_CURRENT_CONFIG" => HKEY_CURRENT_CONFIG,
        _ => return Err(anyhow!("unknown registry root in {full}")),
    };
    Ok((RegKey::predef(h), rest.to_string()))
}

fn open(full: &str, write: bool) -> Result<RegKey> {
    let (root, sub) = split(full)?;
    let flags = if write { KEY_READ | KEY_WRITE } else { KEY_READ } | KEY_WOW64_64KEY;
    root.open_subkey_with_flags(&sub, flags).with_context(|| format!("open {full}"))
}

pub fn key_exists(full: &str) -> bool {
    open(full, false).is_ok()
}

pub fn get(full: &str, name: &str) -> Option<RegVal> {
    let k = open(full, false).ok()?;
    k.get_raw_value(name).ok().map(|r| RegVal::from_raw(&r))
}

pub fn get_u32(full: &str, name: &str) -> Option<u32> {
    get(full, name).and_then(|v| v.as_u32())
}

pub fn get_str(full: &str, name: &str) -> Option<String> {
    get(full, name).and_then(|v| v.as_str().map(String::from))
}

/// Subkey names of a key (empty when it does not exist).
pub fn subkeys(full: &str) -> Vec<String> {
    open(full, false).map(|k| k.enum_keys().filter_map(|r| r.ok()).collect()).unwrap_or_default()
}

/// Value names of a key (empty when it does not exist).
pub fn values(full: &str) -> Vec<String> {
    open(full, false).map(|k| k.enum_values().filter_map(|r| r.ok().map(|(n, _)| n)).collect()).unwrap_or_default()
}

/// Write without journaling. Creates the key path when needed.
pub fn set_raw(full: &str, name: &str, v: &RegVal) -> Result<()> {
    let (root, sub) = split(full)?;
    let (k, _) = root
        .create_subkey_with_flags(&sub, KEY_READ | KEY_WRITE | KEY_WOW64_64KEY)
        .with_context(|| format!("create {full}"))?;
    k.set_raw_value(name, &v.to_raw()).with_context(|| format!("write {full}\\{name}"))
}

/// Delete a value without journaling. Missing is fine.
pub fn del_raw(full: &str, name: &str) -> Result<()> {
    match open(full, true) {
        Ok(k) => match k.delete_value(name) {
            Ok(()) => Ok(()),
            Err(e) if e.kind() == std::io::ErrorKind::NotFound => Ok(()),
            Err(e) => Err(anyhow!("delete {full}\\{name}: {e}")),
        },
        Err(_) => Ok(()),
    }
}

/// Delete a whole key tree without journaling. Missing is fine.
pub fn del_tree_raw(full: &str) -> Result<()> {
    let (root, sub) = split(full)?;
    match root.delete_subkey_all(&sub) {
        Ok(()) => Ok(()),
        Err(e) if e.kind() == std::io::ErrorKind::NotFound => Ok(()),
        Err(e) => Err(anyhow!("delete key {full}: {e}")),
    }
}

/// Record the old value, then write the new one.
pub fn set(tx: &mut Txn, full: &str, name: &str, v: &RegVal) -> Result<()> {
    if get(full, name).as_ref() == Some(v) {
        return Ok(());
    }
    if !key_exists(full) {
        tx.push(Undo::RegKeyCreated { key: full.into() });
    }
    tx.push(Undo::Reg { key: full.into(), name: name.into(), prev: get(full, name) });
    if tx.dry_run {
        return Ok(());
    }
    set_raw(full, name, v)
}

/// Record the old value, then delete it.
pub fn del(tx: &mut Txn, full: &str, name: &str) -> Result<()> {
    let prev = get(full, name);
    if prev.is_none() {
        return Ok(());
    }
    tx.push(Undo::Reg { key: full.into(), name: name.into(), prev });
    if tx.dry_run {
        return Ok(());
    }
    del_raw(full, name)
}

/// Apply a table of (key, name, value). The usual body of a registry tweak.
pub fn apply_table(tx: &mut Txn, rows: &[(&str, &str, V)]) -> Result<()> {
    for (k, n, v) in rows {
        match v.to_val() {
            Some(val) => set(tx, k, n, &val)?,
            None => del(tx, k, n)?,
        }
    }
    Ok(())
}

/// True when every row of a table already holds its value. The usual scan of a registry tweak.
pub fn table_matches(rows: &[(&str, &str, V)]) -> bool {
    rows.iter().all(|(k, n, v)| match v.to_val() {
        Some(val) => match (get(k, n), &val) {
            (Some(RegVal::Dword(a)), RegVal::Dword(b)) => a == *b,
            (Some(a), b) => &a == b,
            (None, _) => false,
        },
        None => get(k, n).is_none(),
    })
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn empty_multi_sz_keeps_its_double_terminator() {
        let raw = RegVal::MultiSz(Vec::new()).to_raw();
        assert_eq!(raw.bytes, [0, 0, 0, 0]);
        assert_eq!(RegVal::from_raw(&raw), RegVal::MultiSz(Vec::new()));
    }
}
