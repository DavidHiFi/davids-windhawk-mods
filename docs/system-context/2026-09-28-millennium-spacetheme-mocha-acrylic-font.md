# SpaceTheme: label in-theme, FiraCode option, real Mocha acrylic (DWMX)

**2026-09-28 (later):** this fork is now its own theme, **Mocha Steam**
(`millennium\themes\MochaSteam`, author DavidHiFi, repo credits). The stock
SpaceTheme install was restored from upstream and left separate. See section 8.

**Date:** 2026-09-28
**Status:** applied and live (Steam restarted, verified by screenshot).
**Verified evidence:** `reports\2026-09-28-steam-polished-small.png`,
`reports\2026-09-28-steam-menu-blur-check.png`.

## 1. "SpaceTheme" titlebar label now lives in the theme

- `themes\Steam\src\css\steam\titlebar.css` — the "Text Logo" block that injected
  the `content: "Space"` / `content: "Theme"` pseudo-elements is replaced with the
  Quick CSS rules (hide both pseudo-elements, `font-size: 0`, Steam icon 23px).
- `millennium\config\quick.css` is left in place as a fallback: it still hides the
  label if a theme update later restores the rule in `titlebar.css`.

## 2. Font option "FiraCode Nerd Font"

- New `themes\Steam\options\fonts\firaCodeNerdFont.css`
  (`font-family: 'FiraCode Nerd Font', monospace !important`).
- Registered in `themes\Steam\skin.json` under the `Font` option; the user's
  selection in `millennium\config\config.json` now reads `"Font": "FiraCode Nerd Font"`
  (was `Source Code Pro`).
- The font is a per-user install
  (`C:\Users\localuser\AppData\Local\Microsoft\Windows\Fonts\FiraCodeNerdFont-*.ttf`),
  family name confirmed as `FiraCode Nerd Font`.

## 3. Real acrylic blur: DWMX plugin installed and patched

The theme's "Mica & Acrylic plugin support" option only tints surfaces and links
to the DWMX plugin (`steambrew.app/plugin?id=b4c58634419b`, Window Styler). It was
not installed, so the option did nothing but lower opacity.

