# Explorer Font Changer by DavidHiFi

A fork of Gabriela Cristei's Explorer Font Changer 0.2, rewritten to preserve
Windows icon fonts and restore GDI drawing state after each call. The original
source remains in `mods/catalog/explorer-font-changer.wh.cpp`.

The fork changes GDI and themed text and both DirectWrite layout creation paths.
It preserves symbol font families, `SYMBOL_CHARSET`, private-use character runs,
surrogate pairs, pre-shaped glyph indices, vertical `@` faces, and custom font
collections that do not contain the target font. DirectWrite format objects stay
unchanged, so a shared format can still create an icon layout with its original
family.

Weights named in a face, such as `Segoe UI Semibold` or `Segoe UI Black`, carry
over to the new font in both GDI and DirectWrite. Invisible direction marks,
such as the ones Explorer puts around every date, do not force the original
font. Visible characters the new font lacks still fall back to the original
font for that run. If GDI does not know the family name, the original font stays
selected instead of a third font the mapper picks.

## Changes

- 1.0.1: Explorer dates and times now use the new font. Legacy weight names keep
  their weight. Vertical fonts and unknown GDI names keep the original font.
- 1.0.0: First fork. Icon and symbol fonts preserved, selected-font lifetime
  fixed, and GDI, themed text and DirectWrite coverage added.

The default include list covers Explorer, Start, Search, Windows shell hosts,
and Settings. It does not change every application. Some XAML controls set their
own fonts after layout creation, and existing cached layouts
can remain until the control recreates them.

## Install

Disable the catalog Explorer Font Changer. Create a new Windhawk mod, paste
`explorer-font-changer-davidhifi.wh.cpp`, and compile it. Select an installed
font family in its settings. FiraCode Nerd Font is the default. Empty or `None`
keeps the original font. Disable this fork and re-enable the catalog mod to
return to the previous setup.

Glow is omitted. The original glow path did not preserve bounded text buffers
or all DrawTextEx parameters. No Windows font registry substitutions are changed.

## Build and test

Run `Build.ps1 -Test` with Windhawk installed. It builds x64 and x86 DLLs and
runs the x64 API regression executable. Production DLLs use Windhawk imports.
The test executable uses editor stubs for the Windhawk callbacks and invokes
the replacement functions against actual GDI and DirectWrite APIs.

The tests check text substitution, icon and PUA preservation, matching text
measurements, DrawTextEx output parameters with a bounded buffer, settings-off
behavior, date strings with direction marks, weight carry-over, vertical and
unknown faces, DirectWrite format reuse, and GDI handle counts over 10,000
calls.
These checks do not establish visual correctness in every Windows control.

MIT license for the rewritten implementation. Credit to Gabriela Cristei for
the original mod and to the Windhawk maintainers for the mod API.
