# Steam taskbar blue bubble — audit 2026-10-13

## What you asked
Remove the little light-blue bubble hanging off the left side of the pinned Steam icon.

## Attachment gap (measured)
The attached `image.png` shows the T3 Code window, not the taskbar. No red arrow,
Steam icon, or bubble is in that frame. So the bubble was audited live instead:
`Shell_TrayWnd` captured with PrintWindow before and after the fix
(`reports\2026-10-13-steam-bubble\`).

## Root cause (measured)
`taskbar-blob-shape` 1.2.0 was enabled on top of the `windows-11-taskbar-styler`
giant-pill theme. Both replace the active indicator, which the blob mod's own
readme says not to combine.

- Blob mod draws one flared shape behind the *active* app only
  (`ActiveRunningIndicator` state in `ModsSource\taskbar-blob-shape.wh.cpp`).
- Live settings: `Dimensions 30,30`, `TopRadius 8`, `Margins 0,0,0,-4`,
  `CustomColor #89b4fa,#cba6f7` (light blue to mauve), `BgOpacity 0.50,0.50`.
  Total footprint 46x38, centered, so 8 px flares spill into the gap next to
  the neighbor icon.
- Before capture: T3 (the foreground app) carries that flared blue shape; its
  right flare sits in the gap and reads as a bubble on Steam's left edge.
  After capture: Steam itself gets the same shape whenever Steam is foreground.
- The styler's own pill (`Rectangle#RunningIndicator` repurposed, rules 4/6)
  stays and is the accepted giant-pill look. The 3 px multi-window dot
  (`Rectangle#DefaultIcon`, rule 17, same `#89B4FA` family) was ruled out: it
  only shows with multiple windows per button and is 3 px, not a bubble.

## Fix applied
Disabled `taskbar-blob-shape` (`Disabled 0 -> 1`, elevated). The styler theme
is untouched.

- Backup: `backups\2026-10-13-steam-bubble\taskbar-blob-shape-before.reg`
- Rollback: `scripts\2026-10-13-steam-bubble-rollback.ps1 -Rollback`
- Receipt: `reports\2026-10-13-steam-bubble\receipt.json`
- Captures: `reports\2026-10-13-steam-bubble\traybar-before-disable.png`,
  `traybar-after-disable.png`, plus `before/after-crop-T3-Steam.png`

## Verification (measured)
- Registry reads back `Disabled=1`.
- After capture (~5 s later, no Explorer restart): T3 icon is clean, no flare;
  Steam's left edge is clean; Discord keeps its styler pill. No reboot test.
- If the bubble returns, it means the mod was re-enabled or Steam's own
  overlay/badge drew it while a game overlay was up. Re-run the rollback
  script in reverse (set `Disabled=0`) only if you want the blob look back.
