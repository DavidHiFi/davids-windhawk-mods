# 2026-11-16 Uptime after the title on every window, Explorer included

Owner ask: "a global, seamless title bar that displays uptime on all windows, including
Explorer ... consistently applied across all applications."

## What already had it

Seamless Title Bars (DWM part) adds the uptime after every title DWM draws. Windows that
draw their own title never get it from DWM, and Title Bars skips Explorer on purpose
(`excludedClasses=CabinetWClass`, its title is XAML).

## What changed

| Window | Mod | Old | New |
|---|---|---|---|
| File Explorer tab title | local@windows-11-file-explorer-styler-plus | 1.10.6, no uptime | 1.10.7, uptime run after the tab title, new setting `titleUptime` (default on, set to 1) |
| Windhawk window caption | local@windhawk-enhanced-styler | 2.2.6, no uptime | 2.2.7, uptime drawn after the title inside the dock |

Both read Seamless Title Bars' own `uptime.*`, `title.hideMode` and on/off state from its
registry settings, so units, compact or clock, separator and colour always match, and the
uptime hides when that mod or its uptime is off. The time format is a copy of Title Bars'
FormatUptime.

- Explorer: born time per window = first time the tab is seen; windows open when the mod
  loads count from the load (same rule Title Bars uses). Times are kept across a mod reload
  in the mod's LocalStorage (`titleBornTimes`), and Title Bars' saved `windowBornTimes` is
  read too. A 1 s timer per Explorer UI thread updates a coloured Run after the tab's
  TextBlock; everything is removed on unload.
- Windhawk window: each opening is its own windhawk-ui process, so the uptime is the
  process age. A timer repaints the caption just after each new second.

## Install, proof, rollback

Scripts: `scripts\2026-11-16-explorer-title-uptime.ps1` and
`scripts\2026-11-16-windhawk-title-uptime.ps1`, `-Action Audit | Install | Disable | Rollback`.
Backups (old source + registry export) in `backups\2026-11-16\explorer-title-uptime\` and
`backups\2026-11-16\windhawk-title-uptime\`. Rollback: `-Action Rollback` reinstalls the old
source. Turn the Explorer uptime alone off: the mod's "Uptime after the title" setting.

Work folder: `work\2026-11-16-title-uptime-everywhere\` (apply.py / apply-es.py build the
staged sources from the live copies; prove.py films an Explorer window's title).

Colour: an empty `uptime.color` means "same as the title" in Title Bars; both new builds
follow that (Explorer clears the Run's Foreground, Enhanced Styler draws in the title colour).

Installed 2026-11-16: Explorer Styler Plus 1.10.7 at 10:31 pm (live sha256 4928…109A),
Enhanced Styler 2.2.7 at 10:33 pm (live sha256 F4FD…5B6D). Explorer did not restart
(same explorer.exe PIDs before and after), the 1.10.7 DLL is loaded in explorer.exe.

Public repo: DavidHiFi/davids-windhawk-mods PR 61, merged (a2e97a0), manifest and both
readmes updated. Previews unchanged, raw URLs return 200.

## Coverage

| Window kind | Uptime | Proof |
|---|---|---|
| Every window whose title DWM draws (most apps, T3, HaloCord, dialogs) | yes, Seamless Title Bars | already shipped |
| File Explorer | yes, 1.10.7 | `work\...\proof\after\` (filmed when the owner was idle) |
| Windhawk window | yes, 2.2.7 | `work\...\proof\windhawk\start.png`, `title.gif` |
| Steam | no, draws its own skin; would need a Steam skin change | not attempted |
| Full-screen games with no caption (Plutonium, s1x) | no, nothing to draw on | by design |
| Store-style apps (ApplicationFrameWindow), Chromium/Electron with custom title bars | untested | open |

Small known nit: in Enhanced Styler's readme the 2.2.7 bullet sits under the
"What's new in 2.2.5" heading. Fix with the next version, not worth a reinstall alone.
