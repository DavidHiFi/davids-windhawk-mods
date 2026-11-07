"""Seamless Volume Mixer 1.3.1: click a compressor value to type it exactly.

Patches work/2026-11-07-volmixer-1.3.1/local@better-volume-mixer-plus.wh.cpp in place.
Fails loudly if any anchor is missing.
"""
import pathlib
import sys

path = pathlib.Path(sys.argv[1])
s = path.read_bytes().decode("utf-8")
nl = "\r\n" if "\r\n" in s else "\n"


def rep(old, new):
    global s
    old = old.replace("\n", nl)
    new = new.replace("\n", nl)
    if s.count(old) != 1:
        sys.exit(f"anchor count {s.count(old)}: {old[:80]!r}")
    s = s.replace(old, new)


rep("// @version      1.3.0", "// @version      1.3.1")
rep("""- exactVolumeEntry: false
  $name: Exact volume entry
  $description: Click a percentage to enter a whole number, 0 to 1000 for apps or 0 to 100 for master volume. Enter applies it; Escape or clicking elsewhere cancels. Off by default.""",
    """- exactVolumeEntry: true
  $name: Exact value entry
  $description: Click a number to type an exact value. Works for volume percentages (0 to 1000 for apps, 0 to 100 for master) and the compressor values (threshold -60 to 0 dB, ratio 1 to 20, attack 1 to 500 ms, release 10 to 2000 ms). Enter applies it; Escape or clicking elsewhere cancels. On by default.""")
rep("bool exactVolumeEntry = false;", "bool exactVolumeEntry = true;")
rep("int g_volumeEntryRow = DRAG_NONE;",
    "int g_volumeEntryRow = DRAG_NONE;\nint g_volumeEntryParam = -1;  // compressor value being typed, or -1 for volume")
rep("""RECT ParamSliderRect(int visibleRow, int clientWidth, int index) {""",
    """// The value text on the right of a compressor label; clicking it types a value.
RECT ParamValueRect(int visibleRow, int clientWidth, int index) {
    RECT label = ParamLabelRect(visibleRow, clientWidth, index);
    label.left = label.right - Scale(64);
    return label;
}

RECT ParamSliderRect(int visibleRow, int clientWidth, int index) {""")
rep("""bool FinishVolumeEntry(HWND owner, bool commit, bool returnFocus) {
    if (!g_volumeEntry) return true;
    if (commit) {
        WCHAR text[32]{};
        GetWindowTextW(g_volumeEdit, text, ARRAYSIZE(text));
        int percent;""",
    """// Accepts "40", "-40", "-40 dB", "2.5", "2.5:1", "150 ms". A positive threshold
// is read as negative, since the range is -60..0 dB.
bool ParseParamValue(const wchar_t* text, int index, float& value) {
    wchar_t* end = nullptr;
    float parsed = std::wcstof(text, &end);
    if (end == text || !std::isfinite(parsed)) return false;
    for (; *end; ++end) {
        if (!wcschr(L" \\tdDbBmMsS:1", *end)) return false;
    }
    if (index == 0 && parsed > 0.0f) parsed = -parsed;
    const ParamRange& range = kParamRanges[index];
    if (parsed < range.minimum || parsed > range.maximum) return false;
    value = parsed;
    return true;
}

bool FinishVolumeEntry(HWND owner, bool commit, bool returnFocus) {
    if (!g_volumeEntry) return true;
    if (commit && g_volumeEntryParam >= 0) {
        WCHAR text[32]{};
        GetWindowTextW(g_volumeEdit, text, ARRAYSIZE(text));
        float value;
        if (!RowHasBoostUi(g_volumeEntryRow) ||
            !ParseParamValue(text, g_volumeEntryParam, value)) {
            MessageBeep(MB_ICONWARNING);
            SendMessageW(g_volumeEdit, EM_SETSEL, 0, -1);
            return false;
        }
        const std::wstring exe = (*g_apps)[g_volumeEntryRow].exeKey;
        boost::Params p = BoostFor(exe);
        SetParamValue(p, g_volumeEntryParam, value);
        UpdateBoost(exe, p);
    } else if (commit) {
        WCHAR text[32]{};
        GetWindowTextW(g_volumeEdit, text, ARRAYSIZE(text));
        int percent;""")
