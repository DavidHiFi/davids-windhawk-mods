# Taskbar progress indicator — research & option menu

Date: 2026-10-15. Type: research, read-only. Nothing applied to settings. Related mod: `windows-11-taskbar-styler` (Catppuccin pill theme). Companion mockup: `reports\2026-10-15-taskbar-progress-indicator\mockup.html`.

## The question

When an app reports progress (ITaskbarList3), the taskbar button pill currently shows an accent-tinted bar that "keeps zooming across". User wants the progress indicator to look better — ideally "a regular progress thingy that goes across" instead of the zoom.

## What the element is

The zooming bar is the **WinUI `ProgressBar` named `ProgressIndicator`** that Windows 11 puts inside each taskbar button. The mod already restyles it — see live settings `controlStyles[7]`–`[11]`:

- **[7]** `ProgressBar#ProgressIndicator` — stretched to the full pill (Min/MaxWidth `BtnW-6`, Height = taskbar minus offsets, ColumnSpan=2, Opacity 1).
- **[8]** `> Grid#LayoutRoot` — BorderThickness 0, CornerRadius `$buttonRadius` (7), Canvas.ZIndex 1.
- **[9]** `Border#ProgressBarRoot > Border > Grid` — Height = Auto (escapes the native 3px template height).
- **[10]** `> Rectangle#ProgressBarTrack` — Fill = Transparent (track hidden).
- **[11]** `Grid#LayoutRoot@CommonStates > ... > Determinate / Indeterminate / Indeterminate2` rects — shared: StrokeThickness 1, RadiusX/Y 7, Fill = 35% AdaptiveAccent; Paused = #FAB387 @ 0.35.

So the color is already Catppuccin accent. The complaint is the **motion**, not the color.

## Why it zooms

The WinUI 2.x `ProgressBar` template (microsoft/microsoft-ui-xaml, `controls/dev/ProgressBar/ProgressBar.xaml`):

```
Grid#LayoutRoot                       ← one visual-state group "CommonStates":
   Normal, Determinate, Updating, UpdatingError, Error, Paused,
   Indeterminate, IndeterminateError, IndeterminatePaused
 > Border#ProgressBarRoot
    > Border (Clip = TemplateSettings.ClipRect)
       > Grid (Height = {TemplateBinding MinHeight}; native 3px)
          > Rectangle#ProgressBarTrack                  (1px, Fill = control Background)
          > Rectangle#DeterminateProgressBarIndicator   (grows from left)
          > Rectangle#IndeterminateProgressBarIndicator (animated)
          > Rectangle#IndeterminateProgressBarIndicator2(trailing, delayed, animated)
```

The `Indeterminate` state runs a `Storyboard` with `RepeatBehavior="Forever"`: bar 1 sweeps left→right over 1.5s (KeySpline 0.4,0,0.6,1) with a hold to 2.0s; the trailing bar 2 starts at 0.75s. The animation targets `(UIElement.RenderTransform).(CompositeTransform.TranslateX)` — it lives **inside the control template**.

**Consequence:** no property setter can retime, slow, or reshape the motion. The only real ways to change it: replace the whole ControlTemplate (experimental, not practical through the styler) or make the moving bars invisible and show something static instead.

## What the styler can and can't do

- Visual states live on `Grid#LayoutRoot` (the template root), **not** on the ProgressBar control. State-scoped rules must target `... > Grid#LayoutRoot@StateName` or deeper. You cannot state-scope the control's own geometry (e.g. `Height@Indeterminate` on the control won't fire) — so a "hairline when busy, pill when determinate" hybrid is out.
- Per-state fill colors are cheap and reliable: `Fill@Paused`, `Fill@Error`, `Fill@IndeterminatePaused`, `Fill@IndeterminateError`. Note: the current config does **not** cover `@IndeterminatePaused`/`@IndeterminateError`, so those states currently fall back to plain accent.
- The styler supports `@GroupName` scoping too (config uses `@CommonStates`).

**Not possible / not practical:** retiming or slowing the native animation (template storyboard); a progress ring (the control is a ProgressBar, not a ring — hiding the bars and drawing a ring would need a template swap); per-app progress colors (one shared template); geometry state-hybrids (states on LayoutRoot, see above).

## Option menu (textual-mode blocks, ready to paste)

### Option A — Static wash (recommended)

Kills the zoom completely. Busy = calm 35% accent wash over the whole pill, icon stays visible; determinate = solid accent fill growing over a faint track.

Replace `[11]` with two targets:

