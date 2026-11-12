// ==WindhawkMod==
// @id              seamless-sound-manager
// @name            Seamless Sound Manager
// @description     Change every Windows sound with a scheme: 161 presets, startup and logon sounds. A port of Sound Manager
// @version         1.0.1
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         windhawk-mod.exe
// @architecture    x86-64
// @compilerOptions -ld2d1 -ldwrite -lwindowscodecs -lole32 -loleaut32 -luuid -lgdi32 -luser32 -lshell32 -lshlwapi -ladvapi32 -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -lshcore -lbcrypt -lmfplat -lmfreadwrite -lmfuuid -lwtsapi32 -lwinmm -lcrypt32 -lwinhttp -lpropsys
// @license         CDDL-1.0
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Sound Manager

Change every Windows sound at once with a sound scheme, edit each sound on its
own, and get the startup, logon, logoff and shutdown sounds back. A full port of
ORelio's Sound Manager to Windhawk, so the app doesn't need to be installed.

![Seamless Sound Manager](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-sound-manager.png)

## What it does

- Every preset from the Sound Manager schemes collection (161), grouped as in
  the collection. Preview one, or load it in a click. Downloads are kept.
- All 31 sound events: play, replace, reset to the Windows sound, remove, turn
  off, or drop a file on the row. Any audio file works; it's converted to WAV
  (up to 30 seconds).
- Scheme files: import .ths, .zip and .soundpack, export .ths or a Windows
  .themepack. Double-click a .ths or .soundpack file to load it.
- The scheme's name, author, description and picture, editable in place.
- Startup, logon, logoff and shutdown sounds, which Windows stopped playing,
  played by the mod at the right moments (lock and unlock too).
- Settings window from the tray icon, in the same style as the other Seamless
  mods.

## Notes

- The scheme in use carries over from Sound Manager: the mod uses the same
  sounds folder (%APPDATA%\SoundManager), so nothing has to be moved.
- Presets download from GitHub the first time you use them.
- Patching the built-in Windows startup sound is off by default and only works
  when Windhawk runs as administrator.

## Credits

A port of Sound Manager by ORelio (https://github.com/ORelio/Sound-Manager),
CDDL-1.0 license, with the schemes from Sound-Manager-Schemes
(https://github.com/ORelio/Sound-Manager-Schemes).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- missingUseDefault: true
  $name: "Keep Windows sounds for gaps"
  $description: "When a scheme has no sound for an event, Windows keeps its own sound there. Off, that event stays silent."
- playSessionSounds: true
  $name: "Play startup, logon and shutdown sounds"
  $description: "Windows no longer plays these itself. The mod plays Startup at boot, Log On and Log Off when you lock or switch users, and Shutdown when you shut down."
- preferStartupSound: false
  $name: "Startup and Shutdown when signing in and out"
  $description: "Play Startup and Shutdown when you sign in and out. Log On and Log Off then only play when you lock the PC or switch users."
- fileAssoc: true
  $name: "Open sound scheme files"
  $description: "Double-click a .ths or .soundpack file to load it with this mod."
- convertProprietary: false
  $name: "Convert .soundpack files"
  $description: "When you import a .soundpack file, save a .ths copy beside it and move the original to the Recycle Bin."
- patchStartupSound: false
  $name: "Patch the built-in startup sound"
  $description: "Writes your Startup sound into Windows' own startup sound file. Needs admin, and Windows updates undo it. Not recommended on Windows 10 and 11."
- animations: true
  $name: "Animations"
  $description: "Short fades and slides in the settings window. Off, changes are instant."
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Save, then reopen settings to apply."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Save, then reopen settings to apply."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "A speaker icon in the system tray. Click it to open these settings, right-click it for a menu. When off, open settings from Windhawk."
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <shldisp.h>
#include <exdisp.h>
#include <shlguid.h>
#include <servprov.h>
#include <commctrl.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <imm.h>
#include <winevt.h>
#include <tlhelp32.h>
#include <sddl.h>
#include <shellscalingapi.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include <mmsystem.h>
#include <wtsapi32.h>
#include <bcrypt.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>
#include <winhttp.h>
#include <propvarutil.h>
#include <aclapi.h>
#include <commdlg.h>
#include <wincrypt.h>
#include <fstream>
#include <thread>
#include <functional>
#include <cstdarg>
#include <cstdio>

#include <windhawk_tool_mod.h>

namespace smset {
void OpenSettingsWindow();
void CloseSettingsWindow();
extern std::atomic<HWND> g_settingsWnd;
}  // namespace smset

void WhTool_ModUninit();

// ---------------------------------------------------------------------------
// The engine API the settings window calls (engine-api.h, pasted as is)
// ---------------------------------------------------------------------------

// The engine API that pages.cpp (the settings window, namespace smset) calls.
// core.cpp implements every function below at global scope, BEFORE the settings block is
// appended, so the block sees full definitions (one translation unit, no headers at build).
// Every function is safe to call from the settings window's thread: engine work that touches
// the registry or the Media folder takes g_smLock (a std::recursive_mutex) itself.
// Strings shown to the user are plain English, short, no file paths unless noted.

constexpr int kSmEventCount = 31;
constexpr UINT WM_APP_SM_ASYNC = WM_APP + 3;  // Posted to the settings window when async work moves.

struct SmEventInfo {
    PCWSTR file;  // File name without .wav, e.g. L"Startup" (same as upstream SoundEvent.FileName).
    PCWSTR name;  // Display name, e.g. L"Log On".
    PCWSTR desc;  // Description, e.g. L"User session resume".
};
extern const SmEventInfo kSmEvents[kSmEventCount];  // Upstream order: Startup ... LoadScheme.

struct SmPreset {
    PCWSTR category;  // Folder with '-' as ' ', e.g. L"Other OS".
    PCWSTR path;      // Repo path, e.g. L"Other-OS/Windows XP.ths".
    PCWSTR name, author, about;
    int sizeKB;
};
extern const SmPreset kSmPresets[];
extern const int kSmPresetCount;

struct SmMeta {
    std::wstring name, author, about;
};

// --- Scheme state ---------------------------------------------------------------------
bool SmSoundExists(int ev);            // Media\<file>.wav exists.
bool SmSoundDisabled(int ev);          // In DisabledSoundEvents.
std::wstring SmSoundPath(int ev);      // Full path of Media\<file>.wav (may not exist).
std::wstring SmSoundInfo(int ev);      // Short line, e.g. L"2.4 s" or L"No sound"; cached by file time.
SmMeta SmGetMeta();                    // From Media\Scheme.ini.
void SmSetMeta(const SmMeta& m);       // Writes Scheme.ini (UTF-8, [SchemeInfo] name= author= about=).
std::wstring SmThumbPath();            // Media\Scheme.png, or L"" when there is none.
UINT SmThumbVersion();                 // Bumps whenever the picture changes (so the window reloads it).

// --- Per-sound actions (each re-applies the scheme so Windows uses the change at once) ---
bool SmPlay(int ev);                   // Async PlaySound of the scheme file; false if none.
void SmStopPlaying();
bool SmReplaceSound(int ev, const std::wstring& file, std::wstring& error);  // Any audio: WAV kept, others converted; 30 s cap.
bool SmResetSound(int ev, std::wstring& error);   // Back to the Windows default sound for this event (CopyDefault for one).
void SmRemoveSound(int ev);                        // Deletes the file (event becomes silent).
void SmSetDisabled(int ev, bool disabled);         // Toggle; updates the INI and re-applies.
void SmShowInFolder(int ev);                       // Explorer with the file selected (or the Media folder).

// --- Scheme actions ---
bool SmSetImage(const std::wstring& file, std::wstring& error);  // Any picture WIC reads, saved 100x100 PNG.
void SmRemoveImage();
bool SmImport(const std::wstring& file, std::wstring& error);    // .ths/.zip/.soundpack; replaces all sounds and meta.
bool SmExportThs(const std::wstring& file, std::wstring& error);
bool SmExportThemepack(const std::wstring& file, std::wstring& error);
bool SmLoadWindowsDefaults(std::wstring& error);                 // Upstream "Reset": CopyDefault for all, meta cleared.
struct SmSystemScheme { std::wstring id, name; };
std::vector<SmSystemScheme> SmSystemSchemes();                   // HKCU AppEvents\Schemes\Names except SoundManager.
bool SmLoadSystemScheme(const std::wstring& id, std::wstring& error);  // Copies that scheme's sounds in.
void SmOpenDataFolder();
bool SmReinstall(std::wstring& error);   // Setup + Apply again.
bool SmUninstall(std::wstring& error);   // Upstream Uninstall: Windows scheme back, SoundManager scheme removed.
bool SmIsActive();                       // HKCU AppEvents\Schemes default value == L"SoundManager".

// --- Presets (downloads run on a worker thread; it posts WM_APP_SM_ASYNC to notify) ---
// action 0 = preview (download, play its Startup or Logon sound), 1 = load (download, SmImport).
void SmPresetStart(int preset, int action, HWND notify);
bool SmPresetCached(int preset);
// Busy preset index or -1, and a status line for the footer (empty when idle). done/error are
// set once when a job finishes, then cleared by the read.
int SmPresetBusy();
std::wstring SmPresetStatus(bool& error, bool& finished);

// --- Offers shown on the Scheme page ---
// A file the owner opened from Explorer (.ths/.soundpack double-click) waiting for "Load".
std::wstring SmPendingFile();       // L"" when none.
void SmClearPendingFile();

// ---------------------------------------------------------------------------
// Sound events (upstream SoundEvent.cs, English names)
// ---------------------------------------------------------------------------

const SmEventInfo kSmEvents[kSmEventCount] = {
    {L"Startup", L"Startup", L"System start"},
    {L"Shutdown", L"Shutdown", L"System shutdown"},
    {L"Logon", L"Log On", L"User session resume"},
    {L"Logoff", L"Log Off", L"User session suspend"},
    {L"Information", L"Information", L"Information message sound"},
    {L"Question", L"Question", L"Interrogative message"},
    {L"Warning", L"Warning", L"Warning message"},
    {L"Error", L"Error", L"Error message"},
    {L"DeviceConnect", L"USB Connect", L"Connecting a USB device"},
    {L"DeviceDisconnect", L"USB Remove", L"Removing a USB device"},
    {L"DeviceFail", L"USB Error", L"USB device failure"},
    {L"Default", L"Default", L"Default Windows sound"},
    {L"Balloon", L"Balloon", L"Notification"},
    {L"Navigate", L"Navigate", L"Navigate in Explorer and Internet Explorer"},
    {L"RecycleBin", L"Recycle Bin", L"Emptying the recycle bin"},
    {L"UAC", L"Admin Access", L"When an application requests Administrator privileges (Vista and greater)"},
    {L"BatteryLow", L"Battery Low", L"Low battery warning"},
    {L"BatteryCritical", L"Battery Critical", L"Critical battery warning"},
    {L"Email", L"Email", L"Receiving an Email"},
    {L"Reminder", L"Reminder", L"Calendar reminder"},
    {L"Print", L"Print", L"Print complete"},
    {L"AppOpen", L"Launch App", L"Launching an application"},
    {L"AppClose", L"Close App", L"Closing an application"},
    {L"Minimize", L"Minimize App", L"Minimize an app to the taskbar"},
    {L"UnMinimize", L"Restore App", L"Restore an app from the taskbar"},
    {L"Maximize", L"Maximize app", L"Maximize an app to fill the screen"},
    {L"UnMaximize", L"Reduce app", L"Un-Maximize an app that took up the whole screen"},
    {L"Menu", L"Menu", L"Opening a context menu"},
    {L"MenuCommand", L"Menu Click", L"Selecting an option from a context menu"},
    {L"Select", L"Select", L"Selecting an item on the desktop or in the file explorer"},
    {L"LoadScheme", L"Load Scheme", L"Loading the Sound Scheme"},
};

// Registry keys (under HKCU\AppEvents\Schemes\Apps) and the Windows XP file name of each event.
struct SmEventData {
    PCWSTR keys[3];
    PCWSTR legacy;
};

static const SmEventData kEvData[kSmEventCount] = {
    {{L".Default\\SystemStart"}, L"D\u00E9marrage"},
    {{L".Default\\SystemExit"}, L"Arr\u00EAt du syst\u00E8me"},
    {{L".Default\\WindowsLogon"}, L"Ouverture de session"},
    {{L".Default\\WindowsLogoff"}, L"Fermeture de session"},
    {{L".Default\\SystemAsterisk"}, L"Erreur"},
    {{L".Default\\SystemQuestion"}, nullptr},
    {{L".Default\\SystemExclamation"}, L"Exclamation"},
    {{L".Default\\SystemHand"}, L"Arr\u00EAt critique"},
    {{L".Default\\DeviceConnect"}, L"Insertion d'un mat\u00E9riel"},
    {{L".Default\\DeviceDisconnect"}, L"Suppression d'un mat\u00E9riel"},
    {{L".Default\\DeviceFail"}, L"\u00C9chec d'un mat\u00E9riel"},
    {{L".Default\\.Default"}, L"Ding"},
    {{L".Default\\SystemNotification", L".Default\\Notification.Default", L"Explorer\\SystemNotification"}, L"Infobulle"},
    {{L"Explorer\\Navigating"}, L"Menu D\u00E9marrer"},
    {{L"Explorer\\EmptyRecycleBin"}, L"Corbeille"},
    {{L".Default\\WindowsUAC"}, nullptr},
    {{L".Default\\LowBatteryAlarm"}, nullptr},
    {{L".Default\\CriticalBatteryAlarm"}, nullptr},
    {{L".Default\\MailBeep", L".Default\\Notification.Mail"}, nullptr},
    {{L".Default\\Notification.Reminder"}, nullptr},
    {{L".Default\\PrintComplete"}, nullptr},
    {{L".Default\\Open"}, nullptr},
    {{L".Default\\Close"}, nullptr},
    {{L".Default\\Minimize"}, nullptr},
    {{L".Default\\RestoreUp"}, nullptr},
    {{L".Default\\Maximize"}, nullptr},
    {{L".Default\\RestoreDown"}, nullptr},
    {{L".Default\\MenuPopup"}, nullptr},
    {{L".Default\\MenuCommand"}, nullptr},
    {{L".Default\\CCSelect"}, nullptr},
    {{L".Default\\ChangeTheme"}, nullptr},
};

constexpr int kEvStartup = 0, kEvShutdown = 1, kEvLogon = 2, kEvLogoff = 3, kEvLoadScheme = 30;

// ---------------------------------------------------------------------------
// Presets (the scheme list of ORelio/Sound-Manager-Schemes)
// ---------------------------------------------------------------------------

const SmPreset kSmPresets[] = {
{L"Abstract", L"Abstract/Andre-Louis-44.1K.ths", L"Andre Louis Sounds Scheme", L"Andre Louis", L"", 3899},
{L"Abstract", L"Abstract/Cheese-Cube.ths", L"Cheese Cube", L"Seediffusion", L"https://github.com/seediffusion/CubeSuite", 4249},
{L"Abstract", L"Abstract/Crystallio.ths", L"Crystallio", L"Grosswired & alismanpro, slight edits by ORelio", L"An orchestral inspired sound scheme", 7804},
{L"Abstract", L"Abstract/Crystal-Sounds.ths", L"Crystal", L"DanielH", L"Crystal Sounds", 6046},
{L"Abstract", L"Abstract/Demure.ths", L"Demure", L"jbgs", L"", 1425},
{L"Abstract", L"Abstract/Discord.ths", L"Discord", L"Discord Inc, ported by TheInsane101", L"Discord sound effects", 2888},
{L"Abstract", L"Abstract/Elegant.ths", L"Elegant", L"jarrypl (with slight modifications by ORelio)", L"Elegant and unnoisy, i hope it's tasteful.", 1424},
{L"Abstract", L"Abstract/Krystal.ths", L"Krystal", L"arVinyl", L"http://arvinyl.wincustomize.com/", 5097},
{L"Abstract", L"Abstract/VOX.ths", L"V O X", L"vStyler (with slight modifications by ORelio)", L"To accompany the V O X windowblinds skin.", 7685},
{L"Entertainment", L"Entertainment/AnimeSounds.ths", L"Anime Theme Sounds", L"DanielH", L"Anime Windows Sounds", 7068},
{L"Entertainment", L"Entertainment/Konata-Izumi.ths", L"Konata Izumi", L"Ninesen & ORelio, files from u/Bleu_Chicken, MagicMaker, Cooper B. Chance", L"https://bsky.app/profile/ninesen.bsky.social", 2301},
{L"Entertainment", L"Entertainment/Naheulbeuk.ths", L"Naheulbeuk", L"", L"", 3456},
{L"Entertainment", L"Entertainment/Nanami-Madobe.ths", L"Nanami Madobe", L"Microsoft Corporation", L"https://archive.org/details/NanamiMadobeTheme", 2402},
{L"Entertainment", L"Entertainment/StarWars.ths", L"Star Wars", L"ORelio", L"https://microzoom.fr/", 3816},
{L"Entertainment", L"Entertainment/The-Simpsons-FR.ths", L"Les Simpsons (FR)", L"ORelio", L"https://microzoom.fr/", 4609},
{L"Entertainment", L"Entertainment/TV-Radio.ths", L"TV Shows & Radio", L"ORelio", L"https://microzoom.fr/", 5427},
{L"Games", L"Games/Age-Of-Empires.ths", L"Age Of Empires", L"Microsoft Game Studios", L"https://www.ageofempires.com/", 5547},
{L"Games", L"Games/Among-Us.ths", L"Among Us", L"InnerSloth / ORelio", L"https://innersloth.com/", 6172},
{L"Games", L"Games/Angry-Birds.ths", L"Angry Birds", L"Rovio Entertainment", L"https://www.angrybirds.com/", 1132},
{L"Games", L"Games/Animal-Crossing-1.ths", L"Animal Crossing: New Horizons", L"Nintendo / ORelio", L"https://animal-crossing.com/", 3011},
{L"Games", L"Games/Animal-Crossing-2.ths", L"Animal Crossing: New Horizons", L"Nintendo / ORelio", L"https://animal-crossing.com/", 4619},
{L"Games", L"Games/Arcade.ths", L"Arcade", L"ORelio", L"https://microzoom.fr/", 1368},
{L"Games", L"Games/Bullet-Asylum.ths", L"Bullet Asylum", L"UberGeekGames", L"http://ubergeekgames.com/bulletasylum/", 4640},
{L"Games", L"Games/Chickens-Cant-Fly.ths", L"Chickens Can't Fly", L"Amused Sloth", L"https://www.amusedsloth.com/", 2478},
{L"Games", L"Games/Deltarune.ths", L"deltarune", L"Toby Fox (Ported By gyevent)", L"https://deltarune.com/", 7984},
{L"Games", L"Games/Diablo-II.ths", L"Diablo II", L"Blizzard", L"https://web.archive.org/web/20020124192605/http://www.blizzard.com/diablo2/", 14831},
{L"Games", L"Games/Disco-Elysium.ths", L"Disco Elysium", L"ZA/UM, shyshallows", L"Sounds from the narrative CRPG Disco Elysium.", 8389},
{L"Games", L"Games/Escape-From-Tarkov.ths", L"Escape From Tarkov Sounds", L"Scav Raiders", L"https://www.escapefromtarkov.com", 3987},
{L"Games", L"Games/Five-Nights-at-Freddys-1.ths", L"FNAF 1", L"Scott Cawthon, ported by TheInsane101", L"Five Nights at Freddy's 1's sound effects", 2500},
{L"Games", L"Games/Friday-Night-Funkin.ths", L"FNF", L"The Funkin Crew, ported by sirthegamercoder", L"Friday Night Funkin's sound effects", 2553},
{L"Games", L"Games/Fruit-Ninja.ths", L"Fruit Ninja", L"Halfbrick Studios", L"https://fruitninja.com/", 2180},
{L"Games", L"Games/GameBoy.ths", L"Game Boy", L"ORelio", L"https://microzoom.fr/", 305},
{L"Games", L"Games/Garrys-Mod.ths", L"Garry's Mod", L"Valve, Facepunch, & Superdave938", L"The HL2 Scheme with some GMod sounds tossed in \u2022 superdave.straw.page", 5332},
{L"Games", L"Games/Geometry-Dash.ths", L"Geometry Dash", L"Robtop Games, ported by realmattlmao & TheInsane101", L"Geometry Dash 2.2's sound effects", 3603},
{L"Games", L"Games/Half-Life-1.ths", L"Half-Life 1", L"Valve & Superdave938", L"A Scheme Based off Half-Life 1 \u2022 superdave.straw.page", 2078},
{L"Games", L"Games/Half-Life-2.ths", L"Half-Life 2", L"Valve & Superdave938", L"A Scheme Based off Half-Life 2 \u2022 superdave.straw.page", 6741},
{L"Games", L"Games/Halo-4.ths", L"Halo 4 Heroes", L"Microsoft Game Studios", L"https://www.halowaypoint.com/", 3891},
{L"Games", L"Games/Hypnospace-Outlaw-Default.ths", L"Hypnospace Outlaw Default", L"No More Robots & Nik Nikovsky", L"Sounds from the default theme of the \"hypnospace outlaw\" game", 4148},
{L"Games", L"Games/Hypnospace-Outlaw-Gleam.ths", L"Hypnospace Outlaw Gleam", L"No More Robots & Nik Nikovsky", L"Sounds from the Gleam theme of the \"hypnospace outlaw\" game", 7420},
{L"Games", L"Games/Mega-Man-Legends.ths", L"Mega Man Legends", L"Capcom, with edits by ORelio", L"http://megaman.capcom.com/", 1038},
{L"Games", L"Games/Metal-Gear-Solid.ths", L"Metal Gear Solid Theme", L"Daniel Alonso (slightly edited by ORelio)", L"A collection of Metal Gear Solid sounds.", 2729},
{L"Games", L"Games/Minecraft-Beta.ths", L"Minecraft Beta", L"ORelio", L"https://microzoom.fr/", 6337},
{L"Games", L"Games/Osu.ths", L"osu!", L"Dean Lewis \"peppy\" Herbert", L"osu.ppy.sh", 1628},
{L"Games", L"Games/Solatorobo.ths", L"Solatorobo", L"CyberConnect2", L"https://en.wikipedia.org/wiki/Solatorobo:_Red_the_Hunter", 6474},
{L"Games", L"Games/Sony-PS4.ths", L"PS4", L"Sony Entertainment Interactive", L"PS4 System Sounds", 2808},
{L"Games", L"Games/Sony-PSP.ths", L"Sony PSP", L"Sony Entertainment, Darthagnon, NikNikovsky, ORelio", L"https://archive.org/details/psp-sounds.rco/", 2969},
{L"Games", L"Games/Super-Mario-Bros.ths", L"Super Mario Bros.", L"ORelio", L"https://microzoom.fr/", 1233},
{L"Games", L"Games/Undertale-1.ths", L"UNDERTALE", L"Toby Fox / ORelio", L"https://undertale.com/", 8525},
{L"Games", L"Games/Undertale-2.ths", L"Undertale", L"Toby Fox / CaytieCat", L"https://undertale.com/", 2000},
{L"Games", L"Games/Wii.ths", L"Wii", L"MasterBruce", L"http://masterbruce.wincustomize.com/", 8687},
{L"Games", L"Games/Winbrick-1.ths", L"Winbrick", L"Soft & Fun / ORelio", L"http://winbrick.de/", 1109},
{L"Games", L"Games/Winbrick-2.ths", L"Winbrick 2", L"Soft & Fun / ORelio", L"http://winbrick.de/", 928},
{L"Games", L"Games/Worms-Menu.ths", L"Worms World Party", L"ORelio", L"http://wwp.team17.com/", 754},
{L"Games", L"Games/Worms-Sounds.ths", L"Worms World Party", L"ORelio", L"http://wwp.team17.com", 1870},
{L"Games", L"Games/Worms-Voices-EN.ths", L"Worms World Party", L"ORelio", L"http://wwp.team17.com", 437},
{L"Games", L"Games/Worms-Voices-FR.ths", L"Worms World Party", L"ORelio", L"http://wwp.team17.com", 398},
{L"Games", L"Games/Xbox-360.ths", L"Xbox 360 (Metro)", L"Microsoft Corporation", L"Sounds from the Metro Xbox 360.", 3805},
{L"Games", L"Games/Zelda-Echoes-Of-Wisdom.ths", L"The Legend of Zelda - Echoes of Wisdom", L"Nintendo / ORelio", L"https://www.nintendo.com/us/store/products/the-legend-of-zelda-echoes-of-wisdom-switch/", 7842},
{L"Holiday", L"Holiday/Christmas.ths", L"Christmas", L"ORelio", L"https://microzoom.fr/", 5041},
{L"Holiday", L"Holiday/Halloween.ths", L"Halloween", L"ORelio", L"https://microzoom.fr/", 6056},
{L"Misc", L"Misc/CatMania.ths", L"Cat Mania", L"CatMan alias VBT2", L"If it's fit, I sit", 8902},
{L"Misc", L"Misc/Cultural.ths", L"Cultural", L"RobJK", L"http://robjk.wincustomize.com/", 8644},
{L"Misc", L"Misc/DECtalk-4.3.ths", L"DECtalk 4.3", L"Unknown", L"https://dectalk.nu/Software%20and%20Manuals/Software/DECtalk/Sound%20Schemes/Dt43Sounds.zip", 342},
{L"Misc", L"Misc/DECtalk-4.3-4.4.ths", L"DECtalk 4.3/4.4", L"x0", L"Combined scheme from the DECtalk 4.3 and DECtalk 4.4 sound schemes", 1551},
{L"Misc", L"Misc/DECtalk-4.4.ths", L"DECtalk 4.4", L"Unknown", L"https://dectalk.nu/Software%20and%20Manuals/Software/DECtalk/Sound%20Schemes/dt440.zip", 1671},
{L"Misc", L"Misc/DECtalk-Scheme.ths", L"DECtalk Sound Scheme", L"Aksel Christoffersen", L"DECtalk sounds for Windows, sourced from https://dectalk.nu/Software%20and%20Manuals/Software/DECtalk/Sound%20Schemes/DECtalk%20Sound%20Scheme%20by%20Aksel%20Christoffersen.zip", 620},
{L"Misc", L"Misc/Majorly-G.ths", L"Majorly G", L"Currently Untitled Audio", L"Formerly at https://currentlyuntitled.design", 6236},
{L"Misc", L"Misc/Nokia-Old.ths", L"Nokia old", L"Sergiaws", L"This scheme is based on the nokia ringtones of old phones (released around 2006)", 9016},
{L"Misc", L"Misc/TropicalFrogs.ths", L"Tropical Frogs", L"Warreni", L"http://warreni.wincustomize.com/", 1626},
{L"Other OS", L"Other-OS/KDE-Plasma.ths", L"KDE Plasma 6", L"K Desktop Environment e.V.", L"A mix of the Ocean/Oxygen theme with some freedesktop stuff", 3586},
{L"Other OS", L"Other-OS/Linux-Celestial-2.0.ths", L"Celestial Linux 2.0", L"Unknown", L"", 2971},
{L"Other OS", L"Other-OS/Linux-Celestial-2.1.ths", L"Celestial Linux 2.1", L"Unknown", L"", 4308},
{L"Other OS", L"Other-OS/Linux-Ubuntu-Classic.ths", L"Ubuntu classic sound scheme", L"Canonical", L"Classic Ubuntu sound scheme from 18.04 and older", 2036},
{L"Other OS", L"Other-OS/Linux-Ubuntu-Newer.ths", L"Ubuntu newer sound scheme", L"Canonical", L"Modern Ubuntu from 20.04 and newer", 1673},
{L"Other OS", L"Other-OS/MacOS-Monterey.ths", L"macOS Monterey", L"Apple Inc.", L"Sourced from a macOS Monterey install.", 2144},
{L"Other OS", L"Other-OS/OxygenOS.ths", L"OxygenOS", L"OnePlus, Paulinux", L"Sounds from Oneplus phones. Contact: t.me/paulinuks", 3500},
{L"Windows", L"Windows/Beta/Windows-10-build-10074.ths", L"Windows 10 build 10074", L"Microsoft Corporation", L"https://www.microsoft.com/", 1668},
{L"Windows", L"Windows/Beta/Windows-XP-Build-2481.ths", L"Windows XP Build 2481", L"Microsoft Corporation", L"This is the XP build 2481 (pre RTM) which countains XP sounds in stereo while the traditional scheme put it in mono.", 2373},
{L"Windows", L"Windows/Custom/Futuristic7.ths", L"Futuristic7", L"AeroPurple (slightly edited by ORelio)", L"Made with Ableton 11", 6100},
{L"Windows", L"Windows/Custom/Futuristic7-II.ths", L"Futuristic7 II", L"AeroPurple", L"Made using Ableton 11.", 11843},
{L"Windows", L"Windows/Custom/MetroAero-20XX.ths", L"MetroAero-20XX", L"Microsoft Corporation **remixed by DNHND28", L"Millennium-20XX, but some sounds are made to fit around more recent times, like the mid 00's, early 10's & beyond", 4948},
{L"Windows", L"Windows/Custom/Millennium-20XX.ths", L"Millennium-20XX", L"Microsoft Corporation **remixed by DNHND28", L"Various 1990s, 2000s and 2010s Windows, Microsoft and custom sounds", 4776},
{L"Windows", L"Windows/Custom/MillenniumPast-19XX.ths", L"Millennium Past-19XX", L"Microsoft Corporation **remixed by DNHND28", L"Various Windows, Microsoft and custom sounds from the oldest versions of Windows & 9x to Windows 2000 & early NT", 8473},
{L"Windows", L"Windows/Custom/Se7XPerience.ths", L"Se7XPerience", L"David Mounder", L"https://youtube.com/watch?v=5THkfr5jf-k", 3724},
{L"Windows", L"Windows/Custom/WindOS.ths", L"WindOS", L"BOG", L"Custom Windows sounds.", 4898},
{L"Windows", L"Windows/Custom/Windows-11-Liquid-Glass.ths", L"Windows 11 Liquid Glass", L"Amr Saad Dewa", L"A mix of Mac OS X, Oxygen OS and Linux sounds", 2795},
{L"Windows", L"Windows/Custom/Windows-7-8-RP-Mix.ths", L"Windows 8 Consumer/Release Preview", L"Microsoft Corporation & Sergiaws", L"this is a modified version of Windows 8 Release preview & Consumer Preview sound schemes. Just the notification sound and Windows 7 sounds are configured correctly. The other sounds are sounds of other Windows 8 events (mostly newer events) which aren't pressent in Windows 7 and older. And since these Windows 8 builds use Windows 7 sounds most of the time, I kept a lot of Windows 7 sounds as you can see.", 1955},
{L"Windows", L"Windows/Custom/Windows-7-Orchestra.ths", L"Windows7 Orchestra", L"bluewave", L"Made by bluewave-y5g on YouTube", 4092},
{L"Windows", L"Windows/Custom/Windows-8-10-11-Mix.ths", L"Windows 8/10/11 remix", L"Microsoft Corporation / Sergiaws", L"https://www.microsoft.com/", 1716},
{L"Windows", L"Windows/Custom/Windows-8-10-Mix.ths", L"Windows 8-10 Mix", L"Microsoft Corporation / ORelio", L"https://www.microsoft.com/", 2140},
{L"Windows", L"Windows/Custom/Windows-9x-2000-Mix.ths", L"Windows 9x/2000 remix", L"Microsoft Corporation / Sergiaws", L"Here is a sound scheme which countains some Windows 95 and 98/2000 sounds", 1677},
{L"Windows", L"Windows/Custom/Windows-Beta-Mix.ths", L"Windows Beta Sound Mix", L"Microsoft Corporation / Sergiaws", L"https://www.microsoft.com/", 1522},
{L"Windows", L"Windows/Custom/Windows-Longhorn-Samsung-Theme.ths", L"Samsung Theme (Aka Windows Longhorn)", L"Samsung Electronics Co.,LTD.", L"https://archive.org/details/samsung-theme", 5773},
{L"Windows", L"Windows/Custom/Windows-Mobile-5.0-XP.ths", L"Windows Mobile 5.0-XP", L"Microsoft Corporation & Sergiaws", L"There are some interesting Windows Movile 5.0 sounds, so I decided to create a pack where I convine some XP sounds (Windows PC OS at Windows Movile 5.0's time) with some Windows Movile 5.0 alarms and sounds", 305},
{L"Windows", L"Windows/Custom/Windows-Vista-11.ths", L"Vista 11", L"Dewa Gee (AmrSaadMega)", L"@AmrsSaadMEGA", 2736},
{L"Windows", L"Windows/Custom/Windows-XP-Tribute-Sergiaws.ths", L"Windows XP Tribute", L"Sergiaws", L"This is a tribute to Windows XP, an operating system with 20 years old since 25 Octover 2021. The sounds were obtained from various sources.", 4674},
{L"Windows", L"Windows/Custom/Windows-XP-Vista-Mix.ths", L"Windows XP-Vista remix", L"Microsoft Corporation / Sergiaws", L"This is a remix between XP and Vista (normal and extra) sounds.", 2134},
{L"Windows", L"Windows/Extra/Windows-7-Afternoon.ths", L"Afternoon", L"Microsoft Corporation", L"https://www.microsoft.com/", 2714},
{L"Windows", L"Windows/Extra/Windows-7-Calligraphy.ths", L"Calligraphy", L"Microsoft Corporation", L"https://www.microsoft.com/", 2974},
{L"Windows", L"Windows/Extra/Windows-7-Characters.ths", L"Characters", L"Microsoft Corporation", L"https://www.microsoft.com/", 2172},
{L"Windows", L"Windows/Extra/Windows-7-Cityscape.ths", L"Cityscape", L"Microsoft Corporation", L"https://www.microsoft.com/", 2658},
{L"Windows", L"Windows/Extra/Windows-7-Delta.ths", L"Delta", L"Microsoft Corporation", L"https://www.microsoft.com/", 2693},
{L"Windows", L"Windows/Extra/Windows-7-Eerie-Autumn.ths", L"Eerie Autumn", L"Microsoft Corporation", L"https://support.microsoft.com/en-us/windows/desktop-themes-94880287-6046-1d35-6d2f-35dee759701e", 4387},
{L"Windows", L"Windows/Extra/Windows-7-Festival.ths", L"Festival", L"Microsoft Corporation", L"https://www.microsoft.com/", 2090},
{L"Windows", L"Windows/Extra/Windows-7-Garden.ths", L"Garden", L"Microsoft Corporation", L"https://www.microsoft.com/", 2337},
{L"Windows", L"Windows/Extra/Windows-7-Heritage.ths", L"Heritage", L"Microsoft Corporation", L"https://www.microsoft.com/", 2359},
{L"Windows", L"Windows/Extra/Windows-7-Landscape.ths", L"Landscape", L"Microsoft Corporation", L"https://www.microsoft.com/", 2196},
{L"Windows", L"Windows/Extra/Windows-7-Quirky.ths", L"Quirky", L"Microsoft Corporation", L"https://www.microsoft.com/", 2041},
{L"Windows", L"Windows/Extra/Windows-7-Raga.ths", L"Raga", L"Microsoft Corporation", L"https://www.microsoft.com/", 2589},
{L"Windows", L"Windows/Extra/Windows-7-Savanna.ths", L"Savanna", L"Microsoft Corporation", L"https://www.microsoft.com/", 1955},
{L"Windows", L"Windows/Extra/Windows-7-Sonata.ths", L"Sonata", L"Microsoft Corporation", L"https://www.microsoft.com/", 2334},
{L"Windows", L"Windows/Extra/Windows-98-Plus.ths", L"Windows 98 plus! Windows 98", L"Microsoft Corporation", L"These sounds came from the Windows 98 plus! Scheme.", 2622},
{L"Windows", L"Windows/Extra/Windows-98-Plus-Architecture.ths", L"Windows 98 Plus! Architecture", L"Microsoft Corporation", L"https://www.microsoft.com/", 3166},
{L"Windows", L"Windows/Extra/Windows-98-Plus-Baseball.ths", L"Windows 98 plus! Baseball", L"Microsoft Corporation", L"https://www.microsoft.com/", 495},
{L"Windows", L"Windows/Extra/Windows-98-Plus-Beta.ths", L"Windows 98 Plus! Beta sounds", L"Microsoft Corporation", L"This sound Scheme is pressent in some of Microsoft plus! beta sound schemes, such as the beta version of Science Fiction", 2047},
{L"Windows", L"Windows/Extra/Windows-98-Plus-Geometry.ths", L"Windows 98 Plus! Geometry", L"Microsoft Corporation", L"https://www.microsoft.com/", 3596},
{L"Windows", L"Windows/Extra/Windows-98-Plus-Jazz.ths", L"Windows 98 Plus! Jazz", L"Microsoft Corporation", L"https://www.microsoft.com/", 1560},
{L"Windows", L"Windows/Extra/Windows-98-Plus-Musica.ths", L"Windows 98 plus! Musica", L"Microsoft Corporation", L"https://www.microsoft.com/", 263},
{L"Windows", L"Windows/Extra/Windows-98-Plus-Robotz.ths", L"Windows 98 plus! Robotz", L"Microsoft Corporation", L"https://www.microsoft.com/", 1472},
{L"Windows", L"Windows/Extra/Windows-98-Plus-Science-Fiction.ths", L"Windows 98 Plus! Science Fiction", L"Microsoft Corporation", L"https://www.microsoft.com/", 4159},
{L"Windows", L"Windows/Extra/Windows-98-Plus-Space.ths", L"Windows 98 plus! Space", L"Microsoft Corporation", L"https://www.microsoft.com/", 289},
{L"Windows", L"Windows/Extra/Windows-98-Plus-World-Traveller.ths", L"Windows 98 plus! World Traveller", L"Microsoft Corporation", L"https://www.microsoft.com/", 2200},
{L"Windows", L"Windows/Extra/Windows-9x-2000-Utopia.ths", L"Utopia", L"Microsoft Corporation", L"This scheme appeared in Microsoft Plus! 95 and it is pressent on Windows 2000", 399},
{L"Windows", L"Windows/Extra/Windows-9x-Dangerous-Creatures.ths", L"Windows 95 plus! Dangerous Creatures", L"Microsoft Corporation", L"https://www.microsoft.com/", 243},
{L"Windows", L"Windows/Extra/Windows-9x-Golden-Era.ths", L"Windows 95 plus! The Golden Era", L"Microsoft Corporation", L"https://www.microsoft.com/", 285},
{L"Windows", L"Windows/Extra/Windows-9x-Inside-Your-Computer.ths", L"Windows 95 plus! Inside Your Computer", L"Microsoft Corporation", L"https://www.microsoft.com/", 295},
{L"Windows", L"Windows/Extra/Windows-9x-Jungle.ths", L"Jungle", L"Microsoft Corporation", L"This Scheme appeared on Microsoft Plus! For Windows 95 and then appeared in newer versions of Windows like Windows NT 4 or old builds of Windows 2000", 1292},
{L"Windows", L"Windows/Extra/Windows-9x-Leonardo-Da-Vinci.ths", L"Windows 95 plus! Leonardo Da Vinci", L"Microsoft Corporation", L"https://www.microsoft.com/", 289},
{L"Windows", L"Windows/Extra/Windows-9x-Mystery.ths", L"Windows 95 plus! Mystery", L"Microsoft Corporation", L"https://www.microsoft.com/", 331},
{L"Windows", L"Windows/Extra/Windows-9x-Nature.ths", L"Windows 95 plus! Nature", L"Microsoft Corporation", L"https://www.microsoft.com/", 328},
{L"Windows", L"Windows/Extra/Windows-9x-Science.ths", L"Windows 95 plus! Science", L"Microsoft Corporation", L"https://www.microsoft.com/", 295},
{L"Windows", L"Windows/Extra/Windows-9x-Sixties-USA.ths", L"Windows 95 plus! The 60's USA", L"Microsoft Corporation", L"https://www.microsoft.com/", 329},
{L"Windows", L"Windows/Extra/Windows-9x-Sports.ths", L"Windows 95 plus! Sports", L"Microsoft Corporation", L"https://www.microsoft.com/", 330},
{L"Windows", L"Windows/Extra/Windows-9x-Travel.ths", L"Windows 95 plus! Travel", L"Microsoft Corporation", L"https://www.microsoft.com/", 339},
{L"Windows", L"Windows/Extra/Windows-9x-Underwater.ths", L"Underwater", L"Microsoft Corporation", L"https://www.microsoft.com/", 410},
{L"Windows", L"Windows/Extra/Windows-CE-Analogue.ths", L"Windows CE Analogue", L"Microsoft Corporation", L"", 49},
{L"Windows", L"Windows/Extra/Windows-CE-Metallic.ths", L"Windows CE Metallic", L"Microsoft Corporation", L"", 23},
{L"Windows", L"Windows/Extra/Windows-CE-Organic.ths", L"Windows CE Organic", L"Microsoft Corporation", L"", 35},
{L"Windows", L"Windows/Extra/Windows-CE-Pocket-PC-2000.ths", L"Windos CE Pocket PC 2002 Default", L"Microsoft Corporation", L"", 62},
{L"Windows", L"Windows/Extra/Windows-CE-UI-Set.ths", L"WinCE UI Set", L"", L"", 262},
{L"Windows", L"Windows/Extra/Windows-NT4-Ancient-Pathways.ths", L"Windows NT 4 Resource Pack Ancient Pathways", L"Microsoft Corporation", L"https://www.microsoft.com/", 232},
{L"Windows", L"Windows/Extra/Windows-Pocket-PC-2000.ths", L"Windows Pocket PC 2000", L"Microsoft Corporation", L"", 34},
{L"Windows", L"Windows/Extra/Windows-Vista-Glass.ths", L"Glass", L"Microsoft Corporation", L"https://www.microsoft.com/", 2279},
{L"Windows", L"Windows/Extra/Windows-Vista-Pearl.ths", L"Pearl", L"Microsoft Corporation", L"https://www.microsoft.com/", 2737},
{L"Windows", L"Windows/Extra/Windows-Vista-Tinker.ths", L"Windows Vista Tinker", L"Microsoft Corporation", L"This scheme cames from Windows Vista Ultimate extras and the tinker game", 2469},
{L"Windows", L"Windows/Extra/Windows-XP-Aquarium.ths", L"Aquarium", L"Microsoft Corporation", L"This scheme appears in Microsoft Plus! For XP", 1084},
{L"Windows", L"Windows/Extra/Windows-XP-Da-Vinci.ths", L"Da Vinci", L"Microsoft Corporation", L"This Scheme appears in Microsoft Plus! for XP", 1584},
{L"Windows", L"Windows/Extra/Windows-XP-Nature.ths", L"Nature", L"Microsoft Corporation", L"This scheme came from Microsoft Plus! XP", 909},
{L"Windows", L"Windows/Extra/Windows-XP-Space.ths", L"Space", L"Microsoft Corporation", L"This scheme came from Microsoft Plus! For XP", 1323},
{L"Windows", L"Windows/Faithful/Windows-10-Faithful.ths", L"Windows 10 - Faithful Experience", L"Microsoft Corporation", L"Original sound scheme with missing sounds", 1751},
{L"Windows", L"Windows/Faithful/Windows-11-Faithful.ths", L"Windows 11 - Faithful Experience", L"Microsoft Corporation", L"Original sound scheme with missing sounds", 2710},
{L"Windows", L"Windows/Faithful/Windows-2000-ME-Faithful.ths", L"Windows 2000/ME - Faithful Experience", L"Microsoft Corporation", L"Original sound scheme with missing sounds", 1754},
{L"Windows", L"Windows/Faithful/Windows-8-Faithful.ths", L"Windows 8 - Faithful Experience", L"Microsoft Corporation", L"Original sound scheme with missing sounds", 1410},
{L"Windows", L"Windows/Faithful/Windows-Vista-7-Faithful.ths", L"Windows Vista/7 - Faithful Experience", L"Microsoft Corporation", L"Original sound scheme with missing sounds", 2231},
{L"Windows", L"Windows/Faithful/Windows-XP-Faithful.ths", L"Windows XP - Faithful Experience", L"Microsoft Corporation", L"Original sound scheme with missing sounds", 1210},
{L"Windows", L"Windows/Main/Windows-10.ths", L"Windows 10", L"Microsoft Corporation", L"https://www.microsoft.com/", 2568},
{L"Windows", L"Windows/Main/Windows-11.ths", L"Windows 11", L"Microsoft Corporation", L"https://www.microsoft.com/", 3607},
{L"Windows", L"Windows/Main/Windows-2000-ME.ths", L"Windows 2000/ME", L"Microsoft Corporation", L"The official Windows 2000/ME sound scheme!", 1926},
{L"Windows", L"Windows/Main/Windows-8.ths", L"Windows 8", L"Microsoft Corporation", L"https://www.microsoft.com/", 2169},
{L"Windows", L"Windows/Main/Windows-Vista-7.ths", L"Windows Vista/7", L"Microsoft Corporation", L"https://www.microsoft.com/", 2470},
{L"Windows", L"Windows/Main/Windows-XP.ths", L"Windows XP", L"Microsoft Corporation", L"https://www.microsoft.com/", 1243},
};
const int kSmPresetCount = 161;

// ---------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------

bool g_smAnimations = true;  // Setting "animations"; the settings window reads it.

using Bytes = std::vector<uint8_t>;

static std::recursive_mutex g_smLock;  // Registry and Media folder work.
static std::atomic<bool> g_stop{false};

static std::atomic<bool> g_cMissing{true}, g_cSession{true}, g_cPreferStartup{false}, g_cAssoc{true},
    g_cConvert{false}, g_cPatch{false}, g_cTray{true};

template <class T>
struct Com {
    T* p = nullptr;
    Com() = default;
    Com(const Com&) = delete;
    Com& operator=(const Com&) = delete;
    ~Com() { Reset(); }
    void Reset() {
        if (p) p->Release();
        p = nullptr;
    }
    T** put() {
        Reset();
        return &p;
    }
    T* get() const { return p; }
    T* operator->() const { return p; }
    explicit operator bool() const { return p != nullptr; }
};

// ---------------------------------------------------------------------------
// Small helpers
// ---------------------------------------------------------------------------

static std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t\r\n");
    if (a == std::wstring::npos) return {};
    return s.substr(a, s.find_last_not_of(L" \t\r\n") - a + 1);
}

static std::wstring Lower(std::wstring s) {
    for (auto& c : s) c = (wchar_t)towlower(c);
    return s;
}

static bool EqCI(const std::wstring& a, const std::wstring& b) { return _wcsicmp(a.c_str(), b.c_str()) == 0; }

static bool FileExists(const std::wstring& p) {
    if (p.empty()) return false;
    DWORD a = GetFileAttributesW(p.c_str());
    return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY);
}

