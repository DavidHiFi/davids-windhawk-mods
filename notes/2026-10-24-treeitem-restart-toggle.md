# Explorer TreeItem Tweaker Plus 1.1.5: restart switch (2026-10-24)

Owner ask: make the "restart Explorer without the popup" behaviour a switch.

## Change
- New Global setting **Restart Explorer without asking** (default on). On: Explorer restarts by
  itself once when the mod loads into a running Explorer (the 1.1.4 behaviour). Off: the original
  mod's "Restart Explorer / Cancel" popup, now shown on its own thread so mod start is not held up;
  uninit cancels an open popup and waits for that thread.
- Added `@donateUrl https://ko-fi.com/DavidHiFi`; readme gained a plain-words "Restarting Explorer" section.
- Source: `work\2026-10-24-treeitem-restart-toggle\explorer-treeitem-tweaker-plus.wh.cpp`, copied to
  `Windhawk\explorer-treeitem-tweaker-plus\`. Install/rollback: `scripts\2026-10-24-treeitem-restart-toggle-install.ps1`.

## Verified (measured, 2026-10-24)
- Installed 6:00 AM: registry Version 1.1.5, `LibraryFileName local@explorer-treeitem-tweaker-plus_1.1.5_670080.dll`,
  setting = 1. Explorer restarted at 6:00:58 AM and `tasklist /m` shows the 1.1.5 DLL in explorer 22068.
- Off path (6:04 AM, `test-prompt-off.ps1`): setting 0 + disable/enable showed the popup
  (`work\...\2026-10-24-prompt-when-off.png`); Cancel left Explorer PIDs unchanged; setting reset to 1.

## Gotcha
`Invoke-Elevated.ps1 -File ... -ArgumentList "-Install"` ran with an empty log and exit 1 from this
shell. `Start-Process cmd.exe -ArgumentList '/c powershell -File "<script>" -Install > log 2>&1' -Verb RunAs` worked.

Rollback: run the install script with `-Rollback` (reinstalls the 1.1.4 source kept in the work folder).
