# Windhawk Styler 2.0.35: list-view table theming (2026-10-11)

## Symptom

In the Windhawk 2.0 (Tauri/antd) UI, the installed-mods LIST view stayed default
gray while grid cards were already themed. Windhawk hard-codes table colors
(.ant-table bg rgb(20,20,20), thead rgb(29,29,29), borders rgb(48,48,48)) and the
styler's injected CSS had no .ant-table rules.

## Root cause

BuildCss never emitted table selectors, so the antd defaults showed through.

## Fix (in `work/styler-release`, ported to `davids-windhawk-mods`)

- New .ant-table rules in BuildCss in
  `mods/local/windhawk-styler/windhawk-styler.wh.cpp`: card-color surface and
  borders, 3% white header overlay, 4% row hover, expanded-row/filter-trigger
  overlays, text color block, accent rules for active sorters and selected rows,
  backdrop-filter blur(24px) when cardOpacity < 100.
- Version 2.0.34 -> 2.0.35, README bullet updated.
- Build.ps1 now links -lws2_32 -ladvapi32 -luxtheme (were missing).

Commits: release worktree `40ba725`, main `1d311f2` (cherry-pick; only the three
styler files staged, the other thread's taskbar-audio-visualizer edits untouched).

## Install

- DLL `C:\ProgramData\Windhawk\Engine\Mods\64\local@windhawk-styler_2.0.35_123813.dll`
  (157696 bytes, sha256 B6C75C06...AF6EB5), ModsSource updated, registry read back:
  Version=2.0.35, SettingsChangeTime=1791693493.
- Backup + receipt: `backups\2026-10-11\styler-listview\` (reg export, 2.0.34 source
  copy, receipt.json).

## Verification (live UI, CDP port 9333)

- `#wh-styler-style` contains
  `.ant-table{background-color:rgba(24,24,37,0.900)...}` (rgba, not opaque rgb,
  because this machine uses 90% card opacity).
- Computed `.ant-table` background: `rgba(24, 24, 37, 0.9)` = card color #181825.
- Computed `.ant-table-thead .ant-table-cell` background:
  `rgba(255, 255, 255, 0.03)`. All checks pass.
- Screenshot: `reports\2026-10-11-styler-listview\styler-2.0.35-listview.png`
  (themed navy surfaces, lavender text, blue accents confirmed by eye).

## Environment notes (learned the hard way)
- The CDP port only opens if `--remote-debugging-port=9333` is in the UI
  process's environment BEFORE its WebView2 browser child spawns. The mod seeds
  it in Wh_ModInit, but that loses the race on some launches.
- `Invoke-Elevated.ps1` drops the caller env through its .cmd hop: setting
  `$env:WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS` inside the elevated script did NOT
  propagate (browser had no flag, CDP down). It also hangs the caller past 180s
  even on success; read the result from its log file instead of waiting.
- Reliable launch: set the env var in your own shell, then non-elevated
  `Start-Process 'C:\Program Files\Windhawk\windhawk-ui.exe'` (runs fine;
  2 flagged webviews, CDP up). Kill a running UI first (single instance).
- `scripts\2026-10-11-styler-listview-cdp.ps1 -Expression "<js>"` is the probe.
- pwsh cannot create files under H:\ (sandbox); the reports copy went through
  `Invoke-Elevated.ps1 -Command "Copy-Item ..."`.

## 2.0.36: rounded element corners (same day, user request)

- New settings in the mod's Settings tab: **Rounded element corners** (on/off,
  default on) and **Corner radius** in px (default 8, clamped 0..32). Off leaves
  Windhawk's stock squared look.
- Implementation in BuildCss: one radius shared by cards, tables (wrapper plus
  the four corner cells), dialogs/drawers/popovers/dropdowns, buttons and
  inputs. Emitted only when on and radius > 0.
- Commits: release `907c9db`, main `000de9d` (cherry-pick; only the two styler
  files).
