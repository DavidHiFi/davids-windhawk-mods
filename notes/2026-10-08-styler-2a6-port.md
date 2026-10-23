# 2026-10-08 — Windhawk Styler ported to Windhawk 2.0.0-alpha.6 (Tauri UI), rev 30

Author thread: styler-port-2 (`work/windhawk-styler/tauri20/`). Follows
`notes/2026-10-08-styler-native-titlebar.md` (the 1.x record).

## What changed

The 2.0 UI is a **Tauri 3 / WebView2** app, not Electron. Window class
`WindhawkTauriMainUI`, webview child `WRY_WEBVIEW` below the native caption:

- Native caption present: HTCAPTION drag region + HTMINBUTTON/HTCLOSE zones,
  so real Windows-drawn caption buttons exist. On this machine the user's
  Catppuccin Mocha msstyles renders them as Catppuccin round dots (verified
  against charmap — same dot style on every DWM-buttoned window); maximized
  buttons are the same native rendering, so the old "XP glyph" problem cannot
  happen. That satisfies "real Windows buttons, no in-app clones".
- The webview sits under a 31 px caption; client covers nothing; no double
  title bar. `nativeTitleBar=0` under 2.0 would mean frameless, and the page
  has no fallback buttons of its own (tested: removing WS_CAPTION leaves no
  buttons at all), so the 2.0 edition treats native=1 as the complete look and
  native=0 as "color the page, don't touch the frame".

## How the 2.0 edition works (all runtime, zero file patching)

Source of truth: `work/windhawk-styler/tauri20/windhawk-styler.wh.cpp`
(revision 30, id `local@windhawk-styler`, Include=`windhawk-ui.exe`,
x86-64; built and deployed through `windhawk-cli.exe mod compile`).

1. **Window stack (in-process, same recipe proven in 1.x):**
   legacy `SetWindowCompositionAttribute` accent (state 4 acrylic, flags 2,
   color `0x10000000 | BGR(#1e1e2e)`), `DWMWA_SYSTEMBACKDROP_TYPE=3`,
   `DWMWA_USE_IMMERSIVE_DARK_MODE=1`, `DWMWA_CAPTION_COLOR=#1e1e2e`,
   `DWMWA_TEXT_COLOR=#cdd6f4`, `DWMWA_BORDER_COLOR=DWMWA_COLOR_NONE`.
   The legacy accent survives maximize, which keeps the maximized state
   uniform (measured, rest + maximized both).
2. **Frame-color watch:** a `DwmSetWindowAttribute` hook corrects the shell's
   own frame re-pushes (caption/text/border) back to the styler colors in the
   same call, so no gray strip or border flashes between activations. Cleared
   at uninit, so disabling the mod restores the stock look.
3. **Page theme over CDP:** at init the mod sets
   `WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS=--remote-debugging-port=9333`
   (process-scoped, before the webview is created — the UI must be started by
   `windhawk.exe` rather than attached to mid-flight, which is what actually
   happens: the engine spawns the UI). A worker thread in the UI process then
   connects to the WebView2 DevTools endpoint every 5 s and pushes, idempotently:
   - `Emulation.setDefaultBackgroundColorOverride` (alpha 0) → real transparent
     webview, so acrylic shows through; verified live (Firefox start page read
     blurred through the window).
   - `Runtime.evaluate` injecting a `<style id="wh-styler-style">` that drives
     the app's own `--whui-*` design tokens: body background
     `rgba(30,30,46,0.5)`, `font-family:'FiraCode Nerd Font'`,
     `--whui-card-background-color`, `--whui-primary`, antd component
     overrides (cards/buttons/switches/inputs). CSP allows it
     (`style-src 'unsafe-inline'`). Re-pushed every cycle so reloads heal.
4. **Settings live-reload:** the worker re-reads the registry settings every
   cycle (event-independent); `Wh_ModSettingsChanged` + worker both apply.
   Verified live: accent change → switches recolored within one cycle, then
   reverted.

## Measured final state (PrintWindow + on-screen, same session)