static bool DirExists(const std::wstring& p) {
    if (p.empty()) return false;
    DWORD a = GetFileAttributesW(p.c_str());
    return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_DIRECTORY);
}

static std::wstring Env(PCWSTR text) {
    WCHAR buf[MAX_PATH * 4]{};
    ExpandEnvironmentStringsW(text, buf, ARRAYSIZE(buf));
    return buf;
}

static std::wstring ReplaceAll(std::wstring s, const std::wstring& from, const std::wstring& to) {
    if (from.empty()) return s;
    for (size_t i = s.find(from); i != std::wstring::npos; i = s.find(from, i + to.size())) s.replace(i, from.size(), to);
    return s;
}

static std::wstring FileNameOf(const std::wstring& p) {
    size_t i = p.find_last_of(L"\\/");
    return i == std::wstring::npos ? p : p.substr(i + 1);
}

static std::wstring DirOf(const std::wstring& p) {
    size_t i = p.find_last_of(L"\\/");
    return i == std::wstring::npos ? std::wstring() : p.substr(0, i);
}

static std::wstring ExtOf(const std::wstring& p) {
    std::wstring n = FileNameOf(p);
    size_t i = n.find_last_of(L'.');
    return i == std::wstring::npos ? std::wstring() : Lower(n.substr(i));
}

static bool IsElevated() {
    HANDLE token = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) return false;
    TOKEN_ELEVATION e{};
    DWORD cb = 0;
    bool elevated = GetTokenInformation(token, TokenElevation, &e, sizeof(e), &cb) && e.TokenIsElevated;
    CloseHandle(token);
    return elevated;
}

static std::string WideToUtf8(const std::wstring& s) {
    if (s.empty()) return {};
    int n = WideCharToMultiByte(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0, nullptr, nullptr);
    std::string out(n > 0 ? n : 0, '\0');
    if (n > 0) WideCharToMultiByte(CP_UTF8, 0, s.data(), (int)s.size(), out.data(), n, nullptr, nullptr);
    return out;
}

static std::wstring Utf8ToWide(const char* p, size_t len, UINT cp = CP_UTF8) {
    if (!len) return {};
    int n = MultiByteToWideChar(cp, 0, p, (int)len, nullptr, 0);
    std::wstring out(n > 0 ? n : 0, L'\0');
    if (n > 0) MultiByteToWideChar(cp, 0, p, (int)len, out.data(), n);
    return out;
}

static bool ReadAll(const std::wstring& path, Bytes& out, size_t maxSize = (size_t)512 << 20) {
    out.clear();
    HANDLE h = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                           OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;
    LARGE_INTEGER sz{};
    bool ok = GetFileSizeEx(h, &sz) && (unsigned long long)sz.QuadPart <= maxSize;
    if (ok) {
        out.resize((size_t)sz.QuadPart);
        size_t done = 0;
        while (ok && done < out.size()) {
            DWORD got = 0, want = (DWORD)std::min<size_t>(out.size() - done, 1u << 24);
            ok = ReadFile(h, out.data() + done, want, &got, nullptr) && got > 0;
            done += got;
        }
        if (!ok) out.clear();
    }
    CloseHandle(h);
    return ok;
}

static bool WriteAll(const std::wstring& path, const void* data, size_t size) {
    HANDLE h = CreateFileW(path.c_str(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;
    bool ok = true;
    const uint8_t* p = (const uint8_t*)data;
    size_t done = 0;
    while (ok && done < size) {
        DWORD put = 0, want = (DWORD)std::min<size_t>(size - done, 1u << 24);
        ok = WriteFile(h, p + done, want, &put, nullptr) && put > 0;
        done += put;
    }
    CloseHandle(h);
    return ok;
}

static bool WriteAllBytes(const std::wstring& path, const Bytes& b) { return WriteAll(path, b.data(), b.size()); }

static bool WriteUtf8File(const std::wstring& path, const std::wstring& text) {
    std::string s = WideToUtf8(text);
    return WriteAll(path, s.data(), s.size());
}

static void MakeDirs(const std::wstring& dir) {
    if (!dir.empty() && !DirExists(dir)) SHCreateDirectoryExW(nullptr, dir.c_str(), nullptr);
}

static void RemoveDirTree(const std::wstring& dir) {
    WIN32_FIND_DATAW fd;
    HANDLE h = FindFirstFileW((dir + L"\\*").c_str(), &fd);
    if (h != INVALID_HANDLE_VALUE) {
        do {
            std::wstring n = fd.cFileName;
            if (n == L"." || n == L"..") continue;
            std::wstring full = dir + L"\\" + n;
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) RemoveDirTree(full);
            else {
                SetFileAttributesW(full.c_str(), FILE_ATTRIBUTE_NORMAL);
                DeleteFileW(full.c_str());
            }
        } while (FindNextFileW(h, &fd));
        FindClose(h);
    }
    RemoveDirectoryW(dir.c_str());
}

static std::wstring StoragePath() {
    static std::wstring p = Env(L"%LOCALAPPDATA%\\SeamlessSoundManager");
    MakeDirs(p);
    return p;
}

static std::wstring DataDir() {
    static std::wstring p = Env(L"%APPDATA%\\SoundManager");
    return p;
}

static std::wstring MediaDir() { return DataDir() + L"\\Media"; }
static std::wstring IniPath() { return DataDir() + L"\\SoundManager.ini"; }
static std::wstring MetaImagePath() { return MediaDir() + L"\\Scheme.png"; }
static std::wstring MetaInfoPath() { return MediaDir() + L"\\Scheme.ini"; }

static std::wstring EventPath(int ev) { return MediaDir() + L"\\" + kSmEvents[ev].file + L".wav"; }

static std::wstring EventLegacyName(int ev) {
    return kEvData[ev].legacy ? std::wstring(L"Windows XP ") + kEvData[ev].legacy + L".wav" : std::wstring();
}

static bool ValidEvent(int ev) { return ev >= 0 && ev < kSmEventCount; }

// Windows version, as upstream WindowsVersion.cs sees it.
struct WinVer {
    DWORD major = 10, minor = 0, build = 0;
};

static const WinVer& GetWinVer() {
    static WinVer v = [] {
        WinVer r;
        using Fn = LONG(WINAPI*)(OSVERSIONINFOW*);
        OSVERSIONINFOW vi{};
        vi.dwOSVersionInfoSize = sizeof(vi);
        if (HMODULE nt = GetModuleHandleW(L"ntdll.dll"))
            if (auto f = (Fn)(void*)GetProcAddress(nt, "RtlGetVersion"))
                if (f(&vi) == 0) {
                    r.major = vi.dwMajorVersion;
                    r.minor = vi.dwMinorVersion;
                    r.build = vi.dwBuildNumber;
                }
        return r;
    }();
    return v;
}

static bool IsWin11() { return GetWinVer().major == 10 && GetWinVer().build >= 22000; }
static bool IsWin10() { return GetWinVer().major == 10 && GetWinVer().build < 22000; }
static bool IsWin8() { return GetWinVer().major == 6 && GetWinVer().minor >= 2; }
static bool IsAtLeast10() { return GetWinVer().major >= 10; }

// A hidden console program, waited for. Returns false if it couldn't start or timed out.
static bool RunHidden(const std::wstring& cmdline, const std::wstring& cwd, DWORD timeoutMs, DWORD* exitCode = nullptr) {
    STARTUPINFOW si{};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    PROCESS_INFORMATION pi{};
    std::wstring cmd = cmdline;
    if (!CreateProcessW(nullptr, cmd.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr,
                        cwd.empty() ? nullptr : cwd.c_str(), &si, &pi))
        return false;
    bool ok = WaitForSingleObject(pi.hProcess, timeoutMs) == WAIT_OBJECT_0;
    if (!ok) TerminateProcess(pi.hProcess, 1);
    DWORD code = 1;
    GetExitCodeProcess(pi.hProcess, &code);
    if (exitCode) *exitCode = code;
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return ok;
}

static std::wstring SystemExe(PCWSTR name) { return Env(L"%SystemRoot%\\System32\\") + name; }

// ---------------------------------------------------------------------------
// Saving settings: one elevated windhawk-cli call, off the calling thread
// ---------------------------------------------------------------------------

static std::wstring CliPath() {
    WCHAR path[MAX_PATH];
    if (HMODULE engine = GetModuleHandleW(L"windhawk.dll"); engine && GetModuleFileNameW(engine, path, MAX_PATH)) {
        std::wstring dir = path;
        for (int i = 0; i < 4 && dir.find_last_of(L'\\') != std::wstring::npos; i++) dir.resize(dir.find_last_of(L'\\'));
        dir += L"\\windhawk-cli.exe";
        if (FileExists(dir)) return dir;
    }
    if (GetModuleFileNameW(nullptr, path, MAX_PATH)) {
        std::wstring dir = path;
        dir.resize(dir.find_last_of(L'\\'));
        dir += L"\\windhawk-cli.exe";
        if (FileExists(dir)) return dir;
    }
    std::wstring pf = Env(L"%ProgramFiles%\\Windhawk\\windhawk-cli.exe");
    return FileExists(pf) ? pf : std::wstring();
}

static std::wstring QuoteArg(const std::wstring& arg) {
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

static std::atomic<int> g_workers{0};

static DWORD WINAPI SaveThread(LPVOID param) {
    std::unique_ptr<std::wstring> params((std::wstring*)param);
    std::wstring cli = CliPath();
    if (cli.empty()) {
        Wh_Log(L"windhawk-cli.exe not found, setting not saved");
    } else {
        SHELLEXECUTEINFOW sei{};
        sei.cbSize = sizeof(sei);
        sei.fMask =SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI | SEE_MASK_NOASYNC;
        sei.lpVerb = L"runas";
        sei.lpFile = cli.c_str();
        sei.lpParameters = params->c_str();
        sei.nShow = SW_HIDE;
        if (ShellExecuteExW(&sei) && sei.hProcess) {
            if (WaitForSingleObject(sei.hProcess, 15000) == WAIT_TIMEOUT) {
                TerminateProcess(sei.hProcess, 1);
                Wh_Log(L"windhawk-cli timed out and was stopped");
            }
            CloseHandle(sei.hProcess);
        } else {
            Wh_Log(L"Couldn't start windhawk-cli (error %lu)", GetLastError());
        }
    }
    g_workers--;
    return 0;
}

static void SaveSettingAsync(PCWSTR key, const std::wstring& value) {
    auto* params = new std::wstring(L"--quiet mod settings set " + QuoteArg(WH_MOD_ID) + L" " +
                                    QuoteArg(std::wstring(key) + L"=" + value));
    g_workers++;
    HANDLE t = CreateThread(nullptr, 0, SaveThread, params, 0, nullptr);
    if (t) CloseHandle(t);
    else {
        g_workers--;
        delete params;
    }
}

// ---------------------------------------------------------------------------
// COM scope, hashes
// ---------------------------------------------------------------------------

struct ComScope {
    bool ok;
    ComScope() { ok = SUCCEEDED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED)); }
    ~ComScope() {
        if (ok) CoUninitialize();
    }
    ComScope(const ComScope&) = delete;
    ComScope& operator=(const ComScope&) = delete;
};

static bool NtOk(NTSTATUS s) { return s >= 0; }

static std::string HashHex(PCWSTR alg, const void* data, size_t size) {
    std::string hex;
    BCRYPT_ALG_HANDLE ha = nullptr;
    if (!NtOk(BCryptOpenAlgorithmProvider(&ha, alg, nullptr, 0))) return hex;
    DWORD objLen = 0, hashLen = 0, cb = 0;
    BCryptGetProperty(ha, BCRYPT_OBJECT_LENGTH, (PUCHAR)&objLen, sizeof(objLen), &cb, 0);
    BCryptGetProperty(ha, BCRYPT_HASH_LENGTH, (PUCHAR)&hashLen, sizeof(hashLen), &cb, 0);
    std::vector<uint8_t> obj(objLen), out(hashLen);
    BCRYPT_HASH_HANDLE hh = nullptr;
    if (objLen && hashLen && NtOk(BCryptCreateHash(ha, &hh, obj.data(), objLen, nullptr, 0, 0))) {
        if (NtOk(BCryptHashData(hh, (PUCHAR)data, (ULONG)size, 0)) && NtOk(BCryptFinishHash(hh, out.data(), hashLen, 0))) {
            static const char* d = "0123456789abcdef";
            for (uint8_t b : out) {
                hex += d[b >> 4];
                hex += d[b & 15];
            }
        }
        BCryptDestroyHash(hh);
    }
    BCryptCloseAlgorithmProvider(ha, 0);
    return hex;
}

// ---------------------------------------------------------------------------
// SoundManager.ini (upstream Settings.cs) and the per-event "disabled" flags
// ---------------------------------------------------------------------------

static bool g_disabledFlag[kSmEventCount];
static bool g_disabledDirty = false;
static std::wstring g_disabledRaw, g_listViewRaw;

static bool ParseIniFile(const std::wstring& path, std::map<std::wstring, std::wstring>& kv) {
    kv.clear();
    Bytes b;
    if (!ReadAll(path, b, 1 << 20)) return false;
    size_t off = (b.size() >= 3 && b[0] == 0xEF && b[1] == 0xBB && b[2] == 0xBF) ? 3 : 0;
    std::wstring text = Utf8ToWide((const char*)b.data() + off, b.size() - off);
    std::wstring section;
    size_t pos = 0;
    while (pos < text.size()) {
        size_t e = text.find(L'\n', pos);
        if (e == std::wstring::npos) e = text.size();
        std::wstring line = Trim(text.substr(pos, e - pos));
        pos = e + 1;
        if (line.empty() || line[0] == L'#' || line[0] == L';') continue;
        if (line[0] == L'[' && line.back() == L']') {
            section = Lower(Trim(line.substr(1, line.size() - 2)));
            continue;
        }
        size_t eq = line.find(L'=');
        if (eq == std::wstring::npos) continue;
        if (!section.empty() && section != L"main") continue;
        kv[Lower(Trim(line.substr(0, eq)))] = Trim(line.substr(eq + 1));
    }
    return true;
}

static bool Str2Bool(const std::wstring& s) {
    std::wstring l = Lower(Trim(s));
    return l == L"true" || l == L"1";
}

static void LoadIniState() {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    std::map<std::wstring, std::wstring> kv;
    for (bool& f : g_disabledFlag) f = false;
    g_disabledRaw.clear();
    g_listViewRaw.clear();
    g_disabledDirty = false;
    if (!ParseIniFile(IniPath(), kv)) return;
    g_disabledRaw = kv[L"disabledsoundevents"];
    g_listViewRaw = kv[L"schemeitemslistview"];
    size_t pos = 0;
    while (pos <= g_disabledRaw.size()) {
        size_t e = g_disabledRaw.find(L',', pos);
        if (e == std::wstring::npos) e = g_disabledRaw.size();
        std::wstring name = Trim(g_disabledRaw.substr(pos, e - pos));
        pos = e + 1;
        for (int i = 0; i < kSmEventCount; i++)
            if (EqCI(name, kSmEvents[i].file)) g_disabledFlag[i] = true;
    }
}

static void WriteIniState() {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    if (g_disabledDirty) {
        std::wstring joined;
        for (int i = 0; i < kSmEventCount; i++)
            if (g_disabledFlag[i]) joined += (joined.empty() ? L"" : L",") + std::wstring(kSmEvents[i].file);
        g_disabledRaw = joined;
        g_disabledDirty = false;
    }
    auto b = [](bool v) { return v ? L"True" : L"False"; };
    std::wstring t = L"#SoundManager Configuration File\r\n[Main]\r\n";
    t += std::wstring(L"PatchStartupSound=") + b(g_cPatch) + L"\r\n";
    t += std::wstring(L"UseDefaultOnMissingSound=") + b(g_cMissing) + L"\r\n";
    t += std::wstring(L"ConvertProprietaryFiles=") + b(g_cConvert) + L"\r\n";
    t += std::wstring(L"PreferStartupSoundOnLogon=") + b(g_cPreferStartup) + L"\r\n";
    t += L"DisabledSoundEvents=" + g_disabledRaw + L"\r\n";
    t += L"SchemeItemsListView=" + g_listViewRaw + L"\r\n";
    MakeDirs(DataDir());
    WriteUtf8File(IniPath(), t);
}

// ---------------------------------------------------------------------------
// Registry helpers for the Windows sound scheme
// ---------------------------------------------------------------------------

static const wchar_t kSchemesKey[] = L"AppEvents\\Schemes";
static const wchar_t kNamesKey[] = L"AppEvents\\Schemes\\Names";
static const wchar_t kAppsKey[] = L"AppEvents\\Schemes\\Apps";
static const wchar_t kDisabledMark[] = L"<DISABLED>";

static bool RegReadDefault(const std::wstring& sub, std::wstring& out) {
    DWORD cb = 0;
    const DWORD flags = RRF_RT_REG_SZ | RRF_RT_REG_EXPAND_SZ | RRF_NOEXPAND;
    if (RegGetValueW(HKEY_CURRENT_USER, sub.c_str(), nullptr, flags, nullptr, nullptr, &cb) != ERROR_SUCCESS) return false;
    std::wstring buf(cb / 2 + 2, L'\0');
    cb = (DWORD)(buf.size() * 2);
    if (RegGetValueW(HKEY_CURRENT_USER, sub.c_str(), nullptr, flags, nullptr, buf.data(), &cb) != ERROR_SUCCESS) return false;
    out.assign(buf.c_str());
    return true;
}

static bool RegWriteDefault(const std::wstring& sub, const std::wstring& value) {
    HKEY k = nullptr;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, sub.c_str(), 0, nullptr, 0, KEY_SET_VALUE, nullptr, &k, nullptr) != ERROR_SUCCESS) return false;
    bool ok = RegSetValueExW(k, nullptr, 0, REG_SZ, (const BYTE*)value.c_str(), (DWORD)((value.size() + 1) * 2)) == ERROR_SUCCESS;
    RegCloseKey(k);
    return ok;
}

static std::vector<std::wstring> RegSubKeys(const std::wstring& sub) {
    std::vector<std::wstring> out;
    HKEY k = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, sub.c_str(), 0, KEY_READ, &k) != ERROR_SUCCESS) return out;
    for (DWORD i = 0;; i++) {
        WCHAR name[256];
        DWORD len = ARRAYSIZE(name);
        LSTATUS r = RegEnumKeyExW(k, i, name, &len, nullptr, nullptr, nullptr, nullptr);
        if (r == ERROR_NO_MORE_ITEMS) break;
        if (r == ERROR_SUCCESS) out.emplace_back(name, len);
    }
    RegCloseKey(k);
    return out;
}

static std::wstring AppsPath(PCWSTR evKey, const std::wstring& leaf) {
    return std::wstring(kAppsKey) + L"\\" + evKey + L"\\" + leaf;
}

