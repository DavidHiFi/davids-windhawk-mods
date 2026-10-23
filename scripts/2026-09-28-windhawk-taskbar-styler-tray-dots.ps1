<#
.SYNOPSIS
    Replaces the Windows 11 tray overflow chevron (up arrow) with the
    RosePine three-dot glyph in the Windhawk "Windows 11 Taskbar Styler" mod.

.DESCRIPTION
    Adds exactly one controlStyles entry to the mod's live settings:

        target: Windows.UI.Xaml.Controls.TextBlock#InnerTextBlock[Text=<U+E971>]
        style:  Text=<U+E712>

    U+E971 (ChevronUpMed) is the tray overflow chevron glyph in Segoe Fluent
    Icons; U+E712 ("More") is the horizontal three-dot glyph. This is the
    same rule the RosePine theme from windows-11-taskbar-styling-guide ships.

    The glyph characters are built with [char]0xE971 / [char]0xE712 at run
    time on purpose: a literal PUA character in a BOM-less UTF-8 .ps1 file
    gets misread as ANSI by Windows PowerShell 5.1.

    Modes (default -Audit, which changes nothing):

    -Audit      Print the mod state, the current rule search result, and the
                index the installer would use.
    -Install    Back up the mod registry key, append the rule, bump
                SettingsChangeTime, restart the Windhawk engine, write a
                receipt. Requires elevation.
    -Rollback   Remove the rule (shifting any later entries down), bump
                SettingsChangeTime, restart the engine. Requires elevation.

    Rollback procedure is also written into
    notes\2026-09-28-windhawk-taskbar-styler-tray-dots.md.
#>
[CmdletBinding()]
param(
    [switch]$Install,
    [switch]$Rollback,
    [switch]$Audit,
    [string]$LogPath   = 'H:\System Configuration\reports\2026-09-28\windhawk-taskbar-styler-tray-dots.log',
    [string]$BackupDir = 'H:\System Configuration\backups\2026-09-28\windhawk-taskbar-styler-tray-dots'
)

$ErrorActionPreference = 'Stop'

$ModId       = 'windows-11-taskbar-styler'
$ModKey      = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$ModId"
$SettingsKey = "$ModKey\Settings"
$WindhawkExe = 'C:\Program Files\Windhawk\windhawk.exe'

# Glyphs: U+E971 is the tray chevron-up, U+E712 is the three-dot "More".
$ChevronGlyph = [char]0xE971
$DotsGlyph    = [char]0xE712
$Selector     = 'Windows.UI.Xaml.Controls.TextBlock#InnerTextBlock[Text=' + $ChevronGlyph + ']'
$StyleValue   = 'Text=' + $DotsGlyph

$logDir = Split-Path -Parent $LogPath
if (-not (Test-Path -LiteralPath $logDir)) { New-Item -ItemType Directory -Path $logDir -Force | Out-Null }
function Write-Log {
    param([string]$Message)
    $line = '{0} {1}' -f (Get-Date -Format 'yyyy-MM-dd HH:mm:ss'), $Message
    Write-Host $line
    Add-Content -LiteralPath $LogPath -Value $line -Encoding UTF8
}
function Test-Admin {
    (New-Object Security.Principal.WindowsPrincipal(
        [Security.Principal.WindowsIdentity]::GetCurrent())
    ).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}
