# Helper: run inline admin reg writes for the styler to avoid quoting traps.
# Usage: powershell -File styler-set.ps1 "<valueName>" "<regSzData>"   (or -Bump only)
param(
  [string]$Value,
  [string]$Data,
  [switch]$Bump
)
$key = "HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler"
if ($Value) {
  reg add $key\Settings /v $Value /t REG_SZ /d $Data /f
}
if ($Bump -or $Value) {
  $t = [int][double]::Parse((Get-Date -UFormat %s))
  reg add $key /v SettingsChangeTime /t REG_DWORD /d $t /f
}
reg query $key\Settings /v $Value 2>$null
reg query $key /v SettingsChangeTime
