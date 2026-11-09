"""Install Notification Center Styler Plus 1.8.4: keeps the group "..." menu above the panel
window, and lets the menu grow wide enough for its longest line. Rollback: ... rollback"""
import json, re, shutil, subprocess, sys, time, winreg
from pathlib import Path

root = Path(r'H:\Windhawk Configuration')
backup = root / 'backups/2026-11-10/nc-menu-above'
key_path = r'SOFTWARE\Windhawk\Engine\Mods\local@notification-center-styler-plus'
data = Path(r'C:\ProgramData\Windhawk')
new_library = 'local@notification-center-styler-plus_1.8.4_1.dll'
source = data / 'ModsSource/local@notification-center-styler-plus.wh.cpp'
menu_target = 'MenuFlyoutPresenter'


def run(*args):
    r = subprocess.run(args, capture_output=True, timeout=60, creationflags=subprocess.CREATE_NO_WINDOW)
    if r.returncode:
        raise RuntimeError(r.stdout.decode(errors='replace') + r.stderr.decode(errors='replace'))
    return r.stdout.decode(errors='replace')


def state():
    with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, key_path) as k:
        return {n: winreg.QueryValueEx(k, n)[0] for n in ('Disabled', 'Version', 'LibraryFileName')}


def settings():
    out = {}
    with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, key_path + chr(92) + 'Settings') as k:
        i = 0
        while True:
            try:
                n, v, _ = winreg.EnumValue(k, i)
            except OSError:
                return out
            out[n] = v; i += 1


def write(values, sub=''):
    with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, key_path + sub, 0, winreg.KEY_SET_VALUE) as k:
        for n, kind, v in values:
            winreg.SetValueEx(k, n, 0, kind, v)


def touch():
    write([('SettingsChangeTime', winreg.REG_DWORD, int(time.time()))])


if sys.argv[1] == 'install':
    old = state()
    assert old['Disabled'] == 0 and old['Version'] == '1.8.3', old
    backup.mkdir(parents=True, exist_ok=False)
    run('reg.exe', 'export', 'HKLM' + chr(92) + key_path, str(backup / 'before.reg'), '/y')
    shutil.copy2(source, backup / source.name)
    s = settings()
    idx = [int(m.group(1)) for n in s for m in [re.match(r'controlStyles\[(\d+)\]\.target$', n)] if m]
    existing = [i for i in idx if s[f'controlStyles[{i}].target'] == menu_target]
    rule = existing[0] if existing else max(idx) + 1
    (backup / 'receipt.json').write_text(json.dumps({'old': old, 'new_library': new_library, 'menu_rule': rule}, indent=2))
    shutil.copy2(root / 'work/nc-hover-plus/notification-center-styler-plus.dll', data / 'Engine/Mods/64' / new_library)
    shutil.copy2(root / 'work/nc-hover-plus/notification-center-styler-plus.wh.cpp', source)
    write([(f'controlStyles[{rule}].target', winreg.REG_SZ, menu_target),
           (f'controlStyles[{rule}].styles[0]', winreg.REG_SZ, 'MaxWidth=640')], chr(92) + 'Settings')
    write([('Version', winreg.REG_SZ, '1.8.4'), ('LibraryFileName', winreg.REG_SZ, new_library)])
    touch()
    print('menu rule', rule)
elif sys.argv[1] == 'rollback':
    shutil.copy2(backup / source.name, source)
    rule = json.loads((backup / 'receipt.json').read_text())['menu_rule']
    with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, key_path + chr(92) + 'Settings', 0, winreg.KEY_SET_VALUE) as k:
        for n in (f'controlStyles[{rule}].target', f'controlStyles[{rule}].styles[0]'):
            try: winreg.DeleteValue(k, n)
            except OSError: pass
    run('reg.exe', 'import', str(backup / 'before.reg'))
    touch()
print(state())
