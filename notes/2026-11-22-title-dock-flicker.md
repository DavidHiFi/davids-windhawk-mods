# Seamless Title Bars 1.3.13: title dock flicker

Owner report (2026-11-22): the title dock flickers when the pointer moves onto it and
the hover look comes in, and now and then it blinks for a split second with no hover.

## What was wrong

- A passive watcher (no input) caught the hover dropping while the pointer sat still
  on the Ableton dock: hot at 1332.1 s, off at 1333.3 s, same pointer spot, one uptime
  tick later. The hover only comes back on a pointer move, so it faded out and in.
- Cause in the code: every uptime tick re-lays out the title. `ClearWinLayout` runs
  first, so `StoreTitleInfo` read no layout and wrote `band = 0`. `HoverTick` then saw
  the pointer below a 0 px band and dropped the hover at once.
- The one-frame blink with no hover: when DWM redraws a title without asking its
  metrics again, the dock hook had no geometry and drew nothing for that frame.
  Not caught on screen; 1.3.13 counts these renders so it can be checked.

## Change (1.3.13)

- `StoreTitleInfo` keeps the last band while a re-layout has none.
- Hover stays on while the pointer has not moved since a hit test put it on the dock
  (and the window has not moved), with 2 px edge slack and a 3-tick grace before
  it drops.
- A render that skips the metrics call draws the dock from the last good render of
  the same layout.
- Counters appended to the shared block `Local\SeamlessTitleBarsHotDock` (after the
  suffix, offset 136): renders ok / missed / from cache, hover starts / drops and
  where the pointer was at the last drop. Reader:
  `D:\Agent Work\2026-11-22-titlebar-flicker\diag.py`.

## Old, new, rollback

- Old: 1.3.12, source hash d2599cf9...3c05acd. Copy:
  `backups\local@seamless-title-bars.wh.cpp.bak-20261122-1.3.12`.
