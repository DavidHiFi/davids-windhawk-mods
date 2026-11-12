static LRESULT CALLBACK Set_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetWindow* w = g_setWin && g_setWin->hwnd == hwnd ? g_setWin.get() : nullptr;
    if (!w) return DefWindowProcW(hwnd, msg, wParam, lParam);
    if (w->nativeButtons || w->nativeTitle) {
        LRESULT r = 0;
        if (DwmDefWindowProc(hwnd, msg, wParam, lParam, &r)) return r;  // Hover and clicks on DWM's buttons.
    }
    auto dipX = [&](LPARAM l) { return (float)(short)LOWORD(l) * 96.0f / w->dpi; };
    auto dipY = [&](LPARAM l) { return (float)(short)HIWORD(l) * 96.0f / w->dpi - kSetCapH; };
    switch (msg) {
        case WM_APP_SETTINGS_RELOAD: if (!w->saving) Set_LoadFields(*w); return 0;
        case WM_APP_SETTINGS_ACTIVATE: ShowWindow(hwnd, SW_RESTORE); ForceForeground(hwnd); return 0;
        case WM_NCCALCSIZE:
            // No system title bar: keep the side and bottom frames, the client starts at the top edge.
            if (wParam && !w->render && !w->nativeTitle) {
                auto* nc = (NCCALCSIZE_PARAMS*)lParam;
                LONG top = nc->rgrc[0].top;
                LRESULT r = DefWindowProcW(hwnd, msg, wParam, lParam);
                nc->rgrc[0].top = top;
                if (IsZoomed(hwnd))
                    nc->rgrc[0].top += GetSystemMetricsForDpi(SM_CYSIZEFRAME, w->dpi) +
                                       GetSystemMetricsForDpi(SM_CXPADDEDBORDER, w->dpi);
                return r;
            }
            break;
        case WM_NCHITTEST: {
            if (w->render || w->nativeTitle) break;
            POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            ScreenToClient(hwnd, &pt);
            RECT rc;
            GetClientRect(hwnd, &rc);
            if (pt.x < 0 || pt.y < 0 || pt.x >= rc.right || pt.y >= rc.bottom) break;
            int frame = GetSystemMetricsForDpi(SM_CYSIZEFRAME, w->dpi) + GetSystemMetricsForDpi(SM_CXPADDEDBORDER, w->dpi);
            if (!IsZoomed(hwnd) && pt.y < frame)
                return pt.x < frame * 2 ? HTTOPLEFT : pt.x >= rc.right - frame * 2 ? HTTOPRIGHT : HTTOP;
            float x = pt.x * 96.0f / w->dpi, y = pt.y * 96.0f / w->dpi - kSetCapH;
            if (y < 0) return Set_CapButtonAt(*w, x, y) >= 0 ? HTCLIENT : HTCAPTION;
            return HTCLIENT;
        }
        case WM_ACTIVATE:
            w->active = LOWORD(wParam) != WA_INACTIVE;
            Set_Invalidate(*w);
            break;
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT:
        case WM_PRINTCLIENT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            if (!w->render && Set_EnsureRt(*w)) Set_Draw(*w, w->rt.get());
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_CTLCOLOREDIT: {
            HDC dc = (HDC)wParam;
            SetTextColor(dc, RefFromRgb(mocha::text));
            SetBkColor(dc, RefFromRgb(kSetBoxFill));
            return (LRESULT)w->editBrush;
        }
        case WM_SIZE:
            if (wParam != SIZE_MINIMIZED && !w->render) {
                Set_Relayout(*w);
                Set_RememberRect(*w);
                RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);  // No stale title bar after a snap.
            }
            return 0;
        case WM_MOVE:
            Set_RememberRect(*w);
            return 0;
        case WM_GETMINMAXINFO: {
            auto* mm = (MINMAXINFO*)lParam;
            RECT r{0, 0, MulDiv(760, w->dpi, 96), MulDiv(520, w->dpi, 96)};
            AdjustWindowRectExForDpi(&r, GetWindowLongW(hwnd, GWL_STYLE), FALSE, GetWindowLongW(hwnd, GWL_EXSTYLE),
                                     w->dpi);
            mm->ptMinTrackSize = {r.right - r.left, r.bottom - r.top};
            return 0;
        }
        case WM_DPICHANGED: {
            if (g_setForceDpi) return 0;
            Set_CommitEdit(*w, true);
            w->dpi = HIWORD(wParam);
            if (w->rt) w->rt->SetDpi((float)w->dpi, (float)w->dpi);
            auto* r = (RECT*)lParam;
            SetWindowPos(hwnd, nullptr, r->left, r->top, r->right - r->left, r->bottom - r->top,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            Set_Relayout(*w);
            return 0;
        }
        case WM_TIMER:
            if (wParam == kSetTimerId) {
                if (Set_Tick(*w)) Set_Invalidate(*w);
                return 0;
            }
            break;
        case WM_MOUSEMOVE: {
            if (w->saving) return 0;
#ifdef LP_TEST_HOVER  // Only the test script's moves (marked 0x8000), never a real cursor passing over.
            if (!(wParam & 0x8000)) return 0;
#endif
            float x = dipX(lParam), y = dipY(lParam);
#ifndef LP_TEST_HOVER  // The test build feeds pointer moves by message; a leave would undo them.
            if (!w->tracking && !w->render) {
#else
            if (false) {
#endif
                TRACKMOUSEEVENT t{sizeof(t), TME_LEAVE, hwnd, 0};
                TrackMouseEvent(&t);
                w->tracking = true;
            }
            w->mouseX = x;
            w->mouseY = y;
            if (w->dragRail) {
                Set_RailDragTo(*w, x - w->dragOff);
                return 0;
            }
            if (w->dragSlider >= 0) {
                Set_SliderTo(*w, w->dragSlider, x);
                return 0;
            }
            if (w->dragScroll) {
                D2D1_RECT_F th = Set_ScrollThumb(*w);
                float view = Set_ViewH(*w), thh = th.bottom - th.top, range = view - thh - 8;
                float t = range > 0 ? std::clamp((y - w->dragOff - 4) / range, 0.0f, 1.0f) : 0;
                w->scrollTarget = w->scrollY = t * std::max(0.0f, w->contentH - view);
                Set_PlaceEdit(*w);
                Set_Invalidate(*w);
                return 0;
            }
            SetHit h = Set_Hit(*w, x, y);
            int dh = h.kind == SetHit::Drop ? h.b : -1;
            if (h.kind != w->hover.kind || h.id != w->hover.id || h.a != w->hover.a || h.b != w->hover.b ||
                dh != w->dropHover) {
                w->hover = h;
                if (w->openSel >= 0) w->dropHover = dh;
                Set_Invalidate(*w);
            }
            return 0;
        }
        case WM_MOUSELEAVE: {
            POINT pointer; GetCursorPos(&pointer);
            w->tracking = false;
            w->hover = SetHit();
            if (!w->dragRail) w->mouseX = w->mouseY = -1;
            Set_Invalidate(*w);
            return 0;
        }
        case WM_SETCURSOR:
            if (LOWORD(lParam) == HTCLIENT) {
                PCWSTR cur = w->dragRail || w->hover.kind == SetHit::RailEdge ? IDC_SIZEWE
                             : Set_Clickable(w->hover)                         ? IDC_HAND
                                                                               : IDC_ARROW;
                SetCursor(LoadCursorW(nullptr, cur));
                return TRUE;
            }
            break;
        case WM_LBUTTONDOWN: {
            if (w->saving) return 0;
            if (!w->render) SetFocus(hwnd);
            w->kbd = false;
            float x = dipX(lParam), y = dipY(lParam);
            SetHit h = Set_Hit(*w, x, y);
            if (w->openSel >= 0) {  // The popup eats the click, whatever it hits.
                if (h.kind == SetHit::Drop) Set_Choose(*w, h.a, h.b);
                else Set_ClosePopup(*w);
                return 0;
            }
            Set_CommitEdit(*w, true);
            if (w->recording >= 0 && !(h.kind == SetHit::Control && h.a == w->recording)) Set_StopRecording(*w);
            w->hover = h;
            switch (h.kind) {
                case SetHit::Rail:
                    Set_GoPage(*w, h.a);
                    break;
                case SetHit::RailToggle:
                    Set_ToggleRail(*w);
                    break;
                case SetHit::RailEdge:
                    w->dragRail = true;
                    w->dragOff = x - Set_RailDock(*w).right;
                    SetCapture(hwnd);
                    Set_Invalidate(*w);
                    break;
                case SetHit::Footer:
                    Set_FooterAction(*w, h.a);
                    return 0;  // The window may be gone.
                case SetHit::Control:
                case SetHit::Clear:
                case SetHit::Chip:
                    w->focus = h.a;
                    Set_ActivateField(*w, h.a, &h);
                    break;
                case SetHit::Slider:
                    w->focus = h.a;
                    w->dragSlider = h.a;
                    SetCapture(hwnd);
                    Set_SliderTo(*w, h.a, x);
                    break;
                case SetHit::Scroll: {
                    w->dragScroll = true;
                    w->dragOff = y - Set_ScrollThumb(*w).top;
                    SetCapture(hwnd);
                    Set_Invalidate(*w);
                    break;
                }
                case SetHit::Link:
                    Set_OpenLink(w->items[h.a].url.c_str());
                    break;
                case SetHit::Caption:
                    w->capDown = h.a + 1;
                    SetCapture(hwnd);
                    Set_Invalidate(*w);
                    break;
                default:
                    break;
            }
            return 0;
        }
        case WM_LBUTTONUP:
        case WM_CAPTURECHANGED:
            if (w->capDown) {
                int b = w->capDown - 1;
                w->capDown = 0;
                if (msg == WM_LBUTTONUP) {
                    if (GetCapture() == hwnd) ReleaseCapture();
                    SetHit h = Set_Hit(*w, dipX(lParam), dipY(lParam));
                    if (h.kind == SetHit::Caption && h.a == b) {
                        if (b == 0) ShowWindow(hwnd, SW_MINIMIZE);
                        else if (b == 1) ShowWindow(hwnd, IsZoomed(hwnd) ? SW_RESTORE : SW_MAXIMIZE);
                        else PostMessageW(hwnd, WM_CLOSE, 0, 0);
                    }
                }
                Set_Invalidate(*w);
                return 0;
            }
            if (w->dragSlider >= 0 || w->dragScroll || w->dragRail) {
                w->dragSlider = -1;
                w->dragScroll = false;
                w->dragRail = false;
                if (msg == WM_LBUTTONUP && GetCapture() == hwnd) ReleaseCapture();
                Set_Invalidate(*w);
            }
            return 0;
        case WM_MOUSEWHEEL: {
            Set_CommitEdit(*w, true);
            Set_ClosePopup(*w);
            float delta = (float)GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            float maxScroll = std::max(0.0f, w->contentH - Set_ViewH(*w));
            w->scrollTarget = std::clamp(w->scrollTarget - delta * 72, 0.0f, maxScroll);
            if (!Set_Anim(*w)) w->scrollY = w->scrollTarget;
            Set_Invalidate(*w);
            return 0;
        }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            if (Set_OnKey(*w, (UINT)wParam)) return 0;
            // Without a system menu (glass title bar) Windows no longer turns Alt+F4 into a close.
            if (msg == WM_SYSKEYDOWN && wParam == VK_F4 && w->recording < 0) {
                PostMessageW(hwnd, WM_CLOSE, 0, 0);
                return 0;
            }
            break;
        case WM_CHAR:
        case WM_SYSCHAR:
            if (w->recording >= 0) return 0;
            break;
        case WM_KILLFOCUS:
            if (w->recording >= 0 && (HWND)wParam != w->edit) Set_StopRecording(*w);
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY: {
            Set_StopRecording(*w);
            if (w->timer) KillTimer(hwnd, kSetTimerId);
            if (!w->render && w->normalRect.right > w->normalRect.left) {
                const RECT& r = w->normalRect;
                SetState(StateKey(L"Settings", L"X").c_str(), r.left);
                SetState(StateKey(L"Settings", L"Y").c_str(), r.top);
                SetState(StateKey(L"Settings", L"CX").c_str(), r.right - r.left);
                SetState(StateKey(L"Settings", L"CY").c_str(), r.bottom - r.top);
            }
            if (!w->render) {
                SetState(StateKey(L"Settings", L"RailW").c_str(), (int)w->railW);
                SetState(StateKey(L"Settings", L"RailCollapsed").c_str(), w->railCollapsed ? 1 : 0);
            }
            return 0;
        }
        case WM_NCDESTROY: {
            if (w->editFont) DeleteObject(w->editFont);
            if (w->editBrush) DeleteObject(w->editBrush);
            if (w->iconSmall) DestroyIcon(w->iconSmall);
            if (w->iconBig) DestroyIcon(w->iconBig);
            if (w->owner) DestroyWindow(w->owner);
            w->destroyed = true;
            w->hwnd = nullptr;
            w->edit = nullptr;
            w->rt.reset();
            g_settingsWnd = nullptr; PostQuitMessage(0);
            g_setWin.reset();
            Set_ReleaseFactories();
            return DefWindowProcW(hwnd, msg, wParam, lParam);
        }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// Blue to mauve rounded square with a clipboard glyph, px pixels square.
static HICON Set_MakeIcon(const std::wstring& iconFamily, int px) {
    if (px <= 0 || !Set_EnsureFactories()) return nullptr;
    SetCom<IWICBitmap> bmp;
    SetCom<ID2D1RenderTarget> rt;
    if (FAILED(g_setWic->CreateBitmap(px, px, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnLoad, bmp.put())))
        return nullptr;
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96);
    if (FAILED(g_setD2d->CreateWicBitmapRenderTarget(bmp.get(), props, rt.put()))) return nullptr;
    float s = (float)px;
    SetWindow dummy;
    SetPaint p(dummy, rt.get());
    auto glyph = Set_Fmt(iconFamily, s * 0.6f, 400, false, DWRITE_TEXT_ALIGNMENT_CENTER, true);
    rt->BeginDraw();
    rt->Clear(D2D1::ColorF(0, 0));
    Set_DrawMark(p, glyph.get(), {0, 0, s, s}, 1);
    if (FAILED(rt->EndDraw())) return nullptr;
    std::vector<BYTE> pix((size_t)px * px * 4);
    if (FAILED(bmp->CopyPixels(nullptr, px * 4, (UINT)pix.size(), pix.data()))) return nullptr;
    for (size_t i = 0; i < pix.size(); i += 4) {  // Icons want straight alpha.
        BYTE a = pix[i + 3];
        if (a && a < 255)
            for (int c = 0; c < 3; c++) pix[i + c] = (BYTE)std::min(255, pix[i + c] * 255 / a);
    }
    BITMAPV5HEADER bi{};
    bi.bV5Size = sizeof(bi);
    bi.bV5Width = px;
    bi.bV5Height = -px;
    bi.bV5Planes = 1;
    bi.bV5BitCount = 32;
    bi.bV5Compression = BI_BITFIELDS;
    bi.bV5RedMask = 0x00FF0000;
    bi.bV5GreenMask = 0x0000FF00;
    bi.bV5BlueMask = 0x000000FF;
    bi.bV5AlphaMask = 0xFF000000;
    void* bits = nullptr;
    HDC dc = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(dc, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, dc);
    if (!color || !bits) return nullptr;
    memcpy(bits, pix.data(), pix.size());
    std::vector<BYTE> maskBits((size_t)((px + 15) / 16) * 2 * px, 0);
    HBITMAP mask = CreateBitmap(px, px, 1, 1, maskBits.data());
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    return icon;
}

// The class belongs to this DLL and goes away with the settings thread. Registered under
// Explorer's handle it outlived a mod update, and the next window ran the unloaded code.
static void Set_RegisterClass() {
    UnregisterClassW(kSettingsClass, GetModuleHandleW(nullptr));  // left by builds before 2.3.0
    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = Set_WndProc;
    wc.hInstance = (HINSTANCE)&__ImageBase;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kSettingsClass;
    RegisterClassExW(&wc);
}

// Builds the window, hidden. render: an off-screen copy that is never shown (tests and PNG output).
static bool Set_Create(bool render) {
    if (!Set_EnsureFactories()) return false;
    Set_RegisterClass();
    auto w = std::make_shared<SetWindow>();
    w->render = render;
    w->editBrush = CreateSolidBrush(RefFromRgb(kSetBoxFill));
    g_setWin = w;
    if (render) {
        // An owned window gets no taskbar button.
        w->owner = CreateWindowExW(WS_EX_TOOLWINDOW, L"STATIC", L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr,
                                   GetModuleHandleW(nullptr), nullptr);
    }
    const int offX = GetSystemMetrics(SM_XVIRTUALSCREEN) - 6000, offY = GetSystemMetrics(SM_YVIRTUALSCREEN);
    // Off: the window draws its own title bar and buttons. On: Windows draws both.
    w->nativeTitle = !render && Wh_GetIntSetting(L"nativeSettingsTitleBar") != 0;
    w->glass = !render && Wh_GetIntSetting(L"settingsGlass") != 0;
    kSetCapH = w->nativeTitle ? 0.0f : 40.0f;
    const DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Launchpad settings", style,
                                render ? offX : CW_USEDEFAULT, render ? offY : CW_USEDEFAULT, 800, 600, w->owner,
                                nullptr, (HINSTANCE)&__ImageBase, nullptr);
    if (!hwnd) {
        g_setWin.reset();
        return false;
    }
    w->hwnd = hwnd;
    w->dpi = g_setForceDpi ? g_setForceDpi : GetDpiForWindow(hwnd);
    ApplyDarkWindow(hwnd);
    COLORREF caption = RefFromRgb(mocha::crust), captionText = RefFromRgb(mocha::text);
    DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &caption, sizeof(caption));
    DwmSetWindowAttribute(hwnd, 36 /* DWMWA_TEXT_COLOR */, &captionText, sizeof(captionText));
    Set_MakeFormats(*w);
    Set_LoadFields(*w);
    if (!render) {
        w->railW = std::clamp((float)GetState(StateKey(L"Settings", L"RailW").c_str(), (int)kSetRailDef), kSetRailMin, kSetRailMax);
        w->railCollapsed = GetState(StateKey(L"Settings", L"RailCollapsed").c_str(), 0) != 0;
        w->railCur = w->railCollapsed ? kSetRailMini : w->railW;
    }
    if (!render) {
        w->iconSmall = Set_MakeIcon(w->iconFamily, GetSystemMetricsForDpi(SM_CXSMICON, w->dpi));
        w->iconBig = Set_MakeIcon(w->iconFamily, GetSystemMetricsForDpi(SM_CXICON, w->dpi));
        if (w->iconSmall) SendMessageW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)w->iconSmall);
        if (w->iconBig) SendMessageW(hwnd, WM_SETICON, ICON_BIG, (LPARAM)w->iconBig);
        if (w->glass) {
            // Acrylic as one sheet over the whole window, the same material Seamless Flyouts
            // gives the Launchpad settings window in Explorer: the accent acrylic with an 85%
            // Mocha base tint, under the page's own crust tint. The system backdrop
            // (DWMSBT_TRANSIENTWINDOW) went light grey over bright windows and turned to a flat
            // grey slab when the window lost focus; the accent acrylic stays the same.
            int backdrop = 1;  // DWMSBT_NONE
            DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
            DWM_BLURBEHIND bb{};
            bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
            bb.fEnable = TRUE;
            bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
            DwmEnableBlurBehindWindow(hwnd, &bb);
            if (bb.hRgnBlur) DeleteObject(bb.hRgnBlur);
            struct SetAccentPolicy { int state, flags, abgr, animation; };
            struct SetCompositionData { DWORD attribute; void* data; SIZE_T size; };
            using SetComposition_t = BOOL(WINAPI*)(HWND, SetCompositionData*);
            if (auto setComposition = (SetComposition_t)(void*)GetProcAddress(
                    GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute")) {
                SetAccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, (int)0x012E1E1E, 0};  // same as the launcher grid
                SetCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
                setComposition(hwnd, &data);
            }
            MARGINS margins{-1, -1, -1, -1};
            DwmExtendFrameIntoClientArea(hwnd, &margins);
            COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE
            DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
        } else if (w->nativeButtons) {
            // Solid window: DWM draws its buttons only where the frame reaches, so extend it
            // over the title bar strip.
            MARGINS margins{0, 0, MulDiv((int)kSetCapH, w->dpi, 96), 0};
            DwmExtendFrameIntoClientArea(hwnd, &margins);
        }
        // With the frame extended, DWM draws its own minimize, maximize and close buttons in the
        // corner. "Windows buttons" keeps them (Set_WndProc passes their hover and clicks to
        // DwmDefWindowProc); "Built-in buttons" drops the system menu so DWM draws none and the
        // window draws its own. Minimize, maximize and close still work from the taskbar.
        if (!w->nativeTitle && !w->nativeButtons)
            SetWindowLongPtrW(hwnd, GWL_STYLE, GetWindowLongPtrW(hwnd, GWL_STYLE) & ~WS_SYSMENU);
        // The first WM_NCCALCSIZE ran before w->hwnd was set; drop the system title bar now.
        SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }

    auto outer = [&](float cwDip, float chDip, SIZE& size) {
        RECT r{0, 0, MulDiv((int)cwDip, w->dpi, 96), MulDiv((int)chDip, w->dpi, 96)};
        AdjustWindowRectExForDpi(&r, style, FALSE, 0, w->dpi);
        size = {r.right - r.left, r.bottom - r.top};
    };
    SIZE size;
    if (render) {
        w->cw = 980;
        w->ch = 700;
        outer(w->cw, w->ch, size);
        SetWindowPos(hwnd, nullptr, offX, offY, size.cx, size.cy, SWP_NOZORDER | SWP_NOACTIVATE);
        Set_BuildPage(*w);
        return true;
    }
    outer(980, 720, size);
    POINT cursor;
    GetCursorPos(&cursor);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromPoint(cursor, MONITOR_DEFAULTTONEAREST), &mi);
    const RECT& work = mi.rcWork;
    int width = std::min((int)size.cx, (int)(work.right - work.left) * 9 / 10);
    int height = std::min((int)size.cy, (int)(work.bottom - work.top) * 9 / 10);
    RECT r{(work.left + work.right - width) / 2, (work.top + work.bottom - height) / 2, 0, 0};
    r.right = r.left + width;
    r.bottom = r.top + height;
    int cx = GetState(StateKey(L"Settings", L"CX").c_str(), 0);
    int cy = GetState(StateKey(L"Settings", L"CY").c_str(), 0);
    if (cx > 0 && cy > 0) {
        RECT saved{GetState(StateKey(L"Settings", L"X").c_str(), 0), GetState(StateKey(L"Settings", L"Y").c_str(), 0),
                   0, 0};
        saved.right = saved.left + cx;
        saved.bottom = saved.top + cy;
        if (MonitorFromRect(&saved, MONITOR_DEFAULTTONULL)) r = saved;
    }
    SetWindowPos(hwnd, nullptr, r.left, r.top, r.right - r.left, r.bottom - r.top, SWP_NOZORDER | SWP_NOACTIVATE);
    // The monitor it landed on may have a different scale.
    UINT dpi = GetDpiForWindow(hwnd);
    if (!g_setForceDpi && dpi != w->dpi) w->dpi = dpi;
    Set_Relayout(*w);
    w->pageT = Set_Anim(*w) ? 0.0f : 1.0f;
    w->timer = SetTimer(hwnd, kSetTimerId, 15, nullptr) != 0;
    return true;
}

