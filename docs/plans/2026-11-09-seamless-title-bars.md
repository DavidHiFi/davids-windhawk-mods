# Seamless Title Bars — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this
> plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Merge all seven enabled title-bar mods into one new mod, `local@seamless-title-bars`
("Seamless Title Bars"), with every option carried and every section individually toggleable.

**Architecture:** One tool-mod `.wh.cpp` (window-manager precedent): a single tool host part in
`windhawk.exe` plus in-process parts selected per host process. Eight code sections, each gated by
its own `<section>.enabled` setting and its own app list, so no engine-level exclusion list is
needed to separate sections. All per-section app exclusions are first-class settings.

**Tech stack:** Windhawk mod (C++/clang, x86-64), `windhawk_tool_mod.h`, Windhawk engine registry
(`HKLM\SOFTWARE\Windhawk\Engine\Mods`), PowerShell install script with `-Audit/-Install/-Rollback`.

**Spec:** Owner request 2026-11-09: merge ALL title bar mods into one mod named "Seamless Title
Bars", all options and functionality carried, sections individually toggleable, workspace mod
conventions (`docs\mod-style-guide.md`). Audit basis: the seven live mods and their engine keys
(read 2026-11-09, receipts in `backups\2026-11-09\` at install time).

## Global Constraints

- Id `local@seamless-title-bars`, name `Seamless Title Bars`, version 1.0.0.
- `@author DavidHiFi, Th3Fanbus, grn15RenS, Ingan121, Anixx, aubymori` (DavidHiFi first, then every
  upstream author in Credits).
- `@donateUrl https://ko-fi.com/DavidHiFi` right after `@homepage`.
- Tool-mod build ONLY via `windhawk-cli.exe mod compile` (elevated, under `coop lock
  windhawk-engine`); a hand-built DLL crashed the host. Async stderr read, hard
  `WaitForExit(15000)` then kill.
- `debugLog` stays 0 (install refuses otherwise) — required to load into dwm.exe.
- Never restart the engine or dwm by hand; per-mod hot reload only (bump `SettingsChangeTime`).
- The taskbar styler is unrelated here but every dock-family rule still applies: this work touches
  dwm.exe and explorer.exe, so all shell-risk rules are live; one change at a time, screenshot
  before/after.
- Before touching the engine key: `reg export` every old mod key and copy every old source into
  `backups\2026-11-09\seamless-title-bars\`.
- Settings text follows the StartPad style (`docs\reference\startpad-settings-block.yaml`): short
  plain `$name`, `$description` with range or on/off meaning, readable `$options` labels. Defaults
  in the schema are the LIVE values of the seven mods today; every value clamped in code.
- Never have both the old and new caption-button hooks active in dwm.exe at once: the install
  script disables all seven old mods in the same elevated run, before the new mod is enabled.

## Review Focus

The five failure modes most likely to bite, most likely first, with the test that pins each:

1. **dwm.exe injection dies silently.** With `@include *`, dwm.exe only matches when the engine
   key has `PatternsMatchCriticalSystemProcesses=1`. Miss it and buttons/titles revert everywhere
   with no error. Test: Task 5 step reads dwm.exe's module list for the new DLL name.
2. **Maximize/restore click regression** (the widthfix bug class: layout computed from a stale
   title-bar rect). The ported source is the live widthfix source (`ComputeLayout` uses
   `GetWindowRect`, line 1064). Test: Task 5 runs
   `scripts\2026-10-27-caption-settings-verify.ps1` after a maximize + restore and expects hit
   codes 8, 9, 20 at the right-edge spots.
3. **Flat colour painted over blur apps.** If the colours exclusion list loses one of
   `Discord*.exe, ESDDiscord.exe, FreeDictate.exe, chrome.exe, WindowsTerminal.exe`, a measured
   blur turns flat dark again (measured 2026-10-31). Test: Task 5 pixel-checks Terminal's bar and
   Helium's bar are NOT rgb(30,30,46).
4. **Double hooks in dwm.exe** (old and new caption machinery both active). Test: Task 5 readback
   shows `Disabled=1` on all seven old keys before the new mod's `Disabled=0` lands.
5. **Unsafe compile path.** Any build outside `windhawk-cli mod compile` (or a bare
   `WaitForExit()`) risks the host. Test: Task 3's command shape and timeout are the only build
   path, and the script asserts the DLL exists before install.

---

## The seven mods being merged (live state, 2026-11-09)

| Old mod | Version | Host include (engine) | Live extra engine values |
| --- | --- | --- | --- |
| `caption-buttons-customizer` | 1.1 (`1.1_widthfix` DLL) | dwm.exe\|explorer.exe (+IncludeCustom explorer.exe) | `PatternsMatchCriticalSystemProcesses=1` |
| `win11-custom-title-bar-colours` | 1.0.0 | `*`, Exclude devenv.exe, windhawk-ui.exe | `ExcludeCustom=Discord*.exe\|ESDDiscord.exe\|FreeDictate.exe\|chrome.exe\|WindowsTerminal.exe` |
| `local@remove-uwp-title-bars-plus` | 2.3.0 | ApplicationFrameHost.exe | — |
| `local@terminal-titlebar-blur` | 1.0.0 (tool mod) | windhawk.exe | — |
| `titlebar-for-everyone` | 0.5 | Chromium/Office/VS/Steam list | `IncludeCustom=Discord.exe\|DiscordPTB.exe\|DiscordCanary.exe\|DiscordDevelopment.exe` |
| `cef-titlebar-enabler-universal` | 2.0 | spotify.exe\|cefclient.exe | — |
| `fix-basic-caption-text` | 1.1.1 | `*` | — |

Audit resolutions folded into this plan:

- **Widthfix gap (closed):** the live ModsSource copy of `caption-buttons-customizer.wh.cpp` IS
  the widthfix source (`scripts\2026-10-27-caption-width-fix-install.ps1 -Apply` copied it in;
  `ComputeLayout` reads the real width via `GetWindowRect`, line 1064). Porting the live source
  carries the fix; nothing to reverse-engineer. The merged mod replaces the widthfix DLL, so the
  rollback must restore `LibraryFileName=caption-buttons-customizer_1.1_widthfix.dll` exactly.
- **Ghost excludes (resolved):** the colours exclusions are engine-level `ExcludeCustom` on the
  mod key, not mod settings — the 1.0.0 source never reads them. In the merged mod they become
  the `colours.excludedApps` setting (in code), so they are visible and editable.
- **Repo lag (noted, not this task):** `local@remove-uwp-title-bars-plus` 2.3.0 is uncommitted to
  davids-windhawk-mods. The merge supersedes it; commit the retirement alongside the release.

## New mod metadata

```
// @id              local@seamless-title-bars
// @name            Seamless Title Bars
// @description     One title bar everywhere: colours, caption buttons, native frames in every app kind
// @version         1.0.0
// @author          DavidHiFi, Th3Fanbus, grn15RenS, Ingan121, Anixx, aubymori
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         MIT
// @include         *
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -lcomctl32 -luxtheme -lgdi32 -lshlwapi -ldwmapi -luser32 -lole32 -lshell32 -loleaut32 -lruntimeobject -lversion
```

`@include *` + `@include windhawk.exe` mirrors `local@window-manager` (tool-mod host). Section
gates in code make the broad include safe; nothing acts outside its section's process list.

## Section layout (one gate per section, all in one file)

| Section | Setting group | Runs in | Ported from |
| --- | --- | --- | --- |
| Colours | `colours` | every process except `colours.excludedApps` | win11-custom-title-bar-colours |
| Caption buttons (layout + paint) | `buttons`, `buttonStyle` | dwm.exe (uDWM hooks), explorer.exe (image bridge) | caption-buttons-customizer parts 1–2 (live widthfix source) |
| Icon and title | `title` | dwm.exe + explorer.exe (same engine) | caption-buttons-customizer |
| Button exclusions | `exclusions` | (applies to the above) | caption-buttons-customizer |
| File Explorer tabs | `explorerTabs` | explorer.exe | caption-buttons-customizer |
| UWP apps | `uwp` | ApplicationFrameHost.exe | local@remove-uwp-title-bars-plus (incl. backdrop-window machinery) |
| Native frames | `nativeFrames` | processes matching `nativeFrames.apps` | titlebar-for-everyone |
| Spotify and CEF | `spotify` | spotify.exe, cefclient.exe | cef-titlebar-enabler-universal (incl. pipe + JS API) |
| Terminal bar | `terminalBar` | tool host (windhawk.exe), drives CASCADIA windows | local@terminal-titlebar-blur |
| Basic frames | `basicFrames` | every process | fix-basic-caption-text |
| Advanced | `debugLog` | — | caption-buttons-customizer |

Shared helpers written once: `SectionOn(name)` (reads `<name>.enabled`), `ExeMatches(list)`
(`PathMatchSpecW` on the process name, comma-separated, wildcards allowed), hex colour parser
(from terminal-titlebar-blur).

## Settings block (StartPad style; defaults = today's live values)

```yaml
- colours:
  - enabled: true
    $name: Enable colours
    $description: "Sets the title bar colour in apps that use the Windows title bar. When off, apps keep their own colours."
  - useImmersiveDarkMode: true
    $name: Dark mode title bars
    $description: "When on, title bars use the dark mode caption style."
  - activeColor: "#1E1E2E"
    $name: Active colour
    $description: "Title bar colour while a window is focused, as a hex colour like #1E1E2E."
  - inactiveColor: "#1E1E2E"
    $name: Inactive colour
    $description: "Title bar colour while a window is unfocused."
  - excludedApps: "Discord*.exe, ESDDiscord.exe, FreeDictate.exe, chrome.exe, WindowsTerminal.exe, devenv.exe, windhawk-ui.exe"
    $name: Excluded apps
    $description: "Comma-separated process names or wildcards. These apps keep their own title bar material (blur, custom bars) instead of a flat colour."
  $name: Colours
  $description: Title bar colour for standard Windows title bars.
- buttons:
  - enabled: true
    $name: Enable caption buttons
    $description: "When off, the caption buttons and the icon and title keep the Windows layout everywhere."
  - moveButtons: false
    $name: Move caption buttons to the left
    $description: "On = buttons move to the left side. Off = buttons stay in their default place on the right."
  - leftMargin: 0
    $name: Left margin (px)
    $description: Gap between the left window edge and the first button.
  - buttonTighten: 0
    $name: Tighten button spacing (px)
    $description: "0 = default spacing. Higher = buttons closer together (up to about 20, so the middle button stays usable). Meant for the circle and custom image styles."
  - order: minMaxClose
    $name: Button order
    $description: Order of the three buttons, counted from the left edge.
    $options:
    - closeMinMax: Close, minimize, maximize (macOS)
    - closeMaxMin: Close, maximize, minimize
    - minMaxClose: Minimize, maximize, close
  - showDialogClose: true
    $name: Show the close button on dialogs
    $description: "Applies to windows that only have a close button (message boxes, About windows). Off = the button is hidden; Alt+F4 and Esc still close the window."
  $name: Caption buttons
  $description: Position and order of the minimize, maximize and close buttons.
- buttonStyle:
  - style: windows
    $name: Caption button style
    $description: "Windows = the default glyphs. macOS = coloured circles. Custom images = your own images; a button without an image keeps its circle. Switching back to Windows takes effect after dwm.exe restarts (sign out and in)."
    $options:
    - macos: macOS style (circles)
    - custom: Custom images
    - windows: Windows default
  - minimizeColor: "#FEBC2E"
    $name: Minimize colour
    $description: "Hex colour of the minimize circle, e.g. #FEBC2E."
  - maximizeColor: "#28C840"
    $name: Maximize / restore colour
    $description: "Hex colour of the maximize/restore circle, e.g. #28C840."
  - closeColor: "#FF5F57"
    $name: Close colour
    $description: "Hex colour of the close circle, e.g. #FF5F57."
  - iconFolder: ""
    $name: Icon folder
    $description: "Only used with the Custom images style. Folder with minimize, restore, maximize and close images (.png, .jpg, .bmp). Optional state variants: close_hover, close_pressed, close_disabled."
  - minimizeIcon: ""
    $name: Minimize image (file)
    $description: Optional. Full path of an image file; overrides the folder for this button.
  - maximizeIcon: ""
    $name: Maximize image (file)
    $description: Optional. Full path; overrides the folder for this button.
  - restoreIcon: ""
    $name: Restore image (file)
    $description: Optional. Full path; overrides the folder for this button. Used when the window is maximized.
  - closeIcon: ""
    $name: Close image (file)
    $description: Optional. Full path; overrides the folder for this button.
  - restartDwmOnUnload: false
    $name: Restart dwm.exe when the mod is unloaded
    $description: "Off (recommended): the painted glyphs stay until dwm.exe restarts. On: dwm.exe ends when the mod is unloaded; the screen flickers briefly and apps stay open. dwm.exe is never restarted twice within 30 seconds."
  $name: Button style
  $description: How the caption buttons look - circles, your own images, or the Windows default.
- title:
  - titleAlign: center
    $name: Icon and title alignment
    $description: "Where the icon and title sit in the title bar. Left = right after the buttons."
    $options:
    - left: Left
    - center: Center
    - right: Right
  - dialogAlign: center
    $name: Icon and title alignment in dialogs
    $description: "Same as above, but only for windows that have just a close button."
    $options:
    - left: Left
    - center: Center
    - right: Right
  - centerOnText: true
    $name: Center the title text itself
    $description: "On = the title text is centered on the window (icon sits beside it). Off = the icon + title group is centered."
  - centerNudge: 0
    $name: Center fine-tune (px)
    $description: Positive moves the centered title right, negative moves it left.
  - iconPosition: beforeTitle
    $name: Icon position
    $description: "Where the window icon goes. Left/Right of the title keeps it attached to the title. Far left / Far right pins it to that edge."
    $options:
    - beforeTitle: Left of the title
    - afterTitle: Right of the title
    - farLeft: Far left
    - farRight: Far right
  - titleGap: 8
    $name: Gap after buttons (px)
    $description: Space between the last button and the icon/title group.
  - iconTitleGap: 5
    $name: Gap between icon and title (px)
    $description: Space between the icon and the title text.
  - rightEdgeGap: 8
    $name: Right edge gap (px)
    $description: Space between the right edge of the window and the icon/title group.
  - hideMode: off
    $name: Hide window icon and title
    $description: Choose what to hide in the title bar.
    $options:
    - off: Off (show both)
    - icon: Hide icon only
    - title: Hide title only
    - both: Hide both
  - iconClickable: true
    $name: Icon responds to click and double-click
    $description: "On = clicking the icon opens the window menu and double-clicking closes the window. Off = the icon acts like an empty part of the title bar (drag, double-click to maximize or restore)."
  $name: Icon and title text
  $description: Where the window icon and the title text are placed.
- exclusions:
  - excludedApps: ""
    $name: Excluded apps (process names)
    $description: "Comma-separated executable names. Every window of these apps keeps the default Windows button layout."
  - excludedClasses: "CabinetWClass"
    $name: Excluded window classes
    $description: "Comma-separated window class names, to exclude only specific windows of an app. CabinetWClass (File Explorer) is here by default; remove it to use left buttons in File Explorer."
  $name: Button exclusions
  $description: Apps and window classes that keep the default Windows button layout.
- explorerTabs:
  - enabled: true
    $name: Make caption buttons clickable in File Explorer
    $description: "On = the caption buttons can be clicked in File Explorer. Only works while Move caption buttons to the left is on and CabinetWClass is not excluded."
  - buttonsExtraMargin: 5
    $name: Extra left margin for File Explorer buttons (px)
    $description: "Moves the caption buttons right, in File Explorer only. About 5 aligns the circles with the nav arrows."
  - extraPx: 0
    $name: Shift tab bar and toolbar (px)
    $description: "0 = leave the tab bar and toolbar where they are. A positive value moves them right, scaled by DPI; about 145 clears the three buttons."
  $name: File Explorer tabs
  $description: Keeps the tab bar of File Explorer from blocking the buttons.
- uwp:
  - enabled: true
    $name: Enable UWP apps
    $description: "Normal Windows title bars in Store apps (Settings, Calculator, Photos). Turning off puts every open app window back the way it was."
  - blur: true
    $name: Blur material
    $description: Frosted acrylic title bars instead of a flat colour.
  - tint: 60
    $name: Tint strength
    $description: How much dark tint covers the blur, 0 to 100 percent.
  $name: UWP apps
  $description: Native title bars in Store apps.
- nativeFrames:
  - enabled: true
    $name: Enable native frames
    $description: "The standard Windows title bar in Chromium browsers, Office, Visual Studio, Steam, Discord and similar apps. New app lists need those apps restarted."
  - apps: "chrome.exe, brave.exe, msedge.exe, opera.exe, yandex.exe, whale.exe, supermium.exe, chromium.exe, devenv.exe, steamwebhelper.exe, PowerToys.*.exe, olk.exe, WebViewHost.exe, winword.exe, excel.exe, powerpnt.exe, msaccess.exe, onenote.exe, outlook.exe, mspub.exe, hwp.exe, Photos.exe, MuseScore*.exe, ms-teams.exe, Discord.exe, DiscordPTB.exe, DiscordCanary.exe, DiscordDevelopment.exe"
    $name: Apps
    $description: "Comma-separated process names or wildcards. The Discord entries carry over the old custom include list."
  - buttonFaceChrome: true
    $name: Chromium - paint the classic button face colour
    $description: "In Chromium browsers, paints the classic Windows button face colour behind the title and tab bar. Needs DWM frames, hardware acceleration, and 'Windows 11 Mica titlebar' in chrome://flags."
  - clientEdge: remove
    $name: Client edge
    $description: The thin sunken border around the window content.
    $options:
    - keep: Keep application behavior
    - add: Always show
    - remove: Always hide
  - steamToolFrames: true
    $name: Steam - hide tool window frames
    $description: Removes the frames of Steam's small tool windows.
  - steamScriptInject: false
    $name: Steam - allow script injection
    $description: "Only for the \"Change Window Parameters\" Millennium extension. Needs a Steam restart."
  $name: Native frames
  $description: Forces the standard Windows title bar in apps that draw their own.
- spotify:
  - enabled: true
    $name: Enable Spotify and CEF
    $description: Native frames and tweaks for Spotify. Options marked with * need a Spotify restart.
  - showframe: true
    $name: Native frames on the main window*
    $description: "Requires a Spotify restart to take effect."
  - showframeonothers: false
    $name: Native frames on other windows
    $description: Includes Miniplayer, DevTools and similar windows.
  - showmenu: true
    $name: Show the menu button*
    $description: When off, the Alt key no longer opens the Spotify menu either.
  - showcontrols: false
    $name: Show Spotify's own window controls*
    $description: The custom controls Spotify draws next to its title bar.
  - transparentcontrols: false
    $name: Transparent Spotify window controls
    $description: Makes Spotify's own window controls transparent.
  - transparentrendering: true
    $name: Transparent rendering*
    $description: "Makes the transparent parts of the web content transparent. Needs the Chrome runtime."
  - noforceddarkmode: false
    $name: Disable forced dark mode*
    $description: Stops Spotify from forcing dark mode on its UI.
  - forceextensions: true
    $name: Force Chrome extensions*
    $description: "Always enables Chrome extensions, regardless of the DevTools status. Needs the Chrome runtime."
  - blockupdates: false
    $name: Block automatic updates*
    $description: Stops Spotify from updating itself.
  - ignoreminsize: false
    $name: Ignore minimum window size
    $description: Allows resizing the window below the minimum size Spotify sets.
  - playbackspeed: "1"
    $name: (Deprecated) Playback speed
    $description: "A decimal number like 1.0. Needs an x64 Spotify client between 1.2.36 and 1.2.66."
  - allowuntested: false
    $name: (Advanced) Use unsafe methods on untested CEF versions*
    $description: May cause crashes. When off, a slower but safe method is used on untested versions.
  $name: Spotify and CEF
  $description: Native frames and tweaks for Spotify.
- terminalBar:
  - enabled: true
    $name: Enable Terminal bar
    $description: "Gives the Windows Terminal title bar the same acrylic blur as the window body. Needs a Terminal with a native title bar (Show tabs in the title bar off)."
  - tint: "#1e1e2e"
    $name: Tint colour
    $description: "The colour mixed into the blur, as a hex colour like #1e1e2e. Use your Terminal background colour for a seamless bar."
  - opacity: 85
    $name: Tint opacity
    $description: "How strong the tint is, 0 to 100. Match Terminal's body opacity for a seamless bar."
  $name: Terminal bar
  $description: Matches the Windows Terminal title bar to its blurred body.
- basicFrames:
  - enabled: true
    $name: Enable basic frames
    $description: "Fixes caption colours on windows without DWM frames (classic themes, UIRibbon text)."
  - smallIcons: true
    $name: Small window icons
    $description: Uses small icons on basic theme windows instead of downscaling large icons.
  $name: Basic frames
  $description: Correct caption colours on basic and non-DWM frames.
- debugLog: false
  $name: Write debug log
  $description: Writes detailed debug messages to the Windhawk log output. Turn on logging for this mod in Windhawk to see them.
```

## Settings migration map (old → new)

| Old mod | Old value(s) | New value(s) |
| --- | --- | --- |
| win11-custom-title-bar-colours | `UseImmersiveDarkMode=1` | `colours.useImmersiveDarkMode=1` |
| | `ActiveColour.R/G/B=30/30/46` | `colours.activeColor="#1E1E2E"` (computed from the three ints) |
| | `InactiveColour.R/G/B=30/30/46` | `colours.inactiveColor="#1E1E2E"` |
| | engine `ExcludeCustom` | `colours.excludedApps` (string, preserved verbatim) + engine split, see below |
| caption-buttons-customizer | `buttons.*` (9 values) | `buttons.*` same leaf names |
| | `buttonStyle.*` (10) | `buttonStyle.*` |
| | `titleText.*` (11) | `title.*` (same leaf names, group renamed) |
| | `exclusions.*` (2) | `exclusions.*` |
| | `explorerTabs.*` (3) | `explorerTabs.*` |
| | `debugLog=0` | `debugLog=0` |
| local@remove-uwp-title-bars-plus | `blur=1`, `tint=60` | `uwp.blur=1`, `uwp.tint=60` |
| local@terminal-titlebar-blur | `tint=#1e1e2e`, `opacity=85` | `terminalBar.tint`, `terminalBar.opacity` |
| titlebar-for-everyone | `btnfacechrome=1` | `nativeFrames.buttonFaceChrome=1` |
| | `clientedge=remove` | `nativeFrames.clientEdge=remove` |
| | `notoolwinsteam`, `nosteamhtmlinject` (defaults) | `nativeFrames.steamToolFrames=true`, `nativeFrames.steamScriptInject=false` |
| | engine `IncludeCustom` (Discord ×4) | folded into `nativeFrames.apps` default |
| cef-titlebar-enabler-universal | 12 settings, same names | `spotify.*` same leaf names |
| fix-basic-caption-text | `smallicons=1` | `basicFrames.smallIcons=1` |

The migration script copies whatever values exist under each old key at run time (so unlisted
tweaks survive), using this name map. Values absent from the registry keep the schema defaults.

### Engine key for the new mod (decided)

| Value | Setting |
| --- | --- |
| `Include` | `*` (from metadata; metadata also adds `windhawk.exe`) |
| `PatternsMatchCriticalSystemProcesses` | `1` — REQUIRED for dwm.exe injection with the `*` pattern |
| `ExcludeCustom` | `FreeDictate.exe\|WindowsTerminal.exe\|ESDDiscord.exe\|windhawk-ui.exe` — only processes no section needs |
| `Exclude` | empty — `devenv.exe` must stay injected (native frames), unlike the old colours mod's engine exclude |
| `LoggingEnabled` | `0` |

Per-section exclusions live in code (`colours.excludedApps` etc.), because engine exclusions are
all-or-nothing per process and `chrome.exe` needs native frames while its colours must not paint.

## Tasks

### Task 1: Scaffold the mod source

**Files:**
- Create: `H:\Windhawk Configuration\Windhawk\seamless-title-bars\local@seamless-title-bars.wh.cpp`

- [ ] **Step 1:** Write the metadata block (above), the readme (style-guide layout: intro, preview
  line `media/previews/local@seamless-title-bars.png`, Features with one bullet per section, Setup
  note that dwm.exe injection needs `PatternsMatchCriticalSystemProcesses`, Notes: Windows-glyph
  style switch needs a dwm restart, Spotify * options need a restart, Credits naming all five
  upstream mods), and the settings block (above, verbatim).
- [ ] **Step 2:** Check the text with the `humanizer` skill.
- [ ] **Step 3:** Verify: `@id`, `@author`, `@donateUrl` match Global Constraints; every section
  group starts with `enabled`; every `$description` states range or on/off effect.

### Task 2: Port the eight section engines

**Files:**
- Modify: `H:\Windhawk Configuration\Windhawk\seamless-title-bars\local@seamless-title-bars.wh.cpp`

**Interfaces:**
- Produces: `bool SectionOn(PCWSTR section)`, `bool ExeMatches(PCWSTR list)`,
  `bool ParseHexColor(PCWSTR, BYTE[4])`, and per-section `Init/Uninit/LoadSettings/ApplySettings`
  functions named `ColoursInit`, `ButtonsInit` (dwm+explorer parts), `UwpInit`, `NativeFramesInit`,
  `SpotifyInit`, `TerminalBarInit` (tool host), `BasicFramesInit`.

- [ ] **Step 1:** Write the shared helpers (`SectionOn`, `ExeMatches`, `ParseHexColor`) and the
  `#include <windhawk_tool_mod.h>` tool-host base at the end (window-manager pattern, line 5507).
- [ ] **Step 2:** Port each section's code from its live source unchanged except for: setting
  names per the migration map, the section gate around its `Init`, and the per-process app-list
  gate for NativeFrames and Spotify. The caption-buttons part is ported from the LIVE ModsSource
  copy (widthfix included; `ComputeLayout` keeps the `GetWindowRect` width at line 1064).
- [ ] **Step 3:** Wire `Wh_ModInit`/`Wh_ModUninit`/`Wh_ModSettingsChanged` to call each enabled
  section's Init/Uninit in order, each guarded by its own gate, so a disabled section never hooks
  anything.
- [ ] **Step 4:** Verify: grep the new file for each old `Wh_GetIntSetting`/`Wh_GetStringSetting`
  name and confirm each now reads the new `section.leaf` name; confirm zero references to old ids.

### Task 3: Compile

- [ ] **Step 1:** Under `coop lock windhawk-engine`, elevated:
  `windhawk-cli.exe mod compile local@seamless-title-bars` with stderr read asynchronously and
  `WaitForExit(15000)` then kill. Compile from the workspace copy per the tool-mod workflow
  (register the source first if windhawk-cli requires it).
- [ ] **Step 2:** Verify: exit 0, `local@seamless-title-bars_1.0.0_<hash>.dll` in
  `C:\ProgramData\Windhawk\Engine\Mods\64\`. Fix errors and repeat until clean (no timeouts, no
  bare waits).

### Task 4: Install script with -Audit / -Install / -Rollback

**Files:**
- Create: `H:\Windhawk Configuration\scripts\2026-11-09-seamless-title-bars.ps1`
- Create: `H:\Windhawk Configuration\backups\2026-11-09\seamless-title-bars\` (made by -Install)

- [ ] **Step 1:** Write the script. `-Audit` (default, read-only) prints: the seven old mod keys
  (Version, LibraryFileName, Disabled, Include/Exclude/IncludeCustom/ExcludeCustom), the new mod
  key state, and which DLL dwm.exe maps. `-Install` (elevated): `reg export` all seven keys plus
  `HKLM\SOFTWARE\Windhawk\Engine\Mods` subkey list, copy the seven live sources into the backup
  folder, copy the new source into `ModsSource`, run the settings migration (map above, reading
  live old values), write the engine values (table above), then in ONE elevated run: set
  `Disabled=1` on all seven old keys, set the new key `Disabled=0` and bump its
  `SettingsChangeTime`, bump each old key's `SettingsChangeTime` so they unload, read everything
  back and fail loudly on any mismatch, assert `debugLog=0` before touching dwm, assert the new
  DLL exists. `-Rollback` (elevated): set the new key `Disabled=1`, re-import each old key's
  exported values (`reg import` of the backups, which restores `LibraryFileName=...widthfix.dll`
  and the colours `ExcludeCustom` exactly), bump `SettingsChangeTime` on all, read back.
- [ ] **Step 2:** Run `-Audit` and verify it prints the expected seven-mod state.

### Task 5: Live install and on-screen verification

- [ ] **Step 1:** Run `scripts\2026-11-09-seamless-title-bars.ps1 -Install` elevated (via
  `Invoke-Elevated.ps1`), under `coop lock windhawk-engine`.
- [ ] **Step 2:** Verify injection: dwm.exe's module list contains
  `local@seamless-title-bars_1.0.0_*.dll`; readback shows all seven old keys `Disabled=1`.
- [ ] **Step 3:** Widthfix regression check: maximize + restore a window, then run
  `scripts\2026-10-27-caption-settings-verify.ps1` and expect hit codes 8, 9, 20 at the
  right-edge spots.
- [ ] **Step 4:** Captures (PrintWindow scripts, no input injection): Explorer (title centred,
  buttons right — CabinetWClass excluded), Windows Terminal focused AND unfocused (bar material
  intact, title centred), Settings app (UWP native frame + blur), Spotify (native frame), Helium
  and Discord (native frames, bar NOT flat `rgb(30,30,46)`), FreeDictate (own bar untouched).
  4x zoom on one title bar: text inside its border, buttons show resting + hover states.
- [ ] **Step 5:** Pixel checks: Settings caption reads `30,30,46`; Terminal and Helium bars do not.
- [ ] **Step 6:** Toggle test: turn `uwp.enabled` off and on in the registry (bump
  `SettingsChangeTime`), confirm a Settings window reverts and returns without a shell restart.

### Task 6: Retire the seven and record

**Files:**
- Create: `H:\Windhawk Configuration\notes\2026-11-09-seamless-title-bars.md`
- Create: receipt JSON in `backups\2026-11-09\seamless-title-bars\`

- [ ] **Step 1:** Only after Task 5 passes: leave the seven old keys `Disabled=1` (sources stay in
  `ModsSource`; no key deletion yet — that waits for the owner's confirmation). The taskbar-styler
  and dock-family rules are untouched by this work.
- [ ] **Step 2:** Write the note (what changed, verification evidence paths, rollback command) and
  the receipt JSON. Update `CURRENT-STATUS.md` mod-state section.
- [ ] **Step 3:** Prepare the davids-windhawk-mods release items for a later round: remove-uwp-plus
  2.3.0 commit backlog noted; new mod source + preview image go to the repo when the owner says.

## Self-review notes

- Spec coverage: all seven mods map to sections; every live registry value appears either in the
  defaults, the migration map, or the engine table; interlocks (seamless-flyouts blur, Terminal
  exclusions, settings-styler handshake inside remove-uwp code, dwm inclusion) are carried in the
  ported code and the colours exclusion default.
- The settings block is quoted in full because it IS the spec of what the owner can toggle; code
  bodies are deliberately referenced, not transcribed.
- Execution: native (I implement it in this session) — the sections share one file and one
  settings schema, and a shipped mistake lands in dwm.exe, so the fastest safe loop is me
  compiling and verifying each step here rather than handing interfaces to fresh contexts.
