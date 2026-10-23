# Title bar menu is red (2026-10-13)

Resolved (13:07): windhawk-ui.exe is on translucent-flyouts' process block list, so the Windhawk window uses the plain Windows menu. See `notes\2026-10-13-titlebar-menu-standard.md`.

Update (12:51): the menu colour changed after the rollback, and its look needs a re-check. The translucent-flyouts thread rolled back to 0.6.16 (modern acrylic, Mocha 80%), and that build is loaded in windhawk-ui. Its colour decision is still open: `notes\2026-10-13-translucent-flyouts-menu-colour-attempts.md`.

Symptom: right-clicking the Windhawk title bar opens the system menu with a solid red fill. The items and their enabled states are correct.

Measured:

- The red fill is #FF0000. Sampled from the owner's screenshot, pixels inside the menu body.
- The earlier verification shot `reports\2026-10-13-styler-polish\sysmenu-shot.png` (12:09:11) shows the same menu near-black, #040405 to #050505.

Timeline (file times):

| Time | Event |
| --- | --- |
| 12:08:08 | Windhawk Styler 2.0.45 installed (DLL built 12:08:01; same menu code as now) |
| 12:09:11 | Dark menu captured |
| 12:09:27 | translucent-flyouts 0.6.17 installed |
| 12:19:35 | translucent-flyouts 0.6.18 installed (diff vs 0.6.17 is logging only) |
| 12:21:37 | Windhawk Styler 2.0.46 installed (DLL built 12:20:34; CSS only, no menu change) |
| 12:21:43 | windhawk-ui.exe restarted, loads translucent-flyouts 0.6.18 |
| 12:27 and 12:31 | translucent-flyouts 0.6.19 and 0.6.20 installed; 0.6.20 is loaded in windhawk-ui now |

Diff 0.6.16 to 0.6.17 (`Windhawk\translucency-flyouts\build-0.6.1{6,7}`):

- `HandleMenuDrawThemeBackground` and `HandleCustomRendering` replaced `PatBlt(..., BLACKNESS)` with `FillMenuBody(hdc, rc, tint)`.
- `FillMenuBody` paints a solid brush from `MenuBodyTint(state)` when a tint is set.

build-0.6.20 still has the same path: `FillMenuBody` defined at line 2833, called at 2896 and 3026.

Styler side: `ShowSystemMenu` in `windhawk-styler.wh.cpp` (GetSystemMenu, uxtheme ordinal 135 and 136, TrackPopupMenu) has not changed since 2.0.45.

Conclusion (inferred): translucent-flyouts 0.6.17 and later paint this menu's body with a bad tint. The exact line that produces pure #FF0000 is not confirmed.

Debugging note for the owner: `Log::IsTargetProcess` in translucent-flyouts covers explorer.exe and a few test hosts, not windhawk-ui.exe. Its debug log will not capture this process until that list includes windhawk-ui.exe.

Owner: translucent-flyouts thread (coop 55f21ec1). Board note posted 2026-10-13. Nothing in translucent-flyouts was changed by this thread.

Options (owner's call):

1. Add windhawk-ui.exe to translucent-flyouts' advanced process block list. The title bar menu returns to dark-menus styling. The Windhawk window loses only its native-menu translucency.
2. Fix the menu fill for windhawk-ui.exe in translucent-flyouts and keep the translucency.
