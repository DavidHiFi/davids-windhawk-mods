# Seamless Explorer Search replaces Seamless Find (2026-11-12, now 2.0.5)

Owner order: replace the slow Windows Explorer search inside File Explorer windows, the job
Listary did for them. Rebrand to **Seamless Explorer Search**. No launcher (Halo Launcher does
that). A quick search box that pops up as you type, set up through the standard settings
window, with Everything doing the indexing so results are global.

id `local@seamless-explorer-search`, version 2.0.0, a tool mod (runs in windhawk-mod.exe).
It replaces `local@seamless-find` 1.2.0, which is removed.

## What it does

- Type a letter, digit or symbol in a File Explorer file list. A search box opens in that
  window, at the top or the bottom of the folder area, and the key you typed is its first
  character. Ctrl+F, Ctrl+E and F3 open it empty. The address bar, the search field,
  rename boxes and other apps never trigger it.
- Results come from Everything. When "This folder first" is on, the open folder and its
  subfolders are searched first (up to 30 hits) and placed on top, labelled "This folder".
  Results from every other drive follow.
- Enter on a folder opens it in the same window ("Open folders here"). Enter on a file opens
  it. Ctrl+Enter shows the item in its folder, selected. Tab or Right opens the menu: Open,
  Show in folder, Open in new window, Copy path, Copy file.
- Esc closes the box and hands focus back to the file list. Backspace on an empty box
  closes it too. The box closes when the window closes, minimises or loses focus.
- It stands down while Listary.exe is running, so the two never both answer a key.

## Removed from Seamless Find

The launcher: Ctrl Ctrl and the open hotkey, app launching and launch history, web keywords,
custom commands, the quick menu on the desktop, file dialog search and the path bar flash.

## Settings (standard settings window, template Launchpad 2.4.9)

| Page | Group | Settings |
| --- | --- | --- |
| General | In Explorer windows | Type to search, Search keys, Open folders here, Box position |
| General | Behaviour | Hide when focus moves away, Search as you type |
| Search | Everything | Result limit, Search time limit, Match the whole path |
| Search | Ranking | This folder first, Smart ranking |
| Appearance | Search box | Accent colour, Box opacity, Animations |
| Appearance | Settings window | Blurred settings window, Native title bar, Tray icon |

`settings-engine.py check` says in sync. The glass check (same test as
`settings-material.py check`) says ok. Manifest entry added to `docs\settings-engine.json`
(swap `L"Launchpad"` to `L"Explorer Search"`). Backup: `docs\settings-engine.json.bak-20261112-2018`.

## Engineering notes

- Explorer is asked for its folder and told to navigate only from worker threads (MTA COM,
  ShellWindows matched by window and tab). The UI thread never makes a cross-process COM
  call, so a busy Explorer cannot freeze the box or the hook.
- The keyboard hook has its own thread and acts only when the focus is the file list
  (`DirectUIHWND` or `SysListView32` under `SHELLDLL_DefView`) in a `CabinetWClass` window.
  It swallows the typed key and its key-up, and lets everything through when the UI thread
  has not answered for 3 s.
- Window classes `SeamlessExplorerSearchPopup`, `SeamlessExplorerSearchMsg`,
  `SeamlessExplorerSearchEverything`; mutex `Local\SeamlessExplorerSearchRunning`.
- Kept from Seamless Find: the `SeamlessMenuSkin` block and its Init and Uninit calls
  (asked for by the Key Click thread).
