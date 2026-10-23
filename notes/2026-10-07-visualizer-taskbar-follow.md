# 2026-10-07: Taskbar Audio Visualizer 1.3.0 - the strip now follows the taskbar's auto-hide

## The complaint

The user asked for an audit of the visualizer mod's auto-hide behavior. Two
symptoms: hiding was delayed (up to ~1.2 s), and in the alt-tab/tab-out
scenario the strip stayed visible where the taskbar would be, even though the
taskbar was hidden. They wanted the strip to hide "seamlessly alongside the
taskbar", integrated as if native.

## Root cause

The strip is a separate topmost layered window parked over the taskbar rect
(`DesktopAudioVisOverlay_local@taskbar-audio-visualizer`). When the Windows
taskbar auto-hides, the strip stayed exactly where the bar had been. The only
hide paths were:

- `performance.hideWhenFullscreen` (the fullscreen watcher): only hides when
  the *foreground* window is fullscreen or covers ≥90 % of the taskbar rect.
  Alt-tab out of a game to the desktop, press Win, click another window:
  foreground is an ordinary window, nothing covers the strip's monitor logic,
  so the strip stayed up. This is the reported bug.
- The audio-idle fade (removed from the live settings in rev 3), and the
  1-second fullscreen-watch timer added ~1 s latency on top.

## What Windows 11 25H2 (build 26200.9457) actually reports

Measured on this machine (taskbar auto-hide ON via `StuckRects3\Settings`
byte 12 bit 0 = 1; taskbar at the top edge; taskbar-on-top mod installed):

| Signal | Revealed | Hidden | Verdict |
| --- | --- | --- | --- |
| `GetWindowRect(Shell_TrayWnd)` | 0,0,2560,50 | 0,0,2560,50 | never changes |
| `IsWindowVisible(Shell_TrayWnd)` | TRUE | TRUE | useless |
| `DWMWA_CLOAKED` | 0 | 0 | useless |
| `SHAppBarMessage(ABM_GETSTATE)` | 0 | 0 | lies on this build |
| `ABM_GETAUTOHIDEBAR` (all edges) | 0 | 0 | not an autohide appbar |
| `DesktopWindowContentBridge` child | not found | not found | no signal |
| UIA taskbar `BoundingRectangle`/`IsOffscreen` | 0,0,2560x50 / False | same | transform invisible to UIA |

The reveal/hide slide is a XAML/composition transform on the taskbar's
content. Nothing exposes the momentary state through any window API, so the
mod rebuilds the shell's reveal decision from the same inputs the shell
reacts to.

## The fix (revision 1.3.0_1)

New setting `performance.followTaskbarAutoHide` (default on), new code block
"Taskbar auto-hide follow" after `RepositionAndRepaintMediaControls`:

- `IsTaskbarAutoHideEnabled()` reads the auto-hide switch from
  `HKCU\...\Explorer\StuckRects3` (byte 12, bit 0) - the only place Windows 11
  actually keeps it; the appbar API remains as the fallback for older builds.
- `IsTaskbarCurrentlyRevealed()` rebuilds the shell's decision: the cursor
  inside the bar (revealed-hold zone) or, from the hidden state, within ~3 px
  of the bar's screen edge (the reveal sliver); or the foreground window is
  the taskbar, owned by it (`GA_ROOTOWNER`), or a shell host class
  (`XamlExplorerHostIslandWindow`, `MultitaskingViewFrame`), or an
  explorer-pid / Start-Search-ShellExperienceHost-pid `CoreWindow` (Start,
  search, flyouts).
- `UpdateTaskbarFollow()` runs every 100 ms (the existing 0xCA71 timer) and -
  crucially - on every `WM_APP+202` (the existing WinEvent hook posts that on
  `EVENT_SYSTEM_FOREGROUND` and taskbar location change), so alt-tab, Win-key
  and click transitions re-decide on the same event the shell itself reacts
  to. The auto-hide setting is re-read from the registry every ~3 s.
- On a hidden decision the strip slides off the bar's edge over 150 ms
  (smoothstep, matching the shell's own slide) by folding a progress-scaled
  offset into the composition visual offset in `UpdateSwapChainForLayout`,
  then switches to the existing blank-frame path (no drawing). The media
  strip and the capture-device picker hide with it (new `g_mediaHiddenByBar`
  flag; gates in `RepositionAndRepaintMediaControls` and `UpdateCapturePicker`).
- On reveal it slides back in over 150 ms and restores the companions.
- Snapping instead of animating at startup and on fullscreen-resume (decided
  while the overlay is still hidden), so a strip created into a hidden bar
  never flashes seated for a frame.
- The fullscreen watcher timer went 1000 ms → 250 ms, so the non-auto-hide
  fullscreen path also reacts 4× faster. `pauseWhenObscured` stays
  unavailable (hardcoded off since rev 3); no behavior change there.

Fullscreen pause (`hideWhenFullscreen`) and the follow feature compose: while
paused the follow tick returns early and re-decides on the resume tick.

## Verification

- Built clean for 64 and 32 with Windhawk's bundled clang++
  (`Build.ps1`, output `..._1.3.0_1_{64,32}.dll`, hashes in the receipt).
- Installed live via `install-visualizer-130.ps1` (disable → tool process
  exit → relabel → bump → re-enable). Audit: LibraryFileName =
  `local@taskbar-audio-visualizer_1.3.0_1.dll`, tool process running,
  source hash matches the repo.
- Diagnostic log (enabled for the test): the reloaded process logged
  `followAutoHide=1`, decided the follow state, and the strip went out while
  a fullscreen game (`CoDBlackOps`) was foreground with the taskbar
  auto-hidden - the exact reported scenario, now hidden.
- Screenshots + probe logs in `reports\2026-10-07-visualizer-taskbar-follow\`.

## Known limitations

- Flash-for-attention reveals (an app flashing its taskbar button, brief
  notification reveals) are not modeled: the shell pops the bar open for a
  few seconds while the strip stays out. There is no event or API for the
  flash state; fixing it would need pixel forensics or an explorer hook this
  tool-process mod cannot install.
- Reveal-by-touch: the strip reveals when the cursor enters the ~3 px edge
  band, matching the shell closely but not frame-exactly; worst case the
  slide leads or trails the bar by ~150 ms.
- Only the main (primary) taskbar is followed, as before.

## Records

- Source, install/audit/rollback script, probe scripts, logs, screenshots:
  `reports\2026-10-07-visualizer-taskbar-follow\`
- Backup: `backups\2026-10-07\visualizer-follow\` (rev 3 DLLs, registry
  export, live source as of 2026-10-04 10:42 PM).
- Rollback: `install-visualizer-130.ps1 -Rollback` (points LibraryFileName
  back at `..._1.2.0_3.dll`).
- The `diagnostics.enabled` setting was turned on for verification; restore
  it with `reports\2026-10-07-visualizer-taskbar-follow\set-diagnostics.ps1 0`
  after the user confirms the behavior in a game.
