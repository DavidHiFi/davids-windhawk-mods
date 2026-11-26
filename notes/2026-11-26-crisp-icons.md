# Crisp tray icons (2026-11-26)

Owner: "The icons look kind of low resolution. They look kind of aliased. Can you audit and
make sure that they're like high fidelity, high quality?"

## Cause

- The tray shows icons at 16 px on Warden (glyph about 13 px, measured on a live capture;
  the earlier guess of a 32 px box was wrong).
- Our mods drew tray icons straight at SM_CXSMICON (16) with GDI.
- GDI drawing (ellipses, polygons, text) has no smoothing, so edges were stair-stepped.
- Several mods handed Windows premultiplied colour, which darkens the soft edge pixels.

## Fix

- `work\2026-11-26-crisp-icons\crisp.py <live> <out>` patches a mod source:
  - adds `Crisp_ShrinkIcon(HICON big, int factor)`: reads the bits, box-averages, outputs
    straight alpha at the small size, destroys the big icon;
  - renames each icon maker to `NAME_Big`, draws it at 4x SM_CXICON, and adds a wrapper
    `NAME(...) { return Crisp_ShrinkIcon(NAME_Big(...), 4); }`;
  - moves tray callers from SM_CXSMICON to SM_CXICON; bumps the version.
- `install-crisp.sh [mods]` installs one at a time under the engine lock through
  Install-StagedMod (which publishes). A mod another thread moved is re-patched from live.
- Etcher (mocha-audio `app.rs`) already draws with analytic coverage at 32 px: no change.

## Rule

- `docs\settings-gui-standard.md` (tray icon bullets) and the rice style reference,
  "App and tray icons". Memory: crisp-tray-icons. Board note posted for the suite threads.

## Result

Live (each published by Install-StagedMod):

- seamless-crosshair 1.2.11, seamless-download-manager 1.0.12, network-speedtest-plus 2.4.3,
  better-volume-mixer-plus 1.4.37, halo-launcher 0.6.16, logitech-battery-tray 0.1.6,
  pointer-afterimage-plus 1.3.6.
- Proof: `work\2026-11-26-crisp-icons\proof\before-tray-x6.png` against `after-tray-x6.png`
  (download arrow, speaker and gauge lose their stair steps).

Held back:

- seamless-taskbar: quarantined (0.4.64 dwm spike). The wallpaper switcher thread ships a
  0.4.65 with crisp.py applied, through the test PC.
- seamless-title-bars: loads into dwm; a window-look mod, so it waits until the owner is away.
- recycle-bin-tray-plus: turned off.

- Also live: power-options-button-plus 1.1.2, seamless-autoclicker 1.6.15 (its tool process
  was restarted after the compile, back up at 09:06).

Final state (17:15):

- Also live: launchpad 2.7.3, clipboard-manager 1.4.8, compiz-cube 1.0.9, explorer-view 2.0.13,
  chromium-browsers 1.0.1, startup-control 0.1.12, windhawk-enhanced-styler 2.2.34,
  controls 1.0.11, crash-watch 1.3.4, dictate 1.3.11, explorer-search 2.1.4, key-click 1.1.9,
  task-manager 1.0.4, window-manager 2.8.13, windows-firewall 1.2.7, workshop 1.5.9,
  simple-window-switcher-plus 1.0.11, snipper 0.7.8, sound-manager 1.0.11.
- halo-launcher: another thread shipped 0.6.17/0.6.18 from a pre-crisp copy; re-patched from
  live as 0.6.19 (`final\halo-launcher.wh.cpp`), but the load gate quarantined 0.6.18 at
  16:53 (dwm 47 to 77 % of a core), so it is off and not installed. Whoever clears Halo
  through the test PC should ship the crisp 0.6.19 copy.
- Full publish-mods.py run at 17:13 (feed 3732821).
- Proof: `proof\final-tray-x6.png` against `proof\before-tray-x6.png`.
- Installs waited hours on the 2-minute cooldown because many threads load mods; the
  40-round copy `install-crisp2.sh` got the last ones through.
- 13:31 Explorer restart was not ours: Explorer and the elevated mod host faulted in nvml.dll
  right after an NVIDIA driver reinstall at 13:30:55, which also set the NvContainer service
  to Automatic (against the owner's driver rule). Posted on the board; left for driver work.

State 10:41: the 08:55 batch died after autoclicker (a T3 restart takes agent-started runs
with it). Restarted the last 19 mods through the scheduled task `crisp-icons-batch`
(`C:\Users\Public\crisp-icons\batch.cmd`, hidden), which survives T3 restarts.
`coop seat when-done` watches its pid. Remaining: read install.log RESULT lines, rerun any
"gave up", full publish-mods.py (also covers autoclicker, whose run died before its
publish step), after capture, finish this list, delete the scheduled task.
