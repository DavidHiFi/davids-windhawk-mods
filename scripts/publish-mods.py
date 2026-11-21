"""Publish every installed DavidHiFi Windhawk mod to GitHub, with its preset, and refresh the Workshop feed.

    python publish-mods.py                 # publish everything that changed, push both repos
    python publish-mods.py --mod <id>      # publish one mod (local@ prefix optional)
    python publish-mods.py --dry-run       # show what would change, write nothing
    python publish-mods.py --no-push       # commit locally, do not push
    python publish-mods.py --scrub-settings  # only re-scrub settings/*.json in the repo (Build-Repo.ps1 calls this)
    python publish-mods.py --self-test     # run the scrubber's unit tests

What it does, in order:
 1. Reads the installed sources (C:\\ProgramData\\Windhawk\\ModsSource\\local@*.wh.cpp) whose @author starts
    with DavidHiFi, and their live settings and on/off state from the registry (read only).
 2. Writes into davids-windhawk-mods: the source (existing path kept), the manifest entry, presets/<id>.json,
    presets/davidhifi-setup.json, and the mod's entries in settings/mods-settings.json and mods-state.json.
    Every setting goes through the scrubber below first: credentials, personal data and profile paths never leave.
 3. Commits "Publish: <mods>" and pushes main (never forced). No change, no commit.
 4. Writes feed.json in the seamless-workshop repo, pinned to the pushed commit, commits and pushes it.

Files are staged in memory and each is written to a temp file, then moved into place. If anything fails before
the commit, every file is put back the way it was.
"""
from __future__ import annotations

import argparse
import copy
import datetime as dt
import getpass
import hashlib
import json
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

WORKSPACE = Path(__file__).resolve().parent.parent
MODS_REPO = WORKSPACE / 'davids-windhawk-mods'
WORKSHOP_REPO = WORKSPACE / 'seamless-workshop'
MODS_SOURCE = Path(r'C:\ProgramData\Windhawk\ModsSource')
REG_MODS = r'SOFTWARE\Windhawk\Engine\Mods'
GH_PUSH = ['-c', 'credential.helper=', '-c', 'credential.helper=!gh auth git-credential']
OWNER = 'DavidHiFi'
WORKSHOP_ID = 'local@seamless-workshop'
PRESET_FORMAT = 'seamless-workshop-preset-1'
FEED_FORMAT = 'seamless-workshop-feed-1'
RAW = 'https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods'
NOWIN = getattr(subprocess, 'CREATE_NO_WINDOW', 0)

# Repo paths that differ from mods/local/<name>/<name>.wh.cpp (same table as tools/Build-Repo.ps1).
LOCAL_PATHS = {
    'local@alt-snap-drag': 'mods/local/alt-snap-drag/alt-snap.wh.cpp',
}

# ----------------------------------------------------------------------------------------------------------
# Scrubber
# ----------------------------------------------------------------------------------------------------------

# Whole words in a key name that mark it private. Keys are split into words on ".", "[n]", "_", "-", spaces
# and camelCase, so "accounts[0].apiKey" -> accounts, api, key.
PRIVATE_WORDS = {
    'token', 'tokens', 'secret', 'secrets', 'password', 'passwords', 'passwd', 'pwd', 'passphrase',
    'apikey', 'apikeys', 'webhook', 'webhooks', 'auth', 'oauth', 'bearer', 'cookie', 'cookies',
    'credential', 'credentials', 'clientid', 'appsecret', 'privatekey', 'accesskey',
    'location', 'city', 'latitude', 'longitude', 'lat', 'lon', 'lng', 'zip', 'zipcode', 'postcode',
    'postal', 'address', 'email', 'username', 'phone', 'country', 'street', 'placename', 'geo',
}
# Adjacent word pairs that mark a key private.
PRIVATE_PAIRS = {
    ('api', 'key'), ('client', 'id'), ('client', 'secret'), ('application', 'id'), ('user', 'name'),
    ('place', 'name'), ('access', 'key'), ('secret', 'key'), ('private', 'key'), ('license', 'key'),
    ('subscription', 'key'), ('auth', 'key'), ('zip', 'code'), ('post', 'code'), ('e', 'mail'),
    ('session', 'key'), ('refresh', 'token'), ('access', 'token'), ('sync', 'peers'),
}
# Word pairs that look private but are layout or behaviour switches; a key holding one of these is kept
# (its value still goes through the value checks).
SAFE_PAIRS = {
    ('taskbar', 'location'), ('target', 'location'), ('detect', 'location'), ('address', 'bar'),
    ('country', 'display'), ('password', 'screen'), ('location', 'secondary'),
}

SECRET_VALUE = re.compile(
    r'(?:\bsk-[A-Za-z0-9_\-]{8,}|\bsk_(?:live|test)_[A-Za-z0-9]{10,}|\bgh[pousr]_[A-Za-z0-9]{10,}|\bgithub_pat_[A-Za-z0-9_]{20,}|'
    r'\bxox[abposr]-|\bAIza[0-9A-Za-z_\-]{10,}|\bAKIA[0-9A-Z]{12,}|\beyJ[A-Za-z0-9_\-]{8,}\.[A-Za-z0-9_\-]{4,}|'
    r'\bbearer\s+[A-Za-z0-9._~+/\-]{12,}=*|discord(?:app)?\.com/api/webhooks|hooks\.slack\.com/|-----BEGIN [A-Z ]*PRIVATE KEY)',
    re.I)
