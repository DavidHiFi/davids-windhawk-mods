// ==WindhawkMod==
// @id              translucent-flyouts
// @name            Translucent Flyouts
// @description     Acrylic, Mica and blur backgrounds, plus dark mode, for context menus, dropdowns and tooltips in every app
// @version         0.6.74
// @author          DavidHiFi, ALTaleX531, Mgg Sk
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @exclude         discord*.exe
// @exclude         Voicemeeter*.exe
// @exclude         Matrix*.exe
// @exclude         Stream Deck*.exe
// @exclude         dwm.exe
// @architecture    x86-64
// @architecture    x86
// @license         LGPL-3.0
// @compilerOptions -ld2d1 -ldwrite -ldwmapi -luxtheme -lcomctl32 -lgdi32 -luser32 -lole32 -ladvapi32 -lshlwapi -lversion -lmsimg32 -loleaut32 -luuid -lwindowscodecs
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// This mod is a port of TranslucentFlyouts (TFMain) by ALTaleX531 to the
// Windhawk mod platform. Upstream: https://github.com/ALTaleX531/TranslucentFlyouts
// (LGPL-3.0). The settings surface follows the TranslucentFlyouts configuration
// schema (as exposed by GID0317's translucent-flyouts-controller). No helper
// application is required: this mod implements the engine itself.

// ==WindhawkModSettings==
/*
- global:
  - effectType: modern_acrylic
    $name: Effect Type
    $description: Background effect for menus, dropdowns and tooltips. Each section can override it.
    $options:
      - none: None / Disabled
      - transparent: Fully Transparent
      - solid: Solid Color
      - blurred: Blurred
      - acrylic: Acrylic
      - modern_acrylic: Modern Acrylic (Recommended)
      - acrylic_bg: Acrylic Background Layer
      - mica_bg: Mica Background Layer
      - mica_variant: Mica Variant Background Layer
  - cornerType: small_round
    $name: Corner Style
    $description: Corner shape for menus, dropdowns and tooltips. Each section can override it.
    $options:
      - dont_change: Don't Change
      - sharp: Sharp Corners
      - large_round: Large Round Corners
      - small_round: Small Round Corners
  - enableDropShadow: false
    $name: Enable Drop Shadow
    $description: Shadow behind menus, dropdowns and tooltips. Each section can override it.
  - noBorderColor: false
    $name: Disable Border Color
    $description: Whether these pop-ups keep their system borders. Each section can override it.
  - enableThemeColorization: false
    $name: Enable Theme Colorization
    $description: Tint with the Windows accent color instead of the fixed border colors. Each section can override it.
  - darkModeThemeColorizationType: start_hover
    $name: Dark Accent Source
    $description: Which Windows accent slot tints the pop-ups in dark mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - lightModeThemeColorizationType: start_hover
    $name: Light Accent Source
    $description: Which Windows accent slot tints the pop-ups in light mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - darkModeBorderColor: "0xFF89B4FA"
    $name: Dark Border Color
    $description: Border color in dark mode, as 0xAARRGGBB.
  - lightModeBorderColor: "0xFF89B4FA"
    $name: Light Border Color
    $description: Border color in light mode, as 0xAARRGGBB.
  - darkModeGradientColor: "0xCC1E1E2E"
    $name: Dark Gradient Color
    $description: Acrylic tint in dark mode, as 0xAARRGGBB.
  - lightModeGradientColor: "0xCC1E1E2E"
    $name: Light Gradient Color
    $description: Acrylic tint in light mode, as 0xAARRGGBB.
  - enableMiniDump: true
    $name: Enable MiniDump
    $description: Saves a crash minidump if the mod fails.
  - disabled: false
    $name: Disabled
    $description: Turns off every effect in all sections.
  $name: Global

- dropDown:
  - effectType: use_global
    $name: Effect Type
    $description: Background effect for dropdowns. Pick Use Global Setting to follow the Global section.
    $options:
      - none: None
      - transparent: Fully Transparent
      - solid: Solid Color
      - blurred: Blurred
      - acrylic: Acrylic
      - modern_acrylic: Modern Acrylic
      - acrylic_bg: Acrylic Background Layer
      - mica_bg: Mica Background Layer
      - mica_variant: Mica Variant Background Layer
      - use_global: Use Global Setting
  - cornerType: use_global
    $name: Corner Style
    $description: Corner shape for dropdowns. Pick Use Global Setting to follow the Global section.
    $options:
      - dont_change: Don't Change
      - sharp: Sharp
      - large_round: Large Round
      - small_round: Small Round
      - use_global: Use Global Setting
  - enableDropShadow: use_global
    $name: Enable Drop Shadow
    $description: Shadow behind dropdowns. Pick Use Global Setting to follow the Global section.
    $options:
      - no: No
      - yes: Yes
      - use_global: Use Global Setting
  - enableFluentAnimation: false
    $name: Enable Fluent Animation
    $description: Fluent animation for dropdowns.
  - noBorderColor: use_global
    $name: Disable Border Color
    $description: Whether dropdowns keep their system borders. Pick Use Global Setting to follow the Global section.
    $options:
      - no: No
      - yes: Yes
      - use_global: Use Global Setting
  - enableThemeColorization: use_global
    $name: Enable Theme Colorization
    $description: Tint with the Windows accent color instead of the fixed border colors. Pick Use Global Setting to follow the Global section.
    $options:
      - no: No
      - yes: Yes
      - use_global: Use Global Setting
  - darkModeThemeColorizationType: start_hover
    $name: Dark Accent Source
    $description: Which Windows accent slot tints the pop-ups in dark mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - lightModeThemeColorizationType: start_hover
    $name: Light Accent Source
    $description: Which Windows accent slot tints the pop-ups in light mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - darkModeBorderColor: "0xFF89B4FA"
    $name: Dark Border Color
    $description: Border color in dark mode, as 0xAARRGGBB.
  - lightModeBorderColor: "0xFF89B4FA"
    $name: Light Border Color
    $description: Border color in light mode, as 0xAARRGGBB.
  - darkModeGradientColor: "0xCC1E1E2E"
    $name: Dark Gradient Color
    $description: Acrylic tint in dark mode, as 0xAARRGGBB.
  - lightModeGradientColor: "0xCC1E1E2E"
    $name: Light Gradient Color
    $description: Acrylic tint in light mode, as 0xAARRGGBB.
  - disabled: use_global
    $name: Disabled
    $description: Turns off every effect for this pop-up type. Pick Use Global Setting to follow the Global section.
    $options:
      - no: No
      - yes: Yes
      - use_global: Use Global Setting
  - animation_fadeOutTime: 350
    $name: Fade Out Time
    $description: Fade-out length in milliseconds.
  - animation_popInTime: 250
    $name: Pop In Time
    $description: Pop-in length in milliseconds.
  - animation_fadeInTime: 87
    $name: Fade In Time
    $description: Fade-in length in milliseconds.
  - animation_popInStyle: slide_down
    $name: Pop In Style
    $description: How the pop-in animation looks.
    $options:
      - slide_down: Slide Down
      - ripple: Ripple
      - smooth_scroll: Smooth Scroll
      - smooth_zoom: Smooth Zoom
  - animation_startRatio: 50
    $name: Start Ratio
    $description: Where the pop-in starts. Higher values start closer to the finished state.
  - animation_enableImmediateInterupting: false
    $name: Enable Immediate Interruption
    $description: Lets a new animation cut in over one that is still running.
  $name: DropDown

- menu:
  - noSystemDropShadow: false
    $name: Disable System Drop Shadow
    $description: Hides the shadow Windows draws behind menus.
  - enableImmersiveStyle: true
    $name: Enable Immersive Style
    $description: Uses the modern, uniformly styled menus. Best left on for Windows 11.
  - enableCustomRendering: false
    $name: Enable Custom Rendering
    $description: Draws menus with the mod's own renderer. Needed for several menu options in this section.
  - enableFluentAnimation: false
    $name: Enable Fluent Animation
    $description: Fluent animation for menus.
  - enableCompatibilityMode: false
    $name: Enable Compatibility Mode
    $description: Fallback rendering for apps whose menus break with the normal renderer.
  - noModernAppBackgroundColor: true
    $name: Disable Modern App Background Color
    $description: Ignores the background color modern apps supply, and uses this mod's appearance instead.
  - colorTreatAsTransparentEnabled: false
    $name: Treat a Color as Transparent
    $description: Treats one menu color as transparent when rendering.
  - colorTreatAsTransparent: "0x00000000"
    $name: Transparent Color
    $description: The color treated as transparent, as 0xAARRGGBB.
  - colorTreatAsTransparentThreshold: 50
    $name: Color Treat As Transparent Threshold
    $description: How close a color must be to count as transparent. Higher matches more shades.
  - effectType: use_global
    $name: Effect Type
    $description: Background effect for menus. Pick Use Global Setting to follow the Global section.
    $options:
      - none: None
      - transparent: Fully Transparent
      - solid: Solid Color
      - blurred: Blurred
      - acrylic: Acrylic
      - modern_acrylic: Modern Acrylic
      - acrylic_bg: Acrylic Background Layer
      - mica_bg: Mica Background Layer
      - mica_variant: Mica Variant Background Layer
      - use_global: Use Global Setting
  - cornerType: use_global
    $name: Corner Style
    $description: Corner shape for menus. Pick Use Global Setting to follow the Global section.
    $options:
      - dont_change: Don't Change
      - sharp: Sharp
      - large_round: Large Round
      - small_round: Small Round
      - use_global: Use Global Setting
  - enableDropShadow: use_global
    $name: Enable Drop Shadow
    $description: Shadow behind menus. Pick Use Global Setting to follow the Global section.
    $options:
      - no: No
      - yes: Yes
      - use_global: Use Global Setting
  - noBorderColor: use_global
    $name: Disable Border Color
    $description: Whether menus keep their system borders. Pick Use Global Setting to follow the Global section.
    $options:
      - no: No
      - yes: Yes
      - use_global: Use Global Setting
  - enableThemeColorization: use_global
    $name: Enable Theme Colorization
    $description: Tint with the Windows accent color instead of the fixed border colors. Pick Use Global Setting to follow the Global section.
    $options:
      - no: No
      - yes: Yes
      - use_global: Use Global Setting
  - darkModeThemeColorizationType: start_hover
    $name: Dark Accent Source
    $description: Which Windows accent slot tints the pop-ups in dark mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - lightModeThemeColorizationType: start_hover
    $name: Light Accent Source
    $description: Which Windows accent slot tints the pop-ups in light mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - darkModeBorderColor: "0xFF89B4FA"
    $name: Dark Border Color
    $description: Border color in dark mode, as 0xAARRGGBB.
  - lightModeBorderColor: "0xFF89B4FA"
    $name: Light Border Color
    $description: Border color in light mode, as 0xAARRGGBB.
  - darkModeGradientColor: "0xCC1E1E2E"
    $name: Dark Gradient Color
    $description: Acrylic tint in dark mode, as 0xAARRGGBB.
  - lightModeGradientColor: "0xCC1E1E2E"
    $name: Light Gradient Color
    $description: Acrylic tint in light mode, as 0xAARRGGBB.
  - disabled: use_global
    $name: Disabled
    $description: Turns off every effect for this pop-up type. Pick Use Global Setting to follow the Global section.
    $options:
      - no: No
      - yes: Yes
      - use_global: Use Global Setting
  - animation_fadeOutTime: 350
    $name: Fade Out Time
    $description: Fade-out length in milliseconds.
  - animation_popInTime: 250
    $name: Pop In Time
    $description: Pop-in length in milliseconds.
  - animation_fadeInTime: 87
    $name: Fade In Time
    $description: Fade-in length in milliseconds.
  - animation_popInStyle: slide_down
    $name: Pop In Style
    $description: How the pop-in animation looks.
    $options:
      - slide_down: Slide Down
      - ripple: Ripple
      - smooth_scroll: Smooth Scroll
      - smooth_zoom: Smooth Zoom
  - animation_startRatio: 50
    $name: Start Ratio
    $description: Where the pop-in starts. Higher values start closer to the finished state.
  - animation_enableImmediateInterupting: false
    $name: Enable Immediate Interruption
    $description: Lets a new animation cut in over one that is still running.
  - separator_disabled: 0
    $name: Separator / Disabled
    $description: Turns off the separator.
  - separator_width: 1000
    $name: Separator / Width
    $description: Separator line thickness. 1000 is the default thickness.
  - separator_darkModeColor: "0x30D9D9D9"
    $name: Separator / Dark Color
    $description: Separator color in dark mode, as 0xAARRGGBB.
  - separator_lightModeColor: "0x30262626"
    $name: Separator / Light Color
    $description: Separator color in light mode, as 0xAARRGGBB.
  - separator_enableThemeColorization: 0
    $name: Separator / Enable Theme Colorization
    $description: Tints the separator with the Windows accent instead of the fixed color.
  - separator_darkThemeColorizationType: start_hover
    $name: Separator / Dark Accent Source
    $description: Which Windows accent slot tints the separator in dark mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - separator_lightThemeColorizationType: start_hover
    $name: Separator / Light Accent Source
    $description: Which Windows accent slot tints the separator in light mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - focusing_disabled: 0
    $name: Focusing / Disabled
    $description: Turns off the focus highlight.
  - focusing_cornerRadius: 8
    $name: Focusing / Corner Radius
    $description: Corner roundness of the focus highlight.
  - focusing_width: 1000
    $name: Focusing / Width
    $description: Width of the focus highlight. 1000 spans the full item.
  - focusing_darkModeColor: "0xFFFFFFFF"
    $name: Focusing / Dark Color
    $description: Focus highlight color in dark mode, as 0xAARRGGBB.
  - focusing_lightModeColor: "0xFF000000"
    $name: Focusing / Light Color
    $description: Focus highlight color in light mode, as 0xAARRGGBB.
  - focusing_enableThemeColorization: 0
    $name: Focusing / Enable Theme Colorization
    $description: Tints the focus highlight with the Windows accent instead of the fixed color.
  - focusing_darkThemeColorizationType: start_hover
    $name: Focusing / Dark Accent Source
    $description: Which Windows accent slot tints the focus highlight in dark mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - focusing_lightThemeColorizationType: start_hover
    $name: Focusing / Light Accent Source
    $description: Which Windows accent slot tints the focus highlight in light mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - disabledHot_disabled: 0
    $name: Disabled Hot / Disabled
    $description: Turns off the highlight for hovered disabled items.
  - disabledHot_cornerRadius: 8
    $name: Disabled Hot / Corner Radius
    $description: Corner roundness of that highlight.
  - disabledHot_darkModeColor: "0x00000000"
    $name: Disabled Hot / Dark Color
    $description: Highlight color for hovered disabled items in dark mode, as 0xAARRGGBB.
  - disabledHot_lightModeColor: "0x00000000"
    $name: Disabled Hot / Light Color
    $description: Highlight color for hovered disabled items in light mode, as 0xAARRGGBB.
  - disabledHot_enableThemeColorization: 0
    $name: Disabled Hot / Enable Theme Colorization
    $description: Tints that highlight with the Windows accent instead of the fixed color.
  - disabledHot_darkThemeColorizationType: start_hover
    $name: Disabled Hot / Dark Accent Source
    $description: Which Windows accent slot tints that highlight in dark mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - disabledHot_lightThemeColorizationType: start_hover
    $name: Disabled Hot / Light Accent Source
    $description: Which Windows accent slot tints that highlight in light mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - hot_disabled: 0
    $name: Hot / Disabled
    $description: Turns off the hover highlight.
  - hot_cornerRadius: 8
    $name: Hot / Corner Radius
    $description: Corner roundness of the hover highlight.
  - hot_darkModeColor: "0x41808080"
    $name: Hot / Dark Color
    $description: Hover highlight color in dark mode, as 0xAARRGGBB.
  - hot_lightModeColor: "0x30000000"
    $name: Hot / Light Color
    $description: Hover highlight color in light mode, as 0xAARRGGBB.
  - hot_enableThemeColorization: 0
    $name: Hot / Enable Theme Colorization
    $description: Tints the hover highlight with the Windows accent instead of the fixed color.
  - hot_darkThemeColorizationType: start_hover
    $name: Hot / Dark Accent Source
    $description: Which Windows accent slot tints the hover highlight in dark mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - hot_lightThemeColorizationType: start_hover
    $name: Hot / Light Accent Source
    $description: Which Windows accent slot tints the hover highlight in light mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  $name: Menu

- tooltip:
  - noSystemDropShadow: false
    $name: Disable System Drop Shadow
    $description: Hides the shadow Windows draws behind tooltips.
  - effectType: use_global
    $name: Effect Type
    $description: Background effect for tooltips. Pick Use Global Setting to follow the Global section.
    $options:
      - none: None
      - transparent: Fully Transparent
      - solid: Solid Color
      - blurred: Blurred
      - acrylic: Acrylic
      - modern_acrylic: Modern Acrylic
      - acrylic_bg: Acrylic Background Layer
      - mica_bg: Mica Background Layer
      - mica_variant: Mica Variant Background Layer
      - use_global: Use Global Setting
  - cornerType: use_global
    $name: Corner Style
    $description: Corner shape for tooltips. Pick Use Global Setting to follow the Global section.
    $options:
      - dont_change: Don't Change
      - sharp: Sharp
      - large_round: Large Round
      - small_round: Small Round
      - use_global: Use Global Setting
  - enableDropShadow: use_global
    $name: Enable Drop Shadow
    $description: Shadow behind tooltips. Pick Use Global Setting to follow the Global section.
    $options:
      - no: No
      - yes: Yes
      - use_global: Use Global Setting
  - noBorderColor: use_global
    $name: Disable Border Color
    $description: Whether tooltips keep their system borders. Pick Use Global Setting to follow the Global section.
    $options:
      - no: No
      - yes: Yes
      - use_global: Use Global Setting
  - enableThemeColorization: use_global
    $name: Enable Theme Colorization
    $description: Tint with the Windows accent color instead of the fixed border colors. Pick Use Global Setting to follow the Global section.
    $options:
      - no: No
      - yes: Yes
      - use_global: Use Global Setting
  - darkModeThemeColorizationType: start_hover
    $name: Dark Accent Source
    $description: Which Windows accent slot tints the pop-ups in dark mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - lightModeThemeColorizationType: start_hover
    $name: Light Accent Source
    $description: Which Windows accent slot tints the pop-ups in light mode.
    $options:
      - start_background: ImmersiveStartBackground
      - start_hover: ImmersiveStartHoverBackground
      - system_accent: ImmersiveSystemAccent
      - accent_dark1: ImmersiveSystemAccentDark1
      - accent_dark2: ImmersiveSystemAccentDark2
      - accent_dark3: ImmersiveSystemAccentDark3
      - accent_light1: ImmersiveSystemAccentLight1
      - accent_light2: ImmersiveSystemAccentLight2
      - accent_light3: ImmersiveSystemAccentLight3
  - darkModeBorderColor: "0xFF89B4FA"
    $name: Dark Border Color
    $description: Border color in dark mode, as 0xAARRGGBB.
  - lightModeBorderColor: "0xFF89B4FA"
    $name: Light Border Color
    $description: Border color in light mode, as 0xAARRGGBB.
  - darkModeGradientColor: "0xCC1E1E2E"
    $name: Dark Gradient Color
    $description: Acrylic tint in dark mode, as 0xAARRGGBB.
  - lightModeGradientColor: "0xCC1E1E2E"
    $name: Light Gradient Color
    $description: Acrylic tint in light mode, as 0xAARRGGBB.
  - darkModeColor: "0xFFFFFFFF"
    $name: Dark Fill Color
    $description: Tooltip fill color in dark mode, as 0xAARRGGBB.
  - lightModeColor: "0xFF1A1A1A"
    $name: Light Fill Color
    $description: Tooltip fill color in light mode, as 0xAARRGGBB.
  - marginsType: add_to_existing
    $name: Margins Mode
    $description: Whether the margins below add to the existing ones or replace them.
    $options:
      - add_to_existing: AddToExisting
      - replace_existing: ReplaceExisting
  - marginLeft: 6
    $name: Margin Left
    $description: Left margin in pixels.
  - marginRight: 6
    $name: Margin Right
    $description: Right margin in pixels.
  - marginTop: 6
    $name: Margin Top
    $description: Top margin in pixels.
  - marginBottom: 6
    $name: Margin Bottom
    $description: Bottom margin in pixels.
  - disabled: use_global
    $name: Disabled
    $description: Turns off every effect for this pop-up type. Pick Use Global Setting to follow the Global section.
    $options:
      - no: No
      - yes: Yes
      - use_global: Use Global Setting
  $name: Tooltip


- darkMenus:
  - appMode: force_dark
    $name: Dark Menus
    $description: When context menus and menu bars should be dark. Pick the Windows setting if you switch between light and dark mode a lot, or use a tool like Auto Dark Mode.
    $options:
      - force_dark: Always
      - allow_dark: Only when Windows is in dark mode
      - off: Leave menus alone
  $name: Dark Menus


- advancedFunctions:
  - processBlockList: ""
    $name: Process Block List
    $description: Advanced users only. Process names (comma, semicolon or newline separated) that TranslucentFlyouts never loads into, for example explorer.exe. Takes effect after a restart. A bad entry can cause high CPU usage.
  - processDisabledList: ""
    $name: Process Disabled List (Global)
    $description: Advanced users only. Process names (comma, semicolon or newline separated) where every effect stays off, for example app.exe.
  - menuProcessDisabledList: ""
    $name: Process Disabled List (Menu)
    $description: Advanced users only. Process names (comma, semicolon or newline separated) where only menu effects stay off.
  - tooltipProcessDisabledList: ""
    $name: Process Disabled List (Tooltip)
    $description: Advanced users only. Process names (comma, semicolon or newline separated) where only tooltip effects stay off.
  - dropDownProcessDisabledList: ""
    $name: Process Disabled List (DropDown)
    $description: Advanced users only. Process names (comma, semicolon or newline separated) where only dropdown effects stay off.
  $name: Advanced Functions
*/
// ==/WindhawkModSettings==

// ==WindhawkModReadme==
/*
# Translucent Flyouts

Give the classic menus, dropdowns and tooltips in every app a modern acrylic,
Mica or blur background. The TranslucentFlyouts app, rebuilt as one mod with
no helper program.

![Translucent Flyouts preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/translucent-flyouts.png)

## Features

- **Context menus, menu bars, dropdown lists and tooltips** in 64-bit and
  32-bit apps.
- **Modern Acrylic, Acrylic, Mica, blur, transparent or solid** backgrounds.
- **Rounded or square corners**, drop shadows and accent-colored borders.
- **Separate styles** for menus, dropdowns and tooltips, or one global style.
- **Light and dark mode colors**, set independently.
- **Fluent animations** for menus and dropdowns.
- **Dark menus** in every app, always or only when Windows is in dark mode.

## Tips

- Dark menus are built in, so the separate Dark mode context menus mod is not
  needed. Remove it if it is still installed.
- Programs listed in this mod's exclusions are left untouched. Add any app
  that should keep its original menus.

## Credits

A port of [TranslucentFlyouts](https://github.com/ALTaleX531/TranslucentFlyouts)
by ALTaleX531. The settings follow its configuration schema. LGPL-3.0.

The dark menus part comes from
[Dark mode context menus](https://github.com/MGGSK/DarkMenus) by Mgg Sk, which
builds on [win32-darkmode](https://github.com/adzm/win32-darkmode) and
[Notepad++](https://github.com/notepad-plus-plus/notepad-plus-plus).
*/
// ==/WindhawkModReadme==

#include <windhawk_api.h>
#include <windhawk_utils.h>

#include <windows.h>
#include <windowsx.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <vsstyle.h>
#include <vssym32.h>
#include <commctrl.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <d2d1.h>
#include <gdiplus.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cwchar>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

// The MinGW vsstyle.h predates these parts (Windows Insider Preview 22621+);
// the 26100 SDK renamed the second one without the inner underscore.
#ifndef MENU_POPUPITEMKBFOCUS
#define MENU_POPUPITEMKBFOCUS 26
#endif
#ifndef MENU_POPUPITEMFOCUSABLE
#define MENU_POPUPITEMFOCUSABLE 27
#endif

namespace tf {

// ===========================================================================
// Minimal WIL-style helpers (the upstream uses WIL; this port keeps only the
// pieces the engine needs)
// ===========================================================================

struct HandleCloser {
    using pointer = HANDLE;
    void operator()(HANDLE h) const {
        if (h) {
            DeleteObject(h);
        }
    }
};

template <typename T, typename Closer = HandleCloser>
class unique_handle {
   public:
    unique_handle() = default;
    explicit unique_handle(T value) : m_value(value) {}
    ~unique_handle() { reset(); }
    unique_handle(const unique_handle&) = delete;
    unique_handle& operator=(const unique_handle&) = delete;
    unique_handle(unique_handle&& other) noexcept : m_value(other.release()) {}
    unique_handle& operator=(unique_handle&& other) noexcept {
        reset(other.release());
        return *this;
    }
    T get() const { return m_value; }
    T release() {
        T v = m_value;
        m_value = T{};
        return v;
    }
    void reset(T value = T{}) {
        if (m_value) {
            Closer{}(m_value);
        }
        m_value = value;
    }
    explicit operator bool() const { return m_value != nullptr; }

