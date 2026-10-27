# 2026-10-27 taskbar visualizer: put build _1.3.3_6 live (one tool process, launched only by the taskbar explorer.exe). Run elevated.
# Rollback: this script -Rollback (back to _1.3.3_5, the crash-guard build).
param([switch]$Rollback)
if ($Rollback) {
    & 'H:\Windhawk Configuration\scripts\2026-10-27-taskbar-visualizer-apply.ps1' -Mode Apply `
        -NewLib 'local@taskbar-audio-visualizer_1.3.3_5.dll' `
        -BuildDir 'H:\Windhawk Configuration\reports\2026-10-27-visualizer-crash\build5' `
        -Source 'H:\Windhawk Configuration\work\2026-10-27-visualizer-crash\local@taskbar-audio-visualizer.wh.cpp'
} else {
    & 'H:\Windhawk Configuration\scripts\2026-10-27-taskbar-visualizer-apply.ps1' -Mode Apply `
        -NewLib 'local@taskbar-audio-visualizer_1.3.3_6.dll' `
        -BuildDir 'H:\Windhawk Configuration\reports\2026-10-27-visualizer-single\build6' `
        -Source 'H:\Windhawk Configuration\work\2026-10-27-visualizer-single\local@taskbar-audio-visualizer.wh.cpp'
}