LONG_RUN = re.compile(r'[A-Za-z0-9+/=_\-]{32,}')
EMAIL = re.compile(r'(?<![\w@])[A-Za-z0-9._%+\-]+@[A-Za-z0-9\-]+(?:\.[A-Za-z0-9\-]+)*\.[A-Za-z]{2,24}\b')
PROFILE = re.compile(r'(?i)\b([A-Z]:[\\/]+Users[\\/]+)([^\\/:"*?<>|\r\n]+)')
PUBLIC_PROFILES = {'public', 'default', 'default user', 'all users'}


def _personal_names() -> set[str]:
    names = {'localuser', 'foxtrot'}
    for n in (os.environ.get('USERNAME'), Path.home().name):
        if n:
            names.add(n.lower())
    try:
        for d in Path(r'C:\Users').iterdir():
            if d.is_dir() and d.name.lower() not in PUBLIC_PROFILES:
                names.add(d.name.lower())
    except OSError:
        pass
    try:
        import winreg
        with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, r'SOFTWARE\Microsoft\Windows NT\CurrentVersion') as k:
            owner = str(winreg.QueryValueEx(k, 'RegisteredOwner')[0]).strip()
            if owner and owner.lower() not in {'user', 'owner', 'admin', 'windows user'}:
                names.add(owner.lower())
    except OSError:
        pass
    return {n for n in names if len(n) >= 3}


PERSONAL_NAMES = _personal_names()


def key_words(key: str) -> list[str]:
    s = re.sub(r'\[\d*\]', ' ', key)
    s = re.sub(r'([a-z0-9])([A-Z])', r'\1 \2', s)
    s = re.sub(r'([A-Z]+)([A-Z][a-z])', r'\1 \2', s)
    return [w for w in re.split(r'[\s._\-/]+', s.lower()) if w]


def private_key_reason(key: str) -> str | None:
    """Why a key name is private, or None. Plain 'key' counts only as the whole last segment ('key', 'keys'),
    so hotkey and shortcut settings like 'toggleKey' survive."""
    words = key_words(key)
    if any(p in SAFE_PAIRS for p in zip(words, words[1:])):
        return None
    for w in words:
        if w in PRIVATE_WORDS:
            return f'name:{w}'
    for a, b in zip(words, words[1:]):
        if (a, b) in PRIVATE_PAIRS:
            return f'name:{a} {b}'
    last = key_words(re.split(r'[.\]]', key.rstrip(']'))[-1] or key)
    if last in (['key'], ['keys']):
        return 'name:key'
    return None


def _looks_random(run: str) -> bool:
    if re.fullmatch(r'[0-9a-fA-F]{32,}', run):
        return True
    classes = sum(bool(re.search(p, run)) for p in (r'[a-z]', r'[A-Z]', r'[0-9]'))
    digits = sum(c.isdigit() for c in run)
    # Random keys flip between upper, lower and digits all the time; CamelCase names and hyphenated words
    # ("TaskNeedsAttentionRunningIndicator=1", "my-theme-name-2024") flip once per word.
    flips = sum(1 for a, b in zip(run, run[1:])
                if (a.islower() and b.isupper()) or (a.isupper() and b.islower()) or (a.isdigit() != b.isdigit()))
    return classes == 3 and digits >= 3 and flips >= 0.35 * len(run)


def secret_value_reason(value: str) -> str | None:
    if SECRET_VALUE.search(value):
        return 'value:token pattern'
    for run in LONG_RUN.findall(value):
        if _looks_random(run):
            return 'value:long random string'
    for m in EMAIL.finditer(value):
        if not m.group(0).lower().startswith('local@'):
            return 'value:email'
    return None


def scrub_string(value: str) -> tuple[str | None, str | None]:
    """Returns (new value or None to drop, reason or None when unchanged)."""
    r = secret_value_reason(value)
    if r:
        return None, r
    new, changed = value, False

    def repl(m: re.Match) -> str:
        nonlocal changed
        if m.group(2).strip().lower() in PUBLIC_PROFILES:
            return m.group(0)
        changed = True
        return '%USERPROFILE%'
    new = PROFILE.sub(repl, new)
    low = new.lower()
    if any(n in low for n in PERSONAL_NAMES):
        return None, 'value:personal name or path'
    return (new, 'value:profile path made generic') if changed else (value, None)


def scrub_flat(settings: dict) -> tuple[dict, list[tuple[str, str]]]:
    """Scrub one mod's flat settings {key: str|int}. Returns (clean copy, [(key, reason)])."""
    out, notes = {}, []
    for k, v in settings.items():
        r = private_key_reason(k)
        if r:
            notes.append((k, r))
            continue
        if isinstance(v, str):
            nv, r = scrub_string(v)
            if r:
                notes.append((k, r))
            if nv is None:
                continue
            v = nv
        out[k] = v
    return out, notes


