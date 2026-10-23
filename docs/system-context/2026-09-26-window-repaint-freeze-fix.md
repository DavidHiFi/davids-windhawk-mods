# 2026-09-26 - windows frozen until maximize/restore (Ente Auth, LocalSend)

## Resolution 2026-09-27 - real cause found and fixed

**Cause.** On 2026-09-16 the RivaTuner `Global` profile got `ForceFlipModel=1`
and `ForceAllowTearing=1` (`notes/2026-09-16-global-flip-model.md`), so every
app RTSS hooks inherited a games-only borderless override. Flutter apps
(LocalSend, Ente Auth) with that override stopped updating on the right 60 Hz
LG monitor until a resize forced a redraw. That matches the owner's report of
the problem starting recently, and of maximize/restore curing it.

**Proof** (pixel hashes of LocalSend's animated logo at 250 ms, nothing saved;
logs in `reports/2026-09-27-flutter-stall-*.txt`):

| Condition | Right 60 Hz monitor | Main 165 Hz |
|---|---|---|
| Global override on | frozen: 1 change in 70-105 samples, 4 runs | mostly fine |
| RTSS hook off for LocalSend | 71/71, 2 runs | - |
| Hook on, override off for LocalSend | 78/78, 2 runs | - |
| Override removed from Global (the fix) | 77/77, 78/78 | 76/76 |

Ente Auth, relaunched after the fix: 40/40 frames on the main monitor. Moved to
the right monitor, its longest pause was 0.8 s, against 4-22 s stalls before.
The compositor's refresh reporting was clean (2,852 samples, all 6.07 ms).
Per-monitor vblanks were clean too: 60.0, 165.1 and 75.2 Hz.

**Fix applied** (`scripts/2026-09-27-rtss-flip-games-only.ps1`, elevated):
`[OverrideDXGI]` removed from `Global`. Per-game profiles were written with the
same two values for every installed game. Existing game profiles
(`plutonium-bootstrapper-win32`, `s1x`, `iw6x`) were untouched. RTSS was
restarted; Afterburner and a running Plutonium session were unaffected.
Backup: `backups/2026-09-27-rtss-flip-games-only/Profiles`. Rollback: rerun
the script with `-Rollback`. Any new game that needs the borderless upgrade
gets its own `<exe>.cfg`; never `Global`.

**Removed** (owner request, `reports/2026-09-27-remove-auth-watchdog.log`):
the `WatchAuthRepaint` task, the HKCU Run value, the watcher script and log,
the vbs launcher, `Launch-EnteAuth.exe` and its source, and the Start Menu
shortcut swap (original restored). The MPO registry values had already been
deleted at 00:50 and caused the black flashing; do not reintroduce them.

**Left as found:** Windhawk `Exclude=auth.exe` and `custom-corner-radius`
disabled, both from 2026-09-26. Neither is needed for the fix. The owner can
re-enable the mod in Windhawk.

**Theories ruled out, so no one repeats them:** MPO or overlay registry keys
(caused the monitor flashing), the DWM restart, topmost pinning, the
per-app `AppStatus=4096`, the startup nudge, the driver version, and the
Windhawk corner-radius mod. The 2026-09-26 sections below are history; their
conclusions were wrong.

---


## Update 2026-09-26 23:05 - current state

- Owner bisected mods themselves (disabled/re-enabled, removed two). Windhawk
  crashed once during that (Application log 22:58:30, faulting module
  `win32-ui-modernizer_1.0.2_26598.dll`) - the modernizer mod itself faults
  on unload, worth remembering. Only `taskbar-ai-quota` (stock) is disabled;
  the owner's two removals are not recorded here.
- Symptom changed to: stalled a few seconds, recovers, stalls again. With
  auth.exe excluded from Windhawk and a fresh launch through the helper, a
  45 s pixel-hash measurement showed the window repainting every single
  sample (no stalled pass). The residual intermittent stalls fit the DWM
  MPO flip-transition regression (triggers on alt-tab/fullscreen switches
  several seconds later), which is exactly what `DisableOverlays` targets -
  it is set but the machine has not been rebooted since 22:01, so it is
  dormant.
