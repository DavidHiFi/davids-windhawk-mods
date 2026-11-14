# Seamless Title Bars 1.2.0: glass dock, title font, settings window, right-click menus

Date: 2026-11-12. Thread: Seamless Title Bar Docks and Uptime (1a27061b).
Owner ask: the dock fill was too dark; make it fit the rice with proper blur material; configurable
title font and weight, default FiraCode Nerd Font Medium; our template settings window; right-click
the dock for our template menu.

## Files
- Build: `work\2026-11-11-title-dock\v12\gen12.py` turns live 1.1.3 (sha256 ADA48C66…B03C) plus
  Launchpad's installed settings engine (2.4.9) and `kc-menu.cpp` (SeamlessMenuSkin) into
  `v12\seamless-title-bars.wh.cpp`. Blocks: `blk-shared.cpp` (DWM <-> tool shared memory),
  `blk-tfont.cpp` (title font in DWM), `blk-tool.cpp` (tray, dock menu, font copy).
- Offline compile: `v12\compile12.py` (through the load gate): exit 0, no errors; d2d1, dwrite,
  windowscodecs, comdlg32 and imm32 are delay-loaded (none in the import table).
- Script: `scripts\2026-11-12-seamless-title-bars-1.2.ps1` -Action Audit | Install | Rollback.
  Backups: `backups\2026-11-12\seamless-title-bars-1.2\` (1.1.3 source, reg exports, log).

## What changed
- Dock fill: surface-0 #313244 at 45% (was crust #11111B at 85%), plus a soft top shine
  (Glass shine switch). DWM's title surface cannot sample what is behind it, so the "blur" is
  the light glass tint over the frame's own Mica/acrylic, matching the rice's light-glass docks.
- Title font: Family (default FiraCode Nerd Font) and Weight (default Medium, 500). In DWM the
  factory CreateTextFormat is hooked (vtable slot 15) and only acts inside CDWriteText's own
  CreateTextFormat/CreateTextLayout. A font change flips one byte of the window's cached LOGFONT
  (+0x13C) once so each title makes a new format; this is only done when the expected bytes are
  found in CreateTextLayout. Title width for centring is measured in the same font.
- Per-user fonts (FiraCode is installed per user) are invisible to DWM, so the tool process finds
  the font file (DirectWrite, family + weight) and copies it to mod storage with a read-only ACL
  for SYSTEM, admins, everyone and the Window Manager group, then bumps a counter in shared memory.
  Fonts under C:\Windows\Fonts are used in place.
- Settings window: the universal Launchpad engine (Look, Uptime, Colours and buttons, Apps, About;
  Settings window group: glass, native title bar, tray icon). Saves go through windhawk-cli.
- Tray icon (tool process): click opens settings; right-click shows the template menu with Title
  dock, Window uptime, Caption buttons toggles and Settings.
- Dock right-click: DWM writes the hovered dock's rectangle to `Local\SeamlessTitleBarsHotDock`;
  the tool's low-level mouse hook swallows a right-click only when the snapshot is fresh, the
  window is alive and not hung, and the point is inside that dock. Menu: Restore, Minimize,
  Maximize, Always on top, Copy title, Window menu, Title bar settings, Close. Off switch:
  Title dock > Right-click menu.

## Rollback
`scripts\2026-11-12-seamless-title-bars-1.2.ps1 -Action Rollback` reinstalls 1.1.3 from the copy.
Settings stay; the new keys are ignored by 1.1.3. Titles keep the chosen font until each window's
font is next refreshed (or the window reopens).

## Verification (2026-11-14, 4:15 pm)
- 1.2.0 installed and ran through 1.2.1 to 1.2.5 (now live, enabled); every later build is a patch on this one.
- The dock with the glass fill and title font shows on the not-responding box capture `work\2026-11-13-hung-dialog\hung124.png`.
- Not separately filmed in this thread: the dock right-click menu and the tray menu.
