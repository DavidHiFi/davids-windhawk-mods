# Styler 2.0.13 — settings descriptions fixed and reworded

Date: 2026-10-09
Range: 2.0.12 → 2.0.13 (`local@windhawk-styler`, dll
`local@windhawk-styler_2.0.13_915768.dll`). Text-only release: no code paths
changed.

## Root cause of the truncated descriptions

Windhawk parses the `==WindhawkModSettings==` block as YAML. In YAML,
` #...` mid-line starts a comment. The shipped descriptions contained
`in #RRGGBB format` unquoted, so the engine parsed:

- `Background color` → "Main background tint, in" (everything from `#` dropped)
- `Title bar color` → "Solid fill for the title bar strip," (same)

The source text was complete; the truncation happened at parse time, before
the UI ever saw it. Every description is now double-quoted (`$description:
"..."`), which installed mods like `explorer-title-bar-label` and
`local@taskbar-system-info-weather` already use, so `#RRGGBB` survives.

## Changes (source `work\windhawk-styler\tauri20\windhawk-styler.wh.cpp`)

- Quoted every `$description` value.
- Fixed the two `#`-truncated descriptions (above).
- Added a description for `Background blur` ("The backdrop behind the
  interface. Acrylic is the frosted Windows 11 material") and gave
  `Text color` a first clause ("Interface text, including the title bar").
- Reworded the long acrylic-title-bar and native-title-bar descriptions into
  short plain sentences; "Blank keeps no caption fill" became "Blank uses
  Windows' own color" (accurate: blank sets `DWMWA_COLOR_NONE`).
- Reordered settings: background trio first, then the title-bar trio
  (`Native title bar`, `Acrylic title bar`, `Title bar color`), then cards,
  controls, accent, text and font. Values are keyed, so nothing moved in the
  registry.
- Version bump to 2.0.13 only as a reload carrier for the metadata.

## Verified (measured)

- Compiled and installed: 2.0.13 (
  `scripts\2026-10-09-styler-descriptions.ps1 -Install`, engine lock held),
  include `windhawk-ui.exe`, DLL loaded in both windhawk-ui processes
  (`-Audit`).
- Descriptions read back from the rendered settings page through the mod's
  own CDP port (9333), per setting row (`reports\2026-10-09-styler-descriptions\settings-dom.json`):
  all twelve render complete, both `#RRGGBB` descriptions display in full,
  and the new order is what the DOM shows. Screenshot:
  `reports\2026-10-09-styler-descriptions\settings-after.png`.
- No settings values were touched: install-time registry backup
  (`backups\2026-10-09\styler-descriptions\mod-key.reg`) matches the live
  values (`backgroundColor #1e1e2e`, `backgroundOpacity 60`, `blur acrylic`,
  `cardOpacity 90`, `fontFamily FiraCode Nerd Font`) and `SettingsChangeTime`
  (1791485839) is identical before and after. The user's screenshot showed
  typed-but-unsaved UI edits; the saved state was already defaults for those
  three before this change.

## Latent bug elsewhere (not fixed here, unfixed on purpose)

Same unquoted-`#` truncation exists in other installed mods:
`explorer-glyphs-colorizer.wh.cpp` lines 135-137 (`RGB hex color, such as
#FF8C00...` renders truncated) and `file-operation-styler.wh.cpp` lines 156
and 180. Worth a text-only hotfix wave someday.

## Rollback

`H:\Windhawk Configuration\scripts\2026-10-09-styler-descriptions.ps1
-Rollback` (elevated) restores the 2.0.12 sources from
`backups\2026-10-09\styler-descriptions` and recompiles.
