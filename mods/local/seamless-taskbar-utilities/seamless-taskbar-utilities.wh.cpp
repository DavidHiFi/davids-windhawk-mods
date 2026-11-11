// ==WindhawkMod==
// @id              seamless-taskbar-utilities
// @name            Seamless Taskbar Utilities
// @description     Quick system tools in the taskbar right-click menu, with a Catppuccin Mocha menu and result cards
// @version         1.5.0
// @author          DavidHiFi, Marco Petrucci
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -DWIN32_LEAN_AND_MEAN -lole32 -loleaut32 -lruntimeobject -lshell32 -lws2_32 -liphlpapi -lwininet -luser32
// @license         MIT
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Taskbar Utilities

Right-click an empty spot on the taskbar to restart Explorer, clear temp files,
free up memory and more. Results show up in a small card above the taskbar.
Nothing asks for admin rights.

![Seamless Taskbar Utilities preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-taskbar-utilities.png)

## Features
- **Restart Explorer.** Restarts the taskbar and desktop in one click.
- **Clean Temp.** Deletes the files in your temp folders that nothing is using
  right now, and can empty the Recycle Bin too.
- **Reduce Memory.** Asks your running apps to hand back memory they are not
  using, then shows how much came back.
- **Restart Graphics Driver.** Same as pressing Win + Ctrl + Shift + B. Handy
  when the screen goes black or flickers.
- **Get IP Address.** Lists your local addresses, and your public one if you
  turn that on. It can copy them for you.
- **Rebuild Icon and Thumbnail Cache.** Fixes blank or wrong icons and
  thumbnails without restarting Explorer.
- **Clean DNS Cache.** Clears saved website addresses when a site will not load
  after a change.
- **Your look.** The whole taskbar menu and the cards get the same font,
  blue icons and a blue to mauve gradient border, including the stock Task
  Manager and Taskbar settings items. The clock's right-click menu gets the
  same look, and the menus use the same blurred background as the taskbar.
  The default is FiraCode Nerd Font Medium on Catppuccin Mocha.

## Notes
- Every tool can be hidden or renamed in the settings.
- Public IP lookup is off by default. When on, it asks api.ipify.org.
- If the font is not installed, the menu and cards fall back to Segoe UI.

