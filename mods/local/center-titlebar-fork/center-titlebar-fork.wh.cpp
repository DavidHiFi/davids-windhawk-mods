// ==WindhawkMod==
// @id              center-titlebar-fork
// @name            Center Titlebar - Fork
// @description     Center align the text in titlebar
// @version         3.4
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @license         MIT
// @include         dwm.exe
// @architecture    x86-64
// ==/WindhawkMod==

// A fork of center-titlebar by rounk-ctrl (https://github.com/rounk-ctrl),
// which is a port of valinet's WinCenterTitle
// (https://github.com/valinet/WinCenterTitle). This fork reworks the title
// centering for modern Windows 11 builds, where the caption is rendered with
// DirectWrite. Development takes place here:
// https://github.com/DavidHiFi/davids-windhawk-mods
//
// Status: prototype, not published upstream and not installed on the live setup.

// ==WindhawkModReadme==
/*
# Center Titlebar (fork)

Based on rounk-ctrl's [center-titlebar](https://windhawk.net/mods/center-titlebar), which is a
port of valinet's [WinCenterTitle](https://github.com/valinet/WinCenterTitle). Rewritten for
modern Windows 11 builds.

## Why the original never worked

The original mod hooks `user32!DrawTextW`. On current Windows 11 builds, `uDWM.dll` imports no GDI
or theme text API at all — not `DrawTextW`, `DrawTextExW`, `DrawThemeText(Ex)` nor `ExtTextOutW`.
The caption title is rendered with **DirectWrite**, by an internal class called `CDWriteText`. So
the hook installs fine and never fires, which is why the mod appears to do nothing rather than
failing loudly.

## How this one centers the title

Not by text alignment. DWM builds an `IDWriteTextLayout` whose width spans the whole caption text
area, but it renders the glyphs at the visual's left edge and discards the alignment offset
DirectWrite computed — so setting `DWRITE_TEXT_ALIGNMENT_CENTER` changes nothing on screen.

What moves the title is the caption text visual's **left inset**, and the trick is *when* to change
it. The mod hooks `CVisual::UpdateLayout` — the call that hands the parent's size and this visual's
insets to `DoCanvasLayout` — and rewrites the inset just before the layout is computed from it.

Timing is the whole problem. DWM positions the caption's children in
`UpdateNCAreaPositionsAndSizes`, which runs *before* the layout traversal resizes their parent, so
anything computed there is centered against the previous window's width; the title ends up stranded
off to one side after a maximize or restore until something happens to recompute it. Inside
`UpdateLayout` the parent size is current by construction, so there is nothing stale to center
against and no later pass to wait for.

Both numbers that decide where centre is are read live: the text width from the layout's own
metrics, and the titlebar width from the parent visual (`CVisual` keeps its parent at `+0x18` and
its size at `+0x48`). `CVisual::SetInsetFromParentLeft` is still hooked, but only to record the
inset DWM asked for, which is where the window icon ends.

## Options

* **Center the title text** — the actual centering.
* **Center on the window, not the free space** — the caption text area excludes the window icon on
  the left and the caption buttons on the right, and the button side is much wider, so centering
  within the leftover space lands well left of the window's true centre. With this on, the title is
  centered on the window itself. Either way it is clamped so it can never overlap the icon or the
  buttons; if a title is too long to fit centered, it falls back to its normal position.
* **Maximized caption buttons** — fixes caption buttons sitting too low on maximized windows with
  custom (UltraUXThemePatcher / msstyles) themes. *Center vertically* centres the button block in
  the caption band DWM reports, and the extra offset applies in **every** mode so it doubles as a
  fine-tune. There is no way to derive the right value automatically — it depends on where your
  msstyles paints the caption background, which DWM does not know. Nudge the offset until it looks
  right.
* **Log diagnostics** — reports the caption geometry and the text metrics.

## Notes

* You must enable **"Inject into system processes"** in Windhawk's advanced settings, or this
  silently does nothing — DWM is a protected process. The portable version of Windhawk cannot do
  this at all.
* Everything is resolved from public Microsoft symbols rather than hardcoded addresses. The only
  structure offsets used are the parent, size and inset fields that `CVisual` hands to its own
  layout code, and the DirectWrite objects are located by validated scanning rather than fixed
  offsets.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- centerText: true
  $name: Center the title text
- centerOnWindow: true
  $name: Center on the window, not the free space
  $description: >-
    Compensate for the window icon and caption buttons so the title sits on the window's true
    centre rather than the centre of the space left over between them.
- maximizedButtons: none
  $name: Maximized window caption buttons
  $description: >-
    For caption buttons sitting too low on maximized windows with custom themes.
  $options:
  - none: Leave alone
  - auto: Center them vertically in the caption band
  - manual: Use DWM's position as the starting point
- maximizedButtonOffset: 0
  $name: Extra vertical offset (pixels)
  $description: >-
    Applied on top of whichever mode is selected above, so it fine-tunes the automatic centering
    too. Negative values move the buttons up.
- verboseLogging: false
  $name: Log diagnostics
  $description: Noisy - turn it off afterwards.
*/
// ==/WindhawkModSettings==