// ---------------------------------------------------------------------------
// Audio files: WAV header, duration, conversion (Media Foundation), ACL
// ---------------------------------------------------------------------------

struct WavInfo {
    bool valid = false;
    uint16_t tag = 0;
    uint32_t bytesPerSec = 0;
    uint64_t dataBytes = 0;
};

static bool ReadWavInfo(const std::wstring& path, WavInfo& w) {
    w = {};
    HANDLE h = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                           OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;
    LARGE_INTEGER sz{};
    uint8_t hdr[12];
    DWORD got = 0;
    bool ok = GetFileSizeEx(h, &sz) && ReadFile(h, hdr, 12, &got, nullptr) && got == 12 && !memcmp(hdr, "RIFF", 4) &&
              !memcmp(hdr + 8, "WAVE", 4);
    LONGLONG pos = 12;
    bool haveFmt = false, haveData = false;
    while (ok && pos + 8 <= sz.QuadPart && !(haveFmt && haveData)) {
        LARGE_INTEGER p;
        p.QuadPart = pos;
        uint8_t ch[8];
        if (!SetFilePointerEx(h, p, nullptr, FILE_BEGIN) || !ReadFile(h, ch, 8, &got, nullptr) || got != 8) break;
        uint32_t csz;
        memcpy(&csz, ch + 4, 4);
        if (!memcmp(ch, "fmt ", 4) && csz >= 16) {
            uint8_t f[16];
            if (!ReadFile(h, f, 16, &got, nullptr) || got != 16) break;
            w.tag = (uint16_t)(f[0] | (f[1] << 8));
            memcpy(&w.bytesPerSec, f + 8, 4);
            haveFmt = true;
        } else if (!memcmp(ch, "data", 4)) {
            LONGLONG remaining = sz.QuadPart - (pos + 8);
            w.dataBytes = (uint64_t)std::min<LONGLONG>((LONGLONG)csz, remaining);
            haveData = true;
        }
        pos += 8 + (LONGLONG)csz + (csz & 1);
    }
    CloseHandle(h);
    w.valid = ok && haveFmt && haveData;
    return w.valid;
}

static bool MfDuration(const std::wstring& path, double& seconds) {
    ComScope com;
    if (FAILED(MFStartup(MF_VERSION, MFSTARTUP_LITE))) return false;
    bool ok = false;
    {
        Com<IMFSourceReader> r;
        if (SUCCEEDED(MFCreateSourceReaderFromURL(path.c_str(), nullptr, r.put()))) {
            PROPVARIANT pv;
            PropVariantInit(&pv);
            if (SUCCEEDED(r->GetPresentationAttribute((DWORD)MF_SOURCE_READER_MEDIASOURCE, MF_PD_DURATION, &pv)) && pv.vt == VT_UI8) {
                seconds = (double)pv.uhVal.QuadPart / 1e7;
                ok = true;
            }
            PropVariantClear(&pv);
        }
    }
    MFShutdown();
    return ok;
}

static bool AudioSeconds(const std::wstring& path, double& seconds) {
    WavInfo w;
    if (ReadWavInfo(path, w) && w.bytesPerSec) {
        seconds = (double)w.dataBytes / (double)w.bytesPerSec;
        return true;
    }
    return MfDuration(path, seconds);
}

static void PutU32(Bytes& b, uint32_t v) {
    for (int i = 0; i < 4; i++) b.push_back((uint8_t)(v >> (8 * i)));
}
static void PutU16(Bytes& b, uint16_t v) {
    b.push_back((uint8_t)v);
    b.push_back((uint8_t)(v >> 8));
}
static void PutStr(Bytes& b, const char* s) {
    while (*s) b.push_back((uint8_t)*s++);
}

static bool MfConvertToWav(const std::wstring& src, const std::wstring& dst) {
    ComScope com;
    if (FAILED(MFStartup(MF_VERSION, MFSTARTUP_LITE))) return false;
    bool ok = false;
    {
        Com<IMFSourceReader> r;
        if (SUCCEEDED(MFCreateSourceReaderFromURL(src.c_str(), nullptr, r.put()))) {
            const DWORD kAudio = (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM;
            r->SetStreamSelection((DWORD)MF_SOURCE_READER_ALL_STREAMS, FALSE);
            r->SetStreamSelection(kAudio, TRUE);
            Com<IMFMediaType> want;
            if (SUCCEEDED(MFCreateMediaType(want.put())) && SUCCEEDED(want->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio)) &&
                SUCCEEDED(want->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM)) &&
                SUCCEEDED(r->SetCurrentMediaType(kAudio, nullptr, want.get()))) {
                Com<IMFMediaType> got;
                WAVEFORMATEX* wfx = nullptr;
                UINT32 wsz = 0;
                if (SUCCEEDED(r->GetCurrentMediaType(kAudio, got.put())) &&
                    SUCCEEDED(MFCreateWaveFormatExFromMFMediaType(got.get(), &wfx, &wsz, 0)) && wfx) {
                    Bytes pcm;
                    bool eos = false, fail = false;
                    while (!eos && !fail && pcm.size() < ((size_t)128 << 20)) {
                        DWORD flags = 0;
                        Com<IMFSample> s;
                        if (FAILED(r->ReadSample(kAudio, 0, nullptr, &flags, nullptr, s.put()))) {
                            fail = true;
                            break;
                        }
                        if (flags & MF_SOURCE_READERF_ENDOFSTREAM) eos = true;
                        if (s) {
                            Com<IMFMediaBuffer> mb;
                            if (SUCCEEDED(s->ConvertToContiguousBuffer(mb.put()))) {
                                BYTE* p = nullptr;
                                DWORD len = 0;
                                if (SUCCEEDED(mb->Lock(&p, nullptr, &len))) {
                                    pcm.insert(pcm.end(), p, p + len);
                                    mb->Unlock();
                                }
                            }
                        }
                    }
                    if (!fail && !pcm.empty()) {
                        Bytes w;
                        PutStr(w, "RIFF");
                        PutU32(w, (uint32_t)(36 + pcm.size()));
                        PutStr(w, "WAVEfmt ");
                        PutU32(w, 16);
                        PutU16(w, 1);
                        PutU16(w, wfx->nChannels);
                        PutU32(w, wfx->nSamplesPerSec);
                        PutU32(w, wfx->nAvgBytesPerSec);
                        PutU16(w, wfx->nBlockAlign);
                        PutU16(w, wfx->wBitsPerSample);
                        PutStr(w, "data");
                        PutU32(w, (uint32_t)pcm.size());
                        w.insert(w.end(), pcm.begin(), pcm.end());
                        ok = WriteAllBytes(dst, w);
                    }
                    CoTaskMemFree(wfx);
                }
            }
        }
    }
    MFShutdown();
    return ok;
}

// Let packaged apps (ALL APPLICATION PACKAGES) read a sound file.
static void GrantAppContainerRead(const std::wstring& path) {
    PSID sid = nullptr;
    if (!ConvertStringSidToSidW(L"S-1-15-2-1", &sid)) return;
    PACL oldAcl = nullptr;
    PSECURITY_DESCRIPTOR sd = nullptr;
    std::wstring p = path;
    if (GetNamedSecurityInfoW(p.data(), SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, &oldAcl, nullptr, &sd) == ERROR_SUCCESS) {
        EXPLICIT_ACCESSW ea{};
        ea.grfAccessPermissions = FILE_GENERIC_READ | FILE_GENERIC_EXECUTE;
        ea.grfAccessMode = GRANT_ACCESS;
        ea.grfInheritance = NO_INHERITANCE;
        BuildTrusteeWithSidW(&ea.Trustee, sid);
        PACL newAcl = nullptr;
        if (SetEntriesInAclW(1, &ea, oldAcl, &newAcl) == ERROR_SUCCESS) {
            SetNamedSecurityInfoW(p.data(), SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, newAcl, nullptr);
            LocalFree(newAcl);
        }
        LocalFree(sd);
    }
    LocalFree(sid);
}

// ---------------------------------------------------------------------------
// imageres.dll startup sound patch (upstream ImageresPatcher.cs), only when opted in and elevated
// ---------------------------------------------------------------------------

static const uint8_t kEmptyWav[70] = {0x52, 0x49, 0x46, 0x46, 0x3e, 0x00, 0x00, 0x00, 0x57, 0x41, 0x56, 0x45, 0x66, 0x6d,
                                      0x74, 0x20, 0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x44, 0xac, 0x00, 0x00,
                                      0x10, 0xb1, 0x02, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x66, 0x61, 0x63, 0x74,
                                      0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x61, 0x74, 0x61, 0x00, 0x00,
                                      0x00, 0x00, 0x4c, 0x49, 0x53, 0x54, 0x04, 0x00, 0x00, 0x00, 0x49, 0x4e, 0x46, 0x4f};

static bool CanPatch() {
    static const bool elevated = IsElevated();
    return g_cPatch.load() && elevated;
}

static std::wstring ImageresPath() {
    WCHAR win[MAX_PATH]{};
    GetWindowsDirectoryW(win, MAX_PATH);
    BOOL wow = FALSE;
    IsWow64Process(GetCurrentProcess(), &wow);
    return std::wstring(win) + (wow ? L"\\Sysnative\\imageres.dll" : L"\\System32\\imageres.dll");
}

static void GrantAdmins(const std::wstring& path, bool isDir) {
    RunHidden(QuoteArg(SystemExe(L"takeown.exe")) + L" /F " + QuoteArg(path) + L" /A", L"", 30000);
    RunHidden(QuoteArg(SystemExe(L"icacls.exe")) + L" " + QuoteArg(path) + L" /grant *S-1-5-32-544:" + (isDir ? L"(M)" : L"F"), L"", 30000);
}

static bool ImageresBackup() {
    std::wstring path = ImageresPath(), bak = path + L".bak";
    GrantAdmins(DirOf(path), true);
    GrantAdmins(path, false);
    if (FileExists(bak)) {
        GrantAdmins(bak, false);
        return true;
    }
    if (!MoveFileExW(path.c_str(), bak.c_str(), 0)) return false;
    return CopyFileW(bak.c_str(), path.c_str(), FALSE) != 0;
}

static bool ImageresRestore() {
    std::wstring path = ImageresPath(), bak = path + L".bak", old = path + L".old";
    if (!FileExists(bak)) return false;
    GrantAdmins(DirOf(path), true);
    GrantAdmins(path, false);
    GrantAdmins(bak, false);
    DeleteFileW(old.c_str());
    MoveFileExW(path.c_str(), old.c_str(), MOVEFILE_REPLACE_EXISTING);
    DeleteFileW(path.c_str());
    return MoveFileExW(bak.c_str(), path.c_str(), 0) != 0;
}

static bool ImageresPatch(const void* wav, size_t size) {
    std::wstring path = ImageresPath(), bak = path + L".bak", old = path + L".old";
    if (!ImageresBackup()) return false;
    DeleteFileW(old.c_str());
    if (!MoveFileExW(path.c_str(), old.c_str(), MOVEFILE_REPLACE_EXISTING)) return false;
    if (!CopyFileW(bak.c_str(), path.c_str(), FALSE)) return false;
    bool ok = false;
    if (HANDLE h = BeginUpdateResourceW(path.c_str(), FALSE)) {
        BOOL put = UpdateResourceW(h, L"WAVE", MAKEINTRESOURCEW(5080), 1033, (LPVOID)wav, (DWORD)size);
        ok = EndUpdateResourceW(h, !put) && put;
    }
    if (!ok) CopyFileW(bak.c_str(), path.c_str(), FALSE);
    return ok;
}

static bool ImageresExtract(const std::wstring& outFile) {
    std::wstring path = ImageresPath(), bak = path + L".bak";
    HMODULE m = LoadLibraryExW(FileExists(bak) ? bak.c_str() : path.c_str(), nullptr, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE);
    if (!m) return false;
    bool ok = false;
    if (HRSRC r = FindResourceExW(m, L"WAVE", MAKEINTRESOURCEW(5080), 1033))
        if (HGLOBAL g = LoadResource(m, r))
            if (void* p = LockResource(g)) ok = WriteAll(outFile, p, SizeofResource(m, r));
    FreeLibrary(m);
    return ok;
}

// ---------------------------------------------------------------------------
// Scheme files: Update, CopyDefault, Setup, Apply, Uninstall (upstream SoundScheme.cs)
// ---------------------------------------------------------------------------

static void PostUpdate(int ev) {
    std::wstring target = EventPath(ev);
    if (ev == kEvStartup && CanPatch()) {
        Bytes b;
        if (FileExists(target) && ReadAll(target, b, 64 << 20)) ImageresPatch(b.data(), b.size());
        else ImageresPatch(kEmptyWav, sizeof(kEmptyWav));
    }
    if (FileExists(target) && IsAtLeast10()) GrantAppContainerRead(target);
}

// file empty or missing: the event's sound is removed.
static bool UpdateEvent(int ev, const std::wstring& file, std::wstring& err) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    std::wstring target = EventPath(ev);
    MakeDirs(MediaDir());
    if (!EqCI(file, target)) {
        SetFileAttributesW(target.c_str(), FILE_ATTRIBUTE_NORMAL);
        if (!file.empty() && FileExists(file)) {
            double secs = 0;
            if (AudioSeconds(file, secs) && secs > 30.0) {
                err = L"The sound file duration is too long.";
                return false;
            }
            WavInfo wi;
            bool ok;
            if (ReadWavInfo(file, wi) && (wi.tag == 1 || wi.tag == 2 || wi.tag == 3)) ok = CopyFileW(file.c_str(), target.c_str(), FALSE) != 0;
            else ok = MfConvertToWav(file, target);
            if (!ok) {
                DeleteFileW(target.c_str());
                err = L"This file format is unsupported, try converting it to WAV first.";
                return false;
            }
            SetFileAttributesW(target.c_str(), FILE_ATTRIBUTE_NORMAL);
        } else {
            DeleteFileW(target.c_str());
        }
    }
    PostUpdate(ev);
    return true;
}

static bool CopyDefaultEvent(int ev, const std::wstring& source, std::wstring& err) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    MakeDirs(MediaDir());
    bool found = false;
    for (PCWSTR key : kEvData[ev].keys) {
        if (!key || found) break;
        std::wstring v;
        if (!RegReadDefault(AppsPath(key, source), v)) continue;
        std::wstring p = Env(v.c_str());
        if (p.empty() || !FileExists(p)) continue;
        std::wstring e;
        if (UpdateEvent(ev, p, e)) found = true;
        else if (err.empty()) err = e;
    }
    if (ev == kEvStartup && g_cPatch.load()) {
        if (IsElevated()) ImageresRestore();
        found = ImageresExtract(EventPath(ev)) || found;
    }
    if (!found) {
        std::wstring e;
        UpdateEvent(ev, L"", e);
    }
    return found;
}

static std::wstring GetCurrentFile(int ev) {
    for (PCWSTR key : kEvData[ev].keys) {
        if (!key) break;
        std::wstring v;
        if (!RegReadDefault(AppsPath(key, L".Current"), v)) continue;
        std::wstring p = Env(v.c_str());
        if (!p.empty() && FileExists(p)) return p;
    }
    return {};
}

static void SchemeSetup() {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    MakeDirs(MediaDir());
    RegWriteDefault(std::wstring(kNamesKey) + L"\\SoundManager", L"Sound Manager");
    for (int ev = 0; ev < kSmEventCount; ev++) {
        std::wstring value = g_disabledFlag[ev] ? std::wstring(kDisabledMark) : EventPath(ev);
        for (PCWSTR key : kEvData[ev].keys) {
            if (!key) break;
            RegWriteDefault(AppsPath(key, L"SoundManager"), value);
        }
    }
    if (CanPatch()) ImageresBackup();
}

static bool SchemeApply(const std::wstring& scheme, bool missingUseDefault, std::wstring& err) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    std::wstring tmp;
    if (!RegReadDefault(std::wstring(kNamesKey) + L"\\" + scheme, tmp)) {
        err = L"The sound scheme isn't installed.";
        return false;
    }
    for (const std::wstring& app : RegSubKeys(kAppsKey)) {
        for (const std::wstring& snd : RegSubKeys(std::wstring(kAppsKey) + L"\\" + app)) {
            std::wstring base = std::wstring(kAppsKey) + L"\\" + app + L"\\" + snd;
            std::wstring path;
            bool has = RegReadDefault(base + L"\\" + scheme, path);
            bool missing = !has || !FileExists(Env(path.c_str()));
            if (missing && missingUseDefault && !(has && path == kDisabledMark)) {
                std::wstring def;
                if (RegReadDefault(base + L"\\.Default", def)) {
                    path = def;
                    has = true;
                }
            }
            if (has && !FileExists(Env(path.c_str()))) has = false;
            RegWriteDefault(base + L"\\.Current", has ? path : std::wstring());
        }
    }
    RegWriteDefault(kSchemesKey, scheme);
    return true;
}

static bool SchemeInstalled() {
    std::wstring v;
    return RegReadDefault(std::wstring(kNamesKey) + L"\\SoundManager", v);
}

static bool SchemeIsActive() {
    std::wstring v;
    return RegReadDefault(kSchemesKey, v) && EqCI(v, L"SoundManager");
}

// Setup + Apply, the way every edit makes Windows use the change at once.
static bool Reapply(std::wstring& err) {
    SchemeSetup();
    return SchemeApply(L"SoundManager", g_cMissing.load(), err);
}

static bool SchemeUninstall(std::wstring& err) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    if (SchemeIsActive() && !SchemeApply(L".Default", true, err)) return false;
    for (const std::wstring& app : RegSubKeys(kAppsKey))
        for (const std::wstring& snd : RegSubKeys(std::wstring(kAppsKey) + L"\\" + app))
            RegDeleteTreeW(HKEY_CURRENT_USER, (std::wstring(kAppsKey) + L"\\" + app + L"\\" + snd + L"\\SoundManager").c_str());
    RegDeleteTreeW(HKEY_CURRENT_USER, (std::wstring(kNamesKey) + L"\\SoundManager").c_str());
    if (CanPatch()) ImageresRestore();
    return true;
}

// ---------------------------------------------------------------------------
// Scheme picture and info (upstream SchemeMeta.cs)
// ---------------------------------------------------------------------------

static std::atomic<UINT> g_thumbVersion{1};
static void BumpThumb() { g_thumbVersion++; }

static SmMeta ReadMeta() {
    SmMeta m;
    Bytes b;
    if (!ReadAll(MetaInfoPath(), b, 1 << 20)) return m;
    size_t off = (b.size() >= 3 && b[0] == 0xEF && b[1] == 0xBB && b[2] == 0xBF) ? 3 : 0;
    std::wstring text = Utf8ToWide((const char*)b.data() + off, b.size() - off);
    std::vector<std::wstring> lines;
    size_t pos = 0;
    while (pos < text.size()) {
        size_t e = text.find(L'\n', pos);
        if (e == std::wstring::npos) e = text.size();
        lines.push_back(text.substr(pos, e - pos));
        pos = e + 1;
    }
    if (lines.size() == 1 && lines[0].find(L';') != std::wstring::npos) {
        std::wstring one = lines[0];
        lines.clear();
        size_t p = 0;
        while (p <= one.size()) {
            size_t e = one.find(L';', p);
            if (e == std::wstring::npos) e = one.size();
            lines.push_back(one.substr(p, e - p));
            p = e + 1;
        }
    }
    for (const std::wstring& raw : lines) {
        std::wstring line = Trim(raw);
        size_t eq = line.find(L'=');
        if (eq == std::wstring::npos) continue;
        std::wstring field = Lower(line.substr(0, eq));
        size_t a = field.find_first_not_of(L" \"");
        size_t z = field.find_last_not_of(L" \"");
        field = a == std::wstring::npos ? std::wstring() : field.substr(a, z - a + 1);
        std::wstring value = Trim(line.substr(eq + 1));
        if (field == L"name" || field == L"nom") m.name = value;
        else if (field == L"author" || field == L"auteur") m.author = value;
        else if (field == L"about" || field == L"commentaire") m.about = value;
    }
    return m;
}

static std::wstring OneLine(std::wstring s) {
    for (auto& c : s)
        if (c == L'\r' || c == L'\n') c = L' ';
    return s;
}

static std::wstring SerializeMeta(const SmMeta& m) {
    return L"[SchemeInfo]\r\nname=" + OneLine(m.name) + L"\r\nauthor=" + OneLine(m.author) + L"\r\nabout=" + OneLine(m.about) + L"\r\n";
}

static void WriteMeta(const SmMeta& m) {
    MakeDirs(MediaDir());
    WriteUtf8File(MetaInfoPath(), SerializeMeta(m));
}

static void ResetMetaAll() {
    WriteMeta({L"Default Windows sounds", L"Microsoft Corporation", L"https://www.microsoft.com/"});
    DeleteFileW(MetaImagePath().c_str());
    BumpThumb();
}

static bool CreateWic(Com<IWICImagingFactory>& f) {
    return SUCCEEDED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(f.put())));
}

// Saves a BGRA source as PNG.
static bool SavePng(IWICImagingFactory* f, IWICBitmapSource* src, UINT w, UINT h, const std::wstring& path) {
    Com<IWICStream> stream;
    Com<IWICBitmapEncoder> enc;
    Com<IWICBitmapFrameEncode> frame;
    if (FAILED(f->CreateStream(stream.put())) || FAILED(stream->InitializeFromFilename(path.c_str(), GENERIC_WRITE))) return false;
    if (FAILED(f->CreateEncoder(GUID_ContainerFormatPng, nullptr, enc.put())) || FAILED(enc->Initialize(stream.get(), WICBitmapEncoderNoCache))) return false;
    if (FAILED(enc->CreateNewFrame(frame.put(), nullptr)) || FAILED(frame->Initialize(nullptr))) return false;
    WICPixelFormatGUID fmt = GUID_WICPixelFormat32bppBGRA;
    if (FAILED(frame->SetSize(w, h)) || FAILED(frame->SetPixelFormat(&fmt))) return false;
    if (FAILED(frame->WriteSource(src, nullptr)) || FAILED(frame->Commit()) || FAILED(enc->Commit())) return false;
    return true;
}

static bool ImageToThumb(const std::wstring& file, const std::wstring& outPng) {
    ComScope com;
    Com<IWICImagingFactory> f;
    if (!CreateWic(f)) return false;
    Com<IWICBitmapDecoder> dec;
    Com<IWICBitmapFrameDecode> frame;
    Com<IWICBitmapScaler> scaler;
    Com<IWICFormatConverter> conv;
    if (FAILED(f->CreateDecoderFromFilename(file.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, dec.put())) ||
        FAILED(dec->GetFrame(0, frame.put())))
        return false;
    if (FAILED(f->CreateBitmapScaler(scaler.put())) || FAILED(scaler->Initialize(frame.get(), 100, 100, WICBitmapInterpolationModeFant))) return false;
    if (FAILED(f->CreateFormatConverter(conv.put())) ||
        FAILED(conv->Initialize(scaler.get(), GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom)))
        return false;
    return SavePng(f.get(), conv.get(), 100, 100, outPng);
}

static std::wstring EventToPlayOnLoad() {
    auto name = [](int ev) { return EventPath(ev); };
    if (FileExists(name(kEvLoadScheme)) && !g_disabledFlag[kEvLoadScheme]) return name(kEvLoadScheme);
    if (!FileExists(name(kEvStartup))) return !g_disabledFlag[kEvLogon] ? name(kEvLogon) : name(kEvStartup);
    Bytes b;
    if (ReadAll(name(kEvStartup), b, 64 << 20) && HashHex(BCRYPT_MD5_ALGORITHM, b.data(), b.size()) == "155f2a0f886570157416ea85f4b4c613") return name(kEvLogon);
    return name(kEvStartup);
}

// ---------------------------------------------------------------------------
// Zip: reader with its own inflate, writer that stores
// ---------------------------------------------------------------------------

namespace zipx {

struct Bits {
    const uint8_t* in;
    size_t size, pos = 0;
    uint32_t buf = 0;
    int cnt = 0;
    bool err = false;
    int Get(int need) {
        long val = buf;
        while (cnt < need) {
            if (pos >= size) {
                err = true;
                return 0;
            }
            val |= (long)in[pos++] << cnt;
            cnt += 8;
        }
        buf = (uint32_t)(val >> need);
        cnt -= need;
        return (int)(val & ((1L << need) - 1));
    }
};

struct Huff {
    short count[16];
    short symbol[288];
};

static int Decode(Bits& s, const Huff& h) {
    int code = 0, first = 0, index = 0;
    for (int len = 1; len <= 15; len++) {
        code |= s.Get(1);
        if (s.err) return -1;
        int count = h.count[len];
        if (code - count < first) return h.symbol[index + (code - first)];
        index += count;
        first += count;
        first <<= 1;
        code <<= 1;
    }
    return -1;
}

static int Construct(Huff& h, const short* length, int n) {
    short offs[16];
    for (int len = 0; len <= 15; len++) h.count[len] = 0;
    for (int sym = 0; sym < n; sym++) h.count[length[sym]]++;
    if (h.count[0] == n) return 0;
    int left = 1;
    for (int len = 1; len <= 15; len++) {
        left <<= 1;
        left -= h.count[len];
        if (left < 0) return left;
    }
    offs[1] = 0;
    for (int len = 1; len < 15; len++) offs[len + 1] = (short)(offs[len] + h.count[len]);
    for (int sym = 0; sym < n; sym++)
        if (length[sym] != 0) h.symbol[offs[length[sym]]++] = (short)sym;
    return left;
}

static bool Codes(Bits& s, Bytes& out, const Huff& lencode, const Huff& distcode, size_t limit) {
    static const short lens[29] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258};
    static const short lext[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
    static const short dists[30] = {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577};
    static const short dext[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
    for (;;) {
        int symbol = Decode(s, lencode);
        if (symbol < 0 || s.err) return false;
        if (symbol < 256) {
            out.push_back((uint8_t)symbol);
        } else if (symbol == 256) {
            return true;
        } else {
            symbol -= 257;
            if (symbol >= 29) return false;
            int len = lens[symbol] + s.Get(lext[symbol]);
            int ds = Decode(s, distcode);
            if (ds < 0 || ds >= 30 || s.err) return false;
            size_t dist = (size_t)dists[ds] + (size_t)s.Get(dext[ds]);
            if (s.err || dist > out.size()) return false;
            size_t from = out.size() - dist;
            for (int i = 0; i < len; i++) out.push_back(out[from + i]);
        }
        if (out.size() > limit) return false;
    }
}

static bool Inflate(const uint8_t* data, size_t size, Bytes& out, size_t limit) {
    Bits s{data, size};
    int last;
    static Huff fixedLen, fixedDist;
    static bool fixedBuilt = false;
    do {
        last = s.Get(1);
        int type = s.Get(2);
        if (s.err) return false;
        if (type == 0) {
            s.buf = 0;
            s.cnt = 0;
            if (s.pos + 4 > s.size) return false;
            unsigned len = data[s.pos] | (data[s.pos + 1] << 8);
            unsigned nlen = data[s.pos + 2] | (data[s.pos + 3] << 8);
            s.pos += 4;
            if (len != (~nlen & 0xFFFF) || s.pos + len > s.size) return false;
            out.insert(out.end(), data + s.pos, data + s.pos + len);
            s.pos += len;
        } else if (type == 1) {
            if (!fixedBuilt) {
                short lengths[288];
                int sym = 0;
                for (; sym < 144; sym++) lengths[sym] = 8;
                for (; sym < 256; sym++) lengths[sym] = 9;
                for (; sym < 280; sym++) lengths[sym] = 7;
                for (; sym < 288; sym++) lengths[sym] = 8;
                Construct(fixedLen, lengths, 288);
                for (sym = 0; sym < 30; sym++) lengths[sym] = 5;
                Construct(fixedDist, lengths, 30);
                fixedBuilt = true;
            }
            if (!Codes(s, out, fixedLen, fixedDist, limit)) return false;
        } else if (type == 2) {
            static const short order[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
            short lengths[320];
            int nlen = s.Get(5) + 257, ndist = s.Get(5) + 1, ncode = s.Get(4) + 4;
            if (s.err || nlen > 286 || ndist > 30) return false;
            int index = 0;
            for (; index < ncode; index++) lengths[order[index]] = (short)s.Get(3);
            for (; index < 19; index++) lengths[order[index]] = 0;
            Huff lencode, distcode;
            if (Construct(lencode, lengths, 19) != 0) return false;
            index = 0;
            while (index < nlen + ndist) {
                int symbol = Decode(s, lencode);
                if (symbol < 0 || s.err) return false;
                if (symbol < 16) {
                    lengths[index++] = (short)symbol;
                } else {
                    int len = 0, rep;
                    if (symbol == 16) {
                        if (index == 0) return false;
                        len = lengths[index - 1];
                        rep = 3 + s.Get(2);
                    } else if (symbol == 17) {
                        rep = 3 + s.Get(3);
                    } else {
                        rep = 11 + s.Get(7);
                    }
                    if (s.err || index + rep > nlen + ndist) return false;
                    while (rep--) lengths[index++] = (short)len;
                }
            }
            if (lengths[256] == 0) return false;
            int err = Construct(lencode, lengths, nlen);
            if (err && (err < 0 || nlen - lencode.count[0] != 1)) return false;
            err = Construct(distcode, lengths + nlen, ndist);
            if (err && (err < 0 || ndist - distcode.count[0] != 1)) return false;
            if (!Codes(s, out, lencode, distcode, limit)) return false;
        } else {
            return false;
        }
        if (out.size() > limit) return false;
    } while (!last);
    return true;
}

static uint32_t Crc32(const uint8_t* p, size_t n, uint32_t crc = 0) {
    static uint32_t table[256];
    static bool built = false;
    if (!built) {
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t c = i;
            for (int k = 0; k < 8; k++) c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
            table[i] = c;
        }
        built = true;
    }
    crc = ~crc;
    for (size_t i = 0; i < n; i++) crc = table[(crc ^ p[i]) & 0xFF] ^ (crc >> 8);
    return ~crc;
}

struct Entry {
    std::wstring name;
    uint16_t method = 0;
    uint32_t csize = 0, usize = 0, localOff = 0;
};

struct Reader {
    Bytes data;
    std::vector<Entry> entries;

    static uint16_t U16(const uint8_t* p) { return (uint16_t)(p[0] | (p[1] << 8)); }
    static uint32_t U32(const uint8_t* p) { return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24); }

    bool Open(const Bytes& d) {
        data = d;
        entries.clear();
        if (data.size() < 22) return false;
        size_t from = data.size() - 22, lo = data.size() > 65557 ? data.size() - 65557 : 0;
        size_t eocd = std::wstring::npos;
        for (size_t i = from + 1; i-- > lo;)
            if (U32(&data[i]) == 0x06054b50) {
                eocd = i;
                break;
            }
        if (eocd == std::wstring::npos) return false;
        unsigned count = U16(&data[eocd + 10]);
        size_t cdOff = U32(&data[eocd + 16]);
        size_t p = cdOff;
        for (unsigned i = 0; i < count; i++) {
            if (p + 46 > data.size() || U32(&data[p]) != 0x02014b50) return false;
            uint16_t flags = U16(&data[p + 8]), method = U16(&data[p + 10]);
            uint32_t csize = U32(&data[p + 20]), usize = U32(&data[p + 24]);
            unsigned nlen = U16(&data[p + 28]), elen = U16(&data[p + 30]), clen = U16(&data[p + 32]);
            uint32_t loff = U32(&data[p + 42]);
            if (p + 46 + nlen > data.size()) return false;
            Entry e;
            e.name = (flags & 0x0800) ? Utf8ToWide((const char*)&data[p + 46], nlen) : Utf8ToWide((const char*)&data[p + 46], nlen, 437);
            e.method = method;
            e.csize = csize;
            e.usize = usize;
            e.localOff = loff;
            entries.push_back(e);
            p += 46 + nlen + elen + clen;
        }
        return true;
    }

    int Find(const std::wstring& name) const {
        for (size_t i = 0; i < entries.size(); i++) {
            std::wstring n = ReplaceAll(entries[i].name, L"\\", L"/");
            if (n.find(L'/') == std::wstring::npos && EqCI(n, name)) return (int)i;
        }
        return -1;
    }

    bool Extract(int idx, Bytes& out) const {
        out.clear();
        if (idx < 0 || (size_t)idx >= entries.size()) return false;
        const Entry& e = entries[idx];
        size_t p = e.localOff;
        if (p + 30 > data.size() || U32(&data[p]) != 0x04034b50) return false;
        size_t start = p + 30 + U16(&data[p + 26]) + U16(&data[p + 28]);
        if (start + e.csize > data.size()) return false;
        if (e.method == 0) {
            out.assign(data.begin() + start, data.begin() + start + e.csize);
            return true;
        }
        if (e.method != 8) return false;
        out.reserve(e.usize);
        if (!Inflate(&data[start], e.csize, out, (size_t)256 << 20)) {
            out.clear();
            return false;
        }
        return true;
    }
};

struct Writer {
    Bytes out;
    struct Rec {
        std::string name;
        uint32_t crc, size, off;
    };
    std::vector<Rec> recs;

