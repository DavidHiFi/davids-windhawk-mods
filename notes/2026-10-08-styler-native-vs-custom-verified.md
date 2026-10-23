# Windhawk Styler rev 18 — native vs custom title bar verified (2026-10-08)

Fills a gap: the 03:42 corner-bug thread built and installed rev 18
(`local@windhawk-styler_1.5.0_18.dll`) and reloaded the tool, but never
captured it — the newest capture in `reports\2026-10-08-corner-bug\` is
named r17, and the UI window (started 03:33) predated rev 18 anyway.

## Method

- `scripts\2026-10-08-styler-native-titlebar.ps1` (elevated): flips
  `nativeTitleBar`, bumps `SettingsChangeTime`, waits for the recreated
  window, reports style bytes. Both flips triggered a clean window restart.
- `scripts\2026-10-08-styler-capture.ps1` (elevated): title-based window
  finder that works in both modes (the r17 finder required WS_CAPTION and
  would miss the frameless window), full capture, strip 1x, four corners 5x,
  region stats.
- Both captures same session, same animated wallpaper, same window rect
  1100x760 at (1308,360), both after a forced restart so both show rev 18.

## Findings

| Mode | Style | Strip mean | lumStd | Corners |
| --- | --- | --- | --- | --- |
| Native | 0x16CF0000 | (27.8,27.7,42.8) | 6.77 | TL/TR/BL/BR clean |
| Custom | 0x14030000 | left (34.2,33.1,44) / right (31.4,32.3,45) | 9.6-21 | TL/TR clean |

- No artifacting in either mode: no corner blocks, no band, no menubar
  remnant, no seam. Corners are rounded with the standard Win11 corner
  border highlight.
- The acrylic is the same frosted sheet in both modes: strip tone within
  ~5 RGB units same-session, and both vary left-to-right with the wallpaper
  gradient — live glass, not a solid fill. Custom reads a touch brighter
  because the page veil tints it; native shows DWM acrylic with the strip
  veil popup on top (the rev 15 architecture, unchanged).
- Custom mode extras: HTML titlebar (logo, centered title, glyph buttons)
  and the light-blue accent border around the frameless window. Native
  extras: real caption with themed pastel buttons.

## End state

- `nativeTitleBar=1` (the user's setting), mod live on rev 18, window open
  in native mode. Pre-change registry backup:
  `backups\2026-10-08\styler-native-compare\mod.reg`.
- Clickable copies for T3 threads:
  `C:\Users\localuser\AppData\Local\Temp\opencode\windhawk-styler-2026-10-08\`
  served by the running T3Viewer on http://127.0.0.1:8477 (all 10 embeds
  verified 200).
- Receipt: `reports\2026-10-08-native-vs-custom\receipt.json`.
