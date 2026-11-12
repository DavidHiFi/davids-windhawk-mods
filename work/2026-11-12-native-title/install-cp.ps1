# Compiles and installs the staged Color Picker (native title bar default off), restarts its tool
# process, then turns the switch off in Launchpad and Color Picker. Under heavy.py + engine lock.
param([Parameter(Mandatory)][string]$BaseHash)
$o = "C:\Users\Public\native-title"; $id = 'local@seamless-color-picker'
$elev = "H:\System Configuration\scripts\Invoke-Elevated.ps1"
$cl = Start-Process 'C:\Program Files\Windhawk\Compiler\bin\clang++.exe' -PassThru -Wait -WindowStyle Hidden `
    -RedirectStandardError "$o\$id.err" -ArgumentList ('-std=c++23 -O1 -target x86_64-w64-mingw32 -DUNICODE -D_UNICODE ' +
    "-DWINVER=0x0A00 -D_WIN32_WINNT=0x0A00 -DWH_MOD -c -include `"$o\$id.id.h`" -include windhawk_api.h " +
    "-I `"C:/Program Files/Windhawk/Compiler/include`" -x c++ `"$o\$id.wh.cpp`" -o `"$o\$id.o`"")
"COMPILE exit $($cl.ExitCode)"
if ($cl.ExitCode -ne 0) { exit 1 }
& $elev -File "H:\Windhawk Configuration\scripts\Install-StagedMod.ps1" -ArgumentList "-Id $id -Staged `"$o\$id.wh.cpp`" -BaseHash $BaseHash"
"$id registry v" + (Get-ItemProperty "HKLM:\SOFTWARE\Windhawk\Engine\Mods\$id").Version
& $elev -File "H:\Windhawk Configuration\scripts\2026-11-10-tool-mod-restart.ps1" -ArgumentList "-Id $id"
& $elev -File "H:\Windhawk Configuration\work\2026-11-12-native-title\native-off.ps1"
