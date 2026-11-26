# Seamless Settings Styler (2026-11-26)

Owner asked: our own copy of the Settings styler, named Seamless Settings Styler, page
glass matching the title bar (asked before), full audit of the Settings window, highly
configurable, our edge recipe on everything, Catppuccin Mocha, a sidebar that folds to
icons, a Mocha blue+mauve Settings icon, a fully riced theme of our own.

## What was built

- Mod `local@seamless-settings-styler` (header `@id seamless-settings-styler`), 2.0.0,
  built on `local@settings-styler-plus` 1.4.1 (itself from m417z's Windows 11 Settings
  Styler). Work folder: `work\2026-11-26-seamless-settings-styler\`.
  - `theme.py` writes the three themes (main, sidebar fold, line icons) as C++.
  - `seamless.cpp` is our added code (colours from settings, title bar tint, fold,
    tree dump). `patch.py` joins them into `seamless-settings-styler.wh.cpp`.
- Page glass = Seamless Title Bars' caption material: raw host backdrop plus #1E1E2E at
  the title bar's own `uwp.tint` alpha (percent*255/100), read from
  `HKLM\SOFTWARE\Windhawk\Engine\Mods\local@seamless-title-bars\Settings` at load.
  Fallback tint 60 when that mod is off. Rule added to AGENTS.md, Traps section.
- Settings: theme, glass (style, match title bar, tint), colours (accent start/end,
  edge, text, subtext, base, card, card opacity, hover), edges (width, corner size,
  sidebar item edges), sidebar (fold button, start folded, remember fold, width, parts to
  hide when folded), Mocha line icons, tree dump.
- Settings icon: 28 gradient gear images in the uwp-assets-redirect-plus catppuccin
  Settings folder (backup beside it), done earlier in this job.

## Open items found while building

- Offline compile kept being refused for memory (other threads' builds, about 1 GB
  free); the first run that got through found one missing header (pop-up class), fixed.
  Clean compile 2026-11-26 (0 errors, 0 warnings, 405 s), `mod-consistency.py check
  --staged` consistent.

## State (left off here)

- Done: source, themes, settings, icon, clean compile, consistency check.
- Test PC was 12th in its queue; owner said "you make the decisions, skip the queue", so
  it installs straight on the tower (Settings only, one app, nothing in the shell).
- 3:08 pm: `local@settings-styler-plus` turned off, key saved as
  `work\...\settings-styler-plus.bak-20261126-1507.reg` and in
  `backups\settings-material\`.
- Install runs as a hidden one-shot task (`launch-install.ps1` through Invoke-Elevated,
  log `install-sss.log`). First try 3:08 pm: busy (free memory 3.7 GB). Second try
  3:19 pm: the CLI was killed at Install-StagedMod's 120 s limit while the compile (about
  7 minutes here) kept going; a DLL landed with no registry key. Third try 3:33 pm with
  `-TimeoutSec 900`. Trap: big mods need `-TimeoutSec` well past their compile time.
- 3:45 pm: third try installed v2.0.0 (DLL `..._123707.dll`), desktop fine after the
  60 s watch. Its publish step failed on a rebase; publish again after the retire PR.
  Install-StagedMod's default `-TimeoutSec` is now 900.
- 3:49 pm: old mod removed with `scripts\2026-11-26-remove-settings-styler-plus.ps1
  -Install` (source, DLLs and .reg in `backups\2026-11-26-remove-settings-styler-plus\`).
  Orphan DLL from try two gone, the install task deleted.
- 4:05 pm: retire PR https://github.com/DavidHiFi/seamless-workshop/pull/73 (old mod to
  `mods/retired/`, preset, preview and setup entries dropped, new readme). Portfolio has
  no Settings Styler card, nothing to change there.
- Live check of 2.0.0 found four things, fixed in 2.0.1:
  - Side menu icons landed on the wrong rows: the styler matches `[Content=X]` once when
    a row is made, but Settings reuses its rows. The glyphs are now set from code
    (`kPageGlyphs` in `seamless.cpp`) and follow each row's page name and selection.
  - The folded strip was 48 px and clipped rows (inner content is 40 wide). New setting
    `sidebar.foldedWidth`, default 64. The 60 px account picture spilled out; new
    setting `sidebar.shrinkPicture` (on) makes it 36 px round while folded.
  - The fold button had a white focus ring; now Mocha blue, plain colour.
  - The page drew its own extra shade over the glass (mantle at 0x40), so it was darker
    than the title bar. New setting `glass.pageShade`, default 0: page and title bar
    now use the same tint.
- 2.0.1: clean compile (95 s), consistency ok. Install 5:00 pm as an update
  (`-BaseHash` of the 2.0.0 source); new settings written by `install-sss.ps1`.
- 5:12 pm: 2.0.1 installed (DLL `..._2.0.1_354227.dll`), new settings in the registry
  (foldedWidth 64, shrinkPicture 1, pageShade 0, dumpTree 0). Published to main
  (commit 2c321a0). PR #73 rebased on it; manifest conflict fixed by dropping the old mod.
- 5:18 pm: dwm.exe crashed during another thread's Seamless Title Bars 1.3.19 install
  (quarantined by the gate) and Windows did not bring it back. Screen grabs are black and
  window capture fails without it, so the 2.0.1 live proof and preview wait. Tried
  Win+Ctrl+Shift+B (no effect). Asked the owner to sign out or restart.
- 6:50 pm: dwm.exe back (pid 14520). PR #73 branch caught up with main by a merge (no
  force push), readme 2.0.1 committed (362ac42, merge b7811fc), not pushed yet. Fourth in
  line for the desktop lock for the captures.
- 8:01 pm: 2.1.0 built (clean compile, consistency ok) and launched elevated as an
  update over 2.0.1. New: dark edged page buttons with gradient hover, one edge round
  open sections (expanders), dark list cards with a gradient hover edge set from code,
  darker sidebar rows, no line between menu and page (optional `edges.pageEdge`), folded
  icons centred, `sidebar.hideAccount`, `pages.hide[]`, and a `cleanup` group (carbon
  note, activation nag, promos on; help links off; free `hideText[]` list). cardOpacity
  default 90. Backup of the installer: `install-sss.ps1.bak-20261126-2010`.
- 8:14 pm: 2.1.0 installed and published (mods 9007af5, feed c9af40b). Live checks:
  carbon line gone on Windows Update, dark edged cards and buttons, page hiding works
  and undoes cleanly (Gaming hidden then back), fold recording clean
  (`liveec-fold-201835old.mp4`). Preview `media/previews/seamless-settings-styler.png`
  (account name painted out). PR #73 merged, branch and worktree deleted.
- Narrow window fault: the small search button sat on the wider "Settings" title with a
  white ring. Tried live with trial styles, then built in as 2.1.1 (margin 28,8,0,0, Mocha
  edge, gradient hover). Installer BaseHash now the 2.1.0 source (F78BC876...), backup
  `install-sss.ps1.bak-20261126-2035`. Install launched 8:26 pm.
- 8:35 pm: 2.1.1 installed and published (mods 5ab0946, feed d944678), desktop fine.
  Narrow capture `live\narrow-211.png`: search button clear of the title, Mocha edge.
  Something snaps the Settings window back to its old place within a second, so narrow
  captures hold the size from a loop while PrintWindow runs.
- 8:39 pm: `sidebar.hideAccount` was off (default false), so the account block still
  showed. Turned on for the owner (`live\acct-on.ps1`, elevated); proof
  `live\acct-off.png`. Presets republished (mods 86a0eb2, feed 00e5cea).
  Rollback: set `sidebar.hideAccount` to 0 and bump SettingsChangeTime.
- Portfolio: mods appear only through the Workshop card, nothing to change.
- Left: hover glow proof needs the desktop lock (queued behind the FPS overlay proof;
  the owner was active at 8:40 pm). Card hover is set from code, so a forced style
  cannot stand in for it.
- Done earlier, kept for history: live captures (icons per row, folded strip, picture, focus ring, glass check,
  corners, fold recording), preview PNG into PR #73, merge, delete branch and worktree
  `D:\Agent Work\2026-11-26-sss-retire` (uncommitted: mods/README 2.0.1, readme line).

## Rollback

- `scripts\2026-11-26-remove-settings-styler-plus.ps1 -Rollback` (elevated) puts the old
  mod back from its backup; then turn `local@seamless-settings-styler` off with
  `scripts\Set-ModState.ps1 -Id local@seamless-settings-styler -Off`.
