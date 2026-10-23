<#
.SYNOPSIS
    Builds the local translucent-flyouts Windhawk mod (x64 and x86) from its source.

.DESCRIPTION
    Compiles Windhawk\translucency-flyouts\translucent-flyouts.wh.cpp with the
    Windhawk-bundled clang++ for both architectures, the same way the Windhawk
    Developer UI does: one DLL per architecture, linked against windhawk.lib
    from the matching engine folder. Output DLLs:
      local@translucent-flyouts_<version>_1_64.dll / _32.dll
    next to the source; log in reports\2026-09-28\translucent-flyouts-build.log.
    Release builds carry no debug logging; pass -DebugLog to compile it in.

    The version is parsed from the mod source header (@version), and the mod id
    local@translucent-flyouts is passed via a force-included header because
    PowerShell 5.1 mangles -DWH_MOD_ID=L"..." quoting.

    No elevation needed. Pairs with scripts\2026-09-28-translucent-flyouts-install.ps1.

.EXAMPLE
    .\2026-09-28-translucent-flyouts-build.ps1
    .\2026-09-28-translucent-flyouts-build.ps1 -Arch x64
#>
[CmdletBinding()]
param(
    [string]$Source     = 'H:\Windhawk Configuration\Windhawk\translucency-flyouts\translucent-flyouts.wh.cpp',
    [string]$OutDir     = 'H:\Windhawk Configuration\Windhawk\translucency-flyouts',
    [string]$LogPath    = 'H:\Windhawk Configuration\reports\2026-09-28\translucent-flyouts-build.log',
    [string]$Compiler   = 'C:\Program Files\Windhawk\Compiler\bin\clang++.exe',
    [string]$IncludeDir = 'C:\Program Files\Windhawk\Compiler\include',
    [string]$EngineLibRoot = 'C:\Program Files\Windhawk\Engine\1.7.3_2',
    [string]$ModId      = 'local@translucent-flyouts',
    [string]$ModIdHeader = 'H:\Windhawk Configuration\Windhawk\translucency-flyouts\translucent-flyouts-modid.h',
    [ValidateSet('x64','x86','both')]
    [string]$Arch       = 'both',
    [switch]$DebugLog
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

# Assemble the single-file mod from the modular sources: the settings block
# (settings-block.inc, the controller schema) replaces the placeholder in
# 00-foundation.inc, then the code parts are concatenated in name order.
$srcDir = Join-Path (Split-Path -Parent $Source) 'src'
$parts = @('00-foundation.inc', '10-settings.inc', '30-engine.inc')
$settingsFile = Join-Path $srcDir 'settings-block.inc'
if ((Test-Path -LiteralPath $srcDir) -and (Test-Path -LiteralPath $settingsFile)) {
    $settings = Get-Content -LiteralPath $settingsFile -Raw
    $assembled = ''
    foreach ($part in $parts) {
        $path = Join-Path $srcDir $part
        if (-not (Test-Path -LiteralPath $path)) {
            Write-Log "missing part: $path"
            exit 10
        }
        $content = Get-Content -LiteralPath $path -Raw
        if ($part -eq '00-foundation.inc') {
            $content = $content.Replace('__SETTINGS_BLOCK__', $settings.TrimEnd())
        }
        $assembled += $content + "`r`n"
    }
    Set-Content -LiteralPath $Source -Value $assembled -Encoding UTF8
    Write-Log "assembled $($parts.Count) parts + settings -> $Source"
}

foreach ($p in @($Source, $Compiler, (Join-Path $IncludeDir 'windhawk_api.h'))) {
    if (-not (Test-Path -LiteralPath $p)) {
        Write-Log "missing: $p"
        exit 11
    }
}

$versionMatch = Select-String -LiteralPath $Source -Pattern '^\s*//\s*@version\s+(\S+)' | Select-Object -First 1
if (-not $versionMatch) {
    Write-Log "cannot parse @version from $Source"
    exit 12
}
$version = $versionMatch.Matches[0].Groups[1].Value
Write-Log "mod version: $version"

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
        '-fms-extensions',
        '-Wno-microsoft-template', '-Wno-microsoft-enum-forward-reference',
        '-Wno-pragma-pack', '-Wno-pragma-system-header-outside-header',
        '-Wno-unknown-pragmas', '-Wno-invalid-offsetof',
        '-include', $ModIdHeader,
        '-include', 'windhawk_api.h',
        '-I', $IncludeDir,
        '-Wl,--export-all-symbols',
        '-Wl,--allow-multiple-definition',
        $Source, $t.Lib,
        '-ld2d1', '-ldwrite', '-ldwmapi', '-luxtheme', '-lcomctl32', '-lgdi32',
        '-luser32', '-lole32', '-ladvapi32', '-lshlwapi', '-lversion', '-lmsimg32',
        '-loleaut32', '-luuid', '-lwindowscodecs',
        '-o', $t.Out
    )
    if ($DebugLog) { $compileArgs += '-DTF_DEBUG_LOG' }
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
