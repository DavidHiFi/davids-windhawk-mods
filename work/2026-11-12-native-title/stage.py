# Native title bar fix for every mod on the settings engine.
# Bug: "Title bar buttons = Windows buttons" (the default) also turned the native title bar on, so
# the settings window showed the Windows title bar while "Native Windows title bar" was off.
# Fix: the native title bar follows only its own switch. Off = the window's own title bar with its
# own buttons; on = Windows draws both. The "Title bar buttons" setting is dropped (its hybrid mode,
# Windows buttons on the custom title bar, drew dull buttons with no hover, see 2026-10-18 notes).
# Stages each live source to C:\Users\Public\native-title with the patch version bumped, compiles
# it offline and prints "STAGED <id> <version> <sha256 of live>".
import hashlib, re, subprocess, sys
from pathlib import Path

SRC = Path(r"C:\ProgramData\Windhawk\ModsSource")
OUT = Path(r"C:\Users\Public\native-title")
CLANG = r"C:\Program Files\Windhawk\Compiler\bin\clang++.exe"
INC = r"C:/Program Files/Windhawk/Compiler/include"
MODS = sys.argv[1:] or [
    "local@seamless-launchpad", "local@seamless-clipboard-manager", "local@seamless-dictate",
    "local@seamless-color-picker", "local@seamless-media-player", "local@seamless-key-click",
    "local@seamless-crash-watch", "local@seamless-autoclicker", "local@seamless-listary",
    "local@taskbar-ai-usage-plus"]

ENGINE = re.compile(
    r'w->nativeTitle = !render && \(?Wh_GetIntSetting\(L"((?:SettingsWindow\.)?nativeSettingsTitleBar)"\) != 0'
    r'(?: \|\|\n\s*GetStringSetting\(L"(?:SettingsWindow\.)?settingsTitleButtons"\) != L"builtin"\))?;\n'
    r'\s*w->nativeButtons = !render && !w->nativeTitle && GetStringSetting\(L"(?:SettingsWindow\.)?settingsTitleButtons"\) != L"builtin";')
YAML = re.compile(r'^( *)- settingsTitleButtons:.*\n(?:\1  .*\n)+', re.M)
ROW = re.compile(r'^[ \t]*\{K::Choice, L"(?:SettingsWindow\.)?settingsTitleButtons",.*\n', re.M)
KEYLIST = ' ||\n           wcscmp(key, L"settingsTitleButtons") == 0 || wcscmp(key, L"settingsTrayIcon") == 0;'

OUT.mkdir(exist_ok=True)
bad = 0
for mid in MODS:
    raw = (SRC / f"{mid}.wh.cpp").read_bytes()
    s = raw.decode("utf-8").replace("\r\n", "\n")
    s, n1 = ENGINE.subn(lambda m: (
        '// Off: the window draws its own title bar and buttons. On: Windows draws both.\n'
        f'    w->nativeTitle = !render && Wh_GetIntSetting(L"{m.group(1)}") != 0;'), s)
    s, n2 = YAML.subn("", s)
    s, n3 = ROW.subn("", s)
    s = s.replace(KEYLIST, ' ||\n           wcscmp(key, L"settingsTrayIcon") == 0;')
    left = s.count("settingsTitleButtons")
    if (n1, n2, n3, left) != (1, 1, 1, 0):
        print(f"SKIP {mid}: engine {n1}, yaml {n2}, row {n3}, left {left}"); bad += 1; continue
    m = re.search(r'(//\s*@version\s+)(\d+)\.(\d+)\.(\d+)', s)
    v = f"{m[2]}.{m[3]}.{int(m[4]) + 1}"
    s = s[:m.start()] + m[1] + v + s[m.end():]
    (OUT / f"{mid}.wh.cpp").write_text(s, encoding="utf-8", newline="\n")
    (OUT / f"{mid}.id.h").write_text(f'#define WH_MOD_ID L"{mid}"\n#define WH_MOD_VERSION L"{v}"\n', encoding="ascii")
    r = subprocess.run([CLANG, "-std=c++23", "-O1", "-target", "x86_64-w64-mingw32", "-DUNICODE", "-D_UNICODE",
                        "-DWINVER=0x0A00", "-D_WIN32_WINNT=0x0A00", "-DWH_MOD", "-c", "-include", str(OUT / f"{mid}.id.h"),
                        "-include", "windhawk_api.h", "-I", INC, "-x", "c++", str(OUT / f"{mid}.wh.cpp"),
                        "-o", str(OUT / f"{mid}.o")], capture_output=True, text=True, creationflags=0x08000000)
    if r.returncode:
        print(f"COMPILE FAIL {mid}:", "\n".join([l for l in r.stderr.splitlines() if " error" in l][:6])); bad += 1; continue
    print(f"STAGED {mid} {v} {hashlib.sha256(raw).hexdigest().upper()}")
sys.exit(1 if bad else 0)