#include <windhawk_utils.h>

#include <dwrite.h>

#include <algorithm>

// ============================================================================
//  Settings
// ============================================================================

enum MaximizedButtonMode {
    MAXBTN_NONE = 0,
    MAXBTN_AUTO,
    MAXBTN_MANUAL,
};

struct {
    bool centerText;
    bool centerOnWindow;
    int maximizedButtons;
    int maximizedButtonOffset;
    bool verboseLogging;
} g_settings;

static void LoadSettings() {
    g_settings.centerText = Wh_GetIntSetting(L"centerText");
    g_settings.centerOnWindow = Wh_GetIntSetting(L"centerOnWindow");
    g_settings.maximizedButtonOffset =
        Wh_GetIntSetting(L"maximizedButtonOffset");
    g_settings.verboseLogging = Wh_GetIntSetting(L"verboseLogging");

    g_settings.maximizedButtons = MAXBTN_NONE;
    PCWSTR mode = Wh_GetStringSetting(L"maximizedButtons");
    if (wcscmp(mode, L"auto") == 0) {
        g_settings.maximizedButtons = MAXBTN_AUTO;
    } else if (wcscmp(mode, L"manual") == 0) {
        g_settings.maximizedButtons = MAXBTN_MANUAL;
    }
    Wh_FreeStringSetting(mode);
}

// ============================================================================
//  Memory safety helpers
//
//  We poke at DWM-internal objects, and a wrong guess there takes the whole
//  desktop down. Everything read out of an object is validated first.
// ============================================================================

static bool IsReadableMemory(const void* p, size_t size) {
    if (!p) {
        return false;
    }

    MEMORY_BASIC_INFORMATION mbi;
    if (!VirtualQuery(p, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT) {
        return false;
    }

    constexpr DWORD kReadable = PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY |
                                PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE |
                                PAGE_EXECUTE_WRITECOPY;
    if (!(mbi.Protect & kReadable) ||
        (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS))) {
        return false;
    }

    ULONG_PTR regionEnd = (ULONG_PTR)mbi.BaseAddress + mbi.RegionSize;
    return (ULONG_PTR)p + size <= regionEnd;
}

// A COM object's vtable has to live in the read-only data of some loaded DLL.
static bool HasModuleVtable(void* object) {
    if (!IsReadableMemory(object, sizeof(void*))) {
        return false;
    }

    void* vtable = *(void**)object;
    MEMORY_BASIC_INFORMATION mbi;
    if (!IsReadableMemory(vtable, sizeof(void*)) ||
        !VirtualQuery(vtable, &mbi, sizeof(mbi)) || mbi.Type != MEM_IMAGE) {
        return false;
    }

    void* firstMethod = *(void**)vtable;
    MEMORY_BASIC_INFORMATION methodMbi;
    return IsReadableMemory(firstMethod, 1) &&
           VirtualQuery(firstMethod, &methodMbi, sizeof(methodMbi)) &&
           methodMbi.AllocationBase == mbi.AllocationBase;
}

