# Translucent Flyouts as a Windhawk mod: port plan and progress

2026-09-28. Thread `windhawk-tf-merge`.

## The ask

Fork the `translucent-flyouts-controller` Windhawk mod (GID0317, a settings
bridge that requires the discontinued TranslucentFlyouts app) into a new,
self-contained mod that implements the whole TranslucentFlyouts engine
natively: no app install, no registry bridge, no external downloads. Owner:
DavidHiFi.

Upstream engine (discontinued app): `ALTaleX531/TranslucentFlyouts` (archived
2025-01-04) and its identical fork `GID0317/TranslucentFlyouts`. Cloned to
`Windhawk\translucency-flyouts\upstream\TranslucentFlyouts`.

Controller source (settings surface + semantics): `mods.windhawk.net` ->
`translucent-flyouts-controller.wh.cpp` 1.1.0, saved in
`Windhawk\translucency-flyouts\translucent-flyouts-controller.wh.cpp`.

## Target

- Mod id `translucent-flyouts`, name "Translucent Flyouts", author DavidHiFi,
  LGPL-3.0 with attribution to ALTaleX531 (derivative of the app).
- One single-file `.wh.cpp` port of TFMain (the injectable engine DLL), with
  Windhawk APIs replacing the app/service/installer parts.
- Settings: the controller's schema (global / dropDown / menu / tooltip +
  process lists), read with `Wh_Get*Setting`; no HKCU\Software\TranslucentFlyouts
  dependency at runtime.

## What the upstream engine is (map)

