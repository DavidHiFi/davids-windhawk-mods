# Universal settings window for our Windhawk mods

Owner decision, 2026-11-11: every Windhawk mod we make that has its own settings window uses
this one design. It covers the layout, the look, the options and the About page. Today that
means Seamless Launchpad, Seamless Dictate and Seamless Clipboard Manager. Any new mod with a
settings window starts from this design. Do not invent a different one.

Reference implementation, the template (copy from this, never rewrite from scratch): the
installed Seamless Launchpad source, `C:\ProgramData\Windhawk\ModsSource\local@seamless-launchpad.wh.cpp`,
version 2.5.0 or later. The engine is the `Set_*` family: `SetWindow`, `SetPaint`,
`Set_MakeFields`, `kSetPages`, `Set_Draw*` and `Set_Create`. Each mod keeps its own field table,
pages and About text. The engine code and every look value stay identical.

## Keeping every mod in sync with the template (since 2026-11-12)

A template edit must reach every mod. `scripts\settings-engine.py` does it, with
`docs\settings-engine.json` listing what each mod may differ in.

- Change the engine in Launchpad first, then install Launchpad.
- `python scripts\settings-engine.py check` lists every mod that is behind.
- `python scripts\settings-engine.py sync <id> --out <dir>` writes the mod brought up to the
  template (version bumped). It copies every engine function, struct member, constant and the
  standard row descriptions. For a function the mod changed on purpose ("owned"), it merges the
  template's edit into the mod's version, like git. Only where both edited the same lines does
  it say "port by hand"; then port it and run `rebaseline <id> <Set_Fn>`.
- Compile, then install with `scripts\Install-StagedMod.ps1`. The installer runs the check and
  refuses (exit 4) a mod whose settings window is behind the template.
- A new mod: copy the engine from Launchpad, then `settings-engine.py add <id>` (before its
  first install: `add --staged <file>`).
- Mods built by a generator folder (`scripts\settings-engine-sync.py`): run its `adopt` after a
  sync, or the next generator build undoes the sync.

## Layout

- The window is drawn with Direct2D on its own thread. It is never drawn on a mod's hook thread.
- Title bar: by default the window draws its own (mark and title centred, its own minimize,
  maximize and close). "Native Windows title bar" on hands the whole title bar and its buttons
  to Windows, so title bar mods style it like any other app. Nothing else turns the native
  title bar on, and there is no in-between mode. Maximize, restore and snap work in both.
  (Changed 2026-11-12: the old "Title bar buttons" option forced the native title bar on.)
- The native title bar and glass switches apply the moment Save is pressed (`Set_ApplyFrame`),
  and again when settings change from outside. Never "reopen to apply".
- Left: a sidebar dock with rounded corners. It can be resized by dragging its edge. Hovering
  or dragging that edge lights up the dock's own rounded border, never a floating line. A
  panel button in the header collapses the sidebar to icons. Its width and collapsed state are
  remembered.
- The sidebar lists the pages with an icon and a name. About is always the last page, set
  apart by a divider and a small gap.
- Right: the page title, a one-line intro, then group headings in small caps. Each setting is
  a rounded row card with a name, a short description, and its control on the right.
- Pages that list things (installed mods, a catalogue or marketplace, modules, presets) use the
  whole page width, never one narrow centred column (owner, 2026-11-20). The items are cards in
  a fluid grid: as many columns as fit (minimum card width about 300 px at 96 dpi), even gaps,
  equal heights within a row, and one column at narrow widths. A Grid / List switch sits in the
  page toolbar and is remembered. Each card works like a Windhawk card: name, author, version,
  a short description, an on/off switch for installed items, and Details, Settings, Source,
  Remove (with a confirm step), Update or Install as they apply. Catalogue pages have a clean
  search bar on top with filter and sort beside it. Copy Halo Launcher's Modules page.
- View controls (search, filter, sort, grid or list) apply at once and re-lay out the page.
  They never wait for Save and never count as an unsaved change.
- Settings pages stay lean: few groups with plain names, one-line descriptions or none, rare
  options under a collapsed Advanced group, and two columns of compact rows on wide windows.
- Controls: on/off switch, dropdown (popup list with a gradient ring), text box, number slider
  with its value, colour box and key-capture box.
- Text is never cut off. Dropdown, text and key boxes grow to fit their longest text
  (`Set_FitBoxes`, up to half the page width), and an open dropdown list is at least as wide as
  its longest option. A list with more than 9 options scrolls (wheel, arrow keys) and opens
  with the chosen option in view.
