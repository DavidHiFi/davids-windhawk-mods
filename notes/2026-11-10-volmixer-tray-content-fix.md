# 2026-11-10 — Volume mixer: invisible content + duplicate/dead tray icon

Mod: `local@better-volume-mixer-plus` (Seamless Volume Mixer), tool mod.
Symptoms reported by owner: (1) duplicate mixer icon in the expanded tray
overlay, (2) clicking the pinned tray icon does nothing, (3) the mixer popup
opens invisible (dark panel only).

## Root causes

1. **Invisible content — wrong renderer value.** The mod accepts only
   `renderer=gpu|gdi` (source line ~1276 compares against `L"gdi"`). A value of
   `legacy` is invalid and silently maps to `gpu`. The GPU path's
   DirectComposition content surface never presents anything (chrome draws,
   content does not — a separate, still-unfixed DComp bug, see below), so the
   popup was empty. Verified by burst captures: on `gdi` the full popup renders
   (header, master row, 20 app rows, pagination).
2. **Settings did not hot-apply to the running tool host.** Raw registry writes
   + `SettingsChangeTime` bumps, and even `windhawk-cli mod settings set`, did
   not reach the running host (style stayed NOREDIRECTIONBITMAP). A tool-mod
   restart is required after a renderer change. The valid values only took
   effect on restart because the restart happened while the value was still the
   invalid `legacy`; after `renderer=gdi` through the CLI, a fresh host read it
   correctly.
3. **Duplicate/dead tray icon — zombie GUID identity.** A killed tool host left
   its GUID tray identity registered. The new session's `NIM_ADD` with the same
   GUID failed, the code fell back to a window/ID icon (duplicate, live, in the
   overflow) and the dead zombie kept the pinned spot — dead click.

## Fixes

- Settings: `renderer=gdi` via `windhawk-cli.exe mod settings set` (elevated).
  This is a supported setting ("How the mixer draws"); owner keeps it.
- Code (1.4.4, commit `3df2aa5` in davids-windhawk-mods):
  `AddTrayIcon` now deletes a stale GUID identity (`NIM_DELETE` with
  `NIF_GUID`) and retries the GUID add before falling back to the window/ID
  identity; `RemoveTrayIcon` deletes both identities. Explorer restores the
  pin by GUID, and the probe confirmed the icon back at the owner's pinned
  spot (2265,10) with no duplicate.
- DLL: `local@better-volume-mixer-plus_1.4.4_322907.dll` compiled by the
  engine; `LibraryFileName` switched to it (the CLI was killed at the 15 s
  timeout but the engine finished the build; the pointer was set manually).

## Verification

- `ex=0x80088` (WS_EX_LAYERED, no NOREDIRECTIONBITMAP) → GDI path armed.
- `work\2026-11-10-volmixer-tray-fix\burst-01.png` (1.4.4): full popup content.
- `tray-probe.exe`: GUID identity S_OK at the pinned rect; plain identity not
  found (no duplicate).
- PID 15544 after the sanctioned restart script.

## Known issue left open

The GPU/DirectComposition renderer draws chrome (background + border ring) but
its content surface never presents (all captures show through). The mod stays
on `renderer=gdi`, which is fully functional. If the GPU path is ever wanted,
debug `GpuUploadContent`/skip-compare in `UpdateGpuFrame` first.

## Rollback

- Backups: `backups\2026-11-10\volmixer-tray-fix\` (reg export + 1.4.3 source).
- Mod key: `HKLM\SOFTWARE\Windhawk\Engine\Mods\local@better-volume-mixer-plus`
  (import the reg export), point `LibraryFileName` back to
  `local@better-volume-mixer-plus_1.4.3_979435.dll`, restart the tool mod.
- Repo: fork repo commit `3df2aa5` (local only, not pushed).

## 2026-11-10 8:40 pm — black menu bodies + resting pill borders (owner report)

Two follow-ups on the same mod, plus the recycle-bin mod's menu:

1. **Device-picker menu body fully black** (and the same for the recycle-bin
   tray menu): the SeamlessMenuSkin paints menu parts black expecting the
   acrylic accent (applied by `ApplyEffects` on the menu window) to composite
   over it. `ApplyEffects` never reached the menu window — the create-event
   hook (`WINEVENT_INCONTEXT`) did not deliver in the tool host. Fix: a
   `WH_CBT` hook installed around every `TrackPopupMenu(Ex)` call applies the
   skin at `HCBT_CREATEWND` for `#32768` windows, before the first paint.
   `OnMenuCreated` is now idempotent (prop guard) because both paths can reach
   it. Applied to **both** `local@better-volume-mixer-plus` (1.4.5) and
   `local@recycle-bin-tray-plus` (1.0.4).
2. **Previous/Next pagination pills had no resting border**: `DrawStateSurface`
   gained an optional `resting` parameter that draws a grey edge
   (#585b70 at 0.55 alpha) under the gradient hover stroke; only the
   pagination pills pass it (`0.55f`), so rows, sliders and other controls are
   untouched.

Verification (probes, no cursor moves): the device menu body samples
#191925/#242437/#343642 (was #000000), the bin menu body samples
#3A3B4B/#363752/#393A56, and the 4x pill zoom shows both grey resting edges.
Hover state of the pills was not captured (would need the owner's cursor);
the hover path is code-unchanged (gradient fades in over the grey edge).

DLLs: `local@better-volume-mixer-plus_1.4.5_125480.dll`,
`local@recycle-bin-tray-plus_1.0.4_961128.dll`. Backups:
`backups\2026-11-10\menu-skin-fix\` (both reg exports + prior sources).
Repo: commit `6445144` (local only, not pushed).
