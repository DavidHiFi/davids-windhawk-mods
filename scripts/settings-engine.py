"""Keeps every mod's settings window in sync with the template: Seamless Launchpad's settings engine.

Every Seamless mod with a settings window carries a copy of Launchpad's settings engine (the Set_*
functions, the SetField / SetWindow structs, the kSet constants). This tool makes a template edit
reach every mod, and refuses a mod the edit has not reached.

The manifest (docs/settings-engine.json) lists, per mod:
  swaps   name changes inside engine functions, {"Set_Fn": [[template text, mod text], ...]}
          ("*" for every function), e.g. the window title or the logo glyph.
  owned   engine functions the mod has changed on purpose (its own hooks), each with the hash of
          the template version it was forked from (the text is kept in docs/settings-engine-base/).
          When the template's version of an owned function changes, sync merges the template's
          edit into the mod's version three-way (git merge-file). Only when both edited the same
          lines does check fail until the change is ported by hand and rebaselined.
Every other engine function must equal the template (after swaps), word for word.

  python settings-engine.py check [ids...]          every engine mod, or the ones named
  python settings-engine.py check --staged <file>   a staged source (Install-StagedMod runs this)
  python settings-engine.py sync <id> --out <dir>   writes <dir>/<id>.wh.cpp brought up to the
                                                    template (version bumped); never writes live
  python settings-engine.py sync --staged <file> --out <dir>
  python settings-engine.py rebaseline <id> <Set_Fn>...   after porting a template change by hand
  python settings-engine.py own <id> <Set_Fn>...    mark a function as the mod's own (hash now)
  python settings-engine.py add <id>                add a new mod (owned = its differing functions)
  python settings-engine.py add --staged <file>     the same for a mod not installed yet
  python settings-engine.py status                  one line per mod
  Any command takes --template <file> to use a staged template instead of the installed Launchpad.

Exit codes: 0 in sync, 1 drift (the message says what to do), 2 usage or a source not found.
"""
import difflib
import hashlib
import json
import pathlib
import re
import sys
import time

ROOT = pathlib.Path(__file__).resolve().parent.parent
MANIFEST = ROOT / 'docs' / 'settings-engine.json'
BASE = ROOT / 'docs' / 'settings-engine-base'  # template text of each owned function's fork point
MODS = pathlib.Path(r'C:\ProgramData\Windhawk\ModsSource')
TEMPLATE_ID = 'local@seamless-launchpad'
# Functions that are mod content in every mod: they are never compared, and never flagged.
CONTENT = {'Set_MakeFields', 'Set_BuildPage', 'Set_DrawAbout'}
STRUCTS = ['SetField', 'SetItem', 'SetHit', 'SetWindow', 'SetParts']
# The window switches every mod shows; their descriptions follow the template word for word.
STANDARD_ROWS = ['settingsGlass', 'nativeSettingsTitleBar']

FN = re.compile(r'^(?:static |inline )*[\w:<>&*, ]+?\b(Set_\w+)\([^;{]*\)\s*(?:const\s*)?\{', re.M)
DECL = re.compile(r'^static [^=;{}\n]*\b(Set_\w+)\([^;{}\n]*\);[ \t]*$', re.M)


def read(p):
    return pathlib.Path(p).read_text('utf-8').replace('\r\n', '\n')


def is_engine(text):
    return 'static void Set_DrawPopup(' in text and 'Set_MakeFields' in text


def funcs(text):
    """name -> (start, end, body) for every Set_* function definition."""
    out = {}
    for m in FN.finditer(text):
        end = close_brace(text, m.end() - 1)
        if end is None or m.group(1) in out:
            continue
        end = text.find('\n', end) + 1 or len(text)  # Through the end of the closing line.
        out[m.group(1)] = (m.start(), end, text[m.start():end])
    return out


def close_brace(text, i):
    """Index just past the brace that closes the one at text[i], skipping strings and comments."""
    depth, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == '#' and text[text.rfind('\n', 0, i) + 1:i].strip() == '' and \
                re.match(r'#\s*(else|elif)\b', text[i:i + 12]):
            # Only the first branch of #if/#else counts; the others repeat its braces.
            nest, j = 0, i
            while True:
                m = re.compile(r'^[ \t]*#\s*(if|ifdef|ifndef|endif)\b', re.M).search(text, text.find('\n', j) + 1)
                if not m:
                    return None
                j = m.start()
                if m.group(1).startswith('if'):
                    nest += 1
                elif nest:
                    nest -= 1
                else:
                    i = j
                    break
            continue
        if c == '/' and text.startswith('//', i):
            i = text.find('\n', i)
            if i < 0:
                return None
            continue
        if c == '/' and text.startswith('/*', i):
            i = text.find('*/', i) + 2
            if i < 2:
                return None
            continue
        if c in '"\'':
            if c == '"' and i > 0 and text[i - 1] == 'R':  # Raw string R"x(...)x"
                d = text[i + 1:text.index('(', i)]
                i = text.index(')' + d + '"', i) + len(d) + 2
                continue
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == '\\' else 1
            i = j + 1
            continue
        if c == '{':
            depth += 1
        elif c == '}':
            depth -= 1
            if depth == 0:
                return i + 1
        i += 1
    return None


