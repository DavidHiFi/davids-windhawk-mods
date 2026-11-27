//! Windows settings for the Privacy, Performance, Apps, Updates and Windows pages.
//!
//! Written clean from Microsoft's own documentation of each setting: the Group
//! Policy and Policy CSP references and the registry values those policies
//! write, the documented per-user values behind the Settings app's switches,
//! and the powercfg, DISM and Appx command references. No other optimizer's
//! code, lists or wording were used.
//!
//! A toggle is "on" when every part of it holds its value. Turning one on
//! records each old value first, so turning it off puts back exactly what was
//! there. A toggle found on without a record (set by hand or by Windows) is
//! turned off by writing the Windows default instead.

use anyhow::{anyhow, bail, Result};
use swo_core::reg::V::{self, D, S};
use swo_core::{proc, reg, svc, sys, task, Ctx, Done, Item, Kind, Provider, Risk, State, Txn, Undo};

type Row = (&'static str, &'static str, V);

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum Special {
    /// The High performance power plan is active.
    HighPlan,
    /// Hibernation (and with it the hibernation file and fast startup) is off.
    Hibernate,
    /// The space Windows holds back for updates is given back.
    ReservedStorage,
}

enum Op {
    Reg(&'static [Row]),
    /// Service name, start type when on, Windows default.
    Svc(&'static str, u32, u32),
    /// Scheduled tasks that are switched off when on.
    Tasks(&'static [&'static str]),
    Special(Special),
}

struct Tweak {
    id: String,
    page: &'static str,
    group: &'static str,
    name: &'static str,
    desc: &'static str,
    risk: Risk,
    pick: bool,
    reboot: bool,
    warn: Option<&'static str>,
    ops: Vec<Op>,
    /// Values written when turning off a tweak with no undo record. Rows of
    /// the tweak not listed here are deleted (the default for policy values).
    off: &'static [Row],
    /// Keys removed when turning off a tweak with no undo record.
    off_keys: &'static [&'static str],
}

fn t(page: &'static str, id: &str, group: &'static str, name: &'static str, desc: &'static str) -> Tweak {
    Tweak {
        id: format!("{page}.{id}"),
        page,
        group,
        name,
        desc,
        risk: Risk::Safe,
        pick: false,
        reboot: false,
        warn: None,
        ops: Vec::new(),
        off: &[],
        off_keys: &[],
    }
}

impl Tweak {
    fn reg(mut self, rows: &'static [Row]) -> Self {
        self.ops.push(Op::Reg(rows));
        self
    }
    fn svc(mut self, name: &'static str, on: u32, default: u32) -> Self {
        self.ops.push(Op::Svc(name, on, default));
        self
    }
    fn tasks(mut self, paths: &'static [&'static str]) -> Self {
        self.ops.push(Op::Tasks(paths));
        self
    }
    fn special(mut self, s: Special) -> Self {
        self.ops.push(Op::Special(s));
        self
    }
    fn off(mut self, rows: &'static [Row]) -> Self {
        self.off = rows;
        self
    }
    fn off_keys(mut self, keys: &'static [&'static str]) -> Self {
        self.off_keys = keys;
        self
    }
    fn pick(mut self) -> Self {
        self.pick = true;
        self
    }
    fn moderate(mut self) -> Self {
        self.risk = Risk::Moderate;
        self
    }
    fn advanced(mut self) -> Self {
        self.risk = Risk::Advanced;
        self
    }
    fn reboot(mut self) -> Self {
        self.reboot = true;
        self
    }
    fn warn(mut self, w: &'static str) -> Self {
        self.warn = Some(w);
        self
    }

    fn admin(&self) -> bool {
        self.ops.iter().any(|o| match o {
            Op::Reg(rows) => rows.iter().any(|(k, _, _)| !k.to_ascii_uppercase().starts_with("HKCU")),
            _ => true,
        })
    }

    fn item(&self) -> Item {
        let mut i = Item::new(self.id.clone(), self.page, self.group, self.name, self.desc, Kind::Toggle).risk(self.risk);
        if self.admin() {
            i = i.admin();
        }
        if self.reboot {
            i = i.reboot();
        }
        if self.pick {
            i = i.pick();
        }
        if let Some(w) = self.warn {
            i = i.warn(w);
        }
        i
    }
}

// ---------------------------------------------------------------- catalog

const CLASSIC_MENU: &str = "HKCU\\Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}";

