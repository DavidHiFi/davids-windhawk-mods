param(
    [Parameter(Mandatory = $true)]
    [ValidateSet('Apply', 'Restore')]
    [string]$Action,

    [int]$Index = 59,
    [string]$Target = '',
    [string]$Style0 = ''
)

$dir = Split-Path -Parent $MyInvocation.MyCommand.Path
$jobFile = Join-Path $dir 'elev-job.json'
$cmdFile = Join-Path $dir 'Run-Elev.cmd'
$logFile = Join-Path $dir 'elev.log'

[pscustomobject]@{
    action = $Action
    index  = $Index
    target = $Target
    style0 = $Style0
} | ConvertTo-Json | Set-Content -LiteralPath $jobFile -Encoding UTF8

$before = 0
if (Test-Path -LiteralPath $logFile) { $before = (Get-Content -LiteralPath $logFile | Measure-Object -Line).Lines }

$p = Start-Process -FilePath $cmdFile -Verb RunAs -Wait -PassThru
Write-Output "elevated exit code: $($p.ExitCode)"

if (Test-Path -LiteralPath $logFile) {
    $all = Get-Content -LiteralPath $logFile
    $all | Select-Object -Skip $before | Write-Output
}
exit $p.ExitCode
