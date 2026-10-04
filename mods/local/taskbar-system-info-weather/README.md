# Taskbar System Info Plus

A compact hardware monitor on the taskbar: CPU, GPU, memory, temperatures and
network speed at a glance. Taskbar System Info, plus network speeds and a
tighter layout.

![Taskbar System Info Plus preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/taskbar-system-info-weather.png)

```text
CPU 10% 72°C ↑ 1.2 MB/s   RAM  52% 16.7/32G
GPU  4% 56°C ↓ 8.4 MB/s   VRAM  9%  2.1/24G
```

## Features

- **CPU and GPU** load and temperature.
- **RAM and VRAM** usage with used and total gigabytes, plus capacity bars.
- **Upload and download speed** from your real network adapters. Virtual
  adapters and VPN tunnels are skipped so nothing is counted twice.
- **Optional graphs** of recent history for CPU/GPU and RAM/VRAM.
- **Warning colors** when temperatures or memory get high.
- **Any font, any monitor.** Pick an installed font and the taskbar to show it
  on; the width fits the content automatically.
- **Light, dark and high-contrast** taskbars are followed automatically.
- **Plays well with Taskbar Weather.** With it enabled, the panel sits right
  after the weather.

## Temperatures

The default **Automatic** source uses the first one that works:

1. **HWiNFO Shared Memory** - in HWiNFO, open **Settings** and enable
   **Shared Memory Support**.
2. **HWiNFO Gadget** - in HWiNFO's **Sensor Settings > HWiNFO Gadget**, turn on
   **Report to Gadget** for the CPU and GPU temperatures.
3. **Windows** - the GPU driver for the GPU temperature, and ACPI thermal zones
   for the CPU. These need no extra software, but a thermal zone is not always
   the CPU package sensor.

HWiNFO is optional and runs fine in Sensors-only mode. The free edition stops
Shared Memory after 12 hours; the Gadget option or HWiNFO Pro avoid that. A
missing reading shows as `--°C` and everything else keeps working.

## Troubleshooting

- **Wrong GPU:** set **GPU adapter filter** to part of the card's name. Use the
  HWiNFO sensor filters only if the temperature is still wrong.
- **VRAM shows `--` after a driver update:** give it a minute, then reload the
  mod if it stays empty.
- **Integrated GPU memory looks too large:** Automatic shows the Windows shared
  limit. Set **GPU memory type** to Dedicated for the reserved amount.
- **The panel overlaps taskbar buttons:** adjust **Left offset**, or turn on
  **Reserve space before the Start button**.

Disable the original Taskbar System Info and Network Speed Indicator to avoid
duplicates.

## Credits

Based on [Taskbar System Info](https://windhawk.net/mods/taskbar-system-info)
by Yevhenii Starychenko. Network readouts are inspired by Taskbar Network Speed
Indicator by Narayan. Taskbar discovery follows
[Multirow taskbar](https://windhawk.net/mods/taskbar-multirow) and the GPU
temperature code follows Taskbar Clock Customization, both by m417z.
Secondary-taskbar support is adapted from
[Taskbar Fluent Media Player](https://github.com/Salyts/Taskbar-Fluent-Media-Player)
by Salyts. GPL-3.0.

## Install

1. Install [Windhawk](https://windhawk.net/).
2. Choose **Create a new mod**, paste [taskbar-system-info-weather.wh.cpp](taskbar-system-info-weather.wh.cpp) and click **Compile**.

License: GPL-3.0.
