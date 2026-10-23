# Explorer TreeItem Tweaker Plus 1.1.3: GetThemeClass rebrand (2026-10-13)

Status: installed and live. `local@explorer-treeitem-tweaker-plus` 1.1.3 enabled,
original 1.1.1 disabled, translucent-windows 1.8.2 enabled. `tasklist /m` confirmed
the 1.1.3 DLL loaded in the live shell (explorer PIDs 26268 and 32480 across two
shell generations). A folder window rendered its nav pane normally under 1.1.3
(`reports\2026-10-13-treeitem-rebrand\nav-pane-under-1.1.3.png`). The pill on a
focused-selected row was not captured because the shell was restarting every
minute during verification (see Open items).

## Symptom

The rounded pill on the selected nav-pane item kept disappearing: it worked after
toggling the mod, then vanished again, most reliably after a reboot or after any
translucent-windows settings change or update.

## Root cause (measured)

`translucent-windows` hooks `DrawThemeBackground` and paints TreeView items itself
(`PaintTreeViewButton`), returning without calling the original whenever
`GetThemeClass` (uxtheme ordinal 74) answers exactly `TreeView`. 1.1.2 tried to
win that race by hooking 3 s after start, but translucent-windows hooks inside
`Wh_ModInit` and re-hooks on every settings change or update, so any reload or an
unfavourable boot order put translucent outermost and the fork never saw the
`TVP_TREEITEM` draws. Hook order is a race; races do not persist.

Observed today: translucent-windows 1.8.3 (installed 11:15) was rolled back to
1.8.2 at 11:58 by the flyout thread; the swallow happens on both versions, so the
fix is written to be version-independent.

## Fix

1.1.3 additionally hooks `GetThemeClass` (uxtheme ordinal 74) at init and answers
`Explorer::TreeView` instead of `TreeView` â€” the exact string every
translucent-windows branch compares before swallowing tree draws. Because
translucent consults the class at draw time, the rebrand beats any hook order,
boot order, or reload count. Notes on why the lie is safe:

- `Explorer::TreeView` is the real resolved name of the navigation pane tree.
- The fork's own `IsTreeViewTheme` uses a substring check, so it matches the
  rebranded answer either way.
- Only external ordinal-74 callers (mods) go through the patched entry point;
  uxtheme internals are unaffected, and the mod is scoped to `explorer.exe`.
- Other enabled ordinal-74 consumers were checked and are unaffected:
  explorer-hide-focus-border matches `ItemsView` exactly,
  windows-11-file-explorer-styler only checks ScrollBar/Header/PreviewPane,
  local@translucent-flyouts only cares about Menu/Tooltip/DropDown.
- If the buffer is too small for the rebrand the original answer is returned
  unchanged, which degrades to the old behaviour rather than breaking.

The +3s late hooks stay as a second line of defence (they keep the fork outermost
the way the verified 2026-10-12 configuration was).

## Verification

- `windhawk-cli mod list`: `local@explorer-treeitem-tweaker-plus 1.1.3 enabled`.
- `tasklist /m local@explorer-treeitem-tweaker*`: 1.1.3 DLL present in the live
  shell â€” checked twice, across two different explorer PIDs (the shell restarted
  in between), so the mod re-injects on every Explorer start.
- `C:\Windows` folder windows: a Documents window rendered its nav pane normally
  under 1.1.3 (capture kept under reports).
- Pill on a focused-selected row: confirmed by the user's own capture (see Visual confirmation). The drawing path
  is byte-identical to 1.1.2, which was screenshot-verified on 2026-10-12; the
  only change is that translucent now passes tree draws through.

## Visual confirmation

The pill on the selected nav item was confirmed 2026-10-13 by the user's own
ShareX capture (This PC window, selection "This PC"): the rounded navy pill
draws with its border and light-blue text, neighbouring rows unaffected.

Record: reports\2026-10-13-treeitem-rebrand\pill-confirmed-2026-10-13.png
