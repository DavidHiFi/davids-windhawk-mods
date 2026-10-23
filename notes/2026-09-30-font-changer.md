# Windhawk font changer fork

2026-09-30. Explorer Font Changer by DavidHiFi 1.0.1 is installed and enabled
with FiraCode Nerd Font. The original Explorer Font Changer 0.2 is disabled.
The source is published in DavidHiFi/davids-windhawk-mods on main at fc29259,
under mods/local/explorer-font-changer-davidhifi. The repository is public. The
original author, Gabriela Cristei, is credited in the mod README.

The original mod replaced every selected GDI font, including Windows symbol
fonts. That produced the boxed question marks in the desktop context menu. It
also left its replacement font selected when it called DeleteObject, used an
unbounded wcslen in its glow path, and covered only DrawTextW and DrawTextExW in
Explorer. The fork restores the original selected font before deleting its
temporary font, preserves symbol and emoji families and private-use runs, and
adds TextOut, ExtTextOut, text measurements, themed text, and both DirectWrite
layout creation paths. Glow is omitted. Existing DirectWrite format objects stay
unchanged. GDI font creation stays unchanged, so disabling the mod does not
leave replacement HFONT objects in controls.

## 1.0.1 fixes

Explorer wraps every formatted date in U+200E left-to-right marks, for example
`U+200E 30/09/U+200E 2026 U+200F U+200E 8:51 AM`. FiraCode Nerd Font has no
glyph for U+200E or U+200F, so 1.0.0's missing-glyph check kept the original
font for every date and time in Explorer. A pixel test showed GDI draws those
controls, and the other zero-width joiners, embeddings and variation selectors,
as nothing when the font lacks them. 1.0.1 ignores that list in the check.
Controls GDI draws visibly when missing, such as U+2066 to U+2069, still force
the original font. The raw results are in reports/2026-09-30/font-changer/format-chars.txt.

Legacy face names such as Segoe UI Semibold and Segoe UI Black carry their
weight in the name. 1.0.0 replaced the name and lost the weight. 1.0.1 keeps
it in GDI and DirectWrite. It also leaves vertical `@` faces alone, and keeps
the original font when GDI would realize the target name as a third font.

## Scope and limits

The installed targets are explorer.exe, StartMenuExperienceHost.exe,
ShellExperienceHost.exe, SearchHost.exe, ShellHost.exe, and SystemSettings.exe.
Other applications keep their own fonts. Some XAML controls can override fonts
after layout creation. Cached DirectWrite layouts may need to be recreated
before a setting change appears.

Winaero Tweaker changed the font for every application through FontSubstitutes
and WindowMetrics. The 2026-09-28 clipping fix removed both on purpose,
because a monospaced font in those places made fixed-size layouts in other
applications clip. This mod stays scoped to the shell for the same reason.

The system font registry still has blank file values for Segoe UI, Bold,
Italic, Bold Italic, Light and Semibold in HKLM Fonts. The files exist in
C:\Windows\Fonts. GDI therefore realizes a plain `Segoe UI` request as Arial,
while DirectWrite still finds Segoe UI. This predates the fork, likely from the
Winaero period, and is not changed here. Restoring those six values would
affect every application and needs its own approved change.

## Verification

Both production architectures compile with Windhawk's compiler. Forty-two API
checks pass, up from 31. New checks cover Explorer date strings, visible
missing controls, weight carry-over from bold and legacy names in GDI and
DirectWrite, vertical faces, unknown faces, and 10,000 nested and fallback
scopes with GDI objects unchanged at 9.

The hidden injected probe received the installed 1.0.1 DLL. It passed GDI text
and date substitution, DirectWrite substitution, icon glyph 1393 preservation,
private-use preservation, and 10,000 DrawText calls with GDI objects at 9.
Disabling the mod restored the original fonts, including the date string, and
re-enabling it restored the fork. Evidence is live-after-101.json,
live-off-101.json, update-101.log, api-tests-101.txt and final-state-101.json.

1.0.1 is mapped in Explorer, Start and ShellHost. SearchHost and
ShellExperienceHost are suspended by Windows while hidden and still hold the
1.0.0 revision 2 DLL. They load 1.0.1 the next time Windows starts them. No
process, engine or computer restart was used by this task. The PC was restarted
by the user at 18:16 before 1.0.1 was installed. No crash events for the shell
hosts were logged after the 1.0.0 install. The desktop context menu was not
opened by automation.

## Changes and rollback

Original mod Disabled changed from 0 to 1. The fork is enabled with font.name
FiraCode Nerd Font and the shell include list above. Its library is
local@explorer-font-changer-davidhifi_1.0.1_1.dll. Windows FontSubstitutes,
WindowMetrics and installed font files were not changed.

To stop the replacement, disable Explorer Font Changer by DavidHiFi in
Windhawk. To return to 1.0.0, import
backups/2026-09-30/font-changer/fork-1.0.0-revision2.reg elevated. The 1.0.0
DLLs stay in the engine Mods folders. To restore the original mod setup, run
scripts/2026-09-30-font-changer.ps1 -Rollback elevated. `-Audit` writes nothing.

The development checkout is work/font-changer/repo. The shared checkout at
H:\Windhawk Configuration\davids-windhawk-mods was fast-forwarded to fc29259.
Its uncommitted Better Volume Mixer Plus header edit was left in place. No pull
request was created.
