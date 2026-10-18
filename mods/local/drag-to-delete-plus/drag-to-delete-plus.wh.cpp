// ==WindhawkMod==
// @id              drag-to-delete-plus
// @name            Drag to Delete Plus
// @description     Drag files onto a floating trash target with themes, shapes and colors
// @version         1.1.0
// @author          DavidHiFi, iMAboud
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         explorer.exe
// @compilerOptions -lole32 -lgdi32 -lshell32 -lgdiplus
// @donateUrl    https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Drag to Delete Plus

A floating trash target appears while you drag files, so you can drop them
straight into the Recycle Bin. Glass, acrylic and mica finishes, round or
squircle shapes, and full color control, in Catppuccin Mocha with a blue
accent out of the box.

![Drag to Delete Plus preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/drag-to-delete-plus.png)

## Features

- **Five background finishes.** Glass, acrylic, mica, solid or clear, with a
  soft top gloss on the frosted ones. The dynamic backdrop blend samples the
  real pixels behind the target, so its rim melts into the taskbar or desktop
  with no visible edge on any theme.
- **Circle or rounded-square target** with adjustable diameter, corner radius,
  border width and drop shadow.
- **Every color is yours.** Background gradient, border, trash icon, shadow
  and the hint label, each with its own hover color.
- **Blue hover glow.** The ring and icon light up and the target grows when
  your files are over it.
- **Top or bottom placement** with an edge offset, per-monitor DPI aware.
- **Hint label** under the target, with custom text.
- **Tunable motion.** Animation speed, hover grow amount and overall opacity.

## How to use

Drag any file or folder and the target fades in. Drop the files on it to move
them to the Recycle Bin, or let go anywhere else to cancel. Disable the
original Drag to Delete before enabling this mod.

## Credits

Based on [Drag to Delete](https://windhawk.net/mods/drag-to-delete) by
iMAboud.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- material: glass
  $name: Background finish
  $description: The look of the target surface. Glass and acrylic add a soft top gloss; mica is flat; solid is opaque; clear draws only the ring and icon.
  $options:
  - glass: Glass
  - acrylic: Acrylic
  - mica: Mica
  - solid: Solid
  - clear: Clear
- dynamicBackdrop: true
  $name: Dynamic backdrop blend
  $description: Sample the real pixels behind the target and tune the fill so its rim melts into the taskbar or desktop with no visible edge. Turn off to use the custom background colors below.
- shape: circle
  $name: Target shape
  $description: A circle, or a rounded square whose corners use the corner radius below.
  $options:
  - circle: Circle
  - rounded: Rounded square
- cornerRadius: 30
  $name: Corner radius
  $description: Corner roundness in pixels at 100 percent scaling, for the rounded square shape. Valid range is 0 to 64; default is 30.
- targetDiameter: 68
  $name: Target size
  $description: Diameter of the target in pixels at 100 percent scaling. Valid range is 40 to 128; default is 68.
- borderWidth: 2
  $name: Border width
  $description: Ring thickness in pixels at 100 percent scaling. Valid range is 1 to 8; default is 2.
- showShadow: true
  $name: Drop shadow
  $description: Draw a soft shadow under the target. On by default.
- windowOpacity: 100
  $name: Window opacity
  $description: Overall opacity of the floating target from 40 to 100 percent. Default is 100.
- animationSpeed: 5
  $name: Animation speed
  $description: How quickly the target fades, grows and shrinks, from 1 (slow) to 10 (snappy). Default is 5.
- hoverScale: 120
  $name: Hover grow
  $description: Target size while your files hover over it, in percent. Valid range is 100 to 160; default is 120.
- position: top
  $name: Screen position
  $description: Whether the target floats near the top or the bottom edge of the monitor you are dragging on.
  $options:
  - top: Top center
  - bottom: Bottom center
- edgeOffset: 8
  $name: Edge offset
  $description: Distance in pixels from the top or bottom screen edge. Valid range is 0 to 128; default is 8.
- backgroundTop: "#D9323244"
  $name: Background top color
  $description: Top of the background gradient. Hex ARGB such as #D9323244, RGB such as #313244, or a color name such as Blue.
- backgroundBottom: "#BE1E1E2E"
  $name: Background bottom color
  $description: Bottom of the background gradient. Hex ARGB such as #BE1E1E2E, RGB such as #1E1E2E, or a color name.
- borderColor: "#5989B4FA"
  $name: Border color
  $description: Ring color at rest. Hex ARGB such as #5989B4FA, or a color name.
- hoverBorderColor: "#CC89B4FA"
  $name: Hover border color
  $description: Ring color while your files hover over the target. Hex ARGB such as #CC89B4FA, or a color name.
- iconColor: "#F2CDD6F4"
  $name: Trash icon color
  $description: Trash can color at rest. Hex ARGB such as #F2CDD6F4, or a color name.
- hoverIconColor: "#FF89B4FA"
  $name: Hover trash icon color
  $description: Trash can color while your files hover over the target. Hex ARGB such as #FF89B4FA, or a color name.
- shadowColor: "#40000000"
  $name: Shadow color
  $description: Drop shadow color. Hex ARGB such as #40000000, or a color name.
- labelColor: "#E6CDD6F4"
  $name: Label color
  $description: Hint text color under the target. Hex ARGB such as #E6CDD6F4, or a color name.
- showLabel: true
  $name: Show hint label
  $description: Show a short hint under the target while dragging. On by default.
- labelText: "Release to delete"
  $name: Hint label text
  $description: The hint shown under the target while dragging.
*/
// ==/WindhawkModSettings==

#include <shlobj.h>
#include <gdiplus.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cwctype>
#include <windhawk_utils.h>

using namespace Gdiplus;

enum class PlusMaterial { GLASS = 0, ACRYLIC = 1, MICA = 2, SOLID = 3, CLEAR = 4 };
enum class PlusShape { CIRCLE = 0, ROUNDED = 1 };
enum class PlusPosition { TOP = 0, BOTTOM = 1 };

struct PlusSettings {
    PlusMaterial material = PlusMaterial::GLASS;
    bool dynamicBackdrop = true;
    PlusShape shape = PlusShape::CIRCLE;
    int cornerRadius = 30;
    int targetDiameter = 68;
    int borderWidth = 2;
    bool showShadow = true;
    int windowOpacity = 100;
    int animationSpeed = 5;
    int hoverScale = 120;
    PlusPosition position = PlusPosition::TOP;
    int edgeOffset = 8;
    Color backgroundTop = Color(0xD9, 0x31, 0x32, 0x44);
    Color backgroundBottom = Color(0xBE, 0x1E, 0x1E, 0x2E);
    Color borderColor = Color(0x59, 0x89, 0xB4, 0xFA);
    Color hoverBorderColor = Color(0xCC, 0x89, 0xB4, 0xFA);
    Color iconColor = Color(0xF2, 0xCD, 0xD6, 0xF4);
    Color hoverIconColor = Color(0xFF, 0x89, 0xB4, 0xFA);
    Color shadowColor = Color(0x40, 0x00, 0x00, 0x00);
    Color labelColor = Color(0xE6, 0xCD, 0xD6, 0xF4);
    bool showLabel = true;
    std::wstring labelText = L"Release to delete";
};

static PlusSettings g_settings;
static bool g_hovered = false;

static const float BASE_HIT_MARGIN = 16.0f;

constexpr WCHAR kClassName[] = L"WindhawkDragToDeletePlusOverlay";

enum class AnimState { HIDDEN, VISIBLE, DROPPED };

static HWND g_hOverlayWnd = nullptr;
static HANDLE g_hUIThread = nullptr;
static DWORD g_dwUIThreadId = 0;
static HANDLE g_readyEvent = nullptr;
static LONG g_activeDrags = 0;
static ULONG_PTR g_gdiplusToken = 0;

static HANDLE g_hDeleteWorker = nullptr;
static HANDLE g_hDeleteQueueEvent = nullptr;
static HANDLE g_hDeleteStopEvent = nullptr;
static CRITICAL_SECTION g_deleteCs;
static std::vector<std::vector<wchar_t>> g_deleteQueue;

static RECT g_targetWorkArea = {};
static float g_currentDpiScale = 1.0f;
static AnimState g_animState = AnimState::HIDDEN;
static float g_currentScale = 0.0f;
static float g_targetScale = 0.0f;
static float g_lastRenderedScale = -1.0f;

#define WM_UPDATE_DRAG_STATE (WM_USER + 101)
#define TIMER_ANIM 1

static int ClampInt(int value, int minimum, int maximum) {
    return std::clamp(value, minimum, maximum);
}

static bool EqualsNoCase(const std::wstring& a, const std::wstring& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++) {
        if (std::towlower(a[i]) != std::towlower(b[i])) return false;
    }
    return true;
}

