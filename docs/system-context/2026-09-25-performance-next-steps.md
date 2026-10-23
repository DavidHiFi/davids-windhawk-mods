# Performance audit: next steps

Update later on 2026-09-25: steps 1 and 2 are done. C: has one broken file record, and the spot fix is queued for the next restart. User data is copied to D:. The same work found a Ryzen Master CPU and RAM overclock and an Afterburner GPU overclock running, which changes step 3. The 2026-09-24 deep-dive's "0 nvlddmkm events" was wrong: there were 28 since 2026-09-11. See `2026-09-25-c-volume-repair.md`.

Date: 2026-09-25. This is a read-only follow-up to `2026-09-24-full-system-audit.md` and `2026-09-24-perf-deep-dive.md`. No system settings or files outside this workspace were changed.

## Current evidence

- `Get-Volume C` still reports `HealthStatus=Warning` and `OperationalStatus=Full Repair Needed`. About 382 GB of 998 GB remains free, so lack of free space is not the apparent cause.
- The System log has Ntfs event 131 at 2026-09-24 11:27:53 saying C: cannot be corrected and requests `chkdsk`. Ntfs event 55 at 11:27:55 reports a corrupted Master File Table record on C:. Later event 98 reports a shadow copy needing a full offline check. The last boot was 2026-09-24 10:30.
- Kernel-Power 41 and EventLog 6008 occurred together on September 20, 22, and 23. They establish unclean shutdowns, not their cause.
- Both RAM modules still report 3600 MT/s. The earlier crash-isolation plan calls for testing at stock memory and PBO settings; the current firmware settings have not been independently verified. BIOS 4304 is already installed.
- `fsutil dirty query C:` returned Access denied in this non-elevated session. No repair, scan, reboot, or firmware change was performed.

## Recommended order

1. Confirm a current, restorable backup of irreplaceable data on C:. The workspace `backups` directory contains configuration backups, not proof of a full data backup. Avoid major cleanup or tuning until this is settled.
2. In an elevated session, run `chkdsk C: /scan` and save its output. This can clarify the required repair, but the existing event 131 and `Full Repair Needed` status already make an offline repair likely. If Windows requests it, schedule `chkdsk C: /f` for a reboot at a time the owner chooses. A repair can take time and may recover or remove damaged file records, so backup and a controlled restart matter. Recheck `Get-Volume C` and Ntfs events afterward.
3. If unclean shutdowns continue, follow the existing crash-isolation plan: test stock RAM/DOCP and PBO settings one variable at a time, with the owner handling firmware changes. If crashes persist at stock, run a memory diagnostic and inspect its result. A clean memory result does not rule out intermittent instability.
4. After the file system is healthy and stability is understood, measure a specific slow task or game before and after one reversible change. Keep the RTSS flip-model setup and protected audio chain intact.

## Correction to the prior deep-dive recommendations

The earlier note called several changes "zero / near-zero drawback" without evidence of a measured benefit. They are candidates for controlled tests, not a set to apply together:

- `DisablePagingExecutive=1` can increase RAM pressure and has no demonstrated benefit here. Do not apply it as a routine speed tweak.
- Re-enabling Prefetch may improve some launches and may increase background disk activity. Measure the workload first.
- Disabling Ethernet energy-saving options can change power use and may briefly interrupt the link. Test only if link or latency symptoms point there.
- Widgets, NVIDIA Overlay, Windhawk mods, transparency, and startup apps may serve active workflows. Disable only a confirmed unused component, with a before-and-after measurement.
- The `s1x.exe` graphics entry may have reappeared, but changing it is game-specific and needs an actual presentation or latency test. Do not include it in a blanket system optimization.

No Windows tuning change can honestly be guaranteed to have zero possible drawback on this machine. Filesystem repair and crash diagnosis take priority over speculative micro-optimizations.
