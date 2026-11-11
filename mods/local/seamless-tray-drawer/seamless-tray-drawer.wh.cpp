// ==WindhawkMod==
// @id              seamless-tray-drawer
// @name            Seamless Tray Drawer
// @description     A themed second drawer for rarely used tray icons, with your own colors, border and material
// @version         1.0.2
// @author          DavidHiFi, MEI
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -lole32 -loleaut32 -lruntimeobject -lversion -ladvapi32
// @license         GPL-3.0
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Tray Drawer

Adds a second drawer to the hidden tray icons panel and lets you restyle both.
The defaults follow Catppuccin Mocha: a dark acrylic blur with a blue to mauve
gradient border.

![Seamless Tray Drawer preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-tray-drawer.png)

## Features

- Drag an icon onto the footer button to move it into the second drawer, then
  click the button to open that drawer. Both drawers can stay open at once.
- Use acrylic blur or a solid fill, in any color.
- Set the border's two gradient colors, its direction, width and corner radius.
- Choose the footer button's icon, side and colors, and show a count of the
  icons you moved.
- The second drawer opens on the side away from the taskbar, so a top or bottom
  taskbar both work. You can also pin it to one side.
- Open both drawers every time you open the panel, if you like.
- Give the second drawer and the right-click menu the same look.
- Icons in both drawers grow when you point at them, with the same easing as
  Seamless Dock Animation's dock.
- The footer button gets a soft hover box with a colored edge.

## How to use

1. Open the hidden icons panel on the taskbar.
2. Drag an icon onto the footer button and let go. Repeat for more icons.
3. Click the footer button to open or close the second drawer.
4. Right-click the footer button and choose **Restore all collected icons** to
   put every icon back.

Icons keep their own menus and click actions. Turning the mod off brings back the
normal tray and keeps your saved list for next time.

## Notes

- Turn off Nested Tray Drawer before you turn this on. Only one of them can run.
- Every color setting takes a hex code such as `#89B4FA`. Add two more digits at
  the front for transparency, such as `#CC181825`. A wrong code falls back to the
  default color.
- High contrast mode always keeps the system colors.
- Tested on Windows 11 x64. The mod finds the tray code by its symbols and
  leaves the tray alone when it does not recognize them.

## Credits

Based on [Nested Tray Drawer](https://windhawk.net/mods/nested-tray-drawer) by
[MEI](https://github.com/Meidios), GPL-3.0. Its tray access builds on m417z's
[Taskbar notification icon spacing](https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-notification-icon-spacing.wh.cpp)
and [Taskbar height and icon size](https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-icon-size.wh.cpp),
and on Ris Peng's [System Tray Folders](https://github.com/ramensoftware/windhawk-mods/blob/main/mods/system-tray-folders.wh.cpp),
all GPL-3.0. This mod stays GPL-3.0.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- theme: true
  $name: Custom look
  $description: Turn this off to keep the stock Windows look
- styleMainPanel: true
  $name: Theme the hidden icons panel
  $description: Also apply the background and border to the main panel
- material: acrylic
  $name: Background material
  $options:
  - acrylic: Acrylic blur
  - solid: Solid color
- backgroundColor: "#181825"
  $name: Background color
  $description: Hex code. Catppuccin Mocha mantle is #181825
- backgroundOpacity: 52
  $name: Background strength (%)
  $description: How strongly the color covers the blur. 100 is fully solid
- luminosity: 70
  $name: Blur brightness (%)
  $description: Acrylic only. Lower values let more of the wallpaper's light through
- border:
  - enabled: true
    $name: Show border
  - startColor: "#89B4FA"
    $name: Border start color
  - endColor: "#CBA6F7"
    $name: Border end color
    $description: Use the same color as the start for a plain border
  - direction: horizontal
    $name: Gradient direction
    $options:
    - horizontal: Left to right
    - vertical: Top to bottom
    - diagonal: Corner to corner
  - thickness: 2
    $name: Border width (px)
  $name: Border
- cornerRadius: 15
  $name: Corner radius (px)
  $description: 15 matches a rounded taskbar
- textColor: "#CDD6F4"
  $name: Text color
  $description: Used by the counter and the right-click menu
- footer:
  - height: 40
    $name: Footer height (px)
  - divider: true
    $name: Show divider line
  - dividerColor: "#45475A"
    $name: Divider color
  $name: Footer
- chevron:
  - glyph: arrow
    $name: Button icon
    $options:
    - arrow: Arrow pointing at the second drawer
    - more: Three dots
    - grid: Grid
    - folder: Folder
    - star: Star
  - position: right
    $name: Button position
    $options:
    - right: Right
    - center: Center
    - left: Left
  - color: "#CBA6F7"
    $name: Icon color
  - hoverColor: "#BF45475A"
    $name: Hover color
  - hoverEdge: "#89B4FA"
    $name: Hover edge color
  - pressedColor: "#E6585B70"
    $name: Pressed color
  - pressedEdge: "#CBA6F7"
    $name: Pressed edge color
  - rotate: true
    $name: Turn the arrow while the drawer is open
  - showCount: true
    $name: Show how many icons are tucked away
  $name: Footer button
- secondDrawer:
  - placement: auto
    $name: Where it opens
    $options:
    - auto: Away from the taskbar
    - above: Above the panel
    - below: Below the panel
    - left: Left of the panel
    - right: Right of the panel
  - autoOpen: false
    $name: Open it with the panel
    $description: Show both drawers every time you open the hidden icons panel
  - padding: 6
    $name: Inner padding (px)
  - matchStyle: true
    $name: Use the same look as the panel
  $name: Second drawer
- styleMenu: true
  $name: Theme the right-click menu
- hoverZoom:
  - enabled: true
    $name: Grow icons on hover
  - size: 130
    $name: Largest size (%)
    $description: 100 to 200. Suggested 130, the same as the taskbar dock
  - reach: 64
    $name: Reach (px)
    $description: 20 to 200. How far from the pointer icons still grow. Suggested 64
  $name: Icon hover zoom
*/
// ==/WindhawkModSettings==

#include <windhawk_utils.h>
#include <cstring>
#include <winver.h>
#include <sddl.h>
#include <algorithm>
#include <array>
#include <charconv>
#include <cctype>
#include <string_view>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#undef GetCurrentTime
#include <winrt/Windows.Devices.Input.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Input.h>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.UI.Xaml.Automation.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Media.Animation.h>
#include <winrt/Windows.UI.Xaml.h>

using namespace winrt::Windows::UI::Xaml;
using Controls::Button;
using Controls::ContentPresenter;
using Controls::Flyout;
using Controls::Grid;
using Controls::ItemsControl;
using winrt::Windows::Foundation::IInspectable;

std::atomic<bool> g_unloading;
std::atomic<bool> g_runtimeAvailable{true};
std::atomic<int> g_hookState;  // 0: waiting, 1: resolving, 2: ready, 3: failed.
std::atomic<HWND> g_uiWindow;
std::atomic<DWORD> g_uiThread;
std::atomic<bool> g_hasDrawer;
SRWLOCK g_attachmentLock = SRWLOCK_INIT;
HANDLE g_cleanupEvent;
HANDLE g_uiThreadHandle;
thread_local unsigned g_uiCallbackDepth;
thread_local bool g_cleanupPending;
constexpr UINT kRemoveDrawerMessage = WM_APP + 0x731;

struct UiCallbackScope {
    UiCallbackScope() noexcept { ++g_uiCallbackDepth; }
    ~UiCallbackScope() noexcept {
        if (--g_uiCallbackDepth == 0 && g_cleanupPending) {
            g_cleanupPending = false;
            PostMessageW(g_uiWindow, kRemoveDrawerMessage, 0, 0);
        }
    }
};

bool Chinese() {
    return PRIMARYLANGID(GetUserDefaultUILanguage()) == LANG_CHINESE;
}

PCWSTR Text(PCWSTR en, PCWSTR zh) {
    return Chinese() ? zh : en;
}

void LogException(PCWSTR operation) noexcept {
    // Called only inside an exception handler.
    if (!g_runtimeAvailable)
        return;
    Wh_Log(L"%s failed: HRESULT=%08X", operation, static_cast<unsigned>(winrt::to_hresult()));
}

// BEGIN SETTINGS
using winrt::Windows::UI::Color;

enum class Placement { Auto, Above, Below, Left, Right };

struct Settings {
    bool theme{true};
    bool styleMainPanel{true};
    bool acrylic{true};
    Color background{255, 0x18, 0x18, 0x25};
    int backgroundOpacity{52};
    int luminosity{70};
    bool borderEnabled{true};
    Color borderStart{255, 0x89, 0xB4, 0xFA};
    Color borderEnd{255, 0xCB, 0xA6, 0xF7};
    std::wstring borderDirection{L"horizontal"};
    int borderThickness{2};
    int cornerRadius{15};
    Color text{255, 0xCD, 0xD6, 0xF4};
    int footerHeight{40};
    bool footerDivider{true};
    Color dividerColor{255, 0x45, 0x47, 0x5A};
    std::wstring glyph{L"arrow"};
    std::wstring position{L"right"};
    Color chevronColor{255, 0xCB, 0xA6, 0xF7};
    Color hoverColor{0xBF, 0x45, 0x47, 0x5A};
    Color hoverEdge{255, 0x89, 0xB4, 0xFA};
    Color pressedColor{0xE6, 0x58, 0x5B, 0x70};
    Color pressedEdge{255, 0xCB, 0xA6, 0xF7};
    bool rotate{true};
    bool showCount{true};
    Placement placement{Placement::Auto};
    bool autoOpen{};
    int innerPadding{6};
    bool matchStyle{true};
    bool styleMenu{true};
    bool zoom{true};
    int zoomSize{130};
    int zoomReach{64};
};

SRWLOCK g_settingsLock = SRWLOCK_INIT;
[[clang::no_destroy]] Settings g_settings;

Settings CurrentSettings() {
    AcquireSRWLockShared(&g_settingsLock);
    Settings copy = g_settings;
    ReleaseSRWLockShared(&g_settingsLock);
    return copy;
}

// Accepts #RGB, #RRGGBB and #AARRGGBB, with or without the leading #.
std::optional<Color> ParseHexColor(std::wstring_view text) {
    while (!text.empty() && iswspace(text.front()))
        text.remove_prefix(1);
    while (!text.empty() && iswspace(text.back()))
        text.remove_suffix(1);
    if (!text.empty() && text.front() == L'#')
        text.remove_prefix(1);
    if (text.size() != 3 && text.size() != 6 && text.size() != 8)
        return std::nullopt;
    uint32_t value = 0;
    for (wchar_t ch : text) {
        int digit;
        if (ch >= L'0' && ch <= L'9')
            digit = ch - L'0';
        else if (ch >= L'a' && ch <= L'f')
            digit = ch - L'a' + 10;
        else if (ch >= L'A' && ch <= L'F')
            digit = ch - L'A' + 10;
        else
            return std::nullopt;
        value = (value << 4) | static_cast<uint32_t>(digit);
    }
    if (text.size() == 3) {
        auto expand = [](uint32_t nibble) { return static_cast<uint8_t>(nibble * 17); };
        return Color{255, expand((value >> 8) & 0xF), expand((value >> 4) & 0xF),
                     expand(value & 0xF)};
    }
    uint8_t alpha = text.size() == 8 ? static_cast<uint8_t>(value >> 24) : 255;
    return Color{alpha, static_cast<uint8_t>(value >> 16), static_cast<uint8_t>(value >> 8),
                 static_cast<uint8_t>(value)};
}

std::wstring StringSetting(PCWSTR name) {
    PCWSTR raw = Wh_GetStringSetting(name);
    std::wstring value = raw ? raw : L"";
    Wh_FreeStringSetting(raw);
    return value;
}

Color ColorSetting(PCWSTR name, Color fallback) {
    return ParseHexColor(StringSetting(name)).value_or(fallback);
}

int IntSetting(PCWSTR name, int fallback, int low, int high) {
    // Windhawk returns 0 for a cleared number field; 0 is valid for some fields,
    // so only out-of-range values fall back.
    int value = Wh_GetIntSetting(name);
    return value < low || value > high ? fallback : value;
}

void LoadSettings() {
    Settings next;
    Settings const defaults;
    next.theme = Wh_GetIntSetting(L"theme") != 0;
    next.styleMainPanel = Wh_GetIntSetting(L"styleMainPanel") != 0;
    next.acrylic = StringSetting(L"material") != L"solid";
    next.background = ColorSetting(L"backgroundColor", defaults.background);
    next.backgroundOpacity = IntSetting(L"backgroundOpacity", defaults.backgroundOpacity, 0, 100);
    next.luminosity = IntSetting(L"luminosity", defaults.luminosity, 0, 100);
    next.borderEnabled = Wh_GetIntSetting(L"border.enabled") != 0;
    next.borderStart = ColorSetting(L"border.startColor", defaults.borderStart);
    next.borderEnd = ColorSetting(L"border.endColor", defaults.borderEnd);
    next.borderDirection = StringSetting(L"border.direction");
    next.borderThickness = IntSetting(L"border.thickness", defaults.borderThickness, 0, 8);
    next.cornerRadius = IntSetting(L"cornerRadius", defaults.cornerRadius, 0, 32);
    next.text = ColorSetting(L"textColor", defaults.text);
    next.footerHeight = IntSetting(L"footer.height", defaults.footerHeight, 28, 72);
    next.footerDivider = Wh_GetIntSetting(L"footer.divider") != 0;
    next.dividerColor = ColorSetting(L"footer.dividerColor", defaults.dividerColor);
    next.glyph = StringSetting(L"chevron.glyph");
    next.position = StringSetting(L"chevron.position");
    next.chevronColor = ColorSetting(L"chevron.color", defaults.chevronColor);
    next.hoverColor = ColorSetting(L"chevron.hoverColor", defaults.hoverColor);
    next.pressedColor = ColorSetting(L"chevron.pressedColor", defaults.pressedColor);
    next.hoverEdge = ColorSetting(L"chevron.hoverEdge", defaults.hoverEdge);
    next.pressedEdge = ColorSetting(L"chevron.pressedEdge", defaults.pressedEdge);
    next.rotate = Wh_GetIntSetting(L"chevron.rotate") != 0;
    next.showCount = Wh_GetIntSetting(L"chevron.showCount") != 0;
    auto placement = StringSetting(L"secondDrawer.placement");
    next.placement = placement == L"above"   ? Placement::Above
                     : placement == L"below" ? Placement::Below
                     : placement == L"left"  ? Placement::Left
                     : placement == L"right" ? Placement::Right
                                             : Placement::Auto;
    next.autoOpen = Wh_GetIntSetting(L"secondDrawer.autoOpen") != 0;
    next.innerPadding = IntSetting(L"secondDrawer.padding", defaults.innerPadding, 0, 24);
    next.matchStyle = Wh_GetIntSetting(L"secondDrawer.matchStyle") != 0;
    next.styleMenu = Wh_GetIntSetting(L"styleMenu") != 0;
    next.zoom = Wh_GetIntSetting(L"hoverZoom.enabled") != 0;
    next.zoomSize = IntSetting(L"hoverZoom.size", defaults.zoomSize, 100, 200);
    next.zoomReach = IntSetting(L"hoverZoom.reach", defaults.zoomReach, 20, 200);
    AcquireSRWLockExclusive(&g_settingsLock);
    g_settings = std::move(next);
    ReleaseSRWLockExclusive(&g_settingsLock);
}
// END SETTINGS

FrameworkElement FindDescendant(DependencyObject const& parent, PCWSTR className) {
    int count = Media::VisualTreeHelper::GetChildrenCount(parent);
    for (int i = 0; i < count; ++i) {
        auto child = Media::VisualTreeHelper::GetChild(parent, i);
        auto element = child.try_as<FrameworkElement>();
        if (element && winrt::get_class_name(element) == className)
            return element;
        if (auto found = FindDescendant(child, className))
            return found;
    }
    return nullptr;
}

struct SavedProperty {
    DependencyObject target{nullptr};
    DependencyProperty property{nullptr};
    IInspectable value{nullptr};
    Data::Binding binding{nullptr};

    SavedProperty() = default;
    SavedProperty(DependencyObject const& object, DependencyProperty const& key)
        : target(object), property(key), value(object.ReadLocalValue(key)) {
        if (auto element = object.try_as<FrameworkElement>()) {
            if (auto expression = element.GetBindingExpression(key))
                binding = expression.ParentBinding();
        }
    }

    void Restore() const {
        if (!target)
            return;
        if (binding)
            Data::BindingOperations::SetBinding(target, property, binding);
        else if (value == DependencyProperty::UnsetValue())
            target.ClearValue(property);
        else
            target.SetValue(property, value);
    }
};

struct IconCandidate {
    IInspectable model{nullptr};
};

constexpr UINT kCollectDroppedIconMessage = WM_APP + 0x732;
constexpr UINT kRefreshCollectionMessage = WM_APP + 0x733;
constexpr UINT kRefreshAppearanceMessage = WM_APP + 0x734;

// BEGIN COLLECTION RECORD
constexpr size_t kMaxCollectionChars = 262144;
constexpr size_t kMaxCollectionKeys = 512;

bool IsHex(wchar_t ch) {
    return (ch >= L'0' && ch <= L'9') || (ch >= L'a' && ch <= L'f');
}

bool ValidCollectionKey(std::wstring const& key) {
    if (key.starts_with(L"g:") && key.size() == 40) {
        if (key[2] != L'{' || key[39] != L'}')
            return false;
        for (size_t i = 3; i < 39; ++i) {
            if (i == 11 || i == 16 || i == 21 || i == 26) {
                if (key[i] != L'-')
                    return false;
            } else if (!IsHex(key[i]))
                return false;
        }
        return key != L"g:{00000000-0000-0000-0000-000000000000}";
    }
    if (!key.starts_with(L"p:") || key.size() > 32768)
        return false;
    auto colon = key.find(L':', 2);
    if (colon == std::wstring::npos || colon < 3 || colon > 12)
        return false;
    std::uint64_t uid{};
    for (size_t i = 2; i < colon; ++i) {
        if (key[i] < L'0' || key[i] > L'9')
            return false;
        uid = uid * 10 + key[i] - L'0';
        if (uid > 0xffffffffu)
            return false;
    }
    if (colon > 3 && key[2] == L'0')
        return false;
    if (key.size() == colon + 1 || (key.size() - colon - 1) % 4)
        return false;
    return std::all_of(key.begin() + colon + 1, key.end(), IsHex);
}

std::wstring PathCollectionKey(std::wstring const& lowerPath, uint32_t uid) {
    if (lowerPath.empty() || lowerPath.size() > 4096)
        return {};
    constexpr wchar_t digits[] = L"0123456789abcdef";
    std::wstring result = L"p:" + std::to_wstring(uid) + L":";
    for (wchar_t ch : lowerPath) {
        if (!ch || ch < 32 || ch > 0xffff)
            return {};
        for (int shift : {12, 8, 4, 0})
            result += digits[(ch >> shift) & 15];
    }
    return result;
}

bool ParseCollectionRecord(std::wstring const& text, std::vector<std::wstring>& keys) {
    keys.clear();
    if (text.empty())
        return true;  // A new installation has no stored value.
    if (text.size() > kMaxCollectionChars || !text.starts_with(L"NTD1\n"))
        return false;
    for (size_t pos = 5; pos < text.size();) {
        auto end = text.find(L'\n', pos);
        if (end == std::wstring::npos || end == pos || keys.size() >= kMaxCollectionKeys)
            return false;
        auto key = text.substr(pos, end - pos);
        if (!ValidCollectionKey(key) || std::find(keys.begin(), keys.end(), key) != keys.end())
            return false;
        keys.push_back(std::move(key));
        pos = end + 1;
    }
    return true;
}

bool SerializeCollectionRecord(std::vector<std::wstring> const& keys, std::wstring& text) {
    text = L"NTD1\n";
    if (keys.size() > kMaxCollectionKeys)
        return false;
    for (size_t i = 0; i < keys.size(); ++i) {
        if (!ValidCollectionKey(keys[i]) ||
            std::find(keys.begin(), keys.begin() + i, keys[i]) != keys.begin() + i)
            return false;
        text += keys[i] + L"\n";
        if (text.size() > kMaxCollectionChars)
            return false;
    }
    return true;
}

std::vector<size_t> MatchCollectionKeys(std::vector<std::wstring> const& live,
                                        std::vector<std::wstring> const& saved) {
    std::vector<size_t> matches;
    for (size_t i = 0; i < live.size(); ++i) {
        if (!live[i].empty() && std::count(live.begin(), live.end(), live[i]) == 1 &&
            std::find(saved.begin(), saved.end(), live[i]) != saved.end())
            matches.push_back(i);
    }
    return matches;
}
// END COLLECTION RECORD

HANDLE g_collectionMutex;
HANDLE g_instanceGuard;

// BEGIN INSTANCE GUARD
HANDLE AcquireDrawerInstance(DWORD processId) {
    auto name = L"Local\\Windhawk.NestedTrayDrawer.Instance.v1." + std::to_wstring(processId);
    SetLastError(ERROR_SUCCESS);
    auto handle = CreateEventW(nullptr, TRUE, FALSE, name.c_str());
    auto error = GetLastError();
    if (handle && error == ERROR_ALREADY_EXISTS) {
        CloseHandle(handle);
        return nullptr;
    }
    return handle;
}
// END INSTANCE GUARD

struct CollectionLock {
    bool acquired{};
    CollectionLock() {
        if (!g_collectionMutex)
            return;
        auto result = WaitForSingleObject(g_collectionMutex, 1000);
        acquired = result == WAIT_OBJECT_0 || result == WAIT_ABANDONED;
    }
    ~CollectionLock() {
        if (acquired)
            ReleaseMutex(g_collectionMutex);
    }
};

// BEGIN COLLECTION STORAGE
// Canonical storage is Windhawk's public API, scoped to this mod and user.
std::wstring g_collectionStorageKey;
std::wstring g_collectionReadyKey;

enum class RecordState { Missing, Present, Error };
struct StoredCollection {
    RecordState state{RecordState::Missing};
    std::wstring text;
};

bool ValidStoredCollection(std::wstring const& text) {
    std::vector<std::wstring> keys;
    return !text.empty() && ParseCollectionRecord(text, keys);
}

StoredCollection ReadWindhawkCollection() {
    if (g_collectionStorageKey.empty())
        return {RecordState::Error, {}};
    std::vector<wchar_t> buffer(kMaxCollectionChars + 1);
    auto count = Wh_GetStringValue(g_collectionStorageKey.c_str(), buffer.data(), buffer.size());
    if (!count) {
        // A marker distinguishes missing storage from an unreadable/empty value
        // after initialization. An unreadable initialized record is preserved.
        return {Wh_GetIntValue(g_collectionReadyKey.c_str(), 0) ? RecordState::Error
                                                                : RecordState::Missing,
                {}};
    }
    std::wstring text(buffer.data(), count);
    return {ValidStoredCollection(text) ? RecordState::Present : RecordState::Error,
            std::move(text)};
}

bool SaveWindhawkCollection(std::wstring const& text) {
    if (g_collectionStorageKey.empty() || !ValidStoredCollection(text) ||
        !Wh_SetStringValue(g_collectionStorageKey.c_str(), text.c_str()))
        return false;
    // The valid string also identifies an initialized destination if a process
    // exits before the marker write. Explicit-empty is the valid NTD1 record.
    return Wh_SetIntValue(g_collectionReadyKey.c_str(), 1);
}

bool ReadCollection(std::vector<std::wstring>& keys) {
    auto stored = ReadWindhawkCollection();
    return stored.state == RecordState::Present && ParseCollectionRecord(stored.text, keys);
}

bool WriteCollection(std::vector<std::wstring> const& keys) {
    auto current = ReadWindhawkCollection();
    // Only the explicit restore/reset command may replace an invalid record.
    if (current.state == RecordState::Error && !keys.empty())
        return false;
    if (current.state == RecordState::Error && !current.text.empty()) {
        auto backup = g_collectionStorageKey + L".invalid-backup";
        if (!Wh_SetStringValue(backup.c_str(), current.text.c_str()))
            return false;
    }
    std::wstring text;
    return SerializeCollectionRecord(keys, text) && SaveWindhawkCollection(text);
}
// END COLLECTION STORAGE

// BEGIN STORAGE NAMES
bool InitializeStorageNames() {
    HANDLE token{};
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token))
        return false;
    DWORD bytes{};
    GetTokenInformation(token, TokenUser, nullptr, 0, &bytes);
    std::vector<BYTE> buffer(bytes);
    bool ok = bytes && GetTokenInformation(token, TokenUser, buffer.data(), bytes, &bytes);
    CloseHandle(token);
    if (!ok)
        return false;
    wchar_t* sid{};
    if (!ConvertSidToStringSidW(reinterpret_cast<TOKEN_USER*>(buffer.data())->User.Sid, &sid))
        return false;
    g_collectionStorageKey = L"CollectionV2." + std::wstring(sid);
    LocalFree(sid);
    g_collectionReadyKey = g_collectionStorageKey + L".ready";
    return true;
}

