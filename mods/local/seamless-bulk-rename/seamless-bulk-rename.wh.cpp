// ==WindhawkMod==
// @id              seamless-bulk-rename
// @name            Seamless Bulk Rename
// @description     Rename many files at once with a stack of rules and a live before and after list
// @version         1.0.1
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/seamless-workshop
// @license         MIT
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         windhawk.exe
// @include         explorer.exe
// @compilerOptions -ld2d1 -ldwrite -lwindowscodecs -lole32 -loleaut32 -luuid -lgdi32 -lgdiplus -luser32 -lshell32 -lshlwapi -ladvapi32 -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -lversion -lntdll -lpropsys -lbcrypt -Wl,--delayload=d2d1.dll -Wl,--delayload=dwrite.dll -Wl,--delayload=windowscodecs.dll -Wl,--delayload=comdlg32.dll -Wl,--delayload=imm32.dll -Wl,--delayload=gdiplus.dll -Wl,--delayload=propsys.dll -Wl,--delayload=bcrypt.dll -ldelayimp
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Bulk Rename

Rename a whole folder of files in one go. Stack up rules on the left, watch every
new name appear on the right before anything changes, then press Rename. One click
puts it all back if you change your mind.

![Seamless Bulk Rename](https://raw.githubusercontent.com/DavidHiFi/seamless-workshop/main/media/previews/seamless-bulk-rename.png)

## How to open it

- Select files in Explorer and press Ctrl+Shift+F2. With nothing selected, it takes the whole folder.
- Or right-click them, pick Show more options, then Bulk rename.
- Or click its tray icon and drop files on the window.

## What it can do

- Find and replace, with plain text or patterns, in the name, the extension or both.
- Swap characters, change letter case, cut letters from the start, end or middle.
- Remove words, digits, symbols, accents, double spaces, or everything before or after some text.
- Move a part of the name from the front to the back, or the other way.
- Add text at the front, the back or any spot, with dates and counters inside it.
- Add the file's date, its folder's name, or a number in five styles with padding.
- Change, add or drop the extension.
- Use photo and music details in names: title, artist, album, track, year, camera, size and more.
- Change file dates and the read-only, hidden and archive marks.
- Copy to a folder under the new names instead of renaming.
- Five saved presets, and undo for the last ten runs, even after a restart.

## Words you can type into any text box

- `$YYYY $YY $MM $MMM $MMMM $DD $DDD $DDDD $hh $mm $ss $fff`: the file's date.
- `${}` a counter, `${start=10,increment=5,padding=3}` with options.
- `${rstringalnum=8}`, `${rstringalpha=8}`, `${rstringdigit=8}`, `${ruuidv4}`: random text.
- `{title} {artist} {album} {albumartist} {track} {year} {genre}`: music details.
- `{taken} {camera} {make} {width} {height} {duration}`: photo and video details.
- `{folder} {size} {md5} {sha1} {sha256} {crc32}`: the folder, size and checksums.

## Good to know

- Nothing changes until you press Rename. Names that would clash, break or repeat show in red and are skipped.
- Every run is written to an undo list first, so even a crash halfway can be put back.
- The rules you set are kept when you press Save. Presets keep up to five sets.

## Credits

- Built on the ideas and rename tokens of [PowerToys PowerRename](https://github.com/microsoft/PowerToys) by Microsoft (MIT).
- Inspired by [Bulk Rename Utility](https://www.bulkrenameutility.co.uk) by TGRMN Software. No code from it is used.

Made by [DavidHiFi](https://github.com/DavidHiFi). Like it? [Buy me a coffee on Ko-fi](https://ko-fi.com/DavidHiFi).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- rep:
  - find: ""
    $name: Find
    $description: "The text to look for. Leave blank to skip."
  - with: ""
    $name: Replace with
    $description: "What goes in its place. Dates, counters and $1 for pattern groups work here."
  - regex: false
    $name: Use a pattern
    $description: "Treat Find as a pattern, so one rule can match many shapes of name."
  - matchCase: false
    $name: Match case
    $description: "Only match the same capitals and small letters."
  - all: true
    $name: Replace every match
    $description: "Off replaces only the first match in each name."
  - scope: name
    $name: Look in
    $description: "Which part of the file name the rule changes."
    $options:
    - name: The name
    - ext: The extension
    - both: Name and extension
  $name: Find and replace
- ch:
  - from: ""
    $name: Characters to swap
    $description: "Each character here is swapped for the one at the same spot below."
  - to: ""
    $name: Swap them for
    $description: "Leave a spot empty to drop that character."
  $name: Swap characters
- nm:
  - mode: keep
    $name: Name
    $description: "Keep the name, clear it, set a new one, or flip it back to front."
    $options:
    - keep: Keep the name
    - remove: Clear the name
    - fixed: Use a new name
    - reverse: Flip it back to front
  - fixed: ""
    $name: New name
    $description: "Used when Name is set to Use a new name. Add a counter so names don't repeat."
  $name: Name
- cs:
  - mode: same
    $name: Letter case
    $description: "Change the capitals in the name."
    $options:
    - same: Leave as is
    - lower: all small
    - upper: ALL CAPITALS
    - title: Each Word Capital
    - sentence: First letter capital
  - except: ""
    $name: Words to leave alone
    $description: "Space-separated words kept exactly as you type them, like USB or iPhone."
  $name: Letter case
- rm:
  - first: 0
    $name: Cut from the start
    $description: "0 to 255 letters cut from the start."
  - last: 0
    $name: Cut from the end
    $description: "0 to 255 letters cut from the end."
  - from: 0
    $name: Cut from spot
    $description: "0 to 255: where a middle cut starts, 1 is the first letter. 0 turns it off."
  - count: 0
    $name: Letters to cut there
    $description: "0 to 255 letters cut from that spot."
  - chars: ""
    $name: Characters to remove
    $description: "Every one of these characters is removed wherever it shows."
  - words: ""
    $name: Words to remove
    $description: "Space-separated whole words that are removed."
  - digits: false
    $name: Remove digits
    $description: "Drops 0 to 9 from the name."
  - symbols: false
    $name: Remove symbols
    $description: "Drops everything that isn't a letter, a digit or a space."
  - accents: false
    $name: Remove accents
    $description: "Turns letters like e with an accent into plain ones."
  - doubleSpaces: true
    $name: Remove double spaces
    $description: "Turns runs of spaces into one."
  - trim: true
    $name: Trim spaces
    $description: "Drops spaces at the start and end of the name."
  - crop: none
    $name: Crop
    $description: "Drop everything before or after some text."
    $options:
    - none: Off
    - before: Drop what comes before it
    - after: Drop what comes after it
  - cropText: ""
    $name: Crop at
    $description: "The text Crop looks for. The text itself stays."
  $name: Remove
- mv:
  - mode: none
    $name: Move part
    $description: "Move some letters from one end of the name to the other."
    $options:
    - none: Off
    - startToEnd: From the start to the end
    - endToStart: From the end to the start
  - count: 0
    $name: Letters to move
    $description: "0 to 255 letters moved."
  - sep: " "
    $name: Joined with
    $description: "Text put between the moved part and the rest."
  $name: Move part
- add:
  - prefix: ""
    $name: Add to the start
    $description: "Text put in front of the name."
  - suffix: ""
    $name: Add to the end
    $description: "Text put after the name, before the extension."
  - insert: ""
    $name: Insert text
    $description: "Text put at the spot below."
  - at: 0
    $name: Insert at spot
    $description: "0 to 255: where Insert text goes, 0 is before the first letter."
  - fromEnd: false
    $name: Count the spot from the end
    $description: "Count Insert at spot from the end of the name."
  - wordSpace: false
    $name: Space between words
    $description: "Puts a space before each capital, so MyHolidayPhoto reads My Holiday Photo."
  $name: Add text
- dt:
  - mode: none
    $name: Add the date
    $description: "Put the file's date in the name."
    $options:
    - none: Off
    - prefix: At the start
    - suffix: At the end
  - which: modified
    $name: Which date
    $description: "Photo taken falls back to the change date when a file has none."
    $options:
    - modified: Last changed
    - created: Created
    - taken: Photo taken
    - now: Today
  - format: "YYYY-MM-DD"
    $name: Date shape
    $description: "YYYY year, MM month, DD day, hh hour, mm minute, ss second."
  - sep: " "
    $name: Joined with
    $description: "Text put between the date and the name."
  $name: Date
- fd:
  - mode: none
    $name: Add the folder name
    $description: "Put the name of the folder the file sits in into the name."
    $options:
    - none: Off
    - prefix: At the start
    - suffix: At the end
  - levels: 1
    $name: Folders up
    $description: "1 to 5 folder names, nearest last."
  - sep: " - "
    $name: Joined with
    $description: "Text put between the folder name and the name."
  $name: Folder name
- num:
  - mode: none
    $name: Add a number
    $description: "Count the files in list order."
    $options:
    - none: Off
    - prefix: At the start
    - suffix: At the end
    - insert: At a spot
    - replace: Instead of the name
  - start: 1
    $name: Start at
    $description: "0 to 999999: the first number."
  - step: 1
    $name: Count by
    $description: "1 to 1000: how much each number goes up."
  - pad: 0
    $name: Digits
    $description: "0 to 10: pad with zeros to this many digits, 3 makes 001."
  - at: 0
    $name: Spot
    $description: "0 to 255: where the number goes when it is At a spot."
  - sep: " "
    $name: Joined with
    $description: "Text put between the number and the name."
  - restart: false
    $name: Start again in each folder
    $description: "Each folder counts from the start again."
  - style: decimal
    $name: Number style
    $description: "How the number is written."
    $options:
    - decimal: 1 2 3
    - alphaLower: a b c
    - alphaUpper: A B C
    - roman: I II III
    - hex: 1 A 1F
  $name: Numbers
- ext:
  - mode: same
    $name: Extension
    $description: "Change the part after the last dot."
    $options:
    - same: Leave as is
    - lower: all small
    - upper: ALL CAPITALS
    - fixed: Use a new one
    - add: Add one after it
    - remove: Remove it
  - fixed: ""
    $name: New extension
    $description: "Without the dot. Used by Use a new one and Add one after it."
  $name: Extension
- f:
  - include: "*"
    $name: Only these files
    $description: "Wildcards split by a semicolon, like *.jpg;*.png. Used when a whole folder is added."
  - files: true
    $name: Files
    $description: "Take files when a folder is added."
  - folders: false
    $name: Folders
    $description: "Take folders when a folder is added."
  - subfolders: false
    $name: Look inside subfolders
    $description: "Take what is inside the folders too."
  - hidden: false
    $name: Hidden files
    $description: "Take hidden and system files too."
  - sort: natural
    $name: Order
    $description: "The order numbers count in."
    $options:
    - natural: Name, 2 before 10
    - name: Name, letter by letter
    - modified: Last changed
    - created: Created
    - size: Size
    - type: Type
    - added: As added
  - sortDesc: false
    $name: Reverse the order
    $description: "Count from the last one."
  $name: Files
- fdt:
  - on: false
    $name: Change file dates
    $description: "Set the dates on each file as it is renamed."
  - which: modified
    $name: Dates to change
    $description: "Which of the dates are set."
    $options:
    - modified: Last changed
    - created: Created
    - both: Both
  - mode: now
    $name: Set them to
    $description: "Now, the date below, or the date the photo was taken."
    $options:
    - now: Now
    - fixed: The date below
    - taken: Photo taken
  - value: "2026-01-01 12:00"
    $name: Date
    $description: "As YYYY-MM-DD hh:mm."
  $name: File dates
- at:
  - readOnly: keep
    $name: Read-only
    $description: "Lock the file against changes, or unlock it."
    $options:
    - keep: Leave as is
    - set: Turn on
    - clear: Turn off
  - hidden: keep
    $name: Hidden
    $description: "Hide the file, or show it."
    $options:
    - keep: Leave as is
    - set: Turn on
    - clear: Turn off
  - archive: keep
    $name: Archive
    $description: "The mark backup apps use."
    $options:
    - keep: Leave as is
    - set: Turn on
    - clear: Turn off
  $name: Marks
- cp:
  - on: false
    $name: Copy instead of rename
    $description: "Leave the files as they are and copy them under the new names."
  - folder: ""
    $name: Copy to
    $description: "The folder the copies go in. Blank puts them next to the files."
  $name: Copy
- preset:
  - name: ""
    $name: Preset name
    $description: "The name a preset is saved under."
  $name: Presets
- renameHotkey: Ctrl+Shift+F2
  $name: Shortcut
  $description: "Press it in Explorer or on the desktop to rename what is selected, or the whole folder when nothing is."
- menuEntry: true
  $name: Bulk rename in the right-click menu
  $description: "Adds Bulk rename next to Rename. It shows under Show more options."
- undoLevels: 10
  $name: Runs to keep for undo
  $description: "1 to 20 runs kept, newest first."
- afterRename: keep
  $name: After renaming
  $description: "What the window does once a rename is done."
  $options:
  - keep: Keep the list
  - clear: Clear the list
  - close: Close the window
- confirmBig: true
  $name: Ask before big runs
  $description: "Over 500 files, Rename needs a second click."
- settingsAnimation: true
  $name: Open and close animation
  $description: "The window fades in with a short slide. Stays still when Windows animations are off."
- settingsGlass: true
  $name: Blurred settings window
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: Native Windows title bar
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: Tray icon
  $description: "An icon in the tray. Click it to open the window. Right-click for undo and settings."
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <commdlg.h>
#include <dwmapi.h>
#include <gdiplus.h>
#include <objbase.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <uxtheme.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <windhawk_utils.h>
#include <tlhelp32.h>
#include <bcrypt.h>
#include <propvarutil.h>
#include <propsys.h>
#include <shlguid.h>
#include <exdisp.h>
#include <shobjidl.h>
#include <cstring>
#include <random>
#include <map>
#include <imm.h>
#include <d2d1helper.h>
#include <d2d1_1.h>
#include <shlobj.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <cwctype>
#include <functional>
#include <memory>
#include <mutex>
#include <regex>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

extern "C" IMAGE_DOS_HEADER __ImageBase;

// ---- Keys ---------------------------------------------------------------------------------------------------------

static std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t\r\n");
    if (a == std::wstring::npos) return {};
    return s.substr(a, s.find_last_not_of(L" \t\r\n") - a + 1);
}

struct KeyName {
    UINT vk;
    const wchar_t* name;
};
// Canonical names first; later entries for the same key are accepted aliases.
static const KeyName kKeyNames[] = {
    {VK_SPACE, L"Space"},   {VK_TAB, L"Tab"},         {VK_RETURN, L"Enter"},   {VK_ESCAPE, L"Esc"},
    {VK_INSERT, L"Insert"}, {VK_DELETE, L"Delete"},   {VK_HOME, L"Home"},      {VK_END, L"End"},
    {VK_PRIOR, L"PageUp"},  {VK_NEXT, L"PageDown"},   {VK_UP, L"Up"},          {VK_DOWN, L"Down"},
    {VK_LEFT, L"Left"},     {VK_RIGHT, L"Right"},     {VK_OEM_3, L"`"},        {VK_OEM_MINUS, L"-"},
    {VK_OEM_PLUS, L"="},    {VK_OEM_4, L"["},         {VK_OEM_6, L"]"},        {VK_OEM_5, L"\\"},
    {VK_OEM_1, L";"},       {VK_OEM_7, L"'"},         {VK_OEM_COMMA, L","},    {VK_OEM_PERIOD, L"."},
    {VK_OEM_2, L"/"},       {VK_PAUSE, L"Pause"},     {VK_SNAPSHOT, L"PrintScreen"},
    {VK_CAPITAL, L"CapsLock"}, {VK_ADD, L"NumpadPlus"}, {VK_SUBTRACT, L"NumpadMinus"},
    {VK_MULTIPLY, L"NumpadStar"}, {VK_DIVIDE, L"NumpadSlash"}, {VK_DECIMAL, L"NumpadDot"},
    {VK_RETURN, L"Return"}, {VK_ESCAPE, L"Escape"},   {VK_INSERT, L"Ins"},     {VK_DELETE, L"Del"},
    {VK_PRIOR, L"PgUp"},    {VK_NEXT, L"PgDn"},
};

static UINT KeyFromName(const std::wstring& n) {
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
    for (const auto& k : kKeyNames)
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
        parts.push_back(Trim(text.substr(start, plus == std::wstring::npos ? std::wstring::npos : plus - start)));
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
    vk = parts.back().empty() ? 0 : KeyFromName(parts.back());
    if (!vk) mods = 0;
    return vk != 0;
}

std::wstring Hotkey_Format(UINT mods, UINT vk) {
    std::wstring key;
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) key = std::wstring(1, (wchar_t)vk);
    else if (vk >= VK_F1 && vk <= VK_F24) key = L"F" + std::to_wstring(vk - VK_F1 + 1);
    else if (vk >= VK_NUMPAD0 && vk <= VK_NUMPAD9) key = L"Numpad" + std::to_wstring(vk - VK_NUMPAD0);
    else
        for (const auto& k : kKeyNames)
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

static std::wstring SettingString(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return s;
}

// The class of the tool process's hidden tray window. Explorer sends it the selected paths.
constexpr WCHAR kBruTrayClass[] = L"SeamlessBulkRenameTray";
constexpr ULONG_PTR kBruCopyPaths = 0x53425231;  // "SBR1": the paths to rename, joined by NULs.

// ---- Rename rules ---------------------------------------------------------------------------------------------------
// One pass per file, in the order the pages show: replace, swap letters, name, capitals, remove, move, add, date,
// folder, number, extension. The preview and the rename both use this, so what the list shows is what happens.

static std::atomic<bool> g_bruAnim{true};

namespace bru {

using Getter = std::function<std::wstring(PCWSTR)>;

struct Item {
    std::wstring path, dir, name;
    bool isDir = false;
    FILETIME created{}, modified{};
    ULONGLONG size = 0;
    DWORD attrs = 0;
    int order = 0;
    std::wstring newName, error;
    int state = 0;  // 0 same, 1 changes, 2 has a problem
    bool checked = true;
    bool tagsRead = false;
    std::map<std::wstring, std::wstring> tags;
    FILETIME takenFt{};
    bool hasTaken = false;
    std::map<std::wstring, std::wstring> hashes;
};

static bool Truthy(const std::wstring& v) { return v == L"1" || v == L"true"; }

static int Pick(const std::wstring& v, std::initializer_list<PCWSTR> opts) {
    int i = 0;
    for (PCWSTR o : opts) {
        if (v == o) return i;
        i++;
    }
    return 0;
}

static long long Num(const std::wstring& v, long long lo, long long hi, long long def) {
    if (v.empty()) return def;
    wchar_t* end = nullptr;
    long long n = wcstoll(v.c_str(), &end, 10);
    if (end == v.c_str()) return def;
    return std::clamp(n, lo, hi);
}

static std::vector<std::wstring> Words(const std::wstring& s) {
    std::vector<std::wstring> out;
    std::wstring cur;
    for (wchar_t c : s) {
        if (c == L' ' || c == L'\t') {
            if (!cur.empty()) out.push_back(cur);
            cur.clear();
        } else {
            cur += c;
        }
    }
    if (!cur.empty()) out.push_back(cur);
    return out;
}

static std::wstring MapCase(const std::wstring& s, DWORD flag) {
    if (s.empty()) return s;
    int n = LCMapStringEx(LOCALE_NAME_USER_DEFAULT, flag | LCMAP_LINGUISTIC_CASING, s.c_str(), (int)s.size(), nullptr,
                          0, nullptr, nullptr, 0);
    if (n <= 0) return s;
    std::wstring o((size_t)n, L'\0');
    LCMapStringEx(LOCALE_NAME_USER_DEFAULT, flag | LCMAP_LINGUISTIC_CASING, s.c_str(), (int)s.size(), o.data(), n,
                  nullptr, nullptr, 0);
    return o;
}
static std::wstring Lower(const std::wstring& s) { return MapCase(s, LCMAP_LOWERCASE); }
static std::wstring Upper(const std::wstring& s) { return MapCase(s, LCMAP_UPPERCASE); }

static bool SameAt(const std::wstring& h, size_t i, const std::wstring& n, bool matchCase) {
    if (i + n.size() > h.size()) return false;
    if (matchCase) return h.compare(i, n.size(), n) == 0;
    return CompareStringOrdinal(h.c_str() + i, (int)n.size(), n.c_str(), (int)n.size(), TRUE) == CSTR_EQUAL;
}

static size_t Find(const std::wstring& h, const std::wstring& n, size_t from, bool matchCase) {
    if (n.empty() || n.size() > h.size()) return std::wstring::npos;
    for (size_t i = from; i + n.size() <= h.size(); i++)
        if (SameAt(h, i, n, matchCase)) return i;
    return std::wstring::npos;
}

static bool WordChar(wchar_t c) { return IsCharAlphaNumericW(c) != FALSE; }

static bool WholeAt(const std::wstring& h, size_t i, size_t len) {
    return (i == 0 || !WordChar(h[i - 1])) && (i + len >= h.size() || !WordChar(h[i + len]));
}

// ---- Dates ----------------------------------------------------------------------------------------------------------

static SYSTEMTIME LocalTime(const FILETIME& ft) {
    SYSTEMTIME utc{}, local{};
    FileTimeToSystemTime(&ft, &utc);
    if (!SystemTimeToTzSpecificLocalTime(nullptr, &utc, &local)) local = utc;
    return local;
}

static std::wstring Pad(long long v, int width) {
    std::wstring s = std::to_wstring(v < 0 ? -v : v);
    while ((int)s.size() < width) s.insert(s.begin(), L'0');
    return v < 0 ? L"-" + s : s;
}

static std::wstring LocaleDate(const SYSTEMTIME& st, PCWSTR picture) {
    WCHAR buf[96];
    if (GetDateFormatEx(LOCALE_NAME_USER_DEFAULT, 0, &st, picture, buf, 96, nullptr) > 0) return buf;
    return {};
}

// Matches the longest date word at p. YYYY year, MM month, MMM and MMMM its name, DD day, DDD and DDDD the day's
// name, hh hour, mm minute, ss second, fff thousandths.
static bool DateWord(const wchar_t* p, const SYSTEMTIME& st, size_t& len, std::wstring& out) {
    struct W {
        PCWSTR w;
        int id;
    };
    static const W kWords[] = {{L"YYYY", 0}, {L"MMMM", 1}, {L"DDDD", 2}, {L"MMM", 3}, {L"DDD", 4}, {L"fff", 5},
                               {L"YY", 6},   {L"MM", 7},   {L"DD", 8},   {L"hh", 9}, {L"mm", 10}, {L"ss", 11}};
    for (const W& w : kWords) {
        size_t n = wcslen(w.w);
        if (wcsncmp(p, w.w, n) != 0) continue;
        len = n;
        switch (w.id) {
            case 0: out = Pad(st.wYear, 4); break;
            case 1: out = LocaleDate(st, L"MMMM"); break;
            case 2: out = LocaleDate(st, L"dddd"); break;
            case 3: out = LocaleDate(st, L"MMM"); break;
            case 4: out = LocaleDate(st, L"ddd"); break;
            case 5: out = Pad(st.wMilliseconds, 3); break;
            case 6: out = Pad(st.wYear % 100, 2); break;
            case 7: out = Pad(st.wMonth, 2); break;
            case 8: out = Pad(st.wDay, 2); break;
            case 9: out = Pad(st.wHour, 2); break;
            case 10: out = Pad(st.wMinute, 2); break;
            default: out = Pad(st.wSecond, 2); break;
        }
        return true;
    }
    return false;
}

static std::wstring FormatDate(const std::wstring& shape, const SYSTEMTIME& st) {
    std::wstring out, word;
    for (size_t i = 0; i < shape.size();) {
        size_t len = 0;
        if (DateWord(shape.c_str() + i, st, len, word)) {
            out += word;
            i += len;
        } else {
            out += shape[i++];
        }
    }
    return out;
}

// ---- File details ---------------------------------------------------------------------------------------------------

#define BRU_KEY(name, a, b, c, d0, d1, d2, d3, d4, d5, d6, d7, pid) \
    static const PROPERTYKEY name = {{a, b, c, {d0, d1, d2, d3, d4, d5, d6, d7}}, pid}
BRU_KEY(kPkTitle, 0xF29F85E0, 0x4FF9, 0x1068, 0xAB, 0x91, 0x08, 0x00, 0x2B, 0x27, 0xB3, 0xD9, 2);
BRU_KEY(kPkArtist, 0x56A3372E, 0xCE9C, 0x11D2, 0x9F, 0x0E, 0x00, 0x60, 0x97, 0xC6, 0x86, 0xF6, 2);
BRU_KEY(kPkAlbum, 0x56A3372E, 0xCE9C, 0x11D2, 0x9F, 0x0E, 0x00, 0x60, 0x97, 0xC6, 0x86, 0xF6, 4);
BRU_KEY(kPkYear, 0x56A3372E, 0xCE9C, 0x11D2, 0x9F, 0x0E, 0x00, 0x60, 0x97, 0xC6, 0x86, 0xF6, 5);
BRU_KEY(kPkTrack, 0x56A3372E, 0xCE9C, 0x11D2, 0x9F, 0x0E, 0x00, 0x60, 0x97, 0xC6, 0x86, 0xF6, 7);
BRU_KEY(kPkGenre, 0x56A3372E, 0xCE9C, 0x11D2, 0x9F, 0x0E, 0x00, 0x60, 0x97, 0xC6, 0x86, 0xF6, 11);
BRU_KEY(kPkAlbumArtist, 0x56A3372E, 0xCE9C, 0x11D2, 0x9F, 0x0E, 0x00, 0x60, 0x97, 0xC6, 0x86, 0xF6, 13);
BRU_KEY(kPkDuration, 0x64440490, 0x4C8B, 0x11D1, 0x8B, 0x70, 0x08, 0x00, 0x36, 0xB1, 0x1A, 0x03, 3);
BRU_KEY(kPkTaken, 0x14B81DA1, 0x0135, 0x4D31, 0x96, 0xD9, 0x6C, 0xBF, 0xC9, 0x67, 0x1A, 0x99, 36867);
BRU_KEY(kPkMake, 0x14B81DA1, 0x0135, 0x4D31, 0x96, 0xD9, 0x6C, 0xBF, 0xC9, 0x67, 0x1A, 0x99, 271);
BRU_KEY(kPkModel, 0x14B81DA1, 0x0135, 0x4D31, 0x96, 0xD9, 0x6C, 0xBF, 0xC9, 0x67, 0x1A, 0x99, 272);
BRU_KEY(kPkImageW, 0x6444048F, 0x4C8B, 0x11D1, 0x8B, 0x70, 0x08, 0x00, 0x36, 0xB1, 0x1A, 0x03, 3);
BRU_KEY(kPkImageH, 0x6444048F, 0x4C8B, 0x11D1, 0x8B, 0x70, 0x08, 0x00, 0x36, 0xB1, 0x1A, 0x03, 4);
BRU_KEY(kPkVideoW, 0x64440491, 0x4C8B, 0x11D1, 0x8B, 0x70, 0x08, 0x00, 0x36, 0xB1, 0x1A, 0x03, 3);
BRU_KEY(kPkVideoH, 0x64440491, 0x4C8B, 0x11D1, 0x8B, 0x70, 0x08, 0x00, 0x36, 0xB1, 0x1A, 0x03, 4);
#undef BRU_KEY

static std::wstring PropText(IPropertyStore* ps, const PROPERTYKEY& k) {
    PROPVARIANT pv;
    PropVariantInit(&pv);
    std::wstring out;
    if (SUCCEEDED(ps->GetValue(k, &pv)) && pv.vt != VT_EMPTY) {
        PWSTR s = nullptr;
        if (SUCCEEDED(PropVariantToStringAlloc(pv, &s)) && s) {
            out = s;
            CoTaskMemFree(s);
        }
    }
    PropVariantClear(&pv);
    return out;
}

// Reads the music, photo and video details once, the first time a {word} needs them.
static void ReadTags(Item& it) {
    if (it.tagsRead) return;
    it.tagsRead = true;
    if (it.isDir) return;
    IPropertyStore* ps = nullptr;
    if (FAILED(SHGetPropertyStoreFromParsingName(it.path.c_str(), nullptr, GPS_BESTEFFORT, IID_PPV_ARGS(&ps))) || !ps)
        return;
    it.tags[L"title"] = PropText(ps, kPkTitle);
    it.tags[L"artist"] = PropText(ps, kPkArtist);
    it.tags[L"album"] = PropText(ps, kPkAlbum);
    it.tags[L"albumartist"] = PropText(ps, kPkAlbumArtist);
    it.tags[L"track"] = PropText(ps, kPkTrack);
    it.tags[L"year"] = PropText(ps, kPkYear);
    it.tags[L"genre"] = PropText(ps, kPkGenre);
    it.tags[L"make"] = PropText(ps, kPkMake);
    it.tags[L"camera"] = PropText(ps, kPkModel);
    std::wstring w = PropText(ps, kPkImageW), h = PropText(ps, kPkImageH);
    if (w.empty()) w = PropText(ps, kPkVideoW);
    if (h.empty()) h = PropText(ps, kPkVideoH);
    it.tags[L"width"] = w;
    it.tags[L"height"] = h;
    PROPVARIANT pv;
    PropVariantInit(&pv);
    if (SUCCEEDED(ps->GetValue(kPkDuration, &pv)) && pv.vt != VT_EMPTY) {
        ULONGLONG d = 0;
        if (SUCCEEDED(PropVariantToUInt64(pv, &d)) && d) {
            ULONGLONG s = d / 10000000ULL;
            ULONGLONG hh = s / 3600, mm = (s / 60) % 60, ss = s % 60;
            it.tags[L"duration"] = hh ? std::to_wstring(hh) + L"-" + Pad((long long)mm, 2) + L"-" + Pad((long long)ss, 2)
                                      : Pad((long long)mm, 2) + L"-" + Pad((long long)ss, 2);
        }
    }
    PropVariantClear(&pv);
    PropVariantInit(&pv);
    if (SUCCEEDED(ps->GetValue(kPkTaken, &pv)) && pv.vt == VT_FILETIME) {
        it.takenFt = pv.filetime;
        it.hasTaken = true;
    }
    PropVariantClear(&pv);
    ps->Release();
}

static uint32_t Crc32Of(const uint8_t* p, size_t n, uint32_t crc) {
    static uint32_t table[256];
    static bool ready = false;
    if (!ready) {
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t c = i;
            for (int k = 0; k < 8; k++) c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
            table[i] = c;
        }
        ready = true;
    }
    for (size_t i = 0; i < n; i++) crc = table[(crc ^ p[i]) & 0xFF] ^ (crc >> 8);
    return crc;
}

// md5, sha1, sha256 or crc32 of the file, in small letters. Files over 512 MB are skipped, so the list stays quick.
static std::wstring HashOf(Item& it, const std::wstring& algo) {
    auto found = it.hashes.find(algo);
    if (found != it.hashes.end()) return found->second;
    std::wstring out;
    if (!it.isDir && it.size <= 512ULL * 1024 * 1024) {
        HANDLE f = CreateFileW(it.path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                               nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
        if (f != INVALID_HANDLE_VALUE) {
            std::vector<uint8_t> buf(1 << 20);
            BCRYPT_ALG_HANDLE alg = nullptr;
            BCRYPT_HASH_HANDLE hash = nullptr;
            bool crc = algo == L"crc32";
            uint32_t crcv = 0xFFFFFFFFu;
            PCWSTR id = algo == L"md5" ? L"MD5" : algo == L"sha1" ? L"SHA1" : L"SHA256";
            bool ok = crc || (BCryptOpenAlgorithmProvider(&alg, id, nullptr, 0) >= 0 &&
                              BCryptCreateHash(alg, &hash, nullptr, 0, nullptr, 0, 0) >= 0);
            DWORD got = 0;
            while (ok && ReadFile(f, buf.data(), (DWORD)buf.size(), &got, nullptr) && got) {
                if (crc) crcv = Crc32Of(buf.data(), got, crcv);
                else ok = BCryptHashData(hash, buf.data(), got, 0) >= 0;
            }
            if (ok) {
                uint8_t digest[32];
                ULONG dn = 0;
                if (crc) {
                    crcv ^= 0xFFFFFFFFu;
                    for (int i = 0; i < 4; i++) digest[i] = (uint8_t)(crcv >> (24 - 8 * i));
                    dn = 4;
                } else {
                    dn = algo == L"md5" ? 16 : algo == L"sha1" ? 20 : 32;
                    if (BCryptFinishHash(hash, digest, dn, 0) < 0) dn = 0;
                }
                static const wchar_t hex[] = L"0123456789abcdef";
                for (ULONG i = 0; i < dn; i++) {
                    out += hex[digest[i] >> 4];
                    out += hex[digest[i] & 15];
                }
            }
            if (hash) BCryptDestroyHash(hash);
            if (alg) BCryptCloseAlgorithmProvider(alg, 0);
            CloseHandle(f);
        }
    }
    it.hashes[algo] = out;
    return out;
}

// ---- The rules ------------------------------------------------------------------------------------------------------

struct Rules {
    std::wstring repFind, repWith;
    bool repRegex = false, repCase = false, repAll = true;
    int repScope = 0;  // 0 name, 1 extension, 2 both
    std::shared_ptr<std::wregex> re;
    bool reBad = false;
    std::wstring chFrom, chTo;
    int nmMode = 0;  // keep, remove, fixed, reverse
    std::wstring nmFixed;
    int csMode = 0;  // same, lower, upper, title, sentence
    std::vector<std::wstring> csExcept;
    int rmFirst = 0, rmLast = 0, rmFrom = 0, rmCount = 0;
    std::wstring rmChars;
    std::vector<std::wstring> rmWords;
    bool rmDigits = false, rmSymbols = false, rmAccents = false, rmDouble = true, rmTrim = true;
    int rmCrop = 0;  // none, before, after
    std::wstring rmCropText;
    int mvMode = 0, mvCount = 0;  // none, startToEnd, endToStart
    std::wstring mvSep;
    std::wstring addPrefix, addSuffix, addInsert;
    int addAt = 0;
    bool addFromEnd = false, addWordSpace = false;
    int dtMode = 0, dtWhich = 0;  // none, prefix, suffix / modified, created, taken, now
    std::wstring dtFormat, dtSep;
    int fdMode = 0, fdLevels = 1;
    std::wstring fdSep;
    int numMode = 0;  // none, prefix, suffix, insert, replace
    long long numStart = 1, numStep = 1;
    int numPad = 0, numAt = 0, numStyle = 0;  // decimal, alphaLower, alphaUpper, roman, hex
    std::wstring numSep;
    bool numRestart = false;
    int extMode = 0;  // same, lower, upper, fixed, add, remove
    std::wstring extFixed;
    uint32_t seed = 0;
    SYSTEMTIME now{};
};

static Rules ReadRules(const Getter& g, uint32_t seed) {
    Rules r;
    r.repFind = g(L"rep.find");
    r.repWith = g(L"rep.with");
    r.repRegex = Truthy(g(L"rep.regex"));
    r.repCase = Truthy(g(L"rep.matchCase"));
    r.repAll = Truthy(g(L"rep.all"));
    r.repScope = Pick(g(L"rep.scope"), {L"name", L"ext", L"both"});
    if (r.repRegex && !r.repFind.empty()) {
        try {
            auto flags = std::regex_constants::ECMAScript;
            if (!r.repCase) flags |= std::regex_constants::icase;
            r.re = std::make_shared<std::wregex>(r.repFind, flags);
        } catch (...) {
            r.reBad = true;
        }
    }
    r.chFrom = g(L"ch.from");
    r.chTo = g(L"ch.to");
    r.nmMode = Pick(g(L"nm.mode"), {L"keep", L"remove", L"fixed", L"reverse"});
    r.nmFixed = g(L"nm.fixed");
    r.csMode = Pick(g(L"cs.mode"), {L"same", L"lower", L"upper", L"title", L"sentence"});
    r.csExcept = Words(g(L"cs.except"));
    r.rmFirst = (int)Num(g(L"rm.first"), 0, 255, 0);
    r.rmLast = (int)Num(g(L"rm.last"), 0, 255, 0);
    r.rmFrom = (int)Num(g(L"rm.from"), 0, 255, 0);
    r.rmCount = (int)Num(g(L"rm.count"), 0, 255, 0);
    r.rmChars = g(L"rm.chars");
    r.rmWords = Words(g(L"rm.words"));
    r.rmDigits = Truthy(g(L"rm.digits"));
    r.rmSymbols = Truthy(g(L"rm.symbols"));
    r.rmAccents = Truthy(g(L"rm.accents"));
    r.rmDouble = Truthy(g(L"rm.doubleSpaces"));
    r.rmTrim = Truthy(g(L"rm.trim"));
    r.rmCrop = Pick(g(L"rm.crop"), {L"none", L"before", L"after"});
    r.rmCropText = g(L"rm.cropText");
    r.mvMode = Pick(g(L"mv.mode"), {L"none", L"startToEnd", L"endToStart"});
    r.mvCount = (int)Num(g(L"mv.count"), 0, 255, 0);
    r.mvSep = g(L"mv.sep");
    r.addPrefix = g(L"add.prefix");
    r.addSuffix = g(L"add.suffix");
    r.addInsert = g(L"add.insert");
    r.addAt = (int)Num(g(L"add.at"), 0, 255, 0);
    r.addFromEnd = Truthy(g(L"add.fromEnd"));
    r.addWordSpace = Truthy(g(L"add.wordSpace"));
    r.dtMode = Pick(g(L"dt.mode"), {L"none", L"prefix", L"suffix"});
    r.dtWhich = Pick(g(L"dt.which"), {L"modified", L"created", L"taken", L"now"});
    r.dtFormat = g(L"dt.format");
    if (r.dtFormat.empty()) r.dtFormat = L"YYYY-MM-DD";
    r.dtSep = g(L"dt.sep");
    r.fdMode = Pick(g(L"fd.mode"), {L"none", L"prefix", L"suffix"});
    r.fdLevels = (int)Num(g(L"fd.levels"), 1, 5, 1);
    r.fdSep = g(L"fd.sep");
    r.numMode = Pick(g(L"num.mode"), {L"none", L"prefix", L"suffix", L"insert", L"replace"});
    r.numStart = Num(g(L"num.start"), 0, 999999, 1);
    r.numStep = Num(g(L"num.step"), 1, 1000, 1);
    r.numPad = (int)Num(g(L"num.pad"), 0, 10, 0);
    r.numAt = (int)Num(g(L"num.at"), 0, 255, 0);
    r.numSep = g(L"num.sep");
    r.numRestart = Truthy(g(L"num.restart"));
    r.numStyle = Pick(g(L"num.style"), {L"decimal", L"alphaLower", L"alphaUpper", L"roman", L"hex"});
    r.extMode = Pick(g(L"ext.mode"), {L"same", L"lower", L"upper", L"fixed", L"add", L"remove"});
    r.extFixed = g(L"ext.fixed");
    while (!r.extFixed.empty() && r.extFixed[0] == L'.') r.extFixed.erase(0, 1);
    r.seed = seed;
    GetLocalTime(&r.now);
    return r;
}

// Splits a file name at its last dot. Folders and names that start with their only dot have no extension.
static void Split(const std::wstring& name, bool isDir, std::wstring& stem, std::wstring& ext, bool& dotted) {
    size_t dot = isDir ? std::wstring::npos : name.rfind(L'.');
    dotted = dot != std::wstring::npos && dot > 0;
    if (dotted) {
        stem = name.substr(0, dot);
        ext = name.substr(dot + 1);
    } else {
        stem = name;
        ext.clear();
    }
}

static FILETIME DateOf(Item& it, int which) {
    if (which == 1) return it.created;
    if (which == 2) {
        ReadTags(it);
        if (it.hasTaken) return it.takenFt;
    }
    return it.modified;
}

struct Ctx {
    Item& it;
    int idx;
    const Rules& r;
};

static const PCWSTR kTagWords[] = {L"title", L"artist", L"album", L"albumartist", L"track",  L"year",
                                   L"genre", L"taken",  L"camera", L"make",       L"width",  L"height",
                                   L"duration", L"folder", L"size", L"md5",       L"sha1",   L"sha256", L"crc32"};

static std::wstring TagValue(Ctx& c, const std::wstring& word) {
    Item& it = c.it;
    if (word == L"folder") return PathFindFileNameW(it.dir.c_str());
    if (word == L"size") {
        WCHAR buf[64] = {};
        StrFormatByteSizeW((LONGLONG)it.size, buf, 64);
        return buf;
    }
    if (word == L"md5" || word == L"sha1" || word == L"sha256" || word == L"crc32") return HashOf(it, word);
    ReadTags(it);
    if (word == L"taken") return it.hasTaken ? FormatDate(L"YYYY-MM-DD", LocalTime(it.takenFt)) : L"";
    auto f = it.tags.find(word);
    return f == it.tags.end() ? L"" : f->second;
}

static std::wstring CounterOrRandom(Ctx& c, const std::wstring& body, std::mt19937& rng, bool& ok) {
    ok = true;
    auto eq = body.find(L'=');
    std::wstring head = Trim(eq == std::wstring::npos ? body : body.substr(0, eq));
    if (head == L"ruuidv4") {
        static const wchar_t hex[] = L"0123456789abcdef";
        std::wstring s;
        for (int i = 0; i < 36; i++) {
            if (i == 8 || i == 13 || i == 18 || i == 23) s += L'-';
            else if (i == 14) s += L'4';
            else if (i == 19) s += hex[8 + (rng() & 3)];
            else s += hex[rng() & 15];
        }
        return s;
    }
    if (head == L"rstringalnum" || head == L"rstringalpha" || head == L"rstringdigit") {
        int n = (int)Num(Trim(body.substr(eq + 1)), 1, 64, 8);
        PCWSTR set = head == L"rstringalnum"   ? L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
                     : head == L"rstringalpha" ? L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
                                               : L"0123456789";
        size_t len = wcslen(set);
        std::wstring s;
        for (int i = 0; i < n; i++) s += set[rng() % len];
        return s;
    }
    long long start = 0, inc = 1;
    int pad = 0;
    size_t pos = 0;
    while (pos <= body.size()) {
        size_t comma = body.find(L',', pos);
        std::wstring part = Trim(body.substr(pos, comma == std::wstring::npos ? std::wstring::npos : comma - pos));
        if (!part.empty()) {
            size_t e = part.find(L'=');
            if (e == std::wstring::npos) return (ok = false), L"";
            std::wstring k = Trim(part.substr(0, e)), v = Trim(part.substr(e + 1));
            if (k == L"start") start = Num(v, -999999999, 999999999, 0);
            else if (k == L"increment") inc = Num(v, -999999, 999999, 1);
            else if (k == L"padding") pad = (int)Num(v, 0, 20, 0);
            else return (ok = false), L"";
        }
        if (comma == std::wstring::npos) break;
        pos = comma + 1;
    }
    return Pad(start + (long long)c.idx * inc, pad);
}

// Fills in the words a text box can hold: $YYYY and the other date words (from the change date), ${} counters,
// ${rstringalnum=N} and ${ruuidv4} random text, and {title}, {artist} and the other file details. In a pattern rule
// $1 and the other group words are left alone, and any $ in a filled-in value is doubled so it stays a $.
static std::wstring Expand(const std::wstring& t, Ctx& c, bool regex, uint32_t salt) {
    if (t.find(L'$') == std::wstring::npos && t.find(L'{') == std::wstring::npos) return t;
    std::mt19937 rng(c.r.seed ^ ((uint32_t)c.idx * 2654435761u) ^ salt);
    auto esc = [&](const std::wstring& v) {
        if (!regex || v.find(L'$') == std::wstring::npos) return v;
        std::wstring o;
        for (wchar_t ch : v) {
            o += ch;
            if (ch == L'$') o += L'$';
        }
        return o;
    };
    std::wstring out, word;
    bool haveDate = false;
    SYSTEMTIME st{};
    for (size_t i = 0; i < t.size();) {
        wchar_t ch = t[i];
        if (ch == L'$' && i + 1 < t.size()) {
            if (t[i + 1] == L'$') {
                out += regex ? L"$$" : L"$";
                i += 2;
                continue;
            }
            if (t[i + 1] == L'{') {
                size_t close = t.find(L'}', i + 2);
                if (close != std::wstring::npos) {
                    bool ok = false;
                    std::wstring v = CounterOrRandom(c, t.substr(i + 2, close - i - 2), rng, ok);
                    if (ok) {
                        out += esc(v);
                        i = close + 1;
                        continue;
                    }
                }
            }
            if (!haveDate) {
                st = LocalTime(c.it.modified);
                haveDate = true;
            }
            size_t len = 0;
            if (DateWord(t.c_str() + i + 1, st, len, word)) {
                out += esc(word);
                i += 1 + len;
                continue;
            }
        }
        if (ch == L'{') {
            size_t close = t.find(L'}', i + 1);
            if (close != std::wstring::npos && close - i - 1 <= 12) {
                std::wstring w = t.substr(i + 1, close - i - 1);
                bool known = false;
                for (PCWSTR k : kTagWords)
                    if (w == k) known = true;
                if (known) {
                    out += esc(TagValue(c, w));
                    i = close + 1;
                    continue;
                }
            }
        }
        out += ch;
        i++;
    }
    return out;
}

static std::wstring PlainReplace(const std::wstring& s, const std::wstring& find, const std::wstring& with, bool mc,
                                 bool all) {
    std::wstring out;
    size_t pos = 0;
    while (true) {
        size_t at = Find(s, find, pos, mc);
        if (at == std::wstring::npos) break;
        out += s.substr(pos, at - pos);
        out += with;
        pos = at + find.size();
        if (!all) break;
    }
    return out + s.substr(pos);
}

static std::wstring Roman(long long n) {
    if (n < 1 || n > 3999) return std::to_wstring(n);
    static const int v[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    static const PCWSTR s[] = {L"M", L"CM", L"D", L"CD", L"C", L"XC", L"L", L"XL", L"X", L"IX", L"V", L"IV", L"I"};
    std::wstring o;
    for (int i = 0; i < 13; i++)
        while (n >= v[i]) {
            o += s[i];
            n -= v[i];
        }
    return o;
}

static std::wstring NumberText(const Rules& r, long long n) {
    switch (r.numStyle) {
        case 1:
        case 2: {
            if (n < 1) n = 1;
            std::wstring s;
            while (n > 0) {
                n--;
                s.insert(s.begin(), (wchar_t)((r.numStyle == 1 ? L'a' : L'A') + n % 26));
                n /= 26;
            }
            return s;
        }
        case 3:
            return Roman(n);
        case 4: {
            WCHAR buf[32];
            swprintf(buf, 32, L"%llX", (unsigned long long)(n < 0 ? 0 : n));
            std::wstring s = buf;
            while ((int)s.size() < r.numPad) s.insert(s.begin(), L'0');
            return s;
        }
        default:
            return Pad(n, r.numPad);
    }
}

static std::wstring DropAccents(const std::wstring& s) {
    int n = FoldStringW(MAP_COMPOSITE, s.c_str(), (int)s.size(), nullptr, 0);
    if (n <= 0) return s;
    std::wstring d((size_t)n, L'\0');
    FoldStringW(MAP_COMPOSITE, s.c_str(), (int)s.size(), d.data(), n);
    std::wstring o;
    for (wchar_t c : d)
        if (c < 0x300 || c > 0x36F) o += c;
    return o;
}

static std::wstring PutBack(const std::wstring& s, const std::vector<std::wstring>& words) {
    std::wstring out = s;
    for (const auto& w : words) {
        size_t pos = 0;
        while ((pos = Find(out, w, pos, false)) != std::wstring::npos) {
            if (WholeAt(out, pos, w.size())) out.replace(pos, w.size(), w);
            pos += w.size();
        }
    }
    return out;
}

static std::wstring TitleCase(const std::wstring& s) {
    std::wstring o = Lower(s);
    bool up = true;
    for (size_t i = 0; i < o.size(); i++) {
        wchar_t c = o[i];
        if (up && IsCharAlphaW(c)) {
            std::wstring u = Upper(std::wstring(1, c));
            if (u.size() == 1) o[i] = u[0];
        }
        up = c == L' ' || c == L'_' || c == L'-' || c == L'(' || c == L'[' || c == L'.' || c == L',';
        if (IsCharAlphaNumericW(c)) up = false;
    }
    return o;
}

static std::wstring SentenceCase(const std::wstring& s) {
    std::wstring o = Lower(s);
    for (size_t i = 0; i < o.size(); i++)
        if (IsCharAlphaW(o[i])) {
            std::wstring u = Upper(std::wstring(1, o[i]));
            if (u.size() == 1) o[i] = u[0];
            break;
        }
    return o;
}

// Works out it.newName for the file at list spot idx (and folderIdx inside its own folder). Sets it.error when a
// rule itself is broken.
static void Compute(Item& it, int idx, int folderIdx, const Rules& r) {
    it.error.clear();
    std::wstring stem, ext;
    bool dotted = false;
    Split(it.name, it.isDir, stem, ext, dotted);
    Ctx c{it, idx, r};

    // 1 Replace.
    if (!r.repFind.empty()) {
        if (r.reBad) {
            it.error = L"The pattern has a mistake";
        } else {
            std::wstring with = Expand(r.repWith, c, r.repRegex, 0x11);
            auto run = [&](const std::wstring& s) -> std::wstring {
                if (!r.repRegex) return PlainReplace(s, r.repFind, with, r.repCase, r.repAll);
                try {
                    auto f = r.repAll ? std::regex_constants::format_default : std::regex_constants::format_first_only;
                    return std::regex_replace(s, *r.re, with, f);
                } catch (...) {
                    it.error = L"The pattern is too slow on this name";
                    return s;
                }
            };
            if (r.repScope == 0) stem = run(stem);
            else if (r.repScope == 1) ext = run(ext);
            else {
                std::wstring whole = dotted ? stem + L"." + ext : stem;
                whole = run(whole);
                Split(whole, it.isDir, stem, ext, dotted);
            }
        }
    }

    // 2 Swap letters.
    if (!r.chFrom.empty()) {
        std::wstring o;
        for (wchar_t ch : stem) {
            size_t k = r.chFrom.find(ch);
            if (k == std::wstring::npos) o += ch;
            else if (k < r.chTo.size()) o += r.chTo[k];
        }
        stem = o;
    }

    // 3 Name.
    if (r.nmMode == 1) stem.clear();
    else if (r.nmMode == 2) stem = Expand(r.nmFixed, c, false, 0x22);
    else if (r.nmMode == 3) std::reverse(stem.begin(), stem.end());

    // 4 Capitals.
    if (r.csMode) {
        if (r.csMode == 1) stem = Lower(stem);
        else if (r.csMode == 2) stem = Upper(stem);
        else if (r.csMode == 3) stem = TitleCase(stem);
        else stem = SentenceCase(stem);
        stem = PutBack(stem, r.csExcept);
    }

    // 5 Remove.
    if (r.rmFrom > 0 && r.rmCount > 0 && (size_t)r.rmFrom <= stem.size()) stem.erase(r.rmFrom - 1, r.rmCount);
    if (r.rmFirst) stem.erase(0, std::min<size_t>(r.rmFirst, stem.size()));
    if (r.rmLast) stem.erase(stem.size() - std::min<size_t>(r.rmLast, stem.size()));
    if (!r.rmChars.empty()) {
        std::wstring o;
        for (wchar_t ch : stem)
            if (r.rmChars.find(ch) == std::wstring::npos) o += ch;
        stem = o;
    }
    for (const auto& w : r.rmWords) {
        size_t pos = 0;
        while ((pos = Find(stem, w, pos, false)) != std::wstring::npos) {
            if (WholeAt(stem, pos, w.size())) stem.erase(pos, w.size());
            else pos += w.size();
        }
    }
    if (r.rmDigits || r.rmSymbols) {
        std::wstring o;
        for (wchar_t ch : stem) {
            if (r.rmDigits && ch >= L'0' && ch <= L'9') continue;
            if (r.rmSymbols && ch != L' ' && !IsCharAlphaNumericW(ch)) continue;
            o += ch;
        }
        stem = o;
    }
    if (r.rmAccents) stem = DropAccents(stem);
    if (r.rmCrop && !r.rmCropText.empty()) {
        size_t at = Find(stem, r.rmCropText, 0, false);
        if (at != std::wstring::npos) stem = r.rmCrop == 1 ? stem.substr(at) : stem.substr(0, at + r.rmCropText.size());
    }
    if (r.rmDouble) {
        std::wstring o;
        for (wchar_t ch : stem)
            if (!(ch == L' ' && !o.empty() && o.back() == L' ')) o += ch;
        stem = o;
    }
    if (r.rmTrim) stem = Trim(stem);

    // 6 Move.
    if (r.mvMode && r.mvCount > 0 && (size_t)r.mvCount < stem.size()) {
        if (r.mvMode == 1) stem = stem.substr(r.mvCount) + r.mvSep + stem.substr(0, r.mvCount);
        else stem = stem.substr(stem.size() - r.mvCount) + r.mvSep + stem.substr(0, stem.size() - r.mvCount);
    }

    // 7 Add.
    if (!r.addInsert.empty()) {
        size_t at = std::min<size_t>(r.addAt, stem.size());
        if (r.addFromEnd) at = stem.size() - at;
        stem.insert(at, Expand(r.addInsert, c, false, 0x33));
    }
    if (!r.addPrefix.empty()) stem = Expand(r.addPrefix, c, false, 0x44) + stem;
    if (!r.addSuffix.empty()) stem += Expand(r.addSuffix, c, false, 0x55);
    if (r.addWordSpace) {
        std::wstring o;
        for (size_t i = 0; i < stem.size(); i++) {
            wchar_t ch = stem[i];
            if (i > 0 && IsCharUpperW(ch) && IsCharLowerW(stem[i - 1])) o += L' ';
            o += ch;
        }
        stem = o;
    }

    // 8 Date.
    if (r.dtMode) {
        std::wstring d = FormatDate(r.dtFormat, r.dtWhich == 3 ? r.now : LocalTime(DateOf(it, r.dtWhich)));
        stem = r.dtMode == 1 ? d + r.dtSep + stem : stem + r.dtSep + d;
    }

    // 9 Folder name.
    if (r.fdMode) {
        std::vector<std::wstring> parts;
        std::wstring cur;
        for (wchar_t ch : it.dir) {
            if (ch == L'\\' || ch == L'/') {
                if (!cur.empty()) parts.push_back(cur);
                cur.clear();
            } else {
                cur += ch;
            }
        }
        if (!cur.empty()) parts.push_back(cur);
        if (!parts.empty() && parts[0].size() == 2 && parts[0][1] == L':') parts.erase(parts.begin());
        size_t take = std::min<size_t>(r.fdLevels, parts.size());
        std::wstring f;
        for (size_t i = parts.size() - take; i < parts.size(); i++) f += (f.empty() ? L"" : r.fdSep) + parts[i];
        if (!f.empty()) stem = r.fdMode == 1 ? f + r.fdSep + stem : stem + r.fdSep + f;
    }

    // 10 Number.
    if (r.numMode) {
        long long n = r.numStart + (long long)(r.numRestart ? folderIdx : idx) * r.numStep;
        std::wstring t = NumberText(r, n);
        if (r.numMode == 1) stem = t + r.numSep + stem;
        else if (r.numMode == 2) stem = stem + r.numSep + t;
        else if (r.numMode == 3) stem.insert(std::min<size_t>(r.numAt, stem.size()), t);
        else stem = t;
    }

    // 11 Extension.
    if (!it.isDir && r.extMode) {
        if (r.extMode == 1) ext = Lower(ext);
        else if (r.extMode == 2) ext = Upper(ext);
        else if (r.extMode == 3) {
            ext = r.extFixed;
            dotted = !ext.empty();
        } else if (r.extMode == 4) {
            if (!r.extFixed.empty()) {
                if (dotted) stem += L"." + ext;
                ext = r.extFixed;
                dotted = true;
            }
        } else {
            ext.clear();
            dotted = false;
        }
    }

    it.newName = dotted ? stem + L"." + ext : stem;
}

}  // namespace bru

// ---- The file list, the rename run and undo -------------------------------------------------------------------------
// Renames go in two steps (each file to a short temporary name, then to its new name) so names can swap places and a
// half-done run never leaves two files fighting for one name. Before anything moves, every planned move is written to
// an undo record under %LOCALAPPDATA%\Seamless Bulk Rename\undo, so even a crash mid-run can be undone.

namespace bru {

constexpr size_t kMaxItems = 50000;

struct List {
    std::vector<Item> items;
    std::set<std::wstring> seen;  // lowercase paths already in the list
    std::vector<int> view;        // item indices in list order
    int nextOrder = 0;
};

struct Counts {
    int total = 0, changing = 0, problems = 0;
};

struct FileRules {
    std::vector<std::wstring> include;
    bool files = true, folders = false, subfolders = false, hidden = false;
    int sort = 0;  // natural, name, modified, created, size, type, added
    bool desc = false;
};

static FileRules ReadFileRules(const Getter& g) {
    FileRules f;
    std::wstring inc = g(L"f.include");
    size_t pos = 0;
    while (pos <= inc.size()) {
        size_t semi = inc.find(L';', pos);
        std::wstring part = Trim(inc.substr(pos, semi == std::wstring::npos ? std::wstring::npos : semi - pos));
        if (!part.empty()) f.include.push_back(part);
        if (semi == std::wstring::npos) break;
        pos = semi + 1;
    }
    f.files = Truthy(g(L"f.files"));
    f.folders = Truthy(g(L"f.folders"));
    f.subfolders = Truthy(g(L"f.subfolders"));
    f.hidden = Truthy(g(L"f.hidden"));
    f.sort = Pick(g(L"f.sort"), {L"natural", L"name", L"modified", L"created", L"size", L"type", L"added"});
    f.desc = Truthy(g(L"f.sortDesc"));
    return f;
}

static std::wstring LowerPath(const std::wstring& p) {
    std::wstring s = p;
    if (!s.empty()) CharLowerBuffW(s.data(), (DWORD)s.size());
    return s;
}

// Adds the \\?\ start Windows needs for paths of 248 characters and more.
static std::wstring Long(const std::wstring& p) {
    if (p.size() < 248 || p.rfind(L"\\\\?\\", 0) == 0) return p;
    if (p.rfind(L"\\\\", 0) == 0) return L"\\\\?\\UNC\\" + p.substr(2);
    return L"\\\\?\\" + p;
}

static std::wstring DirOf(const std::wstring& path) {
    size_t s = path.find_last_of(L"\\/");
    if (s == std::wstring::npos) return {};
    std::wstring d = path.substr(0, s);
    if (d.size() == 2 && d[1] == L':') d += L'\\';
    return d;
}

static std::wstring JoinPath(const std::wstring& dir, const std::wstring& name) {
    if (dir.empty()) return name;
    return dir.back() == L'\\' ? dir + name : dir + L"\\" + name;
}

static bool AddOne(List& L, const std::wstring& path, const WIN32_FILE_ATTRIBUTE_DATA& a) {
    if (L.items.size() >= kMaxItems) return false;
    std::wstring key = LowerPath(path);
    if (!L.seen.insert(key).second) return true;
    Item it;
    it.path = path;
    it.dir = DirOf(path);
    it.name = PathFindFileNameW(path.c_str());
    it.isDir = (a.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    it.created = a.ftCreationTime;
    it.modified = a.ftLastWriteTime;
    it.size = ((ULONGLONG)a.nFileSizeHigh << 32) | a.nFileSizeLow;
    it.attrs = a.dwFileAttributes;
    it.order = L.nextOrder++;
    L.items.push_back(std::move(it));
    L.view.push_back((int)L.items.size() - 1);
    return true;
}

static bool Matches(const FileRules& f, PCWSTR name) {
    if (f.include.empty()) return true;
    for (const auto& p : f.include)
        if (PathMatchSpecW(name, p.c_str())) return true;
    return false;
}

static void Walk(List& L, const std::wstring& dir, const FileRules& f, int depth) {
    if (depth > 64 || L.items.size() >= kMaxItems) return;
    WIN32_FIND_DATAW fd;
    HANDLE h = FindFirstFileExW(Long(JoinPath(dir, L"*")).c_str(), FindExInfoBasic, &fd, FindExSearchNameMatch,
                                nullptr, FIND_FIRST_EX_LARGE_FETCH);
    if (h == INVALID_HANDLE_VALUE) return;
    std::vector<std::wstring> sub;
    do {
        if (!wcscmp(fd.cFileName, L".") || !wcscmp(fd.cFileName, L"..")) continue;
        if (!f.hidden && (fd.dwFileAttributes & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM))) continue;
        std::wstring path = JoinPath(dir, fd.cFileName);
        WIN32_FILE_ATTRIBUTE_DATA a{fd.dwFileAttributes, fd.ftCreationTime, fd.ftLastAccessTime, fd.ftLastWriteTime,
                                    fd.nFileSizeHigh, fd.nFileSizeLow};
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (f.folders && !AddOne(L, path, a)) break;
            if (f.subfolders && !(fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)) sub.push_back(path);
        } else if (f.files && Matches(f, fd.cFileName)) {
            if (!AddOne(L, path, a)) break;
        }
    } while (FindNextFileW(h, &fd));
    FindClose(h);
    for (const auto& s : sub) Walk(L, s, f, depth + 1);
}

// Adds files and folders. With expand, a folder brings in what is inside it (by the Files page) instead of itself.
static void AddPaths(List& L, const std::vector<std::wstring>& paths, bool expand, const FileRules& f) {
    for (const auto& raw : paths) {
        std::wstring p = raw;
        while (p.size() > 3 && (p.back() == L'\\' || p.back() == L'/')) p.pop_back();
        WIN32_FILE_ATTRIBUTE_DATA a{};
        if (!GetFileAttributesExW(Long(p).c_str(), GetFileExInfoStandard, &a)) continue;
        if ((a.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (expand || p.size() <= 3)) Walk(L, p, f, 0);
        else AddOne(L, p, a);
        if (L.items.size() >= kMaxItems) break;
    }
}

static int CompareFt(const FILETIME& a, const FILETIME& b) { return CompareFileTime(&a, &b); }

static void Sort(List& L, int sort, bool desc) {
    auto& it = L.items;
    auto ext = [](const Item& x) -> PCWSTR { return x.isDir ? L"" : PathFindExtensionW(x.name.c_str()); };
    std::stable_sort(L.view.begin(), L.view.end(), [&](int a, int b) {
        const Item &x = it[a], &y = it[b];
        int c = 0;
        switch (sort) {
            case 0: c = StrCmpLogicalW(x.name.c_str(), y.name.c_str()); break;
            case 1: c = CompareStringOrdinal(x.name.c_str(), -1, y.name.c_str(), -1, TRUE) - 2; break;
            case 2: c = CompareFt(x.modified, y.modified); break;
            case 3: c = CompareFt(x.created, y.created); break;
            case 4: c = x.size < y.size ? -1 : x.size > y.size ? 1 : 0; break;
            case 5:
                c = CompareStringOrdinal(ext(x), -1, ext(y), -1, TRUE) - 2;
                if (!c) c = StrCmpLogicalW(x.name.c_str(), y.name.c_str());
                break;
            default: c = x.order - y.order; break;
        }
        if (!c && sort != 6) c = x.order - y.order;
        return c < 0;
    });
    if (desc) std::reverse(L.view.begin(), L.view.end());
}

static void RemoveItems(List& L, const std::vector<int>& drop) {
    if (drop.empty()) return;
    std::vector<char> gone(L.items.size(), 0);
    for (int i : drop)
        if (i >= 0 && (size_t)i < gone.size()) gone[i] = 1;
    std::vector<Item> keep;
    for (size_t i = 0; i < L.items.size(); i++)
        if (!gone[i]) keep.push_back(std::move(L.items[i]));
    L.items = std::move(keep);
    L.seen.clear();
    L.view.clear();
    for (size_t i = 0; i < L.items.size(); i++) {
        L.seen.insert(LowerPath(L.items[i].path));
        L.view.push_back((int)i);
    }
}

// ---- Checking the new names -----------------------------------------------------------------------------------------

static bool ReservedName(const std::wstring& name) {
    std::wstring stem = Upper(name.substr(0, name.find(L'.')));
    while (!stem.empty() && stem.back() == L' ') stem.pop_back();
    static const PCWSTR kFixed[] = {L"CON", L"PRN", L"AUX", L"NUL"};
    for (PCWSTR r : kFixed)
        if (stem == r) return true;
    if (stem.size() == 4 && (stem.rfind(L"COM", 0) == 0 || stem.rfind(L"LPT", 0) == 0) && stem[3] >= L'1' &&
        stem[3] <= L'9')
        return true;
    return false;
}

static std::wstring NameProblem(const std::wstring& n) {
    if (n.empty()) return L"The new name is empty";
    for (wchar_t c : n)
        if (c < 32 || wcschr(L"<>:\"/\\|?*", c)) return L"Has a character Windows can't use in a name";
    if (n.back() == L'.' || n.back() == L' ') return L"Can't end with a dot or a space";
    if (ReservedName(n)) return L"Windows keeps this name for itself";
    if (n.size() > 255) return L"The name is too long";
    return {};
}

struct Extras {
    bool fdt = false, marks = false, copy = false;
    std::wstring copyDir;
};

static Extras ReadExtras(const Getter& g) {
    Extras e;
    e.fdt = Truthy(g(L"fdt.on"));
    e.marks = g(L"at.readOnly") != L"keep" || g(L"at.hidden") != L"keep" || g(L"at.archive") != L"keep";
    e.copy = Truthy(g(L"cp.on"));
    e.copyDir = Trim(g(L"cp.folder"));
    while (e.copyDir.size() > 3 && e.copyDir.back() == L'\\') e.copyDir.pop_back();
    return e;
}

static std::wstring TargetOf(const Item& it, const Extras& e) {
    return JoinPath(e.copy && !e.copyDir.empty() ? e.copyDir : it.dir, it.newName);
}

// Runs the rules over the whole list in list order and checks every new name. Unticked files stay as they are.
static Counts Recompute(List& L, const Getter& g, uint32_t seed) {
    Rules r = ReadRules(g, seed);
    Extras e = ReadExtras(g);
    std::unordered_map<std::wstring, int> perFolder;
    int idx = 0;
    for (int i : L.view) {
        Item& it = L.items[i];
        if (!it.checked) {
            it.newName = it.name;
            it.error.clear();
            continue;
        }
        int& fi = perFolder[LowerPath(it.dir)];
        Compute(it, idx++, fi++, r);
    }
    std::unordered_map<std::wstring, int> originals, targets;
    for (size_t i = 0; i < L.items.size(); i++) originals[LowerPath(L.items[i].path)] = (int)i;
    for (int i : L.view) {
        Item& it = L.items[i];
        if (!it.checked) continue;
        if (it.error.empty()) it.error = NameProblem(it.newName);
        if (it.error.empty()) {
            int& n = targets[LowerPath(TargetOf(it, e))];
            n++;
        }
    }
    if (e.copy && !e.copyDir.empty() && GetFileAttributesW(Long(e.copyDir).c_str()) == INVALID_FILE_ATTRIBUTES)
        for (int i : L.view)
            if (L.items[i].checked && L.items[i].error.empty()) L.items[i].error = L"The copy folder isn't there";
    Counts c;
    for (int i : L.view) {
        Item& it = L.items[i];
        c.total++;
        if (!it.checked) {
            it.state = 0;
            continue;
        }
        bool renamed = it.newName != it.name;
        if (it.error.empty() && (renamed || e.copy)) {
            std::wstring target = TargetOf(it, e);
            std::wstring key = LowerPath(target);
            if (targets[key] > 1) {
                it.error = L"Two files would get this name";
            } else if (e.copy) {
                if (key == LowerPath(it.path)) it.error = L"The copy would land on the file itself";
                else if (GetFileAttributesW(Long(target).c_str()) != INVALID_FILE_ATTRIBUTES)
                    it.error = L"A file with this name is already there";
            } else if (key != LowerPath(it.path)) {
                auto o = originals.find(key);
                if (o != originals.end()) {
                    const Item& other = L.items[o->second];
                    if (!other.checked || other.newName == other.name)
                        it.error = L"Another file in the list keeps this name";
                } else if (GetFileAttributesW(Long(target).c_str()) != INVALID_FILE_ATTRIBUTES) {
                    it.error = L"A file with this name is already there";
                }
            }
        }
        if (!it.error.empty()) {
            it.state = 2;
            c.problems++;
        } else if (renamed || e.copy || e.fdt || e.marks) {
            it.state = 1;
            c.changing++;
        } else {
            it.state = 0;
        }
    }
    return c;
}

// ---- The undo record ------------------------------------------------------------------------------------------------

static std::wstring UndoDir() {
    PWSTR base = nullptr;
    std::wstring d;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &base)) && base) {
        d = std::wstring(base) + L"\\Seamless Bulk Rename\\undo";
        CoTaskMemFree(base);
    }
    return d;
}

static std::vector<std::wstring> Journals() {
    std::vector<std::wstring> out;
    std::wstring dir = UndoDir();
    if (dir.empty()) return out;
    WIN32_FIND_DATAW fd;
    HANDLE h = FindFirstFileW((dir + L"\\run-*.tsv").c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE) return out;
    do out.push_back(dir + L"\\" + fd.cFileName);
    while (FindNextFileW(h, &fd));
    FindClose(h);
    std::sort(out.begin(), out.end());
    return out;
}

static bool CanUndo() { return !Journals().empty(); }

static void TrimJournals(int keep) {
    auto all = Journals();
    while ((int)all.size() > std::max(1, keep)) {
        DeleteFileW(all.front().c_str());
        all.erase(all.begin());
    }
}

static std::string Utf8(const std::wstring& s) {
    if (s.empty()) return {};
    int n = WideCharToMultiByte(CP_UTF8, 0, s.c_str(), (int)s.size(), nullptr, 0, nullptr, nullptr);
    std::string o((size_t)n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, s.c_str(), (int)s.size(), o.data(), n, nullptr, nullptr);
    return o;
}

static std::wstring Wide(const std::string& s) {
    if (s.empty()) return {};
    int n = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), nullptr, 0);
    std::wstring o((size_t)n, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), o.data(), n);
    return o;
}

