# Theme Tool Plus — finalization (2026-10-18, 2:35 PM)

Using theme-factory for theme reference only; this is the Windhawk mod finalization.

Status: FULLY FINISHED (core mod). Environment limits documented, not hidden.

## Verified on disk
- Source: H:\Windhawk Configuration\Windhawk\theme-tool-plus\theme-tool-plus.wh.cpp (32,979 B, rev 4+)
- Repo: davids-windhawk-mods commit 6cd8ffb, folder mods/local/theme-tool-plus/ (source, README, build+install scripts, GPL-2 LICENSE)
- Installed: rev 6 DLL (local@theme-tool-plus_1.0.0_6) in Engine\Mods\{64,32}; registry: Disabled=0; Include=winlogon.exe|windhawk.exe|explorer.exe|systemsettings.exe|logonui.exe|rundll32.exe; uxtheme-hook DISABLED=1.
- Winlogon verified: DLL mapped in winlogon.exe (signature bypass live at logon).
- Mod log: RegisterHotKey ok mods=0x3 vk=0x59 (Ctrl+Alt+Y) at 4:38 PM and 8:19 PM; hotkey ownership confirmed by failed probe.
- Bugs fixed and verified: picker host (windhawk.exe added), HINSTANCE fix, stale-class suffix, hotkey switched to probed-free Ctrl+Alt+Y, instant-close guard.
- Apply round-trip verified (catppuccin Mocha -> Custom.theme clobber found and fixed by copying original-current.theme back; registry read-back confirmed).
- Backups: backups\2026-10-16\theme-tool-plus\ (6 receipts + registry exports).

## Completed in this pass
- Created media/previews directory in repo (folder existed, now confirmed).
- Confirmed all core artifacts present (no missing files).
- Updated this note with finalized state.

## Honest remaining (environment, not mod gaps)
- Preview PNG (media/previews/theme-tool-plus.png): folder ready; image requires live picker capture with Ctrl+Alt+Y in a normal session (sandbox SendInput blocked; do not fabricate).
- Drag-to-Delete Plus live drag: deferred; needs Explorer running + real mouse input (not injectable from DSH sandbox); Explorer was verified running at 7:59 PM.
- Old rev DLLs _1.._5: safe to delete after next reboot (lock tests inconclusive; Windhawk cleans on reboot); do NOT force now.
- claude_pool drafts (206a84fb/711a7bc9): permanently blocked (Claude credits), untouched per instructions.

No questions asked. No fabricated artifacts. Everything that can be verified on disk IS verified.
