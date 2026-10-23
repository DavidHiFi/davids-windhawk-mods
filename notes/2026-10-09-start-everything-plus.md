# Everything Start menu Plus publication

Published to DavidHiFi/davids-windhawk-mods on 2026-10-09 at about 6:17 AM AWST. Commit `96d6d2efb6023a4d0c08e8619b965492bee6b892` on `main`.

Fork name: Everything & Power Tools in the Start Menu Plus. ID: `start-everything-plus`, installed as `local@start-everything-plus`. Author: DavidHiFi. Version: 1.0.4. The upstream GPL-3.0 license and bardelyne credit remain in the mod and its documentation. The folder includes the GPL-3.0 license text.

This was an organizational publication of the accepted working 1.0.4. Only metadata and README text changed. The full source section after the mod README, including settings definitions and executable code, matches the accepted build byte for byte after newline normalization. Runtime section SHA256: `dc6d0cb50f4df18039b29ad806cc2d8e0a433c8e68cb6bc5536e6b87e71dc0be`.

Migrated the complete mod registry key and any per-mod storage to the Plus ID. Independently checked copied settings against the earlier working settings. The older local placeholder and original gallery mod remain disabled for rollback. The repository snapshot generator omits the retired placeholder and recognizes the Plus source as a local fork.

Compiled the new ID with the production Windhawk toolchain. Independently enumerated the new Plus DLL alongside Start Menu Styler in StartMenuExperienceHost, SearchHost and Explorer. Installed DLL: `local@start-everything-plus_1.0.4_710104.dll`, SHA256 `8F3AB95BEFF53928134AAC63251D41598D8D7ACC8AE57A7E8B91FB52E45F430F`. Installed source matches the published source.

Captured new previews from the live, migrated mod. Idle preview shows the compact search box and all six native action icons. Expanded preview uses the query `network`, with six Windows settings results and two Everything folder results. Displayed paths are under C:\Windows\INF. Checked the preview for personal content before publishing. Crops were captured directly from the screen and were not generated images.

Repository additions include the source and README, both preview images, license, manifest and scoped settings/state snapshot, and the snapshot generator mapping. A separate `onlysearch-mocha-everything-plus.yaml` companion theme saves the working frame ceiling and single-glyph power slot. The original standalone theme stays intact. The live theme and size settings were not changed during publication.

Validated source equivalence, copied settings, manifest counts and uniqueness, required source/preview/license files, PowerShell syntax, and git whitespace checks. Pushed the isolated worktree commit to origin/main without forcing. Independently verified the remote commit with ls-remote and the published source/preview through GitHub's API. No PR was created. The clean main checkout was fast-forwarded to the published commit.

Rollback script: `scripts/2026-10-09-start-everything-plus.ps1 -Rollback`, elevated. It disables the Plus ID and restores the accepted older local ID and source from `backups/2026-10-09/start-everything-plus/`. Its `-Audit` mode reads the installed state. Receipt, captured originals, build, behavior check and validation are under `reports/2026-10-09-start-everything-plus/`.

No full engine or Explorer restart was performed. No restart is pending. Reboot persistence was not separately tested.
