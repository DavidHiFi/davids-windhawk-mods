# Menu hover gap: the hover keeps a gap above and below, so the first and last rows stay
# clear of the menu's rounded corners. Six mods. Runs ELEVATED.
#   -Action install   back up each source, copy the staged one in, compile; tool mods restart once
#   -Action rollback  restore the backed-up sources, compile, restart tool mods
# Seamless Flyouts reloads on compile. No windhawk.exe -restart.
param([ValidateSet('install', 'rollback')][string]$Action = 'install')
$ErrorActionPreference = 'Stop'
$ids   = 'local@seamless-flyouts', 'local@recycle-bin-tray-plus', 'local@magic-pointer-plus',
         'local@better-volume-mixer-plus', 'local@seamless-dictate', 'local@window-manager'
$tools = $ids | Where-Object { $_ -ne 'local@seamless-flyouts' }
$src   = 'C:\ProgramData\Windhawk\ModsSource'
$stage = 'H:\Windhawk Configuration\work\2026-11-09-flyout-match\menu-skin\staged-gap'
$bk    = 'H:\Windhawk Configuration\backups\2026-11-09\menu-hover-gap'
$cli   = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$mods  = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$log   = Join-Path $bk 'receipt.txt'
New-Item -ItemType Directory -Force $bk | Out-Null
function Say($t) { Add-Content -Path $log -Value "$(Get-Date -Format 'h:mm:ss tt') $t" -Encoding UTF8 }
function Bump($k) { Set-ItemProperty $k -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord }
function Compile($id) {
    $o = Join-Path $bk 'cli.out'; $e = "$o.err"
    $p = Start-Process $cli -ArgumentList @('mod', 'compile', $id, '--json') -WindowStyle Hidden -PassThru -Wait `
        -RedirectStandardOutput $o -RedirectStandardError $e
    Say "compile $id exit=$($p.ExitCode)"
    if ($p.ExitCode -ne 0) { Get-Content $o, $e | Select-Object -Last 15 | ForEach-Object { Say "  $_" }; return $false }
    return $true
}
foreach ($id in $ids) {
    $live = "$src\$id.wh.cpp"
    $tag  = $id -replace '@', '_'
    if ($Action -eq 'install') {
        Copy-Item $live "$bk\$tag.wh.cpp.bak-$(Get-Date -Format yyyyMMdd-HHmm)" -Force
        Copy-Item "$stage\$id.wh.cpp" $live -Force
    } else {
        $b = Get-ChildItem $bk -Filter "$tag.wh.cpp.bak-*" | Sort-Object Name | Select-Object -First 1
        Copy-Item $b.FullName $live -Force
    }
    if (-not (Compile $id)) {
        $b = Get-ChildItem $bk -Filter "$tag.wh.cpp.bak-*" | Sort-Object Name | Select-Object -First 1
        Copy-Item $b.FullName $live -Force; Compile $id | Out-Null
        Say "FAIL $id, old source restored"; continue
    }
    if ($tools -contains $id) {
        $k = "$mods\$id"
        Set-ItemProperty $k -Name Disabled -Value 1 -Type DWord; Bump $k; Start-Sleep -Seconds 2
        Set-ItemProperty $k -Name Disabled -Value 0 -Type DWord; Bump $k; Start-Sleep -Seconds 2
    }
    $a = Get-ItemProperty "$mods\$id"
    Say ("OK {0} Version={1} Disabled={2}" -f $id, $a.Version, $a.Disabled)
}
Say "DONE $Action"
