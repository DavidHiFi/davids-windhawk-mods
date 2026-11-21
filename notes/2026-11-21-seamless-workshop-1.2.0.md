# Seamless Workshop 1.2.0 (2026-11-21, late evening)

Owner asked for four in-app changes as one update ("1, do all four").

## What changed

1. Marketplace: DavidHiFi's mods first, with a count line ("N mods made by DavidHiFi, M of them
   installed"). A notice shows while his list is read or when it fails. Clicking one of his
   mods that is installed and current opens it on the Mods page (button "Open") instead of
   reinstalling it.
2. What changed in each update: the feed now carries `changes` per mod, taken from the mod's
   own readme section `## What's new in <version>` (scrubbed, one line, max 280 chars). The
   Workshop itself falls back to its CHANGELOG. Shown on the Updates page links, on the
   update card ("New in X: ...") and in the tray message when there is one update.
3. Welcome on first open (Mods page, above the list): shows when `Set.welcomed` is not set
   and none of his mods are installed. Apply his whole setup, Pick from his mods (opens
   Marketplace on "From DavidHiFi"), or Not now. Applying the setup also sets the flag.
4. Remove all of DavidHiFi's mods (Updates page, "DavidHiFi's setup" group): click twice,
   backs up source and settings, copies the settings to the Presets page as
   "Before removing DavidHiFi's mods <tick>.json", then removes them in one admin job.
   Seamless Workshop itself and other mods stay.
5. Backups no longer stop at 32 mods (Hub_BackupFiles passes the real count).

## Files

| File | Old | New | Rollback |
|---|---|---|---|
| work/2026-11-12-seamless-hub/src/features.inc | 1.1.1 code | four features | `.bak-20261121-2343` beside it |
| work/2026-11-12-seamless-hub/src/cards.inc | 1.1.1 code | update card text, Open button | `.bak-20261121-2343` |
| work/2026-11-12-seamless-hub/src/hub.cpp | 1.1.1 code | welcome hook, arm reset | `.bak-20261121-2343` |
| work/2026-11-12-seamless-hub/make_mod.py | @version 1.1.0, no preview, no What's new | 1.2.0, preview line, What's new in 1.2.0 | `.bak-20261121-2343` |
| scripts/publish-mods.py | no `changes` in feed | `one_line`, `whats_new`, feed `changes` | `.bak-20261121-2343` |
| Live mod local@seamless-workshop | 1.1.1, sha256 5f7f1b0b...555f | 1.2.0 | reinstall the 1.1.1 asset from the GitHub release v1.1.1 with Install-StagedMod.ps1 |

Registry value added by the app: HKCU Seamless Workshop key, `Set.welcomed` (DWORD 1). Delete it
to see the welcome again.

## Habit for every mod release

Put a `## What's new in <version>` section in the mod's readme. That is the only place the
Workshop reads "what changed" from for a mod. Today 1 of 49 mods has one.
