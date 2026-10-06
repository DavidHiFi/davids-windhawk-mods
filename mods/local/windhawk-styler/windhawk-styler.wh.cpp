// ==WindhawkMod==
// @id              windhawk-styler
// @name            Windhawk Styler
// @description     Theme Windhawk itself with your own colors, font, transparency and blur
// @version         1.3.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @license         MIT
// @include         windhawk.exe
// @include         VSCodium.exe
// @compilerOptions -luser32 -lshell32 -ldwmapi -lbcrypt -lcomctl32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Windhawk Styler

Rice Windhawk like the rest of your desktop: pick its colors and font, and
give it a see-through, blurred background.

![Windhawk Styler preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/windhawk-styler.png)

## Features

- **Background.** Any color, with its own opacity. Text, cards and buttons
  stay solid and sharp.
- **Acrylic or blur.** Blur sits behind the background only, with rounded
  window corners, with or without the native title bar.
- **Element colors.** Separate colors for mod cards and pages, for buttons,
  inputs and menus, for the accent and for text.
- **Font.** Any installed font across the interface. Icons keep their own font.
- **Native title bar.** Use the real Windows title bar, with your own
  Windows theme and its window buttons. The window behaves like any
  other window, and the background keeps its transparency and blur.
- **Clean removal.** Disabling the mod restores every file it changed.

## How to use

Set the options in the Settings tab and save. Windhawk closes and reopens
its interface to apply background, font and title bar changes.

Colors use `#RRGGBB`. Leave an element color blank to keep Windhawk's own.

## Notes

The mod edits a few of Windhawk's interface files and keeps a backup beside
each. After a Windhawk update, reopen Windhawk to apply the styles again.
The mod editor's code area keeps its own font setting.
The native title bar draws the real Windows caption, and without it the
window controls come from the interface itself. Both modes keep the
see-through, blurred background. The window frame technique is adapted
from Titlebar For Everyone by Ingan121 (MIT).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- backgroundColor: "#1e1e2e"
  $name: Background color
  $description: Main background, in #RRGGBB format
- backgroundOpacity: 60
  $name: Background opacity
  $description: 0 to 100 percent. Only the background turns see-through, never text or cards
- blur: acrylic
  $name: Background blur
  $options:
  - acrylic: Acrylic
  - blur: Blur
  - none: None
- cardColor: "#181825"
  $name: Card color
  $description: Mod cards, mod pages and lists. Blank keeps Windhawk's color
- cardOpacity: 100
  $name: Card opacity
  $description: 0 to 100 percent
- controlColor: "#313244"
  $name: Control color
  $description: Buttons, inputs, menus and dialogs. Blank keeps Windhawk's color
- accentColor: "#89b4fa"
  $name: Accent color
  $description: Selected buttons, switches, tabs and links. Blank keeps Windhawk's color
- textColor: "#cdd6f4"
  $name: Text color
  $description: Blank keeps Windhawk's color
- fontFamily: "Segoe UI"
  $name: Font
  $description: An installed font name. Blank keeps Windhawk's font
- nativeTitleBar: false
  $name: Native title bar
  $description: Use the real Windows title bar and its window buttons, drawn by Windows itself
*/
// ==/WindhawkModSettings==

#include <windhawk_utils.h>
#include <windows.h>
#include <shellapi.h>
#include <dwmapi.h>
#include <bcrypt.h>
#include <tlhelp32.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <mutex>
#include <set>
#include <algorithm>

namespace fs = std::filesystem;
static bool g_tool;
static HANDLE g_stop, g_thread, g_mutex;
static fs::path g_root;
static std::mutex g_guard;
static std::set<HWND> g_windows;
static const std::string kBegin = "/* windhawk-styler begin */";
static const std::string kEnd = "/* windhawk-styler end */";

struct Style {
    DWORD background = 0x1e1e2e;
    int backgroundOpacity = 60, cardOpacity = 100;
    int blur = 2;  // 0 none, 1 blur, 2 acrylic
    std::string card, control, accent, text;  // "r,g,b" or empty
    DWORD textRgb = 0xcdd6f4, accentRgb = 0x89b4fa;
    bool hasText = false, nativeTitleBar = false;
    std::wstring font;
    bool Transparent() const { return backgroundOpacity < 100 || blur != 0; }
};
static Style g_style;

static std::string Read(const fs::path& p) {
    std::ifstream f(p, std::ios::binary);
    if (!f) throw std::runtime_error("Cannot read " + p.filename().string());
    return {std::istreambuf_iterator<char>(f), {}};
}
static void Write(const fs::path& p, const std::string& s) {
    std::ofstream f(p, std::ios::binary | std::ios::trunc);
    if (!f || !f.write(s.data(), s.size())) throw std::runtime_error("Cannot write " + p.filename().string());
}
static void Backup(const fs::path& p) {
    fs::path bak = p.wstring() + L".windhawk-styler.bak";
    if (!fs::exists(bak)) fs::copy_file(p, bak);
}
// Removes every marked block, including the HTML comment wrapper used in index.html.
static std::string Strip(std::string s) {
    for (size_t a; (a = s.find(kBegin)) != std::string::npos;) {
        auto b = s.find(kEnd, a);
        if (b == std::string::npos) throw std::runtime_error("Unterminated style marker");
        auto end = b + kEnd.size();
        if (a >= 4 && s.compare(a - 4, 4, "<!--") == 0 && s.compare(end, 3, "-->") == 0) {
            a -= 4; end += 3;
        }
        s.erase(a, end - a);
    }
    return s;
}
static bool Changes(const fs::path& p, const std::string& next) { return Read(p) != next; }
static void Store(const fs::path& p, const std::string& next) {
    if (!Changes(p, next)) return;
    Backup(p); Write(p, next);
}

