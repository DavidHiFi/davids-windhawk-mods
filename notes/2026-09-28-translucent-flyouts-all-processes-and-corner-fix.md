# Translucent Flyouts: all-process scope + corner consistency fix

2026-09-28. Thread `translucent-flyouts`. Follow-up to
`2026-09-28-translucent-flyouts-port.md` after the owner reported "half the
flyouts aren't translucent" and context-menu corners not matching the 16px
window radius.

## What the owner saw

- Explorer's context menu styled (v0.4.0 was injected into `explorer.exe`).
- System menus ("Restore / Move / Size / ...") in other apps dark but opaque,
  near-square corners (measured ~4px).
- Ableton Live's Help menu unchanged (light, square, opaque).

## Findings

1. **Injection scope was the "half".** 0.4.0 `Include` was
   `explorer.exe|FlyoutTestWindow.exe` and only a 64-bit DLL existed. Menus and
   tooltips in every other process - and every 32-bit process - were never
   touched. Nothing else was wrong with the engine; the same engine version
   styles menus correctly once injected.
2. **Menus are DWM "small radius" elements.** With `custom-corner-radius`
   active, a menu's effective radius follows that mod's `smallRadius`, not the
   menu's corner preference. Verified:
   - `translucent-flyouts` sets `DWMWA_WINDOW_CORNER_PREFERENCE = ROUND(2)` on
     menus (read back live from a `winver` system menu via
     `DwmGetWindowAttribute`), yet
   - an A/B on a white-background test menu measured an arc of ~8px at
     `smallRadius=8` and ~16px at `smallRadius=16` (same menu, same settings
     otherwise).
   So the "squared" menus were radius 8 (or 4 outside the mod's reach) next to
   16px windows. The owner's `custom-corner-radius` had `radius=16`,
   `smallRadius=8`.
3. **Ableton Live menus are native after all.** An initial string scan of
   `Ableton Live 12 Suite.exe` found no `TrackPopupMenu`/`uxtheme` and I read
   that as "app-drawn". Wrong: the exe imports `CreateMenu`, `AppendMenuW`,
   `SetMenu`, `DrawMenuBar` and `SetMenuItemInfoW` from USER32 - Live attaches
   a real Win32 menu bar, and the dropdowns are user32-drawn `#32768` popups
   (they are DWM-rounded already, consistent with a real popup window). Live
   was simply excluded from the mod. Follow-up: Ableton is now included
   (0.6.0+, see the update at the bottom).

## Changes applied

### 1. `local@translucent-flyouts` 0.5.0 (rev 20), both architectures

- Source header: no `@include` (all processes), `@exclude` =
  `discord*.exe|Ableton*.exe|Voicemeeter*.exe|Matrix*.exe|Stream Deck*.exe|dwm.exe`;
  `@architecture x86-64 x86`.
- Install/registry: `Include=*`, same `Exclude`; `0.5.0_20.dll` installed to
  both `Engine\Mods\64` and `Engine\Mods\32`.
- Owner's settings untouched (verified: `global.effectType=modern_acrylic`,
  `global.cornerType=large_round`, custom rendering on).
- Test tooling: `FlyoutTestWindow` now builds a 32-bit twin
  (`FlyoutTestWindow32.exe`) and a `menulight` mode (menu over a white form for
  radius measurements); the menu-test script now accepts either executable.
- Engine hot-reloaded the new revision into running processes without a
  restart; explorer (5 processes) now runs `0.5.0_20`.

Receipt: `backups\2026-09-28\translucent-flyouts\install-receipt.json`.

### 2. `custom-corner-radius` smallRadius 8 -> 16 (live)

- Menus now render at the same 16px as windows. `tooltipRadius=4` unchanged.
- Receipt: `backups\2026-09-28\custom-corner-radius\small-radius-receipt.json`.
- Rollback:

```powershell
# corner radius back to 8
.\scripts\2026-09-28-custom-corner-radius-small-radius.ps1 -Set 8
# mod back to explorer-only scope (old behavior)
.\scripts\2026-09-28-translucent-flyouts-install.ps1 -Install -Include explorer.exe -Exclude 'discord.exe|Ableton*.exe|Voicemeeter*.exe|Matrix*.exe|Stream Deck*.exe'
# or disable the mod entirely
.\scripts\2026-09-28-translucent-flyouts-install.ps1 -Rollback
```

## Evidence (reports\2026-09-28)

