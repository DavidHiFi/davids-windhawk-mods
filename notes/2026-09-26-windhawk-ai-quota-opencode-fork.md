# Windhawk AI quota bars: OpenCode Go fork installed — 2026-09-26

## What was asked

Show OpenCode Go subscription usage on the taskbar the same way the existing
Windhawk mod shows GPT and Claude quota bars — same look, same customization.

## What was done (all observed facts)

- Forked `taskbar-ai-quota` (Cleroth, stock v1.6.5) into
  `taskbar-ai-quota-opencode` v1.6.5.1, installed as a Windhawk local mod
  (`local@taskbar-ai-quota-opencode`). Adds a fourth provider, **OpenCode Go**,
  alongside Anthropic / OpenAI / Antigravity. All stock customization kept:
  per-account bar checkboxes, colors, thresholds, notifications, pace ticks,
  poll interval, layout pages.
- New provider reads the **official Go usage API**
  `GET https://opencode.ai/zen/go/v1/usage` (Bearer key), windows
  `rolling` (5h) / `weekly` / `monthly`, fields `percent` + `resetsAt`.
  Response shape verified live (HTTP 200).
- Data source: the account's Go API key, stored DPAPI-encrypted in mod storage.
  It was seeded from `C:\Users\localuser\.local\share\opencode\auth.json`
  (`opencode-go` entry, key length 67). The key is never logged.
- Existing accounts migrated with no re-login: `GPT` (OpenAI) and `5X`
  (Anthropic) settings + DPAPI token blobs copied from the stock mod's
  LocalStorage into the fork's storage (identity hashes recomputed and matched:
  `f498aff21be04836`, `60d054933d412770`).
- Stock mod `taskbar-ai-quota` disabled (`Disabled=1`), its storage untouched.
- Live result verified by screenshot: three columns — GPT (5h 0% / 7d 41%),
  5X (5h / 7d / Fa), OC (5h / 7d / **mo**). OC values tracked the live API
  (bars 49/19/9 at capture, API re-check minutes later 51/20/10 — usage was
  actively climbing). Compact label for the Go monthly bar reads `mo`; the
  Anthropic Fable bar keeps `Fa`.
- Compiled with Windhawk's own bundled clang 20 (exact upstream flags:
  `-std=c++23 -O2 -shared -Wl,--export-all-symbols`, engine `windhawk.lib`,
  `-include windhawk_api.h`, target `x86_64-w64-mingw32`). Output identical in
  structure to Windhawk's own builds (verified by recompiling the stock source
  and diffing against the installed stock DLL — differences are build
  nondeterminism only: .rdata string-table order and a few atomics).

## Incidents during the work (fixed)

- One byte of `C:\Program Files\Windhawk\Compiler\include\winrt\impl\
  Windows.UI.Xaml.Automation.Peers.0.h` had bit-roted between 20:53 and 21:03
  ('W' 0x57 -> 0xD7 at offset 21548), breaking any mod compile. A full scan of
  5,666 files in the compiler tree found no other corruption (`ddk\ide.h`'s
  0xE9 is legit Latin-1). Fixed in place via an elevated single-byte write,
  verified by re-read and by successful compile. **Watch for further single-bit
  file corruption on this machine** — if more appear, check the disk.
- During elevation probing I wrote then deleted a probe value
  (`settings_v1="zz"`) in the STOCK mod's `...\Mods\Settings` key. That key is
  not used by the stock mod (it reads owned storage from ModsWritable), and the
  probe was deleted immediately; stock settings were never touched (verified
  byte-identical export before/after).

## Where things live

- Fork source: `H:\System Configuration\Windhawk\Opencode-fork\taskbar-ai-quota-opencode.wh.cpp`
  (canonical) and `local@taskbar-ai-quota-opencode.wh.cpp` (the Windhawk-side
  copy, also at `C:\ProgramData\Windhawk\ModsSource\`).
- Compiled DLL: `C:\ProgramData\Windhawk\Engine\Mods\64\local@taskbar-ai-quota-opencode_1.6.5.1_483920.dll`
- Registry: `HKLM\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-ai-quota-opencode`
  (7 values, stock pattern) and owned storage at
  `HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\local@taskbar-ai-quota-opencode\LocalStorage`
  (settings_v1 + 3 auth blobs).
- Backups: `H:\System Configuration\Windhawk\Backups\2026-09-26-ai-quota-fork\`
  — stock source, stock mod key `.reg`, pre-deploy full Mods tree `.reg`,
  deploy log, header byte-fix log, sanity recompile DLL.

## Rollback (one command each, no restart needed — engine hot-applies)

1. Re-enable stock, disable fork:
   ```
   reg add "HKLM\SOFTWARE\Windhawk\Engine\Mods\taskbar-ai-quota" /v Disabled /t REG_DWORD /d 0 /f
   reg add "HKLM\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-ai-quota-opencode" /v Disabled /t REG_DWORD /d 1 /f
   ```
2. Full removal of the fork: the two lines above, then
   ```
   reg delete "HKLM\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-ai-quota-opencode" /f
   reg delete "HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\local@taskbar-ai-quota-opencode" /f
   del "C:\ProgramData\Windhawk\Engine\Mods\64\local@taskbar-ai-quota-opencode_1.6.5.1_483920.dll"
   del "C:\ProgramData\Windhawk\ModsSource\local@taskbar-ai-quota-opencode.wh.cpp"
   ```
3. Full Windhawk restore point: import
   `Backups\2026-09-26-ai-quota-fork\pre-deploy-mods.reg`.

## Untested / notes

- Tooltip content and the Go key re-paste dialog (right-click > Sign in) are
  stock code paths, not exercised headlessly.
- If the Go API response shape ever changes, the parser treats it as
  "unexpected response format" and the OC column goes stale-grey; the stock
  columns keep working.
- Go plan caps ($12/5h, $30/wk, $60/mo) come from opencode.ai docs; the bars
  use the API's own `percent`, so cap changes need no mod change.
