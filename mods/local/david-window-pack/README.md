# David's Window Pack

Window dragging, resizing, keyboard snapping and monitor movement in one Windhawk mod. The keyboard helper runs elevated so the controls work on ordinary and administrator windows.

This mod combines AltSnap Drag, Snap Commander and Move Window to Monitor. Disable those separate mods, including the stock AltDrag mod, before enabling this pack. Close standalone AltSnap or AltDrag if it owns the same shortcuts.

## Install

1. Install [Windhawk](https://windhawk.net/).
2. Open [david-window-pack.wh.cpp](david-window-pack.wh.cpp) using GitHub's Raw button, or download it from this folder.
3. In Windhawk, choose Create new mod, paste the complete source and compile it.
4. Configure the combined settings page. Allow the elevated helper when Windows requests administrator permission.

Fresh editor installations start with the defaults in the source. They do not automatically import settings from the separate mods.

Windhawk's Explore page uses its official catalog. The source is available here while the catalog submission is under review. The mod will appear on Explore after that submission is merged and the catalog is deployed.

## Default controls

| Control | Action |
| --- | --- |
| Alt + left drag | Move a window from inside its client area. |
| Alt + right drag | Resize from the closest edge or corner. |
| Alt + F | Toggle maximize. |
| Alt + M | Minimize. |
| Alt + Shift + Q | Close the active window. |
| Alt + U / I / J / K | Top-left / top-right / bottom-left / bottom-right quarter. |
| Alt + Q / W / E / R | Left / right / top / bottom half. |
| Ctrl + Alt + arrows | Move between monitors. |

Every keyboard action is configurable. For Alt+arrow snapping, change the four half-screen keys to `left`, `right`, `up` and `down`. For Alt+Shift+arrow monitor movement, select Alt+Shift under Modifier Keys.

Monitor targets default to automatic spatial movement. Saved targets use monitor indices sorted by horizontal position, then vertical position. If a saved monitor is missing, movement falls back to the nearest monitor in the requested direction. With no destination in that direction, the window stays in place.

The elevated keyboard helper starts with Windhawk and exits when the mod unloads. Declining its elevation request prevents the keyboard helper from starting. The mod does not change UAC policy, registry graphics settings or display modes.

## Verification

Tested with Windhawk 1.7.3 on Windows 11. Ordinary windows and elevated Task Scheduler passed all four corner and half-screen shortcuts, monitor movement in every available direction, client-area dragging and resizing. Windhawk's elevated UI passed corner shortcuts, monitor movement, dragging and resizing.

The public source has the same C++ implementation as the tested installed build. Publication changes cover metadata, comments, documentation and license notices. Both x86 and x64 builds compile. Live checks used x64 applications.

To build from a PowerShell shell using Windhawk's bundled compiler:

```powershell
.\Build.ps1
```

Windhawk's editor remains the usual installation route. Build.ps1 produces DLLs without installing them or changing system settings.

## Credits and license

GPL-3.0. The full license is in [COPYING](COPYING). This mod's license overrides the collection's root MIT license for this folder.

- AltDrag by [m417z](https://github.com/m417z/my-windhawk-mods), based on [AltSnap by RamonUnch](https://github.com/RamonUnch/AltSnap) and AltDrag by Stefan Sundin. GPL-3.0.
- Snap Commander by [Asteski](https://github.com/Asteski). MIT under the Windhawk catalog's submission terms.
- Move Window to Monitor by [TomberWolf](https://github.com/TomberWolf). MIT.
- Integration and changes by DavidHiFi, with ChatGPT assistance. The MIT notices for the included components remain in the single-file source.
