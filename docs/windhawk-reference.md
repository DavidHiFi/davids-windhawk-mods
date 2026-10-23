# Windhawk reference (this machine)

Facts verified on 2026-09-28. Update when they change.

## Layout

| Thing | Path |
| --- | --- |
| Engine exe | `C:\Program Files\Windhawk\windhawk.exe` (`-restart` restarts the engine) |
| Engine data | `C:\ProgramData\Windhawk\` |
| Mod sources | `C:\ProgramData\Windhawk\ModsSource\<mod-id>.wh.cpp` |
| Mod DLLs | `C:\ProgramData\Windhawk\Engine\Mods\64\` and `\32\` |
| Mod settings | `HKLM\SOFTWARE\Windhawk\Engine\Mods\<mod-id>\Settings` |
| Mod state | `HKLM\SOFTWARE\Windhawk\Engine\Mods\<mod-id>` - `Disabled`, `Include`, `Exclude`, `LibraryFileName`, `Version`, `SettingsChangeTime` |
| Engine service | `Windhawk` (Automatic, Running) |
| UI | `windhawk.exe`; mod settings editable in the app, including "Textual mode" |

## Settings: structured registry form

Taskbar-styler settings are stored as flat named values, parsed from the YAML the
UI's textual mode shows. For `windows-11-taskbar-styler` (v1.10):

```
theme                REG_SZ    ('' or a built-in theme id)
styleConstants[0..]  REG_SZ    "name = value"
controlStyles[i].target      REG_SZ   selector, e.g. "Taskbar.TaskListButton#TaskListButton"
controlStyles[i].styles[j]   REG_SZ   style line, e.g. "Height => TaskbarHeight"
themeResourceVariables[0..]  REG_SZ   "AdaptiveText@Dark =#CDD6F4"
clickThroughTaskbar  REG_DWORD
xamlDiagnosticsHandling REG_SZ
```

The values mirror the textual YAML one-to-one (comments included as their own
values). Appending a rule = adding `controlStyles[N].target` and
`controlStyles[N].styles[0..k]` where `N` is `max+1`. Keep indices contiguous;
a gap can truncate parsing.

## Applying changes

1. `reg export` the mod key to `backups\<date>\...` (elevated).
2. Write the new values (elevated).
3. Bump `SettingsChangeTime` (unix seconds, REG_DWORD).
4. `windhawk.exe -restart` (elevated, hidden window). The engine re-injects mods
   into running processes; no explorer restart or reboot.
5. Verify by screenshot (taskbar/tray) or by reading the registry back.

The taskbar styler additionally picks up settings live off `SettingsChangeTime`
(the giant-pill notes show registry writes applying with no engine restart), but
a restart is the reliable, general path for every mod.

## Selector and style syntax (taskbar styler)

- Target: `ClassName#XamlName`, `ClassName#XamlName@StateGroup`, descendant paths
  with `>`, comma-separated alternatives, and property filters like
  `[Text=<glyph>]` or `[AutomationProperties.AutomationId=StartButton]`.
- Styles: `Property=Value` (typed assignment), `Property:=Value` (binding),
  `Property => Name` (capture into a style constant), `@State` suffixes for
  state-specific values, `{{...}}` expressions, `$name` style constants.
- Built-in helpers: `<SolidColorBrush>`, `<WindhawkBlur>`, `{ThemeResource ...}`
  with `themeResourceVariables` overrides.
- Glyph swap trick: a tray chevron is a `TextBlock#InnerTextBlock` whose `Text`
  is a Segoe Fluent Icons glyph. Match it with `[Text=<glyph>]` and reassign
  `Text`. The tray overflow chevron is U+E971 (ChevronUpMed); U+E712 is "More"
  (three horizontal dots); U+ED14 is the vertical-dots variant other themes use.

## Mod development (local mods)

- Local mods use ids like `local@<name>`; `LibraryFileName` points at
  `<mod-id>_<version>_<rev>.dll` in the `64`/`32` folders, `Include`/`Exclude`
  decide target processes, `Disabled` toggles it.
- Build pattern and traps: see `docs\traps-and-tips.md` and
  `Windhawk\altsnap-fork\` (build script in
  `H:\System Configuration\scripts\2026-09-28-altsnap-windhawk-build.ps1`).
- Mod settings for local mods live under the same `Settings` subkey, values named
  as the mod's settings declaration.

## Useful links

- Windhawk: https://windhawk.net
- Taskbar styling guide (themes, selector docs):
  https://github.com/ramensoftware/windows-11-taskbar-styling-guide
- RosePine theme source:
  https://github.com/ramensoftware/windows-11-taskbar-styling-guide/blob/main/Themes/RosePine/README.md
- Local fork repo: https://github.com/DavidHiFi/davids-windhawk-mods
