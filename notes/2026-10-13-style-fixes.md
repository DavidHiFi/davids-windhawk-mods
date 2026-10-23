# Style-guide pass on forked mods (2026-10-13)

Audited every fork against `docs\mod-style-guide.md`: names, id matches name, one-line description, GitHub and homepage, readme title matches name, Credits with a "Based on" line, preview present.

## Fixed

- **Simple Window Switcher Plus**: added `@homepage` (workspace and live).
- **Explorer TreeItem Tweaker Plus**: `@github` now DavidHiFi (was Languster), added `@homepage`, readme title is "Explorer TreeItem Tweaker Plus", Credits now say "Based on ... by Languster" (workspace and live). A first pass left stray carriage returns in the Credits block; fixed and verified.
- **Center Titlebar - Fork** renamed to **Center Titlebar Plus** (`@name`, readme title, and `@id` `center-titlebar-plus`). Added a Credits section. Not installed, so no settings move. The published copy on `main` still has the old id until republish.
- **Taskbar AI Quota Bars Plus** (live): added the Credits section (Cleroth).

Script: `scripts\2026-10-13-style-fixes.ps1` (`-Group Workspace` / `-Group Live`). Live originals backed up to `backups\2026-10-13-style-fixes\`.

## Left for the user

1. **David's Window Pack** (`work\window-pack-publish\...\david-window-pack`): superseded by Window Manager on 2026-10-04 and not installed. It still has a personal name in `@name` and `@id`, a 102-character description and no Credits. Recommend archiving or deleting it. Not changed: deleting is destructive.
2. **Previews missing**: Center Titlebar Plus (prototype, not installed), Explorer TreeItem Tweaker Plus (installed). These need a screenshot. Taskbar AI Quota Bars Plus has a preview on GitHub, but the local file is missing.
3. **Stale AI Quota folder**: `davids-windhawk-mods\mods\local\taskbar-ai-quota-opencode` has the old id. The published and live copy is `taskbar-ai-quota-plus`. Recommend retiring the old folder.
4. **No license upstream**: the TreeItem Tweaker source has no `@license` line, so the plus fork has none either. I did not invent one.
5. **Not pushed**: the author-credit and style changes exist only in the working tree. GitHub will show the old metadata until republish.