def scrub_tree(obj, path: str = '') -> tuple[object, list[tuple[str, str]]]:
    """Scrub any JSON value. Private keys are dropped from objects; secret strings are dropped from objects and
    blanked in lists (so list positions stay meaningful)."""
    notes: list[tuple[str, str]] = []
    if isinstance(obj, dict):
        out = {}
        for k, v in obj.items():
            p = f'{path}.{k}' if path else str(k)
            r = private_key_reason(str(k))
            if r:
                notes.append((p, r))
                continue
            if isinstance(v, str):
                nv, r = scrub_string(v)
                if r:
                    notes.append((p, r))
                if nv is None:
                    continue
                out[k] = nv
            else:
                nv, sub = scrub_tree(v, p)
                notes += sub
                out[k] = nv
        return out, notes
    if isinstance(obj, list):
        out = []
        for i, v in enumerate(obj):
            nv, sub = (scrub_string(v) if isinstance(v, str) else scrub_tree(v, f'{path}[{i}]'))
            if isinstance(v, str):
                if sub:
                    notes.append((f'{path}[{i}]', sub))
                nv = '' if nv is None else nv
            else:
                notes += sub
            out.append(nv)
        return out, notes
    if isinstance(obj, str):
        nv, r = scrub_string(obj)
        return ('' if nv is None else nv), ([(path, r)] if r else [])
    return obj, notes


def scrub_by_mod(data: dict) -> tuple[dict, list[tuple[str, str]]]:
    """Scrub {mod id: {...}} files. The mod id itself is never judged (start-menu-open-real-file-location is a
    mod, not a location)."""
    out, notes = {}, []
    for mid, vals in data.items():
        clean, sub = scrub_tree(vals, mid)
        out[mid] = clean
        notes += sub
    return out, notes


def source_secret_reason(text: str) -> str | None:
    """A mod source is held back only for a real credential pattern; long strings are normal in code."""
    m = SECRET_VALUE.search(text)
    return 'token pattern' if m else None


# ----------------------------------------------------------------------------------------------------------
# Live install (read only)
# ----------------------------------------------------------------------------------------------------------

def header(text: str) -> dict:
    block = text.split('// ==/WindhawkMod==')[0]
    out = {}
    for tag in ('id', 'name', 'description', 'version', 'author', 'github', 'license'):
        m = re.search(rf'^//\s*@{tag}\s+(.+?)\s*$', block, re.M)
        out[tag] = m.group(1) if m else ''
    return out


def one_line(md: str, limit: int = 280) -> str:
    """Markdown bullets or lines as one plain line for the Workshop to show, scrubbed, or ''."""
    md = re.sub(r'!\[[^\]]*\]\([^)]*\)', '', md)
    md = re.sub(r'\[([^\]]+)\]\([^)]*\)', r'\1', md)
    md = re.sub(r'\*\*|__|`', '', md)
    items, cur = [], ''
    for line in md.splitlines():
        t = line.strip()
        bullet = re.match(r'[-*+] +', t)
        if not t or bullet or t.startswith('#'):
            if cur:
                items.append(cur)
            cur = t[bullet.end():] if bullet else ''
        else:
            cur = f'{cur} {t}'.strip()
    if cur:
        items.append(cur)
    out = ' '.join(i if i.endswith(('.', '!', '?', ':')) else i + '.' for i in items)
    if len(out) > limit:
        out = out[:limit].rsplit(' ', 1)[0].rstrip(',;:') + '...'
    value, _ = scrub_string(out)
    return value or ''


def whats_new(text: str, version: str) -> str:
    """The source readme's '## What's new in <version>' section as one line, or ''."""
    text = text.replace('\r\n', '\n')
    m = re.search(r'//\s*==WindhawkModReadme==\s*/\*(.*?)\*/', text, re.S)
    if not m or not version:
        return ''
    sec = re.search(rf"^#+[ \t]*What's new in {re.escape(version)}[ \t]*$(.*?)(?=^#|\Z)", m.group(1), re.M | re.S | re.I)
    return one_line(sec.group(1)) if sec else ''


def reg_values(path: str) -> dict:
    import winreg
    out = {}
    try:
        with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, path, 0, winreg.KEY_READ | winreg.KEY_WOW64_64KEY) as k:
            i = 0
            while True:
                try:
                    name, val, typ = winreg.EnumValue(k, i)
                except OSError:
                    break
                i += 1
                if typ in (winreg.REG_SZ, winreg.REG_EXPAND_SZ):
                    out[name] = str(val)
                elif typ in (winreg.REG_DWORD, winreg.REG_QWORD):
                    out[name] = int(val)
    except FileNotFoundError:
        return {}
    return out


def installed_owner_mods() -> dict[str, dict]:
    """{'local@x': {'path','bytes','header','state','settings'}} for every installed DavidHiFi mod."""
    mods = {}
    for f in sorted(MODS_SOURCE.glob('local@*.wh.cpp')):
        mid = f.name[:-len('.wh.cpp')]
        raw = f.read_bytes()
        h = header(raw.decode('utf-8', 'replace'))
        if not h['author'].startswith(OWNER):
            continue
        if h['id'] and 'local@' + h['id'] != mid:
            print(f'warning: {mid} skipped, its @id is {h["id"]}')
            continue
        key = reg_values(rf'{REG_MODS}\{mid}')
        if not key:
            continue  # source left behind by an uninstall
        mods[mid] = {
            'path': f, 'bytes': raw, 'header': h,
            'state': {'disabled': int(key.get('Disabled', 0) or 0) != 0, 'include': str(key.get('Include', '')),
                      'exclude': str(key.get('Exclude', '')), 'architecture': str(key.get('Architecture', '')),
                      'version': str(key.get('Version', ''))},
            'settings': dict(sorted(reg_values(rf'{REG_MODS}\{mid}\Settings').items())),
        }
    return mods


