# Windhawk Styler 2.0.10 sticky toolbar restored

The user requested the dark background behind Save settings and the Visual mode/Textual mode controls. It separates the sticky controls from settings scrolling underneath.

Removed the transparent-background override on `SaveSettingsCard`. The toolbar again uses the normal card background. With the current 80% card opacity, it renders `rgba(24,24,37,0.8)` with a 16-pixel backdrop blur. Opaque card settings retain an opaque toolbar without extra blur.

Measured verification after deployment and interface restart:

- At scroll positions 500 and 1000, the toolbar stays at viewport y=100, with height 56. Its background and blur remain intact.
- Active and inactive screenshots show the dark rectangle behind Save settings, editing modes, density and fullscreen controls.
- Textual mode opens the Monaco editor with the same toolbar. Visual mode was restored afterward. Save settings remained disabled throughout; no settings changed during these checks.
- The native accent border, clean corners, visible inactive caption and live blur remain intact. No centered startup logo appears.
- Workspace and installed source hashes match. Compilation completed without warnings. Injection remains scoped to `windhawk-ui.exe`.

Final source: `work/windhawk-styler/tauri20/windhawk-styler.wh.cpp`. Installed version: 2.0.10. Evidence and receipt: `reports/2026-10-09-styler-toolbar/`.

The border work and wider window checks are recorded in [the edge verification](2026-10-09-styler-edges.md). The original rendering fixes and actual settings-save checks are recorded in [the stability verification](2026-10-09-styler-stability.md).

Rollback: run `scripts/2026-10-09-styler-toolbar.ps1 -Rollback` elevated to restore 2.0.9. The separate `scripts/2026-10-09-styler-edges.ps1 -Rollback` restores the accepted 2.0.8 appearance. Both compile the backed-up source and reload only this mod; neither restarts the Windhawk engine.
