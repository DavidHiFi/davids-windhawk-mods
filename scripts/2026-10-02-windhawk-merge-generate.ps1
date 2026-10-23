<#
.SYNOPSIS
    Assembles the merged "David's Window Pack" Windhawk mod source from the
    three installed mods: local@alt-snap-drag (drag + AltSnap shortcuts),
    snap-commander (keyboard snapping) and move-window-to-monitor (monitor
    hotkeys).

.DESCRIPTION
    Reads the installed sources from C:\ProgramData\Windhawk\ModsSource,
    strips each metadata/readme/settings block, hoists #include lines to the
    top, renames the per-module Windhawk callbacks, wraps each module in its
    own namespace, strips the duplicated tool-mod boilerplate from snap and
    move (replaced by one shared dispatcher), and writes a single .wh.cpp
    with one merged metadata block, readme and settings block.

    Module order in the output is drag, snap, move. move stays last because
    it #defines WM_APP_SETTINGS_CHANGED, which would break snap's
    constexpr of the same name if it came first.

    Read-only against ModsWithSource inputs; writes only the output file.
    No elevation needed.

.EXAMPLE
    .\2026-10-02-windhawk-merge-generate.ps1
#>
[CmdletBinding()]
param(
    [string]$OutFile  = 'H:\System Configuration\Windhawk\window-pack\david-window-pack.wh.cpp',
    [string]$LogPath  = 'H:\System Configuration\reports\2026-10-02-windhawk-merge\generate.log',
    [string]$ModName  = "David's Window Pack",
    [string]$ModId    = 'david-window-pack',
    [string]$Author   = 'david high five',
    [string]$Version  = '1.0.0'
)

$ErrorActionPreference = 'Stop'

$Sources = [ordered]@{
    drag = 'C:\ProgramData\Windhawk\ModsSource\local@alt-snap-drag.wh.cpp'
    snap = 'C:\ProgramData\Windhawk\ModsSource\snap-commander.wh.cpp'
    move = 'C:\ProgramData\Windhawk\ModsSource\move-window-to-monitor.wh.cpp'
}
$Namespaces = @{
    drag = 'altSnapDrag'
    snap = 'snapCommander'
    move = 'moveToMonitor'
}

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

foreach ($p in $Sources.Values) {
    if (-not (Test-Path -LiteralPath $p)) { Write-Log "missing source: $p"; exit 11 }
}

# Remove one ==WindhawkMod*/...== block (metadata, readme or settings).
function Remove-Block {
    param([string[]]$Lines, [string]$Name)
    $start = "// ==WindhawkMod$Name=="
    $end   = "// ==/WindhawkMod$Name=="
    $out = New-Object System.Collections.Generic.List[string]
    $inBlock = $false
    foreach ($l in $Lines) {
        if (-not $inBlock -and $l.TrimEnd() -eq $start) { $inBlock = $true; continue }
        if ($inBlock) {
            if ($l.TrimEnd() -eq $end) { $inBlock = $false; continue }
            continue
        }
        $out.Add($l)
    }
    if ($inBlock) { throw "unterminated $start block" }
    , $out.ToArray()
}

# Rename a whole function whose body starts at its definition line; returns
# the lines before it, with the function removed, plus updated count state.
function Remove-Function {
    param([string[]]$Lines, [string]$Pattern)
    for ($i = 0; $i -lt $Lines.Count; $i++) {
        if ($Lines[$i] -match $Pattern) {
            $depth = 0
            $seenBrace = $false
            for ($j = $i; $j -lt $Lines.Count; $j++) {
                foreach ($ch in $Lines[$j].ToCharArray()) {
                    if ($ch -eq '{') { $depth++; $seenBrace = $true }
                    elseif ($ch -eq '}') { $depth-- }
                }
                if ($seenBrace -and $depth -le 0) {
                    $before = if ($i -gt 0) { $Lines[0..($i - 1)] } else { @() }
                    $after  = if ($j + 1 -le $Lines.Count - 1) { $Lines[($j + 1)..($Lines.Count - 1)] } else { @() }
                    return , (@($before) + @($after))
                }
            }
            throw "unterminated function at line $($i + 1): $($Lines[$i])"
        }
    }
    $Lines
}

