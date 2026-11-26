# Explorer icon: Catppuccin Mocha blue folder instead of the niivu pack's pink one (owner, 2026-11-26).
# Run elevated (Invoke-Elevated.ps1).
#   -Install   copy the live Catppuccin theme into a new dated folder, swap in the blue explorer.dll,
#              point Resource Redirect's stored theme folder (LocalStorage themeFolder_Catppuccin) at it
#   -Rollback  point the stored theme folder back at the original 'Catppuccin' folder
# The base pack's explorer.dll wins over themePaths, so the override has to live in the base pack.
# iconTheme is never touched, so the mod does not ask to restart Explorer. The live folder is never
# overwritten: running programs keep its DLLs open (memory: resource-redirect-theme-folder-locked).
param([switch]$Install, [switch]$Rollback)
$ErrorActionPreference = 'Stop'
$job = 'D:\Agent Work\2026-11-26-explorer-blue'
$blue = "$job\explorer-blue.dll"
$storage = 'C:\ProgramData\Windhawk\Engine\ModsWritable\mod-storage\icon-resource-redirect'
$ls = 'HKLM:\SOFTWARE\Windhawk\Engine\ModsWritable\icon-resource-redirect\LocalStorage'
$modKey = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\icon-resource-redirect'
$bk = 'H:\Windhawk Configuration\backups\2026-11-26-explorer-blue'
$stamp = Get-Date -Format 'yyyyMMdd-HHmm'
New-Item -ItemType Directory -Force $bk | Out-Null
$log = "$bk\log.txt"
function Write-Log([string]$t) { "$(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')  $t" | Tee-Object -FilePath $log -Append }
function Set-Folder([string]$name) {
    Set-ItemProperty -LiteralPath $ls 'themeFolder_Catppuccin' $name -Type String
    Set-ItemProperty -LiteralPath $modKey 'SettingsChangeTime' ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
}
function Refresh-Icons {
    Start-Process "$env:WINDIR\System32\ie4uinit.exe" -ArgumentList '-show' -WindowStyle Hidden -Wait
    $psi = New-Object Diagnostics.ProcessStartInfo
    $psi.FileName = (Get-Command python).Source
    $psi.Arguments = '"' + "$PSScriptRoot\Refresh-TaskbarIcons.py" + '" --apply --receipt "' + "$bk\taskbar-icons-$stamp.json" + '"'
    $psi.UseShellExecute = $false; $psi.CreateNoWindow = $true
    $psi.RedirectStandardOutput = $true; $psi.RedirectStandardError = $true
    $p = [Diagnostics.Process]::Start($psi)
    $o = $p.StandardOutput.ReadToEnd(); $e = $p.StandardError.ReadToEnd(); $p.WaitForExit()
    Write-Log "refresh exit $($p.ExitCode): $($o.Trim()) $($e.Trim())"
}

$old = (Get-ItemProperty -LiteralPath $ls).themeFolder_Catppuccin
Write-Log "themeFolder_Catppuccin was '$old'"
if ($Install) {
    & reg.exe export 'HKLM\SOFTWARE\Windhawk\Engine\ModsWritable\icon-resource-redirect\LocalStorage' "$bk\LocalStorage.bak-$stamp.reg" /y | Out-Null
    $src = Join-Path $storage 'Catppuccin'
    $name = "Catppuccin-blue-$stamp"
    $dest = Join-Path $storage $name
    Copy-Item -LiteralPath $src -Destination $dest -Recurse
    Copy-Item -LiteralPath $blue -Destination "$dest\Windhawk Resources\explorer.dll" -Force
    $want = (Get-ChildItem $src -Recurse -File).Count
    $n = (Get-ChildItem $dest -Recurse -File).Count
    $h = (Get-FileHash "$dest\Windhawk Resources\explorer.dll").Hash
    if ($n -ne $want -or $h -ne (Get-FileHash $blue).Hash) { throw "copy incomplete: $n of $want files, hash $h" }
    Set-Folder $name
    Write-Log "installed: $n files, themeFolder_Catppuccin='$name'"
    Refresh-Icons
}
if ($Rollback) {
    Set-Folder 'Catppuccin'
    Write-Log "rollback: themeFolder_Catppuccin='Catppuccin'"
    Refresh-Icons
}
Write-Log "now '$((Get-ItemProperty -LiteralPath $ls).themeFolder_Catppuccin)'"
