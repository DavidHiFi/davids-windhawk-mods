# Steam notification, overlay and store fixes

Continuation of failed T3 thread `mcp:2242e54d-d712-4458-8bd5-1f34f6b80b13` in `mcp:518fff02-d5cc-4bca-967b-0a932c2fa9f9`.

## Cause and applied changes

Windhawk's Titlebar For Everyone 0.4 intercepts reads of Steam's index.html. It serves a temporary replacement that injects `window.open` and forces `browserType=3` for every popup. Its source at `C:/ProgramData/Windhawk/ModsSource/titlebar-for-everyone.wh.cpp` contains the exact script observed in the running SharedJSContext. The disk copy of Steam's index.html was clean, which explains why earlier file searches missed it.

Steam logs show notifications originally used type 4 and overlays type 0. With the injection, both used type 3. Desktop notifications requested 283x70 but grew to 299x109. DWMX painted acrylic into that extra window area. Game overlays became full desktop windows instead of offscreen overlay browsers.

Applied `ExcludeCustom=steamwebhelper.exe` to the Titlebar For Everyone mod only. Original value was empty. The mod remains enabled and its other application lists are unchanged. Export and original-value receipt are in `backups/2026-09-30/steam-final-fixes`. The Windhawk engine watches these changes, so no engine restart was needed. An independent registry read confirmed the exclusion. A fresh fetch through Steam's own loopback interface returned the original 457-byte HTML with no injected wrapper.

The running session retained its already executed JavaScript closure. Used the existing background CDP connection and `Debugger.setScriptSource` to remove the forced query parameter from that closure. The result was `status: Ok`. No foreground console, keyboard automation, focus change, Steam restart or game-file change occurred. The script tag's text still contains the old string, but the executed function changed, as confirmed by subsequent native popup creation.

Store search results now use a mantle fill at 0.78, `blur(16px) saturate(1.15)` and a 1px edge. Both current and legacy selectors are covered. Store options tooltips use the same material. Installed webkit.css matches the repository.

## Verification

- A real silent local notification while a game was active used native overlay type 0. Its viewport and body both measured 283x70. The card retained the existing 0.84 mantle and 6px blur styling. The notification expired automatically.
- A hidden desktop notification test window used native type 4 and measured 283x70. It closed immediately after checking its dimensions and CSS.
- In that isolated browser fixture, both store search selectors and the store options tooltip computed 16px blur, 0.78 mantle and a 1px edge.
- Main controls remain at x16, y1261, 400x90, display flex. TopBar has no backdrop filter. Sidebar alpha remains 0.9.
- Installed backend, notification CSS, DWMX CSS and webkit.css match the repository after line-ending normalization. `git diff --check` passes.

Evidence is in `reports/2026-09-30/steam-final-fixes`. The popup report is a browser fixture check, not a screenshot of the actual store. A fresh game launch and a real incoming desktop notification have not been tested after this change. The owner's game was running, so it was left running. No restart is pending to activate the Windhawk exclusion; it is persistent, and the current JavaScript closure was repaired too. An old overlay created before the fix may persist until the current game session ends.

## Repository handoff

The release thread `mcp:0bbbfa2f-60a3-415e-9d76-d3ac43ba6618` owns commit and publication. Glass-ready handoff names these five files:

- plugins/dwmx/backend/main.lua
- plugins/dwmx-src/backend/main.lua
- themes/mocha-steam/src/css/plugins/dwmx.css
- themes/mocha-steam/src/css/notifications.custom.css
- themes/mocha-steam/src/css/webkit.css

The first four are inherited, deployed acrylic-continuity changes. This continuation added the store stylesheet correction and the separate machine-specific Windhawk exclusion.

Published [v1.1.5](https://github.com/DavidHiFi/millennium-stuff/releases/tag/v1.1.5) at commit `c68cc20de0369ceb3c37fd904c1d62ca94374267`. The release thread verified that main and the tag match, the repository is clean, all 191 archive files match Git, and the GitHub archive hash is `88046af53c721e7b526576dd065adce008378253382200e3d88518a5098b7e99`. Its independent installed-hash and backend-mirror checks passed. The uploaded archive is 5,753,408 bytes. A separate release API read in this continuation confirmed the public URL, publication time and asset size.

## Rollback

Run `scripts/Repair-Steam-TitlebarConflict.ps1 -Rollback` through the same silent elevation wrapper to restore only the original exclusion. The script defaults to a read-only audit. Rollback reinstates the popup-type conflict on subsequent Steam initialization. Restore webkit-before.css from the backup to the installed theme to undo this continuation's store styling. Inherited acrylic changes have their rollback recorded in `notes/2026-09-30-steam-acrylic-continuity.md`.
