# Halo owns its system commands; Wispr Flow removed (2026-11-26)

## Halo Launcher 0.6.15 (engine change)

The owner saw Flow Launcher words left in Halo's system commands.

- Cause: the system plugin matches on each command's saved search word, and those words live in
  `%LOCALAPPDATA%\HaloLauncher\engine\UserData\Settings\Plugins\Flow.Launcher.Plugin.Sys\Settings.json`.
  The earlier rebrand only changed the titles, so typing "flow" still found them.
- Three commands led only back to Flow: "Flow Launcher Tips" (Flow's docs), "Check For Update"
  (Flow's updater) and "Set Flow Launcher Theme" (the `fltheme` query).
- Fix, in `work\2026-11-11-halo-launcher\engine\src\HaloEngine.cs` (step "own sys" after the rebrand):
  - every system command's search word goes through `Rebrand()` (old "Flow Launcher", new "Halo Launcher");
    the save step after it writes them to the Settings.json above;
  - the plugin is wrapped in `HaloSys`, which drops the three Flow-only results and the `fltheme` query.
    The commands stay in the list because the plugin looks them up by key.
- The readme lines that said "Flow's plugin store" now say "the community plugin store".
- Build script: the 15 s compile timeout is gone (it killed builds while the CPU was busy).

Rollback:
- engine: `Halo.Engine.dll.bak-<stamp>` beside the live one in the engine folder (stamp in the ship log);
- mod: `C:\ProgramData\Windhawk\ModsSource\local@halo-launcher.wh.cpp.bak-<stamp>` (0.6.14);
- source: `HaloEngine.cs.bak-20261126-0535`;
- the renamed search words: change them back in the system plugin's Settings.json while the mod is off.

Shipped as 0.6.15 at 8:01 am (published). The gate then refused to switch it back on: free memory
was 0.3 GB because another thread's heavy job (a full virus scan of a game dump) held 13.5 GB.
`C:\Users\Public\halo-0616-chain.ps1` waits for memory and switches it on.

## Halo Launcher 0.6.16 (Catppuccin icons for Windows' own apps)

Asked for by the native-icons thread. Halo loads the package logo straight from WindowsApps, and UWP
Assets Redirect Plus only swaps those inside Explorer and Start, so Terminal, Notepad and Paint showed
the stock icons. `LoadBitmap` now asks `ThemeFileFor()` first: it reads that mod's icon theme once
(registry setting `icon-theme`, `theme.ini` in its mod storage) and loads the biggest frame of the .ico.
Stage script: `work\2026-11-26-halo-theme-icons\stage.py`, with an offline compile check in `compile.py`
(clean, no warnings). It also fixes a stray capital in the readme.
Rollback: the `.bak-<stamp>` of the mod source that the install writes, or turn UWP Assets Redirect Plus off.

## Wispr Flow removed

The owner no longer uses it and asked to remove it completely, about 1.2 GB.

- Removed:
  - its app folder in Local AppData;
  - its data folder in Roaming;
  - the Start menu folder "Wispr AI";
  - the taskbar pin shortcut;
  - its `HKCU\Software` keys;
  - the `wispr-flow` link handler.
- The old `%APPDATA%\FlowLauncher` folder was removed too. Halo keeps its own copy in its engine folder.
- Backups: `backups\2026-11-26-wispr-removal\` (registry exports, including `wispr-flow-protocol.reg`).
  The app itself is not kept. Reinstall from its site if it is ever wanted again.

## Halo 0.6.17: lighter glass, like Explorer

The owner said Halo's search window was darker than Explorer and the other apps.
Halo laid Mocha crust (`#11111B`) at 55% over the blur. Explorer's window glass is Mocha base
(`#1E1E2E`) at about 55% with a luminosity layer, so it reads lighter.

- Old: tint `cCrust`, setting `backgroundOpacity` 55 (default 55).
- New: tint `cMochaBase`, setting `backgroundOpacity` 40 (default 40). Description now says
  "40 is the same frosted glass as Explorer".
- The owner's saved setting moved from 55 to 40. Backup of the settings key:
  `backups\settings-material\local@halo-launcher-settings.bak-<stamp>.reg`.
- Scripts: `C:\Users\Public\halo-0617-chain.ps1` (lock, then ship) and `halo-0617-ship.ps1`.
- Rollback: set "Glass darkness" back to 55 in Halo's settings, or import the settings backup and
  reinstall 0.6.16 from the `.bak-<stamp>` of the mod source that the install writes.