def norm(s):
    return re.sub(r'\s+', ' ', s).strip()


def h(s):
    return hashlib.sha256(norm(s).encode()).hexdigest()[:16]


def load_manifest():
    return json.loads(MANIFEST.read_text('utf-8')) if MANIFEST.exists() else {'mods': {}}


def save_manifest(m):
    # H: is shared by every thread; opening the file can fail for a moment (Errno 22), so retry.
    data = (json.dumps(m, indent=1, sort_keys=True) + '\n').encode('utf-8')
    for i in range(10):
        try:
            MANIFEST.write_bytes(data)
            return
        except OSError:
            if i == 9:
                raise
            time.sleep(0.5)


def apply_swaps(name, body, swaps):
    for scope in ('*', name):
        for a, b in swaps.get(scope, []):
            body = body.replace(a, b)
    return body


# ---- Struct members ------------------------------------------------------------------------------

def split_top(s, sep=','):
    out, depth, cur = [], 0, ''
    for c in s:
        if c in '<({[':
            depth += 1
        elif c in '>)}]':
            depth -= 1
        if c == sep and depth == 0:
            out.append(cur)
            cur = ''
        else:
            cur += c
    out.append(cur)
    return out


def member_names(line):
    code = line.split('//')[0].strip()
    if not code.endswith(';') or code.startswith(('enum', 'struct', '}')) or '(' in code.split('=')[0]:
        return []
    names = []
    for piece in split_top(code[:-1]):
        piece = re.split(r'[={]', piece, maxsplit=1)[0]
        ids = re.findall(r'[A-Za-z_]\w*', piece)
        if ids:
            names.append(ids[-1])
    return names


def struct_span(text, name):
    m = re.search(r'^struct ' + name + r' \{\n', text, re.M)
    if not m:
        return None
    end = text.index('\n};\n', m.end())
    return m.end(), end + 1


def sync_struct(mod, tpl, name, log):
    ts, ms = struct_span(tpl, name), struct_span(mod, name)
    if not ts or not ms:
        return mod
    tlines = tpl[ts[0]:ts[1]].splitlines(keepends=True)
    mlines = mod[ms[0]:ms[1]].splitlines(keepends=True)
    have = {n for l in mlines for n in member_names(l)}
    last = None  # Index in mlines after which the next missing line goes.
    for tl in tlines:
        names = member_names(tl)
        if not names:
            continue
        missing = [n for n in names if n not in have]
        if not missing:
            idx = max((i for i, l in enumerate(mlines) if set(member_names(l)) & set(names)), default=None)
            if idx is not None:
                last = idx
            continue
        if len(missing) < len(names):
            # Some names exist on their own lines: swap lines that hold only these names for the template line.
            for i in range(len(mlines) - 1, -1, -1):
                mn = member_names(mlines[i])
                if mn and set(mn) <= set(names):
                    del mlines[i]
                    if last is not None and i <= last:
                        last -= 1
        pos = (last + 1) if last is not None else len(mlines)
        mlines.insert(pos, tl)
        last = pos
        have.update(names)
        log.append(f'{name}: added {", ".join(missing)}')
    return mod[:ms[0]] + ''.join(mlines) + mod[ms[1]:]


# ---- Constants and forward declarations ----------------------------------------------------------

# Engine constants: one-line constexpr / static float kSet* declarations. String constants (links,
# titles) are mod content and never copied.
CONST = re.compile(r'^(?:constexpr|static float) (?!PCWSTR|WCHAR)[^\n(]*\bkSet\w+[^\n(]*;[^\n]*$', re.M)


def const_names(line):
    code = line.split('//')[0].strip().rstrip(';')
    code = re.sub(r'^(constexpr|static)\s+\w+(\s*\*)?\s+', '', code)
    return [re.split(r'[={\[]', p, maxsplit=1)[0].strip() for p in split_top(code)]


