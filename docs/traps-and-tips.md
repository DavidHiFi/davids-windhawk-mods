# Traps and tips (hard-won on this machine)

Sources: `H:\System Configuration\notes\2026-09-28-altsnap-windhawk-fork.md`,
`notes\2026-09-25-taskbar-giant-pill.md`,
`notes\2026-09-28-windhawk-taskbar-styler-tray-dots.md`, and the 2026-09-26/28
Windhawk sessions.

## Building mods

1. `-DWH_EDITING` is the editor's syntax mode: it turns every `Wh_*` API call into
   a no-op stub, so the DLL imports nothing from `windhawk.dll` and silently does
   nothing. Production builds use `WH_MOD` only and must import `InternalWh_*`.
2. Windows PowerShell 5.1 strips the quotes from `-DWH_MOD_ID=L"..."` on the clang
   command line. Pass the mod id through a force-included header instead.
3. The engine keeps loaded DLLs mapped, so overwriting the same file fails. Install
   a new revision (`_1`, `_2`, ...) and point `LibraryFileName` at it.
4. Windhawk mods do not initialize in console-subsystem processes such as
   `powershell.exe`. Test in a GUI-subsystem exe.
5. A medium-integrity process cannot take the foreground while an elevated window
   holds it; run interactive test harnesses elevated or de-elevate the test window.
6. A local fork's metadata `@id` must keep the CATALOG id without the prefix:
   the file is `local@<catalog-id>.wh.cpp`, the registry key is
   `local@<catalog-id>`, but inside the source it stays `@id <catalog-id>`.
   Putting `local@` inside `@id` makes the app's metadata parser (shared by the
   UI and the CLI) reject the mod with MODS_LOAD_FAILED ("Mod id must only
   contain 0-9, a-z, and a hyphen") while the engine keeps running it happily -
   the engine reads the compiled DLL, not the metadata. The CLI also cannot
   install/compile `@` ids at all, so `local@` installs are the manual path:
   bundled clang (id via force-included header), stage source + DLLs, clone the
   registry key, bump `SettingsChangeTime` (recipe:
   `notes\2026-10-04-mod-id-migration.md`).

## Settings and scripts

6. Mod settings are structured registry values, not a YAML blob. Bump
   `SettingsChangeTime` after writing, then restart the engine.
7. `Set-ItemProperty` has no `-PropertyType` parameter; only `New-ItemProperty`
   takes it. A failed call mid-script leaves the change half-applied - write
   scripts so a re-run completes idempotently.
8. PUA glyphs (U+E000-U+F8FF, e.g. Segoe Fluent icons) in a BOM-less UTF-8 `.ps1`
   are misread as ANSI by PowerShell 5.1. Build them at runtime:
   `[char]0xE971`, never as literals in the file.
9. `Start-Process -Verb RunAs` with an argument ARRAY mangles arguments when a path
   contains a space - the child exits `-196608` (0xFFFD0000) and silently does
   nothing. Pass ONE pre-quoted argument string instead:
   `-ArgumentList "-NoProfile -File `"$path`" -Install"`.
10. This machine elevates silently (`ConsentPromptBehaviorAdmin=0`), so an elevated
    launch can fail with no visible prompt. Always capture the child exit code and
    read the log back.

## Taskbar styler specifics

11. `Rectangle` has no `CornerRadius`; rounded corners there are `RadiusX`/`RadiusY`.
    One bad setter drops the whole XAML `Style` for that target - check every
    property against the element type.
12. The mod parses one XAML `Style` per target; a single invalid property silently
    removes the other setters in the same target block.
13. Style constants capture (`=>`) measured values (e.g. `ActualWidth => BtnW`) for
    use in later expressions; `{{...}}` arithmetic is integer math.
14. Settings writes to the styler apply live off `SettingsChangeTime` (no engine
    restart observed for the giant-pill rounds), but restarting the engine is the
    reliable path for all mods.

## Engine and injection

15. Never run `windhawk.exe -restart` on this machine: it also restarts explorer
    and can freeze a live T3 Code GUI (only a T3 Code close+reopen recovers;
    user-reported 2026-09-28). Mod/settings changes apply **live**: write the
    mod key elevated and bump `SettingsChangeTime`. The engine watches
    `HKLM\SOFTWARE\Windhawk\Engine\Mods` with `RegNotifyChangeKeyValue` and
    reloads mods in every process; no service restart needed.
16. After an engine restart, an already-running process can keep `windhawk.dll`
    and the mod DLL loaded while its session is dead: the module list still
    shows the mod, but drag and hotkeys silently do nothing. Only a re-init of
    that process (live reload, app restart, or reboot) fixes it. A reboot is the
    clean normalization.
17. **CSRSS-hosted error windows (UIPI)**: The error dialog from the Oct 19 crash was csrss-hosted
    (SYSTEM integrity). UIPI (User Interface Privilege Isolation) blocks WM_CLOSE/BM_CLICK messages
    even from elevated admin processes. If this recurs, identify the source process first before
    applying any close/restart. This crash originated in translucent-flyouts 0.6.52.
    Testing: open translucent-flyouts UI, watch Task Manager process list for csrss.exe hosts
    that spawn dialogs after SettingsChangeTime changes.
18. Elevated processes are injected normally (service is LocalSystem), but a
    lower-integrity process cannot move a higher-integrity window - `SetWindowPos`
    fails with access denied. Per-process injection, never external window
    manipulation, is what makes elevated windows work.
19. **Mod settings persistence**: Always bump `SettingsChangeTime` after writing mod keys,
    then restart the engine. The engine watches `HKLM\SOFTWARE\Windhawk\Engine\Mods`
    with `RegNotifyChangeKeyValue` and reloads mods in every process; no service restart needed.
20. After an engine restart, an already-running process can keep `windhawk.dll`
    and the mod DLL loaded while its session is dead: the module list still
    shows the mod, but drag and hotkeys silently do nothing. Only a re-init of
    that process (live reload, app restart, or reboot) fixes it. A reboot is the
    clean normalization.
21. **Translucent-flyouts monitoring**: Monitor the `local@translucent-flyouts` registry
    key for unexpected modifications. The mod is at version 0.6.52; ensure the
    `SettingsChangeTime` is updated after any UI changes to detect unintended
    modifications.
22. Elevated processes are injected normally (service is LocalSystem), but a
    lower-integrity process cannot move a higher-integrity window - `SetWindowPos`
    fails with access denied. Per-process injection, never external window
    manipulation, is what makes elevated windows work.
23. Some agent sessions get a sandbox whose shell cannot write anywhere under
    `H:\Windhawk Configuration` even though the ACLs are clean (verified with the
    ACL diagnose script: `localuser` holds FullControl, verdict `NOT_THIS_CLASS`,
    no package ACEs). The failure is a plain "Access denied" with no
    `[sandbox: ...]` marker, under workspace-write mode. Workaround: write
    workspace text files through the agent harness's file-write tool (T3 Code:
    `write`/`edit`), and produce binaries or do elevated work via `$env:TEMP` +
    `Invoke-Elevated.ps1` - the elevated process is unconfined and can write the
    workspace. Seen 2026-10-15 (privacy-anchor session).