- Installed at `millennium\plugins\dwmx\` (from `github.com/ejalxndr/dwmx`, pinned
  commit `28c1a17f533d0ae5e98745616e859548912898e0`, built locally with
  `pnpm install && pnpm build` using `@steambrew/ttc`; temp build dir under
  `%TEMP%\opencode\dwmx-build`).
- **Backend bug fixed** (`backend\main.lua`): `ULONG_PTR`, `LONG_PTR` and `SIZE_T`
  were declared 32-bit, but Millennium's Lua VM is 64-bit (`millennium.luavm64.exe`).
  That mis-laid-out `PROCESSENTRY32W`, so the executable name was read from the wrong
  offset, `find_pids_by_name("steamwebhelper.exe")` returned nothing and
  `PatchAllWindows` returned `false`. Types are now 64-bit.
- **Effect fixed:** the primary call is again the legacy acrylic accent
  (`ACCENT_ENABLE_ACRYLICBLURBEHIND`, state 4, flag `0x20`), because
  `DWMWA_SYSTEMBACKDROP_TYPE` is a no-op on this build (25H2, 26200) for Steam's
  opaque CEF windows. The DWM backdrop is kept only as a fallback.
- Rounded corners are skipped on maximized windows (`IsZoomed` ->
  `DWMWCP_DONOTROUND`), which removes 1px edge lines over the backdrop.
- `on_load` now calls `PatchAllWindows` so the main window is patched at startup.
- **Frontend fixed** (`frontend\index.tsx`, rebuilt): `PatchAllWindows` is called
  *after* `window.open` as well, retried at 0/100/300/800 ms, plus startup re-patches
  at 0.5/1.5/3/6/10 s. This is what gives context menus and popups the backdrop.
  `NEW_WINDOW_FLAG` changed from `274` to `4194576`
  (Resizable | Composited | TransparentParentWindow) so windows stay
  transparency-capable.

## 4. Catppuccin Mocha + blue accents, consistent frosted surface

- `themes\Steam\src\css\plugins\dwmx.css` now uses the official Catppuccin Mocha
  palette from `github.com/catppuccin/catppuccin` (palette.json v1.8.0):
  base `30,30,46`, mantle `24,24,37`, crust `17,17,27`, surface0 `49,50,68`,
  accents Blue `137,180,250` and Lavender `180,190,254`.
- `Mica Transparency` raised from `50` to `75` in `millennium\config\config.json`.
  At 50 the dark, high-contrast wallpaper showed through as bands/lines; at 75 the
  surface reads as one consistent frosted panel.

## 5. Chrome polish, second pass (same day)

- Bottom-left and top-right chrome read washed out and grey (Steam's default
  `rgb(139-169)` labels on a 75% base), so the chrome surfaces now use solid
  Mocha mantle at 92% (`--st-panel` / `--st-panel-opacity` in `dwmx.css`):
  `[class~="BottomBar"]` (sidebar user panel + downloads) and
  `[class~="TitleBarControls"]`.
- No hard outlines on chrome: first attempt added `inset 0 0 0 1px` rings to
  `BottomBar`, `Queue`, `TitleBarControls` and `AddShowcase`, which drew
  "cut-off" lines and a box around the downloads row (`.Queue` is nested inside
  `.BottomBar`, so two rings stacked). All rings removed; `Queue` is left
  transparent so the bar reads as one panel.
- "Add shelf" keeps a single very soft hairline
  (`inset 0 0 0 1px rgba(69, 71, 90, 0.25)`, Mocha surface1) plus a brighter
  fill on hover; same hover fill on Add a Game / download status.
- Chrome label text is now `subtext1` `186,194,222` instead of Steam's grey;
  hover text is `text` `205,214,244`.
- Verified live and by screenshot:
  `reports\2026-09-28-steam-chrome2-full.png`,
  `reports\2026-09-28-steam-chrome2-bottomleft.png`.
- Trap: `SteamClient.Browser.RestartJSContext()` closed the whole Steam client
  when called over CDP (all steam/webhelper processes exited). Restart Steam
  with `steam.exe -shutdown` + relaunch instead; that is also what reloads the
  persisted theme CSS.

## 6. Backdrop flatten: the last line, and the blur itself

Steam stacks backgrounds inside the library: window wrapper + content `Container`
+ each `ShowcaseOuter` shelf. With translucent theme colours that is **three**
alpha layers in the library (~98% opaque) against **two** in the sidebar (~94%):
the library painted darker, its edge showed as a hard vertical line, and nothing
looked see-through at all. Live probe confirmed
`ShowcaseOuter 0.75` over `Container 0.75` over `Wrapper 0.75`.

`dwmx.css` now makes the inner surfaces transparent so only the window wrapper
carries the tint:

```css
[class~="ShowcaseOuter"],
._3VQUewWB8g6Z5qB4C7dGFr,   /* library content Container */
._1ijTaXJJA5YWl_fW2IxcaT {  /* sidebar Container */
    background-color: transparent !important;
}
```

`Mica Transparency` then does real work: 75 -> **55**. Verified by a magenta-window
test behind Steam (strong bleed-through = genuine acrylic) and by the user.

Order of operations matters here: any new surface added inside the window must not
stack its own alpha over the wrapper, or the toned edge/line comes back.

## 7. Published: github.com/DavidHiFi/millennium-stuff

- Public repo, MIT (`LICENSE`), commit `b7d2999`, 190 files, ~8.6 MB.
  Layout: `themes/enhanced-space-theme/` (the fork, `metadata.json` removed so
  Millennium cannot update it back to the store build), `plugins/dwmx/` (built,
  drop-in), `plugins/dwmx-src/` (changed backend/frontend + `theme-dwmx.css`),
  `configs/millennium-config.example.json`, `docs/`, `NOTICE.md`,
  `install.ps1` (audit by default, `-Apply`, `-Apply -Configure`).
- Provenance recorded in `NOTICE.md`: SpaceTheme `ed560f2b`, DWMX `28c1a17f`.
- Built from a temp checkout at `%TEMP%\opencode\millennium-stuff` and pushed with
  `gh repo create --source . --push`.

## 8. Modal flatten, and the fork becomes its own theme (later 2026-09-28)

- Modal dialogs had the same stacked-alpha problem as the library: the tab strip,
  the content and every section row each painted their own 55% layer (probe:
  `PagedSettingsDialog` base 0.55 with `DialogContent_InnerWidth` mantle 0.55 and
  base/mantle rows inside), which read as rectangles in the Millennium settings
  dialog. Now the dialog is one solid surface
  (`.PagedSettingsDialog` / `.ModalPosition_Content` at 92% mantle) and
  `.DialogContent_InnerWidth`, the tab strip, `.DialogBody > .Panel`,
  `.DialogSubHeader`/`.SettingsDialogSubHeader` and the row/description rows are
  transparent. Theme-item hover keeps a soft fill.
- **Mocha Steam**: the fork was duplicated to
  `millennium\themes\MochaSteam` and is now the active theme
  (`themes.activeTheme = MochaSteam`). `skin.json` -> name `Mocha Steam`, author
  `DavidHiFi`, `github` = DavidHiFi/millennium-stuff, SpaceTheme's kofi/discord
  fields dropped. Its options were copied in the config under the `MochaSteam`
  condition key plus `themeColors.MochaSteam`, so `Font`, `Mica & Acrylic plugin
  support` and `Mica Transparency 55` carry over. No `metadata.json`, so Millennium
  treats it as a local theme and will not update it from the store.
- **SpaceTheme restored to stock** in `millennium\themes\Steam` from
  `codeload.github.com/SpaceTheme/Steam/zip/ed560f2b...` plus its original
  `metadata.json`, and it is not active. Verified stock: name `SpaceTheme for
  Steam`, author `SpaceEnergy`, original grey `dwmx.css`, the `content: "Space"`
  label rules back, no FiraCode font option. If it is ever re-enabled it behaves
  like a normal store theme.
- Repo updated to match: `themes/mocha-steam` (the old `enhanced-space-theme`
  folder is gone), README/NOTICE/`docs/mocha-steam.md` renamed, and `install.ps1`
  now installs to `themes\MochaSteam`, sets `activeTheme`, copies the options and
  never touches a SpaceTheme install. Commit `7c2e9fb`.
- Steam CEF input note: synthetic CDP clicks work for Steam's own menus, but the
  Millennium settings dialog can be re-hosted in another target while probing, so a
  one-shot DOM probe can report `no-el` even though the dialog is fine - wait for
  the element in the expression instead.

## 9. Release v1.0.0 published (later 2026-09-28)

- `https://github.com/DavidHiFi/millennium-stuff/releases/tag/v1.0.0` - packaged zip
  (`millennium-stuff-v1.0.0.zip`, 5.74 MB, `git archive` of HEAD `682420a`): theme,
  built plugin, patched sources, installer, configs, docs. Asset verified HTTP 200.
