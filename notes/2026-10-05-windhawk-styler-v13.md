# Windhawk Styler 1.3.0

Installed revision 4 (`local@windhawk-styler_1.3.0_4.dll`) and published commit `b13299e` to DavidHiFi/davids-windhawk-mods main. The native title bar now keeps its themed caption and window buttons through maximize, and transparency works with or without the native title bar.

## What changed from the 1.2.0 line

The previous session's revisions 7 to 9 (never published before now) replaced the hand-drawn round buttons on the custom title bar with the real native caption and left the remaining defects open. 1.3.0 fixes the defects:

- **The maximize button works and keeps the themed caption.** On this OS, a transparent Electron window that enters the real maximized state loses the DWM themed frame; DWM reporting flips to NC rendering off and the caption falls back to the classic drawing (the small square "legacy" buttons and, when combined with the DWM policy reset, the unstyled frame). The mod now intercepts `ShowWindow`/`ShowWindowAsync(SW_MAXIMIZE)` in the interface process and fits the window to the monitor work area instead, like Chromium's own frameless maximize. The caption, with this machine's theme dots, stays exactly as it is. State the OS maximized by other means (snap to top, drag to edge) is converted on `WM_SIZE` via a posted message.
- **No black strip at the bottom.** Chromium sizes its page surface a caption height shorter than the client rect. `WM_NCCALCSIZE` now extends the client into the bottom frame by that same amount, so the page reaches the window's bottom edge in every state, restored and fit. The bottom resize grip is restored explicitly in `WM_NCHITTEST`.
- **The classic caption never paints while DWM is on.** `WM_NCPAINT` used to fall through to `DefWindowProc` whenever NC rendering read disabled (which is exactly what happens when maximized), painting the classic caption. It now only paints classic when DWM composition is actually off, and the NC rendering policy is re-asserted after Chromium handles `WM_SIZE`/`WM_WINDOWPOSCHANGED`, not before.
- **Transparency in both modes.** The interface background alpha and the acrylic backdrop are no longer forced opaque with the native title bar. The stripes test shows the blur behind the window in native mode (`v130-native-stripes.png`).
- **Window commands are not swallowed.** `WM_SYSCOMMAND` for `SC_MAXIMIZE`, `SC_RESTORE` and `SC_MINIMIZE` now runs the window action directly; Chromium otherwise drops the default caption-button commands.

## Verification

- Caption maximize click: window fits the work area, `IsZoomed=false`, work-area rect, no band (`accept-r3.log` bottom scans: page reaches the bottom edge).
- Caption click again restores the exact previous rect, including after the workspace-coordinate correction (rev 4 fixed the 50 px task-bar offset).
- External `ShowWindow(SW_MAXIMIZE)` converts to the same clean fit within the message round-trip.
- Custom mode (native title bar off): the page maximize control and `SW_MAXIMIZE` both give a full-bleed client with no band; no classic caption anywhere.
- Native-mode stripes test: the red/cyan stripes are visible through the window (`v130-native-stripes.png`).
- Captures in this folder; machine-readable receipt in `install-receipt.json`.

## Files

- Source: `work/windhawk-styler/v3/windhawk-styler.wh.cpp` (sha256 `566BFF3F...74094`), synced to the fork.
- Builds: `work/windhawk-styler/v3/local@windhawk-styler_1.3.0_4_{64,32}.dll`.
- Evidence: `reports/2026-10-05-windhawk-styler-v13`.
- Backups (pre-change settings, registry, source): `backups/2026-10-05/windhawk-styler/v130`.
- Audit/rollback: `scripts/2026-10-05-windhawk-styler.ps1` (`-Audit`, `-Rollback`).

## Errors along the way worth remembering

- `DwmSetWindowAttribute(DWMWA_NCRENDERING_POLICY, ENABLED)` is accepted on this transparent window in the maximized state but never sticks; do not fight for the OS maximized state, avoid it (the fit) instead.
- A registry `LibraryFileName` swap with a `-replace` that only matched part of the paths left the engine pointing at a nonexistent DLL; the mod silently stopped loading, no tool spawned, and the interface files stayed stripped. Check that the DLL exists in `Engine\Mods\{64,32}` after every install, and that a `-tool-mod` process appears.
- The engine reloads the mod DLL only on a disable/enable cycle. A `SettingsChangeTime` bump alone does not reload the DLL.
- `windhawk.exe` manager instances exit immediately when another instance is running; the tool spawn comes from the engine's mod load (`Wh_ModAfterInit`).
- With the window exactly at the work-area rect, `DefWindowProc`'s `WM_NCHITTEST` stops reporting the caption and resize borders, so scripted hit-tests should move the window to a normal rect first.
- PowerShell `@($a-$b, $c+$d)` inside a return parses the comma before the arithmetic; compute into variables first.

## Traps carried over

- The mod's tool process only launches when a plain `windhawk.exe` instance loads the mod. After a disable/enable cycle, start `windhawk.exe` once or no tool runs and the files stay unstyled.
- Windhawk resets the mod's `Settings` key when the source file is updated; the install script captures and restores the settings.
