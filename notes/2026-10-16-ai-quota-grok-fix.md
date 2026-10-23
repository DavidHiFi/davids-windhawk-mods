# 2026-10-16 — Taskbar AI quota: Grok real amount + stack fix (1.8.2.0)

Gen-2/3 chain (f101f39e → mcp:08750cc2 → this). Gen 1 diagnosed the Grok provider
error as transient (free limit NOT exhausted, retry grok-4.7); gen 2 patched the
source; this session compiled, installed, and verified.

## What changed

- **Grok free plan shows the real amount**: the mod now also reads the plain
  `/v1/billing` payload (`used` + `monthlyLimit: 0` + monthly period). With no
  published cap the bar fill stays empty and the percent slot shows the amount
  (`802cr`), the label shows the true window (`31d`, Oct 1 – Nov 1), and the
  tooltip says credits used / no published cap / reset date.
- **Stack regression fixed**: Grok free rejoins the compact stack
  (`VisibleBarCount` exception for the weekly bar when grok-free), so it sits
  **above OpenAI** in accounts order.
- Version 1.8.2.0, built with the Windhawk clang
  (sha256 EAB4EA85…FD53), installed via `LibraryFileName` + `SettingsChangeTime`
  hot reload. No engine restart, ModsWritable untouched.

## Verification (all live, 2:27–2:38 AM)

- explorer has 1.8.2.0 mapped; screenshots in
  `reports\2026-10-16-ai-quota-grok\` show `Grok 31d 802cr` above `OAI 30d 100%`.
- Grok probe: `used=802`, `monthlyLimit=0`, period Oct 1 – Nov 1 — matches bar.
- OpenAI probe: wham/usage → free plan, 30d window, `used_percent: 100`,
  `limit_reached: true`, resets ~Nov 8 — the full red bar is genuine.
- The OAI probe decrypts `auth_*` DPAPI blobs (no entropy; `taskbar-ai-quota`
  is just the description label) and prints no tokens.

## Gotchas hit / fixed

- `grok-probe.ps1` logged the token via string interpolation in
  `"($null -ne $token)"` — fixed to a pre-computed boolean (gen-2 scrub of the
  output file still held).
- T3 write tools can't touch `C:\ProgramData`; all engine-side steps ran
  elevated with exact-literal scripts.

## Artifacts

- Build dir: `work\ai-quota-grok-20261016\` (build.ps1, install.ps1, DLL)
- Probes: `t3-handoff\scratch\grok-probe.ps1`, `oai-probe.ps1` (+ out files)
- Rollback: `backups\2026-10-16-ai-quota-grok\` + receipt JSON in reports.

## Gen 3 (mcp:77a602be) — Grok bar REMOVED, ~4:00–4:50 AM

The user rejected the 1.8.2.0 Grok bar (gray + "802cr" reads as broken, label
misaligned) and asked: show a REAL limit, or remove Grok. Research proved no
real limit can be shown, triple-proven:

- **Binary mine**: `~\.grok\bin\grok.exe` (169,345,536 B) contains only 17
  unique `/v1/` paths, ZERO usage/limit/quota endpoints
  (`t3-handoff\scratch\grok-endpoints-out.txt`).
- **Live probes**: `/v1/usage`, `/v1/rate-limits`, `/v1/limits`, `/v1/api-key`,
  `/v1/team` → 404; `/v1/user` → profile only, zero limit fields
  (`grok-user-out.txt`).
- **Billing**: `/v1/billing` `monthlyLimit {val:0}` (no published cap),
  `?format=credits` weekly, `onDemandCap 0`. No denominator → no honest %.

Removal applied via the mod's own hide mechanism:

- First attempt appended grok's hash to the `hiddenAccounts` REG_SZ — the
  running mod IGNORED it: that value is only read by the legacy import path
  (source lines 6953–6966, 7014–7024). The live settings blob `settings_v1`
  carries per-account `"hidden"` booleans (line 6797) and is what runs.
- `work\ai-quota-grok-20261016\hide-grok-v2.ps1` (elevated): exported
  `mods-writable-key-pre-grok-hide-v2.reg`, set grok `"hidden":true` in
  settings_v1 (len 1398→1397, sentinel updated), bumped SettingsChangeTime,
  toggled Disabled 1→0. The mod has NO `Wh_ModSettingsChanged` export, so a
  marker bump alone cannot repaint — a per-mod reload is required. No Explorer
  restart (`windhawk.exe -restart` stays banned).
- The hide-grok.ps1 BigInteger `x16` sign-padding bug (17-char hashes) was
  fixed first (last-16-chars); its CC 2 proof then passed exactly.
- A fullscreen game (NativeTweaks overlay) covered the taskbar during two mid-
  verification captures — left it alone; verified non-visually meanwhile
  (DLL mapped in explorer PID 9708 via `tasklist /m`) and visually after the
  game closed.

**Result (taskbar-fix1.png + bars-fix1-zoom.png)**: Grok row GONE; column 1
shows only `OAI 30d 100%` (full red — correct: wham/usage free plan, 30d
window, used_percent 100, resets ~Sat Nov 8); CC 1 and Go+ unchanged. The
alignment complaint is resolved by removal (OAI now matches CC 1 / Go+ layout).

Rollback: import `mods-writable-key-pre-grok-hide-v2.reg` (or set grok
`hidden:false` + `settings_v1_len=1398`), bump SettingsChangeTime, toggle
Disabled 1→0. Token stays stored; Grok can be re-enabled from the mod UI.
