# G HUB: no more installing by itself

Date: 2026-11-24, 1:50 to 2:00 am. The owner found G HUB in the tray and asked why.

## Why it was there

Seamless Workshop 1.5.0's first auto round (2026-11-23, 10:05 am) installed it: the
`ghub` extra had `"auto": true`, a Logitech receiver is plugged in, and the battery tray mod
is on. See `notes\2026-11-23-seamless-workshop-1.5.0.md`.

## What changed (owner picked option 1)

- `davids-windhawk-mods\deps\extras.json`: `ghub` lost `"auto": true` and the text now says
  it is optional and goes in only when asked. Mods repo commit 359d3ea, published: mods
  b3656e7, feed efc7569. The live feed on GitHub shows `auto: False`. Every PC's Workshop
  reads this on its next round, so it never installs G HUB by itself again. It stays on the
  Extras page for anyone who wants it.
- Tower: removed with the Workshop's own `ghub.ps1 -Mode remove` (elevated): "G HUB is
  removed." No uninstall entry, no program folder, no G HUB process or updater service, no
  window left. Backup of extras.json in `D:\Agent Work\2026-11-24-ghub-why\`.
- Left alone: `logi_lamparray_service`. It is Windows' own Logitech lighting driver from
  2026-08-25, not part of G HUB.
- The battery tray mod reads the LIGHTSPEED receiver directly (HID++) without G HUB.
