# Give the menus of five tool mods the Seamless Flyouts look. Runs ELEVATED.
# Tool mods run in windhawk-mod.exe, where no other mod is loaded, so each carries the look.
#   -Action install   back up each key and source; own mods: new source + compile;
#                     repo mods: install the Plus fork disabled, copy settings and app lists,
#                     turn the original off and the fork on. Then restart each tool once.
#   -Action rollback  own mods: restore the backed-up source + compile; forks: remove the
#                     fork and turn the original back on.
# No windhawk.exe -restart.
param([ValidateSet('install', 'rollback')][string]$Action = 'install', [string]$Only = '')
$ErrorActionPreference = 'Stop'
$mods  = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$src   = 'C:\ProgramData\Windhawk\ModsSource'
$plan  = Get-Content 'H:\Windhawk Configuration\work\2026-11-09-flyout-match\menu-skin\staged\plan.json' -Raw | ConvertFrom-Json
$bk    = 'H:\Windhawk Configuration\backups\2026-11-09\menu-skin'
$cli   = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$log   = Join-Path $bk 'receipt.txt'
New-Item -ItemType Directory -Force $bk | Out-Null
function Say($t) { $l = "$(Get-Date -Format 'h:mm:ss tt') $t"; Add-Content -Path $log -Value $l -Encoding UTF8; Write-Host $l }
function Fail($m) { Say "FAIL: $m"; exit 1 }
function Bump($k) { Set-ItemProperty "Registry::$k" -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord }
function SetOn($k, [int]$on) { Set-ItemProperty "Registry::$k" -Name Disabled -Value ([int](1 - $on)) -Type DWord; Bump $k }
function Invoke-WhCli([string[]]$a) {
    $o = Join-Path $bk 'cli.out'; $e = "$o.err"
    $p = Start-Process $cli -ArgumentList $a -WindowStyle Hidden -PassThru -Wait -RedirectStandardOutput $o -RedirectStandardError $e
    Say "cli $($a -join ' ') exit=$($p.ExitCode)"
    if ($p.ExitCode -ne 0) { Get-Content $o, $e | Select-Object -Last 15 | ForEach-Object { Say "  $_" } }
    return $p.ExitCode
}
function Restart-Tool($k) { SetOn $k 0; Start-Sleep -Seconds 2; SetOn $k 1; Start-Sleep -Seconds 3 }

foreach ($m in $plan) {
    if ($Only -and $m.new -ne $Only) { continue }
    $old = "$mods\$($m.old)"; $new = "$mods\$($m.new)"; $fork = $m.old -ne $m.new
    $tag = $m.new -replace '[@]', '_'

    if ($Action -eq 'rollback') {
        if ($fork) {
            if (Test-Path "Registry::$new") { SetOn $new 0; Start-Sleep -Seconds 2; Invoke-WhCli @('mod', 'remove', $m.new, '--yes') | Out-Null }
            SetOn $old 1
        } else {
            $b = Get-ChildItem $bk -Filter "$tag.wh.cpp.bak-*" | Sort-Object Name | Select-Object -Last 1
            Copy-Item $b.FullName "$src\$($m.old).wh.cpp" -Force
            if ((Invoke-WhCli @('mod', 'compile', $m.old, '--json')) -ne 0) { Fail "$($m.old) compile" }
            Restart-Tool $old
        }
        Say "ROLLBACK OK $($m.new)"; continue
    }

    if (-not (Test-Path "$bk\$tag-old-key.reg")) { reg export $old "$bk\$tag-old-key.reg" /y | Out-Null }
    Copy-Item "$src\$($m.old).wh.cpp" "$bk\$tag.wh.cpp.bak-$(Get-Date -Format yyyyMMdd-HHmm)" -Force
    if (-not $fork) {
        Copy-Item $m.file "$src\$($m.old).wh.cpp" -Force
        if ((Invoke-WhCli @('mod', 'compile', $m.old, '--json')) -ne 0) { Fail "$($m.old) compile" }
        Restart-Tool $old
    } else {
        if (-not (Test-Path "Registry::$new")) {
            if ((Invoke-WhCli @('mod', 'install', '--file', "`"$($m.file)`"", '--disabled', '--json')) -ne 0) { Fail "$($m.new) install" }
        }
        if (-not (Test-Path "Registry::$new")) { Fail "$new missing" }
        $s = Get-Item "Registry::$old\Settings" -ErrorAction SilentlyContinue
        if ($s) {
            $dst = "Registry::$new\Settings"
            if (-not (Test-Path $dst)) { New-Item -Path $dst -Force | Out-Null }
            foreach ($n in $s.GetValueNames()) {
                New-ItemProperty -Path $dst -Name $n -Value $s.GetValue($n, $null, 'DoNotExpandEnvironmentNames') -PropertyType $s.GetValueKind($n) -Force | Out-Null
            }
            if ((Get-Item $dst).ValueCount -lt $s.ValueCount) { Fail "$($m.new) settings count" }
        }
        $before = Get-ItemProperty "Registry::$old"
        foreach ($v in 'Include', 'Exclude', 'IncludeCustom', 'ExcludeCustom', 'IncludeExcludeCustomOnly', 'Architecture') {
            if ($null -ne $before.$v) {
                $type = if ($v -eq 'IncludeExcludeCustomOnly') { 'DWord' } else { 'String' }
                New-ItemProperty -Path "Registry::$new" -Name $v -Value $before.$v -PropertyType $type -Force | Out-Null
            }
        }
        SetOn $old 0; Start-Sleep -Seconds 3
        SetOn $new 1; Start-Sleep -Seconds 3
    }
    $a = Get-ItemProperty "Registry::$new"
    Say ("OK {0} Lib={1} Version={2} Disabled={3}" -f $m.new, $a.LibraryFileName, $a.Version, $a.Disabled)
}
Say "DONE $Action"
