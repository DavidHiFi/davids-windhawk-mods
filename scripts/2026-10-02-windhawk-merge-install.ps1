[CmdletBinding()]
param([ValidateSet('Audit','Install','Rollback')][string]$Mode='Audit')
$ErrorActionPreference='Stop'
$id='local@david-window-pack'
$root='HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$originals=@('snap-commander','move-window-to-monitor','local@alt-snap-drag')
$work='H:\System Configuration\Windhawk\window-pack'
$backup='H:\System Configuration\backups\2026-10-03-windhawk-window-pack'
$lib='local@david-window-pack_1.0.0_3.dll'
if($Mode -eq 'Audit') {
    foreach($m in ($originals+@($id))) {
        Get-ItemProperty "$root\$m" -ErrorAction SilentlyContinue | Select-Object PSChildName,Disabled,Include,LibraryFileName,Version
    }
    exit
}
if(-not ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)){throw 'Elevated execution required'}
if($Mode -eq 'Rollback') {
    Set-ItemProperty "$root\$id" Disabled 1
    foreach($m in $originals) {
        & reg.exe import "$backup\$m.reg"
        if($LASTEXITCODE){throw "Registry restore failed: $m"}
    }
    Write-Output 'Merged mod disabled; original mod configurations restored.'
    exit
}
New-Item -ItemType Directory -Path $backup -Force | Out-Null
foreach($m in $originals) {
    if(Test-Path "$backup\$m.reg"){throw 'Backup already exists. Audit before installing again.'}
    & reg.exe export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$m" "$backup\$m.reg" /y
    if($LASTEXITCODE){throw "Backup failed: $m"}
    Copy-Item -LiteralPath "C:\ProgramData\Windhawk\ModsSource\$m.wh.cpp" -Destination $backup
}
foreach($a in '64','32') {
    $src="$work\local@david-window-pack_1.0.0_3_$a.dll"
    $dst="C:\ProgramData\Windhawk\Engine\Mods\$a\$lib"
    Copy-Item -LiteralPath $src -Destination $dst
    if((Get-FileHash $src).Hash -ne (Get-FileHash $dst).Hash){throw "DLL verification failed: $a"}
}
Copy-Item -LiteralPath "$work\david-window-pack.wh.cpp" -Destination "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$key=New-Item "$root\$id" -Force
$strings=@{LibraryFileName=$lib;Version='1.0.0';Include='*|windhawk.exe';Exclude='';Architecture=''}
foreach($n in $strings.Keys){New-ItemProperty $key.PSPath $n -Value $strings[$n] -PropertyType String -Force | Out-Null}
New-ItemProperty $key.PSPath Disabled -Value 1 -PropertyType DWord -Force | Out-Null
New-ItemProperty $key.PSPath SettingsChangeTime -Value ([int][DateTimeOffset]::Now.ToUnixTimeSeconds()) -PropertyType DWord -Force | Out-Null
$settings=New-Item "$root\$id\Settings" -Force
$seen=@{}
foreach($m in $originals) {
    $old=Get-Item "$root\$m\Settings"
    foreach($n in $old.GetValueNames()) {
        if($seen.ContainsKey($n)){throw "Duplicate setting: $n"}
        $seen[$n]=$true
        $settings.SetValue($n,$old.GetValue($n),$old.GetValueKind($n))
    }
}
foreach($m in $originals){Set-ItemProperty "$root\$m" Disabled 1}
Start-Sleep -Seconds 3
Set-ItemProperty "$root\$id" Disabled 0
Write-Output "Installed $id with $($seen.Count) preserved settings. No engine restart requested."
@{installedAt=(Get-Date -Format o);id=$id;settingsCount=$seen.Count;dll64=(Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\64\$lib").Hash;dll32=(Get-FileHash "C:\ProgramData\Windhawk\Engine\Mods\32\$lib").Hash;backup=$backup} | ConvertTo-Json | Set-Content "$backup\receipt.json" -Encoding UTF8

