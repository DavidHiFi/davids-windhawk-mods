# Translucent Flyouts corners: 2026-10-13 status (not fixed, nothing installed)

Thread 912ca616, continuing 903cdb47 (failed on a provider rate limit) and b350e228 (interrupted).
Live mod: `local@translucent-flyouts` 0.6.9 (`_0.6.9_1.dll`, `Include=*`). Exclude list intact:
`discord*.exe|Voicemeeter*.exe|Matrix*.exe|Stream Deck*.exe|dwm.exe`. No registry, DLL or source
change was made in this run.

## Measured (live, Explorer pid 26112, started 06:32 local)

- Desktop main menu, 321x597 at (150,693). Region: complex, 16 px arc. Corner pixel (0,0) is
  outside the region and (8,8) is inside. DWM corner preference: ROUNDSMALL (3).
- 8x crops in `2026-10-13-flyout-fix\m1-TL.png` and `m1-TR.png`: the outer outline is rounded,
  but the grey fill inside has a square corner. A dark band about 5 px wide runs along every
  side. The first fill pixel sits at inset 5 for rows 6 to 16.
- The user's own crop (`2026-10-13-flyout-audit\user-zoom-TL.png`) shows the same square inner
  corner.
- Submenu: not captured in the steady-state run. The keyboard walk did not open it. An earlier
  probe (`2026-10-13-flyout-audit\sub-TL.png`) caught it mid-animation, so that crop can't be
  used.

## From source (`src\30-engine.inc`)

- `DrawThemeBackgroundHook`, MENU_POPUPBORDERS (lines 585-598): PatBlt BLACKNESS over the whole
  rect, then `HandlePopupMenuNonClientBorderColors` draws a 1 px square `FrameRect`.
- `HandleMenuDrawThemeBackground` (lines 483-484): BACKGROUND, GUTTER and ITEM parts are each
  PatBlt'd BLACKNESS over their clip rect.
- `ApplyMenuWindowRegion` (lines 248-286): 16 px rounded-rect window region on menus with
  ROUND or ROUNDSMALL.

## Why the 16 px region does not fix it

The region only trims the outermost corner. The fill's square corner sits at about (5,5) from the
window corner. That point is inside the 16 px circle centred at (16,16), so the fill is not
clipped. On the diagonal the fill corner comes within about 0.4 px of the outline, so the fill
reads as square. A concentric inner radius would be 16 - 5 = 11 px.

## Not verified

- Which paint call draws the 5 px dark band. The BORDERS and BACKGROUND hooks above both
  PatBlt full rects, so the band may come from uxtheme or from DWM, not from our paint.
- Submenu corners in steady state.

## Options (pick one before the next install)

1. Recommended: clip the menu fill to a rounded rect inset by the band width, with radius
   16 - band (about 11 px), so the fill is concentric with the outline. First confirm the band's
   origin with one experiment: set `menu.enableCustomRendering=0`, bump `SettingsChangeTime`,
   probe, then restore.
2. Raise the region radius to 18 or more so the arc cuts the square corner. Quick to build, but
   the outline then no longer matches the 16 px DWM radius from custom-corner-radius.
3. Square menus (`DWMWCP_DONOTROUND`). Removes the mismatch and also the rounding.

## Files

- `2026-10-13-flyout-fix\probe-v3.ps1`: steady-state probe. It right-clicks the desktop, walks
  to View, records region and DWM state and a first-fill profile, and saves 8x corner crops
  `m<n>-<corner>.png`. A wrong menu count means the old menu was still open. Press Escape first.
- `2026-10-13-flyout-fix\menu-probe-copy.ps1`: copy of the v2 probe, output redirected here.
- Rollback for 0.6.9, unchanged: `scripts\2026-10-12-translucent-flyouts-0.6.9.ps1 -Rollback`
  (points `LibraryFileName` back to `_0.6.8_350274.dll`).