static ULONGLONG FtNum(const FILETIME& f) { return ((ULONGLONG)f.dwHighDateTime << 32) | f.dwLowDateTime; }
static FILETIME NumFt(ULONGLONG v) { return FILETIME{(DWORD)v, (DWORD)(v >> 32)}; }

struct Job {
    std::wstring from, temp, to;
    bool isDir = false;
    FILETIME oldC{}, oldM{};
    DWORD oldAttrs = 0;
    bool setTime = false;
    FILETIME setFt{};
    bool ok = false;
    std::wstring error;
};

struct Plan {
    std::vector<Job> jobs;
    bool copy = false;
    int fdtWhich = 0;  // modified, created, both
    int marks[3] = {0, 0, 0};  // read-only, hidden, archive: keep, set, clear
    int undoLevels = 10;
    std::wstring runId;
};

struct Result {
    bool undo = false;
    int done = 0, failed = 0;
    std::vector<std::pair<std::wstring, std::wstring>> moved;  // old path, new path
    std::vector<std::pair<std::wstring, std::wstring>> errors;  // path, why
};

static bool WriteJournal(const std::wstring& path, const Plan& p, bool onlyOk) {
    std::string text;
    int count = 0;
    std::string body;
    for (const Job& j : p.jobs) {
        if (onlyOk && !j.ok) continue;
        count++;
        body += Utf8(j.from) + "\t" + Utf8(j.temp) + "\t" + Utf8(j.to) + "\t" + std::to_string(FtNum(j.oldC)) + "\t" +
                std::to_string(FtNum(j.oldM)) + "\t" + std::to_string(j.oldAttrs) + "\n";
    }
    text = "SBR1\t" + std::to_string(count) + "\t" + (p.copy ? "1" : "0") + "\n" + body;
    std::wstring tmp = path + L".part";
    HANDLE h = CreateFileW(tmp.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;
    DWORD w = 0;
    bool ok = WriteFile(h, text.data(), (DWORD)text.size(), &w, nullptr) && w == text.size();
    FlushFileBuffers(h);
    CloseHandle(h);
    if (!ok) {
        DeleteFileW(tmp.c_str());
        return false;
    }
    return MoveFileExW(tmp.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != FALSE;
}

static std::wstring LastErrorText(DWORD e) {
    switch (e) {
        case ERROR_ACCESS_DENIED: return L"Windows said no. The file may be open or protected";
        case ERROR_SHARING_VIOLATION: return L"Another app has the file open";
        case ERROR_ALREADY_EXISTS:
        case ERROR_FILE_EXISTS: return L"A file with this name is already there";
        case ERROR_FILE_NOT_FOUND:
        case ERROR_PATH_NOT_FOUND: return L"The file is gone";
        case ERROR_DISK_FULL: return L"The drive is full";
        case ERROR_FILENAME_EXCED_RANGE: return L"The path is too long";
    }
    WCHAR buf[256] = {};
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, e, 0, buf, 256, nullptr);
    std::wstring s = Trim(buf);
    while (!s.empty() && s.back() == L'.') s.pop_back();
    return s.empty() ? L"It didn't work" : s;
}

static void SetTimes(const std::wstring& path, bool dir, const FILETIME* c, const FILETIME* m) {
    HANDLE h = CreateFileW(Long(path).c_str(), FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                           nullptr, OPEN_EXISTING, dir ? FILE_FLAG_BACKUP_SEMANTICS : 0, nullptr);
    if (h == INVALID_HANDLE_VALUE) return;
    SetFileTime(h, c, nullptr, m);
    CloseHandle(h);
}

static void ApplyMarks(const std::wstring& path, const int marks[3]) {
    if (!marks[0] && !marks[1] && !marks[2]) return;
    DWORD a = GetFileAttributesW(Long(path).c_str());
    if (a == INVALID_FILE_ATTRIBUTES) return;
    DWORD n = a;
    const DWORD bits[3] = {FILE_ATTRIBUTE_READONLY, FILE_ATTRIBUTE_HIDDEN, FILE_ATTRIBUTE_ARCHIVE};
    for (int i = 0; i < 3; i++) {
        if (marks[i] == 1) n |= bits[i];
        else if (marks[i] == 2) n &= ~bits[i];
    }
    if (n != a) SetFileAttributesW(Long(path).c_str(), n & ~FILE_ATTRIBUTE_DIRECTORY);
}

static std::wstring RunId() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    WCHAR buf[64];
    swprintf(buf, 64, L"%04u%02u%02u-%02u%02u%02u-%03u", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute,
             st.wSecond, st.wMilliseconds);
    return buf;
}

