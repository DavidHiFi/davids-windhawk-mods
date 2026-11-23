# Styler 2.2.23: Enhanced badge gone, header logo is the Mocha tile (2026-11-23)

Owner: drop the "Enhanced" text beside the Windhawk name in the top left, and swap the
white hawk logo for the app icon (blue to mauve tile, dark hawk).

- Badge removed outright: the `enhancedBadge` and `badgeText` settings and their CSS are gone.
  The title gradient uses the no-badge stops.
- Logo: with Mocha Windhawk icons on (owner has it on), `AppHeader__LogoMark` drops its mask and
  shows the 96 px frame of the Mocha icon the mod already carries (`kMochaLogoPng`, a data URL).
  Off: the stock logo with the gradient, as before.
- Built on live 2.2.22 with `work\2026-11-23-styler-header-logo\make.py`, installed with
  Install-StagedMod as 2.2.23, backup `local@windhawk-enhanced-styler-20261123-0453.wh.cpp`.
  Desktop watched 60 s after load: fine. Published: mods e617c91, workshop feed c2ab1c5.
- First install try failed before staging: the 5.1 child from the load gate lost Get-FileHash.
  install.ps1 now resets PSModulePath and imports the Utility module first.
- Rollback: reinstall that backup with Install-StagedMod.
- Live check: `verify.py` in the work folder (needs `coop lock desktop`); results below.

## 2.2.31 and 2.2.32: the logo was blank in 2.2.23

(Other threads shipped 2.2.24 to 2.2.30 meanwhile; the fix landed as 2.2.31 on top of them.)

- Live check of 2.2.23: badge gone (`::after` content none, header text "Windhawk"), but the logo
  showed nothing. Windhawk's page security policy refuses `data:` and `blob:` images (probe.py
  caught the securitypolicyviolation), so no embedded picture can ever show in the Windhawk UI.
- Fix: no image at all. The page script reads the stock logo's computed hawk mask (absolute url),
  puts it in `--wh-logo-mask` and adds `html.wh-logo-tile`. CSS then paints the LogoMark span
  with the blue to mauve gradient, rounds it, and masks it with the hawk XOR a full square, so
  the hawk is cut out and the dark header shows through: the Mocha tile look. Until the script
  finds the mask, the stock gradient hawk shows. `kMochaLogoPng` is removed.
- 2.2.31 (`make2.py`) used that cut-out. Live check: the tile showed, but the Windhawk page is
  see-through, so the hole showed whatever sat behind the window (white in the capture).
- 2.2.32 (`make3.py`, current): the span is the gradient tile with no mask, and its `::after`
  (inset 17%) is Crust #11111b masked by `--wh-logo-mask`: a real dark hawk. Installed with
  Install-StagedMod, desktop fine after 60 s, published mods ecc034c, feed 2659b73.
- Live proof 2026-11-23: `header.png` in the work folder, badge `::after` none, text "Windhawk".
  The 2.2.32 check logged repeated focus grabs by the opening Windhawk window; verify.py handed
  the front back each time and the owner's window was in front at the end (owner idle 43 min).
- Install path: the load gate stayed full for over two hours; a single mod install goes straight
  through `install.ps1` (Install-StagedMod has its own desktop checks), as other threads do.
- Rollback: reinstall the backup Install-StagedMod made before 2.2.32, or set Mocha icons off.
