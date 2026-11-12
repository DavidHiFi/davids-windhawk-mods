"""Lists which settings-engine functions (Set_*) in each mod differ from Seamless Launchpad's copy.
  python engine-drift.py            summary per mod
  python engine-drift.py <id> <fn>  unified diff of one function against Launchpad
"""
import re, sys, glob, os, difflib
SRC = os.environ.get("DRIFT_SRC", r"C:\ProgramData\Windhawk\ModsSource")  # or a folder of staged copies
FN = re.compile(r"^(?:static |inline |template[^\n]*\n)*[\w:<>*&, ]+?\b(Set_\w+)\([^;{]*\)\s*(?:const\s*)?\{", re.M)


def funcs(path):
    s = open(path, encoding="utf-8", errors="replace").read().replace("\r\n", "\n")
    out = {}
    for m in FN.finditer(s):
        end = s.find("\n}\n", m.end())
        if end < 0:
            continue
        out.setdefault(m.group(1), s[m.start():end + 2])
    return out


ref = funcs(os.path.join(SRC, "local@seamless-launchpad.wh.cpp"))
if len(sys.argv) == 3:
    mine = funcs(os.path.join(SRC, sys.argv[1] + ".wh.cpp"))
    a, b = ref.get(sys.argv[2], ""), mine.get(sys.argv[2], "")
    sys.stdout.writelines(difflib.unified_diff(a.splitlines(True), b.splitlines(True), "launchpad", sys.argv[1], n=1))
    sys.exit()
print(f"launchpad: {len(ref)} engine functions")
for p in sorted(glob.glob(os.path.join(SRC, "*.wh.cpp"))):
    mid = os.path.basename(p)[:-7]
    if mid == "local@seamless-launchpad":
        continue
    mine = funcs(p)
    if "Set_DrawFooter" not in mine:
        continue
    diff = [k for k in ref if k in mine and ref[k] != mine[k]]
    missing = [k for k in ref if k not in mine]
    print(f"\n{mid}: {len(mine)} fns, {len(diff)} differ, {len(missing)} missing")
    for k in diff:
        d = sum(1 for l in difflib.unified_diff(ref[k].splitlines(), mine[k].splitlines(), n=0) if l[:1] in "+-" and l[:3] not in ("+++", "---"))
        print(f"   {k} ({d} lines)")
    if missing:
        print("   missing:", ", ".join(missing[:30]))