# ----------------------------------------------------------------------------------------------------------
# Git and files
# ----------------------------------------------------------------------------------------------------------

class Fail(Exception):
    pass


def git(repo: Path, *args: str, check: bool = True, raw: bool = False):
    p = subprocess.run(['git', '-C', str(repo), *args], capture_output=True, creationflags=NOWIN)
    if check and p.returncode != 0:
        raise Fail(f'git {args[0]} failed: {p.stderr.decode("utf-8", "replace").strip()[-300:]}')
    return p if not check else (p.stdout if raw else p.stdout.decode('utf-8', 'replace').strip())


def jdump(obj) -> bytes:
    return (json.dumps(obj, indent=2, ensure_ascii=False) + '\n').encode('utf-8')


def jload(path: Path, default):
    try:
        return json.loads(path.read_text(encoding='utf-8-sig'))
    except FileNotFoundError:
        return default


class Stage:
    """Collects file writes; applies them atomically per file and can undo them all."""

    def __init__(self, repo: Path):
        self.repo, self.files, self.backup = repo, {}, {}

    def put(self, rel: str, data: bytes):
        p = self.repo / rel
        old = p.read_bytes() if p.exists() else None
        if old != data:
            self.files[rel] = data
        else:
            self.files.pop(rel, None)

    def apply(self):
        for rel, data in self.files.items():
            p = self.repo / rel
            self.backup[rel] = p.read_bytes() if p.exists() else None
            p.parent.mkdir(parents=True, exist_ok=True)
            fd, tmp = tempfile.mkstemp(dir=p.parent, prefix='.publish-', suffix='.tmp')
            with os.fdopen(fd, 'wb') as fh:
                fh.write(data)
            os.replace(tmp, p)

    def undo(self):
        for rel, old in self.backup.items():
            p = self.repo / rel
            if old is None:
                p.unlink(missing_ok=True)
            else:
                p.write_bytes(old)


def ensure_main_current(repo: Path, push: bool):
    branch = git(repo, 'rev-parse', '--abbrev-ref', 'HEAD')
    if branch != 'main':
        raise Fail(f'{repo.name} is on {branch}, not main')
    if push:
        git(repo, *GH_PUSH, 'fetch', '--quiet', 'origin', 'main')
        behind = int(git(repo, 'rev-list', '--count', 'main..origin/main') or 0)
        if behind:
            git(repo, *GH_PUSH, 'pull', '--quiet', '--rebase', '--autostash', 'origin', 'main')


def push(repo: Path):
    p = git(repo, *GH_PUSH, 'push', 'origin', 'main', check=False)
    if p.returncode == 0:
        return
    err = p.stderr.decode('utf-8', 'replace')
    if 'non-fast-forward' in err or 'rejected' in err or 'fetch first' in err:
        r = git(repo, *GH_PUSH, 'pull', '--rebase', '--autostash', 'origin', 'main', check=False)
        if r.returncode != 0:
            git(repo, 'rebase', '--abort', check=False)
            raise Fail(f'{repo.name}: pull --rebase failed, local commit kept, nothing forced')
        p = git(repo, *GH_PUSH, 'push', 'origin', 'main', check=False)
        if p.returncode == 0:
            return
        err = p.stderr.decode('utf-8', 'replace')
    raise Fail(f'{repo.name}: push failed: {err.strip()[-200:]}')


def commit(repo: Path, stage: Stage, message: str):
    paths = list(stage.files)
    git(repo, 'add', '--', *paths)
    git(repo, 'commit', '--quiet', '-m', message, '--', *paths)


# ----------------------------------------------------------------------------------------------------------
# Publishing
# ----------------------------------------------------------------------------------------------------------

def repo_path(mid: str, manifest_by_id: dict) -> str:
    e = manifest_by_id.get(mid)
    if e and e.get('source'):
        return e['source']
    if mid in LOCAL_PATHS:
        return LOCAL_PATHS[mid]
    name = mid.removeprefix('local@')
    return f'mods/local/{name}/{name}.wh.cpp'


def preset_doc(entries: list[dict]) -> dict:
    return {'format': PRESET_FORMAT, 'mods': entries}


def preset_entry(mid: str, info: dict) -> tuple[dict, list]:
    clean, notes = scrub_flat(info['settings'])
    return {'id': mid, 'enabled': not info['state']['disabled'], 'settings': clean}, notes


def scrub_settings_files(stage: Stage, repo: Path) -> list[str]:
    """Run settings/mods-settings.json, mods-state.json and quota-mod-localstorage.json through the scrubber."""
    report = []
    ms_path = repo / 'settings' / 'mods-settings.json'
    ms = jload(ms_path, None)
    if isinstance(ms, dict):
        out = {}
        for mid, vals in ms.items():
            if isinstance(vals, dict):
                out[mid], notes = scrub_flat(vals)
                report += [f'mods-settings.json {mid} {k} ({r})' for k, r in notes]
            else:
                out[mid] = vals
        if out != ms:
            stage.put('settings/mods-settings.json', jdump(out))
    for rel in ('settings/mods-state.json', 'settings/quota-mod-localstorage.json'):
        data = jload(repo / rel, None)
        if not isinstance(data, dict):
            continue
        clean, notes = scrub_by_mod(data)
        report += [f'{Path(rel).name} {k} ({r})' for k, r in notes]
        if clean != data:
            stage.put(rel, jdump(clean))
    return report