// ============================================================================
//  CVisual layout fields
//
//  These are the offsets CVisual::UpdateLayout itself uses: it reads the parent
//  from +0x18 and passes the parent's size at +0x48, together with this
//  visual's insets at +0x50, to DoCanvasLayout. SetInsetFromParentLeft/Right
//  write +0x50 and +0x54; SetHeight reads the size at +0x48 as {LONG cx, cy}.
// ============================================================================

constexpr size_t kVisualParentOffset = 0x18;
constexpr size_t kVisualSizeOffset = 0x48;
constexpr size_t kVisualInsetOffset = 0x50;

struct VisualGeometry {
    LONG cx, cy;
    LONG insetLeft, insetRight;
};

static bool GetVisualGeometry(void* pVisual, VisualGeometry* geometry) {
    auto* size = (LONG*)((BYTE*)pVisual + kVisualSizeOffset);
    auto* insets = (LONG*)((BYTE*)pVisual + kVisualInsetOffset);
    if (!IsReadableMemory(size, sizeof(LONG) * 2) ||
        !IsReadableMemory(insets, sizeof(LONG) * 2)) {
        return false;
    }

    geometry->cx = size[0];
    geometry->cy = size[1];
    geometry->insetLeft = insets[0];
    geometry->insetRight = insets[1];
    return true;
}

// The width the insets are measured against - read from the parent rather than
// inferred from this visual, so it is right even mid-resize.
static bool GetParentWidth(void* pVisual, LONG* width) {
    auto* parentSlot = (void**)((BYTE*)pVisual + kVisualParentOffset);
    if (!IsReadableMemory(parentSlot, sizeof(void*))) {
        return false;
    }

    void* parent = *parentSlot;
    if (!parent) {
        return false;
    }

    auto* parentSize = (LONG*)((BYTE*)parent + kVisualSizeOffset);
    if (!IsReadableMemory(parentSize, sizeof(LONG) * 2) || parentSize[0] <= 0) {
        return false;
    }

    *width = parentSize[0];
    return true;
}

// ============================================================================
//  CDWriteText members
//
//  Found by scanning for a member that is a live COM object answering to
//  IDWriteTextLayout, rather than hardcoding a build-specific offset. Scanning
//  only ever happens from inside the CreateTextLayout hook, where the object is
//  known to be a CDWriteText; everywhere else only the cached offset is used.
// ============================================================================

static const GUID kIID_IDWriteTextLayout = {
    0x53737037,
    0x6d14,
    0x410b,
    {0x9b, 0xfe, 0x0b, 0x18, 0x2b, 0xb7, 0x09, 0x61}};

// Range of member offsets scanned inside CDWriteText.
constexpr size_t kScanBegin = 0x40;
constexpr size_t kScanEnd = 0x200;

static bool ImplementsInterface(void* object, const GUID& iid) {
    void* result = nullptr;
    if (FAILED(((IUnknown*)object)->QueryInterface(iid, &result)) || !result) {
        return false;
    }

    ((IUnknown*)result)->Release();
    return true;
}

static void* GetComMember(void* pThis, size_t offset) {
    void** slot = (void**)((BYTE*)pThis + offset);
    if (!IsReadableMemory(slot, sizeof(void*)) || !HasModuleVtable(*slot)) {
        return nullptr;
    }

    return *slot;
}

static volatile size_t g_textLayoutOffset = 0;