static std::wstring Setting(PCWSTR name) {
    auto p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    Wh_FreeStringSetting(p);
    s.erase(0, s.find_first_not_of(L" \t"));
    s.erase(s.find_last_not_of(L" \t") + 1);
    return s;
}
static bool Hex(const std::wstring& s, DWORD& rgb) {
    if (s.size() != 7 || s[0] != L'#' ||
        !std::all_of(s.begin() + 1, s.end(), [](wchar_t c) { return iswxdigit(c); }))
        return false;
    rgb = std::stoul(s.substr(1), nullptr, 16);
    return true;
}
static std::string Rgb(DWORD c) {
    return std::to_string(c >> 16) + "," + std::to_string((c >> 8) & 255) + "," + std::to_string(c & 255);
}
static std::string Color(PCWSTR name, DWORD* out = nullptr) {
    DWORD c;
    if (!Hex(Setting(name), c)) return "";
    if (out) *out = c;
    return Rgb(c);
}
static void LoadStyle() {
    Style s;
    Hex(Setting(L"backgroundColor"), s.background);
    s.backgroundOpacity = std::clamp(Wh_GetIntSetting(L"backgroundOpacity"), 0, 100);
    s.cardOpacity = std::clamp(Wh_GetIntSetting(L"cardOpacity"), 0, 100);
    auto blur = Setting(L"blur");
    s.blur = blur == L"none" ? 0 : blur == L"blur" ? 1 : 2;
    s.card = Color(L"cardColor");
    s.control = Color(L"controlColor");
    s.accent = Color(L"accentColor", &s.accentRgb);
    s.text = Color(L"textColor", &s.textRgb);
    s.hasText = !s.text.empty();
    s.font = Setting(L"fontFamily");
    s.nativeTitleBar = Wh_GetIntSetting(L"nativeTitleBar") != 0;
    g_style = s;
}

