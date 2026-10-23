# NanaZip drag-select trails (Windhawk)

Opened 2026-09-24. Fixed and verified 2026-09-25.

## Symptom
Left-dragging in NanaZip's file list left every frame of the selection rectangle on screen as white nested outlines.

## Cause
The `win32-ui-modernizer` 1.0.2 mod, setting `GeneralSection.ModernFocusRect = modern`.

- NanaZip's file list is a classic comctl32 `SysListView32`, not double-buffered. It draws the drag rectangle with `DrawFocusRect` and erases the previous frame by drawing the same rectangle again, which works only because `DrawFocusRect` uses XOR.
- The mod hooks `user32!DrawFocusRect` (`DrawFocusRect_hook`, `win32-ui-modernizer.wh.cpp` line 12594) and draws an opaque rounded GDI+ outline instead. The second "erase" call draws another outline, so nothing is ever removed.
- The mod's `SysListView32` bypass only runs when `ExplorerSection.RoundedSelection` is on, and it is off here. The 2026-09-24 note used that bypass to rule this mod out, which was wrong.
- No other installed mod hooks `DrawFocusRect`.

## Ruled out
`translucent-windows` acrylic on NanaZip. On 2026-09-24 its `RuledPrograms[21]` acrylic rule was turned off, and the trails stayed. That change was reverted with `scripts\2026-09-24-revert-nanazip-windhawk-trails.ps1` (log `reports\2026-09-24-nanazip-windhawk-revert.log`), so NanaZip has its acrylic again.

## Fix
`scripts\2026-09-25-fix-nanazip-marquee-modernizer.ps1` (elevated):

- Sets `HKLM\SOFTWARE\Windhawk\Engine\Mods\win32-ui-modernizer\ExcludeCustom` from empty to `NanaZip.Modern.FileManager.exe`. This is the same value Windhawk's "Custom process exclusion list" writes. Every other process keeps the mod and all of its settings.
- Bumps the mod's `SettingsChangeTime`, which makes Windhawk reload the config without a service restart.
- Changes `translucent-windows\SettingsChangeTime` back to `REG_DWORD`, the type Windhawk writes, because the 2026-09-24 revert script had written it as `REG_QWORD`.
- Log: `reports\2026-09-25-nanazip-marquee-fix.log`.

## Verification
`scripts\Test-NanaZipMarquee.py` makes NanaZip topmost. Before it sends any input, it uses `WindowFromPoint` to check that every test point lands on NanaZip's list, and it aborts otherwise. The first version had no such check: it captured and clicked a game window that was on top, so its result was discarded. The test drags through empty rows and compares the region before and after, and a run only counts when the marquee showed up mid-drag.

| Run | Modernizer DLL in NanaZip | Marquee seen | Pixels left after release |
|---|---|---|---|
| `02-baseline-modernizer-on` | yes | yes | 8368 (trails) |
| `03-modernizer-excluded` | no | yes, native dotted | 0 |
| `04-modernizer-excluded-repeat` | no | yes | 0 |

Evidence: `.tmp\nanazip-marquee\<run>\` (before, mid-drag, after, diff mask, `result.json`).

The fix costs NanaZip one thing: the modernizer's rounded focus outlines. The drag rectangle is back to the native dotted one.

## Rollback
Run `scripts\2026-09-25-fix-nanazip-marquee-modernizer.ps1 -Rollback` elevated. It re-imports `backups\2026-09-25-win32-ui-modernizer-windhawk.reg`. Any NanaZip window that is already open keeps its current state until it is reopened.

## Update 2026-09-28
The same trails returned in Registry Editor. Fixed system-wide instead of with
another exclusion: `GeneralSection.Enabled = 0` on the modernizer forces a
native `DrawFocusRect` in every process, so NanaZip's per-process exclusion is
now redundant (kept, harmless). Detail:
`notes\2026-09-28-windhawk-modernizer-focusrect-global.md`.