    void Add(const std::wstring& name, const Bytes& body) {
        Rec r;
        r.name = WideToUtf8(name);
        r.crc = Crc32(body.data(), body.size());
        r.size = (uint32_t)body.size();
        r.off = (uint32_t)out.size();
        PutU32(out, 0x04034b50);
        PutU16(out, 20);
        PutU16(out, 0x0800);
        PutU16(out, 0);
        PutU16(out, DosTime());
        PutU16(out, DosDate());
        PutU32(out, r.crc);
        PutU32(out, r.size);
        PutU32(out, r.size);
        PutU16(out, (uint16_t)r.name.size());
        PutU16(out, 0);
        PutStr(out, r.name.c_str());
        out.insert(out.end(), body.begin(), body.end());
        recs.push_back(r);
    }

    Bytes Finish() {
        uint32_t cdStart = (uint32_t)out.size();
        for (const Rec& r : recs) {
            PutU32(out, 0x02014b50);
            PutU16(out, 20);
            PutU16(out, 20);
            PutU16(out, 0x0800);
            PutU16(out, 0);
            PutU16(out, DosTime());
            PutU16(out, DosDate());
            PutU32(out, r.crc);
            PutU32(out, r.size);
            PutU32(out, r.size);
            PutU16(out, (uint16_t)r.name.size());
            PutU16(out, 0);
            PutU16(out, 0);
            PutU16(out, 0);
            PutU16(out, 0);
            PutU32(out, 0);
            PutU32(out, r.off);
            PutStr(out, r.name.c_str());
        }
        uint32_t cdSize = (uint32_t)out.size() - cdStart;
        PutU32(out, 0x06054b50);
        PutU16(out, 0);
        PutU16(out, 0);
        PutU16(out, (uint16_t)recs.size());
        PutU16(out, (uint16_t)recs.size());
        PutU32(out, cdSize);
        PutU32(out, cdStart);
        PutU16(out, 0);
        return out;
    }

    static uint16_t DosTime() {
        SYSTEMTIME t;
        GetLocalTime(&t);
        return (uint16_t)((t.wHour << 11) | (t.wMinute << 5) | (t.wSecond / 2));
    }
    static uint16_t DosDate() {
        SYSTEMTIME t;
        GetLocalTime(&t);
        return (uint16_t)(((t.wYear < 1980 ? 0 : t.wYear - 1980) << 9) | (t.wMonth << 5) | t.wDay);
    }
};

}  // namespace zipx

// ---------------------------------------------------------------------------
// The icon: a rounded square in the blue to mauve gradient with a glyph (GDI)
// ---------------------------------------------------------------------------

// Premultiplied BGRA pixels, size x size.
static bool RenderIconPixels(int size, std::vector<uint32_t>& out) {
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = size;
    bi.bmiHeader.biHeight = -size;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    void* glyphBits = nullptr;
    HDC screen = GetDC(nullptr);
    HBITMAP glyph = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &glyphBits, nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!glyph) return false;
    HDC dc = CreateCompatibleDC(nullptr);
    HGDIOBJ old = SelectObject(dc, glyph);
    memset(glyphBits, 0, (size_t)size * size * 4);
    HFONT font = CreateFontW(-(int)(size * 0.62f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, 0,
                             L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    WCHAR face[64]{};
    GetTextFaceW(dc, 64, face);
    if (_wcsicmp(face, L"Segoe Fluent Icons") != 0) {
        SelectObject(dc, oldFont);
        DeleteObject(font);
        font = CreateFontW(-(int)(size * 0.62f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, 0,
                           L"Segoe MDL2 Assets");
        oldFont = SelectObject(dc, font);
    }
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR gl[2] = {(WCHAR)0xE767, 0};
    DrawTextW(dc, gl, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    const float c0[3] = {0x89 / 255.f, 0xB4 / 255.f, 0xFA / 255.f};
    const float c1[3] = {0xCB / 255.f, 0xA6 / 255.f, 0xF7 / 255.f};
    const float ink[3] = {0x11 / 255.f, 0x11 / 255.f, 0x1B / 255.f};
    float radius = size * 0.26f, half = size / 2.0f;
    out.assign((size_t)size * size, 0);
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float qx = std::fabs(x + 0.5f - half) - (half - radius), qy = std::fabs(y + 0.5f - half) - (half - radius);
            float ox = std::max(qx, 0.0f), oy = std::max(qy, 0.0f);
            float d = std::sqrt(ox * ox + oy * oy) + std::min(std::max(qx, qy), 0.0f) - radius;
            float a = std::clamp(0.5f - d, 0.0f, 1.0f);
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) {
                float base = c0[i] + (c1[i] - c0[i]) * t;
                rgb[i] = (base + (ink[i] - base) * cov) * a;
            }
            out[(size_t)y * size + x] = ((uint32_t)(a * 255 + 0.5f) << 24) | ((uint32_t)(rgb[0] * 255 + 0.5f) << 16) |
                                        ((uint32_t)(rgb[1] * 255 + 0.5f) << 8) | (uint32_t)(rgb[2] * 255 + 0.5f);
        }
    DeleteObject(glyph);
    return true;
}

static HICON MakeTrayIcon() {
    int size = GetSystemMetricsForDpi(SM_CXSMICON, GetDpiForSystem());
    if (size < 16) size = 16;
    std::vector<uint32_t> px;
    if (!RenderIconPixels(size, px)) return nullptr;
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = size;
    bi.bmiHeader.biHeight = -size;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    void* bits = nullptr;
    HDC screen = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!color) return nullptr;
    memcpy(bits, px.data(), px.size() * 4);
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    return icon;
}

static bool WriteLogoPng(const std::wstring& path) {
    const int size = 128;
    std::vector<uint32_t> px;
    if (!RenderIconPixels(size, px)) return false;
    ComScope com;
    Com<IWICImagingFactory> f;
    Com<IWICBitmap> bmp;
    Com<IWICFormatConverter> conv;
    if (!CreateWic(f)) return false;
    if (FAILED(f->CreateBitmapFromMemory(size, size, GUID_WICPixelFormat32bppPBGRA, size * 4, (UINT)(px.size() * 4), (BYTE*)px.data(), bmp.put()))) return false;
    if (FAILED(f->CreateFormatConverter(conv.put())) ||
        FAILED(conv->Initialize(bmp.get(), GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom)))
        return false;
    return SavePng(f.get(), conv.get(), size, size, path);
}

// ---------------------------------------------------------------------------
// Proprietary .soundpack: AES-128-CBC zip, 3DES-CBC XML
// ---------------------------------------------------------------------------

static bool CbcDecrypt(PCWSTR alg, const uint8_t* key, ULONG keyLen, const uint8_t* iv, ULONG ivLen, const Bytes& in, Bytes& out) {
    out.clear();
    BCRYPT_ALG_HANDLE ha = nullptr;
    BCRYPT_KEY_HANDLE hk = nullptr;
    bool ok = false;
    if (NtOk(BCryptOpenAlgorithmProvider(&ha, alg, nullptr, 0))) {
        static const wchar_t kCbc[] = L"ChainingModeCBC";
        if (NtOk(BCryptSetProperty(ha, L"ChainingMode", (PUCHAR)kCbc, sizeof(kCbc), 0)) &&
            NtOk(BCryptGenerateSymmetricKey(ha, &hk, nullptr, 0, (PUCHAR)key, keyLen, 0)) && !in.empty() && in.size() % ivLen == 0) {
            std::vector<uint8_t> ivc(iv, iv + ivLen);
            out.resize(in.size());
            ULONG got = 0;
            if (NtOk(BCryptDecrypt(hk, (PUCHAR)in.data(), (ULONG)in.size(), nullptr, ivc.data(), ivLen, out.data(), (ULONG)out.size(), &got, 0))) {
                out.resize(got);
                ok = true;
            } else {
                out.clear();
            }
        }
        if (hk) BCryptDestroyKey(hk);
        BCryptCloseAlgorithmProvider(ha, 0);
    }
    return ok;
}

// ---------------------------------------------------------------------------
// A forgiving little XML reader, enough for the soundpack metadata
// ---------------------------------------------------------------------------

struct XNode {
    std::wstring tag, text;
    std::map<std::wstring, std::wstring> attrs;
    std::vector<std::unique_ptr<XNode>> kids;
    const XNode* Child(const std::wstring& t) const {
        for (auto& k : kids)
            if (k->tag == t) return k.get();
        return nullptr;
    }
    std::wstring Inner() const {
        std::wstring s = text;
        for (auto& k : kids) s += k->Inner();
        return s;
    }
};

struct XmlParser {
    const std::wstring& s;
    size_t p = 0;
    bool bad = false;
    explicit XmlParser(const std::wstring& t) : s(t) {}

    bool Starts(const wchar_t* lit) const { return s.compare(p, wcslen(lit), lit) == 0; }
    void Skip() {
        while (p < s.size() && iswspace(s[p])) p++;
    }
    std::wstring Decode(const std::wstring& raw) {
        std::wstring out;
        for (size_t i = 0; i < raw.size(); i++) {
            if (raw[i] != L'&') {
                out += raw[i];
                continue;
            }
            size_t e = raw.find(L';', i);
            if (e == std::wstring::npos || e - i > 10) {
                bad = true;
                return out;
            }
            std::wstring n = raw.substr(i + 1, e - i - 1);
            if (n == L"amp") out += L'&';
            else if (n == L"lt") out += L'<';
            else if (n == L"gt") out += L'>';
            else if (n == L"quot") out += L'"';
            else if (n == L"apos") out += L'\'';
            else if (n.size() > 1 && n[0] == L'#') {
                long v = n[1] == L'x' ? wcstol(n.c_str() + 2, nullptr, 16) : wcstol(n.c_str() + 1, nullptr, 10);
                if (v > 0 && v < 0x10000) out += (wchar_t)v;
                else bad = true;
            } else {
                bad = true;
                return out;
            }
            i = e;
        }
        return out;
    }
    bool SkipMisc() {
        for (;;) {
            Skip();
            if (Starts(L"<?")) {
                size_t e = s.find(L"?>", p);
                if (e == std::wstring::npos) return false;
                p = e + 2;
            } else if (Starts(L"<!--")) {
                size_t e = s.find(L"-->", p);
                if (e == std::wstring::npos) return false;
                p = e + 3;
            } else if (Starts(L"<!DOCTYPE")) {
                size_t e = s.find(L'>', p);
                if (e == std::wstring::npos) return false;
                p = e + 1;
            } else {
                return true;
            }
        }
    }
    std::unique_ptr<XNode> Element(int depth) {
        if (depth > 64 || p >= s.size() || s[p] != L'<') return nullptr;
        p++;
        auto n = std::make_unique<XNode>();
        size_t a = p;
        while (p < s.size() && !iswspace(s[p]) && s[p] != L'>' && s[p] != L'/') p++;
        n->tag = s.substr(a, p - a);
        if (n->tag.empty()) return nullptr;
        for (;;) {
            Skip();
            if (p >= s.size()) return nullptr;
            if (s[p] == L'/') {
                if (p + 1 < s.size() && s[p + 1] == L'>') {
                    p += 2;
                    return n;
                }
                return nullptr;
            }
            if (s[p] == L'>') {
                p++;
                break;
            }
            size_t b = p;
            while (p < s.size() && s[p] != L'=' && !iswspace(s[p]) && s[p] != L'>') p++;
            std::wstring an = s.substr(b, p - b);
            Skip();
            if (p >= s.size() || s[p] != L'=' || an.empty()) return nullptr;
            p++;
            Skip();
            if (p >= s.size() || (s[p] != L'"' && s[p] != L'\'')) return nullptr;
            wchar_t q = s[p++];
            size_t e = s.find(q, p);
            if (e == std::wstring::npos) return nullptr;
            n->attrs[an] = Decode(s.substr(p, e - p));
            if (bad) return nullptr;
            p = e + 1;
        }
        for (;;) {
            if (p >= s.size()) return nullptr;
            if (Starts(L"</")) {
                size_t e = s.find(L'>', p);
                if (e == std::wstring::npos) return nullptr;
                std::wstring close = Trim(s.substr(p + 2, e - p - 2));
                p = e + 1;
                return close == n->tag ? std::move(n) : nullptr;
            }
            if (Starts(L"<!--")) {
                size_t e = s.find(L"-->", p);
                if (e == std::wstring::npos) return nullptr;
                p = e + 3;
            } else if (Starts(L"<![CDATA[")) {
                size_t e = s.find(L"]]>", p);
                if (e == std::wstring::npos) return nullptr;
                n->text += s.substr(p + 9, e - p - 9);
                p = e + 3;
            } else if (s[p] == L'<') {
                auto k = Element(depth + 1);
                if (!k) return nullptr;
                n->kids.push_back(std::move(k));
            } else {
                size_t e = s.find(L'<', p);
                if (e == std::wstring::npos) return nullptr;
                n->text += Decode(s.substr(p, e - p));
                if (bad) return nullptr;
                p = e;
            }
        }
    }
    std::unique_ptr<XNode> Parse() {
        if (!SkipMisc()) return nullptr;
        return Element(0);
    }
};

static std::unique_ptr<XNode> ParseXml(const std::wstring& text) {
    XmlParser a(text);
    if (auto r = a.Parse()) return r;
    std::wstring fixed = ReplaceAll(text, L"&", L"&amp;");
    XmlParser b(fixed);
    return b.Parse();
}

static bool XmlPathByAttr(const XNode* node, const std::wstring& regPath, std::wstring& value) {
    size_t pos = 0;
    while (pos <= regPath.size()) {
        size_t e = regPath.find(L'\\', pos);
        if (e == std::wstring::npos) e = regPath.size();
        std::wstring part = regPath.substr(pos, e - pos);
        pos = e + 1;
        const XNode* next = nullptr;
        for (auto& k : node->kids) {
            auto it = k->attrs.find(L"name");
            if (it != k->attrs.end() && it->second == part) {
                next = k.get();
                break;
            }
        }
        if (!next) return false;
        node = next;
    }
    value = node->Inner();
    return true;
}

static std::wstring XmlChildText(const XNode* root, std::initializer_list<PCWSTR> tags, bool& found) {
    found = false;
    for (PCWSTR t : tags)
        if (const XNode* c = root->Child(t)) {
            found = true;
            return c->Inner();
        }
    return {};
}

// Turns a proprietary .soundpack into a plain .ths zip (SoundArchiveProprietary.cs).
static bool ProprietaryToThs(const std::wstring& file, Bytes& zipOut, std::wstring& err) {
    static const uint8_t zipKey[16] = {0x43, 0x6f, 0x70, 0x79, 0x72, 0x69, 0x67, 0x68, 0x74, 0x3f, 0x53, 0x74, 0x61, 0x72, 0x64, 0x6f};
    static const uint8_t zipIv[16] = {0x7d, 0x2a, 0x7e, 0x61, 0x70, 0x3f, 0x3f, 0x3f, 0x53, 0x74, 0x61, 0x72, 0x64, 0x6f, 0x63, 0x6b};
    static const uint8_t xmlKey[24] = {0x3f, 0x43, 0x6f, 0x70, 0x79, 0x72, 0x69, 0x67, 0x68, 0x74, 0x53, 0x74, 0x61, 0x72, 0x64, 0x6f, 0x63, 0x6b, 0x32, 0x30, 0x30, 0x38, 0x3f, 0x3f};
    static const uint8_t xmlIv[8] = {0x7d, 0x6c, 0x60, 0x3f, 0x2a, 0x7e, 0x61, 0x70};
    Bytes raw;
    if (!ReadAll(file, raw, (size_t)256 << 20)) {
        err = L"Couldn't read the file.";
        return false;
    }
    zipx::Reader in;
    if (!in.Open(raw)) {
        Bytes dec;
        if (!CbcDecrypt(BCRYPT_AES_ALGORITHM, zipKey, 16, zipIv, 16, raw, dec) || dec.empty() || dec.back() == 0 || dec.back() > 16 ||
            dec.back() > dec.size()) {
            err = L"This isn't a valid sound pack.";
            return false;
        }
        dec.resize(dec.size() - dec.back());
        if (!in.Open(dec)) {
            err = L"This isn't a valid sound pack.";
            return false;
        }
    }
    int mi = -1;
    for (size_t i = 0; i < in.entries.size(); i++)
        if (EqCI(in.entries[i].name, L"soundpackage.data")) mi = (int)i;
    Bytes enc;
    if (mi < 0 || !in.Extract(mi, enc)) {
        err = L"The sound pack has no soundpackage.data.";
        return false;
    }
    std::string b64(enc.begin(), enc.end());
    for (char& c : b64)
        if (c == ' ') c = '+';
    DWORD blen = 0;
    if (!CryptStringToBinaryA(b64.c_str(), (DWORD)b64.size(), CRYPT_STRING_BASE64_ANY, nullptr, &blen, nullptr, nullptr) || !blen) {
        err = L"The sound pack data is damaged.";
        return false;
    }
    Bytes cipher(blen), plain;
    CryptStringToBinaryA(b64.c_str(), (DWORD)b64.size(), CRYPT_STRING_BASE64_ANY, cipher.data(), &blen, nullptr, nullptr);
    cipher.resize(blen);
    if (!CbcDecrypt(BCRYPT_3DES_ALGORITHM, xmlKey, 24, xmlIv, 8, cipher, plain) || plain.empty() || plain.back() == 0 || plain.back() > 8 ||
        plain.back() > plain.size()) {
        err = L"The sound pack data is damaged.";
        return false;
    }
    plain.resize(plain.size() - plain.back());
    size_t off = (plain.size() >= 3 && plain[0] == 0xEF && plain[1] == 0xBB && plain[2] == 0xBF) ? 3 : 0;
    std::wstring xmlText = Utf8ToWide((const char*)plain.data() + off, plain.size() - off);
    auto root = ParseXml(xmlText);
    if (!root) {
        err = L"The sound pack data is damaged.";
        return false;
    }
    bool f1;
    SmMeta meta;
    meta.name = XmlChildText(root.get(), {L"name"}, f1);
    meta.author = XmlChildText(root.get(), {L"author"}, f1);
    meta.about = XmlChildText(root.get(), {L"notes", L"website", L"email", L"copyright"}, f1);
    std::wstring thumb = XmlChildText(root.get(), {L"preview", L"icon"}, f1);

    std::vector<std::pair<std::wstring, std::wstring>> toCopy;  // dest <- source
    std::set<std::wstring> copied;
    auto put = [&](const std::wstring& dest, const std::wstring& srcName) {
        for (auto& pr : toCopy)
            if (pr.first == dest) {
                pr.second = srcName;
                return;
            }
        toCopy.emplace_back(dest, srcName);
    };
    if (!thumb.empty()) {
        put(L"Scheme.png", thumb);
        copied.insert(thumb);
    }
    if (const XNode* groups = root->Child(L"groups")) {
        for (int ev = 0; ev < kSmEventCount; ev++)
            for (PCWSTR key : kEvData[ev].keys) {
                if (!key) break;
                std::wstring fn;
                if (XmlPathByAttr(groups, key, fn) && !fn.empty()) {
                    put(std::wstring(kSmEvents[ev].file) + L".wav", fn);
                    copied.insert(fn);
                    break;
                }
            }
    }
    for (auto& e : in.entries)
        if (!copied.count(e.name)) put(L"_unused_" + e.name, e.name);

    zipx::Writer w;
    for (auto& pr : toCopy) {
        int idx = -1;
        for (size_t i = 0; i < in.entries.size(); i++)
            if (EqCI(in.entries[i].name, pr.second)) {
                idx = (int)i;
                break;
            }
        Bytes body;
        if (idx >= 0 && in.Extract(idx, body)) w.Add(pr.first, body);
    }
    std::string info = WideToUtf8(SerializeMeta(meta));
    w.Add(L"Scheme.ini", Bytes(info.begin(), info.end()));
    std::string xmlUtf8 = WideToUtf8(xmlText);
    w.Add(L"_unused_soundpackage.data.xml", Bytes(xmlUtf8.begin(), xmlUtf8.end()));
    zipOut = w.Finish();
    return true;
}

// ---------------------------------------------------------------------------
// Import, export, themepack
// ---------------------------------------------------------------------------

static std::atomic<bool> g_previewPlaying{false};

static void PlayFileAsync(const std::wstring& path) {
    PlaySoundW(path.c_str(), nullptr, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
    g_previewPlaying = true;
}

static void RecycleFile(const std::wstring& path) {
    std::wstring from = path;
    from.push_back(L'\0');
    SHFILEOPSTRUCTW op{};
    op.wFunc = FO_DELETE;
    op.pFrom = from.c_str();
    op.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI;
    SHFileOperationW(&op);
}

static bool ImportArchive(const std::wstring& file, std::wstring& err) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    if (!FileExists(file)) {
        err = L"The file doesn't exist.";
        return false;
    }
    Bytes zipBytes;
    if (ExtOf(file) == L".soundpack") {
        if (!ProprietaryToThs(file, zipBytes, err)) return false;
        if (g_cConvert.load()) {
            std::wstring outFile = file.substr(0, file.find_last_of(L'.')) + L".ths";
            if (WriteAllBytes(outFile, zipBytes)) RecycleFile(file);
        }
    } else if (!ReadAll(file, zipBytes, (size_t)512 << 20)) {
        err = L"Couldn't read the file.";
        return false;
    }
    zipx::Reader zr;
    if (!zr.Open(zipBytes)) {
        err = L"This isn't a valid sound scheme file.";
        return false;
    }
    MakeDirs(MediaDir());
    for (int ev = 0; ev < kSmEventCount; ev++) {
        std::wstring target = EventPath(ev);
        int idx = zr.Find(std::wstring(kSmEvents[ev].file) + L".wav");
        if (idx < 0 && kEvData[ev].legacy) idx = zr.Find(EventLegacyName(ev));
        Bytes body;
        std::wstring e;
        if (idx >= 0 && zr.Extract(idx, body)) {
            SetFileAttributesW(target.c_str(), FILE_ATTRIBUTE_NORMAL);
            if (WriteAllBytes(target, body)) {
                WavInfo wi;
                if (!ReadWavInfo(target, wi)) DeleteFileW(target.c_str());
                PostUpdate(ev);
            } else {
                UpdateEvent(ev, L"", e);
            }
        } else {
            UpdateEvent(ev, L"", e);
        }
    }
    ResetMetaAll();
    auto extractAs = [&](PCWSTR first, PCWSTR second, const std::wstring& dest) {
        int idx = zr.Find(first);
        if (idx < 0) idx = zr.Find(second);
        Bytes body;
        if (idx >= 0 && zr.Extract(idx, body)) {
            SetFileAttributesW(dest.c_str(), FILE_ATTRIBUTE_NORMAL);
            WriteAllBytes(dest, body);
        }
    };
    extractAs(L"Scheme.png", L"visuel.bmp", MetaImagePath());
    extractAs(L"Scheme.ini", L"infos.ini", MetaInfoPath());
    BumpThumb();
    if (!Reapply(err)) return false;
    PlayFileAsync(EventToPlayOnLoad());
    return true;
}

static bool ExportZip(const std::wstring& file, std::wstring& err) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    zipx::Writer w;
    Bytes b;
    for (int ev = 0; ev < kSmEventCount; ev++)
        if (FileExists(EventPath(ev)) && ReadAll(EventPath(ev), b, 64 << 20)) w.Add(std::wstring(kSmEvents[ev].file) + L".wav", b);
    if (FileExists(MetaImagePath()) && ReadAll(MetaImagePath(), b, 64 << 20)) w.Add(L"Scheme.png", b);
    if (FileExists(MetaInfoPath()) && ReadAll(MetaInfoPath(), b, 64 << 20)) w.Add(L"Scheme.ini", b);
    Bytes z = w.Finish();
    if (!WriteAllBytes(file, z)) {
        err = L"Couldn't write the file.";
        return false;
    }
    return true;
}

static std::string AnsiBytes(const std::wstring& s) {
    if (s.empty()) return {};
    int n = WideCharToMultiByte(CP_ACP, 0, s.data(), (int)s.size(), nullptr, 0, nullptr, nullptr);
    std::string out(n > 0 ? n : 0, '\0');
    if (n > 0) WideCharToMultiByte(CP_ACP, 0, s.data(), (int)s.size(), out.data(), n, nullptr, nullptr);
    return out;
}

static bool ExportThemepack(const std::wstring& file, std::wstring& err) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    WCHAR tmpRoot[MAX_PATH]{};
    GetTempPathW(MAX_PATH, tmpRoot);
    std::wstring tmp = std::wstring(tmpRoot) + L"SeamlessSoundManager-" + std::to_wstring(GetTickCount64());
    MakeDirs(tmp);
    SmMeta meta = ReadMeta();
    std::wstring displayName = meta.name.empty() ? L"Sound Manager" : meta.name;
    std::wstring onLoad = EventToPlayOnLoad();
    std::vector<std::wstring> files;
    for (int ev = 0; ev < kSmEventCount; ev++) {
        if (!FileExists(EventPath(ev))) continue;
        std::wstring n = std::wstring(kSmEvents[ev].file) + L".wav";
        CopyFileW(EventPath(ev).c_str(), (tmp + L"\\" + n).c_str(), FALSE);
        files.push_back(n);
    }
    bool haveLogo = WriteLogoPng(tmp + L"\\SoundManager.png");
    if (FileExists(MetaImagePath())) CopyFileW(MetaImagePath().c_str(), (tmp + L"\\Scheme.png").c_str(), FALSE);
    else if (haveLogo) CopyFileW((tmp + L"\\SoundManager.png").c_str(), (tmp + L"\\Scheme.png").c_str(), FALSE);

    std::wstring theme = L"; Generated by SoundManager\r\n; https://github.com/ORelio/Sound-Manager/\r\n[Theme]\r\nDisplayName=" + displayName +
                         L"\r\nBrandImage=SoundManager.png\r\n[MasterThemeSelector]\r\nMTSM=DABJDKT\r\n[Control Panel\\Desktop]\r\nWallpaper=Scheme.png\r\n"
                         L"TileWallpaper=0\r\nWallpaperStyle=0\r\n[VisualStyles]\r\nPath=%SystemRoot%\\resources\\Themes\\Aero\\Aero.msstyles\r\n"
                         L"ColorStyle=NormalColor\r\nSize=NormalSize\r\n[Sounds]\r\nSchemeName=" + displayName + L"\r\n";
    for (int ev = 0; ev < kSmEventCount; ev++) {
        if (!FileExists(EventPath(ev))) continue;
        std::wstring fn = ev == kEvLoadScheme ? FileNameOf(onLoad) : std::wstring(kSmEvents[ev].file) + L".wav";
        for (PCWSTR key : kEvData[ev].keys) {
            if (!key) break;
            theme += L"[AppEvents\\Schemes\\Apps\\" + std::wstring(key) + L"]\r\nDefaultValue=" + fn + L"\r\n";
        }
    }
    std::string themeAnsi = AnsiBytes(theme);
    WriteAll(tmp + L"\\Scheme.theme", themeAnsi.data(), themeAnsi.size());

    std::wstring ddf =
        L".OPTION EXPLICIT\r\n.Set CabinetNameTemplate=Scheme.themepack\r\n.Set Cabinet=on\r\n.Set Compress=on\r\n.Set CabinetFileCountThreshold=0\r\n"
        L".Set FolderFileCountThreshold=0\r\n.Set FolderSizeThreshold=0\r\n.Set MaxCabinetSize=0\r\n.Set MaxDiskFileCount=0\r\n.Set MaxDiskSize=0\r\n"
        L".Set DiskDirectory1=.\r\n";
    for (const auto& n : files) ddf += L"\"" + n + L"\"\r\n";
    if (haveLogo) ddf += L"\"SoundManager.png\"\r\n";
    if (FileExists(tmp + L"\\Scheme.png")) ddf += L"\"Scheme.png\"\r\n";
    ddf += L"\"Scheme.theme\"\r\n";
    std::string ddfAnsi = AnsiBytes(ddf);
    WriteAll(tmp + L"\\Scheme.ddf", ddfAnsi.data(), ddfAnsi.size());

    DWORD code = 1;
    bool ran = RunHidden(QuoteArg(SystemExe(L"makecab.exe")) + L" /F Scheme.ddf", tmp, 60000, &code);
    bool ok = ran && code == 0 && FileExists(tmp + L"\\Scheme.themepack") &&
              CopyFileW((tmp + L"\\Scheme.themepack").c_str(), file.c_str(), FALSE);
    RemoveDirTree(tmp);
    if (!ok) err = L"Couldn't build the themepack.";
    return ok;
}

// ---------------------------------------------------------------------------
// Shared window state
// ---------------------------------------------------------------------------

constexpr UINT WM_SM_TRAY = WM_APP + 10;
constexpr UINT WM_SM_SETTINGS = WM_APP + 11;
constexpr UINT WM_SM_OPEN = WM_APP + 12;
constexpr UINT WM_APP_SETTINGS_RELOAD = WM_APP + 1;
constexpr UINT kTrayId = 1;

static HWND g_msgWnd = nullptr;
static HINSTANCE g_inst = nullptr;

static void NotifySettingsWindow() {
    if (HWND s = smset::g_settingsWnd.load()) PostMessageW(s, WM_APP_SM_ASYNC, 0, 0);
}

// ---------------------------------------------------------------------------
// Engine API: scheme state
// ---------------------------------------------------------------------------

bool SmSoundExists(int ev) { return ValidEvent(ev) && FileExists(EventPath(ev)); }

bool SmSoundDisabled(int ev) {
    if (!ValidEvent(ev)) return false;
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    return g_disabledFlag[ev];
}

std::wstring SmSoundPath(int ev) { return ValidEvent(ev) ? EventPath(ev) : std::wstring(); }

std::wstring SmSoundInfo(int ev) {
    if (!ValidEvent(ev)) return L"No sound";
    static std::mutex mu;
    struct Cached {
        ULONGLONG key = 0;
        std::wstring text;
    };
    static Cached cache[kSmEventCount];
    std::wstring p = EventPath(ev);
    WIN32_FILE_ATTRIBUTE_DATA fa;
    if (!GetFileAttributesExW(p.c_str(), GetFileExInfoStandard, &fa)) return L"No sound";
    ULONGLONG key = (((ULONGLONG)fa.ftLastWriteTime.dwHighDateTime << 32) | fa.ftLastWriteTime.dwLowDateTime) ^
                    (((ULONGLONG)fa.nFileSizeHigh << 32) | fa.nFileSizeLow) ^ 0x9E3779B97F4A7C15ull;
    {
        std::lock_guard<std::mutex> g(mu);
        if (cache[ev].key == key && !cache[ev].text.empty()) return cache[ev].text;
    }
    double secs = 0;
    std::wstring text;
    if (AudioSeconds(p, secs)) {
        WCHAR buf[32];
        swprintf(buf, ARRAYSIZE(buf), L"%.1f s", secs);
        text = buf;
    } else {
        text = L"Unknown length";
    }
    std::lock_guard<std::mutex> g(mu);
    cache[ev].key = key;
    cache[ev].text = text;
    return text;
}

SmMeta SmGetMeta() {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    return ReadMeta();
}

void SmSetMeta(const SmMeta& m) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    WriteMeta(m);
}

std::wstring SmThumbPath() { return FileExists(MetaImagePath()) ? MetaImagePath() : std::wstring(); }

UINT SmThumbVersion() { return g_thumbVersion.load(); }

// ---------------------------------------------------------------------------
// Engine API: per-sound actions
// ---------------------------------------------------------------------------

bool SmPlay(int ev) {
    if (!ValidEvent(ev) || !FileExists(EventPath(ev))) return false;
    PlayFileAsync(EventPath(ev));
    return true;
}

void SmStopPlaying() {
    if (g_previewPlaying.exchange(false)) PlaySoundW(nullptr, nullptr, 0);
}

bool SmReplaceSound(int ev, const std::wstring& file, std::wstring& error) {
    if (!ValidEvent(ev)) return false;
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    SmStopPlaying();
    if (!UpdateEvent(ev, file, error)) return false;
    return Reapply(error);
}

bool SmResetSound(int ev, std::wstring& error) {
    if (!ValidEvent(ev)) return false;
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    SmStopPlaying();
    CopyDefaultEvent(ev, L".Default", error);
    std::wstring e2;
    bool ok = Reapply(e2);
    if (error.empty()) error = e2;
    return error.empty() && ok;
}

void SmRemoveSound(int ev) {
    if (!ValidEvent(ev)) return;
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    SmStopPlaying();
    std::wstring e;
    UpdateEvent(ev, L"", e);
    Reapply(e);
}

