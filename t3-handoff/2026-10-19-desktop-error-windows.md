# Handoff: desktop error-window cleanup — 2026-10-19, from ~3:20 PM

**Thread:** halo-sparks-desktop-fix (Halo's Sparks, single-model-request mode)
**Mission:** identify + resolve the 2 error windows reported ~3:00 PM today, restore the
Windhawk window visible/normal, write `notes\2026-10-19-workspace-stability.md`, hardening pass.

**Singleton (windhawk-engine) intent:** READ-ONLY during diagnostics (engine log,
registry reads). I will only mutate engine state if the error windows trace to it, and
I will update this brief before doing so. No mod rebuilds/reinstalls — translucent-flyouts
0.6.51 is verified good and stays untouched (per thread 276e1786).

**Explorer budget:** at most ONE further restart, patient pattern, only if debris cannot be
cleared otherwise. `windhawk.exe -restart` is banned. Sign-out-level cleanup out of scope.

**Will not touch:** Discord, Ableton Live, VB-Audio Matrix, Stream Deck, T3 Code itself.

**Coop CLI note:** `coop.py` cannot run under this session's DSH workspace-write sandbox
(its state dir is `%LOCALAPPDATA%\agent-coop`, outside the sandbox) — this brief is the
coordination record for my run. Check `t3-handoff\` newer than this file before colliding.

**Done marker:** I will append "DONE —" with the outcome and release everything when finished.

DONE — 8:55 PM 2026-10-19. RESOLVED. Zero error windows (final proof 8:40:07 PM, delivered
as thread attachments). Window #1 (csrss 0xc0000142 box) disappeared 7:33–7:41 PM; scripted
closes were proven UIPI-blocked (probe logs saved). Window #2 = the "Windhawk error
80070005 Access is denied" family — reproduced at 8:30:15 PM by my own non-elevated
windhawk.exe relaunch (host pid 68912) and closed by elevated BM_CLICK; trigger + fix are
now hardening rules (traps-and-tips.md 23–26, playbook 13–15). Windhawk GUI captured
visible and normal at 7:58:25 PM; currently in tray (owner's state). Engine untouched
(4 + 17 pids stable since 2:29 PM); translucent-flyouts 0.6.51 verified and untouched;
no explorer restarts used; `windhawk.exe -restart` never used. Note:
`notes\2026-10-19-workspace-stability.md`; receipt: `reports\2026-10-19-workspace-stability\receipt.json`.
Open item for the next thread: the SYSTEM-in-session-1 clicker's token retarget fails
err 203 — scripts + failure points are in the report folder.
