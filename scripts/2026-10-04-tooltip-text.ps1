param([switch]$Install,[switch]$Rollback,[switch]$Audit)
$ErrorActionPreference='Stop'
$root='H:\Windhawk Configuration'
$backup=Join-Path $root 'backups\2026-10-04\tooltip-text'
$key='HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@translucent-flyouts'
if ($Audit -or (!$Install -and !$Rollback)) { Get-ItemProperty $key; Get-ItemProperty "$key\Settings"; exit }
if (!(New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) { throw 'Elevated execution required' }
if ($Rollback) {
    & reg.exe import (Join-Path $backup 'before.reg')
    if ($LASTEXITCODE) { throw 'Registry restore failed' }
    foreach ($name in @('tooltip.lightModeColor','tooltip.darkModeColor')) { Remove-ItemProperty "$key\Settings" $name -ErrorAction SilentlyContinue }
    Copy-Item (Join-Path $backup 'source-before.cpp') 'C:\ProgramData\Windhawk\ModsSource\local@translucent-flyouts.wh.cpp' -Force
} else {
    $lib='local@translucent-flyouts_0.6.6_27.dll'
    $hashes=@{}
    foreach ($arch in @('64','32')) {
        $src=Join-Path $root "Windhawk\translucency-flyouts\local@translucent-flyouts_0.6.6_1_$arch.dll"
        $dst="C:\ProgramData\Windhawk\Engine\Mods\$arch\$lib"
        Copy-Item $src $dst -Force
        $hashes[$arch]=(Get-FileHash $dst).Hash
        if ($hashes[$arch] -ne (Get-FileHash $src).Hash) { throw 'Installed hash mismatch' }
    }
    Copy-Item (Join-Path $root 'Windhawk\translucency-flyouts\translucent-flyouts.wh.cpp') 'C:\ProgramData\Windhawk\ModsSource\local@translucent-flyouts.wh.cpp' -Force
    Set-ItemProperty $key LibraryFileName $lib
    Set-ItemProperty $key Version '0.6.6'
    # Keep protected audio applications outside the mod's injection scope.
    $exclude=(Get-ItemProperty $key).Exclude
    if ($exclude -notlike '*Ableton*') { Set-ItemProperty $key Exclude "$exclude|Ableton*.exe" }
    foreach ($name in @('tooltip.lightModeColor','tooltip.darkModeColor')) { New-ItemProperty "$key\Settings" $name -Value '0xFFFFFFFF' -PropertyType String -Force | Out-Null }
    @{version='0.6.6';library=$lib;hashes=$hashes;backup=(Join-Path $backup 'before.reg');time=(Get-Date -Format o)} | ConvertTo-Json -Depth 5 | Set-Content (Join-Path $backup 'receipt.json')
}
Set-ItemProperty $key SettingsChangeTime ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds())
Get-ItemProperty $key | Select-Object LibraryFileName,Version,SettingsChangeTime,Exclude
Get-ItemProperty "$key\Settings" | Select-Object tooltip.lightModeColor,tooltip.darkModeColor