// END STORAGE NAMES

// BEGIN STORAGE INITIALIZATION
bool InitializeCollectionStorage() {
    CollectionLock lock;
    if (!lock.acquired)
        return false;
    auto destination = ReadWindhawkCollection();
    if (destination.state == RecordState::Error) {
        Wh_Log(
            L"Saved collection invalid/unreadable; leaving icons visible. Use Reset saved collection to recover.");
        return true;
    }
    if (destination.state == RecordState::Present)
        return true;
    bool saved = SaveWindhawkCollection(L"NTD1\n");
    std::vector<std::wstring> confirmed;
    return saved && ReadCollection(confirmed) && confirmed.empty();
}
// END STORAGE INITIALIZATION

// Symbol-based internal interface access follows System Tray Folders (Ris Peng,
// GPLv3). Never call an implementation getter on an unverified COM interface.
using ObjectGetter = HRESULT(WINAPI*)(void*, void**);
GUID *g_viewIid, *g_configIid, *g_modelIid, *g_nativeIconIid;
void *g_viewVtable, *g_configVtable, *g_modelVtable, *g_nativeIconVtable;
ObjectGetter g_getConfiguration, g_getDataModel, g_getUdkObject;
void *g_nativeIdentityGetter, *g_nativeIdentityCopy, *g_nativeQueryInterface;
std::atomic<int> g_identityState;
ptrdiff_t g_nativeThisAdjustment;
size_t g_nativeIdentityOffset;

IInspectable NativeObjectProperty(IInspectable const& object,
                                  GUID const* iid,
                                  void* expectedVtable,
                                  ObjectGetter getter) {
    if (!object || !iid || !expectedVtable || !getter)
        return nullptr;
    winrt::com_ptr<IUnknown> iface;
    if (FAILED(reinterpret_cast<IUnknown*>(winrt::get_abi(object))
                   ->QueryInterface(*iid, iface.put_void())) ||
        *reinterpret_cast<void**>(iface.get()) != expectedVtable)
        return nullptr;
    IInspectable result{nullptr};
    winrt::check_hresult(getter(iface.get(), winrt::put_abi(result)));
    return result;
}

// BEGIN IDENTITY ACCESSOR
// Decode only bounded, symbol-resolved thunks and identity-prefix copies. The
// native MSVC owning-string return value is never constructed or called here.
enum class IdentityMachine { X64, Arm64 };
#ifdef _M_ARM64
constexpr IdentityMachine kIdentityMachine = IdentityMachine::Arm64;
#else
constexpr IdentityMachine kIdentityMachine = IdentityMachine::X64;
#endif

struct IdentityInstruction {
    std::string operation;
    std::vector<std::string> operands;
};

bool ReadIdentityInstruction(const BYTE*& pc, IdentityMachine machine, IdentityInstruction& out) {
    WH_DISASM_RESULT result{};
    if (!Wh_Disasm(const_cast<BYTE*>(pc), &result) || !result.length ||
        result.length > (machine == IdentityMachine::Arm64 ? 4u : 15u) ||
        (machine == IdentityMachine::Arm64 && result.length != 4) ||
        !memchr(result.text, 0, sizeof(result.text)))
        return false;
    pc += result.length;
    std::string_view text(result.text);
    auto separator = text.find_first_of(" \t");
    out.operation = text.substr(0, separator);
    for (auto& ch : out.operation)
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    out.operands.clear();
    if (separator == text.npos)
        return true;
    std::string operand;
    int depth{};
    for (char ch : text.substr(separator)) {
        if (std::isspace(static_cast<unsigned char>(ch)))
            continue;
        if (ch == '[')
            ++depth;
        if (ch == ']')
            --depth;
        if (ch == ',' && depth == 0) {
            out.operands.push_back(std::move(operand));
            operand.clear();
        } else {
            operand += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    if (!operand.empty())
        out.operands.push_back(std::move(operand));
    return depth == 0;
}

bool IdentityNumber(std::string_view text, int64_t& value) {
    if (text.starts_with('#'))
        text.remove_prefix(1);
    bool negative = text.starts_with('-');
    if (negative || text.starts_with('+'))
        text.remove_prefix(1);
    int base = 10;
    if (text.starts_with("0x")) {
        base = 16;
        text.remove_prefix(2);
    }
    uint64_t magnitude{};
    auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), magnitude, base);
    if (text.empty() || error != std::errc{} || end != text.data() + text.size() ||
        magnitude > INT64_MAX)
        return false;
    value = negative ? -static_cast<int64_t>(magnitude) : static_cast<int64_t>(magnitude);
    return true;
}

struct IdentityRegister {
    int index{-1};
    size_t width{};
};
IdentityRegister IdentityReg(std::string_view name, IdentityMachine machine) {
    if (machine == IdentityMachine::X64) {
        constexpr std::string_view wide[] = {"rax", "rcx", "rdx", "rbx",
                                             "rsp", "rbp", "rsi", "rdi"};
        constexpr std::string_view narrow[] = {"eax", "ecx", "edx", "ebx",
                                               "esp", "ebp", "esi", "edi"};
        for (int i = 0; i < 8; ++i) {
            if (name == wide[i])
                return {i, 8};
            if (name == narrow[i])
                return {i, 4};
        }
        if (name.starts_with("xmm")) {
            int64_t n{};
            if (IdentityNumber(name.substr(3), n) && n >= 0 && n < 32)
                return {32 + int(n), 16};
        }
        if (name.starts_with('r')) {
            auto width = name.ends_with('d') ? 4u : 8u;
            name.remove_prefix(1);
            if (width == 4)
                name.remove_suffix(1);
            int64_t n{};
            if (IdentityNumber(name, n) && n >= 8 && n <= 15)
                return {int(n), width};
        }
    } else {
        if (name == "sp")
            return {31, 8};
        if (name.empty())
            return {};
        char type = name.front();
        if (type != 'x' && type != 'w' && type != 'q' && type != 'v')
            return {};
        name.remove_prefix(1);
        if (auto dot = name.find('.'); dot != name.npos)
            name = name.substr(0, dot);
        int64_t n{};
        if (IdentityNumber(name, n) && n >= 0 && n < 31)
            return {int(n) + (type == 'q' || type == 'v' ? 32 : 0), type == 'x'   ? 8u
                                                                    : type == 'w' ? 4u
                                                                                  : 16u};
    }
    return {};
}

bool IdentityMemory(std::string_view text, IdentityMachine machine, int& base, int64_t& offset) {
    auto open = text.find('[');
    if (open == text.npos || !text.ends_with(']'))
        return false;
    text = text.substr(open + 1, text.size() - open - 2);
    auto separator = text.find_first_of(",+-");
    auto reg = IdentityReg(text.substr(0, separator), machine);
    if (reg.index < 0 || reg.width != 8)
        return false;
    base = reg.index;
    offset = 0;
    if (separator == text.npos)
        return true;
    if (text[separator] == ',')
        ++separator;
    return IdentityNumber(text.substr(separator), offset) && offset >= -4096 && offset <= 4096;
}

bool DecodeIdentityAdjustment(const BYTE* query, IdentityMachine machine, ptrdiff_t& adjustment) {
    std::vector<IdentityInstruction> code;
    for (int i = 0; i < 12; ++i) {
        IdentityInstruction instruction;
        if (!ReadIdentityInstruction(query, machine, instruction))
            return false;
        if (instruction.operation == "nop" || instruction.operation == "endbr64" ||
            instruction.operation == "bti")
            continue;
        bool terminal = instruction.operation == "b" || instruction.operation == "jmp";
        code.push_back(std::move(instruction));
        if (terminal)
            break;
    }
    int64_t target{};
    if (code.empty() || code.back().operands.size() != 1 ||
        !IdentityNumber(code.back().operands[0], target) || target <= 0)
        return false;
    int64_t delta{};
    if (machine == IdentityMachine::X64 && code.size() == 5) {
        int base{};
        if (code[0].operation != "lea" || code[0].operands.size() != 2 ||
            !IdentityMemory(code[0].operands[1], machine, base, delta) || base != 1 ||
            code[1].operation != "neg" || code[1].operands != std::vector<std::string>{"rcx"} ||
            code[2].operation != "sbb" ||
            code[2].operands != std::vector<std::string>{"rcx", "rcx"} ||
            code[3].operation != "and" ||
            code[3].operands != std::vector<std::string>{"rcx", code[0].operands[0]} ||
            code[4].operation != "jmp" ||
            (IdentityReg(code[0].operands[0], machine).width != 8 ||
             IdentityReg(code[0].operands[0], machine).index == 1))
            return false;
    } else if (machine == IdentityMachine::Arm64 && code.size() == 4) {
        if (code[0].operation != "sub" || code[0].operands.size() != 3 ||
            code[0].operands[1] != "x0" || IdentityReg(code[0].operands[0], machine).width != 8 ||
            IdentityReg(code[0].operands[0], machine).index == 0 ||
            !IdentityNumber(code[0].operands[2], delta) || code[1].operation != "cmp" ||
            code[1].operands != std::vector<std::string>{"x0", "#0"} ||
            code[2].operation != "csel" ||
            code[2].operands != std::vector<std::string>{"x0", "xzr", code[0].operands[0], "eq"} ||
            code[3].operation != "b")
            return false;
        delta = -delta;
    } else {
        return false;
    }
    if (delta >= 0 || delta < -4096)
        return false;
    adjustment = static_cast<ptrdiff_t>(delta);
    return true;
}

