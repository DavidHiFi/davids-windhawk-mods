# Seamless Windows Firewall 1.0.0 (port of !Net by Ashix)

Owner asked 2026-11-22: port https://windhawk.net/mods/not-net, make it ours as Seamless
Windows Firewall, full rice, universal settings window, tray icon, app icon, workflow.

Owner's picks: tray icon plus edge pill (pill hides in full-screen games); Ctrl+Alt+F blocks or
allows the app in front, Ctrl+Alt+Shift+F opens the panel, allow-all has no default key;
publish with credit (original has no license, we claim none); full Mocha rice.

## Where things are

- Work folder: `work\2026-11-22-seamless-windows-firewall\` (src\core.cpp, settings.yaml,
  settings-block.cpp; `assemble.py` builds `seamless-windows-firewall.wh.cpp`).
- Icon: `make_icon.py` -> `media\` (256 and 64 px PNG, multi-size .ico).
- Offline compile: `test\compile.ps1` (writes test\compile.log), started detached through the
  load gate, result in `test\gate.log`.
- Test PC kit: `D:\Agent Work\swf\` (swf-driver.ps1 on Warden; swf-setup, swf-run, swf-test inside).
- Settings engine: added with `settings-engine.py add --staged` (backup of
  docs\settings-engine.json beside it).
- Workshop group: `davids-windhawk-mods\mods\categories.json` -> Tools (backup in `backups\`).

## Checks so far

- settings-engine: in sync. settings-material: ok. mod-consistency: 0 fail, 0 warn.
- Source pure ASCII, bare @id, no @license, credits in the readme and @author.

## Result (9:40 pm)

- Offline compile: passed.
- Test PC first load (Windhawk 1.7.3): 10 of 11 checks pass. Panel opens and closes,
  Ctrl+Alt+F adds 4 block filters and removes them, Explorer fine, no error boxes, no crash
  dumps. The one miss: 1.7.3's tray runs without admin rights and our launcher only starts the
  tool process when elevated, so the test starts it by hand. The tower's 2.0 alpha runs tool
  mods elevated, so this is a test PC gap only. Logs: `D:\Agent Work\swf\results\out\`.
- Tower: installed 1.0.0 through Install-StagedMod, desktop fine after the 60 s watch, tool
  process elevated, pill on the right edge, 34 settings present.
- Captures: `work\2026-11-22-seamless-windows-firewall\media\live\` (pill, panel,
  panel-context, preview). Taken by posting the panel's own tray message, no input, no focus,
  with "Hide from screenshots" off for the shot and back on after.

## 1.1.0 (2026-11-23)

- The three yes/no boxes (block a VPN or remote app, allow one back, stop a timer) now use our
  own frosted Mocha box (`SeamlessFirewall_Confirm_v1`): 2 px edges on the live radius, red
  "Block anyway" on risky questions, Tab, Y, N, Esc, Enter and hover. If the box cannot open,
  it falls back to the stock message box so the question is never skipped.
- A risky box starts on the safe button, so Enter keeps things as they are (found on the test
  PC shot: 1.1.0's first build had "Block anyway" picked first).
- Offline compile passed (test\gate6.log). Test PC: 14 of 15 (box appears for the remote
  desktop app, Esc blocks nothing, Y blocks, allow works, no crash or error events; the one
  miss is the known 1.7.3 tool-process gap). Shot: `D:\Agent Work\swf\results\out\box-crop.png`.
- Tower: installed 3:00 am over 1.0.0, registry 1.1.0, desktop fine after the 60 s watch, mod
  and feed pushed (test\install-1.1.0.log).
- Live captures (box rest, Tab, hover, tray menu, settings window, glass check, 4x corners,
  motion clip) run from `test\capture-when-free.ps1`, which waits its turn for the screen.
  Output in `media\live\1.1.0\` (capture.json, analyze.json). capture-all.py refuses to send
  the hotkey unless the remote desktop app is in front, so it can never block a real app.

## 1.2.0 (2026-11-23): our own box replaces the Windows Firewall pop-up

Owner asked for the "allow this app?" pop-up to use the mod's look. Picks: same apps as
Windows asks about, keep Windows Firewall and swap only the pop-up, a centred box, and the box
waits until answered (the app stays blocked meanwhile, as with Windows).

- How: a worker thread looks at the TCP and UDP listeners every 2 s (IPv4 and IPv6, loopback
  skipped). An app in the desktop session, outside Windows' folders, with no inbound firewall
  rule of its own, is asked once per session, and only while a current network profile has the
  firewall on and inbound blocked by default. The box is the FwConfirm box, centred on the
  screen under the pointer, never activated (the app you type in keeps the keyboard), hidden
  while a game is full screen. Allow or Block adds a normal inbound rule named
  "Seamless Firewall: <app>" in the group "Seamless Windows Firewall" (Allow: private and
  domain, plus public if the setting is on or you are on a public network now; Block: all).
- Settings (Blocking, Connection requests): "Ask with our own box" (on) and "Allow on public
  networks too" (off).
- **Windows setting changed while the mod runs:** each profile's "notify on listen"
  (`NotificationsDisabled` through the firewall's own interface). Old: the per-profile value
  found at start, saved in the mod's storage (`fwPromptOrig_domain/_private/_public`). New:
  notifications off. Given back when the setting goes off, when the mod stops, and at the next
  start if the setting is off (covers a crash).
- Rollback: `Set-ModState.ps1 -Id local@seamless-windows-firewall -Off`. If the mod ever
  crashed and was then turned off before it could give the setting back:
  `netsh advfirewall set allprofiles settings inboundusernotification enable`.
- Offline compile passed (test\compile.log). Test PC kit: `D:\Agent Work\swf-120\`.
- Test PC (10:37 pm): 20 of 20. Box comes for a listening app, no Windows alert, centred to the
  pixel, Notepad kept the keyboard, Allow by click and Block by N each saved the right rule, a
  second app got its own box, no box while a full-screen window was in front and it showed
  after, setting off gave the Windows pop-up back and on took it again, Explorer and the tool
  stayed up, no error events, no crash dumps. Logs and shots: `D:\Agent Work\swf-120\results\out\`.
  The test PC has no GPU, so corners and glass are proven on the tower captures instead.
- Before the tower install: every app already listening there has an inbound rule
  (test\dry-run-listeners.ps1), so no burst of boxes at install.
- Tower install: test\install-when-free.ps1 (log test\install-1.2.0.log). It writes the two new
  settings (on, off) when missing, since a missing setting reads as off.
- Tower result (10:39 pm): registry 1.2.0 (was 1.1.1), desktop fine after the 60 s watch, the
  engine had already written the two new settings (on, off), Windows pop-up switch now off on all
  three profiles, mod pushed (26d53b7) and feed pushed (b8d0334).
- Live captures: capture-all.py now calls the box up with a throwaway listener app (no hotkey,
  so no real app can be blocked), slides it over the open panel for the glass check, answers
  Block with Esc, then removes the rule and the app. Output `media\live\1.2.0\`.

- First tower capture run (10:42 pm): the box came up 2 s after the throwaway app started,
  centred to the pixel, the app in front kept the keyboard, Esc saved a Block rule, the rule and
  app were removed after, the Windows pop-up switch read off on all three profiles. The shots
  and clip did not show the box, and that was the capture, not the mod: the plain screen copy
  leaves out see-through (layered) windows (the tray menu shot came out blank the same way), and
  the recorder's screen numbers had moved, so the clip filmed a side screen. The full-screen
  check was read live too (notification state 5, accepting, front window not full screen), so it
  does not hide the box by mistake.
- Fixed in capture-all.py: shots include layered windows, the main screen's recorder number is
  found each run, the panel open is retried until it is really open, the box's visible state and
  fade level are logged, and analyze.py cuts a second shot of the box from the video. Rerun
  queued (test\capture-1.2.0b.log).

- Correction, third run (10:59 pm, test\capture-1.2.0c.log): the capture fixes worked, and the
  box really was invisible. It was up after 3 s, centred, keyboard kept, Esc saved Block, but its
  fade level read 0 of 255 a second later, the glass check saw straight through it and the video
  shows no box. So the earlier "only the capture" line above was wrong. The panel's open
  animation stalled in the same run (6 px wide).
- Cause: every window that opens or closes anywhere on the PC (consoles, tooltips, menus)
  made the hook post one message to the mod's window thread. On the busy tower that stream
  never stops, and Windows only hands out timer ticks when the queue is empty, so the box's
  10 ms fade-in timer and the panel animation never ran. The test PC is quiet, so it passed there.
- Fix in 1.2.1: the hook only marks "apps changed" and "front window may have changed" and arms
  one 60 ms timer that handles both once. The 1 s full-screen check also forces the box to full
  strength if it is still see-through after 300 ms, and a box shown again after a game ends
  comes back at full strength. Readme "What's new in 1.2.1" added. Backups:
  src\core.cpp.bak-20261123-pre-121, assemble.py.bak-20261123-pre-121.
- Test PC kit for 1.2.1: `D:\Agent Work\swf-121\`, with flood.ps1 that opens and closes hidden
  windows nonstop while the first box comes up, and a new check that the box reads 255.
- test\pipeline-1.2.1.ps1 runs build (load gate), test PC, install (base = the live 1.2.0
  source), then the live captures into `media\live\1.2.1\`. Log test\pipeline-1.2.1.log.

- 1.2.1 result (11-24, 1:02 am): test PC 21 of 21, the box read 255 of 255 while the busy-PC
  flood ran. Installed on the tower (install exit 0, registry 1.2.1), published (feed 368fe40).
  Its live captures were dropped for 1.2.2, which supersedes it.

## 1.2.2: no edge pill, no hover (11-24)

- Owner, 11-24: the pill on the top monitor and the hover reveal at the bottom right were never
  wanted. The mod is a tray icon plus the centred connection box, nothing else on screen.
- core.cpp (backup src\core.cpp.bak-20261124-pre-122, edit script edit122.py): the window
  starts hidden and is shown only while the panel is open. The panel opens centred on the work
  area of the screen the pointer is on (the tray's screen after a tray click), with a short grow
  from 94%, and hides the moment it closes. Settings for the pill, hover reveal, edge position,
  remember position, follow cursor and the clock button next to the pill are forced off in
  LoadSettings, so old registry values from 1.2.1 cannot bring the pill back. A header drag
  moves the panel for that opening only (no edge snapping, nothing saved). A tray click within
  400 ms of an outside-click close is ignored, so one click on the icon closes an open panel
  instead of reopening it.
- spec.py (edit122spec.py): those settings are gone from the settings window and Windhawk's
  page; "Hide from screenshots" moved to the Panel page. gen.py: 20 fields.
- assemble.py (edit122readme.py): version 1.2.2, readme without the pill, "What's new in 1.2.2".
- Offline compile clean. Test PC kit `D:\Agent Work\swf-122\` adds: nothing of ours visible at
  rest, pointer resting on four screen edges opens nothing, a posted tray click and
  Ctrl+Alt+Shift+F each open the panel centred (3 px), a click outside, the shortcut again
  and a second tray click each close it. All 1.2.1 box checks stay.
- test\pipeline-1.2.2.ps1: build, test PC (must pass the no-pill and tray checks too), install
  (base = the live 1.2.1 source), then capture-122.py: a shot of every screen at rest, the panel
  opened from the tray on the main screen (recorded), and the connection box. Log
  test\pipeline-1.2.2.log, media in `media\live\1.2.2\`.
- First test PC run (1:28 am, test\pipeline-1.2.2-run1.log): 25 of 29, not installed. No pill,
  edges open nothing, the tray opens the panel centred to half a pixel, every box check passed.
  The miss: a click outside did not close a panel opened from the tray, and the three checks
  after it failed only because of that. Cause: the panel never takes focus now, so only the 50 ms
  button poll could see the click, and a short click falls between two polls.
- Fix (backup src\core.cpp.bak-20261124-pre-122b, edit122b.py): while the panel is open a
  low-level mouse hook passes every press to the panel, which closes when the press is outside
  it, the connection box and the clock. The hook is removed the moment the panel closes. The
  test click now holds the button 150 ms like a real one. Rerun started 1:34 am.

- 1.2.2 result (11-24): test PC 30 of 30 (1:58 am). Installed 2:00 am over 1.2.1, registry 1.2.2,
  desktop fine after the 60 s watch, mod pushed ecce141, feed 2ad4a0f. Live captures 2:16 am
  (`media\live\1.2.2\`): none of our windows visible on any screen at rest, the tray opens the
  panel dead centre on the main screen (0,0 off), a second tray click closes it, the connection
  box came up in 1.3 s centred, alpha 255, the app in front kept the keyboard, Esc saved Block and
  the test rule was removed. Clips: panel-from-tray and connection-box-motion (mp4 and gif).

## 1.2.3: glass and open and close motion (11-24)

- Owner, 11-24: the box glass was "a bit flat"; every panel and box opens and closes with a
  fade plus a short slide, on by default, with its own on/off and a speed that follows the
  global speed (HKCU\Software\DavidHiFi\Motion), still when Windows animations are off.
- core.cpp (backups src\core.cpp.bak-20261124-pre-123 to pre-123d): the panel is layered only
  while it moves. A kept frame is pushed with UpdateLayeredWindow at the slid position with
  alpha rising over about 160 ms (ease-out) on open and 120 ms (ease-in) on close; once
  settled the layer drops and the real glass goes on, so DWM glass is never faded. New
  settings flyoutAnimation and animationSpeed on a Motion page (spec.py, settings-block.cpp).
- First test PC runs: 25 of 34. Box glass and box motion passed; every panel check after the
  first open was out of step. Trace (temporary TRACE123C lines, removed before release by
  untrace123c.py) showed the motion code was right: the panel's first paint took 3.5 s on the
  cold test PC (later paints about 6 ms), so the test's next input landed mid-stall and every
  toggle after it was one behind. Slow parts: GDI+ font loading for the text and icon faces
  and the first app icon extraction.
- Fix: WarmPanelDraw, two seconds after the mod starts, draws the panel's fonts once into a
  small bitmap and loads every listed app's icon into the cache, so the first real open is fast.
- Build and test ran through `D:\Agent Work\swf-123\lowrun.py` (queue skipped as the owner
  asked; idle priority, 40% cap, 10% while the owner plays). The test PC VM sits outside that
  cap, so chain-d.sh holds the VM run while the owner plays. test\compile.log starts with a
  byte-order mark: match "exit 0" anywhere on the line, never "^exit".
- gen.py now stops at the icon glyph patch because the key click donor changed since 4:22 am;
  settings-block.cpp and settings.yaml from 4:22 are current, so 1.2.3 builds from
  assemble.py alone. Fix gen.py's patch list before the next settings change.

## 1.2.5: right-click menu for apps, replacing Sordum's Firewall App Blocker (11-26)

- Owner, 11-26: remove the installed Sordum Firewall App Blocker right-click menu and merge it
  into this mod, so a right-click on a program blocks or allows it the same way, with a setting
  to turn the menu entry off. 1.2.4 (another thread, icon only) shipped meanwhile, so this is
  1.2.5 on top of it (its plateless shield icon ported into core.cpp and gen.py).
- What Sordum had: HKLM\SOFTWARE\Classes\exefile\shell\WinFirewall, "&Firewall App Blocker"
  with Block In Windows Firewall (`Fab.exe /A "%1"`), Remove From Windows Firewall (`/D`) and
  Launch, plus the program folder C:\Program Files\Firewall App Blocker (Fab.exe, Fab.ini, v1.9
  from 2022). No service, task, startup entry, uninstall entry or rule group of its own.
- What the mod does now (setting contextMenu, page General, on by default): a "Seamless Windows
  Firewall" submenu on every program file with Block in Windows Firewall, Allow again (remove the
  block) and Open the firewall panel. The keys live under HKCU\Software\Classes\exefile\shell\
  SeamlessFirewall (HKLM when the mod runs as SYSTEM), written when the mod starts or the setting
  turns on, removed when it turns off or the mod stops.
- How a click gets to the mod: the menu runs windhawk-mod.exe with `-windhawk-tool-mod
  "local@seamless-windows-firewall" -swf-block "<exe>"`. The engine loads the mod into that copy,
  whose static constructor sends the request to the running tool's message-only window
  (WM_COPYDATA) and ends itself before any tool code starts. The tool checks the setting, real
  input in the last 15 s, that the sender is windhawk-mod.exe from its own folder, and that the
  path is an existing .exe. Block adds permanent Windows Firewall rules (out, plus in when the
  default direction blocks both; group "Seamless Windows Firewall"; protected and system apps
  refused). Allow again removes every block rule for that program (Sordum's old ones too) and
  keeps allow rules.
- Test PC: swf-test.ps1 section 5 (menu keys follow the setting; Block and Allow again run as the
  tester's normal rights through a scheduled task; no helper copies left; no second tool).
  chain-f.sh, 45 checks.
- Run 1 (2:55 am): 39/45. The test PC's Windhawk 1.7.3 has no windhawk-mod.exe (tool mods run
  inside windhawk.exe there), so the mod left the menu off. Fix: CtxForwarderExe falls back to
  the host exe when it is windhawk.exe, and the test reads the helper from the menu command.
  The tower (2.0 alpha) has windhawk-mod.exe, so it keeps the first path.
- Run 2 (3:14 am): 43/45. Block, Allow again and Open all worked through the 1.7 helper; block
  rules land in PersistentStore. The two left: the menu was missing at first start because a
  setting new in an update is not in the registry yet and reads as 0. Fix: contextMenu=1 added
  to test\elevated-install.ps1's new-setting defaults (backup .bak-20261126-pre125) and to the
  test PC's defaults.json.
- Run 3 (3:28 am): 45/45 passed, crash dumps 0. Install queued on the windhawk-engine lock
  (held by tray-folder-gap); chain-f retries every 10 s.
- Sordum removed from the tower (3:42 am, test\elevated-remove-sordum.ps1 and -lnk.ps1, log
  C:\Users\Public\remove-sordum.log). Old: HKLM\SOFTWARE\Classes\exefile\shell\WinFirewall,
  C:\Program Files\Firewall App Blocker (Fab.exe, Fab.ini) and the Start menu shortcut
  "Firewall App Blocker.lnk". New: all three gone. Its firewall rules were left in place (an
  audit found none that look like its own). Rollback: `reg import "backups\sordum-fab-winfirewall
  .bak-20261126-0244.reg"`, copy backups\sordum-firewall-app-blocker.bak-20261126-0244\Fab.* back
  to C:\Program Files\Firewall App Blocker and the .lnk back to ProgramData\...\Start Menu\Programs.