## Credits
Based on [Taskbar System Utilities](https://windhawk.net/mods/taskbar-system-utilities)
by Marco Petrucci, which adapts the menu hooks from Taskbar Restart Explorer by
Mgrmjp. MIT license.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- restartExplorer:
  - enabled: true
    $name: Show in menu
  - label: Restart Explorer
    $name: Menu text
  $name: Restart Explorer
  $description: Restarts the taskbar and desktop.
- cleanTemp:
  - enabled: true
    $name: Show in menu
  - label: Clean Temp
    $name: Menu text
  - cleanRecycleBin: false
    $name: Empty Recycle Bin too
    $description: When on, the Recycle Bin on every drive is emptied for good.
  - showCard: true
    $name: Show result card
    $description: When on, a card shows how many files went and how much space came back.
  $name: Clean Temp
  $description: Deletes temp files that nothing is using.
- reduceMemory:
  - enabled: true
    $name: Show in menu
  - label: Reduce Memory
    $name: Menu text
  - showCard: true
    $name: Show result card
    $description: When on, a card shows how much memory came back.
  $name: Reduce Memory
  $description: Asks running apps to give back memory they are not using.
- restartGpu:
  - enabled: true
    $name: Show in menu
  - label: Restart Graphics Driver
    $name: Menu text
  $name: Restart Graphics Driver
  $description: Presses Win + Ctrl + Shift + B for you.
- getIp:
  - enabled: true
    $name: Show in menu
  - label: Get IP Address
    $name: Menu text
  - queryPublicIp: false
    $name: Show public IP
    $description: When on, asks api.ipify.org for your public address. Off keeps everything on your PC.
  - copyToClipboard: false
    $name: Copy to clipboard
    $description: When on, the addresses are copied as soon as they show up.
  $name: Get IP Address
  $description: Shows your network addresses.
- rebuildCache:
  - enabled: true
    $name: Show in menu
  - label: Rebuild Icon & Thumbnail Cache
    $name: Menu text
  - showCard: true
    $name: Show result card
    $description: When on, a card shows what was cleared and rebuilt.
  $name: Rebuild Icon and Thumbnail Cache
  $description: Fixes blank or wrong icons and thumbnails.
- flushDns:
  - enabled: true
    $name: Show in menu
  - label: Clean DNS Cache
    $name: Menu text
  - showCard: true
    $name: Show result card
    $description: When on, a card confirms the cache was cleared.
  $name: Clean DNS Cache
  $description: Clears saved website addresses.
- look:
  - fontFamily: FiraCode Nerd Font
    $name: Font
    $description: Used for the menu items and the cards. Leave empty for Segoe UI. Falls back to Segoe UI if the font is not installed (Suggested: FiraCode Nerd Font).
  - fontWeight: medium
    $name: Font weight
    $description: How thick the text is (Suggested: Medium).
    $options:
    - light: Light
    - regular: Regular
    - medium: Medium
    - semibold: Semibold
    - bold: Bold
  - border: gradient
    $name: Border
    $description: The outline around the menu and each result card (Suggested: Gradient).
    $options:
    - gradient: Gradient
    - solid: One color
    - none: No border
  - gradientStart: "#89B4FA"
    $name: Gradient start color
    $description: Left side of the gradient, and the color for a one-color border. Hex like #89B4FA (Suggested: Mocha blue #89B4FA).
  - gradientEnd: "#CBA6F7"
    $name: Gradient end color
    $description: Right side of the gradient. Hex like #CBA6F7 (Suggested: Mocha mauve #CBA6F7).
  - borderWidth: 2
    $name: Border width
    $description: 1 to 4 pixels (Suggested: 2).
  - matchTaskbar: true
    $name: Match the taskbar background
    $description: When on, the menus and cards use the exact same blurred background as your taskbar, so a taskbar theme change carries over. When off, or if the taskbar background is not found, they use the Mocha background below (Suggested: on).
  - cardOpacity: 90
    $name: Card background strength
    $description: How solid the Mocha background of the menu and cards is when they do not match the taskbar, 85 to 100. Higher hides more of what is behind (Suggested: 90).
  - colorIcons: true
    $name: Blue menu icons
    $description: When on, every menu icon uses Mocha blue, the stock ones too. When off, they match the menu text.
  $name: Look
  $description: Font, border and colors for the menu items and the result cards.
*/
// ==/WindhawkModSettings==

// clang-format off
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iphlpapi.h>
#include <psapi.h>
#include <roapi.h>
#include <shellapi.h>
#include <wininet.h>
// clang-format on

#include <windhawk_utils.h>

#undef GetCurrentTime

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.h>
#include <winrt/base.h>

#include <atomic>
#include <cctype>
#include <cwchar>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace wf = winrt::Windows::Foundation;
namespace wu = winrt::Windows::UI;
namespace wut = winrt::Windows::UI::Text;
namespace wux = winrt::Windows::UI::Xaml;
namespace wuxc = winrt::Windows::UI::Xaml::Controls;
namespace wuxcp = winrt::Windows::UI::Xaml::Controls::Primitives;
namespace wuxi = winrt::Windows::UI::Xaml::Input;
namespace wuxm = winrt::Windows::UI::Xaml::Media;

// ============================================================================
// Global State & Thread / Window Synchronization
// ============================================================================

struct ModSettings {
    bool showRestartExplorer = true;
    std::wstring textRestartExplorer = L"Restart Explorer";

    bool showCleanTemp = true;
    std::wstring textCleanTemp = L"Clean Temp";
    bool cleanRecycleBin = false;
    bool notifyCleanTemp = true;

    bool showReduceMemory = true;
    std::wstring textReduceMemory = L"Reduce Memory";
    bool notifyReduceMemory = true;

    bool showRestartGpu = true;
    std::wstring textRestartGpu = L"Restart Graphics Driver";

    bool showGetIp = true;
    std::wstring textGetIp = L"Get IP Address";
    bool queryPublicIp = false;
    bool copyIpToClipboard = false;

    bool showRebuildCache = true;
    std::wstring textRebuildCache = L"Rebuild Icon & Thumbnail Cache";
    bool notifyRebuildCache = true;

    bool showFlushDns = true;
    std::wstring textFlushDns = L"Clean DNS Cache";
    bool notifyFlushDns = true;

    std::wstring fontFamily = L"FiraCode Nerd Font";
    uint16_t fontWeight = 500;
    int borderStyle = 0;  // 0 gradient, 1 solid, 2 none
    wu::Color gradientStart{255, 0x89, 0xB4, 0xFA};
    wu::Color gradientEnd{255, 0xCB, 0xA6, 0xF7};
    int borderWidth = 2;
    int cardOpacity = 90;
    bool matchTaskbar = true;
    bool colorIcons = true;
};

std::mutex g_settingsMutex;
ModSettings g_settings;

static constexpr wchar_t kGuardItemName[] = L"WindhawkSystemUtilitiesGuardItem";

std::atomic<bool> g_taskbarViewModuleHooked{false};
std::atomic<bool> g_restartStarted{false};
std::atomic<bool> g_unloading{false};

thread_local int g_taskbarSettingsMenuDepth = 0;
thread_local bool g_currentMenuInjected = false;

// Accessed only on the taskbar UI thread
winrt::weak_ref<wux::FrameworkElement> g_lastTargetWeak;
winrt::weak_ref<wuxc::Flyout> g_activeFlyoutWeak;
winrt::weak_ref<wuxc::Button> g_activeOkButtonWeak;
winrt::event_token g_activeOkClickToken{};

std::mutex g_threadsMutex;
std::vector<HANDLE> g_threads;
std::mutex g_dispatchMutex;

ModSettings GetSettingsSnapshot() {
    std::lock_guard<std::mutex> lock(g_settingsMutex);
    return g_settings;
}

HWND FindCurrentProcessTaskbarWnd() {
    HWND hTaskbarWnd = nullptr;
    EnumWindows(
        [](HWND hWnd, LPARAM lParam) -> BOOL {
            DWORD dwProcessId = 0;
            if (GetWindowThreadProcessId(hWnd, &dwProcessId) &&
                dwProcessId == GetCurrentProcessId()) {
                WCHAR szClassName[32];
                if (GetClassNameW(hWnd, szClassName, ARRAYSIZE(szClassName)) &&
                    _wcsicmp(szClassName, L"Shell_TrayWnd") == 0) {
                    *reinterpret_cast<HWND*>(lParam) = hWnd;
                    return FALSE;
                }
            }
            return TRUE;
        },
        reinterpret_cast<LPARAM>(&hTaskbarWnd));
    return hTaskbarWnd;
}

bool RunFromWindowThread(HWND hWnd, std::function<void()> proc) {
    DWORD dwThreadId = GetWindowThreadProcessId(hWnd, nullptr);
    if (!dwThreadId) {
        return false;
    }

    if (dwThreadId == GetCurrentThreadId()) {
        proc();
        return true;
    }

    static const UINT runMsg =
        RegisterWindowMessageW(L"Windhawk_RunFromWindowThread_" WH_MOD_ID);

    struct CallWndProcParam {
        std::function<void()>* proc;
    };

    HHOOK hook = SetWindowsHookExW(
        WH_CALLWNDPROC,
        [](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT {
            if (nCode == HC_ACTION) {
                const CWPSTRUCT* cwp =
                    reinterpret_cast<const CWPSTRUCT*>(lParam);
                if (cwp->message == runMsg) {
                    auto* param =
                        reinterpret_cast<CallWndProcParam*>(cwp->lParam);
                    (*param->proc)();
                }
            }
            return CallNextHookEx(nullptr, nCode, wParam, lParam);
        },
        nullptr, dwThreadId);
    if (!hook) {
        return false;
    }

    CallWndProcParam param{&proc};
    SendMessageW(hWnd, runMsg, 0, reinterpret_cast<LPARAM>(&param));
    UnhookWindowsHookEx(hook);
    return true;
}

template <typename F>
void RunAsyncTracked(F&& fn) {
    std::lock_guard<std::mutex> lock(g_threadsMutex);
    if (g_unloading.load()) {
        return;
    }

    for (auto it = g_threads.begin(); it != g_threads.end();) {
        if (WaitForSingleObject(*it, 0) == WAIT_OBJECT_0) {
            CloseHandle(*it);
            it = g_threads.erase(it);
        } else {
            ++it;
        }
    }

    auto task = std::make_unique<std::function<void()>>(std::forward<F>(fn));
    HANDLE thread = CreateThread(
        nullptr, 0,
        [](void* p) -> DWORD {
            std::unique_ptr<std::function<void()>> task(
                static_cast<std::function<void()>*>(p));
            try {
                (*task)();
            } catch (...) {
                Wh_Log(L"Background task threw an exception");
            }
            return 0;
        },
        task.get(), 0, nullptr);

    if (thread) {
        task.release();
        g_threads.push_back(thread);
    }
}

// ============================================================================
// Native XAML Flyout Card Builder (Theme-Aware & Unload-Safe)
// ============================================================================

using DialogRow = std::pair<std::wstring, std::wstring>;

// Catppuccin Mocha
constexpr wu::Color kBase{255, 0x1E, 0x1E, 0x2E};
constexpr wu::Color kCrust{255, 0x11, 0x11, 0x1B};
constexpr wu::Color kText{255, 0xCD, 0xD6, 0xF4};
constexpr wu::Color kSubtext{255, 0xA6, 0xAD, 0xC8};
constexpr wu::Color kBlue{255, 0x89, 0xB4, 0xFA};
constexpr wu::Color kLavender{255, 0xB4, 0xBE, 0xFE};
constexpr wu::Color kMauve{255, 0xCB, 0xA6, 0xF7};
constexpr wu::Color kGreen{255, 0xA6, 0xE3, 0xA1};
constexpr wu::Color kRed{255, 0xF3, 0x8B, 0xA8};

wuxm::SolidColorBrush MakeBrush(wu::Color c, uint8_t alpha = 255) {
    c.A = alpha;
    return wuxm::SolidColorBrush(c);
}

wuxm::FontFamily MakeFont(const ModSettings& cfg) {
    if (cfg.fontFamily.empty()) {
        return wuxm::FontFamily(L"Segoe UI Variable Text, Segoe UI");
    }
    return wuxm::FontFamily(winrt::hstring(
        cfg.fontFamily + L", Segoe UI Variable Text, Segoe UI"));
}

wuxc::FontIcon CreateFluentIcon(const wchar_t* glyph, double size = 16.0) {
    wuxc::FontIcon icon;
    icon.FontFamily(wuxm::FontFamily(L"Segoe Fluent Icons"));
    icon.Glyph(glyph);
    icon.FontSize(size);
    return icon;
}

wuxc::TextBlock MakeText(const std::wstring& value,
                         double size,
                         wu::Color color,
                         const ModSettings& cfg) {
    wuxc::TextBlock block;
    block.Text(value);
    block.FontSize(size);
    block.FontFamily(MakeFont(cfg));
    block.FontWeight(wut::FontWeight{cfg.fontWeight});
    block.Foreground(MakeBrush(color));
    block.VerticalAlignment(wux::VerticalAlignment::Center);
    return block;
}

wuxm::Brush MakeBorderBrush(const ModSettings& cfg) {
    if (cfg.borderStyle == 1) {
        return MakeBrush(cfg.gradientStart);
    }
    wuxm::LinearGradientBrush grad;
    grad.StartPoint({0, 0.5f});
    grad.EndPoint({1, 0.5f});
    wuxm::GradientStop a;
    a.Color(cfg.gradientStart);
    a.Offset(0.0);
    wuxm::GradientStop b;
    b.Color(cfg.gradientEnd);
    b.Offset(1.0);
    grad.GradientStops().Append(a);
    grad.GradientStops().Append(b);
    return grad;
}

// The taskbar's own background (Rectangle#BackgroundFill inside
// TaskbarBackground). The taskbar styler paints it, so handing the same brush
// to the menus and cards keeps one material for the whole bar.
winrt::weak_ref<winrt::Windows::UI::Xaml::Shapes::Rectangle> g_taskbarFillWeak;

winrt::Windows::UI::Xaml::Shapes::Rectangle FindTaskbarFill(
    wux::DependencyObject const& root) {
    std::vector<std::pair<wux::DependencyObject, int>> stack{{root, 0}};
    int visited = 0;
    while (!stack.empty() && visited++ < 4000) {
        auto [node, depth] = stack.back();
        stack.pop_back();
        if (auto rect = node.try_as<winrt::Windows::UI::Xaml::Shapes::Rectangle>()) {
            if (rect.Name() == L"BackgroundFill") {
                return rect;
            }
        }
        if (depth >= 30) {
            continue;
        }
        int n = wuxm::VisualTreeHelper::GetChildrenCount(node);
        for (int i = n - 1; i >= 0; i--) {
            stack.push_back({wuxm::VisualTreeHelper::GetChild(node, i), depth + 1});
        }
    }
    return nullptr;
}

wuxm::Brush TaskbarMaterial(wux::FrameworkElement const& anchor) {
    try {
        auto rect = g_taskbarFillWeak.get();
        if (!rect) {
            for (auto el : {anchor, g_lastTargetWeak.get()}) {
                if (!el || !el.XamlRoot()) {
                    continue;
                }
                if (auto content = el.XamlRoot().Content()) {
                    rect = FindTaskbarFill(content);
                    if (rect) {
                        g_taskbarFillWeak = rect;
                        break;
                    }
                }
            }
        }
        if (rect) {
            return rect.Fill();
        }
    } catch (...) {
    }
    return nullptr;
}

// Menu and card background: the taskbar's material when "Match the taskbar"
// is on and the taskbar is found, else the Mocha acrylic.
wuxm::Brush MenuBackground(wux::FrameworkElement const& anchor,
                           const ModSettings& cfg) {
    if (cfg.matchTaskbar) {
        auto brush = TaskbarMaterial(anchor);
        Wh_SetIntValue(L"menuMaterialFromTaskbar", brush ? 1 : 0);
        if (brush) {
            return brush;
        }
    }
    wuxm::AcrylicBrush acrylic;
    acrylic.BackgroundSource(wuxm::AcrylicBackgroundSource::HostBackdrop);
    acrylic.TintColor(kBase);
    acrylic.TintOpacity(cfg.cardOpacity / 100.0);
    acrylic.FallbackColor(kBase);
    return acrylic;
}

void CloseActiveFlyoutOnUIThread() {
    try {
        if (auto btn = g_activeOkButtonWeak.get()) {
            if (g_activeOkClickToken) {
                btn.Click(g_activeOkClickToken);
            }
        }
    } catch (...) {
    }
    g_activeOkButtonWeak = nullptr;
    g_activeOkClickToken = {};

    try {
        if (auto fl = g_activeFlyoutWeak.get()) {
            fl.Hide();
        }
    } catch (...) {
    }
    g_activeFlyoutWeak = nullptr;
}

void ShowModernXAMLCardOnUIThread(const std::wstring& titleText,
                                  const wchar_t* glyphIcon,
                                  const std::vector<DialogRow>& rows,
                                  const std::wstring& footerNote = L"",
                                  bool failed = false) {
    if (g_unloading.load()) {
        return;
    }

    try {
        CloseActiveFlyoutOnUIThread();

        auto target = g_lastTargetWeak.get();
        if (!target || !target.XamlRoot()) {
            Wh_Log(L"Cannot display XAML card: target or XamlRoot unavailable");
            return;
        }

        auto cfg = GetSettingsSnapshot();
        const double radius = 12.0;

        wuxc::Flyout flyout;
        flyout.ShouldConstrainToRootBounds(false);
        flyout.Placement(wuxcp::FlyoutPlacementMode::Top);
        flyout.XamlRoot(target.XamlRoot());

        // Clear the presenter so only our card draws, and match its corners
        // so the presenter does not clip the border.
        wux::Interop::TypeName presenterType{
            winrt::hstring{winrt::name_of<wuxc::FlyoutPresenter>()},
            wux::Interop::TypeKind::Metadata};
        wux::Style presenterStyle(presenterType);
        presenterStyle.Setters().Append(
            wux::Setter(wuxc::Control::PaddingProperty(),
                        winrt::box_value(wux::Thickness{0, 0, 0, 0})));
        presenterStyle.Setters().Append(
            wux::Setter(wuxc::Control::BorderThicknessProperty(),
                        winrt::box_value(wux::Thickness{0, 0, 0, 0})));
        presenterStyle.Setters().Append(wux::Setter(
            wuxc::Control::BackgroundProperty(), MakeBrush(kBase, 0)));
        presenterStyle.Setters().Append(wux::Setter(
            wuxc::Control::CornerRadiusProperty(),
            winrt::box_value(wux::CornerRadius{radius, radius, radius, radius})));
        flyout.FlyoutPresenterStyle(presenterStyle);

        wuxc::Border card;
        card.Background(MenuBackground(target, cfg));
        if (cfg.borderStyle != 2) {
            double w = cfg.borderWidth;
            card.BorderBrush(MakeBorderBrush(cfg));
            card.BorderThickness({w, w, w, w});
        }
        card.CornerRadius({radius, radius, radius, radius});
        card.Padding({22, 20, 22, 18});
        card.Width(380);

        wuxc::StackPanel mainStack;
        mainStack.Spacing(14);

        // Header: tinted icon badge and title.
        wuxc::StackPanel headerStack;
        headerStack.Orientation(wuxc::Orientation::Horizontal);
        headerStack.Spacing(12);

        wuxc::Border iconBadge;
        iconBadge.Background(MakeBrush(kBlue, 0x26));
        iconBadge.CornerRadius({8, 8, 8, 8});
        iconBadge.Width(36);
        iconBadge.Height(36);

        auto headerIcon = CreateFluentIcon(glyphIcon, 18.0);
        headerIcon.Foreground(MakeBrush(kBlue));
        headerIcon.HorizontalAlignment(wux::HorizontalAlignment::Center);
        headerIcon.VerticalAlignment(wux::VerticalAlignment::Center);
        iconBadge.Child(headerIcon);
        headerStack.Children().Append(iconBadge);
        headerStack.Children().Append(MakeText(titleText, 16, kText, cfg));
        mainStack.Children().Append(headerStack);

        // Rows of label and value.
        wuxc::Border metricsBox;
        metricsBox.Background(MakeBrush({255, 0x31, 0x32, 0x44}, 0x99));
        metricsBox.BorderBrush(MakeBrush({255, 0x45, 0x47, 0x5A}, 0x99));
        metricsBox.BorderThickness({1, 1, 1, 1});
        metricsBox.CornerRadius({8, 8, 8, 8});
        metricsBox.Padding({14, 12, 14, 12});

        wuxc::StackPanel rowsStack;
        rowsStack.Spacing(8);

        for (const auto& [label, val] : rows) {
            wuxc::Grid rowGrid;
            wuxc::ColumnDefinition col0;
            col0.Width(wux::GridLength{1.0, wux::GridUnitType::Auto});
            wuxc::ColumnDefinition col1;
            col1.Width(wux::GridLength{1.0, wux::GridUnitType::Star});
            rowGrid.ColumnDefinitions().Append(col0);
            rowGrid.ColumnDefinitions().Append(col1);

            auto lblBlock = MakeText(label, 13, kSubtext, cfg);
            lblBlock.Margin({0, 0, 16, 0});
            rowGrid.Children().Append(lblBlock);
            wuxc::Grid::SetColumn(lblBlock, 0);

            auto valBlock = MakeText(val, 13, kText, cfg);
            valBlock.HorizontalAlignment(wux::HorizontalAlignment::Right);
            valBlock.TextAlignment(wux::TextAlignment::Right);
            valBlock.TextWrapping(wux::TextWrapping::Wrap);
            valBlock.IsTextSelectionEnabled(true);
            rowGrid.Children().Append(valBlock);
            wuxc::Grid::SetColumn(valBlock, 1);

            rowsStack.Children().Append(rowGrid);
        }

        metricsBox.Child(rowsStack);
        mainStack.Children().Append(metricsBox);

        // Footer: status note and OK button.
        wuxc::Grid footerGrid;

        if (!footerNote.empty()) {
            wuxc::StackPanel noteStack;
            noteStack.Orientation(wuxc::Orientation::Horizontal);
            noteStack.Spacing(6);
            noteStack.VerticalAlignment(wux::VerticalAlignment::Center);

            auto noteIcon =
                CreateFluentIcon(failed ? L"\xE783" : L"\xE73E", 13.0);
            noteIcon.Foreground(MakeBrush(failed ? kRed : kGreen));
            noteStack.Children().Append(noteIcon);
            noteStack.Children().Append(MakeText(footerNote, 12, kSubtext, cfg));

            footerGrid.Children().Append(noteStack);
        }

        wuxc::Button okButton;
        okButton.Content(winrt::box_value(L"OK"));
        okButton.FontFamily(MakeFont(cfg));
        okButton.FontWeight(wut::FontWeight{cfg.fontWeight});
        okButton.Width(76);
        okButton.Height(30);
        okButton.CornerRadius({8, 8, 8, 8});
        okButton.BorderThickness({0, 0, 0, 0});
        okButton.HorizontalAlignment(wux::HorizontalAlignment::Right);
        // Lightweight styling so hover and press stay Mocha instead of the
        // system grey: blue at rest, lavender on hover, mauve when pressed.
        auto res = okButton.Resources();
        auto put = [&](const wchar_t* key, wuxm::SolidColorBrush brush) {
            res.Insert(winrt::box_value(key), brush);
        };
        put(L"ButtonBackground", MakeBrush(kBlue));
        put(L"ButtonBackgroundPointerOver", MakeBrush(kLavender));
        put(L"ButtonBackgroundPressed", MakeBrush(kMauve));
        put(L"ButtonForeground", MakeBrush(kCrust));
        put(L"ButtonForegroundPointerOver", MakeBrush(kCrust));
        put(L"ButtonForegroundPressed", MakeBrush(kCrust));
        put(L"ButtonBorderBrush", MakeBrush(kBlue, 0));
        put(L"ButtonBorderBrushPointerOver", MakeBrush(kBlue, 0));
        put(L"ButtonBorderBrushPressed", MakeBrush(kBlue, 0));
        okButton.Background(MakeBrush(kBlue));
        okButton.Foreground(MakeBrush(kCrust));

        winrt::weak_ref<wuxc::Flyout> weakFlyout(flyout);
        g_activeFlyoutWeak = flyout;
        g_activeOkButtonWeak = okButton;
        g_activeOkClickToken = okButton.Click(
            [weakFlyout](wf::IInspectable const&, wux::RoutedEventArgs const&) {
                if (auto fl = weakFlyout.get()) {
                    fl.Hide();
                }
            });

        footerGrid.Children().Append(okButton);
        mainStack.Children().Append(footerGrid);

        card.Child(mainStack);
        flyout.Content(card);
        flyout.ShowAt(target);
    } catch (...) {
        Wh_Log(L"Failed to display XAML Flyout card");
    }
}

void DispatchXAMLCardSync(const std::wstring& titleText,
                          const wchar_t* glyphIcon,
                          const std::vector<DialogRow>& rows,
                          const std::wstring& footerNote = L"",
                          bool failed = false) {
    std::lock_guard<std::mutex> lock(g_dispatchMutex);
    if (g_unloading.load()) {
        return;
    }

    HWND hTaskbarWnd = FindCurrentProcessTaskbarWnd();
    if (!hTaskbarWnd) {
        return;
    }

    RunFromWindowThread(hTaskbarWnd, [&]() {
        if (!g_unloading.load()) {
            ShowModernXAMLCardOnUIThread(titleText, glyphIcon, rows,
                                         footerNote, failed);
        }
    });
}

bool CopyTextToClipboard(const std::wstring& text) {
    HWND tempOwner = CreateWindowExW(0, L"STATIC", nullptr, 0, 0, 0, 0, 0,
                                     HWND_MESSAGE, nullptr, nullptr, nullptr);
    HWND owner = tempOwner ? tempOwner : GetShellWindow();

    bool opened = false;
    for (int i = 0; i < 6 && !opened; ++i) {
        opened = OpenClipboard(owner) != FALSE;
        if (!opened) {
            Sleep(25);
        }
    }

    bool copied = false;
    if (opened) {
        EmptyClipboard();
        size_t byteSize = (text.size() + 1) * sizeof(wchar_t);
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, byteSize);
        if (hMem) {
            if (void* ptr = GlobalLock(hMem)) {
                memcpy(ptr, text.c_str(), byteSize);
                GlobalUnlock(hMem);
                if (SetClipboardData(CF_UNICODETEXT, hMem)) {
                    copied = true;
                } else {
                    GlobalFree(hMem);
                }
            } else {
                GlobalFree(hMem);
            }
        }
        CloseClipboard();
    }

    if (tempOwner) {
        DestroyWindow(tempOwner);
    }
    return copied;
}

// ============================================================================
// Native Action Implementations
// ============================================================================

// 1. Restart Explorer
void OnRestartExplorerClick(wf::IInspectable const&,
                            wux::RoutedEventArgs const&) {
    if (g_restartStarted.exchange(true)) {
        return;
    }

    wchar_t sysDir[MAX_PATH] = {};
    if (GetSystemDirectoryW(sysDir, MAX_PATH) == 0) {
        g_restartStarted = false;
        return;
    }

    std::wstring cmdPath = std::wstring(sysDir) + L"\\cmd.exe";
    wchar_t cmdArgs[] =
        L"/d /c \"taskkill /f /im explorer.exe >nul 2>nul & start \"\" "
        L"explorer.exe\"";

    STARTUPINFOW si = {};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    PROCESS_INFORMATION pi = {};

    if (CreateProcessW(cmdPath.c_str(), cmdArgs, nullptr, nullptr, FALSE,
                       CREATE_NO_WINDOW | CREATE_NEW_PROCESS_GROUP, nullptr,
                       nullptr, &si, &pi)) {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    } else {
        g_restartStarted = false;
    }
}

// 2. Clean Temp
struct CleanStats {
    DWORD filesDeleted = 0;
    DWORD filesSkipped = 0;
    ULONGLONG bytesFreed = 0;
};

std::wstring ToExtendedPath(const std::wstring& path) {
    if (path.rfind(L"\\\\?\\", 0) == 0) {
        return path;
    }
    return L"\\\\?\\" + path;
}

bool IsSafeCleanTarget(const std::wstring& path) {
    if (path.size() < 4) {
        return false;
    }

    auto equalsEnv = [&](const wchar_t* var) {
        wchar_t buf[MAX_PATH] = {};
        DWORD n = GetEnvironmentVariableW(var, buf, MAX_PATH);
        if (n == 0 || n >= MAX_PATH) {
            return false;
        }
        std::wstring v(buf);
        while (!v.empty() && v.back() == L'\\') {
            v.pop_back();
        }
        return _wcsicmp(v.c_str(), path.c_str()) == 0;
    };

    return !(equalsEnv(L"USERPROFILE") || equalsEnv(L"SystemRoot") ||
             equalsEnv(L"SystemDrive"));
}

void CleanDirectoryRecursive(const std::wstring& dirPath,
                             bool removeRoot,
                             CleanStats& stats) {
    if (g_unloading.load()) {
        return;
    }

    std::wstring searchMask = dirPath + L"\\*";
    WIN32_FIND_DATAW fd;
    HANDLE hFind = FindFirstFileW(searchMask.c_str(), &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        if (wcscmp(fd.cFileName, L".") == 0 ||
            wcscmp(fd.cFileName, L"..") == 0) {
            continue;
        }

        std::wstring fullPath = dirPath + L"\\" + fd.cFileName;

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)) {
                CleanDirectoryRecursive(fullPath, true, stats);
            }
        } else {
            ULONGLONG fileSize =
                (static_cast<ULONGLONG>(fd.nFileSizeHigh) << 32) |
                fd.nFileSizeLow;
            if (DeleteFileW(fullPath.c_str())) {
                stats.filesDeleted++;
                stats.bytesFreed += fileSize;
            } else {
                stats.filesSkipped++;
            }
        }
    } while (!g_unloading.load() && FindNextFileW(hFind, &fd));

    FindClose(hFind);

    if (removeRoot && !g_unloading.load()) {
        RemoveDirectoryW(dirPath.c_str());
    }
}

void OnCleanTempClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    RunAsyncTracked([]() {
        auto cfg = GetSettingsSnapshot();
        CleanStats stats;

        wchar_t tempPath[MAX_PATH] = {};
        if (GetTempPathW(MAX_PATH, tempPath) > 0) {
            std::wstring userTemp(tempPath);
            while (!userTemp.empty() && userTemp.back() == L'\\') {
                userTemp.pop_back();
            }
            if (IsSafeCleanTarget(userTemp)) {
                CleanDirectoryRecursive(ToExtendedPath(userTemp), false, stats);
            } else {
                Wh_Log(L"Temp path rejected by safety check: %s",
                       userTemp.c_str());
            }
        }

        wchar_t winDir[MAX_PATH] = {};
        if (GetWindowsDirectoryW(winDir, MAX_PATH) >= 3) {
            std::wstring sysTemp = std::wstring(winDir) + L"\\Temp";
            CleanDirectoryRecursive(ToExtendedPath(sysTemp), false, stats);
        }

        if (cfg.cleanRecycleBin && !g_unloading.load()) {
            SHEmptyRecycleBinW(
                nullptr, nullptr,
                SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
        }

        if (cfg.notifyCleanTemp && !g_unloading.load()) {
            double mbFreed =
                static_cast<double>(stats.bytesFreed) / (1024.0 * 1024.0);
            wchar_t mbBuf[64] = {};
            swprintf_s(mbBuf, L"%.2f MB", mbFreed);

            std::vector<DialogRow> rows = {
                {L"Deleted files", std::to_wstring(stats.filesDeleted)},
                {L"Locked / skipped", std::to_wstring(stats.filesSkipped)},
                {L"Space recovered", mbBuf},
            };

            std::wstring footer =
                (stats.filesDeleted == 0 && stats.filesSkipped == 0)
                    ? L"No removable temp files found"
                    : L"Cleanup completed";

            DispatchXAMLCardSync(L"Temporary Files Cleaned", L"\xE74D", rows,
                                 footer);
        }
    });
}

