# Window Manager 1.3.0 hardening (2026-11-07)

Source: `work\2026-11-06-window-manager\window-manager.wh.cpp`. Backup before changes: `window-manager.wh.cpp.bak-20261107`.

## Changes
- The elevated helper relaunches itself through `windhawk-mod.exe -windhawk-tool-mod`. Before this it used `windhawk.exe -tool-mod`, so the helper never started.
- Actions picked inside the mouse hook (right-click action, maximize while dragging) are posted to the hook thread's queue instead of running inside the callback.
- The window menu runs on its own thread with its own owner window.
- Topmost, lower, center and side-snap use `SWP_ASYNCWINDOWPOS`, so a hung app can't block input.
- Watchdog: if the pointer moved and the mouse hook saw nothing for 2 s, both hooks are reinstalled.
- The helper mutex grants SYNCHRONIZE to Everyone (low-integrity label), so normal apps see the helper and skip their own hook. ACCESS_DENIED also counts as "helper present".
- A second helper exits. A helper that fails partway through init stops its threads and releases the mutex.
- Center on a maximized window sizes from the restored rect.

## Verified (measured, 2026-11-07 1:27 am)
- x86, x64 and ARM64 compile with no warnings.
- One helper, PID 4648, started 1:26 am, still running 30 s later.
- A non-elevated process opens the helper mutex.

## Not done
- Physical drag and hotkey test: needs the owner at the mouse.
- Review items left as minor: per-click process lookup cost, `Sleep(1)` loop in the target app, duplicate right-button code.

## Rollback
Reinstall the `.bak-20261107` source with `scripts\2026-11-07-wm-install.ps1`, after pointing that script's file path at the backup.

## Drag latency (1:40 am)
- Global helper now moves dragged windows from a dedicated above-normal-priority thread that applies only the newest position and waits for it to land (posted move only for hung apps). Before, every mouse step queued an async move in the app, so busy apps trailed the cursor. Windows are already GPU-composited by DWM; the composition-visual path from GPU Accelerated Explorer only animates content inside a process and can't move another app's window.
- Measured: builds clean on 3 archs, helper running. Not measured: drag feel.

## Stuck Alt (1:51 am)
- Cause (inferred from code): GlobalAltProc swallowed the real Alt key-up after a drag, so Windows kept Alt held. Typing broke and plain drags acted as Alt drags.
- Fix: the real release is replaced with an injected dummy key (0xE8) followed by an Alt key-up. Windows always sees the release, and the dummy stops the window menu from opening. Helper restarted 1:50 am. Not measured live yet.

## Input-state audit (1:56 am)
Same class as the stuck Alt: anything that hides half of a press/release pair. Fixed:
- Helper no longer swallows the Alt release at all; it taps the 0xE8 mask key first and lets the real release through (an injected release can be dropped by UIPI).
- Per-app hook no longer eats the app's Alt release.
- Action mouse button and action hotkey flags reset on a fresh press, so a missed release can't eat the next one.
- The "mask the next Alt release" flag is only set while Alt is really held, and clears on every real Alt press.
- Watchdog also clears a drag whose button is no longer held.
- Explorer title-strip double-click now swallows its release as well as its press.
Measured: builds clean on 3 archs, one helper running since 1:56 am. Not measured: live typing and drag (owner test).
