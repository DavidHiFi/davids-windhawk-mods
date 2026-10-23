[CmdletBinding()]
param([switch]$Audit,[switch]$Install,[switch]$Rollback,[string]$BackupPath)
$ErrorActionPreference='Stop'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler\Settings'
$obsolete=@('opacity','acrylic')
if ($Audit) {Get-ItemProperty $key | Select-Object $obsolete;return}
if ($Rollback) {
 if (!$BackupPath) {throw 'Specify the exact backup directory'}
 & reg.exe import "$BackupPath\mod.reg" | Out-Null
 if ($LASTEXITCODE) {throw 'Registry restore failed'}
 return
}
if (!$Install) {throw 'Choose -Audit, -Install or -Rollback'}
$BackupPath="H:\Windhawk Configuration\backups\2026-10-09\styler-audit\obsolete-settings-$(Get-Date -Format HHmmss)"
New-Item -ItemType Directory -Path $BackupPath | Out-Null
& reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@windhawk-styler' "$BackupPath\mod.reg" /y | Out-Null
if ($LASTEXITCODE) {throw 'Registry backup failed'}
$before=Get-ItemProperty $key
$removed=@()
foreach ($name in $obsolete) {
 if ($before.PSObject.Properties.Name -contains $name) {
  Remove-ItemProperty -LiteralPath $key -Name $name
  $removed+=@{name=$name;value=$before.$name}
 }
}
$after=Get-ItemProperty $key
foreach ($name in $obsolete) {if ($after.PSObject.Properties.Name -contains $name) {throw "Obsolete value remains: $name"}}
foreach ($property in $before.PSObject.Properties) {
 if ($property.Name -notin $obsolete -and $property.Name -notlike 'PS*' -and $after.($property.Name) -ne $property.Value) {throw "Unrelated setting changed: $($property.Name)"}
}
@{time=(Get-Date -Format o);backup=$BackupPath;removed=$removed} | ConvertTo-Json -Depth 4 | Set-Content 'H:\Windhawk Configuration\reports\2026-10-09-styler-audit\obsolete-settings-receipt.json' -Encoding UTF8
Get-Content 'H:\Windhawk Configuration\reports\2026-10-09-styler-audit\obsolete-settings-receipt.json'
