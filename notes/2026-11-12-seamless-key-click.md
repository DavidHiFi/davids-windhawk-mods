# Seamless Key Click 1.0.1 (fork of Key Click by Anixx, with Keyboard Sounds packs)

Date: 2026-11-12, thread 138571e3. Live since 1:07 am.

## What it is
- Tool mod `local@seamless-key-click`, runs in its own windhawk-mod.exe.
- Every Keyboard Sounds pack (17 keyboard, 1 mouse), pinned to Keyboard Sounds commit 6785c7ac,
  downloaded on demand into the mod's storage `packs\` folder. Own packs work too (any folder with profile.yaml).
- Key-specific sounds (space, enter, backspace...), release sounds, random pitch, overlap limit, app allow/block lists,
  ignore synthetic input (default on), mouse buttons incl. side buttons.
- Shortcuts: Ctrl+Alt+K turns all sounds on or off by default; keyboard, mouse, volume up and down are settable.
- Tray icon: click opens settings, right-click menu toggles and picks packs.
- Settings window: the Launchpad engine with the standard glass (accent 4/2/0x012E1E1E, backdrop none,
  blur-behind, tint 0.55 flat). `settings-material.py check` says ok.

## Source and build
- Generator: `work\2026-11-11-seamless-key-click\` (spec.py, gen.py, assemble.py, src\). Run gen.py then assemble.py.
- The glass is folded into `src\settings-template.cpp`, so a rebuild keeps it; the rebuilt file was byte-identical
  (line ends aside) to `settings-material.py stage` output.
- Template backup before the glass edit: `src\settings-template.cpp.bak-20261112-*`.
- Offline harness `test\harness.exe`: 18 packs parse, key mapping right, plays, downloads.

## Install
- `scripts\2026-11-12-seamless-key-click.ps1 -Install` (elevated, under coop lock windhawk-engine, through heavy.py).
  Compiled 1.0.1, restarted the helper (pid 17560), then removed the original `key-click`.
- Original backed up first: `backups\2026-11-12\key-click\` (source and registry key).
- Receipt: `reports\2026-11-12-seamless-key-click-receipt.json`.
- Rollback: same script with `-Rollback` (removes the fork, reinstalls Key Click disabled, as it was).

## Live checks (1:07 to 1:17 am)
- Registry: version 1.0.1, enabled, library `local@seamless-key-click_1.0.1_747024.dll`.
- Helper running, XAudio2 and Media Foundation loaded, audio session active.
- The live mod downloaded the Alpaca pack by itself (15 files).
- Sound: over 3 minutes of the owner's own typing, 194 meter samples with sound, peak 0.17, first at 1:10:53 am.
- Ctrl+Alt+K is held (RegisterHotKey from outside gets error 1409).
- Tray icon registered (Shell_NotifyIconGetRect ok).
- Settings window opened by posting the tray message (no cursor, no keys), recorded, closed by WM_CLOSE.
  Preview: `work\2026-11-11-seamless-key-click\media\seamless-key-click.png`.
  The first recording showed the page wider than the window once; the window was 841x1357 on reopen and drew
  correctly; not reproduced.

## Found on the way (told the owners on the coop board)
- `Install-StagedMod.ps1` splits a staged path with a space ("Failed to read 'H:\Windhawk'") and still prints
  "installed". The fork got installed by its own script instead.
- `vcap.py record` takes a folder, not a file name; its share step fails on odd frame heights (1039).
- A window that does not change gives the recorder one frame only; use a still for static windows.

## 1.0.2 (8:52 am): tray menu look and the 2.4.7 settings engine
- Owner: the tray menu hover was a flat grey, not Launchpad's blue to mauve pill; the settings footer
  dock was see-through.
- Cause of the menu: tool mods run in their own windhawk-mod.exe, where Seamless Flyouts (which
  paints Launchpad's menu in explorer) never loads.
- Fix: `src\menu-look.cpp` is Mixer's shared block (menu room + pill + skin with its CBT hook),
  copied verbatim. `core.cpp` includes it and calls `SeamlessMenuSkin::Init()` in WhTool_ModInit
  (hooks apply when init returns, so it has to be there) and `Uninit()` in WhTool_ModUninit.
  `assemble.py` inlines it.
- Footer blur and hovers: bd0ca06f's refreshed engine (Launchpad 2.4.7) through gen.py.
- Offline compile clean (`test\compile-offline.ps1`; only the expected InternalWh_* link errors).
- Installed by `install-1.0.2.ps1` through Install-StagedMod with the 1.0.1 base hash; registry
  1.0.2, enabled, helper restarted. settings-material check: ok.
- Proof recorder: `test\capture-tray-menu.py` opens the menu by its own tray message, walks the
  hover with MN_SELECTITEM, closes it with a posted Escape. It must wait for the recorder's first
  frames: the first run opened the menu while ffmpeg was still starting (8 s under load).
- The same block goes to the other tool mods with `scripts\2026-11-12-tool-menu-look.py`
  (note `notes\2026-11-12-tool-menu-look.md`).

## 1.1.0 (11-12 night): sound toggles, Look tab, notifier dock
- Keyboard and mouse sounds each have an on/off toggle; a new Look tab holds the settings-window
  options plus the notifier dock (place, size, glass, gradient ring, timing).

## 1.1.1 (11-13, 12:41 am): dock corners no longer cut off
- Owner: the dock's corners clipped the gradient ring (screenshot "Sounds ... Off").
- Cause, by pixel read: the dock used Windows' own round corner (DWMWCP_ROUND, acrylic accent). On
  this build that arc is 12 to 16 px and not circular, larger than the 8 px painted ring, so it
  sliced the ring at all four corners.
- Fix, copied from Seamless Dictate's Glass class: the dock window is DONOTROUND, no border, per-pixel
  alpha only (blur-behind with an empty region). A separate click-through glass window under it
  carries the blur: host backdrop brush, Gaussian blur 18, clipped by a composition rounded rect at
  the same 12 DIP radius. The ring is drawn concentric (inset half its width, radius minus half).
  UI thread now CoInitializes (STA) for the dispatcher queue. `-lruntimeobject` added.
- Old: DWM round corner, acrylic accent, 8 px ring. New: own glass, DONOTROUND, 12 DIP corner.
- Verified live: registry 1.1.1, helper restarted, capture shows all four arcs whole, background
  text not readable behind the dock. Proof: `work\2026-11-12-key-click-notifier\media\dock-corners-1.1.1.*`.
- Rollback: install `ModsSource\local@seamless-key-click.wh.cpp.bak-20261113-0040` (1.1.0) with
  Install-StagedMod; settings backup `work\...\settings.bak-20261113-0040.reg`.

## Not done
- Public repo: the mod is not published, and the readme's preview link is not live yet. Waiting on the owner.
