# Seamless Workshop 1.4.0 (2026-11-22)

Owner's request: a friend installs only Seamless Workshop and gets every mod the owner runs, his
own and the Windhawk library ones, with or without his settings, optionally on a clean slate.

## What changed

- Feed gains `library`: every installed Windhawk library mod with its version, on/off, scrubbed
  settings and custom include/exclude app lists (`publish-mods.py`, `presets/davidhifi-library.json`).
  Audit: 131 library mods, all published at the pinned version (`work/2026-11-22-friend-setup/`).
- New group "DavidHiFi's whole setup" on the welcome card and the Updates page:
  - "Clean slate first" (on by default): every mod but the Workshop is backed up, saved as a
    "Before DavidHiFi's whole setup" preset, then removed.
  - "Copy everything, settings included": installs all turned off, writes his settings and app
    lists, then turns on the ones he has on (last, so a stopped job leaves nothing half set up).
  - "Install everything, default settings": installs all turned off, no settings copied.
  - Both need a second click within 5 seconds.
- `Hub_RunBlocks`: the job runs one block per mod. A failed block is skipped and named, the rest
  carries on. A library install tries his exact version, then the newest.
- Windhawk's own engine settings (its Exclude list) are not copied.
- README (seamless-workshop 95189e5) and windhawk-alpha-updater README (e62c41d, pushed) give the
  three steps: alpha updater, the one-line Workshop install, then the whole-setup buttons. The
  Workshop installer runs the updater itself when Windhawk is older than 2.0.

## Files

| File | Old | New | Rollback |
|---|---|---|---|
| work/2026-11-12-seamless-hub/src/features.inc | 1.3.0 | library parse, Hub_FullSetup, whole-setup group | `.bak-20261122-1049` |
| work/2026-11-12-seamless-hub/src/hub.cpp | 1.3.0 | Hub_RunBlocks, arm timer covers g_fullArmed | `.bak-20261122-1049` |
| work/2026-11-12-seamless-hub/make_mod.py | @version 1.3.0 | 1.4.0, What's new in 1.4.0 | `.bak-20261122-1049` |
| scripts/publish-mods.py | no library | library preset and feed list | git |
| seamless-workshop/CHANGELOG.md | top 1.3.0 | 1.4.0 entry | git revert |
| Live mod local@seamless-workshop | 1.3.0, sha256 11b3278d...9de2 | 1.4.0 | reinstall the v1.3.0 release asset with Install-StagedMod.ps1 |

## Install

Staged at `work/2026-11-21-tray-ids/staged/seamless-workshop.wh.cpp` (sha256 2d9d8ca0...d60f).
settings-engine in sync, settings-material ok, mod-consistency 0 fail 0 warn. The compile check and
install wait on the load gate (`chain-1.4.0.ps1`, log `chain-1.4.0.txt`) because the owner was in
Ableton when it was ready. Never click the clean-slate or whole-setup buttons on the owner's PC.
