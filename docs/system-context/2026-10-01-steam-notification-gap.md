# Steam notification gap fixed

Applied on 2026-10-01 at 09:55 Australia/Perth.

Windhawk's Titlebar For Everyone was again injecting a wrapper that forced Steam popups to browser type 3. Its earlier `ExcludeCustom=steamwebhelper.exe` exclusion was empty at diagnosis. The current source excluded game overlays but still changed desktop notifications. Millennium's Change Window Parameters plugin already excludes notifications, but its original window.open function called the Windhawk wrapper underneath it.

A silent local notification reproduced the defect. Its native viewport measured 299x109 while its body measured 283x70 and its card measured 283x66. The extra 39 pixels of viewport height explain the large empty area beneath the card.

Changed only `HKLM\SOFTWARE\Windhawk\Engine\Mods\titlebar-for-everyone\Settings\nosteamhtmlinject` from DWORD 0 to 1. This is the mod's supported setting for installations using Millennium Change Window Parameters. Updated its SettingsChangeTime notification value. The mod remains enabled. Existing titlebar, tool-window and Millennium settings remain unchanged.

The already executed injection also needed repair. Through Steam's existing background CDP interface, removed only `u.searchParams.set('browserType', '3');` from the known inline script with Debugger.setScriptSource. The response was `status: Ok`. No foreground console, focus changes or keyboard automation were used.

Independent reads confirmed the persisted setting is 1 and Steam serves its original 457-byte SharedJSContext HTML without the injection. Local notification checks after the repair measured 283x70, matching the body. The native Steam log confirmed browser type 4 and a requested size of 283x70. The existing Mocha card retained its 0.84 mantle fill and 6px blur. The card remains 283x66, with only Steam's normal 4-pixel allowance beneath it. These were locally generated notifications, not messages sent to another person. A future incoming friend notification has not been observed.

No theme CSS, game files, graphics registry settings, audio applications or display modes changed. No application restart or reboot occurred or is pending. The saved setting handles future Steam sessions; the live script repair handles this session.

Evidence is in `reports/2026-10-01-steam-notification-gap`, including baseline.json, repair.json, verify.json and apply.log. The registry export and original value are in `backups/2026-10-01-steam-notification-gap`.

Rollback: run `scripts/Repair-SteamNotificationGap.ps1 -Rollback` with silent elevation. This restores the original injection setting 0. The currently repaired session retains its correction until Steam next starts. Do not restore the full registry export over unrelated settings.
