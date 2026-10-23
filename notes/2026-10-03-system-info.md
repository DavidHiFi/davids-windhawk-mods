# Taskbar system info revision 1.2.2

Installed, verified and published on 2026-10-03 at 17:45 AWST. PR https://github.com/DavidHiFi/davids-windhawk-mods/pull/4 merged as `0e54446a85266a45c6911556cd8f9fde6d0d5fbd` and is linked to this T3 thread.

Upload/download arrows, numeric values and units now use separate matching columns. Arrows align on the left. Numbers and units align on the right. CPU/GPU also use shared columns, so the network arrows start at the same horizontal position. The network unit column ends exactly one configured gap before RAM/VRAM when CPU/GPU history is off. The oversized placeholder area from 1.2.1 is removed. Memory columns remain aligned and stable.

The current settings are preserved: gap 8, both history-line pairs off, original memory-capacity bars on, network on, and FiraCode Nerd Font. Six changing live samples included KB/s and MB/s readings and kept the panel right edge at 515 DIP, compared with 531 before the patch. Captures show both network rows aligned and the gap before memory reduced to the configured spacing. Explorer stayed at PID 32028.

The x64 build, production-source counter tests and Git diff checks passed. Tests now cover promoting a rounded 1000.0 reading to the next unit. Installed source and DLL hashes match the successful build, and GitHub main matches the installed source after line-ending normalization. Evidence is in `reports/2026-10-03/system-info-v1.2.2`, including live captures, `alignment-samples.json`, `final.json`, `build-result.json`, `network-tests.log` and `publication.json`. No restart is pending. Reboot, sleep and other display scales were not tested for this patch.

The installed library is `local@taskbar-system-info-weather_1.2.2_1.dll`. Rollback to 1.2.1 is saved under `backups/2026-10-03/system-info-v1.2.2`, including the previous registry record, source, DLL and `Install-1.2.2.ps1`. Run the saved installer with `-Rollback` through the silent elevated cmd-wrapper route. No Explorer restart is required.

## Previous revision 1.2.1

Installed and published on 2026-10-03 at 17:34 AWST. PR https://github.com/DavidHiFi/davids-windhawk-mods/pull/3 merged as `cb98a3f29d811fea73e846d7bdae8155c0146c3c` and is linked to this T3 thread.

RAM/VRAM labels, percentages and gigabyte values now share stable columns. The compute area reserves a font-measured width for its values, so changes in CPU/GPU or network text length no longer move the memory panel. Memory percentage columns reserve 100%, and capacity columns reserve each device's full-capacity reading. The two memory rows have zero offset from their common origin. This supersedes the per-row memory positioning in 1.2.0.

The install changed only the source, version, library filename and reload timestamp. Current settings were preserved. At baseline and after installation, the user's saved settings were an 8-pixel gap, CPU/GPU history off, RAM/VRAM history off, filled memory bars on, network on, and FiraCode Nerd Font. The user had disabled memory history after the preceding revision; this patch leaves that preference intact.

The bundled x64 build passed. Source and DLL hashes match the installed files, and GitHub main matches the installed source after line-ending normalization. Eight consecutive live samples kept the panel right edge at 531 DIP while the readings changed. Captures show both memory labels, percentages and gigabyte readings aligned vertically. Explorer stayed at PID 32028. No restart is pending. Evidence is in `reports/2026-10-03/system-info-v1.2.1`, including `alignment-samples.json`, `final.png`, `build-result.json` and `publication.json`.

The installed library is `local@taskbar-system-info-weather_1.2.1_1.dll`. Rollback to 1.2.0 is saved in `backups/2026-10-03/system-info-v1.2.1`, with the old source, DLL, registry export and a copy of the installer. Use the saved `Install-1.2.1.ps1 -Rollback` through the silent elevated cmd-wrapper route. No Explorer restart is required.

## Previous revision 1.2.0

Updated on 2026-10-03 at 17:21 AWST. PR https://github.com/DavidHiFi/davids-windhawk-mods/pull/2 was merged as `f080304a72545d46f2bec73680814f5d59fc98cb`. It is linked to this T3 thread. This section supersedes the earlier spacing, graph and rollback instructions below.

The user clarified that the original filled RAM/VRAM rectangles must remain, as well as the history lines on the right. The mod now has independent switches for CPU/GPU history lines, RAM/VRAM history lines and the original memory-capacity bars. The saved preset is `showComputeGraphs=0`, `showMemoryGraphs=1`, `showMemoryBars=1`, and `showNetwork=1`.

One `itemGap` setting applies throughout each row, from 0 to 24 logical pixels. The preset is 8. Each field measures its own text, so short readings and the RAM label leave no reserved blank space. The boundary before RAM/VRAM uses the same gap. Fields can occupy different horizontal positions in the two rows when their text lengths differ. The audio visualizer follows the longest row's measured right edge.

Memory history lines appear after the gigabyte readings. Their scale runs from empty to full capacity over the selected history duration. The original thin filled rectangles remain underneath the memory readings and fill according to current usage. Their switch does not affect the history lines. The font, sensors, colors, offset and refresh interval remain as before.