   private:
    T m_value{};
};

struct DcCloser {
    using pointer = HDC;
    void operator()(HDC dc) const {
        if (dc) {
            ReleaseDC(nullptr, dc);
        }
    }
};

class unique_dc {
   public:
    unique_dc() = default;
    explicit unique_dc(HDC dc, HWND fromWindow = nullptr) : m_dc(dc), m_hwnd(fromWindow) {}
    ~unique_dc() { reset(); }
    unique_dc(const unique_dc&) = delete;
    unique_dc& operator=(const unique_dc&) = delete;
    HDC get() const { return m_dc; }
    operator HDC() const { return m_dc; }
    bool is_valid() const { return m_dc != nullptr; }
    HDC release() {
        HDC dc = m_dc;
        m_dc = nullptr;
        return dc;
    }
    void reset(HDC dc = nullptr, HWND fromWindow = nullptr) {
        if (m_dc) {
            if (m_hwnd) {
                ReleaseDC(m_hwnd, m_dc);
            } else {
                ReleaseDC(nullptr, m_dc);
            }
        }
        m_dc = dc;
        m_hwnd = fromWindow;
    }

   private:
    HDC m_dc{};
    HWND m_hwnd{};
};

// Saves and restores a DC on scope exit.
class DcStateGuard {
   public:
    explicit DcStateGuard(HDC dc, bool saveState = true) : m_dc(dc), m_saved(saveState ? SaveDC(dc) : -1) {}
    ~DcStateGuard() {
        if (m_saved != -1) {
            RestoreDC(m_dc, m_saved);
        }
    }
    DcStateGuard(const DcStateGuard&) = delete;
    DcStateGuard& operator=(const DcStateGuard&) = delete;

   private:
    HDC m_dc{};
    int m_saved{-1};
};

// A selected-object guard for memory DCs.
class SelectObjectGuard {
   public:
    SelectObjectGuard(HDC dc, HGDIOBJ obj) : m_dc(dc) {
        if (dc && obj) {
            m_old = SelectObject(dc, obj);
        }
    }
    ~SelectObjectGuard() {
        if (m_dc && m_old) {
            SelectObject(m_dc, m_old);
        }
    }
    SelectObjectGuard(const SelectObjectGuard&) = delete;
    SelectObjectGuard& operator=(const SelectObjectGuard&) = delete;

   private:
    HDC m_dc{};
    HGDIOBJ m_old{};
};

inline int RectWidth(const RECT& r) { return r.right - r.left; }
inline int RectHeight(const RECT& r) { return r.bottom - r.top; }

// ===========================================================================
// Logging
// ===========================================================================

namespace Log {
// Writes to <mod storage>\translucent-flyouts-<process>-<pid>.log. Disabled in
// release unless TF_DEBUG_LOG is defined; kept because it is the only way to
// see what the mod does inside other processes.
#ifdef TF_DEBUG_LOG
constexpr bool kEnabled = true;
#else
constexpr bool kEnabled = false;
#endif
#ifdef TF_DEBUG_LOG
constexpr size_t kMaxLines = 60000;
#else
constexpr size_t kMaxLines = 4000;
#endif

inline bool IsTargetProcess() {
    static const bool value = []() {
        wchar_t path[MAX_PATH]{};
        GetModuleFileNameW(nullptr, path, MAX_PATH);
        const wchar_t* base = wcsrchr(path, L'\\');
        base = base ? base + 1 : path;
        return !_wcsicmp(base, L"explorer.exe") || !_wcsicmp(base, L"FlyoutTestWindow.exe") ||
               !_wcsicmp(base, L"FlyoutTestWindow32.exe") || !_wcsicmp(base, L"notepad++.exe") ||
               !_wcsicmp(base, L"regedit.exe") || !_wcsicmp(base, L"winver.exe") ||
               !_wcsicmp(base, L"Ableton Live 12 Suite.exe");
    }();
    return value;
}

inline void Write(const wchar_t* fmt, ...) {
    if (!kEnabled || !IsTargetProcess()) {
        return;
    }
    static std::mutex lock;
    static HANDLE file = INVALID_HANDLE_VALUE;
    static int lines = 0;

    std::lock_guard<std::mutex> guard(lock);
    if (lines >= (int)kMaxLines) {
        return;
    }
    if (file == INVALID_HANDLE_VALUE) {
        wchar_t dir[MAX_PATH]{};
        if (!Wh_GetModStoragePath(dir, MAX_PATH)) {
            return;
        }
        wchar_t path[MAX_PATH]{};
        GetModuleFileNameW(nullptr, path, MAX_PATH);
        const wchar_t* base = wcsrchr(path, L'\\');
        base = base ? base + 1 : path;
        wchar_t filePath[MAX_PATH]{};
        swprintf_s(filePath, L"%s\\tf-%s-%lu.log", dir, base, GetCurrentProcessId());
        file = CreateFileW(filePath, FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                           CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file == INVALID_HANDLE_VALUE) {
            return;
        }
    }
    wchar_t line[1024]{};
    va_list args;
    va_start(args, fmt);
    _vsnwprintf_s(line, _TRUNCATE, fmt, args);
    va_end(args);
    DWORD written = 0;
    WriteFile(file, line, (DWORD)(wcslen(line) * sizeof(wchar_t)), &written, nullptr);
    WriteFile(file, L"\r\n", 4, &written, nullptr);
    lines++;
}
}  // namespace Log

// ===========================================================================
// Utils (subset of Common/Utils.hpp)
// ===========================================================================

namespace Utils {

inline std::wstring GetProcessName() {
    static const std::wstring value = []() {
        wchar_t path[MAX_PATH]{};
        GetModuleFileNameW(nullptr, path, MAX_PATH);
        const wchar_t* base = wcsrchr(path, L'\\');
        return std::wstring(base ? base + 1 : path);
    }();
    return value;
}

inline bool IsWindowClass(HWND hWnd, std::wstring_view className) {
    if (!hWnd) {
        return false;
    }
    wchar_t cls[MAX_PATH + 1]{};
    if (!GetClassNameW(hWnd, cls, MAX_PATH)) {
        return false;
    }
    return !_wcsicmp(cls, std::wstring(className).c_str());
}

// Some frameworks (WinForms) register their own window classes that embed the
// system class name, e.g. "WindowsForms10.tooltips_class32.app.0.1_2_ad1".
inline bool IsWindowClassContains(HWND hWnd, std::wstring_view part) {
    if (!hWnd) {
        return false;
    }
    wchar_t cls[MAX_PATH + 1]{};
    if (!GetClassNameW(hWnd, cls, MAX_PATH)) {
        return false;
    }
    std::wstring haystack(cls);
    std::wstring needle(part);
    for (wchar_t& ch : haystack) {
        ch = static_cast<wchar_t>(towlower(ch));
    }
    for (wchar_t& ch : needle) {
        ch = static_cast<wchar_t>(towlower(ch));
    }
    return haystack.find(needle) != std::wstring::npos;
}

inline bool IsPopupMenu(HWND hWnd) {
    return hWnd && GetClassLongPtrW(hWnd, GCW_ATOM) == 32768;
}

inline HWND GetCurrentMenuOwner() {
    GUITHREADINFO guiThreadInfo{sizeof(GUITHREADINFO)};
    GetGUIThreadInfo(GetCurrentThreadId(), &guiThreadInfo);
    return guiThreadInfo.hwndMenuOwner;
}

inline bool IsRectEmptySafe(const RECT* rect) { return !rect || IsRectEmpty(rect); }

inline UCHAR PremultiplyColor(UCHAR color, UCHAR alpha = 255) {
    return static_cast<UCHAR>(color * (alpha + 1) >> 8);
}

inline COLORREF MakeCOLORREF(DWORD argb) {
    return RGB(argb >> 16 & 0xff, argb >> 8 & 0xff, argb & 0xff);
}

inline DWORD MakeArgb(UCHAR a, UCHAR r, UCHAR g, UCHAR b) {
    return (static_cast<DWORD>(a) << 24) | (static_cast<DWORD>(r) << 16) |
           (static_cast<DWORD>(g) << 8) | b;
}

inline UCHAR GetAlphaFromARGB(DWORD argb) { return static_cast<UCHAR>(argb >> 24); }

inline HBITMAP CreateDIB(LONG width = 1, LONG height = -1, UCHAR** bits = nullptr) {
    BITMAPINFO bitmapInfo{{sizeof(bitmapInfo.bmiHeader), width, height, 1, 32, BI_RGB}};
    return CreateDIBSection(nullptr, &bitmapInfo, DIB_RGB_COLORS, reinterpret_cast<PVOID*>(bits),
                            nullptr, 0);
}

// A solid brush that honors alpha channel: a 1x1 pattern brush from a 32bpp
// premultiplied DIB.
inline HBRUSH CreateSolidColorBrushWithAlpha(COLORREF color, UCHAR alpha) {
    UCHAR* bits{nullptr};
    unique_handle<HBITMAP> bitmap{CreateDIB(1, -1, &bits)};
    if (!bitmap) {
        return nullptr;
    }
    bits[0] = PremultiplyColor(GetBValue(color), alpha);
    bits[1] = PremultiplyColor(GetGValue(color), alpha);
    bits[2] = PremultiplyColor(GetRValue(color), alpha);
    bits[3] = alpha;
    return CreatePatternBrush(bitmap.get());
}

// Converts a bitmap to a 32bpp premultiplied-alpha DIB (upstream
// ConvertTo32BPP/Promise32BPP, used to fix menu item icons).
inline bool IsBitmapSupportAlpha(HBITMAP bitmap) {
    bool hasAlpha{false};
    BITMAPINFO bitmapInfo{sizeof(bitmapInfo.bmiHeader)};
    HDC hdc = GetDC(nullptr);
    if (!hdc) {
        return false;
    }
    unique_dc dcGuard(hdc);
    if (!bitmap || GetObjectType(bitmap) != OBJ_BITMAP ||
        GetDIBits(hdc, bitmap, 0, 0, nullptr, &bitmapInfo, DIB_RGB_COLORS) == 0) {
        return false;
    }
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
    if (bitmapInfo.bmiHeader.biBitCount != 32) {
        return false;
    }
    auto pixelBits = std::make_unique<UCHAR[]>(bitmapInfo.bmiHeader.biSizeImage);
    if (GetDIBits(hdc, bitmap, 0, bitmapInfo.bmiHeader.biHeight, pixelBits.get(), &bitmapInfo,
                  DIB_RGB_COLORS) == 0) {
        return false;
    }
    for (size_t i = 0; i < bitmapInfo.bmiHeader.biSizeImage; i += 4) {
        if (pixelBits[i + 3] != 0) {
            hasAlpha = true;
            break;
        }
    }
    return hasAlpha;
}

inline HBITMAP ConvertTo32BPP(HBITMAP bitmap) {
    if (!bitmap || GetObjectType(bitmap) != OBJ_BITMAP) {
        return nullptr;
    }
    BITMAPINFO bitmapInfo{sizeof(bitmapInfo.bmiHeader)};
    HDC hdc = GetDC(nullptr);
    if (!hdc) {
        return nullptr;
    }
    unique_dc dcGuard(hdc);
    if (GetDIBits(hdc, bitmap, 0, 0, nullptr, &bitmapInfo, DIB_RGB_COLORS) == 0) {
        return nullptr;
    }
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
    auto pixelBits = std::make_unique<UCHAR[]>(bitmapInfo.bmiHeader.biSizeImage);
    if (GetDIBits(hdc, bitmap, 0, bitmapInfo.bmiHeader.biHeight, pixelBits.get(), &bitmapInfo,
                  DIB_RGB_COLORS) == 0) {
        return nullptr;
    }

    UCHAR* pixelBitsWithAlpha{nullptr};
    BITMAPINFO bitmapWithAlphaInfo{{sizeof(bitmapInfo.bmiHeader), bitmapInfo.bmiHeader.biWidth,
                                    -abs(bitmapInfo.bmiHeader.biHeight), 1, 32, BI_RGB}};
    unique_handle<HBITMAP> bitmapWithAlpha{
        CreateDIBSection(nullptr, &bitmapWithAlphaInfo, DIB_RGB_COLORS,
                         reinterpret_cast<PVOID*>(&pixelBitsWithAlpha), nullptr, 0)};
    if (!bitmapWithAlpha) {
        return nullptr;
    }
    HDC memoryDC = CreateCompatibleDC(hdc);
    if (!memoryDC) {
        return nullptr;
    }
    unique_dc memoryDcGuard(memoryDC);

    size_t bitmapSize = static_cast<size_t>(bitmapInfo.bmiHeader.biWidth) *
                        static_cast<size_t>(abs(bitmapInfo.bmiHeader.biHeight)) * 4ull;
    for (size_t i = 0; i < bitmapSize; i += 4) {
        pixelBitsWithAlpha[i + 3] = 255;
    }
    {
        SelectObjectGuard select(memoryDC, bitmapWithAlpha.get());
        StretchDIBits(memoryDC, 0, 0, bitmapInfo.bmiHeader.biWidth, bitmapInfo.bmiHeader.biHeight,
                      0, 0, bitmapInfo.bmiHeader.biWidth, bitmapInfo.bmiHeader.biHeight,
                      pixelBits.get(), &bitmapInfo, DIB_RGB_COLORS, SRCPAINT);
    }
    return bitmapWithAlpha.release();
}

inline HBITMAP Promise32BPP(HBITMAP bitmap) {
    if (IsBitmapSupportAlpha(bitmap)) {
        return reinterpret_cast<HBITMAP>(
            CopyImage(bitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE));
    }
    return ConvertTo32BPP(bitmap);
}

// Removes a specific background color from a 32bpp bitmap (upstream
// SpriteEffect: flood fill from the corners, distance threshold).
inline HRESULT BitmapRemoveColor(HBITMAP bitmap, DWORD color, DWORD distance) {
    if (!bitmap || GetObjectType(bitmap) != OBJ_BITMAP) {
        return E_INVALIDARG;
    }
    BITMAPINFO bitmapInfo{sizeof(bitmapInfo.bmiHeader)};
    HDC hdc = GetDC(nullptr);
    if (!hdc) {
        return E_FAIL;
    }
    unique_dc dcGuard(hdc);
    if (GetDIBits(hdc, bitmap, 0, 0, nullptr, &bitmapInfo, DIB_RGB_COLORS) == 0) {
        return E_FAIL;
    }
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
    if (bitmapInfo.bmiHeader.biBitCount != 32) {
        return E_NOTIMPL;
    }
    const LONG width = abs(bitmapInfo.bmiHeader.biWidth);
    const LONG height = abs(bitmapInfo.bmiHeader.biHeight);
    auto pixelBits = std::make_unique<UCHAR[]>(bitmapInfo.bmiHeader.biSizeImage);
    if (GetDIBits(hdc, bitmap, 0, bitmapInfo.bmiHeader.biHeight, pixelBits.get(), &bitmapInfo,
                  DIB_RGB_COLORS) == 0) {
        return E_FAIL;
    }

    auto map = std::make_unique<bool[]>(static_cast<size_t>(width) * height);
    auto matches = [&](LONG x, LONG y) -> bool {
        size_t index = (static_cast<size_t>(width) * y + x) * 4;
        const UCHAR* px = &pixelBits[index];
        long long db = static_cast<long long>(px[0]) - GetBValue(MakeCOLORREF(color));
        long long dg = static_cast<long long>(px[1]) - GetGValue(MakeCOLORREF(color));
        long long dr = static_cast<long long>(px[2]) - GetRValue(MakeCOLORREF(color));
        long long da = static_cast<long long>(px[3]) - GetAlphaFromARGB(color);
        return (db * db + dg * dg + dr * dr + da * da) <= static_cast<long long>(distance) * distance;
    };

    struct StackItem {
        LONG x, y;
    };
    std::vector<StackItem> stack;
    auto push = [&](LONG x, LONG y) {
        if (x < 0 || y < 0 || x >= width || y >= height) {
            return;
        }
        if (map[static_cast<size_t>(width) * y + x]) {
            return;
        }
        if (!matches(x, y)) {
            return;
        }
        map[static_cast<size_t>(width) * y + x] = true;
        stack.push_back({x, y});
    };
    push(0, 0);
    push(width - 1, 0);
    push(0, height - 1);
    push(width - 1, height - 1);

    while (!stack.empty()) {
        StackItem item = stack.back();
        stack.pop_back();
        size_t index = (static_cast<size_t>(width) * item.y + item.x) * 4;
        pixelBits[index] = 0;
        pixelBits[index + 1] = 0;
        pixelBits[index + 2] = 0;
        pixelBits[index + 3] = 0;
        push(item.x + 1, item.y);
        push(item.x - 1, item.y);
        push(item.x, item.y + 1);
        push(item.x, item.y - 1);
    }

    if (SetDIBits(hdc, bitmap, 0, bitmapInfo.bmiHeader.biHeight, pixelBits.get(), &bitmapInfo,
                  DIB_RGB_COLORS) == 0) {
        return E_FAIL;
    }
    return S_OK;
}

inline bool IsOemBitmap(HBITMAP bitmap) {
    switch (reinterpret_cast<DWORD64>(bitmap)) {
        case (DWORD64)-1:
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            return true;
        default:
            return false;
    }
}

inline bool IsHighContrast() {
    HIGHCONTRASTW hc{sizeof(hc)};
    SystemParametersInfoW(SPI_GETHIGHCONTRAST, sizeof(HIGHCONTRAST), &hc, 0);
    return (hc.dwFlags & HCF_HIGHCONTRASTON) != 0;
}

}  // namespace Utils

// ===========================================================================
// SystemHelper (build number)
// ===========================================================================

namespace SystemHelper {
// CurrentBuildNumber is REG_SZ; read it as text and parse, or the raw bytes get
// interpreted as a bogus integer (works by accident on digit strings only).
inline DWORD GetBuildNumber() {
    static const DWORD value = []() -> DWORD {
        HKEY hKey{};
        wchar_t text[32]{};
        DWORD size = sizeof(text);
        DWORD build = 0;
        if (RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                          L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_QUERY_VALUE,
                          &hKey) == ERROR_SUCCESS) {
            RegQueryValueExW(hKey, L"CurrentBuildNumber", nullptr, nullptr,
                             reinterpret_cast<LPBYTE>(text), &size);
            RegCloseKey(hKey);
            wchar_t* end{nullptr};
            unsigned long parsed = wcstoul(text, &end, 10);
            if (end != text) {
                build = static_cast<DWORD>(parsed);
            }
        }
        return build;
    }();
    return value;
}
inline bool IsWindows11() { return GetBuildNumber() >= 22000; }
inline bool SupportsDwmBackdrop() { return GetBuildNumber() >= 22621; }
}  // namespace SystemHelper

// ===========================================================================
// ThemeHelper (subset)
// ===========================================================================

namespace ThemeHelper {
__forceinline bool ShouldAppsUseDarkMode() {
    static const auto actual = reinterpret_cast<bool(WINAPI*)()>(
        GetProcAddress(GetModuleHandleW(L"UxTheme.dll"), MAKEINTRESOURCEA(132)));
    return actual ? actual() : false;
}

__forceinline bool IsDarkModeAllowedForApp() {
    static const auto actual = reinterpret_cast<bool(WINAPI*)()>(
        GetProcAddress(GetModuleHandleW(L"UxTheme.dll"), MAKEINTRESOURCEA(139)));
    return actual ? actual() : false;
}

__forceinline HRESULT GetThemeClass(HTHEME hTheme, LPCWSTR pszClassIdList, int cchClass) {
    static const auto actual = reinterpret_cast<HRESULT(WINAPI*)(HTHEME, LPCWSTR, int)>(
        GetProcAddress(GetModuleHandleW(L"UxTheme"), MAKEINTRESOURCEA(74)));
    return actual ? actual(hTheme, pszClassIdList, cchClass) : E_FAIL;
}

// The accent slots read straight from the user's AccentPalette (Light3..Light1,
// Accent, Dark1..Dark3 in that order, 4 bytes RGBA each). uxtheme's colour-set
// cache in a shell that started before the user's accent was applied keeps the
// stock 0078D4 for the life of the process (the Explorer title-bar sysmenu
// screenshot, 2026-10-21); the registry palette is always current.
inline bool GetAccentPaletteColor(std::wstring_view type, DWORD& argb) {
    static constexpr std::wstring_view kSlots[] = {
        L"ImmersiveSystemAccentLight3", L"ImmersiveSystemAccentLight2",
        L"ImmersiveSystemAccentLight1", L"ImmersiveSystemAccent",
        L"ImmersiveSystemAccentDark1",  L"ImmersiveSystemAccentDark2",
        L"ImmersiveSystemAccentDark3"};
    int slot = -1;
    for (int i = 0; i < (int)std::size(kSlots); ++i) {
        if (kSlots[i] == type) {
            slot = i;
        }
    }
    if (slot < 0) {
        return false;
    }
    BYTE palette[32]{};
    DWORD size = sizeof(palette);
    if (RegGetValueW(HKEY_CURRENT_USER,
                     L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Accent",
                     L"AccentPalette", RRF_RT_REG_BINARY, nullptr, palette,
                     &size) != ERROR_SUCCESS ||
        size < sizeof(palette)) {
        return false;
    }
    const BYTE* rgba = palette + slot * 4;
    argb = Utils::MakeArgb(0xFF, rgba[0], rgba[1], rgba[2]);
    return true;
}

inline DWORD GetThemeColorizationColor(std::wstring_view type) {
    DWORD paletteArgb{0};
    if (GetAccentPaletteColor(type, paletteArgb)) {
        return paletteArgb;
    }
    static const auto GetImmersiveColorFromColorSetEx =
        reinterpret_cast<DWORD(WINAPI*)(DWORD, DWORD, bool, DWORD)>(
            GetProcAddress(GetModuleHandleW(L"UxTheme.dll"), MAKEINTRESOURCEA(95)));
    static const auto GetImmersiveColorTypeFromName = reinterpret_cast<DWORD(WINAPI*)(LPCWSTR)>(
        GetProcAddress(GetModuleHandleW(L"UxTheme.dll"), MAKEINTRESOURCEA(96)));
    static const auto GetImmersiveUserColorSetPreference = reinterpret_cast<DWORD(WINAPI*)(bool, bool)>(
        GetProcAddress(GetModuleHandleW(L"UxTheme.dll"), MAKEINTRESOURCEA(98)));

    DWORD argb{0};
    if (GetImmersiveColorFromColorSetEx && GetImmersiveColorTypeFromName &&
        GetImmersiveUserColorSetPreference) {
        std::wstring typeName(type);
        DWORD abgr = GetImmersiveColorFromColorSetEx(GetImmersiveUserColorSetPreference(0, 0),
                                                     GetImmersiveColorTypeFromName(typeName.c_str()),
                                                     true, 0);
        argb = Utils::MakeArgb(abgr >> 24, abgr & 0xff, (abgr >> 8) & 0xff, (abgr >> 16) & 0xff);
    } else {
        BOOL opaque{FALSE};
        DwmGetColorizationColor(&argb, &opaque);
    }
    return argb;
}

// Renders content with alpha through a buffered paint DC (upstream
// DrawThemeContent).
inline HRESULT DrawThemeContent(HDC hdc,
                                const RECT& paintRect,
                                LPCRECT clipRect,
                                LPCRECT excludeRect,
                                DWORD additionalFlags,
                                void (*callback)(HDC memoryDC, HPAINTBUFFER, RGBQUAD*, int, LPARAM),
                                LPARAM lParam) try {
    BOOL updateTarget{FALSE};
    HDC memoryDC{nullptr};
    HPAINTBUFFER bufferedPaint{nullptr};
    BLENDFUNCTION blendFunction{AC_SRC_OVER, 0, 0xFF, AC_SRC_ALPHA};
    BP_PAINTPARAMS paintParams{sizeof(BP_PAINTPARAMS), BPPF_ERASE | additionalFlags, excludeRect,
                               &blendFunction};

    DcStateGuard dcState(hdc);
    if (clipRect) {
        IntersectClipRect(hdc, clipRect->left, clipRect->top, clipRect->right, clipRect->bottom);
    }
    if (excludeRect) {
        ExcludeClipRect(hdc, excludeRect->left, excludeRect->top, excludeRect->right,
                        excludeRect->bottom);
    }

    bufferedPaint = BeginBufferedPaint(hdc, &paintRect, BPBF_TOPDOWNDIB, &paintParams, &memoryDC);
    if (!bufferedPaint) {
        return E_FAIL;
    }
    {
        SelectObjectGuard fontGuard(memoryDC, GetCurrentObject(hdc, OBJ_FONT));
        SelectObjectGuard brushGuard(memoryDC, GetCurrentObject(hdc, OBJ_BRUSH));
        SelectObjectGuard penGuard(memoryDC, GetCurrentObject(hdc, OBJ_PEN));
        int cxRow{0};
        RGBQUAD* buffer{nullptr};
        if (FAILED(GetBufferedPaintBits(bufferedPaint, &buffer, &cxRow))) {
            EndBufferedPaint(bufferedPaint, FALSE);
            return E_FAIL;
        }
        callback(memoryDC, bufferedPaint, buffer, cxRow, lParam);
    }
    updateTarget = TRUE;
    EndBufferedPaint(bufferedPaint, updateTarget);
    return S_OK;
} catch (...) {
    return E_FAIL;
}

__forceinline HRESULT DrawTextWithGlow(HDC hdc,
                                       LPCWSTR pszText,
                                       int cchText,
                                       LPRECT prc,
                                       UINT dwFlags,
                                       UINT crText,
                                       UINT crGlow,
                                       UINT nGlowRadius,
                                       UINT nGlowIntensity,
                                       BOOL bPreMultiply,
                                       DTT_CALLBACK_PROC actualDrawTextCallback,
                                       LPARAM lParam) {
    static const auto actual = reinterpret_cast<HRESULT(WINAPI*)(
        HDC, LPCWSTR, int, LPRECT, UINT, UINT, UINT, UINT, UINT, BOOL, DTT_CALLBACK_PROC, LPARAM)>(
        GetProcAddress(GetModuleHandleW(L"UxTheme"), MAKEINTRESOURCEA(126)));
    if (actual) {
        return actual(hdc, pszText, cchText, prc, dwFlags, crText, crGlow, nGlowRadius,
                      nGlowIntensity, bPreMultiply, actualDrawTextCallback, lParam);
    }
    return E_FAIL;
}
}  // namespace ThemeHelper

