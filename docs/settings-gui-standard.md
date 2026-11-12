# Universal settings window for our Windhawk mods

Owner decision, 2026-11-11: every Windhawk mod we make that has its own settings window uses
this one design. It covers the layout, the look, the options and the About page. Today that
means Seamless Launchpad, Seamless Dictate and Seamless Clipboard Manager. Any new mod with a
settings window starts from this design. Do not invent a different one.

Reference implementation (copy from this, never rewrite from scratch):
`davids-windhawk-mods\mods\local\seamless-launchpad\seamless-launchpad.wh.cpp`, version 2.4.3
or later. The engine is the `Set_*` family: `SetWindow`, `SetPaint`, `Set_MakeFields`,
`kSetPages`, `Set_Draw*` and `Set_Create`. Each mod keeps its own field table, pages and About
text. The engine code and every look value stay identical.

## Layout

- The window is drawn with Direct2D on its own thread. It is never drawn on a mod's hook thread.
- Title bar: by default the window draws its own (mark and title centred, its own minimize,
  maximize and close). "Native Windows title bar" on hands the whole title bar and its buttons
  to Windows, so title bar mods style it like any other app. Nothing else turns the native
  title bar on, and there is no in-between mode. Maximize, restore and snap work in both.
  (Changed 2026-11-12: the old "Title bar buttons" option forced the native title bar on.)
- Left: a sidebar dock with rounded corners. It can be resized by dragging its edge. Hovering
  or dragging that edge lights up the dock's own rounded border, never a floating line. A
  panel button in the header collapses the sidebar to icons. Its width and collapsed state are
  remembered.
- The sidebar lists the pages with an icon and a name. About is always the last page, set
  apart by a divider and a small gap.
- Right: the page title, a one-line intro, then group headings in small caps. Each setting is
  a rounded row card with a name, a short description, and its control on the right.
- Controls: on/off switch, dropdown (popup list with a gradient ring), text box, number slider
  with its value, colour box and key-capture box.
- Footer: a floating pill dock at the bottom right, drawn inside the settings window. It is
  never a separate window, because a separate window showed square corners on screen. It holds
  the status line (unsaved count or message) and the buttons Reset to suggested, Cancel and
  Save. The page scrolls under it, and the last row can rise above it.

## Look (Catppuccin Mocha)

- Base #1E1E2E, mantle #181825, crust #11111B, surface0 #313244, surface1 #45475A,
  surface2 #585B70, overlay0 #6C7086, text #CDD6F4, subtext0 #A6ADC8.
- Hover and focus everywhere: a gradient from blue #89B4FA to mauve #CBA6F7. It is a faint
  gradient wash plus a gradient ring that fades in over about 120 ms. Every card that reacts
  to the pointer gets it: rows, sidebar items, value boxes, footer buttons, dropdown items,
  and the About header and Ko-fi cards.
- At rest, every card and box has a soft border (surface2 or overlay0), never none.
- Value boxes are filled #232434, between mantle and surface0, never black crust. They have
  an overlay0 edge at rest and the gradient ring on hover or while open. An editing text box
  uses the same fill.
- Row cards are base with a 32% surface0 wash, corner radius 10. Boxes use radius 8. The
  footer is a full pill.
- Glass mode uses the launcher grid's own material: accent acrylic with the grid's call
  (state 4, flags 2, colour 0x012E1E1E, so only the blur shows), full-window blur-behind and
  the frame extended, then crust painted flat at 55% over the whole page, title band included
  (no lighter fade under the title). Never the transient system backdrop, and never the old
  D82E1E1E acrylic tint: both read as a light grey slab. (Changed 2026-11-12.) Check every mod with `python scripts\settings-material.py check` before shipping (`stage <id> <out>` copies the reference glass in from the live Launchpad source), build on the installed source in ModsSource, and install with `scripts\Install-StagedMod.ps1`, which refuses if another thread changed the source since staging.

## Options every mod's settings window has

Put these in a group named "Settings window" on the mod's Look page (or its nearest
equivalent):

| Key | Name | Default |
|---|---|---|
| settingsGlass | Blurred settings window | on |
| nativeSettingsTitleBar | Native Windows title bar | off |
| settingsTrayIcon | Tray icon (click opens settings, right-click menu) | on |

Add the matching `$name` and `$description` lines to the mod's YAML settings block, and
default values to its install script.

## About page

- A header card with the mod icon, name, version and a one-line description. It gets the
  gradient hover.
- A support card: "Like it? Help the mod keep going", with the line "Free and open source. A
  tip on Ko-fi keeps it moving." and an Open Ko-fi button. It links to ko-fi.com/DavidHiFi
  and gets the gradient hover.
- Link rows: Ko-fi, source and credits.

## Proof before calling a port done

- Build offline first. Then install, checking that the mod's host process and Explorer stay up.
- Show still captures of the live window for every page, plus a hover proof in the test copy
  built with LP_TEST_HOVER. Find the test window by its process id, never by name.
- If the mod already had settings, every value it had must still load and save under the same
  key names.
