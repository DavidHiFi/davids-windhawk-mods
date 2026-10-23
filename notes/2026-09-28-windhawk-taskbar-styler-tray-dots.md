# Tray overflow chevron replaced with three dots (Windhawk Taskbar Styler)

2026-09-28. Status: live, verified by screenshot. Owner asked for the RosePine
theme's three-dot tray icon in place of the up-arrow chevron.

## What changed

One `controlStyles` entry appended to the live settings of the Windhawk mod
`windows-11-taskbar-styler`
(registry `HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings`):

    controlStyles[59].target    = Windows.UI.Xaml.Controls.TextBlock#InnerTextBlock[Text=<U+E971>]
    controlStyles[59].styles[0] = Text=<U+E712>

U+E971 is ChevronUpMed (the tray overflow button glyph); U+E712 is "More"
(three horizontal dots). Both are Segoe Fluent Icons. This is the exact rule
the RosePine theme ships, and every other theme in the guide targets the same
U+E971 glyph for the tray chevron. Rules 0-58 untouched.

`SettingsChangeTime` was bumped to 1790554512 and the engine restarted
(`windhawk.exe -restart`). No explorer restart, no reboot.

## Files

| Item | Path |
| --- | --- |
| Script (`-Audit` / `-Install` / `-Rollback`, elevated) | `scripts\2026-09-28-windhawk-taskbar-styler-tray-dots.ps1` |
| Pre-change registry export | `backups\2026-09-28\windhawk-taskbar-styler-tray-dots\windhawk-taskbar-styler-before-20260928-081419.reg` |
| Receipt | `backups\2026-09-28\windhawk-taskbar-styler-tray-dots\install-receipt.json` |
| Log | `reports\2026-09-28\windhawk-taskbar-styler-tray-dots.log` |
| Screenshots | `reports\2026-09-28\tray-before-zoom.png`, `tray-after-zoom.png` |

## Verification

Screenshot before/after: the `^` at the left of the tray cluster is now `...`.
`-Audit` reports the rule at index 59.

## Rollback

    powershell.exe -NoProfile -ExecutionPolicy Bypass -File `
      'H:\System Configuration\scripts\2026-09-28-windhawk-taskbar-styler-tray-dots.ps1' -Rollback

(elevated; removes rule 59, shifts any later entries down, bumps
`SettingsChangeTime`, restarts the engine). Or import the `.reg` backup above
and restart the engine. Or delete `controlStyles[59].*` from the mod's
textual mode.

## Notes

- The first `-Install` run wrote the registry values but then failed on
  `Set-ItemProperty -PropertyType` (invalid parameter; only
  `New-ItemProperty` takes it), so the settings-time bump and engine restart
  did not happen then. Fixed; a re-run completed the job idempotently. The
  `.reg` backup was exported immediately before the write, so it is the true
  pre-change state.
- Elevation trap: `Start-Process -Verb RunAs -ArgumentList` with an argument
  array mangles arguments when a path contains a space (child exits
  -196608 and silently does nothing). Pass one pre-quoted argument string
  instead.
- The dots render at the same tray font size as the chevron; nothing else in
  the taskbar changed.
