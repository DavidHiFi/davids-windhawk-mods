# Explorer styler: tabless, no search box, left command bar (2026-10-27)

Mod: windows-11-file-explorer-styler 1.7.2, theme OS26 Liquid Glass kept. Custom controlStyles replaced
(the old ones were inert: controlStyles[0].target was empty, so the mod stopped reading at entry 0).

- Tabs: the window-behaviour parts of the Tabless theme (tab strip border, add and close buttons hidden,
  36 px title row) plus an override of the OS26 tab pill, so the one tab reads as a plain window title.
  Skipped from Tabless: its row swap, Segoe UI font and chrome background, which would undo the OS26 look.
- Search: AutoSuggestBox#FileExplorerSearchBox collapsed, address bar spans its column (Grid.ColumnSpan=2).
  The linked hide-search-bar mod targets the old Win32 search box, so the styler route replaces it.
- Command bar: HorizontalAlignment=Left; the command bar root grid gets columns Auto, Auto, * so Details
  sits right after View.

Evidence: reports/2026-10-27-explorer-tabless/2026-10-27-explorer-final.png (PrintWindow of a freshly
opened This PC window, 3:18 PM). A window open during the hot reload showed doubled blur on disabled
buttons until reopened.
Script: scripts/2026-10-27-explorer-styler-tabless.ps1 (elevated). Rollback: same script with -Rollback,
restores backups/2026-10-27/explorer-styler-tabless/settings-before.reg.

## Blur fix (3:25 PM)

Explorer drew a flat dark background with no blur (measured: on-screen capture of a fresh window,
reports/2026-10-27-explorer-tabless/blur-0-now.png). Two mods were setting the Explorer backdrop: the styler
(backgroundTranslucentEffect=acrylicblur) and translucent-windows (RuledPrograms explorer.exe, acrylicblur
8C1E1E2E). Setting the styler effect to "" (theme default, the styler leaves the backdrop alone) brought the
blur back (2026-10-27-explorer-blur-final.png, on-screen capture). It also removes one of the two mods
writing the same window part in Explorer, which is on the freeze-risk list.
The Translucent Explorer11 theme was not merged as styles: its transparent bars are already in OS26, and its
only other change is its own acrylic backdrop, which would bring back the double-backdrop conflict.
Rollback: scripts/2026-10-27-explorer-styler-effect.ps1 -Effect acrylicblur (elevated).
