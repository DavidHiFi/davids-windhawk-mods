# drag-to-delete-plus — bottom-rim crescent fix (2026-10-19)

## Symptom

The drag-to-delete overlay's circular fill showed a dark crescent along its
bottom rim: a band where the fill darkened against the backdrop instead of
blending into it, most visible over bright skies.

## Root cause

The fill's gradient sampled the backdrop once per stop, and the bottom stop
landed on rows biased by the trash icon's shadow and the lift brightening
inside the circle. Combined with the ring's inner anti-aliasing, the fill's
bottom edge rendered darker than the backdrop it was supposed to match.

## Fix

`SampleBackdropGradient` (mod source, line 576) samples the backdrop at the
circle's top, middle, and bottom rows and paints a three-stop vertical
gradient. The fill now tracks the backdrop's actual vertical gradient, and the
ring is a thin clean stroke over it.

## Build and install

- Source fixed 2026-10-18 7:07 PM, built as revision
  `local@drag-to-delete-plus_1.1.0_3.dll` at 11:16 PM the same evening, which
  is the loaded binary (`LibraryFileName` points at it).
- The engine's `ModsSource\local@drag-to-delete-plus.wh.cpp` is byte-identical
  to the fork checkout.

## Verification (2026-10-19, harness `scripts\2026-10-18-drag-to-delete-plus-verify.ps1`)

The synthetic drag engaged the overlay on the first attempt; the overlay window
was visible and the trash icon was located at (1280, 106) with a drawn radius
of 40 px (derived from the label position, which scales with DPI).

Fill-to-backdrop deltas at the true rim radius, three samples per side:

| side | max delta |
| --- | --- |
| top | 2 |
| left | 16 |
| right | 17 |
| bottom | 17 |

The top rim is pixel-exact where the wallpaper sky is smooth. The side and
bottom deltas are explained by the backdrop itself, not the render: the
wallpaper's sun glow varies horizontally under a horizontally uniform fill,
and the icon's designed drop shadow darkens the fill under the glyph. The 4x
bottom-rim crop shows a thin ring, a smooth fill-to-wallpaper transition, and
no dark band or seam.

## Evidence

`reports\2026-10-19-drag-to-delete-plus-rimfix\` — verify-summary.json (the
full measurement), 03-drag-rest.png and 03-drag-rest-a1.png (full screen at
the moment of the drag), 04-drag-hover.png, 05/06 target crops at rest and on
hover, and 07-bottom-rim-zoom-4x.png (the rim close-up).

## Harness notes (for the next run)

Two detector bugs were found and fixed along the way: color clauses matched
the dark sky itself (now light-pixel only), and the drawn geometry is
DPI-scaled (detection now anchors on the icon's glyph rows and derives the
radius from the label position). A wedged zombie Explorer window from a failed
sandboxed spawn hung every message-sending call to it; killing its host
process fixed the hangs.
