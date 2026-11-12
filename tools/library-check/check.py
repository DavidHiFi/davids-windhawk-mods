"""Check every mod in mods/local against the rules of the official Windhawk
mod library (ramensoftware/windhawk-mods): its validator and its compile test.

  check.py validate --upstream <windhawk-mods checkout> [--only "a b"]
  check.py compile  --upstream <windhawk-mods checkout> --windhawk <portable dir>

Prints one RESULT line of JSON per mod and writes a table to the job summary.
It reports; it never fails the job.
"""
import argparse
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

AUTHOR = 'DavidHiFi'
AUTHOR_ID = '106938608'
ROOT = Path(__file__).resolve().parents[2]


def mods(only):
    for path in sorted((ROOT / 'mods' / 'local').glob('*/*.wh.cpp')):
        text = path.read_text(encoding='utf-8', errors='replace')
        match = re.search(r'^//\s*@id\s+(\S+)', text, re.M)
        mod_id = (match.group(1) if match else path.name[:-7]).removeprefix('local@')
        if only and mod_id not in only and path.parent.name not in only:
            continue
        yield mod_id, path


def stage(work, mod_id, path):
    target = work / 'mods' / f'{mod_id}.wh.cpp'
    target.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(path, target)
    return target


def run(cmd, cwd, timeout=1500):
    try:
        env = {**os.environ, 'PYTHONUTF8': '1'}
        done = subprocess.run(cmd, cwd=cwd, capture_output=True, timeout=timeout, env=env)
    except subprocess.TimeoutExpired:
        return -1, '', f'timed out after {timeout} s'
    out = done.stdout.decode('utf-8', 'replace')
    err = done.stderr.decode('utf-8', 'replace')
    return done.returncode, out, err


def validate(args, work):
    script = Path(args.upstream).resolve() / '.github' / 'pr_validation.py'
    for mod_id, path in mods(args.only):
        staged = stage(work, mod_id, path)
        code, out, err = run(
            [sys.executable, str(script), f'mods/{staged.name}', AUTHOR, AUTHOR_ID],
            work,
            600,
        )
        problems = []
        for line in out.splitlines():
            match = re.match(r'::(?:warning|error) file=[^,]*,line=(\d+)[^:]*::(.*)', line)
            if match:
                text = match.group(2).replace('%0A', ' ').replace('%25', '%')
                problems.append(f'L{match.group(1)}: {text[:300]}')
        if code != 0 and not problems:
            problems.append((err or out).strip()[-600:])
        yield {'id': mod_id, 'ok': not problems, 'problems': problems}


def diagnostics(text):
    lines = [l for l in text.splitlines() if re.search(r'\b(error|warning)\b', l)]
    return [l.strip()[:300] for l in lines[:12]]


def compile_mods(args, work):
    windhawk = Path(args.windhawk).resolve()
    cli = windhawk / 'windhawk-cli.exe'
    legacy = Path(args.upstream).resolve() / 'scripts' / 'compile_mod.py'
    for mod_id, path in mods(args.only):
        staged = stage(work, mod_id, path)
        if cli.exists():
            code, out, err = run(
                [str(cli), '--json', 'mod', 'install', '--disabled', '--arch', 'all',
                 '--strict', '--file', str(staged)],
                work,
            )
            problems = diagnostics(err)
            try:
                data = json.loads(out)
            except ValueError:
                data = {}
            warned = bool((data.get('data') or {}).get('warnings'))
            if code != 0:
                error = data.get('error') or {}
                message = str(error.get('message', '')) or err.strip()[-300:]
                problems.insert(0, f"{error.get('code', code)}: {message[:400]}")
            elif warned:
                problems.insert(0, 'compiled with warnings')
            ok = code == 0 and not warned
        else:
            outputs = [str(work / f'mod_{a}.dll') for a in ('32', '64', 'arm64')]
            code, out, err = run(
                [sys.executable, str(legacy), '-w', str(windhawk), '-f', str(staged),
                 '-o32', outputs[0], '-o64', outputs[1], '-oarm64', outputs[2]],
                work,
            )
            ok = code == 0
            problems = []
            if not ok:
                problems = diagnostics(out + '\n' + err) or [(err or out).strip()[-600:]]
        yield {'id': mod_id, 'ok': ok, 'problems': problems}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('mode', choices=['validate', 'compile'])
    parser.add_argument('--upstream', required=True)
    parser.add_argument('--windhawk')
    parser.add_argument('--label', default='')
    parser.add_argument('--only', default='')
    args = parser.parse_args()
    args.only = {x for x in re.split(r'[\s,]+', args.only) if x}

    work = Path(os.environ.get('RUNNER_TEMP', '.')) / 'library-check'
    work.mkdir(parents=True, exist_ok=True)
    if args.mode == 'validate':
        results = validate(args, work)
    else:
        results = compile_mods(args, work)

    label = args.label or args.mode
    rows = [f'### {label}', '', '| Mod | Result | First problem |', '| --- | --- | --- |']
    for result in results:
        print('RESULT ' + json.dumps({'check': label, **result}), flush=True)
        first = ''
        if result['problems']:
            first = result['problems'][0].replace('|', '\\|')[:200]
        rows.append(f"| {result['id']} | {'pass' if result['ok'] else 'FAIL'} | {first} |")
    summary = os.environ.get('GITHUB_STEP_SUMMARY')
    if summary:
        with open(summary, 'a', encoding='utf-8') as handle:
            handle.write('\n'.join(rows) + '\n\n')


if __name__ == '__main__':
    main()
