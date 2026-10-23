# Windhawk window controls completed

Installed David's Window Pack, `local@david-window-pack`, version 1.0.0, DLL revision 3, on 2026-10-03 at approximately 02:53 Perth time.

The mod combines Snap Commander, Move Window to Monitor and the existing local AltSnap drag fork. Keyboard controls run in one elevated Windhawk tool process. The drag code runs inside applications, including administrator applications. The native Windhawk launcher also loads the drag code for its own dialogs. The merged mod does not inject a launcher into DWM.

All 65 original setting values and their registry types match the merged settings. The original three mods changed from `Disabled=0` to `Disabled=1`. Their source files, DLLs and settings remain available. The merged mod has `Disabled=0` and `Include=*|windhawk.exe`.

Windows currently reports three screens. The saved left-monitor target is index 3, which no longer exists. The merged code falls back to spatial movement when a saved target is missing. This preserves the setting while allowing the shortcut to work with the current display arrangement. A direction without a destination leaves the window in place.

## Verified behavior

- Ordinary test window and elevated Task Scheduler passed all four corner shortcuts, all four half-screen shortcuts, monitor movement up/right/left/down, Alt+left dragging and Alt+right resizing.
- Windhawk's elevated VSCodium UI passed all four corner shortcuts, monitor movement right/left/down, dragging and resizing. The test restored its original window placement.
- Task Scheduler loaded the final merged DLL. The dedicated Windhawk tool process runs elevated.
- Both x64 and x86 DLLs compiled successfully. Live tests used x64 applications.
- Installed DLL hashes and source hash match the workspace artifacts. All 65 settings match their original values and types.

The old test sent arrows using virtual keys without proper scan codes and extended-key flags. With Shift held, this produced the wrong hotkey. It also attempted to inject mouse input from a medium process into an elevated foreground window. The corrected tests send physical scan codes and use an elevated test controller for administrator windows. Those earlier failed synthetic-input tests were not proof that the mod itself failed.

No Windows, Windhawk engine or Explorer restart was requested. No restart is pending. Audio applications, display settings, security policy, scheduled tasks and unrelated mods were not reconfigured. Temporary Task Scheduler test processes were closed. Windhawk's UI remains open at its restored placement.

## Files and rollback

The final machine receipt is `reports/2026-10-03-windhawk-final-receipt.json`. Behavior evidence is in `reports/2026-10-03-windhawk-detailed.json`, `reports/2026-10-03-windhawk-medium.json` and `reports/2026-10-03-windhawk-own-ui.json`.

Original registry exports and source copies are in `backups/2026-10-03-windhawk-window-pack`. The initial install receipt in that folder records revision 1. The final receipt records revision 3.

To restore the exact pre-merge configuration, run `scripts/2026-10-02-windhawk-merge-install.ps1 -Mode Rollback` through an elevated shell or the workspace's silent `.cmd` elevation route. This disables the merged mod and imports the three original registry exports. It does not restart the engine or delete the original mods.

Read-only audit: `scripts/2026-10-02-windhawk-merge-install.ps1 -Mode Audit`.

Sources and compiled artifacts are in `Windhawk/window-pack`. The generator is `scripts/2026-10-02-windhawk-merge-generate.ps1`; the build script is `scripts/2026-10-02-windhawk-merge-build.ps1`. The test API and drivers are in `Windhawk/window-pack`.
