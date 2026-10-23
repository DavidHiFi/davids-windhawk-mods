# Deep performance dive — 2026-09-24

Thread: `syscfg-perf-deep`  
Mode: read-only research (no system changes)  
Baseline: `notes/2026-09-24-full-system-audit.md` (extends it; does not reverse RTSS flip-model or Defender posture)

---

## Observed facts

### Filesystem / power integrity (highest severity)

- `C:` still `OperationalStatus=Full Repair Needed`, `HealthStatus=Warning`.
- Ntfs events **55 / 131** continue, including **2026-09-24 11:27–11:29** (MFT corrupted file record; “cannot be corrected — run chkdsk”).
- **Kernel-Power 41** unclean reboots: **12 events since 2026-09-13** (latest 2026-09-23). Correlation with FS stress is a hypothesis, not proven.
- Elevated `chkdsk` / `fltmc` / `Get-MMAgent` denied in this session (non-admin shell).
- Disk queues on `5 C:` idle ~0; latency samples ~0.00s — FS structure damage, not current spindle/queue bottleneck.

### Memory / commit

- 31.9 GB RAM; available ~12.7 GB; **committed ~40.3 GB (~72%)**; pagefile.sys ~24 GB auto-managed on C:.
- Standby cache ~12.4 GB; Memory Compression ~1.3 GB WS.
- Heavy always-on private memory (examples): Discord ~1.0 GB WS (7 procs, ~1.75 GB group), opencode ×4, T3 Code ×9, Ableton (protected), FrostWire, Hydra, Dopamine ×5, steamwebhelper ×10, NVIDIA Overlay ×5 (~393 MB), windhawk ×12, Everything, Listary (+ 2 hook hosts), DSX, WinLaunch, Flow.Launcher.

### Prefetch / SysMain inconsistency

- `EnablePrefetcher=0`; `C:\Windows\Prefetch` file count **0**.
- **SysMain is still Running / Automatic**.
- Prefetch stays empty while Superfetch/SysMain service runs: leftover or intentional override not recorded in the baseline note. On NVMe C:, re-enabling prefetch is the usual low-risk default; keeping both “off service + off prefetch” would at least be consistent.

### Networking (subtle)

- Ethernet advanced: **`*EEE=Enabled`**, **`Green Ethernet=Enabled`**, **`Power Saving Mode=Enabled`**; AdvancedEEE already Disabled.
- Offloads (LSO/TSO/UDP/TCP checksum) enabled — fine.
- Wi-Fi: Wake-on-magic/pattern, ARP/NS offload enabled; MIMO power save Auto.
- DNS: Ethernet `1.1.1.1`/`1.0.0.1`, Mullvad iface `10.64.0.1`; display-dns record count ~6707 (cache size only; not a defect).
- `NetworkThrottlingIndex=0xa`, `SystemResponsiveness=0xa`; Games task: High scheduling, GPU priority 8, clock rate 0x2710 — stock “tuned” multimedia profile already present.

### Overlay / hook / latency stack (tiny things most people miss)

| Layer | Evidence |
|--------|-----------|
| RTSS | Hooking DX8–12, OpenGL, Vulkan, DDraw; `ForceFlipModel=1`, `ForceAllowTearing=1` (preserve); OSD on; PassiveWait=1 |
| NVIDIA Overlay | **5 processes**, ~393 MB; NVIDIA App CEF; FrameViewSDK folder present; `shadowplay-do-not-disable` Windhawk mod patches nvcontainer |
| nvcontainer | Encoder sample showed **~12% ENC** while Overlay running |
| Discord | 7 main + helpers; overlay historically on; ~1.7 GB WS |
| Steam | steamwebhelper ×10 always (library UI) |
| Windhawk | Engine service running; **~90 mods** in HKLM Mods; compiled DLLs include stylers, `timer-resolution-control`, `startup-app-delay-fix`, `d3d9-flip-model-upgrade`, `translucent-windows`, taskbar/explorer injectors; 12 `windhawk` processes |
| Listary | Service + main + HookHost32/64 (global hooks) |
| WinLaunch / Flow.Launcher / Hydra / DSX | All resident; Hydra cumulative CPU sample very high vs peers |

Idle-ish sample: `% Processor Utility` ~58%, DPCs queued/s ~12k, interrupts/s ~90k, context switches/s ~151k — elevated for a quiet desktop; consistent with many injectors/drivers, not proof of a single bad driver (no elevated DPC ranking without admin/ETW).

### DirectX / display leftovers

- One **`AppStatus=4096`** remains:  
  `F:\SteamLibrary\steamapps\common\Call of Duty Advanced Warfare\s1x.exe`  
  (Baseline reported all such blocks cleared on 2026-09-11 → this is a **regression / reappeared** entry.)
