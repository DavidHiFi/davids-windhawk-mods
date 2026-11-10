# AI Usage Plus 1.1.6: Mocha chip buttons (2026-11-11)

Owner asked: footer buttons (dashboard, refresh, settings) and the two header pills
(reset credits, plan) were too light. Make them dark Mocha with a dull border at rest
and the blue-to-mauve gradient border on hover.

## What changed

- New `MakeMochaChipStyle()` XAML button style (dark theme, not high contrast only):
  - rest: crust `#D911111B` fill, surface1 `#45475A` 1px edge, content at 78%.
  - hover: base `#1E1E2E` fill and a blue `#89B4FA` -> mauve `#CBA6F7` edge fade in
    over 150 ms (Storyboard opacity on layered borders), content to 100%.
  - pressed: opaque crust fill under the gradient edge (60 ms).
  - focus ring: same gradient, no white secondary ring.
  - all brushes are gradients: plain SolidColorBrush dims in this popup.
- Footer buttons: radius 8. Header pills: now a chip button inside the pill holder,
  radius 11, 22 px high, not a tab stop; text uses the main text colour.
- Light theme and high contrast keep the old look.

## Evidence

- Compiled 1.1.5 then 1.1.6 (`_1.1.6_675324.dll`), registry readback ok.
- Shell guard on the 1.1.6 compile reported CHURN: new `explorer.exe /factory ...
  -Embedding` processes (folder COM helpers), main shell 9912 unchanged since 1:24 am,
  no crash events. False positive; mod re-enabled once at 2:01 am, shell steady after.
- Capture of the resting state (1.1.5, via UIA Invoke, no cursor moved):
  `work\2026-11-11-ai-usage-buttons\proof-rest3.png`. Dark fill and dull edge render.
- Not checked: hover and pressed (need the real cursor), the pills with live data, and
  the 1.1.6 focus ring (a full-screen window covered the taskbar).
- Repo copy in davids-windhawk-mods not synced yet (publishing is the owner's call).

## Rollback

`scripts\2026-11-11-ai-usage-buttons.ps1 -Action Rollback` (elevated) restores
`backups\2026-11-11-ai-usage-buttons\source-1.1.4.wh.cpp` and recompiles.