| surface | target | measured |
| --- | --- | --- |
| caption strip | #1e1e2e | (30,30,46) exact, both corners |
| caption title text | #cdd6f4 | (205,214,244) exact |
| switches | #89b4fa | (136,179,248) |
| cards/dialogs | #181825 | (24,24,37) exact |
| buttons/inputs | #313244 | (49,50,68) exact |
| page veil | rgba(30,30,46,0.5) over acrylic | computed style = rgba(30,30,46,0.5); on-screen (24,24,37) over dark |
| window font | FiraCode Nerd Font | computed style = "FiraCode Nerd Font" |
| border | none | edges show continuous acrylic tones, no accent line |
| bottom | no band | edges continuous; maximized uniform |

Captures: `reports/2026-10-08-styler-2a6-port/` (`rev30-final-full.png`,
`rev30-rest-screen.png` for the on-screen acrylic look,
`rev30-max-btns-6x.png` for the maximized native buttons, before-state
`before-*.png`).

## Setup facts (recorded, why + where)

- **Registry (HKCU, elevated write once):**
  `Software\Policies\Microsoft\Edge\WebView2\AdditionalBrowserArguments`
  value `windhawk-ui.exe` = `--remote-debugging-port=9333`. The mod's env var
  covers engine-spawned starts; the registry value is belt and braces for any
  launch path. Trade-off: while the Windhawk UI runs, a local process can
  speak CDP to it on 127.0.0.1:9333 (localhost only).
- **Mod key:** `HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler` →
  `LibraryFileName=local@windhawk-styler_2.0.0_*.dll` (the core's own
  revision number, currently 308518-generation builds from the synced source),
  `Include=windhawk-ui.exe`, enabled. Backup at
  `backups/2026-10-08/styler-rev30-deploy/`.
- **Racer mods excluded on this window** (they are Include=* and fight the
  caption/border on every activation): `win11-accent-border` and
  `win11-custom-title-bar-colours` now carry `Exclude: devenv.exe|
  windhawk-ui.exe`. Backups under `backups/2026-10-08/styler-rev30-titlebar-race/`.
- The 1.x rev 29 architecture (VSCodium file patching, tool host, heartbeat
  watchdog) is retired: 2.0 loads mods into windhawk-ui.exe directly, the
  tool-host problem is gone, and the old patch targets are dead files.
  Rev 29 DLLs remain on disk unused for rollback history.

## Deploy / workflow for the 2.0 edition

- Compile via the core: elevated
  `"C:\Program Files\Windhawk\windhawk-cli.exe" mod compile local@windhawk-styler`
  (compiles the synced `C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp`,
  bumps the key, hot-swaps the DLL in the running UI).
- Local tool build: `pwsh Build.ps1` in `work/windhawk-styler/tauri20/` (x64,
  `-EngineVersion 2.0.0` default).
- Source sync before compile is admin-only (ModsSource ACL); copy elevated.
- Fresh UI start picks up the env-var port; mid-flight attach means the CSS
  waits for the next UI start while DWM theming still applies.

## Known gaps / follow-ups

