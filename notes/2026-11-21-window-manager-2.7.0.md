# Seamless Window Manager 2.7.0 (2026-11-21)

Owner asked for three things, answers all on the recommended options:

1. New windows tile at a sensible size. Screenshot: Startup Control squeezed into a thin
   column on the right beside full-screen Black Ops 2.
2. No fade-in when focus jumps by hotkey (Alt+arrows and the other jump keys).
   Real Alt+Tab keeps its zoom.
3. A key to cycle through windows hidden behind the ones in front.

## Audit (2.6.7)

- A new window was inserted next to the last focused tile and the row was shared equally.
  With three windows in a row that is a third of the screen; with windows the owner cannot
  see (sitting behind a full-screen game) still holding tiles, the new one ended up as a
  thin column beside them.
- Over a full-screen game the new window was tiled into a layout nobody could see.
- The fade came from Windows Animations, not from this mod: its focus watcher cloaks the
  newly focused window and fades it in, unless a switcher has marked the change as its own.
- Alt+PageDown only reached windows that overlapped the active one directly and pushed the
  active window to the bottom, so the order shuffled after each press and windows fully
  covered by other windows were skipped.

## Change

- New windows split the biggest tile in half, along its long side (a wide tile splits
  side by side, a tall one top and bottom). A tie goes to the window last focused.
- A new window that opens while a full-screen app is up on that monitor floats centered
  (3/5 wide, 3/4 tall) on top. Once a second it checks again; when the full-screen app is
  gone it joins the tiles the same way.
- Fade: the mod now keeps the switcher note window Windows Animations already reads (the
  same one its own switcher protocol uses). Every focus jump the mod makes marks it just
  before switching, so Windows Animations skips the fade for that jump only. Real Alt+Tab
  never marks it, so its zoom stays. No change to Windows Animations was needed.
- Alt+PageDown ("Bring up a hidden window") walks a fixed list made when the walk starts:
  the active window first, then every window behind it front to back that it overlaps or
  that is at least half hidden by the windows in front. Each press focuses the next one,
  wrapping round. Alt+PageUp ("Go back up the hidden windows") walks back. Nothing is
  pushed to the bottom any more.

## Files

- Work copy: `work\2026-11-21-window-manager\local@seamless-window-manager.wh.cpp`
- Old source kept: `work\2026-11-21-window-manager\2.6.7-installed.wh.cpp`
- Test PC job: `D:\Agent Work\swm-270\` (driver, setup, test, results)

## Rollback

Reinstall the old source, elevated, under `coop lock windhawk-engine`:
`scripts\Install-StagedMod.ps1 -Id local@seamless-window-manager -Staged
work\2026-11-21-window-manager\2.6.7-installed.wh.cpp -BaseHash <hash of the live 2.7.0 source>`.
The install script also leaves `ModsSource\local@seamless-window-manager.wh.cpp.bak-<stamp>`.

## Verification

### Test PC first load (2026-11-22, 5:10 am): 16 of 16 passed

Clean rewind point, Windhawk 1.7.3, the 2.7.0 build compiled 64 and 32 bit with no
warnings. Driver and checks in `D:\Agent Work\swm-270\` (results in `results\out\`).

- First window took the whole work area; the second halved it; the third split the
  second's tile (all three at least 38% of the screen each way, none thin, no overlap).
- Alt+arrow moved focus and marked the switcher note (token 33 to 34), so no fade.
- A full-screen window was left alone; a window opened over it floated centered
  (512,363 against a centre of 512,360) and the tiles behind did not move.
- Alt+PageDown walked game > C > A > B and back to the front window; Alt+PageUp went back
  one; every jump marked the note (token 34 to 40).
- Once the full-screen window closed, the floating window joined the tiles (2x2, no overlap).
- Explorer stayed up, no application errors.

Fresh VM quirk, not a 2.7 bug: on a just-installed Windhawk the tool helper
(`windhawk.exe -windhawk-tool-mod`) did not start after the reboot. Turning the mod off and
on (Disabled 1 then 0 with SettingsChangeTime) started it at once. The run script does this.
Also turn the permission prompt and lock screen off in the VM first: a prompt on the secure
desktop leaves no input desktop and every capture fails.

### Tower (2026-11-22, 5:25 am)

- Installed with `Install-StagedMod.ps1` under the engine lock: registry 2.7.0, live source
  hash matches the work copy (EB176A28...), backup
  `local@seamless-window-manager-20261122-0523.wh.cpp`.
- Published: davids-windhawk-mods 6f96df0, seamless-workshop feed 6fe5a9e.
- One helper (`windhawk-mod.exe -windhawk-tool-mod`) restarted at 5:25:24 am on the new
  build; Explorer and about a hundred apps hold 2.7.0; no application errors after install.
- Hand test on the tower, first pass (under the desktop lock, elevated script
  `C:\Users\Public\swm-hand\hand.ps1`): a new 500x400 window took 49% x 98% of the work
  area (a proper half, not a thin column); the switch note window exists and belongs to
  our helper; the owner's front window was put back afterwards.
- Still open on the tower: the Alt+PageDown / Alt+PageUp walk and the note token rising.
  The second pass is queued for the screen (ninth in line at 2026-11-22). The test PC run
  above passed both.
