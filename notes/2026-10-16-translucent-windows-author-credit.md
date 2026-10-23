# 2026-10-16 — translucent-windows fork: DavidHiFi credited per the mod style guide

## What and why

The `local@translucent-windows` fork (1.8.3, based on Undisputed00x's
Translucent Windows) still carried upstream's metadata: the author line named
only the original creator, and the readme Credits had no based-on line. The
style guide (`docs\mod-style-guide.md`) requires `@author` to list DavidHiFi
first, then the original creator, with the `@github` link pointing at DavidHiFi,
and a "Based on ..." line opening the Credits section.

## Changes (11:15 AM +08, elevated install)

Three byte-exact edits in both source copies (`ModsSource` and the dev copy in
`Windhawk\translucent-windows\`):

- `@author   Undisputed00x`                    → `DavidHiFi, Undisputed00x`
- `@github   https://github.com/Undisputed00x` → `https://github.com/DavidHiFi`
- Credits now opens with
  `Based on [Translucent Windows](https://windhawk.net/mods/translucent-windows) by [Undisputed00x](https://github.com/Undisputed00x).`
  followed by the `#` separator the upstream readme uses; upstream's own credit
  paragraphs (WinExperiments, Maplespe, ALTaleX531, m417z) are untouched.

Name, id, description, version and the DLLs were not touched - the metadata
block is app-layer, the same reasoning as the 2026-10-15 metadata-id fix.

## Style-guide audit (what was checked and left alone)

- `@id translucent-windows`: kept. A `local@` install must keep the catalog id
  in the metadata (the 2026-10-15 trap); the fork's identity lives in the
  filename and registry key.
- `@name Translucent Windows`: catalog style, no personal names - kept. This
  fork tracks upstream (fix fork), so it does not take a "Plus" name, and
  renaming would break the local@ id contract.
- `@description`: one line, under 100 characters, no trailing period - kept.
- `@license`: not added. Upstream ships no license tag and the windhawk.net
  page is JavaScript-only, so no license was invented; the based-on link is the
  source of truth.
- `@homepage`: not added. The fork is not published in
  davids-windhawk-mods, so a repo link would point at something that does not
  exist there.
- Readme: upstream's kept (its FAQ is the operator documentation for this mod);
  only the Credits line was added.

## Verification (11:17 AM +08)

- Both copies byte-identical, SHA-256
  `90E6F83DE06D1720BF0FC8E542C0FC514660FF1888B085EA2D76ADF5B33986A1`
  (was `F694DA98C260CCF01FF8C7E765463CC6F98F54A99010651C9B7FE8D9EFCD7878`).
- `windhawk-cli source meta` parses: id=translucent-windows,
  author=DavidHiFi, Undisputed00x.
- `windhawk-cli --json mod list`: `local@translucent-windows` 1.8.3,
  author "DavidHiFi, Undisputed00x", enabled=true, updateAvailable=false - the
  engine picked up the source metadata without a rebuild.
- Registry key unchanged: Version 1.8.3, Disabled=0,
  `local@translucent-windows_1.8.3_1.dll`; settings untouched (no
  SettingsChangeTime bump needed for a metadata-only change).
- DLL hashes unchanged (both archs match the guard's constants).
- Drift guard: suspended for the edit, `$forkHash` repointed to the new hash,
  resumed; suspend marker cleared; heartbeat stamp fresh (11:18 AM run).

## Records

- Script (Install / Audit / Rollback):
  `scripts\2026-10-16-translucent-windows-author-credit.ps1`, run elevated via
  `scripts\2026-10-16-author-credit-run-elevated.ps1`
  (transcript: `reports\2026-10-16-translucent-windows-author-credit\install-log.txt`).
- Receipt: `reports\2026-10-16-translucent-windows-author-credit\receipt.json`.
- Backup: `backups\2026-10-16\translucent-windows-author-credit\`
  (pre-change source copy + pre-change guard script).

## Rollback

`pwsh -File scripts\2026-10-16-translucent-windows-author-credit.ps1 -Action Rollback`
(restores both source copies from the backup, restores the guard's old hash,
verifies, resumes the guard).

## Notes

- The agent-coop board was unreachable from this session's sandbox (denied on
  the AppData state lock, also on the one allowed escalation retry), so the
  task ran without it; no other thread was working the same files.
- The fork source is not in `davids-windhawk-mods` (it lives in
  `Windhawk\translucent-windows\` like the other private checkouts). If it is
  ever published, the style-guide readme treatment (feature bullets, preview
  image) would apply at that point.
