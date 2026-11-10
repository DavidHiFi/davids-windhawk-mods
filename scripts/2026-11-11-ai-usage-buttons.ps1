param([ValidateSet('Audit','Install','Rollback')][string]$Action='Install')
# Taskbar AI Usage Plus 1.1.1 -> 1.1.3: flyout card border 1px -> 2px (Seamless Borders width 2) and
# settings GUI metadata audit (Plus name/title, author, version, fork links).
# Rollback copies the 1.1.1 source back and recompiles (the compile deletes the old DLL).
$ErrorActionPreference='Stop'
$id='local@taskbar-ai-usage-plus'
$w='H:\Windhawk Configuration\work\2026-11-11-ai-usage-buttons'
$b='H:\Windhawk Configuration\backups\2026-11-11-ai-usage-buttons'
$log="$w\install.log"
$dst="C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$src=switch ($Action) { 'Install' { "$w\patched.wh.cpp" } 'Rollback' { "$b\source-1.1.4.wh.cpp" } default { $dst } }
if ($Action -eq 'Audit') {
  $k=Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
  [pscustomobject]@{ Version=$k.Version; LibraryFileName=$k.LibraryFileName; Disabled=$k.Disabled; SettingsChangeTime=$k.SettingsChangeTime }
  Select-String -Path $dst -Pattern 'MakeMochaChipStyle' | ForEach-Object Line
  return
}
New-Item -ItemType Directory -Force $b,$w | Out-Null
if (-not (Test-Path "$b\source-1.1.4.wh.cpp")) {
  Copy-Item $dst "$b\source-1.1.4.wh.cpp"
  reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$b\mod.reg" | Out-Null
}
Copy-Item $src $dst -Force
$ErrorActionPreference='Continue'
$out = & 'C:\Program Files\Windhawk\windhawk-cli.exe' mod compile $id 2>&1 | % { "$_" }
$code=$LASTEXITCODE
Add-Content $log "$(Get-Date -Format o) $Action exit=$code`n$($out -join "`n")"
$k=Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
Add-Content $log "version=$($k.Version) lib=$($k.LibraryFileName) disabled=$($k.Disabled)"
& 'H:\Windhawk Configuration\scripts\2026-11-04-shell-guard.ps1' -Seconds 20 -DisableMod $id *>> $log
$receipt=[ordered]@{
  date=(Get-Date -Format o); change='Flyout footer buttons and header pills: Mocha chip (crust fill, dull surface1 edge; blue-to-mauve edge fades in on hover; Mocha focus ring)'; version='1.1.4 -> 1.1.6'
  exitCode=$code; libraryFileName=$k.LibraryFileName; disabled=$k.Disabled
  backup="$b\source-1.1.4.wh.cpp"; registryBackup="$b\mod.reg"
  rollback="scripts\2026-11-11-ai-usage-buttons.ps1 -Action Rollback"
}
$receipt | ConvertTo-Json | Set-Content "$b\receipt.json"
Get-Content $log -Tail 5
