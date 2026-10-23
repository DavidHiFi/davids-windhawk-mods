# Shell font clipping fix

The drive Properties buttons and quota description used fixed boxes designed for a narrower font. Shell Font Changer 1.1.0 replaced the face while retaining the original size. FiraCode Nerd Font ran beyond those boxes.

The 1.2.0 source sizes the replacement from the original average character width and line height. DrawText and themed drawing reduce it further when a fixed box is too small. Wrapped descriptions fit by measured block height. DirectWrite layouts keep the original footprint and fit the available width and height. Font measurement calls use the same initial scale as drawing. Controls retain their original HFONT and DirectWrite format objects.

Both architecture builds pass. The 64 API checks cover the button strings at four sizes, wrapped quota text, a small DirectWrite layout, null paths, icons, emoji, missing glyphs, font weights, measurement consistency, and repeated fitted drawing. Both 10,000-call handle tests pass.

Installed 1.2.0 at 2026-10-05 01:32 AWST. Both DLL hashes and the installed source match the build. FiraCode Nerd Font and the six existing shell targets are unchanged. Explorer, StartMenuExperienceHost and ShellHost loaded the new DLL without a restart. SearchHost was suspended and still held 1.1.0 at the module audit; it can load the new revision when Windows resumes it. No reboot is pending. Existing cached layouts may need their windows reopened.

The hidden injected production probe passed. Its offscreen bitmap recreates the clipped labels and description with a same-size FiraCode replacement in the left column. The right column draws through the installed hooks and shows both complete labels and the complete description inside the same boxes. DirectWrite uses FiraCode and fits an 80 by 20 pixel box. Drawing restores the original HFONT and agrees with text measurements. Ten thousand live fitted draws kept the GDI handle count at 9. The temporary probe target was removed and the original include list independently read back.

Evidence is reports/2026-10-05-shell-font-fit/test-results.txt, install.json, verify.log, live.json, and live-render.bmp. This verifies production drawing paths and the affected strings in fixed boxes. It is not a screenshot of the actual D: Properties pages or a guarantee for every possible application layout. The mod applies throughout its existing Windows shell targets. Other applications retain their existing font handling.

No global font registry, display, graphics, security, or game settings changed. No application or engine restart was performed. A coordination mistake ran the scoped installer despite a declined lock; the peer was notified. Only this mod and its separate backup directory changed. All subsequent settings mutations waited for the successfully acquired lock.

The audit, install, probe, and rollback script is scripts/2026-10-05-shell-font-fit.ps1. Rollback restores the exported mod key and previous source. Original DLLs remain installed and have backup copies.

Run scripts/2026-10-05-shell-font-fit-rollback.cmd elevated to restore 1.1.0. Acquire windhawk-engine before applying it. The PowerShell script defaults to a read-only audit. The source changes are local in davids-windhawk-mods and were not published. Other threads can commit their own paths independently.
