// ==WindhawkMod==
// @id              ableton-glass-fill
// @name            Ableton Glass Fill
// @description     Matches Ableton's menu bar and Settings window to its title bar glass, and keeps the glass tint Mocha
// @version         1.5.1
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         Ableton Live 12 Suite.exe
// @compilerOptions -ldwmapi -lgdi32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
Ableton paints its menu bar with a see-through dark colour, so on a window with glass behind
it the area comes out lighter than the title bar. This mod paints that fill black so the glass
shows through as is. The glass tint is a light Mocha veil (38% on the main window, 25% on
Settings), so the blur stays visible like Explorer's frosted glass instead of a flat slab.

![Ableton Glass Fill preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/ableton-glass-fill.png)

The Settings window paints its whole body, slate background included, into a Direct3D frame
that sits on top of the glass. For that one window the mod turns the background colour into
see-through just before each frame is shown, so the same glass as the title bar shows behind
it. Text, fields and highlights keep their look, and the frame is put back the way Ableton
had it right after, so nothing changes twice.
*/
// ==/WindhawkModReadme==

#include <windows.h>
#include <dwmapi.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <stdio.h>
#include <stdarg.h>

static void FLog(const wchar_t* fmt, ...) {
    wchar_t b[512];
    va_list a;
    va_start(a, fmt);
    _vsnwprintf(b, 511, fmt, a);
    va_end(a);
    b[511] = 0;
    Wh_Log(L"%s", b);
    HANDLE h = CreateFileW(L"C:\\Temp\\wh\\abl.log", FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE,
                           nullptr, OPEN_ALWAYS, 0, nullptr);
    if (h == INVALID_HANDLE_VALUE) return;
    char u[1024];
    int n = WideCharToMultiByte(CP_UTF8, 0, b, -1, u, 1020, nullptr, nullptr);
    if (n > 0) { u[n - 1] = '\n'; DWORD w; WriteFile(h, u, n, &w, nullptr); }
    CloseHandle(h);
}

// Glass tint, AABBGGRR. A thick D8 tint hides the blur when the content behind is flat,
// so it stays light: 0x60 on the main window (has a menu), 0x40 on Settings and other windows.
// Measured 2026-11-19: these give the same visible frost as Explorer over the wallpaper.
static const DWORD kTintMainAbgr = 0x602E1E1E;
static const DWORD kTintOtherAbgr = 0x402E1E1E;
static DWORD TintFor(HWND hWnd) { return GetMenu(hWnd) ? kTintMainAbgr : kTintOtherAbgr; }
// Background colour Ableton paints see-through (alpha 0) on its menu bar.
static const COLORREF kMenuBarFill = RGB(24, 25, 38);

struct ACCENT_POLICY { int AccentState; int AccentFlags; DWORD GradientColor; int AnimationId; };
struct WINCOMPATTRDATA { int Attrib; PVOID pvData; SIZE_T cbData; };

static bool IsAbletonTop(HWND hWnd) {
    if (!hWnd || !IsWindow(hWnd)) return false;
    if (GetWindowLongPtrW(hWnd, GWL_STYLE) & WS_CHILD) return false;
    WCHAR cls[64];
    if (!GetClassNameW(hWnd, cls, 64)) return false;
    return wcscmp(cls, L"Ableton Live Window Class") == 0;
}

// ---- glass tint ----
using SetWCA_t = BOOL(WINAPI*)(HWND, WINCOMPATTRDATA*);
static SetWCA_t SetWCA_orig = nullptr;

static BOOL WINAPI SetWCA_hook(HWND hWnd, WINCOMPATTRDATA* data) {
    if (data && data->Attrib == 19 && data->pvData && data->cbData >= sizeof(ACCENT_POLICY) &&
        IsAbletonTop(hWnd)) {
        ACCENT_POLICY* a = (ACCENT_POLICY*)data->pvData;
        if (a->AccentState == 4) {
            ACCENT_POLICY copy = *a;
            copy.GradientColor = TintFor(hWnd);
            WINCOMPATTRDATA d2 = *data;
            d2.pvData = &copy;
            return SetWCA_orig(hWnd, &d2);
        }
    }
    return SetWCA_orig(hWnd, data);
}