- Repo description updated, topics `catppuccin, millennium, steam, theme`, README
  got download links (release, theme folder, clone), MIT license detected.
- Trap (again, same as the Windhawk thread): `gh release create` without `-R` inferred
  the repo from the shell's working directory and briefly created the release in the
  workspace's GitHub twin `DavidHiFi/system-configuration` instead. Deleted with
  `gh release delete v1.0.0 -R DavidHiFi/system-configuration --yes --cleanup-tag`;
  the pre-existing draft release there (2026-09-20) was left as it was, no tag
  remains. Always pass `-R <owner>/<repo>` for gh commands that touch a repo other
  than the current directory's.

## Notes and gotchas

- Steam's CEF runs with `--remote-debugging-port=8080`, so the live client can be
  inspected and driven over CDP. Helper: `scripts\Steam-CdpEval.mjs`
  (`--match main|SharedJSContext --expr "..."`, `--method`/`--params` for raw CDP,
  `--list`). Plugin backends are callable from the SharedJSContext page:
  `Millennium.callServerMethod("dwmx", "PatchAllWindows", [])`.
- `scripts\Steam-WindowAcrylic.ps1` (`-Mode Audit|Accent4|Accent3|Acrylic|Mica|Reset`)
  is the manual/diagnostic version of the same window effects.
- An accent set before a window's composition target exists is dropped, and a window
  keeps a stale look until it repaints. That is why DWMX now re-patches on a timer.
- Theme updates from the Millennium store overwrite `themes\Steam\...`; DWMX is a
  local build, so the store will not update it. Re-apply from this note if needed.

## Rollback

1. Plugins: delete `C:\Program Files (x86)\Steam\millennium\plugins\dwmx`, remove
   `"dwmx"` from `plugins.enabledPlugins` in `millennium\config\config.json`.
