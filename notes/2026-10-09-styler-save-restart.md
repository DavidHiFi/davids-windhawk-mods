# 2026-10-09: styler save-settings restarts the interface (2.0.7)

User ask (verbatim intent): saving the styler's settings changed nothing you
could see; closing to tray and reopening left the window bugged. They want the
1.x behavior back: on save, Windhawk closes and reopens its interface, with an
option to turn that off.

## What shipped

`local@windhawk-styler` **2.0.7** (live DLL
`C:\ProgramData\Windhawk\Engine\Mods\64\local@windhawk-styler_2.0.7_597474.dll`,
Include `windhawk-ui.exe` verified after every compile). Source of truth:
`work\windhawk-styler\tauri20\windhawk-styler.wh.cpp`, synced and compiled
through `windhawk-cli mod compile`.

- **Save watch (the fix).** Every worker cycle the mod reads the engine's
  `SettingsChangeTime` marker on its own mod key (`HKLM\...\Mods\local@windhawk-styler`)
  and, on a bump, requests a close+reopen through the existing mutex-guarded
  PowerShell helper (`Wh_ModSettingsChanged` stays wired as the fast path). Took
  about 1 s from a registry write to both processes logging `save marker bump`.
- **The option.** New setting `restartOnSave` (default ON), display name
  "Restart the interface on save" in the mod's Settings tab. OFF = the
  interface stays open and changes apply live (the per-cycle CSS/DWM push already
  does this; verified: a color write turned the page pink within one cycle while
  the restart path was still gated off).

## The trap this surfaced

The 2.0 pre-alpha reads a **never-saved boolean as 0** instead of the schema
default. First test: the marker bumped, both processes saw it, and nothing
restarted because `restartOnSave` (no value in the key yet) read false.
Materializing it as `REG_DWORD 1` made the same marker-only bump restart the
interface immediately. Two layers of fix:

1. The value is materialized ON in the live key
   (`...\Mods\local@windhawk-styler\Settings\restartOnSave` = 1).
2. `ReadBoolSetting()` reads the boolean directly with fallback-to-true at
   read time (DWORD and REG_SZ forms), so a fresh install defaults ON without
   depending on the schema-default behavior.

Also in 2.0.7: ownership for the restart relaxed to "the visible window's
process, else whichever process holds the hidden one" (a save with the
interface in the tray still restarts), and the helper itself is unchanged
(mutex + 4 s cooldown + restart2 fallback).

## Verified live (all measured tonight)

- 01:14:47 marker-only bump -> both pids log the bump -> `26876` spawns the
  helper -> RUN 01:14:49 -> pair `30272,18200` -> `18200,30272` swap -> port
  9333 LISTENING -> page already themed (styleLen 1656) a minute later.
- 01:17:16 full save (accent `#f5c2e7` -> `#89b4fa` + bump) -> bump detected
  < 1 s -> helper RUN 01:17:19 -> pair swap -> port up at ~14 s -> page shows
  `rgb(137,180,250)` (#89b4fa) with the veil, background rgba(30,30,46,0.75),
  FiraCode Nerd Font. Current live pair `39888,3008`, browser pid 29768.
- Live-apply without a restart: the pink accent write took effect on the page
  within one cycle while restarts were still off.

## Rollback

- `scripts\2026-10-09-styler-save-restart.ps1 -Rollback` restores the 2.0.6
  source, deletes the `restartOnSave` value, and recompiles.
- Backups in `backups\2026-10-09\styler-save-restart\`: the pre-change mod key
  (`mod-key-pre-2.0.7.reg`, 2.0.6 rev 647557), the 2.0.6 ModsSource, and the
  2.0.6 DLLs.

## Related state on the machine

- Whatever thread shipped styler 2.0.5 (00:11, "sheet veil") and 2.0.6
  (00:18) did not leave coop notes; my note to them sits on the board.
  The avatar/veil/acrylic line of work is theirs and untouched here.
- The old `windows-11-taskbar-styler` (taskbar) is a different mod and was
  not touched.
- Chain of deploys tonight: 2.0.6 rev 647557 -> 2.0.7 rev 369937 (first
  build) -> 2.0.7 rev 597474 (with ReadBoolSetting).
