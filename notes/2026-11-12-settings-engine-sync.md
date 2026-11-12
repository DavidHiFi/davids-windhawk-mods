# Settings engine: every mod synced to the Launchpad template (2026-11-12 to 11-13)

Thread bd0ca06f. Owner asks: the native title bar switch must work, boxes and dropdowns must fit
their text, every scrollbar uses the blue to mauve gradient, and every mod (present and future)
must follow every template edit.

## What changed

- Template: Seamless Launchpad 2.4.9 (installed 3:28 pm 2026-11-12). `Set_ApplyFrame` applies the
  native title bar and glass on first open, on Save and on any outside reload, so no reopen is needed.
  Dropdowns and text boxes size to their longest option, long lists scroll, and every scrollbar
  thumb is the blue to mauve gradient.
- `scripts\settings-engine.py`
  - three-way merge of each owned function against `docs\settings-engine-base\`;
  - `add --staged <file>` for a mod that is not installed yet;
  - the manifest write retries ten times (H: briefly refused it with Errno 22).
- `scripts\Install-StagedMod.ps1`: exit 4 (refuses) when the staged mod is behind the template.
  Backup: `scripts\Install-StagedMod.ps1.bak-20261112-1515`.
- `scripts\settings-material.py`: the glass check takes the block nearest Set_ApplyFrame's
  `else if (wasGlass)`, so a mod's own earlier `if (glass)` code no longer gives a false "OFF"
  (Dictate). `stage` is gone; it points at `settings-engine.py sync`.
  Backup: `scripts\settings-material.py.bak-20261112-1528`.
- `docs\settings-engine.json`: Crosshair added; every installed mod rebaselined after install.
- `docs\settings-gui-standard.md`: the stale `stage` line now names `settings-engine.py sync`.
  Backup: `docs\settings-gui-standard.md.bak-20261113-0044`.

## Mods synced and installed by this thread

Colour Picker 1.1.10, Clipboard 1.3.10, Sound Manager 1.0.2, Autoclicker 1.6.5, Media Player
1.10.14, AI Usage 1.2.3. Other threads synced their own: Dictate 1.2.2, Crash Watch 1.2.5,
Key Click 1.1.0, Crosshair 1.0.1, Snipper, Explorer Search, Seamless Taskbar.
Previous sources and registry keys: `backups\settings-material\<id>-<stamp>.wh.cpp` and `-key-<stamp>.reg`.
Clipboard, Sound Manager and Autoclicker stopped after their rebuild and were restarted with
`scripts\2026-11-10-tool-mod-restart.ps1`.

Checks after install: `settings-engine.py check` in sync for all 13 engine mods;
`settings-material.py check` ok for all 14 (Launchpad included).

## Rollback

- A mod: copy its `backups\settings-material\<id>-<stamp>.wh.cpp` back over
  `C:\ProgramData\Windhawk\ModsSource\<id>.wh.cpp` and install it with `Install-StagedMod.ps1`.
- A script: copy its `.bak-<stamp>` file back.
- The live proof flips two Launchpad settings and puts them back; the full key before it is in
  `work\2026-11-12-engine-sync\launchpad-settings-before-proof.reg` (import elevated).

## Slip

12:41 am 2026-11-13: the desktop lock was piped (`| tail -1 && ...`), so a failed lock (held by
2475bbcb) did not stop the live proof. It opened the Launchpad settings window, took focus,
recorded 4 s and closed it. No setting changed (checked after). The proof now runs only when the
lock's own exit code is 0. Memory: desktop-lock-gate-exit-code.

## Live proof (12:45 am 2026-11-13, under the desktop lock, owner idle)

Take `work\2026-11-12-engine-sync\proof-004532\` (monitor recording, `share.mp4`, `proof.gif`,
stills `0-` to `6-`). Settings flipped from outside with `flip-setting.ps1`, as Save would:

- native title bar 1 -> 0: the built-in Mocha title bar and its buttons appear at once; 0 -> 1:
  the Windows title bar returns. No reopen.
- glass 1 -> 0: the page turns solid crust; 0 -> 1: the acrylic is back.
- Windows key dropdown opened by a posted click: all three options shown in full, the chosen one
  ticked. Box text "Run the program below" fits.
- Both switches ended on 1 (checked in the registry afterwards).
- Not shown live yet: the gradient scrollbar. The Keys page is too short to scroll, and a second
  take on the Look page (`live-proof-scroll.py`) waited for the desktop lock, held by another
  thread, and never ran. A retry at 5:49 am got the lock but the owner was at the PC (2 s idle), so it
  opened nothing. Code check instead: all 13 engine mods use `Set_ThumbFill` for every thumb, and none
  paints a grey thumb.

Manifest: on request from the Dictate and Crosshair threads, `own` was added for Dictate
Set_DrawLinkRow and Crosshair Set_Parts and Set_DrawRow (backup `docs\settings-engine.json.bak-*`
of 2026-11-13). Media Player and AI Usage are no longer installed (merged into Seamless Taskbar);
their manifest entries stay until that thread removes them.
