# translucent-flyouts 0.6.50 (2026-10-19)

Shipped 0.6.50: the 0.6.49 title-bar-menu text regression is fixed, and the desktop
context menu now gets the accent ring and rounded region. Installed and verified on the
test window; the desktop-menu ring is verified in mechanism and awaits one shell restart
to show on the real desktop menu.

## Fix 1: title-bar menu text erased (0.6.48/0.6.49 regression)

Root cause (proven by the 0.6.50-diag4 probe): `HandlePopupMenuNonClientBorderColors`
did `SelectClipRgn(nullptr)` + `PatBlt(full rect, BLACKNESS)` after all item text was
drawn. `nzBefore=9, nzAfter=0` â€” the rim clear wiped the whole surface to alpha 0 and
erased every glyph.

Fix: the rim clear is now geometrically limited to the rim â€” the window round-rect
minus the inner round-rect, inset by the band rect recorded from the first
POPUPBACKGROUND draw (fallback inset 3). Implemented in
`Windhawk\translucency-flyouts\src\30-engine.inc`. The ring drawing (FillRgn ring-diff)
is unchanged.

Verification, final release build `0.6.50` on the FlyoutTestWindow system menu:

- `reports\2026-10-18-flyout-border\test-window-sysmenu-0650-final-030838.png` â€”
  all five items with text, separator, submenu arrow, and the accent ring.
- Glyph pixel counts per item row: 178/578/212/215/203 â€” identical to the good 0.6.47
  captures (the regression had them at 0).
- Probe in the diag build: `nzBefore=165 nzAfter=165` with the rim built
  (`rim=1 band=3,3,261,122`) â€” the text row is untouched by the rim clear.

## Fix 2: desktop context menu accent ring

The desktop menu is painted by DirectUI with zero uxtheme calls, so the draw hooks never
fire (proved in the 2026-10-18 diagnostic). Measured facts that chose the design:

- The menu window is class `#32768` (atom 0x8000), **not layered** (exstyle 0x189, no
  WS_EX_LAYERED, no SetLayeredWindowAttributes) â€” it paints into its DWM redirection
  surface. `UpdateLayeredWindow`, `UpdateLayeredWindowIndirect` and
  `win32u!NtUserUpdateLayeredWindow` hooks all stayed silent for menus
  (`reports\2026-10-18-flyout-border\build-0.6.50-diag6/7`).
- Drawing straight onto `GetWindowDC(#32768)` persists â€” proven by the red-frame probe
  `reports\2026-10-18-flyout-border\probe-direct-draw-sysmenu-020904.png`.

So 0.6.50 adds a small watcher thread (per process): every 250 ms it finds visible
`#32768` menus of the current process that the theme hooks never styled (no window
state), and for each it applies the same rounded region. Menus styled by the theme path
are skipped, so nothing is double-ringed. Menus with the border set to default/none get
no ring. The first build had atom 0xFFFF in the class check â€” wrong, `#32768` is atom
32768 (0x8000); fixed in diag9.

### The three real bugs (found 2026-10-19 midday, diag10-diag16)

The first six diag rounds on the live shell showed the watcher silently doing nothing.
The tf log of the shell proved each step:

1. **Thread id compared to process id.** `CollectPopupShellMenu` used
   `GetWindowThreadProcessId(hWnd, nullptr) == GetCurrentProcessId()` â€” the function
   *returns the thread id*; the process id arrives through the out parameter. The
   comparison could never match, so `EnumWindows` "found" nothing
   (diag13: `[um] tick found=1` appears the moment this is fixed).
2. **A message pump that never dispatches.** The watcher thread ran
   `while (GetMessageW(...)) {}` with no `DispatchMessage`, so the `SetTimer` callback
   (`UnthemedMenuTimerProc`) never fired even once â€” diag10-diag12 logs show watcher
   start lines and zero ticks until the pump dispatches (diag12: `[um] tick found=0`
   lines appear).
