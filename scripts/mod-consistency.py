r"""Cross-mod consistency check: every Seamless mod looks and behaves the same where they overlap.

Owner rule (2026-11-16): consistency is the most important thing. Every mod with a tray icon,
a tray menu or a settings window uses the same recipe, and this check runs before any install
(Install-StagedMod.ps1 refuses a staged source that fails, exit 5) and after every mod job.

  python scripts\mod-consistency.py check               every installed local mod
  python scripts\mod-consistency.py check <ids...>      the ones named (local@x or x)
  python scripts\mod-consistency.py check --staged <file>   one staged source (the install gate)
  python scripts\mod-consistency.py check --full        also runs settings-engine and settings-material

Rules (fail = refused at install, warn = shown, fix when the mod is next touched):
  tray-badge     fail  A tray icon is the shared clean icon (owner, 2026-11-24): the glyph itself in
                       the blue #89B4FA to mauve #CBA6F7 diagonal gradient on a clear background,
                       Segoe Fluent Icons glyph at 0.84 of the icon, grey #6C7086 to #585B70 when
                       off. Copy MakeTrayIcon from local@seamless-crosshair. Never the mod's own logo.
  tray-plate     warn  The old rounded plate behind the glyph (radius 0.26 of the icon). Becomes a
                       fail once every mod has the clean icon.
  menu-reference fail  A tray menu is the engine's Set_TrayMenu (Clipboard's renderer moved into
                       the Launchpad template, 2026-11-17): regular text, leading glyph column,
                       inset separator, dark Mocha fill, gradient outline, matching hover.
                       Native TrackPopupMenu plus a font hook is not this renderer. Clipboard's
                       own copy of the renderer is a warn until it moves to Set_TrayMenu.
                       A tray mod without an engine settings window has no engine to sync
                       from, so it is a warn there, never a block.
                       This source check is only a preflight; live visual proof is required.
                       Exempt from the badge (not the font): mods whose tray picture is live
                       state, listed in STATE_ICONS.
  window-options fail  A settings window has settingsGlass, nativeSettingsTitleBar and, when the
                       mod has a tray icon, settingsTrayIcon (docs\settings-gui-standard.md).
  frame-apply    fail  The native title bar and glass apply at once, only through the engine:
                       Set_ApplyFrame is called from Set_Save, Set_WndProc (the reload message)
                       and Set_Create; the mod posts WM_APP_SETTINGS_RELOAD to its settings window
                       when settings change from outside; no other engine function touches the
                       window frame or glass (DwmExtendFrameIntoClientArea, blur, accent, backdrop).
  font-default   fail  Every font setting defaults to FiraCode Nerd Font.
  stray-fonts    warn  Text faces other than FiraCode Nerd Font (Fira Code, Fira Mono, Cascadia,
                       Consolas, JetBrains Mono) appear in the source; fine only as a fallback.
  font-value     warn  A stored font setting is not FiraCode Nerd Font (owner data: change it in
                       the mod's settings, with a backup).
  engine         fail  (--full) settings-engine.py check: the settings window equals the template.
  material       fail  (--full) settings-material.py check: the glass is the launcher's.
"""
import re
import subprocess
import sys
import winreg
from pathlib import Path

HERE = Path(__file__).resolve().parent
SRC = Path(r"C:\ProgramData\Windhawk\ModsSource")
REG = r"SOFTWARE\Windhawk\Engine\Mods"
FACE = "FiraCode Nerd Font"
STRAY = ["Fira Code", "Fira Mono", "FiraMono", "Cascadia Code", "Cascadia Mono", "Consolas",
         "JetBrainsMono", "JetBrains Mono"]
HIDDEN = 0x08000000  # CREATE_NO_WINDOW


# Tray icons whose picture is the mod's live state (volume level, bin full or empty): exempt
# from the badge, still bound by the menu font.
STATE_ICONS = ["better-volume-mixer-plus", "recycle-bin-tray-plus"]
# Mods that swap another app's own tray icon (Steam's) and add none of their own: exempt too.
STATE_ICONS += ["mocha-steam-icons", "mocha-app-icons", "dsx-tray-icon-fix"]
# Store mod by uMk0: its backup tray icon is the live battery level (2026-11-24).
STATE_ICONS += ["logitech-battery-tray"]


def is_badge(t):
    """The shared icon colours: blue #89B4FA to mauve #CBA6F7.
    Accepts every spelling in use (0x89B4FA, 0x89 / 255.f, 0x89 + (0xCB - 0x89) * t, 137,180,250)."""
    return bool(("0x89B4FA" in t and "0xCBA6F7" in t)
                or (re.search(r"0x89\b", t) and re.search(r"0xCB\b", t) and re.search(r"0xA6\b", t))
                or (re.search(r"\b137,\s*180,\s*250", t) and re.search(r"\b203,\s*166,\s*247", t)))


