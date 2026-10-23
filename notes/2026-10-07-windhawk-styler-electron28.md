# 2026-10-07 — Windhawk Styler 1.5.0 (rev 15): Electron 28 runtime, real native frame with system acrylic

Supersedes the 1.3.1/1.4.0 approaches (page-transparency + DWM attribute
poking + caption-color games + the strip veil popup as the only fix). Those
kept hitting the same wall: a real DWM caption is non-client area no page can
paint, and every workaround left some seam, artifact or dead interaction
behind. The user's verdict on 1.4.0: corner artifact blocks in all four
corners, Alt-drag + right-click maximize broken, and still no proper
transparency.

## What ships

The UI runs on a locally prepared **Electron 28.3.3 runtime** (Chrome 120).
Electron 28 has `backgroundMaterial: "acrylic"`, which hands the window to
the DWM system backdrop natively, and with `frame: true` the caption is
Windows' own drawn over the same glass. No transparency games, no overlays,
no UI-process injection at all (the mod returns FALSE in VSCodium).

- Inject for native+blur: `transparent:!1, backgroundColor:"#00000000",
  frame:!0, backgroundMaterial:"acrylic"` plus, after the BrowserWindow
  constructor, `setBackgroundMaterial("acrylic")` and `setMaximizable(!0)`
  (Chromium setup drops the maximize style on acrylic windows).
- Custom mode keeps the old transparent frameless path.
- The tool keeps: file patching, settings.json, watcher, cleanup, and the
  Worker (whose Effect() leaves the caption at its default in native+blur
  mode — on Electron 28 DWM keeps NC rendering enabled, so an unset caption
  shows the glass; a solid color sat as a dark band).

## Rev 15: the native-mode workbench CSS

The modern runtime needs three rules the Electron 19 line never did:

1. `.monaco-workbench .part.titlebar{display:none!important}` — the app's
   renderer hide path for the custom titlebar part does not fire on Electron
   28. Without this the menubar (File/Edit/View…) renders under the caption
   AND the layout reserves its 30px, spilling a flat gray band at the window
   bottom.
2. `html{background:rgba(bg,opacity)!important}` — the same reserved 30px
   means the page's webview guest ends 30px above the client; the host canvas
   is transparent, so raw acrylic (unveiled, darker) showed there. Painting
   the host canvas with the veil makes the whole bottom uniform.
3. `.monaco-workbench .part.editor .editor-group-container{background:transparent!important}`
   with FULL specificity — the app's own rule paints that container opaque
   (it showed as the gray band before this; identified with a color-ladder
   probe: body #010101, html #020202, workbench #030303 … the band's shade
   named the exact element).

The tool's strip veil popup (ported from 1.4.0) tints the caption strip with
the same rgba veil: strip = body, one frosted sheet.

## Fixture → live install

Tests ran on an isolated copy (`C:\Program Files\Windhawk\UI-styler-test\`,
data in `C:\Users\localuser\WindhawkStylerTest\`). The runtime was assembled
from the upstream Electron 28.3.3 binaries; the native addons (spdlog,
windows-mutex, windows-process-tree, node-pty, fs-ext) were rebuilt against
Electron's node ABI 119. `Runtime.ps1 -Install` copies 79 runtime files into
the live UI after backing each original up with a hash manifest, then
`Install.ps1` installs the mod DLLs, points LibraryFileName, restores
settings, enables, bumps, and starts tool + UI.

## Verification (all same-moment, on the live window)

- Style `0x16CF0000` (real frame, maximize, snap), backdrop 3.
- Corner crops TL/TR/BL/BR: clean tinted acrylic, rounded corners, no blocks.
- Bottom rows uniform (37,38,53); strip (42,40,52) vs body (33,34,48) — the
  difference is the wallpaper's vertical gradient sampled by live acrylic.
- `modern-drag.log` rev 13 and rev 15 runs: plain Alt-drag moves; Alt-drag +
  right-click maximizes to a REAL OS zoom (-8,42)-(2568,1448); press+rclick
  does not (matches the fixture baseline).
- Custom mode flip: frameless `0x14030000`, HTML titlebar, transparent
  inject; flip back restores the acrylic inject. UI restarts cleanly.

## Traps learned this round

- Runtime.ps1's manifest pins NewHash from the first run; rebuilding the
  fixture then rerunning throws 'Prepared runtime has changed' (this killed
  the first rev-13 attempt — nothing was copied, originals intact).
- The Invoke-Elevated wrapper can run a DIFFERENT queued payload if invoked
  right after a crash/restart; always confirm the payload's own log exists.
- CIM CommandLine is null for elevated processes from a non-elevated shell —
  a "tool not running" conclusion from a cmdline filter is unreliable; check
  elevated or by pid.
- Minified single-line CSS: removing appended blocks needs a `(?s)` regex —
  plain `.*?` stops at the first newline and silently matches nothing.
- Manual CSS edits break product.json's recorded checksum; the integrity
  service shows "Your Windhawk installation appears to be corrupt" until
  ApplyFiles re-records and the window restarts (bump + one window restart).
- The editor group container's gray fill + the 30px reserved titlebar slot
  are the reason v13's NCCALCSIZE trick existed on Electron 19; on Electron
  28 the CSS rules above replace it.

## Publication

Fork main still has 1.4.0 (`28ef40a`). The runtime swap is machine-local;
publishing 1.5.0 needs a decision on shipping the Electron 28 dependency
(bundle, download step, or document-only). Not decided this run.

## Rollback

`Runtime.ps1 -Rollback` restores all 79 runtime files from the manifest;
`Install.ps1 -Rollback` restores LibraryFileName/settings from
`backups\2026-10-07-native-v15\mod.reg` + `original.json`.