// Track only register aliases, constant pointer additions and three prefix
// load/store pairs, rather than attempting to interpret arbitrary native code.
struct IdentityValue {
    enum Kind { Unknown, Source, Output, Field } kind{};
    int64_t offset{};
    size_t width{};
};

bool DecodeIdentityPrefix(const BYTE* function,
                          const BYTE* copy,
                          bool copyVerified,
                          bool getter,
                          IdentityMachine machine,
                          size_t& offset) {
    std::array<IdentityValue, 64> registers{};
    const int first = machine == IdentityMachine::X64 ? 1 : 0;
    const int second = machine == IdentityMachine::X64 ? 2 : 1;
    const int stack = machine == IdentityMachine::X64 ? 4 : 31;
    registers[getter ? first : second] = {IdentityValue::Source, 0, 8};
    registers[getter ? second : first] = {IdentityValue::Output, 0, 8};
    int64_t candidate = -1;
    unsigned fields{};
    for (int i = 0; i < 40; ++i) {
        IdentityInstruction instruction;
        if (!ReadIdentityInstruction(function, machine, instruction))
            return false;
        auto const& op = instruction.operation;
        auto const& args = instruction.operands;
        if (op == "call" || op == "bl") {
            int64_t target{};
            auto destination = registers[first], source = registers[second];
            if (!getter || !copyVerified || args.size() != 1 || !IdentityNumber(args[0], target) ||
                reinterpret_cast<uintptr_t>(copy) != static_cast<uintptr_t>(target) ||
                destination.kind != IdentityValue::Output || destination.offset != 0 ||
                source.kind != IdentityValue::Source || source.offset < 8 || source.offset > 4096 ||
                source.offset % 8)
                return false;
            offset = static_cast<size_t>(source.offset);
            return true;
        }
        if (op == "bti")
            continue;
        if (op.starts_with('b') || op.starts_with('j') || op == "ret")
            return false;
        if (op == "cmp" || op == "test" || op == "nop" || op == "endbr64")
            continue;
        if (op == "push" && machine == IdentityMachine::X64 &&
            registers[stack].kind == IdentityValue::Unknown)
            continue;
        if (machine == IdentityMachine::Arm64 && (op == "pacibsp" || op == "paciasp")) {
            registers[30] = {};  // Pointer authentication writes the link register.
            continue;
        }
        // These stores only save registers to an untracked stack frame. In
        // particular, STP does not write its two register operands. All other
        // write-back/pair forms must be rejected, not treated as a single write.
        if (machine == IdentityMachine::Arm64 && (op == "str" || op == "stur" || op == "stp")) {
            size_t memoryIndex = op == "stp" ? 2 : 1;
            if ((args.size() == memoryIndex + 1 || args.size() == memoryIndex + 2) &&
                registers[stack].kind == IdentityValue::Unknown) {
                std::string_view memory = args[memoryIndex];
                bool preIndexed = memory.ends_with('!');
                if (preIndexed)
                    memory.remove_suffix(1);
                int base{};
                int64_t displacement{}, postIndex{};
                if (IdentityMemory(memory, machine, base, displacement) && base == stack &&
                    (args.size() == memoryIndex + 1 ||
                     (!preIndexed && IdentityNumber(args.back(), postIndex) && postIndex >= -4096 &&
                      postIndex <= 4096)))
                    continue;
            }
        }
        bool move = op == "mov" || op == "movups" || op == "movdqu" || op == "movdqa";
        bool load = move || op == "ldr" || op == "ldur";
        bool store = move || op == "str" || op == "stur";
        if (args.size() == 2 && (load || store)) {
            auto left = IdentityReg(args[0], machine), right = IdentityReg(args[1], machine);
            int base{};
            int64_t displacement{};
            bool memoryLoad =
                load && left.index >= 0 && IdentityMemory(args[1], machine, base, displacement);
            if (memoryLoad) {
                if (left.index == stack)
                    return false;
                auto pointer = registers[base];
                registers[left.index] =
                    pointer.kind == IdentityValue::Source
                        ? IdentityValue{IdentityValue::Field, pointer.offset + displacement,
                                        left.width}
                        : IdentityValue{};
                continue;
            }
            auto valueReg = machine == IdentityMachine::X64 ? right : left;
            auto memory = machine == IdentityMachine::X64 ? args[0] : args[1];
            if (store && valueReg.index >= 0 &&
                IdentityMemory(memory, machine, base, displacement)) {
                auto pointer = registers[base], value = registers[valueReg.index];
                auto destination = pointer.offset + displacement;
                int field = destination == 0    ? 0
                            : destination == 8  ? 1
                            : destination == 12 ? 2
                                                : -1;
                if (pointer.kind == IdentityValue::Output && field >= 0) {
                    size_t width = field == 0 ? 8 : field == 1 ? 4 : 16;
                    int64_t begin = value.offset - destination;
                    if (value.kind != IdentityValue::Field || value.width != width ||
                        valueReg.width != width || begin < (getter ? 8 : 0) || begin > 4096 ||
                        begin % 8 || (candidate >= 0 && candidate != begin))
                        return false;
                    candidate = begin;
                    fields |= 1u << field;
                    if (fields == 7) {
                        offset = static_cast<size_t>(candidate);
                        return true;
                    }
                }
                continue;
            }
            if (move && left.index >= 0 && right.index >= 0) {
                auto value = registers[right.index];
                if ((value.kind == IdentityValue::Source || value.kind == IdentityValue::Output) &&
                    (left.width != 8 || right.width != 8))
                    value = {};
                if (left.index == stack && value.kind != IdentityValue::Unknown)
                    return false;
                registers[left.index] = left.width == right.width ? value : IdentityValue{};
                continue;
            }
        }
        if (op == "lea" && args.size() == 2) {
            auto destination = IdentityReg(args[0], machine);
            int base{};
            int64_t displacement{};
            if (destination.index < 0 || destination.width != 8 ||
                !IdentityMemory(args[1], machine, base, displacement))
                return false;
            auto value = registers[base];
            if (value.kind == IdentityValue::Source || value.kind == IdentityValue::Output)
                value.offset += displacement;
            else
                value = {};
            if (destination.index == stack && value.kind != IdentityValue::Unknown)
                return false;
            registers[destination.index] = value;
            continue;
        }
        if ((op == "add" || op == "sub") && (args.size() == 2 || args.size() == 3)) {
            auto destination = IdentityReg(args[0], machine);
            auto source = IdentityReg(args.size() == 3 ? args[1] : args[0], machine);
            int64_t immediate{};
            if (destination.index < 0 || source.index < 0 || destination.width != 8 ||
                source.width != 8 || !IdentityNumber(args.back(), immediate) || immediate < -4096 ||
                immediate > 4096)
                return false;
            auto value = registers[source.index];
            if (value.kind == IdentityValue::Source || value.kind == IdentityValue::Output)
                value.offset += op == "sub" ? -immediate : immediate;
            else
                value = {};
            if (value.offset < -4096 || value.offset > 4096)
                return false;
            if (destination.index == stack && value.kind != IdentityValue::Unknown)
                return false;
            registers[destination.index] = value;
            continue;
        }
        // Unknown instructions can modify additional or implicit registers.
        // Reject them instead of leaving a potentially stale tracked alias.
        return false;
    }
    return false;
}

bool DecodeIdentityAccessor(const BYTE* query,
                            const BYTE* getter,
                            const BYTE* copy,
                            ptrdiff_t& adjustment,
                            size_t& identityOffset,
                            IdentityMachine machine = kIdentityMachine) {
    size_t copiedOffset{};
    bool copyVerified = DecodeIdentityPrefix(copy, nullptr, false, false, machine, copiedOffset) &&
                        copiedOffset == 0;
    return DecodeIdentityAdjustment(query, machine, adjustment) &&
           DecodeIdentityPrefix(getter, copy, copyVerified, true, machine, identityOffset);
}
// END IDENTITY ACCESSOR

bool ResolveNativeIdentity(HMODULE module) {
    int expected = 0;
    if (!g_identityState.compare_exchange_strong(expected, 1))
        return g_identityState == 2;
    // taskbar.dll
    WindhawkUtils::SYMBOL_HOOK identityHooks[] = {
        {{LR"(struct guid::guid const winrt::impl::guid_v<struct winrt::WindowsUdk::UI::Shell::INotificationAreaIcon>)"},
         &g_nativeIconIid},
        {{LR"(const winrt::impl::produce<struct winrt::WindowsUdk::UI::Shell::implementation::NotificationAreaIcon2,struct winrt::WindowsUdk::UI::Shell::INotificationAreaIcon>::`vftable')"},
         &g_nativeIconVtable},
        {{LR"(public: virtual int __cdecl winrt::impl::produce_base<struct winrt::WindowsUdk::UI::Shell::implementation::NotificationAreaIcon2,struct winrt::WindowsUdk::UI::Shell::INotificationAreaIcon,void>::QueryInterface(struct winrt::guid const &,void * *))"},
         &g_nativeQueryInterface},
        {{LR"(public: struct NotificationAreaIconIdentity __cdecl winrt::WindowsUdk::UI::Shell::implementation::NotificationAreaIcon2::Identity(void)const)",
          LR"(public: struct NotificationAreaIconIdentity __cdecl winrt::WindowsUdk::UI::Shell::implementation::NotificationAreaIcon2::Identity(void)const )"},
         &g_nativeIdentityGetter},
        {{LR"(public: __cdecl NotificationAreaIconIdentity::NotificationAreaIconIdentity(struct NotificationAreaIconIdentity const &))"},
         &g_nativeIdentityCopy},
    };
    bool ok = WindhawkUtils::HookSymbols(module, identityHooks, ARRAYSIZE(identityHooks));
    if (ok) {
        // All three addresses are verified symbol addresses in this loaded DLL.
        ok = DecodeIdentityAccessor(static_cast<const BYTE*>(g_nativeQueryInterface),
                                    static_cast<const BYTE*>(g_nativeIdentityGetter),
                                    static_cast<const BYTE*>(g_nativeIdentityCopy),
                                    g_nativeThisAdjustment, g_nativeIdentityOffset);
    }
    g_identityState = ok ? 2 : 3;
    Wh_Log(L"Native identity symbols and instruction validation: %d", ok);
    return ok;
}

std::wstring GuidCollectionKey(GUID const& guid) {
    constexpr GUID empty{};
    if (IsEqualGUID(guid, empty))
        return {};
    wchar_t text[40]{};
    if (!StringFromGUID2(guid, text, ARRAYSIZE(text)))
        return {};
    for (auto& ch : text)
        if (ch >= L'A' && ch <= L'F')
            ch += L'a' - L'A';
    return std::wstring(L"g:") + text;
}

std::wstring StableIconKey(IInspectable const& model) {
    if (g_identityState != 2)
        return {};
    auto config = NativeObjectProperty(model, g_viewIid, g_viewVtable, g_getConfiguration);
    auto dataModel = NativeObjectProperty(config, g_configIid, g_configVtable, g_getDataModel);
    auto icon = NativeObjectProperty(dataModel, g_modelIid, g_modelVtable, g_getUdkObject);
    if (!icon)
        return {};
    winrt::com_ptr<IUnknown> native;
    if (FAILED(reinterpret_cast<IUnknown*>(winrt::get_abi(icon))
                   ->QueryInterface(*g_nativeIconIid, native.put_void())) ||
        *reinterpret_cast<void**>(native.get()) != g_nativeIconVtable ||
        (*reinterpret_cast<void***>(native.get()))[0] != g_nativeQueryInterface)
        return {};
    struct IdentityPrefix {
        HWND owner;
        uint32_t uid;
        GUID guid;
    } fields{};
    static_assert(offsetof(IdentityPrefix, uid) == 8 && offsetof(IdentityPrefix, guid) == 12);
    SIZE_T copied{};
    auto address = reinterpret_cast<const BYTE*>(native.get()) + g_nativeThisAdjustment +
                   g_nativeIdentityOffset;
    if (!ReadProcessMemory(GetCurrentProcess(), address, &fields, sizeof(fields), &copied) ||
        copied != sizeof(fields))
        return {};
    if (auto key = GuidCollectionKey(fields.guid); !key.empty())
        return key;
    // Query the owning process through the documented API. No registry settings
    // ID field or guessed application-name matching is needed.
    DWORD processId{};
    if (!fields.owner || !GetWindowThreadProcessId(fields.owner, &processId) || !processId)
        return {};
    std::unique_ptr<void, decltype(&CloseHandle)> process(
        OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId), CloseHandle);
    if (!process)
        return {};
    wchar_t path[4097]{};
    DWORD length = ARRAYSIZE(path);
    if (!QueryFullProcessImageNameW(process.get(), 0, path, &length) || !length ||
        length >= ARRAYSIZE(path))
        return {};
    std::wstring lower(length, L'\0');
    if (!LCMapStringEx(LOCALE_NAME_INVARIANT, LCMAP_LOWERCASE, path, static_cast<int>(length),
                       lower.data(), static_cast<int>(lower.size()), nullptr, nullptr, 0))
        return {};
    return PathCollectionKey(lower, fields.uid);
}

// BEGIN CHEVRON DROP POLICY
bool AcceptChevronDrop(bool ownedSource,
                       bool samePointer,
                       bool available,
                       double x,
                       double y,
                       double width,
                       double height) {
    return ownedSource && samePointer && available && std::isfinite(x) && std::isfinite(y) &&
           std::isfinite(width) && std::isfinite(height) && width > 0 && height > 0 && x >= 0 &&
           y >= 0 && x < width && y < height;
}
// END CHEVRON DROP POLICY

// BEGIN MENU HOLD POLICY
// Pure lifetime policy: only an explicit inner-icon context-menu gesture may
// arm this guard. An unrelated native menu must never keep these drawers open.
struct MenuHoldPolicy {
    bool armed{};
    bool observed{};
    std::uintptr_t owner{};
    std::uint64_t deadline{};
    std::uint64_t lastMenuTick{};

    void Reset() { *this = {}; }
    void Arm(std::uint64_t now) {
        Reset();
        armed = true;
        deadline = now + 1000;
    }
    bool Observe(std::uint64_t now, bool inMenu, std::uintptr_t menuOwner) {
        if (!armed)
            return false;
        if (inMenu) {
            if (observed && owner && menuOwner && owner != menuOwner) {
                Reset();
                return false;
            }
            observed = true;
            if (menuOwner)
                owner = menuOwner;
            lastMenuTick = now;
            return true;
        }
        // Briefly allow the application's async menu creation and focus return.
        if ((!observed && now < deadline) || (observed && now - lastMenuTick < 150))
            return true;
        Reset();
        return false;
    }
};
// END MENU HOLD POLICY

