# GitHub: davids-windhawk-mods expanded into the full setup snapshot

2026-09-28. Status: published. Repo https://github.com/DavidHiFi/davids-windhawk-mods,
release v1.0.0 "Setup snapshot 2026-09-28".

## What is published

The repo already held the two local mods; this session expanded it into the
whole setup, from the live install:

- `mods/catalog/` 89 sources, copies of every catalog mod installed on this
  machine, taken from `C:\ProgramData\Windhawk\ModsSource`.
- `mods/local/` the three local mods: alt-snap-drag 1.2.2,
  taskbar-ai-quota-opencode 1.6.5.1, npp-taskdlg-textcolor 1.0.1.
- `settings/` mods-state.json (per-mod disable/include/version),
  mods-settings.json (every `Settings` value), the app and engine `.reg`
  exports, quota-mod-localstorage.json (the two quota mods' `settings_v1`),
  and windhawk-userprofile.json.
- `mod-storage/` the Taskbar Styler images, `editor/settings.json`.
- `manifest.json` all 92 mods with author, version, license, origin, enabled
  state, and source path.
- `media/` tray before/after screenshots.
- `tools/Apply-WindhawkSettings.ps1` applies the snapshot (elevated; `-Audit`
  previews and reported 0 differences on this machine).
- `tools/Build-Repo.ps1` regenerates sources, settings, manifest and the
  catalog table from the live install.

Commit 8418fb3 on main, tag v1.0.0. The release carries
`davids-windhawk-mods-1.0.0.zip`, sha256
`2fa56d39a6f0c296f922c9f4907da1399921d22e1f0b429be1b9edce4951bcf7`.

## Local checkout

`H:\Windhawk Configuration\davids-windhawk-mods` is fast-forwarded to 8418fb3.
The junction at `H:\System Configuration\davids-windhawk-mods` resolves there.

## Not published

- `auth_*` values in the quota mods' LocalStorage (DPAPI credentials, tied to
  this machine). The staged content was scanned for DPAPI blobs and key
  material before the push; none present.
- Runtime caches: SymbolCache, stats timers, the taskbar app order file.

## Incident: stray draft release in DavidHiFi/system-configuration

`gh release create` without `-R`, run with H:\System Configuration as the
working directory, attached to a pre-existing draft release v1.0.0 in
DavidHiFi/system-configuration (created 2026-09-20) and published it with the
Windhawk zip and notes. Undone: the zip asset was deleted, the release was
deleted and recreated as a draft named "v1.0.0" with a note explaining the
overwrite; the tag v1.0.0 was left in place. The draft's original notes were
overwritten and are not recoverable. The correct release was then created with
an explicit `-R DavidHiFi/davids-windhawk-mods`. Lesson: pass `-R` to every gh
command when the working directory is another repo.

## Keeping it current

After changing mods or settings, run `tools\Build-Repo.ps1` from the repo root,
review `git diff`, commit, push. To add a new local mod, add its id and repo
path to the `$localPaths` map in Build-Repo.ps1, add a license override if it
is not repo MIT (alt-snap-drag is GPL-3.0), then rerun it.

## Rollback

Nothing on the live system was changed by this work; the exports are read-only
and the machine's own registry/files remain authoritative. To remove the
publication, delete the release and the repo, or revert main to cef8945.

## Update 2026-09-28 (evening): translucent-flyouts published

- Repo `main`: f9246e9 "Add translucent-flyouts and refresh the snapshot"
  (fourth local mod, LGPL-3.0; refresh: file-operation-styler 1.1.0, catalog
  additions better-volume-mixer / explorer-hide-focus-border /
  parallax-wallpaper, settings exports) and 0f2a1f7 "translucent-flyouts: fix
  the architecture metadata format". `tools/Build-Repo.ps1` lists
  `local@translucent-flyouts` in `$localPaths`; `mods/local/translucent-flyouts/`
  and both READMEs updated.
- Release v1.1.0 "Setup snapshot with translucent-flyouts", tag at 0f2a1f7,
  asset `davids-windhawk-mods-1.1.0.zip`, sha256
  F4D70692D37CA676D4BB5FB661B0CBDF7EAE19806C31455B9905CE41615A3234.
- Upstream catalog: PR https://github.com/ramensoftware/windhawk-mods/pull/5785
  "Add translucent-flyouts" from `DavidHiFi:add-translucent-flyouts`
  (fork `DavidHiFi/windhawk-mods`), single file `mods/translucent-flyouts.wh.cpp`.
  The repo's `pr_validation` check passed. Pending maintainer review/merge;
  after merge the mod appears on windhawk.net/mods and installable from the
  catalog.
- Publication flow used for a new local mod: add it to `$localPaths` in
  `Build-Repo.ps1`, run it, commit+push, then `git clone` the fork, branch from
  `main`, copy the single `.wh.cpp` to `mods/`, push, `gh pr create -R`.
