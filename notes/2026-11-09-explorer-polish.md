# 2026-11-09: Explorer polish (status dock, details pane, drive bars, lines)

Mods: File Explorer Styler Plus 1.9.2 -> 1.10.2, GPU Accelerated Explorer View Plus 1.3.2 -> 1.3.3.
Work: `work\2026-11-09-explorer-polish\` (`patch.py styler|gpu <src> <dst>`, `src\*-new.wh.cpp`,
`capture.ps1`, `children.ps1`). Script: `scripts\explorer-polish-2026-11-09.ps1`.
Backups: `backups\2026-11-09-explorer-polish\` (1.9.2 and 1.3.2 sources, both .reg exports,
pre-install export, run.log, installed.json).

| Part | Old | New |
|---|---|---|
| Status dock | rounded pill, inset 2 px, gradient ring | flat band border to border, 1 px #585B70 top line, blue to mauve while hovered |
| Status separators | short theme line with gaps | 1 px #585B70 from the top line to the dock bottom |
| Details pane margin | 20,20,20,1 (cut by the dock) | 20,20,20,20 (ends 20 px above the dock) |
| Details pane card | no border, Segoe UI | 1 px glass gradient border, blue to mauve on hover (mod code), FiraCode Nerd Font |
| Toolbar lines | #3A3A3A, barely visible | #585B70 (rule 40 and `controlStyles[11].styles[1]`) |
| Drive bars | no outline | 1 px #585B70 ring around the free-space track (GPU 1.3.3) |

- Installed: Styler 1.10.0 at 2:44 pm, GPU 1.3.3 at 2:47 pm, Styler 1.10.2 at 2:59 pm.
  Settings rules 37-40 added. No Explorer restart.
- Verified from captures (`reports\2026-11-09-explorer-polish\after.png`, `after4.png`, zooms):
  dock line full width #585B70, separators full height, toolbar lines #585B70, details card
  ends at y=848 above the dock at y=868, drive bar ring visible.
- Not verified: hover states (dock line gradient, details pane border) need the cursor, which
  is never moved by automation.
- Still open: the vertical lines between the side panel, the content and the details pane stay
  translucent (about #4B4C5A on this wallpaper, not #585B70). 1.10.1 tried the ExplorerFrame
  Polyline path, 1.10.2 tried 1 px DirectUI fills (FillRect, PatBlt, theme parts); neither
  changed the pixels, so the line comes from another call. The code is harmless and can stay
  or go in the next build. The line sits in the DirectUIHWND gap between the tree window and
  the GPU overlay (screen x 1225 to 1229 in the `children.ps1` run).
- GPU 1.3.3 also changed "(Suggested: 25)" to "(suggested 25)": a second colon in a settings
  description fails the engine's YAML parse.
- Rollback: `scripts\explorer-polish-2026-11-09.ps1 -Action Rollback`, elevated, under
  `coop lock windhawk-engine`. Restores both old sources, removes rules 37-40 and the extra
  value, and imports `styler-plus.reg`.

## Second pass, 3:13 pm (owner feedback on This PC)

GPU 1.3.3 -> 1.3.4, Styler 1.10.2 -> 1.10.3. Made by `work\2026-11-09-explorer-polish\patch2.py`
(`src\gpu-b.wh.cpp`, `src\styler-b.wh.cpp`). Script: `scripts\explorer-polish-2026-11-09b.ps1`.
Backups: `backups\2026-11-09-explorer-polish-b\` (1.3.3 and 1.10.2 sources, styler-plus.reg, run.log).

| Part | Old | New |
|---|---|---|
| Group heading at rest | nothing (border only on hover) | 1px #45475A outline, same box and radius as the hover border |
| Drive usage fill | solid blue | blue to mauve across the used part; peach at 80%, red at 90% unchanged |
| Drive track / ring | surface1 track, #585B70 ring | surface0 #313244 track, #45475A ring |
| Lines the styler paints (dock top line, status separators, nav pane lines) | #585B70 | #45475A |
| Toolbar lines (`controlStyles[40].styles[0]`, `controlStyles[11].styles[1]`) | BorderBrush=#585B70 | BorderBrush=#45475A |

- Verified 3:14 pm (`reports\2026-11-09-explorer-polish\after5.png`): toolbar line, dock top line,
  heading outline and drive ring all sample (69,71,90); C: fill runs (134,173,240) to (193,160,238).
- The resting outline shows on every group heading in GPU views, not only This PC.
- Rollback: `scripts\explorer-polish-2026-11-09b.ps1 -Action Rollback`, elevated, under
  `coop lock windhawk-engine`.

## Third pass, 3:22 pm (more contrast, see-through dock)

GPU 1.3.4 -> 1.3.5, Styler 1.10.3 -> 1.10.4. Made by `work\2026-11-09-explorer-polish\patch3.py`
(`src\gpu-c.wh.cpp`, `src\styler-c.wh.cpp`). Script: `scripts\explorer-polish-2026-11-09c.ps1`.
Backups: `backups\2026-11-09-explorer-polish-c\` (1.3.4 and 1.10.3 sources, styler-plus.reg, run.log).

| Part | Old | New |
|---|---|---|
| Group heading at rest | outline only | outline over crust #11111B at 35% |
| Command bar row (`controlStyles[11].styles[2]`) | (none) | Background=#4011111B |
| Status dock fill | #1E1E2E at 95% (looked solid) | #1E1E2E at 60%, window glass shows through |

- Verified from `reports\2026-11-09-explorer-polish\after6.png`: the command bar row reads about 10
  levels darker than the rows above and below it; heading inside 39 vs 50 outside; dock
  (28,28,44) = 60% base over the glass (it would be about 18 over opaque black).
- Rollback: `scripts\explorer-polish-2026-11-09c.ps1 -Action Rollback`, elevated, under
  `coop lock windhawk-engine`.
