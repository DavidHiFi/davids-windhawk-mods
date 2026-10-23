# Translucent Windows Plus — read-only plan

Using writing-plans, humanizer, antislop, antislop-copywriting. Read-only. No file edits yet.

Status (verified 18 Oct 2026 from live engine + 10-16 notes + 10-15 id-migration + style guide):
- Author line OK — "DavidHiFi, Undisputed00x" in ModsSource + registry (windhawk-cli mod list).
- Description OK — "Blur, acrylic and mica for app windows, with per-app rules and custom themes" (76 chars, no period, human, not bloated); rewritten 10-16 per notes/2026-10-16-translucent-windows-fork-audit.md.
- Credits OK — readme opens with "Based on Translucent Windows by Undisputed00x".
- Source hash 8280803C... = guard = live; task TranslucentWindowsGuard running, no suspend marker, stamp fresh.
- No phantom 1.8.2 update (local@ id fixed 10-15).

Open only: rename to Plus, since this is a real enhanced fork (PowerToys acrylic rule + general caption hook in build-local _2 DLL, 10-16 powertoys script).

Why keep the home id: the style guide (docs/mod-style-guide.md) says a fork that extends a catalog mod keeps the original name plus Plus and takes a new id. The 10-16 audit explicitly kept "Translucent Windows" because this is a fix fork tracking upstream; the Plus rename is the change that justifies the new identity. Do it with the id migration (10-15 recipe: backup, build local@translucent-windows-plus, new registry key, retire old, guard restaged).

Proposed new metadata (one line, plain):
- @name Translucent Windows Plus
- @id translucent-windows-plus
- @description Blur, acrylic and mica for windows with custom themes and per-app rules
- @author DavidHiFi, Undisputed00x (kept)
- Source: Windhawk\translucent-windows\ + new build dir; do NOT put local@ inside @id (trap, docs/traps-and-tips.md item 6).

No AI slop in this note. No em dashes. No "it is important to note", no triads, no bold-every-term. End on the verified state.
