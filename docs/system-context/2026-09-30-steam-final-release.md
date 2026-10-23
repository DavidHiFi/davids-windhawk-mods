# Final Steam publication, 2026-09-30

Published v1.1.5 at https://github.com/DavidHiFi/millennium-stuff/releases/tag/v1.1.5.
Commit and remote main/tag are c68cc20de0369ceb3c37fd904c1d62ca94374267.
The working tree is clean. The commit contains the five handed-off backend/CSS
files and docs/mocha-steam.md guidance for the Windhawk exclusion.

Windhawk Titlebar for Everyone injected browserType=3 into every Steam popup.
The continuation thread backed up and excluded steamwebhelper.exe only.
Independent read confirms Disabled=0 and ExcludeCustom=steamwebhelper.exe.
The mod remains enabled elsewhere. Its served HTML is clean, and the current
session closure was repaired through the existing background connection.

A native in-game toast used type 0 with body 283x70 and card 283x66, leaving the
normal 4px margin rather than the oversized 39px strip. A hidden desktop fixture
used type 4 at 283x70. Store dropdown fixture computed blur 16px, mantle 0.78 and
1px edge. Main controls retain their bottom-left geometry, sidebar alpha 0.9.
Detailed implementation and evidence limits are in
notes/2026-09-30-steam-final-fixes.md.

Publisher independently verified installed hashes for backend and three CSS
files, plus the backend/source mirror. git diff --check passed. The release
ZIP contains all 191 tracked files, each byte-identical to its committed blob.
GitHub asset digest matches SHA256
88046af53c721e7b526576dd065adce008378253382200e3d88518a5098b7e99.

No Steam restart or game-file change occurred. The active game was preserved.
Fresh game launch and full actual store visuals remain untested. An overlay
created before the fix may remain until the current game session ends.
No restart is pending for the Windhawk exclusion. Inherited DWMX backend
settings load from saved files on the next normal plugin/application start.

Rollback for the system exclusion is scripts/Repair-Steam-TitlebarConflict.ps1
-Rollback, which restores its backed-up original value. Theme/backend rollback
uses the matching files from v1.1.4. Do not reset the shared working tree.
Evidence and archive are in reports/2026-09-30-steam-final-release.