void Settings_Open() {
    if (g_setWin && g_setWin->hwnd && !g_setWin->render) {
        HWND hwnd = g_setWin->hwnd;
        if (IsIconic(hwnd)) ShowWindow(hwnd, SW_RESTORE);
        SetForegroundWindow(hwnd);
        return;
    }
    if (g_setWin) Settings_Close();
    if (!Set_Create(false)) return;
    HWND hwnd = g_setWin->hwnd;
    ShowWindow(hwnd, SW_SHOW);
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}

void Settings_Close() {
    if (g_setWin && g_setWin->hwnd) DestroyWindow(g_setWin->hwnd);
    g_setWin.reset();
}

bool Settings_IsOpen() { return g_setWin && g_setWin->hwnd && !g_setWin->render; }


DWORD WINAPI SettingsThread(void*) {
 SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
 CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
 Settings_Open();
 if (g_setWin) g_settingsWnd=g_setWin->hwnd;
 MSG msg;
 while (g_settingsWnd && GetMessageW(&msg,nullptr,0,0)>0) { TranslateMessage(&msg); DispatchMessageW(&msg); }
 Settings_Close(); UnregisterClassW(kSettingsClass,(HINSTANCE)&__ImageBase); Set_ReleaseFactories(); CoUninitialize(); return 0;
}
void OpenSettingsWindow() {
 if (HWND hwnd=g_settingsWnd) { PostMessageW(hwnd,WM_APP_SETTINGS_ACTIVATE,0,0); return; }
 if(g_settingsThread) { if(WaitForSingleObject(g_settingsThread,0)==WAIT_TIMEOUT) return; CloseHandle(g_settingsThread); }
 g_settingsStop=false; g_settingsThread=CreateThread(nullptr,0,SettingsThread,nullptr,0,nullptr);
}
void CloseSettingsWindow() {
 g_settingsStop=true;
 if(HWND hwnd=g_settingsWnd) PostMessageW(hwnd,WM_CLOSE,0,0);
 if(g_settingsThread) { WaitForSingleObject(g_settingsThread,15000); CloseHandle(g_settingsThread); g_settingsThread=nullptr; }
}

