// ==WindhawkMod==
// @id              shell-font-changer-plus
// @name            Shell Font Changer Plus
// @description     Any installed font in File Explorer, Start, Search, Settings and the shell, with icons and emoji left intact
// @version         2.0.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @license         MIT
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         explorer.exe
// @include         StartMenuExperienceHost.exe
// @include         SearchHost.exe
// @include         ShellExperienceHost.exe
// @include         ShellHost.exe
// @include         TextInputHost.exe
// @include         SystemSettings.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -luser32 -luxtheme
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Shell Font Changer Plus

Change the text font in File Explorer, Start, Search, Settings and the rest of
the shell to any font you have installed. Icons and emoji keep their own
glyphs, so buttons never turn into empty boxes.

![Shell Font Changer Plus preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/shell-font-changer-plus.png)

## Features

- **The whole shell.** File Explorer, the desktop, the taskbar, Start and
  Search, Quick Settings and the notification center, Windows Settings and the
  touch keyboard.
- **Classic and modern text.** Classic Windows controls, themed controls and
  modern (XAML) text are all covered.
- **Pick the weight.** Medium is the default. Bold text stays bold unless you
  ask for one weight everywhere.
- **Icons and emoji stay intact.** Symbol, icon and emoji fonts keep their own
  glyphs, and so does text the new font has no letters for.
- **Text fits its controls.** In File Explorer, text that would overflow
  shrinks a little, to no less than 85% of its height or 80% of its width. If
  it still overflows, the original UI font draws it.
- **You choose which fonts change.** The usual Windows UI fonts change by
  default. Add more, change every eligible font, or keep some as they are.
- **Clean to remove.** The mod changes fonts in memory only and writes nothing
  to the registry, so turning it off leaves nothing behind.

## How to use

Type an installed font family name in the settings, such as
`FiraCode Nerd Font` or `Inter`, the way Settings shows it under
Personalization > Fonts. Leave it empty, or type `None`, to keep the original
fonts.

If the font is not installed, the mod stays loaded and changes nothing. The
Windhawk log says why. Install the font, then change any setting to try again.

Apps pick up the new font the next time they create or lay out text. Restart
an app, or sign out and back in for Start and the shell, if some text keeps the
old font.

## Fonts to replace

The default list covers the usual Windows UI fonts (Segoe UI and its variants,
Tahoma, MS Shell Dlg and the Japanese UI faces). Add families under **Also
replace these fonts**, or turn on **Replace every eligible font** to include
document fonts such as Arial and Calibri. Turn on **Include monospace fonts**
for fonts such as Consolas. **Keep these fonts** always wins.

Fonts made for one writing system (Chinese, Japanese, Korean, Arabic, Hebrew,
Indic and others) are never replaced, so their text keeps rendering.

## More apps

To try another app, add its program name under this mod's **Advanced >
Process inclusion list**. The app needs to draw its text with classic Windows
text or the system DirectWrite. Only 64-bit apps are supported. Use the
exclusion list there to skip an app.

## Compatibility

Run one font mod at a time. Turn off Explorer Font Changer and Change More
Fonts before you turn this one on.

Taskbar, Start menu and notification center stylers can set fonts on single
controls. If a theme's font should stay, add it to **Keep these fonts**.

If menu text looks wrong next to another mod that draws menus, try **Keep
cached classic fonts**. Web content, DWM title bars and text drawn as pictures
keep their fonts.

## Credits

Merges two mods, both MIT:

- [Explorer Font Changer](https://windhawk.net/mods/explorer-font-changer) by
  Gabriela Cristei, the base of the File Explorer text and the fitting.
- [Change More Fonts](https://windhawk.net/mods/change-more-fonts) by xh1le,
  the base of the shell-wide coverage, weights and font lists.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- font:
  - name: FiraCode Nerd Font
    $name: Font family
    $description: An installed font family, as Settings shows it under Personalization > Fonts. Leave empty or type None to keep the original fonts.
  - weight: medium
    $name: Font weight
    $description: Medium matches the rest of the desktop. Keep uses the weight each app asks for.
    $options:
    - keep: Keep the app's weight
    - light: Light (300)
    - regular: Regular (400)
    - medium: Medium (500)
    - semibold: Semibold (600)
    - bold: Bold (700)
  - forceBaseWeight: false
    $name: Use the chosen weight for bold text too
    $description: When off, semibold and bold text stays heavier than the rest.
  - pause: false
    $name: Pause font changes
    $description: When on, apps use their usual font the next time they draw or lay out text.
  $name: Text font
- rendering:
  - noFit: false
    $name: Never shrink text
    $description: When off, File Explorer text that would not fit shrinks to no less than 85% of its size, and past that the original font draws it. When on, text keeps its size and may clip.
  - gdiCreate: false
    $name: Change classic fonts when apps create them
    $description: Reaches a few more classic controls, such as edit boxes, but that text cannot shrink or fall back when it does not fit. Off is safer.
  - disableGdiDrawing: false
    $name: Keep cached classic fonts
    $description: When on, classic text keeps the font that is already selected when it is drawn. Try it if another mod changes menu text drawing.
  - disableGdi: false
    $name: Leave classic text alone
    $description: When on, classic Windows controls (menus, dialogs, the file list) keep their fonts.
  - disableDirectWrite: false
    $name: Leave modern text alone
    $description: When on, modern text (Start, Search, Settings, most XAML controls) keeps its fonts.
  $name: Rendering
- replace:
  - replaceAllFonts: false
    $name: Replace every eligible font
    $description: When on, document fonts such as Arial and Calibri change too, in the apps this mod runs in.
  - replaceMonospace: false
    $name: Include monospace fonts
    $description: When on, monospace fonts such as Consolas change too, if they are on your list or every font is replaced.
  - additionalFonts: ""
    $name: Also replace these fonts
    $description: Family names separated by commas, such as Arial, Verdana.
  - excludedFonts: ""
    $name: Keep these fonts
    $description: Family names separated by commas. This list wins over the others.
  $name: Fonts to replace
*/
// ==/WindhawkModSettings==

#include <dwrite.h>
#include <dwrite_2.h>
#include <dwrite_3.h>
#include <uxtheme.h>
#include <windhawk_utils.h>
#include <windows.h>
#include <wrl/client.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <cwctype>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {

using Microsoft::WRL::ComPtr;

constexpr const wchar_t* kDefaultReplaceFamilies[] = {
    // Windows 11 and Windows 10 shell families.
    L"Segoe UI",
    L"Segoe UI Variable",
    L"Segoe UI VF",
    L"Segoe UI Variable Text",
    L"Segoe UI Variable Display",
    L"Segoe UI Variable Small",
    L"Segoe UI Variable Text Semibold",
    L"Segoe UI Variable Display Semibold",
    L"Segoe UI Variable Small Semibold",
    L"Segoe UI Variable Text Light",
    L"Segoe UI Variable Display Light",
    L"Segoe UI Variable Text Semilight",
    L"Segoe UI Variable Display Semilight",
    L"Segoe UI Semibold",
    L"Segoe UI Semilight",
    L"Segoe UI Light",
    L"Segoe UI Bold",
    L"Segoe UI Black",
    // Classic Win32 UI faces.
    L"Tahoma",
    L"Microsoft Sans Serif",
    L"MS Shell Dlg",
    L"MS Shell Dlg 2",
    L"MS Sans Serif",
    // Japanese UI faces (document faces are intentionally excluded).
    L"Yu Gothic UI",
    L"Meiryo UI",
    L"MS UI Gothic",
};

constexpr const wchar_t* kProtectedScriptFamilies[] = {
    // Japanese document faces.
    L"Yu Gothic",
    L"Yu Mincho",
    L"Meiryo",
    L"MS Gothic",
    L"MS Mincho",
    L"MS PGothic",
    L"MS PMincho",
    // CJK faces with distinct glyph coverage.
    L"Microsoft YaHei",
    L"Microsoft YaHei UI",
    L"Microsoft JhengHei",
    L"SimSun",
    L"NSimSun",
    L"SimHei",
    L"KaiTi",
    L"FangSong",
    L"MingLiU",
    L"PMingLiU",
    L"Malgun Gothic",
    L"Gulim",
    L"Batang",
    L"Dotum",
    L"Leelawadee",
    L"Leelawadee UI",
    // Fonts used for particular writing systems.
    L"Nirmala UI",
    L"Mangal",
    L"Kokila",
    L"Utsaah",
    L"Aparajita",
    L"Sangam MN",
    L"Gautami",
    L"Vrinda",
    L"Shonar Bangla",
    L"Bangla UI",
    L"Iskoola Pota",
    L"Kartika",
    L"Raavi",
    L"Latha",
    L"Tunga",
    L"Shruti",
    L"Kalinga",
    L"Myanmar Text",
    L"Myanmar UI",
    L"Khmer UI",
    L"Lao UI",
    L"DokChampa",
    L"Ebrima",
    L"Gadugi",
    L"Microsoft Himalaya",
    // Arabic and Hebrew faces.
    L"Arabic Typesetting",
    L"Traditional Arabic",
    L"Simplified Arabic",
    L"Sakkal Majalla",
    L"Aldhabi",
    L"Urdu Typesetting",
    L"Andalus",
    L"Arabic Transparent",
    L"David",
    L"Narkisim",
    L"FrankRuehl",
    L"Miriam",
    L"Miriam Fixed",
    L"Rod",
    L"Arial Hebrew",
    L"Arial Unicode MS",
};

struct Settings {
    std::wstring fontFamily;
    int fontWeight = 500;
    bool forceBaseWeight = false;
    bool disableMod = false;
    bool noFit = false;
    bool gdiCreate = false;
    bool disableGdi = false;
    bool disableGdiDrawing = false;
    bool disableDirectWrite = false;
    bool replaceAllFonts = false;
    bool replaceMonospace = false;
    std::vector<std::wstring> additionalFamilies;
    std::vector<std::wstring> extraExcludedFamilies;
};

struct Runtime {
    Settings settings;
    bool enabled = false;
    std::wstring dwFamily;
    std::wstring gdiFaceBase;
    std::wstring gdiFaceSemi;
    std::wstring gdiFaceBold;
    bool dwValid = false;
    bool gdiValid = false;
    std::vector<std::wstring> replaceFamilies;
    std::vector<std::wstring> excludedFamilies;
};

std::shared_ptr<const Runtime> g_runtime;
SRWLOCK g_runtimeLock = SRWLOCK_INIT;
thread_local bool t_internal = false;
bool g_isExplorer = false;

// Declared early because GDI face checks and the draw-time swap both need
// the unhooked creation call.
using CreateFontIndirectW_t = decltype(&CreateFontIndirectW);
CreateFontIndirectW_t g_origCreateFontIndirectW = nullptr;

struct InternalScope {
    bool previous;
    InternalScope() : previous(t_internal) { t_internal = true; }
    ~InternalScope() { t_internal = previous; }
    InternalScope(const InternalScope&) = delete;
    InternalScope& operator=(const InternalScope&) = delete;
};

std::shared_ptr<const Runtime> GetRuntimeSnapshot() {
    AcquireSRWLockShared(&g_runtimeLock);
    auto runtime = g_runtime;
    ReleaseSRWLockShared(&g_runtimeLock);
    return runtime;
}

void PublishRuntime(std::shared_ptr<const Runtime> runtime) noexcept {
    AcquireSRWLockExclusive(&g_runtimeLock);
    g_runtime.swap(runtime);
    ReleaseSRWLockExclusive(&g_runtimeLock);
}

HFONT CreateFontUnhooked(const LOGFONTW* logFont) {
    InternalScope scope;
    return g_origCreateFontIndirectW ? g_origCreateFontIndirectW(logFont)
                                     : CreateFontIndirectW(logFont);
}

// ---------------------------------------------------------------------------
// String helpers
// ---------------------------------------------------------------------------

std::wstring ReadStringSetting(PCWSTR name) {
    return WindhawkUtils::StringSetting::make(name).get();
}

std::wstring Trim(std::wstring value) {
    size_t begin = 0;
    while (begin < value.size() && iswspace(value[begin])) {
        begin++;
    }
    size_t end = value.size();
    while (end > begin && iswspace(value[end - 1])) {
        end--;
    }
    return value.substr(begin, end - begin);
}

std::wstring ToLower(std::wstring value) {
    for (auto& ch : value) {
        ch = static_cast<wchar_t>(towlower(ch));
    }
    return value;
}

bool EqualsCI(std::wstring_view a, std::wstring_view b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); i++) {
        if (towlower(a[i]) != towlower(b[i])) {
            return false;
        }
    }
    return true;
}

