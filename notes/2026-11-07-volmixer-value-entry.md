# Seamless Volume Mixer 1.3.1: type exact compressor values

Date: 2026-11-07. Owner asked to type exact numbers instead of dragging the compressor sliders.

## Audit
- Volume percentages already had click-to-type ("Exact volume entry", on in the owner's settings).
- The compressor values (threshold, ratio, attack, release) had no text entry: slider drag and mouse wheel only.

## Change
- Clicking the value text on the right of each compressor label (for example "102 ms") opens the same popup editor the volume percentage uses.
- Accepts `-40`, `40` (read as -40 dB), `2.5`, `2.5:1`, `150 ms`. Out of range beeps and keeps the box open. Enter applies, Escape or clicking away cancels.
- Ranges: threshold -60..0 dB, ratio 1..20 (0.5 steps), attack 1..500 ms, release 10..2000 ms.
- Setting renamed "Exact value entry" and now defaults on.

## Files
- Patch: `scripts\2026-11-07-volmixer-value-entry-patch.py`
- Deploy and rollback: `scripts\2026-11-07-volmixer-value-entry-deploy.ps1 -Install|-Rollback` (elevated)
- Pre-change source: `backups\local@better-volume-mixer-plus.wh.cpp.pre-1.3.1`

## Status
- Compiled 1.3.1 (measured, windhawk-cli). Running in windhawk-mod.exe as `_1.3.1_954235.dll` (measured, process modules).
- Clicking a value in the live mixer: unverified, not driven to avoid taking the owner's cursor.
- Not pushed to the public repo (DavidHiFi/davids-windhawk-mods).
