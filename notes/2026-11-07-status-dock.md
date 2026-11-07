# File Explorer status bar dock (2026-11-07)

The status bar at the bottom of File Explorer now sits on a rounded Catppuccin Mocha dock. It lives in `local@windows-11-file-explorer-styler-plus` 1.8.1, setting **Status bar dock** (`statusBarDock`, default on).

## Why it is GDI, not XAML

The status bar is a DirectUI element, not XAML, so control styles can't reach it. A probe mod (`work\2026-11-07-status-dock\status-dock-probe.wh.cpp`, log `reports\2026-11-07-status-dock\probe.log`) showed the paint order inside the folder view's `DirectUIHWND` (parent `DUIViewWndClassName`):

1. `BeginPaint`, then `BeginBufferedPaint` (format 0) into a memory DC.
2. Root fill `0,0,W,H`, then the status band fill `0,H-24,W,H` (black), twice.
3. Child fills inside the band, then the text (glyph `ExtTextOutW`, alpha text via a nested format 2 buffer), the `ShellStatusBarSeparator` lines, and the `CommandModule` part 4 view buttons.
4. Nav pane and items view fills after that.

## What the mod does

- Hooks `BeginBufferedPaint`/`EndBufferedPaint` and records format 0 buffers whose target is the folder view `DirectUIHWND` being painted.
- In `FillRect`, a dark fill in that buffer that spans the full width and ends at the client bottom (16 to 48 px high, DPI scaled) is the band. The pill is drawn right after it. Later dark fills inside the band repaint the pill in their own rect, so the text and buttons still land on top.
- Pill: inset 2 px left and right, 1 px top, 2 px bottom, radius min(10 px, half height), fill `#313244`, 1 px border gradient `#B36C7086` to `#8C45475A` to `#B36C7086`. Same values as the top bar bubble buttons. Cached per size and DPI (max 8), freed with the theme part cache.

- The GPU Accelerated Explorer View Plus view toggle (a child button with prop `WindhawkExplorerGpuViewToggleOwner`) filled its own background black over the dock. Its format 2 buffered paint is tracked too: the pill slice under it is painted after its background fill, and the button gets a window region clipped to the pill's height so no black rows show. The GPU mod itself is untouched. Turning the dock off leaves that region in place until the toggle is recreated (harmless, 3 px).

## 1.9.0: partial repaint fix, darker dock, view button states

- Artifact (owner report, 2026-11-07): dark blocks under the status text and a dark square near the right end that cleared after a while. Probe log `reports\2026-11-07-status-dock\probe-run1.log` (measured): a selection change repaints only `6,1189,340,1213`, and every fill in that paint is clipped to the dirty rect, so the full-width band test never matched and the black fills stayed until the next full paint. Same for the `1155,1190,1175,1211` patch at the right.
- Fix: the band height of each folder view is stored on its full paint (`g_statusDockBands`, client coordinates). In a partial paint, a dark fill that lies inside those band rows repaints the dock clipped to itself. A full paint with no band (status bar hidden) drops the entry. The view toggle now finds the dock from the same map, so moving the window no longer leaves a stale screen rect.
- Dock: base `#1E1E2E` at 95%, 1px border gradient surface1 `#45475A` to surface0 `#313244` (was surface0 fill, which the owner found too light).
- View buttons (`CommandModule` part 4): measured states are only 1 (normal) and 2 (current view); a posted hover changed no state. Current view: surface0 face, 1px blue `#89B4FA` ring. Hover (cursor over the button at paint time, read with `GetCursorPos`): mantle face, blue to mauve gradient ring; current view plus hover: surface0 face, gradient ring. Radius 6. No fade: DirectUI repaints the button on enter and leave, there is no animation hook.
- The light grey icon tiles are Explorer's own glyphs, drawn after the face; left as is.
- Hover is not verified live: the owner was active at the PC, so the real cursor was not moved.

## 1.9.1 / 1.9.2: hover border, Mocha icons, switch button