static std::wstring GetStringSettingValue(PCWSTR name) {
    PCWSTR raw = Wh_GetStringSetting(name);
    std::wstring value = raw ? raw : L"";
    if (raw) {
        Wh_FreeStringSetting(raw);
    }
    return value;
}

static bool ParseHexColor(const std::wstring& text, Color& color) {
    std::wstring value = text;
    if (!value.empty() && value[0] == L'#') {
        value.erase(value.begin());
    } else if (value.size() > 2 && value[0] == L'0' &&
               (value[1] == L'x' || value[1] == L'X')) {
        value.erase(0, 2);
    } else {
        return false;
    }

    std::wstring argb;
    if (value.size() == 8) {
        argb = value;
    } else if (value.size() == 6) {
        argb = L"FF" + value;
    } else if (value.size() == 4 || value.size() == 3) {
        argb = L"";
        if (value.size() == 3) argb += L"FF";
        size_t start = (value.size() == 3) ? 0 : 1;
        if (value.size() == 4) argb += value[0], argb += value[0];
        for (size_t i = start; i < value.size(); i++) {
            argb += value[i];
            argb += value[i];
        }
    } else {
        return false;
    }

    wchar_t* end = nullptr;
    unsigned long parsed = wcstoul(argb.c_str(), &end, 16);
    if (!end || *end != L'\0' || parsed > 0xFFFFFFFFul) {
        return false;
    }

    color = Color((BYTE)((parsed >> 24) & 0xFF),
                  (BYTE)((parsed >> 16) & 0xFF),
                  (BYTE)((parsed >> 8) & 0xFF),
                  (BYTE)(parsed & 0xFF));
    return true;
}

static bool ParseNamedColor(const std::wstring& text, Color& color) {
    struct NamedColor { PCWSTR name; BYTE r; BYTE g; BYTE b; };
    static const NamedColor kNames[] = {
        { L"black", 0x00, 0x00, 0x00 },       { L"white", 0xFF, 0xFF, 0xFF },
        { L"red", 0xF3, 0x8B, 0xA8 },         { L"green", 0xA6, 0xE3, 0xA1 },
        { L"yellow", 0xF9, 0xE2, 0xAF },      { L"blue", 0x89, 0xB4, 0xFA },
        { L"pink", 0xF5, 0xC2, 0xE7 },        { L"teal", 0x94, 0xE2, 0xD5 },
        { L"lavender", 0xB4, 0xBE, 0xFE },    { L"text", 0xCD, 0xD6, 0xF4 },
        { L"subtext", 0xA6, 0xAD, 0xC8 },     { L"base", 0x1E, 0x1E, 0x2E },
        { L"surface", 0x31, 0x32, 0x44 },     { L"transparent", 0x00, 0x00, 0x00 },
    };
    for (const auto& entry : kNames) {
        if (EqualsNoCase(text, entry.name)) {
            BYTE alpha = EqualsNoCase(text, L"transparent") ? 0x00 : 0xFF;
            color = Color(alpha, entry.r, entry.g, entry.b);
            return true;
        }
    }
    return false;
}

