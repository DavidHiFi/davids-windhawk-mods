# Launchpad 2.6.3 and Halo 0.5.4: Windows key belongs to Halo, plugins are Modules

Plan: owner request 2026-11-20 ("audit both mods, remove the Flow launcher option from
Seamless Launchpad, make Halo's plugins Modules with a modules page"). Work done from the
laptop over ssh; sources staged and installed with `scripts\Install-StagedMod.ps1`.

## What changed

| Thing | Old | New | Rollback |
|---|---|---|---|
| Launchpad Keys page | `winKeyAction` choice, "Windows key" (default grid) | removed; the option and its load are gone | install `backups\settings-material\local@seamless-launchpad-20261120-0256.wh.cpp` |
| Launchpad keyboard starts | the ShowStartView hook turned every keyboard open into the grid | keyboard opens that are not its own Shift + Win press pass through to the original Start; the Start button and non-keyboard ways still open the grid | same backup |
| Launchpad readme | claimed the Windows key | Start button + Shift + Win; notes the Windows key stays with the launcher that takes it (Halo) | same backup |
| Halo wording | "Plugins" in the description, readme, Modules page intro, count line, card fields, results settings, About line, link row | "Modules"; internal keys unchanged | install `backups\settings-material\local@halo-launcher-20261120-0257.wh.cpp` |

Kept on purpose: internal `plugin:` field keys, `halo:plugset:` urls, engine ops
`plug/plugset/plugsettings`, registry value names, Flow's own module settings windows,
Flow and Wox credits. Owner's live settings untouched: `shiftWinKeyAction=grid`
(Shift + Windows key still opens the Launchpad grid); the leftover `winKeyAction=start`
stays in the registry but nothing reads it.

## Proof

- `settings-material.py check --staged`: both ok. `mod-consistency.py check --full`:
  both pass; `local@seamless-title-bars` and `local@seamless-window-manager` fail
  behind-template (other threads' work, untouched).
- Installed elevated, base-hash guarded: registry v2.6.3 and v0.5.4, both enabled.
- On-screen key and menu proof was refused by its own guard twice: first the focused
  app swallowed the test chords, then the owner was in GTA5 fullscreen. The owner's
  check: Windows key opens Halo, Shift + Windows key opens the Launchpad grid.
- Attempt recordings and logs: `D:\Agent Work\2026-11-20-halo-proof\` (no state changed).