Owner report (2026-11-07): no blue to mauve border on hover; the GPU switch button hover is a "classic greyish black" box; the two view icons look grey or white; the switch arrows jump and double while the window moves.

- Dock hover: the folder view is subclassed (`SetWindowSubclass`). Mouse move inside the pill, or a 50 ms cursor check while hovered (also covers the cursor sitting on the toggle child), flips the dock to a blue `#89B4FA` to mauve `#CBA6F7` border and repaints the band and toggle. Leaving drops back to the grey border. Subclass removed on uninit and `WM_NCDESTROY`.
- Icons (measured, `reports\2026-11-07-status-dock\glyph-probe.log` from a temporary probe mod, since removed): dui70 draws them with `DrawIconEx` 16x16 after the `CommandModule` part 4 face. They are light theme icons: a grey tile with black strokes. 1.9.1 wrongly hooked `GdiAlphaBlend` (those 9 slices are uxtheme's own face) and changed nothing. 1.9.2 hooks `DrawIconEx` inside the view button rect, renders the icon on black and on white to recover alpha, keeps only the dark strokes and draws them in Mocha: blue on the current view, text `#CDD6F4` on hover, subtext0 `#A6ADC8` otherwise.
- Switch button: after the GPU mod's own paint, the dock slice is painted over its hover box, then the view button face (mantle plus gradient ring on hover, surface0 when pressed), then its icon.
- Jump while moving (inferred from source, not changed here): the GPU mod's status button query stores screen coordinates and compares them with `EqualRect`, so every move misses the cache, falls back to a guessed spot and requeries UIA, then snaps back. Fix handed to the thread that holds that mod (compare in client coordinates and offset the stored rect).
- Explorer got a new main shell at 12:26 pm during the 1.9.1 install. No crash (1000) or Winlogon 1002 event; crash logging works (an unrelated 11:10 am crash is logged). Cause unknown, not attributed to the mod. 1.9.2 install: same shell PID before and after.

## Change record

- 1.9.2 (2026-11-07): `local@windows-11-file-explorer-styler-plus_1.9.2_915359.dll`. Source copy `backups\2026-11-07\status-dock\styler-plus-1.9.2.wh.cpp`. 1.9.1 (`_1.9.1_475830.dll`, copy `styler-plus-1.9.1.wh.cpp`) had the hover border and switch face but the dead icon hook. Rollback: elevated `windhawk-cli mod install --file` with the 1.9.0 copy.

- 1.9.0 (2026-11-07): `local@windows-11-file-explorer-styler-plus_1.9.0_604282.dll`. Source copy `backups\2026-11-07\status-dock\styler-plus-1.9.0.wh.cpp`. The 1.8.1 source was not kept separately; roll back by turning the setting off or reinstalling 1.7.3 as below.
- Old: 1.7.3, `local@windows-11-file-explorer-styler-plus_1.7.3_1.dll`.
- New: 1.8.1, `local@windows-11-file-explorer-styler-plus_1.8.1_171741.dll` (1.8.0 was the first pass, without the toggle fix), installed with `scripts\2026-11-07-status-dock-deploy.ps1` (elevated). `statusBarDock=1` in the mod Settings key.
- Backups: `backups\2026-11-07\status-dock\styler-plus-1.7.3.wh.cpp` and `.reg`.
- Rollback: turn off **Status bar dock** (instant, next repaint), or elevated `windhawk-cli mod install --file "H:\Windhawk Configuration\backups\2026-11-07\status-dock\styler-plus-1.7.3.wh.cpp"`.
- No Explorer restart; the mod hot-reloaded. No window-look mod touched.

## Evidence

- Loaded in both explorer.exe shells (`tasklist /m`, 2026-11-07), same two shell PIDs before and after.
- Captures: `reports\2026-11-07-status-dock\before.png`, `after.png` (1.8.0, black toggle square), `after-1.8.1.png` (final).
- Shell: main shell PID 37540 unchanged since 5:57 am; churn check 0/2, 0 crashes (10:35 am). Extra explorer.exe processes seen then were windowless /factory folder hosts from capture windows, responsive, exiting on their own.
