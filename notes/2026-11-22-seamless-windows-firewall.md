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

## Open

1. Live captures and the glass check: queued for the screen (see above).
2. The panel's own glass: the app list fills it, so the box over the panel is the measured
   floating surface. The box is modal, so the unfocused-glass check does not apply to it.

Rollback: `Set-ModState.ps1 -Id local@seamless-windows-firewall -Off`; the mod's blocks are
dynamic, so turning it off gives every app its internet back.
