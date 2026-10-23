# Worker liveness probe: if the tool's Worker tracks the window, Effect()
# re-asserts DWMWA_CAPTION_COLOR (=0xFFFFFFFF in native+blur) every 5s.
# An unset attr returns ERROR_NOT_FOUND (0x80070049 via HRESULT, or -1 here).
param([string]$OutDir = "H:\Windhawk Configuration\reports\2026-10-08-native-vs-custom")
$ErrorActionPreference = 'Stop'
Add-Type @'
using System;using System.Runtime.InteropServices;using System.Text;
public class V{
public delegate bool CB(IntPtr h,IntPtr l);
[DllImport("user32.dll")] public static extern bool EnumWindows(CB cb,IntPtr l);
[DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr h,out uint p);
[DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
[DllImport("user32.dll")] public static extern bool IsIconic(IntPtr h);
[DllImport("user32.dll")] public static extern IntPtr GetWindow(IntPtr h,uint f);
[DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr h,StringBuilder s,int n);
[DllImport("dwmapi.dll")] public static extern int DwmGetWindowAttribute(IntPtr h,int a,out int v,int s);
}
'@
$script:vs = @(Get-CimInstance Win32_Process -Filter "Name='VSCodium.exe'" | ForEach-Object { [int]$_.ProcessId })
$script:found = [IntPtr]::Zero
$cb = [V+CB] { param($w, $l)
    if ($script:found -ne [IntPtr]::Zero) { return $true }
    if (-not [V]::IsWindowVisible($w)) { return $true }
    $wp = [uint32]0; [void][V]::GetWindowThreadProcessId($w, [ref]$wp)
    if ($script:vs -contains [int]$wp) {
        $sb = New-Object System.Text.StringBuilder 256
        [void][V]::GetWindowText($w, $sb, 256)
        if ($sb.ToString() -eq 'Windhawk' -and -not [V]::IsIconic($w) -and [V]::GetWindow($w, 4) -eq [IntPtr]::Zero) { $script:found = $w }
    }
    return $true
}
[void][V]::EnumWindows($cb, [IntPtr]::Zero)
$vh = $script:found
if ($vh -eq [IntPtr]::Zero) { 'no window'; exit 1 }
$pid2 = 0; [void][V]::GetWindowThreadProcessId($vh, [ref]([uint32]$pid2))
$p = Get-Process -Id $pid2 -ErrorAction SilentlyContinue
"path: $($p.Path)"
$c = 0; $hr = [V]::DwmGetWindowAttribute($vh, 35, [ref]$c, 4)
"CAPTION_COLOR attr35 hr=0x$($hr.ToString('X8')) value=0x$($c.ToString('X8'))"
$b = 0; $hr2 = [V]::DwmGetWindowAttribute($vh, 38, [ref]$b, 4)
"BACKDROP attr38 hr=0x$($hr2.ToString('X8')) value=$b"
# veil popup by class
$found2 = [IntPtr]::Zero
$cb2 = [V+CB] { param($w, $l)
    $sb = New-Object System.Text.StringBuilder 256
    [Runtime.InteropServices.Marshal]::GetLastWin32Error() | Out-Null
    return $true }
Add-Type @'
using System;using System.Runtime.InteropServices;using System.Text;
public class V2{
public delegate bool CB(IntPtr h,IntPtr l);
[DllImport("user32.dll")] public static extern bool EnumWindows(CB cb,IntPtr l);
[DllImport("user32.dll",CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr h,StringBuilder s,int n);
[DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h,out RECT r);
[DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr h);
public struct RECT{public int L,T,R,B;}
}
'@
$cb3 = [V2+CB] { param($w, $l)
    $sb = New-Object System.Text.StringBuilder 256
    [void][V2]::GetClassName($w, $sb, 256)
    if ($sb.ToString() -eq 'WindhawkStylerVeil') {
        $r = New-Object V2+RECT; [void][V2]::GetWindowRect($w, [ref]$r)
        $script:veil = "($($r.L),$($r.T))-($($r.R),$($r.B)) $($r.R-$r.L)x$($r.B-$r.T) visible=$([V2]::IsWindowVisible($w))"
    }
    return $true }
$script:veil = ''
[void][V2]::EnumWindows($cb3, [IntPtr]::Zero)
"veil popup: $(if ($script:veil) { $script:veil } else { 'NOT FOUND' })"
