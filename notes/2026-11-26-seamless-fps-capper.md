# Seamless FPS Capper (local@seamless-fps-capper)

2026-11-26. A Windhawk tool mod that takes over RivaTuner's frame limiter job.
Work folder: `work\2026-11-26-fps-suite\capper\` (state in `STATE.md`, proof in `proof\`).
Report: `work\2026-11-26-fps-suite\reports\capper.md`.

## What it does

- In-game cap, loaded only into games on its list (Games page slots or game folders).
  Ways: async, front edge, back edge, Reflex (falls back to async where Reflex is missing).
- Never loads into Plutonium or anti-cheat games (written to ExcludeCustom, exclude wins).
  Those get the NVIDIA driver cap instead.
- Driver cap through NVAPI profiles, only while "Let this mod set the NVIDIA driver cap" is on.
  Every value it changes is recorded first and mirrored to
  `%ProgramData%\SeamlessFpsCapper\driver-undo.txt`. Turning the setting off, turning the mod
  off or removing it puts every recorded value back.
- Hotkey Ctrl+Alt+Shift+/ (Afterburner's limiter key), tray click toggles, raise/lower/preset keys.
- Universal settings window copied from Seamless AutoClicker.

## Changes on the tower

### Mod install
- 1.0.0 installed through `Install-StagedMod.ps1`. It made no driver write: no
  `driver-undo.txt` exists, and the dump in `capper\proof\drs-after-install.json` matches
  `drs-before-install.json` (global 157, Plutonium profile 120).
- 1.0.1: game list now saves on Windhawk 1.7 (32-bit tool host read the wrong registry view),
  and a new install defaults to way = async with the driver cap off.
  Defaults moved on the tower only where they still held the 1.0.0 defaults:
  - old: mode=driver, driverCap=1
  - new: mode=async, driverCap=0
  - rollback: set them back in the mod's settings, or `Set-ModState.ps1 -Id local@seamless-fps-capper -Off`.

### 1.0.0 never really ran on the tower
- Found at 8:30 am: no capper tool process existed. Windows still splits rights here (UAC prompts are
  off, not UAC itself), so Windhawk 2.0's normal tool helper runs without admin. 1.0.0 then restarted
  itself as admin without the switch 2.0 needs, and the copy quit. That is also why it never wrote to
  the driver.
- 1.0.1 lists Windhawk 2.0's admin tool helper the way every working admin tool mod here does (Seamless
  Firewall, Startup Control, Seamless Taskbar), and only restarts itself as admin on Windhawk 1.7.
- Because 1.0.1 is the first build whose tool really starts, the defaults move to async with the driver
  cap off before the install, not after it.

### Live proof on the tower (9:16 to 9:30 am)
- Every way of capping held 60 on the test app (async, front edge, back edge, Reflex fallback,
  D3D9, D3D12, OpenGL, 32-bit). The per-game cap of 45 won over the global 60 and averaged 43.
- The on/off key and the tray click both turned the cap off and back on.
- An anti-cheat style name was never loaded into, alone or inside a listed folder.
- The driver cap on the test exe's own profile measured 50, then was taken off again.
- The driver dump at the end equals the one from 8:50 (global 157, Plutonium 120). Every mod
  setting is back as it was, the mod's driver cap is off and no undo list is left.
- Proof files and numbers: `capper\proof\tower\`, written up in `reports\capper.md`.
- Temporary changes, all undone: test exes in `C:\Users\Public\fpcbin` and `fpcgames`, scheduled
  tasks `fpc-tower-proof` and `fpc-folder`, test values in the mod's settings. All removed.
- Catch: a folder added to the mod takes Windhawk a few seconds to pick up. A game started right
  after can run uncapped until restarted.

### Why these defaults
RivaTuner on this tower caps nothing: Global Framerate Limit=0, limiter type async
(SyncLimiter=0), no per-game caps (per-game profiles only hold OverrideDXGI and Hooking).
The owner's real caps live in the NVIDIA driver (global 157, Plutonium 120), and the mod leaves
those alone. So the copied defaults are: way async (RivaTuner's type), cap 157 (the cap the owner
actually runs), Plutonium kept in slot 1 at 120 (inert while the driver cap is off), no game listed
for the in-game cap. The mod does nothing until a game is listed or the driver cap is turned on.

### MSI Afterburner limiter key
- File: `C:\Program Files (x86)\MSI Afterburner\Profiles\MSIAfterburner.cfg`
- old: `LimiterToggleHotkey=000700BFh` (Ctrl+Alt+Shift+/)
- new: `LimiterToggleHotkey=00000000h` (none), so the mod owns that key.
- Backup: `MSIAfterburner.cfg.bak-20261126-0726` beside it. Only that line differs.
- Rollback: close Afterburner, copy the backup over `MSIAfterburner.cfg`, start it again
  (`schtasks /run /tn MSIAfterburner`).
- Afterburner was restarted minimized; RivaTuner kept running (same process). GPU tune untouched.
- Log: `capper\proof\afterburner-hotkey.log`.

## Rollback of the whole mod
`scripts\Set-ModState.ps1 -Id local@seamless-fps-capper -Off`. That restores any driver value it
changed. If the mod is already gone, the undo list in `driver-undo.txt` names every old value.
