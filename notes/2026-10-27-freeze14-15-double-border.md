# Freezes 14 and 15: two border systems at once (2026-10-27)

## What happened (measured)
- `reports\caption-dwm-guard.log`: DWM stalled 10.6 s at 10:12:29 AM and 10.9 s at 10:19:50 AM. The guard killed dwm.exe both times, the screen went black and the owner hard-reset (Kernel-Power 41 at 10:13 AM and 10:20 AM).
- `local@window-borders` `SettingsChangeTime` read 10:11:14 AM with `Disabled=0`. It had been switched off at 7:56 AM when `window-ring.exe` took over the borders (`backups\2026-10-27\window-borders\window-borders-disabled-before-ring-app.txt`). So from 10:11 AM both the mod and the ring app drew a border on every window.
- After the 10:13 AM restart both came back up (ring app and Windhawk), and the second stall followed six minutes later.
- caption-buttons-customizer was already off for the second stall (guard set it at 10:12:32 AM), so it is not the cause of that one.
- The only mod loaded in dwm.exe at 10:26 AM: custom-corner-radius.

## Cause (inferred from timing, not proven)
Two border systems on every window. Both stalls came within minutes of that state starting. Other changes in the same window: the settings-styler-plus and remove-uwp-title-bars-plus work in ApplicationFrameHost (10:09 AM install, 10:17 AM toggle). remove-uwp-title-bars-plus is off.

## Fix (10:30 AM)
- `local@window-borders` `Disabled=1`. Backup: `backups\2026-10-27\freeze-lockdown\window-borders-before-off.reg`. Script: `work\2026-10-27-freeze-lockdown\window-borders-off.ps1`.
- Rules added to every agent's global rules (`H:\System Configuration\agent-tools\AgentRules\global.md`, rendered to Claude, Codex, OpenCode and Gemini) and posted to all threads with `coop note`.

## Owner's two asks, done the safe way
- Border on the Windhawk window: `window-ring.exe` no longer excludes `windhawk-ui.exe` (`bin\window-ring.ini` `exclude=`; old copy in `backups\2026-10-27\freeze-lockdown\window-ring.ini.before`). No mod is injected; the ring is a separate window. Measured at 10:35 AM: ring windows at 68,68 to 1324,1424 around the Windhawk window at 71,71 to 1321,1421.
- Centered title in the Windhawk window: the Windhawk Styler paints that title itself, so Caption Buttons Customizer (which works inside DWM) cannot move it. Styler 2.0.83 adds `centerTitle` (on): the text sits on the window center with the icon 5 px before it. It runs only in windhawk-ui.exe and touches nothing in DWM. Deploy: `scripts\2026-10-27-styler-2.0.83-deploy.ps1` (`-Rollback` restores 2.0.82). Screenshot: `reports\2026-10-27-windhawk-centered-title\2026-10-27-windhawk-titlebar-screen.png`.

## Rollback
- Border mod: `reg import backups\2026-10-27\freeze-lockdown\window-borders-before-off.reg` (do not, while window-ring.exe runs).
- Ring: copy `window-ring.ini.before` back over `bin\window-ring.ini`, then `window-ring.exe --stop` and start it.
- Styler: run the deploy script with `-Rollback` elevated.
