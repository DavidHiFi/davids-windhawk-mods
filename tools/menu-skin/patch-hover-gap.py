"""Stage the hover-gap fix: the menu hover keeps a gap above and below, so the first and last
rows stay clear of the menu's rounded corners. Six mods, patch version bump each.
Output: menu-skin/staged-gap/<id>.wh.cpp
Usage: python -I patch-hover-gap.py"""
import os, re, sys

SRC = r"C:\ProgramData\Windhawk\ModsSource"
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "staged-gap")

TOOL_OLD = """        if (!g_hoverDC) return FALSE;
        NineGrid(hdc, g_hoverDC, pRect, 9, 9, 8, 8);"""
TOOL_NEW = """        if (!g_hoverDC) return FALSE;
        // Keep the same gap above and below as at the sides, so the first and last rows'
        // rounded hover stays clear of the menu's own rounded corners.
        RECT rc = *pRect;
        InflateRect(&rc, 0, -MulDiv(2, Dpi(), USER_DEFAULT_SCREEN_DPI));
        NineGrid(hdc, g_hoverDC, &rc, 9, 9, 8, 8);"""
SF_OLD = """    if (iPartId != MENU_POPUPSEPARATOR)
        DrawNineGridStretch(hdc, g_themeCache.menuitem[index], pRect, 9, 9, 8, 8);"""
SF_NEW = """    if (iPartId != MENU_POPUPSEPARATOR) {
        // Popup rows keep the same gap above and below as at the sides, so the first and
        // last rows' rounded hover stays clear of the menu's own rounded corners.
        RECT rc = *pRect;
        if (index == 1)
            InflateRect(&rc, 0, -MulDiv(2, g_Dpi, USER_DEFAULT_SCREEN_DPI));
        DrawNineGridStretch(hdc, g_themeCache.menuitem[index], &rc, 9, 9, 8, 8);
    }"""

MODS = [
    ("local@seamless-flyouts", "2.0.0", "2.0.1", SF_OLD, SF_NEW),
    ("local@recycle-bin-tray-plus", "1.0.1", "1.0.2", TOOL_OLD, TOOL_NEW),
    ("local@magic-pointer-plus", "1.0.5", "1.0.6", TOOL_OLD, TOOL_NEW),
    ("local@better-volume-mixer-plus", "1.4.1", "1.4.2", TOOL_OLD, TOOL_NEW),
    ("local@seamless-dictate", "1.0.4", "1.0.5", TOOL_OLD, TOOL_NEW),
    ("local@window-manager", "1.3.1", "1.3.2", TOOL_OLD, TOOL_NEW),
]

os.makedirs(OUT, exist_ok=True)
for mod_id, v0, v1, old, new in MODS:
    raw = open(os.path.join(SRC, mod_id + ".wh.cpp"), encoding="utf-8", newline="").read()
    crlf = "\r\n" in raw
    s = raw.replace("\r\n", "\n")
    if s.count(old) != 1:
        sys.exit(f"{mod_id}: hover code found {s.count(old)} times")
    s = s.replace(old, new)
    s, n = re.subn(r"^(// @version\s+)" + re.escape(v0) + r"[ \t]*$", r"\g<1>" + v1, s, count=1, flags=re.M)
    if n != 1:
        sys.exit(f"{mod_id}: version {v0} not found")
    if crlf:
        s = s.replace("\n", "\r\n")
    open(os.path.join(OUT, mod_id + ".wh.cpp"), "w", encoding="utf-8", newline="").write(s)
    print("staged", mod_id, v1)
