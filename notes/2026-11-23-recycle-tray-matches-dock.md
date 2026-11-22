# Recycle Bin Tray Plus 1.0.9: tray bin matches the dock (2026-11-23)

Installed 7:20 am, published (mods c146160, feed 683e506). Thread a65eb88a.

## Why
The owner: the tray bin (top bar) and the dock bin (bottom) looked different; make them
the same, empty and full. The dock draws the Windows stock icons
(SHGetStockIconInfo SIID_RECYCLER / SIID_RECYCLERFULL, which the owner's icon theme turns
into a green and a red can). The tray was on the "badge" style (blue to mauve plate).

## What changed
- general.iconStyle badge -> system. The "system" style already used the same stock icon
  calls as the dock.
- 1.0.8 had a "Catppuccin self-heal" that turned "system" back into "badge" on every
  load, so the setting alone did not stick. 1.0.9 only fills in an empty style (with
  system) and leaves a chosen one alone. The default in the settings block is system.
- Readme: "What's new in 1.0.9", System listed first and marked as the default.

## Proof
- empty2-top.png / empty2-dock.png: green can in both.
- full-top.png / full-dock.png: red can in both, after one test file of mine went to
  the bin. That one item was then removed from the bin by hand; the bin is back to 0.
- Side by side: work\2026-11-23-modular-bar\bin-compare.png.
- Install-StagedMod watched 60 s: desktop fine.

## Rollback
- Setting: work\2026-11-23-modular-bar\tray-icon-style.ps1 -Style badge (elevated).
  The old key export is recycle-tray-settings.bak-20261123-0718.reg there.
- Mod: backup local@recycle-bin-tray-plus-20261123-0720.wh.cpp from Install-StagedMod.