static void ApplyTint(HWND hWnd) {
    if (!SetWCA_orig) return;
    ACCENT_POLICY a = {4, 0, TintFor(hWnd), 0};
    WINCOMPATTRDATA d = {19, &a, sizeof(a)};
    SetWCA_orig(hWnd, &d);
}

// ---- menu bar: GDI fill with alpha 0 ----
using FillRect_t = int(WINAPI*)(HDC, const RECT*, HBRUSH);
static FillRect_t FillRect_orig = nullptr;

// Windows reads menu row spacing once per process. Seamless Flyouts reports the compact spacing,
// but an Ableton that was already running keeps the old one, so it is re-read once, on the UI
// thread, the first time the menu bar paints (uxtheme ordinal 136, the same call Flyouts uses).
static volatile LONG g_menuFlushed = 0;
static void FlushMenuSpacingOnce() {
    if (InterlockedExchange(&g_menuFlushed, 1)) return;
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    auto flush = ux ? (void(WINAPI*)())GetProcAddress(ux, MAKEINTRESOURCEA(136)) : nullptr;
    if (flush) { flush(); FLog(L"menu spacing re-read"); }
}

static int WINAPI FillRect_hook(HDC hdc, const RECT* rc, HBRUSH br) {
    if ((ULONG_PTR)br > 32 && GetObjectType(br) == OBJ_BRUSH) {
        LOGBRUSH lb;
        if (GetObjectW(br, sizeof(lb), &lb) == sizeof(lb) && lb.lbStyle == BS_SOLID &&
            lb.lbColor == kMenuBarFill && IsAbletonTop(WindowFromDC(hdc))) {
            FlushMenuSpacingOnce();
            return FillRect_orig(hdc, rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
        }
    }
    return FillRect_orig(hdc, rc, br);
}

// ---- Settings window: background colour to glass ----
// DWM blends this frame premultiplied over the window's glass. Before Present one pass does a
// colour-to-alpha on Ableton's slate background: the background becomes alpha 0 / rgb 0 (pure
// glass, same as the title bar), every other pixel keeps its look as premultiplied colour.
// Right after Present the frame is restored to what Ableton wrote, for its partial redraws.
static const char kShader[] =
    "Texture2D srcTex : register(t0);"
    "SamplerState srcSamp : register(s0);"
    "float4 vs(uint id : SV_VertexID, out float2 uv : TEXCOORD0) : SV_Position {"
    "  float2 p = float2((id << 1) & 2, id & 2);"
    "  uv = p;"
    "  return float4(p * float2(2, -2) + float2(-1, 1), 0, 1); }"
    "float4 ps(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {"
    "  float3 c = srcTex.Sample(srcSamp, uv).rgb;"
    "  float3 bg = float3(30, 32, 48) / 255.0;"
    "  float3 up = saturate((c - bg) / (1 - bg));"
    "  float3 dn = saturate((bg - c) / bg);"
    "  float a = max(max(max(up.x, up.y), up.z), max(max(dn.x, dn.y), dn.z));"
    "  if (a < 0.02) return float4(0, 0, 0, 0);"
    "  return float4(saturate(c - (1 - a) * bg), a); }";

using D3DCompile_t = HRESULT(WINAPI*)(LPCVOID, SIZE_T, LPCSTR, const void*, void*, LPCSTR, LPCSTR,
                                      UINT, UINT, ID3DBlob**, ID3DBlob**);

struct ChainCache {
    void* sc;
    DWORD tick;              // last settings-window check for this chain
    bool isSettings;
    ID3D11Texture2D* copy;   // pristine copy of Ableton's frame
    ID3D11ShaderResourceView* srv;
    UINT w, h;
};

static CRITICAL_SECTION g_cs;
static ID3D11Device* g_dev = nullptr;
static ID3D11VertexShader* g_vs = nullptr;
static ID3D11PixelShader* g_ps = nullptr;
static ID3D11SamplerState* g_samp = nullptr;
static ChainCache g_chains[8] = {};
static HWND g_settingsHwnd = nullptr;
static DWORD g_lastFind = 0;
static volatile LONG g_remapLogs = 0;

template <class T> static void SafeRelease(T*& p) { if (p) { p->Release(); p = nullptr; } }

static void ReleaseResources() {
    for (int i = 0; i < 8; i++) { SafeRelease(g_chains[i].srv); SafeRelease(g_chains[i].copy); g_chains[i] = {}; }
    SafeRelease(g_vs); SafeRelease(g_ps); SafeRelease(g_samp);
    SafeRelease(g_dev);
}

struct SettingsFind { HWND found; };

static BOOL CALLBACK FindSettingsProc(HWND hWnd, LPARAM l) {
    auto* c = (SettingsFind*)l;
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid != GetCurrentProcessId() || !IsWindowVisible(hWnd)) return TRUE;
    WCHAR cls[64], title[64];
    if (!GetClassNameW(hWnd, cls, 64) || wcscmp(cls, L"Ableton Live Window Class") != 0) return TRUE;
    if (!GetWindowTextW(hWnd, title, 64) || wcscmp(title, L"Settings") != 0) return TRUE;
    c->found = hWnd;
    return FALSE;
}

