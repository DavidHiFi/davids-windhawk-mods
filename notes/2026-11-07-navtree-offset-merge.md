# Explorer Navigation Tree Offset merged into GPU Accelerated Explorer View Plus 1.3.0

Date: 2026-11-07. Thread: t3-gex-navtree-merge. Work folder: `2026-11-07-navtree-offset-merge\`.

## What changed

- `explorer-navigation-pane-tweaks` 1.1 (Languster, MIT) is now the `NavOffset` namespace in
  `local@gpu-accelerated-explorer-view-plus` 1.3.0. Same code paths: tree subclass moves the
  tree from `WM_WINDOWPOSCHANGING`, style bits `TVS_HASBUTTONS` / `TVS_LINESATROOT` /
  `TVS_HASLINES` cleared, item background left edge trimmed, WinEvent worker plus one-shot
  repatch threads, full restore on unload.
- Shared hooks instead of double hooks: `CreateWindowExW` goes through `NavTree::OnWindowCreated`
  (called by the page-animation or NavTree hook), and NavTree's late `DrawThemeBackground(Ex)`
  hooks call `NavOffset::CompensateRect` first. NavOffset hooks these itself only when
  page animations / NavTree styling are off.
- Settings: new group **Navigation pane > Tree position and arrows** (`navTree.offset.*`):
  `enabled` (new master switch, reloads the mod), `leftShift` (was `TargetIndent`, clamped
  -100..200), `removeAllGlyphs` (was `RemoveHasButtons`), `removeRootGlyph` (was
  `RemoveLinesAtRoot`), `removeLines` (was `RemoveHasLines`), `compensateBackground` (was
  `CompensateItemBackgroundPosition`).
- Migrated values (measured from the old key): leftShift 0, removeAllGlyphs 1,
  removeRootGlyph 1, removeLines 1, compensateBackground 1, enabled 1.
- Credits: readme Credits names Explorer Navigation Tree Offset 1.1 by Languster (MIT) with
  links; `@author` already lists Languster; code block header credits it too.
- Old mod removed: registry key, ModsWritable key, source and dll deleted (backups first).
- NavTree's "restart Explorer on load" would have run `taskkill explorer.exe` on this hot
  swap, so the install set `NavTreeHandledExplorer` to the running shell's stamp first.

## Evidence (2026-11-07, about 10:10 am)

- Build: clean, `local@gpu-accelerated-explorer-view-plus_1.3.0_1.dll`, sha256 90A4D3C5...EC6DE03.
- Install log: `H:\System Configuration\backups\2026-11-07-elevated\log-101009.txt`:
  churn=False, newLoaded=1, oldLoaded=0, same shell pid before and after.
- Guard check after: 0/2 shell stops, breaker clear, 0 explorer crashes.
- Removal log: `log-102459.txt`, REMOVAL OK.

## Rollback

1. `reg import backup\gpu-mod-1.2.4.reg` (points back at the 1.2.4 dll still in Engine\Mods\64)
   and copy `backup\gpu-1.2.4.wh.cpp` to `ModsSource\local@gpu-accelerated-explorer-view-plus.wh.cpp`.
2. `reg import backup\navtree-offset-1.1.reg`, copy `backup\explorer-navigation-pane-tweaks.wh.cpp`
   to ModsSource and `backup\explorer-navigation-pane-tweaks_1.1_573450.dll` to Engine\Mods\64.
3. Registry-only reload; never `windhawk.exe -restart`.

## Live check (2026-11-07, about 10:40 am)

- Fresh Explorer window at C:\: nav tree style 0x56019228, TVS_HASBUTTONS / TVS_HASLINES /
  TVS_LINESATROOT all clear. Screen capture `2026-11-07-navtree-offset-merge\proof2.png`
  shows the tree without arrows or lines and the folder listing loaded (38 items).
  `proof.png` (PrintWindow) came out blank; PrintWindow misses the composed content.
