// ==WindhawkMod==
// @id              shell-font-changer
// @name            Shell Font Changer
// @description     Use any font in Explorer, Start, Search and Settings without breaking icons or emoji
// @version         1.1.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @license         MIT
// @include         explorer.exe
// @include         StartMenuExperienceHost.exe
// @include         ShellExperienceHost.exe
// @include         SearchHost.exe
// @include         ShellHost.exe
// @include         SystemSettings.exe
// @compilerOptions -lgdi32 -luxtheme -ldwrite
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Shell Font Changer

Replace the font used across File Explorer and the Windows shell with any font
you have installed.

![Shell Font Changer preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/shell-font-changer.png)

## Features

- **Changes text in File Explorer, Start, Search and Settings.**
- **Icons and emoji stay intact.** Symbol and icon fonts keep their own
  glyphs, so buttons never turn into empty boxes.
- **Keeps font weights.** Semibold and bold text stays semibold and bold.
- **Covers classic, themed and modern text**, including DirectWrite layouts.
- **Nothing is written to the registry**, so turning it off is fully clean.

## How to use

Type an installed font family name in the settings, such as
`FiraCode Nerd Font` or `Inter`. Leave it empty to turn the mod off.

Some apps, such as Chromium browsers, draw text with their own fonts and keep
them. Windows that were already open may need to be reopened.

Disable the original Explorer Font Changer before enabling this mod.

## Credits