static bool ParseWhen(const std::wstring& s, FILETIME& out) {
    SYSTEMTIME st{};
    unsigned y = 0, mo = 0, d = 0, h = 0, mi = 0;
    int n = swscanf(s.c_str(), L"%u-%u-%u %u:%u", &y, &mo, &d, &h, &mi);
    if (n < 3 || y < 1601 || y > 30827 || mo < 1 || mo > 12 || d < 1 || d > 31 || h > 23 || mi > 59) return false;
    st.wYear = (WORD)y;
    st.wMonth = (WORD)mo;
    st.wDay = (WORD)d;
    st.wHour = (WORD)h;
    st.wMinute = (WORD)mi;
    SYSTEMTIME utc{};
    if (!TzSpecificLocalTimeToSystemTime(nullptr, &st, &utc)) return false;
    return SystemTimeToFileTime(&utc, &out) != FALSE;
}

// Builds the moves for every ticked file that changes and has no problem. Runs where the list lives.
static Plan* BuildPlan(List& L, const Getter& g) {
    Extras e = ReadExtras(g);
    auto* p = new Plan;
    p->copy = e.copy;
    p->runId = RunId();
    p->undoLevels = (int)Num(g(L"undoLevels"), 1, 20, 10);
    p->fdtWhich = Pick(g(L"fdt.which"), {L"modified", L"created", L"both"});
    int fdtMode = Pick(g(L"fdt.mode"), {L"now", L"fixed", L"taken"});
    FILETIME fixed{}, now{};
    bool fixedOk = ParseWhen(g(L"fdt.value"), fixed);
    GetSystemTimeAsFileTime(&now);
    PCWSTR markKeys[3] = {L"at.readOnly", L"at.hidden", L"at.archive"};
    for (int i = 0; i < 3; i++) p->marks[i] = Pick(g(markKeys[i]), {L"keep", L"set", L"clear"});
    int n = 0;
    for (int i : L.view) {
        Item& it = L.items[i];
        if (!it.checked || it.state != 1) continue;
        Job j;
        j.from = it.path;
        j.to = TargetOf(it, e);
        j.isDir = it.isDir;
        j.oldC = it.created;
        j.oldM = it.modified;
        j.oldAttrs = it.attrs;
        if (!e.copy && j.from != j.to) j.temp = JoinPath(it.dir, L".sbr-" + p->runId + L"-" + std::to_wstring(n));
        if (e.fdt) {
            if (fdtMode == 0) j.setFt = now, j.setTime = true;
            else if (fdtMode == 1) j.setFt = fixed, j.setTime = fixedOk;
            else {
                ReadTags(it);
                j.setFt = it.takenFt;
                j.setTime = it.hasTaken;
            }
        }
        p->jobs.push_back(std::move(j));
        n++;
    }
    return p;
}

// Does the renames. Runs on its own thread; the result goes back to the window.
static Result* RunPlan(Plan& p) {
    auto* res = new Result;
    std::wstring dir = UndoDir();
    std::wstring journal;
    if (!dir.empty()) {
        SHCreateDirectoryExW(nullptr, dir.c_str(), nullptr);
        journal = dir + L"\\run-" + p.runId + L".tsv";
        if (!WriteJournal(journal, p, false)) journal.clear();
    }
    if (journal.empty()) {
        for (Job& j : p.jobs) res->errors.push_back({j.from, L"The undo record couldn't be saved, so nothing moved"});
        res->failed = (int)p.jobs.size();
        return res;
    }
    if (p.copy) {
        for (Job& j : p.jobs) {
            if (j.isDir) {
                j.error = L"Folders can't be copied";
                continue;
            }
            if (!CopyFileExW(Long(j.from).c_str(), Long(j.to).c_str(), nullptr, nullptr, nullptr,
                             COPY_FILE_FAIL_IF_EXISTS))
                j.error = LastErrorText(GetLastError());
            else
                j.ok = true;
        }
    } else {
        // Step 1: each file to its temporary name.
        for (Job& j : p.jobs) {
            if (j.temp.empty()) continue;
            if (!MoveFileExW(Long(j.from).c_str(), Long(j.temp).c_str(), 0)) j.error = LastErrorText(GetLastError());
        }
        // Step 2: from the temporary name to the new one, or back if that fails.
        for (Job& j : p.jobs) {
            if (!j.error.empty()) continue;
            if (j.temp.empty()) {
                j.ok = true;
                continue;
            }
            if (MoveFileExW(Long(j.temp).c_str(), Long(j.to).c_str(), 0)) {
                j.ok = true;
            } else {
                j.error = LastErrorText(GetLastError());
                MoveFileExW(Long(j.temp).c_str(), Long(j.from).c_str(), 0);
            }
        }
    }
    for (Job& j : p.jobs) {
        if (!j.ok) {
            res->failed++;
            res->errors.push_back({j.from, j.error});
            continue;
        }
        res->done++;
        if (j.setTime)
            SetTimes(j.to, j.isDir, p.fdtWhich != 0 ? &j.setFt : nullptr, p.fdtWhich != 1 ? &j.setFt : nullptr);
        ApplyMarks(j.to, p.marks);
        if (!p.copy) res->moved.push_back({j.from, j.to});
    }
    if (res->done) WriteJournal(journal, p, true);
    else DeleteFileW(journal.c_str());
    TrimJournals(p.undoLevels);
    return res;
}

static std::vector<std::wstring> SplitTabs(const std::wstring& line) {
    std::vector<std::wstring> out;
    size_t pos = 0;
    while (true) {
        size_t t = line.find(L'\t', pos);
        out.push_back(line.substr(pos, t == std::wstring::npos ? std::wstring::npos : t - pos));
        if (t == std::wstring::npos) break;
        pos = t + 1;
    }
    return out;
}

static bool Exists(const std::wstring& p) {
    return !p.empty() && GetFileAttributesW(Long(p).c_str()) != INVALID_FILE_ATTRIBUTES;
}

// Puts the newest run back: renamed files get their old names, dates and marks; copies go to the Recycle Bin.
static Result* RunUndo() {
    auto* res = new Result;
    res->undo = true;
    auto all = Journals();
    if (all.empty()) return res;
    std::wstring journal = all.back();
    std::string raw;
    HANDLE h = CreateFileW(journal.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
    if (h == INVALID_HANDLE_VALUE) return res;
    LARGE_INTEGER sz{};
    GetFileSizeEx(h, &sz);
    if (sz.QuadPart > 0 && sz.QuadPart < 256LL * 1024 * 1024) {
        raw.resize((size_t)sz.QuadPart);
        DWORD got = 0;
        ReadFile(h, raw.data(), (DWORD)raw.size(), &got, nullptr);
        raw.resize(got);
    }
    CloseHandle(h);
    std::wstring text = Wide(raw);
    std::vector<std::wstring> lines;
    size_t pos = 0;
    while (pos < text.size()) {
        size_t nl = text.find(L'\n', pos);
        lines.push_back(text.substr(pos, nl == std::wstring::npos ? std::wstring::npos : nl - pos));
        if (nl == std::wstring::npos) break;
        pos = nl + 1;
    }
    if (lines.empty() || lines[0].rfind(L"SBR1\t", 0) != 0) {
        res->errors.push_back({journal, L"The undo record is damaged"});
        res->failed = 1;
        return res;
    }
    bool copy = SplitTabs(lines[0]).size() > 2 && SplitTabs(lines[0])[2] == L"1";
    struct Back {
        std::wstring orig, spot, temp;
        FILETIME c, m;
        DWORD attrs;
        bool ok = false;
    };
    std::vector<Back> backs;
    for (size_t i = 1; i < lines.size(); i++) {
        auto f = SplitTabs(lines[i]);
        if (f.size() < 6) continue;
        Back b;
        b.orig = f[0];
        b.spot = Exists(f[1]) ? f[1] : f[2];
        b.c = NumFt(_wcstoui64(f[3].c_str(), nullptr, 10));
        b.m = NumFt(_wcstoui64(f[4].c_str(), nullptr, 10));
        b.attrs = (DWORD)wcstoul(f[5].c_str(), nullptr, 10);
        backs.push_back(b);
    }
    if (copy) {
        std::wstring list;
        int n = 0;
        for (auto& b : backs)
            if (Exists(b.spot)) {
                list += b.spot;
                list += L'\0';
                n++;
            }
        if (n) {
            list += L'\0';
            SHFILEOPSTRUCTW op{};
            op.wFunc = FO_DELETE;
            op.pFrom = list.c_str();
            op.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;
            int r = SHFileOperationW(&op);
            if (r == 0 && !op.fAnyOperationsAborted) res->done = n;
            else {
                res->failed = n;
                res->errors.push_back({backs.front().spot, L"The copies couldn't go to the Recycle Bin"});
            }
        }
    } else {
        std::wstring id = RunId();
        int n = 0;
        // Step 1: to a fresh temporary name, so files that swapped names can swap back.
        for (auto& b : backs) {
            if (b.spot == b.orig) {
                b.ok = true;
                continue;
            }
            if (!Exists(b.spot)) {
                res->errors.push_back({b.orig, L"The renamed file is gone"});
                continue;
            }
            if (Exists(b.orig) && LowerPath(b.orig) != LowerPath(b.spot)) {
                res->errors.push_back({b.spot, L"Something new already has the old name"});
                continue;
            }
            b.temp = JoinPath(DirOf(b.spot), L".sbr-u" + id + L"-" + std::to_wstring(n++));
            if (!MoveFileExW(Long(b.spot).c_str(), Long(b.temp).c_str(), 0)) {
                res->errors.push_back({b.spot, LastErrorText(GetLastError())});
                b.temp.clear();
            }
        }
        // Step 2: to the old name.
        for (auto& b : backs) {
            if (b.temp.empty()) continue;
            if (MoveFileExW(Long(b.temp).c_str(), Long(b.orig).c_str(), 0)) {
                b.ok = true;
            } else {
                res->errors.push_back({b.spot, LastErrorText(GetLastError())});
                MoveFileExW(Long(b.temp).c_str(), Long(b.spot).c_str(), 0);
            }
        }
        for (auto& b : backs) {
            if (!b.ok) {
                res->failed++;
                continue;
            }
            res->done++;
            bool dir = (b.attrs & FILE_ATTRIBUTE_DIRECTORY) != 0;
            DWORD now = GetFileAttributesW(Long(b.orig).c_str());
            if (now != INVALID_FILE_ATTRIBUTES && (now & FILE_ATTRIBUTE_READONLY))
                SetFileAttributesW(Long(b.orig).c_str(), now & ~FILE_ATTRIBUTE_READONLY & ~FILE_ATTRIBUTE_DIRECTORY);
            SetTimes(b.orig, dir, &b.c, &b.m);
            DWORD want = b.attrs & ~FILE_ATTRIBUTE_DIRECTORY;
            SetFileAttributesW(Long(b.orig).c_str(), want ? want : FILE_ATTRIBUTE_NORMAL);
            if (b.spot != b.orig) res->moved.push_back({b.spot, b.orig});
        }
    }
    if (!res->failed) DeleteFileW(journal.c_str());
    return res;
}

// ---- Presets --------------------------------------------------------------------------------------------------------
// Stored as "#name" on the first line, then key=value lines.

static std::wstring PresetText(int n) {
    std::vector<WCHAR> buf(32768, 0);
    Wh_GetStringValue((L"preset" + std::to_wstring(n)).c_str(), buf.data(), buf.size());
    return buf.data();
}

static void SavePreset(int n, const std::wstring& name, const std::vector<std::pair<std::wstring, std::wstring>>& kv) {
    std::wstring t = L"#" + name + L"\n";
    for (const auto& [k, v] : kv) t += k + L"=" + v + L"\n";
    Wh_SetStringValue((L"preset" + std::to_wstring(n)).c_str(), t.c_str());
}

static bool LoadPreset(int n, std::wstring& name, std::vector<std::pair<std::wstring, std::wstring>>& kv) {
    std::wstring t = PresetText(n);
    if (t.empty()) return false;
    size_t pos = 0;
    bool first = true;
    while (pos < t.size()) {
        size_t nl = t.find(L'\n', pos);
        std::wstring line = t.substr(pos, nl == std::wstring::npos ? std::wstring::npos : nl - pos);
        pos = nl == std::wstring::npos ? t.size() : nl + 1;
        if (first && !line.empty() && line[0] == L'#') {
            name = line.substr(1);
            first = false;
            continue;
        }
        first = false;
        size_t eq = line.find(L'=');
        if (eq != std::wstring::npos) kv.push_back({line.substr(0, eq), line.substr(eq + 1)});
    }
    return true;
}

}  // namespace bru

// ---- Explorer: the right-click entry and the shortcut ---------------------------------------------------------------
// Runs only inside explorer.exe. Both read what is selected in the folder window (or on the desktop) and send the
// paths to the tool process, which owns the rename window. Nothing here renames anything.

