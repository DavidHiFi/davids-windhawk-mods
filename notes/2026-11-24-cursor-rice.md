# Cursor rice: Mocha base fill, blue to mauve edge (2026-11-24)

## Audit (before)
- Scheme `Catppuccin-Mocha-Dark-Cursors` (niivu port, 2022). Fill was Mocha mantle `#181825`
  (24,24,37), darker than base. Edge was plain text `#CDD6F4`. Spinners lavender. Sizes 32/48/64.
- Leftover keys from older themes stay untouched: `precisionhair` (Gemstone), `Grab`, `Pan`,
  `Grabbing`, `Zoom-in`, `Zoom-out` (Notwaita). Windows does not read these roles.
- Washout fix `HKCU\Control Panel\Mouse\MouseTrails = -1` still in place.

## Change
- `tools\catppuccin-cur\build-mocha.py` renders the 15 Windows roles from upstream
  catppuccin/cursors SVGs (same shapes as before): fill `#1E1E2E`, edge a blue `#89B4FA` to
  mauve `#CBA6F7` gradient (top-left to bottom-right), busy and working spinners the same
  gradient. Unavailable badge stays red. Sizes 32/48/64/96/128; animated frames 32/48/64/96
  (user32 refuses an .ani once a frame passes about 128 KB). Spin speed unchanged (12 frames, 1/6 s).
- Also rebuilt the ten chromium-cursor-remap files with the same edge, overwritten in place in
  `C:\WINDOWS\Cursors\Catppuccin-Mocha-Dark-Cursors\chromium\` (mod settings unchanged; each
  browser process picks them up when it next loads them).
- New folder `C:\WINDOWS\Cursors\Catppuccin-Mocha-Seamless-Cursors`, scheme entry of the same
  name in `HKCU\Control Panel\Cursors\Schemes`, 15 role values repointed, applied live.
- Script: `scripts\2026-11-24-cursor-rice.ps1 -Install` (run elevated from `C:\Users\Public`;
  the elevated run exits 1 after the work with an empty log, the effect was verified instead).

## Evidence
- Live system cursors via `LoadCursorW(NULL, IDC_*)` sample fill (30,30,46) on arrow, wait,
  hand, no, appstarting (`tools\catppuccin-cur\livecheck.py`, `reports\2026-11-24-cursor-rice\live.png`).
- Every file loads through `LoadImageW`. Before and after montage, arrow zoom, spinner GIFs:
  `reports\2026-11-24-cursor-rice\`.

## Shapes, option 1 (later the same day)
- Owner picked option 1: same shapes, thicker edge on the filled ones, one smooth spinner arc.
- `build-mocha.py`: `thicken()` strokes each inner fill with the ring colour (EDGE_W 1.2), so the
  edge grows inward and hotspots stay put; only the `THICKEN` set (arrow, hand, help, pencil, no,
  spinners). Thin shapes (I-beam, crosshair, resize) would lose their dark core, so they stay.
- Spinner: base disc with the gradient edge, a surface0 track, one 140 degree round-capped
  gradient arc turning 30 degrees a frame. Built into `out-mocha2`; previews `shape-32px.png`,
  `spinner-strip.png`, `now-*/new-*.gif` in `reports\2026-11-24-cursor-rice\`.
- Went live as part of the theme rename: `2026-11-24-davidhifi-theme.md`. The cursors now live in
  the Theme Tool Plus pack folder, not `C:\WINDOWS\Cursors`.

## Rollback
- Elevated: `scripts\2026-11-24-cursor-rice.ps1 -Rollback` imports
  `backups\2026-11-24-cursor-rice\cursors-before.reg` and restores `chromium-before\`.
- Or pick `Catppuccin-Mocha-Dark-Cursors` in Mouse pointer settings (that dialog's Apply resets
  MouseTrails; rerun `Fix-CursorWashout.ps1` after).