def publish_mods_repo(args) -> tuple[str, list[str]]:
    repo = MODS_REPO
    ensure_main_current(repo, push=not (args.dry_run or args.no_push))
    live = installed_owner_mods()
    want = None
    if args.mod:
        want = args.mod if args.mod.startswith('local@') else 'local@' + args.mod
        if want not in live:
            return f'davids-windhawk-mods: {want} is not an installed {OWNER} mod, nothing to publish', []
    targets = {want: live[want]} if want else live

    manifest = jload(repo / 'manifest.json', None)
    if not isinstance(manifest, dict) or 'mods' not in manifest:
        raise Fail('manifest.json is missing or not in the expected shape')
    by_id = {m['id']: m for m in manifest['mods']}
    mods_settings = jload(repo / 'settings' / 'mods-settings.json', {})
    mods_state = jload(repo / 'settings' / 'mods-state.json', {})
    setup_old = jload(repo / 'presets' / 'davidhifi-setup.json', {'mods': []})
    setup = {e['id']: e for e in setup_old.get('mods', [])}

    stage = Stage(repo)
    held, scrub_notes, changed_ids = [], [], []
    new_manifest_mods = copy.deepcopy(manifest['mods'])
    idx = {m['id']: i for i, m in enumerate(new_manifest_mods)}
    for mid, info in targets.items():
        text = info['bytes'].decode('utf-8', 'replace')
        r = source_secret_reason(text)
        if r:
            held.append(f'{mid} ({r})')
            continue
        h = info['header']
        rel = repo_path(mid, by_id)
        before = set(stage.files)
        stage.put(rel, info['bytes'])
        entry = dict(by_id.get(mid) or {'id': mid, 'name': '', 'author': '', 'github': '', 'version': '',
                                         'license': '', 'origin': 'local', 'upstream': '', 'source': rel,
                                         'enabled': False})
        entry.update({'name': h['name'], 'author': h['author'], 'github': h['github'] or entry.get('github', ''),
                      'version': info['state']['version'] or h['version'],
                      'license': h['license'] or entry.get('license') or '', 'origin': 'local', 'source': rel,
                      'enabled': not info['state']['disabled']})
        if mid in idx:
            new_manifest_mods[idx[mid]] = entry
        else:
            idx[mid] = len(new_manifest_mods)
            new_manifest_mods.append(entry)
        pe, notes = preset_entry(mid, info)
        scrub_notes += [f'{mid} {k} ({why})' for k, why in notes]
        bare = mid.removeprefix('local@')
        stage.put(f'presets/{bare}.json', jdump(preset_doc([pe])))
        setup[mid] = pe
        if info['settings']:
            mods_settings[mid] = info['settings']  # scrubbed with the whole file below
        else:
            mods_settings.pop(mid, None)
        mods_state[mid] = info['state']
        if set(stage.files) != before:
            changed_ids.append(mid)

    if not want:  # a full run drops mods that are no longer installed from the whole-setup preset
        for mid in list(setup):
            if mid not in live:
                setup.pop(mid)
    stage.put('presets/davidhifi-setup.json',
              jdump(preset_doc([setup[k] for k in sorted(setup, key=lambda x: x.removeprefix('local@'))])))

    if new_manifest_mods != manifest['mods']:
        m2 = dict(manifest)
        m2['mods'] = new_manifest_mods
        m2['counts'] = {'mods': len(new_manifest_mods),
                        'enabled': sum(1 for m in new_manifest_mods if m.get('enabled')),
                        'local': sum(1 for m in new_manifest_mods if m.get('origin') == 'local')}
        m2['generatedAt'] = dt.datetime.now().astimezone().isoformat(timespec='seconds')
        stage.put('manifest.json', jdump(m2))

    # settings files: write the refreshed entries, then scrub everything in them
    clean_settings = {}
    for mid, vals in mods_settings.items():
        clean_settings[mid], notes = scrub_flat(vals) if isinstance(vals, dict) else (vals, [])
    clean_state, _ = scrub_by_mod(mods_state)
    if clean_settings != jload(repo / 'settings' / 'mods-settings.json', {}):
        stage.put('settings/mods-settings.json', jdump(clean_settings))
    if clean_state != jload(repo / 'settings' / 'mods-state.json', {}):
        stage.put('settings/mods-state.json', jdump(clean_state))
    quota = jload(repo / 'settings' / 'quota-mod-localstorage.json', None)
    if isinstance(quota, dict):
        q2, _ = scrub_by_mod(quota)
        if q2 != quota:
            stage.put('settings/quota-mod-localstorage.json', jdump(q2))

    gi = repo / '.gitignore'
    gtext = gi.read_text(encoding='utf-8') if gi.exists() else ''
    if '*.bak-*' not in gtext.split():
        stage.put('.gitignore', (gtext.rstrip('\n') + '\n# Local backups\n*.bak-*\n').encode('utf-8'))

    extra = []
    if held:
        extra.append('held back (credential-like text in the source): ' + ', '.join(held))
    if args.verbose:
        extra += ['scrubbed: ' + n for n in scrub_notes]

    ahead = 0
    if not (args.dry_run or args.no_push):
        ahead = int(git(repo, 'rev-list', '--count', 'origin/main..main') or 0)
    if not stage.files:
        if ahead:
            push(repo)
            return f'davids-windhawk-mods: no new change, pushed {ahead} waiting commit(s) ({git(repo, "rev-parse", "--short", "HEAD")})', extra
        return 'davids-windhawk-mods: up to date, nothing to commit', extra
    names = changed_ids or ['presets and settings']
    msg = 'Publish: ' + ', '.join(n.removeprefix('local@') for n in names)
    if len(msg) > 300:
        msg = f'Publish: {len(names)} mods'
    if args.dry_run:
        files = sorted(stage.files)
        return f'davids-windhawk-mods: would commit {len(files)} file(s) as "{msg[:120]}"', extra + ['  ' + f for f in files[:60]]
    try:
        stage.apply()
        commit(repo, stage, msg + '\n\nWritten by scripts/publish-mods.py: sources, presets and scrubbed settings.')
    except Exception:
        stage.undo()
        git(repo, 'reset', '--quiet', '--', *stage.files, check=False)
        raise
    sha = git(repo, 'rev-parse', '--short', 'HEAD')
    if args.no_push:
        return f'davids-windhawk-mods: committed {sha} ({len(stage.files)} files), not pushed', extra
    push(repo)
    return f'davids-windhawk-mods: pushed {git(repo, "rev-parse", "--short", "HEAD")} ({len(stage.files)} files, {len(changed_ids)} mods)', extra


