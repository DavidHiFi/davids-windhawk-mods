param([ValidateSet('Audit','Install','Rollback','WaitInstall')][string]$Action='Audit',[int]$WaitMinutes=240)
# Windhawk Enhanced Styler 2.1.9: reset pills, number arrow pill, gradient changed-setting bars, segmented switches as pill docks.
# Install and Rollback run only while the Windhawk window (windhawk-ui) is closed, so the
# window-look mod never reloads under the owner. WaitInstall polls for that, then installs.
$ErrorActionPreference='Stop'
$root='H:\Windhawk Configuration'
$bak="$root\backups\2026-11-10-styler-219"
$report="$root\reports\2026-11-10-styler-219"
$keyReg='HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-enhanced-styler'
$key="HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-enhanced-styler"
$source='C:\ProgramData\Windhawk\ModsSource\local@windhawk-enhanced-styler.wh.cpp'
$repoSource="$root\davids-windhawk-mods\mods\local\windhawk-enhanced-styler\windhawk-enhanced-styler.wh.cpp"
$libs='C:\ProgramData\Windhawk\Engine\Mods\64'
$new='local@windhawk-enhanced-styler_2.1.9_settings.dll'
$log="$report\install.log"
function Log($m){ "$(Get-Date -Format 'yyyy-MM-dd HH:mm:ss') $m" | Add-Content $log }

if($Action -eq 'Audit'){ Get-ItemProperty $key | Select-Object Disabled,LibraryFileName; return }

if($Action -eq 'WaitInstall'){
 Log "waiting for windhawk-ui to close (max $WaitMinutes min)"
 $deadline=(Get-Date).AddMinutes($WaitMinutes)
 while(Get-Process windhawk-ui -ErrorAction SilentlyContinue){
  if((Get-Date) -gt $deadline){ Log 'gave up: window stayed open'; exit 2 }
  Start-Sleep -Seconds 3
 }
 Start-Sleep -Seconds 2
 if(Get-Process windhawk-ui -ErrorAction SilentlyContinue){ Log 'window reopened at once; not installing'; exit 3 }
 $Action='Install'
}

if(Get-Process windhawk-ui -ErrorAction SilentlyContinue){ throw 'Close the Windhawk window before installing or rolling back.' }

if($Action -eq 'Rollback'){
 reg import "$bak\mod-key.reg" 2>$null
 if($LASTEXITCODE){ throw 'Registry restore failed' }
 Copy-Item "$bak\live.wh.cpp" $source -Force
 Log 'rolled back'
 Get-ItemProperty $key | Select-Object Disabled,LibraryFileName
 return
}

$before=Get-ItemProperty $key
if($before.Disabled -eq 1){ Log 'owner disabled the mod; left alone'; throw 'Owner disabled this mod; leaving it disabled.' }
if(-not (Test-Path "$bak\mod-key.reg")){ throw 'Backup missing; run the backup step first.' }
Copy-Item "$report\styler-buttons.dll" "$libs\$new" -Force
if((Get-FileHash "$report\styler-buttons.dll").Hash -ne (Get-FileHash "$libs\$new").Hash){ throw 'DLL copy mismatch' }
Copy-Item $source "$source.bak-$(Get-Date -Format yyyyMMdd-HHmm)" -Force
Copy-Item $repoSource $source -Force
Set-ItemProperty $key LibraryFileName $new
$after=(Get-ItemProperty $key).LibraryFileName
if($after -ne $new){ throw 'Library readback mismatch' }
@{installed=$true;oldLibrary=$before.LibraryFileName;newLibrary=$after;version='2.1.9';uiClosed=$true;timestamp=(Get-Date -Format o)} | ConvertTo-Json | Set-Content "$report\install-receipt.json"
Log "installed $new (was $($before.LibraryFileName))"
Get-ItemProperty $key | Select-Object Disabled,LibraryFileName