// ===========================================================================
// EffectHelper (backdrop effects, upstream EffectHelper.hpp)
// ===========================================================================

namespace EffectHelper {
enum class EffectType {
    None,
    Transparent,
    Solid,
    Blur,
    AcrylicBlur,
    // Windows 11
    ModernAcrylicBlur,
    Acrylic,
    Mica,
    MicaAlt,
    Max,
};

enum class WINDOWCOMPOSITIONATTRIBUTE : DWORD {
    WCA_ACCENT_POLICY = 19,
};

enum class ACCENT_STATE : DWORD {
    ACCENT_DISABLED,
    ACCENT_ENABLE_GRADIENT,
    ACCENT_ENABLE_TRANSPARENTGRADIENT,
    ACCENT_ENABLE_BLURBEHIND,
    ACCENT_ENABLE_ACRYLICBLURBEHIND,
    ACCENT_ENABLE_HOSTBACKDROP,
    ACCENT_INVALID_STATE,
};

enum ACCENT_FLAG : DWORD {
    ACCENT_NONE = 0,
    ACCENT_ENABLE_MODERN_ACRYLIC_RECIPE = 1 << 1,
    ACCENT_ENABLE_GRADIENT_COLOR = 1 << 1,
    ACCENT_ENABLE_BORDER_LEFT = 1 << 5,
    ACCENT_ENABLE_BORDER_TOP = 1 << 6,
    ACCENT_ENABLE_BORDER_RIGHT = 1 << 7,
    ACCENT_ENABLE_BORDER_BOTTOM = 1 << 8,
    ACCENT_ENABLE_BORDER = ACCENT_ENABLE_BORDER_LEFT | ACCENT_ENABLE_BORDER_TOP |
                          ACCENT_ENABLE_BORDER_RIGHT | ACCENT_ENABLE_BORDER_BOTTOM,
};

struct ACCENT_POLICY {
    DWORD AccentState;
    DWORD AccentFlags;
    DWORD dwGradientColor;
    DWORD dwAnimationId;
};

struct WINDOWCOMPOSITIONATTRIBUTEDATA {
    DWORD dwAttribute;
    PVOID pvData;
    SIZE_T cbData;
};

inline BOOL WINAPI SetWindowCompositionAttribute(HWND hWnd,
                                                 WINDOWCOMPOSITIONATTRIBUTEDATA* data) {
    static const auto actual = reinterpret_cast<BOOL(WINAPI*)(HWND, WINDOWCOMPOSITIONATTRIBUTEDATA*)>(
        GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute"));
    return actual ? actual(hWnd, data) : FALSE;
}

inline void DwmMakeWindowTransparent(HWND hwnd, BOOL enable) {
    DWM_BLURBEHIND bb{DWM_BB_ENABLE | static_cast<DWORD>(enable ? (DWM_BB_BLURREGION | DWM_BB_TRANSITIONONMAXIMIZED) : 0),
                      enable, CreateRectRgn(0, 0, -1, -1), TRUE};
    DwmEnableBlurBehindWindow(hwnd, &bb);
    if (bb.hRgnBlur) {
        DeleteObject(bb.hRgnBlur);
    }
}

__forceinline void EnableWindowDarkMode(HWND hwnd, BOOL darkMode) {
    if (!SystemHelper::IsWindows11()) {
        constexpr DWORD kDwmwaUseImmersiveDarkModeWin10{19};
        DwmSetWindowAttribute(hwnd, kDwmwaUseImmersiveDarkModeWin10, &darkMode, sizeof(darkMode));
    } else {
        DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkMode, sizeof(darkMode));
    }
}

inline void TriggerWindowNCRendering(HWND hwnd) {
    DefWindowProcW(hwnd, WM_NCACTIVATE, TRUE, 0);
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_DRAWFRAME |
                     SWP_NOACTIVATE);
}

// Applies a backdrop effect to a flyout window (port of
// EffectHelper::SetWindowBackdrop).
inline void SetWindowBackdrop(HWND hwnd, BOOL dropShadow, DWORD tintColor, DWORD effectType) {
    ACCENT_POLICY accentPolicy{static_cast<DWORD>(ACCENT_STATE::ACCENT_DISABLED),
                               dropShadow ? static_cast<DWORD>(ACCENT_ENABLE_BORDER)
                                          : static_cast<DWORD>(ACCENT_NONE),
                               tintColor, 0};
    WINDOWCOMPOSITIONATTRIBUTEDATA data{static_cast<DWORD>(WINDOWCOMPOSITIONATTRIBUTE::WCA_ACCENT_POLICY),
                                        &accentPolicy, sizeof(ACCENT_POLICY)};
    DWM_SYSTEMBACKDROP_TYPE backdropType{DWMSBT_NONE};

    BOOL mica{FALSE};
    BOOL ncRendering{FALSE};
    BOOL windowTransparent{FALSE};

    switch (static_cast<EffectType>(effectType)) {
        case EffectType::None:
            break;
        case EffectType::Solid:
            accentPolicy.AccentState = static_cast<DWORD>(ACCENT_STATE::ACCENT_ENABLE_GRADIENT);
            accentPolicy.AccentFlags |= ACCENT_ENABLE_GRADIENT_COLOR;
            break;
        case EffectType::Transparent:
            accentPolicy.AccentState =
                static_cast<DWORD>(ACCENT_STATE::ACCENT_ENABLE_TRANSPARENTGRADIENT);
            accentPolicy.AccentFlags |= ACCENT_ENABLE_GRADIENT_COLOR;
            break;
        case EffectType::Blur:
            accentPolicy.AccentState =
                static_cast<DWORD>(ACCENT_STATE::ACCENT_ENABLE_BLURBEHIND);
            accentPolicy.AccentFlags |= ACCENT_ENABLE_GRADIENT_COLOR;
            break;
        case EffectType::AcrylicBlur:
            accentPolicy.AccentState =
                static_cast<DWORD>(ACCENT_STATE::ACCENT_ENABLE_ACRYLICBLURBEHIND);
            break;
        case EffectType::ModernAcrylicBlur:
            accentPolicy.AccentState =
                static_cast<DWORD>(ACCENT_STATE::ACCENT_ENABLE_ACRYLICBLURBEHIND);
            accentPolicy.AccentFlags |= ACCENT_ENABLE_MODERN_ACRYLIC_RECIPE;
            break;
        case EffectType::Acrylic:
            backdropType = DWMSBT_TRANSIENTWINDOW;
            ncRendering = TRUE;
            windowTransparent = TRUE;
            break;
        case EffectType::Mica:
            mica = TRUE;
            backdropType = DWMSBT_MAINWINDOW;
            ncRendering = TRUE;
            windowTransparent = TRUE;
            break;
        case EffectType::MicaAlt:
            backdropType = DWMSBT_TABBEDWINDOW;
            ncRendering = TRUE;
            windowTransparent = TRUE;
            break;
        default:
            break;
    }

    if (SystemHelper::GetBuildNumber() > 22000 && SystemHelper::GetBuildNumber() < 22621) {
        DwmSetWindowAttribute(hwnd, 1029, &mica, sizeof(mica));
    }
    if (SystemHelper::GetBuildNumber() >= 22621) {
        DwmSetWindowAttribute(hwnd, DWMWA_SYSTEMBACKDROP_TYPE, &backdropType,
                              sizeof(DWM_SYSTEMBACKDROP_TYPE));
    }
    // DwmEnableBlurBehindWindow can deadlock when called synchronously from
    // inside a flyout's paint (seen on tooltips). Only call it when the effect
    // actually needs the window made transparent; there is nothing to clear on
    // a freshly seen window otherwise.
    if (windowTransparent) {
        DwmMakeWindowTransparent(hwnd, TRUE);
    }
    SetWindowCompositionAttribute(hwnd, &data);
    if (ncRendering) {
        TriggerWindowNCRendering(hwnd);
    }
}
}  // namespace EffectHelper

}  // namespace tf


// ===========================================================================
// Configuration: Windhawk settings -> engine values
//
// The settings schema and semantics follow the TranslucentFlyouts controller
// mod (GID0317): four categories (global / dropDown / menu / tooltip) where a
// category value of "use_global" (a sentinel index) inherits the global value.
// ===========================================================================

namespace tf {

namespace Cfg {

constexpr int kUseGlobalEffect = 9;   // dropDown/menu/tooltip effectType
constexpr int kUseGlobalCorner = 4;   // dropDown/menu/tooltip cornerType
constexpr int kUseGlobalBool = 2;     // no/yes/use_global dropdowns

struct Category {
    int disabledMode{0};
    int effectType{5};
    int cornerType{3};
    int enableDropShadowMode{0};
    int noBorderColorMode{0};
    int enableThemeColorizationMode{0};
    int darkThemeColorizationType{1};
    int lightThemeColorizationType{1};
    DWORD darkBorderColor{0xFF89B4FA};
    DWORD lightBorderColor{0xFF89B4FA};
    DWORD darkGradientColor{0xCC1E1E2E};
    DWORD lightGradientColor{0xCC1E1E2E};
};

struct MenuExtras {
    bool noSystemDropShadow{false};
    bool enableImmersiveStyle{true};
    bool enableCustomRendering{false};
    bool enableCompatibilityMode{false};
    bool noModernAppBackgroundColor{true};
    bool colorTreatAsTransparentEnabled{false};
    DWORD colorTreatAsTransparent{0};
    DWORD colorTreatAsTransparentThreshold{50};

    bool separator_disabled{false};
    DWORD separator_width{1000};
    DWORD separator_darkModeColor{0x30D9D9D9};
    DWORD separator_lightModeColor{0x30262626};
    bool separator_enableThemeColorization{false};
    int separator_darkThemeColorizationType{1};
    int separator_lightThemeColorizationType{1};

    bool focusing_disabled{false};
    DWORD focusing_cornerRadius{8};
    DWORD focusing_width{1000};
    DWORD focusing_darkModeColor{0xFFFFFFFF};
    DWORD focusing_lightModeColor{0xFF000000};
    bool focusing_enableThemeColorization{false};
    int focusing_darkThemeColorizationType{1};
    int focusing_lightThemeColorizationType{1};

    bool disabledHot_disabled{false};
    DWORD disabledHot_cornerRadius{8};
    DWORD disabledHot_darkModeColor{0x00000000};
    DWORD disabledHot_lightModeColor{0x00000000};
    bool disabledHot_enableThemeColorization{false};
    int disabledHot_darkThemeColorizationType{1};
    int disabledHot_lightThemeColorizationType{1};

    bool hot_disabled{false};
    DWORD hot_cornerRadius{8};
    DWORD hot_darkModeColor{0x41808080};
    DWORD hot_lightModeColor{0x30000000};
    bool hot_enableThemeColorization{false};
    int hot_darkThemeColorizationType{1};
    int hot_lightThemeColorizationType{1};

    bool enableFluentAnimation{false};
    DWORD fadeOutTime{350};
    DWORD popInTime{250};
    DWORD fadeInTime{87};
    DWORD popInStyle{0};
    DWORD startRatio{50};
    bool immediateInterupting{false};
};

struct TooltipExtras {
    bool noSystemDropShadow{false};
    DWORD darkModeColor{0xFFFFFFFF};
    DWORD lightModeColor{0xFF1A1A1A};
    DWORD marginsType{0};
    MARGINS margins{6, 6, 6, 6};
};

struct State {
    bool loaded{false};
    Category global;
    Category dropDown;
    Category menu;
    Category tooltip;
    MenuExtras menuExtras;
    TooltipExtras tooltipExtras;
    std::vector<std::wstring> processBlockList;
    std::vector<std::wstring> processDisabledList;
    std::vector<std::wstring> menuProcessDisabledList;
    std::vector<std::wstring> tooltipProcessDisabledList;
    std::vector<std::wstring> dropDownProcessDisabledList;
};

inline State& Get() {
    static State state;
    return state;
}

// ------------------------------------------------------------- raw values ---
//
// Settings are read straight from the engine's settings registry key.
// Windhawk stores every setting as a value under
// HKLM\SOFTWARE\Windhawk\Engine\Mods\<mod-id>\Settings, with dotted names for
// nested settings ("menu.effectType"). Values are REG_DWORD for numbers and
// checkboxes, and REG_SZ for option settings (the option key, e.g.
// "modern_acrylic"). Wh_GetIntSetting cannot be used for this: it returns 0
// both for "the user chose 0" and "the value is not set", so code defaults
// would be indistinguishable from a real zero. Reading the registry directly
// keeps "not set -> code default" exact.

inline std::wstring ToLower(std::wstring text) {
    for (wchar_t& ch : text) {
        ch = static_cast<wchar_t>(towlower(ch));
    }
    return text;
}

inline std::unordered_map<std::wstring, std::wstring>& Values() {
    static std::unordered_map<std::wstring, std::wstring> values;
    return values;
}

inline void ReloadValues() {
    auto& values = Values();
    values.clear();

    HKEY hKey{};
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                      L"SOFTWARE\\Windhawk\\Engine\\Mods\\" WH_MOD_ID L"\\Settings", 0,
                      KEY_QUERY_VALUE | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS) {
        return;
    }
    DWORD index = 0;
    for (;;) {
        wchar_t name[512]{};
        DWORD nameSize = _countof(name);
        BYTE data[1024]{};
        DWORD dataSize = sizeof(data);
        DWORD type = 0;
        LONG rc = RegEnumValueW(hKey, index++, name, &nameSize, nullptr, &type, data, &dataSize);
        if (rc == ERROR_NO_MORE_ITEMS) {
            break;
        }
        if (rc != ERROR_SUCCESS) {
            continue;
        }
        if (type == REG_DWORD && dataSize >= sizeof(DWORD)) {
            wchar_t text[32]{};
            swprintf_s(text, L"%u", *reinterpret_cast<DWORD*>(data));
            values[ToLower(name)] = text;
        } else if (type == REG_SZ && dataSize >= sizeof(wchar_t)) {
            values[ToLower(name)] =
                std::wstring(reinterpret_cast<wchar_t*>(data),
                             wcsnlen(reinterpret_cast<wchar_t*>(data),
                                     dataSize / sizeof(wchar_t)));
        }
    }
    RegCloseKey(hKey);
}

// Registry value names are matched case-insensitively (the map is keyed by
// lowercase name).
inline bool TryGetValue(PCWSTR name, std::wstring& result) {
    auto& values = Values();
    auto it = values.find(ToLower(name));
    if (it == values.end()) {
        return false;
    }
    result = it->second;
    return true;
}

inline bool ParseIntText(const std::wstring& text, int& result) {
    if (text.empty()) {
        return false;
    }
    wchar_t* end{nullptr};
    long value = wcstol(text.c_str(), &end, 10);
    if (end == text.c_str() || *end != 0) {
        return false;
    }
    result = static_cast<int>(value);
    return true;
}

inline int GetInt(const wchar_t* name, int fallback) {
    std::wstring value;
    int result{};
    if (!TryGetValue(name, value) || !ParseIntText(value, result)) {
        return fallback;
    }
    return result;
}

// ---------------------------------------------------------------- parsing ---

inline DWORD ParseColorSetting(PCWSTR value, DWORD fallback) {
    if (!value || !*value) {
        return fallback;
    }
    PCWSTR p = value;
    while (*p == L' ' || *p == L'\t') {
        p++;
    }
    if ((p[0] == L'0') && (p[1] == L'x' || p[1] == L'X')) {
        p += 2;
    }
    wchar_t* end{nullptr};
    unsigned long long parsed = wcstoull(p, &end, 16);
    if (end == p) {
        return fallback;
    }
    return static_cast<DWORD>(parsed);
}

inline std::vector<std::wstring> ParseProcessList(PCWSTR value) {
    std::vector<std::wstring> result;
    if (!value) {
        return result;
    }
    std::wstring current;
    for (PCWSTR p = value; *p; p++) {
        if (*p == L',' || *p == L';' || *p == L'\n' || *p == L'\r') {
            if (!current.empty()) {
                result.push_back(current);
                current.clear();
            }
        } else if (*p != L' ' && *p != L'\t') {
            current.push_back(*p);
        }
    }
    if (!current.empty()) {
        result.push_back(current);
    }
    return result;
}

inline bool WildcardMatch(PCWSTR pattern, PCWSTR text) {
    if (!pattern || !text) {
        return false;
    }
    PCWSTR p = pattern;
    PCWSTR t = text;
    PCWSTR starP{nullptr};
    PCWSTR starT{nullptr};
    while (*t) {
        if (*p == L'*') {
            starP = p++;
            starT = t;
        } else if (towlower(*p) == towlower(*t)) {
            p++;
            t++;
        } else if (starP) {
            p = starP + 1;
            t = ++starT;
        } else {
            return false;
        }
    }
    while (*p == L'*') {
        p++;
    }
    return *p == 0;
}

inline bool MatchesProcessList(const std::vector<std::wstring>& list, const std::wstring& name) {
    for (const auto& entry : list) {
        if (WildcardMatch(entry.c_str(), name.c_str())) {
            return true;
        }
    }
    return false;
}

// --------------------------------------------------------------- loading ---

// Option key -> internal index tables (identical to the controller's mapping).
struct SettingChoice {
    const wchar_t* key;
    int value;
};

inline constexpr SettingChoice kEffectGlobal[] = {
    {L"none", 0},        {L"transparent", 1},  {L"solid", 2},       {L"blurred", 3},
    {L"acrylic", 4},     {L"modern_acrylic", 5}, {L"acrylic_bg", 6}, {L"mica_bg", 7},
    {L"mica_variant", 8},
};

inline constexpr SettingChoice kEffectPart[] = {
    {L"none", 0},        {L"transparent", 1},  {L"solid", 2},        {L"blurred", 3},
    {L"acrylic", 4},     {L"modern_acrylic", 5}, {L"acrylic_bg", 6}, {L"mica_bg", 7},
    {L"mica_variant", 8}, {L"use_global", 9},
};

inline constexpr SettingChoice kCornerGlobal[] = {
    {L"dont_change", 0}, {L"sharp", 1}, {L"large_round", 2}, {L"small_round", 3},
};

inline constexpr SettingChoice kCornerPart[] = {
    {L"dont_change", 0}, {L"sharp", 1},          {L"large_round", 2},
    {L"small_round", 3}, {L"use_global", 4},
};

inline constexpr SettingChoice kTriState[] = {
    {L"no", 0}, {L"yes", 1}, {L"use_global", 2},
};

// Options are textual in the controller schema, but older exports stored the
// numeric index; both are accepted.
inline constexpr SettingChoice kColorizationType[] = {
    {L"start_background", 0}, {L"start_hover", 1},   {L"system_accent", 2},
    {L"accent_dark1", 3},     {L"accent_dark2", 4},  {L"accent_dark3", 5},
    {L"accent_light1", 6},    {L"accent_light2", 7}, {L"accent_light3", 8},
};

inline constexpr SettingChoice kPopInStyle[] = {
    {L"slide_down", 0}, {L"ripple", 1}, {L"smooth_scroll", 2}, {L"smooth_zoom", 3},
};

inline constexpr SettingChoice kMarginsType[] = {
    {L"add_to_existing", 0}, {L"replace_existing", 1},
};

inline int GetBool(const wchar_t* name, int fallback) {
    std::wstring value;
    if (!TryGetValue(name, value) || value.empty()) {
        return fallback;
    }
    if (!_wcsicmp(value.c_str(), L"yes") || !_wcsicmp(value.c_str(), L"true") ||
        !_wcsicmp(value.c_str(), L"on") || value == L"1") {
        return 1;
    }
    if (!_wcsicmp(value.c_str(), L"no") || !_wcsicmp(value.c_str(), L"false") ||
        !_wcsicmp(value.c_str(), L"off") || value == L"0") {
        return 0;
    }
    return fallback;
}

inline int GetMappedInt(const wchar_t* name, const SettingChoice* choices, size_t count,
                        int fallback) {
    std::wstring value;
    if (!TryGetValue(name, value) || value.empty()) {
        return fallback;
    }
    for (size_t i = 0; i < count; i++) {
        if (!_wcsicmp(value.c_str(), choices[i].key)) {
            return choices[i].value;
        }
    }
    int numeric{};
    return ParseIntText(value, numeric) ? numeric : fallback;
}

inline DWORD GetColor(const wchar_t* name, DWORD fallback) {
    std::wstring value;
    if (!TryGetValue(name, value) || value.empty()) {
        return fallback;
    }
    return ParseColorSetting(value.c_str(), fallback);
}

inline std::wstring GetString(const wchar_t* name) {
    std::wstring value;
    TryGetValue(name, value);
    return value;
}

inline int GetColorizationType(const wchar_t* name, int fallback) {
    return GetMappedInt(name, kColorizationType, _countof(kColorizationType), fallback);
}

inline void ReadCategory(PCWSTR prefix, Category& category, bool isGlobal) {
    wchar_t key[160]{};
    auto make = [&](const wchar_t* name) -> const wchar_t* {
        swprintf_s(key, L"%s.%s", prefix, name);
        return key;
    };

    category.effectType =
        GetMappedInt(make(L"effectType"), isGlobal ? kEffectGlobal : kEffectPart,
                     isGlobal ? _countof(kEffectGlobal) : _countof(kEffectPart),
                     isGlobal ? 5 : kUseGlobalEffect);
    category.cornerType =
        GetMappedInt(make(L"cornerType"), isGlobal ? kCornerGlobal : kCornerPart,
                     isGlobal ? _countof(kCornerGlobal) : _countof(kCornerPart),
                     isGlobal ? 3 : kUseGlobalCorner);
    category.enableDropShadowMode =
        GetBool(make(L"enableDropShadow"), isGlobal ? 0 : kUseGlobalBool);
    category.noBorderColorMode = GetBool(make(L"noBorderColor"), isGlobal ? 0 : kUseGlobalBool);
    category.enableThemeColorizationMode =
        GetBool(make(L"enableThemeColorization"), isGlobal ? 0 : kUseGlobalBool);
    category.darkThemeColorizationType = GetColorizationType(make(L"darkModeThemeColorizationType"), 1);
    category.lightThemeColorizationType = GetColorizationType(make(L"lightModeThemeColorizationType"), 1);
    // Catppuccin Mocha: blue border (#89B4FA), base tint (#1E1E2E) at about 60% alpha.
    category.darkBorderColor = GetColor(make(L"darkModeBorderColor"), 0xFF89B4FA);
    category.lightBorderColor = GetColor(make(L"lightModeBorderColor"), 0xFF89B4FA);
    category.darkGradientColor = GetColor(make(L"darkModeGradientColor"), 0xCC1E1E2E);
    category.lightGradientColor = GetColor(make(L"lightModeGradientColor"), 0xCC1E1E2E);
    category.disabledMode = GetBool(make(L"disabled"), isGlobal ? 0 : kUseGlobalBool);
}

inline void Load() {
    static std::mutex loadLock;
    std::lock_guard<std::mutex> guard(loadLock);

    State& state = Get();
    ReloadValues();

    ReadCategory(L"global", state.global, true);
    ReadCategory(L"dropDown", state.dropDown, false);
    ReadCategory(L"menu", state.menu, false);
    ReadCategory(L"tooltip", state.tooltip, false);

    MenuExtras& ex = state.menuExtras;
    ex.noSystemDropShadow = GetBool(L"menu.noSystemDropShadow", 0) != 0;
    ex.enableImmersiveStyle = GetBool(L"menu.enableImmersiveStyle", 1) != 0;
    ex.enableCustomRendering = GetBool(L"menu.enableCustomRendering", 0) != 0;
    ex.enableCompatibilityMode = GetBool(L"menu.enableCompatibilityMode", 0) != 0;
    ex.noModernAppBackgroundColor = GetBool(L"menu.noModernAppBackgroundColor", 1) != 0;
    ex.colorTreatAsTransparentEnabled =
        GetBool(L"menu.colorTreatAsTransparentEnabled", 0) != 0;
    ex.colorTreatAsTransparent = GetColor(L"menu.colorTreatAsTransparent", 0x00000000);
    ex.colorTreatAsTransparentThreshold =
        (DWORD)GetInt(L"menu.colorTreatAsTransparentThreshold", 50);

    ex.separator_disabled = GetBool(L"menu.separator_disabled", 0) != 0;
    ex.separator_width = (DWORD)GetInt(L"menu.separator_width", 1000);
    ex.separator_darkModeColor = GetColor(L"menu.separator_darkModeColor", 0x30D9D9D9);
    ex.separator_lightModeColor = GetColor(L"menu.separator_lightModeColor", 0x30262626);
    ex.separator_enableThemeColorization =
        GetBool(L"menu.separator_enableThemeColorization", 0) != 0;
    ex.separator_darkThemeColorizationType =
        GetColorizationType(L"menu.separator_darkThemeColorizationType", 1);
    ex.separator_lightThemeColorizationType =
        GetColorizationType(L"menu.separator_lightThemeColorizationType", 1);

    ex.focusing_disabled = GetBool(L"menu.focusing_disabled", 0) != 0;
    ex.focusing_cornerRadius = (DWORD)GetInt(L"menu.focusing_cornerRadius", 8);
    ex.focusing_width = (DWORD)GetInt(L"menu.focusing_width", 1000);
    ex.focusing_darkModeColor = GetColor(L"menu.focusing_darkModeColor", 0xFFFFFFFF);
    ex.focusing_lightModeColor = GetColor(L"menu.focusing_lightModeColor", 0xFF000000);
    ex.focusing_enableThemeColorization =
        GetBool(L"menu.focusing_enableThemeColorization", 0) != 0;
    ex.focusing_darkThemeColorizationType =
        GetColorizationType(L"menu.focusing_darkThemeColorizationType", 1);
    ex.focusing_lightThemeColorizationType =
        GetColorizationType(L"menu.focusing_lightThemeColorizationType", 1);

    ex.disabledHot_disabled = GetBool(L"menu.disabledHot_disabled", 0) != 0;
    ex.disabledHot_cornerRadius = (DWORD)GetInt(L"menu.disabledHot_cornerRadius", 8);
    ex.disabledHot_darkModeColor = GetColor(L"menu.disabledHot_darkModeColor", 0x00000000);
    ex.disabledHot_lightModeColor = GetColor(L"menu.disabledHot_lightModeColor", 0x00000000);
    ex.disabledHot_enableThemeColorization =
        GetBool(L"menu.disabledHot_enableThemeColorization", 0) != 0;
    ex.disabledHot_darkThemeColorizationType =
        GetColorizationType(L"menu.disabledHot_darkThemeColorizationType", 1);
    ex.disabledHot_lightThemeColorizationType =
        GetColorizationType(L"menu.disabledHot_lightThemeColorizationType", 1);

    ex.hot_disabled = GetBool(L"menu.hot_disabled", 0) != 0;
    ex.hot_cornerRadius = (DWORD)GetInt(L"menu.hot_cornerRadius", 8);
    ex.hot_darkModeColor = GetColor(L"menu.hot_darkModeColor", 0x41808080);
    ex.hot_lightModeColor = GetColor(L"menu.hot_lightModeColor", 0x30000000);
    ex.hot_enableThemeColorization =
        GetBool(L"menu.hot_enableThemeColorization", 0) != 0;
    ex.hot_darkThemeColorizationType =
        GetColorizationType(L"menu.hot_darkThemeColorizationType", 1);
    ex.hot_lightThemeColorizationType =
        GetColorizationType(L"menu.hot_lightThemeColorizationType", 1);

    ex.enableFluentAnimation = GetBool(L"menu.enableFluentAnimation", 0) != 0;
    ex.fadeOutTime = (DWORD)GetInt(L"menu.animation_fadeOutTime", 350);
    ex.popInTime = (DWORD)GetInt(L"menu.animation_popInTime", 250);
    ex.fadeInTime = (DWORD)GetInt(L"menu.animation_fadeInTime", 87);
    ex.popInStyle = (DWORD)GetMappedInt(L"menu.animation_popInStyle", kPopInStyle,
                                        _countof(kPopInStyle), 0);
    ex.startRatio = (DWORD)GetInt(L"menu.animation_startRatio", 50);
    ex.immediateInterupting =
        GetBool(L"menu.animation_enableImmediateInterupting", 0) != 0;

    TooltipExtras& tip = state.tooltipExtras;
    tip.noSystemDropShadow = GetBool(L"tooltip.noSystemDropShadow", 0) != 0;
    tip.darkModeColor = GetColor(L"tooltip.darkModeColor", 0xFFFFFFFF);
    tip.lightModeColor = GetColor(L"tooltip.lightModeColor", 0xFF1A1A1A);
    tip.marginsType = (DWORD)GetMappedInt(L"tooltip.marginsType", kMarginsType,
                                          _countof(kMarginsType), 0);
    tip.margins.cxLeftWidth = (LONG)GetInt(L"tooltip.marginLeft", 6);
    tip.margins.cxRightWidth = (LONG)GetInt(L"tooltip.marginRight", 6);
    tip.margins.cyTopHeight = (LONG)GetInt(L"tooltip.marginTop", 6);
    tip.margins.cyBottomHeight = (LONG)GetInt(L"tooltip.marginBottom", 6);

    auto readList = [](const wchar_t* name) { return ParseProcessList(GetString(name).c_str()); };
    state.processBlockList = readList(L"advancedFunctions.processBlockList");
    state.processDisabledList = readList(L"advancedFunctions.processDisabledList");
    state.menuProcessDisabledList = readList(L"advancedFunctions.menuProcessDisabledList");
    state.tooltipProcessDisabledList = readList(L"advancedFunctions.tooltipProcessDisabledList");
    state.dropDownProcessDisabledList = readList(L"advancedFunctions.dropDownProcessDisabledList");

    state.loaded = true;
}

}  // namespace Cfg

