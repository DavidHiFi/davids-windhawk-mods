// ==WindhawkMod==
// @id              ditto-styler
// @name            Ditto Styler
// @description     Glass tooltips, a rounded bottom dock and a soft fade for the Ditto clipboard window
// @version         1.1.10
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         Ditto.exe
// @compilerOptions -ldwmapi -luser32 -lgdi32 -lgdiplus -luxtheme -lcomctl32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Ditto Styler

Ditto's clip tooltips are plain grey boxes and its bottom row is three loose
controls. This mod gives the tooltips a dark glass look, turns the bottom row
into one rounded dock, and fades the window in and out instead of snapping.

## Features
- **Glass window.** A blurred glass backdrop behind Ditto's see-through window,
  16 px rounded corners and a thin blue to mauve ring.
- **Easier to read.** Bigger row numbers, a darker side strip, and smooth
  mouse wheel scrolling through the clip list.
- **Glass tooltips.** Rounded, blurred, a thin blue ring, FiraCode text.
- **Bottom dock.** The folder button, search box and menu button sit in one
  rounded dock. Buttons light up on hover with a soft fill and a blue ring;
  pressing shows a mauve ring. The search field floats inside the shared dock,
  whose hover ring blends blue into mauve.
- **Soft open and close.** The window fades in and out over a short moment.
- **Reversible.** Turn the mod off and Ditto looks the way it did.

## Notes
- Made for the Catppuccin Mocha theme in Ditto (Options, Theme).
- Respects the Windows "Animation effects" setting.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- tooltips: true
  $name: Glass tooltips
  $description: When on, clip tooltips get the rounded glass look. When off, Ditto's own tooltip shows.
- tooltipFontSize: 9
  $name: Tooltip text size
  $description: 8 to 12 points (Suggested: 9).
- tooltipTint: 88
  $name: Tooltip glass strength
  $description: 85 to 100 percent. Higher hides more of what is behind (Suggested: 88).
- glass: true
  $name: Glass window
  $description: When on, the Ditto window gets a blurred glass backdrop instead of plain see-through.
- dock: true
  $name: Bottom dock
  $description: When on, the folder button, search box and menu button sit in one rounded dock with hover rings.
- animate: true
  $name: Fade on open and close
  $description: When on, the window fades in and out.
- animMs: 150
  $name: Fade length
  $description: 120 to 200 milliseconds (Suggested: 150).
