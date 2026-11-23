# Seamless Dock 0.3.4: keep the reserved strip on a stray TaskbarCreated

Date: 2026-11-24. Job folder: `D:\Agent Work\2026-11-24-dock-taskbarcreated\`.
Asked for by the dock-bounce thread (see `notes\2026-11-24-dock-bounce.md`).

## What was wrong

Any app can broadcast TaskbarCreated. The store mod taskbar-disappearing-tray-icons-fix did
it every 5 s (now off). Each time, 0.3.3 dropped its appbar and took it back, so the work
area bottom went from 1366 to 1440 for about half a second and maximised windows dipped
under the dock.

## Fix (0.3.4)

- `AppBarRegister` records the Shell_TrayWnd hwnd and its pid after a good registration.
- On TaskbarCreated: if the appbar is held and the tray hwnd and pid are the same, only the
  shell hook and the recycle watch are refreshed ("strip kept" in the log). Otherwise the
  old full path runs ("strip taken back").
- Patch script: `patch.py` (builds 0.3.4 from live 0.3.3, base hash 69E1DD13...).

## Install and proof (1:32 to 1:38 am)

- `install.ps1`: Install-StagedMod under the windhawk-engine lock, base hash checked. Tool
  process restarted (pid 20632), gate watched 60 s: desktop fine. Published: mods 318da6a,
  feed 9727715. Live hash A1267869....
- Proof: `tbc-listen3.ps1` ran 12 s while an elevated script posted TaskbarCreated to all
  six dock windows (`post.log`). Work area bottom stayed 1366 the whole time
  (`listen.log`). Before the fix the same signal pushed it to 1440.
- A real Explorer restart was not tested (no restart run for this); that path is unchanged.