static std::string Alpha(int percent) {
    char b[8]; sprintf_s(b, "%.2f", percent / 100.0); return b;
}
// Encodes every font character as a CSS escape so a setting cannot add CSS or HTML.
static std::string FontCss() {
    std::string escaped;
    for (wchar_t c : g_style.font) { char b[20]; sprintf_s(b, "\\%x ", unsigned(c)); escaped += b; }
    return "\"" + escaped + "\",sans-serif";
}
static std::string AppCss() {
    const auto& s = g_style;
    auto bg = "rgba(" + Rgb(s.background) + "," + Alpha(s.backgroundOpacity) + ")";
    std::string css =
        "html{background:" + bg + "!important}body{background:transparent!important;"
        "--app-background-color:" + bg + "!important}";
    if (!s.font.empty())
        css += "body,button,input,textarea,select,h1,h2,h3,h4,h5,.ant-typography,.ant-btn,.ant-input,"
               ".ant-card,.ant-select,.ant-select-dropdown,.ant-tabs,.ant-list,.ant-menu,.ant-dropdown,"
               ".ant-modal,.ant-tooltip,.ant-popover,.ant-radio-wrapper,.ant-checkbox-wrapper,.ant-alert,"
               ".ant-message,.ant-notification,.ant-empty,.ant-table,.ant-collapse,.ant-tag,.ant-badge"
               "{font-family:" + FontCss() + "!important}";
    if (!s.card.empty()) {
        auto card = "rgba(" + s.card + "," + Alpha(s.cardOpacity) + ")";
        css += ".ant-card,.ant-collapse,.ant-table,.ant-list-bordered{background-color:" + card + "!important}"
               ".ant-card-actions,.ant-collapse-content,.ant-table-thead>tr>th,.ant-table-tbody>tr>td,"
               ".ant-table-placeholder,[class*=SyntaxHighlighterWrapper] pre,[class*=DiffWrapper] pre"
               "{background:transparent!important}";
    }
    if (!s.control.empty()) {
        auto inline_ = "rgba(" + s.control + "," + Alpha(std::max(s.cardOpacity, 50)) + ")";
        auto solid = "rgb(" + s.control + ")";
        css += ".ant-btn:not(.ant-btn-primary):not(.ant-btn-link):not(.ant-btn-text):not(.ant-btn-background-ghost):not(:disabled):not(.ant-btn-disabled),"
               ".ant-input:not(:disabled),.ant-input-affix-wrapper:not(.ant-input-affix-wrapper-disabled),"
               ".ant-input-number:not(.ant-input-number-disabled),.ant-picker:not(.ant-picker-disabled),"
               ".ant-select:not(.ant-select-disabled):not(.ant-select-customize-input) .ant-select-selector,"
               ".ant-radio-button-wrapper:not(.ant-radio-button-wrapper-checked):not(.ant-radio-button-wrapper-disabled),"
               "[class*=CreateNewModButton__CreateButton]{background-color:" + inline_ + "!important}"
               ".ant-input-affix-wrapper .ant-input,.ant-input-number .ant-input-number-input"
               "{background:transparent!important}"
               ".ant-select-dropdown,.ant-dropdown-menu,.ant-modal-content,.ant-modal-header,"
               ".ant-popover-inner,.ant-popover-arrow-content,.ant-tooltip-inner,.ant-tooltip-arrow-content,"
               ".ant-message-notice-content,.ant-notification-notice,.ant-dropdown-menu-submenu-popup"
               "{background-color:" + solid + "!important}"
               ".ant-tooltip-arrow-content:before{background:" + solid + "!important}";
    }
    if (!s.accent.empty()) {
        auto a = "rgb(" + s.accent + ")";
        // Text on an accent fill must contrast with it, or light accents leave buttons unreadable.
        int luma = ((s.accentRgb >> 16 & 255) * 299 + (s.accentRgb >> 8 & 255) * 587 + (s.accentRgb & 255) * 114) / 1000;
        std::string onAccent = luma > 150 ? "rgb(30,30,46)" : "#ffffff";
        css += ".ant-btn-primary:not(.ant-btn-background-ghost):not(:disabled):not(.ant-btn-disabled),"
               ".ant-switch-checked,.ant-tabs-ink-bar,"
               ".ant-slider-track,.ant-progress-bg,.ant-spin-dot-item,.ant-badge-count,"
               ".ant-radio-button-wrapper-checked:not(.ant-radio-button-wrapper-disabled),"
               ".ant-checkbox-checked .ant-checkbox-inner,.ant-radio-inner:after"
               "{background-color:" + a + "!important;border-color:" + a + "!important}"
               ".ant-btn-primary:not(.ant-btn-background-ghost):not(:disabled):not(.ant-btn-disabled),"
               ".ant-radio-button-wrapper-checked:not(.ant-radio-button-wrapper-disabled),.ant-badge-count"
               "{color:" + onAccent + "!important}"
               ".ant-checkbox-checked .ant-checkbox-inner:after{border-color:" + onAccent + "!important}"
               ".ant-btn-primary:disabled,.ant-btn-primary.ant-btn-disabled,.ant-btn-primary[disabled]"
               "{background-color:rgba(120,122,140,.28)!important;color:rgba(230,232,245,.55)!important;"
               "border-color:transparent!important}"
               ".ant-btn-primary.ant-btn-background-ghost,.ant-btn:not(.ant-btn-primary):hover,"
               ".ant-btn:not(.ant-btn-primary):focus,.ant-pagination-item-active,.ant-radio-checked .ant-radio-inner,"
               ".ant-input:hover,.ant-input:focus,.ant-input-affix-wrapper:hover,.ant-input-affix-wrapper-focused,"
               ".ant-select:hover .ant-select-selector,.ant-select-focused .ant-select-selector"
               "{border-color:" + a + "!important}"
               "a,.ant-btn-link,.ant-btn-primary.ant-btn-background-ghost,.ant-btn:not(.ant-btn-primary):hover,"
               ".ant-btn:not(.ant-btn-primary):focus,.ant-tabs-tab.ant-tabs-tab-active .ant-tabs-tab-btn,"
               ".ant-tabs-tab:hover,.ant-pagination-item-active a,.ant-typography a"
               "{color:" + a + "!important}"
               ".ant-select-item-option-selected{background-color:rgba(" + s.accent + ",.22)!important}"
               ".ant-select-item-option-selected.ant-select-item-option-active"
               "{background-color:rgba(" + s.accent + ",.32)!important}"
               ".ant-btn-primary.ant-btn-background-ghost{background:transparent!important}";
    }
    if (s.hasText) {
        auto t = "rgb(" + s.text + ")", dim = "rgba(" + s.text + ",.68)";
        css += "body,h1,h2,h3,h4,h5,.ant-typography,.ant-card,.ant-card-head,.ant-card-head-title,"
               ".ant-card-meta-title,.ant-list-item,.ant-list-item-meta-title,.ant-modal-title,.ant-modal-content,"
               ".ant-collapse-header,.ant-tabs,.ant-tabs-tab-btn,.ant-select,.ant-select-item,.ant-dropdown-menu-item,"
               ".ant-input,.ant-input-number-input,.ant-radio-button-wrapper,.ant-radio-wrapper,.ant-checkbox-wrapper,"
               ".ant-btn:not(.ant-btn-primary):not(.ant-btn-link):not(.ant-btn-background-ghost),.ant-descriptions,"
               ".ant-form-item-label>label,.ant-empty-description{color:" + t + "}"
               ".ant-typography-secondary,.ant-card-meta-description,.ant-list-item-meta-description,"
               "[class*=ModCard] .ant-card-body,.ant-input::placeholder{color:" + dim + "!important}"
               ".ant-select-item-option-selected{color:" + t + "!important}";
    }
    return css;
}
static std::string WorkbenchCss() {
    const auto& s = g_style;
    auto bg = "rgba(" + Rgb(s.background) + "," + Alpha(s.backgroundOpacity) + ")";
    std::string css =
        "html,body,.monaco-workbench,.monaco-workbench .part,.monaco-workbench .part>.content,"
        ".monaco-workbench .split-view-view,.monaco-workbench .monaco-grid-view,"
        ".monaco-workbench .editor-group-container,.monaco-workbench .editor-container,"
        ".monaco-workbench .webview{background:transparent!important}"
        ".monaco-workbench .part.titlebar,.monaco-workbench .monaco-editor,"
        ".monaco-workbench .monaco-editor-background,.monaco-workbench .monaco-editor .margin"
        "{background-color:" + bg + "!important}";
    if (s.hasText)
        css += ".monaco-workbench .part.titlebar,.monaco-workbench .part.titlebar .window-icon"
               "{color:rgb(" + s.text + ")!important}";
    if (!s.font.empty())
        css += ".monaco-workbench .part.titlebar .window-title,.monaco-workbench .part.titlebar .menubar"
               "{font-family:" + FontCss() + "!important}";
    return kBegin + css + kEnd;
}

