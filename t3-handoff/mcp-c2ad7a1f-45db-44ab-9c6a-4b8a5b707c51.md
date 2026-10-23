# Handoff — 2026-10-15 ~23:5x — T3 Code: duplicate Grok provider + permanent OpenCode fix (continuation of f6a8d385)

(Requested filename was `mcp:c2ad7a1f-...md`; `:` is invalid on Windows, so this file is `mcp-c2ad7a1f-45db-44ab-9c6a-4b8a5b707c51.md`.)

## Objective (from user, this thread)

1. **Duplicate "Grok" row** in T3 Code Settings → Providers (two identical "Grok — Available" rows). Remove the duplicate and stop it recurring.
2. **OpenCode provider "Needs attention"** after every T3 Code update — make the fix permanent. User banned the manual disable/re-enable toggle.

## Environment (unchanged from parent brief f6a8d385 — read it too)

- T3 Code Nightly `0.0.46-nightly.20261015.3158`, server pid 40544, port 3773. Install `C:\Users\localuser\AppData\Local\Programs\t3code` (per-user). User data `C:\Users\localuser\.t3\userdata` (settings.json), caches `C:\Users\localuser\.t3\caches` (NOT userdata\caches).
- We run INSIDE T3 Code — never kill/restart T3. Renderer/web-UI chunks live inside `server.asar` (apps\server\dist\client\assets\*.js); the desktop app is thin.
- Halo's Sparks: ≤2 model requests at a time (currently busy: run ONE at a time).
- DSH sandbox: workspace writes only under `H:\Windhawk Configuration`; anything else needs escalation — `workspace-write` was NOT enough for `C:\Users\localuser\...` writes, use `danger-full-access` with justification. Scheduled Task queries blocked in sandbox; use `danger-full-access` for Get-ScheduledTask/Register-ScheduledTask.

## ISSUE 2 (OpenCode): DONE — nothing left for the agent

- The `T3-OpenCodeStartup-KeepAlive` scheduled task fired on schedule at **23:10:25**, wrote backup `server.asar.bak-pre-opencode-startup-20261015-2310`, applied all three 9 s budgets, verified byte-reads, logged to `H:\System Configuration\reports\2026-10-15-opencode-startup-keepalive.log`.
- Independent re-audit (`H:\System Configuration\scripts\2026-10-15-t3-opencode-startup-budget.ps1`): all three sites "already patched (9 s)"; size 114,863,909 unchanged. My own `-Apply` was a no-op (correct behavior).
- Interval TIGHTENED 4 h → 30 min: script now takes `-IntervalMinutes` (default 240) and success message reflects it; task re-registered with `-IntervalMinutes 30`; verified NextRunTime 23:15:28, State Ready, LastTaskResult 0.
- **User action needed (tell them): restart T3 Code once** for the 9 s budgets to take effect (or toggle OpenCode once for this session only). After that, cold starts are fixed permanently and updates self-heal within 30 min.
- Receipt/note: `H:\System Configuration\notes\2026-10-15-t3-opencode-cold-start-auth-error.md` — successor should append a short 23:10 section (update reverted + keepalive self-healed at 23:10:25, interval now 30 min) per convention. Not yet written.

## ISSUE 1 (duplicate Grok): ROOT CAUSE FOUND, fix chosen, NOT yet applied

### Root cause (proven by reading the shipped chunks)

- Renderer settings page = `server.asar → apps/server/dist/client/assets/settings.providers-Chu9EOJp.js`, function `Gi`. Rows (`V`) are built from:
  1. For each driver def in `Ai` (= `Mt.definitions.map(e=>({provider:e.driverKind,hasDefaultInstance:e.hasDefaultInstance!==!1}))`): push `{instanceId:n, instance:r2, driver:t, isDefault:!0}` where `n=j(t)` (default instance id = driverKind string), `r2=C.providerInstances?.[n]`, IF `(hasDefaultInstance || r2!==void 0) && (t==='codex' || t==='claudeAgent' || a || d(i) || n===g)`.
  2. Then push every configured instance of that driver except the default id (`B.get(t)` where B groups settings providerInstances by driver).
- The driver registry (`ChatGptUsageButton-CEHGytQk.js`, export `S as Mt`) defines BOTH a **legacy `grok` driver** (`he=O({driverKind:C.make(\`grok\`),label:\`Grok\`,settingsSchema:me,icon:{…}})`, no `hasDefaultInstance` → defaults true) AND `acpRegistry` (hasDefaultInstance:!1).
- settings.json has ONE instance id `grok` with driver `acpRegistry`. So the loop pushes it TWICE: (a) legacy grok driver claims default instanceId 'grok', `r2` exists → pushed with the real instance data; (b) acpRegistry inner loop pushes `grok` (t2!==n). Both rows show displayName "Grok" + the SAME live provider status ("Available" from `De.get('grok')`). Exactly the screenshot.
- `d` = `Kl` from utils chunk = `XH`: enabled check = `e.enabled===!1||GH(e.config)===!1 ? !1 : e.enabled ?? t ?? YH(e.driver)`; `YH(x)=!KH.has(x)`; `KH=new Set(['cursor','grok','muse','pi','opencode','antigravity'])`. So `d({driver:'grok'})` = false → NO phantom row for an unconfigured legacy grok driver. This makes the chosen fix work (see below).
- Server-side is definitively deduped (providerRegistry keyed Map by instanceId; `loadServerConfig`/`subscribeServerConfig` use `providerRegistry.getProviders`). Composer model picker uses the live provider list — also one grok. Only the Settings page duplicates.
- Verified one-grok in `userdata\settings.json` (10 instances) and `caches\grok.json` (models: grok-4.7 "Grok 4.7", default "Default", grok-build "Grok Build").

