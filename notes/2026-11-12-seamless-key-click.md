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

## Not done
- Public repo: the mod is not published, and the readme's preview link is not live yet. Waiting on the owner.
