# Settings reference

This page lists all 49 settings. They reload without restarting Explorer, Windhawk or audio applications.

Geometry is clamped to fit the main horizontal taskbar. Colors accept `#AARRGGBB`, `#RRGGBB`, `rgba(...)`, or `rgb(...)`. Invalid color and quad values fall back to their documented defaults.

## Position

| Setting | Default | Behavior |
| --- | --- | --- |
| `position.taskbarOffset` | `500` | Distance from the main taskbar left edge in logical pixels. Values are clamped to keep the strip on screen. |
| `position.verticalOffset` | `0` | Logical pixels from the taskbar center. Negative values move upward. The strip stays inside the taskbar. |

## Appearance

| Setting | Default | Behavior |
| --- | --- | --- |
| `appearance.shape` | `stereo` | Choose how the spectrum is drawn. Options: stereo, mountain, mirror, wave, breathe, dots. |
| `appearance.barCount` | `32` | 1 to 128 bars. The media buttons follow the end of the bar group. |
| `appearance.barWidth` | `3` | 1 to 24 logical pixels. |
| `appearance.barGap` | `2` | 0 to 24 logical pixels between bars. |
| `appearance.barMaxSize` | `26` | 2 to 128 logical pixels, limited by the taskbar height. |
| `appearance.barIdleSize` | `2` | Visible height during silence. 0 removes idle bars; values cannot exceed the maximum bar height. |
| `appearance.barCornerRadius` | `1` | One radius for all corners, or four comma-separated radii in top-left, top-right, bottom-right, bottom-left order. |
| `appearance.verticalAnchor` | `bottom` | Choose the direction in which each bar grows. Options: bottom, middle, top. |
| `appearance.colorMode` | `gradient` | Choose a fixed color, gradient, level-reactive gradient, Windows accent, or rainbow. Options: solid, gradient, reactive_gradient, accent, rainbow. |
| `appearance.color` | `#FFCBA6F7` | Color in #AARRGGBB or #RRGGBB format. Default is Catppuccin Mocha mauve. |
| `appearance.gradientColor1` | `#FFCBA6F7` | First gradient color. Default is Catppuccin Mocha mauve. |
| `appearance.gradientColor2` | `#FF89B4FA` | Second gradient color. Default is Catppuccin Mocha blue. |
| `appearance.rainbowSpeed` | `40` | 1 to 300. Used by the Rainbow color mode. |
| `appearance.sensitivity` | `175` | 0 to 300. Changes spectrum response without changing playback volume. |
| `appearance.sensitivityCurve` | `knee` | Choose how captured levels map to bar height. Options: knee, exponential, power. |
| `appearance.smoothing` | `60` | 0 to 100. Higher values soften bar movement. |
| `appearance.eqPreset` | `default` | Weights frequency bands for drawing. This does not change audio playback. Options: default, bass, rock, pop, jazz, electronic. |
| `appearance.fftSize` | `1024` | Larger windows improve frequency resolution and increase analysis latency. Options: 1024, 2048, 4096, 8192. |
| `appearance.freqScale` | `log` | Maps the analyzed frequency bands across the bar group. Options: log, linear, mel. |
| `appearance.peakHoldEnabled` | `false` | Draw a falling cap above recent peak levels. |
| `appearance.peakHoldColor` | `#FF89B4FA` | Color of the peak hold caps. |

## Audio

| Setting | Default | Behavior |
| --- | --- | --- |
| `audio.captureMode` | `all` | All outputs follows per-app Windows routing. Default output reads only the default multimedia render endpoint. Options: all, default. |
| `audio.hardwareLoopbacks` | `true` | Also read recording endpoints explicitly named Loopback, which can include an interface ASIO mix. Microphone and general recording endpoints are excluded. |
| `audio.deviceFilter` | `empty` | Optional case-insensitive substring of an endpoint name. Blank includes every endpoint selected by the capture options above. |
| `audio.inputGain` | `0` | -24 to +24 dB applied only to the captured analysis signal. Playback and routing stay unchanged. |

## Background

| Setting | Default | Behavior |
| --- | --- | --- |
| `background.enabled` | `false` | Draw a panel behind the bars. |
| `background.color` | `#801E1E2E` | Color and opacity of the panel. Default is translucent Catppuccin Mocha base. |
| `background.padding` | `4` | One value or four values in left, right, top, bottom order. 0 to 12 logical pixels per side. |
| `background.cornerRadius` | `6` | One radius or four corner radii in top-left, top-right, bottom-right, bottom-left order. |
| `background.borderSize` | `0` | 0 to 8 logical pixels. 0 removes the border. |
| `background.borderColor` | `#FF45475A` | Color of the panel border. |

## Media controls

| Setting | Default | Behavior |
| --- | --- | --- |
| `media_controls.enabled` | `true` | Show Previous, Play/Pause, and Next beside the bars. Buttons use the active Windows media session. |
| `media_controls.gap` | `18` | 0 to 200 logical pixels between the bar group and media buttons. |
| `media_controls.iconSize` | `16` | 8 to 32 logical pixels, limited by the taskbar height. |
| `media_controls.iconSpacing` | `8` | 0 to 64 logical pixels between buttons. |
| `media_controls.iconColor` | `#FFCDD6F4` | Color of the built-in button glyphs. Default is Catppuccin Mocha text. |
| `media_controls.iconPrevPath` | `empty` | Optional local PNG, JPG, BMP, or ICO file. Blank uses the built-in glyph. |
| `media_controls.iconPlayPath` | `empty` | Optional local PNG, JPG, BMP, or ICO file. Blank uses the built-in glyph. |
| `media_controls.iconPausePath` | `empty` | Optional local PNG, JPG, BMP, or ICO file. Blank uses the built-in glyph. |
| `media_controls.iconNextPath` | `empty` | Optional local PNG, JPG, BMP, or ICO file. Blank uses the built-in glyph. |
| `media_controls.plateColor` | `#00000000` | Color of the media button backing panel. Alpha 0 keeps it transparent. |
| `media_controls.platePadding` | `0` | 0 to 8 logical pixels around the media buttons. |
| `media_controls.plateCornerRadius` | `6` | 0 to 16 logical pixels. |

## Performance

| Setting | Default | Behavior |
| --- | --- | --- |
| `performance.targetFps` | `30` | 10 to 120 frames per second. Default is 30. |
| `performance.pauseWhenSilentSeconds` | `10` | After this many silent seconds, draw at 5 FPS. The strip remains visible and resumes its normal rate when audio returns. 0 disables idle throttling. |

| `performance.hideWhenFullscreen` | `true` | Hide bars and media buttons when a fullscreen or borderless foreground window covers the taskbar. Restore them when the taskbar is available. |

## Diagnostics

| Setting | Default | Behavior |
| --- | --- | --- |
| `diagnostics.enabled` | `false` | Write endpoint status and level summaries to diagnostic.log in this mod Windhawk storage directory. Logs rotate at 1 MiB. Audio samples are never recorded. |

## Capture device menu

Right-click the bars and choose one active Windows endpoint under Input device
or Output device. This overrides capture mode, hardware loopbacks, and the
name filter until you choose Use configured multi-device capture. The mod saves
the selected endpoint ID in Windhawk local storage as `captureEndpointId`.
Input selection permits a recording source, including microphones. Output
selection captures that device's playback mix through WASAPI loopback.
The menu changes capture only. It leaves playback routing and defaults alone.
