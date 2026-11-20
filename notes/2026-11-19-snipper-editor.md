# Snipper drawing controls update

The staged source was assembled from the installed Snipper source, including its current shared settings window. The new build adds resize handles to selected shapes and connects the drawing strip to right-click and wheel input. Text and speech balloons have a Font and size button. It opens the Windows font picker and applies the choice to the text being edited or selected. The picker keeps a separate font for each text object, so changing one object does not restyle the rest.

The completed offline syntax check returned 0. The settings engine and glass checks passed. The consistency check reported zero failures for Snipper, with existing warnings about its tray renderer and alternate font names. The full check found that Seamless Title Bars and Seamless Window Manager need the latest shared settings template.

Windhawk installed the new build and saved the previous source and full mod key in the settings-material backup folder with stamp 20261119-1831. No capture defaults or registry settings were intentionally changed. During installation, the enabled entry updated but the helper did not start. The standard one-mod restart is the next recovery step.

Rollback is to install the backed-up Snipper source with the guarded installer against the new source hash, then verify the helper. The registry backup is available if settings need restoring. The capture editor and font picker still need live verification.

Helper correction (8:15 pm): the helper never died after the 7:06 pm restart. An unelevated process query cannot read an elevated helper's command line, so it looked missing. The 0.6.2 helper self-elevates; detect it by the SeamlessSnipperMsg window (or read its pid from that window), never by Win32_Process CommandLine from an unelevated shell. Now pid 32152.

Live proof script: test\prove-editor-062.py (posted input only, waits for the owner to be idle via test\wait-idle.py, records video, drives the Font pill through the Windows font dialog with posted WM_COMMAND/WM_SETTEXT). Pill click point computed from LayoutStrip at ui 1: first pill, centre about (monitor centre - 123, bar bottom + 6 + 16).

## 0.6.3 (2026-11-20): ShareX-style editing

- Every strip option opens a dropdown list; Text and Balloon have a font list and size list, kept per shape.
- A new drawing stays picked with handles, in every drawing tool. Changing an option restyles the picked shape and becomes the tool's default.
- Handles: boxes have 8 (corners and sides, with matching resize pointers); lines, balloons and numbered steps have their two points; arrows add a round middle handle that bends the arrow (dragging it straight turns the curve off).
- Pressing on any shape in any tool picks and moves it. Areas (blur, pixelate, highlight, spotlight, magnifier, eraser) and unfilled boxes or circles grab only on their edge, so new drawings can start inside them. Clicking picked words again (or a double-click) opens them for typing.
- Esc lets go of the pick before it closes the overlay; arrow keys nudge the pick 1 px (Shift 10).
- Known gaps: pen strokes move but do not reshape; text has no drag-to-scale handle (size from the list, wheel or [ ]); balloon text colour is automatic contrast.
- Backup of 0.6.2: backups\2026-11-20\snipper-0.6.2 (source and mod key). Rollback: install that source with Install-StagedMod.ps1 against the 0.6.3 hash.

### 0.6.3 installed and proved live (2026-11-21, 3:30 am / 4:59 am)
- Installed with Install-StagedMod (registry v0.6.3, backup local@seamless-snipper-20261121-0330.wh.cpp); published davids-windhawk-mods 07f9a71, seamless-workshop d0e7acb.
- Live proof (test\prove-editor-063.py, run elevated via test\run-proof-063.ps1): new box picked with 8 handles, corner and edge resize, arrow bend and end drag, arrow-key nudge (8 right, 4 down), Esc drops the pick and keeps the screen, box moved by its edge with another tool, text picked shows the strip font list and size. Shots and video in test\proof-063-live.
- Not driven live: choosing a different font from the list (the old test drove the Windows font box, which 0.6.3 replaced).
- The helper runs elevated: tests from normal rights get PostMessage error 5 and nothing opens.

### 0.6.4 installed and proved live (2026-11-21, 5:53 am / 6:47 am)
- New: text and balloon words wrap like ShareX. Picked text has 6 handles (corners and side middles); the sides set how wide the words run before they wrap, and the left ones keep the right edge still. A balloon gets a third handle on its right side for the same job. Pen strokes stay move-only, as in ShareX.
- Installed with Install-StagedMod at 5:53 am (backup local@seamless-snipper-20261121-0553.wh.cpp, live hash A6CE69F6..., same as staged); published davids-windhawk-mods 159492b, seamless-workshop 812f1c7.
- Live proof (test\prove-editor-064.py, elevated via test\run-locked-proof-064.ps1 under the desktop lock): 6 text handles; right side dragged in, so the box got 423 px narrower and 59 px taller (3 lines); left side dragged 160 px out with the right edge kept to the pixel; font list opened from the strip, typing G E O and Enter picked Georgia, the list closed and the words redrew in Georgia; balloon width handle moved 220 px and the words wrapped. Shots, video and GIF in test\proof-064-live.
- The first run (6:39 am) missed the handles: a Windows Security firewall prompt for etcher-cli (another thread's program, not answered by us) dimmed the screen and covered the text. The handle finder now tries dimmed colours too, and the test text sits low on the left.
- Rollback: install local@seamless-snipper-20261121-0553.wh.cpp (0.6.3) with Install-StagedMod.ps1 against the 0.6.4 hash.
