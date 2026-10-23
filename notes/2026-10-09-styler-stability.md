# Windhawk Styler 2.0.8 rendering fixes

Installed and verified on October 9, 2026. Source: `work/windhawk-styler/tauri20/windhawk-styler.wh.cpp`. The installed mod targets only `windhawk-ui.exe`.

Measured causes and changes:

- The sheet veil was a separate layered window above the native frame. Its inactive caption tint had alpha 255, covering the title, icon and window controls. Removed the veil, including its frame-sized bitmap, corner approximation and positioning hooks.
- Windows normally replaces inactive acrylic with a flat fill. The main window now keeps its active frame appearance through composition attribute 15 and a scoped `WM_NCACTIVATE` subclass. Actual foreground ownership, `WM_ACTIVATE` and keyboard focus keep their real state.
- The faint centered logo was leftover startup drawing beneath the transparent WebView. Clearing the root drawing surface before the splash finished was too early. The mod now clears it after a successful page style injection, a two-second settling period and removal of the startup-logo child. Its paint handler keeps the extended frame transparent afterward.
- The old composition structure had its pointer and size fields in the wrong order. Corrected it to the Windows ABI. Added the subclass import library and fixed the Winsock include configuration. The final CLI compile produced no warnings.

Measured verification:

- One visible main window and zero sheet-veil windows.
- Native title, icon and controls remained visible when active and inactive, restored and maximized.
- Both surfaces responded to a controlled dark-to-light background while inactive. Caption mean RGB changed from approximately (69,71,76) to (117,119,124); the body changed from (40,42,57) to (52,55,71). This proves the inactive backdrop remains live.
- On the same light background, active/inactive caption means differed by less than 0.1 per RGB channel and body means by less than 0.4. The small differences over the dark background are consistent with the other installed animated background effects (inferred); neither surface switched to a flat inactive fill.
- Twelve controlled focus transitions, maximize/restore, resize and minimize/restore passed. Screenshots show clean rounded outer edges and no centered logo.
- Clicked the actual Save settings button twice, changing the accent from `#89b4fa` to `#89b4fb` and back. Each save closed and reopened the interface, and the injected page reflected the saved color. The original accent is restored.
- Text/accent contrast checks passed at 8.19:1 and 8.91:1 for the sampled pairings. This was not a full accessibility audit of Windhawk.

The native caption uses the system material directly; the page keeps the user's 75% background tint. The caption therefore remains lighter than the page. No extra overlay covers the frame or its controls.

Evidence: `reports/2026-10-09-styler-stability/receipt.json`, `visual-verification.json`, screenshots and saved API references. Previous claims about the legacy accent path used the malformed composition structure and should not be treated as reliable API tests.

Rollback: run `scripts/2026-10-09-styler-stability.ps1 -Rollback` elevated. It restores the backed-up source and compiles 2.0.7; the existing helper reopens the interface. The prior registry export, source and DLL are in `backups/2026-10-09/styler-stability/`. This rollback preserves subsequently changed settings.
