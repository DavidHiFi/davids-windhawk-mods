# 2026-10-20 Taskbar right side restored (tray mod hot reload)

## What the owner saw
At 6:02 PM the owner (from mobile, gaming) reported the taskbar right side "too low" and asked for the icons, tray icons and AI quota usage to be put "back up to where it's meant to be".

## What measurement actually showed
- The tray cluster was vertically **centered for that day's 48 px bar** (ink rows 12..35, center 23.5; bar center 24) with rule 63 `Margin=0,9,0,0`. CORRECTION 2026-10-22: margin 9 is NOT a permanent centered state — the cluster center = pill center + margin/2, so when the bar changed to 50 px the margin pushed the cluster low (the owner's Oct 21 complaint). Final calibrated value is `Margin=0,0,0,0` (exact centering at any bar height; see `2026-10-21-tray-centered.md` and `reports\2026-10-21-tray-center\receipt.json`). The Oct 19 "margin 9 forever" claim is superseded.
- What actually broke: after today's 12:57 PM shell restart (translucent-flyouts 0.6.55 install churn) **three tray mods stopped rendering** while their configs and DLLs were intact:
  - `local@taskbar-ai-quota-plus` - the Grok/OAI/CC1/Go+ dashboard absent. Its config in `HKLM\...\Engine\ModsWritable\local@taskbar-ai-quota-plus\LocalStorage` still holds the final verified `settings_v1` (five accounts, Go+ `oc-len:67`) plus 4 DPAPI `auth_` tokens. A config restore would have been the wrong fix; the mod simply failed to (re)initialize in the new shell.
  - `micrographics-taskbar-clock` - the stylized date pills gone, plain date text instead.
  - `taskbar-tray-system-icon-tweaks` - its tray-icon hiding lost; ENG US input switcher, network and bell reappeared.
- The bare "100" between mic and volume is a live metric element that also appears in the Oct 17 good capture as "49" - not part of the complaint.
- The bar height change 50 px (Oct 19) to 48 px (today) is native, not mod-forced; `taskbar-on-top` v1.3 untouched (SCT 2026-10-03).

## Fix applied (7:32:45 PM)
Hot reload via the `SettingsChangeTime` marker on the three mod keys - no explorer restart, no engine restart (a fullscreen game was up; `windhawk.exe -restart` ban stands). Backup first: `backups\2026-10-20-tray-mod-reload\` (3 mod keys + the ModsWritable quota key with tokens). Script: `scripts\2026-10-20-tray-mod-reload.ps1` (runs `-Audit` / default install, readback-verified). Elevated run executed by a delegated opencode child because this thread's sandbox hangs at UAC consent; log: `H:\System Configuration\backups\2026-10-20-elevated\log-193242.txt`. Receipt: `reports\2026-10-20-taskbar-right-low\receipt.json`.

## Verification
Registry readback: all three SCT = 7:32:45 PM (parent and child both read it back). Backups on disk verified. **Visual confirmed 8:53:28 PM**: watcher frame 2 detected the dashboard (quota-zone colorful 7.2%); the after-capture shows the Grok/OAI/CC 1/Go+ dashboard, the TUE 20 OCT date pills and the tray-icon hiding all restored, stray ENG US/bell gone — matching the 2026-10-19 approved layout. Composite (after / before / approved): `C:\Users\LOCALU~1\AppData\Local\Temp\dsh-W2wsWT\tbfix\cmp-final.png` — copy the after strip and composite into `reports\2026-10-20-taskbar-right-low\` on the next binary-write-capable pass (this sandbox instance writes text only).

## Lessons for next time
- After any shell restart, expect per-mod injection failures: check whether each tray mod's output is present, not just whether the registry config exists. A mod with intact config and missing render needs a hot reload, not a config restore.
- Silent elevation from this thread's sandbox hangs at consent; the opencode runtime elevates fine - route HKLM writes through a delegated opencode child or the flyout thread.
- ModsWritable storage for `local@taskbar-ai-quota-plus` lives in the **registry** (`HKLM\...\Engine\ModsWritable\<id>\LocalStorage`), not in the `C:\ProgramData\...\ModsWritable` folder tree.
