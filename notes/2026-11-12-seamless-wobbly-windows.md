# Seamless Wobbly Windows 1.0.0 and Seamless Window Manager 2.5.2

Date: 2026-11-12. Thread: Seamless Wobbly Windows Mod Overhaul.

## What

- New mod `local@seamless-wobbly-windows` 1.0.0, a GPL fork of HeyJeay's Window Wobble 1.0.0.
  - Follow mode: Windows (or the window manager) still moves the real window, which is cloaked;
    the overlay follows its rect. Snap, Snap Layouts and drag-to-restore keep working.
  - Seamless Borders ring is drawn into the wobble texture (Borders' own renderer, copied
    verbatim), so it bends with the window. Borders hides its own ring while the window is cloaked.
  - Alt-drag from Seamless Window Manager wobbles: SWM posts `SeamlessWobblyWindows_ExternalDrag`
    (wParam 1 start, 0 end) to the moved window.
  - Renderer: desktop-sized flip swapchain, frame latency 1, dirty-rect presents, split position
    and UV streams, 16-bit indices, fixed 1/480 s physics steps, GPU memory freed after idle.
  - Corners follow Custom Window Corner Radius when it is on.
  - `@exclude dwm.exe` and the shell hosts. Nothing loads into dwm.
- `local@seamless-window-manager` 2.5.1 to 2.5.2: posts the start and end message around its
  low-level move drags (not resizes). No other change.

## Old, new, rollback

| Item | Old | New |
|---|---|---|
| Seamless Window Manager | 2.5.1 | 2.5.2 |
| Seamless Wobbly Windows | not installed | 1.0.0, enabled |
| Wobbly Windows (lalimatyus) | disabled | disabled (unchanged) |
| Window Wobble (HeyJeay) | disabled | disabled (unchanged) |

Rollback:

- Window manager: `backups\2026-11-12\seamless-window-manager\2.5.1-pre-wobble.wh.cpp` (also
  `backups\settings-material\local@seamless-window-manager-20261112-0518.wh.cpp` and the `.reg`
  beside it). Install it with `scripts\Install-StagedMod.ps1` (elevated), base hash = sha256 of
  the live 2.5.2 source.
- Wobble mod: disable it in Windhawk, or remove it. Nothing else depends on it; the window manager
  message is ignored by apps without it.

## Files

- Source: `work\2026-11-11-wobbly\mod.template.cpp` (shaders spliced by
  `scripts\2026-11-11-wobbly-splice.py`), staged `local@seamless-wobbly-windows.wh.cpp`.
- Shaders: `work\2026-11-11-wobbly\wobble.hlsl`, `vs.h`, `ps.h`.
- Build: `scripts\2026-11-11-wobbly-build.ps1` (offline, through the load gate).

## Log

- 3:21 am: both mods build clean offline (`-Wall`, no warnings).
- 5:18 am: Seamless Window Manager 2.5.2 installed, registry v2.5.2, new DLL loaded in Explorer.
  Shell check healthy (0.8 GB, 364 GDI).
- Wobble mod install waits for the owner to be idle 5 min (window-look rule).
- Slip: the 5:18 am window manager install ran without taking the `windhawk-engine` coop lock
  (another thread held it). No harm seen; every later install takes the lock first.
- `Install-StagedMod.ps1` gained `-BaseHash new` for a first install (refuses if the mod
  appeared meanwhile).
- Live test: `scripts\2026-11-12-wobbly-live-test.py <new dir>` opens an owned test window (so the
  window manager does not tile it), does a caption drag, an Alt-drag, a flick and a snap to the
  top edge, samples the cloak state, records the primary screen (gfxcapture monitor 1 =
  2560x1440) and restores the cursor. Run only while the owner is away, under `coop lock desktop`.
- 9:04 am: Seamless Wobbly Windows 1.0.0 installed (owner idle, engine lock held). Registry v1.0.0,
  enabled, DLL loaded in 270 processes. Window Wobble and Wobbly Windows stay disabled.
  Registry backup: `backups\2026-11-12\seamless-wobbly-windows\engine-mods-before-*.reg`.
- 10:02 am: Explorer stopped (Winlogon 1002, no crash event, no dump). Six seconds earlier the
  AI Usage thread's `proof120.ps1 -Mode open` invoked a taskbar tile in Explorer through UIA, and
  File Operation Styler Plus had been installed at 10:01. The wobble mod had been in Explorer for
  an hour with no drags. Coop note left for the AI Usage thread. Shell healthy afterwards
  (0.3 GB, 121 GDI).
