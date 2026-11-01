# Remove UWP Title Bars Plus 2.2.0: title bar blur option (2026-11-01)

Owner asked for a settings option that turns the flat UWP title bar colour into a blur, plus a preview.

## Audit of 2.1.0
- Every native frame got the acrylic system backdrop (`DWMSBT_TRANSIENTWINDOW`). DWM draws that backdrop flat once the window loses focus, and Settings' own page blur (settings-styler-plus host backdrop brush) ignores focus, so the caption showed as a solid band next to a blurred page. The owner's screenshot: caption a flat 32 grey across the strip.
- Nothing else wrong found: hooks, restore path and icon thread are sound.

## Change
- New settings: `blur` (default off for public users) and `blurTint` (AARRGGBB, default `661E1E2E`).
- With blur on, each native frame gets the recipe measured on FreeDictate on 10/31: frame extended to -1, legacy blur-behind with an empty region (without it DWM paints the caption flat over the accent), the acrylic accent with the tint, system backdrop set to none. Turning the setting off or the mod off undoes all four. Settings changes apply to open windows live.
- `-lgdi32` added for the region calls.
- Source: `work\2026-11-01-uwp-titlebar-blur\remove-uwp-title-bars-plus.wh.cpp`.

## Install (measured 7:05 PM)
- `scripts\2026-11-01-uwp-titlebar-blur.ps1 -Install` elevated: lib `local@remove-uwp-title-bars-plus_2.2.0_864547.dll`, Disabled 0, blur 1, blurTint 661E1E2E (registry read back).
- Settings opened once by `work\...\capture-preview.ps1` under the desktop lock: ApplicationFrameHost loaded the 2.2.0 DLL, frame visible (cloak 0, style 0x14CF0000), icon, title and buttons drawn. Caption colour now follows the background, 38 to 51 across the strip, the same focused and unfocused. Captures: `settings-focused.png`, `settings-unfocused.png`, `preview.png`. Settings closed afterwards.

## Rollback
`scripts\2026-11-01-uwp-titlebar-blur.ps1 -Rollback` elevated (reinstalls 2.1.0 from `backups\2026-11-01\remove-uwp-title-bars-plus\`). To keep 2.2.0 without blur, set `blur` to 0 in the mod settings.

## Open
- Fork repo copy not updated: `davids-windhawk-mods` is checked out on another thread's branch (`peek-1-2-0-blur`). Copy the work source and `preview.png` into `mods/local/remove-uwp-title-bars-plus/` on main later.
- Freeze gate: FAIL on windows-animations (`Include=*`), pre-existing since 10/30 and owner-run. Not touched.
- AGENTS rule "every blur app stays in window-borders' Exclude list": window-borders 2.0 has an empty exclude list today, so that rule is not enforced for any blur app. Not changed here (another thread holds window-borders).