// 3. Reduce Memory
void OnReduceMemoryClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    RunAsyncTracked([]() {
        auto cfg = GetSettingsSnapshot();

        MEMORYSTATUSEX memBefore = {sizeof(memBefore)};
        GlobalMemoryStatusEx(&memBefore);

        std::vector<DWORD> pids(1024);
        DWORD bytesReturned = 0;
        while (K32EnumProcesses(pids.data(),
                                static_cast<DWORD>(pids.size() * sizeof(DWORD)),
                                &bytesReturned)) {
            if (bytesReturned < pids.size() * sizeof(DWORD)) {
                break;
            }
            pids.resize(pids.size() * 2);
        }

        DWORD currentPid = GetCurrentProcessId();
        DWORD count = bytesReturned / sizeof(DWORD);
        DWORD trimmedCount = 0;
        DWORD skippedCount = 0;

        for (DWORD i = 0; i < count && !g_unloading.load(); ++i) {
            if (pids[i] == 0 || pids[i] == 4 || pids[i] == currentPid) {
                continue;
            }

            HANDLE hProc = OpenProcess(
                PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_SET_QUOTA, FALSE,
                pids[i]);
            if (hProc) {
                if (K32EmptyWorkingSet(hProc)) {
                    trimmedCount++;
                } else {
                    skippedCount++;
                }
                CloseHandle(hProc);
            } else {
                skippedCount++;
            }
        }

        if (cfg.notifyReduceMemory && !g_unloading.load()) {
            MEMORYSTATUSEX memAfter = {sizeof(memAfter)};
            GlobalMemoryStatusEx(&memAfter);

            double freedMb = 0.0;
            if (memAfter.ullAvailPhys > memBefore.ullAvailPhys) {
                freedMb = static_cast<double>(memAfter.ullAvailPhys -
                                              memBefore.ullAvailPhys) /
                          (1024.0 * 1024.0);
            }
            double availGb = static_cast<double>(memAfter.ullAvailPhys) /
                             (1024.0 * 1024.0 * 1024.0);

            wchar_t freedBuf[64] = {};
            swprintf_s(freedBuf, L"%.1f MB", freedMb);

            wchar_t availBuf[64] = {};
            swprintf_s(availBuf, L"%.2f GB (%lu%% used)", availGb,
                       memAfter.dwMemoryLoad);

            std::vector<DialogRow> rows = {
                {L"Processes optimized", std::to_wstring(trimmedCount)},
                {L"Processes skipped", std::to_wstring(skippedCount)},
                {L"RAM recovered", freedBuf},
                {L"Available RAM", availBuf},
            };

            DispatchXAMLCardSync(L"Memory Optimized", L"\xE950", rows,
                                 L"Working sets trimmed");
        }
    });
}

