# Clean icons, no plate (2026-11-24)

Owner, from a screenshot of the tray row: the wallpaper button (gradient mountains and sun, no box)
looks clean; every other icon of ours sat on a rounded blue-mauve plate with the glyph cut out in
dark ink. New standard for every app and mod: the glyph itself in the blue to mauve gradient on a
clear background. A fill stays only where the object is solid, or the app's own logo had one.

## What changed

- Rule text: rice skill style reference (App and tray icons), `docs\settings-gui-standard.md`,
  `AGENTS.md`, memory `clean-icons-no-plate`.
- `scripts\mod-consistency.py`: new `tray-plate` rule (the old plate, radius 0.26 of the icon).
  Warn during the rollout, set to fail by the install runner once every mod is clean.
- Tray icons (31 mods): plate and ink gone, glyph coverage is the alpha, glyph font 0.84 of the
  icon (was 0.62 to 0.66). Drawn marks scaled up about their centre: Launchpad dots 1.55x, dock
  mark 1.4x, cube 1.2x, styler glyph 1.3x, bin 1.3x, Halo mark 1.4x, speed test gauge radius
  0.30 to 0.40.
- Settings window (engine template, Launchpad 2.7.x): `Set_DrawMark` draws the mod's glyph alone
  in the gradient, 1.4x about the centre (taskbar icon `Set_MakeIcon` follows). About header:
  same, 1.75x. Halo owns its mark: `HaloGlyph` takes a fill brush. Taskbar's AI usage copy too.
- Kept on purpose: Clipboard's solid clipboard board (object shape), Helium's riced logo (the
  browser's own logo has a plate).

## Result (2026-11-26, 2:40 am)

- All 31 mods live and clean (`verify.py` exit 0; 6 show a newer version because the title bar
  menu thread patched them after us). Clipboard went live 11-25 11:37 pm, cube 11-26 2:23 am,
  each published by Install-StagedMod; full `publish-mods.py` after: nothing left to push.
- Why the 11-24 retries failed with an empty log: Install-StagedMod threw (exit 1), and a throw
  is not caught by Invoke-Elevated's `*>&1 | Out-File`. The wrapper
  `C:\Users\Public\clean-icons\run-one.ps1` wraps the call in try/catch and logs the message.
  Run one at a time; the runs that collided shared a log second.
- `scripts\mod-consistency.py`: `PLATE_LEVEL = "fail"` (backup `.bak-20261126-0240`). Proved:
  an old plated cube source now fails `tray-plate`; the live sources pass.
- `install-all.sh` compares hashes with CR stripped (Windhawk saves some sources with CRLF).
- Tray capture after: every icon of ours plain except Etcher (an app, not a mod). Its icon is
  drawn in `mocha-audio\src\bin\app.rs` `icon_rgba`: now bars alone, commit bd795ef. Build and
  install are left to the Etcher thread (972d9bf1), which was building at the time.

## Files

Job folder `work\2026-11-24-clean-icons\`:
- `patch.py` tray icons, `about_fix.py`, `halo_fix.py`, `aiset_fix.py`
- `restage.py <src> <out>` the whole pipeline for one source (live or another thread's staged copy)
- `check-all.py <dir>` offline syntax check, `install-all.sh` the one-at-a-time install runner
- `final\` the sources that go live, `base-hashes.txt` the live hash each was made from

## Rollback

Install-StagedMod keeps `<mod>.wh.cpp.bak-<stamp>` beside each live source and a copy in
`backups\settings-material\`. Reinstall that copy with Install-StagedMod. Manifest backup:
`docs\settings-engine.json.bak-20261124-0504`. Plate check back to warn: `PLATE_LEVEL = "warn"`.
