# Regedit drag-select trails, fixed system-wide (Windhawk modernizer)

Opened and fixed 2026-09-28. Same bug as NanaZip on 2026-09-24, same mod.

## Symptom

Left-dragging to select in Registry Editor's values list left every frame of
the drag rectangle on screen as white rounded outlines (owner screenshot).
NanaZip showed identical trails before its fix.

## Cause

The `win32-ui-modernizer` 1.0.2 mod (crazyboyybs), setting
`GeneralSection.ModernFocusRect = modern`. Its `user32!DrawFocusRect` hook
draws an opaque rounded GDI+ outline instead of the native rectangle.

A classic SysListView32 draws its drag marquee with `DrawFocusRect` and
erases the previous frame by calling it again, a trick that works only
because `DrawFocusRect` is XOR. The opaque outline never erases, so each
mouse move leaves a frame behind. Regedit's values list is such a control,
and it carries `LVS_EX_DOUBLEBUFFER` yet still trails (checked in the
harness run).

## Why not the NanaZip fix

NanaZip got a per-process exclusion (`ExcludeCustom`). Excluding regedit
would have cost it the mod's RegeditSection features, including the
transparent background that gives the owner's regedit its dark look (visible
in their screenshot with the trails). The mod itself defines a global off
switch for this one feature.

## Change

- `HKLM\SOFTWARE\Windhawk\Engine\Mods\win32-ui-modernizer\Settings\GeneralSection.Enabled`:
  1 to 0. This forces `ModernFocusRect = -1` (native passthrough) in every
  process, per the mod source (Settings field comment line 878, hook check
  line 12598, gate at lines 30568 to 30569).
- `...\win32-ui-modernizer\SettingsChangeTime` bumped, which reloads the
  config live. No engine restart (engine restarts freeze T3 Code on this
  machine; see the Windhawk workspace coop board).
- Applied 2026-09-28 about 14:51 (+08) with a direct `reg add`, then
  re-applied and logged by the fix script at 14:52:40 (idempotent).
- Backup of the whole mod key including the Settings subkey:
  `backups\2026-09-28\win32-ui-modernizer-before-focusrect-off.reg`.
- Log: `reports\2026-09-28\windhawk-modernizer-focusrect-fix.log`.

Every other GeneralSection feature was already off in this configuration, so
the net visible change is exactly one thing: focus rectangles go from the
mod's rounded outline back to the native dotted one, everywhere. Regedit's
styling, the ExplorerSection and RegeditSection features, and every other mod
are untouched. The NanaZip exclusion stays (now redundant, harmless).

## Verification

`scripts\Test-RegeditMarquee.py` launches its own elevated regedit, clicks it
awake, drags through the empty lower half of the values list, and compares
that region before the drag with the same region after the button is
released. A run counts only when the marquee was visible mid-drag. Method
note: a freshly launched window eats the first click, and a click at the
drag start reads as a double-click, which suppresses the marquee. The harness
clicks a different spot first, then drags.

| Run | Modernizer DLL in regedit | Marquee seen | Pixels left after release |
|---|---|---|---|
| `01c-baseline-instrumented` | yes | yes | 36218 (trails) |
| `02-fixed-general-native` | yes | yes, native dotted | 0 |

Evidence: `.tmp\regedit-marquee\<run>\` (before, mid-drag, full mid-drag,
after, diff mask, `result.json`).

## Permanence

The setting lives in HKLM, so it survives reboots, Windhawk updates and mod
updates. It is process-independent: every process still loads the mod
(Include `*`), but the hook now passes through, so any app with a classic
marquee (regedit, NanaZip, 7-Zip style lists, old tools) is covered without
a per-app exclusion list to maintain.

## Rollback

`scripts\2026-09-28-windhawk-modernizer-focusrect-fix.ps1 -Rollback`
(elevated) re-imports the backup and bumps `SettingsChangeTime`. Direct
equivalent: `reg import` of the backup file above plus a SettingsChangeTime
write. Already-open windows pick the change up on their next repaint, new
processes at start. Rollback restores the trails in any app that marquees, so
only do it to get the rounded focus outline back.

## If it ever returns

1. `scripts\2026-09-28-windhawk-modernizer-focusrect-fix.ps1 -Audit` (elevated)
   must print `GeneralSection.Enabled='0x0'`. If not, run the script without
   switches to re-apply the fix and the change-time bump.
2. `rg -l DrawFocusRect C:\ProgramData\Windhawk\ModsSource` must list only
   `win32-ui-modernizer.wh.cpp`. If another mod appears, its DrawFocusRect
   hook needs the same review before trusting the setting alone.
3. For a fresh measurement, run `scripts\Test-RegeditMarquee.py` elevated and
   read `trails_detected` in `result.json`; it must be false, with
   `marquee_seen` true.

## Records

- Script: `scripts\2026-09-28-windhawk-modernizer-focusrect-fix.ps1`
  (`-Audit` and `-Rollback`).
- Harness: `scripts\Test-RegeditMarquee.py` (run elevated; writes PNGs and
  `result.json`).
- Also recorded in the Windhawk workspace: `H:\Windhawk Configuration\CURRENT-STATUS.md`
  ("Live Windhawk state" bullet, 2026-09-28) and a coop note on its board.
  The local `davids-windhawk-mods` snapshot copy is aligned to the new value
  (2026-09-28); the repo thread still has to publish it.
- Previous fix this replaces: `notes\2026-09-24-nanazip-windhawk-trails.md`.

One operational observation: an elevated run of the fix script stalled once
at 14:45 while the Windhawk workspace's other elevated script was active. It
completed cleanly on the next run at 14:52, and the registry state had been
applied with a direct `reg add` in between. Not reproduced.
