# Translucent Flyouts: menu look settled by settings (2026-10-13)

Continues `2026-10-13-translucent-flyouts-0.6.10.md`. Thread 912ca616.

## What changed in the live registry (no DLL change in this step)

| Key | Before | Now | Why |
| --- | --- | --- | --- |
| `local@translucent-flyouts\Settings\global.enableDropShadow` | 1 | 0 | The 4 to 5 px dark ring was present with the mod's menu styling off too. Removing the drop shadow made the ring read as a thin outline. |
| `local@translucent-flyouts\Settings\global.enableThemeColorization` | 1 | 0 | Accent-coloured borders made the submenu's border blue and the main menu's dark. With it off, both use the same neutral border. |

Also tested and restored: `menu.disabled` (set to yes for a stock baseline, then back to `use_global`).
`custom-corner-radius\Settings\smallRadius` was set to 8 for a test and is back at 16, with its reload marker bumped.

## Measured (live desktop menu, `2026-10-13-flyout-fix\probe-v3.ps1`)

- Main menu and submenu both have a window region and the same translucent grey fill.
- `screen.png` and the 8x crops (`m1-*.png`, `m2-*.png`): corners are rounded, edges are not
  aliased in the crops. A dark band about 4 to 5 px wide still sits between the outline and the
  fill at 8x. It reads as a thin outline at normal size, but it is still there.
- Not checked: tooltips and dropdowns. Both settings are global, so they change those too.

## Rollback

Set the two keys back to 1 (both are DWORD). Pre-experiment values are in
`backups\2026-10-13\translucent-flyouts-corners\settings-pre-experiment-local@translucent-flyouts.reg`.
Each change is applied with the elevated helper:

    H:\System Configuration\scripts\Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-13-translucent-flyouts-menu-experiment.ps1" -ArgumentList "-Name global.enableDropShadow -Value 1 -Type DWORD"

## Open

- The 4 to 5 px dark band is still unexplained. The drop shadow appears to account for the heavy
  look, but the band is still measurable at 8x.
- The submenu fill is no longer black. Its region is set in this state, so the earlier
  `FindFlyoutWindowOnCurrentThread` concern did not reproduce here.
