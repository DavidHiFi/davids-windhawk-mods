# Seamless Winver Configurator (new mod, 2026-11-26)

Six About Windows mods merged into one: Fully Customizable WinVer (ItsTauTvyDas), Classic Winver and
Winver Text Customizer (aubymori), Winver Custom Text (Thomas Shrader), Winver Redirector (winui64) and
Text Replace (m417z). Id `local@seamless-winver-configurator`, GPL-3.0-or-later.

## Build

- Work folder: `work\2026-11-26-seamless-winver-configurator\`. Parts 00 header, 10 settings, 20 redirect and
  ShellAbout text, 30 classic dialogs, 40 custom dialog, 50 text replace, 60 lifecycle. The helper ports of 40 and
  50 were cancelled, so both were written in this thread.
- Custom dialog rules: every change to the box runs on its own thread (WinEvent hook for a new box, registered
  messages for reload, teardown, setup and logo capture). Turning the mod off puts the stock box back in place.
- `python gen.py` assembles them with the Launchpad settings engine (sliced from Seamless Crosshair, renamed
  `swcset`), a field table generated from the settings block, the six credits and the clean gradient tray icon.

## How it runs

- `@include winver.exe` and `windhawk.exe` only. Other apps need "Include other apps" plus an entry in the
  mod's Advanced tab; they get only the hooks their settings need, and reload when that changes.
- winver: every hook at start (ShellAbout, text replace, custom dialog watcher), settings apply live.
- Tool process (windhawk.exe -windhawk-tool-mod): settings window and tray (click: settings, right-click:
  Open About Windows / Settings). "Open About Windows after saving" starts winver only when none is open.

## Checks so far

- Full source (7,202 lines): syntax check compiles. settings-engine add + check: in sync. settings-material: ok.
  mod-consistency: 0 fail, 0 warn.
- Test PC scripts: `D:\Agent Work\swc\` (swc-driver.ps1 on Warden; phases A default, B live change, C off while
  open, D classic, E text replace, F redirect, G close animation).

## State at handoff (2026-11-26, moved here from a Discord workspace thread)

- Done: all seven parts written, `gen.py` gives 7,218 lines; syntax, settings-engine add + check, settings-material
  and mod-consistency all pass on that build. Test copy refreshed (`D:\Agent Work\swc\swc.wh.cpp`, defaults.json 89).
- Not done: the first reviewer delegate was cancelled before it wrote `work\2026-11-26-swc-scratch\review-1.md`;
  start a fresh review. Then the test PC run (`swc-driver.ps1`, lock `coop lock test-pc --queue`), install with
  `Install-StagedMod.ps1 -BaseHash new` (elevated), preview PNG from the A-default shot, final reviewer, coop note.
- Leave the store Text Replace mod alone: thread 540f02cc folds it into Seamless Input and retires it itself.
  This mod later joins the Seamless Apps suite; post a coop note when it is live so that generator can read it.
- Test PC risks to look at: stock banner on the Mocha background, SysLink licence text colour, fade-in flash,
  32-bit tool process in Windhawk 1.7.3 needs the i686 build.
- Portfolio: the Windows mods card covers new mods; no card change needed.

## Test PC runs 1 to 3 (this thread)

- Run 3: A default, B live change, B3, C off while open and E text replace pass. F redirect and G close
  animation passed in run 2. B2 glass shows grey: Hyper-V draws no glass, not a mod fault. D classic falls back
  to the stock box because the VM has no classic shell32 resources (expected).
- Fixed from the runs: ApplyFrame dropped WS_VISIBLE (box vanished after a frame change); the 32-bit build
  failed on EnumThreadWindows/EnumWindows callbacks; a `cur` redefinition.
- No tray in run 3: the tool process started but made no tray window. Cause: the mod rolled its own tool-mod
  lifecycle and treated any process not named windhawk.exe as a hook process. Windhawk 2.0 alpha runs tool
  mods in windhawk-mod.exe. Fix: `#include <windhawk_tool_mod.h>` with WhTool_* for the tool process and
  WhToolLauncher_* for windhawk.exe (launch) and for winver and added apps (hooks, no launch), the same
  pattern as Seamless Window Manager. Windhawk 1.7.3 on the test PC lacks that header; `swc-setup.ps1` copies
  the tower's copy into the VM's compiler folder.
