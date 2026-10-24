# Handoff: Windhawk UI blur (styler), 2026-10-24 12:20 PM

Predecessor thread: "Restore real blur in Windhawk UI" (settled). Full record: `notes\2026-10-24-styler-blur.md`.

## The user's three asks
1. Window background really blurred, native title bar and body matching.
2. "Save settings" bar properly blurred, so text behind it can't be read.
3. The darker card areas blurred too.

## State (measured unless marked)
- Styler 2.0.68 is live: registry LibraryFileName `local@windhawk-styler_2.0.68_1.dll`, installed DLL hash equals the build. Source committed in worktree `work\styler-release` (branch styler-tauri-release, commit 2ead1a0, not pushed).
- Title strip and body match in color (27,27,38 vs 28,28,39).
- Save bar: 92% card tint plus blur(16px). Text under it is a faint ghost (`work\2026-10-24-windhawk-blur\live-v68-savebar.png`). This hides the text but it is not a true blur of the text.
- Root cause for no true blur: the WebView blurs page text only where the backdrop under it is opaque. In Acrylic mode the page is transparent down to DWM. Proof: `exp-scrolltest.png` vs `exp-scrolltest-opaque.png`.
- Cards: cardOpacity 40, no CSS blur. They show the DWM sheet behind them.

## Open
1. STILL OPEN (12:30 PM the user was in RustDesk fullscreen again). Not checked: real on-screen blur behind the window (asks 1 and 3). The user was in a fullscreen RustDesk session, so no desktop tests. Check `work\2026-10-24-windhawk-blur\idle.ps1`; run desktop tests (stripes-proof.ps1) only under `coop lock desktop` and only while the user is idle.
2. DONE 12:28 PM (2.0.69, see the main note): true save-bar blur via an opaque patch under the bar. Was: possible true save-bar blur: an opaque surface under the settings rows would let backdrop-filter blur them, but it would hide the window blur in that card. Try a scoped variant (opaque only within the bar's band, or a near-opaque settings card) and compare to the 92% floor.
3. DONE 12:28 PM (2.0.70): seam rule merged with !important; scrollbar blocks not needed. Was: thread "Fix Windhawk settings dialog layout" handed over two CSS blocks to merge into the styler payload: `scripts\2026-10-24-windhawk-ui-dialog-fix.css` and `...-round2.css`. The UI serves CSS embedded in windhawk-ui.exe, so the webview css file on disk is never read. User question still open: under the 16 px radii, square the textarea/info-box seam or not.
4. Side finding: the Exclude lists for win11-custom-title-bar-colours and win11-accent-border don't exclude windhawk-ui.exe (it reads as a two-item array), so both still load in it.

## Rules that bit
- Never `windhawk.exe -restart`. Bumping SettingsChangeTime reopens the UI.
- Post a coop note before restarting the UI (other threads use CDP on 9333).
- Python with playwright: `work\2026-10-24-windhawk-ui-dialog\.venv\Scripts\python.exe`. Live CDP scripts: `work\2026-10-24-windhawk-blur\live_v67.py` (navigates with location.hash).
- Deploy scripts: `scripts\2026-10-24-styler-2.0.6x-deploy.ps1 -Install|-Rollback`, run through `H:\System Configuration\scripts\Invoke-Elevated.ps1`.
