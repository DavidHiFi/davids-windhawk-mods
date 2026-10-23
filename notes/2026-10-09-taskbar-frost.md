# 2026-10-09 taskbar frost: TintOpacity 0.92 to 0.8, BlurAmount 80 to 110

User ask: make the taskbar a little more frosted glass / more blurry, "a tiny
bit", in `windows-11-taskbar-styler`. Done live, no restart.

## Change

One registry value, `HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings\styleConstants[18]`
(the `taskbarFill` constant used by `Taskbar.TaskbarBackground#BackgroundControl > Grid > Rectangle#BackgroundFill`):

- before: `taskbarFill = <WindhawkBlur BlurAmount="80" TintColor="#1E1E2E" TintOpacity="0.92" TintLuminosityOpacity="0.8" FallbackColor="#EB1E1E2E"/>`
- after:  `taskbarFill = <WindhawkBlur BlurAmount="110" TintColor="#1E1E2E" TintOpacity="0.8" TintLuminosityOpacity="0.8" FallbackColor="#CC1E1E2E"/>`

`TintOpacity` is the frost knob: at 0.92 the tint layer was nearly opaque, so
the blur behind barely showed. 0.8 lets the blurred wallpaper through while
`tintColor` and `TintLuminosityOpacity` stay unchanged, so the Catppuccin tint
and text contrast keep their character. `BlurAmount` 80 to 110 adds smear.
FallbackColor alpha EB (0.92) to CC (0.8) keeps the no-composition fallback
matched.

Applied via `scripts\2026-10-09-taskbar-frost.ps1 -Install`, hot-reload by
`SettingsChangeTime` bump (marker 1791486674). Verified by registry readback
and before/after screenshots:
`reports\2026-10-09-taskbar-frost\before-after.png` (also `before.png`,
`after.png`, `receipt.json`).

## Trap: elevation flap and the dead-between-steps child (measured)

1. `-Install` through `Invoke-Elevated.ps1` exited 1 with a ZERO-byte log, but
   the registry value HAD changed: the elevated 5.1 child imported the .reg,
   then died between the import and the `SettingsChangeTime` bump. A
   "successful" reg import with no bump leaves the mod on the old look until
   something else bumps.
2. Ninety seconds later the same wrapper failed on a trivial elevated `reg add`
   with no log at all, so the wrapper route itself flapped. The machine
   gotcha's manual route (one pre-quoted `-ArgumentList` string to `pwsh`,
   log to a file, read it back) worked on the first try.
3. After any elevated install that dies: read the value back, check the marker
   age, bump manually if stale, then run the script's `-Finish` mode (added
   this session) non-elevated for the evidence pass.

## Rollback

    pwsh -File "H:\Windhawk Configuration\scripts\2026-10-09-taskbar-frost.ps1" -Rollback

It imports `backups\2026-10-09\taskbar-frost\mod-key-full.reg` (full mod key,
pre-change) and bumps the marker. One-line manual rollback of just the value:
restore `styleConstants[18]` from that .reg.

## Pass 2, same morning: TintOpacity 0.8 to 0.75

User ask: a tiny bit more frost, mocha base exactly as is. One number:
`TintOpacity` 0.8 to 0.75, `TintColor` #1E1E2E (30,30,46), `BlurAmount` 110 and
`TintLuminosityOpacity` 0.8 all untouched, fallback alpha echoed CC to BF.
Script, receipt, backup and rollback:
`scripts\2026-10-09-taskbar-frost-pass2.ps1`,
`reports\2026-10-09-taskbar-frost-pass2\receipt.json`,
`backups\2026-10-09\taskbar-frost-2\` (full pass-1-state export +
`pass2.reg`). Evidence: `before-after-2.png`. Manual rollback to pass-1 state:

    pwsh -File "H:\Windhawk Configuration\scripts\2026-10-09-taskbar-frost-pass2.ps1" Rollback

Two traps hit and fixed in the pass-2 script (both measured, both now guarded):

1. First apply: the pass2.reg parent-key header used the `HKLM`
   abbreviation, which .reg files reject silently (the Settings section still
   imported, exit 0). So the value went live while the marker stayed at the
   pass-1 time and the mod never reloaded; the first "after" screenshot was
   wallpaper drift, not the change. Fixed: full `HKEY_LOCAL_MACHINE` root in
   every .reg section, marker baked into the same file, and Capture now
   refuses unless the live marker is at least the baked one.
2. A tray overflow flyout was open across one after shot; recaptured clean.

The safe pattern this session: value + marker in ONE .reg import, elevated
child runs only that import and writes its own result file, all capture and
verification non-elevated.

## Snapshot pushed to GitHub (commit eaebad6)

`davids-windhawk-mods\settings\mods-settings.json` was stale for this mod:
it still had the pre-frost taskbarFill and, since the 2026-10-07 tray-gap
work, sysTraySpacing = 6 and the rule-61 margin plus the 17
controlStyles[60..65] entries. Synced with
`scripts\2026-10-09-taskbar-frost-snapshot-sync.ps1 -Apply` (needle-verified
edits, JSON validation, post-apply diff: 429 = 429 keys, zero mismatches) and
pushed as `eaebad6` (verified with `git ls-remote origin main`). One trap
found while syncing: the block's last key line carries a PUA glyph and no
trailing comma, so the sync appends by prefix match and adds the comma
itself; a verbatim-copy insert produced invalid JSON on the first attempt
(caught by the script's own validation, restored from git, fixed).