// ===========================================================================
// Api: the queries the engine uses (port of TFMain/ApiEx.cpp + Api.cpp)
// ===========================================================================

namespace Api {

struct WindowBackdropEffectContext {
    DWORD effectType;
    DWORD enableDropShadow;
    DWORD gradientColor;
};

struct BorderContext {
    bool colorUseNone;
    bool colorUseDefault;
    DWORD color;
    DWM_WINDOW_CORNER_PREFERENCE cornerType;
};

struct MenuCustomRenderingContext {
    bool enable;

    bool separator_disabled;
    DWORD separator_cornerRadius;
    DWORD separator_color;
    DWORD separator_width;

    bool focusing_disabled;
    DWORD focusing_cornerRadius;
    DWORD focusing_color;
    DWORD focusing_width;

    bool disabledHot_disabled;
    DWORD disabledHot_cornerRadius;
    DWORD disabledHot_color;

    bool hot_disabled;
    DWORD hot_cornerRadius;
    DWORD hot_color;
};

struct MenuIconBackgroundColorRemovalContext {
    bool enable;
    DWORD colorTreatAsTransparent;
    DWORD colorTreatAsTransparentThreshold;
};

struct FlyoutAnimationContext {
    bool enable;
    DWORD fadeOutTime;
    bool immediateInterupting;
    DWORD startRatio;
    DWORD popInTime;
    DWORD fadeInTime;
    DWORD popInStyle;
};

struct TooltipRenderingContext {
    COLORREF color;
    DWORD marginsType;
    MARGINS margins;
};

inline bool IsGlobalPart(std::wstring_view part) { return part.empty(); }

inline const Cfg::Category& GlobalCategory() { return Cfg::Get().global; }

// Maps a part name ("Menu" / "DropDown" / "Tooltip" / "") to its category.
inline Cfg::Category& CategoryForPart(std::wstring_view part) {
    Cfg::State& state = Cfg::Get();
    if (!_wcsicmp(std::wstring(part).c_str(), L"Menu")) {
        return state.menu;
    }
    if (!_wcsicmp(std::wstring(part).c_str(), L"DropDown")) {
        return state.dropDown;
    }
    if (!_wcsicmp(std::wstring(part).c_str(), L"Tooltip")) {
        return state.tooltip;
    }
    return state.global;
}

inline int ResolveInt(std::wstring_view part, int categoryValue, int sentinel, int globalValue) {
    if (IsGlobalPart(part) || categoryValue == sentinel) {
        return globalValue;
    }
    return categoryValue;
}

inline bool ResolveBoolMode(std::wstring_view part, int categoryMode, bool globalValue) {
    if (IsGlobalPart(part) || categoryMode == Cfg::kUseGlobalBool) {
        return globalValue;
    }
    return categoryMode != 0;
}

inline const wchar_t* ThemeColorizationTypeToName(int index) {
    static const wchar_t* kTypes[] = {
        L"ImmersiveStartBackground",       L"ImmersiveStartHoverBackground",
        L"ImmersiveSystemAccent",          L"ImmersiveSystemAccentDark1",
        L"ImmersiveSystemAccentDark2",     L"ImmersiveSystemAccentDark3",
        L"ImmersiveSystemAccentLight1",    L"ImmersiveSystemAccentLight2",
        L"ImmersiveSystemAccentLight3",
    };
    if (index < 0 || index > 8) {
        return kTypes[1];
    }
    return kTypes[index];
}

inline bool IsPartDisabled(std::wstring_view part) {
    Cfg::State& state = Cfg::Get();
    const Cfg::Category& global = state.global;
    const std::wstring processName = Utils::GetProcessName();

    bool globalDisabled = global.disabledMode != 0;
    globalDisabled = globalDisabled || Cfg::MatchesProcessList(state.processDisabledList, processName);
    if (globalDisabled) {
        return true;
    }

    const Cfg::Category& category = CategoryForPart(part);
    bool partDisabled = ResolveBoolMode(part, category.disabledMode, false);
    if (!IsGlobalPart(part)) {
        if (!_wcsicmp(std::wstring(part).c_str(), L"Menu")) {
            partDisabled =
                partDisabled || Cfg::MatchesProcessList(state.menuProcessDisabledList, processName);
        } else if (!_wcsicmp(std::wstring(part).c_str(), L"Tooltip")) {
            partDisabled = partDisabled ||
                           Cfg::MatchesProcessList(state.tooltipProcessDisabledList, processName);
        } else if (!_wcsicmp(std::wstring(part).c_str(), L"DropDown")) {
            partDisabled = partDisabled ||
                           Cfg::MatchesProcessList(state.dropDownProcessDisabledList, processName);
        }
    }
    return partDisabled;
}

inline bool IsCurrentProcessInBlockList() {
    Cfg::State& state = Cfg::Get();
    return Cfg::MatchesProcessList(state.processBlockList, Utils::GetProcessName());
}

// ------------------------------------------------------------------ query ---

inline void QueryBackdropEffectContext(std::wstring_view part, bool darkMode,
                                       WindowBackdropEffectContext& context) {
    RtlSecureZeroMemory(&context, sizeof(context));
    Cfg::State& state = Cfg::Get();
    Cfg::Category& category = CategoryForPart(part);
    const Cfg::Category& global = state.global;

    context.effectType = static_cast<DWORD>(
        ResolveInt(part, category.effectType, Cfg::kUseGlobalEffect, global.effectType));
    context.enableDropShadow =
        ResolveBoolMode(part, category.enableDropShadowMode, global.enableDropShadowMode != 0)
            ? 1
            : 0;
    context.gradientColor = darkMode ? category.darkGradientColor : category.lightGradientColor;
}

inline void QueryBorderContext(std::wstring_view part, bool darkMode, BorderContext& context) {
    RtlSecureZeroMemory(&context, sizeof(context));
    Cfg::State& state = Cfg::Get();
    Cfg::Category& category = CategoryForPart(part);
    const Cfg::Category& global = state.global;

    context.colorUseDefault = true;
    context.colorUseNone =
        ResolveBoolMode(part, category.noBorderColorMode, global.noBorderColorMode != 0);
    if (!context.colorUseNone) {
        bool enableColorization = ResolveBoolMode(
            part, category.enableThemeColorizationMode, global.enableThemeColorizationMode != 0);
        if (enableColorization) {
            int typeIndex = darkMode ? category.darkThemeColorizationType
                                     : category.lightThemeColorizationType;
            context.color = ThemeHelper::GetThemeColorizationColor(
                ThemeColorizationTypeToName(typeIndex));
            context.colorUseDefault = false;
        } else {
            context.color = darkMode ? category.darkBorderColor : category.lightBorderColor;
            context.colorUseDefault = false;
        }
    } else {
        context.color = DWMWA_COLOR_NONE;
        context.colorUseDefault = false;
    }

    int cornerIndex = ResolveInt(part, category.cornerType, Cfg::kUseGlobalCorner,
                                 global.cornerType);
    switch (cornerIndex) {
        case 1:
            context.cornerType = DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DONOTROUND;
            break;
        case 2:
            context.cornerType = DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUND;
            break;
        case 3:
            context.cornerType = DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUNDSMALL;
            break;
        default:
            context.cornerType = DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DEFAULT;
            break;
    }
    if (!SystemHelper::IsWindows11()) {
        context.cornerType = DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DONOTROUND;
    }
}

inline void QueryMenuCustomRenderingContext(bool darkMode, MenuCustomRenderingContext& context) {
    RtlSecureZeroMemory(&context, sizeof(context));
    Cfg::MenuExtras& ex = Cfg::Get().menuExtras;

    context.enable = ex.enableCustomRendering;
    if (!context.enable) {
        return;
    }

    context.separator_disabled = ex.separator_disabled;
    if (!context.separator_disabled) {
        context.separator_width = ex.separator_width;
        context.separator_color =
            darkMode ? ex.separator_darkModeColor : ex.separator_lightModeColor;
        if (ex.separator_enableThemeColorization) {
            context.separator_color = ThemeHelper::GetThemeColorizationColor(
                ThemeColorizationTypeToName(darkMode ? ex.separator_darkThemeColorizationType
                                                     : ex.separator_lightThemeColorizationType));
        }
    }

    context.focusing_disabled = ex.focusing_disabled;
    if (!context.focusing_disabled) {
        context.focusing_cornerRadius = ex.focusing_cornerRadius;
        context.focusing_width = ex.focusing_width;
        context.focusing_color =
            darkMode ? ex.focusing_darkModeColor : ex.focusing_lightModeColor;
        if (ex.focusing_enableThemeColorization) {
            context.focusing_color = ThemeHelper::GetThemeColorizationColor(
                ThemeColorizationTypeToName(darkMode ? ex.focusing_darkThemeColorizationType
                                                     : ex.focusing_lightThemeColorizationType));
        }
    }

    context.disabledHot_disabled = ex.disabledHot_disabled;
    if (!context.disabledHot_disabled) {
        context.disabledHot_cornerRadius = ex.disabledHot_cornerRadius;
        context.disabledHot_color =
            darkMode ? ex.disabledHot_darkModeColor : ex.disabledHot_lightModeColor;
        if (ex.disabledHot_enableThemeColorization) {
            context.disabledHot_color = ThemeHelper::GetThemeColorizationColor(
                ThemeColorizationTypeToName(darkMode ? ex.disabledHot_darkThemeColorizationType
                                                     : ex.disabledHot_lightThemeColorizationType));
        }
    }

    context.hot_disabled = ex.hot_disabled;
    if (!context.hot_disabled) {
        context.hot_cornerRadius = ex.hot_cornerRadius;
        context.hot_color = darkMode ? ex.hot_darkModeColor : ex.hot_lightModeColor;
        if (ex.hot_enableThemeColorization) {
            context.hot_color = ThemeHelper::GetThemeColorizationColor(
                ThemeColorizationTypeToName(darkMode ? ex.hot_darkThemeColorizationType
                                                     : ex.hot_lightThemeColorizationType));
        }
    }
}

inline void QueryMenuIconBackgroundColorRemovalContext(
    MenuIconBackgroundColorRemovalContext& context) {
    RtlSecureZeroMemory(&context, sizeof(context));
    Cfg::MenuExtras& ex = Cfg::Get().menuExtras;
    context.enable = ex.colorTreatAsTransparentEnabled;
    if (context.enable) {
        context.colorTreatAsTransparent = ex.colorTreatAsTransparent;
        context.colorTreatAsTransparentThreshold = ex.colorTreatAsTransparentThreshold;
    }
}

inline void QueryFlyoutAnimationContext(std::wstring_view part, FlyoutAnimationContext& context) {
    RtlSecureZeroMemory(&context, sizeof(context));
    if (_wcsicmp(std::wstring(part).c_str(), L"Menu") != 0) {
        // Dropdown animation settings exist but are not ported yet; keep off.
        return;
    }
    Cfg::MenuExtras& ex = Cfg::Get().menuExtras;
    context.enable = ex.enableFluentAnimation;
    context.fadeOutTime = ex.fadeOutTime;
    if (context.enable) {
        context.startRatio = ex.startRatio;
        context.popInTime = ex.popInTime;
        context.fadeInTime = ex.fadeInTime;
        context.popInStyle = ex.popInStyle;
        context.immediateInterupting = ex.immediateInterupting;
    }
}

inline void QueryTooltipRenderingContext(TooltipRenderingContext& context, bool darkMode) {
    RtlSecureZeroMemory(&context, sizeof(context));
    Cfg::TooltipExtras& tip = Cfg::Get().tooltipExtras;
    context.color = Utils::MakeCOLORREF(darkMode ? tip.darkModeColor : tip.lightModeColor);
    context.marginsType = tip.marginsType;
    context.margins = tip.margins;
}

// ------------------------------------------------------------------ apply ---

inline void ApplyBorderEffect(HWND hWnd, bool darkMode, const BorderContext& border) {
    EffectHelper::EnableWindowDarkMode(hWnd, darkMode);
    if (SystemHelper::IsWindows11()) {
        if (border.cornerType != DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DEFAULT) {
            DwmSetWindowAttribute(hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, &border.cornerType,
                                  sizeof(border.cornerType));
        }
        COLORREF color{Utils::MakeCOLORREF(border.color)};
        if (border.colorUseNone) {
            color = border.color;
        }
        if (!border.colorUseDefault || border.colorUseNone) {
            DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &color, sizeof(color));
        }
    }
    DwmTransitionOwnedWindow(hWnd, DWMTRANSITION_OWNEDWINDOW_REPOSITION);
}

inline void ApplyBackdropEffect(HWND hWnd, bool darkMode,
                                const WindowBackdropEffectContext& backdropContext) {
    EffectHelper::EnableWindowDarkMode(hWnd, darkMode);
    EffectHelper::SetWindowBackdrop(
        hWnd, backdropContext.enableDropShadow,
        Utils::MakeCOLORREF(backdropContext.gradientColor) |
            (static_cast<DWORD>(Utils::GetAlphaFromARGB(backdropContext.gradientColor)) << 24),
        backdropContext.effectType);
    DwmTransitionOwnedWindow(hWnd, DWMTRANSITION_OWNEDWINDOW_REPOSITION);
}

inline void ApplyEffect(HWND hWnd, bool darkMode, const WindowBackdropEffectContext& backdropContext,
                        const BorderContext& border) {
    ApplyBackdropEffect(hWnd, darkMode, backdropContext);
    ApplyBorderEffect(hWnd, darkMode, border);
}

inline void DropEffect(std::wstring_view part, HWND hWnd) {
    EffectHelper::SetWindowBackdrop(hWnd, FALSE, 0,
                                    static_cast<DWORD>(EffectHelper::EffectType::None));
    if (SystemHelper::IsWindows11()) {
        auto cornerType{DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DEFAULT};
        if (!_wcsicmp(std::wstring(part).c_str(), L"Menu")) {
            cornerType = DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUNDSMALL;
        }
        DwmSetWindowAttribute(hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerType,
                              sizeof(cornerType));
        COLORREF color{DWMWA_COLOR_NONE};
        DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &color, sizeof(color));
    }
    InvalidateRect(hWnd, nullptr, TRUE);
}

}  // namespace Api

}  // namespace tf

// ===========================================================================
// Dark menus: dark mode for every Win32 menu and menu bar.
//
// Merged in from the "Dark mode context menus" mod by Mgg Sk
// (https://github.com/MGGSK/DarkMenus, based on win32-darkmode by adzm and
// Notepad++'s NppDarkMode). It used to be a separate mod that had to be paired with
// this one; running both cost a second injection into every process.
// ===========================================================================

namespace tf::DarkMenus {

constexpr COLORREF kMenuColour = 0x2C2C2C;
constexpr COLORREF kItemForeground = 0xFFFFFF;
constexpr COLORREF kItemForegroundDisabled = 0xAAAAAA;

HBRUSH g_menuBrush = nullptr;
HBRUSH g_separatorBrush = nullptr;
HBRUSH g_hoverBrush = nullptr;
HBRUSH g_selectedBrush = nullptr;
HFONT g_iconFont = nullptr;
HMODULE g_uxtheme = nullptr;
thread_local HTHEME g_menuBarTheme = nullptr;

enum class AppMode { Default, AllowDark, ForceDark, ForceLight };

using FlushMenuThemesFn = void(WINAPI*)();
using SetPreferredAppModeFn = AppMode(WINAPI*)(AppMode);
using ShouldAppsUseDarkModeFn = bool(WINAPI*)();

FlushMenuThemesFn g_flushMenuThemes = nullptr;
SetPreferredAppModeFn g_setPreferredAppMode = nullptr;
ShouldAppsUseDarkModeFn g_shouldAppsUseDarkMode = nullptr;

std::atomic<AppMode> g_mode{AppMode::Default};

void* g_hookTargets[5]{};
int g_hookTargetCount = 0;

// Undocumented menu bar messages and structs (win32-darkmode).
constexpr UINT WM_UAHDRAWMENU = 0x91;
constexpr UINT WM_UAHDRAWMENUITEM = 0x92;

union UAHMENUITEMMETRICS {
    struct {
        DWORD cx;
        DWORD cy;
    } rgsizeBar[2];
    struct {
        DWORD cx;
        DWORD cy;
    } rgsizePopup[4];
};

struct UAHMENUPOPUPMETRICS {
    DWORD rgcx[4];
    DWORD fUpdateMaxWidths : 2;
};

struct UAHMENU {
    HMENU hMenu;
    HDC hdc;
    DWORD dwFlags;
};

struct UAHMENUITEM {
    int iPosition;
    UAHMENUITEMMETRICS umim;
    UAHMENUPOPUPMETRICS umpm;
};

struct UAHDRAWMENUITEM {
    DRAWITEMSTRUCT dis;
    UAHMENU um;
    UAHMENUITEM umi;
};

// The 1-pixel line under the menu bar that the theme leaves light.
void DrawMenuBarBottomLine(HWND hWnd) {
    MENUBARINFO menuBarInfo{sizeof(menuBarInfo)};
    if (!GetMenuBarInfo(hWnd, OBJID_MENU, 0, &menuBarInfo)) {
        return;
    }

    RECT rcClient;
    GetClientRect(hWnd, &rcClient);
    MapWindowPoints(hWnd, nullptr, reinterpret_cast<LPPOINT>(&rcClient), 2);

    RECT rcWindow;
    GetWindowRect(hWnd, &rcWindow);
    OffsetRect(&rcClient, -rcWindow.left, -rcWindow.top);

    RECT line = rcClient;
    line.bottom = line.top;
    line.top--;

    HDC hdc = GetWindowDC(hWnd);
    FillRect(hdc, &line, g_separatorBrush);
    ReleaseDC(hWnd, hdc);
}

// Paints the menu bar and its items. Returns true when the message was handled.
bool HandleMenuBarMessage(HWND hWnd, UINT uMsg, LPARAM lParam, LRESULT* result) {
    switch (uMsg) {
        case WM_UAHDRAWMENU: {
            const auto* drawingInfo = reinterpret_cast<UAHMENU*>(lParam);

            MENUBARINFO menuBarInfo{sizeof(menuBarInfo)};
            if (!GetMenuBarInfo(hWnd, OBJID_MENU, 0, &menuBarInfo)) {
                return false;
            }
            RECT rcWindow;
            if (!GetWindowRect(hWnd, &rcWindow)) {
                return false;
            }
            RECT rcMenu = menuBarInfo.rcBar;
            if (!OffsetRect(&rcMenu, -rcWindow.left, -rcWindow.top)) {
                return false;
            }
            FillRect(drawingInfo->hdc, &rcMenu, g_menuBrush);
            *result = 0;
            return true;
        }

        case WM_UAHDRAWMENUITEM: {
            auto* drawingInfo = reinterpret_cast<UAHDRAWMENUITEM*>(lParam);
            HBRUSH background = g_menuBrush;

            wchar_t menuString[256]{};
            MENUITEMINFOW itemInfo{sizeof(itemInfo), MIIM_STRING};
            itemInfo.dwTypeData = menuString;
            itemInfo.cch = (sizeof(menuString) / sizeof(wchar_t)) - 1;
            if (!GetMenuItemInfoW(drawingInfo->um.hMenu, drawingInfo->umi.iPosition, TRUE,
                                  &itemInfo)) {
                return false;
            }
            menuString[255] = L'\0';

            const UINT state = drawingInfo->dis.itemState;
            DWORD textFlags = DT_CENTER | DT_SINGLELINE | DT_VCENTER;
            int textStateId = 0;

            if ((state & ODS_INACTIVE) || (state & ODS_DEFAULT)) {
                textStateId = MBI_NORMAL;
            } else if (state & ODS_HOTLIGHT) {
                textStateId = MBI_HOT;
            } else if (state & ODS_SELECTED) {
                textStateId = MBI_PUSHED;
            } else if ((state & ODS_GRAYED) || (state & ODS_DISABLED)) {
                textStateId = MBI_DISABLED;
            }
            if (GetForegroundWindow() != hWnd) {
                textStateId = MBI_DISABLED;
            }

            if (state & ODS_HOTLIGHT) {
                background = g_hoverBrush;
            } else if (state & ODS_SELECTED) {
                background = g_selectedBrush;
            }
            if (state & ODS_NOACCEL) {
                textFlags |= DT_HIDEPREFIX;
            }

            if (!g_menuBarTheme) {
                g_menuBarTheme = OpenThemeData(hWnd, L"Menu");
            }

            const DTTOPTS textOptions{sizeof(textOptions), DTT_TEXTCOLOR,
                                      textStateId != MBI_DISABLED ? kItemForeground
                                                                  : kItemForegroundDisabled};
            FillRect(drawingInfo->um.hdc, &drawingInfo->dis.rcItem, background);

            // An item with no text is an MDI child's system menu or caption button.
            if (menuString[0] == L'\0') {
                const int offset = GetMenuItemCount(drawingInfo->um.hMenu) -
                                   drawingInfo->umi.iPosition;
                wchar_t glyph;
                if (drawingInfo->umi.iPosition == 0) {
                    glyph = 0xE700;  // menu
                } else if (offset == 3) {
                    glyph = 0xE921;  // minimize
                } else if (offset == 2) {
                    glyph = 0xE923;  // maximize
                } else if (offset == 1) {
                    glyph = 0xE8BB;  // close
                } else {
                    return false;
                }

                if (!g_iconFont) {
                    g_iconFont = CreateFontW(10, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                             CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                             DEFAULT_PITCH | FF_DONTCARE,
                                             L"Segoe Fluent Icons");
                }
                HFONT oldFont = SelectFont(drawingInfo->um.hdc, g_iconFont);
                const HRESULT hr = DrawThemeTextEx(
                    g_menuBarTheme, drawingInfo->um.hdc, MENU_BARITEM, MBI_NORMAL, &glyph, 1,
                    textFlags, &drawingInfo->dis.rcItem, &textOptions);
                SelectFont(drawingInfo->um.hdc, oldFont);
                if (FAILED(hr)) {
                    return false;
                }
                *result = 0;
                return true;
            }

            const HRESULT hr = DrawThemeTextEx(
                g_menuBarTheme, drawingInfo->um.hdc, MENU_BARITEM, MBI_NORMAL, menuString,
                itemInfo.cch, textFlags, &drawingInfo->dis.rcItem, &textOptions);
            if (FAILED(hr)) {
                return false;
            }
            *result = 0;
            return true;
        }

        case WM_THEMECHANGED:
        case WM_DESTROY:
            if (g_menuBarTheme) {
                CloseThemeData(g_menuBarTheme);
                g_menuBarTheme = nullptr;
            }
            return false;

        default:
            return false;
    }
}

bool IsDarkMenuBarWindow(HWND hWnd) {
    const AppMode mode = g_mode.load();
    const bool dark = mode == AppMode::ForceDark ||
                      (mode == AppMode::AllowDark && g_shouldAppsUseDarkMode &&
                       g_shouldAppsUseDarkMode());
    return dark && GetMenu(hWnd);
}

// Runs the original window procedure and then redraws the line under the menu bar.
template <typename Proc>
LRESULT RunMenuBarPass(HWND hWnd, UINT uMsg, LPARAM lParam, Proc&& original) {
    LRESULT result = 0;
    if (HandleMenuBarMessage(hWnd, uMsg, lParam, &result)) {
        return result;
    }
    if (uMsg == WM_ACTIVATE || uMsg == WM_NCPAINT) {
        result = original();
        DrawMenuBarBottomLine(hWnd);
        return result;
    }
    return original();
}

decltype(&DefWindowProcW) g_defWindowProcWOrig = nullptr;
LRESULT CALLBACK DefWindowProcWHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (!IsDarkMenuBarWindow(hWnd)) {
        return g_defWindowProcWOrig(hWnd, uMsg, wParam, lParam);
    }
    return RunMenuBarPass(hWnd, uMsg, lParam,
                          [&] { return g_defWindowProcWOrig(hWnd, uMsg, wParam, lParam); });
}