function Get-ModProps {
    $key = Get-Item -LiteralPath $ModKey -ErrorAction SilentlyContinue
    if (-not $key) { return $null }
    foreach ($n in $key.Property) {
        [pscustomobject]@{ Name = $n; Kind = $key.GetValueKind($n); Value = $key.GetValue($n) }
    }
}
function Get-ControlStyleIndices {
    $key = Get-Item -LiteralPath $SettingsKey
    $idx = @()
    foreach ($n in $key.GetValueNames()) {
        if ($n -match '^controlStyles\[(\d+)\]\.target$') { $idx += [int]$Matches[1] }
    }
    ,($idx | Sort-Object -Unique)
}
function Find-RuleIndices {
    # Any controlStyles entry whose target contains the chevron glyph.
    $key = Get-Item -LiteralPath $SettingsKey
    $found = @()
    foreach ($n in $key.GetValueNames()) {
        if ($n -match '^controlStyles\[(\d+)\]\.target$' -and $key.GetValue($n) -like "*$ChevronGlyph*") {
            $found += [int]$Matches[1]
        }
    }
    ,($found | Sort-Object -Unique)
}
function Show-Rule {
    param([int]$Index)
    $key = Get-Item -LiteralPath $SettingsKey
    $target = $key.GetValue("controlStyles[$Index].target")
    $t = ($target.ToCharArray() | ForEach-Object { $c = [int][char]$_; if ($c -gt 126 -or $c -lt 32) { 'U+{0:X4}' -f $c } else { [char]$c } }) -join ''
    Write-Log ("controlStyles[{0}].target = {1}" -f $Index, $t)
    for ($j = 0; ; $j++) {
        $sname = "controlStyles[$Index].styles[$j]"
        $sv = $key.GetValue($sname)
        if ($null -eq $sv) { break }
        $s = ($sv.ToCharArray() | ForEach-Object { $c = [int][char]$_; if ($c -gt 126 -or $c -lt 32) { 'U+{0:X4}' -f $c } else { [char]$c } }) -join ''
        Write-Log ("  styles[{0}] = {1}" -f $j, $s)
    }
}
function Restart-Engine {
    Write-Log 'restarting Windhawk engine'
    Start-Process -FilePath $WindhawkExe -ArgumentList '-restart' -WindowStyle Hidden
    Start-Sleep -Seconds 5
    $alive = Get-Process -Name windhawk -ErrorAction SilentlyContinue
    Write-Log ("windhawk processes after restart: " + @($alive).Count)
}
function Bump-SettingsChangeTime {
    # New-ItemProperty, not Set-ItemProperty: only the former takes
    # -PropertyType, and the value must stay REG_DWORD.
    $now = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
    $null = New-ItemProperty -LiteralPath $ModKey -Name SettingsChangeTime -Value $now -PropertyType DWord -Force
    Write-Log "registry: SettingsChangeTime = $now"
}

if (($Install -and $Rollback) -or ($Install -and $Audit) -or ($Rollback -and $Audit)) {
    Write-Log 'use exactly one of -Audit, -Install, -Rollback'
    exit 2
}
if (-not ($Install -or $Rollback)) { $Audit = $true }

Write-Log "=== windhawk-taskbar-styler tray dots: mode=$($(if ($Install) {'install'} elseif ($Rollback) {'rollback'} else {'audit'})) ==="
Write-Log ("identity={0} elevated={1}" -f [Security.Principal.WindowsIdentity]::GetCurrent().Name, (Test-Admin))

if (-not (Test-Path -LiteralPath $SettingsKey)) {
    Write-Log "settings key missing: $SettingsKey"
    exit 3
}
$props = Get-ModProps
foreach ($p in $props) { Write-Log ("mod: {0} = {1}" -f $p.Name, $p.Value) }
$indices = Get-ControlStyleIndices
Write-Log ("controlStyles entries: count={0} maxIndex={1}" -f $indices.Count, ($indices | Measure-Object -Maximum).Maximum)

if ($Audit) {
    $found = Find-RuleIndices
    if ($found.Count -eq 0) {
        Write-Log 'chevron rule: NOT present'
    } else {
        foreach ($i in $found) { Write-Log "chevron rule: present at index $i" ; Show-Rule $i }
    }
    $next = (($indices | Measure-Object -Maximum).Maximum) + 1
    Write-Log "installer would use index $next"
    Write-Log 'AUDIT OK'
    exit 0
}

if (-not (Test-Admin)) {
    Write-Log 'not elevated; aborting'
    exit 10
}

