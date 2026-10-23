<#
.SYNOPSIS
    Compiles scripts\tools\FlyoutTestWindow.cs into FlyoutTestWindow.exe.

.DESCRIPTION
    Runs under Windows PowerShell 5.1 (Add-Type binds to the .NET Framework
    csc, where System.Windows.Forms is a direct reference). Output:
    scripts\tools\FlyoutTestWindow.exe.
#>
[CmdletBinding()]
param(
    [string]$Source,
    [string]$Output,
    [ValidateSet('x64', 'x86', 'both')]
    [string]$Arch = 'x64'
)

$ErrorActionPreference = 'Stop'
$here = Split-Path -Parent $MyInvocation.MyCommand.Path
if (-not $Source) { $Source = Join-Path $here 'FlyoutTestWindow.cs' }

if (-not (Test-Path -LiteralPath $Source)) { throw "missing source: $Source" }

# csc embeds a default manifest unless told otherwise, which would block the
# visual-styles activation context. Compile with the v6 common-controls manifest
# embedded so menus/tooltips/dropdowns render themed (the mod styles themed
# flyouts).
$manifest = Join-Path $here 'FlyoutTestWindow.manifest'
if (-not (Test-Path -LiteralPath $manifest)) { throw "missing manifest: $manifest" }

# x86 output is named FlyoutTestWindow32.exe so both can sit side by side and
# tests can exercise the 32-bit mod DLL.
$targets = @(
    [pscustomobject]@{
        Name = 'x64'
        Csc  = Join-Path $env:WINDIR 'Microsoft.NET\Framework64\v4.0.30319\csc.exe'
        Out  = if ($Output) { $Output } else { Join-Path $here 'FlyoutTestWindow.exe' }
        Platform = 'x64'
    },
    [pscustomobject]@{
        Name = 'x86'
        Csc  = Join-Path $env:WINDIR 'Microsoft.NET\Framework\v4.0.30319\csc.exe'
        Out  = Join-Path $here 'FlyoutTestWindow32.exe'
        Platform = 'x86'
    }
) | Where-Object { $Arch -eq 'both' -or $_.Name -eq $Arch }

foreach ($t in $targets) {
    if (-not (Test-Path -LiteralPath $t.Csc)) { throw "missing csc: $($t.Csc)" }
    & $t.Csc /nologo /target:winexe ('/platform:{0}' -f $t.Platform) `
        ('/out:{0}' -f $t.Out) ('/win32manifest:{0}' -f $manifest) `
        /r:System.Windows.Forms.dll /r:System.Drawing.dll $Source
    if ($LASTEXITCODE -ne 0) { throw "csc ($($t.Name)) failed with exit code $LASTEXITCODE" }
    if (-not (Test-Path -LiteralPath $t.Out)) { throw "compile ($($t.Name)) produced no output" }
    Write-Host "built: $($t.Out)"
}