- Startup latency: the page shows the stock dark look for ~5–15 s after a new
  UI start until the first CSS push (screen shows acrylic as soon as the
  worker's first pass lands).
- The 2.0 UI has no setting of its own for fonts/colors; the styler's token
  overrides are the theme mechanism. If the upstream app adds namespace
  tokens, retarget `BuildCss`.
- Alt-drag: handled by the window-manager mod (loaded in windhawk-ui.exe,
  enabled), and the window is a standard framed window; not driven with
  synthetic input in this session per the workspace rules.
- If an upstream Windhawk update ships a different `--whui-*` token set or
  embeds a new renderer, re-check `ExtractPageWsUrl`/`BuildCss` first.

## 19:55 final state — 2.0.1 rev "put-site-patch", verified

Architecture (v4, the one that lived):
- Surface transparency: windhawk-ui.exe .text scanned at init for the 3 inlined
  `call [rax+0xD8]` (Controller2 put_DefaultBackgroundColor, slot 27) sites;
  each patched to `call stub` where the stub (in the .text tail page padding,
  zero-filled, executable) does `mov dl,0` then TAIL-JUMPS to the original
  target (`jmp [rax+0xD8]`, FF A0 D8 00 00 00). Tail-jump keeps the stack byte
  identical to the original direct call: an extra call frame shifts rsp by 8
  and the runtime's `movaps [rsp+...]` faults with 0xc0000005 (the 19:35 crash).
  Alpha sits in the low byte of the by-value color (COREWEBVIEW2_COLOR A,R,G,B).
- Uninit restores every patch byte + cave. The shell's theme-change puts are
  covered too (site3 = apply_background_color path).
- Page CSS via CDP port 9333 (policy value + env var), CSS-first push with the
  injected JS returning "ok len=N" (the missing return caused "push failed").
- Save/settings-changed OR late mod attach -> ONE detached powershell helper
  (mutex-guarded) closes ALL windhawk-ui processes, then starts windhawk.exe
  (the engine path, which yields the debug port; direct windhawk-ui spawn does
  not). The broker process no longer spawns helpers (twin-window cause).
  Verified: exactly one helper spawn + one new UI pair per save; one visible
  WindhawkTauriMainUI after.
- Crash root causes fixed this session: 5-arg forward of the 6-arg internal
  export (garbage env -> QI crash), options-object misread as a handler
  (QI-shaped fn invoked with wrong arity), stack misalignment in the put stub.
- Compiler gotcha: @compilerOptions must list -lws2_32 or the CLI compile
  silently keeps the previous DLL (all "compile ok" runs log this).
- cdpPort no longer a setting (hardcoded 9333); stale value deleted from
  HKLM ...Settings. Policy value HKCU ...AdditionalBrowserArguments kept.
- No user-visible artifacts; crashes traced via disassembly, no debugger used.

Evidence:
- put sites patched (3) in every boot since 19:37:37, zero crashes since 19:37.
- Transparency proof: reports\2026-10-08-styler-2a6-port\over-white.png (white
  window blooms through the card gaps under the acrylic + veil).
- Final look: reports\2026-10-08-styler-2a6-port\final-look.png.
- Save round-trips: #89b4fa -> #f5c2e7 -> #89b4fa through two full UI restarts.
- Regenerate transparency proof any time: tauri20\test-transparent.ps1
  (white WinForms backdrop + client capture; careful: never Stop-Process pwsh
  by name on this box, the tool shell runs there).

## 20:36 — caption acrylic + the duplicate/relaunch saga solved

- Caption: DWMWA_CAPTION_COLOR with alpha composites as a SOLID strip on this
  build (measured spread 8 = solid); the fix is to not color the caption at
  all - DWMWA_COLOR_NONE - so Win11's system backdrop acrylic (set via
  DWMWA_SYSTEMBACKDROP_TYPE=3) owns the caption exactly like the client. The
  frame watch hook neutralizes the shell's own caption puts with COLOR_NONE.
  Measured after: caption spread 113-133 (real texture) vs 8 (solid).
- Relaunch helper (now): mutex-guarded single helper; closes ALL windhawk-ui
  (CloseMainWindow first, Stop-Process fallback), waits for windhawk's own
  msedgewebview2 (command line like *UIMainData*) to exit so a stale browser
  cannot be reused with old args, sets
  WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS=--remote-debugging-port=9333 itself,
  then starts windhawk-ui.exe via plain `& path` invocation (NOT
  Start-Process - it fails silently inside the CREATE_NO_WINDOW helper), then
  sweeps any extra windows, keeping only the newest. Restart2 covers a dead
  first spawn. Optionally engine (windhawk.exe) also spawns the UI, but only
  sometimes honors secondary launches - the direct spawn is the reliable path.
- The silent-helper-postmortem: three sequential instant-death causes, all
  fixed in this build:
  1) helper script buffer truncation (script[1024] -> grew past 2200, cut
     mid-quote -> unparseable base64). Buffers now 3200 + cmdLine[10240] with
     a "helper b64 len" DebugNote (~6516 now).
  2) Start-Process inside the 5.1 helper fails silently under CREATE_NO_WINDOW
     (the UI never started; plain & invocation works).
  3) Stale windhawk-owned msedgewebview2 kept alive after Stop-Process, so the
     reused browser carried no debug port (the 19:43 dead-port case).
- Save round-trips measured: pids replaced 10512/34256 -> 10456/14924, one
  visible window, style=YES len=1540, netstat 9333 LISTENING, caption spread
  113. Helper step log lives in %TEMP%\wh-styler-helper.log (leave it: it is
  the easiest place to triage a future save problem).