- Install: DLL `local@windhawk-styler_2.0.36_135051.dll` (160256 bytes, sha256
  C0B481E9...416E6C), ModsSource updated, registry Version=2.0.36,
  SettingsChangeTime=1791697851. Backup + receipt: `backups\2026-10-11\styler-corners\`.
  New keys seeded in `...\Settings`: roundedCorners=1, cornerRadius=8 (DWORD).
- Verification (live UI, mod's own save-relaunch each round):
  ON: style tag has `border-radius:8px`, computed radius 8px on .ant-table,
  .ant-card and .ant-btn. OFF (roundedCorners=0): no border-radius rules at all.
  Back ON: `RADIUS-8-OK TABLE-OK 8px`. List theming intact throughout.
- Screenshot: `reports\2026-10-11-styler-listview\styler-2.0.36-corners.png`.
- Note: `Invoke-Elevated -Command` with `$k\Settings` interpolation failed
  before running (exit 1, quoting trap); the same commands in a `-File` script
  worked. `Invoke-Elevated` hangs past 180s on UI-launch scripts but returns
  promptly on quick admin scripts.

## 2.0.39: shared surfaces, accent and scroll fixes (same day)

The follow-up pass fixed the remaining visual gaps across Home, Explore, Settings
and the More advanced settings dialog:

- The page root used a caption-height margin and calculated height, which let
  document content extend below the viewport. The scroll host also inherited
  hidden scrollbars. The root now fits between the title bar and viewport edge,
  and the host uses a thin inset scrollbar with a themed thumb.
- Windhawk and Ant Design supplied independent colors for focused controls,
  selected items, links and status controls. BuildCss now sets the shared primary,
  link and focus variables and styles the common Ant controls from the selected
  accent color.
- The card color previously missed collapsible Advanced settings and several
  floating surfaces. Cards, tables, collapse panels, dialogs, menus and related
  surfaces now share the card color and receive blur when translucent.
- Nested table borders, row backgrounds and collapse children painted square
  edges over rounded parents. The style now removes duplicate table borders and
  clips inner painting to the rounded surface.

## Install and backup

- Version **2.0.39** is live. DLL:
  `C:\ProgramData\Windhawk\Engine\Mods\64\local@windhawk-styler_2.0.39_145520.dll`
  (174592 bytes, SHA256 `0C938A7FBB0215BEAC30612B709EC513DF8D09008EBEA3F14B986E0EB5293FE7`).
  Installed source SHA256: `6D14E0726266326EC98246CF685032B5E2B74820AF4417F08050D0F01FF6AF53`.
  Registry readback: Version `2.0.39`, SettingsChangeTime `1791701720`.
- Backup and receipt: `backups\2026-10-11\styler-theme-consistency\` (registry
  export, installed 2.0.38 source, pre-install source copy and JSON receipt).
  Audit/install/rollback helper:
  `scripts\2026-10-11-styler-theme-consistency.ps1`.
- Release commit `cd32dfb`; cherry-picked to main as `e44ca4b`. Only the Styler
  source and README were committed. The main checkout's taskbar-audio-visualizer
  edits remain uncommitted and untouched.

## Verification (live UI, CDP port 9333)

- Home list still reports Windhawk Styler `2.0.39`. The injected table has the
  card surface `rgba(24,24,37,0.900)`, 16px blur, and the 3% white header overlay.
- Focused search border pixels in the captured screen are the configured accent
  `rgb(137,180,250)`. The switches and selected Home tab use the same accent.
- The document height equals the viewport (1097px). The inner scroll host ends
  at the viewport boundary and uses a thin scrollbar. Computed table and dialog
  corners are 16px; table, Advanced settings and More advanced settings surfaces
  use the card color with blur.
- Screenshots reviewed and saved:
  `reports\2026-10-11-styler-listview\styler-2.0.39-list-view.png`,
  `reports\2026-10-11-styler-listview\styler-2.0.39-settings-advanced.png`,
  and `reports\2026-10-11-styler-listview\styler-2.0.39-more-advanced-dialog.png`.

## 2.0.40: single search focus ring and rounded table header corners (same day)

The 2.0.39 pass left two polish bugs, both visible on the Home list:

- The Home search bar painted a doubled blue focus ring. The input sits inside
  an antd affix wrapper, which owns the focus ring, but the nested input still
  painted its own accent border and halo on top (the 2.0.39 focus rules match
  both elements).
- With rounded element corners on, the table header's corner cells stayed
  square. The 2.0.36 rule zeroed every first-row corner radius, so the header
  cell backgrounds painted square corners over the table's rounded surface as
  dark notches.

Fix in BuildCss:

- `.ant-input-affix-wrapper>.ant-input:focus` and `:focus-visible` get
  `border-color:transparent; box-shadow:none; outline:none`, leaving the
  wrapper's single accent ring: `rgb(137,180,250)` border plus the 2px
  `rgba(137,180,250,0.2)` halo.
- The thead first-row corner cells now take the configured radius with
  `background-clip:padding-box`, matching the table's 16px; the tbody
  last-row corners and collapse stay 0.

## Install and backup (2.0.40)

- Version 2.0.39 -> 2.0.40, built 64+32-bit via
  `scripts\2026-10-11-styler-build-2040.ps1` (log:
  `backups\2026-10-11\styler-search-corners\build-log.txt`, only the benign
  winsock2 include-order warning). `build\windhawk-styler-64.dll` is 175104
  bytes, SHA256 `EBD70E15CD985BB352BE0EDDFC873D64AB80A81B8B351BA83CD96987DC78DF82`.
- Installed: `C:\ProgramData\Windhawk\Engine\Mods\64\local@windhawk-styler_2.0.40_160630204.dll`
  (175104 bytes), ModsSource updated, registry readback Version `2.0.40`,
  SettingsChangeTime `1791705990`.
- Backup + receipt: `backups\2026-10-11\styler-search-corners\` (registry
  export, installed 2.0.39 source, worktree 2.0.40 source, receipt.json, and
  the build/install/screenshot/commit/pick logs from this session).
- Release commit `9b323e3`; cherry-picked to main as `0efb076` (blob parity
  `2899993`). Only the Styler source was committed; the main checkout's
  taskbar-audio-visualizer edits remain uncommitted and untouched.

## Verification (live UI, CDP port 9333)

- Home list (`#/`) renders the themed table: `.ant-table` background
  `rgba(24, 24, 37, 0.9)`, and both thead corner cells report 16px matching
  the table's 16px with `background-clip: padding-box`.
