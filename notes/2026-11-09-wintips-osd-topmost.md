# WinTips OSD Plus 1.4.1: card stays in front (2026-11-09)

Problem: copy/paste card showed behind windows. The window already had WS_EX_TOPMOST, but
other topmost windows (Launchpad settings, Always On Top Plus border, Seamless Borders parts)
share that band and re-raise themselves; the card used plain ShowWindow, so it never moved up.

Fix (local@wintips-osd-plus 1.4.0 -> 1.4.1):
- ShowCardOnTop(): SetWindowPos(HWND_TOPMOST, SWP_SHOWWINDOW|NOACTIVATE) replaces the three
  ShowWindow(SW_SHOWNOACTIVATE) calls, also runs when a new tip arrives while visible.
- GPU-path SetWindowPos now passes HWND_TOPMOST instead of SWP_NOZORDER.
- kTimerTop (100 ms) re-asserts topmost while the card is visible; killed in HideNow.

Install: scripts\2026-11-09-wintips-osd-topmost.ps1 (elevated): stage source, windhawk-cli
compile, disable+enable. Lesson: a first attempt installed a hand-built DLL; the tool-mod
process died and did not return. Tool mods need windhawk-cli compile (AGENTS.md rule).

Verified: simulated Ctrl+C + clipboard change; card visible for the whole hold at z-position 2,
behind only a 1x1 invisible ThumbnailDeviceHelperWnd. Before the timer it sank from 4 to 9.

Rollback: copy backups\2026-11-07-gpu-plan\local@wintips-osd-plus\2026-11-09-2153\
local@wintips-osd-plus.wh.cpp into ModsSource, run windhawk-cli mod compile, disable+enable.
