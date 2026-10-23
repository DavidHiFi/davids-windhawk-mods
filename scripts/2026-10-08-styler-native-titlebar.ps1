# Flip the Windhawk Styler nativeTitleBar setting and wait for the UI window
# to restart on the new mode. Run elevated:
#   Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-08-styler-native-titlebar.ps1" -ArgumentList "-Value 0"
# Logs to reports\2026-10-08-native-vs-custom\flip-<Value>.log
param(
    [Parameter(Mandatory = $true)][int]$Value,
    [string]$OutDir = "H:\Windhawk Configuration\reports\2026-10-08-native-vs-custom"
)
$ErrorActionPreference = 'Stop'
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
$log = Join-Path $OutDir "flip-$Value.log"
if (Test-Path $log) { Remove-Item $log }
function L($m) { $m | Tee-Object -FilePath $log -Append }

Add-Type @'
using System;using System.Runtime.InteropServices;using System.Text;
public class W{
public delegate bool CB(IntPtr h,IntPtr l);
[DllImport("user32.dll")] public static extern bool EnumWindows(CB cb,IntPtr l);
[DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h,out uint p);
[DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
[DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
[DllImport("user32.dll")] public static extern IntPtr GetWindow(IntPtr h,uint f);
[DllImport("user32.dll")] public static extern int GetWindowLong(IntPtr h,int i);
[DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h,StringBuilder s,int n);
}
'@

$script:vs = @(Get-CimInstance Win32_Process -Filter "Name='VSCodium.exe'" | ForEach-Object { [int]$_.ProcessId })
$script:found = [IntPtr]::Zero
$cb = [W+CB] { param($w, $l)
    if ($script:found -ne [IntPtr]::Zero) { return $true }
    if (-not [W]::IsWindowVisible($w)) { return $true }
    $wp = [uint32]0; [void][W]::GetWindowThreadProcessId($w, [ref]$wp)
    if ($script:vs -contains [int]$wp) {
        $sb = New-Object System.Text.StringBuilder 256
        [void][W]::GetWindowText($w, $sb, 256)
        if ($sb.ToString() -eq 'Windhawk' -and -not [W]::IsIconic($w) -and [W]::GetWindow($w, 4) -eq [IntPtr]::Zero) { $script:found = $w }
    }
    return $true
}

function Find-WhWindow {
    $script:vs = @(Get-CimInstance Win32_Process -Filter "Name='VSCodium.exe'" | ForEach-Object { [int]$_.ProcessId })
    $script:found = [IntPtr]::Zero
    [void][W]::EnumWindows($cb, [IntPtr]::Zero)
    return $script:found
}

$old = Find-WhWindow
$oldPid = 0
if ($old -ne [IntPtr]::Zero) { [void][W]::GetWindowThreadProcessId($old, [ref]([uint32]$oldPid)) }
L ("old window pid=$oldPid handle=$old")

$tool = Get-CimInstance Win32_Process -Filter "Name='windhawk.exe'" | Where-Object { $_.CommandLine -match 'tool-mod.*local@windhawk-styler' }
if (-not $tool) { L "ERROR: styler tool process not running - aborting without change"; exit 2 }
L ("styler tool pid=" + ($tool.ProcessId -join ','))

$key = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler'
$stamp = [int][DateTimeOffset]::Now.ToUnixTimeSeconds()
Set-ItemProperty "$key\Settings" -Name nativeTitleBar -Value $Value -Type DWord
Set-ItemProperty $key -Name SettingsChangeTime -Value $stamp -Type DWord
L "bumped SettingsChangeTime=$stamp nativeTitleBar=$Value"

# Wait for the UI window to be recreated (new pid or new handle).
$deadline = (Get-Date).AddSeconds(75)
$new = [IntPtr]::Zero
$newPid = 0
while ((Get-Date) -lt $deadline) {
    Start-Sleep -Milliseconds 800
    $h = Find-WhWindow
    if ($h -ne [IntPtr]::Zero) {
        $p = 0; [void][W]::GetWindowThreadProcessId($h, [ref]([uint32]$p))
        if ($p -ne $oldPid -or $h -ne $old) { $new = $h; $newPid = $p; break }
    }
}
if ($new -eq [IntPtr]::Zero) {
    $still = Find-WhWindow
    $sp = 0; if ($still -ne [IntPtr]::Zero) { [void][W]::GetWindowThreadProcessId($still, [ref]([uint32]$sp)) }
    L ("NO-RESTART: window pid=$sp handle=$still still up after 75s; check tool logs")
    exit 3
}
Start-Sleep -Seconds 3
$st = [W]::GetWindowLong($new, -16)
$cap = if (($st -band 0x00C00000) -ne 0) { 'native(frame)' } else { 'frameless(custom)' }
L ("new window pid=$newPid handle=$new style=0x{0:X8} -> $cap" -f $st)
$rb = (Get-ItemProperty "$key\Settings").nativeTitleBar
L "registry nativeTitleBar now=$rb (wanted $Value)"
L "flip-$Value done"
exit 0
