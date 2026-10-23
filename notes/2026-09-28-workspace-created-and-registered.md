# Windhawk Configuration workspace created and registered

2026-09-28. Status: done; both T3 apps recognize the workspace.

## What was created

`H:\Windhawk Configuration` as a standalone workspace for all Windhawk work,
split out of `H:\System Configuration`:

- `AGENTS.md` - scope, engine facts, safety rules, conventions
- `README.md`, `CURRENT-STATUS.md`, `.agent-coop.json`
- `docs\windhawk-reference.md` - engine layout, settings formats, selector syntax
- `docs\traps-and-tips.md` - the hard-won traps from this machine
- `scripts\`, `notes\`, `reports\`, `backups\`, `mods\`

## What moved

| From (`H:\System Configuration`) | To (this workspace) |
| --- | --- |
| `Windhawk\` (altsnap-fork, Opencode-fork, npp sources/DLLs, `Backups\`, helper scripts) | `Windhawk\` |
| `davids-windhawk-mods\` (git repo, branch `main`, clean) | `davids-windhawk-mods\` |

Directory junctions were left at both old paths so every historical absolute path
in notes, scripts, and receipts still resolves:

- `H:\System Configuration\Windhawk` -> `H:\Windhawk Configuration\Windhawk`
- `H:\System Configuration\davids-windhawk-mods` -> `H:\Windhawk Configuration\davids-windhawk-mods`

Git in System Configuration still sees its one tracked file
(`Windhawk/Backup-Windhawk.ps1`) through the junction; no repo state changed.

Windhawk records from before this date (notes, scripts, reports, backups) were
left in `H:\System Configuration` because existing rollback commands reference
them by absolute path. New Windhawk records go here.

## Registrations

- **T3 Code V2 Orchestration**: project `mcp:910c75a3-54ea-48b0-ae30-ccc5f13666f7`
  ("Windhawk Configuration", `H:\Windhawk Configuration`), created through the
  app's own project service at 2026-09-28T00:52:57Z.
- **T3 Code Nightly**: a native `project.created` event appended to
  `C:\Users\localuser\.t3\userdata\state.sqlite` (Nightly closed during the edit):
  - project_id `4dfe0b41-410a-4735-ab60-2a3d1da640c9`
  - event_id `fa01d646-632a-4e86-85fe-413f766647aa`, sequence 221035
  - projection row upserted as well; the projector cursors were at 221034, so
    Nightly's startup catch-up applies the same event (its `project.created`
    handler is an idempotent upsert - verified in the server source) and advances
    the cursors. The project is visible either way.
  - Pre-change backup (state.sqlite + wal + shm, byte-identical) and a receipt
    with undo SQL:
    `backups\2026-09-28\t3-nightly-project-registration\`.

## Undo

- V2: delete the project in the app (it owns the row).
- Nightly (app closed): run the two `undo_sql` statements from
  `backups\2026-09-28\t3-nightly-project-registration\registration-receipt.json`
  against `state.sqlite`.

## Notes

- The workspace is not a git repo yet. If worktrees or history are wanted,
  `git init` plus a first commit is the follow-up.
- The V2 project has no `repositoryIdentity` (no remote); System Configuration
  is the only project bound to a GitHub remote.
