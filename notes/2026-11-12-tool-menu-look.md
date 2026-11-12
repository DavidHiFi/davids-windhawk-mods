# 2026-11-12 Tool mod menus get Launchpad's look

Owner (with screenshots): Key Click's tray menu hover was a flat grey; Launchpad's is the blue to
mauve pill. Every mod menu has to match Launchpad's.

## Cause
- Launchpad's menu lives in explorer, where Seamless Flyouts paints it (Mocha body, the pill,
  submenus that touch their parent).
- Tool mods run in their own windhawk-mod.exe. Flyouts never loads there, so their menus show the
  plain dark hover.
- Mixer already carries the fix inside itself: the shared block (menu room + pill + skin with a
  CBT hook that skins every #32768 menu of the process). Dictate and Magic Pointer carry an older
  copy without the CBT hook.

## Fix
- `scripts\2026-11-12-tool-menu-look.py <mod-id>`: reads the live source, copies Mixer's block in
  (or replaces an older one), calls `SeamlessMenuSkin::Init()` first thing in WhTool_ModInit and
  `Uninit()` in WhTool_ModUninit, adds missing libraries, bumps the version. Output goes to
  `work\2026-11-12-tool-menu-look\`; nothing live is touched.
- `work\2026-11-12-tool-menu-look\compile-offline.ps1 -Id <id>`: Windhawk's clang, DLL to %TEMP%.
  Only InternalWh_* link errors are expected.
- `work\2026-11-12-tool-menu-look\install.ps1 -Id <id> -BaseHash <live sha256>`: elevated, under
  the windhawk-engine lock, through heavy.py. Install-StagedMod refuses if the live source changed
  since the copy was built; then the helper restarts and the registry version is checked.
- Rollback: Install-StagedMod's backup in `backups\settings-material\` (previous source), installed
  the same way.

## Which mods
| Mod | Before | Status |
|---|---|---|
| Seamless Key Click | plain hover | 1.0.2 live 8:52 am (kept in bd0ca06f's 1.0.3), recorded: ring pill |
| Seamless AutoClicker | plain hover | 1.6.2 live 10:36 am, helper running |
| Seamless Listary | plain hover | 1.1.3 live 10:36 am, helper running |
| Seamless Crash Watch | plain hover | carried by crash-toast's 1.2.2 |
| Seamless Window Manager | older skin, no pill | 2.5.3 live 10:38 am, helper running |
| Seamless Media Player | already skinned | not a windhawk-mod.exe tool: both halves are explorer.exe, where Flyouts paints menus. 1.10.12 (10:20) added a second skin by mistake; 1.10.13 (10:32) is 1.10.11 byte for byte |
| Clipboard Manager, Color Picker | no native menus | nothing to do |
| Dictate, Magic Pointer | pill, older block | tray hover already matches; no CBT hook (title bar menus); left to their owners |

All five carry Mixer's block byte for byte (the script reports "already has the current menu look").
The script now refuses a mod that also runs outside Windhawk's own processes.

Listary: the block sits inside listary-port's core span (splice.py swaps it), so they copy it into
their src/core.cpp before the next splice (asked on the coop board).

## Proof
- Key Click: `work\2026-11-11-seamless-key-click\media\key-click-tray-menu.mp4` (and .gif, .png).
