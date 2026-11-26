## Explorer icon: Catppuccin Mocha blue folder instead of pink (done on the tower)

What changed
- explorer.exe's icon still comes from the base niivu Catppuccin pack: `C:\ProgramData\Windhawk\Engine\ModsWritable\mod-storage\icon-resource-redirect\Catppuccin\Windhawk Resources\explorer.dll`. That pack's explorer.dll wins over any later themePaths override.
- Recalled the pink folder tones in that explorer.dll (Mocha pink #F5C2E7 main folder) to Mocha blue #89B4FA at every size (256 png, 48/32/24/16 dib), keeping each pixel's brightness relative to the main pink so the flap stays darker; paper sheet and grey shadow untouched. Built `explorer-blue.dll` from `explorer-pink.dll` with `D:\Agent Work\2026-11-26-explorer-blue\recolor.py`.
- Installed the blue explorer.dll into a new dated copy of the pack, `Catppuccin-blue-20261126-1050`, and pointed Resource Redirect's stored theme folder `HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\icon-resource-redirect\LocalStorage\themeFolder_Catppuccin` at it via `scripts\2026-11-26-explorer-blue.ps1 -Install` (run elevated). iconTheme and disableThumbnails untouched, so no visible Explorer cache prompt appeared. SettingsChangeTime bumped.
- Windows now hands out the blue folder for explorer.exe itself (Extracted icon colours: #89B4FA #D9E0EE #8CB8FF; see `verify.py` output in the job folder).
- The dock kept showing pink because its process loads its own icon cache live and caches icons per process. Turned the dock off with `Set-ModState.ps1 -Id local@seamless-dock -Off`, then tried `-On` again.

Dock restart
- 10:58 the first -On was refused by the live-load gate (free memory 3.6 GB, under 4); the dock stayed off until 12:06.
- 12:06 `restart-dock.ps1` again: off, on, 60 s watch "desktop fine". New dock process 12816, version 0.3.15.

Proof
- Fresh process, the dock's exact lookup (IShellItemImageFactory on explorer.exe, `factory.ps1`): #89B4FA main, #7AA0DF flap, #D9E0EE paper. No pink.
- Screen grab of all monitors at 12:07: no #F5C2E7 pixels anywhere. Explorer is not pinned on the dock, so its folder only shows while an Explorer window is open; none was open, and no window was opened for the proof.

Left as is
- The original `Catppuccin` folder stays (rollback target). Nothing to publish: this is Resource Redirect's stored theme folder, not a mod source or setting.

Files
- `D:\Agent Work\2026-11-26-explorer-blue\explorer-blue.dll` — the new icon file
- `D:\Agent Work\2026-11-26-explorer-blue\explorer-pink.dll` — the old one, for comparison
- `H:\Windhawk Configuration\backups\2026-11-26-explorer-blue\LocalStorage.bak-20261126-1050.reg` — registry before the switch
- `H:\Windhawk Configuration\backups\2026-11-26-explorer-blue\LocalStorage.bak-20261126-105851.reg` — registry after turning the dock off

Rollback
`scripts\2026-11-26-explorer-blue.ps1 -Rollback` points themeFolder_Catppuccin back at the original 'Catppuccin' folder and bumps SettingsChangeTime.