struct DrawerState {
    Grid root{nullptr};
    ItemsControl nativeItems{nullptr};
    Controls::Border footer{nullptr};
    winrt::Windows::UI::ViewManagement::AccessibilitySettings accessibility{nullptr};
    Button chevron{nullptr};
    Flyout inner{nullptr};
    ItemsControl innerItems{nullptr};
    ItemsControl sourceMirror{nullptr};
    Controls::MenuFlyout picker{nullptr};
    winrt::Windows::Foundation::Collections::IObservableVector<IInspectable> observedSource{
        nullptr};
    Controls::MenuFlyoutItem restoreCommand{nullptr};
    winrt::event_token restoreClick{};
    std::vector<IInspectable> selectedModels;
    std::vector<IInspectable> sourceSnapshot;
    IInspectable expectedSource{nullptr};
    winrt::event_token sourceLayout{};
    bool partitioned{};
    bool refreshQueued{};
    bool refreshDeferred{};
    bool nativeDragActive{};
    IconCandidate dragSource;
    IconCandidate pendingDrop;
    void* dragSourceView{};
    uint32_t dragPointerId{};
    bool dragOverChevron{};
    std::unique_ptr<SavedProperty> originalItemsSource;
    std::vector<SavedProperty> rootProperties;
    uint32_t originalRowCount{};
    winrt::event_token click{}, rightTap{}, loaded{}, unloaded{}, opened{}, closed{};
    winrt::event_token itemsChanged{}, innerLayout{}, innerClosing{}, previewKey{}, menuTick{},
        footerLoaded{}, appearanceChanged{};
    DispatcherTimer menuTimer{nullptr};
    MenuHoldPolicy menuHold;
    bool deferredNativeDismiss{};
    unsigned layoutReports{};
    bool open{};
    bool changing{};
    bool closing{};
    HWND outerWindow{};
    void* nativeManager{};
    // Seamless look: the native panel background and the footer button parts.
    Controls::Border panelBorder{nullptr};
    std::vector<SavedProperty> panelProperties;
    bool panelStyled{};
    Controls::FontIcon arrow{nullptr};
    Controls::TextBlock countText{nullptr};
    Media::RotateTransform arrowRotation{nullptr};
    Media::Animation::Storyboard arrowStoryboard{nullptr};
    bool autoOpenPending{};
    // Hover zoom: one area for the panel, one for the second drawer.
    struct ZoomIcon {
        winrt::weak_ref<FrameworkElement> view;
        Media::CompositeTransform transform{nullptr};
        double cx{}, cy{}, scale{1.0}, shown{1.0};
    };
    struct ZoomArea {
        FrameworkElement host{nullptr};   // takes the pointer events
        FrameworkElement scope{nullptr};  // holds the icons
        IInspectable moved{nullptr}, exited{nullptr};
        std::vector<ZoomIcon> icons;
        bool inside{};
        double mx{}, my{}, intensity{};
        std::chrono::steady_clock::time_point lastScan{};
    };
    ZoomArea zoomMain, zoomInner;
    winrt::event_token zoomRender{};
    std::chrono::steady_clock::time_point zoomLast{};
};

// XAML objects must never be released from global destructors at process exit.
// All normal-unload cleanup runs explicitly on the owning UI thread.
[[clang::no_destroy]] std::unique_ptr<DrawerState> g_drawer;

// Brushes the footer button template reads through lightweight-styling keys.
// The template resolves each key once, so these instances are kept and only
// their colors change when settings change.
struct ChevronBrushes {
    Media::SolidColorBrush normal{nullptr}, hover{nullptr}, pressed{nullptr};
    Media::SolidColorBrush foreground{nullptr}, border{nullptr};
    Media::SolidColorBrush borderHover{nullptr}, borderPressed{nullptr};
};
[[clang::no_destroy]] ChevronBrushes g_chevronBrushes;

void QueueCollectionRefresh() {
    if (!g_drawer || g_unloading || !g_runtimeAvailable || g_drawer->closing ||
        g_drawer->refreshQueued)
        return;
    g_drawer->refreshQueued = PostMessageW(g_uiWindow, kRefreshCollectionMessage, 0, 0) != FALSE;
}

using NativeDismiss_t = void(WINAPI*)(void*);
NativeDismiss_t LightDismissConditions_Original;
NativeDismiss_t HideAnimation_Original;

void ResetMenuHold(DrawerState& state) noexcept {
    try {
        if (state.menuTimer)
            state.menuTimer.Stop();
    } catch (...) {
        LogException(L"Stop menu hold timer");
    }
    state.menuHold.Reset();
    state.deferredNativeDismiss = false;
}

bool ShouldHoldForMenu(DrawerState& state) {
    if (g_unloading || !g_runtimeAvailable || state.changing || state.closing || !state.open ||
        !state.menuHold.armed)
        return false;
    GUITHREADINFO info{};
    info.cbSize = sizeof(info);
    bool inMenu = GetGUIThreadInfo(0, &info) &&
                  (info.flags & (GUI_INMENUMODE | GUI_POPUPMENUMODE | GUI_SYSTEMMENUMODE));
    bool wasObserved = state.menuHold.observed;
    bool hold = state.menuHold.Observe(GetTickCount64(), inMenu,
                                       reinterpret_cast<std::uintptr_t>(info.hwndMenuOwner));
    if (!wasObserved && state.menuHold.observed) {
        Wh_Log(L"Owned context gesture entered native menu mode; flags=%lu", info.flags);
    }
    return hold;
}

void ArmMenuHold() {
    if (!g_drawer || g_unloading || !g_runtimeAvailable || !g_drawer->open)
        return;
    auto& state = *g_drawer;
    state.menuHold.Arm(GetTickCount64());
    state.deferredNativeDismiss = false;
    state.menuTimer.Start();
    Wh_Log(L"Inner-icon context gesture armed bounded native-menu hold");
}

bool DeferNativeDismiss(void* manager, PCWSTR source) {
    if (g_uiThread != GetCurrentThreadId() || !g_drawer || g_drawer->nativeManager != manager ||
        !ShouldHoldForMenu(*g_drawer))
        return false;
    if (!g_drawer->deferredNativeDismiss)
        Wh_Log(L"Deferring native %s for owned app menu", source);
    g_drawer->deferredNativeDismiss = true;
    return true;
}

void RestoreSelected(DrawerState& state, bool restoreBinding = true) {
    if (state.dragOverChevron)
        VisualStateManager::GoToState(state.chevron, L"Normal", true);
    state.dragOverChevron = false;
    state.pendingDrop = {};
    state.dragSource = {};
    state.dragSourceView = nullptr;
    if (!state.originalItemsSource)
        return;
    state.changing = true;
    ResetMenuHold(state);
    state.inner.Hide();
    // Remove the inner generated view before restoring the outer binding, so
    // a native item model has at most one active view throughout the transfer.
    state.innerItems.ItemsSource(nullptr);
    state.innerItems.UpdateLayout();
    if (state.sourceMirror && state.itemsChanged.value) {
        state.observedSource.VectorChanged(state.itemsChanged);
        state.itemsChanged = {};
    }
    if (restoreBinding)
        state.originalItemsSource->Restore();
    state.nativeItems.UpdateLayout();
    state.originalItemsSource.reset();
    state.observedSource = nullptr;
    state.sourceMirror = nullptr;
    state.selectedModels.clear();
    state.sourceSnapshot.clear();
    state.expectedSource = nullptr;
    state.partitioned = false;
    state.changing = false;
    Wh_Log(L"Original native ItemsSource/binding restored; outer items=%u",
           state.nativeItems.Items().Size());
}

IconCandidate OuterCandidateFromSource(DrawerState& state, IInspectable const& source) {
    auto element = source.try_as<DependencyObject>();
    ContentPresenter presenter{nullptr};
    for (unsigned depth = 0; element && depth < 64; ++depth) {
        if (element == state.nativeItems) {
            if (!presenter)
                break;
            auto model = presenter.Content();
            // Validate against the active source, not a detached old view.
            uint32_t index{};
            if (model && state.nativeItems.Items().IndexOf(model, index)) {
                return {model};
            }
            break;
        }
        if (auto current = element.try_as<ContentPresenter>())
            presenter = current;
        element = Media::VisualTreeHelper::GetParent(element);
    }
    return {};
}

void ClearDragSource(DrawerState& state) {
    if (state.dragOverChevron)
        VisualStateManager::GoToState(state.chevron, L"Normal", true);
    state.dragOverChevron = false;
    state.dragSource = {};
    state.dragSourceView = nullptr;
    state.dragPointerId = 0;
    state.nativeDragActive = false;
    if (state.refreshDeferred)
        QueueCollectionRefresh();
}

bool IsChevronDrop(DrawerState& state,
                   void* sourceView,
                   Input::PointerRoutedEventArgs const& args) {
    auto point = args.GetCurrentPoint(state.chevron).Position();
    uint32_t index{};
    bool owned = state.dragSourceView == sourceView && state.dragSource.model &&
                 state.nativeItems.Items().IndexOf(state.dragSource.model, index);
    return AcceptChevronDrop(
        owned, args.Pointer().PointerId() == state.dragPointerId,
        !state.changing && !state.closing && state.root.IsLoaded() && state.chevron.IsLoaded() &&
            state.chevron.IsEnabled() && IsWindowVisible(state.outerWindow),
        point.X, point.Y, state.chevron.ActualWidth(), state.chevron.ActualHeight());
}

// BEGIN TRAY PARTITION
// Validate model identity before changing either visual tree.
template <typename Model>
bool PartitionTrayModels(std::vector<Model> const& all,
                         std::vector<Model> const& selected,
                         std::vector<Model>& ordinary,
                         std::vector<Model>& rare) {
    ordinary.clear();
    rare.clear();
    if (all.empty() || all.size() > 512)
        return false;
    for (size_t i = 0; i < selected.size(); ++i) {
        if (std::count(all.begin(), all.end(), selected[i]) != 1 ||
            std::find(selected.begin(), selected.begin() + i, selected[i]) != selected.begin() + i)
            return false;
    }
    for (auto const& model : all) {
        if (std::find(selected.begin(), selected.end(), model) != selected.end())
            rare.push_back(model);
        else
            ordinary.push_back(model);
    }
    return true;
}
// END TRAY PARTITION

bool TrackNativeSource(DrawerState& state) {
    auto source = state.nativeItems.ItemsSource();
    if (!source)
        return false;
    state.originalItemsSource =
        std::make_unique<SavedProperty>(state.nativeItems, ItemsControl::ItemsSourceProperty());
    state.sourceMirror = ItemsControl();
    state.sourceMirror.ItemsSource(source);
    state.expectedSource = source;
    state.observedSource =
        state.sourceMirror.Items()
            .as<winrt::Windows::Foundation::Collections::IObservableVector<IInspectable>>();
    state.itemsChanged = state.observedSource.VectorChanged([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        if (g_unloading || !g_runtimeAvailable)
            return;
        QueueCollectionRefresh();
    });
    return true;
}

std::vector<std::wstring> LiveCollectionKeys(std::vector<IInspectable> const& models) {
    std::vector<std::wstring> keys;
    for (auto const& model : models) {
        try {
            keys.push_back(StableIconKey(model));
        } catch (...) {
            keys.emplace_back();
        }
    }
    return keys;
}

void UpdateCount(DrawerState& state);

void RefreshClassification(DrawerState& state) {
    if (g_unloading || state.closing || state.changing)
        return;
    if (state.nativeDragActive || ShouldHoldForMenu(state)) {
        state.refreshDeferred = true;
        return;
    }
    state.refreshDeferred = false;
    try {
        if (state.originalItemsSource && state.nativeItems.ItemsSource() != state.expectedSource) {
            // Windows replaced its source. Do not restore an obsolete binding
            // over the replacement; capture the new source before filtering.
            RestoreSelected(state, false);
        }
        if (!state.originalItemsSource && !TrackNativeSource(state))
            return;
        auto allItems = state.sourceMirror.Items();
        uint32_t count = allItems.Size();
        if (count > 512) {
            RestoreSelected(state);
            Wh_Log(L"Native collection exceeds supported size; saved membership retained");
            return;
        }
        std::vector<IInspectable> all, selected, ordinary, rare;
        for (uint32_t i = 0; i < count; ++i)
            all.push_back(allItems.GetAt(i));
        std::vector<std::wstring> saved;
        if (!ReadCollection(saved)) {
            saved.clear();
            Wh_Log(
                L"Invalid/unsupported saved collection; leaving icons visible and record untouched");
        }
        auto keys = LiveCollectionKeys(all);
        Wh_Log(L"Persistent identity scan: total=%zu identified=%zu", keys.size(),
               static_cast<size_t>(std::count_if(keys.begin(), keys.end(),
                                                 [](auto const& key) { return !key.empty(); })));
        for (auto index : MatchCollectionKeys(keys, saved))
            selected.push_back(all[index]);
        if (state.sourceSnapshot == all && state.selectedModels == selected)
            return;
        if (!selected.empty() && !PartitionTrayModels(all, selected, ordinary, rare)) {
            throw winrt::hresult_error(E_UNEXPECTED);
        }
        state.changing = true;
        ResetMenuHold(state);
        state.innerItems.ItemsSource(nullptr);
        state.innerItems.UpdateLayout();
        if (selected.empty()) {
            state.inner.Hide();
            if (state.partitioned)
                state.originalItemsSource->Restore();
        } else {
            auto itemTemplate = state.nativeItems.ItemTemplate();
            if (!itemTemplate)
                throw winrt::hresult_error(E_UNEXPECTED);
            state.nativeItems.ItemsSource(nullptr);
            state.nativeItems.UpdateLayout();
            state.innerItems.ItemTemplate(itemTemplate);
            state.innerItems.ItemTemplateSelector(state.nativeItems.ItemTemplateSelector());
            state.innerItems.ItemContainerStyle(state.nativeItems.ItemContainerStyle());
            state.innerItems.ItemsPanel(state.nativeItems.ItemsPanel());
            state.innerItems.DataContext(state.nativeItems.DataContext());
            state.nativeItems.ItemsSource(
                winrt::single_threaded_observable_vector<IInspectable>(std::move(ordinary)));
            state.nativeItems.UpdateLayout();
            state.innerItems.ItemsSource(
                winrt::single_threaded_observable_vector<IInspectable>(std::move(rare)));
        }
        state.selectedModels = std::move(selected);
        state.sourceSnapshot = std::move(all);
        state.partitioned = !state.selectedModels.empty();
        state.expectedSource = state.nativeItems.ItemsSource();
        state.layoutReports = 0;
        state.changing = false;
        UpdateCount(state);
        Wh_Log(L"Persistent collection reconciled: saved=%zu original=%u outer=%u inner=%u",
               saved.size(), count, state.nativeItems.Items().Size(),
               state.innerItems.Items().Size());
    } catch (...) {
        LogException(L"Reconcile saved collection");
        RestoreSelected(state);
    }
}

bool SelectIcon(IconCandidate const& candidate) {
    if (!g_drawer || g_unloading || !candidate.model)
        return false;
    auto& state = *g_drawer;
    if (state.changing || state.closing)
        return false;
    if (std::find(state.selectedModels.begin(), state.selectedModels.end(), candidate.model) !=
        state.selectedModels.end())
        return true;
    RefreshClassification(state);
    if (!state.sourceMirror)
        return false;
    auto key = StableIconKey(candidate.model);
    auto keys = LiveCollectionKeys(state.sourceSnapshot);
    if (key.empty() || std::count(keys.begin(), keys.end(), key) != 1) {
        Wh_Log(L"No unique persistent identity for dropped icon; left visible");
        return false;
    }
    {
        CollectionLock lock;
        std::vector<std::wstring> saved;
        if (!lock.acquired || !ReadCollection(saved))
            return false;
        if (std::find(saved.begin(), saved.end(), key) == saved.end())
            saved.push_back(key);
        // Save before hiding the icon. Unload/exit never clears these records.
        if (!WriteCollection(saved)) {
            Wh_Log(L"Could not persist collection; icon left visible");
            return false;
        }
        Wh_Log(L"Collection saved after explicit drop: entries=%zu", saved.size());
    }
    RefreshClassification(state);
    return std::find(state.selectedModels.begin(), state.selectedModels.end(), candidate.model) !=
           state.selectedModels.end();
}

void ShowRestoreMenu() {
    if (!g_drawer || g_unloading)
        return;
    auto& state = *g_drawer;
    if (state.restoreCommand && state.restoreClick.value)
        state.restoreCommand.Click(state.restoreClick);
    state.restoreClick = {};
    state.restoreCommand = nullptr;
    state.picker.Items().Clear();

    auto restore = Controls::MenuFlyoutItem();
    std::vector<std::wstring> saved;
    bool healthy = ReadCollection(saved);
    restore.Text(healthy ? Text(L"Restore all collected icons", L"还原全部收纳图标")
                         : Text(L"Reset saved collection", L"重置收纳记录"));
    restore.IsEnabled(!healthy || !saved.empty());
    if (auto s = CurrentSettings(); s.theme && s.styleMenu && !state.accessibility.HighContrast())
        restore.Foreground(Media::SolidColorBrush(s.text));
    state.restoreCommand = restore;
    state.restoreClick = restore.Click([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        if (g_unloading || !g_runtimeAvailable)
            return;
        try {
            if (!g_drawer)
                return;
            {
                CollectionLock lock;
                if (!lock.acquired || !WriteCollection({})) {
                    Wh_Log(L"Could not clear saved collection; presentation retained");
                    return;
                }
            }
            RefreshClassification(*g_drawer);
            Wh_Log(L"User restored all icons; saved membership explicitly cleared");
        } catch (...) {
            LogException(L"Restore collected icons");
        }
    });
    state.picker.Items().Append(restore);
    state.picker.ShowAt(state.chevron);
}

