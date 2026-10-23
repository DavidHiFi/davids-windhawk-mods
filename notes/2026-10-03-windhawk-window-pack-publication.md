# Window pack publication

Published David's Window Pack 1.0.0 to the public repository on 2026-10-03.

- Source and installation instructions: https://github.com/DavidHiFi/davids-windhawk-mods/tree/main/mods/local/david-window-pack
- Source release: https://github.com/DavidHiFi/davids-windhawk-mods/releases/tag/window-pack-v1.0.0
- Official Windhawk catalog submission: https://github.com/ramensoftware/windhawk-mods/pull/5881

The catalog pull request adds exactly `mods/david-window-pack.wh.cpp`. It is open and linked to this T3 thread. Explore visibility requires Windhawk's maintainers to merge the submission and deploy the catalog. GitHub publication alone does not add it to Explore.

The publication includes the complete source, portable x86/x64 build script, installation README and GPL license. MIT notices for Snap Commander and Move Window to Monitor remain in the single-file source. The repository index and manifest identify the pack and mark its three replacements disabled. The snapshot tool recognizes the new local mod path.

The C++ implementation matches the tested installed source after comments and whitespace are removed. Publication changes cover the author metadata, installation documentation, corrected comments and licensing notices. Both public-source builds passed. The official catalog validator passed its full single-file validation with zero warnings, including symbol extraction. The GitHub PR flow-label check passed; no additional upstream check result was reported at handoff.

Verified that the public repository and catalog branch contain the same Git blob, `15ed5010bfcb316547d85715b2fac27ec3705060`. Downloaded the published ZIP and confirmed its SHA256 matches the upload. Receipt: `reports/2026-10-03-window-pack-publication-receipt.json`.

Publication commit: `0e805de191c63ec35a7f7bae123d05102ecccc9b`. Catalog branch commit: `1660e0e` in `DavidHiFi/windhawk-mods`, branch `add-david-window-pack`.

No live mod or system setting changed during publication. The earlier installed build remains active.

## 2026-10-03 author metadata repair (installed copy)

Observed in Windhawk UI: the installed mod page showed author `david high five` while `@github` and `@homepage` already pointed at `https://github.com/DavidHiFi` and `https://github.com/DavidHiFi/davids-windhawk-mods`. Every repository and work copy already carried `@author DavidHiFi`; only `C:\ProgramData\Windhawk\ModsSource\local@david-window-pack.wh.cpp` still held the stale string.

Change: line 6 `// @author          david high five` → `// @author          DavidHiFi`. No other line touched; version, includes and code unchanged, so no rebuild or restart of the injected mod was needed.

- Backup before edit: `backups/2026-10-03/local@david-window-pack.wh.cpp.bak` (original), `.bak2` (second copy taken by the elevated writer).
- Write required silent elevation; the unelevated attempt failed with access denied and was not retried inline.
- Verification: reread of the header shows `DavidHiFi` plus both GitHub links; a full scan of `C:\ProgramData\Windhawk` and `H:\System Configuration\work` finds no remaining `high five` string.
- Rollback: copy the `.bak` back over the source with the same elevated route.
- Windhawk was running during the edit; the app may show the cached author until the mod page is reopened or Windhawk is restarted. No system setting, driver or live process was changed.
