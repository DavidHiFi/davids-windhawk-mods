# Simple Window Switcher Plus: saved settings restored (2026-10-18)

## What happened

- At 1:07 AM the mod's saved settings held one value: `Accessibility.centerCursor`.
  The other 111 were gone, so the switcher fell back to defaults and looked different.
  (Measured: value count. Inferred: the 1:07 AM settings write removed the rest.)
- The 11 October full registry backup holds 112 values for this mod. It was on revision 3,
  with the Vista renderer and the Flip 3D style.

## What was done

- 5:16 AM: saved the broken key to
  `backups\2026-10-18-swsp-settings-before-off\mod-key-before-off.reg`, then set
  `Accessibility.centerCursor` to 0 (cursor option off).
- 5:17 AM: imported the 112 values from the 11 October backup
  (`backups\2026-10-18-swsp-settings-restore\settings-from-2026-10-11.reg`) and bumped
  `SettingsChangeTime` so Windhawk reloads the mod.
- Read back: all 112 values match the 11 October backup. `centerCursor` is 0.
  `Disabled` is 0. The library is still revision 5, which has the cursor code. That code
  does nothing while the option is off.

## Not verified

- The look itself. An Alt+Tab capture at 5:22 AM did not show the switcher
  (`reports\2026-10-18-swsp-restore\alt-tab-after-restore.png`). The user needs to press
  Alt+Tab once and compare.

## If the look still differs

- Other mods that changed today and touch explorer: translucent-windows (hooks system
  colors, `Include=*`), translucent-flyouts 0.6.36, windhawk-styler 2.0.58.
- Any settings changed between 11 October and 1:07 AM today were lost in the wipe.
  The 11 October copy is the newest full copy found.

## Rollback

- Re-import `backups\2026-10-18-swsp-settings-before-off\mod-key-before-off.reg` with the
  elevated wrapper. This puts back the broken state, so only do it on purpose.
