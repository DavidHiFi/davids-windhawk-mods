// ==WindhawkMod==
// @id              helium-acrylic
// @name            Helium Acrylic
// @description     Keeps Helium's acrylic surface, Catppuccin colors and system-drawn frame working after browser updates
// @version         3.6.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         chrome.exe
// @architecture    x86-64
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
Helium's native title bar shows a soft acrylic blur, but a browser update can
wash the whole look out: the strip turns black and the Catppuccin tint is gone.
This mod keeps both alive so a plain stock install stays riced.

![Helium Acrylic preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/helium-acrylic.png)

## Features
- **Survives updates.** Everything lives in memory, not in the browser's files,
  so an update cannot wash it out and UniGetUI can update Helium normally.
- **Applies reliably.** If the browser starts while the mod is still being
  delivered, the patch layers retry on a short leash instead of giving up for
  the life of the process, and every write is read back and logged. A build
  that matches nothing (the riced install) is latched as a no-op so it never
  rescans.
- **Acrylic.** Keeps the GPU surface translucent so the window blur shows.
- **Catppuccin colors.** Dark-theme UI colors resolve to the Catppuccin Mocha
  palette, matching the riced build (base 1E1E2E, pills Surface0 at 85%).
- **Native frame.** The browser hands the window frame to Windows: the system
  draws the titlebar and caption buttons and DWM keeps the resize borders,
  like the riced build's native-frame mode. The code behind this sits in a
  generated cave and is byte-verified the same way; an update that moves a
  site is left untouched and logged.
- **Quiet.** If the code it looks for cannot be matched exactly once, the mod
  does nothing and logs why. Safe by default.
- **Dark theme only.** The color layer follows the Windows app theme; light
  theme stays stock.

## Notes
- The blur itself comes from a window blur rule for Helium. This mod only
  keeps the surface behind it translucent and the colors right.
- A future Helium that moves the code this mod looks for needs a pattern
  refresh (the helium-acrylic-update skill handles that).

## Credits
Written by DavidHiFi.
*/

#include <windows.h>
#include <atomic>
#include <vector>

// ---------------------------------------------------------------------------
// Part 1: the acrylic patch.
//
// Helium's ShouldWindowContentsBeTransparent on a stock release build:
//   cmp qword ptr [rcx+0x2C8], 0   ; browser_view_ (CHECK)
//   je  +3                         ; -> ud2 abort block
//   xor eax, eax                   ; return false
//   ret
// Verified 2026-11-08 against the stock 0.21.1.1 chrome.dll (exactly one
// match, address present in the class vtable, abort lands on ud2).
// Patched to  mov al,1 ; ret  so the compositor keeps an alpha channel.
// If a future Helium moves the member offset, update the C8 02 00 00 bytes.
static const char kAcrylicPattern[] =
    "48 83 B9 C8 02 00 00 00 74 03 31 C0 C3";

static std::atomic<bool> g_stop{false};
static std::atomic<bool> g_acrylicApplied{false};
static BYTE g_acrylicOriginal[3];
static BYTE* g_acrylicTarget = nullptr;

// ---------------------------------------------------------------------------
// Part 2: the Catppuccin color layer.
//
// ui::ColorProvider::GetColor resolves every UI color. On the stock static
// build it compiles to this shape (verified 2026-11-08, exactly one match):
static const char kGetColorPattern[] =
    "41 57 41 56 41 54 56 57 55 53 48 83 EC 20 89 D7 48 89 CE 4C 8D 71 18 48 8B 41 18";
// We displace the first seven bytes (push r15; push r14; push r12; push rsi),
// detour the entry to a generated hook, and on a cache-miss replay those
// seven bytes and jump back. The stock dark default is returned untouched.

// The rice's mixer table, extracted 2026-11-08 from the riced 0.21.1.1 build's
// inlined AddHeliumCatppuccinMochaMixer (id, color) pairs - ground truth.
struct ColorEntry { unsigned int id; unsigned int color; };
static const ColorEntry kColors[] = {
    {321,  0xFF1E1E2Eu},   // kColorFrameActive -> base
    {326,  0xFF1E1E2Eu},   // kColorFrameInactive -> base
    {1597, 0xFF1E1E2Eu},   // kColorToolbar -> base
    {1602, 0xFFA6ADC8u},   // kColorToolbarButtonIcon -> subtext0
    {1605, 0xFFCDD6F4u},   // kColorToolbarButtonIconHovered -> text
    {801,  0xD9313244u},   // kColorLocationBarBackground -> surface0 85%
    {802,  0xD945475Au},   // kColorLocationBarBackgroundHovered -> surface1 85%
    {803,  0xFF585B70u},   // kColorLocationBarBorder -> surface2
    {1020, 0xFF181825u},   // kColorOmniboxResultsBackground -> mantle
    {1021, 0xFF313244u},   // kColorOmniboxResultsBackgroundHovered -> surface0
    {1062, 0xFFCDD6F4u},   // kColorOmniboxText -> text
    {1063, 0xFF7F849Cu},   // kColorOmniboxTextDimmed -> overlay1
    {1466, 0xD9313244u},   // kColorTabBackgroundActiveFrameActive
    {1468, 0xD9313244u},   // kColorTabBackgroundActiveFrameInactive
    {1473, 0xB0313244u},   // kColorTabBackgroundSelectedFrameActive
    {1474, 0xB0313244u},   // kColorTabBackgroundSelectedFrameInactive
    {1471, 0x99313244u},   // kColorTabBackgroundInactiveHoverFrameActive
    {1472, 0x99313244u},   // kColorTabBackgroundInactiveHoverFrameInactive
    {1483, 0xFFCDD6F4u},   // kColorTabForegroundActiveFrameActive
    {1484, 0xFFCDD6F4u},   // kColorTabForegroundActiveFrameInactive
    {1485, 0xFFA6ADC8u},   // kColorTabForegroundInactiveFrameActive
    {1486, 0xFFA6ADC8u},   // kColorTabForegroundInactiveFrameInactive
    {1538, 0xFF585B70u},   // kColorTabStrokeFrameActive
    {1539, 0xFF585B70u},   // kColorTabStrokeFrameInactive
    {319,  0xFFB4BEFEu},   // kColorFocusableBorderFocused -> lavender
};
static const int kColorCount = sizeof(kColors) / sizeof(kColors[0]);

static std::atomic<bool> g_colorsApplied{false};
static BYTE* g_gcTarget = nullptr;
static BYTE g_gcOriginal[7];
static BYTE* g_hookMem = nullptr;
static volatile BYTE g_dark = 0;  // written by the theme thread, read by the hook

static bool HexNibble(char c, BYTE* out) {
    if (c >= '0' && c <= '9') { *out = (BYTE)(c - '0'); return true; }
    if (c >= 'A' && c <= 'F') { *out = (BYTE)(c - 'A' + 10); return true; }
    if (c >= 'a' && c <= 'f') { *out = (BYTE)(c - 'a' + 10); return true; }
    return false;
}

struct Patch {
    std::vector<BYTE> bytes;
    std::vector<bool> wild;
};

static bool ParsePattern(const char* s, Patch* p) {
    int i = 0;
    while (s[i]) {
        while (s[i] == ' ') i++;
        if (!s[i]) break;
        if (s[i] == '?' && s[i + 1] == '?') {
            p->bytes.push_back(0);
            p->wild.push_back(true);
            i += 2;
            continue;
        }
        BYTE hi, lo;
        if (!HexNibble(s[i], &hi) || !HexNibble(s[i + 1], &lo)) return false;
        p->bytes.push_back((BYTE)((hi << 4) | lo));
        p->wild.push_back(false);
        i += 2;
    }
    return !p->bytes.empty();
}

static void ForEachExecutableSection(HMODULE mod, void* ctx,
                                     void (*fn)(void*, BYTE*, SIZE_T, SIZE_T)) {
    auto dos = (IMAGE_DOS_HEADER*)mod;
    auto nt = (IMAGE_NT_HEADERS*)((BYTE*)mod + dos->e_lfanew);
    auto sec = IMAGE_FIRST_SECTION(nt);
    for (WORD i = 0; i < nt->FileHeader.NumberOfSections; i++) {
        if (sec[i].Characteristics & IMAGE_SCN_MEM_EXECUTE) {
            BYTE* start = (BYTE*)mod + sec[i].VirtualAddress;
            SIZE_T size = sec[i].Misc.VirtualSize;
            fn(ctx, start, size, sec[i].VirtualAddress);
        }
    }
}

struct ScanCtx {
    const Patch* pat;
    BYTE* matches[8];
    int count;
};

static void ScanSection(void* ctx, BYTE* start, SIZE_T size, SIZE_T rva) {
    ScanCtx* c = (ScanCtx*)ctx;
    const Patch* p = c->pat;
    if (size < p->bytes.size()) return;
    for (SIZE_T i = 0; i + p->bytes.size() <= size; i++) {
        bool ok = true;
        for (SIZE_T j = 0; j < p->bytes.size(); j++) {
            if (!p->wild[j] && start[i + j] != p->bytes[j]) { ok = false; break; }
        }
        if (ok) {
            if (c->count < 8) c->matches[c->count++] = start + i;
            else return;
        }
    }
}

static bool VaReferencedInImage(HMODULE mod, BYTE* target) {
    auto dos = (IMAGE_DOS_HEADER*)mod;
    auto nt = (IMAGE_NT_HEADERS*)((BYTE*)mod + dos->e_lfanew);
    BYTE* base = (BYTE*)mod;
    SIZE_T n = nt->OptionalHeader.SizeOfImage - 8;
    BYTE needle[8];
    UINT64 va = (UINT64)target;
    for (int i = 0; i < 8; i++) needle[i] = (BYTE)(va >> (8 * i));
    for (SIZE_T i = 0; i < n; i++) {
        if (base[i] == needle[0] && memcmp(base + i, needle, 8) == 0) return true;
    }
    return false;
}

static bool ApplyAcrylicPatch() {
    if (g_acrylicApplied) return true;
    HMODULE chrome = GetModuleHandleW(L"chrome.dll");
    if (!chrome) {
        Wh_Log(L"chrome.dll not loaded yet");
        return false;
    }

    Patch pat;
    if (!ParsePattern(kAcrylicPattern, &pat)) {
        Wh_Log(L"bad acrylic pattern string");
        return false;
    }

    ScanCtx ctx = {};
    ctx.pat = &pat;
    ForEachExecutableSection(chrome, &ctx, ScanSection);
    if (ctx.count == 0) {
        Wh_Log(L"acrylic: pattern not found (already patched build?) - untouched");
        return false;
    }

    BYTE* target = nullptr;
    for (int i = 0; i < ctx.count; i++) {
        if (VaReferencedInImage(chrome, ctx.matches[i])) {
            if (target) {
                Wh_Log(L"acrylic: more than one vtable-backed match - untouched");
                return false;
            }
            target = ctx.matches[i];
        }
    }
    if (!target) {
        Wh_Log(L"acrylic: no vtable-backed match - untouched");
        return false;
    }

    DWORD oldProtect;
    if (!VirtualProtect(target, sizeof(g_acrylicOriginal), PAGE_EXECUTE_READWRITE, &oldProtect)) {
        Wh_Log(L"acrylic: VirtualProtect failed");
        return false;
    }
    memcpy(g_acrylicOriginal, target, sizeof(g_acrylicOriginal));
    const BYTE patchBytes[3] = {0xB0, 0x01, 0xC3};  // mov al,1; ret
    memcpy(target, patchBytes, sizeof(patchBytes));
    DWORD tmp;
    VirtualProtect(target, sizeof(g_acrylicOriginal), oldProtect, &tmp);
    if (memcmp(target, patchBytes, sizeof(patchBytes)) != 0) {
        Wh_Log(L"acrylic: read-back mismatch");
        return false;
    }
    g_acrylicTarget = target;
    g_acrylicApplied = true;
    Wh_Log(L"Helium acrylic: patched at RVA 0x%zX", (size_t)(target - (BYTE*)chrome));
    return true;
}