// 4. Restart Graphics Driver
void OnRestartGpuClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    RunAsyncTracked([]() {
        Sleep(150);
        if (g_unloading.load()) {
            return;
        }

        static constexpr WORD kKeys[] = {VK_LWIN, VK_CONTROL, VK_SHIFT, 'B'};
        INPUT inputs[8] = {};

        for (size_t i = 0; i < 4; ++i) {
            inputs[i].type = INPUT_KEYBOARD;
            inputs[i].ki.wVk = kKeys[i];

            inputs[i + 4].type = INPUT_KEYBOARD;
            inputs[i + 4].ki.wVk = kKeys[3 - i];
            inputs[i + 4].ki.dwFlags = KEYEVENTF_KEYUP;
        }

        if (SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT)) !=
            ARRAYSIZE(inputs)) {
            Wh_Log(L"SendInput failed: %lu", GetLastError());
        }
    });
}

// 5. Get IP (Preferred Local Adapters + Optional Public IP)
std::vector<DialogRow> GetLocalAdapterIPs(std::wstring& clipboardText) {
    std::vector<DialogRow> rows;
    clipboardText.clear();

    ULONG flags = GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST |
                  GAA_FLAG_SKIP_DNS_SERVER;
    ULONG outBufLen = 15000;
    std::vector<BYTE> buffer(outBufLen);

    DWORD dwRetVal = GetAdaptersAddresses(
        AF_UNSPEC, flags, nullptr,
        reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data()), &outBufLen);
    if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
        buffer.resize(outBufLen);
        dwRetVal = GetAdaptersAddresses(
            AF_UNSPEC, flags, nullptr,
            reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data()), &outBufLen);
    }

    if (dwRetVal != NO_ERROR) {
        rows.emplace_back(L"Status", L"Failed to query adapters");
        return rows;
    }

    for (auto* adapter = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data());
         adapter != nullptr; adapter = adapter->Next) {
        if (adapter->OperStatus != IfOperStatusUp ||
            adapter->IfType == IF_TYPE_SOFTWARE_LOOPBACK) {
            continue;
        }

        bool hasIpv4 = false;
        bool hasIpv6 = false;

        for (auto* unicast = adapter->FirstUnicastAddress; unicast != nullptr;
             unicast = unicast->Next) {
            if (unicast->DadState != IpDadStatePreferred) {
                continue;
            }

            SOCKADDR* addr = unicast->Address.lpSockaddr;
            if (!addr) {
                continue;
            }

            wchar_t ipStr[INET6_ADDRSTRLEN] = {};
            if (addr->sa_family == AF_INET && !hasIpv4) {
                auto* sa4 = reinterpret_cast<sockaddr_in*>(addr);
                const auto* bytes =
                    reinterpret_cast<const uint8_t*>(&sa4->sin_addr);
                // Skip addresses APIPA 169.254.0.0/16
                if (bytes[0] == 169 && bytes[1] == 254) {
                    continue;
                }
                if (InetNtopW(AF_INET, &sa4->sin_addr, ipStr,
                              ARRAYSIZE(ipStr))) {
                    hasIpv4 = true;
                }
            } else if (addr->sa_family == AF_INET6 && !hasIpv6) {
                auto* sa6 = reinterpret_cast<sockaddr_in6*>(addr);
                // Skip link-local addresses (fe80::/10)
                if (IN6_IS_ADDR_LINKLOCAL(&sa6->sin6_addr)) {
                    continue;
                }
                if (InetNtopW(AF_INET6, &sa6->sin6_addr, ipStr,
                              ARRAYSIZE(ipStr))) {
                    hasIpv6 = true;
                }
            }

            if (ipStr[0] != L'\0') {
                std::wstring label =
                    adapter->FriendlyName ? adapter->FriendlyName : L"Adapter";
                if (addr->sa_family == AF_INET6) {
                    label += L" (IPv6)";
                }
                rows.emplace_back(label, ipStr);
                if (!clipboardText.empty()) {
                    clipboardText += L"\r\n";
                }
                clipboardText += label + L": " + ipStr;
            }
        }
    }

    if (rows.empty()) {
        rows.emplace_back(L"Network", L"Disconnected");
    }

    return rows;
}

std::mutex g_inetMutex;
HINTERNET g_activeInternet = nullptr;

void CancelActivePublicIpRequest() {
    std::lock_guard<std::mutex> lock(g_inetMutex);
    if (g_activeInternet) {
        InternetCloseHandle(g_activeInternet);
        g_activeInternet = nullptr;
    }
}

std::wstring GetPublicIP() {
    std::wstring result = L"Unavailable";
    HINTERNET hInternet =
        InternetOpenW(L"SeamlessTaskbarUtilities/" WH_MOD_VERSION,
                      INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
    if (!hInternet) {
        return result;
    }

    {
        std::lock_guard<std::mutex> lock(g_inetMutex);
        if (g_unloading.load()) {
            InternetCloseHandle(hInternet);
            return result;
        }
        g_activeInternet = hInternet;
    }

    DWORD timeout = 2500;
    InternetSetOptionW(hInternet, INTERNET_OPTION_CONNECT_TIMEOUT, &timeout,
                       sizeof(timeout));
    InternetSetOptionW(hInternet, INTERNET_OPTION_RECEIVE_TIMEOUT, &timeout,
                       sizeof(timeout));

    HINTERNET hConnect =
        InternetOpenUrlW(hInternet, L"https://api.ipify.org", nullptr, 0,
                         INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE |
                             INTERNET_FLAG_SECURE,
                         0);
    if (hConnect) {
        char buffer[64] = {};
        DWORD bytesRead = 0;
        if (!g_unloading.load() &&
            InternetReadFile(hConnect, buffer, sizeof(buffer) - 1,
                             &bytesRead) &&
            bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::string raw(buffer);
            while (!raw.empty() &&
                   std::isspace(static_cast<unsigned char>(raw.back()))) {
                raw.pop_back();
            }

            in_addr addr4;
            in6_addr addr6;
            if (InetPtonA(AF_INET, raw.c_str(), &addr4) == 1 ||
                InetPtonA(AF_INET6, raw.c_str(), &addr6) == 1) {
                wchar_t wbuffer[64] = {};
                MultiByteToWideChar(CP_UTF8, 0, raw.c_str(), -1, wbuffer, 64);
                result = wbuffer;
            }
        }
        InternetCloseHandle(hConnect);
    }

    {
        std::lock_guard<std::mutex> lock(g_inetMutex);
        if (g_activeInternet == hInternet) {
            g_activeInternet = nullptr;
            InternetCloseHandle(hInternet);
        }
    }
    return result;
}

void OnGetIpClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    RunAsyncTracked([]() {
        auto cfg = GetSettingsSnapshot();

        std::wstring clipboardText;
        std::vector<DialogRow> rows = GetLocalAdapterIPs(clipboardText);

        if (cfg.queryPublicIp && !g_unloading.load()) {
            std::wstring publicIp = GetPublicIP();
            rows.insert(rows.begin(), {L"Public IP", publicIp});
            if (!clipboardText.empty()) {
                clipboardText =
                    L"Public IP: " + publicIp + L"\r\n" + clipboardText;
            } else {
                clipboardText = L"Public IP: " + publicIp;
            }
        }

        if (g_unloading.load()) {
            return;
        }

        std::wstring footer;
        if (cfg.copyIpToClipboard && !clipboardText.empty()) {
            if (CopyTextToClipboard(clipboardText)) {
                footer = L"Copied to clipboard";
            }
        }

        DispatchXAMLCardSync(L"Network IP Addresses", L"\xE968", rows, footer);
    });
}