# The retired rounded plate behind the glyph (radius 0.26 of the icon), 2026-11-24.
PLATE = re.compile(r"\b(?:radius|rad|plate)\s*=\s*\w+\s*\*\s*0\.26f")
PLATE_LEVEL = "fail"  # every mod clean since 2026-11-26


def yaml_block(t):
    m = re.search(r"// ==WindhawkModSettings==\n(.*?)// ==/WindhawkModSettings==", t, re.S)
    return m.group(1) if m else ""


FRAME_CALLS = re.compile(r"DwmExtendFrameIntoClientArea|SetWindowCompositionAttribute|DwmEnableBlurBehindWindow"
                         r"|DWMWA_SYSTEMBACKDROP_TYPE|\b38 /\* DWMWA_SYSTEMBACKDROP")
FRAME_OWNERS = {"Set_ApplyFrame", "Set_MenuBackdrop"}  # Set_MenuBackdrop: the tray menu popups, not the window.


def set_bodies(t):
    """{name: body} of every engine function, brace-matched."""
    out = {}
    for m in re.finditer(r"^(?:static |inline )*[\w:<>&*, ]+?\b(Set_\w+)\([^;{]*\)\s*(?:const\s*)?\{", t, re.M):
        depth, i = 1, m.end()
        while depth and i < len(t):
            c = t[i]
            if c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
            i += 1
        out.setdefault(m.group(1), t[m.start():i])
    return out


def frame_issues(t):
    out = []
    bodies = set_bodies(t)
    if "Set_ApplyFrame" not in bodies:
        return [("frame-apply", "fail", "no Set_ApplyFrame: the native title bar and glass cannot apply at once")]
    missing = [f for f in ("Set_Save", "Set_WndProc", "Set_Create")
               if f in bodies and "Set_ApplyFrame(" not in bodies[f]]
    if missing:
        out.append(("frame-apply", "fail", "Set_ApplyFrame not called from " + ", ".join(missing)))
    if not re.search(r"PostMessageW\([^;\n]*\b(?:\w+::)?(?:WM_APP_SETTINGS_RELOAD|WM_APP \+ 1\b)", t):
        out.append(("frame-apply", "fail", "settings changed outside are not posted to the window (WM_APP_SETTINGS_RELOAD)"))
    rogue = sorted(n for n, b in bodies.items() if n not in FRAME_OWNERS and FRAME_CALLS.search(b))
    if rogue:
        out.append(("frame-apply", "fail", "frame or glass set outside Set_ApplyFrame: " + ", ".join(rogue)))
    return out


def check_text(t):
    """Returns [(rule, level, detail)] for one source; empty means consistent."""
    out = []
    tray = "Shell_NotifyIcon" in t
    window = "static void Set_DrawPopup(" in t
    state_icon = any(re.search(rf"//\s*@id\s+{x}\s", t) for x in STATE_ICONS)
    if tray and not state_icon:
        if not is_badge(t):
            out.append(("tray-badge", "fail", "tray icon is not the shared gradient icon"))
        else:
            if PLATE.search(t):
                out.append(("tray-plate", PLATE_LEVEL, "tray icon still sits on the old rounded plate: draw the glyph alone"))
            logo = re.search(r"hIcon\s*=\s*\w*(Mark|Logo)\w*", t) or re.search(r"\w*(Mark|Logo)\w*Icon\(", t)
            # A hidden icon (NIS_HIDDEN) only carries a balloon's picture; it never shows in the tray.
            if logo and "NIS_HIDDEN" not in t[max(0, logo.start() - 900):logo.start()]:
                out.append(("tray-badge", "fail", f"tray icon comes from the mod's logo ({logo.group(0)[:40]})"))
    if tray:
        engine_menu = ("static int Set_TrayMenu(" in t and "static void Set_MenuPaint(" in t
                       and len(re.findall(r"\bSet_TrayMenu\(", t)) >= 2)
        clipboard_menu = all(s in t for s in (
            "void PaintMenu(", "void MenuLayout(", "int Ui_ShowMenu(",
            "kMenuIconW", "mocha::surface1", "mocha::base", "c.Glyph(m.glyph",
            "T.ui.get()", "rt->DrawRoundedRectangle({edge, r2, r2}"))
        if clipboard_menu and not engine_menu:
            out.append(("menu-reference", "warn", "own copy of Clipboard's renderer: move the tray menu to the engine's Set_TrayMenu"))
        elif not engine_menu and window:
            out.append(("menu-reference", "fail", "tray menu is not the engine's Set_TrayMenu (sync the engine, docs\\settings-gui-standard.md)"))
        elif not engine_menu:
            # No engine settings window means no engine to sync the menu from: flag it, never block.
            out.append(("menu-reference", "warn", "tray menu is not the engine's Set_TrayMenu (mod has no engine settings window)"))
    if window:
        y = yaml_block(t)
        missing = [k for k in ("settingsGlass", "nativeSettingsTitleBar") + (("settingsTrayIcon",) if tray else ())
                   if not re.search(rf"^\s*- {k}:", y, re.M)]
        if missing:
            out.append(("window-options", "fail", "missing " + ", ".join(missing)))
        out += frame_issues(t)
    options_indent = None
    for line in yaml_block(t).splitlines():
        line = line.lstrip("/ ") if line.startswith("//") else line
        ind = len(line) - len(line.lstrip(" "))
        if options_indent is not None:
            if ind > options_indent and line.strip():
                continue
            options_indent = None
        if re.match(r"^\s*\$options:", line):
            options_indent = ind
            continue
        m = re.match(r"^[ \t]*- ([\w.]*[Ff]ont(?:Family|Name|Face)?):[ \t]*(.*)$", line)
        if not m:
            continue
        key, val = m.group(1), m.group(2).strip().strip("'\"")
        if val and not val.startswith(FACE) and not re.match(r"^(\d|true|false|custom|segoe_)", val):
            out.append(("font-default", "fail", f"{key} defaults to {val}"))
    code = re.sub(r"// ==WindhawkModSettings==.*?// ==/WindhawkModSettings==", "", t, flags=re.S)
    stray = sorted({s for s in STRAY if f'L"{s}' in code})
    if stray:
        out.append(("stray-fonts", "warn", ", ".join(stray)))
    return out


