# Windhawk isolation test for the repaint freeze (read-only then reversible)
# Applies auth.exe exclusion, relaunches Ente Auth plain, auto-reverts on the
# flag below being 0 via a later call. Transcript in reports.
Start-Transcript -Path 'H:\System Configuration\reports\2026-09-26-windhawk-exclusion-test.log' -Force
$ws = 'HKLM:\SOFTWARE\Windhawk\Engine\Settings'
"Exclude before: '$((Get-ItemProperty $ws).Exclude)'"
Set-ItemProperty $ws -Name Exclude -Value 'auth.exe'
Start-Sleep 2
"Exclude after : '$((Get-ItemProperty $ws).Exclude)'"
Stop-Process -Name auth -Force -ErrorAction SilentlyContinue
Start-Sleep 1
Start-Process 'C:\Program Files\Ente Auth\auth.exe'
'auth relaunched plain (no launcher, no nudge)'
Stop-Transcript