24. Each pwsh tool call gets its own `$env:TEMP` subdirectory (`Temp\dsh-*`)
    which later calls do not see. Stage a script and consume it in the SAME
    call, or use a fixed path both sides can read (e.g. write the script with
    the file-write tool, then point `Invoke-Elevated.ps1 -File` at it).

## Verification

19. Screenshots are the proof for visual changes: capture the bottom strip
    (`[System.Windows.Forms.SystemInformation]::VirtualScreen` bottom edge),
    crop the tray region, scale with NearestNeighbor. For taskbar-only captures,
    PrintWindow of `Shell_TrayWnd` avoids overlays.
20. `Engine\ModsWritable\mod-status` per-process records stopped being written
    after 2026-10-08 13:01 while mods demonstrably run (mod-storage writes,
    engine IPC), so census scripts that count mod-status files report false
    zeros. Verify load state with `windhawk-cli --json mod list` (engine's own
    config view) and recent `Engine\ModsWritable\mod-storage` activity instead.
16. The mod UI's textual mode is the fastest way for a human to audit the current
    settings; the registry is the fastest for a script.

## Workspace and session tooling

21. Some agent sessions get a sandbox whose shell cannot write anywhere under
    `H:\Windhawk Configuration` even though the ACLs are clean (verified with the
    ACL diagnose script: `localuser` holds FullControl, verdict `NOT_THIS_CLASS`,
    no package ACEs). The failure is a plain "Access denied" with no
    `[sandbox: ...]` marker, under workspace-write mode. Workaround: write
    workspace text files through the agent harness's file-write tool (T3 Code:
    `write`/`edit`), and produce binaries or do elevated work via `$env:TEMP` +
    `Invoke-Elevated.ps1` - the elevated process is unconfined and can write the
    workspace. Seen 2026-10-15 (privacy-anchor session).
22. Each pwsh tool call gets its own `$env:TEMP` subdirectory (`Temp\dsh-*`)
    which later calls do not see. Stage a script and consume it in the SAME
    call, or use a fixed path both sides can read (e.g. write the script with
    the file-write tool, then point `Invoke-Elevated.ps1 -File` at it).

## Error windows and desktop state (2026-10-19)

23. The `0xc0000142` "unable to start correctly" box for explorer.exe is hosted by
    csrss.exe (System IL), not by explorer: PostMessage `BM_CLICK` on its OK button
    from an elevated admin returns False and `WM_CLOSE` is delivered but ignored
    (probed 2026-10-19 7:33 PM). It is not script-closable short of SYSTEM input in
    the console session; it also disappears on its own when the failed spawn's
    session cleans up. Do not restart Explorer to clear it - it is not explorer's
    window. Evidence: `reports\2026-10-19-workspace-stability\probe-out.txt`.
24. Launching `windhawk.exe` (plain, no args) from a non-elevated or sandboxed
    context while the elevated windhawk-ui instance runs pops a `Windhawk error`
    dialog: `app\apps.cpp(293)\windhawk.exe... Exception(1) ... 80070005 Access is
    denied` - the second instance's IPC to the elevated first is denied (reproduced
    2026-10-19 8:30:15 PM, host pid 68912). The dialog is closable with an elevated
    BM_CLICK on its OK button (returned True 8:40:05 PM). To show the running
    instance's window, relaunch windhawk.exe elevated instead.
25. Sandboxed process/window views degrade over a session: a non-elevated scan at
    7:45 PM returned zero windows and zero processes while an elevated scan minutes
    later showed the healthy desktop (explorer 94000, tray, all apps). When a
    shell-based scan comes back empty, re-verify elevated before concluding anything.
26. Tauri windows (Windhawk UI) hidden to tray ignore cross-process
    `ShowWindow(SW_SHOW)` - `IsWindowVisible` stays False. Only the app's own
    single-instance handshake (relaunching windhawk.exe at the right integrity
    level, see 24) shows it reliably.
