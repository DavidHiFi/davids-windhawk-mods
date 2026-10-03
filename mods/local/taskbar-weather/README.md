# Independent taskbar weather

Version 1.3.2 centers the Celsius temperature above the condition beside the weather icon. The taskbar text uses an available semibold font face, with a bold fallback. The widget measures the wider line so the adjacent stats move left automatically. Loading and unavailable messages remain on one line. Small taskbar glyphs use grayscale antialiasing with grid fitting, stronger text contrast and whole-pixel line positions. This restores smooth edges while retaining the semibold face. The hover highlight has an inset inside the taskbar, while the forecast card opens outside the taskbar as before.

Native weather for the primary Windows 11 taskbar, with a rounded dark hover card, automatic updates and saved readings. Uses [Open-Meteo](https://open-meteo.com/) weather data over HTTPS. No Windows Widgets, Edge, WebView or API key is required.

## Install

1. Install Windhawk and choose **Create new mod**.
2. Paste [taskbar-weather.wh.cpp](taskbar-weather.wh.cpp), then compile and enable it.
3. In Settings, enter your town center's latitude and longitude. Optionally enter a town name for the hover card. Coordinates ship empty and remain in your local settings.
4. Disable Windows Widgets in Windows taskbar settings if it occupies the same space.

Click the weather to refresh. It normally updates every ten minutes, retries failed requests after one minute, refreshes on resume, and recreates its taskbar child if Windows replaces it. A saved reading remains visible during temporary network failures; readings older than thirty minutes are marked stale. The mod shows a setup prompt until coordinates are entered.

The card shows Celsius temperature, conditions, feels-like temperature, today's high and low, humidity, wind and the reading time. Open-Meteo provides modeled weather for the chosen coordinates; it can differ from a phone app using another provider or observation time. Free endpoint use is subject to [Open-Meteo's terms](https://open-meteo.com/en/terms).

For a neatly adjacent performance monitor, install [Taskbar System Info with Weather](../taskbar-system-info-weather). The monitor follows the weather's visible right edge with a shared configurable gap. Width and left offset are configurable. Primary taskbar only; Windows 11 x64.

## Validation and removal

Built with Windhawk 1.7.3. The 1.3.2 smoothed text and hover layout passed an x64 build and live verification at 96 DPI. The stacked Clear reading reduced the widget width by 39 DIP, and the stats and visualizer followed it without restarting Explorer. Tested taskbar child recreation, resume notification refresh, timed refresh, cached readings after a network error and automatic retry. A full reboot and physical sleep cycle have not been tested in this release.

Disable or remove the mod in Windhawk to undo it. No Explorer restart is required. MIT license.
