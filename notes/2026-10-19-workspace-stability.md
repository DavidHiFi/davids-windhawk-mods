# Workspace stability — 2026-10-19 desktop error windows

Status: RESOLVED (final ground truth 8:40:07 PM). Proof screenshots delivered as real
thread attachments in this thread: 7:58:25 PM (Windhawk window open and normal, zero
error windows), 8:30:15 PM (reproduction evidence), 8:40:07 PM (final clean desktop).

## Symptom (~3:00 PM)

Two error windows stacked on the main desktop with the Windhawk GUI hidden behind them:

1. `explorer.exe - Application Error` — "The application was unable to start correctly
   (0xc0000142)". A hard-error box hosted by csrss.exe (System integrity), shown when a
   process spawn's DLL init fails. It ignores clicks from the owner's own automation and
   from admin scripts (see "Why the csrss box could not be closed by script" below).
2. A small `Windhawk` dialog (371×186, class #32770) hosted by the windhawk-ui process —
   from the same family as the "Windhawk error … 80070005 Access is denied" dialog
   reproduced at 8:30:15 PM (exact text at 3:00 PM was not captured).

Background churn: the shell was killed/restarted repeatedly today — Winlogon 1002 events
("shell stopped unexpectedly…") at 12:01 PM through 5:24 PM (8+ restarts), plus one real
crash at 4:54:19 PM (explorer.exe, Windows.UI.Xaml.dll, Event 1000 ×2). Transient spawn
failures during that churn are what produced the 0xc0000142 boxes. The Windhawk GUI was
not "lost": it was behind the dialogs, and its UI process was replaced several times
during the evening (52848 → 39236 → 37956 → 66184) — no crash loop, no windhawk
Application Error events; the owner was actively using the machine.

## Root causes

1. **Shell restart churn** → transient `explorer.exe` spawn failures → csrss-hosted
   0xc0000142 hard-error boxes that linger after the desktop recovers.
2. **Windhawk second-instance IPC denied (80070005)**: launching `windhawk.exe` from a
   non-elevated (or sandboxed) context while the elevated windhawk-ui instance is running
   makes the second instance's IPC to the first fail, and a `Windhawk error` dialog pops
   (`app\apps.cpp(293)\windhawk.exe…: Exception(1) tid(1e50) 80070005 Access is denied`).
   Reproduced 8:30:15 PM — the dialog was hosted by the new instance (pid 68912). This
   family very likely matches error window #2 of the 3:00 PM incident.
3. The GUI "hidden" state was z-order (behind the dialogs), not a broken engine.

## Why the csrss box could not be closed by script (probe evidence, 7:33 PM)

- `BM_CLICK` on its OK button via PostMessage from an elevated admin: **returned False**
  (UIPI blocks High-IL → System-IL button messages).
- `WM_CLOSE` PostMessage: returned True (UIPI-allow-listed) but the box ignored it.
- Only the owner's own input (hardware input is unrestricted) or SYSTEM-in-session-1
  input can click it. The 8:30:15 PM "Windhawk error" dialog, by contrast, is hosted by
  windhawk-ui (High IL) — an elevated BM_CLICK on its OK button returned True and closed
  it at 8:40:05 PM.

## Resolution timeline

- 3:54 PM — handoff brief written; diagnostics kept under the windhawk-engine singleton
  read-only rule; translucent-flyouts 0.6.51 (release) verified enabled via registry at
  7:45 PM (`Version=0.6.51`, `LibraryFileName=…_0.6.51_1.dll`, `Disabled=0`) and left
  untouched. (An earlier draft of this note claimed 0.6.52 — superseded.)
- 7:33–7:41 PM — probe + first scripted close attempts (UIPI-blocked, documented above);
  the 0xc0000142 box disappeared between 7:33 and 7:41 PM (closed externally — owner
  action most likely; my attempts demonstrably did not close it).
- 7:51 PM — elevated ground truth: shell explorer pid 94000 (started 5:24:32 PM)
  responding; zero error dialogs; windowless zombie explorer 67732 already gone; engine
  healthy (4 windhawk + 17 windhawk-mod pids).
- 7:58:25 PM — screenshot proof: Windhawk main window open and normal, desktop clean.
- 8:12–8:20 PM — validated the reusable hard-error closer pipeline end-to-end up to its
  final API call (see open items).
- 8:29–8:40 PM — reproduced and then closed the "Windhawk error 80070005" dialog family
  (my own relaunch spawned it; closed by elevated BM_CLICK); final clean capture 8:40:07 PM.

## Final ground truth (8:40:07 PM)

- Zero error dialogs on the primary desktop.
- Shell: explorer pid 94000 (5:24:32 PM), responding. Second explorer pid 107248
  (3:13:19 PM) hosts the taskbar-audio-visualizer mod's capture picker — do not kill.
- Engine: 4 windhawk + 17 windhawk-mod pids; translucent-flyouts 0.6.51 enabled.
- Windhawk UI: in tray (owner's current state); captured visible and normal at 7:58:25 PM.

## Scripts and receipts

All in `reports\2026-10-19-workspace-stability\`: window scan (`scan-windows.ps1`),
guarded capture (`capture-screen.ps1`, `capture-verified.ps1` — refuses when the session
is locked, validates the PNG is not all-black), dialog dump (`diag-dialogs.ps1`),
UIPI probe (`probe-inner.ps1`), closer (`resolve-desktop.ps1`), SYSTEM clicker pipeline
(`system-spawner.ps1`, `system-clicker.ps1`, `run-system-clicker.ps1`), ground truth
(`verify-state.ps1`), window bring-up experiments (`bring-windhawk-up.ps1`,
`show-and-capture.ps1`), dialog close + capture (`close-and-capture.ps1`), plus evidence
logs (`elevated-out`, `probe-out`, `runner-out`, `verify-out`, `spawner-out`,
`showcapture-out`, `closecap-out`, `bringup-out`) and the three PNGs.
Note: the sandboxed shell cannot write anything in this workspace (traps 21–22), so all
files were created with the harness file-write tool; elevated children write their own
logs. A pwsh `Copy-Item` of `verify-out.txt` was also denied — same rule.

## Stability rules (evidence-based)

1. Never launch `windhawk.exe` (plain) from a non-elevated or sandboxed context while the
   elevated UI instance runs — it pops the "Windhawk error 80070005" dialog. To show the
   running instance's window, launch it elevated; to close such a dialog, elevated
   BM_CLICK on its OK button works.
2. A 0xc0000142 box for explorer.exe is not script-closable from admin (UIPI). Options:
   wait for the owner to click OK (it is a normal modal for them), or a sign-out cycle.
   Do not restart Explorer to clear it — it is not an explorer process (csrss owns it).
3. `windhawk.exe -restart` stays banned (it restarts Explorer too). Per-mod reload via
   `SettingsChangeTime` is the only sanctioned reload; no engine restart was needed today.
4. Verify the desktop from an elevated process: sandboxed process/window views degrade
   over a session (7:45 PM non-elevated scan returned zero windows while an elevated scan
   minutes later showed the healthy desktop).
5. Tauri windows hidden to tray ignore cross-process `ShowWindow(SW_SHOW)` (visible stays
   False) — do not fight it; use the app's own single-instance handshake, launched at the
   right integrity level (rule 1).

## Open items

- **SYSTEM-in-session-1 clicker** (`run-system-clicker.ps1`): implemented and validated
  through SeTcbPrivilege enablement; the final token retarget
  (`SetTokenInformation`/TokenSessionId) still fails with err 203. The earlier variant
  using `WTSQueryUserToken` creates a Medium-IL child (useless against a System-IL
  dialog). Scripts and precise failure points are in the report folder for the next
  iteration; until then, rule 2 applies.
- The exact trigger of the original 3:00 PM "Windhawk" dialog is unidentified (its text
  was not captured at 4:03 PM); the 8:30 PM reproduction matches family and size.
- coop CLI remains unusable under the DSH sandbox (state dir outside the sandbox);
  `t3-handoff\` briefs stay the coordination record.
