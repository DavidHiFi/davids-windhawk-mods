# Taskbar giant pill restyle

Date: 2026-09-25. Owner instruction: apply it autonomously, stop the long investigation, make the taskbar one long floating pill that sits just off the screen edges, no segmented boxes.

## Summary

- The taskbar is one continuous pill: 8 px inset left and right, 4 px top and bottom, radius 15 corners, 2 px outline, mocha blur fill. It spans 2544 px of the 2560 px screen. Round 2 (below) moved the radius from 19 to 15, the outline from 1 px to 2 px, and the app icons from a 50 px pitch to 40 px.
- The per-button and tray boxes are gone. `buttonFill` and `buttonBorderColor` are fully transparent, so icons and widgets sit on the one bar with nothing drawn around them.
- Everything lives in the `windows-11-taskbar-styler` Windhawk mod settings under HKLM. Three elevated writes landed at 10:17:33, 11:09:28 and 11:20:19. Explorer was never restarted; the mod picked up each write live through `SettingsChangeTime`.
- Rollback: import `backups\2026-09-25\windhawk-taskbar-styler-before-pill.reg`, then bump `SettingsChangeTime` or restart explorer.

## Why the first attempt showed an inset but no rounding

The first write put `Margin`, `CornerRadius`, `Stroke` and `StrokeThickness` on `Taskbar.TaskbarBackground > Grid > Rectangle#BackgroundFill`. The inset never showed and the corners stayed square.

Two separate causes:

1. `CornerRadius` is not a property of a XAML `Shapes.Rectangle`. Rounded corners on that element are `RadiusX` and `RadiusY`. The mod builds one XAML `<Style>` per target out of the whole rule set, so a single setter naming a property the element does not have makes the parse fail and drops every setter in that set, `Fill` included.
2. The background layer's own `Grid` does accept `Margin`, so the inset from the new `controlStyles[58]` rule landed while the Rectangle rules were dead. That produced a flat-edged band and made it look like only half the config applied.

Fixed at 11:20:19 by switching `CornerRadius=19` to `RadiusX=19` plus `RadiusY=19`, and by replacing the `{ThemeResource AdaptiveBorder}` stroke with a literal `#9945475A` brush so no theme lookup can fail the parse either.

## What changed

Backup: `backups\2026-09-25\windhawk-taskbar-styler-before-pill.reg` (91,808 bytes), taken before the first write.
Apply script: `scripts\Set-TaskbarGiantPill.ps1`, audit with `-Audit`.

| When | Change | Before | After | Rollback |
|---|---|---|---|---|
| 10:17:33 | `styleConstants[16]/[17]` button fill and border set to `#00000000` | translucent blur brush, visible per-button boxes | transparent, boxes gone | import backup reg |
| 10:17:33 | `styleConstants[18]` taskbar fill set to `WindhawkBlur` 80 / tint `#1E1E2E` 0.92 / fallback `#EB1E1E2E` | 100 blur, tint opacity 0.2, wallpaper showed through | solid mocha bar | import backup reg |
| 10:17:33 | `controlStyles[1]` rules on `Rectangle#BackgroundFill`; `controlStyles[2]` collapses the old top hairline `Rectangle#BackgroundStroke` | full-width hairline stroke | hairline hidden | import backup reg |
| 11:09:28 | Added `controlStyles[58]`, `Taskbar.TaskbarBackground#BackgroundControl > Grid` with `Margin=6,3,6,3`; Rectangle margin reduced to `2,1,2,1` | no inset, square corners | 6 px side / 3 px top-bottom inset, still square | import backup reg |
| 11:20:19 | `controlStyles[1]`: `CornerRadius=19` replaced by `RadiusX=19` and `RadiusY=19`; stroke brush set to literal `#9945475A` | style set dropped by the invalid `CornerRadius` setter | fill, margin, stroke and rounding all apply | import backup reg |

## Evidence

PrintWindow capture of `Shell_TrayWnd` (`reports\tb-pw-after.png`, 2560x48), read pixel by pixel:

