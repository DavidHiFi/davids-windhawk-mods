# Simple Window Switcher Plus: cursor toggle and cleanup

Corrected 2026-10-18 by a second pass. The first pass said the readme and file
cleanup were verified complete. That was wrong in the places listed under
"Corrections" below.

## State now

- Setting "Center the Mouse Cursor on the Switched-To Window" (`Accessibility.centerCursor`,
  default off) is on. Value `1` in
  `HKLM\SOFTWARE\Windhawk\Engine\Mods\local@simple-window-switcher-plus\Settings`.
  Mod is enabled (`Disabled` = 0).
- Live source: `C:\ProgramData\Windhawk\ModsSource\local@simple-window-switcher-plus.wh.cpp`.
  It contains the centering code: `CenterCursorOnWindow`, called on a committed Alt+Tab.
  Canceled switches leave the cursor alone.
- Installed rev 5 (`C:\ProgramData\Windhawk\Engine\Mods\32` and `64`,
  `local@simple-window-switcher-plus_1.0.0_5.dll`) contains `SetCursorPos`.
- Repo source (`work\simple-window-switcher-plus\repo\mods\local\simple-window-switcher-plus\`)
  now matches the live source byte for byte. Uncommitted.
- Readme: 27 text lines, plus the preview image the style guide requires.

## Corrections to the first pass

- The first pass removed the readme's preview image. `docs\mod-style-guide.md` requires one.
  It is restored: `media/previews/simple-window-switcher-plus.gif`, tracked in git.
- The repo source did not have the centering code. Synced from the live source.
- The readme is 27 text lines, not 29.
- The six `local@...` build copies it deleted were in `work\simple-window-switcher-plus\`,
  not the workspace root.
- Two copies still sat in the workspace root: `simple-window-switcher-plus-32.dll` and
  `-64.dll`. Both match installed rev 5 byte for byte. Moved to
  `backups\2026-10-18-simple-window-switcher-plus\`, not deleted.
- The `harmonize` skill is not installed. It is missing from the skill list and from
  `.claude\skills`, `.agents\skills` and `H:\Claude`. The readme was simplified with
  `readme-audit` instead.
- No registry backup of the setting was made before the change. The earlier handoff
  named `backups\2026-10-17\swsp-center-cursor\`, which does not exist.

## Not verified

- Live cursor centering on Alt+Tab. Needs one Alt+Tab press at the PC. It was not tested
  here because it moves the mouse while the PC is in use.

## Rollback

- Setting: set `Accessibility.centerCursor` to `0` (elevated write), then bump `SettingsChangeTime`.
- Source: the July version is in git history at `HEAD` of the repo.
- Root DLLs: move them back from `backups\2026-10-18-simple-window-switcher-plus\`.