3. **The ring was never drawn at all: an inverted `CombineRgn` check.** After the first
   two fixes (diag13), the log showed the watcher *attempting* five rings with
   `color=FF84B1F9` â€” and the capture still had no ring. The suspected causes (blit
   erasure, ignored `DWMWA_BORDER_COLOR` under the accent policy) were real
   constraints but not the killer: `RingUnthemedMenu` and `StrokeUnthemedMenuRing`
   both gated on `CombineRgn(...) != ERROR` and returned â€” but `CombineRgn` returns
   `ERROR` (0) **only on failure**; success returns `COMPLEXREGION` (3). The check
   bailed on success, every time, in both painters. The proven-correct pattern was
   already in `HandlePopupMenuNonClientBorderColors` (`proceed when != ERROR`).
   Fixed in diag19 (both sites bail on `== ERROR`); the same run's log shows 27
   completed buffer strokes, 8 watcher rings with pixel probes, and the capture
   `desktop-menu-0.6.50-diag19-143045.png` shows the accent ring.

Paint-path facts learned en route (diag16-18): the desktop menu's paint path is not
stable across shell sessions â€” one shell drew its items through a full-menu buffer
(`dcObj=10`), the next drew them straight on the window DC (`dcObj=3`) â€” so the fix
covers both: the draw-hook stroke (sized from the live `GetWindowRect`, since the
window state can hold a stale creation-time size like 100x100) and the watcher's
window-DC ring for menus with no state. `state.hWnd` was added to `WindowState`
because the hook only has the DC, not the window.

Also fixed en route: `EnsureWindowState` no longer tells DWM `DWMWA_COLOR_NONE` for a
rounded menu until its themed background actually drew (`bandRectValid`), so it cannot
fight the unthemed ring.

Mechanism evidence: `desktop-menu-0.6.50-diag8-021340.png` shows the desktop menu
owned by an explorer without the mod (native border only). Final proof on the release
build: `desktop-menu-0.6.51-final-143945.png` (accent ring on the desktop menu) and
`test-window-sysmenu-0650-final-143955.png` (title-bar menu: all five items with text
plus the ring â€” no regression).

## 0.6.52 â€” the double-border fix (2026-10-19, ~5:25 PM)

The owner saw two accent lines around the desktop menu. Pixel scanlines of the capture
showed accent at window x=0 *and* x=3: **both painters were ringing, 3 px apart.**
The popup-menu window has a 3 px non-client frame â€” the paint buffer's origin (the
client area) sits 3 px inside the window DC's origin, and the window DC covers the
whole window. Any fixed inset therefore lands differently per painter; diag20 proved
it by moving both rings 3 px apart again.

Fix: one painter per menu. The draw-hook stroke now:
- paints only into buffers (`GetDCOrgEx` != 0,0 means a window DC â€” the watcher owns
  those), and sets `state.unthemedStrokeSeen`;
- sizes its ring from `GetClientRect` (315x584 on this menu), because window-rect
  dimensions pushed the right/bottom ring columns outside the buffer where the blit
  clipped them (diag21: left/top ringed, right/bottom bare).

The watcher stands down once `unthemedStrokeSeen` is set, so exactly one ring is ever
painted. The ring geometry is back to 1 px inside the buffer edge, which lands at
window x=3 â€” the same inset the themed `[nc]` pass produces, with the menu's own dark
border outside it. Measured on the 0.6.52 release build
(`desktop-menu-0.6.52-final-172512.png`): accent at x=3 left, x=316 right, y=3 top,
y=585 bottom â€” one line per side, no doubles; sysmenu unchanged
(`test-window-sysmenu-0650-final-172522.png`).

## 0.6.53 â€” the smooth-ring fix (2026-10-19, ~9:10 PM)

The 0.6.52 "double border" was actually two painters with different coordinate spaces;
after the single-painter fix the user still saw stray lines. diag25 nailed the real
structure of the desktop menu (`#32768`):

