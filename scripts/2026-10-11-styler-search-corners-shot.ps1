# Screenshot the Windhawk Styler UI with the search input focused, for the
# 2.0.40 search-corners fix. The UI window is found by title ('Windhawk',
# unique on this box), restored if minimized, and foregrounded BEFORE the CDP
# evaluate: the DOM focus + computed-style read happen in ONE evaluate, right
# before CopyFromScreen, so the app cannot blur the input in between (it blurs
# the search input when its window is background). Runs under PS 5.1 too.
#
#   .\2026-10-11-styler-search-corners-shot.ps1
#   .\2026-10-11-styler-search-corners-shot.ps1 -OutFile C:\temp\shot.png
param(
    [string]$OutFile = "C:\Users\localuser\AppData\Local\Temp\styler-2.0.40-search-corners.png",
    [int]$Port = 9333
)
$ErrorActionPreference = 'Stop'

Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public static class WinShot {
    private delegate bool EnumProc(IntPtr hWnd, IntPtr lParam);
    [DllImport("user32.dll")] private static extern bool EnumWindows(EnumProc cb, IntPtr lParam);
    [DllImport("user32.dll")] private static extern int GetWindowTextW(IntPtr hWnd, [MarshalAs(UnmanagedType.LPWStr)] StringBuilder sb, int max);
    [DllImport("user32.dll")] private static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint wpid);
    [DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
    [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
    [DllImport("user32.dll")] public static extern bool IsIconic(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT rect);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }

    // Top-level window whose title matches exactly; enumeration happens in C#
    // so the lookup behaves the same under PS 5.1 and PS 7.
    public static IntPtr FindByTitle(string title) {
        IntPtr found = IntPtr.Zero;
        EnumWindows(delegate(IntPtr h, IntPtr l) {
            var sb = new StringBuilder(256);
            GetWindowTextW(h, sb, 256);
            if (sb.ToString() == title) { found = h; return false; }
            return true;
        }, IntPtr.Zero);
        return found;
    }
    public static uint PidOf(IntPtr hWnd) { uint p; GetWindowThreadProcessId(hWnd, out p); return p; }
}
"@
[void][WinShot]::SetProcessDPIAware()

$hwnd = [WinShot]::FindByTitle('Windhawk')
if ($hwnd -eq [IntPtr]::Zero) { throw "no window titled 'Windhawk' found" }
$wpid = [WinShot]::PidOf($hwnd)
$procName = (Get-Process -Id $wpid -ErrorAction Stop).ProcessName
if ($procName -ne 'windhawk-ui') { throw "window 'Windhawk' is owned by $procName, not windhawk-ui" }
"hwnd: $hwnd pid: $wpid"

if ([WinShot]::IsIconic($hwnd)) {
    [void][WinShot]::ShowWindow($hwnd, 9)  # SW_RESTORE
    Start-Sleep -Milliseconds 500
    "restored from minimized"
}
$fg = [WinShot]::SetForegroundWindow($hwnd)
"SetForegroundWindow: $fg"
Start-Sleep -Milliseconds 600

# --- CDP: focus the search input and read computed styles in ONE evaluate ---
$targets = Invoke-RestMethod -Uri "http://127.0.0.1:$Port/json" -TimeoutSec 5
$page = $targets | Where-Object { $_.type -eq 'page' } | Select-Object -First 1
if (-not $page) { throw 'no page target on CDP' }
$ws = [System.Net.WebSockets.ClientWebSocket]::new()
$ct = [System.Threading.CancellationToken]::None
$ws.ConnectAsync([Uri]$page.webSocketDebuggerUrl, $ct).Wait()

function Send-Json([string]$s) {
    $bytes = [System.Text.Encoding]::UTF8.GetBytes($s)
    $seg = [ArraySegment[byte]]::new($bytes)
    $ws.SendAsync($seg, [System.Net.WebSockets.WebSocketMessageType]::Text, $true, $ct).Wait()
}
function Recv-Json {
    $buf = New-Object byte[] (4MB)
    $ms = [System.IO.MemoryStream]::new()
    do {
        $seg = [ArraySegment[byte]]::new($buf)
        $r = $ws.ReceiveAsync($seg, $ct).Result
        if ($r.MessageType -eq [System.Net.WebSockets.WebSocketMessageType]::Close) { throw 'closed' }
        $ms.Write($buf, 0, $r.Count)
    } while (-not $r.EndOfMessage)
    [System.Text.Encoding]::UTF8.GetString($ms.ToArray())
}

$js = @'
(function(){
  var input = document.querySelector(".ant-input-affix-wrapper > input.ant-input") || document.querySelector("input.ant-input");
  if (!input) return JSON.stringify({error:"no search input found"});
  input.focus();
  var wrap = input.closest(".ant-input-affix-wrapper");
  function cs(el){var c=getComputedStyle(el);return {borderColor:c.borderColor,boxShadow:c.boxShadow,outline:c.outline};}
  var out = {activeIsInput:(document.activeElement===input), input:cs(input), wrapper: wrap?cs(wrap):null};
  var ths = document.querySelectorAll("thead th");
  if (ths.length){
    var f=ths[0], l=ths[ths.length-1];
    out.thFirst={tl:getComputedStyle(f).borderTopLeftRadius, clip:getComputedStyle(f).backgroundClip};
    out.thLast={tr:getComputedStyle(l).borderTopRightRadius};
  }
  var row = document.querySelector(".ant-table-tbody tr td");
  out.table = row ? {tableBg:getComputedStyle(row.closest(".ant-table")).backgroundColor} : null;
  return JSON.stringify(out);
})()
'@
$enc = ConvertTo-Json $js -Compress
Send-Json ('{"id":1,"method":"Runtime.evaluate","params":{"expression":' + $enc + ',"returnByValue":true}}')
$deadline = (Get-Date).AddSeconds(20)
while ((Get-Date) -lt $deadline) {
    $obj = Recv-Json | ConvertFrom-Json
    if ($obj.id -eq 1) {
        "styles: " + $obj.result.result.value
        break
    }
}
$ws.Dispose()

# --- capture the window rect immediately after the focus evaluate ---
$rect = New-Object 'WinShot+RECT'
[void][WinShot]::GetWindowRect($hwnd, [ref]$rect)
$w = $rect.Right - $rect.Left
$h = $rect.Bottom - $rect.Top
if ($w -le 0 -or $h -le 0) { throw "bad window rect ${w}x${h}" }
Add-Type -AssemblyName System.Drawing
$bmp = New-Object System.Drawing.Bitmap $w, $h
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($rect.Left, $rect.Top, 0, 0, $bmp.Size)
$bmp.Save($OutFile, [System.Drawing.Imaging.ImageFormat]::Png)
$g.Dispose()
$bmp.Dispose()
"saved: $OutFile ($w x $h)"