Based on [Explorer Font Changer](https://windhawk.net/mods/explorer-font-changer)
by Gabriela Cristei. MIT.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- font:
  - name: FiraCode Nerd Font
    $name: Font family
    $description: Installed font family. Empty or None keeps the original font.
  $name: Text font
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <uxtheme.h>
#include <dwrite.h>
#include <string>
#include <cwctype>
#include <algorithm>
#include <vector>

namespace policy {
std::wstring target;
bool enabled = false;

bool protectedFace(const wchar_t* face, BYTE charset = DEFAULT_CHARSET) {
    if (charset == SYMBOL_CHARSET) return true;
    std::wstring name = face ? face : L"";
    std::transform(name.begin(), name.end(), name.begin(), towlower);
    for (const auto* word : {L"symbol", L"icons", L"mdl2", L"emoji", L"wingdings", L"webdings", L"marlett", L"fontawesome", L"font awesome"}) {
        if (name.find(word) != std::wstring::npos) return true;
    }
    return false;
}

bool protectedText(const wchar_t* text, UINT length) {
    if (!text) return true;
    for (UINT i = 0; i < length; ++i) {
        unsigned c = text[i];
        // PUA and surrogate pairs can encode shell icons, emoji or scripts.
        // Keep the complete original run rather than interpreting glyph IDs.
        if ((c >= 0xE000 && c <= 0xF8FF) || (c >= 0xD800 && c <= 0xDFFF)) return true;
    }
    return false;
}
UINT textLength(const wchar_t* text, int length) {
    return !text ? 0 : length < 0 ? static_cast<UINT>(wcslen(text)) : static_cast<UINT>(length);
}
// GDI draws these format controls as nothing when a face lacks them, so they
// must not force a fallback. Explorer wraps every formatted date in U+200E.
bool invisibleControl(unsigned c) {
    return c < L' ' || c == 0x061C || (c >= 0x200B && c <= 0x200F) || (c >= 0x202A && c <= 0x202E) ||
           (c >= 0x2061 && c <= 0x2064) || (c >= 0x206A && c <= 0x206F) || (c >= 0xFE00 && c <= 0xFE0F) ||
           c == 0xFEFF;
}
int nameWeight(const wchar_t* face) {
    std::wstring name = face ? face : L"";
    std::transform(name.begin(), name.end(), name.begin(), towlower);
    // Longer names first, so " semibold" is not read as " bold".
    const std::pair<const wchar_t*, int> suffixes[] = {
        {L" extrabold", 800}, {L" ultrabold", 800}, {L" semibold", 600}, {L" demibold", 600},
        {L" black", 900}, {L" heavy", 900}, {L" bold", 700}, {L" medium", 500}};
    for (const auto& [suffix, weight] : suffixes) {
        size_t size = wcslen(suffix);
        if (name.size() > size && name.compare(name.size() - size, size, suffix) == 0) return weight;
    }
    return 0;
}
}

// Scope the selected font to one call. Restoring it before DeleteObject is
// required even for DT_CALCRECT, nested drawing calls and failed draws.
class FontScope {
    HDC dc = nullptr;
    HFONT replacement = nullptr;
    HGDIOBJ previous = nullptr;
public:
    FontScope(HDC hdc, const wchar_t* text, UINT length, bool glyphIndices = false) {
        if (!policy::enabled || !hdc || glyphIndices || policy::protectedText(text, length)) return;
        LOGFONTW font{};
        if (GetObjectW(GetCurrentObject(hdc, OBJ_FONT), sizeof(font), &font) != sizeof(font)) return;
        // '@' faces are vertical CJK layouts; a horizontal face would rotate them.
        if (font.lfFaceName[0] == L'@' || policy::protectedFace(font.lfFaceName, font.lfCharSet) ||
            _wcsicmp(font.lfFaceName, policy::target.c_str()) == 0) return;
        // Face names such as "Segoe UI Black" carry their weight in the name.
        TEXTMETRICW metrics{};
        if (GetTextMetricsW(hdc, &metrics) && metrics.tmWeight > font.lfWeight) font.lfWeight = metrics.tmWeight;
        font.lfWeight = std::max<LONG>(font.lfWeight, policy::nameWeight(font.lfFaceName));
        // A script charset the target lacks would make the mapper pick another face.
        font.lfCharSet = DEFAULT_CHARSET;
        wcscpy_s(font.lfFaceName, policy::target.c_str());
        replacement = CreateFontIndirectW(&font);
        if (!replacement) return;
        previous = SelectObject(hdc, replacement);
        if (!previous || previous == HGDI_ERROR) {
            DeleteObject(replacement);
            replacement = nullptr;
            return;
        }
        dc = hdc;
        wchar_t realized[LF_FACESIZE]{};
        // DirectWrite family names are not always GDI face names. Never let
        // the mapper substitute a third font for a name GDI does not know.
        bool missing = !GetTextFaceW(dc, LF_FACESIZE, realized) || _wcsicmp(realized, policy::target.c_str()) != 0;
        if (!missing && length) {
            std::vector<WORD> glyphs(length);
            missing = GetGlyphIndicesW(dc, text, length, glyphs.data(), GGI_MARK_NONEXISTING_GLYPHS) == GDI_ERROR;
            for (UINT i = 0; !missing && i < length; ++i) {
                if (glyphs[i] == 0xffff && !policy::invisibleControl(text[i])) missing = true;
            }
        }
        // GDI font linking varies by family. Preserve the original run
        // when the replacement lacks a character instead of drawing tofu.
        if (missing) {
            SelectObject(dc, previous);
            DeleteObject(replacement);
            replacement = nullptr;
            dc = nullptr;
        }
    }
    ~FontScope() {
        if (dc) SelectObject(dc, previous);
        if (replacement) DeleteObject(replacement);
    }
    FontScope(const FontScope&) = delete;
    FontScope& operator=(const FontScope&) = delete;
};

decltype(&DrawTextW) drawTextOriginal;
int WINAPI drawTextHook(HDC dc, LPCWSTR text, int length, LPRECT rect, UINT flags) {
    FontScope font(dc, text, policy::textLength(text, length));
    return drawTextOriginal(dc, text, length, rect, flags);
}
decltype(&DrawTextExW) drawTextExOriginal;
int WINAPI drawTextExHook(HDC dc, LPWSTR text, int length, LPRECT rect, UINT flags, LPDRAWTEXTPARAMS params) {
    FontScope font(dc, text, policy::textLength(text, length));
    return drawTextExOriginal(dc, text, length, rect, flags, params);
}
decltype(&TextOutW) textOutOriginal;
BOOL WINAPI textOutHook(HDC dc, int x, int y, LPCWSTR text, int length) {
    FontScope font(dc, text, length < 0 ? 0 : length);
    return textOutOriginal(dc, x, y, text, length);
}
decltype(&ExtTextOutW) extTextOutOriginal;
BOOL WINAPI extTextOutHook(HDC dc, int x, int y, UINT flags, const RECT* rect, LPCWSTR text, UINT length, const INT* widths) {
    // Pre-shaped glyph indices belong to the original face, not the new face.
    FontScope font(dc, text, length, (flags & ETO_GLYPH_INDEX) != 0 || widths != nullptr);
    return extTextOutOriginal(dc, x, y, flags, rect, text, length, widths);
}
decltype(&GetTextExtentPoint32W) extentOriginal;
BOOL WINAPI extentHook(HDC dc, LPCWSTR text, int length, LPSIZE size) {
    FontScope font(dc, text, length < 0 ? 0 : length);
    return extentOriginal(dc, text, length, size);
}
decltype(&GetTextExtentExPointW) extentExOriginal;
BOOL WINAPI extentExHook(HDC dc, LPCWSTR text, int length, int maxExtent, LPINT fit, LPINT widths, LPSIZE size) {
    FontScope font(dc, text, length < 0 ? 0 : length);
    return extentExOriginal(dc, text, length, maxExtent, fit, widths, size);
}
decltype(&DrawThemeText) themeOriginal;
HRESULT WINAPI themeHook(HTHEME theme, HDC dc, int part, int state, LPCWSTR text, int length, DWORD flags, DWORD flags2, const RECT* rect) {
    FontScope font(dc, text, policy::textLength(text, length));
    return themeOriginal(theme, dc, part, state, text, length, flags, flags2, rect);
}
decltype(&DrawThemeTextEx) themeExOriginal;
HRESULT WINAPI themeExHook(HTHEME theme, HDC dc, int part, int state, LPCWSTR text, int length, DWORD flags, LPRECT rect, const DTTOPTS* opts) {
    FontScope font(dc, text, policy::textLength(text, length));
    return themeExOriginal(theme, dc, part, state, text, length, flags, rect, opts);
}

void updateLayout(IDWriteTextLayout* layout, const WCHAR* text, UINT length, IDWriteTextFormat* format) {
    if (!policy::enabled || !layout || !format || !length || policy::protectedText(text, length)) return;
    std::wstring family(format->GetFontFamilyNameLength() + 1, L'\0');
    if (FAILED(format->GetFontFamilyName(family.data(), static_cast<UINT>(family.size()))) || policy::protectedFace(family.c_str())) return;
    IDWriteFontCollection* collection = nullptr;
    if (FAILED(format->GetFontCollection(&collection)) || !collection) return;
    UINT index = 0;
    BOOL exists = FALSE;
    collection->FindFamilyName(policy::target.c_str(), &index, &exists);
    collection->Release();
    // A custom font collection without the target keeps its original family.
    if (!exists) return;
    DWRITE_TEXT_RANGE range{0, length};
    // Legacy GDI names such as "Segoe UI Semibold" carry their weight in the
    // name, and DirectWrite does not resolve them. Keep that weight.
    auto weight = static_cast<DWRITE_FONT_WEIGHT>(policy::nameWeight(family.c_str()));
    if (weight > format->GetFontWeight()) layout->SetFontWeight(weight, range);
    layout->SetFontFamilyName(policy::target.c_str(), range);
}
using LayoutFn = HRESULT (STDMETHODCALLTYPE*)(IDWriteFactory*, const WCHAR*, UINT32, IDWriteTextFormat*, FLOAT, FLOAT, IDWriteTextLayout**);
LayoutFn layoutOriginal;
HRESULT STDMETHODCALLTYPE layoutHook(IDWriteFactory* factory, const WCHAR* text, UINT32 length, IDWriteTextFormat* format, FLOAT width, FLOAT height, IDWriteTextLayout** output) {
    auto hr = layoutOriginal(factory, text, length, format, width, height, output);
    if (SUCCEEDED(hr) && output) updateLayout(*output, text, length, format);
    return hr;
}
using GdiLayoutFn = HRESULT (STDMETHODCALLTYPE*)(IDWriteFactory*, const WCHAR*, UINT32, IDWriteTextFormat*, FLOAT, FLOAT, FLOAT, const DWRITE_MATRIX*, BOOL, IDWriteTextLayout**);
GdiLayoutFn gdiLayoutOriginal;
HRESULT STDMETHODCALLTYPE gdiLayoutHook(IDWriteFactory* factory, const WCHAR* text, UINT32 length, IDWriteTextFormat* format, FLOAT width, FLOAT height, FLOAT scale, const DWRITE_MATRIX* transform, BOOL natural, IDWriteTextLayout** output) {
    auto hr = gdiLayoutOriginal(factory, text, length, format, width, height, scale, transform, natural, output);
    if (SUCCEEDED(hr) && output) updateLayout(*output, text, length, format);
    return hr;
}

bool loadSettings() {
    const auto* name = Wh_GetStringSetting(L"font.name");
    policy::target = name ? name : L"";
    Wh_FreeStringSetting(name);
    policy::enabled = !policy::target.empty() && _wcsicmp(policy::target.c_str(), L"None") != 0;
    if (!policy::enabled) return true;
    if (policy::target.size() >= LF_FACESIZE || policy::protectedFace(policy::target.c_str())) {
        Wh_Log(L"Choose a text font family shorter than 32 characters.");
        return false;
    }
    IDWriteFactory* factory = nullptr;
    if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&factory)))) return false;
    IDWriteFontCollection* fonts = nullptr;
    BOOL exists = FALSE;
    UINT index = 0;
    if (SUCCEEDED(factory->GetSystemFontCollection(&fonts))) {
        fonts->FindFamilyName(policy::target.c_str(), &index, &exists);
        fonts->Release();
    }
    factory->Release();
    if (!exists) Wh_Log(L"Font family is not installed: %s", policy::target.c_str());
    return exists != FALSE;
}