void SmSetDisabled(int ev, bool disabled) {
    if (!ValidEvent(ev)) return;
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    g_disabledFlag[ev] = disabled;
    g_disabledDirty = true;
    WriteIniState();
    std::wstring e;
    Reapply(e);
}

void SmShowInFolder(int ev) {
    if (ValidEvent(ev) && FileExists(EventPath(ev))) {
        std::wstring args = L"/select,\"" + EventPath(ev) + L"\"";
        ShellExecuteW(nullptr, L"open", L"explorer.exe", args.c_str(), nullptr, SW_SHOWNORMAL);
    } else {
        MakeDirs(MediaDir());
        ShellExecuteW(nullptr, L"open", MediaDir().c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    }
}

// ---------------------------------------------------------------------------
// Engine API: scheme actions
// ---------------------------------------------------------------------------

bool SmSetImage(const std::wstring& file, std::wstring& error) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    MakeDirs(MediaDir());
    std::wstring tmp = MediaDir() + L"\\Scheme.png.new";
    if (!ImageToThumb(file, tmp)) {
        DeleteFileW(tmp.c_str());
        error = L"This picture can't be read.";
        return false;
    }
    SetFileAttributesW(MetaImagePath().c_str(), FILE_ATTRIBUTE_NORMAL);
    bool ok = MoveFileExW(tmp.c_str(), MetaImagePath().c_str(), MOVEFILE_REPLACE_EXISTING) != 0;
    if (!ok) error = L"Couldn't save the picture.";
    BumpThumb();
    return ok;
}

void SmRemoveImage() {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    SetFileAttributesW(MetaImagePath().c_str(), FILE_ATTRIBUTE_NORMAL);
    DeleteFileW(MetaImagePath().c_str());
    BumpThumb();
}

bool SmImport(const std::wstring& file, std::wstring& error) {
    SmStopPlaying();
    return ImportArchive(file, error);
}

bool SmExportThs(const std::wstring& file, std::wstring& error) { return ExportZip(file, error); }

bool SmExportThemepack(const std::wstring& file, std::wstring& error) { return ExportThemepack(file, error); }

bool SmLoadWindowsDefaults(std::wstring& error) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    SmStopPlaying();
    for (int ev = 0; ev < kSmEventCount; ev++) CopyDefaultEvent(ev, L".Default", error);
    ResetMetaAll();
    std::wstring e2;
    bool ok = Reapply(e2);
    if (error.empty()) error = e2;
    return error.empty() && ok;
}

static std::wstring SystemSchemeName(const std::wstring& id) {
    std::wstring v;
    if (RegReadDefault(std::wstring(kNamesKey) + L"\\" + id, v) && !v.empty() && v[0] != L'@') return v;
    return id;
}

std::vector<SmSystemScheme> SmSystemSchemes() {
    std::vector<SmSystemScheme> out;
    for (const std::wstring& id : RegSubKeys(kNamesKey)) {
        if (EqCI(id, L"SoundManager") || EqCI(id, L".None")) continue;
        out.push_back({id, SystemSchemeName(id)});
    }
    return out;
}

bool SmLoadSystemScheme(const std::wstring& id, std::wstring& error) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    SmStopPlaying();
    for (int ev = 0; ev < kSmEventCount; ev++) CopyDefaultEvent(ev, id, error);
    WriteMeta({SystemSchemeName(id), L"", L""});
    SetFileAttributesW(MetaImagePath().c_str(), FILE_ATTRIBUTE_NORMAL);
    DeleteFileW(MetaImagePath().c_str());
    BumpThumb();
    std::wstring e2;
    bool ok = Reapply(e2);
    if (error.empty()) error = e2;
    return error.empty() && ok;
}

void SmOpenDataFolder() {
    MakeDirs(MediaDir());
    ShellExecuteW(nullptr, L"open", MediaDir().c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

bool SmReinstall(std::wstring& error) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    return Reapply(error);
}

bool SmUninstall(std::wstring& error) {
    std::lock_guard<std::recursive_mutex> g(g_smLock);
    SmStopPlaying();
    return SchemeUninstall(error);
}

bool SmIsActive() { return SchemeIsActive(); }

// ---------------------------------------------------------------------------
// Engine API: presets (download on one worker thread)
// ---------------------------------------------------------------------------

static std::mutex g_jobMu;
static int g_jobPreset = -1;
static bool g_jobBusy = false, g_jobError = false, g_jobFinished = false;
static std::wstring g_jobStatus;
static HANDLE g_jobThread = nullptr;
static HWND g_jobNotify = nullptr;
static ULONGLONG g_jobLastPost = 0;

struct JobArgs {
    int preset, action;
    HWND notify;
};

static std::wstring PresetCachePath(int i) {
    return StoragePath() + L"\\presets\\" + ReplaceAll(kSmPresets[i].path, L"/", L"\\");
}

static void JobNotify(bool force) {
    HWND w;
    {
        std::lock_guard<std::mutex> g(g_jobMu);
        ULONGLONG now = GetTickCount64();
        if (!force && now - g_jobLastPost < 150) return;
        g_jobLastPost = now;
        w = g_jobNotify;
    }
    if (w && IsWindow(w)) PostMessageW(w, WM_APP_SM_ASYNC, 0, 0);
}

static void JobSetStatus(const std::wstring& s, bool force) {
    {
        std::lock_guard<std::mutex> g(g_jobMu);
        g_jobStatus = s;
    }
    JobNotify(force);
}

static std::string UrlEncodePath(const std::wstring& path) {
    std::string utf8 = WideToUtf8(path), out;
    static const char* hex = "0123456789ABCDEF";
    for (unsigned char c : utf8) {
        if (isalnum(c) || strchr("-_.~/()!'*,;:@&=+$", c)) out += (char)c;
        else {
            out += '%';
            out += hex[c >> 4];
            out += hex[c & 15];
        }
    }
    return out;
}

static bool HttpDownload(const std::wstring& repoPath, const std::wstring& dest, const std::function<void(int)>& progress) {
    std::wstring objPath = L"/ORelio/Sound-Manager-Schemes/master/" + Utf8ToWide(UrlEncodePath(repoPath).c_str(), UrlEncodePath(repoPath).size());
    HINTERNET ses = WinHttpOpen(L"SeamlessSoundManager", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, nullptr, nullptr, 0);
    if (!ses) return false;
    WinHttpSetTimeouts(ses, 10000, 10000, 20000, 30000);
    bool ok = false;
    HINTERNET con = WinHttpConnect(ses, L"raw.githubusercontent.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
    HINTERNET req = con ? WinHttpOpenRequest(con, L"GET", objPath.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE) : nullptr;
    if (req && WinHttpSendRequest(req, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0) && WinHttpReceiveResponse(req, nullptr)) {
        DWORD status = 0, sl = sizeof(status);
        WinHttpQueryHeaders(req, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &status, &sl, WINHTTP_NO_HEADER_INDEX);
        wchar_t lenBuf[32]{};
        DWORD ll = sizeof(lenBuf);
        unsigned long long total = 0;
        if (WinHttpQueryHeaders(req, WINHTTP_QUERY_CONTENT_LENGTH, WINHTTP_HEADER_NAME_BY_INDEX, lenBuf, &ll, WINHTTP_NO_HEADER_INDEX)) total = _wcstoui64(lenBuf, nullptr, 10);
        if (status == 200) {
            std::wstring part = dest + L".part";
            HANDLE h = CreateFileW(part.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (h != INVALID_HANDLE_VALUE) {
                unsigned long long done = 0;
                std::vector<uint8_t> buf(64 * 1024);
                bool good = true;
                for (;;) {
                    if (g_stop.load()) {
                        good = false;
                        break;
                    }
                    DWORD got = 0;
                    if (!WinHttpReadData(req, buf.data(), (DWORD)buf.size(), &got)) {
                        good = false;
                        break;
                    }
                    if (!got) break;
                    DWORD put = 0;
                    if (!WriteFile(h, buf.data(), got, &put, nullptr) || put != got) {
                        good = false;
                        break;
                    }
                    done += got;
                    if (done > ((unsigned long long)256 << 20)) {
                        good = false;
                        break;
                    }
                    if (total) progress((int)std::min<unsigned long long>(99, done * 100 / total));
                }
                CloseHandle(h);
                if (good && done > 0) {
                    ok = MoveFileExW(part.c_str(), dest.c_str(), MOVEFILE_REPLACE_EXISTING) != 0;
                    progress(100);
                }
                if (!ok) DeleteFileW(part.c_str());
            }
        }
    }
    if (req) WinHttpCloseHandle(req);
    if (con) WinHttpCloseHandle(con);
    WinHttpCloseHandle(ses);
    return ok;
}

// Plays Startup.wav, else Logon.wav, else the first .wav of the scheme file.
static bool PreviewArchive(const std::wstring& file) {
    Bytes zipBytes;
    std::wstring e;
    if (ExtOf(file) == L".soundpack") {
        if (!ProprietaryToThs(file, zipBytes, e)) return false;
    } else if (!ReadAll(file, zipBytes, (size_t)512 << 20)) {
        return false;
    }
    zipx::Reader zr;
    if (!zr.Open(zipBytes)) return false;
    int idx = zr.Find(L"Startup.wav");
    if (idx < 0) idx = zr.Find(L"Logon.wav");
    if (idx < 0) idx = zr.Find(EventLegacyName(kEvStartup));
    if (idx < 0) idx = zr.Find(EventLegacyName(kEvLogon));
    for (size_t i = 0; idx < 0 && i < zr.entries.size(); i++)
        if (ExtOf(zr.entries[i].name) == L".wav") idx = (int)i;
    Bytes body;
    if (idx < 0 || !zr.Extract(idx, body)) return false;
    std::wstring tmp = StoragePath() + L"\\preview.wav";
    SmStopPlaying();
    if (!WriteAllBytes(tmp, body)) return false;
    PlayFileAsync(tmp);
    return true;
}

static DWORD WINAPI PresetThread(LPVOID param) {
    std::unique_ptr<JobArgs> a((JobArgs*)param);
    const SmPreset& pr = kSmPresets[a->preset];
    std::wstring name = pr.name;
    std::wstring cache = PresetCachePath(a->preset);
    bool failed = false;
    std::wstring finalText;
    if (!FileExists(cache)) {
        MakeDirs(DirOf(cache));
        JobSetStatus(L"Downloading " + name + L"...", true);
        bool ok = HttpDownload(pr.path, cache, [&](int pct) { JobSetStatus(L"Downloading " + name + L": " + std::to_wstring(pct) + L"%", false); });
        if (!ok) {
            failed = true;
            finalText = L"Couldn't download " + name;
        }
    }
    if (!failed) {
        if (a->action == 1) {
            std::wstring e;
            if (ImportArchive(cache, e)) finalText = L"Loaded " + name;
            else {
                failed = true;
                finalText = L"Couldn't load " + name;
            }
        } else if (PreviewArchive(cache)) {
            finalText = L"Loaded " + name;
        } else {
            failed = true;
            finalText = L"Couldn't play " + name;
        }
    }
    {
        std::lock_guard<std::mutex> g(g_jobMu);
        g_jobStatus = finalText;
        g_jobError = failed;
        g_jobFinished = true;
        g_jobBusy = false;
    }
    JobNotify(true);
    return 0;
}

void SmPresetStart(int preset, int action, HWND notify) {
    if (preset < 0 || preset >= kSmPresetCount) return;
    HANDLE old = nullptr;
    {
        std::lock_guard<std::mutex> g(g_jobMu);
        if (g_jobBusy) return;
        old = g_jobThread;
        g_jobThread = nullptr;
    }
    if (old) {
        WaitForSingleObject(old, 5000);
        CloseHandle(old);
    }
    {
        std::lock_guard<std::mutex> g(g_jobMu);
        g_jobBusy = true;
        g_jobPreset = preset;
        g_jobError = false;
        g_jobFinished = false;
        g_jobNotify = notify;
        g_jobStatus = std::wstring(L"Downloading ") + kSmPresets[preset].name + L"...";
    }
    auto* a = new JobArgs{preset, action, notify};
    HANDLE t = CreateThread(nullptr, 0, PresetThread, a, 0, nullptr);
    if (!t) {
        delete a;
        std::lock_guard<std::mutex> g(g_jobMu);
        g_jobBusy = false;
        g_jobError = true;
        g_jobFinished = true;
        g_jobStatus = L"Couldn't start the download";
        return;
    }
    std::lock_guard<std::mutex> g(g_jobMu);
    g_jobThread = t;
}

bool SmPresetCached(int preset) { return preset >= 0 && preset < kSmPresetCount && FileExists(PresetCachePath(preset)); }

int SmPresetBusy() {
    std::lock_guard<std::mutex> g(g_jobMu);
    return g_jobBusy ? g_jobPreset : -1;
}

std::wstring SmPresetStatus(bool& error, bool& finished) {
    std::lock_guard<std::mutex> g(g_jobMu);
    error = g_jobError;
    finished = g_jobFinished;
    if (g_jobFinished) g_jobFinished = false;
    return g_jobStatus;
}

static void StopPresetJob() {
    HANDLE t;
    {
        std::lock_guard<std::mutex> g(g_jobMu);
        t = g_jobThread;
        g_jobThread = nullptr;
        g_jobNotify = nullptr;
    }
    if (t) {
        if (WaitForSingleObject(t, 15000) != WAIT_OBJECT_0) Wh_Log(L"Preset download did not stop in 15 s");
        CloseHandle(t);
    }
}

// ---------------------------------------------------------------------------
// Pending file (double-click in Explorer): ProgIDs, import.js, inbox watcher
// ---------------------------------------------------------------------------

static std::mutex g_pendingMu;
static std::wstring g_pendingFile;

std::wstring SmPendingFile() {
    std::lock_guard<std::mutex> g(g_pendingMu);
    return g_pendingFile;
}

void SmClearPendingFile() {
    std::lock_guard<std::mutex> g(g_pendingMu);
    g_pendingFile.clear();
}

static std::wstring InboxDir() { return StoragePath() + L"\\inbox"; }

static void WriteImportScript() {
    static const char kJs[] =
        "var a = WScript.Arguments;\r\n"
        "if (a.length > 0) {\r\n"
        "  var fso = new ActiveXObject(\"Scripting.FileSystemObject\");\r\n"
        "  var sh = new ActiveXObject(\"WScript.Shell\");\r\n"
        "  var dir = sh.ExpandEnvironmentStrings(\"%LOCALAPPDATA%\") + \"\\\\SeamlessSoundManager\\\\inbox\";\r\n"
        "  if (!fso.FolderExists(dir)) fso.CreateFolder(dir);\r\n"
        "  var base = dir + \"\\\\\" + (new Date().getTime()) + Math.floor(Math.random() * 1000);\r\n"
        "  var f = fso.CreateTextFile(base + \".tmp\", true, true);\r\n"
        "  f.Write(a(0));\r\n"
        "  f.Close();\r\n"
        "  fso.MoveFile(base + \".tmp\", base + \".txt\");\r\n"
        "}\r\n";
    std::wstring path = StoragePath() + L"\\import.js";
    Bytes cur;
    if (ReadAll(path, cur, 1 << 16) && cur.size() == sizeof(kJs) - 1 && !memcmp(cur.data(), kJs, cur.size())) return;
    WriteAll(path, kJs, sizeof(kJs) - 1);
}

static void SetKeyDefault(const std::wstring& sub, const std::wstring& value) { RegWriteDefault(L"Software\\Classes\\" + sub, value); }

static void BackupAssocOnce() {
    if (Wh_GetIntValue(L"assocBackedUp", 0)) return;
    SYSTEMTIME t;
    GetLocalTime(&t);
    WCHAR stamp[32];
    swprintf(stamp, ARRAYSIZE(stamp), L"%04d%02d%02d-%02d%02d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute);
    std::wstring dir = StoragePath() + L"\\backup";
    MakeDirs(dir);
    static const wchar_t* keys[] = {L".ths", L".soundpack", L"ths_auto_file", L"soundpack_auto_file"};
    std::wstring merged = L"Windows Registry Editor Version 5.00\r\n\r\n";
    for (const wchar_t* k : keys) {
        std::wstring tmp = dir + L"\\part-" + k + L".reg";
        DeleteFileW(tmp.c_str());
        DWORD code = 1;
        RunHidden(QuoteArg(SystemExe(L"reg.exe")) + L" export " + QuoteArg(std::wstring(L"HKCU\\Software\\Classes\\") + k) + L" " + QuoteArg(tmp) + L" /y", L"", 20000, &code);
        Bytes b;
        if (code == 0 && ReadAll(tmp, b, 1 << 22) && b.size() >= 2) {
            size_t off = (b[0] == 0xFF && b[1] == 0xFE) ? 2 : 0;
            std::wstring text((const wchar_t*)(b.data() + off), (b.size() - off) / 2);
            size_t nl = text.find(L'\n');
            if (nl != std::wstring::npos) merged += text.substr(nl + 1);
        }
        DeleteFileW(tmp.c_str());
    }
    Bytes out = {0xFF, 0xFE};
    out.insert(out.end(), (const uint8_t*)merged.data(), (const uint8_t*)merged.data() + merged.size() * 2);
    if (WriteAllBytes(dir + L"\\assoc-" + stamp + L".reg", out)) Wh_SetIntValue(L"assocBackedUp", 1);
}

static void SetupAssoc() {
    WriteImportScript();
    BackupAssocOnce();
    std::wstring cmd = L"wscript.exe //B //Nologo \"" + StoragePath() + L"\\import.js\" \"%1\"";
    struct Row {
        PCWSTR ext, prog, desc;
    };
    static const Row rows[] = {{L".ths", L"ths_auto_file", L"Sound Scheme File"},
                               {L".soundpack", L"soundpack_auto_file", L"Sound Scheme File (Proprietary file format)"}};
    for (const Row& r : rows) {
        SetKeyDefault(r.ext, r.prog);
        SetKeyDefault(r.prog, r.desc);
        SetKeyDefault(std::wstring(r.prog) + L"\\DefaultIcon", L"%SystemRoot%\\System32\\mmsys.cpl,0");
        SetKeyDefault(std::wstring(r.prog) + L"\\shell", L"open");
        SetKeyDefault(std::wstring(r.prog) + L"\\shell\\open", L"Open");
        SetKeyDefault(std::wstring(r.prog) + L"\\shell\\open\\command", cmd);
        // Sound Manager's own verb ("import", pointing at the app) goes, so the menu shows one Open.
        RegDeleteTreeW(HKEY_CURRENT_USER, (L"Software\\Classes\\" + std::wstring(r.prog) + L"\\shell\\import").c_str());
    }
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);
}

static void RemoveAssoc() {
    static const wchar_t* progs[] = {L"ths_auto_file", L"soundpack_auto_file"};
    static const wchar_t* exts[] = {L".ths", L".soundpack"};
    for (int i = 0; i < 2; i++) {
        std::wstring cur;
        if (RegReadDefault(std::wstring(L"Software\\Classes\\") + exts[i], cur) && cur == progs[i])
            RegDeleteTreeW(HKEY_CURRENT_USER, (std::wstring(L"Software\\Classes\\") + exts[i]).c_str());
        RegDeleteTreeW(HKEY_CURRENT_USER, (std::wstring(L"Software\\Classes\\") + progs[i]).c_str());
    }
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);
}

static HANDLE g_inboxThread = nullptr, g_inboxStop = nullptr;

static void ScanInbox() {
    std::wstring dir = InboxDir();
    WIN32_FIND_DATAW fd;
    HANDLE h = FindFirstFileW((dir + L"\\*.txt").c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE) return;
    std::vector<std::wstring> names;
    do {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) names.push_back(fd.cFileName);
    } while (FindNextFileW(h, &fd));
    FindClose(h);
    std::sort(names.begin(), names.end());
    bool any = false;
    for (const auto& n : names) {
        std::wstring p = dir + L"\\" + n;
        Bytes b;
        bool read = ReadAll(p, b, 1 << 16);
        DeleteFileW(p.c_str());
        if (!read || b.empty()) continue;
        std::wstring target;
        if (b.size() >= 2 && b[0] == 0xFF && b[1] == 0xFE) target.assign((const wchar_t*)(b.data() + 2), (b.size() - 2) / 2);
        else {
            size_t off = (b.size() >= 3 && b[0] == 0xEF && b[1] == 0xBB && b[2] == 0xBF) ? 3 : 0;
            target = Utf8ToWide((const char*)b.data() + off, b.size() - off);
        }
        target = Trim(target);
        std::wstring ext = ExtOf(target);
        if (target.empty() || (ext != L".ths" && ext != L".soundpack") || !FileExists(target)) continue;
        std::lock_guard<std::mutex> g(g_pendingMu);
        g_pendingFile = target;
        any = true;
    }
    if (any && g_msgWnd) PostMessageW(g_msgWnd, WM_SM_OPEN, 0, 0);
}

static DWORD WINAPI InboxThread(LPVOID) {
    std::wstring dir = InboxDir();
    MakeDirs(dir);
    HANDLE change = FindFirstChangeNotificationW(dir.c_str(), FALSE, FILE_NOTIFY_CHANGE_FILE_NAME);
    ScanInbox();
    if (change == INVALID_HANDLE_VALUE) {
        while (WaitForSingleObject(g_inboxStop, 2000) == WAIT_TIMEOUT) ScanInbox();
        return 0;
    }
    HANDLE hs[2] = {change, g_inboxStop};
    for (;;) {
        DWORD r = WaitForMultipleObjects(2, hs, FALSE, 30000);
        if (r == WAIT_OBJECT_0 + 1) break;
        if (r == WAIT_OBJECT_0) {
            Sleep(150);
            ScanInbox();
            FindNextChangeNotification(change);
        } else if (r == WAIT_TIMEOUT) {
            ScanInbox();
        } else {
            break;
        }
    }
    FindCloseChangeNotification(change);
    return 0;
}

// ---------------------------------------------------------------------------
// Windows startup sound policy (SystemStartupSound.cs)
// ---------------------------------------------------------------------------

static bool StartupDefaultEnabled() { return !(IsWin8() || IsWin10()); }

static void StartupRegLocation(PCWSTR& key, PCWSTR& value) {
    if (IsWin11()) {
        key = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\EditionOverrides";
        value = L"UserSetting_DisableStartupSound";
    } else {
        key = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\LogonUI\\BootAnimation";
        value = L"DisableStartupSound";
    }
}

static bool GetSystemStartupEnabled() {
    PCWSTR key, value;
    StartupRegLocation(key, value);
    DWORD v = 0, cb = sizeof(v);
    if (RegGetValueW(HKEY_LOCAL_MACHINE, key, value, RRF_RT_REG_DWORD | RRF_SUBKEY_WOW6464KEY, nullptr, &v, &cb) == ERROR_SUCCESS) return v == 0;
    return StartupDefaultEnabled();
}

static void SetSystemStartupEnabled(bool enabled) {
    PCWSTR key, value;
    StartupRegLocation(key, value);
    HKEY k = nullptr;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, key, 0, KEY_SET_VALUE | KEY_WOW64_64KEY, &k) != ERROR_SUCCESS) return;  // Needs admin; fine to skip.
    DWORD v = enabled ? 0 : 1;
    RegSetValueExW(k, value, 0, REG_DWORD, (const BYTE*)&v, sizeof(v));
    RegCloseKey(k);
}

static void ApplyStartupPolicy() {
    bool desired = g_cPatch.load() ? true : (g_cSession.load() ? false : StartupDefaultEnabled());
    if (GetSystemStartupEnabled() != desired) SetSystemStartupEnabled(desired);
}

// ---------------------------------------------------------------------------
// Session sounds: boot, logon, logoff, shutdown, lock, unlock (BgSoundPlayer.cs)
// ---------------------------------------------------------------------------

static std::wstring LastBootFile() { return DataDir() + L"\\LastBootTime.ini"; }

static std::string BootTimeString() {
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULONGLONG t = ((ULONGLONG)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
    ULONGLONG nowMs = t / 10000 - 11644473600000ull;
    ULONGLONG bootSec = (nowMs - GetTickCount64()) / 1000;
    std::string s = std::to_string(bootSec);
    s.back() = '0';
    return s;
}

static bool HasPassword() {
    WCHAR user[256]{};
    DWORD n = ARRAYSIZE(user);
    if (!GetUserNameW(user, &n)) return true;
    HANDLE token = nullptr;
    if (LogonUserW(user, L".", L"", LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &token)) {
        CloseHandle(token);
        return false;
    }
    return GetLastError() != 1327;  // ERROR_ACCOUNT_RESTRICTION: blank password.
}

static bool HasAutoLogon() {
    WCHAR user[256]{}, auto_[16]{}, def[256]{};
    DWORD n = ARRAYSIZE(user);
    GetUserNameW(user, &n);
    DWORD cb = sizeof(auto_);
    const wchar_t* key = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon";
    if (RegGetValueW(HKEY_LOCAL_MACHINE, key, L"AutoAdminLogon", RRF_RT_REG_SZ | RRF_SUBKEY_WOW6464KEY, nullptr, auto_, &cb) != ERROR_SUCCESS) return false;
    if (wcscmp(auto_, L"1") != 0) return false;
    cb = sizeof(def);
    if (RegGetValueW(HKEY_LOCAL_MACHINE, key, L"DefaultUserName", RRF_RT_REG_SZ | RRF_SUBKEY_WOW6464KEY, nullptr, def, &cb) != ERROR_SUCCESS) return false;
    return EqCI(def, user);
}

static std::wstring ForegroundExe() {
    HWND h = GetForegroundWindow();
    if (!h) return {};
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    HANDLE p = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!p) return {};
    WCHAR buf[MAX_PATH * 2]{};
    DWORD len = ARRAYSIZE(buf);
    std::wstring out;
    if (QueryFullProcessImageNameW(p, 0, buf, &len)) out = Lower(FileNameOf(buf));
    CloseHandle(p);
    return out;
}

// Plays a file and waits for it to end (or the mod to stop), capped at 30 s.
static void PlayAndWait(const std::wstring& path) {
    if (path.empty() || !FileExists(path)) return;
    double secs = 5;
    AudioSeconds(path, secs);
    secs = std::clamp(secs, 0.2, 30.0);
    if (!PlaySoundW(path.c_str(), nullptr, SND_FILENAME | SND_ASYNC | SND_NODEFAULT)) return;
    g_previewPlaying = true;
    ULONGLONG end = GetTickCount64() + (ULONGLONG)(secs * 1000) + 400;
    while (GetTickCount64() < end && !g_stop.load()) Sleep(50);
    PlaySoundW(nullptr, nullptr, 0);
}

static void PlayEvent(int ev) {
    if (!g_cSession.load()) return;
    std::wstring p;
    {
        std::lock_guard<std::recursive_mutex> g(g_smLock);
        if (g_disabledFlag[ev]) return;
        p = GetCurrentFile(ev);
    }
    PlayAndWait(p);
}

static void PlayBootSound() {
    if (!g_cSession.load()) return;
    std::string boot = BootTimeString();
    std::wstring file = LastBootFile();
    Bytes cur;
    std::string last;
    if (ReadAll(file, cur, 256)) last.assign(cur.begin(), cur.end());
    while (!last.empty() && (last.back() == '\r' || last.back() == '\n' || last.back() == ' ')) last.pop_back();
    if (last == boot) return;  // Not a new boot.
    MakeDirs(DataDir());
    WriteAll(file, boot.data(), boot.size());
    int ev;
    if (!GetSystemStartupEnabled()) ev = kEvStartup;
    else if (!HasPassword() || HasAutoLogon()) return;
    else ev = (g_cPreferStartup.load() && SmSoundExists(kEvStartup)) ? kEvStartup : kEvLogon;
    for (int i = 0; i < 600 && !g_stop.load(); i++) {
        std::wstring fg = ForegroundExe();
        if (fg != L"idle.exe" && fg != L"lockapp.exe" && fg != L"logonui.exe") break;
        Sleep(100);
    }
    if (g_stop.load()) return;
    PlayEvent(ev);
}

static const wchar_t kSessionClass[] = L"SeamlessSoundManagerSession";
static HANDLE g_sessionThread = nullptr;
static DWORD g_sessionTid = 0;

static LRESULT CALLBACK SessionProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_WTSSESSION_CHANGE:
            if (wp == WTS_SESSION_LOCK && SmSoundExists(kEvLogoff)) PlayEvent(kEvLogoff);
            else if (wp == WTS_SESSION_UNLOCK && SmSoundExists(kEvLogon)) PlayEvent(kEvLogon);
            return 0;
        case WM_QUERYENDSESSION: {
            if (!g_cSession.load()) return TRUE;
            bool logoff = (lp & ENDSESSION_LOGOFF) != 0;
            bool shutdown = !logoff;
            bool playShutdown = (shutdown || g_cPreferStartup.load()) && SmSoundExists(kEvShutdown);
            if (playShutdown) {
                ShutdownBlockReasonCreate(hwnd, L"Playing Shutdown sound");
                if (shutdown) DeleteFileW(LastBootFile().c_str());
                PlayEvent(kEvShutdown);
            } else {
                ShutdownBlockReasonCreate(hwnd, L"Playing Logoff sound");
                PlayEvent(kEvLogoff);
            }
            ShutdownBlockReasonDestroy(hwnd);
            return TRUE;
        }
        case WM_ENDSESSION:
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static DWORD WINAPI SessionThread(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    g_sessionTid = GetCurrentThreadId();
    WNDCLASSW wc{};
    wc.lpfnWndProc = SessionProc;
    wc.hInstance = g_inst;
    wc.lpszClassName = kSessionClass;
    RegisterClassW(&wc);
    HWND w = CreateWindowExW(WS_EX_TOOLWINDOW, kSessionClass, L"Seamless Sound Manager session", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, g_inst, nullptr);
    bool reg = w && WTSRegisterSessionNotification(w, NOTIFY_FOR_THIS_SESSION);
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    if (reg) WTSUnRegisterSessionNotification(w);
    if (w) DestroyWindow(w);
    UnregisterClassW(kSessionClass, g_inst);
    return 0;
}

// ---------------------------------------------------------------------------
// Settings, first-run migration, mod start
// ---------------------------------------------------------------------------

static void LoadSettings() {
    g_cMissing = Wh_GetIntSetting(L"missingUseDefault") != 0;
    g_cSession = Wh_GetIntSetting(L"playSessionSounds") != 0;
    g_cPreferStartup = Wh_GetIntSetting(L"preferStartupSound") != 0;
    g_cAssoc = Wh_GetIntSetting(L"fileAssoc") != 0;
    g_cConvert = Wh_GetIntSetting(L"convertProprietary") != 0;
    g_cPatch = Wh_GetIntSetting(L"patchStartupSound") != 0;
    g_cTray = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    g_smAnimations = Wh_GetIntSetting(L"animations") != 0;
}

// The first run reads an existing SoundManager.ini and pushes only differing values into the mod settings.
static void MigrateFromIni() {
    if (Wh_GetIntValue(L"migrated", 0) != 0) return;
    std::map<std::wstring, std::wstring> kv;
    if (ParseIniFile(IniPath(), kv)) {
        struct Row {
            PCWSTR setting;
            std::atomic<bool>* cur;
            PCWSTR k1, k2;
        };
        const Row rows[] = {{L"patchStartupSound", &g_cPatch, L"patchstartupsound", L"win7patch"},
                            {L"missingUseDefault", &g_cMissing, L"usedefaultonmissingsound", nullptr},
                            {L"convertProprietary", &g_cConvert, L"convertproprietaryfiles", nullptr},
                            {L"preferStartupSound", &g_cPreferStartup, L"preferstartupsoundonlogon", nullptr}};
        for (const Row& r : rows) {
            auto it = kv.find(r.k1);
            if (it == kv.end() && r.k2) it = kv.find(r.k2);
            if (it == kv.end()) continue;
            bool want = Str2Bool(it->second);
            if (want != r.cur->load()) {
                SaveSettingAsync(r.setting, want ? L"1" : L"0");
                r.cur->store(want);
            }
        }
    }
    Wh_SetIntValue(L"migrated", 1);
}

static HANDLE g_startThread = nullptr;

// Everything slow at mod start runs here so the tool process comes up at once.
static DWORD WINAPI StartupThread(LPVOID) {
    {
        std::lock_guard<std::recursive_mutex> g(g_smLock);
        MakeDirs(MediaDir());
        bool firstSetup = !SchemeInstalled();
        std::wstring e;
        SchemeSetup();
        if (SchemeIsActive() || firstSetup) SchemeApply(L"SoundManager", g_cMissing.load(), e);
        ApplyStartupPolicy();
        if (CanPatch()) {
            std::wstring p = EventPath(kEvStartup);
            Bytes b;
            if (FileExists(p) && ReadAll(p, b, 64 << 20)) ImageresPatch(b.data(), b.size());
        }
    }
    if (g_cAssoc.load() && !g_stop.load()) SetupAssoc();
    if (!g_stop.load()) PlayBootSound();
    return 0;
}

