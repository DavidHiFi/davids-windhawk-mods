# Start Menu Styler: OnlySearch Mocha theme

Published to https://github.com/DavidHiFi/davids-windhawk-mods/tree/main/themes/start-menu-onlysearch-mocha
in commit `476ad39` on `main`. The same commit refreshed the snapshot from the live install:
six new catalog mods, one removed, five catalog version bumps, and current settings.
Local mod sources and their manifest entries stayed at the published revisions.
The live weather 1.2.3 and system-info-weather 1.0.1 builds were left for their owning thread to publish.

The theme merges OnlySearch (redesigned variant) with RosePine and recolors it with Catppuccin Mocha and a blue accent.
The live settings match `onlysearch-mocha.yaml`.

The Textual-mode paste stored the six private-use glyphs (U+E7E8, U+E72E, U+E708, U+E777, U+F78B, U+E713) as empty strings.
`scripts/2026-10-03-start-menu-styler-glyph-fix.ps1` wrote them back through the registry and bumped `SettingsChangeTime`.
No engine restart was needed. A registry read-back confirmed the codepoints.

Rollback: run `scripts/2026-10-03-start-menu-styler-glyph-fix.cmd -Rollback` elevated.
It imports `backups/2026-10-03/start-menu-styler-glyphs/start-menu-styler.reg`.
