# Explorer column header gap and hover offset (GPU Accelerated Explorer View Plus 1.3.1)

Date: 2026-11-07. Work folder: `2026-11-07-header-gap\`.

## Symptom
The owner sees a gap of about 32 px between the toolbar line and the column headers, and hover lands one row below the cursor.

## Cause (inferred, not reproduced)
The page slide animation (PageAnimation distance 32) moves the overlay visual down by 32 px and animates it back to 0. Hit-testing always uses the real layout. If the curve stalls (hidden target or lost commit), the drawing stays 32 px low while input keeps hitting the real rows. That matches both symptoms.

## Changes in 1.3.1
1. In `PageAnimBeforePresent`, when the animation time ends, the code now sets the translate to 0 and opacity to 1 and commits. A stalled curve can no longer leave the page pushed down.
2. `MaybeRestartExplorer` (merged from NavTree offset) now runs only in the taskbar process (the owner of Shell_TrayWnd).
   - Before: it ran in every explorer.exe, including folder windows in their own processes. Each process has its own stamp, so any hot-swap into an older folder process ran `taskkill /f /im explorer.exe`.

## Incident during deploy (12:26 pm)
The first 1.3.1 install hit bug 2. NavTree's taskkill closed every Explorer process, including the owner's open folder windows. The shell came back on its own. The install script saw the churn and rolled back to 1.3.0. Restart-ExplorerGuarded -Check showed 0 Winlogon stops and 0 crashes afterwards.

## Deploy (12:30 pm)
- DLL `local@gpu-accelerated-explorer-view-plus_1.3.1_2.dll`, sha256 E1BEA2AB291C33DD9CAB59C58E0D9CAE127C1331CC3C95DDED9D510CD2E9657A.
- Result: shell pid unchanged and churn=False.
- After the last old folder process exited, every explorer.exe held 1.3.1 (measured with tasklist /m).

## Evidence
- `repro\` holds 1.3.1 captures and `repro-130\` holds 1.3.0 captures.
  - Each set covers 10 Shell COM navigations, some interrupted on purpose.
  - The headers sit flush under the toolbar in every 1.3.1 frame.
- The 1.3.0 run did not show the gap either, so the original trigger is still unreproduced. Status: fix deployed, gap not seen since. Proof that the stall is the cause: unverified.
- If the gap returns on 1.3.1, the next suspects are modeComposition and the graphics-lane copy of headerPx.

## Rollback
Elevated:
1. `reg import 2026-11-07-header-gap\backup\gpu-mod-1.3.0.reg`
2. Copy `backup\gpu-1.3.0.wh.cpp` to `C:\ProgramData\Windhawk\ModsSource\local@gpu-accelerated-explorer-view-plus.wh.cpp`.
3. Bump SettingsChangeTime.

Before doing this, set LocalStorage `NavTreeHandledExplorer` to the taskbar process stamp. 1.3.0 still has the restart-in-every-process bug, so close extra folder windows first.

## 1.3.2: view switch jump while dragging (12:40 pm)
Reported from the status bar dock thread. StatusButtonQuery holds screen rects, so every window move made the cached accessibility geometry look stale. The switch then dropped to the fallback spot until a new scan snapped it back, which showed up as a jump and a doubled image.
- SameStatusButtonQuery now ignores translation. It compares frame, dpi, rtl, client size and band offset inside the client.
- RefreshViewToggleForFrame shifts the measured rect by the client move before mapping it to the frame.
- DrawViewToggle buffer order is unchanged (Styler Plus 1.9.1 paints inside it).
- Deploy: DLL `_1.3.2_1.dll`, sha256 701A5BF0205063D8FB5D076F1471603407EF9DE5B29E0290E4795EF9770F99C6. Same shell pid and churn=False. Every explorer.exe holds 1.3.2 (tasklist /m).
- Rollback to 1.3.1: elevated `reg import 2026-11-07-header-gap\backup\gpu-mod-1.3.1.reg`, copy `backup\gpu-1.3.1.wh.cpp` back, then bump SettingsChangeTime.
- Drag check (12:55 pm, measured): 40 SetWindowPos moves with 120 samples at 16, 60 and 150 ms. The switch stayed at frame offset 1183,1325 (24x24) in every sample, and drag-proof.png shows a single switch after each move.
