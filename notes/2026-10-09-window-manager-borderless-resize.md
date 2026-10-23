# Alt+drag audit: Ditto / Flow Launcher resize + window-manager 1.1.4

2026-10-09. Status: fix built and installed live, synthetic + real-app
verification pending a hands-off input window.

## Audit findings

1. The standalone fork (`local@alt-snap-drag` 1.2.2) is NOT installed. It was
   uninstalled on 2026-10-04 and never reinstalled: no registry key, no
   ModsSource copy, no engine DLL. Stock `alt-drag` is absent too, and the
   AltSnap app + scheduled task are disabled with no process running.
2. The live Alt+drag behavior comes from `local@window-manager` 1.1.3, which
   embeds the same drag engine (`window-manager.wh.cpp` line 107:
   `local@alt-snap-drag.wh.cpp <- drag`). Live settings: move Alt+Left,
   size Alt+Right, `dragWindowsWithoutTitleBar=1`,
   `rightClickAction=maximize`, Include `*|windhawk.exe`.
3. Root cause of the reported failure: `CanSizeRootWindow` required
   `WS_THICKFRAME` with no override. Measured live styles:
   - Ditto quick-paste popup (`QPasteClass`): style `0x84000000` (WS_POPUP,
     no caption, no sizing border) -> move worked (title-bar bypass), resize
     refused, press fell through to the app.
   - Flow Launcher main (`HwndWrapper`): style `0x06000000`, ex `0x80088`
     (topmost toolwindow, layered) -> same: movable, not resizable.
   - Ditto main (`Ditto` class, `0x4CFC000`) HAS caption + sizing border, so
     it always resized; the popup is the window in the user's screenshot.
4. "Right-click while Alt-dragging, then hold to expand" is not a resize
   gesture in this codebase: pressing Right mid-move is AltSnap's maximize
   toggle by design (readme + `OnLoopMessageRemoved` + low-level hook path).
   The resize gesture is Alt+Right-drag from the start.

## Fix (1.1.4, mirrors AltSnap: resize any window)

New `sizeWindowsWithoutSizingBorder` setting (default on), mirroring
`dragWindowsWithoutTitleBar`. `CanSizeRootWindow` now allows any
non-maximized, non-excluded hooked window when it is on. Applied to:

- `Windhawk\window-pack\window-manager.wh.cpp` (build source, 1.1.3->1.1.4)
- `davids-windhawk-mods\mods\local\window-manager\window-manager.wh.cpp`
  (publish copy, byte-identical after sync)
- Standalone fork `Windhawk\altsnap-fork\alt-snap.wh.cpp` and
  `davids-windhawk-mods\mods\local\alt-snap-drag\alt-snap.wh.cpp`
  (1.2.2->1.2.3, functional code identical; left uninstalled on purpose -
  window-manager already covers it and two hook mods must never run together)

## Install (live, no engine restart)

- Build: `Windhawk\window-pack\Build-window-manager-1.1.4.ps1` (clang++ 20,
  `-DWH_MOD` only, Engine 2.0.0 `windhawk.lib`):
  - 64-bit `local@window-manager_1.1.4_1_64.dll`
    sha256 `C42F3067...499DF2BDC4`
  - 32-bit `local@window-manager_1.1.4_1_32.dll`
    sha256 `B7AB13C6...5AB3436C06FB47`
  - Strings check: `windhawk.dll`, `Wh_SetFunctionHook`,
    `sizeWindowsWithoutSizingBorder` all present (not a stub build).
- Install: `scripts\2026-10-09-window-manager-1.1.4-resize-borderless.ps1
  -Install` (elevated): registry exported to
  `backups\2026-10-09\window-manager-1.1.4\`, mod disabled, tool wait, new
  DLLs + ModsSource copied, `LibraryFileName` 1.1.4_1, `Version` 1.1.4,
  `sizeWindowsWithoutSizingBorder=1`, re-enabled, hot-reloaded.
- Post-install state: Disabled 0, Include `*|windhawk.exe` intact, new
  setting 1, both DLL hashes match the build. New DLL confirmed loaded in
  explorer.exe and Flow.Launcher.exe. Ditto.exe is elevated so its module
  list is not readable from a medium shell; its coverage is proven by the
  pending input test instead.
- Rollback: same script `-Rollback` (points back at 1.1.3_1, removes the
  setting), or reimport the `.reg` backup. Full registry backup of the mod
  key is in the backup dir.

## Verification (owner-confirmed live)

`scripts\2026-10-09-window-manager-1.1.4-verify.ps1`: disposable GUI app
with a normal window + a borderless popup (same style bits as QPaste),
four checks (borderless resize = the fix; normal resize/move/maximize-toggle
regressions). Twice aborted cleanly (exit 5) because the user was active -
it refuses to inject input unless the machine is idle 3 s. The synthetic
suite never ran; instead the owner tested Alt+Right-drag resize on Ditto
and Flow Launcher directly and confirmed it works.

Receipt dir: `reports\2026-10-09-window-manager-1.1.4\`
(install-state.json written; no verify-receipt.json - owner-verified).

## Publication

Publish copies in `davids-windhawk-mods` committed and pushed as `7b0659d`
(Window Manager 1.1.4 / AltSnap 1.2.3) on 2026-10-09, so the fix persists.