// BEGIN CLEANUP STEP
template <typename F>
bool CleanupStep(PCWSTR operation, F&& action) noexcept {
    try {
        action();
        return true;
    } catch (...) {
        LogException(operation);
        return false;
    }
}
// END CLEANUP STEP

void ZoomTeardown(DrawerState& state) noexcept;

void RemoveDrawer() noexcept {
    if (!g_drawer)
        return;
    auto& state = *g_drawer;
    state.closing = true;
    state.changing = true;
    ZoomTeardown(state);
    // Event removers are noexcept in C++/WinRT. Revoke before operations that
    // can pump XAML events, including Hide(), bindings and visual-tree edits.
    if (state.click.value)
        state.chevron.Click(state.click);
    if (state.rightTap.value)
        state.chevron.RightTapped(state.rightTap);
    if (state.loaded.value)
        state.root.Loaded(state.loaded);
    if (state.unloaded.value)
        state.root.Unloaded(state.unloaded);
    if (state.opened.value)
        state.inner.Opened(state.opened);
    if (state.closed.value)
        state.inner.Closed(state.closed);
    if (state.innerClosing.value)
        state.inner.Closing(state.innerClosing);
    if (state.previewKey.value)
        state.innerItems.PreviewKeyDown(state.previewKey);
    if (state.menuTick.value)
        state.menuTimer.Tick(state.menuTick);
    if (state.footerLoaded.value)
        state.footer.Loaded(state.footerLoaded);
    if (state.appearanceChanged.value)
        state.root.ActualThemeChanged(state.appearanceChanged);
    if (state.innerLayout.value)
        state.innerItems.LayoutUpdated(state.innerLayout);
    if (state.sourceLayout.value)
        state.nativeItems.LayoutUpdated(state.sourceLayout);
    if (state.restoreCommand && state.restoreClick.value)
        state.restoreCommand.Click(state.restoreClick);
    CleanupStep(L"Revoke native source observer", [&] {
        if (state.sourceMirror && state.itemsChanged.value)
            state.observedSource.VectorChanged(state.itemsChanged);
    });
    CleanupStep(L"Stop menu timer", [&] {
        if (state.menuTimer)
            state.menuTimer.Stop();
    });
    state.menuHold.Reset();
    CleanupStep(L"Hide restore menu", [&] {
        if (state.picker)
            state.picker.Hide();
    });
    CleanupStep(L"Hide inner drawer", [&] {
        if (state.inner)
            state.inner.Hide();
    });
    // Detach inner views first. An unrelated cleanup failure must never skip
    // restoration of the original native ItemsSource/binding.
    CleanupStep(L"Detach inner icons", [&] {
        if (state.innerItems) {
            state.innerItems.ItemsSource(nullptr);
            state.innerItems.UpdateLayout();
        }
    });
    CleanupStep(L"Restore native source", [&] {
        if (state.originalItemsSource)
            state.originalItemsSource->Restore();
    });
    CleanupStep(L"Refresh native layout", [&] { state.nativeItems.UpdateLayout(); });
    CleanupStep(L"Remove drawer footer", [&] {
        uint32_t index;
        if (state.footer && state.root.Children().IndexOf(state.footer, index))
            state.root.Children().RemoveAt(index);
    });
    for (auto it = state.panelProperties.rbegin(); it != state.panelProperties.rend(); ++it)
        CleanupStep(L"Restore native panel look", [&] { it->Restore(); });
    CleanupStep(L"Clear themed flyout styles", [&] {
        if (state.inner)
            state.inner.ClearValue(Controls::Flyout::FlyoutPresenterStyleProperty());
        if (state.picker)
            state.picker.ClearValue(Controls::MenuFlyout::MenuFlyoutPresenterStyleProperty());
    });
    for (auto it = state.rootProperties.rbegin(); it != state.rootProperties.rend(); ++it)
        CleanupStep(L"Restore native layout property", [&] { it->Restore(); });
    CleanupStep(L"Restore native grid rows", [&] {
        while (state.root.RowDefinitions().Size() > state.originalRowCount)
            state.root.RowDefinitions().RemoveAtEnd();
    });
    CleanupStep(L"Clear restore menu", [&] {
        if (state.picker)
            state.picker.Items().Clear();
    });
    CleanupStep(L"Detach inner content", [&] {
        if (state.inner)
            state.inner.Content(nullptr);
    });
    CleanupStep(L"Stop chevron animation", [&] {
        if (state.arrowStoryboard)
            state.arrowStoryboard.Stop();
        state.arrowStoryboard = nullptr;
    });
    // Release the shared button brushes here, on the owning UI thread.
    g_chevronBrushes = {};
    g_drawer.reset();
    g_hasDrawer = false;
    Wh_Log(L"Drawer callbacks revoked and native presentation restored on owning UI thread");
}

// BEGIN SEAMLESS LOOK
Color WithAlpha(Color color, double factor) {
    color.A = static_cast<uint8_t>(std::clamp(color.A * factor, 0.0, 255.0));
    return color;
}

Media::Brush MakeBackgroundBrush(Settings const& s) {
    double strength = s.backgroundOpacity / 100.0;
    if (!s.acrylic)
        return Media::SolidColorBrush(WithAlpha(s.background, strength));
    Color opaque = s.background;
    opaque.A = 255;
    Media::AcrylicBrush brush;
    // Backdrop samples the desktop behind the window, like the stock flyouts.
    // HostBackdrop is in-app acrylic: dead on Windows 11, it renders a flat
    // tint and the sharp content behind the panel shows through.
    brush.BackgroundSource(Media::AcrylicBackgroundSource::Backdrop);
    brush.TintColor(opaque);
    brush.TintOpacity(strength * (s.background.A / 255.0));
    brush.TintLuminosityOpacity(
        winrt::Windows::Foundation::IReference<double>(s.luminosity / 100.0));
    brush.FallbackColor(WithAlpha(opaque, 0.85));
    return brush;
}

Media::Brush MakeBorderBrush(Settings const& s) {
    using winrt::Windows::Foundation::Point;
    Media::LinearGradientBrush brush;
    if (s.borderDirection == L"vertical") {
        brush.StartPoint(Point{0.5f, 0.0f});
        brush.EndPoint(Point{0.5f, 1.0f});
    } else if (s.borderDirection == L"diagonal") {
        brush.StartPoint(Point{0.0f, 0.0f});
        brush.EndPoint(Point{1.0f, 1.0f});
    } else {
        brush.StartPoint(Point{0.0f, 0.5f});
        brush.EndPoint(Point{1.0f, 0.5f});
    }
    Media::GradientStop start, end;
    start.Color(s.borderStart);
    start.Offset(0);
    end.Color(s.borderEnd);
    end.Offset(1);
    brush.GradientStops().Append(start);
    brush.GradientStops().Append(end);
    return brush;
}

double BorderWidth(Settings const& s) {
    return s.borderEnabled ? s.borderThickness : 0;
}

// True when the outer panel sits in the top half of its monitor, which means
// the taskbar is at the top and the panel drops down from it.
bool PanelInUpperHalf(DrawerState const& state) {
    RECT rect;
    MONITORINFO monitor{sizeof(monitor)};
    if (!state.outerWindow || !GetWindowRect(state.outerWindow, &rect) ||
        !GetMonitorInfoW(MonitorFromWindow(state.outerWindow, MONITOR_DEFAULTTONEAREST), &monitor))
        return false;
    return (rect.top + rect.bottom) / 2 < (monitor.rcMonitor.top + monitor.rcMonitor.bottom) / 2;
}

Placement EffectivePlacement(DrawerState const& state, Settings const& s) {
    if (s.placement != Placement::Auto)
        return s.placement;
    return PanelInUpperHalf(state) ? Placement::Below : Placement::Above;
}

Controls::Primitives::FlyoutPlacementMode InnerPlacementMode(DrawerState const& state,
                                                             Settings const& s) {
    using Mode = Controls::Primitives::FlyoutPlacementMode;
    bool alignLeft = s.theme && s.position == L"left";
    bool upper = PanelInUpperHalf(state);
    switch (s.theme ? EffectivePlacement(state, s) : Placement::Above) {
        case Placement::Below:
            return alignLeft ? Mode::BottomEdgeAlignedLeft : Mode::BottomEdgeAlignedRight;
        case Placement::Left:
            return upper ? Mode::LeftEdgeAlignedTop : Mode::LeftEdgeAlignedBottom;
        case Placement::Right:
            return upper ? Mode::RightEdgeAlignedTop : Mode::RightEdgeAlignedBottom;
        default:
            return alignLeft ? Mode::TopEdgeAlignedLeft : Mode::TopEdgeAlignedRight;
    }
}

PCWSTR ChevronGlyph(DrawerState const& state, Settings const& s) {
    if (s.theme) {
        if (s.glyph == L"more")
            return L"\xE712";
        if (s.glyph == L"grid")
            return L"\xE71D";
        if (s.glyph == L"folder")
            return L"\xE8B7";
        if (s.glyph == L"star")
            return L"\xE734";
        switch (EffectivePlacement(state, s)) {
            case Placement::Below:
                return L"\xE70D";  // ChevronDown
            case Placement::Left:
                return L"\xE76B";  // ChevronLeft
            case Placement::Right:
                return L"\xE76C";  // ChevronRight
            default:
                break;
        }
    }
    return L"\xE70E";  // ChevronUp, the original glyph.
}

void AnimateArrow(DrawerState& state) {
    if (!state.arrowRotation)
        return;
    auto s = CurrentSettings();
    bool arrow = s.glyph == L"arrow" || s.glyph.empty();
    double target = state.open && s.theme && s.rotate && arrow ? 180.0 : 0.0;
    if (state.arrowRotation.Angle() == target)
        return;
    using namespace Media::Animation;
    DoubleAnimation animation;
    animation.To(winrt::Windows::Foundation::IReference<double>(target));
    animation.Duration(DurationHelper::FromTimeSpan(
        winrt::Windows::Foundation::TimeSpan{std::chrono::milliseconds(220)}));
    CubicEase ease;
    ease.EasingMode(EasingMode::EaseOut);
    animation.EasingFunction(ease);
    Storyboard::SetTarget(animation, state.arrowRotation);
    Storyboard::SetTargetProperty(animation, L"Angle");
    if (state.arrowStoryboard)
        state.arrowStoryboard.Stop();
    state.arrowStoryboard = Storyboard();
    state.arrowStoryboard.Children().Append(animation);
    state.arrowStoryboard.Begin();
}

void UpdateCount(DrawerState& state) {
    if (!state.countText)
        return;
    auto s = CurrentSettings();
    size_t count = state.selectedModels.size();
    bool show = s.theme && s.showCount && count > 0 && !state.accessibility.HighContrast();
    state.countText.Text(std::to_wstring(count));
    state.countText.Visibility(show ? Visibility::Visible : Visibility::Collapsed);
    state.chevron.Width(show ? std::numeric_limits<double>::quiet_NaN() : 40.0);
    state.chevron.Padding(show ? Thickness{10, 0, 12, 0} : Thickness{0, 0, 0, 0});
}

void ApplyPanelLook(DrawerState& state, Settings const& s, bool themed) {
    if (!state.panelBorder)
        return;
    using Controls::Border;
    if (themed && s.styleMainPanel) {
        if (!state.panelStyled) {
            state.panelProperties.clear();
            state.panelProperties.emplace_back(state.panelBorder, Border::BackgroundProperty());
            state.panelProperties.emplace_back(state.panelBorder, Border::BorderBrushProperty());
            state.panelProperties.emplace_back(state.panelBorder, Border::BorderThicknessProperty());
            state.panelProperties.emplace_back(state.panelBorder, Border::CornerRadiusProperty());
            state.panelStyled = true;
        }
        double width = BorderWidth(s);
        double radius = s.cornerRadius;
        state.panelBorder.Background(MakeBackgroundBrush(s));
        state.panelBorder.BorderBrush(MakeBorderBrush(s));
        state.panelBorder.BorderThickness(Thickness{width, width, width, width});
        state.panelBorder.CornerRadius(CornerRadius{radius, radius, radius, radius});
    } else if (state.panelStyled) {
        for (auto it = state.panelProperties.rbegin(); it != state.panelProperties.rend(); ++it)
            it->Restore();
        state.panelProperties.clear();
        state.panelStyled = false;
    }
}

Style MakePresenterStyle(winrt::Windows::UI::Xaml::Interop::TypeName const& type,
                         Settings const& s,
                         std::optional<double> padding) {
    double width = BorderWidth(s);
    double radius = s.cornerRadius;
    Style style(type);
    auto setters = style.Setters();
    setters.Append(Setter(Controls::Control::BackgroundProperty(), MakeBackgroundBrush(s)));
    setters.Append(Setter(Controls::Control::BorderBrushProperty(), MakeBorderBrush(s)));
    setters.Append(Setter(Controls::Control::BorderThicknessProperty(),
                          winrt::box_value(Thickness{width, width, width, width})));
    setters.Append(Setter(Controls::Control::CornerRadiusProperty(),
                          winrt::box_value(CornerRadius{radius, radius, radius, radius})));
    if (padding) {
        double p = *padding;
        setters.Append(
            Setter(Controls::Control::PaddingProperty(), winrt::box_value(Thickness{p, p, p, p})));
    }
    return style;
}

void ApplyFlyoutLooks(DrawerState& state, Settings const& s, bool themed) {
    if (themed && s.matchStyle)
        state.inner.FlyoutPresenterStyle(
            MakePresenterStyle(winrt::xaml_typename<Controls::FlyoutPresenter>(), s, s.innerPadding));
    else
        state.inner.ClearValue(Controls::Flyout::FlyoutPresenterStyleProperty());
    if (themed && s.styleMenu)
        state.picker.MenuFlyoutPresenterStyle(MakePresenterStyle(
            winrt::xaml_typename<Controls::MenuFlyoutPresenter>(), s, std::nullopt));
    else
        state.picker.ClearValue(Controls::MenuFlyout::MenuFlyoutPresenterStyleProperty());
}

void UpdateDrawerAppearance(DrawerState& state) {
    using namespace winrt::Windows::UI::ViewManagement;
    auto s = CurrentSettings();
    bool dark = state.root.ActualTheme() == ElementTheme::Dark;
    bool highContrast = state.accessibility.HighContrast();
    bool themed = s.theme && !highContrast;
    auto brush = [](Color color) { return Media::SolidColorBrush(color); };
    auto& b = g_chevronBrushes;
    double width = BorderWidth(s);

    state.footer.Height(themed ? s.footerHeight : 40);
    state.chevron.Height(themed ? s.footerHeight - 8 : 32);
    state.chevron.HorizontalAlignment(themed && s.position == L"left" ? HorizontalAlignment::Left
                                      : themed && s.position == L"center"
                                          ? HorizontalAlignment::Center
                                          : HorizontalAlignment::Right);
    if (state.arrow)
        state.arrow.Glyph(ChevronGlyph(state, themed ? s : Settings{.theme = false}));

    if (highContrast) {
        UISettings colors;
        auto background = colors.GetColorValue(UIColorType::Background);
        auto foreground = colors.GetColorValue(UIColorType::Foreground);
        state.footer.Background(brush(background));
        state.footer.BorderBrush(brush(foreground));
        state.footer.BorderThickness(Thickness{0, 1, 0, 0});
        state.footer.Margin(Thickness{0, 0, 0, 0});
        state.footer.CornerRadius(CornerRadius{0, 0, 8, 8});
        b.normal.Color(background);
        b.hover.Color(background);
        b.pressed.Color(background);
        b.foreground.Color(foreground);
        b.border.Color(foreground);
        b.borderHover.Color(foreground);
        b.borderPressed.Color(foreground);
    } else if (themed) {
        double inner = std::max(0.0, s.cornerRadius - width);
        // The panel background spans the footer row, so a clear footer keeps
        // the whole surface seamless. A clear brush still takes pointer input.
        state.footer.Background(brush(Color{0, 0, 0, 0}));
        state.footer.BorderBrush(brush(s.dividerColor));
        state.footer.BorderThickness(Thickness{0, s.footerDivider ? 1.0 : 0.0, 0, 0});
        state.footer.Margin(Thickness{width, 0, width, width});
        state.footer.CornerRadius(CornerRadius{0, 0, inner, inner});
        b.normal.Color(Color{0, 0, 0, 0});
        b.hover.Color(s.hoverColor);
        b.pressed.Color(s.pressedColor);
        b.foreground.Color(s.chevronColor);
        b.border.Color(Color{0, 0, 0, 0});
        b.borderHover.Color(s.hoverEdge);
        b.borderPressed.Color(s.pressedEdge);
    } else {
        // The original Nested Tray Drawer colors.
        state.footer.Background(brush(dark ? Color{18, 122, 156, 189} : Color{8, 59, 85, 112}));
        state.footer.BorderBrush(brush(dark ? Color{38, 122, 156, 189} : Color{32, 59, 85, 112}));
        state.footer.BorderThickness(Thickness{0, 1, 0, 0});
        state.footer.Margin(Thickness{0, 0, 0, 0});
        state.footer.CornerRadius(CornerRadius{0, 0, 8, 8});
        b.normal.Color(dark ? Color{22, 255, 255, 255} : Color{10, 0, 0, 0});
        b.hover.Color(dark ? Color{36, 255, 255, 255} : Color{18, 0, 0, 0});
        b.pressed.Color(dark ? Color{14, 255, 255, 255} : Color{8, 0, 0, 0});
        b.foreground.Color(dark ? Color{255, 255, 255, 255} : Color{228, 0, 0, 0});
        b.border.Color(dark ? Color{20, 255, 255, 255} : Color{16, 0, 0, 0});
        b.borderHover.Color(b.border.Color());
        b.borderPressed.Color(b.border.Color());
    }
    state.chevron.Background(b.normal);
    state.chevron.BorderBrush(b.border);
    state.chevron.Foreground(b.foreground);
    if (state.countText) {
        if (themed)
            state.countText.Foreground(brush(s.text));
        else
            state.countText.ClearValue(Controls::TextBlock::ForegroundProperty());
    }

    ApplyPanelLook(state, s, themed);
    ApplyFlyoutLooks(state, s, themed);
    UpdateCount(state);
    AnimateArrow(state);
}