- Footer: a floating pill dock at the bottom right, drawn inside the settings window. It is
  never a separate window, because a separate window showed square corners on screen. It holds
  the status line (unsaved count or message) and the buttons Reset to suggested, Cancel and
  Save. The page scrolls under it, and the last row can rise above it.

## Middle-click autoscroll (every settings window, since 2026-11-16)

Owner request, 2026-11-16: pressing the scroll wheel scrolls the page, the same in every mod.
It lives in the engine (`Set_AutoScroll*`, Launchpad 2.5.0 and later), so every mod gets it
through `settings-engine.py sync`. Never write a mod's own version, and never leave it out.

- Press the middle button over the page and move up or down: the page scrolls, faster the
  farther the pointer is from where it started. Nothing moves inside a small dead zone
  (`kSetAutoDead`, 10 DIPs). Speed grows with distance (`kSetAutoGain`) up to a cap
  (`kSetAutoMax`), every animation tick.
- Two ways to use it, like a browser. Press, move and release: it stops on release. Press and
  release without moving: it keeps going until the next click.
- It stops on any mouse click, any key (Escape does nothing else), the wheel, or when the
  window loses focus. It does not start while saving or when the page has nothing to scroll.
- It shows Seamless Autoscroll's anchor where the press happened: a Mocha mantle disc with the
  2px blue to mauve ring, two arrows (the one the page moves toward lights blue, the other is
  overlay1) and a mauve centre dot. It eases in and out. In glass mode the disc frosts what is
  under it with the page blur. Without glass it is opaque. The pointer shows the up-down
  cursor while it runs.
- Every settings window sets the window property `SeamlessOwnAutoscroll` on itself. The
  Seamless Autoscroll mod (1.0.1 and later) skips any window with that property, so a middle
  click never draws two circles. A new engine window must keep that property.
