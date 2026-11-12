"""2026-11-12 tool menu look: give a tool mod's own menus (tray menu and the like) the same look
as Launchpad's tray menu.

Launchpad's menu runs in explorer, where Seamless Flyouts paints it (blurred Mocha body, the
blue to mauve hover pill, submenus that touch their parent). Tool mods run in their own
windhawk-mod.exe, where Flyouts never loads, so their menus show the plain dark hover.
The fix is the shared menu look block (SeamlessMenuRoom + SeamlessMenuPill + SeamlessMenuSkin)
that Mixer carries; this copies it in.

  python 2026-11-12-tool-menu-look.py <mod-id> [<mod-id> ...]

Reads the LIVE source (C:\\ProgramData\\Windhawk\\ModsSource), writes a patched copy with the
version bumped to work\\2026-11-12-tool-menu-look\\local@<id>.wh.cpp. Touches nothing live.
- No block yet: inserts it before WhTool_ModInit and calls Init/Uninit first thing in
  WhTool_ModInit/WhTool_ModUninit.
- An older block (no pill or no CBT hook): replaced by Mixer's.
- Adds missing libraries to @compilerOptions.
"""
import os, re, sys

SRC = r'C:\ProgramData\Windhawk\ModsSource'
OUT = r'H:\Windhawk Configuration\work\2026-11-12-tool-menu-look'
REF = 'better-volume-mixer-plus'
NEED_LIBS = ['-ld2d1', '-ldwmapi', '-luxtheme', '-lcomctl32', '-lgdi32', '-luser32']


def read(mod):
    with open(os.path.join(SRC, f'local@{mod}.wh.cpp'), encoding='utf-8', newline='') as f:
        t = f.read()
    return t.replace('\r\n', '\n'), '\r\n' in t


def block_span(t):
    # Older copies have no room block; they start at the skin's own header.
    head = '// Menu room: shared by' if '// Menu room: shared by' in t else '// Seamless menu look for this mod'
    s = t.index(head)
    s = t.rfind('// ----', 0, s)
    end = '}  // namespace SeamlessMenuSkin\n'
    e = t.index(end) + len(end)
    return s, e


def one(t, old, new, what):
    n = t.count(old)
    if n != 1:
        sys.exit(f'{what}: expected 1 match, found {n}')
    return t.replace(old, new)


def patch(mod, block):
    t, crlf = read(mod)
    # Only for menus in Windhawk's own tool process. A mod that also runs in explorer (Media
    # Player: its "tool" is explorer.exe -tool-mod) already gets Seamless Flyouts there, and a
    # second skin doubles the frame and the pill (they share no guard). 1.10.12 did that.
    inc = re.findall(r'(?m)^//\s*@include\s+(\S+)', t)
    other = [i for i in inc if i.lower() not in ('windhawk.exe', 'windhawk-mod.exe')]
    if other and 'namespace SeamlessMenuSkin {' not in t:
        print(f'{mod}: skipped, also runs in {", ".join(other)} where Seamless Flyouts skins menus')
        return
    if 'namespace SeamlessMenuSkin {' in t:
        s, e = block_span(t)
        if t[s:e] == block:
            print(f'{mod}: already has the current menu look, skipped')
            return
        t = t[:s] + block + t[e:]
        print(f'{mod}: older menu look replaced')
    else:
        m = re.search(r'(?m)^BOOL WhTool_ModInit\(\)\s*\{\n', t)
        if not m:
            sys.exit(f'{mod}: no WhTool_ModInit definition')
        t = t[:m.start()] + block + '\n' + t[m.start():m.end()] + '    SeamlessMenuSkin::Init();\n' + t[m.end():]
        m = re.search(r'(?m)^void WhTool_ModUninit\(\)\s*\{\n', t)
        if not m:
            sys.exit(f'{mod}: no WhTool_ModUninit definition')
        t = t[:m.end()] + '    SeamlessMenuSkin::Uninit();\n' + t[m.end():]
        print(f'{mod}: menu look added')
    m = re.search(r'(?m)^(//\s*@compilerOptions[ \t]+)(.*)$', t)
    if m:
        have = m.group(2).split()
        add = [l for l in NEED_LIBS if l not in have]
        if add:
            t = t[:m.end(2)] + ' ' + ' '.join(add) + t[m.end(2):]
    else:
        m = re.search(r'(?m)^//\s*@version.*$', t)
        t = t[:m.end()] + '\n// @compilerOptions    ' + ' '.join(NEED_LIBS) + t[m.end():]
    m = re.search(r'(?m)^(//\s*@version\s+)(\S+)', t)
    parts = m.group(2).split('.')
    parts[-1] = str(int(parts[-1]) + 1)
    print(f'{mod}: {m.group(2)} -> {".".join(parts)}')
    t = t[:m.start(2)] + '.'.join(parts) + t[m.end(2):]
    os.makedirs(OUT, exist_ok=True)
    with open(os.path.join(OUT, f'local@{mod}.wh.cpp'), 'w', encoding='utf-8', newline='') as f:
        f.write(t.replace('\n', '\r\n') if crlf else t)


def main():
    ref, _ = read(REF)
    s, e = block_span(ref)
    block = ref[s:e]
    for mod in sys.argv[1:]:
        patch(mod.removeprefix('local@'), block)


if __name__ == '__main__':
    main()