// Only call for an object already known to be a CDWriteText.
static IDWriteTextLayout* ResolveTextLayout(void* pCDWriteText) {
    if (g_textLayoutOffset) {
        return (IDWriteTextLayout*)GetComMember(pCDWriteText,
                                                g_textLayoutOffset);
    }

    for (size_t offset = kScanBegin; offset < kScanEnd;
         offset += sizeof(void*)) {
        void* member = GetComMember(pCDWriteText, offset);
        if (member && ImplementsInterface(member, kIID_IDWriteTextLayout)) {
            g_textLayoutOffset = offset;
            Wh_Log(L"Resolved CDWriteText text layout at offset 0x%zX", offset);
            return (IDWriteTextLayout*)member;
        }
    }

    return nullptr;
}

// Confirms an arbitrary visual really is a CDWriteText, guarding against a
// recorded pointer whose object has been destroyed and its memory reused.
static IDWriteTextLayout* GetLiveTextLayout(void* pVisual) {
    if (!g_textLayoutOffset) {
        return nullptr;
    }

    void* member = GetComMember(pVisual, g_textLayoutOffset);
    if (!member || !ImplementsInterface(member, kIID_IDWriteTextLayout)) {
        return nullptr;
    }

    return (IDWriteTextLayout*)member;
}

// ============================================================================
//  Tracking the caption text visuals
//
//  CVisual::SetInsetFromParentLeft is called for every visual DWM lays out, so
//  recognising ours has to be cheap: the pointer scan below is the filter, and
//  only a hit pays for confirmation. Each entry also remembers the inset DWM
//  last asked for, which is where the window icon ends - needed for the clamp
//  once we have overwritten the inset itself.
//
//  Aligned pointer and LONG accesses are atomic on x64, and a stale or torn
//  read can only cost one frame of position, so no lock is needed.
// ============================================================================

constexpr size_t kTextVisualCount = 64;
constexpr LONG kNoTarget = -1;

struct TextVisualInfo {
    void* volatile visual;
    volatile LONG dwmLeft;
};

static TextVisualInfo g_textVisuals[kTextVisualCount];
static volatile LONG g_textVisualNext;

// CDWriteText's own vtable, learned the first time one passes through
// CreateTextLayout. Comparing against it is a single pointer compare, which
// matters in UpdateLayout - that runs for every visual in the tree.
static void* volatile g_textVisualVtable;

static bool HasTextVisualVtable(void* pVisual) {
    void* vtable = g_textVisualVtable;
    return vtable && IsReadableMemory(pVisual, sizeof(void*)) &&
           *(void**)pVisual == vtable;
}

static TextVisualInfo* FindTextVisual(void* pVisual) {
    for (size_t i = 0; i < kTextVisualCount; i++) {
        if (g_textVisuals[i].visual == pVisual) {
            return &g_textVisuals[i];
        }
    }

    return nullptr;
}

static TextVisualInfo* RememberTextVisual(void* pVisual, LONG dwmLeft) {
    TextVisualInfo* entry = FindTextVisual(pVisual);
    if (entry) {
        return entry;
    }

    LONG slot = InterlockedIncrement(&g_textVisualNext);
    entry = &g_textVisuals[(size_t)slot % kTextVisualCount];
    entry->dwmLeft = dwmLeft;
    entry->visual = pVisual;
    return entry;
}

// ============================================================================
//  Hooks
// ============================================================================

// private: long CDWriteText::CreateTextLayout(void)
using CDWriteText_CreateTextLayout_t = HRESULT(WINAPI*)(void* pThis);
CDWriteText_CreateTextLayout_t CDWriteText_CreateTextLayout_Orig;

// public: void CVisual::SetInsetFromParentLeft(int)
using CVisual_SetInsetFromParentLeft_t = void(WINAPI*)(void* pThis, int inset);
CVisual_SetInsetFromParentLeft_t CVisual_SetInsetFromParentLeft_Orig;

// public: virtual long CVisual::UpdateLayout(bool)
using CVisual_UpdateLayout_t = HRESULT(WINAPI*)(void* pThis, bool param);
CVisual_UpdateLayout_t CVisual_UpdateLayout_Orig;

