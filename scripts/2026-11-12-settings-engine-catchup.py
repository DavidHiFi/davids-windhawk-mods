"""Bring AutoClicker's and Listary's settings windows up to Seamless Launchpad's engine.

Both kept a frozen older copy of Launchpad's settings engine (they are not generator mods, so
settings-engine-sync.py never reached them). Missing: the real blur under the footer pill, the
new footer buttons, the value box fill and resting edge, Support and About card hover, the rail
resize edge, and the mouse-leave and native-title fixes.

Every function whose only drift is engine code is copied from Launchpad word for word; the ones
that carry the mod's own words (rail name, About card, window title) get only the engine lines.

  python engine-catchup.py <mod-id>     reads the LIVE source, writes work\\2026-11-12-tool-menu-look\\local@<id>.wh.cpp
"""
import pathlib, re, sys

SRC = pathlib.Path(r'C:\ProgramData\Windhawk\ModsSource')
OUT = pathlib.Path(r'H:\Windhawk Configuration\work\2026-11-12-tool-menu-look')
FN = re.compile(r'^(?:static |inline |template[^\n]*\n)*[\w:<>*&, ]+?\b(Set_\w+)\([^;{]*\)\s*(?:const\s*)?\{', re.M)
WHOLE = ['Set_Valid', 'Set_DrawSupport', 'Set_DrawFooter', 'Set_Draw', 'Set_Hit', 'Set_WndProc']


def spans(s):
    out = {}
    for m in FN.finditer(s):
        end = s.find('\n}\n', m.end())
        if end >= 0 and m.group(1) not in out:
            out[m.group(1)] = (m.start(), end + 2)
    return out


def one(t, old, new, what):
    n = t.count(old)
    if n != 1:
        sys.exit(f'{what}: expected 1 match, found {n}')
    return t.replace(old, new)


def main():
    mod = sys.argv[1].removeprefix('local@')
    lp = (SRC / 'local@seamless-launchpad.wh.cpp').read_text(encoding='utf-8').replace('\r\n', '\n')
    raw = (SRC / f'local@{mod}.wh.cpp').read_bytes().decode('utf-8')
    crlf = '\r\n' in raw
    t = raw.replace('\r\n', '\n')
    ref = spans(lp)
    for name in WHOLE:
        a, b = ref[name]
        mine = spans(t)[name]
        t = t[:mine[0]] + lp[a:b] + t[mine[1]:]

    # Rail: Launchpad's function with the mod's own second name line.
    mine = spans(t)['Set_DrawRail']
    own = re.search(r'p\.Text\(w\.fRailName\.get\(\), L"([^"]*)", \{d\.left \+ 90, d\.top \+ 32', t[mine[0]:mine[1]]).group(1)
    a, b = ref['Set_DrawRail']
    rail = one(lp[a:b], 'L"Launchpad", {d.left + 90, d.top + 32', f'L"{own}", {{d.left + 90, d.top + 32', 'rail name')
    t = t[:mine[0]] + rail + t[mine[1]:]

    # About card: hover like Launchpad's, the mod's own words kept.
    t = one(t, 'static void Set_DrawAbout(SetPaint& p, SetWindow& w, const SetItem& it) {\n'
               '    D2D1_RECT_F row = Set_RowRect(w, it);\n'
               '    Set_DrawCard(p, row, 0);\n',
            'static void Set_DrawAbout(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {\n'
            '    D2D1_RECT_F row = Set_RowRect(w, it);\n'
            '    float hov = Set_GlowOf(w, 3800 + idx);\n'
            '    Set_DrawCard(p, row, hov);\n'
            '    p.GradFill(row, 10, 0.13f * hov);\n'
            '    p.GradRing(row, 10, hov, 1.5f);\n', 'about card')

    # Window: the edit box brush matches the new box fill; the layer the footer blur draws into.
    t = one(t, 'w->editBrush = CreateSolidBrush(RefFromRgb(mocha::crust));',
            'w->editBrush = CreateSolidBrush(RefFromRgb(kSetBoxFill));', 'edit brush')
    t = one(t, '    SetCom<ID2D1HwndRenderTarget> rt;\n    std::wstring family, iconFamily;\n',
            '    SetCom<ID2D1HwndRenderTarget> rt;\n'
            '    SetCom<ID2D1BitmapRenderTarget> layer;  // The page, drawn off screen so the footer can blur it.\n'
            '    D2D1_SIZE_F layerSize{};\n'
            '    std::wstring family, iconFamily;\n', 'layer fields')
    if '#include <d2d1effects.h>' not in t:
        t = one(t, '#include <d2d1_1.h>\n', '#include <d2d1_1.h>\n#include <d2d1effects.h>\n', 'effects include')

    m = re.search(r'(?m)^(//\s*@version\s+)(\S+)', t)
    parts = m.group(2).split('.')
    parts[-1] = str(int(parts[-1]) + 1)
    t = t[:m.start(2)] + '.'.join(parts) + t[m.end(2):]
    print(f'{mod}: {m.group(2)} -> {".".join(parts)}')
    (OUT / f'local@{mod}.wh.cpp').write_bytes((t.replace('\n', '\r\n') if crlf else t).encode('utf-8'))


main()