```
Microsoft.UI.Xaml.Controls.ProgressBar#ProgressIndicator > Grid#LayoutRoot > Border#ProgressBarRoot > Border > Grid > Rectangle#DeterminateProgressBarIndicator
StrokeThickness = 1
RadiusX = $buttonRadius
RadiusY = $buttonRadius
Fill := <SolidColorBrush Color="{ThemeResource AdaptiveAccent}" Opacity="0.9" />
Fill@Paused := <SolidColorBrush Color="#FAB387" Opacity="0.9" />
Fill@Error := <SolidColorBrush Color="#F38BA8" Opacity="0.9" />
```

```
Microsoft.UI.Xaml.Controls.ProgressBar#ProgressIndicator > Grid#LayoutRoot > Border#ProgressBarRoot > Border > Grid > Rectangle#IndeterminateProgressBarIndicator, Microsoft.UI.Xaml.Controls.ProgressBar#ProgressIndicator > Grid#LayoutRoot > Border#ProgressBarRoot > Border > Grid > Rectangle#IndeterminateProgressBarIndicator2
Fill = Transparent
```

Add a new target (static wash while busy):

```
Microsoft.UI.Xaml.Controls.ProgressBar#ProgressIndicator > Grid#LayoutRoot@Indeterminate
Background := <SolidColorBrush Color="{ThemeResource AdaptiveAccent}" Opacity="0.35" />
Background@IndeterminatePaused := <SolidColorBrush Color="#FAB387" Opacity="0.35" />
Background@IndeterminateError := <SolidColorBrush Color="#F38BA8" Opacity="0.35" />
```

Optional two-tone determinate — change `[10]` track:

```
Grid#LayoutRoot > Border#ProgressBarRoot > Border > Grid > Rectangle#ProgressBarTrack
Fill := <SolidColorBrush Color="{ThemeResource AdaptiveAccent}" Opacity="0.12" />
```

Icon visibility is safe: the icon's Canvas.ZIndex (3) sits above LayoutRoot (1) per the existing config.

### Option B — Hairline loader (keeps motion, subtle)

Closest to "a regular progress thingy going across", but as a 3px shimmer pinned to the pill's bottom edge; the native sweep continues but reads as a whisper instead of a zoom. Edits to [7]–[11]:

- **[7]**: Height := 3 (or 4), add `VerticalAlignment = 2` (Bottom), bottom margin ~`{{$taskbarBottomOffset-2}}` to pin at the pill's bottom edge; keep Min/MaxWidth `BtnW-6`.
- **[9]**: Height = 3 (instead of Auto).
- **[8]**: CornerRadius := 1.5.
- **[10]**: faint accent track 0.12 (or transparent).
- **[11]**: all three rects → solid accent 0.9, RadiusX/Y = 1.5.

Caveat: exact pinning margins need a 5-minute live A/B tweak — flag it.

### Option C — Two-tone bold (minimal diff, zoom stays)

Keep the current full-pill geometry and native motion, just fix contrast: `[10]` track to faint accent 0.12; `[11]` fills to solid accent 0.9 and add `Fill@Error := #F38BA8 0.9`. Zoom remains — user hates it — listed for completeness.

### Option D — Hide it

`Microsoft.UI.Xaml.Controls.ProgressBar#ProgressIndicator` → `Visibility = 1` (Collapsed), or Opacity = 0. Minimal, zero noise, but loses all progress information.

## Recommendation

**Option A** — it directly removes what the user dislikes (the zoom) while keeping state information: a calm accent wash when indeterminate, a proper growing fill when determinate, distinct paused/error tints. **Option B** is the pick if they want to keep a sense of motion. **D** if they just want it gone.

## Verification plan (for later, when applying)

1. `reg export` the mod key into `backups\<date>\`.
2. Paste the option's textual-mode block into the mod UI (Textual mode) and save — the mod hot-reloads on SettingsChangeTime.
3. Verify by screenshot: determinate state via a file copy to the taskbar'd app, indeterminate via a download (e.g. browser or Edge download).
4. Revert path: restore the exported `.reg` or re-paste the previous textual block (recorded in the receipt).

## Sources

- Live registry: `HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler` + `/Settings` (dumped 2026-10-15; verified again by the successor session — [7]–[11] targets match this note exactly).
- Template: https://raw.githubusercontent.com/microsoft/microsoft-ui-xaml/main/controls/dev/ProgressBar/ProgressBar.xaml
- Themeresources: https://raw.githubusercontent.com/microsoft/microsoft-ui-xaml/main/controls/dev/ProgressBar/ProgressBar_themeresources.xaml
- Mockup: `reports\2026-10-15-taskbar-progress-indicator\mockup.html`
- Handoff brief: `t3-handoff\1d1f81eb-b0db-4347-8833-91a0c879556a.md`

**Caution:** the `reports\2026-10-09-styler-stability\upstream-styler-reference.md` hit for `ProgressBar#progressBar > Grid > Border#DeterminateRoot` is the *Notification Center* progress bar — a different control; don't confuse it with the taskbar's `ProgressIndicator`.
