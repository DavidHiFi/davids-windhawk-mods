# Settings window material fix (accent acrylic, stays dark when unfocused). Run elevated.
#   -Mod launchpad|dictate|clipboard -Install   back up installed source + registry key, install the patched source, verify
#   -Mod ... -Rollback                          reinstall the backed-up source
param([ValidateSet('launchpad','dictate','clipboard')][string]$Mod, [switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$ids    = @{ launchpad = 'local@seamless-launchpad'; dictate = 'local@seamless-dictate'; clipboard = 'local@seamless-clipboard-manager' }
$id     = $ids[$Mod]
$cli    = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$stage  = 'C:\Users\Public\settings-material'
$bk     = 'H:\Windhawk Configuration\backups\2026-11-11-settings-material'
$stored = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
New-Item -ItemType Directory -Force $bk | Out-Null
function WhCli([string[]]$a) {
    $ErrorActionPreference = 'Continue'
    $p = Start-Process $cli -ArgumentList $a -PassThru -WindowStyle Hidden -RedirectStandardOutput "$bk\cli.out" -RedirectStandardError "$bk\cli.err"
    try { $p.PriorityClass = 'BelowNormal' } catch {}
    if (-not $p.WaitForExit(600000)) { $p.Kill(); throw 'windhawk-cli timed out' }
    [pscustomobject]@{ Code = $p.ExitCode; Text = (Get-Content "$bk\cli.out","$bk\cli.err" -Raw -ErrorAction SilentlyContinue) }
}
function State {
    $p = Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
    $on = -not ($p.PSObject.Properties.Name -contains 'Disabled') -or $p.Disabled -eq 0
    "$(if ($on) {'enabled'} else {'disabled'}) v$($p.Version) $($p.LibraryFileName)"
}
if ($Install) {
    $stamp = Get-Date -Format 'yyyyMMdd-HHmm'
    Copy-Item $stored "$stored.bak-$stamp" -Force
    Copy-Item $stored "$bk\$Mod-installed-$stamp.wh.cpp" -Force
    Copy-Item $stored "$stage\$Mod-old.wh.cpp" -Force
    reg export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$bk\$Mod-key-$stamp.reg" /y | Out-Null
    "$Mod before: " + (State)
    $r = WhCli @('mod','install','--file',"$stage\$Mod.wh.cpp"); $r.Text
    if ($r.Code -ne 0) { throw "mod install failed ($($r.Code))" }
    "$Mod after: " + (State)
}
if ($Rollback) {
    $r = WhCli @('mod','install','--file',"$stage\$Mod-old.wh.cpp"); $r.Text
    "$Mod after rollback: " + (State)
}
