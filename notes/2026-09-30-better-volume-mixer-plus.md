# Better Volume Mixer Plus: per-app output and input devices

2026-09-30. Thread `bvm-device-fork`.

## What it is

A fork of Better Volume Mixer 1.4.5 by 0Allu, published as
`local@better-volume-mixer-plus` 1.0.0 with author DavidHiFi. Right-click any
app row in the mixer to get two new submenus:

- **Output device**: Default, then every active playback device.
- **Input device**: Default, then every active recording device.

The current choice has a check mark. Picking **Default** clears the override.
This is the same per-app table that Settings > System > Sound > Volume mixer
and EarTrumpet write. It replaces EarTrumpet's per-app device menu, for example
putting Discord back on the Discord Output after an update resets it.

System sounds, and rows without a process, keep the upstream menu (Copy
process name and Hide temporarily). Everything else is unchanged from upstream.

## How it works

- API: the undocumented WinRT factory `Windows.Media.Internal.AudioPolicyConfig`
  via `RoGetActivationFactory`. It tries IID `ab3d4648-e242-459f-b02f-541c70306324`
  (21H2 and later) first, then `2a59116d-6c4f-45e0-a74f-707e3fef9258`.
- Vtable slots 25, 26 and 27 are Set, Get, and ClearAll
  PersistedDefaultAudioEndpoint, matching EarTrumpet's
  `IAudioPolicyConfigFactoryVariantFor21H2` and SoundSwitch.
- Device ids are passed as `\\?\SWD#MMDEVAPI#<IMMDevice id>#{interface}`, with
  render `{e6327cad-...}` and capture `{2eef81be-...}`. Reads are normalized
  back to the bare id.
- Set writes the console, multimedia and communications roles for the PID.
  Get reads multimedia.
- The list refreshes right after a change and again 800 ms later, because
  sessions re-bind asynchronously.
- Links `-lruntimeobject` in addition to the upstream libraries.

## Evidence

- Build: `scripts\2026-09-30-better-volume-mixer-plus-build.ps1`, x64 and x86
  clean. Log: `reports\2026-09-30\better-volume-mixer-plus\build.log`.
  x64 sha256 `8628BA29...156EC2`, x86 `282B5FA4...92D7BB`.
- API proof: `Windhawk\better-volume-mixer-fork\tests\policy-probe.cpp` routed
  its own PID to a non-default output. All three role writes returned
  `S_OK`, Get read the device path back, and clearing returned it to empty.
  Result PASS; log `reports\...\policy-probe.log`. No other process was touched.
- Install: tool process `windhawk.exe -tool-mod "local@better-volume-mixer-plus"`
  runs and owns the `WindhawkBetterTaskbarVolumeMixer` window, and the stock
  mixer process is gone. The mixer opened and listed 13 apps
  (`reports\...\mixer-open.png`).
- User confirmed on 2026-09-30 that the right-click Output device and Input
  device menus work.
- Snapshot repo: `davids-windhawk-mods` commit c3ec657 adds
  `mods/local/better-volume-mixer-plus/`, and `tools/Build-Repo.ps1` now
  tracks it. The push landed, but the repo stays invisible to the public
  while the account is flagged; see `notes\2026-09-30-github-account-flagged.md`.

## Install and rollback

- `scripts\2026-09-30-better-volume-mixer-plus-install.ps1` supports `-Audit`,
  `-Install`, `-Rollback`, and `-Uninstall`.
- Install backs up the stock key, its ModsWritable pins, and its source into
  `backups\2026-09-30\better-volume-mixer-plus\`. It copies the stock settings
  into the fork's key, disables the stock mod (the two share a tray GUID), and
  bumps `SettingsChangeTime` on both. There is no engine restart.
- Rollback disables the fork and re-enables stock. Files stay.
- Include stays `windhawk.exe`, as upstream: the mod runs only in its own tool
  process and injects nothing else.

## Not carried over

- Pinned rows: stock pins live under `ModsWritable\better-volume-mixer\LocalStorage`,
  which was empty, so nothing was lost.

## Mistake on this task

The first live check drove the real mouse. A retried tray click landed on
the "UEFI Firmware" item in the desktop right-click menu while the user was
using it, and rebooted the PC to firmware twice. That script is deleted. The user confirmed the
menus themselves.
