# Notification center: Mocha rice, one dock under the clock (2026-11-09)

Mod: `windows-11-notification-center-styler` (theme FrostyGlass kept). Changes are
user rules in its settings, `HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-notification-center-styler\Settings`.

Script: `scripts\2026-11-09-notification-center-mocha.ps1 -Audit | -Install [-Position Top|Bottom] | -Rollback`
Backup: `backups\2026-11-09\notification-center\notification-center-styler-before.reg`
Receipt: `backups\2026-11-09\notification-center\receipt.json` (rules 10..109, 4 constants)

## Old -> new

| Setting | Old | New |
|---|---|---|
| styleConstants Background | FrostyGlass default acrylic | Taskbar material: `WindhawkBlur 48, tint #181825 0.32, luminosity 0.45, saturation 1.4, noise 0.04` |
| styleConstants BorderBrush | theme default | Horizontal gradient #89B4FA -> #CBA6F7 (same as taskbar) |
| BorderThickness / CornerRadius | theme default | 2 / 15 |
| Fonts | Segoe UI Variable | FiraCode Nerd Font Medium everywhere (page-level default, plus calendar header, "+N notifications", toast text) |
| Buttons | stock | Mantle pill, blue ring on hover, mauve on press (Clear all, bell, Focus, +/-, expand, see more, dismiss, settings) |
| Position | bottom right | Top right, under the clock; notifications + calendar as one dock |

## Position setting

`-Position Top` (default) adds the position rules; `-Position Bottom` leaves them out
(Windows default). They also show in the styler's settings in Windhawk and can be
edited or deleted there: the rules on `Grid#RootContent`, `Grid#NotificationCenterGrid`,
`Grid#CalendarCenterGrid` and `ClockCalendarView`.

How Top works: the calendar holder gets `Height=9000` + `Padding=0,0,0,8000`, which
pushes the content to the top of the full-height window; the second row of
`RootContent` takes the calendar's measured height (`ActualHeight=>calH`, row
`Height="{{calH}}"`), which clips the rest. Without that clip a 1px grey line ran
down to the bottom of the screen. Recipe from ramensoftware/windhawk-mods issue
1053 (comment 2405461863).

## Warnings

- Never set `Shadow:=` or `Translation=` on `Grid#CalendarCenterGrid`: both crashed
  ShellExperienceHost (it comes back on the next open).
- Padding on `RootContent` or translating the content hides or clips the panel.
- `ToggleButton` needs its full name `Windows.UI.Xaml.Controls.Primitives.ToggleButton`
  in a selector; the short name does not match.

## Rollback

`scripts\2026-11-09-notification-center-mocha.ps1 -Rollback` (run elevated through
`H:\System Configuration\scripts\Invoke-Elevated.ps1`), or import the backup .reg.

## Proof

`reports\2026-11-09-notification-center-dock4-zoom.png`: one dock, no seam, no side
line, Fira on all text, colour matches the taskbar. Hover states are set but were
not checked on screen (that needs the owner's mouse).