- The menu paints items as per-item rects (`2,2,313,26` â€¦ `2,558,313,582` â€” client
  coords, 2 px margins each side) into **one full-client buffer** (clip box
  0,0,315,584). Any ring drawn into the buffer outside an item's rect â€” including the
  corner arcs â€” is erased by the next item paint. Buffer drawing can never win.
- The ring therefore lives on the **window DC in window coordinates**: the watcher
  (`RingUnthemedMenu`, 250 ms) is the only painter, at inset 3 with radius
  `kMenuRegionRadius-3` = 21. That geometry sits in the 3 px margin the item blits
  never copy over, so it stays put; corner arcs inside item rects are restored by the
  next watcher tick. The draw-hook stroke (`StrokeUnthemedMenuRing`) and the
  `unthemedStrokeSeen` flag were removed entirely.
- Begin/EndBufferedPaint hooks were added (`g_bufferedPaintMenus` map) as a re-stroke
  path for buffered paints â€” on this menu they never fire (the menu uses plain
  compatible DCs), but they are correct for menus that do.
- The native frame line (505172 at window 0..2) is gone: the watcher's rim clear now
  runs again (its skip was reverted to `bandRectValid` only) and darkens it.
  **Superseded by 0.6.54 â€” the rim clear turned out to be a bug; see below.**

## 0.6.54 â€” the corner-darkness fix (2026-10-20, ~1:10 AM)

The owner spotted darkness "seeping out of the blue corner" in the 0.6.53 wide shot.
Cause: the watcher's rim clear â€” a `PatBlt(BLACKNESS)` over the window rect minus the
inset-3 arc. On the flat edges it only hid the native frame line, but at each corner it
filled the whole wedge between the window rectangle's corner and the accent arc with
black.

Fix: no rim paint of any kind. The watcher's region is now
`CreateRoundRectRgn(3, 3, w-3, h-3, 44, 44)` â€” the visible shape starts at the ring's
outer edge, so the frame line's 0..2 px band is excluded at the source (never renders)
and the DWM recomputes the shadow around the tighter shape. The region's arc is one
pixel wider than the ring's (radius 22 vs 21, same centre) so its polygonal
approximation can never clip the ring's corners. The accent ring (inset 3, radius 21)
is the only thing the watcher draws.

Verified 0.6.54: corner crops with the desktop outside show no black crescent (TL and
BR checked); bands accent 84B1F9 at window x=3/316, y=3/585; sysmenu regression clean
(`test-window-sysmenu-0650-final-011057.png`, 1:10 AM). Wide captures
(`desktop-menu-context-0.6.54-011047.png`, `desktop-menu-full-screen-0.6.54-011047.png`)
prove the menu in desktop context.

**Superseded by 0.6.55** â€” the owner's 8:04 AM photo showed the inset-3 region cutting
the ring's corner arcs into dashes on all four corners. A window region can never
reliably bound a ring.

## 0.6.55 â€” the overlay-ring redesign (2026-10-20, morning; PAUSED mid-release)

Diagnosis of the dashes: 0.6.54's inset-3 window region clips the watcher's re-stroke â€”
GDI's polygonal approximation of the region arc cuts chunks out of the ring's corner
arcs. Redesign (diag28/28b/28c): **the ring now lives on its own layered window**
floating exactly over the menu (`TF_RingOverlay`, WS_EX_LAYERED|TRANSPARENT|TOPMOST,
per-pixel alpha). The menu's per-item blits cannot erase it, no menu region applies to
it, and the band is a GDI+ even-odd fill of two nested round-rect subpaths â€”
anti-aliased corners, crisp flats. gdiplus loads via GetProcAddress (Windhawk's link
set has no gdiplus.lib); the mingw headers put the flat API in
`Gdiplus::`/`Gdiplus::DllExports` and the Gp* stubs inside `Gdiplus`.

