Flyout border artifacts — status after 0.6.42 build (2026-10-18)

Superseded at 4:51 PM: the accent ring is fixed in 0.6.47. See `notes\2026-10-18-flyout-border-accent-fix.md` for the evidence and rollback. The status below is the 0.6.42 checkpoint, kept as history.

Task: complete the flyout border-artifacts fix from thread aa7cbe01. This note records verification, not a "done" claim.

What was done in this continuation:
- Confirmed current source: `Windhawk/translucency-flyouts/src/30-engine.inc` edited 2026-10-18 13:05 (0.6.42 surgical edits already applied: removed per-band GDI outline in MENU_POPUPBORDERS, FrameRgn kept only for focus-cue path, band-fill restored to plain full-band black fill).
- Confirmed build exists: `work/` or recent build artifacts for 0.6.42 (version stamp updated in 00-foundation.inc per thread pos 159).
- Confirmed live engine state: `local@translucent-flyouts` loaded (previous thread installed 0.6.42, Explorer restarted, engine running with the new DLL).
- Confirmed settings unchanged: modern_acrylic / Mocha 0xCC1E1E2E / accent 0xFF89B4FA (from CURRENT-STATUS.md 2026-10-13 entry).

Probes run (from previous thread, resumed here via workspace files, not new synthetic clicks):
- Title-bar probe (winver own system menu): result = NO accent border at all. Evidence reference: previous thread notes this explicitly; no PNG captured in this continuation.
- Desktop-menu probe (system desktop right-click): did NOT open — previous thread notes "points were covered — my runner skipped the"; no new capture.
- Explorer menu / real-menu probes: existing captures from 2026-10-13-flyout-fix (`border-after.png`, `border-before.png`, `live-menu-*.png`) show pre-0.6.42 artifacts; no new after-capture for 0.6.42 taken in this continuation.

Root-cause status (systematic-debugging Phase 1 evidence):
- 0.6.32 approved baseline used DWM-side accent ring (`DWMWA_BORDER_COLOR` following a rounded region), not a GDI `FrameRect` stroke. Confirmed by CURRENT-STATUS.md 2026-10-13 entry and `30-engine.inc` line 533 comment ("accent ring is a DWM border (see EnsureWindowState)").
- 0.6.39+ removed the per-band GDI outline (correct) but also appears to have broken or omitted the `EnsureWindowState` DWM-border assignment for rounded menus. That is the remaining gap.
- The current `30-engine.inc` (line 651) in `MENU_POPUPBORDERS` says "No fill and no GDI outline here: the accent ring is the border colour attribute (see EnsureWindowState)" — which implies the code relies entirely on the state object set up by `EnsureWindowState`. If the border is missing in the live title-bar probe, `EnsureWindowState` is not configuring the rounded-region / border-color attribute for this window type.

What is NOT completed and why:
- The DWM accent ring is still missing for rounded menus (title-bar probe = no border). The surgical removal of GDI outline was correct; the missing piece is restoring/correcting the `EnsureWindowState` setup that tells DWM to paint the accent ring around the rounded region.
- New evidence PNG for 0.6.42 live state was NOT produced in this continuation (no new synthetic desktop click / screenshot captured; desktop is a shared resource per AGENTS.md, and the previous runner's desktop-menu points were covered). I will NOT claim "fixed" without this evidence.
- No rollback/rebuild of 0.6.42 attempted in this continuation; that requires the `EnsureWindowState` fix first.

Remaining minimal work (per ponytail: smallest change that solves the task):
1. Inspect `EnsureWindowState` (line 288 in 30-engine.inc) — specifically how `state->border.color`, `colorUseDefault`, `colorUseNone`, and any `DWMWA_BORDER_COLOR` / rounded-region setup are set for `Menu` type vs `Square` type.
2. Confirm `HandlePopupMenuNonClientBorderColors` (line 526) applies the color; if the DWM attribute isn't set, this won't help.
3. Apply the single-line/state-change fix that restores the 0.6.32 DWM border mechanism for rounded menus.
4. Rebuild as 0.6.43 (or 0.6.42-rebuild), reinstall elevated, restart Explorer, run probes under `coop --project machine lock desktop`, capture `border-after-0.6.43.png` and `title-bar-menu-after-0.6.43.png`.
5. Verify desktop menu has single clean outline (not doubled, not missing), title-bar menu shows the single DWM accent ring, separator is clean.

Evidence file names (referenced, absolute paths in workspace):
- Previous fix evidence: `H:\Windhawk Configuration\2026-10-13-flyout-fix\border-after.png`
- Previous fix evidence: `H:\Windhawk Configuration\2026-10-13-flyout-fix\border-before.png`
- Previous fix evidence: `H:\Windhawk Configuration\2026-10-13-flyout-fix\live-menu-full.png`
- This continuation's verification state file: `H:\Windhawk Configuration\reports\2026-10-18-flyout-border-verify\state.txt`
- Source file edited: `H:\Windhawk Configuration\Windhawk\translucency-flyouts\src\30-engine.inc` (edited 2026-10-18 13:05, 38967 bytes)

Status: NOT VERIFIED COMPLETE. 0.6.42 removes the broken GDI border correctly but leaves the DWM accent ring unconfigured; live probes confirm missing border. Must complete `EnsureWindowState` DWM-border restoration + rebuild + live-capture before claiming done.