static Color GetColorSetting(PCWSTR name, Color fallback) {
    std::wstring text = GetStringSettingValue(name);
    Color color = fallback;
    if (!text.empty() &&
        (ParseHexColor(text, color) || ParseNamedColor(text, color))) {
        return color;
    }
    return fallback;
}

static void LoadSettings() {
    PlusSettings defaults;

    std::wstring material = GetStringSettingValue(L"material");
    if (EqualsNoCase(material, L"acrylic")) {
        g_settings.material = PlusMaterial::ACRYLIC;
    } else if (EqualsNoCase(material, L"mica")) {
        g_settings.material = PlusMaterial::MICA;
    } else if (EqualsNoCase(material, L"solid")) {
        g_settings.material = PlusMaterial::SOLID;
    } else if (EqualsNoCase(material, L"clear")) {
        g_settings.material = PlusMaterial::CLEAR;
    } else {
        g_settings.material = PlusMaterial::GLASS;
    }

    std::wstring shape = GetStringSettingValue(L"shape");
    g_settings.shape = EqualsNoCase(shape, L"rounded") ? PlusShape::ROUNDED
                                                      : PlusShape::CIRCLE;

    g_settings.cornerRadius = ClampInt(Wh_GetIntSetting(L"cornerRadius"),
                                       0, 64);
    g_settings.targetDiameter = Wh_GetIntSetting(L"targetDiameter");
    if (g_settings.targetDiameter <= 0) {
        g_settings.targetDiameter = defaults.targetDiameter;
    }
    g_settings.targetDiameter = ClampInt(g_settings.targetDiameter, 40, 128);

    g_settings.borderWidth = Wh_GetIntSetting(L"borderWidth");
    if (g_settings.borderWidth <= 0) {
        g_settings.borderWidth = defaults.borderWidth;
    }
    g_settings.borderWidth = ClampInt(g_settings.borderWidth, 1, 8);

    g_settings.showShadow = Wh_GetIntSetting(L"showShadow") != 0;
    g_settings.dynamicBackdrop = Wh_GetIntSetting(L"dynamicBackdrop") != 0;

    g_settings.windowOpacity = Wh_GetIntSetting(L"windowOpacity");
    if (g_settings.windowOpacity <= 0) {
        g_settings.windowOpacity = defaults.windowOpacity;
    }
    g_settings.windowOpacity = ClampInt(g_settings.windowOpacity, 40, 100);

    g_settings.animationSpeed = Wh_GetIntSetting(L"animationSpeed");
    if (g_settings.animationSpeed <= 0) {
        g_settings.animationSpeed = defaults.animationSpeed;
    }
    g_settings.animationSpeed = ClampInt(g_settings.animationSpeed, 1, 10);

    g_settings.hoverScale = Wh_GetIntSetting(L"hoverScale");
    if (g_settings.hoverScale <= 0) {
        g_settings.hoverScale = defaults.hoverScale;
    }
    g_settings.hoverScale = ClampInt(g_settings.hoverScale, 100, 160);

    std::wstring position = GetStringSettingValue(L"position");
    g_settings.position = EqualsNoCase(position, L"bottom") ? PlusPosition::BOTTOM
                                                            : PlusPosition::TOP;

    g_settings.edgeOffset = Wh_GetIntSetting(L"edgeOffset");
    if (g_settings.edgeOffset < 0) {
        g_settings.edgeOffset = defaults.edgeOffset;
    }
    g_settings.edgeOffset = ClampInt(g_settings.edgeOffset, 0, 128);

    g_settings.backgroundTop = GetColorSetting(L"backgroundTop", defaults.backgroundTop);
    g_settings.backgroundBottom = GetColorSetting(L"backgroundBottom", defaults.backgroundBottom);
    g_settings.borderColor = GetColorSetting(L"borderColor", defaults.borderColor);
    g_settings.hoverBorderColor = GetColorSetting(L"hoverBorderColor", defaults.hoverBorderColor);
    g_settings.iconColor = GetColorSetting(L"iconColor", defaults.iconColor);
    g_settings.hoverIconColor = GetColorSetting(L"hoverIconColor", defaults.hoverIconColor);
    g_settings.shadowColor = GetColorSetting(L"shadowColor", defaults.shadowColor);
    g_settings.labelColor = GetColorSetting(L"labelColor", defaults.labelColor);

    g_settings.showLabel = Wh_GetIntSetting(L"showLabel") != 0;
    std::wstring labelText = GetStringSettingValue(L"labelText");
    if (!labelText.empty()) {
        g_settings.labelText = labelText;
    } else {
        g_settings.labelText = defaults.labelText;
    }
}

HMODULE GetCurrentModuleHandle() {
    HMODULE hModule = nullptr;
    GetModuleHandleExW(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPCWSTR)GetCurrentModuleHandle,
        &hModule
    );
    return hModule;
}

static UINT GetMonitorDpi(HMONITOR hMon) {
    if (hMon) {
        static auto pfnGetDpiForMonitor =
            (HRESULT(WINAPI*)(HMONITOR, int, UINT*, UINT*))
            GetProcAddress(GetModuleHandleW(L"shcore.dll"), "GetDpiForMonitor");
        if (!pfnGetDpiForMonitor) {
            HMODULE hShcore = LoadLibraryW(L"shcore.dll");
            if (hShcore) {
                pfnGetDpiForMonitor =
                    (HRESULT(WINAPI*)(HMONITOR, int, UINT*, UINT*))
                    GetProcAddress(hShcore, "GetDpiForMonitor");
            }
        }
        if (pfnGetDpiForMonitor) {
            UINT dpiX = 96, dpiY = 96;
            if (SUCCEEDED(pfnGetDpiForMonitor(hMon, 0 /* MDT_EFFECTIVE_DPI */, &dpiX, &dpiY))) {
                if (dpiX > 0) return dpiX;
            }
        }
    }
    return 96;
}

