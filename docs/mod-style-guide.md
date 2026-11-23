# Mod style guide

How every Windhawk mod in this workspace is named and described, so it reads
like a mod from the Explore catalog. Adopted 2026-10-04 at the user's request;
apply it to every new or updated mod.

## Names and ids

- No personal names in `@id`, `@name`, file names or folder names.
- `@author` lists `DavidHiFi` first, then the original creator and developers of
  every mod, fork, port or code source the mod is based on, the same names its
  Credits section gives (user, 2026-10-13). A mod with no upstream lists only
  `DavidHiFi`. The GitHub links are the other place the author appears.
- Every mod carries `// @donateUrl       https://ko-fi.com/DavidHiFi` right
  after `@homepage`, so Windhawk shows the Donate button (user, 2026-10-24).
  Forks replace the upstream donate link; the original authors keep their
  credit in `@author` and Credits.
- Write the name, description, settings text and readme with the `humanizer`
  skill: short plain sentences a non-technical person understands, no jargon.
- Name the mod after what it does, in plain words a non-programmer would use:
  "Window Manager", "Taskbar Weather", "Shell Font Changer".
- A fork that extends a catalog mod keeps the original name plus **Plus**
  ("Better Volume Mixer Plus", "Taskbar System Info Plus"). A port of a known
  app may use that app's name ("AltSnap", "Translucent Flyouts").
- No "fork", "by X", version numbers, "with Y" or dashes in the name.
- `@id` is lowercase-kebab and matches the name. Check that the id is free in
  `ramensoftware/windhawk-mods/mods/` before using it. Changing an installed
  mod's id means migrating its registry key, settings, LocalStorage and
  mod-storage folder (see `scripts\2026-10-04-mod-id-migration.ps1`).

## `@description`

One line, under about 100 characters, no trailing period. Say what the user
gets, not how it works: "Current weather on the taskbar with a details card on
hover. No Widgets, browser or API key needed".

## Settings block (owner rule, 2026-11-04)

Every mod with settings writes its `==WindhawkModSettings==` block the way the
StartPad mod (Frankh93) does. Reference copy:
`docs\reference\startpad-settings-block.yaml`.

- Each setting has a short plain `$name` and a `$description` that says the
  range and the suggested value ("4 to 12 (Suggested: 8).") or what on and off
  do ("When off, the Windows key opens the original Start menu.").
- Choices use `$options` with readable labels (`light: Light`), never raw ids.
- Order settings the way a person thinks: opening and keys, layout, icons,
  background, look (colors, glow, opacity), extra bars, behavior.
- Give the user many knobs for the look: accent color (Catppuccin Mocha blue
  `#89B4FA` default), glow strength and size, surface opacity, alignment.
- Never rename an existing key when rewording; saved values live under it.
- Defaults live in the schema; clamp every value in code.
- Every mod that draws a window, flyout, panel or menu animates it open and closed
  (owner rule, 2026-11-24) and carries two settings for it, grouped under Motion on
  its Appearance page:
  - `flyoutAnimation` (or `<surface>Animation`): "Open and close animation", on.
  - `animationSpeed`: "Animation speed", `global` (Follow the global speed),
    `veryQuick`, `quick`, `normal`, `relaxed`, `slow`; default `global`.
  The global base lives in `HKCU\Software\DavidHiFi\Motion` (`Enabled`, `Speed`), and
  Windows "Animation effects" off makes it still. Look and timing: the rice recipe,
  `references\style.md`, Motion. Worked example: Network Speed Test Plus 2.4.0.

## Readme layout

```
# <Name>

One or two sentences: what it does and why you would want it.

![<Name> preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/<id>.<png|gif>)

## Features
- **Bold lead-in.** Short plain sentence.   (4-8 bullets, the things people care about)

## Default shortcuts / How to use / Setup   (only what is needed; a table for shortcuts)

## Notes or Tips   (conflicts to disable, limits; short)

## Credits
Based on [Original](https://windhawk.net/mods/<id>) by <author>. <License>.
```

- Every mod has a preview: a PNG screenshot, or a GIF (8-15 fps, under 3 MB)
  when the feature is motion. Crop tight; no personal titles, accounts,
  locations or notifications. Files live in `davids-windhawk-mods\media\previews\`.
- Plain, friendly English. No internal history ("this fork adds", "on this
  machine"), no implementation detail unless the user needs it to set
  something up, no walls of text. Troubleshooting stays short.
- Credits go last, one short paragraph, with links to the originals.
