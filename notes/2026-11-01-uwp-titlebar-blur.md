# Remove UWP Title Bars Plus: title bar blur option (2026-11-01), not working, rolled back

Owner asked for a settings option that swaps the flat UWP title bar colour for a blur, plus a preview.

## Result (measured 2026-11-01, about 10:15 pm)
No build produced a real blur on ApplicationFrameWindow. The live mod is back on 2.1.0 (registry: Version 2.1.0, lib `local@remove-uwp-title-bars-plus_2.1.0_193157.dll`, blur settings removed). Evidence image: `work\2026-11-01-uwp-titlebar-blur\store-blur-findings.png`.

## Where the flat colour comes from
`win11-custom-title-bar-colours` (Include=*) sets DWMWA_CAPTION_COLOR to #1E1E2E (the same value as AccentColorInactive) on every window, ApplicationFrameWindow included. It sets the colour before this mod makes the frame native, and the 2.1.0 hook only blocks later calls, so the caption stays a solid fill. To make UWP captions plain, add `ApplicationFrameHost.exe` to that mod's Exclude list. Nothing is changed there yet.

## What was tried (Store over a 40px black/white stripe board, then solid white and solid black)
- 2.2.0: acrylic accent (WCA_ACCENT_POLICY 4) plus the -1 frame extension and blur-behind. The caption was clear glass and the stripes stayed sharp. The earlier claim that this blurred was wrong: Settings sits over a smooth wallpaper, which hid the problem. translucent-windows skips this window class for its accent, probably for the same reason.
- 2.2.1: system acrylic (DWMSBT_TRANSIENTWINDOW) plus the WM_NCACTIVATE(TRUE,-1) keep-active trick. Solid #1E1E2E, identical over white and black.
- 2.2.2: same as 2.2.1, with the caption colour set to DWMWA_COLOR_NONE. Solid 17 grey, identical over white and black. The acrylic never draws.
- 2.2.3: see-through frame (-1 extension and blur-behind) plus system acrylic. Pure white over white, pure black over black. No material at all.

Conclusion (measured): DWM draws neither the accent blur nor the system backdrop on UWP frame windows. The only route left is a composition HostBackdropBrush visual drawn inside ApplicationFrameHost over the caption (the same source the Settings page's AcrylicBrush uses). That is a bigger change, so it was not attempted.

## Files
- Last experiment source (2.2.3): `work\2026-11-01-uwp-titlebar-blur\remove-uwp-title-bars-plus.wh.cpp`
- Tests: `work\...\blur-board-test.ps1 [-Tag x] [-Focus] [-Solid White|Black]`, `probe-accent.ps1` (cross-process accent reads fail with error 87)
- Script: `scripts\2026-11-01-uwp-titlebar-blur.ps1 -Audit|-Install|-Rollback`
- Backup of 2.1.0: `backups\2026-11-01\remove-uwp-title-bars-plus\`
