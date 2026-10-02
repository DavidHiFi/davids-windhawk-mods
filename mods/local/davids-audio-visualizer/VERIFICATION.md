# Verification

Verified on Windows 11 with Windhawk 1.7.3 on 2026-10-03.

- Windhawk's installed source parser accepted the ID, name, description, author, Details text, and 48 typed settings. Installed source discovery returned the named mod with no parser errors.
- Both x86 and x64 DLLs compiled. The source and DLL SHA256 hashes matched the installed copies.
- Thirty-six live cases varied every exposed setting. The original values were restored after the cases, and temporary diagnostic logging was then disabled.
- The cases covered all six shapes, five color modes, three sensitivity curves, four FFT sizes, three frequency scales and bar anchors, peak hold, geometry, backgrounds, custom media images, capture selection, idle throttling, and diagnostics.
- With a device filter matching nothing, the idle strip remained visible after idle throttling began. Media visibility and relative placement matched the requested settings.
- A Desktop-only filter opened one render path. A hardware Loopback-only filter opened two capture paths. Default-output mode with hardware loopbacks opened three. Restoring the all-output preset opened nine paths on the test machine.
- The overlay and media windows belonged to the main taskbar. Foreground and taskbar layout events update their ownership, geometry, and stacking without restarting the shell.

These checks cover the installed version and those settings on the test machine.
They do not guarantee capture of exclusive or protected streams on every driver,
or every hardware routing arrangement. The mod reports unavailable endpoints in
its optional diagnostics and retains the idle strip when capture is unavailable.

No audio routing, playback volume, drivers, or audio applications changed during
verification. The mod uses passive shared capture streams.
