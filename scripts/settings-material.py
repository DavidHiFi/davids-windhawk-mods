"""Keeps every mod's settings window on the standard glass (docs\\settings-gui-standard.md).
The reference is Seamless Launchpad's live source: its glass block, page tint and title fade.
  python settings-material.py check                 list every mod using the settings engine, ok or off-standard
  python settings-material.py stage <id> <outfile>  write <id>'s live source with the reference material and a
                                                    bumped patch version to <outfile> (install it yourself)
"""
import re, sys, glob, os
SRC = r"C:\ProgramData\Windhawk\ModsSource"
REF = os.path.join(SRC, "local@seamless-launchpad.wh.cpp")
BLOCK = re.compile(r"        if \(w->glass\) \{\n.*?\n        \} else if \(w->nativeButtons\) \{", re.S)
TINT = re.compile(r"constexpr float kSetGlassTint = [0-9.]+f")
FADE = re.compile(r"D2D1_GRADIENT_STOP stops\[2\] = \{\{0, D2DColor\(mocha::crust, [^)]*\)\}, \{1, D2DColor\(mocha::crust, kSetGlassTint\)\}\};")


def raw(p):
    return open(p, encoding="utf-8", newline="").read()


def parts(s):
    b, t, f = BLOCK.search(s), TINT.search(s), FADE.search(s)
    return (b.group(0) if b else None, t.group(0) if t else None, f.group(0) if f else None)


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
        print(f"{os.path.basename(p)[:-7]:45} {'ok' if not bad else 'OFF: ' + ', '.join(bad)}")
elif sys.argv[1:2] == ["stage"]:
    mid, out = sys.argv[2], sys.argv[3]
    s = raw(os.path.join(SRC, mid + ".wh.cpp"))
    crlf = "\r\n" in s
    s = s.replace("\r\n", "\n")
    s, a = BLOCK.subn(lambda m: ref[0], s, 1)
    s, b = TINT.subn(ref[1], s, 1)
    s, c = FADE.subn(ref[2], s, 1)
    m = re.search(r"// @version\s+(\d+)\.(\d+)(?:\.(\d+))?", s)
    ver = f"{m.group(1)}.{m.group(2)}.{int(m.group(3) or 0) + 1}"
    s = s[:m.start()] + f"// @version         {ver}" + s[m.end():]
    if crlf:
        s = s.replace("\n", "\r\n")
    open(out, "w", encoding="utf-8", newline="").write(s)
    print(mid, "glass", a, "tint", b, "fade", c, "->", ver)
else:
    sys.exit(__doc__)