def sync_consts(mod, tpl, log):
    prev = None
    for m in CONST.finditer(tpl):
        names = [n for n in const_names(m.group(0)) if n]
        # Declared, not merely used: synced functions may already name a constant that is missing.
        if all(re.search(r'\b' + re.escape(n) + r'\s*(?:\[[^\]]*\])?\s*[={]', mod) for n in names):
            prev = names[0]
            continue
        anchor = re.search(r'^[^\n]*\b' + re.escape(prev) + r'\b\s*(?:\[[^\]]*\])?\s*[={][^\n]*\n(?:[ \t]+[^\n]*\n)*', mod, re.M) if prev else None
        if not anchor:
            last = None
            for last in CONST.finditer(mod):
                pass
            anchor = last
        if not anchor:
            log.append(f'constants: cannot place {names}')
            continue
        at = anchor.end()
        if mod[at - 1] != '\n':
            at = mod.index('\n', at) + 1
        mod = mod[:at] + m.group(0) + '\n' + mod[at:]
        log.append(f'constants: added {", ".join(names)}')
        prev = names[0]
    return mod


def sync_rows(mod, tpl, log):
    for key in STANDARD_ROWS:
        tr = re.search(r'\{K::Check, L"' + key + r'", L"(?:[^"\\]|\\.)*", L"((?:[^"\\]|\\.)*)"', tpl)
        ty = re.search(r'^ *- ' + key + r':[^\n]*\n(?: +\$name:[^\n]*\n)? +\$description: ([^\n]*)$', tpl, re.M)
        if not tr or not ty:
            continue

        def row(m):
            return m.group(1) + tr.group(1) + '"'
        new, n = re.subn(r'(\{K::Check, L"(?:\w+\.)?' + key + r'", L"(?:[^"\\]|\\.)*", L")(?:[^"\\]|\\.)*"', row, mod)
        if new != mod:
            log.append(f'row {key}: description')
        mod = new

        want = ty.group(1).strip().strip('"')

        def yml(m):
            quoted = m.group(2).startswith('"')
            return m.group(1) + (f'"{want}"' if quoted else want)
        new = re.sub(r'(^ *- ' + key + r':[^\n]*\n(?: +\$name:[^\n]*\n)? +\$description: )([^\n]*)$', yml, mod, flags=re.M)
        if new != mod:
            log.append(f'settings block {key}: description')
        mod = new
    return mod


# ---- Sync ----------------------------------------------------------------------------------------

def store_base(body):
    """Keeps the template text an owned function was forked from, so a later template change can be
    merged into the mod's version automatically (three-way, like git)."""
    BASE.mkdir(parents=True, exist_ok=True)
    p = BASE / f'{h(body)}.cpp'
    if not p.exists():
        p.write_text(body, 'utf-8', newline='\n')


def merge3(ours, base, theirs):
    """git merge-file on one function. Returns the merged text, or None on a conflict."""
    import subprocess, tempfile
    with tempfile.TemporaryDirectory() as d:
        paths = []
        for name, body in (('ours', ours), ('base', base), ('theirs', theirs)):
            p = pathlib.Path(d) / name
            p.write_text(body, 'utf-8', newline='\n')
            paths.append(str(p))
        r = subprocess.run(['git', 'merge-file', '-p', *paths], capture_output=True,
                           creationflags=0x08000000)
    return r.stdout.decode('utf-8') if r.returncode == 0 else None


def merge_owned(mod, tpl, entry, log, conflicts):
    """Brings the template's newer edits into the functions a mod owns. A function merges when the
    mod's edits and the template's edits touch different lines; otherwise it is left for a hand port."""
    swaps, tf = entry.get('swaps', {}), funcs(tpl)
    for name, base_hash in sorted(entry.get('owned', {}).items()):
        if name in CONTENT or name not in tf or h(tf[name][2]) == base_hash:
            continue
        mf = funcs(mod)
        bp = BASE / f'{base_hash}.cpp'
        if name not in mf or not bp.exists():
            conflicts.append(name)
            continue
        base = apply_swaps(name, read(bp), swaps)
        theirs = apply_swaps(name, tf[name][2], swaps)
        merged = merge3(mf[name][2], base, theirs)
        if merged is None:
            conflicts.append(name)
        elif norm(merged) != norm(mf[name][2]):
            s, e, _ = mf[name]
            mod = mod[:s] + merged + mod[e:]
            log.append(f'{name}: template edit merged into the mod\'s own version')
    return mod


