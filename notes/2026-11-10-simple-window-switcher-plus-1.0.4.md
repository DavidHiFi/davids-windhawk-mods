# Simple Window Switcher Plus 1.0.4 (2026-11-10)

Owner asked: audit, Mocha blue-to-mauve gradient border around every Alt+Tab window, title
pill ("the dock at the bottom") filled solid Mocha base with a gradient border that lights
up on hover.

## Changes

- New `CardBorder` group: gradient edge on every Vista card, `#89B4FA` top-left to
  `#CBA6F7` bottom-right, 2 px, other windows at 40%, the selected one at 100%. It follows
  the rounded corners in perspective (same path as the old selection outline).
- Pill: fill `#1E1E2E` at 100%, text `#CDD6F4`, border 2 px gradient `#89B4FA` to
  `#CBA6F7`, 45% at rest, 100% while the pointer is over the pill (eased, about 0.2 s).
  New settings `TitlePill.borderColorEnd`, `TitlePill.hoverBorderOpacity`.
- Close X hover: Mocha red `#F38BA8` with crust ink (was Windows red with white).
- Placeholder cards (minimized windows, first frame): Mocha base with a surface1 hairline
  (was grey with a white hairline).

## Audit findings

- Fixed: in Flip 3D, Cascade and the other stacked layouts the selection outline never drew;
  only the grid layouts set `highlight`. Cards now carry a `focus` value from their slot.
- Fixed: the pill ran a full Gaussian blur every frame under a solid fill. Skipped when the
  fill is 100%.
- Fixed: placeholder and close-button colours were off-palette.
- Cost: one path geometry per visible card per frame (was one). Small next to the effect
  chains; no hitch seen in the build or install.
- Left alone: the Simple layout, all other settings.

## Settings changed (owner's live values)

Old: tintColor `#1C1C1E`, tintOpacity 45, textColor `#FFFFFF`, borderColor `#FFFFFF`,
borderOpacity 18, borderWidth 1. New: as above, plus the CardBorder group.

## Install and rollback

- Offline build first: `scripts\2026-11-10-swsp-build.ps1` (64 and 32 bit OK, Idle priority).
- Install: `scripts\2026-11-10-swsp-install.ps1 -Install` elevated (copies source, writes the
  look settings, `windhawk-cli mod compile`).
- Rollback: same script `-Rollback` (restores the 1.0.3 source and the settings export in
  `backups\2026-11-10\swsp`, recompiles).

## Evidence

- 9:48 pm: compile exit 0, registry Version 1.0.4. All 10 Explorer processes and both
  Windhawk host processes load `..._1.0.4_839506.dll`. Explorer PIDs unchanged, no
  application crash events.
- Live look, 10:04 pm capture of the main screen (Alt+Tab, two flips, Escape): every Flip 3D
  card has the gradient edge (front card samples #939EBD left, #B1ABD9 right, blue into
  mauve). Pill fill samples #1F1E2D to #211E2F (Mocha base, video-compressed), border
  gradient at rest opacity. Files: work6-11-10-swsp\swsp-live.mp4, .gif, still-*.png.
- A window menu seen top-left in the clip was not left open: no popup menu on screen at 1:40 am.
- Unverified: pill hover. Checking it needs the pointer moved over the pill while
  Alt+Tab is open, and agents may not move the owner's cursor.

## 2026-11-11 1:43 am: darker glass pill (owner request)

Border kept. Fill made darker and glassy, house dock recipe, settings only (live, no compile):
- Old: tintColor `#1E1E2E`, tintOpacity 100 (blur skipped), blur 30, noise 3.
- New: tintColor `#11111B` (crust), tintOpacity 70 (blur runs again), blur 30, noise 4.
- Script `scripts\2026-11-11-swsp-pill-glass.ps1`; rollback `-Rollback` (export in
  `backups\2026-11-11\swsp\settings.bak-20261111-0150.reg`).
- Check, 1:46 am, left screen (Alt+Tab opens on the screen in use): pill samples `#191829`,
  darker than before (`#1F1E2D`), gradient border unchanged. No crash events.
- Capture script now takes `--out N` for the screen; the pointer was on screen 3.