static HWND FindSettingsWindow() {
    DWORD now = GetTickCount();
    if (g_settingsHwnd && IsWindow(g_settingsHwnd) && now - g_lastFind < 500) return g_settingsHwnd;
    g_lastFind = now;
    SettingsFind ctx = {nullptr};
    EnumWindows(FindSettingsProc, (LPARAM)&ctx);
    g_settingsHwnd = ctx.found;
    return g_settingsHwnd;
}

static bool IsSettingsWindow(HWND h) {
    if (!h) return false;
    HWND s = FindSettingsWindow();
    return s && (h == s || IsChild(s, h));
}

static bool EnsureShaders(ID3D11Device* dev) {
    if (dev == g_dev && g_ps) return true;
    ReleaseResources();
    g_dev = dev;
    g_dev->AddRef();
    HMODULE dc = LoadLibraryW(L"d3dcompiler_47.dll");
    D3DCompile_t compile = dc ? (D3DCompile_t)GetProcAddress(dc, "D3DCompile") : nullptr;
    if (!compile) return false;
    ID3DBlob *vsb = nullptr, *psb = nullptr;
    bool ok = SUCCEEDED(compile(kShader, sizeof(kShader) - 1, "agf", nullptr, nullptr, "vs", "vs_4_0", 0, 0, &vsb, nullptr)) &&
              SUCCEEDED(compile(kShader, sizeof(kShader) - 1, "agf", nullptr, nullptr, "ps", "ps_4_0", 0, 0, &psb, nullptr)) &&
              SUCCEEDED(dev->CreateVertexShader(vsb->GetBufferPointer(), vsb->GetBufferSize(), nullptr, &g_vs)) &&
              SUCCEEDED(dev->CreatePixelShader(psb->GetBufferPointer(), psb->GetBufferSize(), nullptr, &g_ps));
    if (vsb) vsb->Release();
    if (psb) psb->Release();
    if (!ok) return false;
    D3D11_SAMPLER_DESC sd = {};
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.MaxLOD = D3D11_FLOAT32_MAX;
    return SUCCEEDED(dev->CreateSamplerState(&sd, &g_samp));
}

static ChainCache* ChainFor(void* sc) {
    for (int i = 0; i < 8; i++) if (g_chains[i].sc == sc) return &g_chains[i];
    for (int i = 0; i < 8; i++) if (!g_chains[i].sc) { g_chains[i].sc = sc; return &g_chains[i]; }
    return nullptr;
}

