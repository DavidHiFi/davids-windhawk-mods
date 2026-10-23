[CmdletBinding()]
param([switch]$Audit,[switch]$Install,[switch]$Rollback)
$ErrorActionPreference = 'Stop'
$backup = 'H:\Windhawk Configuration\backups\2026-10-09\styler-audit'
$report = 'H:\Windhawk Configuration\reports\2026-10-09-styler-audit'
$name = 'WINDHAWK_USE_VSCODIUM_UI'
function Read-State {
    [ordered]@{time=(Get-Date -Format o);machine=[Environment]::GetEnvironmentVariable($name,'Machine');
        user=[Environment]::GetEnvironmentVariable($name,'User');
        styler=(Get-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler' |
            Select-Object Version,LibraryFileName,Include,Disabled)}
}
if ($Audit) { Read-State | ConvertTo-Json -Depth 4; return }
if (!$Install -and !$Rollback) { throw 'Choose -Audit, -Install or -Rollback.' }
New-Item -ItemType Directory -Force -Path $backup,$report | Out-Null
if ($Install) {
    if (!(Test-Path "$backup\startup-before.json")) {
        Read-State | ConvertTo-Json -Depth 4 | Set-Content "$backup\startup-before.json" -Encoding UTF8
        & reg.exe export 'HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment' "$backup\machine-environment.reg" /y | Out-Null
        if ($LASTEXITCODE) { throw 'Environment backup failed.' }
        & reg.exe export 'HKLM\SOFTWARE\Windhawk' "$backup\windhawk.reg" /y | Out-Null
        if ($LASTEXITCODE) { throw 'Windhawk backup failed.' }
        Copy-Item 'C:\ProgramData\Windhawk\ModsSource\local@windhawk-styler.wh.cpp' "$backup\installed-styler.wh.cpp"
        Copy-Item 'H:\Windhawk Configuration\work\windhawk-styler\tauri20\windhawk-styler.wh.cpp' "$backup\work-styler.wh.cpp"
    }
    [Environment]::SetEnvironmentVariable($name,$null,'Machine')
    if ([Environment]::GetEnvironmentVariable($name,'User') -eq '1') {
        [Environment]::SetEnvironmentVariable($name,$null,'User')
    }
} else {
    $before = Get-Content "$backup\startup-before.json" -Raw | ConvertFrom-Json
    [Environment]::SetEnvironmentVariable($name,$before.machine,'Machine')
    [Environment]::SetEnvironmentVariable($name,$before.user,'User')
}
Add-Type @'
using System;using System.Runtime.InteropServices;
public static class StylerEnvironment {
 [DllImport("user32.dll",CharSet=CharSet.Unicode,SetLastError=true)]
 public static extern IntPtr SendMessageTimeout(IntPtr hwnd,uint msg,IntPtr wp,string lp,uint flags,uint timeout,out IntPtr result);
}
'@
$result = [IntPtr]::Zero
[void][StylerEnvironment]::SendMessageTimeout([IntPtr]0xffff,0x1a,[IntPtr]::Zero,'Environment',2,2000,[ref]$result)
$state = Read-State
if ($Install -and ($state.machine -eq '1' -or $state.user -eq '1')) { throw 'Legacy UI override remains.' }
$state | ConvertTo-Json -Depth 4 | Set-Content "$report\startup-after.json" -Encoding UTF8
$state | ConvertTo-Json -Depth 4
