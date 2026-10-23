# Everything search and Start Menu Styler

Applied on 2026-10-09 at 5:39 AM AWST. Owner confirmed at about 5:41 AM that the search menu looks correct and provided a screenshot showing the themed menu with visible app results, file pane, and footer.

Measured cause: Start Menu Styler's custom Only Search theme set `Grid#FrameRoot` to `MaxHeight=160`. Everything puts its search box, results, and footer inside this same frame. The height limit left the results row without usable space.

Changed only `controlStyles[0].styles[0]` from `MaxHeight=160` to `MaxHeight=640`, enabled `windows-11-start-menu-styler`, and bumped its settings marker. Kept the original gallery `start-everything` 1.0. No mod source edits or experimental fork installation. Theme colors, borders, blur settings, and other rules were preserved. Existing start-menu-size remains 750 by 500.

Independent registry read confirmed the new limit and Disabled=0. StartMenuExperienceHost loaded `start-everything_1.0_508550.dll` and `windows-11-start-menu-styler_1.7_797168.dll`. Owner's screenshot confirms visible results and retained theme. Its file pane reports zero matches for the query, so nonempty file results were not separately tested. Restart persistence was not separately tested; the change is stored in the registry. No restart is pending.

Backup: `backups/2026-10-09/start-search-compat/start-menu-styler.reg` and `before.json`. Receipt: `reports/2026-10-09-start-search-compat/receipt.json`.

Audit with `scripts/2026-10-09-start-search-compat.ps1 -Audit`. To undo, run that script elevated with `-Rollback`. Rollback restores the original height and original disabled state, then bumps the settings marker. `-Install` reapplies the fix.

Keyboard automation reached Flow Launcher instead of Start because of this machine's shortcuts. The owner opened the menu for the successful visual test. Do not treat the automation screenshot as search evidence.

Upstream styling guide was fetched with Firecrawl into `reports/2026-10-09-start-search-compat/upstream-guide.md`. No publication or repository push was requested.
