# 2026-10-02 — taskbar gap 1 (system-info ↔ media player) and gap 2 (network ↔ clock)

Session: agent-coop `taskbar-gaps`, lock `system-settings`.
Backups: `backups/2026-10-02-taskbar-gaps/`. Scripts: `scripts/2026-10-02-taskbar-gaps/`.

## Gap 2 — closed (observed)

Ask: remove the 16 px hole between the Mullvad network icon and the date-time clock.

Baseline (UIA, 22:31): network `SystemTray.AccentButton` 2416–2440, clock 2456–2538, element gap **16 px**, visible ink gap ≈26 px.

Cause (observed): the clock's own left margin is 0 and the ControlCenter button carries 16 px on its right. The styler's own clock rules (`controlStyles[22]`/`[24]`, target `SystemTray.OmniButton#NotificationCenterButton`) never match on this build — `NotificationCenterButton` is the bell, whose runtime class is `SystemTray.AccentButton` — so nothing closed the hole.

Change: new rule `controlStyles[60]`

- target: `SystemTray.OmniButton`
- styles[0]: `Margin := -12,0,0,0`

Result (measured after the styler reloaded):

| | before | after |
|---|---|---|
| network box | 2416–2440 | 2440–2464 |
| clock box | 2456–2538 | 2468–2550 |
| element gap | 16 px | **4 px** |
| ink gap (pixel runs) | ≈26 px | **13 px** |

Neighbouring tray glyphs measure 12–14 px between them, so the clock now sits on the same rhythm as the rest of the tray. 4 px of element gap is the practical floor: the boxes must not overlap or the hover rectangles touch. No Explorer restart was needed — bumping the `SettingsChangeTime` DWORD re-runs `Wh_ModSettingsChanged`.

Hypothesis (not proven): the leftover 13 px of ink gap is padding inside the ControlCenter button (4 px) plus the clock's own text inset (5 px).

## Gap 1 — blocked, no change made

Ask: make the system-info widget and the Fluent Media Player card sit 6 px apart *dynamically* instead of the 27 px seen in the user's screenshot.

Facts:

- The player mod `taskbar-fluent-media-player` reads `Disabled=1` in `HKLM\SOFTWARE\Windhawk\Engine\Mods` right now, so no card is on the taskbar and the gap does not currently exist.
- It was present in the user's 20:47 screenshot: system-info content ends at x≈488, card `FluentMedia_OuterBorder` starts at x=515, card ends at 734 → **27 px**.
- With the card absent the widget stretches to the next element (its content now runs to ≈840), so the widget already reflows; what is fixed is the card's `playerMargin = 515 0`.
- The system-info widget, the media player card and the clock are all XAML inside the taskbar's `DesktopWindowContentBridge`. Only the weather widget (`WindhawkIndependentWeather`, 16–152) is a real child window.

Plan, unchanged: Option B — the local system-info mod walks up from `FluentMedia_OuterBorder` to its grid and sets `playerGrid.Margin.Left = panelRight + 6` on layout updates, no-op when the card is absent. It is a pure settings/runtime change on our side; the player mod stays untouched.

Cost: edit `local@taskbar-system-info-weather.wh.cpp`, rebuild the DLL with the `scripts/taskbar-weather/Build.ps1` clang recipe, and reload the mod — which needs an Explorer restart. That restart is the reason this is waiting for the owner rather than being done unilaterally.

## Rollback

- Full: re-import `backups/2026-10-02-taskbar-gaps/windhawk-styler-before.reg`, then bump `SettingsChangeTime`. This removes `controlStyles[60]` and restores `[59]` byte for byte.
- Narrow: `scripts/2026-10-02-taskbar-gaps/Invoke-StylerJob.ps1 -Action Restore -Index 60` (the state entry records that index 60 had no values, so the restore deletes them).
- `windhawk-system-info-before.reg` and `windhawk-media-player-before.reg` were exported before anything was touched; neither mod has been modified.

## Tooling and one hazard

- `Measure-TrayGap.ps1` (UIA, `-OutJson`/`-Quiet`), `Set-StylerControlStyle.ps1` (job-file Apply/Restore), `Run-Elev.cmd`, `Invoke-StylerJob.ps1` (writes the job, elevates with `Start-Process -Verb RunAs -Wait`, prints the new log lines).
- The elevated script runs in PowerShell 5.1, whose `Get-Content` default is ANSI. It read its own UTF-8 state file without `-Encoding UTF8` and wrote the private-use glyph code points of `controlStyles[59]` back as Windows-1252 mojibake (`E971` → `EE A5 B1`). Restored byte-exact with `backups/2026-10-02-taskbar-gaps/fix-controlstyle59.reg` (`reg import`, elevated), verified by re-reading the code points, then re-bumped `SettingsChangeTime`. The script now passes `-Encoding UTF8`.
- Two general facts worth keeping: UIA `ClassName` is the automation peer name, not the runtime class name (`Taskbar.TaskListButtonAutomationPeer` vs `Taskbar.TaskListButton`), and a styler target only matches when `winrt::get_class_name(element)` is equal to it — no inheritance.