- accent: "#89B4FA"
  $name: Accent color
  $description: Ring color for hover, focus and tooltips (Suggested: #89B4FA).
*/
// ==/WindhawkModSettings==

#include <windhawk_utils.h>
#include <windows.h>
#include <commctrl.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <gdiplus.h>
#include <math.h>
#include <mutex>
#include <set>
#include <unordered_map>
#include <string>

// Catppuccin Mocha
static const COLORREF kBase = RGB(30, 30, 46);
static const COLORREF kMantle = RGB(24, 24, 37);
static const COLORREF kCrust = RGB(17, 17, 27);
static const COLORREF kSurface0 = RGB(49, 50, 68);
static const COLORREF kSurface1 = RGB(69, 71, 90);
static const COLORREF kSurface2 = RGB(88, 91, 112);
static const COLORREF kOverlay1 = RGB(127, 132, 156);
static const COLORREF kText = RGB(205, 214, 244);
static const COLORREF kMauve = RGB(203, 166, 247);
static const COLORREF kBlueAccent = RGB(137, 180, 250);

struct Config {
    bool tooltips, dock, animate, glass;
    int tooltipFontSize, tooltipTint, animMs;
    COLORREF accent;
} g_cfg;

static ULONG_PTR g_gdiplusToken;
static std::mutex g_lock;
static std::set<HWND> g_subclassed;

// ---------- helpers ----------

static int Clamp(int v, int lo, int hi) { return v < lo ? lo : v > hi ? hi : v; }

static int HexDigit(wchar_t c) {
    if (c >= L'0' && c <= L'9') return c - L'0';
    if (c >= L'a' && c <= L'f') return c - L'a' + 10;
    if (c >= L'A' && c <= L'F') return c - L'A' + 10;
    return -1;
}

static COLORREF ParseColor(PCWSTR s, COLORREF def) {
    if (!s) return def;
    if (*s == L'#') ++s;
    int v[3];
    for (int i = 0; i < 3; ++i) {
        int hi = HexDigit(s[0]), lo = hi >= 0 ? HexDigit(s[1]) : -1;
        if (hi < 0 || lo < 0) return def;
        v[i] = hi * 16 + lo;
        s += 2;
    }
    return RGB(v[0], v[1], v[2]);
}

static void LoadConfig() {
    g_cfg.tooltips = Wh_GetIntSetting(L"tooltips") != 0;
    g_cfg.dock = Wh_GetIntSetting(L"dock") != 0;
    g_cfg.glass = Wh_GetIntSetting(L"glass") != 0;
    g_cfg.animate = Wh_GetIntSetting(L"animate") != 0;
    g_cfg.tooltipFontSize = Clamp(Wh_GetIntSetting(L"tooltipFontSize"), 8, 12);
    g_cfg.tooltipTint = Clamp(Wh_GetIntSetting(L"tooltipTint"), 85, 100);
    g_cfg.animMs = Clamp(Wh_GetIntSetting(L"animMs"), 120, 200);
    PCWSTR a = Wh_GetStringSetting(L"accent");
    g_cfg.accent = ParseColor(a, RGB(137, 180, 250));
    Wh_FreeStringSetting(a);
}

static bool ClassIs(HWND h, PCWSTR name) {
    wchar_t cls[64];
    return GetClassNameW(h, cls, 64) && _wcsicmp(cls, name) == 0;
}

static bool IsQPaste(HWND h) { return h && ClassIs(h, L"QPasteClass"); }

static int Scale(HWND h, int v) { return MulDiv(v, GetDpiForWindow(h), 96); }

static COLORREF Lerp(COLORREF a, COLORREF b, double t) {
    return RGB((int)(GetRValue(a) + (GetRValue(b) - GetRValue(a)) * t),
               (int)(GetGValue(a) + (GetGValue(b) - GetGValue(a)) * t),
               (int)(GetBValue(a) + (GetBValue(b) - GetBValue(a)) * t));
}

static Gdiplus::Color GpColor(COLORREF c, double alpha = 1.0) {
    return Gdiplus::Color((BYTE)(alpha * 255), GetRValue(c), GetGValue(c), GetBValue(c));
}

static void AddRoundRect(Gdiplus::GraphicsPath& p, Gdiplus::RectF r, float rad) {
    float d = rad * 2;
    if (d > r.Height) d = r.Height;
    if (d > r.Width) d = r.Width;
    p.AddArc(r.X, r.Y, d, d, 180, 90);
    p.AddArc(r.X + r.Width - d, r.Y, d, d, 270, 90);
    p.AddArc(r.X + r.Width - d, r.Y + r.Height - d, d, d, 0, 90);
    p.AddArc(r.X, r.Y + r.Height - d, d, d, 90, 90);
    p.CloseFigure();
}

static void DrawRing(HDC dc, RECT rc, float radius, COLORREF c, double alpha, float width) {
    Gdiplus::Graphics g(dc);
    g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
    g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
    Gdiplus::GraphicsPath path;
    float h = width / 2;
    AddRoundRect(path, Gdiplus::RectF(rc.left + h, rc.top + h, rc.right - rc.left - width,
                                      rc.bottom - rc.top - width), radius);
    Gdiplus::Pen pen(GpColor(c, alpha), width);
    g.DrawPath(&pen, &path);
}

// ---------- accent (acrylic) ----------

struct ACCENT_POLICY { int AccentState; int AccentFlags; UINT GradientColor; int AnimationId; };
struct WINCOMPATTRDATA { int Attrib; PVOID pvData; SIZE_T cbData; };
typedef BOOL(WINAPI* PFN_SWCA)(HWND, WINCOMPATTRDATA*);

static void SetAccent(HWND h, bool on, COLORREF tint, int pct) {
    static PFN_SWCA fn = (PFN_SWCA)GetProcAddress(GetModuleHandleW(L"user32.dll"),
                                                  "SetWindowCompositionAttribute");
    if (!fn) return;
    ACCENT_POLICY ap = {};
    ap.AccentState = on ? 4 : 0;  // ACCENT_ENABLE_ACRYLICBLURBEHIND
    BYTE a = (BYTE)(255 * pct / 100);
    ap.GradientColor = ((UINT)a << 24) | ((UINT)GetBValue(tint) << 16) |
                       ((UINT)GetGValue(tint) << 8) | GetRValue(tint);
    WINCOMPATTRDATA d = {19, &ap, sizeof(ap)};
    fn(h, &d);
}

// ---------- tooltips ----------

struct TipState {
    HFONT font = nullptr;
    HFONT originalFont = nullptr;
    LONG originalStyle = 0;
    COLORREF originalBackground = 0, originalText = 0;
    int width = 0, height = 0;
};
static std::unordered_map<HWND, TipState> g_tips;

// ---------- seamless border: a click-through layered overlay ----------
// A window region clips with hard pixel steps. The overlay draws the anti-aliased
// gradient ring on top of the region edge, so the corners read smooth.
static std::unordered_map<HWND, HWND> g_rings;
static std::unordered_map<HWND, SIZE> g_ringSize;

static void UpdateRing(HWND t) {
    HWND ov = nullptr;
    {
        std::lock_guard<std::mutex> lk(g_lock);
        auto it = g_rings.find(t);
        if (it != g_rings.end()) ov = it->second;
    }
    if (ov && !IsWindow(ov)) ov = nullptr;
    if (!IsWindowVisible(t) || IsIconic(t)) {
        if (ov) ShowWindow(ov, SW_HIDE);
        return;
    }
    RECT wr;
    GetWindowRect(t, &wr);
    int W = wr.right - wr.left, H = wr.bottom - wr.top;
    if (W < 8 || H < 8) return;
    bool topmost = (GetWindowLongW(t, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0;
    if (!ov) {
        // "Static" keeps the window procedure in user32, so unloading the mod is safe.
        ov = CreateWindowExW(WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW |
                                 (topmost ? WS_EX_TOPMOST : 0),
                             L"Static", L"", WS_POPUP, wr.left, wr.top, W, H, t, nullptr,
                             GetModuleHandleW(nullptr), nullptr);
        if (!ov) return;
        std::lock_guard<std::mutex> lk(g_lock);
        g_rings[t] = ov;
    }
    float rad = (float)Scale(t, 16);
    SIZE& last = g_ringSize[t];
    RECT box = {};
    int kind = GetWindowRgnBox(t, &box);
    bool ours = kind != ERROR && kind != NULLREGION && box.left == 1 && box.top == 1 &&
                box.right == W - 1 && box.bottom == H - 1;
    if (last.cx != W || last.cy != H || !ours) {
        last = {W, H};
        // Region sits 1 px inside the ring's outer edge, so every clip step is under the ring.
        int d = 2 * (Scale(t, 16) - 1);
        SetWindowRgn(t, CreateRoundRectRgn(1, 1, W, H, d, d), TRUE);
        // The blur takes its shape when the accent is set, so set it again over the new region.
        if (IsQPaste(t) || ClassIs(t, TOOLTIPS_CLASSW)) {
            COLORREF tint = IsQPaste(t) ? kCrust : kBase;
            int strength = IsQPaste(t) ? 35 : g_cfg.tooltipTint;
            SetAccent(t, false, tint, strength);
            SetAccent(t, true, tint, strength);
        }
    }
    BITMAPINFO bi = {};
    bi.bmiHeader = {sizeof(BITMAPINFOHEADER), W, -H, 1, 32, BI_RGB};
    void* bits = nullptr;
    HDC screen = GetDC(nullptr);
    HDC mem = CreateCompatibleDC(screen);
    HBITMAP bmp = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (bmp && bits) {
        HGDIOBJ old = SelectObject(mem, bmp);
        {
            Gdiplus::Bitmap canvas(W, H, W * 4, PixelFormat32bppPARGB, (BYTE*)bits);
            Gdiplus::Graphics g(&canvas);
            g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
            g.Clear(Gdiplus::Color(0, 0, 0, 0));
            float bw = (float)(Scale(t, 2) < 2 ? 2 : Scale(t, 2));
            Gdiplus::GraphicsPath path;
            AddRoundRect(path, Gdiplus::RectF(bw / 2, bw / 2, W - bw, H - bw), rad - bw / 2);
            Gdiplus::LinearGradientBrush grad(Gdiplus::PointF(0, 0), Gdiplus::PointF((float)W, (float)H),
                                              GpColor(kBlueAccent), GpColor(kMauve));
            Gdiplus::Pen pen(&grad, bw);
            g.DrawPath(&pen, &path);
            g.Flush(Gdiplus::FlushIntentionSync);
        }
        POINT dst = {wr.left, wr.top}, src = {0, 0};
        SIZE sz = {W, H};
        BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
        UpdateLayeredWindow(ov, screen, &dst, &sz, mem, &src, 0, &bf, ULW_ALPHA);
        SelectObject(mem, old);
    }
    if (bmp) DeleteObject(bmp);
    DeleteDC(mem);
    ReleaseDC(nullptr, screen);
    // Directly above its owner, never above other apps.
    HWND above = GetWindow(t, GW_HWNDPREV);
    if (above == ov) above = GetWindow(ov, GW_HWNDPREV);
    SetWindowPos(ov, above ? above : (topmost ? HWND_TOPMOST : HWND_TOP), 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

static void ForgetRing(HWND t) {
    std::lock_guard<std::mutex> lk(g_lock);
    g_rings.erase(t);
    g_ringSize.erase(t);
}

static void RemoveRing(HWND t) {
    HWND ov = nullptr;
    {
        std::lock_guard<std::mutex> lk(g_lock);
        auto it = g_rings.find(t);
        if (it != g_rings.end()) { ov = it->second; g_rings.erase(it); }
        g_ringSize.erase(t);
    }
    if (ov) PostMessageW(ov, WM_CLOSE, 0, 0);
    SetWindowRgn(t, nullptr, TRUE);
}

static void TipApplyLook(HWND h) {
    TipState& st = g_tips[h];
    if (!st.font) {
        st.originalStyle = GetWindowLongW(h, GWL_STYLE);
        st.originalFont = (HFONT)SendMessageW(h, WM_GETFONT, 0, 0);
        st.originalBackground = (COLORREF)SendMessageW(h, TTM_GETTIPBKCOLOR, 0, 0);
        st.originalText = (COLORREF)SendMessageW(h, TTM_GETTIPTEXTCOLOR, 0, 0);
    }
    SetWindowTheme(h, L"", L"");
    LONG ex = GetWindowLongW(h, GWL_EXSTYLE);
    if (ex & WS_EX_LAYERED) SetWindowLongW(h, GWL_EXSTYLE, ex & ~WS_EX_LAYERED);
    SetWindowLongW(h, GWL_STYLE, (GetWindowLongW(h, GWL_STYLE) & ~WS_BORDER) | TTS_NOFADE | TTS_NOANIMATE);

    // Paint black on white so the WM_PRINTCLIENT result is a coverage mask.
    DefSubclassProc(h, TTM_SETTIPBKCOLOR, RGB(0, 0, 0), 0);
    DefSubclassProc(h, TTM_SETTIPTEXTCOLOR, RGB(255, 255, 255), 0);
    int px = Scale(h, 10), py = Scale(h, 7);
    RECT m = {px, py, px, py};
    SendMessageW(h, TTM_SETMARGIN, 0, (LPARAM)&m);

    if (!st.font) {
        LOGFONTW lf = {};
        lf.lfHeight = -MulDiv(g_cfg.tooltipFontSize, GetDpiForWindow(h), 72);
        lf.lfWeight = FW_NORMAL;
        lf.lfQuality = ANTIALIASED_QUALITY;  // grayscale, so the mask stays neutral
        wcscpy_s(lf.lfFaceName, L"FiraCode Nerd Font");
        st.font = CreateFontIndirectW(&lf);
    }
    DefSubclassProc(h, WM_SETFONT, (WPARAM)st.font, FALSE);

    DWORD corner = 1;  // DWMWCP_DONOTROUND: the 16 px region and overlay ring round it
    DwmSetWindowAttribute(h, 33, &corner, sizeof(corner));
    COLORREF border = 0xFFFFFFFE;  // DWMWA_COLOR_NONE
    DwmSetWindowAttribute(h, 34, &border, sizeof(border));
    MARGINS mg = {-1, -1, -1, -1};
    DwmExtendFrameIntoClientArea(h, &mg);
    SetAccent(h, true, kBase, g_cfg.tooltipTint);
}

static void TipPaint(HWND h) {
    PAINTSTRUCT ps;
    HDC dc = BeginPaint(h, &ps);
    RECT rc;
    GetClientRect(h, &rc);
    int w = rc.right, ht = rc.bottom;
    if (w > 0 && ht > 0) {
        BITMAPINFO bi = {};
        bi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -ht, 1, 32, BI_RGB};
        void* bits = nullptr;
        HDC mem = CreateCompatibleDC(dc);
        HBITMAP bmp = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
        HGDIOBJ old = SelectObject(mem, bmp);
        DefSubclassProc(h, WM_PRINTCLIENT, (WPARAM)mem, PRF_CLIENT | PRF_ERASEBKGND);
        GdiFlush();
        DWORD* p = (DWORD*)bits;
        std::string cov(w * ht, '\0');
        for (int i = 0; i < w * ht; ++i) {
            DWORD c = p[i];
            BYTE r = (c >> 16) & 0xFF, g = (c >> 8) & 0xFF, b = c & 0xFF;
            cov[i] = (char)(r > g ? (r > b ? r : b) : (g > b ? g : b));
            p[i] = 0;
        }
        // Tinted glass body plus a blue-to-mauve ring, both on the DWM corner radius.
        {
            Gdiplus::Bitmap canvas(w, ht, w * 4, PixelFormat32bppPARGB, (BYTE*)bits);
            Gdiplus::Graphics g(&canvas);
            g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
            float rad = (float)Scale(h, 16);
            Gdiplus::GraphicsPath body;
            AddRoundRect(body, Gdiplus::RectF(0, 0, (float)w, (float)ht), rad);
            Gdiplus::SolidBrush fill(GpColor(kBase, g_cfg.tooltipTint / 100.0));
            g.FillPath(&fill, &body);
            g.Flush(Gdiplus::FlushIntentionSync);
        }
        BYTE tr = GetRValue(kText), tg = GetGValue(kText), tb = GetBValue(kText);
        for (int i = 0; i < w * ht; ++i) {
            int a = (BYTE)cov[i];
            int x=i%w, y=i/w;
            int radius=Scale(h,16);
            int dx=x<radius ? radius-x : (x>=w-radius ? x-(w-radius-1) : 0);
            int dy=y<radius ? radius-y : (y>=ht-radius ? y-(ht-radius-1) : 0);
            if (dx && dy && dx*dx+dy*dy>=radius*radius) { p[i]=0; continue; }
            if (x<2 || y<2 || x>=w-2 || y>=ht-2) a=0;
            if (!a) continue;
            DWORD c = p[i];
            int inv = 255 - a;
            int A = a + ((c >> 24) & 0xFF) * inv / 255;
            int R = tr * a / 255 + ((c >> 16) & 0xFF) * inv / 255;
            int G = tg * a / 255 + ((c >> 8) & 0xFF) * inv / 255;
            int B = tb * a / 255 + (c & 0xFF) * inv / 255;
            p[i] = ((DWORD)A << 24) | ((DWORD)R << 16) | ((DWORD)G << 8) | (DWORD)B;
        }
        BitBlt(dc, 0, 0, w, ht, mem, 0, 0, SRCCOPY);
        SelectObject(mem, old);
        DeleteObject(bmp);
        DeleteDC(mem);
    }
    EndPaint(h, &ps);
}

static LRESULT CALLBACK TipProc(HWND h, UINT msg, WPARAM wp, LPARAM lp, DWORD_PTR) {
    switch (msg) {
        case WM_NULL:
            if (wp == 0xD177 && lp == 0xD177) { if (g_cfg.tooltips) TipApplyLook(h); return 0; }
            break;
        case WM_PAINT:
            if (g_cfg.tooltips) { TipPaint(h); return 0; }
            break;
        case WM_WINDOWPOSCHANGED:
            if (g_cfg.tooltips) {
                LRESULT r = DefSubclassProc(h, msg, wp, lp);
                UpdateRing(h);
                return r;
            }
            break;
        case WM_ERASEBKGND:
            if (g_cfg.tooltips) return 1;
            break;
        case WM_SETFONT: {
            auto it = g_tips.find(h);
            if (g_cfg.tooltips && it != g_tips.end() && it->second.font)
                return DefSubclassProc(h, msg, (WPARAM)it->second.font, lp);
            break;
        }
        case TTM_SETTIPBKCOLOR:
        case TTM_SETTIPTEXTCOLOR:
            if (g_cfg.tooltips) return 0;  // keep the mask colors
            break;
        case WM_NCDESTROY: {
            std::lock_guard<std::mutex> lk(g_lock);
            auto it = g_tips.find(h);
            if (it != g_tips.end()) { if (it->second.font) DeleteObject(it->second.font); g_tips.erase(it); }
            g_rings.erase(h);
            g_ringSize.erase(h);
            g_subclassed.erase(h);
            break;
        }
    }
    return DefSubclassProc(h, msg, wp, lp);
}

static void Attach(HWND h);
static BOOL CALLBACK AttachChild(HWND c, LPARAM);

// ---------- dock: parent, search box, buttons ----------

static RECT DockRect(HWND parent) {
    RECT rc;
    GetClientRect(parent, &rc);
    // Ditto keeps the clip list above cy-30; the dock lives only in that strip.
    int inset = Scale(parent, 6);
    return {inset, rc.bottom - Scale(parent, 30), rc.right - inset, rc.bottom - Scale(parent, 4)};
}

static RECT SearchPill(HWND parent) {
    RECT d = DockRect(parent);
    int pad = Scale(parent, 3), side = Scale(parent, 4), button = Scale(parent, 20), gap = Scale(parent, 4);
    return {d.left + side + button + gap, d.top + pad, d.right - side - button - gap, d.bottom - pad};
}

static void PlaceControl(HWND parent, int id, RECT target) {
    HWND child = GetDlgItem(parent, id);
    if (!child) return;
    RECT actual;
    GetWindowRect(child, &actual);
    MapWindowPoints(nullptr, parent, (POINT*)&actual, 2);
    if (!EqualRect(&actual, &target))
        SetWindowPos(child, nullptr, target.left, target.top,
            target.right-target.left, target.bottom-target.top,
            SWP_NOZORDER | SWP_NOACTIVATE);
}

static void LayoutDock(HWND h) {
    static thread_local bool busy = false;
    if (busy) return;
    busy = true;
    RECT d = DockRect(h);
    int pad = Scale(h, 4), button = Scale(h, 20);
    int mid = (d.top + d.bottom) / 2;
    PlaceControl(h, 517, {d.left+pad, mid-button/2, d.left+pad+button, mid-button/2+button});
    PlaceControl(h, 528, {d.right-pad-button, mid-button/2, d.right-pad, mid-button/2+button});
    // The edit sits inside the pill the parent paints, so no square edge shows.
    RECT pill = SearchPill(h);
    PlaceControl(h, 514, {pill.left+Scale(h,8), pill.top+Scale(h,2), pill.right-Scale(h,6), pill.bottom-Scale(h,2)});
    HWND edit = GetDlgItem(h, 514);
    if (edit) {
        LPARAM margins=MAKELPARAM(Scale(h,2),Scale(h,30));
        if (SendMessageW(edit,EM_GETMARGINS,0,0) != margins)
            SendMessageW(edit, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, margins);
    }
    // The clip list is left alone: resizing it breaks Ditto's own scrolling.
    busy = false;
}

static bool InDock(HWND child) {
    HWND p = GetParent(child);
    if (!IsQPaste(p)) return false;
    RECT rc, pr;
    GetWindowRect(child, &rc);
    MapWindowPoints(nullptr, p, (POINT*)&rc, 2);
    GetClientRect(p, &pr);
    return rc.top >= pr.bottom - Scale(p, 32);
}

static const BYTE kDarkA = 0xC8;

static bool InRound(int x, int y, const RECT& s, int rad) {
    float fx = x + 0.5f, fy = y + 0.5f;
    if (fx < s.left || fx > s.right || fy < s.top || fy > s.bottom) return false;
    float dx = fx < s.left + rad ? s.left + rad - fx : (fx > s.right - rad ? fx - (s.right - rad) : 0);
    float dy = fy < s.top + rad ? s.top + rad - fy : (fy > s.bottom - rad ? fy - (s.bottom - rad) : 0);
    return dx * dx + dy * dy <= (float)rad * rad;
}

static void DarkenBits(DWORD* p, int w, int ht, int ox, int oy, COLORREF tint, BYTE a,
                       const RECT* shape, int rad) {
    // Premultiplied: a pixel shows max(own colour, tint) at opacity a over the blur.
    auto mix = [a](int ch, int t) { return (ch > t ? ch : t) * a / 255; };
    int tr = GetRValue(tint), tg = GetGValue(tint), tb = GetBValue(tint);
    for (int y = 0; y < ht; ++y)
        for (int x = 0; x < w; ++x) {
            DWORD c = p[y * w + x];
            if (c >> 24) continue;  // already opaque or already darkened
            if (shape && !InRound(ox + x, oy + y, *shape, rad)) continue;
            p[y * w + x] = ((DWORD)a << 24) | ((DWORD)mix((c >> 16) & 0xFF, tr) << 16) |
                           ((DWORD)mix((c >> 8) & 0xFF, tg) << 8) | (DWORD)mix(c & 0xFF, tb);
        }
}

static void DarkenDC(HDC dc, RECT r, COLORREF tint, BYTE a, const RECT* shape, int rad) {
    int w = r.right - r.left, ht = r.bottom - r.top;
    if (w <= 0 || ht <= 0) return;
    BITMAPINFO bi = {};
    bi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -ht, 1, 32, BI_RGB};
    void* bits = nullptr;
    HDC mem = CreateCompatibleDC(dc);
    HBITMAP bmp = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!bmp || !bits) { if (bmp) DeleteObject(bmp); DeleteDC(mem); return; }
    HGDIOBJ old = SelectObject(mem, bmp);
    BitBlt(mem, 0, 0, w, ht, dc, r.left, r.top, SRCCOPY);
    GdiFlush();
    DarkenBits((DWORD*)bits, w, ht, r.left, r.top, tint, a, shape, rad);
    BitBlt(dc, r.left, r.top, w, ht, mem, 0, 0, SRCCOPY);
    SelectObject(mem, old);
    DeleteObject(bmp);
    DeleteDC(mem);
}

static std::unordered_map<HWND,double> g_dockHover;
static const UINT_PTR kDockTimer=0xD179;
static void PaintDock(HWND parent) {
    RECT d=DockRect(parent),client; GetClientRect(parent,&client);
    RECT strip={0,d.top-1,client.right,client.bottom};
    int width=strip.right, height=strip.bottom-strip.top;
    if(width<1 || height<1) return;
    HDC target=GetDC(parent),mem=CreateCompatibleDC(target);
    BITMAPINFO bi={}; bi.bmiHeader={sizeof(BITMAPINFOHEADER),width,-height,1,32,BI_RGB};
    void* pixels=nullptr;
    HBITMAP bitmap=CreateDIBSection(target,&bi,DIB_RGB_COLORS,&pixels,nullptr,0);
    if(!bitmap || !pixels) { if(bitmap) DeleteObject(bitmap); DeleteDC(mem); ReleaseDC(parent,target); return; }
    HGDIOBJ old=SelectObject(mem,bitmap);
    {
        Gdiplus::Bitmap canvas(width,height,width*4,PixelFormat32bppPARGB,(BYTE*)pixels);
        Gdiplus::Graphics g(&canvas);
        g.Clear(Gdiplus::Color(0,0,0,0));
        g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
        g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
        float border=(float)Scale(parent,2);
        Gdiplus::GraphicsPath path;
        AddRoundRect(path,Gdiplus::RectF(d.left+border/2,d.top-strip.top+border/2,
            d.right-d.left-border,d.bottom-d.top-border),(d.bottom-d.top-border)/2.0f);
        Gdiplus::SolidBrush fill(GpColor(kMantle,kDarkA/255.0));
        g.FillPath(&fill,&path);
        Gdiplus::Pen outline(GpColor(kSurface1,0.9),border);
        g.DrawPath(&outline,&path);
        double alpha=1-pow(1-g_dockHover[parent],3);
        if(alpha>0.001) {
            Gdiplus::LinearGradientBrush gradient(Gdiplus::PointF((float)d.left,0),
                Gdiplus::PointF((float)d.right,0),GpColor(kBlueAccent,alpha),GpColor(kMauve,alpha));
            Gdiplus::Pen hover(&gradient,border);
            g.DrawPath(&hover,&path);
        }
        g.Flush(Gdiplus::FlushIntentionSync);
    }
    for(HWND child=GetWindow(parent,GW_CHILD);child;child=GetWindow(child,GW_HWNDNEXT)) {
        if(!IsWindowVisible(child)) continue;
        RECT r;GetWindowRect(child,&r);MapWindowPoints(nullptr,parent,(POINT*)&r,2);
        ExcludeClipRect(target,r.left,r.top,r.right,r.bottom);
    }
    BitBlt(target,0,strip.top,width,height,mem,0,0,SRCCOPY);
    SelectObject(mem,old);DeleteObject(bitmap);DeleteDC(mem);ReleaseDC(parent,target);
}

static void PaintSearchRing(HWND h) {
    if (InDock(h)) PaintDock(GetParent(h));
}

struct BtnState { double t = 0; bool hover = false; bool pressed = false; DWORD last = 0; };
static std::unordered_map<HWND, BtnState> g_btns;
static const UINT_PTR kBtnTimer = 0xD177;

static void PaintButtonOverlay(HWND h) {
    BtnState st;
    {
        std::lock_guard<std::mutex> lk(g_lock);
        st = g_btns[h];
    }
    if (!InDock(h)) return;
    bool hot = st.t > 0.001 || st.pressed;
    RECT rc;
    GetClientRect(h, &rc);
    int w = rc.right, ht = rc.bottom;
    if (w <= 0 || ht <= 0) return;
    double e = 1 - pow(1 - st.t, 3);  // ease-out
    HDC dc = GetDC(h);
    BITMAPINFO bi = {};
    bi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -ht, 1, 32, BI_RGB};
    void* bits = nullptr;
    HDC mem = CreateCompatibleDC(dc);
    HBITMAP bmp = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    HGDIOBJ old = SelectObject(mem, bmp);
    BitBlt(mem, 0, 0, w, ht, dc, 0, 0, SRCCOPY);
    GdiFlush();
    // Hover: lift the black base to surface0 inside the rounded shape, then darken it all.
    COLORREF fill = Lerp(RGB(0, 0, 0), kSurface0, e);
    int rad = Scale(h, 8);
    DWORD* p = (DWORD*)bits;
    for (int y = 0; hot && y < ht; ++y) {
        for (int x = 0; x < w; ++x) {
            int cx = x < rad ? rad - x : (x >= w - rad ? x - (w - rad - 1) : 0);
            int cy = y < rad ? rad - y : (y >= ht - rad ? y - (ht - rad - 1) : 0);
            if (cx && cy && cx * cx + cy * cy > rad * rad) continue;
            DWORD c = p[y * w + x];
            int r = (c >> 16) & 0xFF, g = (c >> 8) & 0xFF, b = c & 0xFF;
            if (!(c >> 24) && r + g + b <= 9)
                p[y * w + x] = (GetRValue(fill) << 16) | (GetGValue(fill) << 8) | GetBValue(fill);
        }
    }
    PaintDock(GetParent(h));
    GdiFlush();
    DarkenBits(p, w, ht, 0, 0, kMantle, kDarkA, nullptr, 0);
    BitBlt(dc, 0, 0, w, ht, mem, 0, 0, SRCCOPY);
    SelectObject(mem, old);
    DeleteObject(bmp);
    DeleteDC(mem);
    ReleaseDC(h, dc);
}

static LRESULT CALLBACK ButtonProc(HWND h, UINT msg, WPARAM wp, LPARAM lp, DWORD_PTR) {
    if (msg==WM_NULL && wp==0xD177) return 0xD200+(InDock(h)?1:0);
    if (!g_cfg.dock) return DefSubclassProc(h, msg, wp, lp);
    switch (msg) {
        case WM_PAINT:
            if (InDock(h)) {
                PAINTSTRUCT ps;
                HDC dc = BeginPaint(h, &ps);
                RECT rc;
                GetClientRect(h, &rc);
                FillRect(dc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
                HFONT font = CreateFontW(-Scale(h, 16), 0, 0, 0, FW_NORMAL,
                    FALSE, FALSE, FALSE, DEFAULT_CHARSET, 0, 0,
                    ANTIALIASED_QUALITY, 0, L"Segoe Fluent Icons");
                HGDIOBJ old = SelectObject(dc, font);
                SetBkMode(dc, TRANSPARENT);
                SetTextColor(dc, kText);
                DrawTextW(dc, GetDlgCtrlID(h) == 517 ? L"\uE8B7" : L"\uE712",
                    -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                SelectObject(dc, old);
                DeleteObject(font);
                EndPaint(h, &ps);
                PaintButtonOverlay(h);
                return 0;
            }
            break;
        case WM_MOUSEMOVE: {
            bool start = false;
            {
                std::lock_guard<std::mutex> lk(g_lock);
                BtnState& st = g_btns[h];
                if (!st.hover) { st.hover = true; st.last = GetTickCount(); start = true; }
            }
            if (start) {
                TRACKMOUSEEVENT tme = {sizeof(tme), TME_LEAVE, h, 0};
                TrackMouseEvent(&tme);
                SetTimer(h, kBtnTimer, 15, nullptr);
            }
            break;
        }
        case WM_MOUSELEAVE: {
            std::lock_guard<std::mutex> lk(g_lock);
            BtnState& st = g_btns[h];
            st.hover = false; st.pressed = false; st.last = GetTickCount();
            SetTimer(h, kBtnTimer, 15, nullptr);
            break;
        }
        case WM_LBUTTONDOWN: { std::lock_guard<std::mutex> lk(g_lock); g_btns[h].pressed = true; break; }
        case WM_LBUTTONUP: { std::lock_guard<std::mutex> lk(g_lock); g_btns[h].pressed = false; break; }
        case WM_TIMER:
            if (wp == kBtnTimer) {
                bool done;
                {
                    std::lock_guard<std::mutex> lk(g_lock);
                    BtnState& st = g_btns[h];
                    DWORD now = GetTickCount();
                    double step = (now - st.last) / 150.0;
                    st.last = now;
                    st.t += st.hover ? step : -step;
                    if (st.t > 1) st.t = 1;
                    if (st.t < 0) st.t = 0;
                    done = st.hover ? st.t >= 1 : st.t <= 0;
                }
                if (done) KillTimer(h, kBtnTimer);
                InvalidateRect(h, nullptr, FALSE);
                return 0;
            }
            break;
        case WM_NCDESTROY: {
            std::lock_guard<std::mutex> lk(g_lock);
            g_btns.erase(h);
            g_subclassed.erase(h);
            break;
        }
    }
    LRESULT r = DefSubclassProc(h, msg, wp, lp);
    if (msg == WM_PAINT || msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP) {
        if (msg != WM_PAINT) UpdateWindow(h);
        PaintButtonOverlay(h);
    }
    return r;
}

static void PaintSearch(HWND h) {
    if (!InDock(h)) return;
    RECT wr, cr;
    GetWindowRect(h, &wr);
    GetClientRect(h, &cr);
    POINT origin = {};
    ClientToScreen(h, &origin);
    origin.x -= wr.left;
    origin.y -= wr.top;
    OffsetRect(&wr, -wr.left, -wr.top);
    HDC dc = GetWindowDC(h);
    HBRUSH brush = CreateSolidBrush(RGB(0,0,0));
    FillRect(dc, &wr, brush);
    DeleteObject(brush);
    int saved = SaveDC(dc);
    SetViewportOrgEx(dc, origin.x, origin.y, nullptr);
    int len = GetWindowTextLengthW(h);
    HFONT font = (HFONT)SendMessageW(h, WM_GETFONT, 0, 0);
    HGDIOBJ old = SelectObject(dc, font ? font : GetStockObject(DEFAULT_GUI_FONT));
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, kText);
    if (len) {
        std::wstring text(len+1,L'\0');
        GetWindowTextW(h,text.data(),len+1);
        int first=(int)SendMessageW(h,EM_GETFIRSTVISIBLELINE,0,0);
        if(first<0 || first>len) first=0;
        LRESULT pos=SendMessageW(h,EM_POSFROMCHAR,first,0);
        int x=(short)LOWORD(pos), y=(short)HIWORD(pos);
        RECT clip=cr;
        clip.left+=Scale(h,2);
        clip.right-=Scale(h,30);
        ExtTextOutW(dc,x,y,ETO_CLIPPED,&clip,text.c_str()+first,len-first,nullptr);
        DWORD begin=0,end=0;
        SendMessageW(h,EM_GETSEL,(WPARAM)&begin,(LPARAM)&end);
        if(GetFocus()==h && end>begin && end>(DWORD)first) {
            begin=begin<(DWORD)first ? first : begin;
            SIZE a={},b={};
            GetTextExtentPoint32W(dc,text.c_str()+first,begin-first,&a);
            GetTextExtentPoint32W(dc,text.c_str()+begin,end-begin,&b);
            RECT selected={x+a.cx,y,x+a.cx+b.cx,y+b.cy};
            IntersectRect(&selected,&selected,&clip);
            SetBkColor(dc,kSurface1);
            ExtTextOutW(dc,x+a.cx,y,ETO_CLIPPED|ETO_OPAQUE,&selected,
                text.c_str()+begin,end-begin,nullptr);
        }
    }
    if (!len) {
        RECT text = cr;
        text.left += Scale(h, 2);
        text.right -= Scale(h, 30);
        SetTextColor(dc, RGB(166,173,200));
        DrawTextW(dc, L"Search", -1, &text, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
    }
    SelectObject(dc, old);
    HFONT icons = CreateFontW(-Scale(h, 12),0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,
        DEFAULT_CHARSET,0,0,ANTIALIASED_QUALITY,0,L"Segoe Fluent Icons");
    old = SelectObject(dc, icons);
    SetTextColor(dc, RGB(166,173,200));
    if (len || GetFocus() == h) {
        RECT icon = {cr.right-Scale(h,18),0,cr.right,cr.bottom};
        DrawTextW(dc,L"\uE70D",-1,&icon,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
    }
    if (len) {
        RECT icon = {cr.right-Scale(h,34),0,cr.right-Scale(h,18),cr.bottom};
        DrawTextW(dc,L"\uE711",-1,&icon,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
    }
    SelectObject(dc, old);
    DeleteObject(icons);
    RestoreDC(dc, saved);
    DarkenDC(dc, wr, kMantle, kDarkA, nullptr, 0);
    ReleaseDC(h, dc);
    PaintSearchRing(h);
}

static LRESULT CALLBACK SearchProc(HWND h, UINT msg, WPARAM wp, LPARAM lp, DWORD_PTR) {
    if (msg==WM_NULL && wp==0xD177) return 0xD100+(InDock(h)?1:0);
    if (msg == WM_NCDESTROY) {
        std::lock_guard<std::mutex> lk(g_lock);
        g_subclassed.erase(h);
    }
    LRESULT r = DefSubclassProc(h, msg, wp, lp);
    if (g_cfg.dock && (msg == WM_PAINT || msg == WM_NCPAINT || msg == WM_SETFOCUS ||
                       msg == WM_KILLFOCUS || msg == WM_CHAR || msg == WM_KEYUP || msg == WM_SETTEXT))
        PaintSearch(h);
    return r;
}

struct CaptionState { double value[2] = {}; int target = -1; bool pressed = false; DWORD last = 0; };
static std::unordered_map<HWND, CaptionState> g_captions;
static constexpr UINT_PTR kCaptionTimer = 0xD178;

static RECT CaptionButton(HWND h, int index) {
    RECT wr, cr;
    GetWindowRect(h, &wr);
    GetClientRect(h, &cr);
    POINT p = {cr.right, 0};
    ClientToScreen(h, &p);
    int right = wr.right-wr.left-Scale(h,3);
    int left = p.x-wr.left;
    int centerY = Scale(h,16+index*24);
    return {left, centerY-Scale(h,12), right, centerY+Scale(h,12)};
}

static void PaintFrame(HWND h);
static void PaintCaptionHover(HWND h) { PaintFrame(h); }

static void PaintCaptionHoverDC(HWND h, HDC dc) {
    auto it = g_captions.find(h);
    if (it == g_captions.end()) return;
    for (int i=0; i<2; ++i) {
        double t = it->second.value[i];
        if (t <= 0) continue;
        RECT r = CaptionButton(h,i);
        if (r.right-r.left < Scale(h,12)) continue;
        int dd = 2 * Scale(h, 8);
        HRGN rg = CreateRoundRectRgn(r.left, r.top, r.right + 1, r.bottom + 1, dd, dd);
        HBRUSH hb = CreateSolidBrush(Lerp(RGB(0, 0, 0), kSurface0, t));
        FillRgn(dc, rg, hb);
        DeleteObject(hb);
        DeleteObject(rg);
        {
            Gdiplus::Graphics g(dc);
            g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            Gdiplus::GraphicsPath path;
            AddRoundRect(path,Gdiplus::RectF((float)r.left+0.5f,(float)r.top+0.5f,
                (float)(r.right-r.left)-1,(float)(r.bottom-r.top)-1),(float)Scale(h,8));
            Gdiplus::Pen pen(GpColor(it->second.pressed ? kMauve : g_cfg.accent,t),1);
            g.DrawPath(&pen,&path);
        }
        HFONT f=CreateFontW(-Scale(h,12),0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,
            DEFAULT_CHARSET,0,0,ANTIALIASED_QUALITY,0,L"Segoe Fluent Icons");
        HGDIOBJ old=SelectObject(dc,f);
        SetBkMode(dc,TRANSPARENT);
        SetTextColor(dc,kText);
        DrawTextW(dc,i==0 ? L"\uE711" : L"\uE76C",-1,&r,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
        SelectObject(dc,old);
        DeleteObject(f);
    }
}

// ---------- scrollbars ----------

// Ditto draws its own scrollbars in two thin Afx child windows over the list.
static std::set<HWND> g_scrollHover;
static std::set<HWND> g_scrollDrag;

static bool ThinBar(HWND h, bool* vertical) {
    RECT r;
    GetClientRect(h, &r);
    int t = Scale(h, 16);
    if (r.right > 0 && r.right <= t && r.bottom > r.right * 3) { *vertical = true; return true; }
    if (r.bottom > 0 && r.bottom <= t && r.right > r.bottom * 3) { *vertical = false; return true; }
    return false;
}

static void SyncScrollBars(HWND parent) {
    HWND list=GetDlgItem(parent,513);
    if(!list) return;
    // Collect first: raising a bar while walking the z-order revisits it forever.
    HWND bars[8]; int count=0;
    for(HWND child=GetWindow(parent,GW_CHILD);child && count<8;child=GetWindow(child,GW_HWNDNEXT)) {
        bool vertical=false;
        wchar_t cls[8]={};GetClassNameW(child,cls,8);
        if(wcsncmp(cls,L"Afx:",4)==0 && ThinBar(child,&vertical)) bars[count++]=child;
    }
    for(int i=0;i<count;++i) {
        HWND child=bars[i];
        bool vertical=false; ThinBar(child,&vertical);
        SCROLLINFO info={sizeof(info),SIF_RANGE|SIF_PAGE|SIF_POS};
        bool overflow=IsWindowVisible(list) && GetScrollInfo(list,vertical?SB_VERT:SB_HORZ,&info) &&
            info.nPage>0 && (int)info.nPage<info.nMax-info.nMin+1;
        if(IsWindowVisible(child)!=overflow) ShowWindow(child,overflow?SW_SHOWNOACTIVATE:SW_HIDE);
        if(!overflow) continue;
        // Only raise when something other than a bar sits above it.
        bool covered=false;
        for(HWND above=GetWindow(child,GW_HWNDPREV);above;above=GetWindow(above,GW_HWNDPREV)) {
            bool isBar=false;
            for(int j=0;j<count;++j) if(bars[j]==above) isBar=true;
            if(!isBar) { covered=true; break; }
        }
        if(covered) SetWindowPos(child,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
    }
}

static void PaintScroll(HWND h, HDC dc, bool vertical) {
    RECT rc;
    GetClientRect(h, &rc);
    int w = rc.right, ht = rc.bottom;
    HDC mem = CreateCompatibleDC(dc);
    HBITMAP bmp = CreateCompatibleBitmap(dc, w, ht);
    HGDIOBJ old = SelectObject(mem, bmp);
    {
        HBRUSH glass = (HBRUSH)GetStockObject(BLACK_BRUSH);
        FillRect(mem, &rc, glass);
        Gdiplus::Graphics g(mem);
        g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
        g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
        bool hot = g_scrollHover.count(h) || g_scrollDrag.count(h);
        float across = (float)(vertical ? w : ht);
        float thick = (float)Scale(h, hot ? 6 : 4);
        if (thick > across) thick = across;
        float off = (across - thick) / 2;
        int len = vertical ? ht : w;
        float pad = (float)Scale(h, 2);
        Gdiplus::GraphicsPath track;
        if (vertical) AddRoundRect(track, Gdiplus::RectF(off, pad, thick, len - 2 * pad), thick / 2);
        else AddRoundRect(track, Gdiplus::RectF(pad, off, len - 2 * pad, thick), thick / 2);
        Gdiplus::SolidBrush trackFill(GpColor(kSurface0, hot ? 0.9 : 0.55));
        g.FillPath(&trackFill, &track);
        HWND list = GetDlgItem(GetParent(h), 513);
        SCROLLINFO si = {sizeof(si), SIF_ALL};
        if (list && GetScrollInfo(list, vertical ? SB_VERT : SB_HORZ, &si)) {
            int range = si.nMax - si.nMin + 1;
            int page = (int)si.nPage;
            if (range > 0 && page > 0 && page < range) {
                float usable = len - 2 * pad;
                float thumb = usable * page / range;
                float minThumb = (float)Scale(h, 24);
                if (thumb < minThumb) thumb = minThumb;
                if (thumb > usable) thumb = usable;
                int pos = si.nPos - si.nMin;
                if (pos < 0) pos = 0;
                if (pos > range - page) pos = range - page;
                float at = pad + (usable - thumb) * pos / (float)(range - page);
                Gdiplus::GraphicsPath th;
                if (vertical) AddRoundRect(th, Gdiplus::RectF(off, at, thick, thumb), thick / 2);
                else AddRoundRect(th, Gdiplus::RectF(at, off, thumb, thick), thick / 2);
                COLORREF c = g_scrollDrag.count(h) ? kMauve : hot ? g_cfg.accent : kOverlay1;
                Gdiplus::SolidBrush thumbFill(GpColor(c));
                g.FillPath(&thumbFill, &th);
            }
        }
    }
    BitBlt(dc, 0, 0, w, ht, mem, 0, 0, SRCCOPY);
    SelectObject(mem, old);
    DeleteObject(bmp);
    DeleteDC(mem);
}

static LRESULT CALLBACK ScrollProc(HWND h, UINT msg, WPARAM wp, LPARAM lp, DWORD_PTR) {
    if (msg == WM_NULL && wp == 0xD177) return 0xD300;
    bool vertical = false;
    if (msg == WM_NCDESTROY) {
        std::lock_guard<std::mutex> lk(g_lock);
        g_subclassed.erase(h);
        g_scrollHover.erase(h);
        g_scrollDrag.erase(h);
    }
    if (!g_cfg.dock || !ThinBar(h, &vertical)) return DefSubclassProc(h, msg, wp, lp);
    if(msg==WM_WINDOWPOSCHANGING) {
        WINDOWPOS* position=(WINDOWPOS*)lp;
        if(!(position->flags&SWP_NOSIZE)) {
            int thickness=Scale(h,8);
            if(vertical) {position->x+=position->cx-thickness;position->cx=thickness;}
            else {position->y+=position->cy-thickness;position->cy=thickness;}
        }
        HWND list=GetDlgItem(GetParent(h),513);
        SCROLLINFO info={sizeof(info),SIF_RANGE|SIF_PAGE};
        bool overflow=GetScrollInfo(list,vertical?SB_VERT:SB_HORZ,&info) && info.nPage>0 &&
            (int)info.nPage<info.nMax-info.nMin+1;
        if(overflow && (position->flags&SWP_HIDEWINDOW)) {
            position->flags=(position->flags&~SWP_HIDEWINDOW)|SWP_SHOWWINDOW;
        }
    }
    switch (msg) {
        case WM_ERASEBKGND: return 1;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC dc = BeginPaint(h, &ps);
            PaintScroll(h, dc, vertical);
            EndPaint(h, &ps);
            return 0;
        }
        case WM_MOUSEMOVE:
            if (!g_scrollHover.count(h)) {
                g_scrollHover.insert(h);
                TRACKMOUSEEVENT tme = {sizeof(tme), TME_LEAVE, h, 0};
                TrackMouseEvent(&tme);
            }
            break;
        case WM_MOUSELEAVE: g_scrollHover.erase(h); break;
        case WM_LBUTTONDOWN: g_scrollDrag.insert(h); break;
        case WM_LBUTTONUP:
        case WM_CAPTURECHANGED: g_scrollDrag.erase(h); break;
    }
    LRESULT r = DefSubclassProc(h, msg, wp, lp);
    // Ditto may draw its own thumb outside WM_PAINT; put ours back on top.
    if (msg == WM_MOUSEMOVE || msg == WM_MOUSELEAVE || msg == WM_LBUTTONDOWN ||
        msg == WM_LBUTTONUP || msg == WM_CAPTURECHANGED || msg == WM_TIMER) {
        HDC dc = GetDC(h);
        PaintScroll(h, dc, vertical);
        ReleaseDC(h, dc);
    }
    return r;
}

// ---------- frame: sidebar and uniform border ----------

static void PaintFrame(HWND h) {
    RECT wr, cr;
    GetWindowRect(h, &wr);
    GetClientRect(h, &cr);
    POINT p = {0, 0};
    ClientToScreen(h, &p);
    int W = wr.right - wr.left, H = wr.bottom - wr.top;
    int cl = p.x - wr.left, ct = p.y - wr.top;
    int cR = cl + cr.right;
    HDC target = GetWindowDC(h);
    HDC dc=CreateCompatibleDC(target);
    BITMAPINFO bi={}; bi.bmiHeader={sizeof(BITMAPINFOHEADER),W,-H,1,32,BI_RGB};
    void* pixels=nullptr;
    HBITMAP bitmap=CreateDIBSection(target,&bi,DIB_RGB_COLORS,&pixels,nullptr,0);
    HGDIOBJ previous=SelectObject(dc,bitmap);
    if (W - cR > Scale(h, 12)) {
        RECT side = {cR, 0, W, H};
        FillRect(dc, &side, (HBRUSH)GetStockObject(BLACK_BRUSH));
        RECT line = {cR, 0, cR + Scale(h, 1), H};
        HBRUSH lb = CreateSolidBrush(kSurface1);
        FillRect(dc, &line, lb);
        DeleteObject(lb);
        HFONT f = CreateFontW(-Scale(h, 12), 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, 0, L"Segoe Fluent Icons");
        HGDIOBJ old = SelectObject(dc, f);
        SetBkMode(dc, TRANSPARENT);
        SetTextColor(dc, kOverlay1);
        for (int i = 0; i < 2; ++i) {
            RECT r = CaptionButton(h, i);
            r.left += Scale(h, 1);
            DrawTextW(dc, i == 0 ? L"\uE711" : L"\uE76C", -1, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        }
        SelectObject(dc, old);
        DeleteObject(f);
        PaintCaptionHoverDC(h, dc);
        DarkenDC(dc, side, kCrust, kDarkA, nullptr, 0);
    }
    BitBlt(target,cR,0,W-cR,H,dc,cR,0,SRCCOPY);
    SelectObject(dc,previous); DeleteObject(bitmap); DeleteDC(dc);
    (void)ct;
    ReleaseDC(h, target);
}

static void ApplyGlass(HWND h, bool on) {
    DWORD corner = on ? 1 : 0;  // DWMWCP_DONOTROUND: our 16 px region rounds instead
    DwmSetWindowAttribute(h, 33, &corner, sizeof(corner));
    COLORREF border = on ? 0xFFFFFFFE : 0xFFFFFFFF;  // our ring is the only border
    DwmSetWindowAttribute(h, 34, &border, sizeof(border));
    if (on) SendMessageW(h, WM_NULL, 0xD177, 3);  // overlay is created on Ditto's own thread
    else RemoveRing(h);
    SetAccent(h, on, kCrust, 35);
    SetWindowPos(h, nullptr, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

static thread_local HWND g_drawingList=nullptr;
static std::unordered_map<HWND,int> g_wheelRemainder;
static bool ScrollClips(HWND h, WPARAM wp) {
    HWND parent=IsQPaste(h) ? h : GetAncestor(h,GA_ROOT);
    if (!IsQPaste(parent)) return false;
    HWND list=GetDlgItem(parent,513);
    if (!list) return false;
    int& remainder=g_wheelRemainder[list];
    remainder+=(short)HIWORD(wp);
    int steps=remainder/WHEEL_DELTA; remainder%=WHEEL_DELTA;
    if (steps) {
        RECT row={}; row.left=LVIR_BOUNDS;
        SendMessageW(list,LVM_GETITEMRECT,0,(LPARAM)&row);
        int height=row.bottom-row.top;
        if(height<1) height=Scale(list,36);
        UINT lines=3; SystemParametersInfoW(SPI_GETWHEELSCROLLLINES,0,&lines,0);
        int count=lines==WHEEL_PAGESCROLL ? (int)SendMessageW(list,LVM_GETCOUNTPERPAGE,0,0) : (lines ? 1 : 0);
        SendMessageW(list,LVM_SCROLL,0,-steps*height*count);
        SyncScrollBars(parent);
        for(HWND child=GetWindow(parent,GW_CHILD);child;child=GetWindow(child,GW_HWNDNEXT)) {
            bool vertical=false;
            if(ThinBar(child,&vertical)) InvalidateRect(child,nullptr,FALSE);
        }
    }
    return true;
}
static LRESULT CALLBACK ListProc(HWND h,UINT msg,WPARAM wp,LPARAM lp,DWORD_PTR) {
    if(msg==WM_MOUSEWHEEL && ScrollClips(h,wp)) return 0;
    if(msg==WM_SIZE) {
        LRESULT result=DefSubclassProc(h,msg,wp,lp);
        RECT visible; GetClientRect(h,&visible);
        SendMessageW(h,LVM_SETCOLUMNWIDTH,0,visible.right-Scale(h,12));
        return result;
    }
    if(msg==WM_PAINT) {
        HWND old=g_drawingList; g_drawingList=h;
        LRESULT result=DefSubclassProc(h,msg,wp,lp); g_drawingList=old; return result;
    }
    return DefSubclassProc(h,msg,wp,lp);
}
static void RouteWheel(MSG* msg) {
    if(msg->message==WM_MOUSEWHEEL && ScrollClips(msg->hwnd,msg->wParam)) msg->message=WM_NULL;
}
static std::unordered_map<DWORD,HHOOK> g_messageHooks;
static LRESULT CALLBACK MessageHook(int code,WPARAM wp,LPARAM lp) {
    if(code>=0 && wp==PM_REMOVE) RouteWheel((MSG*)lp);
    return CallNextHookEx(nullptr,code,wp,lp);
}
static void HookMessages(HWND parent) {
    DWORD thread=GetWindowThreadProcessId(parent,nullptr);
    if(g_messageHooks.count(thread)) return;
    HMODULE module=nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPCWSTR)&MessageHook,&module);
    HHOOK hook=SetWindowsHookExW(WH_GETMESSAGE,MessageHook,module,thread);
    if(hook) g_messageHooks[thread]=hook;
}

static LRESULT CALLBACK ParentProc(HWND h, UINT msg, WPARAM wp, LPARAM lp, DWORD_PTR) {
    if (msg==WM_NULL && wp==0xD177) {
        if(lp==1) { LayoutDock(h); PaintDock(h); return 1; }
        if(lp==3) { UpdateRing(h); return 1; }
        if(lp==4) { KillTimer(h,kDockTimer); KillTimer(h,kCaptionTimer); return 1; }
        if(lp==2) return (g_captions[h].target+1)*1000+(int)(g_captions[h].value[0]*100)+(int)(g_captions[h].value[1]*100);
        return 0xD177;
    }
    if(msg==WM_TIMER && wp==kDockTimer) {
        SyncScrollBars(h);
        POINT point; GetCursorPos(&point); ScreenToClient(h,&point);
        RECT dock=DockRect(h);
        double target=IsWindowVisible(h) && PtInRect(&dock,point) ? 1.0 : 0.0;
        double& current=g_dockHover[h]; double old=current;
        current+=target>current ? 0.2 : -0.2;
        if(current<0) current=0; if(current>1) current=1;
        if(current!=old) PaintDock(h);
        return 0;
    }
    if (msg==WM_MOUSEWHEEL && ScrollClips(h,wp)) return 0;
    if (g_cfg.dock && msg == WM_NCCALCSIZE) {
        RECT* rc = wp ? &((NCCALCSIZE_PARAMS*)lp)->rgrc[0] : (RECT*)lp;
        LONG winBottom = rc->bottom;
        LRESULT r = DefSubclassProc(h, msg, wp, lp);
        LONG want = winBottom - Scale(h, 2);
        if (rc->bottom > rc->top && rc->bottom < want) rc->bottom = want;
        return r;
    }
    if (g_cfg.dock && msg == WM_NCHITTEST) {
        LRESULT r = DefSubclassProc(h, msg, wp, lp);
        if (r == HTCLIENT) {
            RECT wr;
            GetWindowRect(h, &wr);
            int x = (short)LOWORD(lp), y = (short)HIWORD(lp);
            if (y >= wr.bottom - Scale(h, 5)) {
                if (x < wr.left + Scale(h, 16)) return HTBOTTOMLEFT;
                if (x >= wr.right - Scale(h, 16)) return HTBOTTOMRIGHT;
                return HTBOTTOM;
            }
        }
        return r;
    }
    if (g_cfg.dock && msg == WM_CTLCOLOREDIT && InDock((HWND)lp)) {
        SetBkColor((HDC)wp, RGB(0,0,0));
        SetTextColor((HDC)wp, kText);
        static HBRUSH brush = (HBRUSH)GetStockObject(BLACK_BRUSH);
        return (LRESULT)brush;
    }
    if (msg == WM_NCDESTROY) {
        ForgetRing(h);
        std::lock_guard<std::mutex> lk(g_lock);
        g_subclassed.erase(h);
        g_captions.erase(h);
    }
    if (g_cfg.glass && msg == WM_WINDOWPOSCHANGED) {
        LRESULT r = DefSubclassProc(h, msg, wp, lp);
        UpdateRing(h);
        return r;
    }
    if (g_cfg.dock && (msg == WM_NCMOUSEMOVE || msg == WM_NCMOUSELEAVE)) {
        auto& state = g_captions[h];
        int target = -1;
        if (msg == WM_NCMOUSEMOVE) {
            RECT wr;
            GetWindowRect(h,&wr);
            POINT p = {(short)LOWORD(lp)-wr.left,(short)HIWORD(lp)-wr.top};
            for (int i=0;i<2;++i) { RECT r=CaptionButton(h,i); if (PtInRect(&r,p)) target=i; }
            TRACKMOUSEEVENT track={sizeof(track),TME_LEAVE|TME_NONCLIENT,h,0};
            TrackMouseEvent(&track);
        }
        if (state.target != target) {
            state.target=target;
            state.last=GetTickCount();
            SetTimer(h,kCaptionTimer,15,nullptr);
        }
    }
    if (msg == WM_NCLBUTTONDOWN) g_captions[h].pressed=true;
    if (msg == WM_NCLBUTTONUP || msg == WM_NCMOUSELEAVE) g_captions[h].pressed=false;
    if (msg == WM_TIMER && wp == kCaptionTimer) {
        auto& state = g_captions[h];
        DWORD now=GetTickCount();
        double step=(now-state.last)/150.0;
        state.last=now;
        bool done=true;
        for(int i=0;i<2;++i) {
            double target=state.target==i ? 1.0 : 0.0;
            state.value[i] += (target>state.value[i] ? step : -step);
            if(state.value[i]<0) state.value[i]=0;
            if(state.value[i]>1) state.value[i]=1;
            if(state.value[i]!=target) done=false;
        }
        if(done) KillTimer(h,kCaptionTimer);
        PaintFrame(h);
        return 0;
    }
    LRESULT r = DefSubclassProc(h, msg, wp, lp);
    if (g_cfg.dock && msg == WM_PAINT) {
        EnumChildWindows(h, AttachChild, 0);
        LayoutDock(h);
        PaintDock(h);
    }
    if (g_cfg.dock && (msg == WM_NCPAINT || msg == WM_NCACTIVATE || msg == WM_PAINT))
        PaintFrame(h);
    if (g_cfg.dock && (msg == WM_NCPAINT || msg == WM_NCACTIVATE))
        PaintDock(h);
    if (g_cfg.dock && (msg == WM_NCMOUSEMOVE || msg == WM_NCLBUTTONDOWN || msg == WM_NCLBUTTONUP))
        PaintCaptionHover(h);
    if (g_cfg.dock && msg == WM_SIZE) {
        LayoutDock(h);
        RECT d = DockRect(h);
        InflateRect(&d, 4, 4);
        RedrawWindow(h, &d, nullptr, RDW_INVALIDATE | RDW_ALLCHILDREN | RDW_ERASE);
    }
    return r;
}

// ---------- attach ----------

static BOOL CALLBACK AttachChild(HWND c, LPARAM) { Attach(c); return TRUE; }

static void Attach(HWND h) {
    {
        std::lock_guard<std::mutex> lk(g_lock);
        if (g_subclassed.count(h)) return;
    }
    WindhawkUtils::WH_SUBCLASSPROC proc = nullptr;
    if (ClassIs(h, TOOLTIPS_CLASSW)) {
        proc = TipProc;
    } else if (IsQPaste(h)) {
        proc = ParentProc;
    } else if (IsQPaste(GetParent(h))) {
        if (ClassIs(h,L"SysListView32")) proc=ListProc;
        else if (ClassIs(h, L"Edit")) proc = SearchProc;
        else if (ClassIs(h, L"Button") && (GetWindowLongW(h, GWL_STYLE) & BS_TYPEMASK) == BS_OWNERDRAW)
            proc = ButtonProc;
        else {
            wchar_t cls[8] = {};
            GetClassNameW(h, cls, 8);
            if (wcsncmp(cls, L"Afx:", 4) == 0) proc = ScrollProc;
        }
    }
    if (!proc) return;
    if (!WindhawkUtils::SetWindowSubclassFromAnyThread(h, proc, 0)) return;
    {
        std::lock_guard<std::mutex> lk(g_lock);
        g_subclassed.insert(h);
    }
    if (proc == TipProc && g_cfg.tooltips) {
        // Must run on the owner thread; a subclass message gets us there.
        SendMessageW(h, WM_NULL, 0xD177, 0xD177);
    }
    if (proc == ParentProc) {
        HookMessages(h);
        SetTimer(h,kDockTimer,30,nullptr);
        if (g_cfg.glass) ApplyGlass(h, true);
        EnumChildWindows(h, AttachChild, 0);
        HWND list=GetDlgItem(h,513);
        if(list) SendMessageW(list,LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_DOUBLEBUFFER,LVS_EX_DOUBLEBUFFER);
        // Use Ditto's own five-line command so row height and thumbnail caches agree.
        PostMessageW(h,WM_COMMAND,32789,0);
        RECT wr; GetWindowRect(h,&wr);
        int width=Scale(h,960),height=Scale(h,740);
        if(wr.right-wr.left<width) SetWindowPos(h,nullptr,0,0,width,
            (wr.bottom-wr.top)>height ? wr.bottom-wr.top : height,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
        if (IsWindowVisible(h)) RedrawWindow(h, nullptr, nullptr, RDW_INVALIDATE | RDW_ALLCHILDREN | RDW_FRAME);
    }
}

static BOOL CALLBACK AttachTop(HWND h, LPARAM) {
    DWORD pid;
    GetWindowThreadProcessId(h, &pid);
    if (pid == GetCurrentProcessId()) Attach(h);
    return TRUE;
}


// ---------- hooks ----------

using CreateWindowExW_t = decltype(&CreateWindowExW);
static CreateWindowExW_t CreateWindowExW_orig;
static HWND WINAPI CreateWindowExW_hook(DWORD ex, LPCWSTR cls, LPCWSTR name, DWORD style, int x, int y,
                                        int w, int hgt, HWND parent, HMENU menu, HINSTANCE inst, LPVOID param) {
    HWND h = CreateWindowExW_orig(ex, cls, name, style, x, y, w, hgt, parent, menu, inst, param);
    if (h) {
        if (ClassIs(h, TOOLTIPS_CLASSW) || IsQPaste(h)) Attach(h);
        else if (IsQPaste(parent)) Attach(h);  // position is checked at paint time
    }
    return h;
}

static void Animate(HWND h, bool show, int origCmd);
static thread_local bool t_inAnim = false;

using ShowWindow_t = decltype(&ShowWindow);
static ShowWindow_t ShowWindow_orig;
static BOOL WINAPI ShowWindow_hook(HWND h, int cmd) {
    BOOL anim = FALSE;
    SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &anim, 0);
    if (!g_cfg.animate || !anim || t_inAnim || !IsQPaste(h) || (GetWindowLongW(h, GWL_STYLE) & WS_CHILD))
        return ShowWindow_orig(h, cmd);
    bool visible = IsWindowVisible(h);
    if (cmd == SW_HIDE && visible) {
        Animate(h, false, cmd);
        return TRUE;
    }
    if (cmd != SW_HIDE && cmd != SW_MINIMIZE && cmd != SW_FORCEMINIMIZE && !visible) {
        Animate(h, true, cmd);
        return FALSE;  // was hidden
    }
    return ShowWindow_orig(h, cmd);
}

static void Animate(HWND h, bool show, int cmd) {
    t_inAnim = true;
    LONG ex = GetWindowLongW(h, GWL_EXSTYLE);
    bool wasLayered = ex & WS_EX_LAYERED;
    BYTE startAlpha = 255;
    DWORD flags = 0;
    COLORREF key = 0;
    if (wasLayered) {
        GetLayeredWindowAttributes(h, &key, &startAlpha, &flags);
        if (!(flags & LWA_ALPHA)) startAlpha = 255;
    } else {
        SetWindowLongW(h, GWL_EXSTYLE, ex | WS_EX_LAYERED);
    }
    BYTE target = startAlpha;
    if (show) {
        SetLayeredWindowAttributes(h, 0, 0, LWA_ALPHA);
        ShowWindow_orig(h, cmd);
        RedrawWindow(h, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_FRAME);
    }
    int ms = g_cfg.animMs;
    if (!show) ms = ms * 4 / 5;
    DWORD t0 = GetTickCount();
    for (;;) {
        double t = (GetTickCount() - t0) / (double)ms;
        if (t > 1) t = 1;
        double e = 1 - pow(1 - t, 3);
        double a = show ? e : 1 - e;
        SetLayeredWindowAttributes(h, 0, (BYTE)(target * a), LWA_ALPHA);
        DwmFlush();
        if (t >= 1) break;
    }
    if (!show) ShowWindow_orig(h, SW_HIDE);
    if (wasLayered) {
        SetLayeredWindowAttributes(h, key, target, flags);
    } else {
        SetWindowLongW(h, GWL_EXSTYLE, GetWindowLongW(h, GWL_EXSTYLE) & ~WS_EX_LAYERED);
        if (show) RedrawWindow(h, nullptr, nullptr, RDW_INVALIDATE | RDW_ALLCHILDREN | RDW_FRAME);
    }
    t_inAnim = false;
}

static bool LiftTinyFont(LOGFONTW& f) {
    LONG px = f.lfHeight < 0 ? -f.lfHeight : f.lfHeight;
    UINT dpi = GetDpiForSystem();
    if (px <= 0 || px >= MulDiv(11, dpi, 96)) return false;
    Wh_Log(L"lift font %s %ld px", f.lfFaceName, px);
    f.lfHeight = -MulDiv(12, dpi, 96);
    f.lfWidth = 0;
    f.lfWeight = FW_SEMIBOLD;
    f.lfQuality = CLEARTYPE_QUALITY;
    wcscpy_s(f.lfFaceName, L"FiraCode Nerd Font");
    return true;
}

using CreateFontIndirectW_t = decltype(&CreateFontIndirectW);
static CreateFontIndirectW_t CreateFontIndirectW_orig;
static HFONT WINAPI CreateFontIndirectW_hook(const LOGFONTW* lf) {
    if (lf) {
        LOGFONTW f = *lf;
        if (LiftTinyFont(f)) return CreateFontIndirectW_orig(&f);
    }
    return CreateFontIndirectW_orig(lf);
}

using CreateFontW_t = decltype(&CreateFontW);
static CreateFontW_t CreateFontW_orig;
static HFONT WINAPI CreateFontW_hook(int h, int w, int esc, int ori, int weight, DWORD it, DWORD ul,
                                     DWORD so, DWORD cs, DWORD op, DWORD cp, DWORD q, DWORD pf,
                                     LPCWSTR face) {
    LOGFONTW f{};
    f.lfHeight = h;
    if (LiftTinyFont(f))
        return CreateFontW_orig(f.lfHeight, 0, esc, ori, FW_SEMIBOLD, it, ul, so, cs, op, cp,
                                CLEARTYPE_QUALITY, pf, L"FiraCode Nerd Font");
    return CreateFontW_orig(h, w, esc, ori, weight, it, ul, so, cs, op, cp, q, pf, face);
}

static HFONT g_numFont;
static bool IsRowNumber(HDC dc, LPCWSTR t, int n) {
    if (!t) return false;
    if (n < 0) n = lstrlenW(t);
    if (n < 1 || n > 3) return false;
    for (int i = 0; i < n; i++) if (t[i] < L'0' || t[i] > L'9') return false;
    TEXTMETRICW tm;
    return GetTextMetricsW(dc, &tm) && tm.tmHeight < MulDiv(12, GetDpiForSystem(), 96);
}
static HFONT NumberFont() {
    if (!g_numFont)
        g_numFont = CreateFontW(-MulDiv(13, GetDpiForSystem(), 96), 0, 0, 0, FW_SEMIBOLD, 0, 0, 0,
                                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                CLEARTYPE_QUALITY, FIXED_PITCH, L"FiraCode Nerd Font");
    return g_numFont;
}

using DrawTextW_t = decltype(&DrawTextW);
static DrawTextW_t DrawTextW_orig;
static int WINAPI DrawTextW_hook(HDC dc, LPCWSTR t, int n, LPRECT r, UINT fmt) {
    if (g_cfg.dock && IsRowNumber(dc, t, n)) {
        HGDIOBJ old = SelectObject(dc, NumberFont());
        int res = DrawTextW_orig(dc, t, n, r, fmt | DT_NOCLIP);
        SelectObject(dc, old);
        return res;
    }
    if(g_drawingList && r && !(fmt&DT_CALCRECT) && n!=0) {
        RECT visible; GetClientRect(g_drawingList,&visible);
        RECT wrap=*r; wrap.right=(wrap.right<visible.right-12 ? wrap.right : visible.right-12);
        if(wrap.right>wrap.left) return DrawTextW_orig(dc,t,n,&wrap,(fmt&~(DT_SINGLELINE|DT_NOCLIP|DT_VCENTER))|DT_WORDBREAK|DT_EDITCONTROL);
    }
    return DrawTextW_orig(dc, t, n, r, fmt);
}

using DrawTextExW_t = decltype(&DrawTextExW);
static DrawTextExW_t DrawTextExW_orig;
static int WINAPI DrawTextExW_hook(HDC dc, LPWSTR t, int n, LPRECT r, UINT fmt, LPDRAWTEXTPARAMS p) {
    if (g_cfg.dock && IsRowNumber(dc, t, n)) {
        HGDIOBJ old = SelectObject(dc, NumberFont());
        int res = DrawTextExW_orig(dc, t, n, r, fmt | DT_NOCLIP, p);
        SelectObject(dc, old);
        return res;
    }
    return DrawTextExW_orig(dc, t, n, r, fmt, p);
}

using CreateFontIndirectExW_t = decltype(&CreateFontIndirectExW);
static CreateFontIndirectExW_t CreateFontIndirectExW_orig;
static HFONT WINAPI CreateFontIndirectExW_hook(const ENUMLOGFONTEXDVW* e) {
    if (e) {
        const LOGFONTW& lf = e->elfEnumLogfontEx.elfLogFont;
        LONG px = lf.lfHeight < 0 ? -lf.lfHeight : lf.lfHeight;
        if (px > 0 && px < MulDiv(11, GetDpiForSystem(), 96)) {
            ENUMLOGFONTEXDVW copy = *e;
            LOGFONTW& f = copy.elfEnumLogfontEx.elfLogFont;
            f.lfHeight = -MulDiv(12, GetDpiForSystem(), 96);
            f.lfWidth = 0;
            f.lfWeight = FW_SEMIBOLD;
            f.lfQuality = CLEARTYPE_QUALITY;
            wcscpy_s(f.lfFaceName, L"FiraCode Nerd Font");
            return CreateFontIndirectExW_orig(&copy);
        }
    }
    return CreateFontIndirectExW_orig(e);
}

BOOL Wh_ModInit() {
    LoadConfig();
    Gdiplus::GdiplusStartupInput in;
    Gdiplus::GdiplusStartup(&g_gdiplusToken, &in, nullptr);
    Wh_SetFunctionHook((void*)CreateWindowExW, (void*)CreateWindowExW_hook, (void**)&CreateWindowExW_orig);
    Wh_SetFunctionHook((void*)ShowWindow, (void*)ShowWindow_hook, (void**)&ShowWindow_orig);
    Wh_SetFunctionHook((void*)CreateFontIndirectExW, (void*)CreateFontIndirectExW_hook,
                       (void**)&CreateFontIndirectExW_orig);
    Wh_SetFunctionHook((void*)CreateFontIndirectW, (void*)CreateFontIndirectW_hook,
                       (void**)&CreateFontIndirectW_orig);
    Wh_SetFunctionHook((void*)CreateFontW, (void*)CreateFontW_hook, (void**)&CreateFontW_orig);
    Wh_SetFunctionHook((void*)DrawTextW, (void*)DrawTextW_hook, (void**)&DrawTextW_orig);
    Wh_SetFunctionHook((void*)DrawTextExW, (void*)DrawTextExW_hook, (void**)&DrawTextExW_orig);
    return TRUE;
}

void Wh_ModAfterInit() { EnumWindows(AttachTop, 0); }

static BOOL CALLBACK RevertTop(HWND h, LPARAM) {
    DWORD pid;
    GetWindowThreadProcessId(h, &pid);
    if (pid != GetCurrentProcessId()) return TRUE;
    if (ClassIs(h, TOOLTIPS_CLASSW)) {
        RemoveRing(h);
        auto it = g_tips.find(h);
        if (it != g_tips.end()) {
            SetWindowLongW(h, GWL_STYLE, it->second.originalStyle);
            SendMessageW(h, WM_SETFONT, (WPARAM)it->second.originalFont, FALSE);
            SendMessageW(h, TTM_SETTIPBKCOLOR, it->second.originalBackground, 0);
            SendMessageW(h, TTM_SETTIPTEXTCOLOR, it->second.originalText, 0);
        }
        SetAccent(h, false, 0, 0);
        MARGINS mg = {0, 0, 0, 0};
        DwmExtendFrameIntoClientArea(h, &mg);
        DWORD def = 0;
        DwmSetWindowAttribute(h, 33, &def, sizeof(def));
        COLORREF none = 0xFFFFFFFF;  // DWMWA_COLOR_DEFAULT
        DwmSetWindowAttribute(h, 34, &none, sizeof(none));
        SetWindowTheme(h, nullptr, nullptr);
    }
    if (IsQPaste(h)) ApplyGlass(h, false);
    if (IsQPaste(h)) RedrawWindow(h, nullptr, nullptr, RDW_INVALIDATE | RDW_ALLCHILDREN | RDW_FRAME | RDW_ERASE);
    return TRUE;
}

void Wh_ModUninit() {
    for(auto& hook:g_messageHooks) UnhookWindowsHookEx(hook.second);
    g_messageHooks.clear();
    std::set<HWND> copy;
    {
        std::lock_guard<std::mutex> lk(g_lock);
        copy = g_subclassed;
    }
    for (HWND h : copy) {
        // Timers belong to Ditto's thread; KillTimer from the engine thread does nothing.
        DWORD_PTR ignored;
        if (IsQPaste(h)) SendMessageTimeoutW(h, WM_NULL, 0xD177, 4, SMTO_ABORTIFHUNG, 2000, &ignored);
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(h, TipProc);
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(h, ParentProc);
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(h, SearchProc);
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(h, ButtonProc);
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(h, ScrollProc);
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(h, ListProc);
    }
    EnumWindows(RevertTop, 0);
    for (auto& kv : g_tips) if (kv.second.font) DeleteObject(kv.second.font);
    g_tips.clear();
    g_btns.clear();
    g_captions.clear();
    g_subclassed.clear();
}

static BOOL CALLBACK ReapplyTop(HWND h, LPARAM) {
    DWORD pid;
    GetWindowThreadProcessId(h, &pid);
    if (pid == GetCurrentProcessId() && g_cfg.glass && IsQPaste(h)) ApplyGlass(h, true);
    if (pid == GetCurrentProcessId() && g_cfg.tooltips && ClassIs(h, TOOLTIPS_CLASSW))
        SendMessageW(h, WM_NULL, 0xD177, 0xD177);
    return TRUE;
}

void Wh_ModSettingsChanged() {
    LoadConfig();
    EnumWindows(RevertTop, 0);
    EnumWindows(ReapplyTop, 0);
}
