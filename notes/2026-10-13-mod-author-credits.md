# Mod author credits and Everything Start Menu Plus rename (2026-10-13)

## What changed

- `start-everything-plus` renamed to **Everything Start Menu Plus** (`@name`, readme title and preview alt text). The `@id` stays `start-everything-plus`, so its settings and registry key carry over unchanged.
- `@author` now lists DavidHiFi first, then the original creators of each fork or port. Metadata only: no code, version or settings change, so no rebuild.
- `docs\mod-style-guide.md` updated to match.

## Mods updated (`@author` after)

| Mod | `@author` |
| --- | --- |
| Everything Start Menu Plus | DavidHiFi, bardelyne |
| Better Volume Mixer Plus | DavidHiFi, 0Allu |
| Shell Font Changer | DavidHiFi, Gabriela Cristei |
| Simple Window Switcher Plus | DavidHiFi, Lone, valinet, Asteski, bropines, caliberda |
| Taskbar AI Quota Bars Plus | DavidHiFi, Cleroth |
| Taskbar System Info Plus | DavidHiFi, Yevhenii Starychenko, m417z, Salyts |
| Translucent Flyouts | DavidHiFi, ALTaleX531 |
| AltSnap (alt-snap-drag) | DavidHiFi, m417z, RamonUnch, Stefan Sundin |
| Center Titlebar - Fork | DavidHiFi, rounk-ctrl, valinet |
| Window Manager | DavidHiFi, m417z, Asteski, TomberWolf, RamonUnch, Stefan Sundin |
| Windhawk Styler | DavidHiFi, Ingan121 |
| Taskbar Audio Visualizer | DavidHiFi, Salyts |
| David's Window Pack | DavidHiFi, m417z, RamonUnch, Stefan Sundin, Asteski, TomberWolf |
| Explorer TreeItem Tweaker Plus | DavidHiFi, Languster, crazyboyybs, valinet |

Original (not forks, so unchanged): Notepad++ Dark Dialog Fix, Taskbar Weather (Open-Meteo is the data source, not an author).

## Where

- Live: `C:\ProgramData\Windhawk\ModsSource\local@*.wh.cpp`, written elevated by `scripts\2026-10-13-credit-authors-live.ps1`. Originals backed up to `backups\2026-10-13-author-credits\`.
- Workspace: `davids-windhawk-mods\mods\local\*`, `work\window-pack-publish\mods\local\david-window-pack`, `Windhawk\explorer-treeitem-tweaker-plus`.

## Not updated

- Dev snapshots (`Windhawk\translucency-flyouts\build-*`, `Windhawk\altsnap-fork`, `Windhawk\better-volume-mixer-fork`, `Windhawk\Opencode-fork`, `work\styler-release`, `work\start-everything-plus-publish`, `staged\`) keep their old `@author`. They are historical copies. The publish copies update on the next publish.
- Not committed or pushed. The GitHub copies show the old names until the next publish.

## Rollback

Copy the matching file from `backups\2026-10-13-author-credits\` back over `C:\ProgramData\Windhawk\ModsSource\`, elevated. The workspace edits are reversible with git (`davids-windhawk-mods`) and the same single-line change.
