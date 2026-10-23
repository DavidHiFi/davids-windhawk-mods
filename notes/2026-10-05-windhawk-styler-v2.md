# Windhawk Styler 1.1.0

Installed revision 3 and published commit eae19f51bf29c7cdb7eb0b4c68504b1a1b511053 to DavidHiFi/davids-windhawk-mods main.

The UI now uses Electron transparency and acrylic on its actual window. Whole-window opacity and the separate backdrop window are gone. Text and controls stay sharp, and the window corners have no detached backdrop squares. Settings include background opacity, acrylic/blur/none, card color and opacity, control color, accent color, text color, font and native title bar.

The native Windows title bar requires a solid background in bundled Electron/VSCodium 1.74.2. The setting description and readme state this. Custom title bar mode retains true background transparency and blur.

Preserved background #1e1e2e, background opacity 50 and FiraCode Nerd Font. Left native title bar off so the existing acrylic appearance remains active.

Verification:
- Built x64 and x86 production DLLs with WH_MOD, without WH_EDITING.
- Installed source hash matches the published source.
- Color and details-page screenshots show working independent colors.
- Striped background captures distinguish true blur from whole-window transparency.
- Both title bar modes tested. Native mode hides the VSCodium menu.
- All six modified files restore to baseline SHA256 hashes when disabled.
- All six VSCodium integrity checksums match after re-enabling.
- JavaScript syntax checks pass for patched main.js and extension.js.
- A full UI restart on workbench style changes prevents a stale checksum warning.
- Git publication used isolated work/windhawk-styler/publish. No binaries or temporary test scripts published.
- No global engine restart and no changes to protected communications/audio apps.

Evidence is in reports/2026-10-05-windhawk-styler-v2. Backups are in backups/2026-10-05/windhawk-styler/v2. Audit and disable/rollback use scripts/2026-10-05-windhawk-styler.ps1. Run rollback elevated. Disabling restores the original UI, not the flawed older backdrop implementation.
