# 2026-11-22: autoscroll merge, Seamless Task Manager, audit fixes

Owner asked: one autoscroll mod, one Task Manager mod, act on the audit
(`reports\2026-11-22-mod-audit.md`).

## Audit CLEAR items (done)

- Removed with backups (`backups\2026-11-22-stale-mods\<id>`: registry export, source, DLLs;
  log `remove.log`):
  - 10:50 am: no-hidden-cursor, url-blocker, mute-in-background, spoof-machine-guid,
    force-system-cursor, sleep-countdown-reset (items 5, 6, 19).
  - 12:32 pm: fix-10-taskbar-notifications, taskbar-disappearing-icon-fix-win11,
    tray-ghost-cleaner (item 6). Shell check healthy first; Explorer pids unchanged 40 s later.
- Rollback for any of them: `reg import` the saved .reg, copy the source back to
  `C:\ProgramData\Windhawk\ModsSource` and the DLLs to `Engine\Mods\<arch>`, or reinstall
  from windhawk.net.
- Note: Explorer pid 13256 was replaced by 18284 at 12:19 pm, before any change from this
  thread (another thread or a folder window). Not caused here.

## Audit JUDGEMENT items, open for the owner (none touched)

- 1 priority optimizer raises the app in front (against his rule). 2 two volume pop-up mods.
  3 four shell pop-up position mods, merge. 4 two Start search mods, Start barely used.
- 7 border mod off in its settings but still loads into the window manager. 8 two video
  wallpapers with no video. 9 sandbox close-confirm and a diagnostic helper look unused.
  10 home-group and update panel restorers: off, crash Explorer; remove or test PC first.
- 11 text-replace loads everywhere, set up for two apps. 12 console dark mode shares hooks with
  Seamless Flyouts. 13 smooth scrolling overlaps Seamless Explorer View, touches Task Manager.
  14 two taskbar volume mods. 15-16 thirteen taskbar mods could join Seamless Taskbar (tray
  merge already under way in another thread). 17 animations, wobbly and per-monitor Win+D clash.
  18 three window mods could join Seamless Window Manager. 20-21 tree and focus-border mods
  could join Seamless Explorer View. 22-24 right-click, Explorer behaviour and hotkey families.
  25 console and winver text. 26 browser mods. 27 icon mods. 28 dark app mods.
  29 startup delay as a Startup Control setting. 30 wallpaper mods. 31 old window switcher
  waits on the alt-tab plan. 33 Share and notification styler overlap a little, watch only.
- Task Manager caveats: the merged mod also loads into Windhawk's own background process (tray,
  settings window, taskbar-button keeper, where Tail already ran), never Explorer; the older
  DirectUI lists cannot take the look; the styler's window hooks and stats timer were dropped;
  test PC skipped (held by 9036a277).

## Repo manifest drift (audit)

- About 4:45 pm: `scripts\2026-11-22-manifest-sync.py --write` brought the published mod list in
  line with this PC: 187 to 173 entries, 22 library sources added under `mods/catalog` (every one
  passed the publish secret check), versions and on/off from the registry. Commit c1c882c, pushed
  (not forced). Undo: `git revert c1c882c`. Run it again after the nine Task Manager mods go.

## Settings engine manifest

- `docs\settings-engine.json` backed up to `settings-engine.json.bak-20261122-1240`.
- New: `local@seamless-task-manager` (swaps for title, glyph, rail; owns Set_FormatHotkey like
  the AutoClicker it was copied from). Rollback: restore the backup.

## Seamless Autoscroll 2.0.0

- Source: `work\2026-11-22-autoscroll-merge\seamless-autoscroll.wh.cpp`; global scope is now the
  setting "Cover all apps" (coverAllApps). Install keeps the owner's settings and turns
  local@seamless-autoscroll-global off; removal follows once verified.
- 2:11 pm: the gated retries kept getting exit 75 (CPU busy) and the helper script died on a
  missing Get-FileHash under the gate's shell. Owner said skip the queue: installed straight
  under the engine lock. 2:22 pm registry shows 2.0.0 (dll 2.0.0_499116).
- 2:26 pm: Global turned off; 2:27 pm the elevated helper (pid 12004) holds the 2.0.0 dll and
  Global is removed (backup `backups\2026-11-22-stale-mods\local@seamless-autoscroll-global`,
  undo: `reg import` its .reg, copy source and dlls back). Repo: cdf1c19 removes it from the
  source tree, manifest, presets, settings and both READMEs; feed b2a39a8 lists 51 mods.
