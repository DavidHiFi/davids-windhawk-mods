# Style-guide fixes for forked Windhawk mods (docs/mod-style-guide.md).
# -Group Workspace edits the repo and work copies; -Group Live edits ModsSource
# (run elevated through H:\System Configuration\scripts\Invoke-Elevated.ps1).
# Metadata and readme text only: no code, version or settings change.
param(
    [Parameter(Mandatory = $true)][ValidateSet('Workspace', 'Live')][string]$Group,
    [switch]$Audit
)

$ErrorActionPreference = 'Stop'
$ws = 'H:\Windhawk Configuration'
$live = 'C:\ProgramData\Windhawk\ModsSource'
$backup = "$ws\backups\2026-10-13-style-fixes"
$utf8 = New-Object System.Text.UTF8Encoding($false)

function Apply-Edits([string]$path, [object[]]$edits) {
    $name = Split-Path $path -Leaf
    if (-not (Test-Path -LiteralPath $path)) { Write-Output "MISSING  $name"; return }
    $bytes = [IO.File]::ReadAllBytes($path)
    $text = [Text.Encoding]::UTF8.GetString($bytes)
    if ([Convert]::ToBase64String($bytes) -ne [Convert]::ToBase64String([Text.Encoding]::UTF8.GetBytes($text))) {
        Write-Output "SKIP (not clean UTF-8)  $name"; return
    }
    $nl = if ($text.Contains("`r`n")) { "`r`n" } else { "`n" }
    foreach ($e in $edits) {
        $hits = ([regex]::Matches($text, $e.Pattern, 'Multiline')).Count
        if ($hits -ne 1) { Write-Output "SKIP (pattern hits=$hits)  $name  :: $($e.Pattern)"; return }
    }
    if ($Audit) { Write-Output "AUDIT ok  $name"; return }
    if ($Group -eq 'Live') {
        New-Item -ItemType Directory -Force -Path $backup | Out-Null
        Copy-Item -LiteralPath $path -Destination (Join-Path $backup $name) -Force
    }
    foreach ($e in $edits) {
        $rep = $e.Replace.Replace("`n", $nl)
        $text = [regex]::Replace($text, $e.Pattern, $rep, 'Multiline')
    }
    [IO.File]::WriteAllBytes($path, $utf8.GetBytes($text))
    $check = [Text.Encoding]::UTF8.GetString([IO.File]::ReadAllBytes($path))
    foreach ($e in $edits) {
        if (-not [regex]::IsMatch($check, $e.Verify, 'Multiline')) { Write-Output "VERIFY FAILED  $name"; return }
    }
    Write-Output "OK  $name"
}

$homepage = '// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods'
$simpleEdits = @(
    @{ Pattern = '(?m)^(// @github[ \t]+https://github\.com/DavidHiFi)(\r?)$'; Replace = "`${1}`n$homepage`${2}"; Verify = '(?m)^// @homepage\s+https://github\.com/DavidHiFi/davids-windhawk-mods\r?$' }
)
$treeEdits = @(
    @{ Pattern = '(?m)^// @github[ \t]+https://github\.com/Languster(\r?)$'; Replace = "// @github          https://github.com/DavidHiFi`n$homepage`${1}"; Verify = '(?m)^// @github\s+https://github\.com/DavidHiFi\r?$' },
    @{ Pattern = '(?m)^# Explorer TreeItem Tweaker(\r?)$'; Replace = '# Explorer TreeItem Tweaker Plus${1}'; Verify = '(?m)^# Explorer TreeItem Tweaker Plus\r?$' },
    @{ Pattern = '(?m)^## Credits\r?\n'; Replace = "## Credits`n`n" + 'Based on [Explorer TreeItem Tweaker](https://windhawk.net/mods/explorer-treeitem-tweaker) by [Languster](https://github.com/Languster). Plus changes by DavidHiFi.' + "`n"; Verify = '(?m)^Based on \[Explorer TreeItem Tweaker\]' }
)
$creditsInsert = {
    param($block)
    @{ Pattern = '(\r?\n)\*/(\r?\n)// ==/WindhawkModReadme==' ; Replace = "`${1}`n## Credits`n`n$block`n*/`${2}// ==/WindhawkModReadme=="; Verify = '(?m)^## Credits' }
}

if ($Group -eq 'Workspace') {
    Apply-Edits "$ws\davids-windhawk-mods\mods\local\simple-window-switcher-plus\simple-window-switcher-plus.wh.cpp" $simpleEdits
    Apply-Edits "$ws\Windhawk\explorer-treeitem-tweaker-plus\local@explorer-treeitem-tweaker-plus.wh.cpp" $treeEdits
    $cc = "$ws\davids-windhawk-mods\mods\local\center-titlebar-fork\center-titlebar-fork.wh.cpp"
    Apply-Edits $cc @(
        @{ Pattern = '(?m)^// @id(\s+)center-titlebar-fork(\r?)$'; Replace = '// @id$1center-titlebar-plus$2'; Verify = '(?m)^// @id\s+center-titlebar-plus\r?$' },
        @{ Pattern = '(?m)^// @name(\s+)Center Titlebar - Fork(\r?)$'; Replace = '// @name$1Center Titlebar Plus$2'; Verify = '(?m)^// @name\s+Center Titlebar Plus\r?$' },
        @{ Pattern = '(?m)^# Center Titlebar \(fork\)(\r?)$'; Replace = '# Center Titlebar Plus${1}'; Verify = '(?m)^# Center Titlebar Plus\r?$' },
        (& $creditsInsert 'Based on [center-titlebar](https://windhawk.net/mods/center-titlebar) by rounk-ctrl, which is a port of [WinCenterTitle](https://github.com/valinet/WinCenterTitle) by valinet. MIT.')
    )
} else {
    Apply-Edits "$live\local@simple-window-switcher-plus.wh.cpp" $simpleEdits
    Apply-Edits "$live\local@explorer-treeitem-tweaker-plus.wh.cpp" $treeEdits
    Apply-Edits "$live\local@taskbar-ai-quota-plus.wh.cpp" @(
        (& $creditsInsert 'Based on [Taskbar AI Quota Bars](https://windhawk.net/mods/taskbar-ai-quota) by Cleroth. MIT.')
    )
}
