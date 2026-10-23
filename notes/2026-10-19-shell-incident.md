# Shell incident 2026-10-19 (desktop window lost during flyout work)

What happened, honestly: while iterating on the desktop-menu fix I restarted explorer
several times in quick succession (kill, let Winlogon relaunch, verify). Around
2:20 AM the shell stopped coming back: explorer processes started, the taskbar
appeared, but no desktop window (Progman) was ever created, and one explorer instance
showed the classic `0xc0000142` (init failure) dialog.

## What was ruled out

- The translucent-flyouts mod: disabled via registry (`Disabled=1`, marker bumped) and
  the shell still would not create the desktop. The mod is exonerated.
- Shell registry (`Shell`, `Userinit`): intact.
- IFEO on explorer.exe, AppInit_DLLs (64+32): empty/off.
- Application Error event log: no explorer crashes — the processes run, they just never
  take the shell role.
- Windhawk service: stopped during diagnosis — made no difference; it is Running again.

## State right now (3:10 AM)

- Taskbar is back (Shell_TrayWnd exists). Desktop window (Progman, desktop icons) is
  still missing.
- Two zombie explorer processes from 10:36/10:41 PM survived kills and reappeared with
  their original start times — stuck terminating; the kernel is in a bad state.
- Ableton Live has an unsaved project (`Main Setup*`), so I did not sign out or reboot
  without asking.

## Recovery

A sign-out and sign-in (or a reboot) rebuilds the shell and its desktop — the registry
facts above are normal, so a fresh session should come up complete. Save Ableton first.
After that the translucent-flyouts mod (0.6.50, re-enabled) loads into the new shell and
the desktop context menu gets its accent ring.

## Lesson for the record

The 2026-10-18 note already warned about duplicate shell instances after repeated
explorer restarts. Multiple rapid kill/relaunch cycles can wedge the shell role itself.
Next time: at most one explorer restart per change, verify the shell owns Progman before
the next cycle (`FindWindowEx(0,0,'Progman')`), and never chain restarts faster than
the shell has fully come up.
