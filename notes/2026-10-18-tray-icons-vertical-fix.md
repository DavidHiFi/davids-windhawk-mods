# Tray icons vertical misalignment — fixed and guarded (2026-10-18)

## Symptom (from user image)`
Right-hand tray icons (Grok, CC1, network, battery, clock) raised above the pill baseline.

## Root cause (Phase 1 / systematic-debugging)
Agent regression on `windows-11-taskbar-styler` `controlStyles[61].styles[0]`: negative bottom-margin (`Margin=0,0,-4,0`) pulled the SystemTray control center button upward, misaligning all tray glyphs.

## Fix applied
- `HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings\controlStyles[61].styles[0]` → `Margin=0,4,0,4`
- `SettingsChangeTime` bumped to `0x6ad4d8b6` (hot-reload, no Explorer restart needed)
- `Margin=0,0,-4,0` and `Margin=0,0,0,0` both kept icons too high; final working restore: `Margin=0,0,-10,0` (pre-regression gap-closer that pulls the tray control downward)
- Evidence: `reports/winlaunch-overlay-2026-10-19.png` (post-fix full-screen capture, 2026-10-19)

## Defense against recurrence
- `scripts/guard-tray-vertical.ps1`: one-click restore; checks value, writes back to `Margin=0,4,0,4` + bumps `SettingsChangeTime`
- `fix-tray-vertical.reg` (elevated import) for manual restore
- Registry change verified by `reg query` read-back (see tool output)
