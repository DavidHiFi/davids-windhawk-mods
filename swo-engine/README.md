# Seamless Windows Optimizer engine

The small helper program behind the Seamless Windows Optimizer mod. The mod downloads
`swo.exe` from this repo's `swo-engine-v1.0.1` release, checks it against a fixed SHA-256
and runs it hidden. It never shows a window and talks to the mod in JSON lines.

## What it does

- **Clean up**: a Rust port of BleachBit's cleaners for Windows, browsers, games and apps.
  It scans first and deletes only what you ticked.
- **Settings**: privacy, performance, updates, Windows and repair changes. Each one writes a
  journal entry first so it can be put back.
- **Tools**: startup entries, installed programs, hidden updates and a folder space view.

## Build

```
cargo build --release
```

The program lands in `target\release\swo.exe`. Run `swo catalog` to list every item and
`swo scan` to see what the clean-up would free.

## License

GNU General Public License 3.0 or later, the same as BleachBit, whose cleaner list this
ports. See `LICENSE` in this folder. The rest of the repo keeps its own MIT license.

The cleaners follow [BleachBit](https://github.com/bleachbit/bleachbit) by Andrew Ziem and
contributors. Which settings to offer took ideas from Winhance and WTools; nothing was copied
from either.