Verified on diag28b captures: the corner arc stays complete after hovering across
items (`hover-tl.png`/`hover-br.png`) â€” the erasure failure mode is gone. Pixel probe
found the GDI+ quirk: pixel i is centred on integer i, so a band spanning [3,4]
renders half-alpha across pixels 3 and 4. diag28c shifts the band to [2.5,3.5], which
lands a full-intensity 1px line exactly on pixel 3 â€” built as release **0.6.55**.

**PAUSED by the owner** at ~10:20 AM (their Unified Remote phone-mouse was being
restored; my test menus and shell restarts were stealing focus/cursor) â€” **RESUMED and
released at ~12:57 PM the same day.** final5-run.ps1 ran clean: leftovers dismissed,
0.6.55 installed, the ONE shell restart (pid 15172 â†’ 11540), wide + hover captures,
sysmenu regression, band/arc probes.

Verified 0.6.55 (capture `desktop-menu-context-0.6.53-125820.png`, 12:58 PM):

- Flats: accent **84B1F9 at exactly one pixel inside the edge on all four sides**
  (left x=3, right x=318, top y=3 â€” full intensity, the half-pixel fix confirmed).
- Corners: the 45Â° point of the TL arc reads the AA'd band at (329..330, 329..330)
  with the desktop outside at (323,323) â€” a real smooth arc, no dashes, no darkness.
- Hover survival: `hover-tl.png`/`hover-br.png` â€” the ring is untouched after hovering
  across five items (the per-item blits that erased every earlier attempt).
- Sysmenu regression clean (`test-window-sysmenu-0650-final-125837.png`, 12:58 PM,
  test pid 28892 on 0.6.55).

