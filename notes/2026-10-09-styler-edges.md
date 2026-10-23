# Windhawk Styler 2.0.9 native border

The user accepted 2.0.8's overall appearance and asked to fix the remaining faded corner edges and restore the Windows accent border.

Measured configuration: Custom Window Corner Radius uses 16 pixels for both regular and small corners. Windows 11 Accent Window Border is enabled but excludes `windhawk-ui.exe`. The styler itself forced `DWMWA_BORDER_COLOR` to `DWMWA_COLOR_NONE`, so Windhawk had no native border stroke around its corners.

The styler now gives DWM the current Windows accent from `Explorer\Accent\AccentColorMenu` for an active window. Inactive windows use `DWM\AccentColorInactive` when configured, otherwise the Windows default. This is the native DWM border, including its antialiasing and the existing 16-pixel corner geometry. It does not add an overlay or copy the border into a square bitmap. The global corner and accent-border mod settings were not changed.

Measured results: close-up screenshots show a continuous accent stroke around the bottom-left, bottom-right and top-left arcs instead of the previous fading straight segments. Full-window captures cover all four corners. Both caption and body continue responding to a changing background while inactive. Twelve focus transitions, maximize/restore, resize and minimize/restore passed. The title and native controls remained visible and no centered watermark returned. The final build has no compiler warnings.

The screenshots establish that restoring the native stroke resolves the visible edge defect. They do not establish a defect in the global corner-radius mod.

Source: `work/windhawk-styler/tauri20/windhawk-styler.wh.cpp`. Evidence and receipt: `reports/2026-10-09-styler-edges/`. Run `scripts/2026-10-09-styler-edges.ps1 -Rollback` elevated to restore the accepted 2.0.8 source and recompile. Its source, registry export and DLL are saved in `backups/2026-10-09/styler-edges/`.
