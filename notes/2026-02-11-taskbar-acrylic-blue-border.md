# 2026-02-11 — Taskbar more acrylic + Catppuccin Mocha blue border

7:26 PM start (2026-02-11). Request: two edits to the Tasper (Taskbar) Styler — a bit more
acrylic/frosted on the taskbar background, and the pill border from Catppuccin Mocha surface0
(#45475A gray) to Catppuccin Mocha blue (#89B4FA).

## What changed (windows-11-taskbar-styler, registry)

- `styleConstants[18]` taskbarFill: BlurAmount 110 → 140, TintOpacity 0.75 → 0.62,
  TintLuminosityOpacity 0.8 → 0.72, FallbackColor alpha BF → A6. A touch more translucent.
- `controlStyles[1].styles[4]` stroke: `#9945475A` → `#9989B4FA` (alpha 99 kept).

## Incident (honest log)

The first apply script wrote taskbarFill **without the `taskbarFill = ` prefix** that lives
inside the value, so the constant failed to parse and the pill lost both fill override and
stroke. Explorer crashed about 3:41 PM (0xc0000142 on its restart attempt) while that broken
state was live. Recovered by restarting explorer at 3:50 PM, restoring the prefix
(`fix-taskbarfill-prefix.ps1`), and bumping `SettingsChangeTime` on the mod root key
(the Settings-subkey bump alone does not trigger the reload). Second reload was clean.

## Verified

- Registry read-back: both values correct.
- Pixel proof on screen: left edge 5E78A6, right edge 5E79A9 — the expected 60%-alpha blue
  blend of #9989B4FA. Fill tone shifted (1E1E2E → 1F1F2E at sample point) consistent with the
  lower tint opacity.
- Evidence: reports\2026-02-11-taskbar-acrylic-blue\taskbar-full-strip-final.png,
  corner-left-final-zoom.png, taskbar-final-top.png.
- Backup for rollback: backups\2026-02-11\windows-11-taskbar-styler-before.reg
  (receipt in the same folder).
