# Compact taskbar weather

Applied 2026-10-03. Independent Taskbar Weather changed from 1.2.3 to 1.3.0. Temperature is centered above the condition beside the icon. Both lines use the existing modest semibold face. This also publishes the earlier font-weight and icon-centering fixes that were only installed locally.

The widget measures the wider line instead of the combined horizontal label. At the live Clear reading, its right edge moved from 135 to 96 DIP. Stats moved from 456 to 417 DIP and the visualizer start from 464 to 425 DIP. The current reading saves 39 DIP. Longer condition strings were measured offline. Loading and unavailable messages retain a single line.

The x64 build passed. Installed DLL hash matches the build. Explorer loaded the new DLL and remained at PID 32028. All weather settings match the backup. The stats and visualizer DLLs and registry versions remain unchanged. The live capture confirms readable stacked text. Display scale was 96 DPI. Other scales, reboot and physical sleep were not tested. No restart is pending.

Published and merged through https://github.com/DavidHiFi/davids-windhawk-mods/pull/5. GitHub main matches installed source after line-ending and trailing whitespace normalization. Evidence is in reports/2026-10-03/weather-stack.

Rollback copies are in backups/2026-10-03/weather-stack. Run scripts/taskbar-weather/Install-Stack.ps1 -Rollback with silent elevation to restore the previous source and registry metadata. The old DLL remains installed. Calling the script without switches audits the installed version. Only the weather mod was reloaded, with no Explorer restart.
