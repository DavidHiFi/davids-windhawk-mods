# Windhawk 2.0.0-alpha.6 health audit (2026-10-08, thread windhawk-2a6-audit)

Full audit after the 2.0.0-alpha.6 update. Verdict: **install is healthy**; one mod bug found and
fixed; one architecture change needs a decision by the mod owners.

## The "installation corrupted" toast (user saw it after the update)

- Cause: the pre-install UI session (started 12:59:36) was alive while the installer replaced the
  UI payload (12:59:41-13:01:10). It watched its own files change under it. One-off; that session
  is gone.
- Verified clean now: `product.json` checksums are **MD5 base64 without trailing '='** (22 chars),
  not sha256 - my first two comparisons used the wrong scheme. All 6 entries match the files on
  disk (`ok=6 bad=0`).
- The styler's tool process re-applied its patches right after engine start (~13:01:09):
  `product.json` + `workbench.desktop.main.css` differ from the installer's payload, and the
  re-recorded checksums match - i.e. consistent, as the styler's ApplyFiles flow intends.
- Proof method: extracted the pristine payload from the offline installer with 7z
  (`backups\2026-10-08\windhawk-2a6-update\installer\windhawk_setup_offline.exe`) and hashed it
  against disk. `workbench.js` identical, css/product.json styler-patched. Payload dir:
  `%TEMP%\opencode\2a6-payload`.

## Engine / general health

- 112 enabled mods, all with DLLs on disk (my first "missing DLL" check was my own bug: I stripped
  the `local@` prefix before comparing filenames). 2.0 loads 1.7-compiled mod DLLs fine
  (translucent-flyouts from 5/10 runs in every process).
- explorer.exe: 79 windhawk-path modules (engine + runtime + catalog + local mods). No
  Application-log errors/warnings for windhawk/VSCodium/explorer since 13:00. Engine idles at ~1s
  total CPU. `Engine\Settings` byte-identical to the pre-install backup.
- `npp-taskdlg-textcolor`, `win32-ui-modernizer`, `center-titlebar-fork` are registered without a
  `local@` prefix (catalog-style ids) - my prefix lookups were wrong, nothing was dropped
  (119 keys before = 119 after, exact name diff empty).
- `windhawk-cli.exe` (new in 2.0) works: `mod list --json`, `mod show <id> --json`,
  `mod compile <id>`.

## Found and FIXED: visualizer settings YAML rejected by 2.0's parser

- `windhawk-cli mod show local@taskbar-audio-visualizer` failed:
  `Failed to parse settings: mapping values are not allowed in this context ... line 213`.
- Cause: viz-fix rev 4's multi-line `$description` for `followTaskbarAutoHide` contains an
  unquoted `state: ` continuation line. 1.7's lenient parser took it; 2.0's strict YAML rejects
  the whole block -> engine silently skips the mod.
- Fix: `state: while` -> `state - while` in
  `C:\ProgramData\Windhawk\ModsSource\local@taskbar-audio-visualizer.wh.cpp` (one word, meaning
  unchanged). Original backed up to
  `backups\2026-10-08\windhawk-2a6-update\local@taskbar-audio-visualizer.wh.cpp.pre-yamlfix.bak`.
- **The fork source in davids-windhawk-mods needs the same one-word fix** (not touched - claimed
  by windhawk-styler-viz work).
- Recompiled both architectures with the new toolchain: `mod compile` -> x86+x64 ok, registry now
  points at `local@taskbar-audio-visualizer_1.3.1_359131.dll`, parse check OK.
- bvm also recompiled: `local@better-volume-mixer-plus_1.1.0_971983.dll`.

## OPEN: visualizer + Better Volume Mixer Plus do not load (owner decision needed)

- Both are enabled, settings valid (visualizer now; bvm always was), freshly 2.0-compiled - and
  neither is loaded in ANY process after settings-bump reloads and a clean engine restart.
- Both configure `include: ["windhawk.exe"]` (overlay-style mods hosted in Windhawk's own process
  by design; worked under 1.7.3 - visualizer strip verified live 12:29).
- Under 2.0 the engine does not host user mods in `windhawk.exe` the way 1.7 did. Observed:
  mods get per-process injection lists (shim debug shows ~17 mods in a random new process); the
  styler still works because it spawns its own `windhawk.exe -tool-mod local@windhawk-styler`
  host (rev 28, styler-fix iterating). bvm/visualizer get no host.
- Fix path (owner's call): rehost in a real process (explorer.exe) via include change + code
  verification, or adapt to 2.0's tool-host model, or check upstream for an opt-in.
  Handoff posted to windhawk-styler-viz via coop.

## Side notes

- My engine restart test (13:33, under coop lock, no explorer restart) dropped the tray/UI; the
  `-tray-only` start restored it (verified). `windhawk.exe -exit` does NOT stop the 2.0 `-service`
  process - it survives by design; only UI/tray/tool hosts cycle.
- The UI's "Windhawk Compiler" output channel was empty at engine start (no compiles at startup);
  mod-status files in `ModsWritable\mod-status` are a 1.7 mechanism - 2.0 does not write them.
- dbwin capture works for shim/engine debug (`C:\ProgramData\Windhawk\dbwin.log`, needs its full
  75 s window before it flushes).
