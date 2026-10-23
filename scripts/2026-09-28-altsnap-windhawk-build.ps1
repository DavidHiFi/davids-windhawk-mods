<#
.SYNOPSIS
    Builds the local @alt-snap-drag Windhawk mod (x64 and x86) from its source.

.DESCRIPTION
    Compiles Windhawk\altsnap-fork\alt-snap.wh.cpp with the Windhawk-bundled
    clang++ for both architectures, the same way the Windhawk Developer UI does:
    one DLL per architecture, linked against windhawk.lib from the matching
    engine folder. Writes local@alt-snap-drag_1.2.0_1_64.dll and _32.dll next to
    the source and logs to reports\2026-09-28\altsnap-windhawk-build.log.

    No elevation needed. Nothing outside the output folder and the log is
    written. Pairs with scripts\2026-09-28-altsnap-windhawk-install.ps1.

.EXAMPLE
    .\2026-09-28-altsnap-windhawk-build.ps1
#>
[CmdletBinding()]
param(
    [string]$Source    = 'H:\System Configuration\Windhawk\altsnap-fork\alt-snap.wh.cpp',
    [string]$OutDir    = 'H:\System Configuration\Windhawk\altsnap-fork',
    [string]$LogPath   = 'H:\System Configuration\reports\2026-09-28\altsnap-windhawk-build.log',
    [string]$Compiler  = 'C:\Program Files\Windhawk\Compiler\bin\clang++.exe',
    [string]$IncludeDir = 'C:\Program Files\Windhawk\Compiler\include',
    [string]$EngineLibRoot = 'C:\Program Files\Windhawk\Engine\1.7.3_2',
    [string]$ModId     = 'local@alt-snap-drag',
    [string]$ModIdHeader = 'H:\System Configuration\Windhawk\altsnap-fork\altsnap-modid.h'
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

$targets = @(
    [pscustomobject]@{
        Arch = 'x86_64-w64-mingw32'
        Lib  = Join-Path $EngineLibRoot '64\windhawk.lib'
        Out  = Join-Path $OutDir 'local@alt-snap-drag_1.2.2_1_64.dll'
    },
    [pscustomobject]@{
        Arch = 'i686-w64-mingw32'
        Lib  = Join-Path $EngineLibRoot '32\windhawk.lib'
        Out  = Join-Path $OutDir 'local@alt-snap-drag_1.2.2_1_32.dll'
    }
)

Write-Log "build start: $Source"
# The mod ID is passed via a force-included header instead of -D on the command
# line: Windows PowerShell drops the quotes from -DWH_MOD_ID=L"..." and breaks
# the string concatenation in the source.
Set-Content -LiteralPath $ModIdHeader -Value ('#define WH_MOD_ID L"{0}"' -f $ModId) -Encoding Ascii
Write-Log "mod id header: $ModIdHeader"
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
        $Source, $t.Lib, '-lcomctl32',
        '-o', $t.Out
    )
    & $Compiler @compileArgs
    if ($LASTEXITCODE -ne 0 -or -not (Test-Path -LiteralPath $t.Out)) {
        Write-Log "FAILED: $leaf (exit=$LASTEXITCODE)"
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
