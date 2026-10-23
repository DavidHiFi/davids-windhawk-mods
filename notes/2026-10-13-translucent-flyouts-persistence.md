# Translucent Flyouts 0.6.33: persistence check and publish (2026-10-13, thread 72f9bcc6)

Took over the finalize task from capuchin-flyout. Its T3 thread was gone and its 0.6.33
install (receipt 3:49 PM) had no verification or final note. Its claimed source, scripts
and reports were not edited here.

## Live state (measured)

- Mod: local@translucent-flyouts, LibraryFileName local@translucent-flyouts_0.6.33_1.dll, Version 0.6.33, Disabled 0.
- ModsSource, canonical source and build-0.6.33 source: identical SHA-256 (FC0411CE...).
- advancedFunctions.processBlockList: absent (empty), per the owner's 2026-10-13 reversal.

## Explorer restart

- Before: explorer pid 34000 (started 3:49:52 PM, loaded 0.6.33).
- Restart at 4:01:55 PM: new pid 13488 loaded local@translucent-flyouts_0.6.33_1.dll.
- Desktop dark main menu, before and after the restart: body #2D2E41 / #202131 / #292A3B,
  interior #262636, outline #89B4FA on all four edges.
- Bright main menu after the restart (1000,560): outline #89B4FA on all four edges, body
  #2F3043 / #222233, interior #353142. The first attempt at this point popped no menu;
  the second one did.
- Dopamine title-bar menu: before and after the restart, one #89B4FA outline on all four
  edges, body #212131 / #202132.
- One dark submenu sample at the right margin moved from #252435 to #383446 across the
  restart. The outline and the body stayed the same; the blur samples what is behind the
  menu, which changes.

## Publish

- Public repo main was still on 0.6.16 (PR #10). No translucent-flyouts release existed;
  the only release containing the mod was the 2026-09-28 setup snapshot (v1.1.0).
- PR #11 (branch translucent-flyouts-0.6.33, squash-merged as 0241d0a) updates the source,
  the README preview (media/previews/translucent-flyouts.png, captured from the live
  0.6.33 after the restart) and the manifest version (0.6.33).
- Release: translucent-flyouts-v0.6.33 ("Translucent Flyouts 0.6.33"), target 0241d0a.
- The published source is the canonical file with its UTF-8 BOM removed. The compiled code
  is unchanged.

## Descriptions

Checked the settings  strings and the @description against the humanizer
patterns. No tells: no contrasts, closers, dashes or staged openers. The triad in the
@description (Mica, acrylic, blur; menus, dropdowns, tooltips) names real distinct items.
No text was changed.

## Rollback

scripts\2026-10-13-translucent-flyouts-0.6.32.ps1 -Rollback (via Invoke-Elevated), then
restart Explorer. The 0.6.32 DLL and source are still in ProgramData and the backups folder.

## Leftovers

- Local checkout davids-windhawk-mods is on main but stale (its translucent header says
  0.6.6) and has uncommitted edits to taskbar-audio-visualizer that are not this thread's.
  Left untouched.
- The 0.6.33 final note from capuchin-flyout was never written.