// ---------------------------------------------------------------------------
// Tray icon and UI thread
// ---------------------------------------------------------------------------

static UINT g_taskbarCreated;
static bool g_trayAdded;
static HICON g_trayIcon;

static void EnableDarkMenus() {
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!ux) return;
    using SetMode = int(WINAPI*)(int);
    using Flush = void(WINAPI*)();
    if (auto set = (SetMode)(void*)GetProcAddress(ux, MAKEINTRESOURCEA(135))) set(2 /* ForceDark */);
    if (auto flush = (Flush)(void*)GetProcAddress(ux, MAKEINTRESOURCEA(136))) flush();
}

static void UpdateTray(bool add) {
    NOTIFYICONDATAW nid{};
    nid.cbSize = sizeof(nid);
    nid.hWnd = g_msgWnd;
    nid.uID = kTrayId;
    if (!g_cTray.load()) {
        if (g_trayAdded) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
        return;
    }
    HICON icon = MakeTrayIcon();
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_SM_TRAY;
    nid.hIcon = icon ? icon : LoadIconW(nullptr, IDI_APPLICATION);
    wcsncpy_s(nid.szTip, L"Seamless Sound Manager", _TRUNCATE);
    if (!g_trayAdded || add) {
        if (g_trayAdded) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = Shell_NotifyIconW(NIM_ADD, &nid) != FALSE;
        if (g_trayAdded) {
            nid.uVersion = NOTIFYICON_VERSION_4;
            Shell_NotifyIconW(NIM_SETVERSION, &nid);
        }
    } else {
        Shell_NotifyIconW(NIM_MODIFY, &nid);
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = icon;
}

static void ShowTrayMenu(POINT pt) {
    enum { IDM_SETTINGS = 1, IDM_FOLDER };
    HMENU menu = CreatePopupMenu();
    AppendMenuW(menu, MF_STRING, IDM_SETTINGS, L"Settings");
    AppendMenuW(menu, MF_STRING, IDM_FOLDER, L"Open sounds folder");
    SetForegroundWindow(g_msgWnd);
    UINT cmd = TrackPopupMenuEx(menu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_RIGHTBUTTON | (GetSystemMetrics(SM_MENUDROPALIGNMENT) ? TPM_RIGHTALIGN : TPM_LEFTALIGN), pt.x,
                                pt.y, g_msgWnd, nullptr);
    PostMessageW(g_msgWnd, WM_NULL, 0, 0);
    DestroyMenu(menu);
    if (cmd == IDM_SETTINGS) smset::OpenSettingsWindow();
    else if (cmd == IDM_FOLDER) SmOpenDataFolder();
}

static void HandleSettingsChanged() {
    bool oldAssoc = g_cAssoc.load(), oldPatch = g_cPatch.load();
    LoadSettings();
    {
        std::lock_guard<std::recursive_mutex> g(g_smLock);
        WriteIniState();
    }
    UpdateTray(false);
    if (g_cAssoc.load() && !oldAssoc) SetupAssoc();
    else if (!g_cAssoc.load() && oldAssoc) RemoveAssoc();
    if (g_cPatch.load() != oldPatch) {
        // The imageres change itself runs on a short-lived thread, it can take a while.
        HANDLE t = CreateThread(nullptr, 0, [](LPVOID) -> DWORD {
            std::lock_guard<std::recursive_mutex> g(g_smLock);
            ApplyStartupPolicy();
            if (CanPatch()) PostUpdate(kEvStartup);
            else if (IsElevated()) ImageresRestore();
            return 0;
        }, nullptr, 0, nullptr);
        if (t) {
            WaitForSingleObject(t, 120000);
            CloseHandle(t);
        }
    } else {
        ApplyStartupPolicy();
    }
    std::wstring e;
    SmReinstall(e);
    if (HWND s = smset::g_settingsWnd.load()) PostMessageW(s, WM_APP_SETTINGS_RELOAD, 0, 0);
}

static LRESULT CALLBACK MsgWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == g_taskbarCreated && g_taskbarCreated) {
        g_trayAdded = false;
        UpdateTray(true);
        return 0;
    }
    switch (msg) {
        case WM_SM_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT: smset::OpenSettingsWindow(); break;
                case WM_CONTEXTMENU: ShowTrayMenu(POINT{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)}); break;
            }
            return 0;
        case WM_SM_SETTINGS: HandleSettingsChanged(); return 0;
        case WM_SM_OPEN:
            smset::OpenSettingsWindow();
            NotifySettingsWindow();
            SetTimer(hwnd, 1, 600, nullptr);
            return 0;
        case WM_TIMER:
            if (wp == 1) {
                KillTimer(hwnd, 1);
                NotifySettingsWindow();
            }
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static const wchar_t kMsgClass[] = L"SeamlessSoundManagerMsg";
static HANDLE g_uiThread, g_uiReady;
static DWORD g_uiTid;

static DWORD WINAPI UiThread(LPVOID) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    EnableDarkMenus();
    g_inst = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
    WNDCLASSW wc{};
    wc.lpfnWndProc = MsgWndProc;
    wc.hInstance = g_inst;
    wc.lpszClassName = kMsgClass;
    RegisterClassW(&wc);
    g_msgWnd = CreateWindowExW(WS_EX_TOOLWINDOW, kMsgClass, L"Seamless Sound Manager", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, g_inst, nullptr);
    if (g_msgWnd) {
        g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
        ChangeWindowMessageFilterEx(g_msgWnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
        UpdateTray(true);
    }
    SetEvent(g_uiReady);
    if (g_msgWnd) {
        while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    if (g_trayAdded) {
        NOTIFYICONDATAW nid{};
        nid.cbSize = sizeof(nid);
        nid.hWnd = g_msgWnd;
        nid.uID = kTrayId;
        Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
    HWND w = g_msgWnd;
    g_msgWnd = nullptr;
    if (w) DestroyWindow(w);
    UnregisterClassW(kMsgClass, g_inst);
    CoUninitialize();
    return 0;
}

// ---------------------------------------------------------------------------
// Start and stop
// ---------------------------------------------------------------------------

static HANDLE g_singleInstance;

// ---------------------------------------------------------------------------------------------
// Menu room: shared by Seamless Flyouts and the tool mods' menu look.
// - Every popup menu window in this process is caught as it is created, title bar (system)
//   menus included, which never pass through TrackPopupMenu.
// - Menus that Windows draws get 2 px more frame on every side, so the hover has the same room
//   from the border as in Explorer's own desktop menu (4 px at the sides, 6 px top and bottom).
//   Menus with owner-drawn rows (Explorer) already have it and are left alone.
// - A submenu opens touching its parent, and while the pointer heads for an open submenu the
//   parent ignores it, so rows crossed on the way don't swap the submenu (released after a
//   short rest, so stopping on a row still opens that row).
// - A menu too tall for its monitor gets shorter rows while it is open, so the last item
//   shows without scroll arrows. Windows reads row spacing once per process, so the spacing is
//   reloaded (FlushMenuThemes) when such a menu opens and again when the menu closes.
// ---------------------------------------------------------------------------------------------
#include <algorithm>
#include <atomic>
#include <mutex>
#include <vector>
#include <commctrl.h>

namespace SeamlessMenuRoom {

constexpr UINT_PTR kRoomId = 0x6D55;
constexpr INT kRowMargin = 8;                  // row top and bottom margin of the menu look
constexpr INT kMinRowMargin = 2;
static const WCHAR* const kPadProp = L"SeamlessMenuRoomPad";
static const WCHAR* const kSizeProp = L"SeamlessMenuRoomSize";
static const WCHAR* const kSeqProp = L"SeamlessMenuRoomSeq";   // creation order of menu windows
constexpr UINT kAimHoldMs = 250;               // how long the pointer may rest before a held move counts

static std::atomic<INT> g_rowMargin{kRowMargin};
static HWINEVENTHOOK g_createHook = nullptr, g_menuHook = nullptr;
static VOID (*g_onCreate)(HWND) = nullptr;
using Flush_t = VOID(WINAPI*)();
static Flush_t g_flush = nullptr;
static thread_local HHOOK t_loopHook = nullptr;
static thread_local INT t_trackDepth = 0;
static thread_local BOOL t_menuMode = FALSE;
static std::atomic<ULONG> g_seq{0};
static thread_local HHOOK t_aimHook = nullptr;
static thread_local POINT t_apex = {LONG_MIN, LONG_MIN};
static thread_local MSG t_held = {};
static thread_local UINT_PTR t_aimTimer = 0;
static thread_local DWORD t_holdStart = 0;
constexpr DWORD kAimMaxMs = 700;               // a hold never lasts longer than this

// Row top and bottom margin to report for Menu part 27 / POPUPITEM, property 10000.
static INT RowMargin() { return g_rowMargin.load(); }

static UINT DpiOf(HWND h)
{
    UINT d = h ? GetDpiForWindow(h) : 0;
    if (!d) d = GetDpiForSystem();
    return d ? d : USER_DEFAULT_SCREEN_DPI;
}

static BOOL IsPopupMenuWindow(HWND h)
{
    WCHAR cls[16];
    return h && GetClassNameW(h, cls, ARRAYSIZE(cls)) && wcscmp(cls, L"#32768") == 0;
}

static BOOL HasOwnerDraw(HMENU m)
{
    INT n = GetMenuItemCount(m);
    for (INT i = 0; i < n; i++) {
        MENUITEMINFOW mii = {sizeof(mii), MIIM_FTYPE};
        if (GetMenuItemInfoW(m, i, TRUE, &mii) && (mii.fType & MFT_OWNERDRAW)) return TRUE;
    }
    return FALSE;
}

// The nearest visible menu window of this thread made before (parent) or after (child) h.
struct RelativeFind { HWND self; ULONG_PTR seq; BOOL child; HWND best; ULONG_PTR bestSeq; };
static BOOL CALLBACK FindRelative(HWND h, LPARAM l)
{
    auto* f = reinterpret_cast<RelativeFind*>(l);
    if (h == f->self || !IsWindowVisible(h) || !IsPopupMenuWindow(h)) return TRUE;
    ULONG_PTR s = (ULONG_PTR)GetPropW(h, kSeqProp);
    if (!s) return TRUE;
    BOOL better = f->child ? (s > f->seq && (!f->best || s < f->bestSeq))
                           : (s < f->seq && (!f->best || s > f->bestSeq));
    if (better) { f->best = h; f->bestSeq = s; }
    return TRUE;
}
static HWND RelativeMenu(HWND h, BOOL child)
{
    RelativeFind f = {h, (ULONG_PTR)GetPropW(h, kSeqProp), child, nullptr, 0};
    if (!f.seq) return nullptr;
    EnumThreadWindows(GetCurrentThreadId(), FindRelative, reinterpret_cast<LPARAM>(&f));
    return f.best;
}

// Pull a submenu in so it touches its parent (never pushes it further away or off screen).
static VOID SnapToParent(HWND h, WINDOWPOS* wp)
{
    HWND parent = RelativeMenu(h, FALSE);
    RECT pr;
    if (!parent || !GetWindowRect(parent, &pr)) return;
    INT cx = wp->cx;
    if ((wp->flags & SWP_NOSIZE) || cx <= 0) {
        RECT r;
        if (!GetWindowRect(h, &r)) return;
        cx = r.right - r.left;
    }
    LONG mid = (pr.left + pr.right) / 2;
    if (wp->x >= mid) {
        if (pr.right < wp->x) wp->x = pr.right;
    } else if (wp->x + cx <= mid) {
        if (pr.left - cx > wp->x) wp->x = pr.left - cx;
    }
}

static BOOL InTriangle(POINT p, POINT a, POINT b, POINT c)
{
    auto side = [](POINT o, POINT u, POINT v) {
        return (LONGLONG)(u.x - o.x) * (v.y - o.y) - (LONGLONG)(u.y - o.y) * (v.x - o.x);
    };
    LONGLONG d1 = side(p, a, b), d2 = side(p, b, c), d3 = side(p, c, a);
    BOOL neg = d1 < 0 || d2 < 0 || d3 < 0, pos = d1 > 0 || d2 > 0 || d3 > 0;
    return !(neg && pos);
}

static VOID DropHeld()
{
    if (t_aimTimer) KillTimer(nullptr, t_aimTimer);
    t_aimTimer = 0;
    t_held = {};
}

// The pointer rested: let the last held move through, from where it stopped. The timer has no
// callback (a pending one could outlive the mod's unload); AimProc sees its WM_TIMER.
static VOID AimRelease()
{
    MSG m = t_held;
    DropHeld();
    if (m.hwnd && IsWindow(m.hwnd)) {
        t_apex = m.pt;
        PostMessageW(m.hwnd, m.message, m.wParam, m.lParam);
    }
}

// TRUE: hold this move, the pointer is on its way to the open submenu.
static BOOL HoldForSubmenu(const MSG* m)
{
    POINT p = m->pt;
    HWND under = WindowFromPoint(p);
    HWND sub = nullptr;
    if (under && IsPopupMenuWindow(under) && GetWindowThreadProcessId(under, nullptr) == GetCurrentThreadId())
        sub = RelativeMenu(under, TRUE);
    RECT sr, pr;
    if (!sub || !GetWindowRect(sub, &sr) || !GetWindowRect(under, &pr) || t_apex.x == LONG_MIN ||
        (p.x == t_apex.x && p.y == t_apex.y)) {
        DropHeld();
        t_apex = p;
        return FALSE;
    }
    LONG edge = sr.left >= (pr.left + pr.right) / 2 ? sr.left : sr.right;
    INT slack = MulDiv(6, DpiOf(under), USER_DEFAULT_SCREEN_DPI);
    POINT b = {edge, sr.top - slack}, c = {edge, sr.bottom + slack};
    if (!InTriangle(p, t_apex, b, c)) {
        DropHeld();
        t_apex = p;
        return FALSE;
    }
    if (!t_held.hwnd) t_holdStart = GetTickCount();
    else if (GetTickCount() - t_holdStart > kAimMaxMs) {
        DropHeld();
        t_apex = p;
        return FALSE;
    }
    t_held = *m;
    if (t_aimTimer) KillTimer(nullptr, t_aimTimer);
    t_aimTimer = SetTimer(nullptr, 0, kAimHoldMs, nullptr);
    if (!t_aimTimer) { t_held = {}; t_apex = p; return FALSE; }
    return TRUE;
}

static LRESULT CALLBACK AimProc(INT code, WPARAM w, LPARAM l)
{
    if (code == MSGF_MENU && l) {
        auto* m = reinterpret_cast<MSG*>(l);
        if (m->message == WM_TIMER && !m->hwnd && t_aimTimer && m->wParam == t_aimTimer) {
            AimRelease();
            return TRUE;
        }
        if (m->message == WM_MOUSEMOVE || m->message == WM_NCMOUSEMOVE) {
            if (HoldForSubmenu(m)) return TRUE;
        } else if ((m->message >= WM_LBUTTONDOWN && m->message <= WM_MBUTTONDBLCLK) ||
                   (m->message >= WM_NCLBUTTONDOWN && m->message <= WM_NCMBUTTONDBLCLK) ||
                   m->message == WM_KEYDOWN) {
            DropHeld();
            t_apex = {LONG_MIN, LONG_MIN};
        }
    }
    return CallNextHookEx(nullptr, code, w, l);
}

static LRESULT CALLBACK RoomProc(HWND h, UINT msg, WPARAM w, LPARAM l, UINT_PTR, DWORD_PTR)
{
    if (msg == WM_WINDOWPOSCHANGING && l) {
        auto* wp = reinterpret_cast<WINDOWPOS*>(l);
        // Grow only the size Windows asks for, never a size this proc already produced.
        if (!(wp->flags & SWP_NOSIZE) && wp->cx > 0 && wp->cy > 0 &&
            (DWORD)MAKELONG(wp->cx, wp->cy) != (DWORD)(ULONG_PTR)GetPropW(h, kSizeProp)) {
            HMENU m = (HMENU)SendMessageW(h, MN_GETHMENU, 0, 0);
            INT pad = (m && !HasOwnerDraw(m)) ? MulDiv(2, DpiOf(h), USER_DEFAULT_SCREEN_DPI) : 0;
            SetPropW(h, kPadProp, (HANDLE)(INT_PTR)pad);
            if (pad) {
                wp->cx += 2 * pad;
                wp->cy += 2 * pad;
                if (!(wp->flags & SWP_NOMOVE)) {
                    RECT r = {wp->x, wp->y, wp->x + wp->cx, wp->y + wp->cy};
                    MONITORINFO mi = {sizeof(mi)};
                    if (GetMonitorInfoW(MonitorFromRect(&r, MONITOR_DEFAULTTONEAREST), &mi)) {
                        if (r.right > mi.rcMonitor.right) wp->x = std::max(mi.rcMonitor.left, wp->x - (r.right - mi.rcMonitor.right));
                        if (r.bottom > mi.rcMonitor.bottom) wp->y = std::max(mi.rcMonitor.top, wp->y - (r.bottom - mi.rcMonitor.bottom));
                    }
                }
            }
            SetPropW(h, kSizeProp, (HANDLE)(ULONG_PTR)(DWORD)MAKELONG(wp->cx, wp->cy));
        }
        if (!(wp->flags & SWP_NOMOVE)) SnapToParent(h, wp);
    }
    if (msg == WM_NCDESTROY) {
        RemovePropW(h, kPadProp);
        RemovePropW(h, kSizeProp);
        RemovePropW(h, kSeqProp);
        RemoveWindowSubclass(h, RoomProc, kRoomId);
        return DefSubclassProc(h, msg, w, l);
    }
    LRESULT result = DefSubclassProc(h, msg, w, l);
    if (msg == WM_NCCALCSIZE && l) {
        INT pad = (INT)(INT_PTR)GetPropW(h, kPadProp);
        if (pad > 0) InflateRect(reinterpret_cast<RECT*>(l), -pad, -pad);
    }
    return result;
}

static VOID ResetRows()
{
    if (g_rowMargin.exchange(kRowMargin) != kRowMargin && g_flush) g_flush();
}

// Picks the largest row margin (8 down to 2) at which the whole menu fits its monitor.
static VOID FitMenu(HMENU m, HWND owner)
{
    if (!m || !g_flush || HasOwnerDraw(m)) return;
    INT rows = 0, seps = 0, n = GetMenuItemCount(m);
    for (INT i = 0; i < n; i++) {
        MENUITEMINFOW mii = {sizeof(mii), MIIM_FTYPE};
        if (!GetMenuItemInfoW(m, i, TRUE, &mii)) continue;
        (mii.fType & MFT_SEPARATOR) ? seps++ : rows++;
    }
    MONITORINFO mi = {sizeof(mi)};
    if (!rows || !GetMonitorInfoW(MonitorFromWindow(owner, MONITOR_DEFAULTTONEAREST), &mi)) return;
    UINT dpi = DpiOf(owner);
    auto px = [dpi](INT v) { return MulDiv(v, dpi, USER_DEFAULT_SCREEN_DPI); };
    INT avail = mi.rcWork.bottom - mi.rcWork.top - px(8);
    INT pick = kRowMargin;
    for (; pick > kMinRowMargin; pick--) {
        INT cut = px(2 * (kRowMargin - pick));   // rows measure 33 px and separators 21 px at margin 8
        if (rows * (px(33) - cut) + seps * (px(21) - cut) + px(10) <= avail) break;
    }
    if (pick < g_rowMargin.load()) {
        g_rowMargin = pick;
        g_flush();
    }
}

static LRESULT CALLBACK LoopProc(INT code, WPARAM w, LPARAM l)
{
    if (code == HC_ACTION && l) {
        auto* c = reinterpret_cast<CWPSTRUCT*>(l);
        if (c->message == WM_INITMENUPOPUP) FitMenu((HMENU)c->wParam, c->hwnd);
        else if (c->message == WM_EXITMENULOOP) ResetRows();
    }
    return CallNextHookEx(nullptr, code, w, l);
}
// Every live loop hook, so Uninit can remove the ones other threads still hold.
static std::mutex g_hooksLock;
static std::vector<HHOOK> g_hooks;
static VOID SyncLoopHook()
{
    BOOL want = t_trackDepth > 0 || t_menuMode;
    if (want && !t_loopHook) {
        t_loopHook = SetWindowsHookExW(WH_CALLWNDPROC, LoopProc, nullptr, GetCurrentThreadId());
        if (t_loopHook) { std::lock_guard<std::mutex> g(g_hooksLock); g_hooks.push_back(t_loopHook); }
    } else if (!want && t_loopHook) {
        {
            std::lock_guard<std::mutex> g(g_hooksLock);
            auto it = std::find(g_hooks.begin(), g_hooks.end(), t_loopHook);
            if (it != g_hooks.end()) { g_hooks.erase(it); UnhookWindowsHookEx(t_loopHook); }
        }
        t_loopHook = nullptr;
        ResetRows();
    }
    if (want && !t_aimHook) {
        t_apex = {LONG_MIN, LONG_MIN};
        t_aimHook = SetWindowsHookExW(WH_MSGFILTER, AimProc, nullptr, GetCurrentThreadId());
        if (t_aimHook) { std::lock_guard<std::mutex> g(g_hooksLock); g_hooks.push_back(t_aimHook); }
    } else if (!want && t_aimHook) {
        {
            std::lock_guard<std::mutex> g(g_hooksLock);
            auto it = std::find(g_hooks.begin(), g_hooks.end(), t_aimHook);
            if (it != g_hooks.end()) { g_hooks.erase(it); UnhookWindowsHookEx(t_aimHook); }
        }
        t_aimHook = nullptr;
        DropHeld();
    }
}

// Wrap TrackPopupMenu(Ex) with these (menu-bar menus are covered by the menu events).
static VOID BeginTrack() { t_trackDepth++; SyncLoopHook(); }
static VOID EndTrack() { if (t_trackDepth > 0) t_trackDepth--; SyncLoopHook(); }

static VOID CALLBACK OnEvent(HWINEVENTHOOK, DWORD ev, HWND h, LONG obj, LONG child, DWORD, DWORD)
{
    if (ev == EVENT_OBJECT_CREATE) {
        if (obj != OBJID_WINDOW || child != CHILDID_SELF || !IsPopupMenuWindow(h) ||
            GetWindowThreadProcessId(h, nullptr) != GetCurrentThreadId())
            return;
        SetPropW(h, kSeqProp, (HANDLE)(ULONG_PTR)++g_seq);
        if (g_onCreate) g_onCreate(h);
        SetWindowSubclass(h, RoomProc, kRoomId, 0);
    } else if (ev == EVENT_SYSTEM_MENUSTART) {
        t_menuMode = TRUE;
        SyncLoopHook();
    } else if (ev == EVENT_SYSTEM_MENUEND) {
        t_menuMode = FALSE;
        SyncLoopHook();
    }
}

// onCreate (optional) runs for each new popup menu window, on its own thread, after creation.
static VOID Init(VOID (*onCreate)(HWND))
{
    g_onCreate = onCreate;
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    g_flush = ux ? (Flush_t)GetProcAddress(ux, MAKEINTRESOURCEA(136)) : nullptr;
    HMODULE self = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<LPCWSTR>(&OnEvent), &self);
    DWORD pid = GetCurrentProcessId();
    g_createHook = SetWinEventHook(EVENT_OBJECT_CREATE, EVENT_OBJECT_CREATE, self, OnEvent, pid, 0, WINEVENT_INCONTEXT);
    g_menuHook = SetWinEventHook(EVENT_SYSTEM_MENUSTART, EVENT_SYSTEM_MENUEND, self, OnEvent, pid, 0, WINEVENT_INCONTEXT);
}

static VOID Uninit()
{
    for (HWINEVENTHOOK* hk : {&g_createHook, &g_menuHook})
        if (*hk) { UnhookWinEvent(*hk); *hk = nullptr; }
    {
        std::lock_guard<std::mutex> g(g_hooksLock);
        for (HHOOK hk : g_hooks) UnhookWindowsHookEx(hk);
        g_hooks.clear();
    }
    ResetRows();
}

}  // namespace SeamlessMenuRoom
// ---------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------
// Seamless menu look for this mod's own menus.
// Windhawk runs tool mods in their own process, where Seamless Flyouts cannot reach, so the
// menus this mod shows get the same look here: blurred Catppuccin Mocha body, rounded corners,
// roomy rows, separators that run to the border, the blue to mauve hover pill, and
// submenus that open beside their parent with a small gap. Only this process is touched.
// ---------------------------------------------------------------------------------------------
#include <d2d1.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <vssym32.h>
#include <commctrl.h>

// ---------------------------------------------------------------------------------------------
// Menu pill: the one hover look for every menu row, the same pill Seamless Clipboard Manager
// draws: a soft blue to mauve fill (16 %) and a 1 px blue to mauve ring (80 %), radius 8.
// Drawn at the row's real size each time, because a stretched nine-grid can't hold a gradient.
// ---------------------------------------------------------------------------------------------
namespace SeamlessMenuPill {

static BOOL Draw(ID2D1Factory* factory, HDC hdc, const RECT& r, UINT dpi)
{
    INT w = r.right - r.left, h = r.bottom - r.top;
    if (!factory || !hdc || w <= 2 || h <= 2) return FALSE;
    HDC dc = CreateCompatibleDC(hdc);
    if (!dc) return FALSE;
    BITMAPINFO bmi = {};
    bmi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB};
    VOID* bits = nullptr;
    HBITMAP bmp = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!bmp) { DeleteDC(dc); return FALSE; }
    HGDIOBJ old = SelectObject(dc, bmp);
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_SOFTWARE,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0,
        D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE, D2D1_FEATURE_LEVEL_DEFAULT);
    ID2D1DCRenderTarget* rt = nullptr;
    RECT rc = {0, 0, w, h};
    BOOL ok = FALSE;
    if (SUCCEEDED(factory->CreateDCRenderTarget(&props, &rt)) && SUCCEEDED(rt->BindDC(dc, &rc))) {
        FLOAT s = (dpi ? dpi : USER_DEFAULT_SCREEN_DPI) / (FLOAT)USER_DEFAULT_SCREEN_DPI;
        FLOAT ringW = s < 1.5f ? 1.f : 2.f;
        FLOAT rad = std::min(8.f * s, std::min((FLOAT)w, (FLOAT)h) / 2.f);
        D2D1_ROUNDED_RECT rr = {{ringW / 2, ringW / 2, w - ringW / 2, h - ringW / 2}, rad, rad};
        auto gradient = [&](FLOAT a) {
            ID2D1LinearGradientBrush* brush = nullptr;
            ID2D1GradientStopCollection* stops = nullptr;
            D2D1_GRADIENT_STOP st[2] = {{0.f, {137 / 255.f, 180 / 255.f, 250 / 255.f, a}},
                                        {1.f, {203 / 255.f, 166 / 255.f, 247 / 255.f, a}}};
            if (SUCCEEDED(rt->CreateGradientStopCollection(st, 2, &stops)))
                rt->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties({0, 0}, {(FLOAT)w, (FLOAT)h}),
                                              stops, &brush);
            if (stops) stops->Release();
            return brush;
        };
        rt->BeginDraw();
        rt->Clear({0, 0, 0, 0});
        ID2D1LinearGradientBrush* fill = gradient(0.16f);
        ID2D1LinearGradientBrush* ring = gradient(0.8f);
        if (fill) rt->FillRoundedRectangle(&rr, fill);
        if (ring) rt->DrawRoundedRectangle(&rr, ring, ringW);
        ok = SUCCEEDED(rt->EndDraw()) && fill && ring;
        if (fill) fill->Release();
        if (ring) ring->Release();
    }
    if (rt) rt->Release();
    if (ok) {
        BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
        ok = GdiAlphaBlend(hdc, r.left, r.top, w, h, dc, 0, 0, w, h, bf);
    }
    SelectObject(dc, old);
    DeleteObject(bmp);
    DeleteDC(dc);
    return ok;
}

}  // namespace SeamlessMenuPill

namespace SeamlessMenuSkin {

constexpr COLORREF kMenuTint = 0xA01B1111;        // Seamless Flyouts "MenuBlur" A011111B
constexpr UINT_PTR kSubclassId = 0x6D54;
constexpr UINT kAccentAcrylic = 4, kWcaAccentPolicy = 19;

struct AccentPolicy { DWORD state, flags, color, animation; };
struct CompositionData { DWORD attrib; PVOID data; SIZE_T size; };
using SetWca_t = BOOL(WINAPI*)(HWND, CompositionData*);
using GetThemeClass_t = HRESULT(WINAPI*)(HTHEME, LPWSTR, INT);

static ID2D1Factory* g_factory = nullptr;
static HDC g_hoverDC = nullptr, g_sepDC = nullptr;
static UINT g_edgesMsg = 0;

static decltype(&DrawThemeBackground) DrawThemeBackground_orig = nullptr;
static decltype(&DrawThemeBackgroundEx) DrawThemeBackgroundEx_orig = nullptr;
static decltype(&GetThemeColor) GetThemeColor_orig = nullptr;
static decltype(&GetThemeMargins) GetThemeMargins_orig = nullptr;
static decltype(&GetThemeFont) GetThemeFont_orig = nullptr;
static decltype(&DwmSetWindowAttribute) DwmSetWindowAttribute_orig = nullptr;
static decltype(&TrackPopupMenu) TrackPopupMenu_orig = nullptr;
static decltype(&TrackPopupMenuEx) TrackPopupMenuEx_orig = nullptr;

static UINT Dpi() { UINT d = GetDpiForSystem(); return d ? d : USER_DEFAULT_SCREEN_DPI; }

static BOOL IsMenuWindow(HWND hWnd)
{
    WCHAR cls[16];
    return hWnd && GetClassNameW(hWnd, cls, ARRAYSIZE(cls)) && wcscmp(cls, L"#32768") == 0;
}

static BOOL IsMenuTheme(HTHEME hTheme)
{
    static auto getClass = (GetThemeClass_t)GetProcAddress(GetModuleHandleW(L"uxtheme.dll"), MAKEINTRESOURCEA(74));
    WCHAR buf[64] = {};
    return getClass && SUCCEEDED(getClass(hTheme, buf, ARRAYSIZE(buf))) && wcscmp(buf, L"Menu") == 0;
}

static D2D1_COLOR_F Argb(BYTE a, BYTE r, BYTE g, BYTE b) { return {r / 255.f, g / 255.f, b / 255.f, a / 255.f}; }

// A small premultiplied 32-bit bitmap drawn once with Direct2D and stretched as a nine-grid.
static HDC MakeCache(INT w, INT h, BOOL separator)
{
    if (!g_factory) return nullptr;
    HDC dc = CreateCompatibleDC(nullptr);
    if (!dc) return nullptr;
    BITMAPINFO bmi = {};
    bmi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB};
    VOID* bits = nullptr;
    HBITMAP bmp = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!bmp) { DeleteDC(dc); return nullptr; }
    SelectObject(dc, bmp);
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_SOFTWARE,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0,
        D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE, D2D1_FEATURE_LEVEL_DEFAULT);
    ID2D1DCRenderTarget* rt = nullptr;
    RECT rc = {0, 0, w, h};
    if (FAILED(g_factory->CreateDCRenderTarget(&props, &rt)) || FAILED(rt->BindDC(dc, &rc))) {
        if (rt) rt->Release();
        DeleteDC(dc); DeleteObject(bmp);
        return nullptr;
    }
    ID2D1SolidColorBrush *a = nullptr, *b = nullptr;
    rt->BeginDraw();
    if (separator) {
        rt->CreateSolidColorBrush(Argb(255, 69, 71, 90), &a);
        if (a) rt->DrawLine({0, h / 2.f}, {(FLOAT)w, h / 2.f}, a);
    } else {
        auto r = D2D1::RoundedRect(D2D1::RectF(0.5f, 0.5f, w - 0.5f, h - 0.5f), 6.f, 6.f);
        rt->CreateSolidColorBrush(Argb(190, 69, 71, 90), &a);
        rt->CreateSolidColorBrush(Argb(255, 137, 180, 250), &b);
        if (a) rt->FillRoundedRectangle(&r, a);
        if (b) rt->DrawRoundedRectangle(&r, b, 1.f);
    }
    HRESULT hr = rt->EndDraw();
    if (a) a->Release();
    if (b) b->Release();
    rt->Release();
    if (FAILED(hr)) { DeleteDC(dc); DeleteObject(bmp); return nullptr; }
    return dc;
}

static VOID Blend(HDC dst, INT x, INT y, INT w, INT h, HDC src, INT sx, INT sy, INT sw, INT sh)
{
    if (w <= 0 || h <= 0 || sw <= 0 || sh <= 0) return;
    BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    GdiAlphaBlend(dst, x, y, w, h, src, sx, sy, sw, sh, bf);
}

