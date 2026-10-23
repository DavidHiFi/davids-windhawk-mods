# Windhawk Styler 2.0.64: caption buttons bright, hover works maximized (2026-10-18)

## What was wrong (measured)
- Dim buttons: the mod painted a 75% tint over the whole title strip. DWM draws the
  caption buttons *under* the client area, so the tint covered them (dot red channel
  ~0x5a matched 25% button + 75% tint).
- No hover when maximized: with an 8 px top inset in WM_NCCALCSIZE while maximized,
  DwmDefWindowProc returns FALSE for every WM_NCHITTEST (logged: `hit-max ... 0 0`;
  normal state `1 9`). 2.0.58 papered over it by returning HT codes itself, which made
  clicks work but DWM never saw the hover.

## Fix (work\styler-release\...\windhawk-styler.wh.cpp, 2.0.64)
- Title strip painted fully clear (title text and icon kept). Cutting a hole only for the
  buttons left a visible lighter box (screenshot taken, rejected).
- No top inset when maximized; DwmDefWindowProc sees hit tests first; NC mouse-move/hover/
  leave forwarded to DwmDefWindowProc; 2.0.58 release-click handling kept.
- Startup error "Another program is already using the WebView2 data folder" was transient
  leftovers from the previous agent's repeated launches; a clean launch at 9:5x PM worked.

## Verified 2026-10-18 (reports\2026-10-18-styler-caption-buttons\)
- 02-normal / 02-normal-full: bright dots, clean strip.
- 03-normal-hover-max: hover glyph + snap layouts.
- 05-maximized-hover-max, 06-maximized-hover-close: hover glyphs while maximized.
- Real mouse click on restore while maximized: window restored (zoomed=False).
- Loaded module: local@windhawk-styler_2.0.64_1.dll (hash 17F884...6EB8).

## Rollback
Elevated: `scripts\2026-10-18-styler-2.0.59-deploy.ps1 -Rollback` (restores 2.0.58 key + ModsSource
from backups\2026-10-18\styler-2.0.59\).