// 6. Rebuild Icon & Thumbnail Cache
void OnRebuildCacheClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    RunAsyncTracked([]() {
        auto cfg = GetSettingsSnapshot();

        DWORD thumbsDeleted = 0;
        DWORD thumbsSkipped = 0;
        ULONGLONG bytesFreed = 0;

        // Best-effort delete of thumbnail cache files.
        wchar_t localAppData[MAX_PATH] = {};
        DWORD localLen =
            GetEnvironmentVariableW(L"LOCALAPPDATA", localAppData, MAX_PATH);
        if (localLen > 0 && localLen < MAX_PATH) {
            std::wstring explorerDir =
                std::wstring(localAppData) + L"\\Microsoft\\Windows\\Explorer";

            std::wstring searchMask = explorerDir + L"\\thumbcache_*.db";
            WIN32_FIND_DATAW fd;
            HANDLE hFind = FindFirstFileW(searchMask.c_str(), &fd);
            if (hFind != INVALID_HANDLE_VALUE) {
                do {
                    if (g_unloading.load()) {
                        break;
                    }
                    if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        continue;
                    }

                    std::wstring fullPath = explorerDir + L"\\" + fd.cFileName;
                    ULONGLONG fileSize =
                        (static_cast<ULONGLONG>(fd.nFileSizeHigh) << 32) |
                        fd.nFileSizeLow;

                    if (DeleteFileW(ToExtendedPath(fullPath).c_str())) {
                        thumbsDeleted++;
                        bytesFreed += fileSize;
                    } else {
                        thumbsSkipped++;
                    }
                } while (FindNextFileW(hFind, &fd));
                FindClose(hFind);
            }
        }

        // Rebuild icon cache without restarting Explorer via ie4uinit.exe
        // -show.
        bool iconsRebuilt = false;
        if (!g_unloading.load()) {
            wchar_t sysDir[MAX_PATH] = {};
            DWORD sysLen = GetSystemDirectoryW(sysDir, MAX_PATH);
            if (sysLen > 0 && sysLen < MAX_PATH) {
                std::wstring exePath = std::wstring(sysDir) + L"\\ie4uinit.exe";

                STARTUPINFOW si = {};
                si.cb = sizeof(si);
                si.dwFlags = STARTF_USESHOWWINDOW;
                si.wShowWindow = SW_HIDE;
                PROCESS_INFORMATION pi = {};

                wchar_t cmdLine[] = L"ie4uinit.exe -show";
                if (CreateProcessW(exePath.c_str(), cmdLine, nullptr, nullptr,
                                   FALSE, CREATE_NO_WINDOW, nullptr, nullptr,
                                   &si, &pi)) {
                    DWORD waitRes = WaitForSingleObject(pi.hProcess, 5000);
                    DWORD exitCode = 1;
                    GetExitCodeProcess(pi.hProcess, &exitCode);
                    CloseHandle(pi.hThread);
                    CloseHandle(pi.hProcess);
                    iconsRebuilt = (waitRes == WAIT_OBJECT_0 && exitCode == 0);
                } else {
                    Wh_Log(L"ie4uinit.exe launch failed: %lu", GetLastError());
                }
            }
        }

        if (cfg.notifyRebuildCache && !g_unloading.load()) {
            double mbFreed =
                static_cast<double>(bytesFreed) / (1024.0 * 1024.0);
            wchar_t mbBuf[64] = {};
            swprintf_s(mbBuf, L"%.2f MB", mbFreed);

            std::vector<DialogRow> rows = {
                {L"Thumbnail files deleted", std::to_wstring(thumbsDeleted)},
                {L"Locked / skipped", std::to_wstring(thumbsSkipped)},
                {L"Space recovered", mbBuf},
                {L"Icon cache", iconsRebuilt ? L"Rebuilt" : L"Failed"},
            };

            std::wstring footer;
            if (!iconsRebuilt) {
                footer = L"Icon rebuild failed";
            } else if (thumbsSkipped > 0) {
                footer = L"Some thumbnails locked by Explorer";
            } else {
                footer = L"Cache rebuilt successfully";
            }

            DispatchXAMLCardSync(L"Cache Rebuilt", L"\xE8B9", rows, footer,
                                 !iconsRebuilt);
        }
    });
}

// 7. Clean DNS Cache
using DnsFlushResolverCache_t = BOOL(WINAPI*)();

void OnFlushDnsClick(wf::IInspectable const&, wux::RoutedEventArgs const&) {
    RunAsyncTracked([]() {
        BOOL flushed = FALSE;
        if (HMODULE hDnsApi = LoadLibraryExW(L"dnsapi.dll", nullptr,
                                             LOAD_LIBRARY_SEARCH_SYSTEM32)) {
            auto pFlush = reinterpret_cast<DnsFlushResolverCache_t>(
                GetProcAddress(hDnsApi, "DnsFlushResolverCache"));
            if (pFlush)
                flushed = pFlush();
            FreeLibrary(hDnsApi);
        }

        auto cfg = GetSettingsSnapshot();
        if (cfg.notifyFlushDns && !g_unloading.load()) {
            std::vector<DialogRow> rows = {
                {L"Resolver Cache", flushed ? L"Flushed" : L"Failed"},
                {L"Method", L"dnsapi.dll (In-Memory)"},
            };
            DispatchXAMLCardSync(L"DNS Cache", L"\xE774", rows,
                                 flushed ? L"Cache cleared successfully"
                                         : L"Error flushing cache",
                                 !flushed);
        }
    });
}

// ============================================================================
// Taskbar Context Menu Injection Hooks
// ============================================================================

bool HStringEquals(winrt::hstring const& value, const wchar_t* text) {
    return std::wstring_view(value.c_str(), value.size()) == text;
}

bool IsNamedItem(wuxc::MenuFlyoutItemBase const& baseItem,
                 const wchar_t* name) {
    try {
        if (auto frameworkElement = baseItem.try_as<wux::FrameworkElement>()) {
            return HStringEquals(frameworkElement.Name(), name);
        }
    } catch (...) {
    }
    return false;
}

bool IsSeparator(wuxc::MenuFlyoutItemBase const& baseItem) {
    try {
        return !!baseItem.try_as<wuxc::MenuFlyoutSeparator>();
    } catch (...) {
    }
    return false;
}

using MenuFlyoutItemBaseVector_Append_t =
    void(__cdecl*)(void* pThis, wuxc::MenuFlyoutItemBase const& item);
MenuFlyoutItemBaseVector_Append_t MenuFlyoutItemBaseVector_Append_Original;

struct MenuItemSpec {
    bool enabled;
    std::wstring text;
    const wchar_t* glyph;
    void (*handler)(wf::IInspectable const&, wux::RoutedEventArgs const&);
};

constexpr wu::Color kMantle{255, 0x18, 0x18, 0x25};
constexpr wu::Color kSurface1{255, 0x45, 0x47, 0x5A};

void InsertResource(wux::ResourceDictionary const& res,
                    const wchar_t* key,
                    wf::IInspectable const& value) {
    auto boxedKey = winrt::box_value(winrt::hstring(key));
    if (res.HasKey(boxedKey)) {
        res.Remove(boxedKey);
    }
    res.Insert(boxedKey, value);
}

// Mocha acrylic and the gradient border on the menu itself. Walks up from a
// loaded item to its MenuFlyoutPresenter; the presenter template binds
// Background, BorderBrush and BorderThickness, so local values win.
void ThemeMenuPresenter(wux::DependencyObject node) {
    auto cfg = GetSettingsSnapshot();
    for (int depth = 0; node && depth < 16; depth++) {
        if (auto presenter = node.try_as<wuxc::MenuFlyoutPresenter>()) {
            presenter.Background(MenuBackground(presenter, cfg));
            if (cfg.borderStyle != 2) {
                double w = cfg.borderWidth;
                presenter.BorderBrush(MakeBorderBrush(cfg));
                presenter.BorderThickness({w, w, w, w});
            }
            return;
        }
        node = wuxm::VisualTreeHelper::GetParent(node);
    }
}

void ThemeMenuIcon(wuxc::MenuFlyoutItem const& item, const ModSettings& cfg) {
    if (!cfg.colorIcons) {
        return;
    }
    if (auto icon = item.Icon()) {
        icon.Foreground(MakeBrush(kBlue));
    }
}

// Applies to every item in the taskbar menu, ours and the stock ones, so
// Task Manager and Taskbar settings match. Hover copies the dock hover:
// mantle fill with a 1 px blue ring, mauve ring when pressed.
void ThemeMenuItem(wuxc::MenuFlyoutItemBase const& base) {
    auto cfg = GetSettingsSnapshot();
    if (auto separator = base.try_as<wuxc::MenuFlyoutSeparator>()) {
        separator.Background(MakeBrush(kSurface1));
        return;
    }

    base.FontFamily(MakeFont(cfg));
    base.FontWeight(wut::FontWeight{cfg.fontWeight});
    base.Foreground(MakeBrush(kText));
    base.BorderThickness({1, 1, 1, 1});
    base.BorderBrush(MakeBrush(kBlue, 0));
    base.CornerRadius({8, 8, 8, 8});

    auto res = base.Resources();
    auto hoverFill = MakeBrush(kMantle, 0xBF);
    auto text = MakeBrush(kText);
    InsertResource(res, L"MenuFlyoutItemRevealBackgroundPointerOver", hoverFill);
    InsertResource(res, L"MenuFlyoutItemBackgroundPointerOver", hoverFill);
    InsertResource(res, L"MenuFlyoutItemRevealBackgroundPressed", hoverFill);
    InsertResource(res, L"MenuFlyoutItemBackgroundPressed", hoverFill);
    InsertResource(res, L"MenuFlyoutItemRevealBorderBrushPointerOver", MakeBrush(kBlue));
    InsertResource(res, L"MenuFlyoutItemRevealBorderBrushPressed", MakeBrush(kMauve));
    InsertResource(res, L"MenuFlyoutItemForegroundPointerOver", text);
    InsertResource(res, L"MenuFlyoutItemForegroundPressed", text);

    if (auto item = base.try_as<wuxc::MenuFlyoutItem>()) {
        ThemeMenuIcon(item, cfg);
        item.Loaded([](wf::IInspectable const& sender, wux::RoutedEventArgs const&) {
            try {
                auto loaded = sender.as<wuxc::MenuFlyoutItem>();
                ThemeMenuIcon(loaded, GetSettingsSnapshot());
                ThemeMenuPresenter(loaded);
            } catch (...) {
                Wh_Log(L"Menu theming on load failed");
            }
        });
    }
}