def build_feed(repo: Path, ref: str) -> dict:
    commit_sha = git(repo, 'rev-parse', ref)

    def show(path: str) -> bytes | None:
        p = git(repo, 'show', f'{commit_sha}:{path}', check=False)
        return p.stdout if p.returncode == 0 else None

    manifest = json.loads(show('manifest.json'))
    by_id = {m['id']: m for m in manifest['mods']}
    setup_raw = show('presets/davidhifi-setup.json')
    setup = json.loads(setup_raw) if setup_raw else {'mods': []}
    feed = {'format': FEED_FORMAT, 'commit': commit_sha, 'generatedAt': ''}
    mods = []
    ids = [e['id'] for e in setup['mods']]
    if WORKSHOP_ID not in ids and WORKSHOP_ID in by_id:
        ids.append(WORKSHOP_ID)
    presets = {e['id']: e for e in setup['mods']}
    for mid in ids:
        m = by_id.get(mid)
        if not m or not m.get('source'):
            continue
        raw = show(m['source'])
        if raw is None:
            continue
        h = header(raw.decode('utf-8', 'replace'))
        if 'local@' + h['id'] != mid or not h['author'].startswith(OWNER):
            print(f'feed: skipped {mid}, its @id or @author does not match')
            continue
        item = {'id': mid, 'name': h['name'] or m.get('name', ''), 'version': h['version'] or m.get('version', ''),
                'description': h['description'],
                'url': f'{RAW}/{commit_sha}/{m["source"]}', 'sha256': hashlib.sha256(raw).hexdigest()}
        text = raw.decode('utf-8', 'replace')
        changes = whats_new(text, item['version'])
        if mid == WORKSHOP_ID and not changes:
            changes = one_line(changelog_notes(item['version']))
        if changes:
            item['changes'] = changes
        if mid == WORKSHOP_ID:
            feed['app'] = item
            continue
        p = presets.get(mid, {'enabled': bool(m.get('enabled')), 'settings': {}})
        item['preset'] = {'enabled': bool(p.get('enabled')), 'settings': p.get('settings', {})}
        mods.append(item)
    if 'app' in feed:  # key order: app before mods
        feed = {'format': feed['format'], 'commit': commit_sha, 'generatedAt': '', 'app': feed['app']}
    feed['mods'] = sorted(mods, key=lambda x: x['name'].lower())
    return feed


def publish_workshop_repo(args) -> str:
    repo = WORKSHOP_REPO
    if not (repo / '.git').exists():
        return 'seamless-workshop: no clone yet, feed not written'
    pushing = not (args.dry_run or args.no_push)
    ensure_main_current(repo, push=pushing)
    ref = 'origin/main' if pushing else ('origin/main' if git(MODS_REPO, 'rev-parse', '--verify', '--quiet', 'origin/main', check=False).returncode == 0 else 'main')
    if pushing:
        git(MODS_REPO, *GH_PUSH, 'fetch', '--quiet', 'origin', 'main')
    feed = build_feed(MODS_REPO, ref)
    old = jload(repo / 'feed.json', None)
    if isinstance(old, dict):
        cmp_old = dict(old, generatedAt='')
        if cmp_old == feed:
            ahead = int(git(repo, 'rev-list', '--count', 'origin/main..main') or 0) if pushing else 0
            if ahead:
                push(repo)
                return f'seamless-workshop: feed current, pushed {ahead} waiting commit(s)'
            return f'seamless-workshop: feed already at {feed["commit"][:7]}, nothing to commit'
    feed['generatedAt'] = dt.datetime.now(dt.timezone.utc).isoformat(timespec='seconds').replace('+00:00', 'Z')
    stage = Stage(repo)
    stage.put('feed.json', jdump(feed))
    n = len(feed['mods'])
    app = ', app ' + feed['app']['version'] if 'app' in feed else ''
    if args.dry_run:
        return f'seamless-workshop: would write feed.json ({n} mods{app}, commit {feed["commit"][:7]})'
    try:
        stage.apply()
        commit(repo, stage, f'Feed: {n} mods at davids-windhawk-mods {feed["commit"][:7]}')
    except Exception:
        stage.undo()
        git(repo, 'reset', '--quiet', '--', 'feed.json', check=False)
        raise
    if not pushing:
        return f'seamless-workshop: committed feed ({n} mods{app}), not pushed'
    push(repo)
    return f'seamless-workshop: pushed {git(repo, "rev-parse", "--short", "HEAD")} (feed {n} mods{app}, pinned {feed["commit"][:7]})'


