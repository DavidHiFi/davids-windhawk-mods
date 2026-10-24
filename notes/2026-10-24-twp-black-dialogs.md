# 2026-10-24 Black Explorer dialogs and clipped dialog text

## 1. Translucent Windows Plus 1.8.4: Properties dialogs were solid black

Cause (measured with a file-logging debug build, `work\2026-10-24-twp-black-dialogs\`):
the Explorer-only reapply timer (`DelayedReapplyTimerProc`) turned the blur off
with `DisableAccentBlurBehind`, then called `NewWindowShown`. That call found the
dialog ineligible, because its ex-style had gained 0x000C0000 by then. The blur was
never turned back on, so the window showed the black transparency key.

Fix: the timer waits (re-arms) while `!IsWindowEligible(hWnd)`, the same way it
already waits for `!IsWindowVisible`. The source has a forward declaration and the
version is now 1.8.4. The timer is still Explorer-only (`g_InsideExplorerProc`).

- Live: `local@translucent-windows-plus_1.8.4_874514.dll`, LoggingEnabled 0.
- Verified by the owner on screen (their screenshot, 2026-10-24): Properties is blurred, not black.
- The guard is restaged by `scripts\2026-10-24-twp-guard-restage.ps1`. It pins the new
  DLL name and hashes, and the suspend marker is removed. Enforce exit 0, Audit shows no
  drift. The new pristine `.reg` holds only top-level values, so a heal can't rewrite the
  Settings key (it keeps RuledPrograms[31], T3 Code). The old guard script and the old
  source are in `backups\2026-10-24-twp-black-dialogs\guard-before\`.
- The T3 freeze from 10:56 to 10:58 AM lines up with the debug build, which logged
  to a file from every process it covered. Inferred, not proven. That build is gone.

## 2. Shell Font Changer Plus 1.3.3: labels cut off in Properties

Cause (debug log, `work\2026-10-24-sfc-clipping\`): themed checkboxes and buttons
draw into a buffered-paint bitmap. They pass DrawTextEx a box wider than that bitmap:
the Read-only checkbox got 16..317 inside a 245 px control, and the "Change settings
for all users" button got -3..200 centred in a 180 px bitmap. `fitBox` trusted the
box, so the wider Fira Code text was clipped.

Fix in `fitBox`: limit the box to the window's client area (window DCs) or to the
clip box (memory DCs, skipping the 1x1 stock bitmap). Centred text is limited
evenly on both sides around the box centre. When the text still doesn't fit, the
existing floors apply and the label falls back to the original font.

- Tests: three new cases in `tests\font-tests.cpp`. `Build.ps1 -Test`: Failures 0.
- Live: `local@shell-font-changer-plus_1.3.3_277020.dll`.
- On-screen captures, 4:00 PM: `work\2026-10-24-sfc-clipping\general-final.png`
  and `compat-final.png`. Every label is whole. The Location field scrolls long
  paths, and stock Windows does that too.
- Pushed to davids-windhawk-mods main on 2026-10-24 at 4:05 PM (checked with git log origin/main).

## Rollback

- TWP: restore `backups\2026-10-24-twp-black-dialogs\local@translucent-windows-plus.wh.cpp.before`
  and the guard script from `guard-before\`, suspend the guard, then compile.
- Font mod: `work\2026-10-24-sfc-clipping\live-before.wh.cpp` is the 1.3.0 source.
  Install it with `scripts\2026-10-24-mod-install-source.ps1`.