- New: 1.3.13, staged from `work\2026-11-22-title-dock-flicker\`.
- Rollback: install the backup with `scripts\Install-StagedMod.ps1 -Id
  local@seamless-title-bars -Staged <copy in C:\Users\Public> -BaseHash <current hash>`
  under `coop lock windhawk-engine`, while the owner is away (dwm.exe mod).

## Proof

- Installed 3:07 pm: registry v1.3.13, library `local@seamless-title-bars_1.3.13_136827.dll`,
  desktop fine 60 s after load, published (mods 465b367, feed eaaf545).
- Counters at 3:42 pm, from the owner's own use: 7140 dock renders, 0 missed, 0 needed
  the cache. 5 hovers started, 4 ended; the last end had the pointer at x 657, y 53 against
  a dock of 405..641 and a 25 px band, so it ended because the pointer had really left.
  94 hit tests, all on the dock.
- Passive watcher, 15 min (`D:\Agent Work\2026-11-22-titlebar-flicker\watch2`): 7 screen
  changes near the pointer, all inside RustDesk or untitled windows, none on a title dock.
- Recorded hover test, 4:32 pm under `coop lock desktop --input` (posted mouse messages
  cannot drive it: the hover comes from DWM's own hit test on the real cursor). Folder
  `D:\Agent Work\2026-11-22-titlebar-flicker\hover3`: 5 in/out passes, a 1 px creep
  over the edge, 6 s resting on the dock, small moves. Hot flag 120 of 120 samples while
  resting. Hovers 6 started, 6 ended, each with the pointer outside. Renders 193 more, 0
  missed. Frame scan of all 5058 frames (about 190 a second): no one-frame blink on the
  dock; every change sits on a hover fade. Clip `hover-dock.mp4`, `hover-dock.gif`.

# 1.3.14: the blink with no hover (owner, 2026-11-24)

Owner still saw a split-second blink on the Windhawk window's dock with no hover.

## What was wrong

- Counters on 11-24, 7:07 am: 410166 renders, 0 missed, 0 from cache, so the
  "render with no geometry" idea is ruled out.
- A hover started on any hit test inside the dock box, even one DWM ran for a spot the
  pointer was not on (19 such hit tests), and on a pointer only passing over the title.
  `HoverTick` then gave it 3 ticks of grace with the target at full, so the glow rose to
  about a third and fell back: a flash of roughly 100 ms.
- Passive logger, 7:09 to 7:24 am, owner at the PC (`D:\Agent Work\2026-11-22-titlebar-flicker\starts1.json`):
  3 hover starts, all 3 ended within 50 ms with the pointer gone (two on Scrcpy GUI's dock,
  one as the pointer crossed into Explorer). Every one was a pass-over that 1.3.13 flashed.

## Change (1.3.14)

- A hover starts only from a hit test for where the pointer is now.
- The glow waits 3 ticks (about 50 ms) with the pointer on the dock before it fades in.
- The 3-tick grace only covers a hover that has already lit; one that never lit ends at once.
- Counters appended to the shared block: `startsRefused` (hit tests on the dock not at the
  pointer), `startsUnlit` (hovers that ended before lighting).

## Old, new, rollback

- Old: 1.3.13, source hash e32c67f5...14e1b5. Copy:
  `backups\local@seamless-title-bars.wh.cpp.bak-20261124-1.3.13`.
- New: 1.3.14, `work\2026-11-22-title-dock-flicker\local@seamless-title-bars.wh.cpp`.
- Install: `install-1314-when-idle.ps1` (waits for 90 s with no input, then the engine lock).
- Rollback: install the 1.3.13 copy the same way, with the 1.3.14 hash as BaseHash.

# 1.3.16: the 1.3.14 fix, rebased (2026-11-25)

- 1.3.14 never went in: the installer refused it three times on 11-24 because its settings
  window was behind the template, and meanwhile another thread shipped 1.3.15 (clean icons).
- 1.3.16 = live 1.3.15 plus the same 1.3.14 changes, made by `rebase-1316.py` (exact-match
  patches, each must hit once). Settings template check: in sync.
- Old: 1.3.15, source hash A86BAA14...93DA70 (live copy in ModsSource).
- New: `work\2026-11-22-title-dock-flicker\local@seamless-title-bars-1.3.16.wh.cpp`.
- Install: `install-1316-when-idle.ps1` (90 s idle, then the engine lock).
- Rollback: reinstall 1.3.15 from the Windhawk backup the installer takes, with the 1.3.16 hash
  as BaseHash, while the owner is away.

## 1.3.16 proof

- Installed 11:48 pm on 11-25 while the owner was idle: registry v1.3.16, library
  `local@seamless-title-bars_1.3.16_494407.dll`, desktop fine 60 s after load, published
  (mods 298b70e, feed 389c3d4). Backup of 1.3.15: `local@seamless-title-bars-20261125-2348.wh.cpp`.
- Counters on 11-26 from the owner's own use: 19777 dock renders, 0 missed. 6 hovers started;
  5 were pass-overs that ended before lighting (`startsUnlit`), each one a flash in 1.3.13.
  0 hit tests refused for being away from the pointer.

- 2026-11-26: another thread shipped 1.3.17 (Chromium pop-up frames). Checked the live source: the 1.3.16 dwell and grace fix is still in (dwellTicks, startsRefused present).

# 1.3.18: the Windhawk app's title blinks with no hover (owner, 2026-11-26)

Owner still saw the blink, now only on the Windhawk app's title ("Windhawk • 2m 32s").

## What was wrong

- 90 s recording of that window alone, no input (`D:\Agent Work\2026-11-22-titlebar-flicker\whrec1`,
  240 fps): 8 times the whole title, pill and icon, vanished for 20 to 83 ms. Each one sat on an
  uptime tick. Frame dumps `dump633.png`, `dump1296.png` show the empty title bar.
- Cause: every tick ran DWM's full title update (`OnTitleUpdated`) to swap in the new time. On the
  Windhawk app's window that rebuild sometimes draws a frame with no title at all. The hover fade,
  which only marks the title surface dirty, never blinked.

## Change (1.3.18)

- `TitleInfo` keeps the window's own title text (`base`) from the text hook.
- A tick whose time text keeps the same length now sets the text in place and marks the surface
  dirty, like the hover fade. Only a tick that changes the length (59s to 1m 00s) still runs the
  full update, so a centred title can move.
- Build check with Windhawk's own compiler: clean (`work\2026-11-26-title-tick\syntax.py`).

## Old, new, rollback

- Old: 1.3.17 (another thread's Chromium pop-up fix), source hash 76125B8E...CF664289.
- New: `work\2026-11-26-title-tick\seamless-title-bars.wh.cpp`.
- Install: `work\2026-11-26-title-tick\install-1318-when-idle.ps1`, started 12:23 pm as the one-shot
  task "Agent title bars 1.3.18 install" (90 s idle and coop guard clear, then the engine lock).
  Log: `install-1318.log`.
- Rollback: reinstall 1.3.17 from the backup the installer takes, with the 1.3.18 hash as BaseHash,
  while the owner is away.
