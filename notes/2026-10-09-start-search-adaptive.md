# Compact Start menu with Everything results

Applied on 2026-10-09 at 5:45 AM AWST. Owner verified all four behaviors: compact idle menu, expansion when searching, collapse when clearing the query or pressing Escape, and clean footer icons.

This replaces the fixed-height behavior recorded in `2026-10-09-start-search-compat.md`.

## Changes

Built local Everything 1.0.2 from the clean gallery 1.0 source. Added an event-driven MaxHeight storyboard on the existing `FrameRoot`, with a 160-DIP idle limit and 640-DIP search limit. The existing start-menu-size settings still choose the expanded 750-by-500 size. Reveal, hide, activation, close, and teardown handle the size state. Stopping the storyboard restores the base theme value. The frame keeps its name and theme matching. No polling timer, native window resizing, or background recovery process was added.

The storyboard holds its value at XAML's animation precedence, above local values from Start Menu Styler and start-menu-size. Microsoft's dependency-property documentation confirms this precedence. Saved reference: `reports/2026-10-09-start-search-adaptive/dependency-properties.md`.

Corrected theme rule `controlStyles[21].styles[0]` from a four-glyph Text value to one U+E7E8 glyph. The other footer icons remain separate controls. Colors, blur, borders, and other theme settings remain intact.

Installed `local@start-everything_1.0.2_710101.dll` and copied the gallery settings. Disabled the original gallery mod, retaining it for rollback. The local source preserves the upstream GPL-3.0 license, author credit, and preview. Independent module enumeration confirmed the local DLL and Start Menu Styler loaded together in StartMenuExperienceHost. The owner then confirmed all four visual checks.

## Recovery

Script: `scripts/2026-10-09-start-search-adaptive.ps1`, with `-Audit`, `-Install`, and `-Rollback`. Run mutations elevated through `H:\System Configuration\scripts\Invoke-Elevated.ps1`.

Backups: `backups/2026-10-09/start-search-adaptive/`. Registry exports cover the original gallery mod, theme, and any pre-existing local fork. The script saves any pre-existing local source and original values. Rollback disables the new local build and restores those exports and source. The rollback point is the earlier working fixed-size configuration, before this adaptive follow-up.

Receipt and build inputs: `reports/2026-10-09-start-search-adaptive/receipt.json` and `work/start-search-adaptive/`. DLL SHA256: `D15936EFEBEEF49ACBE6EA163FEFDA8C91BA898F04D8413652B5FB03D144C786`.

No full engine or Explorer restart was performed. No restart is pending. Reboot persistence was not separately tested; the local installation and theme correction are saved on disk and in the registry.
