# Restore readable shell text

The user confirmed 1.2.0 fixed clipping but reported very small text in drive Properties. Its average-width scaling shrank ordinary labels, and DirectWrite constrained every replacement to the previous font footprint even when the control had more space.

Installed Shell Font Changer 1.2.1 on 2026-10-05. GDI keeps the original requested font height. DirectWrite keeps the requested size unless text exceeds actual layout bounds. Fixed boxes still reduce overflowing strings. Single-line height checks use the rendered text height rather than adding external line spacing.

Both architecture builds pass all 67 checks. New checks prove unconstrained GDI text, roomy GDI controls and roomy DirectWrite layouts retain normal size. Existing clipping, font restoration, icon, glyph, weight, null-path and handle-leak checks pass.

The injected production probe passed its normal-size comparison against a same-height FiraCode font. The measured label width increased from 135 pixels in 1.2.0 to 150 pixels in 1.2.1. Its fixed-box and DirectWrite clipping checks pass, and 10,000 live draws keep GDI handles at 9. live-render.bmp shows normal-size text with space and fitted text in deliberately narrow boxes. This is a controlled production drawing test, not a capture of the actual drive Properties dialog.

Both installed DLL hashes and installed source match the build. Explorer, Start and ShellHost load 1.2.1. Suspended SearchHost still holds its older DLL until resumed. Font name and original six shell targets are unchanged. The temporary probe target was removed. No engine, application or computer restart occurred. Existing cached windows may need reopening.

Evidence is reports/2026-10-05-shell-font-readable. Backup is backups/2026-10-05-shell-font-readable. Run scripts/2026-10-05-shell-font-readable.ps1 -Audit for read-only state. Roll back with scripts/2026-10-05-shell-font-readable-rollback.cmd elevated after acquiring windhawk-engine. This restores 1.2.0, including its smaller text. The earlier clipping-fix rollback restores 1.1.0.

Source changes remain local. No Git commit, branch change or publication was performed while another thread worked in the shared repository.