// VSCodium checks its workbench files against product.json and warns when they differ.
static std::string Md5Base64(const std::string& data) {
    BCRYPT_ALG_HANDLE alg; UCHAR hash[16]; std::string r;
    if (BCryptOpenAlgorithmProvider(&alg, BCRYPT_MD5_ALGORITHM, nullptr, 0)) return r;
    BCryptHash(alg, nullptr, 0, (PUCHAR)data.data(), ULONG(data.size()), hash, 16);
    BCryptCloseAlgorithmProvider(alg, 0);
    static const char* b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    for (int i = 0; i < 16; i += 3) {
        unsigned v = hash[i] << 16 | (i + 1 < 16 ? hash[i + 1] << 8 : 0) | (i + 2 < 16 ? hash[i + 2] : 0);
        for (int j = 0; j < 4 && i * 8 / 6 + j < 22; ++j) r += b64[(v >> (18 - 6 * j)) & 63];
    }
    return r;
}
static std::string Checksums(std::string product, const std::string& css) {
    const std::string key = "\"vs/workbench/workbench.desktop.main.css\": \"";
    auto a = product.find(key);
    if (a == std::string::npos) return product;
    a += key.size();
    auto b = product.find('"', a);
    auto sum = Md5Base64(css);
    if (b != std::string::npos && !sum.empty()) product.replace(a, b - a, sum);
    return product;
}

// Makes the main window transparent and stops VSCodium painting its theme color behind the page.
static std::string MainJs(const std::string& clean) {
    if (!g_style.Transparent()) return clean;
    auto word = [](char c) { return isalnum((unsigned char)c) || c == '_' || c == '$'; };
    std::string out = clean;
    // The main window is the only one created from an options variable: new X.BrowserWindow(name)
    size_t at = std::string::npos;
    for (size_t p = 0; (p = out.find(".BrowserWindow(", p)) != std::string::npos; p += 15) {
        size_t a = p + 15, b = a;
        while (b < out.size() && word(out[b])) ++b;
        if (b > a && b < out.size() && out[b] == ')' && p >= 5 && out.rfind("new ", p) != std::string::npos &&
            out.rfind("new ", p) + 4 < p && std::all_of(out.begin() + out.rfind("new ", p) + 4, out.begin() + p, word)) {
            if (at != std::string::npos) throw std::runtime_error("Window options are ambiguous");
            at = a;
        }
    }
    if (at == std::string::npos) throw std::runtime_error("Window options not found");
    auto opts = out.substr(at, out.find(')', at) - at);
    std::string inject = "transparent:!0,backgroundColor:\"#00000000\"";
    if (g_style.nativeTitleBar) inject += ",frame:!1";
    out.insert(at, kBegin + "Object.assign(" + opts + ",{" + inject + "})&&" + kEnd);
    auto p = out.find("updateBackgroundColor(");
    while (p != std::string::npos) {
        auto brace = out.find(')', p);
        if (brace != std::string::npos && brace + 1 < out.size() && out[brace + 1] == '{' && brace - p < 40) {
            out.insert(brace + 2, kBegin + "return;" + kEnd);
            break;
        }
        p = out.find("updateBackgroundColor(", p + 1);
    }
    return out;
}
static std::string SettingsJson(const std::string& clean) {
    std::string keys;
    if (g_style.nativeTitleBar) keys = "\"window.titleBarStyle\":\"native\",\"window.menuBarVisibility\":\"hidden\"";
    else keys = "\"window.titleBarStyle\":\"custom\",\"window.experimental.windowControlsOverlay.enabled\":false";
    if (keys.empty()) return clean;
    auto close = clean.rfind('}');
    if (close == std::string::npos) throw std::runtime_error("Unexpected settings file");
    auto last = clean.find_last_not_of(" \t\r\n", close - 1);
    bool comma = last != std::string::npos && clean[last] != '{' && clean[last] != ',';
    auto at = last == std::string::npos ? close : last + 1;
    return clean.substr(0, at) + kBegin + (comma ? "," : "") + keys + kEnd + clean.substr(at);
}

static bool OurProcess(DWORD pid) {
    HANDLE p = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!p) return false;
    WCHAR path[MAX_PATH * 4]; DWORD n = ARRAYSIZE(path);
    bool ours = QueryFullProcessImageNameW(p, 0, path, &n) &&
        _wcsicmp(path, (g_root / L"UI" / L"VSCodium.exe").c_str()) == 0;
    CloseHandle(p);
    return ours;
}
static bool MainWindow(HWND h) {
    WCHAR cls[64];
    if (!GetClassNameW(h, cls, 64) || wcscmp(cls, L"Chrome_WidgetWin_1") || !IsWindowVisible(h) ||
        GetWindow(h, GW_OWNER) || !(GetWindowLongPtrW(h, GWL_STYLE) & WS_MINIMIZEBOX))
        return false;
    DWORD pid; GetWindowThreadProcessId(h, &pid);
    return OurProcess(pid);
}
static std::set<DWORD> UiProcesses() {
    std::set<DWORD> r;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W e{sizeof(e)};
    for (BOOL ok = Process32FirstW(snap, &e); ok; ok = Process32NextW(snap, &e))
        if (!_wcsicmp(e.szExeFile, L"VSCodium.exe") && OurProcess(e.th32ProcessID)) r.insert(e.th32ProcessID);
    CloseHandle(snap);
    return r;
}
// The interface process can outlive its window, so make sure all of it exits.
static BOOL CALLBACK CloseWindow(HWND h, LPARAM) {
    if (MainWindow(h)) PostMessageW(h, WM_CLOSE, 0, 0);
    return TRUE;
}
static void StopUi() {
    EnumWindows(CloseWindow, 0);
    for (int i = 0; i < 40 && !UiProcesses().empty(); ++i) Sleep(100);
    for (DWORD pid : UiProcesses())
        if (HANDLE p = OpenProcess(PROCESS_TERMINATE | SYNCHRONIZE, FALSE, pid)) {
            TerminateProcess(p, 0); WaitForSingleObject(p, 3000); CloseHandle(p);
        }
}
static void StartUi() {
    auto exe = g_root / L"windhawk.exe";
    SHELLEXECUTEINFOW s{sizeof(s)}; s.fMask = SEE_MASK_FLAG_NO_UI;
    s.lpFile = exe.c_str(); s.nShow = SW_SHOWNORMAL;
    if (!ShellExecuteExW(&s)) Wh_Log(L"Reopen failed: %u", GetLastError());
}

