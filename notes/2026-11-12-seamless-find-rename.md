# Seamless Listary renamed to Seamless Find (2026-11-12)

Owner order: "dont call the mod Listary, give it our own custom name". The mod is now
**Seamless Find**, id `local@seamless-find`, version 1.2.0. Same code as Seamless Listary 1.1.3.
Listary stays only in the credit ("Inspired by Listary by Bopsoft") and where the code means
the real Listary.exe (it stands down while Listary runs).

## What changed

- Header @id and @name, description, readme title, three settings texts
  ("Ctrl Ctrl opens the search box.", "Smart ranking", path bar text).
- Settings window: class `WindhawkSeamlessFindSettings`, title, rail name, About page text
  and credit link, feedback subject.
- Core: window classes `SeamlessFindEverything`, `SeamlessFindPopup`, `SeamlessFindMsg`;
  mutex `Local\SeamlessFindRunning`; tray tips and command row say Seamless Find.
- Build helpers in `work\2026-11-12-listary-port\` (gen.py, spec.py, settings.yaml,
  assemble.py, glass-precheck.py, splice.py, check.py) now write the new names.
  Backups beside each as `.bak-<stamp>`.

## Also in this release

- Unload crash fix (shipped first in 1.1.2): the WIC factory and the Direct2D and DirectWrite
  objects are released before CoUninitialize. Before, the static destructor called into an
  unloaded windowscodecs.dll and crashed windhawk-mod.exe when the mod was turned off.

## Migration

Script: `scripts\2026-11-12-seamless-find-rename.ps1` (runs elevated).

1. Back up the old Mods key, its ModsWritable key (launch history and pause) and the 1.1.3
   source to `backups\2026-11-12\seamless-find-rename\`.
2. Install Seamless Find disabled, copy all Settings values and the LocalStorage values,
   and the Include/Architecture values.
3. Turn the old mod off, then the new one on (never both: both would grab Ctrl Ctrl).
4. Remove the old mod.

| Item | Old | New |
| --- | --- | --- |
| Mod id | local@seamless-listary | local@seamless-find |
| Name | Seamless Listary | Seamless Find |
| Version | 1.1.3 | 1.2.0 |

## Rollback

    Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-11-12-seamless-find-rename.ps1" -ArgumentList "-Action rollback"

It removes Seamless Find, re-imports both old keys, restores the 1.1.3 source, compiles and
enables it.

## 1.2.1: popup stuck on "Searching" after a launch

Seen at 3:19 pm in the live test: Enter on the Notepad row opened nothing, and every search
after it stayed on "Searching".

- Cause: launches ran on the popup's own thread. To start an app as the signed-in user the
  mod asks Explorer's desktop window to run it, which is a cross-process COM call. Explorer
  did not answer, so the thread sat in COM's wait loop. Sent messages (the test's queries)
  still ran there, but posted ones (Everything's results) were never read.
  Proof: a cdb stack of the mod process showed the UI thread in combase ModalLoop, called
  from the mod; Everything itself answered a direct test with 62 results.
- Fix (core.cpp): each launch runs on its own short thread (COM multithreaded there), which
  holds a reference to the mod so it can finish even if the mod is turned off. A good launch
  posts the path back to the popup's thread, which counts it for smart ranking. Opening the
  settings window still runs inline.
- Rule for later mods: never make a cross-process COM call on a mod's window thread.

## Result

- 3:16 pm: installed. Receipt: "INSTALL OK Lib=local@seamless-find_1.2.0_910185.dll settings=27
  stored=6". Old key gone. `tasklist /m` shows the DLL in its own windhawk-mod.exe. No
  Application error events. `settings-material.py check`: local@seamless-find ok.
- Backups and receipt: `backups\2026-11-12\seamless-find-rename\`.
- The Key Click thread (138571e3) was told the menu look block is already in, and that later
  menu or footer work now goes to local@seamless-find.

## Replaced (2026-11-12, 8:21 pm)

Seamless Find was replaced by **Seamless Explorer Search** (`local@seamless-explorer-search`
2.0.0, now 2.0.1) and removed. See `notes\2026-11-12-seamless-explorer-search.md`.