namespace bruex {

static std::atomic<bool> g_menuOn{true};
static HANDLE g_hotThread;
static std::atomic<DWORD> g_hotThreadId;
constexpr UINT WM_APP_HOTKEY_RELOAD = WM_APP + 1;

static bool ClassIs(HWND h, PCWSTR cls) {
    WCHAR buf[64];
    return h && GetClassNameW(h, buf, 64) && !wcscmp(buf, cls);
}

static bool IsShellRoot(HWND root) {
    return ClassIs(root, L"CabinetWClass") || ClassIs(root, L"Progman") || ClassIs(root, L"WorkerW");
}

// What the view has selected, or the folder itself when nothing is. Returns 'S' or 'F', or 0 for nothing usable.
static wchar_t ReadView(IShellBrowser* sb, std::vector<std::wstring>& out) {
    if (!sb) return 0;
    wchar_t kind = 0;
    IShellView* sv = nullptr;
    if (FAILED(sb->QueryActiveShellView(&sv)) || !sv) return 0;
    IFolderView2* fv = nullptr;
    if (SUCCEEDED(sv->QueryInterface(IID_PPV_ARGS(&fv))) && fv) {
        IShellItemArray* sel = nullptr;
        DWORD count = 0;
        if (SUCCEEDED(fv->GetSelection(FALSE, &sel)) && sel && SUCCEEDED(sel->GetCount(&count))) {
            for (DWORD i = 0; i < count; i++) {
                IShellItem* si = nullptr;
                if (FAILED(sel->GetItemAt(i, &si)) || !si) continue;
                PWSTR p = nullptr;
                if (SUCCEEDED(si->GetDisplayName(SIGDN_FILESYSPATH, &p)) && p) {
                    out.push_back(p);
                    CoTaskMemFree(p);
                }
                si->Release();
            }
        }
        if (sel) sel->Release();
        if (!out.empty()) {
            kind = L'S';
        } else {
            IPersistFolder2* pf = nullptr;
            if (SUCCEEDED(fv->GetFolder(IID_PPV_ARGS(&pf))) && pf) {
                PIDLIST_ABSOLUTE pidl = nullptr;
                if (SUCCEEDED(pf->GetCurFolder(&pidl)) && pidl) {
                    WCHAR path[MAX_PATH * 4] = {};
                    if (SHGetPathFromIDListEx(pidl, path, ARRAYSIZE(path), GPFIDL_DEFAULT) && *path) {
                        out.push_back(path);
                        kind = L'F';
                    }
                    CoTaskMemFree(pidl);
                }
                pf->Release();
            }
        }
        fv->Release();
    }
    sv->Release();
    return kind;
}

struct SendJob {
    wchar_t kind;
    std::vector<std::wstring> paths;
};

static DWORD WINAPI SendThread(void* p) {
    std::unique_ptr<SendJob> job((SendJob*)p);
    HWND tray = FindWindowW(kBruTrayClass, nullptr);
    if (!tray) {
        Wh_Log(L"The rename window isn't running yet");
        return 0;
    }
    std::wstring blob(1, job->kind);
    for (const auto& s : job->paths) {
        blob += s;
        blob += L'\0';
    }
    DWORD pid = 0;
    GetWindowThreadProcessId(tray, &pid);
    if (pid) AllowSetForegroundWindow(pid);
    COPYDATASTRUCT cd{kBruCopyPaths, (DWORD)(blob.size() * sizeof(WCHAR)), (void*)blob.data()};
    DWORD_PTR r = 0;
    SendMessageTimeoutW(tray, WM_COPYDATA, 0, (LPARAM)&cd, SMTO_ABORTIFHUNG, 2000, &r);
    return 0;
}

// Hands the paths to a short-lived thread so Explorer's own window never waits on the tool process.
static void Send(wchar_t kind, std::vector<std::wstring>&& paths) {
    if (!kind || paths.empty()) return;
    auto* job = new SendJob{kind, std::move(paths)};
    HANDLE t = CreateThread(nullptr, 0, SendThread, job, 0, nullptr);
    if (t) CloseHandle(t);
    else delete job;
}

// ---- The right-click entry ------------------------------------------------------------------------------------------

using TrackPopupMenu_t = BOOL(WINAPI*)(HMENU, UINT, int, int, int, HWND, const RECT*);
using TrackPopupMenuEx_t = BOOL(WINAPI*)(HMENU, UINT, int, int, HWND, LPTPMPARAMS);
static TrackPopupMenu_t TrackPopupMenu_Orig;
static TrackPopupMenuEx_t TrackPopupMenuEx_Orig;
static thread_local bool t_inMenu;

static std::wstring PlainText(HMENU m, UINT pos) {
    WCHAR buf[128] = {};
    MENUITEMINFOW mi{sizeof(mi)};
    mi.fMask = MIIM_STRING | MIIM_FTYPE;
    mi.dwTypeData = buf;
    mi.cch = ARRAYSIZE(buf) - 1;
    if (!GetMenuItemInfoW(m, pos, TRUE, &mi) || (mi.fType & MFT_SEPARATOR)) return {};
    std::wstring s;
    for (PCWSTR p = buf; *p && *p != L'\t'; p++)
        if (*p != L'&') s += *p;
    return s;
}

static bool IdUsed(HMENU m, UINT id, int depth = 0) {
    if (depth > 6) return false;
    int n = GetMenuItemCount(m);
    for (int i = 0; i < n; i++) {
        if (GetMenuItemID(m, i) == id) return true;
        if (HMENU sub = GetSubMenu(m, i))
            if (IdUsed(sub, id, depth + 1)) return true;
    }
    return false;
}

// Returns where Rename sits when this is a file menu in a folder window or on the desktop, else -1.
static int RenamePos(HMENU m, HWND owner) {
    if (!g_menuOn || !m || !IsShellRoot(GetAncestor(owner, GA_ROOT))) return -1;
    int n = GetMenuItemCount(m), rename = -1;
    bool props = false;
    for (int i = 0; i < n; i++) {
        std::wstring t = PlainText(m, (UINT)i);
        if (t == L"Rename") rename = i;
        else if (t == L"Properties") props = true;
    }
    return props ? rename : -1;
}

static IShellBrowser* BrowserOf(HWND h) {
    for (HWND w = h; w; w = GetParent(w)) {
        DWORD_PTR r = 0;
        if (SendMessageTimeoutW(w, WM_USER + 7, 0, 0, SMTO_ABORTIFHUNG, 500, &r) && r) return (IShellBrowser*)r;
        if (GetWindowLongPtrW(w, GWL_STYLE) & WS_CHILD) continue;
        break;
    }
    return nullptr;
}

static std::wstring_view kEntry = L"Bulk rename";

template <class F>
static BOOL Around(HMENU m, UINT flags, HWND owner, F call) {
    int pos = t_inMenu ? -1 : RenamePos(m, owner);
    if (pos < 0) return call(flags);
    UINT id = 0x7FF0;
    while (id > 0x7000 && IdUsed(m, id)) id--;
    if (!InsertMenuW(m, (UINT)pos + 1, MF_BYPOSITION | MF_STRING, id, kEntry.data())) return call(flags);
    t_inMenu = true;
    BOOL r = call(flags | TPM_RETURNCMD);
    t_inMenu = false;
    DeleteMenu(m, id, MF_BYCOMMAND);
    if ((UINT)r == id) {
        std::vector<std::wstring> paths;
        wchar_t kind = ReadView(BrowserOf(owner), paths);
        Send(kind, std::move(paths));
        return (flags & TPM_RETURNCMD) ? 0 : TRUE;
    }
    if (flags & TPM_RETURNCMD) return r;
    if (r && !(flags & TPM_NONOTIFY)) PostMessageW(owner, WM_COMMAND, MAKEWPARAM((UINT)r, 0), 0);
    return r ? TRUE : FALSE;
}

static BOOL WINAPI TrackPopupMenu_Hook(HMENU m, UINT flags, int x, int y, int res, HWND owner, const RECT* rc) {
    return Around(m, flags, owner, [&](UINT f) { return TrackPopupMenu_Orig(m, f, x, y, res, owner, rc); });
}

static BOOL WINAPI TrackPopupMenuEx_Hook(HMENU m, UINT flags, int x, int y, HWND owner, LPTPMPARAMS tpm) {
    return Around(m, flags, owner, [&](UINT f) { return TrackPopupMenuEx_Orig(m, f, x, y, owner, tpm); });
}

static bool HookMenus() {
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    void* a = user32 ? (void*)GetProcAddress(user32, "TrackPopupMenu") : nullptr;
    void* b = user32 ? (void*)GetProcAddress(user32, "TrackPopupMenuEx") : nullptr;
    bool ok = a && b && Wh_SetFunctionHook(a, (void*)TrackPopupMenu_Hook, (void**)&TrackPopupMenu_Orig) &&
              Wh_SetFunctionHook(b, (void*)TrackPopupMenuEx_Hook, (void**)&TrackPopupMenuEx_Orig);
    if (!ok) Wh_Log(L"Couldn't hook the right-click menu");
    return ok;
}

// ---- The shortcut ---------------------------------------------------------------------------------------------------
// Registered only while one of this Explorer's own windows is in front, so the keys stay free in every other app.

static UINT g_hotMods, g_hotVk;
static bool g_hotOn;

static bool OwnShellWindow(HWND fg) {
    if (!fg || !IsShellRoot(fg)) return false;
    DWORD pid = 0;
    GetWindowThreadProcessId(fg, &pid);
    return pid == GetCurrentProcessId();
}

static void ReadHotkey() {
    if (!Hotkey_Parse(SettingString(L"renameHotkey"), g_hotMods, g_hotVk)) g_hotMods = g_hotVk = 0;
}

static void SyncHotkey(HWND fg) {
    bool want = g_hotVk && OwnShellWindow(fg);
    if (want == g_hotOn) return;
    if (want) {
        g_hotOn = RegisterHotKey(nullptr, 1, g_hotMods | MOD_NOREPEAT, g_hotVk) != FALSE;
        if (!g_hotOn) Wh_Log(L"Another app already uses the shortcut");
    } else {
        UnregisterHotKey(nullptr, 1);
        g_hotOn = false;
    }
}

static void CALLBACK OnForeground(HWINEVENTHOOK, DWORD, HWND hwnd, LONG idObject, LONG, DWORD, DWORD) {
    if (idObject == OBJID_WINDOW) SyncHotkey(hwnd);
}

// The active tab of a folder window, or the desktop.
static IShellBrowser* ForegroundBrowser(HWND fg, IShellWindows* sw) {
    if (!sw) return nullptr;
    if (ClassIs(fg, L"Progman") || ClassIs(fg, L"WorkerW")) {
        VARIANT empty{};
        long h = 0;
        IDispatch* disp = nullptr;
        if (FAILED(sw->FindWindowSW(&empty, &empty, SWC_DESKTOP, &h, SWFO_NEEDDISPATCH, &disp)) || !disp)
            return nullptr;
        IShellBrowser* sb = nullptr;
        IServiceProvider* sp = nullptr;
        if (SUCCEEDED(disp->QueryInterface(IID_PPV_ARGS(&sp))) && sp) {
            sp->QueryService(SID_STopLevelBrowser, IID_PPV_ARGS(&sb));
            sp->Release();
        }
        disp->Release();
        return sb;
    }
    HWND activeTab = FindWindowExW(fg, nullptr, L"ShellTabWindowClass", nullptr);
    long count = 0;
    sw->get_Count(&count);
    IShellBrowser* pick = nullptr;
    for (long i = 0; i < count && !pick; i++) {
        VARIANT v{};
        v.vt = VT_I4;
        v.lVal = i;
        IDispatch* disp = nullptr;
        if (FAILED(sw->Item(v, &disp)) || !disp) continue;
        IWebBrowserApp* app = nullptr;
        SHANDLE_PTR h = 0;
        if (SUCCEEDED(disp->QueryInterface(IID_PPV_ARGS(&app))) && app) {
            app->get_HWND(&h);
            app->Release();
        }
        if ((HWND)h == fg) {
            IServiceProvider* sp = nullptr;
            IShellBrowser* sb = nullptr;
            if (SUCCEEDED(disp->QueryInterface(IID_PPV_ARGS(&sp))) && sp) {
                sp->QueryService(SID_STopLevelBrowser, IID_PPV_ARGS(&sb));
                sp->Release();
            }
            if (sb) {
                HWND tab = nullptr;
                if (!activeTab || (SUCCEEDED(sb->GetWindow(&tab)) && tab == activeTab)) pick = sb;
                else sb->Release();
            }
        }
        disp->Release();
    }
    return pick;
}

static void OnHotkey() {
    HWND fg = GetForegroundWindow();
    if (!OwnShellWindow(fg)) return;
    IShellWindows* sw = nullptr;
    if (FAILED(CoCreateInstance(CLSID_ShellWindows, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&sw))) || !sw) return;
    IShellBrowser* sb = ForegroundBrowser(fg, sw);
    std::vector<std::wstring> paths;
    wchar_t kind = ReadView(sb, paths);
    if (sb) sb->Release();
    sw->Release();
    Send(kind, std::move(paths));
}

static DWORD WINAPI HotkeyThread(void*) {
    HRESULT co = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    MSG m;
    PeekMessageW(&m, nullptr, WM_USER, WM_USER, PM_NOREMOVE);  // the queue exists before anyone posts to it
    ReadHotkey();
    HWINEVENTHOOK hook = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr, OnForeground, 0, 0,
                                         WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNTHREAD);
    SyncHotkey(GetForegroundWindow());
    while (GetMessageW(&m, nullptr, 0, 0) > 0) {
        if (!m.hwnd && m.message == WM_HOTKEY) {
            OnHotkey();
            continue;
        }
        if (!m.hwnd && m.message == WM_APP_HOTKEY_RELOAD) {
            if (g_hotOn) UnregisterHotKey(nullptr, 1);
            g_hotOn = false;
            ReadHotkey();
            SyncHotkey(GetForegroundWindow());
            continue;
        }
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    if (g_hotOn) UnregisterHotKey(nullptr, 1);
    g_hotOn = false;
    if (hook) UnhookWinEvent(hook);
    if (SUCCEEDED(co)) CoUninitialize();
    return 0;
}

static void StartHotkeyThread() {
    DWORD id = 0;
    g_hotThread = CreateThread(nullptr, 0, HotkeyThread, nullptr, 0, &id);
    g_hotThreadId = id;
}

static void ReloadHotkey() {
    if (DWORD id = g_hotThreadId) PostThreadMessageW(id, WM_APP_HOTKEY_RELOAD, 0, 0);
}

static void StopHotkeyThread() {
    if (!g_hotThread) return;
    if (DWORD id = g_hotThreadId) PostThreadMessageW(id, WM_QUIT, 0, 0);
    if (WaitForSingleObject(g_hotThread, 5000) == WAIT_TIMEOUT) Wh_Log(L"The shortcut thread did not stop");
    CloseHandle(g_hotThread);
    g_hotThread = nullptr;
    g_hotThreadId = 0;
}

}  // namespace bruex

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-26-seamless-bulk-rename\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace brset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessBulkRenameSettings";
constexpr UINT WM_APP_SETTINGS_RELOAD = WM_APP + 1, WM_APP_SETTINGS_ACTIVATE = WM_APP + 2;
HANDLE g_settingsThread = nullptr;
std::atomic<HWND> g_settingsWnd;
std::atomic<bool> g_settingsStop;
void Settings_Close();
static std::wstring GetStringSetting(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return s;
}
// SetForegroundWindow works when this process had the last input; an empty SendInput gives it.
static void ForceForeground(HWND hwnd) {
    INPUT input{};
    SendInput(1, &input, sizeof(INPUT));
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}
static float SystemCornerRadius(bool) { return 8; }
static int GetState(PCWSTR key, int fallback) { return Wh_GetIntValue(key, fallback); }
static void SetState(PCWSTR key, int value) { Wh_SetIntValue(key, value); }
static std::wstring StateKey(PCWSTR window, PCWSTR field) { return std::wstring(window)+L"_"+field; }
static void ApplyDarkWindow(HWND hwnd) { BOOL dark=TRUE; DwmSetWindowAttribute(hwnd,20,&dark,sizeof(dark)); }
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

COLORREF ParseColorRef(const std::wstring& text, COLORREF fallback) {
    std::wstring hex = !text.empty() && text[0] == L'#' ? text.substr(1) : text;
    if (hex.size() != 6 || hex.find_first_not_of(L"0123456789abcdefABCDEF") !=
                               std::wstring::npos) {
        return fallback;
    }
    UINT rgb = wcstoul(hex.c_str(), nullptr, 16);
    return RGB(rgb >> 16, (rgb >> 8) & 0xFF, rgb & 0xFF);
}

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

// One row of a tray menu (Set_TrayMenu). Every mod's tray menu is a list of these.
struct SetMenuItem {
    int id = 0;                    // What Set_TrayMenu returns when this row is picked.
    std::wstring glyph;            // FiraCode Nerd Font glyph for the leading column.
    std::wstring label;
    std::wstring hint;             // Grey text on the right, such as a hotkey.
    bool checked = false;          // Accent check mark on the right.
    bool separator = false;
    bool disabled = false;
    std::vector<SetMenuItem> sub;  // A submenu, drawn by the same renderer.
};

// One open level of a tray menu: its own popup window and Direct2D target.
struct SetMenuLevel {
    const std::vector<SetMenuItem>* items = nullptr;
    HWND hwnd = nullptr;
    SetCom<ID2D1HwndRenderTarget> rt;
    float scale = 1, wDip = 0, hDip = 0, itemH = 30, hintW = 0;
    std::vector<float> top, height;  // Per row, DIPs inside the window.
    int hover = -1;                  // Highlighted row.
    int open = -1;                   // Row whose submenu is the next level.
};

// A running tray menu. It owns its factories, so it runs on whatever thread owns the tray icon.
struct SetMenuSession {
    SetCom<ID2D1Factory> d2d;
    SetCom<IDWriteFactory> dw;
    SetCom<IDWriteTextFormat> fText, fHint, fGlyph, fGlyphS;
    std::vector<std::unique_ptr<SetMenuLevel>> levels;
    HINSTANCE inst = nullptr;
    std::wstring cls;
    float radius = 8;
    int result = 0;
    bool done = false;
    bool pressed = false;  // A button went down inside the menu; only then does a release pick a row.
    bool wasActive = false;
    float alpha = 1;
    ULONGLONG fadeStart = 0;
    int pendingLevel = -1, pendingItem = -1;  // Hover timer: open (item >= 0) or close a submenu after a delay.
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
    float fitW = 0;      // Box width that fits the text (Set_FitBoxes); 0 until measured.
    float fitText = -1;  // Measured text width behind fitW.
    std::wstring fitFor; // The text that was measured.
};

// Names, descriptions and option labels match the ==WindhawkModSettings== block word for word.
// Generated by work\2026-11-26-seamless-bulk-rename\gen.py from the settings block.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Text, L"rep.find", L"Find", L"The text to look for. Leave blank to skip.", L"", {}, 0, 100, 0, L"Find and replace"},
{K::Text, L"rep.with", L"Replace with", L"What goes in its place. Dates, counters and $1 for pattern groups work here.", L"", {}, 0, 100, 0, L"Find and replace"},
{K::Check, L"rep.regex", L"Use a pattern", L"Treat Find as a pattern, so one rule can match many shapes of name.", L"0", {}, 0, 100, 0, L"Find and replace"},
{K::Check, L"rep.matchCase", L"Match case", L"Only match the same capitals and small letters.", L"0", {}, 0, 100, 0, L"Find and replace"},
{K::Check, L"rep.all", L"Replace every match", L"Off replaces only the first match in each name.", L"1", {}, 0, 100, 0, L"Find and replace"},
{K::Choice, L"rep.scope", L"Look in", L"Which part of the file name the rule changes.", L"name", {{L"name", L"The name"}, {L"ext", L"The extension"}, {L"both", L"Name and extension"}}, 0, 100, 0, L"Find and replace"},
{K::Text, L"ch.from", L"Characters to swap", L"Each character here is swapped for the one at the same spot below.", L"", {}, 0, 100, 0, L"Swap characters"},
{K::Text, L"ch.to", L"Swap them for", L"Leave a spot empty to drop that character.", L"", {}, 0, 100, 0, L"Swap characters"},
{K::Choice, L"nm.mode", L"Name", L"Keep the name, clear it, set a new one, or flip it back to front.", L"keep", {{L"keep", L"Keep the name"}, {L"remove", L"Clear the name"}, {L"fixed", L"Use a new name"}, {L"reverse", L"Flip it back to front"}}, 0, 100, 1, L"Name"},
{K::Text, L"nm.fixed", L"New name", L"Used when Name is set to Use a new name. Add a counter so names don't repeat.", L"", {}, 0, 100, 1, L"Name"},
{K::Choice, L"cs.mode", L"Letter case", L"Change the capitals in the name.", L"same", {{L"same", L"Leave as is"}, {L"lower", L"all small"}, {L"upper", L"ALL CAPITALS"}, {L"title", L"Each Word Capital"}, {L"sentence", L"First letter capital"}}, 0, 100, 1, L"Letter case"},
{K::Text, L"cs.except", L"Words to leave alone", L"Space-separated words kept exactly as you type them, like USB or iPhone.", L"", {}, 0, 100, 1, L"Letter case"},
{K::Number, L"rm.first", L"Cut from the start", L"0 to 255 letters cut from the start.", L"0", {}, 0, 255, 1, L"Remove"},
{K::Number, L"rm.last", L"Cut from the end", L"0 to 255 letters cut from the end.", L"0", {}, 0, 255, 1, L"Remove"},
{K::Number, L"rm.from", L"Cut from spot", L"0 to 255: where a middle cut starts, 1 is the first letter. 0 turns it off.", L"0", {}, 0, 255, 1, L"Remove"},
{K::Number, L"rm.count", L"Letters to cut there", L"0 to 255 letters cut from that spot.", L"0", {}, 0, 255, 1, L"Remove"},
{K::Text, L"rm.chars", L"Characters to remove", L"Every one of these characters is removed wherever it shows.", L"", {}, 0, 100, 1, L"Remove"},
{K::Text, L"rm.words", L"Words to remove", L"Space-separated whole words that are removed.", L"", {}, 0, 100, 1, L"Remove"},
{K::Check, L"rm.digits", L"Remove digits", L"Drops 0 to 9 from the name.", L"0", {}, 0, 100, 1, L"Remove"},
{K::Check, L"rm.symbols", L"Remove symbols", L"Drops everything that isn't a letter, a digit or a space.", L"0", {}, 0, 100, 1, L"Remove"},
{K::Check, L"rm.accents", L"Remove accents", L"Turns letters like e with an accent into plain ones.", L"0", {}, 0, 100, 1, L"Remove"},
{K::Check, L"rm.doubleSpaces", L"Remove double spaces", L"Turns runs of spaces into one.", L"1", {}, 0, 100, 1, L"Remove"},
{K::Check, L"rm.trim", L"Trim spaces", L"Drops spaces at the start and end of the name.", L"1", {}, 0, 100, 1, L"Remove"},
{K::Choice, L"rm.crop", L"Crop", L"Drop everything before or after some text.", L"none", {{L"none", L"Off"}, {L"before", L"Drop what comes before it"}, {L"after", L"Drop what comes after it"}}, 0, 100, 1, L"Remove"},
{K::Text, L"rm.cropText", L"Crop at", L"The text Crop looks for. The text itself stays.", L"", {}, 0, 100, 1, L"Remove"},
{K::Choice, L"mv.mode", L"Move part", L"Move some letters from one end of the name to the other.", L"none", {{L"none", L"Off"}, {L"startToEnd", L"From the start to the end"}, {L"endToStart", L"From the end to the start"}}, 0, 100, 1, L"Move part"},
{K::Number, L"mv.count", L"Letters to move", L"0 to 255 letters moved.", L"0", {}, 0, 255, 1, L"Move part"},
{K::Text, L"mv.sep", L"Joined with", L"Text put between the moved part and the rest.", L" ", {}, 0, 100, 1, L"Move part"},
{K::Text, L"add.prefix", L"Add to the start", L"Text put in front of the name.", L"", {}, 0, 100, 2, L"Add text"},
{K::Text, L"add.suffix", L"Add to the end", L"Text put after the name, before the extension.", L"", {}, 0, 100, 2, L"Add text"},
{K::Text, L"add.insert", L"Insert text", L"Text put at the spot below.", L"", {}, 0, 100, 2, L"Add text"},
{K::Number, L"add.at", L"Insert at spot", L"0 to 255: where Insert text goes, 0 is before the first letter.", L"0", {}, 0, 255, 2, L"Add text"},
{K::Check, L"add.fromEnd", L"Count the spot from the end", L"Count Insert at spot from the end of the name.", L"0", {}, 0, 100, 2, L"Add text"},
{K::Check, L"add.wordSpace", L"Space between words", L"Puts a space before each capital, so MyHolidayPhoto reads My Holiday Photo.", L"0", {}, 0, 100, 2, L"Add text"},
{K::Choice, L"dt.mode", L"Add the date", L"Put the file's date in the name.", L"none", {{L"none", L"Off"}, {L"prefix", L"At the start"}, {L"suffix", L"At the end"}}, 0, 100, 2, L"Date"},
{K::Choice, L"dt.which", L"Which date", L"Photo taken falls back to the change date when a file has none.", L"modified", {{L"modified", L"Last changed"}, {L"created", L"Created"}, {L"taken", L"Photo taken"}, {L"now", L"Today"}}, 0, 100, 2, L"Date"},
{K::Text, L"dt.format", L"Date shape", L"YYYY year, MM month, DD day, hh hour, mm minute, ss second.", L"YYYY-MM-DD", {}, 0, 100, 2, L"Date"},
{K::Text, L"dt.sep", L"Joined with", L"Text put between the date and the name.", L" ", {}, 0, 100, 2, L"Date"},
{K::Choice, L"fd.mode", L"Add the folder name", L"Put the name of the folder the file sits in into the name.", L"none", {{L"none", L"Off"}, {L"prefix", L"At the start"}, {L"suffix", L"At the end"}}, 0, 100, 2, L"Folder name"},
{K::Number, L"fd.levels", L"Folders up", L"1 to 5 folder names, nearest last.", L"1", {}, 1, 5, 2, L"Folder name"},
{K::Text, L"fd.sep", L"Joined with", L"Text put between the folder name and the name.", L" - ", {}, 0, 100, 2, L"Folder name"},
{K::Choice, L"num.mode", L"Add a number", L"Count the files in list order.", L"none", {{L"none", L"Off"}, {L"prefix", L"At the start"}, {L"suffix", L"At the end"}, {L"insert", L"At a spot"}, {L"replace", L"Instead of the name"}}, 0, 100, 2, L"Numbers"},
{K::Number, L"num.start", L"Start at", L"0 to 999999: the first number.", L"1", {}, 0, 999999, 2, L"Numbers"},
{K::Number, L"num.step", L"Count by", L"1 to 1000: how much each number goes up.", L"1", {}, 1, 1000, 2, L"Numbers"},
{K::Number, L"num.pad", L"Digits", L"0 to 10: pad with zeros to this many digits, 3 makes 001.", L"0", {}, 0, 10, 2, L"Numbers"},
{K::Number, L"num.at", L"Spot", L"0 to 255: where the number goes when it is At a spot.", L"0", {}, 0, 255, 2, L"Numbers"},
{K::Text, L"num.sep", L"Joined with", L"Text put between the number and the name.", L" ", {}, 0, 100, 2, L"Numbers"},
{K::Check, L"num.restart", L"Start again in each folder", L"Each folder counts from the start again.", L"0", {}, 0, 100, 2, L"Numbers"},
{K::Choice, L"num.style", L"Number style", L"How the number is written.", L"decimal", {{L"decimal", L"1 2 3"}, {L"alphaLower", L"a b c"}, {L"alphaUpper", L"A B C"}, {L"roman", L"I II III"}, {L"hex", L"1 A 1F"}}, 0, 100, 2, L"Numbers"},
{K::Choice, L"ext.mode", L"Extension", L"Change the part after the last dot.", L"same", {{L"same", L"Leave as is"}, {L"lower", L"all small"}, {L"upper", L"ALL CAPITALS"}, {L"fixed", L"Use a new one"}, {L"add", L"Add one after it"}, {L"remove", L"Remove it"}}, 0, 100, 3, L"Extension"},
{K::Text, L"ext.fixed", L"New extension", L"Without the dot. Used by Use a new one and Add one after it.", L"", {}, 0, 100, 3, L"Extension"},
{K::Text, L"f.include", L"Only these files", L"Wildcards split by a semicolon, like *.jpg;*.png. Used when a whole folder is added.", L"*", {}, 0, 100, 4, L"Files"},
{K::Check, L"f.files", L"Files", L"Take files when a folder is added.", L"1", {}, 0, 100, 4, L"Files"},
{K::Check, L"f.folders", L"Folders", L"Take folders when a folder is added.", L"0", {}, 0, 100, 4, L"Files"},
{K::Check, L"f.subfolders", L"Look inside subfolders", L"Take what is inside the folders too.", L"0", {}, 0, 100, 4, L"Files"},
{K::Check, L"f.hidden", L"Hidden files", L"Take hidden and system files too.", L"0", {}, 0, 100, 4, L"Files"},
{K::Choice, L"f.sort", L"Order", L"The order numbers count in.", L"natural", {{L"natural", L"Name, 2 before 10"}, {L"name", L"Name, letter by letter"}, {L"modified", L"Last changed"}, {L"created", L"Created"}, {L"size", L"Size"}, {L"type", L"Type"}, {L"added", L"As added"}}, 0, 100, 4, L"Files"},
{K::Check, L"f.sortDesc", L"Reverse the order", L"Count from the last one.", L"0", {}, 0, 100, 4, L"Files"},
{K::Check, L"fdt.on", L"Change file dates", L"Set the dates on each file as it is renamed.", L"0", {}, 0, 100, 5, L"File dates"},
{K::Choice, L"fdt.which", L"Dates to change", L"Which of the dates are set.", L"modified", {{L"modified", L"Last changed"}, {L"created", L"Created"}, {L"both", L"Both"}}, 0, 100, 5, L"File dates"},
{K::Choice, L"fdt.mode", L"Set them to", L"Now, the date below, or the date the photo was taken.", L"now", {{L"now", L"Now"}, {L"fixed", L"The date below"}, {L"taken", L"Photo taken"}}, 0, 100, 5, L"File dates"},
{K::Text, L"fdt.value", L"Date", L"As YYYY-MM-DD hh:mm.", L"2026-01-01 12:00", {}, 0, 100, 5, L"File dates"},
{K::Choice, L"at.readOnly", L"Read-only", L"Lock the file against changes, or unlock it.", L"keep", {{L"keep", L"Leave as is"}, {L"set", L"Turn on"}, {L"clear", L"Turn off"}}, 0, 100, 5, L"Marks"},
{K::Choice, L"at.hidden", L"Hidden", L"Hide the file, or show it.", L"keep", {{L"keep", L"Leave as is"}, {L"set", L"Turn on"}, {L"clear", L"Turn off"}}, 0, 100, 5, L"Marks"},
{K::Choice, L"at.archive", L"Archive", L"The mark backup apps use.", L"keep", {{L"keep", L"Leave as is"}, {L"set", L"Turn on"}, {L"clear", L"Turn off"}}, 0, 100, 5, L"Marks"},
{K::Check, L"cp.on", L"Copy instead of rename", L"Leave the files as they are and copy them under the new names.", L"0", {}, 0, 100, 4, L"Copy"},
{K::Text, L"cp.folder", L"Copy to", L"The folder the copies go in. Blank puts them next to the files.", L"", {}, 0, 100, 4, L"Copy"},
{K::Text, L"preset.name", L"Preset name", L"The name a preset is saved under.", L"", {}, 0, 100, 6, L"Presets"},
{K::Hotkey, L"renameHotkey", L"Shortcut", L"Press it in Explorer or on the desktop to rename what is selected, or the whole folder when nothing is.", L"Ctrl+Shift+F2", {}, 0, 100, 7, L"Behavior"},
{K::Check, L"menuEntry", L"Bulk rename in the right-click menu", L"Adds Bulk rename next to Rename. It shows under Show more options.", L"1", {}, 0, 100, 7, L"Behavior"},
{K::Number, L"undoLevels", L"Runs to keep for undo", L"1 to 20 runs kept, newest first.", L"10", {}, 1, 20, 7, L"Behavior"},
{K::Choice, L"afterRename", L"After renaming", L"What the window does once a rename is done.", L"keep", {{L"keep", L"Keep the list"}, {L"clear", L"Clear the list"}, {L"close", L"Close the window"}}, 0, 100, 7, L"Behavior"},
{K::Check, L"confirmBig", L"Ask before big runs", L"Over 500 files, Rename needs a second click.", L"1", {}, 0, 100, 7, L"Behavior"},
{K::Check, L"settingsAnimation", L"Open and close animation", L"The window fades in with a short slide. Stays still when Windows animations are off.", L"1", {}, 0, 100, 8, L"Settings window"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 8, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 8, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"An icon in the tray. Click it to open the window. Right-click for undo and settings.", L"1", {}, 0, 100, 8, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Replace", L"Find text in the names and put something else in its place.", 0xE8AB},
{L"Name", L"Set a new name, change the capitals, cut letters or move part of the name.", 0xE8AC},
{L"Add", L"Put text, the date, the folder name or a number into each name.", 0xE710},
{L"Extension", L"Change, add or drop the part after the last dot.", 0xE7C3},
{L"Files", L"Which files a dropped folder brings in, the order they count in, and copying.", 0xE8B7},
{L"Dates and marks", L"Set file dates and the read-only, hidden and archive marks as files are renamed.", 0xE787},
{L"Presets", L"Keep up to five sets of rules and load them again in one click.", 0xE728},
{L"Settings", L"The shortcut, the right-click menu, undo and what happens after a rename.", 0xE713},
{L"Look", L"Choose how this window looks and whether its tray icon is shown.", 0xE771},
{L"About", L"Version, credits, support and links.", 0xE946},
};
constexpr int kSetPageCount = (int)(sizeof(kSetPages) / sizeof(kSetPages[0]));
// About sits apart at the end of the sidebar, as in Seamless Dictate.
constexpr int kSetAboutPage = kSetPageCount - 1;
constexpr float kSetAboutGap = 17;

// All sizes are DIPs; the render target does the scaling.
constexpr float kSetPadX = 40, kSetMaxW = 720, kSetRowMin = 56, kSetRowGap = 8, kSetBoxH = 32, kSetRowPad = 16,
                kSetDropItem = 32, kSetRailTop = 76, kSetRailItem = 36, kSetRailPitch = 40;
constexpr int kSetDropMax = 9;  // A dropdown with more options than this scrolls.
// The sidebar is a floating dock: dragged between min and max, or collapsed to an icon rail.
constexpr float kSetDockGap = 10, kSetRailDef = 232, kSetRailMin = 200, kSetRailMax = 380, kSetRailMini = 60,
                kSetRailSnap = 130, kSetEdgeGrab = 5;
// The footer is a floating pill dock at the bottom right of the page.
constexpr float kSetFootBtnH = 36, kSetFootPad = 8, kSetFootH = kSetFootBtnH + 2 * kSetFootPad, kSetFootGap = 14;
// The glass tint is one layer over the whole window, title bar included, so the two always match.
constexpr float kSetGlassTint = 0.55f, kSetNativeFade = 56;
constexpr float kSetEdgeW = 2, kSetRadius = 16;
constexpr int kSetChipCount = 10;
constexpr UINT32 kSetChips[kSetChipCount] = {mocha::blue,   mocha::sapphire, mocha::teal, mocha::green, mocha::yellow,
                                             mocha::peach,  mocha::red,      mocha::pink, mocha::mauve, mocha::lavender};
