# Styler 2.0.12 — visible WebView after every save restart

Date: 2026-10-09
Thread: 7a15511f-17b4-4b61-8fff-da47eceade79 (continuation; install + verify rounds completed 02:39–02:44)

## Change (2.0.11 → 2.0.12, diff of backups\2026-10-09\styler-visible\work-source.wh.cpp)

- New `g_pageReady` flag and `MainWindowPass()` visibility guard: in the 1-second
  worker pass, if the page is ready, the main window is visible and not iconic,
  no startup logo remains, and the `WRY_WEBVIEW` child is hidden
  (splash handover can leave a rendered page in a hidden native host), the mod
  shows it with `ShowWindowAsync(SW_SHOWNOACTIVATE)` and logs
  "restored hidden WebView". Also called after the CDP theme push.
- Acrylic title-bar mode: one Windows material across caption and body
  (veil forced transparent when nativeTitleBar + titleBarAcrylic + blur);
  background tint/opacity now scoped to "Acrylic title bar off".
- Page-injected JS readiness gate (`return 'loading'` until the root has
  children) so the style is not evaluated against a still-loading DOM.
- Harness: `reports\2026-10-09-styler-visible\verify-save.ps1` extended to
  four Save-button rounds, each ending in `WaitPage` plus
  `reports\2026-10-09-styler-visible\check-native.py` (main window, WebView,
  render host visibility, no splash, responsive).

## Verified (measured)

- 2.0.12 compiled and installed: dll
  `local@windhawk-styler_2.0.12_903057.dll`, source hash ECAF7258BBA…, include
  `windhawk-ui.exe`, receipts in `reports\2026-10-09-styler-visible\receipt.json`.
- Four real Save-button restarts passed (accent flips #89b4fb ↔ #89b4fa,
  original restored): UI 12956/38336 → 24548 → 19092 → 5584 → 18664;
  page-ready 18.9–22.1 s per round; 8 px reset spacing on every round;
  no `restartOnSave` setting; theme (FiraCode Nerd Font, transparent acrylic
  body) correct after each restart. Details in
  `save-verification.json`, native proof in `native-save-0..3.json`.
- The new recovery fired live once: `[02:41:36 pid=24548] restored hidden
  WebView (0)` — round 2 still passed its native check.
- Recurring `http get failed (0)` log lines are the one-shot CDP theme push
  attempt racing the devtools server at boot; present in all passing versions,
  styling is applied at the patched put-sites, not a regression.

## Rollback

`H:\Windhawk Configuration\scripts\2026-10-09-styler-visible.ps1 -Rollback`
restores 2.0.11 from `backups\2026-10-09\styler-visible` (registry + both sources
+ recompile).
