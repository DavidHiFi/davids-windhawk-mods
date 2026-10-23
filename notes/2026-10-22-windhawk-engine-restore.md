# Windhawk engine restore — tiered bring-up per the sanctioned runbook (2026-10-22)

## What this is

The freeze verdict (`H:\System Configuration\t3-handoff\2026-10-22-freeze-verdict-consensus.md`,
closed 6:25 PM) held the Windhawk engine off with 9 broken mods disabled, and sanctioned exactly
one path back up: watchdog armed, tiered re-enable with soaks, input-touching mods last, the 9
stay off. The owner's 10:10 PM go ("get Windhawk back up and running and in a working state")
activated that path. This note is the record of the run.

## Run parameters

- Run stamp: **20261022-223922** (resume of 20261022-223435; the first launch died with its
  parent tool call — the sandbox reaps spawned trees; the WMI-detached relaunch survives).
- Engine: Windhawk 2.0.0-alpha.7 (checked 10:14 PM: `updateDue false` — no newer pre-release
  exists, so bring-up discipline is the fix path, not a newer build).
- `InjectIntoCriticalProcesses` = 0 (verified). `LowLevelHooksTimeout` absent (both hives).
- Registry backup: `backups\2026-10-22\engine-restore\windhawk-engine-pre-restore-20261022-223922.reg`
  (627,830 bytes, full `HKLM\SOFTWARE\Windhawk`).
- Orchestrator: `work\2026-10-22-engine-restore\orchestrator.ps1` (pid 30620, WMI-detached,
  elevated, singleton-guarded). Companion: `scripts\2026-10-22-windhawk-engine-restore.ps1`
  (`-Audit` / `-Rollback`; rollback = engine off + snapshot import + stays off).
- Tier plan: `work\2026-10-22-engine-restore\tier-plan.json` — 10 tiers, ≤13 mods each,
  30-minute soak between tiers, input-touching last (tier 8), tool-hosted/own-app mods last
  (tiers 9–10). The 9 verdict mods + removed uwp-assets-redirect are forced `Disabled=1` and
  re-asserted at every preflight.

## Protections active during the run

- Input-death watchdog (patch 5 processed-input verdict, pid 5664) — captures and names the
  culprit on death.
- The orchestrator probes input every 30 s during soaks; on 3 strikes it executes the
  freeze-response itself (engine off + tier reverted to `Disabled=1` + coop note) and exits 3.
- Also fatal to the run: unexpected service stop, a watchdog `DEATH.txt` capture, or any
  explorer crash into a Windhawk module (WER 1000 filtered on explorer.exe + Windhawk).
- Runtime-enable fallback: if a tier's DLLs don't appear within 25 s, the orchestrator bumps
  `SettingsChangeTime` once and rechecks; still-unloaded mods are logged (target process may
  simply not be running) and never block the run.

## Timeline (12-hour am/pm)

- 10:14 PM — state verified: service Stopped/Manual, 0 processes, 9 disabled mods, 120 enabled;
  coop fleet clear; update check: alpha.7 is newest, no update due.
- 10:34 PM — first orchestrator launch: tier 1 staged (only shell-look enabled), engine
  started, 2 windhawk processes, input ALIVE, tier-1 injection verified by module scan
  (explorer 6/6, StartMenuExperienceHost 7, ShellHost 1).
- 10:37 PM — first orchestrator died with its parent tool call (sandbox tree-reap). Engine
  unaffected (service-owned).
- 10:39 PM — WMI-detached relaunch (`-Resume`): verified engine up with tier 1, no restart,
  soak resumed. pid 30620 confirmed by elevated process check.
- 10:43 PM — independent mid-soak health check: input ALIVE, 6/6 tier-1 explorer DLLs loaded,
  0 new Windhawk-module explorer crashes, 0 watchdog captures.
- 10:49 PM — triple-redundant monitoring set: harness background job watcher
  (`pwsh-a8ae32a9494b46fc`), WMI-detached watcher (pid 12944 → `watcher-result.txt`),
  goal rounds. Soak log: 20/60 loops clean at 10:49 PM.

## Incident: silent orchestrator deaths → architecture v2 (11:33 PM)

The WMI-detached orchestrator died silently **three times** (22:55, ~70 s and ~35 s into
later runs) with **zero event-log trace** — no WER, no .NET error, no reboot; input stayed
ALIVE and the engine was untouched each time. A killer-sweep found no scheduled killer
(`\FreezeDLLSampler` is Running again but is read-only module inventory — left in place as
freeze forensics). Rather than chase an invisible reaper, the run switched to an
architecture with **no long-lived process at all**:

- `\WindhawkRestoreInputGuard` — every 1 min: patch-5 probe ×2 strikes → freeze-response
  (engine off + current tier reverted + ALERT status + coop note). Also honours new
  watchdog `DEATH.txt` captures. Silent when healthy or engine-off.
- `\WindhawkRestoreTierStep` — every 5 min: state machine over `status.json`. 40-min soak
  gates, DLL verification at every enable, stay-off re-asserted every pass, final phase
  sets service Automatic + captures the taskbar. Halts itself on alert/reboot/service-stop.
- Both tasks: interactive token, highest run level, 9 h repetition. First trigger 11:33 PM:
  tier 1 CLEAN after 58 min (enabled 10:34 PM), tier 2 (explorer-ux-1) enabled with
  13/13 DLLs loaded live.
- Projected completion ~5:45 AM. The `-Resume` orchestrator is retired (kept for record).

## Final result

*(appended at run completion)*
