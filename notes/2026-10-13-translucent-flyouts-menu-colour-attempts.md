# Translucent Flyouts: menu colour and blur attempts (2026-10-13)

Thread 55f21ec1. Goal: menus with a real blur and the Catppuccin Mocha base colour (#1E1E2E), with a thin #89B4FA outline.

## Live state now

- `local@translucent-flyouts` 0.6.16, `LibraryFileName=local@translucent-flyouts_0.6.16_1.dll`, source matches `backups\2026-10-13\translucent-flyouts-0.6.17\local@translucent-flyouts.wh.cpp.0.6.16`.
- `menu.effectType = modern_acrylic`, `menu.darkModeGradientColor` and `menu.lightModeGradientColor` = `0xCC1E1E2E` (Mocha at 80%). Global keys unchanged.
- Measured on the desktop menu (`reports\2026-10-13-translucent-flyouts-0.6.17\probe-0.6.17.ps1`): body about #2D2E40 to #48495A, outline #89B4FA on all four edges, rounded corners clean. The body is lighter than the base and carries the wallpaper blur.

## Ruled out (measured)

| Build | Idea | Result |
| --- | --- | --- |
| 0.6.19 to 0.6.21 | Paint the Mocha tint into the menu body with alpha (FillRect alpha brush, AlphaBlend, direct DIB write) | Never visible. GDI leaves the surface alpha at zero, which DWM shows as transparent. The menu DC is a device bitmap, not a DIB section (`[tint] direct=0`). |
| 0.6.22 | Layer the menu window (WS_EX_LAYERED, LWA_ALPHA = tint alpha) with DWM blur-behind | Menu content disappeared. Only the wallpaper and blur showed. |
| 0.6.23 | Solid accent with the Mocha colour plus DWM blur-behind | Flat light blue (#A9D4FF). Not Mocha, not blurred. |
| experiment | Solid accent, Mocha at 85% (no blur) | Body about #3E3E4E. Not #1E1E2E. |
| experiment | Solid accent, Mocha opaque (FF) | Body still about #3E3E4E. A lighter layer sits over the accent; not identified. |
| 0.6.17 era | Blurred (BLURBEHIND) | Neutral grey (about #252526). The tint is ignored. |
| 0.6.17 era | Modern acrylic with Mocha at any alpha | Lightened. Acrylic adds a luminosity layer, so a dark tint can't reach the base. |

Accent-tint zero (neutral acrylic underlay) measured about #2A2F48 to #464A5F on the dark side, so the underlay alone is lighter than the base too.

Build and source archive: `Windhawk\translucency-flyouts\build-0.6.17` to `build-0.6.23`; the last experiment source is `backups\2026-10-13\translucent-flyouts-0.6.17\src-0.6.23-experiment`. Install and rollback scripts: `scripts\2026-10-13-translucent-flyouts-0.6.17.ps1` to `0.6.23.ps1`. Rollback to 0.6.16: `scripts\2026-10-13-translucent-flyouts-0.6.17.ps1 -Rollback`, run through `Invoke-Elevated.ps1`. Settings baseline: `backups\2026-10-13\translucent-flyouts-0.6.17\settings-pre-0.6.17.reg`.

## Options

1. Keep blur, accept a lighter body: stay on 0.6.16 modern acrylic with Mocha at 80% (the live state). A higher alpha moves it closer to the base and cuts the blur.
2. Exact-looking Mocha, no blur: solid accent, Mocha opaque. Clean and flat, but the body still reads lighter than the base in this build, and there is no blur.
3. Real fix: draw the menu body with DirectComposition, or use a pre-blurred capture of the desktop behind the menu with Mocha drawn over it. This gives both blur and exact colour, and is a new rendering path that needs its own build and test.

Recommendation: option 3 if both matter; option 1 if the blur matters more than the exact colour.

Public repo: `DavidHiFi/davids-windhawk-mods` main still holds 0.6.16 (PR #10). Nothing new was pushed or opened.
