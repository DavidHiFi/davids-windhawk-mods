# Windhawk Styler

Completed the task from T3 thread 20b498cf-6d1c-4506-aa32-11c338b4f728.
New mod `local@windhawk-styler`, version 1.0.0, revision 6, installed and enabled.
Source and portable build script are in `davids-windhawk-mods/mods/local/windhawk-styler`.

Four settings control background color, interface font, window opacity and acrylic.
Current saved settings are `#1e1e2e`, `FiraCode Nerd Font`, 50% opacity and acrylic on.
The code editor keeps its separate font setting. Transparency also affects text.

The helper targets only Windhawk's bundled VSCodium executable. It adds marked
CSS to the extension webview HTML and a file watcher to the extension JavaScript.
The watcher refreshes the main page after a settings save, except during code editing.
Users must reopen the Windhawk window once after first enabling the mod.
The native acrylic backdrop is a disabled, click-through tool window immediately
below the Windhawk window. It follows movement, sizing and minimized state.
Chromium can overwrite opacity on startup, so the helper checks and reapplies it.

Verification covered x86 and x64 builds, the public build script, live color and
font changes, acrylic on/off captures, reopening, movement, minimizing, disable/re-enable, saved settings
restoration, installed DLL hashes and JavaScript syntax. Disabling restored the
original HTML, extension JavaScript and workbench CSS hashes. The final version
does not modify workbench CSS. An earlier test did and produced an integrity
warning; restoring the original CSS removed it.

Backups are in `backups/2026-10-05/windhawk-styler`. Audit, install and rollback
are in `scripts/2026-10-05-windhawk-styler.ps1`. Receipts and captures are in
`reports/2026-10-05-windhawk-styler`. Intermediate builds are in
`work/windhawk-styler`. Publication uses its `publish` worktree so it does not
commit concurrent Shell Font Changer edits.

Evidence is scoped to Windhawk 1.7.3 on this Windows installation. An engine or
interface update can replace the patched files. Disable and re-enable the mod,
then reopen its window if that happens. No protected audio or communication app
was stopped, configured or targeted by this mod.


Published commit 75d4686 to DavidHiFi/davids-windhawk-mods main. GitHub source and preview blob hashes match the publication checkout. The shared main checkout stays at its old commit while another thread edits Shell Font Changer; the Styler files there match the published content. Future Git work should fetch and use an isolated worktree based on origin/main.