- Build: `work\2026-11-12-listary-port\build2.py` (source `src\es-head.cpp`, menu block from the
  installed Seamless Find, settings block from the engine-synced copy) and `check2.py`
  (compiles with Windhawk's clang, exit 0).

## Migration (done 8:21 pm)

Script: `scripts\2026-11-12-seamless-explorer-search-install.ps1`, run elevated.

1. Backed up the old Mods key, its ModsWritable key and the 1.2.0 source to
   `backups\2026-11-12\seamless-explorer-search\`.
2. Old mod off. New mod installed through `Install-StagedMod.ps1` (template check passed).
3. Copied the 12 settings both mods share (hide on focus lost, search as you type, result
   limit 60, time limit 200 ms, match path, smart ranking, accent #89B4FA, opacity 90,
   animations, the three settings-window options) and the 6 settings-window position values.
   Launcher settings and the dropped `settingsTitleButtons` stayed behind.
4. New mod off and on to restart it with the copied values, then
   `windhawk-cli mod remove local@seamless-find`.

| Item | Old | New |
| --- | --- | --- |
| Mod id | local@seamless-find | local@seamless-explorer-search |
| Version | 1.2.0 | 2.0.0 |
| Library | local@seamless-find_1.2.0_910185.dll | local@seamless-explorer-search_2.0.0_998759.dll |

Rollback: run the same script elevated with `-Action rollback`. It removes the new mod,
re-imports the old keys, restores the 1.2.0 source, compiles it and turns it on.

## Listary retired (2026-11-13, 12:43 am)

Listary came back at the 10:40 pm logon through its own scheduled task `\Listary`
(`"C:\Program Files\Listary\Listary.exe" --startup`, run level Highest). While Listary runs the
mod stands down, so the first live test (12:13 am) only showed Listary's own popup.
This mod replaces Listary's Explorer search, and Halo Launcher and Flow Launcher cover the
launcher side, so Listary was retired. It is still installed.

Script: `scripts\2026-11-13-retire-listary.ps1`, run elevated.

| Item | Old | New |
| --- | --- | --- |
| Task `\Listary` | Ready, runs at logon | Disabled |
| Listary.exe | running (pid 8976) | ended |

Backup: `backups\2026-11-13\retire-listary\Listary-task.xml`.
Rollback: run the script elevated with `-Action rollback` (it re-enables the task and starts it).

## Explorer launcher crashes (not this mod)

Crash Watch logged `explorer.exe` exits with 0xc0000005 at 9:45, 9:46, 9:50, 9:51 and 9:53 pm,
then at 12:13 am and 12:37 am. The 12:13 am one was the short-lived `explorer.exe <folder>`
launcher process that the first test started. This mod is a tool mod (Include
`windhawk-mod.exe`) and loads nothing into explorer.exe, so the crashes come from somewhere
else. The test now opens its folder through ShellExecute instead.

## Live test, take 3 (2026-11-13, about 1:00 am): failed, fixed in 2.0.1

- Typing "alpha project" opened the box, and it took the keyboard (Explorer's caption went
  grey). About 250 ms later the keyboard went back to the Explorer window and the box hid.
- The rest of the typed keys then reached Explorer's own type-ahead, and the test's Enter
  opened `alpha notes.txt` in Notepad++. Only that tab was closed; Notepad++ stayed open
  because it holds the owner's session.
- The test now stops before Enter unless the box has the keyboard, and logs every
  foreground change and every key.
- The window manager (local@seamless-window-manager 2.5.5) was read for a cause: focus
  follows the mouse is off ("windows"), the box is a tool window so it is never tiled, and
  its foreground handler only refreshes opacity. It does not take focus back by itself.
- Take 2 ran without holding the desktop lock (a piped lock command hid its failure). Lesson
  saved to memory; the runner now checks the lock output.

## 2.0.1 (2026-11-13, 5:48 am)

- Focus lost: the box waits 60 ms before it hides. If, within 1 s of opening, the keyboard
  went straight back to its own Explorer window without a mouse click, the box takes it
  back (at most twice per opening). A click elsewhere or another app still closes it at once.
- Why the box closed, and keys that went past it in the 3 s after it opened, are written to
  Windhawk's log and to the mod value `diag`, so the next live test names the cause.
- Build: `build2.py` now takes the menu block and the settings block from the installed
  Explorer Search source (Seamless Find's source is gone). Diff against 2.0.0: only the
  version line and the focus changes. Compile check exit 0, `settings-engine.py check` in
  sync, glass check ok.

| Item | Old | New |
| --- | --- | --- |
| Version | 2.0.0 | 2.0.1 |
| Library | local@seamless-explorer-search_2.0.0_998759.dll | local@seamless-explorer-search_2.0.1_721663.dll |
| Process | windhawk-mod.exe pid 9852 | pid 7404, started 5:48 am |

Backup: `backups\settings-material\local@seamless-explorer-search-20261113-0548.wh.cpp` (and the
registry key beside it).

## Live test, take 8 (5:57 am): the real cause

The 2.0.1 log named it: "closed, folder view changed". The box's 250 ms watch asked
`IsWindowVisible` of the folder view, and Explorer leaves `WS_VISIBLE` off the `CtrlNotifySink`
window above `SHELLDLL_DefView` while the files show (probe: true at 0.4 s after the window
opened, false from 0.5 s on, files on screen the whole time). So the box closed itself on its
first watch tick. Windows then activated the bare Explorer frame with no focused child, and
the hook rightly let the rest of the keys past ("focus not on the file list"). The window
manager was not involved.

## 2.0.2 (10:43 am)

- The watch checks that the view still exists, has its own `WS_VISIBLE`, and that its tab is
  the one showing (`ViewShown`). The Ctrl+F fallback that looks up the view uses the same rule.
- When the box hides while it holds the keyboard, it hands focus back to the Explorer window
  the way Esc does, so typing never lands on the bare frame.
- The 2.0.1 bounce guard and the `diag` log stay.

| Item | Old | New |
| --- | --- | --- |
| Version | 2.0.1 | 2.0.2 |
| Library | local@seamless-explorer-search_2.0.1_721663.dll | local@seamless-explorer-search_2.0.2_463547.dll |
| Process | pid 7404 | pid 19072, started 10:43 am |

Backup: `backups\settings-material\local@seamless-explorer-search-20261113-1043.wh.cpp`.
Rollback: install that file with `scripts\Install-StagedMod.ps1` (`-BaseHash` = hash of the
live source), run elevated.

## Live test, take 10 (10:45 am): 11 of 15

The box now opens, sits in the window and keeps the keyboard. Two causes left:

- After a folder opens in the window, Explorer's new folder view has no `WS_VISIBLE` of its own
  either (probe through Shell COM, no keys: old view `+`, new view `-` for the whole 6 s). So the
  Ctrl+F box closed on its first watch tick ("closed, folder view changed"), and Ctrl+Enter
  never reached it.
- When the box hides, Explorer's frame comes forward but keeps the keyboard on itself, not on
  the file list. Typing then went nowhere ("focus not on the file list: CabinetWClass").
- The test's Enter check wanted the title "Alpha project"; this PC shows the full path. The
  folder did open.

## 2.0.3 (10:52 am)

- A view counts as shown while it exists and sits in the tab that is showing. Style bits are
  no longer read.
- When the box hides and hands the keyboard back, a job thread waits for the Explorer frame to
  come forward and, only if the frame holds the keyboard itself, puts it in the file list
  (`AttachThreadInput` plus `SetFocus`, on its own thread so a hung Explorer cannot hold the box).
- Test: the Enter check accepts the full-path title, a new check that the files have focus after
  a folder opens, and a stop before Ctrl+Enter unless the box has the keyboard.
- Compile check exit 0, `settings-engine.py check` in sync, glass check ok.

| Item | Old | New |
| --- | --- | --- |
| Version | 2.0.2 | 2.0.3 |
| Library | local@seamless-explorer-search_2.0.2_463547.dll | local@seamless-explorer-search_2.0.3_179432.dll |
| Process | pid 19072 | pid 38192, started 10:52 am |

Backup: `backups\settings-material\local@seamless-explorer-search-20261113-1051.wh.cpp`.
Rollback: install that file with `scripts\Install-StagedMod.ps1` (`-BaseHash` = hash of the
live source), run elevated.

## Live test, take 11 (10:52 am): 15 of 16

Every focus check passed: Enter opened the folder, the files had focus after it, Ctrl+Enter
selected `alpha plan.txt`, typing again opened the box, Esc gave the keyboard back to the files.
The one miss: the window opened narrow this time (629 px), and with the folder tree open the
file list was narrower than the box's minimum width, so the box hung 13 px past the window's
right edge (it was kept on screen only).

## 2.0.4 (10:54 am)

- The box never gets wider than the Explorer window (visible frame, less the margin), and it is
  kept inside that frame. In a narrow window it may cover the folder tree.

| Item | Old | New |
| --- | --- | --- |
| Version | 2.0.3 | 2.0.4 |
| Library | local@seamless-explorer-search_2.0.3_179432.dll | local@seamless-explorer-search_2.0.4_974870.dll |
| Process | pid 38192 | pid 23560, started 10:54 am |

Backup: `backups\settings-material\local@seamless-explorer-search-20261113-1054.wh.cpp`.

## Live test, take 16 (11:02 am): 15 of 16

The box now fits the narrow window (box 2108 to 2528, window 1918 to 2547). Esc closed the box
but the keyboard stayed on the Explorer frame: a race. Explorer handles its own activation after
the frame is already in front, and its handler put the keyboard on the frame after the hand-back
had set it on the list (take 11 won the race, take 16 lost it).

## 2.0.5 (11:04 am)

- The hand-back first lets Explorer finish what it has queued (`WM_NULL` with a 200 ms timeout,
  aborting if Explorer hangs), then watches for 600 ms and puts the keyboard back in the list each
  time the frame takes it. It stops as soon as the list keeps it for three checks, or the
  moment Explorer puts the keyboard anywhere else (address bar, rename box).

| Item | Old | New |
| --- | --- | --- |
| Version | 2.0.4 | 2.0.5 |
| Library | local@seamless-explorer-search_2.0.4_974870.dll | local@seamless-explorer-search_2.0.5_543757.dll |
| Process | pid 23560 | pid 12124, started 11:04 am |

Backup: `backups\settings-material\local@seamless-explorer-search-20261113-1104.wh.cpp`.
Rollback: install that file with `scripts\Install-StagedMod.ps1` (`-BaseHash` = hash of the
live source), run elevated.

## Live tests, takes 20 and 21 (11:05 and 11:07 am): 16 of 16, twice

Both runs on 2.0.5 passed every step: type to search, box inside the window with the keyboard,
Enter opens the folder in place, files have focus after it, Ctrl+F, Ctrl+Enter selects
`alpha plan.txt`, typing again, Esc hands the keyboard back to the files, Backspace on an empty
box, and the address bar never opens it. No browser was started by either run.

Proof (take 20, cropped to the Explorer window): `work\2026-11-12-listary-port\proof\explorer-search-2.0.5.mp4`,
`explorer-search-2.0.5.gif` and stills. The demo folder, the test helpers in `C:\Users\Public` and
the staged copies were deleted afterwards.

## Test side effect: Helium opened on http://abc/ (10:46 am)

The test's last step types "abc" in Explorer's address bar to prove the box stays shut, then
pressed Esc twice and closed its window. At 10:46:20 am (end of take 10) Explorer started the
owner's Helium browser with `http://abc/` (process parent explorer.exe). Take 11 likely added a
second such tab. That Helium window then sat in front and takes 12 to 15 stopped at their
first check, typing nothing. The test now deletes the text before it leaves the address bar.
The Helium window was left alone: it is the owner's browser and may hold their own tabs now.
Rollback: install that file with `scripts\Install-StagedMod.ps1` (`-BaseHash` = hash of the
live source), run elevated.
