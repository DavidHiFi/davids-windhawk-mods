# Fix local@start-everything mod id and recompile (elevated).
# The mod's @id carried the "local@" prefix; Windhawk only allows [0-9a-z-]
# in the id, so every UI start raised MODS_LOAD_FAILED toasts.
$ErrorActionPreference = 'Stop'
$ws = 'H:\Windhawk Configuration'
$report = "$ws\reports\2026-10-09-start-everything-id"
$backup = "$ws\backups\2026-10-09\start-everything-id"
New-Item -ItemType Directory -Force -Path $report, $backup | Out-Null
$liveSource = 'C:\ProgramData\Windhawk\ModsSource\local@start-everything.wh.cpp'
$workSource = "$ws\work\start-everything-fix\start-everything.wh.cpp"

# backup of the live file + registry key
Copy-Item $liveSource "$backup\local@start-everything.wh.cpp" -Force
reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@start-everything' "$backup\mod-key.reg" /y | Out-Null

# deploy the fixed source (id start-everything; the local@ prefix lives in the file name only)
Copy-Item $workSource $liveSource -Force
Select-String -Path $liveSource -Pattern '^// @id' | ForEach-Object { "live id line: $($_.Line)" }

$proc = Start-Process 'C:\Program Files\Windhawk\windhawk-cli.exe' -ArgumentList 'mod compile local@start-everything' -WindowStyle Hidden -Wait -PassThru -RedirectStandardOutput "$report\compile-out.txt" -RedirectStandardError "$report\compile-err.txt"
Get-Content "$report\compile-out.txt", "$report\compile-err.txt"
if ($proc.ExitCode) { throw "Compile failed: $($proc.ExitCode)" }

$state = Get-ItemProperty 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@start-everything'
"registry: version=$($state.Version) library=$($state.LibraryFileName) disabled=$($state.Disabled)"

[PSCustomObject]@{
    when        = (Get-Date).ToString('o')
    version     = $state.Version
    library     = $state.LibraryFileName
    backup      = $backup
    sourceHash  = (Get-FileHash $workSource).Hash
    liveHash    = (Get-FileHash $liveSource).Hash
} | ConvertTo-Json | Set-Content "$report\receipt.json" -Encoding UTF8
"receipt: $report\receipt.json"