- 11:28 am: Explorer restart was the planned guarded restart that removed the old
  uwp-assets-redirect mod (another thread, owner order). Not this mod.
- 10:58 am (2026-11-12): live test skipped because the owner came back. Window Manager 2.5.3 (menu look, by the
  Key Click thread) keeps the wobble drag message. Test re-armed at 2:02 pm.

## 1.1.0: Acrylic Color Glows merged in (2026-11-13)

- Acrylic Color Glows (HaVeN80, GPL-3.0) is now part of the mod: `work\2026-11-11-wobbly\glow.part.cpp`,
  spliced in at `/*@@GLOW@@*/`. Mocha gradient defaults (#89B4FA, #CBA6F7, #B4BEFE), every option kept.
  ACG itself was never installed, so nothing doubles up.
- Process roles: in apps the mod wobbles (as 1.0). In `windhawk.exe` it launches one tool process
  (`windhawk.exe -tool-mod local@seamless-wobbly-windows`, mutex `windhawk-tool-mod_<id>`) that draws
  every glow on the compositor (Windows.UI.Composition, GPU). Service and session 0 are skipped.
  The launcher starts the tool only while the glow is on, and again if the glow is turned on later.
- Glow inside the wobble: the tool publishes its clock and windows in a read-only shared map
  (`Local\SeamlessWobblyWindows.Glow`, seqlock). On a drag the wobble checks the window is acrylic
  (backdrop 3 or accent 2 to 4) and has a glow, finds the backdrop's flat colour in the capture
  (title band, 30% share), and the pixel shader paints the same sprites at the same clock time
  onto that colour only (text and controls untouched). Up to 32 sprites in a 1.6 KB constant buffer,
  refreshed per drawn frame; held still it redraws at 60 fps only while the glow moves.
- Hand-off: the window property `SeamlessWobblyWindows.Glow` is set before the cloak and kept 0.5 s
  after the drag; the tool keeps the glow's clock live and shows its own glow at full opacity, no fade,
  when the window lands.
- Imports: same static set as 1.0 (dwmapi, gdi32, advapi32, user32, kernel32); ole32, oleaut32,
  shcore, shell32 and the WinRT API sets are delay-loaded, so app processes load nothing new.
- Builds: x64 and x86 clean with `-Wall` (11:00 am).

| Item | Old | New |
|---|---|---|
| Seamless Wobbly Windows | 1.0.0 | 1.1.0 |
| Settings | 12 wobble keys | same, plus glow defaults written only where missing |

Rollback: disable the mod, or reinstall the 1.0.0 source (`backups\settings-material\
local@seamless-wobbly-windows-<stamp>.wh.cpp`, written by Install-StagedMod) with
`scripts\Install-StagedMod.ps1`; the registry key before 1.1.0 is in
`backups\2026-11-13\seamless-wobbly-windows\mod-key-before-1.1.0-*.reg`. Ending the tool process
removes every glow; the wobble keeps working without it.

### 1.1.0 install and live test (2026-11-13)
- 11:22 am: installed at idle under the engine lock; 39 glow defaults written where missing.
- 11:27 am live test (main screen is gfxcapture index 3 today, not 1): caption drag, flick and
  Alt-drag all wobble with the glow painted inside; cloak and overlay states right, Explorer stable,
  cursor restored. Two defects found:
  1. Too bright while wobbling: about 3.5x the real glow seen through the acrylic (held: column
     peak about 60 over a key of 35; at rest the real glow adds about 7). Visible drop on release.
  2. Glow freezes while the window is held still mid-drag. Cause: the wobble overlay is a topmost
     window over the whole virtual screen, so Windows reports QUNS_BUSY ("full-screen app") and
     the glow tool's "pause in full screen" power rule froze every glow for the drag.

## 1.1.1: glow fixes (2026-11-13)
- Glow tool: QUNS_BUSY is ignored while a visible `SeamlessWobblyOverlay` window exists
  (D3D full screen and presentation mode still freeze).
- Wobble: a frozen glow is re-checked four times a second while held, so it starts moving
  again on its own; `live` is also read at drag start.
- Strength: the painted glow is scaled by how much the window lets through: acrylic backdrop
  0.28 (measured), accent blur 1 - tint alpha. "Glow strength while wobbling" 100 now means
  "matches the resting window".
- Builds x64 and x86 clean, same imports as 1.1.0.

| Item | Old | New |
|---|---|---|
| Seamless Wobbly Windows | 1.1.0 | 1.1.1 |
| Painted glow strength at 100% | 1.0 | 0.28 on acrylic |

Rollback: reinstall the 1.1.0 source that Install-StagedMod backed up (newest
`local@seamless-wobbly-windows-*.wh.cpp` in its backup folder) with `scripts\Install-StagedMod.ps1`,
or restore `work\2026-11-11-wobbly\mod.template.cpp.bak-20261113-1136` and
`glow.part.cpp.bak-20261113-1136`, splice and install. Registry key before install:
`backups\2026-11-13\seamless-wobbly-windows\mod-key-before-install-*.reg`.

### 1.1.1 install and the missing glow (2026-11-13)
- 11:39 am: 1.1.1 installed at idle under the engine lock; the glow tool restarted at 11:39:39
  with the 1.1.1 DLL. Live takes at 11:40 and 11:46 showed the wobble but no glow at all.
- Read-only checks: the shared map is published every 2 s with running 0 and count 0; no other
  mod's key changed after 11:16; transparency on; tool and test window both medium integrity in
  session 1; the test-window code is unchanged since the 11:31 probe that did show a glow on 1.0.
- 12:00 pm diagnosis under the desktop lock (`scripts\2026-11-13-wobbly-glow-diag.py`): posting
  "settings changed" to the tool's controller did nothing; restarting only the glow worker did
  nothing either. So the cause is not stuck state.

Registry change made by that diagnosis (worker restart, `scripts\2026-11-13-wobbly-glow-worker-restart.ps1`):

| Value | Old | During | New |
|---|---|---|---|
| `Settings\glow.enabled` | 1 | 0 (12:00:56 pm) | 1 (12:01:00 pm) |
| `SettingsChangeTime` | 1794445476 | bumped | bumped again |

Rollback: none needed (the setting is back to its old value); the key before it is in
`backups\2026-11-13\seamless-wobbly-windows\mod-key-before-worker-restart-*.reg`.

## 1.1.2: glow check report (2026-11-13)
- The glow tool's checks are split out (`BasicReject` returns which check turned a window down).
- A window that sets the property `SeamlessWobblyWindows.GlowWatch` gets a report in the map's
  spare field (renamed `watch`): reject code, seen, process name read, matched, skipped,
  can't create, has effect, threw, no compositor, hidden, frozen, a refresh counter and the
  window's backdrop type. Cost: one GetProp per top-level window per refresh.
- The test window sets the property; the drag test logs the field with every map change.
- Build script: `$p.Handle` is read after Start-Process so the exit code survives (the 12:09
  build "failed" with an empty exit code though the DLL was fine).
- Builds x64 and x86 clean.

| Item | Old | New |
|---|---|---|
| Seamless Wobbly Windows | 1.1.1 | 1.1.2 |
| Map field at offset 52 | `pad`, unused | `watch`, the report |

Rollback: reinstall the 1.1.1 source (`work\2026-11-11-wobbly\local@seamless-wobbly-windows.wh.cpp.bak-20261113-1208`,
or the copy Install-StagedMod backs up) with `scripts\Install-StagedMod.ps1`. Part backups:
`mod.template.cpp.bak-20261113-1207`, `glow.part.cpp.bak-20261113-1207`.

### 1.1.2 install: no glow process at all (12:11 pm)
- 1.1.2 installed fine (registry v1.1.2, wobble test passed, Explorer untouched), but the
  shared map was gone and no `-tool-mod "local@seamless-wobbly-windows"` process existed.
- Cause, a start-up race: on an update the engine unloads the old DLL in the glow process
  (which then calls ExitProcess) and loads the new one in the launcher (windhawk.exe tray).
  The new launcher's AfterInit checked "does the tool mutex exist?" while the old glow
  process was still closing, saw it, and started nothing. At 11:39 the old one happened to
  close first. The same flaw is in every version since 1.1.0.

## 1.1.3: glow process always comes back after an update (2026-11-13)
- The glow process now *owns* the mutex instead of merely creating it: it opens it and waits
  up to 8 s for ownership (an old glow process that is closing hands it over, even if it
  ends without releasing). If it can't get it, another glow process is running and it leaves.
- The launcher starts a glow process every time the mod is loaded or updated; on a settings
  change it starts one only if nothing owns the mutex (checked without waiting).
- Builds x64 and x86 clean.

| Item | Old | New |
|---|---|---|
| Seamless Wobbly Windows | 1.1.2 | 1.1.3 |
| Glow process dedupe | mutex already exists, exit | wait up to 8 s to own it, else exit |
| Launcher after load | skip if mutex exists | always start one |

Rollback: reinstall the 1.1.2 source (`work\2026-11-11-wobbly\local@seamless-wobbly-windows.wh.cpp.bak-20261113-1216`
or the installer's own backup) with `scripts\Install-StagedMod.ps1`. If the glow process is
missing after a rollback, bump any glow setting once to start it.

### 1.1.3 live (12:18 pm): glow process back, still no glow
- After the 1.1.3 install the glow process started on its own (12:18:17 pm), and the map was
  back. So the start-up race fix works.
- The 1.1.2 readout for the test window said: seen, passes every basic check, process name
  read, **not matched**, backdrop type 0. Read from outside, other windows report their
  backdrop fine (Crash Watch settings: 1), so the read works; the test window's acrylic
  setting does not show from outside. Still being checked (the test now reports it).
- Found a real miss on the way: **Helium's program file is `chrome.exe`** (product name
  "Helium", in `%LOCALAPPDATA%\imput\Helium\Application`). The default list says
  `helium.exe`, so Helium windows never matched. Brave is not installed on the tower.

## 1.1.4: app lists also match the product name (2026-11-13)
- Each new process is read once: file name, plus "<product name>.exe" from the program's
  version info (version.dll, loaded on first use). An entry in Glow apps or Never glow these
  apps matches either. So `helium.exe` finds Helium's chrome.exe, and Google Chrome would
  not be caught by it.
- Settings text for Glow apps says so.
- Test: the test window prints whether its acrylic backdrop stuck (inside its own process),
  the driver reads it from outside too, and the map log carries the glow count.
- Builds x64 and x86 clean.

| Item | Old | New |
|---|---|---|
| Seamless Wobbly Windows | 1.1.3 | 1.1.4 |
| Glow apps match | program file name | file name or product name |

Rollback: reinstall the 1.1.3 source (`work\2026-11-11-wobbly\local@seamless-wobbly-windows.wh.cpp.bak-20261113-1544`)
with `scripts\Install-StagedMod.ps1`. Part backups: `*.bak-20261113-1215`.

### 1.1.4 live (5:46 pm onward)
- Installed, registry 1.1.4. The glow map shows Helium matched: running 1, count 1.
- The install task hung for its full 2 h limit: a `windhawk-cli.exe` child never exited, and
  the elevation wrapper waits for every descendant. Stopped it with
  `scripts\2026-11-13-stop-hung-windhawk-cli.ps1` (stops the given pid only if it is
  windhawk-cli). The mod was already installed; nothing else was touched.
- Why the test window never glowed: **Seamless Flyouts hooks DwmSetWindowAttribute in every
  process** and, with its background set to acrylic blur, turns a program's acrylic request
  (attribute 38 = 3) into its own accent blur. The call returns S_OK and the window reads 0.
  Reading the accent blur from another process is refused (GetWindowCompositionAttribute,
  error 87), so the glow's automatic acrylic check cannot see those windows on this PC.
  Programs in Glow apps (Helium) are unaffected. Not changed: Seamless Flyouts is its own mod.
- Test fix: the test window now calls a private copy of dwmapi.dll (in %TEMP%), which the
  hook does not cover, so DWM gets the real acrylic request, as on a PC without Flyouts.
  Backup `scripts\2026-11-13-wobbly-glow-test.py.bak-20261113-1750`.
- Seen on the way, not ours and known since 2026-10-26: the engine Include ends in dwm.exe and
  Seamless Title Bars names dwm.exe. Left as is.
- Second hold-up, found in the first take with the private dwmapi: Window Animations re-applies
  the backdrop after its open animation, through the same Flyouts hook, so it went back to 0.
  The test window now re-asserts acrylic every 0.5 s through the private copy if it changed.

### 1.1.4 glow drag test passes (5:58 pm)
- Take `live-1.1.4-175807`: test window acrylic 3 in and out of its process, glow map
  matched + has effect, 2 glows (Helium and the test window).
- Band above the cards, final drag position (900x70 px): during the hold the glow keeps
  moving (frame-to-frame mean change 0.64 over 0.3 s), across the release the change is 0.16
  mean, 6 max, which is encoder noise level. Release brightness step: red 0.85, green 0.33,
  blue 0.4 of 255. Under the 2-level bar.
- Found: after the flick drag the glow stood still for about a second (frames 10.2 to 10.8 s
  identical, map shows the frozen bit). Windows still reports "busy" for a moment after the
  wobble overlay hides, and the refresh that follows the drag froze the glow until the next
  2 s poll.
- Also seen: the hung `windhawk-cli.exe` (pid 17796) is a dead process (HasExited, one
  suspended thread) kept by an open handle; the Windhawk tray still shows its "Mod tasks in
  progress" window with our mod "Uninitializing". Our mod does nothing there (no wobble
  worker in a windowless process); left alone, it clears when Windhawk restarts.