// Copies Ableton's frame aside and runs the glass pass on the back buffer.
static void SettingsPrepare(IDXGISwapChain* sc) {
    DXGI_SWAP_CHAIN_DESC d = {};
    if (FAILED(sc->GetDesc(&d))) return;
    ChainCache* e = nullptr;
    EnterCriticalSection(&g_cs);
    e = ChainFor(sc);
    if (e) {
        DWORD now = GetTickCount();
        if (now - e->tick >= 500) { e->tick = now; e->isSettings = IsSettingsWindow(d.OutputWindow); }
        if (!e->isSettings) e = nullptr;
    }
    LeaveCriticalSection(&g_cs);
    if (!e) return;

    ID3D11Device* dev = nullptr;
    if (FAILED(sc->GetDevice(__uuidof(ID3D11Device), (void**)&dev))) return;
    EnterCriticalSection(&g_cs);
    if (EnsureShaders(dev)) {
        ID3D11Texture2D* bb = nullptr;
        if (SUCCEEDED(sc->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&bb))) {
            D3D11_TEXTURE2D_DESC td;
            bb->GetDesc(&td);
            if (!e->copy || e->w != td.Width || e->h != td.Height) {
                SafeRelease(e->srv); SafeRelease(e->copy);
                td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
                td.MiscFlags = 0;
                if (SUCCEEDED(dev->CreateTexture2D(&td, nullptr, &e->copy))) {
                    D3D11_SHADER_RESOURCE_VIEW_DESC vd = {};
                    vd.Format = td.Format;
                    vd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
                    vd.Texture2D.MipLevels = 1;
                    dev->CreateShaderResourceView(e->copy, &vd, &e->srv);
                }
                e->w = td.Width; e->h = td.Height;
                if (InterlockedIncrement(&g_remapLogs) <= 4)
                    FLog(L"settings remap on %ux%u", td.Width, td.Height);
            }
            if (e->copy && e->srv) {
                ID3D11DeviceContext* imm = nullptr;
                dev->GetImmediateContext(&imm);
                ID3D11RenderTargetView* rtv = nullptr;
                if (SUCCEEDED(dev->CreateRenderTargetView(bb, nullptr, &rtv))) {
                    imm->CopyResource(e->copy, bb);
                    D3D11_VIEWPORT vp = {0, 0, (float)td.Width, (float)td.Height, 0, 1};
                    imm->OMSetRenderTargets(1, &rtv, nullptr);
                    imm->RSSetViewports(1, &vp);
                    imm->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                    imm->VSSetShader(g_vs, nullptr, 0);
                    imm->PSSetShader(g_ps, nullptr, 0);
                    imm->PSSetShaderResources(0, 1, &e->srv);
                    imm->PSSetSamplers(0, 1, &g_samp);
                    imm->Draw(3, 0);
                    ID3D11ShaderResourceView* nullSrv = nullptr;
                    imm->PSSetShaderResources(0, 1, &nullSrv);
                    imm->OMSetRenderTargets(0, nullptr, nullptr);
                    SafeRelease(rtv);
                }
                imm->Release();
            }
        }
        SafeRelease(bb);
    }
    LeaveCriticalSection(&g_cs);
    dev->Release();
}

static void SettingsRestore(IDXGISwapChain* sc) {
    ID3D11Device* dev = nullptr;
    if (FAILED(sc->GetDevice(__uuidof(ID3D11Device), (void**)&dev))) return;
    EnterCriticalSection(&g_cs);
    ChainCache* e = ChainFor(sc);
    if (e && e->copy) {
        ID3D11Texture2D* bb = nullptr;
        if (SUCCEEDED(sc->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&bb))) {
            ID3D11DeviceContext* imm = nullptr;
            dev->GetImmediateContext(&imm);
            imm->CopyResource(bb, e->copy);
            imm->Release();
            bb->Release();
        }
    }
    LeaveCriticalSection(&g_cs);
    dev->Release();
}

// One frame can arrive through both slots (Present delegates to Present1 inside d3d11);
// this guard makes sure a frame is darkened exactly once.
static thread_local bool t_inPresent = false;

