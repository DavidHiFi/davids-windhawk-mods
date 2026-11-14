# 2026-11-14: Explorer Search settings window, no cut-off text

Owner: "Make sure there's no text being cut off in the settings GUI ... double check that."

## What was cut off (2.0.7, proof\settings-2.0.7)

- Appearance: the accent colour row. Ten swatches plus the hex box left the label and hint too
  little room, so the hint was clipped.
- Sidebar: the mod name showed as "Sea..." because the rail minimum was too narrow for
  "Seamless Explorer Search" at the window's tiled width (client about 760 x 1349).
- About: the hero card title, version line and credits, the Ko-fi heading and the last link's
  hint were drawn in fixed heights and clipped.

## Fix (room made, nothing hidden or shrunk)

- 2.0.8: rows stack (text on top, control below) when the text would get under 150 DIP;
  sidebar minimum 264 DIP so the name fits on two lines at full size.
  Owned functions added: Set_MakeFormats, Set_Parts, Set_DrawRow, Set_RailDragTo.
- 2.0.9: About hero, Ko-fi card and link rows measure their text and grow to fit; the hero
  title splits onto two lines when too wide.
- Installed 6:07 pm (2.0.8) and 8:02 pm (2.0.9) through `Install-StagedMod.ps1` under the engine
  lock, base hash checked each time. Registry 2.0.9, helper running.
- Proof: work\2026-11-12-listary-port\proof\settings-2.0.9, all four pages, nothing clipped.
  `settings-engine.py check` says in sync.

## Config change

- docs/settings-engine.json, backup `settings-engine.json.bak-20261114-1803`.
  Old owned list for local@seamless-explorer-search: Set_Create, Set_Draw, Set_DrawBox,
  Set_DrawFooter, Set_DrawRail, Set_DrawSupport, Set_FormatHotkey, Set_Hit, Set_WndProc.
  New: the same plus Set_DrawRow, Set_MakeFormats, Set_Parts, Set_RailDragTo.
  Rollback: copy the backup over the file.

## Rollback of the mod

Elevated, under `coop lock windhawk-engine`, stage one of the installer's backups with
`scripts\Install-StagedMod.ps1 -Id local@seamless-explorer-search -BaseHash <sha256 of live>`:
`C:\ProgramData\Windhawk\ModsSource\local@seamless-explorer-search.wh.cpp.bak-20261114-1807`
(2.0.7) or `...bak-20261114-2002` (2.0.8). Then restore the manifest backup above.
