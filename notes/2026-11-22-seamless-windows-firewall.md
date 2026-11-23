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

## Open

1. Live captures and the glass check: queued for the screen (see above).
2. The panel's own glass: the app list fills it, so the box over the panel is the measured
   floating surface. The box is modal, so the unfocused-glass check does not apply to it.

Rollback: `Set-ModState.ps1 -Id local@seamless-windows-firewall -Off`; the mod's blocks are
dynamic, so turning it off gives every app its internet back.
