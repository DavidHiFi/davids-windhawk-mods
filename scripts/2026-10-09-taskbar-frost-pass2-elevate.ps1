# Launches the pass-2 Apply elevated, silently, with one pre-quoted string
# (the machine gotcha's manual route; Invoke-Elevated.ps1 flapped this session).
$argLine = '-NoProfile -ExecutionPolicy Bypass -File "H:\Windhawk Configuration\scripts\2026-10-09-taskbar-frost-pass2.ps1" Apply'
$p = Start-Process pwsh -ArgumentList $argLine -Verb RunAs -Wait -PassThru -WindowStyle Hidden
Set-Content 'H:\Windhawk Configuration\reports\2026-10-09-taskbar-frost-pass2\elevate-log.txt' -Value "elevated exit=$($p.ExitCode)" -Encoding UTF8