def stored_fonts(mod_id):
    out = []
    try:
        k = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, rf"{REG}\{mod_id}\Settings")
    except OSError:
        return out
    i = 0
    while True:
        try:
            name, val, kind = winreg.EnumValue(k, i)
        except OSError:
            break
        i += 1
        if (kind == winreg.REG_SZ and re.search(r"[Ff]ont(Family|Name|Face)?$", name)
                and val and not val.startswith(FACE) and not re.match(r"^(custom|segoe_)", val)):
            out.append(("font-value", "warn", f"{name} = {val}"))
    return out


def run_tool(script, mod_id):
    try:
        p = subprocess.run([sys.executable, str(HERE / script), "check", mod_id], capture_output=True,
                           text=True, creationflags=HIDDEN, timeout=120)  # Taskbar takes over 30 s under load
    except (OSError, subprocess.TimeoutExpired) as e:
        return True, f"{mod_id}: check could not finish ({type(e).__name__})"
    text = (p.stdout + p.stderr).strip()
    line = next((l for l in text.splitlines() if l.startswith(mod_id)), text[:160])
    bad = p.returncode != 0
    if script == "settings-material.py":
        # This older checker prints every mod and returns zero even for OFF rows.
        row = next((l for l in text.splitlines() if l.split()[:1] == [mod_id]), None)
        bad = bad or row is None or "OFF:" in row
        line = row or f"{mod_id}: material check returned no result: {text[:100]}"
    return bad, line


def installed_ids():
    ids = []
    k = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, REG)
    i = 0
    while True:
        try:
            ids.append(winreg.EnumKey(k, i))
        except OSError:
            break
        i += 1
    return sorted(x for x in ids if x.startswith("local@") and (SRC / f"{x}.wh.cpp").exists())


def main(argv):
    if not argv or argv[0] != "check":
        print(__doc__)
        return 2
    args = argv[1:]
    full = "--full" in args
    args = [a for a in args if a != "--full"]
    if args and args[0] == "--staged":
        f = Path(args[1])
        issues = check_text(f.read_text(encoding="utf-8", errors="replace"))
        for rule, level, detail in issues:
            print(f"{f.name}: {level} {rule}: {detail}")
        fails = [i for i in issues if i[1] == "fail"]
        print(f"{f.name}: {'NOT consistent' if fails else 'consistent'}"
              f" ({len(fails)} fail, {len(issues) - len(fails)} warn)")
        return 1 if fails else 0
    ids = [a if a.startswith("local@") else f"local@{a}" for a in args] or installed_ids()
    total_fail = 0
    for mod_id in ids:
        p = SRC / f"{mod_id}.wh.cpp"
        if not p.exists():
            print(f"{mod_id:44} not installed")
            total_fail += 1
            continue
        t = p.read_text(encoding="utf-8", errors="replace")
        issues = check_text(t) + stored_fonts(mod_id)
        if full and "static void Set_DrawPopup(" in t:
            for script, rule in (("settings-engine.py", "engine"), ("settings-material.py", "material")):
                if rule == "engine" and mod_id == "local@seamless-launchpad":
                    continue  # Launchpad is the template; never compare it with itself.
                bad, line = run_tool(script, mod_id)
                if bad:
                    issues.append((rule, "fail", line[len(mod_id):].strip(" :")[:140]))
        fails = sum(1 for i in issues if i[1] == "fail")
        total_fail += fails
        if not issues:
            if args:
                print(f"{mod_id:44} ok")
            continue
        print(f"{mod_id:44} {'FAIL' if fails else 'warn'}")
        for rule, level, detail in issues:
            print(f"    {level:4} {rule:15} {detail}")
    print(f"\n{len(ids)} mods checked, {total_fail} fail(s)")
    return 1 if total_fail else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
