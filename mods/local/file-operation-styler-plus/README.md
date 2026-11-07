# File Operation Styler Plus

[☕ Support on Ko-fi](https://ko-fi.com/DavidHiFi)

A modern replacement for the standard Windows 11 file operation window. Copy,
move, delete and recycle operations get a cleaner layout with a large
progress circle, while Windows keeps handling the operation itself.

![File Operation Styler](https://raw.githubusercontent.com/digart11/File-Operation-Styler/master/images/file-operation-styler.png)

## Features
- **Drawn on the GPU.** The custom chrome composites through
  DirectComposition: static frames draw once, progress redraws only when the
  values change, and fades run on the compositor while the processor sleeps.
- **Circular progress.** The large circle pauses and resumes the operation,
  with the current file, speed and estimated time around it.
- **One window for many operations,** with automatic vertical scrolling when
  needed.
- **Themes.** Several built-in themes including Frosted Glass, with Windows
  Acrylic and Custom Blur, plus custom colors, fonts and progress thickness.
- **Renderer setting.** GPU is the default. Legacy keeps the original GDI+
  painting, and any GPU failure falls back to it automatically.

## Using another file manager
The mod works with Windows Explorer automatically, and can also work with
file managers that use the native Windows copy dialogs. Add your file
manager's EXE name to **Custom process inclusion list** under
**File Operation Styler > Advanced** in Windhawk, then completely restart
the file manager.

## Install
1. In Windhawk, choose **Create a new mod**.
2. Paste [file-operation-styler-plus.wh.cpp](file-operation-styler-plus.wh.cpp)
   and click **Compile**.

## Changes
- **1.5.0:** the GPU renderer and the Renderer setting, on a fork of File
  Operation Styler 1.4.0. Everything else from 1.4.0 is unchanged.

## Credits
Made by [DavidHiFi](https://github.com/DavidHiFi). Based on
[File Operation Styler](https://github.com/digart11/File-Operation-Styler)
by digART.
