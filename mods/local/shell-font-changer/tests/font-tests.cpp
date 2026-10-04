#include "../shell-font-changer.wh.cpp"
#include <cstdio>

int failures = 0;
void check(bool ok, const char* label) {
    std::printf("%s %s\n", ok ? "PASS" : "FAIL", label);
    failures += !ok;
}
auto keptOriginal = [](HDC dc) {
    wchar_t face[LF_FACESIZE]{};
    GetTextFaceW(dc, LF_FACESIZE, face);
    return _wcsicmp(face, policy::target.c_str()) != 0;
};
// Readable: never below the scale floor, never condensed past the width floor.
auto readable = [](HDC dc, LONG height) {
    LOGFONTW f{};
    GetObjectW(GetCurrentObject(dc, OBJ_FONT), sizeof(f), &f);
    return std::labs(f.lfHeight) >= std::labs(height) * 0.85 - 1;
};int main() {
    policy::target = L"FiraCode Nerd Font";
    policy::enabled = true;
    check(policy::protectedFace(L"Segoe Fluent Icons"), "Fluent icons preserved");
    check(policy::protectedFace(L"Segoe MDL2 Assets"), "MDL2 icons preserved");
    check(policy::protectedFace(L"Segoe UI Emoji"), "emoji face preserved");
    check(policy::protectedFace(L"Wingdings"), "Wingdings preserved");
    check(policy::protectedFace(L"Custom", SYMBOL_CHARSET), "symbol charset preserved");
    check(policy::protectedText(L"\uE710", 1), "private-use run preserved");
    check(policy::protectedText(L"\xD83D\xDE00", 2), "surrogate run preserved");
    check(!policy::protectedText(L"Explorer", 8), "ordinary text eligible");
    HDC dc = CreateCompatibleDC(nullptr);
    LOGFONTW lf{};
    lf.lfHeight = -16;
    wcscpy_s(lf.lfFaceName, L"Segoe UI");
    HFONT original = CreateFontIndirectW(&lf);
    auto stock = SelectObject(dc, original);
    {
        FontScope scope(dc, L"Explorer", 8);
        wchar_t face[LF_FACESIZE]{};
        GetTextFaceW(dc, LF_FACESIZE, face);
        check(!_wcsicmp(face, policy::target.c_str()), "GDI selected FiraCode family");
        LOGFONTW selected{};GetObjectW(GetCurrentObject(dc,OBJ_FONT),sizeof(selected),&selected);
        check(selected.lfHeight==lf.lfHeight,"unconstrained text keeps normal height");
        RECT roomy{0,0,1000,100};fitBox(scope,dc,L"Explorer",8,&roomy,DT_SINGLELINE,nullptr,true);
        GetObjectW(GetCurrentObject(dc,OBJ_FONT),sizeof(selected),&selected);
        check(selected.lfHeight==lf.lfHeight,"roomy control keeps normal height");
    }
    check(GetCurrentObject(dc, OBJ_FONT) == original, "original HFONT restored");
    {
        FontScope scope(dc, L"\uE710", 1);
        check(GetCurrentObject(dc, OBJ_FONT) == original, "PUA draw keeps original HFONT");
    }
    {
        FontScope scope(dc, L"abc", 3, true);
        check(GetCurrentObject(dc, OBJ_FONT) == original, "glyph-index draw keeps original HFONT");
    }
    drawTextOriginal = DrawTextW;
    drawTextExOriginal = DrawTextExW;
    extentOriginal = GetTextExtentPoint32W;
    RECT measured{0,0,2000,2000};
    drawTextHook(dc,L"Explorer",8,&measured,DT_CALCRECT | DT_SINGLELINE);
    SIZE size{};
    extentHook(dc,L"Explorer",8,&size);
    check(measured.right == size.cx, "DrawText and extent measurements match");
    DRAWTEXTPARAMS params{sizeof(params)};
    wchar_t bounded[3] = {L'a',L'b',L'c'};
    RECT rect{0,0,1000,100};
    drawTextExHook(dc,bounded,3,&rect,DT_CALCRECT,&params);
    check(params.uiLengthDrawn == 3, "DrawTextEx bounded buffer and output parameters preserved");
    for (auto label : {L"Choose File...", L"Restore Default"}) {
        for (int height : {-12, -16, -24, -32}) {
            LOGFONTW sample = lf;
            sample.lfHeight = height;
            HFONT base = CreateFontIndirectW(&sample);
            SelectObject(dc, base);
            {
                FontScope scope(dc, label, static_cast<UINT>(wcslen(label)));
                RECT box{0,0,80,20};
                fitBox(scope,dc,label,static_cast<UINT>(wcslen(label)),&box,DT_SINGLELINE,nullptr,true);
                RECT measured = box;
                DrawTextW(dc,label,-1,&measured,DT_SINGLELINE|DT_CALCRECT);
                check(((measured.right <= 80 && measured.bottom <= 20) || keptOriginal(dc)) && readable(dc,height),"button text fits or keeps original font, readable");
            }
            check(GetCurrentObject(dc,OBJ_FONT)==base,"fit restores control font");
            SelectObject(dc,original);
            DeleteObject(base);
        }
    }
    {
        const wchar_t* description = L"You can use this page to limit the amount of disk space each user can use on this volume.";
        FontScope scope(dc,description,static_cast<UINT>(wcslen(description)));
        RECT box{0,0,250,30};
        fitBox(scope,dc,description,static_cast<UINT>(wcslen(description)),&box,DT_WORDBREAK,nullptr,true);
        RECT measured=box;
        DrawTextW(dc,description,-1,&measured,DT_WORDBREAK|DT_CALCRECT);
        check((measured.bottom<=30 && measured.right<=250) || keptOriginal(dc),"wrapped quota description fits or keeps original font");
    }
    {
        FontScope scope(dc,L"Restore Default",15);
        RECT box{0,0,80,20};DRAWTEXTPARAMS margins{sizeof(margins)};
        margins.iLeftMargin=10;margins.iRightMargin=10;
        fitBox(scope,dc,L"Restore Default",15,&box,DT_SINGLELINE,&margins,true);
        SIZE measured{};GetTextExtentPoint32W(dc,L"Restore Default",15,&measured);
        check(measured.cx<=60 || keptOriginal(dc),"DrawTextEx margins reserve space");
    }
    {
        FontScope scope(dc,L"Line one\nLine two\nLine three",28);
        RECT box{0,0,100,25};
        fitBox(scope,dc,L"Line one\nLine two\nLine three",28,&box,0,nullptr,true);
        RECT measured=box;DrawTextW(dc,L"Line one\nLine two\nLine three",28,&measured,DT_CALCRECT);
        check(measured.bottom<=25 || keptOriginal(dc),"explicit multiple lines fit height");
    }
    {
        FontScope scope(dc,L"Object name:",12);
        RECT box{0,0,50,22};fitBox(scope,dc,L"Object name:",12,&box,0,nullptr,true);
        LOGFONTW selected{};GetObjectW(GetCurrentObject(dc,OBJ_FONT),sizeof(selected),&selected);
        RECT measured=box;DrawTextW(dc,L"Object name:",12,&measured,DT_CALCRECT);
        check(selected.lfHeight==lf.lfHeight,"narrow Object name label retains regular height");
        check(measured.right<=50 || keptOriginal(dc),"narrow Object name label fits width or keeps original font");
    }
    auto before = GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS);
    for (int i=0; i<10000; ++i) {
        RECT r{0,0,80,20};
        drawTextHook(dc,L"Restore Default",15,&r,DT_SINGLELINE);
    }
    auto after = GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS);
    std::printf("GDI handles before=%lu after=%lu\n",before,after);
    check(after == before, "10000 calls leak no GDI handles");
    {
        RECT box{0,0,80,20};
        drawTextHook(nullptr,nullptr,0,&box,DT_SINGLELINE);
        drawTextHook(dc,nullptr,0,&box,DT_SINGLELINE);
        check(GetCurrentObject(dc,OBJ_FONT)==original,"null drawing paths preserve font");
    }
    policy::enabled = false;
    {
        FontScope scope(dc,L"abc",3);
        check(GetCurrentObject(dc,OBJ_FONT) == original,"None/disabled policy preserves selected font");
    }
    policy::enabled = true;
    {
        FontScope scope(dc,L"\u4E00",1);
        check(GetCurrentObject(dc,OBJ_FONT) == original,"missing target glyph keeps original font");
    }
    {
        // Explorer formats dates as U+200E 30/09/U+200E 2026 U+200F U+200E 8:51 AM.
        FontScope scope(dc,L"‎30/09/‎2026 ‏‎8:51 AM",19);
        wchar_t face[LF_FACESIZE]{};
        GetTextFaceW(dc,LF_FACESIZE,face);
        check(!_wcsicmp(face,policy::target.c_str()),"direction marks in dates do not block substitution");
    }
    check(GetCurrentObject(dc,OBJ_FONT) == original,"date run restores original HFONT");
    {
        FontScope scope(dc,L"a⁦b",3);
        check(GetCurrentObject(dc,OBJ_FONT) == original,"visible missing control keeps original font");
    }
    {
        LOGFONTW heavy = lf;
        heavy.lfWeight = FW_BOLD;
        HFONT bold = CreateFontIndirectW(&heavy);
        SelectObject(dc,bold);
        {
            FontScope scope(dc,L"Explorer",8);
            TEXTMETRICW tm{};
            GetTextMetricsW(dc,&tm);
            check(tm.tmWeight >= FW_BOLD,"bold weight carried to replacement");
        }
        SelectObject(dc,original);
        DeleteObject(bold);
    }
    check(policy::nameWeight(L"Segoe UI Semibold") == 600 && policy::nameWeight(L"Segoe UI Black") == 900 &&
          policy::nameWeight(L"Segoe UI Bold") == 700 && policy::nameWeight(L"Segoe UI") == 0 &&
          policy::nameWeight(L"Bold") == 0, "weight read from legacy face names");
    {
        LOGFONTW named = lf;
        wcscpy_s(named.lfFaceName,L"Segoe UI Semibold");
        HFONT semibold = CreateFontIndirectW(&named);
        SelectObject(dc,semibold);
        {
            FontScope scope(dc,L"Explorer",8);
            LOGFONTW selected{};
            GetObjectW(GetCurrentObject(dc,OBJ_FONT),sizeof(selected),&selected);
            check(!_wcsicmp(selected.lfFaceName,policy::target.c_str()) && selected.lfWeight >= 600,"GDI legacy semibold face keeps its weight");
        }
        SelectObject(dc,original);
        DeleteObject(semibold);
    }
    {
        LOGFONTW vertical = lf;
        wcscpy_s(vertical.lfFaceName,L"@Yu Gothic UI");
        HFONT tall = CreateFontIndirectW(&vertical);
        SelectObject(dc,tall);
        {
            FontScope scope(dc,L"Explorer",8);
            check(GetCurrentObject(dc,OBJ_FONT) == tall,"vertical face keeps original font");
        }
        SelectObject(dc,original);
        DeleteObject(tall);
    }
    {
        auto saved = policy::target;
        policy::target = L"No Such Font Family";
        FontScope scope(dc,L"Explorer",8);
        check(GetCurrentObject(dc,OBJ_FONT) == original,"unknown GDI face never maps to a third font");
        policy::target = saved;
    }
    before = GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS);
    for (int i=0; i<10000; ++i) {
        FontScope a(dc,L"‎30/09/2026",11);
        FontScope b(dc,L"一",1);
    }
    after = GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS);
    check(after == before && GetCurrentObject(dc,OBJ_FONT) == original,"10000 fallback and nested scopes leak no GDI handles");
    LOGFONTW retained{};
    GetObjectW(original,sizeof(retained),&retained);
    check(!_wcsicmp(retained.lfFaceName,L"Segoe UI"),"persistent HFONT unchanged after drawing");
    IDWriteFactory* factory=nullptr;
    HRESULT hr=DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),reinterpret_cast<IUnknown**>(&factory));
    check(SUCCEEDED(hr),"DirectWrite factory available");
    if(factory) {
        layoutOriginal=reinterpret_cast<LayoutFn>((*reinterpret_cast<void***>(factory))[18]);
        gdiLayoutOriginal=reinterpret_cast<GdiLayoutFn>((*reinterpret_cast<void***>(factory))[19]);
        for (auto family : {L"Segoe UI",L"Segoe Fluent Icons"}) {
            IDWriteTextFormat* format=nullptr;
            factory->CreateTextFormat(family,nullptr,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,16,L"en-us",&format);
            check(format != nullptr,"DirectWrite original format creation");
            if(!format) continue;
            IDWriteTextLayout* layout=nullptr;
            layoutHook(factory,L"Explorer",8,format,500,100,&layout);
            check(layout != nullptr,"DirectWrite layout creation");
            if(layout) {
                wchar_t actual[64]{};
                layout->GetFontFamilyName(0,actual,64);
                check(!_wcsicmp(actual,policy::protectedFace(family) ? family : policy::target.c_str()),"DirectWrite layout text substitution / icon preservation");
                layout->Release();
            }
            layout=nullptr;
            layoutHook(factory,L"\uE710",1,format,500,100,&layout);
            if(layout) {
                wchar_t actual[64]{};
                layout->GetFontFamilyName(0,actual,64);
                check(!_wcsicmp(actual,family),"DirectWrite PUA keeps original family");
                layout->Release();
            } else check(false,"DirectWrite PUA layout");
            wchar_t unchanged[64]{};
            format->GetFontFamilyName(unchanged,64);
            check(!_wcsicmp(unchanged,family),"cached DirectWrite format unchanged");
            layout=nullptr;
            gdiLayoutHook(factory,L"Explorer",8,format,500,100,1.0f,nullptr,FALSE,&layout);
            if(layout) {
                wchar_t actual[64]{};
                layout->GetFontFamilyName(0,actual,64);
                check(!_wcsicmp(actual,policy::protectedFace(family) ? family : policy::target.c_str()),"GDI-compatible DirectWrite layout");
                layout->Release();
            } else check(false,"GDI-compatible DirectWrite layout");
            format->Release();
        }
        IDWriteTextFormat* semibold=nullptr;
        factory->CreateTextFormat(L"Segoe UI Semibold",nullptr,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,16,L"en-us",&semibold);
        if(semibold) {
            IDWriteTextLayout* layout=nullptr;
            layoutHook(factory,L"‎Explorer",9,semibold,500,100,&layout);
            if(layout) {
                wchar_t actual[64]{};
                layout->GetFontFamilyName(0,actual,64);
                check(!_wcsicmp(actual,policy::target.c_str()),"DirectWrite legacy family substituted");
                DWRITE_FONT_WEIGHT weight=DWRITE_FONT_WEIGHT_NORMAL;
                layout->GetFontWeight(0,&weight);
                check(weight >= DWRITE_FONT_WEIGHT_SEMI_BOLD,"DirectWrite legacy family weight carried");
                layout->Release();
            } else check(false,"DirectWrite legacy family layout");
            semibold->Release();
        } else check(false,"DirectWrite legacy family format");
        IDWriteTextFormat* roomy=nullptr;
        factory->CreateTextFormat(L"Segoe UI",nullptr,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,16,L"en-us",&roomy);
        if(roomy) {
            IDWriteTextLayout* layout=nullptr;layoutHook(factory,L"Explorer",8,roomy,1000,100,&layout);
            if(layout){float size=0;layout->GetFontSize(0,&size);check(size==16,"DirectWrite roomy control keeps normal size");layout->Release();}
            roomy->Release();
        }
        IDWriteTextFormat* compact=nullptr;
        factory->CreateTextFormat(L"Segoe UI",nullptr,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,DWRITE_FONT_STRETCH_NORMAL,24,L"en-us",&compact);
        if(compact) {
            IDWriteTextLayout* layout=nullptr;
            layoutHook(factory,L"Restore Default",15,compact,80,20,&layout);
            if(layout) {
                DWRITE_TEXT_METRICS metrics{};layout->GetMetrics(&metrics);
                check(metrics.widthIncludingTrailingWhitespace<=80.01f && metrics.height<=20.01f,"DirectWrite fixed box fits");
                check(compact->GetFontSize()==24,"DirectWrite original size unchanged");
                layout->Release();
            } else check(false,"DirectWrite compact layout");
            compact->Release();
        }
        factory->Release();
    }
    SelectObject(dc,stock);
    DeleteObject(original);
    DeleteDC(dc);
    std::printf("Failures: %d\n",failures);
    return failures ? 1 : 0;
}