void AppendInjectedItems(void* vectorThis) {
    auto cfg = GetSettingsSnapshot();

    const MenuItemSpec specs[] = {
        {cfg.showRestartExplorer, cfg.textRestartExplorer, L"\xE72C",
         &OnRestartExplorerClick},
        {cfg.showCleanTemp, cfg.textCleanTemp, L"\xE74D", &OnCleanTempClick},
        {cfg.showReduceMemory, cfg.textReduceMemory, L"\xE950",
         &OnReduceMemoryClick},
        {cfg.showRestartGpu, cfg.textRestartGpu, L"\xE7F4", &OnRestartGpuClick},
        {cfg.showGetIp, cfg.textGetIp, L"\xE968", &OnGetIpClick},
        {cfg.showRebuildCache, cfg.textRebuildCache, L"\xE8B9",
         &OnRebuildCacheClick},
        {cfg.showFlushDns, cfg.textFlushDns, L"\xE774", &OnFlushDnsClick},
    };

    bool anyInjected = false;
    for (const auto& spec : specs) {
        if (!spec.enabled) {
            continue;
        }

        wuxc::MenuFlyoutItem menuItem;
        if (!anyInjected) {
            menuItem.Name(kGuardItemName);
        }
        menuItem.Text(spec.text);
        menuItem.Icon(CreateFluentIcon(spec.glyph));
        menuItem.Click(wux::RoutedEventHandler{spec.handler});
        ThemeMenuItem(menuItem);

        MenuFlyoutItemBaseVector_Append_Original(vectorThis, menuItem);
        anyInjected = true;
    }

    if (anyInjected) {
        wuxc::MenuFlyoutSeparator separator;
        ThemeMenuItem(separator);
        MenuFlyoutItemBaseVector_Append_Original(vectorThis, separator);
        g_currentMenuInjected = true;
    }
}

void __cdecl MenuFlyoutItemBaseVector_Append_Hook(
    void* pThis,
    wuxc::MenuFlyoutItemBase const& item) {
    if (g_taskbarSettingsMenuDepth > 0 && !g_currentMenuInjected) {
        try {
            if (!IsSeparator(item) && !IsNamedItem(item, kGuardItemName)) {
                AppendInjectedItems(pThis);
            }
        } catch (...) {
            Wh_Log(L"Taskbar menu append inspection failed");
        }
    }
    if (g_taskbarSettingsMenuDepth > 0) {
        try {
            ThemeMenuItem(item);
        } catch (...) {
            Wh_Log(L"Stock menu item theming failed");
        }
    }

    MenuFlyoutItemBaseVector_Append_Original(pThis, item);
}

struct ScopedTaskbarSettingsMenuBuild {
    bool outer = false;

    ScopedTaskbarSettingsMenuBuild() {
        outer = g_taskbarSettingsMenuDepth++ == 0;
        if (outer) {
            g_currentMenuInjected = false;
        }
    }

    ~ScopedTaskbarSettingsMenuBuild() { g_taskbarSettingsMenuDepth--; }
};

using ContextMenus_ShowTaskbarSettingsContextMenu_t =
    void(__cdecl*)(wux::FrameworkElement const& target,
                   void* taskbarSettings,
                   wuxi::ContextRequestedEventArgs const& args,
                   unsigned long long options);
ContextMenus_ShowTaskbarSettingsContextMenu_t
    ContextMenus_ShowTaskbarSettingsContextMenu_Original;

void __cdecl ContextMenus_ShowTaskbarSettingsContextMenu_Hook(
    wux::FrameworkElement const& target,
    void* taskbarSettings,
    wuxi::ContextRequestedEventArgs const& args,
    unsigned long long options) {
    try {
        if (target && target.XamlRoot()) {
            g_lastTargetWeak = target;
        }
    } catch (...) {
    }

    ScopedTaskbarSettingsMenuBuild scopedBuild;

    ContextMenus_ShowTaskbarSettingsContextMenu_Original(
        target, taskbarSettings, args, options);
}

// The clock's right-click menu (Adjust date and time, Notifications settings)
// is a MenuFlyout that SystemTray.dll keeps on the clock's Grid. Every tray
// icon menu, the clock's included, opens through
// ContextMenuPositionHelper::ShowContextMenuFlyout(grid, ...), which calls the
// flyout's ShowAt through its vtable. Hooking that one function themes the
// menu just before it opens. Counter: LocalStorage\attachedMenuShows.
const wchar_t kThemedMarker[] = L"SeamlessTaskbarUtilitiesThemed";
std::atomic<int> g_attachedMenuShows{0};

void ThemeWholeMenu(wuxc::MenuFlyout const& menu) {
    auto cfg = GetSettingsSnapshot();
    if (!menu.MenuFlyoutPresenterStyle()) {
        wux::Style style(winrt::xaml_typename<wuxc::MenuFlyoutPresenter>());
        style.Setters().Append(wux::Setter(wuxc::Control::BackgroundProperty(),
                                           MenuBackground(nullptr, cfg)));
        if (cfg.borderStyle != 2) {
            double w = cfg.borderWidth;
            style.Setters().Append(wux::Setter(wuxc::Control::BorderBrushProperty(),
                                               MakeBorderBrush(cfg)));
            style.Setters().Append(wux::Setter(wuxc::Control::BorderThicknessProperty(),
                                               winrt::box_value(wux::Thickness{w, w, w, w})));
        }
        menu.MenuFlyoutPresenterStyle(style);
    }
    auto marker = winrt::box_value(winrt::hstring(kThemedMarker));
    for (auto const& item : menu.Items()) {
        auto res = item.Resources();
        if (res.HasKey(marker)) {
            continue;
        }
        ThemeMenuItem(item);
        res.Insert(marker, winrt::box_value(true));
    }
}

bool ThemeFlyout(wuxcp::FlyoutBase const& flyout) {
    if (auto menu = flyout ? flyout.try_as<wuxc::MenuFlyout>() : nullptr) {
        ThemeWholeMenu(menu);
        return true;
    }
    return false;
}

void ThemeTrayIconMenu(wuxc::Grid const& grid) {
    try {
        if (!grid) {
            return;
        }
        bool themed = ThemeFlyout(wuxcp::FlyoutBase::GetAttachedFlyout(grid));
        themed |= ThemeFlyout(grid.ContextFlyout());
        if (themed) {
            Wh_SetIntValue(L"attachedMenuShows", ++g_attachedMenuShows);
        }
    } catch (...) {
        Wh_Log(L"Tray icon menu theming failed");
    }
}

using ShowContextMenuFlyout_t = void(__cdecl*)(wuxc::Grid const& grid,
                                               double scale,
                                               int taskbarLocation,
                                               void* const& xamlRoot);
ShowContextMenuFlyout_t ShowContextMenuFlyout_Original;
std::atomic<bool> g_systemTrayModuleHooked{false};

void __cdecl ShowContextMenuFlyout_Hook(wuxc::Grid const& grid,
                                        double scale,
                                        int taskbarLocation,
                                        void* const& xamlRoot) {
    ThemeTrayIconMenu(grid);
    ShowContextMenuFlyout_Original(grid, scale, taskbarLocation, xamlRoot);
}

void HookSystemTraySymbols(HMODULE module, bool applyHookOperations) {
    if (!module || g_systemTrayModuleHooked.exchange(true)) {
        return;
    }
    WindhawkUtils::SYMBOL_HOOK symbolHooks[] = {
        {
            {
                LR"(void __cdecl ContextMenuPositionHelper::ShowContextMenuFlyout(struct winrt::Windows::UI::Xaml::Controls::Grid const &,double,enum winrt::WindowsUdk::UI::Shell::TaskbarLocation,struct winrt::Windows::UI::Xaml::XamlRoot const &))",
            },
            &ShowContextMenuFlyout_Original,
            ShowContextMenuFlyout_Hook,
        },
    };
    if (!HookSymbols(module, symbolHooks, ARRAYSIZE(symbolHooks))) {
        Wh_Log(L"Failed to hook SystemTray tray menu");
        return;
    }
    Wh_SetIntValue(L"attachedMenuShows", 0);
    if (applyHookOperations) {
        Wh_ApplyHookOperations();
    }
}
// ============================================================================
// Symbol Hooking & Mod Lifecycle
// ============================================================================

using RtlGetVersion_t = LONG(WINAPI*)(OSVERSIONINFOW* versionInfo);

DWORD GetWindowsBuild() {
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    auto rtlGetVersion = ntdll ? reinterpret_cast<RtlGetVersion_t>(
                                     GetProcAddress(ntdll, "RtlGetVersion"))
                               : nullptr;
    if (!rtlGetVersion) {
        return 0;
    }

    OSVERSIONINFOW versionInfo = {};
    versionInfo.dwOSVersionInfoSize = sizeof(versionInfo);

    if (rtlGetVersion(&versionInfo) != 0) {
        return 0;
    }

    return versionInfo.dwBuildNumber;
}

HMODULE GetTaskbarViewModuleHandle() {
    HMODULE module = GetModuleHandleW(L"Taskbar.View.dll");
    if (!module) {
        module = GetModuleHandleW(L"ExplorerExtensions.dll");
    }
    return module;
}

