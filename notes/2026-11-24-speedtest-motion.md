# Network Speed Test Plus 2.4.0: open and close animation (2026-11-24)

Owner asks: give the speed test window an open and close animation, and make the rule stick
for every UI job. Answers: fade and slide; several speeds plus one global base speed; on by
default with a switch.

## The mod (work\2026-11-24-speedtest-motion)

- Base: installed 2.3.3 (`C:\ProgramData\Windhawk\ModsSource\local@network-speedtest-plus.wh.cpp`).
- Open: fade in plus an 8 DIP slide (from above when the window sits near the top, rising
  otherwise), 160 ms ease-out. Close: 120 ms ease-in. Both times the speed scale.
- Runs on DirectComposition (an effect group's opacity plus the visual's Y offset), so the
  compositor does the work. It can be interrupted: a re-open during a close carries on from
  where the fade is.
- DWM glass cannot fade. So the window opens over its solid frame with the glass off, then
  switches the glass on when the fade ends. The close switches the glass off first.
- New settings (Appearance page, Motion group): `flyoutAnimation` (on) and `animationSpeed`
  (`global` default, then veryQuick 0.5, quick 0.75, normal 1, relaxed 1.5, slow 2).
- Global base: `HKCU\Software\DavidHiFi\Motion`, `Enabled` DWORD, `Speed` level name or a
  DWORD percent (25 to 400). A missing key means on at Normal. Windows "Animation
  effects" off also makes it still.
- Offline compile: `compile.py` through `heavy.py` (3:23 am, 0 errors, 6 old warnings).
- Checks before install: settings-material ok, mod-consistency 0 fail 0 warn,
  settings-engine in sync.
- Installed 3:30 am with `install-240.ps1` (Install-StagedMod): registry 2.4.0, tool process
  back (pid 32164), desktop fine after the watch minute. Published: mods ac88cb4, feed
  7cd7413. Installer backup `local@network-speedtest-plus-20261124-0330.wh.cpp`.
- Proven live at 4:02 am (owner said do it now; plain `coop lock desktop`, no game in front).
  Recorded with vcap on gfxcapture monitor 3 (the left screen; the flyout opens at
  -412,181). Posts must come from an elevated script (Invoke-Elevated), the tool process is
  elevated. Escape only cancels the auto-started test; WM_CLOSE twice, 0.25 s apart, cancels
  then closes.
- Measured frame by frame (opacity fitted between the open and closed frames): open goes
  0, 0.44, 0.74, 0.9, 1.0 over about 170 ms; close 1.0, 0.92, 0.7, 0.4, 0.1, 0 over about
  150 ms. No black box, no shadow pop, no see-through frame. The small dip just after the
  open settles is the glass switching on, as designed.
- Clips: `work\2026-11-24-speedtest-motion\rec\` (real speed MP4, quarter-speed MP4 and GIF).

## The rules (backups `.bak-20261124-0314` beside each file)

- rice `references\style.md`: new Motion subsection "Open and close animation, every window
  and panel". `references\coverage.md`: the Motion column needs it too. `SKILL.md`: a new
  hard rule, and ship gate item 6 now records open and close.
- `docs\mod-style-guide.md`: Settings block bullet with the two keys.
- `docs\settings-gui-standard.md`: the settings window animates too, with a key table.
- `AgentRules\global.md`: a bullet after the visual work rule, rendered to every runtime
  (render backups in `H:\System Configuration\backups\2026-11-24-agent-rules\`), and the
  skills were synced.
- Memory: `toggleable-open-close-animation.md`.

Rollback: copy each `.bak-20261124-0314` back, run `render.py` and `sync-agents.py`. For the
mod, reinstall 2.3.3 from the installer's backup.

## Workshop global control

Done by the Seamless Dock thread (f28b8868): Seamless Workshop 1.5.4 has a new "All mods"
group on its Look page, holding motionEnabled and motionSpeed. It writes the Motion key at
startup and on every settings change. It is published (mods 1c77407, feed 1bdaf0a, release
v1.5.4). Checked here at 3:39 am: the registry shows 1.5.4, and the key reads Enabled=1,
Speed=normal. The Workshop window's own Save button has not been clicked through yet.

Original handoff, kept for the record:

Handed to the thread that owns the Workshop's code ("Fix middle dock right-click pill"):
two Look settings, motionEnabled and motionSpeed, are written to the Motion key. The
Workshop's src folder is still at 1.5.2 while the live copy is 1.5.3, so it waits for that
thread.
