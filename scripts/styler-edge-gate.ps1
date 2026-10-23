[CmdletBinding()]
param()
$ErrorActionPreference='Stop'
$root='H:\Windhawk Configuration'
$report="$root\reports\2026-10-09-styler-audit"
& "$root\scripts\styler-maintenance.ps1" -Audit | Out-Null
& "$root\scripts\2026-10-09-styler-verify.ps1" -Label 'edge-gate' -Activate -ProbeCaption | Out-Null
$probe=Get-Content "$report\edge-gate.json" -Raw | ConvertFrom-Json
$failures=[System.Collections.Generic.List[string]]::new()
if ($probe.sideInset -ne 0 -or $probe.bottomInset -ne 0) { $failures.Add('The restored window has a non-client edge gap.') }
if ($probe.captionProbe.growth -ne 0) { $failures.Add('Repeated activation leaks GDI objects.') }
if (!$probe.foreground) { $failures.Add('The captured interface is not the foreground window. Repeat when it can be brought forward.') }
$main=$probe.windows | Where-Object Class -eq 'WindhawkTauriMainUI' | Where-Object { $_.Visible -and !$_.Cloaked }
$settings=Get-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler\Settings'
$integrated=$settings.nativeTitleBar -and $settings.titleBarAcrylic
$veil=@($probe.windows | Where-Object { $_.Class -eq 'WindhawkStylerVeil' -and $_.Visible -and $_.Pid -eq $main.Pid })
if ($veil.Count) { $failures.Add('A detached caption overlay is still visible.') }
if ($integrated -and $probe.captionHeight -ne 0) { $failures.Add('The integrated caption still has a non-client top gap.') }
if (!$integrated -and $probe.captionHeight -le 0) { $failures.Add('The native caption is missing.') }
$raw=& "$root\work\windhawk-styler\tauri20\cdp-eval.ps1" -Expr "JSON.stringify({styled:!!document.getElementById('wh-styler-style'),content:document.body.innerText.length,errors:[...document.querySelectorAll('[role=alert],.ant-notification-notice,.ant-message-notice')].map(e=>e.innerText),overflow:document.documentElement.scrollWidth>innerWidth+1})"
$response=$raw | ConvertFrom-Json
$page=$response.result.result.value | ConvertFrom-Json
if (!$page.styled -or $page.content -lt 100) { $failures.Add('The WebView does not contain the themed interface.') }
if ($page.errors.Count) { $failures.Add('The interface reports an error notice.') }
if ($page.overflow) { $failures.Add('The page overflows horizontally.') }
[ordered]@{time=(Get-Date -Format o);passed=($failures.Count -eq 0);failures=@($failures);page=$page;
    screenshot="$report\edge-gate.png";geometry="$report\edge-gate.json"} |
    ConvertTo-Json -Depth 5 | Set-Content "$report\edge-gate-receipt.json" -Encoding UTF8
if ($failures.Count) { throw ($failures -join ' ') }
Write-Output 'PASS: installed source, theme, caption, edge geometry, GDI stability, and visible errors.'
