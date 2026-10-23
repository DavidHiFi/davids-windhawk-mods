# Notepad++ Save/confirm dialog text color fix

Date: 2026-09-22
Status: **Verified — user confirmed text is readable**

## Problem

Notepad++ 8.9.8 dark-mode Save/confirm dialogs showed dark-on-dark body text (unreadable). Evidence: `reports/npp-save-dialog-orig.png`.

## Fix

Windhawk mod **npp-taskdlg-textcolor** v1.0.1 (GetThemeColor-only).

- Source: `Windhawk/npp-taskdlg-textcolor.wh.cpp`
- DLL: `Windhawk/npp-taskdlg-textcolor_1.0.1_2.dll`
- Installed to: `C:\ProgramData\Windhawk\ModsSource\` + `Engine\Mods\64\` + registry
- Scope: `@include notepad++.exe` only
- Hook: `GetThemeColor` forces dark `TMT_TEXTCOLOR` to `RGB(242,242,242)` for theme classes `TaskDialog*`, `Static`, `Button`

v1.0.0 (GetThemeColor + GetSysColor + CreateWindowExW + subclassing) crashed notepad++.exe (msvcrt AV) — disabled/superseded.

## Verification

- Reload/Save TaskDialog body text light and readable on dark background — **user confirmed**.
- Evidence: `reports/npp-dialog-after-fix3.png`
- N++ loads with mod + windhawk.dll in module list; no crash with v1.0.1.

## Side changes (restored)

- N++ `config.xml` Backup mode temporarily set to `action=0` / `isSnapshotMode=no` to try to force the exit prompt; **restored** from `backups/2026-09-22/notepad++-config.xml`.

## How to undo

1. Set registry `HKLM:\SOFTWARE\Windhawk\Engine\Mods\npp-taskdlg-textcolor` `Disabled=1`, or remove the mod.
2. Restart Windhawk (`windhawk.exe -restart`).
3. N++ config already restored.

## Notes

- Exit-path Save prompt was hard to trigger programmatically (UIA Close/Exit often closed without a visible dialog). Same MessageBox→TaskDialog path as Reload; color fix applies to both.
- Reload dialog capture proved the fix.