- Tower install (6:22 am, detached chain D:\Agent Work\swf-123\finish-125.ps1, log finish-125.log):
  registry 1.2.4 to 1.2.5, desktop fine 60 s after loading, mods pushed 04604c0, feed 855c681.
  Windows' own "allow this app" pop-up stays off on all three profiles.
- Tower captures (6:44 am, media\live\1.2.5): panel opens centred from the tray and closes on a
  second click; box centred, app in front kept the keyboard, Esc saved Block, test rule removed;
  tray menu and settings shown; our menu key present, Sordum's gone. Clips: connection-box-motion
  and panel-from-tray (mp4 and gif). Edges #585B70 on all four sides.
- The right-click submenu shot failed in that run: the capture runs elevated and the elevated
  script did not set COOP_AGENT, so the window manager kept Explorer from the front and the keys
  went nowhere. "menu_helpers_left 1" was the check's own PowerShell (its command line holds the
  search text); no -swf- helper was running. Retake: test\capture-menu-125.py through
  menu-when-free-125.ps1 and elevated-menu-125.ps1 (sets COOP_AGENT), log D:\Agent Work\swf-123\menu-125.log.
- That retake ran twice (7:44 and 7:45) and both said explorer_opened false: `explorer /select`
  put the test folder in a background tab of the window already open, so no window with the
  folder's name appeared. Explorer is no longer needed: test\capture-menu2-125.py asks the shell
  for the same classic menu Explorer shows (IContextMenu on a copy of where.exe, extended verbs,
  submenu filled through IContextMenu3 with comtypes; pywin32 has no wrapper for that one).
