# Seamless Snipper: design

Date: 2026-11-12. Thread 62d4485d. Status: design, waiting on owner approval before any build.

## Why

The owner runs ShareX all day (about 4,700 captures since 25 Aug 2026) but uses a thin slice
of it. ShareX is a heavy .NET app with 80+ upload services, a main window, a task list and
dozens of tools the owner never opens. Seamless Snipper replaces it with one Windhawk tool mod
that does only what the owner uses, opens instantly, looks like the rest of the Seamless family
(Mocha glass, blue to mauve hover) and is configured from our universal settings window.
It also absorbs Magic Pointer Plus, which is retired once Snipper carries all of it.

## What the owner actually uses (evidence)

From the live ShareX profile (`D:\Configuration Files\ShareX\Personal`) and both log folders:

| Use | Count |
|---|---|
| Region snip (Print Screen) | about 5,200 hotkey presses |
| Active window, active monitor, full screen | about 450 together |
| Make window borderless (now in Seamless Window Manager, Ctrl+Shift+F) | 108 |
| Open image history | about 80 |
| Screen recording, video plus GIF | 16 |
| Uploads | 0, ever (every history row has no host and no URL) |

After every capture: copy image to clipboard and save PNG to `G:\Gallery\<dd-mm-yy>\`.
Windows' own "Print Screen opens Snipping Tool" is already off (`PrintScreenKeyForSnippingEnabled = 0`).

## Owner decisions (2026-11-12)

Keep:
- Region, window, active monitor and full-screen capture.
- Scrolling capture, repeat last region, timer snip, screen recording.
- Markup editor (arrows, boxes, text, highlight, blur or pixelate, numbered steps, crop).
- Borders and shadows on window shots (optional frame, rounded corners, drop shadow).
- Snip history, screen ruler, QR code reader.
- Recording: MP4 with system audio by default, GIF as an option, hardware encoder, small stop
  bar with a timer. Microphone off unless turned on.
- Region snip look: ShareX style, riced. Frozen screen, dim outside the selection, magnifier with
  a pixel grid, snapping to windows and controls, size readout, Mocha glass toolbar on the box.
- Saving: same folder (`G:\Gallery`) and day folders (`dd-mm-yy`), PNG, clipboard plus save,
  but readable file names built from the app and time, for example `Discord 4.05 pm.png`.
- Hotkeys: the live ShareX map stays. Print Screen = region, Shift+PrtSc = full screen,
  Alt+PrtSc = active window, Ctrl+PrtSc = active monitor, Ctrl+Shift+H = history.
- Magic Pointer Plus: keep all of it. Shake to summon still works, and the snip toolbar also gets
  "Ask AI" and "Copy text". Magic Pointer Plus is then retired.

Drop:
- All uploading, URL shorteners, sharing services, upload history, FTP, custom uploaders.
- Pin to screen (the owner already has a Windhawk mod for pinning windows).
- Image effects presets, watermarks, thumbnails, the ShareX main window and task list,
  hash checker, image combiner/splitter, video converter, thumbnailer, monitor test, DNS
  changer, tweet/social tools, workflows, the after-upload pipeline, auto-update, languages.
- Webcam overlay, two-pass encoding, ffmpeg dependency.

Leave alone:
- Seamless Color Picker stays its own mod. Snipper's magnifier only shows the hex under the
  cursor and copies it with one key.
- The borderless hotkey stays in Seamless Window Manager.

After Snipper is built and verified: close ShareX, turn off its startup and hotkeys, keep it
installed. The owner uninstalls later.

## Goals

- Print Screen to frozen overlay in under 100 ms on the owner's three-monitor tower, every time.
- Smooth: the overlay, magnifier and drag run at the monitor's refresh rate with no tearing,
  no flicker and no white flash.
- Nothing runs between snips except the hotkey listener and the shake detector. No polling
  timers, no idle CPU, memory back near baseline after each snip.
- One mod, one settings window, one tray icon.

## Non-goals

- Uploading of any kind, now or later.
- A general image editor. The markup editor works on the snip that was just taken (and on a
  file opened from history), nothing more.
- Feature parity with ShareX.

## Anti-goals (a fail even if it works)

- Any visible lag on Print Screen, or a dropped key press.
- A console window, a flash of another window, or the cursor moving on its own.
- A crash or freeze of Explorer or the desktop. Snipper runs in its own tool-mod process,
  never inside Explorer or `dwm.exe`.
- Text that does not read like a person wrote it (humanizer pass).
- A second look: every surface is the Seamless look, no stock Win32 grey.

## Constraints

- Windhawk tool mod (`windhawk_tool_mod.h`), built only with `windhawk-cli.exe mod compile`
  (elevated), through the load gate. Id `local@seamless-snipper` in the registry, bare
  `seamless-snipper` in the source header.
- Follow `AGENTS.md`, `docs\mod-style-guide.md` and the release checklist: `@author DavidHiFi`
  first, Ko-fi `@donateUrl`, StartPad-style settings, real preview image.
- Settings window: generated from the Seamless Launchpad engine (`work\2026-11-10-media-settings\gen.py`),
  per `docs\settings-gui-standard.md`; `scripts\settings-material.py check` must say ok. Install
  with `scripts\Install-StagedMod.ps1`. Restart only with `scripts\2026-11-10-tool-mod-restart.ps1`.
- Screens are SDR (ACM off). Judge on-screen results from a real frame (gfxcapture or ddagrab).
- No hook may swallow a modifier key-up.
- Magic Pointer Plus is claimed right now by another thread (menu compact). Read its source, do
  not edit it. Retiring it means turning it off after Snipper carries every feature, with its
  settings carried over.

## How it works (builder's outline; calls marked "my call" are the designer's, not the owner's)

### Process and shape
One tool-mod process. A message-only window owns hotkeys, the tray icon and the settings window.
Overlay, editor, recorder bar, history and ruler are windows created on demand and destroyed
after use (my call: pre-create the overlay window hidden once, so the first snip is as fast as
the rest).

### Capture
- Freeze frame: Desktop Duplication (DXGI) per monitor into one virtual-desktop bitmap, with
  BitBlt as fallback (my call). Cursor drawn in only when "Include cursor" is on (ShareX had it on).
- Window shot: DWM extended frame bounds. With "Borders and shadows" on, capture the window with
  its transparent rounded corners and add an optional drop shadow and frame (settings: shadow
  on/off, shadow size, corner radius, frame colour and width).
- Readable names: `<App> <h.mm am/pm>.png` from the window under the selection centre (region),
  the target window (window shot) or "Screen" (monitor and full screen). A clash adds ` (2)`.
  Pattern is a setting.

### Region overlay (Print Screen)
Topmost borderless window per monitor showing the frozen frame, drawn with Direct2D (my call).
Dim outside the selection, bright inside. Hover highlights the window or control under the
cursor; click takes it, drag draws a box. Magnifier with pixel grid and hex readout near the
cursor; arrow keys nudge by 1 px, Shift+arrows by 10. Size readout. Right-click or Esc cancels.
After the box is set, a Mocha glass toolbar sits on the box edge: markup tools, Copy text,
Ask AI, QR, Save, Copy, Close. Enter or double-click finishes (copy plus save).

### Markup editor
Runs on the selection inside the overlay (ShareX style): arrow, line, rectangle, ellipse,
freehand, text, highlighter, blur, pixelate, numbered steps, crop. Colour and thickness on the
toolbar, Ctrl+Z and Ctrl+Y, Shift snaps angles and squares. The same editor opens a file from
history.

### Other capture modes
- Repeat last region: one key, no overlay.
- Timer snip: 3, 5 or 10 s countdown pill (setting), then the region overlay.
- Scrolling capture: pick a window or area, Snipper scrolls it and stitches frames by matching
  rows; a stop button and a max length setting.
- Screen recording: pick a region, MP4 through Media Foundation with the hardware H.264 encoder
  and system audio (WASAPI loopback), mic optional; GIF through WIC at 15 fps (setting). Small
  glass stop bar with timer; the same hotkey stops it.

### Tools
- Screen ruler: frozen frame, drag to measure width, height, diagonal; hover shows gaps to edges.
- QR reader: on a snip or a selection; decodes with an embedded small decoder (my call: quirc,
  ISC licence, credited); result copied, links offered to open.
- Snip history: glass window listing the save folder newest first with thumbnails, search by
  name, copy again, open, open folder, edit in markup, delete to recycle bin. Ctrl+Shift+H.
  (My call: also lists the old ShareX history files that still exist.)

### Magic Pointer, folded in
Every feature of Magic Pointer Plus moves over unchanged in behaviour: shake detection and
sensitivity, Win+Shift+G, point or select, type to ask, Gemini, ChatGPT and Claude, text
recognition, glow colour, glass, ripple, excluded apps, theme, its translations. The snip
toolbar gets "Ask AI" (sends the snip) and "Copy text" (Windows OCR). Settings migrate from
`local@magic-pointer-plus` on first run.

### Default keys
Owner-set: PrtSc region, Shift+PrtSc full screen, Alt+PrtSc active window, Ctrl+PrtSc active
monitor, Ctrl+Shift+H history, Win+Shift+G Magic Pointer.
My call for the new ones (all changeable, empty turns one off): Ctrl+Shift+PrtSc record MP4,
Ctrl+Alt+PrtSc record GIF, Alt+Shift+PrtSc scrolling capture, Ctrl+Alt+Shift+PrtSc repeat last
region; timer, ruler and QR start with no key and live in the tray menu.

### Settings groups
Keys, Capture (cursor, folder, day folder pattern, name pattern, format), Region snip
(magnifier, snapping, dim strength), Borders and shadows, Markup defaults, Recording,
Scrolling, Magic Pointer, Settings window (glass, title bar, title buttons, tray icon), About.

## Switch-over
1. Build and verify Snipper with its hotkeys off by default while ShareX still runs.
2. Owner sign-off, then: close ShareX, turn off its startup entry and hotkeys, enable Snipper's
   keys, turn off Magic Pointer Plus. Back up ShareX's settings first.
3. ShareX stays installed.

## Settled after the builder check (all designer's calls)

- Process and keys: Snipper runs in the same tool-mod process type Magic Pointer uses today
  (`@include windhawk.exe`), which has the engine's elevation, so Print Screen works over admin
  windows and snapping sees them. Keys use one low-level keyboard hook (Print Screen needs it);
  a handled key is eaten only on key-down and its key-up, never a modifier key-up.
- Magic Pointer: a straight port of the installed source at port time (after the menu-compact
  thread releases it), not a rewrite. In scope: shake and hotkey, point and select (UI
  Automation outlines), the ask card with API keys for Gemini, ChatGPT or Claude (one key setting,
  auto-detected, Fast/Balanced/Smartest), Gemini in the browser when no key, Smart suggestions,
  Translate, Google Lens, copy text (Windows OCR), its menus and translations. "Ask AI" on the
  snip toolbar opens that same card with the snip attached.
- Build order: 1 core capture, overlay, save, clipboard, keys, tray, settings window;
  2 markup editor and borders/shadows; 3 history, ruler, QR, timer, repeat region;
  4 Magic Pointer fold-in; 5 recording; 6 scrolling capture. Switch-over from ShareX may happen
  after step 3 (that covers everything the owner uses daily); Magic Pointer Plus is retired after
  step 4.
- Scrolling capture: the owner places the cursor by clicking the area, then Snipper sends wheel
  input at that spot without moving the cursor, with Page Down and scroll messages as fallbacks.
  Must work in Chromium browsers, Discord and Explorer; custom-drawn apps may stop early with a
  clear message.
- Recording: one region, may span monitors; fps 30 default (15, 30, 60); hardware H.264 first,
  software encoder fallback without asking; GIF uses a per-frame palette and stays at the GIF fps.
- Monitors: four on the tower (2560x1440 main, three 1920x1080, one above). The overlay is one
  window per monitor, per-monitor DPI aware; the frozen frame is built per monitor.
- History: scans the save folder (all ShareX captures already live in `G:\Gallery`), so no
  ShareX database reading.

## Left to the builder
Window structure, file layout of the single source, Direct2D vs GDI per surface, exact stitching
algorithm, encoder settings, thumbnail cache, how translations are carried over.

## Proof of done
Live, on the tower: a recorded clip of a region snip with snapping and markup, a window shot with
shadow, a scrolling capture, an MP4 with sound, a GIF, the ruler, a QR read, history, and Magic
Pointer by shake; settings window passing `settings-material.py check`; saved files in
`G:\Gallery\<day>\` with readable names; CPU idle between snips.