void EnsureVisible(int index) {
    if (index < 0) {
        return;
    }
    if (g_openFolder) {
        FolderLayout F = GetFolderLayout();
        int row = index / F.columns;
        g_folderRow = std::clamp(g_folderRow, row - F.visibleRows + 1, row);
        return;
    }
    const Layout& L = g_layout;
    if (g_settings.pages) {
        g_scrollTarget = (index / L.perPage) * (float)L.width;
        return;
    }
    int row = index / L.columns;
    int firstRow = (int)std::lround(g_scrollTarget / L.cellHeight);
    if (row < firstRow) {
        g_scrollTarget = row * L.cellHeight;
    } else if (row >= firstRow + L.visibleRows) {
        g_scrollTarget = (row - L.visibleRows + 1) * L.cellHeight;
    }
    g_scrollTarget = std::clamp(g_scrollTarget, 0.0f, MaxScroll());
}

// With pages, any number of rows flips one page that way.
void ScrollRows(int rows) {
    if (g_settings.pages) {
        float width = (float)g_layout.width;
        float target =
            (std::lround(g_scrollTarget / width) + (rows > 0 ? 1 : -1)) * width;
        g_scrollTarget = std::clamp(target, 0.0f, MaxScroll());
        StartFrames();
        return;
    }
    float cell = g_layout.cellHeight;
    float target = (std::lround(g_scrollTarget / cell) + rows) * cell;
    g_scrollTarget = std::clamp(target, 0.0f, MaxScroll());
    StartFrames();
}

////////////////////////////////////////////////////////////////////////////////
// Folders, dragging and the right-click menus

// After the arrangement changed.
void Refresh() {
    UpdateFilter();
    ComputeLayout();
    Render();
}

int IndexOf(const Tiles& tiles, const Tile& tile) {
    for (int i = 0; i < (int)tiles.size(); i++) {
        if (tiles[i].app == tile.app && tiles[i].folder == tile.folder) {
            return i;
        }
    }
    return -1;
}

// After a change that may have left the open folder with one app or none.
void DropGoneFolder() {
    TidyTiles();
    if (g_openFolder && IndexOf(g_tiles, {nullptr, g_openFolder}) < 0) {
        g_openFolder = nullptr;
    }
    g_hover = g_selected = g_pressed = -1;
}

void OpenFolder(std::shared_ptr<Folder> folder) {
    g_folderRenaming = false;
    g_folderTitleHover = false;
    g_openFolder = std::move(folder);
    g_closingFolder = nullptr;
    g_folderAnim = Animate() ? 0.0f : 1.0f;
    if (g_folderAnim < 1) {
        StartFrames();
    }
    g_folderRow = 0;
    g_hover = g_selected = g_pressed = -1;
    g_searchDrag = false;
    g_hist[1] = {};  // Fresh history per folder.
    SetCaret(EditText().size(), false);  // At the end of the name.
    Render();
}

void CloseFolder() {
    if (!g_openFolder) {
        return;
    }
    if (Animate()) {
        g_closingFolder = g_openFolder;
        StartFrames();
    }
    g_folderRenaming = false;
    g_folderTitleHover = false;
    g_openFolder = nullptr;
    g_hover = g_selected = g_pressed = -1;
    g_searchDrag = false;
    SetCaret(g_query.size(), false);
    SaveTiles();  // Keeps a new name.
    Refresh();
}

void ActivateItem(int index) {
    const Tiles& items = Items();
    if (index < 0 || index >= (int)items.size()) {
        return;
    }
    if (items[index].folder) {
        OpenFolder(items[index].folder);
    } else {
        LaunchTarget(items[index].app->target);
    }
}

// Where the click doesn't count as one on empty space.
bool ClickKeepsOpen(int x, int y) {
    return g_openFolder ? InRect(GetFolderLayout().panel, (float)x, (float)y)
                        : InRect(g_layout.search, (float)x, (float)y) ||
                              PowerAt(x, y) >= 0;
}

// The words both names start with ("Microsoft Edge" and "Microsoft Teams"
// give "Microsoft"), or "Folder".
std::wstring FolderName(const std::wstring& a, const std::wstring& b) {
    size_t same = 0;
    for (size_t i = 0;; i++) {
        bool endA = i == a.size() || a[i] == L' ';
        bool endB = i == b.size() || b[i] == L' ';
        if (endA && endB) {
            same = i;
            if (i == a.size() || i == b.size()) {
                break;
            }
            continue;
        }
        if (endA || endB || towlower(a[i]) != towlower(b[i])) {
            break;
        }
    }
    return same ? a.substr(0, same) : L"Folder";
}

void StartDrag() {
    const Tiles& items = Items();
    int i = g_pressed;
    g_drag.pending = false;
    if (i < 0 || i >= (int)items.size() || !g_query.empty()) {
        return;
    }
    Cell c = ItemCell(i);
    g_drag.active = true;
    g_drag.tile = items[i];
    g_drag.at = g_drag.start;
    g_drag.grab = D2D1::Point2F(g_drag.start.x - c.icon.left,
                                g_drag.start.y - c.icon.top);
    g_drag.target = g_drag.slot = -1;
    g_drag.edge = 0;
    g_drag.inPanel = g_openFolder != nullptr;
    g_drag.backup = ArrangementLines();
    g_hover = g_selected = g_pressed = -1;
    StartFrames();
}

void DragMove(int x, int y) {
    const Layout& L = g_layout;
    double now = Now();
    g_drag.at = {x, y};
    if (g_openFolder) {
        if (InRect(GetFolderLayout().panel, (float)x, (float)y)) {
            g_drag.inPanel = true;
        } else if (g_drag.inPanel) {
            // Out of the folder, into the grid right after it.
            Tiles& apps = g_openFolder->apps;
            int i = IndexOf(apps, g_drag.tile);
            if (i >= 0) {
                apps.erase(apps.begin() + i);
                int f = IndexOf(g_tiles, {nullptr, g_openFolder});
                g_tiles.insert(g_tiles.begin() + (f + 1), g_drag.tile);
            }
            g_openFolder = nullptr;
            UpdateFilter();
            ComputeLayout();
        }
    }

    // Over the middle of another icon: dropping there makes or fills a folder.
    // The rest of that icon moves nothing, so reaching the middle doesn't
    // shuffle the icons first.
    int target = -1;
    bool overIcon = false;
    if (!g_openFolder && g_drag.tile.app) {
        int i = ItemAt(x, y);
        if (i >= 0 && !IsDragged(g_visible[i])) {
            D2D1_RECT_F r = CellAt(i).icon;
            overIcon = InRect(r, (float)x, (float)y);
            float in = (r.right - r.left) * 0.2f;
            if (InRect(D2D1::RectF(r.left + in, r.top + in, r.right - in,
                                   r.bottom - in),
                       (float)x, (float)y)) {
                target = i;
            }
        }
    }
    if (target != g_drag.target) {
        g_drag.target = target;
        g_drag.targetTime = now;
    }
    int slot = overIcon ? -1 : SlotAt(x, y);
    if (slot != g_drag.slot) {
        g_drag.slot = slot;
        g_drag.slotTime = now;
    }

    int edge = 0;
    if (!g_openFolder) {
        if (g_settings.pages) {
            float zone =
                std::max(36 * L.scale, std::min(L.gridLeft, L.width * 0.06f));
            edge = x < zone ? -1 : x >= L.width - zone ? 1 : 0;
        } else {
            edge = y < L.viewTop ? -1 : y >= L.viewBottom ? 1 : 0;
        }
    }
    if (edge != g_drag.edge) {
        g_drag.edge = edge;
        g_drag.edgeTime = now;
    }
}

