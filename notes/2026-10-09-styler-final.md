# Windhawk Styler 2.0.11 final refinements

Installed 2.0.11 after the user accepted the existing appearance and requested reset-button spacing, automatic restart on save without a switch, and removal of a faint logo returning after saves.

The reset control has a built-in negative eight-pixel margin that cancels the title row's gap. That suits a transparent link, but the themed button background touched the setting name. The Styler now sets this control's start margin to zero, restoring the existing eight-pixel gap. Measurements confirmed this gap on every altered setting tested.

Removed `restartOnSave` from the settings schema, settings structure and reads. Both the settings-changed callback and registry save-marker watcher now request a restart unconditionally. Removed the obsolete registry value after backing it up. Saving these mod settings always closes and reopens the interface. The readme describes that behavior without an optional switch.

The native startup splash copies a cached logo bitmap into its window with `BitBlt`. The transparent WebView exposes pixels from that native surface. The previous delayed, one-time root clear did not prevent the logo from being drawn during a fresh startup. The new hook replaces that copy with transparent black only for the current process's `WindhawkTauriStartupLogo` child, and only when blur is enabled. The splash keeps its existing startup and dismissal lifecycle. Other drawing and windows use the original function. Removed the delayed root-DC clear.

Measured verification:

- Compilation completed without warnings. Workspace and installed source hashes match. Injection stays scoped to `windhawk-ui.exe`.
- Two actual Save-button changes restarted the interface and reapplied the font, colors and transparency. The test changed the accent to `#89b4fb`, then restored `#89b4fa`. All other settings matched the starting values, including the user's current 75% card opacity.
- Every tested reset control measured eight pixels from its setting name. The restart option was absent from the settings form.
- Each restarted visible process logged `startup splash painted transparent`. A screenshot with page content briefly hidden showed the full background without a residual logo; the page was restored immediately afterward.
- Twelve focus transitions, changing dark/light backgrounds while inactive, maximize, resize and minimize/restore passed. Caption and body pixels changed with the background while inactive, confirming live blur. The native accent border and 16-pixel corners remain intact.
- The obsolete restart registry value was removed and the interface refreshed. Final Audit verifies the loaded DLL and source hashes.
- Textual mode opens normally and contains no legacy restart option. Visual mode was restored with Save settings disabled. The frosted toolbar retains its 16-pixel blur and current card opacity.

Evidence: `reports/2026-10-09-styler-final/`. The receipt identifies the exact DLL. `save-verification.json` records real saves and spacing; `visual-verification.json` records window checks. `background-after-save.png` exposes the area where the faint logo had appeared, and `settings-after-save.png` shows the final settings layout.

The stock startup theme can appear briefly before the Styler's CSS is applied. This work removes the centered splash mark, not the interface's startup time. The two measured saves reached the themed page in about 22 seconds, including closing the old processes and creating WebView2.

Rollback: run `scripts/2026-10-09-styler-final.ps1 -Rollback` elevated. It restores the backed-up 2.0.10 source and legacy switch value, then compiles a new DLL revision and reloads this mod. It does not restart the Windhawk engine. Backups are in `backups/2026-10-09/styler-final/`.