def sync_text(mod, tpl, entry, log, conflicts=None):
    swaps, owned = entry.get('swaps', {}), set(entry.get('owned', {})) | CONTENT
    mod = merge_owned(mod, tpl, entry, log, conflicts if conflicts is not None else [])
    tf = funcs(tpl)
    order = sorted(tf, key=lambda n: tf[n][0])
    for i, name in enumerate(order):
        if name in owned:
            continue
        want = apply_swaps(name, tf[name][2], swaps)
        mf = funcs(mod)
        if name in mf:
            if norm(mf[name][2]) != norm(want):
                s, e, _ = mf[name]
                mod = mod[:s] + want + mod[e:]
                log.append(f'{name}: updated')
            continue
        after = next((n for n in order[i + 1:] if n in mf), None)
        if not after:
            log.append(f'{name}: missing and cannot place')
            continue
        s = mf[after][0]
        mod = mod[:s] + want + '\n' + mod[s:]
        log.append(f'{name}: added')
    # Forward declarations the template keeps, placed before the function that follows them.
    tf = funcs(tpl)
    for m in DECL.finditer(tpl):
        if m.group(0) in mod:
            continue
        nxt = min((v[0], n) for n, v in tf.items() if v[0] > m.start())[1] if any(v[0] > m.start() for v in tf.values()) else None
        mf = funcs(mod)
        if nxt in mf:
            s = mf[nxt][0]
            mod = mod[:s] + m.group(0) + '\n\n' + mod[s:]
            log.append(f'declaration {m.group(1)}: added')
    for st in STRUCTS:
        mod = sync_struct(mod, tpl, st, log)
    mod = sync_consts(mod, tpl, log)
    mod = sync_rows(mod, tpl, log)
    return mod


def owned_drift(mod, tpl, entry):
    """Owned functions whose template edits could not be merged automatically."""
    conflicts = []
    merge_owned(mod, tpl, entry, [], conflicts)
    return conflicts


def mod_id_of(text, path):
    m = re.search(r'//\s*@id\s+(\S+)', text)
    return ('local@' + m.group(1)) if m else pathlib.Path(path).name.replace('.wh.cpp', '')


TEMPLATE_FILE = None  # --template <file>: judge against a staged template instead of the live one.


def template_text():
    return read(TEMPLATE_FILE or MODS / f'{TEMPLATE_ID}.wh.cpp')


def check_one(mid, text, tpl, man, quiet=False):
    entry = man['mods'].get(mid)
    if entry is None:
        print(f'{mid}: has the settings engine but is not in docs/settings-engine.json. '
              f'Run: python scripts/settings-engine.py add {mid}')
        return False
    log = []
    synced = sync_text(text, tpl, entry, log)
    drift = owned_drift(text, tpl, entry)
    ok = not log and not drift
    if ok:
        if not quiet:
            print(f'{mid}: in sync')
        return True
    if log:
        print(f'{mid}: behind the template ({len(log)} change(s)): ' + '; '.join(log[:12]) + (' ...' if len(log) > 12 else ''))
        print(f'   fix: python scripts/settings-engine.py sync {mid} --out <dir>, compile, install')
    if drift:
        print(f'{mid}: the template changed these functions the mod owns: {" ".join(drift)}')
        print(f'   fix: port the template change into the mod by hand, then '
              f'python scripts/settings-engine.py rebaseline {mid} {" ".join(drift)}')
    return False


def engine_mods():
    out = []
    for p in sorted(MODS.glob('*.wh.cpp')):
        mid = p.name[:-7]
        if mid != TEMPLATE_ID and is_engine(read(p)):
            out.append(mid)
    return out


def bump(text):
    m = re.search(r'(//\s*@version\s+)(\d+)\.(\d+)\.(\d+)', text)
    new = f'{m.group(2)}.{m.group(3)}.{int(m.group(4)) + 1}'
    return text[:m.start()] + m.group(1) + new + text[m.end():], new