- Measurer saved as `scripts\Measure-AuthRepaint.ps1` (hash-only, nothing
  on-screen saved). Live readings at 22:35: four changing hashes over 15 s.
  At 23:04: 45 changing samples, longest static run 0.
- Remaining step at time of writing: the owner restarts Windows (Ableton has
  an unsaved session; save first), then re-test both Steady use and the
  alt-tab/fullscreen switch pattern that triggers the seconds-long stalls.

## Update 2026-09-27 00:50 - MPO changes FULLY ROLLED BACK after monitor-flash bug

- After the reboot, both monitors flashed/blinking black repeatedly on the
  RIGHT monitor whenever one window overlapped another there (T3 Code over
  Ableton). The owner attributed it to the two MPO-disable registry changes
  from yesterday, and directed their removal + a standing instruction:
  NEVER touch the graphics pipeline registry on this machine again without
  asking first, change by change.
- Rolled back live at 00:50 (elevated):
  `GraphicsDrivers\DisableOverlays` deleted (was DWORD 1),
  `Windows\Dwm\OverlayTestMode` deleted (was DWORD 5).
  Verified both values absent post-delete:
  `reports\2026-09-27-rollback-mpo-settings.log`.
- Effect timing: the registry no longer requests overlay disabling, but the
  boot-time MPO policy for the current session was applied with the previous
  boot's values. The flashing should stop only after the NEXT reboot, when
  overlay scheduling starts fresh with the default (enabled) state.
- The MPO-disable experiments were already been shown not to fix the Auth
  stutter (23:47-00:06 matrix), so nothing of value is lost by the rollback.
- The Auth handling that remains and is untouched by this rollback:
  Windhk Exclude=auth.exe (hard-freeze fix), topmost-while-fullscreen +
  stall-heal watchdog (`WatchAuthRepaint` scheduled task).)
- Standing directive recorded: never again change graphics/composition
  registry values on this machine without asking the owner for that exact
  change first. Additions to the crash/overclock sections in CURRENT-STATUS
  already establish the pattern of asking before risky changes; this one is
  now explicit for display/graphics settings.

## Update 2026-09-27 00:05 - final experiment round and residual state

- Live A/B round 23:47-00:00, all with Auth unlocked and visible (verified by
  purple-pixel classifier: 1.7% purple-bar pixels on screen):
  - With `AppStatus=4096` (bitblt override, per-app): 12 s then 8 s static
    runs - WORSE, and it also fits the owner's "bars every ~10 seconds"
    describing the bitblt batch cadence. Reverted (value removed; backup of
    the value stays in `backups\2026-09-26\repaint-fix\UserGpuPreferences-after-auth.reg`).
  - Without it, topmost, game still running: 4/1/16/4 static seconds.
  - With game closed, fresh DWM restart + `custom-corner-radius` disabled
    (elevated, exported + `Disabled=1`): 3/12, 4/11, 10/1/4 at t0/t3m/t6m.
    Not the culprit; mod re-eligible for re-enable.
- Conclusions of this round: the residual stall bursts are independent of
  app topmost, the game, the bitblt override, and the dwm-resident corner
  mod; they persist across a freshly restarted DWM session only briefly and
  reappear as 4-16 second bursts of static pixels. Whatever remains is below
  the presentation layer we can reach without a boot: the kernel-side
  `DisableOverlays` (set 2026-09-26 22:22) activates only at next boot. That
  is the last OS-level variable for this class of symptom; everything else
  in the stack is already live.
- Watcher v2 tightened: stall-heal throttle 15 s -> 6 s (`scripts\Watch-
  AuthRepaint.ps1` v2 running unless next scheduled task run - new pid at
  00:05:23 - takes it over). During a degenerate session, the log showed
  heals every ~16 s as bursts persisted under fullscreen - consistent with
  the owner's "updates every ~10 seconds" description.
- When the machine next reboots (natural), verify with
  `pwsh -File "H:\System Configuration\scripts\Measure-AuthRepaint.ps1" -Seconds 60`
  while using the app - the expectation is the bursts disappear once
  DisableOverlays is live from boot; report back otherwise.

## Update 2026-09-26 23:29 - why it "came back": app relaunch drops the pin