constexpr UINT_PTR kSetTimerId = 1;
constexpr float kSetAutoDead = 10, kSetAutoR = 18, kSetAutoGain = 0.14f, kSetAutoMax = 56;
constexpr PCWSTR kSetAutoProp = L"SeamlessOwnAutoscroll";  // Seamless Autoscroll skips this window.
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetCreditPowerToys = L"https://github.com/microsoft/PowerToys";
constexpr PCWSTR kSetCreditBru = L"https://www.bulkrenameutility.co.uk";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/seamless-workshop";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/seamless-workshop/issues/new?title=%5BSeamless%20Bulk%20Rename%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Bulk Rename";
// The self-drawn title bar. Everything below it is laid out as before, in "content" DIPs.
static float kSetCapH = 40;
constexpr float kSetCapBtnW = 46, kSetHoverMs = 120;
constexpr float kSetMenuPad = 6, kSetMenuIconW = 22, kSetMenuSepH = 9, kSetMenuOverlap = 3, kSetMenuMinW = 190, kSetMenuMaxW = 640, kSetMenuBorderW = 2;
constexpr UINT kSetMenuSubDelayMs = 200, kSetMenuFadeMs = 90, kSetMenuTimerSub = 0x5E71, kSetMenuTimerFade = 0x5E72, kSetMenuTimerPoll = 0x5E73;

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
    bool glass = false;        // Acrylic behind the window; the page is drawn see-through.
    ULONGLONG lastTick = 0;
    int page = 0, recording = -1, editing = -1, focus = -1, openSel = -1;
    bool kbd = false;  // Show the focus ring (after a Tab).
    D2D1_RECT_F dropRect{};
    int dropHover = -1, dropTop = 0;  // dropTop: first option shown when the dropdown scrolls.
    bool frameApplied = false;        // Set_ApplyFrame has run once.
    float scrollY = 0, scrollTarget = 0, contentH = 0, contentX = 0, contentW = 720, pageT = 1;
    SetHit hover;
    int dragSlider = -1;
    bool dragScroll = false, tracking = false, timer = false;
    float dragOff = 0;
    bool autoScroll = false, autoMoved = false;
    float autoX = 0, autoY = 0, autoA = 0, autoDir = 0;
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

static float Set_Rad(const D2D1_RECT_F& r, float most = kSetRadius) {
    return std::min(most, std::min(r.right - r.left, r.bottom - r.top) / 2);
}

static std::wstring Set_WindowText(HWND hwnd) {
    std::wstring text(GetWindowTextLengthW(hwnd) + 1, L'\0');
    text.resize(GetWindowTextW(hwnd, text.data(), (int)text.size()));
    return text;
}

static std::wstring Set_KeyStatusText() {
#ifdef SCM_HARNESS
    if (!g_setFakeKeyStatus.empty()) return g_setFakeKeyStatus;
#endif
    return std::wstring();
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
    if (Set_FamilyExists(std::wstring(L"FiraCode Nerd Font"))) return std::wstring(L"FiraCode Nerd Font");
    std::wstring joined;
    for (WCHAR c : std::wstring(L"FiraCode Nerd Font"))
        if (c != L' ') joined += c;
    for (const std::wstring& face : {joined + L" Nerd Font", std::wstring(L"FiraCode Nerd Font") + L" Nerd Font", joined})
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

// std::wstring(L"FiraCode Nerd Font") at 500; emphasis is one step heavier, never past bold.
static float Set_MenuCornerRadius() {
    float radius = 8.0f;
    HKEY key;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius", 0,
                      KEY_READ | KEY_WOW64_64KEY, &key) == ERROR_SUCCESS) {
        DWORD disabled = 0, size = sizeof(disabled);
        bool off = RegQueryValueExW(key, L"Disabled", nullptr, nullptr, (BYTE*)&disabled, &size) == ERROR_SUCCESS && disabled;
        DWORD value = 0;
        size = sizeof(value);
        if (!off && RegGetValueW(key, L"Settings", L"radius", RRF_RT_REG_DWORD, nullptr, &value, &size) == ERROR_SUCCESS &&
            value > 0 && value <= 64)
            radius = (float)value;
        RegCloseKey(key);
    }
    return radius;
}

static SetMenuItem Set_MenuRow(int id, PCWSTR glyph, PCWSTR label, bool checked = false, bool disabled = false,
                               PCWSTR hint = L"") {
    SetMenuItem m;
    m.id = id;
    m.glyph = glyph ? glyph : L"";
    m.label = label ? label : L"";
    m.hint = hint ? hint : L"";
    m.checked = checked;
    m.disabled = disabled;
    return m;
}

static SetMenuItem Set_MenuSub(PCWSTR glyph, PCWSTR label, std::vector<SetMenuItem> sub, bool disabled = false) {
    SetMenuItem m = Set_MenuRow(0, glyph, label, false, disabled);
    m.sub = std::move(sub);
    return m;
}

static SetMenuItem Set_MenuSep() {
    SetMenuItem m;
    m.separator = true;
    return m;
}

static SetMenuSession*& Set_MenuCur() {
    static thread_local SetMenuSession* session = nullptr;  // One menu per thread; History menus run on the settings thread.
    return session;
}

static bool Set_MenuSelectable(const SetMenuItem& m) { return !m.separator && !m.disabled; }

static float Set_MenuTextW(SetMenuSession& s, IDWriteTextFormat* f, const std::wstring& text) {
    SetCom<IDWriteTextLayout> layout;
    DWRITE_TEXT_METRICS m{};
    if (text.empty() || !f || FAILED(s.dw->CreateTextLayout(text.c_str(), (UINT32)text.size(), f, 10000, 1000, layout.put())) ||
        FAILED(layout->GetMetrics(&m)))
        return 0;
    return m.widthIncludingTrailingWhitespace;
}

static bool Set_MenuFormats(SetMenuSession& s) {
    if (!s.d2d && FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), nullptr,
                                           (void**)s.d2d.put())))
        return false;
    if (!s.dw && FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)s.dw.put())))
        return false;
    std::wstring family = L"Segoe UI";
    SetCom<IDWriteFontCollection> sys;
    if (SUCCEEDED(s.dw->GetSystemFontCollection(sys.put(), FALSE))) {
        for (PCWSTR face : {L"FiraCode Nerd Font", L"FiraCodeNerdFont", L"FiraCode Nerd Font Mono"}) {
            UINT32 index = 0;
            BOOL exists = FALSE;
            if (SUCCEEDED(sys->FindFamilyName(face, &index, &exists)) && exists) {
                family = face;
                break;
            }
        }
    }
    auto make = [&](float size, DWRITE_TEXT_ALIGNMENT align, SetCom<IDWriteTextFormat>& out) {
        if (FAILED(s.dw->CreateTextFormat(family.c_str(), nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
                                          DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", out.put())))
            return false;
        out->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
        out->SetTextAlignment(align);
        out->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
        // Only a label wider than the widest menu (kSetMenuMaxW) is ever shortened, with an ellipsis.
        DWRITE_TRIMMING trim{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
        SetCom<IDWriteInlineObject> sign;
        if (SUCCEEDED(s.dw->CreateEllipsisTrimmingSign(out.get(), sign.put()))) out->SetTrimming(&trim, sign.get());
        return true;
    };
    return make(13.5f, DWRITE_TEXT_ALIGNMENT_LEADING, s.fText) && make(12.5f, DWRITE_TEXT_ALIGNMENT_TRAILING, s.fHint) &&
           make(15, DWRITE_TEXT_ALIGNMENT_CENTER, s.fGlyph) && make(12, DWRITE_TEXT_ALIGNMENT_CENTER, s.fGlyphS);
}

static void Set_MenuLayout(SetMenuSession& s, SetMenuLevel& lv) {
    const auto& items = *lv.items;
    lv.itemH = 30;
    lv.top.assign(items.size(), 0);
    lv.height.assign(items.size(), 0);
    float textW = 0, hintW = 0, y = kSetMenuPad;
    for (size_t i = 0; i < items.size(); i++) {
        lv.top[i] = y;
        lv.height[i] = items[i].separator ? kSetMenuSepH : lv.itemH;
        y += lv.height[i];
        if (items[i].separator) continue;
        textW = std::max(textW, Set_MenuTextW(s, s.fText.get(), items[i].label));
        hintW = std::max(hintW, Set_MenuTextW(s, s.fHint.get(), items[i].hint));
    }
    lv.hintW = std::ceil(hintW);
    float w = kSetMenuPad * 2 + 8 + kSetMenuIconW + 10 + std::ceil(textW) + 2 + (hintW > 0 ? 24 + lv.hintW : 0) + 10 + 20 + 8;
    lv.wDip = std::ceil(std::clamp(w, kSetMenuMinW, kSetMenuMaxW));
    lv.hDip = std::ceil(y + kSetMenuPad);
}

static int Set_MenuItemAt(const SetMenuLevel& lv, float x, float y) {
    if (x < kSetMenuPad || x >= lv.wDip - kSetMenuPad) return -1;
    for (size_t i = 0; i < lv.top.size(); i++)
        if (y >= lv.top[i] && y < lv.top[i] + lv.height[i]) return (*lv.items)[i].separator ? -1 : (int)i;
    return -1;
}

static int Set_MenuNext(const SetMenuLevel& lv, int from, int dir) {
    int n = (int)lv.items->size();
    if (!n) return -1;
    int i = from < 0 ? (dir > 0 ? -1 : n) : from;
    for (int k = 0; k < n; k++) {
        i = ((i + dir) % n + n) % n;
        if (Set_MenuSelectable((*lv.items)[(size_t)i])) return i;
    }
    return -1;
}

static void Set_MenuPaint(SetMenuSession& s, SetMenuLevel& lv) {
    ID2D1RenderTarget* rt = lv.rt.get();
    SetCom<ID2D1SolidColorBrush> brush;
    if (FAILED(rt->CreateSolidColorBrush(D2DColor(mocha::text), brush.put()))) return;
    auto solid = [&](UINT32 rgb, float a) {
        brush->SetColor(D2DColor(rgb, a));
        return brush.get();
    };
    auto gradient = [&](D2D1_POINT_2F a, D2D1_POINT_2F b, D2D1_COLOR_F c1, D2D1_COLOR_F c2) {
        SetCom<ID2D1LinearGradientBrush> g;
        D2D1_GRADIENT_STOP stops[2] = {{0, c1}, {1, c2}};
        SetCom<ID2D1GradientStopCollection> coll;
        if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, coll.put())))
            rt->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(a, b), coll.get(), g.put());
        return g;
    };
    // Blue to mauve at 45 degrees across a rect, like Seamless Borders.
    auto accent = [&](const D2D1_RECT_F& r, float a) {
        float d = ((r.right - r.left) + (r.bottom - r.top)) / 2;
        return gradient({r.left, r.top}, {r.left + d, r.top + d}, D2DColor(mocha::blue, a), D2DColor(mocha::mauve, a));
    };
    const float w = lv.wDip, h = lv.hDip;
    rt->Clear(D2D1::ColorF(0, 0, 0, 0));
    SetCom<ID2D1Layer> layer;
    bool faded = s.alpha < 0.999f && SUCCEEDED(rt->CreateLayer(nullptr, layer.put()));
    if (faded)
        rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), nullptr, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
                                            D2D1::IdentityMatrix(), std::max(0.0f, s.alpha)),
                      layer.get());
    // Dark Mocha over the acrylic blur; DWM rounds the window.
    auto tint = gradient({0, 0}, {0, h}, D2DColor(mocha::base, 0.80f), D2DColor(mocha::base, 0.84f));
    if (tint) rt->FillRectangle({0, 0, w, h}, tint.get());
    const auto& items = *lv.items;
    const float slotRight = w - kSetMenuPad - 8, slotLeft = slotRight - 20;
    for (size_t i = 0; i < items.size(); i++) {
        const SetMenuItem& m = items[i];
        D2D1_RECT_F r{kSetMenuPad, lv.top[i], w - kSetMenuPad, lv.top[i] + lv.height[i]};
        if (m.separator) {
            float y = std::floor((r.top + r.bottom) / 2);
            rt->FillRectangle({r.left + 8, y, r.right - 8, y + 1}, solid(mocha::surface1, 0.8f));
            continue;
        }
        bool hot = ((int)i == lv.hover || (int)i == lv.open) && !m.disabled;
        if (hot) {
            // The hover look of every card: a faint blue to mauve wash and the 2 px gradient ring.
            float ringW = kSetEdgeW, rad = std::min(12.0f, (r.bottom - r.top) / 2);
            D2D1_ROUNDED_RECT rr{{r.left + ringW / 2, r.top + ringW / 2, r.right - ringW / 2, r.bottom - ringW / 2}, rad, rad};
            auto fill = gradient({r.left, r.top}, {r.right, r.bottom}, D2DColor(mocha::blue, 0.16f), D2DColor(mocha::mauve, 0.16f));
            if (fill) rt->FillRoundedRectangle(rr, fill.get());
            auto ring = accent(r, 0.8f);
            if (ring) rt->DrawRoundedRectangle(rr, ring.get(), ringW);
        }
        UINT32 col = m.disabled ? mocha::overlay0 : mocha::text;
        if (!m.glyph.empty())
            rt->DrawText(m.glyph.c_str(), (UINT32)m.glyph.size(), s.fGlyph.get(),
                         {r.left + 8, r.top, r.left + 8 + kSetMenuIconW, r.bottom}, solid(col, 1));
        float textX = r.left + 8 + kSetMenuIconW + 10;
        float hintRight = slotLeft - 10, hintLeft = hintRight - lv.hintW;
        float textRight = lv.hintW > 0 ? hintLeft - 12 : slotLeft - 4;
        if (!m.label.empty())
            rt->DrawText(m.label.c_str(), (UINT32)m.label.size(), s.fText.get(), {textX, r.top, textRight, r.bottom},
                         solid(col, 1));
        if (!m.hint.empty())
            rt->DrawText(m.hint.c_str(), (UINT32)m.hint.size(), s.fHint.get(), {hintLeft, r.top, hintRight, r.bottom},
                         solid(m.disabled ? mocha::overlay0 : mocha::subtext0, 1));
        if (!m.sub.empty()) {
            rt->DrawText(L"", 1, s.fGlyphS.get(), {slotLeft, r.top, slotRight, r.bottom}, solid(col, 1));  // chevron_right
        } else if (m.checked) {
            rt->DrawText(L"", 1, s.fGlyph.get(), {slotLeft, r.top, slotRight, r.bottom},  // check
                         solid(m.disabled ? mocha::overlay0 : mocha::blue, 1));
        }
    }
    // The edge on DWM's real corner curve: 2 px, blue to mauve, inset half the stroke.
    const float bw = kSetMenuBorderW;
    D2D1_RECT_F edge{bw / 2, bw / 2, w - bw / 2, h - bw / 2};
    auto border = accent({0, 0, w, h}, 1);
    float r2 = std::max(0.0f, s.radius - bw / 2);
    if (border) rt->DrawRoundedRectangle({edge, r2, r2}, border.get(), bw);
    if (faded) rt->PopLayer();
}

static int Set_MenuIndexOf(HWND hwnd) {
    if (SetMenuSession* s = Set_MenuCur())
        for (size_t i = 0; i < s->levels.size(); i++)
            if (s->levels[i]->hwnd == hwnd) return (int)i;
    return -1;
}

static void Set_MenuInvalidate() {
    if (SetMenuSession* s = Set_MenuCur())
        for (auto& lv : s->levels)
            if (lv->hwnd) InvalidateRect(lv->hwnd, nullptr, FALSE);
}

static void Set_MenuCloseFrom(size_t n) {
    SetMenuSession* s = Set_MenuCur();
    if (!s) return;
    while (s->levels.size() > n) {
        HWND h = s->levels.back()->hwnd;
        s->levels.back()->rt.reset();
        s->levels.pop_back();
        if (h) DestroyWindow(h);
    }
    if (n > 0 && !s->levels.empty()) s->levels.back()->open = -1;
    Set_MenuInvalidate();
}

static void Set_MenuFinish(int id) {
    SetMenuSession* s = Set_MenuCur();
    if (!s || s->done) return;
    s->result = id;
    s->done = true;
}

static void Set_MenuBackdrop(HWND hwnd) {
    BOOL dark = TRUE;
    DwmSetWindowAttribute(hwnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    int corner = 2;  // DWMWCP_ROUND
    DwmSetWindowAttribute(hwnd, 33 /* DWMWA_WINDOW_CORNER_PREFERENCE */, &corner, sizeof(corner));
    COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE: the menu draws its own edge.
    DwmSetWindowAttribute(hwnd, 34 /* DWMWA_BORDER_COLOR */, &none, sizeof(none));
    DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
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
    if (auto setComposition =
            (SetComposition_t)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute")) {
        SetAccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, (int)0x012E1E1E, 0};
        SetCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
        setComposition(hwnd, &data);
    }
}

static RECT Set_MenuWorkArea(POINT pt) {
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST), &mi);
    return mi.rcWork;
}

static bool Set_MenuCreateWindow(SetMenuSession& s, SetMenuLevel& lv, POINT at, const RECT* parent, int rowTopPx) {
    DWORD ex = WS_EX_TOOLWINDOW | WS_EX_TOPMOST | (parent ? WS_EX_NOACTIVATE : 0);
    HWND hwnd = CreateWindowExW(ex, s.cls.c_str(), L"", WS_POPUP, at.x, at.y, 1, 1, nullptr, nullptr, s.inst, nullptr);
    if (!hwnd) return false;
    lv.hwnd = hwnd;
    lv.scale = GetDpiForWindow(hwnd) / 96.0f;
    if (lv.scale <= 0) lv.scale = 1;
    Set_MenuLayout(s, lv);
    int w = (int)std::ceil(lv.wDip * lv.scale), h = (int)std::ceil(lv.hDip * lv.scale);
    RECT wa = Set_MenuWorkArea(parent ? POINT{parent->right, parent->top + rowTopPx} : at);
    int x = at.x, y = at.y;
    if (parent) {
        int overlap = (int)kSetMenuOverlap;
        x = parent->right - overlap;
        if (x + w > wa.right) x = parent->left - w + overlap;
        y = parent->top + rowTopPx - (int)(kSetMenuPad * lv.scale);
        if (y + h > wa.bottom) y = wa.bottom - h;
    } else {
        if (x + w > wa.right) x = at.x - w;
        if (y + h > wa.bottom) y = at.y - h;
    }
    x = std::clamp<int>(x, wa.left, std::max<int>(wa.left, wa.right - w));
    y = std::clamp<int>(y, wa.top, std::max<int>(wa.top, wa.bottom - h));
    Set_MenuBackdrop(hwnd);
    SetWindowPos(hwnd, HWND_TOPMOST, x, y, w, h, SWP_NOACTIVATE | SWP_FRAMECHANGED);
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
        96 * lv.scale, 96 * lv.scale);
    s.d2d->CreateHwndRenderTarget(props, D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU((UINT32)w, (UINT32)h)),
                                  lv.rt.put());
    return (bool)lv.rt;
}

static void Set_MenuOpenSub(size_t level, int item, bool keyboard) {
    SetMenuSession* s = Set_MenuCur();
    if (!s || level >= s->levels.size()) return;
    SetMenuLevel& parent = *s->levels[level];
    const SetMenuItem& m = (*parent.items)[(size_t)item];
    if (m.sub.empty() || m.disabled) return;
    Set_MenuCloseFrom(level + 1);
    auto lv = std::make_unique<SetMenuLevel>();
    lv->items = &m.sub;
    RECT pr{};
    GetWindowRect(parent.hwnd, &pr);
    SetMenuLevel* raw = lv.get();
    s->levels.push_back(std::move(lv));
    parent.open = item;
    if (!Set_MenuCreateWindow(*s, *raw, POINT{pr.right, pr.top}, &pr, (int)(parent.top[(size_t)item] * parent.scale))) {
        Set_MenuCloseFrom(level + 1);
        return;
    }
    if (keyboard) raw->hover = Set_MenuNext(*raw, -1, +1);
    ShowWindow(raw->hwnd, SW_SHOWNOACTIVATE);
    Set_MenuInvalidate();
}

static void Set_MenuActivate(size_t level, int item, bool keyboard) {
    SetMenuSession* s = Set_MenuCur();
    if (!s || level >= s->levels.size()) return;
    const SetMenuItem& m = (*s->levels[level]->items)[(size_t)item];
    if (!Set_MenuSelectable(m)) return;
    if (!m.sub.empty()) Set_MenuOpenSub(level, item, keyboard);
    else Set_MenuFinish(m.id);
}

static void Set_MenuHoverChanged(size_t level, int item) {
    SetMenuSession* s = Set_MenuCur();
    if (!s) return;
    SetMenuLevel& lv = *s->levels[level];
    HWND root = s->levels[0]->hwnd;
    KillTimer(root, kSetMenuTimerSub);
    s->pendingItem = -1;
    bool wantsSub = item >= 0 && Set_MenuSelectable((*lv.items)[(size_t)item]) && !(*lv.items)[(size_t)item].sub.empty();
    if (wantsSub && lv.open != item) {
        s->pendingLevel = (int)level;
        s->pendingItem = item;
        SetTimer(root, kSetMenuTimerSub, kSetMenuSubDelayMs, nullptr);
    } else if (!wantsSub && lv.open != -1 && s->levels.size() > level + 1) {
        s->pendingLevel = (int)level;
        s->pendingItem = -1;
        SetTimer(root, kSetMenuTimerSub, kSetMenuSubDelayMs, nullptr);
    }
}

static void Set_MenuKey(WPARAM vk) {
    SetMenuSession* s = Set_MenuCur();
    if (!s || s->levels.empty()) return;
    size_t li = s->levels.size() - 1;
    SetMenuLevel& cur = *s->levels[li];
    const auto& items = *cur.items;
    switch (vk) {
        case VK_DOWN: cur.hover = Set_MenuNext(cur, cur.hover, +1); break;
        case VK_UP: cur.hover = Set_MenuNext(cur, cur.hover, -1); break;
        case VK_HOME: cur.hover = Set_MenuNext(cur, -1, +1); break;
        case VK_END: cur.hover = Set_MenuNext(cur, (int)items.size(), -1); break;
        case VK_RIGHT:
            if (cur.hover >= 0 && !items[(size_t)cur.hover].sub.empty()) Set_MenuActivate(li, cur.hover, true);
            break;
        case VK_LEFT:
            if (li > 0) Set_MenuCloseFrom(li);
            break;
        case VK_RETURN:
        case VK_SPACE:
            if (cur.hover >= 0) Set_MenuActivate(li, cur.hover, true);
            break;
        case VK_ESCAPE:
        case VK_MENU:
            if (li > 0 && vk == VK_ESCAPE) Set_MenuCloseFrom(li);
            else Set_MenuFinish(0);
            break;
        default: return;
    }
    Set_MenuInvalidate();
}

static LRESULT CALLBACK Set_MenuProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetMenuSession* s = Set_MenuCur();
    int li = Set_MenuIndexOf(hwnd);
    if (!s || li < 0) return DefWindowProcW(hwnd, msg, wParam, lParam);
    SetMenuLevel& lv = *s->levels[(size_t)li];
    switch (msg) {
        case WM_ERASEBKGND: return 1;
        case WM_MOUSEACTIVATE: return li == 0 ? MA_ACTIVATE : MA_NOACTIVATE;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            if (lv.rt) {
                lv.rt->BeginDraw();
                Set_MenuPaint(*s, lv);
                if (lv.rt->EndDraw() == D2DERR_RECREATE_TARGET) {
                    RECT rc;
                    GetClientRect(hwnd, &rc);
                    lv.rt.reset();
                    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
                        D2D1_RENDER_TARGET_TYPE_DEFAULT,
                        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 96 * lv.scale,
                        96 * lv.scale);
                    s->d2d->CreateHwndRenderTarget(
                        props, D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU((UINT32)rc.right, (UINT32)rc.bottom)),
                        lv.rt.put());
                    InvalidateRect(hwnd, nullptr, FALSE);
                }
            }
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_MOUSEMOVE: {
            if (s->pendingLevel > li) {  // The pointer reached a deeper level: keep it open.
                KillTimer(s->levels[0]->hwnd, kSetMenuTimerSub);
                s->pendingItem = s->pendingLevel = -1;
            }
            TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
            TrackMouseEvent(&tme);
            int i = Set_MenuItemAt(lv, (short)LOWORD(lParam) / lv.scale, (short)HIWORD(lParam) / lv.scale);
            if (i >= 0 && !Set_MenuSelectable((*lv.items)[(size_t)i])) i = -1;
            if (i != lv.hover) {
                lv.hover = i;
                Set_MenuHoverChanged((size_t)li, i);
                Set_MenuInvalidate();
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
            if (!s->pressed) return 0;  // The release of the click that opened the menu.
            int i = Set_MenuItemAt(lv, (short)LOWORD(lParam) / lv.scale, (short)HIWORD(lParam) / lv.scale);
            if (i >= 0) Set_MenuActivate((size_t)li, i, false);
            return 0;
        }
        case WM_ACTIVATE:
            if (li == 0 && LOWORD(wParam) != WA_INACTIVE) s->wasActive = true;
            if (li == 0 && LOWORD(wParam) == WA_INACTIVE && Set_MenuIndexOf((HWND)lParam) < 0) Set_MenuFinish(0);
            return 0;
        case WM_TIMER:
            if (wParam == kSetMenuTimerSub) {
                KillTimer(hwnd, kSetMenuTimerSub);
                int pl = s->pendingLevel, pi = s->pendingItem;
                s->pendingLevel = s->pendingItem = -1;
                if (pl >= 0 && (size_t)pl < s->levels.size()) {
                    if (pi >= 0) Set_MenuOpenSub((size_t)pl, pi, false);
                    else Set_MenuCloseFrom((size_t)pl + 1);
                }
            } else if (wParam == kSetMenuTimerFade) {
                float t = std::min(1.0f, (GetTickCount64() - s->fadeStart) / (float)kSetMenuFadeMs);
                s->alpha = 1 - (1 - t) * (1 - t);
                if (t >= 1) KillTimer(hwnd, kSetMenuTimerFade);
                Set_MenuInvalidate();
            } else if (wParam == kSetMenuTimerPoll) {
                // Click-away when Windows kept the menu out of the foreground: a press outside every level.
                if (GetForegroundWindow() != s->levels[0]->hwnd &&
                    ((GetAsyncKeyState(VK_LBUTTON) | GetAsyncKeyState(VK_RBUTTON) | GetAsyncKeyState(VK_MBUTTON)) & 0x8000)) {
                    POINT pt;
                    GetCursorPos(&pt);
                    if (Set_MenuIndexOf(WindowFromPoint(pt)) < 0) Set_MenuFinish(0);
                }
            }
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static int Set_TrayMenu(HWND owner, const std::vector<SetMenuItem>& items, const POINT* at = nullptr) {
    if (Set_MenuCur()) {  // A second right-click while open closes the first menu.
        Set_MenuFinish(0);
        return 0;
    }
    if (items.empty()) return 0;
    POINT pt{};
    if (at) pt = *at;
    else GetCursorPos(&pt);
    SetMenuSession session;
    if (!Set_MenuFormats(session)) return 0;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       (LPCWSTR)(void*)&Set_MenuProc, &session.inst);
    // One class per mod, even when several mods share a process.
    session.cls = L"SeamlessTrayMenu_" + std::to_wstring((unsigned long long)(uintptr_t)(void*)&Set_MenuProc);
    PCWSTR cls = session.cls.c_str();
    WNDCLASSEXW wc{sizeof(wc)};
    wc.hInstance = session.inst;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpfnWndProc = Set_MenuProc;
    wc.lpszClassName = cls;
    RegisterClassExW(&wc);
    session.radius = Set_MenuCornerRadius();
    Set_MenuCur() = &session;
    session.levels.push_back(std::make_unique<SetMenuLevel>());
    SetMenuLevel* root = session.levels[0].get();
    root->items = &items;
    if (!Set_MenuCreateWindow(session, *root, pt, nullptr, 0)) {
        Set_MenuCloseFrom(0);
        Set_MenuCur() = nullptr;
        UnregisterClassW(cls, session.inst);
        return 0;
    }
    BOOL animations = TRUE;
    SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &animations, 0);
    session.alpha = animations ? 0.0f : 1.0f;
    session.fadeStart = GetTickCount64();
    if (owner && IsWindow(owner)) SetForegroundWindow(owner);  // Windows' tray rule; lets the menu take the foreground.
    ShowWindow(root->hwnd, SW_SHOW);
    if (!SetForegroundWindow(root->hwnd)) {
        DWORD fg = GetWindowThreadProcessId(GetForegroundWindow(), nullptr), me = GetCurrentThreadId();
        if (fg && fg != me && AttachThreadInput(me, fg, TRUE)) {
            SetForegroundWindow(root->hwnd);
            AttachThreadInput(me, fg, FALSE);
        }
    }
    SetFocus(root->hwnd);
    if (animations) SetTimer(root->hwnd, kSetMenuTimerFade, 15, nullptr);
    SetTimer(root->hwnd, kSetMenuTimerPoll, 50, nullptr);
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
                Set_MenuKey(m.wParam);
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
                if (Set_MenuIndexOf(m.hwnd) < 0) {  // A click on another window of this thread closes the menu.
                    Set_MenuFinish(0);
                    continue;
                }
                session.pressed = true;
                break;
        }
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    int result = session.result;
    Set_MenuCloseFrom(0);
    Set_MenuCur() = nullptr;
    UnregisterClassW(cls, session.inst);
    if (owner && IsWindow(owner)) PostMessageW(owner, WM_NULL, 0, 0);
    return result;
}


