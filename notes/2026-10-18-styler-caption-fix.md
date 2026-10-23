# Styler caption fix — 2026-10-18 (autonomous)

## What changed
- `nativeTitleBar` 1 -> 0 (HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler\Settings)
- `titleBarAcrylic` 1 -> 0
- `SettingsChangeTime` bumped to 0x6ad52364 (1792353124)
- Backup: backups\2026-10-18-styler-caption-fix\mod-key-before.reg
- Elevated script receipt: backups\2026-10-18-elevated\log-195201.txt

## Why
Both symptoms (dim native title-bar buttons always; missing hover state when maximized) had open root causes after the 10-17 investigation (notes\2026-10-17-styler-caption-investigation.md). The custom DWM-caption path (`DWMWA_CAPTION_COLOR=NONE` + acrylic + active-look force) is what makes Windows draw the caption buttons dull/low-opacity and suppresses the maximized hover overlay. Removing the custom caption (nativeTitleBar=0, titleBarAcrylic=0) lets DWM/Windows draw the title bar fully natively — buttons bright, hover states present in both normal and maximized states.

The styled body (cards, controls, text, background blur) stays intact because those are separate CSS injections; only the caption strip and caption child crop are disabled.

## Verification
- Registry read confirmed values 0x0 for both keys; SettingsChangeTime updated.
- Elevated execution exit=0 (Invoke-Elevated.ps1 log 195201).
- Source reference: work\styler-release\mods\local\windhawk-styler\windhawk-styler.wh.cpp lines 625-640 (caption color path conditional on nativeTitleBar) and 567-574 (caption CSS offset conditional on nativeTitleBar + titleBarAcrylic).

## Status
Registry fix applied. Windhawk UI window must be recreated (normal on settings save / mod reload) for the caption subclass to drop and DWM to restore native buttons fully. Visual verification should be done by creating a new screenshot after the window restarts; if buttons remain dim after recreation, the next step is to disable this mod entirely (body theming can be replicated with translucent-flyouts + theme-tool-plus instead) — not needed unless recreation fails.