// Each frame of a drag: what happens when the pointer rests somewhere.
void DragTick() {
    // The page or rows under a still pointer move while scrolling.
    DragMove(g_drag.at.x, g_drag.at.y);
    double now = Now();
    if (g_drag.edge &&
        now - g_drag.edgeTime >= (g_settings.pages ? 0.6 : 0.3)) {
        g_drag.edgeTime = now;
        ScrollRows(g_drag.edge);
    }

    int t = g_drag.target;
    if (t >= 0 && t < (int)g_visible.size() && g_visible[t].folder &&
        now - g_drag.targetTime >= 0.7) {
        // Resting on a folder opens it, to place the app inside.
        std::shared_ptr<Folder> folder = g_visible[t].folder;
        int i = IndexOf(g_tiles, g_drag.tile);
        if (i >= 0) {
            g_tiles.erase(g_tiles.begin() + i);
        }
        folder->apps.push_back(g_drag.tile);
        UpdateFilter();
        ComputeLayout();
        OpenFolder(folder);
        FolderLayout F = GetFolderLayout();
        g_folderRow = F.rows - F.visibleRows;
        g_drag.target = g_drag.slot = -1;
        g_drag.edge = 0;
        g_drag.inPanel = false;
        return;
    }

    if (g_drag.slot >= 0 && now - g_drag.slotTime >= 0.2) {
        Tiles& tiles = g_openFolder ? g_openFolder->apps : g_tiles;
        int from = IndexOf(tiles, g_drag.tile);
        int to = std::min(g_drag.slot, (int)tiles.size() - 1);
        if (from >= 0 && to != from) {
            CaptureTileMotion();
            Tile tile = tiles[from];
            tiles.erase(tiles.begin() + from);
            tiles.insert(tiles.begin() + to, tile);
            if (!g_openFolder) {
                UpdateFilter();
                ComputeLayout();
            }
        }
    }
}

// drop: keep the new place (and make or fill a folder); otherwise everything
// goes back.
void EndDrag(bool drop) {
    g_drag.pending = false;
    if (!g_drag.active) {
        return;
    }
    CaptureTileMotion();
    if (drop) {
        for (auto& motion : g_tileMotion) {
            if (motion.key == MotionKey(g_drag.tile)) {
                float size = std::round(g_layout.icon * 1.06f);
                motion.from = {g_drag.at.x-g_drag.grab.x-(size-g_layout.icon)/2,
                               g_drag.at.y-g_drag.grab.y-(size-g_layout.icon)/2};
            }
        }
    }
    g_drag.active = false;
    Tile tile = std::move(g_drag.tile);
    g_drag.tile = {};
    int target = g_drag.target;
    g_drag.target = g_drag.slot = -1;
    g_drag.edge = 0;
    if (!drop) {
        g_openFolder = nullptr;
        ArrangeTiles(g_drag.backup);
    } else if (target >= 0 && target < (int)g_tiles.size()) {
        Tile onto = g_tiles[target];
        int from = IndexOf(g_tiles, tile);
        if (onto.folder) {
            onto.folder->apps.push_back(tile);
        } else {
            auto folder = std::make_shared<Folder>();
            folder->name = FolderName(onto.app->name, tile.app->name);
            folder->apps = {onto, tile};
            g_tiles[target] = {nullptr, folder};
        }
        if (from >= 0) {
            g_tiles.erase(g_tiles.begin() + from);
        }
    }
    g_drag.backup.clear();
    DropGoneFolder();
    if (drop) {
        SaveTiles();
    }
    Refresh();
}

// What an app's menu needs.
struct AppPaths {
    std::wstring file;      // The program it starts, when that's a file.
    std::wstring folder;    // A Store app's install folder.
    std::wstring shortcut;  // Its shortcut in the Start menu or on the desktop.
};

std::wstring ItemString(IShellItem2* item, PCWSTR property) {
    PROPERTYKEY key;
    PWSTR value = nullptr;
    std::wstring result;
    if (SUCCEEDED(PSGetPropertyKeyFromName(property, &key)) &&
        SUCCEEDED(item->GetString(key, &value))) {
        result = value;
        CoTaskMemFree(value);
    }
    return result;
}

bool FileExists(const std::wstring& path) {
    return !path.empty() &&
           GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES;
}

// Start lists the shortcuts in these two folders and their subfolders. The
// one named like the app, or else the one that starts the same file.
std::wstring FindStartShortcut(const std::wstring& name,
                               const std::wstring& file) {
    std::vector<std::wstring> dirs, links;
    for (REFKNOWNFOLDERID id : {FOLDERID_Programs, FOLDERID_CommonPrograms}) {
        PWSTR root = nullptr;
        if (SUCCEEDED(SHGetKnownFolderPath(id, 0, nullptr, &root))) {
            dirs.push_back(root);
        }
        CoTaskMemFree(root);
    }
    while (!dirs.empty() && links.size() < 5000) {
        std::wstring dir = std::move(dirs.back());
        dirs.pop_back();
        WIN32_FIND_DATAW fd;
        HANDLE find = FindFirstFileW((dir + L"\\*").c_str(), &fd);
        if (find == INVALID_HANDLE_VALUE) {
            continue;
        }
        do {
            std::wstring path = dir + L"\\" + fd.cFileName;
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (fd.cFileName[0] != L'.' &&
                    !(fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)) {
                    dirs.push_back(path);
                }
            } else if (EndsWith(ToLower(path), L".lnk")) {
                links.push_back(path);
            }
        } while (FindNextFileW(find, &fd));
        FindClose(find);
    }

    std::wstring wanted = L"\\" + ToLower(name) + L".lnk";
    for (const auto& link : links) {
        if (EndsWith(ToLower(link), wanted)) {
            return link;
        }
    }
    ComPtr<IShellLinkW> shellLink;
    ComPtr<IPersistFile> persist;
    if (file.empty() ||
        FAILED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER,
                                IID_PPV_ARGS(&shellLink))) ||
        FAILED(shellLink.As(&persist))) {
        return {};
    }
    std::wstring lowerFile = ToLower(file);
    for (const auto& link : links) {
        WCHAR target[MAX_PATH];
        if (SUCCEEDED(persist->Load(link.c_str(), STGM_READ)) &&
            shellLink->GetPath(target, ARRAYSIZE(target), nullptr, 0) == S_OK &&
            ToLower(target) == lowerFile) {
            return link;
        }
    }
    return {};
}

AppPaths GetAppPaths(const App& app) {
    AppPaths paths;
    std::wstring lower = ToLower(app.target);
    bool fromAppsFolder = lower.rfind(ToLower(kAppsFolder), 0) == 0;
    ComPtr<IShellItem2> item;
    if (SUCCEEDED(SHCreateItemFromParsingName(app.target.c_str(), nullptr,
                                              IID_PPV_ARGS(&item)))) {
        paths.file = ItemString(item.Get(), L"System.Link.TargetParsingPath");
        paths.folder =
            ItemString(item.Get(), L"System.AppUserModel.PackageInstallPath");
    }
    if (!fromAppsFolder) {
        if (EndsWith(lower, L".lnk")) {
            paths.shortcut = app.target;
        } else if (paths.file.empty()) {
            paths.file = app.target;
        }
    }
    // Control Panel and the like point to "::{...}", not a file.
    if (paths.file.rfind(L"::", 0) == 0 || !FileExists(paths.file)) {
        paths.file.clear();
    }
    if (paths.shortcut.empty() && fromAppsFolder && paths.folder.empty()) {
        paths.shortcut = FindStartShortcut(app.name, paths.file);
    }
    return paths;
}

void ShowInFolder(const std::wstring& path) {
    PIDLIST_ABSOLUTE pidl = nullptr;
    if (SUCCEEDED(SHParseDisplayName(path.c_str(), nullptr, &pidl, 0,
                                     nullptr))) {
        SHOpenFolderAndSelectItems(pidl, 0, nullptr, 0);
        CoTaskMemFree(pidl);
    }
}

bool PickIconFile(HWND hwnd, std::wstring& path) {
    WCHAR file[MAX_PATH] = L"";
    OPENFILENAMEW ofn{sizeof(ofn)};
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter =
        L"Pictures and icons\0*.ico;*.png;*.jpg;*.jpeg;*.bmp;*.gif;*.exe\0"
        L"All files\0*.*\0";
    ofn.lpstrFile = file;
    ofn.nMaxFile = ARRAYSIZE(file);
    ofn.lpstrTitle = L"Choose a picture for the icon";
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST |
                OFN_NOCHANGEDIR;
    g_modal = true;
    BOOL ok = GetOpenFileNameW(&ofn);
    g_modal = false;
    if (g_shown && !g_closing) {
        ForceForeground(hwnd);
    }
    if (ok) {
        path = file;
    }
    return ok;
}

// Takes the app off the grid: removed, or unpinned when only pinned apps show.
void RemoveApp(const std::shared_ptr<App>& app) {
    if (PinnedOnly()) {
        g_pins.erase(AppKey(*app));
        SavePins();
    } else {
        g_hidden.insert(AppKey(*app));
    }
    auto drop = [&](Tiles& tiles) {
        tiles.erase(std::remove_if(tiles.begin(), tiles.end(),
                                   [&](const Tile& t) { return t.app == app; }),
                    tiles.end());
    };
    drop(g_tiles);
    for (auto& tile : g_tiles) {
        if (tile.folder) {
            drop(tile.folder->apps);
        }
    }
    DropGoneFolder();
    SaveTiles();
    Refresh();
}

void TakeOutOfFolder(const Tile& tile) {
    if (!g_openFolder) {
        return;
    }
    Tiles& apps = g_openFolder->apps;
    int i = IndexOf(apps, tile);
    if (i < 0) {
        return;
    }
    apps.erase(apps.begin() + i);
    int f = IndexOf(g_tiles, {nullptr, g_openFolder});
    g_tiles.insert(g_tiles.begin() + (f + 1), tile);
    DropGoneFolder();
    SaveTiles();
    Refresh();
}

void Ungroup(const std::shared_ptr<Folder>& folder) {
    int f = IndexOf(g_tiles, {nullptr, folder});
    if (f < 0) {
        return;
    }
    Tiles apps = folder->apps;
    g_tiles.erase(g_tiles.begin() + f);
    g_tiles.insert(g_tiles.begin() + f, apps.begin(), apps.end());
    DropGoneFolder();
    SaveTiles();
    Refresh();
}

// An "&" in a menu would underline the next letter.
std::wstring MenuText(const std::wstring& text) {
    std::wstring out;
    for (WCHAR c : text) {
        if (c == L'&') {
            out += L'&';
        }
        out += c;
    }
    return out;
}

// Store apps and shell-resolved exes live behind an AppsFolder target; their
// elevation goes through a temporary .lnk, never the raw target.
bool IsPackagedTarget(const std::wstring& target) {
    return ToLower(target).rfind(ToLower(kAppsFolder), 0) == 0;
}