static void Set_MakeFormats(SetWindow& w) {
    w.family = Set_ResolveFamily();
    w.iconFamily = Set_FamilyExists(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
    int base = std::clamp(500, 100, 900);
    int bold = std::max(base, std::min(700, base + 100));
    const auto L_ = DWRITE_TEXT_ALIGNMENT_LEADING, C_ = DWRITE_TEXT_ALIGNMENT_CENTER;
    w.fLabel = Set_Fmt(w.family, 16, base, true);
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Bulk Rename") <= railW) break;
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
    return !w.render && g_bruAnim && on;
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

// Boxes grow to fit their text, so no option, hotkey or value is ever cut off: a choice box fits
// its longest option, a hotkey or text box its value. A box never takes more than half the row;
// past that the dropdown list still shows every option in full. Text is measured only when it
// changes. Returns true when a width changed, so the page is laid out again.
static bool Set_FitBoxes(SetWindow& w) {
    if (!w.fValue) return false;
    bool changed = false;
    const float cap = std::floor(w.contentW * 0.5f);
    for (auto& f : w.fields) {
        float base, pad;
        std::wstring text;
        if (f.kind == SetField::Choice) {
            base = 200, pad = 46;  // 12 before the text, 30 for the arrow, 4 spare.
            for (const auto& o : f.options) text += std::wstring(o.second) + L'\n';
        } else if (f.kind == SetField::Hotkey) {
            base = 220, pad = 60;  // The key cap's own padding and the clear button.
            text = f.cur;
        } else if (f.kind == SetField::Text) {
            base = 280, pad = 26;
            text = f.cur;
        } else {
            continue;
        }
        if (f.fitText < 0 || text != f.fitFor) {
            float m = 0;
            if (f.kind == SetField::Choice) {
                for (const auto& o : f.options) m = std::max(m, Set_TextW(w.fValue.get(), o.second));
            } else {
                m = Set_TextW(w.fValue.get(), f.cur);
            }
            f.fitText = std::ceil(m);
            f.fitFor = text;
        }
        float want = std::min(std::max(base, f.fitText + pad), std::max(base, cap));
        if (fabsf(want - f.fitW) > 0.5f) {
            f.fitW = want;
            changed = true;
        }
    }
    return changed;
}

// ---- Layout -----------------------------------------------------------------

// The right-hand control's width, so the label column knows how much room it has.
static float Set_FitOr(const SetField& f, float base) { return f.fitW > 0 ? f.fitW : base; }

static float Set_ControlW(const SetField& f) {
    switch (f.kind) {
        case SetField::Check: return 40;
        case SetField::Choice: return Set_FitOr(f, 200);
        case SetField::Number: return f.max - f.min <= 100 ? 150 + 12 + 64 : 96;
        case SetField::Text: return Set_FitOr(f, 280);
        case SetField::Hotkey: return Set_FitOr(f, 220);
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

// A colour row needs 362 DIP for its hex box and chips; when that leaves the label under 200 DIP,
// the chips drop to a line of their own under the text.
constexpr float kSgcColorFullW = 362, kSgcLabelMinW = 200, kSgcChipLine = 30;
static bool ColorRowStacked(const SetField& f, float rowW) {
    return f.kind == SetField::Color && rowW - 2 * kSetRowPad - kSgcColorFullW - 24 < kSgcLabelMinW;
}
static float RowControlW(const SetField& f, float rowW) { return ColorRowStacked(f, rowW) ? 96 : Set_ControlW(f); }

static SetParts Set_Parts(const SetField& f, const D2D1_RECT_F& row) {
    SetParts p;
    float r = row.right - kSetRowPad, mid = (row.top + row.bottom) / 2, h = kSetBoxH / 2;
    switch (f.kind) {
        case SetField::Check:
            p.box = {r - 40, mid - 11, r, mid + 11};
            break;
        case SetField::Choice:
            p.box = {r - Set_FitOr(f, 200), mid - h, r, mid + h};
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
            p.box = {r - Set_FitOr(f, 280), mid - h, r, mid + h};
            break;
        case SetField::Hotkey:
            p.box = {r - Set_FitOr(f, 220), mid - h, r, mid + h};
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

struct SetPaint;
static float Bru_PaneW(const SetWindow&);
static float Bru_ThumbX(const SetWindow&);
static LONG Bru_MinSide(HWND, int, UINT, bool);
static void Bru_DrawPreview(SetPaint&, SetWindow&);
static void Bru_Link(PCWSTR);
static void Bru_Attach();
static std::wstring Bru_PresetLabel(int);

// A window too narrow for the open sidebar, the page and the rename list folds the sidebar to its icons by itself,
// and opens it again once there is room. Opening it by hand while narrow is respected until the window widens.
static bool g_bruRailAuto = false, g_bruRailKeep = false;
static void Bru_FitRail(SetWindow& w) {
    const bool narrow = w.cw < kSetDockGap + w.railW + 14 + 500 + 320;
    if (!narrow) {
        g_bruRailKeep = false;
        if (g_bruRailAuto) { g_bruRailAuto = false; w.railCollapsed = false; }
        return;
    }
    if (g_bruRailAuto && !w.railCollapsed) { g_bruRailAuto = false; g_bruRailKeep = true; }
    if (!w.railCollapsed && !g_bruRailKeep) { w.railCollapsed = true; g_bruRailAuto = true; }
}

// Lays out the current page's items for the current width. The rename list takes the right side of the window, so
// the page is centred in what is left of it.
static void Set_BuildPage(SetWindow& w) {
    w.items.clear();
    Bru_FitRail(w);
    const float space = Set_RailSpace(w), paneW = Bru_PaneW(w);
    const float avail = w.cw - space - paneW - (paneW > 0 ? 14 : 0);
    w.contentW = std::clamp(avail - 2 * kSetPadX, 420.0f, kSetMaxW);
    w.contentX = space + std::max(kSetPadX, (avail - w.contentW) / 2);
    float introH = Set_TextH(w.fIntro.get(), kSetPages[w.page].intro, w.contentW);
    float y = 36 + 36 + 4 + introH + 24;
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
        float dh = (f.desc && *f.desc) ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
        it.y = y;
        it.h = std::max(kSetRowMin, 28 + lh + dh);
        y += it.h + kSetRowGap;
        w.items.push_back(it);
    }
    auto add = [&](SetItem::Type t, float h, const std::wstring& text, const std::wstring& sub, const std::wstring& url) {
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
    if (w.page == 6) {
        group(L"Load");
        for (int n = 1; n <= 5; n++)
            add(SetItem::Link, 56, Bru_PresetLabel(n), L"Puts these rules in the boxes. Press Save to keep them",
                L"ren:load" + std::to_wstring(n));
        group(L"Save");
        for (int n = 1; n <= 5; n++)
            add(SetItem::Link, 56, L"Save to preset " + std::to_wstring(n),
                L"Keeps the rules you have now, under the name above", L"ren:save" + std::to_wstring(n));
    }
    if (w.page == kSetAboutPage) {
        add(SetItem::About, 146, L"", L"", L"");
        add(SetItem::Support, 84, L"Like it? Help the mod keep going.",
            L"Free and open source. A tip on Ko-fi keeps it moving.", kSetKofiUrl);
        group(L"Author");
        add(SetItem::Link, 56, L"DavidHiFi on GitHub", L"github.com/DavidHiFi", kSetAuthorUrl);
        add(SetItem::Link, 56, L"Ko-fi", L"ko-fi.com/DavidHiFi", kSetKofiUrl);
        group(L"Credits");
        add(SetItem::Link, 56, L"Built on PowerToys PowerRename", L"By Microsoft: the rename words and ideas",
            kSetCreditPowerToys);
        add(SetItem::Link, 56, L"Inspired by Bulk Rename Utility", L"By TGRMN Software. No code from it is used",
            kSetCreditBru);
        group(L"Project");
        add(SetItem::Link, 56, L"Project page on GitHub", L"github.com/DavidHiFi/seamless-workshop", kSetRepoUrl);
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
    return {Bru_ThumbX(w) - 18, top + 4, Bru_ThumbX(w) - 12, top + th - 4};
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
    const float rad = Set_Rad(box);
    p.Round(box, rad, kSetBoxFill);
    float g = std::max(Set_GlowOf(w, 6000 + k), active ? 1.0f : 0.0f);
    p.Edge(box, rad, mocha::overlay0, 0.7f * (1 - g));
    p.GradRing(box, rad, g);
}

static void Set_DrawRow(SetPaint& p, SetWindow& w, const SetItem& it) {
    const SetField& f = w.fields[it.field];
    int k = it.field;
    D2D1_RECT_F row = Set_RowRect(w, it);
    p.Round(row, kSetRadius, mocha::base);
    p.Round(row, kSetRadius, mocha::surface0, 0.32f);
    float hov = Set_GlowOf(w, 1000 + k);
    p.Edge(row, kSetRadius, mocha::surface2, 0.55f * (1 - hov));
    p.GradFill(row, kSetRadius, 0.13f * hov);
    p.GradRing(row, kSetRadius, hov);
    if (w.kbd && w.focus == k) p.GradRing(row, kSetRadius, 1.0f);

    float textW = w.contentW - 2 * kSetRowPad - Set_ControlW(f) - 24;
    float lh = Set_TextH(w.fLabel.get(), f.label, textW);
    float dh = (f.desc && *f.desc) ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
    float top = row.top + (it.h - lh - dh) / 2;
    p.Text(w.fLabel.get(), f.label, {row.left + kSetRowPad, top, row.left + kSetRowPad + textW, top + lh + 2}, mocha::text);
    if (f.desc && *f.desc)
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
    p.Round(row, kSetRadius, mocha::base);
    p.Round(row, kSetRadius, mocha::surface0, 0.32f);
    p.Edge(row, kSetRadius, mocha::surface2, 0.55f * (1 - hov));
}

static void Set_DrawLinkRow(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3000 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, kSetRadius, 0.13f * hov);
    p.GradRing(row, kSetRadius, hov);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 9, row.right - 50, row.top + 30}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 30, row.right - 50, row.bottom - 4}, mocha::subtext0);
    p.Glyph(w.fIcon.get(), 0xE8A7, {row.right - 46, row.top, row.right - 12, row.bottom}, mocha::subtext1);
}

static void Set_DrawSupport(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float card = std::max(Set_GlowOf(w, 3700 + idx), Set_GlowOf(w, 3500 + idx));
    Set_DrawCard(p, row, card);
    p.GradFill(row, kSetRadius, 0.13f * card);
    p.GradRing(row, kSetRadius, card);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 14, row.right - 180, row.top + 36}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 38, row.right - 180, row.bottom - 6}, mocha::subtext0);
    D2D1_RECT_F b = Set_SupportButton(w, it);
    float hov = Set_GlowOf(w, 3500 + idx);
    p.GradFill(b, Set_Rad(b), 0.85f + 0.15f * hov);
    p.GradRing(b, Set_Rad(b), hov);
    p.Text(w.fButton.get(), L"Open Ko-fi", b, mocha::crust);
}

static void Set_DrawAbout(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3800 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    D2D1_RECT_F mark{row.left + 20, row.top + 20, row.left + 92, row.top + 92};
    {  // The glyph alone in the gradient, no plate (owner, 2026-11-24).
        D2D1_MATRIX_3X2_F old;
        p.rt->GetTransform(&old);
        const D2D1_POINT_2F mc{(mark.left + mark.right) / 2, (mark.top + mark.bottom) / 2};
        p.rt->SetTransform(D2D1::Matrix3x2F::Scale(1.75f, 1.75f, mc) * old);
        const WCHAR glyph = 0xE8AC;
        auto br = p.G({mc.x - 19, mc.y - 19, mc.x + 19, mc.y + 19});
        if (br) p.rt->DrawText(&glyph, 1, w.fIconL.get(), mark, br.get());
        p.rt->SetTransform(old);
    }
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Bulk Rename", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Rename many files at once: stacked rules, a live preview and undo.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, built on PowerToys PowerRename.",
           {x, row.top + 112, row.right - 16, row.bottom - 8}, mocha::overlay2);
}

static void Set_DrawBanner(SetPaint& p, SetWindow& w, const SetItem& it) {
    D2D1_RECT_F r = Set_RowRect(w, it);
    p.Round(r, kSetRadius, mocha::peach, 0.14f);
    p.Text(w.fHint.get(), it.text, {r.left + 16, r.top + 14, r.right - 16, r.bottom - 8}, mocha::peach);
}

// A floating dock: soft shadow, mantle fill, a quiet 1px edge at rest and the blue to mauve
// edge as the pointer comes over it.
static void Set_DrawDock(SetPaint& p, SetWindow& w, const D2D1_RECT_F& d, float rad, float fill, float glow) {
    p.Round({d.left, d.top + 3, d.right, d.bottom + 5}, rad + 2, mocha::crust, w.glass ? 0.28f : 0.5f);
    p.Round(d, rad, mocha::mantle, fill);  // Hover lights only the edge: a wash showed as a blue blob down the left.
    p.Edge(d, rad, mocha::surface1, 0.75f * (1 - glow));
    p.GradRing(d, rad, glow);
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
    Set_DrawDock(p, w, d, kSetRadius, w.glass ? 0.58f : 1.0f, std::max(w.railGlow * 0.85f, edge));

    D2D1_RECT_F tb = Set_RailToggleRect(w);
    float th = Set_GlowOf(w, 42);
    const float tr = Set_Rad(tb);
    p.Round(tb, tr, mocha::surface0, 0.45f + 0.25f * th);
    p.GradFill(tb, tr, 0.16f * th);
    p.GradRing(tb, tr, 0.9f * th);
    if (w.kbd && w.focus == -20) p.GradRing(tb, tr, 1);
    Set_DrawPanelIcon(p, tb, open, th > 0.5f ? mocha::text : mocha::subtext1);

    p.rt->PushAxisAlignedClip(D2D1::RectF(d.left, d.top, d.right - 6, d.bottom), D2D1_ANTIALIAS_MODE_ALIASED);
    if (textA > 0.003f) {
        float my = (tb.top + tb.bottom) / 2;
        Set_DrawMark(p, w.fIcon.get(), {d.left + 56, my - 13, d.left + 82, my + 13}, textA);
    }
    p.Text(w.fRailName.get(), L"Seamless", {d.left + 90, d.top + 9, d.left + w.railW - 10, d.top + 33}, mocha::text, textA);
    p.Text(w.fRailName.get(), L"Bulk Rename", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
    for (int i = 0; i < kSetPageCount; i++) {
        D2D1_RECT_F r = Set_RailRect(w, i);
        if (i == kSetAboutPage) {
            float ly = std::round(r.top - (kSetAboutGap + kSetRailPitch - kSetRailItem) / 2);
            p.Fill({r.left + 6, ly, r.right - 6, ly + 1}, mocha::surface1, 0.7f);
        }
        float hov = Set_GlowOf(w, 100 + i);
        bool act = i == w.page;
        const float rr = Set_Rad(r);
        if (act) {
            p.GradFill(r, rr, 0.22f);
            p.GradRing(r, rr, 0.5f);
            D2D1_RECT_F bar{r.left, r.top + 8, r.left + 3, r.bottom - 8};
            p.GradFill({bar.left, bar.top, bar.left + 3, bar.bottom}, 1.5f, 1);
        } else {
            p.Round(r, rr, mocha::surface0, 0.28f);
            p.Edge(r, rr, mocha::surface2, 0.5f * (1 - hov));
            p.GradFill(r, rr, 0.10f * hov);
            p.GradRing(r, rr, 0.8f * hov);
        }
        if (w.kbd && w.focus == -10 - i) p.GradRing(r, rr, 1);
        UINT32 c = act ? mocha::text : mocha::subtext1;
        // The glyph sits in a fixed 44-wide slot, so it stays centered in the collapsed rail.
        p.Glyph(w.fIcon.get(), kSetPages[i].glyph, {r.left, r.top, r.left + 44, r.bottom}, act ? mocha::blue : mocha::subtext0);
        p.Text(w.fValue.get(), kSetPages[i].name, {r.left + 50, r.top, r.left + w.railW - 24, r.bottom}, c, textA);
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
    // The same see-through mantle as the rail dock, so the blurred rows under the pill read as
    // real glass instead of a near-solid bar.
    p.Round(d, rad, mocha::mantle, w.render ? 1.0f : (w.glass ? 0.58f : 0.85f));
    p.Edge(d, rad, mocha::overlay0, 0.9f * (1 - w.footGlow));
    p.GradRing(d, rad, w.footGlow);
    UINT32 sc;
    std::wstring status = Set_FooterStatus(w, &sc);
    float sw = Set_FooterStatusW(w);
    if (sw > 0) p.Text(w.fStatusLine.get(), status, {d.left + 18, d.top, d.left + 18 + sw, d.bottom}, sc);
    static const PCWSTR names[3] = {L"Reset to suggested", L"Cancel", L"Save"};
    for (int i = 0; i < 3; i++) {
        D2D1_RECT_F b = Set_FooterButton(w, i);
        float hov = Set_GlowOf(w, 10 + i);
        p.Round(b, brad, mocha::base, 0.98f);
        p.Edge(b, brad, mocha::overlay0, 0.78f * (1 - hov));
        p.GradRing(b, brad, hov);
        p.Text(w.fButton.get(), names[i], b, mocha::text, w.saving ? 0.5f : 1.0f);
        if (w.kbd && w.focus == -1 - i) p.GradRing(b, brad, 1);
    }
}


// Every scrollbar thumb in every mod: a top to bottom blue to mauve gradient, brighter while
// hovered or dragged. Never a flat grey thumb.
static void Set_ThumbFill(SetPaint& p, const D2D1_RECT_F& r, float a) {
    if (r.bottom <= r.top) return;
    float rad = (r.right - r.left) / 2;
    SetCom<ID2D1LinearGradientBrush> g;
    D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::blue, a * p.fade)}, {1, D2DColor(mocha::mauve, a * p.fade)}};
    SetCom<ID2D1GradientStopCollection> coll;
    if (SUCCEEDED(p.rt->CreateGradientStopCollection(stops, 2, coll.put())) &&
        SUCCEEDED(p.rt->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, r.top), D2D1::Point2F(r.left, r.bottom)),
            coll.get(), g.put())))
        p.rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), g.get());
}

static int Set_DropVisible(const SetWindow& w) {
    return w.openSel < 0 ? 0 : std::min((int)w.fields[w.openSel].options.size(), kSetDropMax);
}

// Keeps option i inside the visible part of a scrolling dropdown.
static void Set_DropShow(SetWindow& w, int i) {
    int vis = Set_DropVisible(w), n = w.openSel < 0 ? 0 : (int)w.fields[w.openSel].options.size();
    if (i < 0 || vis <= 0) return;
    if (i < w.dropTop) w.dropTop = i;
    if (i >= w.dropTop + vis) w.dropTop = i - vis + 1;
    w.dropTop = std::clamp(w.dropTop, 0, std::max(0, n - vis));
}

static void Set_DrawPopup(SetPaint& p, SetWindow& w) {
    if (w.openSel < 0) return;
    const SetField& f = w.fields[w.openSel];
    const D2D1_RECT_F& r = w.dropRect;
    const int n = (int)f.options.size(), vis = Set_DropVisible(w);
    const bool scrolls = n > vis;
    D2D1_RECT_F shadow{r.left - 1, r.top + 3, r.right + 1, r.bottom + 5};
    p.Round(shadow, kSetRadius + 2, mocha::crust, 0.6f);
    p.Round(r, kSetRadius, mocha::mantle);
    p.GradRing(r, kSetRadius, 0.9f);
    const float right = r.right - (scrolls ? 12 : 4);
    for (int v = 0; v < vis; v++) {
        int i = w.dropTop + v;
        if (i >= n) break;
        D2D1_RECT_F it{r.left + 4, r.top + 4 + v * kSetDropItem, right, r.top + 4 + (v + 1) * kSetDropItem};
        bool sel = f.cur == f.options[i].first;
        if (i == w.dropHover) {
            p.GradFill(it, Set_Rad(it, kSetRadius - 4), 0.28f);  // Inset 4 in a 16 corner: 12.
            p.GradRing(it, Set_Rad(it, kSetRadius - 4), 0.6f);
        }
        p.Text(w.fValue.get(), f.options[i].second, {it.left + 10, it.top, it.right - 28, it.bottom}, sel ? mocha::blue : mocha::text);
        if (sel) p.Glyph(w.fIconS.get(), 0xE73E, {it.right - 28, it.top, it.right - 6, it.bottom}, mocha::blue);
    }
    if (scrolls) {
        float track = r.bottom - r.top - 12, th = std::max(24.0f, track * vis / n);
        float top = r.top + 6 + (track - th) * w.dropTop / std::max(1, n - vis);
        Set_ThumbFill(p, {r.right - 9, top, r.right - 5, top + th}, 0.85f);
    }
}

// Title bar buttons, in title bar DIPs: 0 minimize, 1 maximize or restore, 2 close.
static D2D1_RECT_F Set_CapButton(const SetWindow& w, int i) {
    float right = w.cw - (2 - i) * kSetCapBtnW;
    return {right - kSetCapBtnW, 0, right, kSetCapH};
}

// y is in content DIPs, so the title bar is y < 0.
static int Set_CapButtonAt(const SetWindow& w, float x, float y) {
    if (w.nativeTitle) return -1;
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
    // The mod's glyph alone in the blue to mauve gradient on a clear background, no plate
    // (owner, 2026-11-24), scaled up about its centre to fill the room the plate had.
    const float cx = (r.left + r.right) / 2, cy = (r.top + r.bottom) / 2;
    const float ix = (r.right - r.left) * 0.31f, iy = (r.bottom - r.top) * 0.31f;
    SetCom<ID2D1LinearGradientBrush> g;
    D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::blue, a * p.fade)}, {1, D2DColor(mocha::mauve, a * p.fade)}};
    SetCom<ID2D1GradientStopCollection> coll;
    if (FAILED(p.rt->CreateGradientStopCollection(stops, 2, coll.put())) ||
        FAILED(p.rt->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(D2D1::Point2F(cx - ix, cy - iy), D2D1::Point2F(cx + ix, cy + iy)),
            coll.get(), g.put())))
        return;
    D2D1_MATRIX_3X2_F old;
    p.rt->GetTransform(&old);
    p.rt->SetTransform(D2D1::Matrix3x2F::Scale(1.4f, 1.4f, D2D1::Point2F(cx, cy)) * old);
    const WCHAR mark = 0xE8AC;
    p.rt->DrawText(&mark, 1, glyph, r, g.get());
    p.rt->SetTransform(old);
}

static void Set_DrawCaption(SetPaint& p, SetWindow& w) {
    if (!w.glass) p.Fill({0, 0, w.cw, kSetCapH}, mocha::crust);  // Glass: the window tint already covers it.
    D2D1_RECT_F t = Set_CapTitleRect(w);
    float mid = kSetCapH / 2;
    Set_DrawMark(p, w.fCapGlyph.get(), {t.left, mid - 8, t.left + 16, mid + 8}, w.active ? 1.0f : 0.6f);
    p.Text(w.fCap.get(), kSetTitle, {t.left + 24, 0, t.right, kSetCapH}, w.active ? mocha::text : mocha::overlay1);
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
static void Set_PlaceEdit(SetWindow& w);

static void Set_DrawAutoScroll(SetPaint& p, SetWindow& w, bool frosted) {
    if (w.autoA <= 0.003f) return;
    const float a = w.autoA, s = 0.8f + 0.2f * a, r = kSetAutoR * s, cx = w.autoX, cy = w.autoY;
    const D2D1_RECT_F disc{cx - r, cy - r, cx + r, cy + r};
    p.Round(disc, r, mocha::mantle, (frosted ? 0.86f : 1.0f) * a);  // Opaque when nothing blurs under it.
    p.GradRing(disc, r - 1, a, 2);
    auto arrow = [&](float dir, bool lit) {
        SetCom<ID2D1PathGeometry> g;
        SetCom<ID2D1GeometrySink> k;
        if (FAILED(g_setD2d->CreatePathGeometry(g.put())) || FAILED(g->Open(k.put()))) return;
        const float tip = cy + dir * r * 0.62f, foot = cy + dir * r * 0.30f, half = r * 0.22f;
        k->BeginFigure(D2D1::Point2F(cx, tip), D2D1_FIGURE_BEGIN_FILLED);
        k->AddLine(D2D1::Point2F(cx + half, foot));
        k->AddLine(D2D1::Point2F(cx - half, foot));
        k->EndFigure(D2D1_FIGURE_END_CLOSED);
        if (SUCCEEDED(k->Close())) p.rt->FillGeometry(g.get(), p.B(lit ? mocha::blue : mocha::overlay1, a));
    };
    arrow(-1, w.autoDir < 0);
    arrow(1, w.autoDir > 0);
    const float d = 2.5f * s;
    p.Round({cx - d, cy - d, cx + d, cy + d}, d, mocha::mauve, a);
}

static void Set_Draw(SetWindow& w, ID2D1RenderTarget* rt) {
    if (Set_FitBoxes(w)) {
        Set_BuildPage(w);
        Set_PlaceEdit(w);
    }
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
            // The window's acrylic already carries the tint (Set_ApplyFrame), title bar included.
        } else if (false) {
            SetCom<ID2D1LinearGradientBrush> fade;
            D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::crust, kSetGlassTint)}, {1, D2DColor(mocha::crust, kSetGlassTint)}};
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
                if (w.autoA > 0.003f) {  // The autoscroll disc frosts the rows under it the same way.
                    const float r = kSetAutoR * (0.8f + 0.2f * w.autoA), cx = w.autoX, cy = w.autoY + kSetCapH;
                    SetCom<ID2D1EllipseGeometry> disc;
                    if (SUCCEEDED(g_setD2d->CreateEllipseGeometry(D2D1::Ellipse(D2D1::Point2F(cx, cy), r, r), disc.put()))) {
                        rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), disc.get()), nullptr);
                        D2D1_RECT_F ds{cx - r - 1, cy - r - 1, cx + r + 1, cy + r + 1};
                        dc->DrawImage(blur.get(), D2D1::Point2F(ds.left, ds.top), ds);
                        rt->PopLayer();
                    }
                }
                blurred = true;
            }
        }
    }
    if (!blurred) drawPage(p);
    rt->SetTransform(base);

    D2D1_RECT_F th = Set_ScrollThumb(w);
    Set_ThumbFill(p, th, w.dragScroll || w.hover.kind == SetHit::Scroll ? 1.0f : 0.7f);

    Bru_DrawPreview(p, w);
    Set_DrawFooter(p, w);
    Set_DrawRail(p, w);
    Set_DrawPopup(p, w);
    Set_DrawAutoScroll(p, w, blurred);
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
            int v = (int)((y - w.dropRect.top - 4) / kSetDropItem), i = w.dropTop + v;
            if (v >= 0 && v < Set_DropVisible(w) && i < (int)w.fields[w.openSel].options.size() &&
                y >= w.dropRect.top + 4 && x < w.dropRect.right - (Set_DropVisible(w) < (int)w.fields[w.openSel].options.size() ? 12 : 4)) {
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
    if (th.bottom > th.top && x >= Bru_ThumbX(w) - 16 && y >= th.top && y <= th.bottom) {
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

static std::wstring Set_FormatHotkey(UINT mods, UINT vk) { return ::Hotkey_Format(mods, vk); }

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
    
    Set_Invalidate(w);
}

static void Set_StartRecording(SetWindow& w, int k) {
    Set_StopRecording(w);
    w.recording = k;
    // Our own keys would fire instead of reaching the window while it listens.
    if (!w.render) {
        SetFocus(w.hwnd);
    }
    Set_SetStatus(w, L"Press the keys you want. Esc cancels, Backspace clears.");
}

static void Set_ClosePopup(SetWindow& w) {
    if (w.openSel < 0) return;
    w.openSel = -1;
    w.dropHover = -1;
    w.dropTop = 0;
    Set_Invalidate(w);
}

static void Set_OpenPopup(SetWindow& w, int k) {
    const SetItem* it = Set_ItemOfField(w, k);
    if (!it) return;
    const SetField& f = w.fields[k];
    SetParts pt = Set_Parts(f, Set_RowRect(w, *it));
    float boxTop = pt.box.top - w.scrollY, boxBottom = pt.box.bottom - w.scrollY;
    const int n = (int)f.options.size(), vis = std::min(n, kSetDropMax);
    float h = (float)vis * kSetDropItem + 8;
    float top = boxBottom + 4;
    if (top + h > Set_ViewH(w) + 20 && boxTop - 4 - h > 0) top = boxTop - 4 - h;  // No room below: open upward.
    // As wide as the longest option (text, check mark, scrollbar), growing leftward from the box.
    float textW = 0;
    for (const auto& o : f.options) textW = std::max(textW, Set_TextW(w.fValue.get(), o.second));
    float width = std::max(pt.box.right - pt.box.left, std::ceil(textW) + 52 + (n > vis ? 8 : 0));
    float left = std::max(pt.box.right - width, Set_RailSpace(w) + 8);
    w.dropRect = {left, top, std::max(pt.box.right, left + width), top + h};
    w.openSel = k;
    w.dropHover = -1;
    w.dropTop = 0;
    for (int i = 0; i < n; i++)
        if (f.cur == f.options[i].first) w.dropHover = i;
    Set_DropShow(w, w.dropHover);
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
                             GetModuleHandleW(nullptr), nullptr);
    if (!w.edit) return;
    if (w.glass) SetLayeredWindowAttributes(w.edit, 0, 255, LWA_ALPHA);
    int base = std::clamp(500, 100, 900);
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
    if (wcsncmp(url, L"ren:", 4) == 0) { Bru_Link(url + 4); return; }
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
            changed++;
        }
    }
    return params;
}

static void Set_ApplyFrame(SetWindow& w);

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
        Set_ApplyFrame(w);  // The title bar and glass switches take effect now, no reopen.
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

static bool Set_AutoScrollStart(SetWindow& w, float x, float y) {
    if (w.render || w.contentH - Set_ViewH(w) <= 0) return false;  // Nothing to scroll.
    Set_CommitEdit(w, true);
    Set_ClosePopup(w);
    w.autoScroll = true;
    w.autoMoved = false;
    w.autoX = x, w.autoY = y, w.autoDir = 0;
    w.hover = SetHit();
    SetCapture(w.hwnd);
    SetCursor(LoadCursorW(nullptr, IDC_SIZENS));
    Set_Invalidate(w);
    return true;
}

static void Set_AutoScrollStop(SetWindow& w) {
    if (!w.autoScroll) return;
    w.autoScroll = false;  // Before ReleaseCapture: its WM_CAPTURECHANGED comes straight back here.
    w.autoDir = 0;
    if (GetCapture() == w.hwnd) ReleaseCapture();
    Set_Invalidate(w);
}

static void Set_AutoScrollMove(SetWindow& w, bool held) {
    if (held && fabsf(w.mouseY - w.autoY) > kSetAutoDead) w.autoMoved = true;
    SetCursor(LoadCursorW(nullptr, IDC_SIZENS));
}

static bool Set_AutoScrollStep(SetWindow& w) {
    if (!w.autoScroll) return false;
    const float dy = w.mouseY - w.autoY, dist = fabsf(dy) - kSetAutoDead;
    const float dir = dist > 0 ? (dy > 0 ? 1.0f : -1.0f) : 0.0f;
    bool changed = dir != w.autoDir;
    w.autoDir = dir;
    if (dist <= 0) return changed;
    const float maxScroll = std::max(0.0f, w.contentH - Set_ViewH(w));
    const float next = std::clamp(w.scrollY + dir * std::min(kSetAutoMax, dist * kSetAutoGain), 0.0f, maxScroll);
    if (next == w.scrollY) return changed;
    w.scrollY = w.scrollTarget = next;
    Set_PlaceEdit(w);
    return true;
}

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
    if (Set_AutoScrollStep(w)) moved = true;
    step(w.autoA, w.autoScroll ? 1.0f : 0.0f, 0.3f);
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
        else if (vk == VK_UP) Set_DropShow(w, w.dropHover = w.dropHover < 0 ? n - 1 : (w.dropHover - 1 + n) % n);
        else if (vk == VK_DOWN) Set_DropShow(w, w.dropHover = w.dropHover < 0 ? 0 : (w.dropHover + 1) % n);
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

