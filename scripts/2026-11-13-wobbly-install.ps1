# Seamless Wobbly Windows install (1.1.0 glows merged in; 1.1.1 glow fixes). Run elevated.
# 1. Backs up the mod's registry key. 2. Writes the schema defaults for the new
# glow settings that are not stored yet (an install by script stores none, and
# Wh_GetIntSetting would read 0, turning the glow off). Existing values are
# never touched. 3. Installs the staged source with Install-StagedMod.ps1,
# which refuses if the live source changed since BaseHash.
param([Parameter(Mandatory)][string]$Staged, [Parameter(Mandatory)][string]$BaseHash,
      [string]$Log = 'H:\Windhawk Configuration\work\2026-11-11-wobbly\install.log')
$ErrorActionPreference = 'Stop'
$id  = 'local@seamless-wobbly-windows'
$key = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$set = "$key\Settings"
$bk  = 'H:\Windhawk Configuration\backups\2026-11-13\seamless-wobbly-windows'
New-Item -ItemType Directory -Force $bk | Out-Null
$stamp = Get-Date -Format 'yyyyMMdd-HHmm'
& reg.exe export ($key -replace '^HKLM:', 'HKLM') "$bk\mod-key-before-install-$stamp.reg" /y | Out-Null

$ints = [ordered]@{
    'glow.enabled' = 1; 'glow.seconds' = 12; 'glow.opacity' = 32; 'glow.size' = 380
    'glow.inDrag' = 1; 'glow.dragStrength' = 100
    'glowMotion.maxWindows' = 20
    'glowAudio.reactive' = 0; 'glowAudio.fastestSeconds' = 3; 'glowAudio.sensitivity' = 100
    'glowPower.batterySaver' = 1; 'glowPower.fullscreen' = 1
    'glowPower.reduceMotion' = 1; 'glowPower.transparency' = 1
    'glowBeams.count' = 3; 'glowBeams.sweep' = 30
    'glowOrbs[0].angle' = 30;  'glowOrbs[0].speed' = 100
    'glowOrbs[1].angle' = 150; 'glowOrbs[1].speed' = 70
    'glowOrbs[2].angle' = 250; 'glowOrbs[2].speed' = 130
    'glowWaves.amplitude' = 18; 'glowWaves.length' = 100
}
$strs = [ordered]@{
    'glow.effect' = 'glows'; 'glow.mode' = 'combined'
    'glow.color1' = '#89B4FA'; 'glow.color2' = '#CBA6F7'; 'glow.color3' = '#B4BEFE'
    'glowApps[0]' = 'helium.exe'; 'glowApps[1]' = 'brave.exe'; 'glowExcluded[0]' = 'windhawk.exe'
    'glowMotion.animate' = 'all'; 'glowMotion.smoothness' = 'full'
    'glowBeams.origin' = 'top'
    'glowOrbs[0].color' = '#89B4FA'; 'glowOrbs[1].color' = '#CBA6F7'; 'glowOrbs[2].color' = '#B4BEFE'
    'glowOrbEdges' = 'bounce'
}
if (-not (Test-Path $set)) { "no Settings key, stopping" | Tee-Object $Log; exit 5 }
$have = (Get-Item $set).Property
$wrote = @()
foreach ($d in $ints.GetEnumerator()) {
    if ($have -notcontains $d.Key) { New-ItemProperty $set -Name $d.Key -Value ([int]$d.Value) -PropertyType DWord | Out-Null; $wrote += $d.Key }
}
foreach ($d in $strs.GetEnumerator()) {
    if ($have -notcontains $d.Key) { New-ItemProperty $set -Name $d.Key -Value $d.Value -PropertyType String | Out-Null; $wrote += $d.Key }
}
"$(Get-Date -Format 'h:mm:ss tt') defaults written: $($wrote.Count)" | Set-Content $Log
$out = & "$PSScriptRoot\Install-StagedMod.ps1" -Id $id -Staged $Staged -BaseHash $BaseHash 2>&1
$code = $LASTEXITCODE
$out | Add-Content $Log
"install exit $code" | Add-Content $Log
exit $code
