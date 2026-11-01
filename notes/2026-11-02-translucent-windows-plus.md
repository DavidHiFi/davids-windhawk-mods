# Translucent Windows Plus 1.9.0 replaces the repo mod (2026-11-02)

Owner order: stop patching the repo `translucent-windows` under its own id (Windhawk kept offering "update" to stock 1.8.2, and accepting that on 10/31 wiped the fork). Fork it properly as a Plus mod.

## What changed
- New source `Windhawk\translucent-windows-plus\translucent-windows-plus.wh.cpp`: the 1.8.3 re-apply fork with only the metadata changed. Id `translucent-windows-plus`, name "Translucent Windows Plus", version 1.9.0, `@author DavidHiFi, Undisputed00x`, Ko-fi `@donateUrl`, homepage, and a "Based on Translucent Windows by Undisputed00x" readme line. Code is the same as stock 1.8.2 plus the Explorer re-apply.
- `scripts\2026-11-02-twp-migrate.ps1 -Action install` (elevated, under the windhawk-engine lock): turned the old mod off, copied its key with all 166 settings to `local@translucent-windows-plus`, pointed it at `local@translucent-windows-plus_1.9.0_1.dll`, then deleted the old key and the old ModsSource file.
- `Test-WindhawkFreezeGate.ps1`: removed the 10/25 ban on the Plus id. That ban was for the old fork's border-color change, which this fork doesn't include.
- `AGENTS.md`: Translucent Windows line updated, fork recipe written down.
- The old `notes\2026-11-02-tw-false-update.md` DisableUpdateCheck workaround went away with the old key.

## Evidence (measured 2026-11-02, about 5:11 am)
- Migration log: INSTALL OK, Version 1.9.0, Disabled 0, 166 settings, include/exclude unchanged.
- Only `local@translucent-windows-plus` is in `HKLM\SOFTWARE\Windhawk\Engine\Mods`; `translucent-windows` is gone.
- Plus DLL loaded in Discord and in 34 of 35 explorer.exe processes. One process (pid 12636) still maps the stale `translucent-windows_1.8.2_414194.dll` from 10/31 until it exits.
- Freeze gate: no line for the Plus mod. It still fails on `windows-animations` (Include `*`), which was already the case and isn't part of this change.
- Not checked yet: what the Windhawk UI shows (no update banner, Plus card). I didn't automate the UI.

## Rollback
`scripts\2026-11-02-twp-migrate.ps1 -Action rollback`, elevated. Backups are in `backups\2026-11-02\translucent-windows-plus\` (old key and source).