- One circle everywhere (owner, 2026-11-17: "the styled one, not the white auto scroller,
  across the board"). Seamless Autoscroll 1.1.0 and later also runs in Chromium browsers
  (Chrome, Edge, Brave, Vivaldi, Opera, Chromium, Helium). There the browser keeps its own
  scrolling and links still open in a new tab; the mod only hides the browser's white pan
  cursor and shows the same frosted circle at the press point. Never ship a mod or app tweak
  that brings the white circle back. Firefox is not covered (not installed).

## Look (Catppuccin Mocha)

- Base #1E1E2E, mantle #181825, crust #11111B, surface0 #313244, surface1 #45475A,
  surface2 #585B70, overlay0 #6C7086, text #CDD6F4, subtext0 #A6ADC8.
- Hover and focus everywhere: a gradient from blue #89B4FA to mauve #CBA6F7. It is a faint
  gradient wash plus a gradient ring that fades in over about 120 ms. Every card that reacts
  to the pointer gets it: rows, sidebar items, value boxes, footer buttons, dropdown items,
  and the About header and Ko-fi cards.
- Every scrollbar thumb, everywhere (the page, dropdown lists, the Launchpad grid, any new
  list), is a vertical blue #89B4FA to mauve #CBA6F7 gradient: `Set_ThumbFill`. Never a grey
  thumb.
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
  D82E1E1E acrylic tint: both read as a light grey slab. (Changed 2026-11-12.) Check every mod with `python scripts\settings-material.py check` before shipping (a mod that is off gets the template's glass, title bar, fitted boxes and gradient scrollbars with `python scripts\settings-engine.py sync <id> --out <dir>`), build on the installed source in ModsSource, and install with `scripts\Install-StagedMod.ps1`, which refuses if another thread changed the source since staging.

- Use Explorer's frosted glass as the visual reference. Check the rendered title band and body over busy text, focused and unfocused, with the shared rice skill's glass checker. The background should soften into visible colour changes, with no readable text behind the glass. A flat or barely frosted result fails in glass mode.

## Options every mod's settings window has

Every settings window has a sidebar tab named "Look". Place it directly below
"Appearance" when that tab exists. Keep the app's appearance controls on
"Appearance" and put these shared controls together on Look under "Settings window":

| Key | Name | Default |
|---|---|---|
| settingsGlass | Blurred settings window | on |
| nativeSettingsTitleBar | Native Windows title bar | off |
| settingsTrayIcon | Tray icon (click opens settings, right-click menu) | on |

Add the matching `$name` and `$description` lines to the mod's YAML settings block, and
default values to its install script.

The settings window itself opens and closes with the same fade and short slide as the
mod's own windows (owner rule, 2026-11-24), and goes still when Windows animations are
off. A mod that draws its own window, flyout or panel also puts these two on its
Appearance page, in a "Motion" group:

| Key | Name | Default |
|---|---|---|
| flyoutAnimation | Open and close animation | on |
| animationSpeed | Animation speed (Follow the global speed, Very quick, Quick, Normal, Relaxed, Slow) | Follow the global speed |

The global speed and on/off live in `HKCU\Software\DavidHiFi\Motion` (`Enabled`,
`Speed`) and Seamless Workshop owns that control. Rules: `docs\mod-style-guide.md`.

## Tray menu (every mod with a tray icon, since 2026-11-17)

The tray menu is part of the engine, like the window. Clipboard's Direct2D menu moved into the
Launchpad template as `Set_TrayMenu`, and `settings-engine.py sync` copies it into every mod.
Never build a tray menu with `CreatePopupMenu` and `TrackPopupMenuEx`, and never keep a private
copy of the renderer.

- Build the rows as a list: `Set_MenuRow(id, glyph, label, checked, disabled, hint)`,
  `Set_MenuSub(glyph, label, rows)` and `Set_MenuSep()`. Call
  `Set_TrayMenu(owner, rows, &pt)`. It returns the picked row's id, or 0 when nothing was picked.
- Every row gets a FiraCode Nerd Font glyph (codicons, `\uEAxx` to `\uECxx`; write them as
  `\u` escapes). A hotkey goes in `hint`, never after a tab in the label.
- Keep each mod's own commands, ids and order. The action code stays where it was. Only the
  drawing moves.
- The engine types live in the mod's settings namespace, which usually comes after the tray
  code. Put a small function at the end of that namespace that builds the rows and returns
  `Set_TrayMenu(...)`, declare it in the namespace's forward block, and call it from the tray
  code. Crash Watch and Crosshair 2026-11-17 are worked examples.
- The engine sizes labels so nothing clips. Submenus open on hover after 200 ms or with the
  right arrow key. Up, Down, Home, End, Enter, Left and Esc work. A click anywhere else closes
  the menu. It fades in over 90 ms, follows the live corner radius, and uses the window's glass.
- One menu per thread. A menu on the settings thread, such as a History row menu, works too.
- The `owner` is the mod's tray message window (it takes the foreground, as Windows asks).
- `mod-consistency.py` fails a tray mod that has an engine settings window but no
  `Set_TrayMenu`. A tray mod without an engine settings window is only warned.

## Native title bar and glass apply at once

`Set_ApplyFrame` is the only code that sets the frame, the system title bar or the glass. The
engine calls it on Save, when the window is created and from `Set_WndProc` when settings
change from outside. The mod must post `WM_APP_SETTINGS_RELOAD` to the settings window from
`Wh_ModSettingsChanged` (or its tool-mod version). `mod-consistency.py` fails a mod that sets DWM
frame or glass state in any other engine function, or that never posts the reload.

## About page

- A header card with the mod icon, name, version and a one-line description. It gets the
  gradient hover.
- A support card: "Like it? Help the mod keep going", with the line "Free and open source. A
  tip on Ko-fi keeps it moving." and an Open Ko-fi button. It links to ko-fi.com/DavidHiFi
  and gets the gradient hover.
- Link rows: Ko-fi, source and credits.

## Proof before calling a port done

- Run `python scripts\mod-consistency.py check --full` after every mod job. This covers
  every installed local mod. Report outstanding failures instead of calling the fleet synced.
  Before installation, `Install-StagedMod.ps1` also checks the staged source and refuses
  inconsistent tray badges, menu fonts, settings options and font defaults.
- Text uses FiraCode Nerd Font, and every font setting defaults to it. The tray menu is the engine's `Set_TrayMenu` (see Tray menu
  above), Clipboard's look: regular text, a leading glyph column, compact rows, an inset
  separator, dark Mocha fill, gradient edge and its hover. Halo's old native menu is the
  rejected reference. Do not make Settings bold as a native default item. Show a still
  capture of the open menu and of one hover state for every tray mod you touch.
- Tray badges share Crosshair's rounded blue-to-mauve plate and dark cutout glyph.
  The glyph identifies the mod. Icons displaying live state, such as volume or bin contents,
  may retain that state display. Keep application logos for the About page.
- Sync from the installed Launchpad settings engine before staging an update. Keep each
  mod's saved keys and content. Run saving and other slow work off the window thread,
  and show progress without blocking input. Coordinate template changes through coop.

- Build offline first. Then install, checking that the mod's host process and Explorer stay up.
- Show still captures of the live window for every page, plus a hover proof in the test copy
  built with LP_TEST_HOVER. Find the test window by its process id, never by name.
- If the mod already had settings, every value it had must still load and save under the same
  key names.
