# Pointer Afterimage Plus

[☕ Support on Ko-fi](https://ko-fi.com/DavidHiFi)

A live motion blur for the mouse pointer, everywhere in Windows. While the
mouse moves, fading copies of your actual cursor are drawn along its recent
path, so it looks like a camera motion blur rather than a trail.

![Pointer Afterimage demo](https://raw.githubusercontent.com/sidlikesgrapess/CursorMotionBlur/main/assets/demo.gif)

## Features
- **Drawn on the GPU.** The blur is composited with DirectComposition and
  drawn with Direct2D. The look is the same as the original, with almost no
  CPU use while the mouse moves.
- **Uses your real cursor.** Your scheme, size and colour, and whatever shape
  it has right now. Works with any pointer size and monitor scaling.
- **Renderer setting.** GPU is the default. GDI is the older painter, kept
  for troubleshooting. If the GPU path cannot start or fails while running,
  the mod switches to GDI by itself and writes a log line saying which
  renderer armed.
- **Idle means idle.** Nothing is drawn while the pointer is still, and the
  mod pauses itself while a fullscreen app or game is in front.

## Notes
- The GPU renderer draws in the mod's own window, which sits above normal
  windows and the taskbar but not above the Start menu or Search. Pick the
  GDI renderer if you want the blur over those.
- In a few apps (Paint, Photos, File Explorer's address and search bars) the
  pointer can briefly flicker to the arrow while the blur is drawn. Raise
  "Minimum blur speed" if it gets in the way.

## Install
1. In Windhawk, choose **Create a new mod**.
2. Paste [pointer-afterimage-plus.wh.cpp](pointer-afterimage-plus.wh.cpp) and
   click **Compile**.

## Changes
- **1.2.1:** pieces of earlier trails no longer linger on screen around the
  pointer while it moves.
- **1.2.0:** the GPU renderer and the Renderer setting, on a fork of Pointer
  Afterimage Motion Blur 1.1.

## Credits
Made by [DavidHiFi](https://github.com/DavidHiFi). Based on
[Pointer Afterimage Motion Blur](https://github.com/sidlikesgrapess/CursorMotionBlur)
by sidlikesgrapess.
