// ==WindhawkMod==
// @id              explorer-font-changer-davidhifi
// @name            Explorer Font Changer by DavidHiFi
// @description     Change shell text fonts while preserving Windows icons and emoji.
// @version         1.0.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi/davids-windhawk-mods
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
# Explorer Font Changer by DavidHiFi

Fork of Explorer Font Changer 0.2 by Gabriela Cristei.
Original: https://github.com/ramensoftware/windhawk-mods/blob/main/mods/explorer-font-changer.wh.cpp

Changes GDI, themed text, and DirectWrite layouts in Explorer and Windows shell
hosts, Search, Start, and Settings. Symbol,
icon, emoji, and private-use character runs keep their original fonts.
GDI replacements restore the original selected font before deleting their handles.
Settings changes request a mod reload, so drawing threads never read partially
updated settings. No font substitution registry entries are written.

Choose an installed family name, such as FiraCode Nerd Font. Empty or None
disables substitution. Disable the original Explorer Font Changer before
enabling this fork. Glow is omitted because the original undocumented glow
path does not preserve DrawTextEx parameters or bounded text buffers.

Scope is the Windows shell by default. This does not promise to change text in every
Windows application. XAML controls that set their own fonts after layout
creation, Chromium, and applications outside the include list can keep their
own fonts. Do not add active audio or communications applications to the list.
Existing cached DirectWrite layouts may retain their fonts until recreated.
Disabling the mod restores drawing hooks; existing UI caches may need to refresh.
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
        if (policy::protectedFace(font.lfFaceName, font.lfCharSet) || _wcsicmp(font.lfFaceName, policy::target.c_str()) == 0) return;
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
    }
    ~FontScope() {
        if (dc) SelectObject(dc, previous);
        if (replacement) DeleteObject(replacement);
    }
    FontScope(const FontScope&) = delete;
    FontScope& operator=(const FontScope&) = delete;
};

decltype(&CreateFontIndirectW) createFontOriginal;
HFONT WINAPI createFontHook(const LOGFONTW* requested) {
    if (!policy::enabled || !requested || policy::protectedFace(requested->lfFaceName, requested->lfCharSet)) return createFontOriginal(requested);
    // Substitute common UI families at creation so shaped glyph runs and
    // controls that cache HFONT objects measure and draw with the same face.
    const auto* face = requested->lfFaceName;
    if (_wcsicmp(face, L"Segoe UI") && _wcsicmp(face, L"Segoe UI Variable") &&
        _wcsicmp(face, L"Tahoma") && _wcsicmp(face, L"Microsoft Sans Serif") &&
        _wcsicmp(face, L"MS Shell Dlg") && _wcsicmp(face, L"MS Shell Dlg 2")) return createFontOriginal(requested);
    auto font = *requested;
    wcscpy_s(font.lfFaceName, policy::target.c_str());
    return createFontOriginal(&font);
}

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
    if (exists) layout->SetFontFamilyName(policy::target.c_str(), DWRITE_TEXT_RANGE{0, length});
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
    HOOK(DrawTextW, drawTextHook, drawTextOriginal);
    HOOK(DrawTextExW, drawTextExHook, drawTextExOriginal);
    HOOK(TextOutW, textOutHook, textOutOriginal);
    HOOK(ExtTextOutW, extTextOutHook, extTextOutOriginal);
    HOOK(GetTextExtentPoint32W, extentHook, extentOriginal);
    HOOK(GetTextExtentExPointW, extentExHook, extentExOriginal);
    HOOK(CreateFontIndirectW, createFontHook, createFontOriginal);
    HOOK(DrawThemeText, themeHook, themeOriginal);
    HOOK(DrawThemeTextEx, themeExHook, themeExOriginal);
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
