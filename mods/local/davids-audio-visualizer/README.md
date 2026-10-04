# David's Audio Visualizer

A taskbar spectrum visualizer with Catppuccin Mocha defaults, media buttons,
and capture of active Windows audio outputs plus hardware loopback inputs.

![David's Audio Visualizer on the taskbar](preview.gif)

## Installation

Requires Windows 11 and Windhawk 1.7.3 or later. Paste this complete source into
Windhawk's Create a new mod editor and compile it. Disable Tourne'Table or any
older local visualizer before enabling this mod.

The bars stay on the main taskbar. Set Horizontal offset to place them after
your system information widgets. Media buttons follow the bars automatically.
Changing the taskbar position or display layout updates both windows through
Windows events. Hide when fullscreen is on by default. It hides the bars and
media buttons while a fullscreen or borderless window covers the taskbar,
then restores them when the taskbar is available. Silence uses idle throttling.

## Settings

- Position sets the horizontal and vertical offsets in logical pixels.
- Appearance controls shapes, geometry, colors, response, EQ, FFT, and peaks.
- Audio selects all active outputs or the default output, hardware loopbacks,
  an optional device-name filter, and analysis gain.
- Background adds a panel and optional border behind the bars.
- Media buttons support built-in glyphs or local image files.
- Performance sets the drawing rate, idle throttling delay, and Hide when fullscreen.
- Diagnostics writes a rotating status log without recording audio samples.

Each frequency band uses the strongest captured level across devices. A signal
routed through several Matrix endpoints does not multiply its displayed level.
Capture uses shared WASAPI streams. Exclusive or protected outputs can reject
loopback capture. An interface hardware Loopback input can expose its ASIO mix,
depending on that interface's routing. Recording inputs are opened only when you explicitly select one from the device menu.

The mod does not change playback devices, routing, volume, or driver settings.
Right-click the bars to choose an Input device or Output device as the capture source.
The selection is saved by endpoint ID and survives restarts. Output devices use
WASAPI loopback. Input devices use their recording stream. Selecting a source
does not change Windows defaults or application routing. The menu can restore
the configured multi-device capture mode. Unavailable sources leave idle bars
and reconnect when the same endpoint returns. Media buttons receive clicks.

## Source and credits

Source, settings reference, license, and verification:
https://github.com/DavidHiFi/davids-windhawk-mods/tree/main/mods/local/davids-audio-visualizer

Maintained by DavidHiFi. Derived from USER-TOURNE's Tourne'Table 1.3.0 and
Salyts' Desktop Audio Visualizer. Their Direct2D renderer and Windows media
session implementation are retained under the MIT license. This version adds
taskbar ownership and event handling, multiple-output analysis, hardware
loopback support, settings validation, and a focused taskbar settings interface.

## Build and install

The Windhawk editor compiles the self-contained `.wh.cpp` source. For an offline
build with the standard Windhawk 1.7.3 installation, run `Build.ps1` from this
folder. It writes x86 and x64 DLLs beside the source and changes no live settings.
Compiled DLLs are not distributed because Windhawk normally builds them locally.

`defaults.json` contains the typed, complete preset. [SETTINGS.md](SETTINGS.md)
documents every exposed setting. A horizontal Windows 11 main taskbar is required.
Adjust Horizontal offset for your own taskbar layout; the default is 500 pixels.

## Verification

The installed Windhawk 1.7.3 parser accepts the metadata, Details text, and all
49 settings. Both x86 and x64 builds were compiled and matched their installed
SHA256 hashes. Live checks cover settings reloads, shape and color modes, FFT
sizes, frequency scales, EQ and sensitivity, geometry, background, media images,
capture filters, idle behavior, and diagnostics. Capture opens shared streams
without changing audio routing. Silent output and unavailable devices retain
the idle bars. Hardware loopback availability depends on the interface driver.

This is a maintained local mod published in DavidHiFi's repository. It is not
an entry in the upstream Windhawk catalog. The complete MIT notice and upstream
copyright are preserved in [LICENSE](LICENSE).


## Changes in 1.0.1

The bar window now uses layered-window transparency so taskbar clicks reach
Explorer across processes. If transparency initialization fails, the mod closes
the overlay instead of leaving a window that blocks input.

Hide when fullscreen now has an exposed setting, enabled by default. It checks
whether the foreground window covers the taskbar, including borderless games,
and hides both overlay windows during the pause. The media window limits its
hit-test handler to the three button squares.

Both architecture builds passed. With the installed fix, all 32 sampled points
across the main taskbar resolved to Explorer while the bars remained visible.
The fullscreen fix was observed hiding the overlay about three seconds after a
taskbar-covering test window took focus and restoring it after the window closed.
These checks did not send actual taskbar clicks or test enabled media controls.

## Changes in 1.1.0

The bars have a rounded Mocha hover highlight and a right-click capture-device
menu. Input device and Output device list active Windows endpoints. One selected
endpoint replaces the combined capture, and a checkmark identifies it.
The visualizer also respects the system-information widget boundary.