- Left: Crash Watch's default "never quiet" list still names the old id (harmless text).
  Live middle-drag proof: owner said do it now (2:45 pm). `drag-test.ps1` opens a WinForms text
  box in powershell.exe (not on the include list), middle-drags down: top line 0 -> 575, frosted
  circle with the gradient ring captured in `drag-test.png`. Cursor put back, window closed.
  Run with SWM_AGENT_QUIET=0; the desktop lock was free but two threads were queued for it.

## Seamless Autoscroll 2.0.1 (toggle everywhere), installed

- Owner: toggle works in Explorer but other apps act like hold. Cause: the all-apps helper's
  middle-release handler stopped the scroll before it checked toggle mode (the in-app path was
  right). Fix: in toggle mode the release is swallowed and the scroll keeps going; the next
  middle click stops it. Default stays hold. Owner's setting is already toggle.
- Source: `work\2026-11-22-autoscroll-toggle\seamless-autoscroll.wh.cpp`, staged as
  `C:\Users\Public\seamless-autoscroll-2.0.1.wh.cpp`, base hash in `base-hash.txt` there.
- 3:14 pm install waited 15 min on the gate (CPU 100%, owner in Ableton, heavy slots full) and
  was stopped. Nothing changed: registry still 2.0.0, engine lock released 3:30 pm.
- To finish: `coop --as autoscroll-toggle lock windhawk-engine`, then Invoke-Elevated -File
  `work\2026-11-22-autoscroll-merge\elevated-install.ps1` -ArgumentList '-Id
  local@seamless-autoscroll -Staged C:\Users\Public\seamless-autoscroll-2.0.1.wh.cpp -BaseHash
  <base-hash.txt>', unlock; check the helper loads the 2.0.1 dll.
- Owner said get it done, don't wait: Install-StagedMod got a -NoCpuWait switch (skips only the
  CPU-under-70% wait; the desktop health check, cooldown and watch still run; backup beside it).
  T3 restarts killed three background tries; installed in the foreground 4:25 to 4:32 pm.
- Proof: registry 2.0.1; the elevated all-apps helper (pid 40324, started 4:31 pm) and Explorer,
  T3, Hydra hold dll 2.0.1_458654; repo source is 2.0.1 with the fix, pushed. Owner setting
  toggleMode=1, schema default stays hold. Live click proof (toggle-test.ps1) not run: owner was
  playing; it needs the desktop input lock.

## Seamless Task Manager 1.0.0

- Built by `work\2026-11-22-seamless-task-manager\gen.py` from the nine Task Manager mods, the
  AutoClicker tool side and settings window, and Windows Settings Styler's engine with a new
  Mocha theme. Every original setting kept, word for word, plus one on/off switch per tweak.
- Process filter: Taskmgr.exe for the tweaks and the look. windhawk.exe is also included: that is
  where the tray icon, settings window and the taskbar button keeper (Task Manager Tail, which
  was itself a windhawk.exe tool mod) run. Nothing loads into Explorer.
- Dropped from the styler: the CreateWindowInBand hooks and stats timer (Task Manager is found by
  polling for its window instead) and every bundled theme except the new Mocha one.
- Undo: turn Seamless Task Manager off and turn the nine old mods back on (they are disabled,
  not removed, until the new one is proved live).
- State at about 4:40 pm: NOT compiled, NOT installed. The offline compile went through the load
  gate from about 2:50 pm and every try got exit 75: Ableton, then two games (pvzgame,
  Plutonium), with both heavy slots busy. Loop stopped. Registry is unchanged: all nine old mods
  are on and local@seamless-task-manager is absent. The test PC was held by thread 9036a277.
- 6:27 pm: still not compiled. `pipeline.sh` (bash pid 25512, started 4:15 pm) holds one gate job
  with a 6 hour wait (until about 10:15 pm): compile, then install, then Autoscroll 2.0.1, all
  through heavy.py; progress in `pipeline.log`. The gate has held it the whole time: both slots
  busy, then the owner in Ableton; about 15 other threads are queued behind it. When it lands,
  run steps 2 to 5 below by hand (the pipeline only compiles and installs).
- 7:41 pm compiled with no errors (gate let it through). 7:49 pm installed: registry 1.0.0, desktop
  fine 60 s after, published (mods 5c3585b, feed 491c835). The pipeline's Autoscroll step stopped
  at 8:12 pm on "changed since staging": 2.0.1 was already in from 4:32 pm, registry says 2.0.1.
