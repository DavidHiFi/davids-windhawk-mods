# Main 01 renamed DavidHiFi's Theme, with the riced cursors (2026-11-24)

Owner: "Make sure that's in our theme preset for the theme thingy. And rename our theme from
main01 ... to davidhighfivestheme." Theme Tool Plus is the theme thingy; its bundled theme Main 01
is now **DavidHiFi's Theme**, and it carries the new Mocha cursors (option 1 shapes: thicker edge on
the filled shapes, one smooth spinner arc; see `2026-11-24-cursor-rice.md`).

## Pack v2
- `work\theme-pack\build_pack_v2.py` starts from the v1 stage and adds
  `Cursors\Catppuccin-Mocha-Seamless-Cursors` (from `tools\catppuccin-cur\out-mocha2`), renames the
  theme and wallpaper, sets `pack.ini` Version=2.
- Release `theme-tool-plus-pack-v2` on DavidHiFi/seamless-workshop (not latest), asset
  `theme-tool-plus-pack.zip`, 8,192,317 bytes, SHA-256
  `C4CA9B14EB7F1E59F7285406613E78956569130AACF8A8AB45075BCC1057EAAB`. Downloaded back, hash matched.

## Mod 1.3.0 (`work\theme-pack\stage-1.3.0`, made by `patch_1_3_0.py`)
- Pack url, hash and `kPackVersion = 2`. Settings option "DavidHiFi's Theme" replaces Main 01.
- A saved `themeName` of "Main 01" is read as the new name.
- `RemoveOldMainTheme` deletes the marked `Main 01.theme` and its wallpaper after the new pack
  lands, unless Windows is using Main 01 right now.

## This PC (`scripts\2026-11-24-theme-rename.ps1 -Install`, elevated, 5:08 am)
- Pack folder got the v2 cursors, theme, wallpaper and pack.ini. `DavidHiFi's Theme.theme` is in
  `C:\WINDOWS\Resources\Themes` and is CurrentTheme. Main 01 theme and wallpaper removed.
- 15 cursor roles point at the pack's cursor folder; scheme `Catppuccin-Mocha-Seamless-Cursors`;
  the duplicate `C:\WINDOWS\Cursors\Catppuccin-Mocha-Seamless-Cursors` was removed.
- Browser cursors (chromium-cursor-remap folder) replaced with the option 1 set.
- Mod setting `themeName` changed to the new name. MouseTrails still -1.
- Live check: arrow, wait, hand, no and working sample fill (30,30,46); wait shows the surface0
  track (49,50,68) of the new spinner.

## Rollback
- Elevated: `scripts\2026-11-24-theme-rename.ps1 -Rollback` (copy to `C:\Users\Public` first). It
  restores Main 01, pack.ini and the three registry exports in `backups\2026-11-24-theme-rename\`.
  Its cursor export points at the removed `C:\WINDOWS\Cursors\Catppuccin-Mocha-Seamless-Cursors`,
  so run `2026-11-24-cursor-rice.ps1 -Install` first.
- Mod: reinstall 1.2.0 from `C:\ProgramData\Windhawk\ModsSource\local@theme-tool-plus.wh.cpp.bak-*`.