void ShowInner(DrawerState& state) {
    if (state.selectedModels.empty() || state.open)
        return;
    auto s = CurrentSettings();
    if (state.arrow)
        state.arrow.Glyph(ChevronGlyph(
            state, s.theme && !state.accessibility.HighContrast() ? s : Settings{.theme = false}));
    state.inner.XamlRoot(state.root.XamlRoot());
    // Anchor to the entire outer surface, not the footer button: the
    // placement must clear all of the outer drawer.
    Controls::Primitives::FlyoutShowOptions options;
    options.Placement(InnerPlacementMode(state, s));
    state.inner.ShowAt(state.root, options);
}

// The first refresh after the panel loads opens the second drawer when the
// owner asked for it and it has icons.
void TryAutoOpen(DrawerState& state) {
    if (!state.autoOpenPending || state.changing || state.closing || state.refreshDeferred)
        return;
    state.autoOpenPending = false;
    auto s = CurrentSettings();
    if (s.autoOpen && state.root.IsLoaded() && IsWindowVisible(state.outerWindow))
        ShowInner(state);
}

Controls::Border CreateDrawerFooter() {
    // Create native controls directly, avoiding standalone XAML resource parsing
    // in Explorer's unpackaged island.
    // The Button retains its Windows template, including hover/focus states.
    Controls::Border footer;
    footer.Height(40);
    footer.Padding(Thickness{8, 3, 8, 4});
    footer.BorderThickness(Thickness{0, 1, 0, 0});
    footer.CornerRadius(CornerRadius{0, 0, 8, 8});
    Button button;
    button.Width(40);
    button.Height(32);
    button.MinWidth(40);
    button.MinHeight(0);
    button.Padding(Thickness{0, 0, 0, 0});
    button.BorderThickness(Thickness{1, 1, 1, 1});
    button.CornerRadius(CornerRadius{8, 8, 8, 8});
    button.HorizontalAlignment(HorizontalAlignment::Right);
    button.VerticalAlignment(VerticalAlignment::Center);
    // Lightweight styling: the template reads these keys for its hover and
    // pressed states. They must be present before the template is applied.
    auto& b = g_chevronBrushes;
    if (!b.normal) {
        b.normal = Media::SolidColorBrush();
        b.hover = Media::SolidColorBrush();
        b.pressed = Media::SolidColorBrush();
        b.foreground = Media::SolidColorBrush();
        b.border = Media::SolidColorBrush();
        b.borderHover = Media::SolidColorBrush();
        b.borderPressed = Media::SolidColorBrush();
    }
    auto resources = button.Resources();
    auto put = [&](PCWSTR key, Media::SolidColorBrush const& value) {
        resources.Insert(winrt::box_value(key), value);
    };
    put(L"ButtonBackground", b.normal);
    put(L"ButtonBackgroundPointerOver", b.hover);
    put(L"ButtonBackgroundPressed", b.pressed);
    put(L"ButtonForeground", b.foreground);
    put(L"ButtonForegroundPointerOver", b.foreground);
    put(L"ButtonForegroundPressed", b.foreground);
    put(L"ButtonBorderBrush", b.border);
    put(L"ButtonBorderBrushPointerOver", b.borderHover);
    put(L"ButtonBorderBrushPressed", b.borderPressed);
    footer.Child(button);
    return footer;
}
// END SEAMLESS LOOK

// BEGIN HOVER ZOOM
// Same recipe as Seamless Dock Animation's dock: the size follows the pointer
// distance on a cosine curve, fades in and out over 250 ms, and is eased every
// frame. The whole icon button grows from its centre, hover box included.
constexpr double kZoomFocusMs = 250.0;
constexpr double kZoomLerp = 60.0;
using ZoomIcon = DrawerState::ZoomIcon;
using ZoomArea = DrawerState::ZoomArea;

void ZoomCollect(DependencyObject const& node, std::vector<FrameworkElement>& out, int depth) {
    if (depth > 24)
        return;
    int count = Media::VisualTreeHelper::GetChildrenCount(node);
    for (int i = 0; i < count; ++i) {
        auto child = Media::VisualTreeHelper::GetChild(node, i);
        auto element = child.try_as<FrameworkElement>();
        if (element && winrt::get_class_name(element) == L"SystemTray.NotifyIconView") {
            out.push_back(element);
            continue;
        }
        ZoomCollect(child, out, depth + 1);
    }
}

bool IsIdentity(Media::Transform const& transform) {
    if (!transform)
        return true;
    if (auto m = transform.try_as<Media::MatrixTransform>()) {
        auto v = m.Matrix();
        return v.M11 == 1 && v.M12 == 0 && v.M21 == 0 && v.M22 == 1 && v.OffsetX == 0 &&
               v.OffsetY == 0;
    }
    return false;
}

void ZoomWrite(ZoomIcon& icon, double scale) {
    icon.transform.ScaleX(scale);
    icon.transform.ScaleY(scale);
    icon.shown = scale;
}

// Puts the icon back exactly as the tray had it.
void ZoomRelease(ZoomIcon& icon) noexcept {
    try {
        if (!icon.transform)
            return;
        if (auto view = icon.view.get()) {
            if (view.RenderTransform() == icon.transform)
                view.ClearValue(UIElement::RenderTransformProperty());
        }
        icon.transform = nullptr;
    } catch (...) {
    }
}

void ZoomRebuild(ZoomArea& area) {
    std::vector<FrameworkElement> views;
    ZoomCollect(area.scope, views, 0);
    std::vector<ZoomIcon> next;
    for (auto const& view : views) {
        double w = view.ActualWidth(), h = view.ActualHeight();
        if (w < 1 || h < 1 || view.Visibility() != Visibility::Visible)
            continue;
        ZoomIcon icon;
        for (auto& old : area.icons) {
            if (old.transform && old.view.get() == view) {
                icon = std::move(old);
                break;
            }
        }
        if (!icon.transform) {
            // Only take an icon nobody else transforms.
            if (!IsIdentity(view.RenderTransform()))
                continue;
            icon.view = winrt::make_weak(view);
            icon.transform = Media::CompositeTransform();
            view.RenderTransform(icon.transform);
        }
        try {
            icon.transform.CenterX(w / 2);
            icon.transform.CenterY(h / 2);
            // A centred scale never moves the centre, so this is the resting spot.
            auto p = view.TransformToVisual(area.host)
                         .TransformPoint({static_cast<float>(w / 2), static_cast<float>(h / 2)});
            icon.cx = p.X;
            icon.cy = p.Y;
        } catch (...) {
            ZoomRelease(icon);
            continue;
        }
        next.push_back(std::move(icon));
    }
    for (auto& old : area.icons)
        ZoomRelease(old);
    area.icons = std::move(next);
}

void ZoomDrop(ZoomArea& area) noexcept {
    area.inside = false;
    area.intensity = 0;
    for (auto& icon : area.icons)
        ZoomRelease(icon);
    area.icons.clear();
}

// Returns true while the area still needs frames.
bool ZoomAdvance(ZoomArea& area, Settings const& s, double step, double alpha,
                 std::chrono::steady_clock::time_point now) {
    if (!area.host)
        return false;
    area.intensity = area.inside ? std::min(1.0, area.intensity + step)
                                 : std::max(0.0, area.intensity - step);
    if (area.inside && now - area.lastScan > std::chrono::milliseconds(400)) {
        ZoomRebuild(area);
        area.lastScan = now;
    }
    double reach = s.zoomReach;
    double peak = s.zoomSize / 100.0;
    bool moving = false;
    for (auto& icon : area.icons) {
        if (!icon.transform)
            continue;
        double target = 1.0;
        double d = std::hypot(area.mx - icon.cx, area.my - icon.cy);
        if (area.intensity > 0 && d < reach) {
            double factor = (std::cos(d / reach * 3.14159265358979) + 1.0) / 2.0;
            target = 1.0 + (peak - 1.0) * factor * area.intensity;
        }
        icon.scale += (target - icon.scale) * alpha;
        if (std::abs(target - icon.scale) < 0.0005)
            icon.scale = target;
        if (std::abs(icon.scale - icon.shown) > 0.0001) {
            if (!icon.view.get()) {
                icon.transform = nullptr;
                continue;
            }
            ZoomWrite(icon, icon.scale);
        }
        if (icon.scale != 1.0 || target != 1.0)
            moving = true;
    }
    if (!area.inside && area.intensity <= 0 && !moving) {
        ZoomDrop(area);
        return false;
    }
    return true;
}

bool CursorInWindow(HWND window) {
    POINT p;
    RECT r;
    return window && IsWindowVisible(window) && GetCursorPos(&p) && GetWindowRect(window, &r) &&
           PtInRect(&r, p);
}

void ZoomStop(DrawerState& state) noexcept {
    if (!state.zoomRender.value)
        return;
    try {
        Media::CompositionTarget::Rendering(state.zoomRender);
    } catch (...) {
    }
    state.zoomRender = {};
}

void ZoomFrame() {
    if (!g_drawer)
        return;
    auto& state = *g_drawer;
    auto now = std::chrono::steady_clock::now();
    double dt = std::clamp(std::chrono::duration<double>(now - state.zoomLast).count(), 0.0, 0.1);
    state.zoomLast = now;
    auto s = CurrentSettings();
    if (!s.theme || !s.zoom || state.nativeDragActive || state.closing) {
        ZoomDrop(state.zoomMain);
        ZoomDrop(state.zoomInner);
        ZoomStop(state);
        return;
    }
    // A fast flick off the panel can skip the exit event.
    if (state.zoomMain.inside && !CursorInWindow(state.outerWindow))
        state.zoomMain.inside = false;
    double step = dt * 1000.0 / kZoomFocusMs;
    double alpha = std::clamp(1.0 - std::exp(-kZoomLerp * dt), 0.0, 1.0);
    bool busy = ZoomAdvance(state.zoomMain, s, step, alpha, now);
    busy = ZoomAdvance(state.zoomInner, s, step, alpha, now) || busy;
    if (!busy)
        ZoomStop(state);
}

void ZoomStart(DrawerState& state) {
    if (state.zoomRender.value)
        return;
    state.zoomLast = std::chrono::steady_clock::now();
    state.zoomRender = Media::CompositionTarget::Rendering([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        if (g_unloading || !g_runtimeAvailable)
            return;
        try {
            ZoomFrame();
        } catch (...) {
            LogException(L"Hover zoom frame");
            if (g_drawer) {
                ZoomDrop(g_drawer->zoomMain);
                ZoomDrop(g_drawer->zoomInner);
                ZoomStop(*g_drawer);
            }
        }
    });
}

void ZoomAttach(ZoomArea& area, FrameworkElement const& host, FrameworkElement const& scope,
                bool inner) {
    area.host = host;
    area.scope = scope;
    Input::PointerEventHandler moved(
        [inner](IInspectable const&, Input::PointerRoutedEventArgs const& args) noexcept {
            UiCallbackScope callbackScope;
            if (g_unloading || !g_runtimeAvailable || !g_drawer)
                return;
            try {
                auto& state = *g_drawer;
                auto& a = inner ? state.zoomInner : state.zoomMain;
                if (!a.host || state.nativeDragActive || state.closing)
                    return;
                if (args.Pointer().PointerDeviceType() ==
                    winrt::Windows::Devices::Input::PointerDeviceType::Touch)
                    return;
                auto s = CurrentSettings();
                if (!s.theme || !s.zoom)
                    return;
                auto p = args.GetCurrentPoint(a.host).Position();
                a.mx = p.X;
                a.my = p.Y;
                if (!a.inside) {
                    a.inside = true;
                    a.lastScan = {};
                }
                ZoomStart(state);
            } catch (...) {
                LogException(L"Hover zoom move");
            }
        });
    Input::PointerEventHandler exited(
        [inner](IInspectable const&, Input::PointerRoutedEventArgs const& args) noexcept {
            UiCallbackScope callbackScope;
            if (g_unloading || !g_runtimeAvailable || !g_drawer)
                return;
            try {
                auto& a = inner ? g_drawer->zoomInner : g_drawer->zoomMain;
                if (!a.host)
                    return;
                // A child leaving still bubbles here; only a real exit counts.
                auto p = args.GetCurrentPoint(a.host).Position();
                if (p.X > 0 && p.Y > 0 && p.X < a.host.ActualWidth() &&
                    p.Y < a.host.ActualHeight())
                    return;
                a.inside = false;
            } catch (...) {
                LogException(L"Hover zoom exit");
            }
        });
    area.moved = winrt::box_value(moved);
    area.exited = winrt::box_value(exited);
    host.AddHandler(UIElement::PointerMovedEvent(), area.moved, true);
    host.AddHandler(UIElement::PointerExitedEvent(), area.exited, true);
}

void ZoomTeardown(DrawerState& state) noexcept {
    ZoomStop(state);
    for (auto* area : {&state.zoomMain, &state.zoomInner}) {
        try {
            if (area->host && area->moved)
                area->host.RemoveHandler(UIElement::PointerMovedEvent(), area->moved);
            if (area->host && area->exited)
                area->host.RemoveHandler(UIElement::PointerExitedEvent(), area->exited);
        } catch (...) {
        }
        ZoomDrop(*area);
        area->host = nullptr;
        area->scope = nullptr;
        area->moved = nullptr;
        area->exited = nullptr;
    }
}
// END HOVER ZOOM

