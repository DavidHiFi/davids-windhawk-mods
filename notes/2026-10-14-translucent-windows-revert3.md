# Translucent-windows third silent revert — restored, guard installed (2026-10-14)

## What happened

The T3 drift canary (scheduled task `translucent-windows drift check`, every 6 h)
caught the third revert at 08:27 local (00:27Z) on 2026-10-14:

- Registry pointed back at stock 1.8.2 (`LibraryFileName
  translucent-windows_1.8.2_137900.dll`, `Version 1.8.2`, `Disabled 0`).
- Fresh stock build 137900 (x86 267,776 B, x64 266,240 B) written 07:54:17–22
  local (2026-10-13T23:54Z); `ModsSource\translucent-windows.wh.cpp` overwritten
  with stock 1.8.2 (`0F8801…`) at 07:54:22 local, in the engine's install order
  (x86 DLL → x64 DLL → source save).
- The round-5 x64 DLL `1.8.3_256343` was still on disk with intact hash
  `D284A5E3…` — just unreferenced.

## Who did it: the Windhawk app itself

- `C:\ProgramData\Windhawk\userprofile.json` (the app's own state file, which
  agents never touch) was rewritten 4 ms after the source save — 23:54:22.412Z
  vs 23:54:22.407Z. Its `translucent-windows` entry says plain stock 1.8.2, so
  the catalog machinery keeps reconciling the fork away.
- Recurring stock builds confirm repeated app-level reinstalls: 795679
  (dbwin.log, 2026-10-08), 598230 (2026-10-13 11:58 local), 137900 (2026-10-14
  07:54 local).
- No Windows scheduled task exists for it (name scan, TaskCache action scan,
  task-XML scan), no Run-key entry, no event-log entries, no engine log, and no
  T3 thread on the machine was active in the window (checked this project's 67
  threads plus the newest activity of System Configuration, localuser, Claude,
  scratch, davids-windhawk-mods and weather-catalog projects).

Timeline correction: the drift report's "SettingsChangeTime bumped 2 h 21 m
before the writes" was an artifact. The 2026-10-13 revert2 script bumped SCT
with `Get-Date -UFormat %s` under elevated Windows PowerShell 5.1, which
encodes local time as UTC — an 8 h skew here. Fix #2 really ran 21:32:59
local. Both new scripts use `[DateTimeOffset]::UtcNow.ToUnixTimeSeconds()`.
Existing SCT values are +8 h shifted; harmless (the engine only detects
change), but do not do forensics on raw SCT epochs.

## Restore (2026-10-14 09:05 local)

`scripts\2026-10-14-translucent-windows-revert3.ps1 -Action Install`
(elevated): backed the drifted state up to
`backups\2026-10-14\translucent-windows-revert3\` (key export + stock 137900
source copy), copied the reviewed fork source back, re-pointed
`LibraryFileName` at the on-disk `1.8.3_256343`, bumped SCT. No recompile.

Verified by independent readback (registry + both hashes) and module census:
25 processes (3 explorer + 22 conhost) mapped `1.8.3_256343` immediately after.
Receipt: `reports\2026-10-14-translucent-windows-revert3\receipt-reapply.json`.

## Guard (make it stick)

`scripts\2026-10-14-translucent-windows-guard.ps1` + scheduled task
`TranslucentWindowsGuard` (every 5 min + at logon, highest privileges, silent
UAC). Checks registry values, source hash and both DLL hashes against pristine
copies staged in `Windhawk\translucent-windows\guard\` (both DLLs + a full key
export). On drift it backs the drifted state up to
`backups\<date>\guard-<HHmmss>\`, restores, bumps SCT, writes a receipt to
`reports\2026-10-14-translucent-windows-guard\` and logs to
`C:\ProgramData\Windhawk\ModsWritable\translucent-windows-guard.log`.

Live-tested: induced the exact revert signature, guard detected and healed it
in 0.4 s, end state verified. Receipt `heal-20261014-091203.json`.

- Settings edits through the engine are safe (the guard ignores
  `SettingsChangeTime`).
- For source edits, new builds or an id migration: touch the suspend marker
  `C:\ProgramData\Windhawk\ModsWritable\translucent-guard.suspend` first and
  delete it afterwards.
- To retire the guard: `Disable-ScheduledTask -TaskName TranslucentWindowsGuard`.

agent-coop remained unreachable from this sandbox (state dir denied, same as
2026-10-13); no other thread was active during the writes.

## Definitive fix still recommended

The guard is a tripwire, not a cure: the catalog machinery still owns the
`translucent-windows` id. Every other forked mod here is a `local@` id. Migrate
this one the same way (see `notes\2026-10-04-mod-id-migration.md`: rebuild x86
and x64 with the bundled clang, `-DWH_MOD` only, id via a force-included
header, `reg copy /s`, disable the old id) — and suspend the guard while doing
it. After that the catalog cannot see the mod and the reverter has no target.

## Rollback

`scripts\2026-10-14-translucent-windows-revert3.ps1 -Action Rollback`
(restores stock 1.8.2/137900 from the backup), or import
`backups\2026-10-14\translucent-windows-revert3\translucent-windows-before-revert3.reg`.
The guard task must be disabled first if rollback is intentional.
