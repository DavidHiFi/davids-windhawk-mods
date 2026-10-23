# Windhawk Styler maintenance

The current edition targets Windhawk 2.0's `windhawk-ui.exe`. Its canonical source is `work/styler-release/mods/local/windhawk-styler/windhawk-styler.wh.cpp`, the checkout published to `main`. Since 2.0.45, releases are built there with `Build.ps1` and installed by the dated `scripts/2026-10-13-styler-polish-*.ps1` installer for that version, which keeps the same audit, backup and receipt steps. The installed source must have the same SHA256. The source folder contains the mod and its background CDP inspection helper. Old builders, probes and DLLs are archived, with their original paths and hashes recorded in the audit report.

Use `scripts/styler-maintenance.ps1 -Audit` to compare source, installed source, version, DLL and injection scope. Run `-Install` elevated under the `windhawk-engine` coop lock. It backs up the registry and source, compiles with Windhawk's CLI and records the DLL. Do not use historical dated installers or restart the engine.

The integrated title bar belongs to the main window. It has no separate caption popup. A restored window has zero side and bottom insets and, with both title bar switches enabled, zero non-client caption height. Its WebView reserves space below the native caption. The original icon stays unchanged.

`scripts/styler-edge-gate.ps1` checks the installation, frame geometry, caption integration, GDI stability and visible page errors. Inspect its screenshot too. `reports/2026-10-09-styler-audit/verify-settings-matrix.ps1` exercises the real settings form and restores the recorded original settings. These checks are tools for future changes, not a requirement to repeat after an already verified build.

Acrylic is the supported frosted material. None uses an empty DWM blur region for alpha composition. The unsupported legacy Blur choice was removed from the release. Existing blur values fall back to Acrylic.

Rollback uses `-Rollback -BackupPath '<exact directory from build-receipt.json>'` elevated under the same coop lock. It restores the previous source and registry and builds a new DLL revision, because loaded DLLs can remain mapped. `scripts/styler-retire-old-settings.ps1` separately backs up and removes only the unused opacity/acrylic values. Its rollback takes the exact directory from its receipt.

The machine and user WINDHAWK_USE_VSCODIUM_UI selectors must be absent. The startup-repair script separately records their rollback. Refreshing the tray process is sufficient; do not run windhawk.exe -restart. Other mods and their parallel threads keep their own sources and settings.
