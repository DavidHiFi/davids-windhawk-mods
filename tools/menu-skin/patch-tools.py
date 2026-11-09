"""Stage the five tool mods that show their own menus with the Seamless menu look.
Tool mods run in windhawk-mod.exe, which Windhawk never loads other mods into, so each
mod carries the look for its own menus (menu-skin.inc.cpp).
- Own mods: version bump in place.
- Repo mods (Magic Pointer, Recycle Bin Tray): forked to local@<id>-plus per the fork recipe.
Output: menu-skin/staged/<new id>.wh.cpp and a plan.json for the install script.
"""
import json, os, re, sys

SRC = r"C:\ProgramData\Windhawk\ModsSource"
HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.join(HERE, "staged")
BLOCK = open(os.path.join(HERE, "menu-skin.inc.cpp"), encoding="utf-8").read()
LIBS = " -ld2d1 -ldwmapi -lcomctl32 -luxtheme -lgdi32"
KOFI = "https://ko-fi.com/DavidHiFi"

MODS = [
    # old id, new id, (old version, new version), fork info or None
    ("local@better-volume-mixer-plus", "local@better-volume-mixer-plus", ("1.4.0", "1.4.1"), None),
    ("local@seamless-dictate", "local@seamless-dictate", ("1.0.3", "1.0.4"), None),
    ("local@window-manager", "local@window-manager", ("1.3.0", "1.3.1"), None),
    ("magic-pointer", "local@magic-pointer-plus", ("1.0.4", "1.0.5"),
     {"id": ("magic-pointer", "magic-pointer-plus"), "name": ("Magic Pointer", "Magic Pointer Plus"),
      "author": "Rono", "based": "Based on Magic Pointer by Rono."}),
    ("recycle-bin-tray", "local@recycle-bin-tray-plus", ("1.0.0", "1.0.1"),
     {"id": ("recycle-bin-tray", "recycle-bin-tray-plus"), "name": ("Recycle Bin Tray", "Recycle Bin Tray Plus"),
      "author": "Wildstyle23", "based": "Based on Recycle Bin Tray by Wildstyle23."}),
]

PLUS_NOTE = ("The Plus version gives its menus the same look as the rest of the desktop: a blurred,\n"
             "rounded Catppuccin menu with roomy rows and one soft hover, matching Seamless Flyouts.\n")


def one(s, pat, repl, name, flags=re.M):
    new, n = re.subn(pat, repl, s, count=1, flags=flags)
    if n != 1:
        sys.exit(f"{name}: pattern not found")
    return new


os.makedirs(OUT, exist_ok=True)
plan = []
for old_id, new_id, (v0, v1), fork in MODS:
    s = open(os.path.join(SRC, old_id + ".wh.cpp"), encoding="utf-8").read()
    if "namespace SeamlessMenuSkin" in s:
        sys.exit(f"{old_id}: already has the menu look")
    s = one(s, r"^(// @version\s+)" + re.escape(v0) + r"\s*$", r"\g<1>" + v1, old_id + " version")
    s = one(s, r"^(// @compilerOptions .*?)\s*$", lambda m: m.group(1) + LIBS, old_id + " libs")
    if fork:
        a, b = fork["id"]
        s = one(s, r"^(// @id\s+)" + re.escape(a) + r"\s*$", r"\g<1>" + b, old_id + " id")
        a, b = fork["name"]
        s = one(s, r"^(// @name\s+)" + re.escape(a) + r"\s*$", r"\g<1>" + b, old_id + " name")
        s = one(s, r"^(// @author\s+)" + re.escape(fork["author"]) + r"\s*$",
                r"\g<1>DavidHiFi, " + fork["author"], old_id + " author")
        if re.search(r"^// @donateUrl", s, re.M):
            s = one(s, r"^(// @donateUrl\s+).*$", r"\g<1>" + KOFI, old_id + " donate")
        else:
            s = one(s, r"^(// @author .*)$", lambda m: m.group(1) + "\n// @donateUrl       " + KOFI, old_id + " donate add")
        # Readme: retitle and say what the Plus version adds and where it comes from.
        a, b = fork["name"]
        s = one(s, r"^# " + re.escape(a) + r"\s*$", "# " + b + "\n\n" + PLUS_NOTE + fork["based"], old_id + " readme")
    # The look sits just before the tool init, which turns it on first thing.
    s = one(s, r"^BOOL WhTool_ModInit\(\) \{\s*$", lambda m: BLOCK + m.group(0) + "\n    SeamlessMenuSkin::Init();",
            old_id + " init")
    s = one(s, r"^void WhTool_ModUninit\(\) \{\s*$", lambda m: m.group(0) + "\n    SeamlessMenuSkin::Uninit();",
            old_id + " uninit")
    out = os.path.join(OUT, new_id + ".wh.cpp")
    open(out, "w", encoding="utf-8", newline="").write(s)
    plan.append({"old": old_id, "new": new_id, "file": out, "version": v1})
    print("staged", new_id, v1)

json.dump(plan, open(os.path.join(OUT, "plan.json"), "w"), indent=1)
