# Translucent Flyouts 0.6.32: clean release, title-bar menu artefacts fixed, look verified persistent

Thread 72f9bcc6, continuing settled thread 55f21ec1. The owner's screenshot showed the
wanted look (blurred Mocha desktop menu); the remaining complaint was the title-bar
system menu (Dopamine, and the same shape in other apps): stray bright ticks down the
right edge, a doubled right outline, and bright lines flanking the separator.

## Root cause (measured, not guessed)

Every menu background band (`MENU_POPUPBACKGROUND`, one per item row) was re-framed with
the border colour after its clear (`HandleMenuDrawThemeBackground` in
`Windhawk\translucency-flyouts\src\30-engine.inc`). The real outline (POPUPBORDERS, full
window rect) already paints last in every pass, so the per-band frame only added strays:

- vertical ticks at each band's right clip edge (client x=178), one per 22 px row — the
  item BLACKNESS covers the frame's left edge but the item rect ends at x=176, leaving the
  right edge exposed. That is why only the right side showed ticks.
- a second vertical at the separator row and full-width horizontals at each band boundary
  (the bright lines around the separator the owner saw).
- a doubled right outline (band frame at local x=281 + real outline at 284).

Proved with a temporary magenta-border / cyan-gradient / green-separator attribution run:
every stray shape rendered in border magenta at exactly the band-frame geometry
(`reports\2026-10-13-translucent-flyouts-0.6.32\appmenu-attr-dopamine-3x.png`, magenta
run map in the receipt). Test colours were restored afterwards; separators are empty
(= schema defaults `0x30D9D9D9`/`0x30262626`), matching the 0.6.17 baseline reg.

## Change (0.6.32)

- `src\30-engine.inc`: removed the per-band border re-draw; the BLACKNESS clear stays.
  Four lines removed, comment explains why.
- `src\00-foundation.inc`: version 0.6.31 -> 0.6.32.
- `scripts\2026-09-28-translucent-flyouts-build.ps1`: `-DTF_DEBUG_LOG` is no longer baked
  in; debug logging is opt-in via `-DebugLog`. Release DLLs carry no logging hooks.
- Built x64+x86 against `Engine\2.0.0_1`, clean, in `Windhawk\translucency-flyouts\build-0.6.32`.
- Installed live with `scripts\2026-10-13-translucent-flyouts-0.6.32.ps1` (`-Audit` /
  `-Install` / `-Rollback` to 0.6.31): `LibraryFileName=local@translucent-flyouts_0.6.32_1.dll`,
  `Version=0.6.32`, `Include=*`, marker bumped. Registry backup:
  `backups\2026-10-13\translucent-flyouts-0.6.32\mod-key-0.6.32.reg`.

Settings untouched (modern_acrylic, Mocha `0xCC1E1E2E` at 80%, border `0xFF89B4FA`,
`windhawk-ui.exe` still block-listed for the plain Windhawk title-bar menu).

## Verification (all measured, all on the live build)

- Dopamine title-bar menu (the owner's surface): single #89B4FA outline, uniform Mocha
  body (#212131/#202132), single separator, zero interior border-colour pixels
  (`appmenu-dopamine-final-3x.png`, `appmenu-dopamine-final-result.txt`).
- Desktop menu dark + bright, main + first submenu (`final-0632-result.txt` + 2x views):
  body #242534/#343142, outline #89B4FA on all four edges, rounded corners, blur visible.
  Matches the 0.6.31 baseline within 1-2 levels per channel.
- Persistence: Explorer restarted twice (PIDs 20512, 8748); 0.6.32 loads in the new
  process each time; post-restart probe (`persist-0632-result.txt`) matches within 1-2
  levels. The look sticks.
- TIDAL window was minimized for the desktop probes and restored (pid 22812, visible).
  No popups left open. One stale Dopamine child (pid 6544) still maps 0.6.31; it reloads
  on the next marker/Dopamine restart and paints no menus.

## Leftovers / traps for the next thread

- `build-0.6.32-diag\` + `.tmp\translucent-flyouts-0.6.32-diag.ps1` + `.tmp\dopamine-diag-copy.log`:
  the diagnostic build used for tracing. Never install it; 0.6.32 is live.
- `IsTargetProcess()` in `00-foundation.inc` gates log output to a fixed process list;
  add a name there (as was done for Dopamine.exe) before tracing a new process.
- The probe scripts live in `reports\2026-10-13-translucent-flyouts-0.6.32\`:
  `verify-flyouts.ps1` (desktop dark/bright + submenu), `probe-app-menu.ps1` (any window),
  `probe-minimize-cover.ps1` (minimize covering windows first), `probe-titlebar-menu.ps1`
  (classic apps), `probe-desktop-toggled.ps1` (Win+D variant, less reliable than minimize).
- Win+X is a XAML popup (`Xaml_WindowedPopupClass`), not a classic menu; this mod does not
  style it.
- Colour attribution trick: distinctive border/gradient/separator values make artefact
  geometry obvious; always snapshot + restore (`.tmp\menu-colours-test.ps1 -Apply/-Restore`,
  empty separator = schema default).
- Public repo untouched: `DavidHiFi/davids-windhawk-mods` main still holds 0.6.16
  (PR #10). 0.6.32 is local-only until the owner asks for a publish.
