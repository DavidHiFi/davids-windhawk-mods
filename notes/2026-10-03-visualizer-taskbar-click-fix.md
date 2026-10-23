# Visualizer taskbar click fix

Applied 2026-10-03 at 05:53 Perth time after resuming T3 thread a7f01a24-eb5b-45bd-8645-d873cb003ae4.

The full-width DirectComposition overlay intercepted every one of 32 sampled taskbar points. It returned HTTRANSPARENT and had WS_EX_TRANSPARENT, but it was not layered. HTTRANSPARENT searches windows on the same thread. Explorer owns the taskbar on a different thread and in a different process. The earlier single-point test did not establish working input routing.

Added WS_EX_LAYERED and SetLayeredWindowAttributes with alpha 255. The existing DirectComposition rendering remains visible. If layered-window initialization fails, the mod destroys the overlay instead of showing a window that blocks input. A live EnableWindow(false) experiment did not resolve routing and was reverted before applying the layered-window fix.

Both architecture builds passed. Installed source differs from the backup only by the layered-window flag and initialization check. The installed DLLs match their build hashes. All 32 post-install sampled points resolve to Explorer, including the application strip and system tray. Cropped taskbar images show the bars still rendering. No synthetic clicks or playback commands were sent, so actual app launching and context-menu interaction were not exercised.

LibraryFileName changed from local@davids-audio-visualizer_1.0.0_1.dll to local@davids-audio-visualizer_1.0.0_2.dll. Disabled remains 0. Hide when fullscreen remains 1. Only the visualizer process was replaced. Explorer, Windhawk's main engine, audio applications, display configuration and game files were not changed. No Windows restart is pending.

Evidence and installation script are in reports/2026-10-03-visualizer-clicks. Exact previous source, both DLLs and registry export are in backups/2026-10-03-visualizer-clicks. The source generator was updated in H:/work-visualizer-hide/Windhawk/davids-audio-visualizer and copied into the evidence directory. This thread has not published or committed the source.

To roll back, silently elevate rollback.cmd in the evidence directory. It briefly disables this mod, restores the previous source and registry, and selects the retained previous DLL filename. This restores the version that blocked taskbar input.
