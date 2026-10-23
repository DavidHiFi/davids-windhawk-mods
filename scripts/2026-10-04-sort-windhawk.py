import argparse, hashlib, json, os, re, subprocess
from pathlib import Path

SOURCE = Path(r'H:\System Configuration')
DEST = Path(r'H:\Windhawk Configuration')
REPORT = DEST / 'reports/2026-10-04-workspace-sort'
IDENTITY = 'windhawk-sort-20261004'
COOP = r'H:\Claude\tools\AgentCoop\coop.py'
pattern = re.compile(r'windhawk|windhog|taskbar|weather|system-info|altsnap|font-changer|window-pack|memory-align|npp-taskdlg|visualizer|tourne|nanazip.*(?:trail|marquee)|regedit-marquee|win32-ui-modernizer|translucent-windows|^npp-(?:dialog|save-dialog)|^tb\d?[-.]', re.I)
work_names = {'davids-audio-publish','font-changer','memory-align','taskbar-weather','taskbar-weather-publish','taskbar-widget-fit','weather-catalog','weather-crisp-repo','weather-smooth-repo','weather-stack-repo','windhawk-system-info','window-pack-catalog','window-pack-publish','visualizer-publish-20261003'}

def digest(path):
    h = hashlib.sha256()
    with path.open('rb') as f:
        for chunk in iter(lambda: f.read(1024*1024), b''):
            h.update(chunk)
    return h.hexdigest()

def candidates():
    found = []
    receipt_path = REPORT/'receipt.json'
    completed = {row['source'] for row in json.loads(receipt_path.read_text(encoding='utf-8'))} if receipt_path.exists() else set()
    for section in ['notes','scripts','reports','backups','themes','patches','packages','.tmp','work']:
        base = SOURCE / section
        if not base.exists():
            continue
        for root, dirs, files in os.walk(base, followlinks=False):
            dirs[:] = [d for d in dirs if d not in {'.git','node_modules','vendor','__pycache__'} and not (Path(root)/d).is_junction()]
            for name in list(dirs):
                p = Path(root)/name
                if str(p) in completed:
                    continue
                if 'steam' in name.lower():
                    dirs.remove(name)
                    continue
                if (section == 'work' and name in work_names) or (section != 'work' and pattern.search(name)) or (section == '.tmp' and name in {'altsnap-src','taskbar-pill4','nanazip-marquee','regedit-marquee'}):
                    found.append(p)
                    dirs.remove(name)
                elif section != 'scripts' and not re.fullmatch(r'\d{4}-\d{2}-\d{2}', name):
                    dirs.remove(name)
                elif section == 'scripts' and name not in {'state'} and not re.fullmatch(r'\d{4}-\d{2}-\d{2}', name):
                    dirs.remove(name)
            if section == 'work':
                dirs[:] = []
            for name in files:
                p = Path(root)/name
                if str(p) in completed:
                    continue
                if 'steam' in name.lower():
                    continue
                if name == '2026-09-24-organize-e-drive.ps1':
                    continue
                target = DEST / p.relative_to(SOURCE)
                if target.exists() and os.path.samefile(p, target):
                    continue
                if pattern.search(name) or name in {'Set-TaskbarGiantPill.ps1','Test-NanaZipMarquee.py','Test-RegeditMarquee.py'}:
                    found.append(p)
                elif section == 'scripts' and p.suffix.lower() in {'.ps1','.py','.cmd'} and p.stat().st_size < 300000:
                    text = p.read_text(encoding='utf-8', errors='replace')
                    if re.search(r'Wh_Mod|SOFTWARE\\Windhawk|ProgramData\\Windhawk', text, re.I):
                        found.append(p)
    return sorted(set(found))

def coop(root, command, value, reason):
    args = ['python', COOP, '-C', str(root), command, value, '--as', IDENTITY, '--reason', reason]
    subprocess.run(args, check=True, capture_output=True, text=True)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--install', action='store_true')
    args = parser.parse_args()
    REPORT.mkdir(parents=True, exist_ok=True)
    paths = candidates()
    plan = [{'source':str(p), 'destination':str(DEST/p.relative_to(SOURCE)), 'directory':p.is_dir()} for p in paths]
    (REPORT/'remaining-plan.json').write_text(json.dumps(plan, indent=2), encoding='utf-8')
    if not args.install:
        print(json.dumps(plan, indent=2))
        return
    receipt_path = REPORT/'receipt.json'
    receipt = json.loads(receipt_path.read_text(encoding='utf-8')) if receipt_path.exists() else []
    for row in plan:
        src, dst = Path(row['source']), Path(row['destination'])
        rel = src.relative_to(SOURCE).as_posix()
        coop(SOURCE, 'claim', rel + ('/**' if src.is_dir() else ''), 'Move Windhawk records to their workspace')
        coop(DEST, 'claim', rel + ('/**' if src.is_dir() else ''), 'Receive Windhawk records')
        if dst.exists():
            dst = DEST/'archive/system-configuration-2026-10-04'/src.relative_to(SOURCE)
            coop(DEST, 'claim', dst.relative_to(DEST).as_posix() + ('/**' if src.is_dir() else ''), 'Preserve colliding historical record')
        if dst.exists():
            raise RuntimeError(f'Destination already exists: {dst}')
        dst.parent.mkdir(parents=True, exist_ok=True)
        # Resolve and constrain both targets before moving a directory.
        assert src.resolve().is_relative_to(SOURCE.resolve())
        assert dst.resolve().is_relative_to(DEST.resolve())
        hashes = {str(p.relative_to(src)):digest(p) for p in src.rglob('*') if p.is_file() and not p.is_symlink()} if src.is_dir() else {'':digest(src)}
        src.rename(dst)
        if row['directory']:
            result = subprocess.run(['cmd','/c','mklink','/J',str(src),str(dst)], capture_output=True, text=True)
            if result.returncode:
                dst.rename(src)
                raise RuntimeError(result.stderr)
        else:
            os.link(dst, src)
        for name, expected in hashes.items():
            assert digest(dst/name if name else dst) == expected
            assert os.path.samefile(dst/name if name else dst, src/name if name else src)
        row.update(destination=str(dst), files=len(hashes), sha256=hashes, compatibility='junction' if row['directory'] else 'hardlink', verified=True)
        receipt.append(row)
        (REPORT/'receipt.json').write_text(json.dumps(receipt, indent=2), encoding='utf-8')
        print(f'Moved {rel}: {len(hashes)} files', flush=True)
    print(f'Completed: {len(receipt)} items, {sum(r["files"] for r in receipt)} files')

if __name__ == '__main__':
    main()