- Banner rice: the stock Windows banner stayed white on the Mocha box. The dialog now repaints the banner
  band after each WM_PAINT: white goes to the box colour, black text to the text colour, the blue logo keeps
  its colour. It runs only while the band is still light, so it never paints twice.

## Test PC runs 4 and 5

- Run 4 was cut short by a T3 restart; its trace showed the tray was fine and the probe was wrong:
  `swc-probe.ps1` passed `$null` to FindWindow, which PowerShell sends as "" (fixed with `[NullString]::Value`).
- Run 5 (8:20 to 8:32 am, driver started detached so T3 restarts cannot kill it): every phase passes.
  Tool process up, tray window found, settings window opens (921x648) and closes, banner dark, live change,
  mod off while open puts the stock box back, classic, text replace, redirect (notepad opens, no winver),
  close fade (half faded at 60 ms, gone at 188 ms). Explorer stayed up; the only app errors were Windows
  activation in the VM.
- Found from the settings shot: Theme preset, Animation speed and XP branding showed as text boxes.
  `gen.py` only read option lines indented deeper than `$options:`; this header puts them at the same depth.
  Fixed, all three are dropdowns now; the four checks and both compiles pass again.

## Review 1 (Sonnet, Halo was full)

`work\2026-11-26-swc-scratch\review-1.md`: 0 high, 2 medium, 5 low. Fixed:
- "Top" z-order never applied (HWND_TOP is 0, the null check skipped it).
- A redirect pointing at winver itself would start winver forever: now skipped, the normal box shows.
- Settings window closed while it was still opening left its thread running: the thread now closes itself
  when a stop came in first (patched into the engine slice by `gen.py`).
- A failed hand-off to the box's thread now removes its setup subclass.
- A logo at native size is capped at 1024 px on its longest side.
- Empty text falls back to the default (Windhawk cannot tell empty from unset): the descriptions now say
  so and suggest a space to hide a line.
Left as is: a winver UI thread hung for 3 s at the moment the mod unloads keeps its subclasses; nothing can
remove a comctl subclass from another thread while that thread is hung.

## Final review (Sonnet, Halo refused the model name)

`work\2026-11-26-swc-scratch\review-final.md` (copied below before the scratch folder went): SHIP, all six
review-1 fixes landed, 0 high, 0 medium, 4 low. Fixed: the tool process now stops the tray before it closes the
settings window, so a tray click mid-unload cannot open a new one. Left as is (the process exits right after, or
it needs a deliberate odd setting): the settings thread handle touched by two threads at unload, a plain
SendMessage in the failed hand-off cleanup, and a redirect to `cmd /c winver` looping.
Rebuilt (7,217 lines, staged copy starts caabaee7): all four checks and the 32-bit compile pass.

## Install

- Two detached installs died while they waited for the engine lock (a T3 restart killed them; nothing was
  installed). The third starts from a one-shot scheduled task: `D:\Agent Work\swc\install-launch.ps1`.
- Try 4 waited 25 min for the engine lock and gave up. Try 5 (90 min wait) got the lock at 10:28 am and
  installed v1.0.0 at 10:29 (backup `local@seamless-winver-configurator-20261126-1029.wh.cpp`), watched 60 s:
  desktop fine. Installed source matches the staged copy line for line (only line endings differ). Tool
  process `windhawk-mod.exe` up at 10:36. Shell pid unchanged since 9:08, no crash dumps.
- Published: mods 1a90dbe, then grouped under "Windows and menus" in `mods/categories.json` (1092313),
  feed ce660d3. One-shot install task removed.

## Rollback

Turn the mod off with `scripts\Set-ModState.ps1 -Id local@seamless-winver-configurator -Off`.
Header backup: `00-header.cpp.bak-20261126` in the work folder.
