# Translucent Windows: why some windows go black, and how to smooth it out

Date: 2026-10-24. Read-only audit. No mod, registry or engine change was made for this plan.
Thread: e50dff90-4ecb-4c93-82e9-5480de69dae1

## The three symptoms

1. A window flashes black, then turns transparent.
2. A window stays solid black and never becomes transparent.
3. Some windows are not translucent at all.

## What is measured, inferred, or guessed

Measured:
- Explorer's "Delete Folder" confirmation dialog (`#32770`) is 66.2% pure black with the mod on. With `translucent-windows` disabled in Explorer it is 0% black. Source: `notes\2026-10-17-black-popups.md`.
- The Windows color scheme in `HKCU\Control Panel\Colors` is not the cause of that black. Same note.
- The engine loads the mod's source and DLL under `local@translucent-windows` 1.8.3, enabled, with 156 settings. Registry and `ModsSource` checked 10:45 AM today.

Inferred from the source (`C:\ProgramData\Windhawk\ModsSource\local@translucent-windows.wh.cpp`), not yet run:
- Pure black (RGB 0,0,0) is the mod's transparency key. `GetSysColor` and `GetSysColorBrush` return black for `COLOR_WINDOW`, `COLOR_BTNFACE`, `COLOR_MENU` and a few more. `FillRect` with a black brush then paints alpha 0. Black fills are at roughly lines 1262, 2118, 2231, 2832, 4996 to 5149.
- The backdrop is set in `NewWindowShown` and `HandleEffects` (around lines 5340 and 5371). Menus get it on `WM_NCPAINT` and `WM_PRINT`. Other windows get it when they show.
- Likely cause of symptom 1: a window's first paint can land before the backdrop call. That first frame uses the black key with no backdrop behind it, so it looks black. Then the backdrop lands and the window turns transparent. This fits the report, but it is a guess until a frame capture shows it.
- Likely cause of symptom 2: any window the mod does not back (not eligible, a dialog, a window with a process rule that turns effects off) keeps the black key and stays solid black. Dialogs are measured. The rest are guesses.

Guessed, needs a test:
- `translucent-flyouts` and `translucent-windows` both style menus (`FlyoutsEffects=TRUE` in this mod). Two hooks on the same menus may fight. Turning one off would show it.

Not a fix path:
- Setting `SysColors=1` writes black into the system color table for every app. Notes say do not.
- Setting the Explorer rule `ThemeBackground=0` does not clear the black, because the color hook still runs.
- A GDI body tint is a dead end on menu surfaces (memory: `translucent-flyouts-gdi-alpha`). The accent is the only tint path.

## Plan, one change at a time, each with a before and after number

Step 0. Measure first (no change to the mod).
- Write a sweep: capture every visible top-level window and report its pure-black percentage. This extends the 10-17 method to all windows.
- Write a flash probe: capture frames about every 20 ms while a window opens, and count black frames in the first 300 ms.
- Save the output under `reports\2026-10-24-translucent-windows-smoothing\`.
- Touches the desktop, so it runs under the machine desktop lock.

Step 1. Test the menu overlap (settings only, reversible).
- Turn `FlyoutsEffects` off in `translucent-windows` for one test pass and measure menus again.
- If menu black drops, the two mods are fighting. Then pick one owner for menus.
- Reversible: restore the old value and bump `SettingsChangeTime`.

Step 2. Stop the first-frame black.
- Apply the backdrop at window creation, before the first show and paint. Likely place: a CBT hook on window creation, or the first `WM_NCCREATE`.
- Target: flash probe shows 0 black frames for normal windows.
- Build a new revision, keep the old DLL, point the registry at the new file, and keep a guard copy.

Step 3. Stop the solid black on windows the mod does not back.
- Option A (recommended, from the 10-17 note): add dialog windows (`#32770`) to the backdrop path. Explorer keeps its blur and dialogs stop being black.
- Option B: per-process rule that drops the color hook for Explorer. Settings only, but Explorer loses its blur.
- Option C: leave the black. No change.

Step 4. Verify and record.
- Sweep again. Target: no unexpected pure-black windows that the mod is supposed to back.
- Check the Delete Folder dialog, Properties, a Qt or Electron app, and one WinUI app. Qt, Electron, Chromium, UWP and WinUI are not covered by design (readme FAQ).

## Constraints that apply

- Engine restart is banned: `windhawk.exe -restart` also restarts Explorer.
- The freeze hunt of 10-22 to 10-24 is open. Nothing here is on its suspect list, but a new DLL in Explorer changes the mod set the hunt measures. Wait for the hunt to close before any Explorer-facing change, or log the change in the hunt notes.
- A new DLL does not replace the old one in processes that are already running. Those keep the old code until they restart. Explorer restart is pre-approved but should wait for the hunt.
- Every change: backup, one change, measure before and after, receipt, rollback line in the note.

## Decision for you (the look is yours to choose)

1. Give dialogs the Explorer backdrop (recommended). Dialogs match the rest of Explorer, and Explorer keeps its blur.
2. Exclude Explorer from the color hook. Dialogs turn to real colors. Explorer loses its blur.
3. Leave it. Dialogs stay solid black.

## Verified state at the time of this plan

- Engine service: Running, started 1:02 AM today.
- Guard task `TranslucentWindowsGuard`: Ready, checks every 5 minutes.
- No coop locks held on `windhawk-engine`.
- Overlapping plan already on file: `notes\2026-10-18-translucent-windows-plus-plan.md` (the rename).

## Measured after the rename attempt (added 6:20 AM)

- The mod loads into Explorer processes unevenly. At 6:13 AM, the taskbar process (owner of Shell_TrayWnd, PID 8136) had 12 mods and no translucent DLL. Another Explorer process (PID 29340) had the translucent DLL and 2 other mods. The Plus id behaved the same way at 6:08 AM. The gap does not depend on the id.
- This is the first measured candidate for "some windows are not translucent". Next step: find why the taskbar process skips the mod (per-process init failure or exclusion). Measure before changing any setting.
- Record of the rename: notes\2026-10-24-translucent-windows-plus-rename.md.