// A switch's stored value, found by the end of its key so a "SettingsWindow." prefix still matches.
static bool Set_FieldOn(const SetWindow& w, PCWSTR key, bool def) {
    // The window group wins over a module option with the same suffix.
    const std::wstring windowKey = std::wstring(L"SettingsWindow.") + key;
    for (const auto& f : w.fields)
        if (windowKey == f.key) return f.value == L"1";
    for (const auto& f : w.fields)
        if (wcscmp(f.key, key) == 0) return f.value == L"1";
    const size_t n = wcslen(key);
    for (const auto& f : w.fields) {
        const size_t m = wcslen(f.key);
        if (m >= n && wcscmp(f.key + m - n, key) == 0 && (m == n || f.key[m - n - 1] == L'.')) return f.value == L"1";
    }
    return def;
}

// "Native Windows title bar" and "Blurred settings window", applied to the live window: on first
// open and again whenever a save or a reload changes them, so neither needs a reopen.
static void Set_ApplyFrame(SetWindow& w) {
    if (w.render || !w.hwnd) return;
    const HWND hwnd = w.hwnd;
    const bool native = Set_FieldOn(w, L"nativeSettingsTitleBar", false), glass = Set_FieldOn(w, L"settingsGlass", true);
    const bool first = !w.frameApplied, wasGlass = w.glass;
    if (!first && native == w.nativeTitle && glass == w.glass) return;  // A title bar switch re-runs the accent below.
    w.frameApplied = true;
    w.nativeTitle = native;
    w.glass = glass;
    kSetCapH = native ? 0.0f : 40.0f;
    struct SetAccentPolicy { int state, flags, abgr, animation; };
    struct SetCompositionData { DWORD attribute; void* data; SIZE_T size; };
    using SetComposition_t = BOOL(WINAPI*)(HWND, SetCompositionData*);
    auto setComposition =
        (SetComposition_t)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    if (glass) {
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
        if (setComposition) {
            // Same as the launcher grid. With the Windows title bar the tint is in here instead of
            // on the page, so the title bar gets it too: crust at the page's 55%.
            const int tint = native ? (int)(((DWORD)(kSetGlassTint * 255 + 0.5f) << 24) | (mocha::crust & 0xFF) << 16 |
                                            (mocha::crust & 0xFF00) | (mocha::crust >> 16 & 0xFF))
                                    : (int)0x012E1E1E;
            SetAccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, tint, 0};
            SetCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
            setComposition(hwnd, &data);
        }
        MARGINS margins{-1, -1, -1, -1};
        DwmExtendFrameIntoClientArea(hwnd, &margins);
        COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE
        DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
    } else if (wasGlass) {
        // Glass switched off while open: back to a plain solid window.
        if (setComposition) {
            SetAccentPolicy policy{0, 0, 0, 0};
            SetCompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
            setComposition(hwnd, &data);
        }
        DWM_BLURBEHIND bb{};
        bb.dwFlags = DWM_BB_ENABLE;
        bb.fEnable = FALSE;
        DwmEnableBlurBehindWindow(hwnd, &bb);
        MARGINS margins{0, 0, 0, 0};
        DwmExtendFrameIntoClientArea(hwnd, &margins);
        int backdrop = 0;  // DWMSBT_AUTO
        DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
        COLORREF caption = RefFromRgb(mocha::crust);
        DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &caption, sizeof(caption));
    }
    // With the frame extended DWM would draw its own minimize, maximize and close buttons over the
    // built-in title bar; without a system menu it draws none. The Windows title bar keeps it.
    // Minimize, maximize and close still work from the taskbar either way.
    LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);
    SetWindowLongPtrW(hwnd, GWL_STYLE, native ? (style | WS_SYSMENU) : (style & ~WS_SYSMENU));
    // Set_WndProc's WM_NCCALCSIZE drops or keeps the system title bar to match.
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    if (!first) {
        Set_Relayout(w);
        RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW);
    }
}

static void Set_RememberRect(SetWindow& w) {
    if (w.render || IsIconic(w.hwnd) || IsZoomed(w.hwnd)) return;
    GetWindowRect(w.hwnd, &w.normalRect);
}

static LRESULT CALLBACK Set_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetWindow* w = g_setWin && g_setWin->hwnd == hwnd ? g_setWin.get() : nullptr;
    if (!w) return DefWindowProcW(hwnd, msg, wParam, lParam);
    if (w->nativeTitle) {
        LRESULT r = 0;
        if (DwmDefWindowProc(hwnd, msg, wParam, lParam, &r)) return r;  // Hover and clicks on DWM's buttons.
    }
    auto dipX = [&](LPARAM l) { return (float)(short)LOWORD(l) * 96.0f / w->dpi; };
    auto dipY = [&](LPARAM l) { return (float)(short)HIWORD(l) * 96.0f / w->dpi - kSetCapH; };
    switch (msg) {
        case WM_APP_SETTINGS_RELOAD:
            if (!w->saving) {
                Set_LoadFields(*w);
                Set_ApplyFrame(*w);
            }
            return 0;
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
            if (!w->active) Set_AutoScrollStop(*w);
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
            RECT r{0, 0, Bru_MinSide(hwnd, 1180, w->dpi, false), Bru_MinSide(hwnd, 640, w->dpi, true)};
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
            if (w->autoScroll) {
                Set_AutoScrollMove(*w, (wParam & MK_MBUTTON) != 0);
                return 0;
            }
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
            if (!w->dragRail && !w->autoScroll) w->mouseX = w->mouseY = -1;
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
            if (w->autoScroll) {  // A click ends autoscroll and does nothing else.
                Set_AutoScrollStop(*w);
                return 0;
            }
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
            if (msg == WM_CAPTURECHANGED && w->autoScroll && (HWND)lParam != hwnd) Set_AutoScrollStop(*w);
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
        case WM_MBUTTONDOWN:
            if (w->saving) return 0;
            if (w->autoScroll) Set_AutoScrollStop(*w);  // Toggle mode: the next middle click ends it.
            else Set_AutoScrollStart(*w, dipX(lParam), dipY(lParam));
            return 0;
        case WM_MBUTTONUP:
            if (w->autoScroll && w->autoMoved) Set_AutoScrollStop(*w);  // Held and dragged: stop on release.
            return 0;
        case WM_RBUTTONDOWN:
        case WM_XBUTTONDOWN:
            if (w->autoScroll) {
                Set_AutoScrollStop(*w);
                return msg == WM_XBUTTONDOWN ? TRUE : 0;
            }
            break;
        case WM_MOUSEWHEEL: {
            Set_AutoScrollStop(*w);
            if (w->openSel >= 0 && Set_In(w->dropRect, w->mouseX, w->mouseY)) {
                int n = (int)w->fields[w->openSel].options.size(), vis = Set_DropVisible(*w);
                int step = GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? -3 : 3;
                w->dropTop = std::clamp(w->dropTop + step, 0, std::max(0, n - vis));
                SetHit h = Set_Hit(*w, w->mouseX, w->mouseY);
                w->hover = h;
                w->dropHover = h.kind == SetHit::Drop ? h.b : w->dropHover;
                Set_Invalidate(*w);
                return 0;
            }
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
            if (w->autoScroll) {  // Any key ends autoscroll; Escape does nothing else.
                Set_AutoScrollStop(*w);
                if (wParam == VK_ESCAPE) return 0;
            }
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
            RemovePropW(hwnd, kSetAutoProp);
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
                SetState(StateKey(L"Settings", L"RailCollapsed").c_str(), (w->railCollapsed && !g_bruRailAuto) ? 1 : 0);
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
    // The built-in title bar until Set_ApplyFrame reads the switches.
    kSetCapH = 40.0f;
    const DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Bulk Rename settings", style,
                                render ? offX : CW_USEDEFAULT, render ? offY : CW_USEDEFAULT, 800, 600, w->owner,
                                nullptr, (HINSTANCE)&__ImageBase, nullptr);
    if (!hwnd) {
        g_setWin.reset();
        return false;
    }
    w->hwnd = hwnd;
    SetPropW(hwnd, kSetAutoProp, (HANDLE)1);  // Seamless Autoscroll leaves this window to Set_AutoScroll*.
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
        Set_ApplyFrame(*w);  // Title bar and glass; also drops the system title bar the first WM_NCCALCSIZE kept.
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
    outer(1320, 780, size);
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
 if (g_settingsStop && g_settingsWnd) PostMessageW(g_settingsWnd,WM_CLOSE,0,0);  // closed while opening
 if (g_setWin) Bru_Attach();
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
// ---- The rename list ------------------------------------------------------------------------------------------------
// A dock on the right of the settings window: the files, their names now and after the rules, and the Rename button.
// The rule cards on the left are the settings pages, so every change shows in the list straight away.

static constexpr UINT WM_APP_BRU_TAKE = WM_APP + 60, WM_APP_BRU_UNDO = WM_APP + 61, WM_APP_BRU_DONE = WM_APP + 62;
static constexpr UINT_PTR kBruTimer = 0xB0, kBruSubclass = 0xB1;
static constexpr float kBruRowH = 28;

struct BruPane {
    bru::List list;
    bru::Counts counts;
    std::wstring sig, sortSig;
    uint32_t seed = 0;
    int version = 0, builtVersion = -1;
    bool needSort = false;
    float scroll = 0, scrollTarget = 0;
    bool dragThumb = false;
    float dragOff = 0;
    std::map<int, float> glow;
    int hover = -1;
    bool tracking = false;
    bool busy = false, lastCopy = false, canUndo = false, timer = false;
    DWORD confirmUntil = 0;
    std::wstring status;
    bool statusError = false;
    SetCom<IDWriteTextFormat> fCenter;
};
static BruPane* g_pane = nullptr;
static HANDLE g_bruWorker = nullptr;
[[clang::no_destroy]] static std::mutex g_bruQueueLock;
[[clang::no_destroy]] static std::vector<std::pair<std::vector<std::wstring>, bool>> g_bruQueue;
static std::atomic<bool> g_bruUndoPending{false};

static const WCHAR kBruPillGlyph[4] = {0xE8E5, 0xE8F4, 0xE74D, 0xE7A7};
static const PCWSTR kBruPillText[4] = {L"Add files", L"Add folder", L"Clear", L"Undo"};
static const PCWSTR kBruRuleKeys[] = {L"rep.", L"ch.", L"nm.", L"cs.", L"rm.", L"mv.", L"add.", L"dt.",
                                      L"fd.", L"num.", L"ext.", L"f.", L"fdt.", L"at.", L"cp."};

static bool Bru_IsRuleKey(PCWSTR key) {
    for (PCWSTR p : kBruRuleKeys)
        if (wcsncmp(key, p, wcslen(p)) == 0) return true;
    return false;
}

// What a setting says right now in the window, with the box being typed in read as it is typed.
static std::wstring Bru_Get(const SetWindow& w, PCWSTR key) {
    for (size_t k = 0; k < w.fields.size(); k++) {
        const SetField& f = w.fields[k];
        if (wcscmp(f.key, key) != 0) continue;
        if ((int)k == w.editing && w.edit && (f.kind == SetField::Text || f.kind == SetField::Number)) {
            std::wstring t = Set_WindowText(w.edit);
            if (f.kind == SetField::Number)
                return t.empty() ? Set_FieldValue(f) : std::to_wstring(std::clamp(_wtoi(t.c_str()), f.min, f.max));
            return t;
        }
        return Set_FieldValue(f);
    }
    return SettingString(key);
}

static bru::Getter Bru_Getter(const SetWindow& w) {
    return [&w](PCWSTR key) { return Bru_Get(w, key); };
}

static std::wstring Bru_Files(int n) { return std::to_wstring(n) + (n == 1 ? L" file" : L" files"); }

// ---- Layout ---------------------------------------------------------------------------------------------------------

static float Bru_PaneW(const SetWindow& w) {
    return std::clamp(w.cw - Set_RailSpace(w) - 14 - 560, 320.0f, 640.0f);
}

static float Bru_ThumbX(const SetWindow& w) { return w.cw - Bru_PaneW(w) - 24; }

// The smallest the window may get, but never more than most of the screen it is on, so a small screen still
// shows the whole window and its Rename button.
static LONG Bru_MinSide(HWND hwnd, int want, UINT dpi, bool tall) {
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST), &mi);
    LONG room = tall ? mi.rcWork.bottom - mi.rcWork.top : mi.rcWork.right - mi.rcWork.left;
    return std::min<LONG>(MulDiv(want, dpi, 96), room * 9 / 10);
}

static D2D1_RECT_F Bru_Pane(const SetWindow& w) {
    float pw = Bru_PaneW(w);
    return {w.cw - pw - 10, 10, w.cw - 10, w.ch - 10};
}

static D2D1_RECT_F Bru_ListRect(const SetWindow& w) {
    D2D1_RECT_F P = Bru_Pane(w);
    return {P.left + 8, P.top + 146, P.right - 8, P.bottom - 100};
}

static D2D1_RECT_F Bru_RenameRect(const SetWindow& w) {
    D2D1_RECT_F P = Bru_Pane(w);
    return {P.left + 20, P.bottom - 62, P.right - 20, P.bottom - 18};
}

struct BruPills {
    D2D1_RECT_F r[4];
    bool label[4];
};

static BruPills Bru_Pills(const SetWindow& w) {
    D2D1_RECT_F P = Bru_Pane(w);
    BruPills b{};
    float left = P.left + 20, avail = P.right - 20 - left, gap = 8, tw[4];
    for (int i = 0; i < 4; i++) {
        b.label[i] = true;
        tw[i] = (w.fSmall ? Set_TextW(w.fSmall.get(), kBruPillText[i]) : 60) + 12 + 16 + 8 + 14;
    }
    auto total = [&] {
        float s = gap * 3;
        for (int i = 0; i < 4; i++) s += b.label[i] ? tw[i] : 32;
        return s;
    };
    if (total() > avail) b.label[2] = b.label[3] = false;
    if (total() > avail) b.label[0] = b.label[1] = false;
    float x = left;
    for (int i = 0; i < 4; i++) {
        float wd = b.label[i] ? tw[i] : 32;
        b.r[i] = {x, P.top + 76, x + wd, P.top + 108};
        x += wd + gap;
    }
    return b;
}

static float Bru_MaxScroll(const SetWindow& w) {
    if (!g_pane) return 0;
    D2D1_RECT_F L = Bru_ListRect(w);
    return std::max(0.0f, g_pane->list.view.size() * kBruRowH - (L.bottom - L.top));
}

static D2D1_RECT_F Bru_Thumb(const SetWindow& w) {
    D2D1_RECT_F L = Bru_ListRect(w);
    float view = L.bottom - L.top, content = g_pane ? g_pane->list.view.size() * kBruRowH : 0;
    if (content <= view || view <= 0) return {};
    float th = std::max(30.0f, view * view / content), range = content - view;
    float top = L.top + (g_pane->scroll / range) * (view - th);
    return {L.right - 8, top + 2, L.right - 4, top + th - 2};
}

// 0 inside the pane on nothing, -1 outside it. 1-4 the pills, 5 Rename, 6 the scroll thumb, 100+ a row.
static int Bru_HitAt(const SetWindow& w, float x, float y) {
    if (!g_pane) return -1;
    D2D1_RECT_F P = Bru_Pane(w);
    if (!Set_In(P, x, y)) return -1;
    BruPills b = Bru_Pills(w);
    for (int i = 0; i < 4; i++)
        if (Set_In(b.r[i], x, y)) return 1 + i;
    if (Set_In(Bru_RenameRect(w), x, y)) return 5;
    D2D1_RECT_F L = Bru_ListRect(w);
    if (!Set_In(L, x, y)) return 0;
    D2D1_RECT_F th = Bru_Thumb(w);
    if (th.bottom > th.top && x >= L.right - 14) return 6;
    int i = (int)((y - L.top + g_pane->scroll) / kBruRowH);
    if (i >= 0 && i < (int)g_pane->list.view.size()) return 100 + i;
    return 0;
}

static bool Bru_Clickable(int id) {
    if (!g_pane || id <= 0) return false;
    if (id >= 100 || id == 1 || id == 2 || id == 6) return !g_pane->busy || id >= 100 || id == 6;
    if (id == 3) return !g_pane->busy && !g_pane->list.items.empty();
    if (id == 4) return !g_pane->busy && g_pane->canUndo;
    return true;
}

// ---- Keeping the list current ---------------------------------------------------------------------------------------

static void Bru_Refresh(SetWindow& w, bool force = false) {
    if (!g_pane) return;
    BruPane& pn = *g_pane;
    bru::Getter get = Bru_Getter(w);
    std::wstring sortSig = get(L"f.sort") + L"|" + get(L"f.sortDesc");
    if (pn.needSort || sortSig != pn.sortSig) {
        bru::Sort(pn.list, bru::Pick(get(L"f.sort"), {L"natural", L"name", L"modified", L"created", L"size", L"type",
                                                       L"added"}),
                  bru::Truthy(get(L"f.sortDesc")));
        pn.sortSig = sortSig;
        pn.needSort = false;
        pn.version++;
    }
    std::wstring sig;
    for (const auto& f : w.fields)
        if (Bru_IsRuleKey(f.key)) sig += Bru_Get(w, f.key) + L'\x1F';
    if (!force && sig == pn.sig && pn.version == pn.builtVersion) return;
    pn.sig = sig;
    pn.builtVersion = pn.version;
    pn.counts = bru::Recompute(pn.list, get, pn.seed);
    pn.scrollTarget = std::clamp(pn.scrollTarget, 0.0f, Bru_MaxScroll(w));
    pn.scroll = std::clamp(pn.scroll, 0.0f, Bru_MaxScroll(w));
}

static void Bru_Status(PCWSTR text, bool error = false) {
    if (!g_pane) return;
    g_pane->status = text;
    g_pane->statusError = error;
}

static void Bru_Kick(SetWindow& w) {
    if (!g_pane || g_pane->timer || !w.hwnd) return;
    g_pane->timer = SetTimer(w.hwnd, kBruTimer, 15, nullptr) != 0;
}

static void Bru_AddNow(SetWindow& w, const std::vector<std::wstring>& paths, bool expand) {
    if (!g_pane || paths.empty()) return;
    BruPane& pn = *g_pane;
    size_t before = pn.list.items.size();
    bru::AddPaths(pn.list, paths, expand, bru::ReadFileRules(Bru_Getter(w)));
    size_t added = pn.list.items.size() - before;
    pn.needSort = true;
    pn.version++;
    if (pn.list.items.size() >= bru::kMaxItems) Bru_Status(L"The list is full: it holds up to 50,000 files.", true);
    else if (!added) Bru_Status(L"Nothing new to add. Check what the Files page lets in.");
    else Bru_Status((L"Added " + Bru_Files((int)added) + L".").c_str());
    Set_Invalidate(w);
}

static void Bru_Clear(SetWindow& w) {
    if (!g_pane) return;
    g_pane->list = bru::List();
    g_pane->scroll = g_pane->scrollTarget = 0;
    g_pane->version++;
    Set_Invalidate(w);
}

static void Bru_PickFiles(SetWindow& w, bool folders) {
    IFileOpenDialog* d = nullptr;
    if (FAILED(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&d)))) return;
    DWORD o = 0;
    d->GetOptions(&o);
    d->SetOptions(o | FOS_ALLOWMULTISELECT | FOS_FORCEFILESYSTEM | (folders ? FOS_PICKFOLDERS : 0));
    d->SetTitle(folders ? L"Add the files in these folders" : L"Add files");
    std::vector<std::wstring> paths;
    if (SUCCEEDED(d->Show(w.hwnd))) {
        IShellItemArray* arr = nullptr;
        if (SUCCEEDED(d->GetResults(&arr)) && arr) {
            DWORD n = 0;
            arr->GetCount(&n);
            for (DWORD i = 0; i < n; i++) {
                IShellItem* it = nullptr;
                if (FAILED(arr->GetItemAt(i, &it)) || !it) continue;
                PWSTR p = nullptr;
                if (SUCCEEDED(it->GetDisplayName(SIGDN_FILESYSPATH, &p)) && p) {
                    paths.push_back(p);
                    CoTaskMemFree(p);
                }
                it->Release();
            }
            arr->Release();
        }
    }
    d->Release();
    if (!g_setWin || g_setWin.get() != &w) return;  // The window closed while the picker was up.
    Bru_AddNow(w, paths, folders);
}

// ---- Running ----------------------------------------------------------------------------------------------------------

struct BruWork {
    bru::Plan* plan;
    HWND hwnd;
};

static DWORD WINAPI Bru_Worker(void* arg) {
    auto* job = (BruWork*)arg;
    HRESULT co = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    bool undo = !job->plan;
    bru::Result* r = nullptr;
    try {
        r = undo ? bru::RunUndo() : bru::RunPlan(*job->plan);
    } catch (...) {
        r = new bru::Result;
        r->undo = undo;
        r->failed = 1;
        r->errors.push_back({L"", L"Something went wrong partway. Undo can put back what moved"});
    }
    delete job->plan;
    HWND hwnd = job->hwnd;
    delete job;
    if (!PostMessageW(hwnd, WM_APP_BRU_DONE, undo, (LPARAM)r)) delete r;
    if (SUCCEEDED(co)) CoUninitialize();
    return 0;
}

static bool Bru_StartWorker(SetWindow& w, bru::Plan* plan) {
    if (g_bruWorker) {
        if (WaitForSingleObject(g_bruWorker, 0) == WAIT_TIMEOUT) {
            delete plan;
            return false;
        }
        CloseHandle(g_bruWorker);
        g_bruWorker = nullptr;
    }
    auto* job = new BruWork{plan, w.hwnd};
    g_bruWorker = CreateThread(nullptr, 0, Bru_Worker, job, 0, nullptr);
    if (!g_bruWorker) {
        delete plan;
        delete job;
        return false;
    }
    return true;
}

static void Bru_Rename(SetWindow& w) {
    if (!g_pane || g_pane->busy) return;
    BruPane& pn = *g_pane;
    Set_CommitEdit(w, true);
    Bru_Refresh(w, true);
    if (pn.counts.changing == 0) {
        Bru_Status(pn.list.items.empty() ? L"Add some files first." : L"Nothing to rename yet. Set a rule on the left.");
        Set_Invalidate(w);
        return;
    }
    bru::Getter get = Bru_Getter(w);
    if (bru::Truthy(get(L"confirmBig")) && pn.counts.changing > 500 && GetTickCount() > pn.confirmUntil) {
        pn.confirmUntil = GetTickCount() + 4000;
        Bru_Status((L"Press Rename again to rename " + Bru_Files(pn.counts.changing) + L".").c_str());
        Set_Invalidate(w);
        return;
    }
    pn.confirmUntil = 0;
    bru::Plan* plan = bru::BuildPlan(pn.list, get);
    pn.lastCopy = plan->copy;
    if (!Bru_StartWorker(w, plan)) {
        Bru_Status(L"Couldn't start the rename. Try again.", true);
        Set_Invalidate(w);
        return;
    }
    pn.busy = true;
    Bru_Status(L"");
    Set_Invalidate(w);
}

static void Bru_RunUndo(SetWindow& w) {
    if (!g_pane || g_pane->busy) return;
    if (!bru::CanUndo()) {
        g_pane->canUndo = false;
        Bru_Status(L"Nothing to undo.");
        Set_Invalidate(w);
        return;
    }
    if (!Bru_StartWorker(w, nullptr)) return;
    g_pane->busy = true;
    Bru_Status(L"Putting the last rename back...");
    Set_Invalidate(w);
}

static void Bru_Done(SetWindow& w, bool undo, bru::Result* r) {
    if (!g_pane) return;
    BruPane& pn = *g_pane;
    pn.busy = false;
    std::unordered_map<std::wstring, size_t> at;
    for (size_t i = 0; i < pn.list.items.size(); i++) at[bru::LowerPath(pn.list.items[i].path)] = i;
    for (const auto& [from, to] : r->moved) {
        auto f = at.find(bru::LowerPath(from));
        if (f == at.end()) continue;
        bru::Item& it = pn.list.items[f->second];
        it.path = to;
        it.dir = bru::DirOf(to);
        it.name = PathFindFileNameW(to.c_str());
        it.tagsRead = false;
        it.tags.clear();
        it.hashes.clear();
    }
    pn.list.seen.clear();
    for (bru::Item& it : pn.list.items) {
        pn.list.seen.insert(bru::LowerPath(it.path));
        WIN32_FILE_ATTRIBUTE_DATA a{};
        if (it.state == 1 && GetFileAttributesExW(bru::Long(it.path).c_str(), GetFileExInfoStandard, &a)) {
            it.created = a.ftCreationTime;
            it.modified = a.ftLastWriteTime;
            it.attrs = a.dwFileAttributes;
        }
    }
    pn.version++;
    pn.canUndo = bru::CanUndo();
    std::wstring verb = undo ? L"Put back " : pn.lastCopy ? L"Copied " : L"Renamed ";
    if (r->failed) {
        std::wstring why = r->errors.empty() ? L"" : r->errors[0].second;
        std::wstring s = verb + std::to_wstring(r->done) + L". " + std::to_wstring(r->failed) +
                         (undo ? L" couldn't be put back" : L" couldn't be renamed") + (why.empty() ? L"." : L": " + why + L".");
        Bru_Status(s.c_str(), true);
    } else if (!r->done) {
        Bru_Status(undo ? L"Nothing to undo." : L"Nothing changed.");
    } else {
        Bru_Status((verb + Bru_Files(r->done) + L".").c_str());
    }
    if (!undo && !r->failed && r->done) {
        int after = bru::Pick(Bru_Get(w, L"afterRename"), {L"keep", L"clear", L"close"});
        if (after == 1) Bru_Clear(w);
        else if (after == 2) PostMessageW(w.hwnd, WM_CLOSE, 0, 0);
    }
    delete r;
    Set_Invalidate(w);
}

// ---- Presets ----------------------------------------------------------------------------------------------------------

static std::wstring Bru_PresetLabel(int n) {
    std::wstring t = bru::PresetText(n);
    if (t.empty()) return L"Preset " + std::to_wstring(n) + L" (empty)";
    if (t[0] == L'#') {
        std::wstring name = t.substr(1, t.find(L'\n') == std::wstring::npos ? std::wstring::npos : t.find(L'\n') - 1);
        name = Trim(name);
        if (!name.empty()) return name;
    }
    return L"Preset " + std::to_wstring(n);
}

static void Bru_Link(PCWSTR what) {
    SetWindow* w = g_setWin.get();
    if (!w || !w->hwnd) return;
    bool load = wcsncmp(what, L"load", 4) == 0, save = wcsncmp(what, L"save", 4) == 0;
    int n = (load || save) ? _wtoi(what + 4) : 0;
    if (n < 1 || n > 5) return;
    Set_CommitEdit(*w, true);
    if (load) {
        std::wstring name;
        std::vector<std::pair<std::wstring, std::wstring>> kv;
        if (!bru::LoadPreset(n, name, kv)) {
            Set_SetStatus(*w, L"That preset is empty. Save one first.", true);
            return;
        }
        for (SetField& f : w->fields) {
            if (!Bru_IsRuleKey(f.key)) continue;
            Set_PutValue(f, f.def);
            for (const auto& [k, v] : kv)
                if (k == f.key) Set_PutValue(f, v);
        }
        for (SetField& f : w->fields)
            if (wcscmp(f.key, L"preset.name") == 0) Set_PutValue(f, name);
        Set_SetStatus(*w, L"Loaded. Press Save to keep these rules.");
    } else {
        std::wstring name = Trim(Bru_Get(*w, L"preset.name"));
        if (name.empty()) name = L"Preset " + std::to_wstring(n);
        std::vector<std::pair<std::wstring, std::wstring>> kv;
        for (const SetField& f : w->fields)
            if (Bru_IsRuleKey(f.key)) kv.push_back({f.key, Bru_Get(*w, f.key)});
        bru::SavePreset(n, name, kv);
        Set_SetStatus(*w, (L"Saved as preset " + std::to_wstring(n) + L".").c_str());
    }
    Set_Relayout(*w);
    Set_Invalidate(*w);
}

// ---- Painting ---------------------------------------------------------------------------------------------------------

static float Bru_Glow(int id) {
    if (!g_pane) return 0;
    auto it = g_pane->glow.find(id);
    return it == g_pane->glow.end() ? 0 : it->second;
}

static void Bru_DrawPill(SetPaint& p, SetWindow& w, const D2D1_RECT_F& r, int i, bool label, bool off) {
    float g = off ? 0 : Bru_Glow(1 + i), rad = (r.bottom - r.top) / 2;
    p.Round(r, rad, mocha::surface0, w.glass ? 0.7f : 1);
    p.Edge(r, rad, mocha::surface1, 0.8f * (1 - g), 1);
    p.GradRing(r, rad, g, 1.5f);
    UINT32 c = off ? mocha::overlay0 : mocha::text;
    if (label) {
        p.Glyph(w.fIconS.get(), kBruPillGlyph[i], {r.left + 12, r.top, r.left + 28, r.bottom}, c);
        p.Text(w.fSmall.get(), kBruPillText[i], {r.left + 36, r.top, r.right - 10, r.bottom}, c);
    } else {
        p.Glyph(w.fIconS.get(), kBruPillGlyph[i], r, c);
    }
}

