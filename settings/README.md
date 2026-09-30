# Settings

Everything here comes from this machine's `HKLM\SOFTWARE\Windhawk`, plus one
file from ProgramData. These are the values every mod is tuned with.

| File | What it holds | Where it lands |
| --- | --- | --- |
| `mods-state.json` | Per mod: disabled, include and exclude lists, architecture, version. | `HKLM\SOFTWARE\Windhawk\Engine\Mods\<id>` |
| `mods-settings.json` | Every value under each mod's `Settings` key. | `HKLM\SOFTWARE\Windhawk\Engine\Mods\<id>\Settings` |
| `windhawk-app-settings.reg` | Windhawk app preferences (language, tray icon, toolkit, safe mode). | `HKLM\SOFTWARE\Windhawk\Settings` |
| `windhawk-engine-settings.reg` | Engine preferences (logging, injected processes). | `HKLM\SOFTWARE\Windhawk\Engine\Settings` |
| `quota-mod-localstorage.json` | The two quota mods' own config (`settings_v1`), credentials stripped. | LocalStorage values, see below |
| `windhawk-userprofile.json` | The installed mod set and versions at snapshot time. | Reference only |

Apply everything with `tools\Apply-WindhawkSettings.ps1` from an elevated shell.
Add `-Audit` to preview without writing, `-IncludeAppSettings` to import the two
`.reg` files, and `-RestartEngine` to restart Windhawk when done.

## What is deliberately not here

- `auth_*` values in the quota mods' LocalStorage. Those are DPAPI-encrypted
  account credentials tied to this machine. Sign in again through the mod's UI
  on your machine.
- Runtime caches: SymbolCache keys, stats timers, the taskbar app order file.
- Mod DLLs. Windhawk compiles mods on your machine.

## The quota mods' config

Both quota mods store their configuration in LocalStorage registry values
instead of the usual `Settings` key, so `mods-settings.json` cannot carry it.
`quota-mod-localstorage.json` holds the same `settings_v1` JSON for both: the
account list, bar layout, thresholds and colors. The simplest way to reuse it
is to set the mod up through its own UI using these values. To do it through
the registry instead, write the `settings_v1` string under
`HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\<mod id>\LocalStorage` and restart
the engine. The `opencodeKey` field is a length reference, not a key; your own
key is entered through the mod UI.

## Weather location

Weather latitude, longitude and place name are blank in the public snapshot. The export script removes these values, and the apply script skips blank location fields to preserve an existing local town. Configure your own town in the weather mod settings after installation. Cached weather readings are excluded.
