# Terminal/cmd window fully transparent, no acrylic — second mod revert (2026-10-13)

## Bug

Evening of 2026-10-13 (~21:00): a freshly opened cmd.exe window (hosted by Windows
Terminal — console delegation is "let Windows decide") was completely see-through
with no blur anywhere: body and title strip showed the desktop sharply. Terminal
profile settings (`opacity` 0, `useAcrylic` false) make Terminal apply its own
`ACCENT_ENABLE_TRANSPARENTGRADIENT` accent; the mod is supposed to override that
with the rule-11 acrylic blur.

## Root cause

The translucent-windows mod had been reverted from the round-5 state
(**1.8.3 / build 256343**, source `70B64AF…`) to **stock 1.8.2 / build 598230**
(source `0F8801…`) at **11:58:47** the same morning. Stock 1.8.2 bails out of
`EnableBlurBehind` for `CASCADIA_HOSTING_WINDOW_CLASS` (line 787), so Terminal
windows got no accent from the mod and fell back to Terminal's own fully
transparent one. Settings were untouched — only the binary and ModsSource
flipped, and `SettingsChangeTime` was **not** bumped (same signature as the
unexplained 2026-10-11 revert; no thread transcript mentions it, no engine log
exists to attribute it). Anything launched before 11:58 kept the accent applied
at creation, which is why the damage only surfaced hours later in a new window.

## Fix (2026-10-13 ~21:45)

`scripts\2026-10-13-translucent-windows-revert2.ps1 -Action Install` (elevated):
backed up the reverted state to
`backups\2026-10-13\translucent-windows-revert2\` (reg export + stock source
copy), copied the reviewed fork source back to
`C:\ProgramData\Windhawk\ModsSource\translucent-windows.wh.cpp`, pointed
`LibraryFileName` at the still-on-disk, hash-verified
`translucent-windows_1.8.3_256343.dll` (x64 `D284A5E3…` matches the round-5
receipt — no recompile), bumped `SettingsChangeTime`. No recompile, no engine
restart, protected chain untouched.

## Verification

- Registry readback: 1.8.3 / 256343, Disabled 0, source hash `70B64AF…`.
- Module census (elevated, `module-census.log`): all live explorer and conhost
  processes plus a newly spawned WindowsTerminal (pid 36964) map
  `translucent-windows_1.8.3_256343.dll`.
- Visual (`terminal-after-fix.png`): Terminal window shows tinted acrylic blur
  across body and title strip alike (caption colour hook active), prompt text
  crisp on top; client-area mean RGB (42, 44, 60) vs 0,0,0 for the broken
  transparent state.

## Rollback

Elevated: `…\2026-10-13-translucent-windows-revert2.ps1 -Action Rollback`
(restores 1.8.2/598230 from the backup reg + source copy), or import
`backups\2026-10-13\translucent-windows-revert2\translucent-windows-before-revert2.reg`
and bump `SettingsChangeTime`.

## Open items

- The reverter is still unidentified — second occurrence of the same silent
  pattern (new stock build compiled, ModsSource overwritten, no marker bump).
  If it recurs, capture `LibraryFileName` + `SettingsChangeTime` + DLL mtimes
  before touching anything and check which threads are live at that minute.
- agent-coop was unreachable from this sandbox (state dir denied); other
  threads should read this note before touching translucent-windows.
- A "JavaScript error … Cannot find module H:\Windhawk Configuration\.windhawk\…"
  toast was on screen during verification — not caused by this change (no JS
  touched); likely the live Start-menu mod thread's local build.