TFMain is the injected DLL (the app's service only injects it globally).
Modules that matter for the port:

| Upstream file | Role | Port decision |
| --- | --- | --- |
| `TFMain/dllmain.cpp` | DLL attach/detach + service/install cmdline | replace with `Wh_ModInit` etc. |
| `TFMain/Framework.cpp` | startup, WinEvent hook (menu create), settings watch | port |
| `TFMain/MenuHandler.cpp` | menu `#32768` subclass, type detect, effect apply | port |
| `TFMain/MenuHooks.cpp` | IAT `SetMenuInfo` per-module, shell32 icon bg removal | port (IAT shim), defer icon part |
| `TFMain/UxThemeHooks.cpp` | DrawThemeBackground/Text interception, E8 redirects, StretchBlt/DwmSetWindowAttribute | port export-hook first (compatible-mode path), E8/symbols later |
| `TFMain/MenuRendering.cpp` | popup bg gutting, borders, custom D2D hot/focus/separator | port |
| `TFMain/FlyoutAnimation.cpp` | fluent open/close animations | port |
| `TFMain/DXHelper.*` | shared D2D/DXGI device for custom rendering | port |
| `TFMain/ToolTipHandler.cpp` + `TooltipHooks.cpp` | tooltip subclass/hooks | port |
| `TFMain/DropDownHandler.cpp` + `DropDownHooks.cpp` | combobox dropdown | port |
| `TFMain/ImmersiveHooks.cpp` | owner-drawn (immersive) menus | port |
| `TFMain/TraverseLogHooks.cpp` | keyboard-nav "TraverseLog" menus | port |
| `TFMain/KbxLabelHooks.cpp` | keyboard-accelerator labels | port if small |
| `TFMain/MenuHooks.cpp` symbol bits, `SymbolResolver.*`, `HookDispatcher.hpp` | PDB-driven offsets | replaced: `WindhawkUtils::HookSymbols` / `Wh_FindFirstSymbol` / Wh_Disasm |
| `TFMain/DiagnosticsHooks.cpp` | debug tooling | skip |
| `TFModern/*` | WinRT/XAML flyouts (immersive surfaces) | defer, out of v1 scope |
| `Common/*` | utils, registry, theme, hook helper, WIL | port with a small WIL shim |

Effective settings funnel: TF reads HKCU via `RegHelper::Get<DWORD>({part},
name, def, useFallback)` where `useFallback` means "fall back to the global
(empty) subtree". The engine queries are concentrated in `ApiEx.cpp`
(`Api::Query*Context`) — port those over a settings table.

## Environment facts

- Windows 11 25H2, build 26200.9457.
- Windhawk engine 1.7.3_2 (`C:\Program Files\Windhawk\Engine\1.7.3_2\`),
  compiler = clang 20 mingw at `C:\Program Files\Windhawk\Compiler\bin\clang++.exe`,
  headers incl. `windhawk_api.h`, `windhawk_utils.h` in `Compiler\include`.
- Build pattern proven by the altsnap fork:
  `H:\System Configuration\scripts\2026-09-28-altsnap-windhawk-build.ps1`
  (clang++ -std=c++23 -shared -target x86_64-w64-mingw32, link `windhawk.lib`,
  `-DWH_MOD`, mod id via force-included header).
- Install pattern: DLLs into `C:\ProgramData\Windhawk\Engine\Mods\{64,32}\`,
  registry `HKLM\SOFTWARE\Windhawk\Engine\Mods\<id>` (`LibraryFileName`,
  `Version`, `Disabled`, `Include`, `Exclude`), then bump `SettingsChangeTime`
  for live reload. **Never `windhawk.exe -restart`** (restarts explorer, kills
  the live T3 Code GUI).
- Do not touch the protected audio/comms chain processes in testing.

## Milestones

1. Probe mod compiles, loads, hooks `DrawThemeBackground/Ex/Text`, logs, and a
   bare acrylic backdrop shows on a `#32768` menu. (proves toolchain + approach)
2. Core menu port: settings table + menu subclass + uxtheme hooks + effects
   (acrylic/blur/transparent/solid/mica), corners, borders, custom rendering.
3. Tooltips, dropdowns, immersive/traverse-log menus, animations.
4. Settings UI (controller schema), process lists, readme, receipts, note, repo.

## Progress log

- 2026-09-28: discovery done; upstream + controller sources in place; toolchain
  and engine paths verified; coop claims made. Probe next.
- 2026-09-28: **probe milestone reached (v0.2.3)**. A working Windhawk mod now:
  - builds with the bundled clang (script `scripts\2026-09-28-translucent-flyouts-build.ps1`),
  - installs live via registry + `SettingsChangeTime` bump (script
    `scripts\2026-09-28-translucent-flyouts-install.ps1`; self-elevating;
    **does not restart the engine**),
  - hooks `uxtheme!DrawThemeBackground`/`DrawThemeText` via export addresses,
  - identifies the menu window during paint (WindowFromDC fails for buffered
    DCs; `EnumThreadWindows` for class atom 32768 works),
  - applies real acrylic backdrop + rounded corners to the `#32768` menu and
    gutting (PatBlt BLACKNESS = alpha 0) of MENU_POPUPBACKGROUND / BORDERS /
    GUTTER. Verified visually with an isolated WinForms test app
    (`scripts\tools\FlyoutTestWindow.exe`, native legacy context menu) and
    screenshots in `reports\2026-09-28\`.
  - Key finding: on this build (26100.9457), classic/legacy menu painting goes
    through the **exported** DrawThemeBackground (the exporter is hit with menu
    parts from a memory DC), so the E8/internal-symbol machinery of upstream is
    not needed for the core effect path. `MENU_POPUPITEMFOCUSABLE` (no inner
    underscore, =27) is missing from MinGW headers; defined locally.
  - Installer gotcha: `LibraryFileName` is the exact file name inside
    `Engine\Mods\{64,32}` (no `_64`/`_32` suffix, unlike the build outputs).
    Each install uses a new revision number (mapped DLLs cannot be overwritten).
  - Engine injection verified for new processes with
    `Include = explorer.exe|FlyoutTestWindow.exe`; the mod reloads live in
    already-running processes on each registry bump.
- Next: port the full engine: settings layer (controller schema), menu/tooltip/
  dropdown rendering, borders/dark-mode/custom rendering, animations.
- 2026-09-28 (rescue thread `windhawk-tf-rescue`): settings defaults fixed and
  the engine port verified. **v0.4.0** installed as
  `local@translucent-flyouts_0.4.0_*`, `Include=explorer.exe|FlyoutTestWindow.exe`,
  `Exclude=discord.exe|Ableton*.exe|Voicemeeter*.exe|Matrix*.exe|Stream Deck*.exe`,
  all settings at defaults (no `Settings` key).
  - Root cause of "effect resolves to 0" found: `Wh_GetIntSetting(name, fallback)`
    is variadic (the extra arg is a printf argument, not a default) and the code
    read flat names (`menuEffectType`) that do not exist - Windhawk stores nested
    settings as dotted value names (`menu.effectType`) under
    `HKLM\SOFTWARE\Windhawk\Engine\Mods\<id>\Settings`, options as REG_SZ option
    keys (e.g. `modern_acrylic`), numbers/bools as REG_DWORD. Fix: registry-backed
    reads in `src\10-settings.inc` (case-insensitive, `KEY_WOW64_64KEY`) with the
    controller's option-key -> index tables and explicit code defaults; absent
    value = default, present value (even 0) = user choice. Verified: default
    resolves to effect=5 (ModernAcrylicBlur).
  - Bug fix: theme class `Combobox` was wrongly treated as a flyout type, so
    closed ComboBox fields got the effect. Upstream styles only `ListviewPopup`;
    removed the `Combobox` mapping.
  - Bug fix: WinForms registers window classes like
    `WindowsForms10.tooltips_class32.app.0.*`; exact class-name matching failed,
    so tooltips were never seen. `Utils::IsWindowClassContains` added; tooltip
    windows are additionally gated on `GetWindowTheme(hwnd) != nullptr` (the
    original app skips unthemed tooltips - e.g. the WinForms `ToolTip` control
    calls `SetWindowTheme(hwnd, L"", L"")` internally and paints classic).
  - Bug fix (deadlock): `DwmEnableBlurBehindWindow` called synchronously from a
    tooltip's paint hangs the window thread (reproduced: tooltip froze the app and
    screen captures). The call is now only made when the effect actually needs
    window transparency (Acrylic/Mica); for ModernAcrylicBlur/none it is skipped.
    Menu path unaffected.
  - Verified in the isolated app (`scripts\tools\FlyoutTestWindow.exe`, now with
    an embedded v6 common-controls manifest and menu/tooltip/nativetip/dropdown
    modes): menu modern acrylic, `global.effectType=acrylic` (accent acrylic
    blur), `=transparent` (background shows through), custom rendering separator,
    tooltip detection + effect application. Screenshots in `reports\2026-09-28\`.
  - Known boundaries: classic `ComboLBox` dropdown lists on this build do not
    paint through uxtheme (no theme part calls), so they stay unstyled - same as
    the archived upstream engine, which only hooks `ListviewPopup`. The synthetic
    raw-tooltip test target never becomes visible (layered alpha stays 0 without
    real mouse tracking) even with the mod disabled, so tooltip visuals could not
    be photographed this way; the functional path (detect -> apply) is proven.
  - New helpers: `scripts\2026-09-28-translucent-flyouts-set-setting.ps1`
    (set/remove/list one setting, bumps `SettingsChangeTime`, self-elevating);
    build script assembles `src\00-foundation.inc` + `10-settings.inc` +
    `30-engine.inc` + `src\settings-block.inc` into the single `.wh.cpp`.
- Next (not yet ported, v1 scope): fluent open/close animations
  (`enableFluentAnimation` is a settings surface only), immersive/traverse-log
  menus, WinRT `TFModern` flyouts, compatibility mode (read but no-op), mini
  dumps (not applicable). Widening the mod beyond explorer: update the header
  `@include` / the mod key `Include` - keep the protected-chain `@exclude`s.
- 2026-09-28 (thread `translucent-flyouts`): **0.5.0** - scope widened to all
  processes (x64 + x86; protected chain and `dwm.exe` excluded), and the
  corner inconsistency with `custom-corner-radius` fixed (smallRadius 8 -> 16;
  menus are DWM "small radius" elements and follow that setting). Full record,
  evidence and boundaries:
  `2026-09-28-translucent-flyouts-all-processes-and-corner-fix.md`.

