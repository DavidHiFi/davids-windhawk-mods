# 2026-10-20 Taskbar right side "too low" — diagnosis + fix handoff

Thread: t3-64e98aa2 (Fix Taskbar Vertical Positioning), started 6:01 PM from mobile, fully autonomous.

## Owner complaint (6:02 PM)
"Taskbar too low — put the right hand side (icons, tray icons, AI quota usage, everything) back up to where it's meant to be."
Context: owner games on this machine (Plutonium T6 fullscreen on primary as of ~7:15 PM); request came from mobile.

## Measured facts
- Primary taskbar: 2560x48 at (0,0), TOP (taskbar-on-top). Bar height changed 50px (Oct 19) → 48px (today) — native height, not mod-forced; taskbar-on-top v1.3 unchanged (SCT 2026-10-03).
- Tray cluster vertical position: ink rows 12..35 of 48, center 23.5 ≈ bar center 24. STYLER RULE 63 (margin 9, VerticalAlignment=1) is intact per registry and matches pixels. Position is CENTERED — the owner-approved calibration. No position change is warranted.
- What actually regressed after today's 12:57 PM shell restart (translucent-flyouts 0.6.55 install):
  - local@taskbar-ai-quota-plus: dashboard (Grok/OAI/CC1/Go+ bars) not rendered. Config INTACT (ModsWritable\local@taskbar-ai-quota-plus\LocalStorage settings_v1 = final verified state incl. Go+ oc-len:67; 4 auth_* tokens present). DLL present (1.8.2.1_216543). => injection/init failure, not config loss.
  - micrographics-taskbar-clock: stylized date pills (MON 19 OCT) gone; plain date text today. Mod enabled (SCT 2026-10-15).
  - taskbar-tray-system-icon-tweaks: its tray hiding lost; ENG US input switcher, network, bell reappeared.
- The bare "100" between mic and volume: same slot held "49" on Oct 17 (good state) — a live metric element, present in approved states; not the complaint.
- Elevation from this thread's sandbox HANGS at UAC consent (temp wrapper run-190206.cmd at 7:02 PM, no child log) => elevated steps routed to an opencode child (same runtime the flyout thread uses, proven silent elevation today).

## Fix (in flight)
scripts\2026-10-20-tray-mod-reload.ps1 — backup 3 mod keys + ModsWritable quota key to backups\2026-10-20-tray-mod-reload\, then bump SettingsChangeTime on: local@taskbar-ai-quota-plus, micrographics-taskbar-clock, taskbar-tray-system-icon-tweaks. Hot reload only. NO explorer restart, NO windhawk.exe -restart (game up; engine restart ban stands).

## Verification plan
Registry readback (script prints); engine reload implied by SCT marker; visual capture deferred until the game leaves the primary (watcher job saving strips to $env:TEMP\tbfix\watch-*.png). Evidence delivery per hard rules: html_render embed + real T3 attachment in reports\2026-10-20-taskbar-right-low\.

## For the next thread
- Do not re-tune rule 63 / rule 61 — margin 9 is the owner-approved centered state (see notes\2026-10-19-tray-vertical-shift.md).
- If the dashboard is still absent after the reload, check the quota mod's init in the current shell (fetch thread/XAML insert) before assuming config loss; config is verifiably intact.
- An unrelated "ollama app.exe" application error dialog was on screen at 7:16 PM (owner's app, left alone).
