# Seamless Taskbar: fourth tray folder menu and edge gap (2026-11-26)

## 0.4.58 (1:44 am)
- The rightmost (fourth) footer button in the tray drawer still showed the old
  one-item "Restore all collected icons" menu. It now opens the same folder menu
  as the other three (drag here, empty, icon, colour, settings).
- Proof: `work\2026-11-26-tray-folder-menu-consistency\menu-4th.png`.

## 0.4.59 (2:22 am)
- Owner: the fourth folder's hover ring touched the drawer's outer border.
- Cause: `AlignFooterToIcons` shifts the footer row so the outer buttons centre
  on the first and last icon columns. With a 40 px button and the last icon
  column close to the panel edge, the right margin went negative and pushed the
  button onto the border (only the +-40 px guard limited it).
- Fix: the outer buttons keep at least the footer's bottom padding (4 px) as
  their side gap: `left/right >= pad.Bottom - pad.Left/Right`.
- Installed through Install-StagedMod (desktop fine 60 s, dock line-up ok).
  Published: mods ea024c7, feed 5fa9126 (first publish failed on a DNS blip,
  retry pushed).
- Rollback: restore backup `local@seamless-taskbar-20261126-0222.wh.cpp` with
  Install-StagedMod.

## Live check (after 0.4.60 from the tray-folder-gap thread, which keeps this clamp)
- Drawer opened under the desktop lock and captured (`hover-0459.png`).
- Rightmost folder icon centre x 164.5, drawer border inner edge x 184.5; with the
  32x28 buttons that puts the button's edge 4 px from the side border and about
  5 px from the bottom border. Hover ring itself was not caught (the posted mouse
  move did not trigger XAML hover); the desktop queue was 8 deep for a retry.
