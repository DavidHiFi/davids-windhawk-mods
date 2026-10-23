# RAM and VRAM capacity alignment

Applied 2026-10-03. System Info changed from 1.2.2 to 1.2.3. Both gigabyte readings now align to the right of their existing shared capacity column. The RAM and VRAM totals and G suffixes end at the same position, removing the trailing gap on the shorter VRAM reading.

The x64 Windhawk 1.7.3 build passed. Installed source and DLL hashes matched the build. All saved system-info settings were preserved. The live 96-DPI capture confirms aligned endings, with panel right edge unchanged at 417 DIP. Explorer remained at PID 32028. Weather, visualizer, graph switches and capacity bars kept their settings. Other scales, reboot and physical sleep were not tested. No restart is pending.

Published and merged through https://github.com/DavidHiFi/davids-windhawk-mods/pull/7 as 8f4fb049e847b9829f7348e191c9fc75c0fc6ee8. GitHub main matches the installed source after line-ending normalization. Evidence is in reports/2026-10-03/memory-align, including baseline and final captures, build result and publication receipt.

Rollback: run scripts/system-info/Install-Capacity.ps1 -Rollback with silent elevation. Backups are in backups/2026-10-03/memory-align. The previous DLL remains installed. Calling the script without switches audits the installed configuration. Only this mod was reloaded; Explorer was not restarted.
