# Independent taskbar weather

Replacement thread `mcp:38c1a225-0406-424e-b0df-13adbe0b405d` recovered source `ac4941a8-882c-46a8-aaa5-7ea013eb24ba` and predecessor `24e9aa75-4660-4220-8e0f-15ba91192612` through T3 tools. The final predecessor instruction superseded restoration of Windows Widgets. It requested disabling Widgets and replacing taskbar weather with an independent Windhawk mod.

The new source is `work/taskbar-weather/taskbar-weather.wh.cpp`. The mod runs only in Explorer. It uses WinHTTP to fetch Open-Meteo current weather over HTTPS, with no API key, browser, MSN, Widgets, or Windows location service. It shows a colored weather icon, rounded Celsius temperature and weather condition. Colors and single-row placement match the existing taskbar theme. Its native tooltip gives the data timestamp and connection status. Clicking it refreshes the reading. Requests are bounded in size and have timeouts. Failed requests retain the last reading and retry after one minute; the tooltip marks readings older than thirty minutes as stale.

The previous weather cache supplied local coordinates. That cache explicitly marked the location as automatically detected. No manually selected town was recovered. The user explicitly chose "Keep the existing weather location" on 2026-09-30. The mod preserves that selection as fixed coordinates, so future VPN or IP changes will not silently move it. Location values remain in private local files and mod settings; they are excluded from this report.

## Changes

Applied at about 06:37 Perth time on 2026-09-30, after a rollback snapshot:

| Setting | Before | After | Reason |
|---|---|---|---|
| User Explorer TaskbarDa | 0 | 0 | Widgets already hidden; preserved |
| User Dsh AllowNewsAndInterests | 1 | 0 | Disable Widgets |
| Machine Dsh AllowNewsAndInterests | 1 | 0 | Disable Widgets |
| taskbar-system-info leftOffset | 175 | 175 fallback; measured weather edge + 6 while weather is present | Follow changing weather width |
| local@taskbar-weather | absent | enabled, Explorer only | Independent weather |

Stopped only Widgets and WidgetService after disabling their policies. No Edge installation, Explorer restart, global Windhawk restart, reboot, display change, or protected audio application operation occurred. Explorer remained PID 26784 with start time 05:57:03. T3 tools later returned Authentication required, so peer messaging and settlement could not proceed through that transport. Source history remains intact.

Initial installation exposed a registry helper error. Creating an already existing key with `New-Item -Force` cleared values in the newly created weather mod key. It reached no existing-key write before failing on the protected Explorer key. The helper now creates only absent keys and skips values already set. Installation resumed from the original snapshot without replacing it. Registry values and installed hashes were independently checked afterwards.

## Verification and rollback

The bundled Windhawk compiler built the production x64 DLL successfully. The independent endpoint returned a current reading; the live taskbar showed the same rounded temperature and condition. Screenshots are cropped to the taskbar in `reports/2026-09-30/taskbar-weather/`. Live audits read the mod's HWND status without clicks, foreground changes, keyboard shortcuts, or DevTools. With a temporary one-minute interval, the successful update counter increased from 2 at 06:40:18 to 4 at 06:41:38 without input. The normal interval is ten minutes. Disabling only this mod removed its HWND, then re-enabling restored it. Policy restoration in the full rollback script was reviewed against the saved values; full rollback was not executed because it would re-enable Widgets.

Audit with `scripts/taskbar-weather/Audit-Live.ps1`. Build with `scripts/taskbar-weather/Build.ps1`. Rollback with the saved `scripts/taskbar-weather/rollback-elevated.cmd` through silent elevation. `Install.ps1 -Rollback` disables the weather mod and restores the exact recorded policy and system-monitor values, including removal of values previously absent. It retains the disabled source and DLL. The snapshot is `backups/2026-09-30/taskbar-weather/before.json`. No restart is pending.

The taskbar rendering reproduces the existing layout and colors through a native transparent child window. It is not a byte-for-byte copy of Microsoft's weather artwork or its full Widgets board. The mod has an independent tooltip rather than the Widgets board. Forecast values are modeled weather for the configured coordinates, not a local physical sensor.

## Weather and performance panel alignment

The user rejected the fixed gap on 2026-09-30. The weather mod now measures its displayed text, sizes its window to that content, and publishes its right edge in logical taskbar pixels through the `WindhawkTaskbarWeatherRightDip` window property. A local revision of Taskbar System Info reads that property during every metrics update and places its panel six logical pixels after the weather window. Weather changes, font changes, and DPI changes therefore update placement without registry writes. Disabling weather removes the property, and the performance panel falls back to its original offset of 175.

