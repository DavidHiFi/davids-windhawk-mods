# Windhawk Configuration workspace

NOTE (2026-10-22): finish deploy/restart/verify before reporting — never say "pending" when one step closes it.

This workspace is the home for all Windhawk work on this machine: installed mods and
their settings, taskbar and shell themes, local/forked mod development, and the
Windhawk engine itself. General Windows configuration stays in
`H:\System Configuration`; this workspace exists so the two do not blur together.

## Scope

- Windhawk engine, installed mods, mod settings, and local or forked mod development.
- `windows-11-taskbar-styler` configs and other appearance/shell mods.
- `Windhawk\` (mod sources, builds, historical backups) and
  `davids-windhawk-mods\` (public fork repo: DavidHiFi/davids-windhawk-mods).
- Records: notes in `notes\`, diagnostics and screenshots in `reports\`, reusable
  scripts in `scripts\`, backups and receipts in `backups\`, reference docs in `docs\`.
- Not here: WinLaunch Enhanced, the standalone launcher app, retired by the owner on
  2026-10-24 (uninstalled, repo private and archived; do not resume it). Its records
  stay in `H:\System Configuration` (`notes\2026-10-24-winlaunch-retired.md`). The
  launcher now lives here as the mod Fullscreen Start Plus:
  `notes\2026-10-24-fullscreen-start-plus.md`.

## Multi-agent reliability rules (owner-mandated 2026-10-16)

All autonomous agent threads follow
`H:\System Configuration\notes\2026-10-16-agent-reliability-playbook.md`.
Short form: verify the deliverable on disk before claiming or settling a task
done; only the thread that verified a completion settles it; coordinate
concurrent executors through `t3-handoff\` briefs; pace to at most 2 own model
requests on Halo's Sparks (1 when 5+ of 8 slots are busy); resume failed runs
with a "continue to completion" nudge instead of restarting; keep handoff
briefs current — the watchdog relies on them (it runs only when `t3-handoff\watch-check.py` finds a stalled, rate-limited or oversized thread); 12-hour am/pm times in
prose; no secrets in reports.

## Engine facts (this machine)

| Thing | Where |
| --- | --- |
| Install | `C:\Program Files\Windhawk\windhawk.exe` |
| Data | `C:\ProgramData\Windhawk\` (`ModsSource\`, `Engine\Mods\{64,32}\`) |
| Mod settings | `HKLM\SOFTWARE\Windhawk\Engine\Mods\<mod-id>\Settings` (structured registry values, not YAML) |
| Settings change marker | `SettingsChangeTime` REG_DWORD (unix seconds) on the mod key |
| Apply a settings change | write registry elevated and bump `SettingsChangeTime`; the mod hot-reloads on the marker |
| Engine restart | `windhawk.exe -restart` is banned on this machine: it restarts Explorer too (2026-09-28, `CURRENT-STATUS.md`). Reload per mod instead. A full engine restart happens only when the user asks for that exact action, and only with no T3 Code window live |

The mod UI's "Textual mode" is the canonical editor for taskbar-styler settings; the
registry holds the parsed structured form. The two are equivalent - a textual-mode
paste and a registry write end up in the same place.

## Safety

- Back up first: `reg export` the mod key (and copy any files) into
  `backups\<date>\...` before changing settings, and record the original values.
- Elevated writes only. This machine elevates silently for admin tasks, so verify
  every change by reading it back - never by assuming a prompt appeared.
- The active audio and communications chain is protected: do not inject mods into
  Discord, Ableton Live, VB-Audio Matrix, or Stream Deck processes, and do not stop
  or reconfigure them, without an explicit request for that exact action. One
  standing exception: translucent-flyouts deliberately styles Ableton Live's
  menus (requested 2026-09-28, live-verified). Ableton stays out of every other
  mod unless asked.
- Prefer scoped mod targets (`Include=explorer.exe`) over all-process injection.
- Do not use debloat scripts, registry cleaners, or blanket tweaks. One change at a
  time, with a measurable or visible before/after.

## Traps worth remembering (full list in `docs\traps-and-tips.md`)

- `-DWH_EDITING` builds no-op Wh_* stubs; production mods build with `WH_MOD` only.
- PowerShell 5.1 strips quotes from `-DWH_MOD_ID=L"..."`; pass the id via a
  force-included header.
- The engine keeps loaded DLLs mapped; install a new revision and point
  `LibraryFileName` at it.
- Mods do not initialize in console-subsystem processes (e.g. `powershell.exe`).
- PUA glyphs (U+E000-U+F8FF) in a BOM-less `.ps1` are misread as ANSI by PS 5.1;
  build them with `[char]0xE971` instead.
- `Start-Process -Verb RunAs` quoting traps (an array ArgumentList mangles paths
  with spaces) are in `H:\System Configuration\agent-tools\AgentRules\machine-gotchas.md`, Elevating.
- Verify visual changes by screenshot (tray, taskbar), not by assuming the write
  landed.

## Conventions

- Preview (alpha) engine updates: load the `windhawk-alpha-update` skill and run
  `scripts\windhawk-alpha-update.ps1` (`-Check`, `-Prepare`, `-Launch`, `-Rollback`). Do not
  update by hand. The engine restart waits for T3 Code to close, so ask the user to close it.
- Every mod we write or fork follows `docs\mod-style-guide.md`: no personal
  names in ids or names, plain Explore-catalog style names, a one-line
  description, a feature-bullet readme and a preview image or GIF (user,
  2026-10-04).
- Mod release checklist (user, 2026-10-24), for every current and future mod we
  write or fork; check it before any install or publish:
  1. `@author` starts with `DavidHiFi`, then every original author we built on.
  2. `@donateUrl https://ko-fi.com/DavidHiFi` is set, so the Donate button shows.
  3. Name, description, settings and readme pass the `humanizer` skill: plain
     human words, no tech jargon.
  4. The readme shows a real, clean preview (PNG or GIF) of the mod working.
  Details in `docs\mod-style-guide.md`.
- ISO dates in filenames (`2026-09-28-...`), matching the System Configuration
  conventions.
- Every applied change gets: a script with `-Audit` / `-Install` / `-Rollback` when
  practical, a registry or file backup, a receipt JSON, and a note.
- Parallel threads: follow the agent-coop rule; singleton resources are declared in
  `.agent-coop.json` (currently `windhawk-engine`, `backups`, `packages`).
- Windhawk records, including historical notes, scripts, reports, backups, and
  development checkouts, belong here. The 2026-10-04 sort moved the remaining
  Windhawk records from System Configuration; mixed system notes have copies
  in `docs\system-context\`.
  The `Windhawk\` and `davids-windhawk-mods\` folders moved here on 2026-09-28;
  directory junctions in `H:\System Configuration` keep every old absolute path
  resolving.

## Shared rules

Time format, public GitHub repos, visual-output proof and attachment failures are machine-wide rules. They live once in `H:\System Configuration\agent-tools\AgentRules\global.md` (rendered into every runtime's rules file); do not copy them back here (2026-10-24 audit: four copies had drifted apart).