Cleanup 1:08 PM removed 10 diag DLLs (diag14's lock finally freed too) and the
tf-*.log debug artifacts from
`C:\ProgramData\Windhawk\Engine\ModsWritable\mod-storage\local@translucent-flyouts\`;
two log handles held live by running processes die with them. One file kept, locked:
`Mods\64\local@translucent-flyouts_0.6.50-diag28b_1.dll` (Ableton) â€” delete after a
reboot.

## Install state

- Registry: `Version=0.6.55`, `LibraryFileName=local@translucent-flyouts_0.6.55_1.dll`,
  `Disabled=0`. DLLs in `C:\ProgramData\Windhawk\Engine\Mods\{64,32}`; sha256 in
  `reports\2026-10-18-flyout-border\build-0.6.55-final.log`.
- Shell pid 11540 (started 12:57 PM), 0.6.55 mapped.
- Backup: `backups\2026-10-18\translucent-flyoutso-0.6.50\mod-key-before-0.6.50-install.reg`
  (sic, the folder is `translucent-flyouts-0.6.50`).
- Cleanup 1:08 PM removed 10 diag DLLs; only `Mods\64\â€¦diag28b_1.dll` remains, locked
  by Ableton until a reboot. Debug logging is OFF in 0.6.55 (release build); the two
  tf-*.log handles still held by running processes disappear when those exit.
- The Windhawk service is Running.

## Pending

- None for the border. The locked diag28b DLL frees up after a reboot; delete then.

## 0.6.56 + 0.6.57 + 0.6.58 -- the field-failure fix (2026-10-20, ~4:00 PM to 7:22 PM)

Owner complaint on 0.6.55: duplicate borders and a dark area outside the border.
Z-order ground truth (diag0656-z.ps1) explained everything the probes saw:
the ring overlay ended up BELOW its menu -- the z-walk above a live desktop menu
showed only invisible windows, so the ring painted under the menu's opaque body
and survived only through region holes (the faint 5C77A8 arc pixel at menu-local
(9,9) in the 0.6.56/0.6.57 captures). In 0.6.55 what actually read as the ring was
the DC re-stroke drawn on the menu's own DC, which the overlay's silence had been
masking all along.

- 0.6.56 (6:04 PM build, 6:10 PM install): removed the buffered-paint re-stroke
  and its hooks entirely (one painter), restored the watcher region inset 3
  `(3,3,w-3,h-3) r44-clamped`, clamped RenderRingDib corner radius. Disabled it:
  ring invisible (below the menu). Shell restarts: 11852 -> 14792 (6:19 PM).
- 0.6.57 (6:53 PM build, 6:54 PM install): per-tick insert-above the menu
  (`SetWindowPos(overlay, menu, ...)`). Did not hold: the menu re-raises itself
  on hover/repaint between 250ms ticks. Shell restarts: 12904 -> 15960 (6:59 PM),
  -> 24268, then 24268 -> 10420 (7:20 PM for 0.6.58).
- 0.6.58 (7:09 PM build, 7:10 PM install): overlay created with the menu as its
  window owner (`CreateWindowExW(..., menu, ...)`). Windows guarantees an owned
  window stays above its owner regardless of the menu's own re-raises, and the
  overlay auto-dies with the menu. The 7:11 PM z-walk then showed the overlay
  directly above the menu, and the 7:13 PM capture confirmed the ring:
  left flat menu-x 3 = 84B1F9 full accent, top flat y=3, right flat x=318,
  corner arc AA at (9,9), nothing outside the border; pixels 0..2 now show what
  is behind the menu (region inset 3 holds, confirmed by GetWindowRgnBox
  bbox (3,3) 314x583 on the live menu) instead of the native dark frame.
  Hover survival: ring intact after item repaints (hover-context-0.6.50-diag28-191554.png).
  Sysmenu regression clean (test-window-sysmenu-0650-final-192142.png, 7:21 PM,
  test pid 16844, 264x125).
- custom-corner-radius (dwm.exe, radius 0x10) rounds the menu corners at the DWM
  level (visible corner cut at ~12.5px diagonal = radius ~32 at this monitor's
  scale) on top of the TF region; the ring does not depend on the region anymore,
  so the two no longer fight over the look.

## Install state (0.6.58)

- Registry: `Version=0.6.58`, `LibraryFileName=local@translucent-flyouts_0.6.58_1.dll`,
  SettingsChangeTime=1792494631. DLLs hash-verified in Engine\Mods\{64,32};
  sha256 in `reports\2026-10-20-flyout-border\build-0.6.58.log`.
- Shell pid 10420 (started 7:20 PM), 0.6.58 mapped. Publish copy synced at
  `work\window-pack-publish\mods\local\translucent-flyouts\translucent-flyouts.wh.cpp`.
- Backups: `backups\2026-10-20\translucent-flyouts-0.6.5{6,7,8}\`.
- Release evidence in `reports\2026-10-20-flyout-border\` (captures 191358/191554/192142).

## Pending (0.6.58)

- None for the border. The locked diag28b DLL frees up after a reboot; delete then.

## 2026-10-20 evening / 2026-10-21: ring geometry re-meter (0.6.59), sysmenu double border (0.6.60-0.6.62)

### 0.6.59 â€” overlay dib ring flattened to inset 0.5/rr16 (installed 2026-10-20 9:22 PM)

- 0.6.58's overlay band ([2.5,3.5), rr24) left a navy crescent at the corners: DWM
  composites the menu's own base layer as a full-rect round rect at r16 and ignores the
  window region, so the band's arc sat inside the base's corner fill. 0.6.59 pins the
  overlay band to [0.5,1.5) with rr16, concentric with that base.
- Live verification (10:31 PM capture 0.6.59-flat-mid-223138.png, 321x590 menu at 200%):
  full 84B1F9 at pixel 1 on all four flats; px0 = partial AA over shadow; TL diagonal
  void to (4,4), ring AA at (5,5)/(6,6), navy after; BR diag (âˆ’4) ~50% at (âˆ’5) AA,
  navy from (âˆ’6). Corner spill gone.
- Rig cross-check (reports\2026-10-20-flyout-border\cpp\): GDI+ replica at both menu
  sizes matches the live captures byte-for-byte, mid-edge probes (y=295 / x=160).
  An early "right/bottom inconsistency" reading was a stale checkpoint probing corner-
  zone rows at mid-edge columns.

### The sysmenu double border â€” root cause and fix (0.6.60-0.6.62, installed 2026-10-21 3:30 PM)

- Symptom: the test-window sysmenu (FlyoutTestWindow, WinForms ContextMenu, 264x125)
  showed two accent lines on the right/bottom (x=261 AND 263) while left/top had one.
- Facts established: the overlay dib is innocent (rig at exact sysmenu size renders a
  single inset-1 ring); the app draws no border of its own; the doubler colors are the
  mod's own constants, so the mod's DC pass painted them.
- GDI ground truth (render-test.cpp GdiStage, memory DC over DIB, per-stage probes):
  GDI round-rect regions cover to right-2/bottom-2, not the textbook right-1. The
  themed DC ring therefore lands at {1, w-3} x {1, h-3} â€” asymmetric: left/top inset 1,
  right/bottom inset 3.
- Why both painters ran: the sysmenu draws MENU_POPUPBORDERS (border pass fires, DC
  ring painted) but its POPUPBACKGROUND clip fails the bandRectValid record test, so
  the watcher tick treats it as unthemed and keeps/creates the overlay each tick. Two
  rings on one menu: DC at {1,w-3}/{1,h-3}, overlay at {1,w-1}/{1,h-1} â€” overlap on
  left/top, double on right/bottom.
- 0.6.60: `WindowState.dcBorderPainted` set by `HandlePopupMenuNonClientBorderColors`;
  the watcher tick destroys the overlay when bandRectValid OR dcBorderPainted. Live
  check: single line everywhere (261 full, 263 down to shadow AA) â€”
  test-window-sysmenu-0660-151106.png.
- 0.6.61 (broken, replaced same hour): moved the DC ring to the symmetric inset
  {1, w-2}/{1, h-2} by widening the CreateRoundRectRgn params (GDI +2 exclusion) â€” but
  the rim-clear clip stayed selected through the ring FillRgn and the ring's right/
  bottom pixels sit OUTSIDE the new rim region, so that half was clipped away: right/
  bottom read 40/41 partials with no full accent. DLLs left in the engine dirs as a
  receipt; never shipped.
- 0.6.62 (installed 3:30 PM): adds SelectClipRgn(hdc, nullptr) after the rim PatBlt so
  the ring paints unclipped; also widens the rim inner (band.right+2) and the
  POPUPBACKGROUND fill clip (w-2 -> w-1) by the same GDI exclusion, so no un-cleared
  old-theme column sits between the fill and the relocated ring. Live check
  (test-window-sysmenu-0662-153133.png): left px1 full / px2 = 3F partial; right x262
  FULL, x263 cleared; bottom y123 FULL, y124 cleared; TL arc full at (5,6), BR arc
  mirrored at (258,119) â€” the DC ring is now symmetric inset 1 on all four sides, no
  spill, single line.

### Install state (0.6.62)

- Registry: Version=0.6.62, LibraryFileName=local@translucent-flyouts_0.6.62_1.dll,
  SettingsChangeTime=1792567860 (hash-verified copies, elevated log-152424.txt).
- Scripts: scripts\2026-10-21-translucent-flyouts-0.6.6{0,1,2}.ps1; backups
  backups\2026-10-21\translucent-flyouts-0.6.6{0,1,2}\; build logs
  reports\2026-10-20-flyout-border\build-0.6.6{0,1,2}.log.
- Lesson for every rebuild: the engine maps the DLL into running processes, so a
  same-version overwrite of the DLL in ProgramData fails. Each source change ships
  as a bumped version with a new filename.
- Explorer still runs 0.6.59 until its next restart (per-process pickup); fresh
  processes (the test app) load 0.6.62. The overlay path is untouched from 0.6.59,
  so the verified desktop-menu look carries over unchanged.

## Pending (0.6.62)

- Publish copy and repo/main-menu docs unchanged â€” re-sync on the next publish round.

