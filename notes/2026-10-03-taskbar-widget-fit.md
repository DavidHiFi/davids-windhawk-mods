# Taskbar weather weight and visualizer spacing

Applied on 2026-10-03. The first install completed at 10:55 AWST.

The previous font fix changed only the size. The weather row still used regular weight while the system-info labels used semibold. Weather 1.2.3 now draws and measures its row with the installed FiraCode Nerd Font SemBd face at 11 pixels. Its hover card retains its existing typography. The existing centering and 8-pixel icon gap remain in place.

System-info 1.0.1 publishes its right edge on the taskbar as `WindhawkTaskbarSystemInfoRightDip`. It updates this value before each metrics refresh, including when the weather width changes, and removes it when unloaded. Visualizer 1.0.1 reads that edge each frame and places its content 8 logical pixels after it. Background padding and optional text also reserve space. If the panel is unavailable, the visualizer uses the saved offset. The saved offset stays at 500. No audio routing settings changed.

The visualizer requires both 32-bit and 64-bit builds. Windhawk runs its dedicated tool process as 32-bit on this machine. Both builds are installed under the same library filename.

## Verification

All builds passed. Installed DLL hashes matched their build files. Explorer loaded the new weather and system-info modules; the visualizer tool process loaded its new module. The taskbar capture shows the heavier weather text and the spectrum after the panel.

A reversible live test moved the weather offset from 16 to 76, then restored 16 in a finally block. The weather right edge changed from 135 to 195, the panel edge from 471 to 531, and the visualizer start from 479 to 539. After restoration all values returned to their original positions. Captures show the visualizer following the panel without overlap. Explorer stayed at PID 9576.

Evidence is in `reports/2026-10-03/taskbar-weather/widget-fit-restored.json`, `widget-fit-shifted.json`, and their PNG captures. No restart is pending. Discord, Ableton, VB-Audio Matrix, and Stream Deck were untouched.

## Rollback

Registry exports and original sources are in `backups/2026-10-03/taskbar-widget-fit`. Original DLLs remain installed alongside the new files. Run `scripts/taskbar-weather/Install-WidgetFit.ps1 -Rollback` through the documented silent elevation route to restore the three original registry records and sources. The script supports a read-only audit when called without switches.

Build sources are in `work/taskbar-weather/taskbar-weather.wh.cpp` and `work/taskbar-widget-fit`. Installation changes only these three mods' versions, library filenames, and reload timestamps. Their stored appearance, weather location, capture settings, and other preferences are preserved.

