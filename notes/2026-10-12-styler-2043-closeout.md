# Windhawk Styler 2.0.43 closeout (2026-10-12)

Continuation of thread `db6a16f9-962d-4575-ab9c-ab2f934b0d36` (interrupted 2026-10-11
16:37 mid-verification). Canonical task note:
`H:\Windhawk Configuration\notes\2026-10-11-styler-2041-ring-accent.md`.

## State verified this session

- Installed: registry `Version 2.0.43`, `LibraryFileName
  local@windhawk-styler_2.0.43_212412.dll`, `SettingsChangeTime 1791725052`.
- Installed source `C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp`
  SHA256 `728971159015974C18027EA7AA316D072419FA576D084C7AD700B63D2FC7AC55` —
  equals both repo copies (`davids-windhawk-mods` main and `work\styler-release`).
- Release checkout `work\styler-release`: clean at `7e02dc3` (2.0.43).
- Main checkout `davids-windhawk-mods`: `main` at `3c17f10` (2.0.43); only the
  other thread's `taskbar-audio-visualizer` edits dirty, untouched.
- Nothing pushed; no PRs. Nothing left running; no leftover UI (probe instance
  died with its sandbox job).

## Final review round

The interrupted session's review subagent finished but its report was lost with
the session. A re-run review subagent exhausted its context before reporting.
Closeout instead verified every 2.0.43 hardening item directly in the shipped
source (`work\styler-release\...\windhawk-styler.wh.cpp`, 1779 lines):

| # | Item | Evidence (line) |
|---|------|-----------------|
| 1 | Cave capacity = tail/32, guarded before any write | 1115, 1148 |
| 2 | Put site: 5-byte call + one NOP; original `test/js` kept | 1164-1175 |
| 3 | 32-byte cave records matching 32-byte slots | 1149-1153, 1180 |
| 4 | `FlushInstructionCache` on every restore path | 1063, 1072, 1161, 1177 |
| 5 | Relaunch cooldown single CAS | 1605 |
| 6 | 16 KB relaunch cmdline, checked length | 1658-1661 |
| 7 | `GetClassNameW` results checked (3 sites) | 624, 637, 702 |
| 8 | Pong payload > 125 dropped (RFC 6455) | 1291-1292 |
| 9 | Unload waits 30 s, logs if worker still running | 1741 |
| 10 | CDP target chosen by `tauri.localhost` URL | 1240, 1260 |
| 11 | Dead `g_webview` block and `BuildCleanupJs` fully removed | zero refs |

CSS parity was already proven before the interruption: shipped `BuildCss` output
== captured live-page baseline (10,520 chars) for this machine's settings, plus
a 4,097-combination settings sweep (case 9999 byte-identical).

## Live re-pull attempt (not completed)

Two launch+CDP probes failed from this session's sandbox: the launched UI was
invisible to process APIs, stayed alive through the 90 s wait but never bound
CDP, and died with the job's teardown. Event log shows no windhawk crashes in
the last 30 h — kills, not crashes. Recorded evidence from 2026-10-11 (registry,
module list, live style tag, ring crops) stands; the re-pull was redundant.

## Tools added here

- `scripts\2026-10-12-styler-cdp-repull.ps1`, `scripts\2026-10-12-styler-cdp-repull2.ps1`
  (probe scripts; kept for reference).

## Verdict

Set-and-forget: 2.0.43 installed, committed in both checkouts, all hardening
verified in place. Deliberately open (documented, not a defect): put-site
rewrite without thread freezing — needs a test rig to change safely.
