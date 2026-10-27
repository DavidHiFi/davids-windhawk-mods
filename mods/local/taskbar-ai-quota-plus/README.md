# Taskbar AI Quota Bars Plus

Usage bars for your AI subscriptions sit on the Windows 11 taskbar, next to the tray.
Claude, OpenCode Go and Antigravity, each showing the window the provider reports.

![Taskbar AI Quota Bars Plus preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/taskbar-ai-quota-plus.png)

## Features

- **Truthful window labels.** Bars read the window the provider reports: 5h, 7d, 3h or 30d, not a guessed 5h.
- **Compact stacking.** In the Stacked layout, accounts that show a single window share one column.
- **Remaining or used.** Show what is left or what has been used.
- **Alerts.** Optional notifications when usage crosses your red threshold.
- **Antigravity.** Shows usage while an Antigravity CLI or IDE session is running, and keeps the last reading it captured.

## Setup

Open the mod's settings from the taskbar and add accounts under Accounts > Add.

- **Anthropic:** sign in through the browser. Tokens are encrypted with Windows DPAPI.
- **OpenCode Go:** choose provider "OpenCode (Go)" and paste your key from the OpenCode console. The key is encrypted with DPAPI.
- **Antigravity:** keep an Antigravity CLI or IDE session running while quota is fetched.

## Notes

- Antigravity quota comes from a local language server that runs only during a session.
  While no session is running, the mod shows the last saved reading.
- Disable the original Taskbar AI Quota Bars mod if it is installed, or the bars will overlap.

## Credits

Based on [Taskbar AI Quota Bars](https://windhawk.net/mods/taskbar-ai-quota) by Cleroth. MIT license.
