# Seamless Snipper (ShareX port), 2026-11-12

Plan and owner decisions: `docs/plans/2026-11-12-seamless-snipper.md`.
Work folder: `work/2026-11-12-seamless-snipper/` (spec.py, gen.py, assemble.py, src/, test/).

## Step 1: core (0.1.0)

What it has: region snip (frozen screen, dim, window and control snapping, magnifier with pixel
grid, size pill), window, monitor and full-screen snips, clipboard plus save to
`G:\Gallery\<dd-mm-yy>\<App> h.mm am.png`, toast card, tray icon and menu, ShareX keys
(PrintScreen, Shift, Alt, Ctrl + PrintScreen), and the standard settings window.

- Keys step aside while ShareX.exe runs (setting "Step aside for ShareX", on). The keys are
  checked every 3 seconds, so they take over by themselves once ShareX closes.
- The real Gallery uses per-app folders; the design asked for day folders, so it is a setting
  (Subfolder: day, app or none; default day).
- Settings engine: built on the current Launchpad engine (template copied from crosshair, which
  `settings-engine.py check` reports in sync).

Build: `python gen.py`, `python assemble.py`, then the offline compile through the load gate
(`test\compile-offline.ps1`; the only errors are the expected Windhawk API link gaps).

Install: `install-0.1.1.ps1` (elevated, under `coop lock windhawk-engine`). Its BaseHash is the
live source's hash (the live copy is CRLF, so it never matches the staged LF file).

## 0.1.1 (review fixes, live now)

- Save reserves the file name first (CREATE_NEW, " (2)" suffixes), so two snips in one minute
  never overwrite each other; a failed encode deletes the empty file.
- Toast hides before a new snip and never enlarges a tiny snip past 1:1; D2D device loss
  redraws instead of leaving a blank card or region screen.
- Shutdown waits for saves in flight, then drains their messages before the window goes.
- Missing keys retry every 3 s (one key held by another app no longer blocks the rest).
- While a settings key box is listening, the mod hands its own keys (PrintScreen) to that box
  instead of snipping. Limit: if no app has PrintScreen registered at all, Windows only sends
  the key-up, so the box can't record it; fixing that needs an engine change (owned WndProc).

Tested live (posted keys, ShareX still running so real keys step aside):
- Active screen 1920x1080, every screen 6400x2520 (negative origins right), window snip
  "T3 Code (Nightly) 8.41 pm.png" 1880x1040; clipboard holds the image; toast on the right monitor.
- Helper idles at 18 MB; after full-screen snips it holds ~65 MB working / ~128 MB private and
  stays there across further snips (heap and D2D caches, not a per-snip leak).

2026-11-13, after the restart: ShareX did not start again, so Snipper holds the real keys.
The owner took 7 snips with them (12:02 to 12:33 am), including two in one minute that saved
as "12.18 am.png" and "12.18 am (2).png". Region take (`test\take-region-3`): window highlight
with name and size, magnifier with pixel grid, colour and position readout, Enter takes the
window, toast with thumbnail. Settings window opens from the tray on the Keys page.
Rollback: `windhawk-cli mod uninstall local@seamless-snipper`. Nothing else is touched; ShareX
stays installed and running until the switch-over after step 3.