# Everything from the shared "Mods as tools" banner to the end of file is
# the boilerplate the shared dispatcher replaces.
function Remove-TrailingToolBoilerplate {
    param([string[]]$Lines)
    for ($i = 0; $i -lt $Lines.Count; $i++) {
        if ($Lines[$i] -match 'Windhawk tool mod implementation for mods which don''t need to inject') {
            if ($i -gt 0) { return , $Lines[0..($i - 1)] }
            return , @()
        }
    }
    throw 'tool-mod boilerplate banner not found'
}

function Get-BodyAndIncludes {
    param([string]$Path, [string]$Key)
    $lines = Get-Content -LiteralPath $Path
    Write-Log "$Key : loaded $($lines.Count) lines"
    $lines = Remove-Block $lines ''
    $lines = Remove-Block $lines 'Readme'
    $lines = Remove-Block $lines 'Settings'
    Write-Log "$Key : blocks stripped -> $($lines.Count) lines"
    if ($Key -ne 'drag') {
        $lines = Remove-TrailingToolBoilerplate $lines
        Write-Log "$Key : tool boilerplate stripped -> $($lines.Count) lines"
    }
    if ($Key -eq 'drag') {
        # The DllMain must stay global; rename the module copy and forward.
        $lines = $lines | ForEach-Object { $_ -replace '\bBOOL WINAPI DllMain\(', 'BOOL WINAPI DragDllMain(' }
    }
    $includes = [System.Collections.Generic.List[string]]::new()
    $body = [System.Collections.Generic.List[string]]::new()
    foreach ($l in $lines) {
        if ($l -match '^\s*#\s*include\b') {
            $t = $l.Trim()
            if (-not $includes.Contains($t)) { $includes.Add($t) }
        } else {
            $body.Add($l)
        }
    }
    Write-Log "$Key : $($includes.Count) include lines hoisted, $($body.Count) body lines"
    [pscustomobject]@{ Includes = $includes; Body = $body.ToArray() }
}

# Engine-facing callbacks become module-local names.
function Rename-Callbacks {
    param([string[]]$Lines)
    $map = [ordered]@{
        'WhTool_ModSettingsChanged' = 'ToolModSettingsChanged'
        'WhTool_ModUninit'          = 'ToolModUninit'
        'WhTool_ModInit'            = 'ToolModInit'
        'Wh_ModAfterInit'           = 'ModAfterInit'
        'Wh_ModSettingsChanged'     = 'ModSettingsChanged'
        'Wh_ModUninit'              = 'ModUninit'
        'Wh_ModInit'                = 'ModInit'
    }
    $out = $Lines
    foreach ($from in $map.Keys) {
        $to = $map[$from]
        $out = $out | ForEach-Object { [regex]::Replace($_, "\b$from\b", $to) }
    }
    , @($out)
}

Write-Log "=== generate: id=$ModId name=$ModName ==="

$parts = @{}
$allIncludes = [System.Collections.Generic.List[string]]::new()
foreach ($key in $Sources.Keys) {
    $part = Get-BodyAndIncludes -Path $Sources[$key] -Key $key
    $part.Body = Rename-Callbacks $part.Body
    if ($key -eq 'move') {
        $part.Body = $part.Body | ForEach-Object {
            $_ -replace '^    int dstIdx = -1;', ('    if (fixedIndex >= (int)monitors.size()) fixedIndex = -1; // Missing saved display: use spatial movement.' + "`n" + '    int dstIdx = -1;')
        }
    }
    $parts[$key] = $part
    foreach ($inc in $part.Includes) {
        if (-not $allIncludes.Contains($inc)) { $allIncludes.Add($inc) }
    }
}

# --- header -----------------------------------------------------------------
$header = @"
// ==WindhawkMod==
// @id              $ModId
// @name            $ModName
// @description     Alt-drag window movement, keyboard snapping, monitor hotkeys and AltSnap keyboard shortcuts in one mod
// @version         $Version
// @author          $Author
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @license         GPL-3.0
// @include         *
// @include         windhawk.exe
// @compilerOptions -luser32 -ldwmapi -lgdi32 -lshcore -lcomctl32 -lshell32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# $ModName