void ShowTileMenu(HWND hwnd, int index, POINT pt) {
    enum {
        kOpen = 1,
        kRunAs,
        kFileLocation,
        kShortcutLocation,
        kChangeIcon,
        kRestoreIcon,
        kOutOfFolder,
        kRemove,
        kProperties,
        kUngroup,
        kPin,
    };
    Tile tile = Items()[index];
    g_selected = index;
    Render();
    HMENU menu = CreatePopupMenu();
    AppPaths paths;
    std::wstring key;
    if (tile.folder) {
        AppendMenuW(menu, MF_STRING, kOpen, L"Open");
        AppendMenuW(menu, MF_STRING, kUngroup, L"Take the apps out");
    } else {
        paths = GetAppPaths(*tile.app);
        key = AppKey(*tile.app);
        AppendMenuW(menu, MF_STRING, kOpen, L"Open");
        // Anything with a launchable file can be elevated: a classic .exe,
        // any Start-menu shortcut, or a packaged app through a temporary
        // .lnk aimed at its AppsFolder target.
        if (!paths.shortcut.empty() || !paths.folder.empty() ||
            IsPackagedTarget(tile.app->target) ||
            (!paths.file.empty() && EndsWith(ToLower(paths.file), L".exe"))) {
            AppendMenuW(menu, MF_STRING, kRunAs, L"Run as administrator");
        }
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(menu,
                    MF_STRING | (paths.file.empty() && paths.folder.empty()
                                     ? MF_GRAYED
                                     : 0),
                    kFileLocation, L"Open file location");
        AppendMenuW(menu, MF_STRING | (paths.shortcut.empty() ? MF_GRAYED : 0),
                    kShortcutLocation, L"Open shortcut location");
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(menu, MF_STRING, kChangeIcon, L"Change icon\u2026");
        if (g_customIcons.count(key)) {
            AppendMenuW(menu, MF_STRING, kRestoreIcon,
                        L"Restore original icon");
        }
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        if (g_openFolder) {
            AppendMenuW(menu, MF_STRING, kOutOfFolder, L"Take out of folder");
        }
        if (!PinnedOnly()) {
            AppendMenuW(menu, MF_STRING, kRemove, L"Remove from this grid");
        } else if (g_pins.count(key)) {
            AppendMenuW(menu, MF_STRING, kRemove, L"Unpin from this grid");
        } else {
            AppendMenuW(menu, MF_STRING, kPin, L"Pin to this grid");
        }
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(menu,
                    MF_STRING | (paths.shortcut.empty() && paths.file.empty()
                                     ? MF_GRAYED
                                     : 0),
                    kProperties, L"Properties");
    }
    SetMenuDefaultItem(menu, kOpen, FALSE);
    g_modal = true;
    int command = TrackPopupMenuEx(
        menu, TPM_RETURNCMD | TPM_RIGHTBUTTON | TPM_NONOTIFY, pt.x, pt.y, hwnd,
        nullptr);
    g_modal = false;
    DestroyMenu(menu);

    int size = g_appsKey & 0xFFFF;
    const std::wstring& linkOrFile =
        paths.shortcut.empty() ? paths.file : paths.shortcut;
    switch (command) {
        case kOpen:
            if (tile.folder) {
                OpenFolder(tile.folder);
            } else {
                LaunchTarget(tile.app->target);
            }
            break;
        case kUngroup:
            Ungroup(tile.folder);
            break;
        case kRunAs:
            // A Store app's .lnk brokers an elevated launch; the raw
            // AppsFolder target — with or without a real exe inside it — is
            // a silent no-op. Packaged apps go through the temporary .lnk.
            if (IsPackagedTarget(tile.app->target)) {
                ElevateViaTempLnk(tile.app->target);
            } else {
                LaunchTarget(linkOrFile, L"runas");
            }
            break;
        case kFileLocation:
            if (paths.file.empty()) {
                LaunchTarget(paths.folder);
            } else {
                Close();
                ShowInFolder(paths.file);
            }
            break;
        case kShortcutLocation:
            Close();
            ShowInFolder(paths.shortcut);
            break;
        case kChangeIcon: {
            std::wstring picture;
            if (PickIconFile(hwnd, picture)) {
                if (LoadIconFile(picture, size, *tile.app)) {
                    g_customIcons[key] = picture;
                    SaveCustomIcons();
                } else {
                    Wh_Log(L"No picture in %s", picture.c_str());
                }
            }
            Render();
            break;
        }
        case kRestoreIcon:
            g_customIcons.erase(key);
            SaveCustomIcons();
            ReloadAppIcon(size, *tile.app);
            Render();
            break;
        case kOutOfFolder:
            TakeOutOfFolder(tile);
            break;
        case kRemove:
            RemoveApp(tile.app);
            break;
        case kPin:
            g_pins.insert(key);
            SavePins();
            g_hidden.erase(key);
            g_tiles.push_back(tile);  // At the end of the grid.
            SaveTiles();
            Refresh();
            break;
        case kProperties:
            Close();
            SHObjectProperties(nullptr, SHOP_FILEPATH, linkOrFile.c_str(),
                               nullptr);
            break;
    }
}

// The menu key: the menu of the selected icon.
void ShowSelectedMenu() {
    if (g_drag.active || g_selected < 0 || g_selected >= (int)Items().size()) {
        return;
    }
    Cell c = ItemCell(g_selected);
    POINT pt{(LONG)c.icon.left, (LONG)c.icon.bottom};
    ClientToScreen(g_wnd, &pt);
    ShowTileMenu(g_wnd, g_selected, pt);
}