- Band spans x 8..2551 and rows 4..43, so the inset is 8 px on each side and 4 px top and bottom.
- Top rows start at x 22, 19, 17, 13 and 8 for rows 4, 5, 6, 10 and 20. Left columns span rows 18..29 at x=8 and rows 11..36 at x=12. That is the radius 19 arc.
- Interior pixels are `(28,28,42)`, the mocha tint over a black backdrop. Top and bottom edge rows are `(47,49,62)`, the 1 px stroke.
- Column 1280 shows rows 4..43 filled and rows 0..3 and 44..47 clear.

Live captures for comparison: `reports\tb-live5-bottom.png` (inset present, corners square, before the 11:20:19 write) and `reports\tb-live3-strip.png` (original band, no inset).

## Notes for the next session

- A fullscreen game (Plutonium T6, Bus Depot) covered the screen during the final check, so the last verification used PrintWindow of the taskbar window instead of a screen capture. PrintWindow renders the taskbar's own XAML but not the blur backdrop, which is why the interior reads as a flat `(28,28,42)`. Take one screen capture after the game exits to see the blurred result.
- `Get-ItemProperty -Name 'controlStyles[1]...'` returns nothing because the brackets are wildcards. Use `(Get-Item -LiteralPath $key).GetValue('controlStyles[1].styles[3]')`.
- The apply wrapper that elevation runs is `C:\Users\localuser\AppData\Local\Temp\opencode\pill-apply-wrapper.ps1`; it logs to `pill-apply-2.log` in the same folder.
- Pixel tools used for the checks are in the same temp folder: `dump2.exe` (row/column dump), `edge.exe` (band bounds per row/column), `zoom.exe` (crop and magnify), `pw.exe` (PrintWindow capture).

## Round 2, 11:39:25

Owner asked for three adjustments after seeing the first result: a slightly thicker border, slightly less rounded corners, and app icons closer together.

| Value | Before | After |
|---|---|---|
| `controlStyles[1].styles[3]` / `[6]` | `RadiusX=19`, `RadiusY=19` | `RadiusX=15`, `RadiusY=15` |
| `controlStyles[1].styles[5]` | `StrokeThickness=1` | `StrokeThickness=2` |
| `controlStyles[16].styles[0]` | `MinWidth := {{max(40,(2*ImageIconWidth+2))}}` | `MinWidth := {{max(34,(ImageIconWidth+14))}}` |

The icon spacing came from that MinWidth formula. It reserved two icon widths (2 x 26 + 2 = 54, and the buttons measured out at a 50 px pitch), so the gap between 26 px icons was about 26 px. One icon width plus 14 px gives a 40 px pitch and a 14 px gap. The new figure agrees with the 38 px `TaskbarButtonWidth` the `taskbar-icon-size` mod asks for, so the two settings no longer fight.

Measured after the write, on `reports\tb-pw-round2.png` and confirmed on the live screen (`reports\tb-live7-bottom.png`):

- Stroke: rows 4 and 5 on the top edge, 44 and 45 on the bottom, so 2 px.
- Corners: the straight part of the left edge now runs rows 20 to 29 at x=8. With radius 19 that straight part was only two rows, so the arc is shorter and the corners read as less round while the ends still close like a pill.
- Icons: pitch 40 px (was 50), gap 14 px (was 26). Icon starts measured at 932, 972, 1012, 1052 and so on, identical in the PrintWindow capture and the screen capture.

The taskbar window also grew from 48 px to 50 px tall between rounds (`taskbar-icon-size` has `TaskbarHeight = 50`). That mod was open in the Windhawk UI at the time, so it re-applied itself. The pill inset is unchanged at 4 px top and bottom because it comes from margins, not from the height.

## Round 3, 12:00 (SettingsChangeTime 1790308774)

