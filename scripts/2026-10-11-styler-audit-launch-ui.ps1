# Launch the Windhawk UI detached with the styler CDP env var set.
# Runs elevated via Invoke-Elevated.ps1 so the process escapes the caller's
# sandbox job; the styler mod also seeds the same env var in Wh_ModInit.
$env:WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS = '--remote-debugging-port=9333'
Start-Process 'C:\Program Files\Windhawk\windhawk-ui.exe'
Start-Sleep -Seconds 3
"launched windhawk-ui pid=$((Get-Process windhawk-ui -ErrorAction SilentlyContinue).Id)"
