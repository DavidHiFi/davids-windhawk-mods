# 2026-10-24 Windhawk settings dialog fix

Two issues in Settings > More advanced settings > Process inclusion list:

1. The inclusion textarea and its info box looked like two boxes, not one. Both had rounded corners at the seam.
2. The scrollbars had square arrow buttons and a square thumb, and the dialog scrollbar sat flush against the frame edge.

## What changed

- Installed file: `C:\Program Files\Windhawk\UI\resources\app\extensions\windhawk\webview\main.d4a0304aa029f0f1.css`
- One marked block appended to the end of that stylesheet. Source: `scripts\2026-10-24-windhawk-ui-dialog-fix.css`.
- Textarea (`engine-include`): bottom corners square. Info box under it: top corners square, pulled up 1 px so the borders overlap.
- Scrollbars inside `.ant-modal` textareas and `.ant-modal-body`: 12 px, transparent track, no arrow buttons, rounded thumb inset by a 4 px border.
- `.ant-modal-body`: 6 px right margin, so the dialog scrollbar sits inside the frame.
- Hashes: original `9DE12EA8...AEDFA`, patched `C9578835...0F6D`.
- Original saved to `H:\Windhawk Configuration\backups\2026-10-24\windhawk-ui-dialog\main.d4a0304aa029f0f1.css.orig`.

## Verification

- Audit: `scripts\2026-10-24-windhawk-ui-dialog-fix.ps1 -Audit` reads the hash and the block marker.
- Install and rollback were each run elevated and read back. Rollback restored the original hash, and reinstall restored the patched hash.
- Headless check: a plain Chromium render of the same installed stylesheet reproduces the dialog. Measured before and after:
  - Textarea bottom corners: 2 px → 0 px. Info box top corners: 2 px → 0 px.
  - Dialog scrollbar: 15 px, flush → 12 px, inset 6 px from the frame.
  - Proof: `H:\Windhawk Configuration\reports\2026-10-24-windhawk-ui-dialog\2026-10-24-windhawk-ui-dialog-proof.html` (before and after images, shown in the thread).
- Not verified in the live app. The Windhawk window was open when the change went in, so the new stylesheet applies only after the window is closed and reopened.

## Rollback

    Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-24-windhawk-ui-dialog-fix.ps1" -ArgumentList "-Rollback"

Check with `-Audit`. The block should read `False`.

## Caveats

- A Windhawk update replaces the UI folder and drops the block. Run `-Install` again after any engine or UI update. The script refuses to edit a file whose hash is not the original, so it will not patch an unknown build.
- The harness used the installed webview with a stub host (Playwright, headless Chromium 156, Python 3.13 venv under `work\2026-10-24-windhawk-ui-dialog`). It answers only the version handshake and the settings read. Scrollbar pixel sizes come from headless Chromium, so the real app may differ by a pixel or two.
- Page-level scrollbars, the main window scrollbar, and scrollbars in other Windhawk screens were left native.
