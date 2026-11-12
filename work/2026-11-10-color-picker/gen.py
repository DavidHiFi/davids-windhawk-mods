"""Builds the Seamless Color Picker settings window from the Seamless Launchpad one.

src/settings-template.cpp is the house settings GUI, copied word for word. This script swaps the
field table, the sidebar pages, names, About text, the icon glyph and a few setting keys, and gives
key boxes real key names so the mod can read them back.

Output: src/settings-block.cpp, wrapped in namespace scpset.
"""
import pathlib
import re
import sys

import schema

HERE = pathlib.Path(__file__).parent
SRC = HERE / 'src'


def cstr(s):
    out = []
    for ch in s:
        o = ord(ch)
        if ch == '\\':
            out.append('\\\\')
        elif ch == '"':
            out.append('\\"')
        elif ch == '\n':
            out.append(' ')
        elif o < 0x20:
            continue
        elif o > 0x7E:
            out.append('\\u%04X' % o)
        else:
            out.append(ch)
    return 'L"' + ''.join(out) + '"'


PAGES = [
    ('Keys', 'The hotkeys that open the picker and the screen magnifier.', 0xE765),
    ('Picker', 'Starting color, the slider, recent colors and the window.', 0xE790),
    ('Screen picker', 'The magnifier you pick screen pixels with.', 0xE71E),
    ('Copying', 'What a copy puts on the clipboard.', 0xE8C8),
    ('Look', 'Accent colors, glass, corners, glow and this window.', 0xE771),
    ('About', 'Version, credits, support and links.', 0xE946),
]
TOP_PAGE = {'Keys': 0, 'Picker': 1, 'Screen': 2, 'Copying': 3, 'Look': 4, 'SettingsWindow': 4}
PAGE_ORDER = list(TOP_PAGE)
HOTKEYS = {'Keys.hotkey', 'Keys.screenHotkey'}


def fields_from(path):
    leaves = schema.walk(schema.load(path))
    rows = []
    leaves.sort(key=lambda l: PAGE_ORDER.index(l[0].split('.')[0]))
    for key, e, v, names in leaves:
        top = key.split('.')[0]
        page = TOP_PAGE[top]
        group = (names[-1] if names else top)
        label = e.get('$name', key.split('.')[-1])
        desc = e.get('$description', '') or ''
        if key in HOTKEYS:
            rows.append(('Hotkey', key, label, desc, str(v), [], 0, 100, page, group))
        elif isinstance(v, bool):
            rows.append(('Check', key, label, desc, '1' if v else '0', [], 0, 100, page, group))
        elif isinstance(v, int):
            m = re.search(r'(-?\d+)\s+to\s+(-?\d+)', desc)
            lo, hi = (int(m.group(1)), int(m.group(2))) if m else (0, 100)
            rows.append(('Number', key, label, desc, str(v), [], min(lo, v), max(hi, v), page, group))
        elif '$options' in e:
            opts = []
            for o in e['$options']:
                (val, lab), = o.items()
                opts.append((str(val), str(lab)))
            rows.append(('Choice', key, label, desc, str(v), opts, 0, 100, page, group))
        elif re.fullmatch(r'#[0-9A-Fa-f]{6}', str(v)):
            rows.append(('Color', key, label, desc, str(v), [], 0, 100, page, group))
        else:
            rows.append(('Text', key, label, desc, str(v), [], 0, 100, page, group))
    return rows


def table(rows):
    out = []
    for kind, key, label, desc, d, opts, lo, hi, page, group in rows:
        o = '{' + ', '.join('{%s, %s}' % (cstr(a), cstr(b)) for a, b in opts) + '}'
        out.append('{K::%s, %s, %s, %s, %s, %s, %d, %d, %d, %s}' % (
            kind, cstr(key), cstr(label), cstr(desc), cstr(d), o, lo, hi, page, cstr(group)))
    return ',\n'.join(out) + '\n'


def sub1(text, old, new, count=1):
    n = text.count(old)
    if n != count:
        sys.exit(f'expected {count}x, found {n}x: {old[:80]!r}')
    return text.replace(old, new)


FORMAT_HOTKEY = '''static std::wstring Set_FormatHotkey(UINT mods, UINT vk) {
    std::wstring text;
    if (mods & MOD_CONTROL) text += L"Ctrl+";
    if (mods & MOD_ALT) text += L"Alt+";
    if (mods & MOD_SHIFT) text += L"Shift+";
    if (mods & MOD_WIN) text += L"Win+";
    // Names the mod's hotkey reader understands.
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) return text + (WCHAR)vk;
    if (vk >= VK_F1 && vk <= VK_F24) return text + L"F" + std::to_wstring(vk - VK_F1 + 1);
    if (vk >= VK_NUMPAD0 && vk <= VK_NUMPAD9) return text + L"Numpad" + std::to_wstring(vk - VK_NUMPAD0);
    static const struct { UINT vk; PCWSTR name; } names[] = {
        {VK_SPACE, L"Space"}, {VK_TAB, L"Tab"}, {VK_RETURN, L"Enter"}, {VK_ESCAPE, L"Esc"},
        {VK_BACK, L"Backspace"}, {VK_INSERT, L"Insert"}, {VK_DELETE, L"Delete"}, {VK_HOME, L"Home"},
        {VK_END, L"End"}, {VK_PRIOR, L"PageUp"}, {VK_NEXT, L"PageDown"}, {VK_UP, L"Up"},
        {VK_DOWN, L"Down"}, {VK_LEFT, L"Left"}, {VK_RIGHT, L"Right"}, {VK_SNAPSHOT, L"PrintScreen"},
        {VK_PAUSE, L"Pause"}, {VK_OEM_PLUS, L"Plus"}, {VK_OEM_MINUS, L"Minus"}, {VK_OEM_COMMA, L"Comma"},
        {VK_OEM_PERIOD, L"Period"},
    };
    for (auto& n : names)
        if (n.vk == vk) return text + n.name;
    WCHAR ch = (WCHAR)MapVirtualKeyW(vk, MAPVK_VK_TO_CHAR);
    if (ch > L' ') return text + ch;
    return text + std::to_wstring(vk);
}'''


