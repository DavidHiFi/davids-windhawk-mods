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
