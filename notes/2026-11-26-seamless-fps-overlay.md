# Seamless FPS Overlay 1.1.0

2026-11-26. Mod `local@seamless-fps-overlay`, Tools category, elevated tool mod.
Work folder: `work\2026-11-26-fps-suite\overlay\` (STATE.md has the step log). Report: `work\2026-11-26-fps-suite\reports\overlay.md`.

## What changed from 1.0.0

- The Benchmark preset is now the default and is rebuilt to look like the owner's RivaTuner layout
  ("TM Benchmark 2"): CPU and GPU cards, a GPU card picture with three fans that spin with the real
  fan reading, rings with flames, a power bolt, gauges, thermometers, core bars, a RAM stick, a
  binary code strip and a frame time graph. All drawn as our own shapes, none of the .ovl art.
- Mocha colours, blue to mauve gradient (can be flipped), rounded corners with a radius setting,
  2 px edges on the live radius, crisp text.
- 164 settings over 10 pages, common ones first: each block can be shown, moved to the other column,
  reordered, resized and recoloured; every label can be renamed; warning levels; graph style, length
  and height; animation on/off and frame rate; show and hide animate with their own switch and follow
  the shared Motion speed.
- Animations run on their own timer only while the overlay is shown and animations are on.
- Readings come from the sensor core. No HWiNFO shared memory: neither build holds the name.

## Rebuild record

- Source parts: `overlay\src\core.cpp` (backups `.bak-20261126-0735`, `-1000`, `-e5`, `-edge`),
  `overlay\spec.py`, `overlay\gen.py`, `overlay\assemble.py`.
- Installed from 1.0.0 (source hash ae1e6898...0fffd4) through `Install-StagedMod.ps1`.

## Not possible or open

- A live RivaTuner reference shot: RivaTuner's on-screen display slot is empty while a game is in
  front (Overlay Editor feeds nothing), so it draws nothing. Turning it on would change RivaTuner's
  settings, which was not allowed. The side-by-side uses a still rebuilt from the layout file.
- Test PC was held by another thread past the 10 minute wait, so 1.1.0 went straight to the tower.
- Latency and "limited by CPU/GPU" readings are not available, so they show a dash.
- Installed 10:52, published (mods 07f0294, feed 44fc1a7). At 12:21 the mod's process was gone with
  no crash record; a settings stamp brought it back at 12:21:04. Live proofs and any 1.1.1 fix moved to
  the "Fix and prove rebuilt FPS Overlay" thread. No cost numbers or live captures from this thread.

## 1.1.2 (19:40) and live proof (20:25)

- 1.1.2: labels no longer run into values; RAM speed, clock and driver are filled in when Seamless
  Taskbar 0.4.65 publishes the older readings block. Installed, on, published (mods 9c1c457, feed 6faa5d1).
- Live proof passed: corners, layouts, on/off key, next-layout key, moving parts clip, settings restored.
  Pictures and clips in `work\2026-11-26-fps-suite\reports\media\`.
- Cost: shown with animations 1 % of the machine (about 16 % of one core), animations off 0.17 %,
  hidden 0.02 %, 80 MB. RivaTuner + HWiNFO + Afterburner used about 33 % of one core and 52 MB.
- Trap: the on/off key state is not saved. A test that ends with the overlay switched off makes every
  later shot empty. The proof script now switches it on first.
- RivaTuner is uninstalled; 3 locked files clear at the next restart. HWiNFO is uninstalled.
  Afterburner stays (fan curve).

## 1.1.3 (21:25) and live proof (22:03): one panel

- Owner asked again for one panel, not separate floating boxes: no gaps, columns level, thin lines between sections.
- New setting "Boxes": One panel (default) or Separate boxes. One panel: no gaps, a 1px #45475A line between
  sections and between the two columns, and the shorter column spreads its spare room so both end level.
- Gates: settings in sync, glass ok, consistency clean. Installed with Install-StagedMod.ps1, published (mods 3a68fa4, feed 458e291).
- Live proof on the side screen at 100% and 200% size, solid fill, bottom right corner, plus separate boxes.
  Pictures: work\2026-11-26-fps-suite\reports\media\overlay-one-panel*.png.
- Rule added: AGENTS.md Conventions, and rice defects 97 (synced). Backups beside each file, .bak-20261126-2058.
- Proof needs: python without -I (psutil), and the out folder made first.
- Undo: Boxes setting to Separate boxes, or roll back to 1.1.2 from the mods repo.
