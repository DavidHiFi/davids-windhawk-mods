# Windhawk workspace sort, 2026-10-04

Moved 219 Windhawk files and folders containing 4503 files
from System Configuration into this workspace. Sources, development checkouts,
registry backups, scripts, diagnostics, screenshots, themes and notes now belong here.
All moved files passed SHA-256 verification. Directory junctions and file hardlinks
preserve old paths; the final check verified every compatibility link.

Mixed system records remain in System Configuration. 51 reference copies
here preserve Windhawk context without moving unrelated system work. Their source
and destination paths appear in `reports/2026-10-04-workspace-sort/mixed-context.json`.
Existing destination files were preserved; colliding imports live under
`archive/system-configuration-2026-10-04` and appear in the receipt.

Both current-status files point future Windhawk work here. The Windhawk workspace
instructions and README describe the consolidated layout. Another thread held the
System Configuration instructions, so its coordination board received the requested
scope update rather than a competing edit.

No live mod, registry value, application, T3 conversation binding, or installation
was changed. Git checkouts retain their branches, edits and history. Old paths remain
valid through compatibility links.

The complete receipt is `reports/2026-10-04-workspace-sort/receipt.json`.
Documentation backups are in `backups/2026-10-04/workspace-sort-docs`.
To undo an individual move, use its receipt row: remove only its old compatibility
link, then move the destination back to the recorded source. For directory junctions,
remove the junction itself without recursive deletion. Do not delete its target.
Restore the saved documentation copies to undo the workspace handoff text.