One mod combining the three window-management mods it replaces:

* **AltSnap drag** (from local@alt-snap-drag, a fork of alt-drag by m417z,
  based on AltSnap by RamonUnch): hold Alt and drag with the left button to
  move a window, with the right button to resize it; Alt+F maximizes,
  Alt+M minimizes, Alt+Shift+Q closes, and a right click while moving
  toggles maximize.
* **Snap Commander** (by Asteski): move the active window to screen halves
  and corners with keyboard shortcuts (Alt+Q/W/E/R, Alt+U/I/J/K, Alt+G
  center, Alt+H maximize, Alt+M minimize, Alt+]/[ next/previous display
  and more; see the settings).
* **Move Window to Monitor** (by TomberWolf): move the active window to
  another monitor with hotkeys (default Alt+Shift+arrow keys).

Settings from all three mods are preserved in one settings page. The
mouse and in-process shortcut behaviour is unchanged from
local@alt-snap-drag; the keyboard tools run in one dedicated elevated
Windhawk tool process instead of two. The tool runs elevated so it can move
administrator windows. A saved monitor index that is no longer present uses
the nearest monitor in the requested direction.

Published under GPL-3.0 because the drag code derives from alt-drag.
*/
// ==/WindhawkModReadme==

"@

# --- merged settings block (drag, snap, move) ------------------------------
function Get-SettingsInner {
    param([string]$Path)
    $lines = Get-Content -LiteralPath $Path
    $inner = New-Object System.Collections.Generic.List[string]
    $inBlock = $false
    foreach ($l in $lines) {
        if ($l.TrimEnd() -eq '// ==WindhawkModSettings==') { $inBlock = $true; continue }
        if ($inBlock -and $l.TrimEnd() -eq '// ==/WindhawkModSettings==') { break }
        if ($inBlock) { $inner.Add($l) }
    }
    # Inner block is "/*" ... "*/"; strip those two lines.
    $body = $inner.ToArray()
    if ($body.Count -lt 2 -or $body[0].Trim() -ne '/*' -or $body[-1].Trim() -ne '*/') {
        throw "unexpected settings block shape in $Path"
    }
    $body[1..($body.Count - 2)]
}
$settingsParts = foreach ($key in $Sources.Keys) { Get-SettingsInner $Sources[$key] }
$settingsBlock = (@('// ==WindhawkModSettings==', '/*') + $settingsParts + @('*/', '// ==/WindhawkModSettings==')) -join "`r`n"

# --- dispatcher ------------------------------------------------------------
$dispatcher = @'

////////////////////////////////////////////////////////////////////////////////
// Shared dispatcher: one set of engine callbacks for the three modules.
//
// Host selection:
//   dwm.exe -tool-mod <id>  -> tool process: both hotkey tools run here.
//   dwm.exe                 -> launcher: spawns the tool process above. The
//                              tool inherits dwm's elevation, which is what
//                              lets the hotkeys move elevated windows.
//   anything else           -> drag module only (it must run inside every
//                              process that owns a draggable window).
//
// The launcher gate on the executable name keeps a single spawner: without
// it, Include=* would spawn a tool from every injected process.

static bool g_packIsTool;
static bool g_packIsLauncher;
static bool g_packDragInited;

static bool PackIsToolProcess(int argc, LPWSTR* argv) {
    for (int i = 1; i < argc - 1; i++) {
        if (wcscmp(argv[i], L"-tool-mod") == 0) {
            return wcscmp(argv[i + 1], WH_MOD_ID) == 0;
        }
    }
    return false;
}

static bool PackIsExcludedProcess(int argc, LPWSTR* argv) {
    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-service") == 0 ||
            wcscmp(argv[i], L"-service-start") == 0 ||
            wcscmp(argv[i], L"-service-stop") == 0) {
            return true;
        }
    }
    return false;
}

static bool PackIsDwmProcess() {
    WCHAR path[MAX_PATH];
    DWORD len = GetModuleFileNameW(nullptr, path, ARRAYSIZE(path));
    if (!len || len >= ARRAYSIZE(path)) {
        return false;
    }
    PCWSTR name = path;
    for (PCWSTR p = path; *p; p++) {
        if (*p == L'\\' || *p == L'/') name = p + 1;
    }
    return _wcsicmp(name, L"dwm.exe") == 0;
}