def version_key(v: str) -> tuple:
    return tuple(int(x) for x in re.findall(r'\d+', v)[:4])


def changelog_notes(version: str) -> str:
    """The '## <version>' section of the Workshop CHANGELOG.md, or ''."""
    p = WORKSHOP_REPO / 'CHANGELOG.md'
    if not p.exists():
        return ''
    m = re.search(rf'^## {re.escape(version)}\b[^\n]*\n(.*?)(?=^## |\Z)', p.read_text(encoding='utf-8'), re.M | re.S)
    return m.group(1).strip() if m else ''


def release_workshop(args) -> str:
    """Cut a seamless-workshop GitHub release when the Workshop in the feed is newer than the latest release,
    so the one-line installer always hands out the version the feed lists."""
    feed = jload(WORKSHOP_REPO / 'feed.json', None)
    app = feed.get('app') if isinstance(feed, dict) else None
    if not app:
        return 'seamless-workshop release: no app entry in the feed'
    ver = app['version']
    p = subprocess.run(['gh', 'release', 'view', '-R', f'{OWNER}/seamless-workshop', '--json', 'tagName', '-q', '.tagName'],
                       capture_output=True, text=True, creationflags=NOWIN)
    latest = p.stdout.strip() if p.returncode == 0 else ''
    if latest and version_key(latest) >= version_key(ver):
        return f'seamless-workshop release: {latest} is current'
    raw = git(MODS_REPO, 'show', f'{feed["commit"]}:{app["url"].split(feed["commit"] + "/", 1)[1]}', raw=True)
    if hashlib.sha256(raw).hexdigest() != app['sha256']:
        raise Fail('Workshop source does not match the feed checksum; no release cut')
    if source_secret_reason(raw.decode('utf-8', 'replace')):
        raise Fail('Workshop source looks like it holds a secret; no release cut')
    if args.dry_run or args.no_push:
        return f'seamless-workshop release: would cut v{ver} (latest is {latest or "none"})'
    notes = changelog_notes(ver) or f'Seamless Workshop {ver}.'
    notes += ('\n\n### Install or update\n\nNew here? One line in PowerShell installs it, and Windhawk too if you need it:\n\n'
              '```powershell\nirm https://raw.githubusercontent.com/DavidHiFi/seamless-workshop/main/Install-SeamlessWorkshop.ps1 | iex\n```\n\n'
              'Already have it? It updates itself: open Updates in Seamless Workshop. '
              'The `.sha256` file lets you check the download by hand.')
    with tempfile.TemporaryDirectory(prefix='workshop-release-') as d:
        cpp = Path(d) / 'seamless-workshop.wh.cpp'
        cpp.write_bytes(raw)
        (Path(d) / 'seamless-workshop.wh.cpp.sha256').write_text(f'{app["sha256"]}  seamless-workshop.wh.cpp\n', encoding='ascii')
        nf = Path(d) / 'notes.md'
        nf.write_text(notes, encoding='utf-8')
        p = subprocess.run(['gh', 'release', 'create', f'v{ver}', '-R', f'{OWNER}/seamless-workshop', '--target', 'main',
                            '--title', f'Seamless Workshop {ver}', '--notes-file', str(nf), '--latest',
                            str(cpp), str(Path(d) / 'seamless-workshop.wh.cpp.sha256')],
                           capture_output=True, text=True, creationflags=NOWIN)
    if p.returncode != 0:
        raise Fail(f'gh release create v{ver} failed: {(p.stderr or p.stdout).strip()[:300]}')
    return f'seamless-workshop release: cut v{ver}'


# ----------------------------------------------------------------------------------------------------------
# Tests
# ----------------------------------------------------------------------------------------------------------

