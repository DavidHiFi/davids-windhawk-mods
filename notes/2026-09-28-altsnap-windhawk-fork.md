# AltSnap replaced by a local Windhawk mod (local@alt-snap-drag)

2026-09-28. Status: live, owner-verified, version 1.2.2.

## What is installed

A local Windhawk mod, `local@alt-snap-drag` 1.2.2, replaces both the stock
Windhawk AltDrag mod and the standalone AltSnap app. It is enabled for all
processes with settings matching the owner's AltSnap.ini.

| Item | Value |
| --- | --- |
| Registry key | `HKLM\SOFTWARE\Windhawk\Engine\Mods\local@alt-snap-drag` |
| LibraryFileName | `local@alt-snap-drag_1.2.2_1.dll` |
| Disabled | 0 (enabled) |
| Include / Exclude | `*` / (empty) |
| Architecture | (empty, both 64-bit and 32-bit payloads installed) |
| 64-bit payload | `C:\ProgramData\Windhawk\Engine\Mods\64\local@alt-snap-drag_1.2.2_1.dll` - sha256 `983481A2C598F5D11FB52CBB69EC40AEC484547B09136307FCDEB86462EFAE7C` |
| 32-bit payload | `C:\ProgramData\Windhawk\Engine\Mods\32\local@alt-snap-drag_1.2.2_1.dll` - sha256 `E2C974009BF41A1B04041B530794D374BE42DE4F19D8A4386A3D3E0F74BE953D` |
| Source (installed) | `C:\ProgramData\Windhawk\ModsSource\local@alt-snap-drag.wh.cpp` |
| Public source | https://github.com/DavidHiFi/davids-windhawk-mods |

## Behaviour (parity with the owner's AltSnap)

Mouse, with Alt held: left drag moves a window; right drag resizes it from the
edge or corner nearest the starting point; middle click opens the window menu;
right-clicking while a window is being moved toggles its maximized state, and
the toggled state sticks once Alt and the mouse are released. That last one is
AltSnap's built-in trick (AltSnap.txt: "If you are moving a window you can
press the right mouse button to toggle the maximized state").

Keys, with Alt held: F toggles maximize, M minimizes, Shift+Q closes. These are
the values in the owner's AltSnap.ini `[KBShortcuts]`: `Maximize=326` (Alt+F),
`Minimize=333` (Alt+M), `Close=1361` (Alt+Shift+Q); `Menu`, `Lower` and `Kill`
are unbound there.

Settings written: 28 values under the mod's `Settings` subkey - the source
defaults, with `dragWindowsWithoutTitleBar=1` carried over from the previous
alt-drag configuration on this machine.

## Changes applied (2026-09-28)

| # | What | Original | Now | Rollback |
| --- | --- | --- | --- | --- |
| 1 | Stock AltDrag Windhawk mod | `alt-drag` Disabled=0, Include=* | Disabled=1 | set Disabled=0 |
| 2 | Local mod | (absent) | enabled, see table above | set Disabled=1, or delete the key |
| 3 | AltSnap auto-start | task `AltSnap` Ready | Disabled | `Enable-ScheduledTask -TaskName AltSnap` |
| 4 | Fork revisions | 1.2.0_1, 1.2.0_2, 1.2.1_1 | 1.2.2_1 at 08:05 | point `LibraryFileName` back and restart the engine |

Applied by `scripts\2026-09-28-altsnap-windhawk-install.ps1 -Install`, run
elevated. Pre-change backups:
`backups\2026-09-28\altsnap-fork\windhawk-mods-before-*.reg` (full
`HKLM\SOFTWARE\Windhawk\Engine\Mods` export) and
`backups\2026-09-28\altsnap-fork\alt-snap-scheduled-task.xml`.

The AltSnap app itself was not modified. It was already closed by the owner and
does not auto-start now.

## Rollback

Elevated:

```powershell
powershell.exe -NoProfile -ExecutionPolicy Bypass -File `
  'H:\System Configuration\scripts\2026-09-28-altsnap-windhawk-install.ps1' -Rollback