The installed library is `local@taskbar-system-info-weather_1.2.0_2.dll`. Successful build and installed hashes match. GitHub main source matches after CRLF/LF normalization. Live tests passed all four history-line combinations, capacity bars on/off, spacing at 4/8/12 pixels, Segoe UI and network on/off. Captures confirm the original bars return when enabled and the memory lines remain separate. Explorer remained at PID 32028. Production-source network tests, settings YAML and Git diff checks passed. No restart is pending. Reboot, sleep and other display scales were not tested.

Evidence is in `reports/2026-10-03/system-info-v1.2`. The final preset is in `final.json`, and `final.png` shows the taskbar. Build and GitHub verification are in `build-result.json` and `publication.json`.

Rollback to 1.1.0 is preserved in `backups/2026-10-03/system-info-v1.2`, including the source, DLL, registry export and a copy of the installer. Run the saved `Install-1.2.ps1 -Rollback` through the silent elevated cmd-wrapper route. It restores the source and registry record, removes the newly added settings, verifies the original DLL/source hashes, and advances the reload timestamp. The original installed DLL remains available. No Explorer restart is required.

## Previous revision 1.1.0

Completed on 2026-10-03 at 17:03 AWST. The existing fork was updated rather than creating another installed mod. GitHub PR https://github.com/DavidHiFi/davids-windhawk-mods/pull/1 was merged to main as `b0b4590b0f95104c449d0e126dfaf7cf0ef92700`. The PR is linked to this T3 thread.

The installed source previously reported Yevhenii Starychenko as author, while the published fork already reported DavidHiFi. Both now report DavidHiFi. Original credits and GPL-3.0 notices remain.

CPU/GPU label, percentage and temperature columns now measure their text with the selected font and use small gaps. Upload follows the CPU temperature and download follows the GPU temperature. The network column reserves enough width for normal unit changes. Memory labels also measure the selected font. The panel publishes its measured right edge so the audio visualizer follows it.

The new Show graphs switch controls CPU/GPU history traces and RAM/VRAM capacity bars. Hidden graphs release their layout space. Show network speeds controls both network readings. The existing Font family setting remains editable and applies to the new readings too. An empty font name uses Segoe UI Variable Text.

Network collection uses local 64-bit interface counters in the existing worker. It sums active physical Ethernet/Wi-Fi interfaces, excludes virtual adapters and uses actual elapsed time. First samples, changed adapters and reset counters need a baseline; unavailable readings show `-- B/s`. Idle rates show `0 B/s`. Units are decimal bytes per second. The mod makes no network requests.

## Applied changes

Only the local system-info mod was installed and reloaded. Its version changed from 1.0.1 to 1.1.0. Its library changed from `local@taskbar-system-info-weather_1.0.1_fit1.dll` to `local@taskbar-system-info-weather_1.1.0_3.dll`. The new saved values are `showGraphs=0` and `showNetwork=1`. Width remains 0, now meaning automatic content width. The font remains FiraCode Nerd Font at size 11. Existing offsets, temperature providers, colors and update interval are preserved. SettingsChangeTime was advanced for reloads.

The original System Info and separate Network Speed Indicator were already disabled and remain disabled. Weather and audio settings were preserved. No global Windhawk restart or Explorer restart was issued. No Windows restart is pending.

## Verification

The bundled x64 compiler passed. Final installed source and DLL hashes match the build receipt. GitHub main's source matches the installed source after normalizing Git's LF and Windows CRLF line endings. Both raw hashes are recorded in the publication receipt. Explorer PID remained 32028 during installation and tests. Its module list contains the new library.

Live saved-setting tests covered graphs on/off, network on/off, Segoe UI, an empty font value and font size 13. Captures show the requested row order, tight CPU/GPU spacing, graph visibility and readable fonts. Font size 11 and the original family were restored. The graph toggle and network toggle changed the panel's measured right edge as expected. The visualizer followed the panel without overlap in the captures.

Production-source counter tests passed baseline sampling, elapsed-time rates, idle traffic, counter resets, adapter changes, physical/virtual/loopback/down filtering, failed API calls, recovery, disabling collection, units and missing values. Windhawk settings YAML parsed with both boolean switches and the font setting. Git diff checks passed. This repository has no PR CI checks configured.

Reboot, physical sleep and other display scales were not tested for this revision. Multiple physical adapters are summed; virtual-only traffic is not displayed. Evidence is under `reports/2026-10-03/system-info`, including `build-result.json`, `network-tests.log`, setting captures, `final.json` and `publication.json`.

## Rollback

Original registry settings, source and DLL are in `backups/2026-10-03/system-info`. The original library remains installed. Run `scripts/system-info/Install.ps1 -Rollback` through the silent elevated cmd-wrapper route. It disables only this mod, restores its saved source and registry record, then advances the reload timestamp. No Explorer restart is needed. Calling the script without switches performs a read-only audit.

Reusable build and audit scripts are in `scripts/system-info`. The isolated GitHub checkout is in `work/windhawk-system-info/repo`. The counter test is also published under the mod's `tests` folder.