struct TargetGeometry {
    int wndWidth = 0;
    int wndHeight = 0;
    float cx = 0.0f;
    float cy = 0.0f;
    float radius = 0.0f;
    int wndLeft = 0;
    int wndTop = 0;
};

static TargetGeometry ComputeGeometry() {
    TargetGeometry geo;
    float dpiScale = g_currentDpiScale;
    float diameter = (float)g_settings.targetDiameter * dpiScale;
    float r = diameter / 2.0f;

    geo.wndWidth = (int)(diameter + 132.0f * dpiScale);
    geo.wndHeight = (int)(diameter + 92.0f * dpiScale);
    geo.cx = (float)geo.wndWidth / 2.0f;
    geo.cy = 16.0f * dpiScale + r;
    geo.radius = r;

    int monLeft = g_targetWorkArea.left;
    int monWidth = g_targetWorkArea.right - g_targetWorkArea.left;
    geo.wndLeft = monLeft + (monWidth - geo.wndWidth) / 2;
    if (g_settings.position == PlusPosition::BOTTOM) {
        geo.wndTop = g_targetWorkArea.bottom - geo.wndHeight -
                     (int)((float)g_settings.edgeOffset * dpiScale);
    } else {
        geo.wndTop = g_targetWorkArea.top +
                     (int)((float)g_settings.edgeOffset * dpiScale);
    }
    return geo;
}

static void MakeTargetPath(GraphicsPath& path, float cx, float cy, float half,
                            float cornerRadius) {
    path.Reset();
    if (g_settings.shape == PlusShape::ROUNDED) {
        float r = std::min(cornerRadius, half);
        if (r < 1.0f) {
            path.AddRectangle(RectF(cx - half, cy - half, half * 2, half * 2));
            return;
        }
        float left = cx - half;
        float top = cy - half;
        float d = half * 2;
        path.AddArc(left, top, r * 2, r * 2, 180, 90);
        path.AddArc(left + d - r * 2, top, r * 2, r * 2, 270, 90);
        path.AddArc(left + d - r * 2, top + d - r * 2, r * 2, r * 2, 0, 90);
        path.AddArc(left, top + d - r * 2, r * 2, r * 2, 90, 90);
        path.CloseFigure();
    } else {
        path.AddEllipse(cx - half, cy - half, half * 2, half * 2);
    }
}

static bool PointHitsTarget(POINTL pt, const TargetGeometry& geo) {
    float dpiScale = g_currentDpiScale;
    float margin = BASE_HIT_MARGIN * dpiScale;
    float half = geo.radius * g_currentScale;
    float dx = (float)(pt.x - geo.wndLeft) - geo.cx;
    float dy = (float)(pt.y - geo.wndTop) - geo.cy;

    if (g_settings.shape == PlusShape::ROUNDED) {
        float expanded = half + margin;
        float ax = std::abs(dx);
        float ay = std::abs(dy);
        float r = std::min((float)g_settings.cornerRadius * dpiScale, half);
        float inner = std::max(expanded - r, 0.0f);
        float ox = std::max(ax - inner, 0.0f);
        float oy = std::max(ay - inner, 0.0f);
        return (ox * ox + oy * oy) <= (r + margin) * (r + margin) &&
               ax <= expanded && ay <= expanded;
    }

    float hitRadius = half + margin;
    return (dx * dx + dy * dy) <= (hitRadius * hitRadius);
}

void RenderFrame(HWND hWnd);
void MoveFilesToRecycleBin(const std::vector<wchar_t>& buffer);

void DrawModernTrashIcon(Graphics& g, float cx, float cy, float scale, Color color) {
    SolidBrush brush(color);
    float s = scale;

    Pen handlePen(color, 2.5f * s);
    handlePen.SetStartCap(LineCapRound);
    handlePen.SetEndCap(LineCapRound);
    g.DrawLine(&handlePen, cx - 4.5f * s, cy - 16.5f * s, cx + 4.5f * s, cy - 16.5f * s);

    Pen lidPen(color, 3.5f * s);
    lidPen.SetStartCap(LineCapRound);
    lidPen.SetEndCap(LineCapRound);
    g.DrawLine(&lidPen, cx - 14.0f * s, cy - 12.0f * s, cx + 14.0f * s, cy - 12.0f * s);

    GraphicsPath bodyPath;
    float topW = 12.0f * s;
    float botW = 9.5f * s;
    float topY = cy - 8.0f * s;
    float botY = cy + 15.0f * s;
    float r = 3.5f * s;

    bodyPath.AddLine(cx - topW, topY, cx + topW, topY);
    bodyPath.AddLine(cx + topW, topY, cx + botW, botY - r);
    bodyPath.AddArc(cx + botW - r * 2, botY - r * 2, r * 2, r * 2, 0, 90);
    bodyPath.AddLine(cx + botW - r, botY, cx - botW + r, botY);
    bodyPath.AddArc(cx - botW, botY - r * 2, r * 2, r * 2, 90, 90);
    bodyPath.AddLine(cx - botW, botY - r, cx - topW, topY);
    bodyPath.CloseFigure();
    g.FillPath(&brush, &bodyPath);

    float luminance = (0.299f * (float)color.GetR() +
                       0.587f * (float)color.GetG() +
                       0.114f * (float)color.GetB()) / 255.0f;
    Color slotColor = luminance > 0.5f ? Color(180, 22, 22, 26)
                                       : Color(180, 230, 230, 240);
    Pen slotPen(slotColor, 1.8f * s);
    slotPen.SetStartCap(LineCapRound);
    slotPen.SetEndCap(LineCapRound);
    for (float off : { -4.5f * s, 0.0f, 4.5f * s }) {
        g.DrawLine(&slotPen, cx + off, topY + 4.0f * s, cx + off, botY - 4.0f * s);
    }
}

static inline BYTE LiftByte(int value, int amount) {
    int v = value + amount;
    if (v < 0) v = 0;
    if (v > 255) v = 255;
    return (BYTE)v;
}