Owner sent a screenshot showing the hover/active highlight box sitting off-centre behind an app icon. The box (Border#BackgroundElement) and the icon were each anchored to the left of the button: box margins were left 4 / right 6, and the icon was left-aligned plus a fixed 10 px translate, so the box centre landed at 19 and the icon centre at 23 in a 40 px slot.

Six values changed (audit showed 6 real deltas, the rest idempotent):

| Value | Before | After |
|---|---|---|
| `controlStyles[4].styles[2]` | `Margin := {{$highlightOffset}},... ,{{$highlightOffset+2}},...` | right term `$highlightOffset+2` -> `$highlightOffset` (symmetric 4/4) |
| `controlStyles[4].styles[3]` | `Margin@NoRunningIndicator := 0,...,2,...` | right term `2` -> `0` |
| `controlStyles[15].styles[2]` | `HorizontalAlignment = 0` (left) | `HorizontalAlignment = 1` (centre) |
| `controlStyles[15].styles[4]` | `RenderTransformOrigin = 1,0.5` | `RenderTransformOrigin = 0.5,0.5` |
| `controlStyles[15].styles[5]` | `TranslateTransform X="{{max((ImageIconWidth/2-3),10)}}"` | `TranslateTransform X="0"` |
| `controlStyles[15].styles[6]` | same translate inside the `InactivePointerOver` group | `X="0"`, scale 0.9 kept, now pivots on the icon centre |

Applied elevated through `pill-apply-wrapper.ps1` at SettingsChangeTime 1790308774; the script verified all 21 values against the registry.

### How the alignment was proven

Live hover tests are impossible while the fullscreen game owns the screen: synthetic cursor moves get warped (the cursor was pulled back to the screen centre), and screen captures return game pixels. PrintWindow still renders the taskbar XAML, so the box geometry was measured with a temporary forced-visibility probe instead (`temp-box.ps1` in the temp folder, run elevated):

1. Probe wrote `controlStyles[4].styles[21]` = unqualified `Background := #40FFFFFF`, `styles[22]` = same for `@NoRunningIndicator`, and shifted the pill (`controlStyles[58]` margin 60) as a reload marker.
2. PrintWindow capture `reports\tb-pw-probe2.png`: boxes visible on all 16 buttons, pill shifted - the mod definitely reloaded.
3. Measured per button: box 32 px wide (inset 4/4 inside the 40 px slot, symmetric), rows 6..43 (centred vertically), and icon centre vs box centre delta = -1 px on every one of the 16 buttons. Before the fix the delta was -4 px. The residual 1 px is icon artwork padding inside its 26 px layout box, not layout. (Round 4 correction: it is layout. See below.)
4. Probe reverted (`-Revert` deletes styles[21]/[22] and restores the pill margin), SettingsChangeTime 1790311138. A full `-Audit` afterwards: 21 pairs, 0 differences - registry is byte-identical to the script again.

Evidence: `reports\tb-pw-round3.png` (icons centred), `reports\tb-pw-probe2.png` (boxes visible for measuring), `reports\tb-pw-round3-final.png` (after revert: fill rows 6..43, probe colour gone, 17 icons at 40 px pitch: 946, 986, 1026, ...).

Hover caveat: with the probe removed the box is only visible in the states Windows drives itself (hover/active). Synthetic hover (SetCursorPos and SendInput, absolute virtual-desktop coordinates) produced no visual state change in every test, so hover alignment is verified by construction (symmetric margins + centred icon, both centred on the same slot) rather than by a hover screenshot. Next real-mouse hover can be eyeballed against the -1 px measurement.

## Tool notes added in round 3

- `dump2 <img> row <y> <x0> <x1>` and `icons <img> <y0> <y1> <x0> <x1>` take ranges; both crash with IndexOutOfRange if the ranges are missing.
- `zoom <src> <out> <x> <y> <w> <h> <scale>` (nearest-neighbour upscale with a red border).
- Elevation: `Start-Process -Verb RunAs` cannot combine with `-RedirectStandardOutput`, and child environment variables did NOT survive the UAC elevation for the revert wrapper - the revert must be its own script, not an env-var switch (see `box-revert-wrapper.ps1`).
- The display layout is dual-monitor with the virtual screen at left=0, top=-1080, w=4480, h=2520; absolute SendInput must normalise against those metrics, and relative moves fight the fullscreen game.
- Do not append markdown through a PowerShell double-quoted here-string (`@"..."@`). Backtick sequences become escape codes (`` `r ``, `` `0 ``, `` `b ``, `` `t ``) and `$names` get interpolated, which is how this section was first written with NUL, CR, backspace and tab bytes in it. Use a single-quoted here-string (`@'...'@`).

## Round 4, 14:55 (SettingsChangeTime 1790320966)

Owner sent a crop of the Discord button: the hover box still sat slightly right of the icon and looked cramped. Measured on that crop: box x 20..47 (28 px, centre 33.5), icon x 21..44 (centre 32.5), so the box was 1 px right of the icon and only 2 px wider than it on each side.

Round 3 blamed that 1 px on icon artwork padding, and that was wrong. The box centres on the 40 px button (`MinWidth` in `controlStyles[16]`), but the icon centres in the icon column, and `taskbar-icon-size` sets that column to its `TaskbarButtonWidth` of 38 (`TaskListButton_UpdateVisualStates_Hook` writes `MediumTaskbarButtonExtent`). Every icon sat (40-38)/2 = 1 px left of its box.

Backup before the writes: `backups\2026-09-25\windhawk-taskbar-styler-before-round4.reg` (92,544 bytes).

| Value | Before | After |
|---|---|---|
| `controlStyles[15].styles[5]` | `TranslateTransform X="0"` | `X="1"` |
| `controlStyles[15].styles[6]` | translate then `ScaleTransform 0.9` | scale first, then `TranslateTransform X="1"`, so the hover shift stays a full 1 px |
| `controlStyles[4].styles[2]` | side margins `{{$highlightOffset}}` (4) | `1`, so the box is 34 px wide, same as its height |
| `controlStyles[4].styles[1]` | `Height@NoRunningIndicator` full pill height (42) | same formula as running apps (34) |
| `controlStyles[4].styles[3]` | `Margin@NoRunningIndicator := 0,0,0,0` | `1,-2,1,-2`, same as running apps |
| `controlStyles[4].styles[7]` | `BorderThickness@NoRunningIndicator := $borderThickness` | `0` |
| `controlStyles[4].styles[9]` | `CornerRadius@NoRunningIndicator := $buttonRadius` (7) | `$highlightRadius` (5) |

The last three rows exist because the first probe after the width change showed two box sizes. Running apps had 34x34 boxes, while pinned apps that are not running had 32x38 boxes with radius 7. Those buttons reuse the full-height pill geometry, with a transparent 2 px border inside it. Their fill and border are transparent in this rice, so the only visible effect of unifying them is the hover box.

`$highlightOffset` is left at 4, because `controlStyles[25]` (tray and widget backgrounds) and `controlStyles[50]` (overflow button) also use it. The box's side inset is now a literal.

Two elevated applies (`.tmp\taskbar-pill4\apply-wrapper.ps1`, 14:52 and 14:55), each verified by the script. A forced-visible probe (`.tmp\taskbar-pill4\probe.ps1`, the same `#40FFFFFF` Background trick as round 3, without the pill shift) was used for measurement, then reverted.

Measured on `reports\tb-pw-round4b-probe.png` against `tb-pw-round4b.png`:

- All 16 boxes are 34 px wide and 34 px tall (rows 8..41), radius 5. Running and pinned buttons are identical.
- Icon-vs-box centre delta: 0 on 13 buttons and -0.5 on 3. Those three have odd-width artwork (25 or 21 px), so they cannot centre on a whole pixel.
- Every icon moved exactly +1 px between `tb-pw-round4-before.png` and `tb-pw-round4.png`.
- After the probe was reverted, `tb-pw-round4-final.png` matches `tb-pw-round4b.png` pixel for pixel across the whole icon strip (x 900..1640). The only differences are the weather ticker and the tray clock changing between captures.
- Final `-Audit`: 24 pairs, 0 differences. Probe values `styles[21]`/`[22]` are absent.

Zoomed before/after of one box: `reports\tb-round4-box-compare.png` (left: round 3, 28 px wide and off-centre; right: round 4, 34x34 and centred).

Rollback for round 4 only: import `backups\2026-09-25\windhawk-taskbar-styler-before-round4.reg`, then bump `SettingsChangeTime`.
