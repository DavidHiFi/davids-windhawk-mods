param([switch]$Audit,[switch]$Install,[switch]$Rollback)
# Seamless Dictate 1.0.6: correction cue. Run elevated for -Install / -Rollback.
$ErrorActionPreference='Stop'
$base='H:\Windhawk Configuration'
$backup="$base\backups\2026-11-10-dictate-correction-cue"
$stored='C:\ProgramData\Windhawk\ModsSource\local@seamless-dictate.wh.cpp'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@seamless-dictate'
$log="$backup\build.log"
if($Audit){Get-ItemProperty $key | Select-Object Disabled,LibraryFileName;exit}
if(!($Install -or $Rollback)){throw 'Choose -Audit, -Install or -Rollback'}
if((Get-ItemProperty $key).Disabled){throw 'Mod is off; leaving it off'}
if($Install){
 if(!(Test-Path "$backup\mod.reg")){
  & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@seamless-dictate' "$backup\mod.reg" /y | Out-Null
  if($LASTEXITCODE){throw 'Backup failed'}
 }
 Copy-Item "$base\Windhawk\seamless-dictate\seamless-dictate.wh.cpp" $stored -Force
}else{Copy-Item "$backup\installed.wh.cpp" $stored -Force}
function RunCli($arguments,$ms){
 $psi=New-Object Diagnostics.ProcessStartInfo
 $psi.FileName='C:\Program Files\Windhawk\windhawk-cli.exe';$psi.Arguments=$arguments
 $psi.UseShellExecute=$false;$psi.CreateNoWindow=$true;$psi.RedirectStandardOutput=$true;$psi.RedirectStandardError=$true
 $p=[Diagnostics.Process]::Start($psi)
 $out=$p.StandardOutput.ReadToEndAsync();$err=$p.StandardError.ReadToEndAsync()
 if(!$p.WaitForExit($ms)){$p.Kill();throw "Timed out: $arguments"}
 "== $arguments" | Add-Content $log;$out.Result | Add-Content $log;$err.Result | Add-Content $log
 if($p.ExitCode){throw "CLI failed ($($p.ExitCode)): $arguments"}
}
RunCli 'mod compile local@seamless-dictate --arch x64' 300000
RunCli 'mod disable local@seamless-dictate' 15000
RunCli 'mod enable local@seamless-dictate' 15000
Start-Sleep -Seconds 3
$hosts=@(Get-CimInstance Win32_Process -Filter "Name='windhawk-mod.exe'" | Where-Object {$_.CommandLine -like '*tool-mod*local@seamless-dictate*'})
@{date=(Get-Date).ToString('o');library=(Get-ItemProperty $key).LibraryFileName;hosts=$hosts.Count;sourceHash=(Get-FileHash $stored).Hash;rollback=[bool]$Rollback}|ConvertTo-Json|Set-Content "$backup\receipt.json"
"done hosts=$($hosts.Count)" | Add-Content $log
