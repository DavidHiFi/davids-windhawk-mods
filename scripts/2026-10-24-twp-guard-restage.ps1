# Restages the Translucent Windows Plus guard for the 1.8.4 build (Explorer dialog black fix).
# Run elevated. Copies the live DLLs and source as the new pristine set, rewrites the guard's
# pinned names and hashes, and clears the suspend marker. Log: work\2026-10-24-twp-black-dialogs\restage.log
$ErrorActionPreference = 'Stop'
$ws   = 'H:\Windhawk Configuration'
$logf = "$ws\work\2026-10-24-twp-black-dialogs\restage.log"
trap { "ERROR: $_" | Out-File $logf -Append; exit 1 }
"$(Get-Date -Format 'h:mm:ss tt') restage" | Out-File $logf
$key  = 'HKLM:\SOFTWARE\Windhawk\Engine\Mods\local@translucent-windows-plus'
$dll  = (Get-ItemProperty $key).LibraryFileName
if ($dll -notlike '*_1.8.4_*') { throw "live DLL is $dll, expected 1.8.4" }
$gd   = "$ws\Windhawk\translucent-windows-plus\guard"
$src  = 'C:\ProgramData\Windhawk\ModsSource\local@translucent-windows-plus.wh.cpp'
$dev  = "$ws\Windhawk\translucent-windows-plus\local@translucent-windows-plus.wh.cpp"
$bk   = "$ws\backups\2026-10-24-twp-black-dialogs\guard-before"
New-Item -ItemType Directory $bk -Force | Out-Null
Copy-Item "$ws\scripts\2026-10-24-translucent-windows-plus-guard.ps1", $dev -Destination $bk -Force
foreach ($a in '64','32') { Copy-Item "C:\ProgramData\Windhawk\Engine\Mods\$a\$dll" "$gd\$a\$dll" -Force }
Copy-Item $src $dev -Force
# Top-level values only, so a heal never rewrites the user's Settings (RuledPrograms[31] and later).
$k = Get-ItemProperty $key
@"
Windows Registry Editor Version 5.00

[HKEY_LOCAL_MACHINE\SOFTWARE\Windhawk\Engine\Mods\local@translucent-windows-plus]
"LibraryFileName"="$dll"
"Disabled"=dword:00000000
"Version"="1.8.4"
"LoggingEnabled"=dword:00000000
"@ | Out-File "$gd\local@translucent-windows-plus-1.8.4.reg" -Encoding unicode
$h = @{ fork = (Get-FileHash $src).Hash; d64 = (Get-FileHash "$gd\64\$dll").Hash; d32 = (Get-FileHash "$gd\32\$dll").Hash }
$g = "$ws\scripts\2026-10-24-translucent-windows-plus-guard.ps1"
$c = [IO.File]::ReadAllText($g)
$c = $c -replace "\`$fixDll    = '[^']+'", "`$fixDll    = '$dll'"
$c = $c -replace "\`$forkHash  = '[^']+'", "`$forkHash  = '$($h.fork)'"
$c = $c -replace "\`$dll64Hash = '[^']+'", "`$dll64Hash = '$($h.d64)'"
$c = $c -replace "\`$dll32Hash = '[^']+'", "`$dll32Hash = '$($h.d32)'"
$c = $c.Replace("-ne '1.8.3')", "-ne '1.8.4')").Replace("'local@translucent-windows-plus-1.8.3-1.reg'", "'local@translucent-windows-plus-1.8.4.reg'").Replace("-Name Version -Value '1.8.3'", "-Name Version -Value '1.8.4'")
[IO.File]::WriteAllText($g, $c)
Remove-Item 'C:\ProgramData\Windhawk\ModsWritable\translucent-guard.suspend' -Force -ErrorAction SilentlyContinue
"dll=$dll`n$($h | ConvertTo-Json)" | Out-File $logf -Append
& pwsh -NoProfile -ExecutionPolicy Bypass -File $g -Action Enforce; "enforce exit $LASTEXITCODE" | Out-File $logf -Append
& pwsh -NoProfile -ExecutionPolicy Bypass -File $g -Action Audit | Out-File $logf -Append