```

That re-enables `alt-drag`, disables the fork, re-enables the AltSnap task and
restarts the Windhawk engine. To go back to AltSnap immediately instead, just
run `%APPDATA%\AltSnap\AltSnap.exe`; `Uninstall.exe` in the same folder removes
the app if it is no longer wanted.

## Source and build

- Fork source: `Windhawk\altsnap-fork\alt-snap.wh.cpp` (1.2.2), also published
  in `davids-windhawk-mods`. The stock mod source is kept beside it as
  `alt-drag.stock-1.1.wh.cpp`.
- Build: `scripts\2026-09-28-altsnap-windhawk-build.ps1` compiles both
  architectures with the Windhawk-bundled clang++ 20 against the engine's
  `windhawk.lib`, producing
  `Windhawk\altsnap-fork\local@alt-snap-drag_1.2.2_1_{64,32}.dll`.
- Traps hit and fixed along the way:
  1. `-DWH_EDITING` is the editor's syntax mode: it turns every Wh_* API call
     into a no-op stub, so the DLL imports nothing from `windhawk.dll` and the
     mod silently does nothing. Production mods build with `WH_MOD` only and
     must import `InternalWh_*` from `windhawk.dll`, like the stock mods do.
  2. Windows PowerShell 5.1 strips the quotes from `-DWH_MOD_ID=L"..."` on the
     clang command line, which breaks the `L"..." WH_MOD_ID` concatenation in
     the source. The mod id is passed through the force-included
     `Windhawk\altsnap-fork\altsnap-modid.h` instead.
  3. The engine keeps a loaded DLL mapped, so an install that overwrites the
     same file fails. Each install uses a new revision and points
     `LibraryFileName` at it.
  4. The right-click maximize first reverted as soon as Alt was released: the
     move was a system modal loop, and ending it, or letting the Alt release
     reach the window and open its menu, cancels the loop, which restores the
     window to its pre-drag state. 1.2.2 ends the loop at the right-click
     itself and keeps that Alt release from reaching the window.

## Verification

The harness `scripts\2026-09-28-altsnap-windhawk-test.ps1` compiles a
throwaway GUI-subsystem window, drives it with injected input, records the
window messages it receives, and waits for keyboard idle first. Run of
2026-09-28 08:08 against 1.2.2:

| Check | Result |
| --- | --- |
| Right click while moving maximizes, state survives releasing Alt and the mouse | pass (also pass at 08:06) |
| Alt + right drag resize | pass (size delta 120,80) |
| Alt+F maximize toggle | pass |
| Alt+M minimize | pass |
| Alt+Shift+Q close | pass |
| Alt + right click on a maximized window restores it | pass |
| Alt + left drag move | informational, see below |

The move check fails in the harness only: the throwaway window deactivates
right after the first injected Alt of a session (the captured message log shows
`WM_SYSKEYDOWN 18` then `WM_ACTIVATE 0` with no mouse message), so the drag
press goes to whatever holds the foreground instead. The same move path passes
inside the right-click check, whose message log shows the mod's
`WM_SYSCOMMAND 0xF012` (SC_MOVE) followed by a run of `WM_MOVE` messages, and
the owner uses Alt+drag all day. The harness must run as administrator: a
medium-integrity process cannot take the foreground while an elevated window
holds it, so it launches the test window itself de-elevated via
`runas /trustlevel`.

## Notes and leftovers

- Superseded `local@alt-snap-drag_1.2.0_2.dll` and `..._1.2.1_1.dll` files
  remain in the two Mods folders because the engine had them mapped when the
  newer revision was installed. They are unreferenced and harmless; the install
  script deletes stale revisions when Windows releases them.
- AltSnap's other features (Aero snapping, zones, title-bar actions, scroll
  actions) are not part of this fork; the owner's use is window movement, the
  key shortcuts above, the menu action, and the right-click maximize toggle.
