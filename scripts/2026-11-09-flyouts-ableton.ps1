# Let Seamless Flyouts style the menus of apps it skipped. Runs ELEVATED.
# Ableton Live: standing owner exception (2026-09-28), asked again 2026-11-09.
# Notepad++: only ever kept out to skip window blur (its rule was "none"); no window rule now.
# Neither app has a window rule in the mod, so only their menus change.
# FreeDictate and Windows Terminal stay out: they draw their own materials.
# No engine restart, no app restart.
#   -Action apply -Drop 'Ableton*.exe'   remove those names from ExcludeCustom (backup first)
#   -Action rollback                      put the original 2026-11-09 value back
param([ValidateSet('apply', 'rollback')][string]$Action = 'apply', [string[]]$Drop = @('Ableton*.exe'))
$ErrorActionPreference = 'Stop'
$k    = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@seamless-flyouts'
$bk   = 'H:\Windhawk Configuration\backups\2026-11-09\menu-skin'
$log  = Join-Path $bk 'ableton-receipt.txt'
$orig = 'FreeDictate.exe|Ableton*.exe|notepad++.exe|WindowsTerminal.exe'
New-Item -ItemType Directory -Force $bk | Out-Null
function Say($t) { Add-Content -Path $log -Value "$(Get-Date -Format 'h:mm:ss tt') $t" -Encoding UTF8 }
$now = (Get-ItemProperty $k).ExcludeCustom
Say "before ExcludeCustom=$now"
if ($Action -eq 'apply') {
    $f = Join-Path $bk "seamless-flyouts-key.reg.bak-$(Get-Date -Format yyyyMMdd-HHmm)"
    reg export 'HKLM\SOFTWARE\Windhawk\Engine\Mods\local@seamless-flyouts' $f /y | Out-Null
    if (-not (Test-Path $f)) { Say 'FAIL backup'; exit 1 }
    $new = (@($now -split '\|') | Where-Object { $_ -and ($Drop -notcontains $_) }) -join '|'
    Set-ItemProperty $k -Name ExcludeCustom -Value $new
} else {
    Set-ItemProperty $k -Name ExcludeCustom -Value $orig
}
Set-ItemProperty $k -Name SettingsChangeTime -Value ([int][DateTimeOffset]::UtcNow.ToUnixTimeSeconds()) -Type DWord
Say "after ExcludeCustom=$((Get-ItemProperty $k).ExcludeCustom) DONE $Action"
