$ErrorActionPreference = 'Continue'
# Identify only Windhawk's own WebView2 children by command line, kill them,
# kill any UI instance, then relaunch the UI elevated with the CDP flag seeded
# so the WebView2 browser child opens port 9333 for verification.
$targets = Get-CimInstance Win32_Process -Filter "Name='msedgewebview2.exe'" |
    Where-Object { $_.CommandLine -match 'Windhawk' }
foreach ($t in $targets) {
    Write-Output ("killing windhawk webview pid=" + $t.ProcessId)
    Stop-Process -Id $t.ProcessId -Force -ErrorAction SilentlyContinue
}
if (-not $targets) { Write-Output 'no windhawk webview processes matched' }
Get-Process windhawk-ui -ErrorAction SilentlyContinue | ForEach-Object {
    Write-Output ("killing windhawk-ui pid=" + $_.Id)
    Stop-Process -Id $_.Id -Force
}
Start-Sleep -Seconds 2
$env:WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS = '--remote-debugging-port=9333'
Start-Process 'C:\Program Files\Windhawk\windhawk-ui.exe'
Start-Sleep -Seconds 6
Get-Process windhawk-ui -ErrorAction SilentlyContinue |
    Select-Object Id, MainWindowTitle | Format-Table -AutoSize | Out-String