// The "..." menu, below the button, or at the pointer after a right-click on
// empty space.
void ShowOptionsMenu(HWND hwnd, POINT pt, bool underButton) {
    enum { kOpenSettings = 1, kRestoreAll, kSort, kRestoreFirst = 100 };
    // Removed apps that are still installed, A to Z like the list.
    std::vector<std::shared_ptr<App>> removed;
    for (const auto& app : g_apps) {
        if (g_hidden.count(AppKey(*app)) && removed.size() < 500) {
            removed.push_back(app);
        }
    }
    HMENU menu = CreatePopupMenu();
    AppendMenuW(menu, MF_STRING, kOpenSettings, L"Open settings");
    HMENU sub = CreatePopupMenu();
    for (int i = 0; i < (int)removed.size(); i++) {
        AppendMenuW(sub, MF_STRING, kRestoreFirst + i,
                    MenuText(removed[i]->name).c_str());
    }
    if (!removed.empty()) {
        AppendMenuW(sub, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(sub, MF_STRING, kRestoreAll, L"Bring them all back");
    }
    AppendMenuW(menu, MF_POPUP | (removed.empty() ? MF_GRAYED : 0),
                (UINT_PTR)sub, L"Bring back a removed app");
    AppendMenuW(menu,
                MF_STRING | (!g_appsLoaded ? MF_GRAYED : 0),
                kSort, L"Sort A to Z");
    UINT flags = TPM_RETURNCMD | TPM_RIGHTBUTTON | TPM_NONOTIFY |
                 (underButton ? TPM_RIGHTALIGN | TPM_TOPALIGN : 0);
    g_modal = true;
    int command = TrackPopupMenuEx(menu, flags, pt.x, pt.y, hwnd, nullptr);
    g_modal = false;
    DestroyMenu(menu);

    if (command == kOpenSettings) {
        HideNow();
        OpenSettingsWindow();
    } else if (command == kRestoreAll ||
               (command >= kRestoreFirst &&
                command < kRestoreFirst + (int)removed.size())) {
        if (command == kRestoreAll) {
            for (const auto& app : removed) {
                g_hidden.erase(AppKey(*app));
            }
        } else {
            g_hidden.erase(AppKey(*removed[command - kRestoreFirst]));
        }
        ArrangeTiles(ArrangementLines());  // They come back at the end.
        DropGoneFolder();
        SaveTiles();
        Refresh();
    } else if (command == kSort) {
        g_modal = true;
        int answer = MessageBoxW(
            hwnd,
            L"Put every app back in A to Z order and out of its folder? "
            L"Removed apps stay removed.",
            L"Sort A to Z", MB_OKCANCEL | MB_ICONQUESTION);
        g_modal = false;
        if (g_shown && !g_closing) {
            ForceForeground(hwnd);
        }
        if (answer == IDOK) {
            std::vector<std::wstring> lines;
            for (const auto& key : g_hidden) {
                lines.push_back(L"hidden\t" + key);
            }
            ArrangeTiles(lines);
            DropGoneFolder();
            g_scroll = g_scrollTarget = 0;
            SaveTiles();
            Refresh();
        }
    }
}

void QueryChanged() {
    UpdateFilter();
    g_hover = -1;
    g_selected = g_query.empty() || g_visible.empty() ? -1 : 0;
    g_scroll = g_scrollTarget = 0;
    ComputeLayout();
    StartFrames();  // The glow eases in as typing starts.
    Render();
}

void PasteText() {
    if (!OpenClipboard(g_wnd)) {
        return;
    }
    if (HANDLE data = GetClipboardData(CF_UNICODETEXT)) {
        if (auto* text = (PCWSTR)GlobalLock(data)) {
            std::wstring line = text;
            GlobalUnlock(data);
            line = line.substr(0, line.find_first_of(L"\r\n"));
            // Tabs would split the saved folder name; typed ones never get in.
            std::erase_if(line, [](WCHAR c) { return c < 32; });
            EditPush(0);
            InsertAtCaret(line);
            EditDone();
        }
    }
    CloseClipboard();
    EditChanged();
}

void OnChar(WCHAR ch) {
    if (g_openFolder && !g_folderRenaming) return;
    if (g_drag.active || g_drag.pending) {
        return;
    }
    switch (ch) {
        case 8: {  // Backspace: the selection, or a code point before the caret.
            size_t from, to;
            if (SearchSelection(&from, &to) || g_caret > 0) {
                EditPush(2);
                if (!DeleteSelection()) {
                    size_t prev = CaretStep(g_caret, -1);
                    EditText().erase(prev, g_caret - prev);
                    g_caret = g_anchor = prev;
                }
                EditChanged();
                EditDone();
            }
            TouchCaret();
            return;
        }
        case 0x7F: {  // Ctrl+Backspace: the word before the caret.
            size_t from, to;
            if (SearchSelection(&from, &to) || g_caret > 0) {
                EditPush(2);
                if (!DeleteSelection()) {
                    size_t start = WordStart(g_caret);
                    EditText().erase(start, g_caret - start);
                    g_caret = g_anchor = start;
                }
                EditChanged();
                EditDone();
            }
            TouchCaret();
            return;
        }
        case 0x01:  // Ctrl+A: select all.
            g_anchor = 0;
            g_caret = EditText().size();
            TouchCaret();
            Render();
            return;
        case 0x03:  // Ctrl+C
            CopySelection(false);
            return;
        case 0x18:  // Ctrl+X
            CopySelection(true);
            return;
        case 0x16:  // Ctrl+V
            PasteText();
            return;
        case 0x1A:  // Ctrl+Z: undo; Ctrl+Shift+Z: redo.
            if (GetKeyState(VK_SHIFT) < 0) {
                RedoEdit();
            } else {
                UndoEdit();
            }
            return;
        case 0x19:  // Ctrl+Y: redo.
            RedoEdit();
            return;
    }
    if (ch >= 32 && EditText().size() < MaxEditChars()) {
        EditPush(1);
        InsertAtCaret(std::wstring(1, ch));
        EditDone();
        EditChanged();
    }
}

void MoveSelection(int delta) {
    const Tiles& items = Items();
    if (items.empty()) {
        return;
    }
    int count = (int)items.size();
    if (g_selected < 0) {
        g_selected = 0;
    } else {
        int next = g_selected + delta;
        if (next >= 0 && next < count) {
            g_selected = next;
        } else if (delta > 0 && delta == Columns()) {
            g_selected = count - 1;  // Down on the last incomplete row.
        }
    }
    EnsureVisible(g_selected);
    Render();
    StartFrames();
}

void OnKeyDown(WPARAM key) {
    if (g_drag.active && key != VK_ESCAPE) return;
    if (g_openFolder && g_folderRenaming && (key == VK_RETURN || key == VK_ESCAPE)) {
        g_folderRenaming = false;
        g_searchDrag = false;
        g_anchor = g_caret;
        SaveTiles();
        Render();
        return;
    }
    if (g_openFolder && !g_folderRenaming) {
        switch (key) {
            case VK_LEFT: MoveSelection(-1); break;
            case VK_RIGHT: MoveSelection(1); break;
            case VK_UP: MoveSelection(-Columns()); break;
            case VK_DOWN: MoveSelection(Columns()); break;
            case VK_RETURN: if (g_selected >= 0) ActivateItem(g_selected); break;
            case VK_ESCAPE: break;
            case VK_APPS: ShowSelectedMenu(); break;
        }
        if (key != VK_ESCAPE) return;
    }
    if (g_drag.active && key != VK_ESCAPE) {
        return;
    }
    switch (key) {
        case VK_ESCAPE:
            if (g_drag.active) {
                EndDrag(false);
                ReleaseCapture();
            } else if (g_powerArmed >= 0) {
                DisarmPower();
                Render();
            } else if (g_openFolder) {
                CloseFolder();
            } else if (!g_query.empty()) {
                EditPush(0);  // Ctrl+Z brings the cleared search back.
                g_query.clear();
                g_caret = g_anchor = 0;
                QueryChanged();
            } else {
                Close();
            }
            break;
        case VK_RETURN:
            if (g_selected >= 0) {
                ActivateItem(g_selected);
            } else if (!g_query.empty() && !g_visible.empty()) {
                ActivateItem(0);
            }
            break;
        case VK_APPS:
            ShowSelectedMenu();
            break;
        case VK_LEFT:
            if (!EditText().empty()) {
                bool word = GetKeyState(VK_CONTROL) < 0;
                SetCaret(word ? WordStart(g_caret) : CaretStep(g_caret, -1),
                         GetKeyState(VK_SHIFT) < 0);
                Render();
            } else {
                MoveSelection(-1);
            }
            break;
        case VK_RIGHT:
            if (!EditText().empty()) {
                bool word = GetKeyState(VK_CONTROL) < 0;
                SetCaret(word ? WordEnd(g_caret) : CaretStep(g_caret, 1),
                         GetKeyState(VK_SHIFT) < 0);
                Render();
            } else {
                MoveSelection(1);
            }
            break;
        case VK_UP:
            MoveSelection(-Columns());
            break;
        case VK_DOWN:
            MoveSelection(Columns());
            break;
        case VK_PRIOR:
            if (!g_openFolder) {
                ScrollRows(-g_layout.visibleRows);
            }
            break;
        case VK_NEXT:
            if (!g_openFolder) {
                ScrollRows(g_layout.visibleRows);
            }
            break;
        case VK_HOME:
            if (!EditText().empty()) {
                SetCaret(0, GetKeyState(VK_SHIFT) < 0);
                Render();
            }
            break;
        case VK_END:
            if (!EditText().empty()) {
                SetCaret(EditText().size(), GetKeyState(VK_SHIFT) < 0);
                Render();
            }
            break;
        case VK_DELETE:
            if (!EditText().empty()) {
                size_t dfrom, dto;
                if (SearchSelection(&dfrom, &dto) || g_caret < EditText().size()) {
                    EditPush(2);
                    bool changed = DeleteSelection();
                    if (!changed) {
                        size_t next = CaretStep(g_caret, 1);
                        if (next != g_caret) {
                            EditText().erase(g_caret, next - g_caret);
                            changed = true;
                        }
                    }
                    if (changed) {
                        EditChanged();
                        EditDone();
                    }
                }
                TouchCaret();
            }
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Opening instead of the Windows Start
//
// Every way of opening Start (Windows key, Ctrl+Esc, the taskbar's Start
// button, WM_SYSCOMMAND/SC_TASKLIST from the Dock) goes through
// XamlLauncher::ShowStartView in twinui.pcshell.dll. The hook asks the mod's
// window to toggle and doesn't call the original, so the Windows Start never
// opens.

// Observed on Windows 11 build 26300: the Windows key and Ctrl+Esc arrive as
// method 1 with flag 8; WM_SYSCOMMAND/SC_TASKLIST (the Dock's Start button)
// also arrives as method 1, without that flag.
constexpr int kShowMethodKeyboard = 1;
constexpr int kShowFlagKeyboard = 0x8;

bool IsKeyboardShow(int showMethod, int showFlags) {
    return showMethod == kShowMethodKeyboard && (showFlags & kShowFlagKeyboard);
}

// Shift + Windows key
//
// Windows doesn't open Start for the Windows key pressed with Shift, so
// ShowStartView never sees it. A low-level keyboard hook on its own thread
// (the window thread can be busy drawing) watches for a Windows key press
// with Shift down during it, and no other key pressed in between (Shift+Win+S and
// the like stay Windows shortcuts). For the grid and the original Start, the
// window presses Ctrl+Esc once the keys are up, and the ShowStartView hook
// gives that one the Shift + Windows key action.
//
// Windows keeps keys typed in an administrator window from this hook, and
// drops the Ctrl+Esc it would press there. The optional helper
// (helper/launchpad-keys.cpp) runs as administrator with the same hook. While its
// window exists, this hook leaves the key to it, and the helper sends
// WM_APP_SHIFT_WIN with wParam 1, then presses Ctrl+Esc itself if the answer
// is 1.
constexpr WCHAR kHelperClass[] = L"SeamlessLaunchpadKeys";

std::atomic<ULONGLONG> g_shiftWinUntil;
HANDLE g_keyThread;
DWORD g_keyThreadId;

LRESULT CALLBACK KeyboardHook(int code, WPARAM wParam, LPARAM lParam) {
    // Keyboards that send Shift+Win from one key (macro keys) let go of Shift
    // a moment before Win, so Shift counts if it was down at any point.
    static bool winDown, otherKey, withShift;
    if (code == HC_ACTION) {
        DWORD vk = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;
        bool up = wParam == WM_KEYUP || wParam == WM_SYSKEYUP;
        bool shift = vk == VK_SHIFT || vk == VK_LSHIFT || vk == VK_RSHIFT;
        if (vk == VK_LWIN || vk == VK_RWIN) {
            if (!up && !winDown) {
                winDown = true;
                otherKey = false;
                withShift = GetAsyncKeyState(VK_SHIFT) < 0;
            } else if (up && winDown) {
                winDown = false;
                HWND wnd = g_wnd;
                if (!otherKey && withShift && wnd &&
                    !FindWindowW(kHelperClass, nullptr)) {
                    PostMessageW(wnd, WM_APP_SHIFT_WIN, 0, 0);
                }
            }
        } else if (shift && !up && winDown) {
            withShift = true;
        } else if (!up && !shift && winDown) {
            otherKey = true;
        }
    }
    return CallNextHookEx(nullptr, code, wParam, lParam);
}

DWORD WINAPI KeyThread(void*) {
    HHOOK hook = SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardHook,
                                   GetModuleHandleW(nullptr), 0);
    if (!hook) {
        Wh_Log(L"Keyboard hook failed: %u", GetLastError());
        return 0;
    }
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
    }
    UnhookWindowsHookEx(hook);
    return 0;
}

bool OwnsTaskbar() {
    DWORD pid = 0;
    HWND tray = FindWindowW(L"Shell_TrayWnd", nullptr);
    return tray && GetWindowThreadProcessId(tray, &pid) &&
           pid == GetCurrentProcessId();
}

using XamlLauncher_ShowStartView_t = HRESULT(WINAPI*)(void* pThis,
                                                      int showMethod,
                                                      int showFlags);
XamlLauncher_ShowStartView_t XamlLauncher_ShowStartView_Original;
HRESULT WINAPI XamlLauncher_ShowStartView_Hook(void* pThis,
                                               int showMethod,
                                               int showFlags) {
    Wh_Log(L"> method %d, flags %d", showMethod, showFlags);
    KeyAction action = GetTickCount64() < g_shiftWinUntil
                           ? g_shiftWinKeyAction.load()
                       : IsKeyboardShow(showMethod, showFlags)
                           ? g_winKeyAction.load()
                           : g_startButtonAction.load();
    g_shiftWinUntil = 0;
    HWND wnd = g_wnd;
    if (action == KeyAction::Start || !wnd) {
        return XamlLauncher_ShowStartView_Original(pThis, showMethod,
                                                   showFlags);
    }
    PostMessageW(wnd, action == KeyAction::Program ? WM_APP_RUN
                                                   : WM_APP_TOGGLE,
                 0, 0);
    return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
// Windows


void OnAppsLoaded(AppList* list, int key) {
    if (g_drag.active || g_modal) {
        // Not under a dragged icon or an open menu: read again on the next
        // open.
        delete list;
        g_appsTime = 0;
        return;
    }
    if (g_openFolder) {
        SaveTiles();  // A name being typed.
        g_openFolder = nullptr;
    }
    g_apps = list ? std::move(*list) : AppList{};
    delete list;
    g_appsLoaded = true;
    g_appsKey = key;
    LoadTiles();
    ApplyCustomIcons(key & 0xFFFF);
    if (key != AppsKey()) {
        // The settings changed while this list was read: the reload then
        // found the worker busy. It has posted and is about to end.
        WaitForSingleObject(g_worker, 1000);
        StartLoadingApps();
    }
    if (g_shown) {
        UpdateFilter();
        int count = (int)g_visible.size();
        if (g_selected >= count) {
            g_selected = count ? 0 : -1;
        }
        g_hover = g_pressed = -1;
        ComputeLayout();
        Render();
    }
}

// The tray icon (Look > Tray icon): click opens the settings, right-click shows a menu.
// It lives on the grid's window and thread, like the rest of Launchpad.
constexpr UINT WM_APP_TRAY = WM_APP + 21;
constexpr UINT kTrayId = 1;
static HICON g_trayIcon;
static bool g_trayShown;
static UINT g_taskbarCreated;

// A blue to mauve rounded square with a 3 by 3 grid of dots, drawn per pixel so no
// resource file is needed.
static HICON MakeTrayIcon(int size) {
    BITMAPV5HEADER bi{};
    bi.bV5Size = sizeof(bi); bi.bV5Width = size; bi.bV5Height = -size; bi.bV5Planes = 1;
    bi.bV5BitCount = 32; bi.bV5Compression = BI_BITFIELDS;
    bi.bV5RedMask = 0x00FF0000; bi.bV5GreenMask = 0x0000FF00; bi.bV5BlueMask = 0x000000FF; bi.bV5AlphaMask = 0xFF000000;
    void* bits = nullptr;
    HDC dc = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(dc, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, dc);
    if (!color) return nullptr;
    auto px = (UINT32*)bits;
    const float n = (float)size, rad = n * 0.26f, ss = 4;
    auto inRound = [&](float x, float y) {
        float cx = std::clamp(x, rad, n - rad), cy = std::clamp(y, rad, n - rad);
        return (x - cx) * (x - cx) + (y - cy) * (y - cy) <= rad * rad;
    };
    auto inDot = [&](float x, float y) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                float cx = n * (0.3f + 0.2f * i), cy = n * (0.3f + 0.2f * j), r = n * 0.065f;
                if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r) return true;
            }
        return false;
    };
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float cover = 0, dot = 0;
            for (int sy = 0; sy < ss; sy++)
                for (int sx = 0; sx < ss; sx++) {
                    float fx = x + (sx + 0.5f) / ss, fy = y + (sy + 0.5f) / ss;
                    if (inRound(fx, fy)) { cover++; if (inDot(fx, fy)) dot++; }
                }
            cover /= ss * ss; dot /= ss * ss;
            float t = std::clamp((x + y) / (2.0f * n), 0.0f, 1.0f);
            // 0x89B4FA to 0xCBA6F7, with the dots in crust (0x11111B).
            float r = (0x89 + (0xCB - 0x89) * t), g = (0xB4 + (0xA6 - 0xB4) * t), b = (0xFA + (0xF7 - 0xFA) * t);
            float k = cover > 0 ? dot / cover : 0;
            r = r * (1 - k) + 0x11 * k; g = g * (1 - k) + 0x11 * k; b = b * (1 - k) + 0x1B * k;
            BYTE a = (BYTE)(cover * 255 + 0.5f);
            px[y * size + x] = ((UINT32)a << 24) | ((UINT32)(r * cover) << 16) | ((UINT32)(g * cover) << 8) | (UINT32)(b * cover);
        }
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    return icon;
}