bool HookTaskbarViewDllSymbols(HMODULE module) {
    // Taskbar.View.dll, ExplorerExtensions.dll
    WindhawkUtils::SYMBOL_HOOK symbolHooks[] = {
        {
            {
                LR"(void __cdecl winrt::Taskbar::implementation::ContextMenus::ShowTaskbarSettingsContextMenu(struct winrt::Windows::UI::Xaml::FrameworkElement const &,struct winrt::WindowsUdk::UI::Shell::TaskbarSettings const &,struct winrt::Windows::UI::Xaml::Input::ContextRequestedEventArgs const &,unsigned __int64))",
            },
            &ContextMenus_ShowTaskbarSettingsContextMenu_Original,
            ContextMenus_ShowTaskbarSettingsContextMenu_Hook,
        },
        {
            {
                LR"(public: __cdecl winrt::impl::consume_Windows_Foundation_Collections_IVector<struct winrt::Windows::Foundation::Collections::IVector<struct winrt::Windows::UI::Xaml::Controls::MenuFlyoutItemBase>,struct winrt::Windows::UI::Xaml::Controls::MenuFlyoutItemBase>::Append(struct winrt::Windows::UI::Xaml::Controls::MenuFlyoutItemBase const &)const )",
            },
            &MenuFlyoutItemBaseVector_Append_Original,
            MenuFlyoutItemBaseVector_Append_Hook,
        },
    };

    return HookSymbols(module, symbolHooks, ARRAYSIZE(symbolHooks));
}

void HandleLoadedModuleIfTaskbarView(HMODULE module, bool applyHookOperations) {
    if (!module || g_taskbarViewModuleHooked.load()) {
        return;
    }

    if (GetTaskbarViewModuleHandle() != module) {
        return;
    }

    if (g_taskbarViewModuleHooked.exchange(true)) {
        return;
    }

    if (HookTaskbarViewDllSymbols(module)) {
        if (applyHookOperations) {
            Wh_ApplyHookOperations();
        }
    } else {
        Wh_Log(L"Failed to hook Taskbar.View symbols");
    }
}

using LoadLibraryExW_t = decltype(&LoadLibraryExW);
LoadLibraryExW_t LoadLibraryExW_Original;

HMODULE WINAPI LoadLibraryExW_Hook(LPCWSTR lpLibFileName,
                                   HANDLE hFile,
                                   DWORD dwFlags) {
    HMODULE module = LoadLibraryExW_Original(lpLibFileName, hFile, dwFlags);
    if (module) {
        HandleLoadedModuleIfTaskbarView(module, true);
        if (!g_systemTrayModuleHooked.load() &&
            module == GetModuleHandleW(L"SystemTray.dll")) {
            HookSystemTraySymbols(module, true);
        }
    }
    return module;
}

std::wstring LoadStringSetting(const wchar_t* name,
                               const wchar_t* defaultValue) {
    auto val = WindhawkUtils::StringSetting::make(name);
    return val.get()[0] != L'\0' ? val.get() : defaultValue;
}

int ClampInt(int value, int lo, int hi) {
    return value < lo ? lo : value > hi ? hi : value;
}

// Reads "#RRGGBB" or "#AARRGGBB"; anything else keeps the fallback.
wu::Color ParseColor(const wchar_t* name, wu::Color fallback) {
    auto setting = WindhawkUtils::StringSetting::make(name);
    std::wstring s = setting.get();
    if (!s.empty() && s[0] == L'#') {
        s.erase(0, 1);
    }
    if (s.size() != 6 && s.size() != 8) {
        return fallback;
    }
    wchar_t* end = nullptr;
    unsigned long v = wcstoul(s.c_str(), &end, 16);
    if (!end || *end != L'\0') {
        return fallback;
    }
    uint8_t a = s.size() == 8 ? static_cast<uint8_t>(v >> 24) : 255;
    return wu::Color{a, static_cast<uint8_t>(v >> 16),
                     static_cast<uint8_t>(v >> 8), static_cast<uint8_t>(v)};
}

void LoadSettings() {
    ModSettings fresh;
    fresh.showRestartExplorer = Wh_GetIntSetting(L"restartExplorer.enabled");
    fresh.textRestartExplorer =
        LoadStringSetting(L"restartExplorer.label", L"Restart Explorer");

    fresh.showCleanTemp = Wh_GetIntSetting(L"cleanTemp.enabled");
    fresh.textCleanTemp = LoadStringSetting(L"cleanTemp.label", L"Clean Temp");
    fresh.cleanRecycleBin = Wh_GetIntSetting(L"cleanTemp.cleanRecycleBin");
    fresh.notifyCleanTemp = Wh_GetIntSetting(L"cleanTemp.showCard");

    fresh.showReduceMemory = Wh_GetIntSetting(L"reduceMemory.enabled");
    fresh.textReduceMemory =
        LoadStringSetting(L"reduceMemory.label", L"Reduce Memory");
    fresh.notifyReduceMemory = Wh_GetIntSetting(L"reduceMemory.showCard");

    fresh.showRestartGpu = Wh_GetIntSetting(L"restartGpu.enabled");
    fresh.textRestartGpu =
        LoadStringSetting(L"restartGpu.label", L"Restart Graphics Driver");

    fresh.showGetIp = Wh_GetIntSetting(L"getIp.enabled");
    fresh.textGetIp = LoadStringSetting(L"getIp.label", L"Get IP Address");
    fresh.queryPublicIp = Wh_GetIntSetting(L"getIp.queryPublicIp");
    fresh.copyIpToClipboard = Wh_GetIntSetting(L"getIp.copyToClipboard");

    fresh.showRebuildCache = Wh_GetIntSetting(L"rebuildCache.enabled");
    fresh.textRebuildCache = LoadStringSetting(
        L"rebuildCache.label", L"Rebuild Icon & Thumbnail Cache");
    fresh.notifyRebuildCache = Wh_GetIntSetting(L"rebuildCache.showCard");

    fresh.showFlushDns = Wh_GetIntSetting(L"flushDns.enabled");
    fresh.textFlushDns =
        LoadStringSetting(L"flushDns.label", L"Clean DNS Cache");
    fresh.notifyFlushDns = Wh_GetIntSetting(L"flushDns.showCard");

    {
        auto font = WindhawkUtils::StringSetting::make(L"look.fontFamily");
        fresh.fontFamily = font.get();
    }
    {
        auto weight = WindhawkUtils::StringSetting::make(L"look.fontWeight");
        std::wstring_view w = weight.get();
        fresh.fontWeight = w == L"light"      ? 300
                           : w == L"regular"  ? 400
                           : w == L"semibold" ? 600
                           : w == L"bold"     ? 700
                                              : 500;
    }
    {
        auto border = WindhawkUtils::StringSetting::make(L"look.border");
        std::wstring_view b = border.get();
        fresh.borderStyle = b == L"solid" ? 1 : b == L"none" ? 2 : 0;
    }
    fresh.gradientStart = ParseColor(L"look.gradientStart", fresh.gradientStart);
    fresh.gradientEnd = ParseColor(L"look.gradientEnd", fresh.gradientEnd);
    fresh.borderWidth = ClampInt(Wh_GetIntSetting(L"look.borderWidth"), 1, 4);
    fresh.cardOpacity = ClampInt(Wh_GetIntSetting(L"look.cardOpacity"), 85, 100);
    fresh.matchTaskbar = Wh_GetIntSetting(L"look.matchTaskbar");
    fresh.colorIcons = Wh_GetIntSetting(L"look.colorIcons");

    std::lock_guard<std::mutex> lock(g_settingsMutex);
    g_settings = std::move(fresh);
}

BOOL Wh_ModInit() {
    g_unloading.store(false);
    LoadSettings();

    DWORD build = GetWindowsBuild();
    if (build && build < 22000) {
        Wh_Log(L"Unsupported Windows build %lu", build);
        return TRUE;
    }

    if (HMODULE taskbarViewModule = GetTaskbarViewModuleHandle()) {
        g_taskbarViewModuleHooked.store(true);
        if (!HookTaskbarViewDllSymbols(taskbarViewModule)) {
            Wh_Log(L"Failed to hook Taskbar.View symbols during init");
        }
    }
    HookSystemTraySymbols(GetModuleHandleW(L"SystemTray.dll"), false);

    HMODULE kernelBase = GetModuleHandleW(L"kernelbase.dll");
    auto loadLibraryExW =
        kernelBase ? reinterpret_cast<LoadLibraryExW_t>(
                         GetProcAddress(kernelBase, "LoadLibraryExW"))
                   : nullptr;
    if (loadLibraryExW) {
        WindhawkUtils::SetFunctionHook(loadLibraryExW, LoadLibraryExW_Hook,
                                       &LoadLibraryExW_Original);
    }

    return TRUE;
}

void Wh_ModAfterInit() {
    if (!g_systemTrayModuleHooked.load()) {
        HookSystemTraySymbols(GetModuleHandleW(L"SystemTray.dll"), true);
    }
    if (!g_taskbarViewModuleHooked.load()) {
        if (HMODULE taskbarViewModule = GetTaskbarViewModuleHandle()) {
            HandleLoadedModuleIfTaskbarView(taskbarViewModule, true);
        }
    }
}

void Wh_ModSettingsChanged() {
    LoadSettings();
}

void Wh_ModUninit() {
    std::vector<HANDLE> threads;
    {
        std::lock_guard<std::mutex> lock(g_threadsMutex);
        g_unloading.store(true);
        threads.swap(g_threads);
    }

    CancelActivePublicIpRequest();

    for (HANDLE thread : threads) {
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
    }

    if (HWND hTaskbarWnd = FindCurrentProcessTaskbarWnd()) {
        RunFromWindowThread(hTaskbarWnd,
                            []() { CloseActiveFlyoutOnUIThread(); });
    }
}
