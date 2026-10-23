# Taskbar AI Quota: Grok + Antigravity accounts added (v1.6.5.1 → 1.7.0.0)

Date: 2026-10-11 evening. Continues reference T3 thread `75292a9b-2989-4276-916e-9b56c5863709`
(the install was interrupted there twice on installer bugs; both were fixed and the final run
succeeded from this thread).

## Request

Show all six AI quota accounts on the Windhawk `taskbar-ai-quota-opencode` taskbar mod:
OpenAI, Claude Code 1, Claude Code 2, OpenCode Go (already present) **plus Grok and Google
Antigravity**.

## What changed

| Item | Original value | New value |
|---|---|---|
| Mod version (HKLM\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-ai-quota-opencode `Version`) | `1.6.5.1` | `1.7.0.0` |
| `LibraryFileName` | `local@taskbar-ai-quota-opencode_1.6.5.1_483920.dll` | `local@taskbar-ai-quota-opencode_1.7.0.0_1_64.dll` |
| `SettingsChangeTime` | (old) | set to install time → engine hot-reloaded the mod, no explorer restart |
| LocalStorage `settings_v1` | 4 accounts (1247 chars) | 6 accounts (1555 chars): appended `grok`/"Grok" (weekly bar) and `antigravity`/"AG" (5h+weekly bars) |
| DLL in `C:\ProgramData\Windhawk\Engine\Mods\64` | 1.6.5.1 only | 1.6.5.1 (kept) + 1.7.0.0 |
| `C:\ProgramData\Windhawk\ModsSource\local@taskbar-ai-quota-opencode.wh.cpp` | 1.6.5.1 source | 1.7.0.0 source (fork copy synced) |

The existing 4 accounts were preserved byte-identically: the two new account objects were
inserted into the JSON array by string surgery before the `],"monitorMode"` marker, validated
with `ConvertFrom-Json`, and the `settings_v1_len` mirror value updated. Nothing else in the
JSON was touched. Go's API key field stayed intact.

Build artifacts: `H:\Windhawk Configuration\build-2026-10-11-ai-quota\` (source fork,
`build.ps1`, `install.ps1`, signed-off DLL SHA256
`3F8895BFC0FE9003032B2E961C7DF6949B6E2A0DCF6A38870DDAD5ABBFE100A5`).

## Test results (screenshots in %TEMP% during session, cropped from `Shell_TrayWnd`)

- 20:54 install completed `INSTALL OK`; verify settings/modkey/dll all true.
- 20:58–21:01 taskbar renders **6** account groups: OAI, CC 1, CC 2, Go, Grok, AG.
- Grok fetches live via `%USERPROFILE%\.grok\auth.json` OIDC credential →
  `cli-chat-proxy.grok.com`; shows `wk 0%` (valid response, no process needed).
- Antigravity bars are empty **by design until an Antigravity app/CLI is running** — the
  provider discovers the local Antigravity server (IDE language server / `agy.exe` / ACP) and
  reports "Antigravity not running" otherwise. No such process was running at test time.
- No regression: compared against the user's own 18:24 screenshot from the reference thread —
  CC 2 was already showing no data (empty 5h/7d/Fa bars) before the change. CC 1 (identical
  provider code path) fetches fine, so the Anthropic path is healthy; CC 2 is an
  account-level auth/data issue that predates this change.

## Rollback

1. Elevated PowerShell.
2. `reg import "H:\Windhawk Configuration\backups\2026-10-11-ai-quota-6-accounts\writable-key-before.reg"`
   (restores 4-account `settings_v1`), then `reg import ...\mods-key-before.reg`
   (restores Version 1.6.5.1 + old LibraryFileName).
3. Delete `C:\ProgramData\Windhawk\Engine\Mods\64\local@taskbar-ai-quota-opencode_1.7.0.0_1_64.dll`.
4. Copy `...\backups\2026-10-11-ai-quota-6-accounts\original-modssource-1.6.5.1.wh.cpp` back to
   `C:\ProgramData\Windhawk\ModsSource\local@taskbar-ai-quota-opencode.wh.cpp`.
5. The engine re-applies 1.6.5.1 on the settings change; pre-change registry exports and the
   old DLL copy are in the same backup folder.

## Open items

- CC 2 has no data — expected: the Max 5x subscription starts in ~2 weeks. The bars should
  populate on their own once the account is active (same provider path as CC 1, which works).
  If it is still empty after activation, re-sign-in from the bars' right-click menu is the
  next step.

## Antigravity deep-dive (21:30–22:10 same evening)

Live-probed the whole chain while an idle `agy` CLI session was running:

- Mod discovery works: the Windhawk mod found the agy language server and probed it once per
  minute (visible as TLS handshake errors in agy's own log, one per poll).
- The language server hosts the quota endpoint on two loopback ports
  (`server.go:649/657`): one HTTPS "(gRPC)" port and one plain-HTTP port. Verified by
  replaying the mod's exact Connect-JSON request.
- The HTTPS port demands a **client certificate** (Schannel: "No credentials are available in
  the security package") — WinHTTP, which the mod uses, cannot connect to it.
- The plain-HTTP port answers but returns `401 unauthenticated: missing/invalid CSRF token`;
  the server validates the token value (a fake token is rejected).
- A plain `agy` CLI session does not publish its CSRF token on its command line, so the mod
  has nothing to authenticate with → AG bars stay empty for headless `agy` sessions. This is
  an agy-behaviour limit, not an install fault.
- The supported data sources are processes that carry `--csrf_token` on their command line:
  the Antigravity IDE's language server, and per the fork's own notes T3's Antigravity ACP
  harness (`agy_acp_server.exe` / `localharness_external.exe` in
  `~\.t3\tools\antigravity-acp\`), which is how this user actually runs Antigravity. The
  harness could not be end-to-end tested tonight because the T3 Code MCP endpoint began
  returning HTTP 401 mid-session (blocked the test-thread launch); the ACP binary also
  refuses to unpack under the agent sandbox.

**Practical upshot:** the AG bars fill automatically whenever the user's normal Antigravity
usage is active (T3 antigravity provider session). They stay gray otherwise — that is the
mod's designed staleness (AG data expires 2 minutes after the last successful fetch). If the
bars remain gray during a real T3 antigravity session, the next step is checking whether the
harness passes `--csrf_token` to its language server child.

## Antigravity status probe (23:22 next evening)

- Launched a real T3 scratch thread on the antigravity provider
  (`mcp:21731016-56c7-4356-a18c-e89cd79ca755`). The provider turn returned in ~3 s with
  **"Usage Limit Reached — limit will reset in 6 days, 18 hours"**: the free-tier weekly AG
  quota was exhausted at 23:22 on 2026-10-11, resetting ~2026-10-18 17:00 local.
- The harness lived only ~3 s, too short for the mod's 60 s poll to catch it — the AG-bar
  behaviour during a real (long) antigravity session remains the one unverified link.
- Re-verify after the quota reset, or during the first real antigravity session after it:
  bars should show ~100% used with the reset time in the tooltip.

## Deferred item

- T3 Code MCP returned HTTP 401 to this session earlier in the evening (blocked tool calls);
  recovered by 23:2x. If it recurs, restarting T3 Code clears it.
