# GitHub Desktop: all 23 repositories restored

Date: 2026-09-29. Thread: restore GitHub Desktop repository files.
Follows `2026-09-28-github-desktop-refresh.md` (that pass synced 20 repos).

## Why 3 repos were missing

The account has 23 repos (`gh repo list`); Desktop tracked 20. The three
missing ones were all created on 2026-09-28, after the sync pass ran:

| Repo | Clone used for tracking |
|---|---|
| MochaCord | `C:\Users\localuser\Documents\MochaCord` (existing) |
| Ditto | `H:\System Configuration\work\ditto-rice` (existing; origin DavidHiFi/Ditto) |
| windhawk-mods | `C:\Users\localuser\Documents\GitHub\windhawk-mods` (cloned today, full, via `gh repo clone`) |

## What was done

- Cloned `DavidHiFi/windhawk-mods` (fork of ramensoftware/windhawk-mods) with
  `gh repo clone` so Git Credential Manager never prompts.
- Quit GitHub Desktop, relaunched with
  `app-3.6.6\GitHubDesktop.exe --remote-debugging-port=9223`
  (`ELECTRON_RUN_AS_NODE` removed, real `APPDATA`/`LOCALAPPDATA` set;
  Discord already holds 9222, so 9223 is the free port).
- React fiber walk from `#desktop-app-container` (`_reactRootContainer`) to the
  app's own `dispatcher` and `appStore`, then
  `dispatcher.addRepositories([...3 paths])` → store went 20 → 23.
- Evidence: `reports\2026-09-29\github-desktop-23-repos.png` (sidebar with all
  23, incl. Ditto / MochaCord / windhawk-mods) and
  `reports\2026-09-29\github-desktop-t6qol-history.png` (History view showing a
  commit's changed files — Desktop has no file tree; files live on disk or in
  History).
- Clean quit via CDP `Browser.close`; normal relaunch; log:
  `[AppStore] loading 23 repositories from store` (13:44:01Z). Persistence proven.
- UI note: the repository sidebar toggles from the "Current repository" header;
  a fresh launch may start with it collapsed.

## Account flag context (not caused by this work)

- DavidHiFi is GitHub-flagged and hidden from the public (anonymous
  `api.github.com/users/DavidHiFi` and `github.com/DavidHiFi` = 404, still true
  at 21:30 local 2026-09-29). Appeal submitted 13:13Z; nothing local can lift it.
- The GitHub Desktop sync work is local-only (adds existing clones to the app's
  list, runs git fetch). It made no GitHub mutations and is not the cause.
  Forum download/version badges stay broken until GitHub clears the flag.

## Rollback

- Remove the three repos in the app (right-click → Remove). That is the entire
  change; no GitHub state was modified.