// private: void CTopLevelWindow::GetButtonHeightAndOffset(int*, int*) const
using CTopLevelWindow_GetButtonHeightAndOffset_t = void(WINAPI*)(void* pThis,
                                                                 int* pHeight,
                                                                 int* pOffset);
CTopLevelWindow_GetButtonHeightAndOffset_t
    CTopLevelWindow_GetButtonHeightAndOffset_Orig;

// public: bool CTopLevelWindow::IsMaximizedOrSnapped(void) const
using CTopLevelWindow_IsMaximizedOrSnapped_t = bool(WINAPI*)(void* pThis);
CTopLevelWindow_IsMaximizedOrSnapped_t CTopLevelWindow_IsMaximizedOrSnapped_Orig;

// private: int CTopLevelWindow::GetTitlebarHeight(void) const
using CTopLevelWindow_GetTitlebarHeight_t = int(WINAPI*)(void* pThis);
CTopLevelWindow_GetTitlebarHeight_t CTopLevelWindow_GetTitlebarHeight_Orig;

// ---------------------------------------------------------------------------
//  Where the title should sit
//
//  Everything here is read live, so the answer is correct for the layout pass
//  it is being asked about rather than the one before it.
// ---------------------------------------------------------------------------

static LONG ComputeTarget(void* pVisual,
                          IDWriteTextLayout* layout,
                          LONG dwmLeft) {
    LONG parentWidth;
    if (!GetParentWidth(pVisual, &parentWidth)) {
        return kNoTarget;
    }

    VisualGeometry geometry;
    if (!GetVisualGeometry(pVisual, &geometry) || geometry.insetRight < 0) {
        return kNoTarget;
    }

    DWRITE_TEXT_METRICS metrics;
    if (FAILED(layout->GetMetrics(&metrics))) {
        return kNoTarget;
    }

    LONG textWidth = (LONG)(metrics.width + 0.5f);
    if (textWidth <= 0) {
        return kNoTarget;
    }

    // DWM's right inset is left alone, so it still marks where the caption
    // buttons begin.
    LONG rightEdge = parentWidth - geometry.insetRight;

    LONG centered;
    if (g_settings.centerOnWindow) {
        centered = (parentWidth - textWidth) / 2;
    } else {
        centered = dwmLeft + (rightEdge - dwmLeft - textWidth) / 2;
    }

    // Never over the icon, never under the buttons. A title too long to fit
    // centered keeps the position DWM chose.
    if (centered < dwmLeft || centered + textWidth > rightEdge) {
        return kNoTarget;
    }

    return centered;
}

// ---------------------------------------------------------------------------
//  Learning which visuals hold caption text, and repositioning when the title
//  itself changes rather than the window
// ---------------------------------------------------------------------------

HRESULT WINAPI CDWriteText_CreateTextLayout_Hook(void* pThis) {
    HRESULT hr = CDWriteText_CreateTextLayout_Orig(pThis);
    if (FAILED(hr)) {
        return hr;
    }

    IDWriteTextLayout* layout = ResolveTextLayout(pThis);

    VisualGeometry geometry = {};
    if (!layout || !GetVisualGeometry(pThis, &geometry)) {
        return hr;
    }

    // If this visual is new to us, the inset it currently has is still DWM's.
    TextVisualInfo* entry = RememberTextVisual(pThis, geometry.insetLeft);
    if (!g_textVisualVtable && IsReadableMemory(pThis, sizeof(void*))) {
        g_textVisualVtable = *(void**)pThis;
    }

    if (!g_settings.centerText) {
        return hr;
    }

    LONG target = ComputeTarget(pThis, layout, entry->dwmLeft);

    if (g_settings.verboseLogging) {
        LONG parentWidth = 0;
        GetParentWidth(pThis, &parentWidth);
        DWRITE_TEXT_METRICS metrics = {};
        layout->GetMetrics(&metrics);

        Wh_Log(L"caption text: visual=%dx%d insets l=%d r=%d parent=%d, "
               L"textWidth=%.0f, dwmLeft=%d, target=%d",
               (int)geometry.cx, (int)geometry.cy, (int)geometry.insetLeft,
               (int)geometry.insetRight, (int)parentWidth, metrics.width,
               (int)entry->dwmLeft, (int)target);
    }

    // A title that changed length needs moving even if the window did not
    // change, and there may be no layout pass coming to do it.
    if (target != kNoTarget && target != geometry.insetLeft) {
        CVisual_SetInsetFromParentLeft_Orig(pThis, target);
    }

    return hr;
}

