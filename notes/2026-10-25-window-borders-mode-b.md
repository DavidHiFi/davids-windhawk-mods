# window-borders Mode B (overlay) checkpoint, 2026-10-25

Owner, about 7:30 AM: keep building, do not disturb the desktop. So: offline only.

Plan (assumptions decided here, from research report section 5.2):
- One layered, click-through overlay per top-level window, created on the window's own
  thread and owned by it (no cross-thread owner, which would join input queues).
- Painted with UpdateLayeredWindow and a CPU-drawn anti-aliased rounded ring
  (no D2D/DComp, no DwmEnableBlurBehindWindow: keeps the mod away from blur APIs).
- Tracking from the existing DefWindowProc hook (WM_WINDOWPOSCHANGED, activation,
  DPI) plus a 200 ms poll timer on the overlay's own thread.
- Hidden when the window is maximized, minimized, hidden, cloaked or fullscreen.
- Settings: mode (overlay default), width, offset, radius, style solid/gradient,
  gradient end color and angle, fade duration.
- Verify: compile both arches, plus an offline render test that writes a PNG.
- Install: not done. Needs a short app list (freeze rules); owner picks.

Status: see bottom.

## Freeze audit — completed (10/25)

40-minute kill-switch watch ended clean at 8:33 AM: samples=2314, avg DwmFlush=5.9 ms, worst=226 ms (single spike, recovered), no freeze, service Running. No single mod implicated — a freeze needs translucent-windows widely loaded together with other window or shell mods. translucent-windows stays Disabled=1.

## Status 8:10 AM (measured)

- Mode B written in `Windhawk\window-borders\local@window-borders.wh.cpp`; rev 5 builds clean for 64- and 32-bit.
- Opus review found 7 issues, all fixed: worker class registered under the app's module (crash on reload), DPI-unaware apps (now physical-pixel scope + monitor DPI), full-window layered surfaces (now 4 thin strips, about 40x less surface; faded-out overlays are destroyed), child-control message cost (early WS_CHILD exit), unload while code is running (busy counter, 1 s drain), topmost leak in z-order, NaN fade when fade time is 0.
- Offline render test: `Test-window-borders-render.ps1` -> `reports\2026-10-25-window-borders-overlay-render.png` (strip split, no seams).
- Install script: refuses missing or `*` Include, runs the freeze gate, writes mode=overlay.
- Mod id line fixed to `window-borders` (freeze thread report, 7:36 AM).
- NOT installed; mod stays Disabled=1 (owner). Not tested live.

Next: owner picks a short app list, then one install:
`Install-window-borders.ps1 -Action Install -Revision 5 -Include 'notepad.exe|...'`

## Settings Styler Plus — 2026-10-25 update (option 1, completed)

- Registry: `local@settings-styler-plus` `IncludeExcludeCustomOnly` set to `0` (reverting freeze-cutback `IncludeCustom` override). `Include` list (`SystemSettings.exe|ApplicationFrameHost.exe`) now active for both processes. `dwm.exe` stays in global `Exclude`; caption buttons mod stays out of DWM.
- Source (work-settings-styler-plus): 1.3.1 already includes both `@include` targets.
- PR #21 linked (`link_pull_request`); open, 1.3.0 commit 40ca980 (1.3.1 commit e26f91a is local only).
- Freeze gate (`scripts/Test-WindhawkFreezeGate.ps1`) not re-run this turn; kill-switch scripts (`scripts/2026-10-25-windhawk-watched-start.ps1`, `freeze12-prestart.ps1`) kept intact.
- Visual verification of Settings window (one window, blurred title bar + caption buttons, no jump) and freeze re-check: still pending per freeze-safety rule and owner's instruction; change is verified by registry readback (`reg query`).

## Live on Notepad++ (2:35 PM, measured)

- Owner said "continue working" after the two-app offer; took option 1, narrowed. Notepad is not installed on this PC, and File Explorer already carries caption-buttons, title-bar colours, file-explorer-styler and window-manager, so the test app is Notepad++ only (`Include=notepad++.exe`). Freeze gate PASS.
- First install drew a 1 px square ring: the installer never wrote the `overlay.*` settings and a registry install gets no @settings defaults, so width/radius/fade read as 0. Fixed in `Install-window-borders.ps1` (writes and reads back overlay.width/radius/fadeMs).
- Recheck (`scripts/2026-10-25-window-borders-notepad-check.ps1`): DLL `local@window-borders_1.0.0_5.dll` loaded in the new Notepad++ process; focused capture shows a 2 px #89B4FA rounded ring, unfocused capture shows none. Proof: `reports/2026-10-25-window-borders-live/notepad-{focused,unfocused}.png`.
- Rollback: `Install-window-borders.ps1 -Action Rollback -Revision 5`. Widening the app list is the owner's call; keep File Explorer off it.

## Gradient on (owner request, 3:00 PM, measured)

- overlay.style set to gradient (installer default changed too): accent blue to Catppuccin Mocha mauve #cba6f7 at 45 degrees. Ring pixels read 8BB4FA top-left, BEA9F8 right middle, CAA6F7 bottom-right. Proof: reports/2026-10-25-window-borders-live/gradient-corners-zoom.png. Backup: backups/2026-10-25/window-borders/mod-key-before-gradient.reg.

## Gap closed (owner request, 3:10 PM, measured)

- overlay.offset -1 (installer default too). Ring pixels now touch the window on left, right and top (no 545454 desktop pixel between). Proof: reports/2026-10-25-window-borders-live/tight-corners-zoom.png.
- Same turn: the rainbow bars on screen were two full-screen H:\System Configuration\work\abdm-backdrop.ps1 windows left open by the ABDM blur thread (12:16 PM and 2:43 PM). Closed at owner's request; that thread was told.
