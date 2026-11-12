# Installs the staged native title bar fix, each mod only if its live source is unchanged since
# staging (hash from stage.py). Run under heavy.py with the windhawk-engine coop lock held.
param([Parameter(Mandatory)][string]$HashFile)
$py = "C:\Users\localuser\AppData\Local\Programs\Python\Python313\python.exe"
$o = "C:\Users\Public\native-title"
$elev = "H:\System Configuration\scripts\Invoke-Elevated.ps1"
$inst = "H:\Windhawk Configuration\scripts\Install-StagedMod.ps1"
foreach ($line in Get-Content $HashFile) {
    if ($line -notmatch '^STAGED (\S+) (\S+) (\S+)$') { continue }
    $id = $Matches[1]; $v = $Matches[2]; $h = $Matches[3]
    & $elev -File $inst -ArgumentList "-Id $id -Staged `"$o\$id.wh.cpp`" -BaseHash $h"
    "$id registry v" + (Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id").Version + " (staged $v)"
}
& $py "H:\Windhawk Configuration\scripts\settings-material.py" check
