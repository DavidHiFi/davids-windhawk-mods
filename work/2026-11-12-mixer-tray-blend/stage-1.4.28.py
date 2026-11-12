import hashlib, pathlib
w = pathlib.Path(r"H:\Windhawk Configuration\work\2026-11-12-mixer-tray-blend")
live = pathlib.Path(r"C:\ProgramData\Windhawk\ModsSource\local@better-volume-mixer-plus.wh.cpp")
raw = live.read_bytes()
h = hashlib.sha256(raw).hexdigest().upper()
print("live is 1.4.27:", h == hashlib.sha256((w / "better-volume-mixer-plus-1.4.27.wh.cpp").read_bytes()).hexdigest().upper())
(w / "base-1.4.27.sha256").write_text(h)
s = raw.decode("utf-8")
nl = "\r\n"
def rep(old, new, count=1):
    global s
    n = s.count(old)
    print(f"{n}x {old[:50]!r}")
    assert n == count, n
    s = s.replace(old, new)
rep("// @version      1.4.27", "// @version      1.4.28")
rep('wcscpy_s(data.szTip, L"Seamless Volume Mixer");', "wcscpy_s(data.szTip, TrayTip());", 3)
rep("void AddTrayIcon(HWND hWnd) {", nl.join([
    "// Styler rules 64/65 widen the speaker's slot for the volume number by matching",
    "// this exact name. With the number off, a zero-width space at the end (the tooltip",
    "// reads the same) keeps the rules off the icon, so the slot is normal width.",
    "const wchar_t* TrayTip() {",
    '    return g_settings.trayVolumeNumber ? L"Seamless Volume Mixer"',
    '                                       : L"Seamless Volume Mixer\\u200B";',
    "}",
    "",
    "void AddTrayIcon(HWND hWnd) {"]))
rep("            LoadSettings();" + nl + "            SyncTrayNumberIcon(hWnd, true);", nl.join([
    "            {",
    "                bool hadNumber = g_settings.trayVolumeNumber;",
    "                LoadSettings();",
    "                // The slot's width follows the number: re-add the icon under its",
    "                // new name so the styler matches (or skips) a fresh element.",
    "                if (hadNumber != g_settings.trayVolumeNumber) {",
    "                    RemoveTrayIcon(hWnd);",
    "                    AddTrayIcon(hWnd);",
    "                }",
    "            }",
    "            SyncTrayNumberIcon(hWnd, true);"]))
(w / "better-volume-mixer-plus-1.4.28.wh.cpp").write_bytes(s.encode("utf-8"))
print("staged")
