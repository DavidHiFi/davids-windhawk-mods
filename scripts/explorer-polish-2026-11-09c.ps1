# 2026-11-09 Explorer polish, third pass. Run elevated (Invoke-Elevated.ps1), under `coop lock windhawk-engine`.
#   GPU Explorer View Plus 1.3.4 -> 1.3.5: faint crust tint inside the resting group heading outline.
#   File Explorer Styler Plus 1.10.3 -> 1.10.4: status dock fill 95% -> 60% so the window glass shows through.
#   Styler settings: command bar row gets a faint crust tint (controlStyles[11].styles[2]).
# -Action Rollback reinstalls the 1.3.4 / 1.10.3 sources and removes the tint.
# No Explorer restart: both mods hot reload.
param([ValidateSet('Install', 'Rollback', 'Audit')][string]$Action = 'Audit')
$ErrorActionPreference = 'Stop'
$work = 'H:\Windhawk Configuration\work\2026-11-09-explorer-polish\src'
$bk = 'H:\Windhawk Configuration\backups\2026-11-09-explorer-polish-c'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$base = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$sources = 'C:\ProgramData\Windhawk\ModsSource'
$stylerId = 'local@windows-11-file-explorer-styler-plus'
$gpuId = 'local@gpu-accelerated-explorer-view-plus'
$settings = "$base\$stylerId\Settings"
$log = "$bk\run.log"
$values = [ordered]@{
    'controlStyles[11].styles[2]' = @{ Old = $null; New = 'Background=#4011111B' }
}

New-Item $bk -ItemType Directory -Force | Out-Null
function Log([string]$m) { $line = "$(Get-Date -Format 'HH:mm:ss') $m"; $line; Add-Content $log $line }
function Get([string]$n) { (Get-Item $settings).GetValue($n) }
function Bump { Set-ItemProperty "$base\$stylerId" -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) }
function InvokeCli([string]$arguments, [int]$limit = 240000) {
    $si = [Diagnostics.ProcessStartInfo]::new(); $si.FileName = $cli; $si.Arguments = $arguments
    $si.UseShellExecute = $false; $si.CreateNoWindow = $true
    $si.RedirectStandardOutput = $true; $si.RedirectStandardError = $true
    $p = [Diagnostics.Process]::Start($si)
    $ot = $p.StandardOutput.ReadToEndAsync(); $et = $p.StandardError.ReadToEndAsync()
    if (-not $p.WaitForExit($limit)) { try { $p.Kill() } catch {}; Log "[$arguments] KILLED after $limit ms"; throw "CLI timed out" }
    Log "[$arguments] exit $($p.ExitCode) $($ot.Result.Trim()) $($et.Result.Trim())"
    if ($p.ExitCode) { throw "CLI failed: $arguments" }
}
function Show {
    foreach ($id in $stylerId, $gpuId) { $k = Get-ItemProperty "$base\$id"; Log "$id version=$($k.Version) lib=$($k.LibraryFileName)" }
    foreach ($n in $values.Keys) { Log "$n = $(Get $n)" }
}

Show
if ($Action -eq 'Audit') { return }

if ($Action -eq 'Install') {
    if (-not (Test-Path "$bk\styler-1.10.3.wh.cpp")) {
        Copy-Item "$sources\$stylerId.wh.cpp" "$bk\styler-1.10.3.wh.cpp"
        Copy-Item "$sources\$gpuId.wh.cpp" "$bk\gpu-1.3.4.wh.cpp"
        & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$stylerId" "$bk\styler-plus.reg" /y | Out-Null
        Log 'backups taken'
    }
    foreach ($n in $values.Keys) {
        $cur = Get $n
        if ($cur -ne $values[$n].Old -and $cur -ne $values[$n].New) { throw "$n is '$cur'; inspect first" }
    }
    if ((Get-ItemProperty "$base\$gpuId").Version -ne '1.3.5') { InvokeCli "mod install --file `"$work\gpu-c.wh.cpp`" --yes" }
    if ((Get-ItemProperty "$base\$stylerId").Version -ne '1.10.4') { InvokeCli "mod install --file `"$work\styler-c.wh.cpp`"" }
    foreach ($n in $values.Keys) { New-ItemProperty $settings -Name $n -Value $values[$n].New -PropertyType String -Force | Out-Null }
} else {
    InvokeCli "mod install --file `"$bk\gpu-1.3.4.wh.cpp`" --yes"
    InvokeCli "mod install --file `"$bk\styler-1.10.3.wh.cpp`""
    $k = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey('SOFTWARE\Windhawk\Engine\Mods\local@windows-11-file-explorer-styler-plus\Settings', $true)
    foreach ($n in $values.Keys) { $k.DeleteValue($n, $false) }
    $k.Close()
}
Bump
Show
