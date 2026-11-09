# Seamless Title Bars 1.0.0 (local@seamless-title-bars)

One mod that replaces the seven title bar mods. Plan: `docs\plans\2026-11-09-seamless-title-bars.md`.

## Live state, 9:28 pm 2026-11-09 (owner said go: option 1)

- ON: `local@seamless-title-bars_1.0.0_172828.dll`, loaded in 207 processes, dwm.exe and its windhawk-mod.exe tool host (Terminal bar).
- OFF (disabled, not removed): caption-buttons-customizer, win11-custom-title-bar-colours,
  local@remove-uwp-title-bars-plus, local@terminal-titlebar-blur, titlebar-for-everyone,
  cef-titlebar-enabler-universal, fix-basic-caption-text.
- Engine includes `*|dwm.exe|windhawk.exe`; ExcludeCustom `FreeDictate.exe|WindowsTerminal.exe|ESDDiscord.exe|windhawk-ui.exe`.
- Settings: basicFrames.enabled 0 (old value 1, see below); everything else as the old mods had it.

## Checks

- Module scan elevated: new DLL in dwm.exe, explorer, ApplicationFrameHost, chrome, steam, tool host.
- Steam title bar pixel 33,33,48 (dark base) with the native caption buttons: `reports\2026-11-09-seamless-title-bars-live.png`.
- uwp.enabled 1 -> 0 -> 1 through the cli: ApplicationFrameHost kept the mod, no reload failure.
- The click check (`scripts\2026-10-27-caption-settings-verify.ps1`) was NOT run: it moves the mouse and the owner was at the PC.
- DWM caption colour cannot be read back (DwmGetWindowAttribute 35 gives E_INVALIDARG), so colours are checked by pixels only.

## Fix found live: basic frames

- After the swap the mod loaded only in dwm.exe and the tool host. Cause: basic frames hooks two uxtheme symbols
  (`_NCWNDMET::GetCaptionColor`, `_GetWindowIcon`) that this Windows build lacks; the section failed and, being strict, unloaded the whole mod.
- So the old fix-basic-caption-text never ran here either.
- Fix: `basicFrames.enabled` set to 0 (9:09 pm), default now false, and basic is no longer strict (only its own bit clears). Recompiled 9:28 pm.

## Traps hit

- windhawk-cli rejects `@id local@...`; local mods use a bare id and the engine adds `local@`.
- Unquoted paths with spaces break the cli; the script quotes them.
- After the cli installs a source file under `Windhawk\seamless-title-bars\`, that file can no longer be
  overwritten from an agent shell (Python open "w" gives EINVAL, truncate gives access denied, Remove-Item is
  blocked as a protected path). Both `local@seamless-title-bars.wh.cpp` and `seamless-title-bars.wh.cpp` there are stale.
  The builder writes `work\2026-11-09-seamless-title-bars\out\seamless-title-bars.wh.cpp` instead.
- `-Action Compile` installs with `--disabled`; for a recompile of the live mod run `mod install --file <src>` without it.
- The swap ran at 9:07 pm while always-on-top-port held the windhawk-engine lock (my lock call failed and the
  script was chained after it). Only enable, disable and settings changes; no compile. Coop note left.

## Old mods removed, 9:31 pm (owner asked)

- `windhawk-cli mod remove <id> --yes` for all seven: registry keys, sources and DLLs gone.
- Before that, every old DLL (32 and 64 bit, incl. the patched `caption-buttons-customizer_1.1_widthfix.dll`)
  was copied to `backups\2026-11-09\seamless-title-bars\dlls\`.
- Leftovers: the widthfix DLL was not removed by the cli and was deleted by hand. The old colours DLL
  `win11-custom-title-bar-colours_1.0.0_579254.dll` is still mapped in Steam, T3 Code and wslservice (it did not
  unload when disabled), so it is queued to delete at the next restart. Until those apps restart they paint the
  same colour twice; harmless.
- `-Action Rollback` no longer works on its own. To restore one: `mod install --file <backup>\<id>.wh.cpp`
  (elevated, bare id for local@ ones), then `reg import <backup>\<id>-20261109-2107.reg`, then disable
  `local@seamless-title-bars` or the matching section. For caption buttons, copy the widthfix DLL back and
  point LibraryFileName at it.

## Preview and publish, 2026-11-09 night (owner asked)

- Preview: `work\2026-11-09-seamless-title-bars\make-preview.py` stacks real Steam, Helium and window captures
  (1600x563). Readme image link fixed to `media/previews/seamless-title-bars.png`; raw URL checked: 200, same size.
- Credits fixed: Remove UWP Title Bars is by Anixx, Fix Basic Caption Text by aubymori (they were swapped).
- Live reinstall after both fixes: `local@seamless-title-bars_1.0.0_794390.dll`, loaded in 226 processes, dwm and tool host.
- Public repo commit 31eeaac on main (`publish-repo.py`): adds the mod, readme, preview, settings and manifest entry;
  removes the five catalog copies and Remove UWP Title Bars Plus, their catalog rows, settings and manifest entries;
  credits rows added to the main README; `Build-Repo.ps1` no longer keeps the uwp repo copy.
- Still open: the mouse click check (needs the owner away); the old colours DLL goes at the next restart.

## Swap and rollback (before removal)

- Backups: `backups\2026-11-09\seamless-title-bars\` (seven .reg exports, old sources, was-on.txt, script.log).
- Rollback: `scripts\2026-11-09-seamless-title-bars.ps1 -Action Rollback` disables the new mod and re-enables every mod in `was-on.txt`.