def main(argv):
    if not argv:
        sys.exit(__doc__)
    cmd, args = argv[0], argv[1:]
    man = load_manifest()
    staged = None
    if '--staged' in args:
        i = args.index('--staged')
        staged = args[i + 1]
        del args[i:i + 2]
    global TEMPLATE_FILE
    if '--template' in args:
        i = args.index('--template')
        TEMPLATE_FILE = args[i + 1]
        del args[i:i + 2]
    out = None
    if '--out' in args:
        i = args.index('--out')
        out = pathlib.Path(args[i + 1])
        del args[i:i + 2]

    if cmd == 'check':
        if staged:
            text = read(staged)
            mid = mod_id_of(text, staged)
            if mid == TEMPLATE_ID:
                # A new template: every other mod's owned functions are judged against it later.
                print(f'{mid}: this is the template; run check after installing to see which mods need a sync')
                return 0
            if not is_engine(text):
                print(f'{mid}: no settings engine')
                return 0
            return 0 if check_one(mid, text, template_text(), man) else 1
        tpl = template_text()
        ids = args or engine_mods()
        bad = sum(not check_one(m, read(MODS / f'{m}.wh.cpp'), tpl, man) for m in ids)
        listed = set(man['mods']) - set(engine_mods())
        for m in sorted(listed):
            if not (MODS / f'{m}.wh.cpp').exists():
                print(f'{m}: listed in the manifest but not installed (fine while it is being built)')
        return 1 if bad else 0

    if cmd == 'sync':
        if not out:
            sys.exit('sync needs --out <dir>')
        src = staged or (MODS / f'{args[0]}.wh.cpp')
        text = read(src)
        mid = mod_id_of(text, src)
        entry = man['mods'].get(mid)
        if entry is None:
            sys.exit(f'{mid} is not in the manifest; run add first')
        log = []
        new = sync_text(text, template_text(), entry, log)
        if not log:
            print(f'{mid}: already in sync')
            return 0
        new, ver = bump(new)
        out.mkdir(parents=True, exist_ok=True)
        (out / f'{mid}.wh.cpp').write_bytes(new.encode('utf-8'))
        print(f'{mid}: v{ver} written to {out / (mid + ".wh.cpp")}')
        for l in log:
            print('   ' + l)
        drift = owned_drift(new, template_text(), entry)
        if drift:
            print(f'   still to port by hand (owned, the edits overlap): {" ".join(drift)}')
        return 0

    if cmd in ('rebaseline', 'own'):
        mid, names = args[0], args[1:]
        tf = funcs(template_text())
        entry = man['mods'].setdefault(mid, {'owned': {}, 'swaps': {}})
        for n in names:
            if n not in tf:
                sys.exit(f'{n} is not a template function')
            entry.setdefault('owned', {})[n] = h(tf[n][2])
            store_base(tf[n][2])
        save_manifest(man)
        print(f'{mid}: {cmd} {" ".join(names)}')
        return 0

    if cmd == 'add':
        # A first install has no live source yet: add --staged <file>. If it was built on an older
        # template, pass that one with --template, then sync --staged against the installed one.
        src = staged or (MODS / f'{args[0]}.wh.cpp')
        text, tpl = read(src), template_text()
        mid = mod_id_of(text, src)
        tf, mf = funcs(tpl), funcs(text)
        entry = {'owned': {}, 'swaps': {}}
        for n in tf:
            if n in CONTENT or n not in mf or norm(mf[n][2]) == norm(tf[n][2]):
                continue
            sw = derive_swaps(tf[n][2], mf[n][2])
            if sw is not None:
                entry['swaps'][n] = sw
            else:
                entry['owned'][n] = h(tf[n][2])
                store_base(tf[n][2])
        man['mods'][mid] = entry
        save_manifest(man)
        print(f'{mid}: added; swaps in {sorted(entry["swaps"])}; owned {sorted(entry["owned"])}')
        return 0

    if cmd == 'status':
        tpl = template_text()
        for m in engine_mods():
            check_one(m, read(MODS / f'{m}.wh.cpp'), tpl, man)
        return 0

    sys.exit(__doc__)


TOK = re.compile(r'L"(?:\\.|[^"\\])*"|"(?:\\.|[^"\\])*"|0x[0-9A-Fa-f]+|\w+|\S')


def derive_swaps(tbody, mbody):
    """Swaps that turn the template function into the mod's, if the only differences are string
    literals, hex numbers or a dropped 'g_settings.animations &&'. None if the mod changed logic."""
    a, b = TOK.findall(tbody), TOK.findall(mbody)
    sw = []
    for op, i1, i2, j1, j2 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
        if op == 'equal':
            continue
        ta, tb = a[i1:i2], b[j1:j2]
        lit = lambda t: t.startswith(('L"', '"', '0x'))
        if op == 'replace' and len(ta) == len(tb) and all(lit(x) and lit(y) for x, y in zip(ta, tb)):
            sw += [[x, y] for x, y in zip(ta, tb)]
        elif op == 'delete' and ta == ['g_settings', '.', 'animations', '&', '&']:
            sw.append(['g_settings.animations && ', ''])
        else:
            return None
    return sw


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
