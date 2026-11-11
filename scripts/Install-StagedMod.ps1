# Installs a staged mod source, but only if the live source is still the one it was staged from,
# so another thread's newer build is never overwritten. Waits for CPU under 70% first. Run elevated.
#   -Id local@seamless-color-picker -Staged C:\Users\Public\x.wh.cpp -BaseHash <sha256 of the live source when staged>
param([string]$Id, [string]$Staged, [string]$BaseHash)
$ErrorActionPreference = 'Stop'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$stored = "C:\ProgramData\Windhawk\ModsSource\$Id.wh.cpp"
$bk = "H:\Windhawk Configuration\backups\settings-material"
New-Item -ItemType Directory -Force $bk | Out-Null
for ($i = 0; $i -lt 90; $i++) {
    $cpu = (Get-CimInstance Win32_Processor | Measure-Object LoadPercentage -Average).Average
    if ($cpu -lt 70) { break }; Start-Sleep 10
}
$now = (Get-FileHash $stored -Algorithm SHA256).Hash
if ($now -ne $BaseHash) { "$Id CHANGED since staging, not installed"; exit 2 }
$stamp = Get-Date -Format 'yyyyMMdd-HHmm'
Copy-Item $stored "$stored.bak-$stamp" -Force
Copy-Item $stored "$bk\$Id-$stamp.wh.cpp" -Force
reg export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$Id" "$bk\$Id-key-$stamp.reg" /y | Out-Null
$p = Start-Process $cli -ArgumentList 'mod','install','--file',$Staged -PassThru -WindowStyle Hidden `
     -RedirectStandardOutput "$bk\cli.out" -RedirectStandardError "$bk\cli.err"
try { $p.PriorityClass = 'BelowNormal' } catch {}
$null = $p.WaitForExit(600000)
$v = (Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$Id").Version
"$Id installed, registry v$v, backup $Id-$stamp.wh.cpp"