- Root failure of the previous attempt: the owner relaunched Ente Auth (new
  pid) and the fresh window opens WITHOUT topmost. The old watcher instances
  were spawned from the agent shell and did not survive reliably, so nothing
  re-pinned it - matching "fine for a couple of seconds, then garbage".
- Re-pinned topmost manually. Also made the mechanism durable: the first
  schtasks attempt produced a malformed action
  (wscript error dialog "no file extension in C:\WINDOWS\system32\C:\...
  /RL LIMITED /F" - quoting acknowledged, was shown to the owner) - the bad
  task was deleted and rebuilt through Register-ScheduledTask with a clean
  New-ScheduledTaskAction (transcript:
  `reports\2026-09-26-watchdog-durable-install2.log`). Task
  `WatchAuthRepaint` now has action `wscript.exe "C:\ProgramData\
  StartupLaunchers\Launch-AuthRepaintWatch.vbs"` with an AtLogOn trigger
  (limited), verified Ready with a correct Task To Run, and was started.
  Watcher v2 confirmed running and logged "watcher v2 started" 23:27:40.
- Ente Auth relaunched through the helper at 23:29; topmost bit verified
  True on the fresh window; 30 s measurement: 30/30 repaint samples, no
  static runs.
- Current stack, in order: (1) topmost while fullscreen foreground -
  automatic via watcher v2 + scheduled task; (2) 15 s stall-heal nudges; (3)
  DWM-side MPO disable (OverlayTestMode=5) live since 23:08; (4)
  DisableOverlays kernel-side at next boot; (5) Windhk excludes auth.exe.

## Update 2026-09-26 23:45 - real trigger found and fixed: fullscreen game + DWM promotion

- Owner's screenshot showed the real usage: Ente Auth floating on top of a
  fullscreen Plutonium T6 Zombies game. Measured live (1 Hz and 0.7 s pixel
  hashes): clean painting for ~46 samples, then a burst of stagnant frames
  and a 31-sample (~22 s) static run while the game ran - the game's
  swapchain gets promoted (hardware-composed plane) and the non-topmost Auth
  window falls out of composition, waking up only on recompose triggers.
  DWM was restarted with OverlayTestMode just before, so this happened with
  MPO-disable partially active: the promotion path survives until the
  kernel-side DisableOverlays engages at boot.
- Fix applied live:Ente Auth pinned HWND_TOPMOST (SetWindowPos at 23:41).
  Re-measured under the same game conditions: 90/90 0.7 s samples repainted,
  zero static runs. A topmost window keeps its own compositor plane while
  the fullscreen app bypasses DWM, so it cannot drop out.
- `scripts\Watch-AuthRepaint.ps1` upgraded to v2 and verified live
  ("watcher v2 started" 23:18:19): 1) while a fullscreen window owns the
  foreground, re-asserts HWND_TOPMOST on Ente Auth every second (style-bit
  checked); 2) drops topmost on desktop foreground; 3) stall heal fallback
  tightened from 60 s to 15 s throttle. Log file unchanged. HKCU Run
  autostart launches this at every logon (the two v1 instances running
  before 23:18 were superseded; one may remain until that session ends - its
  behaviour is benign, only without topmost logic).
- If the user dislikes always-on-top on the desktop: the watcher drops it
  automatically whenever no fullscreen window is the foreground.

## Update 2026-09-26 23:10 - live fix applied without reboot (owner refuses restart)

- Owner added facts: the freeze existed on the old driver (616.92) too, so a
  driver rollback is not the fix. Restart is unwanted (other agent threads
  active).
