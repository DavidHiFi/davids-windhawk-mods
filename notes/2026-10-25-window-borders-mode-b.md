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

## Status 8:10 AM (measured)

- Mode B written in `Windhawk\window-borders\local@window-borders.wh.cpp`; rev 5 builds clean for 64- and 32-bit.
- Opus review found 7 issues, all fixed: worker class registered under the app's module (crash on reload), DPI-unaware apps (now physical-pixel scope + monitor DPI), full-window layered surfaces (now 4 thin strips, about 40x less surface; faded-out overlays are destroyed), child-control message cost (early WS_CHILD exit), unload while code is running (busy counter, 1 s drain), topmost leak in z-order, NaN fade when fade time is 0.
- Offline render test: `Test-window-borders-render.ps1` -> `reports\2026-10-25-window-borders-overlay-render.png` (strip split, no seams).
- Install script: refuses missing or `*` Include, runs the freeze gate, writes mode=overlay.
- Mod id line fixed to `window-borders` (freeze thread report, 7:36 AM).
- NOT installed; mod stays Disabled=1 (owner). Not tested live.

Next: owner picks a short app list, then one install:
`Install-window-borders.ps1 -Action Install -Revision 5 -Include 'notepad.exe|...'`