// ---------------------------------------------------------------------------
//  Handing DWM a different left inset than it asked for
// ---------------------------------------------------------------------------

// DWM's value is the one thing this call is good for: it says where the window
// icon ends, which is the left bound the title must not cross. It is recorded
// rather than replaced, because at this point in the frame the parent has not
// been resized yet - DWM positions the caption's children before the layout
// traversal updates their parent - so centering here would use the previous
// window's width.
void WINAPI CVisual_SetInsetFromParentLeft_Hook(void* pThis, int inset) {
    if (g_settings.centerText && HasTextVisualVtable(pThis)) {
        TextVisualInfo* entry = FindTextVisual(pThis);
        if (entry) {
            entry->dwmLeft = inset;
        }
    }

    CVisual_SetInsetFromParentLeft_Orig(pThis, inset);
}

// The title is placed here instead. CVisual::UpdateLayout is the call that
// feeds the parent's size and this visual's insets to DoCanvasLayout, so at
// this instant the parent size is current by construction - there is no layout
// pass left to wait for, and nothing stale to center against.
//
// The inset field is written directly rather than through the setter: the
// layout is about to be recomputed from it anyway, so the setter's dirty flag
// would only schedule redundant work.
HRESULT WINAPI CVisual_UpdateLayout_Hook(void* pThis, bool param) {
    if (g_settings.centerText && HasTextVisualVtable(pThis)) {
        TextVisualInfo* entry = FindTextVisual(pThis);
        IDWriteTextLayout* layout = entry ? GetLiveTextLayout(pThis) : nullptr;

        if (layout) {
            LONG target = ComputeTarget(pThis, layout, entry->dwmLeft);
            auto* insets = (LONG*)((BYTE*)pThis + kVisualInsetOffset);

            if (target != kNoTarget && IsReadableMemory(insets, sizeof(LONG)) &&
                insets[0] != target) {
                insets[0] = target;
            }
        } else if (entry) {
            // Destroyed and its memory reused - stop matching it.
            entry->visual = nullptr;
        }
    }

    return CVisual_UpdateLayout_Orig(pThis, param);
}

// ---------------------------------------------------------------------------
//  Maximized caption button alignment
// ---------------------------------------------------------------------------

static thread_local int g_inGetButtonHeightAndOffset;

void WINAPI CTopLevelWindow_GetButtonHeightAndOffset_Hook(void* pThis,
                                                          int* pHeight,
                                                          int* pOffset) {
    g_inGetButtonHeightAndOffset++;
    CTopLevelWindow_GetButtonHeightAndOffset_Orig(pThis, pHeight, pOffset);
    g_inGetButtonHeightAndOffset--;

    // Nested call (GetTitlebarHeight calls this too, including when we call it
    // ourselves below). Leave those results untouched so we can't recurse.
    if (g_inGetButtonHeightAndOffset > 0) {
        return;
    }

    if (g_settings.maximizedButtons == MAXBTN_NONE || !pHeight || !pOffset) {
        return;
    }

    if (!CTopLevelWindow_IsMaximizedOrSnapped_Orig ||
        !CTopLevelWindow_IsMaximizedOrSnapped_Orig(pThis)) {
        return;
    }

    int before = *pOffset;
    int titlebarHeight = -1;

    if (g_settings.maximizedButtons == MAXBTN_AUTO &&
        CTopLevelWindow_GetTitlebarHeight_Orig) {
        g_inGetButtonHeightAndOffset++;
        titlebarHeight = CTopLevelWindow_GetTitlebarHeight_Orig(pThis);
        g_inGetButtonHeightAndOffset--;

        // DWM's own offset is the top margin plus one, so the top of the
        // drawable caption band can be recovered from it.
        int bandTop = std::max(before - 1, 0);
        int bandHeight = titlebarHeight - bandTop;
        *pOffset = bandTop + std::max((bandHeight - *pHeight) / 2, 0);
    }

    // Applied in every mode, so the automatic result can be nudged too.
    *pOffset = std::max(*pOffset + g_settings.maximizedButtonOffset, 0);

    if (g_settings.verboseLogging) {
        Wh_Log(L"maximized buttons: height=%d titlebarHeight=%d offset %d -> %d",
               *pHeight, titlebarHeight, before, *pOffset);
    }
}