void InstallDrawer(Grid const& root) {
    if (g_unloading || g_identityState != 2 || !root || root.Name() != L"OverflowRootGrid")
        return;
    if (g_drawer && g_drawer->root == root)
        return;
    if (g_drawer)
        RemoveDrawer();
    auto items =
        FindDescendant(root, L"Windows.UI.Xaml.Controls.ItemsControl").try_as<ItemsControl>();
    if (!items || root.RowDefinitions().Size() > 1) {
        Wh_Log(L"Unsupported overflow layout; nothing changed");
        return;
    }

    auto state = std::make_unique<DrawerState>();
    state->root = root;
    EnumThreadWindows(
        GetCurrentThreadId(),
        [](HWND window, LPARAM parameter) -> BOOL {
            wchar_t className[128];
            if (GetClassNameW(window, className, ARRAYSIZE(className)) &&
                wcscmp(className, L"TopLevelWindowForOverflowXamlIsland") == 0) {
                *reinterpret_cast<HWND*>(parameter) = window;
                return FALSE;
            }
            return TRUE;
        },
        reinterpret_cast<LPARAM>(&state->outerWindow));
    state->nativeItems = items;
    state->originalRowCount = root.RowDefinitions().Size();
    state->accessibility = winrt::Windows::UI::ViewManagement::AccessibilitySettings();
    state->footer = CreateDrawerFooter();
    state->chevron = state->footer.Child().as<Button>();
    state->inner = Flyout();
    state->innerItems = ItemsControl();
    state->picker = Controls::MenuFlyout();
    state->menuTimer = DispatcherTimer();
    state->menuTimer.Interval(winrt::Windows::Foundation::TimeSpan{std::chrono::milliseconds(100)});
    auto arrow = Controls::FontIcon();
    arrow.FontFamily(Media::FontFamily(L"Segoe Fluent Icons"));
    arrow.Glyph(L"\xE70E");  // Official ChevronUp font asset, not a literal caret.
    arrow.FontSize(12);
    arrow.RenderTransformOrigin(winrt::Windows::Foundation::Point{0.5f, 0.5f});
    state->arrowRotation = Media::RotateTransform();
    arrow.RenderTransform(state->arrowRotation);
    state->arrow = arrow;
    state->countText = Controls::TextBlock();
    state->countText.FontSize(11);
    state->countText.FontWeight(winrt::Windows::UI::Text::FontWeights::SemiBold());
    state->countText.Margin(Thickness{6, 0, 0, 0});
    state->countText.VerticalAlignment(VerticalAlignment::Center);
    state->countText.Visibility(Visibility::Collapsed);
    Controls::StackPanel chevronContent;
    chevronContent.Orientation(Controls::Orientation::Horizontal);
    chevronContent.VerticalAlignment(VerticalAlignment::Center);
    chevronContent.Children().Append(arrow);
    chevronContent.Children().Append(state->countText);
    state->chevron.Content(chevronContent);
    // The native panel background, restyled when the theme is on.
    for (auto const& child : root.Children()) {
        auto border = child.try_as<Controls::Border>();
        if (!border)
            continue;
        if (border.Name() == L"OverflowFlyoutBackgroundBorder") {
            state->panelBorder = border;
            break;
        }
        if (!state->panelBorder)
            state->panelBorder = border;
    }
    Wh_Log(L"Panel background border: %s",
           state->panelBorder ? state->panelBorder.Name().c_str() : L"<none>");
    Automation::AutomationProperties::SetName(
        state->chevron, Text(L"Rarely used tray icons", L"较少使用的托盘图标"));
    state->inner.Placement(Controls::Primitives::FlyoutPlacementMode::Top);
    // A plain Flyout defaults to rendering inside the XAML island HWND. The
    // tray island is only as large as the outer drawer, so that default can
    // replace/cover its visible surface. Use the same native windowed-popup
    // capability that MenuFlyout uses, rather than overriding light dismiss.
    state->inner.ShouldConstrainToRootBounds(false);
    state->innerItems.MinWidth(40);
    state->innerItems.MinHeight(40);
    state->innerItems.Background(Media::SolidColorBrush(Color{0, 0, 0, 0}));
    state->inner.Content(state->innerItems);

    g_drawer = std::move(state);
    g_hasDrawer = true;
    auto& current = *g_drawer;
    struct InstallRollback {
        bool committed{};
        ~InstallRollback() noexcept {
            if (!committed) {
                try {
                    RemoveDrawer();
                } catch (...) {
                    LogException(L"Roll back incomplete attachment");
                }
            }
        }
    } rollback;
    if (root.RowDefinitions().Size() == 0) {
        auto row = Controls::RowDefinition();
        row.Height(GridLength{1, GridUnitType::Auto});
        root.RowDefinitions().Append(row);
    }
    auto footerRow = Controls::RowDefinition();
    footerRow.Height(GridLength{1, GridUnitType::Auto});
    root.RowDefinitions().Append(footerRow);
    Grid::SetRow(current.footer, 1);
    for (auto const& child : root.Children()) {
        if (child == items)
            continue;
        current.rootProperties.emplace_back(child, Grid::RowSpanProperty());
        if (auto element = child.try_as<FrameworkElement>())
            Grid::SetRowSpan(element, 2);
    }
    current.click = current.chevron.Click([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        try {
            if (!g_drawer || g_unloading)
                return;
            auto& state = *g_drawer;
            if (state.selectedModels.empty())
                return;
            if (state.open)
                state.inner.Hide();
            else
                ShowInner(state);
        } catch (...) {
            LogException(L"Open inner drawer");
        }
    });
    current.rightTap = current.chevron.RightTapped(
        [](auto const&, Input::RightTappedRoutedEventArgs const& args) noexcept {
            UiCallbackScope callbackScope;
            try {
                args.Handled(true);
                ShowRestoreMenu();
            } catch (...) {
                LogException(L"Open restore menu");
            }
        });
    current.opened = current.inner.Opened([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        if (g_unloading || !g_runtimeAvailable)
            return;
        if (g_drawer) {
            g_drawer->open = true;
            Wh_Log(L"Inner drawer opened; outerWindowVisible=%d",
                   IsWindowVisible(g_drawer->outerWindow));
            try {
                AnimateArrow(*g_drawer);
            } catch (...) {
                LogException(L"Rotate chevron open");
            }
        }
    });
    current.innerClosing = current.inner.Closing(
        [](auto const&, Controls::Primitives::FlyoutBaseClosingEventArgs const& args) noexcept {
            UiCallbackScope callbackScope;
            if (g_unloading || !g_runtimeAvailable)
                return;
            try {
                if (g_drawer && ShouldHoldForMenu(*g_drawer)) {
                    args.Cancel(true);
                    Wh_Log(L"Inner light-dismiss deferred while owned app menu is active");
                }
            } catch (...) {
                LogException(L"Keep inner drawer during app menu");
            }
        });
    current.previewKey = current.innerItems.PreviewKeyDown(
        [](auto const&, Input::KeyRoutedEventArgs const& args) noexcept {
            UiCallbackScope callbackScope;
            if (g_unloading || !g_runtimeAvailable)
                return;
            try {
                using winrt::Windows::System::VirtualKey;
                if (args.Key() == VirtualKey::Application ||
                    (args.Key() == VirtualKey::F10 && (GetKeyState(VK_SHIFT) & 0x8000)))
                    ArmMenuHold();
            } catch (...) {
                LogException(L"Arm keyboard context menu");
            }
        });
    current.menuTick = current.menuTimer.Tick([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        if (g_unloading || !g_runtimeAvailable || !g_drawer)
            return;
        try {
            auto& state = *g_drawer;
            if (ShouldHoldForMenu(state))
                return;
            bool replay = state.deferredNativeDismiss;
            void* manager = state.nativeManager;
            ResetMenuHold(state);
            if (state.refreshDeferred)
                QueueCollectionRefresh();
            Wh_Log(L"Context-menu hold ended; native dismissal reevaluation=%d", replay);
            if (replay && manager && LightDismissConditions_Original) {
                LightDismissConditions_Original(manager);
            }
        } catch (...) {
            LogException(L"Release context-menu hold");
        }
    });
    current.innerLayout = current.innerItems.LayoutUpdated([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        if (g_unloading || !g_runtimeAvailable || !g_drawer || !g_drawer->open ||
            g_drawer->layoutReports >= 3)
            return;
        try {
            auto& state = *g_drawer;
            auto icon = FindDescendant(state.innerItems, L"SystemTray.NotifyIconView");
            Wh_Log(
                L"Inner layout: items=%u nativeView=%d loaded=%d size=%.1fx%.1f modelMatch=%d outerLoaded=%d outerWindowVisible=%d",
                state.innerItems.Items().Size(), !!icon, icon ? icon.IsLoaded() : false,
                icon ? icon.ActualWidth() : 0.0, icon ? icon.ActualHeight() : 0.0,
                icon ? std::find(state.selectedModels.begin(), state.selectedModels.end(),
                                 icon.DataContext()) != state.selectedModels.end()
                     : false,
                state.root.IsLoaded(), IsWindowVisible(state.outerWindow));
            ++state.layoutReports;
        } catch (...) {
            LogException(L"Inspect generated inner icon");
        }
    });
    current.closed = current.inner.Closed([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        if (g_unloading || !g_runtimeAvailable)
            return;
        if (g_drawer) {
            g_drawer->open = false;
            ZoomDrop(g_drawer->zoomInner);
            ResetMenuHold(*g_drawer);
            try {
                AnimateArrow(*g_drawer);
            } catch (...) {
                LogException(L"Rotate chevron closed");
            }
        }
        Wh_Log(L"Inner drawer closed through native Flyout lifecycle");
    });
    current.loaded = root.Loaded([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        if (g_unloading || !g_runtimeAvailable)
            return;
        Wh_Log(L"Native outer drawer loaded");
        if (g_drawer) {
            auto s = CurrentSettings();
            g_drawer->autoOpenPending = s.theme && s.autoOpen;
        }
        QueueCollectionRefresh();
    });
    current.unloaded = root.Unloaded([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        if (g_unloading || !g_runtimeAvailable)
            return;
        try {
            if (g_drawer) {
                ZoomDrop(g_drawer->zoomMain);
                ZoomDrop(g_drawer->zoomInner);
            }
            if (!g_drawer || g_drawer->changing || g_drawer->closing)
                return;
            if (g_drawer->open)
                Wh_Log(L"COEXISTENCE NOT VERIFIED: outer unloaded while inner was open");
            g_drawer->inner.Hide();
            g_drawer->picker.Hide();
        } catch (...) {
            LogException(L"Outer drawer unloaded");
        }
    });
    current.footerLoaded = current.footer.Loaded([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        if (g_unloading || !g_runtimeAvailable || !g_drawer)
            return;
        try {
            UpdateDrawerAppearance(*g_drawer);
            Wh_Log(L"Drawer footer loaded: surface=%.1fx%.1f button=%.1fx%.1f theme=%d",
                   g_drawer->footer.ActualWidth(), g_drawer->footer.ActualHeight(),
                   g_drawer->chevron.ActualWidth(), g_drawer->chevron.ActualHeight(),
                   static_cast<int>(g_drawer->footer.ActualTheme()));
        } catch (...) {
            LogException(L"Refresh loaded footer appearance");
        }
    });
    current.appearanceChanged = root.ActualThemeChanged([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        if (!g_unloading && g_runtimeAvailable)
            PostMessageW(g_uiWindow, kRefreshAppearanceMessage, 0, 0);
    });
    // Avoid an off-thread AccessibilitySettings delegate outliving this DLL.
    // High contrast is sampled when the footer loads and on UI theme changes.
    UpdateDrawerAppearance(current);
    root.Children().Append(current.footer);
    // A normal revocable event avoids a throwing property-callback removal.
    // The mirrored collection still handles icon additions/removals directly.
    current.sourceLayout = current.nativeItems.LayoutUpdated([](auto const&, auto const&) noexcept {
        UiCallbackScope callbackScope;
        if (!g_unloading && g_runtimeAvailable && g_drawer && !g_drawer->changing &&
            !g_drawer->closing) {
            try {
                if (g_drawer->originalItemsSource &&
                    g_drawer->nativeItems.ItemsSource() != g_drawer->expectedSource)
                    QueueCollectionRefresh();
            } catch (...) {
                LogException(L"Observe native source replacement");
            }
        }
    });
    ZoomAttach(current.zoomMain, root, current.nativeItems, false);
    ZoomAttach(current.zoomInner, current.innerItems, current.innerItems, true);
    QueueCollectionRefresh();
    rollback.committed = true;
    Wh_Log(L"Seamless tray drawer entry point attached");
}

using Initialize_t = void(WINAPI*)(void*);
Initialize_t Initialize_Original;

constexpr WCHAR kUiClass[] = L"Windhawk_SeamlessTrayDrawer_1";
HMODULE g_selfModule;

