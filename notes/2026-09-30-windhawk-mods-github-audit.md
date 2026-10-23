# All local Windhawk mods audited against GitHub, made catalog-ready

2026-09-30. Status: done; upstream PRs pending maintainer review.

## What the audit found

Five mod sources of ours existed on this machine. All were already on GitHub
in some form; what was missing was consistent, unattributed-look metadata and,
for three of them, any catalog presence at all.

| Mod | Where it lived | On GitHub before | Catalog before |
| --- | --- | --- | --- |
| local@translucent-flyouts 0.6.1 | ModsSource + repo | yes (repo, v1.1.0) | PR #5785 pending |
| local@alt-snap-drag 1.2.2 | ModsSource + repo | yes (repo) | no |
| local@taskbar-ai-quota-opencode 1.6.5.1 | ModsSource + repo | yes (repo) | no |
| npp-taskdlg-textcolor 1.0.1 | ModsSource + repo | yes (repo) | no |
| center-titlebar-fork 3.4 | H:\Claude\misc\side-projects\windhawk | no | no (prototype) |

Metadata checks before the fix: authors read "m417z, local fork",
"Cleroth (OpenCode Go fork)" and "local"; only translucent-flyouts had
github/homepage/license fields. Sweeps for other strays (H: roots, user
profile, Documents\GitHub\windhawk-mods clone = 651 files, all upstream
catalog) found no further mods of ours.

## What changed

1. Metadata in all five sources: `@author DavidHiFi`, `@github
   https://github.com/DavidHiFi`, `@homepage
   https://github.com/DavidHiFi/davids-windhawk-mods`, explicit `@license`
   (GPL-3.0 / MIT / LGPL-3.0 / MIT). Fork credits for m417z and RamonUnch
   (AltSnap), Cleroth, and rounk-ctrl stay in the source comments and READMEs,
   including the GPL modification notice on alt-snap-drag.
2. Live `C:\ProgramData\Windhawk\ModsSource` files updated 2026-09-30 via
   `scripts\2026-09-30-apply-modsource-metadata.ps1` (`-Audit` supported).
   Elevated apply verified by SHA256 read-back; backups of the previous files
   and a receipt are in `backups\2026-09-30\modsource\`. Metadata-only change:
   no engine restart, no DLL rebuild, running mods untouched.
3. Working copies under `Windhawk\` updated to match the live sources.
4. `center-titlebar-fork` moved from H:\Claude into
   `Windhawk\center-titlebar-fork\` and added to the snapshot repo
   (`mods/local/center-titlebar-fork/`). `Build-Repo.ps1` gained an
   `$offlineLocal` map for mods that are not installed on the machine.
5. Snapshot repo refreshed and pushed: commit b49cb90 "Local mod metadata for
   the catalog, add center-titlebar-fork, refresh snapshot". Catalog refresh
   included restore-folder-menubar-25h2 3.1.0 and
   taskbar-notification-icon-spacing 1.4. Tag and release v1.2.0, zip sha256
   `C58360B6FADDFDBF9498626B60A0B157773AE86ADCFF3EF159B2A815FF0EAB81`.
6. Upstream catalog submissions (ramensoftware/windhawk-mods), each a
   single-file PR from the DavidHiFi/windhawk-mods fork:
   - PR #5813 "Add alt-snap-drag"
   - PR #5814 "Add taskbar-ai-quota-opencode"
   - PR #5815 "Add npp-taskdlg-textcolor"
   - PR #5785 (translucent-flyouts) updated with the homepage line.
   All four files were preflighted locally with the repo's own
   `.github/pr_validation.py` (0 warnings) and its symbol extractor (0
   errors). Workflow runs on fork PRs wait for maintainer approval before CI
   starts, so the validation check will appear once a maintainer approves.

## Verification

- `pr_validation.py mods/<file> DavidHiFi 106938608`: clean for all four.
- `get_mod_symbols`: no extraction errors for all four.
- Live read-back of the four ModsSource headers (author/github/homepage/
  license lines) matches staging; receipt:
  `backups\2026-09-30\modsource\apply-receipt.json`.
- Repo: clean working tree after push; release v1.2.0 carries
  `davids-windhawk-mods-1.2.0.zip`.

## Rollback

- Metadata: copy the originals back from `backups\2026-09-30\modsource\`.
- Repo: revert b49cb90; delete release and tag v1.2.0.
- PRs: close #5813/#5814/#5815; #5785's homepage commit can be reverted on the
  branch if unwanted.

## Open items

- BLOCKED: the GitHub account DavidHiFi is flagged (hidden account). All
  workflow runs on the four PRs and on the `/ai-review` comments are
  suppressed, and every DavidHiFi URL (profile, repos, release) returns 404
  to everyone else until GitHub Support restores the account. Evidence, the
  support draft and the post-unflag checklist:
  `notes\2026-09-30-github-account-flagged.md`.
- center-titlebar-fork is deliberately not submitted upstream: it is a
  prototype that has never been installed or tested live (it injects into
  dwm.exe). It needs a supervised live test before any submission.