- HAGS `HwSchMode=2`; `UnsupportedMonitorModesAllowed=1`; `SwapEffectUpgradeEnable=1`; `VRROptimizeEnable=1`; `AutoHDREnable=0`.
- Game DVR / AppCapture off; Game Mode on; XboxGamingOverlay still installed (AppCapture disabled).
- `EnableTransparency=1` while `VisualFXSetting=3` and taskbar animations/shadows already off — transparency still costs DWM/composition.
- Widgets policy: **`AllowNewsAndInterests=1`**; `WidgetBoard` + `WidgetService` resident (~135 MB) and listed on GPU.
- MPO / classic `HKLM\...\Windows\Dwm\MPOEnabled` value absent (driver path may handle multi-plane separately).

### Power plan / CPU

- Active scheme: **High performance** (`8c5e7fda-…`).
- Mouse pointer precision off (`MouseSpeed=0`, thresholds 0); keyboard repeat maxed; `MenuShowDelay=0`.
- `DisablePagingExecutive=0` (drivers/pageable kernel can leave RAM under pressure); `LargeSystemCache=0` (correct for desktop).
- Cannot read some processor power GUIDs without elevation.

### Security / VBS (tradeoffs, not free wins)

- Defender: `WdFilter`/`WdNisDrv` **DISABLED**; `DisableAntiSpyware=1`; `Get-MpComputerStatus` all off — matches intentional GTweak posture; do **not** treat re-enable as zero-drawback.
- VBS: `VirtualizationBasedSecurityStatus=2`; code integrity enforcement present; `SecurityServicesRunning={0}` (HVCI/CG not reported as running services in this snapshot). Changing VBS = security tradeoff — out of “free” list.
- UAC: `EnableLUA=1`, `ConsentPromptBehaviorAdmin=0` (auto-elevate) — security posture already loosened; not a perf recommendation.

### Startup / services / tasks (perf-relevant)

**Startup working set (where process matched):** Discord ~1753 MB, Everything ~287 MB, LuaTools ~182 MB, RustDesk Tray ~52 MB, Steam, Ditto, AltSnap. Reduce Memory no longer present (user-disabled; binary still on `E:`).

**Ready non-MS scheduled (recent):**  
`CLIProxyAPI-Watchdog`, `ProwlarrDiscord-Watchdog` (other thread just silenced probes), `FlareSolverr` / `-Watchdog`, `HWiNFO`, `TidalVolume-Watchdog`, `Stream Deck`, `Open-Shell`, `Mullvad VPN`, `DSX`, `Discord Stable`, `EarTrumpet`, `Volume Controller SD Plugin`, `VB Audio Matrix Coconut Trial Bypass` (protected audio), `WindhawkRunUITask`, `soft landing`, Zen/PowerToys agents.

**Auto services of note:** SysMain, DPS, InventorySvc (Appraisal), whesvc, WlanSvc, Bonjour/mDNSResponder, Everything, FanControl.Service, Jackett, Prowlarr, MullvadVPN, RustDesk, Windhawk, GamingServices(+Net), GameInputRedistService (two instances), WpnService, WSLService, iphlpsvc.

### Devices / hardware health

- **Intel Wireless Bluetooth** — PnP **Error**, problem code **10** (cannot start).
- All six disks `Healthy` at PhysicalDisk layer; only volume **C:** Warning/Full Repair Needed.
- GPU: RTX 4070, driver **616.92**, ~36°C, ~50 W, clocks high while “idle” with Overlay/CEF/DWM multi-app GPU list (not under 3D load).

### Crash / TDR

- **nvlddmkm 4101 last 7 days: 0** (baseline 21× historically — quiet window now).
- Unclean shutdowns remain the active stability problem.

---

## Hypotheses (labeled)

1. **MFT corruption + unclean 41s** → root reliability issue; micro-opts are secondary until `chkdsk` scan/repair runs elevated.  
2. **EEE + Green Ethernet + Power Saving** on an always-on desktop → possible latency spikes / link renegotiation under load; common “invisible” NIC setting.  
3. **Prefetch disabled + empty Prefetch** → slower warm app launches; SysMain left running adds little benefit for launch paths it would feed.  
4. **Multi-overlay (RTSS + NVIDIA Overlay + Discord + Windhawk UI hooks)** → idle DPC/context-switch elevation and small frame-time noise; RTSS flip override is deliberate (keep).  
5. **AppStatus=4096 on `s1x.exe`** → Windows still treats that exe as legacy full-screen-optimized-disabled; may worsen that title’s present path vs other games.  
6. **Widgets + transparency + 5 NVIDIA Overlay processes** → pure background composition/GPU residency cost with no user-visible need unless used.  
7. **`DisablePagingExecutive=0`** → unnecessary kernel paging risk on a 32 GB machine (classic overlooked bit).

