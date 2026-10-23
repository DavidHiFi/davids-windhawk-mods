# Windhawk Styler audit and release

The owner accepted the integrated title bar and 75% Acrylic appearance, then asked for cleanup and GitHub publication. They stopped further testing on 2026-10-09 to conserve their usage limit.

## Changes

- Removed the stale machine VSCodium selector that opened the wrong interface after reboot. The engine service stayed running.
- Removed the separate caption popup and padded-icon machinery. The real window paints its caption, retains the original icon, and uses Windows hit testing and buttons. A real mouse drag recorded 137 distinct window positions with no detached caption window.
- Fixed the fresh-launch edge gap and repeated-save window growth.
- Reordered all twelve settings and rewrote their names and descriptions. Preserved the owner's colors, FiraCode Nerd Font, 75% background opacity and 90% card opacity.
- Removed hardcoded diagnostic paths, redundant style writes, obsolete opacity/acrylic registry values and the unused manual build workflow. Archived historical probes and build helpers with hashes. Windhawk's CLI is the single installation path.
- The controlled background probe showed that the legacy Blur option rendered opaque on this Windows build. Removed that option; Acrylic provides the supported frosted background. Legacy blur values fall back to Acrylic. An empty DWM blur region enables transparency in None mode, which the native probe measured against black and white stripes.

## Measured checks and limits

Eight real settings-save cases exercised all twelve fields, including colors, font, opacity limits, blank defaults and title bar switches. Every save reopened a themed interface, read back its expected registry values, showed no error notice, and measured zero side/bottom frame gaps and zero GDI growth across repeated activation. Versions 2.0.29 through 2.0.32 were used during this matrix.

The final 2.0.33 build compiled successfully. It preserves the tested Acrylic path and includes the last None-mode correction and removal of the unsupported Blur choice. The owner requested no further test matrix. No whole-PC reboot or universal compatibility claim is made. Main text contrast was calculated as 12.14:1 against cards and 8.69:1 against controls, not certified for every inherited UI treatment.

## Records and rollback

Canonical source: `work/windhawk-styler/tauri20/windhawk-styler.wh.cpp`. Installer: `scripts/styler-maintenance.ps1`. The report's `build-receipt.json` identifies the immediately preceding build backup. Pass its exact backup directory to `-Rollback -BackupPath` elevated under the windhawk-engine coop lock. `obsolete-settings-receipt.json` records the separate backup for the two retired registry values. Historical files remain in the archive.

The publication worktree is `work/styler-release`, based on the other thread's completed Everything commit 96d6d2e. It updates only Styler source, documentation, preview and snapshot entries. The previous published 1.4.0 source and preview are preserved in its legacy folder.

Published and independently verified remote main commit `74250027c0b5428f99ec2e30506deeb0db626420` in DavidHiFi/davids-windhawk-mods.

## Toggle follow-up

Installed 2.0.34. A real disable now starts the existing detached relaunch helper after restoring the frame and runtime patches. It checks the Disabled registry value and ownership of a visible main window, so ordinary exit and recompilation do not reopen the app. The existing late-attach path handles enable. One disable/enable cycle measured fresh process IDs and the expected unstyled/styled page after each toggle. Settings remain 75% Acrylic and the mod is enabled. Receipt: reports/2026-10-09-styler-audit/toggle-relaunch.json.
