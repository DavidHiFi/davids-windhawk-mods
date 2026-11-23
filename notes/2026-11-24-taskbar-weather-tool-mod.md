# Taskbar Weather 1.6.0: tool mod, 2026-11-24

The catalog reviewer (m417z, PR ramensoftware/windhawk-mods#5834) asked for a tool mod so a
crash can't take Explorer down. 1.6.0 does that.

- Runs in its own `windhawk.exe -tool-mod "taskbar-weather"` process (`@include windhawk.exe`,
  `WhTool_*` entry points). No `@architecture`: windhawk.exe 1.7.3 is 32-bit.
- The label is a cross-process child of `Shell_TrayWnd`. `TaskbarCreated` plus the 2 s check put
  it back after an Explorer restart.
- Pushed to DavidHiFi/windhawk-mods branch `taskbar-weather` as 8a84767. Validation, build and
  label checks passed. Reply posted to m417z with `/ai-review` at 2:45 am.
- Not in the owner's own repo or on the tower (the local copy was retired), so nothing to
  publish there.

## Test PC run (release copy, 2:36 to 2:42 am)

All pass: tool process 32-bit with the mod loaded; label visible, child of the tray, owned by the
tool process; hover card shows and hides; back after an Explorer restart in the same tool
process; left offset moves it; off removes process and label; on again starts a new one;
killing the tool leaves Explorer up and removes the label; no crash events. Test PC reset and
unlocked.

Kit and results: Warden `D:\Agent Work\weather-tool-160\` (`wt-driver.ps1`, `wtvm.ps1`,
`results\out\`). `make-diag.py` writes a file-logging test build into `diag\`; never push it.

## Lesson

Two earlier runs said "label none". The mod was fine: the probe passed `$null` as the window
title to `FindWindowExW`, which PowerShell turns into "", so only empty-titled windows matched.
Use `[NullString]::Value` (memory: powershell-null-string-findwindow).

## 1.6.1 (AI review of 1.6.0)

The robot review had no code problems. It asked for the launcher block to match the wiki
snippet exactly (the session 0 check and the full header comment were missing) and for the
README to say "a crash can't take Explorer down" instead of "a problem can't take the taskbar
down" (a hang can still stall taskbar input). Both done, compiled for 32 and 64 bit with only
the snippet's own `lpReserved` warning, pushed as eb8cc7f. Kit: Warden
`D:\Agent Work\weather-tool-161\`. Behaviour in a user session is unchanged, so no new test PC
run.

## Next

When the AI review of 1.6.1 comes back clean, comment `/ready-for-reviewer`.