static void WINAPI PackEntryPointHook() {
    Wh_Log(L">");
    ExitThread(0);
}

// Spawns "<this process>" -tool-mod "<id>", exactly like the stock tool-mod
// pattern: the child is whatever this process is, so spawning from dwm.exe
// yields an elevated tool.
static void PackSpawnTool() {
    WCHAR currentProcessPath[MAX_PATH];
    switch (GetModuleFileName(nullptr, currentProcessPath,
                              ARRAYSIZE(currentProcessPath))) {
        case 0:
        case ARRAYSIZE(currentProcessPath):
            Wh_Log(L"GetModuleFileName failed");
            return;
    }

    WCHAR commandLine[MAX_PATH + 2 +
                      (sizeof(L" -tool-mod \"" WH_MOD_ID "\"") / sizeof(WCHAR)) - 1];
    swprintf_s(commandLine, L"\"%s\" -tool-mod \"%s\"", currentProcessPath,
               WH_MOD_ID);

    HMODULE kernelModule = GetModuleHandle(L"kernelbase.dll");
    if (!kernelModule) {
        kernelModule = GetModuleHandle(L"kernel32.dll");
        if (!kernelModule) {
            Wh_Log(L"No kernelbase.dll/kernel32.dll");
            return;
        }
    }

    using CreateProcessInternalW_t = BOOL(WINAPI*)(
        HANDLE hUserToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
        LPSECURITY_ATTRIBUTES lpProcessAttributes,
        LPSECURITY_ATTRIBUTES lpThreadAttributes, WINBOOL bInheritHandles,
        DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory,
        LPSTARTUPINFOW lpStartupInfo,
        LPPROCESS_INFORMATION lpProcessInformation,
        PHANDLE hRestrictedUserToken);
    CreateProcessInternalW_t pCreateProcessInternalW =
        (CreateProcessInternalW_t)GetProcAddress(kernelModule,
                                                 "CreateProcessInternalW");
    if (!pCreateProcessInternalW) {
        Wh_Log(L"No CreateProcessInternalW");
        return;
    }

    STARTUPINFO si{
        .cb = sizeof(STARTUPINFO),
        .dwFlags = STARTF_FORCEOFFFEEDBACK,
    };
    PROCESS_INFORMATION pi;
    if (!pCreateProcessInternalW(nullptr, currentProcessPath, commandLine,
                                 nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS,
                                 nullptr, nullptr, &si, &pi, nullptr)) {
        Wh_Log(L"CreateProcess failed");
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

BOOL Wh_ModInit() {
    DWORD sessionId;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &sessionId) &&
        sessionId == 0) {
        return FALSE;
    }

    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!argv) {
        Wh_Log(L"CommandLineToArgvW failed");
        return FALSE;
    }

    bool excluded = PackIsExcludedProcess(argc, argv);
    bool ourTool = PackIsToolProcess(argc, argv);
    LocalFree(argv);

    if (excluded) {
        return FALSE;
    }

    if (ourTool) {
        g_packIsTool = true;

        HANDLE mutex = CreateMutex(nullptr, TRUE,
                                   L"windhawk-tool-mod_" WH_MOD_ID);
        if (!mutex) {
            Wh_Log(L"CreateMutex failed");
            ExitProcess(1);
        }
        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            Wh_Log(L"Tool mod already running (%s)", WH_MOD_ID);
            ExitProcess(1);
        }

        if (!snapCommander::ToolModInit()) {
            Wh_Log(L"snapCommander tool init failed");
            ExitProcess(1);
        }
        if (!moveToMonitor::ToolModInit()) {
            Wh_Log(L"moveToMonitor tool init failed");
            ExitProcess(1);
        }

        IMAGE_DOS_HEADER* dosHeader =
            (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders =
            (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);
        void* entryPoint =
            (BYTE*)dosHeader + ntHeaders->OptionalHeader.AddressOfEntryPoint;
        Wh_SetFunctionHook(entryPoint, (void*)PackEntryPointHook, nullptr);
        return TRUE;
    }

    if (PackIsDwmProcess()) {
        // Real dwm.exe: only the launcher runs here. The drag module stays
        // out of the composition process, as it is today (a pattern include
        // never matches critical system processes).
        g_packIsLauncher = true;
        g_packDragInited = altSnapDrag::ModInit();
        return TRUE;
    }

    g_packDragInited = altSnapDrag::ModInit();
    return g_packDragInited ? TRUE : FALSE;
}

