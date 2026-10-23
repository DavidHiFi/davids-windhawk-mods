# Steam Alt-drag freeze

Alt-drag on Steam's SDL_app window left the cursor captured and the window
stuck in a modal move loop (GUI_INMOVESIZE). window-manager 1.1.1_3 moves
and resizes Steam windows directly and releases capture on button-up,
without the modal move command.

Installed via scripts/2026-10-05-steam-drag-r3.ps1 (elevated). Steam loads
local@window-manager_1.1.1_3.dll.

Test (synthetic Alt+drag, scripts/2026-10-05-steam-drag-test.py):
8 consecutive moves and 6 Alt+right-drag resizes; every one moved the window,
then reported no capture, no move window, flags 0, responding.
Evidence: reports/2026-10-05-steam-drag/fixed-r3-move.json, fixed-r3-resize.json.

Rollback: run 2026-10-05-steam-drag.ps1 -Rollback elevated (backup in
backups/2026-10-05-steam-drag holds the pre-task 1.1.0 state).

## 1.1.1_4: right button while Alt-dragging maximizes

The direct SDL drag in _3 ignored the right button, so Alt-drag + right-click
did nothing on Steam. _4 handles it like the modal loop does: the drag ends,
capture is released, maximize toggles, and the right release and Alt release
are kept from Steam (no window menu). Installed with
scripts/2026-10-05-steam-drag-r4.ps1; Steam loads _4.

Test (scripts/2026-10-05-steam-drag-rclick-test.py, reports/.../fixed-r4-rclick.json):
in 3 of 4 runs the drag was live (capture held, window restored), and right-click
left the window maximized, capture released, no menu open. Run 1 hit the window
before the test's restore had settled and isn't counted.
