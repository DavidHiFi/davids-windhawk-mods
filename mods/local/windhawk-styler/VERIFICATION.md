# Release verification

## 2.0.73 to 2.0.76 (2026-10-24)

Checked on Windows 11 in the live interface through its debugging port, from the installed mod.

- Select and drop-down menus are solid (`rgb(24, 24, 37)`, `backdrop-filter: none`) and the first option starts at the panel's top edge with no gap (2.0.73).
- In long drop-down lists, including the accent colour list, the scrollbar stays inside the rounded corners. Three long menus were measured with a corner hit test and an arc check, and no scrollbar point lies outside the curve (2.0.74, 2.0.75).
- Drop-down lists no longer get Windhawk's own square overlay bar on top of the list bar (2.0.75).
- On a mod's settings page the scrollbar sits on the card's right edge (0px gap, measured), no longer inset 8px. Every Windhawk overlay thumb has rounded ends in the list-bar colour (2.0.76).
- Not checked: date-picker drop-downs and right-click menus long enough to scroll, and the blur of the desktop behind the window as seen on screen.

## 2.0.71 and 2.0.72 (2026-10-24)

Checked on Windows 11 in the live interface through its debugging port, read-only: no clicks, no reloads, forced focus cleared after each read.

- The mod loads again in 2.0.71. The header had a second `@donateUrl` line, which stopped the mod from loading. The duplicate is gone.
- Focus and press on the Explore funnel use the accent instead of antd's blue. Forced focus gives the funnel icon `rgb(140, 182, 250)`.
- The focus ring uses `outline-offset: -1px`, so the 2px ring sits on the 1px control border with no gap at the top, bottom or arcs. The style block has the -1px rule once and the old `2px` offset zero times (2.0.72).
- Inputs and the select show a 2px solid ring at -1px offset.
- Not checked: pickers, checkboxes and radios, because none were on the page.
- Not fixed: the number input's focus glow still uses antd's blue at about 18% alpha, outside the ring. The funnel reports a 1px computed outline width while the rule says 2px. Not resolved.

## 2.0.66 to 2.0.70 (2026-10-24)

Checked on Windows 11 in the live interface through its debugging port, from the installed mod with no probe present.

- The caption strip and the body form one acrylic sheet: strip 27,27,38 and body 28,28,39 (2.0.66).
- The save bar blurs the settings rows behind it. The settings scroller paints an opaque rounded patch exactly under the bar, because the renderer only blurs text over an opaque backdrop. Measured bar background `rgba(24, 24, 37, 0.4)` with `blur(16px)`; rows behind it unreadable (2.0.69).
- In the Advanced settings dialog the process inclusion list and its info box join as one block: seam corners 0px, borders overlapping by 1px (2.0.70).
- Not checked: the blur of the desktop behind the window as seen on screen.

## 2.0.53 to 2.0.57 (2026-10-13)

Checked on Windows 11 with Windhawk 2.0.0-alpha.7, in the live interface through its debugging port and window captures.

- The mod card stays in place while its settings scroll. Its body scrolls instead, inset 8px from the right and 16px from the bottom, so the scrollbar never reaches the rounded corners. The header and tabs stay pinned (measured at top and bottom scroll, 2.0.56).
- The card's outline is an inset shadow on the card, not a pseudo-element, so it no longer scrolls into view mid-box (2.0.53).
- The scrollbar has no arrow buttons. `scrollbar-width` is no longer set on the scrolling areas, because Chromium ignores the `::-webkit-scrollbar` rules when it is set (2.0.54).
- The save bar sits 12px under the tabs at the top scroll position, and the first setting clears it by 12px (measured, 2.0.57). It had sat 36px down with free space above it in 2.0.56.

## 2.0.48 to 2.0.51 (2026-10-13)

Checked on Windows 11 with Windhawk 2.0.0-alpha.7, in the live interface through its debugging port.

- The save bar floats while the settings scroll. The mod had forced `position: relative` on it (it also matches `.ant-card`), which overrode the interface's own sticky positioning; 2.0.48/2.0.49 exclude it so stock sticky applies. 2.0.51 sticks it 12px below the scroll top so the rounded top corners and outline stay visible (measured 12px offset at 600px scroll).
- The page container has 12px bottom padding because the scroller leaves the card's bottom margin out of its scroll range (measured: 0px gap before, 12px after at max scroll).
- The Visual/Textual switch joins into one pill (outer ends 14px, middle square), as does the Installed/Other versions switch (outer ends 16px). The mod id chip is rounded.
- The save bar, pills and chip were first proven with a temporary page style, then measured again from the installed mod with no probe present.

## 2.0.47 (2026-10-13)

Checked on Windows 11 with Windhawk 2.0.0-alpha.7, in the live interface through its debugging port.

- Number spinners sit in an inset pill, 4px from the input edge and 20px wide.
- The save settings bar is 12px inside both card edges.
- Every icon-only button measured centered (0px offset). The tab overflow trigger was 1.25px high in 2.0.45 and 0.22px high in 2.0.46, measured on the real button.
- The open-in-browser and share buttons are 6px apart.
- The accent color marks modified settings, links and selections. No default Windhawk blue remained on the Home, Explore, About or Styler settings pages.
- The title bar right-click menu, icon click and Alt+Space each open the Windows window menu, and Escape closes it.

## 2.0.34

Windhawk Styler 2.0.34 was compiled and installed on Windows 11 with Windhawk 2.0.0-alpha.6.

Before the final release, eight real UI save cases exercised every setting, including opacity endpoints, blank optional values and title bar switches. Each reopened a themed interface with the expected saved values, no visible error notices, zero side/bottom frame gaps and zero GDI growth across repeated activation. A real caption drag recorded 137 different window positions without a separate caption window.

The final release preserves the accepted Acrylic appearance. A controlled native probe established the empty-region alpha path used by None. The legacy Blur option was removed after it rendered opaque on this Windows build. No further matrix was run after these final adjustments at the owner's request. No full-PC reboot or compatibility check against every Windhawk version was performed.

A disable/enable cycle verified that each toggle reopened fresh interface processes. Disable reopened without the injected style; Enable reopened with it. The mod was left enabled with the original 75% Acrylic settings. Ordinary app exit and recompilation do not request a disable relaunch.
