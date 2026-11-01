# Remove UWP Title Bars Plus: title bar blur option (2026-11-01 to 11-02), working in 2.3.0

The owner asked for a settings option that swaps the flat colour of UWP title bars for a real blur, keeping the native title bar. The owner approved the result on 2026-11-02 with a Store screenshot.

## Result (measured 2026-11-02, about 5:10 am)
- Live: version 2.3.0, lib `local@remove-uwp-title-bars-plus_2.3.0_802538.dll`, loaded in ApplicationFrameHost. Settings: blur=1, tint=60. The live ModsSource file has the same hash as `work\2026-11-01-uwp-titlebar-blur\remove-uwp-title-bars-plus.wh.cpp`.
- Stripe test: the Store caption sits over 40 px black and white stripes. The stripes come through as a smooth 65 to 73 grey ramp, unfocused. A solid white board reads 120 and a solid black board reads 18, focused. Those are the expected values for a 60% #1E1E2E tint over a real blur. Captures: `work\...\board-b-*.png`.
- When the Store closed, its backdrop window was destroyed (none left afterwards).
- Not checked yet: other UWP apps, and window move, minimize and restore. The owner stopped the move test. The code has no per-app path: every frame the mod makes native gets the backdrop.

## How it works
DWM draws neither the accent blur nor a system backdrop on ApplicationFrameWindow (2.2.0 to 2.2.4, measured). The frame host already owns both DirectComposition targets on the frame: CreateDesktopWindowTarget fails with 0x88980800 (WINDOW_ALREADY_COMPOSED) for topmost and for non-topmost. So 2.3.0 does the following:
- Makes the native caption see-through: -1 frame extension, blur-behind, caption colour set to NONE, and the keep-active WM_NCACTIVATE trick.
- Creates one click-through tool window per native frame on a worker thread (class `RemoveUwpTitleBarsPlus_Backdrop`). Its composition HostBackdropBrush sits under a #1E1E2E tint, and its corners are rounded.
- Keeps that window on the frame's bounds, directly below it in z-order. The frame's WM_WINDOWPOSCHANGED and WM_SHOWWINDOW trigger the sync, as do cloak and uncloak events.
- Hides it while the frame is minimized or cloaked. Destroys it when the frame is destroyed, when blur is turned off, or when the mod unloads.

## Known gap
Frames the host created before the mod (re)loaded keep the stock title bar until the app is reopened. This was already true before the blur work.

## Files
- Source: `work\2026-11-01-uwp-titlebar-blur\remove-uwp-title-bars-plus.wh.cpp`
- Install: `scripts\2026-11-01-uwp-titlebar-blur.ps1 -Audit|-Install|-Rollback` (run elevated; -Rollback reinstalls 2.1.0)
- Tests: `work\...\blur-board-test.ps1`, `follow-test.ps1`. Log capture: `dbwin-listen.ps1` (lossy when other mods log heavily) plus `diag-install.ps1 -Logging 1`; turn logging off again with `logging-off.ps1`.
- Backup of 2.1.0: `backups\2026-11-01\remove-uwp-title-bars-plus\`
