# Windhawk Styler 2.0.54: frozen card, inset ring, rounded scrollbar (2026-10-13)

Owner report: the accent color row showed a rounded edge mid-box, and the page scrollbar and its arrows poked past the rounded corners.

| Symptom | Cause (measured) | Fix |
| --- | --- | --- |
| Rounded edge mid-box beside Accent color | The card's ring is a `::after` pseudo-element. Inside the card's own scroller it scrolls with the content. Its bottom edge sat at 1187px, so at max scroll (641px) it showed at y 697, matching the screenshot. | Frozen card paints its ring as `box-shadow: inset 0 0 0 1px`; the `::after` is hidden on that card |
| Card corners go square on scroll | The page scrolled, so the card moved under the rounded frame | Card is capped at `100vh - 163px` and scrolls inside itself (2.0.52 rule, kept) |
| Arrows and square track at the corners | `scrollbar-width: thin` on `.wh-cscroll-host` and the card made Chromium ignore every `::-webkit-scrollbar` rule | `scrollbar-width` and `scrollbar-color` removed; webkit thumb with radius and track clipped by the card radius; scroll buttons hidden |

Verified live via CDP and window captures (`reports\2026-10-13-styler-polish\bottom-2054.png`, `accent-crop.png`):
the card stays at y=151 while scrolling; no stray ring at max or mid scroll; no scroll arrows; the thumb follows the rounded corner.

Installed: `local@windhawk-styler_2.0.54_160341.dll`. Source committed in `work\styler-release` (not pushed).
Rollback: `scripts\2026-10-13-styler-polish-2054.ps1 -Action Rollback` (to 2.0.53).
Intermediate: 2.0.53 (`scripts\2026-10-13-styler-polish-2053.ps1`) froze the card but kept the arrows, because scrollbar-width was still set.

## 2.0.55: scrollbar thumb past the corner curve

Owner report after 2.0.54: the thumb at the top and bottom still drew square, past the card's 16px corner.
Cause (measured): Chromium paints the scrollbar thumb outside the border-radius clip. Track margin had no effect.
Fix: `clip-path: inset(0 round <cornerRadius>px)` on the frozen mod card only, using the card's own radius.
Verified live: top and bottom corner crops (`reports\2026-10-13-styler-polish\corners-2055.png`) show the thumb following the curve.
Installed: `local@windhawk-styler_2.0.55_160728.dll`. Commit in `work\styler-release`. Rollback: `scripts\2026-10-13-styler-polish-2055.ps1 -Action Rollback` (to 2.0.54).

## 2.0.56: scroller moved inside the card

Owner report after 2.0.55: the scrollbar still protruded at the top-right and bottom-right corners.
Cause: the thumb reaches the card's top and bottom, where the 16px corner curves away. Clipping can trim it but cannot keep it inside.
Fix: the card keeps its header and tabs pinned (flex column, `overflow: hidden`), and `.ant-card-body` is the scroller, inset `margin-inline-end: 8px` and `margin-bottom: 16px`. The thumb never reaches a corner. clip-path was removed.
Verified live with PrintWindow captures (`reports\2026-10-13-styler-polish\pw-top0-corner.png`, `final-corners-2056.png`): top and bottom scroll positions both keep the thumb inside the straight edge.
Installed: `local@windhawk-styler_2.0.56_161935.dll`. Commit in `work\styler-release`. Rollback: `scripts\2026-10-13-styler-polish-2056.ps1 -Action Rollback` (to 2.0.55).
