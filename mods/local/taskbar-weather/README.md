# Taskbar Weather

The current weather on the left side of the taskbar, with a details card when
you hover over it. It works on its own, without Windows Widgets.

![Taskbar Weather preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/taskbar-weather.png)

## Features

- **Weather icon, temperature and conditions** on the taskbar, updated every
  ten minutes by default.
- **Hover card** with the feels-like temperature, today's high and low,
  humidity and wind.
- **Click to refresh** at any time.
- **No Widgets, MSN, Edge or location permission.** Data comes from
  Open-Meteo, with no account or API key.
- **Adjustable** position, width, font and size, in Catppuccin Mocha colors.

## Setup

Open the settings and enter your town's **latitude** and **longitude** (in most
map apps, right-click a place to copy them). Add a **place name** to show it in
the hover card. The coordinates are saved locally and sent to Open-Meteo with each request.
Internet access is required; Open-Meteo also receives your IP address.

Temperatures are in Celsius. If a request fails, the last reading stays and
the mod retries a minute later; readings older than 30 minutes are marked in
the card. Turn off Windows Widgets to avoid a second weather button.

## Credits

Weather data by [Open-Meteo.com](https://open-meteo.com/) (CC BY 4.0). MIT.

## Install

1. Install [Windhawk](https://windhawk.net/).
2. Choose **Create a new mod**, paste [taskbar-weather.wh.cpp](taskbar-weather.wh.cpp) and click **Compile**.

License: MIT.
