# Privacy Indicator Anchor: tray-consistent restyle

Date: 2026-10-15. User ask: the privacy indicator group looked oversized ("almost going
off the taskbar") and its spacing did not match the rest of the tray; configure all
mod settings sensibly and theme it Catppuccin Mocha. Follow-up round the same day:
fix the near-zero seam between the network icon and the slashed location icon.

## What was wrong

- `Layout.Arrangement=auto` built a 2x2 block of 16px icons: 36px tall inside the
  48px pill's 40px inner band, so the cluster nearly touched both edges. The
  neighbours are single-row 16px tray glyphs.
- `Surface.GlowStyle=radiate` at `GlowSize=220` spread halos well past the icon
  slots, making the cluster look even bigger.
- Round 2: as a single row, the group's reserved column sat flush against the
  native tray cell (left) and the clock button (right), leaving ~2px seams, while
  the internal rhythm and the tray's own rhythm are ~12px glyph-to-glyph
  (native tray = 16px glyphs in 28px cells; `taskbar-notification-icon-spacing`
  `notificationIconWidth=28`, `windows-11-taskbar-styler` `sysTrayIconSize=16`).

## Applied

All in `HKLM\SOFTWARE\Windhawk\Engine\Mods\privacy-indicator-anchor\Settings`,
written elevated, both rounds applied live via `SettingsChangeTime` bumps
(1792058812, then 1792064341). Script:
`scripts\2026-10-15-privacy-anchor-settings.ps1` (`-Audit`/`-Install`/`-Rollback`).

| Value | From | To |
|---|---|---|
| Layout.Arrangement | auto (2x2) | `location \| mic \| camera \| copilot` |
| Size.ItemSpacing | 4 | 12 (16+12 = 28px pitch, matches tray cells) |
| Adjust.PadX | 0 | 10 (round 2: seam fix) |
| Surface.IdleColor | empty | #A6ADC8 (Mocha Subtext0) |
| Surface.IdleOpacity | 50 | 60 |
| Surface.ActiveColor | empty | #F38BA8 (Mocha Red) |
| Surface.DisabledColor | empty | #6C7086 (Mocha Overlay0) |
| Surface.SlashColor | empty | #F38BA8 |
| Surface.GlowStyle | radiate | steady |
| Surface.GlowColor | empty | #F38BA8 |
| Surface.GlowOpacity | 40 | 25 |
| Surface.GlowSize | 220 | 130 |

Kept: `beforeClock` placement, all four icons on, `ItemSize=16`, camera hardware
detection on (it is what reports the physical camera block), native indicator
suppression on, `AlertWhenBlockedAndActive` on. Mocha anchors on this machine:
taskbar fill #1E1E2E, accent pair #89B4FA/#CBA6F7, close-button red #F38BA8.

## Evidence

`reports\2026-10-15-privacy-anchor\`: `before-1-2x2-block-6x.png` (original
near-full-height 2x2), `before-2-tight-seams-6x.png` (the ~2px seams),
`after-cluster-4x.png` (uniform rhythm; live states: active mic in Mocha red with
the contained steady glow, idle/disabled at Subtext0/Overlay0 with red slashes),
`after-taskbar-strip.png`. Measured after round 2 (real px, 2560-wide screen):
network→location ≈14px, internal gaps 11–13px, copilot→clock ≈19px.

## Rollback

`Invoke-Elevated.ps1 -File scripts\2026-10-15-privacy-anchor-settings.ps1
-ArgumentList '-Rollback'` — reg imports
`backups\2026-10-15-privacy-anchor\privacy-indicator-anchor-before-2026-10-15.reg`
and bumps the marker. No Explorer restart happened at any point.
