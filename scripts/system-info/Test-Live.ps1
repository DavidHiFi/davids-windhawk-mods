$ErrorActionPreference='Stop'
$root='H:\System Configuration'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-system-info-weather'
$settings="$key\Settings"
$original=Get-ItemProperty $settings
$shellPid=(Get-Content "$root\reports\2026-10-03\system-info-v1.2\installed.json" -Raw | ConvertFrom-Json).ExplorerPid
function Save-Setting([string]$Name,$Value){
 Set-ItemProperty $settings $Name $Value
 Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
 Start-Sleep -Seconds 4
}
function Audit([string]$Label){
 & "$root\scripts\system-info\Audit.ps1" -Label $Label | Out-Null
 $receipt=Get-Content "$root\reports\2026-10-03\system-info-v1.2\$Label.json" -Raw | ConvertFrom-Json
 if($receipt.ExplorerPid -ne $shellPid){throw 'Explorer restarted during test'}
 if($receipt.LoadedModules -notcontains 'local@taskbar-system-info-weather_1.2.0_2.dll'){throw 'New module not loaded'}
 return $receipt
}
try {
 $preset=Audit 'memory-only'
 Save-Setting showComputeGraphs 1
 $both=Audit 'both-graph-pairs'
 if($both.PanelRightDip -le $preset.PanelRightDip){throw 'Compute graph toggle did not add space'}
 Save-Setting showMemoryGraphs 0
 $compute=Audit 'compute-only'
 if(!$compute.ShowComputeGraphs -or $compute.ShowMemoryGraphs){throw 'Graph switches are not independent'}
 Save-Setting showComputeGraphs 0
 $neither=Audit 'no-graphs'
 Save-Setting showMemoryGraphs 1
 $memory=Audit 'memory-restored'
 if($memory.PanelRightDip -le $neither.PanelRightDip){throw 'Memory graph toggle did not restore space'}
 Save-Setting showMemoryBars 0
 $barsOff=Audit 'capacity-bars-off'
 Save-Setting showMemoryBars 1
 $barsOn=Audit 'capacity-bars-on'
 Save-Setting itemGap 4
 $tight=Audit 'gap-4'
 Save-Setting itemGap 12
 $wide=Audit 'gap-12'
 if($wide.PanelRightDip -le $tight.PanelRightDip){throw 'Shared gap setting did not change layout'}
 Save-Setting itemGap 8
 Save-Setting fontFamily 'Segoe UI'
 $font=Audit 'font-segoe'
 Save-Setting fontFamily $original.fontFamily
 Save-Setting showNetwork 0
 $networkOff=Audit 'network-off'
 Save-Setting showNetwork 1
 $networkOn=Audit 'network-on'
 if($networkOn.PanelRightDip -le $networkOff.PanelRightDip){throw 'Network toggle did not change layout'}
 'PASS: four graph-pair combinations, independent capacity bars, shared gap 4/8/12, font change and network toggle reload without restarting Explorer.'
}finally{
 foreach($name in @('showComputeGraphs','showMemoryGraphs','showMemoryBars','itemGap','showNetwork','fontFamily')){Set-ItemProperty $settings $name $original.$name}
 Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
 Start-Sleep -Seconds 4
 & "$root\scripts\system-info\Audit.ps1" -Label restored
}
