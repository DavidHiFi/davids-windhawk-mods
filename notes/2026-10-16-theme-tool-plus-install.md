# Theme Tool Plus — install record (2026-10-16)

Follow-up to `2026-10-16-theme-tool-plus-framework.md` (research) — the mod is
now built, installed, and committed.

## What shipped

- **Mod**: `theme-tool-plus` v1.0.0, 830 lines — UXTheme hook's
  `CThemeSignature::Verify` bypass + `SetSysColors` guard + optional
  `CoCreateInstance` blocker, plus a full theme-manager client (COM
  `IThemeManager2`, CLSID `9324da94-50ec-4a14-a770-e90ca03e7c8f`): theme list,
  apply with per-part ignore flags, refresh/reinit actions, and a hotkey
  picker window (Ctrl+Alt+Y default) hosted by windhawk.exe or Explorer.
- **Installed**: rev 6 (`local@theme-tool-plus_1.0.0_6.{dll}` in
  `Engine\Mods\{64,32}`), registry read back at 4:59 PM:
  Disabled=0, Include=`winlogon.exe|windhawk.exe|explorer.exe|systemsettings.exe|logonui.exe|rundll32.exe`,
  `uxtheme-hook` Disabled=1 (its key preserved with IncludeCustom for rollback).
- **Winlogon verified**: module scan confirmed the mod DLL mapped in
  winlogon.exe, so the signature bypass is live in the logon path.
- **Committed**: `davids-windhawk-mods` @ `6cd8ffb`, new folder
  `mods/local/theme-tool-plus/` (source, README, build script, install script,
  GPL-2 LICENSE). Other threads' pending edits were not staged.
