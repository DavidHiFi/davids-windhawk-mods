import argparse, hashlib, json, os, shutil, subprocess
from pathlib import Path

SC = Path(r'H:\System Configuration')
WH = Path(r'H:\Windhawk Configuration')
REPORT = WH / 'reports/2026-10-13-workspace-sweep'
COOP = r'H:\Claude\tools\AgentCoop\coop.py'
IDENTITY = 'd6c3e4f4-bf26-4700-8aa5-54c55d22e840'
REPARSE = 0x400

TO_WINDHAWK = [
    'backups/2026-10-05/weather-fit',
    'backups/2026-10-05/weather-single-process',
    'reports/2026-10-05/weather-fit',
    'reports/2026-10-05/weather-single-process',
    'notes/2026-10-11-taskbar-ai-quota-6-accounts.md',
    'notes/2026-10-11-translucent-windows-blur-fix.md',
    'notes/2026-10-12-styler-2043-closeout.md',
    'scripts/Get-TaskbarCrop.ps1',
    'scripts/Get-TaskbarStrip.ps1',
    'scripts/2026-10-12-styler-cdp-repull.ps1',
    'scripts/2026-10-12-styler-cdp-repull2.ps1',
]

TO_SYSTEM = [
    ('reports/2026-10-12-winlaunch-enhanced-completion.md', 'notes/2026-10-12-winlaunch-enhanced-completion.md'),
    ('reports/release-notes-v2.0.0.md', 'reports/2026-10-12-winlaunch-enhanced-release-notes-v2.0.0.md'),
    ('reports/find-winlaunch-windows.ps1', 'scripts/2026-10-12-find-winlaunch-windows.ps1'),
]


def is_reparse(p):
    return bool(os.stat(p, follow_symlinks=False).st_file_attributes & REPARSE)


def digest(path):
    h = hashlib.sha256()
    with path.open('rb') as f:
        for chunk in iter(lambda: f.read(1024 * 1024), b''):
            h.update(chunk)
    return h.hexdigest()


def tree_hashes(p):
    if p.is_dir():
        return {f.relative_to(p).as_posix(): digest(f) for f in p.rglob('*') if f.is_file()}
    return {'': digest(p)}


def coop(root, command, value, reason):
    r = subprocess.run(['python', COOP, '-C', str(root), command, value, '--as', IDENTITY, '--reason', reason],
                       capture_output=True, text=True)
    return r.returncode == 0, (r.stdout + r.stderr).strip()


def build_plan():
    rows = []
    for rel in TO_WINDHAWK:
        src, dst = SC / rel, WH / rel
        problem = None
        if not src.exists():
            problem = 'source missing'
        elif is_reparse(src):
            problem = 'source is already a link'
        elif dst.exists():
            problem = 'destination exists'
        rows.append(dict(direction='system->windhawk', rel=rel, source=str(src), destination=str(dst),
                         directory=src.is_dir(), problem=problem))
    for src_rel, dst_rel in TO_SYSTEM:
        src, dst = WH / src_rel, SC / dst_rel
        problem = None
        if not src.exists():
            problem = 'source missing'
        elif dst.exists():
            problem = 'destination exists'
        rows.append(dict(direction='windhawk->system', rel=src_rel, source=str(src), destination=str(dst),
                         directory=False, problem=problem))
    return rows


def move_to_windhawk(row):
    src, dst, rel = Path(row['source']), Path(row['destination']), row['rel']
    suffix = '/**' if row['directory'] else ''
    ok, msg = coop(SC, 'claim', rel + suffix, 'Relocate Windhawk record to its workspace')
    if not ok:
        return dict(row, verified=False, error='claim blocked in System Configuration: ' + msg)
    ok, msg = coop(WH, 'claim', rel + suffix, 'Receive Windhawk record')
    if not ok:
        return dict(row, verified=False, error='claim blocked in Windhawk Configuration: ' + msg)
    hashes = tree_hashes(src)
    dst.parent.mkdir(parents=True, exist_ok=True)
    src.rename(dst)
    if row['directory']:
        r = subprocess.run(['cmd', '/c', 'mklink', '/J', str(src), str(dst)], capture_output=True, text=True)
        if r.returncode:
            dst.rename(src)
            return dict(row, verified=False, error='junction failed: ' + r.stderr.strip())
        compat = 'junction'
    else:
        os.link(dst, src)
        compat = 'hardlink'
    for name, expected in hashes.items():
        target = dst / name if name else dst
        assert digest(target) == expected, name
        link = src / name if name else src
        assert link.exists(), name
        if not row['directory']:
            assert os.path.samefile(link, target)
    return dict(row, files=len(hashes), sha256=hashes, compatibility=compat, verified=True)


def move_to_system(row):
    src, dst, rel = Path(row['source']), Path(row['destination']), row['rel']
    ok, msg = coop(WH, 'claim', rel, 'Relocate WinLaunch record out of Windhawk')
    if not ok:
        return dict(row, verified=False, error='claim blocked in Windhawk Configuration: ' + msg)
    ok, msg = coop(SC, 'claim', dst.relative_to(SC).as_posix(), 'Receive WinLaunch record')
    if not ok:
        return dict(row, verified=False, error='claim blocked in System Configuration: ' + msg)
    expected = digest(src)
    dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.move(str(src), str(dst))
    assert digest(dst) == expected
    return dict(row, files=1, sha256={'': expected}, compatibility='none', verified=True)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--install', action='store_true')
    args = ap.parse_args()
    REPORT.mkdir(parents=True, exist_ok=True)
    plan = build_plan()
    (REPORT / 'plan.json').write_text(json.dumps(plan, indent=2), encoding='utf-8')
    print(json.dumps(plan, indent=2))
    if not args.install:
        return
    receipt = []
    for row in plan:
        if row['problem']:
            receipt.append(dict(row, verified=False, error=row['problem']))
            print('SKIP', row['rel'], row['problem'], flush=True)
            continue
        result = move_to_windhawk(row) if row['direction'] == 'system->windhawk' else move_to_system(row)
        receipt.append(result)
        (REPORT / 'receipt.json').write_text(json.dumps(receipt, indent=2), encoding='utf-8')
        print(('MOVED ' if result.get('verified') else 'FAILED ') + row['rel'], result.get('compatibility', result.get('error')), flush=True)
    print(f"Done: {sum(1 for r in receipt if r.get('verified'))} verified of {len(receipt)}")


if __name__ == '__main__':
    main()
