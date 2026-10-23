# Black Delete Folder dialog: root cause and options (2026-10-17)

Thread: 4fd80e25-2ee1-4b2c-aae8-c1e3ad8706e1

## Result

The black body of the Explorer "Delete Folder" confirmation dialog is painted by `local@translucent-windows` 1.8.3, which is loaded into `explorer.exe`. The mod's in-process `GetSysColor` and `GetSysColorBrush` hooks return black for `COLOR_WINDOW`, `COLOR_BTNFACE` and `COLOR_MENU`, and black is the mod's transparency key. The dialog is not covered by the mod's acrylic backdrop, so the key shows as solid black.

The registry value `HKCU\Control Panel\Colors` is not the driver for this dialog. Measured.

## Measurements

| Test | Pure-black % of dialog | Mean RGB |
|---|---|---|
| Baseline, registry Colors black | 66.2 | 17,17,20 |
| Live Window, ButtonFace, Menu set to 30 30 46 (SetSysColors verified in another process as 0x002E1E1E) | 66.2 | 17,18,20 |
| translucent-windows `Disabled=1` (module unloaded from explorer.exe), registry still black | 0 | 44,47,65 |
| translucent-windows re-enabled | restored (Disabled=0, module loaded) | |

Captures: `C:\Users\localuser\AppData\Local\Temp\wh-black-probe\shots\` (`delete-dialog-before.png`, `delete-dialog-dark-live.png`, `delete-dialog-no-translucent.png`).

## Why the registry is not the cause

The `Custom.theme` file at `C:\Users\localuser\AppData\Local\Microsoft\Windows\Themes\Custom.theme` (saved 11:17 PM, 10/17) has a `[Control Panel\Colors]` section that matches the live registry values exactly. Windows wrote those values when that theme was applied. They are the user's theme choice and are not from a Windhawk mod. The `[Control Panel\Colors]` backup is `H:\Windhawk Configuration\backup-2026-10-17-colors\HKCU-Control-Panel-Colors.reg`, and the theme copy is in the same folder.

Those black values still affect processes without the hook. They are not what makes this dialog black.

## Why translucent-windows is the mechanism

- `RenderingMod.SysColors` is 0, so the mod hooks `GetSysColor` and `GetSysColorBrush` in every process it loads into.
- `GetCustomSysColor` returns `RGB(0,0,0)` for `COLOR_WINDOW`, `COLOR_BTNFACE`, `COLOR_MENU`, `COLOR_SCROLLBAR`, `COLOR_BACKGROUND`, `COLOR_INFOBK` and `COLOR_MENUBAR`.
- The mod's `FillRect` hook maps black fills to transparency, so black is the key for the translucent effect.
- The explorer.exe rule (`RuledPrograms[6]`) has `RenderingMod.ThemeBackground=1` with `acrylicblur`. Explorer windows get the blur. The `#32770` dialog does not get it, so the key shows as black.

## Constraint that makes this a real choice

Setting `RenderingMod.SysColors=1` or setting the explorer rule to `ThemeBackground=0` does not clear the black. The `GetSysColor` hook is installed whenever `SysColors=0`, and `ThemeBackground` only changes the per-process path. Making the dialog use real colors without changing the mod's source requires turning on the global Syscolors path, which writes black into the live system table for every app.

## Options

1. **Patch translucent-windows so `#32770` dialogs get the Explorer backdrop, or real system colors for their body (recommended).** Explorer windows keep their blur. Other translucent windows are untouched. Cost: a source change to a fork the guard manages, a compile, a guard hash update, and a translucency check across Explorer, Discord, and flyouts. I have not built this yet.
2. **Exclude explorer.exe from translucent-windows.** The dialog gets real colors, which are black in this theme. Set the Window, ButtonFace and Menu values to a dark non-black value at the same time, or the dialog stays dark. Cost: Explorer loses its acrylic blur. Settings-only, reversible.
3. **Leave it.** The dialog stays solid black. No change.

## Not done

- Full-screen sweep for other pure-black windows (menus, tooltips, Properties). The same key mechanism applies to Explorer-hosted windows in general, so expect more `#32770`-style cases. Not measured.
- No fix applied. Nothing in mod settings or sources changed.
- The Explorer window the probe navigated was already closed when the probe resumed. Remaining probe windows were navigated to This PC. The probe folder `wh-del-probe` was deleted after its contents were checked (`wh-probe-folder\probe.txt` only).

## Incident during the test

The translucent-windows re-enable run hit a log collision with another thread's elevated run (translucent-flyouts 0.6.34-diag install, `backups\2026-10-17-elevated\log-233744.txt`). The first re-enable did not run, and the mod stayed disabled until a second inline elevated write re-enabled it. Verified `Disabled=0` and loaded. Future elevated calls from parallel threads should use one-off command strings, or check the log for the expected output.
