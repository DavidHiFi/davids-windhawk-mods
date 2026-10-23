# Title bar menu: plain Windows menu (2026-10-13)

REVERSED later the same day: the owner wants Translucent Flyouts on the Windhawk window like any other app. The block list was emptied (script rollback) and the mod cycled once. Menu verified translucent (`#282838`, accent border, not red). Keep the block list EMPTY through future installs unless the owner says otherwise.

Owner decision: the Windhawk window's right-click title bar menu should be the normal Windows menu. It may bypass Translucent Flyouts. Translucent menus everywhere else are unchanged.

## Change

- `local@translucent-flyouts`, setting `advancedFunctions.processBlockList` = `windhawk-ui.exe` (was empty). This is the mod's own process block list.
- The block list is read only when the mod starts, so the mod was cycled once: Disabled 1, then 0, with SettingsChangeTime bumped each time. Same as switching the mod off and on in the Windhawk UI.
- Script: `scripts\2026-10-13-titlebar-menu-standard.ps1` (`-Action Audit | Apply | Cycle | Rollback`), run elevated through `Invoke-Elevated.ps1`.
- Backup and receipt: `backups\2026-10-13\titlebar-menu-standard\` (`translucent-flyouts.reg`, `receipt.json`).

## Verified

- Registry reads `windhawk-ui.exe`. Mod version 0.6.24, enabled.
- Windhawk UI (pid 33928, not restarted): `local@translucent-flyouts` is no longer loaded in it. `local@windhawk-styler_2.0.46` is loaded.
- Right-click, icon click and Alt+Space each open the menu. Escape closes it.
- Icon-click capture (`reports\2026-10-13-styler-polish\titlebar-check-iconclick.png`): solid #1E1E2E body, standard items, Restore greyed out when not maximised.
- Styler CSS still present: 20 input rules, accent #89B4FA.

## Side effects

- Every process running translucent-flyouts reloaded during the cycle (about 8 seconds), explorer included. Other menus on the PC stay translucent.
- Explorer restarted at 13:10:23, before the cycle began. These commands did not cause it. The Application log shows no crash.

## Rollback

1. `Invoke-Elevated.ps1 -File scripts\2026-10-13-titlebar-menu-standard.ps1 -ArgumentList "-Action Rollback"`. Empties the block list and renames the receipt.
2. Same script with `-ArgumentList "-Action Cycle"`. The block list is read at start, so the mod must restart to pick up the rollback.
