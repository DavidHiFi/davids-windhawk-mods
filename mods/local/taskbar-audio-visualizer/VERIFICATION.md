# Verification

Verified on Windows 11 with Windhawk 1.7.3 on 2026-10-03.

- Windhawk's installed source parser accepted the ID, name, description, author, Details text, and 48 typed settings. Installed source discovery returned the named mod with no parser errors.
- Both x86 and x64 DLLs compiled. The source and DLL SHA256 hashes matched the installed copies.
- Thirty-six live cases varied every exposed setting. The original values were restored after the cases, and temporary diagnostic logging was then disabled.
- The cases covered all six shapes, five color modes, three sensitivity curves, four FFT sizes, three frequency scales and bar anchors, peak hold, geometry, backgrounds, custom media images, capture selection, idle throttling, and diagnostics.
- With a device filter matching nothing, the idle strip remained visible after idle throttling began. Media visibility and relative placement matched the requested settings.
- A Desktop-only filter opened one render path. A hardware Loopback-only filter opened two capture paths. Default-output mode with hardware loopbacks opened three. Restoring the all-output preset opened nine paths on the test machine.
- The overlay and media windows belonged to the main taskbar. Foreground and taskbar layout events update their ownership, geometry, and stacking without restarting the shell.

## Fullscreen and input fixes in 1.0.1

The fullscreen option adds a 49th setting, `performance.hideWhenFullscreen`,
enabled by default. A taskbar-covering foreground test window hid the overlay
after about three seconds. Closing it restored the overlay.

Before the input fix, all 32 sampled points across the taskbar resolved to the
visualizer window. After adding layered-window transparency with alpha 255,
all 32 resolved to Explorer while the spectrum remained visible. The overlay
uses DirectComposition and keeps its taskbar ownership. Its initialization
now closes the window if layered transparency cannot be configured.

These input checks did not send actual clicks or exercise enabled media
buttons. Version 1.0.1 contains the installed fix with updated version metadata.

These checks cover the installed version and those settings on the test machine.
They do not guarantee capture of exclusive or protected streams on every driver,
or every hardware routing arrangement. The mod reports unavailable endpoints in
its optional diagnostics and retains the idle strip when capture is unavailable.

No audio routing, playback volume, drivers, or audio applications changed during
verification. The mod uses passive shared capture streams.

## Capture picker in 1.1.0

Both x86 and x64 builds pass. The live picker covers only the bars on the
main taskbar. A screenshot confirms the rounded Mocha hover highlight.
The menu lists six recording inputs and eight playback outputs on this machine.
Selecting Desktop Output saves its endpoint ID and captures one stream.
Selecting Recording Input opens exactly one capture endpoint successfully at
48 kHz, stereo float32. Existing system-widget positioning is retained.

The selected recording endpoint survives replacement of the visualizer process
and opens one stream again. Both the root menu and the output submenu have
WS_EX_TOPMOST, and WindowFromPoint resolves to the menu at each sampled menu
point. The menu opens outside the taskbar rectangle. A screenshot confirms
that the root menu and submenu are fully visible beside the taskbar.
Test selection and diagnostic logging were restored to their original values.

## Taskbar auto-hide follow and hide when covered in 1.3.1

Five new and updated behaviors verified live on 25H2 (build 26200.9457), a
four-monitor desktop with the taskbar on the primary's top edge and the
auto-hide switch on:

- Measured first: with the auto-hide switch on, the shell keeps the work area
  pushed in by the full bar height while the bar sits parked and visible with
  the cursor on another monitor and an ordinary window in the foreground. No
  window-state API returns the bar's true on-screen state. The mod therefore
  keys its follow mode to the work-area reservation itself: a bar that holds
  its space is resident and the strip stays visible with it; a free work area
  means the reveal model decides anything. A screenshot shows the strip
  seated with the resident bar, cursor far away.
- Hide when covered is enabled by default, and the coverage enumeration now
  counts only topmost windows: ordinary windows sit below the taskbar and
  their rects can never cover the strip, while a coverer's own topmost status
  is enough to prove it is on top. Enabling the check before this change
  would have hidden the strip whenever any maximized app was open.
- The occlusion target rect is published from the overlay window's screen
  origin and measured (442,12,600,38), matching the strip. The previous
  publisher added the virtual-screen origin, which on a multi-monitor desktop
  pointed the check at a different monitor.
- A titled topmost window placed over the strip met the 100 percent covered
  threshold: the log records the occluded transition, the hide, and the
  resume within one watcher tick each way. Removing the cover restored the
  strip.
- The health of four separate published builds was exercised: the old tool
  process wedged mid-reload was cleared, a fresh overlay recreates itself
  within one 100 ms tick if its window is lost, and one failed DirectX
  initialization no longer makes the instance permanently dead (retries are
  throttled to one attempt per 5 s).

Both architectures compile with the 1.7.3 engine toolchain. Verification was
performed with diagnostic logging enabled, then restored to its original off
state. Settings snapshots in manifest, mods-state and mods-settings were
refreshed to the 1.3.1 live state (51 typed settings).