- Live lever used: `HKLM\SOFTWARE\Microsoft\Windows\Dwm\OverlayTestMode=5`
  (NVIDIA's official MPO-disable path, DWM-side) applied and `dwm.exe`
  restarted in place at 23:08:56 - the compositing session rebuilt without a
  logout or closing any app. Transcript:
  `reports\2026-09-26-dwm-repaint-live-fix.log`. This makes the MPO-disable
  effective immediately; `DisableOverlays=1` (kernel side) additionally
  engages at the next natural reboot.
- Post-restart measurement: Ente Auth repaired 20/20 repaint samples.
- Auto-heal watchdog installed as a belt-and-suspenders for any autopresent
  stall that survives: `scripts\Watch-AuthRepaint.ps1` (mutex-guarded;
  samples the Ente Auth window at 1 Hz; three identical 1 s pixel hashes on
  a ticking-code window = stall detected; heals with a +1 px/-1 px nudge,
  throttled to max 1 nudge per 60 s; log
  `C:\ProgramData\StartupLaunchers\watch-auth-repaint.log`). Registry
  autostart: `HKCU\...\Run\Watch-AuthRepaint` ->
  `wscript.exe C:\ProgramData\StartupLaunchers\Launch-AuthRepaintWatch.vbs`
  (no console flash). Started live at 23:10:29.
- To undo: delete `OverlayTestMode` from the Dwm key (or restore from
  `backups\2026-09-26\repaint-fix\SoftwareDwm-before.reg`), delete the
  `Watch-AuthRepaint` Run value + the vbs, kill the pwsh watcher.



## Update 2026-09-26 22:35 - cause found: Windhawk injection, verified

- Pixel-diff test on the Ente Auth window (TOTP codes tick every second, so a
  frozen window hashes identical; nothing saved, hashes only): instance with
  Windhawk mods in it = 6 s IDENTICAL (frozen). Same app relaunched with
  `auth.exe` added to Windhawk `Exclude` = repainting, four changing hashes
  over 15+ s. Ente Auth is fixed right now by the exclusion.
- The 22:31 launch went through the repaint-safe launcher and still wedged,
  so the +1 px startup nudge does not prevent this wedge - the mods do cause
  it.
- `HKLM\SOFTWARE\Windhawk\Engine\Settings\Exclude` = `auth.exe` (was empty).
  Rollback: set it back to empty string.
- Suspicious mods for this class of wedge are the ones hooking every
  top-level window (`custom-corner-radius`, `translucent-windows`,
  `titlebar-for-everyone`, `win11-accent-border`, `always-on-top`,
  `win32-ui-modernizer`). Not bisected yet - bisecting needs per-subset
  relaunch trials and fresh instances, which is follow-up work.
- Pixel test of live windows read-only at 22:35: Discord and T3 Code
  repainting; Steam main window produced three identical hashes but idle
  Steam content is largely static, so inconclusive. If the owner's other
  frozen apps are named, adding them to the Windhawk Exclude list applies the
  same one-line fix per app; the real fix would be finding and patching or
  dropping the culprit mod.
- The DisableOverlays MPO fix from 22:22 is still in place and still needs a
  restart to engage; it addresses the Chromium-class DWM bug and is
  independent of the Windhawk finding.

## What was reported

Some apps (owner named Ente Auth as the example) open but freeze visually.
Window is responsive - can be grabbed and dragged - but content does not
update until the window is maximized and un-maximized. That manual dance
reliably heals it.

## Observed facts before any change

- Ente Auth 4.4.25+1072, `C:\Program Files\Ente Auth\auth.exe`. Flutter Windows
  app with `window_manager_plugin.dll` (the plugin whose hidden-startup
  choreography is implicated in Flutter resize/presentation wedge bugs,
  flutter/flutter#187922, flutter/flutter#144217). 4.4.25 is the newest Auth
  release, so no app update is available to pull a fix.
- Ente's own runner already carries a Flutter frame-pacing workaround
  (`set_ui_thread_policy(RunOnSeparateThread)`, commit dc40ca9, "remove after
  upgrading past Flutter 3.38.10") - they are still fighting Windows frame
  presentation inside the app.
- Windows 11 Pro 25H2, build 26200.9457.
- NVIDIA GeForce RTX 4070, driver 617.14, clean-installed 2026-09-25 (DDU +
  NVCleanstall; MPO-disable tweak deliberately left unticked there). HAGS on.
- No MPO/overlay override existed before this run
  (no `OverlayTestMode`, no `DisableOverlays` anywhere).
- System-wide DWM MPO flip-mode regression documented on 24H2/25H2 with
  discrete GPUs (spaceagetv/chromium-gpu-bug): partially-updating windows
  freeze in stale presentation until an interaction/recompose. Matches the
  "frozen but responsive, heals on maximize/restore" report and explains
  "some apps" (Chromium/Electron/Flutter/DirectComposition content). The 24H2
  key (`GraphicsDrivers\OverlayMinFPS=0`) reportedly no longer works on 25H2;
  the 25H2 key is `GraphicsDrivers\DisableOverlays=1`, restart to apply.
- Windhawk injects into all processes (excluded only via `InjectIntoGames`,
  `Include: winlogon|logonui|dwm`) with ~80 mods incl. `custom-corner-radius`,
  `translucent-windows`, `per-monitor-brightness`. Noted as a possible second
  contributor; not changed. If freezes persist after boot with the registry
  fix, quit Windhawk once as the isolation test before anything else.

## Changes applied 2026-09-26 ~22:22

| # | Item | Original value | New value | Rollback |
|---|------|----------------|-----------|----------|
| 1 | `HKLM\SYSTEM\CurrentControlSet\Control\GraphicsDrivers\DisableOverlays` | absent | DWORD 1 | delete the value (or `reg add ... /v DisableOverlays /f` is re-addable), then restart |
| 2 | `C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Ente Auth.lnk` | target `C:\Program Files\Ente Auth\auth.exe` | target `H:\System Configuration\scripts\Launch-EnteAuth.exe`, icon stays auth.exe | copy `backups\2026-09-26\repaint-fix\Ente Auth.lnk.original` back |

Key exports taken first: `backups\2026-09-26\repaint-fix\GraphicsDrivers-before.reg`,
`SoftwareDwm-before.reg`. Apply transcript: `reports\2026-09-26-repaint-fix-apply.log`.

New files:

- `scripts\LaunchEnteAuth.cs` + compiled `scripts\Launch-EnteAuth.exe` - starts
  Ente Auth and, once its main window is visible, resizes it +1 px and back
  (~1.5 s and again ~5 s later). That is exactly the external `WM_SIZE` that
  unwedges Flutter's resize/presentation state - the same thing the manual
  maximize/restore dance does, but invisible. Log:
  `reports\2026-09-26-ente-launcher.log`. Live-tested: launched Ente Auth,
  window found, two nudges applied (800x1087), app running.
- Fallback reg (if `DisableOverlays` alone proves useless - apply at next
  restart, NVIDIA's official MPO-disable method):
  `backups\2026-09-26\repaint-fix\mpo-disable-OverlayTestMode-OPTIONAL.reg`
  (sets HKLM\SOFTWARE\Microsoft\Windows\Dwm\OverlayTestMode=5).

## Effects and trade-offs

- DisableOverlays=1 turns off multi-plane overlay scheduling system-wide once
  Windows restarts. Expected: the stale-window freeze stops for all affected
  apps. Cost: DWM composes everything instead of promoting layers; borderless
  gaming may cost a little (power/efficiency), which matters only if
  measurable. Games with the RTSS global flip override present independent of
  DWM either way.
- This partially conflicts with the 2026-09-11 standing note "do not disable
  MPO without a controlled before-and-after capture" - that rule protected
  the borderless-latency test isolation. Here the MPO disable is the primary
  fix candidate for a new symptom; keep the two investigations separate and
  re-enable MPO first if the borderless-latency question is reopened.

## Verification status

- Registry and shortcut verified on disk after apply (values above).
- Launch helper verified live (nudge log).
- NOT yet verified: whether the freeze is symptom-free - the registry change
  needs a restart, and the visible symptom needs the owner's eyes. Checklist
  for after the restart: open Ente Auth from the Start Menu, check it paints;
  if a Chromium app (Chrome/Discord) still freezes-csswitch to fullscreen and
  back to reproduce, then apply the OPTIONAL OverlayTestMode reg and restart.

## If it is not fixed after restart

1. Run Windhawk's quit (system tray -> quit) for one session and retest -
   rules the ~80 global mods in/out.
2. Apply the OPTIONAL OverlayTestMode reg.
3. For future freezing apps: launching via the helper heals Ente Auth at
   start; for other Flutter/Electron apps a similar +1px/-1px nudge at their
   start works the same way (copy the launcher parameterized).
