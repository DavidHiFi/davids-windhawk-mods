# Flyout accent: desktop menu diagnostic (2026-10-18)

Status: NOT FIXED. The desktop context menu in your screenshot still has no accent ring. The
installed mod is back on 0.6.47, the same build that was running before this session.

## What the measurements show

- The real desktop menu was opened and captured with no clicks and no cursor movement. It is
  321 by 590 px, the same menu as your screenshot. Captures:
  `reports\2026-10-18-flyout-border\desktop-menu-0.6.48-diag-215051.png` and
  `desktop-menu-0.6.48-diag2-*.png`.
- With a logging build (0.6.48-diag, `TF_DEBUG_LOG`) loaded into a freshly started explorer.exe,
  the menu painted with zero theme draw calls in the log. The hooked `DrawThemeBackground` never
  ran for it, so `MENU_POPUPBORDERS` never reached the accent-ring code. Log copy:
  `reports\2026-10-18-flyout-border\tf-explorer-0.6.48-diag-215051.log` (8 init lines only).
- The menu window is class `#32768`, visible, and paints its own dark body. Its DirectUI library
  (`dui70.dll`) was the faulting module in an Explorer crash at 9:52:06 PM. This suggests the desktop
  menu is drawn through DirectUI rather than uxtheme. Not yet proven.
- DWM test on the open menu (`scripts\2026-10-18-dwm-border-test.ps1`): setting
  `DWMWA_WINDOW_CORNER_PREFERENCE` = round and `DWMWA_BORDER_COLOR` = `#89B4FA` returns S_OK, but the
  edge pixels do not change (left edge 232332 before, 232433 after). DWM alone does not draw the
  accent on this menu. Images: `dwm-test-before.png`, `dwm-test-after.png`.

## Why 0.6.42 to 0.6.47 did not reach it

Every fix since 0.6.42 changed the paint code inside the uxtheme hooks. The desktop menu never enters
those hooks, so none of those changes could show on it. The 0.6.47 "verified" result came from a
native test menu (`MenuTest.exe`), which does use the uxtheme path. It was never checked on a real
Explorer menu. The earlier handoff said the `DWMWA_BORDER_COLOR` injection was removed from
`ApplyWindowEffects`; it is still in `src\30-engine.inc` (lines 228 to 238). That claim was wrong.

## Options for the next step (for the user to pick, recommendation first)

1. Paint the ring onto the menu window from inside explorer.exe: subclass each popup `#32768` window
   (same process, so allowed) and draw a 1 px rounded accent frame on its window DC after WM_NCPAINT
   or WM_PRINT. Recommended. It reaches every popup regardless of who draws the body. Needs a new
   build, one Explorer restart, and a before and after capture.
2. Hook the DirectUI menu paint in dui70.dll. More fragile across Windows updates, and the library
   is not a stable interface.
3. Leave the desktop menu as it is and fix only uxtheme menus (apps, title bars). That does not match
   the complaint.

## Operational notes

- Several Explorer restarts today left duplicate shell instances and a missing desktop window for a
  few minutes. Winlogon relaunches explorer.exe by itself when it is killed. A restart script that
  also calls `Start-Process explorer.exe` starts a second copy. Use a kill and let Winlogon relaunch.
- `desktop` is not declared in `.agent-coop.json`. Coop accepted the lock anyway; declare it.
- Diagnostic code (`#ifdef TF_DEBUG_LOG` blocks, the `kMaxLines` change in `00-foundation.inc`)
  stays in `src` until the fix lands. Release builds are unaffected.
- Installed state: LibraryFileName `local@translucent-flyouts_0.6.47_1.dll`, Version 0.6.47.
  Rollback record: `backups\2026-10-18\translucent-flyouts-0.6.48-diag\`.