def build():
    t = (SRC / 'settings-template.cpp').read_text(encoding='utf-8')
    rows = fields_from(SRC / 'head.wh.cpp')

    a = t.index('    return {\n', t.index('static std::vector<SetField> Set_MakeFields()')) + len('    return {\n')
    b = t.index('    };\n}', a)
    t = t[:a] + table(rows) + t[b:]
    a = t.index('static const SetPageInfo kSetPages[] = {\n') + len('static const SetPageInfo kSetPages[] = {\n')
    b = t.index('};\n', a)
    t = t[:a] + ''.join('{%s, %s, 0x%04X},\n' % (cstr(n), cstr(i), g) for n, i, g in PAGES) + t[b:]

    # Hotkey text the mod can parse back.
    a = t.index('static std::wstring Set_FormatHotkey(UINT mods, UINT vk) {')
    b = t.index('\n}\n', a) + 2
    t = t[:a] + FORMAT_HOTKEY + t[b:]

    t = sub1(t, 'L"WindhawkSeamlessLaunchpadSettings"', 'L"WindhawkSeamlessColorPickerSettings"')
    t = sub1(t, 'constexpr PCWSTR kSetDittoUrl = L"https://windhawk.net/mods/fullscreen-start";',
             'constexpr PCWSTR kSetDittoUrl = L"https://github.com/ShareX/ShareX";')
    t = sub1(t, '%5BSeamless%20Launchpad%5D', '%5BSeamless%20Color%20Picker%5D')
    t = sub1(t, 'constexpr PCWSTR kSetTitle = L"Seamless Launchpad";', 'constexpr PCWSTR kSetTitle = L"Seamless Color Picker";')
    t = sub1(t, 'Set_TextW(w.fRailName.get(), L"Launchpad")', 'Set_TextW(w.fRailName.get(), L"Color Picker")')
    t = sub1(t, 'p.Text(w.fRailName.get(), L"Launchpad",', 'p.Text(w.fRailName.get(), L"Color Picker",')
    t = sub1(t, 'L"Seamless Launchpad settings"', 'L"Seamless Color Picker settings"')
    t = sub1(t, 'p.Text(w.fBig.get(), L"Seamless Launchpad",', 'p.Text(w.fBig.get(), L"Seamless Color Picker",')
    t = sub1(t, 'L"Apps, folders and search in one fullscreen grid, in place of Start."',
             'L"A full color picker on a hotkey, with a screen magnifier and one-click copy."')
    t = sub1(t, 'L"Made by DavidHiFi, based on Fullscreen Start by Rafael Mendes."',
             'L"Made by DavidHiFi, based on the color picker in ShareX."')
    t = sub1(t, 'add(SetItem::Link, 56, L"Based on Fullscreen Start by Rafael Mendes", L"The original Windhawk mod", kSetDittoUrl);',
             'add(SetItem::Link, 56, L"Based on the ShareX color picker", L"By Jaex and the ShareX contributors, GPL-3.0", kSetDittoUrl);')
    t = sub1(t, 'p.Glyph(w.fIconL.get(), 0xE80A, mark, mocha::crust);', 'p.Glyph(w.fIconL.get(), 0xEF3C, mark, mocha::crust);')
    t = sub1(t, 'p.Glyph(glyph, 0xE80A, r, mocha::crust);', 'p.Glyph(glyph, 0xEF3C, r, mocha::crust);')
    t = sub1(t, '// The settings window, from the "..." menu.', '// The settings window, from the gear in the picker.')

    for k in ('nativeSettingsTitleBar', 'settingsGlass'):
        t = sub1(t, f'L"{k}")', f'L"SettingsWindow.{k}")')
    t = sub1(t, 'return !w.render && g_settings.animations && on;',
             'return !w.render && Wh_GetIntSetting(L"Look.animations") && on;')

    t = sub1(t, 'void Settings_Close();\n', '''void Settings_Close();
static std::wstring GetStringSetting(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return s;
}
static void ForceForeground(HWND hwnd) {
    INPUT input{};
    SendInput(1, &input, sizeof(INPUT));
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}
''')

    block = ('// ===========================================================================\n'
             '// Settings window: the Seamless Launchpad settings GUI, the standard for every\n'
             '// DavidHiFi mod. Generated by work\\2026-11-10-color-picker\\gen.py.\n'
             '// ===========================================================================\n'
             '#include <map>\n#include <atomic>\n#include <memory>\n#include <set>\n'
             '#ifndef SCP_SETTINGS_NO_IMAGEBASE\nextern "C" IMAGE_DOS_HEADER __ImageBase;\n#endif\n'
             'namespace scpset {\n' + t.rstrip() + '\n}  // namespace scpset\n')
    (SRC / 'settings-block.cpp').write_text(block, encoding='utf-8')
    print(len(rows), 'fields,', block.count('\n'), 'lines')
    from collections import Counter
    print(Counter((r[8], r[0]) for r in rows))


if __name__ == '__main__':
    build()
