import json
import pathlib
import subprocess

root = pathlib.Path(r'H:\Windhawk Configuration')
cli = r'C:\Program Files\Windhawk\windhawk-cli.exe'
listed = json.loads(subprocess.check_output([cli, '--json', 'mod', 'list'], text=True, encoding='utf-8'))
rows = []
for mod in listed['data']['mods']:
    result = subprocess.run([cli, '--json', 'mod', 'show', mod['id']], capture_output=True, text=True, encoding='utf-8', timeout=15)
    try:
        data = json.loads(result.stdout)
    except json.JSONDecodeError:
        data = {'success': False, 'error': {'message': result.stderr or result.stdout}}
    config = mod['config']
    dll = config.get('libraryFileName', '')
    rows.append({'id': mod['id'], 'enabled': mod['enabled'], 'version': mod['version'],
                 'parses': bool(data.get('success')),
                 'error': data.get('error'),
                 'hasLibrary': any((pathlib.Path(r'C:\ProgramData\Windhawk\Engine\Mods') / arch / dll).is_file() for arch in ['64', '32'])})
report = {'mods': rows, 'count': len(rows), 'enabled': sum(row['enabled'] for row in rows),
          'parseFailures': [row['id'] for row in rows if not row['parses']],
          'enabledMissingLibraries': [row['id'] for row in rows if row['enabled'] and not row['hasLibrary']]}
(root / 'reports/2026-10-09-styler-audit/mod-inventory.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
print(json.dumps({key: value for key, value in report.items() if key != 'mods'}))
