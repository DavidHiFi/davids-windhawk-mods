# Stop the AI quota dashboard from raising the tray's height (which pushes the tray icons and clock up).
# -Install: back up, add negative vertical margins to the dashboard root, recompile the mod (hot reload, no Explorer restart).
# -Rollback: restore the backed-up source and recompile.  Run elevated.
param([switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$id   = 'local@taskbar-ai-quota-plus'
$src  = "C:\ProgramData\Windhawk\ModsSource\$id.wh.cpp"
$bdir = 'H:\Windhawk Configuration\backups\2026-10-24-quota-tray-height'
$cli  = 'C:\Program Files\Windhawk\windhawk-cli.exe'
$key  = "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id"
New-Item -ItemType Directory -Force $bdir | Out-Null
"before lib: $((Get-ItemProperty $key).LibraryFileName)"

if ($Install) {
    if (-not (Test-Path "$bdir\source-before.wh.cpp")) {
        Copy-Item $src "$bdir\source-before.wh.cpp"
        reg export "HKLM\SOFTWARE\Windhawk\Engine\Mods\$id" "$bdir\mod-key-before.reg" /y | Out-Null
    }
    $text = [IO.File]::ReadAllText($src)
    $anchor = "        root.VerticalAlignment(VerticalAlignment::Center);`n"
    if ($text.Contains('root.Margin({0, -16, 0, -16});')) { 'patch already present' }
    else {
        if (-not $text.Contains($anchor)) { $anchor = $anchor -replace "`n", "`r`n" }
        if (-not $text.Contains($anchor)) { 'ABORT: anchor not found'; exit 1 }
        $nl = if ($anchor.EndsWith("`r`n")) { "`r`n" } else { "`n" }
        $add = "        // Negative vertical margins keep the dashboard from raising the tray's measured$nl" +
               "        // height; a taller tray frame pushes the native icons and clock off center.$nl" +
               "        root.Margin({0, -16, 0, -16});$nl"
        [IO.File]::WriteAllText($src, $text.Replace($anchor, $anchor + $add), (New-Object Text.UTF8Encoding $false))
        'patched source'
    }
}
elseif ($Rollback) { Copy-Item "$bdir\source-before.wh.cpp" $src -Force; 'restored source' }
else { 'pass -Install or -Rollback'; exit 1 }

$ErrorActionPreference = 'Continue'   # the CLI writes progress to stderr
& $cli mod compile $id 2>&1 | ForEach-Object { "$_" }
"cli-exit=$LASTEXITCODE"
"after lib: $((Get-ItemProperty $key).LibraryFileName)  SCT: $((Get-ItemProperty $key).SettingsChangeTime)"
"patch present: $((Get-Content $src -Raw).Contains('root.Margin({0, -16, 0, -16});'))"