decltype(&DefWindowProcA) g_defWindowProcAOrig = nullptr;
LRESULT CALLBACK DefWindowProcAHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (!IsDarkMenuBarWindow(hWnd)) {
        return g_defWindowProcAOrig(hWnd, uMsg, wParam, lParam);
    }
    return RunMenuBarPass(hWnd, uMsg, lParam,
                          [&] { return g_defWindowProcAOrig(hWnd, uMsg, wParam, lParam); });
}

decltype(&DefFrameProcW) g_defFrameProcWOrig = nullptr;
LRESULT CALLBACK DefFrameProcWHook(HWND hWnd, HWND hMdiClient, UINT uMsg, WPARAM wParam,
                                   LPARAM lParam) {
    if (!IsDarkMenuBarWindow(hWnd)) {
        return g_defFrameProcWOrig(hWnd, hMdiClient, uMsg, wParam, lParam);
    }
    return RunMenuBarPass(hWnd, uMsg, lParam, [&] {
        return g_defFrameProcWOrig(hWnd, hMdiClient, uMsg, wParam, lParam);
    });
}

decltype(&DefFrameProcA) g_defFrameProcAOrig = nullptr;
LRESULT CALLBACK DefFrameProcAHook(HWND hWnd, HWND hMdiClient, UINT uMsg, WPARAM wParam,
                                   LPARAM lParam) {
    if (!IsDarkMenuBarWindow(hWnd)) {
        return g_defFrameProcAOrig(hWnd, hMdiClient, uMsg, wParam, lParam);
    }
    return RunMenuBarPass(hWnd, uMsg, lParam, [&] {
        return g_defFrameProcAOrig(hWnd, hMdiClient, uMsg, wParam, lParam);
    });
}

// Custom menu backgrounds break in dark mode (MGGSK/DarkMenus issues 16, 18 and 26),
// so every background an app sets is swapped. Under the translucent menu effect the
// brush has to be black, which adds nothing over the acrylic; with the effect off in
// this process it is the plain dark menu colour.
decltype(&SetMenuInfo) g_setMenuInfoOrig = nullptr;
BOOL WINAPI SetMenuInfoHook(HMENU hMenu, LPCMENUINFO info) {
    alignas(MENUINFO) BYTE buffer[256];
    if (!info || !(info->fMask & MIM_BACKGROUND) || info->cbSize > sizeof(buffer) ||
        g_mode.load() == AppMode::Default) {
        return g_setMenuInfoOrig(hMenu, info);
    }

    memcpy(buffer, info, info->cbSize);
    auto* copy = reinterpret_cast<LPMENUINFO>(buffer);
    copy->hbrBack = Api::IsPartDisabled(L"Menu")
                        ? g_menuBrush
                        : static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    return g_setMenuInfoOrig(hMenu, copy);
}

AppMode ReadMode() {
    const std::wstring value = Cfg::ToLower(Cfg::GetString(L"darkMenus.appMode"));
    if (value == L"allow_dark") {
        return AppMode::AllowDark;
    }
    if (value == L"off") {
        return AppMode::Default;
    }
    return AppMode::ForceDark;
}

void Apply(AppMode mode) {
    if (g_flushMenuThemes && g_setPreferredAppMode) {
        g_flushMenuThemes();
        g_setPreferredAppMode(mode);
    }
    g_mode.store(mode);
}

void Refresh() {
    Apply(ReadMode());
}

void InstallDarkMenuHook(HMODULE module, const char* name, void* hook, void** original) {
    FARPROC target = module ? GetProcAddress(module, name) : nullptr;
    if (!target) {
        Log::Write(L"[dark] %S not found", name);
        return;
    }
    if (WindhawkUtils::SetFunctionHook(reinterpret_cast<void*>(target), hook,
                                       reinterpret_cast<void**>(original))) {
        if (g_hookTargetCount < (int)std::size(g_hookTargets)) {
            g_hookTargets[g_hookTargetCount++] = reinterpret_cast<void*>(target);
        }
    } else {
        Log::Write(L"[dark] hook FAILED %S", name);
    }
}

void Install() {
    g_uxtheme = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!g_uxtheme) {
        return;
    }
    g_setPreferredAppMode =
        reinterpret_cast<SetPreferredAppModeFn>(GetProcAddress(g_uxtheme, MAKEINTRESOURCEA(135)));
    g_flushMenuThemes =
        reinterpret_cast<FlushMenuThemesFn>(GetProcAddress(g_uxtheme, MAKEINTRESOURCEA(136)));
    g_shouldAppsUseDarkMode =
        reinterpret_cast<ShouldAppsUseDarkModeFn>(GetProcAddress(g_uxtheme, MAKEINTRESOURCEA(132)));

    g_menuBrush = CreateSolidBrush(kMenuColour);
    g_separatorBrush = CreateSolidBrush(0x222222);
    g_hoverBrush = CreateSolidBrush(0x353535);
    g_selectedBrush = CreateSolidBrush(0x454545);

    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    InstallDarkMenuHook(user32, "DefWindowProcW", reinterpret_cast<void*>(DefWindowProcWHook),
                        reinterpret_cast<void**>(&g_defWindowProcWOrig));
    InstallDarkMenuHook(user32, "DefWindowProcA", reinterpret_cast<void*>(DefWindowProcAHook),
                        reinterpret_cast<void**>(&g_defWindowProcAOrig));
    InstallDarkMenuHook(user32, "DefFrameProcW", reinterpret_cast<void*>(DefFrameProcWHook),
                        reinterpret_cast<void**>(&g_defFrameProcWOrig));
    InstallDarkMenuHook(user32, "DefFrameProcA", reinterpret_cast<void*>(DefFrameProcAHook),
                        reinterpret_cast<void**>(&g_defFrameProcAOrig));
    InstallDarkMenuHook(user32, "SetMenuInfo", reinterpret_cast<void*>(SetMenuInfoHook),
                        reinterpret_cast<void**>(&g_setMenuInfoOrig));

    Refresh();
}

// Puts the system menu theme back and releases what Install created. The caller
// applies the hook removals.
void Uninstall() {
    Apply(AppMode::Default);
    for (int i = 0; i < g_hookTargetCount; i++) {
        Wh_RemoveFunctionHook(g_hookTargets[i]);
    }
    g_hookTargetCount = 0;

    // Processes that block win32k calls fail the GDI and theme cleanup calls below
    // (MGGSK/DarkMenus issue 9), so they keep their handles until exit.
    PROCESS_MITIGATION_SYSTEM_CALL_DISABLE_POLICY policy{};
    if (GetProcessMitigationPolicy(GetCurrentProcess(), ProcessSystemCallDisablePolicy, &policy,
                                   sizeof(policy)) &&
        policy.DisallowWin32kSystemCalls != 0) {
        return;
    }
    for (HBRUSH* brush : {&g_menuBrush, &g_separatorBrush, &g_hoverBrush, &g_selectedBrush}) {
        if (*brush) {
            DeleteObject(*brush);
            *brush = nullptr;
        }
    }
    if (g_iconFont) {
        DeleteObject(g_iconFont);
        g_iconFont = nullptr;
    }
    if (g_menuBarTheme) {
        CloseThemeData(g_menuBarTheme);
        g_menuBarTheme = nullptr;
    }
    if (g_uxtheme) {
        FreeLibrary(g_uxtheme);
        g_uxtheme = nullptr;
    }
}

}  // namespace tf::DarkMenus


// ===========================================================================
// Flyout handling: menus, tooltips and dropdown lists.
//
// The engine intercepts uxtheme drawing in the target process (the same
// functions the upstream TranslucentFlyouts hooks) and identifies the owning
// flyout window during paint. uxtheme paints flyouts into buffered/memory DCs,
// so WindowFromDC is not enough; the flyout window is found by class among the
// painting thread's windows.
// ===========================================================================

namespace tf {

namespace Handler {

enum class FlyoutType {
    Unknown,
    Menu,
    Tooltip,
    DropDown,
    // A menu drawn by an app with its own drawing code: leave it alone.
    ThirdParty,
};

struct WindowState {
    FlyoutType type{FlyoutType::Unknown};
    // The window this state belongs to (the map key, kept on the state so paint-time
    // helpers can query the window's current geometry).
    HWND hWnd{nullptr};
    bool darkMode{false};
    bool effectsApplied{false};
    DWORD tick{0};
    Api::WindowBackdropEffectContext backdrop{};
    Api::BorderContext border{};
    Api::MenuCustomRenderingContext customRendering{};
    Api::MenuIconBackgroundColorRemovalContext iconRemoval{};
    Api::FlyoutAnimationContext animation{};
    bool noSystemDropShadow{false};
    bool immersiveStyle{true};
    // Size and radius of the window region last set on a rounded menu; zero
    // when no region is set.
    int regionWidth{0};
    int regionHeight{0};
    int regionRadius{0};
    // The interior rect the background bands painted, recorded from the first
    // full-size POPUPBACKGROUND draw. The rim between it and the window edge is
    // the only area the border pass may clear; everything inside holds content.
    RECT bandRect{};
    bool bandRectValid{false};
    // The border pass framed this square menu on its DC, or left the border to the
    // native drawing. The watcher overlay must then stay off this menu.
    bool dcBorderPainted{false};
};

std::mutex g_windowsLock;
std::unordered_map<HWND, WindowState> g_windows;

// The window state of the flyout being painted on this thread (set by the
// hooks while a flyout paint is in progress).
thread_local WindowState* g_paintingState = nullptr;

constexpr size_t kMaxWindows = 64;

WindowState* FindWindowState(HWND hWnd) {
    if (!hWnd) {
        return nullptr;
    }
    std::lock_guard<std::mutex> lock(g_windowsLock);
    auto it = g_windows.find(hWnd);
    return it == g_windows.end() ? nullptr : &it->second;
}

WindowState& GetOrCreateWindowState(HWND hWnd) {
    std::lock_guard<std::mutex> lock(g_windowsLock);
    auto it = g_windows.find(hWnd);
    if (it != g_windows.end()) {
        return it->second;
    }
    if (g_windows.size() >= kMaxWindows) {
        // Drop the oldest entry.
        auto oldest = g_windows.begin();
        for (auto iter = g_windows.begin(); iter != g_windows.end(); ++iter) {
            if (iter->second.tick < oldest->second.tick) {
                oldest = iter;
            }
        }
        g_windows.erase(oldest);
    }
    WindowState& state = g_windows[hWnd];
    state.hWnd = hWnd;
    state.tick = GetTickCount();
    return state;
}

void RemoveWindowState(HWND hWnd) {
    std::lock_guard<std::mutex> lock(g_windowsLock);
    g_windows.erase(hWnd);
}

// ---------------------------------------------------------------- helpers ---

inline bool IsBalloonTooltip(HWND hWnd) {
    return (GetWindowLongPtrW(hWnd, GWL_STYLE) & TTS_BALLOON) == TTS_BALLOON;
}

inline bool IsTooltipWindow(HWND hWnd) {
    // An unthemed tooltip window (e.g. the WinForms ToolTip control, which
    // calls SetWindowTheme(hwnd, L"", L"") internally) paints its own classic
    // background and cannot show the backdrop effect; the original app skips
    // these too.
    return hWnd && !IsBalloonTooltip(hWnd) && GetWindowTheme(hWnd) != nullptr &&
           Utils::IsWindowClassContains(hWnd, L"tooltips_class32");
}

inline bool IsMenuWindow(HWND hWnd) { return Utils::IsPopupMenu(hWnd); }

inline bool IsDropDownWindow(HWND hWnd) {
    return Utils::IsWindowClassContains(hWnd, L"listviewpopup") ||
           Utils::IsWindowClassContains(hWnd, L"combolbox") ||
           Utils::IsWindowClassContains(hWnd, L"dropdown");
}

struct EnumWindowParam {
    FlyoutType type;
    HWND result;
};

BOOL CALLBACK EnumFlyoutProc(HWND hWnd, LPARAM lParam) {
    auto* param = reinterpret_cast<EnumWindowParam*>(lParam);
    bool match = false;
    switch (param->type) {
        case FlyoutType::Menu:
            match = IsMenuWindow(hWnd);
            break;
        case FlyoutType::Tooltip:
            match = IsTooltipWindow(hWnd);
            break;
        case FlyoutType::DropDown:
            match = IsDropDownWindow(hWnd);
            break;
        default:
            break;
    }
    if (match) {
        param->result = hWnd;
        return FALSE;
    }
    return TRUE;
}

HWND FindFlyoutWindowOnCurrentThread(FlyoutType type) {
    EnumWindowParam param{type, nullptr};
    EnumThreadWindows(GetCurrentThreadId(), EnumFlyoutProc, reinterpret_cast<LPARAM>(&param));
    return param.result;
}

// The flyout window for the DC being painted. Prefers WindowFromDC; falls back
// to the thread's window of the given type (buffered paint DCs have no window).
HWND ResolveFlyoutWindow(HDC hdc, FlyoutType type) {
    HWND w = WindowFromDC(hdc);
    if (w && (IsMenuWindow(w) || IsTooltipWindow(w) || IsDropDownWindow(w))) {
        return w;
    }
    return FindFlyoutWindowOnCurrentThread(type);
}

struct MenuSurfaceParam {
    int width;
    int height;
    bool visibleOnly;
    HWND result;
};

BOOL CALLBACK MatchMenuSurfaceProc(HWND hWnd, LPARAM lParam) {
    auto* param = reinterpret_cast<MenuSurfaceParam*>(lParam);
    if (!IsMenuWindow(hWnd) || (param->visibleOnly && !IsWindowVisible(hWnd))) {
        return TRUE;
    }
    RECT rc{};
    if (GetWindowRect(hWnd, &rc) && rc.right - rc.left == param->width &&
        rc.bottom - rc.top == param->height) {
        param->result = hWnd;
        return FALSE;
    }
    return TRUE;
}

// A buffered paint DC has no window, and the thread's first menu in z-order is the
// root menu even while a submenu paints (the 0.6.65 trace credited every submenu
// paint to the root menu). The buffer is sized to the window it paints, so the menu
// of that size is the one being drawn. |exact| is false when no size matched.
HWND ResolveMenuWindow(HDC hdc, bool& exact) {
    exact = false;
    HWND w = WindowFromDC(hdc);
    if (w && IsMenuWindow(w)) {
        exact = true;
        return w;
    }
    BITMAP surface{};
    HGDIOBJ bitmap = GetCurrentObject(hdc, OBJ_BITMAP);
    if (bitmap && GetObjectW(bitmap, sizeof(surface), &surface)) {
        // A menu is only visible after its first paint, so the hidden pass is needed.
        for (bool visibleOnly : {true, false}) {
            MenuSurfaceParam param{surface.bmWidth, surface.bmHeight, visibleOnly, nullptr};
            EnumThreadWindows(GetCurrentThreadId(), MatchMenuSurfaceProc, reinterpret_cast<LPARAM>(&param));
#ifdef TF_DEBUG_LOG
            Log::Write(L"[bp] surface=%ldx%ld visibleOnly=%d match=%p", surface.bmWidth,
                       surface.bmHeight, (int)visibleOnly, (void*)param.result);
#endif
            if (param.result) {
                exact = true;
                return param.result;
            }
        }
    }
    return FindFlyoutWindowOnCurrentThread(FlyoutType::Menu);
}

FlyoutType TypeForThemeClass(PCWSTR themeClass) {
    if (!_wcsicmp(themeClass, L"Menu")) {
        return FlyoutType::Menu;
    }
    if (!_wcsicmp(themeClass, L"Tooltip")) {
        return FlyoutType::Tooltip;
    }
    // Only the dropped-down list draws with the ListviewPopup theme class; the
    // closed combo box uses "Combobox" and must not be treated as a flyout.
    if (!_wcsicmp(themeClass, L"ListviewPopup")) {
        return FlyoutType::DropDown;
    }
    return FlyoutType::Unknown;
}

// Dark mode for menus: compare the menu's text color with the color of the
// dark menu theme (upstream method).
bool MenuShouldUseDarkMode(HTHEME hTheme) {
    COLORREF color{DWMWA_COLOR_NONE};
    COLORREF expectedColor{0};
    HTHEME darkTheme = OpenThemeData(nullptr, L"DarkMode::Menu");
    if (darkTheme) {
        HRESULT hr1 = GetThemeColor(hTheme, MENU_POPUPITEM, 0, TMT_TEXTCOLOR, &color);
        HRESULT hr2 = GetThemeColor(darkTheme, MENU_POPUPITEM, 0, TMT_TEXTCOLOR, &expectedColor);
        CloseThemeData(darkTheme);
        if (SUCCEEDED(hr1) && SUCCEEDED(hr2) && color == expectedColor) {
            return true;
        }
        return false;
    }
    return ThemeHelper::ShouldAppsUseDarkMode() && ThemeHelper::IsDarkModeAllowedForApp();
}

bool TooltipShouldUseDarkMode(HWND hWnd, HWND owner) {
    HWND tray = FindWindowW(L"Shell_TrayWnd", nullptr);
    if (tray && GetWindowThreadProcessId(tray, nullptr) == GetWindowThreadProcessId(hWnd, nullptr)) {
        static const auto ShouldSystemUseDarkMode = reinterpret_cast<bool(WINAPI*)()>(
            GetProcAddress(GetModuleHandleW(L"UxTheme.dll"), MAKEINTRESOURCEA(138)));
        return ShouldSystemUseDarkMode ? ShouldSystemUseDarkMode() : false;
    }
    (void)owner;
    return ThemeHelper::ShouldAppsUseDarkMode() && ThemeHelper::IsDarkModeAllowedForApp();
}

// Refresh the cached window state from the current settings.
void RefreshWindowState(HWND hWnd, WindowState& state, bool darkMode) {
    state.darkMode = darkMode;
    switch (state.type) {
        case FlyoutType::Menu: {
            state.noSystemDropShadow = Cfg::Get().menuExtras.noSystemDropShadow;
            state.immersiveStyle = Cfg::Get().menuExtras.enableImmersiveStyle;
            Api::QueryBackdropEffectContext(L"Menu", darkMode, state.backdrop);
            Api::QueryBorderContext(L"Menu", darkMode, state.border);
            Api::QueryMenuCustomRenderingContext(darkMode, state.customRendering);
            Api::QueryMenuIconBackgroundColorRemovalContext(state.iconRemoval);
            Api::QueryFlyoutAnimationContext(L"Menu", state.animation);
            break;
        }
        case FlyoutType::Tooltip: {
            state.noSystemDropShadow = Cfg::Get().tooltipExtras.noSystemDropShadow;
            Api::QueryBackdropEffectContext(L"Tooltip", darkMode, state.backdrop);
            Api::QueryBorderContext(L"Tooltip", darkMode, state.border);
            break;
        }
        case FlyoutType::DropDown: {
            Api::QueryBackdropEffectContext(L"DropDown", darkMode, state.backdrop);
            Api::QueryBorderContext(L"DropDown", darkMode, state.border);
            break;
        }
        default:
            break;
    }
}

void ApplyWindowEffects(HWND hWnd, WindowState& state) {
    if (!state.border.colorUseDefault && SystemHelper::IsWindows11()) {
        COLORREF color = Utils::MakeCOLORREF(state.border.color);
        if (state.border.colorUseNone) {
            color = state.border.color;
        }
        if (state.regionRadius > 0) {
            color = DWMWA_COLOR_NONE;
        }
        [[maybe_unused]] HRESULT hrSet = DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &color, sizeof(color));
    }
    Api::ApplyEffect(hWnd, state.darkMode, state.backdrop, state.border);
    state.effectsApplied = true;

    // Hide the system drop shadow window that follows flyouts (the "SysShadow"
    // class sibling), when the settings ask for no system shadow.
    if (state.noSystemDropShadow) {
        HWND backdropWindow = GetWindow(hWnd, GW_HWNDNEXT);
        if (Utils::IsWindowClass(backdropWindow, L"SysShadow")) {
            ShowWindow(backdropWindow, SW_HIDE);
        }
    }
}

// Reads one DWORD value from the engine hive. False when it is missing or not a DWORD.
// The engine writes its keys in the 64-bit view, so a 32-bit process must ask for it
// (RegGetValueW has no such flag).
bool ReadEngineDword(const wchar_t* subkey, const wchar_t* name, DWORD& value) {
    HKEY hKey{};
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, subkey, 0, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &hKey) !=
        ERROR_SUCCESS) {
        return false;
    }
    DWORD type = 0;
    DWORD size = sizeof(value);
    const bool ok = RegQueryValueExW(hKey, name, nullptr, &type, reinterpret_cast<BYTE*>(&value),
                                     &size) == ERROR_SUCCESS &&
                    type == REG_DWORD;
    RegCloseKey(hKey);
    return ok;
}

// The custom-corner-radius mod (Include dwm.exe) replaces the radius DWM gives a window
// before DWM draws the base layer: a value under 6 px becomes its small radius, anything
// else its radius, and -1 keeps DWM's value. Its settings live in the engine hive, so
// they are read there. Returns |dwmRadius| when the mod is not installed or is off.
int CustomCornerRadiusFor(int dwmRadius) {
    constexpr wchar_t kModKey[] = L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius";
    constexpr wchar_t kSettingsKey[] =
        L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius\\Settings";
    HKEY modKey{};
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, kModKey, 0, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &modKey) !=
        ERROR_SUCCESS) {
        return dwmRadius;
    }
    RegCloseKey(modKey);
    DWORD disabled = 0;
    if (ReadEngineDword(kModKey, L"Disabled", disabled) && disabled) {
        return dwmRadius;
    }
    // The mod's own defaults, for a setting that was never saved.
    DWORD radius = 12;
    DWORD smallRadius = 6;
    ReadEngineDword(kSettingsKey, L"radius", radius);
    ReadEngineDword(kSettingsKey, L"smallRadius", smallRadius);
    const int replaced = dwmRadius < 6 ? (int)smallRadius : (int)radius;
    return replaced < 0 ? dwmRadius : replaced;
}

