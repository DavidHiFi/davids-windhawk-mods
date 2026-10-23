# 2026-10-18 taskbar AI quota: Grok alignment and Go+ key (pass 2)

Status: Grok alignment and label fixed and verified. Go+ usage is blocked until a fresh OpenCode Go key is entered. Only the account owner can create that key.

## Done and verified
- Installed `local@taskbar-ai-quota-plus` 1.8.2.1 (revision 1). Explorer has the DLL mapped (`tasklist /m`). Registry readback matches and the DLL and source hashes match. Log: `work\ai-quota-fix-20261018\install-1821-log.txt` (RESULT=OK).
- Grok alignment: the compact stack now gives every row the same label width, so the Grok bar track starts at the same x as OAI. Evidence: `work\ai-quota-fix-20261018\bars-1821-6x.png` and `bars-1821-poll2-6x.png`.
- Grok amount label: `1,055 used` replaces `1055cr`. The number is the xAI credit count used this period. xAI publishes no cap for the free plan, so no percentage can be shown honestly.
- Rollback: `backups\2026-10-18-ai-quota-fix\mod-key-pre-1821.reg` and `mods-writable-pre-1821.reg`. Set `LibraryFileName` back to `local@taskbar-ai-quota-plus_1.8.2.0_1.dll` and `Version` to `1.8.2.0`, and copy `backups\2026-10-18-ai-quota-fix\original.wh.cpp` back to `ModsSource`.

## Not done: Go+ usage
- OpenCode returns 401 for every key on this machine: the `opencode-go` key in `auth.json`, the key the mod had stored, and the OpenRouter key. `/zen/go/v1/usage` and `/zen/go/v1/models` both reject them. The Go key is revoked or expired.
- The `sk-or-v1-` key is an OpenRouter key, not an OpenCode Go key. The previous pass put it in the mod settings. Reverted to the `oc-len:67` placeholder.
- To finish: open the opencode.ai console, create an API key, then right-click the Go+ slot on the taskbar, choose Sign in, and paste the key. The mod will fetch on its next poll (every 10 minutes).

## Corrections to the earlier receipt
- The earlier receipt said Grok was set to `hidden:true`. That was wrong. The settings blob has Grok `"hidden":false`. The check matched CC 2's `"hidden":true` instead.
- The earlier pass stored the OpenRouter key as the Go key. This pass replaced it: the token store now holds the original value again, verified by readback.
- This pass first wrote a token under a wrong name (leading zero from the hash). That stray value was deleted.

## Mechanics (for the next person)
- The mod's account id is FNV-1a 64 over the UTF-16 bytes of `provider` + LF + `label`, printed as 16 hex digits with no leading zero padding.
- Tokens live in `ModsWritable\...\LocalStorage` as `auth_<id>`, base64 of a DPAPI blob that holds JSON with `access`. `Go+` = `auth_97d7a97e22a96a73`.
- The fetch reads the token store, not the `opencodeKey` setting.
- Explorer started at 4:37:55 PM, before this pass installed anything. The cause is not confirmed.
