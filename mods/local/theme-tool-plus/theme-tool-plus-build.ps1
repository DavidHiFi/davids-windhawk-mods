<#
.SYNOPSIS
    Builds the local Theme Tool Plus Windhawk mod (x64 and x86).

.DESCRIPTION
    Compiles Windhawk\theme-tool-plus\theme-tool-plus.wh.cpp with the
    Windhawk-bundled clang++ for both architectures, the same way the Windhawk
    Developer UI does: one DLL per architecture, linked against windhawk.lib
    from the matching engine folder, plus the libraries named in the mod's
    @compilerOptions line. Output DLLs:
      local@theme-tool-plus_<version>_1_64.dll / _32.dll
    next to the source. The mod id is passed via a force-included header
    because PowerShell 5.1 mangles -DWH_MOD_ID=L"..." quoting. No elevation
    needed. Pairs with theme-tool-plus-install.ps1 in the same folder.

.EXAMPLE
    .\theme-tool-plus-build.ps1
    .\theme-tool-plus-build.ps1 -Arch x64
#>
[CmdletBinding()]
param(
    [string]$Source     = (Join-Path $PSScriptRoot 'theme-tool-plus.wh.cpp'),
    [string]$OutDir     = (Join-Path $env:TEMP 'theme-tool-plus-build'),
    [string]$LogPath    = (Join-Path (Join-Path $env:TEMP 'theme-tool-plus-build') 'build.log'),
    [string]$Compiler   = 'C:\Program Files\Windhawk\Compiler\bin\clang++.exe',
    [string]$IncludeDir = 'C:\Program Files\Windhawk\Compiler\include',
    [string]$EngineLibRoot = 'C:\Program Files\Windhawk\Engine\2.0.0_1',
    [string]$ModId      = 'local@theme-tool-plus',
    [string]$ModIdHeader = (Join-Path (Join-Path $env:TEMP 'theme-tool-plus-build') 'ttp-modid.h'),
    [ValidateSet('x64','x86','both')]
    [string]$Arch       = 'both'
)

$ErrorActionPreference = 'Stop'

$logDir = Split-Path -Parent $LogPath
if (-not (Test-Path -LiteralPath $logDir)) {
    New-Item -ItemType Directory -Path $logDir -Force | Out-Null
}
function Write-Log {
    param([string]$Message)
    $line = '{0} {1}' -f (Get-Date -Format 'yyyy-MM-dd HH:mm:ss'), $Message
    Write-Host $line
    Add-Content -LiteralPath $LogPath -Value $line -Encoding UTF8
}

foreach ($p in @($Source, $Compiler, (Join-Path $IncludeDir 'windhawk_api.h'))) {
    if (-not (Test-Path -LiteralPath $p)) {
        Write-Log "missing: $p"
        exit 11
    }
}
if (-not (Test-Path -LiteralPath (Join-Path $EngineLibRoot '64\windhawk.lib'))) {
    Write-Log "missing engine lib root: $EngineLibRoot"
    exit 11
}

$versionMatch = Select-String -LiteralPath $Source -Pattern '^\s*//\s*@version\s+(\S+)' | Select-Object -First 1
if (-not $versionMatch) {
    Write-Log "cannot parse @version from $Source"
    exit 12
}
$version = $versionMatch.Matches[0].Groups[1].Value

$optionsMatch = Select-String -LiteralPath $Source -Pattern '^\s*//\s*@compilerOptions\s+(.+)$' | Select-Object -First 1
$modOptions = @()
if ($optionsMatch) {
    $modOptions = $optionsMatch.Matches[0].Groups[1].Value.Trim() -split '\s+'
}
Write-Log "mod version: $version; compilerOptions: $($modOptions -join ' ')"

$allTargets = @(
    [pscustomobject]@{
        Name = 'x64'
        Arch = 'x86_64-w64-mingw32'
        Lib  = Join-Path $EngineLibRoot '64\windhawk.lib'
        Out  = Join-Path $OutDir ('{0}_{1}_1_64.dll' -f $ModId, $version)
    },
    [pscustomobject]@{
        Name = 'x86'
        Arch = 'i686-w64-mingw32'
        Lib  = Join-Path $EngineLibRoot '32\windhawk.lib'
        Out  = Join-Path $OutDir ('{0}_{1}_1_32.dll' -f $ModId, $version)
    }
)
$targets = $allTargets | Where-Object { $Arch -eq 'both' -or $_.Name -eq $Arch }

Set-Content -LiteralPath $ModIdHeader -Value ('#define WH_MOD_ID L"{0}"' -f $ModId) -Encoding Ascii
Write-Log "build start: $Source"
$failed = $false
foreach ($t in $targets) {
    $leaf = Split-Path $t.Out -Leaf
    Write-Log "compiling $leaf ($($t.Arch))"
    $compileArgs = @(
        '-std=c++23', '-O2', '-shared',
        '-target', $t.Arch,
        '-DUNICODE', '-D_UNICODE',
        '-DWINVER=0x0A00', '-D_WIN32_WINNT=0x0A00', '-D_WIN32_IE=0x0A00',
        '-DNTDDI_VERSION=0x0A000008',
        '-D__USE_MINGW_ANSI_STDIO=0',
        '-DWH_MOD',
        '-include', $ModIdHeader,
        '-include', 'windhawk_api.h',
        '-I', $IncludeDir,
        '-Wno-pragma-pack', '-Wno-pragma-system-header-outside-header',
        '-Wl,--export-all-symbols',
        $Source, $t.Lib
    ) + $modOptions + @('-o', $t.Out)
    $output = & $Compiler @compileArgs 2>&1
    $exit = $LASTEXITCODE
    foreach ($line in $output) { Write-Log "  $line" }
    if ($exit -ne 0 -or -not (Test-Path -LiteralPath $t.Out)) {
        Write-Log "FAILED: $leaf (exit=$exit)"
        $failed = $true
        continue
    }
    $hash = (Get-FileHash -LiteralPath $t.Out -Algorithm SHA256).Hash
    Write-Log "ok: $leaf sha256=$hash"
}

if ($failed) {
    Write-Log 'BUILD FAILED'
    exit 20
}
Write-Log 'BUILD OK'
exit 0