static VOID NineGrid(HDC hdc, HDC src, const RECT* d, INT l, INT t, INT r, INT b)
{
    BITMAP bm = {};
    GetObject(GetCurrentObject(src, OBJ_BITMAP), sizeof(bm), &bm);
    INT sw = bm.bmWidth, sh = bm.bmHeight, dw = d->right - d->left, dh = d->bottom - d->top;
    l = std::min(l, dw); r = std::min(r, dw - l); t = std::min(t, dh); b = std::min(b, dh - t);
    if (l + r >= sw || t + b >= sh) { Blend(hdc, d->left, d->top, dw, dh, src, 0, 0, sw, sh); return; }
    INT cw = dw - l - r, ch = dh - t - b, scw = sw - l - r, sch = sh - t - b;
    Blend(hdc, d->left + l, d->top + t, cw, ch, src, l, t, scw, sch);
    Blend(hdc, d->left, d->top, l, t, src, 0, 0, l, t);
    Blend(hdc, d->left + l, d->top, cw, t, src, l, 0, scw, t);
    Blend(hdc, d->right - r, d->top, r, t, src, sw - r, 0, r, t);
    Blend(hdc, d->left, d->top + t, l, ch, src, 0, t, l, sch);
    Blend(hdc, d->right - r, d->top + t, r, ch, src, sw - r, t, r, sch);
    Blend(hdc, d->left, d->bottom - b, l, b, src, 0, sh - b, l, b);
    Blend(hdc, d->left + l, d->bottom - b, cw, b, src, l, sh - b, scw, b);
    Blend(hdc, d->right - r, d->bottom - b, r, b, src, sw - r, sh - b, r, b);
}

static VOID ApplyEffects(HWND hWnd)
{
    static auto setWca = (SetWca_t)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    BOOL dark = TRUE;
    DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof(dark));
    DWM_BLURBEHIND bb = {DWM_BB_ENABLE | DWM_BB_BLURREGION | DWM_BB_TRANSITIONONMAXIMIZED, TRUE, CreateRectRgn(0, 0, -1, -1), TRUE};
    DwmEnableBlurBehindWindow(hWnd, &bb);
    DeleteObject(bb.hRgnBlur);
    AccentPolicy ap = {kAccentAcrylic, 0, kMenuTint, 0};
    CompositionData data = {kWcaAccentPolicy, &ap, sizeof(ap)};
    if (setWca) setWca(hWnd, &data);
    UINT corner = DWMWCP_ROUND;
    DwmSetWindowAttribute(hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, &corner, sizeof(corner));
}

// Separator lines stop at the client edge; copy each one across the thin menu frame so it
// meets the border.
static BOOL IsSeparatorPixel(COLORREF c)
{
    return abs(GetRValue(c) - 69) <= 8 && abs(GetGValue(c) - 71) <= 8 && abs(GetBValue(c) - 90) <= 8;
}
static VOID PaintSeparatorEdges(HWND hWnd)
{
    if (!g_sepDC || !IsWindowVisible(hWnd)) return;
    HMENU hMenu = (HMENU)SendMessageW(hWnd, MN_GETHMENU, 0, 0);
    if (!hMenu) return;
    RECT wr, cr;
    GetWindowRect(hWnd, &wr);
    GetClientRect(hWnd, &cr);
    POINT org = {0, 0};
    ClientToScreen(hWnd, &org);
    INT cl = org.x - wr.left, cw = cr.right, winW = wr.right - wr.left;
    if (cl <= 0 || cw <= 0) return;
    HDC wdc = GetWindowDC(hWnd);
    if (!wdc) return;
    INT count = GetMenuItemCount(hMenu);
    for (INT i = 0; i < count; i++) {
        MENUITEMINFOW mii = {sizeof(mii), MIIM_FTYPE};
        if (!GetMenuItemInfoW(hMenu, i, TRUE, &mii) || !(mii.fType & MFT_SEPARATOR)) continue;
        RECT ir;
        if (!GetMenuItemRect(hWnd, hMenu, i, &ir)) continue;
        for (INT y = ir.top - wr.top; y < ir.bottom - wr.top; y++) {
            if (!IsSeparatorPixel(GetPixel(wdc, cl, y)) || !IsSeparatorPixel(GetPixel(wdc, cl + cw - 1, y))) continue;
            RECT left = {0, y - 2, cl, y + 3}, right = {cl + cw, y - 2, winW, y + 3};
            NineGrid(wdc, g_sepDC, &left, 0, 5, 0, 0);
            NineGrid(wdc, g_sepDC, &right, 0, 5, 0, 0);
        }
    }
    ReleaseDC(hWnd, wdc);
}

struct ParentSearch { HWND self; RECT r; HWND parent; RECT pr; BOOL right; };
static BOOL CALLBACK FindParent(HWND hWnd, LPARAM lParam)
{
    auto* f = reinterpret_cast<ParentSearch*>(lParam);
    if (hWnd == f->self || !IsWindowVisible(hWnd) || !IsMenuWindow(hWnd)) return TRUE;
    RECT p;
    GetWindowRect(hWnd, &p);
    if (f->r.top >= p.bottom || f->r.bottom <= p.top) return TRUE;
    BOOL right = f->r.left > p.left && f->r.left < p.right + 2 && f->r.right > p.right;
    BOOL left = f->r.right < p.right && f->r.right > p.left - 2 && f->r.left < p.left;
    if (!right && !left) return TRUE;
    f->parent = hWnd; f->pr = p; f->right = right;
    return FALSE;
}
// Submenus open over the parent's edge; move them beside it with an 8 px gap.
static VOID PlaceSubmenu(HWND hWnd, WINDOWPOS* wp)
{
    RECT cur;
    GetWindowRect(hWnd, &cur);
    INT w = (wp->flags & SWP_NOSIZE) ? cur.right - cur.left : wp->cx;
    INT h = (wp->flags & SWP_NOSIZE) ? cur.bottom - cur.top : wp->cy;
    if (w <= 0 || h <= 0) return;
    ParentSearch f = {hWnd, {wp->x, wp->y, wp->x + w, wp->y + h}, nullptr, {}, FALSE};
    EnumThreadWindows(GetCurrentThreadId(), FindParent, reinterpret_cast<LPARAM>(&f));
    if (!f.parent) return;
    UINT dpi = GetDpiForWindow(hWnd);
    INT gap = MulDiv(8, dpi ? dpi : Dpi(), USER_DEFAULT_SCREEN_DPI);
    MONITORINFO mi = {sizeof(mi)};
    if (!GetMonitorInfoW(MonitorFromRect(&f.pr, MONITOR_DEFAULTTONEAREST), &mi)) return;
    INT toRight = f.pr.right + gap, toLeft = f.pr.left - gap - w;
    if (f.right)
        wp->x = (toRight + w <= mi.rcWork.right) ? toRight : (toLeft >= mi.rcWork.left ? toLeft : wp->x);
    else
        wp->x = (toLeft >= mi.rcWork.left) ? toLeft : (toRight + w <= mi.rcWork.right ? toRight : wp->x);
}

static LRESULT CALLBACK MenuProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR)
{
    if (msg == g_edgesMsg && g_edgesMsg) { PaintSeparatorEdges(hWnd); return 0; }
    if (msg == WM_TIMER && wParam == kSubclassId) {
        KillTimer(hWnd, kSubclassId);
        PaintSeparatorEdges(hWnd);
        return 0;
    }
    if (msg == WM_NCDESTROY) {
        KillTimer(hWnd, kSubclassId);
        RemoveWindowSubclass(hWnd, MenuProc, kSubclassId);
        return DefSubclassProc(hWnd, msg, wParam, lParam);
    }
    if (msg == WM_WINDOWPOSCHANGING && lParam && !(reinterpret_cast<WINDOWPOS*>(lParam)->flags & SWP_NOMOVE))
        PlaceSubmenu(hWnd, reinterpret_cast<WINDOWPOS*>(lParam));
    if (msg == WM_NCPAINT)
        ApplyEffects(hWnd);
    LRESULT result = DefSubclassProc(hWnd, msg, wParam, lParam);
    if (msg == WM_CREATE)
        ApplyEffects(hWnd);
    if (msg == WM_NCPAINT || msg == WM_PAINT)
        PostMessageW(hWnd, g_edgesMsg, 0, 0);
    if (msg == WM_WINDOWPOSCHANGED && lParam && (reinterpret_cast<WINDOWPOS*>(lParam)->flags & SWP_SHOWWINDOW)) {
        PostMessageW(hWnd, g_edgesMsg, 0, 0);
        SetTimer(hWnd, kSubclassId, 150, nullptr);
    }
    return result;
}

// Every popup menu window of this process, title bar menus included (those never pass
// through TrackPopupMenu, so they used to keep a black, unblurred body).
static VOID OnMenuCreated(HWND hWnd)
{
    // The CBT hook and the create-event hook can both reach this window.
    static const WCHAR* const kSkinProp = L"SeamlessMenuSkinAttached";
    if (GetPropW(hWnd, kSkinProp)) return;
    SetPropW(hWnd, kSkinProp, (HANDLE)1);
    SetWindowSubclass(hWnd, MenuProc, kSubclassId, 0);
    ApplyEffects(hWnd);
}

// Delivered synchronously on this thread during the menu window's creation, before
// its first paint, so the black body never shows without the acrylic behind it.
static LRESULT CALLBACK MenuCbtProc(INT code, WPARAM w, LPARAM l)
{
    if (code == HCBT_CREATEWND) {
        HWND created = reinterpret_cast<HWND>(w);
        WCHAR cls[16];
        if (GetClassNameW(created, cls, ARRAYSIZE(cls)) &&
            wcscmp(cls, L"#32768") == 0)
            OnMenuCreated(created);
    }
    return CallNextHookEx(nullptr, code, w, l);
}
static HHOOK InstallMenuCbtHook()
{
    return SetWindowsHookExW(WH_CBT, MenuCbtProc, nullptr, GetCurrentThreadId());
}

static BOOL WINAPI TrackPopupMenu_hook(HMENU m, UINT f, INT x, INT y, INT r, HWND h, const RECT* rc)
{
    SeamlessMenuRoom::BeginTrack();
    HHOOK cbt = InstallMenuCbtHook();
    BOOL ret = TrackPopupMenu_orig(m, f, x, y, r, h, rc);
    if (cbt) UnhookWindowsHookEx(cbt);
    SeamlessMenuRoom::EndTrack();
    return ret;
}
static BOOL WINAPI TrackPopupMenuEx_hook(HMENU m, UINT f, INT x, INT y, HWND h, LPTPMPARAMS p)
{
    SeamlessMenuRoom::BeginTrack();
    HHOOK cbt = InstallMenuCbtHook();
    BOOL ret = TrackPopupMenuEx_orig(m, f, x, y, h, p);
    if (cbt) UnhookWindowsHookEx(cbt);
    SeamlessMenuRoom::EndTrack();
    return ret;
}

// Returns TRUE when the menu part was drawn here.
static BOOL PaintMenuPart(HDC hdc, INT part, INT state, LPCRECT pRect, LPCRECT pClip)
{
    if (part == 26) { part = 27; state = 2; }                   // keyboard focus: same hover
    if ((part == 27 || part == MENU_POPUPITEM) && state == 2) {
        // Keep the same gap above and below as at the sides, so the first and last rows'
        // rounded hover stays clear of the menu's own rounded corners.
        RECT rc = *pRect;
        InflateRect(&rc, 0, -MulDiv(2, Dpi(), USER_DEFAULT_SCREEN_DPI));
        return SeamlessMenuPill::Draw(g_factory, hdc, rc, Dpi());
    }
    if (part == MENU_POPUPSEPARATOR) {
        if (!g_sepDC) g_sepDC = MakeCache(1, 5, TRUE);
        if (!g_sepDC) return FALSE;
        RECT rc = *pRect;
        INT reach = MulDiv(64, Dpi(), USER_DEFAULT_SCREEN_DPI);
        rc.left -= reach; rc.right += reach;
        NineGrid(hdc, g_sepDC, &rc, 1, 5, 0, 0);
        return TRUE;
    }
    if (part == MENU_POPUPBACKGROUND || part == MENU_POPUPBORDERS || part == MENU_POPUPGUTTER ||
        part == MENU_POPUPCHECKBACKGROUND || part == 27 || part == MENU_POPUPITEM) {
        RECT rc = *pRect;
        if (pClip) IntersectRect(&rc, pRect, pClip);
        FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));   // clear: the blur shows through
        return TRUE;
    }
    return FALSE;
}

static HRESULT WINAPI DrawThemeBackground_hook(HTHEME t, HDC hdc, INT part, INT state, LPCRECT r, LPCRECT clip)
{
    if (r && IsMenuTheme(t) && PaintMenuPart(hdc, part, state, r, clip)) return S_OK;
    return DrawThemeBackground_orig(t, hdc, part, state, r, clip);
}
static HRESULT WINAPI DrawThemeBackgroundEx_hook(HTHEME t, HDC hdc, INT part, INT state, LPCRECT r, const DTBGOPTS* o)
{
    LPCRECT clip = (o && (o->dwFlags & DTBG_CLIPRECT)) ? &o->rcClip : nullptr;
    if (r && IsMenuTheme(t) && PaintMenuPart(hdc, part, state, r, clip)) return S_OK;
    return DrawThemeBackgroundEx_orig(t, hdc, part, state, r, o);
}
static HRESULT WINAPI GetThemeColor_hook(HTHEME t, INT part, INT state, INT prop, COLORREF* c)
{
    HRESULT hr = GetThemeColor_orig(t, part, state, prop, c);
    if (!c || !IsMenuTheme(t)) return hr;
    if (prop == TMT_TEXTCOLOR && (part == MENU_POPUPITEM || part == 27) && state != 3 && state != 4) {
        *c = RGB(205, 214, 244);
        return S_OK;
    }
    if (prop == TMT_FILLCOLOR || prop == TMT_FILLCOLORHINT) { *c = RGB(0, 0, 0); return S_OK; }
    return hr;
}
static HRESULT WINAPI GetThemeMargins_hook(HTHEME t, HDC hdc, INT part, INT state, INT prop, LPRECT prc, MARGINS* m)
{
    HRESULT hr = GetThemeMargins_orig(t, hdc, part, state, prop, prc, m);
    if (m && IsMenuTheme(t) && (part == MENU_POPUPITEM || part == 27 || part == 26)) {
        if (prop == TMT_CONTENTMARGINS) *m = {2, 2, 8, 8};
        else if (prop == TMT_SIZINGMARGINS) *m = {10, 10, 10, 10};
        else if (prop == 10000) *m = {0, 0, SeamlessMenuRoom::RowMargin(), SeamlessMenuRoom::RowMargin()};
    }
    return hr;
}
static HRESULT WINAPI GetThemeFont_hook(HTHEME t, HDC hdc, INT part, INT state, INT prop, LOGFONTW* f)
{
    HRESULT hr = GetThemeFont_orig(t, hdc, part, state, prop, f);
    if (SUCCEEDED(hr) && f && prop == TMT_FONT && IsMenuTheme(t) && wcscmp(f->lfFaceName, L"Segoe UI") == 0) {
        wcscpy_s(f->lfFaceName, LF_FACESIZE, L"FiraCode Nerd Font Med");
        f->lfHeight = -MulDiv(14, Dpi(), USER_DEFAULT_SCREEN_DPI);
        f->lfWeight = 500;
        f->lfQuality = CLEARTYPE_QUALITY;
        f->lfPitchAndFamily = DEFAULT_PITCH;
    }
    return hr;
}
static HRESULT WINAPI DwmSetWindowAttribute_hook(HWND h, DWORD attr, LPCVOID v, DWORD cb)
{
    if (attr == DWMWA_WINDOW_CORNER_PREFERENCE && IsMenuWindow(h)) {
        UINT corner = DWMWCP_ROUND;
        return DwmSetWindowAttribute_orig(h, attr, &corner, sizeof(corner));
    }
    return DwmSetWindowAttribute_orig(h, attr, v, cb);
}

template <typename T>
static VOID Hook(HMODULE mod, LPCSTR name, T hook, T* orig)
{
    if (auto p = mod ? GetProcAddress(mod, name) : nullptr)
        Wh_SetFunctionHook((void*)p, (void*)hook, (void**)orig);
}

// Call from the mod's init, before it returns (hooks are applied when init finishes).
static VOID Init()
{
    D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory), nullptr, (void**)&g_factory);
    g_edgesMsg = RegisterWindowMessageW(L"SeamlessFlyouts_MenuSeparatorEdges");
    HMODULE ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    HMODULE dwm = LoadLibraryExW(L"dwmapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    HMODULE u32 = GetModuleHandleW(L"user32.dll");
    // Dark menus in this process (SetPreferredAppMode ForceDark, then FlushMenuThemes).
    using SetMode_t = INT(WINAPI*)(INT);
    using Flush_t = VOID(WINAPI*)();
    if (auto setMode = ux ? (SetMode_t)GetProcAddress(ux, MAKEINTRESOURCEA(135)) : nullptr) setMode(2);
    if (auto flush = ux ? (Flush_t)GetProcAddress(ux, MAKEINTRESOURCEA(136)) : nullptr) flush();
    Hook(ux, "DrawThemeBackground", DrawThemeBackground_hook, &DrawThemeBackground_orig);
    Hook(ux, "DrawThemeBackgroundEx", DrawThemeBackgroundEx_hook, &DrawThemeBackgroundEx_orig);
    Hook(ux, "GetThemeColor", GetThemeColor_hook, &GetThemeColor_orig);
    Hook(ux, "GetThemeMargins", GetThemeMargins_hook, &GetThemeMargins_orig);
    Hook(ux, "GetThemeFont", GetThemeFont_hook, &GetThemeFont_orig);
    Hook(dwm, "DwmSetWindowAttribute", DwmSetWindowAttribute_hook, &DwmSetWindowAttribute_orig);
    Hook(u32, "TrackPopupMenu", TrackPopupMenu_hook, &TrackPopupMenu_orig);
    Hook(u32, "TrackPopupMenuEx", TrackPopupMenuEx_hook, &TrackPopupMenuEx_orig);
    SeamlessMenuRoom::Init(OnMenuCreated);
}

static VOID Uninit()
{
    SeamlessMenuRoom::Uninit();
    for (HDC* dc : {&g_hoverDC, &g_sepDC})
        if (*dc) {
            HGDIOBJ bmp = GetCurrentObject(*dc, OBJ_BITMAP);
            DeleteDC(*dc);
            DeleteObject(bmp);
            *dc = nullptr;
        }
    if (g_factory) { g_factory->Release(); g_factory = nullptr; }
}

}  // namespace SeamlessMenuSkin

BOOL WhTool_ModInit() {
    SeamlessMenuSkin::Init();
    g_singleInstance = CreateMutexW(nullptr, FALSE, L"Local\\SeamlessSoundManagerRunning");
    if (!g_singleInstance || GetLastError() == ERROR_ALREADY_EXISTS) {
        if (g_singleInstance) CloseHandle(g_singleInstance);
        g_singleInstance = nullptr;
        Wh_Log(L"Already running");
        return FALSE;
    }
    g_stop = false;
    g_inst = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
    LoadSettings();
    LoadIniState();
    MigrateFromIni();
    {
        std::lock_guard<std::recursive_mutex> g(g_smLock);
        MakeDirs(MediaDir());
        WriteIniState();
    }
    g_uiReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_uiThread = CreateThread(nullptr, 0, UiThread, nullptr, 0, &g_uiTid);
    if (g_uiThread) WaitForSingleObject(g_uiReady, 10000);
    CloseHandle(g_uiReady);
    g_uiReady = nullptr;
    if (!g_uiThread || !g_msgWnd) {
        Wh_Log(L"Couldn't start");
        WhTool_ModUninit();
        return FALSE;
    }
    g_inboxStop = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_inboxThread = CreateThread(nullptr, 0, InboxThread, nullptr, 0, nullptr);
    g_sessionThread = CreateThread(nullptr, 0, SessionThread, nullptr, 0, nullptr);
    g_startThread = CreateThread(nullptr, 0, StartupThread, nullptr, 0, nullptr);
    Wh_Log(L"Started");
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (g_msgWnd) PostMessageW(g_msgWnd, WM_SM_SETTINGS, 0, 0);
}

static void JoinThread(HANDLE& h, DWORD ms, PCWSTR what) {
    if (!h) return;
    if (WaitForSingleObject(h, ms) != WAIT_OBJECT_0) Wh_Log(L"%s did not stop in time", what);
    CloseHandle(h);
    h = nullptr;
}

