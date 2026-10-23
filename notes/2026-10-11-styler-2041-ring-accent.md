# Windhawk Styler 2.0.41: shared ring and accent coverage (2026-10-11)

## Symptom (user report, 2026-10-11)

- Box outlines looked inconsistent: gray along the top edge, and the top-left and
  top-right corners went dark.
- The accent was not applied everywhere. The filter area and some Windhawk
  surfaces kept an antd blue instead of the configured accent.

## Root cause (measured on the live UI, 2.0.40)

- `.ant-table` had a 1px `rgba(255,255,255,0.08)` border on a 0.9-alpha fill with
  a 16px radius. Its header cells paint a 3% white overlay on top of the same
  area, so the straight top edge and the arc around each corner did not meet
  the same color.
- The "Installed" mod-card ribbon (`.ant-ribbon`) painted `rgb(23,125,220)`, antd's
  default primary. No Styler rule covered it. Scanning the Explore page for
  saturated colors found it (18 hits). Home and the filter popover showed only the
  accent in their idle state.

## Fix (2.0.41)

- One shared surface list (`kSurfaces`, `kRelativeSurfaces` in the source) for
  cards, tables, collapse panels, dialogs, pop-ups and menus. Each one gets
  `border:0`, the card color, and a single 1px ring painted by `::after` over its
  content (`:is(...)::after`, so every selector in the list gets it). The ring
  follows the radius with `border-radius:inherit`, so the outline is the same
  color around the corners and along the edges.
- Accent coverage added: `.ant-ribbon` (with `.ant-ribbon-corner`),
  `.ant-spin-dot-item`, `.ant-tabs-tab:hover`, selected drop-down items
  (`.ant-dropdown-menu-item-selected`), selected select options and option state,
  and hover on default buttons.
- Version 2.0.40 -> 2.0.41 in the mod header.

## Verification (live UI, CDP port 9333)

- Installed 2.0.41, readback: registry Version `2.0.41`, LibraryFileName
  `local@windhawk-styler_2.0.41_211145.dll`, SettingsChangeTime `1791724305`.
  DLL SHA256 `52BAFDA3AD8C71389C9B523B5F65C054E23D7DE3292B8C3BC2ED6C6AA789CE43`.
  Installed source SHA256 equals the repo file `7377E868...FE854D`.
- Live style block: 10,520 chars, with the `:is(` ring rule and the ribbon rule.
  `.ant-table` border `0px`, `::after` ring `1px rgba(255,255,255,0.08)`, radius
  16px on both the table and the ring.
- Corners (12x crops of the captured window, `scripts\2026-10-11-styler-crop.ps1`):
  top-left and top-right arcs show one continuous 1px gray ring that matches the
  straight top edge. No dark notch.
- Explore page: no stray default blue (scan of every visible element); ribbon
  background `rgb(137,180,250)`.
- Filter popover: ring 1px, radius 16px, card surface. Selecting "Enabled mods"
  gives selected text `rgb(137,180,250)` on `rgba(137,180,250,0.16)`; the filter
  was cleared afterwards.

## Tools added

- `scripts\2026-10-11-styler-capture.ps1`: captures the Windhawk window with
  PrintWindow, so other windows stacked on top stay out of the picture and
  nothing is foregrounded.
- `scripts\2026-10-11-styler-crop.ps1`: crops and enlarges a region with
  nearest-neighbour scaling.
- `scripts\2026-10-11-styler-build-2041.ps1` and
  `scripts\2026-10-11-styler-ring-accent-2041.ps1` (Audit / Install / Rollback).
  Backups and receipt: `backups\2026-10-11\styler-ring-accent-2041\`.

## 2.0.42 (same day): cleanup, readme, install and commit

- `focus` computed once at the top of `BuildCss`; unused `hover` local removed;
  readme wording for the outline and wider accent in the source and
  `mods\local\windhawk-styler\README.md`. No CSS output change from 2.0.41.
- Installed: `local@windhawk-styler_2.0.42_211443.dll`, DLL SHA256
  `3B66C73B...A202694`, installed source SHA256 `772DA637...1AA509` (equal to the
  repo file). Registry readback Version `2.0.42`, SettingsChangeTime `1791724483`.
  The running UI loads that DLL (module list), and the live style block carries
  the ring rule. Backup and receipt: `backups\2026-10-11\styler-ring-accent-2042\`.
- Commits: release `a13f1bd` on `styler-tauri-release`; `main` `dfe2d56`
  (blob `415d662`, equal on both). Not pushed. Only the two Styler files were
  committed; the taskbar-audio-visualizer edits in the main checkout stay
  uncommitted and untouched.

## Native review and 2.0.43

Read-only review of lines 498-1753 by a DeepSeek-harness worker (`dsh_halo_glm`,
model `["halo-sparks","glm-5.3-flash"]`, task `styler-2041-native-audit-r2`).
Each finding was checked against the code before any change. Result:

| # | Finding | Disposition |
|---|---------|-------------|
| 1 | Fifth cave stub written past the tail padding | Fixed: capacity = tail / 32 |
| 2 | Unload waits 6 s; worker can run longer | Partly: wait 30 s and log if still running. Worst case (20 socket reads of 4 s) is still theoretical |
| 3 | Put-site rewrite without freezing threads | Open: needs thread suspension; not tested here |
| 4 | Original test/js error check NOPed out | Fixed: only the 5-byte call and one NOP are written |
| 5 | `g_webview` never assigned; cleanup dead | Fixed: block and `BuildCleanupJs` removed (disable relaunches the UI) |
| 6 | Relaunch command line too small for worst case | Fixed: 16 KB buffer, checked length |
| 7 | `GetClassNameW` result unchecked | Fixed |
| 8 | Pong frame over 125 bytes malformed | Fixed: dropped |
| 9 | 36-byte cave record restores 4 bytes past a slot | Fixed: 32 bytes |
| 10 | First `webSocketDebuggerUrl` may be the wrong target | Fixed: target whose URL has `tauri.localhost` |
| 11 | Relaunch cooldown race | Fixed: one compare-and-swap |
| 12 | Restore path without instruction-cache flush | Fixed |

Installed 2.0.43: `local@windhawk-styler_2.0.43_212412.dll`, DLL SHA256
`CBF93C9E...73A0A032E`, installed source equals the repo file (SHA256
`72897115...FC7AC55`). Registry Version `2.0.43`, SettingsChangeTime
`1791725052`. The running UI loads the 2.0.43 DLL. The live page is found through
the new selection, the style is injected, and the table ring is unchanged
(1px, radius 16px). Corner crop checked. Not verified directly: the patched
machine code itself (the UI runs, so it did not crash at patch time).

Commits: release `7e02dc3`, `main` `3c17f10` (blob `9418c46`). Not pushed.

## Still open

- Finding 3 above: a live put-site rewrite without freezing threads. Fixing it
  means suspending the process's other threads during the patch, which I would
  not ship without a test rig.
- Full rewrite: not done. The native hooks carry the mod's working behavior, so
  they changed only where the review found a real defect. The CSS builder is
  cleaned up in place.
