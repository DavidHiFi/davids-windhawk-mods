//! Shared base for the Seamless Windows Optimizer engine (`swo.exe`).
//!
//! Every part of the engine is a [`Provider`]: it lists its items, reports their
//! current state, and applies or reverts them. All output goes to stdout as one
//! JSON object per line through [`Emitter`]; the Windhawk mod reads those lines.
//! Anything that changes the system records how to put it back in the [`journal`]
//! first, so every toggle can be undone exactly.

pub mod emit;
pub mod item;
pub mod journal;
pub mod proc;
pub mod reg;
pub mod restore;
pub mod svc;
pub mod sys;
pub mod task;

pub use emit::Emitter;
pub use item::{Done, Item, Kind, Risk, State};
pub use journal::{Journal, Txn, Undo};
pub use reg::{RegVal, V};

/// What every provider gets: the output line writer, the undo journal and run flags.
pub struct Ctx {
    pub emit: Emitter,
    pub journal: Journal,
    /// Report what would happen, change nothing.
    pub dry_run: bool,
    pub elevated: bool,
}

impl Ctx {
    pub fn new(dry_run: bool) -> Self {
        Ctx { emit: Emitter::stdout(), journal: Journal::open(), dry_run, elevated: sys::is_elevated() }
    }
}

pub trait Provider: Send + Sync {
    /// Short name for logs ("clean", "tweaks", "tools").
    fn name(&self) -> &'static str;

    /// The full list of items this provider offers. Must be fast (no disk scans).
    fn items(&self) -> Vec<Item>;

    /// Current state of the given items (all of this provider's when `ids` is empty).
    /// For clean items this is the space that would be freed.
    fn scan(&self, ctx: &Ctx, ids: &[String]) -> Vec<State>;

    /// Apply one item. Clean items delete; toggles change settings (journaled).
    fn apply(&self, ctx: &Ctx, id: &str) -> anyhow::Result<Done>;

    /// Undo one item. The default replays the journal entry for it.
    fn revert(&self, ctx: &Ctx, id: &str) -> anyhow::Result<Done> {
        ctx.journal.undo(id, ctx.dry_run)
    }

    /// Free-form tools (`swo tool <name> ...`). Return None when the name is not ours.
    fn run_tool(&self, _ctx: &Ctx, _name: &str, _args: &[String]) -> Option<anyhow::Result<()>> {
        None
    }
}
