# Translucent Windows blur fix — install, revert mystery, restore (2026-10-11)

Task thread: `6dcfec35-c1fd-4b74-843c-7bc26e439c7a` (failed on provider error at 21:23),
continued in `ec600b95-653b-44ec-9350-eeeed39d16af`. All Windhawk-side files live in
`H:\Windhawk Configuration`; this note records the full state because the continuation
session can only write inside `H:\System Configuration`.

## Bug

Newly opened Explorer windows sometimes showed a flat static tint with no acrylic blur.
The Translucent Windows mod applies the accent policy once, at window-creation time,
before the window is shown and composited; DWM occasionally fails to build the acrylic
material from that pre-show state (same class of race as upstream
ramensoftware/windhawk-mods#5122).

## Fix (local fork, version 1.8.3)

Source: `H:\Windhawk Configuration\Windhawk\translucent-windows\translucent-windows.wh.cpp`
(sha256 `B1B906…DB0B`). Change: explorer-only, one-shot re-apply timer
(`ArmAccentReapplyTimer` / `DelayedReapplyTimerProc`, 100 ms ticks, max ~4 s): once the
window is actually visible, toggle the accent policy off and on between two DWM frames —
which forces the backdrop to be rebuilt without visible flicker — then re-run eligibility
and apply effects. No change for any other app; Discord and others untouched.

- Build: `translucent-windows_1.8.3_478335.dll`, x64 sha256 `88C35BAC…4AAB`,
  x86 `D907CD57…C1`, compiled 21:00 via `windhawk-cli mod compile`.
- Validation (earlier session, occlusion-checked test `blur-test.ps1`): fix runs
  0 flat / 12 valid trials (runs 2–4); stock 1.8.2 baseline 1 flat / 12 valid (run 2),
  plus earlier unvalidated baseline runs with up to 9 flat captures (some were
  occlusion artifacts). stdev ≈ 0 is the bug signature; threshold 0.2.

## Timeline

| Time (local) | Event |
|---|---|
| 21:00 | Fix installed (receipt-install.json), registry → 1.8.3/478335 |
| 21:07–21:19 | Test cycles, rollback to 1.8.2/795679, baseline test |
| 21:21:52 | Reapply → 1.8.3/478335 verified loaded in explorer (receipt 21:22:06) |
| 21:22:30 | Last good read: registry 1.8.3; explorer mapped 373279 + 478335 |
| 21:22:17 | `translucent-windows_1.8.2_373279.dll` written by unknown actor |
| 21:23:04 | Thread failed (provider 400) — wrap-up never ran |
| later | Mod found reverted: source = stock 1.8.2 (`0F8801…`), registry 1.8.2/373279 |
| 23:07 | Restored the fix (below), hash-verified |

## The revert (unattributed)

Between 21:22:30 and ~22:50 someone recompiled stock 1.8.2 into a new revision
(`373279`), flipped `LibraryFileName` to it and overwrote `ModsSource` with pristine
1.8.2. Facts: Windhawk UI did **not** run tonight (newest UI log folder 2026-10-09);
`SettingsChangeTime` was never bumped again (still the 21:21:52 value); no explorer
crash (no WER report, no Application-log entry); no reboot (Mullvad from 09:10 still
alive). No engine-side log exists to attribute it. If the user reverted it deliberately
via some other tool, say so; otherwise treat as unexplained. The pre-restore state is
backed up: `backups\2026-10-11\translucent-windows-blur-fix\current-after-revert-1.8.2-373279.reg`.

## Restore (2026-10-11 23:07, this session)

`Invoke-Elevated.ps1` → reg export (above) + `2026-10-11-translucent-windows-blur-fix.ps1
-Action Reapply` (no recompile; reuses the hash-identical 478335 DLLs, imports
`fix-state.reg`, bumps `SettingsChangeTime`). Verified independently: registry
1.8.3/478335, ModsSource `B1B906…`, x64 DLL `88C35BAC…`, x86 `D907CD57…`, and the
elevated readback shows the 1.8.3 DLL mapped in the live explorer process. Receipt:
`reports\2026-10-11-translucent-windows-blur-fix\receipt-reapply.json` (23:07:13).

Not re-run: the 12-trial blur test (the restored DLL is byte-identical to the validated
build; automation could not spawn Explorer windows from the continuation sandbox).
A fresh visual check: open any Explorer window — it should show mottled acrylic, never
a flat tint. `Get-Process`/WMI/tasklist/COM-enumeration are all restricted in that
sandbox; a desktop screenshot proved Explorer was healthy all along.

## Side effect to disclose

The earlier test's trial-04 sent WM_CLOSE to a window that turned out to be the
**FreeDictate settings window** (not an Explorer window); the process is alive with no
main window, so the settings window was most likely closed by the test. Reopen it if
needed. The test script has since been hardened to only close windows it opened
(CabinetWClass + expected folder title).

## Rollback

Elevated: `…\scripts\2026-10-11-translucent-windows-blur-fix.ps1 -Action Rollback`
(returns stock 1.8.2/795679 + source). Or import either reg backup. Old revisions stay
mapped until Explorer restarts — cosmetic, precedented, stable.

## Change log

| When | What | Old → new | Test | Undo |
|---|---|---|---|---|
| 23:07 | translucent-windows restored to 1.8.3 fix | 1.8.2/373279 → 1.8.3/478335 | hash + registry + loaded-module readback | `-Action Rollback` or reg import |
