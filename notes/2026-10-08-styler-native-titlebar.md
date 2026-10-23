# 2026-10-08 — Windhawk Styler native title bar: root causes, fixes, and the 2.0 interruption

## What the user reported (native title bar enabled)
1. Weird light border/outline artifact around the Windhawk window.
2. A bar/block at the bottom of the window that does not exist in custom mode.
3. Acrylic/transparency not matching the custom-mode look.
4. On maximize the title bar buttons turn into tiny "old Windows / XP" glyphs.
5. (Earlier) alt-drag broken, later fixed by the user themselves (window-manager mod).

## Root causes found (all measured live, not guessed)
1. **The whole mod was dead since ~11:30 AM** — tool pid 21104 (rev 19 era spawn,
   10:14) retained its `windhawk-tool-mod_local@windhawk-styler` mutex while its
   worker was gone, so every later tool spawn died at Wh_ModInit
   (ERROR_ALREADY_EXISTS → exit). No tool ⇒ no file application, no veil popup,
   no Effect() re-asserts ⇒ the user saw raw NC frame zones, the accent border,
   and no blur, exactly matching screenshots 1 and 2.
2. **Border artifact** = `win11-accent-border` (Include=*; loaded inside
   VSCodium.exe, confirmed by PSAPI not tasklist which fails on wow64 and the
   '@' in the name) drawing AccentColorMenu 0xfab489 = #89b4fa via
   DWMWA_BORDER_COLOR on WM_ACTIVATE. Visible only in native mode because the
   custom (frameless) window edge is already painted and the mod-dead state had
   no veil popup to mask the outer frame band.
3. **Win11-accent border race:** the accent mod re-applies on activation from
   inside VSCodium; external COLOR_NONE re-asserts from the tool raced and lost.
4. **Caption+buttons painted by Chromium, not DWM** — DWMWA_CAPTION_COLOR /
   DWMWA_TEXT_COLOR were inert (proved with red/green caption probes: no visual
   change). VS Code's workbench draws its own NC for titleBarStyle:native on
   this build; its buttons rendered as three muted tan/green/red dots
   (per-Keybar-like circles), ~32px, HTMIN/HTMAX/HTCLOSE confirmed by
   WM_NCHITTEST, and as tiny boxed glyphs when maximized = the "XP" complaint.
5. **Bottom band** = the veil popup's opaque bottom/side zone in rev 19 plus the
   reserved-hidden-titlebar slot painted by the html canvas; tone mismatch vs
   the veiled glass client read as a band.
6. **Maximize glass drop** = the Electron backgroundMaterial + DWMSBT path loses
   material on maximize; the legacy accent (custom-mode stack) does not.

## The fix that works (Windhawk 1.x architecture) — mods rev 23→29 stack
- Native title bar = **Window Controls Overlay**: keep the exact custom-mode
  window (transparent:!0, no frame, legacy accent acrylic, page veil), inject
  `titleBarStyle:"hidden" + titleBarOverlay{color,symbolColor,height}` in
  main.js and `window.titleBarStyle:custom + window.titleBarOverlay` +
  `workbench.colorCustomizations{titleBar.active/inactiveBackground:#1e1e2e}`
  in settings.json. Windows then draws REAL system caption buttons over the
  acrylic; the page stays uniform; no NC zones, no vl popup (want=false),
  no caption color for other mods to fight (DWM attributes inert by design).
- Overlay color must be **opaque**; WCO falls back to system gray (60,60,60) =
  #3C3C3C otherwise. `symbolColor` must be a real hex ("#cdd6f4") — the earlier
  "#205,214,244" format was invalid and silently broke the whole overlay.
- `workbench.colorCustomizations.titleBar.*Background = #1e1e2e` drives the
  app's own forged overlay color (themeMainService splash colorInfo), taming
  the button-zone background to match the veil (measured (30,30,46) zone on a
  (27-30,27-30,39-48) glassy surround).
- Reliability: tool heartbeat (HKLM\SOFTWARE\Windhawk\ToolPings\<id>, volatile,
  KEY_WOW64_64KEY both ways), stale-owner takeover (TerminateProcess old pid),
  tray watchdog re-spawn (verified: killed tool 29780 → respawned in ~18s),
  lock-free Wh_ModSettingsChanged (ApplyFiles outside g_guard).
- Verified live 13:23-13:31 under 1.7.3: native rest = clean uniform strip
  (33.7,34.9,50.3) matching custom; maximize = uniform (29-31,30-31,44-46) with
  real WCO buttons (m/M/X at standard width); no border artifact; no bottom
  band vs body; backdrop=3 acrylic everywhere (shimmer verified earlier).

## The interruption: Windhawk switched to 2.0.0-alpha.6 mid-deploy
- Another thread (windhawk-2a6-update) staged and switched the live engine at
  ~13:34 despite the coop request to wait; windhawk.exe/all helpers replaced
  13:00:30-13:01:06 (this is the 2.0 binary set).
- Windhawk 2.0 replaces the UI app with `windhawk-ui.exe` (own 13 MB binary).
  Our VSCodium.exe-based patch tree no longer runs: direct launch of
  UI\VSCodium.exe exits instantly (0 processes), windhawk-ui.exe shows no
  window (2 instances), VSCodium processes count = 0. The styler's patches are
  harmless dead weight under 2.0.
- Bisection proved: under 2.0, the mod's rev-28 patches (WCO injects) kept the
  UI dead; removing the VSCodium-loaded suppressor hook (rev 29) plus the clean
  uninstall (files stripped, settings clean, Disable=1 then re-enabled after)
  restored UI behavior under 2.0 — but the **UI did not return even with the
  mod fully disabled**, so the 2.0-install state itself is currently broken
  (no visible UI at all, last check 13:57).
- Note: `windhawk-ui.exe` 2.0-alpha shows no window on this machine right now
  (semi-migrated alpha). The styler under 2.0 needs a redesign of its file
  patch target (out of scope today).

## End state on disk/registry (intentional, safe)
- Mod enabled, rev 29 DLL (`local@windhawk-styler_1.5.0_29.dll`), source
  synced to C:\ProgramData\Windhkawk\ModsSource\local@windhawk-styler.wh.cpp.
- All UI file patches STRIPPED (clean app files), settings.json clean —
  Wh_ModUninit confirmed working; nativeTitleBar=0 in Settings.
- Tool heartbeat mechanism live (HKLM\SOFTWARE\Windhkawk\ToolPings\local@
  windhawk-styler, Pid/Time). Tray watchdog active from any windhawk.exe
  main-process instance.
- Builds are in work\windhawk-styler\native-v15 (rev 20-29 + deploy-*.ps1,
  all hash-verified copies).
- If Windhawk 1.7.3 is restored (winget supports 1.7.3), the styler's rev 29
  re-applies everything on the next UI start with nativeTitleBar=1 (flip via
  scripts\2026-10-08-styler-native-titlebar.ps1 -Value 1).

## Open items
- The 2.0 UI port (new windhawk-ui.exe architecture) — new project.
- Windows 11 accent border on the Windhawk window in native mode: with WCO the
  border equals the custom-mode look (user's own design choice); if ever needed
  natively-only, the clean path is excluding VSCodium.exe/windhawk-ui.exe from
  win11-accent-border (no hook, no race), not in-process swallowing.
- The user may still want alt-drag + maximize verification on the restored
  1.7.3 environment: window-manager alt-drag handled by the user (already
  verified by them in custom mode), WCO-mode = frameless, same as custom.
