# start-everything-plus 1.1.0 — upstream 1.1 sync (2026-10-11)

Task: the original `start-everything` mod by bardelyne shipped v1.1 today (PR
ramensoftware/windhawk-mods#5986). Merged it into our fork and reinstalled.

## What 1.1 brings (now in the fork)

- File preview card on results (with `filePreview` / `animatePreview` settings)
- Drag & drop from results (always copies, never moves)
- **Uninstall** entry in the results right-click menu
- Calculator / unit conversion without the `/c` prefix (`2^10`, `100 km`,
  `100 km to mi`, `255 hex`), plus Reciprocal
- New settings: **panelMargin** (Search Panel Margin, default 0 = edge-to-edge)
  and **textScale** (Text Size %)
- Everything 1.5a / named-instance support; website shortcuts no longer shown
  as web searches

## Fork deltas re-applied over the 1.1 base

- Adaptive compact view: `SetSearchFrameSize()` (idle 160 / searching 500,
  `g_adaptiveBody` collapse, `g_resultsHost` 64px + top align), 9 call sites,
  `RestoreSearchFrameSize()` in `TeardownStartMenuUi`, layout debug logger
- Instant hide (no fade) via opacity 1.0 / `IsHitTestVisible(true)` swaps
- DavidHiFi identity: id `start-everything-plus`, name "…Plus", author,
  fork README updated for the 1.1 feature set

## Build & install

- Compiled with the Windhawk-bundled clang++ (`-std=c++23`, x64, `-DWH_MOD`),
  linked against the **alpha-7** engine import lib
  (`Engine\2.0.0_1\64\windhawk.lib`) — the alpha-7 update landed mid-task and
  replaced the old `2.0.0` engine folder, so the first build was redone.
- `scripts\2026-10-11-start-everything-plus-1.1.0.ps1` (`-Build`, `-Install`,
  `-Audit`, `-Rollback`); DLL `…_1.1.0_710105.dll` sha256
  `9909BEFE…F2944E4B`, 1,930,752 bytes.
- Installed via the silent elevated child: DLL → `Engine\Mods\64\`, source →
  `ModsSource\`, registry Version/LibraryFileName updated,
  `SettingsChangeTime` bumped for a hot reload. No engine or Explorer restart.
- Backup (pre-change): `backups\2026-10-11\start-everything-plus\` (old DLL,
  old source, `mod-settings.reg`). Rollback: `-Rollback` restores 1.0.4.

## Verification

- Registry readback: Version 1.1.0, LibraryFileName → 710105, Disabled 0. ✔
- Module check: 1.1.0 loaded in **StartMenuExperienceHost** and **explorer**.
  SearchHost still maps 1.0.4 — the suspended host defers the reload until its
  next activation; expected, no action needed.
- Windhawk UI shows "Everything & Power Tools in the Start Menu Plus 1.1.0"
  enabled (`reports\2026-10-11-start-everything-sync\probe-screen.png`).
- **Visual check pending**: the Start menu has not been opened since the new
  DLL loaded, and other threads' windows were on the desktop, so no synthetic
  keys were sent. Owner: press Win, confirm the compact idle view, type to
  expand, Esc to collapse. If anything is off, run `-Rollback`.

Engine context: Windhawk was updated to 2.0.0-alpha.7 by another thread during
this task (T3 stayed up; Explorer restarted once at 11:20, unrelated to us).
The fork compiled/loads fine on alpha 7.

Receipt: `reports\2026-10-11-start-everything-sync\install-receipt.json`.
Upstream mirror `mods\catalog\start-everything.wh.cpp` refreshed to 1.1.

## Follow-up: acrylic outline clipped at the bottom (rev 710106)

Owner-reported after first look (2026-10-11): the idle compact view showed a
1px stroke around the frame that lost its bottom rounded corners — cut off
mid-radius. Cause: 1.1's `SyncOverlayBackground()` now draws the stock
`AcrylicBorder` look on the search surface, and that stock element keeps its
own taller geometry inside our forced 160px compact frame, so its stroke
bottom fell outside the clip.

Fix in `SetSearchFrameSize()`: capture the acrylic border's original
Height/MinHeight/Margin once, clamp it to the compact frame (MinHeight 0,
Height 160, Margin 0) while compact, restore stock geometry when expanded,
and restore again in `RestoreSearchFrameSize()`. Rebuilt and installed as
revision `…_1.1.0_710106.dll` (sha256 `504206A6…95BF947`); 710105 stayed
mapped in SearchHost and is superseded — the registry points at 710106,
which StartMenuExperienceHost and explorer loaded.

## Fix that stuck: strip the mod's own copied surface (rev 710107)

Owner verdict on 710106: it cut off the entire menu at the bottom. The
clamp forced a Height on the stock `AcrylicBorder`, which hosts the menu
content — so the content got clipped, not just the stroke. Registry was
reverted to 710105; the clamp commit `c8a6a55` stayed on main.

Re-diagnosis: the visible stroke was not (only) the stock acrylic. 1.1's
`SyncOverlayBackground()` copies the acrylic's BorderBrush/BorderThickness
onto the mod's own `g_resultsHost`, and that copy sat exactly on the
compact frame's clip boundary — bottom edge invisible, corner arcs chopped
mid-curve, i.e. the hooks.

Fix (working copy, installed as `…_1.1.0_710107.dll`, 1,943,040 bytes):
`g_searchFrameCompact` flag, set in `SetSearchFrameSize()` and cleared in
`RestoreSearchFrameSize()`; while compact, `g_resultsHost` gets
`Background(nullptr)` + zero `BorderThickness`, and
`SyncOverlayBackground()` re-strips instead of re-copying. The search area
rides directly on Start's own acrylic, like the footer below it. Expanded
searching restores the stock panel look. A one-shot `LogCompactSurfaces()`
dump (borders + acrylic ancestry → `local@start-everything-plus-layout.log`)
runs on every compact transition, so any surviving outline traces to its
exact element. The 710106 clamp code is fully removed (revert of `c8a6a55`
is part of the published commit).

Install: hot reload only, confirmed mapped in explorer +
StartMenuExperienceHost. Owner visually approved ("that looks great").

Follow-up note: once a revision is mapped by the hosts, its DLL on disk is
locked — the `-Install` script path (which overwrites the same filename)
fails with "being used by another process". Refresh comment-only source
changes with a source-only elevated copy (hash-verified), no stamp, no
reload. Any new binary needs a new revision filename.

## Description + repo refresh (same day)

- `@description` → "Compact Start menu search with Everything, preview,
  apps, settings, power tools" (79 chars, style-guide clean).
- New feature bullet in both readmes (embedded + standalone): "Seamless
  idle view. The compact search box sits directly on the menu's own
  background with no extra outline."
- `manifest.json`: `local@start-everything-plus` 1.0.4 → 1.1.0.
- Root `README.md` table cell aligned with the new description;
  `mods/README.md` gained the missing start-everything-plus row (1.1.0,
  GPL-3.0).
- Preview: refreshed in commit `3ed7138` from the owner's screenshot of
  the fixed idle view (780x169, same tight framing; capture cursor
  removed over flat background, verified invisible at 4x). Expanded
  preview `start-everything-plus.png` unchanged.
