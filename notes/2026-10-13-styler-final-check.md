# Windhawk Styler final check (2026-10-13)

Checked on the live Windhawk UI unless noted. Windhawk Styler 2.0.46 is loaded.

| Request | Status | Evidence |
| --- | --- | --- |
| Spinner arrows inside the rounded box | Done (2.0.45) | 3 number fields. Handler inset 4px from the input border box on all sides (3px inside the border), 20px wide, 13px radius. |
| Save settings bar inset from the card edges | Done (2.0.45) | 12px from the card's left and right edges. |
| Icons centered in their buttons | Done (2.0.45, 2.0.46) | Styler settings: 4 icon-only buttons, 0px off. Styler details: back arrow, 0px. Better Dialogs details: 3 icon-only buttons, 0px. Tab overflow trigger: 1.25px high before, 0.22px after, measured on the real button in a probe. Not seen with tabs overflowing. |
| Gap between share and open-in-browser | Done (2.0.45) | 6px on the Better Dialogs page. The Styler page has neither button. |
| Accent on modified markers and links | Done (2.0.45) | Accent variables are #89B4FA. 143 accent markers on the Styler settings page. No default-blue colour on Home, Explore, About or the Styler settings page. One zero-size, invisible shadow on an antd button ripple. |
| Title bar right-click menu | Done (standard look). | Translucent Flyouts no longer applies to windhawk-ui.exe (`notes\2026-10-13-titlebar-menu-standard.md`). Right-click, icon click and Alt+Space open it, and Escape closes it. Solid #1E1E2E body. No menu item was selected. |
| DeepSeek helper route | Done | Native subagent on `opencode-go/deepseek-v4.1-flash` completed a read-only probe. |

## Other changes in this check

- `scripts\styler-maintenance.ps1` pointed at `work\windhawk-styler\tauri20` (2.0.34). `-Install` would have copied that old source over the live one. It now points at `work\styler-release\mods\local\windhawk-styler`. `-Audit` passes: installed source matches the canonical source, library hash matches the build, and the legacy UI is not selected.
- `reports\2026-10-13-styler-polish\titlebar-check.ps1` and its three screenshots.

## Open

- Translucent menu colour: the translucent-flyouts thread is on 0.6.16 (modern acrylic, Mocha 80%). It needs a decision. Options are in `notes\2026-10-13-translucent-flyouts-menu-colour-attempts.md`.
- Push: `styler-tauri-release` has 8 commits that origin/main lacks, and origin/main has 6 that this branch lacks. A plain push is rejected. Nothing is pushed.
