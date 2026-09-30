# Taskbar System Info with Weather

GPL-3.0 fork of [Yevhenii Starychenko's Taskbar System Info](https://github.com/starychenko/windhawk-taskbar-system-info). Upstream credits and license notices remain in the source.

Paste [taskbar-system-info-weather.wh.cpp](taskbar-system-info-weather.wh.cpp) into Windhawk's **Create new mod** editor, compile and enable it. Disable the original **Taskbar System Info** to avoid duplicate monitors.

With [Independent Taskbar Weather](../taskbar-weather) enabled, this monitor starts six DIP after the weather's visible right edge and follows changes in width. Without weather it uses its configured left offset. CPU, GPU, RAM, VRAM and history graphs retain the upstream behavior and settings. Windows 11 x64.

Disable this fork and re-enable the original monitor to undo it. No Explorer restart is required.
