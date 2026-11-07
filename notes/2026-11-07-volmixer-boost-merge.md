# Seamless Volume Mixer 1.3.0: App Volume Booster merged in (2026-11-07)

App Volume Booster 1.0 (shubho) is now part of Seamless Volume Mixer
(`local@better-volume-mixer-plus`). The booster mod is uninstalled.

## What changed

- Per-app sliders run 0 to 1000%. Past 100% the fill turns mauve and the
  booster gain takes over. Up to 100% the slider is still the Windows session volume.
- Each app row has a compressor toggle button and a chevron. The chevron opens
  a per-app panel with Threshold, Ratio, Attack and Release sliders. It is
  collapsed by default.
- No boost controls on explorer, windhawk-mod or System sounds.
- Settings are saved in mod storage (`boostConfig`, format
  `exe=gain%,comp,thrDb,ratio*10,atkMs,relMs;`). When an app first gets a
  setting, the mixer adds that exe to its own custom include list, so the boost
  code loads into that app.
- Header: Seamless Volume Mixer 1.3.0, author "DavidHiFi, 0Allu, shubho", Ko-fi.

Old: mixer 1.2.1 plus app-volume-booster 1.0. New: mixer 1.3.0 only.

## Evidence (measured, 2026-11-07)

Measured with a silent test program (`scripts\tools\bvmp-boosttest.exe probe`).
It writes 0.01 samples and reads each buffer back after the boost hook runs.

| Setup | Output | Ratio |
|---|---|---|
| No boost | 0.0100 | 1.00 |
| 300%, compressor off | 0.0300 | 3.00 |
| 300%, compressor -60 dB, 20:1 | 0.0034 | matches the calculation |

The mod log showed "Boost: active in bvmp-boosttest.exe, gain 3.00x",
"render client attached" and "processing audio".

Screenshots: `reports\2026-11-07-mixer-1.3.0-rows.png` (collapsed rows) and
`reports\2026-11-07-mixer-1.3.0-panel.png` (open panel).

Final state, read from the deploy script's audit at 10:44 am: 1.3.0 loaded,
the source matches the package, IncludeCustom is empty, boostConfig is empty,
and the booster has no key, source or DLLs left (receipt in `reports\`).

## Findings

- The tool mod runs in `windhawk-mod.exe`, not `windhawk.exe`. The launcher
  check has to accept any exe starting with `windhawk`, or the host never
  starts the mixer.
- Writing IncludeCustom does not restart the tool host. Only toggling Disabled does.
- Self-updating apps rename their running exe (HaloCord runs as
  `HaloCord.exe.<digits>.old`). The mixer strips everything after `.exe.` when
  it builds the key.
- Boost inside HaloCord is unverified. It takes effect the next time HaloCord
  starts, and it was not restarted because it was in use.

## Limits

- A boost takes effect when the app next starts its audio. Apps that were
  already playing pick it up on the next stream or restart.
- Boosting past 100% can clip. The compressor is the guard against that.
- App Volume Booster has no @license line. The public repo copy stays at 1.2.1
  until that is cleared with the author. The 1.3.0 source lives in
  `work\2026-11-07-volmixer-1.3.0\`.

## Files

- Patch generator: `scripts\2026-11-07-volmixer-boost-patch.py` (makes 1.3.0 from the 1.2.1 backup, same hash)
- Deploy: `scripts\2026-11-07-volmixer-boost-deploy.ps1 -Audit | -Install | -Rollback`
- Backups: `backups\2026-11-07-volmixer-boost-merge\` (both sources, both registry keys)

## Rollback

Run elevated: `scripts\2026-11-07-volmixer-boost-deploy.ps1 -Rollback`. It
restores the 1.2.1 source, compiles it and reloads it, then restores the
booster's source and registry key and compiles it. The booster half of the
rollback has not been tested.
