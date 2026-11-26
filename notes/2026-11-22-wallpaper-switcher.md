# Wallpaper switcher module for Seamless Taskbar (live, 2026-11-22)

Port of Simple Wallpaper Switcher 0.1.3 by HHeitlager (MIT) into Seamless Taskbar as
module `wallpaper` (index 11, settings `wallpaper.*`). Job folder: `work\2026-11-22-wallpaper-switcher\`.

## Live state: Seamless Taskbar 0.4.38
- Tray button (Seamless badge, hashed tray id). Left click opens the picker; right click opens the
  riced menu (previous, next, open picker, settings). Shortcut ctrl+alt+w. Host window
  `SeamlessTaskbarWallpaperHost`: WM_COMMAND 2001 picker, 2002 previous, 2003 next; tray callback 0x8001.
- Picker: 560x360, Mocha, FiraCode Nerd Font, 2px #585B70 tile edges, blue to mauve on hover and
  keyboard select, live corner radius 16, folder breadcrumb with drop-down, search, paging
  (3138 images in the owner's folder = 262 pages). Arrow keys move, Enter sets, Esc closes,
  scroll pages. Closes when it loses focus (WM_ACTIVATE WA_INACTIVE), so there is no unfocused state.
- Glass: colour-keyed layered picker over a backdrop window with acrylic (accent 4).

## Versions
- 0.4.36: module added (`patch_wallpaper.py`).
- 0.4.37: icons drawn through GDI+ (`patch_icons.py`), hint line shortened with an ellipsis.
  Published: mods 6d70666, feed d2f5508.
- 0.4.38: acrylic tint 0x99 (0.60) to 0x66 (0.40) (`patch_tint.py`). glass-check was WARN
  "barely frosted" (movement 0.52); now PASS, movement 4.75, over busy text (`proof2\glass-busy.png`).

- 0.4.42 (2026-11-23, `patch_ring.py`): corners went thin and dim (owner). The 2px edge was an
  unsmoothed GDI RoundRect on the same curve as the hard window region, so every curve lost half
  its width. The edge now lives on `SeamlessTaskbarWallpaperRing`: click-through, owned by the
  picker, UpdateLayeredWindow ULW_ALPHA, GDI+ AntiAlias, 2px at inset 1 on R-1, DWM rounding and
  border off. If the layer fails it logs "[Wallpaper] edge layer failed" and the old in-window
  edge comes back. Rule added as rice defect 70 on every agent, both machines. Proof `proof3\`.
  Published: mods f9288ce, feed d85257a. (0.4.41 was another thread's change.)

- 0.4.51 (2026-11-24, `patch_tiles.py`): dark specks poked out of every tile corner (owner:
  "what are those weird little dark bits poking out of the corners"). The picker is colour-keyed
  on #1E1E2E and the tiles' smoothed edge and picture clip mixed with the key on each curve, so
  those pixels stayed solid. Tile edges now draw on the ring layer (`SetTileEdgeState` feeds the
  tile loop in `PaintPickerRing`), pictures take a hard clip 1px inside the edge, unsmoothed GDI
  edge if the layer fails. Rule: rice defect 71 on every agent, both machines.
  Proof `proof6\` (`tile-proof2.py`, no input): the picker's own pixels read by PrintWindow show
  0 non-see-through pixels outside all 48 corners; on screen the six uncovered tiles count 0 dark
  specks against 150 before (`proof3`); `before-after-corners.png`. Glass top band passes.
  Published: mods db072f0, feed 52fc3a6. Log has no "edge layer failed".
  `proof4` and `proof5` are void: the picker opened by posted message sat under other windows,
  and a leftover csrss box ("explorer.exe - System Error / Unknown Hard Error", raised 11:02 pm
  on 11-23 by the shell that crashed then) covered it. That box was closed with an elevated
  posted OK at 12:37 am; the live shell was healthy throughout.
  Rollback: `C:\ProgramData\Windhawk\ModsSource\local@seamless-taskbar.wh.cpp.bak-20261124-0024`
  (0.4.50) through Install-StagedMod.

- 0.4.52 (2026-11-24, `patch_picker_size.py`): owner asked for a bigger, configurable switcher,
  an open and close motion with an on/off switch, and a better tray icon. New settings (group 11):
  columns 5 (2-8), rows 4 (1-6), tile size 176 (96-320), tile spacing 8, tile rounding 8, file
  names under tiles (off), hint line (on), close after picking (off), open and close motion (on),
  motion speed 180 ms. The window sizes itself to the grid and shrinks the tiles to fit the
  screen's work area. Motion: a snapshot of the picker on its own layer
  (`SeamlessTaskbarWallpaperMotion`) grows from 92% to 100% around the cursor (tray click) or the
  middle while it fades in; closing runs it back. "[Wallpaper] motion snapshot failed" in the log
  means it opened without motion. Tray icon: two peaks and a sun in the blue to mauve gradient,
  no box (`MakeMountainIcon`, badge fallback). Defaults stored in the registry by `seed-size.ps1`.
  Installed 4:20 am, desktop fine after 60 s, dock line-up ok. Published: mods 89dfb92, feed 4e74c59.
  The tray folder-menu thread's own 0.4.52 was built on 0.4.51; told it to rebase as 0.4.53.
  Rollback: Install-StagedMod backup `local@seamless-taskbar-20261124-0420` (0.4.51).
  Proof (`proof12\`, `proof17\`): picker 944x564, 20 tiles of 176x105 in a 5x4 grid; frosted
  glass passes glass-check; corners smooth at 4x, 0 specks in the keyed layer. Motion take
  (`motion-take.py`, no lifts, visibility logged every 1 ms) shows it runs on open and close,
  but only 3 to 4 distinct frames each (about 15 fps): choppy.

- 0.4.57 (2026-11-24, `patch_motion_smooth.py` on the tray thread's 0.4.53; numbers 0.4.55 and
  0.4.56 were set aside for the taskbar CPU thread and the tray folder thread, which rebase on
  this one; the folder thread ships its footer fix as 0.4.58): smooth motion. The install also
  syncs the main settings window to the template and ports the plate-free mark into the AI usage
  settings copy (`patch_aiset_mark.py`), because Install-StagedMod refused both as behind.
  The backdrop glass window is placed at full size once before the loop; each frame only
  changes its rounded region (no redraw, no DWM corner reset). Log lines: "[Wallpaper] motion
  open/close: N frames in M ms" and "motion snapshot M ms". Install with `install-motion.ps1`
  (takes the engine lock, patches whatever is live, Install-StagedMod).
  Rollback: the Install-StagedMod backup taken at that install (0.4.53).
  Actually installed 11:43 pm on 11-25 on top of 0.4.56, published. The tray thread's 0.4.58
  (1:47 am 11-26) and 0.4.59 (2:25 am) carry the motion code; checked by grep on the live source.
  Explorer healthy, no crash dumps, dock line-up ok at 2:27 am. Live motion video (proof18) waits
  for the owner to stop playing: the guard said "playing" at 2:26 am.
  Live proof `proof20\` (posted tray message, no input, guard clear): open runs about 10 to 16
  changed frames in 150 to 195 ms, close about 7 frames in 90 ms (before: 3 to 4 frames each,
  `proof17`). The motion layer shows about 154 ms on open, 130 ms on close (setting 180 ms).
  60 fps strips `open-strip.png` and `close-strip.png`: rounded glass first, grid fades in over
  it, no square flash. Open caveat: in the second open the glass came 1 s after the picker
  (slow snapshot or capture stall; the first open had no gap). `proof18` and `proof19` are void:
  they filmed the wrong screen. `motion-take.py` now maps the monitor origin to its capture index.

- 0.4.65 (2026-11-26, `v3\combined-0.4.65.wh.cpp` = live 0.4.64 + `crisp.py` (crisp tray
  icons, rider for thread 20dc1789) + `patch_picker_v2.py`): the owner's picker list. Edge is
  Mocha grey at rest and the blue to mauve gradient on hover; the picker resizes from any edge
  and remembers its size (more or fewer tiles); sort (name, newest, oldest, shuffled); badge on
  the current picture and open on its page; hover zoom; tile shape; auto-change; this screen or
  all screens; fit mode; random-wallpaper hotkey; edge width and three colours; glass strength;
  stay open; hide the search and folder bar. Probes: WM_APP+31 resize, WM_APP+32 hover.
  Quarantine: 0.4.64 was quarantined at 5:46 am (dwm 50 to 86 %). 0.4.65 passed the test PC at
  9:17 am (`D:\Agent Work\taskbar-0465-testpc\driver.log`: mod loaded, dwm 0 %, Explorer kept
  its pid over 60 s, 0 crash reports). quarantine.json: `testPcPassed` null -> {0.4.65, that log};
  backup `quarantine.json.bak-20261126-0918`; rollback = copy the backup back. The entry stays.
  Install: `install-v3.ps1` (engine lock, base-hash check, Install-StagedMod), then
  `seed-v2.ps1` elevated for the new defaults. Rollback: the Install-StagedMod backup (0.4.64).
  Installed 10:34 am (backup `local@seamless-taskbar-20261126-1027.wh.cpp`), watched 60 s: desktop
  fine, dock line-up ok, published (mods e7e419c, feed f1e0320). First try failed at 9:36: the
  compile takes over 2 min and Install-StagedMod's default 120 s timeout threw with an empty
  elevated log; `install-v3.ps1` now passes `-TimeoutSec 420`. Defaults stored with
  `seed-v2-quiet.ps1` (no settings reload while the owner played). Shell Explorer kept its pid.
  Live hover and resize proof is queued on `coop lock desktop` (owner playing at 10:35 am).

## Traps found while proving the motion
- A shell started inside a sandboxed desktop (the Antigravity run) finds none of the picker windows
  and CopyFromScreen fails with an invalid handle. Run the take from a shell on the real desktop.
- gfxcapture monitor probes of 0.3 s record 0 frames when nothing on that screen moves, so the
  probe finds no monitor. Pass RECORD_MON (main screen 0,0,2560,1440 = index 1; left = 3).
- A cross-process SetWindowPos (topmost lift) on the picker layers blocks while Explorer's
  thread is inside the motion loop, so a harness that lifts windows hides the motion it records.
- vcap marks use `rec.elapsed()`; the video's frame 0 is about 0.6 s later. Read real frame
  times from the video with ffmpeg showinfo, never from the marks.

## Trap found
Shell Font Changer Plus hooks DrawTextW inside Explorer and trims Nerd Font icons whose ink runs
past their advance (F002 at 9pt: advance 7, ABC 0/11/-4). The search icon showed as a "C" and the
folder icon was cut in half. Draw icon glyphs in Explorer-hosted mods through GDI+ DrawString
(`DrawIconGlyph`), which the hook does not touch.

## Proof (`work\...\proof2\`)
- Picker opened in 0.27 s; stills 1 to 5, zooms of the search, folder and hint; corners at 4x pass.
- picker.mp4 and picker.gif (2230 frames in 13.6 s). Explorer stayed up through every install.
- The owner's wallpapers were restored from `walls-before.json` after the proof.

## Rollback
Corner layer: Install-StagedMod backup `local@seamless-taskbar-20261123-0234` (0.4.41, before it).
`backups\local@seamless-taskbar.wh.cpp.bak-20261122-2133` (before 0.4.37) and the
Install-StagedMod backup `local@seamless-taskbar-20261122-2119` (before the module). Or switch
the module off: `wallpaper.moduleOn` = 0.
