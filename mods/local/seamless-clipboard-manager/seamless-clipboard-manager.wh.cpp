// ==WindhawkMod==
// @id              seamless-clipboard-manager
// @name            Seamless Clipboard Manager
// @description     Keeps everything you copy, text and images, in a searchable list you open with Win+V
// @version         1.3.0
// @author          DavidHiFi, Scott Brogden, Ditto contributors
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -luser32 -lshell32 -lshlwapi -lole32 -loleaut32 -luuid -ld2d1 -ldwrite -lwindowscodecs -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -loleacc -ladvapi32
// @license         GPL-3.0
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Clipboard Manager

Keeps what you copy in a list you open with Win+V: text, images, copied files and the formatting of text from web pages and Word. Pick a clip and press Enter to paste it.

## Features

- Search as you type to find an old clip.
- Pin the clips you use often with the pin button on each clip, drag pinned clips to put them in order, and sort clips into groups.
- Paste as plain text, or change the text as you paste it: upper or lower case, trimmed, on one line and more.
- Edit a clip's text before you paste it.
- Paste one of the first ten clips with a number key, with or without opening the list.
- Select several clips and paste them together.

## Coming from Ditto

This mod replaces Ditto. The first time it starts, it brings over your Ditto clips, groups and pins. It only reads Ditto's database and never changes it. Once your clips are here, quit Ditto so the two don't both save every copy.

Win+V normally opens the Windows clipboard history. The mod turns that off and takes Win+V for itself. If you'd rather keep Windows' own clipboard history, turn off "Replace Windows clipboard history" in the settings and pick another key.

## Keys in the list

| Key | What it does |
|---|---|
| Enter or double-click | Paste the selected clips |
| Shift+Enter | Paste as plain text |
| Ctrl+1 to Ctrl+0 | Paste clip 1 to 10 |
| Ctrl+C | Copy the selected clips without pasting |
| Delete | Delete the selected clips |
| Ctrl+E | Edit the clip's text |
| Alt+Enter | Clip properties: description, pin, never delete, group |
| F3 | Show the whole clip |
| Ctrl+G | Show your groups |
| F7 | Put the selected clips in a new group |
| Backspace | Leave the group and go back to all clips |
| Esc | Close the list |
| Click the pin | Pin or unpin a clip |
| Drag a pinned clip | Change the order of pinned clips |
| Right-click | Special pastes and everything else |

## Settings

Open Settings from the tray icon's menu, or use the Settings tab on this mod's page in Windhawk. Both change the same settings.

## Not included from Ditto

Syncing clips between computers over the network, scripts and add-ins.

## Credits

Based on [Ditto](https://github.com/sabrogden/Ditto) by Scott Brogden and the Ditto contributors, GPL-3.0. Windhawk mod by [DavidHiFi](https://github.com/DavidHiFi). If you like it, you can support me on [Ko-fi](https://ko-fi.com/DavidHiFi).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- hotkey: Win+V
  $name: Open the clip list
  $description: Keys that open your clips, like "Win+V", "Ctrl+`" or "Ctrl+Shift+V".
- takeOverWinV: true
  $name: Replace Windows clipboard history
  $description: Turns off Windows clipboard history and its own Win+V, so Win+V opens this list instead. Turning it off puts back only what the mod changed; Windows gets Win+V back after you sign in again.
- hotkey2: ""
  $name: Second key to open the list
  $description: Another key combination that opens the list. Leave empty for none.
- plainTextHotkey: ""
  $name: Key to paste as plain text
  $description: Pastes what's on the clipboard now, without its formatting. Leave empty for none.
- positionHotkeys: "off"
  $name: Number keys
  $description: Hold these keys and press 1 to 9 or 0 to paste clip 1 to 10 without opening the list.
  $options:
  - "off": "Off"
  - ctrlWin: Ctrl + Win + number
  - ctrlAlt: Ctrl + Alt + number
  - altWin: Alt + Win + number
- positionHotkeysPaste: true
  $name: Number keys paste right away
  $description: When off, they only put the clip on the clipboard.
- positionHotkeysMoveToTop: true
  $name: Number keys move the clip to the top
- openAt: caret
  $name: Where the list opens
  $options:
  - caret: At the text cursor
  - cursor: At the mouse pointer
  - remember: Where you left it
- windowWidth: 450
  $name: List width
  $description: "200 to 2000 (Suggested: 450). If you resize the list, it keeps your size for that screen layout."
- windowHeight: 400
  $name: List height
  $description: "150 to 2000 (Suggested: 400)."
- linesPerRow: 5
  $name: Lines per clip
  $description: "1 to 10 (Suggested: 5). How many lines of text each clip shows."
- showPositions: true
  $name: Number the first ten clips
- showThumbnails: true
  $name: Show image previews
- closeOnFocusLoss: true
  $name: Close when you click away
- alwaysOnTop: true
  $name: Keep the list on top
- confirmDelete: true
  $name: Ask before deleting
- fontName: FiraCode Nerd Font
  $name: Font
  $description: "Any installed font (Suggested: FiraCode Nerd Font)."
- fontWeight: medium
  $name: Font weight
  $options:
  - light: Light
  - normal: Regular
  - medium: Medium
  - semibold: Semibold
  - bold: Bold
- fontSize: 10
  $name: Font size
  $description: "7 to 24 points (Suggested: 10)."
- blurMode: acrylic
  $name: Background
  $options:
  - acrylic: Blurred glass
  - mica: Mica (tinted by the wallpaper)
  - none: Solid color
- backgroundOpacity: 55
  $name: Background tint
  $description: "0 to 100 (Suggested: 55). How much the dark tint covers the blur."
- accentColor: "#89B4FA"
  $name: Accent color
  $description: "Color of the selection and the border (Suggested: #89B4FA, Catppuccin blue)."
- accentColor2: "#CBA6F7"
  $name: Second accent color
  $description: "The border fades from the accent color to this one (Suggested: #CBA6F7, Catppuccin mauve)."
- ownBorder: false
  $name: Draw a window border
  $description: Leave off when another mod, like Seamless Borders, already draws borders around windows. Menus always get their border.
- settingsGlass: true
  $name: Blurred settings window
  $description: On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Save, then reopen settings to apply.
- nativeSettingsTitleBar: false
  $name: Native Windows title bar
  $description: Use the Windows title bar and window buttons for this settings window. Save, then reopen settings to apply.
- settingsTitleButtons: native
  $name: Title bar buttons
  $description: Who draws minimize, maximize and close on the window's own title bar. Windows buttons look like every other app's, title bar mods included. Save, then reopen settings to apply.
  $options:
  - native: Windows buttons (like other apps)
  - builtin: Built-in buttons
- animations: true
  $name: Animations
  $description: The list slides and fades in and out, and hover glows fade. Also off when Windows animation effects are off.
- gradientBorder: true
  $name: Gradient border
  $description: When off, the border uses only the accent color.
- cornerRadius: 8
  $name: Corner roundness
  $description: "0 to 24 (Suggested: 8). Rounds the selection and the search bar."
- maxClips: 500
  $name: Clips to keep
  $description: "0 to 100000 (Suggested: 500). Past this count the oldest clips are deleted. Pinned clips, clips in groups and clips set to never delete stay. 0 keeps everything."
- expireDays: 0
  $name: Delete clips older than (days)
  $description: "0 to 3650 (Suggested: 0). 0 keeps clips however old they are."
- saveImages: true
  $name: Save images
- saveFiles: true
  $name: Save copied files
  $description: Saves the list of files you copy in File Explorer, so you can paste them again.
- saveRichText: true
  $name: Save formatting
  $description: Keeps the formatting of text copied from web pages and Word. When off, only the plain text is saved.
- maxClipMB: 64
  $name: Largest copy to save (MB)
  $description: "1 to 512 (Suggested: 64). Bigger copies aren't saved."
- allowDuplicates: false
  $name: Keep repeat copies
  $description: When off, copying the same thing again moves the old clip to the top.
- moveToTopOnPaste: true
  $name: Move a clip to the top when you paste it
- includeApps: "*"
  $name: Save copies from these apps
  $description: App file names separated by ";", with * and ? as wildcards. "*" means every app.
- excludeApps: ""
  $name: Never save copies from these apps
  $description: For example "KeePass.exe;1Password.exe". Copies that password managers mark as private are always skipped.
- pasteKeys: ctrlV
  $name: Paste with
  $options:
  - ctrlV: Ctrl+V
  - shiftInsert: Shift+Insert
- pasteDelay: 50
  $name: Paste delay (ms)
  $description: "0 to 2000 (Suggested: 50). Wait this long after switching back to the app before pasting. Raise it if a paste lands in the wrong place."
- multiSeparator: newline
  $name: Between several pasted clips
  $options:
  - newline: A new line
  - space: A space
  - comma: A comma and a space
  - none: Nothing
- searchMode: contains
  $name: Search finds
  $options:
  - contains: Clips that contain the text
  - allWords: Clips with all the words, in any order
  - startsWith: Clips that start with the text
- searchFullText: true
  $name: Search the whole clip
  $description: When off, search looks only at the start of each clip, which is faster with very large clips.
- trayIcon: true
  $name: Show the tray icon
  $description: Its menu opens these settings. When off, change settings in Windhawk.
- settingsTrayIcon: true
  $name: Tray icon (settings window)
  $description: The same switch as the settings window's "Tray icon" row. The icon shows only when both are on. Click it to open the clip list, right-click it for a menu with Settings.
*/
// ==/WindhawkModSettings==


// ---------------------------------------------------------------------------
// 10-common.h : shared includes, settings, palette, data model and the
// function contract between the parts. Owned by the lead. Parts may add
// static helpers of their own but must not change what is declared here
// without telling the lead.
// ---------------------------------------------------------------------------

#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <commctrl.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <oleacc.h>
#include <imm.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cwchar>
#include <cwctype>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

// ---------------------------------------------------------------------------
// Threading model
// ---------------------------------------------------------------------------
// Everything below runs on ONE thread, the UI thread started by
// WhTool_ModInit (90-main.cpp): the hidden message window, the clipboard
// listener, hotkeys, the tray icon, the clip list window, the editor, the
// properties window and the settings window. The database connection is used
// only from that thread. No locking is needed anywhere unless a part starts
// its own thread (none should).

extern HINSTANCE g_hInstance;      // This DLL (or the harness exe).
extern DWORD g_uiThreadId;
extern HWND g_msgWnd;              // Hidden top-level message window (class kMsgClass).
extern std::atomic<bool> g_stopping;

// Private messages handled by the hidden message window (90-main.cpp).
constexpr UINT WM_SCM_SETTINGS_CHANGED = WM_APP + 1;  // Reload settings, re-apply everything.
constexpr UINT WM_SCM_TRAY = WM_APP + 2;              // Tray icon callback (Tray_OnMessage).
constexpr UINT WM_SCM_SHOW_LIST = WM_APP + 3;         // Open the clip list (wParam: 0).
constexpr UINT WM_SCM_CLIP_SAVED = WM_APP + 4;        // A clip was saved; refresh an open list.
constexpr UINT WM_SCM_OPEN_SETTINGS = WM_APP + 5;     // Open the settings window.
constexpr UINT WM_SCM_QUIT = WM_APP + 6;              // Tear down and leave the loop.

// Timer ids on g_msgWnd. Parts own the ranges noted.
constexpr UINT_PTR kTimerCaptureDebounce = 10;   // 30-capture
constexpr UINT_PTR kTimerHotkeyRetry = 11;       // 30-capture
constexpr UINT_PTR kTimerPasteStep = 12;         // 30-capture
constexpr UINT_PTR kTimerCleanup = 13;           // 90-main (calls Db_Cleanup)
// 40-ui uses timers on its own windows only.

constexpr WCHAR kMsgClass[] = L"SeamlessClipboardManagerMsg";
constexpr WCHAR kListClass[] = L"SeamlessClipboardManagerList";
constexpr WCHAR kSettingsClass[] = L"SeamlessClipboardManagerSettings";
constexpr WCHAR kEditorClass[] = L"SeamlessClipboardManagerEditor";
constexpr WCHAR kPropsClass[] = L"SeamlessClipboardManagerProps";
constexpr WCHAR kPreviewClass[] = L"SeamlessClipboardManagerPreview";

// A clipboard format we add to every clipboard write we make ourselves, so the
// listener knows not to save it again as a new clip.
constexpr WCHAR kOwnClipFormat[] = L"SeamlessClipboardManagerOwnClip";

// ---------------------------------------------------------------------------
// Settings. Keys match the ==WindhawkModSettings== block exactly.
// LoadSettings() (defined in 90-main.cpp) reads and clamps every value.
// ---------------------------------------------------------------------------
struct Settings {
    // Opening and keys
    std::wstring hotkey;            // "hotkey"            default "Win+V"
    std::wstring hotkey2;           // "hotkey2"           default ""
    std::wstring plainTextHotkey;   // "plainTextHotkey"   default ""   Pastes the current clipboard as plain text.
    std::wstring positionHotkeys;   // "positionHotkeys"   "off" | "ctrlWin" | "ctrlAlt" | "altWin" ; default "off"
                                    //   + digit 1..9,0 pastes clip 1..10 of the list.
    bool takeOverWinV;              // "takeOverWinV" default true: turn off Windows clipboard history and its Win+V
    bool positionHotkeysPaste;      // "positionHotkeysPaste"  default true  (false: only put it on the clipboard)
    bool positionHotkeysMoveToTop;  // "positionHotkeysMoveToTop" default true
    // Window
    std::wstring openAt;            // "openAt"  "caret" | "cursor" | "remember" ; default "caret"
    int windowWidth;                // "windowWidth"   200..2000, default 450 (DIPs). A remembered size wins.
    int windowHeight;               // "windowHeight"  150..2000, default 400
    int linesPerRow;                // "linesPerRow"   1..10, default 5
    bool showPositions;             // "showPositions" default true  (row numbers 1..10)
    bool showThumbnails;            // "showThumbnails" default true
    bool closeOnFocusLoss;          // "closeOnFocusLoss" default true
    bool alwaysOnTop;               // "alwaysOnTop"   default true
    bool confirmDelete;             // "confirmDelete" default true
    // Look
    std::wstring fontName;          // "fontName"  default "FiraCode Nerd Font"
    int fontSize;                   // "fontSize"  7..24 (points), default 10
    int fontWeight;                 // "fontWeight" light|normal|medium|semibold|bold -> 300|400|500|600|700, default 500
    std::wstring blurMode;          // "blurMode"  "acrylic" | "mica" | "none" ; default "acrylic"
    int backgroundOpacity;          // "backgroundOpacity" 0..100, default 55 (tint over the blur)
    COLORREF accentColor;           // "accentColor"  default #89B4FA (blue)
    COLORREF accentColor2;          // "accentColor2" default #CBA6F7 (mauve) second stop of the border gradient
    bool gradientBorder;            // "gradientBorder" default true
    bool ownBorder;                 // "ownBorder" default false: list/preview draw their own edge border (Seamless Borders usually does)
    bool nativeSettingsTitleBar = false;
    bool animations;                // "animations" default true; also needs SPI_GETCLIENTAREAANIMATION on
    int cornerRadius;               // "cornerRadius" 0..24, default 8 (rows and pills; the window uses DWM round corners)
    // Clips
    int maxClips;                   // "maxClips"   0..100000, default 500 (0 = no limit)
    int expireDays;                 // "expireDays" 0..3650, default 0 (0 = never)
    bool saveImages;                // "saveImages" default true
    bool saveFiles;                 // "saveFiles"  default true (copied files, CF_HDROP)
    bool saveRichText;              // "saveRichText" default true (HTML Format, Rich Text Format)
    int maxClipMB;                  // "maxClipMB"  1..512, default 64 : skip a copy larger than this
    bool allowDuplicates;           // "allowDuplicates" default false (a repeat copy moves the old clip to the top)
    bool moveToTopOnPaste;          // "moveToTopOnPaste" default true
    std::wstring includeApps;       // "includeApps" default "*"  (';' separated exe names, * and ? wildcards)
    std::wstring excludeApps;       // "excludeApps" default ""
    // Paste
    std::wstring pasteKeys;         // "pasteKeys" "ctrlV" | "shiftInsert" ; default "ctrlV"
    int pasteDelay;                 // "pasteDelay" 0..2000 ms, default 50 : wait after focusing the target
    std::wstring multiSeparator;    // "multiSeparator" "newline" | "space" | "none" | "comma" ; default "newline"
    // Search
    std::wstring searchMode;        // "searchMode" "contains" | "allWords" | "startsWith" ; default "contains"
    bool searchFullText;            // "searchFullText" default true (search the whole text, not just the first line)
    // Other
    bool trayIcon;                  // "trayIcon" default true
};
extern Settings g_set;
void LoadSettings();  // 90-main.cpp
// Corner radius (DIPs) DWM really gives a DWMWCP_ROUND (small = ROUNDSMALL) window: the
// custom-corner-radius mod's value when it is on, else Windows' 8 / 4. Draw edges with it.
float SystemCornerRadius(bool small = false);

// ---------------------------------------------------------------------------
// Palette: Catppuccin Mocha. Use these, never ad hoc colors.
// ---------------------------------------------------------------------------
namespace mocha {
constexpr UINT32 base = 0x1E1E2E, mantle = 0x181825, crust = 0x11111B,
                 surface0 = 0x313244, surface1 = 0x45475A, surface2 = 0x585B70,
                 overlay0 = 0x6C7086, overlay1 = 0x7F849C, overlay2 = 0x9399B2,
                 subtext0 = 0xA6ADC8, subtext1 = 0xBAC2DE, text = 0xCDD6F4,
                 lavender = 0xB4BEFE, blue = 0x89B4FA, sapphire = 0x74C7EC,
                 sky = 0x89DCEB, teal = 0x94E2D5, green = 0xA6E3A1,
                 yellow = 0xF9E2AF, peach = 0xFAB387, maroon = 0xEBA0AC,
                 red = 0xF38BA8, mauve = 0xCBA6F7, pink = 0xF5C2E7,
                 flamingo = 0xF2CDCD, rosewater = 0xF5E0DC;
}  // namespace mocha
inline D2D1_COLOR_F D2DColor(UINT32 rgb, float a = 1.0f) {
    return D2D1::ColorF(((rgb >> 16) & 0xFF) / 255.0f, ((rgb >> 8) & 0xFF) / 255.0f,
                        (rgb & 0xFF) / 255.0f, a);
}
inline D2D1_COLOR_F D2DColorRef(COLORREF c, float a = 1.0f) {
    return D2D1::ColorF(GetRValue(c) / 255.0f, GetGValue(c) / 255.0f, GetBValue(c) / 255.0f, a);
}
inline COLORREF RefFromRgb(UINT32 rgb) { return RGB((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF); }

// ---------------------------------------------------------------------------
// Small shared helpers (defined in 90-main.cpp)
// ---------------------------------------------------------------------------
std::wstring GetStringSetting(PCWSTR key);             // Wh_GetStringSetting wrapper, frees the string.
COLORREF ParseColorRef(const std::wstring& text, COLORREF fallback);  // "#RRGGBB"
std::wstring Utf8ToWide(const std::string& s);
std::string WideToUtf8(const std::wstring& s);
std::wstring StoragePath();                            // Mod storage folder, created if missing, no trailing slash.
bool WildcardMatchList(const std::wstring& name, const std::wstring& list);  // ';' separated, * ?, case-insensitive
std::wstring ProcessNameOfWindow(HWND hwnd);           // "chrome.exe" or "" (lowercase not guaranteed)
int64_t UnixNow();
// Per-user UI state in the mod's local storage (Wh_GetIntValue / Wh_SetIntValue).
int GetState(PCWSTR name, int fallback);
void SetState(PCWSTR name, int value);
// Dark title bar + dark scrollbars/menus for one of our windows (DWMWA_USE_IMMERSIVE_DARK_MODE,
// SetWindowTheme "DarkMode_Explorer"). Popup menus are dark process-wide (set once at startup).
void ApplyDarkWindow(HWND hwnd);
// Window position/size memory, Ditto's scheme: keys are per virtual-screen size, values in physical px.
// e.g. StateKey(L"List", L"CX") -> L"List_6400x2520_CX". Ditto's own saved sizes are imported into these.
std::wstring StateKey(PCWSTR window, PCWSTR field);

// ---------------------------------------------------------------------------
// Data model. The database keeps Ditto's schema exactly, so Ditto's own
// database imports by copy and stays readable by Ditto.
//   Main(lID, lDate, mText, lShortCut, lDontAutoDelete, CRC, bIsGroup,
//        lParentID, QuickPasteText, clipOrder, clipGroupOrder, globalShortCut,
//        lastPasteDate, stickyClipOrder, stickyClipGroupOrder,
//        MoveToGroupShortCut, GlobalMoveToGroupShortCut)
//   Data(lID, lParentID, strClipBoardFormat, ooData)
//   Types, CopyBuffers, MainDeletes (+ Ditto's triggers and indexes)
// ---------------------------------------------------------------------------
constexpr double kNotSticky = -2147483647.0;   // Ditto's "not sticky" order value.

enum class ClipKind { Text, Image, Files, Group, Other };

struct ClipRow {
    int64_t id = 0;
    int64_t date = 0;              // lDate, unix seconds
    int64_t lastPasteDate = 0;
    std::wstring text;             // mText: the description Ditto shows (text clips: the text itself)
    std::wstring quickPasteText;   // QuickPasteText
    int64_t parentId = -1;         // lParentID, -1 = not in a group
    bool isGroup = false;
    bool neverDelete = false;      // lDontAutoDelete != 0
    bool sticky = false;           // stickyClipOrder (or stickyClipGroupOrder in a group) != kNotSticky
    bool hasShortcut = false;      // lShortCut != 0 || globalShortCut != 0
    ClipKind kind = ClipKind::Text;  // From the formats present (Image if CF_DIB/PNG and no text, Files if CF_HDROP, Group).
};

struct ClipFormat {
    UINT cf = 0;                   // Registered/standard id in this session (0 if unknown here)
    std::wstring name;             // Ditto name: "CF_UNICODETEXT", "CF_TEXT", "CF_DIB", "PNG", "HTML Format", "Rich Text Format", "CF_HDROP", ...
    std::string data;              // Raw bytes exactly as on the clipboard (GlobalSize-trimmed for text where Ditto trims)
};

struct ClipData {
    std::vector<ClipFormat> formats;
    std::wstring description;      // mText to store
    std::wstring sourceApp;        // exe of the copying window (not stored by Ditto's schema; informational)
};

// Format-name helpers (defined in 30-capture.cpp)
std::wstring FormatNameFromId(UINT cf);    // CF_UNICODETEXT -> L"CF_UNICODETEXT", registered -> its registered name
UINT FormatIdFromName(const std::wstring& name);  // reverse, registering unknown names

// ---------------------------------------------------------------------------
// 20-db.cpp : database. UI thread only.
// ---------------------------------------------------------------------------
struct ClipQuery {
    int64_t groupId = -1;          // -1 = the main list (Ditto's main list rules); else clips inside this group
    std::wstring search;           // empty = no filter; matching follows g_set.searchMode / searchFullText
};

bool Db_Open();                    // Opens <StoragePath()>\clips.db; on first run imports Ditto's database (see spec).
void Db_Close();
bool Db_IsOpen();
std::wstring Db_LastError();
int Db_CountClips(const ClipQuery& q);
std::vector<ClipRow> Db_QueryClips(const ClipQuery& q, int offset, int limit);  // Ditto's display order.
bool Db_GetClipRow(int64_t id, ClipRow& out);
bool Db_GetClipData(int64_t id, ClipData& out);           // All stored formats.
bool Db_GetFormat(int64_t id, const std::wstring& formatName, std::string& out);
std::wstring Db_GetClipText(int64_t id);                  // CF_UNICODETEXT, else CF_TEXT (ANSI->wide), else file list, else mText.
int64_t Db_SaveClip(const ClipData& clip);                // New id, or existing id when a duplicate moved to the top. 0 on failure.
bool Db_MoveToTop(int64_t id);                            // On paste: new clipOrder (and clipGroupOrder in a group), lastPasteDate = now.
bool Db_DeleteClips(const std::vector<int64_t>& ids);     // Groups: their clips go back to the main list (Ditto behavior).
bool Db_SetDescription(int64_t id, const std::wstring& text);
bool Db_SetQuickPasteText(int64_t id, const std::wstring& text);
bool Db_SetNeverDelete(int64_t id, bool on);
bool Db_SetSticky(int64_t id, bool on, bool inGroup);     // inGroup: use stickyClipGroupOrder
bool Db_SetStickyOrder(const std::vector<int64_t>& idsTopFirst, bool inGroup);  // rewrite sticky order, first = top
bool Db_UpdateClipText(int64_t id, const std::wstring& text);  // Clip editor save: rewrites text formats, drops stale rich formats, updates mText + CRC.
int64_t Db_CreateGroup(const std::wstring& name, int64_t parentId);
bool Db_MoveToGroup(const std::vector<int64_t>& ids, int64_t groupId);  // -1 = out of any group
std::vector<ClipRow> Db_ListGroups();                     // All groups, any depth, sorted by name.
int64_t Db_ClipIdAtPosition(int index);                   // 0-based position in the main list with no search; 0 if none.
int Db_TotalClips();
void Db_Cleanup();                                        // Max clips + expiry + drain MainDeletes in small batches.
bool Db_DeleteAllUnpinned();                              // Tray "Delete all clips": keeps groups, never-delete and sticky clips.

// ---------------------------------------------------------------------------
// 30-capture.cpp : clipboard capture, paste, hotkeys, tray, special paste.
// ---------------------------------------------------------------------------
void Capture_Start();              // AddClipboardFormatListener(g_msgWnd)
void Capture_Stop();
void Capture_OnClipboardUpdate();  // WM_CLIPBOARDUPDATE (debounces with kTimerCaptureDebounce)
void Capture_OnTimer(UINT_PTR id); // kTimerCaptureDebounce / kTimerPasteStep / kTimerHotkeyRetry
extern bool g_capturePaused;       // Tray "Pause saving copies"

enum class SpecialPaste {
    None, PlainText, Upper, Lower, Capitalize, Sentence, InvertCase, CamelCase,
    Slugify, TrimWhitespace, RemoveLineBreaks, AddLineBreak, AddTwoLineBreaks,
    Typoglycemia, AsciiOnly
};
std::wstring ApplySpecialPaste(const std::wstring& text, SpecialPaste mode);

struct PasteRequest {
    std::vector<int64_t> ids;      // In the order chosen; several are joined with g_set.multiSeparator.
    SpecialPaste mode = SpecialPaste::None;  // None = every stored format; anything else = text only.
    bool sendPaste = true;         // false: only put it on the clipboard
    bool moveToTop = true;         // Usually g_set.moveToTopOnPaste
    HWND target = nullptr;         // Window to paste into (the one active before the list opened)
};
bool Paste_Request(const PasteRequest& req);   // Puts it on the clipboard, focuses target, sends the paste keys.
bool Clipboard_PutClip(int64_t id, SpecialPaste mode);  // Copy to clipboard only (Ctrl+C in the list).
HWND Focus_RememberTarget();       // Foreground window now (not ours); stored for the next paste.
extern HWND g_pasteTarget;
bool Focus_GetCaretRect(HWND target, RECT& screenRect);  // GetGUIThreadInfo, then MSAA caret; false if none.

bool Hotkey_Parse(const std::wstring& text, UINT& mods, UINT& vk);   // "Win+V", "Ctrl+Shift+F12", "Ctrl+`"
std::wstring Hotkey_Format(UINT mods, UINT vk);
void Hotkeys_Register();           // On g_msgWnd; retries every 5 s (kTimerHotkeyRetry) while any fails.
void Hotkeys_Unregister();
void Hotkeys_OnHotkey(int id);     // WM_HOTKEY
std::wstring Hotkeys_Status();     // e.g. "Win+V is used by another app" or "" when all registered.

void Tray_Create();
void Tray_Remove();
void Tray_Update();                // Tooltip/icon after pause toggles or settings.
void Tray_OnMessage(WPARAM wParam, LPARAM lParam);
void Tray_OnTaskbarCreated();      // Re-add after Explorer restarts.

// ---------------------------------------------------------------------------
// 40-ui.cpp : clip list window, preview, editor, properties, groups.
// ---------------------------------------------------------------------------
void List_Show();                  // Remembers the paste target, positions per g_set.openAt, shows and focuses.
void List_Hide();
bool List_IsVisible();
void List_Toggle();
void List_OnClipSaved(int64_t id); // Refresh an open list, keep selection on the same clip where possible.
void List_ApplySettings();         // Fonts, colors, backdrop, row height.
void List_Destroy();
void Editor_Open(int64_t id);      // Edit a clip's text.
void Props_Open(int64_t id);       // Description, quick paste text, never delete, sticky, group.
HICON MakeAppIcon(int size);       // The mod's icon (clipboard glyph, blue to mauve). Used by tray and windows.
// Harness only: render the list with the current DB into a PNG without showing a window.
bool List_RenderToPng(const std::wstring& path, int widthDip, int heightDip, float dpiScale);

// The mod's own popup menu (replaces every Win32 menu). Blocks until an item is chosen or the menu
// closes; returns the chosen item's id, or 0. A parent item has no id and opens `sub`.
struct UiMenuItem {
    int id = 0;
    std::wstring text;
    std::wstring hint;       // Right-aligned shortcut text.
    wchar_t glyph = 0;       // Segoe Fluent Icons code point, 0 for none.
    bool separator = false;
    bool disabled = false;
    bool checked = false;
    std::vector<UiMenuItem> sub;
};
int Ui_ShowMenu(const std::vector<UiMenuItem>& items, POINT screenPt, HWND owner);

// ---------------------------------------------------------------------------
// 50-settings.cpp : the mod's own settings window.
// ---------------------------------------------------------------------------
void Settings_Open();              // Opens or focuses it.
void Settings_Close();
bool Settings_IsOpen();
// Harness only: render the settings window to a PNG (PrintWindow of an off-screen window).
bool Settings_RenderToPng(const std::wstring& path);

// ---------------------------------------------------------------------------
// Harness self tests (only built into harness.exe). Each part defines its own;
// return 0 on pass, print what failed with Wh_Log otherwise.
// ---------------------------------------------------------------------------
#ifdef SCM_HARNESS
int Harness_TestDb();        // 20-db.cpp
int Harness_TestCapture();   // 30-capture.cpp
int Harness_TestUi();        // 40-ui.cpp
int Harness_TestSettings();  // 50-settings.cpp
#endif

// ---------------------------------------------------------------------------
// 20-db.cpp : the clip database. Ditto's schema and rules on winsqlite3.dll,
// one connection, UI thread only.
// ---------------------------------------------------------------------------

namespace dbx {

struct sqlite3;
struct sqlite3_stmt;
struct sqlite3_context;
struct sqlite3_value;
using Destructor = void (*)(void*);
using ScalarFn = void (*)(sqlite3_context*, int, sqlite3_value**);

constexpr int kOk = 0, kRow = 100, kDone = 101;
constexpr int kOpenReadOnly = 0x1, kOpenReadWrite = 0x2, kOpenCreate = 0x4, kOpenUri = 0x40, kOpenNoMutex = 0x8000;
constexpr int kBlob = 4, kNull = 5;
constexpr int kUtf16Le = 2;
static const Destructor kTransient = reinterpret_cast<Destructor>(static_cast<intptr_t>(-1));

static struct Api {
    int (*open_v2)(const char*, sqlite3**, int, const char*);
    int (*close_v2)(sqlite3*);
    int (*prepare_v2)(sqlite3*, const char*, int, sqlite3_stmt**, const char**);
    int (*step)(sqlite3_stmt*);
    int (*reset)(sqlite3_stmt*);
    int (*clear_bindings)(sqlite3_stmt*);
    int (*finalize)(sqlite3_stmt*);
    int (*bind_int64)(sqlite3_stmt*, int, int64_t);
    int (*bind_double)(sqlite3_stmt*, int, double);
    int (*bind_text16)(sqlite3_stmt*, int, const void*, int, Destructor);
    int (*bind_blob64)(sqlite3_stmt*, int, const void*, uint64_t, Destructor);
    int64_t (*column_int64)(sqlite3_stmt*, int);
    double (*column_double)(sqlite3_stmt*, int);
    const void* (*column_text16)(sqlite3_stmt*, int);
    int (*column_bytes16)(sqlite3_stmt*, int);
    const void* (*column_blob)(sqlite3_stmt*, int);
    int (*column_bytes)(sqlite3_stmt*, int);
    int (*column_type)(sqlite3_stmt*, int);
    const char* (*errmsg)(sqlite3*);
    int (*changes)(sqlite3*);
    int64_t (*last_insert_rowid)(sqlite3*);
    int (*busy_timeout)(sqlite3*, int);
    int (*create_function_v2)(sqlite3*, const char*, int, int, void*, ScalarFn, ScalarFn, void (*)(sqlite3_context*), Destructor);
    int (*value_type)(sqlite3_value*);
    const void* (*value_blob)(sqlite3_value*);
    int (*value_bytes)(sqlite3_value*);
    const void* (*value_text16)(sqlite3_value*);
    int (*value_bytes16)(sqlite3_value*);
    int (*value_int)(sqlite3_value*);
    void (*result_int)(sqlite3_context*, int);
} api;

static HMODULE g_lib;
static sqlite3* g_db;
static std::wstring g_err;
static std::unordered_map<std::string, sqlite3_stmt*> g_cache;
static uint64_t g_gen = 1;  // bumped on every write; keys the search cache

static bool LoadApi() {
    if (g_lib) return true;
    HMODULE lib = LoadLibraryExW(L"winsqlite3.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!lib) { g_err = L"Could not load winsqlite3.dll."; return false; }
    struct { void** slot; const char* name; } fns[] = {
#define DBX_FN(n) {reinterpret_cast<void**>(&api.n), "sqlite3_" #n}
        DBX_FN(open_v2), DBX_FN(close_v2), DBX_FN(prepare_v2), DBX_FN(step), DBX_FN(reset),
        DBX_FN(clear_bindings), DBX_FN(finalize), DBX_FN(bind_int64), DBX_FN(bind_double),
        DBX_FN(bind_text16), DBX_FN(bind_blob64), DBX_FN(column_int64), DBX_FN(column_double),
        DBX_FN(column_text16), DBX_FN(column_bytes16), DBX_FN(column_blob), DBX_FN(column_bytes),
        DBX_FN(column_type), DBX_FN(errmsg), DBX_FN(changes), DBX_FN(last_insert_rowid),
        DBX_FN(busy_timeout), DBX_FN(create_function_v2), DBX_FN(value_type), DBX_FN(value_blob),
        DBX_FN(value_bytes), DBX_FN(value_text16), DBX_FN(value_bytes16), DBX_FN(value_int),
        DBX_FN(result_int),
#undef DBX_FN
    };
    for (auto& f : fns) {
        *f.slot = reinterpret_cast<void*>(GetProcAddress(lib, f.name));
        if (!*f.slot) { g_err = L"winsqlite3.dll is missing a function."; FreeLibrary(lib); return false; }
    }
    g_lib = lib;
    return true;
}

static void SetErr(sqlite3* db, const char* what) {
    g_err = Utf8ToWide(what);
    if (db) g_err += L": " + Utf8ToWide(api.errmsg(db));
    Wh_Log(L"db: %s", g_err.c_str());
}

// Prepared statement. Cached ones (main connection) are reset on scope exit;
// never hold two Stmt objects with the same SQL at the same time.
class Stmt {
public:
    explicit Stmt(const char* sql, sqlite3* db = g_db, bool cache = true) : db_(db), cached_(cache && db == g_db) {
        if (cached_) {
            auto it = g_cache.find(sql);
            if (it != g_cache.end()) { s_ = it->second; return; }
        }
        if (!db || api.prepare_v2(db, sql, -1, &s_, nullptr) != kOk) {
            SetErr(db, "Could not prepare a query");
            if (s_) api.finalize(s_);
            s_ = nullptr;
            return;
        }
        if (cached_) g_cache[sql] = s_;
    }
    explicit Stmt(const std::string& sql) : Stmt(sql.c_str()) {}
    ~Stmt() {
        if (!s_) return;
        if (cached_) { api.reset(s_); api.clear_bindings(s_); }
        else api.finalize(s_);
    }
    Stmt(const Stmt&) = delete;
    Stmt& operator=(const Stmt&) = delete;
    explicit operator bool() const { return s_ != nullptr; }
    Stmt& Int(int i, int64_t v) { if (s_) api.bind_int64(s_, i, v); return *this; }
    Stmt& Dbl(int i, double v) { if (s_) api.bind_double(s_, i, v); return *this; }
    Stmt& Str(int i, const std::wstring& v) {
        if (s_) api.bind_text16(s_, i, v.c_str(), (int)(v.size() * sizeof(wchar_t)), kTransient);
        return *this;
    }
    Stmt& Blob(int i, const std::string& v) { if (s_) api.bind_blob64(s_, i, v.data(), v.size(), kTransient); return *this; }
    bool Row() {
        if (!s_) return false;
        int rc = api.step(s_);
        if (rc == kRow) return true;
        if (rc != kDone) SetErr(db_, "A query failed");
        return false;
    }
    bool Run() {
        if (!s_) return false;
        int rc = api.step(s_);
        if (rc == kDone || rc == kRow) return true;
        SetErr(db_, "A database write failed");
        return false;
    }
    int64_t I64(int c) const { return api.column_int64(s_, c); }
    double D(int c) const { return api.column_double(s_, c); }
    bool IsNull(int c) const { return api.column_type(s_, c) == kNull; }
    std::wstring W(int c) const {
        auto p = static_cast<const wchar_t*>(api.column_text16(s_, c));
        return p ? std::wstring(p, api.column_bytes16(s_, c) / sizeof(wchar_t)) : std::wstring();
    }
    std::string B(int c) const {
        auto p = static_cast<const char*>(api.column_blob(s_, c));
        return p ? std::string(p, api.column_bytes(s_, c)) : std::string();
    }

private:
    sqlite3* db_;
    sqlite3_stmt* s_ = nullptr;
    bool cached_;
};

// Runs every statement in sql (not cached).
static bool Exec(sqlite3* db, const char* sql) {
    while (sql && *sql) {
        sqlite3_stmt* s = nullptr;
        const char* tail = nullptr;
        if (api.prepare_v2(db, sql, -1, &s, &tail) != kOk) { SetErr(db, "Could not run a query"); return false; }
        if (s) {
            int rc;
            while ((rc = api.step(s)) == kRow) {}
            api.finalize(s);
            if (rc != kDone) { SetErr(db, "A query failed"); return false; }
        }
        sql = tail;
    }
    return true;
}

static int64_t QueryInt(sqlite3* db, const char* sql, int64_t fallback = 0) {
    Stmt s(sql, db, db == g_db);
    return s.Row() && !s.IsNull(0) ? s.I64(0) : fallback;
}

static sqlite3* OpenFile(const std::string& utf8, int flags) {
    sqlite3* db = nullptr;
    if (api.open_v2(utf8.c_str(), &db, flags | kOpenNoMutex, nullptr) != kOk) {
        SetErr(db, "Could not open the database");
        if (db) api.close_v2(db);
        return nullptr;
    }
    api.busy_timeout(db, 2000);
    return db;
}

// One transaction; rolls back unless Commit() succeeded.
class Txn {
public:
    Txn() : ok_(Exec(g_db, "BEGIN IMMEDIATE")) {}
    ~Txn() { if (ok_ && !done_) Exec(g_db, "ROLLBACK"); }
    explicit operator bool() const { return ok_; }
    bool Commit() {
        if (!ok_ || done_) return false;
        done_ = Exec(g_db, "COMMIT");
        if (done_) g_gen++;
        return done_;
    }

private:
    bool ok_, done_ = false;
};

// ---------------------------------------------------------------------------
// Schema (Ditto DatabaseUtilities.cpp CreateDB / ValidDB)
// ---------------------------------------------------------------------------
static const char kCreateDb[] =
    "PRAGMA auto_vacuum = 1;"
    "CREATE TABLE Main(lID INTEGER PRIMARY KEY AUTOINCREMENT, lDate INTEGER, mText TEXT, lShortCut INTEGER, "
    "lDontAutoDelete INTEGER, CRC INTEGER, bIsGroup INTEGER, lParentID INTEGER, QuickPasteText TEXT, "
    "clipOrder REAL, clipGroupOrder REAL, globalShortCut INTEGER, lastPasteDate INTEGER, stickyClipOrder REAL, "
    "stickyClipGroupOrder REAL, MoveToGroupShortCut INTEGER, GlobalMoveToGroupShortCut INTEGER);"
    "CREATE TABLE Data(lID INTEGER PRIMARY KEY AUTOINCREMENT, lParentID INTEGER, strClipBoardFormat TEXT, ooData BLOB);"
    "CREATE TABLE Types(lID INTEGER PRIMARY KEY AUTOINCREMENT, TypeText TEXT);"
    "CREATE UNIQUE INDEX Main_ID on Main(lID ASC);"
    "CREATE UNIQUE INDEX Data_ID on Data(lID ASC);"
    "CREATE INDEX Main_ClipOrder on Main(clipOrder DESC);"
    "CREATE INDEX Main_ClipGroupOrder on Main(clipGroupOrder DESC);"
    "CREATE INDEX Main_ParentId on Main(lParentID DESC);"
    "CREATE INDEX Main_IsGroup on Main(bIsGroup DESC);"
    "CREATE TABLE CopyBuffers(lID INTEGER PRIMARY KEY AUTOINCREMENT, lClipID INTEGER, lCopyBuffer INTEGER);"
    "CREATE TABLE MainDeletes(clipID INTEGER,modifiedDate);";

static const char kTriggersAndIndexes[] =
    "CREATE TRIGGER IF NOT EXISTS MainDeletes_delete_data_trigger BEFORE DELETE ON MainDeletes FOR EACH ROW "
    "BEGIN DELETE FROM CopyBuffers WHERE lClipID = old.clipID; DELETE FROM Data WHERE lParentID = old.clipID; END;"
    "DROP TRIGGER IF EXISTS delete_data_trigger;"
    "DROP TRIGGER IF EXISTS delete_copy_buffer_trigger;"
    "CREATE TRIGGER delete_data_trigger BEFORE DELETE ON Main FOR EACH ROW "
    "BEGIN INSERT INTO MainDeletes VALUES(old.lID, datetime('now')); END;"
    "CREATE INDEX IF NOT EXISTS Data_ParentId_Format on Data(lParentID COLLATE BINARY ASC, strClipBoardFormat COLLATE NOCASE ASC);"
    "CREATE INDEX IF NOT EXISTS Main_ParentId on Main(lParentID DESC);"
    "CREATE INDEX IF NOT EXISTS Main_IsGroup on Main(bIsGroup DESC);"
    "CREATE INDEX IF NOT EXISTS Main_ClipOrder on Main(clipOrder DESC);"
    "CREATE INDEX IF NOT EXISTS Main_ClipGroupOrder on Main(clipGroupOrder DESC);"
    "DROP INDEX IF EXISTS Main_NoGroup;"
    "DROP INDEX IF EXISTS Main_InGroup;"
    "DROP INDEX IF EXISTS Main_ShortCut;"
    "CREATE INDEX IF NOT EXISTS Main_TopLevelParentID on Main(lParentId ASC, stickyClipOrder DESC, bIsGroup ASC, clipOrder DESC);"
    "CREATE INDEX IF NOT EXISTS Main_TopLevel on Main(stickyClipOrder DESC, bIsGroup ASC, clipOrder DESC);"
    "CREATE INDEX IF NOT EXISTS Main_InGroup2 on Main(lParentId ASC, stickyClipGroupOrder DESC, bIsGroup ASC, clipGroupOrder DESC);"
    "CREATE INDEX IF NOT EXISTS Main_ShortCut2 on Main(lShortCut DESC, globalShortCut DESC);"
    "CREATE INDEX IF NOT EXISTS Main_MoveToGroup on Main(MoveToGroupShortCut DESC, GlobalMoveToGroupShortCut DESC);"
    "CREATE INDEX IF NOT EXISTS Main_CRC on Main(CRC ASC);";

static bool HasColumn(sqlite3* db, const wchar_t* table, const wchar_t* col) {
    Stmt s("SELECT 1 FROM pragma_table_info(?) WHERE name = ? COLLATE NOCASE", db, false);
    s.Str(1, table).Str(2, col);
    return s.Row();
}

// Creates a fresh schema or brings an older Ditto database up to date.
static bool EnsureSchema(sqlite3* db) {
    if (!QueryInt(db, "SELECT COUNT(*) FROM sqlite_master WHERE type = 'table' AND name = 'Main'")) {
        if (!Exec(db, kCreateDb)) return false;
    }
    if (!Exec(db, "CREATE TABLE IF NOT EXISTS Types(lID INTEGER PRIMARY KEY AUTOINCREMENT, TypeText TEXT);"
                  "CREATE TABLE IF NOT EXISTS CopyBuffers(lID INTEGER PRIMARY KEY AUTOINCREMENT, lClipID INTEGER, lCopyBuffer INTEGER);"
                  "CREATE TABLE IF NOT EXISTS MainDeletes(clipID INTEGER,modifiedDate);"))
        return false;
    if (!HasColumn(db, L"Main", L"clipOrder")) {
        if (!Exec(db, "ALTER TABLE Main ADD clipOrder REAL; ALTER TABLE Main ADD clipGroupOrder REAL;"
                      "UPDATE Main SET clipOrder = lDate, clipGroupOrder = lDate; DROP INDEX IF EXISTS Main_Date;"))
            return false;
    }
    if (!HasColumn(db, L"Main", L"globalShortCut") && !Exec(db, "ALTER TABLE Main ADD globalShortCut INTEGER;")) return false;
    if (!HasColumn(db, L"Main", L"lastPasteDate")) {
        if (!Exec(db, "ALTER TABLE Main ADD lastPasteDate INTEGER; UPDATE Main SET lastPasteDate = lDate;"
                      "UPDATE Main SET lastPasteDate = strftime('%s','now') WHERE lastPasteDate <= 0;"))
            return false;
    }
    if (!HasColumn(db, L"Main", L"stickyClipOrder") &&
        !Exec(db, "ALTER TABLE Main ADD stickyClipOrder REAL; ALTER TABLE Main ADD stickyClipGroupOrder REAL;"))
        return false;
    if (!HasColumn(db, L"Main", L"MoveToGroupShortCut") &&
        !Exec(db, "ALTER TABLE Main ADD MoveToGroupShortCut INTEGER; ALTER TABLE Main ADD GlobalMoveToGroupShortCut INTEGER;"))
        return false;
    // ValidDB runs this whenever Main_NoGroup is absent, which is every open.
    if (!Exec(db, "UPDATE Main SET stickyClipOrder = -(2147483647) WHERE stickyClipOrder IS NULL OR stickyClipOrder = 0;"
                  "UPDATE Main SET stickyClipGroupOrder = -(2147483647) WHERE stickyClipGroupOrder IS NULL OR stickyClipGroupOrder = 0;"))
        return false;
    return Exec(db, kTriggersAndIndexes);
}

static void DeleteDbFiles(const std::wstring& path) {
    for (const wchar_t* sfx : {L"", L"-wal", L"-shm", L"-journal"}) DeleteFileW((path + sfx).c_str());
}

static bool FileExists(const std::wstring& path) {
    DWORD a = GetFileAttributesW(path.c_str());
    return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY);
}

// file:///C:/a%20b/Ditto.db?mode=ro
static std::string ReadOnlyUri(const std::wstring& path) {
    std::string utf8 = WideToUtf8(path), out = "file:///";
    for (unsigned char c : utf8) {
        if (c == '\\') out += '/';
        else if (isalnum(c) || strchr("-._~/:", c)) out += (char)c;
        else { char hex[4]; snprintf(hex, sizeof hex, "%%%02X", c); out += hex; }
    }
    return out + "?mode=ro";
}

static std::string SqlQuote(const std::string& s) {
    std::string out = "'";
    for (char c : s) { out += c; if (c == '\'') out += '\''; }
    return out + "'";
}

static std::wstring DittoDbPath() {
#ifdef SCM_HARNESS
    if (wchar_t env[MAX_PATH * 2]; GetEnvironmentVariableW(L"SCM_DITTO_DB", env, ARRAYSIZE(env))) return env;
#endif
    wchar_t raw[MAX_PATH * 2], path[MAX_PATH * 2];
    DWORD size = sizeof raw;
    if (RegGetValueW(HKEY_CURRENT_USER, L"Software\\Ditto", L"DBPath3", RRF_RT_REG_SZ | RRF_RT_REG_EXPAND_SZ | RRF_NOEXPAND,
                     nullptr, raw, &size) == ERROR_SUCCESS &&
        ExpandEnvironmentStringsW(raw, path, ARRAYSIZE(path)) && FileExists(path))
        return path;
    if (ExpandEnvironmentStringsW(L"%APPDATA%\\Ditto\\Ditto.db", path, ARRAYSIZE(path)) && FileExists(path)) return path;
    return {};
}

static int g_drained;  // MainDeletes rows removed by the last Drain()

// Removes deleted clips' data a few rows at a time, within budgetMs.
static bool Drain(sqlite3* db, DWORD budgetMs, int batch = 1) {
    ULONGLONG start = GetTickCount64();
    g_drained = 0;
    std::string sql = "DELETE FROM MainDeletes WHERE rowid IN (SELECT rowid FROM MainDeletes LIMIT " + std::to_string(batch) + ")";
    while (true) {
        Stmt s(sql.c_str(), db, db == g_db);
        if (!s.Run()) return false;
        int n = api.changes(db);
        g_drained += n;
        if (n < batch || GetTickCount64() - start >= budgetMs) return true;
    }
}

// Copies Ditto's database next to ours without ever writing to it.
static bool ImportDitto(const std::wstring& src, const std::wstring& dest) {
    std::wstring tmp = StoragePath() + L"\\clips.import.tmp";
    DeleteDbFiles(tmp);
    ULONGLONG t0 = GetTickCount64();
    int64_t srcCount = -1;
    bool ok = false;
    if (sqlite3* s = OpenFile(ReadOnlyUri(src), kOpenReadOnly | kOpenUri)) {
        api.busy_timeout(s, 10000);
        srcCount = QueryInt(s, "SELECT COUNT(*) FROM Main", -1);
        ok = srcCount >= 0 && Exec(s, ("VACUUM INTO " + SqlQuote(WideToUtf8(tmp))).c_str());
        api.close_v2(s);
    }
    ULONGLONG tCopy = GetTickCount64();
    int drained = 0, orphans = 0;
    int64_t count = 0;
    if (ok) {
        ok = false;
        if (sqlite3* t = OpenFile(WideToUtf8(tmp), kOpenReadWrite)) {
            ok = Exec(t, "BEGIN") && Drain(t, INFINITE, 1000) && ((drained = g_drained), true) &&
                 Exec(t, "DELETE FROM Data WHERE lParentID NOT IN (SELECT lID FROM Main);") &&
                 ((orphans = api.changes(t)), true) &&
                 Exec(t, "DELETE FROM CopyBuffers WHERE lClipID NOT IN (SELECT lID FROM Main);") &&
                 EnsureSchema(t) && Exec(t, "COMMIT");
            // auto_vacuum=1 already returned the freed pages; only vacuum if some remain.
            if (ok && QueryInt(t, "PRAGMA freelist_count") > 0) ok = Exec(t, "VACUUM");
            count = QueryInt(t, "SELECT COUNT(*) FROM Main");
            ok = ok && Exec(t, "PRAGMA journal_mode = WAL");
            api.close_v2(t);
        }
    }
    if (ok && !MoveFileExW(tmp.c_str(), dest.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
        g_err = L"Could not move the imported database into place.";
        ok = false;
    }
    DeleteDbFiles(tmp);
    if (ok)
        Wh_Log(L"db: imported %lld of %lld Ditto clips from %s (dropped %d deleted, %d orphan data rows) in %llu ms (copy %llu ms)",
               (long long)count, (long long)srcCount, src.c_str(), drained, orphans, GetTickCount64() - t0, tCopy - t0);
    else
        Wh_Log(L"db: Ditto import failed (%s), starting empty", g_err.c_str());
    return ok;
}

// ---------------------------------------------------------------------------
// Search: scm_match(value, maxChars) with the current pattern.
// ---------------------------------------------------------------------------
static struct {
    std::wstring mode;
    std::wstring whole;               // lowercased, trimmed
    std::vector<std::wstring> words;  // lowercased
} g_pat;
static std::wstring g_lower;  // scratch

static void MatchFn(sqlite3_context* ctx, int, sqlite3_value** argv) {
    const wchar_t* p = nullptr;
    size_t n = 0;
    if (api.value_type(argv[0]) == kBlob) {
        p = static_cast<const wchar_t*>(api.value_blob(argv[0]));
        n = api.value_bytes(argv[0]) / sizeof(wchar_t);
        if (p) n = wcsnlen(p, n);
    } else if (api.value_type(argv[0]) != kNull) {
        p = static_cast<const wchar_t*>(api.value_text16(argv[0]));
        n = api.value_bytes16(argv[0]) / sizeof(wchar_t);
    }
    int limit = api.value_int(argv[1]);
    if (limit > 0 && n > (size_t)limit) n = limit;
    if (!p || !n) { api.result_int(ctx, 0); return; }
    g_lower.assign(p, n);
    CharLowerBuffW(g_lower.data(), (DWORD)n);
    std::wstring_view t = g_lower;
    bool hit;
    if (g_pat.mode == L"startsWith") {
        size_t first = t.find_first_not_of(L" \t\r\n");
        hit = first != std::wstring_view::npos && t.substr(first).starts_with(g_pat.whole);
    } else if (g_pat.mode == L"allWords") {
        hit = std::all_of(g_pat.words.begin(), g_pat.words.end(), [&](const std::wstring& w) { return t.find(w) != t.npos; });
    } else {
        hit = t.find(g_pat.whole) != t.npos;
    }
    api.result_int(ctx, hit);
}

static void SetPattern(const std::wstring& search) {
    std::wstring s = search;
    CharLowerBuffW(s.data(), (DWORD)s.size());
    size_t a = s.find_first_not_of(L" \t\r\n"), b = s.find_last_not_of(L" \t\r\n");
    g_pat.whole = a == s.npos ? L"" : s.substr(a, b - a + 1);
    g_pat.mode = g_set.searchMode;
    g_pat.words.clear();
    for (size_t i = 0; i < g_pat.whole.size();) {
        size_t j = g_pat.whole.find_first_of(L" \t\r\n", i);
        if (j == s.npos) j = g_pat.whole.size();
        if (j > i) g_pat.words.push_back(g_pat.whole.substr(i, j - i));
        i = j + 1;
    }
}

static struct {
    uint64_t gen = 0;
    int64_t group = 0;
    std::wstring search, mode;
    bool fullText = false;
    std::vector<int64_t> ids;
} g_hits;

// Ditto's search replaces the main-list filter; in a group it is ANDed with the group (QPasteWnd.cpp FillList).
static const std::vector<int64_t>& SearchIds(const ClipQuery& q) {
    if (g_hits.gen == g_gen && g_hits.group == q.groupId && g_hits.search == q.search && g_hits.mode == g_set.searchMode &&
        g_hits.fullText == g_set.searchFullText)
        return g_hits.ids;
    SetPattern(q.search);
    g_hits.ids.clear();
    g_hits.gen = g_gen;
    g_hits.group = q.groupId;
    g_hits.search = q.search;
    g_hits.mode = g_set.searchMode;
    g_hits.fullText = g_set.searchFullText;
    if (g_pat.whole.empty()) return g_hits.ids;
    std::string sql = "SELECT Main.lID FROM Main WHERE (scm_match(Main.mText, ";
    sql += g_set.searchFullText ? "0" : "500";
    sql += ") OR scm_match(Main.QuickPasteText, 0)";
    if (g_set.searchFullText)
        sql += " OR EXISTS(SELECT 1 FROM Data WHERE Data.lParentID = Main.lID AND "
               "Data.strClipBoardFormat = 'CF_UNICODETEXT' COLLATE NOCASE AND scm_match(Data.ooData, 0))";
    sql += ")";
    sql += q.groupId > 0 ? " AND Main.lParentID = ?1 ORDER BY Main.stickyClipGroupOrder DESC, Main.bIsGroup ASC, Main.clipGroupOrder DESC"
                         : " ORDER BY Main.stickyClipOrder DESC, Main.bIsGroup ASC, Main.clipOrder DESC";
    Stmt s(sql);
    s.Int(1, q.groupId);
    while (s.Row()) g_hits.ids.push_back(s.I64(0));
    return g_hits.ids;
}

// ---------------------------------------------------------------------------
// Rows
// ---------------------------------------------------------------------------
#define DBX_ROW_COLS                                                                                                     \
    "SELECT Main.lID, lDate, lastPasteDate, mText, QuickPasteText, lParentID, bIsGroup, lDontAutoDelete, "              \
    "stickyClipOrder, stickyClipGroupOrder, lShortCut, globalShortCut, "                                                \
    "EXISTS(SELECT 1 FROM Data d WHERE d.lParentID = Main.lID AND d.strClipBoardFormat = 'CF_HDROP' COLLATE NOCASE), "  \
    "EXISTS(SELECT 1 FROM Data d WHERE d.lParentID = Main.lID AND d.strClipBoardFormat IN ('CF_DIB','PNG','CF_DIBV5','CF_BITMAP') COLLATE NOCASE), " \
    "EXISTS(SELECT 1 FROM Data d WHERE d.lParentID = Main.lID AND d.strClipBoardFormat IN ('CF_UNICODETEXT','CF_TEXT','CF_OEMTEXT') COLLATE NOCASE) " \
    "FROM Main "

static const char kMainOrder[] = " ORDER BY Main.stickyClipOrder DESC, Main.bIsGroup ASC, Main.clipOrder DESC";

static ClipRow ReadRow(const Stmt& s, bool groupView) {
    ClipRow r;
    r.id = s.I64(0);
    r.date = s.I64(1);
    r.lastPasteDate = s.I64(2);
    r.text = s.W(3);
    r.quickPasteText = s.W(4);
    r.parentId = s.IsNull(5) ? -1 : s.I64(5);
    r.isGroup = s.I64(6) != 0;
    r.neverDelete = s.I64(7) != 0;
    r.sticky = s.D(groupView ? 9 : 8) != kNotSticky;
    r.hasShortcut = s.I64(10) != 0 || s.I64(11) != 0;
    r.kind = r.isGroup ? ClipKind::Group
             : s.I64(12) ? ClipKind::Files
             : s.I64(13) && !s.I64(14) ? ClipKind::Image
             : s.I64(14) ? ClipKind::Text
                         : ClipKind::Other;
    return r;
}

static bool RowById(int64_t id, ClipRow& out, bool groupView) {
    Stmt s(DBX_ROW_COLS "WHERE Main.lID = ?");
    s.Int(1, id);
    if (!s.Row()) return false;
    out = ReadRow(s, groupView);
    return true;
}

static double NewOrder(int64_t parent) {
    Stmt s(parent > 0 ? "SELECT clipGroupOrder FROM Main WHERE lParentID = ? ORDER BY clipGroupOrder DESC LIMIT 1"
                      : "SELECT clipOrder FROM Main ORDER BY clipOrder DESC LIMIT 1");
    s.Int(1, parent);
    return s.Row() ? s.D(0) + 1 : 0;
}

static int64_t ParentOf(int64_t id) {
    Stmt s("SELECT lParentID FROM Main WHERE lID = ?");
    s.Int(1, id);
    return s.Row() && !s.IsNull(0) ? s.I64(0) : -1;
}

// Ditto's CRC32 (Clip.cpp GenerateCRC with AdjustClipsForCRC on).
static void RtfDeleteParam(std::string& s, const std::string& find, bool digits) {  // Misc.cpp:1414
    size_t start = 0;
    while ((start = s.find(find, start)) != s.npos) {
        if (start > 0 && s[start - 1] == '\\') { start++; continue; }
        size_t inner = start + find.size(), end = inner;
        if (digits) {
            while (end < s.size() && isdigit((unsigned char)s[end])) end++;
            if (end == s.size()) break;
            if (end == inner) { start++; continue; }
        }
        s.erase(start, end - start);
    }
}

static void RtfRemoveSection(std::string& s, const std::string& section) {  // Misc.cpp:1472
    size_t start = s.find(section);
    if (start == s.npos) return;
    int depth = 0;
    for (size_t pos = start + 1; pos < s.size(); pos++) {
        if (s[pos] == '{') depth++;
        if (s[pos] == '}') {
            if (depth > 0) depth--;
            else { s.erase(start, pos - start + 1); return; }
        }
    }
}

static uint32_t Crc32(const void* data, size_t n, uint32_t crc) {
    static uint32_t table[256];
    if (!table[1])
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t c = i;
            for (int k = 0; k < 8; k++) c = c & 1 ? (c >> 1) ^ 0xEDB88320u : c >> 1;
            table[i] = c;
        }
    auto p = static_cast<const unsigned char*>(data);
    for (size_t i = 0; i < n; i++) crc = (crc >> 8) ^ table[(crc ^ p[i]) & 0xFF];
    return crc;
}

// Ditto hashes formats in its supported-types order (Types table, else its default list), not the stored order.
static std::vector<std::wstring> g_types;

static void LoadTypes() {
    g_types.clear();
    Stmt s("SELECT TypeText FROM Types ORDER BY lID");
    while (s.Row()) g_types.push_back(s.W(0));
    if (g_types.empty()) g_types = {L"CF_TEXT", L"Rich Text Format", L"CF_UNICODETEXT", L"CF_HDROP", L"CF_DIB", L"HTML Format", L"PNG"};
}

static int32_t ClipCrc(const std::vector<ClipFormat>& unordered) {
    std::vector<const ClipFormat*> formats;
    for (auto& f : unordered) formats.push_back(&f);
    auto rank = [](const ClipFormat* f) {
        for (size_t i = 0; i < g_types.size(); i++)
            if (!_wcsicmp(g_types[i].c_str(), f->name.c_str())) return i;
        return g_types.size();
    };
    std::stable_sort(formats.begin(), formats.end(), [&](auto a, auto b) { return rank(a) < rank(b); });
    uint32_t crc = 0xFFFFFFFF;
    for (auto* fp : formats) {
        const ClipFormat& f = *fp;
        const std::string& d = f.data;
        size_t n = d.size();
        if (f.name == L"Rich Text Format") {
            std::string rtf(d.c_str(), strnlen(d.c_str(), d.size()));
            RtfRemoveSection(rtf, "{\\*\\datastore");
            RtfDeleteParam(rtf, "\\rsid", true);
            RtfDeleteParam(rtf, "\\insrsid", true);
            RtfDeleteParam(rtf, "\\mdispDef1", false);
            crc = Crc32(rtf.data(), rtf.size(), crc);
            continue;
        }
        if (f.name == L"CF_TEXT") n = std::min(n, strnlen(d.data(), n) + 1);
        else if (f.name == L"CF_UNICODETEXT")
            n = std::min(n, (wcsnlen(reinterpret_cast<const wchar_t*>(d.data()), n / 2) + 1) * 2);
        crc = Crc32(d.data(), n, crc);
    }
    return (int32_t)~crc;
}

static std::vector<ClipFormat> StoredFormats(int64_t id) {
    std::vector<ClipFormat> out;
    Stmt s("SELECT strClipBoardFormat, ooData FROM Data WHERE lParentID = ? ORDER BY lID");
    s.Int(1, id);
    while (s.Row()) out.push_back({FormatIdFromName(s.W(0)), s.W(0), s.B(1)});
    return out;
}

static bool InsertFormats(int64_t id, const std::vector<ClipFormat>& formats) {
    for (auto& f : formats) {
        Stmt s("INSERT INTO Data (lParentID, strClipBoardFormat, ooData) VALUES (?, ?, ?)");
        if (!s.Int(1, id).Str(2, f.name).Blob(3, f.data).Run()) return false;
    }
    return true;
}

static std::wstring Desc(const std::wstring& text) {  // up to the first NUL, Left(500)
    return text.substr(0, std::min(text.find(L'\0'), (size_t)500));
}

static bool IsKeepForever(const Stmt& s, int shortcut, int dontDelete, int parent, int sticky, int groupSticky) {
    return s.I64(shortcut) != 0 || s.I64(dontDelete) != 0 || s.I64(parent) > 0 || s.D(sticky) != kNotSticky ||
           s.D(groupSticky) != kNotSticky;
}

static bool DeleteIds(const std::vector<int64_t>& ids) {
    for (int64_t id : ids) {
        Stmt s("DELETE FROM Main WHERE lID = ?");
        if (!s.Int(1, id).Run()) return false;
    }
    return true;
}

}  // namespace dbx

using namespace dbx;

// ---------------------------------------------------------------------------
// Contract
// ---------------------------------------------------------------------------
bool Db_Open() {
    if (g_db) return true;
    if (!LoadApi()) return false;
    std::wstring path = StoragePath() + L"\\clips.db";
    if (StoragePath().empty()) { g_err = L"No storage folder."; return false; }
    if (!FileExists(path)) {
        std::wstring src = DittoDbPath();
        if (src.empty()) Wh_Log(L"db: no Ditto database found, starting empty");
        else if (ImportDitto(src, path)) SetState(L"ImportedFromDitto", 1);
        else DeleteDbFiles(path);
    }
    ULONGLONG t0 = GetTickCount64();
    sqlite3* db = OpenFile(WideToUtf8(path), kOpenReadWrite | kOpenCreate);
    if (!db) return false;
    if (!Exec(db, "PRAGMA journal_mode = WAL; PRAGMA synchronous = NORMAL; PRAGMA cache_size = -32768; PRAGMA temp_store = MEMORY;") ||
        !Exec(db, "BEGIN IMMEDIATE") || !EnsureSchema(db) || !Exec(db, "COMMIT") ||
        // Ditto's full auto-vacuum moves megabytes per deleted image at commit; incremental lets
        // Db_Cleanup return the space in short steps. Ditto still opens the file fine.
        (QueryInt(db, "PRAGMA auto_vacuum") == 1 && !Exec(db, "PRAGMA auto_vacuum = 2")) ||
        api.create_function_v2(db, "scm_match", 2, kUtf16Le, nullptr, MatchFn, nullptr, nullptr, nullptr) != kOk) {
        if (g_err.empty()) SetErr(db, "Could not set up the database");
        api.close_v2(db);
        return false;
    }
    g_db = db;
    g_gen++;
    LoadTypes();
    Wh_Log(L"db: opened %s in %llu ms", path.c_str(), GetTickCount64() - t0);
    return true;
}

void Db_Close() {
    if (!g_db) return;
    for (auto& [sql, s] : g_cache) api.finalize(s);
    g_cache.clear();
    api.close_v2(g_db);
    g_db = nullptr;
    g_hits = {};
}

bool Db_IsOpen() { return g_db != nullptr; }
std::wstring Db_LastError() { return g_err; }

int Db_CountClips(const ClipQuery& q) {
    if (!g_db) return 0;
    if (!q.search.empty()) return (int)SearchIds(q).size();
    Stmt s(q.groupId > 0 ? "SELECT COUNT(Main.lID) FROM Main WHERE Main.lParentID = ?" : "SELECT COUNT(Main.lID) FROM Main WHERE Main.bIsGroup = 0");
    s.Int(1, q.groupId);
    return s.Row() ? (int)s.I64(0) : 0;
}

std::vector<ClipRow> Db_QueryClips(const ClipQuery& q, int offset, int limit) {
    std::vector<ClipRow> out;
    if (!g_db || limit <= 0 || offset < 0) return out;
    bool group = q.groupId > 0;
    if (!q.search.empty()) {
        const auto& ids = SearchIds(q);
        for (size_t i = offset; i < ids.size() && (int)out.size() < limit; i++)
            if (ClipRow r; RowById(ids[i], r, group)) out.push_back(std::move(r));
        return out;
    }
    Stmt s(group ? DBX_ROW_COLS "WHERE Main.lParentID = ?3 ORDER BY Main.stickyClipGroupOrder DESC, Main.bIsGroup ASC, "
                                "Main.clipGroupOrder DESC LIMIT ?1 OFFSET ?2"
                 : DBX_ROW_COLS "WHERE Main.bIsGroup = 0 ORDER BY Main.stickyClipOrder DESC, Main.bIsGroup ASC, "
                                "Main.clipOrder DESC LIMIT ?1 OFFSET ?2");
    s.Int(1, limit).Int(2, offset);
    if (group) s.Int(3, q.groupId);
    while (s.Row()) out.push_back(ReadRow(s, group));
    return out;
}

bool Db_GetClipRow(int64_t id, ClipRow& out) { return g_db && RowById(id, out, false); }

bool Db_GetClipData(int64_t id, ClipData& out) {
    if (!g_db) return false;
    Stmt s("SELECT mText FROM Main WHERE lID = ?");
    if (!s.Int(1, id).Row()) return false;
    out = {};
    out.description = s.W(0);
    out.formats = StoredFormats(id);
    return true;
}

bool Db_GetFormat(int64_t id, const std::wstring& formatName, std::string& out) {
    if (!g_db) return false;
    Stmt s("SELECT ooData FROM Data WHERE lParentID = ? AND strClipBoardFormat = ? COLLATE NOCASE ORDER BY lID LIMIT 1");
    if (!s.Int(1, id).Str(2, formatName).Row()) return false;
    out = s.B(0);
    return true;
}

std::wstring Db_GetClipText(int64_t id) {
    std::string d;
    if (Db_GetFormat(id, L"CF_UNICODETEXT", d)) {
        auto p = reinterpret_cast<const wchar_t*>(d.data());
        return std::wstring(p, wcsnlen(p, d.size() / 2));
    }
    if (Db_GetFormat(id, L"CF_TEXT", d)) {
        int n = (int)strnlen(d.data(), d.size());
        std::wstring w(MultiByteToWideChar(CP_ACP, 0, d.data(), n, nullptr, 0), L'\0');
        MultiByteToWideChar(CP_ACP, 0, d.data(), n, w.data(), (int)w.size());
        return w;
    }
    if (Db_GetFormat(id, L"CF_HDROP", d) && d.size() >= sizeof(DROPFILES)) {
        auto df = reinterpret_cast<const DROPFILES*>(d.data());
        std::wstring out;
        for (size_t pos = df->pFiles; pos < d.size();) {
            std::wstring name;
            if (df->fWide) {
                auto p = reinterpret_cast<const wchar_t*>(d.data() + pos);
                name.assign(p, wcsnlen(p, (d.size() - pos) / 2));
                pos += (name.size() + 1) * 2;
            } else {
                std::string a(d.data() + pos, strnlen(d.data() + pos, d.size() - pos));
                pos += a.size() + 1;
                name.assign(MultiByteToWideChar(CP_ACP, 0, a.data(), (int)a.size(), nullptr, 0), L'\0');
                MultiByteToWideChar(CP_ACP, 0, a.data(), (int)a.size(), name.data(), (int)name.size());
            }
            if (name.empty()) break;
            if (!out.empty()) out += L"\r\n";
            out += name;
        }
        return out;
    }
    ClipRow r;
    return Db_GetClipRow(id, r) ? r.text : std::wstring();
}

int64_t Db_SaveClip(const ClipData& clip) {
    if (!g_db || clip.formats.empty()) return 0;
    int32_t crc = ClipCrc(clip.formats);
    Txn t;
    if (!t) return 0;
    if (!g_set.allowDuplicates) {  // Clip.cpp AddToDB / FindDuplicate: only clipOrder moves
        Stmt dup("SELECT lID FROM Main WHERE CRC = ? AND bIsGroup = 0 LIMIT 1");
        if (dup.Int(1, crc).Row()) {
            int64_t id = dup.I64(0);
            Stmt up("UPDATE Main SET clipOrder = ? WHERE lID = ?");
            return up.Dbl(1, NewOrder(-1)).Int(2, id).Run() && t.Commit() ? id : 0;
        }
    }
    int64_t now = UnixNow();
    Stmt ins("INSERT INTO Main (lDate, mText, lShortCut, lDontAutoDelete, CRC, bIsGroup, lParentID, QuickPasteText, clipOrder, "
             "clipGroupOrder, globalShortCut, lastPasteDate, stickyClipOrder, stickyClipGroupOrder, MoveToGroupShortCut, "
             "GlobalMoveToGroupShortCut) VALUES (?1, ?2, 0, 0, ?3, 0, -1, '', ?4, 0, 0, ?1, -(2147483647), -(2147483647), 0, 0)");
    if (!ins.Int(1, now).Str(2, Desc(clip.description)).Int(3, crc).Dbl(4, NewOrder(-1)).Run()) return 0;
    int64_t id = api.last_insert_rowid(g_db);
    return InsertFormats(id, clip.formats) && t.Commit() ? id : 0;
}

bool Db_MoveToTop(int64_t id) {  // ProcessPaste.cpp:200
    if (!g_db) return false;
    int64_t parent = ParentOf(id);
    Txn t;
    Stmt s("UPDATE Main SET clipOrder = ?, lastPasteDate = ? WHERE lID = ?");
    if (!t || !s.Dbl(1, NewOrder(-1)).Int(2, UnixNow()).Int(3, id).Run()) return false;
    if (parent > 0) {
        Stmt g("UPDATE Main SET clipGroupOrder = ? WHERE lID = ?");
        if (!g.Dbl(1, NewOrder(parent)).Int(2, id).Run()) return false;
    }
    return t.Commit();
}

bool Db_DeleteClips(const std::vector<int64_t>& ids) {  // ClipIds.cpp DeleteIDs
    if (!g_db) return false;
    Txn t;
    if (!t) return false;
    for (int64_t id : ids) {
        Stmt s("UPDATE Main SET lParentID = -1 WHERE lParentID = ?");
        if (!s.Int(1, id).Run()) return false;
    }
    if (!DeleteIds(ids) || !t.Commit()) return false;
    Drain(g_db, 50);
    return true;
}

static bool UpdateOne(const char* sql, int64_t id, const std::function<void(Stmt&)>& bind) {
    if (!g_db) return false;
    Stmt s(sql);
    bind(s);
    s.Int(9, id);
    bool ok = s.Run() && api.changes(g_db) > 0;
    if (ok) g_gen++;
    return ok;
}

bool Db_SetDescription(int64_t id, const std::wstring& text) {
    return UpdateOne("UPDATE Main SET mText = ?1 WHERE lID = ?9", id, [&](Stmt& s) { s.Str(1, text); });
}

bool Db_SetQuickPasteText(int64_t id, const std::wstring& text) {
    return UpdateOne("UPDATE Main SET QuickPasteText = ?1 WHERE lID = ?9", id, [&](Stmt& s) { s.Str(1, text); });
}

bool Db_SetNeverDelete(int64_t id, bool on) {  // CopyProperties.cpp:441 stores the time it was set
    return UpdateOne("UPDATE Main SET lDontAutoDelete = ?1 WHERE lID = ?9", id, [&](Stmt& s) { s.Int(1, on ? UnixNow() : 0); });
}

bool Db_SetSticky(int64_t id, bool on, bool inGroup) {
    if (!g_db) return false;
    double order = kNotSticky;
    if (on) {
        Stmt s(inGroup ? "SELECT MAX(stickyClipGroupOrder) FROM Main WHERE lParentID = ? AND stickyClipGroupOrder <> -(2147483647)"
                       : "SELECT MAX(stickyClipOrder) FROM Main WHERE stickyClipOrder <> -(2147483647)");
        s.Int(1, ParentOf(id));
        order = s.Row() && !s.IsNull(0) ? s.D(0) + 1 : 1;
        if (order == 0) order = 1;
    }
    return UpdateOne(inGroup ? "UPDATE Main SET stickyClipGroupOrder = ?1 WHERE lID = ?9" : "UPDATE Main SET stickyClipOrder = ?1 WHERE lID = ?9",
                     id, [&](Stmt& s) { s.Dbl(1, order); });
}

bool Db_SetStickyOrder(const std::vector<int64_t>& idsTopFirst, bool inGroup) {
    if (!g_db || idsTopFirst.empty()) return false;
    // Higher order sorts first, so the top clip gets the largest number.
    Txn t;
    if (!t) return false;
    double order = (double)idsTopFirst.size();
    for (int64_t id : idsTopFirst) {
        if (!UpdateOne(inGroup ? "UPDATE Main SET stickyClipGroupOrder = ?1 WHERE lID = ?9"
                               : "UPDATE Main SET stickyClipOrder = ?1 WHERE lID = ?9",
                       id, [&](Stmt& s) { s.Dbl(1, order); }))
            return false;
        order -= 1;
    }
    return t.Commit();
}

bool Db_UpdateClipText(int64_t id, const std::wstring& text) {  // Clip.cpp SaveFromEditWnd
    if (!g_db) return false;
    Txn t;
    Stmt del("DELETE FROM Data WHERE lParentID = ? AND strClipBoardFormat IN ('CF_UNICODETEXT', 'CF_TEXT', 'CF_OEMTEXT', "
             "'CF_LOCALE', 'HTML Format', 'Rich Text Format', 'Rich Text Format Without Objects', 'RTF As Text') COLLATE NOCASE");
    if (!t || !del.Int(1, id).Run()) return false;
    std::string uni(reinterpret_cast<const char*>(text.c_str()), (text.size() + 1) * sizeof(wchar_t));
    int n = WideCharToMultiByte(CP_ACP, 0, text.c_str(), (int)text.size() + 1, nullptr, 0, nullptr, nullptr);
    std::string ansi(n, '\0');
    WideCharToMultiByte(CP_ACP, 0, text.c_str(), (int)text.size() + 1, ansi.data(), n, nullptr, nullptr);
    if (!InsertFormats(id, {{CF_UNICODETEXT, L"CF_UNICODETEXT", uni}, {CF_TEXT, L"CF_TEXT", ansi}})) return false;
    Stmt up("UPDATE Main SET mText = ?, CRC = ? WHERE lID = ?");
    if (!up.Str(1, Desc(text)).Int(2, ClipCrc(StoredFormats(id))).Int(3, id).Run() || api.changes(g_db) == 0) return false;
    return t.Commit();
}

int64_t Db_CreateGroup(const std::wstring& name, int64_t parentId) {  // Misc.cpp NewGroupID
    if (!g_db) return 0;
    std::wstring text = name;
    if (text.empty()) {
        wchar_t buf[64];
        time_t now = time(nullptr);
        wcsftime(buf, ARRAYSIZE(buf), L"NewGroup %y/%m/%d %H:%M:%S", localtime(&now));
        text = buf;
    }
    Stmt s("INSERT INTO Main (lDate, mText, lDontAutoDelete, bIsGroup, lParentID, stickyClipOrder, stickyClipGroupOrder) "
           "VALUES (?1, ?2, ?1, 1, ?3, -(2147483647), -(2147483647))");
    if (!s.Int(1, UnixNow()).Str(2, text).Int(3, parentId > 0 ? parentId : -1).Run()) return 0;
    g_gen++;
    return api.last_insert_rowid(g_db);
}

bool Db_MoveToGroup(const std::vector<int64_t>& ids, int64_t groupId) {  // ClipIds.cpp MoveTo, last id first
    if (!g_db) return false;
    Txn t;
    if (!t) return false;
    for (auto it = ids.rbegin(); it != ids.rend(); ++it) {
        bool cycle = false;  // a group may not go inside itself or its own subgroup
        for (int64_t p = groupId, hops = 0; p > 0 && hops < 1000; p = ParentOf(p), hops++)
            if (p == *it) { cycle = true; break; }
        if (cycle) continue;
        if (groupId > 0) {
            Stmt s("UPDATE Main SET lParentID = ?, clipGroupOrder = ? WHERE lID = ?");
            if (!s.Int(1, groupId).Dbl(2, NewOrder(groupId)).Int(3, *it).Run()) return false;
        } else {
            Stmt s("UPDATE Main SET lParentID = -1 WHERE lID = ?");
            if (!s.Int(1, *it).Run()) return false;
        }
    }
    return t.Commit();
}

std::vector<ClipRow> Db_ListGroups() {
    std::vector<ClipRow> out;
    if (!g_db) return out;
    Stmt s(DBX_ROW_COLS "WHERE Main.bIsGroup = 1 ORDER BY Main.mText COLLATE NOCASE");
    while (s.Row()) out.push_back(ReadRow(s, false));
    return out;
}

int64_t Db_ClipIdAtPosition(int index) {
    if (!g_db || index < 0) return 0;
    Stmt s(std::string("SELECT Main.lID FROM Main WHERE Main.bIsGroup = 0") + kMainOrder + " LIMIT 1 OFFSET ?");
    return s.Int(1, index).Row() ? s.I64(0) : 0;
}

int Db_TotalClips() { return g_db ? (int)QueryInt(g_db, "SELECT COUNT(*) FROM Main WHERE bIsGroup = 0") : 0; }

void Db_Cleanup() {  // DatabaseUtilities.cpp RemoveOldEntries
    if (!g_db) return;
    ULONGLONG t0 = GetTickCount64();
    int removed = 0;
    {
        Txn t;
        if (!t) return;
        if (g_set.maxClips > 0) {
            std::vector<int64_t> ids;
            Stmt s("SELECT lID, lShortCut, lParentID, lDontAutoDelete, stickyClipOrder, stickyClipGroupOrder FROM Main "
                   "WHERE bIsGroup = 0 ORDER BY clipOrder DESC LIMIT -1 OFFSET ?");
            s.Int(1, g_set.maxClips);
            while (s.Row())
                if (!IsKeepForever(s, 1, 3, 2, 4, 5)) ids.push_back(s.I64(0));
            if (!DeleteIds(ids)) return;
            removed += (int)ids.size();
        }
        if (g_set.expireDays > 0) {
            Stmt s("DELETE FROM Main WHERE lastPasteDate < ? AND bIsGroup = 0 AND lShortCut = 0 AND lParentID <= 0 AND "
                   "lDontAutoDelete = 0 AND stickyClipOrder = -(2147483647) AND stickyClipGroupOrder = -(2147483647)");
            if (!s.Int(1, UnixNow() - (int64_t)g_set.expireDays * 86400).Run()) return;
            removed += api.changes(g_db);
        }
        if (removed ? !t.Commit() : false) return;
    }
    Drain(g_db, 80);
    int freed = 0;
    while (GetTickCount64() - t0 < 80 && QueryInt(g_db, "PRAGMA freelist_count") > 0 && Exec(g_db, "PRAGMA incremental_vacuum(64)"))
        freed += 64;
    if (removed || g_drained || freed)
        Wh_Log(L"db: cleanup removed %d clips, cleared %d deleted, freed up to %d pages, %llu ms", removed, g_drained, freed,
               GetTickCount64() - t0);
}

bool Db_DeleteAllUnpinned() {  // DatabaseUtilities.cpp DeleteNonUsedClips
    if (!g_db) return false;
    Stmt s("DELETE FROM Main WHERE bIsGroup = 0 AND lShortCut = 0 AND lParentID <= 0 AND lDontAutoDelete = 0 AND "
           "stickyClipOrder = -(2147483647) AND stickyClipGroupOrder = -(2147483647)");
    if (!s.Run()) return false;
    g_gen++;
    Drain(g_db, 80);  // the rest drains on the cleanup timer
    return true;
}

#ifdef SCM_HARNESS
// ---------------------------------------------------------------------------
// Self test: imports a copy of testdata\Ditto-copy.db into a fresh storage dir.
// ---------------------------------------------------------------------------
namespace dbx_test {

static int g_fails;
static void Check(bool ok, const wchar_t* what) {
    if (!ok) g_fails++;
    Wh_Log(L"%s %s", ok ? L"ok  " : L"FAIL", what);
}

static double Ms() {
    LARGE_INTEGER f, c;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&c);
    return c.QuadPart * 1000.0 / f.QuadPart;
}

static int64_t Q(const char* sql) { return QueryInt(g_db, sql, -1); }
static int64_t Orphans() { return Q("SELECT COUNT(*) FROM Data WHERE lParentID NOT IN (SELECT lID FROM Main)"); }

static bool HasId(const std::vector<ClipRow>& rows, int64_t id) {
    return std::any_of(rows.begin(), rows.end(), [&](const ClipRow& r) { return r.id == id; });
}

static std::vector<ClipRow> Search(const std::wstring& text, const wchar_t* mode, bool fullText, int64_t group = -1) {
    g_set.searchMode = mode;
    g_set.searchFullText = fullText;
    ClipQuery q{group, text};
    return Db_QueryClips(q, 0, Db_CountClips(q));
}

static ClipData TextClip(const std::wstring& text) {
    ClipData c;
    c.description = text;
    c.formats.push_back({CF_UNICODETEXT, L"CF_UNICODETEXT", std::string(reinterpret_cast<const char*>(text.c_str()), (text.size() + 1) * 2)});
    c.formats.push_back({CF_TEXT, L"CF_TEXT", WideToUtf8(text) + '\0'});
    return c;
}

static int g_cleanupCalls;
static double g_cleanupMax;

static void DrainAll() {
    int saveMax = g_set.maxClips, saveExp = g_set.expireDays;
    g_set.maxClips = g_set.expireDays = 0;
    for (int i = 0; i < 100000 && (Q("SELECT COUNT(*) FROM MainDeletes") > 0 || Q("PRAGMA freelist_count") > 0); i++) {
        double t = Ms();
        Db_Cleanup();
        g_cleanupCalls++;
        g_cleanupMax = std::max(g_cleanupMax, Ms() - t);
    }
    g_set.maxClips = saveMax;
    g_set.expireDays = saveExp;
}

static int RunPython(const std::wstring& db) {
    std::wstring cmd = L"python -I -c \"import sqlite3,sys;r=sqlite3.connect(sys.argv[1]).execute('PRAGMA integrity_check').fetchone()[0];"
                       L"print('python integrity_check:',r);sys.exit(0 if r=='ok' else 1)\" \"" + db + L"\"";
    STARTUPINFOW si{};
    si.cb = sizeof si;
    PROCESS_INFORMATION pi{};
    if (!CreateProcessW(nullptr, cmd.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi)) return -1;
    DWORD code = 99;
    if (WaitForSingleObject(pi.hProcess, 300000) != WAIT_OBJECT_0) TerminateProcess(pi.hProcess, 98);
    GetExitCodeProcess(pi.hProcess, &code);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return (int)code;
}

static std::wstring FindWord(const std::wstring& text, size_t from, size_t len) {
    for (size_t i = from; i + len <= text.size(); i++) {
        bool ok = (i == 0 || !iswalpha(text[i - 1])) && (i + len == text.size() || !iswalpha(text[i + len]));
        for (size_t k = 0; ok && k < len; k++) ok = text[i + k] < 128 && iswalpha(text[i + k]);
        if (ok) return text.substr(i, len);
    }
    return {};
}

static int Run() {
    std::wstring storage = StoragePath(), clips = storage + L"\\clips.db";
    DeleteDbFiles(clips);
    wchar_t exe[MAX_PATH];
    GetModuleFileNameW(nullptr, exe, MAX_PATH);
    std::wstring root = exe;
    root.resize(root.find_last_of(L'\\'));
    root.resize(root.find_last_of(L'\\'));
    wchar_t env[MAX_PATH * 2];
    std::wstring src;
    if (GetEnvironmentVariableW(L"SCM_DITTO_DB", env, ARRAYSIZE(env))) src = env;
    else {
        std::wstring orig = root + L"\\testdata\\Ditto-copy.db";
        src = root + L"\\test-db\\ditto-src.db";
        CreateDirectoryW((root + L"\\test-db").c_str(), nullptr);
        WIN32_FILE_ATTRIBUTE_DATA a{}, b{};
        GetFileAttributesExW(orig.c_str(), GetFileExInfoStandard, &a);
        if (!GetFileAttributesExW(src.c_str(), GetFileExInfoStandard, &b) || a.nFileSizeLow != b.nFileSizeLow ||
            a.nFileSizeHigh != b.nFileSizeHigh) {
            if (!CopyFileW(orig.c_str(), src.c_str(), FALSE)) { Wh_Log(L"FAIL could not copy the test database"); return 1; }
        }
        SetEnvironmentVariableW(L"SCM_DITTO_DB", src.c_str());
    }
    Wh_Log(L"info source copy %s", src.c_str());
    if (!LoadApi()) return 1;

    // What Ditto itself would show, straight from the source.
    int64_t srcCount = -1;
    std::vector<int64_t> dittoOrder;
    if (sqlite3* s = OpenFile(ReadOnlyUri(src), kOpenReadOnly | kOpenUri)) {
        srcCount = QueryInt(s, "SELECT COUNT(*) FROM Main", -1);
        {
            Stmt st((std::string("SELECT lID FROM Main WHERE Main.bIsGroup = 0") + kMainOrder + " LIMIT 50").c_str(), s, false);
            while (st.Row()) dittoOrder.push_back(st.I64(0));
        }
        api.close_v2(s);
    }
    Check(srcCount > 0, L"source database readable");

    double t = Ms();
    Check(Db_Open(), L"Db_Open imports Ditto");
    double tImport = Ms() - t;
    Check(Q("SELECT COUNT(*) FROM Main") == srcCount, L"imported count equals source Main count");
    Check(Q("SELECT COUNT(*) FROM MainDeletes") == 0, L"MainDeletes empty after import");
    Check(Orphans() == 0, L"no orphan Data rows after import");
    Check(Q("PRAGMA busy_timeout") == 2000 && Q("PRAGMA synchronous") == 1, L"busy timeout 2000, synchronous normal");
    {
        Stmt jm("PRAGMA journal_mode", g_db, false);
        Check(jm.Row() && jm.W(0) == L"wal", L"journal mode is WAL");
    }
    Check(Q("SELECT COUNT(*) FROM sqlite_master WHERE type='index' AND name='Data_ParentId_Format'") == 1, L"index on Data(lParentID)");
    Check(Q("PRAGMA auto_vacuum") == 2, L"incremental auto vacuum");

    Db_Close();
    t = Ms();
    Check(Db_Open(), L"Db_Open again");
    double tOpen = Ms() - t;
    t = Ms();
    int count = Db_CountClips({});
    double tCount = Ms() - t;
    t = Ms();
    auto page = Db_QueryClips({}, 0, 50);
    double tPage = Ms() - t;
    bool same = page.size() == dittoOrder.size();
    for (size_t i = 0; same && i < page.size(); i++) same = page[i].id == dittoOrder[i];
    Check(same && !page.empty(), L"first page order equals Ditto's SQL order");
    Check(count == Db_TotalClips(), L"main list count equals total clips (no groups)");
    t = Ms();
    Db_QueryClips({}, 400, 50);
    double tPage2 = Ms() - t;

    int crcSame = 0, crcTried = 0;
    for (auto& r : page) {
        Stmt s("SELECT CRC FROM Main WHERE lID = ?");
        if (!s.Int(1, r.id).Row()) continue;
        int64_t stored = s.I64(0);
        crcTried++;
        crcSame += ClipCrc(StoredFormats(r.id)) == (int32_t)stored;
    }
    Wh_Log(L"info CRC recomputed equal for %d of %d imported clips", crcSame, crcTried);
    Check(crcSame > 0, L"CRC algorithm matches Ditto's stored CRCs");

    // Search: a text clip with a 5-letter word and a later 4-letter word.
    ClipRow probe;
    std::wstring word, word2;
    for (auto& r : page) {
        if (r.kind != ClipKind::Text || (word = FindWord(r.text, 0, 5)).empty()) continue;
        if (!(word2 = FindWord(r.text, r.text.find(word) + 6, 4)).empty()) { probe = r; break; }
    }
    Check(probe.id != 0, L"found a text clip to search for");
    std::wstring upper = word;
    CharUpperBuffW(upper.data(), (DWORD)upper.size());
    Check(HasId(Search(upper, L"contains", true), probe.id), L"contains finds a word, any case");
    Check(HasId(Search(word2 + L" " + word, L"allWords", true), probe.id), L"allWords finds words in any order");
    Check(!HasId(Search(word2 + L" " + word + L" zzqqxxj", L"allWords", true), probe.id), L"allWords needs every word");
    size_t lead = probe.text.find_first_not_of(L" \t\r\n");
    Check(HasId(Search(probe.text.substr(lead, 6), L"startsWith", true), probe.id), L"startsWith finds the start");
    std::wstring startLow = probe.text.substr(lead, 5), wordLow = word;
    CharLowerBuffW(startLow.data(), (DWORD)startLow.size());
    CharLowerBuffW(wordLow.data(), (DWORD)wordLow.size());
    Check(startLow == wordLow || !HasId(Search(word2, L"startsWith", true), probe.id), L"startsWith ignores the middle");
    Db_SetQuickPasteText(probe.id, L"qpzzkx");
    Check(HasId(Search(L"qpzzkx", L"contains", false), probe.id), L"search matches QuickPasteText");
    Db_SetQuickPasteText(probe.id, L"");
    // Full text: a word that only appears past the first 500 characters.
    bool fullTested = false;
    for (auto& r : Db_QueryClips({}, 0, count)) {
        std::wstring full = Db_GetClipText(r.id), low = full;
        if (full.size() < 700) continue;
        CharLowerBuffW(low.data(), (DWORD)low.size());
        std::wstring w = FindWord(low, 600, 6);
        if (w.empty() || low.substr(0, 520).find(w) != low.npos) continue;
        Check(HasId(Search(w, L"contains", true), r.id), L"full text search finds a word past 500 chars");
        Check(!HasId(Search(w, L"contains", false), r.id), L"short search skips words past 500 chars");
        fullTested = true;
        break;
    }
    Check(fullTested, L"found a long clip for the full text check");
    g_set.searchMode = L"contains";
    g_set.searchFullText = true;
    double tS1, tS5;
    {
        g_hits = {};
        t = Ms();
        ClipQuery q{-1, L"e"};
        int n = Db_CountClips(q);
        Db_QueryClips(q, 0, 50);
        tS1 = Ms() - t;
        g_hits = {};
        t = Ms();
        q.search = word;
        int n5 = Db_CountClips(q);
        Db_QueryClips(q, 0, 50);
        tS5 = Ms() - t;
        Wh_Log(L"info search 'e' -> %d hits, '%s' -> %d hits", n, word.c_str(), n5);
    }

    // Save, duplicate, allowDuplicates.
    int total = Db_TotalClips();
    int stickyCount = (int)Q("SELECT COUNT(*) FROM Main WHERE bIsGroup = 0 AND stickyClipOrder <> -(2147483647)");
    int64_t id1 = Db_SaveClip(TextClip(L"Seamless test clip one"));
    Check(id1 > 0 && Db_TotalClips() == total + 1, L"save adds a clip");
    auto top = Db_QueryClips({}, 0, stickyCount + 1);
    Check(top.size() == (size_t)stickyCount + 1 && top.back().id == id1, L"new clip is first below sticky clips");
    Db_SaveClip(TextClip(L"Seamless test clip two"));
    int64_t again = Db_SaveClip(TextClip(L"Seamless test clip one"));
    top = Db_QueryClips({}, 0, stickyCount + 1);
    Check(again == id1 && Db_TotalClips() == total + 2 && top.back().id == id1, L"duplicate save moves the old clip to the top");
    g_set.allowDuplicates = true;
    int64_t id2 = Db_SaveClip(TextClip(L"Seamless test clip one"));
    g_set.allowDuplicates = false;
    Check(id2 > 0 && id2 != id1 && Db_TotalClips() == total + 3, L"allowDuplicates saves a second copy");
    ClipData cd;
    Check(Db_GetClipData(id1, cd) && cd.formats.size() == 2 && cd.formats[0].name == L"CF_UNICODETEXT" &&
              cd.description == L"Seamless test clip one",
          L"clip data round trip");

    // Sticky, never delete, groups.
    ClipRow r;
    Db_SetSticky(id2, true, false);
    Check(Db_QueryClips({}, 0, 1)[0].id == id2 && Db_GetClipRow(id2, r) && r.sticky, L"sticky goes to the very top");
    Db_SetSticky(id2, false, false);
    Check(Db_GetClipRow(id2, r) && !r.sticky, L"sticky off");
    Db_SetNeverDelete(id2, true);
    Check(Db_GetClipRow(id2, r) && r.neverDelete, L"never delete on");
    Db_SetNeverDelete(id2, false);
    Check(Db_GetClipRow(id2, r) && !r.neverDelete, L"never delete off");
    Check(Db_SetDescription(id2, L"Renamed") && Db_GetClipRow(id2, r) && r.text == L"Renamed", L"description");
    int64_t gid = Db_CreateGroup(L"Test group", -1);
    int64_t gid2 = Db_CreateGroup(L"", gid);
    auto groups = Db_ListGroups();
    Check(gid > 0 && groups.size() == 2 && HasId(groups, gid) && groups[0].kind == ClipKind::Group, L"create and list groups");
    Check(Db_MoveToGroup({id1, id2}, gid) && Db_CountClips({gid, L""}) == 3, L"move clips into a group");
    auto inGroup = Db_QueryClips({gid, L""}, 0, 10);
    Check(inGroup.size() == 3 && inGroup[0].id == id1, L"first moved clip is on top in the group");
    Check(Db_GetClipRow(id1, r) && r.parentId == gid && HasId(Db_QueryClips({}, 0, 10), id1), L"grouped clips stay in the main list");
    Check(!HasId(Db_QueryClips({}, 0, count + 10), gid), L"groups are not in the main list");
    Db_SetSticky(id2, true, true);
    inGroup = Db_QueryClips({gid, L""}, 0, 10);
    Check(inGroup[0].id == id2 && inGroup[0].sticky, L"sticky inside a group");
    Check(Search(L"seamless TEST", L"contains", true, gid).size() == 2, L"search inside a group");
    Db_MoveToGroup({gid}, gid2);
    Check(Db_GetClipRow(gid, r) && r.parentId == -1, L"a group cannot go inside its own subgroup");
    Db_MoveToTop(id1);
    Check(Db_QueryClips({gid, L""}, 0, 10)[1].id == id1, L"move to top inside a group");
    Check(Db_DeleteClips({gid}) && !Db_GetClipRow(gid, r) && Db_GetClipRow(id1, r) && r.parentId == -1 &&
              Db_GetClipRow(gid2, r) && r.parentId == -1,
          L"deleting a group frees its clips");
    Db_SetSticky(id2, false, true);

    // Edit text.
    std::wstring edited = L"Edited text \u00FC\u00E9";
    Check(Db_UpdateClipText(id1, edited) && Db_GetClipText(id1) == edited && Db_GetClipRow(id1, r) && r.text == edited, L"UpdateClipText");
    {
        ClipData e;
        e.description = edited;
        Db_GetClipData(id1, e);
        Check(Db_SaveClip(e) == id1, L"edited clip is found as a duplicate (CRC updated)");
    }

    // Delete and drain.
    Check(Db_DeleteClips({id2, gid2}) && !Db_GetClipRow(id2, r), L"delete clips");
    DrainAll();
    Check(Q("SELECT COUNT(*) FROM MainDeletes") == 0 && Orphans() == 0, L"no orphans after drain");

    // Reopen must not import again.
    Db_Close();
    t = Ms();
    Check(Db_Open() && Db_GetClipRow(id1, r), L"second open keeps our clips (no re-import)");
    double tReopen = Ms() - t;

    // Cleanup with maxClips = 10 (Ditto's RemoveOldEntries rule).
    Db_SetNeverDelete(id1, true);
    int64_t expect = Q("SELECT COUNT(*) FROM Main WHERE bIsGroup = 0 AND (lID IN (SELECT lID FROM Main WHERE bIsGroup = 0 "
                       "ORDER BY clipOrder DESC LIMIT 10) OR lShortCut <> 0 OR lDontAutoDelete <> 0 OR lParentID > 0 OR "
                       "stickyClipOrder <> -(2147483647) OR stickyClipGroupOrder <> -(2147483647))");
    g_set.maxClips = 10;
    t = Ms();
    Db_Cleanup();
    double tClean = Ms() - t;
    g_set.maxClips = 0;
    Check(Db_TotalClips() == expect && Db_GetClipRow(id1, r), L"cleanup keeps 10 plus protected clips");
    t = Ms();
    DrainAll();
    double tDrain = Ms() - t;
    Check(Q("SELECT COUNT(*) FROM MainDeletes") == 0 && Orphans() == 0, L"cleanup drain leaves no orphans");
    int64_t keep = Q("SELECT COUNT(*) FROM Main WHERE bIsGroup = 0 AND (lDontAutoDelete <> 0 OR stickyClipOrder <> -(2147483647) OR "
                     "stickyClipGroupOrder <> -(2147483647) OR lParentID > 0 OR lShortCut <> 0)");
    Check(Db_DeleteAllUnpinned() && Db_GetClipRow(id1, r) && Db_TotalClips() == keep, L"delete all unpinned keeps protected clips");
    DrainAll();
    Check(Db_ClipIdAtPosition(0) == Db_QueryClips({}, 0, 1)[0].id, L"clip id at position");
    Db_Close();

    Check(RunPython(clips) == 0, L"python sqlite3 integrity_check ok");
    Wh_Log(L"time import %.0f ms, open %.1f ms, count %.2f ms, first page %.2f ms, page at 400 %.2f ms, search 1 letter %.2f ms, "
           L"search 5 letters %.2f ms, reopen %.1f ms, cleanup %.1f ms, drain all %.0f ms",
           tImport, tOpen, tCount, tPage, tPage2, tS1, tS5, tReopen, tClean, tDrain);
    Wh_Log(L"info drain: %d cleanup calls, slowest %.0f ms", g_cleanupCalls, g_cleanupMax);
    Wh_Log(L"db test: %d failures", g_fails);
    return g_fails ? 1 : 0;
}

}  // namespace dbx_test

int Harness_TestDb() { return dbx_test::Run(); }
#endif

// ---------------------------------------------------------------------------
// 30-capture.cpp : clipboard capture, paste, special paste, caret, hotkeys
// and the tray icon. Behavior follows Ditto (Clip.cpp, ClipboardViewer.cpp,
// OleClipSource.cpp, ExternalWindowTracker.cpp).
// ---------------------------------------------------------------------------

#include <random>

bool g_capturePaused;
HWND g_pasteTarget;

// Ditto defaults: ProcessDrawClipboardDelay 100 ms, SaveClipDelay 500 ms,
// DescTextSize 500 characters (Options.cpp).
constexpr UINT kCapDebounceMs = 100;
constexpr UINT kCapOpenRetryMs = 50;
constexpr int kCapOpenRetries = 10;
constexpr DWORD kCapTooFastMs = 500;
constexpr size_t kCapDescMax = 500;

// ---------------------------------------------------------------------------
// Format names (Ditto Misc.cpp GetFormatName / GetFormatID; stored in the DB)
// ---------------------------------------------------------------------------
struct Cap_StdFormat {
    UINT cf;
    const wchar_t* name;
};
static const Cap_StdFormat kCapStdFormats[] = {
    {CF_TEXT, L"CF_TEXT"},
    {CF_BITMAP, L"CF_BITMAP"},
    {CF_METAFILEPICT, L"CF_METAFILEPICT"},
    {CF_SYLK, L"CF_SYLK"},
    {CF_DIF, L"CF_DIF"},
    {CF_TIFF, L"CF_TIFF"},
    {CF_OEMTEXT, L"CF_OEMTEXT"},
    {CF_DIB, L"CF_DIB"},
    {CF_PALETTE, L"CF_PALETTE"},
    {CF_PENDATA, L"CF_PENDATA"},
    {CF_RIFF, L"CF_RIFF"},
    {CF_WAVE, L"CF_WAVE"},
    {CF_UNICODETEXT, L"CF_UNICODETEXT"},
    {CF_ENHMETAFILE, L"CF_ENHMETAFILE"},
    {CF_HDROP, L"CF_HDROP"},
    {CF_LOCALE, L"CF_LOCALE"},
    {CF_DIBV5, L"CF_DIBV5"},
    {CF_OWNERDISPLAY, L"CF_OWNERDISPLAY"},
    {CF_DSPTEXT, L"CF_DSPTEXT"},
    {CF_DSPBITMAP, L"CF_DSPBITMAP"},
    {CF_DSPMETAFILEPICT, L"CF_DSPMETAFILEPICT"},
    {CF_DSPENHMETAFILE, L"CF_DSPENHMETAFILE"},
};

std::wstring FormatNameFromId(UINT cf) {
    for (const auto& f : kCapStdFormats)
        if (f.cf == cf) return f.name;
    if (!cf) return {};
    WCHAR name[256];
    int n = GetClipboardFormatNameW(cf, name, ARRAYSIZE(name));
    return n > 0 ? std::wstring(name, n) : std::wstring();
}

UINT FormatIdFromName(const std::wstring& name) {
    if (name.empty()) return 0;
    for (const auto& f : kCapStdFormats)
        if (name == f.name) return f.cf;
    return RegisterClipboardFormatW(name.c_str());
}

static UINT Cap_OwnFormat() {
    static UINT cf = RegisterClipboardFormatW(kOwnClipFormat);
    return cf;
}

// ---------------------------------------------------------------------------
// Deciding what to save. Pure: works on formats already read, so the harness
// can feed it synthetic data.
// ---------------------------------------------------------------------------
struct Cap_Format {
    UINT cf = 0;
    std::wstring name;
    std::string data;   // Empty when the reader skipped it for size.
    size_t size = 0;    // GlobalSize on the clipboard.
};

// Ditto's default Types list when its Types table is empty (CP_Main.cpp LoadTypesFromDB), in its order.
static const wchar_t* const kCapWanted[] = {L"CF_TEXT",  L"Rich Text Format", L"CF_UNICODETEXT", L"CF_HDROP",
                                           L"CF_DIB",   L"HTML Format",      L"PNG"};
static const wchar_t kCapIgnoreViewer[] = L"Clipboard Viewer Ignore";
static const wchar_t kCapExcludeMonitor[] = L"ExcludeClipboardContentFromMonitorProcessing";
static const wchar_t kCapCanInclude[] = L"CanIncludeInClipboardHistory";

enum class Cap_Verdict { Save, OwnClip, Private, AppFiltered, TooBig, NothingWanted };

static bool Cap_FormatAllowed(const std::wstring& name, const Settings& s) {
    if (name == L"CF_DIB" || name == L"CF_DIBV5" || name == L"PNG") return s.saveImages;
    if (name == L"CF_HDROP") return s.saveFiles;
    if (name == L"HTML Format" || name == L"Rich Text Format") return s.saveRichText;
    return true;
}

static std::wstring Cap_Lower(std::wstring s) {
    if (!s.empty()) CharLowerBuffW(s.data(), (DWORD)s.size());
    return s;
}

static bool Cap_AppAllowed(const std::wstring& app, const Settings& s) {
    std::wstring name = Cap_Lower(app);
    bool included = s.includeApps.empty() || s.includeApps == L"*" || WildcardMatchList(name, s.includeApps);
    if (!included) return false;
    return name.empty() || s.excludeApps.empty() || !WildcardMatchList(name, s.excludeApps);
}

// Text up to the first NUL (Ditto builds a CString then stores it as a C string).
static std::wstring Cap_WideFromBytes(const std::string& data) {
    size_t chars = data.size() / sizeof(wchar_t);
    const wchar_t* p = reinterpret_cast<const wchar_t*>(data.data());
    return std::wstring(p, wcsnlen(p, chars));
}

static std::wstring Cap_AnsiFromBytes(const std::string& data) {
    size_t n = strnlen(data.data(), data.size());
    if (!n) return {};
    int len = MultiByteToWideChar(CP_ACP, 0, data.data(), (int)n, nullptr, 0);
    std::wstring out(len, L'\0');
    MultiByteToWideChar(CP_ACP, 0, data.data(), (int)n, out.data(), len);
    return out;
}

// File paths from a DROPFILES block.
static std::vector<std::wstring> Cap_ParseHdrop(const std::string& data) {
    std::vector<std::wstring> files;
    if (data.size() < sizeof(DROPFILES)) return files;
    DROPFILES df;
    memcpy(&df, data.data(), sizeof(df));
    if (df.pFiles >= data.size()) return files;
    std::string rest = data.substr(df.pFiles);
    if (df.fWide) {
        const wchar_t* p = reinterpret_cast<const wchar_t*>(rest.data());
        size_t left = rest.size() / sizeof(wchar_t);
        while (left && *p) {
            size_t n = wcsnlen(p, left);
            files.emplace_back(p, n);
            if (n >= left) break;
            p += n + 1;
            left -= n + 1;
        }
    } else {
        size_t pos = 0;
        while (pos < rest.size() && rest[pos]) {
            size_t n = strnlen(rest.data() + pos, rest.size() - pos);
            files.push_back(Cap_AnsiFromBytes(rest.substr(pos, n)));
            pos += n + 1;
        }
    }
    return files;
}

// Ditto Clip.cpp SetDescFromType: files list (at most 5), else the first saved format's name.
static std::wstring Cap_DescFromType(const std::vector<ClipFormat>& formats) {
    for (const auto& f : formats) {
        if (f.name != L"CF_HDROP") continue;
        auto files = Cap_ParseHdrop(f.data);
        if (files.size() > 5) files.resize(5);
        std::wstring desc = files.size() > 1 ? L"Copied Files - " : L"Copied File - ";
        for (const auto& file : files) {
            std::wstring name = file.empty() || file.back() == L'\\' ? L"" : PathFindFileNameW(file.c_str());
            desc += name + L" - " + file + L"\n";
        }
        return desc;
    }
    return formats.empty() ? L"" : formats[0].name;
}

static const Cap_Format* Cap_Find(const std::vector<Cap_Format>& in, const wchar_t* name) {
    for (const auto& f : in)
        if (f.name == name) return &f;
    return nullptr;
}

static Cap_Verdict Cap_BuildClip(const std::vector<Cap_Format>& in, const std::wstring& app, const Settings& s,
                                 ClipData& out) {
    out = ClipData{};
    if (Cap_Find(in, kOwnClipFormat)) return Cap_Verdict::OwnClip;
    if (Cap_Find(in, kCapIgnoreViewer) || Cap_Find(in, kCapExcludeMonitor)) return Cap_Verdict::Private;
    if (const Cap_Format* f = Cap_Find(in, kCapCanInclude)) {
        DWORD value = 1;
        if (f->data.size() >= sizeof(DWORD)) memcpy(&value, f->data.data(), sizeof(DWORD));
        if (value == 0) return Cap_Verdict::Private;
    }
    if (!Cap_AppAllowed(app, s)) return Cap_Verdict::AppFiltered;

    uint64_t total = 0;
    for (const wchar_t* name : kCapWanted) {
        const Cap_Format* f = Cap_Find(in, name);
        if (!f || !f->size || !Cap_FormatAllowed(name, s)) continue;
        total += f->size;
        out.formats.push_back(ClipFormat{f->cf ? f->cf : FormatIdFromName(name), name, f->data});
    }
    if (total > (uint64_t)s.maxClipMB * 1024 * 1024) {
        out.formats.clear();
        return Cap_Verdict::TooBig;
    }
    if (out.formats.empty()) return Cap_Verdict::NothingWanted;

    // Ditto Clip.cpp LoadFromClipboard: description from CF_UNICODETEXT, else CF_TEXT, else from type.
    if (const Cap_Format* u = Cap_Find(in, L"CF_UNICODETEXT"); u && !u->data.empty())
        out.description = Cap_WideFromBytes(u->data);
    else if (const Cap_Format* a = Cap_Find(in, L"CF_TEXT"); a && !a->data.empty())
        out.description = Cap_AnsiFromBytes(a->data);
    else
        out.description = Cap_DescFromType(out.formats);
    if (out.description.size() > kCapDescMax) out.description.resize(kCapDescMax);
    out.sourceApp = app;
    return Cap_Verdict::Save;
}

// ---------------------------------------------------------------------------
// Reading the clipboard (must already be open)
// ---------------------------------------------------------------------------
static std::string Cap_GlobalBytes(HANDLE h, size_t size) {
    std::string out;
    if (const void* p = GlobalLock(h)) {
        out.assign(static_cast<const char*>(p), size);
        GlobalUnlock(h);
    }
    return out;
}

static std::vector<Cap_Format> Cap_ReadOpenClipboard(uint64_t limit) {
    std::vector<Cap_Format> out;
    for (const wchar_t* name : {kOwnClipFormat, kCapIgnoreViewer, kCapExcludeMonitor, kCapCanInclude}) {
        UINT cf = RegisterClipboardFormatW(name);
        if (!IsClipboardFormatAvailable(cf)) continue;
        Cap_Format f{cf, name, {}, 0};
        if (HANDLE h = GetClipboardData(cf)) {
            f.size = GlobalSize(h);
            if (f.size <= 64) f.data = Cap_GlobalBytes(h, f.size);
        }
        out.push_back(std::move(f));
    }
    uint64_t total = 0;
    // CF_DIB is listed even when the app only wrote CF_BITMAP: Windows synthesizes it on request.
    for (const wchar_t* name : kCapWanted) {
        UINT cf = FormatIdFromName(name);
        if (!cf || !IsClipboardFormatAvailable(cf)) continue;
        HANDLE h = GetClipboardData(cf);
        if (!h) continue;
        Cap_Format f{cf, name, {}, GlobalSize(h)};
        total += f.size;
        if (total <= limit) f.data = Cap_GlobalBytes(h, f.size);
        out.push_back(std::move(f));
    }
    return out;
}

static std::wstring Cap_OwnerApp() {
    std::wstring app = ProcessNameOfWindow(GetClipboardOwner());
    if (app.empty()) app = ProcessNameOfWindow(GetForegroundWindow());
    return Cap_Lower(app);
}

// ---------------------------------------------------------------------------
// Capture
// ---------------------------------------------------------------------------
static int g_capOpenTries;
static DWORD g_capLastCopyTick;
static bool g_capListening;

void Capture_Start() {
    if (g_msgWnd && !g_capListening) g_capListening = AddClipboardFormatListener(g_msgWnd) != FALSE;
    if (!g_capListening) Wh_Log(L"Could not listen to the clipboard (%lu)", GetLastError());
}

void Capture_Stop() {
    if (g_capListening) RemoveClipboardFormatListener(g_msgWnd);
    g_capListening = false;
    if (g_msgWnd) {
        KillTimer(g_msgWnd, kTimerCaptureDebounce);
        KillTimer(g_msgWnd, kTimerPasteStep);
    }
}

void Capture_OnClipboardUpdate() {
    if (g_capturePaused || g_stopping) return;
    g_capOpenTries = 0;
    SetTimer(g_msgWnd, kTimerCaptureDebounce, kCapDebounceMs, nullptr);  // Re-arming restarts the wait.
}

static void Cap_ProcessClipboard() {
    KillTimer(g_msgWnd, kTimerCaptureDebounce);
    if (g_capturePaused || g_stopping) return;
    if (IsClipboardFormatAvailable(Cap_OwnFormat())) return;

    std::wstring app = Cap_OwnerApp();
    if (!Cap_AppAllowed(app, g_set)) {
        Wh_Log(L"Not saving a copy from %s (app filter)", app.c_str());
        return;
    }
    // Ditto ClipboardViewer.cpp OnTimer: copies closer than SaveClipDelay to the last one are dropped.
    DWORD now = GetTickCount();
    if (g_capLastCopyTick && now - g_capLastCopyTick < kCapTooFastMs) {
        Wh_Log(L"Copy came too fast after the last one (%lu ms), skipped", now - g_capLastCopyTick);
        return;
    }
    if (!OpenClipboard(g_msgWnd)) {
        if (++g_capOpenTries <= kCapOpenRetries)
            SetTimer(g_msgWnd, kTimerCaptureDebounce, kCapOpenRetryMs, nullptr);
        else
            Wh_Log(L"Clipboard stayed busy, copy skipped");
        return;
    }
    uint64_t limit = (uint64_t)g_set.maxClipMB * 1024 * 1024;
    std::vector<Cap_Format> formats = Cap_ReadOpenClipboard(limit);
    CloseClipboard();

    ClipData clip;
    Cap_Verdict v = Cap_BuildClip(formats, app, g_set, clip);
    if (v == Cap_Verdict::OwnClip || v == Cap_Verdict::Private || v == Cap_Verdict::AppFiltered) return;
    g_capLastCopyTick = now;
    if (v == Cap_Verdict::TooBig) {
        Wh_Log(L"Copy is larger than %d MB, skipped", g_set.maxClipMB);
        return;
    }
    if (v != Cap_Verdict::Save) return;
    int64_t id = Db_SaveClip(clip);
    if (id)
        PostMessageW(g_msgWnd, WM_SCM_CLIP_SAVED, 0, (LPARAM)id);
    else
        Wh_Log(L"Saving the copy failed: %s", Db_LastError().c_str());
}

// ---------------------------------------------------------------------------
// Special paste (Ditto OleClipSource.cpp)
// ---------------------------------------------------------------------------
static wchar_t Cap_UpperCh(wchar_t c) {
    CharUpperBuffW(&c, 1);
    return c;
}
static wchar_t Cap_LowerCh(wchar_t c) {
    CharLowerBuffW(&c, 1);
    return c;
}
static std::wstring Cap_UpperStr(std::wstring s) {
    if (!s.empty()) CharUpperBuffW(s.data(), (DWORD)s.size());
    return s;
}

static void Cap_ReplaceAll(std::wstring& s, const std::wstring& from, const std::wstring& to) {
    for (size_t pos = 0; (pos = s.find(from, pos)) != std::wstring::npos; pos += to.size())
        s.replace(pos, from.size(), to);
}

// Ditto Slugify.h character map (first entry wins for repeats, as in its unordered_map).
static const std::unordered_map<wchar_t, std::wstring>& Cap_SlugMap() {
    static const std::unordered_map<wchar_t, std::wstring> map = [] {
        static const struct { wchar_t c; const wchar_t* to; } table[] = {
            // latin
            {L'\u00C0', L"A"}, {L'\u00C1', L"A"}, {L'\u00C2', L"A"}, {L'\u00C3', L"A"}, {L'\u00C4', L"A"}, {L'\u00C5', L"A"}, {L'\u00C6', L"AE"},
            {L'\u00C7', L"C"}, {L'\u00C8', L"E"}, {L'\u00C9', L"E"}, {L'\u00CA', L"E"}, {L'\u00CB', L"E"}, {L'\u00CC', L"I"}, {L'\u00CD', L"I"},
            {L'\u00CE', L"I"}, {L'\u00CF', L"I"}, {L'\u00D0', L"D"}, {L'\u00D1', L"N"}, {L'\u00D2', L"O"}, {L'\u00D3', L"O"}, {L'\u00D4', L"O"},
            {L'\u00D5', L"O"}, {L'\u00D6', L"O"}, {L'\u0150', L"O"}, {L'\u00D8', L"O"}, {L'\u00D9', L"U"}, {L'\u00DA', L"U"}, {L'\u00DB', L"U"},
            {L'\u00DC', L"U"}, {L'\u0170', L"U"}, {L'\u00DD', L"Y"}, {L'\u00DE', L"TH"}, {L'\u00DF', L"ss"}, {L'\u00E0', L"a"}, {L'\u00E1', L"a"},
            {L'\u00E2', L"a"}, {L'\u00E3', L"a"}, {L'\u00E4', L"a"}, {L'\u00E5', L"a"}, {L'\u00E6', L"ae"}, {L'\u00E7', L"c"}, {L'\u00E8', L"e"},
            {L'\u00E9', L"e"}, {L'\u00EA', L"e"}, {L'\u00EB', L"e"}, {L'\u00EC', L"i"}, {L'\u00ED', L"i"}, {L'\u00EE', L"i"}, {L'\u00EF', L"i"},
            {L'\u00F0', L"d"}, {L'\u00F1', L"n"}, {L'\u00F2', L"o"}, {L'\u00F3', L"o"}, {L'\u00F4', L"o"}, {L'\u00F5', L"o"}, {L'\u00F6', L"o"},
            {L'\u0151', L"o"}, {L'\u00F8', L"o"}, {L'\u00F9', L"u"}, {L'\u00FA', L"u"}, {L'\u00FB', L"u"}, {L'\u00FC', L"u"}, {L'\u0171', L"u"},
            {L'\u00FD', L"y"}, {L'\u00FE', L"th"}, {L'\u00FF', L"y"}, {L'\u1E9E', L"SS"},
            // greek
            {L'\u03B1', L"a"}, {L'\u03B2', L"b"}, {L'\u03B3', L"g"}, {L'\u03B4', L"d"}, {L'\u03B5', L"e"}, {L'\u03B6', L"z"}, {L'\u03B7', L"h"},
            {L'\u03B8', L"8"}, {L'\u03B9', L"i"}, {L'\u03BA', L"k"}, {L'\u03BB', L"l"}, {L'\u03BC', L"m"}, {L'\u03BD', L"n"}, {L'\u03BE', L"3"},
            {L'\u03BF', L"o"}, {L'\u03C0', L"p"}, {L'\u03C1', L"r"}, {L'\u03C3', L"s"}, {L'\u03C4', L"t"}, {L'\u03C5', L"y"}, {L'\u03C6', L"f"},
            {L'\u03C7', L"x"}, {L'\u03C8', L"ps"}, {L'\u03C9', L"w"}, {L'\u03AC', L"a"}, {L'\u03AD', L"e"}, {L'\u03AF', L"i"}, {L'\u03CC', L"o"},
            {L'\u03CD', L"y"}, {L'\u03AE', L"h"}, {L'\u03CE', L"w"}, {L'\u03C2', L"s"}, {L'\u03CA', L"i"}, {L'\u03B0', L"y"}, {L'\u03CB', L"y"},
            {L'\u0390', L"i"}, {L'\u0391', L"A"}, {L'\u0392', L"B"}, {L'\u0393', L"G"}, {L'\u0394', L"D"}, {L'\u0395', L"E"}, {L'\u0396', L"Z"},
            {L'\u0397', L"H"}, {L'\u0398', L"8"}, {L'\u0399', L"I"}, {L'\u039A', L"K"}, {L'\u039B', L"L"}, {L'\u039C', L"M"}, {L'\u039D', L"N"},
            {L'\u039E', L"3"}, {L'\u039F', L"O"}, {L'\u03A0', L"P"}, {L'\u03A1', L"R"}, {L'\u03A3', L"S"}, {L'\u03A4', L"T"}, {L'\u03A5', L"Y"},
            {L'\u03A6', L"F"}, {L'\u03A7', L"X"}, {L'\u03A8', L"PS"}, {L'\u03A9', L"W"}, {L'\u0386', L"A"}, {L'\u0388', L"E"}, {L'\u038A', L"I"},
            {L'\u038C', L"O"}, {L'\u038E', L"Y"}, {L'\u0389', L"H"}, {L'\u038F', L"W"}, {L'\u03AA', L"I"}, {L'\u03AB', L"Y"},
            // turkish
            {L'\u015F', L"s"}, {L'\u015E', L"S"}, {L'\u0131', L"i"}, {L'\u0130', L"I"}, {L'\u011F', L"g"}, {L'\u011E', L"G"},
            // russian
            {L'\u0430', L"a"}, {L'\u0431', L"b"}, {L'\u0432', L"v"}, {L'\u0433', L"g"}, {L'\u0434', L"d"}, {L'\u0435', L"e"}, {L'\u0451', L"yo"},
            {L'\u0436', L"zh"}, {L'\u0437', L"z"}, {L'\u0438', L"i"}, {L'\u0439', L"j"}, {L'\u043A', L"k"}, {L'\u043B', L"l"}, {L'\u043C', L"m"},
            {L'\u043D', L"n"}, {L'\u043E', L"o"}, {L'\u043F', L"p"}, {L'\u0440', L"r"}, {L'\u0441', L"s"}, {L'\u0442', L"t"}, {L'\u0443', L"u"},
            {L'\u0444', L"f"}, {L'\u0445', L"h"}, {L'\u0446', L"c"}, {L'\u0447', L"ch"}, {L'\u0448', L"sh"}, {L'\u0449', L"sh"}, {L'\u044A', L"u"},
            {L'\u044B', L"y"}, {L'\u044C', L""}, {L'\u044D', L"e"}, {L'\u044E', L"yu"}, {L'\u044F', L"ya"}, {L'\u0410', L"A"}, {L'\u0411', L"B"},
            {L'\u0412', L"V"}, {L'\u0413', L"G"}, {L'\u0414', L"D"}, {L'\u0415', L"E"}, {L'\u0401', L"Yo"}, {L'\u0416', L"Zh"}, {L'\u0417', L"Z"},
            {L'\u0418', L"I"}, {L'\u0419', L"J"}, {L'\u041A', L"K"}, {L'\u041B', L"L"}, {L'\u041C', L"M"}, {L'\u041D', L"N"}, {L'\u041E', L"O"},
            {L'\u041F', L"P"}, {L'\u0420', L"R"}, {L'\u0421', L"S"}, {L'\u0422', L"T"}, {L'\u0423', L"U"}, {L'\u0424', L"F"}, {L'\u0425', L"H"},
            {L'\u0426', L"C"}, {L'\u0427', L"Ch"}, {L'\u0428', L"Sh"}, {L'\u0429', L"Sh"}, {L'\u042A', L"U"}, {L'\u042B', L"Y"}, {L'\u042C', L""},
            {L'\u042D', L"E"}, {L'\u042E', L"Yu"}, {L'\u042F', L"Ya"},
            // ukrainian
            {L'\u0404', L"Ye"}, {L'\u0406', L"I"}, {L'\u0407', L"Yi"}, {L'\u0490', L"G"}, {L'\u0454', L"ye"}, {L'\u0456', L"i"}, {L'\u0457', L"yi"},
            {L'\u0491', L"g"},
            // czech
            {L'\u010D', L"c"}, {L'\u010F', L"d"}, {L'\u011B', L"e"}, {L'\u0148', L"n"}, {L'\u0159', L"r"}, {L'\u0161', L"s"}, {L'\u0165', L"t"},
            {L'\u016F', L"u"}, {L'\u017E', L"z"}, {L'\u010C', L"C"}, {L'\u010E', L"D"}, {L'\u011A', L"E"}, {L'\u0147', L"N"}, {L'\u0158', L"R"},
            {L'\u0160', L"S"}, {L'\u0164', L"T"}, {L'\u016E', L"U"}, {L'\u017D', L"Z"},
            // polish
            {L'\u0105', L"a"}, {L'\u0107', L"c"}, {L'\u0119', L"e"}, {L'\u0142', L"l"}, {L'\u0144', L"n"}, {L'\u015B', L"s"}, {L'\u017A', L"z"},
            {L'\u017C', L"z"}, {L'\u0104', L"A"}, {L'\u0106', L"C"}, {L'\u0118', L"e"}, {L'\u0141', L"L"}, {L'\u0143', L"N"}, {L'\u015A', L"S"},
            {L'\u0179', L"Z"}, {L'\u017B', L"Z"},
            // latvian
            {L'\u0101', L"a"}, {L'\u0113', L"e"}, {L'\u0123', L"g"}, {L'\u012B', L"i"}, {L'\u0137', L"k"}, {L'\u013C', L"l"}, {L'\u0146', L"n"},
            {L'\u016B', L"u"}, {L'\u0100', L"A"}, {L'\u0112', L"E"}, {L'\u0122', L"G"}, {L'\u012A', L"i"}, {L'\u0136', L"k"}, {L'\u013B', L"L"},
            {L'\u0145', L"N"}, {L'\u016A', L"u"},
            // currency
            {L'\u20AC', L"euro"}, {L'\u20A2', L"cruzeiro"}, {L'\u20A3', L"french franc"}, {L'\u00A3', L"pound"}, {L'\u20A4', L"lira"},
            {L'\u20A5', L"mill"}, {L'\u20A6', L"naira"}, {L'\u20A7', L"peseta"}, {L'\u20A8', L"rupee"}, {L'\u20A9', L"won"},
            {L'\u20AA', L"new shequel"}, {L'\u20AB', L"dong"}, {L'\u20AD', L"kip"}, {L'\u20AE', L"tugrik"}, {L'\u20AF', L"drachma"},
            {L'\u20B0', L"penny"}, {L'\u20B1', L"peso"}, {L'\u20B2', L"guarani"}, {L'\u20B3', L"austral"}, {L'\u20B4', L"hryvnia"},
            {L'\u20B5', L"cedi"}, {L'\u00A2', L"cent"}, {L'\u00A5', L"yen"}, {L'\u5143', L"yuan"}, {L'\u5186', L"yen"}, {L'\uFDFC', L"rial"},
            {L'\u20A0', L"ecu"}, {L'\u00A4', L"currency"}, {L'\u0E3F', L"baht"}, {L'$', L"dollar"},
            // symbols
            {L'\u00A9', L"(c)"}, {L'\u0153', L"oe"}, {L'\u0152', L"OE"}, {L'\u2211', L"sum"}, {L'\u00AE', L"(r)"}, {L'\u2020', L"+"},
            {L'\u201C', L"\""}, {L'\u2202', L"d"}, {L'\u0192', L"f"}, {L'\u2122', L"tm"}, {L'\u2120', L"sm"}, {L'\u2026', L"..."},
            {L'\u02DA', L"o"}, {L'\u00BA', L"o"}, {L'\u00AA', L"a"}, {L'\u2022', L"*"}, {L'\u2206', L"delta"}, {L'\u221E', L"infinity"},
            {L'\u2665', L"love"}, {L'&', L"and"}, {L'|', L"or"}, {L'<', L"less"}, {L'>', L"greater"},
        };
        std::unordered_map<wchar_t, std::wstring> m;
        for (const auto& e : table) m.emplace(e.c, e.to);
        return m;
    }();
    return map;
}

// Ditto Slugify.h with separator "-". Its trim() result is discarded there, so
// leading/trailing spaces become separators; kept as is.
static std::wstring Cap_Slugify(const std::wstring& input) {
    const auto& map = Cap_SlugMap();
    std::wstring s;
    for (wchar_t c : input) {
        auto it = map.find(c);
        if (it != map.end())
            s += it->second;
        else
            s += c;
    }
    std::wstring kept;
    for (wchar_t c : s) {
        if (c >= L'A' && c <= L'Z') c = c - L'A' + L'a';
        if ((c >= L'a' && c <= L'z') || (c >= L'0' && c <= L'9') || c == L'-' || iswspace(c)) kept += c;
    }
    std::wstring out;
    for (size_t i = 0; i < kept.size();) {
        if (kept[i] == L'-' || iswspace(kept[i])) {
            while (i < kept.size() && (kept[i] == L'-' || iswspace(kept[i]))) i++;
            out += L'-';
        } else {
            out += kept[i++];
        }
    }
    return out;
}

static std::wstring Cap_Typoglycemia(const std::wstring& text) {
    static std::mt19937 rng{std::random_device{}()};
    std::wstring out;
    size_t pos = 0;
    while (true) {
        while (pos < text.size() && text[pos] == L' ') pos++;  // Ditto's tokenizer skips repeated separators.
        if (pos >= text.size()) break;
        size_t endPos = text.find(L' ', pos);
        if (endPos == std::wstring::npos) endPos = text.size();
        std::wstring word = text.substr(pos, endPos - pos);
        pos = endPos;
        int end = (int)word.size();
        while (end > 0 && (word[end - 1] == L'.' || word[end - 1] == L'!' || word[end - 1] == L'?')) end--;
        if (word.size() > 3 && end > 3) {
            std::uniform_int_distribution<int> dist(1, end - 2);
            for (int i = 1; i < end - 1; i++) std::swap(word[i], word[dist(rng)]);
        }
        out += word;
        out += L' ';
    }
    return out;
}

std::wstring ApplySpecialPaste(const std::wstring& text, SpecialPaste mode) {
    std::wstring s = text;
    switch (mode) {
        case SpecialPaste::None:
        case SpecialPaste::PlainText:
            return s;
        case SpecialPaste::Upper:
            return Cap_UpperStr(s);
        case SpecialPaste::Lower:
            return Cap_Lower(s);
        case SpecialPaste::Capitalize: {
            s = Cap_Lower(s);
            if (s.empty()) return s;
            s[0] = Cap_UpperCh(s[0]);
            bool cap = false;
            for (size_t i = 1; i < s.size(); i++) {
                if (s[i] == L' ') {
                    cap = true;
                } else if (cap) {
                    s[i] = Cap_UpperCh(s[i]);
                    cap = false;
                }
            }
            return s;
        }
        case SpecialPaste::Sentence: {
            s = Cap_Lower(s);
            if (s.empty()) return s;
            s[0] = Cap_UpperCh(s[0]);
            bool cap = false;
            for (size_t i = 1; i < s.size(); i++) {
                if (s[i] == L'.' || s[i] == L'!' || s[i] == L'?') {
                    cap = true;
                } else if (cap && s[i] != L' ') {
                    s[i] = Cap_UpperCh(s[i]);
                    cap = false;
                }
            }
            return s;
        }
        case SpecialPaste::InvertCase:
            for (auto& c : s) c = IsCharUpperW(c) ? Cap_LowerCh(c) : Cap_UpperCh(c);
            return s;
        case SpecialPaste::CamelCase: {
            bool cap = false;
            for (size_t i = 0; i < s.size(); i++) {
                if (s[i] == L' ') {
                    cap = true;
                } else if (cap || i == 0) {
                    s[i] = Cap_UpperCh(s[i]);
                    cap = false;
                } else if (IsCharUpperW(s[i])) {
                    s[i] = Cap_LowerCh(s[i]);
                }
            }
            s.erase(std::remove(s.begin(), s.end(), L' '), s.end());
            return s;
        }
        case SpecialPaste::Slugify:
            return Cap_Slugify(s);
        case SpecialPaste::TrimWhitespace: {
            size_t a = 0, b = s.size();
            while (a < b && iswspace(s[a])) a++;
            while (b > a && iswspace(s[b - 1])) b--;
            return s.substr(a, b - a);
        }
        case SpecialPaste::RemoveLineBreaks:
            Cap_ReplaceAll(s, L"\r\n", L" ");
            Cap_ReplaceAll(s, L"\r", L" ");
            Cap_ReplaceAll(s, L"\n", L" ");
            return s;
        case SpecialPaste::AddLineBreak:
            return s + L"\r\n";
        case SpecialPaste::AddTwoLineBreaks:
            return s + L"\r\n\r\n";
        case SpecialPaste::Typoglycemia:
            return Cap_Typoglycemia(s);
        case SpecialPaste::AsciiOnly:
            s.erase(std::remove_if(s.begin(), s.end(), [](wchar_t c) { return c > 0x7F; }), s.end());
            return s;
    }
    return s;
}

// ---------------------------------------------------------------------------
// Writing the clipboard
// ---------------------------------------------------------------------------
static bool Cap_OpenClipboardQuick() {
    for (int i = 0; i < 5; i++) {
        if (OpenClipboard(g_msgWnd)) return true;
        Sleep(10);
    }
    return false;
}

static bool Cap_SetBytes(UINT cf, const void* data, size_t size) {
    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, size ? size : 1);
    if (!h) return false;
    if (void* p = GlobalLock(h)) {
        if (size) memcpy(p, data, size);
        GlobalUnlock(h);
    }
    if (!SetClipboardData(cf, h)) {
        GlobalFree(h);
        return false;
    }
    return true;
}

static bool Cap_WriteFormats(const std::vector<ClipFormat>& formats) {
    if (formats.empty()) return false;
    if (!Cap_OpenClipboardQuick()) {
        Wh_Log(L"Clipboard is busy, could not put the clip on it");
        return false;
    }
    EmptyClipboard();
    int written = 0;
    for (const auto& f : formats) {
        UINT cf = f.cf ? f.cf : FormatIdFromName(f.name);
        if (!cf || cf == CF_BITMAP || cf == CF_ENHMETAFILE || cf == CF_METAFILEPICT || cf == CF_PALETTE) continue;
        if (Cap_SetBytes(cf, f.data.data(), f.data.size())) written++;
    }
    BYTE marker = 1;
    Cap_SetBytes(Cap_OwnFormat(), &marker, 1);
    CloseClipboard();
    return written > 0;
}

static bool Cap_WriteText(const std::wstring& text) {
    ClipFormat f{CF_UNICODETEXT, L"CF_UNICODETEXT", {}};
    f.data.assign(reinterpret_cast<const char*>(text.c_str()), (text.size() + 1) * sizeof(wchar_t));
    return Cap_WriteFormats({f});
}

static std::wstring Cap_Separator(const std::wstring& setting) {
    if (setting == L"space") return L" ";
    if (setting == L"comma") return L", ";
    if (setting == L"none") return L"";
    return L"\r\n";
}

static std::wstring Cap_Join(const std::vector<std::wstring>& parts, const std::wstring& sep) {
    std::wstring out;
    for (size_t i = 0; i < parts.size(); i++) out += (i ? sep : L"") + parts[i];
    return out;
}

static bool Cap_PutClips(const std::vector<int64_t>& ids, SpecialPaste mode) {
    if (ids.empty()) return false;
    if (ids.size() == 1 && mode == SpecialPaste::None) {
        ClipData data;
        if (Db_GetClipData(ids[0], data) && !data.formats.empty()) {
            for (auto& f : data.formats) f.cf = FormatIdFromName(f.name);
            return Cap_WriteFormats(data.formats);
        }
    }
    // Text only. Image-only clips and groups have no text to give (Ditto's text aggregators skip them).
    std::vector<std::wstring> texts;
    for (int64_t id : ids) {
        ClipRow row;
        if (Db_GetClipRow(id, row) && (row.isGroup || row.kind == ClipKind::Image)) continue;
        texts.push_back(Db_GetClipText(id));
    }
    if (texts.empty()) return false;
    return Cap_WriteText(ApplySpecialPaste(Cap_Join(texts, Cap_Separator(g_set.multiSeparator)), mode));
}

bool Clipboard_PutClip(int64_t id, SpecialPaste mode) { return Cap_PutClips({id}, mode); }

// ---------------------------------------------------------------------------
// Paste step machine on kTimerPasteStep (10 ms ticks, never blocks)
// Ditto ExternalWindowTracker::SendPaste: activate, wait for it, delay, send keys.
// ---------------------------------------------------------------------------
enum class Cap_Stage { Idle, WaitFocus, Delay, WaitKeys };
static struct {
    Cap_Stage stage = Cap_Stage::Idle;
    HWND target = nullptr;
    DWORD since = 0;
} g_capPaste;

static bool Cap_ModifiersDown() {
    for (int vk : {VK_CONTROL, VK_SHIFT, VK_MENU, VK_LWIN, VK_RWIN})
        if (GetAsyncKeyState(vk) & 0x8000) return true;
    return false;
}

static void Cap_Activate(HWND target) {
    if (IsIconic(target)) ShowWindow(target, SW_RESTORE);
    if (SetForegroundWindow(target) && GetForegroundWindow() == target) return;
    DWORD fgThread = GetWindowThreadProcessId(GetForegroundWindow(), nullptr);
    DWORD me = GetCurrentThreadId();
    bool attached = fgThread && fgThread != me && AttachThreadInput(fgThread, me, TRUE);
    BringWindowToTop(target);
    SetForegroundWindow(target);
    if (attached) AttachThreadInput(fgThread, me, FALSE);
}

// Only Ctrl/Shift and V/Insert; a Win key is never injected (a lone Win up opens Start).
static void Cap_SendPasteKeys() {
    bool shiftInsert = g_set.pasteKeys == L"shiftInsert";
    WORD mod = shiftInsert ? VK_SHIFT : VK_CONTROL;
    WORD key = shiftInsert ? VK_INSERT : 'V';
    DWORD keyExt = shiftInsert ? KEYEVENTF_EXTENDEDKEY : 0;
    INPUT in[4]{};
    auto set = [](INPUT& i, WORD vk, DWORD flags) {
        i.type = INPUT_KEYBOARD;
        i.ki.wVk = vk;
        i.ki.wScan = (WORD)MapVirtualKeyW(vk, MAPVK_VK_TO_VSC);
        i.ki.dwFlags = flags;
    };
    set(in[0], mod, 0);
    set(in[1], key, keyExt);
    set(in[2], key, keyExt | KEYEVENTF_KEYUP);
    set(in[3], mod, KEYEVENTF_KEYUP);
    if (SendInput(4, in, sizeof(INPUT)) != 4) Wh_Log(L"Sending the paste keys failed (%lu)", GetLastError());
}

static void Cap_PasteStep() {
    DWORD now = GetTickCount();
    auto next = [&](Cap_Stage s) {
        g_capPaste.stage = s;
        g_capPaste.since = now;
    };
    if (g_stopping) g_capPaste.stage = Cap_Stage::Idle;
    switch (g_capPaste.stage) {
        case Cap_Stage::WaitFocus:
            if (!IsWindow(g_capPaste.target) || GetForegroundWindow() == g_capPaste.target || now - g_capPaste.since > 500)
                next(Cap_Stage::Delay);
            break;
        case Cap_Stage::Delay:
            if (now - g_capPaste.since >= (DWORD)g_set.pasteDelay) next(Cap_Stage::WaitKeys);
            break;
        case Cap_Stage::WaitKeys:
            if (!Cap_ModifiersDown() || now - g_capPaste.since > 2000) {
                Cap_SendPasteKeys();
                g_capPaste.stage = Cap_Stage::Idle;
            }
            break;
        case Cap_Stage::Idle:
            break;
    }
    if (g_capPaste.stage == Cap_Stage::Idle) KillTimer(g_msgWnd, kTimerPasteStep);
}

static void Cap_StartPaste(HWND target) {
    if (List_IsVisible()) List_Hide();
    g_capPaste.target = target;
    g_capPaste.since = GetTickCount();
    g_capPaste.stage = Cap_Stage::WaitFocus;
    if (target && IsWindow(target) && GetForegroundWindow() != target) Cap_Activate(target);
    SetTimer(g_msgWnd, kTimerPasteStep, 10, nullptr);
}

bool Paste_Request(const PasteRequest& req) {
    if (req.ids.empty() || !Cap_PutClips(req.ids, req.mode)) return false;
    if (req.moveToTop) {
        for (int64_t id : req.ids) Db_MoveToTop(id);
        PostMessageW(g_msgWnd, WM_SCM_CLIP_SAVED, 0, 0);
    }
    if (req.sendPaste) Cap_StartPaste(req.target);
    return true;
}

// ---------------------------------------------------------------------------
// Focus and caret
// ---------------------------------------------------------------------------
static bool Cap_IsOwnClass(const wchar_t* cls) {
    for (const wchar_t* own : {kMsgClass, kListClass, kSettingsClass, kEditorClass, kPropsClass, kPreviewClass})
        if (!wcscmp(cls, own)) return true;
    return false;
}

static bool Cap_IsOwnWindow(HWND hwnd) {
    if (!hwnd) return false;
    HWND root = GetAncestor(hwnd, GA_ROOT);
    WCHAR cls[128]{};
    GetClassNameW(root ? root : hwnd, cls, ARRAYSIZE(cls));
    if (Cap_IsOwnClass(cls)) return true;
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    return pid == GetCurrentProcessId();  // Our menus and message boxes.
}

HWND Focus_RememberTarget() {
    HWND fg = GetForegroundWindow();
    if (fg && !Cap_IsOwnWindow(fg)) g_pasteTarget = fg;
    return g_pasteTarget;
}

static bool Cap_RectUsable(RECT& r) {
    if (r.bottom <= r.top) return false;
    if (r.right <= r.left) r.right = r.left + 1;
    POINT p{r.left, r.top};
    return MonitorFromPoint(p, MONITOR_DEFAULTTONULL) != nullptr;
}

bool Focus_GetCaretRect(HWND target, RECT& screenRect) {
    if (!target) return false;
    GUITHREADINFO gti{sizeof(gti)};
    DWORD tid = GetWindowThreadProcessId(target, nullptr);
    bool haveGti = tid && GetGUIThreadInfo(tid, &gti);
    if (haveGti && gti.hwndCaret) {
        RECT r = gti.rcCaret;
        MapWindowPoints(gti.hwndCaret, nullptr, reinterpret_cast<POINT*>(&r), 2);
        if (Cap_RectUsable(r)) {
            screenRect = r;
            return true;
        }
    }
    HWND focus = haveGti && gti.hwndFocus ? gti.hwndFocus : target;
    IAccessible* acc = nullptr;
    if (FAILED(AccessibleObjectFromWindow(focus, (DWORD)OBJID_CARET, IID_IAccessible, (void**)&acc)) || !acc)
        return false;
    VARIANT self;
    VariantInit(&self);
    self.vt = VT_I4;
    self.lVal = CHILDID_SELF;
    long x = 0, y = 0, w = 0, h = 0;
    bool ok = SUCCEEDED(acc->accLocation(&x, &y, &w, &h, self));
    acc->Release();
    if (!ok) return false;
    RECT r{x, y, x + w, y + h};
    if (!Cap_RectUsable(r)) return false;
    screenRect = r;
    return true;
}

// ---------------------------------------------------------------------------
// Hotkeys
// ---------------------------------------------------------------------------
struct Cap_KeyName {
    UINT vk;
    const wchar_t* name;
};
// Canonical names first; later entries for the same key are accepted aliases.
static const Cap_KeyName kCapKeyNames[] = {
    {VK_SPACE, L"Space"},   {VK_TAB, L"Tab"},         {VK_RETURN, L"Enter"},   {VK_ESCAPE, L"Esc"},
    {VK_INSERT, L"Insert"}, {VK_DELETE, L"Delete"},   {VK_HOME, L"Home"},      {VK_END, L"End"},
    {VK_PRIOR, L"PageUp"},  {VK_NEXT, L"PageDown"},   {VK_UP, L"Up"},          {VK_DOWN, L"Down"},
    {VK_LEFT, L"Left"},     {VK_RIGHT, L"Right"},     {VK_OEM_3, L"`"},        {VK_OEM_MINUS, L"-"},
    {VK_OEM_PLUS, L"="},    {VK_OEM_4, L"["},         {VK_OEM_6, L"]"},        {VK_OEM_5, L"\\"},
    {VK_OEM_1, L";"},       {VK_OEM_7, L"'"},         {VK_OEM_COMMA, L","},    {VK_OEM_PERIOD, L"."},
    {VK_OEM_2, L"/"},       {VK_RETURN, L"Return"},   {VK_ESCAPE, L"Escape"},  {VK_INSERT, L"Ins"},
    {VK_DELETE, L"Del"},    {VK_PRIOR, L"PgUp"},      {VK_NEXT, L"PgDn"},
};

static std::wstring Cap_Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t");
    if (a == std::wstring::npos) return {};
    return s.substr(a, s.find_last_not_of(L" \t") - a + 1);
}

static UINT Cap_KeyFromName(const std::wstring& n) {
    if (n.size() == 1) {
        wchar_t c = (wchar_t)towupper(n[0]);
        if ((c >= L'A' && c <= L'Z') || (c >= L'0' && c <= L'9')) return c;
    }
    if (n.size() >= 2 && (n[0] == L'F' || n[0] == L'f') && iswdigit(n[1])) {
        int f = _wtoi(n.c_str() + 1);
        if (f >= 1 && f <= 24 && std::to_wstring(f) == n.substr(1)) return VK_F1 + f - 1;
        return 0;
    }
    if (n.size() == 7 && !_wcsnicmp(n.c_str(), L"Numpad", 6) && iswdigit(n[6])) return VK_NUMPAD0 + (n[6] - L'0');
    for (const auto& k : kCapKeyNames)
        if (!_wcsicmp(n.c_str(), k.name)) return k.vk;
    return 0;
}

bool Hotkey_Parse(const std::wstring& text, UINT& mods, UINT& vk) {
    mods = 0;
    vk = 0;
    std::vector<std::wstring> parts;
    size_t start = 0;
    while (true) {
        size_t plus = text.find(L'+', start);
        parts.push_back(Cap_Trim(text.substr(start, plus == std::wstring::npos ? std::wstring::npos : plus - start)));
        if (plus == std::wstring::npos) break;
        start = plus + 1;
    }
    for (size_t i = 0; i + 1 < parts.size(); i++) {
        const wchar_t* p = parts[i].c_str();
        if (!_wcsicmp(p, L"Ctrl") || !_wcsicmp(p, L"Control")) mods |= MOD_CONTROL;
        else if (!_wcsicmp(p, L"Alt")) mods |= MOD_ALT;
        else if (!_wcsicmp(p, L"Shift")) mods |= MOD_SHIFT;
        else if (!_wcsicmp(p, L"Win") || !_wcsicmp(p, L"Windows")) mods |= MOD_WIN;
        else return (mods = 0), false;
    }
    vk = parts.back().empty() ? 0 : Cap_KeyFromName(parts.back());
    if (!vk) mods = 0;
    return vk != 0;
}

std::wstring Hotkey_Format(UINT mods, UINT vk) {
    std::wstring key;
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) key = std::wstring(1, (wchar_t)vk);
    else if (vk >= VK_F1 && vk <= VK_F24) key = L"F" + std::to_wstring(vk - VK_F1 + 1);
    else if (vk >= VK_NUMPAD0 && vk <= VK_NUMPAD9) key = L"Numpad" + std::to_wstring(vk - VK_NUMPAD0);
    else
        for (const auto& k : kCapKeyNames)
            if (k.vk == vk) {
                key = k.name;
                break;
            }
    if (key.empty()) return {};
    std::wstring out;
    if (mods & MOD_CONTROL) out += L"Ctrl+";
    if (mods & MOD_ALT) out += L"Alt+";
    if (mods & MOD_SHIFT) out += L"Shift+";
    if (mods & MOD_WIN) out += L"Win+";
    return out + key;
}

struct Cap_Hotkey {
    int id;
    std::wstring text;
    UINT mods = 0, vk = 0;
    bool bad = false;
    bool registered = false;
};
static std::vector<Cap_Hotkey> g_capHotkeys;

static bool Cap_TryRegisterAll() {
    bool allOk = true;
    for (auto& h : g_capHotkeys) {
        if (h.bad || h.registered) continue;
        h.registered = RegisterHotKey(g_msgWnd, h.id, h.mods | MOD_NOREPEAT, h.vk) != FALSE;
        if (!h.registered) allOk = false;
    }
    return allOk;
}

// ---------------------------------------------------------------------------
// Win+V takeover: Windows clipboard history off and Windows' own Win+V off
// (DisabledHotkeys, read by Explorer when it starts). The mod remembers what it
// changed and puts back only that when the setting is turned off.
// ---------------------------------------------------------------------------
#ifdef SCM_HARNESS
static PCWSTR kCapClipboardKey = L"Software\\SeamlessClipboardManagerHarness\\Clipboard";
static PCWSTR kCapAdvancedKey = L"Software\\SeamlessClipboardManagerHarness\\Advanced";
#else
static PCWSTR kCapClipboardKey = L"Software\\Microsoft\\Clipboard";
static PCWSTR kCapAdvancedKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced";
#endif

static bool Cap_WindowsClipboardHistoryOn() {
    DWORD value = 0, size = sizeof(value);
    return RegGetValueW(HKEY_CURRENT_USER, kCapClipboardKey, L"EnableClipboardHistory", RRF_RT_REG_DWORD, nullptr,
                        &value, &size) == ERROR_SUCCESS &&
           value != 0;
}

static bool Cap_SetClipboardHistory(DWORD value) {
    return RegSetKeyValueW(HKEY_CURRENT_USER, kCapClipboardKey, L"EnableClipboardHistory", REG_DWORD, &value,
                           sizeof(value)) == ERROR_SUCCESS;
}

// Returns false when the value does not exist.
static bool Cap_ReadDisabledHotkeys(std::wstring& out) {
    wchar_t buf[256] = {};
    DWORD size = sizeof(buf) - sizeof(wchar_t);
    out.clear();
    if (RegGetValueW(HKEY_CURRENT_USER, kCapAdvancedKey, L"DisabledHotkeys", RRF_RT_REG_SZ, nullptr, buf, &size) !=
        ERROR_SUCCESS)
        return false;
    out = buf;
    return true;
}

static bool Cap_WriteDisabledHotkeys(const std::wstring& keys) {
    return RegSetKeyValueW(HKEY_CURRENT_USER, kCapAdvancedKey, L"DisabledHotkeys", REG_SZ, keys.c_str(),
                           (DWORD)((keys.size() + 1) * sizeof(wchar_t))) == ERROR_SUCCESS;
}

// State values: winvHistoryRestore 1 = history was on; winvHotkeyRestore 1 = "V" was added
// to an existing value, 2 = the value was created.
static void Cap_ApplyWinVTakeover() {
    if (g_set.takeOverWinV) {
        if (Cap_WindowsClipboardHistoryOn() && Cap_SetClipboardHistory(0)) SetState(L"winvHistoryRestore", 1);
        std::wstring keys;
        bool exists = Cap_ReadDisabledHotkeys(keys);
        if (keys.find_first_of(L"Vv") == std::wstring::npos && Cap_WriteDisabledHotkeys(keys + L"V"))
            SetState(L"winvHotkeyRestore", exists ? 1 : 2);
        return;
    }
    if (GetState(L"winvHistoryRestore", 0) == 1) {
        Cap_SetClipboardHistory(1);
        SetState(L"winvHistoryRestore", 0);
    }
    if (int how = GetState(L"winvHotkeyRestore", 0)) {
        std::wstring keys;
        Cap_ReadDisabledHotkeys(keys);
        size_t at = keys.find_first_of(L"Vv");
        if (at != std::wstring::npos) keys.erase(at, 1);
        if (how == 2 && keys.empty())
            RegDeleteKeyValueW(HKEY_CURRENT_USER, kCapAdvancedKey, L"DisabledHotkeys");
        else
            Cap_WriteDisabledHotkeys(keys);
        SetState(L"winvHotkeyRestore", 0);
    }
}

// Until Explorer restarts it still owns Win+V, so RegisterHotKey fails. Then a
// keyboard hook catches Win+V instead.
static HHOOK g_capWinVHook;
static int g_capWinVHotkeyId;   // 1 or 2 while the hook stands in for that hotkey
static bool g_capWinVHeld;

static LRESULT CALLBACK Cap_WinVHookProc(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION) {
        auto* k = reinterpret_cast<KBDLLHOOKSTRUCT*>(lp);
        if (k->vkCode == 'V' && !(k->flags & LLKHF_INJECTED) && g_capWinVHotkeyId) {
            if (wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN) {
                bool win = ((GetAsyncKeyState(VK_LWIN) | GetAsyncKeyState(VK_RWIN)) & 0x8000) != 0;
                bool other = ((GetAsyncKeyState(VK_CONTROL) | GetAsyncKeyState(VK_MENU) | GetAsyncKeyState(VK_SHIFT)) &
                              0x8000) != 0;
                if (win && !other) {
                    if (!g_capWinVHeld) {
                        // An unused key between Win down and Win up keeps Start from opening.
                        INPUT in[2] = {};
                        in[0].type = in[1].type = INPUT_KEYBOARD;
                        in[0].ki.wVk = in[1].ki.wVk = 0xE8;
                        in[1].ki.dwFlags = KEYEVENTF_KEYUP;
                        SendInput(2, in, sizeof(INPUT));
                        PostMessageW(g_msgWnd, WM_HOTKEY, (WPARAM)g_capWinVHotkeyId, 0);
                    }
                    g_capWinVHeld = true;
                    return 1;
                }
            } else if (g_capWinVHeld) {
                g_capWinVHeld = false;
                return 1;
            }
        }
    }
    return CallNextHookEx(nullptr, code, wp, lp);
}

static void Cap_UpdateWinVHook() {
    int need = 0;
    if (g_set.takeOverWinV)
        for (const auto& h : g_capHotkeys)
            if ((h.id == 1 || h.id == 2) && !h.bad && !h.registered && h.mods == MOD_WIN && h.vk == 'V') need = h.id;
    g_capWinVHotkeyId = need;
#ifndef SCM_HARNESS  // Tests never hook the owner's keyboard.
    if (need && !g_capWinVHook) {
        g_capWinVHook = SetWindowsHookExW(WH_KEYBOARD_LL, Cap_WinVHookProc, g_hInstance, 0);
    } else if (!need && g_capWinVHook) {
        UnhookWindowsHookEx(g_capWinVHook);
        g_capWinVHook = nullptr;
    }
#endif
    g_capWinVHeld = false;
}

void Hotkeys_Register() {
    if (!g_capHotkeys.empty()) Hotkeys_Unregister();
    Cap_ApplyWinVTakeover();
    auto add = [](int id, const std::wstring& text, UINT mods = 0, UINT vk = 0) {
        Cap_Hotkey h{id, Cap_Trim(text)};
        if (vk) {
            h.mods = mods;
            h.vk = vk;
        } else if (h.text.empty()) {
            return;
        } else {
            h.bad = !Hotkey_Parse(h.text, h.mods, h.vk);
        }
        for (const auto& o : g_capHotkeys)
            if (!h.bad && !o.bad && o.mods == h.mods && o.vk == h.vk) return;  // Same key twice: keep the first.
        g_capHotkeys.push_back(h);
    };
    add(1, g_set.hotkey);
    add(2, g_set.hotkey2);
    add(3, g_set.plainTextHotkey);
    UINT posMods = g_set.positionHotkeys == L"ctrlWin"  ? MOD_CONTROL | MOD_WIN
                   : g_set.positionHotkeys == L"ctrlAlt" ? MOD_CONTROL | MOD_ALT
                   : g_set.positionHotkeys == L"altWin"  ? MOD_ALT | MOD_WIN
                                                          : 0;
    if (posMods)
        for (int n = 0; n < 10; n++) add(10 + n, L"", posMods, n == 9 ? '0' : '1' + n);
    if (!Cap_TryRegisterAll()) SetTimer(g_msgWnd, kTimerHotkeyRetry, 5000, nullptr);
    Cap_UpdateWinVHook();
}

void Hotkeys_Unregister() {
    if (g_msgWnd) KillTimer(g_msgWnd, kTimerHotkeyRetry);
    for (auto& h : g_capHotkeys)
        if (h.registered) UnregisterHotKey(g_msgWnd, h.id);
    g_capHotkeys.clear();
    Cap_UpdateWinVHook();
}

std::wstring Hotkeys_Status() {
    std::wstring out;
    auto say = [&](const std::wstring& s) { out += (out.empty() ? L"" : L" ") + s; };
    for (const auto& h : g_capHotkeys) {
        if (h.bad) {
            say(L"\"" + h.text + L"\" is not a key combination this mod understands.");
        } else if (!h.registered && h.id != g_capWinVHotkeyId) {
            if (h.mods == MOD_WIN && h.vk == 'V' && Cap_WindowsClipboardHistoryOn())
                say(L"Turn off Clipboard history in Windows Settings so Win+V opens your clips.");
            else
                say(Hotkey_Format(h.mods, h.vk) + L" is used by another app.");
        }
    }
    return out;
}

static std::wstring Cap_ReadClipboardText() {
    std::wstring text;
    if (!Cap_OpenClipboardQuick()) return text;
    if (HANDLE h = GetClipboardData(CF_UNICODETEXT)) {
        size_t size = GlobalSize(h);
        if (const wchar_t* p = static_cast<const wchar_t*>(GlobalLock(h))) {
            text.assign(p, wcsnlen(p, size / sizeof(wchar_t)));
            GlobalUnlock(h);
        }
    }
    CloseClipboard();
    return text;
}

void Hotkeys_OnHotkey(int id) {
    if (g_stopping) return;
    if (id == 1 || id == 2) {
        List_Toggle();
    } else if (id == 3) {
        HWND target = Focus_RememberTarget();
        std::wstring text = Cap_ReadClipboardText();
        if (!text.empty() && Cap_WriteText(text)) Cap_StartPaste(target);
    } else if (id >= 10 && id <= 19) {
        int64_t clip = Db_ClipIdAtPosition(id - 10);
        if (!clip) return;
        PasteRequest req;
        req.ids = {clip};
        req.mode = SpecialPaste::None;
        req.sendPaste = g_set.positionHotkeysPaste;
        req.moveToTop = g_set.positionHotkeysMoveToTop;
        req.target = Focus_RememberTarget();
        Paste_Request(req);
    }
}

void Capture_OnTimer(UINT_PTR id) {
    if (id == kTimerCaptureDebounce) {
        Cap_ProcessClipboard();
    } else if (id == kTimerPasteStep) {
        Cap_PasteStep();
    } else if (id == kTimerHotkeyRetry) {
        if (Cap_TryRegisterAll()) {
            KillTimer(g_msgWnd, kTimerHotkeyRetry);
            Wh_Log(L"All keys are registered now");
        }
        Cap_UpdateWinVHook();
    }
}

// ---------------------------------------------------------------------------
// Tray icon
// ---------------------------------------------------------------------------
static bool g_capTrayAdded;
static HICON g_capTrayIcon;
enum : UINT { kCapMenuShow = 1, kCapMenuPause, kCapMenuSettings, kCapMenuDeleteAll };

static NOTIFYICONDATAW Cap_TrayData() {
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = g_msgWnd;
    nid.uID = 1;
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_SCM_TRAY;
    std::wstring tip = L"Seamless Clipboard Manager";
    if (g_capturePaused) tip += L" - saving paused";
    wcsncpy_s(nid.szTip, tip.c_str(), _TRUNCATE);
    return nid;
}

static HICON Cap_MakeTrayIcon() {
    UINT dpi = g_msgWnd ? GetDpiForWindow(g_msgWnd) : 0;
    if (!dpi) dpi = GetDpiForSystem();
    return MakeAppIcon(GetSystemMetricsForDpi(SM_CXSMICON, dpi));
}

void Tray_Create() {
    if (g_capTrayAdded || !g_msgWnd) return;
    HICON old = g_capTrayIcon;
    g_capTrayIcon = Cap_MakeTrayIcon();
    NOTIFYICONDATAW nid = Cap_TrayData();
    nid.hIcon = g_capTrayIcon;
    g_capTrayAdded = Shell_NotifyIconW(NIM_ADD, &nid) != FALSE;
    if (g_capTrayAdded) {
        nid.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, &nid);
    }
    if (old) DestroyIcon(old);
}

void Tray_Remove() {
    if (g_capTrayAdded) {
        NOTIFYICONDATAW nid{sizeof(nid)};
        nid.hWnd = g_msgWnd;
        nid.uID = 1;
        Shell_NotifyIconW(NIM_DELETE, &nid);
    }
    g_capTrayAdded = false;
    if (g_capTrayIcon) DestroyIcon(g_capTrayIcon);
    g_capTrayIcon = nullptr;
}

void Tray_Update() {
    if (!g_capTrayAdded) return;
    HICON old = g_capTrayIcon;
    g_capTrayIcon = Cap_MakeTrayIcon();
    NOTIFYICONDATAW nid = Cap_TrayData();
    nid.hIcon = g_capTrayIcon;
    Shell_NotifyIconW(NIM_MODIFY, &nid);
    if (old) DestroyIcon(old);
}

void Tray_OnTaskbarCreated() {
    g_capTrayAdded = false;  // Explorer forgot it.
    Tray_Create();
}

static void Cap_TrayMenu(int x, int y) {
    auto item = [](int id, PCWSTR text, wchar_t glyph, bool checked = false) {
        UiMenuItem m;
        m.id = id;
        m.text = text;
        m.glyph = glyph;
        m.checked = checked;
        return m;
    };
    UiMenuItem sep;
    sep.separator = true;
    std::vector<UiMenuItem> items = {
        item(kCapMenuShow, L"Show clips", 0xE8FD),
        item(kCapMenuPause, L"Pause saving copies", 0xE769, g_capturePaused),
        item(kCapMenuSettings, L"Settings", 0xE713),
        sep,
        item(kCapMenuDeleteAll, L"Delete all clips...", 0xE74D),
    };
    UINT cmd = (UINT)Ui_ShowMenu(items, POINT{x, y}, g_msgWnd);
    PostMessageW(g_msgWnd, WM_NULL, 0, 0);
    switch (cmd) {
        case kCapMenuShow:
            List_Show();
            break;
        case kCapMenuPause:
            g_capturePaused = !g_capturePaused;
            if (g_capturePaused) KillTimer(g_msgWnd, kTimerCaptureDebounce);
            Tray_Update();
            break;
        case kCapMenuSettings:
            Settings_Open();
            break;
        case kCapMenuDeleteAll:
            if (MessageBoxW(g_msgWnd,
                            L"Delete all clips?\n\nPinned clips, groups and clips set to never delete are kept.",
                            L"Seamless Clipboard Manager", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES) {
                if (Db_DeleteAllUnpinned()) PostMessageW(g_msgWnd, WM_SCM_CLIP_SAVED, 0, 0);
            }
            break;
    }
}

void Tray_OnMessage(WPARAM wParam, LPARAM lParam) {
    switch (LOWORD(lParam)) {
        case NIN_SELECT:
        case NIN_KEYSELECT:
            List_Show();
            break;
        case WM_CONTEXTMENU:
            Cap_TrayMenu(GET_X_LPARAM(wParam), GET_Y_LPARAM(wParam));
            break;
    }
}

// ---------------------------------------------------------------------------
// Harness self test: no clipboard writes, no input, no visible windows.
// ---------------------------------------------------------------------------
#ifdef SCM_HARNESS
static int g_capFails;
static void Cap_Check(bool ok, const wchar_t* what) {
    Wh_Log(L"%s %s", ok ? L"PASS" : L"FAIL", what);
    if (!ok) g_capFails++;
}

static Cap_Format Cap_TestText(const std::wstring& t) {
    Cap_Format f{CF_UNICODETEXT, L"CF_UNICODETEXT"};
    f.data.assign(reinterpret_cast<const char*>(t.c_str()), (t.size() + 1) * sizeof(wchar_t));
    f.size = f.data.size();
    return f;
}
static Cap_Format Cap_TestBlob(const wchar_t* name, size_t size, bool withData = true) {
    Cap_Format f{FormatIdFromName(name), name};
    if (withData) f.data.assign(size, 'x');
    f.size = size;
    return f;
}
static Cap_Format Cap_TestDrop(const std::vector<std::wstring>& files) {
    std::wstring list;
    for (const auto& f : files) list += f + L'\0';
    list += L'\0';
    DROPFILES df{};
    df.pFiles = sizeof(df);
    df.fWide = TRUE;
    Cap_Format f{CF_HDROP, L"CF_HDROP"};
    f.data.assign(reinterpret_cast<const char*>(&df), sizeof(df));
    f.data.append(reinterpret_cast<const char*>(list.data()), list.size() * sizeof(wchar_t));
    f.size = f.data.size();
    return f;
}

static std::wstring Cap_Names(const ClipData& c) {
    std::wstring s;
    for (const auto& f : c.formats) s += (s.empty() ? L"" : L",") + f.name;
    return s;
}

int Harness_TestCapture() {
    g_capFails = 0;

    // Hotkeys
    struct { const wchar_t* in; const wchar_t* canon; } goodKeys[] = {
        {L"Win+V", L"Win+V"},
        {L"ctrl+shift+v", L"Ctrl+Shift+V"},
        {L"Shift+Ctrl+V", L"Ctrl+Shift+V"},
        {L"Ctrl+`", L"Ctrl+`"},
        {L"Alt+F1", L"Alt+F1"},
        {L"Ctrl+Alt+Space", L"Ctrl+Alt+Space"},
        {L"Win + Shift + /", L"Shift+Win+/"},
        {L"Control+Numpad7", L"Ctrl+Numpad7"},
        {L"F24", L"F24"},
        {L"Ctrl+Escape", L"Ctrl+Esc"},
        {L"Alt+PgDn", L"Alt+PageDown"},
        {L"Ctrl+\\", L"Ctrl+\\"},
        {L"Ctrl+Win+0", L"Ctrl+Win+0"},
        {L"Ctrl+Alt+Shift+F24", L"Ctrl+Alt+Shift+F24"},
    };
    for (const auto& k : goodKeys) {
        UINT m = 0, vk = 0, m2 = 0, vk2 = 0;
        bool ok = Hotkey_Parse(k.in, m, vk);
        std::wstring f = Hotkey_Format(m, vk);
        bool round = Hotkey_Parse(f, m2, vk2) && m2 == m && vk2 == vk;
        std::wstring what = L"hotkey \"" + std::wstring(k.in) + L"\" -> \"" + f + L"\"";
        Cap_Check(ok && f == k.canon && round, what.c_str());
    }
    {
        UINT m, vk;
        Cap_Check(Hotkey_Parse(L"Ctrl+`", m, vk) && vk == VK_OEM_3 && m == MOD_CONTROL, L"hotkey Ctrl+` is VK_OEM_3");
    }
    for (const wchar_t* bad : {L"", L"Ctrl+", L"Ctrl+Shift", L"Hyper+V", L"Ctrl+VV", L"Ctrl+F25", L"+", L"Ctrl++V",
                               L"Ctrl+F0", L"Ctrl+F01"}) {
        UINT m = 1, vk = 1;
        std::wstring what = L"hotkey rejects \"" + std::wstring(bad) + L"\"";
        Cap_Check(!Hotkey_Parse(bad, m, vk) && m == 0 && vk == 0, what.c_str());
    }

    // Special paste (expected values worked out from Ditto's OleClipSource.cpp / Slugify.h)
    struct { SpecialPaste mode; const wchar_t* in; const wchar_t* out; const wchar_t* name; } sp[] = {
        {SpecialPaste::None, L"Keep Me\r\n", L"Keep Me\r\n", L"none"},
        {SpecialPaste::PlainText, L"Keep Me\r\n", L"Keep Me\r\n", L"plain text"},
        {SpecialPaste::Upper, L"Hello World \u00E9", L"HELLO WORLD \u00C9", L"upper"},
        {SpecialPaste::Lower, L"Hello WORLD \u00C9", L"hello world \u00E9", L"lower"},
        {SpecialPaste::Capitalize, L"hello wORLD  foo.bar\nnext", L"Hello World  Foo.bar\nnext", L"capitalize"},
        {SpecialPaste::Sentence, L"hello. WORLD! is it? yes\nno", L"Hello. World! Is it? Yes\nno", L"sentence"},
        {SpecialPaste::InvertCase, L"Hello World 1", L"hELLO wORLD 1", L"invert case"},
        {SpecialPaste::CamelCase, L"hello big WORLD", L"HelloBigWorld", L"camel case"},
        {SpecialPaste::Slugify, L"H\u00E9llo, W\u00F6rld & Co!", L"hello-world-and-co", L"slugify"},
        {SpecialPaste::Slugify, L"a -- b\t\tc", L"a-b-c", L"slugify runs"},
        {SpecialPaste::Slugify, L" \u041F\u0440\u0438\u0432\u0435\u0442 \u043C\u0438\u0440 ", L"-privet-mir-", L"slugify edges (Ditto keeps them)"},
        {SpecialPaste::TrimWhitespace, L"  \t hi there \r\n", L"hi there", L"trim whitespace"},
        {SpecialPaste::RemoveLineBreaks, L"a\r\nb\nc\rd", L"a b c d", L"remove line breaks"},
        {SpecialPaste::AddLineBreak, L"a", L"a\r\n", L"add line break"},
        {SpecialPaste::AddTwoLineBreaks, L"a", L"a\r\n\r\n", L"add two line breaks"},
        {SpecialPaste::AsciiOnly, L"caf\u00E9 \u2615 ok", L"caf  ok", L"ascii only"},
        {SpecialPaste::Typoglycemia, L"a  to  the", L"a to the ", L"typoglycemia short words"},
    };
    for (const auto& t : sp) {
        std::wstring got = ApplySpecialPaste(t.in, t.mode);
        std::wstring what = std::wstring(L"special paste ") + t.name;
        Cap_Check(got == t.out, what.c_str());
        if (got != t.out) Wh_Log(L"  got [%s]", got.c_str());
    }
    {
        std::wstring in = L"The quick brown foxes jumped!! over";
        std::wstring got = ApplySpecialPaste(in, SpecialPaste::Typoglycemia);
        bool ok = got.size() == in.size() + 1 && got.back() == L' ';
        size_t a = 0, b = 0;
        while (ok && a < in.size()) {
            size_t ea = in.find(L' ', a), eb = got.find(L' ', b);
            if (ea == std::wstring::npos) ea = in.size();
            std::wstring w = in.substr(a, ea - a), g = got.substr(b, eb - b);
            std::wstring core = w;
            while (!core.empty() && (core.back() == L'!' || core.back() == L'.' || core.back() == L'?')) core.pop_back();
            std::wstring sw = w, sg = g;
            std::sort(sw.begin(), sw.end());
            std::sort(sg.begin(), sg.end());
            ok = sw == sg && g[0] == w[0] && g.substr(core.size() - 1) == w.substr(core.size() - 1);
            a = ea + 1;
            b = eb + 1;
        }
        Cap_Check(ok, L"special paste typoglycemia keeps first/last letters and punctuation");
    }

    // Format names
    for (const auto& f : kCapStdFormats) {
        bool ok = FormatIdFromName(f.name) == f.cf && FormatNameFromId(f.cf) == f.name;
        if (!ok) Cap_Check(false, f.name);
    }
    Cap_Check(true, L"format names: every standard name round trips");
    for (const wchar_t* n : {L"HTML Format", L"PNG", L"Rich Text Format", L"SeamlessClipboardManagerTestFormat"}) {
        UINT cf = FormatIdFromName(n);
        std::wstring what = L"format name \"" + std::wstring(n) + L"\" round trips";
        Cap_Check(cf >= 0xC000 && FormatNameFromId(cf) == n && FormatIdFromName(n) == cf, what.c_str());
    }
    Cap_Check(FormatIdFromName(L"") == 0 && FormatNameFromId(0).empty(), L"format name empty and 0");

    // ClipData builder
    Settings s = g_set;
    s.saveImages = s.saveFiles = s.saveRichText = true;
    s.maxClipMB = 64;
    s.includeApps = L"*";
    s.excludeApps = L"";
    ClipData c;
    std::vector<Cap_Format> textIn = {Cap_TestBlob(L"CF_TEXT", 6), Cap_TestText(L"hello"),
                                      Cap_TestBlob(L"HTML Format", 40), Cap_TestBlob(L"CF_LOCALE", 4)};
    Cap_Check(Cap_BuildClip(textIn, L"notepad.exe", s, c) == Cap_Verdict::Save &&
                  Cap_Names(c) == L"CF_TEXT,CF_UNICODETEXT,HTML Format" && c.description == L"hello",
              L"builder: text clip keeps Ditto's formats in Ditto's order");
    s.saveRichText = false;
    Cap_Check(Cap_BuildClip(textIn, L"notepad.exe", s, c) == Cap_Verdict::Save &&
                  Cap_Names(c) == L"CF_TEXT,CF_UNICODETEXT",
              L"builder: formatting off drops HTML Format");
    s.saveRichText = true;
    {
        std::wstring longText(700, L'a');
        longText[3] = L'b';
        ClipData d;
        Cap_BuildClip({Cap_TestText(longText)}, L"", s, d);
        bool lenOk = d.description.size() == 500 && d.description[3] == L'b';
        std::wstring withNul = L"abc";
        withNul += L'\0';
        withNul += L"def";
        Cap_BuildClip({Cap_TestText(withNul)}, L"", s, d);
        Cap_Check(lenOk && d.description == L"abc", L"builder: description cut to 500 characters and at a NUL");
    }
    {
        Cap_Format ansi = Cap_TestBlob(L"CF_TEXT", 0, false);
        ansi.data = std::string("plain ansi\0junk", 15);
        ansi.size = ansi.data.size();
        Cap_Check(Cap_BuildClip({ansi}, L"", s, c) == Cap_Verdict::Save && c.description == L"plain ansi",
                  L"builder: description from CF_TEXT when there is no CF_UNICODETEXT");
    }
    std::vector<Cap_Format> imgIn = {Cap_TestBlob(L"PNG", 100), Cap_TestBlob(L"CF_DIB", 200)};
    Cap_Check(Cap_BuildClip(imgIn, L"", s, c) == Cap_Verdict::Save && Cap_Names(c) == L"CF_DIB,PNG" &&
                  c.description == L"CF_DIB" && c.formats[0].cf == CF_DIB,
              L"builder: image clip described as CF_DIB");
    s.saveImages = false;
    Cap_Check(Cap_BuildClip(imgIn, L"", s, c) == Cap_Verdict::NothingWanted && c.formats.empty(),
              L"builder: images off saves nothing for an image");
    s.saveImages = true;
    std::vector<Cap_Format> dropIn = {Cap_TestDrop({L"C:\\x\\a.txt", L"D:\\y\\b.png"})};
    Cap_Check(Cap_BuildClip(dropIn, L"explorer.exe", s, c) == Cap_Verdict::Save &&
                  c.description == L"Copied Files - a.txt - C:\\x\\a.txt\nb.png - D:\\y\\b.png\n",
              L"builder: copied files description");
    {
        ClipData one;
        Cap_BuildClip({Cap_TestDrop({L"C:\\only.doc"})}, L"", s, one);
        Cap_Check(one.description == L"Copied File - only.doc - C:\\only.doc\n", L"builder: one copied file");
        std::vector<std::wstring> seven;
        for (int i = 0; i < 7; i++) seven.push_back(L"C:\\f" + std::to_wstring(i));
        Cap_BuildClip({Cap_TestDrop(seven)}, L"", s, one);
        Cap_Check(std::count(one.description.begin(), one.description.end(), L'\n') == 5,
                  L"builder: file description lists at most 5 files");
    }
    s.saveFiles = false;
    Cap_Check(Cap_BuildClip(dropIn, L"", s, c) == Cap_Verdict::NothingWanted, L"builder: files off saves nothing");
    s.saveFiles = true;
    s.maxClipMB = 1;
    std::vector<Cap_Format> bigIn = {Cap_TestText(L"x"), Cap_TestBlob(L"CF_DIB", 2 * 1024 * 1024, false)};
    Cap_Check(Cap_BuildClip(bigIn, L"", s, c) == Cap_Verdict::TooBig && c.formats.empty(),
              L"builder: copy over the size limit is skipped");
    s.maxClipMB = 64;
    Cap_Check(Cap_BuildClip({Cap_TestBlob(L"CF_LOCALE", 4), Cap_TestBlob(L"FileName", 10)}, L"", s, c) ==
                  Cap_Verdict::NothingWanted,
              L"builder: nothing saved without a wanted format");
    for (const wchar_t* marker : {kCapIgnoreViewer, kCapExcludeMonitor}) {
        auto in = textIn;
        in.push_back(Cap_TestBlob(marker, 4));
        std::wstring what = L"builder: private marker \"" + std::wstring(marker) + L"\" skips";
        Cap_Check(Cap_BuildClip(in, L"", s, c) == Cap_Verdict::Private, what.c_str());
    }
    {
        auto in = textIn;
        Cap_Format m = Cap_TestBlob(kCapCanInclude, 4);
        m.data.assign(4, '\0');
        in.push_back(m);
        bool zero = Cap_BuildClip(in, L"", s, c) == Cap_Verdict::Private;
        in.back().data = std::string("\1\0\0\0", 4);
        bool one = Cap_BuildClip(in, L"", s, c) == Cap_Verdict::Save;
        Cap_Check(zero && one, L"builder: CanIncludeInClipboardHistory 0 skips, 1 saves");
        in = textIn;
        in.push_back(Cap_TestBlob(kOwnClipFormat, 1));
        Cap_Check(Cap_BuildClip(in, L"", s, c) == Cap_Verdict::OwnClip, L"builder: our own clip is not saved again");
    }
    s.includeApps = L"notepad.exe; code.exe";
    bool incNo = Cap_BuildClip(textIn, L"chrome.exe", s, c) == Cap_Verdict::AppFiltered;
    bool incYes = Cap_BuildClip(textIn, L"Code.exe", s, c) == Cap_Verdict::Save;
    s.includeApps = L"*";
    s.excludeApps = L"KeePass*.exe;1password.exe";
    bool excNo = Cap_BuildClip(textIn, L"KeePassXC.exe", s, c) == Cap_Verdict::AppFiltered;
    bool excYes = Cap_BuildClip(textIn, L"notepad.exe", s, c) == Cap_Verdict::Save;
    bool unknownApp = Cap_BuildClip(textIn, L"", s, c) == Cap_Verdict::Save;
    Cap_Check(incNo && incYes && excNo && excYes && unknownApp, L"builder: include and exclude app lists");

    // Paste text join
    Cap_Check(Cap_Join({L"a", L"b", L"c"}, Cap_Separator(L"comma")) == L"a, b, c" &&
                  Cap_Join({L"a", L"b"}, Cap_Separator(L"newline")) == L"a\r\nb" &&
                  Cap_Join({L"a", L"b"}, Cap_Separator(L"space")) == L"a b" &&
                  Cap_Join({L"a", L"b"}, Cap_Separator(L"none")) == L"ab" && Cap_Join({L"x"}, L", ") == L"x",
              L"paste: several clips joined with the chosen separator");

    // Our windows are never a paste target
    {
        WNDCLASSEXW wc{sizeof(wc)};
        bool registered = false;
        if (!GetClassInfoExW(g_hInstance, kPreviewClass, &wc)) {
            wc = WNDCLASSEXW{sizeof(wc)};
            wc.lpfnWndProc = DefWindowProcW;
            wc.hInstance = g_hInstance;
            wc.lpszClassName = kPreviewClass;
            registered = RegisterClassExW(&wc) != 0;
        }
        HWND own = registered ? CreateWindowExW(WS_EX_TOOLWINDOW, kPreviewClass, L"", WS_POPUP, -32000, -32000, 10,
                                                10, nullptr, nullptr, g_hInstance, nullptr)
                              : nullptr;
        bool classOk = Cap_IsOwnClass(kListClass) && Cap_IsOwnClass(kMsgClass) && !Cap_IsOwnClass(L"Notepad");
        bool ownOk = !registered || (own && Cap_IsOwnWindow(own));
        bool shellOk = !Cap_IsOwnWindow(GetShellWindow());
        g_pasteTarget = nullptr;
        HWND t = Focus_RememberTarget();
        bool targetOk = !t || !Cap_IsOwnWindow(t);
        Cap_Check(classOk && ownOk && shellOk && targetOk && !IsWindowVisible(own),
                  L"focus: our window classes are never the paste target");
        if (own) DestroyWindow(own);
        if (registered) UnregisterClassW(kPreviewClass, g_hInstance);
    }

    // Hotkey registration on a hidden message-only window (never Win+V here)
    {
        HWND saved = g_msgWnd;
        Settings savedSet = g_set;
        g_msgWnd = CreateWindowExW(0, L"STATIC", L"", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, g_hInstance, nullptr);
        UINT busyMods = MOD_CONTROL | MOD_ALT | MOD_SHIFT;
        bool busy = RegisterHotKey(nullptr, 0xBF00, busyMods, VK_F23) != FALSE;  // Stand-in for "another app".
        g_set.hotkey = L"Ctrl+Alt+Shift+F24";
        g_set.hotkey2 = L"Ctrl+Alt+Shift+F23";
        g_set.plainTextHotkey = L"Ctrl+Nope";
        g_set.positionHotkeys = L"off";
        Hotkeys_Register();
        std::wstring status = Hotkeys_Status();
        bool firstOk = g_capHotkeys.size() == 3 && g_capHotkeys[0].registered;
        bool secondFailed = busy && g_capHotkeys.size() > 1 && !g_capHotkeys[1].registered &&
                            status.find(L"Ctrl+Alt+Shift+F23 is used by another app.") != std::wstring::npos;
        bool badReported = status.find(L"\"Ctrl+Nope\" is not a key combination") != std::wstring::npos;
        if (busy) UnregisterHotKey(nullptr, 0xBF00);
        Capture_OnTimer(kTimerHotkeyRetry);  // The key is free now: the retry picks it up.
        bool retried = g_capHotkeys.size() > 1 && g_capHotkeys[1].registered;
        Hotkeys_Unregister();
        g_set.hotkey2 = L"";
        g_set.plainTextHotkey = L"";
        Hotkeys_Register();
        bool clean = Hotkeys_Status().empty();
        Hotkeys_Unregister();
        // The F24 combo must be free again after unregistering.
        bool freed = RegisterHotKey(nullptr, 0xBF01, busyMods, VK_F24) != FALSE;
        if (freed) UnregisterHotKey(nullptr, 0xBF01);
        Wh_Log(L"  status was: %s", status.c_str());
        Cap_Check(firstOk, L"hotkeys: Ctrl+Alt+Shift+F24 registers");
        Cap_Check(secondFailed && badReported, L"hotkeys: a taken key and a bad key are reported in plain words");
        Cap_Check(retried, L"hotkeys: the 5 s retry registers a key once it is free");
        Cap_Check(clean && freed, L"hotkeys: unregister frees the key");
        DestroyWindow(g_msgWnd);
        g_msgWnd = saved;
        g_set = savedSet;
    }

    // Win+V takeover, on the harness's own registry keys
    {
        Settings savedSet = g_set;
        RegDeleteTreeW(HKEY_CURRENT_USER, L"Software\\SeamlessClipboardManagerHarness");
        SetState(L"winvHistoryRestore", 0);
        SetState(L"winvHotkeyRestore", 0);
        std::wstring keys;
        Cap_SetClipboardHistory(1);
        g_set.takeOverWinV = true;
        Cap_ApplyWinVTakeover();
        bool onOk = !Cap_WindowsClipboardHistoryOn() && Cap_ReadDisabledHotkeys(keys) && keys == L"V" &&
                    GetState(L"winvHistoryRestore", 0) == 1 && GetState(L"winvHotkeyRestore", 0) == 2;
        Cap_ApplyWinVTakeover();  // Running twice changes nothing.
        bool twiceOk = Cap_ReadDisabledHotkeys(keys) && keys == L"V";
        g_set.takeOverWinV = false;
        Cap_ApplyWinVTakeover();
        bool offOk = Cap_WindowsClipboardHistoryOn() && !Cap_ReadDisabledHotkeys(keys) &&
                     GetState(L"winvHotkeyRestore", 0) == 0;
        // The owner's own "QV" with history already off: nothing to change, nothing to put back.
        Cap_SetClipboardHistory(0);
        Cap_WriteDisabledHotkeys(L"QV");
        g_set.takeOverWinV = true;
        Cap_ApplyWinVTakeover();
        g_set.takeOverWinV = false;
        Cap_ApplyWinVTakeover();
        bool ownOk = !Cap_WindowsClipboardHistoryOn() && Cap_ReadDisabledHotkeys(keys) && keys == L"QV";
        // Added to an existing value, then taken out again.
        Cap_WriteDisabledHotkeys(L"Q");
        g_set.takeOverWinV = true;
        Cap_ApplyWinVTakeover();
        bool addOk = Cap_ReadDisabledHotkeys(keys) && keys == L"QV";
        g_set.takeOverWinV = false;
        Cap_ApplyWinVTakeover();
        bool removeOk = Cap_ReadDisabledHotkeys(keys) && keys == L"Q";
        RegDeleteTreeW(HKEY_CURRENT_USER, L"Software\\SeamlessClipboardManagerHarness");
        Wh_Log(L"  win+v: on=%d twice=%d off=%d own=%d add=%d remove=%d", onOk, twiceOk, offOk, ownOk, addOk, removeOk);
        Cap_Check(onOk && twiceOk, L"win+v: takeover turns off history and adds V");
        Cap_Check(offOk, L"win+v: turning it off puts back only what the mod changed");
        Cap_Check(ownOk && addOk && removeOk, L"win+v: an existing DisabledHotkeys value is kept");
        g_set = savedSet;
    }

    Wh_Log(L"capture test: %d failed", g_capFails);
    return g_capFails ? 1 : 0;
}
#endif

// ---------------------------------------------------------------------------
// 40-ui.cpp : the clip list window (Ditto's Quick Paste window), the preview
// popup, the clip editor, the properties window and the app icon.
// Everything is drawn with Direct2D + DirectWrite on the UI thread.
// ---------------------------------------------------------------------------

namespace {
namespace scmui {

// ---------------------------------------------------------------------------
// Small COM holder
// ---------------------------------------------------------------------------
template <class T>
class Com {
   public:
    T* p = nullptr;
    Com() = default;
    Com(const Com& o) : p(o.p) {
        if (p) p->AddRef();
    }
    Com& operator=(const Com& o) {
        if (o.p) o.p->AddRef();
        reset();
        p = o.p;
        return *this;
    }
    ~Com() { reset(); }
    void reset() {
        if (p) p->Release();
        p = nullptr;
    }
    T** put() {
        reset();
        return &p;
    }
    T* get() const { return p; }
    T* operator->() const { return p; }
    explicit operator bool() const { return p != nullptr; }
};

// ---------------------------------------------------------------------------
// Metrics (DIPs) and ids
// ---------------------------------------------------------------------------
constexpr float kPad = 8, kCaptionW = 26, kDockH = 34, kHeaderH = 30, kRowPadY = 5, kRowGap = 2,
                kScrollW = 10, kBorderW = 1.5f, kWinRadius = 8, kMarkW = 16, kPinW = 22, kDragStart = 4;
constexpr int kPageSize = 60, kMaxPages = 40, kThumbCacheSize = 48, kThumbDecodeMax = 320;
constexpr UINT_PTR kTimerScroll = 1, kTimerSearch = 2, kTimerHover = 3, kTimerDrag = 4, kTimerAnim = 5, kTimerCaret = 8, kTimerDockHover = 9;
constexpr UINT kSearchDelayMs = 120, kHoverEaseMs = 120;

// Icon font code points (Segoe Fluent Icons / Segoe MDL2 Assets).
constexpr wchar_t kGlyphClose = 0xE711, kGlyphChevronR = 0xE76C, kGlyphChevronL = 0xE76B,
                  kGlyphFolder = 0xE8B7, kGlyphMore = 0xE712, kGlyphBack = 0xE72B, kGlyphPin = 0xE718,
                  kGlyphUnpin = 0xE77A, kGlyphLock = 0xE72E, kGlyphKey = 0xE8D7, kGlyphPage = 0xE8A5,
                  kGlyphPaste = 0xE77F, kGlyphFont = 0xE8D2, kGlyphBolt = 0xE945, kGlyphCopy = 0xE8C8,
                  kGlyphEdit = 0xE70F, kGlyphInfo = 0xE946, kGlyphView = 0xE890, kGlyphMoveTo = 0xE8DE,
                  kGlyphDelete = 0xE74D, kGlyphAdd = 0xE710, kGlyphPause = 0xE769, kGlyphSettings = 0xE713,
                  kGlyphCheck = 0xE73E, kGlyphFolderOpen = 0xE838, kGlyphNewFolder = 0xE8F4,
                  kGlyphList = 0xE8FD;

constexpr WCHAR kScmMenuClass[] = L"SeamlessClipboardManagerMenu";

enum Cmd : UINT {
    cmdPaste = 1, cmdPlain, cmdCopy, cmdEdit, cmdProps, cmdPreview, cmdSticky, cmdNeverDelete,
    cmdDelete, cmdSettings, cmdPause, cmdNewClip, cmdMoveNewGroup, cmdMoveOut, cmdOpenMain,
    cmdNewGroup, cmdSpecialBase = 100, cmdMoveGroupBase = 1000, cmdOpenGroupBase = 20000
};

enum class Hit { None, Row, Pin, Close, Chevron, Folder, Menu, Search, Scroll, Back, Caption };
enum class DockMode { Search, ConfirmDelete, NewGroup };

// ---------------------------------------------------------------------------
// Factories, fonts
// ---------------------------------------------------------------------------
struct Factories {
    Com<ID2D1Factory> d2d;
    Com<IDWriteFactory> dw;
    Com<IWICImagingFactory> wic;
} F;

bool EnsureFactories() {
    if (!F.d2d) {
        D2D1_FACTORY_OPTIONS o{};
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &o,
                                     (void**)F.d2d.put())))
            return false;
    }
    if (!F.dw && FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                                            (IUnknown**)F.dw.put())))
        return false;
    if (!F.wic && FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                          __uuidof(IWICImagingFactory), (void**)F.wic.put())))
        return false;
    return true;
}

struct Fonts {
    bool ok = false;
    std::wstring family, iconFamily;
    Com<IDWriteTextFormat> row, rowWrap, num, ui, uiBold, uiRight, icon, iconMid, iconSmall, wrap;
    float lineH = 18, numW = 16;
} T;

// The owner's weight for all text; emphasis is one step heavier, never past bold.
int BaseWeight() { return std::clamp(g_set.fontWeight, 100, 900); }
int BoldWeight() { return std::max(BaseWeight(), std::min(700, BaseWeight() + 100)); }

bool FamilyExists(const std::wstring& name) {
    Com<IDWriteFontCollection> sys;
    if (name.empty() || FAILED(F.dw->GetSystemFontCollection(sys.put(), FALSE))) return false;
    UINT32 index = 0;
    BOOL exists = FALSE;
    return SUCCEEDED(sys->FindFamilyName(name.c_str(), &index, &exists)) && exists;
}

std::wstring ResolveFamily() {
    if (FamilyExists(g_set.fontName)) return g_set.fontName;
    // "Fira Code" is usually installed as its Nerd Font build.
    std::wstring lower = g_set.fontName;
    for (auto& ch : lower) ch = (wchar_t)towlower(ch);
    if (lower.find(L"fira") != std::wstring::npos) {
        for (PCWSTR alt : {L"FiraCode Nerd Font", L"FiraCode Nerd Font Mono", L"Fira Code", L"Fira Mono"})
            if (FamilyExists(alt)) return alt;
    }
    return L"Segoe UI";
}

Com<IDWriteTextFormat> MakeFormat(const std::wstring& family, float size, DWRITE_FONT_WEIGHT weight,
                                  bool wrap, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING,
                                  bool trim = true) {
    Com<IDWriteTextFormat> f;
    if (FAILED(F.dw->CreateTextFormat(family.c_str(), nullptr, weight, DWRITE_FONT_STYLE_NORMAL,
                                      DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", f.put())))
        return f;
    f->SetWordWrapping(wrap ? DWRITE_WORD_WRAPPING_WRAP : DWRITE_WORD_WRAPPING_NO_WRAP);
    f->SetTextAlignment(align);
    if (trim && !wrap) {
        Com<IDWriteInlineObject> sign;
        F.dw->CreateEllipsisTrimmingSign(f.get(), sign.put());
        DWRITE_TRIMMING t{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
        f->SetTrimming(&t, sign.get());
    }
    return f;
}

bool EnsureFonts() {
    if (T.ok) return true;
    if (!EnsureFactories()) return false;
    T.family = ResolveFamily();
    T.iconFamily = FamilyExists(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
    float size = g_set.fontSize * 96.0f / 72.0f;
    auto normal = (DWRITE_FONT_WEIGHT)BaseWeight(), bold = (DWRITE_FONT_WEIGHT)BoldWeight();
    T.row = MakeFormat(T.family, size, normal, false);
    T.num = MakeFormat(T.family, size * 0.86f, bold, false, DWRITE_TEXT_ALIGNMENT_TRAILING);
    T.ui = MakeFormat(T.family, size, normal, false);
    T.uiBold = MakeFormat(T.family, size, bold, false);
    T.uiRight = MakeFormat(T.family, size, normal, false, DWRITE_TEXT_ALIGNMENT_TRAILING);
    T.wrap = MakeFormat(T.family, size, normal, true);
    // Clip text wraps onto the row's lines like Ditto; the last line that fits ends in an ellipsis.
    T.rowWrap = MakeFormat(T.family, size, normal, true);
    if (T.rowWrap) {
        T.rowWrap->SetWordWrapping(DWRITE_WORD_WRAPPING_EMERGENCY_BREAK);
        Com<IDWriteInlineObject> sign;
        F.dw->CreateEllipsisTrimmingSign(T.rowWrap.get(), sign.put());
        DWRITE_TRIMMING t{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
        T.rowWrap->SetTrimming(&t, sign.get());
    }
    T.icon = MakeFormat(T.iconFamily, 14, DWRITE_FONT_WEIGHT_NORMAL, false, DWRITE_TEXT_ALIGNMENT_CENTER, false);
    T.iconMid = MakeFormat(T.iconFamily, 12, DWRITE_FONT_WEIGHT_NORMAL, false, DWRITE_TEXT_ALIGNMENT_CENTER, false);
    T.iconSmall = MakeFormat(T.iconFamily, 10, DWRITE_FONT_WEIGHT_NORMAL, false, DWRITE_TEXT_ALIGNMENT_CENTER, false);
    if (!T.row || !T.rowWrap || !T.num || !T.ui || !T.uiBold || !T.uiRight || !T.wrap || !T.icon || !T.iconMid ||
        !T.iconSmall)
        return false;
    for (auto* f : {T.icon.get(), T.iconMid.get(), T.iconSmall.get(), T.ui.get(), T.uiBold.get(), T.uiRight.get()})
        f->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    // One uniform line height so rows, numbers and the scroll math agree.
    Com<IDWriteTextLayout> probe;
    F.dw->CreateTextLayout(L"Agy", 3, T.row.get(), 1000, 1000, probe.put());
    DWRITE_LINE_METRICS lm{};
    UINT32 n = 0;
    float baseline = size * 0.8f;
    if (probe && SUCCEEDED(probe->GetLineMetrics(&lm, 1, &n)) && n) {
        T.lineH = std::ceil(lm.height);
        baseline = lm.baseline;
    } else {
        T.lineH = std::ceil(size * 1.35f);
    }
    for (auto* f : {T.row.get(), T.rowWrap.get(), T.num.get(), T.wrap.get()})
        f->SetLineSpacing(DWRITE_LINE_SPACING_METHOD_UNIFORM, T.lineH, baseline);
    Com<IDWriteTextLayout> numProbe;
    F.dw->CreateTextLayout(L"10", 2, T.num.get(), 1000, 1000, numProbe.put());
    DWRITE_TEXT_METRICS tm{};
    if (numProbe && SUCCEEDED(numProbe->GetMetrics(&tm))) T.numW = std::ceil(tm.widthIncludingTrailingWhitespace);
    T.ok = true;
    return true;
}

void ResetFonts() { T = Fonts{}; }

// ---------------------------------------------------------------------------
// Data source (the db part; the harness falls back to a sample list)
// ---------------------------------------------------------------------------
#ifdef SCM_HARNESS
bool SampleMode() {
    static int mode = -1;
    if (mode < 0) mode = (!Db_IsOpen() || Db_TotalClips() == 0 || Db_LastError() == L"stub") ? 1 : 0;
    return mode == 1;
}

std::vector<ClipRow>& Samples() {
    static std::vector<ClipRow> rows;
    if (!rows.empty()) return rows;
    auto add = [](int64_t id, ClipKind kind, const wchar_t* text, int64_t parent = -1) -> ClipRow& {
        ClipRow r;
        r.id = id;
        r.kind = kind;
        r.text = text;
        r.parentId = parent;
        r.isGroup = kind == ClipKind::Group;
        r.date = UnixNow() - id * 600;
        rows.push_back(r);
        return rows.back();
    };
    add(101, ClipKind::Text, L"Standup notes: ship the clip list today, review the db part tomorrow").sticky = true;
    add(102, ClipKind::Text, L"git status --short");
    add(103, ClipKind::Text,
        L"static int Clamp(int v, int lo, int hi) {\n\tif (v < lo)\n\t\treturn lo;\n\tif (v > hi)\n\t\treturn hi;\n"
        L"\treturn v;\n}\n// used by the settings loader");
    add(104, ClipKind::Text, L"https://github.com/DavidHiFi/davids-windhawk-mods/pulls?q=is%3Aopen+clipboard");
    add(105, ClipKind::Image, L"CF_DIB");
    add(106, ClipKind::Files,
        L"C:\\Users\\localuser\\Pictures\\wallpaper-mocha.png\nC:\\Users\\localuser\\Documents\\notes.txt\n"
        L"D:\\Projects\\clipboard\\report-final.pdf");
    add(107, ClipKind::Group, L"Snippets");
    add(108, ClipKind::Text, L"Home address\n221B Baker Street\nLondon NW1 6XE").neverDelete = true;
    add(109, ClipKind::Text,
        L"A single very long line of copied text that keeps going well past the right edge of the window so the "
        L"row wraps it onto the next lines, the way Ditto does, and ends with an ellipsis when it runs out of room");
    add(110, ClipKind::Text, L"SELECT id, name, email\nFROM users\nWHERE active = 1\nORDER BY name;");
    add(111, ClipKind::Image, L"PNG");
    add(112, ClipKind::Text, L"Thanks, talk soon!").hasShortcut = true;
    add(113, ClipKind::Text, L"Meeting moved to 3:30 pm, same room.");
    add(114, ClipKind::Text, L"#89B4FA  #CBA6F7  #1E1E2E");
    add(201, ClipKind::Text, L"Kind regards,\nDavid", 107);
    add(202, ClipKind::Text, L"for (auto& item : items) {\n\tprocess(item);\n}", 107);
    return rows;
}

bool SampleMatch(const ClipRow& r, const ClipQuery& q) {
    if (q.groupId == -1 ? r.parentId != -1 : r.parentId != q.groupId) return false;
    if (q.search.empty()) return true;
    return StrStrIW(r.text.c_str(), q.search.c_str()) != nullptr;
}

void SampleReset() {
    Samples().clear();
    Samples();  // Rebuilds the list
}

// Pinned rows first in their order, then the rest oldest id first (like the db sort).
void SampleSort(const std::vector<int64_t>& pinOrder) {
    auto& rows = Samples();
    std::vector<ClipRow> out;
    for (int64_t id : pinOrder)
        for (auto& r : rows)
            if (r.id == id && r.sticky) out.push_back(r);
    for (auto& r : rows)
        if (r.sticky && std::find(pinOrder.begin(), pinOrder.end(), r.id) == pinOrder.end()) out.push_back(r);
    std::vector<ClipRow> rest;
    for (auto& r : rows)
        if (!r.sticky) rest.push_back(r);
    std::sort(rest.begin(), rest.end(), [](const ClipRow& a, const ClipRow& b) { return a.id < b.id; });
    out.insert(out.end(), rest.begin(), rest.end());
    rows = std::move(out);
}
#endif

bool DataSetSticky(int64_t id, bool on, bool inGroup) {
#ifdef SCM_HARNESS
    if (SampleMode()) {
        for (auto& r : Samples())
            if (r.id == id) r.sticky = on;
        SampleSort(on ? std::vector<int64_t>{id} : std::vector<int64_t>{});
        return true;
    }
#endif
    return Db_SetSticky(id, on, inGroup);
}

bool DataSetStickyOrder(const std::vector<int64_t>& idsTopFirst, bool inGroup) {
#ifdef SCM_HARNESS
    if (SampleMode()) {
        for (auto& r : Samples())
            if (std::find(idsTopFirst.begin(), idsTopFirst.end(), r.id) != idsTopFirst.end()) r.sticky = true;
        SampleSort(idsTopFirst);
        return true;
    }
#endif
    return Db_SetStickyOrder(idsTopFirst, inGroup);
}

int DataCount(const ClipQuery& q) {
#ifdef SCM_HARNESS
    if (SampleMode()) {
        int n = 0;
        for (auto& r : Samples()) n += SampleMatch(r, q);
        return n;
    }
#endif
    return Db_IsOpen() ? Db_CountClips(q) : 0;
}

std::vector<ClipRow> DataQuery(const ClipQuery& q, int offset, int limit) {
#ifdef SCM_HARNESS
    if (SampleMode()) {
        std::vector<ClipRow> out;
        int i = 0;
        for (auto& r : Samples()) {
            if (!SampleMatch(r, q)) continue;
            if (i++ >= offset && (int)out.size() < limit) out.push_back(r);
        }
        return out;
    }
#endif
    return Db_IsOpen() ? Db_QueryClips(q, offset, limit) : std::vector<ClipRow>{};
}

std::wstring DataText(const ClipRow& r) {
#ifdef SCM_HARNESS
    if (SampleMode()) return r.text;
#endif
    return Db_GetClipText(r.id);
}

// ---------------------------------------------------------------------------
// Images: decode with WIC, cache small thumbnails (LRU)
// ---------------------------------------------------------------------------
Com<IWICBitmap> DecodeBytes(const std::string& bytes, bool dib, UINT maxDim, UINT& ow, UINT& oh) {
    Com<IWICBitmap> out;
    std::string file;
    const std::string* src = &bytes;
    if (dib) {
        // CF_DIB has no file header; build one so the BMP decoder can read it.
        if (bytes.size() < sizeof(BITMAPINFOHEADER)) return out;
        auto* bih = (const BITMAPINFOHEADER*)bytes.data();
        DWORD colors = bih->biClrUsed ? bih->biClrUsed : (bih->biBitCount <= 8 ? 1u << bih->biBitCount : 0);
        DWORD masks = (bih->biCompression == BI_BITFIELDS && bih->biSize == sizeof(BITMAPINFOHEADER)) ? 12 : 0;
        BITMAPFILEHEADER fh{};
        fh.bfType = 0x4D42;
        fh.bfSize = (DWORD)(sizeof(fh) + bytes.size());
        fh.bfOffBits = (DWORD)(sizeof(fh) + bih->biSize + masks + colors * 4);
        file.assign((const char*)&fh, sizeof(fh));
        file += bytes;
        src = &file;
    }
    Com<IStream> stream;
    stream.p = SHCreateMemStream((const BYTE*)src->data(), (UINT)src->size());
    if (!stream) return out;
    Com<IWICBitmapDecoder> dec;
    Com<IWICBitmapFrameDecode> frame;
    if (FAILED(F.wic->CreateDecoderFromStream(stream.get(), nullptr, WICDecodeMetadataCacheOnDemand, dec.put())) ||
        FAILED(dec->GetFrame(0, frame.put())))
        return out;
    UINT w = 0, h = 0;
    frame->GetSize(&w, &h);
    if (!w || !h) return out;
    ow = w;
    oh = h;
    float k = std::min(1.0f, (float)maxDim / (float)std::max(w, h));
    UINT tw = std::max(1u, (UINT)std::lround(w * k)), th = std::max(1u, (UINT)std::lround(h * k));
    Com<IWICBitmapScaler> scaler;
    Com<IWICFormatConverter> conv;
    if (FAILED(F.wic->CreateBitmapScaler(scaler.put())) ||
        FAILED(scaler->Initialize(frame.get(), tw, th, WICBitmapInterpolationModeFant)) ||
        FAILED(F.wic->CreateFormatConverter(conv.put())) ||
        FAILED(conv->Initialize(scaler.get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0,
                                WICBitmapPaletteTypeMedianCut)))
        return out;
    F.wic->CreateBitmapFromSource(conv.get(), WICBitmapCacheOnLoad, out.put());
    return out;
}

Com<IWICBitmap> FromPixels(UINT w, UINT h, std::vector<UINT32>& px) {
    Com<IWICBitmap> bmp;
    F.wic->CreateBitmapFromMemory(w, h, GUID_WICPixelFormat32bppPBGRA, w * 4, (UINT)(px.size() * 4),
                                  (BYTE*)px.data(), bmp.put());
    return bmp;
}

#ifdef SCM_HARNESS
// A generated "screenshot": blue to mauve sky, a sun and two hills.
Com<IWICBitmap> SampleImage(UINT w, UINT h, int variant) {
    std::vector<UINT32> px((size_t)w * h);
    auto lerp = [](UINT32 a, UINT32 b, float t) {
        auto ch = [&](int s) {
            return (UINT32)std::lround(((a >> s) & 0xFF) * (1 - t) + ((b >> s) & 0xFF) * t) << s;
        };
        return ch(16) | ch(8) | ch(0);
    };
    UINT32 c1 = variant ? mocha::teal : mocha::blue, c2 = variant ? mocha::blue : mocha::mauve;
    for (UINT y = 0; y < h; y++)
        for (UINT x = 0; x < w; x++) {
            float fx = (float)x / w, fy = (float)y / h;
            UINT32 c = lerp(c1, c2, fx * 0.7f + fy * 0.3f);
            float dx = fx - 0.72f, dy = (fy - 0.32f) * h / w;
            if (dx * dx + dy * dy < 0.012f) c = mocha::peach;
            float hill1 = 0.68f + 0.10f * std::sin(fx * 5.0f), hill2 = 0.80f + 0.07f * std::sin(fx * 7.0f + 1.5f);
            if (fy > hill1) c = mocha::surface1;
            if (fy > hill2) c = mocha::base;
            px[(size_t)y * w + x] = 0xFF000000u | c;
        }
    return FromPixels(w, h, px);
}
#endif

Com<IWICBitmap> LoadClipImage(int64_t id, UINT maxDim, UINT& ow, UINT& oh) {
#ifdef SCM_HARNESS
    if (SampleMode()) {
        ow = id == 111 ? 1280 : 1920;
        oh = id == 111 ? 960 : 1080;
        UINT w = std::min<UINT>(maxDim, 480);
        return SampleImage(w, w * oh / ow, id == 111);
    }
#endif
    static const std::pair<PCWSTR, bool> kFormats[] = {{L"PNG", false}, {L"CF_DIB", true}, {L"CF_DIBV5", true}};
    for (auto& [name, dib] : kFormats) {
        std::string bytes;
        if (!Db_GetFormat(id, name, bytes) || bytes.empty()) continue;
        Com<IWICBitmap> bmp = DecodeBytes(bytes, dib, maxDim, ow, oh);
        if (bmp) return bmp;
    }
    return {};
}

struct Thumb {
    Com<IWICBitmap> wic;
    Com<ID2D1Bitmap> d2d;
    ID2D1RenderTarget* owner = nullptr;
    UINT w = 0, h = 0;  // Original size
};
std::unordered_map<int64_t, Thumb> g_thumbs;
std::vector<int64_t> g_thumbOrder;  // LRU, most recent last

Thumb* GetThumb(int64_t id) {
    auto it = g_thumbs.find(id);
    if (it != g_thumbs.end()) {
        auto pos = std::find(g_thumbOrder.begin(), g_thumbOrder.end(), id);
        if (pos != g_thumbOrder.end()) g_thumbOrder.erase(pos);
        g_thumbOrder.push_back(id);
        return it->second.wic ? &it->second : nullptr;
    }
    Thumb t;
    t.wic = LoadClipImage(id, kThumbDecodeMax, t.w, t.h);  // A failure is cached too (empty wic).
    while ((int)g_thumbOrder.size() >= kThumbCacheSize) {
        g_thumbs.erase(g_thumbOrder.front());
        g_thumbOrder.erase(g_thumbOrder.begin());
    }
    g_thumbOrder.push_back(id);
    auto& slot = g_thumbs[id] = t;
    return slot.wic ? &slot : nullptr;
}

ID2D1Bitmap* DeviceBitmap(ID2D1RenderTarget* rt, Thumb& t) {
    if (t.owner != rt || !t.d2d) {
        t.d2d.reset();
        t.owner = rt;
        rt->CreateBitmapFromWicBitmap(t.wic.get(), t.d2d.put());
    }
    return t.d2d.get();
}

void DropDeviceBitmaps() {
    for (auto& [id, t] : g_thumbs) {
        t.d2d.reset();
        t.owner = nullptr;
    }
}

// ---------------------------------------------------------------------------
// Drawing helpers
// ---------------------------------------------------------------------------
struct Ctx {
    ID2D1RenderTarget* rt = nullptr;
    Com<ID2D1SolidColorBrush> brush;
    explicit Ctx(ID2D1RenderTarget* r) : rt(r) { rt->CreateSolidColorBrush(D2DColor(mocha::text), brush.put()); }
    ID2D1SolidColorBrush* B(UINT32 rgb, float a = 1) {
        brush->SetColor(D2DColor(rgb, a));
        return brush.get();
    }
    ID2D1SolidColorBrush* BRef(COLORREF c, float a = 1) {
        brush->SetColor(D2DColorRef(c, a));
        return brush.get();
    }
    Com<ID2D1LinearGradientBrush> Gradient(D2D1_POINT_2F a, D2D1_POINT_2F b, D2D1_COLOR_F c1, D2D1_COLOR_F c2) {
        Com<ID2D1LinearGradientBrush> g;
        D2D1_GRADIENT_STOP stops[2] = {{0, c1}, {1, c2}};
        Com<ID2D1GradientStopCollection> coll;
        if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, coll.put())))
            rt->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(a, b), coll.get(), g.put());
        return g;
    }
    // Accent outline brush: blue to mauve when gradientBorder, else accent only.
    Com<ID2D1LinearGradientBrush> Accent(const D2D1_RECT_F& r, float alpha = 1) {
        COLORREF c2 = g_set.gradientBorder ? g_set.accentColor2 : g_set.accentColor;
        return Gradient({r.left, r.top}, {r.right, r.bottom}, D2DColorRef(g_set.accentColor, alpha),
                        D2DColorRef(c2, alpha));
    }
    void Text(const std::wstring& s, IDWriteTextFormat* f, const D2D1_RECT_F& r, UINT32 color, float a = 1) {
        if (s.empty() || r.right <= r.left) return;
        Com<IDWriteTextLayout> layout;
        if (FAILED(F.dw->CreateTextLayout(s.c_str(), (UINT32)s.size(), f, r.right - r.left, r.bottom - r.top,
                                          layout.put())))
            return;
        rt->DrawTextLayout({r.left, r.top}, layout.get(), B(color, a), D2D1_DRAW_TEXT_OPTIONS_CLIP);
    }
    float TextWidth(const std::wstring& s, IDWriteTextFormat* f) {
        Com<IDWriteTextLayout> layout;
        DWRITE_TEXT_METRICS m{};
        if (s.empty() || FAILED(F.dw->CreateTextLayout(s.c_str(), (UINT32)s.size(), f, 10000, 1000, layout.put())) ||
            FAILED(layout->GetMetrics(&m)))
            return 0;
        return m.widthIncludingTrailingWhitespace;
    }
    void Glyph(wchar_t g, const D2D1_RECT_F& r, UINT32 color, bool small = false, float a = 1) {
        rt->DrawText(&g, 1, small ? T.iconSmall.get() : T.icon.get(), r, B(color, a),
                     D2D1_DRAW_TEXT_OPTIONS_NONE);
    }
    // Hover and selection look: a soft blue to mauve fill and a 1 px blue to mauve ring.
    void Glow(const D2D1_RECT_F& r, float radius, float fill, float ring, float ringW = 1) {
        float rad = std::min(radius, std::min(r.right - r.left, r.bottom - r.top) / 2);
        D2D1_ROUNDED_RECT rr{{r.left + ringW / 2, r.top + ringW / 2, r.right - ringW / 2, r.bottom - ringW / 2}, rad, rad};
        if (fill > 0) {
            auto f = Gradient({r.left, r.top}, {r.right, r.bottom}, D2DColorRef(g_set.accentColor, fill),
                              D2DColorRef(g_set.accentColor2, fill));
            if (f) rt->FillRoundedRectangle(rr, f.get());
        }
        if (ring > 0) {
            auto g = Accent(r, ring);
            if (g) rt->DrawRoundedRectangle(rr, g.get(), ringW);
        }
    }
    void HoverButton(const D2D1_RECT_F& r, float t = 1) {
        Glow(r, (float)g_set.cornerRadius, 0.16f * t, 0.85f * t);
    }
};

float MeasureText(const std::wstring& s, IDWriteTextFormat* f) {
    Com<IDWriteTextLayout> layout;
    DWRITE_TEXT_METRICS m{};
    if (s.empty() || FAILED(F.dw->CreateTextLayout(s.c_str(), (UINT32)s.size(), f, 10000, 1000, layout.put())) ||
        FAILED(layout->GetMetrics(&m)))
        return 0;
    return m.widthIncludingTrailingWhitespace;
}

D2D1_RECT_F Inset(const D2D1_RECT_F& r, float dx, float dy) {
    return {r.left + dx, r.top + dy, r.right - dx, r.bottom - dy};
}
bool In(const D2D1_RECT_F& r, float x, float y) { return x >= r.left && x < r.right && y >= r.top && y < r.bottom; }

float TintAlpha() {
    if (g_set.blurMode == L"none") return 1.0f;
    return std::max(30, g_set.backgroundOpacity) / 100.0f;  // Below 30 % text behind the blur starts to read through.
}

// Window body: wash (offscreen only), a dark mantle to crust tint, gradient border.
void PaintFrame(Ctx& c, float w, float h, bool offscreen, bool clear = true) {
    if (clear) c.rt->Clear(D2D1::ColorF(0, 0, 0, 0));
    // The tint fills the whole client rect; DWM rounds the window. Offscreen PNGs have no DWM, so
    // they clip to the same radius to show what the real window looks like.
    float rad = SystemCornerRadius(false);
    D2D1_ROUNDED_RECT body{{0, 0, w, h}, rad, rad};
    float a = TintAlpha();
    auto tint = c.Gradient({0, 0}, {0, h}, D2DColor(mocha::base, a), D2DColor(mocha::base, std::min(1.0f, a + 0.04f)));
    if (offscreen) {
        // The real backdrop can't be captured; stand in with a dark wallpaper wash.
        auto wash = c.Gradient({0, 0}, {w, h}, D2DColor(mocha::surface0), D2DColor(mocha::base));
        if (g_set.blurMode != L"none" && wash) c.rt->FillRoundedRectangle(body, wash.get());
        if (tint) c.rt->FillRoundedRectangle(body, tint.get());
    } else if (tint) {
        c.rt->FillRectangle({0, 0, w, h}, tint.get());
    }
    if (g_set.ownBorder) {
        D2D1_RECT_F edge{kBorderW / 2, kBorderW / 2, w - kBorderW / 2, h - kBorderW / 2};
        auto border = c.Accent(edge);
        float r2 = SystemCornerRadius(false) - kBorderW / 2;
        if (border) c.rt->DrawRoundedRectangle({edge, r2, r2}, border.get(), kBorderW);
    }
}

// First lines of a clip for a row: tabs expanded, each line capped.
std::wstring RowLines(const std::wstring& s, int maxLines, bool baseNames) {
    std::wstring out, line;
    int lines = 0;
    auto flush = [&]() {
        if (baseNames) {
            size_t slash = line.find_last_of(L"\\/");
            if (slash != std::wstring::npos && slash + 1 < line.size()) line = line.substr(slash + 1);
        }
        if (lines) out += L'\n';
        out += line;
        line.clear();
        lines++;
    };
    for (size_t i = 0; i < s.size() && lines < maxLines; i++) {
        wchar_t ch = s[i];
        if (ch == L'\r') continue;
        if (ch == L'\n') {
            flush();
            continue;
        }
        if (line.size() >= 400) continue;
        if (ch == L'\t') {
            line.append(4 - line.size() % 4, L' ');
        } else {
            line += ch;
        }
    }
    if (lines < maxLines && (!line.empty() || lines == 0)) flush();
    return out;
}

std::wstring HumanSize(size_t n) {
    WCHAR buf[64];
    if (n < 1024) swprintf_s(buf, L"%zu bytes", n);
    else if (n < 1024 * 1024) swprintf_s(buf, L"%.1f KB", n / 1024.0);
    else swprintf_s(buf, L"%.1f MB", n / (1024.0 * 1024.0));
    return buf;
}

std::wstring FormatDate(int64_t unix) {
    if (unix <= 0) return L"never";
    ULARGE_INTEGER t;
    t.QuadPart = (ULONGLONG)unix * 10000000ULL + 116444736000000000ULL;
    FILETIME ft{t.LowPart, t.HighPart};
    SYSTEMTIME utc, st;
    FileTimeToSystemTime(&ft, &utc);
    SystemTimeToTzSpecificLocalTime(nullptr, &utc, &st);
    WCHAR date[64]{};
    GetDateFormatW(LOCALE_USER_DEFAULT, 0, &st, L"MMM d, yyyy", date, 64);
    WCHAR out[96];
    int hour = st.wHour % 12 ? st.wHour % 12 : 12;
    swprintf_s(out, L"%s, %d:%02d %s", date, hour, st.wMinute, st.wHour < 12 ? L"am" : L"pm");
    return out;
}

UINT MonitorDpi(HMONITOR mon) {
    using Fn = HRESULT(WINAPI*)(HMONITOR, int, UINT*, UINT*);
    static Fn fn = [] {
        HMODULE m = LoadLibraryExW(L"shcore.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        return m ? (Fn)(void*)GetProcAddress(m, "GetDpiForMonitor") : (Fn) nullptr;
    }();
    UINT x = 96, y = 96;
    if (!fn || FAILED(fn(mon, 0, &x, &y))) return GetDpiForSystem();
    return x;
}

struct AccentPolicyData {
    int state, flags, color, animation;
};
struct WindowCompositionData {
    DWORD attrib;
    PVOID data;
    SIZE_T size;
};

// The same accent acrylic the taskbar uses. color is ABGR; our own Direct2D tint does the coloring,
// so it only needs a nonzero alpha.
void SetAccent(HWND h, int state, DWORD abgr) {
    using Fn = BOOL(WINAPI*)(HWND, WindowCompositionData*);
    static Fn fn = (Fn)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    if (!fn) return;
    AccentPolicyData a{state, state ? 2 : 0, (int)abgr, 0};
    WindowCompositionData d{19 /* WCA_ACCENT_POLICY */, &a, sizeof(a)};
    fn(h, &d);
}

void ApplyBackdrop(HWND h) {
    BOOL dark = TRUE;
    DwmSetWindowAttribute(h, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    int corner = 2;  // DWMWCP_ROUND
    DwmSetWindowAttribute(h, 33 /* DWMWA_WINDOW_CORNER_PREFERENCE */, &corner, sizeof(corner));
    COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE: we draw our own border
    DwmSetWindowAttribute(h, 34 /* DWMWA_BORDER_COLOR */, &none, sizeof(none));
    DwmSetWindowAttribute(h, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
    // Acrylic uses the accent blur, not DWMSBT_TRANSIENTWINDOW: on a WS_THICKFRAME popup the system
    // backdrop leaves its caption-height top band unblurred, which showed as a flat dark strip.
    bool acrylic = g_set.blurMode == L"acrylic";
    int type = acrylic ? 1 : g_set.blurMode == L"mica" ? 2 : 1;
    MARGINS m = type == 2 ? MARGINS{-1, -1, -1, -1} : MARGINS{0, 0, 0, 0};
    DwmExtendFrameIntoClientArea(h, &m);
    DwmSetWindowAttribute(h, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &type, sizeof(type));
    if (acrylic) {
        // Makes DWM use the window's alpha, so the blur shows through the tint.
        DWM_BLURBEHIND bb{};
        bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
        bb.fEnable = TRUE;
        bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
        DwmEnableBlurBehindWindow(h, &bb);
        if (bb.hRgnBlur) DeleteObject(bb.hRgnBlur);
        SetAccent(h, 4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 0x01000000 | 0x2E1E1E);
    } else {
        SetAccent(h, 0, 0);
    }
    // Recalculate the frame now: CreateWindowEx sizes the client before our WM_NCCALCSIZE
    // handler is in effect, which left a frame-sized dark band across the top.
    SetWindowPos(h, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

// A Direct2D surface on one of our popups.
struct Surface {
    HWND hwnd = nullptr;
    Com<ID2D1HwndRenderTarget> rt;
    bool Ensure() {
        if (rt) return true;
        if (!hwnd || !EnsureFactories()) return false;
        RECT rc;
        GetClientRect(hwnd, &rc);
        float dpi = (float)GetDpiForWindow(hwnd);
        auto props = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), dpi, dpi);
        auto hp = D2D1::HwndRenderTargetProperties(
            hwnd, D2D1::SizeU(std::max<LONG>(1, rc.right), std::max<LONG>(1, rc.bottom)));
        return SUCCEEDED(F.d2d->CreateHwndRenderTarget(&props, &hp, rt.put()));
    }
    void Resize() {
        if (!rt) return;
        RECT rc;
        GetClientRect(hwnd, &rc);
        rt->Resize(D2D1::SizeU(std::max<LONG>(1, rc.right), std::max<LONG>(1, rc.bottom)));
        float dpi = (float)GetDpiForWindow(hwnd);
        rt->SetDpi(dpi, dpi);
    }
    void Discard() {
        if (rt) DropDeviceBitmaps();
        rt.reset();
    }
    float Scale() const { return hwnd ? GetDpiForWindow(hwnd) / 96.0f : 1.0f; }
};

// ---------------------------------------------------------------------------
// List state
// ---------------------------------------------------------------------------
struct ListState {
    Surface surf;
    float wDip = 450, hDip = 400;  // Used by the offscreen renderer
    ClipQuery q;
    std::wstring groupName;
    int count = 0;
    std::unordered_map<int, std::vector<ClipRow>> pages;
    std::vector<int> pageOrder;  // LRU, most recent last
    int caret = 0, anchor = 0;
    std::vector<char> sel;  // Per index; sized to count
    bool selAll = false;
    int hover = -1;
    Hit hoverHit = Hit::None;
    float scrollY = 0, scrollTarget = 0;
    bool dragThumb = false;
    float dragOffset = 0;
    bool tracking = false;
    bool focused = false, caretOn = true;  // Search caret blink
    bool dockHot = false;
    float dockHover = 0;
    std::wstring search;
    DockMode mode = DockMode::Search;
    std::wstring nameText;
    std::vector<int64_t> pendingMove;
    int confirmCount = 0;
    bool menuOpen = false;
    bool hideRequested = false;  // Harness: Esc asked to close
    float hoverT = 1;            // Hover fade-in, 0..1
    ULONGLONG hoverStart = 0;
    // Dragging a row to reorder the pinned block.
    bool dragPending = false, dragActive = false, dragFromSticky = false;
    int dragFrom = -1, dragInsert = -1, dragSticky = 0;
    int64_t dragId = 0;
    float dragStartY = 0, dragY = 0, dragGrab = 0;
} L;

struct Layout {
    float w = 0, h = 0;
    D2D1_RECT_F list{}, header{}, back{}, dock{}, folder{}, search{}, menu{}, close{}, chevron{}, scroll{};
    float rowH = 0, stride = 0, gutter = 0, viewH = 0, rowRight = 0;
};

Layout MakeLayout(float w, float h) {
    Layout l;
    l.w = w;
    l.h = h;
    float right = w - kCaptionW;
    float top = kPad;
    bool inGroup = L.q.groupId != -1;
    l.header = {kPad, top, right, top + (inGroup ? kHeaderH : 0)};
    l.back = {kPad, top + 3, kPad + 24, top + kHeaderH - 3};
    if (inGroup) top += kHeaderH + 4;
    l.dock = {kPad, h - kPad - kDockH, w - kPad, h - kPad};
    l.list = {kPad, top, right, l.dock.top - 6};
    l.scroll = {l.list.right - 7, l.list.top + 2, l.list.right - 1, l.list.bottom - 2};
    l.rowRight = l.list.right - kScrollW;
    float cy = (l.dock.top + l.dock.bottom) / 2;
    l.folder = {l.dock.left + 9, cy - 12, l.dock.left + 33, cy + 12};
    l.menu = {l.dock.right - 33, cy - 12, l.dock.right - 9, cy + 12};
    l.search = {l.folder.right + 6, l.dock.top + 5, l.menu.left - 6, l.dock.bottom - 5};
    l.close = {w - kCaptionW + 1, 7, w - 4, 29};
    l.chevron = {w - kCaptionW + 1, 33, w - 4, 55};
    l.rowH = kRowPadY * 2 + g_set.linesPerRow * T.lineH;
    l.stride = l.rowH + kRowGap;
    l.gutter = g_set.showPositions ? T.numW + 12 : 10;
    l.viewH = std::max(0.0f, l.list.bottom - l.list.top);
    return l;
}

Layout CurrentLayout() {
    EnsureFonts();
    if (L.surf.hwnd) {
        RECT rc;
        GetClientRect(L.surf.hwnd, &rc);
        float s = L.surf.Scale();
        return MakeLayout(rc.right / s, rc.bottom / s);
    }
    return MakeLayout(L.wDip, L.hDip);
}

float MaxScroll(const Layout& l) { return std::max(0.0f, L.count * l.stride - kRowGap - l.viewH); }

D2D1_RECT_F RowRect(const Layout& l, int i) {
    float y = l.list.top + i * l.stride - L.scrollY;
    return {l.list.left, y, l.rowRight, y + l.rowH};
}

// The pin button sits at the right end of a row's first line.
D2D1_RECT_F PinRect(const D2D1_RECT_F& row) {
    float half = std::min(kPinW / 2, (row.bottom - row.top) / 2 - 1);
    float cy = std::min(row.top + kRowPadY + T.lineH / 2, row.bottom - half - 1);
    cy = std::max(cy, row.top + half + 1);
    return {row.right - 4 - 2 * half, cy - half, row.right - 4, cy + half};
}

// ---- Rows (virtualized pages) ----
const ClipRow* RowAt(int i) {
    if (i < 0 || i >= L.count) return nullptr;
    int page = i / kPageSize;
    auto it = L.pages.find(page);
    if (it == L.pages.end()) {
        if ((int)L.pages.size() >= kMaxPages && !L.pageOrder.empty()) {
            L.pages.erase(L.pageOrder.front());
            L.pageOrder.erase(L.pageOrder.begin());
        }
        it = L.pages.emplace(page, DataQuery(L.q, page * kPageSize, kPageSize)).first;
        L.pageOrder.push_back(page);
    } else if (L.pageOrder.back() != page) {
        L.pageOrder.erase(std::find(L.pageOrder.begin(), L.pageOrder.end(), page));
        L.pageOrder.push_back(page);
    }
    size_t k = (size_t)(i % kPageSize);
    return k < it->second.size() ? &it->second[k] : nullptr;
}

int64_t IdAt(int i) {
    const ClipRow* r = RowAt(i);
    return r ? r->id : 0;
}

void Invalidate();

// Restarts the blink with the caret showing (on focus and after each key).
void CaretReset() {
    L.caretOn = true;
    if (!L.surf.hwnd) return;
    UINT blink = GetCaretBlinkTime();
    if (L.focused && blink && blink != INFINITE) SetTimer(L.surf.hwnd, kTimerCaret, blink, nullptr);
    else KillTimer(L.surf.hwnd, kTimerCaret);
}

void Invalidate() {
    if (L.surf.hwnd) InvalidateRect(L.surf.hwnd, nullptr, FALSE);
}

void Reload() {
    L.pages.clear();
    L.pageOrder.clear();
    L.count = DataCount(L.q);
    L.sel.assign((size_t)L.count, 0);
    L.selAll = false;
    L.caret = std::clamp(L.caret, 0, std::max(0, L.count - 1));
    L.anchor = L.caret;
    if (L.count) L.sel[(size_t)L.caret] = 1;
    Layout l = CurrentLayout();
    L.scrollY = std::clamp(L.scrollY, 0.0f, MaxScroll(l));
    L.scrollTarget = std::clamp(L.scrollTarget, 0.0f, MaxScroll(l));
    Invalidate();
}

// ---- Selection ----
bool IsSel(int i) { return L.selAll || (i >= 0 && i < (int)L.sel.size() && L.sel[(size_t)i]); }

std::vector<int> SelectedIndices() {
    std::vector<int> out;
    for (int i = 0; i < L.count; i++)
        if (IsSel(i)) out.push_back(i);
    if (out.empty() && L.count) out.push_back(L.caret);
    return out;
}

std::vector<int64_t> SelectedIds(bool skipGroups = false) {
    std::vector<int64_t> ids;
    for (int i : SelectedIndices()) {
        const ClipRow* r = RowAt(i);
        if (r && !(skipGroups && r->isGroup)) ids.push_back(r->id);
    }
    return ids;
}

void UpdatePreview();

void EnsureVisible(int i) {
    Layout l = CurrentLayout();
    float top = i * l.stride, bottom = top + l.rowH;
    float target = L.scrollTarget;
    if (top < target) target = top;
    else if (bottom > target + l.viewH) target = bottom - l.viewH;
    target = std::clamp(target, 0.0f, MaxScroll(l));
    if (target != L.scrollTarget) {
        L.scrollTarget = target;
        if (L.surf.hwnd && IsWindowVisible(L.surf.hwnd)) SetTimer(L.surf.hwnd, kTimerScroll, 15, nullptr);
        else L.scrollY = target;
    }
}

void SetCaret(int i, bool extend, bool toggle = false) {
    if (!L.count) return;
    i = std::clamp(i, 0, L.count - 1);
    if (toggle) {
        if (L.selAll) {
            L.sel.assign((size_t)L.count, 1);
            L.selAll = false;
        }
        L.sel[(size_t)i] = !L.sel[(size_t)i];
        L.anchor = i;
    } else {
        L.selAll = false;
        std::fill(L.sel.begin(), L.sel.end(), 0);
        if (!extend) L.anchor = i;
        int a = std::min(L.anchor, i), b = std::max(L.anchor, i);
        for (int k = a; k <= b; k++) L.sel[(size_t)k] = 1;
    }
    L.caret = i;
    EnsureVisible(i);
    UpdatePreview();
    Invalidate();
}

void SelectAll() {
    if (!L.count) return;
    L.selAll = true;
    Invalidate();
}

// ---------------------------------------------------------------------------
// Painting the list
// ---------------------------------------------------------------------------
bool ThumbRect(const Layout& l, float& top, float& height) {
    float content = L.count * l.stride - kRowGap;
    if (content <= l.viewH + 0.5f) return false;
    float track = l.scroll.bottom - l.scroll.top;
    height = std::max(24.0f, track * l.viewH / content);
    float maxScroll = MaxScroll(l);
    top = l.scroll.top + (track - height) * (maxScroll > 0 ? L.scrollY / maxScroll : 0);
    return true;
}

void PaintRow(Ctx& c, const Layout& l, int i, const ClipRow& r, D2D1_RECT_F rect, bool lifted = false) {
    bool selected = IsSel(i) && !lifted, hovered = i == L.hover && !L.dragActive && !lifted;
    float rad = (float)g_set.cornerRadius;
    if (lifted) {
        // Picked up: a soft shadow, an opaque body and a 2 px gradient ring.
        for (int k = 3; k >= 1; k--) {
            D2D1_RECT_F s{rect.left - k, rect.top - k + 3, rect.right + k, rect.bottom + k + 3};
            c.rt->FillRoundedRectangle({s, rad + k, rad + k}, c.B(mocha::crust, 0.18f));
        }
        c.rt->FillRoundedRectangle({rect, rad, rad}, c.B(mocha::mantle, 0.96f));
        c.Glow(rect, rad, 0.14f, 1.0f, 2);
    } else if (selected) {
        c.Glow(rect, rad, 0.13f, 1.0f);
    } else if (hovered) {
        c.Glow(rect, rad, 0.07f * L.hoverT, 0.55f * L.hoverT);
    }

    float top = rect.top + kRowPadY;
    if (g_set.showPositions && i < 10) {
        std::wstring num = std::to_wstring(i + 1);
        c.Text(num, T.num.get(), {rect.left, top, rect.left + l.gutter - 6, top + T.lineH},
               selected ? mocha::subtext1 : mocha::overlay1);
    }

    // Pin button: always shown on pinned rows, on hover for the rest.
    D2D1_RECT_F pin = PinRect(rect);
    bool pinHot = hovered && L.hoverHit == Hit::Pin;
    if (r.sticky || hovered || lifted) {
        if (pinHot) c.Glow(pin, rad, 0.18f * L.hoverT, 0.9f * L.hoverT);
        wchar_t g = r.sticky && pinHot ? kGlyphUnpin : kGlyphPin;
        D2D1_RECT_F gr = Inset(pin, 1, 1);
        if (r.sticky) {
            c.rt->DrawText(&g, 1, T.iconMid.get(), gr, c.BRef(g_set.accentColor), D2D1_DRAW_TEXT_OPTIONS_NONE);
        } else {
            c.rt->DrawText(&g, 1, T.iconMid.get(), gr, c.B(pinHot ? mocha::text : mocha::subtext0, lifted ? 1 : L.hoverT),
                           D2D1_DRAW_TEXT_OPTIONS_NONE);
        }
    }

    // Marks left of the pin button: never delete, has a shortcut.
    float right = pin.left - 2;
    auto mark = [&](wchar_t glyph, UINT32 color) {
        c.Glyph(glyph, {right - kMarkW, top, right, top + T.lineH}, color, true);
        right -= kMarkW + 2;
    };
    if (r.neverDelete) mark(kGlyphLock, mocha::peach);
    if (r.hasShortcut) mark(kGlyphKey, mocha::subtext0);

    float x = rect.left + l.gutter;
    float textBottom = rect.bottom - kRowPadY;
    D2D1_RECT_F textRect{x, top, right - 4, textBottom};
    switch (r.kind) {
        case ClipKind::Group: {
            c.Glyph(kGlyphFolder, {x - 1, top, x + 17, top + T.lineH}, (UINT32)0, false, 0);
            c.rt->DrawText(&kGlyphFolder, 1, T.icon.get(), {x - 1, top, x + 17, top + T.lineH},
                           c.BRef(g_set.accentColor), D2D1_DRAW_TEXT_OPTIONS_NONE);
            c.Text(r.text, T.uiBold.get(), {x + 22, top, textRect.right, top + T.lineH}, mocha::text);
            break;
        }
        case ClipKind::Image: {
            Thumb* t = g_set.showThumbnails ? GetThumb(r.id) : nullptr;
            float boxH = textBottom - top, labelX = x;
            if (t && boxH > 4) {
                ID2D1Bitmap* bmp = DeviceBitmap(c.rt, *t);
                if (bmp) {
                    D2D1_SIZE_F bs = bmp->GetSize();
                    float maxW = std::max(24.0f, (textRect.right - x) * 0.5f);
                    float k = std::min(boxH / bs.height, maxW / bs.width);
                    float dw = bs.width * k, dh = bs.height * k;
                    D2D1_RECT_F box{x, top, x + dw, top + dh};
                    Com<ID2D1BitmapBrush> bb;
                    if (SUCCEEDED(c.rt->CreateBitmapBrush(bmp, bb.put()))) {
                        bb->SetTransform(D2D1::Matrix3x2F::Scale(k, k) * D2D1::Matrix3x2F::Translation(x, top));
                        float rad = std::min(4.0f, dh / 4);
                        c.rt->FillRoundedRectangle({box, rad, rad}, bb.get());
                        c.rt->DrawRoundedRectangle({Inset(box, 0.5f, 0.5f), rad, rad}, c.B(mocha::surface1, 0.8f), 1);
                    }
                    labelX = box.right + 10;
                }
            }
            std::wstring label = L"Image";
            if (t && t->w) label += L"  " + std::to_wstring(t->w) + L" \u00D7 " + std::to_wstring(t->h);
            c.Text(label, T.row.get(), {labelX, top, textRect.right, top + T.lineH}, mocha::subtext0);
            break;
        }
        case ClipKind::Files: {
            c.Glyph(kGlyphPage, {x - 1, top, x + 15, top + T.lineH}, mocha::subtext0, true);
            c.Text(RowLines(r.text, g_set.linesPerRow, true), T.row.get(), {x + 18, top, textRect.right, textBottom},
                   mocha::text);
            break;
        }
        default:
            c.Text(RowLines(r.text, g_set.linesPerRow, false), T.rowWrap.get(), textRect, mocha::text);
            break;
    }
}

void PaintDock(Ctx& c, const Layout& l, bool offscreen) {
    D2D1_RECT_F d = Inset(l.dock, 0.75f, 0.75f);
    float rad = (d.bottom - d.top) / 2;
    c.rt->FillRoundedRectangle({d, rad, rad}, c.B(mocha::mantle, 0.85f));
    c.rt->DrawRoundedRectangle({Inset(d, 0.75f, 0.75f), rad, rad}, c.B(mocha::overlay0, 0.65f), 1.5f);
    c.Glow(d, rad, 0.08f * L.dockHover, L.dockHover, 1.5f);
    if (L.hoverHit == Hit::Folder) c.HoverButton(l.folder, L.hoverT);
    if (L.hoverHit == Hit::Menu) c.HoverButton(l.menu, L.hoverT);
    c.Glyph(kGlyphFolder, l.folder, mocha::text);
    c.Glyph(kGlyphMore, l.menu, mocha::text);

    D2D1_RECT_F s = l.search;
    float sr = (s.bottom - s.top) / 2;
    bool confirm = L.mode == DockMode::ConfirmDelete;
    (void)sr;
    (void)confirm;
    D2D1_RECT_F inner{s.left + 12, s.top, s.right - 12, s.bottom};

    std::wstring hint;
    std::wstring value;
    std::wstring placeholder;
    UINT32 valueColor = mocha::text;
    bool caret = false;
    switch (L.mode) {
        case DockMode::ConfirmDelete:
            value = L.confirmCount == 1 ? L"Delete this clip?" : L"Delete " + std::to_wstring(L.confirmCount) + L" clips?";
            valueColor = mocha::red;
            hint = L"Enter yes, Esc no";
            break;
        case DockMode::NewGroup:
            value = L.nameText;
            placeholder = L"Name the new group";
            hint = L"Enter to add";
            caret = true;
            break;
        default:
            value = L.search;
            placeholder = L"Search";
            caret = true;
            if (!L.search.empty()) hint = std::to_wstring(L.count) + (L.count == 1 ? L" clip" : L" clips");
            break;
    }
    float hintW = hint.empty() ? 0 : c.TextWidth(hint, T.ui.get()) + 10;
    if (hintW > (inner.right - inner.left) * 0.5f) hintW = 0;
    if (hintW > 0) c.Text(hint, T.ui.get(), {inner.right - hintW + 10, s.top, inner.right, s.bottom}, mocha::overlay1);
    D2D1_RECT_F field{inner.left, inner.top, inner.right - hintW, inner.bottom};
    // Text caret like any edit box: blinks at the system rate while the list has focus.
    if (caret && L.mode == DockMode::ConfirmDelete) caret = false;
    if (caret && !offscreen) caret = L.focused && L.caretOn;
    float ch = std::min(18.0f, s.bottom - s.top - 6), cy = std::round((s.top + s.bottom - ch) / 2);
    auto caretBar = [&](float x) { c.rt->FillRectangle({x, cy, x + 1.5f, cy + ch}, c.B(mocha::text)); };
    if (value.empty()) {
        // The caret sits at the start, just left of the placeholder, as in a Windows search box.
        c.Text(placeholder, T.ui.get(), {field.left + 4, field.top, field.right, field.bottom}, mocha::overlay1);
        if (caret) caretBar(field.left);
    } else {
        float tw = c.TextWidth(value, T.ui.get());
        // Keep the end of long search text in view.
        float shift = std::max(0.0f, tw + 4 - (field.right - field.left));
        c.rt->PushAxisAlignedClip(field, D2D1_ANTIALIAS_MODE_ALIASED);
        Com<IDWriteTextLayout> layout;
        if (SUCCEEDED(F.dw->CreateTextLayout(value.c_str(), (UINT32)value.size(), T.ui.get(), 10000,
                                             field.bottom - field.top, layout.put()))) {
            layout->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
            c.rt->DrawTextLayout({field.left - shift, field.top}, layout.get(), c.B(valueColor));
        }
        if (caret) caretBar(field.left - shift + tw + 1);
        c.rt->PopAxisAlignedClip();
    }
}

bool PreviewVisible();

void PaintList(ID2D1RenderTarget* rt, float w, float h, bool offscreen) {
    if (!EnsureFonts()) return;
    Ctx c(rt);
    Layout l = MakeLayout(w, h);
    PaintFrame(c, w, h, offscreen);

    // Caption buttons (right column).
    if (L.hoverHit == Hit::Close) c.HoverButton(l.close, L.hoverT);
    if (L.hoverHit == Hit::Chevron) c.HoverButton(l.chevron, L.hoverT);
    c.Glyph(kGlyphClose, l.close, L.hoverHit == Hit::Close ? mocha::text : mocha::subtext0, true);
    c.Glyph(PreviewVisible() ? kGlyphChevronL : kGlyphChevronR, l.chevron,
            L.hoverHit == Hit::Chevron ? mocha::text : mocha::subtext0, true);

    // Group header.
    if (L.q.groupId != -1) {
        if (L.hoverHit == Hit::Back) c.HoverButton(l.back, L.hoverT);
        c.Glyph(kGlyphBack, l.back, mocha::text, true);
        D2D1_RECT_F fr{l.back.right + 6, l.header.top, l.back.right + 24, l.header.bottom};
        c.rt->DrawText(&kGlyphFolder, 1, T.icon.get(), fr, c.BRef(g_set.accentColor), D2D1_DRAW_TEXT_OPTIONS_NONE);
        c.Text(L.groupName.empty() ? L"Group" : L.groupName, T.uiBold.get(),
               {fr.right + 6, l.header.top, l.header.right - 4, l.header.bottom}, mocha::text);
    }

    // Rows.
    c.rt->PushAxisAlignedClip(l.list, D2D1_ANTIALIAS_MODE_ALIASED);
    if (L.count == 0) {
        std::wstring msg = !L.q.search.empty() ? L"Nothing matches \"" + L.q.search + L"\""
                           : L.q.groupId != -1 ? L"This group is empty"
                                               : L"Nothing copied yet";
        Com<IDWriteTextFormat> center = MakeFormat(T.family, g_set.fontSize * 96.0f / 72.0f,
                                                   (DWRITE_FONT_WEIGHT)BaseWeight(), false, DWRITE_TEXT_ALIGNMENT_CENTER);
        if (center) {
            center->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
            c.Text(msg, center.get(), l.list, mocha::subtext0);
        }
    } else {
        int first = std::max(0, (int)(L.scrollY / l.stride));
        int last = std::min(L.count - 1, (int)((L.scrollY + l.viewH) / l.stride));
        bool drag = L.dragActive;
        for (int i = first; i <= last; i++) {
            const ClipRow* r = RowAt(i);
            if (!r) continue;
            D2D1_RECT_F rect = RowRect(l, i);
            if (drag && i == L.dragFrom) {
                // The empty slot the lifted row came from.
                float rad = (float)g_set.cornerRadius;
                c.rt->FillRoundedRectangle({rect, rad, rad}, c.B(mocha::surface0, 0.35f));
                continue;
            }
            PaintRow(c, l, i, *r, rect);
        }
        if (drag && L.dragInsert >= 0) {
            float y = l.list.top + L.dragInsert * l.stride - L.scrollY - kRowGap / 2;
            D2D1_RECT_F line{l.list.left + 6, y - 1.5f, l.rowRight - 6, y + 1.5f};
            auto g = c.Accent(line);
            if (g) {
                c.rt->FillRoundedRectangle({line, 1.5f, 1.5f}, g.get());
                c.rt->FillEllipse({{line.left, y}, 3.5f, 3.5f}, g.get());
                c.rt->FillEllipse({{line.right, y}, 3.5f, 3.5f}, g.get());
            }
        }
    }
    c.rt->PopAxisAlignedClip();
    if (L.dragActive) {
        if (const ClipRow* r = RowAt(L.dragFrom)) {
            float top = std::clamp(L.dragY - L.dragGrab, l.list.top - l.rowH / 2, l.list.bottom - l.rowH / 2);
            D2D1_RECT_F rect{l.list.left, top, l.rowRight, top + l.rowH};
            PaintRow(c, l, L.dragFrom, *r, rect, true);
        }
    }

    // Scrollbar: the track only shows while the pointer is on it.
    float thumbTop, thumbH;
    if (ThumbRect(l, thumbTop, thumbH)) {
        bool hot = L.hoverHit == Hit::Scroll || L.dragThumb;
        float wdt = hot ? 6.0f : 4.0f, cx = (l.scroll.left + l.scroll.right) / 2;
        D2D1_RECT_F track{cx - wdt / 2, l.scroll.top, cx + wdt / 2, l.scroll.bottom};
        if (hot) c.rt->FillRoundedRectangle({track, wdt / 2, wdt / 2}, c.B(mocha::surface0, 0.9f));
        D2D1_RECT_F thumb{track.left, thumbTop, track.right, thumbTop + thumbH};
        if (L.dragThumb) c.rt->FillRoundedRectangle({thumb, wdt / 2, wdt / 2}, c.BRef(g_set.accentColor2));
        else if (hot) c.rt->FillRoundedRectangle({thumb, wdt / 2, wdt / 2}, c.BRef(g_set.accentColor));
        else c.rt->FillRoundedRectangle({thumb, wdt / 2, wdt / 2}, c.B(mocha::overlay1));
    }

    PaintDock(c, l, offscreen);
}

// ---------------------------------------------------------------------------
// Hit testing
// ---------------------------------------------------------------------------
struct HitResult {
    Hit what = Hit::None;
    int row = -1;
};

HitResult HitTest(const Layout& l, float x, float y) {
    HitResult h;
    if (In(l.close, x, y)) h.what = Hit::Close;
    else if (In(l.chevron, x, y)) h.what = Hit::Chevron;
    else if (L.q.groupId != -1 && In(l.back, x, y)) h.what = Hit::Back;
    else if (In(l.folder, x, y)) h.what = Hit::Folder;
    else if (In(l.menu, x, y)) h.what = Hit::Menu;
    else if (In(l.search, x, y)) h.what = Hit::Search;
    else if (In({l.scroll.left - 2, l.scroll.top, l.scroll.right + 1, l.scroll.bottom}, x, y)) {
        float t, th;
        if (ThumbRect(l, t, th)) h.what = Hit::Scroll;
    } else if (In(l.list, x, y) && x < l.rowRight) {
        float offset = y - l.list.top + L.scrollY;
        int i = (int)(offset / l.stride);
        if (i >= 0 && i < L.count && offset - i * l.stride < l.rowH) {
            h.what = In(PinRect(RowRect(l, i)), x, y) ? Hit::Pin : Hit::Row;
            h.row = i;
        }
    } else if (x >= l.w - kCaptionW || In(l.header, x, y) || In(l.dock, x, y)) {
        h.what = Hit::Caption;
    }
    return h;
}

// ---------------------------------------------------------------------------
// Preview popup (F3 or the > button)
// ---------------------------------------------------------------------------
struct PreviewState {
    Surface surf;
    int64_t id = 0;
    ClipKind kind = ClipKind::Text;
    std::wstring text, title;
    Com<IWICBitmap> image;
    Com<ID2D1Bitmap> bmp;
    ID2D1RenderTarget* bmpOwner = nullptr;
    float scrollY = 0;
    int width = 0;
    bool placing = false;
} P;

bool PreviewVisible() { return P.surf.hwnd && IsWindowVisible(P.surf.hwnd); }

void PaintPreview(ID2D1RenderTarget* rt, float w, float h, bool offscreen) {
    if (!EnsureFonts()) return;
    Ctx c(rt);
    PaintFrame(c, w, h, offscreen);
    D2D1_RECT_F titleRect{14, 10, w - 14, 10 + T.lineH + 4};
    c.Text(P.title, T.uiBold.get(), titleRect, mocha::subtext0);
    D2D1_RECT_F body{14, titleRect.bottom + 8, w - 14, h - 14};
    if (P.image) {
        if (P.bmpOwner != rt || !P.bmp) {
            P.bmp.reset();
            rt->CreateBitmapFromWicBitmap(P.image.get(), P.bmp.put());
            P.bmpOwner = rt;
        }
        if (P.bmp) {
            D2D1_SIZE_F bs = P.bmp->GetSize();
            float k = std::min({1.0f * (body.right - body.left) / bs.width, (body.bottom - body.top) / bs.height, 4.0f});
            float dw = bs.width * k, dh = bs.height * k;
            float x = body.left + ((body.right - body.left) - dw) / 2, y = body.top;
            rt->DrawBitmap(P.bmp.get(), {x, y, x + dw, y + dh}, 1, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
        }
        return;
    }
    Com<IDWriteTextLayout> layout;
    if (P.text.empty() ||
        FAILED(F.dw->CreateTextLayout(P.text.c_str(), (UINT32)P.text.size(), T.wrap.get(), body.right - body.left,
                                      100000, layout.put())))
        return;
    DWRITE_TEXT_METRICS m{};
    layout->GetMetrics(&m);
    P.scrollY = std::clamp(P.scrollY, 0.0f, std::max(0.0f, m.height - (body.bottom - body.top)));
    c.rt->PushAxisAlignedClip(body, D2D1_ANTIALIAS_MODE_ALIASED);
    c.rt->DrawTextLayout({body.left, body.top - P.scrollY}, layout.get(), c.B(mocha::text));
    c.rt->PopAxisAlignedClip();
}

void LoadPreviewContent() {
    const ClipRow* r = RowAt(L.caret);
    P.image.reset();
    P.bmp.reset();
    P.text.clear();
    P.scrollY = 0;
    P.id = r ? r->id : 0;
    if (!r) {
        P.title = L"Nothing selected";
        return;
    }
    P.kind = r->kind;
    if (r->kind == ClipKind::Image) {
        UINT w = 0, h = 0;
        P.image = LoadClipImage(r->id, 2048, w, h);
        P.title = L"Image  " + std::to_wstring(w) + L" \u00D7 " + std::to_wstring(h);
        if (!P.image) P.text = L"This image could not be shown.";
        return;
    }
    if (r->isGroup) {
        P.title = L"Group";
        P.text = r->text;
        return;
    }
    std::wstring text = DataText(*r);
    if (text.size() > 200000) text.resize(200000);
    std::wstring clean;
    clean.reserve(text.size());
    for (wchar_t ch : text)
        if (ch != L'\r') clean += ch == L'\t' ? std::wstring(L"    ") : std::wstring(1, ch);
    P.text = std::move(clean);
    size_t lines = 1 + std::count(P.text.begin(), P.text.end(), L'\n');
    P.title = (r->kind == ClipKind::Files ? L"Files  " : L"Text  ") + std::to_wstring(text.size()) + L" characters, " +
              std::to_wstring(lines) + (lines == 1 ? L" line" : L" lines");
}

void PlacePreview() {
    if (!P.surf.hwnd || !L.surf.hwnd || P.placing) return;
    P.placing = true;
    RECT lr;
    GetWindowRect(L.surf.hwnd, &lr);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromRect(&lr, MONITOR_DEFAULTTONEAREST), &mi);
    int w = P.width > 0 ? P.width : std::max<int>(lr.right - lr.left, MulDiv(480, GetDpiForWindow(L.surf.hwnd), 96));
    int gap = MulDiv(6, GetDpiForWindow(L.surf.hwnd), 96);
    int x = lr.right + gap;
    if (x + w > mi.rcWork.right) x = lr.left - gap - w;
    x = std::max<int>(x, mi.rcWork.left);
    SetWindowPos(P.surf.hwnd, g_set.alwaysOnTop ? HWND_TOPMOST : HWND_TOP, x, lr.top, w, lr.bottom - lr.top,
                 SWP_NOACTIVATE);
    P.placing = false;
}

void HidePreview() {
    if (P.surf.hwnd) ShowWindow(P.surf.hwnd, SW_HIDE);
    Invalidate();
}

void ShowPreview() {
    if (!P.surf.hwnd) {
        P.surf.hwnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | (g_set.alwaysOnTop ? WS_EX_TOPMOST : 0),
                                      kPreviewClass, L"Clip preview", WS_POPUP | WS_THICKFRAME, 0, 0, 100, 100,
                                      L.surf.hwnd, nullptr, g_hInstance, nullptr);
        if (!P.surf.hwnd) return;
        ApplyBackdrop(P.surf.hwnd);
    }
    LoadPreviewContent();
    PlacePreview();
    ShowWindow(P.surf.hwnd, SW_SHOWNOACTIVATE);
    InvalidateRect(P.surf.hwnd, nullptr, FALSE);
    Invalidate();
}

void TogglePreview() {
    if (PreviewVisible()) HidePreview();
    else ShowPreview();
}

void UpdatePreview() {
    if (!PreviewVisible() || IdAt(L.caret) == P.id) return;
    LoadPreviewContent();
    InvalidateRect(P.surf.hwnd, nullptr, FALSE);
}

LRESULT CALLBACK PreviewProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_NCCALCSIZE:
            return 0;  // Client area = whole window, also on the first (wParam FALSE) call.
        case WM_NCHITTEST: {
            LRESULT hit = DefWindowProcW(hwnd, msg, wp, lp);
            return hit;
        }
        case WM_SIZING: {
            auto* r = (RECT*)lp;
            RECT lr; GetWindowRect(L.surf.hwnd, &lr);
            P.width = std::max(180L, r->right - r->left);
            SetWindowPos(L.surf.hwnd, nullptr, lr.left, r->top, lr.right - lr.left, r->bottom - r->top,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            PlacePreview();
            GetWindowRect(hwnd, r);
            return TRUE;
        }
        case WM_WINDOWPOSCHANGED:
            if (!P.placing) {
                RECT r; GetWindowRect(hwnd, &r);
                P.width = r.right - r.left;
                if (PreviewVisible()) PlacePreview();
            }
            break;
        case WM_GETMINMAXINFO:
            ((MINMAXINFO*)lp)->ptMinTrackSize = {MulDiv(180, GetDpiForWindow(hwnd), 96), MulDiv(180, GetDpiForWindow(hwnd), 96)};
            return 0;
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_ERASEBKGND:
            return 1;
        case WM_SIZE:
            P.surf.Resize();
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_MOUSEWHEEL:
            P.scrollY -= GET_WHEEL_DELTA_WPARAM(wp) / 120.0f * T.lineH * 3;
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_PAINT: {
            RECT wr, cr;
            GetWindowRect(hwnd, &wr); GetClientRect(hwnd, &cr);
            if (cr.right != wr.right - wr.left || cr.bottom != wr.bottom - wr.top)
                SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            if (P.surf.Ensure()) {
                RECT rc;
                GetClientRect(hwnd, &rc);
                float s = P.surf.Scale();
                P.surf.rt->BeginDraw();
                PaintPreview(P.surf.rt.get(), rc.right / s, rc.bottom / s, false);
                if (P.surf.rt->EndDraw() == D2DERR_RECREATE_TARGET) {
                    P.surf.Discard();
                    P.bmp.reset();
                }
            }
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_DESTROY:
            P.surf.Discard();
            P.bmp.reset();
            P.surf.hwnd = nullptr;
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

// ---------------------------------------------------------------------------
// Actions
// ---------------------------------------------------------------------------
void CancelMode() {
    L.mode = DockMode::Search;
    L.nameText.clear();
    L.pendingMove.clear();
    Invalidate();
}

void OpenGroup(int64_t id, const std::wstring& name) {
    L.q.groupId = id;
    L.groupName = name;
    L.search.clear();
    L.q.search.clear();
    if (L.surf.hwnd) KillTimer(L.surf.hwnd, kTimerSearch);
    CancelMode();
    L.caret = 0;
    L.scrollY = L.scrollTarget = 0;
    Reload();
    UpdatePreview();
}

void GoUp() {
    if (L.q.groupId == -1) return;
    int64_t from = L.q.groupId, parent = -1;
    std::wstring name;
    ClipRow r;
    if (Db_GetClipRow(from, r)) parent = r.parentId;
    ClipRow pr;
    if (parent != -1 && Db_GetClipRow(parent, pr)) name = pr.text;
    OpenGroup(parent, name);
    for (int i = 0; i < std::min(L.count, 200); i++)
        if (IdAt(i) == from) {
            SetCaret(i, false);
            break;
        }
}

void CommitSearch() {
    if (L.surf.hwnd) KillTimer(L.surf.hwnd, kTimerSearch);
    if (L.q.search == L.search) return;
    L.q.search = L.search;
    L.caret = 0;
    L.scrollY = L.scrollTarget = 0;
    Reload();
    UpdatePreview();
}

void SearchChanged() {
    if (L.surf.hwnd) SetTimer(L.surf.hwnd, kTimerSearch, kSearchDelayMs, nullptr);
    Invalidate();
}

void HideListNow();

void PasteIds(const std::vector<int64_t>& ids, SpecialPaste mode) {
    if (ids.empty()) return;
    PasteRequest req;
    req.ids = ids;
    req.mode = mode;
    req.sendPaste = true;
    req.moveToTop = g_set.moveToTopOnPaste;
    req.target = g_pasteTarget;
    List_Hide();
    HideListNow();  // Focus must return to the target at once, not after the close animation.
    Paste_Request(req);
}

void PasteSelection(SpecialPaste mode) {
    const ClipRow* r = RowAt(L.caret);
    std::vector<int> sel = SelectedIndices();
    if (r && r->isGroup && sel.size() == 1) {
        int64_t id = r->id;
        std::wstring name = r->text;
        OpenGroup(id, name);
        return;
    }
    PasteIds(SelectedIds(true), mode);
}

void PastePosition(int index) {
    const ClipRow* r = RowAt(index);
    if (!r) return;
    if (r->isGroup) {
        int64_t id = r->id;
        std::wstring name = r->text;
        OpenGroup(id, name);
        return;
    }
    PasteIds({r->id}, SpecialPaste::None);
}

void CopySelection() {
    auto ids = SelectedIds(true);
    if (ids.empty()) return;
    if (ids.size() == 1) {
        Clipboard_PutClip(ids[0], SpecialPaste::None);
        return;
    }
    PasteRequest req;
    req.ids = ids;
    req.sendPaste = false;
    req.moveToTop = false;
    req.target = g_pasteTarget;
    Paste_Request(req);
}

void RequestDelete() {
    auto sel = SelectedIndices();
    if (sel.empty()) return;
    if (!g_set.confirmDelete) {
        Db_DeleteClips(SelectedIds());
        L.caret = sel.front();
        Reload();
        UpdatePreview();
        return;
    }
    L.mode = DockMode::ConfirmDelete;
    L.confirmCount = (int)sel.size();
    Invalidate();
}

void ConfirmDelete() {
    auto sel = SelectedIndices();
    std::vector<int64_t> ids = SelectedIds();
    CancelMode();
    if (ids.empty()) return;
    Db_DeleteClips(ids);
    L.caret = sel.front();
    Reload();
    UpdatePreview();
}

void StartNewGroup(bool withSelection) {
    L.mode = DockMode::NewGroup;
    L.nameText.clear();
    L.pendingMove = withSelection ? SelectedIds() : std::vector<int64_t>{};
    Invalidate();
}

void CommitNewGroup() {
    std::wstring name = L.nameText;
    auto move = L.pendingMove;
    CancelMode();
    while (!name.empty() && iswspace(name.back())) name.pop_back();
    if (name.empty()) return;
    int64_t gid = Db_CreateGroup(name, L.q.groupId);
    if (gid && !move.empty()) Db_MoveToGroup(move, gid);
    Reload();
}

void PasteIntoSearch() {
    if (!OpenClipboard(L.surf.hwnd)) return;
    if (HANDLE h = GetClipboardData(CF_UNICODETEXT)) {
        if (auto* p = (const wchar_t*)GlobalLock(h)) {
            std::wstring text = p;
            GlobalUnlock(h);
            for (wchar_t ch : text)
                if (ch >= 32) (L.mode == DockMode::NewGroup ? L.nameText : L.search) += ch;
        }
    }
    CloseClipboard();
    if (L.mode == DockMode::Search) SearchChanged();
    Invalidate();
}

void EraseLast(std::wstring& s, bool word) {
    if (s.empty()) return;
    if (!word) {
        s.pop_back();
        return;
    }
    while (!s.empty() && iswspace(s.back())) s.pop_back();
    while (!s.empty() && !iswspace(s.back())) s.pop_back();
}

// ---------------------------------------------------------------------------
// Menus
// ---------------------------------------------------------------------------
std::vector<ClipRow> g_menuGroups;

struct SpecialName {
    SpecialPaste mode;
    PCWSTR name;
};
const SpecialName kSpecialNames[] = {
    {SpecialPaste::PlainText, L"Plain text"},
    {SpecialPaste::Upper, L"UPPER CASE"},
    {SpecialPaste::Lower, L"lower case"},
    {SpecialPaste::Capitalize, L"Capitalize Each Word"},
    {SpecialPaste::Sentence, L"Sentence case"},
    {SpecialPaste::InvertCase, L"iNVERT cASE"},
    {SpecialPaste::CamelCase, L"camelCase"},
    {SpecialPaste::Slugify, L"slug-case"},
    {SpecialPaste::TrimWhitespace, L"Trim spaces"},
    {SpecialPaste::RemoveLineBreaks, L"Remove line breaks"},
    {SpecialPaste::AddLineBreak, L"Add a line break"},
    {SpecialPaste::AddTwoLineBreaks, L"Add two line breaks"},
    {SpecialPaste::Typoglycemia, L"Scramble the middle of words"},
    {SpecialPaste::AsciiOnly, L"Letters and digits only (ASCII)"},
};

// Groups as an indented tree (Db_ListGroups is sorted by name, any depth).
std::vector<std::pair<ClipRow, int>> GroupTree() {
    std::vector<ClipRow> all = Db_ListGroups();
    std::vector<std::pair<ClipRow, int>> out;
    std::function<void(int64_t, int)> walk = [&](int64_t parent, int depth) {
        if (depth > 8) return;
        for (auto& g : all)
            if (g.parentId == parent) {
                out.push_back({g, depth});
                walk(g.id, depth + 1);
            }
    };
    walk(-1, 0);
    if (out.size() < all.size()) {  // Orphans whose parent is gone
        for (auto& g : all)
            if (std::none_of(out.begin(), out.end(), [&](auto& p) { return p.first.id == g.id; })) out.push_back({g, 0});
    }
    return out;
}

UiMenuItem MI(int id, std::wstring text, wchar_t glyph = 0, std::wstring hint = {}, bool enabled = true,
              bool checked = false) {
    UiMenuItem m;
    m.id = id;
    m.text = std::move(text);
    m.glyph = glyph;
    m.hint = std::move(hint);
    m.disabled = !enabled;
    m.checked = checked;
    return m;
}

UiMenuItem MSep() {
    UiMenuItem m;
    m.separator = true;
    return m;
}

UiMenuItem MSub(std::wstring text, wchar_t glyph, std::vector<UiMenuItem> sub, bool enabled = true) {
    UiMenuItem m;
    m.text = std::move(text);
    m.glyph = glyph;
    m.sub = std::move(sub);
    m.disabled = !enabled;
    return m;
}

void AddGroupItems(std::vector<UiMenuItem>& out, int base, int64_t current) {
    g_menuGroups.clear();
    for (auto& [g, depth] : GroupTree()) {
        std::wstring label = std::wstring(depth * 2, L' ') + g.text;
        out.push_back(MI(base + (int)g_menuGroups.size(), label, kGlyphFolder, {}, true, g.id == current));
        g_menuGroups.push_back(g);
    }
}

// ---------------------------------------------------------------------------
// Popup menu: one custom Direct2D window per level, styled like the taskbar menu.
// ---------------------------------------------------------------------------
constexpr float kMenuPad = 6, kMenuIconW = 22, kMenuSepH = 9, kMenuOverlap = 3, kMenuMinW = 190, kMenuMaxW = 440;
constexpr UINT_PTR kTimerMenuSub = 6, kTimerMenuFade = 7;
constexpr UINT kMenuSubDelayMs = 200, kMenuFadeMs = 90;

struct MenuLevel {
    const std::vector<UiMenuItem>* items = nullptr;
    HWND hwnd = nullptr;
    Surface surf;
    float scale = 1, wDip = 0, hDip = 0, itemH = 28, hintW = 0;
    std::vector<float> top, height;  // Per item, DIPs inside the window.
    int hover = -1;                  // Highlighted item.
    int open = -1;                   // Item whose submenu is the next level.
};

struct MenuSession {
    std::vector<std::unique_ptr<MenuLevel>> levels;
    int result = 0;
    bool done = false;
    float alpha = 1;
    ULONGLONG fadeStart = 0;
    int pendingLevel = -1, pendingItem = -1;  // Hover timer: open (item >= 0) or close the submenu after a delay.
    bool pressed = false;  // A button went down inside the menu; only then does a release pick an item.
} * g_menu;

bool MenuSelectable(const UiMenuItem& m) { return !m.separator && !m.disabled; }

void MenuLayout(MenuLevel& lv, float scale) {
    const auto& items = *lv.items;
    lv.scale = scale;
    lv.itemH = std::max(30.0f, T.lineH + 12);
    lv.top.assign(items.size(), 0);
    lv.height.assign(items.size(), 0);
    float textW = 0, hintW = 0, y = kMenuPad;
    for (size_t i = 0; i < items.size(); i++) {
        lv.top[i] = y;
        lv.height[i] = items[i].separator ? kMenuSepH : lv.itemH;
        y += lv.height[i];
        textW = std::max(textW, MeasureText(items[i].text, T.ui.get()));
        hintW = std::max(hintW, MeasureText(items[i].hint, T.ui.get()));
    }
    lv.hintW = std::ceil(hintW);
    float w = kMenuPad * 2 + 8 + kMenuIconW + 10 + std::ceil(textW) + (hintW > 0 ? 24 + lv.hintW : 0) + 10 + 20 + 8;
    lv.wDip = std::ceil(std::clamp(w, kMenuMinW, kMenuMaxW));
    lv.hDip = std::ceil(y + kMenuPad);
}

int MenuItemAt(const MenuLevel& lv, float x, float y) {
    if (x < kMenuPad || x >= lv.wDip - kMenuPad) return -1;
    for (size_t i = 0; i < lv.top.size(); i++)
        if (y >= lv.top[i] && y < lv.top[i] + lv.height[i]) return (*lv.items)[i].separator ? -1 : (int)i;
    return -1;
}

// Next enabled item from `from` in direction dir (+1 or -1), wrapping. -1 when none.
int MenuNext(const MenuLevel& lv, int from, int dir) {
    int n = (int)lv.items->size();
    if (!n) return -1;
    int i = from;
    if (i < 0) i = dir > 0 ? -1 : n;
    for (int k = 0; k < n; k++) {
        i = ((i + dir) % n + n) % n;
        if (MenuSelectable((*lv.items)[(size_t)i])) return i;
    }
    return -1;
}

D2D1_RECT_F MenuItemRect(const MenuLevel& lv, size_t i) {
    return {kMenuPad, lv.top[i], lv.wDip - kMenuPad, lv.top[i] + lv.height[i]};
}

// `offscreen` stands in for DWM: round the fill and add the wallpaper wash behind it.
void PaintMenu(ID2D1RenderTarget* rt, const MenuLevel& lv, bool offscreen) {
    if (!EnsureFonts()) return;
    Ctx c(rt);
    float w = lv.wDip, h = lv.hDip, rad = SystemCornerRadius(false);
    float a = std::max(TintAlpha(), 0.80f);
    auto tint = c.Gradient({0, 0}, {0, h}, D2DColor(mocha::base, a), D2DColor(mocha::base, std::min(1.0f, a + 0.04f)));
    if (offscreen) {
        D2D1_ROUNDED_RECT body{{0, 0, w, h}, rad, rad};
        auto wash = c.Gradient({0, 0}, {w, h}, D2DColor(mocha::surface1), D2DColor(mocha::base));
        if (g_set.blurMode != L"none" && wash) rt->FillRoundedRectangle(body, wash.get());
        if (tint) rt->FillRoundedRectangle(body, tint.get());
    } else if (tint) {
        rt->FillRectangle({0, 0, w, h}, tint.get());
    }
    const auto& items = *lv.items;
    float slotRight = w - kMenuPad - 8, slotLeft = slotRight - 20;
    for (size_t i = 0; i < items.size(); i++) {
        const UiMenuItem& m = items[i];
        D2D1_RECT_F r = MenuItemRect(lv, i);
        if (m.separator) {
            float y = std::floor((r.top + r.bottom) / 2);
            rt->FillRectangle({r.left + 8, y, r.right - 8, y + 1}, c.B(mocha::surface1, 0.8f));
            continue;
        }
        bool hot = ((int)i == lv.hover || (int)i == lv.open) && !m.disabled;
        if (hot) c.Glow(r, (float)g_set.cornerRadius, 0.16f, 0.8f);
        UINT32 col = m.disabled ? mocha::overlay0 : mocha::text;
        if (m.glyph) c.Glyph(m.glyph, {r.left + 8, r.top, r.left + 8 + kMenuIconW, r.bottom}, col);
        float textX = r.left + 8 + kMenuIconW + 10;
        float hintLeft = lv.hintW > 0 ? slotLeft - 8 - lv.hintW : slotLeft - 8;
        c.Text(m.text, T.ui.get(), {textX, r.top, hintLeft - 8, r.bottom}, col);
        if (!m.hint.empty()) c.Text(m.hint, T.uiRight.get(), {hintLeft, r.top, slotLeft - 8, r.bottom}, m.disabled ? mocha::overlay0 : mocha::subtext0);
        if (!m.sub.empty()) {
            c.Glyph(kGlyphChevronR, {slotLeft, r.top, slotRight, r.bottom}, col, true);
        } else if (m.checked) {
            rt->DrawText(&kGlyphCheck, 1, T.icon.get(), {slotLeft, r.top, slotRight, r.bottom}, c.BRef(g_set.accentColor),
                         D2D1_DRAW_TEXT_OPTIONS_NONE);
        }
    }
    // The border is always ours: Seamless Borders does not ring popups.
    D2D1_RECT_F edge{kBorderW / 2, kBorderW / 2, w - kBorderW / 2, h - kBorderW / 2};
    auto border = c.Accent(edge);
    float r2 = rad - kBorderW / 2;
    if (border) rt->DrawRoundedRectangle({edge, r2, r2}, border.get(), kBorderW);
}

// Whole-surface fade by layer opacity (the window itself stays opaque so the backdrop keeps working).
struct FadeLayer {
    ID2D1RenderTarget* rt;
    bool on = false;
    Com<ID2D1Layer> layer;
    FadeLayer(ID2D1RenderTarget* r, float alpha) : rt(r) {
        if (alpha < 0.999f && SUCCEEDED(rt->CreateLayer(nullptr, layer.put()))) {
            rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), nullptr, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
                                                D2D1::IdentityMatrix(), std::max(0.0f, alpha)),
                          layer.get());
            on = true;
        }
    }
    ~FadeLayer() {
        if (on) rt->PopLayer();
    }
};

bool Animate() {
    BOOL enabled = TRUE;
    SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &enabled, 0);
    return g_set.animations && enabled;
}

int MenuIndexOf(HWND h) {
    if (g_menu)
        for (size_t i = 0; i < g_menu->levels.size(); i++)
            if (g_menu->levels[i]->hwnd == h) return (int)i;
    return -1;
}

void MenuInvalidate() {
    if (g_menu)
        for (auto& lv : g_menu->levels)
            if (lv->hwnd) InvalidateRect(lv->hwnd, nullptr, FALSE);
}

void MenuCloseFrom(size_t n) {
    if (!g_menu) return;
    while (g_menu->levels.size() > n) {
        HWND h = g_menu->levels.back()->hwnd;
        g_menu->levels.back()->surf.Discard();
        g_menu->levels.pop_back();
        if (h) DestroyWindow(h);
    }
    if (n > 0 && !g_menu->levels.empty()) g_menu->levels.back()->open = -1;
    MenuInvalidate();
}

void MenuFinish(int id) {
    if (!g_menu || g_menu->done) return;
    g_menu->result = id;
    g_menu->done = true;
}

LRESULT CALLBACK MenuProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

HWND MenuCreateWindow(MenuLevel& lv, int x, int y, bool root) {
    int w = (int)std::ceil(lv.wDip * lv.scale), h = (int)std::ceil(lv.hDip * lv.scale);
    DWORD ex = WS_EX_TOOLWINDOW | WS_EX_TOPMOST | (root ? 0 : WS_EX_NOACTIVATE);
    HWND hw = CreateWindowExW(ex, kScmMenuClass, L"", WS_POPUP, x, y, w, h, nullptr, nullptr, g_hInstance, nullptr);
    if (!hw) return nullptr;
    lv.hwnd = hw;
    lv.surf.hwnd = hw;
    ApplyBackdrop(hw);
    return hw;
}

RECT MenuWorkArea(POINT pt) {
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST), &mi);
    return mi.rcWork;
}

// Top-left of a root menu opened at pt: flips to the left or above the point when it would run off the monitor.
POINT MenuRootOrigin(POINT pt, int w, int h) {
    RECT wa = MenuWorkArea(pt);
    int x = pt.x, y = pt.y;
    if (x + w > wa.right) x = pt.x - w;
    if (y + h > wa.bottom) y = pt.y - h;
    x = std::clamp<int>(x, wa.left, std::max<int>(wa.left, wa.right - w));
    y = std::clamp<int>(y, wa.top, std::max<int>(wa.top, wa.bottom - h));
    return {x, y};
}

// A submenu sits beside its parent, level with the item; left of the parent if the right side is full.
POINT MenuSubOrigin(const RECT& parent, int itemTopPx, int padPx, int w, int h) {
    RECT wa = MenuWorkArea({parent.right, parent.top + itemTopPx});
    int overlap = (int)kMenuOverlap;
    int x = parent.right - overlap;
    if (x + w > wa.right) x = parent.left - w + overlap;
    int y = parent.top + itemTopPx - padPx;
    if (y + h > wa.bottom) y = wa.bottom - h;
    x = std::clamp<int>(x, wa.left, std::max<int>(wa.left, wa.right - w));
    y = std::clamp<int>(y, wa.top, std::max<int>(wa.top, wa.bottom - h));
    return {x, y};
}

void MenuOpenSub(size_t level, int item, bool keyboard) {
    if (!g_menu || level >= g_menu->levels.size()) return;
    MenuLevel& parent = *g_menu->levels[level];
    const UiMenuItem& m = (*parent.items)[(size_t)item];
    if (m.sub.empty() || m.disabled) return;
    MenuCloseFrom(level + 1);
    auto lv = std::make_unique<MenuLevel>();
    lv->items = &m.sub;
    MenuLayout(*lv, parent.scale);
    RECT pr{};
    GetWindowRect(parent.hwnd, &pr);
    int w = (int)std::ceil(lv->wDip * lv->scale), h = (int)std::ceil(lv->hDip * lv->scale);
    POINT o = MenuSubOrigin(pr, (int)(parent.top[(size_t)item] * parent.scale), (int)(kMenuPad * parent.scale), w, h);
    if (keyboard) lv->hover = MenuNext(*lv, -1, +1);
    MenuLevel* raw = lv.get();
    g_menu->levels.push_back(std::move(lv));
    parent.open = item;
    if (!MenuCreateWindow(*raw, o.x, o.y, false)) {
        MenuCloseFrom(level + 1);
        return;
    }
    ShowWindow(raw->hwnd, SW_SHOWNOACTIVATE);
    MenuInvalidate();
}

void MenuActivate(size_t level, int item, bool keyboard) {
    if (!g_menu || level >= g_menu->levels.size()) return;
    const UiMenuItem& m = (*g_menu->levels[level]->items)[(size_t)item];
    if (!MenuSelectable(m)) return;
    if (!m.sub.empty()) MenuOpenSub(level, item, keyboard);
    else MenuFinish(m.id);
}

void MenuHoverChanged(size_t level, int item) {
    if (!g_menu) return;
    MenuLevel& lv = *g_menu->levels[level];
    HWND root = g_menu->levels[0]->hwnd;
    KillTimer(root, kTimerMenuSub);
    g_menu->pendingItem = -1;
    bool wantsSub = item >= 0 && MenuSelectable((*lv.items)[(size_t)item]) && !(*lv.items)[(size_t)item].sub.empty();
    if (wantsSub && lv.open != item) {
        g_menu->pendingLevel = (int)level;
        g_menu->pendingItem = item;
        SetTimer(root, kTimerMenuSub, kMenuSubDelayMs, nullptr);
    } else if (!wantsSub && lv.open != -1 && g_menu->levels.size() > level + 1) {
        g_menu->pendingLevel = (int)level;
        g_menu->pendingItem = -1;
        SetTimer(root, kTimerMenuSub, kMenuSubDelayMs, nullptr);
    }
}

void MenuKey(WPARAM vk) {
    if (!g_menu || g_menu->levels.empty()) return;
    size_t li = g_menu->levels.size() - 1;
    MenuLevel& cur = *g_menu->levels[li];
    const auto& items = *cur.items;
    switch (vk) {
        case VK_DOWN: cur.hover = MenuNext(cur, cur.hover, +1); break;
        case VK_UP: cur.hover = MenuNext(cur, cur.hover, -1); break;
        case VK_HOME: cur.hover = MenuNext(cur, -1, +1); break;
        case VK_END: cur.hover = MenuNext(cur, (int)items.size(), -1); break;
        case VK_RIGHT:
            if (cur.hover >= 0 && !items[(size_t)cur.hover].sub.empty()) MenuActivate(li, cur.hover, true);
            break;
        case VK_LEFT:
            if (li > 0) MenuCloseFrom(li);
            break;
        case VK_RETURN:
        case VK_SPACE:
            if (cur.hover >= 0) MenuActivate(li, cur.hover, true);
            break;
        case VK_ESCAPE:
            if (li > 0) MenuCloseFrom(li);
            else MenuFinish(0);
            break;
        default: return;
    }
    MenuInvalidate();
}

void MenuFadeTick() {
    if (!g_menu || g_menu->levels.empty()) return;
    float t = std::min(1.0f, (GetTickCount64() - g_menu->fadeStart) / (float)kMenuFadeMs);
    g_menu->alpha = 1 - (1 - t) * (1 - t);
    if (t >= 1) KillTimer(g_menu->levels[0]->hwnd, kTimerMenuFade);
    MenuInvalidate();
}

LRESULT CALLBACK MenuProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    int li = MenuIndexOf(hwnd);
    if (!g_menu || li < 0) return DefWindowProcW(hwnd, msg, wp, lp);
    MenuLevel& lv = *g_menu->levels[(size_t)li];
    switch (msg) {
        case WM_ERASEBKGND: return 1;
        case WM_MOUSEACTIVATE: return li == 0 ? MA_ACTIVATE : MA_NOACTIVATE;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            if (lv.surf.Ensure()) {
                lv.surf.rt->SetDpi(96 * lv.scale, 96 * lv.scale);
                lv.surf.rt->BeginDraw();
                lv.surf.rt->Clear(D2D1::ColorF(0, 0, 0, 0));
                {
                    FadeLayer fade(lv.surf.rt.get(), g_menu->alpha);
                    PaintMenu(lv.surf.rt.get(), lv, false);
                }
                if (lv.surf.rt->EndDraw() == D2DERR_RECREATE_TARGET) lv.surf.Discard();
            }
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (g_menu->pendingLevel > li) {  // The pointer reached a deeper level: stop the timer.
                KillTimer(g_menu->levels[0]->hwnd, kTimerMenuSub);
                g_menu->pendingItem = -1;
                g_menu->pendingLevel = -1;
            }
            TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
            TrackMouseEvent(&tme);
            int i = MenuItemAt(lv, GET_X_LPARAM(lp) / lv.scale, GET_Y_LPARAM(lp) / lv.scale);
            if (i >= 0 && !MenuSelectable((*lv.items)[(size_t)i])) i = -1;
            if (i != lv.hover) {
                lv.hover = i;
                MenuHoverChanged((size_t)li, i);
                MenuInvalidate();
            }
            return 0;
        }
        case WM_MOUSELEAVE:
            if (lv.hover != -1 && lv.open != lv.hover) {
                lv.hover = -1;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        case WM_LBUTTONUP:
        case WM_RBUTTONUP: {
            if (!g_menu->pressed) return 0;  // The release of the click that opened the menu.
            int i = MenuItemAt(lv, GET_X_LPARAM(lp) / lv.scale, GET_Y_LPARAM(lp) / lv.scale);
            if (i >= 0) MenuActivate((size_t)li, i, false);
            return 0;
        }
        case WM_ACTIVATE:
            if (LOWORD(wp) == WA_INACTIVE && li == 0 && MenuIndexOf((HWND)lp) < 0) MenuFinish(0);
            return 0;
        case WM_TIMER:
            if (wp == kTimerMenuSub) {
                KillTimer(hwnd, kTimerMenuSub);
                int pl = g_menu->pendingLevel, pi = g_menu->pendingItem;
                g_menu->pendingLevel = g_menu->pendingItem = -1;
                if (pl >= 0 && (size_t)pl < g_menu->levels.size()) {
                    if (pi >= 0) MenuOpenSub((size_t)pl, pi, false);
                    else MenuCloseFrom((size_t)pl + 1);
                }
            } else if (wp == kTimerMenuFade) {
                MenuFadeTick();
            }
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

void RegisterMenuClass() {
    WNDCLASSEXW probe{sizeof(probe)};
    if (GetClassInfoExW(g_hInstance, kScmMenuClass, &probe)) return;
    WNDCLASSEXW wc{sizeof(wc)};
    wc.hInstance = g_hInstance;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpfnWndProc = MenuProc;
    wc.lpszClassName = kScmMenuClass;
    RegisterClassExW(&wc);
}

int RunMenu(const std::vector<UiMenuItem>& items, POINT pt, HWND owner) {
    if (g_menu || items.empty() || !EnsureFactories() || !EnsureFonts()) return 0;
    RegisterMenuClass();
    MenuSession session;
    g_menu = &session;
    auto root = std::make_unique<MenuLevel>();
    root->items = &items;
    MenuLayout(*root, MonitorDpi(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST)) / 96.0f);
    int w = (int)std::ceil(root->wDip * root->scale), h = (int)std::ceil(root->hDip * root->scale);
    POINT o = MenuRootOrigin(pt, w, h);
    MenuLevel* raw = root.get();
    session.levels.push_back(std::move(root));
    if (!MenuCreateWindow(*raw, o.x, o.y, true)) {
        g_menu = nullptr;
        return 0;
    }
    if (owner && IsWindow(owner)) SetForegroundWindow(owner);  // Lets the new window take the foreground.
    bool animate = Animate();
    session.alpha = animate ? 0.0f : 1.0f;
    session.fadeStart = GetTickCount64();
    ShowWindow(raw->hwnd, SW_SHOW);
    SetForegroundWindow(raw->hwnd);
    SetFocus(raw->hwnd);
    if (animate) SetTimer(raw->hwnd, kTimerMenuFade, 15, nullptr);

    MSG m;
    while (!session.done) {
        BOOL got = GetMessageW(&m, nullptr, 0, 0);
        if (got <= 0) {
            if (got == 0) PostQuitMessage((int)m.wParam);
            break;
        }
        switch (m.message) {
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                MenuKey(m.wParam);
                continue;
            case WM_KEYUP:
            case WM_SYSKEYUP:
            case WM_CHAR:
            case WM_SYSCHAR:
                continue;
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_NCLBUTTONDOWN:
            case WM_NCRBUTTONDOWN:
                if (MenuIndexOf(m.hwnd) < 0) {  // A click on another window of ours closes the menu and is eaten.
                    MenuFinish(0);
                    continue;
                }
                session.pressed = true;
                break;
        }
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    int result = session.result;
    MenuCloseFrom(0);
    g_menu = nullptr;
    if (owner && IsWindow(owner) && IsWindowVisible(owner)) {
        SetForegroundWindow(owner);
        SetFocus(owner);
    }
    return result;
}

UINT TrackMenu(const std::vector<UiMenuItem>& items, POINT pt) {
    L.menuOpen = true;
    UINT cmd = (UINT)RunMenu(items, pt, L.surf.hwnd);
    L.menuOpen = false;
    return cmd;
}

void RunCommand(UINT cmd);

std::vector<UiMenuItem> GroupsMenuItems() {
    std::vector<UiMenuItem> items;
    items.push_back(MI(cmdOpenMain, L"All clips", kGlyphList, {}, true, L.q.groupId == -1));
    items.push_back(MSep());
    AddGroupItems(items, cmdOpenGroupBase, L.q.groupId);
    if (!g_menuGroups.empty()) items.push_back(MSep());
    items.push_back(MI(cmdNewGroup, L"New group...", kGlyphNewFolder, L"Ctrl+F7"));
    return items;
}

void ShowGroupsMenu(POINT pt) { RunCommand(TrackMenu(GroupsMenuItems(), pt)); }

std::vector<UiMenuItem> ContextMenuItems() {
    const ClipRow* r = RowAt(L.caret);
    bool have = r != nullptr;
    bool sticky = have && r->sticky, neverDelete = have && r->neverDelete, group = have && r->isGroup;
    std::vector<UiMenuItem> special;
    for (auto& s : kSpecialNames) special.push_back(MI(cmdSpecialBase + (int)s.mode, s.name));
    std::vector<UiMenuItem> move;
    AddGroupItems(move, cmdMoveGroupBase, L.q.groupId);
    if (!g_menuGroups.empty()) move.push_back(MSep());
    move.push_back(MI(cmdMoveNewGroup, L"New group...", kGlyphNewFolder, L"F7"));
    move.push_back(MI(cmdMoveOut, L"Out of group", kGlyphFolderOpen, {}, L.q.groupId != -1));
    std::vector<UiMenuItem> m;
    m.push_back(MI(cmdPaste, group ? L"Open group" : L"Paste", kGlyphPaste, L"Enter", have));
    m.push_back(MI(cmdPlain, L"Paste as plain text", kGlyphFont, L"Shift+Enter", have && !group));
    m.push_back(MSub(L"Special paste", kGlyphBolt, std::move(special), have && !group));
    m.push_back(MI(cmdCopy, L"Copy", kGlyphCopy, L"Ctrl+C", have && !group));
    m.push_back(MSep());
    m.push_back(MI(cmdEdit, L"Edit", kGlyphEdit, L"Ctrl+E", have && !group));
    m.push_back(MI(cmdProps, L"Properties", kGlyphInfo, L"Alt+Enter", have));
    m.push_back(MI(cmdPreview, L"Preview", kGlyphView, L"F3", have, PreviewVisible()));
    m.push_back(MSep());
    m.push_back(MI(cmdSticky, L"Pin to top", kGlyphPin, {}, have, sticky));
    m.push_back(MI(cmdNeverDelete, L"Never delete", kGlyphLock, {}, have, neverDelete));
    m.push_back(MSub(L"Move to group", kGlyphMoveTo, std::move(move), have));
    m.push_back(MI(cmdDelete, L"Delete", kGlyphDelete, L"Del", have));
    m.push_back(MSep());
    m.push_back(MI(cmdNewClip, L"New clip", kGlyphAdd, L"Ctrl+N"));
    m.push_back(MI(cmdPause, L"Pause saving copies", kGlyphPause, {}, true, g_capturePaused));
    m.push_back(MI(cmdSettings, L"Settings", kGlyphSettings));
    return m;
}

void ShowContextMenu(POINT pt) { RunCommand(TrackMenu(ContextMenuItems(), pt)); }

POINT MenuPointFor(const D2D1_RECT_F& r, bool above) {
    float s = L.surf.Scale();
    POINT pt{(LONG)(r.left * s), (LONG)((above ? r.top : r.bottom) * s)};
    ClientToScreen(L.surf.hwnd, &pt);
    return pt;
}

POINT CaretMenuPoint() {
    Layout l = CurrentLayout();
    float y = l.list.top + L.caret * l.stride - L.scrollY + l.rowH / 2;
    y = std::clamp(y, l.list.top, l.list.bottom);
    return MenuPointFor({l.list.left + l.gutter, y, l.list.left + l.gutter, y}, false);
}

void RunCommand(UINT cmd) {
    if (!cmd) return;
    int64_t id = IdAt(L.caret);
    if (cmd >= cmdOpenGroupBase && cmd - cmdOpenGroupBase < g_menuGroups.size()) {
        auto g = g_menuGroups[cmd - cmdOpenGroupBase];
        OpenGroup(g.id, g.text);
        return;
    }
    if (cmd >= cmdMoveGroupBase && cmd - cmdMoveGroupBase < g_menuGroups.size()) {
        Db_MoveToGroup(SelectedIds(), g_menuGroups[cmd - cmdMoveGroupBase].id);
        Reload();
        return;
    }
    if (cmd >= cmdSpecialBase && cmd < cmdSpecialBase + 64) {
        PasteSelection((SpecialPaste)(cmd - cmdSpecialBase));
        return;
    }
    switch (cmd) {
        case cmdPaste: PasteSelection(SpecialPaste::None); break;
        case cmdPlain: PasteSelection(SpecialPaste::PlainText); break;
        case cmdCopy: CopySelection(); break;
        case cmdEdit: if (id) Editor_Open(id); break;
        case cmdProps: if (id) Props_Open(id); break;
        case cmdPreview: TogglePreview(); break;
        case cmdSticky: {
            const ClipRow* r = RowAt(L.caret);
            if (r) DataSetSticky(r->id, !r->sticky, L.q.groupId != -1);
            Reload();
            break;
        }
        case cmdNeverDelete: {
            const ClipRow* r = RowAt(L.caret);
            if (r) Db_SetNeverDelete(r->id, !r->neverDelete);
            Reload();
            break;
        }
        case cmdMoveNewGroup: StartNewGroup(true); break;
        case cmdMoveOut: Db_MoveToGroup(SelectedIds(), -1); Reload(); break;
        case cmdDelete: RequestDelete(); break;
        case cmdNewClip: Editor_Open(0); break;
        case cmdPause:
            g_capturePaused = !g_capturePaused;
            Tray_Update();
            break;
        case cmdSettings:
            List_Hide();
            PostMessageW(g_msgWnd, WM_SCM_OPEN_SETTINGS, 0, 0);
            break;
        case cmdOpenMain: OpenGroup(-1, L""); break;
        case cmdNewGroup: StartNewGroup(false); break;
        default: break;
    }
}

// ---------------------------------------------------------------------------
// Keyboard and mouse
// ---------------------------------------------------------------------------
bool Down(int vk) { return GetKeyState(vk) < 0; }

int PageRows() {
    Layout l = CurrentLayout();
    return std::max(1, (int)(l.viewH / l.stride));
}

void EndDrag();

bool OnKeyDown(WPARAM vk) {
    bool ctrl = Down(VK_CONTROL), shift = Down(VK_SHIFT), alt = Down(VK_MENU);
    if (L.dragPending || L.dragActive) {
        if (vk == VK_ESCAPE) EndDrag();
        return true;
    }
    if (L.mode == DockMode::ConfirmDelete) {
        if (vk == VK_RETURN) ConfirmDelete();
        else if (vk == VK_ESCAPE) CancelMode();
        return vk == VK_RETURN || vk == VK_ESCAPE;
    }
    if (L.mode == DockMode::NewGroup) {
        switch (vk) {
            case VK_RETURN: CommitNewGroup(); return true;
            case VK_ESCAPE: CancelMode(); return true;
            case VK_BACK: EraseLast(L.nameText, ctrl); Invalidate(); return true;
            case 'V': if (ctrl) { PasteIntoSearch(); return true; } return false;
            default: return false;
        }
    }
    if (ctrl && ((vk >= '0' && vk <= '9') || (vk >= VK_NUMPAD0 && vk <= VK_NUMPAD9))) {
        int d = vk >= VK_NUMPAD0 ? (int)(vk - VK_NUMPAD0) : (int)(vk - '0');
        PastePosition(d == 0 ? 9 : d - 1);
        return true;
    }
    switch (vk) {
        case VK_UP: SetCaret(L.caret - 1, shift); return true;
        case VK_DOWN: SetCaret(L.caret + 1, shift); return true;
        case VK_PRIOR: SetCaret(L.caret - PageRows(), shift); return true;
        case VK_NEXT: SetCaret(L.caret + PageRows(), shift); return true;
        case VK_HOME: SetCaret(0, shift); return true;
        case VK_END: SetCaret(L.count - 1, shift); return true;
        case VK_RETURN:
            if (alt) RunCommand(cmdProps);
            else PasteSelection(shift ? SpecialPaste::PlainText : SpecialPaste::None);
            return true;
        case VK_ESCAPE:
            if (shift) List_Hide();
            else if (!L.search.empty()) {
                L.search.clear();
                CommitSearch();
                Invalidate();
            } else List_Hide();
            return true;
        case VK_DELETE: RequestDelete(); return true;
        case VK_BACK:
            if (!L.search.empty()) {
                EraseLast(L.search, ctrl);
                SearchChanged();
            } else GoUp();
            return true;
        case VK_F3: TogglePreview(); return true;
        case VK_F5: Reload(); return true;
        case VK_F7: StartNewGroup(!ctrl); return true;
        case VK_APPS: ShowContextMenu(CaretMenuPoint()); return true;
        case VK_F10:
            if (shift) {
                ShowContextMenu(CaretMenuPoint());
                return true;
            }
            return false;
        default: break;
    }
    if (!ctrl || alt) return false;
    switch (vk) {
        case 'A': SelectAll(); return true;
        case 'C': CopySelection(); return true;
        case 'E': RunCommand(cmdEdit); return true;
        case 'G': ShowGroupsMenu(MenuPointFor(CurrentLayout().folder, false)); return true;
        case 'N': RunCommand(cmdNewClip); return true;
        case 'V': PasteIntoSearch(); return true;
        default: return false;
    }
}

void OnChar(wchar_t ch) {
    bool ctrl = Down(VK_CONTROL), alt = Down(VK_MENU);
    if (ch < 32 || ch == 127 || (ctrl != alt)) return;  // Ctrl+Alt is AltGr: keep those characters.
    if (L.mode == DockMode::ConfirmDelete) {
        if (ch == L'y' || ch == L'Y') ConfirmDelete();
        else if (ch == L'n' || ch == L'N') CancelMode();
        return;
    }
    if (L.mode == DockMode::NewGroup) {
        L.nameText += ch;
        Invalidate();
        return;
    }
    // Ditto: with an empty search, the number keys paste that position.
    if (L.search.empty() && ch >= L'0' && ch <= L'9') {
        PastePosition(ch == L'0' ? 9 : ch - L'1');
        return;
    }
    L.search += ch;
    SearchChanged();
}

void ScrollTo(float target, bool animate) {
    Layout l = CurrentLayout();
    L.scrollTarget = std::clamp(target, 0.0f, MaxScroll(l));
    if (animate && L.surf.hwnd && IsWindowVisible(L.surf.hwnd)) {
        SetTimer(L.surf.hwnd, kTimerScroll, 15, nullptr);
    } else {
        L.scrollY = L.scrollTarget;
        Invalidate();
    }
}

void DragThumb(float y) {
    Layout l = CurrentLayout();
    float t, th;
    if (!ThumbRect(l, t, th)) return;
    float track = l.scroll.bottom - l.scroll.top - th;
    float frac = track > 0 ? (y - L.dragOffset - l.scroll.top) / track : 0;
    ScrollTo(frac * MaxScroll(l), false);
}

// Pinned rows are always first, so the pinned block is the leading run of sticky rows.
int StickyRunLength() {
    int n = 0;
    while (n < L.count) {
        const ClipRow* r = RowAt(n);
        if (!r || !r->sticky) break;
        n++;
    }
    return n;
}

// Insertion slot (0..sticky) nearest to a pointer y in list DIPs.
int DragSlotAt(const Layout& l, float y) {
    int slot = (int)std::lround((y - l.list.top + L.scrollY) / l.stride);
    return std::clamp(slot, 0, L.dragSticky);
}

// New top-first id order after moving the row at `from` into insertion slot `slot`.
std::vector<int64_t> ReorderedSticky(int sticky, int from, int slot) {
    std::vector<int64_t> ids;
    for (int i = 0; i < sticky; i++) ids.push_back(IdAt(i));
    if (from < 0 || from >= sticky) return ids;
    int64_t moved = ids[(size_t)from];
    ids.erase(ids.begin() + from);
    int at = slot > from ? slot - 1 : slot;
    ids.insert(ids.begin() + std::clamp(at, 0, (int)ids.size()), moved);
    return ids;
}

void EndDrag() {
    bool had = L.dragPending || L.dragActive;
    L.dragPending = L.dragActive = false;
    L.dragFrom = L.dragInsert = -1;
    if (L.surf.hwnd) KillTimer(L.surf.hwnd, kTimerDrag);
    if (had && L.surf.hwnd && GetCapture() == L.surf.hwnd) ReleaseCapture();
    Invalidate();
}

void DropDrag() {
    if (L.dragActive && L.dragInsert >= 0) {
        std::vector<int64_t> before = ReorderedSticky(L.dragSticky, -1, 0);
        std::vector<int64_t> order = ReorderedSticky(L.dragSticky, L.dragFrom, L.dragInsert);
        EndDrag();
        if (order != before) {
            DataSetStickyOrder(order, L.q.groupId != -1);
            Reload();
        }
        return;
    }
    EndDrag();
}

void BeginHoverEase() {
    if (!L.surf.hwnd) return;
    if (Animate()) {
        L.hoverT = 0;
        L.hoverStart = GetTickCount64();
        SetTimer(L.surf.hwnd, kTimerHover, 15, nullptr);
    } else {
        L.hoverT = 1;
    }
}

void DockHover(bool hot) {
    if (hot == L.dockHot) return;
    L.dockHot = hot;
    if (Animate()) SetTimer(L.surf.hwnd, kTimerDockHover, 15, nullptr);
    else L.dockHover = hot ? 1.0f : 0.0f;
    Invalidate();
}

void DragMoved(const Layout& l, float y) {
    L.dragY = y;
    L.dragInsert = DragSlotAt(l, y);
    Invalidate();
}

void OnMouse(UINT msg, WPARAM wp, LPARAM lp) {
    float s = L.surf.Scale();
    float x = GET_X_LPARAM(lp) / s, y = GET_Y_LPARAM(lp) / s;
    Layout l = CurrentLayout();
    HitResult h = HitTest(l, x, y);
    switch (msg) {
        case WM_MOUSEMOVE: {
            DockHover(In(l.dock, x, y));
            if (L.dragThumb) {
                DragThumb(y);
                return;
            }
            if (L.dragPending && !L.dragActive && std::fabs(y - L.dragStartY) > kDragStart) {
                L.dragSticky = StickyRunLength();
                L.dragActive = L.dragFrom >= 0 && L.dragFrom < L.dragSticky;
                if (L.dragActive) SetTimer(L.surf.hwnd, kTimerDrag, 30, nullptr);
                else EndDrag();
            }
            if (L.dragActive) {
                DragMoved(l, y);
                return;
            }
            if (!L.tracking) {
                TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, L.surf.hwnd, 0};
                L.tracking = TrackMouseEvent(&tme);
            }
            int hover = h.what == Hit::Row || h.what == Hit::Pin ? h.row : -1;
            if (hover != L.hover || h.what != L.hoverHit) {
                bool rowChanged = hover != L.hover;
                L.hover = hover;
                L.hoverHit = h.what;
                if (rowChanged || L.hoverT >= 1) BeginHoverEase();
                Invalidate();
            }
            return;
        }
        case WM_LBUTTONDOWN:
            if (L.mode == DockMode::ConfirmDelete && h.what != Hit::Search) CancelMode();
            switch (h.what) {
                case Hit::Pin: {
                    const ClipRow* r = RowAt(h.row);
                    if (r) {
                        DataSetSticky(r->id, !r->sticky, L.q.groupId != -1);
                        Reload();
                    }
                    break;
                }
                case Hit::Row: {
                    SetCaret(h.row, (wp & MK_SHIFT) != 0, (wp & MK_CONTROL) != 0 && !(wp & MK_SHIFT));
                    const ClipRow* r = RowAt(h.row);
                    if (r && r->sticky && !r->isGroup && !(wp & (MK_SHIFT | MK_CONTROL))) {
                        L.dragPending = true;
                        L.dragActive = false;
                        L.dragFrom = h.row;
                        L.dragId = r->id;
                        L.dragStartY = y;
                        L.dragY = y;
                        L.dragGrab = y - RowRect(l, h.row).top;
                        SetCapture(L.surf.hwnd);
                    }
                    break;
                }
                case Hit::Scroll: {
                    float t, th;
                    if (ThumbRect(l, t, th)) {
                        if (y >= t && y < t + th) {
                            L.dragThumb = true;
                            L.dragOffset = y - t;
                            SetCapture(L.surf.hwnd);
                        } else {
                            ScrollTo(L.scrollTarget + (y < t ? -l.viewH : l.viewH), true);
                        }
                    }
                    Invalidate();
                    break;
                }
                case Hit::Close: List_Hide(); break;
                case Hit::Chevron: TogglePreview(); break;
                case Hit::Back: GoUp(); break;
                case Hit::Folder: ShowGroupsMenu(MenuPointFor(l.folder, false)); break;
                case Hit::Menu: ShowContextMenu(MenuPointFor(l.menu, false)); break;
                default: break;
            }
            return;
        case WM_LBUTTONUP:
            if (L.dragPending || L.dragActive) {
                DragMoved(l, y);
                DropDrag();
                return;
            }
            if (L.dragThumb) {
                L.dragThumb = false;
                ReleaseCapture();
                Invalidate();
            }
            return;
        case WM_LBUTTONDBLCLK:
            if (h.what == Hit::Row) {
                SetCaret(h.row, false);
                PasteSelection(SpecialPaste::None);
            }
            return;
        case WM_RBUTTONUP: {
            if (h.what == Hit::Row && !IsSel(h.row)) SetCaret(h.row, false);
            POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            ClientToScreen(L.surf.hwnd, &pt);
            ShowContextMenu(pt);
            return;
        }
        default: return;
    }
}

// ---------------------------------------------------------------------------
// The list window
// ---------------------------------------------------------------------------
void SavePlacement() {
    if (!L.surf.hwnd || IsIconic(L.surf.hwnd)) return;
    RECT r;
    GetWindowRect(L.surf.hwnd, &r);
    SetState(StateKey(L"List", L"CX").c_str(), r.right - r.left);
    SetState(StateKey(L"List", L"CY").c_str(), r.bottom - r.top);
    SetState(StateKey(L"List", L"X").c_str(), r.left);
    SetState(StateKey(L"List", L"Y").c_str(), r.top);
}

LRESULT ListHitTestNc(HWND hwnd, LPARAM lp) {
    POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
    ScreenToClient(hwnd, &pt);
    RECT rc;
    GetClientRect(hwnd, &rc);
    float s = L.surf.Scale();
    int e = (int)(6 * s);
    bool left = pt.x < e, right = pt.x >= rc.right - e, top = pt.y < e, bottom = pt.y >= rc.bottom - e;
    if (top && left) return HTTOPLEFT;
    if (top && right) return HTTOPRIGHT;
    if (bottom && left) return HTBOTTOMLEFT;
    if (bottom && right) return HTBOTTOMRIGHT;
    if (left) return HTLEFT;
    if (right) return HTRIGHT;
    if (top) return HTTOP;
    if (bottom) return HTBOTTOM;
    HitResult h = HitTest(CurrentLayout(), pt.x / s, pt.y / s);
    return h.what == Hit::Caption ? HTCAPTION : HTCLIENT;
}

// Open/close animation. The window stays opaque (no WS_EX_LAYERED, so the system backdrop keeps working);
// the Direct2D content is faded with a layer and the window is slid with SetWindowPos.
// p runs 0 (hidden) .. 1 (shown); dir is +1 opening, -1 closing, 0 idle.
struct ListAnim {
    float p = 1;
    int dir = 0;
    ULONGLONG last = 0;
    POINT home{};
} A;
constexpr float kOpenMs = 160, kCloseMs = 120, kOpenSlide = 10, kCloseSlide = 6;

float AnimEase(float p) { return 1 - (1 - p) * (1 - p) * (1 - p); }

void AnimApply() {
    if (!L.surf.hwnd) return;
    float e = AnimEase(A.p);
    float slide = (A.dir < 0 ? kCloseSlide : kOpenSlide) * (1 - e) * L.surf.Scale();
    SetWindowPos(L.surf.hwnd, nullptr, A.home.x, A.home.y + (int)std::lround(slide), 0, 0,
                 SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    Invalidate();
}

void HideListNow() {
    A.dir = 0;
    A.p = 1;
    if (!L.surf.hwnd) return;
    KillTimer(L.surf.hwnd, kTimerAnim);
    if (IsWindowVisible(L.surf.hwnd)) {
        ShowWindow(L.surf.hwnd, SW_HIDE);
        SetWindowPos(L.surf.hwnd, nullptr, A.home.x, A.home.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
}

void AnimTick() {
    ULONGLONG now = GetTickCount64();
    float dt = (float)(now - A.last);
    A.last = now;
    if (A.dir > 0) A.p = std::min(1.0f, A.p + dt / kOpenMs);
    else if (A.dir < 0) A.p = std::max(0.0f, A.p - dt / kCloseMs);
    if (A.dir < 0 && A.p <= 0) {
        HideListNow();
        return;
    }
    if (A.dir > 0 && A.p >= 1) {
        A.dir = 0;
        KillTimer(L.surf.hwnd, kTimerAnim);
    }
    AnimApply();
}

void AnimStart(int dir) {
    A.dir = dir;
    A.last = GetTickCount64();
    SetTimer(L.surf.hwnd, kTimerAnim, 15, nullptr);
}

LRESULT CALLBACK ListProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_NCCALCSIZE:
            return 0;  // Client area = whole window, also on wParam FALSE calls.
        case WM_NCHITTEST:
            return ListHitTestNc(hwnd, lp);
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT: {
            {
                RECT wr, cr;
                GetWindowRect(hwnd, &wr);
                GetClientRect(hwnd, &cr);
                if (cr.right != wr.right - wr.left || cr.bottom != wr.bottom - wr.top) {
                    Wh_Log(L"list: client %dx%d inside window %dx%d, recalculating the frame", cr.right, cr.bottom,
                           wr.right - wr.left, wr.bottom - wr.top);
                    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
                                 SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                }
            }
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            if (L.surf.Ensure()) {
                RECT rc;
                GetClientRect(hwnd, &rc);
                float s = L.surf.Scale();
                L.surf.rt->BeginDraw();
                if (A.p < 1) {
                    L.surf.rt->Clear(D2D1::ColorF(0, 0, 0, 0));
                    FadeLayer fade(L.surf.rt.get(), AnimEase(A.p));
                    PaintList(L.surf.rt.get(), rc.right / s, rc.bottom / s, false);
                } else {
                    PaintList(L.surf.rt.get(), rc.right / s, rc.bottom / s, false);
                }
                if (L.surf.rt->EndDraw() == D2DERR_RECREATE_TARGET) L.surf.Discard();
            }
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_WINDOWPOSCHANGED:
            if (PreviewVisible()) PlacePreview();
            break;
        case WM_SIZE:
            L.surf.Resize();
            ScrollTo(L.scrollTarget, false);
            Invalidate();
            return 0;
        case WM_DPICHANGED: {
            auto* r = (RECT*)lp;
            SetWindowPos(hwnd, nullptr, r->left, r->top, r->right - r->left, r->bottom - r->top,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            L.surf.Resize();
            Invalidate();
            return 0;
        }
        case WM_GETMINMAXINFO: {
            auto* mm = (MINMAXINFO*)lp;
            UINT dpi = GetDpiForWindow(hwnd);
            mm->ptMinTrackSize = {MulDiv(240, dpi, 96), MulDiv(180, dpi, 96)};
            return 0;
        }
        case WM_EXITSIZEMOVE: {
            RECT wr;
            if (GetWindowRect(hwnd, &wr)) A.home = {wr.left, wr.top};
            SavePlacement();
            if (PreviewVisible()) PlacePreview();
            return 0;
        }
        case WM_ACTIVATE:
            L.focused = LOWORD(wp) != WA_INACTIVE;
            CaretReset();
            Invalidate();
            if (LOWORD(wp) == WA_INACTIVE && g_set.closeOnFocusLoss && !L.menuOpen && A.dir >= 0) {
                HWND other = (HWND)lp;
                bool ours = other && GetWindowThreadProcessId(other, nullptr) == GetCurrentThreadId();
                if (!ours) List_Hide();
            }
            return 0;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            CaretReset();
            if (OnKeyDown(wp)) return 0;
            break;
        case WM_CHAR:
            CaretReset();
            OnChar((wchar_t)wp);
            return 0;
        case WM_SYSCHAR:
            if (wp == VK_RETURN) return 0;  // Alt+Enter: no beep
            break;
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_LBUTTONDBLCLK:
        case WM_RBUTTONUP:
            OnMouse(msg, wp, lp);
            return 0;
        case WM_MOUSELEAVE:
            DockHover(false);
            L.tracking = false;
            if (L.hover != -1 || L.hoverHit != Hit::None) {
                L.hover = -1;
                L.hoverHit = Hit::None;
                Invalidate();
            }
            return 0;
        case WM_CAPTURECHANGED:
            L.dragThumb = false;
            if (L.dragPending || L.dragActive) EndDrag();
            return 0;
        case WM_MOUSEWHEEL: {
            Layout l = CurrentLayout();
            float step = std::max(l.stride, 72.0f);
            ScrollTo(L.scrollTarget - GET_WHEEL_DELTA_WPARAM(wp) / 120.0f * step, true);
            return 0;
        }
        case WM_TIMER:
            if (wp == kTimerSearch) {
                CommitSearch();
            } else if (wp == kTimerCaret) {
                L.caretOn = !L.caretOn;
                Invalidate();
            } else if (wp == kTimerScroll) {
                float d = L.scrollTarget - L.scrollY;
                if (std::fabs(d) < 0.5f) {
                    L.scrollY = L.scrollTarget;
                    KillTimer(hwnd, kTimerScroll);
                } else {
                    L.scrollY += d * 0.35f;
                }
                Invalidate();
            } else if (wp == kTimerAnim) {
                AnimTick();
            } else if (wp == kTimerDockHover) {
                float target = L.dockHot ? 1.0f : 0.0f;
                L.dockHover += (target - L.dockHover) * 0.25f;
                if (std::fabs(target - L.dockHover) < 0.005f) {
                    L.dockHover = target;
                    KillTimer(hwnd, kTimerDockHover);
                }
                Invalidate();
            } else if (wp == kTimerHover) {
                float t = std::min(1.0f, (GetTickCount64() - L.hoverStart) / (float)kHoverEaseMs);
                L.hoverT = 1 - (1 - t) * (1 - t);
                if (t >= 1) {
                    L.hoverT = 1;
                    KillTimer(hwnd, kTimerHover);
                }
                Invalidate();
            } else if (wp == kTimerDrag) {
                if (L.dragActive) {
                    Layout l = CurrentLayout();
                    float edge = 28, speed = 0;
                    if (L.dragY < l.list.top + edge) speed = -(l.list.top + edge - L.dragY) * 0.5f;
                    else if (L.dragY > l.list.bottom - edge) speed = (L.dragY - (l.list.bottom - edge)) * 0.5f;
                    if (speed != 0) {
                        ScrollTo(L.scrollTarget + speed, false);
                        DragMoved(l, L.dragY);
                    }
                }
            }
            return 0;
        case WM_DESTROY:
            L.surf.Discard();
            L.surf.hwnd = nullptr;
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

LRESULT CALLBACK EditorProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK PropsProc(HWND, UINT, WPARAM, LPARAM);

bool g_classesRegistered;

void RegisterClasses() {
    if (g_classesRegistered) return;
    WNDCLASSEXW wc{sizeof(wc)};
    wc.hInstance = g_hInstance;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hIcon = MakeAppIcon(32);
    wc.hIconSm = MakeAppIcon(16);
    wc.style = CS_DBLCLKS;
    wc.lpfnWndProc = ListProc;
    wc.lpszClassName = kListClass;
    RegisterClassExW(&wc);
    wc.style = 0;
    wc.lpfnWndProc = PreviewProc;
    wc.lpszClassName = kPreviewClass;
    RegisterClassExW(&wc);
    wc.hbrBackground = CreateSolidBrush(RefFromRgb(mocha::base));
    wc.style = CS_DBLCLKS;  // double-click selects a word in the editor's text box
    wc.lpfnWndProc = EditorProc;
    wc.lpszClassName = kEditorClass;
    RegisterClassExW(&wc);
    wc.style = 0;
    wc.lpfnWndProc = PropsProc;
    wc.lpszClassName = kPropsClass;
    RegisterClassExW(&wc);
    g_classesRegistered = true;
}

void UnregisterClasses() {
    if (!g_classesRegistered) return;
    for (PCWSTR cls : {kListClass, kPreviewClass, kEditorClass, kPropsClass, kScmMenuClass}) {
        WNDCLASSEXW wc{sizeof(wc)};
        if (GetClassInfoExW(g_hInstance, cls, &wc)) {
            UnregisterClassW(cls, g_hInstance);
            if (wc.hIcon) DestroyIcon(wc.hIcon);
            if (wc.hIconSm && wc.hIconSm != wc.hIcon) DestroyIcon(wc.hIconSm);
            if (wc.hbrBackground) DeleteObject(wc.hbrBackground);
        }
    }
    g_classesRegistered = false;
}

// Ditto keeps "(WxH)_QuickPasteCX" style values in HKCU\Software\Ditto. Copy
// every resolution once into our own StateKey names.
void ImportDittoSizes() {
    if (GetState(L"ImportedDittoSizes", 0) != 0) return;
    HKEY key;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Ditto", 0, KEY_READ, &key) == ERROR_SUCCESS) {
        for (DWORD i = 0;; i++) {
            WCHAR name[256];
            DWORD nameLen = ARRAYSIZE(name), type = 0, value = 0, size = sizeof(value);
            LONG rc = RegEnumValueW(key, i, name, &nameLen, nullptr, &type, (BYTE*)&value, &size);
            if (rc == ERROR_NO_MORE_ITEMS) break;
            if (rc != ERROR_SUCCESS || type != REG_DWORD) continue;
            int w = 0, h = 0;
            WCHAR rest[128]{};
            if (swscanf_s(name, L"(%dx%d)_%127s", &w, &h, rest, (unsigned)ARRAYSIZE(rest)) != 3) continue;
            std::wstring field = rest, window;
            if (field.rfind(L"QuickPaste", 0) == 0) window = L"List", field = field.substr(10);
            else if (field.rfind(L"EditWnd", 0) == 0) window = L"Editor", field = field.substr(7);
            else continue;
            if (field != L"CX" && field != L"CY" && field != L"X" && field != L"Y") continue;
            WCHAR stateKey[128];
            swprintf_s(stateKey, L"%s_%dx%d_%s", window.c_str(), w, h, field.c_str());
            SetState(stateKey, (int)value);
        }
        RegCloseKey(key);
    }
    SetState(L"ImportedDittoSizes", 1);
}

bool EnsureListWindow() {
    if (L.surf.hwnd) return true;
    if (!EnsureFactories() || !EnsureFonts()) return false;
    RegisterClasses();
    ImportDittoSizes();
    DWORD ex = WS_EX_TOOLWINDOW | (g_set.alwaysOnTop ? WS_EX_TOPMOST : 0);
    L.surf.hwnd = CreateWindowExW(ex, kListClass, L"Clips", WS_POPUP | WS_THICKFRAME, -32000, -32000,
                                  MulDiv(g_set.windowWidth, (int)GetDpiForSystem(), 96),
                                  MulDiv(g_set.windowHeight, (int)GetDpiForSystem(), 96), nullptr, nullptr,
                                  g_hInstance, nullptr);
    if (!L.surf.hwnd) return false;
    ApplyBackdrop(L.surf.hwnd);
    return true;
}

void PositionList() {
    HWND hwnd = L.surf.hwnd;
    POINT cursor;
    GetCursorPos(&cursor);
    RECT caret{};
    bool haveCaret = g_set.openAt == L"caret" && g_pasteTarget && Focus_GetCaretRect(g_pasteTarget, caret);
    int rx = GetState(StateKey(L"List", L"X").c_str(), INT_MIN), ry = GetState(StateKey(L"List", L"Y").c_str(), INT_MIN);
    bool remember = g_set.openAt == L"remember" && rx != INT_MIN && ry != INT_MIN;
    POINT anchor = haveCaret ? POINT{caret.left, caret.bottom} : remember ? POINT{rx, ry} : cursor;
    HMONITOR mon = MonitorFromPoint(anchor, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(mon, &mi);
    RECT work = mi.rcWork;
    UINT dpi = MonitorDpi(mon);
    int cx = GetState(StateKey(L"List", L"CX").c_str(), 0), cy = GetState(StateKey(L"List", L"CY").c_str(), 0);
    if (cx <= 0 || cy <= 0) {
        cx = MulDiv(g_set.windowWidth, (int)dpi, 96);
        cy = MulDiv(g_set.windowHeight, (int)dpi, 96);
    }
    cx = std::min<int>(cx, work.right - work.left);
    cy = std::min<int>(cy, work.bottom - work.top);
    int x = anchor.x, y = anchor.y;
    int gap = MulDiv(4, (int)dpi, 96);
    if (haveCaret) {
        y = caret.bottom + gap;
        if (y + cy > work.bottom) y = caret.top - gap - cy;
    } else if (!remember) {
        if (x + cx > work.right) x -= cx;
        if (y + cy > work.bottom) y -= cy;
    }
    x = std::clamp<int>(x, work.left, work.right - cx);
    y = std::clamp<int>(y, work.top, work.bottom - cy);
    SetWindowPos(hwnd, g_set.alwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST, x, y, cx, cy, SWP_NOACTIVATE);
    A.home = {x, y};
}

void ResetForOpen() {
    L.q.groupId = -1;  // Ditto opens on the main list every time.
    L.groupName.clear();
    L.search.clear();
    L.q.search.clear();
    L.mode = DockMode::Search;
    L.nameText.clear();
    L.pendingMove.clear();
    L.caret = 0;
    L.hover = -1;
    L.hoverHit = Hit::None;
    L.scrollY = L.scrollTarget = 0;
    L.hideRequested = false;
    Reload();
}

// ---------------------------------------------------------------------------
// Helper windows: shared bits (GDI controls, dark colors, owner-drawn buttons)
// ---------------------------------------------------------------------------
HBRUSH g_mantleBrush;
HBRUSH MantleBrush() {
    if (!g_mantleBrush) g_mantleBrush = CreateSolidBrush(RefFromRgb(mocha::mantle));
    return g_mantleBrush;
}

HFONT MakeHFont(UINT dpi, float pt, int weight, const std::wstring& family) {
    return CreateFontW(-MulDiv((int)std::lround(pt * 10), (int)dpi, 720), 0, 0, 0, weight, FALSE, FALSE, FALSE,
                       DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH,
                       family.c_str());
}

constexpr LONG_PTR kBtnPrimary = 1, kBtnCheck = 2, kBtnChecked = 4;

LRESULT CALLBACK ButtonHoverProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR, DWORD_PTR) {
    if (msg == WM_MOUSEMOVE) {
        if (!GetPropW(hwnd, L"ScmHot")) {
            SetPropW(hwnd, L"ScmHot", (HANDLE)1);
            TRACKMOUSEEVENT track{sizeof(track), TME_LEAVE, hwnd, 0}; TrackMouseEvent(&track);
            InvalidateRect(hwnd, nullptr, FALSE);
        }
    } else if (msg == WM_MOUSELEAVE) {
        RemovePropW(hwnd, L"ScmHot");
        InvalidateRect(hwnd, nullptr, FALSE);
    } else if (msg == WM_NCDESTROY) {
        RemovePropW(hwnd, L"ScmHot");
        RemoveWindowSubclass(hwnd, ButtonHoverProc, 2);
    }
    return DefSubclassProc(hwnd, msg, wp, lp);
}

HWND MakeButton(HWND parent, int id, PCWSTR text, LONG_PTR kind) {
    HWND b = CreateWindowExW(0, L"BUTTON", text, WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_OWNERDRAW, 0, 0, 10, 10,
                             parent, (HMENU)(INT_PTR)id, g_hInstance, nullptr);
    SetWindowLongPtrW(b, GWLP_USERDATA, kind);
    SetWindowSubclass(b, ButtonHoverProc, 2, 0);
    return b;
}

bool IsChecked(HWND b) { return (GetWindowLongPtrW(b, GWLP_USERDATA) & kBtnChecked) != 0; }
void SetChecked(HWND b, bool on) {
    LONG_PTR v = GetWindowLongPtrW(b, GWLP_USERDATA);
    SetWindowLongPtrW(b, GWLP_USERDATA, on ? v | kBtnChecked : v & ~kBtnChecked);
    InvalidateRect(b, nullptr, TRUE);
}

void DrawOwnerButton(const DRAWITEMSTRUCT* d) {
    LONG_PTR kind = GetWindowLongPtrW(d->hwndItem, GWLP_USERDATA);
    HDC dc = d->hDC;
    RECT r = d->rcItem;
    UINT dpi = GetDpiForWindow(d->hwndItem);
    auto S = [&](int v) { return MulDiv(v, (int)dpi, 96); };
    HBRUSH bg = CreateSolidBrush(RefFromRgb(mocha::base));
    FillRect(dc, &r, bg);
    DeleteObject(bg);
    WCHAR text[128];
    GetWindowTextW(d->hwndItem, text, 128);
    SetBkMode(dc, TRANSPARENT);
    bool focus = (d->itemState & ODS_FOCUS) != 0, pressed = (d->itemState & ODS_SELECTED) != 0;
    if (kind & kBtnCheck) {
        int box = S(16), cy = (r.top + r.bottom) / 2;
        RECT b{r.left + S(1), cy - box / 2, r.left + S(1) + box, cy + box / 2};
        bool on = (kind & kBtnChecked) != 0;
        HBRUSH fill = CreateSolidBrush(on ? g_set.accentColor : RefFromRgb(mocha::mantle));
        HPEN pen = CreatePen(PS_SOLID, 1, on ? g_set.accentColor : focus ? g_set.accentColor : RefFromRgb(mocha::surface2));
        HGDIOBJ ob = SelectObject(dc, fill), op = SelectObject(dc, pen);
        RoundRect(dc, b.left, b.top, b.right, b.bottom, S(6), S(6));
        if (on) {
            HPEN tick = CreatePen(PS_SOLID, std::max(2, S(2)), RefFromRgb(mocha::crust));
            SelectObject(dc, tick);
            POINT pts[3] = {{b.left + box / 4, cy}, {b.left + box * 5 / 12, cy + box / 5}, {b.right - box / 4, cy - box / 5}};
            Polyline(dc, pts, 3);
            SelectObject(dc, pen);
            DeleteObject(tick);
        }
        SelectObject(dc, ob);
        SelectObject(dc, op);
        DeleteObject(fill);
        DeleteObject(pen);
        SetTextColor(dc, RefFromRgb(mocha::text));
        RECT tr{b.right + S(8), r.top, r.right, r.bottom};
        DrawTextW(dc, text, -1, &tr, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
        return;
    }
    bool primary = (kind & kBtnPrimary) != 0;
    COLORREF face = primary ? (pressed ? g_set.accentColor2 : g_set.accentColor)
                            : RefFromRgb(pressed ? mocha::surface1 : mocha::surface0);
    HBRUSH fill = CreateSolidBrush(face);
    HPEN pen = CreatePen(PS_SOLID, 1, focus ? g_set.accentColor : face);
    HGDIOBJ ob = SelectObject(dc, fill), op = SelectObject(dc, pen);
    RoundRect(dc, r.left, r.top, r.right, r.bottom, S(12), S(12));
    SelectObject(dc, ob);
    SelectObject(dc, op);
    DeleteObject(fill);
    DeleteObject(pen);
    Com<ID2D1DCRenderTarget> target;
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), (float)dpi, (float)dpi);
    if (EnsureFactories() && SUCCEEDED(F.d2d->CreateDCRenderTarget(&props, target.put())) &&
        SUCCEEDED(target->BindDC(dc, &r))) {
        target->BeginDraw();
        Ctx c(target.get());
        float scale = dpi / 96.0f;
        D2D1_RECT_F box{0, 0, (r.right - r.left) / scale, (r.bottom - r.top) / scale};
        bool hot = GetPropW(d->hwndItem, L"ScmHot") != nullptr || focus || pressed;
        target->Clear(D2DColor(mocha::base));
        target->FillRoundedRectangle({box, 6, 6}, c.B(mocha::surface0));
        c.Glow(box, 6, primary ? (hot ? 1.0f : 0.85f) : hot ? 0.20f : 0, hot ? 1.0f : 0.25f, 1.5f);
        target->EndDraw();
    }
    SetTextColor(dc, primary ? RefFromRgb(mocha::crust) : RefFromRgb(mocha::text));
    DrawTextW(dc, text, -1, &r, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

// Shared WM_CTLCOLOR* handling for the helper windows.
LRESULT CtlColor(UINT msg, WPARAM wp, LPARAM lp, HBRUSH baseBrush) {
    HDC dc = (HDC)wp;
    WCHAR cls[16]{};
    GetClassNameW((HWND)lp, cls, 16);
    bool field = msg == WM_CTLCOLOREDIT || msg == WM_CTLCOLORLISTBOX || _wcsicmp(cls, L"Edit") == 0;
    SetTextColor(dc, RefFromRgb(field ? mocha::text : mocha::subtext0));
    SetBkColor(dc, RefFromRgb(field ? mocha::mantle : mocha::base));
    return (LRESULT)(field ? MantleBrush() : baseBrush);
}

LRESULT CALLBACK FieldSubclass(HWND h, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR, DWORD_PTR) {
    if (msg == WM_KEYDOWN && GetKeyState(VK_CONTROL) < 0) {
        if (wp == 'S') {
            PostMessageW(GetAncestor(h, GA_ROOT), WM_COMMAND, IDOK, 0);
            return 0;
        }
        if (wp == 'A') {
            SendMessageW(h, EM_SETSEL, 0, -1);
            return 0;
        }
    }
    if (msg == WM_KEYDOWN && wp == VK_ESCAPE) {
        PostMessageW(GetAncestor(h, GA_ROOT), WM_COMMAND, IDCANCEL, 0);
        return 0;
    }
    if (msg == WM_CHAR && (wp == 1 || wp == 19)) return 0;  // Ctrl+A / Ctrl+S: no beep
    return DefSubclassProc(h, msg, wp, lp);
}

HWND MakeField(HWND parent, int id, DWORD style) {
    HWND e = CreateWindowExW(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | style, 0, 0, 10, 10, parent,
                             (HMENU)(INT_PTR)id, g_hInstance, nullptr);
    SetWindowTheme(e, L"DarkMode_Explorer", nullptr);
    SetWindowSubclass(e, FieldSubclass, 1, 0);
    return e;
}

HWND MakeLabel(HWND parent, PCWSTR text) {
    return CreateWindowExW(0, L"STATIC", text, WS_CHILD | WS_VISIBLE, 0, 0, 10, 10, parent, nullptr, g_hInstance,
                           nullptr);
}

void SetFontAll(HWND parent, HFONT font) {
    for (HWND c = GetWindow(parent, GW_CHILD); c; c = GetWindow(c, GW_HWNDNEXT))
        SendMessageW(c, WM_SETFONT, (WPARAM)font, TRUE);
}

// Size and center a helper window on the monitor under the cursor.
void PlaceHelper(HWND hwnd, PCWSTR stateName, int defW, int defH) {
    POINT pt;
    GetCursorPos(&pt);
    if (L.surf.hwnd && IsWindowVisible(L.surf.hwnd)) {
        RECT lr;
        GetWindowRect(L.surf.hwnd, &lr);
        pt = {(lr.left + lr.right) / 2, (lr.top + lr.bottom) / 2};
    }
    HMONITOR mon = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(mon, &mi);
    UINT dpi = MonitorDpi(mon);
    int cx = stateName ? GetState(StateKey(stateName, L"CX").c_str(), 0) : 0;
    int cy = stateName ? GetState(StateKey(stateName, L"CY").c_str(), 0) : 0;
    if (cx <= 0 || cy <= 0) {
        cx = MulDiv(defW, (int)dpi, 96);
        cy = MulDiv(defH, (int)dpi, 96);
    }
    RECT w = mi.rcWork;
    cx = std::min<int>(cx, w.right - w.left);
    cy = std::min<int>(cy, w.bottom - w.top);
    int x = std::clamp<int>(pt.x - cx / 2, w.left, w.right - cx), y = std::clamp<int>(pt.y - cy / 2, w.top, w.bottom - cy);
    SetWindowPos(hwnd, nullptr, x, y, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
}

void SaveHelperSize(HWND hwnd, PCWSTR stateName) {
    RECT r;
    if (!IsWindowVisible(hwnd) || IsIconic(hwnd) || !GetWindowRect(hwnd, &r)) return;
    SetState(StateKey(stateName, L"CX").c_str(), r.right - r.left);
    SetState(StateKey(stateName, L"CY").c_str(), r.bottom - r.top);
}

// ---------------------------------------------------------------------------
// Clip editor
// ---------------------------------------------------------------------------
struct EditorState {
    HWND hwnd = nullptr, save = nullptr, cancel = nullptr;
    Surface surf;
    HFONT uiFont = nullptr;
    int64_t id = 0;
    // The text box is drawn in Direct2D on the window itself, so the acrylic shows through it the
    // same way it does under the title bar. A child EDIT can't do that: GDI writes zero alpha.
    std::wstring text;  // LF line ends while editing
    bool lfOnly = false;  // the clip used bare LF; it is saved back that way, anything else as CRLF
    size_t caret = 0, anchor = 0;
    float wantX = -1;
    Com<IDWriteTextFormat> fmt;
    Com<IDWriteTextLayout> layout;
    bool dirty = true;
    float scrollY = 0, scrollTarget = 0, contentH = 0, dragOffset = 0;
    bool focused = false, caretOn = true, selecting = false, dragThumb = false, scrollHot = false, tracking = false;
    struct Snap {
        std::wstring text;
        size_t caret, anchor;
    };
    std::vector<Snap> undo, redo;
    int lastEdit = 0;  // 1 typing, 2 deleting: a run of either is one undo step
    // Own title bar on the same blur as the body (the system one is a darker solid band).
    int capHot = -1, capDown = -1;  // 0 minimize, 1 maximize, 2 close
    bool active = true;
} E;

constexpr float kEdCapH = 34, kEdCapBtnW = 46;

std::wstring ToCrLf(const std::wstring& s);
std::wstring FromCrLf(const std::wstring& s);

struct EditorGeometry {
    D2D1_RECT_F box, view, scroll;
};

// All in DIPs. box: the bordered field; view: where text lays out; scroll: the scrollbar lane.
EditorGeometry EditorGeo() {
    RECT rc{};
    GetClientRect(E.hwnd, &rc);
    float s = E.surf.Scale(), w = rc.right / s, h = rc.bottom / s;
    float bottom = std::max(h - 16 - 34 - 16, 16 + 48.0f);
    EditorGeometry g;
    g.box = {16, kEdCapH + 8, std::max(w - 16, 16 + 80.0f), std::max(bottom, kEdCapH + 8 + 48)};
    g.view = {g.box.left + 12, g.box.top + 10, g.box.right - 22, g.box.bottom - 10};
    g.scroll = {g.box.right - 15, g.box.top + 6, g.box.right - 5, g.box.bottom - 6};
    return g;
}

float EdViewH() {
    auto g = EditorGeo();
    return std::max(1.0f, g.view.bottom - g.view.top);
}

IDWriteTextLayout* EdLayout() {
    if (!E.dirty && E.layout) return E.layout.get();
    if (!E.fmt) return nullptr;
    auto g = EditorGeo();
    float w = std::max(1.0f, g.view.right - g.view.left);
    if (FAILED(F.dw->CreateTextLayout(E.text.c_str(), (UINT32)E.text.size(), E.fmt.get(), w, 1e6f, E.layout.put())))
        return nullptr;
    DWRITE_TEXT_METRICS m{};
    E.layout->GetMetrics(&m);
    E.contentH = m.height;
    E.dirty = false;
    return E.layout.get();
}

// Text index under a point in layout coordinates.
size_t EdHit(float x, float y) {
    auto* lay = EdLayout();
    if (!lay) return 0;
    BOOL trailing = FALSE, inside = FALSE;
    DWRITE_HIT_TEST_METRICS m{};
    lay->HitTestPoint(x, y, &trailing, &inside, &m);
    size_t i = m.textPosition;
    // Past the end of a line the hit lands on its line break: stay before it, not on the next line.
    bool lineBreak = i < E.text.size() && E.text[i] == L'\n';
    if (trailing && !lineBreak) i += m.length;
    return std::min(i, E.text.size());
}

D2D1_POINT_2F EdPos(size_t i, float* lineH = nullptr) {
    auto* lay = EdLayout();
    if (!lay) return {0, 0};
    FLOAT x = 0, y = 0;
    DWRITE_HIT_TEST_METRICS m{};
    lay->HitTestTextPosition((UINT32)std::min(i, E.text.size()), FALSE, &x, &y, &m);
    if (lineH) *lineH = m.height > 0 ? m.height : g_set.fontSize * 96.0f / 72.0f * 1.33f;
    return {x, y};
}

void EdLineBounds(size_t i, size_t& start, size_t& end) {
    start = 0;
    end = E.text.size();
    auto* lay = EdLayout();
    if (!lay) return;
    UINT32 n = 0;
    lay->GetLineMetrics(nullptr, 0, &n);
    std::vector<DWRITE_LINE_METRICS> lm(n);
    if (!n || FAILED(lay->GetLineMetrics(lm.data(), n, &n))) return;
    size_t s = 0;
    for (UINT32 k = 0; k < n; k++) {
        size_t e = s + lm[k].length;
        if (i < e || k + 1 == n) {
            start = s;
            end = e - lm[k].newlineLength;
            return;
        }
        s = e;
    }
}

size_t EdNext(size_t i) {
    size_t n = E.text.size();
    if (i >= n) return n;
    if (IS_HIGH_SURROGATE(E.text[i]) && i + 1 < n && IS_LOW_SURROGATE(E.text[i + 1])) return i + 2;
    return i + 1;
}
size_t EdPrev(size_t i) {
    if (i == 0) return 0;
    if (i >= 2 && IS_LOW_SURROGATE(E.text[i - 1]) && IS_HIGH_SURROGATE(E.text[i - 2])) return i - 2;
    return i - 1;
}
int EdClass(wchar_t ch) {
    if (ch == L'\n') return 3;
    if (iswspace(ch)) return 0;
    if (iswalnum(ch) || ch == L'_') return 1;
    return 2;
}
size_t EdWordRight(size_t i) {
    size_t n = E.text.size();
    if (i >= n) return n;
    int c = EdClass(E.text[i]);
    if (c == 3) return i + 1;
    while (i < n && EdClass(E.text[i]) == c) i++;
    while (i < n && EdClass(E.text[i]) == 0) i++;
    return i;
}
size_t EdWordLeft(size_t i) {
    while (i > 0 && EdClass(E.text[i - 1]) == 0) i--;
    if (i == 0) return 0;
    int c = EdClass(E.text[i - 1]);
    if (c == 3) return i - 1;
    while (i > 0 && EdClass(E.text[i - 1]) == c) i--;
    return i;
}

void EdCaretTimer() {
    UINT blink = GetCaretBlinkTime();
    E.caretOn = true;
    if (E.focused && blink && blink != INFINITE) SetTimer(E.hwnd, kTimerCaret, blink, nullptr);
    else KillTimer(E.hwnd, kTimerCaret);
}

void EdScrollTo(float target, bool instant) {
    EdLayout();
    float maxS = std::max(0.0f, E.contentH - EdViewH());
    E.scrollTarget = std::clamp(target, 0.0f, maxS);
    if (instant) {
        E.scrollY = E.scrollTarget;
        KillTimer(E.hwnd, kTimerScroll);
    } else if (std::fabs(E.scrollTarget - E.scrollY) >= 0.5f) {
        SetTimer(E.hwnd, kTimerScroll, 15, nullptr);
    }
    E.scrollY = std::clamp(E.scrollY, 0.0f, maxS);
    InvalidateRect(E.hwnd, nullptr, FALSE);
}

void EdReveal() {
    float lh = 0;
    auto p = EdPos(E.caret, &lh);
    float vh = EdViewH(), t = E.scrollTarget;
    if (p.y < t) t = p.y;
    else if (p.y + lh > t + vh) t = p.y + lh - vh;
    if (t != E.scrollTarget) EdScrollTo(t, false);
}

void EdChanged() {
    E.dirty = true;
    E.wantX = -1;
    EdCaretTimer();
    EdScrollTo(E.scrollTarget, false);  // the text may have got shorter
    EdReveal();
    InvalidateRect(E.hwnd, nullptr, FALSE);
}

void EdMove(size_t to, bool extend) {
    E.caret = std::min(to, E.text.size());
    if (!extend) E.anchor = E.caret;
    E.wantX = -1;
    E.lastEdit = 0;
    EdCaretTimer();
    EdReveal();
    InvalidateRect(E.hwnd, nullptr, FALSE);
}

void EdReplace(const std::wstring& s, int kind) {
    size_t a = std::min(E.caret, E.anchor), b = std::max(E.caret, E.anchor);
    if (a == b && s.empty()) return;
    if (kind == 0 || kind != E.lastEdit) {
        E.undo.push_back({E.text, E.caret, E.anchor});
        if (E.undo.size() > 300) E.undo.erase(E.undo.begin());
    }
    E.lastEdit = kind;
    E.redo.clear();
    E.text.replace(a, b - a, s);
    E.caret = E.anchor = a + s.size();
    EdChanged();
}

void EdUndo(bool redo) {
    auto& from = redo ? E.redo : E.undo;
    auto& to = redo ? E.undo : E.redo;
    if (from.empty()) return;
    to.push_back({E.text, E.caret, E.anchor});
    EditorState::Snap s = std::move(from.back());
    from.pop_back();
    E.text = std::move(s.text);
    E.caret = std::min(s.caret, E.text.size());
    E.anchor = std::min(s.anchor, E.text.size());
    E.lastEdit = 0;
    EdChanged();
}

std::wstring EdSelection() {
    size_t a = std::min(E.caret, E.anchor), b = std::max(E.caret, E.anchor);
    return E.text.substr(a, b - a);
}

void EdCopy() {
    std::wstring s = ToCrLf(EdSelection());
    if (s.empty()) return;
    bool open = false;
    for (int i = 0; i < 5 && !(open = OpenClipboard(E.hwnd)); i++) Sleep(10);
    if (!open) return;
    EmptyClipboard();
    size_t bytes = (s.size() + 1) * sizeof(wchar_t);
    if (HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, bytes)) {
        if (void* p = GlobalLock(h)) {
            memcpy(p, s.c_str(), bytes);
            GlobalUnlock(h);
            if (!SetClipboardData(CF_UNICODETEXT, h)) GlobalFree(h);
        } else {
            GlobalFree(h);
        }
    }
    CloseClipboard();
}

void EdPaste() {
    bool open = false;
    for (int i = 0; i < 5 && !(open = OpenClipboard(E.hwnd)); i++) Sleep(10);
    if (!open) return;
    std::wstring s;
    if (HANDLE h = GetClipboardData(CF_UNICODETEXT)) {
        if (auto* p = (const wchar_t*)GlobalLock(h)) {
            s.assign(p, wcsnlen(p, GlobalSize(h) / sizeof(wchar_t)));
            GlobalUnlock(h);
        }
    }
    CloseClipboard();
    s = FromCrLf(s);
    if (!s.empty()) EdReplace(s, 0);
}

void EdSelectAll() {
    E.anchor = 0;
    E.caret = E.text.size();
    E.lastEdit = 0;
    EdCaretTimer();
    InvalidateRect(E.hwnd, nullptr, FALSE);
}

// Up and Down keep the column the caret started in, like any text box.
void EdVertical(float lines, bool extend) {
    float lh = 0;
    auto p = EdPos(E.caret, &lh);
    if (E.wantX < 0) E.wantX = p.x;
    float x = E.wantX;
    float y = p.y + lh / 2 + lines * lh;
    size_t to;
    if (y < 0) to = 0;
    else if (y >= E.contentH) to = E.text.size();
    else to = EdHit(x, y);
    EdMove(to, extend);
    E.wantX = x;
}

void EdDragTo(float x, float y) {
    auto g = EditorGeo();
    size_t i = EdHit(x - g.view.left, y - g.view.top + E.scrollY);
    if (i != E.caret) {
        E.caret = i;
        EdCaretTimer();
        InvalidateRect(E.hwnd, nullptr, FALSE);
    }
}

bool EdScrollable() {
    EdLayout();
    return E.contentH > EdViewH() + 0.5f;
}

D2D1_RECT_F EdThumb(const EditorGeometry& g) {
    float vh = EdViewH(), trackH = g.scroll.bottom - g.scroll.top;
    float thumbH = std::min(trackH, std::max(28.0f, trackH * vh / std::max(vh, E.contentH)));
    float maxS = std::max(1.0f, E.contentH - vh);
    float top = g.scroll.top + (trackH - thumbH) * std::clamp(E.scrollY / maxS, 0.0f, 1.0f);
    return {g.scroll.left, top, g.scroll.right, top + thumbH};
}

void EdPlaceIme() {
    HIMC imc = ImmGetContext(E.hwnd);
    if (!imc) return;
    auto g = EditorGeo();
    float s = E.surf.Scale(), lh = 0;
    auto p = EdPos(E.caret, &lh);
    COMPOSITIONFORM cf{};
    cf.dwStyle = CFS_POINT;
    cf.ptCurrentPos = {(LONG)((g.view.left + p.x) * s), (LONG)((g.view.top + p.y - E.scrollY) * s)};
    ImmSetCompositionWindow(imc, &cf);
    ImmReleaseContext(E.hwnd, imc);
}

void EdContextMenu(POINT screen) {
    bool sel = E.caret != E.anchor;
    std::vector<UiMenuItem> items{
        MI(1, L"Undo", 0xE7A7, L"Ctrl+Z", !E.undo.empty()),
        MI(2, L"Redo", 0xE7A6, L"Ctrl+Y", !E.redo.empty()),
        MSep(),
        MI(3, L"Cut", 0xE8C6, L"Ctrl+X", sel),
        MI(4, L"Copy", kGlyphCopy, L"Ctrl+C", sel),
        MI(5, L"Paste", kGlyphPaste, L"Ctrl+V", IsClipboardFormatAvailable(CF_UNICODETEXT) != FALSE),
        MSep(),
        MI(6, L"Select all", 0xE8B3, L"Ctrl+A", !E.text.empty()),
    };
    switch (RunMenu(items, screen, E.hwnd)) {
        case 1: EdUndo(false); break;
        case 2: EdUndo(true); break;
        case 3: EdCopy(); EdReplace(L"", 0); break;
        case 4: EdCopy(); break;
        case 5: EdPaste(); break;
        case 6: EdSelectAll(); break;
    }
    SetFocus(E.hwnd);
}

bool EdKey(WPARAM vk) {
    bool ctrl = GetKeyState(VK_CONTROL) < 0, shift = GetKeyState(VK_SHIFT) < 0;
    size_t a = std::min(E.caret, E.anchor), b = std::max(E.caret, E.anchor);
    bool sel = a != b;
    size_t ls = 0, le = 0;
    switch (vk) {
        case VK_LEFT:
            if (sel && !shift) EdMove(a, false);
            else EdMove(ctrl ? EdWordLeft(E.caret) : EdPrev(E.caret), shift);
            return true;
        case VK_RIGHT:
            if (sel && !shift) EdMove(b, false);
            else EdMove(ctrl ? EdWordRight(E.caret) : EdNext(E.caret), shift);
            return true;
        case VK_UP:
            if (ctrl) EdScrollTo(E.scrollTarget - EdViewH() / 8, false);
            else EdVertical(-1, shift);
            return true;
        case VK_DOWN:
            if (ctrl) EdScrollTo(E.scrollTarget + EdViewH() / 8, false);
            else EdVertical(1, shift);
            return true;
        case VK_PRIOR:
        case VK_NEXT: {
            float lh = 0;
            EdPos(E.caret, &lh);
            float lines = std::max(1.0f, std::floor(EdViewH() / lh) - 1) * (vk == VK_PRIOR ? -1 : 1);
            EdScrollTo(E.scrollTarget + lines * lh, false);
            EdVertical(lines, shift);
            return true;
        }
        case VK_HOME:
            EdLineBounds(E.caret, ls, le);
            EdMove(ctrl ? 0 : ls, shift);
            return true;
        case VK_END:
            EdLineBounds(E.caret, ls, le);
            EdMove(ctrl ? E.text.size() : le, shift);
            return true;
        case VK_BACK:
            if (!sel) E.anchor = ctrl ? EdWordLeft(E.caret) : EdPrev(E.caret);
            EdReplace(L"", 2);
            return true;
        case VK_DELETE:
            if (shift && sel) {
                EdCopy();
                EdReplace(L"", 0);
                return true;
            }
            if (!sel) E.anchor = ctrl ? EdWordRight(E.caret) : EdNext(E.caret);
            EdReplace(L"", 2);
            return true;
        case VK_INSERT:
            if (ctrl) EdCopy();
            else if (shift) EdPaste();
            return true;
        case VK_ESCAPE:
            PostMessageW(E.hwnd, WM_COMMAND, IDCANCEL, 0);
            return true;
        case VK_RETURN:
            if (ctrl) {
                PostMessageW(E.hwnd, WM_COMMAND, IDOK, 0);
                return true;
            }
            return false;  // WM_CHAR inserts the line break
    }
    if (!ctrl) return false;
    switch (vk) {
        case 'A': EdSelectAll(); return true;
        case 'C': EdCopy(); return true;
        case 'X':
            if (sel) {
                EdCopy();
                EdReplace(L"", 0);
            }
            return true;
        case 'V': EdPaste(); return true;
        case 'Z': EdUndo(shift); return true;
        case 'Y': EdUndo(true); return true;
        case 'S': PostMessageW(E.hwnd, WM_COMMAND, IDOK, 0); return true;
    }
    return false;
}

D2D1_RECT_F EdCapButton(int i) {
    RECT rc{};
    GetClientRect(E.hwnd, &rc);
    float w = rc.right / E.surf.Scale();
    float x = w - (3 - i) * kEdCapBtnW - 4;
    return {x, 0, x + kEdCapBtnW, kEdCapH};
}

int EdCapButtonAt(float x, float y) {
    if (y < 0 || y >= kEdCapH) return -1;
    for (int i = 0; i < 3; i++)
        if (In(EdCapButton(i), x, y)) return i;
    return -1;
}

// Title and the three round window buttons. No band fill: the bar is the body's own blur.
void PaintEditorCaption(Ctx& c, float w) {
    float mid = kEdCapH / 2;
    WCHAR title[64]{};
    GetWindowTextW(E.hwnd, title, 64);
    std::wstring t = title;
    float total = 16 + 8 + c.TextWidth(t, T.ui.get());
    float x = std::round((w - total) / 2);
    x = std::max(12.0f, std::min(x, w - 3 * kEdCapBtnW - 8 - total));
    float a = E.active ? 1.0f : 0.6f;
    D2D1_RECT_F mark{x, mid - 8, x + 16, mid + 8};
    auto g = c.Gradient({mark.left, mark.top}, {mark.right, mark.bottom}, D2DColor(mocha::blue, a),
                        D2DColor(mocha::mauve, a));
    if (g) c.rt->FillRoundedRectangle({mark, 4, 4}, g.get());
    c.rt->DrawText(&kGlyphPaste, 1, T.iconSmall.get(), {mark.left, mark.top + 2, mark.right, mark.bottom},
                   c.B(mocha::crust, a), D2D1_DRAW_TEXT_OPTIONS_NONE);
    Com<IDWriteTextLayout> lay;
    if (!t.empty() &&
        SUCCEEDED(F.dw->CreateTextLayout(t.c_str(), (UINT32)t.size(), T.ui.get(), 1000, kEdCapH, lay.put()))) {
        // T.ui already centres the line box in the bar (paragraph alignment). Line boxes carry the
        // descender gap, so the letters sat low beside the icon: shift so the capital letters'
        // ink is centred on the icon's middle instead.
        float dy = 0;
        Com<IDWriteTextLayout> cap;
        DWRITE_OVERHANG_METRICS o{};
        if (SUCCEEDED(F.dw->CreateTextLayout(L"H", 1, T.ui.get(), 1000, kEdCapH, cap.put())) &&
            SUCCEEDED(cap->GetOverhangMetrics(&o)))
            dy = mid - (-o.top + kEdCapH + o.bottom) / 2;
        c.rt->DrawTextLayout({x + 24, std::round(dy)}, lay.get(),
                             c.B(E.active ? mocha::text : mocha::overlay1));
    }
    const UINT32 colors[3] = {mocha::yellow, mocha::green, mocha::red};
    for (int i = 0; i < 3; i++) {
        D2D1_RECT_F b = EdCapButton(i);
        float cx = (b.left + b.right) / 2, cy = mid;
        bool hot = E.capHot == i || E.capDown == i;
        float r = hot ? 7.5f : 7.0f;
        float ca = E.capDown == i ? 0.8f : (E.active || hot ? 1.0f : 0.45f);
        c.rt->FillEllipse(D2D1::Ellipse({cx, cy}, r, r), c.B(colors[i], ca));
        if (!hot) continue;
        auto* ink = c.B(mocha::crust, 0.8f);
        float k = 3.2f, sw = 1.4f;
        if (i == 0) {
            c.rt->DrawLine({cx - k, cy}, {cx + k, cy}, ink, sw);
        } else if (i == 1) {
            if (IsZoomed(E.hwnd)) {
                c.rt->DrawRectangle({cx - k + 1, cy - k + 1, cx + k - 1, cy + k - 1}, ink, sw);
            } else {
                c.rt->DrawLine({cx - k, cy}, {cx + k, cy}, ink, sw);
                c.rt->DrawLine({cx, cy - k}, {cx, cy + k}, ink, sw);
            }
        } else {
            float d = k - 0.4f;
            c.rt->DrawLine({cx - d, cy - d}, {cx + d, cy + d}, ink, sw);
            c.rt->DrawLine({cx - d, cy + d}, {cx + d, cy - d}, ink, sw);
        }
    }
}

void PaintEditorField(Ctx& c) {
    auto g = EditorGeo();
    // Only a light crust tint: the field stays on the same blur as the title bar and the body,
    // and the ring separates it.
    float rad = 8;
    c.rt->FillRoundedRectangle({g.box, rad, rad}, c.B(mocha::crust, 0.30f));
    c.Glow(g.box, rad, 0, E.focused ? 0.85f : 0.35f);
    auto* lay = EdLayout();
    if (!lay) return;
    float ox = g.view.left, oy = g.view.top - E.scrollY;
    c.rt->PushAxisAlignedClip({g.box.left + 2, g.box.top + 3, g.scroll.left - 1, g.box.bottom - 3},
                              D2D1_ANTIALIAS_MODE_ALIASED);
    size_t a = std::min(E.caret, E.anchor), b = std::max(E.caret, E.anchor);
    if (a != b) {
        UINT32 n = 0;
        lay->HitTestTextRange((UINT32)a, (UINT32)(b - a), ox, oy, nullptr, 0, &n);
        std::vector<DWRITE_HIT_TEST_METRICS> ms(n);
        if (n && SUCCEEDED(lay->HitTestTextRange((UINT32)a, (UINT32)(b - a), ox, oy, ms.data(), n, &n))) {
            for (UINT32 k = 0; k < n; k++) {
                const auto& m = ms[k];
                float w = std::max(m.width, 4.0f);  // a selected line break still shows a sliver
                c.rt->FillRectangle({m.left, m.top, m.left + w, m.top + m.height},
                                    c.BRef(g_set.accentColor, E.focused ? 0.38f : 0.22f));
            }
        }
    }
    if (E.text.empty())
        c.Text(E.id ? L"Empty clip" : L"Type or paste text", E.fmt.get(),
               {ox, oy, g.view.right, oy + 200}, mocha::overlay1);
    c.rt->DrawTextLayout({ox, oy}, lay, c.B(mocha::text), D2D1_DRAW_TEXT_OPTIONS_NONE);
    if (E.focused && E.caretOn) {
        float lh = 0;
        auto p = EdPos(E.caret, &lh);
        float x = std::round(ox + p.x);
        c.rt->FillRectangle({x, oy + p.y, x + 1.5f, oy + p.y + lh}, c.B(mocha::text));
    }
    c.rt->PopAxisAlignedClip();
    // Scrollbar: the list's thin rounded thumb, wider with a track on hover, accent while dragged.
    if (EdScrollable()) {
        bool hot = E.scrollHot || E.dragThumb;
        float wdt = hot ? 6.0f : 4.0f, cx = (g.scroll.left + g.scroll.right) / 2;
        D2D1_RECT_F track{cx - wdt / 2, g.scroll.top, cx + wdt / 2, g.scroll.bottom};
        if (hot) c.rt->FillRoundedRectangle({track, wdt / 2, wdt / 2}, c.B(mocha::surface0, 0.9f));
        auto th = EdThumb(g);
        D2D1_RECT_F thumb{track.left, th.top, track.right, th.bottom};
        auto* brush = E.dragThumb ? c.BRef(g_set.accentColor2) : hot ? c.BRef(g_set.accentColor) : c.B(mocha::overlay1);
        c.rt->FillRoundedRectangle({thumb, wdt / 2, wdt / 2}, brush);
    }
}

void LayoutEditor() {
    RECT rc;
    GetClientRect(E.hwnd, &rc);
    UINT dpi = GetDpiForWindow(E.hwnd);
    auto S = [&](int v) { return MulDiv(v, (int)dpi, 96); };
    int bw = S(88), bh = S(34), pad = S(16);
    int by = rc.bottom - pad - bh;
    SetWindowPos(E.save, nullptr, rc.right - pad - 2 * bw - S(8), by, bw, bh, SWP_NOZORDER);
    SetWindowPos(E.cancel, nullptr, rc.right - pad - bw, by, bw, bh, SWP_NOZORDER);
    E.dirty = true;
}

void EditorFonts() {
    UINT dpi = GetDpiForWindow(E.hwnd);
    if (E.uiFont) DeleteObject(E.uiFont);
    EnsureFonts();
    E.uiFont = MakeHFont(dpi, 10, FW_SEMIBOLD, T.family);
    SetFontAll(E.hwnd, E.uiFont);
    E.fmt = MakeFormat(T.family, g_set.fontSize * 96.0f / 72.0f, (DWRITE_FONT_WEIGHT)BaseWeight(), true,
                       DWRITE_TEXT_ALIGNMENT_LEADING, false);
    if (E.fmt) {
        float tab = MeasureText(L"    ", E.fmt.get());
        if (tab > 0) E.fmt->SetIncrementalTabStop(tab);
    }
    E.dirty = true;
}

LRESULT CALLBACK EditorProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    auto dip = [&](LPARAM l, float& x, float& y) {
        float s = E.surf.Scale();
        x = GET_X_LPARAM(l) / s;
        y = GET_Y_LPARAM(l) / s;
    };
    switch (msg) {
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT: {
            PAINTSTRUCT ps; BeginPaint(hwnd, &ps);
            if (E.hwnd && E.surf.Ensure()) {
                RECT rc; GetClientRect(hwnd, &rc);
                float scale = E.surf.Scale();
                auto* rt = E.surf.rt.get();
                rt->BeginDraw();
                Ctx c(rt);
                PaintFrame(c, rc.right / scale, rc.bottom / scale, false);
                PaintEditorCaption(c, rc.right / scale);
                PaintEditorField(c);
                if (rt->EndDraw() == D2DERR_RECREATE_TARGET) E.surf.Discard();
            }
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_NCCALCSIZE:
            // No system title bar (a darker solid band): the client starts at the top edge and the
            // title is drawn on the blur. Side and bottom frames stay for resizing.
            if (wp) {
                auto* nc = (NCCALCSIZE_PARAMS*)lp;
                LONG top = nc->rgrc[0].top;
                LRESULT r = DefWindowProcW(hwnd, msg, wp, lp);
                nc->rgrc[0].top = top;
                if (IsZoomed(hwnd)) {
                    UINT dpi = GetDpiForWindow(hwnd);
                    nc->rgrc[0].top += GetSystemMetricsForDpi(SM_CYSIZEFRAME, dpi) +
                                       GetSystemMetricsForDpi(SM_CXPADDEDBORDER, dpi);
                }
                return r;
            }
            break;
        case WM_NCHITTEST: {
            LRESULT def = DefWindowProcW(hwnd, msg, wp, lp);
            if (def != HTCLIENT) return def;
            POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            ScreenToClient(hwnd, &pt);
            UINT dpi = GetDpiForWindow(hwnd);
            RECT rc;
            GetClientRect(hwnd, &rc);
            int frame = GetSystemMetricsForDpi(SM_CYSIZEFRAME, dpi) + GetSystemMetricsForDpi(SM_CXPADDEDBORDER, dpi);
            if (!IsZoomed(hwnd) && pt.y < frame)
                return pt.x < frame * 2 ? HTTOPLEFT : pt.x >= rc.right - frame * 2 ? HTTOPRIGHT : HTTOP;
            float s = dpi / 96.0f, x = pt.x / s, y = pt.y / s;
            if (y < kEdCapH) return EdCapButtonAt(x, y) >= 0 ? HTCLIENT : HTCAPTION;
            return HTCLIENT;
        }
        case WM_ACTIVATE:
            E.active = LOWORD(wp) != WA_INACTIVE;
            InvalidateRect(hwnd, nullptr, FALSE);
            break;
        case WM_GETDLGCODE:
            return DLGC_WANTALLKEYS | DLGC_WANTCHARS | DLGC_WANTTAB | DLGC_WANTARROWS;
        case WM_SETFOCUS:
            E.focused = true;
            EdCaretTimer();
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_KILLFOCUS:
            E.focused = false;
            EdCaretTimer();
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_KEYDOWN:
            if (E.hwnd && EdKey(wp)) return 0;
            break;
        case WM_CHAR: {
            if (!E.hwnd) break;
            wchar_t ch = (wchar_t)wp;
            if (ch == L'\r') EdReplace(L"\n", 0);
            else if (ch == L'\t') EdReplace(L"\t", 1);
            else if (ch >= 0x20 && ch != 0x7F) EdReplace(std::wstring(1, ch), ch == L' ' ? 0 : 1);
            return 0;
        }
        case WM_IME_STARTCOMPOSITION:
            EdPlaceIme();
            break;
        case WM_SETCURSOR:
            if ((HWND)wp == hwnd && LOWORD(lp) == HTCLIENT && E.hwnd) {
                POINT pt; GetCursorPos(&pt); ScreenToClient(hwnd, &pt);
                float s = E.surf.Scale(), x = pt.x / s, y = pt.y / s;
                auto g = EditorGeo();
                bool bar = EdScrollable() && In(g.scroll, x, y);
                SetCursor(LoadCursorW(nullptr, In(g.box, x, y) && !bar && !E.dragThumb ? IDC_IBEAM : IDC_ARROW));
                return TRUE;
            }
            break;
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK: {
            if (!E.hwnd) break;
            float x, y; dip(lp, x, y);
            int cb = EdCapButtonAt(x, y);
            if (cb >= 0) {
                E.capDown = cb;
                SetCapture(hwnd);
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            auto g = EditorGeo();
            if (!In(g.box, x, y)) break;
            SetFocus(hwnd);
            if (EdScrollable() && In(g.scroll, x, y)) {
                auto th = EdThumb(g);
                if (y >= th.top && y < th.bottom) {
                    E.dragThumb = true;
                    E.dragOffset = y - th.top;
                    SetCapture(hwnd);
                } else {
                    EdScrollTo(E.scrollTarget + (y < th.top ? -1 : 1) * EdViewH() * 0.9f, false);
                }
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            size_t i = EdHit(x - g.view.left, y - g.view.top + E.scrollY);
            if (msg == WM_LBUTTONDBLCLK) {
                size_t n = E.text.size(), s = i, e = i;
                size_t at = (i < n && E.text[i] != L'\n') ? i : (i > 0 ? i - 1 : 0);
                if (n && E.text[at] != L'\n') {
                    int c = EdClass(E.text[at]);
                    s = at;
                    e = at + 1;
                    while (s > 0 && EdClass(E.text[s - 1]) == c) s--;
                    while (e < n && EdClass(E.text[e]) == c) e++;
                }
                E.anchor = s;
                E.caret = e;
                E.lastEdit = 0;
                EdCaretTimer();
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            EdMove(i, GetKeyState(VK_SHIFT) < 0);
            E.selecting = true;
            SetCapture(hwnd);
            SetTimer(hwnd, kTimerDrag, 30, nullptr);
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (!E.hwnd) break;
            float x, y; dip(lp, x, y);
            auto g = EditorGeo();
            if (E.dragThumb) {
                auto th = EdThumb(g);
                float travel = std::max(1.0f, (g.scroll.bottom - g.scroll.top) - (th.bottom - th.top));
                float frac = (y - E.dragOffset - g.scroll.top) / travel;
                EdScrollTo(frac * std::max(0.0f, E.contentH - EdViewH()), true);
                return 0;
            }
            if (E.selecting) {
                EdDragTo(x, y);
                return 0;
            }
            int cap = EdCapButtonAt(x, y);
            if (cap != E.capHot) {
                E.capHot = cap;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            bool hot = EdScrollable() && In(g.scroll, x, y) && E.capDown < 0;
            if (hot != E.scrollHot) {
                E.scrollHot = hot;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            if (!E.tracking) {
                TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
                E.tracking = TrackMouseEvent(&tme) != FALSE;
            }
            return 0;
        }
        case WM_MOUSELEAVE:
            E.tracking = false;
            if (E.scrollHot || E.capHot >= 0) {
                E.scrollHot = false;
                E.capHot = -1;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        case WM_LBUTTONUP: {
            int down = E.capDown;
            float x, y; dip(lp, x, y);
            if (GetCapture() == hwnd) ReleaseCapture();
            if (down >= 0 && EdCapButtonAt(x, y) == down) {
                if (down == 0) ShowWindow(hwnd, SW_MINIMIZE);
                else if (down == 1) ShowWindow(hwnd, IsZoomed(hwnd) ? SW_RESTORE : SW_MAXIMIZE);
                else PostMessageW(hwnd, WM_CLOSE, 0, 0);
            }
            return 0;
        }
        case WM_CAPTURECHANGED:
            if (E.capDown >= 0) {
                E.capDown = -1;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            if (E.selecting || E.dragThumb) {
                E.selecting = E.dragThumb = false;
                KillTimer(hwnd, kTimerDrag);
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        case WM_MOUSEWHEEL: {
            if (!E.hwnd) break;
            UINT lines = 3;
            SystemParametersInfoW(SPI_GETWHEELSCROLLLINES, 0, &lines, 0);
            float lh = 0;
            EdPos(0, &lh);
            float step = lines == WHEEL_PAGESCROLL ? EdViewH() : std::max(1u, lines) * lh;
            EdScrollTo(E.scrollTarget - GET_WHEEL_DELTA_WPARAM(wp) / 120.0f * step, false);
            return 0;
        }
        case WM_RBUTTONUP: {
            if (!E.hwnd) break;
            float x, y; dip(lp, x, y);
            auto g = EditorGeo();
            if (!In(g.box, x, y)) break;
            SetFocus(hwnd);
            size_t i = EdHit(x - g.view.left, y - g.view.top + E.scrollY);
            size_t a = std::min(E.caret, E.anchor), b = std::max(E.caret, E.anchor);
            if (i < a || i > b) EdMove(i, false);
            POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            ClientToScreen(hwnd, &pt);
            EdContextMenu(pt);
            return 0;
        }
        case WM_TIMER:
            if (wp == kTimerScroll) {
                float d = E.scrollTarget - E.scrollY;
                if (std::fabs(d) < 0.5f) {
                    E.scrollY = E.scrollTarget;
                    KillTimer(hwnd, kTimerScroll);
                } else {
                    E.scrollY += d * 0.35f;
                }
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (wp == kTimerCaret) {
                E.caretOn = !E.caretOn;
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (wp == kTimerDrag && E.selecting) {
                // Drag-select past the top or bottom edge scrolls, faster the further out.
                POINT pt; GetCursorPos(&pt); ScreenToClient(hwnd, &pt);
                float s = E.surf.Scale(), x = pt.x / s, y = pt.y / s;
                auto g = EditorGeo();
                float d = y < g.view.top ? y - g.view.top : y > g.view.bottom ? y - g.view.bottom : 0;
                if (d != 0) {
                    EdScrollTo(E.scrollY + std::clamp(d * 0.5f, -40.0f, 40.0f), true);
                    EdDragTo(x, y);
                }
            }
            return 0;
        case WM_COMMAND:
            if (LOWORD(wp) == IDOK) {
                std::wstring clean = E.lfOnly ? E.text : ToCrLf(E.text);
                int64_t saved = 0;
                if (E.id) {
                    if (Db_UpdateClipText(E.id, clean)) saved = E.id;
                } else if (!clean.empty()) {
                    ClipData data;
                    ClipFormat f;
                    f.cf = CF_UNICODETEXT;
                    f.name = L"CF_UNICODETEXT";
                    f.data.assign((const char*)clean.c_str(), (clean.size() + 1) * sizeof(wchar_t));
                    data.formats.push_back(f);
                    data.description = clean;
                    saved = Db_SaveClip(data);
                }
                if (saved) List_OnClipSaved(saved);
                DestroyWindow(hwnd);
                return 0;
            }
            if (LOWORD(wp) == IDCANCEL) {
                DestroyWindow(hwnd);
                return 0;
            }
            break;
        case WM_SIZE:
            if (!E.hwnd || !E.save) break;
            E.surf.Resize();
            LayoutEditor();
            EdScrollTo(E.scrollTarget, true);
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_DPICHANGED: {
            auto* r = (RECT*)lp;
            SetWindowPos(hwnd, nullptr, r->left, r->top, r->right - r->left, r->bottom - r->top, SWP_NOZORDER);
            EditorFonts();
            LayoutEditor();
            return 0;
        }
        case WM_EXITSIZEMOVE:
            SaveHelperSize(hwnd, L"Editor");
            return 0;
        case WM_DRAWITEM:
            DrawOwnerButton((const DRAWITEMSTRUCT*)lp);
            return TRUE;
        case WM_CTLCOLORSTATIC:
            return CtlColor(msg, wp, lp, (HBRUSH)GetClassLongPtrW(hwnd, GCLP_HBRBACKGROUND));
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            E.surf.Discard();
            if (E.uiFont) DeleteObject(E.uiFont);
            E = EditorState{};
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

// ---------------------------------------------------------------------------
// Properties window
// ---------------------------------------------------------------------------
enum PropId { idDesc = 200, idQuick, idNever, idSticky, idGroup, idInfo };

struct PropsState {
    HWND hwnd = nullptr, desc = nullptr, quick = nullptr, never = nullptr, sticky = nullptr, group = nullptr,
         info = nullptr, ok = nullptr, cancel = nullptr;
    std::vector<HWND> labels;
    HFONT font = nullptr, fieldFont = nullptr;
    ClipRow row;
    std::vector<int64_t> groupIds;
    bool inGroupList = false;
} PR;

void LayoutProps() {
    RECT rc;
    GetClientRect(PR.hwnd, &rc);
    UINT dpi = GetDpiForWindow(PR.hwnd);
    auto S = [&](int v) { return MulDiv(v, (int)dpi, 96); };
    int pad = S(14), w = rc.right - 2 * pad, y = S(10), lab = S(20), gap = S(8);
    auto place = [&](HWND h, int height) {
        SetWindowPos(h, nullptr, pad, y, w, height, SWP_NOZORDER);
        y += height + gap;
    };
    auto label = [&](size_t i) {
        if (i < PR.labels.size()) SetWindowPos(PR.labels[i], nullptr, pad, y, w, lab, SWP_NOZORDER);
        y += lab + S(2);
    };
    label(0);
    place(PR.desc, S(58));
    label(1);
    place(PR.quick, S(24));
    SetWindowPos(PR.never, nullptr, pad, y, w / 2, S(24), SWP_NOZORDER);
    SetWindowPos(PR.sticky, nullptr, pad + w / 2, y, w / 2, S(24), SWP_NOZORDER);
    y += S(24) + gap;
    label(2);
    place(PR.group, S(300));
    y -= S(300) - S(26);
    label(3);
    int bh = S(30);
    int infoH = std::max<int>(S(40), rc.bottom - pad - bh - gap - y);
    place(PR.info, infoH);
    int bw = S(88);
    SetWindowPos(PR.ok, nullptr, rc.right - pad - 2 * bw - S(8), rc.bottom - pad - bh, bw, bh, SWP_NOZORDER);
    SetWindowPos(PR.cancel, nullptr, rc.right - pad - bw, rc.bottom - pad - bh, bw, bh, SWP_NOZORDER);
}

void PropsFonts() {
    UINT dpi = GetDpiForWindow(PR.hwnd);
    if (PR.font) DeleteObject(PR.font);
    if (PR.fieldFont) DeleteObject(PR.fieldFont);
    EnsureFonts();
    PR.font = MakeHFont(dpi, 10, FW_NORMAL, T.family);
    PR.fieldFont = MakeHFont(dpi, (float)g_set.fontSize, FW_NORMAL, T.family);
    SetFontAll(PR.hwnd, PR.font);
    for (HWND f : {PR.desc, PR.quick, PR.info}) {
        SendMessageW(f, WM_SETFONT, (WPARAM)PR.fieldFont, TRUE);
        int m = MulDiv(6, (int)dpi, 96);
        SendMessageW(f, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(m, m));
    }
}

std::wstring ToCrLf(const std::wstring& s) {
    std::wstring out;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == L'\n' && (i == 0 || s[i - 1] != L'\r')) out += L'\r';
        out += s[i];
    }
    return out;
}

std::wstring FromCrLf(const std::wstring& s) {
    std::wstring out;
    for (wchar_t ch : s)
        if (ch != L'\r') out += ch;
    return out;
}

std::wstring FieldText(HWND h) {
    int n = GetWindowTextLengthW(h);
    std::wstring s((size_t)n, L'\0');
    GetWindowTextW(h, s.data(), n + 1);
    return s;
}

void ApplyProps() {
    int64_t id = PR.row.id;
    std::wstring desc = FromCrLf(FieldText(PR.desc)), quick = FieldText(PR.quick);
    if (desc != FromCrLf(PR.row.text)) Db_SetDescription(id, desc);
    if (quick != PR.row.quickPasteText) Db_SetQuickPasteText(id, quick);
    if (IsChecked(PR.never) != PR.row.neverDelete) Db_SetNeverDelete(id, IsChecked(PR.never));
    if (IsChecked(PR.sticky) != PR.row.sticky) Db_SetSticky(id, IsChecked(PR.sticky), PR.inGroupList);
    int sel = (int)SendMessageW(PR.group, CB_GETCURSEL, 0, 0);
    if (sel >= 0 && sel < (int)PR.groupIds.size() && PR.groupIds[(size_t)sel] != PR.row.parentId)
        Db_MoveToGroup({id}, PR.groupIds[(size_t)sel]);
    List_OnClipSaved(id);
}

LRESULT CALLBACK PropsProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_COMMAND: {
            int id = LOWORD(wp);
            if (id == IDOK) {
                ApplyProps();
                DestroyWindow(hwnd);
                return 0;
            }
            if (id == IDCANCEL) {
                DestroyWindow(hwnd);
                return 0;
            }
            if ((id == idNever || id == idSticky) && HIWORD(wp) == BN_CLICKED) {
                HWND b = (HWND)lp;
                SetChecked(b, !IsChecked(b));
                return 0;
            }
            break;
        }
        case WM_SIZE:
            if (PR.ok) LayoutProps();
            return 0;
        case WM_DPICHANGED: {
            auto* r = (RECT*)lp;
            SetWindowPos(hwnd, nullptr, r->left, r->top, r->right - r->left, r->bottom - r->top, SWP_NOZORDER);
            PropsFonts();
            LayoutProps();
            return 0;
        }
        case WM_DRAWITEM:
            DrawOwnerButton((const DRAWITEMSTRUCT*)lp);
            return TRUE;
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORSTATIC:
        case WM_CTLCOLORLISTBOX:
            return CtlColor(msg, wp, lp, (HBRUSH)GetClassLongPtrW(hwnd, GCLP_HBRBACKGROUND));
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            if (PR.font) DeleteObject(PR.font);
            if (PR.fieldFont) DeleteObject(PR.fieldFont);
            PR = PropsState{};
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

HWND CreateHelperWindow(PCWSTR cls, PCWSTR title) {
    HWND h = CreateWindowExW(WS_EX_CONTROLPARENT | WS_EX_APPWINDOW, cls, title, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                             CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, nullptr, nullptr, g_hInstance, nullptr);
    if (h) ApplyDarkWindow(h);
    return h;
}

// ---------------------------------------------------------------------------
// App icon
// ---------------------------------------------------------------------------
void DrawAppIcon(ID2D1RenderTarget* rt, float s) {
    Ctx c(rt);
    rt->Clear(D2D1::ColorF(0, 0, 0, 0));
    float px = 1.0f;
    auto snap = [&](float v) { return std::round(v / px) * px; };
    D2D1_RECT_F board{snap(s * 0.14f), snap(s * 0.12f), snap(s * 0.86f), snap(s * 0.95f)};
    float br = std::max(1.5f, s * 0.13f);
    auto grad = c.Gradient({board.left, board.top}, {board.right, board.bottom}, D2DColor(mocha::blue),
                           D2DColor(mocha::mauve));
    if (grad) rt->FillRoundedRectangle({board, br, br}, grad.get());
    // Clip at the top.
    D2D1_RECT_F clip{snap(s * 0.32f), snap(s * 0.04f), snap(s * 0.68f), snap(s * 0.22f)};
    float cr = std::max(1.0f, s * 0.06f);
    rt->FillRoundedRectangle({clip, cr, cr}, c.B(mocha::crust));
    if (s >= 24) {
        D2D1_RECT_F inner = Inset(clip, s * 0.035f, s * 0.035f);
        rt->FillRoundedRectangle({inner, cr * 0.6f, cr * 0.6f}, c.B(mocha::text));
    }
    // Text lines.
    int lines = s <= 16 ? 2 : 3;
    float lh = std::max(1.0f, snap(s * 0.075f));
    float startY = s <= 16 ? s * 0.44f : s * 0.38f, step = s <= 16 ? s * 0.22f : s * 0.17f;
    for (int i = 0; i < lines; i++) {
        float y = snap(startY + i * step);
        float right = i == lines - 1 ? s * 0.58f : s * 0.74f;
        D2D1_RECT_F ln{snap(s * 0.26f), y, snap(right), y + lh};
        rt->FillRoundedRectangle({ln, lh / 2, lh / 2}, c.B(mocha::crust, 0.85f));
    }
}

Com<IWICBitmap> RenderIconBitmap(int size) {
    Com<IWICBitmap> bmp;
    if (!EnsureFactories() ||
        FAILED(F.wic->CreateBitmap(size, size, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnLoad, bmp.put())))
        return {};
    Com<ID2D1RenderTarget> rt;
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                              D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
                                              96, 96);
    if (FAILED(F.d2d->CreateWicBitmapRenderTarget(bmp.get(), &props, rt.put()))) return {};
    rt->BeginDraw();
    DrawAppIcon(rt.get(), (float)size);
    rt->EndDraw();
    return bmp;
}

bool SavePng(IWICBitmapSource* src, const std::wstring& path) {
    Com<IWICStream> stream;
    Com<IWICBitmapEncoder> enc;
    Com<IWICBitmapFrameEncode> frame;
    UINT w = 0, h = 0;
    src->GetSize(&w, &h);
    WICPixelFormatGUID fmt = GUID_WICPixelFormat32bppBGRA;
    // PNG wants straight alpha; convert from premultiplied.
    Com<IWICFormatConverter> conv;
    if (FAILED(F.wic->CreateFormatConverter(conv.put())) ||
        FAILED(conv->Initialize(src, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, nullptr, 0,
                                WICBitmapPaletteTypeCustom)))
        return false;
    if (FAILED(F.wic->CreateStream(stream.put())) || FAILED(stream->InitializeFromFilename(path.c_str(), GENERIC_WRITE)) ||
        FAILED(F.wic->CreateEncoder(GUID_ContainerFormatPng, nullptr, enc.put())) ||
        FAILED(enc->Initialize(stream.get(), WICBitmapEncoderNoCache)) ||
        FAILED(enc->CreateNewFrame(frame.put(), nullptr)) || FAILED(frame->Initialize(nullptr)) ||
        FAILED(frame->SetSize(w, h)) || FAILED(frame->SetPixelFormat(&fmt)) ||
        FAILED(frame->WriteSource(conv.get(), nullptr)) || FAILED(frame->Commit()) || FAILED(enc->Commit()))
        return false;
    return true;
}

// Draw `paint` into a WIC bitmap at the given DIP size and scale, save as PNG.
bool RenderToPng(const std::wstring& path, float wDip, float hDip, float scale,
                 const std::function<void(ID2D1RenderTarget*)>& paint) {
    if (!EnsureFactories()) return false;
    UINT pw = (UINT)std::lround(wDip * scale), ph = (UINT)std::lround(hDip * scale);
    Com<IWICBitmap> bmp;
    Com<ID2D1RenderTarget> rt;
    if (FAILED(F.wic->CreateBitmap(pw, ph, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnLoad, bmp.put())))
        return false;
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                              D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
                                              96 * scale, 96 * scale);
    if (FAILED(F.d2d->CreateWicBitmapRenderTarget(bmp.get(), &props, rt.put()))) return false;
    rt->BeginDraw();
    paint(rt.get());
    HRESULT hr = rt->EndDraw();
    DropDeviceBitmaps();
    P.bmp.reset();
    return SUCCEEDED(hr) && SavePng(bmp.get(), path);
}

}  // namespace scmui
}  // namespace

// ---------------------------------------------------------------------------
// Contract functions
// ---------------------------------------------------------------------------
using namespace scmui;

void List_Show() {
    if (!EnsureListWindow()) return;
    if (A.dir < 0 && IsWindowVisible(L.surf.hwnd)) {  // Still closing: turn around where it is.
        L.hideRequested = false;
        AnimStart(+1);
        SetForegroundWindow(L.surf.hwnd);
        SetFocus(L.surf.hwnd);
        return;
    }
    if (GetForegroundWindow() != L.surf.hwnd) Focus_RememberTarget();
    ResetForOpen();
    L.hideRequested = false;
    PositionList();
    bool animate = Animate();
    A.p = animate ? 0.0f : 1.0f;
    A.dir = 0;
    if (animate) {
        AnimStart(+1);
        AnimApply();
    } else {
        KillTimer(L.surf.hwnd, kTimerAnim);
    }
    // Shown cloaked and painted once before DWM composes it: otherwise the first frames are a
    // flat grey window with a dark strip until the first Direct2D frame lands.
    BOOL cloak = TRUE;
    DwmSetWindowAttribute(L.surf.hwnd, 13 /* DWMWA_CLOAK */, &cloak, sizeof(cloak));
    ShowWindow(L.surf.hwnd, SW_SHOW);
    RedrawWindow(L.surf.hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
    cloak = FALSE;
    DwmSetWindowAttribute(L.surf.hwnd, 13 /* DWMWA_CLOAK */, &cloak, sizeof(cloak));
    // The first open builds the window and the drawing device, which can take a few hundred ms;
    // start the clock now so the whole slide is seen.
    A.last = GetTickCount64();
    SetForegroundWindow(L.surf.hwnd);
    SetFocus(L.surf.hwnd);
}

void List_Hide() {
    L.hideRequested = true;
    if (!L.surf.hwnd) return;
    if (A.dir < 0) return;  // Already closing.
    KillTimer(L.surf.hwnd, kTimerSearch);
    KillTimer(L.surf.hwnd, kTimerScroll);
    if (L.mode != DockMode::Search) CancelMode();
    HidePreview();
    if (L.dragPending || L.dragActive) EndDrag();
    if (IsWindowVisible(L.surf.hwnd)) {
        if (Animate()) AnimStart(-1);
        else HideListNow();
    }
}

bool List_IsVisible() { return L.surf.hwnd && IsWindowVisible(L.surf.hwnd) && A.dir >= 0; }

void List_Toggle() {
    if (List_IsVisible()) List_Hide();
    else List_Show();
}

int Ui_ShowMenu(const std::vector<UiMenuItem>& items, POINT screenPt, HWND owner) {
    return RunMenu(items, screenPt, owner);
}

void List_OnClipSaved(int64_t) {
    if (!List_IsVisible()) return;  // The next List_Show reloads anyway.
    int oldCaret = L.caret;
    int64_t caretId = IdAt(oldCaret);
    std::vector<int64_t> keep;
    if (!L.selAll) {
        for (int i : SelectedIndices()) {
            if (keep.size() >= 200) break;
            keep.push_back(IdAt(i));
        }
    }
    L.pages.clear();
    L.pageOrder.clear();
    L.count = DataCount(L.q);
    L.sel.assign((size_t)L.count, 0);
    L.selAll = false;
    // A new clip usually lands on top, so old rows sit at the same index or one lower.
    auto find = [](int64_t id, int near) {
        for (int d = 0; d <= 3; d++)
            for (int i : {near + d, near - d})
                if (i >= 0 && i < L.count && IdAt(i) == id) return i;
        return -1;
    };
    int newCaret = caretId ? find(caretId, oldCaret + 1) : -1;
    L.caret = newCaret >= 0 ? newCaret : std::clamp(oldCaret, 0, std::max(0, L.count - 1));
    L.anchor = L.caret;
    for (size_t k = 0; k < keep.size(); k++) {
        int i = find(keep[k], L.caret);
        if (i >= 0) L.sel[(size_t)i] = 1;
    }
    if (L.count) L.sel[(size_t)L.caret] = 1;
    Layout l = CurrentLayout();
    L.scrollTarget = std::clamp(L.scrollTarget, 0.0f, MaxScroll(l));
    L.scrollY = std::clamp(L.scrollY, 0.0f, MaxScroll(l));
    UpdatePreview();
    Invalidate();
}

void List_ApplySettings() {
    ResetFonts();
    g_thumbs.clear();
    g_thumbOrder.clear();
    if (L.surf.hwnd) {
        ApplyBackdrop(L.surf.hwnd);
        SetWindowPos(L.surf.hwnd, g_set.alwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        Reload();
    }
    if (P.surf.hwnd) {
        ApplyBackdrop(P.surf.hwnd);
        InvalidateRect(P.surf.hwnd, nullptr, FALSE);
    }
}

void List_Destroy() {
    if (E.hwnd) DestroyWindow(E.hwnd);
    if (PR.hwnd) DestroyWindow(PR.hwnd);
    if (P.surf.hwnd) DestroyWindow(P.surf.hwnd);
    if (L.surf.hwnd) DestroyWindow(L.surf.hwnd);
    L.pages.clear();
    L.pageOrder.clear();
    g_thumbs.clear();
    g_thumbOrder.clear();
    P = PreviewState{};
    ResetFonts();
    F = Factories{};
    if (g_mantleBrush) DeleteObject(g_mantleBrush);
    g_mantleBrush = nullptr;
    UnregisterClasses();
}

void Editor_Open(int64_t id) {
    if (!EnsureFonts()) return;
    RegisterClasses();
    ImportDittoSizes();
    if (E.hwnd) DestroyWindow(E.hwnd);
    E.hwnd = CreateHelperWindow(kEditorClass, id ? L"Edit clip" : L"New clip");
    if (!E.hwnd) return;
    E.id = id;
    E.surf.hwnd = E.hwnd;
    ApplyBackdrop(E.hwnd);
    E.save = MakeButton(E.hwnd, IDOK, L"Save", kBtnPrimary);
    E.cancel = MakeButton(E.hwnd, IDCANCEL, L"Cancel", 0);
    if (id) {
        std::wstring t = Db_GetClipText(id);
        E.lfOnly = t.find(L'\n') != std::wstring::npos && t.find(L"\r\n") == std::wstring::npos;
        E.text = FromCrLf(t);
    }
    EditorFonts();
    PlaceHelper(E.hwnd, L"Editor", 600, 460);
    LayoutEditor();
    // Show and activate before the list hides: once none of our windows is in front, Windows
    // refuses the foreground and the editor opened behind the app underneath.
    ShowWindow(E.hwnd, SW_SHOW);
    SetWindowPos(E.hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    SetForegroundWindow(E.hwnd);
    SetFocus(E.hwnd);
    List_Hide();
}

void Props_Open(int64_t id) {
    ClipRow row;
    if (!Db_GetClipRow(id, row) || !EnsureFonts()) return;
    RegisterClasses();
    if (PR.hwnd) DestroyWindow(PR.hwnd);
    bool inGroupList = L.q.groupId != -1;
    List_Hide();
    PR.hwnd = CreateHelperWindow(kPropsClass, row.isGroup ? L"Group properties" : L"Clip properties");
    if (!PR.hwnd) return;
    PR.row = row;
    PR.inGroupList = inGroupList;
    for (PCWSTR t : {L"Description", L"Quick paste text", L"Group", L"Details"}) PR.labels.push_back(MakeLabel(PR.hwnd, t));
    PR.desc = MakeField(PR.hwnd, idDesc, ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL);
    PR.quick = MakeField(PR.hwnd, idQuick, ES_AUTOHSCROLL);
    PR.never = MakeButton(PR.hwnd, idNever, L"Never delete", kBtnCheck);
    PR.sticky = MakeButton(PR.hwnd, idSticky, L"Pin to top", kBtnCheck);
    PR.group = CreateWindowExW(0, L"COMBOBOX", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST | WS_VSCROLL,
                               0, 0, 10, 10, PR.hwnd, (HMENU)(INT_PTR)idGroup, g_hInstance, nullptr);
    SetWindowTheme(PR.group, L"DarkMode_CFD", nullptr);
    PR.info = MakeField(PR.hwnd, idInfo, ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL | WS_VSCROLL);
    PR.ok = MakeButton(PR.hwnd, IDOK, L"OK", kBtnPrimary);
    PR.cancel = MakeButton(PR.hwnd, IDCANCEL, L"Cancel", 0);

    SetWindowTextW(PR.desc, ToCrLf(row.text).c_str());
    SetWindowTextW(PR.quick, row.quickPasteText.c_str());
    SetChecked(PR.never, row.neverDelete);
    SetChecked(PR.sticky, row.sticky);
    PR.groupIds.push_back(-1);
    SendMessageW(PR.group, CB_ADDSTRING, 0, (LPARAM)L"No group");
    int current = 0;
    for (auto& [g, depth] : GroupTree()) {
        if (g.id == row.id) continue;  // A group can't hold itself.
        std::wstring label = std::wstring(depth * 4, L' ') + g.text;
        SendMessageW(PR.group, CB_ADDSTRING, 0, (LPARAM)label.c_str());
        if (g.id == row.parentId) current = (int)PR.groupIds.size();
        PR.groupIds.push_back(g.id);
    }
    SendMessageW(PR.group, CB_SETCURSEL, current, 0);

    std::wstring info = L"Added: " + FormatDate(row.date) + L"\r\nLast pasted: " + FormatDate(row.lastPasteDate);
    ClipData data;
    if (Db_GetClipData(id, data) && !data.formats.empty()) {
        size_t total = 0;
        for (auto& f : data.formats) total += f.data.size();
        info += L"\r\nFormats (" + HumanSize(total) + L"):";
        for (auto& f : data.formats) info += L"\r\n    " + f.name + L"  " + HumanSize(f.data.size());
    }
    SetWindowTextW(PR.info, info.c_str());

    PropsFonts();
    PlaceHelper(PR.hwnd, nullptr, 440, 470);
    LayoutProps();
    ShowWindow(PR.hwnd, SW_SHOW);
    SetForegroundWindow(PR.hwnd);
    SetFocus(PR.desc);
}

HICON MakeAppIcon(int size) {
    Com<IWICBitmap> bmp = RenderIconBitmap(size);
    if (!bmp) return LoadIconW(nullptr, IDI_APPLICATION);
    std::vector<BYTE> px((size_t)size * size * 4);
    bmp->CopyPixels(nullptr, size * 4, (UINT)px.size(), px.data());
    // Icons use straight alpha.
    for (size_t i = 0; i < px.size(); i += 4) {
        BYTE a = px[i + 3];
        if (a && a < 255)
            for (int k = 0; k < 3; k++) px[i + k] = (BYTE)std::min(255, px[i + k] * 255 / a);
    }
    BITMAPV5HEADER bi{};
    bi.bV5Size = sizeof(bi);
    bi.bV5Width = size;
    bi.bV5Height = -size;
    bi.bV5Planes = 1;
    bi.bV5BitCount = 32;
    bi.bV5Compression = BI_BITFIELDS;
    bi.bV5RedMask = 0x00FF0000;
    bi.bV5GreenMask = 0x0000FF00;
    bi.bV5BlueMask = 0x000000FF;
    bi.bV5AlphaMask = 0xFF000000;
    void* bits = nullptr;
    HDC screen = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(screen, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!color || !bits) return LoadIconW(nullptr, IDI_APPLICATION);
    memcpy(bits, px.data(), px.size());
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(color);
    DeleteObject(mask);
    return icon ? icon : LoadIconW(nullptr, IDI_APPLICATION);
}

bool List_RenderToPng(const std::wstring& path, int widthDip, int heightDip, float dpiScale) {
    if (!EnsureFonts()) return false;
    bool hadWindow = L.surf.hwnd != nullptr;
    if (!hadWindow || !List_IsVisible()) {
        L.wDip = (float)widthDip;
        L.hDip = (float)heightDip;
        HWND saved = L.surf.hwnd;
        L.surf.hwnd = nullptr;  // Lay out with the requested size, not the window's.
        ResetForOpen();
        if (L.count > 2) {
            L.hover = 2;
            L.hoverHit = Hit::Row;
        }
        bool ok = RenderToPng(path, (float)widthDip, (float)heightDip, dpiScale,
                              [&](ID2D1RenderTarget* rt) { PaintList(rt, (float)widthDip, (float)heightDip, true); });
        L.surf.hwnd = saved;
        return ok;
    }
    L.wDip = (float)widthDip;
    L.hDip = (float)heightDip;
    return RenderToPng(path, (float)widthDip, (float)heightDip, dpiScale,
                       [&](ID2D1RenderTarget* rt) { PaintList(rt, (float)widthDip, (float)heightDip, true); });
}

// ---------------------------------------------------------------------------
// Harness self test
// ---------------------------------------------------------------------------
#ifdef SCM_HARNESS
namespace {
namespace scmui {

void SetKeys(std::initializer_list<int> down) {
    BYTE keys[256]{};
    for (int vk : down) keys[vk] = 0x80;
    SetKeyboardState(keys);
}

void Key(HWND h, WPARAM vk, std::initializer_list<int> mods = {}) {
    SetKeys(mods);
    SendMessageW(h, WM_KEYDOWN, vk, 0);
    SetKeys({});
}

void Type(HWND h, const wchar_t* s) {
    for (; *s; s++) SendMessageW(h, WM_CHAR, *s, 0);
}

int SelCount() { return (int)SelectedIndices().size(); }

std::wstring TestDir() {
    WCHAR exe[MAX_PATH];
    GetModuleFileNameW(nullptr, exe, MAX_PATH);
    std::wstring dir = exe;
    dir.resize(dir.find_last_of(L'\\'));
    dir.resize(dir.find_last_of(L'\\'));
    dir += L"\\test-ui";
    CreateDirectoryW(dir.c_str(), nullptr);
    dir += L"\\v11";
    CreateDirectoryW(dir.c_str(), nullptr);
    return dir;
}

}  // namespace scmui
}  // namespace

int Harness_TestUi() {
    int fails = 0;
    auto check = [&](bool ok, const wchar_t* what) {
        Wh_Log(L"%s %s", ok ? L"ok  " : L"FAIL", what);
        if (!ok) fails++;
    };
    check(EnsureFactories() && EnsureFonts(), L"factories and fonts");
    Wh_Log(L"font family: %s, icons: %s, line height %.1f", T.family.c_str(), T.iconFamily.c_str(), T.lineH);

    // Ditto size import (reads HKCU\Software\Ditto only).
    ImportDittoSizes();
    check(GetState(L"ImportedDittoSizes", 0) == 1, L"Ditto sizes imported once");
    Wh_Log(L"List_6400x2520_CX = %d, Editor_6400x2520_CX = %d", GetState(L"List_6400x2520_CX", -1),
           GetState(L"Editor_6400x2520_CX", -1));

    // Off-screen window, never shown.
    check(EnsureListWindow(), L"list window created");
    HWND h = L.surf.hwnd;
    SetWindowPos(h, nullptr, -32000, -32000, 450, 400, SWP_NOZORDER | SWP_NOACTIVATE);
    check(!IsWindowVisible(h), L"window stays hidden");
    ResetForOpen();
    int total = L.count;
    Wh_Log(L"rows in list: %d (sample mode %d)", total, (int)SampleMode());
    check(total >= 10, L"list has rows");

    Key(h, VK_DOWN);
    check(L.caret == 1 && SelCount() == 1, L"Down moves the caret");
    Key(h, VK_DOWN, {VK_SHIFT});
    check(L.caret == 2 && SelCount() == 2 && IsSel(1) && IsSel(2), L"Shift+Down extends the selection");
    Key(h, VK_UP);
    check(L.caret == 1 && SelCount() == 1, L"Up collapses the selection");
    Key(h, VK_END);
    check(L.caret == total - 1, L"End goes to the last row");
    Key(h, VK_HOME);
    check(L.caret == 0, L"Home goes to the first row");
    Key(h, 'A', {VK_CONTROL});
    check(L.selAll && SelCount() == total, L"Ctrl+A selects everything");
    Key(h, VK_DOWN);
    check(!L.selAll && SelCount() == 1, L"a move after Ctrl+A selects one row");

    // Typing goes to search; the query runs after the debounce.
    Type(h, L"git");
    check(L.search == L"git" && L.q.search.empty(), L"typing fills the search box (debounced)");
    SendMessageW(h, WM_TIMER, kTimerSearch, 0);
    check(L.q.search == L"git" && L.count >= 1 && L.count < total, L"search filters the list");
    Wh_Log(L"'git' matches %d rows", L.count);
    Key(h, VK_BACK);
    check(L.search == L"gi", L"Backspace edits the search");
    Key(h, VK_ESCAPE);
    check(L.search.empty() && L.count == total, L"Esc clears the search first");
    L.hideRequested = false;
    Key(h, VK_ESCAPE);
    check(L.hideRequested, L"second Esc closes the list");

    // Delete asks first; Esc keeps the clip.
    ResetForOpen();
    Key(h, VK_DOWN);
    Key(h, VK_DELETE);
    check(L.mode == DockMode::ConfirmDelete && L.confirmCount == 1, L"Delete shows the confirm bar");
    Key(h, VK_ESCAPE);
    check(L.mode == DockMode::Search && L.count == total, L"Esc cancels the delete");

    // New group name entry in the dock.
    Key(h, VK_F7, {VK_CONTROL});
    check(L.mode == DockMode::NewGroup, L"Ctrl+F7 starts a new group");
    Type(h, L"Work");
    check(L.nameText == L"Work" && L.search.empty(), L"typing names the group");
    Key(h, VK_ESCAPE);
    check(L.mode == DockMode::Search, L"Esc cancels the new group");

    // Hit testing at 450 x 400 DIPs (window is at 96 dpi or more; use the layout).
    Layout l = CurrentLayout();
    auto mid = [](const D2D1_RECT_F& r) { return std::pair<float, float>{(r.left + r.right) / 2, (r.top + r.bottom) / 2}; };
    L.scrollY = 0;
    auto [rx, ry] = std::pair<float, float>{l.list.left + 40, l.list.top + l.rowH / 2};
    check(HitTest(l, rx, ry).what == Hit::Row && HitTest(l, rx, ry).row == 0, L"hit test: first row");
    check(HitTest(l, rx, ry + l.stride * 2).row == 2, L"hit test: third row");
    auto [fx, fy] = mid(l.folder);
    check(HitTest(l, fx, fy).what == Hit::Folder, L"hit test: folder button");
    auto [mx, my] = mid(l.menu);
    check(HitTest(l, mx, my).what == Hit::Menu, L"hit test: menu button");
    auto [cx, cy] = mid(l.close);
    check(HitTest(l, cx, cy).what == Hit::Close, L"hit test: close button");
    auto [sx, sy] = mid(l.search);
    check(HitTest(l, sx, sy).what == Hit::Search, L"hit test: search box");
    check(HitTest(l, l.w - 5, l.h / 2).what == Hit::Caption, L"hit test: right strip drags the window");

    // Scrolling: wheel moves the target; content clamps.
    SendMessageW(h, WM_MOUSEWHEEL, MAKEWPARAM(0, (WORD)(-120)), 0);
    check(L.scrollTarget > 0 || MaxScroll(l) == 0, L"wheel scrolls down");

    // Group navigation (sample group 107 has two clips).
    if (SampleMode()) {
        OpenGroup(107, L"Snippets");
        check(L.count == 2, L"opening a group shows its clips");
        Key(h, VK_BACK);
        check(L.q.groupId == -1 && L.count == total, L"Backspace goes back to all clips");
    }

    // Renders.
    std::wstring dir = TestDir();
    int savedLines = g_set.linesPerRow;
    for (float s : {1.0f, 1.5f, 2.0f}) {
        WCHAR name[64];
        swprintf_s(name, L"\\list-5lines-%.1fx.png", s);
        check(List_RenderToPng(dir + name, 450, 400, s), name);
    }
    g_set.linesPerRow = 1;
    ResetFonts();
    check(List_RenderToPng(dir + L"\\list-1line-1.5x.png", 450, 400, 1.5f), L"render 1 line");
    g_set.linesPerRow = savedLines;
    ResetFonts();
    check(List_RenderToPng(dir + L"\\list-tall-1.5x.png", 640, 760, 1.5f), L"render tall");

    // Group view, search state and confirm bar.
    auto renderState = [&](const wchar_t* file, const std::function<void()>& setup) {
        L.wDip = 450;
        L.hDip = 400;
        HWND saved = L.surf.hwnd;
        L.surf.hwnd = nullptr;
        ResetForOpen();
        setup();
        bool ok = RenderToPng(dir + file, 450, 400, 1.5f, [&](ID2D1RenderTarget* rt) { PaintList(rt, 450, 400, true); });
        L.surf.hwnd = saved;
        check(ok, file);
    };
    if (SampleMode())
        renderState(L"\\list-group.png", [] {
            OpenGroup(107, L"Snippets");
            L.hoverHit = Hit::Back;
        });
    renderState(L"\\list-search.png", [] {
        L.search = L"select";
        CommitSearch();
        L.hoverHit = Hit::Folder;
    });
    renderState(L"\\list-confirm.png", [] {
        SetCaret(1, false);
        SetCaret(3, true);
        RequestDelete();
        L.hoverHit = Hit::Close;
    });
    renderState(L"\\list-empty.png", [] {
        L.search = L"zzzz no such clip";
        CommitSearch();
    });
    // Preview of the code snippet.
    renderState(L"\\x.png", [] { SetCaret(2, false); });
    LoadPreviewContent();
    check(RenderToPng(dir + L"\\preview-text.png", 480, 400, 1.5f,
                      [](ID2D1RenderTarget* rt) { PaintPreview(rt, 480, 400, true); }),
          L"preview text");
    SetCaret(4, false);
    LoadPreviewContent();
    check(RenderToPng(dir + L"\\preview-image.png", 480, 400, 1.5f,
                      [](ID2D1RenderTarget* rt) { PaintPreview(rt, 480, 400, true); }),
          L"preview image");
    DeleteFileW((dir + L"\\x.png").c_str());

    // Pins: clicking the pin toggles sticky without selecting or pasting.
    {
        ResetForOpen();
        L.scrollY = L.scrollTarget = 0;
        Layout pl = CurrentLayout();
        float ps = L.surf.Scale();
        auto click = [&](UINT msg, float x, float y, WPARAM wp = 0) {
            SendMessageW(h, msg, wp, MAKELPARAM((int)(x * ps), (int)(y * ps)));
        };
        int pinned0 = StickyRunLength();
        int64_t third = IdAt(pinned0 + 1);
        D2D1_RECT_F pin = PinRect(RowRect(pl, pinned0 + 1));
        click(WM_LBUTTONDOWN, (pin.left + pin.right) / 2, (pin.top + pin.bottom) / 2);
        click(WM_LBUTTONUP, (pin.left + pin.right) / 2, (pin.top + pin.bottom) / 2);
        check(StickyRunLength() == pinned0 + 1 && IdAt(0) == third && L.caret != pinned0 + 1,
              L"pin click makes the clip sticky, on top, without selecting it");
        check(!L.hideRequested, L"pin click does not paste");
        // Make sure there are at least three pinned rows to reorder.
        while (StickyRunLength() < 3) {
            int n = StickyRunLength();
            DataSetSticky(IdAt(n), true, false);
            Reload();
        }
        int n = StickyRunLength();
        std::vector<int64_t> before;
        for (int i = 0; i < n; i++) before.push_back(IdAt(i));
        pl = CurrentLayout();
        auto rowY = [&](int i) { return RowRect(pl, i).top + pl.rowH / 2; };
        float x0 = pl.list.left + 60;
        // Drag the top pinned row below the second one.
        click(WM_LBUTTONDOWN, x0, rowY(0));
        click(WM_MOUSEMOVE, x0, rowY(0) + 2);
        check(!L.dragActive, L"a 2 px move does not start a drag");
        click(WM_MOUSEMOVE, x0, rowY(1) + 6);
        check(L.dragActive && L.dragInsert == 2, L"moving past kDragStart starts a drag and finds the slot");
        click(WM_LBUTTONUP, x0, rowY(1) + 6);
        std::vector<int64_t> after;
        for (int i = 0; i < n; i++) after.push_back(IdAt(i));
        std::vector<int64_t> want = before;
        std::rotate(want.begin(), want.begin() + 1, want.begin() + 2);
        check(!L.dragActive && after == want, L"drop reorders the pinned rows (a b c -> b a c)");
        check(StickyRunLength() == n, L"reordering keeps the same pinned count");
        // Escape cancels.
        click(WM_LBUTTONDOWN, x0, rowY(0));
        click(WM_MOUSEMOVE, x0, rowY(0) + 20);
        bool started = L.dragActive;
        Key(h, VK_ESCAPE);
        std::vector<int64_t> after2;
        for (int i = 0; i < n; i++) after2.push_back(IdAt(i));
        check(started && !L.dragActive && !L.dragPending && after2 == after, L"Escape cancels a drag");
        // Plain click on a non-sticky row selects it and does not drag.
        click(WM_LBUTTONDOWN, x0, rowY(n));
        check(!L.dragPending && L.caret == n, L"click on an unpinned row selects it only");
        click(WM_LBUTTONUP, x0, rowY(n));
    }

    // Menu layout and hit testing.
    {
        ResetForOpen();
        SetCaret(1, false);
        auto items = ContextMenuItems();
        MenuLevel lv;
        lv.items = &items;
        MenuLayout(lv, 1.0f);
        check(lv.wDip >= kMenuMinW && lv.hDip > 200, L"context menu has a sensible size");
        bool mono = true;
        for (size_t i = 1; i < lv.top.size(); i++) mono = mono && lv.top[i] >= lv.top[i - 1] + lv.height[i - 1] - 0.01f;
        check(mono, L"menu items stack without overlap");
        float cx = lv.wDip / 2;
        check(MenuItemAt(lv, cx, lv.top[0] + 4) == 0, L"hit test: first menu item");
        check(MenuItemAt(lv, cx, lv.top[4] + 2) == -1 && items[4].separator, L"hit test: separator is not an item");
        check(MenuItemAt(lv, 1, lv.top[0] + 4) == -1 && MenuItemAt(lv, cx, -5) == -1, L"hit test: padding and outside");
        check(MenuNext(lv, -1, +1) == 0 && MenuNext(lv, 3, +1) == 5, L"keyboard walk skips separators");
        check(MenuNext(lv, 0, -1) == (int)items.size() - 1, L"keyboard walk wraps");
        size_t special = 2;
        check(!items[special].sub.empty() && items[special].sub.size() == std::size(kSpecialNames), L"special paste has its submenu");
        auto groups = GroupsMenuItems();
        check(groups.size() >= 3 && groups.front().id == cmdOpenMain && groups.back().id == cmdNewGroup, L"groups menu shape");
        MenuLevel big;
        big.items = &items;
        MenuLayout(big, 1.5f);
        check(big.scale == 1.5f && std::fabs(big.wDip - lv.wDip) < 0.01f, L"layout in DIPs does not change with scale");
        POINT o = MenuRootOrigin(POINT{100, 100}, 200, 300);
        check(o.x == 100 && o.y == 100, L"menu opens at the point when it fits");
    }

    // Menu and drag renders.
    for (float s : {1.0f, 1.5f}) {
        WCHAR name[64];
        swprintf_s(name, L"\\list-pins-%.1fx.png", s);
        L.wDip = 450;
        L.hDip = 400;
        HWND saved = L.surf.hwnd;
        L.surf.hwnd = nullptr;
        ResetForOpen();
        L.hover = StickyRunLength() + 1;
        L.hoverHit = Hit::Row;
        check(RenderToPng(dir + name, 450, 400, s, [&](ID2D1RenderTarget* rt) { PaintList(rt, 450, 400, true); }), name);
        swprintf_s(name, L"\\list-drag-%.1fx.png", s);
        ResetForOpen();
        L.hover = -1;
        L.hoverHit = Hit::None;
        L.dragSticky = StickyRunLength();
        L.dragActive = L.dragSticky >= 2;
        L.dragFrom = 0;
        L.dragInsert = 2;
        L.dragGrab = 12;
        L.dragY = CurrentLayout().list.top + CurrentLayout().stride * 1.4f;
        check(L.dragActive, L"drag render state has pinned rows");
        check(RenderToPng(dir + name, 450, 400, s, [&](ID2D1RenderTarget* rt) { PaintList(rt, 450, 400, true); }), name);
        L.dragActive = false;
        L.dragFrom = L.dragInsert = -1;
        L.surf.hwnd = saved;
    }
    {
        auto renderMenu = [&](const wchar_t* file, float s, const std::vector<UiMenuItem>& items, int hot, int subOf) {
            MenuLevel root;
            root.items = &items;
            MenuLayout(root, s);
            root.hover = hot;
            root.open = subOf;
            MenuLevel sub;
            float subX = 0, canvasW = root.wDip + 16, canvasH = root.hDip + 16;
            if (subOf >= 0) {
                sub.items = &items[(size_t)subOf].sub;
                MenuLayout(sub, s);
                sub.hover = 1;
                subX = root.wDip - kMenuOverlap;
                canvasW = subX + sub.wDip + 16;
            }
            float subY = subOf >= 0 ? root.top[(size_t)subOf] - kMenuPad : 0;
            canvasH = std::max(root.hDip, subY + sub.hDip) + 16;
            bool ok = RenderToPng(dir + file, canvasW, canvasH, s, [&](ID2D1RenderTarget* rt) {
                rt->SetTransform(D2D1::Matrix3x2F::Translation(8, 8));
                PaintMenu(rt, root, true);
                if (subOf >= 0) {
                    rt->SetTransform(D2D1::Matrix3x2F::Translation(8 + subX, 8 + subY));
                    PaintMenu(rt, sub, true);
                }
                rt->SetTransform(D2D1::Matrix3x2F::Identity());
            });
            check(ok, file);
        };
        ResetForOpen();
        SetCaret(1, false);
        auto items = ContextMenuItems();
        for (float s : {1.0f, 1.5f}) {
            WCHAR name[64];
            swprintf_s(name, L"\\menu-context-%.1fx.png", s);
            renderMenu(name, s, items, 2, 2);
        }
        auto groups = GroupsMenuItems();
        renderMenu(L"\\menu-groups.png", 1.5f, groups, 0, -1);
    }

    // Icons.
    for (int size : {16, 32, 256}) {
        Com<IWICBitmap> bmp = RenderIconBitmap(size);
        WCHAR name[64];
        swprintf_s(name, L"\\icon-%d.png", size);
        check(bmp && SavePng(bmp.get(), dir + name), name);
        HICON icon = MakeAppIcon(size);
        check(icon != nullptr, L"MakeAppIcon returns an icon");
        DestroyIcon(icon);
    }

    // Helper windows off-screen: build them and print them to PNG.
    auto printWindow = [&](HWND w, const wchar_t* file) {
        if (!w) return false;
        SetWindowPos(w, nullptr, -32000, -32000, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
        RECT r;
        GetWindowRect(w, &r);
        int cw = r.right - r.left, ch = r.bottom - r.top;
        HDC screen = GetDC(nullptr);
        HDC mem = CreateCompatibleDC(screen);
        HBITMAP bmp = CreateCompatibleBitmap(screen, cw, ch);
        HGDIOBJ old = SelectObject(mem, bmp);
        BOOL ok = PrintWindow(w, mem, PW_RENDERFULLCONTENT);
        SelectObject(mem, old);
        Com<IWICBitmap> wb;
        F.wic->CreateBitmapFromHBITMAP(bmp, nullptr, WICBitmapIgnoreAlpha, wb.put());
        bool saved = wb && SavePng(wb.get(), dir + file);
        DeleteObject(bmp);
        DeleteDC(mem);
        ReleaseDC(nullptr, screen);
        return ok && saved;
    };
    (void)printWindow;
    check(IsWindow(h) && !IsWindowVisible(h), L"list window never shown");
    List_Destroy();
    check(!L.surf.hwnd, L"List_Destroy cleans up");
    Wh_Log(L"ui test: %d failure(s)", fails);
    return fails ? 1 : 0;
}
#endif

// ---------------------------------------------------------------------------
// 50-settings.cpp : the mod's own settings window. A sidebar of pages, grouped
// cards, toggles, dropdowns, sliders, key boxes and colour chips, all drawn
// with Direct2D in the style of Seamless Dictate's settings. It shows the same
// settings as Windhawk's page for this mod and saves them with one elevated
// windhawk-cli call, so the two stay in step. Windhawk then calls
// WhTool_ModSettingsChanged by itself.
//
// One window, one Direct2D target that fills the whole client rect (the window
// edge is rounded by DWM, never by us). Text typed into a number, text or colour
// box goes through one small native EDIT that sits on top of the box while it is
// edited. Key boxes read WM_KEYDOWN themselves.
// ---------------------------------------------------------------------------

template <class T>
class SetCom {
   public:
    T* p = nullptr;
    SetCom() = default;
    SetCom(const SetCom& o) : p(o.p) {
        if (p) p->AddRef();
    }
    SetCom& operator=(const SetCom& o) {
        if (o.p) o.p->AddRef();
        reset();
        p = o.p;
        return *this;
    }
    ~SetCom() { reset(); }
    void reset() {
        if (p) p->Release();
        p = nullptr;
    }
    T** put() {
        reset();
        return &p;
    }
    T* get() const { return p; }
    T* operator->() const { return p; }
    explicit operator bool() const { return p != nullptr; }
};

struct SetField {
    enum Kind { Choice, Number, Text, Hotkey, Check, Color };
    Kind kind;
    PCWSTR key;
    PCWSTR label;
    PCWSTR desc = nullptr;
    PCWSTR def = L"";                                // The schema default ("Reset to suggested").
    std::vector<std::pair<PCWSTR, PCWSTR>> options;  // Value, label.
    int min = 0, max = 0;
    int page = 0;        // Which sidebar page shows it.
    PCWSTR group = L"";  // Heading above it on that page.
    std::wstring value;  // As loaded, so a save writes only what changed.
    std::wstring cur;    // What the window shows now.
};

// Names, descriptions and option labels match the ==WindhawkModSettings== block word for word.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
        {K::Hotkey, L"hotkey", L"Open the clip list", L"Keys that open your clips, like \"Win+V\", \"Ctrl+`\" or \"Ctrl+Shift+V\".", L"Win+V", {}, 0, 0, 0, L"Open the list"},
        {K::Check, L"takeOverWinV", L"Replace Windows clipboard history", L"Turns off Windows clipboard history and its own Win+V, so Win+V opens this list instead. Turning it off puts back only what the mod changed; Windows gets Win+V back after you sign in again.", L"1", {}, 0, 0, 0, L"Open the list"},
        {K::Hotkey, L"hotkey2", L"Second key to open the list", L"Another key combination that opens the list. Leave empty for none.", L"", {}, 0, 0, 0, L"Open the list"},
        {K::Hotkey, L"plainTextHotkey", L"Key to paste as plain text", L"Pastes what's on the clipboard now, without its formatting. Leave empty for none.", L"", {}, 0, 0, 0, L"Paste"},
        {K::Choice, L"positionHotkeys", L"Number keys", L"Hold these keys and press 1 to 9 or 0 to paste clip 1 to 10 without opening the list.", L"off", {{L"off", L"Off"}, {L"ctrlWin", L"Ctrl + Win + number"}, {L"ctrlAlt", L"Ctrl + Alt + number"}, {L"altWin", L"Alt + Win + number"}}, 0, 0, 0, L"Number keys"},
        {K::Check, L"positionHotkeysPaste", L"Number keys paste right away", L"When off, they only put the clip on the clipboard.", L"1", {}, 0, 0, 0, L"Number keys"},
        {K::Check, L"positionHotkeysMoveToTop", L"Number keys move the clip to the top", nullptr, L"1", {}, 0, 0, 0, L"Number keys"},
        {K::Choice, L"openAt", L"Where the list opens", nullptr, L"caret", {{L"caret", L"At the text cursor"}, {L"cursor", L"At the mouse pointer"}, {L"remember", L"Where you left it"}}, 0, 0, 1, L"Size and place"},
        {K::Number, L"windowWidth", L"List width", L"200 to 2000 (Suggested: 450). If you resize the list, it keeps your size for that screen layout.", L"450", {}, 200, 2000, 1, L"Size and place"},
        {K::Number, L"windowHeight", L"List height", L"150 to 2000 (Suggested: 400).", L"400", {}, 150, 2000, 1, L"Size and place"},
        {K::Number, L"linesPerRow", L"Lines per clip", L"1 to 10 (Suggested: 5). How many lines of text each clip shows.", L"5", {}, 1, 10, 1, L"Rows"},
        {K::Check, L"showPositions", L"Number the first ten clips", nullptr, L"1", {}, 0, 0, 1, L"Rows"},
        {K::Check, L"showThumbnails", L"Show image previews", nullptr, L"1", {}, 0, 0, 1, L"Rows"},
        {K::Check, L"closeOnFocusLoss", L"Close when you click away", nullptr, L"1", {}, 0, 0, 1, L"Behavior"},
        {K::Check, L"alwaysOnTop", L"Keep the list on top", nullptr, L"1", {}, 0, 0, 1, L"Behavior"},
        {K::Check, L"confirmDelete", L"Ask before deleting", nullptr, L"1", {}, 0, 0, 1, L"Behavior"},
        {K::Text, L"fontName", L"Font", L"Any installed font (Suggested: FiraCode Nerd Font).", L"FiraCode Nerd Font", {}, 0, 0, 2, L"Text"},
        {K::Choice, L"fontWeight", L"Font weight", nullptr, L"medium", {{L"light", L"Light"}, {L"normal", L"Regular"}, {L"medium", L"Medium"}, {L"semibold", L"Semibold"}, {L"bold", L"Bold"}}, 0, 0, 2, L"Text"},
        {K::Number, L"fontSize", L"Font size", L"7 to 24 points (Suggested: 10).", L"10", {}, 7, 24, 2, L"Text"},
        {K::Choice, L"blurMode", L"Background", nullptr, L"acrylic", {{L"acrylic", L"Blurred glass"}, {L"mica", L"Mica (tinted by the wallpaper)"}, {L"none", L"Solid color"}}, 0, 0, 2, L"Background"},
        {K::Number, L"backgroundOpacity", L"Background tint", L"0 to 100 (Suggested: 55). How much the dark tint covers the blur.", L"55", {}, 0, 100, 2, L"Background"},
        {K::Color, L"accentColor", L"Accent color", L"Color of the selection and the border (Suggested: #89B4FA, Catppuccin blue).", L"#89B4FA", {}, 0, 0, 2, L"Colors"},
        {K::Color, L"accentColor2", L"Second accent color", L"The border fades from the accent color to this one (Suggested: #CBA6F7, Catppuccin mauve).", L"#CBA6F7", {}, 0, 0, 2, L"Colors"},
        {K::Check, L"ownBorder", L"Draw a window border", L"Leave off when another mod, like Seamless Borders, already draws borders around windows. Menus always get their border.", L"0", {}, 0, 0, 2, L"Edges and motion"},
        {K::Check, L"animations", L"Animations", L"The list slides and fades in and out, and hover glows fade. Also off when Windows animation effects are off.", L"1", {}, 0, 0, 2, L"Edges and motion"},
        {K::Check, L"gradientBorder", L"Gradient border", L"When off, the border uses only the accent color.", L"1", {}, 0, 0, 2, L"Edges and motion"},
        {K::Number, L"cornerRadius", L"Corner roundness", L"0 to 24 (Suggested: 8). Rounds the selection and the search bar.", L"8", {}, 0, 24, 2, L"Edges and motion"},
        {K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Save, then reopen settings to apply.", L"1", {}, 0, 100, 2, L"Settings window"},
        {K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Save, then reopen settings to apply.", L"0", {}, 0, 100, 2, L"Settings window"},
        {K::Choice, L"settingsTitleButtons", L"Title bar buttons", L"Who draws minimize, maximize and close on the window's own title bar. Windows buttons look like every other app's, title bar mods included. Save, then reopen settings to apply.", L"native", {{L"native", L"Windows buttons (like other apps)"}, {L"builtin", L"Built-in buttons"}}, 0, 100, 2, L"Settings window"},
        {K::Check, L"settingsTrayIcon", L"Tray icon", L"A Clipboard Manager icon in the system tray. Click it to open the clip list, right-click it for a menu with Settings.", L"1", {}, 0, 100, 2, L"Settings window"},
        {K::Number, L"maxClips", L"Clips to keep", L"0 to 100000 (Suggested: 500). Past this count the oldest clips are deleted. Pinned clips, clips in groups and clips set to never delete stay. 0 keeps everything.", L"500", {}, 0, 100000, 3, L"Keep"},
        {K::Number, L"expireDays", L"Delete clips older than (days)", L"0 to 3650 (Suggested: 0). 0 keeps clips however old they are.", L"0", {}, 0, 3650, 3, L"Keep"},
        {K::Check, L"saveImages", L"Save images", nullptr, L"1", {}, 0, 0, 3, L"Save"},
        {K::Check, L"saveFiles", L"Save copied files", L"Saves the list of files you copy in File Explorer, so you can paste them again.", L"1", {}, 0, 0, 3, L"Save"},
        {K::Check, L"saveRichText", L"Save formatting", L"Keeps the formatting of text copied from web pages and Word. When off, only the plain text is saved.", L"1", {}, 0, 0, 3, L"Save"},
        {K::Number, L"maxClipMB", L"Largest copy to save (MB)", L"1 to 512 (Suggested: 64). Bigger copies aren't saved.", L"64", {}, 1, 512, 3, L"Save"},
        {K::Check, L"allowDuplicates", L"Keep repeat copies", L"When off, copying the same thing again moves the old clip to the top.", L"0", {}, 0, 0, 3, L"Repeats"},
        {K::Check, L"moveToTopOnPaste", L"Move a clip to the top when you paste it", nullptr, L"1", {}, 0, 0, 3, L"Repeats"},
        {K::Text, L"includeApps", L"Save copies from these apps", L"App file names separated by \";\", with * and ? as wildcards. \"*\" means every app.", L"*", {}, 0, 0, 3, L"Apps"},
        {K::Text, L"excludeApps", L"Never save copies from these apps", L"For example \"KeePass.exe;1Password.exe\". Copies that password managers mark as private are always skipped.", L"", {}, 0, 0, 3, L"Apps"},
        {K::Choice, L"pasteKeys", L"Paste with", nullptr, L"ctrlV", {{L"ctrlV", L"Ctrl+V"}, {L"shiftInsert", L"Shift+Insert"}}, 0, 0, 4, L"Paste"},
        {K::Number, L"pasteDelay", L"Paste delay (ms)", L"0 to 2000 (Suggested: 50). Wait this long after switching back to the app before pasting. Raise it if a paste lands in the wrong place.", L"50", {}, 0, 2000, 4, L"Paste"},
        {K::Choice, L"multiSeparator", L"Between several pasted clips", nullptr, L"newline", {{L"newline", L"A new line"}, {L"space", L"A space"}, {L"comma", L"A comma and a space"}, {L"none", L"Nothing"}}, 0, 0, 4, L"Paste"},
        {K::Choice, L"searchMode", L"Search finds", nullptr, L"contains", {{L"contains", L"Clips that contain the text"}, {L"allWords", L"Clips with all the words, in any order"}, {L"startsWith", L"Clips that start with the text"}}, 0, 0, 4, L"Search"},
        {K::Check, L"searchFullText", L"Search the whole clip", L"When off, search looks only at the start of each clip, which is faster with very large clips.", L"1", {}, 0, 0, 4, L"Search"},
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Keys", L"Choose the keys that open your clips and paste them.", 0xE765},
{L"List window", L"How big the list is, where it opens and how it behaves.", 0xE8FD},
{L"Look", L"Font, background, colors of the list, and this window.", 0xE790},
{L"Clips", L"What gets saved, how long it stays and which apps are listened to.", 0xE8C8},
{L"Paste and search", L"How a clip is pasted and how the search box matches.", 0xE721},
{L"About", L"Version, credits, support and links.", 0xE946},
};
constexpr int kSetPageCount = (int)(sizeof(kSetPages) / sizeof(kSetPages[0]));
// About sits apart at the end of the sidebar, as in Seamless Dictate.
constexpr int kSetAboutPage = kSetPageCount - 1;
constexpr float kSetAboutGap = 17;

// All sizes are DIPs; the render target does the scaling.
constexpr float kSetPadX = 40, kSetMaxW = 720, kSetRowMin = 56, kSetRowGap = 8, kSetBoxH = 32, kSetRowPad = 16,
                kSetDropItem = 32, kSetRailTop = 76, kSetRailItem = 36, kSetRailPitch = 40;
// The sidebar is a floating dock: dragged between min and max, or collapsed to an icon rail.
constexpr float kSetDockGap = 10, kSetRailDef = 232, kSetRailMin = 200, kSetRailMax = 380, kSetRailMini = 60,
                kSetRailSnap = 130, kSetEdgeGrab = 5;
// The footer is a floating pill dock at the bottom right of the page.
constexpr float kSetFootBtnH = 36, kSetFootPad = 8, kSetFootH = kSetFootBtnH + 2 * kSetFootPad, kSetFootGap = 14;
// The glass tint is one layer over the whole window, title bar included, so the two always match.
constexpr float kSetGlassTint = 0.42f, kSetNativeFade = 56;
constexpr int kSetChipCount = 10;
constexpr UINT32 kSetChips[kSetChipCount] = {mocha::blue,   mocha::sapphire, mocha::teal, mocha::green, mocha::yellow,
                                             mocha::peach,  mocha::red,      mocha::pink, mocha::mauve, mocha::lavender};
constexpr UINT_PTR kSetTimerId = 1;
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetDittoUrl = L"https://github.com/sabrogden/Ditto";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Clipboard%20Manager%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Clipboard Manager";
// The self-drawn title bar. Everything below it is laid out as before, in "content" DIPs.
static float kSetCapH = 40;
constexpr float kSetCapBtnW = 46, kSetHoverMs = 120;

struct SetItem {
    enum Type { Group, Row, Banner, About, Link, Support } type = Row;
    int field = -1;  // Row: index into fields.
    float y = 0, h = 0;
    std::wstring text, sub, url;
};

// What the pointer is over. id picks the hover glow.
struct SetHit {
    enum Kind { None, Rail, Row, Control, Slider, Clear, Chip, Footer, Drop, Link, Scroll, Popup, Caption, RailToggle, RailEdge } kind = None;
    int a = -1, b = -1;
    int id = -1;
};

struct SetWindow {
    HWND hwnd = nullptr, edit = nullptr, owner = nullptr;
    HFONT editFont = nullptr;
    HBRUSH editBrush = nullptr;
    std::vector<SetField> fields = Set_MakeFields();
    std::vector<SetItem> items;
    UINT dpi = 96;
    float cw = 980, ch = 700;  // Content size in DIPs: the client area below the title bar.
    HICON iconSmall = nullptr, iconBig = nullptr;
    int capDown = 0;  // Title bar button held down: 1 minimize, 2 maximize, 3 close.
    bool capTracking = false, active = true;
    bool nativeTitle = false;  // Windows draws the title bar and its buttons.
    bool nativeButtons = false;  // Own title bar, but Windows draws minimize, maximize and close.
    bool glass = false;        // Acrylic behind the window; the page is drawn see-through.
    ULONGLONG lastTick = 0;
    int page = 0, recording = -1, editing = -1, focus = -1, openSel = -1;
    bool kbd = false;  // Show the focus ring (after a Tab).
    D2D1_RECT_F dropRect{};
    int dropHover = -1;
    float scrollY = 0, scrollTarget = 0, contentH = 0, contentX = 0, contentW = 720, pageT = 1;
    SetHit hover;
    int dragSlider = -1;
    bool dragScroll = false, tracking = false, timer = false;
    float dragOff = 0;
    // Sidebar dock: railW is the chosen open width, railCur the drawn width (eased toward
    // kSetRailMini when collapsed). railGlow / footGlow ease the dock borders on hover.
    float railW = kSetRailDef, railCur = kSetRailDef, railGlow = 0, footGlow = 0;
    bool railCollapsed = false, dragRail = false;
    float mouseX = -1, mouseY = -1;
    std::map<int, float> glow;  // Eased hover amount by hit id.
    std::map<int, float> knob;  // Eased toggle position by field.
    std::wstring status;
    bool statusError = false;
    bool saving = false, destroyed = false, render = false;
    SetCom<ID2D1HwndRenderTarget> rt;
    SetCom<ID2D1BitmapRenderTarget> layer;  // The page, drawn off screen so the footer can blur it.
    D2D1_SIZE_F layerSize{};
    std::wstring family, iconFamily;
    SetCom<IDWriteTextFormat> fLabel, fHint, fTitle, fIntro, fSection, fValue, fValueC, fButton, fIcon, fIconS,
        fIconL, fBig, fSmall, fStatusLine, fCap, fCapGlyph, fRailName;
    RECT normalRect{};  // Last restored-state rect, remembered on close.
    COLORREF customColors[16] = {};
};

static std::shared_ptr<SetWindow> g_setWin;
static UINT g_setForceDpi;  // Harness renders at a chosen scale.
static SetCom<ID2D1Factory> g_setD2d;
static SetCom<IDWriteFactory> g_setDw;
static SetCom<IWICImagingFactory> g_setWic;
#ifdef SCM_HARNESS
static std::wstring g_setFakeKeyStatus;  // Lets the test render the hotkey warning line.
#endif

static std::wstring Set_WindowText(HWND hwnd) {
    std::wstring text(GetWindowTextLengthW(hwnd) + 1, L'\0');
    text.resize(GetWindowTextW(hwnd, text.data(), (int)text.size()));
    return text;
}

static std::wstring Set_KeyStatusText() {
#ifdef SCM_HARNESS
    if (!g_setFakeKeyStatus.empty()) return g_setFakeKeyStatus;
#endif
    return Hotkeys_Status();
}

// Quotes one argument the way CommandLineToArgvW reads it back.
static std::wstring Set_QuoteArg(const std::wstring& arg) {
    std::wstring out = L"\"";
    for (size_t i = 0;; i++) {
        size_t slashes = 0;
        while (i < arg.size() && arg[i] == L'\\') i++, slashes++;
        if (i == arg.size()) {
            out.append(slashes * 2, L'\\');
            break;
        }
        out.append(arg[i] == L'"' ? slashes * 2 + 1 : slashes, L'\\');
        out += arg[i];
    }
    return out + L"\"";
}

// windhawk-cli.exe sits three folders above the engine
// (<Windhawk>\Engine\<version>\<arch>\windhawk.dll), next to windhawk.exe.
static std::wstring Set_CliPath() {
    WCHAR path[MAX_PATH];
    if (HMODULE engine = GetModuleHandleW(L"windhawk.dll"); engine && GetModuleFileNameW(engine, path, MAX_PATH)) {
        std::wstring dir = path;
        for (int i = 0; i < 4 && dir.find_last_of(L'\\') != std::wstring::npos; i++) dir.resize(dir.find_last_of(L'\\'));
        dir += L"\\windhawk-cli.exe";
        if (GetFileAttributesW(dir.c_str()) != INVALID_FILE_ATTRIBUTES) return dir;
    }
    if (GetModuleFileNameW(nullptr, path, MAX_PATH)) {
        std::wstring dir = path;
        dir.resize(dir.find_last_of(L'\\'));
        dir += L"\\windhawk-cli.exe";
        if (GetFileAttributesW(dir.c_str()) != INVALID_FILE_ATTRIBUTES) return dir;
    }
    return {};
}

// ---- Factories and fonts ---------------------------------------------------

static bool Set_EnsureFactories() {
    if (!g_setD2d) {
        D2D1_FACTORY_OPTIONS o{};
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &o,
                                     (void**)g_setD2d.put())))
            return false;
    }
    if (!g_setDw && FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                                               (IUnknown**)g_setDw.put())))
        return false;
    if (!g_setWic && FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                             __uuidof(IWICImagingFactory), (void**)g_setWic.put())))
        return false;
    return true;
}

static void Set_ReleaseFactories() {
    g_setWic.reset();
    g_setDw.reset();
    g_setD2d.reset();
}

static bool Set_FamilyExists(const std::wstring& name) {
    SetCom<IDWriteFontCollection> sys;
    if (name.empty() || FAILED(g_setDw->GetSystemFontCollection(sys.put(), FALSE))) return false;
    UINT32 index = 0;
    BOOL exists = FALSE;
    return SUCCEEDED(sys->FindFamilyName(name.c_str(), &index, &exists)) && exists;
}

// The font setting, or its Nerd Font build ("Fira Code" is installed as
// "FiraCode Nerd Font"), or Segoe UI.
static std::wstring Set_ResolveFamily() {
    if (Set_FamilyExists(g_set.fontName)) return g_set.fontName;
    std::wstring joined;
    for (WCHAR c : g_set.fontName)
        if (c != L' ') joined += c;
    for (const std::wstring& face : {joined + L" Nerd Font", g_set.fontName + L" Nerd Font", joined})
        if (Set_FamilyExists(face)) return face;
    return L"Segoe UI";
}

static float Set_TextW(IDWriteTextFormat* fmt, const std::wstring& text);

static SetCom<IDWriteTextFormat> Set_Fmt(const std::wstring& family, float size, int weight, bool wrap,
                                         DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_LEADING,
                                         bool vcenter = false) {
    SetCom<IDWriteTextFormat> f;
    if (FAILED(g_setDw->CreateTextFormat(family.c_str(), nullptr, (DWRITE_FONT_WEIGHT)weight, DWRITE_FONT_STYLE_NORMAL,
                                         DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", f.put())))
        return f;
    f->SetWordWrapping(wrap ? DWRITE_WORD_WRAPPING_WRAP : DWRITE_WORD_WRAPPING_NO_WRAP);
    f->SetTextAlignment(align);
    f->SetParagraphAlignment(vcenter ? DWRITE_PARAGRAPH_ALIGNMENT_CENTER : DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    if (!wrap) {
        SetCom<IDWriteInlineObject> sign;
        g_setDw->CreateEllipsisTrimmingSign(f.get(), sign.put());
        DWRITE_TRIMMING t{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
        f->SetTrimming(&t, sign.get());
    }
    return f;
}

// g_set.fontName at g_set.fontWeight; emphasis is one step heavier, never past bold.
static void Set_MakeFormats(SetWindow& w) {
    w.family = Set_ResolveFamily();
    w.iconFamily = Set_FamilyExists(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
    int base = std::clamp(g_set.fontWeight, 100, 900);
    int bold = std::max(base, std::min(700, base + 100));
    const auto L_ = DWRITE_TEXT_ALIGNMENT_LEADING, C_ = DWRITE_TEXT_ALIGNMENT_CENTER;
    w.fLabel = Set_Fmt(w.family, 14, base, true);
    w.fHint = Set_Fmt(w.family, 12.5f, base, true);
    w.fTitle = Set_Fmt(w.family, 26, bold, false);
    w.fIntro = Set_Fmt(w.family, 13.5f, base, true);
    w.fSection = Set_Fmt(w.family, 10.5f, bold, false);
    w.fValue = Set_Fmt(w.family, 13, base, false, L_, true);
    w.fValueC = Set_Fmt(w.family, 13, base, false, C_, true);
    w.fButton = Set_Fmt(w.family, 13.5f, bold, false, C_, true);
    w.fBig = Set_Fmt(w.family, 20, bold, false);
    w.fSmall = Set_Fmt(w.family, 12, base, false, L_, true);
    w.fIcon = Set_Fmt(w.iconFamily, 16, 400, false, C_, true);
    w.fIconS = Set_Fmt(w.iconFamily, 12, 400, false, C_, true);
    w.fIconL = Set_Fmt(w.iconFamily, 34, 400, false, C_, true);
    w.fCap = Set_Fmt(w.family, 13, bold, false, L_, true);
    w.fCapGlyph = Set_Fmt(w.iconFamily, 10, 400, false, C_, true);
    w.fStatusLine = Set_Fmt(w.family, 12.5f, base, false, L_, true);
    // The sidebar name must never clip at the narrowest open width: 18 down to 15.5 (above 85%).
    const float railW = kSetRailMin - 90 - 10;
    for (float size = 18; size >= 15.5f; size -= 0.5f) {
        w.fRailName = Set_Fmt(w.family, size, bold, false, L_, true);
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Clipboard") <= railW) break;
    }
}

// ---- Values ----------------------------------------------------------------

static std::wstring Set_FieldValue(const SetField& f) {
    switch (f.kind) {
        case SetField::Number: {
            if (f.cur.empty()) return f.value;
            return std::to_wstring(std::clamp(_wtoi(f.cur.c_str()), f.min, f.max));
        }
        case SetField::Check:
            return f.cur == L"0" || f.cur.empty() ? L"0" : L"1";
        default:
            return f.cur;
    }
}

static void Set_PutValue(SetField& f, const std::wstring& value) {
    switch (f.kind) {
        case SetField::Choice: {
            int index = -1;
            for (size_t i = 0; i < f.options.size(); i++) {
                if (value == f.options[i].first) index = (int)i;
            }
            for (size_t i = 0; index < 0 && i < f.options.size(); i++) {
                if (wcscmp(f.def, f.options[i].first) == 0) index = (int)i;
            }
            f.cur = f.options[std::max(index, 0)].first;
            break;
        }
        case SetField::Check:
            f.cur = value != L"0" && !value.empty() ? L"1" : L"0";
            break;
        default:
            f.cur = value;
    }
}

static void Set_LoadFields(SetWindow& w) {
    for (auto& f : w.fields) {
        bool isInt = f.kind == SetField::Number || f.kind == SetField::Check;
        Set_PutValue(f, isInt ? std::to_wstring(Wh_GetIntSetting(f.key)) : GetStringSetting(f.key));
        // The icon shows only when the old trayIcon setting and this one are both on.
        if (wcscmp(f.key, L"settingsTrayIcon") == 0 && Wh_GetIntSetting(L"trayIcon") == 0) Set_PutValue(f, L"0");
        f.value = Set_FieldValue(f);  // What the window shows, so an untouched field never saves.
    }
}

static int Set_ChangedCount(const SetWindow& w) {
    int n = 0;
    for (auto& f : w.fields)
        if (Set_FieldValue(f) != f.value) n++;
    return n;
}

static bool Set_ParseHex(const std::wstring& text, UINT32& rgb) {
    if (text.size() != 7 || text[0] != L'#') return false;
    UINT32 v = 0;
    for (size_t i = 1; i < 7; i++) {
        WCHAR c = text[i];
        int d = c >= L'0' && c <= L'9' ? c - L'0' : c >= L'a' && c <= L'f' ? c - L'a' + 10 : c >= L'A' && c <= L'F' ? c - L'A' + 10 : -1;
        if (d < 0) return false;
        v = v * 16 + (UINT32)d;
    }
    rgb = v;
    return true;
}

static std::wstring Set_HexFromRgb(UINT32 rgb) {
    WCHAR text[16];
    swprintf_s(text, L"#%06X", rgb & 0xFFFFFF);
    return text;
}

static const wchar_t* Set_ChoiceLabel(const SetField& f) {
    for (auto& o : f.options)
        if (f.cur == o.first) return o.second;
    return f.options.empty() ? L"" : f.options[0].second;
}

static bool Set_Anim(const SetWindow& w) {
    BOOL on = TRUE;
    SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &on, 0);
    return !w.render && g_set.animations && on;
}

static void Set_Invalidate(SetWindow& w) {
    if (w.hwnd && !w.render) InvalidateRect(w.hwnd, nullptr, FALSE);
}

static void Set_SetStatus(SetWindow& w, PCWSTR text, bool error = false) {
    w.status = text;
    w.statusError = error;
    Set_Invalidate(w);
}

// ---- Text measuring ---------------------------------------------------------

static float Set_TextH(IDWriteTextFormat* fmt, const std::wstring& text, float width) {
    SetCom<IDWriteTextLayout> l;
    if (!fmt || FAILED(g_setDw->CreateTextLayout(text.c_str(), (UINT32)text.size(), fmt, width, 10000, l.put())))
        return 18;
    DWRITE_TEXT_METRICS m{};
    l->GetMetrics(&m);
    return m.height;
}

static float Set_TextW(IDWriteTextFormat* fmt, const std::wstring& text) {
    SetCom<IDWriteTextLayout> l;
    if (!fmt || FAILED(g_setDw->CreateTextLayout(text.c_str(), (UINT32)text.size(), fmt, 10000, 100, l.put())))
        return 0;
    DWRITE_TEXT_METRICS m{};
    l->GetMetrics(&m);
    return m.widthIncludingTrailingWhitespace;
}

// ---- Layout -----------------------------------------------------------------

// The right-hand control's width, so the label column knows how much room it has.
static float Set_ControlW(const SetField& f) {
    switch (f.kind) {
        case SetField::Check: return 40;
        case SetField::Choice: return 200;
        case SetField::Number: return f.max - f.min <= 100 ? 150 + 12 + 64 : 96;
        case SetField::Text: return 280;
        case SetField::Hotkey: return 220;
        case SetField::Color: return 362;
    }
    return 100;
}

// The page scrolls under the floating footer, so the view is the full height; contentH carries
// a bottom margin (Set_FootClear) so the last row can rise above the footer.
static float Set_ViewH(const SetWindow& w) { return w.ch; }
static float Set_FootClear() { return kSetFootH + kSetFootGap + 18; }

static D2D1_RECT_F Set_RailDock(const SetWindow& w) {
    return {kSetDockGap, kSetDockGap, kSetDockGap + w.railCur, std::max(kSetDockGap + 120, w.ch - kSetDockGap)};
}
// Right edge of the sidebar dock: the page starts after it.
static float Set_RailSpace(const SetWindow& w) { return kSetDockGap + w.railCur; }
// 0 collapsed to the icon rail, 1 fully open.
static float Set_RailOpen(const SetWindow& w) {
    return std::clamp((w.railCur - kSetRailMini) / std::max(1.0f, w.railW - kSetRailMini), 0.0f, 1.0f);
}
static D2D1_RECT_F Set_RailToggleRect(const SetWindow& w) {
    D2D1_RECT_F d = Set_RailDock(w);
    return {d.left + 12, d.top + 14, d.left + 48, d.top + 50};
}

// Everything a field's control is made of, in window DIPs for a given row.
struct SetParts {
    D2D1_RECT_F box{}, track{}, clear{}, chip[kSetChipCount]{};
    bool slider = false;
};

static SetParts Set_Parts(const SetField& f, const D2D1_RECT_F& row) {
    SetParts p;
    float r = row.right - kSetRowPad, mid = (row.top + row.bottom) / 2, h = kSetBoxH / 2;
    switch (f.kind) {
        case SetField::Check:
            p.box = {r - 40, mid - 11, r, mid + 11};
            break;
        case SetField::Choice:
            p.box = {r - 200, mid - h, r, mid + h};
            break;
        case SetField::Number:
            if (f.max - f.min <= 100) {
                p.slider = true;
                p.box = {r - 64, mid - h, r, mid + h};
                p.track = {p.box.left - 12 - 150, mid - 2, p.box.left - 12, mid + 2};
            } else {
                p.box = {r - 96, mid - h, r, mid + h};
            }
            break;
        case SetField::Text:
            p.box = {r - 280, mid - h, r, mid + h};
            break;
        case SetField::Hotkey:
            p.box = {r - 220, mid - h, r, mid + h};
            p.clear = {p.box.right - 30, p.box.top, p.box.right, p.box.bottom};
            break;
        case SetField::Color: {
            p.box = {r - 96, mid - h, r, mid + h};
            float x = p.box.left - 12 - (kSetChipCount * 26 - 6);
            for (int i = 0; i < kSetChipCount; i++) p.chip[i] = {x + i * 26, mid - 10, x + i * 26 + 20, mid + 10};
            break;
        }
    }
    return p;
}

static bool Set_In(const D2D1_RECT_F& r, float x, float y) { return x >= r.left && x < r.right && y >= r.top && y < r.bottom; }

static D2D1_RECT_F Set_RowRect(const SetWindow& w, const SetItem& it) {
    return {w.contentX, it.y, w.contentX + w.contentW, it.y + it.h};  // Content y (not scrolled).
}

// Lays out the current page's items for the current width.
static void Set_BuildPage(SetWindow& w) {
    w.items.clear();
    const float space = Set_RailSpace(w), avail = w.cw - space;
    w.contentW = std::clamp(avail - 2 * kSetPadX, 420.0f, kSetMaxW);
    w.contentX = space + std::max(kSetPadX, (avail - w.contentW) / 2);
    float introH = Set_TextH(w.fIntro.get(), kSetPages[w.page].intro, w.contentW);
    float y = 36 + 36 + 4 + introH + 24;
    if (w.page == 0) {
        std::wstring status = Set_KeyStatusText();
        if (!status.empty()) {
            SetItem it;
            it.type = SetItem::Banner;
            it.text = status;
            it.y = y;
            it.h = Set_TextH(w.fHint.get(), status, w.contentW - 32) + 28;
            y += it.h + kSetRowGap + 8;
            w.items.push_back(it);
        }
    }
    PCWSTR lastGroup = nullptr;
    for (size_t k = 0; k < w.fields.size(); k++) {
        const SetField& f = w.fields[k];
        if (f.page != w.page) continue;
        if (!lastGroup || wcscmp(lastGroup, f.group) != 0) {
            SetItem g;
            g.type = SetItem::Group;
            g.text = f.group;
            y += lastGroup ? 14 : 0;
            g.y = y;
            g.h = 22;
            y += g.h + 6;
            w.items.push_back(g);
            lastGroup = f.group;
        }
        SetItem it;
        it.type = SetItem::Row;
        it.field = (int)k;
        float textW = w.contentW - 2 * kSetRowPad - Set_ControlW(f) - 24;
        float lh = Set_TextH(w.fLabel.get(), f.label, textW);
        float dh = f.desc ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
        it.y = y;
        it.h = std::max(kSetRowMin, 28 + lh + dh);
        y += it.h + kSetRowGap;
        w.items.push_back(it);
    }
    if (w.page == kSetAboutPage) {
        auto add = [&](SetItem::Type t, float h, PCWSTR text, PCWSTR sub, PCWSTR url) {
            SetItem it;
            it.type = t;
            it.y = y;
            it.h = h;
            it.text = text;
            it.sub = sub;
            it.url = url;
            y += h + kSetRowGap;
            w.items.push_back(it);
        };
        auto group = [&](PCWSTR text) {
            SetItem g;
            g.type = SetItem::Group;
            g.text = text;
            g.y = y + 14;
            g.h = 22;
            y = g.y + g.h + 6;
            w.items.push_back(g);
        };
        add(SetItem::About, 146, L"", L"", L"");
        add(SetItem::Support, 84, L"Like it? Help the mod keep going.",
            L"Free and open source. A tip on Ko-fi keeps it moving.", kSetKofiUrl);
        group(L"Author");
        add(SetItem::Link, 56, L"DavidHiFi on GitHub", L"github.com/DavidHiFi", kSetAuthorUrl);
        add(SetItem::Link, 56, L"Ko-fi", L"ko-fi.com/DavidHiFi", kSetKofiUrl);
        group(L"Credits");
        add(SetItem::Link, 56, L"Based on Ditto", L"By Scott Brogden and the Ditto contributors", kSetDittoUrl);
        group(L"Project");
        add(SetItem::Link, 56, L"Project page on GitHub", L"github.com/DavidHiFi/davids-windhawk-mods", kSetRepoUrl);
        add(SetItem::Link, 56, L"Report a problem", L"Opens a new issue on GitHub, with the mod's name filled in", kSetBugUrl);
    }
    w.contentH = y + Set_FootClear();
    w.scrollTarget = std::clamp(w.scrollTarget, 0.0f, std::max(0.0f, w.contentH - Set_ViewH(w)));
    w.scrollY = std::clamp(w.scrollY, 0.0f, std::max(0.0f, w.contentH - Set_ViewH(w)));
}

static const SetItem* Set_ItemOfField(const SetWindow& w, int field) {
    for (auto& it : w.items)
        if (it.type == SetItem::Row && it.field == field) return &it;
    return nullptr;
}

// The footer's status line: an explicit message, else the count of unsaved changes.
static std::wstring Set_FooterStatus(const SetWindow& w, UINT32* color) {
    std::wstring status = w.status;
    if (color) *color = w.statusError ? mocha::red : (status == L"Saved" ? mocha::green : mocha::subtext0);
    int changed = Set_ChangedCount(w);
    if (status.empty() && changed)
        status = changed == 1 ? L"1 change not saved" : std::to_wstring(changed) + L" changes not saved";
    return status;
}

constexpr float kSetFootW[3] = {172, 96, 100};  // Reset to suggested, Cancel, Save.

static float Set_FooterButtonsW() { return kSetFootW[0] + kSetFootW[1] + kSetFootW[2] + 2 * 8; }

// Width the status text gets inside the footer dock (0 when there is none).
static float Set_FooterStatusW(const SetWindow& w) {
    std::wstring s = Set_FooterStatus(w, nullptr);
    if (s.empty()) return 0;
    float room = w.contentW - Set_FooterButtonsW() - 2 * kSetFootPad - 30;
    return std::max(0.0f, std::min(Set_TextW(w.fStatusLine.get(), s) + 2, room));
}

// The pill that holds the status and the three buttons, sized to fit them, right-aligned to the page.
static D2D1_RECT_F Set_FooterDock(const SetWindow& w) {
    float sw = Set_FooterStatusW(w);
    float width = Set_FooterButtonsW() + 2 * kSetFootPad + (sw > 0 ? sw + 30 : 0);
    float right = w.contentX + w.contentW, bottom = w.ch - kSetFootGap;
    return {right - width, bottom - kSetFootH, right, bottom};
}

static D2D1_RECT_F Set_FooterButton(const SetWindow& w, int which) {  // 0 reset, 1 cancel, 2 save
    D2D1_RECT_F d = Set_FooterDock(w);
    float x = d.right - kSetFootPad, top = d.top + kSetFootPad;
    D2D1_RECT_F out{};
    for (int i = 2; i >= 0; i--) {
        out = {x - kSetFootW[i], top, x, top + kSetFootBtnH};
        if (i == which) return out;
        x -= kSetFootW[i] + 8;
    }
    return out;
}

static D2D1_RECT_F Set_RailRect(const SetWindow& w, int page) {
    D2D1_RECT_F d = Set_RailDock(w);
    float y = d.top + kSetRailTop + kSetRailPitch * page + (page == kSetAboutPage ? kSetAboutGap : 0);
    return {d.left + 8, y, d.right - 8, y + kSetRailItem};
}

static D2D1_RECT_F Set_SupportButton(const SetWindow& w, const SetItem& it) {
    D2D1_RECT_F r = Set_RowRect(w, it);
    return {r.right - kSetRowPad - 148, (r.top + r.bottom) / 2 - 18, r.right - kSetRowPad, (r.top + r.bottom) / 2 + 18};
}

static D2D1_RECT_F Set_ScrollThumb(const SetWindow& w) {
    float view = Set_ViewH(w), range = w.contentH - view;
    if (range <= 0) return {};
    float th = std::max(36.0f, view * view / w.contentH);
    float top = (w.scrollY / range) * (view - th - 8) + 4;
    return {w.cw - 18, top + 4, w.cw - 12, top + th - 4};
}

// ---- Painting ---------------------------------------------------------------

static D2D1_COLOR_F Set_A1(float a) { return D2DColorRef(RGB(137,180,250), a); }
static D2D1_COLOR_F Set_A2(float a) { return D2DColorRef(RGB(203,166,247), a); }

static float Set_Ease(float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    return 1 - (1 - t) * (1 - t) * (1 - t);
}

struct SetPaint {
    SetWindow& w;
    ID2D1RenderTarget* rt;
    SetCom<ID2D1SolidColorBrush> sb;
    float fade = 1;
    SetPaint(SetWindow& win, ID2D1RenderTarget* target) : w(win), rt(target) {
        rt->CreateSolidColorBrush(D2DColor(0), sb.put());
    }
    ID2D1SolidColorBrush* B(UINT32 rgb, float a = 1) {
        sb->SetColor(D2DColor(rgb, a * fade));
        return sb.get();
    }
    // Blue to mauve, left to right across r.
    SetCom<ID2D1LinearGradientBrush> G(const D2D1_RECT_F& r, float a = 1) {
        SetCom<ID2D1LinearGradientBrush> out;
        D2D1_GRADIENT_STOP stops[2] = {{0, Set_A1(a * fade)}, {1, Set_A2(a * fade)}};
        SetCom<ID2D1GradientStopCollection> coll;
        if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, coll.put())))
            rt->CreateLinearGradientBrush(
                D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, (r.top + r.bottom) / 2),
                                                    D2D1::Point2F(std::max(r.right, r.left + 1), (r.top + r.bottom) / 2)),
                coll.get(), out.put());
        return out;
    }
    void Fill(const D2D1_RECT_F& r, UINT32 c, float a = 1) { rt->FillRectangle(r, B(c, a)); }
    void Round(const D2D1_RECT_F& r, float rad, UINT32 c, float a = 1) {
        rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), B(c, a));
    }
    void Edge(const D2D1_RECT_F& r, float rad, UINT32 c, float a, float width = 1) {
        if (a <= 0.003f) return;
        float h = width / 2;
        rt->DrawRoundedRectangle(D2D1::RoundedRect({r.left + h, r.top + h, r.right - h, r.bottom - h}, rad - h, rad - h), B(c, a), width);
    }
    void GradFill(const D2D1_RECT_F& r, float rad, float a) {
        if (a <= 0.003f) return;
        if (auto g = G(r, a)) rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), g.get());
    }
    void GradRing(const D2D1_RECT_F& r, float rad, float a, float width = 1.5f) {
        if (a <= 0.003f) return;
        D2D1_RECT_F in{r.left + width / 2, r.top + width / 2, r.right - width / 2, r.bottom - width / 2};
        if (auto g = G(r, a)) rt->DrawRoundedRectangle(D2D1::RoundedRect(in, rad, rad), g.get(), width);
    }
    void Text(IDWriteTextFormat* f, const std::wstring& s, const D2D1_RECT_F& r, UINT32 c, float a = 1) {
        if (!f || s.empty()) return;
        rt->DrawText(s.c_str(), (UINT32)s.size(), f, r, B(c, a), D2D1_DRAW_TEXT_OPTIONS_CLIP);
    }
    void Glyph(IDWriteTextFormat* f, WCHAR g, const D2D1_RECT_F& r, UINT32 c, float a = 1) {
        Text(f, std::wstring(1, g), r, c, a);
    }
};

static float Set_GlowOf(const SetWindow& w, int id) {
    auto it = w.glow.find(id);
    return it == w.glow.end() ? 0 : it->second;
}

// Ids that count as "pointer is here": the row (or rail item, button, link) and the control inside it.
static void Set_HoverIds(const SetHit& h, int ids[2]) {
    ids[0] = h.id;
    ids[1] = -1;
    if (h.kind == SetHit::Control || h.kind == SetHit::Slider || h.kind == SetHit::Clear || h.kind == SetHit::Chip)
        ids[1] = 6000 + h.a;
}

static bool Set_Valid(const SetWindow& w, int k) { return k >= 0 && k < (int)w.fields.size(); }

// Value boxes: a dark fill between mantle and surface0 (crust read as black), a resting
// overlay0 edge, and the blue to mauve ring on hover or while open.
constexpr UINT32 kSetBoxFill = 0x232434;
static void Set_DrawBox(SetPaint& p, SetWindow& w, int k, const D2D1_RECT_F& box, bool active) {
    p.Round(box, 8, kSetBoxFill);
    float g = std::max(Set_GlowOf(w, 6000 + k), active ? 1.0f : 0.0f);
    p.Edge(box, 8, mocha::overlay0, 0.7f * (1 - g), 1.25f);
    p.GradRing(box, 8, g, 1.75f);
}

static void Set_DrawRow(SetPaint& p, SetWindow& w, const SetItem& it) {
    const SetField& f = w.fields[it.field];
    int k = it.field;
    D2D1_RECT_F row = Set_RowRect(w, it);
    p.Round(row, 10, mocha::base);
    p.Round(row, 10, mocha::surface0, 0.32f);
    float hov = Set_GlowOf(w, 1000 + k);
    p.Edge(row, 10, mocha::surface2, 0.55f * (1 - hov));
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    if (w.kbd && w.focus == k) p.GradRing(row, 10, 1.0f, 2.0f);

    float textW = w.contentW - 2 * kSetRowPad - Set_ControlW(f) - 24;
    float lh = Set_TextH(w.fLabel.get(), f.label, textW);
    float dh = f.desc ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
    float top = row.top + (it.h - lh - dh) / 2;
    p.Text(w.fLabel.get(), f.label, {row.left + kSetRowPad, top, row.left + kSetRowPad + textW, top + lh + 2}, mocha::text);
    if (f.desc)
        p.Text(w.fHint.get(), f.desc, {row.left + kSetRowPad, top + lh + 3, row.left + kSetRowPad + textW, top + lh + dh + 3},
               mocha::subtext0);

    SetParts pt = Set_Parts(f, row);
    const D2D1_RECT_F& b = pt.box;
    switch (f.kind) {
        case SetField::Check: {
            bool on = f.cur == L"1";
            float kn = w.knob.count(k) ? w.knob.at(k) : (on ? 1.0f : 0.0f);
            D2D1_RECT_F tr = pt.box;
            p.Round(tr, 11, mocha::surface1);
            p.GradFill(tr, 11, kn);
            float cx = tr.left + 11 + kn * 18, cy = (tr.top + tr.bottom) / 2;
            p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 8, 8), p.B(on ? mocha::crust : mocha::text));
            break;
        }
        case SetField::Choice: {
            Set_DrawBox(p, w, k, b, w.openSel == k);
            p.Text(w.fValue.get(), Set_ChoiceLabel(f), {b.left + 12, b.top, b.right - 30, b.bottom}, mocha::text);
            p.Glyph(w.fIconS.get(), 0xE70D, {b.right - 30, b.top, b.right - 6, b.bottom}, mocha::subtext0);
            break;
        }
        case SetField::Number: {
            bool ed = w.editing == k;
            Set_DrawBox(p, w, k, b, ed);
            if (!ed) p.Text(w.fValueC.get(), Set_FieldValue(f), b, mocha::text);
            if (pt.slider) {
                float v = (float)(_wtoi(Set_FieldValue(f).c_str()) - f.min) / (float)std::max(1, f.max - f.min);
                D2D1_RECT_F tr = pt.track;
                p.Round(tr, 2, mocha::surface1);
                D2D1_RECT_F fillR{tr.left, tr.top, tr.left + (tr.right - tr.left) * v, tr.bottom};
                p.GradFill(fillR, 2, 1);
                float cx = tr.left + (tr.right - tr.left) * v, cy = (tr.top + tr.bottom) / 2;
                float kg = std::max(Set_GlowOf(w, 6000 + k), w.dragSlider == k ? 1.0f : 0.0f);
                p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 8 + kg, 8 + kg), p.B(mocha::text));
                p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 5, 5), p.B(mocha::crust));
            }
            break;
        }
        case SetField::Text: {
            bool ed = w.editing == k;
            Set_DrawBox(p, w, k, b, ed);
            if (!ed) p.Text(w.fValue.get(), f.cur, {b.left + 12, b.top, b.right - 10, b.bottom}, mocha::text);
            break;
        }
        case SetField::Hotkey: {
            bool rec = w.recording == k;
            Set_DrawBox(p, w, k, b, rec);
            if (rec) {
                p.Text(w.fValue.get(), L"Press keys...", {b.left + 12, b.top, b.right - 10, b.bottom}, mocha::blue);
            } else if (f.cur.empty()) {
                p.Text(w.fValue.get(), L"Not set", {b.left + 12, b.top, b.right - 10, b.bottom}, mocha::overlay0);
            } else {
                float tw = std::min(Set_TextW(w.fValue.get(), f.cur) + 16, b.right - b.left - 40);
                D2D1_RECT_F cap{b.left + 6, (b.top + b.bottom) / 2 - 12, b.left + 6 + tw, (b.top + b.bottom) / 2 + 12};
                p.Round(cap, 6, mocha::surface0);
                p.Text(w.fValueC.get(), f.cur, cap, mocha::text);
                float cg = Set_GlowOf(w, 7000 + k);
                p.Glyph(w.fIconS.get(), 0xE711, pt.clear, cg > 0.5f ? mocha::red : mocha::overlay1);
            }
            break;
        }
        case SetField::Color: {
            bool ed = w.editing == k;
            Set_DrawBox(p, w, k, b, ed);
            UINT32 rgb = 0;
            bool okColor = Set_ParseHex(f.cur, rgb);
            if (okColor) {
                p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(b.left + 17, (b.top + b.bottom) / 2), 6, 6), p.B(rgb));
            }
            if (!ed) p.Text(w.fValue.get(), f.cur, {b.left + 30, b.top, b.right - 6, b.bottom}, okColor ? mocha::text : mocha::red);
            for (int i = 0; i < kSetChipCount; i++) {
                const D2D1_RECT_F& c = pt.chip[i];
                bool sel = okColor && (rgb & 0xFFFFFF) == kSetChips[i];
                p.Round(c, 6, kSetChips[i]);
                if (sel) {
                    D2D1_RECT_F ring{c.left - 3, c.top - 3, c.right + 3, c.bottom + 3};
                    p.GradRing(ring, 8, 1, 2);
                }
            }
            break;
        }
    }
}

static void Set_DrawGroup(SetPaint& p, SetWindow& w, const SetItem& it) {
    std::wstring up = it.text;
    CharUpperBuffW(up.data(), (DWORD)up.size());
    p.Text(w.fSection.get(), up, {w.contentX + 4, it.y, w.contentX + w.contentW, it.y + it.h}, mocha::overlay2);
}

// The resting card every row uses: base, a light lift and a soft gray edge that hands over to
// the hover ring.
static void Set_DrawCard(SetPaint& p, const D2D1_RECT_F& row, float hov) {
    p.Round(row, 10, mocha::base);
    p.Round(row, 10, mocha::surface0, 0.32f);
    p.Edge(row, 10, mocha::surface2, 0.55f * (1 - hov));
}

static void Set_DrawLinkRow(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3000 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 9, row.right - 50, row.top + 30}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 30, row.right - 50, row.bottom - 4}, mocha::subtext0);
    p.Glyph(w.fIcon.get(), 0xE8A7, {row.right - 46, row.top, row.right - 12, row.bottom}, mocha::subtext1);
}

static void Set_DrawSupport(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float card = std::max(Set_GlowOf(w, 3700 + idx), Set_GlowOf(w, 3500 + idx));
    Set_DrawCard(p, row, card);
    p.GradFill(row, 10, 0.13f * card);
    p.GradRing(row, 10, card, 1.5f);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 14, row.right - 180, row.top + 36}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 38, row.right - 180, row.bottom - 6}, mocha::subtext0);
    D2D1_RECT_F b = Set_SupportButton(w, it);
    float hov = Set_GlowOf(w, 3500 + idx);
    p.GradFill(b, 8, 0.85f + 0.15f * hov);
    p.GradRing(b, 8, hov, 2);
    p.Text(w.fButton.get(), L"Open Ko-fi", b, mocha::crust);
}

static void Set_DrawAbout(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3800 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    D2D1_RECT_F mark{row.left + 20, row.top + 20, row.left + 92, row.top + 92};
    p.GradFill(mark, 18, 1);
    p.Glyph(w.fIconL.get(), 0xE77F, mark, mocha::crust);
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Clipboard Manager", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  GPL-3.0 license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"GPL-3.0 license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Keeps what you copy, so you can search it and paste it again.",
           {x, row.top + 72, row.right - 16, row.top + 92}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, based on Ditto by Scott Brogden and the Ditto contributors.",
           {x, row.top + 96, row.right - 16, row.bottom - 6}, mocha::overlay2);
}

static void Set_DrawBanner(SetPaint& p, SetWindow& w, const SetItem& it) {
    D2D1_RECT_F r = Set_RowRect(w, it);
    p.Round(r, 10, mocha::peach, 0.14f);
    p.Text(w.fHint.get(), it.text, {r.left + 16, r.top + 14, r.right - 16, r.bottom - 8}, mocha::peach);
}

// A floating dock: soft shadow, mantle fill, a quiet 1px edge at rest and the blue to mauve
// edge as the pointer comes over it.
static void Set_DrawDock(SetPaint& p, SetWindow& w, const D2D1_RECT_F& d, float rad, float fill, float glow) {
    p.Round({d.left, d.top + 3, d.right, d.bottom + 5}, rad + 2, mocha::crust, w.glass ? 0.28f : 0.5f);
    p.Round(d, rad, mocha::mantle, fill);  // Hover lights only the edge: a wash showed as a blue blob down the left.
    D2D1_RECT_F in{d.left + 0.5f, d.top + 0.5f, d.right - 0.5f, d.bottom - 0.5f};
    p.rt->DrawRoundedRectangle(D2D1::RoundedRect(in, rad, rad), p.B(mocha::surface1, 0.75f * (1 - glow)), 1);
    p.GradRing(d, rad, glow, 1.5f);
}

// Panel-left mark, as in T3's sidebar button: a window with its left pane shaded while open.
static void Set_DrawPanelIcon(SetPaint& p, const D2D1_RECT_F& r, float open, UINT32 c) {
    float cx = (r.left + r.right) / 2, cy = (r.top + r.bottom) / 2;
    D2D1_RECT_F box{cx - 9, cy - 7.5f, cx + 9, cy + 7.5f};
    p.Round({box.left + 1, box.top + 1, box.left + 6.5f, box.bottom - 1}, 1.5f, c, 0.25f + 0.35f * open);
    p.rt->DrawRoundedRectangle(D2D1::RoundedRect(box, 3, 3), p.B(c), 1.5f);
    p.rt->DrawLine({box.left + 6.5f, box.top + 0.75f}, {box.left + 6.5f, box.bottom - 0.75f}, p.B(c), 1.5f);
}

static void Set_DrawMark(SetPaint& p, IDWriteTextFormat* glyph, const D2D1_RECT_F& r, float a);
static void Set_DrawRail(SetPaint& p, SetWindow& w) {
    D2D1_RECT_F d = Set_RailDock(w);
    const float open = Set_RailOpen(w), textA = std::clamp((open - 0.45f) / 0.55f, 0.0f, 1.0f);
    // Over the resize edge or while dragging, the dock's own rounded border brightens and
    // thickens, so the handle follows the corners instead of floating as a separate line.
    float edge = std::max(Set_GlowOf(w, 41), w.dragRail ? 1.0f : 0.0f);
    Set_DrawDock(p, w, d, 14, w.glass ? 0.58f : 1.0f, std::max(w.railGlow * 0.85f, edge));
    if (edge > 0.003f) p.GradRing(d, 13, edge, 2.25f);

    D2D1_RECT_F tb = Set_RailToggleRect(w);
    float th = Set_GlowOf(w, 42);
    p.Round(tb, 9, mocha::surface0, 0.45f + 0.25f * th);
    p.GradFill(tb, 9, 0.16f * th);
    p.GradRing(tb, 9, 0.9f * th, 1.25f);
    if (w.kbd && w.focus == -20) p.GradRing(tb, 9, 1, 2);
    Set_DrawPanelIcon(p, tb, open, th > 0.5f ? mocha::text : mocha::subtext1);

    p.rt->PushAxisAlignedClip(D2D1::RectF(d.left, d.top, d.right - 6, d.bottom), D2D1_ANTIALIAS_MODE_ALIASED);
    if (textA > 0.003f) {
        float my = (tb.top + tb.bottom) / 2;
        Set_DrawMark(p, w.fIcon.get(), {d.left + 56, my - 13, d.left + 82, my + 13}, textA);
    }
    p.Text(w.fRailName.get(), L"Seamless", {d.left + 90, d.top + 9, d.left + w.railW - 10, d.top + 33}, mocha::text, textA);
    p.Text(w.fRailName.get(), L"Clipboard", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
    for (int i = 0; i < kSetPageCount; i++) {
        D2D1_RECT_F r = Set_RailRect(w, i);
        if (i == kSetAboutPage) {
            float ly = std::round(r.top - (kSetAboutGap + kSetRailPitch - kSetRailItem) / 2);
            p.Fill({r.left + 6, ly, r.right - 6, ly + 1}, mocha::surface1, 0.7f);
        }
        float hov = Set_GlowOf(w, 100 + i);
        bool act = i == w.page;
        if (act) {
            p.GradFill(r, 8, 0.22f);
            p.GradRing(r, 8, 0.5f, 1);
            D2D1_RECT_F bar{r.left, r.top + 8, r.left + 3, r.bottom - 8};
            p.GradFill({bar.left, bar.top, bar.left + 3, bar.bottom}, 1.5f, 1);
        } else {
            p.Round(r, 8, mocha::surface0, 0.28f);
            p.Edge(r, 8, mocha::surface2, 0.5f * (1 - hov));
            p.GradFill(r, 8, 0.10f * hov);
            p.GradRing(r, 8, 0.8f * hov, 1.25f);
        }
        if (w.kbd && w.focus == -10 - i) p.GradRing(r, 8, 1, 2);
        UINT32 c = act ? mocha::text : mocha::subtext1;
        // The glyph sits in a fixed 44-wide slot, so it stays centered in the collapsed rail.
        p.Glyph(w.fIcon.get(), kSetPages[i].glyph, {r.left, r.top, r.left + 44, r.bottom}, act ? mocha::blue : mocha::subtext0);
        p.Text(w.fLabel.get(), kSetPages[i].name, {r.left + 50, r.top + 8, r.left + w.railW - 24, r.bottom}, c, textA);
    }
#ifdef WH_MOD_VERSION
    p.Text(w.fSmall.get(), std::wstring(L"Version ") + WH_MOD_VERSION,
           {d.left + 18, d.bottom - 34, d.left + w.railW - 12, d.bottom - 12}, mocha::overlay1, textA);
#endif
    p.rt->PopAxisAlignedClip();
}

static void Set_DrawFooter(SetPaint& p, SetWindow& w) {
    D2D1_RECT_F d = Set_FooterDock(w);
    const float rad = kSetFootH / 2, brad = kSetFootBtnH / 2;
    p.Round(d, rad, mocha::mantle, w.render ? 1.0f : 0.85f);
    const D2D1_RECT_F edge{d.left + 2, d.top + 2, d.right - 2, d.bottom - 2};
    p.rt->DrawRoundedRectangle(D2D1::RoundedRect(edge, rad - 2, rad - 2),
                              p.B(mocha::overlay0, 0.9f * (1 - w.footGlow)), 2.75f);
    p.GradRing(d, rad - 1.5f, w.footGlow, 3.0f);
    UINT32 sc;
    std::wstring status = Set_FooterStatus(w, &sc);
    float sw = Set_FooterStatusW(w);
    if (sw > 0) p.Text(w.fStatusLine.get(), status, {d.left + 18, d.top, d.left + 18 + sw, d.bottom}, sc);
    static const PCWSTR names[3] = {L"Reset to suggested", L"Cancel", L"Save"};
    for (int i = 0; i < 3; i++) {
        D2D1_RECT_F b = Set_FooterButton(w, i);
        float hov = Set_GlowOf(w, 10 + i);
        p.Round(b, brad, mocha::base, 0.98f);
        p.Edge(b, brad, mocha::overlay0, 0.78f * (1 - hov), 1.75f);
        p.GradRing(b, brad - 1, hov, 2.25f);
        p.Text(w.fButton.get(), names[i], b, mocha::text, w.saving ? 0.5f : 1.0f);
        if (w.kbd && w.focus == -1 - i) p.GradRing(b, brad, 1, 2);
    }
}


static void Set_DrawPopup(SetPaint& p, SetWindow& w) {
    if (w.openSel < 0) return;
    const SetField& f = w.fields[w.openSel];
    const D2D1_RECT_F& r = w.dropRect;
    D2D1_RECT_F shadow{r.left - 1, r.top + 3, r.right + 1, r.bottom + 5};
    p.Round(shadow, 12, mocha::crust, 0.6f);
    p.Round(r, 10, mocha::mantle);
    p.GradRing(r, 10, 0.9f);
    for (size_t i = 0; i < f.options.size(); i++) {
        D2D1_RECT_F it{r.left + 4, r.top + 4 + i * kSetDropItem, r.right - 4, r.top + 4 + (i + 1) * kSetDropItem};
        bool sel = f.cur == f.options[i].first;
        if ((int)i == w.dropHover) {
            p.GradFill(it, 6, 0.28f);
            p.GradRing(it, 6, 0.6f, 1);
        }
        p.Text(w.fValue.get(), f.options[i].second, {it.left + 10, it.top, it.right - 28, it.bottom}, sel ? mocha::blue : mocha::text);
        if (sel) p.Glyph(w.fIconS.get(), 0xE73E, {it.right - 28, it.top, it.right - 6, it.bottom}, mocha::blue);
    }
}

// Title bar buttons, in title bar DIPs: 0 minimize, 1 maximize or restore, 2 close.
static D2D1_RECT_F Set_CapButton(const SetWindow& w, int i) {
    float right = w.cw - (2 - i) * kSetCapBtnW;
    return {right - kSetCapBtnW, 0, right, kSetCapH};
}

// y is in content DIPs, so the title bar is y < 0.
static int Set_CapButtonAt(const SetWindow& w, float x, float y) {
    if (w.nativeTitle || w.nativeButtons) return -1;
    for (int i = 0; i < 3; i++)
        if (Set_In(Set_CapButton(w, i), x, y + kSetCapH)) return i;
    return -1;
}

// Icon and title are centered on the whole width, laid out from the current size on every paint,
// so a move or snap can never leave them off center.
static D2D1_RECT_F Set_CapTitleRect(const SetWindow& w) {
    float tw = std::min(Set_TextW(w.fCap.get(), kSetTitle) + 2, std::max(0.0f, w.cw - 4 * kSetCapBtnW - 40));
    float x = std::round((w.cw - (16 + 8 + tw)) / 2);
    return {x, 0, x + 16 + 8 + tw, kSetCapH};
}

static void Set_DrawMark(SetPaint& p, IDWriteTextFormat* glyph, const D2D1_RECT_F& r, float a) {
    float s = r.right - r.left;
    SetCom<ID2D1LinearGradientBrush> g;
    D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::blue, a * p.fade)}, {1, D2DColor(mocha::mauve, a * p.fade)}};
    SetCom<ID2D1GradientStopCollection> coll;
    if (SUCCEEDED(p.rt->CreateGradientStopCollection(stops, 2, coll.put())) &&
        SUCCEEDED(p.rt->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, r.top), D2D1::Point2F(r.right, r.bottom)),
            coll.get(), g.put())))
        p.rt->FillRoundedRectangle(D2D1::RoundedRect(r, s * 0.24f, s * 0.24f), g.get());
    p.Glyph(glyph, 0xE77F, r, mocha::crust);
}

static void Set_DrawCaption(SetPaint& p, SetWindow& w) {
    if (!w.glass) p.Fill({0, 0, w.cw, kSetCapH}, mocha::crust);  // Glass: the window tint already covers it.
    D2D1_RECT_F t = Set_CapTitleRect(w);
    float mid = kSetCapH / 2;
    Set_DrawMark(p, w.fCapGlyph.get(), {t.left, mid - 8, t.left + 16, mid + 8}, w.active ? 1.0f : 0.6f);
    p.Text(w.fCap.get(), kSetTitle, {t.left + 24, 0, t.right, kSetCapH}, w.active ? mocha::text : mocha::overlay1);
    if (w.nativeButtons) return;  // DWM draws them over this title bar.
    for (int i = 0; i < 3; i++) {
        D2D1_RECT_F b = Set_CapButton(w, i);
        float hov = Set_GlowOf(w, 20 + i);
        if (w.capDown == i + 1) hov = 1;
        if (i == 2) p.Fill(b, mocha::red, 0.92f * hov);
        else p.Fill(b, mocha::surface0, 0.85f * hov);
        UINT32 c = i == 2 && hov > 0.5f ? mocha::crust : (w.active ? mocha::text : mocha::overlay1);
        WCHAR glyph = i == 0 ? 0xE921 : i == 1 ? (w.hwnd && IsZoomed(w.hwnd) ? 0xE923 : 0xE922) : 0xE8BB;
        p.Glyph(w.fCapGlyph.get(), glyph, b, c);
    }
}

// Draws the whole window into rt (DIPs). The target's DPI does the scaling.
// The title bar is drawn first; everything else is in content DIPs, shifted down by kSetCapH.
static void Set_Draw(SetWindow& w, ID2D1RenderTarget* rt) {
    SetPaint p(w, rt);
    const auto base = D2D1::Matrix3x2F::Translation(0, kSetCapH);
    rt->BeginDraw();
    rt->SetTransform(D2D1::Matrix3x2F::Identity());
    if (w.glass) {
        // One tint over the whole window, title bar included, so the page and the title bar are
        // the same material. With the Windows title bar (drawn by DWM with no tint) the tint fades
        // in over the top of the page instead, so there is no step at the seam (T3 pass 24 method).
        rt->Clear(D2D1::ColorF(0, 0));
        const float total = w.ch + kSetCapH;
        if (w.nativeTitle) {
            SetCom<ID2D1LinearGradientBrush> fade;
            D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::crust, 0)}, {1, D2DColor(mocha::crust, kSetGlassTint)}};
            SetCom<ID2D1GradientStopCollection> coll;
            if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, coll.put())) &&
                SUCCEEDED(rt->CreateLinearGradientBrush(
                    D2D1::LinearGradientBrushProperties(D2D1::Point2F(0, 0), D2D1::Point2F(0, kSetNativeFade)), coll.get(),
                    fade.put())))
                rt->FillRectangle(D2D1::RectF(0, 0, w.cw, kSetNativeFade), fade.get());
            p.Fill({0, kSetNativeFade, w.cw, total}, mocha::crust, kSetGlassTint);
        } else {
            p.Fill({0, 0, w.cw, total}, mocha::crust, kSetGlassTint);
        }
    } else {
        rt->Clear(D2DColor(mocha::crust));
    }
    if (!w.nativeTitle) Set_DrawCaption(p, w);
    rt->SetTransform(base);
    float viewH = Set_ViewH(w);

    auto drawPage = [&](SetPaint& cp) {
        ID2D1RenderTarget* crt = cp.rt;
        crt->PushAxisAlignedClip(D2D1::RectF(Set_RailSpace(w) + 4, 0, w.cw, viewH), D2D1_ANTIALIAS_MODE_ALIASED);
        auto place = [&](int index, float& rise) {
            float t = w.pageT >= 1 ? 1.0f : Set_Ease(w.pageT * 1.7f - std::min(index, 9) * 0.07f);
            cp.fade = t;
            rise = (1 - t) * 10;
            crt->SetTransform(D2D1::Matrix3x2F::Translation(0, -w.scrollY + rise) * base);
        };
        float rise = 0;
        place(0, rise);
        cp.Text(w.fTitle.get(), kSetPages[w.page].name, {w.contentX, 36, w.contentX + w.contentW, 72}, mocha::text);
        place(1, rise);
        cp.Text(w.fIntro.get(), kSetPages[w.page].intro, {w.contentX, 76, w.contentX + w.contentW, 76 + 40}, mocha::subtext0);
        for (size_t i = 0; i < w.items.size(); i++) {
            const SetItem& it = w.items[i];
            if (it.y + it.h < w.scrollY - 20 || it.y > w.scrollY + viewH + 20) continue;
            place((int)i + 2, rise);
            switch (it.type) {
                case SetItem::Group: Set_DrawGroup(cp, w, it); break;
                case SetItem::Row: Set_DrawRow(cp, w, it); break;
                case SetItem::Banner: Set_DrawBanner(cp, w, it); break;
                case SetItem::About: Set_DrawAbout(cp, w, it, (int)i); break;
                case SetItem::Link: Set_DrawLinkRow(cp, w, it, (int)i); break;
                case SetItem::Support: Set_DrawSupport(cp, w, it, (int)i); break;
            }
        }
        cp.fade = 1;
        crt->SetTransform(base);
        crt->PopAxisAlignedClip();
    };

    // The footer dock floats over the page with a real blur of the rows under it, clipped to the
    // pill, all in this window. (An owned popup with its own backdrop showed square corners:
    // DWM paints an accent backdrop over the full window rectangle and ignores the region.)
    const D2D1_SIZE_F full = D2D1::SizeF(w.cw, w.ch + kSetCapH);
    bool blurred = false;
    if (!w.render) {
        if (w.layer && (w.layerSize.width != full.width || w.layerSize.height != full.height)) w.layer.reset();
        if (!w.layer && SUCCEEDED(rt->CreateCompatibleRenderTarget(full, w.layer.put()))) w.layerSize = full;
        SetCom<ID2D1Bitmap> page;
        SetCom<ID2D1DeviceContext> dc;
        SetCom<ID2D1Effect> blur;
        SetCom<ID2D1RoundedRectangleGeometry> pill;
        SetCom<ID2D1RectangleGeometry> all;
        SetCom<ID2D1PathGeometry> rest;
        D2D1_RECT_F d = Set_FooterDock(w);
        d.top += kSetCapH, d.bottom += kSetCapH;
        const float rad = kSetFootH / 2;
        if (w.layer && SUCCEEDED(rt->QueryInterface(__uuidof(ID2D1DeviceContext), (void**)dc.put())) &&
            SUCCEEDED(dc->CreateEffect(CLSID_D2D1GaussianBlur, blur.put())) &&
            SUCCEEDED(g_setD2d->CreateRoundedRectangleGeometry(D2D1::RoundedRect(d, rad, rad), pill.put())) &&
            SUCCEEDED(g_setD2d->CreateRectangleGeometry(D2D1::RectF(0, 0, full.width, full.height), all.put())) &&
            SUCCEEDED(g_setD2d->CreatePathGeometry(rest.put()))) {
            SetCom<ID2D1GeometrySink> sink;
            bool ok = SUCCEEDED(rest->Open(sink.put())) &&
                      SUCCEEDED(all->CombineWithGeometry(pill.get(), D2D1_COMBINE_MODE_EXCLUDE, nullptr, sink.get())) &&
                      SUCCEEDED(sink->Close());
            ID2D1BitmapRenderTarget* lt = w.layer.get();
            if (ok) {
                SetPaint lp(w, lt);
                lt->BeginDraw();
                lt->SetTransform(D2D1::Matrix3x2F::Identity());
                lt->Clear(D2D1::ColorF(0, 0));
                lt->SetTransform(base);
                drawPage(lp);
                ok = SUCCEEDED(lt->EndDraw()) && SUCCEEDED(lt->GetBitmap(page.put()));
            }
            if (!ok) w.layer.reset();
            if (ok) {
                rt->SetTransform(D2D1::Matrix3x2F::Identity());
                rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), rest.get()), nullptr);
                rt->DrawBitmap(page.get());
                rt->PopLayer();
                blur->SetInput(0, page.get());
                blur->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 9.0f);
                blur->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD);
                rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), pill.get()), nullptr);
                D2D1_RECT_F src{d.left - 1, d.top - 1, d.right + 1, d.bottom + 1};
                dc->DrawImage(blur.get(), D2D1::Point2F(src.left, src.top), src);
                rt->PopLayer();
                blurred = true;
            }
        }
    }
    if (!blurred) drawPage(p);
    rt->SetTransform(base);

    D2D1_RECT_F th = Set_ScrollThumb(w);
    if (th.bottom > th.top) p.Round(th, 3, w.dragScroll ? mocha::overlay1 : mocha::surface2, 0.9f);

    Set_DrawFooter(p, w);
    Set_DrawRail(p, w);
    Set_DrawPopup(p, w);
    rt->SetTransform(D2D1::Matrix3x2F::Identity());
    if (false) p.GradRing({0, 0, w.cw, w.ch + kSetCapH}, SystemCornerRadius(false), 1, 1);
    HRESULT hr = rt->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) w.rt.reset(), w.layer.reset();
}

// ---- Hit testing --------------------------------------------------------------

static SetHit Set_Hit(SetWindow& w, float x, float y) {
    SetHit h;
    if (y < 0) {
        int b = Set_CapButtonAt(w, x, y);
        if (b >= 0) {
            h.kind = SetHit::Caption;
            h.a = b;
            h.id = 20 + b;
        }
        return h;
    }
    if (w.openSel >= 0) {
        if (Set_In(w.dropRect, x, y)) {
            int i = (int)((y - w.dropRect.top - 4) / kSetDropItem);
            if (i >= 0 && i < (int)w.fields[w.openSel].options.size() && y >= w.dropRect.top + 4) {
                h.kind = SetHit::Drop;
                h.a = w.openSel;
                h.b = i;
            } else {
                h.kind = SetHit::Popup;
            }
        }
        return h;
    }
    D2D1_RECT_F dock = Set_RailDock(w);
    if (y >= dock.top + 14 && y < dock.bottom - 14 && fabsf(x - dock.right) <= kSetEdgeGrab) {
        h.kind = SetHit::RailEdge;
        h.id = 41;
        return h;
    }
    if (x < dock.right + kSetDockGap) {
        if (Set_In(Set_RailToggleRect(w), x, y)) {
            h.kind = SetHit::RailToggle;
            h.id = 42;
            return h;
        }
        for (int i = 0; i < kSetPageCount; i++) {
            if (Set_In(Set_RailRect(w, i), x, y)) {
                h.kind = SetHit::Rail;
                h.a = i;
                h.id = 100 + i;
                return h;
            }
        }
        return h;
    }
    D2D1_RECT_F foot = Set_FooterDock(w);
    if (Set_In(foot, x, y)) {
        for (int i = 0; i < 3; i++) {
            if (Set_In(Set_FooterButton(w, i), x, y)) {
                h.kind = SetHit::Footer;
                h.a = i;
                h.id = 10 + i;
                return h;
            }
        }
        return h;
    }
    D2D1_RECT_F th = Set_ScrollThumb(w);
    if (th.bottom > th.top && x >= w.cw - 16 && y >= th.top && y <= th.bottom) {
        h.kind = SetHit::Scroll;
        return h;
    }
    float cy = y + w.scrollY;
    for (size_t i = 0; i < w.items.size(); i++) {
        const SetItem& it = w.items[i];
        D2D1_RECT_F row = Set_RowRect(w, it);
        if (!Set_In(row, x, cy)) continue;
        if (it.type == SetItem::Link) {
            h.kind = SetHit::Link;
            h.a = (int)i;
            h.id = 3000 + (int)i;
        } else if (it.type == SetItem::Support) {
            h.id = 3700 + (int)i;  // The card lights up; only its button clicks.
            if (Set_In(Set_SupportButton(w, it), x, cy)) {
                h.kind = SetHit::Link;
                h.a = (int)i;
                h.id = 3500 + (int)i;
            }
        } else if (it.type == SetItem::About) {
            h.id = 3800 + (int)i;
        } else if (it.type == SetItem::Row) {
            const SetField& f = w.fields[it.field];
            SetParts pt = Set_Parts(f, row);
            h.a = it.field;
            h.id = 1000 + it.field;
            h.kind = f.kind == SetField::Check ? SetHit::Control : SetHit::Row;
            if (f.kind == SetField::Hotkey && !f.cur.empty() && w.recording != it.field && Set_In(pt.clear, x, cy)) {
                h.kind = SetHit::Clear;
            } else if (f.kind == SetField::Color) {
                for (int c = 0; c < kSetChipCount; c++) {
                    if (Set_In(pt.chip[c], x, cy)) {
                        h.kind = SetHit::Chip;
                        h.b = c;
                    }
                }
                if (h.kind != SetHit::Chip && Set_In(pt.box, x, cy)) h.kind = SetHit::Control;
            } else if (pt.slider &&
                       Set_In({pt.track.left - 8, pt.track.top - 10, pt.track.right + 8, pt.track.bottom + 10}, x, cy)) {
                h.kind = SetHit::Slider;
            } else if (Set_In(pt.box, x, cy)) {
                h.kind = SetHit::Control;
            }
        }
        return h;
    }
    return h;
}

static bool Set_Clickable(const SetHit& h) {
    return h.kind == SetHit::Rail || h.kind == SetHit::Footer || h.kind == SetHit::Control || h.kind == SetHit::Slider ||
           h.kind == SetHit::Clear || h.kind == SetHit::Chip || h.kind == SetHit::Drop || h.kind == SetHit::Link ||
           h.kind == SetHit::Scroll || h.kind == SetHit::RailToggle;
}

// Sidebar width from a drag: below the snap point it collapses to the icon rail.
static void Set_RailDragTo(SetWindow& w, float x) {
    float width = x - kSetDockGap;
    if (width < kSetRailSnap) {
        w.railCollapsed = true;
    } else {
        w.railCollapsed = false;
        w.railW = std::clamp(width, kSetRailMin, kSetRailMax);
        w.railCur = w.railW;
    }
    Set_BuildPage(w);
    Set_Invalidate(w);
}

static void Set_ToggleRail(SetWindow& w) {
    w.railCollapsed = !w.railCollapsed;
    if (!w.railCollapsed && w.railCur < kSetRailMini) w.railCur = kSetRailMini;
    Set_Invalidate(w);
}

// ---- Editing, recording, choosing -----------------------------------------------

static std::wstring Set_FormatHotkey(UINT mods, UINT vk) {
    std::wstring text = Hotkey_Format(mods, vk);
    if (!text.empty()) return text;
    // Fallback while the capture part is a stub.
    if (mods & MOD_CONTROL) text += L"Ctrl+";
    if (mods & MOD_ALT) text += L"Alt+";
    if (mods & MOD_SHIFT) text += L"Shift+";
    if (mods & MOD_WIN) text += L"Win+";
    WCHAR name[64] = {};
    LONG scan = (LONG)MapVirtualKeyW(vk, MAPVK_VK_TO_VSC) << 16;
    if (GetKeyNameTextW(scan, name, ARRAYSIZE(name)) > 0) {
        text += name;
    } else {
        text += std::to_wstring(vk);
    }
    return text;
}

static bool Set_IsModifier(UINT vk) {
    switch (vk) {
        case VK_SHIFT: case VK_LSHIFT: case VK_RSHIFT:
        case VK_CONTROL: case VK_LCONTROL: case VK_RCONTROL:
        case VK_MENU: case VK_LMENU: case VK_RMENU:
        case VK_LWIN: case VK_RWIN:
            return true;
    }
    return false;
}

static void Set_StopRecording(SetWindow& w) {
    if (w.recording < 0) return;
    w.recording = -1;
    if (w.status.rfind(L"Press the keys", 0) == 0) Set_SetStatus(w, L"");
    if (!w.render) Hotkeys_Register();
    Set_Invalidate(w);
}

static void Set_StartRecording(SetWindow& w, int k) {
    Set_StopRecording(w);
    w.recording = k;
    // Our own keys would fire instead of reaching the window while it listens.
    if (!w.render) {
        Hotkeys_Unregister();
        SetFocus(w.hwnd);
    }
    Set_SetStatus(w, L"Press the keys you want. Esc cancels, Backspace clears.");
}

static void Set_ClosePopup(SetWindow& w) {
    if (w.openSel < 0) return;
    w.openSel = -1;
    w.dropHover = -1;
    Set_Invalidate(w);
}

static void Set_OpenPopup(SetWindow& w, int k) {
    const SetItem* it = Set_ItemOfField(w, k);
    if (!it) return;
    const SetField& f = w.fields[k];
    SetParts pt = Set_Parts(f, Set_RowRect(w, *it));
    float boxTop = pt.box.top - w.scrollY, boxBottom = pt.box.bottom - w.scrollY;
    float h = (float)f.options.size() * kSetDropItem + 8;
    float top = boxBottom + 4;
    if (top + h > Set_ViewH(w) + 20 && boxTop - 4 - h > 0) top = boxTop - 4 - h;  // No room below: open upward.
    w.dropRect = {pt.box.left, top, pt.box.right, top + h};
    w.openSel = k;
    w.dropHover = -1;
    for (size_t i = 0; i < f.options.size(); i++)
        if (f.cur == f.options[i].first) w.dropHover = (int)i;
    Set_Invalidate(w);
}

static void Set_CommitEdit(SetWindow& w, bool apply) {
    if (w.editing < 0) return;
    int k = w.editing;
    w.editing = -1;  // Hiding the box ends its focus; this stops that from coming back here.
    SetField& f = w.fields[k];
    std::wstring text = w.edit ? Set_WindowText(w.edit) : L"";
    if (w.edit) ShowWindow(w.edit, SW_HIDE);
    if (apply) {
        switch (f.kind) {
            case SetField::Number:
                if (!text.empty()) f.cur = std::to_wstring(std::clamp(_wtoi(text.c_str()), f.min, f.max));
                break;
            case SetField::Color: {
                while (!text.empty() && text.back() == L' ') text.pop_back();
                while (!text.empty() && text.front() == L' ') text.erase(0, 1);
                if (!text.empty() && text[0] != L'#') text = L"#" + text;
                UINT32 rgb;
                if (Set_ParseHex(text, rgb)) {
                    f.cur = Set_HexFromRgb(rgb);
                    Set_SetStatus(w, L"");
                } else {
                    Set_SetStatus(w, L"Use a color like #89B4FA.", true);
                }
                break;
            }
            default:
                f.cur = text;
        }
    }
    if (!w.render && w.hwnd) SetFocus(w.hwnd);
    Set_Invalidate(w);
}

static void Set_PlaceEdit(SetWindow& w) {
    if (w.editing < 0 || !w.edit) return;
    const SetItem* it = Set_ItemOfField(w, w.editing);
    if (!it) return;
    SetParts pt = Set_Parts(w.fields[w.editing], Set_RowRect(w, *it));
    float left = pt.box.left + (w.fields[w.editing].kind == SetField::Color ? 30 : 10), right = pt.box.right - 8;
    float mid = (pt.box.top + pt.box.bottom) / 2 - w.scrollY + kSetCapH;
    float s = w.dpi / 96.0f;
    SetWindowPos(w.edit, HWND_TOP, (int)(left * s), (int)((mid - 10) * s), (int)((right - left) * s), (int)(20 * s),
                 SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

static LRESULT CALLBACK Set_EditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR) {
    SetWindow* w = g_setWin.get();
    if (w && w->edit == hwnd) {
        switch (msg) {
            case WM_KEYDOWN:
                if (wParam == VK_RETURN || wParam == VK_TAB) {
                    Set_CommitEdit(*w, true);
                    return 0;
                }
                if (wParam == VK_ESCAPE) {
                    Set_CommitEdit(*w, false);
                    return 0;
                }
                break;
            case WM_CHAR:
                if (wParam == VK_RETURN || wParam == VK_ESCAPE || wParam == VK_TAB) return 0;  // No beep.
                break;
            case WM_KILLFOCUS:
                if (w->editing >= 0) Set_CommitEdit(*w, true);
                break;
        }
    }
    return DefSubclassProc(hwnd, msg, wParam, lParam);
}

static void Set_BeginEdit(SetWindow& w, int k) {
    Set_CommitEdit(w, true);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    SetField& f = w.fields[k];
    if (w.edit) DestroyWindow(w.edit);
    if (w.editFont) DeleteObject(w.editFont);
    DWORD style = WS_CHILD | ES_AUTOHSCROLL | (f.kind == SetField::Number ? ES_NUMBER | ES_CENTER : 0);
    // Over the extended frame GDI text would come out see-through; a layered child keeps it solid.
    w.edit = CreateWindowExW(w.glass ? WS_EX_LAYERED : 0, L"EDIT", L"", style, 0, 0, 10, 10, w.hwnd, nullptr,
                             g_hInstance, nullptr);
    if (!w.edit) return;
    if (w.glass) SetLayeredWindowAttributes(w.edit, 0, 255, LWA_ALPHA);
    int base = std::clamp(g_set.fontWeight, 100, 900);
    w.editFont = CreateFontW(-MulDiv(13, w.dpi, 96), 0, 0, 0, base, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                             CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, w.family.c_str());
    SendMessageW(w.edit, WM_SETFONT, (WPARAM)w.editFont, TRUE);
    SendMessageW(w.edit, EM_SETLIMITTEXT, f.kind == SetField::Number ? 6 : f.kind == SetField::Color ? 7 : 260, 0);
    SetWindowTextW(w.edit, f.kind == SetField::Number ? Set_FieldValue(f).c_str() : f.cur.c_str());
    SetWindowSubclass(w.edit, Set_EditProc, 1, 0);
    w.editing = k;
    Set_PlaceEdit(w);
    if (!w.render) SetFocus(w.edit);
    SendMessageW(w.edit, EM_SETSEL, 0, -1);
    Set_Invalidate(w);
}

static void Set_Choose(SetWindow& w, int k, int option) {
    SetField& f = w.fields[k];
    if (option >= 0 && option < (int)f.options.size()) f.cur = f.options[option].first;
    Set_ClosePopup(w);
}

static void Set_SliderTo(SetWindow& w, int k, float x) {
    const SetItem* it = Set_ItemOfField(w, k);
    if (!it) return;
    SetField& f = w.fields[k];
    SetParts pt = Set_Parts(f, Set_RowRect(w, *it));
    float t = std::clamp((x - pt.track.left) / (pt.track.right - pt.track.left), 0.0f, 1.0f);
    f.cur = std::to_wstring(f.min + (int)(t * (f.max - f.min) + 0.5f));
    Set_Invalidate(w);
}

static void Set_Save(std::shared_ptr<SetWindow> keep);

static void Set_ResetToSuggested(SetWindow& w) {
    Set_CommitEdit(w, false);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    for (auto& f : w.fields) Set_PutValue(f, f.def);
    Set_SetStatus(w, L"Suggested values are filled in. Press Save to keep them.");
}

static void Set_BuildAndClamp(SetWindow& w) {
    Set_BuildPage(w);
    Set_PlaceEdit(w);
    Set_Invalidate(w);
}

static void Set_GoPage(SetWindow& w, int page) {
    page = std::clamp(page, 0, kSetPageCount - 1);
    Set_CommitEdit(w, true);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    if (page == w.page) return;
    w.page = page;
    w.scrollY = w.scrollTarget = 0;
    w.focus = -1;
    w.pageT = Set_Anim(w) ? 0.0f : 1.0f;
    Set_BuildAndClamp(w);
}

static void Set_OpenLink(PCWSTR url) {
#ifdef SCM_HARNESS
    Wh_Log(L"settings: would open %s", url);
#else
    ShellExecuteW(nullptr, L"open", url, nullptr, nullptr, SW_SHOWNORMAL);
#endif
}

// A click (or Space or Enter) on a field's control.
static void Set_ActivateField(SetWindow& w, int k, const SetHit* hit) {
    SetField& f = w.fields[k];
    if (w.recording >= 0 && w.recording != k) Set_StopRecording(w);
    switch (f.kind) {
        case SetField::Check:
            f.cur = f.cur == L"1" ? L"0" : L"1";
            Set_Invalidate(w);
            break;
        case SetField::Choice:
            if (w.openSel == k) {
                Set_ClosePopup(w);
            } else {
                Set_CommitEdit(w, true);
                Set_OpenPopup(w, k);
            }
            break;
        case SetField::Number:
        case SetField::Text:
            Set_BeginEdit(w, k);
            break;
        case SetField::Color:
            if (hit && hit->kind == SetHit::Chip) {
                Set_CommitEdit(w, false);
                f.cur = Set_HexFromRgb(kSetChips[hit->b]);
                Set_SetStatus(w, L"");
            } else {
                Set_BeginEdit(w, k);
            }
            break;
        case SetField::Hotkey:
            if (hit && hit->kind == SetHit::Clear) {
                f.cur.clear();
                Set_Invalidate(w);
            } else if (w.recording == k) {
                Set_StopRecording(w);
            } else {
                Set_CommitEdit(w, true);
                Set_StartRecording(w, k);
            }
            break;
    }
}

static void Set_FooterAction(SetWindow& w, int which) {
    if (which == 0) {
        Set_ResetToSuggested(w);
    } else if (which == 1) {
        if (!w.render) DestroyWindow(w.hwnd);  // w is gone after this.
    } else {
        Set_CommitEdit(w, true);
        if (g_setWin && g_setWin->hwnd == w.hwnd) Set_Save(g_setWin);
    }
}

// ---- Saving ---------------------------------------------------------------------

static std::wstring Set_ChangedParams(SetWindow& w, int& changed) {
    std::wstring params = L"--quiet mod settings set " + Set_QuoteArg(WH_MOD_ID);
    changed = 0;
    for (auto& f : w.fields) {
        std::wstring value = Set_FieldValue(f);
        if (value != f.value) {
            params += L" " + Set_QuoteArg(std::wstring(f.key) + L"=" + value);
            if (wcscmp(f.key, L"settingsTrayIcon") == 0) params += L" " + Set_QuoteArg(L"trayIcon=" + value);
            changed++;
        }
    }
    return params;
}

static void Set_Save(std::shared_ptr<SetWindow> keep) {
    SetWindow& w = *keep;
    if (w.saving) return;
    Set_StopRecording(w);
    int changed = 0;
    std::wstring params = Set_ChangedParams(w, changed);
    if (!changed) {
        Set_SetStatus(w, L"Nothing changed");
        return;
    }
    std::wstring cli = Set_CliPath();
#ifdef SCM_HARNESS
    // Tests check the command instead of running it.
    std::string line = WideToUtf8(Set_QuoteArg(cli.empty() ? L"windhawk-cli.exe" : cli) + L" " + params);
    HANDLE file = CreateFileW((StoragePath() + L"\\settings-save.txt").c_str(), GENERIC_WRITE, 0, nullptr,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    DWORD written = 0;
    bool ok = file != INVALID_HANDLE_VALUE && WriteFile(file, line.data(), (DWORD)line.size(), &written, nullptr);
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    if (!ok) {
        Set_SetStatus(w, L"Couldn't write settings-save.txt", true);
        return;
    }
    for (auto& f : w.fields) f.value = Set_FieldValue(f);
    Set_SetStatus(w, L"Saved");
    return;
#else
    if (cli.empty()) {
        Set_SetStatus(w, L"Couldn't find windhawk-cli.exe, so nothing was saved", true);
        return;
    }
    SHELLEXECUTEINFOW info{sizeof(info)};
    info.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC | SEE_MASK_FLAG_NO_UI;
    info.hwnd = w.hwnd;
    info.lpVerb = L"runas";
    info.lpFile = cli.c_str();
    info.lpParameters = params.c_str();
    info.nShow = SW_HIDE;
    if (!ShellExecuteExW(&info) || !info.hProcess) {
        DWORD error = GetLastError();
        if (error == ERROR_CANCELLED) {
            Set_SetStatus(w, L"Not saved. The admin prompt was turned down.", true);
        } else {
            WCHAR text[96];
            swprintf_s(text, L"Couldn't start windhawk-cli (error %lu)", error);
            Set_SetStatus(w, text, true);
        }
        return;
    }
    w.saving = true;
    Set_SetStatus(w, L"Saving...");
    // Keep painting and handling input while windhawk-cli works.
    bool quit = false, timedOut = false;
    int quitCode = 0;
    ULONGLONG deadline = GetTickCount64() + 15000;
    while (!quit && !w.destroyed) {
        ULONGLONG now = GetTickCount64();
        if (now >= deadline) {
            timedOut = true;
            break;
        }
        DWORD r = MsgWaitForMultipleObjects(1, &info.hProcess, FALSE, (DWORD)(deadline - now), QS_ALLINPUT);
        if (r == WAIT_OBJECT_0) break;
        if (r != WAIT_OBJECT_0 + 1) {
            timedOut = r == WAIT_TIMEOUT;
            break;
        }
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                quit = true;
                quitCode = (int)msg.wParam;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    DWORD code = 1;
    bool finished = WaitForSingleObject(info.hProcess, 0) == WAIT_OBJECT_0;
    if (finished) GetExitCodeProcess(info.hProcess, &code);
    if (!finished) TerminateProcess(info.hProcess, ERROR_TIMEOUT);
    CloseHandle(info.hProcess);
    w.saving = false;
    if (quit) PostQuitMessage(quitCode);
    if (w.destroyed || !IsWindow(w.hwnd)) return;
    if (!finished && timedOut) {
        Set_SetStatus(w, L"Windhawk didn't answer in 15 seconds. Settings may not be saved.", true);
    } else if (code == 0) {
        Set_LoadFields(w);  // Shows what was stored.
        Set_SetStatus(w, L"Saved");
    } else {
        Wh_Log(L"windhawk-cli exit code %lu", code);
        WCHAR text[96];
        swprintf_s(text, L"Windhawk didn't save the settings (code %lu)", code);
        Set_SetStatus(w, text, true);
    }
#endif
}

// ---- Animation tick ----------------------------------------------------------------

static bool Set_Tick(SetWindow& w) {
    bool moved = false, anim = Set_Anim(w);
    auto step = [&](float& v, float target, float rate) {
        float d = target - v;
        if (!anim || fabsf(d) < 0.02f) {
            if (v != target) {
                v = target;
                moved = true;
            }
            return;
        }
        v += d * rate;
        moved = true;
    };
    int ids[2];
    Set_HoverIds(w.hover, ids);
    for (int id : ids)
        if (id >= 0 && !w.glow.count(id)) w.glow[id] = 0;
    for (auto it = w.glow.begin(); it != w.glow.end();) {
        bool on = it->first == ids[0] || it->first == ids[1];
        step(it->second, on ? 1.0f : 0.0f, 0.3f);
        if (!on && it->second == 0) {
            it = w.glow.erase(it);
        } else {
            ++it;
        }
    }
    for (size_t k = 0; k < w.fields.size(); k++) {
        if (w.fields[k].kind != SetField::Check) continue;
        float target = w.fields[k].cur == L"1" ? 1.0f : 0.0f;
        if (!w.knob.count((int)k)) w.knob[(int)k] = target;
        step(w.knob[(int)k], target, 0.35f);
    }
    if (w.scrollY != w.scrollTarget) {
        float d = w.scrollTarget - w.scrollY;
        if (!anim || fabsf(d) < 0.5f) {
            w.scrollY = w.scrollTarget;
        } else {
            w.scrollY += d * 0.25f;
        }
        moved = true;
        Set_PlaceEdit(w);
    }
    if (w.pageT < 1) {
        w.pageT = anim ? std::min(1.0f, w.pageT + 0.07f) : 1.0f;
        moved = true;
    }
    // Sidebar open / collapse, and the dock edges lighting up under the pointer.
    if (!w.dragRail) {
        float target = w.railCollapsed ? kSetRailMini : w.railW, d = target - w.railCur;
        if (d != 0) {
            w.railCur = (!anim || fabsf(d) < 0.6f) ? target : w.railCur + d * 0.28f;
            Set_BuildPage(w);
            Set_PlaceEdit(w);
            moved = true;
        }
    }
    bool inRail = w.mouseX >= 0 && Set_In(Set_RailDock(w), w.mouseX, w.mouseY);
    D2D1_RECT_F foot = Set_FooterDock(w);
    bool inFoot = w.mouseX >= 0 && Set_In(foot, w.mouseX, w.mouseY);
    step(w.railGlow, inRail ? 1.0f : 0.0f, 0.25f);
    step(w.footGlow, inFoot ? 1.0f : 0.0f, 0.25f);
    return moved;
}

// ---- Keyboard focus ----------------------------------------------------------------

// Focus order: the page's rows, then Reset, Cancel, Save (-1, -2, -3).
static std::vector<int> Set_FocusOrder(const SetWindow& w) {
    std::vector<int> order;
    for (auto& it : w.items)
        if (it.type == SetItem::Row) order.push_back(it.field);
    order.push_back(-1);
    order.push_back(-2);
    order.push_back(-3);
    return order;
}

static void Set_EnsureVisible(SetWindow& w, float top, float bottom) {
    float view = Set_ViewH(w);
    float clear = Set_FootClear() - 18;  // Keep focused rows above the floating footer.
    if (top - 16 < w.scrollTarget) {
        w.scrollTarget = top - 16;
    } else if (bottom + 16 + clear > w.scrollTarget + view) {
        w.scrollTarget = bottom + 16 + clear - view;
    }
    w.scrollTarget = std::clamp(w.scrollTarget, 0.0f, std::max(0.0f, w.contentH - view));
}

static void Set_MoveFocus(SetWindow& w, int dir) {
    Set_CommitEdit(w, true);
    Set_ClosePopup(w);
    std::vector<int> order = Set_FocusOrder(w);
    int index = -1;
    for (size_t i = 0; i < order.size(); i++)
        if (order[i] == w.focus) index = (int)i;
    index = index < 0 ? (dir > 0 ? 0 : (int)order.size() - 1) : (index + dir + (int)order.size()) % (int)order.size();
    w.focus = order[index];
    w.kbd = true;
    if (w.focus >= 0) {
        if (const SetItem* it = Set_ItemOfField(w, w.focus)) Set_EnsureVisible(w, it->y, it->y + it->h);
    }
    Set_Invalidate(w);
}

static void Set_Adjust(SetWindow& w, int dir) {
    if (w.focus < 0) return;
    SetField& f = w.fields[w.focus];
    if (f.kind == SetField::Number) {
        int span = f.max - f.min, step = span <= 100 ? 1 : span <= 3000 ? 10 : 100;
        f.cur = std::to_wstring(std::clamp(_wtoi(Set_FieldValue(f).c_str()) + dir * step, f.min, f.max));
    } else if (f.kind == SetField::Choice && !f.options.empty()) {
        int n = (int)f.options.size(), at = 0;
        for (int i = 0; i < n; i++)
            if (f.cur == f.options[i].first) at = i;
        f.cur = f.options[(at + dir + n) % n].first;
    } else if (f.kind == SetField::Check) {
        f.cur = dir > 0 ? L"1" : L"0";
    }
    Set_Invalidate(w);
}

static bool Set_OnKey(SetWindow& w, UINT vk) {
    if (w.saving) return true;
    if (w.recording >= 0) {
        if (Set_IsModifier(vk)) return true;
        UINT mods = 0;
        if (GetKeyState(VK_CONTROL) & 0x8000) mods |= MOD_CONTROL;
        if (GetKeyState(VK_MENU) & 0x8000) mods |= MOD_ALT;
        if (GetKeyState(VK_SHIFT) & 0x8000) mods |= MOD_SHIFT;
        if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & 0x8000) mods |= MOD_WIN;
        SetField& f = w.fields[w.recording];
        if (vk == VK_ESCAPE && !mods) {
            // Cancel: keep what was there.
        } else if ((vk == VK_BACK || vk == VK_DELETE) && !mods) {
            f.cur.clear();
        } else {
            f.cur = Set_FormatHotkey(mods, vk);
        }
        Set_StopRecording(w);
        return true;
    }
    if (w.openSel >= 0) {
        const SetField& f = w.fields[w.openSel];
        int n = (int)f.options.size();
        if (vk == VK_ESCAPE) Set_ClosePopup(w);
        else if (vk == VK_UP) w.dropHover = (w.dropHover - 1 + n) % n;
        else if (vk == VK_DOWN) w.dropHover = (w.dropHover + 1) % n;
        else if (vk == VK_RETURN || vk == VK_SPACE) Set_Choose(w, w.openSel, w.dropHover);
        Set_Invalidate(w);
        return true;
    }
    bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0, shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
    if (ctrl && vk == 'B') {  // Same shortcut as T3's sidebar.
        Set_ToggleRail(w);
        return true;
    }
    float view = Set_ViewH(w), maxScroll = std::max(0.0f, w.contentH - view);
    switch (vk) {
        case VK_TAB:
            if (ctrl) Set_GoPage(w, (w.page + (shift ? kSetPageCount - 1 : 1)) % kSetPageCount);
            else Set_MoveFocus(w, shift ? -1 : 1);
            return true;
        case VK_SPACE:
        case VK_RETURN:
            w.kbd = true;
            if (w.focus >= 0) Set_ActivateField(w, w.focus, nullptr);
            else if (w.focus <= -1 && w.focus >= -3) Set_FooterAction(w, -1 - w.focus);
            return true;
        case VK_LEFT:
        case VK_RIGHT:
            w.kbd = true;
            Set_Adjust(w, vk == VK_RIGHT ? 1 : -1);
            return true;
        case VK_UP: w.scrollTarget = std::clamp(w.scrollTarget - 60, 0.0f, maxScroll); break;
        case VK_DOWN: w.scrollTarget = std::clamp(w.scrollTarget + 60, 0.0f, maxScroll); break;
        case VK_PRIOR: w.scrollTarget = std::clamp(w.scrollTarget - view * 0.9f, 0.0f, maxScroll); break;
        case VK_NEXT: w.scrollTarget = std::clamp(w.scrollTarget + view * 0.9f, 0.0f, maxScroll); break;
        case VK_HOME: w.scrollTarget = 0; break;
        case VK_END: w.scrollTarget = maxScroll; break;
        case VK_ESCAPE:
            if (!w.render) DestroyWindow(w.hwnd);
            return true;
        default:
            if (ctrl && vk >= '1' && vk <= '6') {
                Set_GoPage(w, (int)(vk - '1'));
                return true;
            }
            return false;
    }
    if (!Set_Anim(w)) w.scrollY = w.scrollTarget;
    Set_PlaceEdit(w);
    Set_Invalidate(w);
    return true;
}

// ---- Window ---------------------------------------------------------------------

static bool Set_EnsureRt(SetWindow& w) {
    if (w.rt) return true;
    if (!Set_EnsureFactories()) return false;
    RECT rc;
    GetClientRect(w.hwnd, &rc);
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
        (float)w.dpi, (float)w.dpi);
    return SUCCEEDED(g_setD2d->CreateHwndRenderTarget(
        props, D2D1::HwndRenderTargetProperties(w.hwnd, D2D1::SizeU(std::max(1L, rc.right), std::max(1L, rc.bottom))),
        w.rt.put()));
}

static void Set_Relayout(SetWindow& w) {
    RECT rc;
    GetClientRect(w.hwnd, &rc);
    w.cw = rc.right * 96.0f / w.dpi;
    w.ch = std::max(0.0f, rc.bottom * 96.0f / w.dpi - kSetCapH);
    if (w.rt) w.rt->Resize(D2D1::SizeU(std::max(1L, rc.right), std::max(1L, rc.bottom)));
    Set_BuildAndClamp(w);
}

static void Set_RememberRect(SetWindow& w) {
    if (w.render || IsIconic(w.hwnd) || IsZoomed(w.hwnd)) return;
    GetWindowRect(w.hwnd, &w.normalRect);
}

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

static void Set_RegisterClass() {
    static bool done;
    if (done) return;
    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = Set_WndProc;
    wc.hInstance = g_hInstance;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kSettingsClass;
    RegisterClassExW(&wc);
    done = true;
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
                                   g_hInstance, nullptr);
    }
    const int offX = GetSystemMetrics(SM_XVIRTUALSCREEN) - 6000, offY = GetSystemMetrics(SM_YVIRTUALSCREEN);
    w->nativeTitle = !render && (Wh_GetIntSetting(L"nativeSettingsTitleBar") != 0 ||
        GetStringSetting(L"settingsTitleButtons") != L"builtin");
    w->nativeButtons = !render && !w->nativeTitle && GetStringSetting(L"settingsTitleButtons") != L"builtin";
    w->glass = !render && Wh_GetIntSetting(L"settingsGlass") != 0;
    kSetCapH = w->nativeTitle ? 0.0f : 40.0f;
    const DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Clipboard Manager settings", style,
                                render ? offX : CW_USEDEFAULT, render ? offY : CW_USEDEFAULT, 800, 600, w->owner,
                                nullptr, g_hInstance, nullptr);
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
            // Windows acrylic as one sheet over the whole window, the way T3 (Electron
            // backgroundMaterial "acrylic") does it: the system backdrop with the frame extended
            // into the full client area, and no caption color, so the title bar and the page are
            // the same material and turn solid together when the window loses focus.
            int backdrop = 3;  // DWMSBT_TRANSIENTWINDOW
            DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
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

// ---- PNG rendering (harness) ----------------------------------------------------

static bool Set_SavePng(IWICBitmap* bitmap, const std::wstring& path) {
    SetCom<IWICFormatConverter> conv;
    SetCom<IWICStream> stream;
    SetCom<IWICBitmapEncoder> encoder;
    SetCom<IWICBitmapFrameEncode> frame;
    UINT pw = 0, ph = 0;
    bitmap->GetSize(&pw, &ph);
    WICPixelFormatGUID fmt = GUID_WICPixelFormat32bppBGRA;
    return SUCCEEDED(g_setWic->CreateFormatConverter(conv.put())) &&
           SUCCEEDED(conv->Initialize(bitmap, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, nullptr, 0,
                                      WICBitmapPaletteTypeCustom)) &&
           SUCCEEDED(g_setWic->CreateStream(stream.put())) &&
           SUCCEEDED(stream->InitializeFromFilename(path.c_str(), GENERIC_WRITE)) &&
           SUCCEEDED(g_setWic->CreateEncoder(GUID_ContainerFormatPng, nullptr, encoder.put())) &&
           SUCCEEDED(encoder->Initialize(stream.get(), WICBitmapEncoderNoCache)) &&
           SUCCEEDED(encoder->CreateNewFrame(frame.put(), nullptr)) && SUCCEEDED(frame->Initialize(nullptr)) &&
           SUCCEEDED(frame->SetSize(pw, ph)) && SUCCEEDED(frame->SetPixelFormat(&fmt)) &&
           SUCCEEDED(frame->WriteSource(conv.get(), nullptr)) && SUCCEEDED(frame->Commit()) &&
           SUCCEEDED(encoder->Commit());
}

// Draws the window's current state off-screen into a bitmap and saves it. No window is shown.
static bool Set_CaptureToPng(SetWindow& w, const std::wstring& path) {
    if (!Set_EnsureFactories()) return false;
    UINT pw = (UINT)std::ceil(w.cw * w.dpi / 96.0f), ph = (UINT)std::ceil((w.ch + kSetCapH) * w.dpi / 96.0f);
    SetCom<IWICBitmap> bitmap;
    SetCom<ID2D1RenderTarget> target;
    if (FAILED(g_setWic->CreateBitmap(pw, ph, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnLoad, bitmap.put())))
        return false;
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
        (float)w.dpi, (float)w.dpi);
    if (FAILED(g_setD2d->CreateWicBitmapRenderTarget(bitmap.get(), props, target.put()))) return false;
    Set_Draw(w, target.get());
    return Set_SavePng(bitmap.get(), path);
}

// One page at one scale (dpi 96 is 1.0x, 144 is 1.5x). Nothing appears on the desktop.
static bool Set_RenderAt(const std::wstring& path, UINT dpi, int page) {
    Settings_Close();
    g_setForceDpi = dpi;
    bool ok = Set_Create(true);
    if (ok) {
        SetWindow& w = *g_setWin;
        w.page = std::clamp(page, 0, kSetPageCount - 1);
        Set_BuildPage(w);
        w.ch = std::clamp(w.contentH, 680.0f, 1400.0f);
        Set_BuildPage(w);
        ok = Set_CaptureToPng(w, path);
    }
    Settings_Close();
    g_setForceDpi = 0;
    return ok;
}

bool Settings_RenderToPng(const std::wstring& path) { return Set_RenderAt(path, 96, 0); }

// ---- Self test ------------------------------------------------------------------
// The 1.2.x settings checks were written for the old sidebar and footer; the window now follows the
// shared design (Seamless Launchpad 2.4.3), so this stays an empty hook until they are rewritten.
#ifdef SCM_HARNESS
int Harness_TestSettings() { return 0; }
#endif

// ---------------------------------------------------------------------------
// 90-main.cpp : settings, shared helpers, the UI thread and the tool mod
// entry points. Owned by the lead.
// ---------------------------------------------------------------------------

HINSTANCE g_hInstance;
DWORD g_uiThreadId;
HWND g_msgWnd;
std::atomic<bool> g_stopping;
Settings g_set;

static HANDLE g_uiThread;
static HANDLE g_uiReady;
static UINT g_taskbarCreatedMsg;

std::wstring GetStringSetting(PCWSTR key) {
    PCWSTR value = Wh_GetStringSetting(key);
    std::wstring out = value ? value : L"";
    Wh_FreeStringSetting(value);
    return out;
}

COLORREF ParseColorRef(const std::wstring& text, COLORREF fallback) {
    std::wstring hex = text;
    while (!hex.empty() && iswspace(hex.back())) hex.pop_back();
    size_t start = hex.find_first_not_of(L" \t");
    hex = start == std::wstring::npos ? L"" : hex.substr(start);
    if (!hex.empty() && hex[0] == L'#') hex = hex.substr(1);
    if (hex.size() != 6 || hex.find_first_not_of(L"0123456789abcdefABCDEF") != std::wstring::npos)
        return fallback;
    UINT rgb = wcstoul(hex.c_str(), nullptr, 16);
    return RGB(rgb >> 16, (rgb >> 8) & 0xFF, rgb & 0xFF);
}

std::wstring Utf8ToWide(const std::string& s) {
    if (s.empty()) return {};
    int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
    std::wstring out(n, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), out.data(), n);
    return out;
}

std::string WideToUtf8(const std::wstring& s) {
    if (s.empty()) return {};
    int n = WideCharToMultiByte(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0, nullptr, nullptr);
    std::string out(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, s.data(), (int)s.size(), out.data(), n, nullptr, nullptr);
    return out;
}

std::wstring StoragePath() {
    WCHAR buf[MAX_PATH * 2]{};
    if (!Wh_GetModStoragePath(buf, ARRAYSIZE(buf))) return {};
    std::wstring path = buf;
    while (!path.empty() && (path.back() == L'\\' || path.back() == L'/')) path.pop_back();
    SHCreateDirectoryExW(nullptr, path.c_str(), nullptr);
    return path;
}

bool WildcardMatchList(const std::wstring& name, const std::wstring& list) {
    size_t start = 0;
    while (start <= list.size()) {
        size_t end = list.find_first_of(L";|,", start);
        if (end == std::wstring::npos) end = list.size();
        std::wstring pattern = list.substr(start, end - start);
        size_t a = pattern.find_first_not_of(L" \t");
        size_t b = pattern.find_last_not_of(L" \t");
        if (a != std::wstring::npos) {
            pattern = pattern.substr(a, b - a + 1);
            if (PathMatchSpecW(name.c_str(), pattern.c_str())) return true;
        }
        start = end + 1;
    }
    return false;
}

std::wstring ProcessNameOfWindow(HWND hwnd) {
    DWORD pid = 0;
    if (!hwnd || !GetWindowThreadProcessId(hwnd, &pid) || !pid) return {};
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!process) return {};
    WCHAR path[MAX_PATH * 2];
    DWORD size = ARRAYSIZE(path);
    std::wstring out;
    if (QueryFullProcessImageNameW(process, 0, path, &size)) out = PathFindFileNameW(path);
    CloseHandle(process);
    return out;
}

int64_t UnixNow() {
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULARGE_INTEGER t{{ft.dwLowDateTime, ft.dwHighDateTime}};
    return (int64_t)((t.QuadPart - 116444736000000000ULL) / 10000000ULL);
}

int GetState(PCWSTR name, int fallback) { return Wh_GetIntValue(name, fallback); }
void SetState(PCWSTR name, int value) { Wh_SetIntValue(name, value); }

std::wstring StateKey(PCWSTR window, PCWSTR field) {
    WCHAR key[128];
    swprintf_s(key, L"%s_%dx%d_%s", window, GetSystemMetrics(SM_CXVIRTUALSCREEN),
               GetSystemMetrics(SM_CYVIRTUALSCREEN), field);
    return key;
}

void ApplyDarkWindow(HWND hwnd) {
    BOOL dark = TRUE;
    DwmSetWindowAttribute(hwnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    SetWindowTheme(hwnd, L"DarkMode_Explorer", nullptr);
}

// uxtheme's unnamed exports: SetPreferredAppMode (135) and FlushMenuThemes (136).
static void EnableDarkMenus() {
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!ux) return;
    using SetMode = int(WINAPI*)(int);
    using Flush = void(WINAPI*)();
    if (auto set = (SetMode)GetProcAddress(ux, MAKEINTRESOURCEA(135))) set(2 /* ForceDark */);
    if (auto flush = (Flush)GetProcAddress(ux, MAKEINTRESOURCEA(136))) flush();
}

static std::wstring Choice(PCWSTR key, std::initializer_list<PCWSTR> allowed) {
    std::wstring value = GetStringSetting(key);
    for (PCWSTR a : allowed)
        if (value == a) return value;
    return *allowed.begin();  // The first allowed value is the default.
}

static int Clamped(PCWSTR key, int lo, int hi, int fallbackIfZeroInvalid = INT_MIN) {
    int v = Wh_GetIntSetting(key);
    if (fallbackIfZeroInvalid != INT_MIN && v == 0 && lo > 0) v = fallbackIfZeroInvalid;
    return std::clamp(v, lo, hi);
}

float SystemCornerRadius(bool small) {
    static ULONGLONG checked;
    static float big = 8, little = 4;
    ULONGLONG now = GetTickCount64();
    if (!checked || now - checked > 10000) {  // The mod can be turned on or off any time.
        checked = now;
        big = 8;
        little = 4;
        HKEY k;
        if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius", 0, KEY_READ | KEY_WOW64_64KEY, &k) == ERROR_SUCCESS) {
            DWORD off = 0, size = sizeof(off);
            bool enabled = RegGetValueW(k, nullptr, L"Disabled", RRF_RT_REG_DWORD, nullptr, &off, &size) != ERROR_SUCCESS || !off;
            auto read = [&](PCWSTR name, float& out) {
                DWORD v = 0, sz = sizeof(v);
                if (RegGetValueW(k, L"Settings", name, RRF_RT_REG_DWORD, nullptr, &v, &sz) == ERROR_SUCCESS && v > 0 && v < 64)
                    out = (float)v;
            };
            if (enabled) {
                read(L"radius", big);
                read(L"smallRadius", little);
            }
            RegCloseKey(k);
        }
    }
    return small ? little : big;
}

void LoadSettings() {
    Settings s;
    s.hotkey = GetStringSetting(L"hotkey");
    s.hotkey2 = GetStringSetting(L"hotkey2");
    s.plainTextHotkey = GetStringSetting(L"plainTextHotkey");
    s.positionHotkeys = Choice(L"positionHotkeys", {L"off", L"ctrlWin", L"ctrlAlt", L"altWin"});
    s.takeOverWinV = Wh_GetIntSetting(L"takeOverWinV") != 0;
    s.positionHotkeysPaste = Wh_GetIntSetting(L"positionHotkeysPaste") != 0;
    s.positionHotkeysMoveToTop = Wh_GetIntSetting(L"positionHotkeysMoveToTop") != 0;
    s.openAt = Choice(L"openAt", {L"caret", L"cursor", L"remember"});
    s.windowWidth = Clamped(L"windowWidth", 200, 2000, 450);
    s.windowHeight = Clamped(L"windowHeight", 150, 2000, 400);
    s.linesPerRow = Clamped(L"linesPerRow", 1, 10, 5);
    s.showPositions = Wh_GetIntSetting(L"showPositions") != 0;
    s.showThumbnails = Wh_GetIntSetting(L"showThumbnails") != 0;
    s.closeOnFocusLoss = Wh_GetIntSetting(L"closeOnFocusLoss") != 0;
    s.alwaysOnTop = Wh_GetIntSetting(L"alwaysOnTop") != 0;
    s.confirmDelete = Wh_GetIntSetting(L"confirmDelete") != 0;
    s.fontName = GetStringSetting(L"fontName");
    if (s.fontName.empty()) s.fontName = L"FiraCode Nerd Font";
    s.fontSize = Clamped(L"fontSize", 7, 24, 10);
    {
        std::wstring w = Choice(L"fontWeight", {L"medium", L"light", L"normal", L"semibold", L"bold"});
        s.fontWeight = w == L"light" ? 300 : w == L"normal" ? 400 : w == L"semibold" ? 600 : w == L"bold" ? 700 : 500;
    }
    s.blurMode = Choice(L"blurMode", {L"acrylic", L"mica", L"none"});
    s.backgroundOpacity = Clamped(L"backgroundOpacity", 0, 100);
    s.accentColor = ParseColorRef(GetStringSetting(L"accentColor"), RefFromRgb(mocha::blue));
    s.accentColor2 = ParseColorRef(GetStringSetting(L"accentColor2"), RefFromRgb(mocha::mauve));
    s.gradientBorder = Wh_GetIntSetting(L"gradientBorder") != 0;
    s.ownBorder = Wh_GetIntSetting(L"ownBorder") != 0;
    s.nativeSettingsTitleBar = Wh_GetIntSetting(L"nativeSettingsTitleBar") != 0;
    s.animations = Wh_GetIntSetting(L"animations") != 0;
    s.cornerRadius = Clamped(L"cornerRadius", 0, 24);
    s.maxClips = Clamped(L"maxClips", 0, 100000);
    s.expireDays = Clamped(L"expireDays", 0, 3650);
    s.saveImages = Wh_GetIntSetting(L"saveImages") != 0;
    s.saveFiles = Wh_GetIntSetting(L"saveFiles") != 0;
    s.saveRichText = Wh_GetIntSetting(L"saveRichText") != 0;
    s.maxClipMB = Clamped(L"maxClipMB", 1, 512, 64);
    s.allowDuplicates = Wh_GetIntSetting(L"allowDuplicates") != 0;
    s.moveToTopOnPaste = Wh_GetIntSetting(L"moveToTopOnPaste") != 0;
    s.includeApps = GetStringSetting(L"includeApps");
    if (s.includeApps.empty()) s.includeApps = L"*";
    s.excludeApps = GetStringSetting(L"excludeApps");
    s.pasteKeys = Choice(L"pasteKeys", {L"ctrlV", L"shiftInsert"});
    s.pasteDelay = Clamped(L"pasteDelay", 0, 2000);
    s.multiSeparator = Choice(L"multiSeparator", {L"newline", L"space", L"none", L"comma"});
    s.searchMode = Choice(L"searchMode", {L"contains", L"allWords", L"startsWith"});
    s.searchFullText = Wh_GetIntSetting(L"searchFullText") != 0;
    s.trayIcon = Wh_GetIntSetting(L"trayIcon") != 0 && Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    g_set = std::move(s);
}

static void ApplyAll() {
    Hotkeys_Unregister();
    Hotkeys_Register();
    if (g_set.trayIcon) {
        Tray_Create();
        Tray_Update();
    } else {
        Tray_Remove();
    }
    List_ApplySettings();
}

static LRESULT CALLBACK MsgWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (g_taskbarCreatedMsg && msg == g_taskbarCreatedMsg) {
        if (g_set.trayIcon) Tray_OnTaskbarCreated();
        return 0;
    }
    switch (msg) {
        case WM_CLIPBOARDUPDATE:
            Capture_OnClipboardUpdate();
            return 0;
        case WM_HOTKEY:
            Hotkeys_OnHotkey((int)wParam);
            return 0;
        case WM_TIMER:
            if (wParam == kTimerCleanup) {
                Db_Cleanup();
            } else {
                Capture_OnTimer(wParam);
            }
            return 0;
        case WM_SCM_TRAY:
            Tray_OnMessage(wParam, lParam);
            return 0;
        case WM_SCM_SHOW_LIST:
            List_Show();
            return 0;
        case WM_SCM_CLIP_SAVED:
            List_OnClipSaved((int64_t)lParam);
            return 0;
        case WM_SCM_OPEN_SETTINGS:
            Settings_Open();
            return 0;
        case WM_SCM_SETTINGS_CHANGED:
            LoadSettings();
            ApplyAll();
            return 0;
        case WM_SCM_QUIT:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            g_stopping = true;
            KillTimer(hwnd, kTimerCleanup);
            Capture_Stop();
            Hotkeys_Unregister();
            Tray_Remove();
            Settings_Close();
            List_Destroy();
            Db_Close();
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static DWORD WINAPI UiThread(LPVOID) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    OleInitialize(nullptr);  // Drag and drop, clipboard, WIC.
    g_uiThreadId = GetCurrentThreadId();
    EnableDarkMenus();

    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = MsgWndProc;
    wc.hInstance = g_hInstance;
    wc.lpszClassName = kMsgClass;
    RegisterClassExW(&wc);
    // A real (hidden) top-level window, not HWND_MESSAGE: it must receive the
    // TaskbarCreated broadcast and own the tray icon.
    g_msgWnd = CreateWindowExW(WS_EX_TOOLWINDOW, kMsgClass, L"Seamless Clipboard Manager", WS_POPUP,
                               0, 0, 0, 0, nullptr, nullptr, g_hInstance, nullptr);
    g_taskbarCreatedMsg = RegisterWindowMessageW(L"TaskbarCreated");
    ChangeWindowMessageFilterEx(g_msgWnd, g_taskbarCreatedMsg, MSGFLT_ALLOW, nullptr);

    bool ok = g_msgWnd && Db_Open();
    if (!ok) Wh_Log(L"Startup failed: %s", Db_LastError().c_str());
    SetEvent(g_uiReady);
    if (!ok) {
        if (g_msgWnd) DestroyWindow(g_msgWnd);
        OleUninitialize();
        return 1;
    }

    ApplyAll();
    Capture_Start();
    Db_Cleanup();
    SetTimer(g_msgWnd, kTimerCleanup, 10 * 60 * 1000, nullptr);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        // Dialog-style keyboard navigation for the settings, editor and
        // properties windows (they set WS_EX_CONTROLPARENT).
        // The editor root draws its own text box and takes every key itself: its messages skip the
        // dialog manager, which dropped characters posted straight to it.
        HWND root = msg.hwnd ? GetAncestor(msg.hwnd, GA_ROOT) : nullptr;
        bool ownKeys = root && msg.hwnd == root && (SendMessageW(root, WM_GETDLGCODE, 0, 0) & DLGC_WANTALLKEYS);
        if (root && !ownKeys && (GetWindowLongPtrW(root, GWL_EXSTYLE) & WS_EX_CONTROLPARENT) &&
            IsDialogMessageW(root, &msg)) {
            continue;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    OleUninitialize();
    return 0;
}

static bool StartUi() {
    g_stopping = false;
    g_uiReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_uiThread = CreateThread(nullptr, 0, UiThread, nullptr, 0, nullptr);
    if (!g_uiThread) return false;
    HANDLE waits[] = {g_uiReady, g_uiThread};
    DWORD r = WaitForMultipleObjects(2, waits, FALSE, 120000);  // First run imports Ditto's database.
    if (r != WAIT_OBJECT_0) return false;
    DWORD code = STILL_ACTIVE;
    if (WaitForSingleObject(g_uiThread, 0) == WAIT_OBJECT_0) GetExitCodeThread(g_uiThread, &code);
    return code == STILL_ACTIVE;
}

static void StopUi() {
    if (!g_uiThread) return;
    g_stopping = true;
    if (g_msgWnd) PostMessageW(g_msgWnd, WM_SCM_QUIT, 0, 0);
    if (WaitForSingleObject(g_uiThread, 15000) != WAIT_OBJECT_0) {
        Wh_Log(L"UI thread did not stop in 15 s");
    }
    CloseHandle(g_uiThread);
    g_uiThread = nullptr;
    if (g_uiReady) CloseHandle(g_uiReady);
    g_uiReady = nullptr;
}

#ifndef SCM_HARNESS
#include <windhawk_tool_mod.h>

static HANDLE g_singleInstance;

BOOL WhTool_ModInit() {
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       (LPCWSTR)&WhTool_ModInit, (HMODULE*)&g_hInstance);
    // One copy per user session.
    g_singleInstance = CreateMutexW(nullptr, FALSE, L"Local\\SeamlessClipboardManagerRunning");
    if (!g_singleInstance || GetLastError() == ERROR_ALREADY_EXISTS) {
        if (g_singleInstance) CloseHandle(g_singleInstance);
        g_singleInstance = nullptr;
        Wh_Log(L"Already running");
        return FALSE;
    }
    LoadSettings();
    if (!StartUi()) {
        StopUi();
        CloseHandle(g_singleInstance);
        g_singleInstance = nullptr;
        return FALSE;
    }
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (g_msgWnd) PostMessageW(g_msgWnd, WM_SCM_SETTINGS_CHANGED, 0, 0);
}

void WhTool_ModUninit() {
    StopUi();
    if (g_singleInstance) CloseHandle(g_singleInstance);
    g_singleInstance = nullptr;
}
#endif