- Finding: Taskmgr.exe has an IFEO Debugger set to System Informer (the owner's Task Manager
  replacement since at least 2026-10-06). Every normal Task Manager launch opens System Informer,
  so the nine old mods and this one never show in daily use. The live check started the real
  Taskmgr as a debuggee (skips IFEO) from an elevated helper, `verify.py real_taskmgr()`.
- Live check, 8:00 to 8:10 pm (logs, PrintWindow, UI Automation, no clicks or focus): real Taskmgr
  pid 9656 loaded the dll; log says "started" for 8 tweaks (navigation border, details icon size,
  pause button, Esc, link speed, network bytes, tab slide, taller tab) plus "Mocha look on" and the
  Mocha colour resources. Taskmgr stayed responding. The mod's own tool process
  (windhawk-mod.exe, the Task Manager Tail side, tray and settings window) holds the dll too.
  Off/on cycle worked. Run new task dialog opened, captured and closed through UI Automation.
- Captures: `shot-live2-0.png` (Mocha, blue accent, Pause button, blue heat cells),
  `menus\menus-2-dialog.png`. Glass: the run dialog is solid Mocha (#20202F), glass-check says
  "barely frosted", so opaque fallback, not frosted glass. Corners at 4x (`corners\`): window and
  dialog all round, one edge each. Small misses: the dialog edge is neutral grey (58,58,58), not
  Mocha; the list's scrollbar track is pure black and its corner box stock grey.
- Not proved: the overflow "..." menu (UIA "NULL COM pointer", no capture), hover states (no
  desktop lock taken), Tail's taskbar-button behaviour (dll loaded only), the System Informer
  redirect means the owner will not see any of it unless that changes.
- 8:16 pm: the nine old mods removed under the engine lock, each backed up to
  `backups\2026-11-22-stale-mods\<id>` (registry, source, dlls; `remove.log`). Undo: reg import,
  copy back, or reinstall from windhawk.net. Explorer pids unchanged.
- Repo: manifest-sync af97b34 (174 to 165 entries), old sources dropped 8c73845, full publish
  f114107, feed c8da671. mod-consistency 0 fails, settings-engine check clean. Logging set back to 0
  (backup `local@seamless-task-manager-key-20261122-2021.reg`). Test Taskmgr and System Informer
  closed.
- Open gap, not mine: `settings/mods-state.json`, `mods-settings.json` and
  `windhawk-userprofile.json` in the repo keep entries for removed mods (also the 10:50 am ones);
  publish-mods only prunes `presets/davidhifi-setup.json`, which is clean. Seamless Task Manager has
  no group in `categories.json` (held by another thread), so the feed lists it under Other.
- 4:27 pm: stopped an old autoscroll 2.0.0 retry loop (`autoscroll-merge\retry-install.sh`,
  running since 1:34 pm). 2.0.0 was already in; a late run would have rolled back 2.0.1.
- To finish, in order (all scripts in `work\2026-11-22-seamless-task-manager\`):
  1. `bash gated-build.sh` (offline compile through heavy.py, retries on 75); fix any error in
     gen.py, run `python gen.py`, compile again.
  2. `heavy.py shell` must say healthy. Then
     `heavy.py run --reason "install Seamless Task Manager" -- powershell -NoProfile -ExecutionPolicy Bypass -File install.ps1`.
     It takes the engine lock only once the gate lets it run, turns the nine off (kept), installs,
     writes the defaults and turns logging on. If the install leaves no registry key, the nine
     go back on by themselves.
  3. `coop guard` clear: `python verify.py live 15` (starts Task Manager, reads the mod log, saves
     PrintWindow shots and log-live.txt). Every feature line must say "started", plus "Mocha look on".
     If Taskmgr.exe died: `Set-ModState.ps1 -Id local@seamless-task-manager -Off`, turn the nine
     back on.
  4. Elevated: `python menus.py <outdir>` opens the overflow menu and the Run new task dialog
     through UI Automation (no mouse), captures them and closes them. Then glass-check.py on the
     menu capture, 4x corners. Hover cannot be forced here: list it as not proved unless recorded
     under `coop lock desktop`.
  5. Elevated: `work\2026-11-22-stale-mods\remove-stale.ps1 -IdList "<the nine, comma separated>"`,
     then `python scripts\2026-11-22-manifest-sync.py --write`, `mod-consistency.py check --full`,
     `settings-engine.py check`, and logging off (LoggingEnabled 0).