// Reads the real pixels beside the target so the fill can melt into whatever
// is actually behind it: plain taskbar, acrylic taskbar, desktop, anything.
// Sample points sit clear of the circle, its shadow and the hint label, and
// layered-window transparency means they read the true backdrop, not us.
static COLORREF SampleBackdropColor(HDC hdcScreen, const TargetGeometry& geo) {
    int rowY = geo.wndTop + (int)geo.cy;
    int insetX = (int)(18.0f * g_currentDpiScale);
    POINT samples[] = {
        { geo.wndLeft + insetX, rowY },
        { geo.wndLeft + geo.wndWidth - insetX - 1, rowY },
        { geo.wndLeft - 6, rowY },
        { geo.wndLeft + geo.wndWidth + 6, rowY },
    };
    int red = 0, green = 0, blue = 0, taken = 0;
    for (const POINT& pt : samples) {
        COLORREF c = GetPixel(hdcScreen, pt.x, pt.y);
        if (c == CLR_INVALID) continue;
        red += GetRValue(c);
        green += GetGValue(c);
        blue += GetBValue(c);
        taken++;
    }
    if (!taken) {
        Color fallback = g_settings.backgroundBottom;
        return RGB(fallback.GetR(), fallback.GetG(), fallback.GetB());
    }
    return RGB(red / taken, green / taken, blue / taken);
}

void RenderFrame(HWND hWnd) {
    if (g_animState == AnimState::HIDDEN || g_currentScale < 0.05f) return;

    float dpiScale = g_currentDpiScale;
    TargetGeometry geo = ComputeGeometry();
    int wndWidth = geo.wndWidth;
    int wndHeight = geo.wndHeight;

    HDC hdcScreen = GetDC(nullptr);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = wndWidth;
    bmi.bmiHeader.biHeight = -wndHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* pBits = nullptr;
    HBITMAP hBitmap = CreateDIBSection(hdcMem, &bmi, DIB_RGB_COLORS, &pBits, nullptr, 0);
    HGDIOBJ hOldBitmap = SelectObject(hdcMem, hBitmap);

    {
        Bitmap bmp(wndWidth, wndHeight, wndWidth * 4, PixelFormat32bppPARGB, (BYTE*)pBits);
        Graphics g(&bmp);
        g.SetSmoothingMode(SmoothingModeAntiAlias);
        g.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);

        float r = geo.radius * g_currentScale;
        float corner = (float)g_settings.cornerRadius * dpiScale;
        bool hovered = g_hovered;
        Color border = hovered ? g_settings.hoverBorderColor : g_settings.borderColor;
        Color icon = hovered ? g_settings.hoverIconColor : g_settings.iconColor;

        COLORREF backdrop = SampleBackdropColor(hdcScreen, geo);
        auto backdropColor = [&backdrop](BYTE alpha) {
            return Color(alpha, GetRValue(backdrop), GetGValue(backdrop),
                         GetBValue(backdrop));
        };

        if (g_settings.showShadow) {
            // Soft radial shadow that fades to fully transparent, instead of a
            // solid offset fill that ended in a hard dark arc under the target.
            float drop = 2.5f * dpiScale;
            float grow = 1.5f * dpiScale;
            GraphicsPath shadowPath;
            if (g_settings.shape == PlusShape::ROUNDED) {
                MakeTargetPath(shadowPath, geo.cx, geo.cy + drop, r + grow,
                               corner);
            } else {
                shadowPath.AddEllipse(geo.cx - r - grow, geo.cy - r + drop,
                                      (r + grow) * 2, (r + grow) * 2);
            }
            Color shadowColor = g_settings.shadowColor;
            PathGradientBrush shadowBrush(&shadowPath);
            shadowBrush.SetCenterColor(shadowColor);
            Color shadowEdge(0, shadowColor.GetR(), shadowColor.GetG(),
                             shadowColor.GetB());
            INT shadowCount = 1;
            shadowBrush.SetSurroundColors(&shadowEdge, &shadowCount);
            g.FillPath(&shadowBrush, &shadowPath);
        }

        GraphicsPath targetPath;
        MakeTargetPath(targetPath, geo.cx, geo.cy, r, corner);

        if (g_settings.material != PlusMaterial::CLEAR) {
            bool dynamic = g_settings.dynamicBackdrop;
            PlusMaterial material = g_settings.material;

            // The rim always lands exactly on the backdrop, so the edge of the
            // target dissolves into the taskbar or desktop with no visible seam.
            Color centerColor, edgeColor;
            BYTE glossAlpha = 0;
            BYTE veilAlpha = 0;
            switch (material) {
            case PlusMaterial::ACRYLIC:
                centerColor = dynamic ? Color(0xE8, LiftByte(GetRValue(backdrop), 12),
                                              LiftByte(GetGValue(backdrop), 12),
                                              LiftByte(GetBValue(backdrop), 12))
                                      : g_settings.backgroundTop;
                edgeColor = dynamic ? backdropColor(0xD0) : g_settings.backgroundBottom;
                glossAlpha = 26;
                veilAlpha = 6;
                break;
            case PlusMaterial::MICA:
                centerColor = dynamic ? Color(0xDC, LiftByte(GetRValue(backdrop), 6),
                                              LiftByte(GetGValue(backdrop), 6),
                                              LiftByte(GetBValue(backdrop), 6))
                                      : g_settings.backgroundTop;
                edgeColor = dynamic ? backdropColor(0xE0) : g_settings.backgroundBottom;
                veilAlpha = 4;
                break;
            case PlusMaterial::SOLID:
                centerColor = dynamic ? backdropColor(255) : g_settings.backgroundTop;
                edgeColor = centerColor;
                break;
            case PlusMaterial::GLASS:
            default:
                centerColor = dynamic ? Color(0xF2, LiftByte(GetRValue(backdrop), 22),
                                              LiftByte(GetGValue(backdrop), 22),
                                              LiftByte(GetBValue(backdrop), 22))
                                      : g_settings.backgroundTop;
                edgeColor = dynamic ? backdropColor(0xC0) : g_settings.backgroundBottom;
                glossAlpha = 14;
                break;
            }

            if (material == PlusMaterial::SOLID) {
                SolidBrush flatBrush(centerColor);
                g.FillPath(&flatBrush, &targetPath);
            } else {
                PathGradientBrush radialBrush(&targetPath);
                radialBrush.SetCenterPoint(PointF(geo.cx, geo.cy));
                radialBrush.SetCenterColor(centerColor);
                Color surroundColors[] = { edgeColor };
                INT count = 1;
                radialBrush.SetSurroundColors(surroundColors, &count);
                radialBrush.SetBlendTriangularShape(0.20f, 0.9f);
                g.FillPath(&radialBrush, &targetPath);
            }

            if (veilAlpha) {
                // Even, full-target tint: mica and acrylic are uniform, never a
                // one-sided band that leaves the bottom darker.
                SolidBrush veilBrush(Color(veilAlpha, 255, 255, 255));
                g.FillPath(&veilBrush, &targetPath);
            }

            if (glossAlpha) {
                // Gloss now fades to nothing past mid-circle instead of being a
                // hard ellipse that stops at 80 percent height and left a dark
                // crescent at the bottom.
                g.SetClip(&targetPath);
                LinearGradientBrush glossBrush(
                    PointF(geo.cx, geo.cy - r),
                    PointF(geo.cx, geo.cy - r + 1.25f * r),
                    Color(glossAlpha, 255, 255, 255), Color(0, 255, 255, 255));
                g.FillRectangle(&glossBrush, 0.0f, 0.0f, (REAL)wndWidth,
                                (REAL)wndHeight);
                g.ResetClip();
            }
        }

        float penWidth = (float)g_settings.borderWidth * dpiScale;
        Pen edgePen(border, penWidth);
        edgePen.SetAlignment(PenAlignmentInset);
        if (g_settings.shape == PlusShape::ROUNDED) {
            g.DrawPath(&edgePen, &targetPath);
        } else {
            float inset = penWidth / 2.0f;
            g.DrawEllipse(&edgePen, geo.cx - r + inset, geo.cy - r + inset,
                          (r - inset) * 2, (r - inset) * 2);
        }

        float iconScale = g_currentScale * dpiScale *
                          ((float)g_settings.targetDiameter / 68.0f);
        DrawModernTrashIcon(g, geo.cx, geo.cy, iconScale, icon);

        if (g_settings.showLabel && !g_settings.labelText.empty()) {
            FontFamily fontFamily(L"Segoe UI");
            REAL fontSize = 12.0f * dpiScale;
            Gdiplus::Font labelFont(&fontFamily, fontSize, FontStyleRegular,
                                    UnitPixel);
            StringFormat format;
            format.SetAlignment(StringAlignmentCenter);
            float labelTop = geo.cy + r + 6.0f * dpiScale;
            RectF layout(0.0f, labelTop, (REAL)wndWidth, 30.0f * dpiScale);
            SolidBrush labelShadow(Color(170, 0, 0, 0));
            RectF shadowLayout(1.0f, labelTop + 1.0f, (REAL)wndWidth,
                               30.0f * dpiScale);
            g.DrawString(g_settings.labelText.c_str(), -1, &labelFont,
                         shadowLayout, &format, &labelShadow);
            SolidBrush labelBrush(g_settings.labelColor);
            g.DrawString(g_settings.labelText.c_str(), -1, &labelFont,
                         layout, &format, &labelBrush);
        }
    }

    POINT ptDst = { geo.wndLeft, geo.wndTop };
    POINT ptSrc = { 0, 0 };
    SIZE wndSize = { wndWidth, wndHeight };
    BLENDFUNCTION blend = { AC_SRC_OVER, 0,
        (BYTE)(g_settings.windowOpacity * 255 / 100), AC_SRC_ALPHA };

    UpdateLayeredWindow(hWnd, hdcScreen, &ptDst, &wndSize, hdcMem, &ptSrc, 0,
                        &blend, ULW_ALPHA);

    SelectObject(hdcMem, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(nullptr, hdcScreen);
}

