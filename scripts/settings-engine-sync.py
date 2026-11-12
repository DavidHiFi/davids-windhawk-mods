"""Brings a generator-built mod's settings window up to the current Seamless Launchpad engine.

The generator mods (Color Picker, Media Player, Crash Watch, Key Click) each keep a word-for-word
copy of Launchpad's settings section as src/settings-template.cpp and swap names with gen.py. When
Launchpad's engine moves on (hover states, footer blur, box edges), those copies go stale. This
tool refreshes the copy, reruns the mod's own gen.py in a sandbox, and splices the new settings
block into the INSTALLED source, so the rest of the mod stays exactly as the live build has it.

  python settings-engine-sync.py template <launchpad.wh.cpp> <out.cpp>
      Cuts the settings section out of a Launchpad source (live or staged).
  python settings-engine-sync.py build <id> <gendir> <launchpad.wh.cpp> <outdir>
      Writes <outdir>/<id>.wh.cpp (version bumped) and prints the live hash it was built from.
      The generator folder itself is never written; the sandbox is <outdir>/<gen folder name>.
  python settings-engine-sync.py adopt <gendir> <launchpad.wh.cpp>
      Copies the fresh template into the generator folder (backup beside it), so later rebuilds
      keep the new engine. Only for folders this thread may write.
"""
import hashlib
import pathlib
import re
import shutil
import subprocess
import sys
import time

MODS = pathlib.Path(r'C:\ProgramData\Windhawk\ModsSource')
START = '// The settings window, from the "..." menu.'
END = 'void CloseSettingsWindow() {'


def read(p):
    return pathlib.Path(p).read_text(encoding='utf-8').replace('\r\n', '\n')


def template(lp_path):
    s = read(lp_path)
    a = s.index(START)
    b = s.index('\n}\n', s.index(END)) + 3
    return s[a:b]


def splice(live, block):
    """Swaps the generated settings block in a live source for a new one."""
    head = '// ===========================================================================\n// Settings window: the Seamless Launchpad settings GUI'
    a = live.index(head)
    ns = re.search(r'^namespace (\w+) \{', block, re.M).group(1)
    close = f'\n}}  // namespace {ns}\n'
    b = live.index(close, a) + len(close)
    nb = block.rstrip('\n') + '\n'
    return live[:a] + nb + live[b:]


def bump(text):
    m = re.search(r'(//\s*@version\s+)(\d+)\.(\d+)\.(\d+)', text)
    new = f'{m.group(2)}.{m.group(3)}.{int(m.group(4)) + 1}'
    return text[:m.start()] + m.group(1) + new + text[m.end():], new


def build(mod_id, gendir, lp_path, outdir):
    gendir, outdir = pathlib.Path(gendir), pathlib.Path(outdir)
    live_path = MODS / f'{mod_id}.wh.cpp'
    live_bytes = live_path.read_bytes()
    live_hash = hashlib.sha256(live_bytes).hexdigest().upper()
    sand = outdir / gendir.name
    if sand.exists():
        shutil.rmtree(sand)
    sand.mkdir(parents=True)
    for p in gendir.iterdir():
        if p.is_file() and p.suffix in ('.py',):
            shutil.copy2(p, sand / p.name)
    shutil.copytree(gendir / 'src', sand / 'src', ignore=shutil.ignore_patterns('*.bak-*'))
    (sand / 'src' / 'settings-template.cpp').write_text(template(lp_path), encoding='utf-8', newline='\n')
    r = subprocess.run([sys.executable, 'gen.py'], cwd=sand, capture_output=True, text=True,
                       creationflags=0x08000000)
    if r.returncode:
        sys.exit(f'{mod_id}: gen.py failed\n{r.stdout}{r.stderr}')
    block = read(sand / 'src' / 'settings-block.cpp')
    text, ver = bump(splice(live_bytes.decode('utf-8').replace('\r\n', '\n'), block))
    out = outdir / f'{mod_id}.wh.cpp'
    out.write_bytes(text.encode('utf-8'))
    print(f'{mod_id}: v{ver} staged at {out}')
    print(f'{mod_id}: gen said {r.stdout.strip()[:120]}')
    print(f'BASEHASH {live_hash}')


def adopt(gendir, lp_path):
    t = pathlib.Path(gendir) / 'src' / 'settings-template.cpp'
    stamp = time.strftime('%Y%m%d-%H%M')
    shutil.copy2(t, t.with_name(f'{t.name}.bak-{stamp}'))
    t.write_text(template(lp_path), encoding='utf-8', newline='\n')
    print(f'{t}: refreshed, backup .bak-{stamp}')


if __name__ == '__main__':
    cmd = sys.argv[1]
    if cmd == 'template':
        pathlib.Path(sys.argv[3]).write_text(template(sys.argv[2]), encoding='utf-8', newline='\n')
    elif cmd == 'build':
        build(*sys.argv[2:6])
    elif cmd == 'adopt':
        adopt(*sys.argv[2:4])
    else:
        sys.exit(__doc__)