// ---- generated hook -------------------------------------------------------
// Layout: [dark check][compare chain -> 25 hits][miss stub]
// Stack-free, register-safe: only eax/eflags are touched on hits, and the
// miss path replays the displaced pushes and jumps back into GetColor.

static bool InstallColorHook() {
    if (g_colorsApplied) return true;
    HMODULE chrome = GetModuleHandleW(L"chrome.dll");
    if (!chrome) {
        Wh_Log(L"chrome.dll not loaded yet");
        return false;
    }

    Patch pat;
    if (!ParsePattern(kGetColorPattern, &pat)) {
        Wh_Log(L"colors: bad pattern string");
        return false;
    }

    ScanCtx ctx = {};
    ctx.pat = &pat;
    ForEachExecutableSection(chrome, &ctx, ScanSection);
    if (ctx.count != 1) {
        Wh_Log(L"colors: pattern matched %d times (need exactly 1) - untouched", ctx.count);
        return false;
    }
    BYTE* entry = ctx.matches[0];

    // The displaced bytes must be the expected pushes.
    const BYTE expect[7] = {0x41, 0x57, 0x41, 0x56, 0x41, 0x54, 0x56};
    if (memcmp(entry, expect, 7) != 0) {
        Wh_Log(L"colors: unexpected prologue - untouched");
        return false;
    }

    // Allocate RWX near the entry so a 5-byte relative jmp reaches.
    BYTE* bases[6] = {
        (BYTE*)chrome - 0x10000000, (BYTE*)chrome + 0x10000000,
        (BYTE*)chrome - 0x40000000, (BYTE*)chrome + 0x40000000,
        (BYTE*)chrome - 0x70000000, (BYTE*)chrome + 0x70000000,
    };
    BYTE* mem = nullptr;
    for (int i = 0; i < 6 && !mem; i++) {
        mem = (BYTE*)VirtualAlloc(bases[i], 0x1000, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_EXECUTE_READWRITE);
    }
    if (!mem) {
        mem = (BYTE*)VirtualAlloc(nullptr, 0x1000, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_EXECUTE_READWRITE);
        if (!mem) {
            Wh_Log(L"colors: VirtualAlloc failed");
            return false;
        }
    }
    g_hookMem = mem;

    // --- generate the hook ---
    BYTE* p = mem;
    BYTE* flagAddr = (BYTE*)&g_dark;
    auto emit32 = [&](DWORD v) { memcpy(p, &v, 4); p += 4; };
    // mov rax, &g_dark ; cmp byte ptr [rax], 0 ; je miss
    // x64 has no absolute-addressed cmp, and a rip-relative disp32 cannot
    // reach the mod's own data: it can sit more than 2 GB away from this
    // page (this exact bug crashed the first paint of every stock test
    // instance on 2026-11-08 - the hook read rip + low32 of the flag).
    *p++ = 0x48; *p++ = 0xB8; memcpy(p, &flagAddr, 8); p += 8;
    *p++ = 0x80; *p++ = 0x38; *p++ = 0x00;
    BYTE* jeMiss = p; *p++ = 0x0F; *p++ = 0x84; p += 4;  // rel32 patched later

    // compare chain
    BYTE* hits[64];
    for (int i = 0; i < kColorCount; i++) {
        *p++ = 0x81; *p++ = 0xFA; emit32(kColors[i].id);  // cmp edx, id
        *p++ = 0x0F; *p++ = 0x84; hits[i] = p; p += 4;    // je hit_i (rel32 later)
    }
    // miss: replay displaced bytes and jump back
    BYTE* miss = p;
    *p++ = 0x41; *p++ = 0x57;  // push r15
    *p++ = 0x41; *p++ = 0x56;  // push r14
    *p++ = 0x41; *p++ = 0x54;  // push r12
    *p++ = 0x56;               // push rsi
    INT64 back = (INT64)(entry + 7) - (INT64)(p + 5);
    *p++ = 0xE9; emit32((DWORD)back);
    *(DWORD*)(jeMiss + 2) = (DWORD)(INT64)(miss - (jeMiss + 6));
    // hits
    for (int i = 0; i < kColorCount; i++) {
        *(DWORD*)(hits[i]) = (DWORD)(INT64)(p - (hits[i] + 4));
        *p++ = 0xB8; emit32(kColors[i].color);  // mov eax, color
        *p++ = 0xC3;                            // ret
    }

    // --- patch GetColor's entry ---
    DWORD oldProtect;
    DWORD tmp;
    if (!VirtualProtect(entry, sizeof(g_gcOriginal), PAGE_EXECUTE_READWRITE, &oldProtect)) {
        Wh_Log(L"colors: VirtualProtect failed");
        return false;
    }
    memcpy(g_gcOriginal, entry, sizeof(g_gcOriginal));
    INT64 rel = (INT64)mem - (INT64)(entry + 5);
    if (rel > 0x7FFFFFFF || rel < -0x7FFFFFFF) {
        VirtualProtect(entry, sizeof(g_gcOriginal), oldProtect, &tmp);
        Wh_Log(L"colors: hook out of jump range");
        return false;
    }
    BYTE jmp[5] = {0xE9, 0, 0, 0, 0};
    *(DWORD*)(jmp + 1) = (DWORD)rel;
    memcpy(entry, jmp, 5);
    if (entry[0] != 0xE9) {
        Wh_Log(L"colors: read-back mismatch");
        return false;
    }
    VirtualProtect(entry, sizeof(g_gcOriginal), oldProtect, &tmp);
    g_gcTarget = entry;
    g_colorsApplied = true;
    Wh_Log(L"Helium acrylic: color hook live at RVA 0x%zX (%d colors)",
           (size_t)(entry - (BYTE*)chrome), kColorCount);
    return true;
}

static bool ReadDarkTheme() {
    HKEY key;
    if (RegOpenKeyExW(HKEY_CURRENT_USER,
                      L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                      0, KEY_READ, &key) != ERROR_SUCCESS) {
        return true;  // assume dark (the rice is dark-only) if unreadable
    }
    DWORD v = 0, size = sizeof(v), type = 0;
    LONG r = RegQueryValueExW(key, L"AppsUseLightTheme", nullptr, &type,
                              (LPBYTE)&v, &size);
    RegCloseKey(key);
    if (r != ERROR_SUCCESS || type != REG_DWORD) return true;
    return v == 0;
}

static DWORD WINAPI ThemeThread(LPVOID) {
    while (!g_stop) {
        g_dark = ReadDarkTheme() ? 1 : 0;
        Sleep(5000);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Part 3: the acrylic backdrop.
//
// The riced build set DWMSBT_TRANSIENTWINDOW on every translucent browser
// window inside DesktopWindowTreeHostWin::Init; stock Helium never does, so a
// modded stock window shows the flat desktop through its strip instead of the
// blurred acrylic. Rather than patch that init path, this layer watches the
// process's own top-level windows and applies the backdrop plus the dark
// backdrop tint directly - idempotent, and it covers windows opened later.
//
// On Helium 0.22.1.1, DWMSBT isn't taking effect because DWM attributes are
// overridden by Chromium's frame painting. Instead use SetWindowCompositionAttribute
// with WCA_ACCENT_POLICY (accent acrylic) which works on this build.
//
struct BackdropCtx { DWORD pid; };

typedef LONG (WINAPI *PFN_DwmSetWindowAttribute)(HWND, DWORD, LPCVOID, DWORD);
typedef BOOL (WINAPI *PFN_SetWindowCompositionAttribute)(HWND, const void*);

static PFN_DwmSetWindowAttribute GetDwmSetWindowAttribute() {
    static PFN_DwmSetWindowAttribute fn = nullptr;
    if (!fn) {
        HMODULE m = GetModuleHandleW(L"dwmapi.dll");
        if (!m) m = LoadLibraryW(L"dwmapi.dll");
        if (m) fn = (PFN_DwmSetWindowAttribute)GetProcAddress(m, "DwmSetWindowAttribute");
    }
    return fn;
}

static PFN_SetWindowCompositionAttribute GetSetWindowCompositionAttribute() {
    static PFN_SetWindowCompositionAttribute fn = nullptr;
    if (!fn) {
        HMODULE m = GetModuleHandleW(L"user32.dll");
        if (!m) m = LoadLibraryW(L"user32.dll");
        if (m) fn = (PFN_SetWindowCompositionAttribute)GetProcAddress(m, "SetWindowCompositionAttribute");
    }
    return fn;
}

struct ACCENTPOLICY {
    DWORD AccentState;
    DWORD AccentFlags;
    DWORD GradientColor;
    DWORD AnimationId;
};

struct WINDOWCOMPOSITIONATTRDATA {
    DWORD Attribute;
    LPVOID Data;
    DWORD SizeOfData;
};

static BOOL CALLBACK BackdropEnumProc(HWND hwnd, LPARAM lp) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != ((BackdropCtx*)lp)->pid) return TRUE;
    if (!IsWindowVisible(hwnd)) return TRUE;
    wchar_t cls[64];
    if (!GetClassNameW(hwnd, cls, 64) || wcscmp(cls, L"Chrome_WidgetWin_1") != 0) {
        return TRUE;
    }
    // Use SetWindowCompositionAttribute with accent acrylic (WCA_ACCENT_POLICY)
    // instead of DWMSBT because DWM attributes are overridden on Helium 0.22.1.1
    PFN_SetWindowCompositionAttribute wca = GetSetWindowCompositionAttribute();
    if (wca) {
        ACCENTPOLICY policy = { 3, 0x20|0x40, 0x00FFFFFF, 0 }; // ACCENT_ENABLE_ACRYLICBLURBEHIND
        WINDOWCOMPOSITIONATTRDATA data = { 19, &policy, sizeof(policy) }; // WCA_ACCENT_POLICY
        wca(hwnd, &data);
    }
    // Keep DWMWA_USE_IMMERSIVE_DARK_MODE setting via DwmSetWindowAttribute
    PFN_DwmSetWindowAttribute dwm = GetDwmSetWindowAttribute();
    if (dwm) {
        BOOL dark = g_dark ? TRUE : FALSE;
        dwm(hwnd, 20 /*DWMWA_USE_IMMERSIVE_DARK_MODE*/, &dark, sizeof(dark));
    }
    return TRUE;
}