static void ApplyFiles(bool remove = false) {
    auto app = g_root / L"UI/resources/app";
    auto html = app / L"extensions/windhawk/webview/index.html";
    auto ext = app / L"extensions/windhawk/dist/extension.js";
    auto workbench = app / L"out/vs/workbench/workbench.desktop.main.css";
    auto product = app / L"product.json";
    auto main = app / L"out/vs/code/electron-main/main.js";
    WCHAR data[MAX_PATH];
    fs::path settings = GetEnvironmentVariableW(L"ProgramData", data, MAX_PATH) ? fs::path(data) : fs::path(L"C:\\ProgramData");
    settings /= L"Windhawk/UIData/user-data/User/settings.json";

    auto cleanMain = Strip(Read(main));
    auto nextMain = remove ? cleanMain : MainJs(cleanMain);
    std::string nextSettings;
    bool hasSettings = fs::exists(settings);
    if (hasSettings) {
        auto clean = Strip(Read(settings));
        nextSettings = remove ? clean : SettingsJson(clean);
    }
    // Window-level changes only apply to a freshly started interface.
    auto cleanCss = Strip(Read(workbench));
    auto nextCss = remove ? cleanCss : cleanCss + WorkbenchCss();
    bool restart = Changes(main, nextMain) || Changes(workbench, nextCss) || (hasSettings && Changes(settings, nextSettings));
    bool running = restart && !UiProcesses().empty();
    if (running) StopUi();
    Store(main, nextMain);
    if (hasSettings) Store(settings, nextSettings);

    Store(workbench, nextCss);
    Store(product, Checksums(Read(product), nextCss));
    auto cleanHtml = Strip(Read(html));
    Store(html, remove ? cleanHtml : cleanHtml + "<!--" + kBegin + "--><style>" + AppCss() + "</style><!--" + kEnd + "-->");
    // Refresh the page when its styles change and reload the window when the frame styles change.
    const std::string watcher = R"JS(
;(()=>{const fs=require('fs'),path=require('path'),v=require('vscode');
const watch=(file,run)=>{let t;fs.watchFile(file,{interval:500,persistent:false},(a,b)=>{
if(a.mtimeMs===b.mtimeMs)return;clearTimeout(t);t=setTimeout(run,700);});};
let reloading=false;
watch(path.join(__dirname,'../../../out/vs/workbench/workbench.desktop.main.css'),()=>{
reloading=true;v.commands.executeCommand('workbench.action.reloadWindow');});
watch(path.join(__dirname,'../webview/index.html'),()=>{setTimeout(()=>{
if(!reloading&&!v.workspace.getConfiguration('windhawk').get('editedModId'))
v.commands.executeCommand('windhawk.start');},400);});})();
)JS";
    auto cleanExt = Strip(Read(ext));
    Store(ext, remove ? cleanExt : cleanExt + kBegin + watcher + kEnd);
    if (running) StartUi();
}

struct Accent { int state, flags; DWORD color; int animation; };
struct Composition { int attribute; void* data; SIZE_T size; };
static void Effect(HWND h, bool reset) {
    static auto proc = reinterpret_cast<BOOL(WINAPI*)(HWND, Composition*)>(
        GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute"));
    const auto& s = g_style;
    bool clear = reset || !s.Transparent();
    DWORD c = s.background;
    DWORD bgr = (c & 255) << 16 | (c & 0xff00) | c >> 16;
    // The page paints the color; the tint stays light so the blur keeps its depth.
    Accent accent{clear || !s.blur ? 0 : s.blur == 2 ? 4 : 3, 2, 0x10000000 | bgr, 0};
    Composition data{19, &accent, sizeof(accent)};
    if (proc && !proc(h, &data)) Wh_Log(L"Backdrop update failed: %u", GetLastError());
    // The composition accent draws nothing behind Chromium's own composition
    // surface, so the real backdrop comes from the DWM system backdrop: a
    // proper acrylic material which shows through the page's transparent
    // pixels. Kept alongside the accent, which still serves layered windows.
    int backdrop = clear || !s.blur ? 1 /* DWMSBT_NONE */ : 3 /* DWMSBT_TRANSIENTWINDOW */;
    DwmSetWindowAttribute(h, 38, &backdrop, sizeof(backdrop));  // DWMWA_SYSTEMBACKDROP_TYPE
    DWORD corner = clear ? 0 : 2;  // DWMWCP_DEFAULT or DWMWCP_ROUND
    DwmSetWindowAttribute(h, 33, &corner, sizeof(corner));
    BOOL dark = TRUE;
    DwmSetWindowAttribute(h, 20, &dark, sizeof(dark));
    // With the native title bar the caption strip is drawn by DWM over the
    // same backdrop the page shows through; asking for no caption color keeps
    // the strip as see-through as the body. A solid color would sit opaque.
    DWORD caption = reset                            ? 0xFFFFFFFF
                    : (s.nativeTitleBar && s.blur)   ? 0xFFFFFFFE /* DWMWA_COLOR_NONE */
                                                     : bgr,
            text = reset || !s.hasText ? 0xFFFFFFFF :
        ((s.textRgb & 255) << 16 | (s.textRgb & 0xff00) | s.textRgb >> 16);
    DwmSetWindowAttribute(h, 35, &caption, sizeof(caption));  // DWMWA_CAPTION_COLOR
    DwmSetWindowAttribute(h, 36, &text, sizeof(text));        // DWMWA_TEXT_COLOR
}
static BOOL CALLBACK Track(HWND h, LPARAM) {
    if (!g_windows.contains(h) && MainWindow(h)) { g_windows.insert(h); Effect(h, false); }
    return TRUE;
}
static void CALLBACK Shown(HWINEVENTHOOK, DWORD, HWND h, LONG object, LONG, DWORD, DWORD) {
    if (object != OBJID_WINDOW) return;
    std::lock_guard lock(g_guard);
    Track(h, 0);
}
static DWORD WINAPI Worker(void*) {
    auto hook = SetWinEventHook(EVENT_OBJECT_SHOW, EVENT_OBJECT_SHOW, nullptr, Shown, 0, 0, WINEVENT_OUTOFCONTEXT);
    int tick = 0;
    while (MsgWaitForMultipleObjects(1, &g_stop, FALSE, 1000, QS_ALLINPUT) != WAIT_OBJECT_0) {
        MSG msg; while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) DispatchMessageW(&msg);
        std::lock_guard lock(g_guard);
        std::erase_if(g_windows, [](HWND h) { return !IsWindow(h); });
        EnumWindows(Track, 0);
        // Keep the backdrop in place: the frame can reset it when the window
        // state changes. Both title bar modes need this; the system backdrop
        // and the caption color drop on the same state changes.
        if (++tick % 5 == 0)
            for (HWND h : g_windows) Effect(h, false);
    }
    if (hook) UnhookWinEvent(hook);
    return 0;
}

