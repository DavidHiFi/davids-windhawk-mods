[CmdletBinding()]
param([switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$backup = 'H:\System Configuration\backups\2026-09-30\windhawk-mixer-repair'
$targets = @(
    'C:\ProgramData\Windhawk\ModsSource\local@better-volume-mixer-plus.wh.cpp',
    'H:\Windhawk Configuration\Windhawk\better-volume-mixer-fork\better-volume-mixer-plus.wh.cpp'
)
if ($Install -and $Rollback) { throw 'Choose one mode' }
if ($Install) {
    $null = New-Item -ItemType Directory -Path $backup -Force
    foreach ($index in 0..($targets.Count - 1)) {
        $path = $targets[$index]
        $original = Join-Path $backup "source-$index.wh.cpp"
        if (Test-Path -LiteralPath $original) { throw "Backup already exists: $original" }
        Copy-Item -LiteralPath $path -Destination $original
    }
    $records = foreach ($index in 0..($targets.Count - 1)) {
        $path = $targets[$index]
        $before = (Get-FileHash -LiteralPath $path).Hash
        $source = [IO.File]::ReadAllText($path)
        $updated = $source -replace '(?m)^(//\s*@id\s+)local@better-volume-mixer-plus\s*$', '${1}better-volume-mixer-plus'
        if ($updated -eq $source) { throw "Expected invalid id missing in $path" }
        [IO.File]::WriteAllText($path, $updated, [Text.UTF8Encoding]::new($false))
        [pscustomobject]@{path=$path; before=$before; after=(Get-FileHash -LiteralPath $path).Hash; backup=(Join-Path $backup "source-$index.wh.cpp")}
    }
    [pscustomobject]@{timestamp=(Get-Date -Format o); change='Source @id local@better-volume-mixer-plus -> better-volume-mixer-plus'; files=@($records); registryChanged=$false; dllChanged=$false; restartRequired=$false} |
        ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $backup 'receipt.json') -Encoding UTF8
    $records | Format-Table -AutoSize
} elseif ($Rollback) {
    foreach ($index in 0..($targets.Count - 1)) {
        Copy-Item -LiteralPath (Join-Path $backup "source-$index.wh.cpp") -Destination $targets[$index] -Force
        Write-Output "Restored $($targets[$index])"
    }
} else {
    foreach ($path in $targets) {
        Select-String -LiteralPath $path -Pattern '^//\s*@(id|name|description|author)\s+'
    }
}
