# Freeze #6 first analysis (2026-10-22, written 3:15 PM, thread e4c9ed97)

The machine froze at 3:00 PM while the owner was away and they hard-reset it
(boot 3:00:53 PM). This note is the first-pass breakdown of the evidence. Everything
here is measured from files, the event log, or the recorded capture; nothing is
inferred unless labeled.

## Timeline (all 22 Oct 2026, am/pm)

| Time | Event | Source |
| --- | --- | --- |
| 10:07 AM | WER: local@simple-window-switcher-pl UNLOADED dll crashed explorer.exe 0xc0000005 | fix5-rearm.txt |
| 10:52 AM | WER: local@taskbar-audio-visualizer crashed explorer.exe 0xc0000005 | fix5-rearm.txt |
| 1:08 PM | Retest armed (engine on all mods, watchdog pid 4232) | brief line 74 |
| 1:50 PM | Checker response: 25 capture dirs listed (no DEATH.txt marker) | retest-responded.txt |
| 2:08 PM | WER: taskbar-audio-visualizer crashed explorer again, few seconds before storm start | fix5-rearm.txt |
| 2:08-2:11 PM | Storm test: engine refresh + 4 waves of 12 windows; last report write 2:11:34 PM | storm-run.txt |
| 2:11:47 PM | UNCLEAR shutdown #1 (freeze #5) - hard reset, cause not attributed | Event 6008 2:15:01 PM |
| 2:15 PM | Reboot; engine stays off (startType had been set Manual) | postfreeze5-state.txt |
| 2:29 PM | LoggingEnabled=1 applied to all mod keys by me, engine down, verified 130/130 | log-142920.txt |
| 2:30 PM | [WH] listener live (DbgViewMini pid 16368) | capture header |
| 2:33 PM | Capture proven end-to-end with injected test line | capture line 3 |
| 2:37 PM | dll-state-sampler started by the freeze thread (reads only) | CSV header |
| 2:52 PM | Post-freeze-5 state file written; engine still off | postfreeze5-state.txt |
| 2:55:10 PM | Freeze thread re-arm: audio-visualizer disabled, engine STARTED (18 procs), watchdog pid 3048, marker reset | fix5-rearm.txt |
| 2:55:11-3:00:27 PM | Engine live with all mods; capture records 340,094 lines | capture file |
| ~3:00:01 PM | Freeze #6 onset (recorded unclean shutdown) | Event 6008 3:01:06 PM |
| 3:00:14/17 PM | Sampler still scanning + heartbeat - non-input threads alive past onset | CSV/heartbeat |
| 3:00:27 PM | Last [WH] line (engine injecting process 11408); then silence | capture tail |
| ~3:00:40 PM | Owner hard-reset (power button) | owner report |
| 3:00:53 PM | Reboot; engine did not auto-start (Manual); system stable | boot time + state check |

## Roles in the two freezes (measured)

- I (e4c9ed97) changed only registry config while the engine was OFF: per-mod
  LoggingEnabled=1 (2:29 PM) and a passive debug-stream listener (2:30 PM). I did not
  boot the engine; the engine was booted at 2:55:10 PM by the freeze thread's rearm
  script, and at 2:11 the engine was already live from the 1:08 PM arm.
- The logging bits were a new variable owned by me. Measured footprint: init burst
  peaked at 5,672 lines/s for about a minute, steady state was 30-40 lines/min, and
  the death minute had 3 lines. Blanket logging does not fit as the cause of
  freeze #6 (though it remains unproven either way; per-launch storms multiply each
  app start by ~1,000 debug-stream passes).

## What freeze #6 recorded (the treasure)

- Capture: windhog-dbgview-143006.txt, 35.6 MB, 340,094 lines, in
  H:\Windhawk Configuration\backups\2026-10-22\freeze6-window\ (copy) and
  H:\System Configuration\work\reports\ (original).
- Last line 3:00:27 PM, 26 s after the 3:00:01 shutdown marker - consistent with the
  freeze signature (input dead, other threads alive).
- Freeze-time mod-DLL inventory (sampler scan 3:00:14 PM):
  - explorer.exe: 56 mod DLLs, including copy-queue (infinite mutex suspect),
    local@taskbar-ai-quota-plus (audit suspect #1), keyboard-shortcut-actions,
    caption-buttons-customizer, windows-11-taskbar-styler, local@window-manager,
    local@theme-tool-plus, timer-resolution-control (23,215 log lines in the
    window), icon-resource-redirect (30 s file-lock suspect).
  - dwm.exe: exactly 2 (caption-buttons-customizer, custom-corner-radius).
  - winlogon.exe: local@theme-tool-plus (the boot audit's highest-risk injection
    class; previously given an alibi by bisect round 2 - worth re-testing that logic).
- WER crashers: taskbar-audio-visualizer (explorer, x3 today; disabled at 2:55 PM),
  simple-window-switcher unload crash (10:07 AM). local@simple-window-switcher-plus
  is STILL enabled (Disabled=0) as of 3:12 PM.
- New oddity: mod fix-basic-caption-text throws a repeated engine exception every
  5 s per process (wlanext at 14:55:14-14:55:44, exceptions 1-7, screenshot-level
  line: engine\mod.cpp(2876) windhawk.dll. Its per-call failure mode is unproven
  harm, but it is a runaway repeat pattern.
- Freeze #6 hit at IDLE (no window storm: 2,287 lines in 2:58, 1,723 in 2:59, the
  system was quiet). That breaks the "trigger = window-creation storm" theory for
  this instance; the trigger may be time- or event-based, or the storm theory is
  incomplete.

## Machine state now (verified 3:12 PM elevated)

- Windhawk service Stopped, startType Manual (cannot auto-start after reboot).
- 0 windhog processes, 0 DbgViewMini, watchdog gone, checker task absent from Task
  Scheduler.
- Registry holds: LoggingEnabled=1 on 129/129 keys (inert while engine off),
  audio-visualizer Disabled=1.

## Recommended next steps (in order, all reversible)

1. Disable local@simple-window-switcher-plus (known unloaded-DLL crasher, still
   enabled) - one registry bit, rollback documented.
2. Deep-parse the freeze recording: per-mod timeline 2:58-3:00:27, explorer-thread
   relevance, compare against the sampler inventory; look for the last activity of
   each audit suspect before the silence.
3. Decide with the owner whether the blanket logging stays for one more round
   (cheap, already recorded a death window) or rolls back (fewer variables; the WER
   names no longer depend on it).
4. Re-arm only on explicit owner go.
