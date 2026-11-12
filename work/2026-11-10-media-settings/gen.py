"""Builds the Seamless Media Player settings window from the Seamless Launchpad one.

The Launchpad settings GUI (src/settings-template.cpp, copied word for word from the installed
Launchpad source) is the standard. This script only swaps what is Launchpad-specific: the field
table, the sidebar pages, names, About text, the icon glyph and a few setting keys. It also
teaches colour boxes the #AARRGGBB form the visualizer uses, and adds "Open in Windhawk" rows for
the list settings this window cannot edit.

Output: src/settings-block.cpp, wrapped in namespace smpset.
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
            out.append('\\u%04X' % o if o <= 0xFFFF else ch)
        else:
            out.append(ch)
    return 'L"' + ''.join(out) + '"'


# ---- Pages --------------------------------------------------------------------------------------

PAGES = [
    ('Player', 'Where the player sits, its size, cover, text, buttons and progress.', 0xE768),
    ('Look', 'Background, buttons, title and artist text, and album art.', 0xE790),
    ('Visualizer', 'Where the bars go, their shape and colors, and what they listen to.', 0xE9D9),
    ('Menus', 'The player menu you open with a click, and the right-click menu.', 0xE700),
    ('Behavior', 'Clicks, hiding, notifications, this window and debug tools.', 0xE713),
    ('About', 'Version, credits, support and links.', 0xE946),
]
TOP_PAGE = {
    'MainSettings': 0, 'ProgressSettings': 0, 'AppearanceSettings': 1, 'Visualizer': 2,
    'PlayerMenuSettings': 3, 'ContextMenuSettings': 3, 'BehaviorSettings': 4, 'AnimationSettings': 4,
    'NotificationSettings': 4, 'SettingsWindow': 4, 'DebugSettings': 4,
}
# Behavior page order: behavior, animation, notification, this window, debug.
PAGE_ORDER = ['MainSettings', 'ProgressSettings', 'AppearanceSettings', 'Visualizer', 'PlayerMenuSettings',
              'ContextMenuSettings', 'BehaviorSettings', 'AnimationSettings', 'NotificationSettings',
              'SettingsWindow', 'DebugSettings']

# The settings that belong to this window, added to the mod's schema as their own group.
SETTINGS_WINDOW_YAML = """- SettingsWindow:
  - settingsGlass: true
    $name: Blurred settings window
    $description: On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Save, then reopen settings to apply.
  - nativeSettingsTitleBar: false
    $name: Native Windows title bar
    $description: Use the Windows title bar and window buttons for this settings window. Save, then reopen settings to apply.
  $name: Settings window