// The native title bar is the real Windows frame. The interface window is created
// without a frame so the background stays see-through, then the frame is applied
// from inside the interface process. Non-client messages are handed to
// DefWindowProc, so Windows draws its own caption using the current system theme.
// Technique adapted from Titlebar For Everyone by Ingan121 (MIT).
static bool g_uiProcess, g_nativeBar, g_hookInstalled;
static LRESULT CALLBACK CaptionProc(HWND h, UINT msg, WPARAM w, LPARAM l, DWORD_PTR);
using ShowWindow_t = decltype(&ShowWindow);
static ShowWindow_t ShowWindow_orig;
using ShowWindowAsync_t = decltype(&ShowWindowAsync);
static ShowWindowAsync_t ShowWindowAsync_orig;

static bool CaptionTarget(HWND h);

// The OS maximize state draws the frame without DWM's themed caption on this
// transparent window, so it falls back to the classic drawing. Instead the
// window is fitted to the work area like Chromium's own frameless maximize,
// which keeps the themed caption with its window buttons in place.
static const UINT WM_STYLER_FIT = WM_APP + 0x51;
static HWND g_fit;
static RECT g_fitBack;
static bool g_fitActive;

static RECT WorkArea(HWND h) {
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromWindow(h, MONITOR_DEFAULTTONEAREST), &mi);
    return mi.rcWork;
}
static void FitApply(HWND h) {
    RECT w = WorkArea(h);
    SetWindowPos(h, nullptr, w.left, w.top, w.right - w.left, w.bottom - w.top,
        SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
}
static void FitStart(HWND h) {
    if (g_fitActive && g_fit == h) return;
    if (!g_fitActive) GetWindowRect(h, &g_fitBack);
    g_fit = h;
    g_fitActive = true;
    FitApply(h);
}
static void FitEnd(HWND h) {
    if (!g_fitActive || g_fit != h) return;
    g_fitActive = false;
    if (IsWindow(h))
        SetWindowPos(h, nullptr, g_fitBack.left, g_fitBack.top,
            g_fitBack.right - g_fitBack.left, g_fitBack.bottom - g_fitBack.top,
            SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
}
// Called after the OS maximized the window by other means: keep the fit instead.
static void FitFromZoom(HWND h) {
    if (g_fitActive && g_fit == h) return;
    WINDOWPLACEMENT wp{sizeof(wp)};
    if (GetWindowPlacement(h, &wp)) {
        g_fitBack = wp.rcNormalPosition;
        // Placement is in workspace coordinates; the workspace origin is the
        // primary monitor's work area corner.
        POINT zero{0, 0};
        MONITORINFO mi{sizeof(mi)};
        if (GetMonitorInfoW(MonitorFromPoint(zero, MONITOR_DEFAULTTOPRIMARY), &mi)) {
            g_fitBack.left += mi.rcWork.left;   g_fitBack.right += mi.rcWork.left;
            g_fitBack.top += mi.rcWork.top;     g_fitBack.bottom += mi.rcWork.top;
        }
    } else {
        GetWindowRect(h, &g_fitBack);
    }
    g_fit = h;
    g_fitActive = true;
    ShowWindow_orig(h, SW_RESTORE);
    FitApply(h);
}
static bool FitIntercept(HWND h, int cmd) {
    if (!g_nativeBar || !CaptionTarget(h)) return false;
    if (cmd == SW_MAXIMIZE) {
        if (g_fitActive && g_fit == h) FitEnd(h); else FitStart(h);
        return true;
    }
    if (cmd == SW_RESTORE && g_fitActive && g_fit == h) {
        if (IsIconic(h)) {
            ShowWindow_orig(h, SW_RESTORE);
            FitApply(h);
        } else {
            FitEnd(h);
        }
        return true;
    }
    return false;
}

static bool CaptionTarget(HWND h) {
    if (!h || !IsWindow(h) || GetAncestor(h, GA_ROOT) != h) return false;
    if (GetWindowLongPtrW(h, GWL_EXSTYLE) & WS_EX_TOOLWINDOW) return false;
    WCHAR cls[64];
    if (!GetClassNameW(h, cls, 64)) return false;
    return wcsncmp(cls, L"Chrome_WidgetWin_", 17) == 0;
}
// Keep DWM drawing its own themed caption. The policy resets on window state
// changes, and then the unused frame falls back to the classic drawing.
static void CaptionStyle(HWND h) {
    DWORD policy = 2;  // DWMNCRP_ENABLED: let DWM draw its own themed caption
    DwmSetWindowAttribute(h, 2, &policy, sizeof(policy));
}
static void CaptionApply(HWND h) {
    WindhawkUtils::SetWindowSubclassFromAnyThread(h, CaptionProc, 0);
    CaptionStyle(h);
    LONG style = GetWindowLongW(h, GWL_STYLE);
    if ((style & (WS_CAPTION | WS_THICKFRAME)) != (WS_CAPTION | WS_THICKFRAME)) {
        SetWindowLongW(h, GWL_STYLE, style | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME);
        SetWindowPos(h, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE |
            SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
}
static void CaptionRemove(HWND h) {
    WindhawkUtils::RemoveWindowSubclassFromAnyThread(h, CaptionProc);
    DWORD policy = 0;  // DWMNCRP_USEWINDOWSTYLE
    DwmSetWindowAttribute(h, 2, &policy, sizeof(policy));
    LONG style = GetWindowLongW(h, GWL_STYLE);
    if (style & (WS_CAPTION | WS_THICKFRAME)) {
        SetWindowLongW(h, GWL_STYLE, style & ~(WS_CAPTION | WS_SYSMENU | WS_THICKFRAME));
        SetWindowPos(h, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE |
            SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
}
static BOOL CALLBACK CaptionEnum(HWND h, LPARAM apply) {
    if (CaptionTarget(h)) { if (apply) CaptionApply(h); else CaptionRemove(h); }
    return TRUE;
}
static LRESULT CALLBACK CaptionProc(HWND h, UINT msg, WPARAM w, LPARAM l, DWORD_PTR) {
    switch (msg) {
        case WM_NCCALCSIZE:
            // Chromium's page surface stops a caption short of the client rect, so
            // extend the client into the bottom frame by the same amount. The page
            // then covers the window and the unpainted strip at the bottom is gone.
            if (w) {
                auto params = reinterpret_cast<NCCALCSIZE_PARAMS*>(l);
                LONG windowTop = params->rgrc[0].top;
                LRESULT r = DefWindowProcW(h, msg, w, l);
                params->rgrc[0].bottom += params->rgrc[0].top - windowTop;
                return r;
            }
            return DefWindowProcW(h, msg, w, l);
        case WM_NCACTIVATE:
            return DefWindowProcW(h, msg, w, l);
        case WM_NCHITTEST: {
            LRESULT r = DefWindowProcW(h, msg, w, l);
            // The client extends into the bottom frame, so restore the resize grip
            // DefWindowProc no longer reports there.
            if (r == HTCLIENT) {
                POINT pt{(short)LOWORD(l), (short)HIWORD(l)};
                RECT wr; GetWindowRect(h, &wr);
                int frame = GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER);
                if (pt.x >= wr.left && pt.x < wr.right && pt.y >= wr.bottom - frame && pt.y < wr.bottom)
                    return HTBOTTOM;
            }
            return r;
        }
        case WM_NCLBUTTONDOWN:
            return DefWindowProcW(h, msg, w, l);
        case WM_SYSCOMMAND:
            // Chromium swallows the default window commands, which makes the caption
            // buttons dead. Run the window actions the buttons send directly.
            switch (w & 0xFFF0) {
                case SC_MAXIMIZE: ShowWindow(h, SW_MAXIMIZE); return 0;
                case SC_RESTORE: ShowWindow(h, SW_RESTORE); return 0;
                case SC_MINIMIZE: ShowWindow(h, SW_MINIMIZE); return 0;
            }
            break;
        case WM_NCPAINT: {
            // With DWM on, never paint the classic caption here: the frame belongs
            // to DWM, and the classic drawing is what shows up as the legacy frame.
            BOOL dwm = FALSE;
            DwmIsCompositionEnabled(&dwm);
            if (dwm) return DefSubclassProc(h, msg, w, l);
            return DefWindowProcW(h, msg, w, l);
        }
        case WM_DWMNCRENDERINGCHANGED: {
            // State changes reset the NC rendering policy; without this the caption
            // falls back to the classic drawing when the window is maximized.
            CaptionStyle(h);
            RECT rect; GetWindowRect(h, &rect);
            SetWindowPos(h, nullptr, rect.left, rect.top + 1, 0, 0,
                SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
            SetWindowPos(h, nullptr, rect.left, rect.top, 0, 0,
                SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
            break;
        }
        case WM_SIZE:
        case WM_WINDOWPOSCHANGED: {
            // Chromium re-disables DWM frame rendering while it handles window state
            // changes, so the policy has to be re-asserted after its handler runs.
            LRESULT r = DefSubclassProc(h, msg, w, l);
            CaptionStyle(h);
            // A real OS maximize hides the themed caption; turn it into the fit.
            if (IsZoomed(h) && !(g_fitActive && g_fit == h)) PostMessageW(h, WM_STYLER_FIT, 0, 0);
            return r;
        }
        case WM_STYLER_FIT:
            if (g_nativeBar && IsZoomed(h)) FitFromZoom(h);
            return 0;
    }
    return DefSubclassProc(h, msg, w, l);
}
static BOOL WINAPI ShowWindow_hook(HWND h, int cmd) {
    if (FitIntercept(h, cmd)) return TRUE;
    BOOL r = ShowWindow_orig(h, cmd);
    if (g_nativeBar && CaptionTarget(h)) {
        CaptionApply(h);
        // A state change drops the backdrop and the caption color; put them
        // back at once rather than waiting for the tool's periodic pass.
        Effect(h, false);
    }
    return r;
}
static BOOL WINAPI ShowWindowAsync_hook(HWND h, int cmd) {
    if (FitIntercept(h, cmd)) return TRUE;
    BOOL r = ShowWindowAsync_orig(h, cmd);
    if (g_nativeBar && CaptionTarget(h)) {
        CaptionApply(h);
        Effect(h, false);
    }
    return r;
}
static void InstallHooks() {
    WindhawkUtils::SetFunctionHook(ShowWindow, ShowWindow_hook, &ShowWindow_orig);
    WindhawkUtils::SetFunctionHook(ShowWindowAsync, ShowWindowAsync_hook, &ShowWindowAsync_orig);
    g_hookInstalled = true;
}
static void UiTitlebarInit() {
    g_uiProcess = true;
    g_nativeBar = Wh_GetIntSetting(L"nativeTitleBar") != 0;
    LoadStyle();  // the hooks below reapply the backdrop with the real style
    if (!g_nativeBar) return;
    EnumWindows(CaptionEnum, TRUE);
    InstallHooks();
}
static void UiTitlebarUninit() {
    if (g_fitActive && IsWindow(g_fit)) { FitEnd(g_fit); }
    EnumWindows(CaptionEnum, FALSE);
    g_uiProcess = false;
}
static void UiTitlebarSettings() {
    bool want = Wh_GetIntSetting(L"nativeTitleBar") != 0;
    if (want == g_nativeBar) return;
    g_nativeBar = want;
    if (want && !g_hookInstalled) InstallHooks();
    if (!want && g_fitActive) FitEnd(g_fit);
    EnumWindows(CaptionEnum, want ? TRUE : FALSE);
}

static void WINAPI Entry() { ExitThread(0); }
BOOL Wh_ModInit() {
    DWORD session; if (!ProcessIdToSessionId(GetCurrentProcessId(), &session) || session == 0) return FALSE;
    int argc; auto argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!argv) return FALSE;
    bool excluded = false, subprocess = false;
    for (int i = 1; i < argc; ++i) {
        if (!wcscmp(argv[i], L"-service")) excluded = true;
        if (!wcsncmp(argv[i], L"--type=", 7)) subprocess = true;
        if (!wcscmp(argv[i], L"-tool-mod")) {
            g_tool = i + 1 < argc && !wcscmp(argv[i + 1], WH_MOD_ID);
            if (!g_tool) excluded = true;
        }
    }
    LocalFree(argv); if (excluded) return FALSE;
    WCHAR exe[MAX_PATH]; GetModuleFileNameW(nullptr, exe, MAX_PATH); g_root = fs::path(exe).parent_path();
    if (_wcsicmp(fs::path(exe).filename().c_str(), L"VSCodium.exe") == 0) {
        if (!subprocess) UiTitlebarInit();
        return TRUE;
    }
    if (!g_tool) return TRUE;
    g_mutex = CreateMutexW(nullptr, FALSE, L"windhawk-tool-mod_" WH_MOD_ID);
    if (!g_mutex || GetLastError() == ERROR_ALREADY_EXISTS) return FALSE;
    LoadStyle();
    try { ApplyFiles(); } catch (const std::exception& e) { Wh_Log(L"Style setup failed: %S", e.what()); return FALSE; }
    g_stop = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_thread = CreateThread(nullptr, 0, Worker, nullptr, 0, nullptr);
    if (!g_stop || !g_thread) return FALSE;
    auto base = reinterpret_cast<BYTE*>(GetModuleHandleW(nullptr));
    auto dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
    return Wh_SetFunctionHook(base + nt->OptionalHeader.AddressOfEntryPoint, reinterpret_cast<void*>(Entry), nullptr);
}
void Wh_ModAfterInit() {
    if (g_tool) return;
    auto exe = g_root / L"windhawk.exe";
    SHELLEXECUTEINFOW s{sizeof(s)}; s.fMask = SEE_MASK_FLAG_NO_UI;
    s.lpVerb = L"runas"; s.lpFile = exe.c_str(); s.lpParameters = L"-tool-mod \"" WH_MOD_ID L"\""; s.nShow = SW_HIDE;
    if (!ShellExecuteExW(&s)) Wh_Log(L"Tool launch failed: %u", GetLastError());
}
void Wh_ModSettingsChanged() {
    if (g_uiProcess) {
        LoadStyle();  // keep the hook-side backdrop reapplication current
        UiTitlebarSettings();
        return;
    }
    if (!g_tool) return;
    std::lock_guard lock(g_guard);
    LoadStyle();
    try { ApplyFiles(); } catch (const std::exception& e) { Wh_Log(L"Style update failed: %S", e.what()); }
    std::erase_if(g_windows, [](HWND h) { return !IsWindow(h); });
    for (HWND h : g_windows) Effect(h, false);
}
void Wh_ModUninit() {
    if (g_uiProcess) { UiTitlebarUninit(); return; }
    if (!g_tool) return;
    SetEvent(g_stop); WaitForSingleObject(g_thread, INFINITE);
    for (HWND h : g_windows) if (IsWindow(h)) Effect(h, true);
    try { ApplyFiles(true); } catch (const std::exception& e) { Wh_Log(L"Style cleanup failed: %S", e.what()); }
    CloseHandle(g_thread); CloseHandle(g_stop); CloseHandle(g_mutex);
    ExitProcess(0);
}
