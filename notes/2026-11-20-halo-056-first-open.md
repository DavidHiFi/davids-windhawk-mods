# Halo 0.5.6: first-open flicker fixed, warm draw tools

Plan: owner asked for the flicker on Halo's first open to die and the Windows key to be
a full replacement for Start. Work continued from the 0.5.5 install of 04:39 (which
already brought the Windows-key tap hook and, with Launchpad 2.6.4 at 04:40, the
keyboard-Start handoff to Halo).

## What changed (local@halo-launcher, 0.5.5 -> 0.5.6)

| Thing | Old | New | Rollback |
|---|---|---|---|
| First open | text formats, render target and surface were built lazily inside the first show: 10.6 s of dead air (04:57:27 toggle -> 04:57:37 shown), a second press in the meantime flashed the window open and closed | `WarmRender()` builds them when the engine reports ready, before any key press | install `backups\settings-material\local@halo-launcher-20261120-0911.wh.cpp` |
| Slow open evidence | nothing in the log said which step was slow | the first-show path traces `slow open draw: prep X ms, show+draw+flush Y ms` whenever a step passes 60 ms | same backup |

## Proof

- `settings-material.py check --staged`: ok. `mod-consistency.py check --staged`: 0 fail 0 warn.
- Installed elevated, base-hash guarded: registry v0.5.6, published to
  davids-windhawk-mods (e0e5d6b) and the Workshop feed (c533934) by the installer.
- The owner's real first open after the reload proved the fix in mod.log:
  `09:15:33.976 slow open draw: prep 16 ms, show+draw+flush 94 ms` (was 10,600 ms on 0.5.5).
- Windows-key tap registered (`Windows-key tap on` in mod.log) and in use all morning;
  Launchpad 2.6.4 hands any keyboard Start that still reaches Explorer to Halo. The
  owner's Start-menu screenshot was taken at 04:14, before 0.5.5/2.6.4 landed at 04:39/40.
- Settings GUI audit by code: six pages (General, Search, Keys, Look, Modules, About),
  Modules tab in place, About page with the Ko-fi card, glass and title-bar and tray
  options per the standard; both automated checks pass.
