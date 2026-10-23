# Visualizer capture-device picker

Installed and published 2026-10-04. Version 1.1.0 adds the weather-style Mocha hover highlight and Input device / Output device menus on the bars. The selection names one endpoint ID, persists in Windhawk local storage, and replaces combined capture until the menu restores configured multi-device capture. It does not change routing or Windows defaults.

Both architecture builds passed and the installed source and DLL hashes match. Desktop Output selection saved its endpoint ID. Recording Input opened exactly one shared stream at 48 kHz, stereo float32, with live audio frames and measured nonzero peaks. The endpoint persisted through replacement of the visualizer process. Test selection was cleared and diagnostics restored to 0.

The user reported that the menu appeared behind the taskbar during testing. The final source sets the root menu and submenus topmost with a thread-scoped hook during TrackPopupMenuEx. Placement excludes the taskbar rectangle. Live window style and hit checks pass, and menu-topmost.png shows the root menu and output submenu fully visible below the top taskbar.

The installed system-widget boundary positioning was preserved. Only the visualizer process was replaced. No engine, Explorer, audio-app, or device-routing restart was performed.

Public main and tag davids-audio-visualizer-v1.1.0 point to 82d0aef. Release: https://github.com/DavidHiFi/davids-windhawk-mods/releases/tag/davids-audio-visualizer-v1.1.0

Evidence: reports/2026-10-04-visualizer-devices. Original source, both DLLs, and registry export: backups/2026-10-04-visualizer-devices. Script: scripts/2026-10-04-visualizer-devices/Install.ps1 with -Audit, -Install, and -Rollback. Run elevated via a hidden .cmd wrapper. Installed library: local@davids-audio-visualizer_1.1.0_6.dll. Development checkout: work/visualizer-devices-20261004. The shared repository's existing mixer edit was untouched.
