# Windhawk Styler 2.0.66: real blur for the window, save bar and cards (2026-10-24)

## What the user saw

- The Windhawk window background looked like a flat color, and the title bar looked different from the body.
- The floating "Save settings" bar only lowered its opacity: text behind it stayed readable.
- The darker page cards showed no blur.

## Causes (measured)

1. `titleBarAcrylic` was off (0). With it off the window got DWMSBT_TRANSIENTWINDOW plus an accent policy with a 0x10 tint. That rendered flat: `work\2026-10-24-windhawk-blur\live-before.png`, strip and body stddev 0.
2. With `titleBarAcrylic` on, the body got acrylic, but the CSS veil (`body` at 75% background) covered only the body. The clear caption strip showed raw acrylic and read lighter (strip 71,71,88 vs body 40,40,56, `live-after1c.png`).
3. Test windows on this build (`accent-test4.ps1`, 11:30 AM): DWMSBT_TRANSIENTWINDOW alone gives a flat 84,84,84 fill, and an accent policy without a blur region gives the flat tint. The recipe Translucent Windows Plus uses, `DwmEnableBlurBehindWindow` with an empty region plus `ACCENT_ENABLE_ACRYLICBLURBEHIND`, gives a real blur (stddev 9.1 over a busy background, `g-twp.png`). Caption and body come out as one sheet.
4. Save bar: every `.ant-card` had `backdrop-filter`. The mod page card then becomes the backdrop root for the sticky save bar inside it, so the bar could only blur the card's own (empty) backdrop. Headless probe: `v1-*.png` and `v2-*.png` blur the text once the in-flow cards drop the filter.
5. Cards: 75% card color over the 75% veil is about 94% opaque in total, so almost nothing showed through.

## Change (2.0.66)

- `ApplyWindowStack`: system backdrop type set to NONE. Every mode sets an empty blur region. Acrylic uses `ACCENT_ENABLE_ACRYLICBLURBEHIND` with the background color and opacity as the accent tint, so DWM tints strip and body together. The `DwmSetWindowAttribute` hook now pins the backdrop type to NONE.
- `CssVeil` is transparent in Acrylic mode. The tint lives in DWM now.
- `backdrop-filter: blur(16px)` applies only to floating surfaces (`kFloatingSurfaces`): save bar, modals, drawers, popovers, dropdowns, tooltips, notifications.
- Setting `cardOpacity` changed from 75 to 40 so cards stay darker but show the blur.

Source: `work\styler-release\mods\local\windhawk-styler\windhawk-styler.wh.cpp`. Build: `.tmp\styler-2.0.66`, 64-bit SHA256 86101CB1…C766.

## Deploy and rollback

- Deploy: `scripts\2026-10-24-styler-2.0.66-deploy.ps1 -Install` (elevated). Read back 11:35 AM: LibraryFileName `local@windhawk-styler_2.0.66_1.dll`, Version 2.0.66, cardOpacity 40, and the installed DLL hash matches the build.
- Rollback: `scripts\2026-10-24-styler-2.0.66-deploy.ps1 -Rollback` (elevated). It restores `backups\2026-10-24\styler-blur\mod-key-before-2.0.66.reg` and `ModsSource-before-2.0.66.wh.cpp`. The source backup is also at `backups\2026-10-24\styler-blur\local@windhawk-styler-2.0.65.wh.cpp`.
- The earlier `titleBarAcrylic` 0 to 1 change: `scripts\2026-10-24-styler-blur.ps1 -Rollback`.

## Save bar follow-up (2.0.67, 2.0.68)

Cause #4 was wrong for the live window. Live CDP checks after 2.0.66 (12:00 PM) showed the bar computing `blur(16px)` while the settings text under it stayed sharp (`work\2026-10-24-windhawk-blur\live-savebar-ab.png`). No ancestor sets a backdrop-root property (`live_roots.py`). A test box inside the settings scroller blurs the text only when the scroller gets an opaque background: `exp-scrolltest.png` (transparent, text sharp) vs `exp-scrolltest-opaque.png` (opaque, text blurred), 12:12 PM. In Acrylic mode the page is transparent down to DWM, so the renderer leaves the text sharp.

Fix: floating surfaces keep at least 92% of the card color under the blur. 2.0.67 used 85%, which still left a readable ghost. Deploy: `scripts\2026-10-24-styler-2.0.68-deploy.ps1 -Install` (elevated). Rollback to 2.0.67: the same script with `-Rollback`. The 2.0.67 script's `-Rollback` goes back to 2.0.66.

## Live verification (12:15 PM, over CDP, offline)

- Measured: registry LibraryFileName `local@windhawk-styler_2.0.68_1.dll`, installed 64-bit DLL hash 9B3348DA…C511 equals the build.
- Measured: save bar computed background `rgba(24, 24, 37, 0.92)`, backdrop `blur(16px)`. Text under it is a faint ghost (`live-v68-savebar.png`).
- Measured earlier: caption strip and body match (27,27,38 vs 28,28,39).
- Not checked: the real-desktop blur behind the window on screen. The user was in a fullscreen RustDesk session, so no desktop tests ran. Cards at 40% show whatever DWM paints behind them.

## True save-bar blur (2.0.69) and dialog seam merge (2.0.70), 12:20 PM to 12:30 PM

- Cause recap: the renderer blurs text only over an opaque backdrop. Test (`work\2026-10-24-windhawk-blur\live_band.py`, `band-D.png` vs `band-E.png`): an opaque strip on the settings scroller, only where the sticky bar sits, makes the rows behind a 40% bar blur; without it they stay readable.
- 2.0.69: `.ant-card-body.wh-cscroll-host:has(SaveSettingsCard)` paints an opaque rounded patch in the card color exactly under the bar (12px inset, top 12px, 56px tall, 16px radius; background layers stay pinned to the scroll viewport). The bar drops the 92% floor and uses the normal card opacity (40). Modals and popovers keep the 92% floor. Emitted only when an accent is set, because the bar geometry comes from the accent block. Geometry measured live: `live_geom.py`.
- 2.0.70: the seam rule from the dialog-fix thread, with `!important` so it beats the global 16px radii. The user's original complaint was "two boxes, not one", so squaring was taken as answered. The scrollbar blocks were not merged: the styler's own scrollbars already cover them.
- Measured 12:28 PM over CDP, no injection: bar `rgba(24, 24, 37, 0.4)` + `blur(16px)`, rows behind blurred (`live-v70-savebar.png`); seam gap -1px, radii 0 (`seam-v70.png`). Registry LibraryFileName `local@windhawk-styler_2.0.70_1.dll`, installed 64-bit hash 16EA38FB…6220 equals `.tmp\styler-2.0.70`.
- Commits in `work\styler-release`: ba04eec (2.0.69), 744038c (2.0.70). Not pushed.
- Rollback: `scripts\2026-10-24-styler-2.0.70-deploy.ps1 -Rollback` goes to 2.0.69; the 2.0.69 script's `-Rollback` goes to 2.0.68.
- Seen once: after the 2.0.70 reload the page came up with an empty `#root` (app not mounted, no styler style). A CDP `page.reload()` fixed it with no console errors. Likely a race between the reload and a CDP script navigating. If the UI shows blank after a deploy, reload the page.
- Proof collage: `reports\2026-10-24-styler-blur\2026-10-24-styler-2.0.70-proof.png`.