rep("""    g_volumeEntryRow = DRAG_NONE;
    ++g_volumeEntryGeneration;
    DestroyWindow(entry);""",
    """    g_volumeEntryRow = DRAG_NONE;
    g_volumeEntryParam = -1;
    ++g_volumeEntryGeneration;
    DestroyWindow(entry);""")
rep("""void BeginVolumeEntry(HWND owner, int row) {
    if (!g_settings.exactVolumeEntry || g_dragRow != DRAG_NONE ||
        (row == DRAG_MASTER && !g_endpointVolume)) return;
    FinishVolumeEntry(owner, false, false);
    RECT client{};
    GetClientRect(owner, &client);
    RECT rect = PercentRectForRow(VisibleRowForDataRow(row), client.right);""",
    """void BeginVolumeEntry(HWND owner, int row, int param = -1) {
    if (!g_settings.exactVolumeEntry || g_dragRow != DRAG_NONE ||
        (row == DRAG_MASTER && !g_endpointVolume) ||
        (param >= 0 && !RowHasBoostUi(row))) return;
    FinishVolumeEntry(owner, false, false);
    RECT client{};
    GetClientRect(owner, &client);
    RECT rect = param >= 0
        ? ParamValueRect(VisibleRowForDataRow(row), client.right, param)
        : PercentRectForRow(VisibleRowForDataRow(row), client.right);
    if (param >= 0) InflateRect(&rect, 0, Scale(4));""")
rep("""    g_volumeEntryRow = row;
    ++g_volumeEntryGeneration;
    g_volumeEntry = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
        VOLUME_ENTRY_CLASS,
        RowMaxLevel(row) > 1.0f ? L"Volume (0-1000%)" : L"Volume (0-100%)",""",
    """    g_volumeEntryRow = row;
    g_volumeEntryParam = param;
    ++g_volumeEntryGeneration;
    g_volumeEntry = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
        VOLUME_ENTRY_CLASS,
        param >= 0 ? kParamNames[param]
                   : RowMaxLevel(row) > 1.0f ? L"Volume (0-1000%)" : L"Volume (0-100%)",""")
rep("""        WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER | ES_AUTOHSCROLL,""",
    """        WS_CHILD | WS_VISIBLE | ES_CENTER | ES_AUTOHSCROLL | (param >= 0 ? 0 : ES_NUMBER),""")
rep("""    std::wstring text = std::to_wstring(static_cast<int>(RowLevel(row) * 100.0f + 0.5f));
    SetWindowTextW(g_volumeEdit, text.c_str());""",
    """    std::wstring text;
    if (param >= 0) {
        float value = ParamValue(BoostFor((*g_apps)[row].exeKey), param);
        WCHAR buffer[16];
        if (param == 1) swprintf_s(buffer, L"%.1f", value);
        else swprintf_s(buffer, L"%d", static_cast<int>(std::lround(value)));
        text = buffer;
    } else {
        text = std::to_wstring(static_cast<int>(RowLevel(row) * 100.0f + 0.5f));
    }
    SetWindowTextW(g_volumeEdit, text.c_str());""")
rep("""                if (IsRowExpanded(row)) {
                    for (int i = 0; i < 4; ++i) {
                        RECT hit = ParamHitRect(visibleRow, client.right, i);""",
    """                if (IsRowExpanded(row)) {
                    for (int i = 0; g_settings.exactVolumeEntry && i < 4; ++i) {
                        RECT value = ParamValueRect(visibleRow, client.right, i);
                        if (PtInRect(&value, point)) {
                            BeginVolumeEntry(hWnd, row, i);
                            return 0;
                        }
                    }
                    for (int i = 0; i < 4; ++i) {
                        RECT hit = ParamHitRect(visibleRow, client.right, i);""")
path.write_bytes(s.encode("utf-8"))
print("patched", path)
