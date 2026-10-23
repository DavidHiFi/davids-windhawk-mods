# 2026-10-08 — Styler rev 19: the frame veil, the stray border, and a blank-renderer scare

## The complaint
"Still that weird box going off the side of the title bar, and the acrylicness isn't
properly being implemented." (dictated; "tidal bar" = title bar)

## What was actually wrong (three defects, one cluster)
1. **Raw frame zones.** The window's invisible resize borders (~8 px left/right/bottom)
   are non-client area the page can never paint. They showed raw system acrylic — no
   veil — so their tone tracked the wallpaper behind the window. Over today's
   near-black wallpaper that read as a dark band down the right edge ("acrylicness
   isn't properly being implemented").
2. **Stray accent line.** The app paints a 1 px border at its page edges for the
   frameless (custom) look. In native mode the page is the client, inset 8 px, so the
   line sat at x=7 / x=1092 down the full height, next to the scrollbar thumb —
   the "weird box going off the side of the title bar".
3. **Scroll-lag thumb.** A (65,65,74) 10×28 px box at the client's top-right:
   the mod-list's overlay scrollbar thumb, visible after render, fades when idle.
   Legitimate UI; it only read as a glitch next to defects 1–2.

## The blank-renderer scare (independent of the above)
At ~8:50 AM the live window (pid 9644) rendered nothing at all — CopyFromScreen over
its rect caught pure wallpaper. Not iconic, not cloaked, Responding=True, no
Application-log crash events. A restart (settings flip) restored it. Cause unknown,
one-off so far. If it recurs: check GPU/driver events and the Electron renderer.

## Fixes (rev 19, `local@windhawk-styler_1.5.0_19_{64,32}.dll`)
Source: `work\windhawk-styler\native-v15\windhawk-styler.wh.cpp`
- **Veil popup covers the whole window rect** (was caption strip only). Surface:
  side columns and the bottom band flatten **opaque** to the veil color (raw glass
  there tracks the wallpaper and always reads as a band next to the near-constant
  client (29,29,45)); the caption band's middle keeps the alpha veil over glass;
  the client middle stays transparent so nothing double-tints; all four corners bake
  the DWMWCP_ROUND radius (bottom corners added). Maximized windows keep the
  strip-only behavior.
- **Class registration tolerates ERROR_CLASS_ALREADY_EXISTS** — an in-place engine
  reload re-registers the same class name in the tool process; the old code recorded
  the failure in a function-local static and never created popups again. That was
  the "flaky popup" mechanism.
- **`html,body{border:0!important}`** added to the native-mode workbench CSS patch —
  the stray accent line is gone from native mode (custom mode keeps its border).

## Verified (same session, animated-wallpaper-safe: flips restart the window)
- Edges: left/right at y=304 and y=600, bottom at x=550 — body (29,29,45) →
  frame zone (30,30,46), 1 RGB unit. No line (x1092 was (137,180,250) on rev 18).
- Corners TL/TR/BL/BR at 5×: rounded, clean, no square stubs, no bands.
- Strip y=15: frame columns (30,30,46), client (26,26,41) — the v15-verified look.
- BACKDROP attr 38 = 3 (DWM acrylic) on the live window.
- Veil popup (class `WindhawkStylerVeil`, empty title — match by CLASS, not title):
  (1308,360)-(2408,1120) full-height, visible. Custom mode: unchanged by rev 19
  (popup is native+blur only; border kill is native-only).

## End state
- Registry `nativeTitleBar=1` (the user's setting), LibraryFileName=_19,
  tool pid 21104, window healthy.
- Captures: `reports\2026-10-08-native-vs-custom\` (native-full, custom-full,
  native-strip-1x, native-rightedge-2x, native-{tl,tr,bl,br}-5x — all 10:22–10:23).
- Delivered as 8 real T3 thread attachments (second delivery; the first batch's
  route is now standard in global.md).
- Scripts: `scripts\2026-10-08-styler-live-diag.ps1` (rect+margin+scans+shimmer),
  `scripts\2026-10-08-styler-health-check.ps1` (fix the popup finder to class-based),
  `scripts\2026-10-08-styler-worker-probe.ps1` (class-based popup + DWM attrs),
  `work\windhawk-styler\native-v15\deploy-rev19b.ps1` (disable→copy→enable; the
  DLL locks force this over a plain copy — Copy-Item preserves LastWriteTime, so
  check the hash, not the timestamp).

## Not done / open
- The blank renderer has no diagnosed cause (no event-log trace). One-off so far.
- 1.5.0 remains unpublished to DavidHiFi/davids-windhawk-mods (fork main 1.4.0).
- The 4-unit strip seam (client 26 vs frame 30) persists, same as the v15-verified
  look; a bigger unification would need the client to paint the NC area, which it can't.
