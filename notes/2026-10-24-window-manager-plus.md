# 2026-10-24 Window Manager Plus 1.2.0

- Renamed the mod "Window Manager" to "Window Manager Plus". The id stays
  `local@window-manager`, so settings, the registry key and the helper process carry over.
- New setting `cursorFollowsWindow` ("Move the cursor with the window", off by
  default). When on, the pointer jumps to the middle of a window sent to another
  monitor. Both keyboard paths use it: Alt+Shift+arrows (and the other modifier
  choices) and Alt+] / Alt+[. Only Alt+Shift+arrows was live-tested. Minimized windows are skipped.
- Turned on for this machine by the install script (measured: registry value 1).
- Build: `Windhawk\window-pack\Build-window-manager-1.1.4.ps1 -Version 1.2.0 -Revision 1`
  (engine 2.0.0). x64 SHA-256 403CB495...D804, x86 033CB01C...2C15.
- Install and rollback: `scripts\2026-10-24-window-manager-plus.ps1 -Install|-Rollback`
  (elevated). Backup in `backups\2026-10-24\window-manager-plus\`; pre-edit source in
  `backups\window-manager-window-pack-pre-1.2.0.wh.cpp`.
- Live test (`scripts\2026-10-24-window-manager-plus-cursor-test.py`, own Tk window):
  Alt+Shift+Right moved monitor 1 to 3 and Alt+Shift+Left moved 3 to 0; the cursor
  landed on the window center both times. Result in `reports\2026-10-24-window-manager-plus-cursor-test.json`.
  The first run right after the install saw no move at all (the helper was still
  reloading); the reruns passed.
- Repo `davids-windhawk-mods`: source and readme changes committed on branch
  `window-manager-plus-cursor` (commit `21323d4`) and pushed to origin. Pull request
  #20 is open against `main`, not merged. Checked on GitHub: base `main`, head
  `window-manager-plus-cursor`, state open, mergeable.
- `manifest.json` and `mods/catalog` are left out of the PR. CONTRIBUTING says
  `tools\Build-Repo.ps1` regenerates them from the live install.
- Local-only, not in git: `backups\window-manager-window-pack-pre-1.2.0.wh.cpp` and the
  proof images in `work\` (the root `.gitignore` excludes them).
