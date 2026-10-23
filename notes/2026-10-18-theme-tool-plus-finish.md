# Theme Tool Plus: finish record (2026-10-18)

## What changed

- **Broken metadata fixed in 13 mod sources.** The Ko-fi commit (c635373) put a
  stray backtick and a literal `n` into the metadata of 13 mods. Theme Tool Plus
  would not compile, and that commit was already on public GitHub. Fixed in
  9b7cbf7, pushed as c088e22.
- **Theme Tool Plus 1.0.1 (install revision 7).** The picker and the settings
  path now skip the active custom theme, "Unsaved Theme". Applying it rewrote
  `Custom.theme`. The skip is logged as "Skipped the unsaved custom theme".
- **Install and build scripts.** Default source path now points at the mod's own
  folder. The install script's self-elevation passes the source path through.
- **Preview image.** `media/previews/theme-tool-plus.png`, captured from the live
  picker at 5:00 PM (340 by 434 pixels). The README link now resolves.
- **Pushed.** origin/main at 374fe20 (merge of the README cleanup from PR #14).

## Verified

- Build, 1.0.1, x64 and x86: BUILD OK (temp folder).
- Install at 4:59 PM: INSTALL OK. Installed rev 7 SHA-256 matches the build.
  Registry: LibraryFileName `local@theme-tool-plus_1.0.1_7.dll`, Disabled 0.
  uxtheme-hook Disabled 1.
- Mod log at 4:59 PM: `RegisterHotKey ok mods=0x3 vk=0x59` (Ctrl+Alt+Y).
- Picker test at 5:00 PM: opened with the hotkey, captured, closed with
  WM_CLOSE. No Enter, Escape or Apply, so no theme was applied.
- Other 16 mods in the bad commit: compile for x64.

## Not done

- Revisions 1 to 5 of 1.0.0 are still in `C:\ProgramData\Windhawk\Engine\Mods`
  (32 and 64 bit). The delete was blocked by the environment's protected-path
  guard. They are not loaded and cost nothing. Rev 6 stays as the rollback copy.
- Drag-to-Delete Plus does not compile: two errors at lines 596 and 597. They
  exist before the Ko-fi commit too. Not touched.
- License: the public copy includes code derived from uxtheme-hook, which has no
  license on GitHub. The mod's own note says it has no license basis to be
  public. It is still public. Removing it is the owner's decision.