// The window region clips the menu to one rounded rect, so the outline and the
// fill share one arc. The radius MUST track the DWM backdrop layer: DWM composites
// the menu's own base layer as a full-rect round rect whose radius is the window's
// corner radius (8 dp for DWMWCP_ROUND: 8 px at 100%, 16 px at 200%), and it
// ignores the window region. A larger region radius left the base layer's navy
// corners spilling outside the accent ring (the 0.6.58 corner-spill report, and the
// 0.6.71 fix for the old fixed 16 px that spilled the same way at 100%);
// matching the radii keeps the base layer's arc under the ring (RenderRingDib). The
// custom-corner-radius mod replaces DWM's 8 dp menu radius with its own (16 px in the
// owner's setup), so the region takes the radius the mod gives instead of assuming 8.
int MenuRegionRadius(HWND hWnd) {
    const UINT dpi = GetDpiForWindow(hWnd);
    return CustomCornerRadiusFor(MulDiv(8, dpi ? (int)dpi : 96, 96));
}

void ApplyMenuWindowRegion(HWND hWnd, WindowState& state) {
    const bool rounded =
        state.border.cornerType == DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUND ||
        state.border.cornerType == DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUNDSMALL;
    if (!rounded) {
        if (state.regionRadius) {
            SetWindowRgn(hWnd, nullptr, TRUE);
            state.regionWidth = state.regionHeight = state.regionRadius = 0;
        }
        return;
    }
    RECT rc{};
    if (!GetWindowRect(hWnd, &rc)) {
        return;
    }
    const int width = rc.right - rc.left;
    const int height = rc.bottom - rc.top;
    if (width <= 0 || height <= 0) {
        return;
    }
    const int radius = MenuRegionRadius(hWnd);
    if (state.regionRadius == radius && state.regionWidth == width &&
        state.regionHeight == height) {
        return;
    }
    HRGN region = CreateRoundRectRgn(0, 0, width, height, radius * 2, radius * 2);
    if (!region) {
        return;
    }
    // Record the size before SetWindowRgn: it repaints the window, and that
    // paint comes back through here.
    state.regionWidth = width;
    state.regionHeight = height;
    state.regionRadius = radius;
    if (!SetWindowRgn(hWnd, region, TRUE)) {
        DeleteObject(region);
        state.regionWidth = state.regionHeight = state.regionRadius = 0;
    }
}

// The flyout's first paint triggers the effect application, so the accent
// policy is in place before DWM composites the frame.
WindowState* EnsureWindowState(HWND hWnd, FlyoutType type, bool darkMode) {
    WindowState& state = GetOrCreateWindowState(hWnd);
    bool applyNow = false;
    if (state.type != type) {
        state.type = type;
        state.effectsApplied = false;
    }
    if (!state.effectsApplied) {
        RefreshWindowState(hWnd, state, darkMode);
        applyNow = true;
    }
    if (applyNow && !Api::IsPartDisabled(type == FlyoutType::Menu     ? L"Menu"
                                         : type == FlyoutType::Tooltip ? L"Tooltip"
                                                                       : L"DropDown")) {
        ApplyWindowEffects(hWnd, state);
        Log::Write(L"[fx] applied type=%d hwnd=%p dark=%d effect=%u", (int)type, hWnd,
                   (int)darkMode, state.backdrop.effectType);
    }
    if (type == FlyoutType::Menu || type == FlyoutType::DropDown ||
        type == FlyoutType::Tooltip) {
        ApplyMenuWindowRegion(hWnd, state);
#ifdef TF_DEBUG_LOG
        Log::Write(L"[win] type=%d hwnd=%p atom=%u corner=%d useDefault=%d useNone=%d region=%dx%d r=%d vis=%d",
                   (int)type, hWnd, (unsigned)GetClassLongPtrW(hWnd, GCW_ATOM),
                   (int)state.border.cornerType, (int)state.border.colorUseDefault,
                   (int)state.border.colorUseNone, state.regionWidth, state.regionHeight,
                   state.regionRadius, (int)IsWindowVisible(hWnd));
#endif
        // Menus lose DWMWA_BORDER_COLOR after the first effect pass, so set it on every
        // pass. A rounded menu's accent ring is the watcher overlay, so DWM draws no
        // border there at all: its own line follows a different arc than the region
        // and read as stray corner pieces on the Explorer title-bar sysmenu.
        if (SystemHelper::IsWindows11() && !state.border.colorUseDefault) {
            // Decided by the corner setting, not by the region: a menu painted before
            // it has a size has no region yet, and ApplyBorderEffect has just given
            // DWM the accent (the corner arcs in the 2026-10-21 screenshot). Menus
            // only: tooltips and dropdowns have no overlay, DWM's line is their ring.
            const bool overlayRing =
                type == FlyoutType::Menu &&
                (state.border.cornerType == DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUND ||
                 state.border.cornerType == DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUNDSMALL);
            // A rounded tooltip or dropdown keeps the colour ApplyBorderEffect gave
            // DWM (0.6.63 behaviour).
            const bool keepDwmAccent = !overlayRing && state.regionRadius > 0;
            COLORREF color{Utils::MakeCOLORREF(state.border.color)};
            if (state.border.colorUseNone || overlayRing) {
                color = DWMWA_COLOR_NONE;
            }
            if (!keepDwmAccent) {
                [[maybe_unused]] HRESULT hrSet =
                    DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &color, sizeof(color));
#ifdef TF_DEBUG_LOG
                COLORREF readBack = 0;
                HRESULT hrGet = DwmGetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &readBack, sizeof(readBack));
                Log::Write(L"[dwm] border hwnd=%p want=%08X set=%08X get=%08X getHr=%08X", hWnd,
                           (unsigned)color, (unsigned)hrSet, (unsigned)readBack, (unsigned)hrGet);
#endif
            }
        }
    }
    return &state;
}

// A buffered paint has no window DC, so ResolveFlyoutWindow can return the wrong
// menu (for a submenu, the main menu). Bring every other visible menu on this
// thread up to date as well, so each one gets its own effects and region.
struct MenuSweep {
    HWND except;
    bool darkMode;
};

BOOL CALLBACK EnsureOtherMenuProc(HWND hWnd, LPARAM lParam) {
    auto* sweep = reinterpret_cast<MenuSweep*>(lParam);
    if (hWnd != sweep->except && IsMenuWindow(hWnd)) {
        EnsureWindowState(hWnd, FlyoutType::Menu, sweep->darkMode);
    }
    return TRUE;
}

void EnsureOtherMenuWindows(HWND except, bool darkMode) {
    MenuSweep sweep{except, darkMode};
    EnumThreadWindows(GetCurrentThreadId(), EnsureOtherMenuProc, reinterpret_cast<LPARAM>(&sweep));
}

}  // namespace Handler

// ===========================================================================
// Rendering (port of TFMain/MenuRendering.cpp, GDI variant)
// ===========================================================================

namespace Rendering {

bool HandlePopupMenuNonClientBorderColors(HDC hdc, const RECT& paintRect) {
    Handler::WindowState* state = Handler::g_paintingState;
#ifdef TF_DEBUG_LOG
    Log::Write(L"[nc] state=%p regionR=%d regionW=%d regionH=%d useNone=%d useDefault=%d corner=%d rect=%ld,%ld,%ld,%ld",
               (void*)state, state ? state->regionRadius : -1, state ? state->regionWidth : -1,
               state ? state->regionHeight : -1, state ? (int)state->border.colorUseNone : -1,
               state ? (int)state->border.colorUseDefault : -1, state ? (int)state->border.cornerType : -1,
               paintRect.left, paintRect.top, paintRect.right, paintRect.bottom);
#endif
    if (!state) {
        return false;
    }
    // This pass draws directly on the menu's DC. A rounded menu gets no ring here:
    // its ring is the watcher overlay, the one painter every rounded menu shares.
    // A DC ring is erased by the menu's own item and background blits (the Explorer
    // title-bar sysmenu kept only its corner arcs, 2026-10-21) and raced the overlay
    // whenever both ran (the 0.6.59 sysmenu double border). This pass only clears
    // the rim so the backdrop shows under the overlay's band.
    //
    // A square menu has no overlay (its ring would be rounded), so it keeps the DC
    // frame, and dcBorderPainted tells the watcher to stay away from it.
    const bool rounded =
        state->border.cornerType == DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUND ||
        state->border.cornerType == DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUNDSMALL;
    auto frame = [&](HBRUSH brush) {
        if (!rounded && FrameRect(hdc, &paintRect, brush)) {
            state->dcBorderPainted = true;
        }
    };

    DcStateGuard dcState(hdc);
    SelectClipRgn(hdc, nullptr);
    // No background band paints the rim between the window edge and the band's inset, so it
    // keeps the window's grey background. Clear the rim to alpha 0 so the backdrop shows —
    // the rim only: this pass draws after the items, and the full-rect clear this used to
    // do erased every item text glyph (the 0.6.48/0.6.49 regression). The band starts at
    // inset 2, one pixel inside the [1,2) ring band.
    RECT band{paintRect.left + 2, paintRect.top + 2, paintRect.right - 2, paintRect.bottom - 2};
    if (state->bandRectValid) {
        band = state->bandRect;
    }
    unique_handle<HRGN> rim{CreateRectRgn(paintRect.left, paintRect.top, paintRect.right,
                                          paintRect.bottom)};
    if (rim) {
        unique_handle<HRGN> inner{nullptr};
        if (rounded && state->regionRadius > 2) {
            // GDI round-rect regions cover to right-2/bottom-2, not right-1: the
            // rim must still protect the fill columns through the ring inset, so
            // the round-rect band params widen by 2 (rect regions have no such
            // exclusion and keep the plain band rect).
            inner.reset(CreateRoundRectRgn(band.left, band.top, band.right + 2,
                                           band.bottom + 2,
                                           (state->regionRadius - 2) * 2,
                                           (state->regionRadius - 2) * 2));
        } else {
            inner.reset(CreateRectRgn(band.left, band.top, band.right, band.bottom));
        }
        if (!inner || CombineRgn(rim.get(), rim.get(), inner.get(), RGN_DIFF) == ERROR) {
            rim.reset();
        }
    }
    if (rim) {
        SelectClipRgn(hdc, rim.get());
    }
#ifdef TF_DEBUG_LOG
    int nzBefore = 0;
    for (int x = 35; x < 200; ++x) {
        if (GetPixel(hdc, x, 10) != 0) {
            ++nzBefore;
        }
    }
#endif
    if (rim) {
        PatBlt(hdc, paintRect.left, paintRect.top, paintRect.right - paintRect.left,
               paintRect.bottom - paintRect.top, BLACKNESS);
        SelectClipRgn(hdc, nullptr);
    }
#ifdef TF_DEBUG_LOG
    int nzAfter = 0;
    for (int x = 35; x < 200; ++x) {
        if (GetPixel(hdc, x, 10) != 0) {
            ++nzAfter;
        }
    }
    Log::Write(L"[nc] probe row10 nzBefore=%d nzAfter=%d rim=%d band=%ld,%ld,%ld,%ld", nzBefore,
               nzAfter, rim.get() ? 1 : 0, band.left, band.top, band.right, band.bottom);
#endif
    if (!state->border.colorUseNone) {
        if (state->border.colorUseDefault) {
            // The native POPUPBORDERS drawing takes over below; it owns this
            // menu's border, so the watcher keeps its overlay away all the same.
            state->dcBorderPainted = true;
            return false;
        }
        unique_handle<HBRUSH> brush{Utils::CreateSolidColorBrushWithAlpha(
            Utils::MakeCOLORREF(state->border.color),
            Utils::GetAlphaFromARGB(state->border.color))};
        if (brush) {
            frame(brush.get());
        }
    } else {
        frame(GetStockBrush(BLACK_BRUSH));
    }
    return true;
}

// Menus painted without a themed background (the desktop context menu is drawn by
// DirectUI) get their ring from the overlay window (see the UnthemedMenuWatcher
// section below). Nothing paints on such a menu's own DC any more: every DC stroke
// was another painter racing the overlay — the GDI region arc and the GDI+ arc
// differ at the corners, which read as a duplicate border (0.6.55 field report).

// Menu items paint in client coordinates, which start at the window frame's inner
// edge (3 px in on Windows 11), while the region and ring are window coordinates.
// Region math done in client space without this offset clipped away the client's
// top rows (left uncleared, so the theme's lighter fill showed through) and kept
// the hover fill short of the ring on the left.
POINT ClientOffset(const Handler::WindowState& state) {
    RECT window{};
    POINT client{};
    if (!state.hWnd || !GetWindowRect(state.hWnd, &window) || !ClientToScreen(state.hWnd, &client)) {
        return {};
    }
    return {client.x - window.left, client.y - window.top};
}

// Clips the DC to the menu's fill area: inset 2, concentric with the region arc.
void ClipToMenuInterior(HDC hdc, const Handler::WindowState& state) {
    if (state.regionRadius <= 0 || state.border.colorUseDefault) {
        return;
    }
    const int diameter = (state.regionRadius - 2) * 2;
    // GDI round-rect regions cover to right-2/bottom-2; the clear must reach
    // the column/row next to the ring (inset 3), so the params widen by 1.
    unique_handle<HRGN> inner{CreateRoundRectRgn(2, 2, state.regionWidth - 1,
                                                 state.regionHeight - 1, diameter, diameter)};
    if (inner) {
        // Clip regions are in device units. A window DC's device space is the client
        // area; a buffered-paint DC maps client coordinates onto a window-sized
        // bitmap through its viewport origin, so take the logical-to-device shift too.
        const POINT offset = ClientOffset(state);
        POINT device{};
        LPtoDP(hdc, &device, 1);
        OffsetRgn(inner.get(), device.x - offset.x, device.y - offset.y);
        ExtSelectClipRgn(hdc, inner.get(), RGN_AND);
    }
}

// The area an item's hot fill covers, and so the area its normal paint clears:
// the item rect pushed out to the inside of the ring wherever only menu padding
// lies between them. A fill limited to the item rect left square corners inside
// the rounded ring, gaps at the sides, and a padding row it never reached; on a
// one-item menu (a pill) that read as a box floating inside the outline.
RECT ItemFillRect(const Handler::WindowState& state, const RECT& item) {
    RECT rc = item;
    if (state.regionRadius <= 0 || state.regionWidth <= 0 || state.regionHeight <= 0) {
        return rc;
    }
    constexpr int kInset = 2;
    constexpr int kMaxPadding = 8;
    const POINT offset = ClientOffset(state);
    const int left = kInset - offset.x;
    const int top = kInset - offset.y;
    const int right = state.regionWidth - kInset - offset.x;
    const int bottom = state.regionHeight - kInset - offset.y;
    if (rc.left - left <= kMaxPadding) {
        rc.left = left;
    }
    if (right - rc.right <= kMaxPadding) {
        rc.right = right;
    }
    if (rc.top - top <= kMaxPadding) {
        rc.top = top;
    }
    if (bottom - rc.bottom <= kMaxPadding) {
        rc.bottom = bottom;
    }
    return rc;
}

bool HandleCustomRendering(HDC hdc, int partId, int stateId, const RECT& clipRect,
                           const RECT& itemRect) {
    Handler::WindowState* state = Handler::g_paintingState;
    if (!state) {
        return false;
    }
    const Api::MenuCustomRenderingContext& custom = state->customRendering;
    const bool itemFill = partId == MENU_POPUPITEM || partId == MENU_POPUPITEMFOCUSABLE;
    const RECT paintRect = itemFill ? ItemFillRect(*state, itemRect) : itemRect;
#ifdef TF_DEBUG_LOG
    {
        RECT box{};
        int kind = GetClipBox(hdc, &box);
        POINT org{};
        GetDCOrgEx(hdc, &org);
        RECT dcWin{};
        HWND dcWnd = WindowFromDC(hdc);
        if (dcWnd) GetWindowRect(dcWnd, &dcWin);
        Log::Write(L"[item] part=%d state=%d item=%ld,%ld,%ld,%ld fill=%ld,%ld,%ld,%ld clip=%ld,%ld,%ld,%ld "
                   L"clipbox=%d:%ld,%ld,%ld,%ld org=%ld,%ld dcWnd=%p menu=%p region=%dx%d r=%d",
                   partId, stateId, itemRect.left, itemRect.top, itemRect.right, itemRect.bottom,
                   paintRect.left, paintRect.top, paintRect.right, paintRect.bottom, clipRect.left,
                   clipRect.top, clipRect.right, clipRect.bottom, kind, box.left, box.top, box.right,
                   box.bottom, org.x, org.y, (void*)dcWnd, (void*)state->hWnd, state->regionWidth,
                   state->regionHeight, state->regionRadius);
    }
#endif

    DcStateGuard dcState(hdc);
    if (itemFill) {
        IntersectClipRect(hdc, paintRect.left, paintRect.top, paintRect.right, paintRect.bottom);
        ClipToMenuInterior(hdc, *state);
    } else {
        IntersectClipRect(hdc, clipRect.left, clipRect.top, clipRect.right, clipRect.bottom);
    }
    // The keyboard focus cue is drawn over the hot fill, so it must not clear it.
    if (partId != MENU_POPUPITEMKBFOCUS) {
        PatBlt(hdc, paintRect.left, paintRect.top, paintRect.right - paintRect.left,
               paintRect.bottom - paintRect.top, BLACKNESS);
    }

    auto drawRoundedFill = [&](DWORD color, DWORD radius, bool stroke, DWORD width) {
        RECT rc = paintRect;
        int w = rc.right - rc.left;
        int h = rc.bottom - rc.top;
        if (w <= 0 || h <= 0) {
            return false;
        }
        unique_handle<HBRUSH> brush{Utils::CreateSolidColorBrushWithAlpha(
            Utils::MakeCOLORREF(color), Utils::GetAlphaFromARGB(color))};
        if (!brush) {
            return false;
        }
        if (stroke) {
            // Outline only, like upstream; width is in thousandths of a pixel.
            int thickness = std::max(1, (int)(width / 1000));
            unique_handle<HRGN> region{CreateRoundRectRgn(rc.left, rc.top, rc.right + 1,
                                                          rc.bottom + 1, (int)radius * 2,
                                                          (int)radius * 2)};
            if (!region) {
                return false;
            }
            FrameRgn(hdc, region.get(), brush.get(), thickness, thickness);
            return true;
        }
        // A region fill covers the whole rect; RoundRect with a null pen stops one
        // pixel short on the right and bottom.
        unique_handle<HRGN> region{radius ? CreateRoundRectRgn(rc.left, rc.top, rc.right + 1,
                                                               rc.bottom + 1, (int)radius * 2,
                                                               (int)radius * 2)
                                          : CreateRectRgnIndirect(&rc)};
        return region && FillRgn(hdc, region.get(), brush.get());
    };

    if (partId == MENU_POPUPSEPARATOR) {
        if (custom.separator_disabled) {
            return false;
        }
        int height = paintRect.bottom - paintRect.top;
        int thickness = std::max(1, (int)(custom.separator_width / 1000));
        RECT line{paintRect.left, paintRect.top + height / 2, paintRect.right,
                  paintRect.top + height / 2 + thickness};
        unique_handle<HBRUSH> brush{Utils::CreateSolidColorBrushWithAlpha(
            Utils::MakeCOLORREF(custom.separator_color),
            Utils::GetAlphaFromARGB(custom.separator_color))};
        if (!brush) {
            return false;
        }
        FillRect(hdc, &line, brush.get());
        return true;
    }

    if (partId == MENU_POPUPITEMKBFOCUS) {
        if (custom.focusing_disabled) {
            return false;
        }
        return drawRoundedFill(custom.focusing_color, custom.focusing_cornerRadius, true,
                               custom.focusing_width);
    }

    if (partId == MENU_POPUPITEM || partId == MENU_POPUPITEMFOCUSABLE) {
        if (stateId == MPI_DISABLEDHOT) {
            if (custom.disabledHot_disabled) {
                return false;
            }
            return drawRoundedFill(custom.disabledHot_color, custom.disabledHot_cornerRadius, false,
                                   0);
        }
        if (stateId == MPI_HOT) {
            if (custom.hot_disabled) {
                return false;
            }
            return drawRoundedFill(custom.hot_color, custom.hot_cornerRadius, false, 0);
        }
    }

    return false;
}

// Port of MenuRendering::HandleDrawThemeBackground: decides what to draw for
// "Menu"-themed parts. Returns true when the call was handled.
bool HandleMenuDrawThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId,
                                   LPCRECT pRect, LPCRECT pClipRect,
                                   decltype(&DrawThemeBackground) actualDrawThemeBackground) {
    Handler::WindowState* state = Handler::g_paintingState;
    if (!state || IsRectEmpty(pRect)) {
        return false;
    }

    RECT clipRect{*pRect};
    if (pClipRect) {
        IntersectRect(&clipRect, &clipRect, pClipRect);
    }

    if (iPartId == MENU_POPUPSEPARATOR || iPartId == MENU_POPUPITEMKBFOCUS) {
        if (state->customRendering.enable &&
            HandleCustomRendering(hdc, iPartId, iStateId, clipRect, *pRect)) {
            return true;
        }
        return false;
    }

    if (iPartId == MENU_POPUPITEM || iPartId == MENU_POPUPITEMFOCUSABLE) {
        if (iStateId == MPI_DISABLEDHOT && state->customRendering.enable &&
            HandleCustomRendering(hdc, iPartId, iStateId, clipRect, *pRect)) {
            return true;
        }
        if (iStateId == MPI_HOT) {
            if (state->customRendering.enable &&
                HandleCustomRendering(hdc, iPartId, iStateId, clipRect, *pRect)) {
                return true;
            }
            if (actualDrawThemeBackground) {
                actualDrawThemeBackground(hTheme, hdc, iPartId, iStateId, pRect, pClipRect);
            }
            return true;
        }
    }

    if (iPartId != MENU_POPUPBACKGROUND && iPartId != MENU_POPUPBORDERS &&
        iPartId != MENU_POPUPGUTTER && iPartId != MENU_POPUPITEM &&
        iPartId != MENU_POPUPITEMFOCUSABLE) {
        return false;
    }

    // Record the interior rect the background bands paint, so the border pass can
    // clear the rim without touching anything the bands or items drew.
    if (iPartId == MENU_POPUPBACKGROUND && !state->bandRectValid && state->regionWidth > 0 &&
        state->regionHeight > 0 && clipRect.left <= 2 && clipRect.top <= 2 &&
        clipRect.right >= state->regionWidth - 2 &&
        clipRect.bottom >= state->regionHeight - 2) {
        state->bandRect = clipRect;
        state->bandRectValid = true;
    }

    // The backdrop owns the fill: bands paint black (alpha 0) so the acrylic shows
    // through. A rounded menu's fill stops inside the overlay's 1 px band (pixel 1), so
    // the edge it leaves stays the rim the border pass clears. The fill area must stay
    // concentric with the region arc: inset 2, radius r-2.
    DcStateGuard fillGuard(hdc);
    ClipToMenuInterior(hdc, *state);
    // A normal item clears everything its hot fill covered, or the padding strips
    // of the last hover stay behind as lighter bands.
    RECT clear = clipRect;
    if (iPartId == MENU_POPUPITEM || iPartId == MENU_POPUPITEMFOCUSABLE) {
        clear = ItemFillRect(*state, *pRect);
    }
#ifdef TF_DEBUG_LOG
    {
        RECT box{};
        int kind = GetClipBox(hdc, &box);
        Log::Write(L"[clear] part=%d state=%d rect=%ld,%ld,%ld,%ld clear=%ld,%ld,%ld,%ld clipbox=%d:%ld,%ld,%ld,%ld region=%dx%d",
                   iPartId, iStateId, pRect->left, pRect->top, pRect->right, pRect->bottom, clear.left,
                   clear.top, clear.right, clear.bottom, kind, box.left, box.top, box.right, box.bottom,
                   state->regionWidth, state->regionHeight);
    }
#endif
    PatBlt(hdc, clear.left, clear.top, clear.right - clear.left, clear.bottom - clear.top,
           BLACKNESS);
    return true;
}

bool HandleMenuBitmap(HBITMAP& source, unique_handle<HBITMAP>& target) {
    Handler::WindowState* state = Handler::g_paintingState;
    if (source && !Utils::IsOemBitmap(source)) {
        target.reset(Utils::Promise32BPP(source));
        if (!target) {
            return false;
        }
        if (state && state->iconRemoval.enable) {
            Utils::BitmapRemoveColor(target.get(), state->iconRemoval.colorTreatAsTransparent,
                                     state->iconRemoval.colorTreatAsTransparentThreshold);
        }
        source = target.get();
        return true;
    }
    return false;
}

}  // namespace Rendering

// ===========================================================================
// uxtheme / user32 hooks
// ===========================================================================