void WhTool_ModUninit() {
    SeamlessMenuSkin::Uninit();
    g_stop = true;
    smset::CloseSettingsWindow();
    PlaySoundW(nullptr, nullptr, 0);
    if (g_inboxStop) SetEvent(g_inboxStop);
    if (g_sessionThread && g_sessionTid) PostThreadMessageW(g_sessionTid, WM_QUIT, 0, 0);
    JoinThread(g_startThread, 15000, L"Start-up work");
    JoinThread(g_inboxThread, 5000, L"Inbox watcher");
    JoinThread(g_sessionThread, 5000, L"Session sounds");
    if (g_inboxStop) CloseHandle(g_inboxStop);
    g_inboxStop = nullptr;
    StopPresetJob();
    if (g_uiThread) {
        PostThreadMessageW(g_uiTid, WM_QUIT, 0, 0);
        JoinThread(g_uiThread, 15000, L"UI thread");
    }
    for (int i = 0; i < 150 && g_workers > 0; i++) Sleep(100);
    if (g_singleInstance) CloseHandle(g_singleInstance);
    g_singleInstance = nullptr;
}

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-11-sound-manager\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace smset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessSoundManagerSettings";
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
// Generated by work\2026-11-11-sound-manager\gen.py from spec.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Text, L"#name", L"Name", L"The scheme name Windows shows in Sound settings.", L"", {}, 0, 100, 0, L"Scheme"},
{K::Text, L"#author", L"Author", L"Who made the scheme.", L"", {}, 0, 100, 0, L"Scheme"},
{K::Text, L"#about", L"About", L"A short description, saved with the scheme when you export it.", L"", {}, 0, 100, 0, L"Scheme"},
{K::Check, L"missingUseDefault", L"Keep Windows sounds for gaps", L"When a scheme has no sound for an event, Windows keeps its own sound there. Off, that event stays silent.", L"1", {}, 0, 100, 3, L"Sounds"},
{K::Check, L"playSessionSounds", L"Play startup, logon and shutdown sounds", L"Windows no longer plays these itself. The mod plays Startup at boot, Log On and Log Off when you lock or switch users, and Shutdown when you shut down.", L"1", {}, 0, 100, 3, L"Sounds"},
{K::Check, L"preferStartupSound", L"Startup and Shutdown when signing in and out", L"Play Startup and Shutdown when you sign in and out. Log On and Log Off then only play when you lock the PC or switch users.", L"0", {}, 0, 100, 3, L"Sounds"},
{K::Check, L"fileAssoc", L"Open sound scheme files", L"Double-click a .ths or .soundpack file to load it with this mod.", L"1", {}, 0, 100, 3, L"Files"},
{K::Check, L"convertProprietary", L"Convert .soundpack files", L"When you import a .soundpack file, save a .ths copy beside it and move the original to the Recycle Bin.", L"0", {}, 0, 100, 3, L"Files"},
{K::Check, L"patchStartupSound", L"Patch the built-in startup sound", L"Writes your Startup sound into Windows' own startup sound file. Needs admin, and Windows updates undo it. Not recommended on Windows 10 and 11.", L"0", {}, 0, 100, 3, L"Startup sound"},
{K::Check, L"animations", L"Animations", L"Short fades and slides in the settings window. Off, changes are instant.", L"1", {}, 0, 100, 4, L"Motion"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Save, then reopen settings to apply.", L"1", {}, 0, 100, 4, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Save, then reopen settings to apply.", L"0", {}, 0, 100, 4, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"A speaker icon in the system tray. Click it to open these settings, right-click it for a menu. When off, open settings from Windhawk.", L"1", {}, 0, 100, 4, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Scheme", L"The sound scheme in use: its name, picture, import and export.", 0xE767},
{L"Sounds", L"Every Windows sound event. Play, replace, reset or turn off each one.", 0xE8D6},
{L"Presets", L"The ready sound schemes from the Sound Manager collection. Load one in a click.", 0xE8F1},
{L"System", L"How the scheme plays on this PC, sound files and the startup sound.", 0xE770},
{L"Look", L"Motion and this window.", 0xE790},
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
constexpr float kSetGlassTint = 0.55f, kSetNativeFade = 56;
constexpr int kSetChipCount = 10;
constexpr UINT32 kSetChips[kSetChipCount] = {mocha::blue,   mocha::sapphire, mocha::teal, mocha::green, mocha::yellow,
                                             mocha::peach,  mocha::red,      mocha::pink, mocha::mauve, mocha::lavender};
constexpr UINT_PTR kSetTimerId = 1;
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetDittoUrl = L"https://github.com/ORelio/Sound-Manager";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Sound%20Manager%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Sound Manager";
// The self-drawn title bar. Everything below it is laid out as before, in "content" DIPs.
static float kSetCapH = 40;
constexpr float kSetCapBtnW = 46, kSetHoverMs = 120;

struct SetItem {
    enum Type { Group, Row, Banner, About, Link, Support, Action, SchemeCard, SoundRow, PresetRow, SchemePick, Offer } type = Row;
    int ev = -1, cat = -1;  // Own items: sound event, preset or scheme index; a sub kind.
    int field = -1;  // Row: index into fields.
    float y = 0, h = 0;
    std::wstring text, sub, url;
};

// What the pointer is over. id picks the hover glow.
struct SetHit {
    enum Kind { None, Rail, Row, Control, Slider, Clear, Chip, Footer, Drop, Link, Scroll, Popup, Caption, RailToggle, RailEdge, Btn } kind = None;
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
struct SetPaint;
static float Sm_BuildTop(SetWindow& w, float y);
static float Sm_BuildPage(SetWindow& w, float y);
static void Sm_DrawItem(SetPaint& p, SetWindow& w, const SetItem& it, int idx);
static SetHit Sm_Hit(SetWindow& w, const SetItem& it, int idx, float x, float cy, const D2D1_RECT_F& row);
static void Sm_OnButton(SetWindow& w, const SetHit& h);
static bool Sm_Tick(SetWindow& w, bool anim);
static void Sm_MetaCommitted(SetWindow& w, int k);
static std::wstring Sm_MetaGet(PCWSTR key);
static void Sm_OnDrop(SetWindow& w, HDROP drop);
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
static void Set_MakeFormats(SetWindow& w) {
    w.family = Set_ResolveFamily();
    w.iconFamily = Set_FamilyExists(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
    int base = std::clamp(500, 100, 900);
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Sound Manager") <= railW) break;
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
        Set_PutValue(f, f.key[0] == L'#' ? Sm_MetaGet(f.key)
                        : isInt ? std::to_wstring(Wh_GetIntSetting(f.key)) : GetStringSetting(f.key));
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
    return !w.render && g_smAnimations && on;
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
    y = Sm_BuildTop(w, y);
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
    y = Sm_BuildPage(w, y);
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
        add(SetItem::Link, 56, L"Based on Sound Manager by ORelio", L"The original app, CDDL-1.0 license", kSetDittoUrl);
        add(SetItem::Link, 56, L"Sound Manager schemes by ORelio", L"The preset collection", L"https://github.com/ORelio/Sound-Manager-Schemes");
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
    if (h.kind == SetHit::Btn) ids[1] = 40000 + h.a * 8 + h.b;
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
    p.Glyph(w.fIconL.get(), 0xE767, mark, mocha::crust);
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Sound Manager", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  CDDL-1.0 license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"CDDL-1.0 license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Windows sound schemes: 161 presets, every sound editable.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, a port of Sound Manager by ORelio.",
           {x, row.top + 112, row.right - 16, row.bottom - 8}, mocha::overlay2);
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
    p.Text(w.fRailName.get(), L"Sound Manager", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    // The same see-through mantle as the rail dock, so the blurred rows under the pill read as
    // real glass instead of a near-solid bar.
    p.Round(d, rad, mocha::mantle, w.render ? 1.0f : (w.glass ? 0.58f : 0.85f));
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
    p.Glyph(glyph, 0xE767, r, mocha::crust);
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
                default: Sm_DrawItem(cp, w, it, (int)i); break;
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
        if (it.type > SetItem::Support) return Sm_Hit(w, it, (int)i, x, cy, row);
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
           h.kind == SetHit::Scroll || h.kind == SetHit::RailToggle || h.kind == SetHit::Btn;
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
    std::wstring text = std::to_wstring(vk);
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
        if (f.key[0] == L'#') Sm_MetaCommitted(w, k);
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
    for (auto& f : w.fields)
        if (f.key[0] != L'#') Set_PutValue(f, f.def);
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
    moved |= Sm_Tick(w, anim);
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
        case WM_APP_SETTINGS_RELOAD: if (!w->saving) Set_LoadFields(*w); Set_BuildAndClamp(*w); return 0;
        case WM_APP + 3: Set_LoadFields(*w); Set_BuildAndClamp(*w); return 0;
        case WM_DROPFILES: Sm_OnDrop(*w, (HDROP)wParam); DragFinish((HDROP)wParam); return 0;
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
                case SetHit::Btn:
                    Sm_OnButton(*w, h);
                    return 0;  // May rebuild the page.
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Sound Manager settings", style,
                                render ? offX : CW_USEDEFAULT, render ? offY : CW_USEDEFAULT, 800, 600, w->owner,
                                nullptr, (HINSTANCE)&__ImageBase, nullptr);
    if (!hwnd) {
        g_setWin.reset();
        return false;
    }
    w->hwnd = hwnd;
    if (!render) {
        // Windhawk runs elevated; let Explorer (not elevated) drop files here.
        ChangeWindowMessageFilterEx(hwnd, WM_DROPFILES, MSGFLT_ALLOW, nullptr);
        ChangeWindowMessageFilterEx(hwnd, WM_COPYDATA, MSGFLT_ALLOW, nullptr);
        ChangeWindowMessageFilterEx(hwnd, 0x0049 /* WM_COPYGLOBALDATA */, MSGFLT_ALLOW, nullptr);
        DragAcceptFiles(hwnd, TRUE);
    }
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

// ---- Sound Manager pages -------------------------------------------------------------
// The Scheme, Sounds, Presets and System pages add their own items through the Sm_* hooks
// the generator wires into the shared settings window. Rows are cards like every other row;
// buttons sit on the right of a card and light up with the same blue to mauve ring.

constexpr int kSmPageScheme = 0, kSmPageSounds = 1, kSmPagePresets = 2, kSmPageSystem = 3;

// Action rows (SetItem::Action, it.ev = which).
enum SmAction {
    kActImport, kActExport, kActWindows, kActFolder, kActReinstall, kActUninstall,
};

struct SmBtn {
    std::wstring label;
    WCHAR glyph = 0;       // Icon-only button when set.
    bool primary = false;  // Filled blue to mauve.
    bool enabled = true;
    bool confirm = false;  // Needs a second click within 4 s.
    bool toggle = false;   // On/off switch (Sounds page).
    bool on = false;
};

static int g_smArmed = -1;  // Button id (40000 + item * 8 + b) waiting for its second click.
static ULONGLONG g_smArmedAt = 0;
static int g_smPlaying = -1;  // Sound row whose Play was pressed last.
static ULONGLONG g_smPlayedAt = 0;
static std::wstring g_smLastAsync;
static std::vector<SmSystemScheme> g_smSchemes;
static std::map<int, float> g_smKnob;  // Eased switch position by sound event.

static int Sm_BtnId(int idx, int b) { return 40000 + idx * 8 + b; }

static std::vector<SmBtn> Sm_Buttons(const SetItem& it, int idx) {
    std::vector<SmBtn> b;
    auto add = [&](PCWSTR label, bool primary = false, bool confirm = false) {
        SmBtn x;
        x.label = label;
        x.primary = primary;
        x.confirm = confirm;
        b.push_back(x);
    };
    auto icon = [&](WCHAR g, PCWSTR tip, bool enabled = true) {
        SmBtn x;
        x.glyph = g;
        x.label = tip;
        x.enabled = enabled;
        b.push_back(x);
    };
    switch (it.type) {
        case SetItem::Offer:
            add(L"Load", true);
            add(L"Cancel");
            break;
        case SetItem::SchemeCard:
            add(L"Change image");
            add(L"Remove image");
            b.back().enabled = !SmThumbPath().empty();
            break;
        case SetItem::Action:
            switch (it.ev) {
                case kActImport: add(L"Import", true); break;
                case kActExport: add(L"Export .ths"); add(L"Export .themepack"); break;
                case kActWindows: add(L"Load", false, true); break;
                case kActFolder: add(L"Open"); break;
                case kActReinstall: add(L"Reinstall", false, true); break;
                case kActUninstall: add(L"Uninstall", false, true); break;
            }
            break;
        case SetItem::SchemePick:
            add(L"Load", false, true);
            break;
        case SetItem::PresetRow: {
            int busy = SmPresetBusy();
            add(L"Preview");
            add(L"Load", true, true);
            if (busy >= 0) b[0].enabled = b[1].enabled = false;
            break;
        }
        case SetItem::SoundRow: {
            bool has = SmSoundExists(it.ev);
            SmBtn t;
            t.toggle = true;
            t.on = !SmSoundDisabled(it.ev);
            t.label = t.on ? L"On" : L"Off";
            b.push_back(t);
            icon(0xE8E5, L"Replace");
            icon(0xE777, L"Reset to the Windows sound");
            icon(0xE74D, L"Remove", has);
            icon(0xE838, L"Show the file");
            break;
        }
        default: break;
    }
    if (g_smArmed >= 0)
        for (size_t i = 0; i < b.size(); i++)
            if (b[i].confirm && Sm_BtnId(idx, (int)i) == g_smArmed) b[i].label = L"Click again";
    return b;
}

// Button rectangles, right aligned in the card (bottom right for the scheme card).
static std::vector<D2D1_RECT_F> Sm_BtnRects(SetWindow& w, const SetItem& it, int idx, const D2D1_RECT_F& row) {
    std::vector<SmBtn> b = Sm_Buttons(it, idx);
    std::vector<D2D1_RECT_F> out(b.size());
    float right = row.right - kSetRowPad;
    float mid = it.type == SetItem::SchemeCard ? row.bottom - 16 - 16 : (row.top + row.bottom) / 2;
    for (int i = (int)b.size() - 1; i >= 0; i--) {
        float bw, bh = 32;
        if (b[i].toggle) {
            bw = 44;
            bh = 22;
        } else if (b[i].glyph) {
            bw = 34;
        } else {
            // Width of the widest label this button can show, so "Click again" never resizes it.
            float tw = Set_TextW(w.fButton.get(), b[i].label);
            if (b[i].confirm) tw = std::max(tw, Set_TextW(w.fButton.get(), L"Click again"));
            bw = std::max(76.0f, tw + 28);
        }
        out[i] = {right - bw, mid - bh / 2, right, mid + bh / 2};
        right -= bw + (b[i].toggle ? 14 : 8);
    }
    return out;
}

static float Sm_ButtonsW(SetWindow& w, const SetItem& it, int idx, const D2D1_RECT_F& row) {
    auto r = Sm_BtnRects(w, it, idx, row);
    return r.empty() ? 0 : row.right - kSetRowPad - r.front().left;
}

// ---- Layout ----------------------------------------------------------------------------

static float Sm_Group(SetWindow& w, float y, PCWSTR text, bool first) {
    SetItem g;
    g.type = SetItem::Group;
    g.text = text;
    g.y = y + (first ? 0 : 14);
    g.h = 22;
    w.items.push_back(g);
    return g.y + g.h + 6;
}

static float Sm_Add(SetWindow& w, float y, SetItem::Type t, float h, int ev, PCWSTR text, PCWSTR sub, int cat = -1) {
    SetItem it;
    it.type = t;
    it.y = y;
    it.h = h;
    it.ev = ev;
    it.cat = cat;
    it.text = text ? text : L"";
    it.sub = sub ? sub : L"";
    w.items.push_back(it);
    return y + h + kSetRowGap;
}

// A two-line card tall enough for its wrapped text beside the buttons.
static float Sm_CardH(SetWindow& w, const SetItem& probe, const std::wstring& text, const std::wstring& sub) {
    D2D1_RECT_F row{w.contentX, 0, w.contentX + w.contentW, 60};
    float textW = w.contentW - 2 * kSetRowPad - Sm_ButtonsW(w, probe, 0, row) - 20;
    float lh = Set_TextH(w.fLabel.get(), text, textW);
    float dh = sub.empty() ? 0 : Set_TextH(w.fHint.get(), sub, textW) + 3;
    return std::max(kSetRowMin, 26 + lh + dh);
}

static float Sm_AddCard(SetWindow& w, float y, SetItem::Type t, int ev, const std::wstring& text, const std::wstring& sub,
                        int cat = -1) {
    SetItem probe;
    probe.type = t;
    probe.ev = ev;
    probe.cat = cat;
    return Sm_Add(w, y, t, Sm_CardH(w, probe, text, sub), ev, text.c_str(), sub.c_str(), cat);
}

static void Sm_RefreshMetaFields(SetWindow& w) {
    for (auto& f : w.fields) {
        if (f.key[0] != L'#') continue;
        Set_PutValue(f, Sm_MetaGet(f.key));
        f.value = Set_FieldValue(f);
    }
}

static void Sm_PullAsyncStatus(SetWindow& w) {
    bool error = false, finished = false;
    std::wstring s = SmPresetStatus(error, finished);
    if (!s.empty() && (s != g_smLastAsync || finished)) {
        w.status = s;
        w.statusError = error;
    }
    g_smLastAsync = s;
    if (finished) Sm_RefreshMetaFields(w);  // A load replaced the scheme: its details follow.
}

static float Sm_BuildTop(SetWindow& w, float y) {
    Sm_PullAsyncStatus(w);
    if (w.page != kSmPageScheme) return y;
    std::wstring pending = SmPendingFile();
    if (!pending.empty()) {
        std::wstring name = PathFindFileNameW(pending.c_str());
        y = Sm_AddCard(w, y, SetItem::Offer, 0, L"Would you like to load this sound scheme?",
                       name + L"\nThe current sounds will be replaced.");
        y += 8;
    }
    y = Sm_Add(w, y, SetItem::SchemeCard, 136, 0, L"", L"");
    return y + 6;
}

static float Sm_BuildPage(SetWindow& w, float y) {
    bool first = w.items.empty() || (w.items.size() == 1 && w.items[0].type == SetItem::Banner);
    switch (w.page) {
        case kSmPageScheme: {
            y = Sm_Group(w, y, L"Import and export", false);
            y = Sm_AddCard(w, y, SetItem::Action, kActImport, L"Import a sound scheme",
                           L"A .ths, .soundpack or .zip file. Its sounds, name and picture replace the current ones.");
            y = Sm_AddCard(w, y, SetItem::Action, kActExport, L"Export this scheme",
                           L".ths opens in Sound Manager and this mod. .themepack is a Windows theme with these sounds.");
            y = Sm_Group(w, y, L"Reset", false);
            y = Sm_AddCard(w, y, SetItem::Action, kActWindows, L"Load the Windows sounds",
                           L"The default sound scheme will be loaded and the current sounds will be lost.");
            g_smSchemes = SmSystemSchemes();
            if (!g_smSchemes.empty()) {
                y = Sm_Group(w, y, L"Schemes on this PC", false);
                for (size_t i = 0; i < g_smSchemes.size(); i++)
                    y = Sm_AddCard(w, y, SetItem::SchemePick, (int)i, g_smSchemes[i].name,
                                   L"Copies this Windows scheme's sounds into the current scheme.");
            }
            break;
        }
        case kSmPageSounds: {
            static const struct { int from, to; PCWSTR name; } kGroups[] = {
                {0, 3, L"Startup and sign in"}, {4, 7, L"Messages"}, {8, 10, L"Devices"},
                {11, 20, L"Windows"},           {21, 30, L"Apps and menus"},
            };
            for (const auto& g : kGroups) {
                y = Sm_Group(w, y, g.name, first);
                first = false;
                for (int ev = g.from; ev <= g.to; ev++) {
                    std::wstring sub = std::wstring(kSmEvents[ev].desc) + L"  \u00B7  " + SmSoundInfo(ev);
                    SetItem probe;
                    probe.type = SetItem::SoundRow;
                    probe.ev = ev;
                    float h = Sm_CardH(w, probe, kSmEvents[ev].name, sub) + 0;
                    y = Sm_Add(w, y, SetItem::SoundRow, std::max(64.0f, h), ev, kSmEvents[ev].name, sub.c_str());
                }
            }
            break;
        }
        case kSmPagePresets: {
            SetItem link;
            link.type = SetItem::Link;
            link.y = y;
            link.h = 56;
            link.text = L"The Sound Manager schemes collection";
            link.sub = L"Every preset here comes from it. Downloads are kept, so a preset loads at once the next time.";
            link.url = L"https://github.com/ORelio/Sound-Manager-Schemes";
            link.h = std::max(56.0f, 26 + 21 + Set_TextH(w.fHint.get(), link.sub, w.contentW - 2 * kSetRowPad - 50) + 3);
            w.items.push_back(link);
            y += link.h + kSetRowGap;
            PCWSTR cat = nullptr;
            for (int i = 0; i < kSmPresetCount; i++) {
                const SmPreset& p = kSmPresets[i];
                if (!cat || wcscmp(cat, p.category) != 0) {
                    y = Sm_Group(w, y, p.category, false);
                    cat = p.category;
                }
                std::wstring sub = p.author[0] ? std::wstring(L"By ") + p.author : std::wstring(L"Unknown author");
                if (p.about[0] && wcsncmp(p.about, L"http", 4) != 0) sub += std::wstring(L"  \u00B7  ") + p.about;
                WCHAR size[32];
                if (p.sizeKB >= 1024) swprintf_s(size, L"%.1f MB", p.sizeKB / 1024.0);
                else swprintf_s(size, L"%d KB", p.sizeKB);
                sub += std::wstring(L"  \u00B7  ") + size + (SmPresetCached(i) ? L", downloaded" : L"");
                y = Sm_AddCard(w, y, SetItem::PresetRow, i, p.name, sub);
            }
            break;
        }
        case kSmPageSystem: {
            y = Sm_Group(w, y, L"Maintenance", false);
            y = Sm_AddCard(w, y, SetItem::Action, kActFolder, L"Open the sounds folder",
                           L"Where the scheme's sound files, picture and details are kept.");
            y = Sm_AddCard(w, y, SetItem::Action, kActReinstall, L"Set the scheme up again",
                           SmIsActive() ? L"The Sound Manager scheme is in use. This writes it to Windows again."
                                        : L"Windows is using another scheme now. This makes the Sound Manager scheme the one in use.");
            y = Sm_AddCard(w, y, SetItem::Action, kActUninstall, L"Remove the scheme from Windows",
                           L"Puts the Windows sounds back and removes the Sound Manager scheme. Your sound files stay.");
            break;
        }
        default: break;
    }
    return y;
}

// ---- Drawing ---------------------------------------------------------------------------

static SetCom<ID2D1Bitmap> g_smThumb;
static ID2D1RenderTarget* g_smThumbRt = nullptr;
static UINT g_smThumbVer = (UINT)-1;

static ID2D1Bitmap* Sm_Thumb(ID2D1RenderTarget* rt) {
    UINT ver = SmThumbVersion();
    if (g_smThumbRt == rt && g_smThumbVer == ver) return g_smThumb.get();
    g_smThumb.reset();
    g_smThumbRt = rt;
    g_smThumbVer = ver;
    std::wstring path = SmThumbPath();
    if (path.empty() || !g_setWic) return nullptr;
    SetCom<IWICBitmapDecoder> dec;
    SetCom<IWICBitmapFrameDecode> frame;
    SetCom<IWICFormatConverter> conv;
    if (FAILED(g_setWic->CreateDecoderFromFilename(path.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad,
                                                   dec.put())) ||
        FAILED(dec->GetFrame(0, frame.put())) || FAILED(g_setWic->CreateFormatConverter(conv.put())) ||
        FAILED(conv->Initialize(frame.get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0,
                                WICBitmapPaletteTypeCustom)))
        return nullptr;
    rt->CreateBitmapFromWicBitmap(conv.get(), nullptr, g_smThumb.put());
    return g_smThumb.get();
}

static void Sm_DrawButtons(SetPaint& p, SetWindow& w, const SetItem& it, int idx, const D2D1_RECT_F& row) {
    std::vector<SmBtn> b = Sm_Buttons(it, idx);
    std::vector<D2D1_RECT_F> r = Sm_BtnRects(w, it, idx, row);
    for (size_t i = 0; i < b.size(); i++) {
        int id = Sm_BtnId(idx, (int)i);
        float g = b[i].enabled ? Set_GlowOf(w, id) : 0;
        float a = b[i].enabled ? 1.0f : 0.4f;
        bool armed = id == g_smArmed;
        if (b[i].toggle) {
            float t = g_smKnob.count(it.ev) ? g_smKnob[it.ev] : (b[i].on ? 1.0f : 0.0f);
            const D2D1_RECT_F& s = r[i];
            float rad = (s.bottom - s.top) / 2;
            p.Round(s, rad, mocha::surface1);
            p.GradFill(s, rad, t);
            p.GradRing(s, rad, g * (1 - t), 1.5f);
            float d = s.bottom - s.top - 6, x = s.left + 3 + t * (s.right - s.left - 6 - d);
            p.Round({x, s.top + 3, x + d, s.bottom - 3}, d / 2, t > 0.5f ? mocha::crust : mocha::subtext0);
            continue;
        }
        if (armed) {
            p.Round(r[i], 8, mocha::red, 0.85f + 0.15f * g);
            p.Text(w.fButton.get(), b[i].label, r[i], mocha::crust);
            continue;
        }
        if (b[i].primary && b[i].enabled) {
            p.GradFill(r[i], 8, 0.85f + 0.15f * g);
            p.GradRing(r[i], 8, g, 2);
            p.Text(w.fButton.get(), b[i].label, r[i], mocha::crust);
            continue;
        }
        p.Round(r[i], 8, kSetBoxFill, a);
        p.Edge(r[i], 8, mocha::overlay0, 0.7f * (1 - g) * a, 1.25f);
        p.GradRing(r[i], 8, g, 1.75f);
        if (b[i].glyph) {
            p.Glyph(w.fIcon.get(), b[i].glyph, r[i], g > 0.05f ? mocha::text : mocha::subtext1, a);
        } else {
            p.Text(w.fButton.get(), b[i].label, r[i], mocha::text, a);
        }
    }
}

// The row card, the hover wash and ring, then text left of the buttons.
static void Sm_DrawCardText(SetPaint& p, SetWindow& w, const SetItem& it, int idx, const D2D1_RECT_F& row, float left,
                            float dim) {
    float textR = row.right - kSetRowPad - Sm_ButtonsW(w, it, idx, row) - 20;
    float lh = Set_TextH(w.fLabel.get(), it.text, textR - left);
    float dh = it.sub.empty() ? 0 : Set_TextH(w.fHint.get(), it.sub, textR - left) + 3;
    float top = row.top + (row.bottom - row.top - lh - dh) / 2;
    p.Text(w.fLabel.get(), it.text, {left, top, textR, top + lh + 2}, mocha::text, dim);
    if (!it.sub.empty())
        p.Text(w.fHint.get(), it.sub, {left, top + lh + 3, textR, top + lh + 3 + dh + 2}, mocha::subtext0, dim);
}

static void Sm_DrawItem(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 20000 + idx);
    if (it.type == SetItem::Offer) {
        p.Round(row, 10, mocha::base);
        p.Round(row, 10, mocha::blue, 0.12f);
        p.GradRing(row, 10, 0.6f + 0.4f * hov, 1.5f);
        p.Glyph(w.fIcon.get(), 0xE896, {row.left + 12, row.top, row.left + 44, row.bottom}, mocha::blue);
        Sm_DrawCardText(p, w, it, idx, row, row.left + 48, 1);
        Sm_DrawButtons(p, w, it, idx, row);
        return;
    }
    Set_DrawCard(p, row, hov);
    p.GradFill(row, 10, 0.08f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    switch (it.type) {
        case SetItem::SchemeCard: {
            D2D1_RECT_F pic{row.left + 18, row.top + 18, row.left + 118, row.top + 118};
            if (ID2D1Bitmap* bmp = Sm_Thumb(p.rt)) {
                p.Round(pic, 12, mocha::crust);
                p.rt->DrawBitmap(bmp, pic, p.fade, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
                p.Edge(pic, 4, mocha::surface2, 0.6f);
            } else {
                p.GradFill(pic, 16, 1);
                p.Glyph(w.fIconL.get(), 0xE767, pic, mocha::crust);
            }
            SmMeta m = SmGetMeta();
            float x = pic.right + 20, r = row.right - 16;
            p.Text(w.fBig.get(), m.name.empty() ? L"Untitled scheme" : m.name, {x, row.top + 16, r, row.top + 44},
                   mocha::text);
            p.Text(w.fHint.get(), m.author.empty() ? L"No author" : L"By " + m.author, {x, row.top + 46, r, row.top + 64},
                   mocha::subtext0);
            int count = 0;
            for (int e = 0; e < kSmEventCount; e++) count += SmSoundExists(e) && !SmSoundDisabled(e);
            std::wstring line = std::to_wstring(count) + L" of 31 sounds  \u00B7  " +
                                (SmIsActive() ? L"In use" : L"Not in use");
            p.Text(w.fHint.get(), line, {x, row.top + 66, r, row.top + 84}, SmIsActive() ? mocha::green : mocha::peach);
            float bl = Sm_BtnRects(w, it, idx, row).front().left;
            if (!m.about.empty()) p.Text(w.fSmall.get(), m.about, {x, row.top + 88, bl - 12, row.bottom - 10}, mocha::overlay2);
            Sm_DrawButtons(p, w, it, idx, row);
            break;
        }
        case SetItem::SoundRow: {
            bool off = SmSoundDisabled(it.ev), has = SmSoundExists(it.ev);
            D2D1_RECT_F play{row.left + 14, (row.top + row.bottom) / 2 - 18, row.left + 50, (row.top + row.bottom) / 2 + 18};
            float pg = Set_GlowOf(w, Sm_BtnId(idx, 7));
            bool now = g_smPlaying == it.ev && GetTickCount64() - g_smPlayedAt < 1500;
            if (has) {
                p.GradFill(play, 18, (now ? 1.0f : 0.25f + 0.75f * pg) * (off ? 0.5f : 1));
                p.Glyph(w.fIcon.get(), 0xE768, play, now || pg > 0.5f ? mocha::crust : mocha::text, off ? 0.6f : 1);
            } else {
                p.Round(play, 18, mocha::surface0, 0.8f);
                p.Glyph(w.fIcon.get(), 0xE74F, play, mocha::overlay1);
            }
            Sm_DrawCardText(p, w, it, idx, row, row.left + 64, off ? 0.5f : 1);
            Sm_DrawButtons(p, w, it, idx, row);
            break;
        }
        case SetItem::PresetRow: {
            Sm_DrawCardText(p, w, it, idx, row, row.left + kSetRowPad, 1);
            if (SmPresetBusy() == it.ev) {
                auto r = Sm_BtnRects(w, it, idx, row);
                D2D1_RECT_F all{r.front().left, r.front().top, r.back().right, r.back().bottom};
                p.Round(all, 8, mocha::crust);
                p.Text(w.fButton.get(), L"Working...", all, mocha::subtext1);
            } else {
                Sm_DrawButtons(p, w, it, idx, row);
            }
            break;
        }
        default:  // Action, SchemePick.
            Sm_DrawCardText(p, w, it, idx, row, row.left + kSetRowPad, 1);
            Sm_DrawButtons(p, w, it, idx, row);
            break;
    }
}

// ---- Hit testing -----------------------------------------------------------------------

static SetHit Sm_Hit(SetWindow& w, const SetItem& it, int idx, float x, float cy, const D2D1_RECT_F& row) {
    SetHit h;
    h.id = 20000 + idx;
    h.a = idx;
    std::vector<SmBtn> b = Sm_Buttons(it, idx);
    std::vector<D2D1_RECT_F> r = Sm_BtnRects(w, it, idx, row);
    if (it.type == SetItem::PresetRow && SmPresetBusy() >= 0) return h;
    for (size_t i = 0; i < b.size(); i++) {
        D2D1_RECT_F hit{r[i].left - 3, r[i].top - 4, r[i].right + 3, r[i].bottom + 4};
        if (b[i].enabled && Set_In(hit, x, cy)) {
            h.kind = SetHit::Btn;
            h.b = (int)i;
            return h;
        }
    }
    if (it.type == SetItem::SoundRow && SmSoundExists(it.ev)) {
        D2D1_RECT_F play{row.left + 10, row.top, row.left + 56, row.bottom};
        if (Set_In(play, x, cy)) {
            h.kind = SetHit::Btn;
            h.b = 7;  // Play.
        }
    }
    return h;
}

// ---- File dialogs ----------------------------------------------------------------------

static std::wstring Sm_PickFile(SetWindow& w, PCWSTR filter, PCWSTR title, bool save, PCWSTR defName = L"",
                                PCWSTR defExt = nullptr) {
    WCHAR file[MAX_PATH * 4] = {};
    if (defName) wcsncpy_s(file, defName, _TRUNCATE);
    OPENFILENAMEW ofn{sizeof(ofn)};
    ofn.hwndOwner = w.hwnd;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = file;
    ofn.nMaxFile = ARRAYSIZE(file);
    ofn.lpstrTitle = title;
    ofn.lpstrDefExt = defExt;
    ofn.Flags = OFN_EXPLORER | OFN_NOCHANGEDIR | OFN_HIDEREADONLY |
                (save ? OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST : OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST);
    BOOL ok = save ? GetSaveFileNameW(&ofn) : GetOpenFileNameW(&ofn);
    return ok ? std::wstring(file) : std::wstring();
}

constexpr PCWSTR kSmAudioFilter =
    L"Sound files\0*.wav;*.mp3;*.wma;*.m4a;*.aac;*.flac;*.ogg;*.opus;*.aif;*.aiff;*.mp4\0All files\0*.*\0";
constexpr PCWSTR kSmSchemeFilter = L"Sound schemes\0*.ths;*.soundpack;*.zip\0All files\0*.*\0";
constexpr PCWSTR kSmImageFilter = L"Pictures\0*.png;*.jpg;*.jpeg;*.bmp;*.gif;*.tif;*.tiff;*.ico;*.webp\0All files\0*.*\0";

static std::wstring Sm_SafeName() {
    std::wstring n = SmGetMeta().name;
    if (n.empty()) n = L"Sound scheme";
    for (auto& c : n)
        if (wcschr(L"\\/:*?\"<>|", c)) c = L'_';
    return n;
}

static void Sm_Result(SetWindow& w, bool ok, const std::wstring& done, const std::wstring& error) {
    Set_SetStatus(w, ok ? done.c_str() : (error.empty() ? L"That didn't work." : error.c_str()), !ok);
}

static void Sm_AfterSchemeChange(SetWindow& w) {
    Sm_RefreshMetaFields(w);
    Set_BuildAndClamp(w);
}

// ---- Buttons ---------------------------------------------------------------------------

static void Sm_OnButton(SetWindow& w, const SetHit& h) {
    if (h.a < 0 || h.a >= (int)w.items.size()) return;
    SetItem it = w.items[h.a];  // Copy: the page may rebuild below.
    std::vector<SmBtn> b = Sm_Buttons(it, h.a);
    int id = Sm_BtnId(h.a, h.b);
    if (h.b < (int)b.size() && b[h.b].confirm && g_smArmed != id) {
        g_smArmed = id;
        g_smArmedAt = GetTickCount64();
        Set_SetStatus(w, L"Click again to confirm.");
        return;
    }
    g_smArmed = -1;
    std::wstring err;
    switch (it.type) {
        case SetItem::Offer: {
            std::wstring file = SmPendingFile();
            SmClearPendingFile();
            if (h.b == 0 && !file.empty()) {
                bool ok = SmImport(file, err);
                Sm_Result(w, ok, L"Sound scheme loaded.", err);
            } else {
                Set_SetStatus(w, L"");
            }
            Sm_AfterSchemeChange(w);
            break;
        }
        case SetItem::SchemeCard:
            if (h.b == 0) {
                std::wstring file = Sm_PickFile(w, kSmImageFilter, L"Choose a picture for the scheme", false);
                if (!file.empty()) Sm_Result(w, SmSetImage(file, err), L"Picture changed.", err);
            } else {
                SmRemoveImage();
                Set_SetStatus(w, L"Picture removed.");
            }
            Set_BuildAndClamp(w);
            break;
        case SetItem::Action:
            switch (it.ev) {
                case kActImport: {
                    std::wstring file = Sm_PickFile(w, kSmSchemeFilter, L"Import a sound scheme", false);
                    if (file.empty()) break;
                    Set_SetStatus(w, L"Loading...");
                    UpdateWindow(w.hwnd);
                    Sm_Result(w, SmImport(file, err), L"Sound scheme loaded.", err);
                    Sm_AfterSchemeChange(w);
                    break;
                }
                case kActExport: {
                    bool ths = h.b == 0;
                    std::wstring name = Sm_SafeName() + (ths ? L".ths" : L".themepack");
                    std::wstring file = ths ? Sm_PickFile(w, L"Sound scheme (.ths)\0*.ths\0", L"Export the sound scheme", true,
                                                          name.c_str(), L"ths")
                                            : Sm_PickFile(w, L"Windows theme (.themepack)\0*.themepack\0",
                                                          L"Export as a Windows theme", true, name.c_str(), L"themepack");
                    if (file.empty()) break;
                    Set_SetStatus(w, L"Exporting...");
                    UpdateWindow(w.hwnd);
                    bool ok = ths ? SmExportThs(file, err) : SmExportThemepack(file, err);
                    Sm_Result(w, ok, std::wstring(L"Saved ") + PathFindFileNameW(file.c_str()) + L".", err);
                    break;
                }
                case kActWindows:
                    Sm_Result(w, SmLoadWindowsDefaults(err), L"The Windows sounds are loaded.", err);
                    Sm_AfterSchemeChange(w);
                    break;
                case kActFolder: SmOpenDataFolder(); break;
                case kActReinstall:
                    Sm_Result(w, SmReinstall(err), L"The scheme is set up and in use.", err);
                    Set_BuildAndClamp(w);
                    break;
                case kActUninstall:
                    Sm_Result(w, SmUninstall(err), L"Windows sounds are back. The scheme is removed from Windows.", err);
                    Set_BuildAndClamp(w);
                    break;
            }
            break;
        case SetItem::SchemePick:
            if (it.ev >= 0 && it.ev < (int)g_smSchemes.size()) {
                Sm_Result(w, SmLoadSystemScheme(g_smSchemes[it.ev].id, err),
                          L"Loaded " + g_smSchemes[it.ev].name + L".", err);
                Sm_AfterSchemeChange(w);
            }
            break;
        case SetItem::PresetRow:
            SmPresetStart(it.ev, h.b == 0 ? 0 : 1, w.hwnd);
            Set_SetStatus(w, (std::wstring(h.b == 0 ? L"Getting a preview of " : L"Loading ") + kSmPresets[it.ev].name +
                              L"...").c_str());
            Set_BuildAndClamp(w);
            break;
        case SetItem::SoundRow: {
            int ev = it.ev;
            PCWSTR name = kSmEvents[ev].name;
            switch (h.b) {
                case 7:
                case -1:
                    if (SmPlay(ev)) {
                        g_smPlaying = ev;
                        g_smPlayedAt = GetTickCount64();
                    }
                    break;
                case 0: {
                    bool off = !SmSoundDisabled(ev);
                    SmSetDisabled(ev, off);
                    Set_SetStatus(w, (std::wstring(name) + (off ? L" is off." : L" is on.")).c_str());
                    break;
                }
                case 1: {
                    std::wstring file =
                        Sm_PickFile(w, kSmAudioFilter, (std::wstring(L"Choose a sound for ") + name).c_str(), false);
                    if (file.empty()) break;
                    Set_SetStatus(w, L"Converting...");
                    UpdateWindow(w.hwnd);
                    bool ok = SmReplaceSound(ev, file, err);
                    Sm_Result(w, ok, std::wstring(name) + L" changed.", err);
                    if (ok && SmPlay(ev)) {
                        g_smPlaying = ev;
                        g_smPlayedAt = GetTickCount64();
                    }
                    break;
                }
                case 2: Sm_Result(w, SmResetSound(ev, err), std::wstring(name) + L" is back to the Windows sound.", err); break;
                case 3:
                    SmRemoveSound(ev);
                    Set_SetStatus(w, (std::wstring(name) + L" removed.").c_str());
                    break;
                case 4: SmShowInFolder(ev); break;
            }
            Set_BuildAndClamp(w);
            break;
        }
        default: break;
    }
}

// ---- Tick, fields, drops ---------------------------------------------------------------

static bool Sm_Tick(SetWindow& w, bool anim) {
    bool moved = false;
    if (g_smArmed >= 0 && GetTickCount64() - g_smArmedAt > 4000) {
        g_smArmed = -1;
        if (w.status == L"Click again to confirm.") w.status.clear();
        moved = true;
    }
    if (w.page == kSmPageSounds) {
        for (int ev = 0; ev < kSmEventCount; ev++) {
            float target = SmSoundDisabled(ev) ? 0.0f : 1.0f;
            auto f = g_smKnob.find(ev);
            if (f == g_smKnob.end()) {
                g_smKnob[ev] = target;
                continue;
            }
            float d = target - f->second;
            if (d == 0) continue;
            f->second = (!anim || fabsf(d) < 0.02f) ? target : f->second + d * 0.35f;
            moved = true;
        }
        if (g_smPlaying >= 0 && GetTickCount64() - g_smPlayedAt >= 1500) {
            g_smPlaying = -1;
            moved = true;
        }
    }
    return moved;
}

static std::wstring Sm_MetaGet(PCWSTR key) {
    SmMeta m = SmGetMeta();
    if (!wcscmp(key, L"#name")) return m.name;
    if (!wcscmp(key, L"#author")) return m.author;
    if (!wcscmp(key, L"#about")) return m.about;
    return L"";
}

// Name, author and about save straight into the scheme, not into Windhawk's settings, so they
// never count as unsaved changes.
static void Sm_MetaCommitted(SetWindow& w, int k) {
    SetField& f = w.fields[k];
    SmMeta m = SmGetMeta();
    std::wstring v = f.cur;
    for (auto& c : v)
        if (c == L'\r' || c == L'\n') c = L' ';
    if (!wcscmp(f.key, L"#name")) m.name = v;
    else if (!wcscmp(f.key, L"#author")) m.author = v;
    else if (!wcscmp(f.key, L"#about")) m.about = v;
    if (Sm_MetaGet(f.key) != v) {
        SmSetMeta(m);
        Set_SetStatus(w, L"Scheme details saved.");
    }
    f.cur = v;
    f.value = v;
}

// A file dropped on the window: a sound on a sound row replaces it, a picture on the scheme
// card becomes the picture, and a scheme file anywhere is imported.
static void Sm_OnDrop(SetWindow& w, HDROP drop) {
    WCHAR file[MAX_PATH * 4];
    if (!DragQueryFileW(drop, 0, file, ARRAYSIZE(file))) return;
    POINT pt{};
    DragQueryPoint(drop, &pt);
    float x = pt.x * 96.0f / w.dpi, y = pt.y * 96.0f / w.dpi - kSetCapH + w.scrollY;
    std::wstring ext = PathFindExtensionW(file);
    CharLowerBuffW(ext.data(), (DWORD)ext.size());
    std::wstring err;
    bool scheme = ext == L".ths" || ext == L".soundpack" || ext == L".zip";
    bool image = ext == L".png" || ext == L".jpg" || ext == L".jpeg" || ext == L".bmp" || ext == L".gif" ||
                 ext == L".webp" || ext == L".ico" || ext == L".tif" || ext == L".tiff";
    ForceForeground(w.hwnd);
    if (scheme) {
        Set_SetStatus(w, L"Loading...");
        UpdateWindow(w.hwnd);
        Sm_Result(w, SmImport(file, err), L"Sound scheme loaded.", err);
        Sm_AfterSchemeChange(w);
        return;
    }
    for (const SetItem& it : w.items) {
        D2D1_RECT_F row = Set_RowRect(w, it);
        if (!Set_In(row, x, y)) continue;
        if (it.type == SetItem::SoundRow) {
            Set_SetStatus(w, L"Converting...");
            UpdateWindow(w.hwnd);
            bool ok = SmReplaceSound(it.ev, file, err);
            Sm_Result(w, ok, std::wstring(kSmEvents[it.ev].name) + L" changed.", err);
            if (ok) SmPlay(it.ev);
            Set_BuildAndClamp(w);
            return;
        }
        if (it.type == SetItem::SchemeCard && image) {
            Sm_Result(w, SmSetImage(file, err), L"Picture changed.", err);
            Set_BuildAndClamp(w);
            return;
        }
    }
    if (image && w.page == kSmPageScheme) {
        Sm_Result(w, SmSetImage(file, err), L"Picture changed.", err);
        Set_BuildAndClamp(w);
        return;
    }
    Set_SetStatus(w, w.page == kSmPageSounds ? L"Drop a sound on the row it should replace."
                                             : L"Drop a .ths or .soundpack file to load it.", true);
}
}  // namespace smset