fn catalog() -> Vec<Tweak> {
    vec![
        // ------------------------------------------------------------ Privacy
        t("privacy", "telemetry", "Diagnostics", "Send only required diagnostic data",
          "Windows sends the least usage data your edition allows and stops fetching extra data rules.")
            .reg(&[
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", "AllowTelemetry", D(1)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", "LimitDiagnosticLogCollection", D(1)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", "DisableOneSettingsDownloads", D(1)),
            ])
            .pick(),
        t("privacy", "diagtrack", "Diagnostics", "Stop the usage data service",
          "Turns off the background service that gathers and uploads usage data.")
            .svc("DiagTrack", svc::DISABLED, svc::AUTO)
            .moderate()
            .pick(),
        t("privacy", "feedback", "Diagnostics", "No feedback questions",
          "Windows stops popping up questions asking how it is doing.")
            .reg(&[
                ("HKCU\\Software\\Microsoft\\Siuf\\Rules", "NumberOfSIUFInPeriod", D(0)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", "DoNotShowFeedbackNotifications", D(1)),
            ])
            .pick(),
        t("privacy", "data-tasks", "Diagnostics", "Turn off data collection tasks",
          "Switches off the scheduled jobs that collect app, disk and device usage for Microsoft.")
            .reg(&[("HKLM\\SOFTWARE\\Policies\\Microsoft\\SQMClient\\Windows", "CEIPEnable", D(0))])
            .tasks(&[
                "\\Microsoft\\Windows\\Application Experience\\Microsoft Compatibility Appraiser",
                "\\Microsoft\\Windows\\Application Experience\\ProgramDataUpdater",
                "\\Microsoft\\Windows\\Customer Experience Improvement Program\\Consolidator",
                "\\Microsoft\\Windows\\Customer Experience Improvement Program\\UsbCeip",
                "\\Microsoft\\Windows\\Autochk\\Proxy",
                "\\Microsoft\\Windows\\DiskDiagnostic\\Microsoft-Windows-DiskDiagnosticDataCollector",
                "\\Microsoft\\Windows\\Feedback\\Siuf\\DmClient",
                "\\Microsoft\\Windows\\Feedback\\Siuf\\DmClientOnScenarioDownload",
            ])
            .moderate()
            .pick(),
        t("privacy", "tailored", "Diagnostics", "No tailored experiences",
          "Microsoft stops using your diagnostic data to pick tips and offers for you.")
            .reg(&[
                ("HKCU\\Software\\Policies\\Microsoft\\Windows\\CloudContent", "DisableTailoredExperiencesWithDiagnosticData", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Privacy", "TailoredExperiencesWithDiagnosticDataEnabled", D(0)),
            ])
            .off(&[("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Privacy", "TailoredExperiencesWithDiagnosticDataEnabled", D(1))])
            .pick(),
        t("privacy", "error-reporting", "Diagnostics", "Turn off error reporting",
          "Crashes are no longer reported to Microsoft.")
            .reg(&[("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Error Reporting", "Disabled", D(1))])
            .moderate()
            .warn("Can also stop the crash files that show which mod or app crashed."),
        t("privacy", "advertising-id", "Ads and suggestions", "Turn off the advertising ID",
          "Apps can no longer use a shared ID to show you targeted ads.")
            .reg(&[
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\AdvertisingInfo", "DisabledByGroupPolicy", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo", "Enabled", D(0)),
            ])
            .off(&[("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo", "Enabled", D(1))])
            .pick(),
        t("privacy", "suggested-apps", "Ads and suggestions", "Stop suggested apps installing",
          "Windows stops quietly adding promoted apps and games to Start.")
            .reg(&[
                (CDM_SILENT.0, CDM_SILENT.1, D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "PreInstalledAppsEnabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "OemPreInstalledAppsEnabled", D(0)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\CloudContent", "DisableWindowsConsumerFeatures", D(1)),
            ])
            .off(&[
                (CDM_SILENT.0, CDM_SILENT.1, D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "PreInstalledAppsEnabled", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "OemPreInstalledAppsEnabled", D(1)),
            ])
            .pick(),
        t("privacy", "start-suggestions", "Ads and suggestions", "No suggestions in Start and Settings",
          "Removes promoted apps, account nags and suggested content from Start and Settings.")
            .reg(&[
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SystemPaneSuggestionsEnabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-338388Enabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-338393Enabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-353694Enabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-353696Enabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "Start_IrisRecommendations", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "Start_AccountNotifications", D(0)),
            ])
            .off(&[
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SystemPaneSuggestionsEnabled", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-338388Enabled", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-338393Enabled", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-353694Enabled", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-353696Enabled", D(1)),
            ])
            .pick(),
        t("privacy", "tips", "Ads and suggestions", "No tips and set-up nags",
          "Stops the tips, the welcome tour after updates and the finish setting up your device screen.")
            .reg(&[
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-338389Enabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-310093Enabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SoftLandingEnabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\UserProfileEngagement", "ScoobeSystemSettingEnabled", D(0)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\CloudContent", "DisableSoftLanding", D(1)),
            ])
            .off(&[
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-338389Enabled", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-310093Enabled", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SoftLandingEnabled", D(1)),
            ])
            .pick(),
        t("privacy", "lock-screen-ads", "Ads and suggestions", "No ads on the lock screen",
          "Removes the fun facts and promotions drawn over the lock screen picture.")
            .reg(&[
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "RotatingLockScreenOverlayEnabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-338387Enabled", D(0)),
            ])
            .off(&[
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "RotatingLockScreenOverlayEnabled", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SubscribedContent-338387Enabled", D(1)),
            ])
            .pick(),
        t("privacy", "explorer-ads", "Ads and suggestions", "No ads in File Explorer",
          "Stops File Explorer showing offers for OneDrive and Microsoft 365.")
            .reg(&[(ADV_SYNC.0, ADV_SYNC.1, D(0))])
            .off(&[(ADV_SYNC.0, ADV_SYNC.1, D(1))])
            .pick(),
        t("privacy", "suggestion-toasts", "Ads and suggestions", "No suggestion notifications",
          "Windows stops sending notifications that suggest ways to use it.")
            .reg(&[("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Notifications\\Settings\\Windows.SystemToast.Suggested", "Enabled", D(0))])
            .pick(),
        t("privacy", "activity-history", "Activity and search", "Turn off activity history",
          "Windows stops keeping and uploading a timeline of the apps and files you used.")
            .reg(&[
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\System", "EnableActivityFeed", D(0)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\System", "PublishUserActivities", D(0)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\System", "UploadUserActivities", D(0)),
            ])
            .pick(),
        t("privacy", "web-search", "Activity and search", "No web results in search",
          "Start and taskbar search look only at this PC and stop sending what you type to Bing.")
            .reg(&[
                ("HKCU\\Software\\Policies\\Microsoft\\Windows\\Explorer", "DisableSearchBoxSuggestions", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Search", "BingSearchEnabled", D(0)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", "ConnectedSearchUseWeb", D(0)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", "DisableWebSearch", D(1)),
            ])
            .moderate()
            .warn("File Explorer's search box also stops listing your past searches.")
            .pick(),
        t("privacy", "search-highlights", "Activity and search", "No search highlights",
          "Removes the daily pictures and trending topics from the search box.")
            .reg(&[
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\SearchSettings", "IsDynamicSearchBoxEnabled", D(0)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", "EnableDynamicContentInWSB", D(0)),
            ])
            .off(&[("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\SearchSettings", "IsDynamicSearchBoxEnabled", D(1))])
            .pick(),
        t("privacy", "cloud-search", "Activity and search", "Don't search your online accounts",
          "Search stops including OneDrive, Outlook and other cloud content.")
            .reg(&[
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\SearchSettings", "IsMSACloudSearchEnabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\SearchSettings", "IsAADCloudSearchEnabled", D(0)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", "AllowCloudSearch", D(0)),
            ])
            .off(&[
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\SearchSettings", "IsMSACloudSearchEnabled", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\SearchSettings", "IsAADCloudSearchEnabled", D(1)),
            ]),
        t("privacy", "typing-data", "Activity and search", "Keep typing and handwriting private",
          "Windows stops learning from what you type and write to build a personal dictionary.")
            .reg(&[
                ("HKCU\\Software\\Microsoft\\InputPersonalization", "RestrictImplicitInkCollection", D(1)),
                ("HKCU\\Software\\Microsoft\\InputPersonalization", "RestrictImplicitTextCollection", D(1)),
                ("HKCU\\Software\\Microsoft\\InputPersonalization\\TrainedDataStore", "HarvestContacts", D(0)),
                ("HKCU\\Software\\Microsoft\\Input\\TIPC", "Enabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Personalization\\Settings", "AcceptedPrivacyPolicy", D(0)),
            ])
            .off(&[
                ("HKCU\\Software\\Microsoft\\InputPersonalization", "RestrictImplicitInkCollection", D(0)),
                ("HKCU\\Software\\Microsoft\\InputPersonalization", "RestrictImplicitTextCollection", D(0)),
                ("HKCU\\Software\\Microsoft\\InputPersonalization\\TrainedDataStore", "HarvestContacts", D(1)),
                ("HKCU\\Software\\Microsoft\\Input\\TIPC", "Enabled", D(1)),
                ("HKCU\\Software\\Microsoft\\Personalization\\Settings", "AcceptedPrivacyPolicy", D(1)),
            ])
            .moderate()
            .pick(),
        t("privacy", "app-tracking", "Activity and search", "Don't track app launches",
          "Windows stops counting which apps you open.")
            .reg(&[(ADV_TRACK.0, ADV_TRACK.1, D(0))])
            .off(&[(ADV_TRACK.0, ADV_TRACK.1, D(1))])
            .moderate()
            .warn("Start stops showing your most used apps."),
        t("privacy", "location", "Activity and search", "Turn off location",
          "No app or Windows feature can ask where this PC is.")
            .reg(&[("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\LocationAndSensors", "DisableLocation", D(1))])
            .moderate()
            .warn("Weather, maps and Find my device stop knowing where you are."),
        t("privacy", "clipboard-sync", "Activity and search", "Keep the clipboard on this PC",
          "What you copy is never synced to your other devices.")
            .reg(&[("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\System", "AllowCrossDeviceClipboard", D(0))])
            .moderate(),
        t("privacy", "recall", "AI features", "Turn off Recall",
          "Windows never takes snapshots of your screen to search later.")
            .reg(&[
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsAI", "DisableAIDataAnalysis", D(1)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsAI", "AllowRecallEnablement", D(0)),
                ("HKCU\\Software\\Policies\\Microsoft\\Windows\\WindowsAI", "DisableAIDataAnalysis", D(1)),
            ])
            .reboot()
            .pick(),
        t("privacy", "click-to-do", "AI features", "Turn off Click to Do",
          "Removes the AI actions that read what is on your screen.")
            .reg(&[
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsAI", "DisableClickToDo", D(1)),
                ("HKCU\\Software\\Policies\\Microsoft\\Windows\\WindowsAI", "DisableClickToDo", D(1)),
            ])
            .pick(),
        t("privacy", "copilot", "AI features", "Turn off Copilot in Windows",
          "Hides Copilot from the taskbar and turns off the built-in Copilot.")
            .reg(&[
                ("HKCU\\Software\\Policies\\Microsoft\\Windows\\WindowsCopilot", "TurnOffWindowsCopilot", D(1)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsCopilot", "TurnOffWindowsCopilot", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowCopilotButton", D(0)),
            ])
            .moderate()
            .pick(),
        // -------------------------------------------------------- Performance
        t("performance", "game-mode", "Gaming", "Game Mode on",
          "Windows gives the game you are playing first call on the processor and holds back updates.")
            .reg(&[
                ("HKCU\\Software\\Microsoft\\GameBar", "AutoGameModeEnabled", D(1)),
                ("HKCU\\Software\\Microsoft\\GameBar", "AllowAutoGameMode", D(1)),
            ])
            .pick(),
        t("performance", "background-recording", "Gaming", "No background game recording",
          "Stops Game Bar recording the last minutes of play in the background.")
            .reg(&[
                ("HKCU\\System\\GameConfigStore", "GameDVR_Enabled", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\GameDVR", "AppCaptureEnabled", D(0)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\GameDVR", "AllowGameDVR", D(0)),
            ])
            .off(&[
                ("HKCU\\System\\GameConfigStore", "GameDVR_Enabled", D(1)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\GameDVR", "AppCaptureEnabled", D(1)),
            ])
            .moderate()
            .warn("Game Bar's record button stops working too.")
            .pick(),
        t("performance", "sticky-keys", "Gaming", "No Sticky Keys pop-up",
          "Pressing Shift five times in a game no longer throws up the Sticky Keys box.")
            .reg(&[
                ("HKCU\\Control Panel\\Accessibility\\StickyKeys", "Flags", S("506")),
                ("HKCU\\Control Panel\\Accessibility\\ToggleKeys", "Flags", S("58")),
                ("HKCU\\Control Panel\\Accessibility\\Keyboard Response", "Flags", S("122")),
            ])
            .off(&[
                ("HKCU\\Control Panel\\Accessibility\\StickyKeys", "Flags", S("510")),
                ("HKCU\\Control Panel\\Accessibility\\ToggleKeys", "Flags", S("62")),
                ("HKCU\\Control Panel\\Accessibility\\Keyboard Response", "Flags", S("126")),
            ])
            .pick(),
        t("performance", "mouse-acceleration", "Gaming", "Turn off mouse acceleration",
          "The pointer moves the same distance however fast you move the mouse. Applies after you sign in again.")
            .reg(&[
                ("HKCU\\Control Panel\\Mouse", "MouseSpeed", S("0")),
                ("HKCU\\Control Panel\\Mouse", "MouseThreshold1", S("0")),
                ("HKCU\\Control Panel\\Mouse", "MouseThreshold2", S("0")),
            ])
            .off(&[
                ("HKCU\\Control Panel\\Mouse", "MouseSpeed", S("1")),
                ("HKCU\\Control Panel\\Mouse", "MouseThreshold1", S("6")),
                ("HKCU\\Control Panel\\Mouse", "MouseThreshold2", S("10")),
            ])
            .moderate(),
        t("performance", "gpu-scheduling", "Gaming", "Graphics card schedules its own work",
          "Lets the graphics card manage its own memory queue, which can cut input delay.")
            .reg(&[("HKLM\\SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers", "HwSchMode", D(2))])
            .off(&[("HKLM\\SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers", "HwSchMode", D(1))])
            .moderate()
            .reboot(),
        t("performance", "high-plan", "Power", "High performance power plan",
          "The processor stays at full speed instead of slowing down to save power.")
            .special(Special::HighPlan)
            .moderate()
            .warn("Uses more power and runs a little warmer."),
        t("performance", "hibernate-off", "Power", "Turn off hibernation",
          "Deletes the hibernation file, which frees space about a third the size of your memory.")
            .special(Special::Hibernate)
            .moderate()
            .warn("Fast startup and the Hibernate option go away too."),
        t("performance", "fast-startup-off", "Power", "Turn off fast startup",
          "Shut down fully restarts Windows, which clears stuck drivers and lets updates finish.")
            .reg(&[("HKLM\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Power", "HiberbootEnabled", D(0))])
            .off(&[("HKLM\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Power", "HiberbootEnabled", D(1))]),
        t("performance", "power-throttling-off", "Power", "Turn off power throttling",
          "Background apps keep full speed instead of being slowed down to save power.")
            .reg(&[("HKLM\\SYSTEM\\CurrentControlSet\\Control\\Power\\PowerThrottling", "PowerThrottlingOff", D(1))])
            .moderate()
            .reboot()
            .warn("Laptops run down their battery faster."),
        t("performance", "startup-delay", "Responsiveness", "Start apps at sign-in without waiting",
          "Apps set to start with Windows open at once instead of after a pause.")
            .reg(&[
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Serialize", "StartupDelayInMSec", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Serialize", "WaitForIdleState", D(0)),
            ]),
        t("performance", "menu-delay", "Responsiveness", "Faster menus",
          "Sub-menus open after a tenth of a second instead of almost half a second.")
            .reg(&[("HKCU\\Control Panel\\Desktop", "MenuShowDelay", S("100"))])
            .off(&[("HKCU\\Control Panel\\Desktop", "MenuShowDelay", S("400"))]),
        t("performance", "global-timer", "Responsiveness", "Shared high-precision timer",
          "When a game asks for a finer timer, the whole PC gets it, as it did before Windows 10 2004.")
            .reg(&[("HKLM\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\kernel", "GlobalTimerResolutionRequests", D(1))])
            .advanced()
            .reboot()
            .warn("Uses a little more power while a game runs."),
        t("performance", "sysmain-off", "Background services", "Stop app preloading",
          "Turns off the service that loads apps into memory before you open them. Helps on hard disks.")
            .svc("SysMain", svc::DISABLED, svc::AUTO)
            .moderate(),
        t("performance", "search-index-off", "Background services", "Stop the search index",
          "Turns off the service that keeps an index of your files for search.")
            .svc("WSearch", svc::DISABLED, svc::AUTO)
            .advanced()
            .warn("Start and File Explorer search get slow and stop looking inside files."),
        t("performance", "background-apps-off", "Background services", "Stop Store apps running in the background",
          "Store apps only run while their window is open.")
            .reg(&[("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\AppPrivacy", "LetAppsRunInBackground", D(2))])
            .advanced()
            .warn("Apps like Phone Link and Mail stop sending notifications."),
        t("performance", "print-spooler-off", "Background services", "Stop the print service",
          "Turns off printing support for PCs that never print.")
            .svc("Spooler", svc::DISABLED, svc::AUTO)
            .moderate()
            .warn("Printing and Print to PDF stop working."),
        // ------------------------------------------------------------ Updates
        t("updates", "no-restart", "Windows Update", "Never restart while you are signed in",
          "Updates wait for you to restart, so a game or a stream is never cut off.")
            .reg(&[("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "NoAutoRebootWithLoggedOnUsers", D(1))])
            .pick(),
        t("updates", "no-drivers", "Windows Update", "No drivers from Windows Update",
          "Windows Update stops replacing your drivers, so the graphics driver you chose stays put.")
            .reg(&[
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", "ExcludeWUDriversInQualityUpdate", D(1)),
                ("HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DriverSearching", "SearchOrderConfig", D(0)),
            ])
            .off(&[("HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DriverSearching", "SearchOrderConfig", D(1))])
            .pick(),
        t("updates", "notify-download", "Windows Update", "Ask before downloading updates",
          "Windows tells you when updates are ready and waits for you to start them.")
            .reg(&[
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "NoAutoUpdate", D(0)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU", "AUOptions", D(2)),
            ])
            .moderate()
            .warn("Security fixes wait until you install them."),
        t("updates", "defer-features", "Windows Update", "Hold big updates for a year",
          "The yearly Windows version update arrives a year after release, once it has settled.")
            .reg(&[
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", "DeferFeatureUpdates", D(1)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", "DeferFeatureUpdatesPeriodInDays", D(365)),
            ])
            .moderate()
            .warn("Insider builds ignore this."),
        t("updates", "defer-quality", "Windows Update", "Hold monthly updates for a week",
          "Monthly updates install a week late, after early problems are found.")
            .reg(&[
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", "DeferQualityUpdates", D(1)),
                ("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", "DeferQualityUpdatesPeriodInDays", D(7)),
            ])
            .moderate(),
        t("updates", "no-msrt", "Windows Update", "Skip the monthly removal tool",
          "Windows Update stops downloading the Malicious Software Removal Tool each month.")
            .reg(&[("HKLM\\SOFTWARE\\Policies\\Microsoft\\MRT", "DontOfferThroughWUAU", D(1))])
            .moderate(),
        t("updates", "no-sharing", "Downloads", "Don't share updates over the internet",
          "Updates download only from Microsoft and are never uploaded to other people's PCs.")
            .reg(&[("HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows\\DeliveryOptimization", "DODownloadMode", D(0))])
            .pick(),
        t("updates", "store-auto-off", "Downloads", "Store apps update only when you ask",
          "The Microsoft Store stops updating apps by itself.")
            .reg(&[("HKLM\\SOFTWARE\\Policies\\Microsoft\\WindowsStore", "AutoDownload", D(2))])
            .moderate()
            .warn("Store apps fall behind until you update them."),
        t("updates", "reserved-storage-off", "Downloads", "Give back the space kept for updates",
          "Frees the space, about 7 GB, that Windows keeps aside for installing updates.")
            .special(Special::ReservedStorage)
            .moderate()
            .warn("A big update may then ask you to free space first."),
        // ------------------------------------------------------------ Windows
        t("windows", "file-extensions", "File Explorer", "Show file extensions",
          "File names show their type, like .exe or .pdf, so a fake document is easy to spot.")
            .reg(&[(ADV_EXT.0, ADV_EXT.1, D(0))])
            .off(&[(ADV_EXT.0, ADV_EXT.1, D(1))])
            .pick(),
        t("windows", "hidden-files", "File Explorer", "Show hidden files",
          "File Explorer shows files and folders marked hidden.")
            .reg(&[("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "Hidden", D(1))])
            .off(&[("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "Hidden", D(2))]),
        t("windows", "open-this-pc", "File Explorer", "Open File Explorer on This PC",
          "File Explorer opens on your drives instead of Home.")
            .reg(&[("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "LaunchTo", D(1))]),
        t("windows", "no-recent", "File Explorer", "Don't list recent files in Home",
          "Home stops showing the files and folders you opened lately.")
            .reg(&[
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer", "ShowRecent", D(0)),
                ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer", "ShowFrequent", D(0)),
            ])
            .moderate(),
        t("windows", "classic-menu", "File Explorer", "Classic right-click menu",
          "Right-click shows the full old menu straight away. Applies after you sign in again.")
            .reg(&[("HKCU\\Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\\InprocServer32", "", S(""))])
            .off_keys(&[CLASSIC_MENU])
            .moderate()
            .warn("Menu mods that style the new menu don't style this one."),
        t("windows", "widgets-off", "Taskbar and Start", "Turn off Widgets",
          "Removes the news and weather board and stops it running in the background.")
            .reg(&[("HKLM\\SOFTWARE\\Policies\\Microsoft\\Dsh", "AllowNewsAndInterests", D(0))])
            .pick(),
        t("windows", "end-task", "Taskbar and Start", "End task on the taskbar",
          "Adds End task to a taskbar button's right-click menu, to close a stuck app.")
            .reg(&[("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\TaskbarDeveloperSettings", "TaskbarEndTask", D(1))]),
        t("windows", "search-box-off", "Taskbar and Start", "Hide the taskbar search box",
          "Removes the search box from the taskbar. Start search still works.")
            .reg(&[("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Search", "SearchboxTaskbarMode", D(0))]),
        t("windows", "task-view-off", "Taskbar and Start", "Hide the Task View button",
          "Removes the Task View button. Win+Tab still opens it.")
            .reg(&[("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowTaskViewButton", D(0))])
            .off(&[("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowTaskViewButton", D(1))]),
        t("windows", "spotlight-icon-off", "Taskbar and Start", "Hide the Learn about this picture icon",
          "Removes the Spotlight icon from the desktop.")
            .reg(&[("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", "{2cc5ca98-6485-489a-920e-b3e88a6ccce3}", D(1))]),
        t("windows", "long-paths", "System", "Allow long file paths",
          "Apps that support it can use paths longer than 260 characters, which deep project folders need.")
            .reg(&[("HKLM\\SYSTEM\\CurrentControlSet\\Control\\FileSystem", "LongPathsEnabled", D(1))])
            .off(&[("HKLM\\SYSTEM\\CurrentControlSet\\Control\\FileSystem", "LongPathsEnabled", D(0))])
            .pick(),
        t("windows", "verbose-status", "System", "Say what Windows is doing at start and shut down",
          "Start-up and shut-down screens name the step they are on, so a hang is easy to spot.")
            .reg(&[("HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", "VerboseStatus", D(1))]),
        t("windows", "crash-details", "System", "Show details on the crash screen",
          "The blue crash screen shows the error codes, not just a sad face.")
            .reg(&[("HKLM\\SYSTEM\\CurrentControlSet\\Control\\CrashControl", "DisplayParameters", D(1))]),
    ]
}

const CDM_SILENT: (&str, &str) = ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", "SilentInstalledAppsEnabled");
const ADV_SYNC: (&str, &str) = ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowSyncProviderNotifications");
const ADV_TRACK: (&str, &str) = ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "Start_TrackProgs");
const ADV_EXT: (&str, &str) = ("HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "HideFileExt");

// ---------------------------------------------------------------- built-in apps

struct App {
    id: String,
    group: &'static str,
    name: &'static str,
    desc: &'static str,
    /// Appx package names. Empty for OneDrive, which has its own uninstaller.
    pkgs: &'static [&'static str],
    pick: bool,
    risk: Risk,
}

fn app(id: &str, group: &'static str, name: &'static str, desc: &'static str, pkgs: &'static [&'static str]) -> App {
    App { id: format!("apps.{id}"), group, name, desc, pkgs, pick: false, risk: Risk::Safe }
}

impl App {
    fn pick(mut self) -> Self {
        self.pick = true;
        self
    }
    fn moderate(mut self) -> Self {
        self.risk = Risk::Moderate;
        self
    }
    fn item(&self) -> Item {
        let mut i = Item::new(self.id.clone(), "apps", self.group, self.name, self.desc, Kind::Action)
            .risk(self.risk)
            .admin()
            .warn(if self.pkgs.is_empty() {
                "Comes back only by installing it again from microsoft.com."
            } else {
                "Comes back only by installing it again from the Microsoft Store."
            });
        if self.pick {
            i = i.pick();
        }
        i
    }
}

fn apps() -> Vec<App> {
    vec![
        app("clipchamp", "Extras", "Clipchamp", "Microsoft's online video editor.", &["Clipchamp.Clipchamp"]).pick(),
        app("news", "Extras", "Microsoft News", "The news reader app.", &["Microsoft.BingNews"]).pick(),
        app("weather", "Extras", "Weather", "Microsoft's weather app.", &["Microsoft.BingWeather"]),
        app("solitaire", "Extras", "Solitaire Collection", "Card games with ads.", &["Microsoft.MicrosoftSolitaireCollection"]).pick(),
        app("tips", "Extras", "Tips", "Tips on using Windows.", &["Microsoft.Getstarted"]).pick(),
        app("get-help", "Extras", "Get Help", "Microsoft's support chat app.", &["Microsoft.GetHelp"]).pick(),
        app("feedback-hub", "Extras", "Feedback Hub", "Sends feedback to Microsoft.", &["Microsoft.WindowsFeedbackHub"]).pick(),
        app("maps", "Extras", "Maps", "Offline maps.", &["Microsoft.WindowsMaps"]),
        app("power-automate", "Extras", "Power Automate", "Desktop automation for office work.", &["Microsoft.PowerAutomateDesktop"]).pick(),
        app("bing-search", "Extras", "Bing Search", "The Bing search app.", &["Microsoft.BingSearch"]).pick(),
        app("dev-home", "Extras", "Dev Home", "Microsoft's retired developer dashboard.", &["Microsoft.Windows.DevHome"]).pick(),
        app("family", "Extras", "Microsoft Family", "Parental controls app.", &["MicrosoftCorporationII.MicrosoftFamily"]).pick(),
        app("cortana", "Extras", "Cortana", "Microsoft's retired voice assistant.", &["Microsoft.549981C3F5F10"]).pick(),
        app("office-hub", "Microsoft apps", "Microsoft 365 Copilot", "The hub that advertises Microsoft 365.", &["Microsoft.MicrosoftOfficeHub"]).pick(),
        app("copilot", "Microsoft apps", "Copilot", "Microsoft's AI chat app.", &["Microsoft.Copilot", "Microsoft.Windows.Ai.Copilot.Provider"]).moderate(),
        app("outlook", "Microsoft apps", "Outlook (new)", "The new Outlook mail app.", &["Microsoft.OutlookForWindows"]).moderate(),
        app("mail-calendar", "Microsoft apps", "Mail and Calendar", "The old mail app Microsoft retired.", &["microsoft.windowscommunicationsapps"]).pick(),
        app("teams", "Microsoft apps", "Microsoft Teams", "The free Teams chat app.", &["MSTeams", "MicrosoftTeams"]).moderate(),
        app("todo", "Microsoft apps", "Microsoft To Do", "Lists and reminders.", &["Microsoft.Todos"]).moderate(),
        app("sticky-notes", "Microsoft apps", "Sticky Notes", "Notes on the desktop.", &["Microsoft.MicrosoftStickyNotes"]).moderate(),
        app("sound-recorder", "Microsoft apps", "Sound Recorder", "Records audio.", &["Microsoft.WindowsSoundRecorder"]).moderate(),
        app("clock", "Microsoft apps", "Clock", "Alarms, timers and focus sessions.", &["Microsoft.WindowsAlarms"]).moderate(),
        app("movies-tv", "Microsoft apps", "Movies & TV", "The old video player.", &["Microsoft.ZuneVideo"]),
        app("phone-link", "Online services", "Phone Link", "Links an Android phone or iPhone to this PC.", &["Microsoft.YourPhone"]).moderate(),
        app("quick-assist", "Online services", "Quick Assist", "Lets someone control this PC to help you.", &["MicrosoftCorporationII.QuickAssist"]).moderate(),
        app("onedrive", "Online services", "OneDrive", "Microsoft's cloud storage sync. Files already on this PC stay in your OneDrive folder.", &[]).moderate(),
    ]
}

fn installed_appx() -> Option<Vec<String>> {
    let all = if sys::is_elevated() { " -AllUsers" } else { "" };
    let o = proc::powershell(&format!("Get-AppxPackage{all} | ForEach-Object {{ $_.Name }}")).ok()?;
    if o.code != 0 {
        return None;
    }
    Some(proc::decode(&o.stdout).lines().map(|l| l.trim().to_ascii_lowercase()).filter(|l| !l.is_empty()).collect())
}

fn onedrive_exe() -> Option<std::path::PathBuf> {
    [
        "%LOCALAPPDATA%\\Microsoft\\OneDrive\\OneDrive.exe",
        "%ProgramFiles%\\Microsoft OneDrive\\OneDrive.exe",
        "%ProgramFiles(x86)%\\Microsoft OneDrive\\OneDrive.exe",
    ]
    .iter()
    .map(|p| std::path::PathBuf::from(sys::expand(p)))
    .find(|p| p.is_file())
}

/// The OneDrive uninstaller: the copy in the OneDrive folder (newest version
/// first), else the one Windows ships.
fn onedrive_setup() -> Option<(std::path::PathBuf, bool)> {
    for (base, all_users) in [
        ("%LOCALAPPDATA%\\Microsoft\\OneDrive", false),
        ("%ProgramFiles%\\Microsoft OneDrive", true),
        ("%ProgramFiles(x86)%\\Microsoft OneDrive", true),
    ] {
        let dir = std::path::PathBuf::from(sys::expand(base));
        let mut found: Vec<std::path::PathBuf> = std::fs::read_dir(&dir)
            .into_iter()
            .flatten()
            .flatten()
            .map(|e| e.path().join("OneDriveSetup.exe"))
            .filter(|p| p.is_file())
            .collect();
        found.sort();
        if let Some(p) = found.pop() {
            return Some((p, all_users));
        }
    }
    ["%SystemRoot%\\System32\\OneDriveSetup.exe", "%SystemRoot%\\SysWOW64\\OneDriveSetup.exe"]
        .iter()
        .map(|p| std::path::PathBuf::from(sys::expand(p)))
        .find(|p| p.is_file())
        .map(|p| (p, false))
}

fn app_state(a: &App, list: Option<&[String]>) -> State {
    if a.pkgs.is_empty() {
        return if onedrive_exe().is_some() { State::toggle(&a.id, false) } else { State::missing(&a.id, "Not installed") };
    }
    let Some(list) = list else {
        return State { id: a.id.clone(), available: true, note: Some("Can't list apps".into()), ..Default::default() };
    };
    if a.pkgs.iter().any(|p| list.iter().any(|n| n.eq_ignore_ascii_case(p))) {
        State::toggle(&a.id, false)
    } else {
        State::missing(&a.id, "Not installed")
    }
}

fn remove_app(ctx: &Ctx, a: &App) -> Result<Done> {
    if a.pkgs.is_empty() {
        if onedrive_exe().is_none() {
            return Ok(Done::note("not installed"));
        }
        let (setup, all_users) = onedrive_setup().ok_or_else(|| anyhow!("OneDrive's uninstaller is missing"))?;
        if ctx.dry_run {
            return Ok(Done::note("dry run"));
        }
        let s = setup.to_string_lossy().into_owned();
        let args: &[&str] = if all_users { &["/uninstall", "/allusers"] } else { &["/uninstall"] };
        let o = proc::run(&s, args)?;
        if onedrive_exe().is_some() {
            bail!("OneDrive is still installed (uninstaller exited {})", o.code);
        }
        return Ok(Done::note("removed"));
    }
    if ctx.dry_run {
        return Ok(Done::note("dry run"));
    }
    let names = a.pkgs.iter().map(|p| format!("'{p}'")).collect::<Vec<_>>().join(",");
    let all = if ctx.elevated { "-AllUsers" } else { "" };
    let deprov = if ctx.elevated {
        "Get-AppxProvisionedPackage -Online | Where-Object { $n -contains $_.DisplayName } | ForEach-Object { Remove-AppxProvisionedPackage -Online -PackageName $_.PackageName | Out-Null };"
    } else {
        ""
    };
    let script = format!(
        "$ErrorActionPreference='Stop'; $n=@({names}); \
         foreach($x in $n) {{ Get-AppxPackage {all} -Name $x | Remove-AppxPackage {all} }}; \
         {deprov} \
         foreach($x in $n) {{ if (Get-AppxPackage -Name $x) {{ throw \"$x is still installed\" }} }}"
    );
    let o = proc::powershell(&script)?;
    if o.code != 0 {
        let msg = o.text();
        let first = msg.lines().map(str::trim).find(|l| !l.is_empty()).unwrap_or("Windows refused");
        bail!("{first}");
    }
    Ok(Done::note("removed"))
}

// ---------------------------------------------------------------- toggle state

const HIGH_PLAN: &str = "8c5e7fda-e8bf-4a96-9a85-a6e23a8c635c";
const BALANCED_PLAN: &str = "381b4222-f694-41f0-9685-ff5bb260df2e";

/// First GUID in a piece of text, lower case.
fn find_guid(s: &str) -> Option<String> {
    let b = s.as_bytes();
    if b.len() < 36 {
        return None;
    }
    'outer: for i in 0..=b.len() - 36 {
        for (j, &c) in b[i..i + 36].iter().enumerate() {
            let ok = if matches!(j, 8 | 13 | 18 | 23) { c == b'-' } else { c.is_ascii_hexdigit() };
            if !ok {
                continue 'outer;
            }
        }
        return Some(s[i..i + 36].to_ascii_lowercase());
    }
    None
}

fn active_plan() -> Option<String> {
    let o = proc::run("powercfg.exe", &["/getactivescheme"]).ok()?;
    find_guid(&o.text())
}

fn has_plan(guid: &str) -> bool {
    proc::run("powercfg.exe", &["/list"]).map(|o| o.text().to_ascii_lowercase().contains(guid)).unwrap_or(false)
}

fn hibernate_off() -> bool {
    reg::get_u32("HKLM\\SYSTEM\\CurrentControlSet\\Control\\Power", "HibernateEnabled") == Some(0)
}

const RS_GET: &str = "(Get-WindowsReservedStorageState -ErrorAction Stop).ReservedStorageState";

fn reserved_storage() -> Result<String, String> {
    let o = proc::powershell(RS_GET).map_err(|e| e.to_string())?;
    let s = proc::decode(&o.stdout).trim().to_string();
    if o.code != 0 || s.is_empty() {
        return Err("Can't read it".into());
    }
    Ok(s)
}

/// Ok(None): the part is not on this PC. Err: it cannot be read.
fn op_state(op: &Op) -> Result<Option<bool>, String> {
    match op {
        Op::Reg(rows) => Ok(Some(reg::table_matches(rows))),
        Op::Svc(name, on, _) => Ok(svc::start_type(name).map(|s| s == *on)),
        Op::Tasks(paths) => {
            let states: Vec<bool> = paths.iter().filter_map(|p| task::enabled(p)).collect();
            Ok(if states.is_empty() { None } else { Some(states.iter().all(|e| !e)) })
        }
        Op::Special(Special::HighPlan) => {
            if !has_plan(HIGH_PLAN) {
                return Ok(None);
            }
            Ok(Some(active_plan().as_deref() == Some(HIGH_PLAN)))
        }
        Op::Special(Special::Hibernate) => Ok(Some(hibernate_off())),
        Op::Special(Special::ReservedStorage) => {
            if !sys::is_elevated() {
                return Err("Needs admin to read".into());
            }
            reserved_storage().map(|s| Some(s.eq_ignore_ascii_case("Disabled")))
        }
    }
}

fn tweak_state(tw: &Tweak) -> State {
    let mut on = Vec::new();
    for op in &tw.ops {
        match op_state(op) {
            Ok(Some(v)) => on.push(v),
            Ok(None) => {}
            Err(note) => return State { id: tw.id.clone(), available: true, note: Some(note), ..Default::default() },
        }
    }
    if on.is_empty() {
        return State::missing(&tw.id, "Not on this PC");
    }
    State::toggle(&tw.id, on.iter().all(|v| *v))
}

// ---------------------------------------------------------------- apply and revert

/// Record every missing parent key above `full` (top first), so a revert
/// removes the empty keys this tweak made. `reg::set` records `full` itself.
fn note_new_parents(tx: &mut Txn, full: &str) {
    let parts: Vec<&str> = full.split('\\').collect();
    for depth in 2..parts.len() {
        let k = parts[..depth].join("\\");
        if !reg::key_exists(&k) {
            tx.push(Undo::RegKeyCreated { key: k });
        }
    }
}

fn check(o: proc::Out, what: &str) -> Result<()> {
    if o.code != 0 {
        let t = o.text();
        let first = t.lines().map(str::trim).find(|l| !l.is_empty()).unwrap_or("");
        bail!("{what} failed ({}): {first}", o.code);
    }
    Ok(())
}

fn apply_op(tx: &mut Txn, op: &Op) -> Result<()> {
    match op {
        Op::Reg(rows) => {
            for (k, n, v) in rows.iter() {
                match v.to_val() {
                    Some(val) => {
                        note_new_parents(tx, k);
                        reg::set(tx, k, n, &val)?;
                    }
                    None => reg::del(tx, k, n)?,
                }
            }
        }
        Op::Svc(name, on, _) => {
            svc::set_start(tx, name, *on)?;
            if *on == svc::DISABLED && !tx.dry_run {
                svc::stop(name);
            }
        }
        Op::Tasks(paths) => {
            for p in paths.iter() {
                task::set_enabled(tx, p, false)?;
            }
        }
        Op::Special(Special::HighPlan) => {
            let prev = active_plan().ok_or_else(|| anyhow!("can't read the active power plan"))?;
            if prev == HIGH_PLAN {
                return Ok(());
            }
            if !has_plan(HIGH_PLAN) {
                bail!("this PC hides the High performance plan");
            }
            tx.push(Undo::Cmd { exe: "powercfg.exe".into(), args: vec!["/setactive".into(), prev] });
            if !tx.dry_run {
                check(proc::run("powercfg.exe", &["/setactive", HIGH_PLAN])?, "powercfg")?;
            }
        }
        Op::Special(Special::Hibernate) => {
            if hibernate_off() {
                return Ok(());
            }
            tx.push(Undo::Cmd { exe: "powercfg.exe".into(), args: vec!["/hibernate".into(), "on".into()] });
            if !tx.dry_run {
                check(proc::run("powercfg.exe", &["/hibernate", "off"])?, "powercfg")?;
            }
        }
        Op::Special(Special::ReservedStorage) => {
            if reserved_storage().map(|s| s.eq_ignore_ascii_case("Disabled")).unwrap_or(false) {
                return Ok(());
            }
            tx.push(Undo::Cmd { exe: "powershell.exe".into(), args: ps_args("Set-WindowsReservedStorageState -State Enabled -ErrorAction Stop") });
            if !tx.dry_run {
                check(proc::powershell("Set-WindowsReservedStorageState -State Disabled -ErrorAction Stop")?, "Reserved storage")?;
            }
        }
    }
    Ok(())
}

fn ps_args(script: &str) -> Vec<String> {
    ["-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-Command", script].iter().map(|s| s.to_string()).collect()
}

fn apply_tweak(ctx: &Ctx, tw: &Tweak) -> Result<Done> {
    let mut tx = ctx.journal.begin(&tw.id, ctx.dry_run);
    let mut result = Ok(());
    for op in &tw.ops {
        result = apply_op(&mut tx, op);
        if result.is_err() {
            break;
        }
    }
    // Keep what did change, even after a failure, so a revert can undo it.
    let saved = tx.commit();
    result?;
    saved?;
    Ok(Done { reboot: tw.reboot, note: ctx.dry_run.then(|| "dry run".to_string()), ..Default::default() })
}

/// Turn off a tweak that has no undo record: write the Windows defaults.
fn default_op(tw: &Tweak, op: &Op) -> Result<()> {
    match op {
        Op::Reg(rows) => {
            for (k, n, _) in rows.iter() {
                let off = tw.off.iter().find(|(ok, on, _)| ok.eq_ignore_ascii_case(k) && on.eq_ignore_ascii_case(n));
                match off.and_then(|(_, _, v)| v.to_val()) {
                    Some(val) => reg::set_raw(k, n, &val)?,
                    None => reg::del_raw(k, n)?,
                }
            }
        }
        Op::Svc(name, _, default) => {
            if svc::exists(name) {
                svc::set_start_raw(name, *default)?;
                if *default == svc::AUTO {
                    svc::start(name);
                }
            }
        }
        Op::Tasks(paths) => {
            for p in paths.iter() {
                if task::enabled(p) == Some(false) {
                    task::set_enabled_raw(p, true)?;
                }
            }
        }
        Op::Special(Special::HighPlan) => {
            if active_plan().as_deref() == Some(HIGH_PLAN) {
                check(proc::run("powercfg.exe", &["/setactive", BALANCED_PLAN])?, "powercfg")?;
            }
        }
        Op::Special(Special::Hibernate) => {
            if hibernate_off() {
                check(proc::run("powercfg.exe", &["/hibernate", "on"])?, "powercfg")?;
            }
        }
        Op::Special(Special::ReservedStorage) => {
            check(proc::powershell("Set-WindowsReservedStorageState -State Enabled -ErrorAction Stop")?, "Reserved storage")?;
        }
    }
    Ok(())
}

fn revert_tweak(ctx: &Ctx, tw: &Tweak) -> Result<Done> {
    if ctx.journal.has(&tw.id)? {
        let mut d = ctx.journal.undo(&tw.id, ctx.dry_run)?;
        if !ctx.dry_run {
            for op in &tw.ops {
                if let Op::Svc(name, _, _) = op {
                    if svc::start_type(name) == Some(svc::AUTO) {
                        svc::start(name);
                    }
                }
            }
        }
        d.reboot = tw.reboot;
        return Ok(d);
    }
    if ctx.dry_run {
        return Ok(Done::note("dry run: would write the Windows defaults"));
    }
    for op in &tw.ops {
        default_op(tw, op)?;
    }
    for k in tw.off_keys {
        reg::del_tree_raw(k)?;
    }
    Ok(Done { reboot: tw.reboot, note: Some("set back to the Windows default".into()), ..Default::default() })
}

// ---------------------------------------------------------------- provider

pub struct Tweaks {
    tweaks: Vec<Tweak>,
    apps: Vec<App>,
}

pub fn provider() -> Box<dyn Provider> {
    Box::new(Tweaks { tweaks: catalog(), apps: apps() })
}

impl Provider for Tweaks {
    fn name(&self) -> &'static str {
        "tweaks"
    }

    fn items(&self) -> Vec<Item> {
        self.tweaks.iter().map(Tweak::item).chain(self.apps.iter().map(App::item)).collect()
    }

    fn scan(&self, _ctx: &Ctx, ids: &[String]) -> Vec<State> {
        let want = |id: &str| ids.is_empty() || ids.iter().any(|i| i == id);
        let need_apps = self.apps.iter().any(|a| want(&a.id) && !a.pkgs.is_empty());
        std::thread::scope(|s| {
            let list = need_apps.then(|| s.spawn(installed_appx));
            let jobs: Vec<_> = self.tweaks.iter().filter(|t| want(&t.id)).map(|t| s.spawn(move || tweak_state(t))).collect();
            let mut out: Vec<State> = jobs.into_iter().filter_map(|j| j.join().ok()).collect();
            let list = list.and_then(|h| h.join().ok()).flatten();
            for a in self.apps.iter().filter(|a| want(&a.id)) {
                out.push(app_state(a, list.as_deref()));
            }
            out
        })
    }

    fn apply(&self, ctx: &Ctx, id: &str) -> Result<Done> {
        if let Some(tw) = self.tweaks.iter().find(|t| t.id == id) {
            return apply_tweak(ctx, tw);
        }
        if let Some(a) = self.apps.iter().find(|a| a.id == id) {
            return remove_app(ctx, a);
        }
        bail!("unknown item {id}")
    }

    fn revert(&self, ctx: &Ctx, id: &str) -> Result<Done> {
        if let Some(tw) = self.tweaks.iter().find(|t| t.id == id) {
            return revert_tweak(ctx, tw);
        }
        if self.apps.iter().any(|a| a.id == id) {
            bail!("Removed apps come back only from the Microsoft Store");
        }
        bail!("unknown item {id}")
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn ids_are_unique_and_paged() {
        let p = provider();
        let items = p.items();
        let mut seen = std::collections::HashSet::new();
        for i in &items {
            assert!(seen.insert(i.id.clone()), "duplicate id {}", i.id);
            assert!(i.id.starts_with(&format!("{}.", i.page)), "{} is not on page {}", i.id, i.page);
            assert!(["privacy", "performance", "apps", "updates", "windows"].contains(&i.page));
            assert!(i.desc.ends_with('.'), "{} needs a full sentence", i.id);
        }
        assert!(items.len() > 70);
    }

    #[test]
    fn registry_rows_are_well_formed() {
        for tw in catalog() {
            for op in &tw.ops {
                if let Op::Reg(rows) = op {
                    for (k, _, _) in rows.iter() {
                        assert!(k.starts_with("HKLM\\") || k.starts_with("HKCU\\"), "{}: {k}", tw.id);
                        assert!(!k.ends_with('\\') && !k.contains("\\\\"), "{}: {k}", tw.id);
                    }
                }
            }
            for (k, n, _) in tw.off {
                let listed = tw.ops.iter().any(|o| matches!(o, Op::Reg(rows) if rows.iter().any(|(rk, rn, _)| rk == k && rn == n)));
                assert!(listed, "{}: off row {k}\\{n} is not one of its rows", tw.id);
            }
        }
    }

    #[test]
    fn finds_guids() {
        let s = "Power Scheme GUID: 381B4222-F694-41F0-9685-FF5BB260DF2E  (Balanced)";
        assert_eq!(find_guid(s).as_deref(), Some(BALANCED_PLAN));
        assert_eq!(find_guid("none here"), None);
    }

    #[test]
    fn scan_reads_without_changing() {
        let ctx = Ctx::new(true);
        let p = provider();
        let st = p.scan(&ctx, &["windows.file-extensions".into(), "privacy.recall".into()]);
        assert_eq!(st.len(), 2);
        assert!(st.iter().all(|s| s.applied.is_some()));
    }
}
