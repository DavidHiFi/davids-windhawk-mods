# Explorer TreeItem Tweaker Plus 1.1.4: restart Explorer automatically instead of showing the
# "Restart Explorer / Cancel" dialog (owner request 2026-10-24). A restart within two minutes of the last
# one is skipped, so the mod cannot cause a restart loop.
#   -Install    install 1.1.4 from the repo source, verify, write a receipt
#   -Rollback   reinstall the backed-up 1.1.3 source
# Run elevated through H:\System Configuration\scripts\Invoke-Elevated.ps1.
param([switch]$Install, [switch]$Rollback)

$ErrorActionPreference = 'Stop'
$cli = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$id = 'local@explorer-treeitem-tweaker-plus'
$key = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
$src = 'H:\Windhawk Configuration\Windhawk\explorer-treeitem-tweaker-plus\local@explorer-treeitem-tweaker-plus.wh.cpp'
$bk = 'H:\Windhawk Configuration\backups\2026-10-24-treeitem-auto-restart'
$old = "$bk\local@explorer-treeitem-tweaker-plus_v1.1.3.wh.cpp"
$log = "$bk\install-log.txt"
function L($m) { Add-Content -Path $log -Value ('{0}  {1}' -f (Get-Date -Format 'h:mm:ss tt'), $m) -Encoding UTF8 }

try {
    $file = $src; $want = '1.1.4'
    if ($Rollback) { $file = $old; $want = '1.1.3' }
    # The CLI prints progress on stderr; under 'Stop' Windows PowerShell turns that into a terminating error.
    $ErrorActionPreference = 'Continue'
    $out = & $cli mod install --file $file --yes 2>&1
    $code = $LASTEXITCODE
    $ErrorActionPreference = 'Stop'
    L ("cli exit {0}: {1}" -f $code, (($out | Out-String).Trim() -replace '\s+', ' '))
    if ($code -ne 0) { throw "mod install failed ($code)" }
    $p = Get-ItemProperty $key
    L ("LibraryFileName {0}; Version {1}; Disabled {2}" -f $p.LibraryFileName, $p.Version, $p.Disabled)
    if ($p.LibraryFileName -notmatch [regex]::Escape($want)) { throw "LibraryFileName is not a $want build" }
    $hunt = 'H:\System Configuration\work\freeze8\hunt-log.txt'
    if (Test-Path $hunt) {
        Add-Content -Path $hunt -Encoding UTF8 -Value ('{0}  [Note] cleared mod {1} reinstalled as {2} (auto Explorer restart, no dialog); flags unchanged, round unaffected' -f (Get-Date -Format 'MM-dd h:mm:ss tt'), $id, $want)
    }
    L "OK $want"
} catch {
    L ("FAILED: " + $_.Exception.Message)
    exit 1
}
