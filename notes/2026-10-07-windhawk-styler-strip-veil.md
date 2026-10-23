# 2026-10-07 — Windhawk Styler 1.4.0: native strip keeps the veil

Follow-up to the morning's 1.3.1 (uniform raw acrylic in native mode). The user
rejected the trade-off: with nativeTitleBar on, the whole window read darker
than custom mode because the page's rgba veil could no longer be painted —
the real DWM caption strip is non-client area no page can touch.

## What ships now

The veil returns in both modes. The page paints it over the body as before,
and a new tool-side mechanism veils the strip:

- The tool process keeps one click-through layered popup per native-mode UI
  window (`WindhawkStylerVeil` class, WS_POPUP owned by the UI window,
  WS_EX_LAYERED|TRANSPARENT|TOOLWINDOW|NOACTIVATE), filled with the background
  color and alpha = backgroundOpacity (LWA_ALPHA), sized to the window width x
  (client top - window top).
- `VeilSync` seats it directly above its owner: insert-after is measured to
  place a window BELOW the handle given, so it inserts after
  `GetWindow(owner, GW_HWNDPREV)`.
- Follow mechanisms: `EVENT_OBJECT_LOCATIONCHANGE` hook (drag tracking, measured
  +40px with zero drift), an `EVENT_SYSTEM_FOREGROUND` hook (z reshuffles on
  app switches — measured that owned windows are NOT kept above their owner),
  and the 1s Worker tick as fallback. `VeilPass` rebuilds all veils when the
  color/opacity/mode key changes and reaps dead pairs.
- With blur=none the old solid-sheet behavior stays (page rgb + solid caption).
- Custom mode: no overlay, untouched rendering (verified: no veil window, frameless).

## Dead ends (all measured this session, do not retry)

- **WCO / titleBarOverlay on this Electron 19 build**: with custom+WCO enabled
  the window keeps a REAL DWM caption AND the HTML titlebar AND an opaque
  overlay box — a hybrid mess. Settings were restored afterwards.
- **Accent on a captioned window**: SetWindowCompositionAttribute changes
  nothing on strip or body, with DWMSBT set or cleared.
- **DWMWA_CAPTION_COLOR**: solid only. Color-matching it to the body seams in
  motion (the acrylic responds to what's behind, the solid does not).

## Measurement trap worth remembering

The desktop wallpaper is animated. Same position captured 30 minutes apart
differed by 10 RGB points; the "native darker than custom" gap seen across
phases was wallpaper drift, not a mode difference. Only same-moment
strip-vs-body comparisons are valid. Final same-moment proof: strip
(24,24,37) vs body (23,23,36).

## Install

`elev/install-140-strip-veil.ps1` (adapted from the 1.3.1 script): captures
settings, disables, waits for the old tool, copies 1.4.0_1 to
Engine\Mods\{64,32}, points LibraryFileName, restores settings, enables,
bumps, restarts, verifies files (main.js inject, veil rgba in css/html,
settings native block) and captures per-mode evidence. Verify file state a
few seconds AFTER the tool pid appears (ApplyFiles race, known trap).

## Evidence

- reports/2026-10-07-native-fix/v140-native-final.png (+ titlebar crop): strip
  and body as one frosted sheet, themed dots on top.
- reports/2026-10-07-native-fix/v140-native-drag.png: veil followed the window.
- reports/2026-10-07-native-fix/v140-custom-full.png: custom unchanged.
- final-verify.log: veil rect/alpha/z + same-moment strip/body on the last
  window instance.

## Rollback

Point LibraryFileName back to `local@windhawk-styler_1.3.1_1.dll`, bump
SettingsChangeTime. The 1.3.1_1 DLLs are still in Engine\Mods\{64,32}.
