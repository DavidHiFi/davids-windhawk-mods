# AB Download Manager — Catppuccin Mocha theme + catch-everything capture (2026-09-28)

Status: theme patched and live (screenshot-verified), API-key auth ON with the key
present in the Zen extension, browser capture proven for `.zip` and `.json`.
Acrylic window rule applied (2026-09-28 ~16:43); no visible effect on the
Skia-rendered window — details in the verification pass below.

## 1. Catppuccin Mocha theme (custom build, installed)

- Added `catppuccinMocha` to
  `shared/app/src/commonMain/kotlin/com/abdownloadmanager/shared/ui/theme/DefaultThemes.kt`
  (colors from the official `github.com/catppuccin/palette` `palette.json` v1.8.0:
  base/mantle/crust, mauve primary, lavender/pink accents, pastel status colors).
- Built v1.10.4 from the tag clone with Temurin 25
  (`:desktop:app:createReleaseDistributable`), then swapped the installed `app\`
  payload: `scripts\2026-09-28-abdm-catppuccin-mocha-patch.ps1 -Install`.
  Installed app now runs `app-desktop-a5d26a4a...jar` + `app-7e6fd758...jar`
  (both carry the theme).
- Backup of the stock payload: `backups\2026-09-28\abdm-catppuccin-mocha\app-orig\`.
  Rollback: script `-Rollback` (app closed) or `winget uninstall amir1376.ABDownloadManager`.
- Source clone + build output live in `%TEMP%\opencode\abdm\src-main` (streams clean up
  temp on their own schedule; re-clone the tag and re-build if gone).
- **In-app updates overwrite the patch.** After an ABDM update, re-run the build and
  the patch script.
- Verified: app renders Mocha colors (`reports\2026-09-28\abdm-mocha-theme.png`);
  `appSettings.json` accepted `"theme": "catppuccin_mocha"` at boot (invalid ids would
  reset to dark).

## 2. API key / auth

- `apiAuthEnabled=true` in `~/.abdm\config\appSettings.json` (key: the existing
  `apiAuthKey`). `POST /ping` without a key returns 401, with `X-Api-Key` returns pong;
  the CLI is unaffected.
- The Zen extension's API Key field already contained the same key (user-set); no
  further extension-side action needed. (If auth is ever disabled again, mirror the
  change in the extension or the HTTP fallback path 401s.)

## 3. Catch-everything browser capture

- Extension (Zen, `firefox-integration@abdownloadmanager.com`, active v1.5.0) settings:
  `registeredFileTypes` expanded from the 23 defaults to ~250 common extensions
  (everything incl. `json`, `txt`-adjacent code/data types, archives, media, mod
  formats). Exact list: `backups\2026-09-28\abdm-catppuccin-mocha\filetypes-catchall.txt`.
  `autoCaptureLinks` on, min-size 0, silent add + silent start on, send cookies on.
- How it was set without clicking: MSAA handshake
  (`AccessibleObjectFromWindow(hwnd, OBJID_CLIENT, IID_IAccessible)`) activates
  Firefox content accessibility, then UIA `ValuePattern.SetValue()` on the options-page
  textarea works and persists. Helper: `%TEMP%\opencode\abdm\ui.ps1`.
- **Extension options-page URL uses the EXTENSION INTERNAL UUID**, which must be read
  from `prefs.js` → `extensions.webextensions.uuids`
  (here: `d14f9400-5b23-4e60-bc95-b7e2dc9c14d9`). Wrong UUID = blank page.
- Verified captures (ABDM list shows Finished; browser download folder untouched):
  - `github.com/.../v1.10.4.zip` via `zen --new-tab` (12:46, id 2)
  - forced `.json` download via httpbin `Content-Disposition` (id 3)
- Hard limitation: downloads that exist only inside the browser (`blob:` / `data:`
  URLs, e.g. Bonjourr's own Export button) cannot be handed to any external app.
  Turbo Download Manager captures those because it downloads inside the browser.
- TDM left enabled: it no longer wins normal downloads (proven above); disabling it
  via a11y did not work (Firefox Add-ons UI resists UIA Invoke).

## 4. Steam "Mocha Steam" (separate task, sibling thread's result)

- Canonical theme `themes\MochaSteam` (author DavidHiFi, repo DavidHiFi/millennium-stuff
  v1.0.0). `config.json themes.activeTheme = "MochaSteam"`, options carried over,
  Steam restarted and verified: `reports\2026-09-28\steam-mocha-steam-theme.png`.
- An accidental duplicate (`themes\mocha-steam`, from a parallel copy) was removed;
  only `themes\Steam` (stock SpaceTheme) and `themes\MochaSteam` remain.

## 5. Acrylic/Mica for the ABDM window

- Rule staged as `scripts\2026-09-28-abdm-acrylic-rule.ps1`
  (`-Audit/-Apply/-Rollback`); same recipe as Discord/Zen (`acrylicblur`,
  `AA1E1E2E`). **Applied 2026-09-28 ~16:43** after the UAC prompt was answered
  on the second attempt; `RuledPrograms[25]` + `SettingsChangeTime` bumped
  (no engine restart). Effect on the Skia-rendered window: none visible
  (see verification pass). Left applied; harmless and reversible.

## Verification pass (rescue thread, 2026-09-28 16:25-16:50)

- Fresh capture test: Zen opened
  `httpbin.org/response-headers?...filename="abdm-verify-2026-09-28.zip"`
  (Content-Disposition attachment) at 16:29. ABDM download id 4:
  `Completed`, 150 B, folder `D:\Custom Downloads\AB Download Manager\Compressed`,
  file body matches the httpbin response. The browser's own folder stayed
  untouched (newest file there is still `bonjourr-22.3.0 ...json` at 14:56).
- Extension options re-read live via UIA (helper `%TEMP%\opencode\abdm\uia-final.ps1`;
  MSAA handshake still required): 334 file-type tokens incl. zip/json/exe/rar;
  auto-capture, silent add, silent start and popups all On; Native Messaging
  "Host Is Reachable"; port 15151. API-key field matches `appSettings.json`
  `apiAuthKey`; `apiAuthEnabled=true`; POST `/ping` without key returns 401.
- ABDM list holds only item 4, Finished — no failed items, no
  `~/.abdm/system/log/crash.log`. Evidence: `reports\2026-09-28\abdm-verify-finished.png`,
  `abdm-ext-options-recheck.png`, `abdm-ext-options-top.png`.
- Acrylic check: ABDM was restarted 16:46 (no active downloads) so its window
  was created after the mod reload. Pixel test (window topmost over Zen vs.
  Zen alone; luminance of window region where Zen is bright vs dark below:
  4552 vs 260079 sampled pixels, means 33.16 vs 34.10) -> no bleed-through;
  the window paints fully opaque, so the rule has no visible effect on this
  app. `reports\2026-09-28\abdm-post-acrylic-window.png` shows the normal
  render.
- Trap for reuse: `Get-ItemProperty -Name 'RuledPrograms[25].target'` treats
  `[25]` as a wildcard and reports absent. Read rule values with
  `[Microsoft.Win32.Registry]::LocalMachine.OpenSubKey(...).GetValue(name)`
  or `reg query`.

## Gotchas

- T3 Code V2 agent sessions redirect `$env:APPDATA` to the app sandbox; use explicit
  `C:\Users\localuser\AppData\Roaming` paths when reading real user profiles.
- Never restart the Windhawk engine on this machine (kills explorer/T3); apply mod
  settings by registry write + `SettingsChangeTime` bump.
- ABDM stores data in `~/.abdm`; config at `~/.abdm\config\appSettings.json`,
  downloads DB under `~/.abdm\config\download_db`.

## Rollback summary

| Thing | Undo |
| --- | --- |
| Theme patch | `scripts\2026-09-28-abdm-catppuccin-mocha-patch.ps1 -Rollback` (app closed) |
| API auth | `apiAuthEnabled=false` in appSettings.json (app closed) |
| File types | options page "reset to default" link, or paste the 23-type default list |
| Acrylic rule | `scripts\2026-09-28-abdm-acrylic-rule.ps1 -Rollback` (elevated) |