static void Bru_DrawPreview(SetPaint& p, SetWindow& w) {
    if (!g_pane || w.render) return;
    BruPane& pn = *g_pane;
    Bru_Refresh(w);
    if (!pn.fCenter) pn.fCenter = Set_Fmt(w.family, 13, 500, true, DWRITE_TEXT_ALIGNMENT_CENTER);
    D2D1_RECT_F P = Bru_Pane(w);
    Set_DrawDock(p, w, P, 14, w.glass ? 0.58f : 1, 0);
    float l = P.left + 20, r = P.right - 20, t = P.top;
    p.Text(w.fBig.get(), L"Files", {l, t + 16, r, t + 44}, mocha::text);
    std::wstring count;
    if (pn.list.view.empty()) {
        count = L"Nothing added yet";
    } else {
        count = Bru_Files(pn.counts.total) + L"  ·  " + std::to_wstring(pn.counts.changing) + L" will change";
        if (pn.counts.problems) count += L"  ·  " + std::to_wstring(pn.counts.problems) + L" can't";
    }
    p.Text(w.fSmall.get(), count, {l, t + 46, r, t + 64}, mocha::subtext0);

    BruPills b = Bru_Pills(w);
    for (int i = 0; i < 4; i++) {
        bool off = pn.busy && i != 3 ? true : !Bru_Clickable(1 + i);
        Bru_DrawPill(p, w, b.r[i], i, b.label[i], off);
    }

    D2D1_RECT_F L = Bru_ListRect(w);
    float c1 = L.left + 34, c2r = L.right - 16, mid = (c1 + c2r) / 2;
    p.Text(w.fSection.get(), L"NOW", {c1, t + 124, mid - 8, t + 140}, mocha::subtext0);
    p.Text(w.fSection.get(), L"NEW NAME", {mid + 8, t + 124, c2r, t + 140}, mocha::subtext0);
    p.rt->DrawLine({L.left + 10, L.top - 2}, {L.right - 10, L.top - 2}, p.B(mocha::surface1, 0.6f), 1);

    if (pn.list.view.empty()) {
        float cy = (L.top + L.bottom) / 2;
        p.Glyph(w.fIconL.get(), 0xE8B7, {L.left, cy - 64, L.right, cy - 16}, mocha::overlay1);
        std::wstring hk = Trim(Bru_Get(w, L"renameHotkey"));
        p.Text(pn.fCenter.get(),
               hk.empty() ? L"Drop files here, or right-click files in Explorer and pick Bulk rename."
                          : L"Drop files here, or select them in Explorer and press " + hk + L".",
               {L.left + 30, cy - 4, L.right - 30, cy + 50}, mocha::subtext0);
    } else {
        p.rt->PushAxisAlignedClip(L, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
        int n = (int)pn.list.view.size();
        int first = std::max(0, (int)(pn.scroll / kBruRowH));
        int last = std::min(n - 1, (int)((pn.scroll + (L.bottom - L.top)) / kBruRowH) + 1);
        for (int i = first; i <= last; i++) {
            const bru::Item& it = pn.list.items[pn.list.view[i]];
            float y = L.top + i * kBruRowH - pn.scroll;
            D2D1_RECT_F row{L.left, y + 1, L.right - 12, y + kBruRowH - 1};
            float g = Bru_Glow(100 + i);
            if (g > 0) {
                p.Round(row, 8, mocha::surface0, 0.55f * g);
                p.GradRing(row, 8, 0.6f * g, 1);
            }
            float cx = L.left + 18, cy = y + kBruRowH / 2;
            if (it.checked) {
                SetCom<ID2D1LinearGradientBrush> gb = p.G({cx - 7, cy - 7, cx + 7, cy + 7});
                if (gb) p.rt->FillEllipse(D2D1::Ellipse({cx, cy}, 7, 7), gb.get());
                p.Glyph(w.fIconS.get(), 0xE73E, {cx - 7, cy - 7, cx + 7, cy + 7}, mocha::crust);
            } else {
                p.rt->DrawEllipse(D2D1::Ellipse({cx, cy}, 6.5f, 6.5f), p.B(mocha::overlay0), 1.2f);
            }
            float a = it.checked ? 1 : 0.5f;
            p.Text(w.fValue.get(), it.name, {c1, y, mid - 8, y + kBruRowH}, mocha::subtext1, a);
            std::wstring nn = it.checked ? it.newName : L"Left out";
            UINT32 nc = !it.checked ? mocha::overlay0 : it.state == 2 ? mocha::red : it.state == 1 ? mocha::blue
                                                                                                    : mocha::overlay1;
            p.Text(w.fValue.get(), nn, {mid + 8, y, c2r, y + kBruRowH}, nc, a);
        }
        p.rt->PopAxisAlignedClip();
        D2D1_RECT_F th = Bru_Thumb(w);
        if (th.bottom > th.top) Set_ThumbFill(p, th, 0.45f + 0.55f * std::max(Bru_Glow(6), pn.dragThumb ? 1.0f : 0.0f));
    }

    std::wstring line = pn.status;
    bool err = pn.statusError;
    if (pn.hover >= 100 && pn.hover - 100 < (int)pn.list.view.size()) {
        const bru::Item& it = pn.list.items[pn.list.view[pn.hover - 100]];
        if (it.checked && it.state == 2) line = it.error + L".", err = true;
    }
    if (line.empty() && pn.busy) line = L"Renaming...";
    if (line.empty() && !pn.list.view.empty()) line = L"Click a row to leave that file out.";
    p.Text(w.fStatusLine.get(), line, {l, P.bottom - 94, r, P.bottom - 70}, err ? mocha::red : mocha::overlay1);

    D2D1_RECT_F R = Bru_RenameRect(w);
    bool on = !pn.busy && pn.counts.changing > 0;
    float rg = Bru_Glow(5), rad = 12;
    std::wstring label = pn.busy ? L"Working..." : pn.counts.changing > 0
                                                       ? (bru::Truthy(Bru_Get(w, L"cp.on")) ? L"Copy " : L"Rename ") +
                                                             Bru_Files(pn.counts.changing)
                                                       : L"Rename";
    if (on) {
        p.GradFill(R, rad, 0.86f + 0.14f * rg);
        p.Text(w.fButton.get(), label, R, mocha::crust);
    } else {
        p.Round(R, rad, mocha::surface0, w.glass ? 0.7f : 1);
        p.Edge(R, rad, mocha::surface1, 0.8f, 1);
        p.Text(w.fButton.get(), label, R, mocha::overlay1);
    }
}

// ---- Input ------------------------------------------------------------------------------------------------------------

static bool Bru_Tick(SetWindow& w) {
    if (!g_pane) return false;
    BruPane& pn = *g_pane;
    bool anim = Set_Anim(w), moving = false;
    if (pn.hover > 0 && !pn.glow.count(pn.hover)) pn.glow[pn.hover] = 0;
    for (auto it = pn.glow.begin(); it != pn.glow.end();) {
        float target = it->first == pn.hover && Bru_Clickable(it->first) ? 1.0f : 0.0f;
        float d = target - it->second;
        if (!anim || fabsf(d) < 0.02f) it->second = target;
        else it->second += d * 0.3f, moving = true;
        if (it->second == 0 && target == 0) it = pn.glow.erase(it);
        else ++it;
    }
    float d = pn.scrollTarget - pn.scroll;
    if (!anim || fabsf(d) < 0.5f) pn.scroll = pn.scrollTarget;
    else pn.scroll += d * 0.25f, moving = true;
    return moving;
}

static void Bru_SetHover(SetWindow& w, int id) {
    if (!g_pane || g_pane->hover == id) return;
    g_pane->hover = id;
    Bru_Kick(w);
    Set_Invalidate(w);
}

static void Bru_ThumbTo(SetWindow& w, float y) {
    D2D1_RECT_F L = Bru_ListRect(w), th = Bru_Thumb(w);
    float thh = th.bottom - th.top + 4, range = (L.bottom - L.top) - thh;
    float f = range > 0 ? std::clamp((y - g_pane->dragOff - L.top) / range, 0.0f, 1.0f) : 0;
    g_pane->scroll = g_pane->scrollTarget = f * Bru_MaxScroll(w);
    Set_Invalidate(w);
}

static void Bru_Click(SetWindow& w, int id, float y) {
    BruPane& pn = *g_pane;
    if (id == 6) {
        D2D1_RECT_F th = Bru_Thumb(w);
        pn.dragThumb = true;
        pn.dragOff = Set_In({th.left - 10, th.top, th.right + 10, th.bottom}, th.left, y) ? y - th.top + 2
                                                                                           : (th.bottom - th.top) / 2;
        SetCapture(w.hwnd);
        Bru_ThumbTo(w, y);
        return;
    }
    if (!Bru_Clickable(id)) return;
    if (id >= 100) {
        int i = id - 100;
        if (i < (int)pn.list.view.size()) {
            bru::Item& it = pn.list.items[pn.list.view[i]];
            it.checked = !it.checked;
            pn.version++;
            Set_Invalidate(w);
        }
        return;
    }
    switch (id) {
        case 1: Bru_PickFiles(w, false); break;
        case 2: Bru_PickFiles(w, true); break;
        case 3:
            Bru_Clear(w);
            Bru_Status(L"");
            break;
        case 4:
            g_bruUndoPending = true;
            PostMessageW(w.hwnd, WM_APP_BRU_UNDO, 0, 0);
            break;
        case 5: Bru_Rename(w); break;
    }
}

static void Bru_RowMenu(SetWindow& w, int id, POINT screen) {
    BruPane& pn = *g_pane;
    int i = id - 100;
    if (i < 0 || i >= (int)pn.list.view.size()) return;
    std::vector<SetMenuItem> rows;
    rows.push_back(Set_MenuRow(1, L"", L"Remove from the list"));
    rows.push_back(Set_MenuRow(2, L"", L"Keep only the ticked files"));
    rows.push_back(Set_MenuRow(3, L"", L"Tick every file"));
    int cmd = Set_TrayMenu(w.hwnd, rows, &screen);
    if (!g_pane || g_pane != &pn) return;
    if (cmd == 1) {
        bru::RemoveItems(pn.list, {pn.list.view[i]});
    } else if (cmd == 2) {
        std::vector<int> drop;
        for (size_t k = 0; k < pn.list.items.size(); k++)
            if (!pn.list.items[k].checked) drop.push_back((int)k);
        bru::RemoveItems(pn.list, drop);
    } else if (cmd == 3) {
        for (bru::Item& it : pn.list.items) it.checked = true;
    } else {
        return;
    }
    pn.needSort = true;
    pn.version++;
    Set_Invalidate(w);
}

static LRESULT CALLBACK Bru_Subclass(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR, DWORD_PTR) {
    SetWindow* w = g_setWin && g_setWin->hwnd == hwnd ? g_setWin.get() : nullptr;
    if (!w || !g_pane) {
        if (msg == WM_NCDESTROY) RemoveWindowSubclass(hwnd, Bru_Subclass, kBruSubclass);
        return DefSubclassProc(hwnd, msg, wp, lp);
    }
    BruPane& pn = *g_pane;
    auto dipX = [&](int x) { return x * 96.0f / w->dpi; };
    auto dipY = [&](int y) { return y * 96.0f / w->dpi - kSetCapH; };
    switch (msg) {
        case WM_APP_BRU_TAKE: {
            std::vector<std::pair<std::vector<std::wstring>, bool>> batch;
            {
                std::lock_guard<std::mutex> lock(g_bruQueueLock);
                batch.swap(g_bruQueue);
            }
            if (batch.empty()) return 0;
            if (!pn.busy) Bru_Clear(*w);  // A new pick from Explorer starts a new list.
            for (auto& [paths, folder] : batch) Bru_AddNow(*w, paths, folder);
            return 0;
        }
        case WM_APP_BRU_UNDO:
            if (g_bruUndoPending.exchange(false)) Bru_RunUndo(*w);
            return 0;
        case WM_APP_BRU_DONE:
            Bru_Done(*w, wp != 0, (bru::Result*)lp);
            return 0;
        case WM_TIMER:
            if (wp == kBruTimer) {
                if (!Bru_Tick(*w)) {
                    KillTimer(hwnd, kBruTimer);
                    pn.timer = false;
                }
                Set_Invalidate(*w);
                return 0;
            }
            break;
        case WM_COMMAND:
            if (HIWORD(wp) == EN_CHANGE) Set_Invalidate(*w);
            break;
        case WM_DROPFILES: {
            HDROP drop = (HDROP)wp;
            UINT n = DragQueryFileW(drop, 0xFFFFFFFF, nullptr, 0);
            std::vector<std::wstring> paths;
            for (UINT i = 0; i < n; i++) {
                UINT len = DragQueryFileW(drop, i, nullptr, 0);
                std::wstring p(len + 1, L'\0');
                DragQueryFileW(drop, i, p.data(), len + 1);
                p.resize(len);
                paths.push_back(p);
            }
            DragFinish(drop);
            Bru_AddNow(*w, paths, true);
            return 0;
        }
        case WM_MOUSEMOVE: {
            float x = dipX(GET_X_LPARAM(lp)), y = dipY(GET_Y_LPARAM(lp));
            if (pn.dragThumb) {
                Bru_ThumbTo(*w, y);
                return 0;
            }
            if (w->openSel < 0) Bru_SetHover(*w, Bru_HitAt(*w, x, y));
            if (!pn.tracking) {
                TRACKMOUSEEVENT t{sizeof(t), TME_LEAVE, hwnd, 0};
                pn.tracking = TrackMouseEvent(&t) != FALSE;
            }
            break;
        }
        case WM_MOUSELEAVE:
            pn.tracking = false;
            Bru_SetHover(*w, -1);
            break;
        case WM_LBUTTONDOWN: {
            if (w->openSel >= 0 || pn.dragThumb) break;
            float x = dipX(GET_X_LPARAM(lp)), y = dipY(GET_Y_LPARAM(lp));
            int id = Bru_HitAt(*w, x, y);
            if (id < 0) break;
            Set_CommitEdit(*w, true);
            SetFocus(hwnd);
            Bru_Click(*w, id, y);
            return 0;
        }
        case WM_LBUTTONDBLCLK: {
            float x = dipX(GET_X_LPARAM(lp)), y = dipY(GET_Y_LPARAM(lp));
            if (w->openSel < 0 && Bru_HitAt(*w, x, y) >= 0) return 0;
            break;
        }
        case WM_LBUTTONUP:
            if (pn.dragThumb) {
                pn.dragThumb = false;
                if (GetCapture() == hwnd) ReleaseCapture();
                Set_Invalidate(*w);
                return 0;
            }
            break;
        case WM_CAPTURECHANGED:
            if (pn.dragThumb && (HWND)lp != hwnd) {
                pn.dragThumb = false;
                Set_Invalidate(*w);
            }
            break;
        case WM_RBUTTONUP: {
            if (w->openSel >= 0) break;
            float x = dipX(GET_X_LPARAM(lp)), y = dipY(GET_Y_LPARAM(lp));
            int id = Bru_HitAt(*w, x, y);
            if (id < 0) break;
            if (id >= 100 && !pn.busy) {
                POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
                ClientToScreen(hwnd, &pt);
                Bru_RowMenu(*w, id, pt);
            }
            return 0;
        }
        case WM_MOUSEWHEEL: {
            if (w->openSel >= 0) break;
            POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            ScreenToClient(hwnd, &pt);
            if (!Set_In(Bru_ListRect(*w), dipX(pt.x), dipY(pt.y))) {
                if (Bru_HitAt(*w, dipX(pt.x), dipY(pt.y)) >= 0) return 0;  // Over the pane, not its list.
                break;
            }
            float delta = (float)GET_WHEEL_DELTA_WPARAM(wp) / WHEEL_DELTA;
            pn.scrollTarget = std::clamp(pn.scrollTarget - delta * kBruRowH * 3, 0.0f, Bru_MaxScroll(*w));
            if (!Set_Anim(*w)) pn.scroll = pn.scrollTarget;
            Bru_Kick(*w);
            Set_Invalidate(*w);
            return 0;
        }
        case WM_SETCURSOR:
            if (LOWORD(lp) == HTCLIENT && pn.hover >= 0 && w->openSel < 0) {
                SetCursor(LoadCursorW(nullptr, Bru_Clickable(pn.hover) ? IDC_HAND : IDC_ARROW));
                return TRUE;
            }
            break;
        case WM_KEYDOWN:
            if (GetFocus() == hwnd && GetKeyState(VK_CONTROL) < 0 && w->recording < 0) {
                if (wp == VK_RETURN) {
                    Bru_Rename(*w);
                    return 0;
                }
                if (wp == 'Z' && !pn.busy) {
                    g_bruUndoPending = true;
                    PostMessageW(hwnd, WM_APP_BRU_UNDO, 0, 0);
                    return 0;
                }
            }
            break;
        case WM_NCDESTROY: {
            if (pn.timer) KillTimer(hwnd, kBruTimer);
            RemoveWindowSubclass(hwnd, Bru_Subclass, kBruSubclass);
            delete g_pane;
            g_pane = nullptr;
            break;
        }
    }
    return DefSubclassProc(hwnd, msg, wp, lp);
}

// Called on the window's own thread once it is open.
static void Bru_Attach() {
    SetWindow* w = g_setWin.get();
    if (!w || !w->hwnd || w->render) return;
    delete g_pane;
    g_pane = new BruPane;
    g_pane->seed = GetTickCount();
    g_pane->canUndo = bru::CanUndo();
    DragAcceptFiles(w->hwnd, TRUE);
    // Explorer may run with fewer rights than this window: let its drops through.
    ChangeWindowMessageFilterEx(w->hwnd, WM_DROPFILES, MSGFLT_ALLOW, nullptr);
    ChangeWindowMessageFilterEx(w->hwnd, WM_COPYDATA, MSGFLT_ALLOW, nullptr);
    ChangeWindowMessageFilterEx(w->hwnd, 0x0049 /* WM_COPYGLOBALDATA */, MSGFLT_ALLOW, nullptr);
    SetWindowSubclass(w->hwnd, Bru_Subclass, kBruSubclass, 0);
    PostMessageW(w->hwnd, WM_APP_BRU_TAKE, 0, 0);
    if (g_bruUndoPending) PostMessageW(w->hwnd, WM_APP_BRU_UNDO, 0, 0);
}

// From the tray thread: paths Explorer sent. The window takes them when it gets WM_APP_BRU_TAKE.
void Bru_QueuePaths(std::vector<std::wstring> paths, bool folder) {
    std::lock_guard<std::mutex> lock(g_bruQueueLock);
    g_bruQueue.push_back({std::move(paths), folder});
}

void Bru_UndoLast() {
    g_bruUndoPending = true;
    OpenSettingsWindow();
    if (HWND hwnd = g_settingsWnd) PostMessageW(hwnd, WM_APP_BRU_UNDO, 0, 0);
}

// At unload: a rename still running finishes before the code it runs goes away.
void Bru_WaitWorkers() {
    if (!g_bruWorker) return;
    WaitForSingleObject(g_bruWorker, 120000);
    CloseHandle(g_bruWorker);
    g_bruWorker = nullptr;
}

// The tray icon's right-click menu. Returns 1 to open, 2 to undo, 3 for settings, 0 for nothing.
int ShowTrayMenu(HWND owner, POINT pt) {
    std::vector<SetMenuItem> rows;
    rows.push_back(Set_MenuRow(1, L"\uE8AC", L"Open Bulk Rename"));
    rows.push_back(Set_MenuRow(2, L"\uE7A7", L"Undo last rename"));
    rows.push_back(Set_MenuSep());
    rows.push_back(Set_MenuRow(3, L"\uEB51", L"Settings"));
    return Set_TrayMenu(owner, rows, &pt);
}
}  // namespace brset

// ---- Tray icon (tool process only) -------------------------------------------------------------------------------
// Click opens the window; right-click shows Open, Undo and Settings. Explorer sends the selected paths here.

constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();
static constexpr UINT WM_APP_TRAY = WM_APP + 20, WM_APP_TRAY_REFRESH = WM_APP + 21;
static HANDLE g_trayThread;
static std::atomic<HWND> g_trayWnd;
static UINT g_taskbarCreated;
static bool g_trayShown;
static HICON g_trayIcon;

static HICON Crisp_ShrinkIcon(HICON big, int factor) {
    if (!big || factor <= 1) return big;
    ICONINFO ii{};
    if (!GetIconInfo(big, &ii)) return big;
    HICON out = nullptr;
    BITMAP bm{};
    if (ii.hbmColor && GetObjectW(ii.hbmColor, sizeof(bm), &bm) && bm.bmWidth == bm.bmHeight &&
        bm.bmWidth >= factor && bm.bmWidth % factor == 0) {
        const int src = bm.bmWidth, n = src / factor;
        BITMAPINFO bi{};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        bi.bmiHeader.biWidth = src;
        bi.bmiHeader.biHeight = -src;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;
        unsigned int* in = new unsigned int[(size_t)src * src];
        HDC screen = GetDC(nullptr);
        if (GetDIBits(screen, ii.hbmColor, 0, src, in, &bi, DIB_RGB_COLORS) == src) {
            bool premul = true, anyAlpha = false;
            for (size_t i = 0; i < (size_t)src * src; i++) {
                unsigned int p = in[i], a = p >> 24;
                if (a) anyAlpha = true;
                if (((p >> 16) & 0xFF) > a || ((p >> 8) & 0xFF) > a || (p & 0xFF) > a) premul = false;
            }
            void* bits = nullptr;
            bi.bmiHeader.biWidth = n;
            bi.bmiHeader.biHeight = -n;
            HBITMAP color = anyAlpha ? CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0) : nullptr;
            if (color && bits) {
                unsigned int* px = (unsigned int*)bits;
                const unsigned int cnt = (unsigned int)(factor * factor);
                for (int y = 0; y < n; y++)
                    for (int x = 0; x < n; x++) {
                        unsigned int sa = 0, sr = 0, sg = 0, sb = 0;
                        for (int dy = 0; dy < factor; dy++)
                            for (int dx = 0; dx < factor; dx++) {
                                unsigned int p = in[(size_t)(y * factor + dy) * src + x * factor + dx], a = p >> 24;
                                unsigned int r = (p >> 16) & 0xFF, g = (p >> 8) & 0xFF, b = p & 0xFF;
                                if (!premul) {
                                    r = (r * a + 127) / 255;
                                    g = (g * a + 127) / 255;
                                    b = (b * a + 127) / 255;
                                }
                                sa += a; sr += r; sg += g; sb += b;
                            }
                        unsigned int a = (sa + cnt / 2) / cnt, r = 0, g = 0, b = 0;
                        if (a && sa) {
                            r = (sr * 255 + sa / 2) / sa; if (r > 255) r = 255;
                            g = (sg * 255 + sa / 2) / sa; if (g > 255) g = 255;
                            b = (sb * 255 + sa / 2) / sa; if (b > 255) b = 255;
                        }
                        px[(size_t)y * n + x] = a ? ((a << 24) | (r << 16) | (g << 8) | b) : 0;
                    }
                // A zero mask: with 32-bit colour Windows draws from the alpha channel.
                unsigned char* maskBits = new unsigned char[(size_t)((n + 15) / 16) * 2 * n]();
                HBITMAP mask = CreateBitmap(n, n, 1, 1, maskBits);
                delete[] maskBits;
                if (mask) {
                    ICONINFO o{TRUE, 0, 0, mask, color};
                    out = CreateIconIndirect(&o);
                    DeleteObject(mask);
                }
            }
            if (color) DeleteObject(color);
        }
        ReleaseDC(nullptr, screen);
        delete[] in;
    }
    if (ii.hbmColor) DeleteObject(ii.hbmColor);
    if (ii.hbmMask) DeleteObject(ii.hbmMask);
    if (!out) return big;
    DestroyIcon(big);
    return out;
}

static HICON MakeTrayIcon_Big() {
    int size = GetSystemMetricsForDpi(SM_CXICON, GetDpiForSystem()) * 4;
    if (size < 16) size = 16;
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = size;
    bi.bmiHeader.biHeight = -size;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    void* bits = nullptr;
    void* glyphBits = nullptr;
    HDC screen = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    HBITMAP glyph = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &glyphBits, nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!color || !glyph) {
        if (color) DeleteObject(color);
        if (glyph) DeleteObject(glyph);
        return nullptr;
    }
    HDC dc = CreateCompatibleDC(nullptr);
    HGDIOBJ old = SelectObject(dc, glyph);
    memset(glyphBits, 0, (size_t)size * size * 4);
    HFONT font = CreateFontW(-(int)(size * 0.84f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             ANTIALIASED_QUALITY, 0, L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)0xE8AC, 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    const float c0[3] = {0x89 / 255.f, 0xB4 / 255.f, 0xFA / 255.f};
    const float c1[3] = {0xCB / 255.f, 0xA6 / 255.f, 0xF7 / 255.f};
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) rgb[i] = (c0[i] + (c1[i] - c0[i]) * t) * cov;
            px[y * size + x] = ((uint32_t)(cov * 255 + 0.5f) << 24) | ((uint32_t)(rgb[0] * 255 + 0.5f) << 16) |
                               ((uint32_t)(rgb[1] * 255 + 0.5f) << 8) | (uint32_t)(rgb[2] * 255 + 0.5f);
        }
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    DeleteObject(glyph);
    return icon;
}

// Drawn at 4x and shrunk, so the icon is smooth at the size it is shown.
static HICON MakeTrayIcon() { return Crisp_ShrinkIcon(MakeTrayIcon_Big(), 4); }

static void UpdateTray(HWND hwnd, bool recreate) {
    NOTIFYICONDATAW nid{};
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = kTrayId;
    if (!Wh_GetIntSetting(L"settingsTrayIcon")) {
        if (g_trayShown) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayShown = false;
        return;
    }
    HICON icon = g_trayIcon && !recreate ? g_trayIcon : MakeTrayIcon();
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_APP_TRAY;
    nid.hIcon = icon;
    wcscpy_s(nid.szTip, L"Seamless Bulk Rename");
    if (recreate) g_trayShown = false;
    if (!g_trayShown) {
        Shell_NotifyIconW(NIM_DELETE, &nid);
        if (Shell_NotifyIconW(NIM_ADD, &nid)) {
            nid.uVersion = NOTIFYICON_VERSION_4;
            Shell_NotifyIconW(NIM_SETVERSION, &nid);
            g_trayShown = true;
        }
    } else {
        Shell_NotifyIconW(NIM_MODIFY, &nid);
    }
    if (g_trayIcon && g_trayIcon != icon) DestroyIcon(g_trayIcon);
    g_trayIcon = icon;
}

// Paths from Explorer: 'S' (the selection) or 'F' (a folder to open up), then the paths, each ending in a NUL.
static void TakePaths(const COPYDATASTRUCT* cd) {
    if (!cd || cd->dwData != kBruCopyPaths || cd->cbData < 2 * sizeof(WCHAR) || cd->cbData % sizeof(WCHAR)) return;
    const WCHAR* p = (const WCHAR*)cd->lpData;
    size_t n = cd->cbData / sizeof(WCHAR);
    bool folder = p[0] == L'F';
    std::vector<std::wstring> paths;
    std::wstring cur;
    for (size_t i = 1; i < n; i++) {
        if (p[i]) {
            cur += p[i];
            continue;
        }
        if (!cur.empty()) paths.push_back(cur);
        cur.clear();
    }
    if (!cur.empty()) paths.push_back(cur);
    if (paths.empty()) return;
    brset::Bru_QueuePaths(std::move(paths), folder);
    brset::OpenSettingsWindow();
    if (HWND w = brset::g_settingsWnd) PostMessageW(w, WM_APP + 60, 0, 0);
}

static LRESULT CALLBACK TrayProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (g_taskbarCreated && msg == g_taskbarCreated) {
        UpdateTray(hwnd, true);
        return 0;
    }
    switch (msg) {
        case WM_COPYDATA:
            TakePaths((const COPYDATASTRUCT*)lp);
            return TRUE;
        case WM_APP_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT:
                    brset::OpenSettingsWindow();
                    break;
                case WM_CONTEXTMENU: {
                    POINT pt{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)};
                    SetForegroundWindow(hwnd);
                    int cmd = brset::ShowTrayMenu(hwnd, pt);
                    if (cmd == 1 || cmd == 3) brset::OpenSettingsWindow();
                    else if (cmd == 2) brset::Bru_UndoLast();
                    break;
                }
            }
            return 0;
        case WM_APP_TRAY_REFRESH:
            UpdateTray(hwnd, false);
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY: {
            NOTIFYICONDATAW nid{};
            nid.cbSize = sizeof(nid);
            nid.hWnd = hwnd;
            nid.uID = kTrayId;
            if (g_trayShown) Shell_NotifyIconW(NIM_DELETE, &nid);
            g_trayShown = false;
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static DWORD WINAPI TrayThread(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    HRESULT co = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    HINSTANCE inst = (HINSTANCE)&__ImageBase;
    WNDCLASSW wc{};
    wc.lpfnWndProc = TrayProc;
    wc.hInstance = inst;
    wc.lpszClassName = kBruTrayClass;
    RegisterClassW(&wc);
    // A hidden top-level window, not a message-only one: only top-level windows hear TaskbarCreated, and Explorer
    // finds it by class to send the selection.
    HWND hwnd = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"Seamless Bulk Rename", WS_POPUP, 0, 0, 0, 0,
                                nullptr, nullptr, inst, nullptr);
    if (!hwnd) {
        UnregisterClassW(wc.lpszClassName, inst);
        if (SUCCEEDED(co)) CoUninitialize();
        return 0;
    }
    g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
    ChangeWindowMessageFilterEx(hwnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
    ChangeWindowMessageFilterEx(hwnd, WM_COPYDATA, MSGFLT_ALLOW, nullptr);  // Explorer runs with fewer rights.
    g_trayWnd = hwnd;
    UpdateTray(hwnd, true);
    MSG m;
    while (GetMessageW(&m, nullptr, 0, 0) > 0) {
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    g_trayWnd = nullptr;
    if (IsWindow(hwnd)) DestroyWindow(hwnd);
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
    UnregisterClassW(wc.lpszClassName, inst);
    if (SUCCEEDED(co)) CoUninitialize();
    return 0;
}

static void StopTrayThread() {
    if (!g_trayThread) return;
    if (HWND hwnd = g_trayWnd) PostMessageW(hwnd, WM_CLOSE, 0, 0);
    if (WaitForSingleObject(g_trayThread, 5000) == WAIT_TIMEOUT) Wh_Log(L"The tray thread did not stop");
    CloseHandle(g_trayThread);
    g_trayThread = nullptr;
}


// ---- Start and stop -------------------------------------------------------------------------------------------------
// The tool process owns the tray icon and the rename window. Inside Explorer the mod only adds the right-click entry
// and the shortcut, and sends the selected paths across.

#include <windhawk_tool_mod.h>

static bool g_inExplorer;

static void Bru_ReadToolSettings() { g_bruAnim = Wh_GetIntSetting(L"settingsAnimation") != 0; }

BOOL WhTool_ModInit() {
    Bru_ReadToolSettings();
    g_trayThread = CreateThread(nullptr, 0, TrayThread, nullptr, 0, nullptr);
    if (!g_trayThread) Wh_Log(L"Couldn't start the tray thread");
    return g_trayThread != nullptr;
}

void WhTool_ModSettingsChanged() {
    Bru_ReadToolSettings();
    if (HWND hwnd = g_trayWnd) PostMessageW(hwnd, WM_APP_TRAY_REFRESH, 0, 0);
    if (HWND wnd = brset::g_settingsWnd) PostMessageW(wnd, brset::WM_APP_SETTINGS_RELOAD, 0, 0);
}

void WhTool_ModUninit() {
    brset::CloseSettingsWindow();
    brset::Bru_WaitWorkers();
    StopTrayThread();
}

BOOL WhToolLauncher_ModInit(BOOL* launch) {
    WCHAR path[MAX_PATH]{};
    GetModuleFileNameW(nullptr, path, ARRAYSIZE(path));
    PCWSTR exe = PathFindFileNameW(path);
    if (_wcsicmp(exe, L"windhawk.exe") == 0) {
        *launch = TRUE;
        return TRUE;
    }
    *launch = FALSE;
    if (_wcsicmp(exe, L"explorer.exe") != 0) return FALSE;
    g_inExplorer = true;
    bruex::g_menuOn = Wh_GetIntSetting(L"menuEntry") != 0;
    bruex::HookMenus();
    bruex::StartHotkeyThread();
    return TRUE;
}

void WhToolLauncher_ModUninit() {
    if (g_inExplorer) bruex::StopHotkeyThread();
}

void WhToolLauncher_ModSettingsChanged(BOOL* reload) {
    if (!g_inExplorer) return;
    bruex::g_menuOn = Wh_GetIntSetting(L"menuEntry") != 0;
    bruex::ReloadHotkey();
}