2. Theme: copy back from `backups\2026-09-28-millennium-spacetheme\`
   (`theme-titlebar.css` -> `src\css\steam\titlebar.css`, `theme-skin.json` ->
   `skin.json`, `theme-dwmx.css` -> `src\css\plugins\dwmx.css`; delete
   `options\fonts\firaCodeNerdFont.css` and its `skin.json` entry to drop the font
   option).
3. Config: restore `millennium-config.json` (font, Mica Transparency, plugin list)
   with Steam stopped.
4. Restart Steam. Nothing outside the Steam install was changed; no system settings,
   no graphics/display registry keys.

## Addendum (later on 2026-09-28): Mocha Steam is the live theme, stock Space untouched

- The self-owned rename landed as `themes\MochaSteam` (author DavidHiFi, repo
  `DavidHiFi/millennium-stuff` v1.0.0). `millennium\config\config.json`
  `themes.activeTheme = "MochaSteam"`; options/themeColors entries carried over.
  Steam restarted and visually verified:
  `reports\2026-09-28\steam-mocha-steam-theme.png`.
- A parallel duplicate (`themes\mocha-steam`, from another thread's copy of this
  work) was created and removed the same day; `themes\Steam` (stock SpaceTheme)
  is untouched and only `themes\MochaSteam` is active.

## 10. Audit pass: sidebar seam, Mocha edges, real frost on floating surfaces

**2026-09-28 (evening), live theme `C:\Program Files (x86)\Steam\millennium\themes\MochaSteam`.**
Evidence: `reports\2026-09-28\mocha-live-before.png`, `mocha-live-after.png`,
`mocha-live-final.png`, `mocha-hover-final.png`.

### Root causes found

- **The "line that cuts off and fades"** above the game list was the library
  sidebar painting three different surfaces: the top block (Home + Games and
  Software + search) at `--st-color-2` over the window wrapper, the game list
  container deliberately transparent (the 2026-09-28 flatten in `dwmx.css`),
  and the bottom chrome (`BottomBar`, `TitleBarControls`) at 92% mantle. The
  tint stopped dead at the search block and the block's own `::after` divider
  read as the hard cut. It also depended on how many alpha layers the acrylic
  happened to be compositing, which is why it came and went.
- **Flat "lowered opacity" surfaces**: Steam paints several floating surfaces
  with a translucent fill and no filter. They are all real `backdrop-filter`
  frosted panels now: context menus, tooltips, combobox chips and their popup,
  the game-cover hover popup (`AppPortraitHover`), notification toasts.
- **Console page** was Steam's default teal panel with square corners.

### Changes (files)

- `src/css/regular.css` - shared tokens (`--st-base/mantle/crust`, surface0-2,
  `--st-sidebar-bg`, `--st-glass`, `--st-glass-blur`, `--st-edge`) plus the
  frosted rules for tooltips, combobox chips/popups, caption strip and notice
  buttons, and the `AppPortraitHover` hover popup. Tokens live here, not in
  `root.css`: Millennium regenerates the `RootColors` style tag from the config
  theme colors, so additions to `root.css` are not injected as CSS.
- `src/css/steam/sidebar.css` - one continuous sidebar panel on
  `._3x1HklzyDs4TEjACrRO2tB` (55% mantle + `--st-edge` ring), inner surfaces
  flattened, the search block's `::after` divider removed, `--st-edge` rings on
  the Home pill / dropdown / filter pills / search input / bottom icon buttons /
  account row, the SpaceTheme logo next to HOME hidden, the collections grid
  icon lifted to surface1/2 so it is visible, and the downloads chip matched to
  the account chip (388 wide at x22, 44 tall, 6px gap).
- `src/css/plugins/dwmx.css` - `BottomBar` keeps the account-chip fill,
  `TitleBarControls` is clear so it does not stack, both get the Mocha edge;
  "Add shelf" edge strengthened and frosted.
- `src/css/menu.custom.css` - menu surface is `--st-glass` + 20px blur + 1px
  edge instead of a 3px 55% box with no filter.
- `src/css/notifications.custom.css` - toast surface frosted.
- `src/css/steam/consolePage.css` (new) + import in
  `src/css/libraryroot.custom.css` - Console panel rounded on all four corners
  and painted Mocha.

### Notes

- Millennium does **not** hot-reload theme CSS; `steam.exe -shutdown` + relaunch
  is what applies edits. Live iteration was done by injecting a `<style>` over
  CDP (`scripts\Steam-CdpEval.mjs` or the scratch probe) and comparing.
- Steam's CEF target only answers `Page.captureScreenshot` while the Steam
  window is restored; throwaway restore helper used during the pass.
- Repo mirror: the changed files were copied into
  `work\millennium-stuff\themes\mocha-steam` (clone of `DavidHiFi/millennium-stuff`).
  That working tree also carries an uncommitted `overlay.custom.css` change from
  another thread (the experimental-overlay warning removal) — do not bundle it
  blindly into a commit.
