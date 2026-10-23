# Taskbar audio visualizer

Installed and verified on 2026-10-03 at about 02:58 Perth time. The local Windhawk fork is `local@tourne-table-av`, version 1.3.4. Source and build tools are in `Windhawk/tourne-fork`.

The original mod drew behind desktop icons and captured only the default Windows render endpoint. The fork creates a transparent, non-activating composition window over `Shell_TrayWnd`, follows that taskbar's monitor, and centers the bars vertically. The stock mod remains disabled. Its configuration was already disabled when this continuation began.

The system information block ends at x=481. The fork's 32 bars start at x=500 and occupy 158 pixels, with a maximum height of 26 pixels. Colors are Catppuccin Mocha mauve `#CBA6F7` and blue `#89B4FA`. The media controls occupy x=674..738, y=1407..1423 on the same main display. Taskbar icons and system statistics were not repositioned during this continuation.

Audio capture opens all available active render endpoints plus recording inputs explicitly named Loopback. It never opens microphone or general recording inputs. Each endpoint has its own sample buffer and sample rate. The fork combines the strongest level in each frequency band, so Matrix forwarding the same audio through multiple devices does not multiply its displayed level.

Nine paths opened successfully at 48 kHz, stereo, float32:

- Quantum ES 2 Main/Virtual 1 L/R and Virtual 2 L/R.
- VB-Audio Matrix Desktop, Discord, Media, Soundboard, and Recording outputs.
- Quantum ES 2 Loopback 1 L/R and Loopback 2 L/R. These provide an interface monitor path for ASIO audio.

The High Definition Audio Device Speakers endpoint returned `AUDCLNT_E_DEVICE_IN_USE`, `0x8889000A`. The fork leaves it alone. Direct capture of that exclusive endpoint is unavailable. Actual live signal was measured on the Desktop output and Quantum Loopback 1, and an earlier sample also measured Media output. Opening silent paths proves readiness, not that every application was separately exercised.

Verification included both architecture builds, installed DLL SHA256 comparisons, live window bounds, audio frame counts and nonzero peaks, and taskbar image inspection. A three-second capture had 30 distinct frames and showed moving bars. `WindowFromPoint` resolved the underlying taskbar at the bars, pinned applications, and tray, so the transparent overlay did not intercept those sampled points. No playback commands or synthetic clicks were sent.

The previous revision 1.3.2 averaged 0.29% total CPU use over five seconds and used 48.3 MB working memory. Revision 1.3.3 adds a 1 MiB rotating diagnostic log and the visible taskbar offset setting. Revision 1.3.4 makes both popup windows owned by the taskbar. A final check found that an independent topmost overlay could fall behind the taskbar after window activation. Ownership fixes that ordering without a polling workaround. The final ownership check passed for both windows, and the final animation capture had 30 distinct frames with 108 to 934 colored bar pixels per frame. Diagnostic files are in `reports/2026-10-03-tourne-av`.

The tray check showed Better Volume Mixer at x=2388..2416 and Network at x=2416..2440, with no overlap. The clock starts at x=2456. No taskbar styler settings changed in this continuation.

No system restart is pending. Ableton, Matrix, Discord, Windhawk's main engine, and Explorer were not restarted. Only the fork's own process was replaced when advancing its DLL revision.

## Configuration and rollback

`position.taskbarOffset` sets the bar group's horizontal position in logical pixels. This taskbar fork automatically chooses the main taskbar monitor and vertically centers its bars. The upstream desktop horizontal/vertical percentages and monitor index do not position the bars. Keyboard and drag movement are disabled in the installed profile. The installed spectrum uses the stereo bar shape and knee sensitivity curve.

The original registry configuration is in `backups/2026-10-03-tourne-av/stock.reg`. To undo the new installation, run `Windhawk/tourne-fork/Install.ps1 -Rollback` elevated. It disables the fork and imports that original configuration. This restores the original Disabled=1 state. `Install.ps1` without switches audits the installed state. No audio routing rollback is needed because the task changed no routing, driver, device setting, or audio application configuration.
