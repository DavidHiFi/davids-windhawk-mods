# Release verification

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
