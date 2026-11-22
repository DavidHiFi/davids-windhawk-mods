# Seamless Workshop 1.3.0 (2026-11-22)

Asked by the WacOS thread (0ecf3c2c), started on the owner's "Skip the queue", installed on the owner's
"Install it now anyway" while Ableton was open (8:31 am, engine lock, Idle priority, no load gate).

## What changed

- The feed's `categories` list (Taskbar, Explorer, Windows and menus, Tools, Fixes) sets the headings
  and their order. Each mod's `category` puts it under one. Missing or unknown: "Other".
- Marketplace: "From DavidHiFi" plus the count line, then one heading per group with its count.
  Search looks through every group and also matches the group name.
- Updates: "Check the feed now" and "Update all" sit at the top of "From DavidHiFi", then the
  updates under group headings. "More from DavidHiFi" gets a count line, then group headings.
- Mods page: "What it changes" now sorts into the feed's groups. A mod not in the feed is guessed
  from what it loads into (window look and every app go to Windows and menus, taskbar to
  Taskbar, Explorer to Explorer, tools to Tools, the rest to Other). It is now the default
  sort for anyone who never picked one (Set.modsGroup missing means 1, was 0).
- When the feed arrives, the Mods page sorts again so the feed's words win over the guess.
- New self-test block for the parse and the grouping (runs only in the standalone build; it did
  not run this time).

## Files

| File | Old | New | Rollback |
|---|---|---|---|
| work/2026-11-12-seamless-hub/src/features.inc | 1.2.0 | category field, categories parse, Hub_FeedByCat, grouped Marketplace and Updates | `.bak-20261122-0625` |
| work/2026-11-12-seamless-hub/src/hub.cpp | 1.2.0 | group list helpers, Mods page groups, default sort 1, self-test | `.bak-20261122-0625` |
| work/2026-11-12-seamless-hub/make_mod.py | @version 1.2.0 | 1.3.0, What's new in 1.3.0 | `.bak-20261122-0625` |
| seamless-workshop/CHANGELOG.md | top entry 1.2.0 | 1.3.0 entry (commit db8549b) | git revert |
| Live mod local@seamless-workshop | 1.2.0, sha256 7e56b078...6ef4 | 1.3.0 | reinstall the v1.2.0 release asset with Install-StagedMod.ps1 |

## Proof

- Compile check: "compiles (tool mod)". settings-engine in sync, settings-material ok,
  mod-consistency 0 fail 0 warn.
- Registry v1.3.0, library local@seamless-workshop_1.3.0_996826.dll, loaded by the tool process
  started 8:32 am.
- Release v1.3.0 has both files. Feed: app 1.3.0 with its What's new line, 49 mods, all 49 with a group.
- The desktop shell was not restarted by the install (its last start was 7:00 am, before it).
- No screenshot: opening the window would take focus while the owner was at the PC.
