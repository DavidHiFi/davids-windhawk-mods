param(
    [Parameter(Mandatory = $true)]
    [ValidateSet('Snapshot', 'Set', 'Restore', 'Show')]
    [string]$Action,
    [string]$ListFile = '',
    [ValidateSet(0, 1)]
    [int]$Disabled = 1
)

# Explorer lag bisect: toggles the Disabled flag on Windhawk mods for timing tests.
#   -Action Snapshot          record every mod's current Disabled state + reg export (no writes)
#   -Action Set -ListFile f   write Disabled=<Disabled> for each mod id in f (elevated)
#   -Action Restore           put every mod back to its snapshot Disabled state (elevated)
#   -Action Show              print current Disabled state (no writes)
# Changes take effect when Explorer starts; the cycle driver restarts Explorer.

$ErrorActionPreference = 'Stop'
$modsRoot = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods'
$modsReg  = 'HKLM\SOFTWARE\Windhawk\Engine\Mods'
$dir      = 'H:\Windhawk Configuration\backups\2026-10-13\explorer-lag'
$orig     = Join-Path $dir 'original-disabled.json'

function Test-Admin {
    $id = [Security.Principal.WindowsIdentity]::GetCurrent()
    return ([Security.Principal.WindowsPrincipal]$id).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

function Get-DisabledState([string]$mod) {
    $p = Get-ItemProperty -LiteralPath (Join-Path $modsRoot $mod)
    if ($p.PSObject.Properties.Name -contains 'Disabled') {
        return [pscustomobject]@{ Mod = $mod; HasDisabled = $true; Value = [int]$p.Disabled }
    }
    return [pscustomobject]@{ Mod = $mod; HasDisabled = $false; Value = 0 }
}

switch ($Action) {
    'Snapshot' {
        New-Item -ItemType Directory -Force -Path $dir | Out-Null
        $all = Join-Path $dir 'mods-all-before.reg'
        if (Test-Path -LiteralPath $all) { throw "snapshot already exists: $all (refusing to overwrite the original)" }
        & reg.exe export $modsReg $all /y | Out-Null
        if ($LASTEXITCODE -ne 0) { throw 'reg export failed' }
        $state = Get-ChildItem -LiteralPath $modsRoot | ForEach-Object { Get-DisabledState $_.PSChildName }
        $state | ConvertTo-Json -Depth 3 | Set-Content -LiteralPath $orig -Encoding utf8
        "snapshot: $($state.Count) mods -> $orig"
        "reg export: $all"
    }
    'Set' {
        if (-not (Test-Admin)) { throw 'Set needs an elevated shell' }
        if (-not (Test-Path -LiteralPath $ListFile)) { throw "no list file: $ListFile" }
        $names = Get-Content -LiteralPath $ListFile | Where-Object { $_.Trim() -ne '' }
        foreach ($m in $names) {
            $key = Join-Path $modsRoot $m
            if (-not (Test-Path -LiteralPath $key)) { throw "no mod key: $m" }
            Set-ItemProperty -LiteralPath $key -Name Disabled -Value $Disabled -Type DWord
            $back = Get-DisabledState $m
            if ($back.Value -ne $Disabled) { throw "readback mismatch: $m" }
        }
        "set Disabled=$Disabled on $($names.Count) mods (readback ok)"
    }
    'Restore' {
        if (-not (Test-Admin)) { throw 'Restore needs an elevated shell' }
        if (-not (Test-Path -LiteralPath $orig)) { throw "no snapshot: $orig" }
        $saved = Get-Content -LiteralPath $orig -Raw | ConvertFrom-Json
        $bad = 0
        foreach ($s in $saved) {
            $key = Join-Path $modsRoot $s.Mod
            if ($s.HasDisabled) {
                Set-ItemProperty -LiteralPath $key -Name Disabled -Value ([int]$s.Value) -Type DWord
            } else {
                Remove-ItemProperty -LiteralPath $key -Name Disabled -ErrorAction SilentlyContinue
            }
            $now = Get-DisabledState $s.Mod
            if ($now.HasDisabled -ne $s.HasDisabled -or ($s.HasDisabled -and $now.Value -ne [int]$s.Value)) {
                $bad++
                "MISMATCH: $($s.Mod) wanted HasDisabled=$($s.HasDisabled) Value=$($s.Value), got HasDisabled=$($now.HasDisabled) Value=$($now.Value)"
            }
        }
        "restored $($saved.Count) mods, mismatches: $bad"
    }
    'Show' {
        Get-ChildItem -LiteralPath $modsRoot | ForEach-Object { Get-DisabledState $_.PSChildName } |
            Where-Object { $_.HasDisabled -and $_.Value -eq 1 } | ForEach-Object { "disabled: $($_.Mod)" }
    }
}
