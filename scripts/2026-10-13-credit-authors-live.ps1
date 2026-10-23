# Applies the author credits and the Everything Start Menu Plus rename to the live
# ModsSource copies. Metadata only: no code, version or settings change, so no rebuild.
# Run elevated through H:\System Configuration\scripts\Invoke-Elevated.ps1.
param([switch]$Audit)

$ErrorActionPreference = 'Stop'
$live = 'C:\ProgramData\Windhawk\ModsSource'
$backup = 'H:\Windhawk Configuration\backups\2026-10-13-author-credits'
$utf8 = New-Object System.Text.UTF8Encoding($false)

function Apply-Edits([string]$path, [object[]]$edits) {
    $name = Split-Path $path -Leaf
    if (-not (Test-Path -LiteralPath $path)) { Write-Output "MISSING  $name"; return }
    $bytes = [IO.File]::ReadAllBytes($path)
    $text = [Text.Encoding]::UTF8.GetString($bytes)
    if ([Convert]::ToBase64String($bytes) -ne [Convert]::ToBase64String([Text.Encoding]::UTF8.GetBytes($text))) {
        Write-Output "SKIP (not clean UTF-8)  $name"; return
    }
    foreach ($e in $edits) {
        $hits = ([regex]::Matches($text, $e.Pattern, 'Multiline')).Count
        if ($hits -ne 1) { Write-Output "SKIP (pattern hits=$hits)  $name  :: $($e.Pattern)"; return }
    }
    if ($Audit) { Write-Output "AUDIT ok  $name"; return }
    New-Item -ItemType Directory -Force -Path $backup | Out-Null
    Copy-Item -LiteralPath $path -Destination (Join-Path $backup $name) -Force
    foreach ($e in $edits) { $text = [regex]::Replace($text, $e.Pattern, $e.Replace, 'Multiline') }
    [IO.File]::WriteAllBytes($path, $utf8.GetBytes($text))
    $check = [Text.Encoding]::UTF8.GetString([IO.File]::ReadAllBytes($path))
    foreach ($e in $edits) {
        if (-not [regex]::IsMatch($check, $e.Verify, 'Multiline')) { Write-Output "VERIFY FAILED  $name"; return }
    }
    Write-Output "OK  $name  (backup: $backup\$name)"
}

function Author([string]$from, [string]$to) {
    @{ Pattern = "^(// @author[ \t]+)$from[ \t]*(\r?)$"; Replace = "`${1}$to`${2}"; Verify = "^// @author[ \t]+$([regex]::Escape($to))[ \t]*\r?$" }
}

function Lit([string]$from, [string]$to) {
    @{ Pattern = [regex]::Escape($from); Replace = $to.Replace('$', '$$'); Verify = [regex]::Escape($to) }
}

Apply-Edits "$live\local@start-everything-plus.wh.cpp" @(
    (Lit '// @name            Everything & Power Tools in the Start Menu Plus' '// @name            Everything Start Menu Plus'),
    (Author 'DavidHiFi' 'DavidHiFi, bardelyne'),
    (Lit '# Everything & Power Tools in the Start Menu Plus' '# Everything Start Menu Plus'),
    (Lit 'Everything Start menu Plus preview' 'Everything Start Menu Plus preview')
)
Apply-Edits "$live\local@better-volume-mixer-plus.wh.cpp" @( (Author 'DavidHiFi' 'DavidHiFi, 0Allu') )
Apply-Edits "$live\local@shell-font-changer.wh.cpp" @( (Author 'DavidHiFi' 'DavidHiFi, Gabriela Cristei') )
Apply-Edits "$live\local@simple-window-switcher-plus.wh.cpp" @( (Author 'DavidHiFi' 'DavidHiFi, Lone, valinet, Asteski, bropines, caliberda') )
Apply-Edits "$live\local@taskbar-ai-quota-plus.wh.cpp" @( (Author 'DavidHiFi' 'DavidHiFi, Cleroth') )
Apply-Edits "$live\local@taskbar-system-info-weather.wh.cpp" @( (Author 'DavidHiFi' 'DavidHiFi, Yevhenii Starychenko, m417z, Salyts') )
Apply-Edits "$live\local@translucent-flyouts.wh.cpp" @( (Author 'DavidHiFi' 'DavidHiFi, ALTaleX531') )
Apply-Edits "$live\local@window-manager.wh.cpp" @( (Author 'DavidHiFi' 'DavidHiFi, m417z, Asteski, TomberWolf, RamonUnch, Stefan Sundin') )
Apply-Edits "$live\local@windhawk-styler.wh.cpp" @( (Author 'DavidHiFi' 'DavidHiFi, Ingan121') )
Apply-Edits "$live\local@taskbar-audio-visualizer.wh.cpp" @( (Author 'DavidHiFi' 'DavidHiFi, Salyts') )
Apply-Edits "$live\local@explorer-treeitem-tweaker-plus.wh.cpp" @( (Author 'Languster' 'DavidHiFi, Languster, crazyboyybs, valinet') )