- `translucent-flyouts-menu-20260928-181148.png` - x64 test menu: modern
  acrylic, transparent enough to show the desktop behind, rounded corners.
- `translucent-flyouts-menu-20260928-181217.png` - **32-bit** test menu over
  the Steam library; Steam artwork visibly bleeds through the menu.
- `translucent-flyouts-nativetip-20260928-181317.png` + probe log
  `[fx] applied type=2` - tooltip path.
- `translucent-flyouts-winver-sysmenu-final-20260928-182942.png` - the exact
  "Move / Close" menu class from the owner's screenshots, in a process
  (`winver.exe`) that 0.4.0 never reached; dark, translucent, rounded.
- `corners\menulight-sr16-corner-6x.png`, `corners\winver-corner-8x.png`,
  `corners\img1..4-corners.png` - corner measurements.
- Module checks: `winver.exe` and `regedit.exe` load
  `local@translucent-flyouts_0.5.0_20.dll` on start; probe logs show hook
  install and `[fx] applied` entries.
- No new Application-log errors around the change (last crash before it:
  unrelated `git-credential-manager.exe`, 5:50 PM).

## Boundaries (cannot be styled by this approach, by design)

- Classic ComboBox dropdown lists (`ComboLBox`): no uxtheme paint calls on this
  build; upstream TranslucentFlyouts has the same limit.
- XAML/WinRT shell surfaces: Start menu, Quick Settings, notification center,
  tray overflow, taskbar hover previews. These need the shell styler mods, not
  uxtheme hooks.
- App-drawn menus: Chromium/Electron in-app menus, Qt-widget menus, and other
  custom owner-draw UI. (Ableton turned out not to be one of these.)
- Protected processes stay excluded: Discord, Voicemeeter, VB-Audio Matrix,
  Stream Deck. `dwm.exe` is excluded from this mod.

## Update 2026-09-28 18:50 - Ableton Live included (0.6.0/0.6.1)

The owner asked again with a Live Options-menu screenshot ("flat menus aren't
translucent"). Since Live's menus are native Win32 popups, they are in scope:

- `local@translucent-flyouts` 0.6.0: `Ableton*.exe` removed from the Exclude
  list (protected chain minus Ableton stays). 0.6.1 adds Live's process name to
  the mod's debug-log targets.
- Live was running: the engine hot-loaded `0.6.1_22` into PID 5916 without a
  restart; the mod log
  (`tf-Ableton Live 12 Suite.exe-5916.log`) shows `[init]` with all six
  uxtheme/user32 hooks installed. Menu opens should log `[fx] applied
  type=1 ...` and render acrylic + 16px corners.
- `dark-menus` "TranslucentFlyoutsFix" set to 1 (was 0) per the DarkMenus
  readme when TranslucentFlyouts is in use; receipt and backup in
  `backups\2026-09-28\dark-menus\`.
- Rollback for the Live scope: re-run the install script with
  `-Exclude 'discord*.exe|Ableton*.exe|Voicemeeter*.exe|Matrix*.exe|Stream Deck*.exe|dwm.exe'`.
- Caveat: menu items could still turn out to be owner-drawn by Live (not
  statically detectable). If the Live menus show a patchwork (acrylic gaps,
  opaque rows), that is the owner-draw boundary; nothing to fix in the mod.

## Not yet ported (unchanged by this fix)

- Fluent open/close animations (`enableFluentAnimation` is stored but inert).
- Immersive/owner-draw menu internals (upstream `ImmersiveHooks`).
- Per-app `SetMenuInfo` background takeover (upstream `MenuHooks`).

## Published 2026-09-28 (evening)

- Setup-snapshot repo `DavidHiFi/davids-windhawk-mods`: main commits f9246e9
  (adds `mods/local/translucent-flyouts/`, refreshes the snapshot) and 0f2a1f7
  (one `@architecture` line per value - the single-line form fails the
  upstream catalog validator); release v1.1.0 with the zip.
- Windhawk catalog: PR ramensoftware/windhawk-mods#5785, single file
  `mods/translucent-flyouts.wh.cpp`; the repo's validation check passed;
  pending review. Once merged it becomes installable from windhawk.net/mods
  and supersedes the app-and-bridge route of `translucent-flyouts-controller`
  for this purpose.
- Local install stays `local@translucent-flyouts` 0.6.1 (rev 22); the
  metadata-only header fix does not change the compiled DLL.
