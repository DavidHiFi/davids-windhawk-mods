# Dark menus merged into Translucent Flyouts (2026-10-24)

The standalone mod "Dark mode context menus" (`dark-menus` 1.4.2, by Mgg Sk) is retired and removed.
Its code and its one setting now live inside Translucent Flyouts 0.6.66 (`local@translucent-flyouts`).
There is no separate "Plus" flyouts mod on this machine, so that is the mod that got the merge.

## What moved

- Source part `Windhawk\translucency-flyouts\src\20-dark-menus.inc` (namespace `tf::DarkMenus`): the dark
  menu bar drawing (WM_UAHDRAWMENU / WM_UAHDRAWMENUITEM), the DefWindowProc / DefFrameProc and
  SetMenuInfo hooks, and the uxtheme dark-mode switch.
- New setting `darkMenus.appMode`: `force_dark` (default, same as the old ForceDark), `allow_dark`
  (only when Windows is dark), `off`.
- The old `TranslucentFlyoutsFix` option is automatic now: when the menu effect is on, the menu
  background brush stays black so the blur shows through.
- Header: version 0.6.66, `@author DavidHiFi, ALTaleX531, Mgg Sk`, credits for Mgg Sk, win32-darkmode, Notepad++.
- The build script (`scripts\2026-09-28-translucent-flyouts-build.ps1`) lists the new part and now reads and
  writes UTF-8 without a BOM. Before this, PowerShell 5.1 read the parts as ANSI and garbled the
  em dashes in comments.

## Side effect

Translucent Flyouts skips Discord, Voicemeeter, Matrix, Stream Deck and dwm (protected audio chain).
Dark Menus had no skip list, so those processes no longer get dark menus from this mod.

## Evidence (checked 11:34 AM to 11:40 AM)

- Registry: `local@translucent-flyouts` LibraryFileName `..._0.6.66_1.dll`, Version 0.6.66, Disabled 0,
  `Settings\darkMenus.appMode=force_dark`. `Mods\dark-menus` key gone, `ModsSource\dark-menus.wh.cpp` gone.
- Installed 64-bit DLL hash equals the build output.
- Module scan: 231 processes load the 0.6.66 DLL, all 14 Explorer processes included.
- Screenshot of a fresh menu: `reports\2026-10-24\translucent-flyouts-menu-20261024-113604.png`
  (dark, translucent, accent ring).
- Logs: `work\2026-10-24-dark-menus-merge\install.log`, `build-0.6.66b.log`.

## Still open

13 long-running apps (Discord, Steam web helpers, Mullvad, Dopamine, T3 Code, SearchHost and Qt web
engine) still hold the old `dark-menus_1.4.2_744984.dll` and the 0.6.65 flyouts DLL. They drop them on
their next restart. The two old `dark-menus_*` DLL files stay on disk until then (mapped files cannot be deleted).

## Rollback

`scripts\2026-10-24-dark-menus-merge.ps1 -Rollback` (elevated): points flyouts back at 0.6.65_5 and
reinstalls dark-menus from `backups\2026-10-24\dark-menus-merge\dark-menus.wh.cpp` with AppMode=ForceDark.
Registry exports of both mods are in the same backup folder.

## Final check (3:55 PM)

- Flyouts is now 0.6.67 (another thread's hover fix on top of the merged code). Registry: `darkMenus.appMode=force_dark`,
  no dark-menus key or source. 260 processes load 0.6.67.
- New menu screenshot on 0.6.67: `reports\2026-10-24\translucent-flyouts-menu-20261024-155448.png` (dark, translucent, ring).
- Explorer crashed at 3:44 PM and 3:45 PM. Both dumps (`work\2026-10-24-dark-menus-merge\dump44028.txt`, `dump19164.txt`)
  show the fault inside `file-explorer-content-animation` 1.0.1 (HookBrowseObject, RPC call). Not flyouts, not dark menus.
  Explorer had no crash in the 4 hours 0.6.66 ran alone (event log, 9:48 AM to 3:39 PM).

## Publishing

The public repo (`DavidHiFi/davids-windhawk-mods`) still has flyouts 0.6.33; the workspace repo has no remote. Nothing public
was pushed: that would release 34 unpublished versions, including the unfinished 0.6.67 hover work. When the flyouts release
goes out, replace the README tip "Pair it with Dark Menus" (already done in the source).
