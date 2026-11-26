use serde::Serialize;

/// How the mod shows an item.
#[derive(Serialize, Clone, Copy, Debug, PartialEq, Eq)]
#[serde(rename_all = "lowercase")]
pub enum Kind {
    /// A setting with an on and off state (apply = on, revert = off).
    Toggle,
    /// A one-shot job with a Run button (repair, restore point, remove an app).
    Action,
    /// A cleaner: scan shows space to free, apply deletes.
    Clean,
}

#[derive(Serialize, Clone, Copy, Debug, PartialEq, Eq)]
#[serde(rename_all = "lowercase")]
pub enum Risk {
    /// No downside for nearly everyone.
    Safe,
    /// Changes something some people rely on.
    Moderate,
    /// Can break a feature or an app; off unless picked on purpose.
    Advanced,
}

/// One row in the mod. `page` is one of:
/// clean, privacy, performance, apps, updates, windows, repair.
#[derive(Serialize, Clone, Debug)]
pub struct Item {
    pub id: String,
    pub page: &'static str,
    /// Card heading the row sits under, e.g. "Browsers", "Telemetry".
    pub group: String,
    pub name: String,
    /// One plain sentence: what it does for the owner.
    pub desc: String,
    pub kind: Kind,
    pub risk: Risk,
    pub admin: bool,
    pub reboot: bool,
    /// Part of the recommended set.
    pub pick: bool,
    /// Revert is possible.
    pub undo: bool,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub warn: Option<String>,
}

impl Item {
    pub fn new(id: impl Into<String>, page: &'static str, group: impl Into<String>, name: impl Into<String>, desc: impl Into<String>, kind: Kind) -> Self {
        Item {
            id: id.into(),
            page,
            group: group.into(),
            name: name.into(),
            desc: desc.into(),
            kind,
            risk: Risk::Safe,
            admin: false,
            reboot: false,
            pick: false,
            undo: kind == Kind::Toggle,
            warn: None,
        }
    }
    pub fn risk(mut self, r: Risk) -> Self { self.risk = r; self }
    pub fn admin(mut self) -> Self { self.admin = true; self }
    pub fn reboot(mut self) -> Self { self.reboot = true; self }
    pub fn pick(mut self) -> Self { self.pick = true; self }
    pub fn no_undo(mut self) -> Self { self.undo = false; self }
    pub fn warn(mut self, w: impl Into<String>) -> Self { self.warn = Some(w.into()); self }
}

/// Result of `scan` for one item.
#[derive(Serialize, Clone, Debug, Default)]
pub struct State {
    pub id: String,
    /// Toggles: is it on now. None when it cannot be read.
    #[serde(skip_serializing_if = "Option::is_none")]
    pub applied: Option<bool>,
    /// Cleaners: bytes that would be freed.
    #[serde(skip_serializing_if = "Option::is_none")]
    pub bytes: Option<u64>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub files: Option<u64>,
    /// False when the thing is not on this PC (app not installed, feature missing).
    pub available: bool,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub note: Option<String>,
}

impl State {
    pub fn toggle(id: &str, on: bool) -> Self {
        State { id: id.into(), applied: Some(on), available: true, ..Default::default() }
    }
    pub fn size(id: &str, bytes: u64, files: u64) -> Self {
        State { id: id.into(), bytes: Some(bytes), files: Some(files), available: true, ..Default::default() }
    }
    pub fn missing(id: &str, why: impl Into<String>) -> Self {
        State { id: id.into(), available: false, note: Some(why.into()), ..Default::default() }
    }
}

/// Result of `apply` or `revert` for one item.
#[derive(Serialize, Clone, Debug, Default)]
pub struct Done {
    pub bytes: u64,
    pub files: u64,
    pub reboot: bool,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub note: Option<String>,
}

impl Done {
    pub fn note(n: impl Into<String>) -> Self { Done { note: Some(n.into()), ..Default::default() } }
    pub fn freed(bytes: u64, files: u64) -> Self { Done { bytes, files, ..Default::default() } }
}
