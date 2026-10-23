# Taskbar Blob Shape re-enabled by owner — verified 2026-10-13

Owner turned `taskbar-blob-shape` 1.2.0 back on in the Windhawk GUI after the
steam-bubble disable. This supersedes the disable; the mod stays enabled per
owner choice.

## Health check (measured)
- Registry: `Disabled=0`, settings unchanged from the pre-disable backup:
  `Dimensions 30,30`, `Margins 0,0,0,-4`, `TopRadius 8`, `BottomRadius 4`,
  `BgOpacity 0.50,0.50`, `CustomColor #89b4fa,#cba6f7` (Catppuccin Mocha
  blue to mauve), system-button blobs Start/Search/TaskView on, rest off.
  Styler `windows-11-taskbar-styler` still enabled (`Disabled=0`).
- Fresh `Shell_TrayWnd` capture (`reports\2026-10-13-steam-bubble\traybar-reenabled.png`,
  `reenabled-crop-T3-Steam.png`): the active app (T3 Code, foreground) carries
  the flared blue-mauve blob; Steam's left edge is clean in this frame.
- No Explorer restart was needed; the GUI toggle reloaded the mod live.

## Standing clarification
The "ugly blue bubble" from the first report was this blob's 8 px side flare
spilling into the gap next to the active app's neighbor (e.g. T3 active next
to Steam reads as a nub on Steam's left). That is the mod's designed shape,
not corruption: total footprint is (Width + 2*TopRadius) x (Height + TopRadius).
If the spillover bothers the owner later, soften it with `TopRadius 8 -> 4`
or `Dimensions 30,30 -> auto,30`, one change at a time. No change made today
per owner request to keep the mod as-is.

## Records
- Prior backup still valid: `backups\2026-10-13-steam-bubble\taskbar-blob-shape-before.reg`
- Prior rollback script still valid (only use if the owner asks to remove it again).
