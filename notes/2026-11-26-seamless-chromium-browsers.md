# Seamless Chromium Browsers 1.0.0 and Seamless Title Bars 1.3.17 (2026-11-26)

## What and why
- Owner (2026-11-24): merge Helium Acrylic and Brave Acrylic into one own mod,
  "Seamless Chromium Browsers", every option from both, plus fonts, colours,
  accents and borders. Also kill the grey square frame round extension pop-ups.
- New mod `local@seamless-chromium-browsers` (header @id bare). Built by
  `work\2026-11-26-chromium-browsers\gen.py` from the installed sources
  (helium-acrylic 3.9.3, brave-acrylic 4.0 by bardelyne, MIT).

## Layout of the merged source
- Top-level settings: accentStart, accentEnd, uiFont, uiFontSize, popupCorners,
  popupEdge, popupEdgeColor (shared layer, `common.inc.cpp`, namespace Common).
- Group `helium.*`: every Helium Acrylic key, unchanged names.
- Group `brave.*`: every Brave Acrylic key, unchanged names.
- Each engine sits in its own namespace with Wh_GetIntSetting/Wh_GetStringSetting
  shadows that add the group prefix, so the engine code is untouched otherwise.
- Dispatch: exe path with "helium" runs HeliumEngine; brave.exe runs BraveEngine
  (if it fails, the mod returns FALSE in Brave); Common runs in every browser's
  main process (chrome, brave, msedge, vivaldi, thorium).
- Accent: Helium's hard-coded 89B4FA/CBA6F7 gradient pieces and icon now read
  g_accentA/g_accentB.

## Grey square root cause
- Seamless Title Bars `native::CreateWindowExW_hook` stripped WS_EX_NOREDIRECTIONBITMAP
  from every window in chrome.exe/brave.exe. Chromium bubbles lose their
  see-through shadow margin, which turns into an opaque dark band with a square edge.
- 1.3.17 keeps the flag on Chromium pop-ups (Chrome_WidgetWin_* WS_POPUP without
  caption or thick frame; class atoms resolved with GetClipboardFormatNameW).

## Settings migration
- `migrate-settings.ps1` (elevated) exports the three mod keys to
  `backups\<stamp>-chromium-browsers-merge\` and copies every old value to
  helium.<name> / brave.<name> with its type.
- Owner's values at merge time: Helium all defaults except popupAcrylic=1;
  Brave blurSuggestions=0, hideNativeCaptionButtons=0, rest default.

## Rollback
- Turn off local@seamless-chromium-browsers. The old Helium Acrylic and Brave Acrylic
  mods were removed in the 2026-11-26 audit: bring them back with
  `scripts\2026-11-26-remove-stale.ps1 -Rollback` (elevated), then
  `scripts\Set-ModState.ps1 -Id <id> -On`.
- Title bars: reinstall `work\2026-11-26-chromium-browsers\tb\base-1.3.16.wh.cpp`.

## Install results (2026-11-26, 3:25 to 3:47 am)
- Seamless Chromium Browsers 1.0.0 installed and published (desktop fine after 60 s).
  37 settings copied from the old mods. Helium Acrylic and Brave Acrylic turned off.
  Helium Acrylic retired in the Workshop repo. New mod listed under Windows and menus.
- Seamless Title Bars 1.3.17 installed (desktop fine) and published.
- Live test on Helium: with title bars 1.3.17 the pop-up keeps its flag, but the grey
  square frame stayed. The real cause was the owner's `helium.popupAcrylic = 1`: the
  accent blur fills the whole square window, shadow margin included. Set to 0 (the mod's
  default; the setting's own text warns about the square frame). Frame gone on the
  after shot (`D:\Agent Work\2026-11-26-chromium-popup\pa0-popup0.png`).
- Not tested live: Brave (not installed on Warden), and the new font, accent and pop-up
  corner settings at non-default values.

## 1.1.0 (2026-11-26, afternoon)
- New "Browser font weight" setting (stock, light, regular, medium, semi-bold, bold),
  default medium. Browser font now defaults to FiraCode Nerd Font. Owner asked for
  "a code font, medium weight".
- Owner settings to set after the install: uiFont = FiraCode Nerd Font,
  uiFontWeight = medium (old: uiFont empty, no weight value). `install-scb.ps1` does
  it with a registry export first (`settings.bak-<stamp>.reg`).
- Colour probe for later browser updates: start a test browser with
  `--scb-color-probe=N` and ids N..N+63 paint as red = low byte, green = 0xA5,
  blue = high byte. Only that browser is affected.
- Staged at `C:\Users\Public\seamless-chromium-browsers.wh.cpp`, built by
  `work\2026-11-26-chromium-browsers\patch-110.py` from base 1.0.1. Compiles clean,
  consistency check passes.
- Old Helium Acrylic and Brave Acrylic removed (see `reports\2026-11-26-mod-audit.md`).
