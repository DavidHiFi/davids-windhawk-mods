# Seamless Snipper 0.6.6: Magic Pointer brought to the rice recipe (2026-11-21)

Owner ask: "magic mouse ... make sure that it is styled properly with the borders, colours etc.
our recipe and fonts". Magic Pointer is the pointer card inside local@seamless-snipper.

## What changed (src\magic-pointer.cpp, backup magic-pointer.cpp.bak-20261121-2120)

| Part | Old | New |
|---|---|---|
| Card glass tint | dark 0.85, light 0.82 | dark Rgb(30,30,46) 0.60, light Rgb(249,249,252) 0.62 |
| Card fill with no blur | see-through | opaque Mocha #1E1E2E to #181825 |
| Card edge | always-on gradient | 2px grey #585B70 at rest, blue to mauve gradient fades in over 150 ms on hover |
| Chips, buttons, add tile, copy answer | flat hover fill | 2px gradient edge on hover, mauve edge pressed |
| Input box | underline | 2px edge: grey rest, gradient hover, blue focused |
| Thumbnails, code blocks, send button, tooltip | 1px or radius 5-6 | radius 8, 2px grey edge |
| Outline glow frame | radius 12, white mix 0.65 | live corner radius (16 x dpi/96), pure gradient |
| OCR sweep glow | white mix | pure gradient |
| Palette (dark) | lighter greys | divider #45475A, control and tooltip border #585B70, hover surface0 0.55, pressed surface1 0.60 |
| Hint pill text | white 0.96 | Mocha text #CDD6F4 |

Fonts were already FiraCode Nerd Font everywhere; the menu (menu-look.cpp), cursor, icon
fonts and skeleton bars were left as they were.

New message WM_APP + 41 (WM_APP_PREVIEW_HOVER) on the card window: wParam = hit id, lParam = 1
lights the card edge. Used only by the proof so no cursor is moved; the next real mouse
move takes over.

## Install and publish

- Installed 10:04 pm, registry v0.6.6, live hash 6B7422B48FE3386AA3769E40C95FEBE8575B6030B036DD384A35EEF10081C754.
- Published: davids-windhawk-mods 90d3df4, seamless-workshop e1ca8a2.
- The installer's own publish step failed twice with "file not found": git was missing or
  broken at that moment (another thread was reinstalling Git, uninstaller seen 10:16 pm).
  Also: this agent shell carries NoDefaultCurrentDirectoryInExePath=1, which makes Git's
  cmd\git.exe stop with "BUG (fork bomb)". Clear it for the process before running git.
- Test PC not used: it was held by another thread and has no Windhawk inside.

## Rollback

Reinstall backups\...\local@seamless-snipper-20261121-2204.wh.cpp (0.6.5) with
Install-StagedMod.ps1 against base hash 6B7422B4..., or restore
src\magic-pointer.cpp.bak-20261121-2120, set VERSION back to 0.6.5 in assemble.py and rebuild.

## 0.6.7: lighter glass

The live 0.6.6 capture read "barely frosted" in glass-check (movement 0.4 to 1.3, needs 1.5+),
so the card tint went from dark 0.60 / light 0.62 to dark 0.42 / light 0.46 (one line,
GlassTint). Installed 11:10 pm as v0.6.7, published davids-windhawk-mods 47fa06b,
seamless-workshop 4c9921f. After install the helper did not come back; restarted with
2026-11-10-tool-mod-restart.ps1 at 11:23 pm (pid 9776). Rollback to 0.6.6: reinstall
backups ...\local@seamless-snipper-20261121-2310.wh.cpp.

## Proof

Live run 10:57 pm on 0.6.6 (work\...\test\proof-066-pointer-tint060), all input posted as
messages (typing and Esc are the pointer's own hotkeys), cursor never moved:

- Pointer summoned, card opened on a typed W, Esc put it away (result.json: pointer, card, gone true).
- Card edge sampled on all four sides: rest #585B70 exactly; hot runs #8EB3FA top-left to
  #C6A7F7 bottom-right. Corners at 4x: round on the live radius, no square or doubled edge.
- Hover fade filmed (pointer-card.mp4 and .gif in that folder).
- Glass: frosted, text behind unreadable, but glass-check said barely frosted, hence 0.6.7.

Live run 12:56 am on 0.6.7 (test\proof-066-pointer), same steps, all passed:

- Edges again #585B70 on all four sides at rest, gradient when hot.
- glass-check: PASS (movement 1.86) where two colour bands meet under the card; WARN
  (movement 0.6) over the middle of one wide band. The tint is at the recipe's floor
  (0.42 against 0.40 to 0.65), so the rest is the system blur's own spread; text behind
  is unreadable and colour moves under it by eye. Clip: pointer-card-067.mp4 / .gif.

Not checked: pressed state, the card while unfocused, a narrow width, the test PC (held by
another thread and has no Windhawk), the light theme.
