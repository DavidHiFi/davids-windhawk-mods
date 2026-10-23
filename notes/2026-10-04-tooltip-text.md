# Tooltip text fix

Installed local@translucent-flyouts 0.6.6, revision 27, on 2026-10-04.

Explorer drive tooltips drew black text because TooltipDrawTextCallback used a fresh buffered DC without setting its text color. The callback now sets the configured color and transparent background mode, and calls the original DrawTextW to avoid hook recursion. The DrawTextW hook handles DT_NOCLIP and buffered tooltip DCs. The themed text paths explicitly pass DTT_TEXTCOLOR. Both tooltip color settings are white.

Both architectures compiled and installed hashes matched. A live Explorer screenshot confirms white drive tooltip text: reports/2026-10-04/explorer-tooltip.png. Transparency settings were preserved. No engine restart was issued. Ableton was added to the injection exclusions to respect the protected audio chain.

Backup and receipt: backups/2026-10-04/tooltip-text. Install, audit, and rollback: scripts/2026-10-04-tooltip-text.ps1. Run mutating modes elevated through the CMD wrapper route. The native test application's tooltip was transparent/invisible and did not establish visual success; the Explorer screenshot did.

The public repository and catalog were not published by this task. The editable local sources and installed ModsSource contain the fix.
