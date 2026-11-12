"""Stages Launchpad with the see-through footer, rebuilds the four generator mods from it, and
compiles all five offline the way Windhawk does. Writes nothing in ModsSource. Run under heavy.py."""
import hashlib
import pathlib
import subprocess
import sys

HERE = pathlib.Path(__file__).parent
OUT = pathlib.Path(r'C:\Users\Public\engine-sync')
OUT.mkdir(exist_ok=True)
MODS = pathlib.Path(r'C:\ProgramData\Windhawk\ModsSource')
SYNC = r'H:\Windhawk Configuration\scripts\settings-engine-sync.py'
WORK = pathlib.Path(r'H:\Windhawk Configuration\work')
GENS = {
    'local@seamless-color-picker': WORK / '2026-11-10-color-picker',
    'local@seamless-media-player': WORK / '2026-11-10-media-settings',
    'local@seamless-key-click': WORK / '2026-11-11-seamless-key-click',
}
HIDE = 0x08000000
log = []


def say(s):
    print(s)
    log.append(s)


# 1. Launchpad: the footer dock shows the blurred rows through it, like the rail dock.
lp_id = 'local@seamless-launchpad'
raw = (MODS / f'{lp_id}.wh.cpp').read_bytes()
say(f'BASEHASH {lp_id} {hashlib.sha256(raw).hexdigest().upper()}')
s = raw.decode('utf-8').replace('\r\n', '\n')
old = '    p.Round(d, rad, mocha::mantle, w.render ? 1.0f : 0.85f);\n'
new = ('    // The same see-through mantle as the rail dock, so the blurred rows under the pill read as\n'
       '    // real glass instead of a near-solid bar.\n'
       '    p.Round(d, rad, mocha::mantle, w.render ? 1.0f : (w.glass ? 0.58f : 0.85f));\n')
assert s.count(old) == 1, 'footer fill line not found once'
s = s.replace(old, new)
assert s.count('// @version         2.4.6\n') == 1
s = s.replace('// @version         2.4.6\n', '// @version         2.4.7\n')
lp_out = OUT / f'{lp_id}.wh.cpp'
lp_out.write_bytes(s.encode('utf-8'))
say(f'{lp_id}: v2.4.7 staged')

# 2. The generator mods, rebuilt from the staged Launchpad and spliced into their live sources.
for mid, gd in GENS.items():
    r = subprocess.run([sys.executable, SYNC, 'build', mid, str(gd), str(lp_out), str(OUT)],
                       capture_output=True, text=True, creationflags=HIDE)
    for line in (r.stdout + r.stderr).strip().splitlines():
        say(('BASEHASH ' + mid + ' ' + line.split()[1]) if line.startswith('BASEHASH') else line)
    if r.returncode:
        say(f'{mid}: BUILD FAILED')

# 3. Offline compile, x64, as Windhawk does.
inc = 'C:/Program Files/Windhawk/Compiler/include'
for mid in [lp_id, *GENS]:
    src = OUT / f'{mid}.wh.cpp'
    if not src.exists():
        continue
    ver = [l.split()[-1] for l in src.read_text(encoding='utf-8').splitlines()[:20] if '@version' in l][0]
    hdr = OUT / f'{mid}.id.h'
    hdr.write_text(f'#define WH_MOD_ID L"{mid}"\n#define WH_MOD_VERSION L"{ver}"\n')
    args = ['C:/Program Files/Windhawk/Compiler/bin/clang++.exe', '-std=c++23', '-O1', '-target',
            'x86_64-w64-mingw32', '-DUNICODE', '-D_UNICODE', '-DWINVER=0x0A00', '-D_WIN32_WINNT=0x0A00',
            '-DWH_MOD', '-c', '-include', str(hdr), '-include', 'windhawk_api.h', '-I', inc, '-x', 'c++',
            str(src), '-o', str(OUT / f'{mid}.o')]
    r = subprocess.run(args, capture_output=True, text=True, timeout=900, creationflags=HIDE)
    errs = [l for l in (r.stdout + r.stderr).splitlines() if ' error' in l]
    say(f'COMPILE {mid} v{ver}: exit {r.returncode}' + ('' if not errs else '\n  ' + '\n  '.join(errs[:12])))

(HERE / 'stage.log').write_text('\n'.join(log) + '\n', encoding='utf-8')