class CRecycleDropTarget final : public IDropTarget {
    LONG m_refCount = 1;
    bool m_hasHDrop = false;

    bool IsOverTrash(POINTL pt) {
        if (!g_hOverlayWnd) return false;
        TargetGeometry geo = ComputeGeometry();
        return PointHitsTarget(pt, geo);
    }

    void UpdateHoverState(POINTL pt, DWORD* pdwEffect) {
        bool canMove = pdwEffect && (*pdwEffect & DROPEFFECT_MOVE);
        if (m_hasHDrop && canMove && IsOverTrash(pt)) {
            *pdwEffect = DROPEFFECT_MOVE;
            g_hovered = true;
            g_targetScale = (float)g_settings.hoverScale / 100.0f;
        } else {
            if (pdwEffect) *pdwEffect = DROPEFFECT_NONE;
            g_hovered = false;
            g_targetScale = 1.0f;
        }
    }

public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv) override {
        if (riid == __uuidof(IUnknown) || riid == __uuidof(IDropTarget)) {
            *ppv = static_cast<IDropTarget*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    ULONG STDMETHODCALLTYPE AddRef() override { return InterlockedIncrement(&m_refCount); }
    ULONG STDMETHODCALLTYPE Release() override {
        LONG count = InterlockedDecrement(&m_refCount);
        if (count == 0) delete this;
        return count;
    }

    HRESULT STDMETHODCALLTYPE DragEnter(IDataObject* pDataObj, DWORD, POINTL pt, DWORD* pdwEffect) override {
        FORMATETC fmt = { CF_HDROP, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
        m_hasHDrop = (pDataObj && pDataObj->QueryGetData(&fmt) == S_OK);
        UpdateHoverState(pt, pdwEffect);
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE DragOver(DWORD, POINTL pt, DWORD* pdwEffect) override {
        UpdateHoverState(pt, pdwEffect);
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE DragLeave() override {
        m_hasHDrop = false;
        g_hovered = false;
        g_targetScale = 1.0f;
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE Drop(IDataObject* pDataObj, DWORD, POINTL pt, DWORD* pdwEffect) override {
        bool canMove = pdwEffect && (*pdwEffect & DROPEFFECT_MOVE);
        if (m_hasHDrop && canMove && IsOverTrash(pt)) {
            *pdwEffect = DROPEFFECT_MOVE;

            FORMATETC fmt = { CF_HDROP, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
            STGMEDIUM stg;
            if (SUCCEEDED(pDataObj->GetData(&fmt, &stg))) {
                HDROP hDrop = (HDROP)GlobalLock(stg.hGlobal);
                if (hDrop) {
                    UINT fileCount = DragQueryFileW(hDrop, 0xFFFFFFFF, nullptr, 0);
                    if (fileCount > 0) {
                        std::vector<wchar_t> buffer;
                        for (UINT i = 0; i < fileCount; i++) {
                            UINT len = DragQueryFileW(hDrop, i, nullptr, 0);
                            size_t prevSize = buffer.size();
                            buffer.resize(prevSize + len + 1);
                            DragQueryFileW(hDrop, i, buffer.data() + prevSize, len + 1);
                        }
                        buffer.push_back(L'\0');

                        EnterCriticalSection(&g_deleteCs);
                        g_deleteQueue.push_back(std::move(buffer));
                        LeaveCriticalSection(&g_deleteCs);
                        SetEvent(g_hDeleteQueueEvent);
                    }
                    GlobalUnlock(stg.hGlobal);
                }
                ReleaseStgMedium(&stg);
            }

            g_currentScale = 1.25f;
            g_targetScale = 0.0f;
            g_hovered = false;
            g_animState = AnimState::DROPPED;
        } else {
            if (pdwEffect) *pdwEffect = DROPEFFECT_NONE;
        }
        m_hasHDrop = false;
        return S_OK;
    }
};

static CRecycleDropTarget* g_pDropTarget = nullptr;

void MoveFilesToRecycleBin(const std::vector<wchar_t>& buffer) {
    if (buffer.empty()) return;

    SHFILEOPSTRUCTW fileOp = {};
    fileOp.wFunc = FO_DELETE;
    fileOp.pFrom = buffer.data();
    fileOp.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_WANTNUKEWARNING | FOF_SILENT;
    SHFileOperationW(&fileOp);
}

DWORD WINAPI DeleteWorkerThread(LPVOID) {
    HANDLE handles[2] = { g_hDeleteStopEvent, g_hDeleteQueueEvent };
    while (true) {
        DWORD wait = WaitForMultipleObjects(2, handles, FALSE, INFINITE);
        if (wait == WAIT_OBJECT_0) {
            EnterCriticalSection(&g_deleteCs);
            auto queueCopy = std::move(g_deleteQueue);
            LeaveCriticalSection(&g_deleteCs);

            for (const auto& item : queueCopy) {
                MoveFilesToRecycleBin(item);
            }
            break;
        } else if (wait == WAIT_OBJECT_0 + 1) {
            while (true) {
                std::vector<wchar_t> item;
                EnterCriticalSection(&g_deleteCs);
                if (!g_deleteQueue.empty()) {
                    item = std::move(g_deleteQueue.front());
                    g_deleteQueue.erase(g_deleteQueue.begin());
                }
                LeaveCriticalSection(&g_deleteCs);

                if (item.empty()) break;
                MoveFilesToRecycleBin(item);
            }
        } else {
            break;
        }
    }
    return 0;
}

LRESULT CALLBACK OverlayWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_UPDATE_DRAG_STATE: {
            if (wParam != 0) {
                POINT ptCursor;
                GetCursorPos(&ptCursor);
                HMONITOR hMon = MonitorFromPoint(ptCursor, MONITOR_DEFAULTTONEAREST);
                MONITORINFO mi = { sizeof(mi) };
                if (GetMonitorInfoW(hMon, &mi)) {
                    g_targetWorkArea = mi.rcWork;
                } else {
                    g_targetWorkArea = { 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
                }

                g_currentDpiScale = (float)GetMonitorDpi(hMon) / 96.0f;
                g_animState = AnimState::VISIBLE;
                g_currentScale = 0.3f;
                g_targetScale = 1.0f;
                g_hovered = false;
                g_lastRenderedScale = -1.0f;
                ShowWindow(hWnd, SW_SHOWNOACTIVATE);
                SetTimer(hWnd, TIMER_ANIM, 16, nullptr);
            } else {
                if (g_animState != AnimState::DROPPED) {
                    g_targetScale = 0.0f;
                }
            }
            return 0;
        }

        case WM_TIMER: {
            if (wParam == TIMER_ANIM) {
                float lerp = 0.05f + 0.04f * (float)g_settings.animationSpeed;
                if (abs((int)((g_targetScale - g_currentScale) * 1000.0f)) < 5) {
                    g_currentScale = g_targetScale;
                } else {
                    g_currentScale += (g_targetScale - g_currentScale) * lerp;
                }

                if (g_targetScale == 0.0f && g_currentScale < 0.05f) {
                    g_animState = AnimState::HIDDEN;
                    g_hovered = false;
                    KillTimer(hWnd, TIMER_ANIM);
                    ShowWindow(hWnd, SW_HIDE);
                    return 0;
                }

                if (g_currentScale != g_lastRenderedScale) {
                    g_lastRenderedScale = g_currentScale;
                    RenderFrame(hWnd);
                }
            }
            return 0;
        }

        case WM_DESTROY: {
            KillTimer(hWnd, TIMER_ANIM);
            RevokeDragDrop(hWnd);
            return 0;
        }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

DWORD WINAPI OverlayUIThread(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    SetEvent(g_readyEvent);

    OleInitialize(nullptr);
    GdiplusStartupInput gdiplusInput;
    GdiplusStartup(&g_gdiplusToken, &gdiplusInput, nullptr);

    HINSTANCE hInstance = GetCurrentModuleHandle();
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = OverlayWndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = kClassName;

    if (!RegisterClassExW(&wc)) {
        Wh_Log(L"Failed to register overlay window class (error: %lu)", GetLastError());
        GdiplusShutdown(g_gdiplusToken);
        OleUninitialize();
        return 0;
    }

    HMONITOR hPrimary = MonitorFromPoint({ 0, 0 }, MONITOR_DEFAULTTOPRIMARY);
    g_currentDpiScale = (float)GetMonitorDpi(hPrimary) / 96.0f;

    TargetGeometry geo = ComputeGeometry();

    g_hOverlayWnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
        kClassName, nullptr, WS_POPUP,
        geo.wndLeft, geo.wndTop,
        geo.wndWidth, geo.wndHeight,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!g_hOverlayWnd) {
        Wh_Log(L"Failed to create overlay window (error: %lu)", GetLastError());
        UnregisterClassW(kClassName, hInstance);
        GdiplusShutdown(g_gdiplusToken);
        OleUninitialize();
        return 0;
    }

    g_pDropTarget = new CRecycleDropTarget();
    HRESULT hrDrop = RegisterDragDrop(g_hOverlayWnd, g_pDropTarget);
    if (FAILED(hrDrop)) {
        Wh_Log(L"RegisterDragDrop failed with HRESULT 0x%08X", hrDrop);
    }

    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    if (g_hOverlayWnd) {
        DestroyWindow(g_hOverlayWnd); // WM_DESTROY revokes the drop target
        g_hOverlayWnd = nullptr;
    }

    UnregisterClassW(kClassName, hInstance);

    if (g_pDropTarget) {
        g_pDropTarget->Release();
        g_pDropTarget = nullptr;
    }

    GdiplusShutdown(g_gdiplusToken);
    OleUninitialize();
    return 0;
}

using DoDragDrop_t = decltype(&DoDragDrop);
static DoDragDrop_t pOriginalDoDragDrop = nullptr;

HRESULT WINAPI Hooked_DoDragDrop(IDataObject* pDataObj, IDropSource* pDropSource, DWORD dwOKEffects, LPDWORD pdwEffect) {
    bool bIsFileDrag = false;
    if (pDataObj) {
        FORMATETC fmt = { CF_HDROP, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
        bIsFileDrag = (pDataObj->QueryGetData(&fmt) == S_OK);
    }

    if (bIsFileDrag && InterlockedIncrement(&g_activeDrags) == 1 && g_hOverlayWnd) {
        PostMessageW(g_hOverlayWnd, WM_UPDATE_DRAG_STATE, 1, 0);
    }

    HRESULT hr = pOriginalDoDragDrop(pDataObj, pDropSource, dwOKEffects, pdwEffect);

    if (bIsFileDrag && InterlockedDecrement(&g_activeDrags) == 0 && g_hOverlayWnd) {
        PostMessageW(g_hOverlayWnd, WM_UPDATE_DRAG_STATE, 0, 0);
    }

    return hr;
}

void Wh_ModUninit();

BOOL Wh_ModInit() {
    LoadSettings();

    InitializeCriticalSection(&g_deleteCs);
    g_hDeleteQueueEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    g_hDeleteStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_hDeleteQueueEvent || !g_hDeleteStopEvent) {
        Wh_Log(L"Failed to create deletion worker events");
        Wh_ModUninit();
        return FALSE;
    }

    g_hDeleteWorker = CreateThread(nullptr, 0, DeleteWorkerThread, nullptr, 0, nullptr);
    if (!g_hDeleteWorker) {
        Wh_Log(L"Failed to create deletion worker thread (error: %lu)", GetLastError());
        Wh_ModUninit();
        return FALSE;
    }

    g_readyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_readyEvent) {
        Wh_Log(L"Failed to create ready event (error: %lu)", GetLastError());
        Wh_ModUninit();
        return FALSE;
    }

    g_hUIThread = CreateThread(nullptr, 0, OverlayUIThread, nullptr, 0, &g_dwUIThreadId);
    if (!g_hUIThread) {
        Wh_Log(L"Failed to create overlay UI thread (error: %lu)", GetLastError());
        Wh_ModUninit();
        return FALSE;
    }

    if (!WindhawkUtils::SetFunctionHook(DoDragDrop, Hooked_DoDragDrop, &pOriginalDoDragDrop)) {
        Wh_Log(L"Failed to hook DoDragDrop");
        Wh_ModUninit();
        return FALSE;
    }

    return TRUE;
}

void Wh_ModSettingsChanged() {
    LoadSettings();
}

void Wh_ModUninit() {
    if (g_hUIThread) {
        if (g_readyEvent) WaitForSingleObject(g_readyEvent, INFINITE);
        PostThreadMessageW(g_dwUIThreadId, WM_QUIT, 0, 0);
        WaitForSingleObject(g_hUIThread, INFINITE);
        CloseHandle(g_hUIThread);
        g_hUIThread = nullptr;
    }
    if (g_readyEvent) {
        CloseHandle(g_readyEvent);
        g_readyEvent = nullptr;
    }

    if (g_hDeleteWorker) {
        if (g_hDeleteStopEvent) SetEvent(g_hDeleteStopEvent);
        WaitForSingleObject(g_hDeleteWorker, INFINITE);
        CloseHandle(g_hDeleteWorker);
        g_hDeleteWorker = nullptr;
    }
    if (g_hDeleteStopEvent) {
        CloseHandle(g_hDeleteStopEvent);
        g_hDeleteStopEvent = nullptr;
    }
    if (g_hDeleteQueueEvent) {
        CloseHandle(g_hDeleteQueueEvent);
        g_hDeleteQueueEvent = nullptr;
    }
    DeleteCriticalSection(&g_deleteCs);
}
