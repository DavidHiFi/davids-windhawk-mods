"""Keeps every mod's settings window on the standard glass (docs\\settings-gui-standard.md).
The reference is Seamless Launchpad's live source: its glass block, page tint and title fade.
  python settings-material.py check                 list every mod using the settings engine, ok or off-standard
  To bring a mod onto the standard glass: python settings-engine.py sync <id> --out <dir>
"""
import re, sys, glob, os
SRC = r"C:\ProgramData\Windhawk\ModsSource"
REF = os.path.join(SRC, "local@seamless-launchpad.wh.cpp")
# Since Launchpad 2.4.9 the glass lives in Set_ApplyFrame (applied on Save too); settings-engine.py
# sync copies that function, so a mod still on the old inline block is behind the template.
BLOCK = re.compile(r"    if \(glass\) \{\n.*?\n    \} else if \(wasGlass\) \{", re.S)
TINT = re.compile(r"constexpr float kSetGlassTint = [0-9.]+f")
FADE = re.compile(r"D2D1_GRADIENT_STOP stops\[2\] = \{\{0, D2DColor\(mocha::crust, [^)]*\)\}, \{1, D2DColor\(mocha::crust, kSetGlassTint\)\}\};")


def raw(p):
    return open(p, encoding="utf-8", newline="").read()


def glass_block(s):
    # The block ends at Set_ApplyFrame's "else if (wasGlass)"; start from the nearest "if (glass) {"
    # before it, so a mod's own earlier if (glass) code is never swallowed into the match.
    end = s.find("\n    } else if (wasGlass) {")
    if end < 0:
        return None
    start = s.rfind("    if (glass) {\n", 0, end)
    m = BLOCK.match(s, start) if start >= 0 else None
    return m.group(0) if m else None


def parts(s):
    t, f = TINT.search(s), FADE.search(s)
    return (glass_block(s), t.group(0) if t else None, f.group(0) if f else None)


ref = parts(raw(REF).replace("\r\n", "\n"))
if None in ref:
    sys.exit("reference pieces not found in Launchpad source")

if sys.argv[1:2] == ["check"]:
    for p in sorted(glob.glob(os.path.join(SRC, "*.wh.cpp"))):
        s = raw(p).replace("\r\n", "\n")
        if "kSetGlassTint" not in s:
            continue
        got = parts(s)
        bad = [k for k, a, b in zip(("glass", "tint", "fade"), got, ref) if a != b]
        hint = " (behind the template: python scripts\\settings-engine.py sync <id> --out <dir>)" \
            if "glass" in bad and got[0] is None else ""
        print(f"{os.path.basename(p)[:-7]:45} {'ok' if not bad else 'OFF: ' + ', '.join(bad) + hint}")
elif sys.argv[1:2] == ["stage"]:
    sys.exit("stage is replaced by: python scripts\\settings-engine.py sync <id> --out <dir>")
else:
    sys.exit(__doc__)
