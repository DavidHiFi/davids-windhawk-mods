# Halo Launcher: module settings panels sweep (2026-11-23)

Owner asked: "Get it done all the way, you make the decisions go the extra mile", after
"What is this ugly UI?" on the Modules page. Survey of every Flow module panel in Halo settings.

## Survey

- Panels seen: Calculator, Desktop Cleanup, Discord timestamps, Discord Webhook, Emoji Finder,
  Env, Process Killer, Program, Quick Uninstall, Scoop, Search npm, Shell, Speed Test, Web Searches.
- Every control is already Mocha (combos, checkboxes, list wells with the grey frame, buttons,
  text boxes). No light or white edges.
- The one fault on all of them: the plugin's own dark background (Mantle) painted a square
  920 px slab behind the content, inside the rounded card (#242435). Square inside a round,
  and a dock inside a dock.

## Fix (engine only, no mod change)

- `ClearBacking` in HaloEngine.cs: wide (>= 60% of the panel, or the single-child spine at open),
  opaque, solid fills darker than the card go transparent. Lists, text boxes, buttons, popups,
  thumbs and sliders keep their own fills. Runs at open and on the 400 ms refix tick.
- The 920 px width cap in the mod stays on purpose: stretching Flow panels spreads checkbox rows.
- Work folder: `work\2026-11-23-halo-panel-sweep\` (diff: `fixpaneltree.patch.diff`).

## Real cause and fix (shipped 6:22 am, engine F25EFAC23F63)

- ClearBacking alone did nothing: the slab was Halo's own root Border. `MochaOf` was not
  stable for greys: #242435 mapped to #1E1E2E, and #1E1E2E to #181825. The refix tick runs
  on every layout, so the card fill sank to Mantle within two passes (logged: #1 #FF1E1E2E,
  #2 #FF181825).
- Fix: `MochaKeep` set. Colours already in the Mocha greys, the card fill and the accents
  are returned unchanged. Log after the fix: root stays #FF242435 on every panel.
- Proven live 6:22 to 6:28 am by posted messages only (no cursor, no focus), on Halo 0.6.10:
  Calculator, Program, Scoop, Shell and Web Searches panels all card colour inside, corners
  round at 4x, every card collapsed again. Captures: `work\2026-11-23-halo-panel-sweep\proof2`
  to `proof5` (corners: `proof4\corners-4x.png`).
- Not checked live: the other nine panels (same code path, same root Border).
- The one-line "panel tree" log per panel open stays as a cheap tripwire.
- Rollback to the pre-fix logging build: backups stamped `.bak-20261123-0621`; to the
  original: `.bak-20261123-0512` (steps below).

## Shipped 5:13 am

- Engine old 661BB3E9210F, new AE1B1FDB494C. Helper restarted, engine loaded (pid 38232).
- Rollback: under the windhawk-engine lock, run tool-mod-restart -Off, copy
  `%LOCALAPPDATA%\HaloLauncher\engine\Halo.Engine.dll.bak-20261123-0512` back over the dll,
  restore `work\2026-11-11-halo-launcher\engine\src\HaloEngine.cs.bak-20261123-0512` and
  `build\Halo.Engine.dll.bak-20261123-0512`, then tool-mod-restart again.