Installed monitor revision `taskbar-system-info_1.5.0.weather1_1.dll` preserves the original settings, metric collection, font, colors and upstream GPL credits. Source is `work/taskbar-weather/taskbar-system-info.wh.cpp`. Only its layout changed. The stock source and complete registry key are backed up as `monitor-source-before.wh.cpp` and `monitor-before.reg`. The full rollback script restores these as well as the earlier policy and offset values. The backup key captured the temporary offset of 256, so rollback subsequently applies the original 175 from `before.json`.

Live evidence at 06:45:48 showed weather edge 137 and the CPU label at about x=143 in `aligned.png`, matching the six-pixel panel gap. The previous CPU label was at x=256. Weather and performance metrics remain visible and unobstructed. The weather data timestamp advanced to 06:45. Explorer remains PID 26784, unchanged since 05:57:03. `aligned-live.json` names both installed revisions and the weather hashes. `monitor-build.log` records the monitor build hash. No restart is pending.

## Evening completion, version 1.2.0

The user supplied the intended town after reporting a phone comparison. The previous location was an auto-detected city in another area. The installed settings now use the requested town center, verified against the geocoding result's state and country. Town names and coordinates are omitted from this report. The hover card shows the chosen place locally. The new feed returned about 10 degrees at the time of installation. Open-Meteo reports modeled current conditions, which can differ from a phone provider's observation or update time; no value was forced to match the phone.

The interrupted provider had prepared version 1.1.0 with a rounded custom card, but the installed package was still version 1.0.0. The completed 1.2.0 adds the remaining lifecycle fixes. Previously the UI worker returned immediately when the taskbar was absent during startup, and destroying the taskbar child ended its message loop. A separate hidden controller now owns the loop and normal layout timer. It creates the weather child once the taskbar is ready, recreates that child if it is destroyed, and requests fresh data on resume and clock changes. This is part of the mod's taskbar lifecycle; no scheduled task, launch wrapper, external watchdog, Explorer restart or global Windhawk restart was installed.

The last good reading persists in Windhawk mod storage. The cache is accepted only for the same coordinates and expires after a day; older readings are marked stale in the card. A failed fetch preserves the reading and retries after a minute. Fetches retain HTTPS validation, bounded response size and timeouts, with an additional deadline while reading the response. Final package is `local@taskbar-weather_1.2.0_2.dll`.

The card has an eight-pixel radius, Mocha background and border, large temperature text and brighter 13-16-pixel secondary text. It includes feels-like temperature, daily high and low, humidity, wind and local data time. Its shorter refresh hint fits without truncation. It never activates a window or moves the pointer. The screenshot containing the chosen town stays in ignored private work files rather than public reports.

The stock performance mod had replaced the earlier modified DLL, removing weather-aware placement. The integration is now a separate local mod, `local@taskbar-system-info-weather`, with the stock settings copied unchanged and the stock mod disabled. It follows the measured weather edge plus six logical pixels. Its distinct local ID prevents catalog updates from replacing that integration. Upstream source credits and GPL license remain intact.

Verification on the final package closed only the weather child and observed its removal and automatic recreation within two seconds. A resume notification delivered only to the hidden controller triggered a successful fresh request, increasing its counter from one to two. A card preview preserved the foreground window. Explorer remained PID 20728, started before this task at 18:18:27. `lifecycle-test.json` records these checks. The actual computer was not rebooted or suspended for testing, so a new full login and a real sleep cycle remain unobserved. The source no longer exits on a missing startup taskbar. Automatic timer verification and final settings are recorded in `new-timer-before.json`, `new-timer-after.json` and `final-upgrade-live.json`.

Upgrade rollback is `scripts/taskbar-weather/upgrade-rollback-elevated.cmd`. It restores the previous weather package and location, disables the local performance copy and restores the stock monitor. The immutable snapshot is `backups/2026-09-30/taskbar-weather-1.2/`. Full rollback of all work remains `scripts/taskbar-weather/rollback-elevated.cmd`; it now also disables the new local performance copy before restoring the original settings. No restart is pending. Rollback scripts were syntax-checked and their saved values reviewed; full rollback was not executed because it would undo the requested result.

The final automatic timer test increased the successful-request counter from one at 19:55:51 to three at 19:58:12 without input. The interval was then restored to ten minutes. During that settings reload a network request failed: at 19:58:37 the persisted reading was still visible with counter zero and a request-failed status. The scheduled retry succeeded by 20:00:02, cleared the failure and increased the counter to one. This provides live evidence for cache restoration and recovery after a failed request. `cache-retry-evidence.json` records both observations. Final hashes and settings are in `upgrade-installed.json` and `final-upgrade-live.json`. The backups singleton was released immediately after the peer's request; no further backups were written.
