# Initial compact Start menu

2026-10-09, 5:59 AM AWST. Owner's new screenshot showed that the previous 1.0.2 fix still left the initial menu large and hid its search box. This supersedes the initial-state claims in `2026-10-09-start-search-adaptive.md`.

Measured configuration: start-menu-size still imposed Height=500 and MinHeight=500. Source inspection showed that Everything hid its whole overlay at idle, including the only remaining search box after suppressing the stock box.

Installed local Everything 1.0.3, `local@start-everything_1.0.3_710102.dll`, built from the existing clean-source fork. Removed the MaxHeight storyboard approach. The mod now directly sets FrameRoot Height=160 idle and Height=500 searching, with MinHeight=100. Changed start-menu-size's height setting from 500 to 0 to stop its fixed-height override. Width=750 and SearchHost searchWidth=750/searchHeight=500 remain as before. Theme MaxHeight=640 and the corrected footer glyph remain as before.

The idle overlay stays visible and accepts input. Only its results body and search hints collapse. Clearing the search leaves the search box available and returns to the compact height. Size handling runs through the existing reveal, hide, activation, close, and attach paths. Teardown restores the frame's previous height and minimum height. Frame naming, colors, blur, and borders stay intact. No polling timer or process restart was added.

Independent checks confirmed version 1.0.3 in the registry, height=0 in start-menu-size, and the new DLL loaded with Start Menu Styler in StartMenuExperienceHost. Owner confirmed the three size/search-box states. The layout log independently records ActualHeight=160 idle, ActualHeight=500 searching, and ActualHeight=160 after clearing. Owner's screenshot confirms the compact search box. One remaining issue was that the idle overlay covered the native power controls underneath; version 1.0.4 limits that overlay to 64 DIP at the top while idle so those controls can render and receive clicks.

The layout-change diagnostic writes desired and actual frame heights to `C:\ProgramData\Windhawk\Engine\ModsWritable\local@start-everything-layout.log`. It only writes on state or actual-height changes, without recording queries or results.

Backup: `backups/2026-10-09/start-search-initial/`. Script: `scripts/2026-10-09-start-search-initial.ps1`, supporting `-Install`, `-Audit`, and `-Rollback`. Run mutations elevated. Rollback restores the previous mod source and registry keys for local Everything, start-menu-size, and Start Menu Styler. Receipt: `reports/2026-10-09-start-search-initial/receipt.json`.

DLL SHA256: `E8886AE3239EB996DAC3FB733B0D67ABA761B2E6B0991FB377F8E251E436A8FA`. No reboot test performed. No restart pending.

## Final footer correction

Version 1.0.4 installed at 6:02 AM AWST. Idle overlay Height=64 and VerticalAlignment=Top leave the original native navigation/power controls uncovered underneath the search box. Searching clears the overlay height back to Auto and stretches it across the results area. Independent live screenshot `reports/2026-10-09-start-search-footer/idle-verified.png` shows the compact menu with the search box and all six separate action icons below. The layout log confirms ActualHeight=160. The new DLL is independently enumerated in StartMenuExperienceHost alongside Start Menu Styler. Power actions were not invoked because doing so would shut down, lock, or sign out of the user's active session.

Final build `local@start-everything_1.0.4_710103.dll`, SHA256 `B9D28B84E6A05AC20E5A94A315E0FA2620AA4B6623A8390137DDF00BD4E85E41`. Backup and reversible script: `backups/2026-10-09/start-search-footer/` and `scripts/2026-10-09-start-search-footer.ps1`. Its rollback restores 1.0.3. The initial-state script rollback restores the earlier 1.0.2 and size-mod override. Final receipt: `reports/2026-10-09-start-search-footer/receipt.json`.
