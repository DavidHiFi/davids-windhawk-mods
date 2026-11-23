# Seamless Workshop 1.5.0 (2026-11-22 to 2026-11-23)

Owner's requests (thread c9a281c0, "skip the queue", fully autonomous): keep itself and every mod
up to date, set up the apps mods need, an Extras page, an Editor page, the one-button whole-setup
copy that leaves off mods out, two columns of cards, Discord status that says whether it works.

Work folder: `work/2026-11-22-workshop-150` (copy of `work/2026-11-12-seamless-hub` at 1.4.1).
Patches in order: p1 to p4 (updates, extras, presets, two columns), p5 Editor, p6 Discord note and
readme, p6b code box size, p6c self-test checks, p7 wording and self-test cleanup, p7b code box
font, p8 updates wait for a quiet moment.

## What changed

- Updates: looks at startup and every hour, installs DavidHiFi's mods and itself, keeps every
  setting and the on/off state. Setting "Install updates by themselves" (default on). The round
  waits while anything is full screen (a game, a film) or someone touched the keyboard or mouse
  in the last two minutes, then looks again every two minutes (p8). Putting a mod in reloads it,
  and the tower's rules forbid reloading a look mod while the owner is at the PC.
- Extras page (full width): installs and updates Mocha Steam and FreeDictate. Mods that need
  another app get it set up with a notice: HWiNFO (newest beta), Everything (beta with the
  owner's config), Logitech G HUB (only with a Logitech device). Scripts and list in
  `davids-windhawk-mods/deps/` (`extras.json`, `hwinfo.ps1`, `everything.ps1`,
  `everything.ini`, `ghub.ps1`, `mocha-steam.ps1`, `freedictate.ps1`). The Workshop runs a
  script only when its checksum matches the feed.
- Presets page: one "Copy DavidHiFi's configuration" button with "Are you sure?". The copy
  leaves out mods the owner has turned off.
- Editor page: start a mod or copy one, edit it in the code box (Tab = 4 spaces, Enter keeps
  the indent, Ctrl+S saves, Esc saves and leaves), check it with Windhawk's strict check,
  install it turned off, delete a draft with a 5-second "click again".
- "Show on Discord" now shows a second line: not connected, connecting, shown, or Discord's
  own refusal.
- Self-test (`--verify-dummy`) now deletes its test preset and the backup preset it made.
  Two old ones from 2026-11-14 ("Hub Verification 43914078" and its "Before" backup) were
  sent to the Recycle Bin on 2026-11-23.

## Files

| File | Old | New | Rollback |
|---|---|---|---|
| scripts/publish-mods.py | no extras in the feed | `extras` list from `deps/extras.json`, each script by commit and sha256 | `.bak-20261123-0237` |
| work/2026-11-22-workshop-150/hub.exe.manifest | none | copy of windhawk-mod.exe's manifest (test exe only) | delete the file |
| agent-tools/AgentRules/global.md | no pickup rule | "The owner's PC picks every published change up by itself" | `.bak-20261123-0400`, then `python render.py` |
| docs/settings-engine.json | Set_FitBoxes, Set_DrawGroup, Set_DrawBanner, Set_PlaceEdit followed Launchpad | owned by the Workshop (two columns, the Editor's code box) | `.bak-20261123-0408` |
| HKCU\Software\SeamlessWorkshop (test exe settings) | backup `reg-before.reg` | changed for the live test | restored 2026-11-23 3:5x am from the backup |

## Proof so far (2026-11-23)

- Live test copy, posted messages only (the desktop lock was held by another thread), recorded
  8.5 minutes:
  - Editor: new draft from the template, typing, Tab, Enter indent, Ctrl+S ("Saved.", LF only),
    Esc saves, Check passes and the Install card appears, delete arms, lapses after 5 s, and a
    quick double click sends the draft to the Recycle Bin.
  - Discord with a stand-in pipe: "Not connected", "Connecting to Discord...", "Shown on your
    Discord profile now.", back to "Not connected" when the link drops, then "Discord refused:
    Invalid Client ID". The owner's real Workshop (Show on Discord on) also reached the stand-in
    for about a minute; nothing kept.
- Found and fixed: the test exe had no manifest, so the Editor's see-through code box never
  appeared. The real host (windhawk-mod.exe) has one, so the shipped mod was never affected.
- Not clicked live: "Install it turned off" (it would install into the owner's Windhawk).

- Rebuilt with p8: strict check, settings-material, mod-consistency and settings-engine all ok.
  Self-test 101 checks, 0 failed (hotkey names and style strings survive the secret filter).
- Merged into `work/2026-11-12-seamless-hub` on 2026-11-23 about 5 am. Replaced files have
  `.bak-20261123-0458` copies; auto.inc, extras.inc and hub.exe.manifest are new.

## Test PC run of the deps scripts (2026-11-23, 5:44 to 5:54 am)

Job folder `D:\Agent Work\2026-11-23-workshop-deps\` (`out\` holds the answers and screenshots).
The first run (`out\run1\`) was cut short when thread 7bb65bc7 rewound the test PC by mistake.

- HWiNFO: an older stable (8.60) went to 8.61 on update, settings kept, sensor feed on.
- Everything: installs with DavidHiFi's settings (same checksum), service and task in place.
  Update kept it running. Remove worked but said "could not be removed": the program was
  still locked for a moment. Fixed: remove now waits for the service and program to go, then
  retries the folder delete.
- FreeDictate: install, remove refused while it is open, remove, update from the release
  before. All fine.
- Mocha Steam: says "Steam is not installed" on a PC without Steam. As meant.
- G HUB: waits for a Logitech device when run by itself. Real install about 2.5 minutes,
  remove about 1.5 minutes, but G HUB's own "Are you sure?" window stayed on screen. Fixed:
  remove closes what is left of G HUB afterwards.
- A 6:38 am retest never ran: the test PC refused its login right after the desktop came up.
  The test wrapper now waits 45 seconds and retries the copy.

## Shipped (2026-11-23, 8:15 am)

- Repo commit 188a10a: the five deps scripts (with both remove fixes), `everything.ini` and
  `extras.json`. The other thread's `seamless-download-core` files were left out on purpose.
- Installed on the tower with Install-StagedMod.ps1 (1.4.1 to 1.5.0), watched a minute, desktop
  fine. Backup: `local@seamless-workshop-20261123-0815.wh.cpp`.
- Published: mods 66a99e5, feed c0e3b1f (56 mods, app 1.5.0), release v1.5.0. Every extra in the
  feed is pinned to 66a99e5 with a matching checksum, and GitHub serves the same bytes.
- Wrong at the time: "the round waits for two quiet minutes". In 1.5.0 the round never ran at
  all (see 1.5.1 below). `Set.extrasAt` stayed unset all morning, quiet or not.

## 1.5.1 (2026-11-23, 10:05 am): the update round never ran in 1.5.0

- Cause: `kHubAutoTimer` (features.inc) had the same id as `kHubSyncTimer` (hub.cpp), 0x4858.
  WM_TIMER checks the sync timer first, so every auto tick ran `Hub_SyncTick` and
  `Hub_AutoUpdate` never ran. No mod, extra or self update could go in by itself.
- Fix: `kHubAutoTimer = 0x4859`, plus a `static_assert` that all five hub window timers
  (0x4855 arm, 0x4856 presence, 0x4857 feed, 0x4858 sync, 0x4859 auto) differ.
- Checks: Windhawk strict metadata, settings-material, mod-consistency, settings-engine all ok.
  Windhawk's own compile at install passed (with the new assert).
- Installed with Install-StagedMod.ps1 (1.5.0 to 1.5.1), watched 60 s, desktop fine. Backup
  `local@seamless-workshop-20261123-1004.wh.cpp`. Work-folder backups end in `.bak-20261123-1001`.
- Published: mods 898978f, feed 8a8c2ac (56 mods, app 1.5.1, extras pinned to 898978f, every
  checksum matches what GitHub serves), release v1.5.1.
- First real round, 10:05 am, right after the load (owner idle 4 min, Ableton open but not in
  front): `Set.extrasAt` stamped, no mod changed (the tower is the source), nothing in
  `Set.autoFailed`. HWiNFO 8.61, Everything 1.5.0.1424 and FreeDictate 3.7.4 were already
  newest. Mocha Steam is never updated by itself (no installed-version marker). G HUB
  2026.7.1011216 went in by itself (a Logitech device is plugged in and the battery tray mod
  is on): about 2 minutes, no window left, only G HUB's own virtual mouse, keyboard and bus
  devices added, no sound device.
- Every PC on 1.5.0 needs one click on the Updates page to reach 1.5.1, because 1.5.0 cannot
  update itself. The friend's PC is on 1.4.0 (before auto updates), same click.

## Still to do

- Test PC: retest of the two remove fixes (requeued 10:08 am; the 8:20 try never got a slot).
- Prove that a changed mod arrives by itself on a PC that has an older copy. The tower is the
  source, so it never has one; the friend's PC will show it once it is on 1.5.1.