using Present_t = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);
static Present_t Present_orig = nullptr;
static HRESULT STDMETHODCALLTYPE Present_hook(IDXGISwapChain* sc, UINT sync, UINT flags) {
    if (!t_inPresent) {
        t_inPresent = true;
        bool real = !(flags & DXGI_PRESENT_TEST);
        if (real) SettingsPrepare(sc);
        HRESULT hr = Present_orig(sc, sync, flags);
        if (real) SettingsRestore(sc);
        t_inPresent = false;
        return hr;
    }
    return Present_orig(sc, sync, flags);
}
using Present1_t = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain1*, UINT, UINT, const DXGI_PRESENT_PARAMETERS*);
static Present1_t Present1_orig = nullptr;
static HRESULT STDMETHODCALLTYPE Present1_hook(IDXGISwapChain1* sc, UINT sync, UINT flags,
                                                const DXGI_PRESENT_PARAMETERS* p) {
    if (!t_inPresent) {
        t_inPresent = true;
        bool real = !(flags & DXGI_PRESENT_TEST);
        if (real) SettingsPrepare(sc);
        HRESULT hr = Present1_orig(sc, sync, flags, p);
        if (real) SettingsRestore(sc);
        t_inPresent = false;
        return hr;
    }
    return Present1_orig(sc, sync, flags, p);
}

static void HookPresent() {
    HMODULE d3 = LoadLibraryW(L"d3d11.dll");
    using Create_t = HRESULT(WINAPI*)(IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
                                      const D3D_FEATURE_LEVEL*, UINT, UINT, ID3D11Device**,
                                      D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);
    Create_t create = d3 ? (Create_t)GetProcAddress(d3, "D3D11CreateDevice") : nullptr;
    ID3D11Device* dev = nullptr;
    if (!create || FAILED(create(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                                 nullptr, 0, D3D11_SDK_VERSION, &dev, nullptr, nullptr))) {
        FLog(L"no d3d device");
        return;
    }
    IDXGIDevice* xd = nullptr;
    IDXGIAdapter* ad = nullptr;
    IDXGIFactory2* f = nullptr;
    IDXGISwapChain1* sc = nullptr;
    if (SUCCEEDED(dev->QueryInterface(__uuidof(IDXGIDevice), (void**)&xd)) &&
        SUCCEEDED(xd->GetAdapter(&ad)) &&
        SUCCEEDED(ad->GetParent(__uuidof(IDXGIFactory2), (void**)&f))) {
        DXGI_SWAP_CHAIN_DESC1 d = {};
        d.Width = 16; d.Height = 16;
        d.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        d.SampleDesc.Count = 1;
        d.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        d.BufferCount = 2;
        d.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        d.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;
        if (SUCCEEDED(f->CreateSwapChainForComposition(dev, &d, nullptr, &sc))) {
            void** vt = *(void***)sc;
            Wh_SetFunctionHook(vt[8], (void*)Present_hook, (void**)&Present_orig);
            Wh_SetFunctionHook(vt[22], (void*)Present1_hook, (void**)&Present1_orig);
            FLog(L"present hooks set");
        }
    }
    SafeRelease(sc); SafeRelease(f); SafeRelease(ad); SafeRelease(xd); SafeRelease(dev);
}

static BOOL CALLBACK RefreshProc(HWND hWnd, LPARAM) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == GetCurrentProcessId() && IsAbletonTop(hWnd) && IsWindowVisible(hWnd)) {
        ApplyTint(hWnd);
        if (GetMenu(hWnd)) DrawMenuBar(hWnd);
        RedrawWindow(hWnd, nullptr, nullptr, RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
    }
    return TRUE;
}

BOOL Wh_ModInit() {
    InitializeCriticalSection(&g_cs);
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    void* swca = user32 ? (void*)GetProcAddress(user32, "SetWindowCompositionAttribute") : nullptr;
    if (swca) Wh_SetFunctionHook(swca, (void*)SetWCA_hook, (void**)&SetWCA_orig);
    Wh_SetFunctionHook((void*)FillRect, (void*)FillRect_hook, (void**)&FillRect_orig);
    HookPresent();
    return TRUE;
}

void Wh_ModAfterInit() {
    EnumWindows(RefreshProc, 0);
}

void Wh_ModUninit() {
    EnterCriticalSection(&g_cs);
    ReleaseResources();
    LeaveCriticalSection(&g_cs);
    DeleteCriticalSection(&g_cs);
}