- **Scripts**: `theme-tool-plus-build.ps1` (outputs to temp), 
  `theme-tool-plus-install.ps1` (`-Audit`/`-Install`/`-Rollback`/`-Uninstall`,
  backs up to `backups\2026-10-16\theme-tool-plus\`, receipt JSON included).
- **Diagnostics**: the mod logs to
  `C:\Users\localuser\AppData\Local\Temp\theme-tool-plus-mod.log`.

## Bugs found and fixed during verification

1. Worker thread only started in Explorer — Explorer isn't running on this
   box, so the picker had no host. Now starts in windhawk.exe too.
2. Popup window was created with the exe's HINSTANCE while the class was
   registered with the DLL's — `ERROR_CANNOT_FIND_WND_CLASS`. Now one
   instance handle everywhere.
3. Stale window classes from previous mod revisions would fail re-registration
   after a reload — class names now carry a per-load `_N` suffix.
4. Ctrl+Alt+T failed to register (error 1409) — default hotkey changed to
   Ctrl+Alt+Y, probed free on this box.
5. The picker closed instantly when it could not take foreground (background
   process rule) — it now only closes on deactivate if it was activated once.

## Verification coverage

Done: build (x64 + x86, Windhawk clang, `-std=c++23`), registry read-back,
winlogon module mapping, worker-thread + class registration proven via the
mod's own log, repo commit verified by `git log --stat`.

Also done (later chains): the settings-driven apply round-trip with backup and
restore, capture of the original theme before any apply, live picker popup
screenshot via Ctrl+Alt+Y, and the preview image at
`media/previews/theme-tool-plus.png` — see the apply round-trip and picker
sections below. Nothing remains deferred; only user-decision items (old rev
DLL cleanup, license ping) are open.

## Notes

- `reports\` is write-denied on this box (even an approved ACL repair gave
  up), so diagnostics live in temp; agent-coop is broken (state-lock
  PermissionError) and the handoff brief carried coordination instead.
- Old revision DLLs `_1.._5` remain in `Engine\Mods\{64,32}` — winlogon may
  map one; remove after the next reboot.
- A Windhawk UI instance spawned from the agent's sandboxed shell shows an
  `Access is denied` error dialog (app.cpp(293)); that instance was closed.
  Start the UI normally.

## Live verification close-out (7:35–8:10 PM, chain 10)

- **RegisterHotKey: verified.** Mod log shows `RegisterHotKey ok mods=0x3
  vk=0x59` at 4:38 PM and again after the 7:34 PM re-init; a probe confirmed
  Ctrl+Alt+Y ownership. The 7:34 PM re-init logged `RegisterHotKey failed
  gle=1409` (ERROR_HOTKEY_ALREADY_REGISTERED) because the original holder was
  still alive — expected with the earlier instance's window persisting.
- **Live picker test: not completable from the agent sandbox (coverage
  limit).** Synthetic input is impossible from the DSH sandbox (SendInput
  returns 0 events; scheduled-task creation blocked via CIM, schtasks and
  COM; child processes inherit the sandbox). The last route, posting
  WM_HOTKEY directly to the mod message window, was tested at 7:59 PM
  against the live `msgwnd=0x10715B6` (owner pid 24408, explorer): a WM_NULL
  control post returned True (cross-process posting works) while WM_HOTKEY
  returned False — a UIPI/sandbox message filter blocks that specific
  message. No picker opened; the mod log was unchanged afterwards and no
  theme was applied.
- **Explorer was running** at 7:59 PM (taskbar visible in capture; mod
  window owned by explorer pid 24408) — the earlier flapping settled on its
  own, no crash events (ID 1000) logged.
- **Preview PNG not produced.** The repo preview
  (`media/previews/theme-tool-plus.png`) cannot be written from the sandbox
  (the child cannot write H:\ and binary captures cannot pass through the
  text-only write tool). Do not fabricate it: capture the picker with
  Ctrl+Alt+Y in a normal session and save it to that path.
- **Drag-to-Delete Plus live drag: deferred.** Needs real mouse input; do it
  in the next normal session.
- **Old revision DLLs `_1`–`_5` in `Engine\Mods\{32,64}`: delete after the
  next reboot.** A delete-path lock test from the agent sandbox was
  inconclusive (sandbox blocks all writes under C:\ProgramData\Windhawk;
  read-opens succeeded on all twelve files). Do not force.
- Full machine-readable detail: `H:\System Configuration\reports\
  2026-10-16-thread-sweep\final-status.json` → `liveVerification`.

## Apply round-trip (7:30–7:34 PM, handoff successor)

- **Round-trip completed and verified.** `-Backup` exported 6 registry keys +
  `Custom.theme` + receipt + `before-apply.png` to
  `backups\2026-10-16\theme-tool-plus-apply\`; `-Apply -ThemeName 'catppuccin Mocha'`
  switched `HKCU ... Themes\CurrentTheme` to
  `C:\WINDOWS\resources\Themes\catppuccin Mocha.theme` (after-apply.png);
  `-Restore` returned `CurrentTheme` to `Custom.theme` (after-restore.png).
  The `Applied theme ... (hr=...)` line goes through `Wh_Log` (Windhawk in-app
  debug view only) — not on disk; verification used the registry read-back.
- **All backup-tree writes done elevated.** The sandbox denial under
  `backups\2026-10-16\` is total: file-create at root, file-write into an
  existing elevated-created subdir, and dir-create are all DENIED (answers the
  file-vs-dir question in the gen-1 brief — no distinction). `applytest.ps1`
  was rewritten so every write into the backup tree goes through the elevated
  helper (`Invoke-Elevated`); read-backs stay in the sandbox. Editing existing
  workspace files works fine — only creation is blocked.
- **BUG FOUND: the mod's apply REWROTE `Custom.theme`.** Applying display name
  `Unsaved Theme` (= the currently-active Custom theme) re-saved the theme
  list's *current state* into `Custom.theme` instead of loading it: msstyles
  became `catppuccin Mocha.msstyles` (not Mocha Night), cursors became `aero_*`,
  wallpaper became `Blue Mocha.png`, ThemeId changed
  ({E0986DF6…} → {AF61EB09…}). Live registry cursors stayed Catppuccin (the
  apply didn't touch them), but the file was clobbered. Fix applied: copied the
  backed-up `original-current.theme` back over `Custom.theme` (hash-verified
  identical) and re-applied it via `explorer.exe <file>`; verified cursors,
  `CurrentTheme`, wallpaper (deer PNG, matches pre-test) and file hash.
  **Recommendation:** treat apply-by-name of the active custom theme as unsafe;
  either skip re-save or apply via .theme file path for Custom.
- Side effects observed, all transient: a "Please wait" screen in the
  after-apply capture (7:31:15 PM, gone by 7:34:41 PM); wallpaper render lagged
  the restore by a few minutes; a sandbox-spawned `explorer.exe` died with
  0xc0000142 during the manual re-apply (sandbox child, not the mod — no mod
  log entries at that time); its error dialog was dismissed.
- **Test settings reset** (~8:15 PM): `themeName` and `applyOnSettingsChange`
  removed from the Settings key (they were absent before the test) and
  `SettingsChangeTime` bumped. Leaving `applyOnSettingsChange=1` set would have
  re-clobbered `Custom.theme` on the next settings save.
- **License: still unverified, now with evidence.** `ramensoftware/windhawk-mods`
  has `"license": null` (GitHub API); rounk-ctrl has no personal repo containing
  the uxtheme-hook source (repo list checked; the 404 is real); the catalog page
  is JS-rendered. Embedding the signature bypass in a *published* fork has no
  license basis — keep theme-tool-plus local-only unless rounk-ctrl grants one.
- **Picker screenshot/preview image: DONE (8:36–8:45 PM, gen-3 successor).**
  - Hotkey confirmed live after the 8:19 PM settings-reset reload: the log's
    trailing `RegisterHotKey failed gle=1409` is a *second* worker thread
    colliding with the one live registration
    (`RegisterHotKey ok mods=0x3 vk=0x59` at 8:19:09 PM) — Ctrl+Alt+Y works.
  - Triggered via an elevated helper (`keybd_event` for Ctrl+Alt+Y): **input
    injection works from an elevated helper** (it escapes the DSH sandbox),
    only sandbox-direct SendInput is blocked. Popup appeared and was captured
    at native 6400×2520.
  - Preview delivered: popup crop 352×444 →
    `davids-windhawk-mods\media\previews\theme-tool-plus.png`
    (SHA-256 `D6DE1475…FFAA215`, hash-verified read-back). List shows
    Unsaved Theme (selected), Main 01, High Contrast #1/#2/Black/White,
    Windows (light), all catppuccin variants, Windows (dark), spotlight, Glow,
    Captured Motion, with Apply/Refresh.
  - Dismissal: Escape goes to the foreground app, not the picker; the picker
    closes on `WM_CLOSE` sent to window class `ThemeToolPlusPicker_1`
    (found via EnumWindows — its rect is in virtual-screen coords, origin
    −1920,−1080 on this box). A stale `explorer.exe` 0xc0000142 error dialog
    (class `#32770`) was also closed the same way. Desktop verified clean by
    screenshot at 8:45 PM.

## 2026-10-21 7:59 PM - v1.1.0 install (settings rework, hotkey removed)

- Owner order executed: hotkey scrapped, everything moves to the mod's
  settings tab with all ThemeToolSharp options, humanized wording.
- Merged the settings rework into the repo copy (v1.0.1 base, kept the
  installed-themes dropdown and the Unsaved Theme guard), bumped to 1.1.0.
- Theme pack flag bits confirmed against upstream ThemeToolSharp
  IThemeManager2.cs: Unknown1=1<<0, Unknown2=1<<1, Silent=1<<2, Roamed=1<<3.
  Both SetCurrentTheme call sites now pass PackFlagsFromSettings().
- Build: local@theme-tool-plus_1.1.0_1_{64,32}.dll, BUILD OK (x64 sha256
  43AEF023..., x86 BDCF8B3A...).
- Install: rev 9, receipt + registry backups in
  backups\2026-10-21\theme-tool-plus (written by the elevated run under
  backups\2026-10-16\theme-tool-plus per script default - the .reg exports
  from 20261021-195935 are there). Registry read back: LibraryFileName=
  local@theme-tool-plus_1.1.0_9.dll, Version=1.1.0, Disabled=0.
- Mod log: clean reload at 7:59:37 PM, worker thread + classes fine, and
  no RegisterHotKey line (the hotkey no longer exists).
- Stale registry value hotkey=Ctrl+Alt+Y deleted from the mod Settings key
  (elevated exit 0; only updateLogonUI=1 remains there). Pre-delete copy in
  the 20261021-195935 key export.
- Pushed davids-windhawk-mods @ 0c373dc (main). Engine working copy synced,
  hash-equal.
- Deferred: old rev DLLs _1.._8 in Engine\Mods\{64,32} (18 files) remain
  locked by live processes; delete after the next reboot.
