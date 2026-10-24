# Installs a staged mod source into ModsSource and compiles it with windhawk-cli.
# Run elevated. -Id is the full mod id (local@...). Output goes to -Log.
param([Parameter(Mandatory)][string]$Id, [Parameter(Mandatory)][string]$Source, [Parameter(Mandatory)][string]$Log)
$ErrorActionPreference = 'Stop'
"$(Get-Date -Format 'h:mm:ss tt') install $Source" | Out-File $Log
trap { "ERROR: $_" | Out-File $Log -Append; exit 1 }
Copy-Item $Source "C:\ProgramData\Windhawk\ModsSource\$Id.wh.cpp" -Force
$out = & 'C:\Program Files\Windhawk\windhawk-cli.exe' mod compile $Id 2>&1 | Out-String
"exit $LASTEXITCODE`n$out" | Out-File $Log -Append
Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$Id" | Select-Object Version, LibraryFileName | Out-String | Out-File $Log -Append
