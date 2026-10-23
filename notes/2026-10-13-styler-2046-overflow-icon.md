# Windhawk Styler 2.0.46: tab overflow icon centered (2026-10-13)

The last open item from 2.0.45. The tab overflow trigger (`.ant-tabs-nav-more`, the antd "more tabs" button) sat about 1.25px high relative to its center. It shows only when the mod's tabs overflow, so the 2.0.45 sweep could not see it.

| Step | Measured |
| --- | --- |
| Before (2.0.45, button forced visible) | icon center minus button center: dy -1.25, dx 0. Button 46x38 |
| Rejected: `.ant-tabs-nav-more` with inline-flex centering | dy 0, but button height fell to 30px. Layout changed, so rejected |
| Shipped: `.ant-tabs-nav-more>span.anticon{vertical-align:middle !important;}` | dy 0.22, dx 0. Button still 46x38 |

The before and shipped numbers come from a read-only CDP probe run by a DeepSeek V4.1 Flash subagent on the `opencode-go/` route. The probe restored the button's style and removed its test style afterwards.

## Change

- Source: `work\styler-release\mods\local\windhawk-styler\windhawk-styler.wh.cpp`. Version 2.0.46, one rule after the existing icon-button rules, with a one-line comment.
- Build: `Build.ps1` in the mod folder (Windhawk clang, 64-bit and 32-bit). The 64-bit DLL contains the rule.
- Commit: `work\styler-release`, "Windhawk Styler 2.0.46: center the tab overflow icon". Local only, not pushed.

## Install

- Script: `scripts\2026-10-13-styler-polish-2046.ps1 -Action Install`, run elevated through `Invoke-Elevated.ps1` (exit 0). Log: `backups\2026-10-13-elevated\` under System Configuration.
- Library: `local@windhawk-styler_2.0.46_122137.dll`, SHA256 `7C25D05C5943EC7865252E858B594723DA0EC627D3815D9C6FBEAED7B5EFF79A`.
- Installed source SHA256 `6B3F7378D6B4420C881D55A7A0BAF0B5BCD5A5EFA78DEE4F6EAC2E89F8D0A3A3`, matching the work copy.
- Backups and receipt: `backups\2026-10-13\styler-polish-2046\` (registry export, `installed-2.0.45.wh.cpp`, `receipt.json`).

## Verification

- Audit after install: version 2.0.46, library file and library hash match the receipt.
- Live UI, through CDP port 9333: the mod's rule is in the page's stylesheets (`hasRule: true`).
- A/B on a test button in the same CSS context: with an inline `vertical-align: baseline !important` override the icon sits at dy -3; with the mod rule it sits at dy 0.22. The test button was 30x28, so these numbers show the rule's effect, not the real button size. The real button's 0.22 comes from the probe above.
- The test element was removed (`removed: true`).

The Windhawk UI was on a page without tabs after the reinstall, so the real overflow button was not visible for a direct screenshot check.

## Rollback

`scripts\2026-10-13-styler-polish-2046.ps1 -Action Rollback` restores 2.0.45 from the receipt: the registry library name and version, and the installed source copy.

## Routing

The earlier DeepSeek helper failed on the `opencode/` (Zen) route with "Insufficient account funds". This run used the `opencode-go/` route, model `opencode-go/deepseek-v4.1-flash`, through the OpenCode subagent tool. It completed.
