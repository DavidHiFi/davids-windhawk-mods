# GitHub Desktop repository refresh

Date: 2026-09-28
Thread: ghd-refresh-2 (replacement for the wedged "Refresh GitHub Desktop Repositories" thread, 0a298bd2)
App: GitHub Desktop 3.6.6 (`C:\Users\localuser\AppData\Local\GitHubDesktop\app-3.6.6`), account DavidHiFi

## Outcome

GitHub Desktop now tracks all 20 repositories (was 12). Added the 8 that were missing:

| Repo | Path registered |
|---|---|
| millennium-stuff | `C:\Users\localuser\Documents\GitHub\millennium-stuff` |
| StaffTag-UserPlugin | `C:\Users\localuser\Documents\GitHub\StaffTag-UserPlugin` |
| FakeVoice-UserPlugin | `C:\Users\localuser\Documents\GitHub\FakeVoice-UserPlugin` |
| better-lyrics-sync | `H:\System Configuration\packages\better-lyrics-sync` |
| CustomStreamQuality-UserPlugin | `H:\System Configuration\packages\CustomStreamQuality-UserPlugin` |
| Davids-Vencord-Plugins | `H:\System Configuration\packages\Davids-Vencord-Plugins` |
| davids-windhawk-mods | `H:\Windhawk Configuration\davids-windhawk-mods` |
| freedictate | `H:\System Configuration\packages\FreeDictate-Repo` |

Path decisions (the "canonical clone" question):

- `davids-windhawk-mods`: `H:\System Configuration\davids-windhawk-mods` is a junction to
  `H:\Windhawk Configuration\davids-windhawk-mods` (verified with `Get-Item LinkType=Junction`),
  so both listed clones are one working tree. Registered the real path, not the junction,
  and did not disturb the Windhawk-side workspace.
- `freedictate`: the clone is `H:\System Configuration\packages\FreeDictate-Repo`
  (`scripts\FreeDictate` is the live non-repo install). The app displays it as `freedictate`.

## Verification

- Live renderer state after the add: `appStore.getState().repositories` = 20 paths, all correct.
- Screenshot of the real UI with all 20 in the sidebar: `reports\2026-09-28-github-desktop-sidebar.png`.
- Persistence: quit the app fully, started it normally (no debug flags), and its own log shows
  `[AppStore] loading 20 repositories from store` (16:39:38 local) on a fresh start.

## How it was done (programmatic, no UI automation)

Driven through GitHub Desktop's own React dispatcher over the Chrome DevTools Protocol:

1. App was already closed. Backed up userData first (see below).
2. Launched `app-3.6.6\GitHubDesktop.exe` with `--remote-debugging-port=9222` (a Chromium
   switch; the app does not override it — verified in the 3.6.6 source, `release-3.6.6` tag).
3. Reached the React root from the page (`_reactRootContainer` → fiber walk) and called
   `dispatcher.addRepositories([...8 paths])` — the exact call the app's own multi-folder
   drag-and-drop handler uses (`app/src/ui/app.tsx` `handleDragAndDrop`,
   `app/src/ui/dispatcher/dispatcher.ts`). The app validated each path with git, linked the
   GitHub metadata, and wrote the repository records to its store itself.
4. Quit cleanly with CDP `Browser.close`; relaunched normally.

Routes ruled out:

- `x-github-client://openRepo/...`: in `app/src/lib/parse-app-url.ts` there is no `openLocalRepo`
  action. It only accepts remote URLs and would trigger a clone, never attach an existing local
  clone. This is why the protocol handler "reacted" earlier without adding anything.
- `--cli-open <path>`: a supported launch argument, but for an untracked repo it only opens the
  in-app Add Repository dialog. Unnecessary once the dispatcher was reachable.
- UI driving (UIA / PrintWindow / mouse coordinates): the dead end the previous thread wedged on.
  Not used at all.

## Traps worth remembering

- **Any Electron app launched from a T3 session needs `ELECTRON_RUN_AS_NODE` removed.** The T3
  sandbox exports `ELECTRON_RUN_AS_NODE=1`, so GitHub Desktop started and exited instantly with
  no log lines. Also set `APPDATA=C:\Users\localuser\AppData\Roaming` (T3 redirects it to the
  sandbox; the app then gets a bogus profile).
- `CloseMainWindow()` and `taskkill` (without `/F`) did not close GitHub Desktop. CDP
  `Browser.close` shut it down cleanly.
- The CDP helper is generic: `node scripts\Steam-CdpEval.mjs --port 9222 --match GitHubDesktop --expr "..."`.
- Sidebar vs store: the app shows repositories from its store; entries whose path disappeared
  stay until removed. The stale `D:\GitHub\zm_qol` entry was already gone before this pass.

## Repository update pass (all 20 tracked)

Raw log: `reports\2026-09-28-github-desktop-repo-update.txt`
Reusable script: `scripts\Update-GitHubDesktopTrackedRepos.ps1` (report-only by default;
`-Apply` fast-forwards clean, behind repos).

Result: all 20 fetched. 18 were already current.

- `millennium-stuff`: was 1 behind, fast-forwarded `7c2e9fb` → `682420a` (README download links).
- `davids-windhawk-mods`: skipped, 1 dirty file (active Windhawk work in another thread; left
  untouched, as the workspace isolation rule requires).
- No diverged repos. Submodules were not updated (Davids-Vencord-Plugins carries plugin
  submodules); a fast-forward can move submodule pointers, so run
  `git submodule update --init --recursive` there if it matters.

## Rollback

1. Quit GitHub Desktop (CDP `Browser.close`, or if no debug port: close it from its UI).
2. Copy `backups\2026-09-28\github-desktop\{IndexedDB, Local Storage, Local State, Preferences, window-state.json}`
   back over `C:\Users\localuser\AppData\Roaming\GitHub Desktop`.
3. Start GitHub Desktop.

The fast-forward of `millennium-stuff` is undone with `git -C C:\Users\localuser\Documents\GitHub\millennium-stuff reset --hard 7c2e9fb`
(only if that commit must come back; no local edits were touched).

## Update 2026-09-29

All 23 account repos are now tracked (this note's pass covered 20): MochaCord,
Ditto and windhawk-mods were added. Details:
`2026-09-29-github-desktop-restore-all-repos.md`.