if ($Install) {
    $found = Find-RuleIndices
    $next = (($indices | Measure-Object -Maximum).Maximum) + 1
    $created = $false
    $regFile = $null
    if ($found.Count -gt 0) {
        # Idempotent completion: a previous run may have written the rule
        # before failing later. Skip the write but still finish the job.
        Write-Log "rule already present at index $($found -join ', ')"
        foreach ($i in $found) { Show-Rule $i }
        Write-Log 'skipping write; will still bump SettingsChangeTime and restart the engine'
        $next = $found[0]
    } else {
        # 1. backup
        if (-not (Test-Path -LiteralPath $BackupDir)) { New-Item -ItemType Directory -Path $BackupDir -Force | Out-Null }
        $regFile = Join-Path $BackupDir ('windhawk-taskbar-styler-before-{0}.reg' -f (Get-Date -Format 'yyyyMMdd-HHmmss'))
        $null = & reg.exe export ("HKLM\SOFTWARE\Windhawk\Engine\Mods\$ModId") $regFile /y 2>&1
        Write-Log "backup: reg export -> $regFile (exit=$LASTEXITCODE)"

        # 2. append the rule
        $null = New-ItemProperty -LiteralPath $SettingsKey -Name "controlStyles[$next].target"   -Value $Selector   -PropertyType String -Force
        $null = New-ItemProperty -LiteralPath $SettingsKey -Name "controlStyles[$next].styles[0]" -Value $StyleValue -PropertyType String -Force
        Write-Log "registry: controlStyles[$next].target written (chevron U+E971 -> dots U+E712)"
        Write-Log "registry: controlStyles[$next].styles[0] written"
        $created = $true
    }

    # 3. settings time + engine restart
    Bump-SettingsChangeTime
    Restart-Engine

    # 4. receipt
    $receipt = [ordered]@{
        mode              = 'install'
        timestamp         = (Get-Date -Format o)
        identity          = [Security.Principal.WindowsIdentity]::GetCurrent().Name
        mod_id            = $ModId
        rule_index        = $next
        rule_created      = $created
        target            = 'Windows.UI.Xaml.Controls.TextBlock#InnerTextBlock[Text=<U+E971>]'
        style             = 'Text=<U+E712>'
        source            = 'RosePine theme, ramensoftware/windows-11-taskbar-styling-guide'
        prior_rules_count = $indices.Count
        registry_backup   = $regFile
        log               = $LogPath
    }
    $receiptFile = Join-Path $BackupDir 'install-receipt.json'
    $receipt | ConvertTo-Json -Depth 6 | Set-Content -LiteralPath $receiptFile -Encoding UTF8
    Write-Log "receipt: $receiptFile"
    Write-Log 'INSTALL OK'
    exit 0
}

if ($Rollback) {
    $found = Find-RuleIndices
    if ($found.Count -eq 0) {
        Write-Log 'rule not present; nothing to roll back'
        exit 0
    }
    $key = Get-Item -LiteralPath $SettingsKey
    $max = ($indices | Measure-Object -Maximum).Maximum
    foreach ($i in $found) {
        # remove the rule's values
        for ($j = 0; ; $j++) {
            $sname = "controlStyles[$i].styles[$j]"
            if ($null -eq $key.GetValue($sname)) { break }
            Remove-ItemProperty -LiteralPath $SettingsKey -Name $sname
        }
        Remove-ItemProperty -LiteralPath $SettingsKey -Name "controlStyles[$i].target"
        Write-Log "registry: removed controlStyles[$i]"
        # shift any later entries down by one
        for ($n = $i + 1; $n -le $max; $n++) {
            for ($j = 0; ; $j++) {
                $sname = "controlStyles[$n].styles[$j]"
                $sv = $key.GetValue($sname)
                if ($null -eq $sv) { break }
                $null = New-ItemProperty -LiteralPath $SettingsKey -Name "controlStyles[$($n-1)].styles[$j]" -Value $sv -PropertyType String -Force
                Remove-ItemProperty -LiteralPath $SettingsKey -Name $sname
            }
            $t = $key.GetValue("controlStyles[$n].target")
            if ($null -ne $t) {
                $null = New-ItemProperty -LiteralPath $SettingsKey -Name "controlStyles[$($n-1)].target" -Value $t -PropertyType String -Force
                Remove-ItemProperty -LiteralPath $SettingsKey -Name "controlStyles[$n].target"
            }
        }
    }
    Bump-SettingsChangeTime
    Restart-Engine
    $receiptFile = Join-Path $BackupDir 'rollback-receipt.json'
    if (-not (Test-Path -LiteralPath $BackupDir)) { New-Item -ItemType Directory -Path $BackupDir -Force | Out-Null }
    @{ mode = 'rollback'; timestamp = (Get-Date -Format o); log = $LogPath } | ConvertTo-Json | Set-Content -LiteralPath $receiptFile -Encoding UTF8
    Write-Log "receipt: $receiptFile"
    Write-Log 'ROLLBACK OK'
    exit 0
}