- Read pass, no window or keys (7:55 am, owner gaming): the real menu lists "Seamless Windows
  Firewall" above Properties, and its submenu holds Block in Windows Firewall, Allow again
  (remove the block) and Open the firewall panel. capture-menu-read.json in media\live\1.2.5.
- Full pass, 7:59 to 8:01 am under the desktop input lock (released 8:01:46): menu shown from the
  script's own window and shot with the submenu open (menu-submenu.png); Block through the shell
  added "Seamless Firewall: MenuTestApp.exe" in and out; Allow again removed both; no -swf-
  helper left running, test folder deleted. capture-menu.json and capture-menu.log in media\live\1.2.5.
  1.2.5 is fully proved on the tower.
- Glass: still WARN flat over the open panel (ratio 0.06, movement 0.3). The fill is already
  0.40, the bottom of the rice range, and the backdrop is the dark panel blurred by acrylic, so
  nothing colourful is there to move. Kept as is; open item 1 below now says why.

## 1.2.7 (2026-11-26): bigger box, blur switch, allow by itself

Owner asked: box bigger by default, blue to mauve edge on hover, background blur as a setting
(on by default), and every app that asks for network access allowed by itself.

- Box size setting (Normal 1.0, Large 1.3, Extra large 1.6), Large by default. Every size in
  FwConfirmLayout and FwConfirmPaint now goes through BoxPx(v, dpi, scale); edge widths and the
  window radius stay on the live radius. Applies to the connection box and the warning boxes.
