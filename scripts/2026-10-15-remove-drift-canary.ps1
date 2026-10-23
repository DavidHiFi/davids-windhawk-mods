<#
.SYNOPSIS
Retire the 2026-10-14 T3 drift canary for the old translucent-windows id. The
id is gone after the 2026-10-15 migration; the re-pointed TranslucentWindowsGuard
(every 5 min + logon) supersedes it. Run elevated.
#>
$ErrorActionPreference = 'Stop'
$name = 'translucent-windows drift check'
$t = Get-ScheduledTask -TaskName $name -ErrorAction SilentlyContinue
if ($t) {
    Unregister-ScheduledTask -TaskName $name -Confirm:$false
    "canary task removed: $name"
} else {
    "canary task not present: $name"
}
"translucent guard task: $((Get-ScheduledTask -TaskName 'TranslucentWindowsGuard' -ErrorAction SilentlyContinue).State)"