LRESULT CALLBACK UiWindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    // Normal messages can invoke app/XAML code and enter nested message loops.
    // Cleanup messages deliberately stay outside this scope.
    std::optional<UiCallbackScope> work;
    if (message == kRefreshAppearanceMessage || message == kRefreshCollectionMessage ||
        message == kCollectDroppedIconMessage)
        work.emplace();
    if (message == kRefreshAppearanceMessage) {
        if (!g_unloading && g_runtimeAvailable && g_drawer && !g_drawer->closing) {
            try {
                UpdateDrawerAppearance(*g_drawer);
            } catch (...) {
                LogException(L"Refresh drawer appearance");
            }
        }
        return 0;
    }
    if (message == kRefreshCollectionMessage) {
        if (g_unloading || !g_runtimeAvailable || !g_drawer)
            return 0;
        g_drawer->refreshQueued = false;
        try {
            RefreshClassification(*g_drawer);
            TryAutoOpen(*g_drawer);
        } catch (...) {
            LogException(L"Refresh saved collection");
        }
        return 0;
    }
    if (message == kCollectDroppedIconMessage) {
        if (g_unloading || !g_runtimeAvailable || !g_drawer)
            return 0;
        try {
            // No model pointers or callbacks are carried in the queued message.
            // Defer until native pointer-release and capture cleanup finish.
            auto candidate = std::move(g_drawer->pendingDrop);
            g_drawer->pendingDrop = {};
            if (candidate.model && SelectIcon(candidate)) {
                Wh_Log(L"Chevron drop committed; outer=%u inner=%u",
                       g_drawer->nativeItems.Items().Size(), g_drawer->innerItems.Items().Size());
            }
        } catch (...) {
            LogException(L"Collect dropped tray icon");
        }
        return 0;
    }
    if (message == kRemoveDrawerMessage) {
        if (!g_runtimeAvailable)
            return 0;
        if (g_uiCallbackDepth) {
            g_cleanupPending = true;
            return 0;
        }
        RemoveDrawer();
        SetEvent(g_cleanupEvent);
        return 1;
    }
    if (message == WM_NCDESTROY) {
        RemoveDrawer();
        HWND expected = window;
        if (g_uiWindow.compare_exchange_strong(expected, nullptr))
            g_uiThread = 0;
    }
    if (message == WM_CLOSE) {
        DestroyWindow(window);
        return 0;
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

// BEGIN UI CLASS OWNERSHIP
ATOM g_uiClassAtom;

bool EnsureUiClassRegistered() {
    if (g_uiClassAtom)
        return true;
    WNDCLASSW windowClass{};
    windowClass.lpfnWndProc = UiWindowProc;
    windowClass.hInstance = g_selfModule;
    windowClass.lpszClassName = kUiClass;
    g_uiClassAtom = RegisterClassW(&windowClass);
    // A matching name/HINSTANCE can belong to an earlier DLL mapped at this
    // address. Only our own successful registration proves WndProc ownership.
    if (!g_uiClassAtom) {
        Wh_Log(L"UI class registration rejected: error=%lu", GetLastError());
        return false;
    }
    return true;
}

bool UnregisterOwnedUiClass() {
    if (!g_uiClassAtom)
        return true;
    if (!UnregisterClassW(MAKEINTATOM(g_uiClassAtom), g_selfModule)) {
        Wh_Log(L"Owned UI class could not be unregistered: error=%lu", GetLastError());
        return false;
    }
    g_uiClassAtom = 0;
    return true;
}
// END UI CLASS OWNERSHIP

bool RememberUiThread() {
    if (IsWindow(g_uiWindow))
        return g_uiThread == GetCurrentThreadId();
    if (!EnsureUiClassRegistered())
        return false;
    auto window = CreateWindowExW(0, kUiClass, L"", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr,
                                  g_selfModule, nullptr);
    if (!window) {
        return false;
    }
    auto threadHandle = OpenThread(SYNCHRONIZE, FALSE, GetCurrentThreadId());
    if (!threadHandle) {
        DestroyWindow(window);
        return false;
    }
    if (g_uiThreadHandle)
        CloseHandle(g_uiThreadHandle);
    g_uiThreadHandle = threadHandle;
    g_uiWindow = window;
    g_uiThread = GetCurrentThreadId();
    return true;
}

void WINAPI Initialize_Hook(void* self) {
    UiCallbackScope callbackScope;
    Initialize_Original(self);
    AcquireSRWLockExclusive(&g_attachmentLock);
    struct UnlockAttachment {
        ~UnlockAttachment() { ReleaseSRWLockExclusive(&g_attachmentLock); }
    } unlock;
    if (g_unloading)
        return;
    try {
        // The composed root slot is taken from the official tray-spacing mod.
        Grid root{nullptr};
        auto unknown = reinterpret_cast<IUnknown**>(self)[5];
        if (!unknown ||
            FAILED(unknown->QueryInterface(winrt::guid_of<Grid>(), winrt::put_abi(root))))
            return;
        if (!RememberUiThread()) {
            Wh_Log(L"No UI-thread cleanup endpoint; attachment skipped");
            return;
        }
        InstallDrawer(root);
        if (g_drawer && g_drawer->root == root)
            g_drawer->nativeManager = self;
    } catch (...) {
        LogException(L"Attach to native overflow");
    }
}

using Hide_t = void(WINAPI*)(void*);
Hide_t Hide_Original;
Hide_t HideWindow_Original;
void WINAPI HideWindow_Hook(void* self) {
    UiCallbackScope callbackScope;
    if (DeferNativeDismiss(self, L"HideWindow"))
        return;
    bool inspect = !g_unloading && g_uiThread == GetCurrentThreadId() && g_drawer;
    if (inspect)
        Wh_Log(L"Native HideWindow: innerOpen=%d outerVisibleBefore=%d", g_drawer->open,
               IsWindowVisible(g_drawer->outerWindow));
    HideWindow_Original(self);
    if (inspect && g_drawer)
        Wh_Log(L"Native HideWindow finished: outerVisibleAfter=%d",
               IsWindowVisible(g_drawer->outerWindow));
}

void WINAPI LightDismissConditions_Hook(void* self) {
    UiCallbackScope callbackScope;
    if (!DeferNativeDismiss(self, L"light-dismiss conditions"))
        LightDismissConditions_Original(self);
}

void WINAPI HideAnimation_Hook(void* self) {
    UiCallbackScope callbackScope;
    if (!DeferNativeDismiss(self, L"hide animation"))
        HideAnimation_Original(self);
}

using NotifyPointerPressed_t = void(WINAPI*)(void*, void* const*);
NotifyPointerPressed_t NotifyPointerPressed_Original;
void WINAPI NotifyPointerPressed_Hook(void* self, void* const* args) {
    UiCallbackScope callbackScope;
    if (!g_unloading && g_runtimeAvailable && g_uiThread == GetCurrentThreadId() && g_drawer &&
        args && *args) {
        try {
            IInspectable event{nullptr};
            winrt::copy_from_abi(event, *args);
            auto pointerArgs = event.as<Input::PointerRoutedEventArgs>();
            auto& state = *g_drawer;
            ClearDragSource(state);
            if (pointerArgs.GetCurrentPoint(state.nativeItems).Properties().IsLeftButtonPressed()) {
                auto candidate = OuterCandidateFromSource(state, pointerArgs.OriginalSource());
                if (candidate.model) {
                    state.dragSource = std::move(candidate);
                    state.dragSourceView = self;
                    state.dragPointerId = pointerArgs.Pointer().PointerId();
                }
            }
            auto element = pointerArgs.OriginalSource().try_as<DependencyObject>();
            bool inInner = false;
            for (int i = 0; element && i < 64; ++i) {
                if (element == g_drawer->innerItems) {
                    inInner = true;
                    break;
                }
                element = Media::VisualTreeHelper::GetParent(element);
            }
            if (state.open && inInner &&
                pointerArgs.GetCurrentPoint(g_drawer->innerItems)
                    .Properties()
                    .IsRightButtonPressed())
                ArmMenuHold();
        } catch (...) {
            LogException(L"Identify inner-icon context gesture");
        }
    }
    // Always preserve the native handler, event arguments and app notification.
    NotifyPointerPressed_Original(self, args);
}

using NativeDrag_t = void(WINAPI*)(void*, void*, void* const*);
NativeDrag_t DragMove_Original;
NativeDrag_t DoDrop_Original;
NativeDismiss_t EndDrag_Original;

void WINAPI DragMove_Hook(void* manager, void* sourceView, void* const* args) {
    UiCallbackScope callbackScope;
    DragMove_Original(manager, sourceView, args);
    if (g_unloading || !g_runtimeAvailable || g_uiThread != GetCurrentThreadId() || !g_drawer ||
        !args || !*args)
        return;
    try {
        IInspectable event{nullptr};
        winrt::copy_from_abi(event, *args);
        auto& state = *g_drawer;
        state.nativeDragActive = state.dragSourceView == sourceView;
        bool over = IsChevronDrop(state, sourceView, event.as<Input::PointerRoutedEventArgs>());
        if (over != state.dragOverChevron) {
            state.dragOverChevron = over;
            VisualStateManager::GoToState(state.chevron, over ? L"PointerOver" : L"Normal", true);
        }
    } catch (...) {
        LogException(L"Inspect native drag over chevron");
    }
}

void WINAPI EndDrag_Hook(void* manager) {
    UiCallbackScope callbackScope;
    EndDrag_Original(manager);
    if (!g_unloading && g_runtimeAvailable && g_uiThread == GetCurrentThreadId() && g_drawer) {
        try {
            ClearDragSource(*g_drawer);
        } catch (...) {
            LogException(L"Clear native drag source");
        }
    }
}

void WINAPI DoDrop_Hook(void* manager, void* sourceView, void* const* args) {
    UiCallbackScope callbackScope;
    IconCandidate dropped;
    if (!g_unloading && g_runtimeAvailable && g_uiThread == GetCurrentThreadId() && g_drawer &&
        args && *args && IsWindow(g_uiWindow)) {
        try {
            IInspectable event{nullptr};
            winrt::copy_from_abi(event, *args);
            if (IsChevronDrop(*g_drawer, sourceView, event.as<Input::PointerRoutedEventArgs>()))
                dropped = g_drawer->dragSource;
        } catch (...) {
            LogException(L"Validate native drop target");
        }
    }
    if (!dropped.model) {
        DoDrop_Original(manager, sourceView, args);
        return;
    }
    // The original DoDrop ends via this same native routine. End the drag
    // without issuing a Windows reorder/pin operation on this custom target.
    EndDrag_Hook(manager);
    if (!g_drawer || g_unloading)
        return;
    g_drawer->pendingDrop = std::move(dropped);
    if (!PostMessageW(g_uiWindow, kCollectDroppedIconMessage, 0, 0)) {
        g_drawer->pendingDrop = {};
        Wh_Log(L"Could not queue collection; icon left in original drawer");
    } else
        Wh_Log(L"Native outer-icon drag released over nested chevron");
}
void WINAPI Hide_Hook(void* self) {
    UiCallbackScope callbackScope;
    try {
        if (g_uiThread == GetCurrentThreadId() && g_drawer) {
            if (g_drawer->open)
                Wh_Log(L"Native outer Hide requested while inner is open; inspect coexistence");
            g_drawer->inner.Hide();
            g_drawer->picker.Hide();
        }
    } catch (...) {
        LogException(L"Native outer hide");
    }
    // Do not suppress native close requests or keep an orphaned inner window.
    Hide_Original(self);
}

HMODULE GetSystemTrayModuleHandle() {
    if (auto module = GetModuleHandleW(L"SystemTray.dll"))
        return module;
    if (auto module = GetModuleHandleW(L"Taskbar.View.dll")) {
        auto resource = FindResourceW(module, MAKEINTRESOURCEW(VS_VERSION_INFO), RT_VERSION);
        auto loaded = resource ? LoadResource(module, resource) : nullptr;
        auto bytes = loaded ? LockResource(loaded) : nullptr;
        VS_FIXEDFILEINFO* version{};
        UINT size{};
        if (bytes && VerQueryValueW(bytes, L"\\", reinterpret_cast<void**>(&version), &size) &&
            size >= sizeof(*version) && HIWORD(version->dwFileVersionMS) < 2604)
            return module;
    }
    return GetModuleHandleW(L"ExplorerExtensions.dll");
}

bool HookTrayModule(HMODULE module) {
    int expected = 0;
    if (!g_hookState.compare_exchange_strong(expected, 1))
        return g_hookState == 2;
    // SystemTray.dll, Taskbar.View.dll, ExplorerExtensions.dll
    WindhawkUtils::SYMBOL_HOOK hooks[] = {
        {{LR"(struct guid::guid const winrt::impl::guid_v<struct winrt::SystemTray::IIconViewModel>)"},
         &g_viewIid},
        {{LR"(const winrt::impl::produce<struct winrt::SystemTray::implementation::IconViewModel,struct winrt::SystemTray::IIconViewModel>::`vftable')"},
         &g_viewVtable},
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::SystemTray::implementation::IconViewModel,struct winrt::SystemTray::IIconViewModel>::get_Configuration(void * *))"},
         &g_getConfiguration},
        {{LR"(struct guid::guid const winrt::impl::guid_v<struct winrt::SystemTray::IIconConfiguration>)"},
         &g_configIid},
        {{LR"(const winrt::impl::produce<struct winrt::SystemTray::implementation::IconConfiguration,struct winrt::SystemTray::IIconConfiguration>::`vftable')"},
         &g_configVtable},
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::SystemTray::implementation::IconConfiguration,struct winrt::SystemTray::IIconConfiguration>::get_DataModel(void * *))"},
         &g_getDataModel},
        {{LR"(struct guid::guid const winrt::impl::guid_v<struct winrt::SystemTray::INotificationAreaIconsDataModel>)"},
         &g_modelIid},
        {{LR"(const winrt::impl::produce<struct winrt::SystemTray::implementation::NotificationAreaIconsDataModel,struct winrt::SystemTray::INotificationAreaIconsDataModel>::`vftable')"},
         &g_modelVtable},
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::SystemTray::implementation::NotificationAreaIconsDataModel,struct winrt::SystemTray::INotificationAreaIconsDataModel>::get_UDKObject(void * *))"},
         &g_getUdkObject},
        {{LR"(private: void __cdecl winrt::SystemTray::OverflowXamlIslandManager::InitializeIfNeeded(void))"},
         &Initialize_Original,
         Initialize_Hook},
        {{LR"(public: void __cdecl winrt::SystemTray::OverflowXamlIslandManager::Hide(void))"},
         &Hide_Original,
         Hide_Hook},
        {{LR"(private: void __cdecl winrt::SystemTray::OverflowXamlIslandManager::HideWindow(void))"},
         &HideWindow_Original,
         HideWindow_Hook},
        {{LR"(private: void __cdecl winrt::SystemTray::OverflowXamlIslandManager::OnLightDismissConditionsChanged(void))"},
         &LightDismissConditions_Original,
         LightDismissConditions_Hook},
        {{LR"(private: void __cdecl winrt::SystemTray::OverflowXamlIslandManager::HideAnimation(void))"},
         &HideAnimation_Original,
         HideAnimation_Hook},
        {{LR"(private: virtual void __cdecl winrt::SystemTray::implementation::NotifyIconView::OnPointerPressed(struct winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const &))"},
         &NotifyPointerPressed_Original,
         NotifyPointerPressed_Hook},
        {{LR"(public: void __cdecl winrt::SystemTray::implementation::DragDropManager::DragMove(struct winrt::SystemTray::implementation::NotifyIconView const &,struct winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const &))"},
         &DragMove_Original,
         DragMove_Hook},
        {{LR"(public: void __cdecl winrt::SystemTray::implementation::DragDropManager::DoDrop(struct winrt::SystemTray::implementation::NotifyIconView const &,struct winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const &))"},
         &DoDrop_Original,
         DoDrop_Hook},
        {{LR"(public: void __cdecl winrt::SystemTray::implementation::DragDropManager::EndDrag(void))"},
         &EndDrag_Original,
         EndDrag_Hook},
    };
    bool ok = WindhawkUtils::HookSymbols(module, hooks, ARRAYSIZE(hooks));
    g_hookState = ok ? 2 : 3;
    Wh_Log(L"Native overflow symbol resolution: %d", ok);
    return ok;
}

using LoadLibrary_t = decltype(&LoadLibraryExW);
LoadLibrary_t LoadLibrary_Original;
HMODULE WINAPI LoadLibrary_Hook(LPCWSTR file, HANDLE handle, DWORD flags) {
    auto module = LoadLibrary_Original(file, handle, flags);
    if (module && !g_unloading && g_identityState == 0 &&
        GetModuleHandleW(L"taskbar.dll") == module)
        ResolveNativeIdentity(module);
    if (module && g_hookState == 0 && !g_unloading && GetSystemTrayModuleHandle() == module) {
        if (HookTrayModule(module))
            Wh_ApplyHookOperations();
    }
    return module;
}

// A message-only window survives popup dismissal, so cleanup never depends on
// the temporary native overflow HWND. No queued function pointers are used.
bool RemoveOnUiThread() {
    DWORD thread = g_uiThread;
    HWND window = g_uiWindow;
    if (!thread)
        return !g_hasDrawer;
    if (thread == GetCurrentThreadId()) {
        if (g_uiCallbackDepth)
            return false;
        RemoveDrawer();
        return true;
    }
    // Posted work cannot interrupt an active delegate via SendMessage reentry.
    // If a nested message loop dispatches it, UiCallbackScope posts it again
    // only after the outermost callback has returned.
    ResetEvent(g_cleanupEvent);
    if (!PostMessageW(window, kRemoveDrawerMessage, 0, 0))
        return !g_hasDrawer;
    HANDLE waits[] = {g_cleanupEvent, g_uiThreadHandle};
    auto result = WaitForMultipleObjects(ARRAYSIZE(waits), waits, FALSE, INFINITE);
    return result == WAIT_OBJECT_0 || (result == WAIT_OBJECT_0 + 1 && !g_hasDrawer);
}

BOOL Wh_ModInit() {
    // Named-object presence is independent of callback thread ownership. Hold
    // it until hooks are removed, rather than holding a mutex across callbacks.
    std::unique_ptr<void, decltype(&CloseHandle)> instance(
        AcquireDrawerInstance(GetCurrentProcessId()), CloseHandle);
    if (!instance) {
        Wh_Log(L"Another tray drawer already runs in this Explorer; turn off Nested Tray Drawer first");
        return FALSE;
    }
    LoadSettings();
    if (!GetModuleHandleExW(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCWSTR>(&UiWindowProc), &g_selfModule))
        return FALSE;
    std::unique_ptr<void, decltype(&CloseHandle)> cleanupEvent(
        CreateEventW(nullptr, TRUE, FALSE, nullptr), CloseHandle);
    if (!cleanupEvent)
        return FALSE;
    auto kernel = GetModuleHandleW(L"kernelbase.dll");
    auto load = reinterpret_cast<LoadLibrary_t>(GetProcAddress(kernel, "LoadLibraryExW"));
    if (!load || !WindhawkUtils::SetFunctionHook(load, LoadLibrary_Hook, &LoadLibrary_Original))
        return FALSE;
    if (auto native = GetModuleHandleW(L"taskbar.dll"); native && !ResolveNativeIdentity(native))
        return FALSE;
    auto tray = GetSystemTrayModuleHandle();
    if (tray && !HookTrayModule(tray))
        return FALSE;
    if (!InitializeStorageNames())
        return FALSE;
    g_collectionMutex =
        CreateMutexW(nullptr, FALSE, L"Local\\Windhawk.SeamlessTrayDrawer.Collection.v1");
    if (!g_collectionMutex)
        return FALSE;
    if (!InitializeCollectionStorage()) {
        CloseHandle(g_collectionMutex);
        g_collectionMutex = nullptr;
        return FALSE;
    }
    g_cleanupEvent = cleanupEvent.release();
    g_instanceGuard = instance.release();
    Wh_Log(L"Experimental drawer initialized; open the hidden-icons drawer to attach");
    return TRUE;
}

void Wh_ModAfterInit() {
    if (g_identityState == 0) {
        if (auto native = GetModuleHandleW(L"taskbar.dll"))
            ResolveNativeIdentity(native);
    }
    if (g_hookState == 0) {
        auto tray = GetSystemTrayModuleHandle();
        if (tray && HookTrayModule(tray))
            Wh_ApplyHookOperations();
    }
}

void Wh_ModSettingsChanged() {
    LoadSettings();
    if (HWND window = g_uiWindow; window && !g_unloading)
        PostMessageW(window, kRefreshAppearanceMessage, 0, 0);
}

void Wh_ModBeforeUninit() {
    AcquireSRWLockExclusive(&g_attachmentLock);
    g_unloading = true;
    ReleaseSRWLockExclusive(&g_attachmentLock);
    // The endpoint is created before attachment. Its WM_NCDESTROY also removes
    // the drawer, so an absent endpoint never means a live orphaned drawer.
    bool ok = RemoveOnUiThread();
    HWND window = g_uiWindow;
    if (window)
        SendMessageW(window, WM_CLOSE, 0, 0);
    bool classRemoved = UnregisterOwnedUiClass();
    g_uiWindow = nullptr;
    g_uiThread = 0;
    Wh_Log(L"UI-thread cleanup completed: %d; owned class unregistered: %d", ok, classRemoved);
    if (g_collectionMutex) {
        CloseHandle(g_collectionMutex);
        g_collectionMutex = nullptr;
    }
    g_runtimeAvailable = false;
}

void Wh_ModUninit() {
    // Hooks are removed by the engine before this callback.
    if (g_uiThreadHandle) {
        CloseHandle(g_uiThreadHandle);
        g_uiThreadHandle = nullptr;
    }
    if (g_cleanupEvent) {
        CloseHandle(g_cleanupEvent);
        g_cleanupEvent = nullptr;
    }
    if (g_instanceGuard) {
        CloseHandle(g_instanceGuard);
        g_instanceGuard = nullptr;
    }
}
