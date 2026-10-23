# Translucent Flyouts corner artifact: findings, no install

2026-10-12, thread ebb8ff41-b11c-4417-9d9d-0a4a69f0a0ec. Status: not fixed, not
installed. The live mod is still `local@translucent-flyouts` 0.6.8 (`_350274.dll`,
`Include=*`). Nothing in the mod's source or registry was changed in this run.

## Measured

- Settings that matter: `global.cornerType=large_round` (DWMWCP_ROUND),
  `global.enableThemeColorization=1` (accent border, so `colorUseDefault=false`
  and `ApplyBorderEffect` sets `DWMWA_BORDER_COLOR` on every menu),
  `menu.enableCustomRendering=1`, `global.effectType=modern_acrylic`.
- `custom-corner-radius` 1.3 (`Include=dwm.exe`) has `radius=16`,
  `smallRadius=16`. Its `RadiusForOriginal` maps every DWM radius to 16, so
  menus get a 16 px DWM outline (from source; not read back from DWM).
- The user's Explorer context menu (attachment `ebb8ff41-...-e7be158c...png`,
  crops `reports\2026-10-12-flyout-corners\user-menu-TL-6x.png` and
  `user-menu-BR-6x.png`): the light grey menu fill has square corners inside a
  rounded dark outline. The outline is round, not square, so the square
  `FrameRect` in `HandlePopupMenuNonClientBorderColors` is not the visible
  artifact.
- The harness menu (`2026-09-28-translucent-flyouts-menu-test.ps1`, mode
  `menu`, 0.6.8) shows a clean rounded corner with the fill following the arc.
  The artifact did not reproduce there. `dropdown` is a classic ComboLBox the
  mod does not style. The tooltip crop was too small to judge.
- Two recent attachments (`df29546e...`, `935755b8...`, 1:35 and 1:40 AM) are
  FreeDictate settings and the launchpad, not flyout menus.

## Inferred (not verified)

- The square fill is client/acrylic content that DWM's 16 px rounding does not
  clip. The rounded outline is the DWM frame, drawn outside the square corners.
- A rounded window region that matches the DWM radius (16 px for these menus)
  would clip the fill as well. This is untested. It could also change how DWM
  draws the border.

## Draft from the failed run (not built, not installed)

Uncommitted edits in `src\00-foundation.inc` (version 0.6.9) and
`src\30-engine.inc` (skip `FrameRect` when corners are rounded; fall back to the
theme border when colorized). They change the square ring, which is not the
visible artifact, and the fallback may draw a square theme border. Do not ship
them as the fix. Assembled against `ModsSource` they differ only in those lines.

## Options for the user

1. Clip popup menus to a rounded region matching the 16 px DWM radius
   (`SetWindowRgn`). Recommended. Test on the Explorer menu after install;
   roll back by pointing `LibraryFileName` at `_0.6.8_350274.dll`.
2. Make menus square (`DWMWCP_DONOTROUND`). Removes the mismatch but drops the
   rounding you asked for.
3. Set `custom-corner-radius` `smallRadius` back to 8. Shrinks the gap but does
   not remove the square fill.

## Coop

Claim `corner-fix` belonged to the failed run from this thread. It was released
on 2026-10-12 at about 2:10 AM; the 0.6.8 `ModsSource` file is still canonical.
