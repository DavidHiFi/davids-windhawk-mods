# AB Download Manager: acrylic blur and rounded corners (2026-09-30)

## Result

The Catppuccin Mocha theme in AB Download Manager now shows a real acrylic blur
behind the window and has Windows 11 rounded corners. Both apply on every launch
and whenever the window reopens from the tray. The user checked it and accepted
it on 2026-09-30.

## What was wrong

- The first acrylic build (Codex thread 5f812690) made the window transparent and
  undecorated, then relied on the Windhawk Translucent Windows rule for the blur.
  An undecorated Compose window is `WS_POPUP` with no `WS_CAPTION`, so the mod's
  `IsWindowEligible()` skips it. That left a see-through window with no blur, which
  the user described as "lowered opacity".
- `WS_POPUP` windows don't get DWM's default rounding, so the corners stayed square.
- The stock build (decorated `SunAwtFrame`) is not rounded by default either;
  `DwmSetWindowAttribute(33, DWMWCP_ROUND)` rounds it once the app opts in.

## Fix

The app sets the effect itself. In `CustomWindow.kt`, when the theme is
`catppuccin_mocha` on Windows, a window listener runs `applyWindowsAcrylic(hwnd)`
on open:

- `SetWindowCompositionAttribute(WCA_ACCENT_POLICY)` with
  `ACCENT_ENABLE_ACRYLICBLURBEHIND` (4) and tint `0x302E1E1E` (Mocha base `#1E1E2E`
  at alpha 0x30, ABGR).
- `DwmSetWindowAttribute(DWMWA_WINDOW_CORNER_PREFERENCE, DWMWCP_ROUND)`.

The calls go through JNA, which the app already ships (`jna-5.19.1`). The only
build change is `implementation(libs.jna.core)` in `desktop/app-utils`.

## Where things are

| Item | Path |
| --- | --- |
| Full source patch (theme + acrylic + corners) | `scripts\2026-09-30-abdm-acrylic.patch` |
| Source tree (ABDM 1.10.4, commit afc5763) | `%TEMP%\opencode\abdm\src-main` |
| Build log | `reports\2026-09-30\abdm\build-v3.log` |
| Installed jar | `%LOCALAPPDATA%\ABDownloadManager\app\app-utils-b120e818a8145f78e4eb8b3eb62c762b.jar` |
| Evidence | `reports\2026-09-30\abdm\acrylic-final.png`, `acrylic-final-corner.png` |
| Backup of the 28/09 app payload | `backups\2026-09-30\abdm\app.before\` |
| Windhawk mod key backup | `backups\2026-09-30\windhawk-translucent-windows-2026-09-30.reg` |

Only `app-utils-*.jar` and the three launcher `.cfg` files differ from the 28/09
install. The runtime and user data were not touched.

## Windhawk rule

`translucent-windows` `RuledPrograms[25]` (`ABDownloadManager.exe`, `acrylicblur`)
is still on. It doesn't affect the acrylic build, because the popup window isn't
eligible. It does apply if the stock decorated build comes back. The earlier
diagnostic run switched it off and back on; its state now matches the 28/09 setup.

## Rebuild after an app update

An ABDM update overwrites `app\`. To restore:

1. `git apply scripts\2026-09-30-abdm-acrylic.patch` on a clean checkout of the
   matching tag.
2. `gradlew.bat :desktop:app:createReleaseDistributable` (JDK 25).
3. Close ABDM (`ABDownloadManagerCli.exe gui exit`), then copy the new
   `app-utils-*.jar` and the three `.cfg` files from
   `desktop\app\build\compose\binaries\main-release\app\ABDownloadManager\app\`
   into `%LOCALAPPDATA%\ABDownloadManager\app\`. Delete the old `app-utils-*.jar`.

## Rollback

Close ABDM, then copy `backups\2026-09-30\abdm\app.before\*` over
`%LOCALAPPDATA%\ABDownloadManager\app\`, and delete
`app-utils-b120e818a8145f78e4eb8b3eb62c762b.jar`. That restores the opaque 28/09
Mocha build. Switching ABDM to any other theme also turns the effect off.

## Traps

- A live `SetWindowCompositionAttribute` from PowerShell works but lasts only
  until the window is recreated. Closing to the tray destroys the window.
- Screen captures from a non-DPI-aware PowerShell process can come back offset or
  blank. Use `Save-Screen` from `%TEMP%\opencode\abdm\ui.ps1`, which captures the
  full virtual screen.
