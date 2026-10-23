# Windhawk 2.0 logging + toolkit facts (input-death hunt reference)

Date: 2026-10-22 2:00 PM. Ground truth measured on install (`windhawk.exe` reports 2.0.0-alpha.7),
from the shipped UI's own strings (`Program Files\Windhawk\UI\resources\app\extensions\windhawk\`),
the vendored Rust UI (Angular), the local source checkout `Windhawk\upstream\windhawk-2.0.0-alpha.6`
(alpha .6, one rev behind installed .7 - same model), and live registry reads.

## What "the logging stuff" is

- All Windhog/engine/mod log lines go to the **Windows debug stream**, tagged `[WH] `.
- There is **no persistent file log sink**. Lines are heard only while a listener is attached:
  - the UI's own Debug logs pane / "Show log output" (live, only while the UI is open - it spawns
    the bundled `DbgViewMini.exe`: `--pattern "[WH] *" --no-buffering`, consuming stdout
    (`logOutputChannel.ts`)),
  - **an external capture**: `DbgViewMini.exe --pattern "[WH] *" --no-buffering > file` works
    unattended, e.g. from a boot script (Sysinternals DebugView with Capture Win32 + Global also
    works).

## The knobs (registry: `HKLM\SOFTWARE\Windhawk`)

| Knob | Where | Values now (measured 2:00 PM 10/22) | Applies |
| --- | --- | --- | --- |
| App logging verbosity (`LoggingVerbosity`) | `Settings` key | **2** (= the "Verbose" option; default 0) | app/engine internal lines; already maxed |
| Engine logging verbosity (`LoggingVerbosity` on `Engine`) | `Engine` key root | absent = default 0 | restart-class change (engine restart on write) per `app_settings.rs` test comment |
| Per-mod "Enable logging" (`LoggingEnabled`) | `Engine\Mods\<id>` key root | absent = **off on every installed mod** (swept 130 keys) | that mod's own `Wh_Log()` lines |
| Per-mod "Detailed debug logs" (`DebugLoggingEnabled`) | same key root | absent = off on every mod | mod's verbose internals, in addition to mod logs |
| Toolkit auto-show (`DontAutoShowToolkit`) | `Settings` key | **0 = auto-show kept ON** | shows rescue dialog when taskbar isn't accessible |
| Toolkit hotkey (`DisableToolkitHotkey`) | `Settings` key | **0 = Ctrl+Win+W kept registered** | manual summon of the toolkit dialog |

Per-mod config values live on the mod key root (sample verified: `LibraryFileName, Disabled,
Include, Exclude, Architecture, Version, SettingsChangeTime`; logging bits absent).

## The toolkit

Not a mod-dev kit. It is Windhog's **built-in rescue dialog**: when the engine detects the taskbar
isn't accessible (system instability etc.) it pops automatically; Ctrl+Win+W summons it manually.
It can exit Windhound, switch to safe mode, and perform other recovery operations. Escape tools
around it: `windhawk.exe -safe-mode` (loads the app with zero mods), `-exit [-wait]`,
`-restart [-tray-only]`, and `command-line.txt` documents all of them.

## Windhog CLI (new in 2.0, `windhog-cli.exe`)

- `mod list/show/enable/disable/remove/config/settings/user-config/install/update/compile`
  - `mod config <id>` exposes boolean fields including `loggingEnabled`/`debugLoggingEnabled`
    (field names confirmed in `windhog-core/cli/.../config.rs`).
  - `mod compile` recompiles an installed mod from its stored source; `--arch x64|arm64|all`.
- `app settings` reads/changes app-level settings (the `Settings` key).
- `source` operates directly on `.wh.cpp` files; `repo` queries the catalog; `update` handles
  Windhog updates; `data` exports/inspects user data.
- `windhog-cli.exe app capture-hotkey` prints the next keypress in mod hotkey syntax.

## Recommendation given to the owner (for the hunt)

1. Keep the toolkit as configured (auto-show + hotkey both currently enabled) - it is the escape
   hatch for exactly the "system became unreachable" symptom class.
2. Do not blanket-enable logging across all 130 mods. Enable per-mod `LoggingEnabled` only on the
   suspects (input-adjacent ones first: ignore-focus-loss, keyboard-shortcut-actions,
   force-kill-active-window, no-flash-window + whatever the round names), add
   `DebugLoggingEnabled` only if a specific mod's verbose output is needed.
3. App verbosity is already 2; leave engine verbosity at 0 unless a specific repro needs engine
   internals (its change is restart-class).
4. Attach a listener for boot-round capture: `DbgViewMini.exe --pattern "[WH] *" --no-buffering`
   redirected to a file, started elevated at run start.
5. Flip per-mod bits at a **round boundary**, not mid-run: config writes hot-reload the affected
   mod and shift its timing mid-experiment.

## Outcome (same day, 2:29-2:47 PM)

- Applied for real at the engine-down boundary, user-approved: `LoggingEnabled=1` on every
  installed mod key (130/130 verified at 2:29 PM; 129/129 at 2:35-2:45 PM - the parallel slimdown
  thread removed one mod meanwhile, and the count tracks it live). Backup + receipt:
  `H:\Windhawk Configuration\backups\2026-10-22\log-enable\`. Rollback: the script's `-Rollback`.
- The `[WH]` listener went live 2:30 PM (DbgViewMini v1.0.4, `windhog-dbgview-143006.txt`),
  end-to-end proven 2:33 PM by injecting a `[WH]` test line while the engine was down; the file
  grew 0 -> 158 bytes and the line came back verbatim. Continuous into the next engine boot.
- Scripts: `scripts\2026-10-22-windhawk-log-enable.ps1` (-Audit/-Apply/-Rollback),
  `scripts\2026-10-22-windhawk-dbgview-capture.ps1` (-Start/-Stop/-Status). Both ASCII-only, PS 5.1.
- Gotcha: running the capture script elevated via Invoke-Elevated times out the caller (~120 s)
  even though the work completes seconds later - read the elevated log under
  `backups\<date>-elevated\` as truth instead of waiting on the wrapper. Also, inside an already
  elevated child avoid `Start-Process -Verb RunAs` (the script was fixed to plain Start-Process).
- Handoff to the freeze thread: dated section appended to
  `H:\System Configuration\t3-handoff\2026-10-22-input-death-handoff.md` + coop note posted.