---

## Recommendations

### A. Zero / near-zero drawback (safe to propose; still requires your approval to apply)

1. **Elevated `chkdsk C: /scan` (online) then `/f` if needed** — only real fix for `Full Repair Needed`. Back up critical data first. Needs admin; may schedule offline repair (restart). **Not optional micro-opt — reliability.**
2. **Remove `AppStatus=4096` for `s1x.exe`** (same class of fix as 2026-09-11 pass) — restores windowed/opt-out path parity; reversible per-app.
3. **Ethernet: set Green Ethernet and Power Saving Mode to Disabled** (keep AdvancedEEE off as now; EEE off optional) — desktop on AC; tradeoff ≈ slightly higher NIC idle power only.
4. **Set `DisablePagingExecutive=1`** — keep kernel/drivers in RAM on 32 GB; reversible registry dword; no feature loss.
5. **Re-enable Prefetcher (`EnablePrefetcher=3` or `1`)** on NVMe — improves warm launches; leave SysMain as-is or separately decide consistency; reversible.
6. **Disable Windows Widgets** (`AllowNewsAndInterests=0`) **if you do not use the Widgets board** — frees WidgetBoard/Service + GPU context; reversible policy key. (If you use Widgets, skip.)
7. **Turn off Settings → Personalization → Transparency effects** only if you do not rely on it with `translucent-windows` — visual change; DWM slightly cheaper. **Not free if you want the look.**
8. **Windhawk hygiene (no behavior loss if done carefully):**
   - Disable **automatic updates** on `d3d9-flip-model-upgrade` (mod readme warns unload/update mid-game can crash D3D9 titles).
   - Audit which of ~90 mods are actually needed; each Explorer/taskbar styler is an inject. Turning off unused **cosmetic** stylers is a usage decision, not a silent system hack.
   - Keep `startup-app-delay-fix` and `timer-resolution-control` unless they cause a specific app issue (both are intentional, documented tools).
9. **Gaming process hygiene:** close FrostWire / Dopamine / Hydra / WinLaunch / Listary when latency-sensitive gaming (hydra and DSX showed large cumulative CPU in samples). No uninstall; just exit. Discord/Ableton/Stream Deck/VB-Matrix **stay** (protected).
10. **NVIDIA Overlay:** if you never open the in-game overlay / Instant Replay UI, disable Overlay in NVIDIA App (keep ShadowPlay capture path you care about; `shadowplay-do-not-disable` already patches DRM auto-off). Reduces 5 CEF/GPU processes. **Skip if you use the overlay.**

### B. Tradeoffs / needs your explicit call (not “free”)

| Item | Why not free |
|------|----------------|
| Re-enable Defender / remove GTweak | Security vs AV filter IO — already intentional |
| Change VBS/HVCI | Security feature |
| Disable DPS / InventorySvc / whesvc | May reduce diagnostics/appraisal; not blanket rule |
| Stop HWiNFO scheduled autostart | FanControl sensor source may break |
| Disable Bonjour/mDNSResponder | Breaks mDNS/AirPlay-style discovery |
| Disable WlanSvc | Breaks Wi-Fi when Ethernet unplugged |
| Aggressive `WaitToKill` / `AutoEndTasks` already set | Faster shutdown vs force-kill risk |
| Timer resolution block-all | Can hurt apps/games that need 0.5–1 ms |
| UAC auto-elevate already on | Security, not perf |

### C. Explicit non-actions

- Do **not** reverse `ForceFlipModel` / `ForceAllowTearing` for games.
  Superseded 2026-09-27: these moved from the RTSS `Global` profile to per-game
  profiles. In `Global` they froze non-game app windows. See
  `notes/2026-09-26-window-repaint-freeze-fix.md`.
- Do **not** debloat, cleaner-script, or blanket-disable services.  
- No BIOS/DOCP/PBO/NVIDIA reinstall in this pass (unchanged from baseline plan).

---

## What we did not finish (needs elevation or more time)

- `fltmc` / minifilter list, `Get-MMAgent`, dirty-bit query, BitLocker status, full `bcdedit` (dynamic tick / HPET) — all admin.
- Per-process DPC ranking (requires elevated Event Tracing / LatencyMon).
- Exact count of **enabled vs installed** Windhawk mods from `userprofile.json` parse (file exists; full JSON dump truncated in tool log).
- Live NIC EEE counter before/after (would need controlled change — out of scope until approved).

---

## Change log entry

| When | Change | Result |
|------|--------|--------|
| 2026-09-24 | None applied | Research only; awaiting approval |

Rollback: N/A (no mutations).

---

## Artifacts

- Machine report: `reports/2026-09-24-perf-deep.json`
- Baseline: `notes/2026-09-24-full-system-audit.md`
