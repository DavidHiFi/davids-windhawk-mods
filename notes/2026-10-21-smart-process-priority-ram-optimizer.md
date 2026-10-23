# Smart Process Priority & RAM Optimizer — settings plan (2026-10-21)

**Goal:** set the mod's settings to the best values for this machine: Ryzen 7 5800X
(8C/16T, not hybrid), 32 GB RAM, desktop on AC, user works in T3 Code, Zen
browser, Steam (+ Millennium lua VMs), Discord/TestCord, games (Plutonium/Cold
War), music (Dopamine), and the protected audio chain (Ableton Live 12 Suite,
VB-Audio Matrix, Stream Deck, Mullvad VPN GUI).

**Spec:** `C:\ProgramData\Windhawk\ModsSource\smart-process-priority-ram-optimizer.wh.cpp`
(v1.0.1, ID `smart-process-priority-ram-optimizer`, `@include windhawk.exe` —
the mod runs only inside the Windhawk broker process and manages other
processes externally; it never injects into user apps. Confirmed in source.)

## Hard constraints
- Protected chain: Ableton Live, VB-Audio Matrix, Stream Deck, Discord,
  VB-Audio services must stay OUT of the mod's reach → immunity list.
- No full engine restart; changes must hot-reload via `SettingsChangeTime`.
- Route: `windhawk-cli.exe mod settings set` (validates keys/types against the
  mod's declared settings, atomic batch) over raw registry edits.

## Decisions

| Setting | Was | Now | Why (from source reading) |
| --- | --- | --- | --- |
| enableProBalance | 1 | 1 | keep; boosts foreground window family, restores after alt-tab |
| foregroundPriorityLevel | high | high | max responsiveness for games + DAW foreground |
| enableForegroundCpuSets | 1 | 1 | no-op guarded by `isHybridCpu` (5800X is not hybrid); auto-benefits if CPU changes |
| enableDynamicPowerPlan | 1 | 0 | OFF: v1.0.1 bug targets GUID `a6e23a8e635c`, the real High Performance plan is `a6e23a8c635c` — engagement fails silently. Stop pointless attempts; re-enable after an author fix (check Changelog on update) |
| enableBackgroundThrottling | 1 | 1 | engages only when system load >60% AND a background proc sustains >15% CPU |
| backgroundCpuThrottleThresholdPercent | 15 | 15 | default is right for 16 threads |
| systemCpuContentionThresholdPercent | 60 | 60 | default right |
| enableBackgroundCpuSets | 1 | 1 | no-op guarded by `isHybridCpu`; future-proof |
| enableEcoQosManagement | 1 | 0 | OFF: no E-cores on 5800X, EcoQoS only needlessly caps background frequency |
| enableAudioShielding | 1 | 1 | WASAPI shield is the core protection: no throttle/trim while audio actually plays |
| enableNetworkShielding | 1 | 1 | shields active transfers (downloads, VoIP) |
| enableSmartAiOptimization | 1 | 1 | shields shader compilation + local AI from throttle/trim |
| customAiProcesses | "" | "" | keep; cmdline markers already cover ollama/comfyui/etc |
| freeRamThresholdPercent | 0 | 0 | auto-adaptive: on 32 GB cleans at 45% free standard / 60% heavy-hog tier; adapts if RAM changes |
| trimMinimizedWindows | 1 | 1 | safe, only cold pages |
| enableBrowserTabTrim | 1 | 1 | trims dormant renderer tabs only |
| pauseOnBattery | 1 | 1 | never triggers on AC desktop (also pauses during Windows Energy Saver) |
| enableElectronMemoryCap | 1 | 1 | keep |
| electronMemoryCapMb | 300 | 300 | keep |
| processStartupGraceSeconds | 5 | 5 | keep; avoids trimming during process init |
| customTargetList | default | default | zen/discord/steam already in; T3 Code deliberately NOT added: proactive cap-trim of an active-use editor would hurt re-focus latency; the standard 45%-free sweep still catches it |
| enablePanicHotkey | 1 | 1 | keep Ctrl+Alt+F11 emergency clean |
| enableHotkeySound | 1 | 1 | keep |
| excludedProcesses | default | default + protected chain | append: `mullvad vpn.exe, ableton live 12 suite.exe, push2displayprocess.exe, push3.exe, vbaudiomatrix.exe, vbaudiomatrix_x64.exe, vbaudiomatrixcoconut.exe, vbaudiomatrixcoconut_x64.exe, vbmatrixvaio_controlpanel.exe, streamdeck.exe` (all verified installed exe names) |

Notes:
- Windhawk's own process family (including `windhawk-mod.exe` hosts of the other
  mods) is protected by the mod's built-in path veto (`IsWindhawkProcess`), so no
  registry entry needed for that.
- Games get sanctuary protection built in (no trim + grace after alt-tab).

## Tasks (checkbox)
- [x] T1 Backup: `reg export` mod key → `backups\2026-10-21-smart-priority-ram\mod-settings-backup.reg` (done, 4,274 bytes, 8:53:09 PM)
- [ ] T2 Apply via CLI `mod settings set` (3 changed values: enableDynamicPowerPlan=0, enableEcoQosManagement=0, excludedProcesses=full string) under `coop lock windhawk-engine`
- [ ] T3 Verify: `mod settings get --json` equals target table; `SettingsChangeTime` bumped; mod still enabled/loaded
- [ ] T4 Evidence: screenshot of the mod settings page; receipt JSON; this note completed; CURRENT-STATUS line; coop done

## Rollback
`reg import backups\2026-10-21-smart-priority-ram\mod-settings-backup.reg`
(elevated) — restores every original value including the change-marker.