### Chosen fix (data-side, update-proof; NOT yet applied — THIS IS THE IN-FLIGHT STEP)

**Rename the settings instance `grok` → `grok_acp`** in `C:\Users\localuser\.t3\userdata\settings.json` and update its favorite reference:

1. Backup `settings.json` → e.g. `H:\System Configuration\backups\2026-10-15-t3-grok-duplicate\settings.json.before-grok-rename` (also copy client-settings.json for completeness). Read settings.json before editing (tool policy).
2. In settings.json: rename key `providerInstances.grok` → `grok_acp` (keep all contents: driver acpRegistry, displayName "Grok", commandPath node.exe + `C:\Users\localuser\AppData\Roaming\npm\node_modules\@xai-official\grok\bin\grok agent stdio`). Update the `favorites` entry `{"provider":"grok","model":"grok-4.7"}` → `"provider":"grok_acp"`.
3. client-settings.json favorites: verified NO grok entries — no change needed.
4. model-manifest.json: only 1 `"grok"` occurrence, keyed by DRIVER (compatibility list) — no change.
5. Leave `caches\grok.json` (stale orphan cache; server writes `grok_acp.json` on next sync). Optionally delete it after verifying the new cache appears.
6. Hot-reload: the server picked up direct settings.json edits in prior sessions (2026-10-13 did exactly this); verify by re-reading settings + confirming the provider list updates. If not hot-reloaded, it applies on next T3 restart.
7. Verification: settings.json parses, exactly one grok-keyed instance (grok_acp), favorite updated; `caches\grok_acp.json` appears (or orchestrator_capabilities still lists grok); user confirms Settings → Providers shows ONE "Grok — Available" row.
8. Write receipt JSON + note (`H:\System Configuration\reports\` + `notes\2026-10-15-t3-grok-duplicate-provider.md`) per convention. History: `H:\System Configuration\backups\2026-10-13-grok-popups\` — instance driver was 'grok' → migrated to 'acpRegistry' + local command to avoid detached-process console popups (do NOT switch the driver back to 'grok').

**Rejected alternative** (kept in case rename is objected to): same-length asar patch — insert `,hasDefaultInstance:!1` (23 B) after `label:\`Grok\`` in the legacy grok driver def inside the `ChatGptUsageButton-CEHGytQk.js` chunk of server.asar, compensating −23 B inside the same file's (unused-after-fix) SVG path digits, keeping total asar size identical; would need the keepalive task to re-apply after updates. Rename has no such maintenance burden.

### Rename side effects (acceptable)

- Old threads referencing provider 'grok' show the graceful "This provider instance is no longer available on this device." (string exists in Gi for exactly this). User re-picks grok_acp there.
- providerModelPreferences for 'grok' (hidden models/order) — none exist in settings.json. Favorite is updated in the same edit.

## Gotchas / tooling notes for the successor

- `H:\Windhawk Configuration\t3-handoff\scratch\` has working tools from this session: `asar-extract.mjs` (usage: `node asar-extract.mjs <archive> <list|extract> <substrFilter> [outDir]` — pure-node asar reader), `ctx.mjs` (context grep), plus extracted chunks in `scratch\web\` (client assets) and `scratch\server\` (binCli-D-vPGZz9.mjs, AcpMcpStdioBridge-RtPSYxmj.mjs).
- Minified-chunk reading: use `[System.IO.File]::ReadAllText` + Substring windows; regex for import alias resolution; export lists map `internal as exported` (import `Kl as d` ⇒ find `X as Kl` in the utils export list, then the `X` definition).
- Editing files outside the workspace (settings.json, System Configuration) needs `sandbox_permissions: danger-full-access` with a one-sentence justification (workspace-write was denied even for the backup Copy-Item).
- `server.asar.bak-pre-slowrpc-20261015-2153` and the `15e3→60e3` change = slow-rpc keepalive doing its job, leave alone. No sqlite client; statev2.sqlite is 31 GB — avoid.
- Scheduled task `T3-OpenCodeStartup-KeepAlive` is VERIFIED alive; manage via `H:\System Configuration\scripts\2026-10-15-t3-opencode-startup-keepalive-task.ps1 -Status | -Uninstall` (needs danger-full-access in this sandbox).

## Verification status

- OpenCode patch applied + verified (9 s × 3 sites, size unchanged); keepalive task verified alive, 30 min interval verified via NextRunTime.
- Grok root cause: proven from shipped chunks (no guessing left).
- ~~Grok fix: NOT applied~~ **RESOLVED 2026-10-16 ~00:40** — rename `grok` → `grok_acp` applied in `C:\Users\localuser\.t3\userdata\settings.json` (favorite repointed; backup `H:\System Configuration\backups\2026-10-15-t3-grok-duplicate\` with settings sha256 76C437FF…). Server hot-reloaded: `caches\grok_acp.json` appeared (status ready, models grok-4.7 + default) and `grok.json` became the disabled legacy-driver fallback (normal, like `pi.json`). ACP probe of the CLI (v1.0.52): ONE agent, ONE model, auth healthy — the duplicate was never the CLI. Records: note `H:\System Configuration\notes\2026-10-15-t3-grok-duplicate-provider.md`, receipt `H:\System Configuration\reports\2026-10-16-t3-grok-duplicate-fix\receipt.json`. OpenCode note's 23:10 self-heal section appended.
- Remaining user action only: ONE T3 Code restart to activate the 9 s OpenCode budgets (or toggle OpenCode once). No agent work left.
- No background jobs running.
