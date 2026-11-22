# Seamless Workshop 1.4.1 (2026-11-22)

Owner's request ("yes fix it"): the whole-setup copy dropped every keyboard shortcut and some look
settings, and a newer Windhawk refused several mods' settings. Found while installing the owner's
setup on a friend's PC (`2026-11-22-friend-windhawk-install.md`).

## What changed

- Secret filter (`src/features.inc`):
  - Key names are split into words and checked with publish-mods' word lists. A plain "key" or
    "keys" counts only as a whole last word, so hotkeyCenter, winKey and keyboardSounds stay.
  - Values: the old token prefixes stay. A long run is flagged only when it looks random (32+ hex,
    or mixed case with digits and many flips), so style strings like
    `BackgroundSizing=InnerBorderEdge` stay. Emails are left out.
- Settings fit (`Hub_FitSettings`, `Hub_FitSettingsFile`): before every `mod settings write`, the
  Workshop reads the mod's declared defaults on that PC and:
  - leaves out keys the mod no longer declares,
  - turns a number into text where the mod declares text,
  - turns 2^31 to 2^32-1 into the signed value (4294967295 is -1),
  - fills missing declared keys with the default, except inside arrays the preset already holds.
  If reading the defaults fails, the file is left alone.
- A settings write gets 30 s in the job budget instead of 15 s.
- `scripts/publish-mods.py`: registry DWORDs above 0x7FFFFFFF are published signed, so new
  presets carry -1, not 4294967295.

## Files

| File | Old | New | Rollback |
|---|---|---|---|
| work/2026-11-12-seamless-hub/src/features.inc | 1.4.0 filter | word filter, fit | `.bak-20261122-1432` |
| work/2026-11-12-seamless-hub/src/hub.cpp | 1.4.0 | fit before write, 30 s budget, tests | `.bak-20261122-1432` |
| work/2026-11-12-seamless-hub/make_mod.py | @version 1.4.0 | 1.4.1, What's new in 1.4.1 | `.bak-20261122-1432` |
| scripts/publish-mods.py | DWORD as unsigned | DWORD signed | `.bak-20261122-1443` |
| seamless-workshop CHANGELOG.md | top 1.4.0 | 1.4.1 entry (5909d4f) | git revert |
| Live mod local@seamless-workshop | 1.4.0, sha256 d6fe4f88...8c9e | 1.4.1 | reinstall the v1.4.0 release asset with Install-StagedMod.ps1 |

## Proof

- Gates on the generated file: settings-engine in sync, settings-material ok, mod-consistency
  0 fail 0 warn. publish-mods `--self-test` 7 tests OK.
- Standalone self-test build (load gate, 65 s): `{"checks":93,"failed":0}` at 7:55 pm.
- The install waited on the load gate from 3:57 pm (Ableton open), ran 8:34 to 8:38 pm under the
  engine lock (`chain-1.4.1.ps1`, `install-1.4.1.ps1`, log `install-203415.log`): registry v1.4.1
  (was v1.4.0), cli exit 0, backup `local@seamless-workshop-20261122-2034.wh.cpp`.
- Auto-publish: mods 76e0d32, feed 7095d17 (52 mods, app 1.4.1), release v1.4.1 marked Latest
  with both files and the changelog notes. Live raw feed reads app 1.4.1.
- Tool process (elevated list, 1:45 am): windhawk-mod.exe pid 46556 started 8:36 pm with
  `local@seamless-workshop_1.4.1_898144.dll`. Explorer not restarted (up since 10:18 am).
- The report lines at the end of `install-1.4.1.ps1` had quoting bugs (a filter with OR and an
  unquoted string); the install itself was not affected. Checked by hand instead.
- Not run: the whole-setup buttons (never clicked on the owner's PC).
