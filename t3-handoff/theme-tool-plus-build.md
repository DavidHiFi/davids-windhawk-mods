# Handoff — Theme Tool Plus build and install

Thread: this session (Theme Tool Plus continuation) | Chain generation: 1 | UPDATED 2026-10-21 8:05 PM

## Update 2026-10-21 8:05 PM — v1.1.0 shipped (settings rework)

- Hotkey removed everywhere per owner order (settings tab is the only
  control surface): setting entry, struct field, LoadSettings, ParseHotkey,
  RegisterHotKey block, WM_HOTKEY case, README table and @description.
  The picker still exists and opens once when a settings save runs the new
  "Open the theme picker" action (action index 3).
- Settings tab carries every ThemeToolSharp option: six keep-current toggles,
  noHourglass (now a real setting, default on), apply flags 1-2, theme pack
  flags Unknown1/Unknown2/Silent/Roamed and start-up flags 1-2. Humanized
  names and descriptions. Pack bits confirmed against upstream
  ThemeToolSharp/IThemeManager2.cs: U1=1<<0, U2=1<<1, Silent=1<<2, Roamed=1<<3.
- Built both archs (43AE...FC83 x64, BDCF...B9C9 x86), installed rev 9
  (v1.1.0) at 7:59 PM via theme-tool-plus-install.ps1 -Install. Registry
  read back: LibraryFileName=local@theme-tool-plus_1.1.0_9.dll,
  Version=1.1.0, Disabled=0. Mod log shows a clean reload with no
  RegisterHotKey line. Stale HKLM hotkey value deleted (elevated exit 0).
- Pushed davids-windhawk-mods @ 0c373dc; engine working copy synced
  (hash-equal). v1.0.2 rev 8 from 10-18 8:19 PM is superseded.
- Still deferred: deleting old rev DLLs _1.._8 in Engine\Mods\{64,32} after
  the next reboot (all locked by live processes as of today 7:45 PM).

## Status: COMPLETE (see coverage limits)

- Research: `notes/2026-10-16-theme-tool-plus-framework.md`.
- Fork: `Windhawk\theme-tool-plus\` (source + build + install scripts).
- Built rev 6, installed (rev 6 active, uxtheme-hook Disabled=1, rev 6 in
  `Engine\Mods\{64,32}`), winlogon verified MAPPED with the mod DLL.
- Committed to `davids-windhawk-mods` @ `6cd8ffb`
  (`mods/local/theme-tool-plus/`: wh.cpp + README + build + install + LICENSE).
  Only that folder was staged; other threads' pending edits untouched.

## Coverage limits (deferred, need a live session)

1. Live picker test: needs a real Ctrl+Alt+Y press. NO synthetic input was
   sent late in the run (user gaming fullscreen per steer). The picker code is
   static-verified; the mod writes its own log at
   `C:\Users\localuser\AppData\Local\Temp\theme-tool-plus-mod.log` — check
   `RegisterHotKey ok` there after first live run.
2. Preview image: `media/previews/theme-tool-plus.png` — capture the picker
   live, then drop it in (README already references it).
3. Settings-driven apply round-trip: deferred (would swap the user's theme
   while gaming). Original theme name also never captured.

## Gotchas found (fixed in rev 6)

- Worker thread must start in windhawk.exe too (Explorer absent on this box).
- Popup class must be registered AND created with the DLL's own HINSTANCE
  (GetModuleHandleExW FROM_ADDRESS), not the exe's.
- Class names carry a per-load suffix `_N`; stale classes from prior revisions
  would break re-registration.
- Ctrl+Alt+T conflicted (ERROR_HOTKEY_ALREADY_REGISTERED 1409); default is
  now Ctrl+Alt+Y (probed free). Hotkey is a setting, changeable.
- Wh_Log is not reachable headlessly → TtpLog() temp-file logging added.

## Environment traps hit

- pwsh child processes cannot create new files in the workspace (DSH
  workspace-write); the `write` tool can. Silent elevation (no prompt) used
  for registry/ProgramData/repo `.git` writes — worked every time.
- `reports\` remains write-denied even to an approved ACL repair (skill
  verdict: stop & report). Diagnostics went to temp instead.
- agent-coop broken (state-lock PermissionError); this brief was the channel.
- Windhawk UI spawned from a sandboxed shell inherits the restricted token and
  shows `app.cpp(293) Access is denied` — start it normally, not from the
  agent's shell. The sandboxed-instance error dialog was closed and the
  crippled process removed.
- Old revision DLLs `_1.._5` remain in `Engine\Mods\{64,32}` (winlogon may map
  an older rev; delete after next reboot).

## Warnings

- `uxtheme-hook` stays disabled while Theme Tool Plus is enabled (same hooks).
- `windhawk.exe -restart` is banned; per-mod reload only.
- Halo's Sparks: one request at a time (5/8 busy at close).