BOOL Wh_ModInit() {
    if (!loadSettings()) return FALSE;
    bool ok = true;
    #define HOOK(fn, hook, original) ok = Wh_SetFunctionHook(reinterpret_cast<void*>(fn), reinterpret_cast<void*>(hook), reinterpret_cast<void**>(&original)) && ok
    auto user = LoadLibraryExW(L"user32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    auto gdi = LoadLibraryExW(L"gdi32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    auto theme = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!user || !gdi || !theme) return FALSE;
    // Explicit exports avoid MinGW import thunks inside this mod DLL.
    HOOK(GetProcAddress(user, "DrawTextW"), drawTextHook, drawTextOriginal);
    HOOK(GetProcAddress(user, "DrawTextExW"), drawTextExHook, drawTextExOriginal);
    HOOK(GetProcAddress(gdi, "TextOutW"), textOutHook, textOutOriginal);
    HOOK(GetProcAddress(gdi, "ExtTextOutW"), extTextOutHook, extTextOutOriginal);
    HOOK(GetProcAddress(gdi, "GetTextExtentPoint32W"), extentHook, extentOriginal);
    HOOK(GetProcAddress(gdi, "GetTextExtentExPointW"), extentExHook, extentExOriginal);
    HOOK(GetProcAddress(theme, "DrawThemeText"), themeHook, themeOriginal);
    HOOK(GetProcAddress(theme, "DrawThemeTextEx"), themeExHook, themeExOriginal);
    IDWriteFactory* factory = nullptr;
    if (SUCCEEDED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&factory)))) {
        // IDWriteFactory: IUnknown 0..2; the two layout methods are 18 and 19.
        // Format objects stay untouched, so cached icon formats remain usable.
        auto table = *reinterpret_cast<void***>(factory);
        HOOK(table[18], layoutHook, layoutOriginal);
        HOOK(table[19], gdiLayoutHook, gdiLayoutOriginal);
        factory->Release();
    } else {
        ok = false;
    }
    #undef HOOK
    Wh_Log(L"DavidHiFi font changer initialized. Font: %s", policy::target.c_str());
    return ok;
}
BOOL Wh_ModSettingsChanged(BOOL* reload) {
    *reload = TRUE;
    return TRUE;
}