"""

RANGES = {
    'monitor': (1, 8), 'textSpacing': (-10, 20), 'scrollPauseDuration': (0, 10000), 'loopGap': (0, 500),
    'buttonSize': (16, 48), 'buttonSpacing': (0, 20), 'buttonIconSize': (8, 32), 'titleFontSize': (7, 24),
    'artistFontSize': (7, 24), 'titleCharacterSpacing': (-50, 50), 'artistCharacterSpacing': (-50, 50),
    'emptyIconSize': (6, 64), 'pauseOverlayIconSize': (6, 64), 'appIconSize': (8, 32),
    'miniPlayerHorizontalOffsetNear': (-500, 500), 'horizontalDistanceFromScreenEdge': (0, 1000),
    'verticalDistanceFromScreenEdge': (0, 1000), 'idleHideSeconds': (0, 3600), 'taskbarOffset': (0, 4000),
    'verticalOffset': (-40, 40), 'barIdleSize': (0, 128), 'pauseWhenSilentSeconds': (0, 300),
}

# List settings this window cannot edit: a row that opens Windhawk instead.
LIST_LINKS = {
    'MainSettings.MediaButtonsSettings.mediaButtons': 'Which media buttons show, and their order',
    'BehaviorSettings.ClickActionSettings': 'Click actions',
    'BehaviorSettings.MouseWheelActionSettings': 'Mouse wheel actions',
    'ContextMenuSettings.contextMenuItems': 'Right-click menu items',
}


def clean_group(name):
    name = re.sub(r'\s+(Settings|Setting)(\s+media player)?$', '', name.strip())
    return {'PlayerMenuSettingsNear': 'Near the media player'}.get(name, name)


def num_range(key, name, desc, default):
    leaf = key.split('.')[-1]
    if leaf in RANGES:
        lo, hi = RANGES[leaf]
    else:
        m = re.search(r'\((-?\d+)\s*-\s*(-?\d+)\)', name or '') or \
            re.search(r'(-?\d+)\s+to\s+\+?(-?\d+)', desc or '')
        lo, hi = (int(m.group(1)), int(m.group(2))) if m else (0, 100)
    return min(lo, default), max(hi, default)


def fields_from(path):
    entries = schema.load(path) + __import__('yaml').safe_load(SETTINGS_WINDOW_YAML)
    leaves = schema.walk(entries)
    def group_of(l):
        return clean_group(l[3][-1] if l[3] else l[0].split('.')[0])
    first = {}
    for i, l in enumerate(leaves):
        first.setdefault((l[0].split('.')[0], group_of(l)), i)
    # Page order, then each group's first appearance, so a group never splits around a subgroup.
    leaves.sort(key=lambda l: (PAGE_ORDER.index(l[0].split('.')[0]), first[(l[0].split('.')[0], group_of(l))]))
    rows, links = [], []
    for l in leaves:
        key, e, v, names = l
        top = key.split('.')[0]
        page = TOP_PAGE[top]
        group = group_of(l)
        label = e.get('$name', key.split('.')[-1])
        desc = e.get('$description', '') or ''
        if isinstance(v, list):
            if key in LIST_LINKS:
                links.append((page, group, LIST_LINKS[key]))
            continue
        if isinstance(v, bool):
            rows.append(('Check', key, label, desc, '1' if v else '0', [], 0, 100, page, group))
        elif isinstance(v, int):
            lo, hi = num_range(key, label, desc, v)
            rows.append(('Number', key, label, desc, str(v), [], lo, hi, page, group))
        elif '$options' in e:
            opts = []
            for o in e['$options']:
                (val, lab), = o.items()
                opts.append((str(val), str(lab)))
            rows.append(('Choice', key, label, desc, str(v), opts, 0, 100, page, group))
        elif re.fullmatch(r'#([0-9A-Fa-f]{6}|[0-9A-Fa-f]{8})', str(v)):
            rows.append(('Color', key, label, desc, str(v), [], 0, 100, page, group))
        else:
            rows.append(('Text', key, label, desc, str(v), [], 0, 100, page, group))
    return rows, links


def table(rows):
    out = []
    for kind, key, label, desc, d, opts, lo, hi, page, group in rows:
        o = '{' + ', '.join('{%s, %s}' % (cstr(a), cstr(b)) for a, b in opts) + '}'
        out.append('{K::%s, %s, %s, %s, %s, %s, %d, %d, %d, %s}' % (
            kind, cstr(key), cstr(label), cstr(desc), cstr(d), o, lo, hi, page, cstr(group)))
    return ',\n'.join(out) + '\n'


# ---- Rewrite ------------------------------------------------------------------------------------

def sub1(text, old, new, count=1):
    n = text.count(old)
    if n != count:
        sys.exit(f'expected {count}x, found {n}x: {old[:80]!r}')
    return text.replace(old, new)


def build():
    t = (SRC / 'settings-template.cpp').read_text(encoding='utf-8')
    rows, links = fields_from(SRC / 'media-1.9.11.wh.cpp')

    # Field table and pages.
    a = t.index('    return {\n', t.index('static std::vector<SetField> Set_MakeFields()')) + len('    return {\n')
    b = t.index('    };\n}', a)
    t = t[:a] + table(rows) + t[b:]
    t = sub1(t, '// Generated by test-settings\\gen_table.py from src\\00-header.cpp.',
             '// Generated by work\\2026-11-10-media-settings\\gen.py from the mod\'s settings block.')
    a = t.index('static const SetPageInfo kSetPages[] = {\n') + len('static const SetPageInfo kSetPages[] = {\n')
    b = t.index('};\n', a)
    t = t[:a] + ''.join('{%s, %s, 0x%04X},\n' % (cstr(n), cstr(i), g) for n, i, g in PAGES) + t[b:]

    # Names, links and text.
    t = sub1(t, 'L"WindhawkSeamlessLaunchpadSettings"', 'L"WindhawkSeamlessMediaPlayerSettings"')
    t = sub1(t, 'constexpr PCWSTR kSetDittoUrl = L"https://windhawk.net/mods/fullscreen-start";',
             'constexpr PCWSTR kSetDittoUrl = L"https://windhawk.net/mods/taskbar-media-player";\n'
             'constexpr PCWSTR kSetVizUrl = L"https://windhawk.net/mods/taskbar-audio-visualizer";\n'
             'constexpr PCWSTR kSetWindhawkLink = L"windhawk:";')
    t = sub1(t, '%5BSeamless%20Launchpad%5D', '%5BSeamless%20Media%20Player%5D')
    t = sub1(t, 'constexpr PCWSTR kSetTitle = L"Seamless Launchpad";', 'constexpr PCWSTR kSetTitle = L"Seamless Media Player";')
    t = sub1(t, 'Set_TextW(w.fRailName.get(), L"Launchpad")', 'Set_TextW(w.fRailName.get(), L"Media Player")')
    t = sub1(t, 'p.Text(w.fRailName.get(), L"Launchpad",', 'p.Text(w.fRailName.get(), L"Media Player",')
    t = sub1(t, 'L"Seamless Launchpad settings"', 'L"Seamless Media Player settings"')
    t = sub1(t, 'p.Text(w.fBig.get(), L"Seamless Launchpad",', 'p.Text(w.fBig.get(), L"Seamless Media Player",')
    t = sub1(t, 'L"Apps, folders and search in one fullscreen grid, in place of Start."',
             'L"What\'s playing, with album art, buttons and live spectrum bars, right on the taskbar."')
    t = sub1(t, 'L"Made by DavidHiFi, based on Fullscreen Start by Rafael Mendes."',
             'L"Made by DavidHiFi from two Windhawk mods, credited below."')
    t = sub1(t, 'add(SetItem::Link, 56, L"Based on Fullscreen Start by Rafael Mendes", L"The original Windhawk mod", kSetDittoUrl);',
             'add(SetItem::Link, 56, L"Based on Taskbar Media Player", L"By Salyts, USER-TOURNE and GR0UD", kSetDittoUrl);\n'
             '        add(SetItem::Link, 56, L"Based on Taskbar Audio Visualizer", L"By uMk0", kSetVizUrl);')
    t = sub1(t, '// Blue to mauve rounded square with a clipboard glyph', '// Blue to mauve rounded square with a music note')
    t = sub1(t, 'p.Glyph(w.fIconL.get(), 0xE80A, mark, mocha::crust);', 'p.Glyph(w.fIconL.get(), 0xE8D6, mark, mocha::crust);')
    t = sub1(t, 'p.Glyph(glyph, 0xE80A, r, mocha::crust);', 'p.Glyph(glyph, 0xE8D6, r, mocha::crust);')

    # Keys of this window's own settings, now in the SettingsWindow group.
    for k in ('nativeSettingsTitleBar', 'settingsGlass'):
        t = sub1(t, f'L"{k}")', f'L"SettingsWindow.{k}")')

    # Animations: this mod has no global switch, the Windows setting decides.
    t = sub1(t, 'return !w.render && g_settings.animations && on;', 'return !w.render && on;')

    # Colours: #RRGGBB or #AARRGGBB. The alpha the user had stays when a chip is picked.
    t = sub1(t, '''static bool Set_ParseHex(const std::wstring& text, UINT32& rgb) {
    if (text.size() != 7 || text[0] != L'#') return false;
    UINT32 v = 0;
    for (size_t i = 1; i < 7; i++) {''', '''static bool Set_ParseHex(const std::wstring& text, UINT32& rgb) {
    if ((text.size() != 7 && text.size() != 9) || text[0] != L'#') return false;
    UINT32 v = 0;
    for (size_t i = 1; i < text.size(); i++) {''')
    t = sub1(t, '''static std::wstring Set_HexFromRgb(UINT32 rgb) {
    WCHAR text[16];
    swprintf_s(text, L"#%06X", rgb & 0xFFFFFF);
    return text;
}''', '''static std::wstring Set_HexFromRgb(UINT32 rgb) {
    WCHAR text[16];
    swprintf_s(text, L"#%06X", rgb & 0xFFFFFF);
    return text;
}

// Same colour text, keeping the alpha byte of an #AARRGGBB value.
static std::wstring Set_HexLike(const std::wstring& like, UINT32 rgb) {
    WCHAR text[16];
    if (like.size() == 9) swprintf_s(text, L"#%02X%06X", (rgb >> 24) & 0xFF, rgb & 0xFFFFFF);
    else swprintf_s(text, L"#%06X", rgb & 0xFFFFFF);
    return text;
}''')
    t = sub1(t, '''                if (Set_ParseHex(text, rgb)) {
                    f.cur = Set_HexFromRgb(rgb);''', '''                if (Set_ParseHex(text, rgb)) {
                    f.cur = Set_HexLike(text, rgb);''')
    t = sub1(t, 'Set_SetStatus(w, L"Use a color like #89B4FA.", true);',
             'Set_SetStatus(w, L"Use a color like #89B4FA, or #FF89B4FA with opacity first.", true);')
    t = sub1(t, '''                f.cur = Set_HexFromRgb(kSetChips[hit->b]);''', '''                {
                    UINT32 old = 0xFF000000;
                    Set_ParseHex(f.cur, old);
                    f.cur = Set_HexLike(f.cur, (f.cur.size() == 9 ? (old & 0xFF000000) : 0) | kSetChips[hit->b]);
                }''')
    t = sub1(t, 'f.kind == SetField::Color ? 7 : 260', 'f.kind == SetField::Color ? 9 : 260')
    t = sub1(t, 'case SetField::Color: return 362;', 'case SetField::Color: return 378;')
    t = sub1(t, '''            p.box = {r - 96, mid - h, r, mid + h};
            float x = p.box.left - 12 - (kSetChipCount * 26 - 6);''', '''            p.box = {r - 112, mid - h, r, mid + h};
            float x = p.box.left - 12 - (kSetChipCount * 26 - 6);''')

    # "Open in Windhawk" rows for the list settings, at the end of their page.
    link_tab = ''.join('    {%d, %s},\n' % (p, cstr(text)) for p, g, text in links)
    t = sub1(t, 'struct SetPageInfo {', '''struct SetListLink {
    int page;
    PCWSTR text;
};
// Lists (button order, click actions, menu items) are edited on Windhawk's page.
static const SetListLink kSetListLinks[] = {
%s};

struct SetPageInfo {''' % link_tab)
    t = sub1(t, '''    if (w.page == kSetAboutPage) {
        auto add = [&]''', '''    bool listGroup = false;
    for (const SetListLink& l : kSetListLinks) {
        if (l.page != w.page) continue;
        if (!listGroup) {
            SetItem g;
            g.type = SetItem::Group;
            g.text = L"Lists, edited in Windhawk";
            y += 14;
            g.y = y;
            g.h = 22;
            y += g.h + 6;
            w.items.push_back(g);
            listGroup = true;
        }
        SetItem it;
        it.type = SetItem::Link;
        it.y = y;
        it.h = 56;
        it.text = l.text;
        it.sub = L"Opens Windhawk, where lists can be changed";
        it.url = kSetWindhawkLink;
        y += it.h + kSetRowGap;
        w.items.push_back(it);
    }
    if (w.page == kSetAboutPage) {
        auto add = [&]''')
    t = sub1(t, '''    Wh_Log(L"settings: would open %s", url);
#else
    ShellExecuteW(nullptr, L"open", url, nullptr, nullptr, SW_SHOWNORMAL);
#endif''', '''    Wh_Log(L"settings: would open %s", url);
#else
    if (wcscmp(url, kSetWindhawkLink) == 0) {
        WCHAR exe[MAX_PATH]{};
        ExpandEnvironmentStringsW(L"%ProgramFiles%\\\\Windhawk\\\\windhawk.exe", exe, MAX_PATH);
        DWORD attrs = GetFileAttributesW(exe);
        bool found = attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY);
        ShellExecuteW(nullptr, L"open", found ? exe : L"windhawk.exe", nullptr, nullptr, SW_SHOWNORMAL);
        return;
    }
    ShellExecuteW(nullptr, L"open", url, nullptr, nullptr, SW_SHOWNORMAL);
#endif''')

    # Helpers the Launchpad source had elsewhere.
    t = sub1(t, 'void Settings_Close();\n', '''void Settings_Close();
static std::wstring GetStringSetting(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return s;
}
// SetForegroundWindow works when this process had the last input; an empty SendInput gives it.
static void ForceForeground(HWND hwnd) {
    INPUT input{};
    SendInput(1, &input, sizeof(INPUT));
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}
''')
    t = sub1(t, '// The settings window, from the "..." menu.', '// The settings window, from the gear in the player menu.')

    block = ('// ===========================================================================\n'
             '// Settings window: the Seamless Launchpad settings GUI, the standard for every\n'
             '// DavidHiFi mod. Generated by work\\2026-11-10-media-settings\\gen.py.\n'
             '// ===========================================================================\n'
             '#include <map>\n#include <atomic>\n#include <memory>\n#include <set>\n'
             '#ifndef SMP_SETTINGS_NO_IMAGEBASE\nextern "C" IMAGE_DOS_HEADER __ImageBase;\n#endif\n'
             'namespace smpset {\n' + t.rstrip() + '\n}  // namespace smpset\n')
    (SRC / 'settings-block.cpp').write_text(block, encoding='utf-8')
    print(len(rows), 'fields,', len(links), 'list links,', block.count('\n'), 'lines')
    from collections import Counter
    print(Counter((r[8], r[0]) for r in rows))


if __name__ == '__main__':
    build()
