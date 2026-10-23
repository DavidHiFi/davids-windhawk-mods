# Captures OutputDebugString lines from every process (Windhawk engine and mod Wh_Log)
# for a fixed time, keeping only lines that mention the tree-item mod or the engine.
# Read-only diagnostic: it does not change any mod, setting or process.
#
#   pwsh -File scripts\2026-10-12-treeitem-dbwin-capture.ps1 -Seconds 150 -Out reports\2026-10-12-treeitem\dbwin.txt

param(
    [int]$Seconds = 150,
    [Parameter(Mandatory = $true)][string]$Out
)

Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class DbwinNative {
    [DllImport("kernel32.dll", SetLastError = true)] public static extern IntPtr CreateFileMapping(IntPtr h, IntPtr sec, uint protect, uint maxHi, uint maxLo, string name);
    [DllImport("kernel32.dll", SetLastError = true)] public static extern IntPtr MapViewOfFile(IntPtr h, uint access, uint offHi, uint offLo, uint size);
    [DllImport("kernel32.dll", SetLastError = true)] public static extern IntPtr CreateEvent(IntPtr attr, bool manual, bool initial, string name);
    [DllImport("kernel32.dll")] public static extern bool SetEvent(IntPtr h);
    [DllImport("kernel32.dll")] public static extern uint WaitForSingleObject(IntPtr h, uint ms);
}
"@

$bufReady = [DbwinNative]::CreateEvent([IntPtr]::Zero, $false, $true, 'DBWIN_BUFFER_READY')
$dataReady = [DbwinNative]::CreateEvent([IntPtr]::Zero, $false, $false, 'DBWIN_DATA_READY')
$map = [DbwinNative]::CreateFileMapping([IntPtr](-1), [IntPtr]::Zero, 0x04, 0, 4096, 'DBWIN_BUFFER')
$view = [DbwinNative]::MapViewOfFile($map, 0x000F001F, 0, 0, 4096)
if ($view -eq [IntPtr]::Zero) {
    Set-Content -Path $Out -Value 'MapViewOfFile failed: could not open the DBWIN buffer.'
    exit 1
}

$outDir = Split-Path -Parent $Out
if ($outDir -and -not (Test-Path $outDir)) { New-Item -ItemType Directory -Path $outDir | Out-Null }
Set-Content -Path $Out -Value ("capture started {0:yyyy-MM-dd HH:mm:ss} for {1}s" -f (Get-Date), $Seconds)

$deadline = (Get-Date).AddSeconds($Seconds)
[DbwinNative]::SetEvent($bufReady) | Out-Null
while ((Get-Date) -lt $deadline) {
    if ([DbwinNative]::WaitForSingleObject($dataReady, 500) -eq 0) {
        $pid2 = [Runtime.InteropServices.Marshal]::ReadInt32($view)
        $text = [Runtime.InteropServices.Marshal]::PtrToStringAnsi([IntPtr]::Add($view, 4))
        if ($text -match 'Tree|treeitem|Windhawk|windhawk|Wh_|mod initialized|failed') {
            Add-Content -Path $Out -Value ("{0:HH:mm:ss.fff} [{1}] {2}" -f (Get-Date), $pid2, $text.TrimEnd())
        }
        [DbwinNative]::SetEvent($bufReady) | Out-Null
    }
}
Add-Content -Path $Out -Value ("capture ended {0:yyyy-MM-dd HH:mm:ss}" -f (Get-Date))
