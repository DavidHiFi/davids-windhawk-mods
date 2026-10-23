# Theme Tool Plus — ground framework (research only)

Date: 2026-10-16. Read-only research task; nothing was changed on the system.
Goal: define how we build **Theme Tool Plus**, a single Windhawk mod that merges
the **UXTheme hook** mod (signature bypass so Windows loads custom themes) with
**ThemeToolSharp**'s full feature set, becoming a complete replacement for
running ThemeToolSharp.exe alongside a mod.

## 1. The current stack on this machine (verified)

- `uxtheme-hook` 1.4 (rounk-ctrl) is installed and enabled. Include list:
  `winlogon.exe | explorer.exe | systemsettings.exe | logonui.exe | rundll32.exe`,
  plus `IncludeCustom = ThemeToolSharp.exe`. Setting `preventSettings = false`
  (its only setting).
- ThemeToolSharp.exe is the separate app that applies themes (needs that custom
  include so the signature hook also runs inside it).
- `C:\Windows\Resources\Themes\` holds `aero`, `catppuccin` and `themeA`–`D`
  (.theme files) — the picker will list whatever is there, via the theme
  manager, not by scanning the folder ourselves.
- Facts to keep straight: ThemeToolSharp is **C# (.NET, WinForms), not Go** —
  LGPL-2.1, (C) namazso. SecureUxTheme is the native patcher it grew out of;
  ThemeTool was its old GUI and is gone ("configuration-free" since v4).

## 2. How each piece works (from source)

### uxtheme-hook (the mod half)

Source: `ramensoftware/windhawk-mods/mods/uxtheme-hook.wh.cpp` (v1.4).

- Hooks `CThemeSignature::Verify` **by symbol** (`public: long __cdecl
  CThemeSignature::Verify(void *)` — `__thiscall` on x86) in
  `uxtheme.dll`, `uxinit.dll`, `themeui.dll`; the replacement returns
  `ERROR_SUCCESS` unconditionally, so unsigned .msstyles load.
- Hooks `SetSysColors` so LogonUI's reset of the 13 `DefaultColors\Standard`
  entries is ignored (fixes "theme stops applying after restart").
- Optional `CoCreateInstance` hook returning `E_NOINTERFACE` for
  `CLSID_ApplicationActivationManager`/`IID_IApplicationActivationManager`
  inside rundll32.exe — stops Settings opening on every theme apply.
- Because the hook must exist in **winlogon.exe** (which loads the theme at
  logon) the include list is mandatory, and per its README/FAQ the theme must
  first be "patched" (registered) — with ThemeTool/SecureUxTheme today.

### ThemeToolSharp (the app half)

Source: `namazso/ThemeToolSharp` (single WinForms form; ~6 KB of logic).

- Core: COM `IThemeManager2`, CLSID `9324da94-50ec-4a14-a770-e90ca03e7c8f`.
  Full interface (from `IThemeManager2.cs`): `Init`, `InitAsync`, `Refresh`,
  `RefreshAsync`, `RefreshComplete`, `GetThemeCount`, `GetTheme`,
  `IsThemeDisabled`, `GetCurrentTheme`, `SetCurrentTheme(hwnd, index,
  applyNow, applyFlags, packFlags)`, `GetCustomTheme`, `GetDefaultTheme`,
  `CreateThemePack`, `CloneAndSetCurrentTheme`, `InstallThemePack`,
  `DeleteTheme`, `OpenTheme`, `AddAndSelectTheme`,
  `ExportRoamingThemeToStream`, `ImportRoamingThemeFromStream`,
  `UpdateColorSettingsForLogonUI`, `GetDefaultThemeId`.
- `ThemeApplyFlags` (exactly the option set the user listed):
  `IgnoreBackground`, `IgnoreCursor`, `IgnoreDesktopIcons`, `IgnoreColor`,
  `IgnoreSound`, `IgnoreScreensaver`, `Unknown1` (window metrics),
  `Unknown2`, `NoHourglass`. `ThemePackFlags`: `Unknown1`, `Unknown2`,
  `Silent`, `Roamed`. `InitializationFlags`: `ThemeInitCurrentThemeOnly`,
  `ThemeInitFlagUnk1`, `ThemeInitFlagUnk2`.
- UI actions: Apply (with flag checkboxes), Refresh, Re-initialize; Apply also
  calls `UpdateColorSettingsForLogonUI()` unless "do not set LogonUI" is
  ticked. Settings persist per-user (WinForms `Settings.Default`).

### SecureUxTheme (the mechanism reference)

Source: `namazso/SecureUxTheme`, `SecureUxTheme/hooks.cpp`.

- IAT-hooks `CryptImportKey` in `themeui.dll`, `themeservice.dll`,
  `uxinit.dll`, `uxtheme.dll` (loaded-image notifications + delay-load
  resolution). Because `CreateKey` may be inlined into `Verify`, it uses
  return-address/unwind tricks (CET-safe on x64/ARM64) to force `Verify` to
  return S_OK. The file documents the whole `CThemeSignature::Verify` flow.
- The Windhawk mod's symbol-hook of `Verify` itself is the cleaner equivalent
  and is what we keep; SecureUxTheme remains the reference for edge cases
  (x86 return-hook variants, Win 8.1 themeservice).

## 3. Theme Tool Plus — proposed design

**One mod, id `theme-tool-plus`, name "Theme Tool Plus"** (kebab id matches;
check id is free in the mods repo). Targets `explorer.exe` for the picker, plus
the same mandatory include list as upstream (`winlogon.exe`, `logonui.exe`,
`systemsettings.exe`, `rundll32.exe`) for the bypass. The whole point of
running the picker inside explorer: `IThemeManager2` is created **in-process**,
so ThemeToolSharp.exe and its custom include entry become unnecessary.

Components:

1. **Signature bypass** — carried over verbatim from uxtheme-hook (symbol hook
   in the three DLLs, `SetSysColors` LogonUI guard, optional
   `preventSettings` rundll32 hook). This is the "merge the UX theme mod
   exactly as it is" requirement; it must keep working in winlogon so themes
   survive reboot.
2. **Theme manager client** — thin C++ wrapper over the COM interface above
   (vtable-compatible struct declared locally; `CoCreateInstance` of the
   CLSID). Functions: list themes, current theme, apply with flags, refresh,
   re-init, `UpdateColorSettingsForLogonUI`, `AddAndSelectTheme`,
   `DeleteTheme`, `OpenTheme`.
3. **Picker UI** — small dark-themed popup owned by explorer, toggled by a
   configurable hotkey (default proposed: `Ctrl+Alt+T`) and/or an optional
   tray-ish trigger; list of themes with the current one marked, Apply button,
   and per-apply flags exposed as a compact "Advanced" row. Theme icons via
   `IShellItemImageFactory` if cheap, plain text list as fallback.
4. **Settings-driven apply** — every flag and the selected theme name are Windhawk
   settings (`$name`/`$description` in the settings block, structured registry
   values per our engine facts). On `Wh_ModSettingsChanged`, if a "apply on
   settings change" toggle is set, the mod applies the chosen theme — so the
   user can also drive it entirely from the Windhawk UI without the popup.
5. **Options mapping (complete, per ThemeToolSharp)**: ignore background,
   cursor, desktop icons, color, sound, screensaver; unknown flag 1/2 exposed
   as "advanced (window metrics)" style toggles; NoHourglass always set (as
   upstream does); "update LogonUI colors on apply" toggle (default on);
   init flags 1/2 on the re-initialize path; prevent-Settings toggle.

Conventions (per `docs\mod-style-guide.md`): plain catalog-style name, one-line
description ("Apply and switch custom Windows themes with a hotkey picker. No
separate theme tool needed"), feature-bullet readme, preview image, Credits:
Based on UXTheme hook by rounk-ctrl; theme-engine research from SecureUxTheme
and ThemeToolSharp by namazso (LGPL-2.1) — since the COM wrapper and hook logic
are derived from LGPL and unlicensed-upstream code, the Credits section must
name both and we ship no binary redistribution of their code, only our own
implementation.

## 4. Phasing

1. **Scaffold**: fork structure, header/settings block, bypass hooks carried
   over, build both archs, verify signature bypass still works via existing
   catppuccin theme (no behavior change vs uxtheme-hook alone).
2. **COM wrapper + settings-driven apply**: apply/re-init/refresh from
   settings; verify with themeA–D round-trips and registry `SettingsChangeTime`
   hot-reload.
3. **Picker UI**: hotkey popup, apply from list, current-theme marker.
4. **Full option surface**: all apply/pack/init flags wired to settings.
5. **Cutover**: install Theme Tool Plus, remove `ThemeToolSharp.exe` from
   uxtheme-hook's custom include, disable/retire uxtheme-hook (one at a time,
   backed up first per AGENTS.md), write receipt + note.

## 5. Risks and open questions

- **Login loop**: a broken theme applied while the bypass is active in
  winlogon can loop logon (SecureUxTheme wiki documents recovery). Mitigation:
  the picker never applies themes without an explicit action, settings-driven
  apply defaults off, and the note documents the DefaultColors rename escape
  hatch already covered by the SetSysColors guard.
- **Uninstall path**: if the mod is removed while a custom theme is active,
  the next logon re-verifies signatures. Document: switch to a stock theme
  (or keep the mod) before uninstalling.
- **ARM64/ARM64EC**: upstream ThemeToolSharp README says the Windhawk
  combination is unsupported on ARM64 (no ARM64EC hooks). This machine is
  x64, so out of scope; note it in the readme.
- **`themeservice.dll`** (Win 8.1 path in SecureUxTheme) is not hooked by the
  mod; irrelevant on Win 11 but record it.
- **Settings app launching** on apply is a theme-manager behavior; the
  existing preventSettings hook is the mitigation, keep it opt-in as upstream.
- `Unknown1/2` flags are reverse-engineering artifacts; expose them but label
  them honestly as advanced/undocumented.

## 6. Verification plan (for the build phase)

- Round-trip: apply catppuccin Mocha → LogonUI colors intact → reboot → theme
  still active (winlogon hook verified).
- Each ThemeToolSharp option toggled individually with a visible before/after
  where observable (desktop icons, sounds, cursor).
- `reg export` of the mod key before every apply experiment; receipt JSON per
  AGENTS.md.

Sources: uxtheme-hook 1.4 source (ramensoftware/windhawk-mods),
ThemeToolSharp master (README, `IThemeManager2.cs`, `MainForm.cs`),
SecureUxTheme master (README, `hooks.cpp`), local registry + themes folder.