- Blurred box setting, on by default. Off gives the solid Mocha base fill.
- Hover edge: already there (FwGradEdge while the pointer is inside, surface2 at rest); proved live.
- Allow every app by itself (autoAllowConnections), off for the public, on for the owner. An app
  that starts listening gets an inbound allow rule on all profiles at once, description
  "Allowed by itself: ...", no box. The listen watcher runs when either this or the box is on.
- Owner's tower: elevated-install.ps1 now writes autoAllowConnections=1, confirmBoxGlass=1 and
  confirmBoxSize=large when missing. Old value: missing (reads as off). Rollback: set
  autoAllowConnections to 0 in HKLM\SOFTWARE\Windhawk\Engine\Mods\local@seamless-windows-firewall\Settings
  (or switch "Allow every app by itself" off in the settings window).
- Agent rule: AgentRules\global.md (Windows dialogs) says agents allow network access for apps
  they build, install or run, never ask; rendered to all 7 runtimes (backups in
  H:\System Configuration\backups\2026-11-26-agent-rules), mirrored to Foxtrot (line 93 there).
- Backups: *.bak-20261126-pre126 beside each source file and test script.
- Test PC chain: D:\Agent Work\swf-123\chain-g.sh, 7 new checks (Large width, auto-allow: no
  box, no Windows alert, rule on every network; solid box pixel; box asks again when off).

Version: built as 1.2.6, but another thread shipped its title bar menu fix as 1.2.6 at 10:41
while this one waited for the test PC (src/menu-look.cpp, already in this build). Renamed to
1.2.7 with both news entries; install base hash is now that 1.2.6 (DCED94E6...).

## Open

1. The connection box's glass reads flat over the open panel (1.2.5: movement 0.3). Its fill is
   0.40, the lowest the rice allows; going lower leaves the style. A fair check needs the box
   over a colourful backdrop rather than the dark panel.
2. The panel's own glass: the app list fills it, so the box over the panel is the measured
   floating surface. The box is modal, so the unfocused-glass check does not apply to it.

Rollback: `Set-ModState.ps1 -Id local@seamless-windows-firewall -Off`; the mod's blocks are
dynamic, so turning it off gives every app its internet back.
