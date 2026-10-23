# Full Windows 11 system audit

Date: 2026-09-24  
Mode: **read-only research**. No system settings were changed.  
Thread: `syscfg-audit-20260924`

## Machine snapshot (observed)

| Area | Fact |
|------|------|
| OS | Windows 11 Pro, build **26200** (25H2), install date 2026-08-25, last boot 2026-09-24 10:30 |
| Board / BIOS | ASUS **TUF GAMING B550M-E WIFI**, AMI BIOS **4304** (2026-08-19) |
| CPU | AMD **Ryzen 7 5800X**, 8C/16T, AM4, reports 4601 MHz, virtualization firmware on |
| RAM | **2×16 GB** Corsair `CMH32GX4M2Z3600C18` @ **3600 MT/s** 1.2 V (BANK 1 + 3), ~32 GB total |
| GPU | NVIDIA **GeForce RTX 4070**, driver **616.92** (Windows 32.0.16.1692, 2026-09-04), 12 GB, WDDM, HAGS on |
| Primary display | Samsung Odyssey G5 (per prior notes: 2560×1440 @ 165 Hz, HDR/VRR/G-Sync) + two 1920×1080 @ 60 Hz |
| Storage | 6 disks, all GPT, physical Healthy: 990 PRO 1TB (C:), 990 PRO 2TB (F: Games), BX500 240GB (E:), 3×1 TB HDDs (D/H/G) |
| Network | Realtek 1 Gbps Ethernet up (driver 2026-06-03); Intel AX200 WiFi present, disconnected; Mullvad tunnel up; DNS 1.1.1.1 on Ethernet |
| Power plan | **High performance** active; min/max CPU 100% AC; ASPM **Off**; USB selective suspend **Off**; disk idle 10 min; sleep never on AC |
| VBS | Device Guard reports VBS **Running**, HVCI code integrity enforcement **on** |
| Hypervisor | Present (Hyper-V / WSL / VBS stack) |
| Defender | **WinDefend + WdFilter disabled** via `HKLM\SOFTWARE\Policies\Microsoft\Windows Defender` `DisableAntiVirus=1`, `DisableAntiSpyware=1` (intentional prior GTweak work) |
| Process load | ~294 processes; free RAM ~15 GB of 32; pagefile 23 GB on C: |
| Protected chain | Discord, Ableton Live, VB-Audio Matrix, Stream Deck — **do not touch** |

Sensitive identifiers (serials, MACs, public IPs) intentionally omitted.

## Workflow profile (how this PC is used)

Observed from installed software, running processes, and scheduled tasks:

1. **Creative / audio production** — Ableton Live 12 Suite, large VST/plugin set (FabFilter, Valhalla, Voxengo, Melda, Audiority), PreSonus, Universal Audio, Stream Deck, MIDI tooling, TeVirtualMIDI, LoopMIDI.
2. **AI / agent tooling** — T3 Code Nightly + V2, OpenCode, Claude/CoworkVM, Ollama (common Startup), FreeDictate, Wispr Flow, CLIProxyAPI.
3. **Gaming** — Steam, Epic, Battle.net, Rockstar, Ubisoft; titles include Elden Ring, RDR2, COD family, Dark Souls; RTSS + MSI Afterburner + NVIDIA App overlays; Hydra/DSX; Lossless Scaling; DLSS swappers.
4. **Self-hosted media** — Jackett, Prowlarr, qBittorrent, Stremio, FlareSolverr (+ watchdog).
5. **Developer stack** — .NET multi-version SDKs, VS 2022, VS Code, Python 3.13, Node, Go, Rust, Java, Git, WSL, Windhawk, System Informer.
6. **Remote / privacy** — Mullvad, RustDesk, Unified Remote.
7. **Workspace habit** — heavy use of `H:\System Configuration` notes/backups/scripts with dated ISO filenames; preference for reversible changes and rollback paths.

This machine is a **desktop studio + gaming + agent workstation**, not a clean OEM install. Optimization must protect latency, audio, and multi-monitor G-Sync behavior.

## Findings (facts)

### Critical / stability

1. **C: volume needs filesystem repair**  
   - `HealthStatus=Warning`, `OperationalStatus=Full Repair Needed`.  
   - System log 2026-09-24: Ntfs **55** (corruption on C:), **131** (cannot be corrected online), **98** (needs offline full CHKDSK). Boot-time check also said online scan required.  
   - Consistent with prior crash/NTFS teardown history in `CURRENT-STATUS.md`.

2. **Frequent unclean shutdowns**  
   - Kernel-Power **41** + EventLog **6008** roughly **12 times since 2026-09-13**.  
   - Matches the existing crash-recovery plan (DOCP/PBO isolation on BIOS 4304). BIOS is now 4304; RAM still reports 3600, so DOCP/XMP appears active again.

3. **NVIDIA driver events still present**  
   - **21×** `nvlddmkm` in last 7 days (mostly event **153** on 2026-09-22). No bugcheck/WHEA found in the window queried.  
   - Same class of noise documented in the 2026-09-10 borderless audit.

### Performance-relevant configuration (already good)

- High performance plan, CPU pinned 100–100% on AC, ASPM off, USB selective suspend off.  
- HAGS enabled (`HwSchMode=2`); Game DVR capture disabled; Game Mode auto on.  
- Visual effects already mostly reduced: custom VisualFX, menu delay 0, mouse accel off, taskbar animations off, MinAnimate 0.  
- SysMain **Running**; Windows Search running Manual; Prefetcher registry value **EnablePrefetcher=0** and `C:\Windows\Prefetch` empty.  
- DiagTrack, Spooler, Remote Registry, WerSvc, geolocation already disabled.  
- 990 PRO NVMe for OS; games on second NVMe.

