# Styler caption buttons: investigation checkpoint (2026-10-17, generation 3)

Mod: `local@windhawk-styler` v2.0.57, target `windhawk-ui.exe`. Source: `work\styler-release\mods\local\windhawk-styler\windhawk-styler.wh.cpp`. Handoff: `t3-handoff\mcp-c35fac5c-a990-4b5d-b508-a7a7eb349900.md`.

## Status

Neither symptom is fixed. No code was edited and nothing was deployed. Both symptoms still have open root causes, and the earlier textColor conclusion was wrong (see below).

## Measured

- Hit-testing in the normal state: `WM_NCHITTEST` at the dot centers returns HTCLOSE (20), HTMAXBUTTON (9) and HTMINBUTTON (8). Those codes come from `DwmDefWindowProc` (line 940), which runs before the mod's own caption code.
- Hit-testing in the maximized state (rect `(-8,42)-(2568,1448)`): the same codes at the dot centers, which sit about 22 px below the window top.
- `SC_RESTORE` sent with `SendMessageTimeout`, and `ShowWindowAsync(SW_RESTORE)`, both leave a maximized window maximized. `ShowWindowAsync(SW_SHOWNORMAL)` restores it. `ShowWindowAsync(SW_MAXIMIZE)` works.
- Window style while maximized: `WS_MAXIMIZE`, `WS_THICKFRAME`, `WS_MAXIMIZEBOX`, `WS_MINIMIZEBOX` and `WS_SYSMENU` are all set. The styles are not the cause.
- Two real mouse clicks on the maximize dot while maximized changed nothing, and the window did not become foreground. The cursor was later found at `(-478,1136)`, so someone else was using the mouse. These clicks are not clean evidence.
- The mod never calls `ShowWindow` or `SetWindowPos` on the main window (`windhawk-styler.wh.cpp` lines 1041 and 1061 touch the one-time setup and the WebView child only).
- Settings churn during this session: `titleBarAcrylic` changed 1, then 0, then 1 between about 23:28 and 23:34. `SettingsChangeTime` moved at least three times. The Windhawk UI window was recreated (new HWND) about every few minutes, and a recreated window came up maximized.

## Correction to the textColor experiment

The earlier reading (clearing `textColor` made the dots bright, so `textColor` causes the dim) is not supported.

- Baseline before the experiment: dim. Window handle `0x1BA184E`.
- After clearing `textColor`: bright. The window had been recreated (handle `0xFE023A`).
- After restoring `textColor` to `#cdd6f4`: still bright, same handle. So `textColor` is not the cause.
- Focus A/B (no registry writes): with focus moved to the taskbar the strip is dim. Gen-2 `caption-active-zoom.png` (titleBarAcrylic on) is also dim.

So the dim state is present in both active and inactive captures, and the bright captures happened right after a window recreation. The likely trigger is the window's creation or first-activation state, not the color value. This is unproven.

## Open questions

1. Why are the bright and dim states different across window recreation? Candidates: the initial WM_NCACTIVATE and the mod's forced active look (line 991, which applies only when `titleBarAcrylic` is on), or the DWM text color hook (lines 1115-1116).
2. Why does `SC_RESTORE` get ignored while maximized? Candidates: a Tao/WRY subclass on the main window that swallows WM_SYSCOMMAND, or a WM_NCCALCSIZE/WM_GETMINMAXINFO interaction. The next step is to list the window procedure chain (`GetWindowLongPtr GWL_WNDPROC` plus subclass lookup) in the maximized state.

## Before the next live test

- Ask who is changing the styler settings (the user, or another thread). Coop has no note from a writer. Do not write HKLM without a `coop lock windhawk-engine` and a fresh read of the live values.
- Confirm the window is stable, then run the focus A/B and the maximized probe once each, saving the zoom images under `.tmp\styler-probe\`. Do not truncate the probe output with `Select-Object -First`, which stops the script before it saves the image.

## Files

- Probes and experiment scripts: `.tmp\styler-probe\` (`probe.ps1`, `set-setting.ps1`, `exp-textcolor-clear.ps1`, `exp-textcolor-restore.ps1`, `exp-state.json`).
- Registry backup taken before any change: `backup-2026-10-17-styler\hklm-mod-styler.reg`. It predates the `titleBarAcrylic` and `SettingsChangeTime` changes above.
- Live `textColor` was verified as `#cdd6f4` after the restore.