// ============================================================================
//  Init
// ============================================================================

BOOL Wh_ModInit() {
    LoadSettings();

    HMODULE udwm = LoadLibrary(L"uDWM.dll");
    if (!udwm) {
        Wh_Log(L"Failed to load uDWM.dll - is Windhawk allowed to inject into "
               L"system processes?");
        return FALSE;
    }

    // Both spellings are listed because Windhawk's undecorated symbol strings
    // have dropped the __ptr64 suffix across versions.
    WindhawkUtils::SYMBOL_HOOK hooks[] = {
        {
            {LR"(private: long __cdecl CDWriteText::CreateTextLayout(void) __ptr64)",
             LR"(private: long __cdecl CDWriteText::CreateTextLayout(void))"},
            &CDWriteText_CreateTextLayout_Orig,
            CDWriteText_CreateTextLayout_Hook,
        },
        {
            {LR"(public: void __cdecl CVisual::SetInsetFromParentLeft(int) __ptr64)",
             LR"(public: void __cdecl CVisual::SetInsetFromParentLeft(int))"},
            &CVisual_SetInsetFromParentLeft_Orig,
            CVisual_SetInsetFromParentLeft_Hook,
        },
        {
            {LR"(public: virtual long __cdecl CVisual::UpdateLayout(bool) __ptr64)",
             LR"(public: virtual long __cdecl CVisual::UpdateLayout(bool))"},
            &CVisual_UpdateLayout_Orig,
            CVisual_UpdateLayout_Hook,
        },
        {
            {LR"(private: void __cdecl CTopLevelWindow::GetButtonHeightAndOffset(int * __ptr64,int * __ptr64)const __ptr64)",
             LR"(private: void __cdecl CTopLevelWindow::GetButtonHeightAndOffset(int *,int *)const )"},
            &CTopLevelWindow_GetButtonHeightAndOffset_Orig,
            CTopLevelWindow_GetButtonHeightAndOffset_Hook,
        },
        {
            {LR"(public: bool __cdecl CTopLevelWindow::IsMaximizedOrSnapped(void)const __ptr64)",
             LR"(public: bool __cdecl CTopLevelWindow::IsMaximizedOrSnapped(void)const )"},
            &CTopLevelWindow_IsMaximizedOrSnapped_Orig,
            nullptr,  // resolve only
        },
        {
            {LR"(private: int __cdecl CTopLevelWindow::GetTitlebarHeight(void)const __ptr64)",
             LR"(private: int __cdecl CTopLevelWindow::GetTitlebarHeight(void)const )"},
            &CTopLevelWindow_GetTitlebarHeight_Orig,
            nullptr,  // resolve only
        },
    };

    if (!WindhawkUtils::HookSymbols(udwm, hooks, ARRAYSIZE(hooks))) {
        Wh_Log(L"Failed to hook uDWM.dll symbols");
        return FALSE;
    }

    return TRUE;
}

void Wh_ModSettingsChanged() {
    LoadSettings();
}

void Wh_ModUninit() {
    Wh_Log(L"Uninit");
}