namespace Hooks {

// The watcher globals are defined below the paint hooks; these declarations let
// the border paint reach them without reordering the file.
extern DWORD g_unthemedMenuThreadId;
constexpr UINT kWatcherOverlayMessage = WM_APP + 0x0F00;

thread_local Handler::FlyoutType g_paintingType = Handler::FlyoutType::Unknown;

using DrawThemeBackgroundFn = decltype(&DrawThemeBackground);
using DrawThemeBackgroundExFn = decltype(&DrawThemeBackgroundEx);
using DrawThemeTextFn = decltype(&DrawThemeText);
using DrawThemeTextExFn = decltype(&DrawThemeTextEx);
using GetThemeMarginsFn = decltype(&GetThemeMargins);
using DrawTextWFn = decltype(&DrawTextW);

DrawThemeBackgroundFn g_drawThemeBackgroundOrig = nullptr;
DrawThemeBackgroundExFn g_drawThemeBackgroundExOrig = nullptr;
DrawThemeTextFn g_drawThemeTextOrig = nullptr;
DrawThemeTextExFn g_drawThemeTextExOrig = nullptr;
GetThemeMarginsFn g_getThemeMarginsOrig = nullptr;
DrawTextWFn g_drawTextWOrig = nullptr;

void* g_hookTargets[12]{};
int g_hookTargetCount = 0;

// Sets the per-thread paint context for the current call.
Handler::WindowState* BeginPaint(HTHEME hTheme, HDC hdc, Handler::FlyoutType& typeOut) {
    typeOut = Handler::FlyoutType::Unknown;
    wchar_t themeClass[MAX_PATH + 1]{};
    if (FAILED(ThemeHelper::GetThemeClass(hTheme, themeClass, MAX_PATH))) {
        return nullptr;
    }
    Handler::FlyoutType type = Handler::TypeForThemeClass(themeClass);
    if (type == Handler::FlyoutType::Unknown) {
        return nullptr;
    }
    const wchar_t* part = type == Handler::FlyoutType::Menu     ? L"Menu"
                          : type == Handler::FlyoutType::Tooltip ? L"Tooltip"
                                                                 : L"DropDown";
    if (Api::IsPartDisabled(part)) {
        return nullptr;
    }

    bool exactMenu = false;
    HWND hWnd = type == Handler::FlyoutType::Menu ? Handler::ResolveMenuWindow(hdc, exactMenu)
                                                  : Handler::ResolveFlyoutWindow(hdc, type);
#ifdef TF_DEBUG_LOG
    if (type == Handler::FlyoutType::Menu) {
        Log::Write(L"[bp] menu resolved=%p exact=%d dcWnd=%p dcObj=%lu", (void*)hWnd, (int)exactMenu,
                   (void*)WindowFromDC(hdc), (unsigned long)GetObjectType(hdc));
    }
#endif
    if (!hWnd) {
        return nullptr;
    }

    bool darkMode = false;
    if (type == Handler::FlyoutType::Menu) {
        darkMode = Handler::MenuShouldUseDarkMode(hTheme);
    } else if (type == Handler::FlyoutType::Tooltip) {
        HWND owner = reinterpret_cast<HWND>(GetWindowLongPtrW(hWnd, GWLP_HWNDPARENT));
        darkMode = Handler::TooltipShouldUseDarkMode(hWnd, owner);
    } else {
        darkMode = ThemeHelper::ShouldAppsUseDarkMode() && ThemeHelper::IsDarkModeAllowedForApp();
    }

    typeOut = type;
    if (type == Handler::FlyoutType::Menu && !exactMenu) {
        Handler::EnsureOtherMenuWindows(hWnd, darkMode);
    }
    return Handler::EnsureWindowState(hWnd, type, darkMode);
}

HRESULT WINAPI DrawThemeBackgroundHook(HTHEME hTheme, HDC hdc, int iPartId, int iStateId,
                                       LPCRECT pRect, LPCRECT pClipRect) {
    Handler::FlyoutType type{};
    Handler::WindowState* state = BeginPaint(hTheme, hdc, type);
#ifdef TF_DEBUG_LOG
    {
        static int diagCount = 0;
        wchar_t diagClass[MAX_PATH + 1]{};
        if (diagCount < 20000 && SUCCEEDED(ThemeHelper::GetThemeClass(hTheme, diagClass, MAX_PATH))) {
            diagCount++;
            Log::Write(L"[dtb] class=%ls part=%d state=%d type=%d st=%p dcWnd=%p dcObj=%lu rect=%ld,%ld,%ld,%ld",
                       diagClass, iPartId, iStateId, (int)type, (void*)state, (void*)WindowFromDC(hdc),
                       (unsigned long)GetObjectType(hdc),
                       pRect ? pRect->left : -1L, pRect ? pRect->top : -1L,
                       pRect ? pRect->right : -1L, pRect ? pRect->bottom : -1L);
        }
    }
#endif
    if (!state) {
        return g_drawThemeBackgroundOrig(hTheme, hdc, iPartId, iStateId, pRect, pClipRect);
    }

    auto previous = std::exchange(Handler::g_paintingState, state);
    g_paintingType = type;
    struct Restore {
        Handler::WindowState* previous;
        ~Restore() { Handler::g_paintingState = previous; }
    } restore{previous};

    if (type == Handler::FlyoutType::Menu) {
        if (iPartId == MENU_POPUPBORDERS) {
            RECT clipRect{*pRect};
            if (pClipRect) {
                IntersectRect(&clipRect, &clipRect, pClipRect);
            }
            // No fill here: the dark fill belongs to the POPUPBACKGROUND bands. A square
            // menu's outline is the DC frame from HandlePopupMenuNonClientBorderColors;
            // a rounded menu's is the watcher overlay.
#ifdef TF_DEBUG_LOG
            Log::Write(L"[border] clip=%d,%d,%d,%d color=%08X useDefault=%d useNone=%d",
                       clipRect.left, clipRect.top, clipRect.right, clipRect.bottom,
                       (unsigned)state->border.color, (int)state->border.colorUseDefault,
                       (int)state->border.colorUseNone);
#endif
            const bool painted = Rendering::HandlePopupMenuNonClientBorderColors(hdc, clipRect);
            if (!painted) {
                DcStateGuard dcState(hdc);
                ExcludeClipRect(hdc, clipRect.left + 1, clipRect.top + 1, clipRect.right - 1,
                                clipRect.bottom - 1);
                g_drawThemeBackgroundOrig(hTheme, hdc, iPartId, iStateId, pRect, pClipRect);
            } else if (state->hWnd) {
                // The watcher thread owns the overlay windows, so ask it directly
                // instead of waiting up to 250 ms for its tick: drop the overlay of
                // a menu the DC framed (lParam 0), or ring a rounded one now
                // (lParam 1) so it opens with its border.
                PostThreadMessageW(g_unthemedMenuThreadId, kWatcherOverlayMessage,
                                   (WPARAM)state->hWnd, state->dcBorderPainted ? 0 : 1);
            }
            return S_OK;
        }
        if (Rendering::HandleMenuDrawThemeBackground(hTheme, hdc, iPartId, iStateId, pRect, pClipRect,
                                                     g_drawThemeBackgroundOrig)) {
            return S_OK;
        }
    } else if (type == Handler::FlyoutType::Tooltip) {
        if (iPartId == TTP_STANDARD && !IsRectEmpty(pRect)) {
            RECT paintRect{*pRect};
            if (pClipRect) {
                IntersectRect(&paintRect, &paintRect, pClipRect);
            }
            PatBlt(hdc, paintRect.left, paintRect.top, paintRect.right - paintRect.left,
                   paintRect.bottom - paintRect.top, BLACKNESS);
            return S_OK;
        }
    } else if (type == Handler::FlyoutType::DropDown) {
        if (IsRectEmpty(pRect)) {
            return g_drawThemeBackgroundOrig(hTheme, hdc, iPartId, iStateId, pRect, pClipRect);
        }
        RECT clipRect{*pRect};
        if (pClipRect) {
            IntersectRect(&clipRect, &clipRect, pClipRect);
        }
        // Gut the list background; item paintings go through unchanged.
        if (iPartId != LVP_LISTITEM && iPartId != LVP_LISTGROUP && iPartId != LVP_LISTDETAIL) {
            PatBlt(hdc, clipRect.left, clipRect.top, clipRect.right - clipRect.left,
                   clipRect.bottom - clipRect.top, BLACKNESS);
            return S_OK;
        }
    }

    return g_drawThemeBackgroundOrig(hTheme, hdc, iPartId, iStateId, pRect, pClipRect);
}

HRESULT WINAPI DrawThemeBackgroundExHook(HTHEME hTheme, HDC hdc, int iPartId, int iStateId,
                                         LPCRECT pRect, const DTBGOPTS* pOptions) {
    LPCRECT pClipRect = pOptions ? &pOptions->rcClip : nullptr;
    return DrawThemeBackgroundHook(hTheme, hdc, iPartId, iStateId, pRect, pClipRect);
}

HRESULT WINAPI DrawThemeTextHook(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCWSTR pszText,
                                 int cchText, DWORD dwTextFlags, DWORD dwTextFlags2, LPCRECT pRect) {
    Handler::FlyoutType type{};
    Handler::WindowState* state = BeginPaint(hTheme, hdc, type);
    if (!state) {
        return g_drawThemeTextOrig(hTheme, hdc, iPartId, iStateId, pszText, cchText, dwTextFlags,
                                   dwTextFlags2, pRect);
    }
    if (type == Handler::FlyoutType::Tooltip && !IsRectEmpty(pRect)) {
        DTTOPTS options{sizeof(DTTOPTS), DTT_TEXTCOLOR | DTT_COMPOSITED};
        const auto& tip = Cfg::Get().tooltipExtras;
        options.crText = Utils::MakeCOLORREF(state->darkMode ? tip.darkModeColor : tip.lightModeColor);
        return g_drawThemeTextExOrig(hTheme, hdc, iPartId, iStateId, pszText, cchText,
                                    dwTextFlags, const_cast<LPRECT>(pRect), &options);
    }
    if (type != Handler::FlyoutType::Menu || IsRectEmpty(pRect)) {
        return g_drawThemeTextOrig(hTheme, hdc, iPartId, iStateId, pszText, cchText, dwTextFlags,
                                   dwTextFlags2, pRect);
    }

    // Composite the text with alpha so it renders correctly over the translucent
    // background (upstream MyDrawThemeText).
#ifdef TF_DEBUG_LOG
    Log::Write(L"[txt] enter hdc=%p part=%d state=%d cch=%d rect=%ld,%ld,%ld,%ld", (void*)hdc,
               iPartId, iStateId, cchText, pRect->left, pRect->top, pRect->right, pRect->bottom);
#endif
    auto previous = std::exchange(Handler::g_paintingState, state);
    struct Restore {
        Handler::WindowState* previous;
        ~Restore() { Handler::g_paintingState = previous; }
    } restore{previous};

    struct TextParams {
        HTHEME hTheme;
        int iPartId;
        int iStateId;
        LPCWSTR pszText;
        int cchText;
        DWORD dwTextFlags;
        LPRECT pRect;
    } params{hTheme, iPartId, iStateId, pszText, cchText, dwTextFlags, const_cast<LPRECT>(pRect)};

    HRESULT hr = ThemeHelper::DrawThemeContent(
        hdc, *pRect, nullptr, nullptr, 0,
        [](HDC memoryDC, HPAINTBUFFER, RGBQUAD*, int, LPARAM lParam) {
            auto* p = reinterpret_cast<TextParams*>(lParam);
            DTTOPTS options{sizeof(DTTOPTS), DTT_COMPOSITED};
            DrawThemeTextEx(p->hTheme, memoryDC, p->iPartId, p->iStateId, p->pszText, p->cchText,
                            p->dwTextFlags, p->pRect, &options);
        },
        reinterpret_cast<LPARAM>(&params));
#ifdef TF_DEBUG_LOG
    Log::Write(L"[txt] menu part=%d state=%d content hr=0x%08X", iPartId, iStateId,
               (unsigned)hr);
#endif
    if (FAILED(hr)) {
        return g_drawThemeTextOrig(hTheme, hdc, iPartId, iStateId, pszText, cchText, dwTextFlags,
                                   dwTextFlags2, pRect);
    }
    return S_OK;
}

HRESULT WINAPI DrawThemeTextExHook(HTHEME hTheme, HDC hdc, int iPartId, int iStateId,
                                   LPCWSTR pszText, int cchText, DWORD dwTextFlags, LPRECT pRect,
                                   const DTTOPTS* pOptions) {
    Handler::FlyoutType type{};
    Handler::WindowState* state = BeginPaint(hTheme, hdc, type);
    if (!state) {
        return g_drawThemeTextExOrig(hTheme, hdc, iPartId, iStateId, pszText, cchText, dwTextFlags,
                                     pRect, pOptions);
    }
    if (type == Handler::FlyoutType::Tooltip) {
        auto previous = std::exchange(Handler::g_paintingState, state);
        struct Restore {
            Handler::WindowState* previous;
            ~Restore() { Handler::g_paintingState = previous; }
        } restore{previous};
        Cfg::TooltipExtras& tip = Cfg::Get().tooltipExtras;
        DTTOPTS options = pOptions ? *pOptions : DTTOPTS{};
        options.dwSize = sizeof(options);
        options.dwFlags |= DTT_TEXTCOLOR;
        options.crText = Utils::MakeCOLORREF(state->darkMode ? tip.darkModeColor : tip.lightModeColor);
        return g_drawThemeTextExOrig(hTheme, hdc, iPartId, iStateId, pszText, cchText, dwTextFlags,
                                     pRect, &options);
    }
    return g_drawThemeTextExOrig(hTheme, hdc, iPartId, iStateId, pszText, cchText, dwTextFlags,
                                 pRect, pOptions);
}

HRESULT WINAPI GetThemeMarginsHook(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId,
                                   RECT* prc, MARGINS* pMargins) {
    if (pMargins) {
        wchar_t themeClass[MAX_PATH + 1]{};
        if (SUCCEEDED(ThemeHelper::GetThemeClass(hTheme, themeClass, MAX_PATH)) &&
            !_wcsicmp(themeClass, L"Tooltip")) {
            Cfg::TooltipExtras& tip = Cfg::Get().tooltipExtras;
            if (tip.marginsType == 1) {
                *pMargins = tip.margins;
                return S_OK;
            }
        }
    }
    return g_getThemeMarginsOrig(hTheme, hdc, iPartId, iStateId, iPropId, prc, pMargins);
}

namespace {
struct TooltipDrawTextParams {
    LPCWSTR text;
    int cch;
    LPRECT rect;
    UINT format;
    int result;
    COLORREF color;
};

void TooltipDrawTextCallback(HDC memoryDC, HPAINTBUFFER, RGBQUAD*, int, LPARAM lParam) {
    auto* p = reinterpret_cast<TooltipDrawTextParams*>(lParam);
    SetTextColor(memoryDC, p->color);
    SetBkMode(memoryDC, TRANSPARENT);
    p->result = g_drawTextWOrig(memoryDC, p->text, p->cch, p->rect, p->format);
}
}  // namespace

int WINAPI DrawTextWHook(HDC hdc, LPCWSTR lpchText, int cchText, LPRECT lprc, UINT format) {
    // Tooltip text with alpha (upstream TooltipHooks::MyDrawTextW).
    HWND hWnd = WindowFromDC(hdc);
    // Common controls paint tooltip text into a buffered DC with no HWND.
    if (!hWnd && GetObjectType(hdc) == OBJ_MEMDC) {
        HWND tip = Handler::FindFlyoutWindowOnCurrentThread(Handler::FlyoutType::Tooltip);
        if (tip && IsWindowVisible(tip)) {
            hWnd = tip;
        }
    }
    if (hWnd && Handler::IsTooltipWindow(hWnd) &&
        !(format & (DT_CALCRECT | DT_INTERNAL))) {
        Handler::WindowState& state = Handler::GetOrCreateWindowState(hWnd);
        if (state.type == Handler::FlyoutType::Tooltip ||
            state.type == Handler::FlyoutType::Unknown) {
            Cfg::TooltipExtras& tip = Cfg::Get().tooltipExtras;
            COLORREF color =
                Utils::MakeCOLORREF(state.darkMode ? tip.darkModeColor : tip.lightModeColor);
            COLORREF oldColor = SetTextColor(hdc, color);
            TooltipDrawTextParams params{lpchText, cchText, lprc, format, 0, color};
            HRESULT hr = ThemeHelper::DrawThemeContent(
                hdc, *lprc, nullptr, nullptr, 0, TooltipDrawTextCallback,
                reinterpret_cast<LPARAM>(&params));
            SetTextColor(hdc, oldColor);
            if (SUCCEEDED(hr)) {
                return params.result;
            }
        }
    }
    return g_drawTextWOrig(hdc, lpchText, cchText, lprc, format);
}

// ---------------------------------------------------- unthemed menus ---
// Some menus are painted without any uxtheme call (the desktop context menu is
// drawn by DirectUI), so the draw hooks never fire for them. Anything drawn on
// such a menu's own DC is erased by its per-item buffered blits (diag24/25), and
// anything clipped by a window region is cut into dashes by GDI's polygonal arcs
// (0.6.54). The accent ring therefore lives on its own layered window floating
// exactly over the menu: the menu's paints cannot reach it, no region of the menu
// applies to it, and the band is anti-aliased by GDI+ instead of aliased by GDI
// regions. Themed rounded menus get the same overlay (0.6.64): their DC ring met
// the same blits. Only square menus, framed on their DC, are skipped.

std::mutex g_unthemedMenusLock;
std::unordered_map<HWND, SIZE> g_unthemedMenus;
DWORD g_unthemedMenuThreadId = 0;

struct RingOverlay {
    HWND window{};
    SIZE rendered{};
    DWORD renderedColor{};
};
std::mutex g_ringOverlaysLock;
std::unordered_map<HWND, RingOverlay> g_ringOverlays;  // menu hwnd -> overlay

// A window class outlives the DLL that registered it. Builds up to 0.6.63 never
// unregistered "TF_RingOverlay", so after a hot update that class still points at
// the unloaded DLL's window procedure; a fresh name keeps this build off it, and
// Wh_ModBeforeUninit now unregisters this one.
const wchar_t kRingOverlayClass[] = L"TF_RingOverlay_0664";
HANDLE g_unthemedMenuThread = nullptr;
ULONG_PTR g_gdiplusToken = 0;
bool g_gdiplusReady = false;

// gdiplus is loaded dynamically: Windhawk's fixed link set has no gdiplus.lib, and
// the flat API is a handful of C functions.
using PFN_GdiplusStartup = Gdiplus::Status(WINAPI*)(ULONG_PTR*, Gdiplus::GdiplusStartupInput*, void*);
using PFN_GdipCreateBitmapFromScan0 = decltype(&Gdiplus::DllExports::GdipCreateBitmapFromScan0);
using PFN_GdipGetImageGraphicsContext = decltype(&Gdiplus::DllExports::GdipGetImageGraphicsContext);
using PFN_GdipSetSmoothingMode = decltype(&Gdiplus::DllExports::GdipSetSmoothingMode);
using PFN_GdipCreatePath = decltype(&Gdiplus::DllExports::GdipCreatePath);
using PFN_GdipStartPathFigure = decltype(&Gdiplus::DllExports::GdipStartPathFigure);
using PFN_GdipAddPathArc = decltype(&Gdiplus::DllExports::GdipAddPathArc);
using PFN_GdipClosePathFigure = decltype(&Gdiplus::DllExports::GdipClosePathFigure);
using PFN_GdipCreateSolidFill = decltype(&Gdiplus::DllExports::GdipCreateSolidFill);
using PFN_GdipFillPath = decltype(&Gdiplus::DllExports::GdipFillPath);
using PFN_GdipDeleteBrush = decltype(&Gdiplus::DllExports::GdipDeleteBrush);
using PFN_GdipDeletePath = decltype(&Gdiplus::DllExports::GdipDeletePath);
using PFN_GdipDeleteGraphics = decltype(&Gdiplus::DllExports::GdipDeleteGraphics);
using PFN_GdipDisposeImage = decltype(&Gdiplus::DllExports::GdipDisposeImage);

struct GdiPlusApi {
    PFN_GdiplusStartup startup = nullptr;
    PFN_GdipCreateBitmapFromScan0 createBitmap = nullptr;
    PFN_GdipGetImageGraphicsContext getGraphics = nullptr;
    PFN_GdipSetSmoothingMode setSmoothing = nullptr;
    PFN_GdipCreatePath createPath = nullptr;
    PFN_GdipStartPathFigure startFigure = nullptr;
    PFN_GdipAddPathArc addArc = nullptr;
    PFN_GdipClosePathFigure closeFigure = nullptr;
    PFN_GdipCreateSolidFill createSolidFill = nullptr;
    PFN_GdipFillPath fillPath = nullptr;
    PFN_GdipDeleteBrush deleteBrush = nullptr;
    PFN_GdipDeletePath deletePath = nullptr;
    PFN_GdipDeleteGraphics deleteGraphics = nullptr;
    PFN_GdipDisposeImage disposeImage = nullptr;
};

GdiPlusApi g_gdiplus{};

bool EnsureGdiPlus() {
    if (g_gdiplusReady) {
        return true;
    }
    HMODULE mod = LoadLibraryW(L"gdiplus.dll");
    if (!mod) {
        return false;
    }
    auto proc = [&](const char* name) { return GetProcAddress(mod, name); };
    g_gdiplus.startup = reinterpret_cast<PFN_GdiplusStartup>(proc("GdiplusStartup"));
    g_gdiplus.createBitmap = reinterpret_cast<PFN_GdipCreateBitmapFromScan0>(proc("GdipCreateBitmapFromScan0"));
    g_gdiplus.getGraphics = reinterpret_cast<PFN_GdipGetImageGraphicsContext>(proc("GdipGetImageGraphicsContext"));
    g_gdiplus.setSmoothing = reinterpret_cast<PFN_GdipSetSmoothingMode>(proc("GdipSetSmoothingMode"));
    g_gdiplus.createPath = reinterpret_cast<PFN_GdipCreatePath>(proc("GdipCreatePath"));
    g_gdiplus.startFigure = reinterpret_cast<PFN_GdipStartPathFigure>(proc("GdipStartPathFigure"));
    g_gdiplus.addArc = reinterpret_cast<PFN_GdipAddPathArc>(proc("GdipAddPathArc"));
    g_gdiplus.closeFigure = reinterpret_cast<PFN_GdipClosePathFigure>(proc("GdipClosePathFigure"));
    g_gdiplus.createSolidFill = reinterpret_cast<PFN_GdipCreateSolidFill>(proc("GdipCreateSolidFill"));
    g_gdiplus.fillPath = reinterpret_cast<PFN_GdipFillPath>(proc("GdipFillPath"));
    g_gdiplus.deleteBrush = reinterpret_cast<PFN_GdipDeleteBrush>(proc("GdipDeleteBrush"));
    g_gdiplus.deletePath = reinterpret_cast<PFN_GdipDeletePath>(proc("GdipDeletePath"));
    g_gdiplus.deleteGraphics = reinterpret_cast<PFN_GdipDeleteGraphics>(proc("GdipDeleteGraphics"));
    g_gdiplus.disposeImage = reinterpret_cast<PFN_GdipDisposeImage>(proc("GdipDisposeImage"));
    if (!g_gdiplus.startup || !g_gdiplus.createBitmap || !g_gdiplus.getGraphics ||
        !g_gdiplus.setSmoothing || !g_gdiplus.createPath || !g_gdiplus.startFigure ||
        !g_gdiplus.addArc || !g_gdiplus.closeFigure || !g_gdiplus.createSolidFill ||
        !g_gdiplus.fillPath || !g_gdiplus.deleteBrush || !g_gdiplus.deletePath ||
        !g_gdiplus.deleteGraphics || !g_gdiplus.disposeImage) {
        return false;
    }
    Gdiplus::GdiplusStartupInput input{};
    if (g_gdiplus.startup(&g_gdiplusToken, &input, nullptr) != Gdiplus::Ok) {
        return false;
    }
    g_gdiplusReady = true;
    return true;
}

// Adds a rounded-rectangle subpath to |path|. Rects are exclusive on right/bottom,
// matching GDI conventions; the arcs join the four sides.
void AddRoundRectSubPath(Gdiplus::GpPath* path, float left, float top, float right, float bottom,
                         float radius) {
    const float d = radius * 2.0f;
    g_gdiplus.addArc(path, right - d, top, d, d, 270.0f, 90.0f);
    g_gdiplus.addArc(path, right - d, bottom - d, d, d, 0.0f, 90.0f);
    g_gdiplus.addArc(path, left, bottom - d, d, d, 90.0f, 90.0f);
    g_gdiplus.addArc(path, left, top, d, d, 180.0f, 90.0f);
    g_gdiplus.closeFigure(path);
}

// Renders the accent ring into a fresh premultiplied-ARGB DIB sized w×h and returns
// it, handing the DIB's bits back through |outBits|. The band is the even-odd fill of
// two nested rounded rects — outer inset -0.5 radius r-2, inner inset 0.5 one pixel
// smaller — so the flats land exactly on the outermost pixel at full alpha and the
// corner arcs are smoothed by GDI+ rather than clipped by a region.
HBITMAP RenderRingDib(int w, int h, int ringRadius, const Api::BorderContext& border,
                      void** outBits) {
    *outBits = nullptr;
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -h;  // top-down, matching UpdateLayeredWindow's origin
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HBITMAP dib = CreateDIBSection(nullptr, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!dib || !bits) {
        if (dib) {
            DeleteObject(dib);
        }
        return nullptr;
    }
    memset(bits, 0, (size_t)w * h * 4);

    Gdiplus::GpBitmap* bitmap = nullptr;
    Gdiplus::GpGraphics* graphics = nullptr;
    Gdiplus::GpPath* path = nullptr;
    Gdiplus::GpSolidFill* brush = nullptr;
    if (g_gdiplus.createBitmap(w, h, w * 4, PixelFormat32bppPARGB, (BYTE*)bits, &bitmap) == Gdiplus::Ok &&
        g_gdiplus.getGraphics(bitmap, &graphics) == Gdiplus::Ok &&
        g_gdiplus.setSmoothing(graphics, Gdiplus::SmoothingModeAntiAlias) == Gdiplus::Ok &&
        g_gdiplus.createPath(Gdiplus::FillModeAlternate, &path) == Gdiplus::Ok) {
        // GDI+ centres pixel i on integer i, so a band spanning [a,a+1] renders its
        // full-intensity line exactly on pixel a. The band spans [-0.5,0.5]: the
        // accent line sits on the outermost pixel of every side. The DWM base layer
        // fills the whole window rect (pixel w-1/h-1 included) with a radius-r arc
        // centred (r-0.5, r-0.5), and it ignores the window region; the 0.6.59-0.6.71
        // band on pixel 1 left that navy showing as a 1 px line past the right and
        // bottom ring and a crescent past every corner arc (2026-10-26 owner report,
        // light wallpaper). The outer arc sits 2 px inside the region radius at any radius,
        // so the band follows the menu's corner curve. On the diagonal its outer edge lands
        // about 0.6 px outside the base's arc (from the arc centres, not measured), which
        // covers the base's anti-aliased edge.
        const float inset = -0.5f;
        const float rr = std::max((float)ringRadius - 2.0f, 1.0f);
        // A radius larger than half the shorter side was measurable only on menus
        // taller/wider than 60 px; small menus need it clamped or the arcs overshoot
        // the rect and the even-odd fill distorts.
        const float maxR = (float)std::min(w, h) / 2.0f;
        const float radius = std::min(rr, std::max(maxR, 1.0f));
        // Pixel i spans [i-0.5, i+0.5], so the far edges sit at w-1-inset = w-0.5:
        // the right and bottom lines land on pixel w-1/h-1, mirroring pixel 0.
        const float right = (float)w - 1.0f - inset;
        const float bottom = (float)h - 1.0f - inset;
        AddRoundRectSubPath(path, inset, inset, right, bottom, radius);
        // The inner subpath must be its own figure: appended arcs otherwise connect to
        // the outer loop with a line, and the even-odd fill distorts by half a pixel.
        g_gdiplus.startFigure(path);
        AddRoundRectSubPath(path, inset + 1.0f, inset + 1.0f, right - 1.0f, bottom - 1.0f,
                            std::max(radius - 1.0f, 0.5f));
        // The border colour is stored ARGB; the flat API takes the same layout.
        if (g_gdiplus.createSolidFill(border.color, &brush) == Gdiplus::Ok) {
            g_gdiplus.fillPath(graphics, brush, path);
        }
    }
    if (brush) {
        g_gdiplus.deleteBrush(brush);
    }
    if (path) {
        g_gdiplus.deletePath(path);
    }
    if (graphics) {
        g_gdiplus.deleteGraphics(graphics);
    }
    if (bitmap) {
        g_gdiplus.disposeImage(bitmap);
    }
    *outBits = bits;
    return dib;
}

LRESULT CALLBACK RingOverlayProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

void RegisterRingOverlayClass() {
    WNDCLASSW wc{};
    wc.lpfnWndProc = RingOverlayProc;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = kRingOverlayClass;
    RegisterClassW(&wc);  // ERROR_CLASS_ALREADY_EXISTS is fine
}

// Creates or refreshes the ring overlay for |menu|: same rect, layered per-pixel
// alpha, click-through, topmost, never activated. The bitmap is re-rendered only
// when the menu's size or the accent colour changes.
void UpdateRingOverlay(HWND menu, int w, int h, const Api::BorderContext& border) {
    if (!EnsureGdiPlus()) {
        return;
    }
    RingOverlay* entry = nullptr;
    {
        std::lock_guard<std::mutex> lock(g_ringOverlaysLock);
        entry = &g_ringOverlays[menu];
    }
    if (!entry->window || !IsWindow(entry->window)) {
        // The overlay is owned by its menu. Windows guarantees an owned window stays
        // above its owner no matter how often the menu re-asserts its own topmost z
        // (per-tick insert-above alone lost that race - 0.6.56/0.6.57 field failure),
        // and the overlay is destroyed with the menu when the menu dies.
        entry->window = CreateWindowExW(
            WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_TOPMOST |
                WS_EX_NOACTIVATE,
            kRingOverlayClass, L"", WS_POPUP, 0, 0, w, h, menu, nullptr,
            GetModuleHandleW(nullptr), nullptr);
        if (!entry->window) {
            return;
        }
        entry->rendered = {0, 0};
    }
    if (entry->rendered.cx != w || entry->rendered.cy != h ||
        entry->renderedColor != border.color) {
        void* bits = nullptr;
        HBITMAP dib = RenderRingDib(w, h, Handler::MenuRegionRadius(menu), border, &bits);
        if (!dib) {
            return;
        }
        HDC screenDc = GetDC(nullptr);
        HDC memDc = CreateCompatibleDC(screenDc);
        if (screenDc && memDc) {
            HGDIOBJ old = SelectObject(memDc, dib);
            SIZE size{w, h};
            POINT src{0, 0};
            BLENDFUNCTION blend{AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
            UpdateLayeredWindow(entry->window, screenDc, nullptr, &size, memDc, &src, 0,
                                &blend, ULW_ALPHA);
            SelectObject(memDc, old);
        }
        if (memDc) {
            DeleteDC(memDc);
        }
        if (screenDc) {
            ReleaseDC(nullptr, screenDc);
        }
        DeleteObject(dib);
        entry->rendered = {w, h};
        entry->renderedColor = border.color;
    }
    RECT rc{};
    if (GetWindowRect(menu, &rc)) {
        // Submenu overlap flicker (0.6.70+): parent overlay kept reasserting
        // HWND_TOPMOST above the submenu at the overlap region. Place overlay
        // below any visible submenu that overlaps this menu's right/bottom edge.
        HWND submenuAbove = nullptr;
        {
            // Simple approach: check for overlapping popup windows that might be submenus
            // This avoids complex EnumWindows setup for now - we'll improve if needed.
            RECT submenuRect{};
            for (HWND submenu = GetTopWindow(nullptr); submenu != NULL; submenu = GetNextWindow(submenu, GW_HWNDNEXT)) {
                if (IsWindowVisible(submenu) && Utils::IsPopupMenu(submenu)) {  // popup menu class 32768
                    GetWindowRect(submenu, &submenuRect);
                    if (submenuRect.left < rc.right && submenuRect.right > rc.left &&
                        submenuRect.top < rc.bottom && submenuRect.bottom > rc.top) {
                        submenuAbove = submenu;
                        break;
                    }
                }
            }
        }
        if (submenuAbove && IsWindow(submenuAbove)) {
            // Place overlay below the submenu (submenu is hwndInsertAfter)
            SetWindowPos(entry->window, submenuAbove, rc.left, rc.top, 0, 0,
                         SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
        } else {
            // No overlapping submenu - keep original behavior
            SetWindowPos(entry->window, HWND_TOPMOST, rc.left, rc.top, 0, 0,
                         SWP_NOACTIVATE | SWP_NOSIZE | SWP_SHOWWINDOW);
        }
    }
    // The menu re-asserts its own topmost z on hover and repaint, which can push the
    // overlay below it. hWndInsertAfter is the window that goes above the positioned
    // one, so place the menu directly below the overlay. Passing the menu as
    // hWndInsertAfter put the overlay under the menu, and a submenu then painted over
    // its own ring (measured with probe-ring-overlays.ps1, 2026-10-24).
    SetWindowPos(menu, entry->window, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void DestroyRingOverlay(HWND menu) {
    std::lock_guard<std::mutex> lock(g_ringOverlaysLock);
    auto it = g_ringOverlays.find(menu);
    if (it == g_ringOverlays.end()) {
        return;
    }
    if (it->second.window && IsWindow(it->second.window)) {
        DestroyWindow(it->second.window);
    }
    g_ringOverlays.erase(it);
}

bool IsPopupShellMenu(HWND hWnd) {
    return hWnd && GetClassLongPtrW(hWnd, GCW_ATOM) == 0x8000;  // "#32768" is atom 32768
}

// |regionOwned|: the theme hooks already gave this menu the same full-rect
// region at its current size, so the watcher leaves it alone instead of
// resetting it (and repainting the menu) every tick. |themed|: the border the
// theme hooks resolved for this menu (their dark-mode test reads the menu
// theme, which can differ from the app setting), or null for a DirectUI menu.
void RingUnthemedMenu(HWND hWnd, int w, int h, bool regionOwned,
                      const Api::BorderContext* themed) {
    Api::BorderContext border{};
    bool darkMode = false;
    if (themed) {
        border = *themed;
    } else {
        darkMode = ThemeHelper::ShouldAppsUseDarkMode() && ThemeHelper::IsDarkModeAllowedForApp();
        Api::QueryBorderContext(L"Menu", darkMode, border);
    }
#ifdef TF_DEBUG_LOG
    Log::Write(L"[um] ring hwnd=%p size=%dx%d dark=%d useDefault=%d useNone=%d corner=%d color=%08X",
               hWnd, w, h, (int)darkMode, (int)border.colorUseDefault, (int)border.colorUseNone,
               (int)border.cornerType, (unsigned)border.color);
#endif
    if (border.colorUseDefault || w < 8 || h < 8) {
        DestroyRingOverlay(hWnd);
#ifdef TF_DEBUG_LOG
        Log::Write(L"[um] skip useDefault or tiny");
#endif
        return;
    }
    const bool rounded = border.cornerType == DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUND ||
                         border.cornerType == DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUNDSMALL;
    if (rounded) {
        // Full-rect region with the same radius the DWM backdrop layer uses (the DWM
        // menu base layer is a full-rect round rect of the window's corner radius and
        // ignores the window region - 0.6.58's inset-3 region let its navy corners
        // spill outside the accent ring). Ring band lives on the overlay at inset
        // [0.5,1.5); the region arc (radius r centred (r, r)) matches both that band
        // and the DWM layer's arc. The DWM shadow follows this region.
        int diameter = Handler::MenuRegionRadius(hWnd) * 2;
        diameter = std::min({diameter, w, h});
        if (diameter < 2) {
            diameter = 2;
        }
        if (!regionOwned) {
            unique_handle<HRGN> region{CreateRoundRectRgn(0, 0, w, h, diameter, diameter)};
            if (region) {
                SetWindowRgn(hWnd, region.release(), FALSE);
            }
        }
        // DWM rounds its own backdrop layer from the corner preference; menus default
        // to DWMWCP_ROUNDSMALL (~4 px), which leaves base-layer navy visible inside the
        // arc. ROUND pins the layer to the same radius this region uses.
        DWM_WINDOW_CORNER_PREFERENCE corner = DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUND;
        DwmSetWindowAttribute(hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, &corner, sizeof(corner));
        // The overlay is the ring; DWM's own line follows another arc.
        COLORREF noBorder = DWMWA_COLOR_NONE;
        DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &noBorder, sizeof(noBorder));
    }
    if (border.colorUseNone) {
        DestroyRingOverlay(hWnd);
        return;
    }
    // The ring is a separate layered window above the menu; nothing paints on the
    // menu's own DC, so no item blit can erase it and no region can clip it.
    UpdateRingOverlay(hWnd, w, h, border);
}

BOOL CALLBACK CollectPopupShellMenu(HWND hWnd, LPARAM lParam) {
    auto* found = reinterpret_cast<std::vector<HWND>*>(lParam);
    // GetWindowThreadProcessId returns the THREAD id; the process id arrives through
    // the out parameter. Comparing the return value to the process id never matches.
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (IsPopupShellMenu(hWnd) && IsWindowVisible(hWnd) &&
        pid == GetCurrentProcessId()) {
        RECT rc{};
        if (GetWindowRect(hWnd, &rc)) {
            int w = rc.right - rc.left;
            int h = rc.bottom - rc.top;
            if (w > 20 && h > 20) {
                found->push_back(hWnd);
            }
        }
    }
    return TRUE;
}

// Every rounded menu, themed or not, gets its ring from the overlay. Only a menu
// the theme hooks set up as square, or whose DC pass framed it, owns its border.
void RingMenu(HWND hWnd) {
    // Measure and place the overlay in the menu's own DPI mode: an app whose menu
    // thread runs in another mode than the process default (this thread's) would
    // otherwise get an overlay at the wrong size and position.
    DPI_AWARENESS_CONTEXT previousDpi =
        SetThreadDpiAwarenessContext(GetWindowDpiAwarenessContext(hWnd));
    struct DpiRestore {
        DPI_AWARENESS_CONTEXT previous;
        ~DpiRestore() {
            if (previous) {
                SetThreadDpiAwarenessContext(previous);
            }
        }
    } dpiRestore{previousDpi};
    RECT rc{};
    if (!IsWindowVisible(hWnd) || !GetWindowRect(hWnd, &rc)) {
        return;
    }
    SIZE size{rc.right - rc.left, rc.bottom - rc.top};
    if (size.cx <= 20 || size.cy <= 20) {
        return;
    }
    // Copy what the watcher needs under the lock: the paint thread can evict the
    // entry (64-window cap) at any moment, so no pointer into the map is kept.
    bool themed = false;
    bool ownsBorder = false;
    bool regionOwned = false;
    Api::BorderContext border{};
    {
        std::lock_guard<std::mutex> lock(Handler::g_windowsLock);
        auto it = Handler::g_windows.find(hWnd);
        if (it != Handler::g_windows.end()) {
            const Handler::WindowState& state = it->second;
            themed = true;
            border = state.border;
            ownsBorder = state.dcBorderPainted ||
                         (state.border.cornerType != DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUND &&
                          state.border.cornerType != DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUNDSMALL);
            regionOwned = state.regionRadius == Handler::MenuRegionRadius(hWnd) &&
                          state.regionWidth == size.cx && state.regionHeight == size.cy;
        }
    }
    if (ownsBorder) {
        DestroyRingOverlay(hWnd);
        return;
    }
    RingUnthemedMenu(hWnd, size.cx, size.cy, regionOwned, themed ? &border : nullptr);
    std::lock_guard<std::mutex> lock(g_unthemedMenusLock);
    g_unthemedMenus[hWnd] = size;
}

// The 250 ms tick runs only while a menu of this process is open. The show hook
// arms it, and the first tick that finds no menu stops it, so idle processes
// (most of the ~340 this mod loads into) never scan. Watcher thread only.
UINT_PTR g_menuTimer = 0;
bool g_menuTimerAlwaysOn = false;

void CALLBACK UnthemedMenuTimerProc(HWND, UINT, UINT_PTR, DWORD);

void ArmMenuTimer() {
    if (!g_menuTimer) {
        g_menuTimer = SetTimer(nullptr, 0, 250, UnthemedMenuTimerProc);
    }
}

void CALLBACK UnthemedMenuTimerProc(HWND, UINT, UINT_PTR, DWORD) {
    {
        // A dismissed menu is often hidden, not destroyed; its overlay goes with it.
        std::lock_guard<std::mutex> lock(g_unthemedMenusLock);
        for (auto it = g_unthemedMenus.begin(); it != g_unthemedMenus.end();) {
            if (!IsWindow(it->first) || !IsWindowVisible(it->first)) {
                DestroyRingOverlay(it->first);
                it = g_unthemedMenus.erase(it);
            } else {
                ++it;
            }
        }
    }
    std::vector<HWND> found;
    EnumWindows(CollectPopupShellMenu, reinterpret_cast<LPARAM>(&found));
#ifdef TF_DEBUG_LOG
    Log::Write(L"[um] tick found=%u", (unsigned)found.size());
#endif
    // Refreshed every tick: the overlay must follow the menu's position and z, and
    // the update is idempotent. EnumWindows lists the topmost menu first, and each
    // RingMenu raises its menu to the top, so a forward walk swapped a submenu and
    // its parent on every tick (250 ms flicker, and the submenu's ring hid under the
    // parent). Walking bottom-up keeps the stacking the menus already have.
    for (auto it = found.rbegin(); it != found.rend(); ++it) {
        RingMenu(*it);
    }
    if (found.empty() && g_menuTimer && !g_menuTimerAlwaysOn) {
        std::lock_guard<std::mutex> lock(g_unthemedMenusLock);
        if (g_unthemedMenus.empty()) {
            KillTimer(nullptr, g_menuTimer);
            g_menuTimer = 0;
        }
    }
}

// A menu's show event comes before its first border paint. Ringing it there, instead of on the
// next 250 ms tick, closes the window a submenu opened with no ring (70-200 ms per open, measured
// 2026-10-24). The watcher's own loop does the work, so the ring path stays the same one.
void CALLBACK MenuShownHookProc(HWINEVENTHOOK, DWORD, HWND hWnd, LONG idObject, LONG idChild,
                                DWORD, DWORD) {
    if (idObject != OBJID_WINDOW || idChild != CHILDID_SELF || !IsPopupShellMenu(hWnd)) {
        return;
    }
    PostThreadMessageW(GetCurrentThreadId(), kWatcherOverlayMessage, (WPARAM)hWnd, 1);
}

DWORD WINAPI UnthemedMenuThread(LPVOID) {
    // Out of context, so the callback runs in this thread's loop. Filtered to this process.
    HWINEVENTHOOK showHook = SetWinEventHook(EVENT_OBJECT_SHOW, EVENT_OBJECT_SHOW, nullptr,
                                             MenuShownHookProc, GetCurrentProcessId(), 0,
                                             WINEVENT_OUTOFCONTEXT);
    // The first tick picks up a menu already open; without the show hook nothing
    // would re-arm the tick, so it then runs all the time.
    g_menuTimerAlwaysOn = !showHook;
    ArmMenuTimer();
    if (!g_menuTimer) {
        return 1;
    }
    MSG msg{};
    // WM_TIMER reaches UnthemedMenuTimerProc only through DispatchMessage; a bare
    // GetMessage pump swallows it and the ring would never be drawn.
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (msg.message == kWatcherOverlayMessage && msg.wParam) {
            // A menu's border pass ran on another thread: act now instead of at the
            // next tick. lParam 1 rings a rounded menu as it opens; 0 drops the
            // overlay of a menu its DC framed.
            HWND menu = (HWND)msg.wParam;
            if (msg.lParam) {
                ArmMenuTimer();
                RingMenu(menu);
            } else {
                DestroyRingOverlay(menu);
            }
            continue;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    if (showHook) {
        UnhookWinEvent(showHook);
    }
    // Destroy the overlays this thread created before it exits: the window class
    // can only be unregistered once no window of it is left.
    std::vector<HWND> owned;
    {
        std::lock_guard<std::mutex> lock(g_ringOverlaysLock);
        for (const auto& entry : g_ringOverlays) {
            owned.push_back(entry.first);
        }
    }
    for (HWND menu : owned) {
        DestroyRingOverlay(menu);
    }
    return 0;
}

void StartUnthemedMenuThread() {
    RegisterRingOverlayClass();
    g_unthemedMenuThread = CreateThread(nullptr, 0, UnthemedMenuThread, nullptr, 0,
                                        &g_unthemedMenuThreadId);
#ifdef TF_DEBUG_LOG
    Log::Write(L"[um] watcher thread=%p id=%u", g_unthemedMenuThread,
               (unsigned)g_unthemedMenuThreadId);
#endif
}

// The watcher thread runs code from this DLL and owns the overlay windows, whose
// window procedure lives here too. Both must be gone before the DLL unloads: the
// thread's exit destroys its windows, then the class is unregistered.
void StopUnthemedMenuThread() {
    if (g_unthemedMenuThread) {
        PostThreadMessageW(g_unthemedMenuThreadId, WM_QUIT, 0, 0);
        WaitForSingleObject(g_unthemedMenuThread, 2000);
        CloseHandle(g_unthemedMenuThread);
        g_unthemedMenuThread = nullptr;
    }
    g_unthemedMenuThreadId = 0;
    UnregisterClassW(kRingOverlayClass, GetModuleHandleW(nullptr));
}

// ------------------------------------------------------------- lifecycle ---

void InstallHook(HMODULE module, const char* name, void* hook, void** original) {
    if (!module) {
        return;
    }
    FARPROC target = GetProcAddress(module, name);
    if (!target) {
        return;
    }
    if (WindhawkUtils::SetFunctionHook(reinterpret_cast<void*>(target), hook,
                                       reinterpret_cast<void**>(original))) {
        if (g_hookTargetCount < (int)std::size(g_hookTargets)) {
            g_hookTargets[g_hookTargetCount++] = reinterpret_cast<void*>(target);
        }
        Log::Write(L"[init] hooked %S (%p)", name, target);
    } else {
        Log::Write(L"[init] hook FAILED %S", name);
    }
}

using FillRectFn = decltype(&FillRect);
FillRectFn g_fillRectOrig = nullptr;

// The menu's device context: its window for window DCs, otherwise the flyout menu
// owned by this thread (a buffered paint DC has no window).
HWND MenuForDc(HDC hdc) {
    HWND owner = WindowFromDC(hdc);
    if (owner && Handler::IsMenuWindow(owner)) {
        return owner;
    }
    if (GetObjectType(hdc) == OBJ_MEMDC) {
        return Handler::FindFlyoutWindowOnCurrentThread(Handler::FlyoutType::Menu);
    }
    return nullptr;
}

COLORREF BrushColour(HBRUSH brush, HDC hdc) {
    LOGBRUSH lb{};
    HGDIOBJ current = brush ? static_cast<HGDIOBJ>(brush) : GetCurrentObject(hdc, OBJ_BRUSH);
    if (!current || GetObjectW(current, sizeof(lb), &lb) == 0) {
        return 0xFFFFFFFF;
    }
    return lb.lbColor;
}

// Dark-mode menus erase their body with a #202020 brush. GDI writes that colour into
// alpha-0 pixels and DWM adds it over the accent, so the body comes out lighter than the
// tint. On a menu surface, fill black instead: black adds nothing and the accent shows.
constexpr COLORREF kMenuBodyColour = 0x00202020;

int WINAPI FillRectHook(HDC hdc, const RECT* rc, HBRUSH brush) {
    if (rc) {
        COLORREF colour = BrushColour(brush, hdc);
        if (colour == kMenuBodyColour && MenuForDc(hdc)) {
            return g_fillRectOrig(hdc, rc, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
        }
    }
    return g_fillRectOrig(hdc, rc, brush);
}

// Buffered paints were tracked so the ring could be re-stroked after every item
// blit. The overlay ring (UnthemedMenuWatcher) replaced that: it floats above the
// menu and no blit can erase it, so the hooks had no job left — and their re-stroke
// was a second painter under the overlay.
void Install() {
    HMODULE uxtheme = GetModuleHandleW(L"uxtheme.dll");
    HMODULE gdi32 = GetModuleHandleW(L"gdi32.dll");
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    if (!uxtheme) {
        uxtheme = LoadLibraryW(L"uxtheme.dll");
    }
    if (!uxtheme) {
        Log::Write(L"[init] uxtheme.dll missing");
        return;
    }

    InstallHook(uxtheme, "DrawThemeBackground",
                reinterpret_cast<void*>(DrawThemeBackgroundHook),
                reinterpret_cast<void**>(&g_drawThemeBackgroundOrig));
    InstallHook(uxtheme, "DrawThemeBackgroundEx",
                reinterpret_cast<void*>(DrawThemeBackgroundExHook),
                reinterpret_cast<void**>(&g_drawThemeBackgroundExOrig));
    InstallHook(uxtheme, "DrawThemeText", reinterpret_cast<void*>(DrawThemeTextHook),
                reinterpret_cast<void**>(&g_drawThemeTextOrig));
    InstallHook(uxtheme, "DrawThemeTextEx", reinterpret_cast<void*>(DrawThemeTextExHook),
                reinterpret_cast<void**>(&g_drawThemeTextExOrig));
    InstallHook(uxtheme, "GetThemeMargins", reinterpret_cast<void*>(GetThemeMarginsHook),
                reinterpret_cast<void**>(&g_getThemeMarginsOrig));
    InstallHook(user32, "DrawTextW", reinterpret_cast<void*>(DrawTextWHook),
                reinterpret_cast<void**>(&g_drawTextWOrig));
    InstallHook(user32, "FillRect", reinterpret_cast<void*>(FillRectHook),
                reinterpret_cast<void**>(&g_fillRectOrig));
}

void Uninstall() {
    for (int i = 0; i < g_hookTargetCount; i++) {
        Wh_RemoveFunctionHook(g_hookTargets[i]);
    }
    g_hookTargetCount = 0;
    Wh_ApplyHookOperations();
}

}  // namespace Hooks

}  // namespace tf

// ===========================================================================
// Mod entry points
// ===========================================================================

BOOL Wh_ModInit() {
    tf::Cfg::Load();
    if (tf::Api::IsCurrentProcessInBlockList()) {
        tf::Log::Write(L"[init] process is block-listed");
        return FALSE;
    }
    tf::Log::Write(L"[init] process=%s", tf::Utils::GetProcessName().c_str());
    tf::Hooks::Install();
    tf::DarkMenus::Install();
    if (!tf::Api::IsPartDisabled(L"Menu")) {
        tf::Hooks::StartUnthemedMenuThread();
    }
    return TRUE;
}

void Wh_ModSettingsChanged() {
    tf::Cfg::Load();
    tf::DarkMenus::Refresh();
    // Existing flyout windows keep their applied effect until they close; new
    // ones pick up the new settings.
}

void Wh_ModBeforeUninit() {
    tf::DarkMenus::Uninstall();
    tf::Hooks::Uninstall();
    tf::Hooks::StopUnthemedMenuThread();
}

