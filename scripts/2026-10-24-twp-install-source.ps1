# Installs a staged Translucent Windows Plus source and compiles it with windhawk-cli.
# Run elevated. -Logging 1/0 toggles the mod's debug log. Output goes to -Log.
param([string]$Source = "H:\Windhawk Configuration\work\2026-10-24-twp-black-dialogs\debug.wh.cpp", [int]$Logging = 1, [string]$Log = "H:\Windhawk Configuration\work\2026-10-24-twp-black-dialogs\install.log")
$ErrorActionPreference = 'Stop'
$id  = 'local@translucent-windows-plus'
$dst = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$key = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
"$(Get-Date -Format 'h:mm:ss tt') install $Source" | Out-File $Log
trap { "ERROR: $_" | Out-File $Log -Append; exit 1 }
New-Item C:\ProgramData\Windhawk\ModsWritable\translucent-guard.suspend -Force | Out-Null
Copy-Item $Source $dst -Force
if ($Logging -ge 0) { Set-ItemProperty $key -Name LoggingEnabled -Value $Logging -Type DWord }
$out = & 'C:\Program Files\Windhawk\windhawk-cli.exe' mod compile $id 2>&1 | Out-String
"exit $LASTEXITCODE`n$out" | Out-File $Log -Append
Get-ItemProperty $key | Select-Object Version, LibraryFileName, LoggingEnabled | Out-String | Out-File $Log -Append



