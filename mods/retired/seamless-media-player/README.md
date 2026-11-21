# Seamless Media Player

A taskbar media player and a live audio visualizer in one mod. It shows album
art, the title and the buttons, and the spectrum bars sit right beside it or
behind it.

![Seamless Media Player preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-media-player.png)

## Features
- **Player and bars stay together.** The bars follow the player's right edge,
  so they never overlap it or drift away.
- **Bars beside or behind.** Set Audio visualizer > Position > Placement to
  "Behind widget" and the bars fill the player's background, dimmed under the
  art, title and buttons, with no extra width.
- **Progress bar and time.** A thin progress line along the bottom (click it
  to seek) and an elapsed or elapsed/total clock. Both are off by default.
- **Fits its contents.** The dock shrinks to the bars when nothing plays and
  grows smoothly to the player when music starts. It jumps instead of
  animating when Windows animations are off.
- **Lines up after your system stats.** Choose "Taskbar - After Taskbar System
  Info" and the player sits right after Taskbar System Info.
- **Live spectrum bars** with smooth falloff, six shapes, gradients and EQ
  presets. Right-click the bars to choose what they listen to, including a
  virtual cable or loopback input. The menu matches the Catppuccin Mocha
  taskbar menus.
- **Flat bars on an input you picked?** Check that the input isn't muted in
  Windows sound settings. A muted input still sends audio to apps, but as
  silence, even while its level meter moves.
- **Stays out of the way.** It hides during fullscreen games and follows
  taskbar auto-hide.

## Install
1. In Windhawk, choose **Create a new mod**.
2. Paste [seamless-media-player.wh.cpp](seamless-media-player.wh.cpp) and click
   **Compile**.
3. Turn off **Taskbar Fluent Media Player** and **Taskbar Audio Visualizer** if
   you have them, so you don't get two players or two sets of bars.

The mod only listens to audio. It never changes devices, volume or routing.

## Credits
Made by [DavidHiFi](https://github.com/DavidHiFi). Based on
[Taskbar Fluent Media Player](https://windhawk.net/mods/taskbar-fluent-media-player)
by [Salyts](https://github.com/Salyts) (MIT). The bars come from Taskbar Audio
Visualizer, built on Tourne'Table by USER-TOURNE and Desktop Audio Visualizer by
Salyts. Thanks to [GR0UD](https://github.com/GR0UD) for the audio capture code
in the original player. The behind-widget bars, progress bar and time display
follow [Taskbar Media Widget](https://windhawk.net/mods/taskbar-media-widget) by
[uMk0](https://github.com/umk0) (MIT).
