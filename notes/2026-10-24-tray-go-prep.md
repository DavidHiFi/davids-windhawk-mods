# Tray position: prepared for "go" (2026-10-24, read-only research)

## State read 2026-10-24 (registry reads, nothing changed)
- Windhawk service Stopped / Manual (freeze hunt, `H:\System Configuration\notes\2026-10-23-freeze7-crashers-wer-identified.md`).
- `windows-11-taskbar-styler` Disabled=1 and `taskbar-on-top` Disabled=1: both sit in the hunt's 40 disabled suspects. The pill, the top bar and every position rule are off until those come back.
- Rule 63 still `VerticalAlignment=1` + `Margin=0,0,0,0` (SCT 1792604416, the 1:40 AM Oct 22 value). The value never moved.
- Junk left in the styler Settings key, harmless: a value literally named `\controlStyles[61].styles[0]\` (`\Margin=0,0,-10,0\`), `VerticalAlignment@1=1`, and a stray `Settings\SettingsChangeTime`.

## Why it kept "jumping" (inferred, not measured)
Margin 0 measured dead center at 1:40 AM Oct 22 with the full mod set loaded. The 10:34 AM Oct 22 "too high" report landed in the middle of the freeze hunt, which booted the engine with different mod subsets (styler with or without on-top, quota, tray tweaks). The styler value was unchanged, so the layout around it changed, not the fix. The owner's message said "left-hand side"; read as the right-hand tray cluster (the only part ever moved), and the go script measures both sides so either reading gets caught.

## What "go" does
Precondition: the freeze thread has the engine back on with the taskbar family enabled (styler, taskbar-on-top, ai-quota, tray-system-icon-tweaks). This thread does not start the engine or re-enable suspects.
1. `scripts\2026-10-24-tray-go.ps1 -Measure` (read-only capture of the top strip; left and right offsets from the pill center).
2. Right side off by more than 1.5 px: run `-Apply -Delta <offset>` elevated. It backs up the styler key, rewrites rule 63 margin from the measured law, bumps SettingsChangeTime (hot reload, no Explorer or engine restart), reads back, and prints the rollback.
3. Left side off: that is `local@taskbar-system-info-weather`, not the styler; measure, then fix in that mod's own settings.
4. Re-run `-Measure` and show the proof strip.
Syntax-checked and margin math dry-run 2026-10-24 (0 parse errors; too high by 3 gives `Margin=0,6,0,0`). Not run against the live bar yet: the bar is unstyled right now.

## Outcome (supersedes the margin-0 law below)
See `notes\2026-10-24-tray-centered-outcome.md`. Margin 9 measured centered on 2026-10-24.

## Go run, 2026-10-24 1:25-1:50 AM (measured)
- Live bar at top, 2560x50. Left/middle center ~26.5, right tray cluster center 17.5: about 8 px high. Reproduces on every Explorer start (1:32 AM, 1:49 AM).
- Not the AI quota mod: a negative-margin patch to its dashboard changed nothing for the tray, so it was rolled back (source hash back to 9B093AAF..., recompiled 1:30 AM).
- Reloading `taskbar-icon-size` (TaskbarHeight=50) re-centers the tray (24.5 at 1:34 AM), so the cause is that mod resizing the bar after the tray has laid out. The styler's rule 63 (VerticalAlignment=Center on SystemTrayFrameGrid) is what corrected this before; the styler is Disabled=1 as a freeze8 suspect, so the correction is absent.
- taskbar-on-top: enabling it also re-centered, but the freeze8 hunt resets it (DRIFT at 1:31 and 1:44 AM, caused by me; noted on coop). Do not touch suspect flags while freeze8 runs.
- Incident: a disable/enable reload of taskbar-icon-size hung in "Uninitializing" in explorer around 1:46 AM; the shell restarted 1:47:25 AM and the taskbar came back 1:49 AM. Do not live-reload taskbar-icon-size again.
- Fix path: the tray re-centers once freeze8 clears windows-11-taskbar-styler (rule 63 unchanged, Margin=0,0,0,0). Fallback if the styler stays off: TaskbarHeight 48 in taskbar-icon-size, applied at an Explorer restart boundary, not as a live reload.