## 1.1.5: glow does not freeze after a drag (2026-11-13)
- The glow remembers when it last saw a wobble (overlay up, or a glowing window cloaked or
  uncloaked while the overlay exists) and ignores "busy" for 3 s after. A real game is still
  caught by the next 2 s poll.
- Builds x64 and x86 clean.

| Item | Old | New |
|---|---|---|
| Seamless Wobbly Windows | 1.1.4 | 1.1.5 |
| Glow after a drag | could stand still about 1 s | keeps moving |

Rollback: reinstall the 1.1.4 source (`work\2026-11-11-wobbly\local@seamless-wobbly-windows.wh.cpp.bak-20261113-1802`)
with `scripts\Install-StagedMod.ps1`. Part backups: `*.bak-20261113-1802`.

### 1.1.5 live (6:03 pm)
- Installed at idle, registry 1.1.5, install did not hang. Explorer pid unchanged.
- Take `live-1.1.5-180454`: map never shows the frozen bit, glow running the whole take.
- Hold: frame change 0.84 mean over 0.3 s (moving). Release step about 1 level of 255 on each
  channel, change across the release 0.24 mean, 6 max (noise level).
- After the flick: 1.06, 0.59, 0.37 mean change per 0.3 s, where 1.1.4 showed 0.0. Fixed.
- Clip: `live-1.1.5-180454\glow-drag.mp4` and `glow-drag.gif`.

