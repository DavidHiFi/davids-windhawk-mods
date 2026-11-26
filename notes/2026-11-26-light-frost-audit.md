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

## Live proof and Speed Test 2.4.5 (2026-11-26, evening)

- First live proof (7:12 pm, `work\2026-11-26-glass-audit\proof-live`): speed test pop-up over busy text read
  flat in glass-check (movement 0.25): no light frost, but the 0.80 Mocha layer hid the blur. The About box
  shot did not count: another window sat on top of it (the agent window manager opens it without focus).
- Speed Test 2.4.5: the Mocha layer over the glass went from 0.80 to 0.55, the settings windows' tint.
  Installed 9:38 pm (desktop fine after 60 s), published as commit 6ff08f6 on the mods repo.
- `glass-proof.py` now lifts the About box and the busy window into the topmost band before the shot.
- Second live proof (10:15 pm, `proof-live2`): About box over busy text passes glass-check (movement 5.3,
  frosted): dark house glass, colour moves under it, text behind never reads, gradient banner and FiraCode
  in place. The speed test shot again had a dark app window between it and the test pattern (movement
  0.6 / 0.2, not a fair test), so `glass-proof.py` now lifts the pattern and the pop-up too, and takes
  `winver` or `speedtest` as a second argument to run one part only.
- Third run queued as the hidden task "Agent glass fix run 2" (`D:\Agent Work\swc\fix-run2.ps1`), result in
  `proof-live3` and `fix-run2.log`.