void Wh_ModAfterInit() {
    if (g_packIsLauncher) {
        PackSpawnTool();
    }
}

void Wh_ModSettingsChanged() {
    if (g_packIsTool) {
        snapCommander::ToolModSettingsChanged();
        moveToMonitor::ToolModSettingsChanged();
        return;
    }
    if (g_packDragInited) {
        altSnapDrag::ModSettingsChanged();
    }
}

void Wh_ModUninit() {
    if (g_packIsTool) {
        snapCommander::ToolModUninit();
        moveToMonitor::ToolModUninit();
        ExitProcess(0);
    }
    if (g_packDragInited) {
        altSnapDrag::ModUninit();
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    return altSnapDrag::DragDllMain(hinstDLL, fdwReason, lpReserved);
}
'@

# --- assemble --------------------------------------------------------------
$sb = New-Object System.Text.StringBuilder
[void]$sb.AppendLine($header)
[void]$sb.AppendLine('// Merged from the installed sources:')
foreach ($key in $Sources.Keys) {
    [void]$sb.AppendLine(("//   {0} <- {1}" -f $Sources[$key], $key))
}
[void]$sb.AppendLine()
foreach ($inc in $allIncludes) {
    [void]$sb.AppendLine($inc)
}
[void]$sb.AppendLine()

foreach ($key in $Sources.Keys) {
    [void]$sb.AppendLine(('//////// {0} ////////' -f $key))
    [void]$sb.AppendLine(('namespace {0} {{' -f $Namespaces[$key]))
    foreach ($line in $parts[$key].Body) {
        [void]$sb.AppendLine($line)
    }
    [void]$sb.AppendLine('}  // namespace ' + $Namespaces[$key])
    [void]$sb.AppendLine()
}

[void]$sb.AppendLine($settingsBlock)
[void]$sb.AppendLine()
$dispatcher = $dispatcher.Replace('dwm.exe', 'windhawk.exe').Replace('PackIsDwmProcess', 'PackIsWindhawkProcess')
$dispatcher = $dispatcher.Replace('bool ourTool = PackIsToolProcess(argc, argv);', @'
bool ourTool = PackIsToolProcess(argc, argv);
    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-tool-mod") == 0 && !ourTool) excluded = true;
    }
'@)
$start = $dispatcher.IndexOf('    HMODULE kernelModule = GetModuleHandle', $dispatcher.IndexOf('static void PackSpawnTool'))
$end = $dispatcher.IndexOf("`n}", $start)
$dispatcher = $dispatcher.Substring(0, $start) + @'
    SHELLEXECUTEINFOW sei{sizeof(sei)};
    sei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI;
    sei.lpVerb = L"runas";
    sei.lpFile = currentProcessPath;
    sei.lpParameters = L"-tool-mod \"" WH_MOD_ID L"\"";
    sei.nShow = SW_HIDE;
    if (!ShellExecuteExW(&sei)) {
        Wh_Log(L"Elevated tool launch failed: %u", GetLastError());
        return;
    }
    if (sei.hProcess) CloseHandle(sei.hProcess);
'@ + $dispatcher.Substring($end)
[void]$sb.AppendLine($dispatcher)

$outDir = Split-Path -Parent $OutFile
if (-not (Test-Path -LiteralPath $outDir)) {
    New-Item -ItemType Directory -Path $outDir -Force | Out-Null
}
[System.IO.File]::WriteAllText($OutFile, $sb.ToString(), [System.Text.UTF8Encoding]::new($false))
$hash = (Get-FileHash -LiteralPath $OutFile -Algorithm SHA256).Hash
Write-Log "wrote $OutFile ($((Get-Content -LiteralPath $OutFile).Count) lines, sha256=$hash)"
Write-Log 'GENERATE OK'
exit 0
