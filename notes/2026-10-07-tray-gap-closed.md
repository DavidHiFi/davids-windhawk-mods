# Tray gap closed: ethernet icon to clock

Date: 2026-10-07
Thread: 7b5ce675-fae1-4fc3-a654-6d89172a6f58

## What the user asked

Close the dead gap between the ethernet (network) icon and the date/time in the
taskbar tray. The gaps were uneven and it wasted a little space.

## What was actually wrong

The taskbar is at the top of the primary monitor (taskbar-on-top), 2560x50.
The tray's right end on this build (25H2-era reworked tray) laid out like this,
measured from a PrintWindow capture plus UI Automation rects:

| Element (UIA class) | x | w |
| --- | --- | --- |
| NotifyItemIcon (tray app icons, 28px cells) | 2394/2424 | 28 |
| AccentButton "Network Mullvad..." | 2416 | 24 |
| OmniButtonLeft Clock | 2456 | 82 |

Two leaks, in order of size:

1. **16px between the network button and the clock button.** The network
   button is 24px wide for a 16px glyph (4px template padding each side), and
   16px of dead space sat between the two buttons.
2. **25px dead gap** from the ethernet glyph end (x=2435) to the clock text
   start (x=2461) - the notch the user arrowed.

## The fix (windows-11-taskbar-styler settings, live hot-reload)

- `styleConstants[9]` `sysTraySpacing = 6` -> `0`.
- New rule 61: target `SystemTray.OmniButton#ControlCenterButton`
  (this build's network/system-icon button; UIA reports it as
  "SystemTray.AccentButton" but the runtime class is OmniButton):
  `Margin=0,0,-10,0`. The tray lays out right-to-left, so the button's right
  margin sets the seam to the clock; the native layout reserves a 10px
  constant there. -10 cancels it: the button (still 24px, glyph unclipped)
  butts against the clock button and the notify icons close up behind it.
  Seam 25px -> ~9px, matching the 10px glyph-to-glyph rhythm between the
  tray's own icons.
- A first attempt used `Width=16` + `Margin=0` on the same rule; that clipped
  the ethernet glyph halfway and crushed the spacing to the volume icon
  (user rejected it). Reverted in
  `scripts\2026-10-07-styler-revert-clip.ps1` before the margin fix.
- Measured layout law for this build's tray (from margin probes): items are
  placed right-to-left as `x = nextX - rightMargin - width - 10`; a left
  margin only pushes the left neighbours, and RenderTransform on tray
  buttons is stomped by visual-state animations.
- Rules 60, 62-65 were probe rounds; all inert, commented with `//` in the
  final state.
- No engine or Explorer restart; every change hot-reloaded via
  `SettingsChangeTime` bumps.

Result: ethernet glyph end -> clock text start went 25px -> ~10px, which now
matches the tray's own icon rhythm (16px glyphs in 28px cells = ~12px
glyph-to-glyph between neighbours). Clock button kept its size (82px), the
right edge padding is native, taskbar height and all other mods untouched.

## Registry keys touched

Only `HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler`:
`Settings\styleConstants[9]`, `Settings\controlStyles[60-65].target/.styles[n]`,
root `SettingsChangeTime`.

Backup: `backups\2026-10-07-tray-gap\*.reg` (both keys, pre-change).
Rollback: `scripts\2026-10-07-tray-gap-rollback.ps1` (restore spacing, comment
rules 60-65, bump). Applied by hand this time; no apply script was written
because the change is three registry values.

## Evidence

- `reports\2026-10-07-tray-gap\gap-zoom.png` - before, 6x zoom, 25px gap.
- `reports\2026-10-07-tray-gap\before-after.png` - before/after, same region.
- `reports\2026-10-07-tray-gap\traybar-0.png` - final capture (overwritten each
  round; final state is the last one).
- `reports\2026-10-07-tray-gap\receipt.json` - measurements and settings.

## Traps hit this session (for the next agent)

- The attached screenshot was the T3 Code window, not the taskbar; the taskbar
  was hidden under fullscreen apps on all four monitors. PrintWindow with
  PW_RENDERFULLCONTENT on Shell_TrayWnd captures it anyway.
- `Start-Process -Verb RunAs` with an ArgumentList mangles args with spaces -
  use `H:\System Configuration\scripts\Invoke-Elevated.ps1`.
- .reg lines need the value name QUOTED (`"name"="data"`); unquoted names
  import "successfully" and write nothing.
- The styler matches XAML runtime classes exactly (`winrt::get_class_name`);
  UIA ClassName (automation peer string) can differ from them. `SystemTray.OmniButtonLeft`
  never matched; `SystemTray.OmniButton#ControlCenterButton` did.
- One Windows PowerShell gotcha repeated: PS 5.1 has no `??` operator.