## 1.1.6: smooth edges, gradient effect (2026-11-13, 8:43 pm)
- Owner (8:20 pm): "weird shimmering at the top of the border", "2 weird boxes inside of the
  window", the glow "looks a little bit off like if it jumps", wants clean Mocha blue to mauve
  gradient.
- Boxes: the two dark cards were the test window's own paint, not the mod. Test window now
  paints black only.
- Edges: the spring grid is drawn through Catmull-Rom curves at 64 drawn cells per side, so
  a bent edge is a curve, not straight segments.
- Glow effect set to gradient (blue #89B4FA to mauve #CBA6F7); install defaults use it.
- Live take `live-1.1.6-204443` showed three faults left: a fold ("fin") at the top-left
  edge during the drag at 5.7 s, the gradient barely visible (about 7% tint), and a step of
  about 7 levels of 255 at grab and release.

| Item | Old | New |
|---|---|---|
| Seamless Wobbly Windows | 1.1.5 | 1.1.6 |
| glow.effect (registry) | glows | gradient |

Rollback: reinstall `local@seamless-wobbly-windows-20261113-2043.wh.cpp` (ModsSource backup,
1.1.5) and restore the registry backup in `backups\2026-11-13\seamless-wobbly-windows\`.

## 1.1.7: no fold, glass match, stronger gradient (2026-11-13, 8:56 pm)
Causes, from the 1.1.6 take:
- Fold: only the grid point under the cursor is pinned. Its neighbour on the top edge could
  trail by more than one grid cell and cross under it. Fix: while held, each point may trail
  its rest spot by at most half its distance from the held point (and never more than the old
  limit). The offset field then stretches at most 1:2, so the sheet cannot turn over.
- Jump: the capture (PrintWindow) draws acrylic glass as a flat stand-in, about 41,39,59,
  while the live glass is about 34,34,54. Fix: at the grab, while the real window still shows,
  read 25 small squares of the live glass from the screen, subtract the glow, take the median
  and paint it over the stand-in in the shader. Kept off if the result is more than 0.1 away
  from the stand-in (something covering the window).
- Faint gradient: the stops were 0.75 x opacity. Now 2.5 x opacity, capped at full (about
  0.8 at the default). Same constant in the glow tool and the wobble copy, so they still match.

| Item | Old | New |
|---|---|---|
| Seamless Wobbly Windows | 1.1.6 | 1.1.7 |
| Gradient stop alpha | 0.75 x opacity | 2.5 x opacity, capped |
| Held trail limit | 0.35 x short side | also half the distance from the held point |
| Glass under the copy | capture stand-in | live glass median |

Rollback: reinstall the 1.1.6 source (`work\2026-11-11-wobbly\local@seamless-wobbly-windows.wh.cpp.bak-20261113-2056`)
with `scripts\Install-StagedMod.ps1`; the install also leaves a dated ModsSource backup.
Part backups: `ps.h.bak-20261113-2056`; the 1.1.6 spliced source above holds every part.

### 1.1.7 live (9:18 pm): glass read too slow
- Installed at idle, registry 1.1.7, Explorer pid unchanged (13612).
- Take `live-1.1.7-211952`: the copy only came up once the drag had stopped (video 6.7 to
  7.4 s); during the move the real window showed. The copy was about 20 levels brighter
  than the real window (58,60,89 against 37,39,59). The gradient spread across the copy
  matched the real window (red rises about 9 to 10 levels from top-left to bottom-right in both).
- Cause: each screen read waits for a display frame. Measured here: 25 small reads take
  180 to 250 ms, one read of the whole 960x620 window 8 to 15 ms. While the 25 reads ran,
  the window moved away from the squares being read, so the "glass" was other windows.
- Also on screen: a Flow Launcher error ("Failed to register hotkey Ctrl + Alt + F10") sat
  over the test window the whole take. Not ours; left for the owner.

## 1.1.8: one screen read, taken before the move (2026-11-13, 9:28 pm)
- The glass is read in one picture of the whole window, 40 ms after the press (the window
  has shown active by then) or as the move begins, whichever is first, while the drag is
  still waiting to start. It is dropped if the window moved during the read.
- Squares now come from that picture on a 7 x 7 grid; the picture is freed once the glow starts.

| Item | Old | New |
|---|---|---|
| Seamless Wobbly Windows | 1.1.7 | 1.1.8 |
| Glass read | 25 screen reads at the grab | 1 read before the move |

Rollback: reinstall the 1.1.7 source (`work\2026-11-11-wobbly\local@seamless-wobbly-windows.wh.cpp.bak-20261113-2128`)
with `scripts\Install-StagedMod.ps1`, or the 1.1.6 one (`...bak-20261113-2056`).

### 1.1.8 live: copy still about 20 levels brighter
- The overlay is now up for the whole drag (the read lands before the move).
- The glass read came out near black once the glow was taken out with the copy's old blend
  (about 4, 5, 15 of 255), so the safety check (within 0.1 of the stand-in) threw it away and
  the copy fell back to the brighter stand-in.
- Cause: the real window adds the glow's light over the glass. The copy darkened the glass
  under the glow and then added it, which is wrong for the strong 1.1.x gradient.

## 1.1.9: the copy adds the glow like the real window (2026-11-14, 1:42 am)
- Shader: when the glass was read, glow is added over it (capped at full), not blended over it.
- Glass read: screen minus glow. The "close to the stand-in" check is replaced by an evenness
  check: at least half the samples must sit within 8 levels of the median on every channel,
  else something else covers the window and the stand-in is kept.

| Item | Old | New |
|---|---|---|
| Seamless Wobbly Windows | 1.1.8 | 1.1.9 |
| Copy's glow blend | over the glass | added to the glass |
| Glass read check | within 0.1 of stand-in | half the samples even |

Rollback: reinstall the 1.1.8 source (`work\2026-11-11-wobbly\local@seamless-wobbly-windows.wh.cpp.bak-20261114-0142`)
with `scripts\Install-StagedMod.ps1`. Part backup: `ps.h.bak-20261114-0000`.

## 2026-11-14 11:12 am: glow turned off (owner)

Owner said the merged Acrylic Color Glows caused the Helium regression and asked for the old look.
`glow.enabled` 1 -> 0 in the mod's settings, SettingsChangeTime bumped, applied live by
`scripts\2026-11-14-wobbly-glow-off.ps1`. The glow tool process keeps running with nothing to paint.
Backup: `backups\2026-11-14\seamless-wobbly-windows\mod-key-before-glow-off-*.reg`.
Rollback: set `glow.enabled` back to 1 and bump SettingsChangeTime, or import the .reg.

## 1.2.0: the original Window Wobble springs, back exactly (2026-11-14, afternoon)
Owner: "fix the wobbly windows, it's not like the original mod at all". Our 1.1.x springs had
drifted from HeyJeay's: a pin under the pointer, springs graded by distance from it, a cone cap,
a tight clamp, kicks scaled by frame time, no release flick, a softer 0.25 s landing and a fixed
480 Hz step. All of that is gone. The sheet is now the original's, line for line:
- Stiffness graded by row only (title bar stiff, bottom soft by the softness setting).
- Kick: full velocity on a direction change, 0.4 of it above 80 px/s, every moved frame.
- Release: one flick at half the travel speed, then SettleFast, done within 0.30 s.
- One spring step per frame with the frame's own time, as the original. Only a frame longer than
  1/120 s (a hitch or a 60 Hz screen) is split into equal steps so it cannot blow up.
- Kept from ours: Windows does the move (we follow its frame), the border ring, Alt-drag, the
  landing follow while Windows snaps, and a far-out guard (the window's own size) against runaway.
- Glow is still off by the owner's 11:12 am choice; the install keeps the mod's settings.

| Item | Old | New |
|---|---|---|
| Seamless Wobbly Windows | 1.1.9 | 1.2.0 |
| Spring sheet | pinned at pointer, distance graded, capped | original row graded, no pin |
| Step | fixed 1/480 s | per frame, as the original |
| Release | settle only | half-speed flick, then settle |
| Softness setting name | Far side softness (%) | Body softness (%) |

Rollback: reinstall the 1.1.9 source (`work\2026-11-11-wobbly\local@seamless-wobbly-windows.wh.cpp.bak-20261114-1130`)
with `scripts\Install-StagedMod.ps1`. Template backup: `mod.template.cpp.bak-20261114-1130`.

## 1.2.0 also re-sets the glass after a drag (2026-11-14, 12:48 pm, thread e1fe78e6)
Owner: "fix the wobble mod too", after T3's whole window went see-through at about 11:55 am.
The wobble hides (cloaks) the real window on every drag and showed it again without telling DWM
to rebuild its glass. An acrylic backdrop or accent blur could come back stale, so the window
showed what was behind it unblurred. Seamless Window Manager already fixes the same thing.
- Added `RefreshBackdropAfterUncloak` (a copy of the window manager's): after the uncloak, set
  the same system backdrop (if acrylic or mica) and the same accent (if one is on) again.
- Called at the end of `ShowWindowInPlace`, so every landing path gets it.
- Added into the staged 1.2.0 source, so the already queued 1.2.0 install carries it. Version
  left at 1.2.0 because the queue checks for that exact number.
- Offline build: x64 and x86 both OK (`work\2026-11-11-wobbly\build-glass`).

| Item | Old | New |
|---|---|---|
| Glass after a drag | left as DWM had it | backdrop and accent set again |

Rollback: the staged source without this is `work\2026-11-11-wobbly\local@seamless-wobbly-windows.wh.cpp.bak-20261114-1130`
plus the 1.2.0 spring work; simplest is to delete `RefreshBackdropAfterUncloak` and its one call.
Copy with the fix: `local@seamless-wobbly-windows.wh.cpp.glass-20261114-1248`.

### 1.2.0 also: glass put back after the drag (thread e1fe78e6's finding)
- After the reveal, the mod tells the window its real active state again (WM_NCACTIVATE plus a
  frame-changed SetWindowPos, async), the same as Seamless Window Manager's
  RefreshBackdropAfterUncloak. T3's glass went see-through at about 11:55 am after a drag.
- First queued try (to 1:20 pm) never ran: another thread held the desktop lock. The queue now
  lets go of the engine lock and retries every couple of minutes while the owner is away.
- 3:05 pm: still not installed. The owner never left the PC long enough (queue 1 ran out at
  1:20 pm, queue 2 runs out about 3:11 pm). A hidden follow-up (`scripts\2026-11-14-wobbly-requeue-long.ps1`,
  log `work\2026-11-11-wobbly\queued-1.2.0-c.log`) queues it again for 10 hours behind queue 2, so it
  can go in tonight. It stops on its own if 1.2.0 is already in or the live source changed.
  Shell check at 3:01 pm: healthy. To cancel: stop the hidden powershell running that script.
- 3:33 pm: owner said "go", so 1.2.0 was installed at once (no idle wait, no test drag) by
  thread e1fe78e6 with `2026-11-13-wobbly-install.ps1` under the windhawk-engine lock. The staged
  source by then held the wobble thread's own version of the glass fix (`RefreshBackdropAfterShow`:
  WM_NCACTIVATE with the real active state, then SWP_FRAMECHANGED), which replaced mine; installed as is.
  Compile check OK, shell healthy before and after, no app crashes, Explorer not restarted.
  Loaded in 8 Explorer and 10 of 14 T3 processes; glow still off. T3 capture after: glass solid.
  Registry 1.1.9 -> 1.2.0, DLL `local@seamless-wobbly-windows_1.2.0_252089.dll`.
  Backup: `backups\settings-material\local@seamless-wobbly-windows-20261114-1534.wh.cpp` and
  `ModsSource\local@seamless-wobbly-windows.wh.cpp.bak-20261114-1534`.
  Rollback: reinstall that backup with `scripts\Install-StagedMod.ps1`.
  The wobble thread's queue (started 1:21 pm) still runs its test drag the next time the owner is away.

## 1.2.1 (2026-11-14, 5 pm): steps exactly like the original, glass kept with the glow off

Owner: "Make sure it's just like the original wobbly windows ... optimised, and compatible with all
the remods." Compared line by line with HeyJeay's `window-wobble.wh.cpp` (mesh 517-704, drag 1540-1795).

- **Stepping.** 1.2.0 ran a fixed 1/120 s step. The landing springs (settleK 12000, settleD 210 plus
  8 x meshK) are only stable below about 7.8 ms, so the drop could shake; a max-offset clamp hid it.
  `Mesh::Advance` now does what the original does: a quarter of the stability limit per sub-step,
  at most 64 sub-steps, frame time capped at 50 ms.
- **Integrator.** Same as the original: displacement read before the move, rest at under 2.5 px and
  20 px/s, and a runaway guard (non-finite, over 1e5 px or 1e7 px/s ends it). The `acc` and
  `maxOff` fields went with the clamp.
- **Glass with the glow off.** The capture of the live glass was tied to the glow, so with the glow
  off (owner, 11:12 am) a glass window showed the flat stand-in colour while dragged. `GlassOnly`
  now fills in the screen-read glass under the key colour with glow strength 0.
- Kept from ours: Windows does the move, Seamless Borders ring, Alt-drag and the window manager's
  drags, the landing follow, the smooth grid, partial presents, idling when nothing moves.
- Corner radius still read live from custom-corner-radius (16, 0 when maximized).
- Offline build: x64 354816 bytes, x86 356352 bytes, no warnings.
- Test made strict: it waits up to 40 s for the test window to be in front (an elevated Windhawk
  task dialog ate the 4:43 pm 1.2.0 take, which never moved) and returns 3 when the window did not
  move. Backup `scripts\2026-11-13-wobbly-glow-test.py.bak-20261114-1735`.
- Install queued at 4:57 pm (idle 5 min, engine lock), log `work\2026-11-11-wobbly\queued-1.2.1.log`.

| Item | Old (1.2.0) | New (1.2.1) |
|---|---|---|
| Sub-step | fixed 1/120 s | quarter of stability limit, max 64 |
| Overshoot | clamped to max offset | free, as the original |
| Glass while dragged, glow off | flat stand-in colour | screen-read glass |

Rollback: reinstall the live 1.2.0 copy `work\2026-11-11-wobbly\live-1.2.0.wh.cpp.bak-20261114-1740`
with `scripts\Install-StagedMod.ps1`; template `mod.template.cpp.bak-20261114-1652`.

### 1.2.1 live result (installed 6:33 pm, owner away)
- Registry 1.2.0 -> 1.2.1. Explorer not restarted (same process since 4:40 pm), no app crashes.
- Filmed take `work\2026-11-11-wobbly\live-1.2.1-183336` is valid: test window in front, rect moved.
  Clip `wobble-1.2.1.mp4`, GIF `wobble-1.2.1.gif` in that folder.
- Drag: title bar keeps up, body leans and trails; each drop settles square in a moment, no shake.
- Glass while dragged: mean colour 29,29,43 vs 29,30,45 at rest (within about one shade).
- Top corners at 4x: round, ring on the edge, no fold.
- Explorer's 0xc0000005 "Exception Processing Message" boxes (5:01 pm, 6:01-6:12 pm) are the
  old Bug B from `notes\2026-11-11-explorer-tree-crash.md`, already firing before this install.
  One was still on screen during the take; left alone.
- Shell check after: healthy.
