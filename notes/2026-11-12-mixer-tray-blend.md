# 2026-11-12 Mixer 1.4.22: tooltip with text, even tray spacing

Owner: "the ugly empty hover bubble is still there fix that" and "fix the spacing and alignment
to make it blend in with the rest of our tray smoothly" (shot: big gap from Fan Control's
"98" to our "94").

## Hover bubble
The empty bubble is the taskbar's own tooltip with nothing in it. It showed under 1.4.17
(no tip at all) and under 1.4.18 to 1.4.20 (tip set, NIF_SHOWTIP off). A version 4 icon without
NIF_SHOWTIP still gets the bubble on Windows 11, just empty. The 1.4.19 note's claim that the
shell shows no tooltip was wrong.
Fix: NIF_SHOWTIP on, on the add and on both icon-update modifies (a modify without it drops
the standard tooltip again). The bubble now reads "Seamless Volume Mixer". The tip text stays
fixed because styler rules 64/65 match the icon by that name.

## Spacing (graphics-capture frame, screen x, ink to ink)
| | before | after |
|---|---|---|
| Power to Fan Control | 13 | 12 |
| Fan Control to number | 19 | 15 |
| number to speaker | 7 | 4 |
| speaker to network | 15 | 15 |
Other neighbours are 14-15. Vertical: number rows 19-29, speaker 19-30, Fan Control 21-29
(same baseline).

## Changes
- Styler rule 64 `Width=52` -> `Width=47` (backup `work\2026-11-12-mixer-tray-blend\styler.reg.bak-20261112-1050`).
- Mixer 1.4.20 -> 1.4.22 (1.4.21 was the same minus the clamp):
  - NIF_SHOWTIP as above.
  - Number window 1 px (was 3) left of the speaker's box, so the ink gap is 4 px.
  - A wide value ("100") is clamped 2 px inside the slot so it stays inside the hover box.
- Built on the installed 1.4.20 (another thread's menu work kept), installed with
  `Install-StagedMod.ps1` through the load gate.

## Verify (10:58 am)
- Frame: [after-4x.png](../work/2026-11-12-mixer-tray-blend/after-4x.png), gaps in the table.
- Rule 64 still matches (the slot width changed), so the UIA name is intact.
- Cover test: shown -> hidden -> shown.
- Shell 0.8 GB, healthy, before the load.
- Not checked: the bubble under a real hover (no cursor test reaches the taskbar), "100" live.

## Trap
The 1.4.22 install left the mixer's windhawk-mod.exe stopped (the icon vanished, the tray
re-flowed). A disable and enable brought it back. The script now checks for this.
`cover-test.ps1` needs Windows PowerShell; under pwsh 7 its Form type does not compile.

## Rollback
`scripts\2026-11-12-mixer-tray-blend.ps1 -Action Rollback` elevated: rule 64 back to Width=52,
mixer 1.4.20 reinstalled from the work folder.

## 1.4.23 to 1.4.25 (number hidden, then polished)

- Cause of the hidden number: 1.4.19-1.4.22 hid it whenever anything but the taskbar sat over the slot. ShareX's full-screen "Region capture" overlay (topmost, transparent) counted, so every screenshot showed no number.
- 1.4.24: hide only when a normal window covers the slot, or a topmost one while Windows reports a full-screen game or presentation. Overlays leave it shown.
- 1.4.25: regular FiraCode at the Mocha text colour (205,214,244; Latte 76,79,105), like the battery percent, instead of bold white. Rule 64 Width 47 -> 50 so "100" keeps a 4 px gap to the speaker.
- Measured (1x): Fan Control ink to number 11 px, number to speaker 4 px, speaker to network 16 px; rows level.
- Rollback: scripts\2026-11-12-mixer-tray-blend.ps1 -Action Rollback (Width 52, 1.4.20). Styler backup: work folder styler.reg.bak-*.
