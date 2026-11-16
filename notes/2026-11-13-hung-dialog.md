# System boxes: blur and dark title (Seamless Title Bars 1.2.1 to 1.2.7)

Date: 2026-11-13 to 11-16. Thread: 1a27061b. Owner asks:
- "fix this not responding windows look, make the black area blurry the titlebar dark
  matching the rest of our system"
- (screenshot of "DesktopWindowXamlSource: explorer.exe - System Error", 0xc0000005) "use the
  fix we did for blacked out and light titlebar windows previously, apply it globally so i
  never see this issue on any lingering windows again"

## Why they stayed black
- Windows draws two kinds of box itself, in processes no normal mod loads into:
  - "is not responding" ("Microsoft Windows", #32770): owned by **dwm.exe**.
  - hard-error and session message boxes ("explorer.exe - System Error"): owned by
    **csrss.exe**, a protected process. Nothing can be injected there.
- Stock look for both: body painted flat black, light title.
- Only Seamless Title Bars runs inside dwm.exe (owner-approved list), so the fix lives there.

## Versions
| Version | What it does | Result |
|---|---|---|
| 1.2.1 | worker thread, acrylic accent with a Mocha tint | tint read as flat grey |
| 1.2.2 | trial of three methods (accent, backdrop, both) | backdrop won |
| 1.2.3 | dark mode (20), frame over the whole box, system backdrop 3 | dwm box blurred; csrss box untouched (dark 0) |
| 1.2.4 | csrss boxes set from inside DWM's own window record | dwm box still fine; csrss box unchanged |
| 1.2.5 | 1.2.4 plus readout, setter hooks, hooks on raw addresses | light title gone; with full-glass margins the content sat at the top edge, title missing |
| 1.2.6 | steps picked live from `sysbox.mode` (1 dark, 2 backdrop, 4 margins), default 3 | real box: dark title, dock, blurred frame; body still black |
| 1.2.7 | DWM's own blur-behind for the csrss box body; dark title from DWM on every captioned window | see Verification (1.2.7) |

## Why 1.2.3 missed the csrss box
DWM refuses attribute calls (dark mode, backdrop, extend frame) from one process on another
process's window, and dwm.exe cannot open csrss.exe either. So the worker's calls did nothing.

## Change (1.2.4)
- The WinEvent worker now handles only dwm.exe's own boxes (unchanged path from 1.2.3).
- New `sysbox` part, hooked on DWM's `CWindowList::ShowHide(IDwmWindow*)`. After the original
  runs, under DWM's own lock, it looks up the window's `CWindowData`, reads the HWND, and for a
  top-level `#32770` owned by csrss.exe (`CsrGetProcessId`) calls DWM's own handlers:
  - `CWindowList::SetUseDarkModeColors(window, true)`: dark title
  - `CWindowList::SetSystemBackdropType(window, 3)`: system acrylic
  - writes margins -1 where `ClientMarginsChange` stores them, then
    `CWindowList::OnClientMarginsChange(data)`: the whole box is glass, so its black body
    shows the blur.
- Offsets are read from DWM's code at start, never hard-coded:
  - HWND offset: shared with the caption part (from `CWindowData::IsGhostWindow`).
  - margins offset: the `movdqu [reg+disp32], xmm0` right before the call to
    `OnClientMarginsChange` inside `ClientMarginsChange` (0x10c on this build).
  - lock: the caption part's DWM lock, or the first `lea rcx` + `EnterCriticalSection` in ShowHide.
  If any of these is missing, the csrss part logs "csrss boxes off" and stays out.
- Only window-manager calls that never send a message are used inside the hook
  (GetWindowThreadProcessId, GetClassName, GetAncestor), so DWM cannot wait on the box's thread.
- Build: `work\2026-11-13-hung-dialog\patch124.py` (needs live 1.2.3, sha256 CF1D1A99...),
  `--compile` builds offline.
- Install: `scripts\2026-11-14-seamless-title-bars-1.2.4.ps1 -Action Install`.

## Change (1.2.5)
- 1.2.4 scanned the margins offset through the hook's trampoline. 1.2.5 resolves every DWM address first (no hooks), reads the offsets from the raw code, then sets the hooks.
- Extra hooks on `SetUseDarkModeColors`, `SetSystemBackdropType` and `ClientMarginsChange`: for a csrss box they force dark, backdrop 3 and full-glass margins whenever DWM sets them.
- Readout in the mod's storage (`sysbox.*`): setup bits (63 = all ready), csrss pid, offsets, ShowHide call count, last foreign pid seen, last apply result. Written by the worker thread; no logging inside dwm.
- Build: `patch125.py` (needs live 1.2.4, sha256 2911E646...). Install and rollback: `scripts\2026-11-14-seamless-title-bars-1.2.5.ps1` (rollback reinstalls 1.2.4).
- Readout right after install: setup=63, csrss=1108, margins=268, hwnd=40.

## Change (1.2.6)
- `patch126.py` (needs live 1.2.5, sha256 1175DC6B...). Apply reads `sysbox.mode` from the mod's storage each time; setter hooks only force a step whose bit is on; every apply writes `sysbox.applied` (low bits result, mode in bits 8+).
- Script `scripts\2026-11-14-seamless-title-bars-1.2.6.ps1`: Install, Rollback (to 1.2.5), `-Action Mode -Mode N`.

## Rollback
- `scripts\2026-11-14-seamless-title-bars-1.2.4.ps1 -Action Rollback` reinstalls 1.2.3 from
  `backups\2026-11-14\seamless-title-bars-1.2.4\seamless-title-bars-1.2.3.wh.cpp`.
- Older: `scripts\2026-11-13-seamless-title-bars-1.2.3.ps1 -Action Rollback` goes to 1.2.1.
- Quick off without a reinstall: set `hungDialog.enabled` to 0 in the mod's settings.

## What made the owner's error box
The box in the screenshot is Explorer crashing (0xc0000005). The Windhawk mod
`win7-display-control-panel-restorer` 1.1.0 (third party) crashed Explorer on 11/12 at
2:23 am and on 11/14 at 11:00 am. Both it and windows-update-control-panel-restorer were installed 10 Nov 7:21 pm; the first
Explorer error box on record is 10 Nov 9:52 pm, about 160 since. 14 Nov 8:01 pm: switched off
(`scripts\2026-11-14-disable-win7-display-restorer.ps1 -Action Disable`; `-Action Enable` undoes it;
registry export in `backups\2026-11-14\win7-display-restorer\`). Watch the System log (event 26)
for new "explorer.exe - System Error" boxes; if they continue, the update restorer is next.

Side finding: since 4:27 pm about ten separate-process Explorer hosts (`/factory,{75dff2b7...}`),
started the same second as each error box, stayed alive with no window, about 150 MB each.

## Verification
- 1.2.4 live: dwm box blurred grey with the dark dock (`hung124.png`); csrss box unchanged (`sys124.png`).
- 1.2.5 live: readout setup=63 (all parts found), csrss 1108, margins 0x10c, hwnd 0x28, setters 3. `sys125.png`: light title gone but layout shifted (full-glass margins).
- 1.2.6 live, mode 3, on a real "explorer.exe - System Error" box (5:01 pm): dark title, our dock with the blue to mauve edge, blurred frame (`real126.png`). Body still black.
- Not yet proved: a blurred body (mode 7 trial queued until that box is closed and the owner is away).

### Full-glass trial (mode 7), 14 Nov 8:16 pm

- Ran on the installed 1.2.6 with the owner away, desktop lock held. Readout `applied=1799` (dark, backdrop and margins all applied).
- Result: same break as 1.2.5. The title strip disappears, the content jumps to the top edge and a grey strip shows at the bottom. The body stays black.
- Mode 3 (dark title, dock, blurred frame) gives the right layout. It is set back as the live value and stays the default.
- Open: the black body. Csrss paints its client area solid black; extending the frame into it moves the layout instead of turning it to glass. Needs a different approach (for example a dwm-side backdrop under the client area), not more margin tweaks.
- Captures: `work\2026-11-13-hung-dialog\sys126-m7.png`, `sys126-m7-late.png`, `sys126-m3.png`.

## Change (1.2.7), 16 Nov
Owner: "the task is still not done; we need to make sure that it's consistent system-wide".
- Black body: the margins write is gone. Apply calls DWM's own
  `CWindowList::BlurBehindChange(IDwmWindow*, DWM_BLURBEHIND const*)` with enable on. That
  handler takes DWM's lock itself, sets the blur-behind bit in the window record and calls
  `CTopLevelWindow::OnBlurBehindUpdated`, so the client area is drawn see-through (black
  shows the backdrop) and the layout is untouched. Symbol is optional: missing means
  `sysbox.blurBehind=0` and the body step is skipped.
- System-wide titles: new step 8. The ShowHide hook gives every captioned top-level window
  DWM's dark title (`SetUseDarkModeColors` true), and the setter hook turns a "light" request
  into dark. This covers programs no mod loads into: the engine Exclude list (Git's tools,
  conhost, node and others), protected processes and games (open scan on 16 Nov: `s1x.exe`
  "S1 Console" was the one light title). Same message-free rule as the csrss check.
- A window already open before the install picks it up the next time it is shown.
- `sysbox.mode` default 15 (1 csrss dark, 2 backdrop, 4 see-through body, 8 every window).
  Install sets 15; Rollback reinstalls 1.2.6 and sets 3.
- Build: `work\2026-11-13-hung-dialog\patch127.py` (needs live 1.2.6, sha256 2EB74348...),
  `--compile` builds offline (exit 0). Script: `scripts\2026-11-16-seamless-title-bars-1.2.7.ps1`
  (Audit, Install, Rollback, Mode). Backup dir `backups\2026-11-16\seamless-title-bars-1.2.7\`.
- Test: `test-127.ps1` waits for 90 s idle and no real error box, captures a window from Git's
  mintty (never injected) on 1.2.6, installs under the engine lock, captures it again and
  shows the csrss test box. Tools: `outsider.py`, `syserr.py`, `darkscan.py` (DWM's
  readable dark flag only reflects what the app set, so proof is the screen capture).

## Rebase to 1.2.9 on the tray thread's build, 17 Nov
- The 1.2.7 install was refused twice: first by the settings-engine gate (window behind the
  template), then by the new menu-reference gate. Meanwhile another thread installed a synced
  1.2.7 (sha256 C6FF8EB5...), so the change was rebased as 1.2.8 with a port of Clipboard's
  menu renderer (`menu-port\`, offline render `menu-port\tray-menu.png`).
- At 2:40 am the rules moved again: the engine template now carries `Set_TrayMenu` (Launchpad
  2.6.0) and fleet-tray-43d9edd6 holds the Title Bars source, with its own staged 1.2.8
  (engine sync + `Set_TrayMenu`, sha256 FA0D8947...). My menu port is dropped; theirs wins.
- 1.2.9 = their build + only the DWM part of patch127 (`patch129.py <base>`, writes
  `v129\` and `v129\base.txt`). On their staged 1.2.8 it compiles clean (heavy gate, 0 errors).
  Its gate failures (menu-reference, Set_MenuCur behind) come from their unfinished menu move.
- Script: `scripts\2026-11-17-seamless-title-bars-1.2.9.ps1` (Audit, Install, Rollback, Mode).
  Base version and hash come from `v129\base.txt`; Install copies the base aside,
  Rollback reinstalls it and sets mode 3. Backups `backups\2026-11-17\seamless-title-bars-1.2.9\`.
- `test-129.ps1` runs outside T3 (WMI start, survives T3 restarts), log `test-129.log`. It waits
  until live has their engine menu, nobody claims the source, both gates pass and 1.2.9
  compiles; or until live already has the change (they folded it in). Then, with the owner away
  90 s and the desktop lock held: captures before, installs under the engine lock, captures a
  Tk window from Git (never injected, never asks for dark), the tray menu and a csrss test box.
- Mishap 2:45 am: `syserr.py --help` has no argument parsing, so it showed one test box for its
  9 s timeout while the owner may have been at the PC. It closed itself. Do not pass flags to it.
- Still to prove live: see-through csrss body with the layout intact, dark title on the Tk window.
