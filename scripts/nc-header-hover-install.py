"""Install Notification Center Styler Plus 1.8.3 (header "..." / X hover from the button's pointer)
and its rest-only header edge rules. Rollback: python nc-header-hover-install.py rollback"""
import json, shutil, subprocess, sys, time, winreg
from pathlib import Path

root = Path(r'H:\Windhawk Configuration')
backup = root / 'backups/2026-11-09/nc-header-hover'
key_path = r'SOFTWARE\Windhawk\Engine\Mods\local@notification-center-styler-plus'
data = Path(r'C:\ProgramData\Windhawk')
new_library = 'local@notification-center-styler-plus_1.8.3_1.dll'
source = data / 'ModsSource/local@notification-center-styler-plus.wh.cpp'


def run(*args):
    r = subprocess.run(args, capture_output=True, timeout=60, creationflags=subprocess.CREATE_NO_WINDOW)
    if r.returncode:
        raise RuntimeError(r.stdout.decode(errors='replace') + r.stderr.decode(errors='replace'))
    return r.stdout.decode(errors='replace')


def state():
    with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, key_path) as k:
        return {n: winreg.QueryValueEx(k, n)[0] for n in ('Disabled', 'Version', 'LibraryFileName')}


def write(values):
    with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, key_path, 0, winreg.KEY_SET_VALUE) as k:
        for n, kind, v in values + [('SettingsChangeTime', winreg.REG_DWORD, int(time.time()))]:
            winreg.SetValueEx(k, n, 0, kind, v)


if sys.argv[1] == 'install':
    old = state()
    assert old['Disabled'] == 0 and old['Version'] == '1.8.2', old
    backup.mkdir(parents=True, exist_ok=False)
    run('reg.exe', 'export', r'HKLM' + chr(92) + key_path, str(backup / 'before.reg'), '/y')
    shutil.copy2(source, backup / source.name)
    (backup / 'receipt.json').write_text(json.dumps({'old': old, 'new_library': new_library}, indent=2))
    shutil.copy2(root / 'work/nc-hover-plus/notification-center-styler-plus.dll', data / 'Engine/Mods/64' / new_library)
    shutil.copy2(root / 'work/nc-hover-plus/notification-center-styler-plus.wh.cpp', source)
    print(run('powershell.exe', '-NoProfile', '-ExecutionPolicy', 'Bypass', '-File', str(root / 'scripts/nc-panel.ps1'),
              '-Install', '-Only', '101,102,132,133,134,135'))
    write([('Version', winreg.REG_SZ, '1.8.3'), ('LibraryFileName', winreg.REG_SZ, new_library)])
elif sys.argv[1] == 'rollback':
    shutil.copy2(backup / source.name, source)
    run('reg.exe', 'import', str(backup / 'before.reg'))
    write([])
print(state())
