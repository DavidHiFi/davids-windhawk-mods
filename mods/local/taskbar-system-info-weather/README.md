# Taskbar System Info with Weather

GPL-3.0 fork of [Yevhenii Starychenko's Taskbar System Info](https://github.com/starychenko/windhawk-taskbar-system-info). Upstream credits and license notices remain in the source.

Paste [taskbar-system-info-weather.wh.cpp](taskbar-system-info-weather.wh.cpp) into Windhawk's **Create new mod** editor, compile and enable it. Disable the original **Taskbar System Info** to avoid duplicate monitors.

With [Independent Taskbar Weather](../taskbar-weather) enabled, this monitor starts six DIP after the weather's visible right edge and follows changes in width. Without weather it uses its configured left offset. Windows 11 x64.

Version 1.1.0 adds compact, font-measured CPU/GPU spacing and stacked network rates immediately after the temperatures. Upload is on the CPU row and download on the GPU row. Network readings use the existing metrics worker, so the separate Network Speed Indicator mod is unnecessary.

- **Show graphs** turns CPU/GPU history traces and RAM/VRAM capacity bars on or off. The default is off. Hidden graphs release their layout space.
- **Show network speeds** turns upload and download readings on or off. The default is on.
- **Font family** accepts any installed Windows font name. Save to apply it. Empty uses Segoe UI Variable Text. Labels and values remeasure with the font.
- **Widget width** at 0 fits the content. A positive value sets a minimum width. The network column reserves enough space for unit changes, which prevents those changes from moving the following metrics.

Network rates use local 64-bit byte counters and actual elapsed time from active physical Ethernet and Wi-Fi adapters. Virtual adapters, tunnels and loopback are excluded to avoid duplicate counts. New adapters and reset counters need one baseline sample. Missing readings show `-- B/s`, while idle rates show `0 B/s`. Units are decimal B/s, KB/s, MB/s, GB/s and TB/s. No network requests are made.

Your existing temperature providers, colors, refresh interval and font settings remain available. David's Audio Visualizer follows the panel's measured right edge. The original System Info and separate Network Speed Indicator should stay disabled to avoid duplicate widgets.

Build and live checks on Windows 11 with Windhawk 1.7.3 covered both toggles, changing the font, an empty font setting, and font size 13. Explorer stayed running throughout. Counter tests covered elapsed time, idle traffic, counter resets, adapter changes, filtering, failed API calls and unit formatting. Reboot, sleep and other display scales were not tested for this revision.

Run `python tests/test_network.py` on Windows with Windhawk's bundled compiler installed to repeat the counter tests. The test compiles the collector and formatter directly from this mod's source, supplies controlled interface samples, and writes generated files under `tests/output`. `--output-dir` selects another output directory.

Disable this fork and re-enable the original monitor to undo it. No Explorer restart is required.
