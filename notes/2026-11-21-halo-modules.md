# Halo 0.6.1: Modules page fills the width, settings open inside the card

Owner ask (2026-11-21): the Modules grid sat in the middle with three per row and empty
space either side; opening a module showed an "Open its settings" button instead of the
settings. Wanted: more per row across the whole page, and the module's settings shown the
moment its card opens, like Flow Launcher.

## What changed

| Part | Old (0.6.0) | New (0.6.1) |
|---|---|---|
| Grid width | capped at the page's reading width, 3 per row | fills the page, cards at least 280 wide, up to 8 per row |
| Closed cards | height followed each card | one height for every closed card in the grid |
| Opening a card (grid) | the card grew in place | a full-width card opens under its row, its tile keeps a lit edge |
| Opening a card (list) | grew in place | unchanged, grows in place |
| Module settings | "Open its settings" button (opened Flow's window) | the module's own settings panel sits inside the open card |
| Engine | no panel ops | `panel` / `panelclose` ops; replies `panel` (height) and `panelgone` |

How the inline panel works: the settings window makes a holder child window where the
card's panel row is, cut to the visible page and around the footer pill. The engine builds
the module's settings panel (the same one Flow shows) as a child window of that holder, as
tall as its content, and reports its height so the card grows to fit. Wheel turns the
panel does not use scroll Halo's page. Changes save the way Flow saves them.

Halo's two hooks (panel messages, window closing) use a window subclass, so the shared
settings window code stays word for word the template's (settings-engine check: in sync).

## Files

- Job folder: `work\2026-11-21-halo-modules\` (staged source, engine source, builds).
- Installed through `work\2026-11-11-halo-launcher\` (the Halo installer builds from there).
- Job copy of `Build-HaloEngine.ps1` reads the exit code properly (`$null = $p.Handle`
  after Start-Process). The shared copy in `work\2026-11-11-halo-launcher\engine\` still
  reports "Compile failed ()" on a good build; not changed here (other threads use it).

## Rollback

Backups carry the stamp 20261121-0613.

1. `coop lock windhawk-engine`.
2. Copy `work\2026-11-11-halo-launcher\local@halo-launcher.wh.cpp.bak-20261121-0613` over the work
   copy, `engine\build\Halo.Engine.dll.bak-20261121-0613` over the build, `engine\src\HaloEngine.cs.bak-20261121-0613`
   over the source.
3. Elevated: `Install-StagedMod.ps1 -Id local@halo-launcher -Staged <work copy> -BaseHash <live hash>`,
   then `scripts\2026-11-12-halo-launcher.ps1 -Install` (it swaps the engine while the mod is off).
4. The live engine's own backup: `%LOCALAPPDATA%\HaloLauncher\engine\Halo.Engine.dll.bak-20261121-0613`.

## Result

- Installed 6:14 am, elevated, base-hash guarded: registry v0.6.1, enabled, helper running,
  engine loaded and ready (34 modules), keys taken, draw tools warmed. Live engine library
  hash matches the new build.
- Checks before install: settings-engine in sync, settings-material ok, mod-consistency
  0 fail 0 warn. Mod and engine compiled through the load gate.
- Published: davids-windhawk-mods 035a19e (0.6.1 in the repo), Workshop feed 2c13fb4.
- Not proven on screen: the desktop lock was held by another thread and the owner was
  using the tower, so the Modules page was not opened or recorded. To check: open Halo's
  settings, Modules, open a card with settings (for example Calculator or Shell). Its
  settings should show inside the card, scroll with the page and stop at the footer pill.
  If a card shows "Its settings could not load", the engine log names the module.
- An etcher-cli crash at 6:15 am in the event log belongs to another thread's job, not Halo.

## On-screen proof (2026-11-21, 8:47 pm, Warden, Halo 0.6.3)

- Full-size window: 7 modules per row across the whole page (was 3). Snap: `work\2026-11-21-halo-modules\proof\runA\wide.png`.
- Opening the Shell card shows its own settings right inside the card (checkboxes, picker, number box), no extra button. Closing it folds back cleanly. Snaps and recording: `proof\runB\` (`open.png`, `closed.png`, `take\modules.mp4`, `take\modules.gif`).
- Not proven: scrolling with a card open. At full size the whole page fits on screen, so there was nothing to scroll.
- Seen: the module's own controls keep their own plainer look (smaller system font). Possible follow-up: restyle them to match.
- How it was driven: one-shot interactive task running `proof\halo_drive.py` under the desktop lock; opens settings by the tray-click message, checks the window under the cursor before every click, sends no keys.

## Wheel scroll with a card open (2026-11-22, Warden, engine 2FB4D56DB8B5)

- Engine wheel fix live since 12:34 pm (backup beside it: `Halo.Engine.dll.bak-20261122-1234`).
  The mouse wheel now scrolls the Modules page while the pointer sits over an open card,
  and scrolls the card's own list (Web Searches grid) when that list can still move.
- Proof, run F: `proof/runF/` snaps `c-grid-wheel.png`, `d-panel-wheel.png`, recording
  `scroll-wheel.mp4` (15 s) and `scroll-wheel.gif`.
- Same snaps show the smeared Save bar (stale copies of the footer pill down the card).
  Cause: `Halo_PlacePanels` sets the clip region with no redraw, then SetWindowPos copies
  old bits; newly shown areas are never repainted. Fix idea: SWP_NOCOPYBITS plus
  RedrawWindow(RDW_INVALIDATE | RDW_ALLCHILDREN) when the clip or position changed.
- The 70 px left gap in module panels comes from Flow's `SettingPanelMargin` resource
  (about 70,14,18,14), read once when the control is made. A resource override does nothing;
  the margin has to be replaced by a walk of the panel tree after load.
- Handed over at the owner's word to the "Halo custom keys and plugin store" thread, which now
  owns the smear fix and the module panel look. My unbuilt drafts, for them to reuse:
  `handover-smearfix-066.wh.cpp`, `handover-smearfix.diff`, `handover-engine-panel-look.cs`.
  Nothing of these went live; live mod stayed 0.6.5 (c7f156c84695).
- Trap: `Build-HaloEngine.ps1` runs csc at Idle with a 15 s kill, so it fails silently on a
  busy CPU. Run csc from `build\Halo.Engine.rsp` at BelowNormal instead.

## Smear and panel look live (2026-11-22, 7:44 pm, Warden)

- Mod 0.6.6 (sha256 940D3B9159CA) and engine 3C151E547102 are live. The old ones were 0.6.5 C7F156C84695 and engine 2FB4D56DB8B5, kept as .bak-20261122-1942/1944.
- Run G proof (`work\2026-11-21-halo-modules\proof\runG`): wheel through the grid and the open Web Searches card. No smeared Save bars, one Save bar, and the table now fills the panel width.
- The ship failed three times before any live change. Get-FileHash vanished because 5.1 inherited pwsh 7's module path. The registry write was denied without admin rights. coop lock refused the elevated script because it had no identity. All three are fixed in ship.ps1 and keys-ship.ps1 (backups .bak-20261122-1925).
- keys-ship 0.6.7: Gated() returned Say's Tee output with the exit code. Fixed with `| Out-Null` and relaunched elevated at 7:50 pm. It waits on the load gate.

## Store list and key checks live (2026-11-22, 8:50 pm, Warden)

- Store list empty since 11-12 00:21. Cause: Mullvad excludes `windhawk-mod.exe` from the VPN
  (set 11-04 for the Groq dictation fix). That bypass refuses .NET's default dual-mode socket
  (IPv6 socket to an IPv4-mapped address) with WSAEACCES "access forbidden". Flow's Http
  helper swallows every exception and returns 500, so it looked like a server fault. Proof:
  the excluded opencode binary run as bun connects to 104.16.180.112 but fails on
  ::ffff:104.16.180.112.
- Fix, engine only (mod untouched): `NewWebHandler()` with a ConnectCallback that opens a
  plain IPv4 socket first, used by the engine's own client and swapped into Flow's static
  Http client (`HttpMessageInvoker._handler`), so plugin updates and web suggestions work too.
  Store fetch also falls back to the engine's own fetch over 4 mirrors.
- Live: engine 661BB3E9210F (backups .bak-20261122-2041 and -2048), mod 0.6.8 feabcd242800
  (installed 8:43 pm by the keys thread). Log: "web: Flow's web client now connects over plain
  IPv4 first", no store errors.
- Run I (`proof\runI`): store group fills the Modules page, every store card off by default
  (c-store.png); Win+R through the real hook message opens Halo with "> " and the run history
  (e-win-r.png). Run H covered the Keys page and Ctrl+Alt+F10.
- Rule for any .NET code hosted in windhawk-mod.exe: connect with an IPv4 socket, or every
  web call fails while Mullvad is on.