### Medium findings

4. **Startup / always-on load is high**  
   Enabled or task-running examples: Ollama (common startup), Discord, Steam, LGHUB updater, Stream Deck, UA Connect, Ditto, AltSnap, LuaTools, FreeDictate, Unified Remote, Brave update, Wooting service, Everything, FanControl, OpenRGB, RTSS, Afterburner, ShareX, Mullvad, Hydra, Listary, Flow Launcher, WinLaunch, Windhawk, RustDesk, Ableton USB autostart, plus many Ready non-Microsoft tasks (NVIDIA update, PowerToys, System Informer, etc.).  
   Current snapshot: opencode alone ~4.3 GB working set across 3 processes; Discord ~0.9 GB; TIDAL ~1 GB; T3 Code V2 ~1.3 GB.

5. **Temp bloat on C:**  
   User Temp ≈ **8.9 GB** (ReShade, ffscan, qol-zone, claude, t3v2-stage folders dominate). SoftwareDistribution Download ≈ 0.65 GB.

6. **Free space pressure**  
   - **H: Library 13.8% free** (128 GB of 931 GB) — low.  
   - F: Games 21.9% free — OK.  
   - C: 37.6% free — OK after repair.

7. **Transparency still enabled**  
   `EnableTransparency=1` while other animation reductions are on. Slight DWM cost only; aesthetics tradeoff.

8. **Service / stack overhead (by design, not defects)**  
   Hypervisor present + VBS Running + HVCI on → measurable CPU/game overhead vs bare metal. Disabling is **not** zero-drawback (security).  
   WSL, Windhawk, System Informer, many overlay tools add background work.

9. **App crash noise**  
   Application log last 7 days: 20× .NET Runtime 1000, 12× Application Error, Claude service 7034 terminations multiple times. Not OS-root-cause by themselves.

10. **Defender fully off**  
    No third-party AV registered in SecurityCenter2. This reduces minifilter I/O (faster disk) but is a **security regression**, not a “free speed win.” Prior workspace work (`DisablingWD`) did this deliberately.

11. **Display topology**  
    Three displays, mixed 165 Hz + 60 Hz — known borderless/DWM risk factor; already mitigated by RTSS global flip model (2026-09-16). Current WMI sometimes reports 60 Hz snapshot on one adapter path; prior notes confirm primary was 165 Hz. Re-verify refresh in display settings after any driver work.

12. **Sleep/hibernate**  
    Only S3 available; hibernate/fast startup off (expected with hypervisor). Not a defect.

### Hypotheses (not proven)

- Unclean shutdowns + NTFS corruption on C: are likely **coupled** (crash → dirty volume), consistent with earlier kernel cleanup crashes.  
- `nvlddmkm` 153 bursts may be overlay/driver DPC related; may or may not relate to borderless feel.  
- Prefetch disabled + empty Prefetch folder may be intentional from Winhance/Winaero era; on NVMe it is rarely a large win either way.

## Zero-drawback recommendation list (for approval later)

Only items with **no functional downside** once the user opts in. Nothing applied yet.

| # | Action | Why pure benefit | Effort / restart |
|---|--------|------------------|------------------|
| 1 | Elevated `Repair-Volume C: -Scan` then if needed offline fix / schedule CHKDSK | Clears Full Repair Needed; prevents more corruption; no feature loss | Scan online; offline may need reboot |
| 2 | Clear safe Temp + SoftwareDistribution Download leftovers (~9 GB) | Reclaims C:; no app data loss if temp-only | Minutes, no reboot |
| 3 | Trim H: Library free-space (user-selected junk only) | Avoids low-space slowdowns on data HDD | User review of what to delete |
| 4 | Keep High performance / HAGS / GameDVR-off / flip model as-is | Already optimal for this desktop | None |
| 5 | Leave VBS, Defender policy, protected audio apps **alone** unless user explicitly wants security/perf tradeoffs | Zero-drawback rule | N/A |
| 6 | Optional: disable only clearly unused auto-starts after user reviews list (examples: Ollama if not needed every boot, Brave update task already partially managed, Battle.net already disabled) | Faster boot/login | App-by-app, reversible |
| 7 | Optional: turn off transparency effects | Tiny DWM relief | Cosmetic change |
| 8 | Optional: re-enable Prefetcher only if boot/app-launch feels slower after repairs | Restores default Windows behavior | Registry, reversible |

### Explicitly **not** recommended as “free wins”

- Disabling VBS/HVCI or hypervisor (security cost).  
- Re-enabling Defender “for speed” or leaving it off without a conscious security decision.  
- Disabling SysMain/Search without measurement (mixed results on NVMe).  
- Blind service debloat, registry cleaners, or memory-reducer tools (workspace rule + risk).  
- NVIDIA clean-driver reinstall without a rollback plan (nvlddmkm noise exists but no proof a reinstall fixes it).  
- Changing DOCP/PBO outside the agreed crash-isolation plan.

## Related prior work (do not contradict)

- Crash plan and BIOS 4304: `CURRENT-STATUS.md`  
- Borderless / flip model: `notes\2026-09-16-global-flip-model.md`, `notes\2026-09-10-borderless-latency-audit.md`  
- Visual/power snappy backups: `backups\2026-09-11-snappy\`  
- Read-only borderless audit: `scripts\Audit-Borderless.ps1`  
- Defender disable research: `reports\2026-09-18-gtweak-*`

## How to re-run this audit

```powershell
pwsh -NoProfile -File "H:\System Configuration\scripts\Invoke-SystemAudit.ps1"
```

Write JSON to `reports\` with `-OutFile`. Always read-only.

## Machine-readable companion

`reports\2026-09-24-system-audit.json`
