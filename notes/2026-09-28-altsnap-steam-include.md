# AltSnap fork: Steam support, elevated windows, and the stale-session flakiness

2026-09-28. Status: live and verified on `local@alt-snap-drag` 1.2.2 (release
build). Follows `H:\System Configuration\notes\2026-09-28-altsnap-windhawk-fork.md`.

## What the user reported

"Alt+drag and the Alt+F/Alt+M shortcuts do not work on Steam client windows, on
T3 Code, and on elevated windows like Task Scheduler; AltSnap when run as admin
did work there. Make the fork work for every window, whatever the privileges."

## What was actually wrong (two separate things)

### 1. Steam: the engine never injects there by default

The Windhawk engine's built-in "well-known games" exclusion list contains
`?:\Program Files\Steam\*` and its `Program Files (x86)` twin (see
`ProcessLists::kGames` in the engine source, and the wiki page *Injection
targets and critical system processes*). No mod, including this one, can ever
load in `steam.exe` / `steamwebhelper.exe` until those paths are added to the
engine's **process inclusion list**, which overrides the exclusion list.

Fix applied (persisted in the registry, survives reboot/engine restart):

```
HKLM\SOFTWARE\Windhawk\Engine\Settings
  Include = winlogon.exe|logonui.exe|dwm.exe
            |C:\Program Files (x86)\Steam\*|C:\Program Files\Steam\*
```

Only the Steam client paths were added. Game installs
(`*\steamapps\common\*`, `C:\Program Files\Steam\*` is client-only here) stay
excluded: anti-cheat in the games themselves does not tolerate injection.
Applied by `scripts\2026-09-28-altsnap-steam-include.ps1 -Install`; rollback is
`-Rollback`. Backup and receipt in `backups\2026-09-28\altsnap-steam-include\`.

### 2. T3 Code and intermittent losses: stale mod sessions after engine restarts

Not a mod bug. After an engine restart, an already-running process can keep
`windhawk.dll` and the mod DLL loaded while its session is dead or only
partially re-initialized. The process still shows the module, but drag and
hotkeys silently do nothing until the process (or the engine) is re-initialized.
This is why it "worked earlier, then stopped": the previous setup restarted the
engine several times (`windhawk.exe -restart`), and T3 Code / Steam were
running across those restarts.

Two things follow from this:

- **On this machine `windhawk.exe -restart` also restarts explorer and can
  freeze a live T3 Code GUI** (the user reported this; only a T3 Code
  close+reopen recovered). Avoid engine restarts.
- A mod can be re-initialized **live**, without a service restart: the engine
  watches `HKLM\SOFTWARE\Windhawk\Engine\Mods` with `RegNotifyChangeKeyValue`
  and reloads mods in every process when anything under that key changes. Bump
  the mod key (e.g. `SettingsChangeTime`, or `LibraryFileName`) and the reload
  happens. This was used to test and to restore the release build.

### 3. Elevated windows were already fine

The engine service runs as LocalSystem and injects elevated processes normally.
Verified with an elevated `mmc.exe` (Task Scheduler): `windhawk.dll` and
`local@alt-snap-drag_1.2.2_1.dll` loaded, and the window carried the mod's
`Windhawk_Hooked_local@alt-snap-drag` property.

UIPI still means a lower-integrity process cannot move a higher-integrity
window itself (`SetWindowPos` fails with access denied), so per-process
injection - not external window manipulation - is what makes elevated windows
work. Nothing in the mod needed to change for that.

## Verified final state (release build, 2026-09-28 ~10:4x)

| Check | Evidence |
| --- | --- |
| Steam client injected | `steam.exe` (39684) and 4 `steamwebhelper.exe` carry `local@alt-snap-drag_1.2.2_1.dll`; Steam window (pid 20764, class `SDL_app`) `Hooked=true` |
| Steam hotkey | Alt+F toggled the Steam window maximized state, restore verified |
| T3 Code hotkey | Alt+F toggled with verified keyboard focus (`GetGUIThreadInfo` focus pid = T3 Code); debug log showed `keydown vk=46 mods=2` -> hotkey 0 match, action result 1 |
| T3 Code mouse | Alt+middle-click opened the mod's window menu; Alt+drag moved the window |
| Elevated window (Task Scheduler) | elevated `mmc.exe`: `windhawk.dll` + mod loaded, `Hooked=true` |
| New process coverage | fresh `notepad++.exe` launched mid-session got `windhawk.dll` + the mod at creation |
| No stale sessions | every process checked had the release revision; none left on the debug revision |

## How to change this setup later without breaking it

1. Write the registry value(s) elevated, then bump `SettingsChangeTime` on the
   mod key (or touch anything under `...\Engine\Mods`). The engine reloads mods
   live; do **not** run `windhawk.exe -restart` on this machine.
2. For a different mod DLL revision, copy the DLLs in and point
   `LibraryFileName` at the new name (the engine keeps old DLLs mapped).
3. After any engine restart or Windhawk update, a reboot is the clean way to
   get every process onto a fresh session.

## Rollback

- Steam inclusion: `scripts\2026-09-28-altsnap-steam-include.ps1 -Rollback`
  (removes the Steam entries, restarts the engine - expect explorer to restart).
- The debug revision used during diagnosis (`local@alt-snap-drag_1.2.2d_1.dll`,
  source `Windhawk\altsnap-fork\alt-snap.debug.wh.cpp`, build in
  `Windhawk\altsnap-fork\debug\`) is inert and unreferenced; its DLLs are still
  mapped in the Mods folders and can be deleted after a reboot.

## Artifacts

- `scripts\2026-09-28-altsnap-steam-include.ps1` (Audit/Install/Rollback)
- `reports\2026-09-28\altsnap-steam-include.log`
- `backups\2026-09-28\altsnap-steam-include\` - engine registry export before the
  change, mod-key exports before the debug install and before the release
  restore, install receipt, final-state receipt
- `Windhawk\altsnap-fork\alt-snap.debug.wh.cpp` (instrumented source used for
  diagnosis; not installed)