def self_test() -> int:
    import unittest

    fake_gh = 'gh' + 'p_' + 'A1b2C3d4E5f6G7h8I9j0K1l2M3n4O5p6Q7r8'
    fake_sk = 's' + 'k-' + 'proj-ABCdef123456ghiJKL789'
    fake_b64 = 'Zm9vYmFyMTIzNDU2Nzg5MGFiY2RlZmdoaWprbG1ub3BxcnN0'

    class T(unittest.TestCase):
        def test_key_names(self):
            for k in ('apiKey', 'accounts[0].api_key', 'githubToken', 'clientSecret', 'webhookUrl', 'password',
                      'weather.latitude', 'lon', 'placeName', 'userName', 'email', 'homeAddress', 'clientId',
                      'applicationId', 'auth.bearer', 'cookieJar', 'location', 'zipCode', 'phoneNumber', 'key',
                      'provider[2].key', 'syncPeers'):
                self.assertIsNotNone(private_key_reason(k), k)
            for k in ('toggleKey', 'hotkey', 'shortcutKey', 'keyboardLayout', 'monkeyMode', 'longPress',
                      'translucency', 'colorAccent', 'latency', 'fontName', 'iconSize', 'appName', 'tokenizer',
                      'taskbarLocation', 'transparentAddressBar', 'clock.weather.detectLocation'):
                self.assertIsNone(private_key_reason(k), k)

        def test_values(self):
            for v in (fake_gh, fake_sk, 'Bearer abcdefghijkl1234', fake_b64, 'a' * 8 + '0123456789abcdef' * 2,
                      'https://discord.com/api/webhooks/1/x', 'me@example.com', 'xoxb-1234-abcd'):
                self.assertIsNone(scrub_string(v)[0], v)
            for v in ('Segoe UI Variable', '#89B4FA', 'C:\\Windows\\Media\\chimes.wav', 'explorer.exe|dwm.exe',
                      'local@seamless-launchpad.wh.cpp', 'catppuccin-mocha-blue-to-mauve-gradient-2024', '1.4.32',
                      'Target=TaskNeedsAttentionRunningIndicator=12'):
                self.assertEqual(scrub_string(v), (v, None), v)

        def test_profile_paths(self):
            name = next(iter(sorted(PERSONAL_NAMES)))
            self.assertEqual(scrub_string(f'C:\\Users\\{name}\\Music\\a.wav')[0], '%USERPROFILE%\\Music\\a.wav')
            self.assertEqual(scrub_string(f'C:/Users/{name}/Pictures')[0], '%USERPROFILE%/Pictures')
            self.assertEqual(scrub_string('C:\\Users\\Public\\x.wav')[0], 'C:\\Users\\Public\\x.wav')
            self.assertIsNone(scrub_string(f'D:\\{name}-stuff\\x')[0])
            self.assertIsNone(scrub_string(f'C:\\Users\\{name}\\{name}.txt')[0])

        def test_flat_and_tree(self):
            clean, notes = scrub_flat({'apiKey': 'x', 'size': 4, 'note': fake_gh, 'font': 'Fira Code'})
            self.assertEqual(clean, {'size': 4, 'font': 'Fira Code'})
            self.assertEqual({k for k, _ in notes}, {'apiKey', 'note'})
            tree, _ = scrub_tree({'a': {'accounts': [{'apiKey': 'k', 'name': 'x'}], 'list': [fake_sk, 'ok']}})
            self.assertEqual(tree, {'a': {'accounts': [{'name': 'x'}], 'list': ['', 'ok']}})
            state, _ = scrub_by_mod({'start-menu-open-real-file-location': {'disabled': False, 'include': 'a.exe'}})
            self.assertIn('start-menu-open-real-file-location', state)

        def test_whats_new(self):
            src = ("// ==WindhawkModReadme==\n/*\n# Mod\n\n## What's new in 1.2.0\n\n- **Faster** open.\n"
                   "- Menu [edge](https://x.y) fixed\n  on hover\n\n## What's new in 1.1.0\n\n- Old.\n*/\n")
            self.assertEqual(whats_new(src, '1.2.0'), 'Faster open. Menu edge fixed on hover.')
            self.assertEqual(whats_new(src, '1.1.0'), 'Old.')
            self.assertEqual(whats_new(src, '1.3.0'), '')
            self.assertEqual(one_line(f'- key {fake_gh}'), '')
            self.assertTrue(one_line('- ' + 'word ' * 100).endswith('...'))

        def test_source_scan(self):
            self.assertIsNotNone(source_secret_reason(f'const char* k = "{fake_gh}";'))
            self.assertIsNone(source_secret_reason('// @name Seamless Launchpad\nint hotkey = 0;'))

    suite = unittest.defaultTestLoader.loadTestsFromTestCase(T)
    res = unittest.TextTestRunner(verbosity=1).run(suite)
    return 0 if res.wasSuccessful() else 1


# ----------------------------------------------------------------------------------------------------------

def main() -> int:
    ap = argparse.ArgumentParser(description='Publish DavidHiFi mods, presets and the Workshop feed.')
    ap.add_argument('--dry-run', action='store_true')
    ap.add_argument('--no-push', action='store_true')
    ap.add_argument('--mod')
    ap.add_argument('--scrub-settings', action='store_true')
    ap.add_argument('--self-test', action='store_true')
    ap.add_argument('--verbose', action='store_true')
    args = ap.parse_args()
    if args.self_test:
        return self_test()
    try:
        if args.scrub_settings:
            stage = Stage(MODS_REPO)
            report = scrub_settings_files(stage, MODS_REPO)
            if not args.dry_run:
                stage.apply()
            print(f'settings scrubbed: {len(report)} value(s) removed or made generic, {len(stage.files)} file(s) '
                  f'{"would change" if args.dry_run else "changed"}')
            if args.verbose:
                for line in report:
                    print('  ' + line)
            return 0
        line, extra = publish_mods_repo(args)
        print(line)
        for e in extra:
            print(e)
        if not line.endswith('nothing to publish'):
            print(publish_workshop_repo(args))
        print(release_workshop(args))
        return 0
    except Fail as e:
        print(f'publish failed: {e}', file=sys.stderr)
        return 1


if __name__ == '__main__':
    sys.exit(main())
