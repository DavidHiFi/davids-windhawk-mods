# 2026-10-16 — translucent-windows fork: full regime audit + description rewrite

Owner ask: the fork credited only Undisputed00x, and the description/details
should read like our other mods (human, no AI slop) and follow the same
fork workflow as the rest of the workspace.

## Earlier fix this morning (verified, not redone)

At 11:15 AM an agent credited DavidHiFi in both source copies (ModsSource +
`Windhawk\translucent-windows\`): `@author DavidHiFi, Undisputed00x`,
`@github https://github.com/DavidHiFi`, and a Based-on line opening the
readme Credits. Note:
`notes\2026-10-16-translucent-windows-author-credit.md`. The screenshot in the
owner's message (author = Undisputed00x only) predates that fix. The engine
now reports `local@translucent-windows` 1.8.3, author
"DavidHiFi, Undisputed00x", enabled, `updateAvailable=false`.

## Audit verdict (this session, 1:04 PM)

| Item | Verdict |
|---|---|
| `@id translucent-windows` | Kept. `local@` lives only in the filename and registry key; the parser rejects `@` inside `@id` (traps item 6). |
| `@name Translucent Windows` | Kept. Fix fork that tracks upstream, so no Plus suffix. A Plus name would imply new features and force an id migration. |
| `@description` | **Rewritten** (the one change). Was the generic upstream line "Enables native translucent effects in Windows 11". Now: "Blur, acrylic and mica for app windows, with per-app rules and custom themes" (76 chars, one line, no trailing period). Every fact comes from the mod's own readme (Blur/Acrylic/Mica/MicaAlt, custom theme rendering, per-process rules). Same plain voice as the sibling mods. |
| `@author` / `@github` | Already correct. Only merged code sources are listed (DavidHiFi's fix on Undisputed00x's mod). Upstream's thanked parties stay in the readme, not the author line. |
| `@homepage`, `@license` | Correctly absent. The fork is not published in davids-windhawk-mods, and upstream ships no license to inherit. Nothing invented. |
| Readme | Kept upstream's (FAQ is the operator documentation for this mod's settings) with only the Based-on Credits line. Full style-guide readme treatment (features, preview) applies if it is ever published. |
| Placement | Correct as a private checkout (`Windhawk\translucent-windows\` + ModsSource), outside the public repo, like the other unpublished fix forks. |
| File encoding | Clean. The earlier "mojibake" was a console decoding artifact; the file is valid UTF-8 and the emoji render. |

## Change record (description rewrite, ~1:00 PM)

- Script (`-Audit` / `-Install` / `-Rollback`):
  `scripts\2026-10-16-translucent-windows-description.ps1`, run elevated via
  `scripts\2026-10-16-description-run-elevated.ps1`
  (transcript: `reports\2026-10-16-translucent-windows-description\install-log.txt`).
- One byte-exact line edit in both copies. New source hash
  `9B30ED9687FEB46B8EB9E244CEC41A9D22854B7706ADEB4C0E46C1D23E21133B`
  (was `90E6F83D…B33986A1`).
- Guard repointed to the new hash and resumed (no suspend marker left).
- Verified: both copies identical, `source meta` parses id/description/author,
  engine lists the new description with DavidHiFi first, DLL hashes unchanged
  (x64 `E42532BE…`, x86 `21E15343…`), update offer still absent.
- Receipt: `reports\2026-10-16-translucent-windows-description\receipt.json`.
  Backup (pre-change source + guard):
  `backups\2026-10-16\translucent-windows-description\`.

## Rollback

`Invoke-Elevated.ps1 -File scripts\2026-10-16-translucent-windows-description.ps1`
with `-Action Rollback` appended (restores both copies, restores the guard
hash, resumes the guard). For the morning credit fix, use the author-credit
script's `-Action Rollback` instead.