- Search focus check in ONE evaluate (`.focus()` plus computed styles): the
  nested input reports `border-color: rgba(0, 0, 0, 0)` and `box-shadow:
  none`; the wrapper reports the single accent ring
  `rgba(137, 180, 250, 0.2) 0px 0px 0px 2px`. The app blurs the search input
  when its window is background, so focus and the style read must share one
  evaluate, right before the capture.
- Screenshot: `reports\2026-10-11-styler-listview\styler-2.0.40-search-corners.png`
  (one blue ring around the search bar, rounded header corners without dark
  notches, Windhawk Styler row showing 2.0.40). Captured with
  `scripts\2026-10-11-styler-search-corners-shot.ps1`, which finds the UI
  window by title, restores it if minimized, foregrounds it, focuses the
  input over CDP, and captures the window rect in one run.

Environment notes: `Get-Process windhawk-ui` intermittently returns nothing
from sandboxed non-elevated shells while the UI and its CDP port are fine
(netstat shows port 9333 held by the WebView2 child, msedgewebview2). The
`#/mods-browser` route renders mod cards; the themed list table lives on Home
(`#/`), reached by clicking the Home nav button. Spawned-process writes under
H:\ stay blocked, so the report copy, the release commit and the cherry-pick
all went through the elevated hop.