bool StartsWithCI(std::wstring_view text, std::wstring_view prefix) {
    if (text.size() < prefix.size()) {
        return false;
    }
    return EqualsCI(text.substr(0, prefix.size()), prefix);
}

bool ContainsCI(std::wstring_view text, std::wstring_view needle) {
    if (needle.empty() || text.size() < needle.size()) {
        return false;
    }
    for (size_t i = 0; i + needle.size() <= text.size(); i++) {
        if (EqualsCI(text.substr(i, needle.size()), needle)) {
            return true;
        }
    }
    return false;
}

std::vector<std::wstring> SplitList(std::wstring_view text) {
    std::vector<std::wstring> result;
    std::wstring current;
    for (wchar_t ch : text) {
        if (ch == L',' || ch == L';' || ch == L'\r' || ch == L'\n') {
            auto item = Trim(current);
            if (!item.empty()) {
                result.push_back(std::move(item));
            }
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    auto item = Trim(current);
    if (!item.empty()) {
        result.push_back(std::move(item));
    }
    return result;
}

void AddUnique(std::vector<std::wstring>& list, std::wstring value) {
    value = ToLower(Trim(std::move(value)));
    if (value.empty()) {
        return;
    }
    if (std::find(list.begin(), list.end(), value) == list.end()) {
        list.push_back(std::move(value));
    }
}

std::wstring GetProcessBaseName() {
    std::vector<wchar_t> path(32768);
    DWORD length = GetModuleFileNameW(nullptr, path.data(),
                                      static_cast<DWORD>(path.size()));
    if (!length || length >= path.size()) {
        return {};
    }
    std::wstring result(path.data(), length);
    size_t slash = result.find_last_of(L"\\/");
    if (slash != std::wstring::npos) {
        result = result.substr(slash + 1);
    }
    return ToLower(result);
}

// ---------------------------------------------------------------------------
// Text and font classification
// ---------------------------------------------------------------------------

// PUA and surrogate pairs can encode shell icons, emoji or rare scripts.
// Keep the complete original run rather than guessing at glyphs.
bool IsProtectedText(const wchar_t* text, UINT length) {
    if (!text) {
        return true;
    }
    for (UINT i = 0; i < length; ++i) {
        unsigned c = text[i];
        if ((c >= 0xE000 && c <= 0xF8FF) || (c >= 0xD800 && c <= 0xDFFF)) {
            return true;
        }
    }
    return false;
}

UINT TextLength(const wchar_t* text, int length) {
    if (!text) {
        return 0;
    }
    return length < 0 ? static_cast<UINT>(wcslen(text))
                      : static_cast<UINT>(length);
}

// GDI draws these format controls as nothing when a face lacks them, so they
// must not force a fallback. Explorer wraps every formatted date in U+200E.
bool IsInvisibleControl(unsigned c) {
    return c < L' ' || c == 0x061C || (c >= 0x200B && c <= 0x200F) ||
           (c >= 0x202A && c <= 0x202E) || (c >= 0x2061 && c <= 0x2064) ||
           (c >= 0x206A && c <= 0x206F) || (c >= 0xFE00 && c <= 0xFE0F) ||
           c == 0xFEFF;
}

// Legacy face names such as "Segoe UI Semibold" carry their weight in the
// name. Longer suffixes first, so " semibold" is not read as " bold".
int NameWeight(std::wstring_view face) {
    static constexpr std::pair<const wchar_t*, int> kSuffixes[] = {
        {L" extrabold", 800}, {L" ultrabold", 800}, {L" semibold", 600},
        {L" demibold", 600},  {L" black", 900},     {L" heavy", 900},
        {L" bold", 700},      {L" medium", 500},
    };
    std::wstring name = ToLower(std::wstring(face));
    for (const auto& [suffix, weight] : kSuffixes) {
        size_t size = wcslen(suffix);
        if (name.size() > size &&
            name.compare(name.size() - size, size, suffix) == 0) {
            return weight;
        }
    }
    return 0;
}

bool IsMonospaceName(std::wstring_view lowerName) {
    static constexpr const wchar_t* kExact[] = {
        L"consolas",
        L"courier",
        L"courier new",
        L"lucida console",
        L"lucida sans typewriter",
        L"cascadia mono",
        L"cascadia code",
        L"fira code",
        L"fira mono",
        L"source code pro",
        L"inconsolata",
        L"anonymous pro",
        L"hack",
        L"iosevka",
        L"cousine",
        L"terminal",
        L"fixedsys",
        L"ms gothic",
        L"ms mincho",
        L"nsimsun",
        L"simsun",
        L"mingliu",
        L"pmingliu",
        L"batang",
        L"gulim",
        L"dotum",
    };
    for (auto exact : kExact) {
        if (EqualsCI(lowerName, exact)) {
            return true;
        }
    }
    // "Monotype" is a vendor prefix, not a monospace marker.
    if (ContainsCI(lowerName, L"monotype") &&
        !ContainsCI(lowerName, L"mono ") && !ContainsCI(lowerName, L" mono")) {
        return false;
    }
    static constexpr const wchar_t* kParts[] = {
        L"mono", L"console", L"courier", L"fixed", L"terminal",
    };
    for (auto part : kParts) {
        if (ContainsCI(lowerName, part)) {
            return true;
        }
    }
    return false;
}

bool IsSymbolName(std::wstring_view lowerName) {
    static constexpr const wchar_t* kExact[] = {
        L"symbol",
        L"marlett",
        L"wingdings",
        L"wingdings 2",
        L"wingdings 3",
        L"webdings",
        L"segoe ui symbol",
        L"segoe ui emoji",
        L"segoe ui historic",
        L"segoe fluent icons",
        L"segoe mdl2 assets",
        L"cambria math",
    };
    for (auto exact : kExact) {
        if (EqualsCI(lowerName, exact)) {
            return true;
        }
    }
    static constexpr const wchar_t* kParts[] = {
        L"symbol",  L"emoji",    L"mdl2",     L"icons",       L"marlett",
        L"wingdings", L"webdings", L"fontawesome", L"font awesome",
    };
    for (auto part : kParts) {
        if (ContainsCI(lowerName, part)) {
            return true;
        }
    }
    return false;
}

bool IsProtectedScriptName(std::wstring_view lowerName) {
    for (auto exact : kProtectedScriptFamilies) {
        if (EqualsCI(lowerName, exact)) {
            return true;
        }
    }
    static constexpr const wchar_t* kPrefixes[] = {
        L"microsoft yahei", L"microsoft jhenghei", L"malgun gothic",
        L"noto sans cjk",   L"noto serif cjk",     L"source han",
        L"dengxian",
    };
    for (auto prefix : kPrefixes) {
        if (StartsWithCI(lowerName, prefix)) {
            return true;
        }
    }
    return false;
}

bool IsUnsupportedCharset(BYTE charset) {
    switch (charset) {
        case SYMBOL_CHARSET:
        case OEM_CHARSET:
        case MAC_CHARSET:
        case THAI_CHARSET:
        case HEBREW_CHARSET:
        case ARABIC_CHARSET:
        case VIETNAMESE_CHARSET:
        case GB2312_CHARSET:
        case CHINESEBIG5_CHARSET:
        case HANGEUL_CHARSET:
        case JOHAB_CHARSET:
            return true;
        default:
            return false;
    }
}

bool IsExcludedFamily(const std::wstring& lowerName, const Runtime& rt) {
    for (const auto& excluded : rt.excludedFamilies) {
        if (EqualsCI(lowerName, excluded)) {
            return true;
        }
    }
    return false;
}

// '@' faces are vertical CJK layouts; a horizontal face would rotate them.
bool IsProtectedFamily(const std::wstring& lowerName, BYTE charset,
                       bool fixedPitch, const Runtime& rt) {
    return lowerName.empty() || lowerName[0] == L'@' ||
           IsUnsupportedCharset(charset) ||
           (!rt.settings.replaceMonospace &&
            (fixedPitch || IsMonospaceName(lowerName))) ||
           IsSymbolName(lowerName) || IsProtectedScriptName(lowerName) ||
           IsExcludedFamily(lowerName, rt);
}

bool IsTargetFamily(std::wstring_view name, const Runtime& rt) {
    return !name.empty() &&
           (EqualsCI(name, rt.settings.fontFamily) ||
            EqualsCI(name, rt.dwFamily) || EqualsCI(name, rt.gdiFaceBase) ||
            EqualsCI(name, rt.gdiFaceSemi) || EqualsCI(name, rt.gdiFaceBold));
}

bool IsReplaceListed(const std::wstring& lowerName, const Runtime& rt) {
    for (const auto& family : rt.replaceFamilies) {
        if (EqualsCI(lowerName, family)) {
            return true;
        }
    }
    return false;
}

int ChooseGdiWeight(int originalWeight, const Runtime& rt) {
    if (rt.settings.fontWeight == 0 ||
        (originalWeight >= 600 && !rt.settings.forceBaseWeight)) {
        return originalWeight;
    }
    return rt.settings.fontWeight;
}

DWRITE_FONT_WEIGHT ChooseDWriteWeight(DWRITE_FONT_WEIGHT originalWeight,
                                      const Runtime& rt) {
    return static_cast<DWRITE_FONT_WEIGHT>(ChooseGdiWeight(originalWeight, rt));
}

const std::wstring& GdiFaceForWeight(const Runtime& rt, int weight) {
    if (weight >= 700) {
        return rt.gdiFaceBold;
    }
    if (weight >= 600) {
        return rt.gdiFaceSemi;
    }
    return rt.gdiFaceBase;
}

// One decision for both the draw-time swap and font creation. A face that is
// already the target only gets its weight moved when `includeTarget` is set.
bool DecideGdiFace(const Runtime& rt, std::wstring_view face, BYTE charset,
                   bool fixedPitch, int weight, bool includeTarget,
                   std::wstring& newFace, int& newWeight) {
    std::wstring lower = ToLower(Trim(std::wstring(face)));
    if (IsProtectedFamily(lower, charset, fixedPitch, rt)) {
        return false;
    }
    bool target = IsTargetFamily(lower, rt);
    if (target && !includeTarget) {
        return false;
    }
    if (!target && !rt.settings.replaceAllFonts && !IsReplaceListed(lower, rt)) {
        return false;
    }
    newWeight = ChooseGdiWeight(weight, rt);
    newFace = GdiFaceForWeight(rt, newWeight);
    return !EqualsCI(newFace, face) || newWeight != weight;
}

// ---------------------------------------------------------------------------
// Logging
// ---------------------------------------------------------------------------

void LogInitInfo(const Runtime& rt, const std::wstring& processName) {
    Wh_Log(L"Shell Font Changer Plus in %s", processName.c_str());
    Wh_Log(L"Family='%s' weight=%d forceBaseWeight=%d replaceAll=%d enabled=%d",
           rt.settings.fontFamily.c_str(), rt.settings.fontWeight,
           rt.settings.forceBaseWeight ? 1 : 0,
           rt.settings.replaceAllFonts ? 1 : 0, rt.enabled ? 1 : 0);
    Wh_Log(L"DirectWrite family='%s' valid=%d", rt.dwFamily.c_str(),
           rt.dwValid ? 1 : 0);
    Wh_Log(L"GDI faces base='%s' semibold='%s' bold='%s' valid=%d",
           rt.gdiFaceBase.c_str(), rt.gdiFaceSemi.c_str(),
           rt.gdiFaceBold.c_str(), rt.gdiValid ? 1 : 0);
}

// ---------------------------------------------------------------------------
// GDI face resolution
// ---------------------------------------------------------------------------

struct GdiCandidate {
    std::wstring name;
    int weight = 400;
    bool italic = false;
};

struct GdiEnumContext {
    std::wstring familyLower;
    std::vector<GdiCandidate> candidates;
};

// Nerd Fonts and other families split their weights into GDI faces with
// short suffixes ("FiraCode Nerd Font Med", "... SemBd", "... Ret").
std::wstring StripWeightSuffix(std::wstring name) {
    static constexpr const wchar_t* kSuffixes[] = {
        L" thin",     L" extralight", L" extra light", L" light",
        L" regular",  L" normal",     L" book",        L" medium",
        L" med",      L" retina",     L" ret",         L" semibold",
        L" semi bold", L" sembd",     L" semibd",      L" semilight",
        L" semi light", L" bold",     L" extrabold",   L" extra bold",
        L" black",    L" heavy",      L" italic",      L" oblique",
    };
    auto lower = ToLower(name);
    for (auto suffix : kSuffixes) {
        size_t suffixLength = wcslen(suffix);
        if (lower.size() > suffixLength && lower.ends_with(suffix)) {
            auto stripped = Trim(name.substr(0, name.size() - suffixLength));
            if (!stripped.empty()) {
                return stripped;
            }
        }
    }
    return name;
}

int CALLBACK GdiEnumProc(const LOGFONTW* logFont, const TEXTMETRICW*, DWORD,
                         LPARAM lParam) {
    auto* context = reinterpret_cast<GdiEnumContext*>(lParam);
    if (!logFont || !context) {
        return 1;
    }
    std::wstring name(logFont->lfFaceName,
                      wcsnlen(logFont->lfFaceName, LF_FACESIZE));
    if (name.empty() || name[0] == L'@') {
        return 1;
    }
    std::wstring lower = ToLower(name);
    if (lower != context->familyLower &&
        ToLower(StripWeightSuffix(name)) != context->familyLower) {
        return 1;
    }
    for (const auto& candidate : context->candidates) {
        if (EqualsCI(candidate.name, name) &&
            candidate.weight == logFont->lfWeight &&
            candidate.italic == (logFont->lfItalic != 0)) {
            return 1;
        }
    }
    context->candidates.push_back(
        {name, static_cast<int>(logFont->lfWeight), logFont->lfItalic != 0});
    return 1;
}

bool VerifyGdiFace(const std::wstring& face, int weight) {
    LOGFONTW logFont = {};
    logFont.lfHeight = -16;
    logFont.lfWeight = weight;
    logFont.lfCharSet = DEFAULT_CHARSET;
    wcsncpy_s(logFont.lfFaceName, face.c_str(), _TRUNCATE);

    HFONT font = CreateFontUnhooked(&logFont);
    if (!font) {
        return false;
    }
    bool ok = false;
    HDC dc = CreateCompatibleDC(nullptr);
    if (dc) {
        HGDIOBJ old = SelectObject(dc, font);
        if (old && old != HGDI_ERROR) {
            wchar_t selected[LF_FACESIZE] = {};
            if (GetTextFaceW(dc, LF_FACESIZE, selected) > 0) {
                ok = EqualsCI(selected, face);
            }
            SelectObject(dc, old);
        }
        DeleteDC(dc);
    }
    DeleteObject(font);
    return ok;
}

std::wstring ChooseGdiFace(const std::vector<GdiCandidate>& candidates,
                           int targetWeight, const std::wstring& family,
                           bool* found) {
    std::vector<const GdiCandidate*> ordered;
    for (const auto& candidate : candidates) {
        if (!candidate.italic) {
            ordered.push_back(&candidate);
        }
    }
    *found = false;
    if (ordered.empty()) {
        return {};
    }
    auto score = [&](const GdiCandidate* c) {
        long long value =
            static_cast<long long>(std::abs(c->weight - targetWeight)) * 100;
        if (!EqualsCI(c->name, family)) {
            value += 10;
        }
        return value + static_cast<long long>(c->name.size());
    };
    std::sort(ordered.begin(), ordered.end(),
              [&](const GdiCandidate* a, const GdiCandidate* b) {
                  return score(a) < score(b);
              });
    for (const auto* candidate : ordered) {
        if (VerifyGdiFace(candidate->name, targetWeight)) {
            *found = true;
            return candidate->name;
        }
    }
    return {};
}

void ResolveGdiFaces(Runtime& rt) {
    rt.gdiValid = false;
    rt.gdiFaceBase.clear();
    rt.gdiFaceSemi.clear();
    rt.gdiFaceBold.clear();

    if (rt.settings.fontFamily.size() > LF_FACESIZE - 1) {
        Wh_Log(L"Font family is too long for classic text (max %d): %s",
               LF_FACESIZE - 1, rt.settings.fontFamily.c_str());
        return;
    }
    HDC dc = CreateCompatibleDC(nullptr);
    if (!dc) {
        Wh_Log(L"CreateCompatibleDC failed; classic text stays as it is");
        return;
    }
    GdiEnumContext context;
    context.familyLower = ToLower(rt.settings.fontFamily);
    LOGFONTW filter = {};
    filter.lfCharSet = DEFAULT_CHARSET;
    EnumFontFamiliesExW(dc, &filter, GdiEnumProc,
                        reinterpret_cast<LPARAM>(&context), 0);
    DeleteDC(dc);

    if (context.candidates.empty()) {
        Wh_Log(L"No classic face matches '%s'; classic text stays as it is",
               rt.settings.fontFamily.c_str());
        return;
    }
    for (size_t i = 0; i < context.candidates.size() && i < 20; i++) {
        Wh_Log(L"GDI candidate: face='%s' weight=%d italic=%d",
               context.candidates[i].name.c_str(), context.candidates[i].weight,
               context.candidates[i].italic ? 1 : 0);
    }

    int baseWeight = rt.settings.fontWeight ? rt.settings.fontWeight : FW_NORMAL;
    bool found = false;
    auto base = ChooseGdiFace(context.candidates, baseWeight,
                              rt.settings.fontFamily, &found);
    if (!found) {
        Wh_Log(L"Could not verify a classic face for weight %d", baseWeight);
        return;
    }
    auto semi = ChooseGdiFace(context.candidates, 600, rt.settings.fontFamily,
                              &found);
    if (!found) {
        semi = base;
    }
    auto bold = ChooseGdiFace(context.candidates, 700, rt.settings.fontFamily,
                              &found);
    if (!found) {
        bold = base;
    }
    rt.gdiFaceBase = std::move(base);
    rt.gdiFaceSemi = std::move(semi);
    rt.gdiFaceBold = std::move(bold);
    rt.gdiValid = true;
}

// ---------------------------------------------------------------------------
// DirectWrite family resolution
// ---------------------------------------------------------------------------

IDWriteFactory* g_dwFactory = nullptr;
HMODULE g_dwModule = nullptr;

std::wstring GetLocalizedFamilyName(IDWriteLocalizedStrings* names) {
    if (!names) {
        return {};
    }
    UINT32 index = 0;
    BOOL exists = FALSE;
    names->FindLocaleName(L"en-us", &index, &exists);
    if (!exists) {
        index = 0;
    }
    UINT32 length = 0;
    if (FAILED(names->GetStringLength(index, &length)) || length == 0 ||
        length > 256) {
        return {};
    }
    std::wstring result(length + 1, L'\0');
    if (FAILED(names->GetString(index, result.data(), length + 1))) {
        return {};
    }
    result.resize(length);
    return result;
}

std::wstring GetFamilyName(IDWriteFontFamily* family) {
    ComPtr<IDWriteLocalizedStrings> names;
    if (!family || FAILED(family->GetFamilyNames(names.GetAddressOf()))) {
        return {};
    }
    return GetLocalizedFamilyName(names.Get());
}

bool FindDWriteFamilyExact(IDWriteFontCollection* collection,
                           const std::wstring& name, std::wstring* result) {
    if (!collection || name.empty()) {
        return false;
    }
    UINT32 index = 0;
    BOOL exists = FALSE;
    if (FAILED(collection->FindFamilyName(name.c_str(), &index, &exists)) ||
        !exists) {
        return false;
    }
    ComPtr<IDWriteFontFamily> family;
    if (FAILED(collection->GetFontFamily(index, family.GetAddressOf())) ||
        !family) {
        return false;
    }
    auto actual = GetFamilyName(family.Get());
    *result = actual.empty() ? name : std::move(actual);
    return true;
}

bool ResolveDWriteFamily(Runtime& rt) {
    rt.dwValid = false;
    rt.dwFamily.clear();
    if (!g_dwFactory || rt.settings.fontFamily.empty()) {
        return false;
    }
    ComPtr<IDWriteFontCollection> collection;
    if (FAILED(g_dwFactory->GetSystemFontCollection(collection.GetAddressOf(),
                                                    FALSE)) ||
        !collection) {
        Wh_Log(L"GetSystemFontCollection failed; modern text stays as it is");
        return false;
    }
    std::wstring resolved;
    bool found = FindDWriteFamilyExact(collection.Get(), rt.settings.fontFamily,
                                       &resolved);
    if (!found) {
        auto stripped = StripWeightSuffix(rt.settings.fontFamily);
        if (!EqualsCI(stripped, rt.settings.fontFamily)) {
            found = FindDWriteFamilyExact(collection.Get(), stripped, &resolved);
        }
    }
    if (!found) {
        Wh_Log(L"Font family is not installed: %s",
               rt.settings.fontFamily.c_str());
        return false;
    }
    int baseWeight = rt.settings.fontWeight ? rt.settings.fontWeight : FW_NORMAL;
    ComPtr<IDWriteTextFormat> testFormat;
    InternalScope scope;
    HRESULT hr = g_dwFactory->CreateTextFormat(
        resolved.c_str(), nullptr, static_cast<DWRITE_FONT_WEIGHT>(baseWeight),
        DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 14.0f, L"en-us",
        testFormat.GetAddressOf());
    if (FAILED(hr) || !testFormat) {
        Wh_Log(L"DirectWrite CreateTextFormat failed for '%s' (hr=0x%08X)",
               resolved.c_str(), static_cast<unsigned>(hr));
        return false;
    }
    rt.dwFamily = std::move(resolved);
    rt.dwValid = true;
    return true;
}

// ---------------------------------------------------------------------------
// Settings and runtime construction
// ---------------------------------------------------------------------------

int ParseWeight(std::wstring value) {
    value = ToLower(Trim(std::move(value)));
    if (value == L"keep" || value == L"0") {
        return 0;
    }
    if (value == L"light") {
        return 300;
    }
    if (value == L"regular") {
        return 400;
    }
    if (value == L"semibold") {
        return 600;
    }
    if (value == L"bold") {
        return 700;
    }
    int number = _wtoi(value.c_str());
    if (number >= 100 && number <= 900) {
        return number;
    }
    // Empty (no stored value yet) and "medium" both mean Medium.
    return 500;
}

Settings LoadSettings() {
    Settings settings;
    // One family only. If a fallback list was pasted, use its first entry.
    auto parts = SplitList(Trim(ReadStringSetting(L"font.name")));
    if (!parts.empty()) {
        settings.fontFamily = std::move(parts[0]);
    }
    settings.fontWeight = ParseWeight(ReadStringSetting(L"font.weight"));
    settings.forceBaseWeight = Wh_GetIntSetting(L"font.forceBaseWeight") != 0;
    settings.disableMod = Wh_GetIntSetting(L"font.pause") != 0;
    settings.noFit = Wh_GetIntSetting(L"rendering.noFit") != 0;
    settings.gdiCreate = Wh_GetIntSetting(L"rendering.gdiCreate") != 0;
    settings.disableGdiDrawing =
        Wh_GetIntSetting(L"rendering.disableGdiDrawing") != 0;
    settings.disableGdi = Wh_GetIntSetting(L"rendering.disableGdi") != 0;
    settings.disableDirectWrite =
        Wh_GetIntSetting(L"rendering.disableDirectWrite") != 0;
    settings.replaceAllFonts = Wh_GetIntSetting(L"replace.replaceAllFonts") != 0;
    settings.replaceMonospace =
        Wh_GetIntSetting(L"replace.replaceMonospace") != 0;
    settings.additionalFamilies =
        SplitList(ReadStringSetting(L"replace.additionalFonts"));
    settings.extraExcludedFamilies =
        SplitList(ReadStringSetting(L"replace.excludedFonts"));
    return settings;
}

std::shared_ptr<Runtime> BuildRuntime() {
    InternalScope internalScope;
    auto runtime = std::make_shared<Runtime>();
    runtime->settings = LoadSettings();
    const auto& family = runtime->settings.fontFamily;
    if (family.empty() || EqualsCI(family, L"None")) {
        Wh_Log(L"No font is set, so the mod stays idle.");
        return runtime;
    }
    if (IsSymbolName(ToLower(family))) {
        Wh_Log(L"Icon and emoji fonts cannot be used as the text font.");
        return runtime;
    }
    for (auto name : kDefaultReplaceFamilies) {
        AddUnique(runtime->replaceFamilies, name);
    }
    for (auto& name : runtime->settings.additionalFamilies) {
        AddUnique(runtime->replaceFamilies, name);
    }
    for (auto& name : runtime->settings.extraExcludedFamilies) {
        AddUnique(runtime->excludedFamilies, name);
    }
    ResolveGdiFaces(*runtime);
    ResolveDWriteFamily(*runtime);
    runtime->enabled = runtime->gdiValid || runtime->dwValid;
    return runtime;
}

std::shared_ptr<const Runtime> GetGdiDrawRuntime() {
    if (t_internal) {
        return nullptr;
    }
    auto rt = GetRuntimeSnapshot();
    if (!rt || !rt->enabled || rt->settings.disableMod ||
        rt->settings.disableGdi || rt->settings.disableGdiDrawing ||
        !rt->gdiValid) {
        return nullptr;
    }
    return rt;
}

std::shared_ptr<const Runtime> GetGdiCreateRuntime() {
    if (t_internal) {
        return nullptr;
    }
    auto rt = GetRuntimeSnapshot();
    if (!rt || !rt->enabled || rt->settings.disableMod ||
        rt->settings.disableGdi || !rt->settings.gdiCreate || !rt->gdiValid) {
        return nullptr;
    }
    return rt;
}

std::shared_ptr<const Runtime> GetDWriteRuntime() {
    if (t_internal) {
        return nullptr;
    }
    auto rt = GetRuntimeSnapshot();
    if (!rt || !rt->enabled || rt->settings.disableMod ||
        rt->settings.disableDirectWrite || !rt->dwValid) {
        return nullptr;
    }
    return rt;
}

// ---------------------------------------------------------------------------
// Draw-time GDI swap with fitting
// ---------------------------------------------------------------------------

// Round the original height by the fit scale, keeping its sign so a
// character-cell height stays a character-cell height and a cell of at
// least one pixel remains.
LONG FitHeight(LONG height, double scale) {
    if (!height) {
        return height;
    }
    LONG scaled = static_cast<LONG>(
        std::lround(std::fabs(static_cast<double>(height)) * scale));
    if (scaled < 1) {
        scaled = 1;
    }
    return height < 0 ? -scaled : scaled;
}

// Scope the selected font to one call. Restoring it before DeleteObject is
// required even for DT_CALCRECT, nested drawing calls and failed draws.
class FontScope {
    HDC dc_ = nullptr;
    HFONT replacement_ = nullptr;
    HGDIOBJ previous_ = nullptr;
    LOGFONTW font_{};  // target face at the original height
    double scale_ = 1.0;
    LONG naturalWidth_ = 0;
    bool fit_ = false;

    HFONT Build() const {
        LOGFONTW scaled = font_;
        scaled.lfHeight = FitHeight(font_.lfHeight, scale_);
        return CreateFontUnhooked(&scaled);
    }

    bool SelectReplacement(HFONT rebuilt) {
        HGDIOBJ outgoing = SelectObject(dc_, rebuilt);
        if (!outgoing || outgoing == HGDI_ERROR) {
            DeleteObject(rebuilt);
            return false;
        }
        // `outgoing` is the previous replacement; the original font is
        // still owned by `previous_` and is restored by the destructor.
        if (outgoing != previous_) {
            DeleteObject(outgoing);
        }
        replacement_ = rebuilt;
        return true;
    }

   public:
    static constexpr double kMinWidth = 0.8;
    static constexpr double kMinScale = 0.85;

    FontScope(HDC hdc, const wchar_t* text, UINT length,
              bool glyphIndices = false) {
        if (!hdc || glyphIndices || IsProtectedText(text, length)) {
            return;
        }
        auto rt = GetGdiDrawRuntime();
        if (!rt) {
            return;
        }
        // Printers and metafiles keep the document's own fonts.
        if (GetDeviceCaps(hdc, TECHNOLOGY) != DT_RASDISPLAY) {
            return;
        }
        LOGFONTW font{};
        if (GetObjectW(GetCurrentObject(hdc, OBJ_FONT), sizeof(font), &font) !=
            sizeof(font)) {
            return;
        }
        std::wstring_view face(font.lfFaceName,
                               wcsnlen(font.lfFaceName, LF_FACESIZE));
        // Face names such as "Segoe UI Black" carry their weight in the name.
        int weight = font.lfWeight ? font.lfWeight : FW_NORMAL;
        TEXTMETRICW metrics{};
        if (GetTextMetricsW(hdc, &metrics) && metrics.tmWeight > weight) {
            weight = metrics.tmWeight;
        }
        weight = std::max(weight, NameWeight(face));
        std::wstring newFace;
        int newWeight = weight;
        if (!DecideGdiFace(*rt, face, font.lfCharSet,
                           (font.lfPitchAndFamily & FIXED_PITCH) != 0, weight,
                           false, newFace, newWeight)) {
            return;
        }
        fit_ = !rt->settings.noFit && g_isExplorer;
        font.lfWeight = newWeight;
        // A script charset the target lacks would make the mapper pick
        // another face.
        font.lfCharSet = DEFAULT_CHARSET;
        // A stretched or raster average width belongs to the original face.
        font.lfWidth = 0;
        wcsncpy_s(font.lfFaceName, newFace.c_str(), _TRUNCATE);
        font_ = font;
        replacement_ = Build();
        if (!replacement_) {
            return;
        }
        previous_ = SelectObject(hdc, replacement_);
        if (!previous_ || previous_ == HGDI_ERROR) {
            DeleteObject(replacement_);
            replacement_ = nullptr;
            return;
        }
        dc_ = hdc;
        TEXTMETRICW natural{};
        if (GetTextMetricsW(dc_, &natural)) {
            naturalWidth_ = natural.tmAveCharWidth;
        }
        // Never let the mapper substitute a third font for a name GDI does
        // not know.
        wchar_t realized[LF_FACESIZE]{};
        bool missing = !GetTextFaceW(dc_, LF_FACESIZE, realized) ||
                       _wcsicmp(realized, newFace.c_str()) != 0;
        if (!missing && length) {
            std::vector<WORD> glyphs(length);
            missing = GetGlyphIndicesW(dc_, text, length, glyphs.data(),
                                       GGI_MARK_NONEXISTING_GLYPHS) == GDI_ERROR;
            for (UINT i = 0; !missing && i < length; ++i) {
                if (glyphs[i] == 0xffff && !IsInvisibleControl(text[i])) {
                    missing = true;
                }
            }
        }
        // GDI font linking varies by family. Keep the original run when the
        // replacement lacks a character instead of drawing empty boxes.
        if (missing) {
            Revert();
        }
    }

    ~FontScope() {
        if (dc_) {
            SelectObject(dc_, previous_);
        }
        if (replacement_) {
            DeleteObject(replacement_);
        }
    }

    FontScope(const FontScope&) = delete;
    FontScope& operator=(const FontScope&) = delete;

    bool Active() const { return dc_ != nullptr; }
    bool Fits() const { return dc_ != nullptr && fit_; }
    double CurrentScale() const { return scale_; }

    // Give the run back to the original font. Its metrics are what the
    // control was laid out for, so it fits where the target cannot.
    void Revert() {
        if (!dc_) {
            return;
        }
        SelectObject(dc_, previous_);
        DeleteObject(replacement_);
        replacement_ = nullptr;
        dc_ = nullptr;
    }

    // Narrow the replacement. Returns false when it cannot get narrower
    // within the floor, so the caller falls back to the original face.
    bool Condense(double ratio) {
        if (!dc_ || ratio >= 1.0 || ratio <= 0) {
            return false;
        }
        TEXTMETRICW metrics{};
        if (!GetTextMetricsW(dc_, &metrics)) {
            return false;
        }
        LONG width = std::max<LONG>(
            1, static_cast<LONG>(std::floor(metrics.tmAveCharWidth * ratio)));
        width = std::max<LONG>(
            width, static_cast<LONG>(std::ceil(naturalWidth_ * kMinWidth)));
        if (width >= metrics.tmAveCharWidth) {
            return false;
        }
        LONG saved = font_.lfWidth;
        font_.lfWidth = width;
        HFONT rebuilt = Build();
        if (!rebuilt || !SelectReplacement(rebuilt)) {
            font_.lfWidth = saved;
            return false;
        }
        return true;
    }

    // Rebuild the replacement at a smaller height, never under the floor.
    bool Rescale(double next) {
        if (!dc_ || !(next < scale_) || next < kMinScale) {
            return false;
        }
        double prior = scale_;
        scale_ = next;
        HFONT rebuilt = Build();
        if (!rebuilt || !SelectReplacement(rebuilt)) {
            scale_ = prior;
            return false;
        }
        return true;
    }
};

using DrawTextW_t = decltype(&DrawTextW);
using DrawTextExW_t = decltype(&DrawTextExW);
using TextOutW_t = decltype(&TextOutW);
using ExtTextOutW_t = decltype(&ExtTextOutW);
using GetTextExtentPoint32W_t = decltype(&GetTextExtentPoint32W);
using GetTextExtentExPointW_t = decltype(&GetTextExtentExPointW);
using DrawThemeText_t = decltype(&DrawThemeText);
using DrawThemeTextEx_t = decltype(&DrawThemeTextEx);

DrawTextW_t g_origDrawTextW = nullptr;
DrawTextExW_t g_origDrawTextExW = nullptr;
TextOutW_t g_origTextOutW = nullptr;
ExtTextOutW_t g_origExtTextOutW = nullptr;
GetTextExtentPoint32W_t g_origExtent = nullptr;
GetTextExtentExPointW_t g_origExtentEx = nullptr;
DrawThemeText_t g_origDrawThemeText = nullptr;
DrawThemeTextEx_t g_origDrawThemeTextEx = nullptr;

// Some controls (the Properties checkboxes) pass a box wider than the window
// they draw in; anything past the window's client edge is clipped.
RECT VisibleBox(HDC dc, const RECT& rect, UINT flags) {
    RECT visible = rect;
    RECT client{};
    bool bounded = false;
    if (HWND window = WindowFromDC(dc); window && GetClientRect(window, &client)) {
        bounded = true;
    } else if (GetObjectType(dc) == OBJ_MEMDC &&
               GetClipBox(dc, &client) != ERROR &&
               client.right - client.left > 1) {
        // Themed controls draw into a buffered-paint bitmap the size of the
        // control; its clip box is that size. Skip the 1x1 stock bitmap.
        bounded = true;
    }
    if (!bounded) {
        return visible;
    }
    const LONG left = std::max(visible.left, client.left);
    const LONG right = std::min(visible.right, client.right);
    if (flags & DT_CENTER) {
        // Centred text grows from the box's centre, so the nearer edge
        // limits both sides.
        const LONG centre = (visible.left + visible.right) / 2;
        const LONG half = std::min(centre - left, right - centre);
        if (half > 0) {
            visible.left = centre - half;
            visible.right = centre + half;
        }
    } else if (right > left) {
        visible.left = left;
        visible.right = right;
    }
    return visible;
}

// Shrink a substituted font, within readable limits, until the block fits
// the box the application gave it, else hand it back to the original font.
// Fixed-size boxes are designed around the original font, so this guard is
// what stops buttons, labels and static text from clipping.
void FitBox(FontScope& scope, HDC dc, LPCWSTR text, UINT length,
            const RECT* box, UINT flags, LPDRAWTEXTPARAMS params) {
    if (!scope.Fits() || !box || !length) {
        return;
    }
    // Measuring calls and ellipsis draws report or truncate rather than clip.
    if (flags & (DT_CALCRECT | DT_END_ELLIPSIS | DT_PATH_ELLIPSIS |
                 DT_WORD_ELLIPSIS)) {
        return;
    }
    const RECT visible = VisibleBox(dc, *box, flags);
    const int margins = params ? params->iLeftMargin + params->iRightMargin : 0;
    const int boxWidth = visible.right - visible.left - margins;
    const int boxHeight = visible.bottom - visible.top;
    if (boxWidth <= 0 || boxHeight <= 0) {
        return;
    }
    const bool singleLine = (flags & DT_SINGLELINE) != 0;
    for (int tries = 0; tries < 16 && scope.Active(); ++tries) {
        if (singleLine) {
            SIZE size{};
            if (g_origExtent &&
                g_origExtent(dc, text, static_cast<int>(length), &size) &&
                size.cx > boxWidth) {
                if (scope.Condense(static_cast<double>(boxWidth) / size.cx)) {
                    continue;
                }
                scope.Revert();
                break;
            }
            TEXTMETRICW metrics{};
            if (GetTextMetricsW(dc, &metrics) && metrics.tmHeight > boxHeight) {
                double next = scope.CurrentScale() *
                              static_cast<double>(boxHeight) /
                              metrics.tmHeight * 0.98;
                if (scope.Rescale(next)) {
                    continue;
                }
                scope.Revert();
            }
            break;
        }
        // Wrapped text re-flows inside the width, so only the block height
        // can still overrun the box. DT_CALCRECT measures without drawing.
        RECT probe = visible;
        const UINT probeFlags = (flags | DT_CALCRECT) & ~DT_MODIFYSTRING;
        if (params && g_origDrawTextExW) {
            DRAWTEXTPARAMS probeParams = *params;
            g_origDrawTextExW(dc, const_cast<LPWSTR>(text),
                              static_cast<int>(length), &probe, probeFlags,
                              &probeParams);
        } else if (g_origDrawTextW) {
            g_origDrawTextW(dc, text, static_cast<int>(length), &probe,
                            probeFlags);
        } else {
            break;
        }
        double ratio = 1.0;
        const int needed = probe.bottom - probe.top;
        if (needed > boxHeight) {
            ratio = std::min(ratio, static_cast<double>(boxHeight) / needed);
        }
        const int neededWidth = probe.right - probe.left;
        const int fullWidth = visible.right - visible.left;
        if (neededWidth > fullWidth) {
            ratio = std::min(ratio, static_cast<double>(fullWidth) / neededWidth);
        }
        if (ratio < 1.0) {
            if (scope.Condense(ratio)) {
                continue;
            }
            if (scope.Rescale(scope.CurrentScale() * ratio * 0.98)) {
                continue;
            }
            scope.Revert();
        }
        break;
    }
}

int WINAPI DrawTextW_Hook(HDC dc, LPCWSTR text, int length, LPRECT rect,
                          UINT flags) {
    UINT size = TextLength(text, length);
    FontScope font(dc, text, size);
    FitBox(font, dc, text, size, rect, flags, nullptr);
    return g_origDrawTextW(dc, text, length, rect, flags);
}

int WINAPI DrawTextExW_Hook(HDC dc, LPWSTR text, int length, LPRECT rect,
                            UINT flags, LPDRAWTEXTPARAMS params) {
    UINT size = TextLength(text, length);
    FontScope font(dc, text, size);
    FitBox(font, dc, text, size, rect, flags, params);
    return g_origDrawTextExW(dc, text, length, rect, flags, params);
}

BOOL WINAPI TextOutW_Hook(HDC dc, int x, int y, LPCWSTR text, int length) {
    FontScope font(dc, text, length < 0 ? 0 : length);
    return g_origTextOutW(dc, x, y, text, length);
}

BOOL WINAPI ExtTextOutW_Hook(HDC dc, int x, int y, UINT flags, const RECT* rect,
                             LPCWSTR text, UINT length, const INT* widths) {
    // Pre-shaped glyph indices and advance widths belong to the original face.
    FontScope font(dc, text, length,
                   (flags & ETO_GLYPH_INDEX) != 0 || widths != nullptr);
    return g_origExtTextOutW(dc, x, y, flags, rect, text, length, widths);
}

BOOL WINAPI Extent_Hook(HDC dc, LPCWSTR text, int length, LPSIZE size) {
    FontScope font(dc, text, length < 0 ? 0 : length);
    return g_origExtent(dc, text, length, size);
}

BOOL WINAPI ExtentEx_Hook(HDC dc, LPCWSTR text, int length, int maxExtent,
                          LPINT fit, LPINT widths, LPSIZE size) {
    FontScope font(dc, text, length < 0 ? 0 : length);
    return g_origExtentEx(dc, text, length, maxExtent, fit, widths, size);
}

HRESULT WINAPI DrawThemeText_Hook(HTHEME theme, HDC dc, int part, int state,
                                  LPCWSTR text, int length, DWORD flags,
                                  DWORD flags2, LPCRECT rect) {
    UINT size = TextLength(text, length);
    FontScope font(dc, text, size);
    FitBox(font, dc, text, size, rect, flags, nullptr);
    return g_origDrawThemeText(theme, dc, part, state, text, length, flags,
                               flags2, rect);
}

HRESULT WINAPI DrawThemeTextEx_Hook(HTHEME theme, HDC dc, int part, int state,
                                    LPCWSTR text, int length, DWORD flags,
                                    LPRECT rect, const DTTOPTS* options) {
    UINT size = TextLength(text, length);
    FontScope font(dc, text, size);
    // A measuring call has no final box yet, so it is not fitted.
    if (!(options && (options->dwFlags & DTT_CALCRECT))) {
        FitBox(font, dc, text, size, rect, flags, nullptr);
    }
    return g_origDrawThemeTextEx(theme, dc, part, state, text, length, flags,
                                 rect, options);
}

// ---------------------------------------------------------------------------
// Creation-time GDI swap (off by default)
// ---------------------------------------------------------------------------

using CreateFontIndirectA_t = decltype(&CreateFontIndirectA);
using CreateFontIndirectExW_t = decltype(&CreateFontIndirectExW);
using CreateFontIndirectExA_t = decltype(&CreateFontIndirectExA);
using CreateFontW_t = decltype(&CreateFontW);
using CreateFontA_t = decltype(&CreateFontA);

CreateFontIndirectA_t g_origCreateFontIndirectA = nullptr;
CreateFontIndirectExW_t g_origCreateFontIndirectExW = nullptr;
CreateFontIndirectExA_t g_origCreateFontIndirectExA = nullptr;
CreateFontW_t g_origCreateFontW = nullptr;
CreateFontA_t g_origCreateFontA = nullptr;

bool ApplyToLogFontW(const Runtime& rt, LOGFONTW* logFont) {
    if (!logFont) {
        return false;
    }
    std::wstring_view face(logFont->lfFaceName,
                           wcsnlen(logFont->lfFaceName, LF_FACESIZE));
    int weight = logFont->lfWeight;
    std::wstring newFace;
    int newWeight = weight;
    if (!DecideGdiFace(rt, face, logFont->lfCharSet,
                       (logFont->lfPitchAndFamily & FIXED_PITCH) != 0, weight,
                       true, newFace, newWeight)) {
        return false;
    }
    if (!newFace.empty()) {
        wcsncpy_s(logFont->lfFaceName, newFace.c_str(), _TRUNCATE);
    }
    logFont->lfWeight = newWeight;
    return true;
}

bool ConvertGdiFaceToAnsi(PCWSTR face, char (&result)[LF_FACESIZE]) {
    wchar_t roundTrip[LF_FACESIZE] = {};
    return WideCharToMultiByte(CP_ACP, 0, face, -1, result, LF_FACESIZE,
                               nullptr, nullptr) &&
           MultiByteToWideChar(CP_ACP, 0, result, -1, roundTrip, LF_FACESIZE) &&
           wcscmp(roundTrip, face) == 0;
}

void ApplyToLogFontA(const Runtime& rt, LOGFONTA* logFont) {
    if (!logFont || strnlen(logFont->lfFaceName, LF_FACESIZE) == LF_FACESIZE) {
        return;
    }
    LOGFONTW wide = {};
    wide.lfHeight = logFont->lfHeight;
    wide.lfWidth = logFont->lfWidth;
    wide.lfEscapement = logFont->lfEscapement;
    wide.lfOrientation = logFont->lfOrientation;
    wide.lfWeight = logFont->lfWeight;
    wide.lfItalic = logFont->lfItalic;
    wide.lfUnderline = logFont->lfUnderline;
    wide.lfStrikeOut = logFont->lfStrikeOut;
    wide.lfCharSet = logFont->lfCharSet;
    wide.lfOutPrecision = logFont->lfOutPrecision;
    wide.lfClipPrecision = logFont->lfClipPrecision;
    wide.lfQuality = logFont->lfQuality;
    wide.lfPitchAndFamily = logFont->lfPitchAndFamily;
    wchar_t originalWide[LF_FACESIZE] = {};
    if (!MultiByteToWideChar(CP_ACP, 0, logFont->lfFaceName, -1, originalWide,
                             LF_FACESIZE)) {
        return;
    }
    wcscpy_s(wide.lfFaceName, originalWide);
    if (!ApplyToLogFontW(rt, &wide)) {
        return;
    }
    if (!EqualsCI(wide.lfFaceName, originalWide)) {
        char face[LF_FACESIZE] = {};
        if (!ConvertGdiFaceToAnsi(wide.lfFaceName, face)) {
            return;
        }
        strncpy_s(logFont->lfFaceName, face, _TRUNCATE);
    }
    logFont->lfWeight = wide.lfWeight;
}

HFONT WINAPI CreateFontIndirectW_Hook(const LOGFONTW* logFont) {
    auto rt = GetGdiCreateRuntime();
    if (!rt || !logFont) {
        return g_origCreateFontIndirectW(logFont);
    }
    LOGFONTW copy = *logFont;
    ApplyToLogFontW(*rt, &copy);
    return g_origCreateFontIndirectW(&copy);
}

HFONT WINAPI CreateFontIndirectA_Hook(const LOGFONTA* logFont) {
    auto rt = GetGdiCreateRuntime();
    if (!rt || !logFont) {
        return g_origCreateFontIndirectA(logFont);
    }
    LOGFONTA copy = *logFont;
    ApplyToLogFontA(*rt, &copy);
    return g_origCreateFontIndirectA(&copy);
}

template <typename T>
bool CopyExtendedLogFont(const T& original, T& copy) {
    const DWORD axes = original.elfDesignVector.dvNumAxes;
    if (axes > MM_MAX_NUMAXES) {
        return false;
    }
    const size_t size = offsetof(T, elfDesignVector) +
                        offsetof(DESIGNVECTOR, dvValues) + axes * sizeof(LONG);
    memcpy(&copy, &original, size);
    return true;
}

HFONT WINAPI CreateFontIndirectExW_Hook(const ENUMLOGFONTEXDVW* logFont) {
    auto rt = GetGdiCreateRuntime();
    ENUMLOGFONTEXDVW copy = {};
    if (!rt || !logFont || !CopyExtendedLogFont(*logFont, copy)) {
        return g_origCreateFontIndirectExW(logFont);
    }
    ApplyToLogFontW(*rt, &copy.elfEnumLogfontEx.elfLogFont);
    return g_origCreateFontIndirectExW(&copy);
}

HFONT WINAPI CreateFontIndirectExA_Hook(const ENUMLOGFONTEXDVA* logFont) {
    auto rt = GetGdiCreateRuntime();
    ENUMLOGFONTEXDVA copy = {};
    if (!rt || !logFont || !CopyExtendedLogFont(*logFont, copy)) {
        return g_origCreateFontIndirectExA(logFont);
    }
    ApplyToLogFontA(*rt, &copy.elfEnumLogfontEx.elfLogFont);
    return g_origCreateFontIndirectExA(&copy);
}

HFONT WINAPI CreateFontW_Hook(int height, int width, int escapement,
                              int orientation, int weight, DWORD italic,
                              DWORD underline, DWORD strikeOut, DWORD charset,
                              DWORD outPrecision, DWORD clipPrecision,
                              DWORD quality, DWORD pitchAndFamily,
                              LPCWSTR faceName) {
    auto rt = GetGdiCreateRuntime();
    std::wstring newFace;
    int newWeight = weight;
    if (rt && faceName &&
        DecideGdiFace(*rt, faceName, static_cast<BYTE>(charset),
                      (pitchAndFamily & FIXED_PITCH) != 0, weight, true,
                      newFace, newWeight)) {
        return g_origCreateFontW(
            height, width, escapement, orientation, newWeight, italic,
            underline, strikeOut, charset, outPrecision, clipPrecision, quality,
            pitchAndFamily, newFace.empty() ? faceName : newFace.c_str());
    }
    return g_origCreateFontW(height, width, escapement, orientation, weight,
                             italic, underline, strikeOut, charset,
                             outPrecision, clipPrecision, quality,
                             pitchAndFamily, faceName);
}

HFONT WINAPI CreateFontA_Hook(int height, int width, int escapement,
                              int orientation, int weight, DWORD italic,
                              DWORD underline, DWORD strikeOut, DWORD charset,
                              DWORD outPrecision, DWORD clipPrecision,
                              DWORD quality, DWORD pitchAndFamily,
                              LPCSTR faceName) {
    auto rt = GetGdiCreateRuntime();
    wchar_t wide[LF_FACESIZE] = {};
    std::wstring newFace;
    int newWeight = weight;
    char ansiFace[LF_FACESIZE] = {};
    if (rt && faceName &&
        MultiByteToWideChar(CP_ACP, 0, faceName, -1, wide, LF_FACESIZE) &&
        DecideGdiFace(*rt, wide, static_cast<BYTE>(charset),
                      (pitchAndFamily & FIXED_PITCH) != 0, weight, true,
                      newFace, newWeight) &&
        (newFace.empty() || ConvertGdiFaceToAnsi(newFace.c_str(), ansiFace))) {
        return g_origCreateFontA(
            height, width, escapement, orientation, newWeight, italic,
            underline, strikeOut, charset, outPrecision, clipPrecision, quality,
            pitchAndFamily, newFace.empty() ? faceName : ansiFace);
    }
    return g_origCreateFontA(height, width, escapement, orientation, weight,
                             italic, underline, strikeOut, charset,
                             outPrecision, clipPrecision, quality,
                             pitchAndFamily, faceName);
}

// ---------------------------------------------------------------------------
// DirectWrite hooks
// ---------------------------------------------------------------------------

using CreateTextFormat_t = HRESULT(STDMETHODCALLTYPE*)(IDWriteFactory*,
                                                       const WCHAR*,
                                                       IDWriteFontCollection*,
                                                       DWRITE_FONT_WEIGHT,
                                                       DWRITE_FONT_STYLE,
                                                       DWRITE_FONT_STRETCH,
                                                       FLOAT,
                                                       const WCHAR*,
                                                       IDWriteTextFormat**);

using CreateTextFormat6_t =
    HRESULT(STDMETHODCALLTYPE*)(IDWriteFactory6*,
                                const WCHAR*,
                                IDWriteFontCollection*,
                                const DWRITE_FONT_AXIS_VALUE*,
                                UINT32,
                                FLOAT,
                                const WCHAR*,
                                IDWriteTextFormat3**);

using CreateTextLayout_t = HRESULT(STDMETHODCALLTYPE*)(IDWriteFactory*,
                                                       const WCHAR*,
                                                       UINT32,
                                                       IDWriteTextFormat*,
                                                       FLOAT,
                                                       FLOAT,
                                                       IDWriteTextLayout**);

using CreateGdiLayout_t =
    HRESULT(STDMETHODCALLTYPE*)(IDWriteFactory*,
                                const WCHAR*,
                                UINT32,
                                IDWriteTextFormat*,
                                FLOAT,
                                FLOAT,
                                FLOAT,
                                const DWRITE_MATRIX*,
                                BOOL,
                                IDWriteTextLayout**);

using MapCharacters_t = HRESULT(STDMETHODCALLTYPE*)(
    IDWriteFontFallback*, IDWriteTextAnalysisSource*, UINT32, UINT32,
    IDWriteFontCollection*, const WCHAR*, DWRITE_FONT_WEIGHT,
    DWRITE_FONT_STYLE, DWRITE_FONT_STRETCH, UINT32*, IDWriteFont**, FLOAT*);

using MapCharacters1_t = HRESULT(STDMETHODCALLTYPE*)(
    IDWriteFontFallback1*, IDWriteTextAnalysisSource*, UINT32, UINT32,
    IDWriteFontCollection*, const WCHAR*, const DWRITE_FONT_AXIS_VALUE*,
    UINT32, UINT32*, FLOAT*, IDWriteFontFace5**);

using SetFontFamilyName_t = HRESULT(STDMETHODCALLTYPE*)(
    IDWriteTextLayout*, const WCHAR*, DWRITE_TEXT_RANGE);

CreateTextFormat_t g_origCreateTextFormat = nullptr;
CreateTextFormat6_t g_origCreateTextFormat6 = nullptr;
CreateTextLayout_t g_origCreateTextLayout = nullptr;
CreateGdiLayout_t g_origCreateGdiLayout = nullptr;
MapCharacters_t g_origMapCharacters = nullptr;
MapCharacters1_t g_origMapCharacters1 = nullptr;
SetFontFamilyName_t g_origSetFontFamilyName = nullptr;

bool IsSymbolSegment(const std::wstring& segment) {
    auto lower = ToLower(Trim(segment));
    return IsSymbolName(lower) || IsProtectedScriptName(lower);
}

bool ShouldReplaceDWriteFamily(const std::wstring& family, const Runtime& rt) {
    auto segments = SplitList(family);
    if (segments.empty()) {
        return false;
    }
    // If a XAML font-family fallback list holds an icon or emoji face, keep
    // the whole list so DirectWrite uses its normal fallback chain.
    for (size_t i = 1; i < segments.size(); i++) {
        if (IsSymbolSegment(segments[i])) {
            return false;
        }
    }
    auto lower = ToLower(segments.front());
    if (IsProtectedFamily(lower, DEFAULT_CHARSET, false, rt)) {
        return false;
    }
    return IsTargetFamily(lower, rt) || rt.settings.replaceAllFonts ||
           IsReplaceListed(lower, rt);
}

std::atomic<bool> g_loggedDwFormat{false};
std::atomic<bool> g_loggedDwMapping{false};
std::atomic<bool> g_loggedDwLayout{false};

std::vector<DWRITE_FONT_AXIS_VALUE> ChooseDWriteAxes(
    const DWRITE_FONT_AXIS_VALUE* axisValues, UINT32 axisCount,
    const Runtime& rt) {
    std::vector<DWRITE_FONT_AXIS_VALUE> axes;
    if (axisCount) {
        axes.assign(axisValues, axisValues + axisCount);
    }
    if (rt.settings.fontWeight == 0) {
        return axes;
    }
    auto weightAxis =
        std::find_if(axes.begin(), axes.end(), [](const auto& axis) {
            return axis.axisTag == DWRITE_FONT_AXIS_TAG_WEIGHT;
        });
    if (weightAxis == axes.end()) {
        axes.push_back({DWRITE_FONT_AXIS_TAG_WEIGHT,
                        static_cast<float>(rt.settings.fontWeight)});
    } else if (rt.settings.forceBaseWeight || weightAxis->value < 600.0f) {
        weightAxis->value = static_cast<float>(rt.settings.fontWeight);
    }
    return axes;
}

// DirectWrite accepts a name even when the supplied collection cannot
// resolve it. Let the factory use its system collection in that case.
IDWriteFontCollection* SelectDWriteCollection(IDWriteFontCollection* collection,
                                              const wchar_t* family) {
    if (collection) {
        UINT32 index = 0;
        BOOL exists = FALSE;
        if (SUCCEEDED(collection->FindFamilyName(family, &index, &exists)) &&
            exists) {
            return collection;
        }
    }
    return nullptr;
}

HRESULT STDMETHODCALLTYPE CreateTextFormat_Hook(IDWriteFactory* self,
                                                const WCHAR* familyName,
                                                IDWriteFontCollection* collection,
                                                DWRITE_FONT_WEIGHT weight,
                                                DWRITE_FONT_STYLE style,
                                                DWRITE_FONT_STRETCH stretch,
                                                FLOAT size,
                                                const WCHAR* locale,
                                                IDWriteTextFormat** textFormat) {
    auto rt = familyName ? GetDWriteRuntime() : nullptr;
    if (!rt || !ShouldReplaceDWriteFamily(familyName, *rt)) {
        return g_origCreateTextFormat(self, familyName, collection, weight,
                                      style, stretch, size, locale, textFormat);
    }
    auto original = static_cast<DWRITE_FONT_WEIGHT>(
        std::max<int>(weight, NameWeight(familyName)));
    DWRITE_FONT_WEIGHT newWeight = ChooseDWriteWeight(original, *rt);
    auto* targetCollection =
        SelectDWriteCollection(collection, rt->dwFamily.c_str());
    HRESULT hr = g_origCreateTextFormat(self, rt->dwFamily.c_str(),
                                        targetCollection, newWeight, style,
                                        stretch, size, locale, textFormat);
    if (SUCCEEDED(hr)) {
        if (!g_loggedDwFormat.exchange(true, std::memory_order_relaxed)) {
            Wh_Log(L"DirectWrite format '%s' became '%s' (weight %d to %d)",
                   familyName, rt->dwFamily.c_str(), static_cast<int>(weight),
                   static_cast<int>(newWeight));
        }
        return hr;
    }
    // Keep the caller's original format if the substitute fails.
    return g_origCreateTextFormat(self, familyName, collection, weight, style,
                                  stretch, size, locale, textFormat);
}

HRESULT STDMETHODCALLTYPE
CreateTextFormat6_Hook(IDWriteFactory6* self,
                       const WCHAR* familyName,
                       IDWriteFontCollection* collection,
                       const DWRITE_FONT_AXIS_VALUE* axisValues,
                       UINT32 axisCount,
                       FLOAT size,
                       const WCHAR* locale,
                       IDWriteTextFormat3** textFormat) {
    auto rt = familyName && (!axisCount || axisValues) ? GetDWriteRuntime()
                                                        : nullptr;
    if (!rt || !ShouldReplaceDWriteFamily(familyName, *rt)) {
        return g_origCreateTextFormat6(self, familyName, collection, axisValues,
                                       axisCount, size, locale, textFormat);
    }
    auto axes = ChooseDWriteAxes(axisValues, axisCount, *rt);
    auto* targetCollection =
        SelectDWriteCollection(collection, rt->dwFamily.c_str());
    HRESULT hr = g_origCreateTextFormat6(
        self, rt->dwFamily.c_str(), targetCollection, axes.data(),
        static_cast<UINT32>(axes.size()), size, locale, textFormat);
    if (SUCCEEDED(hr)) {
        return hr;
    }
    return g_origCreateTextFormat6(self, familyName, collection, axisValues,
                                   axisCount, size, locale, textFormat);
}

// XAML can create a default text format, then pick the face for each text
// run through font fallback without using the format's family.
std::shared_ptr<const Runtime> GetMappingRuntime(PCWSTR family) {
    if (!family || !*family) {
        return nullptr;
    }
    auto rt = GetDWriteRuntime();
    if (!rt || !ShouldReplaceDWriteFamily(family, *rt)) {
        return nullptr;
    }
    return rt;
}

ComPtr<IDWriteFontCollection> GetMappingCollection(
    IDWriteFontCollection* collection, const Runtime& rt) {
    ComPtr<IDWriteFontCollection> result =
        SelectDWriteCollection(collection, rt.dwFamily.c_str());
    if (!result && g_dwFactory) {
        g_dwFactory->GetSystemFontCollection(result.GetAddressOf(), FALSE);
    }
    return result;
}

void LogMappedFamily(PCWSTR family, const std::wstring& mappedFamily) {
    if (!g_loggedDwMapping.exchange(true, std::memory_order_relaxed)) {
        Wh_Log(L"DirectWrite drew text asked for in '%s' with '%s'", family,
               mappedFamily.c_str());
    }
}

HRESULT STDMETHODCALLTYPE MapCharacters_Hook(
    IDWriteFontFallback* self, IDWriteTextAnalysisSource* source,
    UINT32 position, UINT32 length, IDWriteFontCollection* collection,
    const WCHAR* family, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style,
    DWRITE_FONT_STRETCH stretch, UINT32* mappedLength, IDWriteFont** mappedFont,
    FLOAT* scale) {
    if (auto rt = GetMappingRuntime(family);
        rt && length && mappedLength && mappedFont && scale) {
        InternalScope scope;
        auto target = GetMappingCollection(collection, *rt);
        ComPtr<IDWriteFont> candidate;
        UINT32 candidateLength = 0;
        FLOAT candidateScale = 1.0f;
        if (target &&
            SUCCEEDED(g_origMapCharacters(
                self, source, position, length, target.Get(),
                rt->dwFamily.c_str(), ChooseDWriteWeight(weight, *rt), style,
                stretch, &candidateLength, candidate.GetAddressOf(),
                &candidateScale)) &&
            candidate && candidateLength) {
            ComPtr<IDWriteFontFamily> actual;
            if (SUCCEEDED(candidate->GetFontFamily(actual.GetAddressOf()))) {
                auto name = GetFamilyName(actual.Get());
                // Only take the run when the target really has these
                // characters; anything else keeps the normal fallback.
                if (IsTargetFamily(name, *rt)) {
                    LogMappedFamily(family, name);
                    *mappedLength = candidateLength;
                    *scale = candidateScale;
                    *mappedFont = candidate.Detach();
                    return S_OK;
                }
            }
        }
    }
    return g_origMapCharacters(self, source, position, length, collection,
                               family, weight, style, stretch, mappedLength,
                               mappedFont, scale);
}

HRESULT STDMETHODCALLTYPE MapCharacters1_Hook(
    IDWriteFontFallback1* self, IDWriteTextAnalysisSource* source,
    UINT32 position, UINT32 length, IDWriteFontCollection* collection,
    const WCHAR* family, const DWRITE_FONT_AXIS_VALUE* axisValues,
    UINT32 axisCount, UINT32* mappedLength, FLOAT* scale,
    IDWriteFontFace5** mappedFace) {
    if (auto rt = GetMappingRuntime(family);
        rt && length && (!axisCount || axisValues) && mappedLength &&
        mappedFace && scale) {
        InternalScope scope;
        auto target = GetMappingCollection(collection, *rt);
        auto axes = ChooseDWriteAxes(axisValues, axisCount, *rt);
        ComPtr<IDWriteFontFace5> candidate;
        UINT32 candidateLength = 0;
        FLOAT candidateScale = 1.0f;
        if (target &&
            SUCCEEDED(g_origMapCharacters1(
                self, source, position, length, target.Get(),
                rt->dwFamily.c_str(), axes.data(),
                static_cast<UINT32>(axes.size()), &candidateLength,
                &candidateScale, candidate.GetAddressOf())) &&
            candidate && candidateLength) {
            ComPtr<IDWriteLocalizedStrings> names;
            if (SUCCEEDED(candidate->GetFamilyNames(names.GetAddressOf()))) {
                auto name = GetLocalizedFamilyName(names.Get());
                if (IsTargetFamily(name, *rt)) {
                    LogMappedFamily(family, name);
                    *mappedLength = candidateLength;
                    *scale = candidateScale;
                    *mappedFace = candidate.Detach();
                    return S_OK;
                }
            }
        }
    }
    return g_origMapCharacters1(self, source, position, length, collection,
                                family, axisValues, axisCount, mappedLength,
                                scale, mappedFace);
}

// Every collection used by the range must hold the target, since a custom
// collection may lack it.
bool RangeHasTarget(IDWriteTextLayout* layout, DWRITE_TEXT_RANGE range,
                    const Runtime& rt) {
    UINT64 end = static_cast<UINT64>(range.startPosition) + range.length;
    UINT64 position = range.startPosition;
    while (position < end && position < UINT32_MAX) {
        ComPtr<IDWriteFontCollection> collection;
        DWRITE_TEXT_RANGE collectionRange{};
        if (FAILED(layout->GetFontCollection(static_cast<UINT32>(position),
                                             collection.GetAddressOf(),
                                             &collectionRange)) ||
            !SelectDWriteCollection(collection.Get(), rt.dwFamily.c_str())) {
            return false;
        }
        UINT64 next = static_cast<UINT64>(collectionRange.startPosition) +
                      collectionRange.length;
        if (next <= position) {
            return false;
        }
        position = next;
    }
    return position >= end;
}

HRESULT STDMETHODCALLTYPE SetFontFamilyName_Hook(IDWriteTextLayout* self,
                                                 const WCHAR* family,
                                                 DWRITE_TEXT_RANGE range) {
    if (auto rt = GetMappingRuntime(family);
        rt && range.length && RangeHasTarget(self, range, *rt)) {
        HRESULT hr = g_origSetFontFamilyName(self, rt->dwFamily.c_str(), range);
        if (SUCCEEDED(hr)) {
            if (!g_loggedDwLayout.exchange(true, std::memory_order_relaxed)) {
                Wh_Log(L"DirectWrite layout range '%s' became '%s'", family,
                       rt->dwFamily.c_str());
            }
            return hr;
        }
    }
    return g_origSetFontFamilyName(self, family, range);
}

HRESULT LayoutSetFamily(IDWriteTextLayout* layout, const WCHAR* family,
                        DWRITE_TEXT_RANGE range) {
    InternalScope scope;
    return g_origSetFontFamilyName
               ? g_origSetFontFamilyName(layout, family, range)
               : layout->SetFontFamilyName(family, range);
}

// File Explorer lays out text with formats it cached before the mod loaded,
// in boxes sized for Segoe UI. Swap those layouts and fit them, with the
// same floor as classic text: past 85% the original font draws the run.
void UpdateLayout(IDWriteTextLayout* layout, const WCHAR* text, UINT32 length,
                  IDWriteTextFormat* format) {
    if (!g_isExplorer || !layout || !format || !length ||
        IsProtectedText(text, length)) {
        return;
    }
    auto rt = GetDWriteRuntime();
    if (!rt) {
        return;
    }
    std::wstring family(format->GetFontFamilyNameLength() + 1, L'\0');
    if (FAILED(format->GetFontFamilyName(family.data(),
                                         static_cast<UINT32>(family.size())))) {
        return;
    }
    family.resize(wcsnlen(family.c_str(), family.size()));
    const bool already = IsTargetFamily(family, *rt);
    if (!already && !ShouldReplaceDWriteFamily(family, *rt)) {
        return;
    }
    DWRITE_TEXT_RANGE range{0, length};
    const DWRITE_FONT_WEIGHT originalWeight = format->GetFontWeight();
    if (!already) {
        if (!RangeHasTarget(layout, range, *rt)) {
            return;
        }
        auto requested = static_cast<DWRITE_FONT_WEIGHT>(
            std::max<int>(originalWeight, NameWeight(family)));
        auto weight = ChooseDWriteWeight(requested, *rt);
        if (weight != originalWeight) {
            layout->SetFontWeight(weight, range);
        }
        if (FAILED(LayoutSetFamily(layout, rt->dwFamily.c_str(), range))) {
            return;
        }
    }
    if (rt->settings.noFit) {
        return;
    }
    // Keep the requested size unless the actual control bounds need less.
    const float original = format->GetFontSize();
    const float floor = original * static_cast<float>(FontScope::kMinScale);
    const float widthLimit = layout->GetMaxWidth();
    const float heightLimit = layout->GetMaxHeight();
    float size = original;
    for (int attempt = 0; attempt < 16; ++attempt) {
        DWRITE_TEXT_METRICS metrics{};
        if (FAILED(layout->GetMetrics(&metrics))) {
            return;
        }
        float ratio = 1.0f;
        if (widthLimit > 0 && metrics.widthIncludingTrailingWhitespace > widthLimit) {
            ratio = std::min(ratio,
                             widthLimit / metrics.widthIncludingTrailingWhitespace);
        }
        if (heightLimit > 0 && metrics.height > heightLimit) {
            ratio = std::min(ratio, heightLimit / metrics.height);
        }
        if (ratio >= 0.999f) {
            return;
        }
        float next = size * ratio * 0.98f;
        if (next < floor) {
            if (already) {
                // The format itself is the target; the floor is the limit.
                layout->SetFontSize(floor, range);
            } else {
                // Past the floor the original font draws the run.
                LayoutSetFamily(layout, family.c_str(), range);
                layout->SetFontWeight(originalWeight, range);
                layout->SetFontSize(original, range);
            }
            return;
        }
        size = next;
        if (FAILED(layout->SetFontSize(size, range))) {
            return;
        }
    }
}

HRESULT STDMETHODCALLTYPE CreateTextLayout_Hook(IDWriteFactory* factory,
                                                const WCHAR* text,
                                                UINT32 length,
                                                IDWriteTextFormat* format,
                                                FLOAT width,
                                                FLOAT height,
                                                IDWriteTextLayout** output) {
    HRESULT hr = g_origCreateTextLayout(factory, text, length, format, width,
                                        height, output);
    if (SUCCEEDED(hr) && output && !t_internal) {
        UpdateLayout(*output, text, length, format);
    }
    return hr;
}

HRESULT STDMETHODCALLTYPE CreateGdiLayout_Hook(IDWriteFactory* factory,
                                               const WCHAR* text,
                                               UINT32 length,
                                               IDWriteTextFormat* format,
                                               FLOAT width,
                                               FLOAT height,
                                               FLOAT pixelsPerDip,
                                               const DWRITE_MATRIX* transform,
                                               BOOL natural,
                                               IDWriteTextLayout** output) {
    HRESULT hr = g_origCreateGdiLayout(factory, text, length, format, width,
                                       height, pixelsPerDip, transform, natural,
                                       output);
    if (SUCCEEDED(hr) && output && !t_internal) {
        UpdateLayout(*output, text, length, format);
    }
    return hr;
}

// ---------------------------------------------------------------------------
// Hook installation
// ---------------------------------------------------------------------------

template <typename T>
bool InstallFunctionHook(HMODULE module, const char* name, T hook, T* original) {
    if (!module) {
        return false;
    }
    auto target = reinterpret_cast<T>(GetProcAddress(module, name));
    if (!target) {
        Wh_Log(L"GetProcAddress failed for %S", name);
        return false;
    }
    if (!WindhawkUtils::SetFunctionHook(target, hook, original)) {
        Wh_Log(L"SetFunctionHook failed for %S", name);
        return false;
    }
    return true;
}

template <typename T>
bool InstallVtableHook(void** vtable, size_t index, T hook, T* original) {
    if (!vtable) {
        return false;
    }
    auto target = reinterpret_cast<T>(vtable[index]);
    if (!target) {
        Wh_Log(L"Vtable entry %zu is null", index);
        return false;
    }
    if (!WindhawkUtils::SetFunctionHook(target, hook, original)) {
        Wh_Log(L"SetFunctionHook failed for vtable entry %zu", index);
        return false;
    }
    return true;
}

void InstallGdiHooks() {
    // Explicit system exports avoid MinGW import thunks inside this DLL.
    HMODULE user32 =
        LoadLibraryExW(L"user32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    HMODULE gdi32 =
        LoadLibraryExW(L"gdi32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    HMODULE uxtheme =
        LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);

    InstallFunctionHook(user32, "DrawTextW", DrawTextW_Hook, &g_origDrawTextW);
    InstallFunctionHook(user32, "DrawTextExW", DrawTextExW_Hook,
                        &g_origDrawTextExW);
    InstallFunctionHook(gdi32, "TextOutW", TextOutW_Hook, &g_origTextOutW);
    InstallFunctionHook(gdi32, "ExtTextOutW", ExtTextOutW_Hook,
                        &g_origExtTextOutW);
    InstallFunctionHook(gdi32, "GetTextExtentPoint32W", Extent_Hook,
                        &g_origExtent);
    InstallFunctionHook(gdi32, "GetTextExtentExPointW", ExtentEx_Hook,
                        &g_origExtentEx);
    InstallFunctionHook(uxtheme, "DrawThemeText", DrawThemeText_Hook,
                        &g_origDrawThemeText);
    InstallFunctionHook(uxtheme, "DrawThemeTextEx", DrawThemeTextEx_Hook,
                        &g_origDrawThemeTextEx);

    InstallFunctionHook(gdi32, "CreateFontIndirectW", CreateFontIndirectW_Hook,
                        &g_origCreateFontIndirectW);
    InstallFunctionHook(gdi32, "CreateFontIndirectA", CreateFontIndirectA_Hook,
                        &g_origCreateFontIndirectA);
    InstallFunctionHook(gdi32, "CreateFontIndirectExW",
                        CreateFontIndirectExW_Hook,
                        &g_origCreateFontIndirectExW);
    InstallFunctionHook(gdi32, "CreateFontIndirectExA",
                        CreateFontIndirectExA_Hook,
                        &g_origCreateFontIndirectExA);
    InstallFunctionHook(gdi32, "CreateFontW", CreateFontW_Hook,
                        &g_origCreateFontW);
    InstallFunctionHook(gdi32, "CreateFontA", CreateFontA_Hook,
                        &g_origCreateFontA);
}

void InstallDirectWriteHooks() {
    if (!g_dwFactory) {
        Wh_Log(L"No DirectWrite factory; modern text stays as it is");
        return;
    }
    // IDWriteFactory: IUnknown 0..2, CreateTextFormat 15, CreateTextLayout 18,
    // CreateGdiCompatibleTextLayout 19.
    void** vtable = *reinterpret_cast<void***>(g_dwFactory);
    InstallVtableHook(vtable, 15, CreateTextFormat_Hook,
                      &g_origCreateTextFormat);
    InstallVtableHook(vtable, 18, CreateTextLayout_Hook,
                      &g_origCreateTextLayout);
    InstallVtableHook(vtable, 19, CreateGdiLayout_Hook, &g_origCreateGdiLayout);

    ComPtr<IDWriteTextFormat> testFormat;
    ComPtr<IDWriteTextLayout> testLayout;
    if (SUCCEEDED(g_dwFactory->CreateTextFormat(
            L"Segoe UI", nullptr, DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 14.0f,
            L"en-us", testFormat.GetAddressOf())) &&
        SUCCEEDED(g_dwFactory->CreateTextLayout(L"x", 1, testFormat.Get(),
                                                100.0f, 100.0f,
                                                testLayout.GetAddressOf()))) {
        auto** layoutVtable = *reinterpret_cast<void***>(testLayout.Get());
        InstallVtableHook(layoutVtable, 31, SetFontFamilyName_Hook,
                          &g_origSetFontFamilyName);
    } else {
        Wh_Log(L"Could not create a DirectWrite layout to install font hooks");
    }

    ComPtr<IDWriteFactory6> factory6;
    if (SUCCEEDED(g_dwFactory->QueryInterface(
            IID_PPV_ARGS(factory6.GetAddressOf())))) {
        // IDWriteFactory6::CreateTextFormat (variable-axis overload).
        void** vtable6 = *reinterpret_cast<void***>(factory6.Get());
        InstallVtableHook(vtable6, 54, CreateTextFormat6_Hook,
                          &g_origCreateTextFormat6);
    }

    ComPtr<IDWriteFactory2> factory2;
    ComPtr<IDWriteFontFallback> fallback;
    if (SUCCEEDED(g_dwFactory->QueryInterface(
            IID_PPV_ARGS(factory2.GetAddressOf()))) &&
        SUCCEEDED(factory2->GetSystemFontFallback(fallback.GetAddressOf())) &&
        fallback) {
        auto** fallbackVtable = *reinterpret_cast<void***>(fallback.Get());
        InstallVtableHook(fallbackVtable, 3, MapCharacters_Hook,
                          &g_origMapCharacters);
        ComPtr<IDWriteFontFallback1> fallback1;
        if (SUCCEEDED(fallback.As(&fallback1))) {
            auto** fallback1Vtable = *reinterpret_cast<void***>(fallback1.Get());
            InstallVtableHook(fallback1Vtable, 4, MapCharacters1_Hook,
                              &g_origMapCharacters1);
        }
    } else {
        Wh_Log(L"Could not get the DirectWrite system font fallback");
    }
}

bool CreateDWriteFactory() {
    if (!g_dwModule) {
        g_dwModule =
            LoadLibraryExW(L"dwrite.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    }
    if (!g_dwModule) {
        Wh_Log(L"Failed to load dwrite.dll");
        return false;
    }
    using DWriteCreateFactory_t =
        HRESULT(WINAPI*)(DWRITE_FACTORY_TYPE, REFIID, IUnknown**);
    auto createFactory = reinterpret_cast<DWriteCreateFactory_t>(
        GetProcAddress(g_dwModule, "DWriteCreateFactory"));
    if (!createFactory) {
        Wh_Log(L"DWriteCreateFactory was not found");
        return false;
    }
    HRESULT hr =
        createFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                      reinterpret_cast<IUnknown**>(&g_dwFactory));
    if (FAILED(hr) || !g_dwFactory) {
        g_dwFactory = nullptr;
        Wh_Log(L"DWriteCreateFactory failed (hr=0x%08X)",
               static_cast<unsigned>(hr));
        return false;
    }
    return true;
}

}  // namespace

// ---------------------------------------------------------------------------
// Windhawk callbacks
// ---------------------------------------------------------------------------

BOOL Wh_ModInit() {
    auto processName = GetProcessBaseName();
    g_isExplorer = processName == L"explorer.exe";
    CreateDWriteFactory();
    auto runtime = BuildRuntime();
    PublishRuntime(runtime);
    LogInitInfo(*runtime, processName);
    // The hooks always go in, so installing the font or changing a setting
    // later works without restarting the app. They pass through while idle.
    InstallGdiHooks();
    InstallDirectWriteHooks();
    return TRUE;
}

void Wh_ModSettingsChanged() {
    if (!g_dwFactory) {
        CreateDWriteFactory();
    }
    auto runtime = BuildRuntime();
    PublishRuntime(runtime);
    LogInitInfo(*runtime, GetProcessBaseName());
    Wh_Log(L"Settings applied. Text already on screen may keep the old font "
           L"until the app draws or lays it out again.");
}

void Wh_ModUninit() {
    PublishRuntime(nullptr);
    if (g_dwFactory) {
        g_dwFactory->Release();
        g_dwFactory = nullptr;
    }
    Wh_Log(L"Uninitialized");
}
