# 2026-11-09 Explorer polish. Run elevated (Invoke-Elevated.ps1), under `coop lock windhawk-engine`.
#   File Explorer Styler Plus 1.9.2 -> 1.10.2: flat full-width status dock with a top line,
#     full-height status separators, details pane hover border, solid surface2 nav pane lines and pane splitters.
#   GPU Explorer View Plus 1.3.2 -> 1.3.3: border around each drive's free-space bar.
#   Styler settings: details pane margin, border and Fira Code font; toolbar lines #585B70.
# -Action Audit prints the current state. -Action Rollback puts back the 1.9.2 / 1.3.2 sources
# and the settings from backups\2026-11-09-explorer-polish\styler-plus.reg.
# No Explorer restart: both mods hot reload.
param([ValidateSet('Install', 'Rollback', 'Audit')][string]$Action = 'Audit')
$ErrorActionPreference = 'Stop'
$work = 'H:\Windhawk Configuration\work\2026-11-09-explorer-polish'
$bk = 'H:\Windhawk Configuration\backups\2026-11-09-explorer-polish'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$base = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$stylerId = 'local@windows-11-file-explorer-styler-plus'
$gpuId = 'local@gpu-accelerated-explorer-view-plus'
$settings = "$base\$stylerId\Settings"
$log = "$bk\run.log"

function Log([string]$m) { $line = "$(Get-Date -Format 'HH:mm:ss') $m"; $line; Add-Content $log $line }

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

# New rules go after the last existing one.
$rules = [ordered]@{
    'Grid#DetailsViewControlRootGrid' = @(
        'Margin=20,20,20,20'
        'BorderThickness=1'
        'BorderBrush:=<LinearGradientBrush StartPoint="0,0" EndPoint="1,1"><GradientStop Color="#B36C7086" Offset="0"/><GradientStop Color="#45475A" Offset="0.55"/><GradientStop Color="#B36C7086" Offset="1"/></LinearGradientBrush>'
        '// Explorer polish 2026-11-09: card ends above the status dock; hover ring comes from the mod code (1.10.0).')
    'Grid#DetailsViewControlRootGrid > * > TextBlock' = @('FontFamily=FiraCode Nerd Font')
    'Grid#DetailsViewControlRootGrid > * > TextBox' = @('FontFamily=FiraCode Nerd Font')
    'Grid#NavigationBarControlGrid' = @('BorderBrush=#585B70')
}
$extra = @{ 'controlStyles[11].styles[1]' = 'BorderBrush=#585B70' }

function RuleCount {
    $p = (Get-ItemProperty $settings).PSObject.Properties.Name
    $n = 0; while ($p -contains "controlStyles[$n].target") { $n++ }; $n
}

function Bump { Set-ItemProperty "$base\$stylerId" -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) }

New-Item $bk -ItemType Directory -Force | Out-Null
foreach ($id in $stylerId, $gpuId) {
    $k = Get-ItemProperty "$base\$id"
    Log "$id version=$($k.Version) lib=$($k.LibraryFileName) disabled=$($k.Disabled)"
}
Log "styler rules=$(RuleCount)"
if ($Action -eq 'Audit') { return }

if ($Action -eq 'Install') {
    # Settings rules go in once; a later run only updates the mod code.
    $rulesDone = Test-Path "$bk\installed.json"
    foreach ($f in 'styler-plus.wh.cpp', 'gpu.wh.cpp', 'styler-plus.reg', 'gpu.reg') {
        if (-not (Test-Path "$bk\$f")) { throw "missing backup $f" }
    }
    if (-not $rulesDone) { & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$stylerId" "$bk\styler-plus-pre-install.reg" /y | Out-Null }

    # Resumable: a mod already at its new version is not installed again.
    if ((Get-ItemProperty "$base\$stylerId").Version -ne '1.10.2') { InvokeCli "mod install --file `"$work\src\styler-new.wh.cpp`"" }
    if ((Get-ItemProperty "$base\$gpuId").Version -ne '1.3.3') { InvokeCli "mod install --file `"$work\src\gpu-new.wh.cpp`" --yes" }

    if ($rulesDone) { Log 'rules already in place' }
    else {
    $n = RuleCount; $added = @()
    foreach ($target in $rules.Keys) {
        New-ItemProperty $settings -Name "controlStyles[$n].target" -Value $target -PropertyType String -Force | Out-Null
        $i = 0
        foreach ($s in $rules[$target]) { New-ItemProperty $settings -Name "controlStyles[$n].styles[$i]" -Value $s -PropertyType String -Force | Out-Null; $i++ }
        $added += $n; Log "rule $n = $target ($i styles)"; $n++
    }
    foreach ($name in $extra.Keys) { New-ItemProperty $settings -Name $name -Value $extra[$name] -PropertyType String -Force | Out-Null; Log "$name = $($extra[$name])" }
    Bump
    [ordered]@{ Date = (Get-Date).ToString('o'); AddedRules = $added; Extra = @($extra.Keys) } | ConvertTo-Json | Set-Content "$bk\installed.json"
    }
    Log 'install done'
} else {
    InvokeCli "mod install --file `"$bk\styler-plus.wh.cpp`""
    InvokeCli "mod install --file `"$bk\gpu.wh.cpp`""
    if (Test-Path "$bk\installed.json") {
        $r = Get-Content "$bk\installed.json" -Raw | ConvertFrom-Json
        $props = (Get-ItemProperty $settings).PSObject.Properties.Name
        foreach ($n in $r.AddedRules) {
            $prefix = "controlStyles[$n]."
            foreach ($p in $props | Where-Object { $_.StartsWith($prefix) }) { Remove-ItemProperty $settings -Name $p }
        }
        foreach ($p in $r.Extra) { Remove-ItemProperty $settings -Name $p -ErrorAction SilentlyContinue }
        Rename-Item "$bk\installed.json" "installed-rolledback-$(Get-Date -Format yyyyMMdd-HHmm).json"
    }
    & reg.exe import "$bk\styler-plus.reg" 2>&1 | Out-Null
    Bump
    Log 'rollback done'
}
foreach ($id in $stylerId, $gpuId) {
    $k = Get-ItemProperty "$base\$id"
    Log "$id version=$($k.Version) lib=$($k.LibraryFileName)"
}
