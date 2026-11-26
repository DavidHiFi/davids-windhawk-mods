# Light frost audit, every mod (2026-11-26)

Owner: "eliminate this light kind of like the blur material globally, do an extensive audit, get rid of it
for good." The light frost is DWM's system acrylic (`DWMWA_SYSTEMBACKDROP_TYPE` 3) and Mica Alt (4), or any
grey body fill under glass. The house look is the accent acrylic sheet, tint 0x012E1E1E, black body.

Tools: `work\2026-11-26-glass-audit\scan.py` (source scan of every installed mod) and `live-backdrops.py`
(every visible window and the system material it has). Live scan at 12:20 pm: 49 windows, none on a system
material.

| Mod | What it asks for | Verdict |
|---|---|---|
| Seamless Winver Configurator | grey body on plain backdrop | fixed in 1.1.1 (house sheet) |
| Network Menu Speed Test Plus 2.4.3 | system acrylic (3) on the flyout, 80% Mocha layer on top | fixed in 2.4.4 (house sheet, Mocha layer kept) |
| Seamless Flyouts | accent acrylic, Mocha base 40 to 85% on all 34 rules | fine |
| File Operation Styler Plus | blur, Mocha #1E1E2E at 85% | fine (its "acrylic" option is the system one; not in use) |
| Seamless Clipboard Manager, Taskbar tray, Enhanced Styler, WinTips OSD | accent acrylic | fine |
| Seamless Controls | dark Mica on Explorer frames, file pickers, wizards; its own winver backdrop is off | fine (dark, no frost) |
| Seamless Taskbar own list windows | dark Mica or none (Mocha) | fine |
| File Explorer Styler Plus | system acrylic under the styler's dark Mocha fills | kept: this is the Explorer glass the owner picked on 2026-11-19 |
| Seamless Title Bars | only on a command from the Windhawk page | fine |

Lesson added to the rice skill (`references\stacks.md`, Native Win32) and synced to every agent.