static void UpdateTrayIcon(HWND hwnd) {
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = hwnd;
    nid.uID = kTrayId;
    if (!g_settings.trayIcon) {
        if (g_trayShown) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayShown = false;
        return;
    }
    if (!g_trayIcon) g_trayIcon = MakeTrayIcon(GetSystemMetricsForDpi(SM_CXSMICON, GetDpiForSystem()));
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_APP_TRAY;
    nid.hIcon = g_trayIcon;
    wcscpy_s(nid.szTip, L"Seamless Launchpad");
    if (g_trayShown && Shell_NotifyIconW(NIM_MODIFY, &nid)) return;
    g_trayShown = Shell_NotifyIconW(NIM_ADD, &nid) != FALSE;
    if (g_trayShown) {
        nid.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, &nid);
    }
}

static void RemoveTrayIcon(HWND hwnd) {
    if (g_trayShown) {
        NOTIFYICONDATAW nid{sizeof(nid)};
        nid.hWnd = hwnd;
        nid.uID = kTrayId;
        Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayShown = false;
    }
    if (g_trayIcon) {
        DestroyIcon(g_trayIcon);
        g_trayIcon = nullptr;
    }
}

static void OnTrayMessage(HWND hwnd, LPARAM lParam) {
    switch (LOWORD(lParam)) {
        case NIN_SELECT:
        case NIN_KEYSELECT:
            OpenSettingsWindow();
            break;
        case WM_CONTEXTMENU: {
            HMENU menu = CreatePopupMenu();
            AppendMenuW(menu, MF_STRING, 1, L"Settings");
            AppendMenuW(menu, MF_STRING, 2, L"Open Launchpad");
            SetMenuDefaultItem(menu, 1, FALSE);
            POINT pt;
            GetCursorPos(&pt);
            SetForegroundWindow(hwnd);
            int cmd = TrackPopupMenuEx(menu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_RIGHTBUTTON, pt.x, pt.y, hwnd, nullptr);
            DestroyMenu(menu);
            if (cmd == 1) OpenSettingsWindow();
            if (cmd == 2) PostMessageW(hwnd, WM_APP_TOGGLE, 0, 0);
            break;
        }
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (g_taskbarCreated && msg == g_taskbarCreated) {
        g_trayShown = false;  // The new taskbar has no icons yet.
        UpdateTrayIcon(hwnd);
        return 0;
    }
    switch (msg) {
        case WM_APP + 20: OpenSettingsWindow(); return 0;
        case WM_APP_TRAY: OnTrayMessage(hwnd, lParam); return 0;
        case WM_APP_TOGGLE:
            // Clicking the taskbar's Start button while this one is open first
            // takes the focus (which closes it) and then asks for Start: that
            // click was meant to close it.
            if ((!g_shown || g_closing) && Now() - g_lastClosed < 0.5) {
                return 0;
            }
            Toggle();
            return 0;

        case WM_APP_APPS:
            OnAppsLoaded((AppList*)lParam, (int)wParam);
            return 0;

        case WM_APP_RELOAD:
            LoadSettings();
            UpdateTrayIcon(hwnd);
            if (g_shown) {
                HideNow();
            }
            if (g_appsKey != AppsKey()) {
                StartLoadingApps();
            }
            return 0;

        case WM_APP_RUN:
            if (g_shown) {
                HideNow();
            }
            RunProgram();
            return 0;

        case WM_APP_SHIFT_WIN:
            // Explorer runs this mod in each of its processes; only the
            // taskbar's one answers the key.
            if (!OwnsTaskbar()) {
                return 0;
            }
            if (g_shiftWinKeyAction == KeyAction::Program) {
                PostMessageW(hwnd, WM_APP_RUN, 0, 0);
                return 0;
            }
            if (g_shown && g_shiftWinKeyAction == KeyAction::Start) {
                HideNow();
            }
            if (wParam == 1) {
                // The helper presses Ctrl+Esc once the keys are up.
                g_shiftWinUntil = GetTickCount64() + 3000;
                return 1;
            }
            // The grid and the original Start open through Ctrl+Esc, once
            // Shift is up (with Shift it's Task Manager): only a Start that
            // Windows opens may take the foreground. SC_TASKLIST to the
            // taskbar does nothing here.
            SetTimer(hwnd, kTimerShiftWin, 20, nullptr);
            return 0;

        case WM_APP_QUIT:
            RemoveTrayIcon(hwnd);
            DestroyWindow(hwnd);
            return 0;

        case WM_TIMER:
            switch (wParam) {
                case kTimerFrame:
                    OnFrame();
                    break;
                case kTimerShiftWin:
                    if (GetAsyncKeyState(VK_SHIFT) >= 0 &&
                        GetAsyncKeyState(VK_LWIN) >= 0 &&
                        GetAsyncKeyState(VK_RWIN) >= 0) {
                        KillTimer(hwnd, kTimerShiftWin);
                        g_shiftWinUntil = GetTickCount64() + 1000;
                        INPUT keys[4] = {};
                        WORD vks[4] = {VK_CONTROL, VK_ESCAPE, VK_ESCAPE,
                                       VK_CONTROL};
                        for (int i = 0; i < 4; i++) {
                            keys[i].type = INPUT_KEYBOARD;
                            keys[i].ki.wVk = vks[i];
                            keys[i].ki.dwFlags = i < 2 ? 0 : KEYEVENTF_KEYUP;
                        }
                        SendInput(4, keys, sizeof(INPUT));
                    }
                    break;
                case kTimerPowerArm:
                    DisarmPower();
                    Render();
                    break;
                case kTimerCaret:
                    // The search caret blinks by plain redraws.
                    if (g_shown && (!g_openFolder || g_folderRenaming)) {
                        Render();
                    }
                    break;
                case kTimerFirstLoad:
                    // Only in the process that owns the taskbar: short-lived
                    // explorer.exe processes (explorer.exe /select,...) get
                    // the mod too, and exit before they'd need the list.
                    if (OwnsTaskbar()) {
                        KillTimer(hwnd, kTimerFirstLoad);
                        if (!g_appsLoaded) {
                            StartLoadingApps();
                        }
                    }
                    break;
            }
            return 0;

        case WM_ACTIVATE:
            if (LOWORD(wParam) == WA_INACTIVE && g_shown && !g_closing &&
                !g_modal) {
                g_lastClosed = Now();
                Close();
            }
            return 0;

        case WM_MOUSEMOVE: {
            if (!g_trackingMouse) {
                TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
                g_trackingMouse = TrackMouseEvent(&tme);
            }
            int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
            if (g_searchDrag) {
                SetCaret(CaretAtPoint((float)x), true);
                Render();
                return 0;
            }
            // A drag is real past the system drag threshold only.
            if (g_drag.pending && !g_drag.active &&
                (std::abs(x - g_drag.start.x) >
                     GetSystemMetrics(SM_CXDRAG) ||
                 std::abs(y - g_drag.start.y) >
                     GetSystemMetrics(SM_CYDRAG))) {
                StartDrag();
            }
            if (g_drag.active) {
                DragMove(x, y);
                return 0;
            }
            bool titleHover = g_openFolder && InRect(FolderTitlePill(), (float)x, (float)y);
            if (titleHover != g_folderTitleHover) {
                g_folderTitleHover = titleHover;
                Render();
            }
            int hover = ItemAt(x, y);
            bool menuHover =
                !g_openFolder && InButton(g_layout.menuButton, (float)x, (float)y);
            bool clearHover = !g_openFolder && !g_query.empty() &&
                              InButton(g_layout.clearButton, (float)x, (float)y);
            bool searchHover = !g_openFolder && !menuHover && !clearHover &&
                               InRect(g_layout.search, (float)x, (float)y);
            int powerHover = g_openFolder ? -1 : PowerAt(x, y);
            if (hover != g_hover || menuHover != g_menuHover ||
                clearHover != g_clearHover ||
                searchHover != g_searchHover ||
                powerHover != g_powerHover) {
                g_hover = hover;
                g_menuHover = menuHover;
                g_clearHover = clearHover;
                g_searchHover = searchHover;
                g_powerHover = powerHover;
                StartFrames();  // The bar's glow eases between states.
                Render();
                StartFrames();
            }
            return 0;
        }

        case WM_MOUSELEAVE:
            g_folderTitleHover = false;
            g_trackingMouse = false;
            if (g_hover >= 0 || g_menuHover || g_clearHover || g_searchHover ||
                g_powerHover >= 0) {
                g_hover = -1;
                g_menuHover = false;
                g_clearHover = false;
                g_searchHover = false;
                g_powerHover = -1;
                StartFrames();
                Render();
                StartFrames();
            }
            return 0;

        case WM_LBUTTONDOWN: {
            int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
            if (g_closing) {
                return 0;  // A click during the closing fade does nothing.
            }
            if (!g_openFolder) {
                int power = PowerAt(x, y);
                if (power >= 0) {
                    g_powerPressed = power;
                    SetCapture(hwnd);
                    Render();
                    return 0;
                }
                if (g_powerArmed >= 0) {
                    DisarmPower();  // A click elsewhere cancels the prompt.
                }
                if (InButton(g_layout.menuButton, (float)x, (float)y)) {
                    POINT pt{(LONG)g_layout.menuButton.right,
                             (LONG)g_layout.menuButton.bottom + 4};
                    ClientToScreen(hwnd, &pt);
                    ShowOptionsMenu(hwnd, pt, true);
                    return 0;
                }
                if (!g_query.empty() &&
                    InButton(g_layout.clearButton, (float)x, (float)y)) {
                    EditPush(0);  // Ctrl+Z brings the cleared search back.
                    g_query.clear();
                    g_caret = g_anchor = 0;
                    g_clearHover = false;
                    QueryChanged();
                    return 0;
                }
                int dot = PageDotAt(x, y);
                if (dot >= 0) {
                    g_scrollTarget = dot * (float)g_layout.width;
                    StartFrames();
                    return 0;
                }
            }
            bool editHit = InRect(g_openFolder ? FolderTitlePill() : EditBox(false), (float)x, (float)y);
            if (g_openFolder && g_folderRenaming && !editHit) {
                g_folderRenaming = false;
                SaveTiles();
            }
            if (editHit) {
                if (g_openFolder) g_folderRenaming = true;
                // A click in the search field, or in an open folder's name,
                // places the caret; holding the button and moving selects
                // text. A second click on the same spot selects the word.
                UINT64 tick = GetTickCount64();
                bool dbl = tick - g_lastSearchClick <=
                               GetDoubleClickTime() &&
                           std::abs(x - g_lastSearchX) <=
                               4 * g_layout.scale;
                g_lastSearchClick = tick;
                g_lastSearchX = x;
                if (dbl) {
                    size_t pos = CaretAtPoint((float)x);
                    g_anchor = WordStart(pos);
                    g_caret = WordEnd(pos);
                } else {
                    SetCaret(CaretAtPoint((float)x), false);
                }
                g_searchDrag = true;
                SetCapture(hwnd);
                Render();
                return 0;
            }
            if (g_anchor != g_caret) {
                g_anchor = g_caret;  // A click elsewhere drops the selection.
            }
            SetCapture(hwnd);
            g_pressed = ItemAt(x, y);
            g_pressedEmpty = g_pressed < 0 && !ClickKeepsOpen(x, y);
            g_drag.pending = g_pressed >= 0 && g_query.empty();
            g_drag.pressTime = Now();
            g_drag.start = {x, y};
            if (g_drag.pending) {
                StartFrames();  // Ticks the hold time toward the edit mode.
            }
            Render();
            return 0;
        }

        case WM_LBUTTONUP: {
            int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
            g_searchDrag = false;
            bool dragged = g_drag.active;
            // ReleaseCapture fires WM_CAPTURECHANGED synchronously, and that
            // handler clears the press; snapshot it before the capture goes.
            int powerPressed = g_powerPressed;
            EndDrag(true);  // Before the capture goes, which would undo it.
            if (GetCapture() == hwnd) {
                ReleaseCapture();
            }
            g_powerPressed = -1;
            if (powerPressed >= 0) {
                if (PowerAt(x, y) == powerPressed) {
                    PowerClick(powerPressed);  // May hide the grid.
                }
                Render();
                return 0;
            }
            int pressed = g_pressed;
            bool pressedEmpty = g_pressedEmpty;
            g_pressed = -1;
            g_pressedEmpty = false;
            if (dragged) {
                return 0;
            }
            int item = ItemAt(x, y);
            if (pressed >= 0 && item == pressed) {
                ActivateItem(item);
            } else if (pressedEmpty && item < 0 && !ClickKeepsOpen(x, y)) {
                // Clicking on empty space closes, like in Launchpad.
                if (g_openFolder) {
                    CloseFolder();
                } else {
                    Close();
                }
            } else {
                Render();
            }
            return 0;
        }

        case WM_CAPTURECHANGED:
            EndDrag(false);  // Another window took the mouse.
            g_searchDrag = false;
            g_powerPressed = -1;
            return 0;

        case WM_RBUTTONUP: {
            if (g_drag.active) {
                return 0;
            }
            int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
            POINT pt{x, y};
            ClientToScreen(hwnd, &pt);
            int item = ItemAt(x, y);
            if (item >= 0) {
                ShowTileMenu(hwnd, item, pt);
            } else if (!g_openFolder) {
                ShowOptionsMenu(hwnd, pt, false);
            }
            return 0;
        }

        case WM_MOUSEWHEEL:
        case WM_MOUSEHWHEEL:
            if (g_openFolder) {
                if (msg == WM_MOUSEWHEEL) {
                    g_wheelDelta += GET_WHEEL_DELTA_WPARAM(wParam);
                    if (std::abs(g_wheelDelta) >= WHEEL_DELTA) {
                        FolderLayout F = GetFolderLayout();
                        g_folderRow =
                            std::clamp(g_folderRow - g_wheelDelta / WHEEL_DELTA,
                                       0, F.rows - F.visibleRows);
                        g_wheelDelta %= WHEEL_DELTA;
                        Render();
                    }
                }
                return 0;
            }
            // Sideways (tilt wheel, touchpad swipe) only flips pages.
            if (msg == WM_MOUSEHWHEEL && !g_settings.pages) {
                return 0;
            }
            g_wheelDelta += msg == WM_MOUSEWHEEL
                                ? GET_WHEEL_DELTA_WPARAM(wParam)
                                : -GET_WHEEL_DELTA_WPARAM(wParam);
            if (std::abs(g_wheelDelta) >= WHEEL_DELTA) {
                ScrollRows(-g_wheelDelta / WHEEL_DELTA);
                g_wheelDelta %= WHEEL_DELTA;
            }
            return 0;

        case WM_KEYDOWN:
            OnKeyDown(wParam);
            return 0;

        case WM_CHAR:
            OnChar((WCHAR)wParam);
            return 0;

        case WM_CLOSE:  // Alt+F4
            Close();
            return 0;

        case WM_DPICHANGED:
            return 0;  // Position and scaling are computed when opening.

        case WM_DISPLAYCHANGE:
        case WM_SETTINGCHANGE:
            if (g_shown && (msg == WM_DISPLAYCHANGE || wParam == SPI_SETWORKAREA)) {
                HideNow();
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK BackdropWndProc(HWND hwnd,
                                 UINT msg,
                                 WPARAM wParam,
                                 LPARAM lParam) {
    switch (msg) {
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_NCHITTEST:
            return HTTRANSPARENT;
        case WM_ERASEBKGND: {
            // Black with zero alpha: only the DWM effect shows.
            RECT rc;
            GetClientRect(hwnd, &rc);
            FillRect((HDC)wParam, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
            return 1;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC dc = BeginPaint(hwnd, &ps);
            FillRect(dc, &ps.rcPaint, (HBRUSH)GetStockObject(BLACK_BRUSH));
            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

HANDLE g_thread;
HANDLE g_readyEvent;

DWORD WINAPI StartThread(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    OleInitialize(nullptr);
    LoadSettings();
    MigrateOldStorage();  // Before the app loading reads the folder.

    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, g_d2d.GetAddressOf());
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                        (IUnknown**)g_dwrite.GetAddressOf());

    HINSTANCE instance = (HINSTANCE)&__ImageBase;
    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = instance;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kWindowClass;
    RegisterClassExW(&wc);

    WNDCLASSEXW bc{sizeof(bc)};
    bc.lpfnWndProc = BackdropWndProc;
    bc.hInstance = instance;
    bc.lpszClassName = kBackdropClass;
    RegisterClassExW(&bc);

    g_backdrop = CreateWindowExW(
        WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE |
            WS_EX_TRANSPARENT,
        kBackdropClass, L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, instance,
        nullptr);
    HWND wnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED,
                               kWindowClass, L"Start", WS_POPUP, 0, 0, 0, 0,
                               nullptr, nullptr, instance, nullptr);
    bool ok = g_d2d && g_dwrite && g_backdrop && wnd;
    if (ok) {
        g_wnd = wnd;
        g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
        ChangeWindowMessageFilterEx(wnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
        UpdateTrayIcon(wnd);
        // The app list is read a bit later, so it doesn't weigh on explorer's
        // startup.
        SetTimer(wnd, kTimerFirstLoad, 3000, nullptr);
    }
    SetEvent(g_readyEvent);

    if (ok) {
        MSG msg;
        while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    } else {
        Wh_Log(L"Failed to create Start");
        if (wnd) {
            DestroyWindow(wnd);
        }
    }
    g_wnd = nullptr;

    g_workerStop = true;
    if (g_worker) {
        WaitForSingleObject(g_worker, INFINITE);
        CloseHandle(g_worker);
        g_worker = nullptr;
    }
    // A list delivered after the window stopped handling messages.
    MSG msg;
    while (PeekMessageW(&msg, nullptr, WM_APP_APPS, WM_APP_APPS, PM_REMOVE)) {
        delete (AppList*)msg.lParam;
    }

    if (g_backdrop) {
        DestroyWindow(g_backdrop);
        g_backdrop = nullptr;
    }
    AppList().swap(g_apps);  // Also frees the memory (no_destroy).
    Tiles().swap(g_tiles);
    Tiles().swap(g_visible);
    g_openFolder = nullptr;
    g_drag = {};
    g_backdropImage = {};
    g_panelBlur = {};
    FreeSurface(g_surface);
    g_labelFormat.Reset();
    g_searchFormat.Reset();
    g_messageFormat.Reset();
    g_iconFormat.Reset();
    g_tipFormat.Reset();
    ResetTarget();
    g_dwrite.Reset();
    g_d2d.Reset();
    UnregisterClassW(kWindowClass, instance);
    UnregisterClassW(kBackdropClass, instance);
    OleUninitialize();
    return 0;
}

// With "Launch folder windows in a separate process", folder windows run in
// their own explorer.exe, which never shows Start.
bool IsFolderWindowsProcess() {
    std::wstring commandLine = ToLower(GetCommandLineW());
    return commandLine.find(L"/factory") != std::wstring::npos ||
           commandLine.find(L"-embedding") != std::wstring::npos ||
           commandLine.find(L"/separate") != std::wstring::npos;
}

bool HookShowStartView() {
    HMODULE module = LoadLibraryExW(L"twinui.pcshell.dll", nullptr,
                                    LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!module) {
        Wh_Log(L"Couldn't load twinui.pcshell.dll");
        return false;
    }
    // twinui.pcshell.dll
    WindhawkUtils::SYMBOL_HOOK hooks[] = {
        {
            {LR"(public: virtual long __cdecl XamlLauncher::ShowStartView(enum IMMERSIVELAUNCHERSHOWMETHOD,enum IMMERSIVELAUNCHERSHOWFLAGS))"},
            &XamlLauncher_ShowStartView_Original,
            XamlLauncher_ShowStartView_Hook,
        },
    };
    if (!WindhawkUtils::HookSymbols(module, hooks, ARRAYSIZE(hooks))) {
        Wh_Log(L"HookSymbols failed");
        return false;
    }
    return true;
}

}  // namespace
