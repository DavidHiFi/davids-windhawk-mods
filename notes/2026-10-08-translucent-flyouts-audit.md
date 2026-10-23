# Translucent Flyouts audit and fix to 0.6.8

2026-10-08, thread `t3-translucent-flyout-audit`. The user reported the Windhawk
toast "Failed to parse settings: instance[1].dropDown[6].darkModeThemeColorizationType
must be a string or array of strings to use $options", no proper flyout effect,
and fully static menus in Ableton Live.

## What was wrong (four separate things)

1. **Settings schema invalid.** The dropDown, menu and tooltip groups declared
   their colorization settings as numbers with numeric `$options`
   (`darkModeThemeColorizationType: 1` with `- 0:`, `- 1:`, ...). Windhawk
   requires a `$options` setting to be a string or a string array. The 2.0
   engine rejects the whole block: `windhawk-cli mod show local@translucent-flyouts`
   returned the same error the UI toast showed. The mod still ran because it
   reads its settings straight from the registry (`src\10-settings.inc`), not
   through the engine's parser, but the settings UI could not show or edit it.
   The global group already used the correct string form; the other groups
   never matched it.

2. **`mod compile` emptied Include.** While fixing the schema I recompiled with
   `windhawk-cli mod compile`. That rewrote the mod key's `Include` from `*` to
   an empty string (the header has no `@include` line). Empty Include means "no
   processes": after the compile the mod injected nowhere, not even into fresh
   processes. Four mods on this machine have empty Include and none of them
   inject anywhere. Restoring `Include=*` fixed injection immediately. This
   also explains why `Architecture` looked suspicious: the pipe-separated
   `x86-64|x86` the compile writes is fine, both architectures inject with it.

3. **Ableton was excluded.** The 2026-10-04 tooltip-text thread added
   `Ableton*.exe` to the mod's Exclude to protect the audio chain. The
   workspace AGENTS.md has a standing exception for exactly this mod styling
   Ableton's menus (requested 2026-09-28, live-verified), and the mod's readme
   documents Ableton as included. Ableton menus were therefore native and
   static. Removed from Exclude; the header `@exclude` list never had it.

4. **translucent-windows fought it.** The catalog `translucent-windows` 1.8.2
   was installed alongside with `FlyoutsEffects=1`, its "Flyout effects"
   option that expands its effects to Win32 context menus. Both mods hook the
   same uxtheme exports in every process. Set `FlyoutsEffects=0` on its
   Settings key; its per-app window backgrounds (Discord, zen, explorer,
   terminal, and the rest of its RuledPrograms) are untouched.

## Code changes (0.6.7 -> 0.6.8)

- The 14 numeric colorization settings became strings (`start_hover` style),
  same option names as the global group. No engine code change needed:
  `kColorizationType` already accepted both forms.
- `GetBuildNumber` now parses the `CurrentBuildNumber` REG_SZ instead of
  reinterpreting its bytes as a DWORD.
- Removed dead code: five unused `TF_*` macros, `WindowDcCloser`,
  `IsBadReadPtr`, `ResultException` and `Throw` (zero call sites).
- Canonical source is `C:\ProgramData\Windhawk\ModsSource\local@translucent-flyouts.wh.cpp`.
  The split tree `Windhawk\translucency-flyouts\src\` was stale at 0.6.6 and is
  regenerated from the shipped 0.6.8 file; the build script's assembly was
  verified to reproduce it (content equality, blank lines ignored).

## Verified

- `mod show` parses both mods' settings (success:true).
- 0.6.8 x64 and x86 DLLs exist; both architectures inject into fresh test
  processes and the x64 DLL is loaded in the running explorer.
- Menu test screenshot shows the modern acrylic dark menu with rounded corners
  and an accent border: `reports\2026-10-08\flyout-check\translucent-flyouts-menu-20261008-191837.png`.
- Registry read-back: Include `*`, Exclude without Ableton, Architecture
  `x86-64|x86`, all colorization values REG_SZ, translucent-windows
  FlyoutsEffects 0, both SettingsChangeTime bumped.

## Rollback

`scripts\2026-10-08-translucent-flyouts-audit.ps1 -Rollback` reimports both
backed-up .reg files (`backups\2026-10-08\translucent-flyouts-audit\`) and
bumps SettingsChangeTime. The pre-audit source is next to it as
`local@translucent-flyouts.wh.cpp.pre-audit.bak`; restoring it needs a
recompile.

## Notes for later

- After every `windhawk-cli mod compile` of a mod whose Include should be `*`,
  check the mod key: the compile resets Include to the header's `@include`
  list. Worth a coop note and maybe a check in the install scripts.
- The fork repo and upstream PR #5785 still carry 0.6.1. Publishing 0.6.8 is a
  separate, external-facing decision and was not done here.
- The 2026-10-04 tooltip-text note says Ableton was added to the exclusions;
  this note supersedes that for this mod.
