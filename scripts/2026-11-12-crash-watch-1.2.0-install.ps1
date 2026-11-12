# Installs Seamless Crash Watch 1.2.0 (no hover glow, History page) via the shared staged installer. Run elevated.
& 'H:\Windhawk Configuration\scripts\Install-StagedMod.ps1' -Id 'local@seamless-crash-watch' -Staged 'C:\Users\Public\seamless-crash-watch-1.2.0.wh.cpp' -BaseHash 'ED1E67614D326BDAD0A1135B2F993A31672DE2CA5338B82F9D33F926E6BDC839' *> 'H:\Windhawk Configuration\work\2026-11-11-crash-toast\build\install-1.2.0.log'
& 'H:\Windhawk Configuration\scripts\2026-11-12-crash-watch-restart.ps1' *>> 'H:\Windhawk Configuration\work\2026-11-11-crash-toast\build\install-1.2.0.log'

