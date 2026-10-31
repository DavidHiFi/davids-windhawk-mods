# Taskbar progress as an underline bar

Date: 2026-10-31. Mod: `windows-11-taskbar-styler` (controlStyles 7, 8, 10, 11 and styleConstants 20).

Before, the progress bar filled the whole button as a square block at 35% accent. Now it is a 3 px rounded bar in the Pill Plus underline spot (bottom margin 4), BtnW-20 wide, with a solid surface1 track (#45475A). Fill colors: accent, peach #FAB387 when paused, red #F38BA8 on error. Indeterminate keeps the native sweep on the thin bar.

Pill Plus appends its `ElasticPillOpen` underline to the same panel after the progress bar, so the bar needs `Canvas.ZIndex = 5` on `ProgressBar#ProgressIndicator` or the underline hides the fill.

- Apply / audit / rollback: `scripts\2026-10-31-taskbar-progress-underline.ps1`
- Backup: `backups\2026-10-31\taskbar-progress\taskbar-styler-before.reg`
- Test: `scripts\2026-10-31-taskbar-progress-test.ps1` shows a minimized window with progress and captures the taskbar
- Evidence: `reports\2026-10-31-taskbar-progress-underline.png`. Measured 2026-10-31 3:27 pm: 60%, paused, error and busy states captured on the live taskbar.
