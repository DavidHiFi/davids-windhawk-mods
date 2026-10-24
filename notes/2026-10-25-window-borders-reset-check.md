# window-borders vs the 1:49 and 1:53 AM resets (2026-10-25)

Checked 1:56 AM, thread 5e208cdd. Answer to thread 5c7ab418.

Measured:
- Kernel-Power 41 at 1:49:26 AM and 1:53:30 AM. Seven earlier resets 6:03 PM to 8:57 PM on 10/24 came before any window-borders DLL existed (first DLL 11:27 PM). The 9:02 PM freeze quarantine already named every `*` mod as a suspect.
- Registry still pointed at rev 2 (LibraryFileName `_2.dll`, SettingsChangeTime 1:45:41 AM). The rev 3 install at 1:52 AM only copied a DLL; the elevated log shows it failed on a missing build path, so the "1:52 rebuild" never went live.
- My two-window desktop tests ran just before 1:49 AM, with Include=* on.

Inferred, not proven: no dump exists. window-borders is a `*` mod that calls DwmSetWindowAttribute from every GUI process, the class the freeze hunt flagged, so it cannot be ruled out.

Done: Disabled=1 at 1:56 AM (readback 1). 13 processes (Steam, T3 Code, Mullvad, SearchHost, ShellExperienceHost, Qt web engines) still map the old DLL until they restart; protected apps not restarted.
Rollback: `scripts\2026-10-25-window-borders-toggle.ps1 -State On`.

Before re-enabling: narrow Include to a short list of apps (not `*`), fix the install script's hard-coded `_1.dll` debug lines, install rev 3, test one app at a time.

## Installer fixed (5:20 AM, offline; nothing installed or enabled)

`Windhawk\window-borders\Install-window-borders.ps1`:
- `-Include` is now a required argument for Install and is written and read back
  instead of the hard-coded `*`. An install without it throws before touching
  ProgramData or the registry.
- The build path no longer comes from the elevated child's `$env:TEMP`, which
  resolved to the 8.3 form `C:\Users\LOCALU~1\...` and failed the copy step. The
  default now resolves through `[Environment]::GetFolderPath('LocalApplicationData')`,
  and the caller's `-BuildRoot` is passed through unchanged.
- The debug lines that probed `_1.dll` now use the requested `$dllName`.
- The error file is written under `$buildRoot`, not the child's TEMP.

Verified: PowerShell parser reports no errors, and `-Action Audit` runs and reads
the live key (Disabled=1, LibraryFileName `_2.dll`, Include still `*`).
Not verified: an actual Install run, because Windhawk is off after freeze 12 and
the freeze rule forbids installing mods until the owner reopens it.


## Whitelist request (5:18 AM)

Owner asked to put the mod on the allow list if the resets were 100% certainly not
its fault. Not done, and no allow-list entry was added: with no crash dump that
certainty cannot be given. What the timeline does support: the mod was off for
the 4:39 AM reset and did not exist for the seven 10/24 resets; it was loaded
into every app for the 1:49 and 1:53 AM resets, so it stays a possible
contributor there. A scoped install needs no exception in
`scripts\Test-WindhawkFreezeGate.ps1`; the `$allowEveryApp` entry is unchanged.

## Source review (owner asked for a verdict from the code)

Read every hook and thread in `local@window-borders.wh.cpp`:
- It only calls `DwmSetWindowAttribute(DWMWA_BORDER_COLOR)` on its own process's windows, after the window's own DefWindowProc returns. No SendMessage, no cross-thread waits (except a 1 s wait at unload), no loop that triggers itself (setting a border color does not send WM_NCACTIVATE), never loads into dwm.exe.
- No other enabled mod sets the border color on normal windows (old accent-border and translucent-flyouts are off; windhawk-styler only in windhawk-ui.exe).
- Found one real bug: unload deleted a lock another thread could still be using. That could crash one app when the mod unloads, not freeze the PC. Fixed in source; rev 4 builds clean (not installed).
Verdict: nothing in the code can hang the system. Install scoped to a short app list after the freeze gate passes.
