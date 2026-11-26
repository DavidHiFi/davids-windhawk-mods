//! JSON-lines output. Every line is one object with a `t` field:
//!
//! - `item`     one catalog entry (see [`Item`])
//! - `state`    scan result for one item (see [`State`])
//! - `progress` `{id, done, total, msg}` while a long job runs
//! - `result`   `{id, ok, bytes, files, reboot, note | error}` after apply or revert
//! - `row`      `{tool, ...}` free-form rows from `swo tool`
//! - `log`      `{msg}` human text for the mod's activity list
//! - `end`      `{ok, failed}` last line of every run

use crate::item::{Done, Item, State};
use serde::Serialize;
use serde_json::{json, Value};
use std::io::Write;
use std::sync::Mutex;

pub struct Emitter {
    out: Mutex<Box<dyn Write + Send>>,
}

impl Emitter {
    pub fn stdout() -> Self {
        Emitter { out: Mutex::new(Box::new(std::io::stdout())) }
    }

    /// For tests: collect lines anywhere.
    pub fn to(w: Box<dyn Write + Send>) -> Self {
        Emitter { out: Mutex::new(w) }
    }

    fn line(&self, t: &str, body: Value) {
        let mut v = body;
        if let Value::Object(ref mut m) = v {
            m.insert("t".into(), Value::String(t.into()));
        }
        let mut o = self.out.lock().unwrap_or_else(|e| e.into_inner());
        let _ = serde_json::to_writer(&mut *o, &v);
        let _ = o.write_all(b"\n");
        let _ = o.flush();
    }

    fn obj<T: Serialize>(x: &T) -> Value {
        serde_json::to_value(x).unwrap_or(Value::Null)
    }

    pub fn item(&self, i: &Item) { self.line("item", Self::obj(i)) }
    pub fn state(&self, s: &State) { self.line("state", Self::obj(s)) }

    pub fn progress(&self, id: &str, done: u64, total: u64, msg: &str) {
        self.line("progress", json!({"id": id, "done": done, "total": total, "msg": msg}))
    }

    pub fn ok(&self, id: &str, d: &Done) {
        let mut v = Self::obj(d);
        v["id"] = json!(id);
        v["ok"] = json!(true);
        self.line("result", v)
    }

    pub fn fail(&self, id: &str, err: &str) {
        self.line("result", json!({"id": id, "ok": false, "error": err}))
    }

    pub fn row(&self, tool: &str, mut fields: Value) {
        if let Value::Object(ref mut m) = fields {
            m.insert("tool".into(), json!(tool));
        }
        self.line("row", fields)
    }

    pub fn log(&self, msg: &str) { self.line("log", json!({"msg": msg})) }

    pub fn end(&self, ok: u64, failed: u64) { self.line("end", json!({"ok": ok, "failed": failed})) }
}
