"""Check every mod in mods/local against the rules of the official Windhawk
mod library (ramensoftware/windhawk-mods): its validator and its compile test.

  check.py validate --upstream <windhawk-mods checkout> [--only "a b"]
  check.py compile  --upstream <windhawk-mods checkout> --windhawk <portable dir> [--gate]

Prints one RESULT line of JSON per mod and writes a table to the job summary.

Each mod gets one of three results:
  pass  ready to submit to the official library.
  warn  works, but not ready to submit: a library-only rule (the author and
        github lines our forks keep on purpose, lengths, preview links), a
        compile warning, an ARM64-only error, or a failure on an older Windhawk
        than the one the Workshop ships on.
  FAIL  a real fault: on the Windhawk the Workshop ships on (--gate) the mod
        does not compile for x86 or x64 or its settings do not parse, or a
        check could not run at all.
The job fails only on FAIL.
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
            # The validator itself broke on this file, so nothing was checked.
            yield {'id': mod_id, 'result': 'FAIL', 'problems': [(err or out).strip()[-600:]]}
            continue
        # Every validator finding is a submission rule: the mod works, it is
        # just not ready for the official library yet.
        yield {'id': mod_id, 'result': 'warn' if problems else 'pass', 'problems': problems}


def diagnostics(text):
    lines = [l for l in text.splitlines() if re.search(r'\b(error|warning)\b', l)]
    return [l.strip()[:300] for l in lines[:12]]


def only_arm64(problems):
    """True when every compiler error line comes from the ARM64 build."""
    errors = [p for p in problems
              if re.search(r'\berror\b', p) and not p.startswith('COMPILE_FAILED')]
    return bool(errors) and all(p.startswith('[compile:ARM64]') for p in errors)


def grade(args, ok, warned, problems):
    if ok:
        return 'warn' if warned else 'pass'
    if not args.gate:
        problems.insert(0, 'fails on this older Windhawk; the Workshop ships on 2.0')
        return 'warn'
    if only_arm64(problems):
        problems.insert(0, 'ARM64 build only')
        return 'warn'
    return 'FAIL'


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
        else:
            outputs = [str(work / f'mod_{a}.dll') for a in ('32', '64', 'arm64')]
            code, out, err = run(
                [sys.executable, str(legacy), '-w', str(windhawk), '-f', str(staged),
                 '-o32', outputs[0], '-o64', outputs[1], '-oarm64', outputs[2]],
                work,
            )
            warned = False
            problems = []
            if code != 0:
                problems = diagnostics(out + '\n' + err) or [(err or out).strip()[-600:]]
        result = grade(args, code == 0, warned, problems)
        yield {'id': mod_id, 'result': result, 'problems': problems}


SHOWN = {'pass': 'pass', 'warn': 'warn: not ready to submit', 'FAIL': 'FAIL'}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('mode', choices=['validate', 'compile'])
    parser.add_argument('--upstream', required=True)
    parser.add_argument('--windhawk')
    parser.add_argument('--label', default='')
    parser.add_argument('--only', default='')
    parser.add_argument('--gate', action='store_true',
                        help='the Windhawk the Workshop ships on: compile errors fail')
    args = parser.parse_args()
    args.only = {x for x in re.split(r'[\s,]+', args.only) if x}

    work = Path(os.environ.get('RUNNER_TEMP', '.')) / 'library-check'
    work.mkdir(parents=True, exist_ok=True)
    if args.mode == 'validate':
        results = validate(args, work)
    else:
        results = compile_mods(args, work)

    label = args.label or args.mode
    table = ['| Mod | Result | First problem |', '| --- | --- | --- |']
    counts = dict.fromkeys(SHOWN, 0)
    for result in results:
        counts[result['result']] += 1
        print('RESULT ' + json.dumps({'check': label, **result}), flush=True)
        first = ''
        if result['problems']:
            first = result['problems'][0].replace('|', '\\|')[:200]
        if result['result'] == 'FAIL':
            print(f"::error title={result['id']}::{first}", flush=True)
        table.append(f"| {result['id']} | {SHOWN[result['result']]} | {first} |")
    head = [f'### {label}', '',
            f"{counts['pass']} ready, {counts['warn']} not ready to submit,"
            f" {counts['FAIL']} failed", '']
    summary = os.environ.get('GITHUB_STEP_SUMMARY')
    if summary:
        with open(summary, 'a', encoding='utf-8') as handle:
            handle.write('\n'.join(head + table) + '\n\n')
    return 1 if counts['FAIL'] else 0


if __name__ == '__main__':
    sys.exit(main())