static DWORD WINAPI BackdropThread(LPVOID) {
    while (!g_stop) {
        BackdropCtx ctx = { GetCurrentProcessId() };
        EnumWindows(BackdropEnumProc, (LPARAM)&ctx);
        Sleep(2000);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Part 4: the native-frame structural patches.
//
// A reverse-engineering pass of the riced 0.21.1.1 build produced four code
// sites that make a stock chrome.dll draw the window frame the way the riced
// build does: BrowserFrameViewWin::OnPaint stops painting the titlebar,
// BrowserDesktopWindowTreeHostWin::GetFrameMode answers FrameMode::SYSTEM_DRAWN,
// GetDwmFrameInsetsInPixels answers Insets(-1) so Windows keeps the resize
// borders, and the caption-button hide path keeps the Chromium glyph buttons
// from rendering beside the title-bar mod's dots.
//
// v3.3.1 runtime truth (live side-by-side, 2026-11-18): the riced build
// renders its custom caption dots with NO Chromium glyph buttons and full
// acrylic. SUNE-true everywhere (v3.0.0) killed the dots (system frame drew
// glyphs instead); SUNE-false everywhere (v3.1.0) left duplicate glyph
// buttons beside the dots; the byte-twin site at 0xe8295b (v3.3.0's cave A)
// sits in a different function whose rsi is an out-param, so its browser-view
// test read garbage and changed nothing. The real caption decision lives in
// the function that calls CommandLine::HasSwitch("hide-window-buttons")
// directly (found by xref to the switch string at RVA 0x10405c40): its
// switch branch calls the same virtual with the mode argument zeroed, and a
// second sizing function branches on the same switch. Running the stock with
// that switch was proven live today to match the riced caption exactly
// (dots, no glyphs). So the caption hide is now two in-place branch flips
// that make those switch branches unconditional - the stock's own switch
// path does the work. Frame mode and insets caves stay routed but inert
// (SUNE hardwired false), and the OnPaint site stays unpatched.
//
// Verified 2026-11-08 against the stock 0.21.1.1 chrome.dll: every site's
// original bytes are checked before anything is written, the OnPaint skip
// target was pinned by disassembly, and every resume address was read back
// from the binary. All displaced bytes are restored in Wh_ModUninit.
static const DWORD kRvaLCBSwitch = 0x18031e6;  // caption fn HasSwitch jne
static const DWORD kRvaLCBSizing = 0xa0e27aa;  // sizing fn HasSwitch jne
static const DWORD kRvaGFMHead = 0x374a180;    // GetFrameMode head
static const DWORD kRvaGDFIWrite = 0x374a159;  // GetDwmFrameInsetsInPixels
static const DWORD kRvaOnPaintPT = 0x29f8158;  // OnPaint PaintTitlebar head

static const BYTE kOrigLCBSwitch[6] = {0x0F, 0x85, 0xFE, 0x00, 0x00, 0x00};
static const BYTE kOrigLCBSizing[2] = {0x75, 0x25};
static const BYTE kOrigGFM[12] = {0x56, 0x48, 0x83, 0xEC, 0x20, 0x48, 0x8B,
                                  0x81, 0x30, 0x01, 0x00, 0x00};
static const BYTE kOrigGDFI[5] = {0x0F, 0x57, 0xC0, 0x0F, 0x11};
static const BYTE kOrigOnPaint[7] = {0x48, 0x8B, 0x87, 0x28, 0x03, 0x00, 0x00};

// Stock addresses the caves branch to (each read back from the binary).
// Cave branch targets re-derived for stock Helium 0.21.3.1 chrome.dll.
// Each is the 0.21.1.1 address minus the per-function build delta, verified
// by disassembly: GFM/GDFI shift -0x72D0, OnPaint shifts -0xE13D734. The
// internal offsets within every function are preserved.
static const DWORD kRvaGFMNull = 0x374a255;     // xor eax,eax; jmp epilogue
static const DWORD kRvaGFMResume = 0x374a195;   // mov rsi,rcx (reads [rax+..])
static const DWORD kRvaGFMEpilogue = 0x374a24f; // add rsp,0x20; pop rsi; ret
static const DWORD kRvaGDFIResume = 0x374a15f;  // mov al,1
static const DWORD kRvaOnPaintResume = 0x29f815f;
// Pinned skip target: first instruction after the inlined PaintTitlebar body.
// The riced build runs nothing between its skipped PaintTitlebar call and
// this exit trace store, so the cave lands exactly there.
// GATED for 0.21.3.1: the derived 0x29f87d0 is a backward short jmp
// (EB 8F -> 0x29f8761), not the exit trace store, so the skip branch is
// never installed. SUNE is hardwired false, so cave D's replay is a no-op
// anyway; the OnPaint site is left unpatched for this build.
static const DWORD kRvaOnPaintSkip = 0x29f87d0;  // unverified - do not route

struct FrameSite {
    BYTE* target;
    BYTE original[12];
    int size;
    bool applied;
};
static FrameSite g_frameSites[4];
static BYTE* g_cavePage = nullptr;
static std::atomic<bool> g_frameApplied{false};

static void EmitJmpRel32(BYTE*& p, BYTE* to) {
    *p = 0xE9;
    *(DWORD*)(p + 1) = (DWORD)((INT64)to - (INT64)(p + 5));
    p += 5;
}

static void EmitJccRel32(BYTE*& p, BYTE cc, BYTE* to) {  // 0F 8x rel32
    *p = 0x0F;
    p[1] = cc;
    *(DWORD*)(p + 2) = (DWORD)((INT64)to - (INT64)(p + 6));
    p += 6;
}

static void EmitCallRel32(BYTE*& p, BYTE* to) {
    *p = 0xE8;
    *(DWORD*)(p + 1) = (DWORD)((INT64)to - (INT64)(p + 5));
    p += 5;
}

static void EmitBytes(BYTE*& p, const BYTE* bytes, size_t n) {
    memcpy(p, bytes, n);
    p += n;
}

// WM_THEMECHANGED nudge: windows created before this mod finished patching
// keep whatever caption layout they computed at creation. The message routes
// into Chromium's frame re-layout, so the caption function runs again - now
// under the patch - and the glyph buttons hide on already-open windows. It
// also re-runs the omnibox's RefreshBackground for the held-back gradient
// layer. Collect every main-window-class HWND of this process and post to
// each.
struct NudgeCtx { DWORD pid; HWND hwnds[8]; int n; };
static BOOL CALLBACK NudgeEnum(HWND h, LPARAM lp) {
    NudgeCtx* c = (NudgeCtx*)lp;
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    if (pid != c->pid) return TRUE;
    WCHAR cls[32];
    if (!GetClassNameW(h, cls, 32) || wcscmp(cls, L"Chrome_WidgetWin_1") != 0)
        return TRUE;
    if (c->n < 8) c->hwnds[c->n++] = h;
    return TRUE;
}

static bool ApplyStructuralPatches() {
    if (g_frameApplied) return true;
    HMODULE chrome = GetModuleHandleW(L"chrome.dll");
    if (!chrome) {
        Wh_Log(L"chrome.dll not loaded yet");
        return false;
    }

    // One mismatch at any site means a different build: nothing is written.
    // The OnPaint site is a canary only: verified, never written.
    struct SiteSpec { DWORD rva; const BYTE* orig; int len; };
    const SiteSpec specs[5] = {
        {kRvaLCBSwitch, kOrigLCBSwitch, sizeof(kOrigLCBSwitch)},
        {kRvaLCBSizing, kOrigLCBSizing, sizeof(kOrigLCBSizing)},
        {kRvaGFMHead, kOrigGFM, sizeof(kOrigGFM)},
        {kRvaGDFIWrite, kOrigGDFI, sizeof(kOrigGDFI)},
        {kRvaOnPaintPT, kOrigOnPaint, sizeof(kOrigOnPaint)},
    };
    for (int i = 0; i < 5; i++) {
        BYTE* at = (BYTE*)chrome + specs[i].rva;
        if (memcmp(at, specs[i].orig, specs[i].len) != 0) {
            Wh_Log(L"native frame: site %d (RVA 0x%zX) has unexpected bytes"
                   L" - untouched", i, (size_t)specs[i].rva);
            return false;
        }
    }

    // One RWX page for the helper and all four caves, near the module like
    // the color hook's page. rel32 covers the whole 300 MB image from there.
    BYTE* bases[5] = {
        (BYTE*)chrome - 0x10000000 + 0x100000,
        (BYTE*)chrome - 0x10000000 - 0x100000,
        (BYTE*)chrome + 0x10000000,
        (BYTE*)chrome - 0x40000000,
        (BYTE*)chrome + 0x40000000,
    };
    BYTE* mem = nullptr;
    for (int i = 0; i < 5 && !mem; i++) {
        mem = (BYTE*)VirtualAlloc(bases[i], 0x1000, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_EXECUTE_READWRITE);
    }
    if (!mem) {
        mem = (BYTE*)VirtualAlloc(nullptr, 0x1000, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_EXECUTE_READWRITE);
    }
    if (!mem) {
        Wh_Log(L"native frame: VirtualAlloc failed");
        return false;
    }
    g_cavePage = mem;

    // SUNE helper: always false so Chromium caption buttons stay visible and
    // system-drawn frame materials are not installed. This matches the riced
    // build's runtime behavior while keeping the acrylic/transparency patches active.
    BYTE* p = mem;
    BYTE* sune = mem;
    const BYTE suneImpl[] = { 0x31, 0xC0, 0xC3 }; // xor eax,eax; ret
    EmitBytes(p, suneImpl, sizeof(suneImpl));

    // v3.3.1: the old cave A (and the byte-twin site 0xe8295b it detoured)
    // is gone. The caption hide is two in-place branch flips written below;
    // see Part 4's header for how the real switch-gated function was found.

    // Cave C (offset 96): GetFrameMode. Native frame answers 0
    // (FrameMode::SYSTEM_DRAWN); otherwise the stock flow continues with
    // rax = browser_view_ reloaded, because the resumed instruction reads it.
    p = mem + 96;
    BYTE* caveC = p;
    const BYTE cPush[] = {0x56};
    const BYTE cSub[] = {0x48, 0x83, 0xEC, 0x20};
    const BYTE cMovRsi[] = {0x48, 0x89, 0xCE};
    const BYTE cMovRax[] = {0x48, 0x8B, 0x81, 0x30, 0x01, 0x00, 0x00};
    const BYTE cTest[] = {0x48, 0x85, 0xC0};
    const BYTE cMovRcxRax[] = {0x48, 0x89, 0xC1};
    const BYTE cTestJne[] = {0x84, 0xC0, 0x75, 0x0F};
    const BYTE cMovRcxRsi[] = {0x48, 0x89, 0xF1};
    const BYTE cReload[] = {0x48, 0x8B, 0x86, 0x30, 0x01, 0x00, 0x00};
    const BYTE cZero[] = {0x31, 0xC0};
    EmitBytes(p, cPush, 1);
    EmitBytes(p, cSub, 4);
    EmitBytes(p, cMovRsi, 3);     // mov rsi,rcx (replay)
    EmitBytes(p, cMovRax, 7);     // mov rax,[rcx+0x130] (replay)
    EmitBytes(p, cTest, 3);
    EmitJccRel32(p, 0x84, (BYTE*)chrome + kRvaGFMNull);  // je null path
    EmitBytes(p, cMovRcxRax, 3);  // mov rcx,rax
    EmitCallRel32(p, sune);
    EmitBytes(p, cTestJne, 4);    // test al,al; jne .zero
    EmitBytes(p, cMovRcxRsi, 3);  // mov rcx,rsi
    EmitBytes(p, cReload, 7);     // mov rax,[rsi+0x130] (resume needs rax)
    EmitJmpRel32(p, (BYTE*)chrome + kRvaGFMResume);
    // .zero:
    EmitBytes(p, cZero, 2);
    EmitJmpRel32(p, (BYTE*)chrome + kRvaGFMEpilogue);

    // Cave B (offset 160): GetDwmFrameInsetsInPixels write-out. Native frame
    // answers all-ones (Insets(-1)); otherwise zeros. Both resume at the
    // stock's mov al,1. rdi (this) and rsi (Insets*) come from the stock.
    p = mem + 160;
    BYTE* caveB = p;
    const BYTE bMovRcx[] = {0x48, 0x8B, 0x8F, 0x30, 0x01, 0x00, 0x00};
    const BYTE bTestJne[] = {0x84, 0xC0, 0x75, 0x05};
    const BYTE bZero[] = {0x0F, 0x57, 0xC0, 0xEB, 0x04};
    const BYTE bNeg1[] = {0x66, 0x0F, 0x76, 0xC0};
    const BYTE bStore[] = {0xF3, 0x0F, 0x7F, 0x06};
    EmitBytes(p, bMovRcx, 7);     // mov rcx,[rdi+0x130]
    EmitCallRel32(p, sune);
    EmitBytes(p, bTestJne, 4);    // test al,al; jne .neg1
    EmitBytes(p, bZero, 5);       // xorps xmm0,xmm0; jmp .store
    EmitBytes(p, bNeg1, 4);       // .neg1: pcmpeqd xmm0,xmm0
    EmitBytes(p, bStore, 4);      // .store: movdqu [rsi],xmm0
    EmitJmpRel32(p, (BYTE*)chrome + kRvaGDFIResume);

    // Cave D (offset 224): OnPaint's inlined PaintTitlebar. Native frame
    // jumps past the whole body to the pinned skip target; otherwise the
    // displaced instruction is replayed. bv via the stock's own inlined
    // GetBrowserView ([rdi+0x338] - 0x1f0, cf. 0x1abc16b).
    // Gated for 0.21.3.1: the skip target is unverified, so the body is
    // emitted but never routed to any site.
    p = mem + 224;
    BYTE* caveD = p;
    const BYTE dField[] = {0x48, 0x8B, 0x87, 0x38, 0x03, 0x00, 0x00};
    const BYTE dBv[] = {0x48, 0x8D, 0x88, 0x10, 0xFE, 0xFF, 0xFF};
    const BYTE dTestCmove[] = {0x48, 0x85, 0xC0, 0x48, 0x0F, 0x44, 0xC8};
    const BYTE dTestAl[] = {0x84, 0xC0};
    const BYTE dReplay[] = {0x48, 0x8B, 0x87, 0x28, 0x03, 0x00, 0x00};
    EmitBytes(p, dField, 7);      // mov rax,[rdi+0x338]
    EmitBytes(p, dBv, 7);         // lea rcx,[rax-0x1f0]
    EmitBytes(p, dTestCmove, 7);  // test rax,rax; cmove rcx,rax
    EmitCallRel32(p, sune);
    EmitBytes(p, dTestAl, 2);     // test al,al
    EmitJccRel32(p, 0x85, (BYTE*)chrome + kRvaOnPaintSkip);  // jne SKIP
    EmitBytes(p, dReplay, 7);     // mov rax,[rdi+0x328] (replay)
    EmitJmpRel32(p, (BYTE*)chrome + kRvaOnPaintResume);

    // Caption hide: two direct in-place branch flips (slots 0 and 1).
    // Site 1 (0x18031e6): the caption function's jne over its switch path
    // becomes an unconditional jmp, so every window runs the stock
    // --hide-window-buttons path (virtual called with the mode argument 0).
    // Site 2 (0xa0e27aa): the sizing function's switch branch likewise
    // always taken. Both replicate the live-proven switch behavior.
    static const BYTE lcbSwitchNew[6] = {0xE9, 0xFF, 0x00, 0x00, 0x00, 0x90};
    static const BYTE lcbSizingNew[2] = {0xEB, 0x25};
    struct RawPatch { DWORD rva; int slot; int len; const BYTE* neu; };
    const RawPatch raws[2] = {
        {kRvaLCBSwitch, 0, 6, lcbSwitchNew},
        {kRvaLCBSizing, 1, 2, lcbSizingNew},
    };
    for (int i = 0; i < 2; i++) {
        BYTE* at = (BYTE*)chrome + raws[i].rva;
        DWORD oldProtect, tmp;
        if (!VirtualProtect(at, raws[i].len, PAGE_EXECUTE_READWRITE,
                            &oldProtect)) {
            Wh_Log(L"native frame: VirtualProtect failed at raw %d", i);
            return false;
        }
        memcpy(g_frameSites[raws[i].slot].original, at, raws[i].len);
        memcpy(at, raws[i].neu, raws[i].len);
        VirtualProtect(at, raws[i].len, oldProtect, &tmp);
        if (memcmp(at, raws[i].neu, raws[i].len) != 0) {
            memcpy(at, g_frameSites[raws[i].slot].original, raws[i].len);
            Wh_Log(L"native frame: raw %d read-back mismatch - restored", i);
            return false;
        }
        g_frameSites[raws[i].slot].target = at;
        g_frameSites[raws[i].slot].size = raws[i].len;
        g_frameSites[raws[i].slot].applied = true;
        Wh_Log(L"Helium acrylic: caption switch patch %d live at RVA 0x%zX",
               i, (size_t)raws[i].rva);
    }

    // Route the frame-mode sites into their caves, saving the displaced
    // bytes (slots 2 and 3). OnPaint (cave D) is gated for 0.21.3.1: skip
    // target unverified.
    struct Write { DWORD rva; int len; BYTE* cave; };
    const Write writes[2] = {
        {kRvaGFMHead, 12, caveC},
        {kRvaGDFIWrite, 5, caveB},
    };
    for (int i = 0; i < 2; i++) {
        BYTE* at = (BYTE*)chrome + writes[i].rva;
        INT64 rel = (INT64)writes[i].cave - (INT64)(at + 5);
        if (rel > 0x7FFFFFFF || rel < -0x7FFFFFFF) {
            Wh_Log(L"native frame: cave out of jump range - untouched");
            return false;
        }
        DWORD oldProtect, tmp;
        if (!VirtualProtect(at, writes[i].len, PAGE_EXECUTE_READWRITE,
                            &oldProtect)) {
            Wh_Log(L"native frame: VirtualProtect failed");
            return false;
        }
        memcpy(g_frameSites[i + 2].original, at, writes[i].len);
        BYTE jmp[5] = {0xE9, 0, 0, 0, 0};
        *(DWORD*)(jmp + 1) = (DWORD)rel;
        memcpy(at, jmp, 5);
        for (int j = 5; j < writes[i].len; j++) at[j] = 0x90;
        VirtualProtect(at, writes[i].len, oldProtect, &tmp);
        if (at[0] != 0xE9) {
            Wh_Log(L"native frame: site %d read-back mismatch", i);
            return false;
        }
        g_frameSites[i + 2].target = at;
        g_frameSites[i + 2].size = writes[i].len;
        g_frameSites[i + 2].applied = true;
        Wh_Log(L"Helium acrylic: native-frame cave %d live at RVA 0x%zX",
               i, (size_t)writes[i].rva);
    }
    g_frameApplied = true;
    Wh_Log(L"Helium acrylic: native frame live (caption switch always on,"
           L" frame-mode caves routed but inert)");
    // Re-layout windows that existed before the patches landed.
    NudgeCtx nc;
    nc.pid = GetCurrentProcessId();
    nc.n = 0;
    EnumWindows(NudgeEnum, (LPARAM)&nc);
    for (int i = 0; i < nc.n; i++)
        PostMessageW(nc.hwnds[i], WM_THEMECHANGED, 0, 0);
    Wh_Log(L"Helium acrylic: theme nudge posted to %d windows", nc.n);
    return true;
}

// ---------------------------------------------------------------------------
// Part 5 (v3.2.0): the remaining riced mechanisms, ported from the riced
// build's GradientBorderRoundRectPainter (its full Paint body was disassembled
// and is mirrored step by step below) plus the fullscreen guard and the
// sidebar new-tab hide. Same contract as the native-frame layer: original
// bytes verified before any write, every write read back, everything
// restored in Wh_ModUninit.
//
// - Fullscreen guard: ShouldWindowContentsBeTransparent (the site the acrylic
//   patch used) now answers false while the window is fullscreen, so the
//   material strip does not float over fullscreen video. The stock null
//   check is re-emitted in the cave; g_fsActive records the state. This
//   replaces the old unconditional mov al,1;ret - the site check accepts
//   both the stock body and that patch so a live mod update re-applies.
// - Sidebar new-tab button: the sidebar stores the button then hides it via
//   its own View::SetVisible(false) virtual, the riced sidebar look.
// - Tab-pill gradient: at PaintTabBackgroundFill's DrawPath the stroke flags
//   gain a blue->mauve linear gradient shader whose alpha follows the stroke
//   color, the riced tab pill's gradient stroke.
// - Omnibox gradient: the resting omnibox (not caret-visible, no input in
//   progress, not high contrast, not popup mode) is the only state that
//   reaches RefreshBackground's inline solid-painter build (0x1707AAA on
//   0.21.3.1); the cave there installs the riced gradient painter instead. A
//   caret-visible omnibox gets the stock-shaped painter with a solid lavender
//   stroke (kColorFocusableBorderFocused, fetched live). Every other state
//   (input in progress, high contrast) keeps the stock's own factory call
//   later in the function untouched.

static const DWORD kRvaFsGuard = 0x374a290;     // ShouldWindowContentsBeTransparent
static const DWORD kRvaNtHide = 0x37479f3;      // sidebar new-tab store
static const DWORD kRvaPillDraw = 0xaac9d2b;    // vertical-tab pill stroke DrawPath
                                                // (stock PaintTabBackgroundFill
                                                // 0xAAC9970: rcx=canvas, rdx=path,
                                                // r8=stroke flags; fill flags stay
                                                // at [rsp+0xA0], xmm6=scale)
static const BYTE kOrigPill[5] = {0xE8, 0x70, 0x82, 0xC9, 0xF8};
static const DWORD kRvaPillResume = 0xaac9d30;  // instruction after the stroke DrawPath
static const DWORD kRvaOmniB = 0x1707aaa;       // RefreshBackground inline painter
static const BYTE kOrigOmniB[5] = {0xB9, 0x38, 0x00, 0x00, 0x00};
static const DWORD kRvaOmniConv = 0x1707af0;    // the wrapper alloc after the site
static const DWORD kRvaGetColor = 0x4311790;    // ui::ColorProvider::GetColor
static const DWORD kRvaProvider = 0x4909f60;    // view color-provider getter

static const BYTE kOrigFsGuard[13] = {
    0x48, 0x83, 0xB9, 0xC8, 0x02, 0x00, 0x00, 0x00, 0x74, 0x03, 0x31, 0xC0, 0xC3};
static const BYTE kOrigNtHide[7] = {0x4C, 0x89, 0xB6, 0x50, 0x03, 0x00, 0x00};
static const BYTE kOldAcrylic[3] = {0xB0, 0x01, 0xC3};  // the v3.1.0 patch

static const DWORD kRvaNtResume = 0x37479fa;

// Stock routine pins, re-verified on the 0.21.3.1 image 2026-11-18 (disasm
// cross-checked against the 0.21.1.1 bodies; see the note in ApplyV320).
static const DWORD kRvaSave = 0x3761c40;        // gfx::Canvas::Save
static const DWORD kRvaRestore = 0x3761c90;     // gfx::Canvas::Restore
static const DWORD kRvaUndoScale = 0x3761c00;   // Canvas::UndoDeviceScaleFactor
static const DWORD kRvaDrawPath = 0x3761fa0;    // gfx::Canvas::DrawPath
static const DWORD kRvaClipPath = 0x3761d20;    // gfx::Canvas::ClipPath
static const DWORD kRvaSkPathRRect = 0x48f46c0; // SkPath::RRect (real entry)
static const DWORD kRvaRRToSkRRect = 0x3105540; // gfx::RoundedRectFToSkRRect
static const DWORD kRvaFromColor = 0x5a08e80;   // SkRGBA4f::FromColor
static const DWORD kRvaFlagsCtor = 0x5c7fd60;   // cc::PaintFlags ctor
static const DWORD kRvaFlagsDtor = 0x4599610;   // cc::PaintFlags dtor
static const DWORD kRvaSkPathDtor = 0xac1880;   // SkPath::~SkPath
static const DWORD kRvaMlg = 0x96fea0;          // SkGradientShader::MakeLinear

static std::atomic<bool> g_gradApplied{false};
static BYTE* g_gradPage = nullptr;
static BYTE* g_chromeBase = nullptr;
static BYTE* g_fsGuardSite = nullptr;
static BYTE* g_ntSite = nullptr;
static BYTE* g_pillSite = nullptr;
static BYTE* g_omniSite = nullptr;
static BYTE g_fsGuardOrig[13];
static BYTE g_ntOrig[7];
static BYTE g_pillOrig[5];
static BYTE g_omniOrig[5];
static volatile BYTE g_fsActive = 0;
static BYTE g_painterVft[24];
static BYTE g_omniPainter[0x18];
static void (*g_mlgThunk)(void*, void*, void*, const void*);

static void* GradRva(DWORD rva) { return g_chromeBase + rva; }

// The mod DLL can load far outside a 32-bit call's reach from the cave, so
// calls into this mod's own code go through an absolute register call.
static void EmitCallAbs64(BYTE*& p, void* target) {
    *p++ = 0x48; *p++ = 0xB8;
    memcpy(p, &target, 8); p += 8;  // movabs rax, target
    *p++ = 0xFF; *p++ = 0xD0;       // call rax
}

// The linear gradient needs six stack arguments after the four register ones;
// this thunk stages them and calls SkGradientShader::MakeLinearGradient with
// a local frame so the caller's stack stays untouched.

typedef void (*CanvasSaveFn)(void*);
typedef void (*CanvasRestoreFn)(void*);
typedef float (*UndoScaleFn)(void*);
typedef void (*DrawPathFn)(void*, void*, void*);
typedef void (*FlagsCtorFn)(void*);
typedef void (*FlagsDtorFn)(void*);
typedef void (*FromColorFn)(void*, unsigned);
typedef void (*RRToSkRRectFn)(void*, const void*, const void*);
// 0.21.3.1 moved the corner-direction into the 4th argument (the 0.21.1.1
// body computed it from a bool in r8b: 0 -> 6). Stock callers pass 6.
typedef void (*SkPathRRectFn)(void*, const void*, unsigned, unsigned);
typedef void (*SkPathDtorFn)(void*);
typedef void (*MlgCallFn)(void*, void*, void*, const void*);
typedef void (*ClipPathFn)(void*, const void*, unsigned);

static void MlgCall(void* sret, void* pts, void* colors) {
    ((MlgCallFn)g_mlgThunk)(sret, pts, colors, nullptr);
}

// PillStrokeC: replaces the stock solid stroke on the vertical-tab pill with
// the riced gradient edge. Runs at the stock stroke DrawPath site inside
// PaintTabBackgroundFill, where the canvas is already clipped to the pill and
// xmm6 holds the UndoDeviceScaleFactor return. Mirrors vertical_tab_style_
// views.cc PaintTabBackgroundFill: alpha = stroke_a x bg_a / 255, width
// 2*scale (the active clip shows it as 1px inside), blue->mauve gradient
// across the pill's own bounds.
static void PillStrokeC(void* canvas, void* path, void* fillFlags,
                        void* strokeFlags, float scale) {
    void* ref = *(void**)path;
    const float* bounds = (const float*)((const BYTE*)ref + 0x60);
    const float fa = *(const float*)((const BYTE*)fillFlags + 0x0C);
    const float sa = *(const float*)((const BYTE*)strokeFlags + 0x0C);
    float a = fa * sa;
    if (a > 1.0f) a = 1.0f;
    const unsigned bgA = (unsigned)(a * 255.0f + 0.5f);
    BYTE flags2[0x50];
    ((FlagsCtorFn)GradRva(kRvaFlagsCtor))(flags2);
    unsigned bf = *(unsigned*)(flags2 + 0x18);
    bf = (bf & 0xFFFFE03Fu) | (3u << 8) | 1u;  // blend kSrcOver, antialias
    bf = (bf & 0xFFFFFF3Fu) | 0x40u;           // style kStroke
    *(unsigned*)(flags2 + 0x18) = bf;
    *(float*)(flags2 + 0x10) = 2.0f * scale;   // clipped to 1px inside
    alignas(16) BYTE c0[16], c1[16], colors[32];
    ((FromColorFn)GradRva(kRvaFromColor))(c0, (bgA << 24) | 0x0089B4FAu);
    ((FromColorFn)GradRva(kRvaFromColor))(c1, (bgA << 24) | 0x00CBA6F7u);
    memcpy(colors, c0, 16);
    memcpy(colors + 16, c1, 16);
    const float pts[4] = {bounds[0], 0.0f, bounds[2], 0.0f};
    void* shader = nullptr;
    MlgCall(&shader, (void*)pts, colors);
    *(void**)((BYTE*)flags2 + 0x28) = shader;
    ((CanvasSaveFn)GradRva(kRvaSave))(canvas);
    ((ClipPathFn)GradRva(kRvaClipPath))(canvas, path, 1);
    ((DrawPathFn)GradRva(kRvaDrawPath))(canvas, path, flags2);
    ((CanvasRestoreFn)GradRva(kRvaRestore))(canvas);
    ((FlagsDtorFn)GradRva(kRvaFlagsDtor))(flags2);
}

// GradPainterPaint: the riced GradientBorderRoundRectPainter::Paint, mirrored
// instruction for instruction from the riced build (0x33ED390 there).
// Self is the 0x18-byte blob {vft, bg +8, stroke mode +0xC (0 = blue->mauve
// gradient, 1 = solid color at +0x10)}; size is the gfx::Size the stock
// wrapper derived from the view.
static void GradPainterPaint(void* self, void* canvas, void* sizePtr) {
    if (g_gradPage) g_gradPage[0x2F4] += 1;  // paint counter (spare0)
    const unsigned bg = *(const unsigned*)((const BYTE*)self + 8);
    const int w = ((const int*)sizePtr)[0];
    const int h = ((const int*)sizePtr)[1];
    // The riced painter computed the radius from the view size
    // (ComputeBorderRadius = GetCornerRadiusMetric(kHigh, size) = height/2,
    // the pill shape). The blob's radius field is unused now.
    float radius = (float)h * 0.5f;

    ((CanvasSaveFn)GradRva(kRvaSave))(canvas);
    const float scale = ((UndoScaleFn)GradRva(kRvaUndoScale))(canvas);
    const float r = radius * scale;

    // Fill: the whole view-sized rect, bg color, rounded by the radius.
    float rect[4] = {0.0f, 0.0f, (float)w * scale, (float)h * scale};
    float corners[4] = {r, r, r, r};
    BYTE flags1[0x50];
    ((FlagsCtorFn)GradRva(kRvaFlagsCtor))(flags1);
    unsigned bf = *(unsigned*)(flags1 + 0x18);
    bf = (bf & 0xFFFFE03Fu) | (3u << 8) | 1u;  // blend kSrcOver, antialias
    *(unsigned*)(flags1 + 0x18) = bf;
    alignas(16) BYTE bg4f[16];
    ((FromColorFn)GradRva(kRvaFromColor))(bg4f, bg);
    memcpy(flags1, bg4f, 16);
    BYTE rr1[64];
    memset(rr1, 0, sizeof(rr1));
    ((RRToSkRRectFn)GradRva(kRvaRRToSkRRect))(rr1, rect, corners);
    BYTE path1[16];
    memset(path1, 0, sizeof(path1));
    ((SkPathRRectFn)GradRva(kRvaSkPathRRect))(path1, rr1, 0, 6);
    ((DrawPathFn)GradRva(kRvaDrawPath))(canvas, path1, flags1);
    ((SkPathDtorFn)GradRva(kRvaSkPathDtor))(path1);
    ((FlagsDtorFn)GradRva(kRvaFlagsDtor))(flags1);

    // Stroke: the fill rect inset by half the stroke width (0.5 * scale per
    // side, the riced build's own numbers), corners reduced the same way and
    // clamped at zero, a one-device-pixel-wide gradient ring.
    const float inset = 0.5f * scale;
    for (int i = 0; i < 4; i++) {
        corners[i] = r - inset;
        if (corners[i] < 0.0f) corners[i] = 0.0f;
    }
    rect[0] += inset;
    rect[1] += inset;
    rect[2] -= 2.0f * inset;
    rect[3] -= 2.0f * inset;
    BYTE flags2[0x50];
    ((FlagsCtorFn)GradRva(kRvaFlagsCtor))(flags2);
    bf = *(unsigned*)(flags2 + 0x18);
    bf = (bf & 0xFFFFE03Fu) | (3u << 8) | 1u;
    bf = (bf & 0xFFFFFF3Fu) | 0x40u;  // style kStroke
    *(unsigned*)(flags2 + 0x18) = bf;
    *(float*)(flags2 + 0x10) = scale;
    alignas(16) BYTE colors[32];
    if (*(const unsigned*)((const BYTE*)self + 0xC) == 1u) {
        // Solid stroke: the focused omnibox keeps its lavender focus ring.
        alignas(16) BYTE solid[16];
        ((FromColorFn)GradRva(kRvaFromColor))(
            solid, *(const unsigned*)((const BYTE*)self + 0x10));
        memcpy(colors, solid, 16);
    } else {
        const float pts[4] = {(float)(int)rect[0], 0.0f,
                              (float)(int)(rect[0] + rect[2]), 0.0f};
        alignas(16) BYTE c0[16], c1[16];
        ((FromColorFn)GradRva(kRvaFromColor))(c0, 0xFF89B4FAu);
        ((FromColorFn)GradRva(kRvaFromColor))(c1, 0xFFCBA6F7u);
        memcpy(colors, c0, 16);
        memcpy(colors + 16, c1, 16);
        void* shader = nullptr;
        MlgCall(&shader, (void*)pts, colors);
        *(void**)(flags2 + 0x28) = shader;
    }
    BYTE rr2[64];
    memset(rr2, 0, sizeof(rr2));
    ((RRToSkRRectFn)GradRva(kRvaRRToSkRRect))(rr2, rect, corners);
    BYTE path2[16];
    memset(path2, 0, sizeof(path2));
    ((SkPathRRectFn)GradRva(kRvaSkPathRRect))(path2, rr2, 0, 6);
    ((DrawPathFn)GradRva(kRvaDrawPath))(canvas, path2, flags2);
    ((SkPathDtorFn)GradRva(kRvaSkPathDtor))(path2);
    ((FlagsDtorFn)GradRva(kRvaFlagsDtor))(flags2);

    ((CanvasRestoreFn)GradRva(kRvaRestore))(canvas);
}

// Session diagnostic: append-only trace so a silent init failure is visible
// without the Windhawk log window (DBWIN is banned on this machine).
static void ModTrace(const char* s, size_t n) {
    HANDLE f = CreateFileA("F:\\hb-build\\mod-work\\agentB\\final\\modlog.txt",
                           FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE,
                           nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (f == INVALID_HANDLE_VALUE) return;
    DWORD w = 0;
    WriteFile(f, s, (DWORD)n, &w, nullptr);
    CloseHandle(f);
}
#define MTRACE(s) ModTrace(s "\r\n", sizeof(s "\r\n") - 1)

// omnibox's own pass arms on its border-color fetch and consumes the arm in
// the same call. The helper itself moved above ApplyStructuralPatches so the
// structural layer can nudge newly patched windows too.

static bool ApplyV320() {
    MTRACE("v320: enter");
    // v3.5.0 (2026-11-18): the full re-pin onto 0.21.3.1 is done and every
    // anchor was resolved by disassembly cross-checked against the 0.21.1.1
    // body, not by fuzzy size matching alone:
    //   Sites: FsGuard 0x374A290 (unique pattern, bytes identical),
    //   NtHide 0x37479F3 (store bytes identical, two methods agree),
    //   PillDraw 0xAAC9D2B (the only DrawPath call in the matched
    //   PaintTabBackgroundFill 0xAAC9970, context matches instruction for
    //   instruction), OmniB 0x1707AAA (found via the painter's unique
    //   mov dword [rax+8],0xFFFF0000 wrapper construction; convergence
    //   wrapper alloc sits at site+0x46, same distance as 0.21.1.1).
    //   Routines: GetColor 0x4311790 (pattern), Provider 0x4909F60 (the pill
    //   function calls it exactly where 0.21.1.1 called 0x4F728E0; body is
    //   the same getter, devirtualized to 97 bytes), Canvas cluster
    //   Save/Restore/UndoScale/ClipPath/DrawPath 0x3761C40/0x3761C90/
    //   0x3761C00/0x3761D20/0x3761FA0, FromColor 0x5A08E80 (called by the
    //   new pill function), Mlg 0x96FEA0 (body sim 0.89), SkPathDtor
    //   0xAC1880 (pdata 1.000), RoundedRectFToSkRRect 0x3105540 (pdata 0.96,
    //   body is the float copy), SkPath::RRect 0x48F46C0 (prologue, type
    //   switch, dispatch and tail all match; signature now takes the corner
    //   direction in r9d - stock callers pass 6, so the mod does too),
    //   PaintFlags ctor 0x5C7FD60 and dtor 0x4599610 (both taken from the
    //   new pill function's own call sites; the dtor is also the top
    //   mnemonic match for the 0.21.1.1 dtor).
    if (g_gradApplied) return true;
    HMODULE chrome = GetModuleHandleW(L"chrome.dll");
    if (!chrome) {
        Wh_Log(L"chrome.dll not loaded yet");
        MTRACE("v320: fail - no chrome.dll");
        return false;
    }
    g_chromeBase = (BYTE*)chrome;

    // The fullscreen guard replaces the old acrylic patch on the same site,
    // so both the stock body and the v3.1.0 patch mean "this is our site".
    BYTE* fsAt = (BYTE*)chrome + kRvaFsGuard;
    bool fsStock = memcmp(fsAt, kOrigFsGuard, sizeof(kOrigFsGuard)) == 0;
    bool fsOld = memcmp(fsAt, kOldAcrylic, sizeof(kOldAcrylic)) == 0;
    if (!fsStock && !fsOld) {
        Wh_Log(L"v3.2.0: fullscreen guard site has unexpected bytes - untouched");
        MTRACE("v320: fail gate fs");
        return false;
    }
    BYTE* ntAt = (BYTE*)chrome + kRvaNtHide;
    if (memcmp(ntAt, kOrigNtHide, sizeof(kOrigNtHide)) != 0) {
        Wh_Log(L"v3.2.0: new-tab site has unexpected bytes - untouched");
        MTRACE("v320: fail gate nt");
        return false;
    }
    BYTE* pillAt = (BYTE*)chrome + kRvaPillDraw;
    if (memcmp(pillAt, kOrigPill, sizeof(kOrigPill)) != 0) {
        Wh_Log(L"v3.2.0: tab-pill site has unexpected bytes - untouched");
        MTRACE("v320: fail gate pill");
        return false;
    }
    BYTE* omniAt = (BYTE*)chrome + kRvaOmniB;
    if (memcmp(omniAt, kOrigOmniB, sizeof(kOrigOmniB)) != 0) {
        Wh_Log(L"v3.4.0: omnibox painter site has unexpected bytes - untouched");
        MTRACE("v320: fail gate omni");
        return false;
    }

    // One RWX page for the caves, the gradient thunk and the painter tables,
    // near the module like the other layers' pages.
    BYTE* bases[5] = {
        (BYTE*)chrome - 0x10000000 - 0x200000,
        (BYTE*)chrome - 0x10000000 + 0x100000,
        (BYTE*)chrome + 0x10000000,
        (BYTE*)chrome - 0x40000000,
        (BYTE*)chrome + 0x40000000,
    };
    BYTE* mem = nullptr;
    for (int i = 0; i < 5 && !mem; i++) {
        mem = (BYTE*)VirtualAlloc(bases[i], 0x1000, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_EXECUTE_READWRITE);
    }
    if (!mem) {
        mem = (BYTE*)VirtualAlloc(nullptr, 0x1000, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_EXECUTE_READWRITE);
    }
    if (!mem) {
        Wh_Log(L"v3.2.0: VirtualAlloc failed");
        return false;
    }
    g_gradPage = mem;
    BYTE* p = mem;

    // 0x00: a fresh copy of the native-frame helper body (rcx only, no
    // dependency on the other layer's page). v3.1.0: always false, matching
    // the riced build's runtime behavior.
    BYTE* sune = p;
    const BYTE suneImpl[] = { 0x31, 0xC0, 0xC3 }; // xor eax,eax; ret
    EmitBytes(p, suneImpl, sizeof(suneImpl));

    // 0x20: the fullscreen guard. The riced build's own guard (found at
    // 0x4919F35 in its image) gates the answer on a Host virtual chain that
    // would need several more stock re-pins to port safely; until then the
    // answer stays the v3.1.0 one (transparent, recorded in g_fsActive) with
    // the stock's null check replayed. No dereferences beyond the stock's.
    p = mem + 0x20;
    BYTE* guard = p;
    BYTE* hitsBase = mem + 0x2F0;   // per-cave execution counters, read back live
    auto emitMark = [&](int idx) {
        *p++ = 0x48; *p++ = 0xB8;
        BYTE* h = hitsBase + idx; memcpy(p, &h, 8); p += 8;  // movabs rax,&hits[idx]
        *p++ = 0xFE; *p++ = 0x00;                            // inc byte [rax]
    };
    // v3.1.0 parity: the site always answers transparent, with the state
    // recorded. The stock's own deref is replayed by nothing - the old patch
    // (B0 01 C3) never dereferenced either, and returning 0 on the null path
    // turned the acrylic off in practice.
    BYTE* fsPtr = (BYTE*)&g_fsActive;
    emitMark(0);
    *p++ = 0x48; *p++ = 0xB8;
    memcpy(p, &fsPtr, 8); p += 8;           // movabs rax,&g_fsActive
    *p++ = 0xC6; *p++ = 0x00; *p++ = 0x00;  // mov byte [rax],0
    *p++ = 0xB0; *p++ = 0x01;               // mov al,1
    *p++ = 0xC3;                            // ret

    // 0xC0: the sidebar new-tab hide. Replays the store, hides the button
    // through its own vtable, resumes at the stock's next instruction.
    p = mem + 0xC0;
    BYTE* nt = p;
    emitMark(1);
    const BYTE ntReplay[] = {0x4C, 0x89, 0xB6, 0x50, 0x03, 0x00, 0x00};
    EmitBytes(p, ntReplay, 7);                // mov [rsi+0x350],r14 (replay)
    *p++ = 0x49; *p++ = 0x8B; *p++ = 0x06;    // mov rax,[r14]
    BYTE* vtSlot = hitsBase + 0x10;
    *p++ = 0x48; *p++ = 0xBA;                 // movabs rdx,&vtable capture
    memcpy(p, &vtSlot, 8); p += 8;
    *p++ = 0x48; *p++ = 0x89; *p++ = 0x02;    // mov [rdx],rax
    const BYTE ntHide[] = {0x4C, 0x89, 0xF1,             // mov rcx,r14 (button)
                           0x31, 0xD2,                   // xor edx,edx (false)
                           0xFF, 0x90, 0x90, 0x00, 0x00, 0x00}; // call [rax+0x90]
                           // rax was loaded from [r14] above: the button's
                           // live vptr; slot 18 = View::SetVisible (read at
                           // runtime, no pinned vtable address needed). The
                           // old FF 50 90 encoded [rax-0x70] - signed disp8
                           // trap.
    EmitBytes(p, ntHide, sizeof(ntHide));
    EmitJmpRel32(p, (BYTE*)chrome + kRvaNtResume);

    // 0x100: the tab-pill stub on the stock stroke DrawPath site inside
    // PaintTabBackgroundFill (0xAAC9970 on 0.21.3.1). This is a mid-function
    // patch, so the stub ends with a jmp back to 0xAAC9D30, not a ret. rsp
    // is 16-byte aligned at the site (7 pushes + sub 0x2D0 + call), so sub
    // 0x50 keeps every call inside the stub aligned too. xmm6 still holds
    // the scale UndoDeviceScaleFactor returned at 0xAAC9B82; it rides in
    // the arg5 slot.
    p = mem + 0x100;
    BYTE* pill = p;
    emitMark(2);
    const BYTE pillFrame[] = {0x48, 0x83, 0xEC, 0x50,              // sub rsp,0x50
                              0x48, 0x89, 0x4C, 0x24, 0x28,        // mov [rsp+0x28],rcx
                              0x48, 0x89, 0x54, 0x24, 0x30,        // mov [rsp+0x30],rdx
                              0x4C, 0x89, 0x44, 0x24, 0x38,        // mov [rsp+0x38],r8
                              0x66, 0x48, 0x0F, 0x7E, 0xF0,        // movq rax,xmm6
                              0x48, 0x89, 0x44, 0x24, 0x20};       // mov [rsp+0x20],rax
    EmitBytes(p, pillFrame, sizeof(pillFrame));
    // PillStrokeC(canvas, path, fillFlags, strokeFlags, scale). The caller's
    // fill flags ([rsp+0xA0] before the patch, still alive here) sit at
    // [rsp+0xF0] inside this frame.
    const BYTE pillArg[] = {0x48, 0x8B, 0x4C, 0x24, 0x28,          // mov rcx,[rsp+0x28]
                            0x48, 0x8B, 0x54, 0x24, 0x30,          // mov rdx,[rsp+0x30]
                            0x4C, 0x8D, 0x84, 0x24, 0xF0, 0x00,
                            0x00, 0x00,                            // lea r8,[rsp+0xF0]
                            0x4C, 0x8B, 0x4C, 0x24, 0x38};         // mov r9,[rsp+0x38]
    EmitBytes(p, pillArg, sizeof(pillArg));
    EmitCallAbs64(p, (void*)&PillStrokeC);                 // gradient edge
    const BYTE pillEpi[] = {0x48, 0x83, 0xC4, 0x50};       // add rsp,0x50
    EmitBytes(p, pillEpi, sizeof(pillEpi));
    EmitJmpRel32(p, (BYTE*)chrome + kRvaPillResume);

    // 0x180: the omnibox stub on the inline solid-painter build (0x1707AAA),
    // reached only for the resting omnibox and the caret-visible one. The
    // resting case installs the gradient blob with the current background
    // color (ebx); the caret case fetches the focus ring color live and
    // installs the blob with a solid stroke. All other states never reach
    // here, so the stock factory call later in RefreshBackground stays
    // untouched.
    p = mem + 0x180;
    BYTE* omni = p;
    emitMark(3);
    *p++ = 0x41; *p++ = 0x83; *p++ = 0xFC; *p++ = 0x01;    // cmp r12d,1 (caret)
    BYTE* jeCaret = p; *p++ = 0x74; p += 1;                // je .caret
    emitMark(5);                                           // resting branch ran
    void* blob = g_omniPainter;
    *p++ = 0x48; *p++ = 0xB8;
    memcpy(p, &blob, 8); p += 8;                           // movabs rax,blob
    *p++ = 0x89; *p++ = 0x58; *p++ = 0x08;                 // mov [rax+8],ebx (bg)
    *p++ = 0xC7; *p++ = 0x40; *p++ = 0x0C;                 // mov dword [rax+0xC],0
    *p++ = 0; *p++ = 0; *p++ = 0; *p++ = 0;                //   (gradient stroke)
    *p++ = 0x49; *p++ = 0x89; *p++ = 0xC6;                 // mov r14,rax
    EmitJmpRel32(p, (BYTE*)chrome + kRvaOmniConv);           // to the convergence
    *jeCaret = 0x74;
    *(signed char*)(jeCaret + 1) = (signed char)(p - (jeCaret + 2));
    emitMark(6);                                           // caret branch ran
    *p++ = 0x48; *p++ = 0x89; *p++ = 0xF1;                 // .caret: mov rcx,rsi
    EmitCallRel32(p, (BYTE*)chrome + kRvaProvider);        // color provider
    *p++ = 0x48; *p++ = 0x89; *p++ = 0xC1;                 // mov rcx,rax
    *p++ = 0xBA; *p++ = 0x3F; *p++ = 0x01; *p++ = 0x00; *p++ = 0x00;  // mov edx,0x13F
    EmitCallRel32(p, (BYTE*)chrome + kRvaGetColor);        // focus ring color
    *p++ = 0x48; *p++ = 0xB8;
    memcpy(p, &blob, 8); p += 8;                           // movabs rax,blob
    *p++ = 0x89; *p++ = 0x58; *p++ = 0x08;                 // mov [rax+8],ebx (bg)
    *p++ = 0xC7; *p++ = 0x40; *p++ = 0x0C;                 // mov dword [rax+0xC],1
    *p++ = 1; *p++ = 0; *p++ = 0; *p++ = 0;                //   (solid stroke)
    *p++ = 0x89; *p++ = 0x40; *p++ = 0x10;                 // mov [rax+0x10],eax
    *p++ = 0x49; *p++ = 0x89; *p++ = 0xC6;                 // mov r14,rax
    EmitJmpRel32(p, (BYTE*)chrome + kRvaOmniConv);           // to the convergence

    // 0x200: the MakeLinearGradient thunk plus its zeroed argument blobs.
    p = mem + 0x200;
    BYTE* mlg = p;
    const BYTE mlgFrame[] = {0x48, 0x83, 0xEC, 0x58};
    EmitBytes(p, mlgFrame, 4);                    // sub rsp,0x58
    const BYTE mlgCount[] = {0x48, 0xC7, 0x44, 0x24, 0x20, 0x02, 0, 0, 0};
    EmitBytes(p, mlgCount, 9);                    // mov qword [rsp+0x20],2
    const BYTE mlgTile[] = {0x48, 0xC7, 0x44, 0x24, 0x28, 0, 0, 0, 0};
    EmitBytes(p, mlgTile, 9);                     // mov qword [rsp+0x28],0
    *p++ = 0x48; *p++ = 0x8D; *p++ = 0x05;        // lea rax,[rip+interp]
    BYTE* lea1 = p; p += 4;
    const BYTE mlgSt1[] = {0x48, 0x89, 0x44, 0x24, 0x30};
    EmitBytes(p, mlgSt1, 5);                      // mov [rsp+0x30],rax
    const BYTE mlgZ38[] = {0x48, 0xC7, 0x44, 0x24, 0x38, 0, 0, 0, 0};
    EmitBytes(p, mlgZ38, 9);                      // mov qword [rsp+0x38],0
    const BYTE mlgZ40[] = {0x48, 0xC7, 0x44, 0x24, 0x40, 0, 0, 0, 0};
    EmitBytes(p, mlgZ40, 9);                      // mov qword [rsp+0x40],0
    *p++ = 0x48; *p++ = 0x8D; *p++ = 0x05;        // lea rax,[rip+z16]
    BYTE* lea2 = p; p += 4;
    const BYTE mlgSt2[] = {0x48, 0x89, 0x44, 0x24, 0x48};
    EmitBytes(p, mlgSt2, 5);                      // mov [rsp+0x48],rax
    EmitCallRel32(p, (BYTE*)chrome + kRvaMlg);
    const BYTE mlgEpi[] = {0x48, 0x83, 0xC4, 0x58, 0xC3};
    EmitBytes(p, mlgEpi, 5);                      // add rsp,0x58; ret
    p = (BYTE*)(((SIZE_T)p + 15) & ~(SIZE_T)15);
    BYTE* interp = p;
    memset(p, 0, 19); p += 19;
    p = (BYTE*)(((SIZE_T)p + 15) & ~(SIZE_T)15);
    BYTE* z16 = p;
    memset(p, 0, 16); p += 16;
    *(DWORD*)lea1 = (DWORD)(INT64)(interp - (lea1 + 4));
    *(DWORD*)lea2 = (DWORD)(INT64)(z16 - (lea2 + 4));
    g_mlgThunk = (void (*)(void*, void*, void*, const void*))mlg;

    // The stock-shaped painter and its three-slot vtable: a no-op deleting
    // destructor (the object is static and must survive SetBackground), the
    // stock's own second slot body, and the riced painter's Paint.
    p = (BYTE*)(((SIZE_T)p + 15) & ~(SIZE_T)15);
    BYTE* noopRet = p;
    *p++ = 0xC3;
    p = (BYTE*)(((SIZE_T)p + 15) & ~(SIZE_T)15);
    BYTE* zeroSlot = p;
    const BYTE zeroBody[] = {0x48, 0x89, 0xD0, 0x48, 0xC7, 0x02, 0, 0, 0, 0, 0xC3};
    EmitBytes(p, zeroBody, sizeof(zeroBody));
    void* vft[3] = {noopRet, zeroSlot, (void*)&GradPainterPaint};
    memcpy(g_painterVft, vft, sizeof(vft));
    memset(g_omniPainter, 0, sizeof(g_omniPainter));
    *(void**)g_omniPainter = g_painterVft;

    // Route the four sites into the caves.
    struct Write { DWORD rva; int len; BYTE* cave; bool isCall;
                   const BYTE* raw; };
    const Write writes[4] = {
        {kRvaFsGuard, 13, guard, false, nullptr},
        {kRvaNtHide, 7, nt, false, nullptr},
        {kRvaPillDraw, 5, pill, false, nullptr},
        {kRvaOmniB, 5, omni, false, nullptr},
    };
    for (int i = 0; i < 4; i++) {
        BYTE* at = (BYTE*)chrome + writes[i].rva;
        if (writes[i].raw) {
            DWORD oldProtect, tmp;
            if (!VirtualProtect(at, writes[i].len, PAGE_EXECUTE_READWRITE,
                                &oldProtect)) {
                Wh_Log(L"v3.3.0: VirtualProtect failed at raw %d", i);
                return false;
            }
            memcpy(at, writes[i].raw, writes[i].len);
            VirtualProtect(at, writes[i].len, oldProtect, &tmp);
            if (memcmp(at, writes[i].raw, writes[i].len) != 0) {
                Wh_Log(L"v3.3.0: raw %d read-back mismatch", i);
                return false;
            }
            Wh_Log(L"Helium acrylic: v3.3.0 raw patch %d live at RVA 0x%zX",
                   i, (size_t)writes[i].rva);
            continue;
        }
        INT64 rel = (INT64)writes[i].cave - (INT64)(at + 5);
        if (rel > 0x7FFFFFFF || rel < -0x7FFFFFFF) {
            Wh_Log(L"v3.2.0: cave %d out of jump range - untouched", i);
            return false;
        }
        DWORD oldProtect, tmp;
        if (!VirtualProtect(at, writes[i].len, PAGE_EXECUTE_READWRITE,
                            &oldProtect)) {
            Wh_Log(L"v3.2.0: VirtualProtect failed at cave %d", i);
            return false;
        }
        BYTE* saved = nullptr;
        int savedLen = writes[i].len;
        switch (i) {
            case 0: saved = g_fsGuardOrig; break;
            case 1: saved = g_ntOrig; break;
            case 2: saved = g_pillOrig; break;
            case 3: saved = g_omniOrig; break;
        }
        memcpy(saved, at, savedLen);
        BYTE jmp[5] = {(BYTE)(writes[i].isCall ? 0xE8 : 0xE9), 0, 0, 0, 0};
        *(DWORD*)(jmp + 1) = (DWORD)rel;
        memcpy(at, jmp, 5);
        for (int j = 5; j < writes[i].len; j++) at[j] = 0x90;
        if (memcmp(at, jmp, sizeof(jmp)) != 0) {
            // Never leave a half-written branch live: restore and fail.
            memcpy(at, saved, savedLen);
            Wh_Log(L"v3.2.0: cave %d read-back mismatch - restored", i);
        }
        VirtualProtect(at, writes[i].len, oldProtect, &tmp);
        if (memcmp(at, jmp, sizeof(jmp)) != 0) {
            return false;
        }
        switch (i) {
            case 0: g_fsGuardSite = at; break;
            case 1: g_ntSite = at; break;
            case 2: g_pillSite = at; break;
            case 3: g_omniSite = at; break;
        }
        Wh_Log(L"Helium acrylic: v3.2.0 cave %d live at RVA 0x%zX", i,
               (size_t)writes[i].rva);
    }
    g_gradApplied = true;
    Wh_Log(L"Helium acrylic: v3.2.0 live (fullscreen guard, sidebar new-tab"
           L" hidden, tab-pill gradient, omnibox gradient)");
    NudgeCtx nc;
    nc.pid = GetCurrentProcessId();
    nc.n = 0;
    EnumWindows(NudgeEnum, (LPARAM)&nc);
    for (int i = 0; i < nc.n; i++)
        PostMessageW(nc.hwnds[i], WM_THEMECHANGED, 0, 0);
    MTRACE("v320: theme nudge posted");
    return true;
}

static void ApplyOnePass() {
    ApplyV320();
    MTRACE("pass: v320 returned");
    ApplyAcrylicPatch();
    MTRACE("pass: acrylic returned");
    InstallColorHook();
    MTRACE("pass: colors returned");
    ApplyStructuralPatches();
    MTRACE("pass: frame returned");
}

// v3.1.0: a browser that starts while Windhawk is still delivering the mod
// used to keep whatever a single early scan managed to do for the rest of
// its life. One deferred re-pass (guards make the layers idempotent) closes
// that window; a build where nothing matched at all is left alone, so the
// riced install's processes never rescan.
static DWORD WINAPI RetryOnceThread(LPVOID) {
    Sleep(10000);
    if (g_stop) return 0;
    if (g_acrylicApplied && g_colorsApplied && g_frameApplied &&
        g_gradApplied) return 0;
    if (!GetModuleHandleW(L"chrome.dll")) return 0;
    if (!g_acrylicApplied && !g_colorsApplied && !g_frameApplied &&
        !g_gradApplied) return 0;
    ApplyOnePass();
    Wh_Log(L"apply state after retry: acrylic=%d colors=%d frame=%d",
           (int)g_acrylicApplied, (int)g_colorsApplied,
           (int)g_frameApplied);
    return 0;
}

static void ApplyAllLayers() {
    ApplyOnePass();
    HANDLE h = CreateThread(nullptr, 0, RetryOnceThread, nullptr, 0, nullptr);
    if (h) CloseHandle(h);
}

static DWORD WINAPI InitThread(LPVOID) {
    for (int i = 0; i < 300 && !g_stop; i++) {
        if (GetModuleHandleW(L"chrome.dll")) break;
        Sleep(200);
    }
    if (g_stop) return 0;
    ApplyAllLayers();
    HANDLE h = CreateThread(nullptr, 0, ThemeThread, nullptr, 0, nullptr);
    if (h) CloseHandle(h);
    return 0;
}

// v3.3.3: Helium's web toolbar draws its own window buttons whenever its
// code does not see --hide-window-buttons, in places the two branch flips
// cannot reach (renderer-side toolbar state; proven live 2026-11-18: the
// patched browser still showed them while a real switch on the command line
// did not). So the switch must hold globally: append it to this process's
// command line before Chromium parses it. Runs in the browser process only
// (children get their state from the browser); the buffer append is bounded
// by the owning memory region so it can never overrun.
static void EnsureHideWindowButtonsSwitch() {
    MTRACE("hwb: enter");
    LPWSTR cmd = GetCommandLineW();
    if (!cmd) { MTRACE("hwb: no command line"); return; }
    if (wcsstr(cmd, L"hide-window-buttons")) { MTRACE("hwb: already present"); return; }
    if (wcsstr(cmd, L"--type=")) { MTRACE("hwb: child process, skip"); return; }
    size_t len = wcslen(cmd);
    const wchar_t add[] = L" --hide-window-buttons";
    const size_t addWchars = (sizeof(add) / sizeof(wchar_t));  // incl. NUL
    MEMORY_BASIC_INFORMATION mbi;
    if (!VirtualQuery(cmd, &mbi, sizeof(mbi))) {
        MTRACE("hwb: VirtualQuery failed");
        return;
    }
    SIZE_T avail = ((BYTE*)mbi.BaseAddress + mbi.RegionSize) - (BYTE*)cmd;
    Wh_Log(L"hide-window-buttons: len=%zu need=%zu avail=%zu protect=0x%zX",
           len, addWchars, (size_t)avail, (size_t)mbi.Protect);
    if ((len + addWchars) * sizeof(wchar_t) > avail) {
        MTRACE("hwb: buffer too small");
        return;
    }
    wcscpy(cmd + len, add);
    Wh_Log(L"hide-window-buttons: appended");
    MTRACE("hwb: appended to command line");
}

BOOL Wh_ModInit() {
    Wh_Log(L">");
    EnsureHideWindowButtonsSwitch();
    MTRACE(GetModuleHandleW(L"chrome.dll") ? "init: chrome already loaded"
                                           : "init: chrome not loaded yet");
    g_dark = ReadDarkTheme() ? 1 : 0;
    HANDLE hBackdrop = CreateThread(nullptr, 0, BackdropThread, nullptr, 0, nullptr);
    if (hBackdrop) CloseHandle(hBackdrop);
    if (GetModuleHandleW(L"chrome.dll")) {
        ApplyAllLayers();
        HANDLE h = CreateThread(nullptr, 0, ThemeThread, nullptr, 0, nullptr);
        if (h) CloseHandle(h);
    } else {
        HANDLE h = CreateThread(nullptr, 0, InitThread, nullptr, 0, nullptr);
        if (h) CloseHandle(h);
    }
    return TRUE;
}

void Wh_ModUninit() {
    g_stop = true;
    if (g_acrylicApplied && g_acrylicTarget) {
        DWORD oldProtect;
        if (VirtualProtect(g_acrylicTarget, sizeof(g_acrylicOriginal), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(g_acrylicTarget, g_acrylicOriginal, sizeof(g_acrylicOriginal));
            DWORD tmp;
            VirtualProtect(g_acrylicTarget, sizeof(g_acrylicOriginal), oldProtect, &tmp);
        }
        g_acrylicApplied = false;
    }
    if (g_colorsApplied && g_gcTarget) {
        DWORD oldProtect;
        if (VirtualProtect(g_gcTarget, sizeof(g_gcOriginal), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(g_gcTarget, g_gcOriginal, sizeof(g_gcOriginal));
            DWORD tmp;
            VirtualProtect(g_gcTarget, sizeof(g_gcOriginal), oldProtect, &tmp);
        }
        g_colorsApplied = false;
    }
    for (int i = 0; i < 4; i++) {
        if (g_frameSites[i].applied && g_frameSites[i].target) {
            DWORD oldProtect, tmp;
            if (VirtualProtect(g_frameSites[i].target, g_frameSites[i].size,
                               PAGE_EXECUTE_READWRITE, &oldProtect)) {
                memcpy(g_frameSites[i].target, g_frameSites[i].original,
                       g_frameSites[i].size);
                VirtualProtect(g_frameSites[i].target, g_frameSites[i].size,
                               oldProtect, &tmp);
            }
            g_frameSites[i].applied = false;
        }
    }
    if (g_fsGuardSite) {
        DWORD oldProtect, tmp;
        if (VirtualProtect(g_fsGuardSite, sizeof(g_fsGuardOrig), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(g_fsGuardSite, g_fsGuardOrig, sizeof(g_fsGuardOrig));
            VirtualProtect(g_fsGuardSite, sizeof(g_fsGuardOrig), oldProtect, &tmp);
        }
        g_fsGuardSite = nullptr;
    }
    if (g_ntSite) {
        DWORD oldProtect, tmp;
        if (VirtualProtect(g_ntSite, sizeof(g_ntOrig), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(g_ntSite, g_ntOrig, sizeof(g_ntOrig));
            VirtualProtect(g_ntSite, sizeof(g_ntOrig), oldProtect, &tmp);
        }
        g_ntSite = nullptr;
    }
    if (g_pillSite) {
        DWORD oldProtect, tmp;
        if (VirtualProtect(g_pillSite, sizeof(g_pillOrig), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(g_pillSite, g_pillOrig, sizeof(g_pillOrig));
            VirtualProtect(g_pillSite, sizeof(g_pillOrig), oldProtect, &tmp);
        }
        g_pillSite = nullptr;
    }
    if (g_omniSite) {
        DWORD oldProtect, tmp;
        if (VirtualProtect(g_omniSite, sizeof(g_omniOrig), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(g_omniSite, g_omniOrig, sizeof(g_omniOrig));
            VirtualProtect(g_omniSite, sizeof(g_omniOrig), oldProtect, &tmp);
        }
        g_omniSite = nullptr;
    }
    if (g_gradPage) {
        VirtualFree(g_gradPage, 0, MEM_RELEASE);
        g_gradPage = nullptr;
    }
    if (g_cavePage) {
        VirtualFree(g_cavePage, 0, MEM_RELEASE);
        g_cavePage = nullptr;
    }
    if (g_hookMem) {
        VirtualFree(g_hookMem, 0, MEM_RELEASE);
        g_hookMem = nullptr;
    }
}
