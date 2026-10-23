# Windhawk Styler published to main (2026-10-13)

## Result

- `origin/main` moved from `ccd3fd6` to `382170e` with a plain fast-forward push from `styler-tauri-release`. No force push.
- Merge commit `5452438` brings in `origin/main` first. That included start-everything-plus changes, translucent-flyouts 0.6.16 (PR #10), and a second copy of the Styler 2.0.35 commit with identical content. Two Styler files conflicted only because of that duplicate. They were resolved to our side, which already contains the same 2.0.35 content plus later releases.
- `382170e` carries 2.0.47: readme, verification record, mods README version row, and preview.

## Files published

- `mods/local/windhawk-styler/windhawk-styler.wh.cpp` (version 2.0.47, readme block)
- `mods/local/windhawk-styler/README.md` (same readme text)
- `mods/local/windhawk-styler/VERIFICATION.md` (2.0.47 section, above the 2.0.34 record)
- `mods/README.md` (Styler row: 2.0.34 changed to 2.0.47)
- `media/previews/windhawk-styler.png` (Styler settings page, 1250 x 1350)

The diff against `origin/main` before the push contained only these five files.

## Live install

- `scripts\2026-10-13-styler-polish-2047.ps1 -Action Install`, run elevated through `Invoke-Elevated.ps1` under the `backups` and `windhawk-engine` locks. Exit 0.
- Library `local@windhawk-styler_2.0.47_133000.dll`, SHA256 `CD125087...`. Installed source SHA256 `18CE758B...`, which matches the repo file.
- Loaded in the Windhawk window after the install.
- Backup and receipt: `backups\2026-10-13\styler-polish-2047\` (registry export, `installed-2.0.46.wh.cpp`, `receipt.json`).
- Rollback: `scripts\2026-10-13-styler-polish-2047.ps1 -Action Rollback` (back to 2.0.46), run elevated.

## Checks

- `Build.ps1` for 64-bit and 32-bit. The 64-bit DLL contains the tab overflow rule.
- `scripts\styler-maintenance.ps1 -Audit`: version 2.0.47, source hash equals installed source hash, library hash equals the build, include `windhawk-ui.exe`, not disabled, legacy UI not selected.
- Published state: `origin/main` is `382170e`, the working tree is clean, and the published readme, version, preview and mods README row match.

## Preview

- Captured through the Windhawk UI's debugging port with `reports\2026-10-13-styler-polish\capture-page.ps1` (`Page.captureScreenshot`), from the Styler settings tab.
- The window is 75% opaque, so the raw capture has semi-transparent margins that image viewers show as grey. It was flattened onto the Styler background color `#1E1E2E`.
- The image shows Styler settings and the public author name. It shows no paths, accounts or notifications.

## Deliberately not done

- The `davids-windhawk-mods` checkout in this workspace was not updated. It has uncommitted changes in `mods/local/taskbar-audio-visualizer` and its history diverged (ahead 5, behind 11). Publish from `work\styler-release` only.
- No pull request was opened. The push went directly to `main`, as requested.
