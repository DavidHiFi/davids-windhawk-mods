# 2026-11-14: Explorer group headings as fitted docks

Owner (screenshot of This PC): the "Devices and drives" and "Network locations" headings ran as
outlined bars across the whole list. Asked for smooth docks that fit their own size, in our style.

## Owner of the edge

`local@seamless-explorer-view` (the GPU Explorer view, ex GPU Explorer View Plus) paints group
headings itself, in the heading pass of its paint routine: a faint crust fill plus a 1 px surface1
outline at rest, the blue to mauve hover box when hot. That bar was the only edge, so it was
reshaped, nothing added.

## Change: 2.0.0 to 2.0.1

- New `GroupHeadingDockRight`: the dock starts 4 DIP in from the list edge and ends 12 DIP after
  the title text (the same room as before the chevron), measured with the body text format, so it
  follows Ctrl+wheel zoom. Clamped to the list width, so a long title can never be cut.
- Radius 10 DIP, or half the dock height when smaller (a pill at small sizes). Rest fill, rest
  outline and the hover box all use it (`FillSelectionRect` got an optional radius).
- `GroupHeaderAtPoint` stops at the dock edge: hover lights and click collapses only on the dock,
  not on the empty band beside a short title.
- Patch: `work\2026-11-14-explorer-heading-docks\patch.py`. Compile check clean (two old unused
  constant warnings). Installed 11:25 am with `install-2.0.1.ps1` (engine lock, base hash check).
  Registry 2.0.1, library `local@seamless-explorer-view_2.0.1_516255.dll`, loaded in the shell.

## Shell restart during the install

- The shell crashed at 11:26:09 (XAML error pop-up) and restarted itself at 11:26:29, while 2.0.1
  hot-loaded. No guarded restart, no breaker trip.
- Explorer error pop-ups (0xc0000005 "Exception Processing Message") were already firing about once
  a minute from 11:18, before the install, each 2 s after a new COM-factory explorer.exe started;
  also at 10:48, 8:01, 6:55 and around 2 am. Quiet from 11:28. Posted to the coop board.
- Shell health after: 0.5 GB, 182 GDI objects, healthy. Cause of the storm not proven.

## Rollback

Elevated, under `coop lock windhawk-engine`: stage
`backups\2026-11-14-explorer-heading-docks\local@seamless-explorer-view-2.0.0.wh.cpp` with
`scripts\Install-StagedMod.ps1 -Id local@seamless-explorer-view -BaseHash <sha256 of the live 2.0.1
source>`. The installer also kept `local@seamless-explorer-view-20261114-1125.wh.cpp`.

## Later the same day

- Thread 0e4f1937 carried the patch forward and shipped it live as 2.0.2.
- The shell restarted again at 1:24 pm on its own. Cause not proven, same as 11:26.
- Captures of This PC (work\2026-11-14-explorer-heading-docks\proof): crop-rest.png and
  zoom-dock-4x.png show each heading as a rounded dock that ends just after its title, outlined.
- Hover not verified: a posted mouse-move never lit the dock, and the cursor is the owner's,
  so hover was left unchecked rather than moved by hand.
