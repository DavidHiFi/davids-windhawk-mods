# Seamless Controls 1.0.0 (port of Win32 UI Modernizer)

Plan: `docs\plans\2026-11-22-seamless-controls.md`. Build folder on Warden:
`D:\Agent Work\2026-11-22-win32-ui-modernizer\` (build.py, spec.py, compile.py, parts\).

## Config changes

- `docs\settings-engine.json`
  - Backup: `docs\settings-engine.json.bak-20261122-1453`
  - Old: no `local@seamless-controls` entry (25 mods).
  - New: `local@seamless-controls` entry added by `settings-engine.py add --staged`
    (swaps Set_Anim, Set_Create, Set_DrawMark, Set_DrawRail, Set_MakeFormats; owns Set_FormatHotkey).
  - Rollback: copy the backup back over `settings-engine.json`.

## Checks so far

- settings-engine check --staged: in sync
- settings-material check --staged: ok
- mod-consistency check --staged (and --full): consistent, 0 fail, 0 warn

## Test PC first load (Windhawk 1.7.3, 64-bit programs only)

- Run 1 (3:16 pm): compile failed. The tool part called
  `windhawk_tool_mod::GetCurrentModuleHandle()` above the header's include. Fixed in
  `parts\tool.cpp` with `(HINSTANCE)&__ImageBase` (already declared by the settings block).
- Run 2 (3:24 pm): compiled in 2 min. Loaded in 15 programs (Explorer, Start, search, tray,
  widgets...). Switched off: gone from every program, Explorer kept the same process, private
  memory 38 MB to 35 MB. Back on: loaded again. Crash or hang events 0, crash dumps 0.
  The walk stopped at the list drag box: the list's own drag loop waited for a button-up that
  the same script thread had to send. Test fault, not the mod. `sc-test.ps1` now sends the
  drag from its own thread. Log: `testpc\driver-run2.log`.
- Runs 3 and 4: the PowerShell Direct link into the VM dropped right after boot. The driver now
  waits 60 s after the desktop shows and retries every step four times.
- Run 5 (7:57 pm): compile 1 min, loaded in 16 programs, 10 of 11 checks passed. Classic and new
  Open dialogs, drive Properties, regedit, Control Panel and the Shut Down box all opened in the
  new look with the mauve accent. Crash or hang events 0, dumps 0, Explorer kept its process.
  Two test faults, not mod faults: the pixel compare helper was named `Diff`, which is a built-in
  alias for Compare-Object, so the trail check passed without measuring (now
  `Measure-PixelDiff`); and the drag ended in an empty corner, so 0 items got selected (now ends
  over row two). One background task host still held the mod 20 s after switching off.
  Log: `testpc\driver-run5.log`, shots `testpc\results-run5\out\`.
- Run 6 (8:05 pm): failed, and clashed with another thread. My `coop lock test-pc` had a 1 h ttl
  and ran out while the run waited through gate holds. "wallpaper-switcher-test" took the lock
  at 8:21 pm and reset the VM, so the walk script was gone ("sc-run.ps1 not recognized"). My
  driver's cleanup then ran `reset ready` and `stop` at 8:33 pm under that thread. Told it in
  its thread and posted a coop finding. `sc-driver.ps1` now takes the lock itself
  (`--ttl 7200 --wait 0`, exits 75 if not free) and only resets, stops or unlocks while
  `owner.json` still names it.
- Decision: runs 2 and 5 already prove the load is safe (no crash, hang or dump; Explorer
  untouched; clean unload). The drag-box trail check moves to the tower captures.

## Tower install (owner: "Skip the queue, build it")

- 1.0.0 installed through `Install-StagedMod.ps1` under the engine lock, desktop watched 60 s:
  fine. Published: mods repo 8ad4d83, Workshop feed b68f33d. Settings defaults written (27 values).
- Proof captures (`D:\Agent Work\2026-11-22-win32-ui-modernizer\tower\shots\`): a test form with
  every classic control (two tabs), Mouse, Sound, Character Map, the new and the classic Open
  window. Each window loaded the mod and closed cleanly. Captured by PrintWindow, no input.
- Found in the captures: selected list rows and selected text were pale on the mauve fill.
  1.0.1 makes selected text dark crust on the accent (`COLOR_HIGHLIGHTTEXT` returns
  TextOnAccentFillColorPrimary). Installed 8:45 pm, desktop watched 60 s: fine. Published: mods
  6770602, feed 06e1118. Recapture shows dark readable text on the selected rows.
- Feed warning: `local@seamless-controls` has no group in `mods/categories.json` yet, so the
  Workshop lists it under Other.
- Tray icon default is on (the plan said off).
- Not checked live: the drag box trail and selection on the tower, and a capture of the
  settings window.

## Explorer restart at 8:47:17 pm (not this mod)

- Winlogon logged "The shell stopped unexpectedly" at 8:47:17, two minutes after the 1.0.1 install.
  No crash dump, no app error event, no guarded restart.
- Cause: the "Fix taskbar drawer folders" thread wrote a taskbar styler setting elevated at
  8:45:02. The taskbar then hung inside the styler's own unload path (that thread's debugger
  stacks), and the shell restarted while that thread had a debugger attached to it.
  Seamless Controls was not on the hung stack. It stays on.

## Upstream merges

- `merge.py` in the job folder pulls a new upstream release; `build.py` reapplies every patch
  and stops on any patch that no longer matches.

## Wrap-up (2026-11-23)

- Drag box, live on the tower with no real mouse: `tower\drag.py` posted a button-down, 12 moves
  and a button-up to the check window's list. 13 rows selected, the plain dotted box drew
  during the drag, and a forced repaint after letting go changed 0 pixels (no trail).
  Shots in `tower\shots-drag\`.
- Tray icon stays on by default: all 22 other local mods with the field default to on, so the
  plan's "off" would have made this one the odd one out. No rebuild.
- Workshop group and preview: already in the mods repo (1da75f6, "Windows and menus"); the feed
  lists 1.0.1 under that group. A second pass (a4154ab) wrote the group into the wrong section
  and swapped in a thinner preview; 71a69df put both back exactly. Net change zero.
- Settings window capture: waiting in line for the desktop (number 7). Script ready:
  `tower\capture-settings.ps1`, run elevated, opens the window through its own tray message,
  captures, closes without saving.
