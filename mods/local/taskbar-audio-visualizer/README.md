# Taskbar Audio Visualizer

A live audio spectrum and media controls that sit on the taskbar, next to your
other widgets.

![Taskbar Audio Visualizer preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/taskbar-audio-visualizer.gif)

## Features

- **Live spectrum bars** that follow whatever is playing, with smooth falloff
  and optional peak caps.
- **Media controls** for previous, play/pause and next, with built-in icons or
  your own images.
- **Choose what it listens to.** Right-click the bars to follow every active
  output, a single output device, or an input such as an audio interface's
  loopback.
- **Stays out of the way.** It hides during fullscreen and borderless-windowed
  games -- including after you alt-tab away while the game keeps covering the
  taskbar -- and while an always-on-top window sits over the strip. It follows
  the taskbar's auto-hide by the shell's live state: when the taskbar actually
  slides off the screen the strip slides with it and comes back with it, and
  while the taskbar sits parked on screen (a wedged auto-hide behaves this
  way) the strip stays visible with it. Clicks on the taskbar pass straight
  through.
- **Customizable** bar shape, size, colors, EQ, response speed and background.
  Catppuccin Mocha colors by default.
- **Light on resources.** Drawing slows down when nothing is playing.

## Tips

- Use **Horizontal offset** to place the bars after other taskbar widgets.
- Disable other taskbar visualizers, such as Tourne'Table, first.
- The mod only listens. It never changes playback devices, volume or routing.

## Credits

Based on [Tourne'Table](https://windhawk.net/mods/tourne-table-desktop-audio-visualizer)
by USER-TOURNE and [Desktop Audio Visualizer](https://windhawk.net/mods/desktop-audio-visualizer)
by Salyts. MIT.
