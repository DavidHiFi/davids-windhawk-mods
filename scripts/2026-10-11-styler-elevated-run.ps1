<#
.SYNOPSIS
Elevate a script silently via a temp .cmd hop, logging by cmd redirection.

Invoke-Elevated.ps1 fails under the DSH sandbox because it writes its hop file
and log under H:\System Configuration\backups, which spawned processes cannot
write. This wrapper uses the same quoting pattern (a .cmd file, no
-ArgumentList array) but stages the hop in $env:TEMP and redirects at the cmd
level, so even a parse error inside the child lands in the log. Pass a
-WritableByChild log path the elevated child may write (workspace paths are
fine; the spawned caller's DSH temp is NOT shared with the child).

  Invoke-ElevatedTemp.ps1 -ScriptFile "H:\...\Build.ps1" -LogPath "H:\...\build-log.txt"
  Invoke-ElevatedTemp.ps1 -ScriptFile "H:\...\x.ps1" -ArgumentList "-Install" -LogPath "H:\...\install-log.txt"
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)] [string]$ScriptFile,
    [string]$ArgumentList = '',
    [Parameter(Mandatory = $true)] [string]$LogPath
)
$ErrorActionPreference = 'Stop'
if (-not (Test-Path $ScriptFile)) { throw "No such script: $ScriptFile" }

$inner = "& '$ScriptFile'"
if ($ArgumentList) { $inner += " $ArgumentList" }

$cmd = Join-Path $env:TEMP ("styler-elevated-{0}.cmd" -f [guid]::NewGuid().ToString('N'))
$content = 'powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "{0}" > "{1}" 2>&1' -f $inner, $LogPath
Set-Content -Path $cmd -Value $content -Encoding ascii
try {
    $p = Start-Process -FilePath $cmd -Verb RunAs -Wait -PassThru -WindowStyle Hidden
    Write-Output ("elevated exit={0}" -f $p.ExitCode)
}
finally {
    Remove-Item $cmd -ErrorAction SilentlyContinue
}
if (Test-Path $LogPath) { Get-Content $LogPath } else { Write-Output '(no log written - the child may have failed before running)' }
