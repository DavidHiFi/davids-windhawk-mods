# Borderless latency audit

Date: 2026-09-10

## Reported symptom

Games feel smooth in fullscreen exclusive mode but appear to run at a much lower refresh rate in borderless mode. RTSS and MSI Afterburner show similar game frametimes in both modes.

## Observed facts

- GPU: NVIDIA GeForce RTX 4070.
- NVIDIA driver: 616.92, Windows driver version 32.0.16.1692, dated 2026-09-04.
- Main gaming display: Samsung Odyssey G5 at 2560 x 1440 and 165 Hz. HDR is enabled.
- Secondary displays: Dell SE2725H at 1920 x 1080 and 60 Hz, and LG 24MB37 at 1920 x 1080 and 60 Hz.
- Desktop topology: three extended displays with mixed 165 Hz and 60 Hz refresh rates.
- Windows "Optimizations for windowed games" is enabled.
- Windows variable-refresh optimization is enabled.
- Hardware-accelerated GPU scheduling is enabled.
- Game DVR capture is disabled and Game Mode is enabled.
- The active power plan is High performance.
- Multi-plane overlay support is available. No MPO-disable registry override is present.
- RTSS, MSI Afterburner, NVIDIA Overlay, Discord, Steam, PowerToys, and a Game Bar crosshair extension were running during the audit.
- The System event log contains repeated NVIDIA `nvlddmkm` errors on 2026-09-08 and further event 153 errors on 2026-09-09.
- Winhance 26.06.12 and Winaero Tweaker 1.65 are installed. Their visible policy changes include disabled Game DVR capture and telemetry. SysMain is disabled. No display, NVIDIA, audio, or power service was found disabled.
- Windhawk is running with Settings and Control Panel appearance mods. The installed Windhawk modules found in this audit do not target games or the Desktop Window Manager.

## Assessment

The matching in-game frametime graph does not rule out a presentation problem. That graph measures the game's render timing, while the symptom can occur after the game hands each frame to Windows.

The leading hypotheses are:

1. A compositor or presentation-path problem caused by the mixed-refresh, three-monitor setup.
2. An overlay or frame-hook conflict that affects composed borderless presentation.
3. An NVIDIA driver problem. The recent `nvlddmkm` errors make this more plausible than an undocumented registry tweak.

The current Windows windowed-game optimization is already set to the expected low-latency state, so enabling it again is not a useful fix. MPO is also at its default state. Disabling MPO without an A/B test would be premature.

## Controlled test order

1. Reproduce the issue in one named game and record its API, VSync state, VRR state, frame cap, foreground FPS, and display mode.
2. Close every overlay or hook for one test, starting with RTSS, MSI Afterburner, NVIDIA Overlay, Discord overlay, Steam overlay, and the Game Bar crosshair extension.
3. If the issue remains, temporarily test with only the 165 Hz Odyssey enabled.
4. If the issue remains, compare HDR off versus on while keeping every other setting unchanged.
5. If the issue remains across games and APIs, inspect the NVIDIA event details and test a clean driver installation or known-good driver version with a rollback plan.

## Changes made

- Closed Discord, RTSS, MSI Afterburner, NVIDIA Overlay, and the Game Bar crosshair extension during an initial isolation attempt. Discord, RTSS, and MSI Afterburner were started again immediately after the user clarified that active applications must remain available. NVIDIA Overlay restarted through its own background component. The audio and communications chain is now marked as protected in the workspace instructions.
- Backed up six per-game Windows graphics values to `backups\2026-09-10\windowed-game-overrides-before.reg`.
- Changed `AppStatus=4096;` to `AppStatus=0;` for Red Dead Redemption 2, Elden Ring, both listed Advanced Warfare executables, GTA V Enhanced, and the listed Black Ops Cold War executable. This removes their per-game opt-out state so they use the enabled global Windows windowed-game optimization.
- Original value: `AppStatus=4096;`.
- New value: `AppStatus=0;`.
- Change time: 2026-09-10 13:12:14 +08:00.
- Restart required: no Windows restart. Affected games must be relaunched if they were open.
- Rollback: merge `backups\2026-09-10\windowed-game-overrides-before.reg`, then relaunch the affected game.
- Test result update 2026-09-11: user tested Plutonium T6 Black Ops 2 Zombies with mod loaded in borderless and reports smooth play. This T6 result is not caused by the AppStatus change above. T6 was never in the six-entry list. Read only check with permission shows the T6 cause is the Plutonium workspace RTSS override for plutonium-bootstrapper-win32.exe with ForceFlipModel 1 and ForceAllowTearing 1. See CURRENT-STATUS.md for the verified paths and measurements.

## Full check 2026-09-11

- No AppStatus 4096 blocks remain. All known games inherit the global setting.
- Global SwapEffectUpgradeEnable is 1 and VRROptimizeEnable is 1. HAGS HwSchMode is 2. No MPO override. Game Mode auto is on.
- Plutonium RTSS override is live and covers all Plutonium titles through the one bootstrapper exe.
- Clean backup saved to backups\2026-09-11\user-gpu-preferences-clean.reg. Read only audit script saved to scripts\Audit-Borderless.ps1.
- No new registry change was needed today. If another game still feels wrong in borderless, test that named game with PresentMon and check for BitBlt versus Independent Flip before changing anything.

## Protected running applications

Do not interrupt Discord, Ableton Live, VB-Audio Matrix, Stream Deck, or their supporting processes, services, and drivers. They form the user's active communications and audio-routing chain.
