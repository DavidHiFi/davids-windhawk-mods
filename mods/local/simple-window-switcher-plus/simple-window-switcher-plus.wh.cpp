// ==WindhawkMod==
// @id              simple-window-switcher-plus
// @name            Simple Window Switcher Plus
// @description     Customizable Alt+Tab with Vista animations, background blur and elevated app support
// @version         1.0.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @include         windhawk.exe
// @include         explorer.exe
// @compilerOptions -ld3d11 -ldxgi -ld2d1 -ldcomp -ldwrite -ldwmapi -lole32 -loleaut32 -luuid -lruntimeobject -lwindowscodecs -lshcore -lshell32 -lgdi32 -luxtheme -lshlwapi -lcomctl32 -lgdiplus -lversion
// @license         GPL-2.0
// ==/WindhawkMod==
// ==WindhawkModReadme==
/*
# Simple Window Switcher Plus

Vista's animated live-window layouts and blurred background, with Simple Window Switcher's configurable layout and shared appearance controls.

![Preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/simple-window-switcher-plus.gif)

## Features

- Vista Flip 3D, Cascade, Cover Flow and the other original animated layouts.
- Simple layout preserves the original grouping, badge, corners, dimensions and navigation settings.
- Shared title font, icon visibility, window exclusions, monitor filtering and minimized-window ordering in Vista mode.
- Custom or accent selection borders and background tint in Vista mode.
- Dedicated administrator host handles shortcuts while elevated apps have focus.
- Change layouts in Settings without restarting Explorer.

## Settings

Choose the switcher layout first. Animation and background settings control Vista mode. Style, Theme, Appearance, Dimensions, Grouping and Accessibility control Simple mode. Vista also uses the shared font, icon/title visibility, theme border/background colors, exclusions, per-monitor filtering and minimized-window sorting. Badge layouts, grouping and thumbnail corner settings apply to Simple mode.

Disable other Alt+Tab replacements before enabling this mod. Administrator hosting requests Windows elevation when needed. It does not replace shortcuts on the secure UAC desktop. Windows that block capture show an icon card.

## Credits

Based on Simple Window Switcher 2.1 by Lone, with improvements by Asteski and bropines, and the original Simple Window Switcher by valinet. Vista rendering is from Alt+Tab Flip 3D 1.5.3 by caliberda. The combined mod is GPL-2.0; the Vista source retains its MIT notice below.
*/
// ==/WindhawkModReadme==
// ==WindhawkModSettings==
/*
- renderer: vista
  $name: Switcher layout
  $options:
  - vista: Vista animated layouts
  - simple: Simple customizable layout
- elevatedHost: true
  $name: Run switcher as administrator
  $description: Handles Alt+Tab while an elevated app has focus. Uses an isolated Windhawk tool process.
- style: flip3d
  $name: Animation style
  $name:pt-BR: Estilo da animação
  $description: How the windows are presented
  $description:pt-BR: Como as janelas são apresentadas
  $options:
  - flip3d: Flip 3D (Vista stack)
  - cascade: Cascade
  - coverflow: Cover Flow
  - carousel: Carousel
  - grid: Grid (Mission Control)
  - helix: Helix
  - fan: Fan
  - panorama: Panorama
  - tunnel: Tunnel
  - rolodex: Rolodex
  - windows11: Windows 11 (enhanced)
  - thumbnails: Thumbnails with titles below
  - icons: Icons and titles
  - list: Vertical list
  - classic: Classic (Windows XP)
  - native: Native Windows Alt+Tab
  $options:pt-BR:
  - flip3d: Flip 3D (pilha do Vista)
  - cascade: Cascata
  - coverflow: Cover Flow
  - carousel: Carrossel
  - grid: Grade (Mission Control)
  - helix: Hélice
  - fan: Leque
  - panorama: Panorama
  - tunnel: Túnel
  - rolodex: Rolodex
  - windows11: Windows 11 (aprimorado)
  - thumbnails: Miniaturas com título embaixo
  - icons: Ícones e títulos
  - list: Lista vertical
  - classic: Clássico (Windows XP)
  - native: Alt+Tab nativo do Windows
- monitor: cursor
  $name: Monitor
  $name:pt-BR: Monitor
  $description: Which monitor the switcher opens on
  $description:pt-BR: Em qual monitor o alternador abre
  $options:
  - cursor: Where the mouse cursor is
  - activeWindow: Where the active window is
  $options:pt-BR:
  - cursor: Onde está o cursor do mouse
  - activeWindow: Onde está a janela ativa
- animationDuration: 420
  $name: Open/close animation duration (ms)
  $name:pt-BR: Duração da animação de abrir/fechar (ms)
  $description: How long the windows take to fly into the stack and back
  $description:pt-BR: Quanto tempo as janelas levam para voar até a pilha e voltar
- flipSpeed: 100
  $name: Flip speed (%)
  $name:pt-BR: Velocidade da troca (%)
  $description: Speed of the spring animation when flipping between windows (25-400)
  $description:pt-BR: Velocidade da animação de mola ao passar entre as janelas (25-400)
- showDelay: 90
  $name: Show delay (ms)
  $name:pt-BR: Atraso para exibir (ms)
  $description: A quick Alt+Tab shorter than this switches instantly without showing the stack
  $description:pt-BR: Um Alt+Tab mais rápido que isso troca na hora, sem mostrar a pilha
- tiltAngle: 30
  $name: Tilt angle (degrees)
  $name:pt-BR: Ângulo de inclinação (graus)
  $description: How much the windows are turned (0-70). Used by Flip 3D, Cascade and Cover Flow
  $description:pt-BR: Quanto as janelas ficam viradas (0-70). Usado pelo Flip 3D, Cascata e Cover Flow
- stackSpacing: 100
  $name: Stack spacing (%)
  $name:pt-BR: Espaçamento da pilha (%)
  $description: Distance between the windows in the stack (40-250)
  $description:pt-BR: Distância entre as janelas na pilha (40-250)
- maxWindows: 20
  $name: Maximum number of windows
  $name:pt-BR: Número máximo de janelas
  $description: Windows beyond this number (by recent use) are not shown (2-40)
  $description:pt-BR: Janelas além desse número (por uso recente) não são mostradas (2-40)
- background: blur
  $name: Background
  $name:pt-BR: Fundo
  $description: What is shown behind the stack
  $description:pt-BR: O que aparece atrás da pilha
  $options:
  - blur: Blurred wallpaper
  - wallpaper: Wallpaper
  - dim: Dim only
  $options:pt-BR:
  - blur: Papel de parede desfocado
  - wallpaper: Papel de parede
  - dim: Apenas escurecer
- blurAmount: 20
  $name: Background blur strength
  $name:pt-BR: Intensidade do desfoque do fundo
  $description: Used by the blurred wallpaper background (1-100)
  $description:pt-BR: Usado pelo fundo com papel de parede desfocado (1-100)
- dimOpacity: 25
  $name: Background dimming (%)
  $name:pt-BR: Escurecimento do fundo (%)
  $description: How dark the background gets (0-90). For "Dim only", around 60 looks best
  $description:pt-BR: Quanto o fundo escurece (0-90). Para "Apenas escurecer", algo perto de 60 fica melhor
- showTitle: true
  $name: Show window title
  $name:pt-BR: Mostrar título da janela
  $description: Shows the icon and title of the window in front
  $description:pt-BR: Mostra o ícone e o título da janela da frente
- shadows: true
  $name: Window shadows
  $name:pt-BR: Sombras das janelas
  $description: Soft shadows under the windows in the stack
  $description:pt-BR: Sombras suaves sob as janelas da pilha
- includeMinimized: true
  $name: Include minimized windows
  $name:pt-BR: Incluir janelas minimizadas
- minimizedContent: true
  $name: Show the content of minimized windows
  $name:pt-BR: Mostrar o conteúdo das janelas minimizadas
  $description: Shows the last content of minimized windows, like the taskbar previews. When off, they're shown as a card with the app icon
  $description:pt-BR: Mostra o último conteúdo das janelas minimizadas, como as miniaturas da barra de tarefas. Desligado, elas aparecem como um cartão com o ícone do app
- Style:
    - theme: none
      $name: Style
      $description: Visual theme style for the switcher background.
      $options:
      - none: None (Solid/Transparent)
      - backdrop: Acrylic (Windows 10+)
      - mica: Mica Blur (Windows 11 only)
    - colorScheme: system
      $name: Color Scheme
      $options:
      - system: Follow system setting
      - light: Light
      - dark: Dark
    - highlightStyle: border
      $name: Task Highlight Style
      $description: Style used for the selected task row/tile. Applies to both light and dark themes.
      $options:
      - border: Border only
      - fillAndBorder: Background fill and border
      - fillOnly: Background fill only
    - opacity: 100
      $name: Background Opacity
      $description: Background opacity percentage (0-100), applies to None and Acrylic themes for both light and dark themes. Set value to '80' for Acrylic to see the effect.
    - DarkMode:
        - borderColorMode: default
          $name: Border Color
          $description: Color source for the selected/hovered task border in dark mode.
          $options:
          - default: Default
          - custom: Custom
          - accent: Accent
        - highlightFillColorMode: default
          $name: Task Highlight Background Fill Color
          $description: Color source for the selected task background fill in dark mode.
          $options:
          - default: Default
          - custom: Custom
          - accent: Accent
        - bgColorMode: default
          $name: Switcher Background Color
          $description: Color source for the switcher window background in dark mode. Applies to None and Acrylic themes.
          $options:
          - default: Default
          - custom: Custom
          - accent: Accent
        - customBorderColor: "#FFFFFF"
          $name: Custom Border Color
          $description: HEX color value, used when Border Color is set to Custom.
        - customHighlightFillColor: "#FFFFFF"
          $name: Custom Task Highlight Background Fill Color
          $description: HEX color value, used when Task Highlight Background Fill Color is set to Custom.
        - customBgColor: "#202020"
          $name: Custom Switcher Background Color
          $description: HEX color value, used when Switcher Background Color is set to Custom.
        - iconBgColorMode: default
          $name: Badge Icon Background Color
          $description: Color source for the badge icon background pill in dark mode.
          $options:
          - default: Default
          - custom: Custom
          - accent: Accent
        - customIconBgColor: "#000000"
          $name: Custom Badge Icon Background Color
          $description: HEX color value, used when Badge Icon Background Color is set to Custom.
        - iconBgOpacity: 55
          $name: Badge Icon Background Opacity
          $description: Opacity percentage (0-100) for the badge icon background in dark mode.
        - indicatorBgColorMode: default
          $name: Group Indicator Background Color
          $description: Color source for the group indicator background pill in dark mode.
          $options:
          - default: Default
          - custom: Custom
          - accent: Accent
        - customIndicatorBgColor: "#333333"
          $name: Custom Group Indicator Background Color
          $description: HEX color value, used when Group Indicator Background Color is set to Custom.
        - indicatorBgOpacity: 85
          $name: Group Indicator Background Opacity
          $description: Opacity percentage (0-100) for the group indicator background in dark mode.
        - indicatorTextColorMode: default
          $name: Group Indicator Text Color
          $description: Color source for the group indicator text in dark mode.
          $options:
          - default: Default
          - custom: Custom
          - accent: Accent
        - customIndicatorTextColor: "#FFFFFF"
          $name: Custom Group Indicator Text Color
          $description: HEX color value, used when Group Indicator Text Color is set to Custom.
      $name: Dark Mode
    - LightMode:
        - borderColorMode: default
          $name: Border Color
          $description: Color source for the selected/hovered task border in light mode.
          $options:
          - default: Default
          - custom: Custom
          - accent: Accent
        - highlightFillColorMode: default
          $name: Task Highlight Background Fill Color
          $description: Color source for the selected task background fill in light mode.
          $options:
          - default: Default
          - custom: Custom
          - accent: Accent
        - bgColorMode: default
          $name: Switcher Background Color
          $description: Color source for the switcher window background in light mode. Applies to None and Acrylic themes.
          $options:
          - default: Default
          - custom: Custom
          - accent: Accent
        - customBorderColor: "#000000"
          $name: Custom Border Color
          $description: HEX color value, used when Border Color is set to Custom.
        - customHighlightFillColor: "#000000"
          $name: Custom Task Highlight Background Fill Color
          $description: HEX color value, used when Task Highlight Background Fill Color is set to Custom.
        - customBgColor: "#F3F3F3"
          $name: Custom Switcher Background Color
          $description: HEX color value, used when Switcher Background Color is set to Custom.
        - iconBgColorMode: default
          $name: Badge Icon Background Color
          $description: Color source for the badge icon background pill in light mode.
          $options:
          - default: Default
          - custom: Custom
          - accent: Accent
        - customIconBgColor: "#FFFFFF"
          $name: Custom Badge Icon Background Color
          $description: HEX color value, used when Badge Icon Background Color is set to Custom.
        - iconBgOpacity: 55
          $name: Badge Icon Background Opacity
          $description: Opacity percentage (0-100) for the badge icon background in light mode.
        - indicatorBgColorMode: default
          $name: Group Indicator Background Color
          $description: Color source for the group indicator background pill in light mode.
          $options:
          - default: Default
          - custom: Custom
          - accent: Accent
        - customIndicatorBgColor: "#EAEAEA"
          $name: Custom Group Indicator Background Color
          $description: HEX color value, used when Group Indicator Background Color is set to Custom.
        - indicatorBgOpacity: 85
          $name: Group Indicator Background Opacity
          $description: Opacity percentage (0-100) for the group indicator background in light mode.
        - indicatorTextColorMode: default
          $name: Group Indicator Text Color
          $description: Color source for the group indicator text in light mode.
          $options:
          - default: Default
          - custom: Custom
          - accent: Accent
        - customIndicatorTextColor: "#000000"
          $name: Custom Group Indicator Text Color
          $description: HEX color value, used when Group Indicator Text Color is set to Custom.
      $name: Light Mode
  $name: Theme
- Appearance:
    - Corners:
        - cornerPreference: round
          $name: Corner Preference
          $description: Corner radius for the switcher window and its elements.
          $options:
          - none: Squared
          - round: Rounded
          - roundSmall: Rounded small
          - custom: Custom
        - customCornerRadius: 8
          $name: Custom Corner Radius (px)
          $description: Corner radius in pixels, used when Corner Preference is set to Custom. Applies to task borders, close buttons, and thumbnails.
        - taskRoundedCorners: false
          $name: Round Task Borders and Close Button
          $description: Apply rounded corners to the selected task border and close button.
        - roundThumbnailCorners: false
          $name: Round Thumbnail Corners
          $description: Round the corners of window thumbnails. Uses the radius from Corner Preference.
        - roundGroupIndicator: false
          $name: Round Group Indicator
          $description: Round the corners of the group indicator. Uses the radius from Corner Preference.
        - roundBadgeIconBackground: false
          $name: Round Icon Background (only for badge-layout)
          $description: Round the corners of the badge icon background pill. Uses the radius from Corner Preference.
      $name: Corners
    - Thumbnails:
        - thumbnailPosition: bottom
          $name: Thumbnail Position
          $description: Change the thumbnail position.
          $options:
          - bottom: Bottom
          - top: Top
          - left: Left
          - right: Right
        - thumbnailAlignment: left
          $name: Thumbnail Alignment
          $description: Align thumbnail content inside the available thumbnail area.
          $options:
          - left: Left
          - centered: Center
          - right: Right
        - showThumbnails: true
          $name: Show Thumbnails
          $description: Show DWM live thumbnail previews of windows.
        - showCloseButton: true
          $name: Show Close Button
          $description: Show the 'X' button on hover to close windows.
        - showHoverBorder: true
          $name: Show Hover Border
          $description: Show a colored border around the thumbnail when hovered.
        - showThumbnailShadow: false
          $name: Show Thumbnail Shadow
          $description: Draw a soft drop shadow behind each window thumbnail.
      $name: Thumbnails
    - HeaderContent:
        - iconSize: small
          $name: Icon Size
          $description: Size of the header icon.
          $options:
          - small: Small (16x16)
          - medium: Medium (32x32)
          - large: Large (48x48)
          - xlarge: Extra Large (64x64)
        - showTitle: true
          $name: Show Title Label
        - showIcon: true
          $name: Show Icon
        - centerTaskContent: false
          $name: Center Task Icon and Title
          $description: Center the icon and title together in each task row.
      $name: Header Content
    - Orientation:
        - taskListOrientation: horizontal
          $name: Task List Orientation
          $description: Arrange tasks left-to-right or top-to-bottom.
          $options:
          - horizontal: Horizontal
          - vertical: Vertical
        - headerContentOrientation: horizontal
          $name: Header Content Orientation
          $description: Orientation of the task header icon and title.
          $options:
          - horizontal: Horizontal
          - vertical: Vertical
      $name: Orientation
    - Position:
        - switcherPosition: center
          $name: Switcher Position
          $description: Where the switcher should appear on the screen.
          $options:
          - topLeft: Top Left
          - topCenter: Top Center
          - topRight: Top Right
          - centerLeft: Center Left
          - center: Center
          - centerRight: Center Right
          - bottomLeft: Bottom Left
          - bottomCenter: Bottom Center
          - bottomRight: Bottom Right
        - switcherPositionMargin: 0
          $name: Switcher Position Margin (px)
          $description: Offset from the screen edges when using non-centered positions.
      $name: Position
    - BadgeLayout:
        - enableBadgeLayout: false
          $name: Enable Badge Layout (macOS-style)
          $description: Overlay the icon on top of the thumbnail and place the title outside. Overrides normal header positioning when enabled. Requires Show Thumbnails to be on.
        - badgeIconPosition: bottomCenter
          $name: Badge Icon Position
          $description: Where to place the icon overlay on the thumbnail.
          $options:
          - topLeft: Top Left
          - topCenter: Top Center
          - topRight: Top Right
          - centerLeft: Center Left
          - center: Center
          - centerRight: Center Right
          - bottomLeft: Bottom Left
          - bottomCenter: Bottom Center
          - bottomRight: Bottom Right
        - badgeTitlePosition: bottom
          $name: Badge Title Position
          $description: Where to place the title label relative to the thumbnail.
          $options:
          - top: Above Thumbnail
          - bottom: Below Thumbnail
        - showBadgeIconBackground: true
          $name: Show Badge Icon Background
          $description: Draw a backdrop shape behind the badge icon. If off, a drop shadow is drawn instead.
        - showBadgeIconBackgroundShadow: false
          $name: Show Badge Icon Background Shadow
          $description: Draw a soft drop shadow under the badge icon background pill.
        - badgeIconPadding: 4
          $name: Badge Icon Padding (px)
          $description: Extra space between the icon and the edge of its background.
        - badgeIconOffsetX: 0
          $name: Badge Icon Offset X (px)
          $description: Nudge the icon horizontally from its default position.
        - badgeIconOffsetY: 0
          $name: Badge Icon Offset Y (px)
          $description: Nudge the icon vertically from its default position.
      $name: Badge Layout
    - Font:
        - fontFamily: Segoe UI
          $name: Font Family
          $description: Font used for window titles (e.g., Segoe UI, Tahoma).
        - fontSize: 9
          $name: Font Size
          $description: Size of the font in points.
        - fontStyle: regular
          $name: Font Style
          $options:
          - light: Light
          - regular: Regular
          - semibold: Semi-Bold
          - bold: Bold
          - italic: Italic
          - boldItalic: Bold Italic
        - applyToGroupIndicator: false
          $name: Apply to Group Indicator
          $description: Use these custom font settings for the grouped window count indicator badge.
      $name: Font
    - showOverflowIndicator: true
      $name: Show Overflow Indicator
      $description: Show chevron indicators at the edges when there are more windows off-screen.
  $name: Appearance
- Dimensions:
    - rowHeight: 230
      $name: Row Height
      $description: Total height of each thumbnail row in pixels (before DPI scaling). Default 230 matches ExplorerPatcher.
    - rowWidth: 0
      $name: Row Width
      $description: Width of each thumbnail tile in pixels (before DPI scaling). Set to 0 for automatic width based on window aspect ratio.
    - maxWidthPercent: 80
      $name: Maximum Width (percentage of screen width)
    - maxHeightPercent: 80
      $name: Maximum Height (percentage of screen height)
    - stretchThumbnailsToTaskWidth: true
      $name: Stretch Thumbnails to Task Width
      $description: When enabled, custom row width also changes thumbnail width. Disable to keep thumbnail aspect sizing while row width controls only task tile width.
    - autoFitTasks: false
      $name: Shrink Tasks to Fit
      $description: Automatically shrink task tiles (thumbnails and icons) in discrete steps as the number of visible windows grows, so more tasks stay visible without being pushed off-screen. Your Row Height and Icon Size act as the maximum size.
  $name: Dimensions
- Grouping:
    - showApplications: false
      $name: Group Windows by Application
      $description: Show one entry per application instead of one per window, similar to macOS Cmd+Tab. Selecting an application switches to its most recently used window. Tap Ctrl while an application is selected to expand it and show all of its windows as thumbnails.
    - showTitles: windowTitle
      $name: Show Titles
      $description: Which title text to display for each entry. Only applies when "Group Windows by Application" is enabled.
      $options:
      - windowTitle: Window Title
      - appName: Application Name
      - appNameWindowTitle: Application Name - Window Title
    - restoreAllWindows: false
      $name: Restore All Windows
      $description: When switching to an application, restore all of its minimized windows to their previous state. Only applies when "Group Windows by Application" is enabled. Tip - to act on a single window instead, tap Ctrl while the application is selected to show all of its windows and pick one.
    - showGroupIndicator: true
      $name: Show Group Indicator
      $description: Show a count badge on grouped application entries indicating how many windows are in the group. Only visible when Group Windows by Application is enabled.
    - showGroupIndicatorShadow: false
      $name: Show Group Indicator Shadow
      $description: Show a soft drop shadow behind the group indicator badge.
    - groupCloseBehavior: closeRecent
      $name: Group Close Button Behavior
      $description: Action when closing a grouped application entry.
      $options:
      - closeRecent: Close Most Recent Window
      - closeAll: Close All Windows
  $name: Grouping
- Accessibility:
    - showDelay: 0
      $name: Show Delay (ms)
      $description: Delay in milliseconds before showing the switcher (0 = instant).
    - scrollWheelBehavior: never
      $name: Scroll Wheel Activation
      $description: When the scroll wheel should be active.
      $options:
      - never: Never
      - always: Always
      - stickyOnly: Only in sticky mode
    - scrollWheelAction: selection
      $name: Scroll Wheel Action
      $options:
      - selection: Change Selection
      - page: Scroll Pages
    - scrollSecondaryAction: page
      $name: Secondary Scroll Wheel Action (With Modifier)
      $options:
      - none: None
      - selection: Change Selection
      - page: Scroll Pages
    - scrollSecondaryModifier: shift
      $name: Secondary Scroll Wheel Modifier Key
      $options:
      - none: None
      - shift: Shift
      - ctrl: Ctrl
      - alt: Alt
    - reverseScrollDirection: false
      $name: Reverse Scroll Direction
    - backwardShortcut: altShiftTab
      $name: Backward Shortcut
      $description: Shortcut used to move backward in the switcher.
      $options:
      - altShiftTab: Alt+Shift+Tab (default)
      - altShift: Alt+Shift
      - altBacktick: Alt+Backtick
    - altBacktickBehavior: backward
      $name: Alt+Backtick Behavior
      $description: Action to perform when pressing Alt+` (Backtick).
      $options:
      - none: Disabled / Do Nothing
      - backward: Cycle Backward
      - sameApp: Cycle Between Windows of Current Application
    - switcherDisplayBehavior: cursorMonitor
      $name: Switcher Display Behavior
      $options:
      - primaryOnly: Primary Monitor Only
      - allMonitors: All Monitors
      - cursorMonitor: Monitor Based on Cursor Location
    - perMonitorWindows: false
      $name: Display Windows Only from the Monitor Containing the Cursor
    - virtualDesktopBehavior: allDesktops
      $name: Virtual Desktop Behavior
      $description: Choose which virtual desktops to show windows from.
      $options:
      - currentOnly: Show windows from current virtual desktop only
      - allDesktops: Show windows from all virtual desktops
    - hideMinimizedWindows: false
      $name: Hide Minimized Windows
      $description: Hide minimized windows from the switcher. When "Group Windows by Application" is enabled, an application is only hidden if all of its windows are minimized.
    - sortMinimizedWindowsToEnd: true
      $name: Sort Minimized Windows to the End
      $description: Sort minimized windows after all active windows. Disable this to keep minimized windows in their Z-order.
  $name: Accessibility
- ExcludedWindows:
    - excludeByTitle: ""
      $name: Exclude by Window Title
      $description: "Window title patterns to exclude, separated by ';' (wildcards supported: * matches any characters, ? matches one). Example: *Notepad*;*Chrome*"
    - excludeByExe: ""
      $name: Exclude by Executable Name
      $description: "Executable name patterns to exclude, separated by ';' (wildcards supported: * matches any characters, ? matches one). Example: notepad.exe;chrome.exe"
  $name: Excluded Windows
  $description: Exclude specific windows from appearing in the switcher.
- customHeader:
  - - process: ""
      $name: Process Name
      $description: "Executable name to match (wildcards supported: * matches any characters, ? matches one). Example: chrome.exe or *code.exe"
    - iconPath: ""
      $name: Icon Path
      $description: "Full path to an icon source (.ico, .exe or .dll); the first icon in the file is used. Leave empty to keep the default icon. Example: C:\\Icons\\myapp.ico"
    - appName: ""
      $name: Application Name
      $description: "Custom name to display for matching tasks, replacing the detected application name. Leave empty to keep the default. Shown in the 'App name' and 'App name + Window title' title modes (requires 'Group Windows by Application' to be enabled)."
  $name: Custom Header
  $description: Assign a custom icon and/or application name to tasks based on their executable name. The first matching rule wins.

*/
// ==/WindhawkModSettings==
/* Vista renderer: Copyright caliberda. MIT License.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <initguid.h>
#include <windows.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <propkey.h>
#include <shobjidl.h>
#include <knownfolders.h>
#include <windowsx.h>
#include <commctrl.h>
#include <appmodel.h>
#include <vector>
#include <atomic>
#include <map>
#include <string>
#include <algorithm>
#include <gdiplus.h>
#include <d2d1_3.h>
#include <d2d1effects_2.h>
#include <d3d11_4.h>
#include <dcomp.h>
#include <dwrite.h>
#include <dxgi1_3.h>
#include <inspectable.h>
#include <propsys.h>
#include <shellscalingapi.h>
#include <tlhelp32.h>
#include <wincodec.h>
#include <windows.graphics.capture.interop.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Graphics.Capture.h>
#include <winrt/Windows.Graphics.DirectX.Direct3D11.h>
#include <winrt/Windows.Graphics.DirectX.h>
#include <winrt/Windows.Security.Authorization.AppCapabilityAccess.h>
#include <cmath>
#include <memory>
#include <unordered_map>
#include <windhawk_utils.h>
namespace Simple {

#define SWS_CLASSNAME       L"WindhawkSWSPlus_Switcher"
#define SWS_ICON_SIZE       16
// Lower bound (pre-DPI px) for the auto-fit "Shrink tasks to fit" row height so
// thumbnails never collapse to an unusable size.
#define SWS_AUTOFIT_MIN_ROWHEIGHT 90
// EP-style nested padding layers (before DPI scaling)
#define SWS_MASTER_PADDING      20  // Outer margin of the entire switcher window
#define SWS_ELEMENT_PAD_TOP     5   // Vertical margin between cell border and content
#define SWS_ELEMENT_PAD_BOTTOM  5
#define SWS_ELEMENT_PAD_LEFT    2   // Horizontal margin between cell border and content
#define SWS_ELEMENT_PAD_RIGHT   2
#define SWS_PAD_TOP             7   // Inner distance from content area to thumbnail
#define SWS_PAD_BOTTOM          7
#define SWS_PAD_LEFT            7
#define SWS_PAD_RIGHT           7
#define SWS_PAD_DIVIDER         7   // Vertical divider between title row and thumbnail
#define SWS_ROW_TITLE_HEIGHT    30  // Height of icon+title row
#define SWS_MAX_TILE_ASPECT     2.0 // Max thumbnail width = thumbH * this
#define SWS_CONTOUR_SIZE        2
#define SWS_HOTKEY_ALTTAB           1
#define SWS_HOTKEY_ALTSHIFTTAB      2
#define SWS_HOTKEY_ALTCTRLTAB       3
#define SWS_HOTKEY_ALTSHIFTCTRLTAB  4
#define SWS_HOTKEY_ALTBACKTICK      5
#define SWS_HOTKEY_WINALTTAB        6
#define SWS_HOTKEY_WINALTSHIFTTAB   7
#define SWS_HOTKEY_RETRY_TIMER_ID   100
#define SWS_HOTKEY_RETRY_INTERVAL   2000
#define SWS_BG_DARK          RGB(32, 32, 32)
#define SWS_BG_LIGHT         RGB(243, 243, 243)
#define SWS_CONTOUR_DARK     RGB(255, 255, 255)
#define SWS_CONTOUR_LIGHT    RGB(0, 0, 0)
#define SWS_TEXT_DARK         RGB(255, 255, 255)
#define SWS_TEXT_LIGHT        RGB(0, 0, 0)
#define SWS_SHOW_DELAY_TIMER_ID 101
#define SWS_ALT_POLL_TIMER_ID   102
// Posted by the low-level mouse hook so the heavy CycleLinear work runs in the
// wndproc instead of on the synchronous raw-input path. WPARAM is the direction.
#define WM_SWS_SCROLL           (WM_APP + 1)
#define WM_SWS_SETTINGS_CHANGED (WM_APP + 2)

typedef BOOL (WINAPI *IsShellWindow_t)(HWND);
typedef HWND (WINAPI *GhostWindowFromHungWindow_t)(HWND);
struct ACCENT_POLICY { DWORD AccentState; DWORD AccentFlags; DWORD GradientColor; DWORD AnimationId; };
struct WINDOWCOMPOSITIONATTRIBDATA { DWORD dwAttrib; PVOID pvData; SIZE_T cbData; };
typedef BOOL(WINAPI *SetWindowCompositionAttribute_t)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);

struct WindowEntry {
    HWND hWnd; HICON hIcon; WCHAR title[256]; std::map<HWND, HTHUMBNAIL> hThumbs;
    RECT rcCell; RECT rcThumbActual; RECT rcThumbSlot;
    SIZE sourceSize;           // Raw DWM surface size
    RECT rcSourceCrop;         // Source crop rect for DWM_TNP_RECTSOURCE
    SIZE effectiveSourceSize;  // Source size after cropping invisible frame
    std::vector<HWND> groupWindows;  // All app windows when grouping by application
    int drawnIconX;            // X coordinate where the icon is drawn
    int drawnIconY;            // Y coordinate where the icon is drawn
    int drawnIconSz;           // Size of the drawn icon
};
struct Settings {
    WCHAR theme[32]; WCHAR colorScheme[32]; WCHAR cornerPreference[32]; WCHAR scrollWheelBehavior[32]; WCHAR scrollWheelAction[32]; WCHAR scrollSecondaryAction[32]; WCHAR scrollSecondaryModifier[32]; WCHAR taskListOrientation[32]; WCHAR headerContentOrientation[32]; WCHAR iconSize[32]; WCHAR backwardShortcut[32]; WCHAR altBacktickBehavior[32]; WCHAR thumbnailPosition[32]; WCHAR thumbnailAlignment[32]; WCHAR switcherDisplayBehavior[32];
    WCHAR virtualDesktopBehavior[32];
    // Global theme settings (apply to both light and dark)
    WCHAR highlightStyle[32]; int opacity;
    // Dark Mode color settings
    WCHAR borderColorModeDark[16]; WCHAR highlightFillColorModeDark[16]; WCHAR bgColorModeDark[16]; WCHAR iconBgColorModeDark[16];
    WCHAR customBorderColorDark[16]; WCHAR customHighlightFillColorDark[16]; WCHAR customBgColorDark[16]; WCHAR customIconBgColorDark[16];
    int iconBgOpacityDark;
    WCHAR indicatorBgColorModeDark[16]; WCHAR customIndicatorBgColorDark[16]; int indicatorBgOpacityDark;
    WCHAR indicatorTextColorModeDark[16]; WCHAR customIndicatorTextColorDark[16];
    // Light Mode color settings
    WCHAR borderColorModeLight[16]; WCHAR highlightFillColorModeLight[16]; WCHAR bgColorModeLight[16]; WCHAR iconBgColorModeLight[16];
    WCHAR customBorderColorLight[16]; WCHAR customHighlightFillColorLight[16]; WCHAR customBgColorLight[16]; WCHAR customIconBgColorLight[16];
    int iconBgOpacityLight;
    WCHAR indicatorBgColorModeLight[16]; WCHAR customIndicatorBgColorLight[16]; int indicatorBgOpacityLight;
    WCHAR indicatorTextColorModeLight[16]; WCHAR customIndicatorTextColorLight[16];
    WCHAR fontFamily[64]; WCHAR fontStyle[32];
    int fontSize;
    bool applyToGroupIndicator;
    int rowHeight;
    int rowWidth;
    bool stretchThumbnailsToTaskWidth;
    bool showThumbnails;
    bool showCloseButton;
    bool showOverflowIndicator;
    bool showTitle;
    bool showIcon;
    int maxWidthPercent;
    bool autoFitTasks;
    int maxHeightPercent; int showDelay;
    bool perMonitorWindows; bool taskRoundedCorners; bool roundThumbnailCorners; bool roundGroupIndicator; bool roundBadgeIconBackground; bool reverseScrollDirection;
    bool centerTaskContent;
    bool showApplications;
    WCHAR showTitles[32];
    bool restoreAllWindows;
    bool hideMinimizedWindows;
    bool sortMinimizedWindowsToEnd;
    int customCornerRadius;
    WCHAR switcherPosition[32];
    int switcherPositionMargin;
    bool showHoverBorder;
    bool showThumbnailShadow;
    // Badge layout (macOS-style)
    bool enableBadgeLayout;
    WCHAR badgeIconPosition[32];
    WCHAR badgeTitlePosition[16];
    bool showBadgeIconBackground; bool showBadgeIconBackgroundShadow;
    int badgeIconPadding;
    int badgeIconOffsetX;
    int badgeIconOffsetY;
    // Grouped indicator
    bool showGroupIndicator;
    bool showGroupIndicatorShadow;
    WCHAR groupCloseBehavior[16];
};

static std::vector<std::wstring> g_excludeTitlePatterns;
static std::vector<std::wstring> g_excludeExePatterns;
static std::vector<HWND> g_hMirrorSwitchers;

static HWND g_hSwitcher = NULL;
static HWND g_hCloseBtnWnd = NULL;
static IVirtualDesktopManager* g_pVirtualDesktopManager = NULL;
static bool g_showAllMonitors = false;
static HHOOK g_hMouseHook = NULL;
static std::vector<WindowEntry> g_windows;
static int g_selectedIndex = 0, g_hoverIndex = -1;
static bool g_isPaginatedView = false;
static bool g_isDryRunLayout = false;
static HWND g_hoverWnd = NULL;
static int g_layoutStartIndex = 0; // EP-style: first window index visible in the layout
// App drill-in: when grouping by application, Ctrl drills into the selected app's
// windows. The grouped app list is stashed here so it can be restored on exit.
static bool g_drilledIn = false;
static std::vector<WindowEntry> g_savedAppList;
static int g_savedSelectedIndex = 0;
static int g_savedLayoutStartIndex = 0;
static bool g_consumeEscUp = false;
static bool g_isVisible = false, g_isSticky = false, g_isDarkMode = false;
static HFONT g_hFont = NULL;
static HTHEME g_hTheme = NULL;
static UINT g_shellHookMsg = 0;
static int g_dpiX = 96, g_dpiY = 96;
// Auto-fit ("Shrink tasks to fit") scale percentage applied to row/thumbnail
// height and icon size. 100 = no shrink. Recomputed in ComputeLayout from the
// visible task count when the setting is enabled.
static int g_autoFitScalePct = 100;
static int g_winW = 0, g_winH = 0;
static int g_activePadDivider = 0;
static bool g_hotkeysRegistered = false;
static bool g_isAltBacktickSameApp = false;
static HMONITOR g_hCurrentMonitor = NULL;
static Settings g_settings;
static HANDLE g_hSwitcherThread = NULL;
static DWORD g_dwSwitcherThreadId = 0;
static bool g_isExplorer = false;
static HANDLE g_restartExplorerPromptThread = NULL;
static std::atomic<HWND> g_restartExplorerPromptWindow{nullptr};
static IsShellWindow_t g_IsShellManagedWindow = nullptr;
static IsShellWindow_t g_IsShellFrameWindow = nullptr;
static GhostWindowFromHungWindow_t g_GhostWindowFromHungWindow = nullptr;
static GhostWindowFromHungWindow_t g_HungWindowFromGhostWindow = nullptr;
static SetWindowCompositionAttribute_t g_SetWindowCompositionAttribute = nullptr;
static ULONG_PTR g_gdiplusToken = 0;
static bool g_isCloseHovered = false;
static HANDLE g_explorerIpcThread = NULL;
static DWORD g_explorerIpcThreadId = 0;
static bool g_isPendingShow = false;
static RECT g_pendingSwitcherRect = {0, 0, 0, 0};
static bool g_isWin11OrGreater = false;

// Forward declarations
static void LoadSettings();
static void SWS_RegisterHotkeys();
static void SWS_UnregisterHotkeys();
static void ApplySwitcherRegion();
static void CreateMirrorSwitchers();
static void HideSwitcher();

// Helpers

static bool ThemeIs(const WCHAR* v) { return wcscmp(g_settings.theme, v) == 0; }
static bool ScrollIs(const WCHAR* v) { return wcscmp(g_settings.scrollWheelBehavior, v) == 0; }
static bool LayoutIsVertical() { return wcscmp(g_settings.taskListOrientation, L"vertical") == 0; }
static bool HeaderOrientationIs(const WCHAR* v) { return wcscmp(g_settings.headerContentOrientation, v) == 0; }
static bool IconSizeIs(const WCHAR* v) { return wcscmp(g_settings.iconSize, v) == 0; }
static bool BackwardShortcutIs(const WCHAR* v) { return wcscmp(g_settings.backwardShortcut, v) == 0; }
static bool ThumbnailPositionIs(const WCHAR* v) { return wcscmp(g_settings.thumbnailPosition, v) == 0; }
static bool HighlightStyleIs(const WCHAR* v) {
    return wcscmp(g_settings.highlightStyle, v) == 0;
}
static bool UseAltShiftTabBackward() { return BackwardShortcutIs(L"altShiftTab"); }
static bool UseAltShiftBackward() { return BackwardShortcutIs(L"altShift"); }
static bool UseAltBacktickBackward() { return BackwardShortcutIs(L"altBacktick"); }
static bool ThumbnailIsBottom() { return ThumbnailPositionIs(L"bottom"); }
static bool ThumbnailIsTop() { return ThumbnailPositionIs(L"top"); }
static bool ThumbnailIsLeft() { return ThumbnailPositionIs(L"left"); }
static bool ThumbnailIsRight() { return ThumbnailPositionIs(L"right"); }
static bool ThumbnailIsSide() { return ThumbnailIsLeft() || ThumbnailIsRight(); }
static bool ThumbnailAlignmentIs(const WCHAR* v) { return wcscmp(g_settings.thumbnailAlignment, v) == 0; }
static bool ThumbnailAlignCentered() { return ThumbnailAlignmentIs(L"centered"); }
static bool ThumbnailAlignRight() { return ThumbnailAlignmentIs(L"right"); }
static bool HighlightHasFill() {
    return HighlightStyleIs(L"fillAndBorder") || HighlightStyleIs(L"fillOnly");
}
static bool HighlightHasBorder() {
    return HighlightStyleIs(L"border") || HighlightStyleIs(L"fillAndBorder");
}
static bool StretchThumbsToTaskWidth() {
    return g_settings.stretchThumbnailsToTaskWidth;
}
static bool HeaderIsVertical() {
    return HeaderOrientationIs(L"vertical");
}
static bool BadgeLayoutActive() {
    return g_settings.enableBadgeLayout && g_settings.showThumbnails;
}
static bool BadgeIconPositionIs(const WCHAR* v) { return wcscmp(g_settings.badgeIconPosition, v) == 0; }
static bool BadgeTitleIsTop() { return wcscmp(g_settings.badgeTitlePosition, L"top") == 0; }
static int GetHeaderIconSizeBase() {
    if (IconSizeIs(L"xlarge")) return 64;
    if (IconSizeIs(L"large")) return 48;
    if (IconSizeIs(L"medium")) return 32;
    return SWS_ICON_SIZE;
}
// Discrete shrink steps for the "Shrink tasks to fit" option, keyed off the
// number of visible tasks. Coarse but predictable; tune thresholds freely.
static int ComputeAutoFitScalePct(int taskCount) {
    if (!g_settings.autoFitTasks) return 100;
    if (taskCount <= 8)  return 100;
    if (taskCount <= 14) return 80;
    if (taskCount <= 22) return 65;
    if (taskCount <= 32) return 50;
    return 40;
}
// Apply the current auto-fit scale to a pixel value (no-op when not shrinking).
static int ScaleAutoFit(int px) {
    return g_autoFitScalePct == 100 ? px : px * g_autoFitScalePct / 100;
}
static int GetHeaderIconSizePx() {
    int px = MulDiv(GetHeaderIconSizeBase(), g_dpiX, 96);
    if (g_autoFitScalePct != 100) {
        px = ScaleAutoFit(px);
        int floorPx = MulDiv(SWS_ICON_SIZE, g_dpiX, 96);
        if (px < floorPx) px = floorPx;
    }
    return px;
}
static int GetHeaderTitleHeightPx() {
    return MulDiv(18, g_dpiY, 96);
}
static int GetHeaderRowHeightPx() {
    if (!g_settings.showTitle && !g_settings.showIcon) {
        return 0;
    }

    if (!HeaderIsVertical()) {
        int h = MulDiv(SWS_ROW_TITLE_HEIGHT, g_dpiY, 96);
        if (g_settings.showIcon && GetHeaderIconSizePx() > h) h = GetHeaderIconSizePx();
        return h;
    }

    int gap = MulDiv(4, g_dpiY, 96);
    int h = 0;
    if (g_settings.showIcon) h += GetHeaderIconSizePx();
    if (g_settings.showTitle) h += (h > 0 ? gap : 0) + GetHeaderTitleHeightPx();
    return h;
}
static INT GetCornerPref() {
    if (wcscmp(g_settings.cornerPreference, L"none") == 0) return 1;
    if (wcscmp(g_settings.cornerPreference, L"roundSmall") == 0) return 3;
    if (wcscmp(g_settings.cornerPreference, L"custom") == 0) return 1; // Don't let DWM round, we'll try to manual mask
    return 2; // Default to round
}

static bool UseTaskRoundedCorners() {
    return g_settings.taskRoundedCorners;
}

static int GetTaskUiCornerRadiusPx() {
    if (!UseTaskRoundedCorners()) {
        return 0;
    }
    if (wcscmp(g_settings.cornerPreference, L"custom") == 0) {
        return MulDiv(g_settings.customCornerRadius, g_dpiX, 96);
    }
    return MulDiv(4, g_dpiX, 96);
}

// Thumbnail corner rounding is controlled independently from the task border /
// close button rounding, but shares the same radius from Corner Preference.
static int GetThumbnailCornerRadiusPx() {
    if (!g_settings.roundThumbnailCorners) {
        return 0;
    }
    if (wcscmp(g_settings.cornerPreference, L"custom") == 0) {
        return MulDiv(g_settings.customCornerRadius, g_dpiX, 96);
    }
    return MulDiv(4, g_dpiX, 96);
}

static int GetGroupIndicatorCornerRadiusPx(int maxRadius) {
    if (!g_settings.roundGroupIndicator) {
        return 0;
    }
    int radius = 0;
    if (wcscmp(g_settings.cornerPreference, L"custom") == 0) {
        radius = MulDiv(g_settings.customCornerRadius, g_dpiX, 96);
    } else {
        radius = MulDiv(4, g_dpiX, 96);
    }
    return (radius > maxRadius) ? maxRadius : radius;
}

static int GetBadgeIconBackgroundCornerRadiusPx(int maxRadius) {
    if (!g_settings.roundBadgeIconBackground) {
        return 0;
    }
    int radius = 0;
    if (wcscmp(g_settings.cornerPreference, L"custom") == 0) {
        radius = MulDiv(g_settings.customCornerRadius, g_dpiX, 96);
    } else {
        radius = MulDiv(4, g_dpiX, 96);
    }
    return (radius > maxRadius) ? maxRadius : radius;
}

static void GetSwitcherPosition(const RECT& workArea, int* outX, int* outY) {
    int w = workArea.right - workArea.left;
    int h = workArea.bottom - workArea.top;
    int m = MulDiv(g_settings.switcherPositionMargin, g_dpiX, 96);
    if (wcscmp(g_settings.switcherPosition, L"topLeft") == 0) {
        *outX = workArea.left + m; *outY = workArea.top + m;
    } else if (wcscmp(g_settings.switcherPosition, L"topCenter") == 0) {
        *outX = workArea.left + (w - g_winW) / 2; *outY = workArea.top + m;
    } else if (wcscmp(g_settings.switcherPosition, L"topRight") == 0) {
        *outX = workArea.right - g_winW - m; *outY = workArea.top + m;
    } else if (wcscmp(g_settings.switcherPosition, L"centerLeft") == 0) {
        *outX = workArea.left + m; *outY = workArea.top + (h - g_winH) / 2;
    } else if (wcscmp(g_settings.switcherPosition, L"centerRight") == 0) {
        *outX = workArea.right - g_winW - m; *outY = workArea.top + (h - g_winH) / 2;
    } else if (wcscmp(g_settings.switcherPosition, L"bottomLeft") == 0) {
        *outX = workArea.left + m; *outY = workArea.bottom - g_winH - m;
    } else if (wcscmp(g_settings.switcherPosition, L"bottomCenter") == 0) {
        *outX = workArea.left + (w - g_winW) / 2; *outY = workArea.bottom - g_winH - m;
    } else if (wcscmp(g_settings.switcherPosition, L"bottomRight") == 0) {
        *outX = workArea.right - g_winW - m; *outY = workArea.bottom - g_winH - m;
    } else { // center
        *outX = workArea.left + (w - g_winW) / 2; *outY = workArea.top + (h - g_winH) / 2;
    }
}

static int GetCloseButtonCornerRadiusPx() {
    return GetTaskUiCornerRadiusPx();
}
static bool ShouldUseDarkMode() {
    if (wcscmp(g_settings.colorScheme, L"light") == 0) return false;
    if (wcscmp(g_settings.colorScheme, L"dark") == 0) return true;
    DWORD val = 0, sz = sizeof(val);
    if (RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"AppsUseLightTheme", RRF_RT_REG_DWORD, NULL, &val, &sz) == ERROR_SUCCESS) return val == 0;
    return true;
}
static COLORREF GetAccentColor() {
    DWORD col = 0, sz = sizeof(col);
    if (RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\DWM",
        L"AccentColor", RRF_RT_REG_DWORD, NULL, &col, &sz) == ERROR_SUCCESS) return col & 0x00FFFFFF;
    return RGB(0, 120, 215);
}

static bool ParseHexColor(const WCHAR* value, COLORREF* outColor) {
    if (!value) {
        return false;
    }

    const WCHAR* p = value;
    size_t len = wcslen(p);
    if (len == 7 && p[0] == L'#') {
        p++;
        len = 6;
    }

    if (len != 6) {
        return false;
    }

    unsigned int rgb = 0;
    if (swscanf_s(p, L"%06x", &rgb) != 1) {
        return false;
    }

    if (outColor) {
        *outColor = RGB((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
    }
    return true;
}

static bool ResolveAPIs() {
    HMODULE h = GetModuleHandleW(L"user32.dll");
    if (!h) return false;
    g_IsShellManagedWindow = (IsShellWindow_t)GetProcAddress(h, (LPCSTR)2574);
    g_IsShellFrameWindow = (IsShellWindow_t)GetProcAddress(h, (LPCSTR)2573);
    g_GhostWindowFromHungWindow = (GhostWindowFromHungWindow_t)GetProcAddress(h, "GhostWindowFromHungWindow");
    g_HungWindowFromGhostWindow = (GhostWindowFromHungWindow_t)GetProcAddress(h, "HungWindowFromGhostWindow");
    g_SetWindowCompositionAttribute = (SetWindowCompositionAttribute_t)GetProcAddress(h, "SetWindowCompositionAttribute");

    return true;
}

// Explorer restart prompt

constexpr WCHAR kRestartTitle[] = L"Simple Window Switcher - Windhawk";
constexpr WCHAR kRestartText[] = L"Explorer needs to be restarted for changes to take effect. Restart now?";

static HRESULT CALLBACK RestartPromptDialogCallback(HWND hwnd, UINT msg, WPARAM, LPARAM, LONG_PTR) {
    if (msg == TDN_CREATED) {
        g_restartExplorerPromptWindow = hwnd;
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    } else if (msg == TDN_DESTROYED) {
        g_restartExplorerPromptWindow = nullptr;
    }
    return S_OK;
}

static DWORD WINAPI RestartPromptThreadProc(LPVOID) {
    TASKDIALOGCONFIG tdc = {};
    tdc.cbSize = sizeof(tdc);
    tdc.dwFlags = TDF_ALLOW_DIALOG_CANCELLATION;
    tdc.dwCommonButtons = TDCBF_YES_BUTTON | TDCBF_NO_BUTTON;
    tdc.pszWindowTitle = kRestartTitle;
    tdc.pszMainIcon = TD_INFORMATION_ICON;
    tdc.pszContent = kRestartText;
    tdc.pfCallback = RestartPromptDialogCallback;

    int button;
    if (SUCCEEDED(TaskDialogIndirect(&tdc, &button, nullptr, nullptr)) && button == IDYES) {
        WCHAR cmd[] = L"cmd.exe /c \"timeout /t 1 /nobreak >nul & taskkill /F /IM explorer.exe & start explorer.exe\"";
        STARTUPINFO si = { .cb = sizeof(si) };
        PROCESS_INFORMATION pi = {};
        if (CreateProcess(nullptr, cmd, nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi)) {
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
        }
    }
    return 0;
}

static void PromptForExplorerRestart() {
    if (g_restartExplorerPromptThread) {
        if (WaitForSingleObject(g_restartExplorerPromptThread, 0) != WAIT_OBJECT_0) return;
        CloseHandle(g_restartExplorerPromptThread);
    }
    g_restartExplorerPromptThread = CreateThread(
        nullptr, 0, RestartPromptThreadProc, nullptr, 0, nullptr);
}


// Window Filtering (ported from SWS)

static bool TestExStyle(HWND h, DWORD s) { return (s & (DWORD)GetWindowLongPtrW(h, GWL_EXSTYLE)) == s; }
static bool IsOwnerToolWindow(HWND hwnd) {
    HWND cur = hwnd, own = GetWindow(hwnd, GW_OWNER);
    while (!TestExStyle(cur, WS_EX_APPWINDOW) && own) {
        HWND prev = cur; cur = own; own = GetWindow(own, GW_OWNER);
        if (TestExStyle(cur, WS_EX_TOOLWINDOW))
            return !TestExStyle(prev, WS_EX_CONTROLPARENT) || own != NULL;
    }
    return false;
}
static bool IsReallyVisible(HWND h) { RECT r; GetWindowRect(h, &r); return IsWindowVisible(h) && !IsRectEmpty(&r); }
static bool IsGhosted(HWND h) { return g_GhostWindowFromHungWindow && g_GhostWindowFromHungWindow(h) != NULL; }
static bool ShouldListInAltTab(HWND hwnd) {
    if (!IsWindow(hwnd)) return false;
    if (!IsReallyVisible(hwnd)) return false;
    if (IsGhosted(hwnd)) return false;

    DWORD ex = (DWORD)GetWindowLongPtrW(hwnd, GWL_EXSTYLE);

    // WS_EX_TOOLWINDOW always excludes from alt-tab, regardless of other flags
    if (ex & WS_EX_TOOLWINDOW) return false;

    // WS_EX_NOACTIVATE excludes unless WS_EX_APPWINDOW is also set
    if ((ex & WS_EX_NOACTIVATE) && !(ex & WS_EX_APPWINDOW)) return false;

    // Prefer the owner over the child popup/dialog, but only if the owner is actually listable —
    // otherwise both windows disappear from the switcher.
    HWND own = GetWindow(hwnd, GW_OWNER);
    if (!(ex & WS_EX_APPWINDOW) && IsWindow(own) && IsReallyVisible(own) &&
        !(GetWindowLongPtrW(own, GWL_EXSTYLE) & WS_EX_TOOLWINDOW) &&
        !IsOwnerToolWindow(own)) {
        return false;
    }

    // Check if an ancestor in the owner chain is a tool window
    if (IsOwnerToolWindow(hwnd)) return false;

    return true;
}
static bool IsAltTabWindow(HWND h) {
    if (!IsWindow(h)) return false;
    if (g_IsShellFrameWindow && g_IsShellFrameWindow(h) && !(g_GhostWindowFromHungWindow && g_GhostWindowFromHungWindow(h))) return true;
    if (g_IsShellManagedWindow && g_IsShellManagedWindow(h) && !GetPropW(h, L"Microsoft.Windows.ShellManagedWindowAsNormalWindow")) return false;
    if (GetPropW(h, L"valinet.ExplorerPatcher.ShellManagedWindow")) return false;
    return ShouldListInAltTab(h);
}


// Window Enumeration

static HICON TryGetUwpIconFromExplorer(HWND hWnd, int desiredSizePx);

// Cache of crisp icons extracted from exe files at a specific pixel size.
// Owned here (DestroyIcon at unload); keyed by "<exePath>_<sizePx>".
static std::map<std::wstring, HICON> g_exeIconCache;

// WM_GETICON returns a fixed (usually 32px) icon that looks blurry when scaled
// up to 48/64. PrivateExtractIconsW pulls the best-matching frame from the
// exe's icon resource at the exact requested size for a crisp result.
static HICON TryGetCrispExeIcon(HWND hWnd, int desiredSizePx) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (!pid) return NULL;
    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProc) return NULL;
    WCHAR exePath[MAX_PATH] = {0};
    DWORD size = MAX_PATH;
    BOOL ok = QueryFullProcessImageNameW(hProc, 0, exePath, &size);
    CloseHandle(hProc);
    if (!ok || !exePath[0]) return NULL;

    std::wstring key = std::wstring(exePath) + L"_" + std::to_wstring(desiredSizePx);
    auto it = g_exeIconCache.find(key);
    if (it != g_exeIconCache.end()) return it->second;

    HICON hIcon = NULL;
    if (PrivateExtractIconsW(exePath, 0, desiredSizePx, desiredSizePx,
                             &hIcon, NULL, 1, 0) == 1 && hIcon) {
        g_exeIconCache[key] = hIcon;
        return hIcon;
    }
    return NULL;
}

// === Custom per-process header (icon and/or application name) ===

struct CustomHeaderRule {
    std::wstring pattern;   // executable name pattern; wildcards * and ? supported
    std::wstring iconPath;  // .ico / .exe / .dll to extract the icon from (optional)
    std::wstring appName;   // custom display name overriding the detected one (optional)
};
static std::vector<CustomHeaderRule> g_customHeaderRules;
// Owned cache of icons loaded from custom paths; keyed by "<path>_<sizePx>".
static std::map<std::wstring, HICON> g_customIconCache;

static HICON LoadCustomIconFromPath(const std::wstring& path, int sizePx) {
    if (path.empty() || sizePx <= 0) return NULL;
    std::wstring key = path + L"_" + std::to_wstring(sizePx);
    auto it = g_customIconCache.find(key);
    if (it != g_customIconCache.end()) return it->second;
    HICON hIcon = NULL;
    if (PrivateExtractIconsW(path.c_str(), 0, sizePx, sizePx,
                             &hIcon, NULL, 1, 0) == 1 && hIcon) {
        g_customIconCache[key] = hIcon;
        return hIcon;
    }
    return NULL;
}

// If the window's executable name matches a user-defined rule, return its
// custom icon. The first matching rule wins; this overrides all other sources.
static HICON TryGetCustomIcon(HWND hWnd, int sizePx) {
    if (g_customHeaderRules.empty()) return NULL;
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (!pid) return NULL;
    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProc) return NULL;
    WCHAR exePath[MAX_PATH] = {0};
    DWORD size = MAX_PATH;
    BOOL ok = QueryFullProcessImageNameW(hProc, 0, exePath, &size);
    CloseHandle(hProc);
    if (!ok || !exePath[0]) return NULL;
    WCHAR* fileName = PathFindFileNameW(exePath);
    for (const auto& rule : g_customHeaderRules) {
        if (PathMatchSpecW(fileName, rule.pattern.c_str())) {
            HICON h = LoadCustomIconFromPath(rule.iconPath, sizePx);
            if (h) return h;
        }
    }
    return NULL;
}

// If the window's executable name matches a user-defined rule with a custom
// application name, copy it into `out` and return true. The first matching rule
// with a non-empty name wins.
static bool TryGetCustomAppName(HWND hWnd, WCHAR* out, size_t cch) {
    if (g_customHeaderRules.empty()) return false;
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (!pid) return false;
    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProc) return false;
    WCHAR exePath[MAX_PATH] = {0};
    DWORD size = MAX_PATH;
    BOOL ok = QueryFullProcessImageNameW(hProc, 0, exePath, &size);
    CloseHandle(hProc);
    if (!ok || !exePath[0]) return false;
    WCHAR* fileName = PathFindFileNameW(exePath);
    for (const auto& rule : g_customHeaderRules) {
        if (!rule.appName.empty() && PathMatchSpecW(fileName, rule.pattern.c_str())) {
            wcsncpy_s(out, cch, rule.appName.c_str(), _TRUNCATE);
            return true;
        }
    }
    return false;
}

static HICON LoadWindowIcon(HWND hWnd) {
    // User-assigned custom icon takes priority over everything else.
    HICON hIcon = TryGetCustomIcon(hWnd, GetHeaderIconSizePx());
    if (hIcon) return hIcon;
    if (g_IsShellFrameWindow && g_IsShellFrameWindow(hWnd)) {
        hIcon = TryGetUwpIconFromExplorer(hWnd, GetHeaderIconSizePx());
    }
    // A crisp exe icon extracted at the exact target size beats the WM_GETICON
    // result, which is a fixed ~32px frame: blurry when upscaled to 48/64 and
    // pixelated when downscaled to 16 (GDI does no smoothing in DrawIconEx).
    // PrivateExtractIconsW picks the best-matching frame at the requested size.
    if (!hIcon) {
        hIcon = TryGetCrispExeIcon(hWnd, GetHeaderIconSizePx());
    }
    if (!hIcon) SendMessageTimeoutW(hWnd, WM_GETICON, ICON_BIG, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 100, (DWORD_PTR*)&hIcon);
    if (!hIcon) SendMessageTimeoutW(hWnd, WM_GETICON, ICON_SMALL2, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 100, (DWORD_PTR*)&hIcon);
    if (!hIcon) SendMessageTimeoutW(hWnd, WM_GETICON, ICON_SMALL, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 100, (DWORD_PTR*)&hIcon);
    if (!hIcon) hIcon = (HICON)GetClassLongPtrW(hWnd, GCLP_HICON);
    if (!hIcon) hIcon = (HICON)GetClassLongPtrW(hWnd, GCLP_HICONSM);
    if (!hIcon) hIcon = LoadIconW(NULL, IDI_APPLICATION);
    return hIcon;
}

static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
    auto* list = reinterpret_cast<std::vector<WindowEntry>*>(lParam);
    if (hWnd == g_hSwitcher) return TRUE;
    if (!IsAltTabWindow(hWnd)) return TRUE;
    BOOL cloaked = FALSE;
    DwmGetWindowAttribute(hWnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));
    if (cloaked) {
        if (wcscmp(g_settings.virtualDesktopBehavior, L"allDesktops") == 0 && g_pVirtualDesktopManager) {
            BOOL onCurrent = FALSE;
            if (SUCCEEDED(g_pVirtualDesktopManager->IsWindowOnCurrentVirtualDesktop(hWnd, &onCurrent)) && !onCurrent) {
                // allow cloaked window since it's just on another virtual desktop
            } else return TRUE;
        } else return TRUE;
    }
    bool isPrimaryOnly = (wcscmp(g_settings.switcherDisplayBehavior, L"primaryOnly") == 0);
    if (g_settings.perMonitorWindows && !g_showAllMonitors && g_hCurrentMonitor && !isPrimaryOnly) {
        if (MonitorFromWindow(hWnd, MONITOR_DEFAULTTONULL) != g_hCurrentMonitor) return TRUE;
    }
    WindowEntry e = {};
    e.hWnd = hWnd;
    GetWindowTextW(hWnd, e.title, 256);
    if (!e.title[0]) InternalGetWindowText(hWnd, e.title, 256);

    bool excluded = false;
    for (const auto& pat : g_excludeTitlePatterns) {
        if (PathMatchSpecW(e.title, pat.c_str())) { excluded = true; break; }
    }
    if (!excluded && !g_excludeExePatterns.empty()) {
        DWORD pid = 0;
        GetWindowThreadProcessId(hWnd, &pid);
        if (pid) {
            HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
            if (hProc) {
                WCHAR exePath[MAX_PATH] = {0};
                DWORD size = MAX_PATH;
                if (QueryFullProcessImageNameW(hProc, 0, exePath, &size)) {
                    WCHAR* filename = PathFindFileNameW(exePath);
                    for (const auto& pat : g_excludeExePatterns) {
                        if (PathMatchSpecW(filename, pat.c_str())) { excluded = true; break; }
                    }
                }
                CloseHandle(hProc);
            }
        }
    }
    if (excluded) return TRUE;

    e.hIcon = LoadWindowIcon(hWnd);
    list->push_back(e);
    return TRUE;
}

// === UWP Icon Extraction (Explorer IPC) ===

UINT g_WM_SWS_GET_UWP_ICON = 0;
std::map<std::wstring, HICON> g_uwpIconCache;

struct FindCoreWindowData { HWND coreHwnd; };

static BOOL CALLBACK FindCoreWindowProc(HWND hChild, LPARAM lParam) {
    auto* data = (FindCoreWindowData*)lParam;
    WCHAR cls[256];
    GetClassNameW(hChild, cls, 256);
    if (wcscmp(cls, L"Windows.UI.Core.CoreWindow") == 0) {
        data->coreHwnd = hChild;
        Wh_Log(L"Explorer IPC: Found CoreWindow %p for UWP app", hChild);
        return FALSE;
    }
    return TRUE;
}

static HICON ResolveIconFromAumid(const WCHAR* aumid, int desiredSizePx) {
    HICON hIcon = NULL;
    Wh_Log(L"ResolveIconFromAumid: aumid=%s, desiredSizePx=%d", aumid, desiredSizePx);

    IShellItem* psi = NULL;
    HRESULT hr = SHCreateItemInKnownFolder(
            FOLDERID_AppsFolder, KF_FLAG_DONT_VERIFY,
            aumid, IID_PPV_ARGS(&psi));
    if (SUCCEEDED(hr) && psi) {
        Wh_Log(L"ResolveIconFromAumid: SHCreateItemInKnownFolder succeeded");
        IShellItemImageFactory* psiif = NULL;
        hr = psi->QueryInterface(IID_PPV_ARGS(&psiif));
        if (SUCCEEDED(hr) && psiif) {
            Wh_Log(L"ResolveIconFromAumid: QueryInterface(IShellItemImageFactory) succeeded");
            SIZE sz = { desiredSizePx, desiredSizePx };
            HBITMAP hBitmap = NULL;
            hr = psiif->GetImage(sz, SIIGBF_RESIZETOFIT | SIIGBF_ICONONLY, &hBitmap);
            if (SUCCEEDED(hr) && hBitmap) {
                Wh_Log(L"ResolveIconFromAumid: GetImage succeeded");
                HIMAGELIST hImageList = ImageList_Create(sz.cx, sz.cy, ILC_COLOR32, 1, 0);
                if (hImageList) {
                    if (ImageList_Add(hImageList, hBitmap, NULL) != -1) {
                        hIcon = ImageList_GetIcon(hImageList, 0, 0);
                        if (hIcon) Wh_Log(L"ResolveIconFromAumid: Successfully converted to HICON");
                        else Wh_Log(L"ResolveIconFromAumid: ImageList_GetIcon failed");
                    } else {
                        Wh_Log(L"ResolveIconFromAumid: ImageList_Add failed");
                    }
                    ImageList_Destroy(hImageList);
                } else {
                    Wh_Log(L"ResolveIconFromAumid: ImageList_Create failed");
                }
                DeleteObject(hBitmap);
            } else {
                Wh_Log(L"ResolveIconFromAumid: GetImage failed, hr=0x%08X", hr);
            }
            psiif->Release();
        } else {
            Wh_Log(L"ResolveIconFromAumid: QueryInterface failed, hr=0x%08X", hr);
        }
        psi->Release();
    } else {
        Wh_Log(L"ResolveIconFromAumid: SHCreateItemInKnownFolder failed, hr=0x%08X", hr);
    }

    // Fallback: SHParseDisplayName + SHGetFileInfo
    if (!hIcon) {
        Wh_Log(L"ResolveIconFromAumid: Falling back to SHParseDisplayName");
        WCHAR appsFolderPath[768];
        if (swprintf_s(appsFolderPath, L"shell:AppsFolder\\%s", aumid) > 0) {
            PIDLIST_ABSOLUTE pidl = NULL;
            hr = SHParseDisplayName(appsFolderPath, NULL, &pidl, 0, NULL);
            if (SUCCEEDED(hr) && pidl) {
                Wh_Log(L"ResolveIconFromAumid: SHParseDisplayName succeeded");
                SHFILEINFOW sfi = {};
                UINT flags = SHGFI_PIDL | SHGFI_ICON | (desiredSizePx > 24 ? SHGFI_LARGEICON : SHGFI_SMALLICON);
                if (SHGetFileInfoW((LPCWSTR)pidl, 0, &sfi, sizeof(sfi), flags)) {
                    hIcon = sfi.hIcon;
                    if (hIcon) Wh_Log(L"ResolveIconFromAumid: SHGetFileInfoW succeeded");
                    else Wh_Log(L"ResolveIconFromAumid: SHGetFileInfoW returned no icon");
                } else {
                    Wh_Log(L"ResolveIconFromAumid: SHGetFileInfoW failed");
                }
                CoTaskMemFree(pidl);
            } else {
                Wh_Log(L"ResolveIconFromAumid: SHParseDisplayName failed, hr=0x%08X", hr);
            }
        }
    }

    return hIcon;
}

LRESULT CALLBACK ExplorerIpcWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (g_WM_SWS_GET_UWP_ICON && uMsg == g_WM_SWS_GET_UWP_ICON) {
        HWND hWndTarget = (HWND)wParam;
        int desiredSizePx = (int)lParam;

        Wh_Log(L"Explorer IPC: Received icon request for HWND %p, size %d", hWndTarget, desiredSizePx);

        std::wstring aumid;

        {
            IPropertyStore* ps = NULL;
            if (SUCCEEDED(SHGetPropertyStoreForWindow(hWndTarget, IID_PPV_ARGS(&ps))) && ps) {
                PROPVARIANT pv;
                PropVariantInit(&pv);
                if (SUCCEEDED(ps->GetValue(PKEY_AppUserModel_ID, &pv)) && pv.vt == VT_LPWSTR && pv.pwszVal && pv.pwszVal[0]) {
                    aumid = pv.pwszVal;
                    Wh_Log(L"Explorer IPC: Got AUMID from PropertyStore = %s", aumid.c_str());
                }
                PropVariantClear(&pv);
                ps->Release();
            }
        }

        if (aumid.empty()) {
            Wh_Log(L"Explorer IPC: PropertyStore failed or empty, trying Process Handle fallback");
            FindCoreWindowData data = {0};
            EnumChildWindows(hWndTarget, FindCoreWindowProc, (LPARAM)&data);
            HWND hCore = data.coreHwnd ? data.coreHwnd : hWndTarget;

            DWORD pid = 0;
            GetWindowThreadProcessId(hCore, &pid);

            if (pid) {
                HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
                if (hProc) {
                    UINT32 aumidLen = 0;
                    LONG rc = GetApplicationUserModelId(hProc, &aumidLen, NULL);
                    if (rc == ERROR_INSUFFICIENT_BUFFER && aumidLen > 0) {
                        WCHAR* buf = new WCHAR[aumidLen];
                        if (GetApplicationUserModelId(hProc, &aumidLen, buf) == ERROR_SUCCESS) {
                            aumid = buf;
                            Wh_Log(L"Explorer IPC: Got AUMID from Process = %s", aumid.c_str());
                        }
                        delete[] buf;
                    } else {
                        Wh_Log(L"Explorer IPC: GetApplicationUserModelId failed, rc=%d", rc);
                    }
                    CloseHandle(hProc);
                } else {
                    Wh_Log(L"Explorer IPC: OpenProcess failed, err=%u", GetLastError());
                }
            }
            // If still no AUMID (common on Win10), try to get the process executable and return its icon
            if (aumid.empty() && pid) {
                // First try window/class icons via WM_GETICON / GetClassLongPtr — sometimes available on Win10
                HICON hWinIcon = NULL;
                DWORD_PTR iconRes = 0;
                if (!hWinIcon && SendMessageTimeoutW(hCore, WM_GETICON, ICON_BIG, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 500, &iconRes) && iconRes)
                    hWinIcon = (HICON)iconRes;
                if (!hWinIcon && SendMessageTimeoutW(hCore, WM_GETICON, ICON_SMALL, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 500, &iconRes) && iconRes)
                    hWinIcon = (HICON)iconRes;
                if (!hWinIcon && SendMessageTimeoutW(hCore, WM_GETICON, ICON_SMALL2, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 500, &iconRes) && iconRes)
                    hWinIcon = (HICON)iconRes;
                if (!hWinIcon) {
                    HICON hClassIcon = (HICON)GetClassLongPtrW(hCore, GCLP_HICON);
                    if (!hClassIcon) hClassIcon = (HICON)GetClassLongPtrW(hCore, GCLP_HICONSM);
                    if (hClassIcon) hWinIcon = hClassIcon;
                }
                if (hWinIcon) {
                    Wh_Log(L"Explorer IPC: Returning WM_GETICON/GetClassLongPtr icon %p as Win10 fallback", hWinIcon);
                    return (LRESULT)hWinIcon;
                }

                WCHAR exePath[MAX_PATH] = {0};
                HANDLE hProc2 = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, FALSE, pid);
                if (hProc2) {
                    DWORD size = MAX_PATH;
                    if (QueryFullProcessImageNameW(hProc2, 0, exePath, &size)) {
                        Wh_Log(L"Explorer IPC: Fallback exe path = %s", exePath);
                        SHFILEINFOW sfi = {};
                        UINT flags = SHGFI_ICON | SHGFI_USEFILEATTRIBUTES | (desiredSizePx > 24 ? SHGFI_LARGEICON : SHGFI_SMALLICON);
                        if (SHGetFileInfoW(exePath, FILE_ATTRIBUTE_NORMAL, &sfi, sizeof(sfi), flags)) {
                            if (sfi.hIcon) {
                                Wh_Log(L"Explorer IPC: Returning exe icon %p as Win10 fallback", sfi.hIcon);
                                g_uwpIconCache[std::wstring(exePath) + L"_" + std::to_wstring(desiredSizePx)] = sfi.hIcon;
                                CloseHandle(hProc2);
                                return (LRESULT)sfi.hIcon;
                            }
                        }
                    } else {
                        Wh_Log(L"Explorer IPC: QueryFullProcessImageNameW failed, err=%u", GetLastError());
                    }
                    CloseHandle(hProc2);
                }
            }
        }

        if (!aumid.empty()) {
            Wh_Log(L"Explorer IPC: Got AUMID = %s", aumid.c_str());

            std::wstring cacheKey = aumid + L"_" + std::to_wstring(desiredSizePx);
            if (g_uwpIconCache.find(cacheKey) != g_uwpIconCache.end()) {
                Wh_Log(L"Explorer IPC: Returning cached icon %p", g_uwpIconCache[cacheKey]);
                return (LRESULT)g_uwpIconCache[cacheKey];
            }

            HICON hIcon = ResolveIconFromAumid(aumid.c_str(), desiredSizePx);
            if (hIcon) {
                Wh_Log(L"Explorer IPC: Resolved new icon %p", hIcon);
                g_uwpIconCache[cacheKey] = hIcon;
                return (LRESULT)hIcon;
            } else {
                Wh_Log(L"Explorer IPC: ResolveIconFromAumid failed");
            }
        } else {
            Wh_Log(L"Explorer IPC: Failed to obtain AUMID for UWP app");
        }
        return NULL;
    }
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

static DWORD WINAPI ExplorerIpcThread(LPVOID) {
    HRESULT hrCo = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    WNDCLASSW wc = {0};
    wc.lpfnWndProc = ExplorerIpcWndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"WindhawkSWS_IpcWindow";
    RegisterClassW(&wc);

    HWND hIpcWnd = CreateWindowExW(0, L"WindhawkSWS_IpcWindow", L"", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, wc.hInstance, NULL);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    if (hIpcWnd) DestroyWindow(hIpcWnd);
    UnregisterClassW(L"WindhawkSWS_IpcWindow", wc.hInstance);

    if (SUCCEEDED(hrCo)) CoUninitialize();
    return 0;
}

static HICON TryGetUwpIconFromExplorer(HWND hWnd, int desiredSizePx) {
    if (!g_WM_SWS_GET_UWP_ICON) {
        g_WM_SWS_GET_UWP_ICON = RegisterWindowMessageW(L"Windhawk_SWS_GetUwpIcon");
        Wh_Log(L"TryGetUwpIconFromExplorer: Registered message %u", g_WM_SWS_GET_UWP_ICON);
    }
    HWND hIpc = FindWindowW(L"WindhawkSWS_IpcWindow", NULL);
    if (hIpc) {
        DWORD_PTR res = 0;
        LRESULT sendRes = SendMessageTimeoutW(hIpc, g_WM_SWS_GET_UWP_ICON, (WPARAM)hWnd, desiredSizePx, SMTO_ABORTIFHUNG | SMTO_BLOCK, 1000, &res);
        Wh_Log(L"TryGetUwpIconFromExplorer: SendMessageTimeoutW to %p returned %ld, res = %p", hIpc, sendRes, res);
        if (res) {
            // On Windows 11 explorer returns usable icon handles via IPC in our environment.
            // Avoid attempting local AUMID->icon resolution on Win11 to preserve that behavior.
            if (g_isWin11OrGreater) {
                return (HICON)res;
            }
            // We got an icon handle from Explorer, but HICON handles are process-local —
            // prefer resolving the AUMID locally and creating an icon in this process.
            // Try to get the AUMID locally using SHGetPropertyStoreForWindow; if available,
            // create a local icon via ResolveIconFromAumid and return it.
            std::wstring aumidLocal;
            IPropertyStore* ps = NULL;
            if (SUCCEEDED(SHGetPropertyStoreForWindow(hWnd, IID_PPV_ARGS(&ps))) && ps) {
                PROPVARIANT pv; PropVariantInit(&pv);
                if (SUCCEEDED(ps->GetValue(PKEY_AppUserModel_ID, &pv)) && pv.vt == VT_LPWSTR && pv.pwszVal && pv.pwszVal[0]) {
                    aumidLocal = pv.pwszVal;
                    Wh_Log(L"TryGetUwpIconFromExplorer: Got AUMID locally = %s", aumidLocal.c_str());
                }
                PropVariantClear(&pv);
                ps->Release();
            }
            if (!aumidLocal.empty()) {
                std::wstring cacheKey = aumidLocal + L"_" + std::to_wstring(desiredSizePx);
                auto it = g_uwpIconCache.find(cacheKey);
                if (it != g_uwpIconCache.end()) return it->second;
                HICON hLocal = ResolveIconFromAumid(aumidLocal.c_str(), desiredSizePx);
                if (hLocal) {
                    g_uwpIconCache[cacheKey] = hLocal;
                    Wh_Log(L"TryGetUwpIconFromExplorer: Resolved local icon %p from AUMID", hLocal);
                    return hLocal;
                }
                Wh_Log(L"TryGetUwpIconFromExplorer: Local ResolveIconFromAumid failed for %s", aumidLocal.c_str());
            }
            // As a last resort, return the handle from explorer (may not be valid across processes)
            return (HICON)res;
        }
        return NULL;
    } else {
        Wh_Log(L"TryGetUwpIconFromExplorer: WindhawkSWS_IpcWindow not found");
    }
    return NULL;
}

// Identity key used to group windows by application. UWP/app-frame-host windows
// all share a single host process, so keying them by executable would merge
// unrelated apps; those are keyed per-window to avoid over-grouping.
static void GetWindowGroupKey(HWND hWnd, WCHAR* out, size_t cch) {
    out[0] = 0;
    if (g_IsShellFrameWindow && g_IsShellFrameWindow(hWnd)) {
        swprintf_s(out, cch, L"hwnd:%p", (void*)hWnd);
        return;
    }
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid) {
        HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
        if (hProc) {
            WCHAR exePath[MAX_PATH] = {0};
            DWORD size = MAX_PATH;
            if (QueryFullProcessImageNameW(hProc, 0, exePath, &size)) {
                wcsncpy_s(out, cch, exePath, _TRUNCATE);
            }
            CloseHandle(hProc);
        }
    }
    if (!out[0]) swprintf_s(out, cch, L"hwnd:%p", (void*)hWnd);
}

// Human-readable application name for a window, taken from the executable's
// FileDescription version-info field (e.g. "Google Chrome"), falling back to
// the executable file name without extension.
static void GetAppName(HWND hWnd, WCHAR* out, size_t cch) {
    out[0] = 0;
    if (TryGetCustomAppName(hWnd, out, cch)) return;
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (!pid) return;
    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!hProc) return;
    WCHAR exePath[MAX_PATH] = {0};
    DWORD size = MAX_PATH;
    bool gotPath = QueryFullProcessImageNameW(hProc, 0, exePath, &size);
    CloseHandle(hProc);
    if (!gotPath) return;

    DWORD handle = 0;
    DWORD verSize = GetFileVersionInfoSizeW(exePath, &handle);
    if (verSize) {
        std::vector<BYTE> buf(verSize);
        if (GetFileVersionInfoW(exePath, handle, verSize, buf.data())) {
            struct LangAndCodePage { WORD wLanguage; WORD wCodePage; } *translate = nullptr;
            UINT cbTranslate = 0;
            if (VerQueryValueW(buf.data(), L"\\VarFileInfo\\Translation",
                               (LPVOID*)&translate, &cbTranslate) &&
                cbTranslate >= sizeof(LangAndCodePage)) {
                WCHAR subBlock[64];
                swprintf_s(subBlock, ARRAYSIZE(subBlock),
                           L"\\StringFileInfo\\%04x%04x\\FileDescription",
                           translate[0].wLanguage, translate[0].wCodePage);
                LPWSTR desc = nullptr;
                UINT descLen = 0;
                if (VerQueryValueW(buf.data(), subBlock, (LPVOID*)&desc, &descLen) &&
                    desc && desc[0]) {
                    wcsncpy_s(out, cch, desc, _TRUNCATE);
                }
            }
        }
    }
    if (!out[0]) {
        wcsncpy_s(out, cch, PathFindFileNameW(exePath), _TRUNCATE);
        PathRemoveExtensionW(out);
    }
}

static void BuildWindowList() {
    for (auto& w : g_windows) {
        for (const auto& kv : w.hThumbs) { if (kv.second) DwmUnregisterThumbnail(kv.second); }
        w.hThumbs.clear();
    }
    g_windows.clear();
    EnumWindows(EnumWindowsProc, (LPARAM)&g_windows);
    // App grouping: keep one entry per application. EnumWindows yields windows in
    // Z-order (top to bottom), so the first window seen for each app is its most
    // recently used one, which becomes the representative entry.
    if (g_settings.showApplications) {
        std::vector<WindowEntry> grouped;
        grouped.reserve(g_windows.size());
        std::vector<std::wstring> seenKeys;  // parallel to grouped
        for (auto& w : g_windows) {
            WCHAR key[MAX_PATH];
            GetWindowGroupKey(w.hWnd, key, ARRAYSIZE(key));
            int found = -1;
            for (size_t i = 0; i < seenKeys.size(); i++) {
                if (seenKeys[i] == key) { found = (int)i; break; }
            }
            if (found >= 0) {
                grouped[found].groupWindows.push_back(w.hWnd);
                continue;
            }
            seenKeys.emplace_back(key);
            w.groupWindows.assign(1, w.hWnd);
            grouped.push_back(std::move(w));
        }
        for (auto& e : grouped) {
            if (wcscmp(g_settings.showTitles, L"windowTitle") == 0) continue;
            WCHAR appName[256] = {0};
            GetAppName(e.hWnd, appName, ARRAYSIZE(appName));
            if (!appName[0]) continue;
            // UWP apps share the "Application Frame Host" executable, whose
            // FileDescription is useless as an app name; use the window title instead.
            if (_wcsicmp(appName, L"Application Frame Host") == 0 && e.title[0]) {
                wcscpy_s(appName, e.title);
            }
            if (wcscmp(g_settings.showTitles, L"appName") == 0) {
                wcscpy_s(e.title, appName);
            } else {  // appNameWindowTitle
                if (e.title[0]) {
                    WCHAR combined[256];
                    _snwprintf_s(combined, ARRAYSIZE(combined), _TRUNCATE,
                                 L"%s - %s", appName, e.title);
                    wcscpy_s(e.title, combined);
                } else {
                    wcscpy_s(e.title, appName);
                }
            }
        }
        g_windows = std::move(grouped);
    }
    // Optionally hide minimized windows. When grouping by application, an app
    // entry is only hidden if every one of its windows is minimized; apps with
    // at least one non-minimized window are kept.
    if (g_settings.hideMinimizedWindows) {
        g_windows.erase(std::remove_if(g_windows.begin(), g_windows.end(),
            [](const WindowEntry& w) {
                if (g_settings.showApplications) {
                    for (HWND hw : w.groupWindows) {
                        if (!IsIconic(hw)) return false;  // keep: has a visible window
                    }
                    return true;  // all windows minimized: hide
                }
                return IsIconic(w.hWnd) != FALSE;  // hide if minimized
            }), g_windows.end());
    }
    if (g_settings.sortMinimizedWindowsToEnd) {
        std::stable_sort(g_windows.begin(), g_windows.end(), [](const WindowEntry& a, const WindowEntry& b) {
            return IsIconic(a.hWnd) < IsIconic(b.hWnd);
        });
    }
}

// Layout + Thumbnails

static int DpiScale(int val, int dpi) { return MulDiv(val, dpi, 96); }

static HFONT CreateScaledFont(int dpiY) {
    NONCLIENTMETRICSW ncm = { sizeof(ncm) };
    HMODULE hUser32 = GetModuleHandleW(L"user32.dll");
    typedef BOOL(WINAPI* SPIFD)(UINT, UINT, PVOID, UINT, UINT);
    SPIFD sysParamInfoForDpi = hUser32 ? (SPIFD)GetProcAddress(hUser32, "SystemParametersInfoForDpi") : NULL;
    if (sysParamInfoForDpi) {
        sysParamInfoForDpi(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0, dpiY);
    } else {
        SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);
    }
    LOGFONTW lf = ncm.lfMessageFont;
    if (g_settings.fontFamily[0] != L'\0') {
        wcsncpy_s(lf.lfFaceName, g_settings.fontFamily, _TRUNCATE);
    }
    lf.lfHeight = -MulDiv(g_settings.fontSize, dpiY, 72);
    if (wcscmp(g_settings.fontStyle, L"light") == 0) {
        lf.lfWeight = FW_LIGHT;
    } else if (wcscmp(g_settings.fontStyle, L"semibold") == 0) {
        lf.lfWeight = FW_SEMIBOLD;
    } else if (wcscmp(g_settings.fontStyle, L"bold") == 0 || wcscmp(g_settings.fontStyle, L"boldItalic") == 0) {
        lf.lfWeight = FW_BOLD;
    } else {
        lf.lfWeight = FW_NORMAL;
    }
    lf.lfItalic = (wcscmp(g_settings.fontStyle, L"italic") == 0 || wcscmp(g_settings.fontStyle, L"boldItalic") == 0) ? TRUE : FALSE;
    lf.lfQuality = CLEARTYPE_QUALITY;
    return CreateFontIndirectW(&lf);
}

static void RegisterThumbnailsEarly() {
    if (!g_settings.showThumbnails || !g_hSwitcher) return;
    for (auto& w : g_windows) {
        if (!w.hThumbs.count(g_hSwitcher)) {
            HTHUMBNAIL hT = NULL;
            if (SUCCEEDED(DwmRegisterThumbnail(g_hSwitcher, w.hWnd, &hT))) {
                w.hThumbs[g_hSwitcher] = hT;
                SIZE src = {0}; DwmQueryThumbnailSourceSize(hT, &src);
                w.sourceSize = src;
            }
        }
        for (HWND m : g_hMirrorSwitchers) {
            if (!w.hThumbs.count(m)) {
                HTHUMBNAIL hT = NULL;
                if (SUCCEEDED(DwmRegisterThumbnail(m, w.hWnd, &hT))) w.hThumbs[m] = hT;
            }
        }
        SIZE src = w.sourceSize;

        // Compute invisible frame crop using DWMWA_EXTENDED_FRAME_BOUNDS.
        // This fixes thumbnail displacement for maximized windows where
        // the window extends beyond screen edges to hide the frame.
        // Only apply for actively maximized windows (not minimized).
        // Minimized windows use DWM's low-res cached thumbnail where
        // frame borders are negligible; cropping them causes aspect ratio
        // distortion that makes the thumbnail overflow its destination.
        // Non-maximized windows are natively handled by DWM.
        if (IsZoomed(w.hWnd) && !IsIconic(w.hWnd)) {
            RECT wr = {0}, efb = {0};
            GetWindowRect(w.hWnd, &wr);
            if (SUCCEEDED(DwmGetWindowAttribute(w.hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &efb, sizeof(efb)))) {
                int wrW = wr.right - wr.left, wrH = wr.bottom - wr.top;
                int efbW = efb.right - efb.left, efbH = efb.bottom - efb.top;
                if (wrW > 0 && wrH > 0 && efbW > 0 && efbH > 0 && src.cx > 0 && src.cy > 0) {
                    int ml = 0, mt = 0, mr = 0, mb = 0;
                    double diffEfb = ((double)src.cx / efbW) - ((double)src.cy / efbH);
                    if (diffEfb < 0) diffEfb = -diffEfb;
                    double diffWr = ((double)src.cx / wrW) - ((double)src.cy / wrH);
                    if (diffWr < 0) diffWr = -diffWr;

                    if (diffEfb >= diffWr) {
                        double sx = (double)src.cx / wrW;
                        double sy = (double)src.cy / wrH;
                        ml = (int)((efb.left - wr.left) * sx);
                        mt = (int)((efb.top - wr.top) * sy);
                        mr = (int)((wr.right - efb.right) * sx);
                        mb = (int)((wr.bottom - efb.bottom) * sy);
                    }
                    if (ml < 0) ml = 0; if (mt < 0) mt = 0;
                    if (mr < 0) mr = 0; if (mb < 0) mb = 0;
                    w.rcSourceCrop = { ml, mt, src.cx - mr, src.cy - mb };
                    w.effectiveSourceSize = { src.cx - ml - mr, src.cy - mt - mb };
                    if (w.effectiveSourceSize.cx <= 0 || w.effectiveSourceSize.cy <= 0) {
                        w.effectiveSourceSize = src;
                        w.rcSourceCrop = { 0, 0, src.cx, src.cy };
                    }
                } else {
                    w.effectiveSourceSize = src;
                    w.rcSourceCrop = { 0, 0, src.cx, src.cy };
                }
            } else {
                w.effectiveSourceSize = src;
                w.rcSourceCrop = { 0, 0, src.cx, src.cy };
            }
        } else {
            w.effectiveSourceSize = src;
            w.rcSourceCrop = { 0, 0, src.cx, src.cy };
        }
    }
}

static void ComputeLayout(HMONITOR hMon) {
    MONITORINFO mi = { sizeof(mi) }; GetMonitorInfoW(hMon, &mi);
    int monW = mi.rcWork.right - mi.rcWork.left, monH = mi.rcWork.bottom - mi.rcWork.top;
    UINT dpiX = 96, dpiY = 96;
    HMODULE hShcore = LoadLibraryW(L"shcore.dll");
    if (hShcore) {
        typedef HRESULT(WINAPI*GDPFM)(HMONITOR,int,UINT*,UINT*);
        auto fn = (GDPFM)GetProcAddress(hShcore, "GetDpiForMonitor");
        if (fn) fn(hMon, 0, &dpiX, &dpiY);
        FreeLibrary(hShcore);
    }
    g_dpiX = dpiX; g_dpiY = dpiY;

    int n = (int)g_windows.size();
    if (n == 0) { g_winW = 0; g_winH = 0; return; }

    // "Shrink tasks to fit": pick a discrete scale from the task count. Must be
    // set before any GetHeaderIconSizePx()/GetHeaderRowHeightPx() call below so
    // icon and row sizes pick it up.
    g_autoFitScalePct = ComputeAutoFitScalePct(n);

    // DPI-scale all EP padding constants
    int masterPad    = DpiScale(SWS_MASTER_PADDING, dpiX);
    int elemPadTop   = DpiScale(SWS_ELEMENT_PAD_TOP, dpiY);
    int elemPadBot   = DpiScale(SWS_ELEMENT_PAD_BOTTOM, dpiY);
    int elemPadLeft  = DpiScale(SWS_ELEMENT_PAD_LEFT, dpiX);
    int elemPadRight = DpiScale(SWS_ELEMENT_PAD_RIGHT, dpiX);
    int padTop       = DpiScale(SWS_PAD_TOP, dpiY);
    int padBot       = DpiScale(SWS_PAD_BOTTOM, dpiY);
    int padLeft      = DpiScale(SWS_PAD_LEFT, dpiX);
    int padRight     = DpiScale(SWS_PAD_RIGHT, dpiX);
    int padDivider   = DpiScale(SWS_PAD_DIVIDER, dpiY);
    int rowTitleH    = GetHeaderRowHeightPx();

    // Badge layout override: the icon overlays the thumbnail, so the header
    // row only needs to account for the title text, not the icon.  Also force
    // the thumbnail position so the title band sits above or below.
    if (BadgeLayoutActive()) {
        rowTitleH = g_settings.showTitle ? GetHeaderTitleHeightPx() : 0;
    }

    // EP: cbThumbnailAvailableHeight = cbRowHeight - cbRowTitleHeight - cbTopPadding - 2 * cbBottomPadding
    // All values are DPI-scaled at this point (matching EP lines 826-844)
    int scaledRowH = DpiScale(g_settings.rowHeight, dpiY);
    if (g_autoFitScalePct != 100) {
        scaledRowH = ScaleAutoFit(scaledRowH);
        int floorH = DpiScale(SWS_AUTOFIT_MIN_ROWHEIGHT, dpiY);
        if (scaledRowH < floorH) scaledRowH = floorH;
    }
    bool sidePlacement = ThumbnailIsSide() && g_settings.showThumbnails;
    if (BadgeLayoutActive()) sidePlacement = false;  // badge mode never uses side placement
    int thumbH = 0;
    if (g_settings.showThumbnails) {
        thumbH = scaledRowH - (sidePlacement ? 0 : rowTitleH) - padTop - 2 * padBot;
        if (thumbH < 0) thumbH = 0;
    }
    // EP: cbMaxTileWidth = cbRowHeight * MAX_TILE_WIDTH (computed before DPI, then scaled)
    int maxTileW = ScaleAutoFit(DpiScale((int)(g_settings.rowHeight * SWS_MAX_TILE_ASPECT), dpiX));

    // EP helper equivalents:
    // initialLeft  = elemPadLeft + padLeft
    // rightInc     = (padRight + elemPadRight) + initialLeft
    // initialTop   = elemPadTop + (padTop + rowTitleH + padDivider)
    // bottomInc    = (thumbH + padBot) + elemPadBot + initialTop
    int initialLeft = elemPadLeft + padLeft;
    int rightInc    = (padRight + elemPadRight) + initialLeft;
    bool showThumbs = g_settings.showThumbnails;
    bool thumbBottom = showThumbs ? ThumbnailIsBottom() : true;
    bool thumbTop = showThumbs ? ThumbnailIsTop() : false;
    bool thumbSide = showThumbs ? ThumbnailIsSide() : false;

    // Badge layout: override thumbnail position semantics.
    // "title on top" → title band above, thumbnail below → thumbBottom = true
    // "title on bottom" → title band below, thumbnail above → thumbTop = true
    int activePadDivider = (showThumbs && rowTitleH > 0) ? padDivider : 0;

    if (BadgeLayoutActive()) {
        thumbSide = false;
        thumbBottom = BadgeTitleIsTop();
        thumbTop = !BadgeTitleIsTop();

        // Calculate icon overlap due to offsets to dynamically resize borders & push title away
        bool isTop = BadgeIconPositionIs(L"topLeft") || BadgeIconPositionIs(L"topCenter") || BadgeIconPositionIs(L"topRight");
        bool isBottom = BadgeIconPositionIs(L"bottomLeft") || BadgeIconPositionIs(L"bottomCenter") || BadgeIconPositionIs(L"bottomRight");
        bool isLeft = BadgeIconPositionIs(L"topLeft") || BadgeIconPositionIs(L"centerLeft") || BadgeIconPositionIs(L"bottomLeft");
        bool isRight = BadgeIconPositionIs(L"topRight") || BadgeIconPositionIs(L"centerRight") || BadgeIconPositionIs(L"bottomRight");

        int shadowPad = g_settings.showBadgeIconBackgroundShadow ? DpiScale(6, dpiY) : 0;
        int shadowPadX = g_settings.showBadgeIconBackgroundShadow ? DpiScale(6, dpiX) : 0;

        int bIconOffY = DpiScale(g_settings.badgeIconOffsetY, dpiY) + shadowPad;
        int bIconOffX = DpiScale(g_settings.badgeIconOffsetX, dpiX) + shadowPadX;

        int bIconOffYNeg = DpiScale(g_settings.badgeIconOffsetY, dpiY) - shadowPad;
        int bIconOffXNeg = DpiScale(g_settings.badgeIconOffsetX, dpiX) - shadowPadX;

        int minGapY = DpiScale(8, dpiY);
        int minGapX = DpiScale(8, dpiX);

        if (bIconOffY > 0 && isBottom && thumbTop) {
            int extra = bIconOffY + minGapY - activePadDivider;
            if (extra > 0) activePadDivider += extra;
        } else if (bIconOffY > 0 && isBottom && !thumbTop) {
            int extra = bIconOffY + minGapY - padBot;
            if (extra > 0) padBot += extra;
        }

        if (bIconOffYNeg < 0 && isTop && thumbBottom) {
            int extra = abs(bIconOffYNeg) + minGapY - activePadDivider;
            if (extra > 0) activePadDivider += extra;
        } else if (bIconOffYNeg < 0 && isTop && !thumbBottom) {
            int extra = abs(bIconOffYNeg) + minGapY - padTop;
            if (extra > 0) padTop += extra;
        }

        if (bIconOffX > 0 && isRight) {
            int extra = bIconOffX + minGapX - padRight;
            if (extra > 0) padRight += extra;
        }
        if (bIconOffXNeg < 0 && isLeft) {
            int extra = abs(bIconOffXNeg) + minGapX - padLeft;
            if (extra > 0) padLeft += extra;
        }
    }

    g_activePadDivider = activePadDivider;

    int headerAndDividerH = rowTitleH + activePadDivider;
    int thumbTopOffset = padTop + (thumbBottom ? headerAndDividerH : 0);
    int initialTop  = elemPadTop + thumbTopOffset;
    int baseContentH = thumbSide ? std::max(thumbH, rowTitleH) : thumbH;
    int bottomInc   = (baseContentH + padBot) + elemPadBot + initialTop + (thumbTop ? headerAndDividerH : 0);
    int sideHeaderWidth = DpiScale(HeaderIsVertical() ? 96 : 150, dpiX);

    int maxW = monW * g_settings.maxWidthPercent / 100;
    int maxH = monH * g_settings.maxHeightPercent / 100;

    int sideThumbSlotW = 0;
    if (g_settings.showThumbnails && sidePlacement && thumbH > 0) {
        for (const auto& w : g_windows) {
            int slotW = thumbH;
            if (w.effectiveSourceSize.cx > 0 && w.effectiveSourceSize.cy > 0) {
                slotW = (int)((double)w.effectiveSourceSize.cx * thumbH / w.effectiveSourceSize.cy);
            }
            if (slotW > maxTileW) slotW = maxTileW;
            if (w.effectiveSourceSize.cx > 0 && slotW > w.effectiveSourceSize.cx) slotW = w.effectiveSourceSize.cx;
            if (slotW > sideThumbSlotW) sideThumbSlotW = slotW;
        }
        if (sideThumbSlotW <= 0) {
            sideThumbSlotW = DpiScale(16, dpiX);
        }
    }

    int curX = initialLeft + masterPad;
    int curY = initialTop + masterPad;
    int placedCount = n; // Track how many windows were actually placed

    auto truncateRemaining = [&](int startIdx) {
        for (int jj = startIdx; jj < n; jj++) {
            int ji = (g_layoutStartIndex + jj) % n;
            g_windows[ji].sourceSize = {0, 0};
            g_windows[ji].rcCell = {0, 0, 0, 0};
            g_windows[ji].rcThumbActual = {0, 0, 0, 0};
            g_windows[ji].rcThumbSlot = {0, 0, 0, 0};
            // During dry-run layout passes (e.g. CyclePage page-map discovery),
            // we do NOT destroy DWM thumbnail handles. Doing so on every scroll
            // event triggers rapid DwmUnregister/Register cycles that cause
            // visible flicker in the DWM compositor. The caller is responsible
            // for proper cleanup when g_isDryRunLayout is false.
            if (!g_isDryRunLayout) {
                for (const auto& kv : g_windows[ji].hThumbs) {
                    if (kv.second) DwmUnregisterThumbnail(kv.second);
                }
                g_windows[ji].hThumbs.clear();
            }
        }
        placedCount = startIdx;
    };

    if (!LayoutIsVertical()) {
        int maxRowW = 0;

        for (int idx = 0; idx < n; idx++) {
            int i = (g_layoutStartIndex + idx) % n;
            auto& w = g_windows[i];

            if (g_layoutStartIndex > 0 && idx > 0 && i < g_layoutStartIndex) {
                if (g_isPaginatedView) {
                    truncateRemaining(idx);
                    break;
                }
                if (((g_layoutStartIndex + idx - 1) % n) >= g_layoutStartIndex
                    && curX > initialLeft + masterPad) {
                    if (curX - initialLeft > maxRowW) maxRowW = curX - initialLeft;
                    curX = initialLeft + masterPad;
                    if (curY + 2 * bottomInc - initialTop > maxH - masterPad) {
                        truncateRemaining(idx);
                        break;
                    }
                    curY = curY + bottomInc;
                }
            }

            int width = 0;
            int thumbWidth = 0;
            int actualThumbH = thumbH;

            if (g_settings.showThumbnails && thumbH > 0) {
                if (w.effectiveSourceSize.cx > 0 && w.effectiveSourceSize.cy > 0) {
                    thumbWidth = (int)((double)w.effectiveSourceSize.cx * thumbH / w.effectiveSourceSize.cy);
                } else {
                    thumbWidth = thumbH;
                }

                int naturalThumbWidth = thumbWidth;
                if (thumbWidth > maxTileW) thumbWidth = maxTileW;
                if (w.effectiveSourceSize.cx > 0 && thumbWidth > w.effectiveSourceSize.cx) thumbWidth = w.effectiveSourceSize.cx;
                if (naturalThumbWidth > 0 && thumbWidth != naturalThumbWidth) {
                    actualThumbH = (int)((double)thumbWidth * thumbH / naturalThumbWidth);
                }

                width = thumbWidth;
                if (g_settings.rowWidth > 0) {
                    width = ScaleAutoFit(DpiScale(g_settings.rowWidth, dpiX));
                    if (StretchThumbsToTaskWidth() && !sidePlacement) {
                        thumbWidth = sidePlacement ? std::max(0, width - ((rowTitleH > 0) ? (sideHeaderWidth + padDivider) : 0)) : width;
                        if (thumbWidth <= 0) thumbWidth = DpiScale(16, dpiX);
                        actualThumbH = thumbH;
                    } else if (thumbWidth > width && width > 0) {
                        actualThumbH = (int)((double)width * actualThumbH / thumbWidth);
                        thumbWidth = width;
                    }
                }

                if (sidePlacement) {
                    int headerExtra = (rowTitleH > 0) ? (sideHeaderWidth + padDivider) : 0;
                    if (g_settings.rowWidth > 0) {
                        int maxThumbW = width - headerExtra;
                        if (maxThumbW > 0 && thumbWidth > maxThumbW) {
                            actualThumbH = (int)((double)maxThumbW * actualThumbH / thumbWidth);
                            thumbWidth = maxThumbW;
                        }
                    } else {
                        width = thumbWidth + headerExtra;
                    }
                }
            } else {
                if (!g_settings.showTitle && g_settings.showIcon) {
                    if (g_settings.centerTaskContent) {
                        width = GetHeaderIconSizePx() + DpiScale(16, dpiX); // Base padding
                    } else {
                        width = GetHeaderIconSizePx() + DpiScale(20, dpiX); // Icon + btnSz(16) + gap(4)
                    }
                } else {
                    width = DpiScale(160, dpiX);
                }
                thumbWidth = width;
                actualThumbH = 0;
            }

            if (!g_settings.showThumbnails && g_settings.rowWidth > 0) {
                width = ScaleAutoFit(DpiScale(g_settings.rowWidth, dpiX));
                thumbWidth = width;
            }

            if (curX + width + rightInc - initialLeft > maxW - masterPad && curX > initialLeft + masterPad) {
                if (curX - initialLeft > maxRowW) maxRowW = curX - initialLeft;
                curX = initialLeft + masterPad;

                if (curY + 2 * bottomInc - initialTop > maxH - masterPad) {
                    truncateRemaining(idx);
                    break;
                }

                curY = curY + bottomInc;
            }

            w.rcCell.left   = curX - initialLeft + elemPadLeft;
            w.rcCell.top    = curY - initialTop + elemPadTop;
            w.rcCell.right  = curX + width + rightInc - initialLeft - elemPadRight;
            w.rcCell.bottom = curY + bottomInc - initialTop - elemPadBot;
            if (g_settings.showThumbnails) {
                if (sidePlacement) {
                    int contentH = std::max(actualThumbH, rowTitleH);
                    int baseH = std::max(thumbH, rowTitleH);
                    if (contentH < baseH) {
                        w.rcCell.bottom -= (baseH - contentH);
                    }
                } else if (actualThumbH < thumbH) {
                    w.rcCell.bottom -= (thumbH - actualThumbH);
                }
            }

            if (g_settings.showThumbnails) {
                int thumbX = curX;
                int thumbY = curY;
                int slotX = curX;
                int slotW = width;
                if (sidePlacement) {
                    int contentH = std::max(actualThumbH, rowTitleH);
                    int headerExtra = (rowTitleH > 0) ? (sideHeaderWidth + padDivider) : 0;
                    int thumbAreaW = (g_settings.rowWidth > 0) ? sideThumbSlotW : std::max(0, width - headerExtra);
                    int thumbAreaStart = ThumbnailIsRight()
                        ? (curX + std::max(0, width - thumbAreaW))
                        : curX;
                    slotX = thumbAreaStart;
                    slotW = thumbAreaW;
                    thumbY = curY + (contentH - actualThumbH) / 2;
                    if (ThumbnailAlignRight()) {
                        thumbX = thumbAreaStart + std::max(0, thumbAreaW - thumbWidth);
                    } else if (ThumbnailAlignCentered()) {
                        thumbX = thumbAreaStart + std::max(0, (thumbAreaW - thumbWidth) / 2);
                    } else {
                        thumbX = thumbAreaStart;
                    }
                } else if (!StretchThumbsToTaskWidth() && width > thumbWidth) {
                    thumbX += (width - thumbWidth) / 2;
                }
                w.rcThumbActual = { thumbX, thumbY, thumbX + thumbWidth, thumbY + actualThumbH };
                w.rcThumbSlot = { slotX, thumbY, slotX + slotW, thumbY + actualThumbH };
            }

            curX = curX + width + rightInc;
            placedCount = idx + 1;
        }

        if (curX - initialLeft > maxRowW) maxRowW = curX - initialLeft;
        g_winW = maxRowW + masterPad;
        g_winH = curY + bottomInc - initialTop + masterPad;
        if (g_winW > maxW) g_winW = maxW;

        for (int idx = 0; idx < placedCount; idx++) {
            int i = (g_layoutStartIndex + idx) % n;
            int rowTop = g_windows[i].rcCell.top;
            int rowMaxRight = 0;
            for (int jdx = idx; jdx < placedCount; jdx++) {
                int j = (g_layoutStartIndex + jdx) % n;
                if (g_windows[j].rcCell.top != rowTop) break;
                if (g_windows[j].rcCell.right > rowMaxRight) rowMaxRight = g_windows[j].rcCell.right;
            }
            int diff = (g_winW - masterPad > rowMaxRight) ? (g_winW - masterPad - rowMaxRight) / 2 : 0;
            if (diff > 0) {
                for (int jdx = idx; jdx < placedCount; jdx++) {
                    int j = (g_layoutStartIndex + jdx) % n;
                    if (g_windows[j].rcCell.top != rowTop) break;
                    g_windows[j].rcCell.left += diff;
                    g_windows[j].rcCell.right += diff;
                    g_windows[j].rcThumbActual.left += diff;
                    g_windows[j].rcThumbActual.right += diff;
                    g_windows[j].rcThumbSlot.left += diff;
                    g_windows[j].rcThumbSlot.right += diff;
                }
            }
            while (idx + 1 < placedCount && g_windows[(g_layoutStartIndex + idx + 1) % n].rcCell.top == rowTop) idx++;
        }
    } else {
        int curColMaxW = 0;
        int maxRight = 0;
        int maxBottom = 0;

        for (int idx = 0; idx < n; idx++) {
            int i = (g_layoutStartIndex + idx) % n;
            auto& w = g_windows[i];

            if (g_layoutStartIndex > 0 && idx > 0 && i < g_layoutStartIndex) {
                if (g_isPaginatedView) {
                    truncateRemaining(idx);
                    break;
                }
                if (((g_layoutStartIndex + idx - 1) % n) >= g_layoutStartIndex
                    && curY > initialTop + masterPad) {
                    curY = initialTop + masterPad;
                    curX = curX + curColMaxW + rightInc;
                    curColMaxW = 0;
                    if (curX + rightInc - initialLeft > maxW - masterPad) {
                        truncateRemaining(idx);
                        break;
                    }
                }
            }

            int width = 0;
            int thumbWidth = 0;
            int actualThumbH = thumbH;

            if (g_settings.showThumbnails && thumbH > 0) {
                if (w.effectiveSourceSize.cx > 0 && w.effectiveSourceSize.cy > 0) {
                    thumbWidth = (int)((double)w.effectiveSourceSize.cx * thumbH / w.effectiveSourceSize.cy);
                } else {
                    thumbWidth = thumbH;
                }

                int naturalThumbWidth = thumbWidth;
                if (thumbWidth > maxTileW) thumbWidth = maxTileW;
                if (w.effectiveSourceSize.cx > 0 && thumbWidth > w.effectiveSourceSize.cx) thumbWidth = w.effectiveSourceSize.cx;
                if (naturalThumbWidth > 0 && thumbWidth != naturalThumbWidth) {
                    actualThumbH = (int)((double)thumbWidth * thumbH / naturalThumbWidth);
                }

                width = thumbWidth;
                if (g_settings.rowWidth > 0) {
                    width = ScaleAutoFit(DpiScale(g_settings.rowWidth, dpiX));
                    if (StretchThumbsToTaskWidth() && !sidePlacement) {
                        thumbWidth = sidePlacement ? std::max(0, width - ((rowTitleH > 0) ? (sideHeaderWidth + padDivider) : 0)) : width;
                        if (thumbWidth <= 0) thumbWidth = DpiScale(16, dpiX);
                        actualThumbH = thumbH;
                    } else if (thumbWidth > width && width > 0) {
                        actualThumbH = (int)((double)width * actualThumbH / thumbWidth);
                        thumbWidth = width;
                    }
                }

                if (sidePlacement) {
                    int headerExtra = (rowTitleH > 0) ? (sideHeaderWidth + padDivider) : 0;
                    if (g_settings.rowWidth > 0) {
                        int minWidth = sideThumbSlotW + headerExtra;
                        if (width < minWidth) width = minWidth;
                    } else {
                        width = sideThumbSlotW + headerExtra;
                    }
                }
            } else {
                if (!g_settings.showTitle && g_settings.showIcon) {
                    if (g_settings.centerTaskContent) {
                        width = GetHeaderIconSizePx() + DpiScale(16, dpiX); // Base padding
                    } else {
                        width = GetHeaderIconSizePx() + DpiScale(20, dpiX); // Icon + btnSz(16) + gap(4)
                    }
                } else {
                    width = DpiScale(160, dpiX);
                }
                thumbWidth = width;
                actualThumbH = 0;
            }

            if (!g_settings.showThumbnails && g_settings.rowWidth > 0) {
                width = ScaleAutoFit(DpiScale(g_settings.rowWidth, dpiX));
                thumbWidth = width;
            }

            if (curY + bottomInc - initialTop > maxH - masterPad && curY > initialTop + masterPad) {
                curY = initialTop + masterPad;
                curX = curX + curColMaxW + rightInc;
                curColMaxW = 0;
            }

            if (curX + width + rightInc - initialLeft > maxW - masterPad && idx > 0) {
                truncateRemaining(idx);
                break;
            }

            w.rcCell.left   = curX - initialLeft + elemPadLeft;
            w.rcCell.top    = curY - initialTop + elemPadTop;
            w.rcCell.right  = curX + width + rightInc - initialLeft - elemPadRight;
            w.rcCell.bottom = curY + bottomInc - initialTop - elemPadBot;
            if (g_settings.showThumbnails) {
                if (sidePlacement) {
                    int contentH = std::max(actualThumbH, rowTitleH);
                    int baseH = std::max(thumbH, rowTitleH);
                    if (contentH < baseH) {
                        w.rcCell.bottom -= (baseH - contentH);
                    }
                } else if (actualThumbH < thumbH) {
                    w.rcCell.bottom -= (thumbH - actualThumbH);
                }
            }

            if (g_settings.showThumbnails) {
                int thumbX = curX;
                int thumbY = curY;
                int slotX = curX;
                int slotW = width;
                if (sidePlacement) {
                    int contentH = std::max(actualThumbH, rowTitleH);
                    int headerExtra = (rowTitleH > 0) ? (sideHeaderWidth + padDivider) : 0;
                    int thumbAreaW = (g_settings.rowWidth > 0) ? sideThumbSlotW : std::max(0, width - headerExtra);
                    int thumbAreaStart = ThumbnailIsRight()
                        ? (curX + std::max(0, width - thumbAreaW))
                        : curX;
                    slotX = thumbAreaStart;
                    slotW = thumbAreaW;
                    thumbY = curY + (contentH - actualThumbH) / 2;
                    if (ThumbnailAlignRight()) {
                        thumbX = thumbAreaStart + std::max(0, thumbAreaW - thumbWidth);
                    } else if (ThumbnailAlignCentered()) {
                        thumbX = thumbAreaStart + std::max(0, (thumbAreaW - thumbWidth) / 2);
                    } else {
                        thumbX = thumbAreaStart;
                    }
                } else if (!StretchThumbsToTaskWidth() && width > thumbWidth) {
                    thumbX += (width - thumbWidth) / 2;
                }
                w.rcThumbActual = { thumbX, thumbY, thumbX + thumbWidth, thumbY + actualThumbH };
                w.rcThumbSlot = { slotX, thumbY, slotX + slotW, thumbY + actualThumbH };
            }

            if (width > curColMaxW) curColMaxW = width;
            if (w.rcCell.right > maxRight) maxRight = w.rcCell.right;
            if (w.rcCell.bottom > maxBottom) maxBottom = w.rcCell.bottom;

            curY = curY + bottomInc;
            placedCount = idx + 1;
        }

        g_winW = maxRight + masterPad;
        g_winH = maxBottom + masterPad;
        if (g_winW > maxW) g_winW = maxW;
        if (g_winH > maxH) g_winH = maxH;

        for (int idx = 0; idx < placedCount; idx++) {
            int i = (g_layoutStartIndex + idx) % n;
            int colLeft = g_windows[i].rcCell.left;
            int colMaxBottom = 0;

            for (int jdx = idx; jdx < placedCount; jdx++) {
                int j = (g_layoutStartIndex + jdx) % n;
                if (g_windows[j].rcCell.left != colLeft) break;
                if (g_windows[j].rcCell.bottom > colMaxBottom) colMaxBottom = g_windows[j].rcCell.bottom;
            }

            int diff = (g_winH - masterPad > colMaxBottom) ? (g_winH - masterPad - colMaxBottom) / 2 : 0;
            if (diff > 0) {
                for (int jdx = idx; jdx < placedCount; jdx++) {
                    int j = (g_layoutStartIndex + jdx) % n;
                    if (g_windows[j].rcCell.left != colLeft) break;
                    g_windows[j].rcCell.top += diff;
                    g_windows[j].rcCell.bottom += diff;
                    g_windows[j].rcThumbActual.top += diff;
                    g_windows[j].rcThumbActual.bottom += diff;
                    g_windows[j].rcThumbSlot.top += diff;
                    g_windows[j].rcThumbSlot.bottom += diff;
                }
            }

            while (idx + 1 < placedCount && g_windows[(g_layoutStartIndex + idx + 1) % n].rcCell.left == colLeft) idx++;
        }
    }
}

static void RegisterThumbnails() {
    if (!g_settings.showThumbnails || !g_hSwitcher) return;
    for (auto& w : g_windows) {
        if (!w.hThumbs.count(g_hSwitcher)) {
            HTHUMBNAIL hT = NULL;
            if (SUCCEEDED(DwmRegisterThumbnail(g_hSwitcher, w.hWnd, &hT))) {
                w.hThumbs[g_hSwitcher] = hT;
                SIZE src = {0}; DwmQueryThumbnailSourceSize(hT, &src);
                w.sourceSize = src;
            }
        }
        for (HWND m : g_hMirrorSwitchers) {
            if (!w.hThumbs.count(m)) {
                HTHUMBNAIL hT = NULL;
                if (SUCCEEDED(DwmRegisterThumbnail(m, w.hWnd, &hT))) w.hThumbs[m] = hT;
            }
        }

        for (const auto& kv : w.hThumbs) {
            HTHUMBNAIL hThumb = kv.second;
            if (!hThumb) continue;
            // Skip truncated windows with zero destination rect
            if (w.rcThumbActual.left == 0 && w.rcThumbActual.right == 0 &&
                w.rcThumbActual.top == 0 && w.rcThumbActual.bottom == 0) continue;
            DWM_THUMBNAIL_PROPERTIES p = {};
            p.dwFlags = DWM_TNP_SOURCECLIENTAREAONLY | DWM_TNP_RECTDESTINATION | DWM_TNP_VISIBLE | DWM_TNP_OPACITY;
            p.fSourceClientAreaOnly = FALSE;
            p.rcDestination = w.rcThumbActual;
            p.opacity = 255; p.fVisible = TRUE;
            // Only set DWM_TNP_RECTSOURCE when the crop is non-trivial (e.g. maximized
            // windows with invisible frame borders). Without it, DWM preserves the
            // window's visual style including rounded corners on Windows 11.
            bool needsCrop = (w.rcSourceCrop.left != 0 || w.rcSourceCrop.top != 0 ||
                              w.rcSourceCrop.right != w.sourceSize.cx || w.rcSourceCrop.bottom != w.sourceSize.cy);
            if (needsCrop) {
                p.dwFlags |= DWM_TNP_RECTSOURCE;
                p.rcSource = w.rcSourceCrop;
            }
            DwmUpdateThumbnailProperties(hThumb, &p);
        }
    }
}
static void UnregisterThumbnails() {
    for (auto& w : g_windows) {
        for (const auto& kv : w.hThumbs) {
            if (kv.second) DwmUnregisterThumbnail(kv.second);
        }
        w.hThumbs.clear();
    }
}


// Drawing Helpers

static COLORREF ResolveColor(const WCHAR* mode, const WCHAR* customHex, COLORREF defaultColor) {
    if (wcscmp(mode, L"accent") == 0) return GetAccentColor();
    if (wcscmp(mode, L"custom") == 0) {
        COLORREF parsed;
        if (ParseHexColor(customHex, &parsed)) return parsed;
    }
    return defaultColor;
}

static COLORREF GetContourColor() {
    if (g_isDarkMode) {
        return ResolveColor(g_settings.borderColorModeDark,
                            g_settings.customBorderColorDark,
                            SWS_CONTOUR_DARK);
    }
    return ResolveColor(g_settings.borderColorModeLight,
                        g_settings.customBorderColorLight,
                        SWS_CONTOUR_LIGHT);
}

static COLORREF GetHighlightFillColor() {
    if (g_isDarkMode) {
        return ResolveColor(g_settings.highlightFillColorModeDark,
                            g_settings.customHighlightFillColorDark,
                            SWS_CONTOUR_DARK);
    }
    return ResolveColor(g_settings.highlightFillColorModeLight,
                        g_settings.customHighlightFillColorLight,
                        SWS_CONTOUR_LIGHT);
}

static COLORREF GetBgColor() {
    if (g_isDarkMode) {
        return ResolveColor(g_settings.bgColorModeDark,
                            g_settings.customBgColorDark,
                            SWS_BG_DARK);
    }
    return ResolveColor(g_settings.bgColorModeLight,
                        g_settings.customBgColorLight,
                        SWS_BG_LIGHT);
}

static COLORREF GetIconBackgroundColor() {
    if (g_isDarkMode) {
        return ResolveColor(g_settings.iconBgColorModeDark,
                            g_settings.customIconBgColorDark,
                            RGB(0, 0, 0));
    }
    return ResolveColor(g_settings.iconBgColorModeLight,
                        g_settings.customIconBgColorLight,
                        RGB(255, 255, 255));
}

static COLORREF GetIndicatorBackgroundColor() {
    if (g_isDarkMode) {
        return ResolveColor(g_settings.indicatorBgColorModeDark,
                            g_settings.customIndicatorBgColorDark,
                            RGB(51, 51, 51)); // #333333
    }
    return ResolveColor(g_settings.indicatorBgColorModeLight,
                        g_settings.customIndicatorBgColorLight,
                        RGB(234, 234, 234)); // #EAEAEA
}

static COLORREF GetIndicatorTextColor() {
    if (g_isDarkMode) {
        return ResolveColor(g_settings.indicatorTextColorModeDark,
                            g_settings.customIndicatorTextColorDark,
                            RGB(255, 255, 255)); // #FFFFFF
    }
    return ResolveColor(g_settings.indicatorTextColorModeLight,
                        g_settings.customIndicatorTextColorLight,
                        RGB(0, 0, 0)); // #000000
}

static Gdiplus::Bitmap* CreateIconShadowBitmap(HICON hIcon, int width, int height, float shadowAlphaMult) {
    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* pBlackBits = nullptr;
    void* pWhiteBits = nullptr;
    HDC hdc = GetDC(NULL);
    HBITMAP hBmpBlack = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pBlackBits, NULL, 0);
    HBITMAP hBmpWhite = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pWhiteBits, NULL, 0);

    if (!hBmpBlack || !hBmpWhite) {
        if (hBmpBlack) DeleteObject(hBmpBlack);
        if (hBmpWhite) DeleteObject(hBmpWhite);
        ReleaseDC(NULL, hdc);
        return nullptr;
    }

    HDC hdcMem = CreateCompatibleDC(hdc);

    // Draw on black
    HBITMAP hOld = (HBITMAP)SelectObject(hdcMem, hBmpBlack);
    RECT rc = {0, 0, width, height};
    HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(hdcMem, &rc, blackBrush);
    DrawIconEx(hdcMem, 0, 0, hIcon, width, height, 0, NULL, DI_NORMAL);
    DeleteObject(blackBrush);

    // Draw on white
    SelectObject(hdcMem, hBmpWhite);
    HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(hdcMem, &rc, whiteBrush);
    DrawIconEx(hdcMem, 0, 0, hIcon, width, height, 0, NULL, DI_NORMAL);
    DeleteObject(whiteBrush);

    SelectObject(hdcMem, hOld);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdc);

    // Compute alpha and create shadow bitmap
    BYTE* shadowBits = new BYTE[width * height * 4];
    BYTE* blackPtr = (BYTE*)pBlackBits;
    BYTE* whitePtr = (BYTE*)pWhiteBits;

    for (int i = 0; i < width * height; ++i) {
        int idx = i * 4;
        int whiteB = whitePtr[idx];
        int blackB = blackPtr[idx];

        int a = 255 - (whiteB - blackB);
        if (a < 0) a = 0;
        if (a > 255) a = 255;

        int finalAlpha = (int)(a * shadowAlphaMult);
        if (finalAlpha > 255) finalAlpha = 255;

        shadowBits[idx] = 0;     // B
        shadowBits[idx+1] = 0;   // G
        shadowBits[idx+2] = 0;   // R
        shadowBits[idx+3] = (BYTE)finalAlpha; // A
    }

    Gdiplus::Bitmap* shadowBmp = new Gdiplus::Bitmap(width, height, width * 4, PixelFormat32bppARGB, shadowBits);
    Gdiplus::Bitmap* shadowBmpCopy = shadowBmp->Clone(0, 0, width, height, PixelFormat32bppARGB);
    delete shadowBmp;
    delete[] shadowBits;
    DeleteObject(hBmpBlack);
    DeleteObject(hBmpWhite);

    return shadowBmpCopy;
}

static void MaskRectCorners(HDC hdc, const RECT& rc, int radiusPx, bool forceOpaque = false, COLORREF overrideBg = CLR_INVALID) {
    if (radiusPx <= 0) {
        return;
    }

    int w = rc.right - rc.left;
    int h = rc.bottom - rc.top;
    if (w <= 0 || h <= 0) {
        return;
    }

    int r = radiusPx;
    if (r * 2 > w) r = w / 2;
    if (r * 2 > h) r = h / 2;
    if (r <= 0) {
        return;
    }

    COLORREF bg = (overrideBg != CLR_INVALID) ? overrideBg : GetBgColor();
    // In layered mode, punch fully transparent corners to force thumbnail clipping.
    BYTE alpha = (ThemeIs(L"none") && !forceOpaque) ? 0 : 255;

    Gdiplus::Graphics graphics(hdc);
    if (alpha == 0) {
        graphics.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
    }
    graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
    Gdiplus::SolidBrush brush(Gdiplus::Color(alpha, GetRValue(bg), GetGValue(bg), GetBValue(bg)));

    int d = r * 2;
    Gdiplus::GraphicsPath cutTl, cutTr, cutBr, cutBl;
    Gdiplus::REAL ext = (alpha != 0) ? 1.0f : 0.0f; // Extend outward to cover anti-aliased edge

    cutTl.StartFigure();
    cutTl.AddLine((Gdiplus::REAL)rc.left - ext, (Gdiplus::REAL)rc.top + r, (Gdiplus::REAL)rc.left - ext, (Gdiplus::REAL)rc.top - ext);
    cutTl.AddLine((Gdiplus::REAL)rc.left - ext, (Gdiplus::REAL)rc.top - ext, (Gdiplus::REAL)rc.left + r, (Gdiplus::REAL)rc.top - ext);
    cutTl.AddArc((Gdiplus::REAL)rc.left, (Gdiplus::REAL)rc.top, (Gdiplus::REAL)d, (Gdiplus::REAL)d, 270, -90);
    cutTl.CloseFigure();

    cutTr.StartFigure();
    cutTr.AddLine((Gdiplus::REAL)rc.right - r, (Gdiplus::REAL)rc.top - ext, (Gdiplus::REAL)rc.right + ext, (Gdiplus::REAL)rc.top - ext);
    cutTr.AddLine((Gdiplus::REAL)rc.right + ext, (Gdiplus::REAL)rc.top - ext, (Gdiplus::REAL)rc.right + ext, (Gdiplus::REAL)rc.top + r);
    cutTr.AddArc((Gdiplus::REAL)rc.right - d, (Gdiplus::REAL)rc.top, (Gdiplus::REAL)d, (Gdiplus::REAL)d, 0, -90);
    cutTr.CloseFigure();

    cutBr.StartFigure();
    cutBr.AddLine((Gdiplus::REAL)rc.right + ext, (Gdiplus::REAL)rc.bottom - r, (Gdiplus::REAL)rc.right + ext, (Gdiplus::REAL)rc.bottom + ext);
    cutBr.AddLine((Gdiplus::REAL)rc.right + ext, (Gdiplus::REAL)rc.bottom + ext, (Gdiplus::REAL)rc.right - r, (Gdiplus::REAL)rc.bottom + ext);
    cutBr.AddArc((Gdiplus::REAL)rc.right - d, (Gdiplus::REAL)rc.bottom - d, (Gdiplus::REAL)d, (Gdiplus::REAL)d, 90, -90);
    cutBr.CloseFigure();

    cutBl.StartFigure();
    cutBl.AddLine((Gdiplus::REAL)rc.left + r, (Gdiplus::REAL)rc.bottom + ext, (Gdiplus::REAL)rc.left - ext, (Gdiplus::REAL)rc.bottom + ext);
    cutBl.AddLine((Gdiplus::REAL)rc.left - ext, (Gdiplus::REAL)rc.bottom + ext, (Gdiplus::REAL)rc.left - ext, (Gdiplus::REAL)rc.bottom - r);
    cutBl.AddArc((Gdiplus::REAL)rc.left, (Gdiplus::REAL)rc.bottom - d, (Gdiplus::REAL)d, (Gdiplus::REAL)d, 180, -90);
    cutBl.CloseFigure();

    graphics.FillPath(&brush, &cutTl);
    graphics.FillPath(&brush, &cutTr);
    graphics.FillPath(&brush, &cutBr);
    graphics.FillPath(&brush, &cutBl);
}

// Draw a rectangular contour around a rect.
// direction: 1 = inner (shrinks inward), -1 = outer (grows outward)
// Uses GDI+ rounded path for contours when cornerRadius > 0.
static void DrawContour(HDC hdc, RECT rc, int contourSize, int direction, int overrideCornerRadius = -1) {
    COLORREF c = GetContourColor();
    BYTE r = GetRValue(c), g = GetGValue(c), b = GetBValue(c);

    int cornerRadius = (overrideCornerRadius != -1) ? overrideCornerRadius : GetTaskUiCornerRadiusPx();
    if (cornerRadius > 0) {
        int penWidth = contourSize * g_dpiX / 96;
        if (penWidth < 1) penWidth = 1;

        RECT drawRc = rc;
        if (direction < 0) {
            InflateRect(&drawRc, 2, 2);
            cornerRadius += 2 + penWidth / 2;
        }

        int width = drawRc.right - drawRc.left - penWidth;
        int height = drawRc.bottom - drawRc.top - penWidth;
        if (width <= 0 || height <= 0) {
            return;
        }

        if (cornerRadius * 2 > width) cornerRadius = width / 2;
        if (cornerRadius * 2 > height) cornerRadius = height / 2;

        Gdiplus::Graphics graphics(hdc);
        graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
        Gdiplus::Pen pen(Gdiplus::Color(255, r, g, b), (Gdiplus::REAL)penWidth);

        Gdiplus::REAL left = (Gdiplus::REAL)drawRc.left + penWidth / 2.0f;
        Gdiplus::REAL top = (Gdiplus::REAL)drawRc.top + penWidth / 2.0f;
        Gdiplus::REAL w = (Gdiplus::REAL)width;
        Gdiplus::REAL h = (Gdiplus::REAL)height;
        Gdiplus::REAL d = (Gdiplus::REAL)(cornerRadius * 2);
        Gdiplus::GraphicsPath path;
        path.AddArc(left, top, d, d, 180, 90);
        path.AddArc(left + w - d, top, d, d, 270, 90);
        path.AddArc(left + w - d, top + h - d, d, d, 0, 90);
        path.AddArc(left, top + h - d, d, d, 90, 90);
        path.CloseFigure();
        graphics.DrawPath(&pen, &path);
        return;
    }

    Gdiplus::Graphics graphics(hdc);
    graphics.SetSmoothingMode(Gdiplus::SmoothingModeNone);
    Gdiplus::SolidBrush solidBrush(Gdiplus::Color(255, r, g, b));

    if (direction < 0) {
        for (int i = 0; i < contourSize; i++) {
            RECT r_rect = rc;
            InflateRect(&r_rect, i + 2, i + 2);
            graphics.FillRectangle(&solidBrush, r_rect.left, r_rect.top, (r_rect.right - r_rect.left), 1);
            graphics.FillRectangle(&solidBrush, r_rect.left, r_rect.bottom - 1, (r_rect.right - r_rect.left), 1);
            graphics.FillRectangle(&solidBrush, r_rect.left, r_rect.top + 1, 1, (r_rect.bottom - r_rect.top) - 2);
            graphics.FillRectangle(&solidBrush, r_rect.right - 1, r_rect.top + 1, 1, (r_rect.bottom - r_rect.top) - 2);
        }
    } else {
        for (int i = 0; i < contourSize; i++) {
            RECT r_rect = rc;
            InflateRect(&r_rect, -i, -i);
            graphics.FillRectangle(&solidBrush, r_rect.left, r_rect.top, (r_rect.right - r_rect.left), 1);
            graphics.FillRectangle(&solidBrush, r_rect.left, r_rect.bottom - 1, (r_rect.right - r_rect.left), 1);
            graphics.FillRectangle(&solidBrush, r_rect.left, r_rect.top + 1, 1, (r_rect.bottom - r_rect.top) - 2);
            graphics.FillRectangle(&solidBrush, r_rect.right - 1, r_rect.top + 1, 1, (r_rect.bottom - r_rect.top) - 2);
        }
    }
}

static void DrawSelectionFill(HDC hdc, RECT rc) {
    RECT fillRc = rc;
    InflateRect(&fillRc, -1, -1);
    int width = fillRc.right - fillRc.left;
    int height = fillRc.bottom - fillRc.top;
    if (width <= 0 || height <= 0) {
        return;
    }

    COLORREF c = GetHighlightFillColor();
    BYTE r = GetRValue(c);
    BYTE g = GetGValue(c);
    BYTE b = GetBValue(c);

    int cornerRadius = GetTaskUiCornerRadiusPx();
    if (cornerRadius > 0) {
        int maxRadius = std::min(width, height) / 2;
        if (cornerRadius > maxRadius) cornerRadius = maxRadius;
    }

    Gdiplus::Graphics graphics(hdc);
    graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
    Gdiplus::SolidBrush brush(Gdiplus::Color(64, r, g, b));

    if (cornerRadius > 0) {
        Gdiplus::REAL left = (Gdiplus::REAL)fillRc.left;
        Gdiplus::REAL top = (Gdiplus::REAL)fillRc.top;
        Gdiplus::REAL w = (Gdiplus::REAL)(fillRc.right - fillRc.left);
        Gdiplus::REAL h = (Gdiplus::REAL)(fillRc.bottom - fillRc.top);
        Gdiplus::REAL d = (Gdiplus::REAL)(cornerRadius * 2);

        Gdiplus::GraphicsPath path;
        path.AddArc(left, top, d, d, 180, 90);
        path.AddArc(left + w - d, top, d, d, 270, 90);
        path.AddArc(left + w - d, top + h - d, d, d, 0, 90);
        path.AddArc(left, top + h - d, d, d, 90, 90);
        path.CloseFigure();
        graphics.FillPath(&brush, &path);
        return;
    }

    graphics.FillRectangle(&brush,
                           (Gdiplus::REAL)fillRc.left,
                           (Gdiplus::REAL)fillRc.top,
                           (Gdiplus::REAL)width,
                           (Gdiplus::REAL)height);
}

static RECT GetHeaderContentRectForEntry(const WindowEntry& e) {
    int padLeft = DpiScale(SWS_PAD_LEFT, g_dpiX);
    int padTop = DpiScale(SWS_PAD_TOP, g_dpiY);
    int padBottom = DpiScale(SWS_PAD_BOTTOM, g_dpiY);
    RECT rc = {
        e.rcCell.left + padLeft,
        e.rcCell.top + padTop,
        e.rcCell.right - padLeft,
        e.rcCell.bottom - padBottom,
    };

    if (!g_settings.showThumbnails) {
        return rc;
    }

    const RECT& rcHeaderSplit = ((e.rcThumbSlot.left != 0 || e.rcThumbSlot.top != 0 ||
                                  e.rcThumbSlot.right != 0 || e.rcThumbSlot.bottom != 0))
                                    ? e.rcThumbSlot
                                    : e.rcThumbActual;

    // In badge mode the title position is controlled by badgeTitlePosition, not thumbnailPosition.
    // "title on top" → thumb on bottom → header rect is above the thumb (ThumbnailIsBottom semantics)
    // "title on bottom" → thumb on top → header rect is below the thumb (ThumbnailIsTop semantics)
    bool effectiveThumbTop = BadgeLayoutActive() ? !BadgeTitleIsTop() : ThumbnailIsTop();
    bool effectiveThumbBottom = BadgeLayoutActive() ? BadgeTitleIsTop() : ThumbnailIsBottom();
    bool effectiveThumbSide = BadgeLayoutActive() ? false : ThumbnailIsSide();

    if (effectiveThumbTop) {
        rc.top = rcHeaderSplit.bottom + g_activePadDivider;
    } else if (effectiveThumbBottom) {
        rc.bottom = rcHeaderSplit.top - g_activePadDivider;
    } else if (effectiveThumbSide) {
        int divider = DpiScale(SWS_PAD_DIVIDER, g_dpiX);
        if (ThumbnailIsLeft()) {
            rc.left = rcHeaderSplit.right + divider;
        } else {
            rc.right = rcHeaderSplit.left - divider;
        }
    }

    if (rc.right < rc.left) rc.right = rc.left;
    if (rc.bottom < rc.top) rc.bottom = rc.top;
    return rc;
}

static int GetHeaderTopForEntry(const WindowEntry& e) {
    RECT rcHeader = GetHeaderContentRectForEntry(e);
    int rowTitleH = GetHeaderRowHeightPx();
    if (BadgeLayoutActive()) {
        rowTitleH = g_settings.showTitle ? GetHeaderTitleHeightPx() : 0;
    }
    if (rowTitleH <= 0) {
        return rcHeader.top;
    }

    int available = rcHeader.bottom - rcHeader.top;
    if (available <= rowTitleH) {
        return rcHeader.top;
    }

    return rcHeader.top + (available - rowTitleH) / 2;
}

// Soft drop shadow behind a thumbnail. Drawn in the content layer, which sits
// below the DWM thumbnail, so only the expanded/offset border peeks out around
// the thumbnail edges, producing a drop-shadow halo.
static void DrawThumbnailShadow(HDC hdc, const RECT& rc, int cornerRadius) {
    int rcw = rc.right - rc.left;
    int rch = rc.bottom - rc.top;
    if (rcw <= 0 || rch <= 0) return;

    Gdiplus::Graphics gfx(hdc);
    gfx.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

    int maxPass = DpiScale(6, g_dpiX);
    if (maxPass < 1) maxPass = 1;
    int yOff = DpiScale(2, g_dpiY);  // nudge down for a "drop" feel

    for (int pass = maxPass; pass > 0; --pass) {
        int shadowAlpha = 16 - (pass * 2);
        if (shadowAlpha < 1) shadowAlpha = 1;
        Gdiplus::SolidBrush shadowBrush(Gdiplus::Color(shadowAlpha, 0, 0, 0));
        int sp = pass;
        Gdiplus::REAL sx = (Gdiplus::REAL)(rc.left - sp);
        Gdiplus::REAL sy = (Gdiplus::REAL)(rc.top - sp + yOff);
        Gdiplus::REAL sw = (Gdiplus::REAL)(rcw + sp * 2);
        Gdiplus::REAL sh = (Gdiplus::REAL)(rch + sp * 2);
        if (cornerRadius > 0) {
            Gdiplus::REAL sd = cornerRadius * 2.0f + sp * 2.0f;
            if (sd > sw) sd = sw;
            if (sd > sh) sd = sh;
            Gdiplus::GraphicsPath sPath;
            sPath.AddArc(sx, sy, sd, sd, 180, 90);
            sPath.AddArc(sx + sw - sd, sy, sd, sd, 270, 90);
            sPath.AddArc(sx + sw - sd, sy + sh - sd, sd, sd, 0, 90);
            sPath.AddArc(sx, sy + sh - sd, sd, sd, 90, 90);
            sPath.CloseFigure();
            gfx.FillPath(&shadowBrush, &sPath);
        } else {
            gfx.FillRectangle(&shadowBrush, sx, sy, sw, sh);
        }
    }
}

static bool IsWindowTruncated(int idx);

// Shared drawing routine for both layered and buffered paint paths
static void DrawSwitcherContent(HDC hdc, bool fillBg, HWND hWnd) {
    RECT rcClient; GetClientRect(g_hSwitcher, &rcClient);
    int w = rcClient.right, h = rcClient.bottom;

    if (fillBg) {
        BYTE bgA = (BYTE)(g_settings.opacity * 255 / 100);
        if (bgA == 0) bgA = 1; // Prevent full transparency click-through
        COLORREF bgC = GetBgColor();
        BYTE bgR = GetRValue(bgC), bgG = GetGValue(bgC), bgB = GetBValue(bgC);
        RGBQUAD bgPx = { (BYTE)(bgB*bgA/255), (BYTE)(bgG*bgA/255), (BYTE)(bgR*bgA/255), bgA };
        BITMAPINFO bgBi = {}; bgBi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bgBi.bmiHeader.biWidth = 1; bgBi.bmiHeader.biHeight = 1;
        bgBi.bmiHeader.biPlanes = 1; bgBi.bmiHeader.biBitCount = 32; bgBi.bmiHeader.biCompression = BI_RGB;
        StretchDIBits(hdc, 0, 0, w, h, 0, 0, 1, 1, &bgPx, &bgBi, DIB_RGB_COLORS, SRCCOPY);
    }

    HFONT hOldFont = (HFONT)SelectObject(hdc, g_hFont);
    SetBkMode(hdc, TRANSPARENT);

    // DPI-scale layout constants for drawing
    int padLeft    = DpiScale(SWS_PAD_LEFT, g_dpiX);
    int rowTitleH  = GetHeaderRowHeightPx();
    int iconSz     = GetHeaderIconSizePx();
    int cornerRadius = GetThumbnailCornerRadiusPx();

    for (int i = 0; i < (int)g_windows.size(); i++) {
        auto& e = g_windows[i];

        // Skip truncated (not placed) windows
        if (e.rcCell.left == 0 && e.rcCell.right == 0 &&
            e.rcCell.top == 0 && e.rcCell.bottom == 0) continue;

        // Selection highlight: configurable border/fill combinations on rcCell.
        if (i == g_selectedIndex) {
            if (HighlightHasFill()) {
                DrawSelectionFill(hdc, e.rcCell);
            }
            if (HighlightHasBorder()) {
                DrawContour(hdc, e.rcCell, SWS_CONTOUR_SIZE, 1);
            }
        }

        // Hover thumbnail border is now drawn in DrawSwitcherOverlay so it sits above the thumbnail mask

        // Drop shadow behind the thumbnail (below the DWM thumbnail layer).
        if (g_settings.showThumbnails && g_settings.showThumbnailShadow &&
            !(e.rcThumbActual.left == 0 && e.rcThumbActual.right == 0 &&
              e.rcThumbActual.top == 0 && e.rcThumbActual.bottom == 0)) {
            DrawThumbnailShadow(hdc, e.rcThumbActual, cornerRadius);
        }

        if (g_settings.showThumbnails && cornerRadius > 0 && ThemeIs(L"none")) {
            MaskRectCorners(hdc, e.rcThumbActual, cornerRadius);
            RECT inset = e.rcThumbActual;
            InflateRect(&inset, -1, -1);
            MaskRectCorners(hdc, inset, cornerRadius);
        }

        int closeBtnReserve = DpiScale(24, g_dpiX) + padLeft;

        // ---- Badge layout rendering path ----
        if (BadgeLayoutActive()) {
            // Badge title: draw centered in the header content rect
            if (g_settings.showTitle && e.title[0]) {
                RECT rcHeaderContent = GetHeaderContentRectForEntry(e);
                int titleH = GetHeaderTitleHeightPx();
                int headerTop = GetHeaderTopForEntry(e);
                RECT rcText = { rcHeaderContent.left, headerTop, rcHeaderContent.right, headerTop + titleH };
                if (g_hTheme) {
                    DTTOPTS opts = { sizeof(DTTOPTS) };
                    opts.dwFlags = DTT_COMPOSITED | DTT_TEXTCOLOR;
                    opts.crText = g_isDarkMode ? SWS_TEXT_DARK : SWS_TEXT_LIGHT;
                    DrawThemeTextEx(g_hTheme, hdc, 0, 0, e.title, -1,
                        DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX, &rcText, &opts);
                } else {
                    SetTextColor(hdc, g_isDarkMode ? SWS_TEXT_DARK : SWS_TEXT_LIGHT);
                    DrawTextW(hdc, e.title, -1, &rcText,
                              DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX);
                }
            }

            // Badge icon is drawn in DrawSwitcherOverlay so it appears
            // above the DWM thumbnail (which composites on top of window content).
            continue;  // Skip normal header content rendering
        }

        // ---- Normal (non-badge) header content rendering ----
        // Keep centered header content stable: reserve close-button space consistently.
        // In vertical mode, never reserve space - close button overlays without displacement.
        int btnReserve = 0;
        bool isIconOnly = !g_settings.showThumbnails && !g_settings.showTitle && g_settings.showIcon;
        if (g_settings.showCloseButton && !HeaderIsVertical()) {
            if (!isIconOnly && !(g_settings.showThumbnails && ThumbnailIsSide())) {
                btnReserve = ((g_settings.centerTaskContent) || (i == g_hoverIndex && g_hoverWnd == hWnd))
                         ? closeBtnReserve
                         : 0;
            }
        }
        RECT rcHeaderContent = GetHeaderContentRectForEntry(e);
        int contentLeft = rcHeaderContent.left;
        int contentRight = rcHeaderContent.right - btnReserve;
        if (contentRight < contentLeft) contentRight = contentLeft;

        int headerTop = GetHeaderTopForEntry(e);
        int iconX = contentLeft;
        int iconY = headerTop + (rowTitleH - iconSz) / 2;

        if (!HeaderIsVertical() && g_settings.showTitle && g_settings.showIcon) {
            // Font rendering and icon boundaries scale slightly differently at higher DPIs.
            // At 100% (96 DPI), mathematical centering is visually perfect (shift = 0).
            // At >100% (e.g. 144 DPI), a small nudge downwards perfectly aligns their visual centers.
            int shift = (g_dpiY - 96) / 24;
            if (shift > 0) iconY += shift;
        }

        int textLeft = contentLeft;
        if (g_settings.showIcon) textLeft += iconSz + padLeft;
        int textRight = contentRight;
        int textTop = headerTop;
        int textBottom = textTop + rowTitleH;

        if (HeaderIsVertical() && !isIconOnly) {
            int availableW = contentRight - contentLeft;
            if (availableW < 0) availableW = 0;

            iconX = contentLeft + ((availableW > iconSz) ? (availableW - iconSz) / 2 : 0);
            iconY = headerTop;

            int headerGap = DpiScale(4, g_dpiY);
            int textH = GetHeaderTitleHeightPx();
            textTop = g_settings.showIcon ? (iconY + iconSz + headerGap) : iconY;
            textBottom = textTop + textH;
            textLeft = contentLeft;
            textRight = contentRight;
        } else if (g_settings.centerTaskContent) {
            int availableW = contentRight - contentLeft;
            if (availableW < 0) availableW = 0;

            int gap = padLeft;
            int textMaxW = availableW - (g_settings.showIcon ? iconSz + gap : 0);
            if (textMaxW < 0) textMaxW = 0;

            int textW = 0;
            if (g_settings.showTitle && textMaxW > 0 && e.title[0]) {
                RECT rcMeasure = { 0, 0, textMaxW, rowTitleH };
                DrawTextW(hdc, e.title, -1, &rcMeasure,
                          DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX | DT_CALCRECT);
                textW = rcMeasure.right - rcMeasure.left;
                if (textW < 0) textW = 0;
                if (textW > textMaxW) textW = textMaxW;
            }

            int blockW = (g_settings.showIcon ? iconSz : 0) + ((g_settings.showIcon && textW > 0) ? gap : 0) + textW;
            if (blockW < availableW) {
                iconX = contentLeft + (availableW - blockW) / 2;
            }

            textLeft = iconX + (g_settings.showIcon ? iconSz + ((textW > 0) ? gap : 0) : 0);
            textRight = textLeft + textW;
        }

        // Icon
        if (g_settings.showIcon && e.hIcon) {
            e.drawnIconX = iconX;
            e.drawnIconY = iconY;
            e.drawnIconSz = iconSz;
            DrawIconEx(hdc, iconX, iconY, e.hIcon, iconSz, iconSz, 0, NULL, DI_NORMAL);
        } else {
            e.drawnIconX = contentLeft;
            e.drawnIconY = headerTop;
            e.drawnIconSz = 0;
        }
        // Title text
        if (g_settings.showTitle) {
            RECT rcText = { textLeft, textTop, textRight, textBottom };
            if (rcText.right < rcText.left) rcText.right = rcText.left;
            if (g_hTheme) {
                DTTOPTS opts = { sizeof(DTTOPTS) };
                opts.dwFlags = DTT_COMPOSITED | DTT_TEXTCOLOR;
                opts.crText = g_isDarkMode ? SWS_TEXT_DARK : SWS_TEXT_LIGHT;
                DrawThemeTextEx(g_hTheme, hdc, 0, 0, e.title, -1,
                    DT_SINGLELINE | (HeaderIsVertical() ? DT_CENTER : DT_VCENTER) | DT_END_ELLIPSIS | DT_NOPREFIX, &rcText, &opts);
            } else {
                SetTextColor(hdc, g_isDarkMode ? SWS_TEXT_DARK : SWS_TEXT_LIGHT);
                DrawTextW(hdc, e.title, -1, &rcText,
                          DT_SINGLELINE | (HeaderIsVertical() ? DT_CENTER : DT_VCENTER) | DT_END_ELLIPSIS | DT_NOPREFIX);
            }
        }
    }

    // Draw overflow indicator if any windows are truncated
    if (g_settings.showOverflowIndicator && g_windows.size() > 0) {
        int n = (int)g_windows.size();
        int visibleCount = 0;
        for (int i = 0; i < n; i++) {
            if (IsWindowTruncated((g_layoutStartIndex + i) % n)) break;
            visibleCount++;
        }

        bool anyTruncated = visibleCount < n;
        bool hasPrev = anyTruncated && (g_layoutStartIndex > 0);
        bool hasNext = anyTruncated && ((g_layoutStartIndex + visibleCount) < n);

        if (hasPrev || hasNext) {
            bool verticalLayout = LayoutIsVertical();
            int masterPadX = DpiScale(SWS_MASTER_PADDING, g_dpiX);
            int masterPadY = DpiScale(SWS_MASTER_PADDING, g_dpiY);

            auto DrawChevronText = [&](LPCWSTR text, RECT& rc, UINT flags) {
                if (g_hTheme) {
                    DTTOPTS opts = { sizeof(DTTOPTS) };
                    opts.dwFlags = DTT_COMPOSITED | DTT_TEXTCOLOR;
                    opts.crText = g_isDarkMode ? SWS_TEXT_DARK : SWS_TEXT_LIGHT;
                    DrawThemeTextEx(g_hTheme, hdc, 0, 0, text, -1, flags | DT_NOCLIP, &rc, &opts);
                } else {
                    SetTextColor(hdc, g_isDarkMode ? SWS_TEXT_DARK : SWS_TEXT_LIGHT);
                    DrawTextW(hdc, text, -1, &rc, flags | DT_NOCLIP);
                }
            };

            if (hasPrev) {
                RECT rcPrev = rcClient;
                LPCWSTR textPrev = verticalLayout ? L"\x25C0" /* Left */ : L"\x25B2" /* Up */;
                if (verticalLayout) {
                    rcPrev.right = rcPrev.left + masterPadX;
                    DrawChevronText(textPrev, rcPrev, DT_SINGLELINE | DT_VCENTER | DT_CENTER | DT_NOPREFIX);
                } else {
                    rcPrev.bottom = rcPrev.top + masterPadY;
                    DrawChevronText(textPrev, rcPrev, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX);
                }
            }
            if (hasNext) {
                RECT rcNext = rcClient;
                LPCWSTR textNext = verticalLayout ? L"\x25B6" /* Right */ : L"\x25BC" /* Down */;
                if (verticalLayout) {
                    rcNext.left = rcNext.right - masterPadX;
                    DrawChevronText(textNext, rcNext, DT_SINGLELINE | DT_VCENTER | DT_CENTER | DT_NOPREFIX);
                } else {
                    rcNext.top = rcNext.bottom - masterPadY;
                    DrawChevronText(textNext, rcNext, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX);
                }
            }
        }
    }

    SelectObject(hdc, hOldFont);
}


// Rendering

static void DrawSwitcherOverlay(HDC hdc, HWND hWnd) {
    if (g_windows.empty()) return;

    int rowTitleH = GetHeaderRowHeightPx();
    int cornerRadius = GetThumbnailCornerRadiusPx();

    for (int idx = 0; idx < (int)g_windows.size(); idx++) {
        int i = (g_layoutStartIndex + idx) % g_windows.size();
        auto& e = g_windows[i];
        if (IsWindowTruncated(i)) continue;

        // ALWAYS draw opaque mask on the overlay window to cover the DWM thumbnail's square corners.
        // Even for the transparent theme, DWM on Windows 11 does not clip the thumbnail to the layered window's alpha channel.
        if (g_settings.showThumbnails && cornerRadius > 0) {
            COLORREF maskColor = GetBgColor();
            if (i == g_selectedIndex && HighlightHasFill()) {
                maskColor = GetHighlightFillColor();
            }
            MaskRectCorners(hdc, e.rcThumbActual, cornerRadius, true, maskColor);
            RECT inset = e.rcThumbActual;
            InflateRect(&inset, -1, -1);
            MaskRectCorners(hdc, inset, cornerRadius, true, maskColor);
        }

        // Hover thumbnail border: outer contour on rcThumbActual (drawn here to overlay the mask)
        if (i == g_hoverIndex && g_hoverWnd == hWnd && g_settings.showThumbnails && g_settings.showHoverBorder) {
            DrawContour(hdc, e.rcThumbActual, 1, -1, cornerRadius);
        }

        // Badge layout: draw icon overlay on thumbnail (must be in overlay layer
        // because DWM thumbnails composite on top of window content)
        if (BadgeLayoutActive() && g_settings.showIcon && e.hIcon) {
            int iconSz = GetHeaderIconSizePx();
            int thumbW = e.rcThumbActual.right - e.rcThumbActual.left;
            int thumbHt = e.rcThumbActual.bottom - e.rcThumbActual.top;
            if (thumbW > 0 && thumbHt > 0) {
                int badgePad = DpiScale(g_settings.badgeIconPadding, g_dpiX);
                int bIconX = 0, bIconY = 0;

                // Horizontal positioning
                if (BadgeIconPositionIs(L"topLeft") || BadgeIconPositionIs(L"centerLeft") || BadgeIconPositionIs(L"bottomLeft")) {
                    bIconX = e.rcThumbActual.left + badgePad;
                } else if (BadgeIconPositionIs(L"topRight") || BadgeIconPositionIs(L"centerRight") || BadgeIconPositionIs(L"bottomRight")) {
                    bIconX = e.rcThumbActual.right - iconSz - badgePad;
                } else {
                    bIconX = e.rcThumbActual.left + (thumbW - iconSz) / 2;
                }
                // Vertical positioning
                if (BadgeIconPositionIs(L"topLeft") || BadgeIconPositionIs(L"topCenter") || BadgeIconPositionIs(L"topRight")) {
                    bIconY = e.rcThumbActual.top + badgePad;
                } else if (BadgeIconPositionIs(L"bottomLeft") || BadgeIconPositionIs(L"bottomCenter") || BadgeIconPositionIs(L"bottomRight")) {
                    bIconY = e.rcThumbActual.bottom - iconSz - badgePad;
                } else {
                    bIconY = e.rcThumbActual.top + (thumbHt - iconSz) / 2;
                }

                bIconX += DpiScale(g_settings.badgeIconOffsetX, g_dpiX);
                bIconY += DpiScale(g_settings.badgeIconOffsetY, g_dpiY);

                e.drawnIconX = bIconX;
                e.drawnIconY = bIconY;
                e.drawnIconSz = iconSz;

                Gdiplus::Graphics gfx(hdc);
                gfx.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

                if (g_settings.showBadgeIconBackground) {
                    int bgSize = iconSz + badgePad * 2;
                    int bgX = bIconX - badgePad;
                    int bgY = bIconY - badgePad;

                    COLORREF bgC = GetIconBackgroundColor();
                    int op = g_isDarkMode ? g_settings.iconBgOpacityDark : g_settings.iconBgOpacityLight;
                    int alpha = (op * 255) / 100;
                    Gdiplus::SolidBrush bgBrush(Gdiplus::Color(alpha, GetRValue(bgC), GetGValue(bgC), GetBValue(bgC)));

                    Gdiplus::REAL r = (Gdiplus::REAL)GetBadgeIconBackgroundCornerRadiusPx(bgSize / 2);

                    if (g_settings.showBadgeIconBackgroundShadow) {
                        for (int pass = 5; pass > 0; --pass) {
                            int shadowAlpha = 15 - (pass * 2);
                            if (shadowAlpha < 1) shadowAlpha = 1;
                            Gdiplus::SolidBrush shadowBrush(Gdiplus::Color(shadowAlpha, 0, 0, 0));
                            int sp = pass;
                            if (r > 0) {
                                Gdiplus::GraphicsPath sPath;
                                Gdiplus::REAL sw = (Gdiplus::REAL)(bgSize + sp * 2), sh = sw;
                                Gdiplus::REAL sx = (Gdiplus::REAL)(bgX - sp), sy = (Gdiplus::REAL)(bgY - sp + 1);
                                Gdiplus::REAL sd = r * 2 + sp * 2;
                                if (sd > sw) sd = sw; if (sd > sh) sd = sh;
                                sPath.AddArc(sx, sy, sd, sd, 180, 90);
                                sPath.AddArc(sx + sw - sd, sy, sd, sd, 270, 90);
                                sPath.AddArc(sx + sw - sd, sy + sh - sd, sd, sd, 0, 90);
                                sPath.AddArc(sx, sy + sh - sd, sd, sd, 90, 90);
                                sPath.CloseFigure();
                                gfx.FillPath(&shadowBrush, &sPath);
                            } else {
                                gfx.FillRectangle(&shadowBrush, bgX - sp, bgY - sp + 1, bgSize + sp * 2, bgSize + sp * 2);
                            }
                        }
                    }

                    if (r > 0) {
                        Gdiplus::GraphicsPath path;
                        Gdiplus::REAL w = (Gdiplus::REAL)bgSize, h = (Gdiplus::REAL)bgSize;
                        Gdiplus::REAL x = (Gdiplus::REAL)bgX, y = (Gdiplus::REAL)bgY;
                        Gdiplus::REAL d = r * 2;
                        if (d > w) d = w; if (d > h) d = h;
                        path.AddArc(x, y, d, d, 180, 90);
                        path.AddArc(x + w - d, y, d, d, 270, 90);
                        path.AddArc(x + w - d, y + h - d, d, d, 0, 90);
                        path.AddArc(x, y + h - d, d, d, 90, 90);
                        path.CloseFigure();
                        gfx.FillPath(&bgBrush, &path);
                    } else {
                        gfx.FillRectangle(&bgBrush, bgX, bgY, bgSize, bgSize);
                    }
                    DrawIconEx(hdc, bIconX, bIconY, e.hIcon, iconSz, iconSz, 0, NULL, DI_NORMAL);
                } else {
                    Gdiplus::Bitmap* pBmp = CreateIconShadowBitmap(e.hIcon, iconSz, iconSz, 0.08f);
                    if (pBmp) {
                        int dx[] = { 0, 1, 0, -1, 1 };
                        int dy[] = { 1, 0, -1, 0, 1 };
                        for (int p = 0; p < 5; ++p) {
                            gfx.DrawImage(pBmp, bIconX + DpiScale(dx[p], g_dpiX), bIconY + DpiScale(dy[p] + 2, g_dpiY), iconSz, iconSz);
                        }
                        delete pBmp;
                    }
                    DrawIconEx(hdc, bIconX, bIconY, e.hIcon, iconSz, iconSz, 0, NULL, DI_NORMAL);
                }
            }
        }

        // Close button (positioned at top-right of the cell, in title area)
        if (g_settings.showCloseButton && i == g_hoverIndex && g_hoverWnd == hWnd) {
            int btnSz = DpiScale(24, g_dpiX);
            int bx, by;
            if (rowTitleH == 0 || (g_settings.showThumbnails && ThumbnailIsSide()) || BadgeLayoutActive()) {
                int btnPadding = DpiScale(4, g_dpiX);
                bx = e.rcThumbActual.right - btnSz - btnPadding;
                by = e.rcThumbActual.top + btnPadding;
            } else if (!g_settings.showThumbnails && !g_settings.showTitle && g_settings.showIcon) {
                int padLeft = DpiScale(SWS_PAD_LEFT, g_dpiX);
                int padTop = DpiScale(SWS_PAD_TOP, g_dpiY);
                int contentLeft = e.rcCell.left + padLeft;
                int contentRight = e.rcCell.right - padLeft;
                int iconSz = GetHeaderIconSizePx();
                int availableW = contentRight - contentLeft;
                if (availableW < 0) availableW = 0;

                int iconX = contentLeft;
                int iconY = e.rcCell.top + padTop + (rowTitleH - iconSz) / 2;

                if (g_settings.centerTaskContent) {
                    if (iconSz < availableW) {
                        iconX = contentLeft + (availableW - iconSz) / 2;
                    }
                }

                int btnPadding = DpiScale(2, g_dpiX);
                btnSz = DpiScale(16, g_dpiX);

                if (g_settings.centerTaskContent) {
                    bx = iconX + iconSz - btnSz + btnPadding;
                    by = iconY - btnPadding;
                } else {
                    int gap = DpiScale(4, g_dpiX);
                    bx = iconX + iconSz + gap;
                    by = iconY;
                }
            } else {
                RECT rcHeaderContent = GetHeaderContentRectForEntry(e);
                int headerTop = GetHeaderTopForEntry(e);
                bx = rcHeaderContent.right - btnSz;
                by = HeaderIsVertical() ? headerTop
                                        : (headerTop + (rowTitleH - btnSz) / 2);
            }

            if (g_isCloseHovered) {
                // Red rounded background for close button
                Gdiplus::Graphics graphics(hdc);
                graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
                int btnRadius = GetCloseButtonCornerRadiusPx();
                Gdiplus::SolidBrush redBrush(Gdiplus::Color(255, 196, 43, 28));
                if (btnRadius > 0) {
                    if (btnRadius * 2 > btnSz) btnRadius = btnSz / 2;
                    Gdiplus::GraphicsPath path;
                    Gdiplus::REAL d = (Gdiplus::REAL)(btnRadius * 2);
                    path.AddArc((Gdiplus::REAL)bx, (Gdiplus::REAL)by, d, d, 180, 90);
                    path.AddArc((Gdiplus::REAL)(bx + btnSz) - d, (Gdiplus::REAL)by, d, d, 270, 90);
                    path.AddArc((Gdiplus::REAL)(bx + btnSz) - d, (Gdiplus::REAL)(by + btnSz) - d, d, d, 0, 90);
                    path.AddArc((Gdiplus::REAL)bx, (Gdiplus::REAL)(by + btnSz) - d, d, d, 90, 90);
                    path.CloseFigure();
                    graphics.FillPath(&redBrush, &path);
                } else {
                    graphics.FillRectangle(&redBrush, (Gdiplus::REAL)bx, (Gdiplus::REAL)by,
                                           (Gdiplus::REAL)btnSz, (Gdiplus::REAL)btnSz);
                }
            }

            // Draw X with GDI+ for smooth diagonal lines only.
            Gdiplus::Graphics graphics(hdc);
            graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            COLORREF xc = (g_isCloseHovered || g_isDarkMode) ? RGB(255, 255, 255) : RGB(0, 0, 0);
            Gdiplus::Pen xPen(Gdiplus::Color(255, GetRValue(xc), GetGValue(xc), GetBValue(xc)), 1.5f * g_dpiX / 96.0f);
            int p = (btnSz == DpiScale(16, g_dpiX)) ? DpiScale(4, g_dpiX) : DpiScale(7, g_dpiX);
            graphics.DrawLine(&xPen, bx + p, by + p, bx + btnSz - p, by + btnSz - p);
            graphics.DrawLine(&xPen, bx + btnSz - p, by + p, bx + p, by + btnSz - p);
        }

        // Grouped window count badge
        if (g_settings.showGroupIndicator && g_settings.showApplications &&
            e.groupWindows.size() > 1) {
            Gdiplus::Graphics gfx(hdc);
            gfx.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
            gfx.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

            // Badge text
            WCHAR countText[8];
            _snwprintf_s(countText, ARRAYSIZE(countText), _TRUNCATE, L"%d", (int)e.groupWindows.size());

            // Badge font
            int badgeFontSz = DpiScale(10, g_dpiX);
            int fontStyle = Gdiplus::FontStyleBold;
            LPCWSTR family = L"Segoe UI";
            if (g_settings.applyToGroupIndicator && g_settings.fontFamily[0]) {
                family = g_settings.fontFamily;
                badgeFontSz = MulDiv(g_settings.fontSize, g_dpiY, 72);
                if (wcscmp(g_settings.fontStyle, L"regular") == 0 || wcscmp(g_settings.fontStyle, L"light") == 0) fontStyle = Gdiplus::FontStyleRegular;
                else if (wcscmp(g_settings.fontStyle, L"semibold") == 0 || wcscmp(g_settings.fontStyle, L"bold") == 0) fontStyle = Gdiplus::FontStyleBold;
                else if (wcscmp(g_settings.fontStyle, L"italic") == 0) fontStyle = Gdiplus::FontStyleItalic;
                else if (wcscmp(g_settings.fontStyle, L"boldItalic") == 0) fontStyle = Gdiplus::FontStyleBoldItalic;
            }
            Gdiplus::Font badgeFont(family, (Gdiplus::REAL)badgeFontSz, fontStyle, Gdiplus::UnitPixel);

            // Measure text
            Gdiplus::StringFormat sf;
            sf.SetAlignment(Gdiplus::StringAlignmentCenter);
            sf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
            Gdiplus::RectF measureRect(0, 0, 100, 100);
            Gdiplus::RectF textBounds;
            gfx.MeasureString(countText, -1, &badgeFont, measureRect, &sf, &textBounds);

            int badgePadX = DpiScale(4, g_dpiX);
            int badgePadY = DpiScale(2, g_dpiY);
            int badgeW = (int)(textBounds.Width + badgePadX * 2);
            int badgeH = (int)(textBounds.Height + badgePadY * 2);
            int minW = badgeH;  // pill shape: at least as wide as tall
            if (badgeW < minW) badgeW = minW;

            // Position: top-right area of the icon
            int badgeX, badgeY;
            if (e.drawnIconSz > 0) {
                badgeX = e.drawnIconX + e.drawnIconSz - (badgeW / 2);
                badgeY = e.drawnIconY - (badgeH / 2);
            } else {
                int cellPad = DpiScale(4, g_dpiX);
                badgeX = e.rcCell.right - badgeW - cellPad;
                badgeY = e.rcCell.top + cellPad;
            }

            // Background pill
            COLORREF bgC = GetIndicatorBackgroundColor();
            int op = g_isDarkMode ? g_settings.indicatorBgOpacityDark : g_settings.indicatorBgOpacityLight;
            int alpha = (op * 255) / 100;
            Gdiplus::SolidBrush pillBrush(Gdiplus::Color(alpha, GetRValue(bgC), GetGValue(bgC), GetBValue(bgC)));
            Gdiplus::REAL pillRadius = (Gdiplus::REAL)GetGroupIndicatorCornerRadiusPx(badgeH / 2);

            if (g_settings.showGroupIndicatorShadow) {
                for (int pass = 5; pass > 0; --pass) {
                    int shadowAlpha = 15 - (pass * 2);
                    if (shadowAlpha < 1) shadowAlpha = 1;
                    Gdiplus::SolidBrush shadowBrush(Gdiplus::Color(shadowAlpha, 0, 0, 0));
                    int sp = pass;
                    Gdiplus::REAL sx = (Gdiplus::REAL)(badgeX - sp);
                    Gdiplus::REAL sy = (Gdiplus::REAL)(badgeY - sp + 1);
                    Gdiplus::REAL sw = (Gdiplus::REAL)(badgeW + sp * 2);
                    Gdiplus::REAL sh = (Gdiplus::REAL)(badgeH + sp * 2);
                    Gdiplus::REAL sd = pillRadius * 2.0f + sp * 2.0f;
                    if (sd > sw) sd = sw; if (sd > sh) sd = sh;

                    if (pillRadius > 0) {
                        Gdiplus::GraphicsPath sPath;
                        sPath.AddArc(sx, sy, sd, sd, 180, 90);
                        sPath.AddArc(sx + sw - sd, sy, sd, sd, 270, 90);
                        sPath.AddArc(sx + sw - sd, sy + sh - sd, sd, sd, 0, 90);
                        sPath.AddArc(sx, sy + sh - sd, sd, sd, 90, 90);
                        sPath.CloseFigure();
                        gfx.FillPath(&shadowBrush, &sPath);
                    } else {
                        gfx.FillRectangle(&shadowBrush, sx, sy, sw, sh);
                    }
                }
            }

            if (pillRadius > 0) {
                Gdiplus::GraphicsPath pillPath;
                Gdiplus::REAL d = pillRadius * 2.0f;
                Gdiplus::REAL px = (Gdiplus::REAL)badgeX, py = (Gdiplus::REAL)badgeY;
                Gdiplus::REAL pw = (Gdiplus::REAL)badgeW, ph = (Gdiplus::REAL)badgeH;
                pillPath.AddArc(px, py, d, d, 180, 90);
                pillPath.AddArc(px + pw - d, py, d, d, 270, 90);
                pillPath.AddArc(px + pw - d, py + ph - d, d, d, 0, 90);
                pillPath.AddArc(px, py + ph - d, d, d, 90, 90);
                pillPath.CloseFigure();
                gfx.FillPath(&pillBrush, &pillPath);
            } else {
                gfx.FillRectangle(&pillBrush, badgeX, badgeY, badgeW, badgeH);
            }

            // Badge text
            COLORREF txtC = GetIndicatorTextColor();
            Gdiplus::SolidBrush textBrush(Gdiplus::Color(255, GetRValue(txtC), GetGValue(txtC), GetBValue(txtC)));
            Gdiplus::RectF pillRect((Gdiplus::REAL)badgeX, (Gdiplus::REAL)badgeY,
                                    (Gdiplus::REAL)badgeW, (Gdiplus::REAL)badgeH);
            gfx.DrawString(countText, -1, &badgeFont, pillRect, &sf, &textBrush);
        }
    }
}

static void PaintSwitcherOverlay() {
    if (!g_hCloseBtnWnd || !g_isVisible) return;
    HWND targetWnd = g_hoverWnd ? g_hoverWnd : g_hSwitcher;
    RECT rc; GetClientRect(targetWnd, &rc);
    int w = rc.right, h = rc.bottom;
    if (w <= 0 || h <= 0) return;
    HDC hdcScreen = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);
    BITMAPINFO bmi = {}; bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w; bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1; bmi.bmiHeader.biBitCount = 32; bmi.bmiHeader.biCompression = BI_RGB;
    void* bits = NULL;
    HBITMAP hBmp = CreateDIBSection(hdcMem, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    HBITMAP hOld = (HBITMAP)SelectObject(hdcMem, hBmp);

    // Clip the overlay DC to the same rounded rect as the main window.
    // SetWindowRgn is ignored for layered windows using UpdateLayeredWindow,
    // so we must clip manually to prevent corner masks from bleeding outside
    // the main window's rounded boundary.
    INT cp = GetCornerPref();
    if (cp == 1 && wcscmp(g_settings.cornerPreference, L"custom") == 0) {
        int radius = MulDiv(g_settings.customCornerRadius, g_dpiX, 96);
        HRGN hClip = CreateRoundRectRgn(0, 0, w + 1, h + 1, radius * 2, radius * 2);
        SelectClipRgn(hdcMem, hClip);
        DeleteObject(hClip);
    } else if (cp == 2) {
        int radius = MulDiv(8, g_dpiX, 96);
        HRGN hClip = CreateRoundRectRgn(0, 0, w + 1, h + 1, radius * 2, radius * 2);
        SelectClipRgn(hdcMem, hClip);
        DeleteObject(hClip);
    } else if (cp == 3) {
        int radius = MulDiv(4, g_dpiX, 96);
        HRGN hClip = CreateRoundRectRgn(0, 0, w + 1, h + 1, radius * 2, radius * 2);
        SelectClipRgn(hdcMem, hClip);
        DeleteObject(hClip);
    }

    DrawSwitcherOverlay(hdcMem, targetWnd);

    POINT ptSrc = {0,0}; SIZE sz = {w, h};
    RECT wr; GetWindowRect(targetWnd, &wr);
    POINT ptDst = { wr.left, wr.top };
    BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    UpdateLayeredWindow(g_hCloseBtnWnd, hdcScreen, &ptDst, &sz, hdcMem, &ptSrc, 0, &bf, ULW_ALPHA);
    SelectObject(hdcMem, hOld); DeleteObject(hBmp); DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcScreen);
}

static void PaintSwitcher() {
    if (!g_hSwitcher || !g_isVisible) return;
    if (ThemeIs(L"none")) {
        // Layered window path: draw to off-screen DIB, UpdateLayeredWindow
        RECT rc; GetClientRect(g_hSwitcher, &rc);
        int w = rc.right, h = rc.bottom;
        if (w <= 0 || h <= 0) return;
        HDC hdcScreen = GetDC(g_hSwitcher);
        HDC hdcMem = CreateCompatibleDC(hdcScreen);
        BITMAPINFO bmi = {}; bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = w; bmi.bmiHeader.biHeight = -h;
        bmi.bmiHeader.biPlanes = 1; bmi.bmiHeader.biBitCount = 32; bmi.bmiHeader.biCompression = BI_RGB;
        void* bits = NULL;
        HBITMAP hBmp = CreateDIBSection(hdcMem, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
        HBITMAP hOld = (HBITMAP)SelectObject(hdcMem, hBmp);

        INT cp = GetCornerPref();
        int radius = 0;
        if (cp == 1 && wcscmp(g_settings.cornerPreference, L"custom") == 0) {
            radius = MulDiv(g_settings.customCornerRadius, g_dpiX, 96);
        } else if (cp == 2) {
            radius = MulDiv(8, g_dpiX, 96);
        } else if (cp == 3) {
            radius = MulDiv(4, g_dpiX, 96);
        }
        if (radius > 0) {
            HRGN hClip = CreateRoundRectRgn(0, 0, w + 1, h + 1, radius * 2, radius * 2);
            SelectClipRgn(hdcMem, hClip);
            DeleteObject(hClip);
        }

        DrawSwitcherContent(hdcMem, true, g_hSwitcher);
        POINT ptSrc = {0,0}; SIZE sz = {w, h};
        BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
        UpdateLayeredWindow(g_hSwitcher, hdcScreen, NULL, &sz, hdcMem, &ptSrc, 0, &bf, ULW_ALPHA);
        for (HWND hMirror : g_hMirrorSwitchers) {
            if (IsWindow(hMirror)) {
                DrawSwitcherContent(hdcMem, true, hMirror);
                HDC hdcMirrorScreen = GetDC(hMirror);
                UpdateLayeredWindow(hMirror, hdcMirrorScreen, NULL, &sz, hdcMem, &ptSrc, 0, &bf, ULW_ALPHA);
                ReleaseDC(hMirror, hdcMirrorScreen);
            }
        }
        SelectObject(hdcMem, hOld); DeleteObject(hBmp); DeleteDC(hdcMem);
        ReleaseDC(g_hSwitcher, hdcScreen);
        PaintSwitcherOverlay();
    } else {
        // Acrylic: trigger WM_PAINT via InvalidateRect.
        // Use FALSE for the erase parameter: TRUE would send WM_ERASEBKGND which
        // blanks the window before WM_PAINT fires, producing a visible flicker gap.
        InvalidateRect(g_hSwitcher, NULL, FALSE);
        UpdateWindow(g_hSwitcher);
        for (HWND hMirror : g_hMirrorSwitchers) {
            if (IsWindow(hMirror)) {
                InvalidateRect(hMirror, NULL, FALSE);
                UpdateWindow(hMirror);
            }
        }
        PaintSwitcherOverlay();
    }
}

// Switcher Show / Hide / Switch

static void GetOffscreenDelayPosition(int* x, int* y) {
    // Position the 1x1 window safely far off every monitor by going 32000px past
    // the virtual screen boundary — arrangement-agnostic and guaranteed
    // to be off-screen even with multiple 4K displays left/above primary,
    // avoiding DWM thickframe/shadow artifacts bleeding into (0, 0).
    *x = GetSystemMetrics(SM_XVIRTUALSCREEN) - 32000;
    *y = GetSystemMetrics(SM_YVIRTUALSCREEN) - 32000;
}

static void CancelPendingShow() {
    if (g_hSwitcher) {
        KillTimer(g_hSwitcher, SWS_SHOW_DELAY_TIMER_ID);
    }

    g_isPendingShow = false;
}

static void ShowPendingOffscreenWindow() {
    int x, y;
    GetOffscreenDelayPosition(&x, &y);

    // Show as 1x1 off-screen. No transparency/style changes needed.
    SetWindowPos(g_hSwitcher, HWND_TOPMOST, x, y, 1, 1, SWP_NOACTIVATE);

    ShowWindow(g_hSwitcher, SW_SHOWNA);
    SetForegroundWindow(g_hSwitcher);
}

static LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && g_isVisible && wParam == WM_MOUSEWHEEL) {
        MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;
        bool ok = ScrollIs(L"always") || (ScrollIs(L"stickyOnly") && g_isSticky);
        if (ok) {
            int dir = (short)HIWORD(pMouseStruct->mouseData) > 0 ? -1 : 1;
            if (g_settings.reverseScrollDirection) dir = -dir;

            bool modActive = false;
            if (wcscmp(g_settings.scrollSecondaryModifier, L"shift") == 0) modActive = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
            else if (wcscmp(g_settings.scrollSecondaryModifier, L"ctrl") == 0) modActive = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
            else if (wcscmp(g_settings.scrollSecondaryModifier, L"alt") == 0) modActive = (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;

            const WCHAR* actionStr = modActive ? g_settings.scrollSecondaryAction : g_settings.scrollWheelAction;

            int action = 0; // 0 = none, 1 = selection, 2 = page
            if (wcscmp(actionStr, L"selection") == 0) action = 1;
            else if (wcscmp(actionStr, L"page") == 0) action = 2;

            if (action > 0) {
                PostMessage(g_hSwitcher, WM_SWS_SCROLL, (WPARAM)dir, (LPARAM)action);
                return 1;
            }
        }
    }
    return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam);
}

static void RevealPendingSwitcher() {
    if (!g_isPendingShow || !g_hSwitcher) {
        return;
    }

    KillTimer(g_hSwitcher, SWS_SHOW_DELAY_TIMER_ID);

    g_isPendingShow = false;
    g_isVisible = true;
    if (!g_hMouseHook) {
        g_hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, GetModuleHandle(NULL), 0);
    }

    int x = g_pendingSwitcherRect.left;
    int y = g_pendingSwitcherRect.top;
    int w = g_pendingSwitcherRect.right - g_pendingSwitcherRect.left;
    int h = g_pendingSwitcherRect.bottom - g_pendingSwitcherRect.top;

    SetWindowPos(g_hSwitcher, HWND_TOPMOST, x, y, w, h, SWP_NOACTIVATE);
    ApplySwitcherRegion();
    CreateMirrorSwitchers();
    if (g_hCloseBtnWnd) {
        SetWindowPos(g_hCloseBtnWnd, HWND_TOPMOST, x, y, w, h, SWP_NOACTIVATE);
        ShowWindow(g_hCloseBtnWnd, SW_SHOWNA);
    }

    RegisterThumbnails();
    PaintSwitcher();

    if (!g_isSticky) {
        SetTimer(g_hSwitcher, SWS_ALT_POLL_TIMER_ID, 50, NULL);
    }
}

static void ApplyThemeToWindow(HWND hWnd) {
    if (g_SetWindowCompositionAttribute) {
        ACCENT_POLICY a = {}; a.AccentState = 0;
        WINDOWCOMPOSITIONATTRIBDATA d = {19, &a, sizeof(a)};
        g_SetWindowCompositionAttribute(hWnd, &d);
    }
    MARGINS marGlassInset = ThemeIs(L"mica") ? MARGINS{-1, -1, -1, -1} : MARGINS{0, 0, 0, 0};
    DwmExtendFrameIntoClientArea(hWnd, &marGlassInset);

    LONG_PTR exs = GetWindowLongPtrW(hWnd, GWL_EXSTYLE);
    if (ThemeIs(L"none")) {
        SetWindowLongPtrW(hWnd, GWL_EXSTYLE, exs | WS_EX_LAYERED);
    } else {
        SetWindowLongPtrW(hWnd, GWL_EXSTYLE, exs & ~WS_EX_LAYERED);
        BOOL dark = g_isDarkMode;
        DwmSetWindowAttribute(hWnd, 20, &dark, sizeof(dark));
        if (ThemeIs(L"mica")) {
            int micaVal = 2; // DWMSBT_MAINWINDOW
            HRESULT hr = DwmSetWindowAttribute(hWnd, 38, &micaVal, sizeof(micaVal));
            if (FAILED(hr)) {
                int oldMicaVal = 1;
                hr = DwmSetWindowAttribute(hWnd, 1029, &oldMicaVal, sizeof(oldMicaVal));
            }
            if (FAILED(hr)) {
                SetWindowLongPtrW(hWnd, GWL_EXSTYLE, GetWindowLongPtrW(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
            }
            // Force the window to evaluate its NCACTIVATE state so Mica stays active
            SendMessage(hWnd, WM_NCACTIVATE, TRUE, 0);
        }
        if (ThemeIs(L"backdrop") && g_SetWindowCompositionAttribute) {
            DWORD blur = (DWORD)((g_settings.opacity / 100.0) * 255);
            COLORREF bg = GetBgColor();
            ACCENT_POLICY accent = {};
            accent.AccentState = 4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */;
            accent.AccentFlags = 0;
            accent.GradientColor = (blur << 24) | (bg & 0x00FFFFFF);
            WINDOWCOMPOSITIONATTRIBDATA data = {19, &accent, sizeof(accent)};
            g_SetWindowCompositionAttribute(hWnd, &data);
        }
        SetClassLongPtrW(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)GetStockObject(BLACK_BRUSH));
    }
    INT cp = GetCornerPref();
    if (cp == 1 && wcscmp(g_settings.cornerPreference, L"custom") == 0) {
        COLORREF none = 0xFFFFFFFE; // DWMWA_COLOR_NONE
        DwmSetWindowAttribute(hWnd, 34 /* DWMWA_BORDER_COLOR */, &none, sizeof(none));

        // Always use DONOTROUND for custom corners. SetWindowRgn defines the
        // window shape; DWM's own rounding (ROUND/ROUNDSMALL) uses a fixed
        // radius that conflicts with our custom radius, creating visible
        // glass artifacts at the corners.
        INT shadowCp = 1; // DWMWCP_DONOTROUND
        DwmSetWindowAttribute(hWnd, 33, &shadowCp, sizeof(shadowCp));
    } else {
        DwmSetWindowAttribute(hWnd, 33, &cp, sizeof(cp));
        COLORREF defaultColor = 0xFFFFFFFF; // DWMWA_COLOR_DEFAULT
        DwmSetWindowAttribute(hWnd, 34, &defaultColor, sizeof(defaultColor));
    }
}

static BOOL WINAPI MirrorEnumProc(HMONITOR hM, HDC, LPRECT, LPARAM) {
    if (hM != g_hCurrentMonitor) {
        MONITORINFO mInfo = { sizeof(mInfo) };
        GetMonitorInfoW(hM, &mInfo);
        int mx, my;
        GetSwitcherPosition(mInfo.rcWork, &mx, &my);
        HWND hMirror = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, SWS_CLASSNAME, L"", WS_POPUP | WS_THICKFRAME | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, mx, my, g_winW, g_winH, g_hSwitcher, NULL, GetModuleHandle(NULL), NULL);
        if (hMirror) {
            ApplyThemeToWindow(hMirror);
            g_hMirrorSwitchers.push_back(hMirror);
            SetWindowPos(hMirror, HWND_TOPMOST, mx, my, g_winW, g_winH, SWP_NOACTIVATE);
            ShowWindow(hMirror, SW_SHOWNA);
            SetActiveWindow(hMirror);
        }
    }
    return TRUE;
}

static void DestroyMirrorSwitchers() {
    for (HWND hMirror : g_hMirrorSwitchers) {
        if (IsWindow(hMirror)) DestroyWindow(hMirror);
    }
    g_hMirrorSwitchers.clear();
}

static void CreateMirrorSwitchers() {
    if (wcscmp(g_settings.switcherDisplayBehavior, L"allMonitors") == 0 || g_showAllMonitors) {
        EnumDisplayMonitors(NULL, NULL, MirrorEnumProc, 0);
    }
}


static void ApplySwitcherRegion() {
    if (!g_hSwitcher) return;
    static bool s_hasCustomRgn = false;
    static int s_lastW = 0, s_lastH = 0, s_lastRadius = -1;

    INT cp = GetCornerPref();
    bool isCustom = (cp == 1 && wcscmp(g_settings.cornerPreference, L"custom") == 0);

    if (isCustom) {
        int radius = MulDiv(g_settings.customCornerRadius, g_dpiX, 96);
        if (!s_hasCustomRgn || s_lastW != g_winW || s_lastH != g_winH || s_lastRadius != radius) {
            HRGN hRgn1 = CreateRoundRectRgn(0, 0, g_winW + 1, g_winH + 1, radius * 2, radius * 2);
            SetWindowRgn(g_hSwitcher, hRgn1, TRUE);
            s_hasCustomRgn = true;
            s_lastW = g_winW;
            s_lastH = g_winH;
            s_lastRadius = radius;
        }
    } else {
        if (s_hasCustomRgn) {
            SetWindowRgn(g_hSwitcher, NULL, TRUE);
            s_hasCustomRgn = false;
            s_lastW = 0;
            s_lastH = 0;
            s_lastRadius = -1;
        }
    }
}

static void ShowSwitcher(bool sticky) {
    DestroyMirrorSwitchers();

    POINT pt; GetCursorPos(&pt);
    HMONITOR hMon = (wcscmp(g_settings.switcherDisplayBehavior, L"primaryOnly") == 0) ?
                    MonitorFromWindow(GetDesktopWindow(), MONITOR_DEFAULTTOPRIMARY) :
                    MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);

    g_hCurrentMonitor = hMon;
    UnregisterThumbnails(); BuildWindowList();

    if (g_isAltBacktickSameApp) {
        WCHAR activeKey[MAX_PATH] = {0};
        GetWindowGroupKey(GetForegroundWindow(), activeKey, ARRAYSIZE(activeKey));
        if (activeKey[0]) {
            g_windows.erase(std::remove_if(g_windows.begin(), g_windows.end(),
                [&](const WindowEntry& e) {
                    WCHAR key[MAX_PATH] = {0};
                    GetWindowGroupKey(e.hWnd, key, ARRAYSIZE(key));
                    return wcscmp(key, activeKey) != 0;
                }),
                g_windows.end());
        }
        g_isAltBacktickSameApp = false;
    }

    if (g_windows.empty()) {
        HideSwitcher();
        return;
    }

    g_isDarkMode = ShouldUseDarkMode(); g_isSticky = sticky;

    g_layoutStartIndex = 0; // Always start from the first window on initial show
    g_drilledIn = false;
    g_savedAppList.clear();
    g_consumeEscUp = false;
    g_selectedIndex = (g_windows.size() > 1) ? 1 : 0;
    g_hoverIndex = -1;
    g_hoverWnd = NULL;
    g_isCloseHovered = false;

    RegisterThumbnailsEarly();
    ComputeLayout(hMon);
    if (g_winW <= 0 || g_winH <= 0) return;

    // Recreate font for current DPI
    if (g_hFont) { DeleteObject(g_hFont); g_hFont = NULL; }
    g_hFont = CreateScaledFont(g_dpiY);

    MONITORINFO mi = { sizeof(mi) }; GetMonitorInfoW(hMon, &mi);
    int cx, cy;
    GetSwitcherPosition(mi.rcWork, &cx, &cy);

    ApplyThemeToWindow(g_hSwitcher);
    ApplySwitcherRegion();

    g_pendingSwitcherRect = {
        cx,
        cy,
        cx + g_winW,
        cy + g_winH
    };

    CancelPendingShow();

    if (g_settings.showDelay > 0 && !sticky) {
        g_isPendingShow = true;
        g_isVisible = false;

        ShowPendingOffscreenWindow();

        SetTimer(g_hSwitcher, SWS_SHOW_DELAY_TIMER_ID, g_settings.showDelay, NULL);
        return;
    }

    g_isPendingShow = false;
    g_isVisible = true;
    if (!g_hMouseHook) {
        g_hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, GetModuleHandle(NULL), 0);
    }

    SetWindowPos(g_hSwitcher, HWND_TOPMOST, cx, cy, g_winW, g_winH, SWP_NOACTIVATE);
    ShowWindow(g_hSwitcher, SW_SHOWNA);
    CreateMirrorSwitchers();

    if (g_hCloseBtnWnd) {
        SetWindowPos(g_hCloseBtnWnd, HWND_TOPMOST, cx, cy, g_winW, g_winH, SWP_NOACTIVATE);
        ShowWindow(g_hCloseBtnWnd, SW_SHOWNA);
    }

    SetForegroundWindow(g_hSwitcher);

    RegisterThumbnails();
    PaintSwitcher();

    if (!sticky) {
        SetTimer(g_hSwitcher, SWS_ALT_POLL_TIMER_ID, 50, NULL);
    }
}

static void HideSwitcher() {
    g_showAllMonitors = false;
    CancelPendingShow();
    if (g_hSwitcher) KillTimer(g_hSwitcher, SWS_ALT_POLL_TIMER_ID);

    DestroyMirrorSwitchers();

    UnregisterThumbnails();
    if (g_hSwitcher) {
        ShowWindow(g_hSwitcher, SW_HIDE);
    }
    if (g_hCloseBtnWnd) {
        ShowWindow(g_hCloseBtnWnd, SW_HIDE);
    }

    g_isVisible = false;
    g_isPendingShow = false;
    if (g_hMouseHook) {
        UnhookWindowsHookEx(g_hMouseHook);
        g_hMouseHook = NULL;
    }
    g_isSticky = false;
    g_drilledIn = false;
    g_savedAppList.clear();
    g_consumeEscUp = false;
    g_isPaginatedView = false;
}

static void SwitchToSelected() {
    if (g_selectedIndex < 0 || g_selectedIndex >= (int)g_windows.size()) { HideSwitcher(); return; }
    HWND hT = g_windows[g_selectedIndex].hWnd;
    std::vector<HWND> groupWindows;
    if (g_settings.showApplications && g_settings.restoreAllWindows) {
        groupWindows = g_windows[g_selectedIndex].groupWindows;
    }

    // Restore sibling windows without stealing activation focus from target
    for (HWND hw : groupWindows) {
        if (IsWindow(hw) && hw != hT && IsIconic(hw)) ShowWindow(hw, SW_SHOWNOACTIVATE);
    }

    if (IsWindow(hT)) {
        HWND hP = GetLastActivePopup(hT);
        HWND hF = IsWindowVisible(hP) ? hP : hT;
        if (IsIconic(hF)) ShowWindow(hF, SW_RESTORE);
        if (!SetForegroundWindow(hF)) SwitchToThisWindow(hF, TRUE);
    }

    HideSwitcher();
}

// Helper: check if a window is truncated (not placed in current layout)
static bool IsWindowTruncated(int idx) {
    auto& w = g_windows[idx];
    return w.rcCell.left == 0 && w.rcCell.right == 0 &&
           w.rcCell.top == 0 && w.rcCell.bottom == 0;
}

// Helper: recompute layout and reposition switcher window
static void RecomputeAndReposition() {
    UnregisterThumbnails();
    RegisterThumbnailsEarly();
    HMONITOR hMon = g_hCurrentMonitor
                    ? g_hCurrentMonitor
                    : MonitorFromWindow(g_hSwitcher, MONITOR_DEFAULTTONEAREST);
    g_hCurrentMonitor = hMon;
    ComputeLayout(hMon);
    MONITORINFO mi = { sizeof(mi) };
    GetMonitorInfoW(hMon, &mi);
    int cx, cy;
    GetSwitcherPosition(mi.rcWork, &cx, &cy);

    g_pendingSwitcherRect = {
        cx,
        cy,
        cx + g_winW,
        cy + g_winH
    };

    if (g_isPendingShow) {
        int ox, oy;
        GetOffscreenDelayPosition(&ox, &oy);

        SetWindowPos(g_hSwitcher, HWND_TOPMOST, ox, oy, 1, 1, SWP_NOACTIVATE);
        return;
    }

    // Only call SetWindowPos when the size or position has actually changed.
    // An unconditional SetWindowPos sends WM_SIZE which triggers a WM_PAINT
    // before our own rendering pass completes, causing a momentary flicker.
    RECT curWndRect = {};
    GetWindowRect(g_hSwitcher, &curWndRect);
    bool posChanged = (curWndRect.left != cx || curWndRect.top != cy
                       || (curWndRect.right - curWndRect.left) != g_winW
                       || (curWndRect.bottom - curWndRect.top) != g_winH);
    if (posChanged) {
        SetWindowPos(g_hSwitcher, HWND_TOPMOST, cx, cy, g_winW, g_winH, SWP_NOACTIVATE);
    } else {
        SetWindowPos(g_hSwitcher, HWND_TOPMOST, cx, cy, g_winW, g_winH,
                     SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW);
    }
    for (HWND hMirror : g_hMirrorSwitchers) {
        if (!IsWindow(hMirror)) continue;
        MONITORINFO mInfo = { sizeof(mInfo) };
        GetMonitorInfoW(MonitorFromWindow(hMirror, MONITOR_DEFAULTTONEAREST), &mInfo);
        int mx, my; GetSwitcherPosition(mInfo.rcWork, &mx, &my);
        SetWindowPos(hMirror, HWND_TOPMOST, mx, my, g_winW, g_winH, SWP_NOACTIVATE);
    }
    if (g_hCloseBtnWnd && g_isVisible && !g_isPendingShow) {
        SetWindowPos(g_hCloseBtnWnd, HWND_TOPMOST, cx, cy, g_winW, g_winH, SWP_NOACTIVATE);
    }
    ApplySwitcherRegion();
    RegisterThumbnails();
}

// Drill into the selected application's windows: stash the grouped app list and
// replace g_windows with one entry per window of that app.
static void EnterAppGroup() {
    if (!g_settings.showApplications || g_drilledIn) return;
    if (g_selectedIndex < 0 || g_selectedIndex >= (int)g_windows.size()) return;
    std::vector<HWND> members = g_windows[g_selectedIndex].groupWindows;
    if (members.size() <= 1) return;  // nothing to expand

    UnregisterThumbnails();  // release app-list thumbnails before stashing
    g_savedAppList = std::move(g_windows);
    g_savedSelectedIndex = g_selectedIndex;
    g_savedLayoutStartIndex = g_layoutStartIndex;

    g_windows.clear();
    for (HWND hw : members) {
        if (!IsWindow(hw)) continue;
        WindowEntry e = {};
        e.hWnd = hw;
        GetWindowTextW(hw, e.title, 256);
        if (!e.title[0]) InternalGetWindowText(hw, e.title, 256);
        e.hIcon = LoadWindowIcon(hw);
        g_windows.push_back(std::move(e));
    }
    if (g_windows.empty()) {  // every window closed in the meantime; abort
        g_windows = std::move(g_savedAppList);
        RecomputeAndReposition();
        return;
    }
    g_drilledIn = true;
    g_selectedIndex = 0;
    g_layoutStartIndex = 0;
    g_hoverIndex = -1;
    g_hoverWnd = NULL;
    g_isCloseHovered = false;
    RecomputeAndReposition();
    PaintSwitcher();
}

// Leave the drilled-in window view and restore the grouped application list.
static void ExitAppGroup() {
    if (!g_drilledIn) return;
    UnregisterThumbnails();  // release drilled-window thumbnails
    g_windows = std::move(g_savedAppList);
    g_savedAppList.clear();
    g_selectedIndex = g_savedSelectedIndex;
    g_layoutStartIndex = g_savedLayoutStartIndex;
    if (g_selectedIndex >= (int)g_windows.size()) g_selectedIndex = (int)g_windows.size() - 1;
    if (g_selectedIndex < 0) g_selectedIndex = 0;
    g_drilledIn = false;
    g_hoverIndex = -1;
    g_hoverWnd = NULL;
    g_isCloseHovered = false;
    RecomputeAndReposition();
    PaintSwitcher();
}

static void ToggleAppDrill() {
    if (g_drilledIn) ExitAppGroup();
    else EnterAppGroup();
}

// Linear navigation: Tab, Shift+Tab, Left, Right, Hotkeys, Scroll
static void CycleLinear(int delta) {
    if (g_windows.empty()) return;
    g_isPaginatedView = false;
    int n = (int)g_windows.size();
    g_selectedIndex = ((g_selectedIndex + delta) % n + n) % n;

    // If the newly selected window is truncated, recompute layout
    if (IsWindowTruncated(g_selectedIndex)) {
        // Always try resetting to index 0 first (top-first view)
        g_layoutStartIndex = 0;
        RecomputeAndReposition();

        // If still truncated, scroll forward line-by-line until visible
        // (row in horizontal mode, column in vertical mode).
        int n2 = n;
        while (IsWindowTruncated(g_selectedIndex) && n2-- > 0) {
            int firstIdx = g_layoutStartIndex % n;
            int firstLineCoord = LayoutIsVertical() ? g_windows[firstIdx].rcCell.left : g_windows[firstIdx].rcCell.top;
            int newStart = g_layoutStartIndex;
            for (int k = 0; k < n; k++) {
                int wi = (g_layoutStartIndex + k) % n;
                if (IsWindowTruncated(wi)) break;
                int lineCoord = LayoutIsVertical() ? g_windows[wi].rcCell.left : g_windows[wi].rcCell.top;
                if (lineCoord != firstLineCoord) {
                    newStart = wi;
                    break;
                }
            }
            if (newStart == g_layoutStartIndex) {
                g_layoutStartIndex = g_selectedIndex;
            } else {
                g_layoutStartIndex = newStart;
            }
            RecomputeAndReposition();
        }
    }

    PaintSwitcher();
}

static void CyclePage(int dir) {
    if (g_windows.empty()) return;
    int n = (int)g_windows.size();

    // ── Step 1: Build a stable page map via a dry-run layout from index 0 ────
    //
    // We temporarily set g_layoutStartIndex = 0 and g_isPaginatedView = false
    // so ComputeLayout places ALL windows with no wrapping suppression.
    // We then read the resulting rcCell coordinates to find where rows/columns
    // are, and record the window index at which each new "page" starts.
    //
    // This is the only reliable approach because ComputeLayout's row/column
    // break conditions depend on many DPI-scaled constants that would be
    // error-prone to replicate here.

    HMONITOR hMon = g_hCurrentMonitor
                    ? g_hCurrentMonitor
                    : MonitorFromWindow(g_hSwitcher, MONITOR_DEFAULTTONEAREST);

    // Save current start index — the dry-run will overwrite g_layoutStartIndex.
    // Also save g_winW/g_winH: the dry-run ComputeLayout calls will overwrite them
    // with intermediate values, which would cause WM_PAINT to draw with wrong dims.
    int savedStart = g_layoutStartIndex;
    int savedWinW  = g_winW;
    int savedWinH  = g_winH;

    // Dry-run: full layout pass from index 0, with wrapping allowed
    g_isDryRunLayout   = true;
    g_layoutStartIndex = 0;
    g_isPaginatedView  = false;
    ComputeLayout(hMon);  // populates rcCell for all windows

    // ── Step 2: Walk rcCell coords to identify page boundaries ───────────────
    //
    // In horizontal mode each page is a group of rows (by rcCell.top).
    // In vertical   mode each page is a group of columns (by rcCell.left).
    //
    // A page boundary occurs at the first row/column whose windows were
    // TRUNCATED by ComputeLayout (rcCell all-zeros), because that is
    // exactly where the layout engine ran out of screen space.
    //
    // pageStarts[p] = the window index (in layout order, which equals the
    // absolute window index when g_layoutStartIndex == 0) at which page p
    // starts.

    std::vector<int> pageStarts;
    pageStarts.push_back(0);

    bool vertical = LayoutIsVertical();
    int  prevLine = -1;   // previous row-top (horiz) or col-left (vert)

    for (int idx = 0; idx < n; idx++) {
        auto& w = g_windows[idx];  // g_layoutStartIndex==0, so idx == window index

        // Truncated window signals the end of what fits on the current page
        if (w.rcCell.left == 0 && w.rcCell.right  == 0 &&
            w.rcCell.top  == 0 && w.rcCell.bottom == 0) {
            // Start a new page here
            pageStarts.push_back(idx);
            prevLine = -1;  // reset for the next page's dry-run (see below)
            break;          // only one overflow region possible per layout pass
        }

        int lineCoord = vertical ? w.rcCell.left : w.rcCell.top;
        if (lineCoord != prevLine) {
            prevLine = lineCoord;
        }
    }

    // If more than one page exists, we need to recursively find further page
    // boundaries by repeating the dry-run from each new page start.
    // We loop until no more pages are detected.
    while (true) {
        int lastPageStart = pageStarts.back();
        if (lastPageStart >= n) break;

        // Dry-run from the last page start
        g_layoutStartIndex = lastPageStart;
        g_isPaginatedView  = true;   // prevent wrapping past end
        ComputeLayout(hMon);

        bool foundTruncation = false;
        prevLine = -1;
        for (int idx = 0; idx < n; idx++) {
            int wi = (lastPageStart + idx) % n;
            // Stop if we've wrapped past the array in paginated mode
            if (idx > 0 && wi < lastPageStart) break;

            auto& w = g_windows[wi];
            if (w.rcCell.left == 0 && w.rcCell.right  == 0 &&
                w.rcCell.top  == 0 && w.rcCell.bottom == 0) {
                // This window starts the next page
                int nextStart = wi;
                if (nextStart <= lastPageStart) break;  // sanity: no progress
                pageStarts.push_back(nextStart);
                foundTruncation = true;
                break;
            }
        }
        if (!foundTruncation) break;  // all remaining windows fit — done
    }

    g_isDryRunLayout = false;

    // ── Step 3: Determine which page we're currently on ──────────────────────
    int currentPage = 0;
    for (int p = (int)pageStarts.size() - 1; p >= 0; p--) {
        if (savedStart >= pageStarts[p]) {
            currentPage = p;
            break;
        }
    }

    // ── Step 4: Navigate to next or previous page ────────────────────────────
    int numPages   = (int)pageStarts.size();
    int targetPage = currentPage;

    if (dir > 0) {
        // Scroll forward: go to next page, clamp at last
        if (currentPage + 1 < numPages)
            targetPage = currentPage + 1;
    } else {
        // Scroll backward: go to previous page, clamp at first
        if (currentPage - 1 >= 0)
            targetPage = currentPage - 1;
    }

    // ── Boundary guard: if already on the first/last page, restore state and
    // exit immediately. Since g_isDryRunLayout prevented any thumbnails from
    // being destroyed during the dry runs, no DWM cleanup or reflow is needed.
    if (targetPage == currentPage) {
        g_layoutStartIndex = savedStart;
        g_winW             = savedWinW;
        g_winH             = savedWinH;
        g_isPaginatedView  = true;

        // Restore the g_windows memory geometry (rcCell, rcThumbActual) to the
        // current page. The dry-runs overwrote it with the last page's layout.
        // We set g_isDryRunLayout = true so truncateRemaining doesn't touch DWM handles.
        g_isDryRunLayout = true;
        ComputeLayout(hMon);
        g_isDryRunLayout = false;

        return;  // nothing changed — no reflow, no repaint, no flicker
    }

    // ── Step 5: Apply the new page and do the real reflow ────────────────────
    // Restore g_winW/g_winH so the window doesn't resize to a dry-run value
    // before RecomputeAndReposition sets the correct final dimensions.
    g_winW = savedWinW;
    g_winH = savedWinH;
    g_layoutStartIndex = pageStarts[targetPage];
    g_isPaginatedView  = true;
    RecomputeAndReposition();  // single real reflow — no flicker, no loops

    // ── Step 6: Place selection on the first visible window of the new page ──
    g_selectedIndex = g_layoutStartIndex % n;

    PaintSwitcher();
}

// Directional navigation: Up, Down (EP-style row-based with nearest-column match)
// Walks in layout placement order (from g_layoutStartIndex, wrapping) instead of raw list index.
static void CycleDirectional(int vertDelta) {
    if (g_windows.empty()) return;
    int n = (int)g_windows.size();
    bool verticalLayout = LayoutIsVertical();

    // Build layout-order mapping: layoutOrder[0] is the first window placed visually
    auto buildLayoutOrder = [&](std::vector<int>& order) {
        order.resize(n);
        for (int idx = 0; idx < n; idx++)
            order[idx] = (g_layoutStartIndex + idx) % n;
    };

    std::vector<int> layoutOrder;
    buildLayoutOrder(layoutOrder);

    // Find current selection's position in layout order
    int layoutPos = 0;
    for (int idx = 0; idx < n; idx++) {
        if (layoutOrder[idx] == g_selectedIndex) { layoutPos = idx; break; }
    }

    // Save current selection's line anchor and perpendicular center.
    RECT rcPrev = g_windows[g_selectedIndex].rcCell;
    int prevLineCoord = verticalLayout ? rcPrev.left : rcPrev.top;
    int prevPerpCenter = verticalLayout ? (rcPrev.top + rcPrev.bottom) / 2 : (rcPrev.left + rcPrev.right) / 2;

    // Walk direction in layout order: DOWN = +1 (visually next), UP = -1 (visually prev)
    int layoutDelta = vertDelta;
    int current = -1;
    bool foundDifferentRow = false;

    for (int step = 0; step < n; step++) {
        int nextPos = ((layoutPos + (step + 1) * layoutDelta) % n + n) % n;
        int windowIdx = layoutOrder[nextPos];

        if (nextPos == layoutPos) break; // Wrapped all the way around

        // Target window is off-screen — scroll layout to reveal it.
        if (IsWindowTruncated(windowIdx)) {
            // First try reset to 0 (handles wrap-to-top / DOWN from last row)
            g_layoutStartIndex = 0;
            RecomputeAndReposition();

            // If still truncated, scroll forward line-by-line.
            int attempts = n;
            while (IsWindowTruncated(windowIdx) && attempts-- > 0) {
                int firstIdx = g_layoutStartIndex % n;
                int firstLineCoord2 = verticalLayout ? g_windows[firstIdx].rcCell.left : g_windows[firstIdx].rcCell.top;
                int newStart = g_layoutStartIndex;
                for (int k = 0; k < n; k++) {
                    int wi = (g_layoutStartIndex + k) % n;
                    if (IsWindowTruncated(wi)) break;
                    int lineCoord = verticalLayout ? g_windows[wi].rcCell.left : g_windows[wi].rcCell.top;
                    if (lineCoord != firstLineCoord2) {
                        newStart = wi;
                        break;
                    }
                }
                if (newStart == g_layoutStartIndex) {
                    g_layoutStartIndex = windowIdx;
                } else {
                    g_layoutStartIndex = newStart;
                }
                RecomputeAndReposition();
            }

            // Rebuild layout order after recompute
            buildLayoutOrder(layoutOrder);
            current = windowIdx;
            foundDifferentRow = true;
            break;
        }

        int lineCoord = verticalLayout ? g_windows[windowIdx].rcCell.left : g_windows[windowIdx].rcCell.top;
        if (lineCoord != prevLineCoord) {
            current = windowIdx;
            foundDifferentRow = true;
            break;
        }
    }

    if (!foundDifferentRow) {
        // Only one line visible; nothing to jump to.
        return;
    }

    // Find current's position in layout order for row scanning
    int currentLayoutPos = 0;
    for (int idx = 0; idx < n; idx++) {
        if (layoutOrder[idx] == current) { currentLayoutPos = idx; break; }
    }

    // Found a window on a different line. Find nearest position match
    // on that line (x-match for horizontal mode, y-match for vertical mode).
    int targetLineCoord = verticalLayout ? g_windows[current].rcCell.left : g_windows[current].rcCell.top;
    int bestIndex = current;
    int bestDist = INT_MAX;

    // Scan forward in layout order from current to find all windows on the target line.
    for (int idx = currentLayoutPos; idx < n; idx++) {
        int wi = layoutOrder[idx];
        if (IsWindowTruncated(wi)) break;
        int lineCoord = verticalLayout ? g_windows[wi].rcCell.left : g_windows[wi].rcCell.top;
        if (lineCoord != targetLineCoord) break;

        int perpCenter = verticalLayout ?
            (g_windows[wi].rcCell.top + g_windows[wi].rcCell.bottom) / 2 :
            (g_windows[wi].rcCell.left + g_windows[wi].rcCell.right) / 2;
        int dist = abs(prevPerpCenter - perpCenter);
        if (dist < bestDist) {
            bestDist = dist;
            bestIndex = wi;
        }
    }

    // Scan backward in layout order from current to cover the full line.
    for (int idx = currentLayoutPos - 1; idx >= 0; idx--) {
        int wi = layoutOrder[idx];
        if (IsWindowTruncated(wi)) break;
        int lineCoord = verticalLayout ? g_windows[wi].rcCell.left : g_windows[wi].rcCell.top;
        if (lineCoord != targetLineCoord) break;

        int perpCenter = verticalLayout ?
            (g_windows[wi].rcCell.top + g_windows[wi].rcCell.bottom) / 2 :
            (g_windows[wi].rcCell.left + g_windows[wi].rcCell.right) / 2;
        int dist = abs(prevPerpCenter - perpCenter);
        if (dist < bestDist) {
            bestDist = dist;
            bestIndex = wi;
        }
    }

    g_selectedIndex = bestIndex;
    PaintSwitcher();
}

static int HitTest(int x, int y) {
    for (int i = 0; i < (int)g_windows.size(); i++) {
        RECT r = g_windows[i].rcCell;
        if (x >= r.left && x < r.right && y >= r.top && y < r.bottom) return i;
    }
    return -1;
}
static int HitTestThumb(int x, int y) {
    if (!g_settings.showThumbnails) return -1;
    for (int i = 0; i < (int)g_windows.size(); i++) {
        RECT r = g_windows[i].rcThumbActual;
        if (x >= r.left && x < r.right && y >= r.top && y < r.bottom) return i;
    }
    return -1;
}


// WndProc

static void SWS_RegisterHotkeys();

static void UpdateEntryForWindow(WindowEntry& e) {
    GetWindowTextW(e.hWnd, e.title, 256);
    if (!e.title[0]) InternalGetWindowText(e.hWnd, e.title, 256);
    e.hIcon = LoadWindowIcon(e.hWnd);

    if (g_settings.showApplications && wcscmp(g_settings.showTitles, L"windowTitle") != 0) {
        WCHAR appName[256] = {0};
        GetAppName(e.hWnd, appName, ARRAYSIZE(appName));
        if (appName[0]) {
            if (_wcsicmp(appName, L"Application Frame Host") == 0 && e.title[0]) {
                wcscpy_s(appName, e.title);
            }
            if (wcscmp(g_settings.showTitles, L"appName") == 0) {
                wcscpy_s(e.title, appName);
            } else {  // appNameWindowTitle
                if (e.title[0]) {
                    WCHAR combined[256];
                    _snwprintf_s(combined, ARRAYSIZE(combined), _TRUNCATE,
                                 L"%s - %s", appName, e.title);
                    wcscpy_s(e.title, combined);
                } else {
                    wcscpy_s(e.title, appName);
                }
            }
        }
    }
}

// Close the window for the entry at idx (posts SC_CLOSE, same as the close
// button), remove it from the list and relayout. Shared by the close button,
// middle-click, Q, Ctrl+W and Del.
static void CloseSwitcherEntry(int idx) {
    if (idx < 0 || idx >= (int)g_windows.size()) return;

    bool eraseEntry = true;
    if (g_settings.showApplications && g_windows[idx].groupWindows.size() > 1) {
        if (wcscmp(g_settings.groupCloseBehavior, L"closeAll") == 0) {
            for (HWND hw : g_windows[idx].groupWindows) {
                PostMessage(hw, WM_SYSCOMMAND, SC_CLOSE, 0);
            }
        } else {
            // closeRecent (Default)
            HWND closedHwnd = g_windows[idx].hWnd;
            PostMessage(closedHwnd, WM_SYSCOMMAND, SC_CLOSE, 0);

            auto& group = g_windows[idx].groupWindows;
            group.erase(std::remove(group.begin(), group.end(), closedHwnd), group.end());

            if (!group.empty()) {
                eraseEntry = false;
                g_windows[idx].hWnd = group[0];
                UpdateEntryForWindow(g_windows[idx]);
                for (const auto& kv : g_windows[idx].hThumbs) {
                    if (kv.second) DwmUnregisterThumbnail(kv.second);
                }
                g_windows[idx].hThumbs.clear();
            }
        }
    } else {
        PostMessage(g_windows[idx].hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
    }

    if (eraseEntry) {
        for (const auto& kv : g_windows[idx].hThumbs) {
            if (kv.second) DwmUnregisterThumbnail(kv.second);
        }
        g_windows[idx].hThumbs.clear();

        g_windows.erase(g_windows.begin() + idx);
    }

    if (g_windows.empty()) { HideSwitcher(); return; }
    if (g_selectedIndex >= (int)g_windows.size()) g_selectedIndex = (int)g_windows.size() - 1;

    RecomputeAndReposition();

    g_hoverIndex = -1;
    g_hoverWnd = NULL;
    g_isCloseHovered = false;
    PaintSwitcher();
}

static bool IsSwitcherWindow(HWND hWnd) {
    if (!hWnd) return false;
    if (hWnd == g_hSwitcher) return true;
    for (HWND h : g_hMirrorSwitchers) {
        if (hWnd == h) return true;
    }
    return false;
}

static LRESULT CALLBACK SwitcherWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_NCCALCSIZE && wParam == TRUE) {
        return 0; // Remove standard frame for WS_OVERLAPPED
    }
    if (uMsg == WM_NCACTIVATE) {
        // Force DWM to keep the active visual state (Mica/Backdrop) even when unfocused
        return DefWindowProcW(hWnd, uMsg, TRUE, lParam);
    }

    if (uMsg == WM_TIMER) {
        if (wParam == SWS_HOTKEY_RETRY_TIMER_ID) {
            SWS_RegisterHotkeys();
            return 0;
        }

        if (wParam == SWS_SHOW_DELAY_TIMER_ID) {
            RevealPendingSwitcher();
            return 0;
        }

        if (wParam == SWS_ALT_POLL_TIMER_ID) {
            if (!g_isSticky && (GetAsyncKeyState(VK_MENU) & 0x8000) == 0) {
                KillTimer(hWnd, SWS_ALT_POLL_TIMER_ID);
                SwitchToSelected();
            }
            return 0;
        }
    }
    if (uMsg == WM_HOTKEY) {
        int id = (int)wParam;
        bool isBackward = false;
        bool isCtrl = false;
        bool isAltBacktickTrigger = false;

        switch (id) {
        case SWS_HOTKEY_ALTTAB:
            break;
        case SWS_HOTKEY_WINALTTAB:
            g_showAllMonitors = true;
            break;
        case SWS_HOTKEY_ALTSHIFTTAB:
            if (!UseAltShiftTabBackward()) return 0;
            isBackward = true;
            break;
        case SWS_HOTKEY_WINALTSHIFTTAB:
            if (!UseAltShiftTabBackward()) return 0;
            isBackward = true;
            g_showAllMonitors = true;
            break;
        case SWS_HOTKEY_ALTCTRLTAB:
            isCtrl = true;
            break;
        case SWS_HOTKEY_ALTSHIFTCTRLTAB:
            if (!UseAltShiftTabBackward()) return 0;
            isBackward = true;
            isCtrl = true;
            break;
        case SWS_HOTKEY_ALTBACKTICK:
            if (wcscmp(g_settings.altBacktickBehavior, L"sameApp") == 0) {
                isAltBacktickTrigger = true;
            } else if (wcscmp(g_settings.altBacktickBehavior, L"backward") == 0 || UseAltBacktickBackward()) {
                isBackward = true;
            } else {
                return 0;
            }
            break;
        default:
            return 0;
        }

        if (!g_isVisible && !g_isPendingShow) {
            if (isAltBacktickTrigger) g_isAltBacktickSameApp = true;
            ShowSwitcher(isCtrl);

            if (isBackward && g_windows.size() > 1) {
                g_selectedIndex = (int)g_windows.size() - 1;

                if (g_isVisible) {
                    PaintSwitcher();
                }
            }
        } else {
            if (g_isPendingShow && isCtrl) {
                g_isSticky = true;
            }

            CycleLinear(isBackward ? -1 : 1);

            if (g_isPendingShow) {
                RevealPendingSwitcher();
            }
        }
        return 0;
    }

    // WM_PAINT for Acrylic (non-layered) path
    if (uMsg == WM_PAINT && !ThemeIs(L"none") && g_isVisible) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rc; GetClientRect(hWnd, &rc);
        BP_PAINTPARAMS params = { sizeof(params) };
        params.dwFlags = BPPF_ERASE;
        HDC hdcBuf = NULL;
        HPAINTBUFFER hBP = BeginBufferedPaint(hdc, &rc, BPBF_TOPDOWNDIB, &params, &hdcBuf);
        if (hBP) {
            DrawSwitcherContent(hdcBuf, false, hWnd);
            // Do NOT call BufferedPaintSetAlpha here — it would force all pixels
            // to opaque (alpha=255), blocking the acrylic blur from showing through.
            // BPPF_ERASE already cleared the buffer to RGBA(0,0,0,0) = transparent.
            // Our contour/icon/text drawing sets correct per-pixel alpha.
            EndBufferedPaint(hBP, TRUE);
        }
        EndPaint(hWnd, &ps);
        return 0;
    }

    switch (uMsg) {
    case WM_KEYUP:
        if (g_isVisible && UseAltShiftBackward() && wParam == VK_TAB) {
            bool altDown = (GetKeyState(VK_MENU) & 0x8000) != 0;
            bool shiftDown = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
            if (altDown && shiftDown) {
                return 0;
            }
        }

        if (wParam == VK_MENU && (g_isVisible || g_isPendingShow) && !g_isSticky) {
            SwitchToSelected();
            return 0;
        }
        if (wParam == VK_ESCAPE && g_isVisible) {
            if (g_consumeEscUp) { g_consumeEscUp = false; return 0; }
            HideSwitcher();
            return 0;
        }
        if (wParam == VK_RETURN && g_isVisible) { SwitchToSelected(); return 0; }
        break;
    case WM_SYSKEYUP:
        if (g_isVisible && UseAltShiftBackward() && wParam == VK_TAB) {
            bool altDown = (GetKeyState(VK_MENU) & 0x8000) != 0;
            bool shiftDown = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
            if (altDown && shiftDown) {
                return 0;
            }
        }

        if (wParam == VK_MENU && (g_isVisible || g_isPendingShow) && !g_isSticky) {
            SwitchToSelected();
            return 0;
        }
        break;
    case WM_SYSKEYDOWN: case WM_KEYDOWN:
        if (g_isVisible) {
            // Ctrl tap: drill into / out of the selected application's windows.
            if ((wParam == VK_CONTROL || wParam == VK_LCONTROL || wParam == VK_RCONTROL)
                && g_settings.showApplications) {
                bool isRepeat = (lParam & 0x40000000) != 0;
                if (!isRepeat) ToggleAppDrill();
                return 0;
            }
            // Block Alt+Shift+Tab from reaching the system if setting is enabled
            if (UseAltShiftBackward() && wParam == VK_TAB) {
                bool altDown = (GetKeyState(VK_MENU) & 0x8000) != 0;
                bool shiftDown = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
                if (altDown && shiftDown) {
                    // Suppress native switcher
                    return 0;
                }
            }
            if (UseAltShiftBackward() &&
                (wParam == VK_SHIFT || wParam == VK_LSHIFT || wParam == VK_RSHIFT)) {
                bool isRepeat = (lParam & 0x40000000) != 0;
                bool altDown = (GetKeyState(VK_MENU) & 0x8000) != 0;
                if (!isRepeat && altDown) {
                    CycleLinear(-1);
                    return 0;
                }
            }

            if (wParam == VK_TAB) {
                bool shiftDown = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
                bool backward = UseAltShiftTabBackward() && shiftDown;
                CycleLinear(backward ? -1 : 1);
                return 0;
            }
            if (!LayoutIsVertical()) {
                if (wParam == VK_LEFT) { CycleLinear(-1); return 0; }
                if (wParam == VK_RIGHT) { CycleLinear(1); return 0; }
                if (wParam == VK_UP) { CycleDirectional(-1); return 0; }
                if (wParam == VK_DOWN) { CycleDirectional(1); return 0; }
            } else {
                if (wParam == VK_UP) { CycleLinear(-1); return 0; }
                if (wParam == VK_DOWN) { CycleLinear(1); return 0; }
                if (wParam == VK_LEFT) { CycleDirectional(-1); return 0; }
                if (wParam == VK_RIGHT) { CycleDirectional(1); return 0; }
            }
            if (wParam == VK_ESCAPE) {
                if (g_drilledIn) { ExitAppGroup(); g_consumeEscUp = true; }
                else HideSwitcher();
                return 0;
            }
            if (wParam == VK_RETURN || wParam == VK_SPACE) { SwitchToSelected(); return 0; }
            bool isCtrlW = (wParam == 'W' && (GetKeyState(VK_CONTROL) & 0x8000) != 0);
            if (wParam == 'Q' || wParam == VK_DELETE || isCtrlW) {
                bool isRepeat = (lParam & 0x40000000) != 0;
                if (!isRepeat) CloseSwitcherEntry(g_selectedIndex);
                return 0;
            }
        }
        break;
    // (Removed duplicate combined case for WM_SYSKEYUP and WM_KEYUP)
    case WM_SWS_SCROLL:
        if (g_isVisible) {
            int dir = (int)wParam;
            int action = (int)lParam;
            if (action == 1) { // selection
                CycleLinear(dir);
            } else if (action == 2) { // page
                CyclePage(dir);
            }
        }
        return 0;
    case WM_SWS_SETTINGS_CHANGED:
        if (g_isVisible) HideSwitcher();
        SWS_UnregisterHotkeys();
        LoadSettings();
        SWS_RegisterHotkeys();
        return 0;
    case WM_SETCURSOR:
        SetCursor(LoadCursor(NULL, IDC_ARROW));
        return TRUE;
    case WM_MOUSEMOVE: {
        int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
        int idx = g_settings.showThumbnails ? HitTestThumb(x, y) : HitTest(x, y);
        if (idx < 0) idx = HitTest(x, y);

        bool closeHovered = false;
        if (g_settings.showCloseButton && idx >= 0) {
            auto& e = g_windows[idx];
            int titleH = GetHeaderRowHeightPx();
            int btnSz = DpiScale(24, g_dpiX);
            int bx, by;
            if (titleH == 0 || (g_settings.showThumbnails && ThumbnailIsSide()) || BadgeLayoutActive()) {
                int btnPadding = DpiScale(4, g_dpiX);
                bx = e.rcThumbActual.right - btnSz - btnPadding;
                by = e.rcThumbActual.top + btnPadding;
            } else if (!g_settings.showThumbnails && !g_settings.showTitle && g_settings.showIcon) {
                int padL = DpiScale(SWS_PAD_LEFT, g_dpiX);
                int padT = DpiScale(SWS_PAD_TOP, g_dpiY);
                int contentLeft = e.rcCell.left + padL;
                int contentRight = e.rcCell.right - padL;
                int iconSz = GetHeaderIconSizePx();
                int availableW = contentRight - contentLeft;
                if (availableW < 0) availableW = 0;

                int iconX = contentLeft;
                int iconY = e.rcCell.top + padT + (titleH - iconSz) / 2;

                if (g_settings.centerTaskContent) {
                    if (iconSz < availableW) {
                        iconX = contentLeft + (availableW - iconSz) / 2;
                    }
                }

                int btnPadding = DpiScale(2, g_dpiX);
                btnSz = DpiScale(16, g_dpiX);

                if (g_settings.centerTaskContent) {
                    bx = iconX + iconSz - btnSz + btnPadding;
                    by = iconY - btnPadding;
                } else {
                    int gap = DpiScale(4, g_dpiX);
                    bx = iconX + iconSz + gap;
                    by = iconY;
                }
            } else {
                RECT rcHeaderContent = GetHeaderContentRectForEntry(e);
                int headerTop = GetHeaderTopForEntry(e);
                bx = rcHeaderContent.right - btnSz;
                by = HeaderIsVertical() ? headerTop
                                        : (headerTop + (titleH - btnSz) / 2);
            }
            if (x >= bx && x <= bx + btnSz && y >= by && y <= by + btnSz) {
                closeHovered = true;
            }
        }

        if (idx != g_hoverIndex || closeHovered != g_isCloseHovered || g_hoverWnd != hWnd) {
            g_hoverIndex = idx;
            g_hoverWnd = hWnd;
            g_isCloseHovered = closeHovered;
            PaintSwitcher();
        }
        return 0;
    }
    case WM_LBUTTONUP: {
        int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
        int idx = HitTest(x, y);
        if (idx >= 0) {
            if (g_isCloseHovered && idx == g_hoverIndex) {
                CloseSwitcherEntry(idx);
            } else {
                g_selectedIndex = idx;
                SwitchToSelected();
            }
        }
        return 0;
    }
    case WM_MBUTTONUP: {
        // Middle-click ends (closes) the task under the cursor.
        if (g_isVisible) {
            int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
            int idx = g_settings.showThumbnails ? HitTestThumb(x, y) : HitTest(x, y);
            if (idx < 0) idx = HitTest(x, y);
            if (idx >= 0) CloseSwitcherEntry(idx);
        }
        return 0;
    }
    case WM_ACTIVATE:
        if (wParam == WA_INACTIVE && g_isVisible) {
            HWND hNewActive = (HWND)lParam;
            if (!IsSwitcherWindow(hNewActive)) {
                HideSwitcher();
            }
            return 0;
        }
        break;
    case WM_KILLFOCUS:
        if (g_isVisible) {
            HWND hNewFocus = (HWND)wParam;
            if (!IsSwitcherWindow(hNewFocus)) {
                HideSwitcher();
            }
            return 0;
        }
        break;
    case WM_ERASEBKGND: return 1;
    case WM_DESTROY: UnregisterThumbnails(); return 0;
    }

    if (g_shellHookMsg && uMsg == g_shellHookMsg && g_isVisible) {
        int code = (int)(wParam & 0x7FFF);
        if (code == HSHELL_WINDOWDESTROYED) {
            HWND hS = (HWND)lParam;
            for (int i = 0; i < (int)g_windows.size(); i++)
                if (g_windows[i].hWnd == hS) { ShowSwitcher(g_isSticky); break; }
        }
        return 0;
    }
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

// Hotkey Helpers

static HANDLE g_hHotkeyMutex = NULL;

static void SWS_RegisterHotkeys() {
    if (g_hotkeysRegistered || !g_hSwitcher) return;
    bool wantAltBacktick = (wcscmp(g_settings.altBacktickBehavior, L"none") != 0) || BackwardShortcutIs(L"altBacktick");
    BOOL r1 = RegisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTTAB, MOD_ALT, VK_TAB);
    BOOL r2 = RegisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTSHIFTTAB, MOD_ALT | MOD_SHIFT, VK_TAB);
    BOOL r3 = RegisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTCTRLTAB, MOD_ALT | MOD_CONTROL, VK_TAB);
    BOOL r4 = RegisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTSHIFTCTRLTAB, MOD_ALT | MOD_SHIFT | MOD_CONTROL, VK_TAB);
    BOOL r5 = wantAltBacktick ? RegisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTBACKTICK, MOD_ALT, VK_OEM_3) : TRUE;
    BOOL r6 = RegisterHotKey(g_hSwitcher, SWS_HOTKEY_WINALTTAB, MOD_ALT | MOD_WIN, VK_TAB);
    BOOL r7 = RegisterHotKey(g_hSwitcher, SWS_HOTKEY_WINALTSHIFTTAB, MOD_ALT | MOD_SHIFT | MOD_WIN, VK_TAB);
    if (r1 && r2 && r3 && r4 && r5 && r6 && r7) {
        g_hotkeysRegistered = true;
        if (!g_hHotkeyMutex) {
            g_hHotkeyMutex = CreateMutexW(NULL, TRUE, L"Windhawk_SWSPlus_HotkeyMutex");
        }
        KillTimer(g_hSwitcher, SWS_HOTKEY_RETRY_TIMER_ID);
        Wh_Log(L"All hotkeys registered successfully");
    } else {
        if (r1) UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTTAB);
        if (r2) UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTSHIFTTAB);
        if (r3) UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTCTRLTAB);
        if (r4) UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTSHIFTCTRLTAB);
        if (wantAltBacktick && r5) UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTBACKTICK);
        if (r6) UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_WINALTTAB);
        if (r7) UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_WINALTSHIFTTAB);
        SetTimer(g_hSwitcher, SWS_HOTKEY_RETRY_TIMER_ID, SWS_HOTKEY_RETRY_INTERVAL, NULL);
        Wh_Log(L"Hotkey registration incomplete, retrying in %dms", SWS_HOTKEY_RETRY_INTERVAL);
    }
}
static void SWS_UnregisterHotkeys() {
    KillTimer(g_hSwitcher, SWS_HOTKEY_RETRY_TIMER_ID);
    if (!g_hotkeysRegistered || !g_hSwitcher) return;
    UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTTAB);
    UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTSHIFTTAB);
    UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTCTRLTAB);
    UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTSHIFTCTRLTAB);
    UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_ALTBACKTICK);
    UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_WINALTTAB);
    UnregisterHotKey(g_hSwitcher, SWS_HOTKEY_WINALTSHIFTTAB);
    g_hotkeysRegistered = false;
    if (g_hHotkeyMutex) {
        ReleaseMutex(g_hHotkeyMutex);
        CloseHandle(g_hHotkeyMutex);
        g_hHotkeyMutex = NULL;
    }
    Wh_Log(L"Hotkeys unregistered");
}


// Settings

template <size_t N>
static void LoadStringSetting(LPCWSTR settingName, WCHAR (&dest)[N], LPCWSTR defaultVal) {
    LPCWSTR v = Wh_GetStringSetting(settingName);
    wcsncpy_s(dest, (v && *v) ? v : defaultVal, _TRUNCATE);
    Wh_FreeStringSetting(v);
}

static void LoadSettings() {
    LPCWSTR v;
    LoadStringSetting(L"Style.theme", g_settings.theme, L"none");
    LoadStringSetting(L"Style.colorScheme", g_settings.colorScheme, L"system");
    LoadStringSetting(L"Appearance.Corners.cornerPreference", g_settings.cornerPreference, L"round");
    g_settings.customCornerRadius = Wh_GetIntSetting(L"Appearance.Corners.customCornerRadius");
    if (g_settings.customCornerRadius < 0) g_settings.customCornerRadius = 0;
    if (g_settings.customCornerRadius > 32) g_settings.customCornerRadius = 32;
    g_settings.taskRoundedCorners = Wh_GetIntSetting(L"Appearance.Corners.taskRoundedCorners");
    g_settings.roundThumbnailCorners = Wh_GetIntSetting(L"Appearance.Corners.roundThumbnailCorners");
    g_settings.roundGroupIndicator = Wh_GetIntSetting(L"Appearance.Corners.roundGroupIndicator");
    g_settings.roundBadgeIconBackground = Wh_GetIntSetting(L"Appearance.Corners.roundBadgeIconBackground");
    LoadStringSetting(L"Accessibility.scrollWheelBehavior", g_settings.scrollWheelBehavior, L"never");
    LoadStringSetting(L"Accessibility.scrollWheelAction", g_settings.scrollWheelAction, L"selection");
    LoadStringSetting(L"Accessibility.scrollSecondaryAction", g_settings.scrollSecondaryAction, L"page");
    LoadStringSetting(L"Accessibility.scrollSecondaryModifier", g_settings.scrollSecondaryModifier, L"shift");
    LoadStringSetting(L"Appearance.Orientation.taskListOrientation", g_settings.taskListOrientation, L"horizontal");
    LoadStringSetting(L"Appearance.Orientation.headerContentOrientation", g_settings.headerContentOrientation, L"horizontal");
    if (wcscmp(g_settings.headerContentOrientation, L"horizontal") != 0 &&
        wcscmp(g_settings.headerContentOrientation, L"vertical") != 0) {
        wcsncpy_s(g_settings.headerContentOrientation, L"horizontal", _TRUNCATE);
    }

    LoadStringSetting(L"Appearance.Position.switcherPosition", g_settings.switcherPosition, L"center");
    if (wcscmp(g_settings.switcherPosition, L"topLeft") != 0 &&
        wcscmp(g_settings.switcherPosition, L"topCenter") != 0 &&
        wcscmp(g_settings.switcherPosition, L"topRight") != 0 &&
        wcscmp(g_settings.switcherPosition, L"centerLeft") != 0 &&
        wcscmp(g_settings.switcherPosition, L"center") != 0 &&
        wcscmp(g_settings.switcherPosition, L"centerRight") != 0 &&
        wcscmp(g_settings.switcherPosition, L"bottomLeft") != 0 &&
        wcscmp(g_settings.switcherPosition, L"bottomCenter") != 0 &&
        wcscmp(g_settings.switcherPosition, L"bottomRight") != 0) {
        wcsncpy_s(g_settings.switcherPosition, L"center", _TRUNCATE);
    }
    g_settings.switcherPositionMargin = Wh_GetIntSetting(L"Appearance.Position.switcherPositionMargin");
    if (g_settings.switcherPositionMargin < 0) g_settings.switcherPositionMargin = 0;
    LoadStringSetting(L"Appearance.HeaderContent.iconSize", g_settings.iconSize, L"small");
    if (wcscmp(g_settings.iconSize, L"small") != 0 &&
        wcscmp(g_settings.iconSize, L"medium") != 0 &&
        wcscmp(g_settings.iconSize, L"large") != 0 &&
        wcscmp(g_settings.iconSize, L"xlarge") != 0) {
        wcsncpy_s(g_settings.iconSize, L"small", _TRUNCATE);
    }
    LoadStringSetting(L"Appearance.Thumbnails.thumbnailPosition", g_settings.thumbnailPosition, L"bottom");
    if (wcscmp(g_settings.thumbnailPosition, L"bottom") != 0 &&
        wcscmp(g_settings.thumbnailPosition, L"top") != 0 &&
        wcscmp(g_settings.thumbnailPosition, L"left") != 0 &&
        wcscmp(g_settings.thumbnailPosition, L"right") != 0) {
        wcsncpy_s(g_settings.thumbnailPosition, L"bottom", _TRUNCATE);
    }
    LoadStringSetting(L"Appearance.Thumbnails.thumbnailAlignment", g_settings.thumbnailAlignment, L"left");
    if (wcscmp(g_settings.thumbnailAlignment, L"left") != 0 &&
        wcscmp(g_settings.thumbnailAlignment, L"centered") != 0 &&
        wcscmp(g_settings.thumbnailAlignment, L"right") != 0) {
        wcsncpy_s(g_settings.thumbnailAlignment, L"left", _TRUNCATE);
    }
    LoadStringSetting(L"Accessibility.backwardShortcut", g_settings.backwardShortcut, L"altShiftTab");
    if (wcscmp(g_settings.backwardShortcut, L"altShiftTab") != 0 &&
        wcscmp(g_settings.backwardShortcut, L"altShift") != 0 &&
        wcscmp(g_settings.backwardShortcut, L"altBacktick") != 0) {
        wcsncpy_s(g_settings.backwardShortcut, L"altShiftTab", _TRUNCATE);
    }

    LoadStringSetting(L"Accessibility.altBacktickBehavior", g_settings.altBacktickBehavior, L"backward");
    if (wcscmp(g_settings.altBacktickBehavior, L"none") != 0 &&
        wcscmp(g_settings.altBacktickBehavior, L"backward") != 0 &&
        wcscmp(g_settings.altBacktickBehavior, L"sameApp") != 0) {
        wcsncpy_s(g_settings.altBacktickBehavior, L"backward", _TRUNCATE);
    }

    LoadStringSetting(L"Accessibility.virtualDesktopBehavior", g_settings.virtualDesktopBehavior, L"allDesktops");
    if (wcscmp(g_settings.virtualDesktopBehavior, L"currentOnly") != 0 &&
        wcscmp(g_settings.virtualDesktopBehavior, L"allDesktops") != 0) {
        wcsncpy_s(g_settings.virtualDesktopBehavior, L"allDesktops", _TRUNCATE);
    }

    g_settings.rowHeight = Wh_GetIntSetting(L"Dimensions.rowHeight");
    if (g_settings.rowHeight <= 0) g_settings.rowHeight = 230;
    g_settings.rowWidth = Wh_GetIntSetting(L"Dimensions.rowWidth");
    if (g_settings.rowWidth < 0) g_settings.rowWidth = 0;
    g_settings.stretchThumbnailsToTaskWidth = Wh_GetIntSetting(L"Dimensions.stretchThumbnailsToTaskWidth");
    g_settings.autoFitTasks = Wh_GetIntSetting(L"Dimensions.autoFitTasks");
    g_settings.showThumbnails = Wh_GetIntSetting(L"Appearance.Thumbnails.showThumbnails");
    g_settings.showCloseButton = Wh_GetIntSetting(L"Appearance.Thumbnails.showCloseButton");
    g_settings.showOverflowIndicator = Wh_GetIntSetting(L"Appearance.showOverflowIndicator");
    g_settings.showHoverBorder = Wh_GetIntSetting(L"Appearance.Thumbnails.showHoverBorder");
    g_settings.showThumbnailShadow = Wh_GetIntSetting(L"Appearance.Thumbnails.showThumbnailShadow");
    g_settings.showTitle = Wh_GetIntSetting(L"Appearance.HeaderContent.showTitle");
    g_settings.showIcon = Wh_GetIntSetting(L"Appearance.HeaderContent.showIcon");
    if (!g_settings.showThumbnails && !g_settings.showTitle && !g_settings.showIcon) {
        g_settings.showTitle = true;
    }
    g_settings.maxWidthPercent = Wh_GetIntSetting(L"Dimensions.maxWidthPercent");
    if (g_settings.maxWidthPercent <= 0 || g_settings.maxWidthPercent > 100) g_settings.maxWidthPercent = 80;
    g_settings.maxHeightPercent = Wh_GetIntSetting(L"Dimensions.maxHeightPercent");
    if (g_settings.maxHeightPercent <= 0 || g_settings.maxHeightPercent > 100) g_settings.maxHeightPercent = 80;

    g_settings.showDelay = Wh_GetIntSetting(L"Accessibility.showDelay");
    if (g_settings.showDelay < 0) g_settings.showDelay = 0;
    g_settings.perMonitorWindows = Wh_GetIntSetting(L"Accessibility.perMonitorWindows");
    g_settings.reverseScrollDirection = Wh_GetIntSetting(L"Accessibility.reverseScrollDirection");
    g_settings.showApplications = Wh_GetIntSetting(L"Grouping.showApplications");
    g_settings.restoreAllWindows = Wh_GetIntSetting(L"Grouping.restoreAllWindows");
    g_settings.hideMinimizedWindows = Wh_GetIntSetting(L"Accessibility.hideMinimizedWindows");
    g_settings.sortMinimizedWindowsToEnd = Wh_GetIntSetting(L"Accessibility.sortMinimizedWindowsToEnd");
    LoadStringSetting(L"Grouping.showTitles", g_settings.showTitles, L"windowTitle");
    if (wcscmp(g_settings.showTitles, L"windowTitle") != 0 &&
        wcscmp(g_settings.showTitles, L"appName") != 0 &&
        wcscmp(g_settings.showTitles, L"appNameWindowTitle") != 0) {
        wcsncpy_s(g_settings.showTitles, L"windowTitle", _TRUNCATE);
    }
    g_settings.centerTaskContent = Wh_GetIntSetting(L"Appearance.HeaderContent.centerTaskContent");

    // Badge layout settings
    g_settings.enableBadgeLayout = Wh_GetIntSetting(L"Appearance.BadgeLayout.enableBadgeLayout");
    LoadStringSetting(L"Appearance.BadgeLayout.badgeIconPosition", g_settings.badgeIconPosition, L"bottomCenter");
    if (wcscmp(g_settings.badgeIconPosition, L"topLeft") != 0 &&
        wcscmp(g_settings.badgeIconPosition, L"topCenter") != 0 &&
        wcscmp(g_settings.badgeIconPosition, L"topRight") != 0 &&
        wcscmp(g_settings.badgeIconPosition, L"centerLeft") != 0 &&
        wcscmp(g_settings.badgeIconPosition, L"center") != 0 &&
        wcscmp(g_settings.badgeIconPosition, L"centerRight") != 0 &&
        wcscmp(g_settings.badgeIconPosition, L"bottomLeft") != 0 &&
        wcscmp(g_settings.badgeIconPosition, L"bottomCenter") != 0 &&
        wcscmp(g_settings.badgeIconPosition, L"bottomRight") != 0) {
        wcsncpy_s(g_settings.badgeIconPosition, L"bottomCenter", _TRUNCATE);
    }
    LoadStringSetting(L"Appearance.BadgeLayout.badgeTitlePosition", g_settings.badgeTitlePosition, L"bottom");
    if (wcscmp(g_settings.badgeTitlePosition, L"top") != 0 &&
        wcscmp(g_settings.badgeTitlePosition, L"bottom") != 0) {
        wcsncpy_s(g_settings.badgeTitlePosition, L"bottom", _TRUNCATE);
    }
    g_settings.showBadgeIconBackground = Wh_GetIntSetting(L"Appearance.BadgeLayout.showBadgeIconBackground");
    g_settings.showBadgeIconBackgroundShadow = Wh_GetIntSetting(L"Appearance.BadgeLayout.showBadgeIconBackgroundShadow");
    g_settings.badgeIconPadding = Wh_GetIntSetting(L"Appearance.BadgeLayout.badgeIconPadding");
    g_settings.badgeIconOffsetX = Wh_GetIntSetting(L"Appearance.BadgeLayout.badgeIconOffsetX");
    g_settings.badgeIconOffsetY = Wh_GetIntSetting(L"Appearance.BadgeLayout.badgeIconOffsetY");

    // Grouped indicator
    g_settings.showGroupIndicator = Wh_GetIntSetting(L"Grouping.showGroupIndicator");
    g_settings.showGroupIndicatorShadow = Wh_GetIntSetting(L"Grouping.showGroupIndicatorShadow");
    LoadStringSetting(L"Grouping.groupCloseBehavior", g_settings.groupCloseBehavior, L"closeRecent");
    if (wcscmp(g_settings.groupCloseBehavior, L"closeAll") != 0 &&
        wcscmp(g_settings.groupCloseBehavior, L"closeRecent") != 0) {
        wcsncpy_s(g_settings.groupCloseBehavior, L"closeRecent", _TRUNCATE);
    }

    // Global theme settings (apply to both light and dark)
    LoadStringSetting(L"Style.highlightStyle", g_settings.highlightStyle, L"border");
    if (wcscmp(g_settings.highlightStyle, L"border") != 0 &&
        wcscmp(g_settings.highlightStyle, L"fillAndBorder") != 0 &&
        wcscmp(g_settings.highlightStyle, L"fillOnly") != 0) {
        wcsncpy_s(g_settings.highlightStyle, L"border", _TRUNCATE);
    }
    g_settings.opacity = Wh_GetIntSetting(L"Style.opacity");
    if (g_settings.opacity < 0) g_settings.opacity = 0;
    if (g_settings.opacity > 100) g_settings.opacity = 100;

    // Dark Mode color settings
    LoadStringSetting(L"Style.DarkMode.borderColorMode", g_settings.borderColorModeDark, L"default");
    LoadStringSetting(L"Style.DarkMode.highlightFillColorMode", g_settings.highlightFillColorModeDark, L"default");
    LoadStringSetting(L"Style.DarkMode.bgColorMode", g_settings.bgColorModeDark, L"default");
    LoadStringSetting(L"Style.DarkMode.customBorderColor", g_settings.customBorderColorDark, L"#FFFFFF");
    LoadStringSetting(L"Style.DarkMode.customHighlightFillColor", g_settings.customHighlightFillColorDark, L"#FFFFFF");
    LoadStringSetting(L"Style.DarkMode.customBgColor", g_settings.customBgColorDark, L"#202020");

    LoadStringSetting(L"Style.DarkMode.iconBgColorMode", g_settings.iconBgColorModeDark, L"default");
    LoadStringSetting(L"Style.DarkMode.customIconBgColor", g_settings.customIconBgColorDark, L"#000000");
    g_settings.iconBgOpacityDark = Wh_GetIntSetting(L"Style.DarkMode.iconBgOpacity");
    if (g_settings.iconBgOpacityDark < 0) g_settings.iconBgOpacityDark = 0;
    if (g_settings.iconBgOpacityDark > 100) g_settings.iconBgOpacityDark = 100;

    LoadStringSetting(L"Style.DarkMode.indicatorBgColorMode", g_settings.indicatorBgColorModeDark, L"default");
    LoadStringSetting(L"Style.DarkMode.customIndicatorBgColor", g_settings.customIndicatorBgColorDark, L"#333333");
    g_settings.indicatorBgOpacityDark = Wh_GetIntSetting(L"Style.DarkMode.indicatorBgOpacity");
    if (g_settings.indicatorBgOpacityDark < 0) g_settings.indicatorBgOpacityDark = 0;
    if (g_settings.indicatorBgOpacityDark > 100) g_settings.indicatorBgOpacityDark = 100;

    LoadStringSetting(L"Style.DarkMode.indicatorTextColorMode", g_settings.indicatorTextColorModeDark, L"default");
    LoadStringSetting(L"Style.DarkMode.customIndicatorTextColor", g_settings.customIndicatorTextColorDark, L"#FFFFFF");

    // Light Mode color settings
    LoadStringSetting(L"Style.LightMode.borderColorMode", g_settings.borderColorModeLight, L"default");
    LoadStringSetting(L"Style.LightMode.highlightFillColorMode", g_settings.highlightFillColorModeLight, L"default");
    LoadStringSetting(L"Style.LightMode.bgColorMode", g_settings.bgColorModeLight, L"default");
    LoadStringSetting(L"Style.LightMode.customBorderColor", g_settings.customBorderColorLight, L"#000000");
    LoadStringSetting(L"Style.LightMode.customHighlightFillColor", g_settings.customHighlightFillColorLight, L"#000000");
    LoadStringSetting(L"Style.LightMode.customBgColor", g_settings.customBgColorLight, L"#F3F3F3");

    LoadStringSetting(L"Style.LightMode.iconBgColorMode", g_settings.iconBgColorModeLight, L"default");
    LoadStringSetting(L"Style.LightMode.customIconBgColor", g_settings.customIconBgColorLight, L"#FFFFFF");
    g_settings.iconBgOpacityLight = Wh_GetIntSetting(L"Style.LightMode.iconBgOpacity");
    if (g_settings.iconBgOpacityLight < 0) g_settings.iconBgOpacityLight = 0;
    if (g_settings.iconBgOpacityLight > 100) g_settings.iconBgOpacityLight = 100;

    LoadStringSetting(L"Style.LightMode.indicatorBgColorMode", g_settings.indicatorBgColorModeLight, L"default");
    LoadStringSetting(L"Style.LightMode.customIndicatorBgColor", g_settings.customIndicatorBgColorLight, L"#EAEAEA");
    g_settings.indicatorBgOpacityLight = Wh_GetIntSetting(L"Style.LightMode.indicatorBgOpacity");
    if (g_settings.indicatorBgOpacityLight < 0) g_settings.indicatorBgOpacityLight = 0;
    if (g_settings.indicatorBgOpacityLight > 100) g_settings.indicatorBgOpacityLight = 100;

    LoadStringSetting(L"Style.LightMode.indicatorTextColorMode", g_settings.indicatorTextColorModeLight, L"default");
    LoadStringSetting(L"Style.LightMode.customIndicatorTextColor", g_settings.customIndicatorTextColorLight, L"#000000");

    LoadStringSetting(L"Appearance.Font.fontFamily", g_settings.fontFamily, L"Segoe UI");

    g_settings.fontSize = Wh_GetIntSetting(L"Appearance.Font.fontSize");
    if (g_settings.fontSize <= 0) g_settings.fontSize = 9;

    LoadStringSetting(L"Appearance.Font.fontStyle", g_settings.fontStyle, L"regular");

    g_settings.applyToGroupIndicator = Wh_GetIntSetting(L"Appearance.Font.applyToGroupIndicator");

    LoadStringSetting(L"Accessibility.switcherDisplayBehavior", g_settings.switcherDisplayBehavior, L"cursorMonitor");

    // Exclusion patterns (newline-delimited text fields)
    g_excludeTitlePatterns.clear();
    g_excludeExePatterns.clear();

    v = Wh_GetStringSetting(L"ExcludedWindows.excludeByTitle");
    if (v && *v) {
        std::wstring valStr(v);
        size_t start = 0;
        while (start < valStr.length()) {
            size_t end = valStr.find(L';', start);
            if (end == std::wstring::npos) end = valStr.length();
            std::wstring token = valStr.substr(start, end - start);
            size_t first = token.find_first_not_of(L" \t\r\n");
            if (first != std::wstring::npos) {
                token = token.substr(first);
                size_t last = token.find_last_not_of(L" \t\r\n");
                token = token.substr(0, last + 1);
                if (!token.empty()) g_excludeTitlePatterns.push_back(token);
            }
            start = end + 1;
        }
    }
    if (v) Wh_FreeStringSetting(v);

    v = Wh_GetStringSetting(L"ExcludedWindows.excludeByExe");
    if (v && *v) {
        std::wstring valStr(v);
        size_t start = 0;
        while (start < valStr.length()) {
            size_t end = valStr.find(L';', start);
            if (end == std::wstring::npos) end = valStr.length();
            std::wstring token = valStr.substr(start, end - start);
            size_t first = token.find_first_not_of(L" \t\r\n");
            if (first != std::wstring::npos) {
                token = token.substr(first);
                size_t last = token.find_last_not_of(L" \t\r\n");
                token = token.substr(0, last + 1);
                if (!token.empty()) g_excludeExePatterns.push_back(token);
            }
            start = end + 1;
        }
    }
    if (v) Wh_FreeStringSetting(v);

    // Custom per-process header (array of { process, iconPath, appName }).
    g_customHeaderRules.clear();
    auto trimWs = [](std::wstring s) -> std::wstring {
        size_t a = s.find_first_not_of(L" \t\r\n");
        if (a == std::wstring::npos) return L"";
        size_t b = s.find_last_not_of(L" \t\r\n");
        return s.substr(a, b - a + 1);
    };
    for (int i = 0; ; i++) {
        PCWSTR proc = Wh_GetStringSetting(L"customHeader[%d].process", i);
        PCWSTR icon = Wh_GetStringSetting(L"customHeader[%d].iconPath", i);
        PCWSTR name = Wh_GetStringSetting(L"customHeader[%d].appName", i);
        bool hasProc = proc && *proc;
        bool hasIcon = icon && *icon;
        bool hasName = name && *name;
        if (hasProc && (hasIcon || hasName)) {
            std::wstring p = trimWs(proc);
            std::wstring ip = hasIcon ? trimWs(icon) : L"";
            std::wstring an = hasName ? trimWs(name) : L"";
            if (!p.empty() && (!ip.empty() || !an.empty()))
                g_customHeaderRules.push_back({p, ip, an});
        }
        bool endOfArray = !hasProc && !hasIcon && !hasName;
        if (proc) Wh_FreeStringSetting(proc);
        if (icon) Wh_FreeStringSetting(icon);
        if (name) Wh_FreeStringSetting(name);
        if (endOfArray) break;
    }
}


// RegisterHotKey hook for explorer.exe

static bool SWS_IsAltTabHotkey(UINT fsModifiers, UINT vk) {
    UINT baseMods = fsModifiers & ~MOD_NOREPEAT;
    if (vk == VK_TAB && (baseMods & MOD_ALT)) return true;
    return false;
}

typedef BOOL(WINAPI *RegisterHotKey_t)(HWND hWnd, int id, UINT fsModifiers, UINT vk);
static RegisterHotKey_t RegisterHotKey_Original;

static BOOL WINAPI RegisterHotKey_Hook(HWND hWnd, int id, UINT fsModifiers, UINT vk) {
    if (SWS_IsAltTabHotkey(fsModifiers, vk)) {
        Wh_Log(L"Blocked explorer RegisterHotKey for Alt+Tab variant (vk=0x%X, mod=0x%X)", vk, fsModifiers);
        SetLastError(0);
        return TRUE;
    }
    return RegisterHotKey_Original(hWnd, id, fsModifiers, vk);
}

// Background thread for tool mod process

static DWORD WINAPI SwitcherThread(LPVOID lpParam) {
    Wh_Log(L"SwitcherThread starting");
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    // Create the virtual desktop manager on this thread so it lives in the same
    // apartment that uses it (EnumWindowsProc runs here). An STA interface
    // pointer is only valid in the apartment that created it.
    CoCreateInstance(CLSID_VirtualDesktopManager, nullptr, CLSCTX_INPROC_SERVER,
                     IID_IVirtualDesktopManager, (void**)&g_pVirtualDesktopManager);
    ResolveAPIs();
    LoadSettings();
    g_isDarkMode = ShouldUseDarkMode();

    BufferedPaintInit();

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&g_gdiplusToken, &gdiplusStartupInput, NULL);

    WNDCLASSEXW wc = { sizeof(wc) };
    wc.lpfnWndProc = SwitcherWndProc;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpszClassName = SWS_CLASSNAME;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.style = CS_DBLCLKS;
    RegisterClassExW(&wc);

    // Use WS_POPUP | WS_THICKFRAME to get DWM rounded corners and shadows,
    // without the system caption buttons. We remove the frame via WM_NCCALCSIZE.
    DWORD dwStyle = WS_POPUP | WS_THICKFRAME | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
    DWORD exStyle = WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED;
    g_hSwitcher = CreateWindowExW(exStyle, SWS_CLASSNAME, L"",
        dwStyle, -9999, -9999, 1, 1, NULL, NULL, GetModuleHandleW(NULL), NULL);
    if (g_hSwitcher) ChangeWindowMessageFilterEx(g_hSwitcher, WM_HOTKEY, MSGFLT_ALLOW, nullptr);
    if (!g_hSwitcher) { Wh_Log(L"Failed to create switcher window"); return 1; }

    g_hCloseBtnWnd = CreateWindowExW(
        WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT,
        SWS_CLASSNAME, L"",
        WS_POPUP, 0, 0, 0, 0, g_hSwitcher, NULL, GetModuleHandleW(NULL), NULL);

    BOOL bExclude = TRUE;
    DwmSetWindowAttribute(g_hSwitcher, DWMWA_EXCLUDED_FROM_PEEK, &bExclude, sizeof(bExclude));

    g_hTheme = OpenThemeData(NULL, L"CompositedWindow::Window");
    g_shellHookMsg = RegisterWindowMessageW(L"SHELLHOOK");
    RegisterShellHookWindow(g_hSwitcher);

    g_hFont = CreateScaledFont(96);

    SWS_RegisterHotkeys();

    Wh_Log(L"Simple Window Switcher initialized, entering message loop");

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    SWS_UnregisterHotkeys();
    if (g_isVisible) HideSwitcher();
    UnregisterThumbnails();
    g_windows.clear();
    if (g_hCloseBtnWnd) { DestroyWindow(g_hCloseBtnWnd); g_hCloseBtnWnd = NULL; }
    if (g_hSwitcher) { DeregisterShellHookWindow(g_hSwitcher); DestroyWindow(g_hSwitcher); g_hSwitcher = NULL; }
    UnregisterClassW(SWS_CLASSNAME, GetModuleHandleW(NULL));
    if (g_hFont) { DeleteObject(g_hFont); g_hFont = NULL; }
    if (g_hTheme) { CloseThemeData(g_hTheme); g_hTheme = NULL; }
    BufferedPaintUnInit();
    if (g_gdiplusToken) {
        Gdiplus::GdiplusShutdown(g_gdiplusToken);
        g_gdiplusToken = 0;
    }

    if (g_pVirtualDesktopManager) {
        g_pVirtualDesktopManager->Release();
        g_pVirtualDesktopManager = NULL;
    }
    CoUninitialize();
    Wh_Log(L"SwitcherThread exiting");
    return 0;
}

// Tool Mod callbacks

BOOL WhTool_ModInit() {
    Wh_Log(L"Simple Window Switcher: WhTool_ModInit");
    g_hSwitcherThread = CreateThread(NULL, 0, SwitcherThread, NULL, 0, &g_dwSwitcherThreadId);
    return g_hSwitcherThread != NULL;
}

void WhTool_ModUninit() {
    Wh_Log(L"Simple Window Switcher: WhTool_ModUninit");
    while (g_dwSwitcherThreadId &&
           !PostThreadMessage(g_dwSwitcherThreadId, WM_QUIT, 0, 0)) {
        if (GetLastError() != ERROR_INVALID_THREAD_ID) break;
        if (WaitForSingleObject(g_hSwitcherThread, 10) != WAIT_TIMEOUT) break;
    }
    if (g_hSwitcherThread) {
        WaitForSingleObject(g_hSwitcherThread, INFINITE);
        CloseHandle(g_hSwitcherThread);
        g_hSwitcherThread = NULL;
        g_dwSwitcherThreadId = 0;
    }
    for (auto& pair : g_uwpIconCache) {
        if (pair.second) DestroyIcon(pair.second);
    }
    g_uwpIconCache.clear();
    for (auto& pair : g_exeIconCache) {
        if (pair.second) DestroyIcon(pair.second);
    }
    g_exeIconCache.clear();
    for (auto& pair : g_customIconCache) {
        if (pair.second) DestroyIcon(pair.second);
    }
    g_customIconCache.clear();
}

void WhTool_ModSettingsChanged() {
    Wh_Log(L"Simple Window Switcher: WhTool_ModSettingsChanged");
    if (g_hSwitcher) {
        PostMessage(g_hSwitcher, WM_SWS_SETTINGS_CHANGED, 0, 0);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Windhawk tool mod boilerplate
// https://github.com/ramensoftware/windhawk/wiki/Mods-as-tools:-Running-mods-in-a-dedicated-process

bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;

void WINAPI EntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

////////////////////////////////////////////////////////////////////////////////
// Windhawk lifecycle

static bool IsMainExplorer() {
    HWND hTaskbar = FindWindowW(L"Shell_TrayWnd", NULL);
    if (hTaskbar) {
        DWORD trayPid = 0;
        GetWindowThreadProcessId(hTaskbar, &trayPid);
        if (trayPid != GetCurrentProcessId()) {
            return false;
        }
    }
    return true;
}




}
namespace Vista {





namespace wgc = winrt::Windows::Graphics::Capture;
namespace wgdx = winrt::Windows::Graphics::DirectX;
namespace wgd3d = winrt::Windows::Graphics::DirectX::Direct3D11;
using winrt::com_ptr;

namespace {

// The llvm-mingw SDK doesn't ship windows.graphics.directx.direct3d11.interop.h,
// so the interop pieces needed here are declared manually.
struct IDirect3DDxgiInterfaceAccess : public IUnknown {
    virtual HRESULT STDMETHODCALLTYPE GetInterface(REFIID iid, void** p) = 0;
};
constexpr GUID kIID_IDirect3DDxgiInterfaceAccess = {
    0xa9b3d012,
    0x3df2,
    0x4ee3,
    {0xb8, 0xd1, 0x86, 0x95, 0xf4, 0x57, 0xd3, 0xc1}};
constexpr GUID kIID_IGraphicsCaptureItemInterop = {
    0x3628e81b,
    0x3cac,
    0x4c60,
    {0xb7, 0xf4, 0x23, 0xce, 0x0e, 0x0c, 0x33, 0x56}};
constexpr GUID kCLSID_DesktopWallpaper = {
    0xc2cf3110,
    0x460e,
    0x4fc1,
    {0xb9, 0xd0, 0x8a, 0x1c, 0x0c, 0x9c, 0xc4, 0xbd}};
// Used to find the icons of packaged (UWP) apps.
constexpr GUID kFOLDERID_AppsFolder = {
    0x1e87508d,
    0x89c2,
    0x42f0,
    {0x8a, 0x7e, 0x64, 0x5a, 0x0f, 0x50, 0xca, 0x58}};
constexpr PROPERTYKEY kPKEY_AppUserModel_ID = {
    {0x9f4c2855,
     0x9f79,
     0x4b39,
     {0xa8, 0xd0, 0xe1, 0xd4, 0x2d, 0xe1, 0xd5, 0xf3}},
    5};

using CreateDirect3D11DeviceFromDXGIDevice_t = HRESULT(WINAPI*)(IDXGIDevice*,
                                                                ::IInspectable**);

// Effect property values missing from the llvm-mingw d2d1effects.h, as
// documented in the Windows SDK.
constexpr UINT32 kTransform3DPropInterpolationMode = 0;
constexpr UINT32 kTransform3DPropBorderMode = 1;
constexpr UINT32 kTransform3DPropTransformMatrix = 2;
constexpr UINT32 kTransform3DInterpolationAnisotropic = 4;
constexpr UINT32 kShadowOptimizationSpeed = 0;
constexpr UINT32 kGaussianBlurOptimizationQuality = 2;

// Messages posted from the hook thread to the overlay window.
constexpr UINT WM_APP_START = WM_APP + 1;   // wParam: kStart* flags
constexpr UINT WM_APP_STEP = WM_APP + 2;    // wParam: signed step
constexpr UINT WM_APP_WHEEL = WM_APP + 3;   // wParam: signed wheel delta
constexpr UINT WM_APP_COMMIT = WM_APP + 4;  // switch to the front window
constexpr UINT WM_APP_CANCEL = WM_APP + 5;  // go back without switching
constexpr UINT WM_APP_SETTINGS = WM_APP + 6;
constexpr UINT WM_APP_CLOSE_SELECTED = WM_APP + 8;
constexpr UINT WM_APP_REFRESH_ICONS = WM_APP + 7;  // Posted to itself.

constexpr WPARAM kStartBackwards = 1;
// Started from explorer's own Alt+Tab hotkey: the keyboard hook didn't see
// the keys, usually because an elevated window has the focus.
constexpr WPARAM kStartFromHotkey = 2;

// The explorer thread that receives the Alt+Tab hotkey, found by its name.
// Until it's found, it's looked for again, less and less often (see
// ExplorerThreadProc).
constexpr PCWSTR kAltTabThreadName = L"Immersive Shell";
constexpr DWORD kFindAltTabThreadIntervalMs = 2000;
constexpr DWORD kFindAltTabThreadMaxIntervalMs = 60000;
// How often explorer checks whether the taskbar has been created yet.
constexpr DWORD kWaitForTaskbarIntervalMs = 1000;

// Thread messages handled by the hook thread.
constexpr UINT WM_HOOK_ENGAGE = WM_APP + 20;
constexpr UINT WM_HOOK_DISENGAGE = WM_APP + 21;
// Installs or removes the keyboard hook, following g_takeOver.
constexpr UINT WM_HOOK_UPDATE = WM_APP + 22;

// Marks input injected by this mod, so the hooks can ignore it.
constexpr ULONG_PTR kInjectedInputTag = 0x46334453;
// Unassigned virtual key, used to stop Alt from activating menu bars.
constexpr WORD kDummyVk = 0xE8;

constexpr WCHAR kOverlayClassName[] = L"WindhawkSWSPlusVistaOverlay";
constexpr WCHAR kProxyClassName[] = L"WindhawkSWSPlusVistaProxy";
// The overlay's title tells explorer whether the switcher can take over
// Alt+Tab right now. FindWindow compares titles without sending messages.
constexpr WCHAR kOverlayTitleIdle[] = L"Simple Window Switcher Plus";
constexpr WCHAR kOverlayTitleReady[] = L"Simple Window Switcher Plus (ready)";
// Posted by explorer to the overlay when it receives the Alt+Tab hotkey.
// wParam: kStartBackwards or 0.
constexpr WCHAR kHotkeyMessageName[] = L"WindhawkSWSPlusVista_Hotkey";

enum class AnimationStyle {
    Flip3D,
    Cascade,
    CoverFlow,
    Carousel,
    Grid,
    Helix,
    Fan,
    Panorama,
    Tunnel,
    Rolodex,
    Windows11,
    Thumbnails,
    IconRow,
    List,
    Classic,
    // The mod leaves Alt+Tab alone, and keeps no hooks or graphics devices.
    Native,
};
enum class MonitorMode { Cursor, ActiveWindow };
enum class BackgroundMode { BlurredWallpaper, Wallpaper, Dim };

struct Settings {
    AnimationStyle style;
    MonitorMode monitor;
    int animationDurationMs;
    float flipSpeed;
    int showDelayMs;
    float tiltRadians;
    float stackSpacing;
    int maxWindows;
    BackgroundMode background;
    float blurAmount;
    float dimOpacity;
    bool showTitle;
    bool shadows;
    bool includeMinimized;
    bool minimizedContent;
};

Settings LoadSettings() {
    Simple::LoadSettings();
    Simple::g_isDarkMode = Simple::ShouldUseDarkMode();
    Settings s;

    constexpr struct {
        PCWSTR name;
        AnimationStyle style;
    } kStyles[] = {
        {L"cascade", AnimationStyle::Cascade},
        {L"coverflow", AnimationStyle::CoverFlow},
        {L"carousel", AnimationStyle::Carousel},
        {L"grid", AnimationStyle::Grid},
        {L"helix", AnimationStyle::Helix},
        {L"fan", AnimationStyle::Fan},
        {L"panorama", AnimationStyle::Panorama},
        {L"tunnel", AnimationStyle::Tunnel},
        {L"rolodex", AnimationStyle::Rolodex},
        {L"windows11", AnimationStyle::Windows11},
        {L"thumbnails", AnimationStyle::Thumbnails},
        {L"icons", AnimationStyle::IconRow},
        {L"list", AnimationStyle::List},
        {L"classic", AnimationStyle::Classic},
        {L"native", AnimationStyle::Native},
    };
    const auto style = WindhawkUtils::StringSetting::make(L"style");
    s.style = AnimationStyle::Flip3D;
    for (const auto& entry : kStyles) {
        if (wcscmp(style, entry.name) == 0) {
            s.style = entry.style;
        }
    }

    const auto monitor = WindhawkUtils::StringSetting::make(L"monitor");
    s.monitor = wcscmp(monitor, L"activeWindow") == 0
                    ? MonitorMode::ActiveWindow
                    : MonitorMode::Cursor;

    s.animationDurationMs =
        std::clamp(Wh_GetIntSetting(L"animationDuration"), 50, 3000);
    s.flipSpeed = std::clamp(Wh_GetIntSetting(L"flipSpeed"), 25, 400) / 100.0f;
    s.showDelayMs = std::clamp(Wh_GetIntSetting(L"showDelay"), 0, 1000);
    s.tiltRadians = std::clamp(Wh_GetIntSetting(L"tiltAngle"), 0, 70) *
                    3.14159265f / 180.0f;
    s.stackSpacing =
        std::clamp(Wh_GetIntSetting(L"stackSpacing"), 40, 250) / 100.0f;
    s.maxWindows = std::clamp(Wh_GetIntSetting(L"maxWindows"), 2, 40);

    const auto background = WindhawkUtils::StringSetting::make(L"background");
    if (wcscmp(background, L"wallpaper") == 0) {
        s.background = BackgroundMode::Wallpaper;
    } else if (wcscmp(background, L"dim") == 0) {
        s.background = BackgroundMode::Dim;
    } else {
        s.background = BackgroundMode::BlurredWallpaper;
    }

    s.blurAmount = (float)std::clamp(Wh_GetIntSetting(L"blurAmount"), 1, 100);
    s.dimOpacity = std::clamp(Wh_GetIntSetting(L"dimOpacity"), 0, 90) / 100.0f;
    s.showTitle = Wh_GetIntSetting(L"showTitle") != 0 && Simple::g_settings.showTitle;
    s.shadows = Wh_GetIntSetting(L"shadows") != 0;
    s.includeMinimized = Wh_GetIntSetting(L"includeMinimized") != 0 && !Simple::g_settings.hideMinimizedWindows;
    s.minimizedContent = Wh_GetIntSetting(L"minimizedContent") != 0;
    return s;
}

HMODULE g_module;
// See kHotkeyMessageName.
UINT g_hotkeyMessage;
HANDLE g_uiThread;
DWORD g_uiThreadId;
HANDLE g_hookThread;
DWORD g_hookThreadId;
HWND g_overlayWnd;
HHOOK g_keyboardHook;  // Hook thread only.
HHOOK g_mouseHook;     // Hook thread only.

// The switcher is initialized and can take over Alt+Tab.
std::atomic<bool> g_ready;
// Alt+Tab is taken over (false with the native switcher style).
std::atomic<bool> g_takeOver;
// An Alt+Tab session is in progress (Alt is still held).
std::atomic<bool> g_switching;
std::atomic<bool> g_sticky;

bool IsPanelStyle(AnimationStyle style) {
    return style == AnimationStyle::Windows11 ||
           style == AnimationStyle::Thumbnails ||
           style == AnimationStyle::IconRow || style == AnimationStyle::List ||
           style == AnimationStyle::Classic;
}

double NowSeconds() {
    static const double frequency = [] {
        LARGE_INTEGER f;
        QueryPerformanceFrequency(&f);
        return (double)f.QuadPart;
    }();
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return counter.QuadPart / frequency;
}

float Lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

float PositiveMod(float value, float modulus) {
    float result = std::fmod(value, modulus);
    return result < 0 ? result + modulus : result;
}

int PositiveMod(long long value, int modulus) {
    long long result = value % modulus;
    return (int)(result < 0 ? result + modulus : result);
}

bool IsKeyDown(int vk) {
    return (GetAsyncKeyState(vk) & 0x8000) != 0;
}

// Injects an unassigned key press. Sent right after the swallowed Tab, it stops
// the foreground app from treating the Alt release as a menu activation. It
// also makes this process the source of the last input, which allows it to
// call SetForegroundWindow.
void SendDummyKeyPress() {
    INPUT inputs[2] = {};
    for (INPUT& input : inputs) {
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = kDummyVk;
        input.ki.dwExtraInfo = kInjectedInputTag;
    }
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}

////////////////////////////////////////////////////////////////////////////////
// Low-level hooks (hook thread).

// Ends the session from any thread. Returns false if it was already ended.
bool EndSwitching() {
    if (!g_switching.exchange(false)) {
        return false;
    }
    PostThreadMessageW(g_hookThreadId, WM_HOOK_DISENGAGE, 0, 0);
    return true;
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
    if (code != HC_ACTION) {
        return CallNextHookEx(nullptr, code, wParam, lParam);
    }

    const auto* kb = reinterpret_cast<const KBDLLHOOKSTRUCT*>(lParam);
    if (kb->dwExtraInfo == kInjectedInputTag) {
        return CallNextHookEx(nullptr, code, wParam, lParam);
    }

    const bool keyDown = wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN;
    const DWORD vk = kb->vkCode;

    if (!g_switching) {
        if (keyDown && vk == VK_TAB && ((kb->flags & LLKHF_ALTDOWN) || IsKeyDown(VK_MENU)) &&
            g_ready && g_takeOver && !IsKeyDown(VK_LWIN) &&
            !IsKeyDown(VK_RWIN)) {
            g_sticky = IsKeyDown(VK_CONTROL);
            g_switching = true;
            PostMessageW(g_overlayWnd, WM_APP_START,
                         (IsKeyDown(VK_SHIFT) ? kStartBackwards : 0) | (g_sticky ? 4 : 0), 0);
            PostThreadMessageW(g_hookThreadId, WM_HOOK_ENGAGE, 0, 0);
            return 1;
        }
        return CallNextHookEx(nullptr, code, wParam, lParam);
    }

    switch (vk) {
        case VK_MENU:
        case VK_LMENU:
        case VK_RMENU:
            if (!keyDown && !g_sticky && EndSwitching()) {
                PostMessageW(g_overlayWnd, WM_APP_COMMIT, 0, 0);
            }
            return CallNextHookEx(nullptr, code, wParam, lParam);

        case VK_SHIFT:
        case VK_LSHIFT:
        case VK_RSHIFT:
        case VK_CONTROL:
        case VK_LCONTROL:
        case VK_RCONTROL:
        case VK_LWIN:
        case VK_RWIN:
            return CallNextHookEx(nullptr, code, wParam, lParam);
    }

    // While switching, every other key belongs to the switcher. Otherwise the
    // foreground app would receive them as Alt+key accelerators.
    if (keyDown) {
        int step = 0;
        switch (vk) {
            case VK_TAB:
                step = IsKeyDown(VK_SHIFT) ? -1 : 1;
                break;
            case VK_RIGHT:
            case VK_DOWN:
                step = 1;
                break;
            case VK_LEFT:
            case VK_UP:
                step = -1;
                break;
            case VK_DELETE:
            case 0x51: // Q
                PostMessageW(g_overlayWnd, WM_APP_CLOSE_SELECTED, 0, 0);
                break;
            case 0x57: // Ctrl+W
                if (IsKeyDown(VK_CONTROL)) PostMessageW(g_overlayWnd, WM_APP_CLOSE_SELECTED, 0, 0);
                break;
            case VK_ESCAPE:
                if (EndSwitching()) {
                    PostMessageW(g_overlayWnd, WM_APP_CANCEL, 0, 0);
                }
                break;
            case VK_RETURN:
            case VK_SPACE:
                if (EndSwitching()) {
                    PostMessageW(g_overlayWnd, WM_APP_COMMIT, 0, 0);
                }
                break;
        }
        if (step) {
            PostMessageW(g_overlayWnd, WM_APP_STEP, (WPARAM)(INT_PTR)step, 0);
        }
    }
    return 1;
}

LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam) {
    if (code == HC_ACTION && wParam == WM_MOUSEWHEEL && g_switching) {
        const auto* ms = reinterpret_cast<const MSLLHOOKSTRUCT*>(lParam);
        if (ms->dwExtraInfo != kInjectedInputTag) {
            const short delta = (short)HIWORD(ms->mouseData);
            PostMessageW(g_overlayWnd, WM_APP_WHEEL, (WPARAM)(INT_PTR)delta,
                         0);
            return 1;
        }
    }
    return CallNextHookEx(nullptr, code, wParam, lParam);
}

// The keyboard hook is only installed while Alt+Tab is taken over, so the
// native style leaves no system-wide hook behind.
void UpdateKeyboardHook() {
    if (g_takeOver && !g_keyboardHook) {
        g_keyboardHook =
            SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardProc, g_module, 0);
        if (!g_keyboardHook) {
            Wh_Log(L"SetWindowsHookEx(WH_KEYBOARD_LL) failed: %u",
                   GetLastError());
        }
    } else if (!g_takeOver && g_keyboardHook) {
        UnhookWindowsHookEx(g_keyboardHook);
        g_keyboardHook = nullptr;
    }
}

DWORD WINAPI HookThreadProc(LPVOID parameter) {
    MSG msg;
    // Create the message queue before the creator continues.
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);

    UpdateKeyboardHook();
    SetEvent((HANDLE)parameter);

    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (msg.hwnd) {
            DispatchMessageW(&msg);
            continue;
        }

        switch (msg.message) {
            case WM_HOOK_UPDATE:
                UpdateKeyboardHook();
                break;

            case WM_HOOK_ENGAGE:
                SendDummyKeyPress();
                if (!g_mouseHook) {
                    g_mouseHook =
                        SetWindowsHookExW(WH_MOUSE_LL, MouseProc, g_module, 0);
                }
                break;

            case WM_HOOK_DISENGAGE:
                if (g_mouseHook && !g_switching) {
                    UnhookWindowsHookEx(g_mouseHook);
                    g_mouseHook = nullptr;
                }
                break;
        }
    }

    if (g_mouseHook) {
        UnhookWindowsHookEx(g_mouseHook);
        g_mouseHook = nullptr;
    }
    if (g_keyboardHook) {
        UnhookWindowsHookEx(g_keyboardHook);
        g_keyboardHook = nullptr;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Explorer's Alt+Tab hotkey (explorer.exe).
//
// The native switcher is started by a hotkey that explorer registers for
// itself. Normally the keyboard hook swallows the Tab before hotkeys are
// processed, but low-level hooks don't see the keys when an elevated window
// has the focus, and physical key presses can slip past them. Hotkeys are
// delivered in every case, so explorer's message retrieval is watched too, and
// the hotkey is handed to the switcher instead of opening the native one.
//
// This is the only part of the mod that runs inside explorer. The hotkey
// arrives on explorer's "Immersive Shell" thread (see kAltTabThreadName),
// which is found by its name: only that thread is hooked, with a thread hook
// inside explorer itself.

// Explorer thread only.
HHOOK g_messageHook;
HANDLE g_messageHookThread;  // To know when it ends.
std::atomic<int> g_messageHookCalls;
HANDLE g_explorerStopEvent;
HANDLE g_explorerThread;

// Hands the hotkey to the switcher. Returns false if the switcher isn't running
// or can't take over Alt+Tab right now; the native switcher then opens.
bool ForwardHotkey(bool backwards) {
    HWND overlay = FindWindowW(kOverlayClassName, kOverlayTitleReady);
    if (!overlay) {
        overlay=FindWindowW(SWS_CLASSNAME,nullptr);
        if(!overlay) return false;
        DWORD pid=0; GetWindowThreadProcessId(overlay,&pid); AllowSetForegroundWindow(pid);
        return PostMessageW(overlay,WM_HOTKEY,backwards?SWS_HOTKEY_ALTSHIFTTAB:SWS_HOTKEY_ALTTAB,MAKELPARAM(MOD_ALT,VK_TAB))!=FALSE;
    }

    // Explorer has just received the hotkey, so it may pass the foreground
    // on. The switcher needs it to take the keyboard focus.
    DWORD processId = 0;
    GetWindowThreadProcessId(overlay, &processId);
    AllowSetForegroundWindow(processId);

    return PostMessageW(overlay, g_hotkeyMessage,
                        backwards ? kStartBackwards : 0, 0) != FALSE;
}

LRESULT CALLBACK GetMessageProc(int code, WPARAM wParam, LPARAM lParam) {
    g_messageHookCalls++;

    auto* msg = reinterpret_cast<MSG*>(lParam);
    if (code == HC_ACTION && wParam == PM_REMOVE &&
        msg->message == WM_HOTKEY && HIWORD(msg->lParam) == VK_TAB) {
        const UINT modifiers = LOWORD(msg->lParam);
        if ((modifiers & MOD_ALT) && !(modifiers & (MOD_CONTROL | MOD_WIN)) &&
            ForwardHotkey((modifiers & MOD_SHIFT) != 0)) {
            Wh_Log(L"Alt+Tab reached explorer's hotkey, handing it over");
            // Explorer gets an empty message instead of the hotkey.
            msg->message = WM_NULL;
        }
    }

    const LRESULT result = CallNextHookEx(nullptr, code, wParam, lParam);
    g_messageHookCalls--;
    return result;
}

// The ID of explorer's thread that receives the hotkey, or 0 if it doesn't
// exist now.
DWORD FindAltTabThread() {
    DWORD found = 0;
    const DWORD processId = GetCurrentProcessId();
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        return found;
    }

    THREADENTRY32 entry{sizeof(entry)};
    for (BOOL more = Thread32First(snapshot, &entry); more && !found;
         more = Thread32Next(snapshot, &entry)) {
        if (entry.th32OwnerProcessID != processId) {
            continue;
        }
        HANDLE thread = OpenThread(THREAD_QUERY_LIMITED_INFORMATION, FALSE,
                                   entry.th32ThreadID);
        if (!thread) {
            continue;
        }
        PWSTR name = nullptr;
        if (SUCCEEDED(GetThreadDescription(thread, &name)) && name &&
            wcscmp(name, kAltTabThreadName) == 0) {
            found = entry.th32ThreadID;
        }
        if (name) {
            LocalFree(name);
        }
        CloseHandle(thread);
    }

    CloseHandle(snapshot);
    return found;
}

// Hooks the thread that receives the hotkey, if it exists now. Returns true if
// it's hooked.
bool HookAltTabThread() {
    const DWORD threadId = FindAltTabThread();
    if (!threadId) {
        return false;
    }
    HANDLE thread = OpenThread(SYNCHRONIZE, FALSE, threadId);
    if (!thread) {
        return false;
    }
    // A thread of this process: no module (SetWindowsHookEx docs).
    HHOOK hook =
        SetWindowsHookExW(WH_GETMESSAGE, GetMessageProc, nullptr, threadId);
    if (!hook) {
        Wh_Log(L"SetWindowsHookEx(WH_GETMESSAGE) failed: %u", GetLastError());
        CloseHandle(thread);
        return false;
    }
    Wh_Log(L"Hooked explorer's thread %u (%s)", threadId, kAltTabThreadName);
    g_messageHook = hook;
    g_messageHookThread = thread;
    return true;
}

void UnhookAltTabThread() {
    if (g_messageHook) {
        UnhookWindowsHookEx(g_messageHook);
        g_messageHook = nullptr;
    }
    if (g_messageHookThread) {
        CloseHandle(g_messageHookThread);
        g_messageHookThread = nullptr;
    }

    // Let calls already running on explorer's thread leave the module before
    // it gets unloaded. No new calls can start after the hook is removed, so
    // this always ends.
    const ULONGLONG start = GetTickCount64();
    bool logged = false;
    while (g_messageHookCalls > 0) {
        if (!logged && GetTickCount64() - start > 1000) {
            Wh_Log(L"Still waiting for message hook calls to return");
            logged = true;
        }
        Sleep(1);
    }
}

DWORD WINAPI ExplorerThreadProc(LPVOID) {
    // Only the shell process (the one with the taskbar) receives the hotkey.
    // With "Launch folder windows in a separate process", folder windows run
    // in other explorer processes, which have nothing to do.
    for (;;) {
        if (HWND taskbar = FindWindowW(L"Shell_TrayWnd", nullptr)) {
            DWORD processId = 0;
            GetWindowThreadProcessId(taskbar, &processId);
            if (processId != GetCurrentProcessId()) {
                Wh_Log(L"Not the shell process, nothing to do");
                return 0;
            }
            break;
        }
        // Explorer is still starting up.
        if (WaitForSingleObject(g_explorerStopEvent,
                                kWaitForTaskbarIntervalMs) != WAIT_TIMEOUT) {
            return 0;
        }
    }

    // Hooks the thread, and again if it's ever made anew. Until it's hooked,
    // it's looked for again, less and less often.
    DWORD interval = kFindAltTabThreadIntervalMs;
    bool loggedMissing = false;
    for (;;) {
        if (!g_messageHook && !HookAltTabThread() && !loggedMissing) {
            Wh_Log(L"Explorer's \"%s\" thread wasn't found yet",
                   kAltTabThreadName);
            loggedMissing = true;
        }

        const HANDLE events[] = {g_explorerStopEvent, g_messageHookThread};
        const DWORD result = WaitForMultipleObjects(
            g_messageHook ? 2 : 1, events, FALSE,
            g_messageHook ? INFINITE : interval);
        if (result == WAIT_TIMEOUT) {
            interval = std::min(interval * 2, kFindAltTabThreadMaxIntervalMs);
        } else if (result == WAIT_OBJECT_0 + 1) {
            // The thread ended (its ID can be reused).
            UnhookAltTabThread();
            interval = kFindAltTabThreadIntervalMs;
            loggedMissing = false;
        } else {
            break;
        }
    }

    UnhookAltTabThread();
    return 0;
}

void StopExplorerPart() {
    if (g_explorerThread) {
        SetEvent(g_explorerStopEvent);
        WaitForSingleObject(g_explorerThread, INFINITE);
        CloseHandle(g_explorerThread);
        g_explorerThread = nullptr;
    }
    if (g_explorerStopEvent) {
        CloseHandle(g_explorerStopEvent);
        g_explorerStopEvent = nullptr;
    }
}

// Doesn't wait for anything, so explorer's startup isn't delayed.
void StartExplorerPart() {
    if (LoadSettings().style == AnimationStyle::Native) {
        // Nothing to hand over.
        return;
    }

    g_explorerStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_explorerStopEvent) {
        return;
    }
    g_explorerThread =
        CreateThread(nullptr, 0, ExplorerThreadProc, nullptr, 0, nullptr);
    if (!g_explorerThread) {
        Wh_Log(L"CreateThread failed: %u", GetLastError());
        StopExplorerPart();
    }
}

////////////////////////////////////////////////////////////////////////////////
// Window list.

bool IsSwitchableWindow(HWND hwnd) {
    if (hwnd == g_overlayWnd || !IsWindowVisible(hwnd) ||
        hwnd == GetShellWindow()) {
        return false;
    }

    const LONG_PTR exStyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    if (!(exStyle & WS_EX_APPWINDOW)) {
        if (exStyle & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE)) {
            return false;
        }
        if (GetWindow(hwnd, GW_OWNER)) {
            return false;
        }
    }

    BOOL cloaked = FALSE;
    if (SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked,
                                        sizeof(cloaked))) &&
        cloaked) {
        return false;
    }

    WCHAR className[64];
    if (GetClassNameW(hwnd, className, ARRAYSIZE(className))) {
        for (PCWSTR excluded : {L"Progman", L"WorkerW", L"Shell_TrayWnd",
                                L"Shell_SecondaryTrayWnd"}) {
            if (wcscmp(className, excluded) == 0) {
                return false;
            }
        }
    }
    return true;
}

// Window bounds in physical pixels. For minimized windows, the restored bounds.
bool GetWindowBounds(HWND hwnd, bool minimized, RECT* rect) {
    if (minimized) {
        WINDOWPLACEMENT placement{sizeof(placement)};
        if (!GetWindowPlacement(hwnd, &placement)) {
            return false;
        }
        // rcNormalPosition is in workspace coordinates.
        *rect = placement.rcNormalPosition;
        HMONITOR monitor = MonitorFromRect(rect, MONITOR_DEFAULTTONEAREST);
        MONITORINFO info{sizeof(info)};
        if (GetMonitorInfoW(monitor, &info)) {
            if (placement.flags & WPF_RESTORETOMAXIMIZED) {
                *rect = info.rcWork;
            } else if (!(GetWindowLongPtrW(hwnd, GWL_EXSTYLE) &
                         WS_EX_TOOLWINDOW)) {
                OffsetRect(rect, info.rcWork.left - info.rcMonitor.left,
                           info.rcWork.top - info.rcMonitor.top);
            }
        }
    } else if (FAILED(DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS,
                                            rect, sizeof(*rect)))) {
        if (!GetWindowRect(hwnd, rect)) {
            return false;
        }
    }
    return rect->right - rect->left > 0 && rect->bottom - rect->top > 0;
}

HICON GetWindowIcon(HWND hwnd) {
    DWORD_PTR result = 0;
    for (WPARAM type : {(WPARAM)ICON_BIG, (WPARAM)ICON_SMALL2}) {
        if (SendMessageTimeoutW(hwnd, WM_GETICON, type, 0,
                                SMTO_ABORTIFHUNG | SMTO_BLOCK, 50, &result) &&
            result) {
            return (HICON)result;
        }
    }
    if (HICON icon = (HICON)GetClassLongPtrW(hwnd, GCLP_HICON)) {
        return icon;
    }
    return (HICON)GetClassLongPtrW(hwnd, GCLP_HICONSM);
}

////////////////////////////////////////////////////////////////////////////////
// Geometry.

struct Pose {
    float x = 0, y = 0, z = 0;  // Card center, relative to the screen center.
    float scale = 1;
    float angleY = 0;  // Turn around the vertical axis, in radians.
    float angleX = 0;  // Tilt around the horizontal axis, in radians.
    float angleZ = 0;  // Roll in the screen plane, in radians.
    float opacity = 1;
    float brightness = 1;
    float highlight = 0;  // Selection outline, used by the grid.
};

Pose LerpPose(const Pose& a, const Pose& b, float t) {
    return {Lerp(a.x, b.x, t),
            Lerp(a.y, b.y, t),
            Lerp(a.z, b.z, t),
            Lerp(a.scale, b.scale, t),
            Lerp(a.angleY, b.angleY, t),
            Lerp(a.angleX, b.angleX, t),
            Lerp(a.angleZ, b.angleZ, t),
            Lerp(a.opacity, b.opacity, t),
            Lerp(a.brightness, b.brightness, t),
            Lerp(a.highlight, b.highlight, t)};
}

// Corners in order: top-left, top-right, bottom-right, bottom-left.
struct Quad {
    D2D1_POINT_2F p[4];
};

bool QuadContains(const Quad& quad, D2D1_POINT_2F pt) {
    bool hasPositive = false;
    bool hasNegative = false;
    for (int i = 0; i < 4; i++) {
        const D2D1_POINT_2F& a = quad.p[i];
        const D2D1_POINT_2F& b = quad.p[(i + 1) % 4];
        const float cross =
            (b.x - a.x) * (pt.y - a.y) - (b.y - a.y) * (pt.x - a.x);
        hasPositive |= cross > 0;
        hasNegative |= cross < 0;
    }
    return !(hasPositive && hasNegative);
}

// Projective transform mapping the (0,0)-(width,height) rectangle onto a quad
// (Heckbert's square-to-quad mapping), as a row-vector 4x4 matrix for D2D.
D2D1_MATRIX_4X4_F RectToQuadMatrix(float width, float height, const Quad& q) {
    const float x0 = q.p[0].x, y0 = q.p[0].y;
    const float x1 = q.p[1].x, y1 = q.p[1].y;
    const float x2 = q.p[2].x, y2 = q.p[2].y;
    const float x3 = q.p[3].x, y3 = q.p[3].y;

    const float sx = x0 - x1 + x2 - x3;
    const float sy = y0 - y1 + y2 - y3;

    float a, b, d, e, g, h;
    if (std::fabs(sx) < 1e-3f && std::fabs(sy) < 1e-3f) {
        a = x1 - x0;
        b = x3 - x0;
        d = y1 - y0;
        e = y3 - y0;
        g = 0;
        h = 0;
    } else {
        const float dx1 = x1 - x2, dx2 = x3 - x2;
        const float dy1 = y1 - y2, dy2 = y3 - y2;
        float den = dx1 * dy2 - dx2 * dy1;
        if (std::fabs(den) < 1e-6f) {
            den = den < 0 ? -1e-6f : 1e-6f;
        }
        g = (sx * dy2 - dx2 * sy) / den;
        h = (dx1 * sy - sx * dy1) / den;
        a = x1 - x0 + g * x1;
        b = x3 - x0 + h * x3;
        d = y1 - y0 + g * y1;
        e = y3 - y0 + h * y3;
    }

    D2D1_MATRIX_4X4_F m{};
    m._11 = a / width;
    m._12 = d / width;
    m._14 = g / width;
    m._21 = b / height;
    m._22 = e / height;
    m._24 = h / height;
    m._33 = 1;
    m._41 = x0;
    m._42 = y0;
    m._44 = 1;
    return m;
}

float EaseOutQuart(float t) {
    const float u = 1 - t;
    return 1 - u * u * u * u;
}

float EaseInOutCubic(float t) {
    const float u = -2 * t + 2;
    return t < 0.5f ? 4 * t * t * t : 1 - u * u * u / 2;
}

struct Tween {
    float from = 0;
    float to = 0;
    double start = 0;
    double duration = 0;
    bool easeInOut = false;

    float Progress(double now) const {
        if (duration <= 0) {
            return 1;
        }
        return (float)std::clamp((now - start) / duration, 0.0, 1.0);
    }
    float Value(double now) const {
        const float p = Progress(now);
        return Lerp(from, to, easeInOut ? EaseInOutCubic(p) : EaseOutQuart(p));
    }
    bool Done(double now) const { return Progress(now) >= 1; }
};

////////////////////////////////////////////////////////////////////////////////
// The switcher (UI thread).

struct EffectChain {
    com_ptr<ID2D1Effect> transform;
    com_ptr<ID2D1Effect> color;
    com_ptr<ID2D1Effect> shadow;
    ID2D1Image* input = nullptr;
};

struct Item {
    HWND hwnd = nullptr;
    std::wstring title;
    RECT rect{};
    bool minimized = false;
    com_ptr<ID2D1Bitmap1> icon;
    com_ptr<ID2D1Bitmap1> placeholder;

    // Minimized windows can't be captured directly. Their DWM thumbnail (the
    // last content, as in the taskbar previews) is shown in an off-screen
    // proxy window, which is captured instead.
    HWND proxy = nullptr;
    HTHUMBNAIL thumbnail = nullptr;

    wgc::GraphicsCaptureItem captureItem{nullptr};
    wgc::Direct3D11CaptureFramePool framePool{nullptr};
    wgc::GraphicsCaptureSession session{nullptr};
    winrt::Windows::Graphics::SizeInt32 poolSize{};
    com_ptr<ID3D11Texture2D> texture;
    com_ptr<ID2D1Bitmap1> content;

    // While an item wraps from the front to the back of the stack, it's drawn
    // twice (flying out, and fading in at the back), so it needs two chains.
    EffectChain chains[2];

    // Title for the panel styles.
    com_ptr<IDWriteTextLayout> label;
    float labelWidth = 0;

    float Width() const { return (float)(rect.right - rect.left); }
    float Height() const { return (float)(rect.bottom - rect.top); }
};

struct DrawEntry {
    Item* item;
    int chain;
    Pose pose;
    float order;  // Larger is farther away, drawn first.
    Quad quad;
};

class Switcher {
   public:
    bool CreateOverlay();
    void Activate();
    void Run();
    void Shutdown();

    LRESULT HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

   private:
    enum class State { Idle, Pending, Open, Closing };

    void Deactivate();
    void PublishState();
    bool CreateDeviceResources();
    void ReleaseDeviceResources();
    void HandleDeviceLost();
    bool EnsureSwapChain(UINT width, UINT height);

    void OnHotkey(bool backwards);
    void OnStart(WPARAM flags);
    void OnStep(int step);
    void OnCommit(int index);
    void OnCancel();
    void OnClick(POINT pt);

    void CollectWindows();
    bool CreateProxy(Item& item);
    void StartCaptures();
    bool FirstFramesReady();
    void StartCapture(Item& item);
    void StopCapture(Item& item);
    void PollFrames(Item& item);
    void Teardown();

    void TakeFocus();
    void ShowOverlay();
    void HideOverlay();
    bool AltReleased(double now);
    void BeginClose(bool commit);
    void FinishClose();
    void EndSession();
    void ActivateWindow(HWND hwnd);

    void ComputeLayout();
    Pose FlatPose(const Item& item) const;
    Pose LayoutPose(const Item& item, int index, float rel) const;
    Quad Project(const Pose& pose, float width, float height) const;
    void BuildDrawList(float t);

    void RenderFrame();
    void DrawCard(const DrawEntry& entry, float t);
    void DrawTitle(float t);
    void ComputePanelLayout();
    D2D1_RECT_F SelectionCell(float* opacity) const;
    void DrawPanelBack(float t);
    void DrawPanelFront(float t);
    bool EnsureLabelFormat();
    void DrawLabel(Item& item,
                   const D2D1_RECT_F& rect,
                   bool centered,
                   D2D1_COLOR_F color);
    bool EnsureChain(EffectChain& chain);

    com_ptr<ID2D1Bitmap1> GetIconBitmap(HWND hwnd);
    void RefreshIcons();
    com_ptr<ID2D1Bitmap1> CreateIconBitmap(HICON icon);
    com_ptr<ID2D1Bitmap1> CreateAppIconBitmap(HWND hwnd);
    com_ptr<ID2D1Bitmap1> CreatePlaceholder(const Item& item);
    com_ptr<ID2D1Bitmap1> CreateTargetBitmap(UINT width, UINT height);
    void UpdateBackground();

    int SelectedIndex() const;

    Settings m_settings{};
    HWND m_hwnd = nullptr;

    // Device resources.
    com_ptr<ID3D11Device> m_d3dDevice;
    com_ptr<ID3D11DeviceContext> m_d3dContext;
    com_ptr<IDXGIDevice> m_dxgiDevice;
    wgd3d::IDirect3DDevice m_captureDevice{nullptr};
    com_ptr<ID2D1Factory1> m_d2dFactory;
    com_ptr<ID2D1Device> m_d2dDevice;
    com_ptr<ID2D1DeviceContext> m_ctx;
    com_ptr<IDCompositionDevice> m_dcompDevice;
    com_ptr<IDCompositionTarget> m_dcompTarget;
    com_ptr<IDCompositionVisual> m_dcompVisual;
    com_ptr<IDXGISwapChain1> m_swapChain;
    com_ptr<ID2D1Bitmap1> m_targetBitmap;
    com_ptr<ID2D1SolidColorBrush> m_brush;
    com_ptr<IDWriteFactory> m_dwriteFactory;
    com_ptr<IDWriteTextFormat> m_titleFormat;
    com_ptr<IWICImagingFactory> m_wicFactory;
    UINT m_swapWidth = 0;
    UINT m_swapHeight = 0;
    bool m_borderlessRequested = false;

    // Window icons, kept across sessions (see GetIconBitmap). The bitmap is
    // null for windows without an icon.
    struct CachedIcon {
        HICON source = nullptr;  // The window icon it was made from, if any.
        com_ptr<ID2D1Bitmap1> bitmap;
    };
    std::unordered_map<HWND, CachedIcon> m_iconCache;

    // Background.
    com_ptr<ID2D1Bitmap1> m_background;
    std::wstring m_backgroundKey;

    // Session.
    State m_state = State::Idle;
    std::vector<std::unique_ptr<Item>> m_items;
    std::vector<DrawEntry> m_drawList;
    RECT m_monitor{};
    // Monitor DPI / 96, for text sizes.
    float m_dpiScale = 1;
    double m_showAt = 0;
    // Captures start once the show delay has passed. The overlay is shown
    // when their first frames arrived, or at this time at the latest.
    bool m_capturing = false;
    double m_captureDeadline = 0;
    double m_lastFrame = 0;
    double m_altReleasedAt = 0;
    Tween m_open;
    bool m_commit = false;
    bool m_selectedOnTopWhenFlat = false;
    // The overlay took the keyboard focus (sessions started from the hotkey).
    bool m_hasFocus = false;
    HWND m_previousForeground = nullptr;
    long long m_target = 0;  // Index of the front item, not wrapped.
    double m_scroll = 0;     // Animated towards m_target.
    double m_velocity = 0;
    int m_wheelRemainder = 0;
    int m_titleIndex = -1;
    com_ptr<IDWriteTextLayout> m_titleLayout;

    // Layout, in pixels.
    float m_width = 0, m_height = 0;
    float m_focal = 0;
    float m_boxWidth = 0, m_boxHeight = 0;
    float m_frontX = 0, m_frontY = 0;
    float m_stepX = 0, m_stepY = 0, m_stepZ = 0;
    int m_gridColumns = 1, m_gridRows = 1;

    // Panel styles: each window's cell and the parts inside it, the panel
    // around them, and the classic style's title box.
    std::vector<D2D1_RECT_F> m_cells;
    std::vector<D2D1_RECT_F> m_thumbnails;
    std::vector<D2D1_RECT_F> m_iconRects;
    std::vector<D2D1_RECT_F> m_labelRects;
    D2D1_RECT_F m_panel{};
    D2D1_RECT_F m_caption{};
    float m_labelFontSize = 0;
    com_ptr<IDWriteTextFormat> m_labelFormat;
};

Switcher* g_switcher;

LRESULT CALLBACK OverlayWndProc(HWND hwnd,
                                UINT msg,
                                WPARAM wParam,
                                LPARAM lParam) {
    if (g_switcher) {
        return g_switcher->HandleMessage(hwnd, msg, wParam, lParam);
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// Creates the overlay window only. It's quick, so the mod finishes loading
// right away; the graphics devices are created afterwards, in Activate.
bool Switcher::CreateOverlay() {
    m_settings = LoadSettings();
    g_takeOver = m_settings.style != AnimationStyle::Native;

    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = OverlayWndProc;
    wc.hInstance = g_module;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = kOverlayClassName;
    if (!RegisterClassExW(&wc)) {
        Wh_Log(L"RegisterClassEx failed: %u", GetLastError());
        return false;
    }

    // Proxy windows only host a DWM thumbnail, they draw nothing themselves.
    WNDCLASSEXW proxyClass{sizeof(proxyClass)};
    proxyClass.lpfnWndProc = DefWindowProcW;
    proxyClass.hInstance = g_module;
    proxyClass.lpszClassName = kProxyClassName;
    if (!RegisterClassExW(&proxyClass)) {
        Wh_Log(L"RegisterClassEx failed: %u", GetLastError());
    }

    m_hwnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST |
                                 WS_EX_NOACTIVATE | WS_EX_NOREDIRECTIONBITMAP,
                             kOverlayClassName, kOverlayTitleIdle, WS_POPUP, 0,
                             0, 0, 0, nullptr, nullptr, g_module, nullptr);
    if (!m_hwnd) {
        Wh_Log(L"CreateWindowEx failed: %u", GetLastError());
        return false;
    }
    g_overlayWnd = m_hwnd;

    // Explorer posts the hotkey message. Allow it even if this process runs
    // at a higher integrity level than explorer.
    ChangeWindowMessageFilterEx(m_hwnd, g_hotkeyMessage, MSGFLT_ALLOW,
                                nullptr);

    BOOL disableTransitions = TRUE;
    DwmSetWindowAttribute(m_hwnd, DWMWA_TRANSITIONS_FORCEDISABLED,
                          &disableTransitions, sizeof(disableTransitions));
    DWM_WINDOW_CORNER_PREFERENCE corners = DWMWCP_DONOTROUND;
    DwmSetWindowAttribute(m_hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &corners,
                          sizeof(corners));
    return true;
}

// Gets ready to take over Alt+Tab. With the native style, nothing is created.
void Switcher::Activate() {
    if (!g_takeOver || m_d3dDevice) {
        PublishState();
        return;
    }

    if (!CreateDeviceResources()) {
        // Alt+Tab isn't taken over, so the native switcher keeps working.
        ReleaseDeviceResources();
        PublishState();
        return;
    }

    if (!m_borderlessRequested) {
        m_borderlessRequested = true;
        // Unpackaged processes are granted borderless capture without a
        // prompt. Without it, Windows draws a yellow border around captured
        // windows.
        try {
            const auto status =
                wgc::GraphicsCaptureAccess::RequestAccessAsync(
                    wgc::GraphicsCaptureAccessKind::Borderless)
                    .get();
            if (status != winrt::Windows::Security::Authorization::
                              AppCapabilityAccess::AppCapabilityAccessStatus::
                                  Allowed) {
                Wh_Log(L"Borderless capture not allowed: %d", (int)status);
            }
        } catch (const winrt::hresult_error& e) {
            Wh_Log(L"RequestAccessAsync failed: 0x%08X", (UINT)e.code());
        }
    }

    g_ready = true;
    PublishState();
}

// Switched to the native style: let go of everything.
void Switcher::Deactivate() {
    EndSwitching();
    HideOverlay();
    Teardown();
    m_state = State::Idle;
    ReleaseDeviceResources();
    PublishState();
}

// Tells explorer, through the overlay's title, whether to hand the Alt+Tab
// hotkey over (see ForwardHotkey).
void Switcher::PublishState() {
    if (m_hwnd) {
        SetWindowTextW(m_hwnd, g_ready && g_takeOver ? kOverlayTitleReady
                                                     : kOverlayTitleIdle);
    }
}

bool Switcher::CreateDeviceResources() {
    HRESULT hr = D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0, D3D11_SDK_VERSION,
        m_d3dDevice.put(), nullptr, m_d3dContext.put());
    if (FAILED(hr)) {
        Wh_Log(L"D3D11CreateDevice failed: 0x%08X", (UINT)hr);
        return false;
    }

    // Capture frame pools use the device from their own threads.
    if (auto multithread = m_d3dDevice.try_as<ID3D11Multithread>()) {
        multithread->SetMultithreadProtected(TRUE);
    }

    m_dxgiDevice = m_d3dDevice.as<IDXGIDevice>();

    auto createCaptureDevice =
        (CreateDirect3D11DeviceFromDXGIDevice_t)GetProcAddress(
            GetModuleHandleW(L"d3d11.dll"),
            "CreateDirect3D11DeviceFromDXGIDevice");
    if (!createCaptureDevice) {
        Wh_Log(L"CreateDirect3D11DeviceFromDXGIDevice not found");
        return false;
    }
    com_ptr<::IInspectable> inspectable;
    hr = createCaptureDevice(m_dxgiDevice.get(), inspectable.put());
    if (FAILED(hr)) {
        Wh_Log(L"CreateDirect3D11DeviceFromDXGIDevice failed: 0x%08X",
               (UINT)hr);
        return false;
    }
    hr = inspectable->QueryInterface(winrt::guid_of<wgd3d::IDirect3DDevice>(),
                                     winrt::put_abi(m_captureDevice));
    if (FAILED(hr)) {
        return false;
    }

    D2D1_FACTORY_OPTIONS options{};
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED,
                           __uuidof(ID2D1Factory1), &options,
                           m_d2dFactory.put_void());
    if (FAILED(hr)) {
        Wh_Log(L"D2D1CreateFactory failed: 0x%08X", (UINT)hr);
        return false;
    }
    hr = m_d2dFactory->CreateDevice(m_dxgiDevice.get(), m_d2dDevice.put());
    if (FAILED(hr)) {
        return false;
    }
    hr = m_d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
                                          m_ctx.put());
    if (FAILED(hr)) {
        return false;
    }
    // Everything is in physical pixels.
    m_ctx->SetDpi(96, 96);
    m_ctx->SetUnitMode(D2D1_UNIT_MODE_PIXELS);
    hr = m_ctx->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White),
                                      m_brush.put());
    if (FAILED(hr)) {
        return false;
    }

    hr = DCompositionCreateDevice(m_dxgiDevice.get(),
                                  IID_PPV_ARGS(m_dcompDevice.put()));
    if (FAILED(hr)) {
        Wh_Log(L"DCompositionCreateDevice failed: 0x%08X", (UINT)hr);
        return false;
    }
    hr = m_dcompDevice->CreateTargetForHwnd(m_hwnd, TRUE, m_dcompTarget.put());
    if (FAILED(hr)) {
        return false;
    }
    hr = m_dcompDevice->CreateVisual(m_dcompVisual.put());
    if (FAILED(hr)) {
        return false;
    }
    m_dcompTarget->SetRoot(m_dcompVisual.get());

    if (!m_dwriteFactory) {
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(m_dwriteFactory.put()));
        if (FAILED(hr)) {
            return false;
        }
    }
    if (!m_wicFactory) {
        hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
                              CLSCTX_INPROC_SERVER,
                              IID_PPV_ARGS(m_wicFactory.put()));
        if (FAILED(hr)) {
            return false;
        }
    }
    return true;
}

void Switcher::ReleaseDeviceResources() {
    g_ready = false;
    m_titleLayout = nullptr;
    m_titleFormat = nullptr;
    m_titleIndex = -1;
    m_background = nullptr;
    m_backgroundKey.clear();
    // The bitmaps belong to the device.
    m_iconCache.clear();
    if (m_ctx) {
        m_ctx->SetTarget(nullptr);
    }
    m_targetBitmap = nullptr;
    m_swapChain = nullptr;
    m_swapWidth = m_swapHeight = 0;
    m_dcompVisual = nullptr;
    m_dcompTarget = nullptr;
    m_dcompDevice = nullptr;
    m_brush = nullptr;
    m_ctx = nullptr;
    m_d2dDevice = nullptr;
    m_d2dFactory = nullptr;
    m_captureDevice = nullptr;
    m_dxgiDevice = nullptr;
    m_d3dContext = nullptr;
    m_d3dDevice = nullptr;
}

void Switcher::HandleDeviceLost() {
    Wh_Log(L"Graphics device lost, recreating");
    // The Alt release will reach the foreground app normally.
    EndSwitching();
    HideOverlay();
    Teardown();
    m_state = State::Idle;
    ReleaseDeviceResources();
    if (CreateDeviceResources()) {
        g_ready = true;
    } else {
        ReleaseDeviceResources();
    }
    PublishState();
}

bool Switcher::EnsureSwapChain(UINT width, UINT height) {
    if (m_swapChain && m_swapWidth == width && m_swapHeight == height) {
        return true;
    }

    m_ctx->SetTarget(nullptr);
    m_targetBitmap = nullptr;
    m_swapChain = nullptr;
    m_swapWidth = m_swapHeight = 0;

    com_ptr<IDXGIAdapter> adapter;
    com_ptr<IDXGIFactory2> factory;
    if (FAILED(m_dxgiDevice->GetAdapter(adapter.put())) ||
        FAILED(adapter->GetParent(IID_PPV_ARGS(factory.put())))) {
        return false;
    }

    DXGI_SWAP_CHAIN_DESC1 desc{};
    desc.Width = width;
    desc.Height = height;
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.BufferCount = 2;
    desc.Scaling = DXGI_SCALING_STRETCH;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    desc.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;
    HRESULT hr = factory->CreateSwapChainForComposition(
        m_d3dDevice.get(), &desc, nullptr, m_swapChain.put());
    if (FAILED(hr)) {
        Wh_Log(L"CreateSwapChainForComposition failed: 0x%08X", (UINT)hr);
        return false;
    }

    com_ptr<IDXGISurface> surface;
    hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(surface.put()));
    if (SUCCEEDED(hr)) {
        D2D1_BITMAP_PROPERTIES1 props = D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
            D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                              D2D1_ALPHA_MODE_PREMULTIPLIED));
        hr = m_ctx->CreateBitmapFromDxgiSurface(surface.get(), &props,
                                                m_targetBitmap.put());
    }
    if (SUCCEEDED(hr)) {
        hr = m_dcompVisual->SetContent(m_swapChain.get());
    }
    if (SUCCEEDED(hr)) {
        hr = m_dcompDevice->Commit();
    }
    if (FAILED(hr)) {
        Wh_Log(L"Swap chain setup failed: 0x%08X", (UINT)hr);
        m_targetBitmap = nullptr;
        m_swapChain = nullptr;
        return false;
    }

    m_swapWidth = width;
    m_swapHeight = height;
    return true;
}

void Switcher::Shutdown() {
    g_ready = false;
    EndSwitching();
    if (m_hwnd) {
        HideOverlay();
    }
    Teardown();
    ReleaseDeviceResources();
    m_dwriteFactory = nullptr;
    m_wicFactory = nullptr;
    if (m_hwnd) {
        DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
    }
    UnregisterClassW(kOverlayClassName, g_module);
    UnregisterClassW(kProxyClassName, g_module);
}

void Switcher::Run() {
    MSG msg;
    for (;;) {
        if (m_state == State::Idle || m_state == State::Pending) {
            DWORD timeout = INFINITE;
            if (m_state == State::Pending) {
                // Wake up regularly to watch the Alt key (see AltReleased),
                // and often while waiting for the first frames.
                const double remaining = m_showAt - NowSeconds();
                timeout = m_capturing
                              ? 4
                              : (DWORD)std::clamp(std::ceil(remaining * 1000),
                                                  0.0, 15.0);
            }
            MsgWaitForMultipleObjectsEx(0, nullptr, timeout, QS_ALLINPUT,
                                        MWMO_INPUTAVAILABLE);
        }

        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return;
            }
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        if (m_state == State::Pending) {
            const double now = NowSeconds();
            if (AltReleased(now) && EndSwitching()) {
                OnCommit(-1);
            } else if (now >= m_showAt) {
                // A quick Alt+Tab never gets here, so it doesn't pay for
                // captures it wouldn't show.
                if (!m_capturing) {
                    StartCaptures();
                    m_captureDeadline = now + 0.15;
                }
                if (FirstFramesReady() || now >= m_captureDeadline) {
                    ShowOverlay();
                }
            }
        }

        if (m_state == State::Open || m_state == State::Closing) {
            // Blocks until the next vertical blank.
            RenderFrame();
        }
    }
}

LRESULT Switcher::HandleMessage(HWND hwnd,
                                UINT msg,
                                WPARAM wParam,
                                LPARAM lParam) {
    if (msg == g_hotkeyMessage && g_hotkeyMessage) {
        OnHotkey((wParam & kStartBackwards) != 0);
        return 0;
    }

    switch (msg) {
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;

        case WM_LBUTTONDOWN:
            OnClick({(short)LOWORD(lParam), (short)HIWORD(lParam)});
            return 0;

        case WM_APP_START:
            OnStart(wParam);
            return 0;

        case WM_APP_STEP:
            OnStep((int)(INT_PTR)wParam);
            return 0;

        case WM_APP_WHEEL:
            m_wheelRemainder += (int)(INT_PTR)wParam;
            while (std::abs(m_wheelRemainder) >= WHEEL_DELTA) {
                // Wheel up brings the previous window to the front.
                const int direction = m_wheelRemainder > 0 ? 1 : -1;
                m_wheelRemainder -= direction * WHEEL_DELTA;
                OnStep(-direction);
            }
            return 0;

        case WM_APP_COMMIT:
            OnCommit(-1);
            return 0;

        case WM_APP_CANCEL:
            OnCancel();
            return 0;

        case WM_APP_REFRESH_ICONS:
            // Skipped if a new session started meanwhile; it posts this again
            // when it ends.
            if (m_state == State::Idle && m_ctx) {
                RefreshIcons();
            }
            return 0;

        case WM_APP_CLOSE_SELECTED: {
            int selected = SelectedIndex();
            if(selected >= 0) {
                HWND target = m_items[selected]->hwnd;
                OnCancel(); EndSwitching();
                PostMessageW(target, WM_CLOSE, 0, 0);
            }
            return 0;
        }
        case WM_APP_SETTINGS:
            m_settings = LoadSettings();
            g_takeOver = m_settings.style != AnimationStyle::Native;
            PostThreadMessageW(g_hookThreadId, WM_HOOK_UPDATE, 0, 0);
            m_backgroundKey.clear();
            m_titleFormat = nullptr;
            if (!g_takeOver) {
                Deactivate();
            } else if (!m_d3dDevice) {
                Activate();
            } else {
                if (m_state != State::Idle) {
                    ComputeLayout();
                }
                PublishState();
            }
            return 0;

        case WM_SETTINGCHANGE:
        case WM_DISPLAYCHANGE:
            m_backgroundKey.clear();
            break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int Switcher::SelectedIndex() const {
    if (m_items.empty()) {
        return -1;
    }
    return PositiveMod(m_target, (int)m_items.size());
}

// Explorer received the Alt+Tab hotkey and handed it over: the keyboard hook
// didn't see the keys, usually because an elevated window has the focus.
void Switcher::OnHotkey(bool backwards) {
    if (!g_ready || !g_takeOver) {
        return;
    }
    if (g_switching.exchange(true)) {
        // Tab pressed again while Alt is held.
        OnStep(backwards ? -1 : 1);
        return;
    }
    Wh_Log(L"Alt+Tab reached explorer's hotkey, taking it over");
    PostThreadMessageW(g_hookThreadId, WM_HOOK_ENGAGE, 0, 0);
    OnStart(kStartFromHotkey | (backwards ? kStartBackwards : 0));
}

void Switcher::OnStart(WPARAM flags) {
    if (!g_ready) {
        EndSwitching();
        return;
    }
    const bool backwards = (flags & kStartBackwards) != 0;
    const bool fromHotkey = (flags & kStartFromHotkey) != 0;

    // A new Alt+Tab while the previous one is still animating out.
    if (m_state == State::Closing) {
        FinishClose();
    } else if (m_state != State::Idle) {
        HideOverlay();
        Teardown();
        m_state = State::Idle;
    }

    g_sticky = (flags & 4) != 0;
    m_previousForeground = GetForegroundWindow();

    HMONITOR monitor;
    POINT cursor;
    if (m_settings.monitor == MonitorMode::Cursor && GetCursorPos(&cursor)) {
        monitor = MonitorFromPoint(cursor, MONITOR_DEFAULTTOPRIMARY);
    } else {
        monitor =
            MonitorFromWindow(m_previousForeground, MONITOR_DEFAULTTOPRIMARY);
    }
    MONITORINFO info{sizeof(info)};
    if (!GetMonitorInfoW(monitor, &info)) {
        EndSwitching();
        return;
    }
    m_monitor = info.rcMonitor;

    UINT dpiX = 96, dpiY = 96;
    if (FAILED(GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY))) {
        dpiY = 96;
    }
    if (m_dpiScale != dpiY / 96.0f) {
        m_dpiScale = dpiY / 96.0f;
        m_titleFormat = nullptr;
    }

    CollectWindows();
    if (m_items.empty()) {
        // Nothing to switch to. The rest of the keys go to the apps again.
        EndSwitching();
        return;
    }

    const int count = (int)m_items.size();
    m_target = count > 1 ? (backwards ? count - 1 : 1) : 0;
    m_scroll = (double)m_target;
    m_velocity = 0;
    m_wheelRemainder = 0;
    m_altReleasedAt = 0;
    m_titleIndex = -1;
    m_commit = false;
    m_selectedOnTopWhenFlat = false;

    ComputeLayout();

    m_showAt = NowSeconds() + m_settings.showDelayMs / 1000.0;
    m_capturing = false;
    m_state = State::Pending;

    if (fromHotkey) {
        TakeFocus();
    }
}

// Used when the keyboard hook can't see the keys (e.g. an elevated window has
// the focus). Like the native switcher, the overlay then takes the keyboard
// focus, so the rest of the session goes through the hook again. It stays
// fully transparent until the stack is shown.
void Switcher::TakeFocus() {
    const UINT width = (UINT)(m_monitor.right - m_monitor.left);
    const UINT height = (UINT)(m_monitor.bottom - m_monitor.top);
    if (!EnsureSwapChain(width, height)) {
        return;
    }

    m_ctx->SetTarget(m_targetBitmap.get());
    m_ctx->BeginDraw();
    m_ctx->Clear(D2D1::ColorF(0, 0, 0, 0));
    HRESULT hr = m_ctx->EndDraw();
    m_ctx->SetTarget(nullptr);
    if (SUCCEEDED(hr)) {
        hr = m_swapChain->Present(0, 0);
    }
    if (FAILED(hr)) {
        return;
    }

    SetWindowLongPtrW(m_hwnd, GWL_EXSTYLE,
                      GetWindowLongPtrW(m_hwnd, GWL_EXSTYLE) &
                          ~WS_EX_NOACTIVATE);
    SetWindowPos(m_hwnd, HWND_TOPMOST, m_monitor.left, m_monitor.top, width,
                 height, SWP_NOACTIVATE | SWP_SHOWWINDOW);
    // Receiving the hotkey allows this process to change the foreground.
    m_hasFocus = SetForegroundWindow(m_hwnd) != FALSE;
    if (!m_hasFocus) {
        Wh_Log(L"Couldn't take the focus");
    }
}

void Switcher::HideOverlay() {
    ShowWindow(m_hwnd, SW_HIDE);
    SetWindowLongPtrW(m_hwnd, GWL_EXSTYLE,
                      GetWindowLongPtrW(m_hwnd, GWL_EXSTYLE) |
                          WS_EX_NOACTIVATE);
    m_hasFocus = false;
}

// Fallback for a missed Alt release (e.g. a secure desktop took the input, or
// the keys never reached the hook). The hook normally reports it first, so
// it only counts once Alt stays released for a moment.
bool Switcher::AltReleased(double now) {
    if (!g_switching || g_sticky || IsKeyDown(VK_MENU)) {
        m_altReleasedAt = 0;
        return false;
    }
    if (!m_altReleasedAt) {
        m_altReleasedAt = now;
    }
    return now - m_altReleasedAt > 0.15;
}

void Switcher::OnStep(int step) {
    if ((m_state != State::Pending && m_state != State::Open) ||
        m_items.size() < 2) {
        return;
    }
    m_target += step;
    if (m_state == State::Pending) {
        m_scroll = (double)m_target;
    }
}

void Switcher::OnCommit(int index) {
    if (m_state == State::Idle || m_state == State::Closing) {
        return;
    }

    if (index >= 0 && !m_items.empty()) {
        // Bring the chosen item to the front the shortest way.
        const int count = (int)m_items.size();
        int delta = index - SelectedIndex();
        if (delta > count / 2) {
            delta -= count;
        } else if (delta < -count / 2) {
            delta += count;
        }
        m_target += delta;
    }

    if (m_state == State::Pending) {
        // Quick Alt+Tab: switch right away, without showing anything.
        const int selected = SelectedIndex();
        HWND target = selected >= 0 ? m_items[selected]->hwnd : nullptr;
        if (target) {
            ActivateWindow(target);
        }
        EndSession();
        return;
    }

    BeginClose(true);
}

void Switcher::OnCancel() {
    if (m_state == State::Pending) {
        // If the overlay took the focus, give it back.
        if (m_hasFocus && m_previousForeground) {
            ActivateWindow(m_previousForeground);
        }
        EndSession();
    } else if (m_state == State::Open) {
        BeginClose(false);
    }
}

void Switcher::OnClick(POINT pt) {
    if (m_state != State::Open) {
        return;
    }
    const D2D1_POINT_2F point{(float)pt.x, (float)pt.y};
    if (IsPanelStyle(m_settings.style)) {
        for (size_t i = 0; i < m_cells.size(); i++) {
            const D2D1_RECT_F& cell = m_cells[i];
            if (point.x >= cell.left && point.x < cell.right &&
                point.y >= cell.top && point.y < cell.bottom) {
                EndSwitching();
                OnCommit((int)i);
                return;
            }
        }
        return;
    }
    for (auto it = m_drawList.rbegin(); it != m_drawList.rend(); ++it) {
        if (it->pose.opacity < 0.5f || !QuadContains(it->quad, point)) {
            continue;
        }
        for (size_t i = 0; i < m_items.size(); i++) {
            if (m_items[i].get() == it->item) {
                EndSwitching();
                OnCommit((int)i);
                return;
            }
        }
    }
}

struct EnumWindowsContext {
    std::vector<HWND> windows;
    size_t max;
    bool includeMinimized;
};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    auto* context = reinterpret_cast<EnumWindowsContext*>(lParam);
    if (IsSwitchableWindow(hwnd) &&
        (context->includeMinimized || !IsIconic(hwnd))) {
        context->windows.push_back(hwnd);
    }
    return context->windows.size() < context->max;
}

void Switcher::CollectWindows() {
    EnumWindowsContext context{
        {}, 4096, m_settings.includeMinimized};
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&context));

    // EnumWindows returns the Z order, which puts topmost windows first. The
    // foreground window must come first, like in the native switcher.
    HWND foreground = GetForegroundWindow();
    auto it =
        std::find(context.windows.begin(), context.windows.end(), foreground);
    if (it != context.windows.end()) {
        std::rotate(context.windows.begin(), it, it + 1);
    }

    if (Simple::g_settings.sortMinimizedWindowsToEnd) {
        std::stable_partition(context.windows.begin(), context.windows.end(), [](HWND h) { return !IsIconic(h); });
    }
    m_items.clear();
    for (HWND hwnd : context.windows) {
        if (Simple::g_settings.perMonitorWindows && MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY) != MonitorFromRect(&m_monitor, MONITOR_DEFAULTTOPRIMARY)) continue;
        WCHAR filterTitle[512]{};
        GetWindowTextW(hwnd, filterTitle, ARRAYSIZE(filterTitle));
        bool excluded = false;
        for (const auto& pattern : Simple::g_excludeTitlePatterns) if (PathMatchSpecW(filterTitle, pattern.c_str())) excluded = true;
        DWORD pid = 0; GetWindowThreadProcessId(hwnd, &pid);
        HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
        if (process) {
            WCHAR path[32768]{}; DWORD length = ARRAYSIZE(path);
            if (QueryFullProcessImageNameW(process, 0, path, &length)) {
                for (const auto& pattern : Simple::g_excludeExePatterns) if (PathMatchSpecW(PathFindFileNameW(path), pattern.c_str())) excluded = true;
            }
            CloseHandle(process);
        }
        if (excluded) continue;

        auto item = std::make_unique<Item>();
        item->hwnd = hwnd;
        item->minimized = IsIconic(hwnd);
        if (!GetWindowBounds(hwnd, item->minimized, &item->rect)) {
            continue;
        }

        WCHAR title[256];
        const int length = GetWindowTextW(hwnd, title, ARRAYSIZE(title));
        item->title.assign(title, std::max(length, 0));

        item->icon = GetIconBitmap(hwnd);
        item->placeholder = CreatePlaceholder(*item);
        if (!item->placeholder) {
            continue;
        }
        m_items.push_back(std::move(item));
        if (m_items.size() >= (size_t)m_settings.maxWindows) break;
    }
}

bool Switcher::CreateProxy(Item& item) {
    item.proxy = CreateWindowExW(
        WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_NOREDIRECTIONBITMAP,
        kProxyClassName, L"", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, g_module,
        nullptr);
    if (!item.proxy) {
        return false;
    }

    BOOL disableTransitions = TRUE;
    DwmSetWindowAttribute(item.proxy, DWMWA_TRANSITIONS_FORCEDISABLED,
                          &disableTransitions, sizeof(disableTransitions));

    SIZE size{};
    if (FAILED(DwmRegisterThumbnail(item.proxy, item.hwnd, &item.thumbnail)) ||
        FAILED(DwmQueryThumbnailSourceSize(item.thumbnail, &size)) ||
        size.cx <= 0 || size.cy <= 0) {
        return false;
    }

    DWM_THUMBNAIL_PROPERTIES properties{};
    properties.dwFlags = DWM_TNP_RECTDESTINATION | DWM_TNP_VISIBLE |
                         DWM_TNP_OPACITY | DWM_TNP_SOURCECLIENTAREAONLY;
    properties.rcDestination = {0, 0, size.cx, size.cy};
    properties.fVisible = TRUE;
    properties.opacity = 255;
    properties.fSourceClientAreaOnly = FALSE;
    if (FAILED(DwmUpdateThumbnailProperties(item.thumbnail, &properties))) {
        return false;
    }

    // To the left of all monitors, where nobody can see or click it.
    const int x = GetSystemMetrics(SM_XVIRTUALSCREEN) - size.cx - 100;
    const int y = GetSystemMetrics(SM_YVIRTUALSCREEN);
    return SetWindowPos(item.proxy, HWND_BOTTOM, x, y, size.cx, size.cy,
                        SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

void Switcher::StartCaptures() {
    m_capturing = true;
    for (auto& item : m_items) {
        StartCapture(*item);
    }
}

// Whether every capture delivered its first frame, so the stack can open with
// the windows' content instead of placeholders.
bool Switcher::FirstFramesReady() {
    bool ready = true;
    for (auto& item : m_items) {
        PollFrames(*item);
        if (item->framePool && !item->content) {
            ready = false;
        }
    }
    return ready;
}

void Switcher::StartCapture(Item& item) {
    HWND source = item.hwnd;
    if (item.minimized) {
        if (!m_settings.minimizedContent) {
            return;
        }
        if (!CreateProxy(item)) {
            Wh_Log(L"Proxy failed for %p", item.hwnd);
            StopCapture(item);
            return;
        }
        source = item.proxy;
    }

    try {
        auto factory =
            winrt::get_activation_factory<wgc::GraphicsCaptureItem>();
        com_ptr<IGraphicsCaptureItemInterop> interop;
        winrt::check_hresult(winrt::get_unknown(factory)->QueryInterface(
            kIID_IGraphicsCaptureItemInterop, interop.put_void()));
        winrt::check_hresult(interop->CreateForWindow(
            source, winrt::guid_of<wgc::GraphicsCaptureItem>(),
            winrt::put_abi(item.captureItem)));

        const auto size = item.captureItem.Size();
        if (size.Width <= 0 || size.Height <= 0) {
            StopCapture(item);
            return;
        }

        item.framePool = wgc::Direct3D11CaptureFramePool::CreateFreeThreaded(
            m_captureDevice, wgdx::DirectXPixelFormat::B8G8R8A8UIntNormalized,
            2, size);
        item.poolSize = size;
        item.session = item.framePool.CreateCaptureSession(item.captureItem);

        // Both are optional: older builds lack them, and the border can be
        // enforced by policy.
        try {
            item.session.IsCursorCaptureEnabled(false);
        } catch (...) {
        }
        try {
            item.session.IsBorderRequired(false);
        } catch (...) {
        }

        item.session.StartCapture();
    } catch (const winrt::hresult_error& e) {
        Wh_Log(L"Capture failed for %p: 0x%08X", item.hwnd, (UINT)e.code());
        StopCapture(item);
    }
}

void Switcher::StopCapture(Item& item) {
    try {
        if (item.session) {
            item.session.Close();
        }
        if (item.framePool) {
            item.framePool.Close();
        }
    } catch (...) {
    }
    item.session = nullptr;
    item.framePool = nullptr;
    item.captureItem = nullptr;

    if (item.thumbnail) {
        DwmUnregisterThumbnail(item.thumbnail);
        item.thumbnail = nullptr;
    }
    if (item.proxy) {
        DestroyWindow(item.proxy);
        item.proxy = nullptr;
    }
}

void Switcher::PollFrames(Item& item) {
    if (!item.framePool) {
        return;
    }

    try {
        wgc::Direct3D11CaptureFrame latest{nullptr};
        while (auto frame = item.framePool.TryGetNextFrame()) {
            if (latest) {
                latest.Close();
            }
            latest = frame;
        }
        if (!latest) {
            return;
        }

        const auto contentSize = latest.ContentSize();
        com_ptr<IDirect3DDxgiInterfaceAccess> access;
        winrt::check_hresult(
            winrt::get_unknown(latest.Surface())
                ->QueryInterface(kIID_IDirect3DDxgiInterfaceAccess,
                                 access.put_void()));
        com_ptr<ID3D11Texture2D> source;
        winrt::check_hresult(access->GetInterface(IID_PPV_ARGS(source.put())));

        D3D11_TEXTURE2D_DESC sourceDesc;
        source->GetDesc(&sourceDesc);
        const UINT width = std::min((UINT)std::max(contentSize.Width, 1),
                                    sourceDesc.Width);
        const UINT height = std::min((UINT)std::max(contentSize.Height, 1),
                                     sourceDesc.Height);

        D3D11_TEXTURE2D_DESC desc{};
        if (item.texture) {
            item.texture->GetDesc(&desc);
        }
        if (!item.texture || desc.Width != width || desc.Height != height) {
            desc = {};
            desc.Width = width;
            desc.Height = height;
            desc.MipLevels = 1;
            desc.ArraySize = 1;
            desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
            desc.SampleDesc.Count = 1;
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

            com_ptr<ID3D11Texture2D> texture;
            com_ptr<ID2D1Bitmap1> content;
            winrt::check_hresult(
                m_d3dDevice->CreateTexture2D(&desc, nullptr, texture.put()));
            D2D1_BITMAP_PROPERTIES1 props = D2D1::BitmapProperties1(
                D2D1_BITMAP_OPTIONS_NONE,
                D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                                  D2D1_ALPHA_MODE_PREMULTIPLIED));
            winrt::check_hresult(m_ctx->CreateBitmapFromDxgiSurface(
                texture.as<IDXGISurface>().get(), &props, content.put()));
            item.texture = texture;
            item.content = content;
        }

        const D3D11_BOX box{0, 0, 0, width, height, 1};
        m_d3dContext->CopySubresourceRegion(item.texture.get(), 0, 0, 0, 0,
                                            source.get(), 0, &box);
        latest.Close();

        if (contentSize.Width != item.poolSize.Width ||
            contentSize.Height != item.poolSize.Height) {
            item.framePool.Recreate(
                m_captureDevice,
                wgdx::DirectXPixelFormat::B8G8R8A8UIntNormalized, 2,
                contentSize);
            item.poolSize = contentSize;
        }
    } catch (const winrt::hresult_error& e) {
        Wh_Log(L"Frame update failed for %p: 0x%08X", item.hwnd,
               (UINT)e.code());
        StopCapture(item);
    }
}

void Switcher::Teardown() {
    for (auto& item : m_items) {
        StopCapture(*item);
    }
    m_drawList.clear();
    m_items.clear();
    m_titleLayout = nullptr;
    m_titleIndex = -1;
    m_capturing = false;
}

void Switcher::ShowOverlay() {
    const UINT width = (UINT)(m_monitor.right - m_monitor.left);
    const UINT height = (UINT)(m_monitor.bottom - m_monitor.top);
    if (!EnsureSwapChain(width, height)) {
        HandleDeviceLost();
        return;
    }
    UpdateBackground();
    if (!m_capturing) {
        StartCaptures();
    }

    m_open = {0, 1, NowSeconds(), m_settings.animationDurationMs / 1000.0,
              false};
    m_lastFrame = NowSeconds();
    m_state = State::Open;

    // Present the first frame (identical to the desktop) before showing the
    // window, so nothing stale ever appears.
    RenderFrame();
    if (m_state != State::Open) {
        return;
    }
    SetWindowPos(m_hwnd, HWND_TOPMOST, m_monitor.left, m_monitor.top, width,
                 height, SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

void Switcher::BeginClose(bool commit) {
    const double now = NowSeconds();
    const float current = m_open.Value(now);
    m_open = {current, 0, now,
              m_settings.animationDurationMs * 0.85 / 1000.0 * current, true};
    m_commit = commit;
    m_selectedOnTopWhenFlat = commit;
    m_state = State::Closing;
}

void Switcher::FinishClose() {
    HWND target = nullptr;
    if (m_commit) {
        const int selected = SelectedIndex();
        if (selected >= 0) {
            target = m_items[selected]->hwnd;
        }
    } else if (m_hasFocus) {
        // Canceled after the overlay took the focus: give it back.
        target = m_previousForeground;
    }

    if (target) {
        ActivateWindow(target);
        // Give DWM a frame to bring the window up before revealing it.
        DwmFlush();
    }
    EndSession();
}

void Switcher::EndSession() {
    g_sticky = false;
    HideOverlay();
    Teardown();
    m_state = State::Idle;
    // Nobody is waiting now, so check the cached icons (see GetIconBitmap).
    PostMessageW(m_hwnd, WM_APP_REFRESH_ICONS, 0, 0);
}

void Switcher::ActivateWindow(HWND hwnd) {
    if (!IsWindow(hwnd)) {
        return;
    }

    HWND popup = GetLastActivePopup(hwnd);
    if (!popup || !IsWindowVisible(popup) || !IsWindowEnabled(popup)) {
        popup = hwnd;
    }

    if (IsIconic(hwnd)) {
        ShowWindowAsync(hwnd, SW_RESTORE);
    }

    SendDummyKeyPress();
    if (!SetForegroundWindow(popup)) {
        Wh_Log(L"SetForegroundWindow failed for %p", popup);
    }
}

void Switcher::ComputeLayout() {
    m_width = (float)(m_monitor.right - m_monitor.left);
    m_height = (float)(m_monitor.bottom - m_monitor.top);
    m_focal = m_width * 0.95f;

    const int count = std::max((int)m_items.size(), 1);
    const float spacing = m_settings.stackSpacing;
    // Long stacks are compressed so that the last window stays on screen.
    const float density = std::min(1.0f, 7.0f / std::max(count - 1, 1)) * spacing;

    switch (m_settings.style) {
        case AnimationStyle::Native:
            // Never laid out: nothing is shown with this style.
            break;

        case AnimationStyle::Flip3D:
            // Like Flip 3D, the stack recedes up and to the left.
            m_boxWidth = m_width * 0.48f;
            m_boxHeight = m_height * 0.50f;
            m_frontX = m_width * 0.12f;
            m_frontY = m_height * 0.05f;
            m_stepX = -m_width * 0.065f * density;
            m_stepY = -m_height * 0.04f * density;
            m_stepZ = m_width * 0.07f * density;
            break;

        case AnimationStyle::Cascade:
            // A deck tilted backwards, receding upwards.
            m_boxWidth = m_width * 0.52f;
            m_boxHeight = m_height * 0.50f;
            m_frontX = 0;
            m_frontY = m_height * 0.10f;
            m_stepX = 0;
            m_stepY = -m_height * 0.075f * density;
            m_stepZ = m_width * 0.09f * density;
            break;

        case AnimationStyle::CoverFlow:
            m_boxWidth = m_width * 0.42f;
            m_boxHeight = m_height * 0.55f;
            m_frontX = m_width * 0.27f;  // Distance of the first side window.
            m_frontY = -m_height * 0.02f;
            m_stepX = m_width * 0.075f * spacing;
            m_stepY = 0;
            m_stepZ = m_width * 0.22f;  // How far back the sides are.
            break;

        case AnimationStyle::Carousel:
            m_boxWidth = m_width * 0.38f;
            m_boxHeight = m_height * 0.45f;
            m_frontX = 0;
            m_frontY = m_height * 0.08f;
            m_stepX = m_width * 0.30f * spacing;  // Ring radius.
            m_stepY = 0;
            m_stepZ = 2 * 3.14159265f / std::max(count, 5);  // Angle per window.
            break;

        case AnimationStyle::Grid: {
            // As many columns as make the cells closest to a 16:10 window.
            const float areaWidth = m_width * 0.92f;
            const float areaHeight = m_height * 0.78f;
            m_gridColumns = std::clamp(
                (int)std::ceil(std::sqrt(count * areaWidth / areaHeight / 1.6f)),
                1, count);
            m_gridRows = (count + m_gridColumns - 1) / m_gridColumns;
            m_boxWidth = areaWidth / m_gridColumns;
            m_boxHeight = areaHeight / m_gridRows;
            m_frontX = 0;
            m_frontY = m_height * 0.05f - m_height / 2;  // Top of the grid.
            m_stepX = m_stepY = m_stepZ = 0;
            break;
        }

        case AnimationStyle::Helix:
            m_boxWidth = m_width * 0.36f;
            m_boxHeight = m_height * 0.40f;
            m_frontX = 0;
            m_frontY = m_height * 0.02f;
            m_stepX = m_width * 0.28f * spacing;   // Radius.
            m_stepY = m_height * 0.09f * spacing;  // Rise per window.
            m_stepZ = 0.75f;                       // Angle per window.
            break;

        case AnimationStyle::Fan:
            m_boxWidth = m_width * 0.34f;
            m_boxHeight = m_height * 0.42f;
            m_frontX = 0;
            m_frontY = m_height * 0.95f;           // Pivot, below the screen.
            m_stepX = m_height * 0.95f;            // Distance to the pivot.
            m_stepY = 0;
            m_stepZ = 0.16f * spacing;             // Angle per window.
            break;

        case AnimationStyle::Panorama:
            m_boxWidth = m_width * 0.26f;
            m_boxHeight = m_height * 0.36f;
            m_frontX = 0;
            m_frontY = -m_height * 0.02f;
            m_stepX = m_width * 1.4f;              // Wall radius.
            m_stepY = 0;
            m_stepZ = m_width * 0.29f * spacing / m_stepX;  // Angle per window.
            break;

        case AnimationStyle::Tunnel:
            m_boxWidth = m_width * 0.42f;
            m_boxHeight = m_height * 0.44f;
            m_frontX = 0;
            m_frontY = m_height * 0.08f;
            m_stepX = 0;
            m_stepY = -m_height * 0.06f * density;  // Deeper ones peek above.
            m_stepZ = m_width * 0.12f * density;
            break;

        case AnimationStyle::Windows11:
        case AnimationStyle::Thumbnails:
        case AnimationStyle::IconRow:
        case AnimationStyle::List:
        case AnimationStyle::Classic:
            ComputePanelLayout();
            break;

        case AnimationStyle::Rolodex:
            m_boxWidth = m_width * 0.36f;
            m_boxHeight = m_height * 0.30f;
            m_frontX = 0;
            m_frontY = -m_height * 0.04f;
            m_stepX = m_height * 0.42f * spacing;  // Wheel radius.
            m_stepY = 0;
            m_stepZ = 0.75f;                       // Angle per window.
            break;
    }
}

Pose Switcher::FlatPose(const Item& item) const {
    Pose pose;
    pose.x = (item.rect.left + item.rect.right) / 2.0f - m_monitor.left -
             m_width / 2;
    pose.y = (item.rect.top + item.rect.bottom) / 2.0f - m_monitor.top -
             m_height / 2;
    pose.scale = item.minimized ? 0.85f : 1.0f;
    pose.opacity = item.minimized ? 0.0f : 1.0f;
    return pose;
}

// The pose of a window in the switcher. For the stacked styles, `rel` is the
// slot (0 is the front, negative is leaving the front). For the others, it's
// the signed distance from the selected window.
Pose Switcher::LayoutPose(const Item& item, int index, float rel) const {
    Pose pose;
    const float fit =
        std::min({m_boxWidth / item.Width(), m_boxHeight / item.Height(), 1.0f});
    pose.scale = fit;
    const float tilt = m_settings.tiltRadians;
    const float distance = std::fabs(rel);
    const float side = rel < 0 ? -1.0f : 1.0f;

    switch (m_settings.style) {
        case AnimationStyle::Native:
            break;

        case AnimationStyle::Flip3D:
        case AnimationStyle::Cascade: {
            const bool flip = m_settings.style != AnimationStyle::Cascade;
            if (flip) {
                pose.angleY = tilt;
            } else {
                pose.angleX = tilt;
            }
            if (rel >= 0) {
                pose.x = m_frontX + rel * m_stepX;
                pose.y = m_frontY + rel * m_stepY;
                pose.z = rel * m_stepZ;
                pose.brightness = 1 - std::min(rel * 0.07f, 0.55f);
            } else if (flip) {
                // Leaving the front: fly towards the viewer and fade out.
                pose.x = m_frontX - rel * m_width * 0.22f;
                pose.y = m_frontY - rel * m_height * 0.10f;
                pose.z = rel * m_focal * 0.45f;
                pose.opacity = (1 + rel) * (1 + rel);
            } else {
                // Leaving the front: drop down and fade out.
                pose.x = m_frontX;
                pose.y = m_frontY - rel * m_height * 0.45f;
                pose.z = rel * m_focal * 0.25f;
                pose.opacity = (1 + rel) * (1 + rel);
            }
            break;
        }

        case AnimationStyle::CoverFlow: {
            // The selected window faces the viewer; the others are turned
            // towards it on both sides.
            const float inner = std::min(distance, 1.0f);
            const float outer = std::max(distance - 1, 0.0f);
            pose.x = side * (inner * m_frontX + outer * m_stepX);
            pose.y = m_frontY;
            pose.z = inner * m_stepZ + outer * m_width * 0.01f;
            pose.angleY =
                std::clamp(rel, -1.0f, 1.0f) * std::min(tilt * 2.2f, 1.3f);
            pose.brightness = 1 - inner * 0.2f - std::min(outer * 0.04f, 0.3f);
            pose.opacity = std::clamp(8 - distance, 0.0f, 1.0f);
            break;
        }

        case AnimationStyle::Carousel: {
            // A ring seen slightly from above, rotating around its center.
            const float angle = rel * m_stepZ;
            pose.x = m_stepX * std::sin(angle);
            pose.z = m_stepX * (1 - std::cos(angle));
            pose.y = m_frontY - pose.z * 0.18f;
            pose.angleY = angle * 0.55f;
            pose.brightness = 1 - (1 - std::cos(angle)) * 0.22f;
            pose.opacity = std::clamp(3.5f - std::fabs(angle), 0.0f, 1.0f);
            break;
        }

        case AnimationStyle::Grid: {
            const int row = index / m_gridColumns;
            const int column = index % m_gridColumns;
            const int inRow = std::min(
                m_gridColumns, (int)m_items.size() - row * m_gridColumns);
            const float selected = std::max(0.0f, 1 - distance);
            pose.scale = std::min({m_boxWidth * 0.88f / item.Width(),
                                   m_boxHeight * 0.84f / item.Height(), 1.0f}) *
                         (1 + selected * 0.05f);
            pose.x = (column - (inRow - 1) / 2.0f) * m_boxWidth;
            pose.y = m_frontY + (row + 0.5f) * m_boxHeight;
            pose.z = -selected * m_width * 0.02f;
            pose.brightness = 0.72f + selected * 0.28f;
            pose.highlight = selected;
            break;
        }

        case AnimationStyle::Helix: {
            // A spiral around a vertical axis: earlier windows go up and
            // around, later ones down and around.
            const float angle = rel * m_stepZ;
            pose.x = m_stepX * std::sin(angle);
            pose.z = m_stepX * (1 - std::cos(angle));
            pose.y = m_frontY + rel * m_stepY;
            pose.angleY = angle * 0.6f;
            pose.brightness = 1 - (1 - std::cos(angle)) * 0.22f;
            pose.opacity = std::clamp(3.6f - std::fabs(angle), 0.0f, 1.0f);
            break;
        }

        case AnimationStyle::Fan: {
            // Like playing cards held in a hand, around a pivot below.
            const float angle = rel * m_stepZ;
            const float selected = std::max(0.0f, 1 - distance);
            pose.x = m_stepX * std::sin(angle);
            pose.y = m_frontY - m_stepX * std::cos(angle) -
                     selected * m_height * 0.05f;
            pose.z = distance * m_width * 0.004f - selected * m_width * 0.02f;
            pose.angleZ = angle;
            pose.brightness = 0.8f + selected * 0.2f;
            pose.opacity = std::clamp((1.45f - std::fabs(angle)) * 3, 0.0f, 1.0f);
            break;
        }

        case AnimationStyle::Panorama: {
            // A row of windows on a wall curving around the viewer.
            const float angle = rel * m_stepZ;
            const float selected = std::max(0.0f, 1 - distance);
            pose.x = m_stepX * std::sin(angle);
            pose.y = m_frontY;
            pose.z = -m_stepX * (1 - std::cos(angle)) * 0.25f -
                     selected * m_width * 0.02f;
            pose.angleY = -angle * 0.8f;
            pose.scale = fit * (1 + selected * 0.08f);
            pose.brightness = 0.7f + selected * 0.3f;
            pose.highlight = selected;
            pose.opacity = std::clamp(4.5f - distance, 0.0f, 1.0f);
            break;
        }

        case AnimationStyle::Tunnel:
            // Windows sink into a twisting tunnel.
            pose.x = m_frontX;
            pose.y = m_frontY;
            if (rel >= 0) {
                pose.y += rel * m_stepY;
                pose.z = rel * m_stepZ;
                pose.angleZ = rel * 0.3f;
                pose.brightness = 1 - std::min(rel * 0.09f, 0.6f);
            } else {
                // Leaving the front: spin towards the viewer and fade out.
                pose.z = rel * m_focal * 0.4f;
                pose.angleZ = rel * 0.6f;
                pose.opacity = (1 + rel) * (1 + rel);
            }
            break;

        case AnimationStyle::Windows11:
        case AnimationStyle::Thumbnails: {
            // The window shrinks into its thumbnail.
            const D2D1_RECT_F& thumbnail = m_thumbnails[index];
            const float selected = std::max(0.0f, 1 - distance);
            pose.x = (thumbnail.left + thumbnail.right) / 2 - m_width / 2;
            pose.y = (thumbnail.top + thumbnail.bottom) / 2 - m_height / 2;
            pose.z = -selected * m_width * 0.002f;
            pose.scale =
                std::min((thumbnail.right - thumbnail.left) / item.Width(),
                         (thumbnail.bottom - thumbnail.top) / item.Height()) *
                (1 + selected * 0.03f);
            break;
        }

        case AnimationStyle::IconRow:
        case AnimationStyle::List:
        case AnimationStyle::Classic:
            // No thumbnails: the windows fade out where they are.
            pose = FlatPose(item);
            pose.opacity = 0;
            break;

        case AnimationStyle::Rolodex: {
            // A wheel around a horizontal axis: earlier windows roll over the
            // top, later ones under the bottom.
            const float angle = rel * m_stepZ;
            pose.x = m_frontX;
            pose.y = m_frontY + m_stepX * std::sin(angle);
            pose.z = m_stepX * (1 - std::cos(angle));
            pose.angleX = -angle;
            pose.brightness = 1 - (1 - std::cos(angle)) * 0.45f;
            // Fade out before the back side of the wheel comes around.
            pose.opacity = std::clamp((1.9f - std::fabs(angle)) * 2, 0.0f, 1.0f);
            break;
        }
    }
    return pose;
}

Quad Switcher::Project(const Pose& pose, float width, float height) const {
    const float halfWidth = width * pose.scale / 2;
    const float halfHeight = height * pose.scale / 2;
    const float cosY = std::cos(pose.angleY), sinY = std::sin(pose.angleY);
    const float cosX = std::cos(pose.angleX), sinX = std::sin(pose.angleX);
    const float cosZ = std::cos(pose.angleZ), sinZ = std::sin(pose.angleZ);
    const float corners[4][2] = {{-halfWidth, -halfHeight},
                                 {halfWidth, -halfHeight},
                                 {halfWidth, halfHeight},
                                 {-halfWidth, halfHeight}};

    Quad quad;
    for (int i = 0; i < 4; i++) {
        // Roll in the screen plane, turn around the vertical axis, then tilt
        // (positive tilts the top away from the viewer).
        const float localX = corners[i][0] * cosZ - corners[i][1] * sinZ;
        const float localY = corners[i][0] * sinZ + corners[i][1] * cosZ;
        const float turnedZ = localX * sinY;
        const float x = pose.x + localX * cosY;
        const float y = pose.y + localY * cosX + turnedZ * sinX;
        const float z = pose.z + turnedZ * cosX - localY * sinX;
        const float k = m_focal / std::max(m_focal + z, m_focal * 0.05f);
        quad.p[i] = {m_width / 2 + x * k, m_height / 2 + y * k};
    }
    return quad;
}

void Switcher::BuildDrawList(float t) {
    m_drawList.clear();
    const int count = (int)m_items.size();
    if (!count) {
        return;
    }
    const int selected = SelectedIndex();

    auto add = [&](int index, int chain, float rel, float fade) {
        Item* item = m_items[index].get();
        Pose layout = LayoutPose(*item, index, rel);
        layout.opacity *= fade;

        // Drawing order: the real Z order while flat, depth in the switcher.
        float flatOrder = (float)index;
        if (m_selectedOnTopWhenFlat && index == selected) {
            flatOrder = -1;
        }
        const float depthOrder = layout.z / (m_width * 0.05f);

        DrawEntry entry;
        entry.item = item;
        entry.chain = chain;
        entry.pose = LerpPose(FlatPose(*item), layout, t);
        entry.order = Lerp(flatOrder, depthOrder, t);
        entry.quad = Project(entry.pose, item->Width(), item->Height());
        if (entry.pose.opacity > 0.003f) {
            m_drawList.push_back(entry);
        }
    };

    const bool stacked = m_settings.style == AnimationStyle::Flip3D ||
                         m_settings.style == AnimationStyle::Cascade ||
                         m_settings.style == AnimationStyle::Tunnel;
    for (int i = 0; i < count; i++) {
        if (count == 1) {
            add(i, 0, 0, 1);
            continue;
        }
        const float slot = PositiveMod((float)(i - m_scroll), (float)count);
        if (!stacked) {
            // Signed distance from the selected window, wrapping around.
            add(i, 0, slot >= count / 2.0f ? slot - count : slot, 1);
        } else if (slot <= count - 1) {
            add(i, 0, slot, 1);
        } else {
            // Wrapping from the front to the back of the stack.
            const float leaving = slot - count;  // In (-1, 0).
            add(i, 0, leaving, 1);
            add(i, 1, slot, -leaving);
        }
    }

    std::stable_sort(m_drawList.begin(), m_drawList.end(),
                     [](const DrawEntry& a, const DrawEntry& b) {
                         return a.order > b.order;
                     });
}

// Lays out the 2D panel styles: every window gets a cell, which may hold a
// thumbnail, an icon and a title, and the cells flow in rows (or, for the
// list, in columns) inside a panel.
void Switcher::ComputePanelLayout() {
    const int count = (int)m_items.size();
    m_cells.assign(count, {});
    m_thumbnails.assign(count, {});
    m_iconRects.assign(count, {});
    m_labelRects.assign(count, {});
    m_caption = {};
    m_labelFormat = nullptr;
    for (auto& item : m_items) {
        item->label = nullptr;
    }
    if (!count) {
        return;
    }

    const AnimationStyle style = m_settings.style;
    const bool vertical = style == AnimationStyle::List;
    const float spacing = m_settings.stackSpacing;
    // Follows the monitor's scaling, like the system's own text.
    const float font = std::round(14 * m_dpiScale);
    m_labelFontSize = font;

    // Cell geometry relative to the cell's top-left corner, for one window.
    struct CellLayout {
        D2D1_SIZE_F size;
        D2D1_RECT_F thumbnail, icon, label;
    };
    auto cellFor = [&](int index, float scale) {
        const Item& item = *m_items[index];
        CellLayout cell{};
        switch (style) {
            case AnimationStyle::Windows11:
            case AnimationStyle::Thumbnails: {
                const float height = std::round(m_height * 0.17f * scale);
                const float width = std::round(
                    std::clamp(height * item.Width() / item.Height(),
                               height * 0.75f, height * 1.9f));
                const float pad = std::round(height * 0.07f);
                const float label = std::round(font * 2.1f);
                const float icon = std::round(font * 1.35f);
                cell.size = {width + 2 * pad, label + height + 2 * pad};
                const float thumbnailTop =
                    style == AnimationStyle::Windows11 ? pad + label : pad;
                const float labelTop =
                    style == AnimationStyle::Windows11 ? pad : pad + height;
                cell.thumbnail = {pad, thumbnailTop, pad + width,
                                  thumbnailTop + height};
                const float iconTop = std::round(labelTop + (label - icon) / 2);
                cell.icon = {pad, iconTop, pad + icon, iconTop + icon};
                cell.label = {pad + icon + std::round(font * 0.55f), labelTop,
                              pad + width, labelTop + label};
                break;
            }

            case AnimationStyle::IconRow: {
                const float icon = std::round(font * 3 * scale);
                const float width = std::round(font * 11 * scale);
                const float pad = std::round(font * 0.9f * scale);
                const float label = std::round(font * 2.1f);
                const float iconLeft = std::round((width - icon) / 2);
                cell.size = {width, pad + icon + font * 0.5f + label + pad};
                cell.icon = {iconLeft, pad, iconLeft + icon, pad + icon};
                cell.label = {pad, pad + icon + font * 0.5f, width - pad,
                              pad + icon + font * 0.5f + label};
                break;
            }

            case AnimationStyle::List: {
                const float height = std::round(font * 2.7f * scale);
                const float width =
                    std::round(std::min(m_width * 0.34f, font * 30));
                const float icon = std::round(font * 1.45f);
                const float pad = std::round(font * 0.8f);
                const float iconTop = std::round((height - icon) / 2);
                cell.size = {width, height};
                cell.icon = {pad, iconTop, pad + icon, iconTop + icon};
                cell.label = {pad + icon + std::round(font * 0.7f), 0,
                              width - pad, height};
                break;
            }

            case AnimationStyle::Classic:
            default: {
                const float size = std::round(font * 3.6f * scale);
                const float icon = std::round(font * 2.4f * scale);
                const float offset = std::round((size - icon) / 2);
                cell.size = {size, size};
                cell.icon = {offset, offset, offset + icon, offset + icon};
                break;
            }
        }
        return cell;
    };

    float gap;
    switch (style) {
        case AnimationStyle::Windows11:
        case AnimationStyle::Thumbnails:
            gap = std::round(m_height * 0.01f * spacing);
            break;
        case AnimationStyle::IconRow:
            gap = std::round(font * 0.4f * spacing);
            break;
        case AnimationStyle::List:
            gap = std::round(font * 0.25f * spacing);
            break;
        default:
            gap = std::round(font * 0.15f * spacing);
            break;
    }
    // The classic switcher shows at most 7 icons per row.
    const int maxPerLine = style == AnimationStyle::Classic ? 7 : count;
    const float maxLine = vertical ? m_height * 0.78f : m_width * 0.86f;
    const float maxAcross = vertical ? m_width * 0.86f : m_height * 0.78f;

    // Flow the cells into lines, shrinking them until everything fits.
    std::vector<CellLayout> cells(count);
    std::vector<int> lineOf(count);
    std::vector<float> lineLengths, lineThickness;
    float scale = 1;
    for (int attempt = 0; attempt < 10; attempt++) {
        lineLengths.clear();
        lineThickness.clear();
        int inLine = 0;
        for (int i = 0; i < count; i++) {
            cells[i] = cellFor(i, scale);
            const float along = vertical ? cells[i].size.height
                                         : cells[i].size.width;
            const float across = vertical ? cells[i].size.width
                                          : cells[i].size.height;
            if (lineLengths.empty() || inLine >= maxPerLine ||
                lineLengths.back() + gap + along > maxLine) {
                lineLengths.push_back(along);
                lineThickness.push_back(across);
                inLine = 1;
            } else {
                lineLengths.back() += gap + along;
                lineThickness.back() = std::max(lineThickness.back(), across);
                inLine++;
            }
            lineOf[i] = (int)lineLengths.size() - 1;
        }
        float total = gap * (lineThickness.size() - 1);
        for (float thickness : lineThickness) {
            total += thickness;
        }
        if (total <= maxAcross) {
            break;
        }
        scale *= 0.85f;
    }

    // Classic and list lines start at the same edge; the others are centered.
    const bool centerLines = style != AnimationStyle::Classic &&
                             style != AnimationStyle::List;
    float totalAcross = gap * (lineThickness.size() - 1);
    for (float thickness : lineThickness) {
        totalAcross += thickness;
    }
    const float longest =
        *std::max_element(lineLengths.begin(), lineLengths.end());

    float lineStart = 0, along = 0;
    float across = std::round(
        ((vertical ? m_width : m_height) - totalAcross) / 2);
    for (int i = 0; i < count; i++) {
        const int line = lineOf[i];
        if (i > 0 && lineOf[i - 1] != line) {
            across += lineThickness[line - 1] + gap;
        }
        if (i == 0 || lineOf[i - 1] != line) {
            const float length = centerLines ? lineLengths[line] : longest;
            lineStart = std::round(
                ((vertical ? m_height : m_width) - length) / 2);
            along = lineStart;
        }

        const CellLayout& cell = cells[i];
        const float x = vertical ? across : along;
        const float y = vertical ? along : across;
        auto offset = [x, y](const D2D1_RECT_F& r) {
            return D2D1_RECT_F{x + r.left, y + r.top, x + r.right,
                               y + r.bottom};
        };
        m_cells[i] = {x, y, x + cell.size.width, y + cell.size.height};
        m_thumbnails[i] = offset(cell.thumbnail);
        m_iconRects[i] = offset(cell.icon);
        m_labelRects[i] = offset(cell.label);
        along += (vertical ? cell.size.height : cell.size.width) + gap;
    }

    m_panel = m_cells[0];
    for (const D2D1_RECT_F& cell : m_cells) {
        m_panel.left = std::min(m_panel.left, cell.left);
        m_panel.top = std::min(m_panel.top, cell.top);
        m_panel.right = std::max(m_panel.right, cell.right);
        m_panel.bottom = std::max(m_panel.bottom, cell.bottom);
    }
    const float margin = std::round(font * (style == AnimationStyle::Classic
                                                ? 0.9f
                                                : 1.1f));
    m_panel = {m_panel.left - margin, m_panel.top - margin,
               m_panel.right + margin, m_panel.bottom + margin};

    if (style == AnimationStyle::Classic) {
        // The title of the selected window goes in a box under the icons.
        const float height = std::round(font * 2.2f);
        m_caption = {m_panel.left + margin, m_panel.bottom,
                     m_panel.right - margin, m_panel.bottom + height};
        m_panel.bottom = m_caption.bottom + margin;
    }
}

// The selection slides between neighboring cells. When it wraps around from
// the last window to the first, it fades instead of crossing the panel.
D2D1_RECT_F Switcher::SelectionCell(float* opacity) const {
    const int count = (int)m_cells.size();
    const double base = std::floor(m_scroll);
    const float fraction = (float)(m_scroll - base);
    const int from = PositiveMod((long long)base, count);
    const int to = PositiveMod((long long)base + 1, count);

    if (to == 0 && count > 2) {
        *opacity = std::fabs(fraction - 0.5f) * 2;
        return m_cells[fraction < 0.5f ? from : to];
    }

    *opacity = 1;
    const D2D1_RECT_F& a = m_cells[from];
    const D2D1_RECT_F& b = m_cells[to];
    return {Lerp(a.left, b.left, fraction), Lerp(a.top, b.top, fraction),
            Lerp(a.right, b.right, fraction),
            Lerp(a.bottom, b.bottom, fraction)};
}

D2D1_COLOR_F GetAccentColor(float alpha) {
    DWORD color = 0;
    BOOL opaque = FALSE;
    if (FAILED(DwmGetColorizationColor(&color, &opaque))) {
        return D2D1::ColorF(0.30f, 0.76f, 1.0f, alpha);
    }
    return D2D1::ColorF(((color >> 16) & 0xff) / 255.0f,
                        ((color >> 8) & 0xff) / 255.0f, (color & 0xff) / 255.0f,
                        alpha);
}

// Panel and selection background, drawn under the thumbnails.
void Switcher::DrawPanelBack(float t) {
    if (m_cells.empty()) {
        return;
    }

    if (m_settings.style == AnimationStyle::Classic) {
        // Windows XP: a beige panel with a blue frame.
        m_brush->SetColor(D2D1::ColorF(0.925f, 0.914f, 0.847f, t));
        m_ctx->FillRectangle(m_panel, m_brush.get());
        m_brush->SetColor(D2D1::ColorF(0.0f, 0.24f, 0.65f, t));
        m_ctx->DrawRectangle(m_panel, m_brush.get(), 2);
        return;
    }

    const float radius = m_settings.style == AnimationStyle::Thumbnails
                             ? 0.0f
                             : std::round(m_height / 135);
    m_brush->SetColor(D2D1::ColorF(0.11f, 0.11f, 0.12f, 0.82f * t));
    m_ctx->FillRoundedRectangle({m_panel, radius, radius}, m_brush.get());
    m_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.08f * t));
    m_ctx->DrawRoundedRectangle({m_panel, radius, radius}, m_brush.get(), 1);

    float opacity;
    const D2D1_RECT_F cell = SelectionCell(&opacity);
    m_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.07f * t * opacity));
    m_ctx->FillRoundedRectangle({cell, radius, radius}, m_brush.get());
}

bool Switcher::EnsureLabelFormat() {
    if (m_labelFormat) {
        return true;
    }
    const bool classic = m_settings.style == AnimationStyle::Classic;
    if (FAILED(m_dwriteFactory->CreateTextFormat(
            Simple::g_settings.fontFamily, nullptr,
            classic ? DWRITE_FONT_WEIGHT_BOLD : DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
            m_labelFontSize, L"", m_labelFormat.put()))) {
        return false;
    }
    m_labelFormat->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    m_labelFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    const DWRITE_TRIMMING trimming{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0,
                                   0};
    com_ptr<IDWriteInlineObject> ellipsis;
    m_dwriteFactory->CreateEllipsisTrimmingSign(m_labelFormat.get(),
                                                ellipsis.put());
    m_labelFormat->SetTrimming(&trimming, ellipsis.get());
    return true;
}

// Draws a window title in a rectangle, vertically centered.
void Switcher::DrawLabel(Item& item,
                         const D2D1_RECT_F& rect,
                         bool centered,
                         D2D1_COLOR_F color) {
    const float width = rect.right - rect.left;
    const float height = rect.bottom - rect.top;
    if (width <= 0 || height <= 0 || !EnsureLabelFormat()) {
        return;
    }
    if (!item.label || item.labelWidth != width) {
        item.label = nullptr;
        item.labelWidth = width;
        if (FAILED(m_dwriteFactory->CreateTextLayout(
                item.title.c_str(), (UINT32)item.title.size(),
                m_labelFormat.get(), width, height, item.label.put()))) {
            return;
        }
    }
    item.label->SetTextAlignment(centered ? DWRITE_TEXT_ALIGNMENT_CENTER
                                          : DWRITE_TEXT_ALIGNMENT_LEADING);
    item.label->SetMaxHeight(height);
    m_brush->SetColor(color);
    m_ctx->DrawTextLayout({rect.left, rect.top}, item.label.get(),
                          m_brush.get(), D2D1_DRAW_TEXT_OPTIONS_CLIP);
}

// Icons, titles and the selection border, drawn over the thumbnails.
void Switcher::DrawPanelFront(float t) {
    if (m_cells.empty()) {
        return;
    }
    const AnimationStyle style = m_settings.style;
    const bool classic = style == AnimationStyle::Classic;

    float opacity;
    const D2D1_RECT_F cell = SelectionCell(&opacity);
    if (classic) {
        m_brush->SetColor(D2D1::ColorF(0.19f, 0.42f, 0.77f, 0.25f * t * opacity));
        m_ctx->FillRectangle(cell, m_brush.get());
        m_brush->SetColor(D2D1::ColorF(0.19f, 0.42f, 0.77f, t * opacity));
        m_ctx->DrawRectangle(cell, m_brush.get(), 2);
    } else {
        const float radius = style == AnimationStyle::Thumbnails
                                 ? 0.0f
                                 : std::round(m_height / 135);
        const float border = std::max(2.0f, std::round(m_height / 360));
        const D2D1_RECT_F rect{cell.left + border / 2, cell.top + border / 2,
                               cell.right - border / 2,
                               cell.bottom - border / 2};
        m_brush->SetColor(GetAccentColor(t * opacity));
        m_ctx->DrawRoundedRectangle({rect, radius, radius}, m_brush.get(),
                                    border);
    }

    const float labelOpacity = t * t;
    for (size_t i = 0; i < m_items.size(); i++) {
        Item& item = *m_items[i];
        const D2D1_RECT_F& icon = m_iconRects[i];
        if (item.icon && icon.right > icon.left) {
            m_ctx->DrawBitmap(item.icon.get(), icon, t,
                              D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC);
        }
        if (!classic && labelOpacity > 0.01f) {
            DrawLabel(item, m_labelRects[i], style == AnimationStyle::IconRow,
                      D2D1::ColorF(1, 1, 1, 0.92f * labelOpacity));
        }
    }

    if (classic && labelOpacity > 0.01f) {
        // Sunken box with the title of the window under the selection.
        m_brush->SetColor(D2D1::ColorF(0.98f, 0.98f, 0.96f, t));
        m_ctx->FillRectangle(m_caption, m_brush.get());
        m_brush->SetColor(D2D1::ColorF(0.5f, 0.5f, 0.5f, t));
        m_ctx->DrawRectangle(m_caption, m_brush.get(), 1);

        const int index = PositiveMod((long long)std::round(m_scroll),
                                      (int)m_items.size());
        const float pad = std::round(m_labelFontSize * 0.5f);
        DrawLabel(*m_items[index],
                  {m_caption.left + pad, m_caption.top, m_caption.right - pad,
                   m_caption.bottom},
                  false, D2D1::ColorF(0, 0, 0, labelOpacity));
    }
}

bool Switcher::EnsureChain(EffectChain& chain) {
    if (chain.transform) {
        return true;
    }
    if (FAILED(m_ctx->CreateEffect(CLSID_D2D13DTransform,
                                   chain.transform.put())) ||
        FAILED(m_ctx->CreateEffect(CLSID_D2D1ColorMatrix,
                                   chain.color.put())) ||
        FAILED(m_ctx->CreateEffect(CLSID_D2D1Shadow, chain.shadow.put()))) {
        chain = {};
        return false;
    }

    chain.transform->SetValue(kTransform3DPropInterpolationMode,
                              kTransform3DInterpolationAnisotropic);
    chain.transform->SetValue(kTransform3DPropBorderMode,
                              (UINT32)D2D1_BORDER_MODE_SOFT);
    chain.color->SetInputEffect(0, chain.transform.get());
    chain.shadow->SetInputEffect(0, chain.color.get());
    chain.shadow->SetValue(D2D1_SHADOW_PROP_OPTIMIZATION,
                           kShadowOptimizationSpeed);
    return true;
}

D2D1_COLOR_F SharedColor(bool border, float opacity) {
    const auto& s = Simple::g_settings;
    const bool dark = Simple::g_isDarkMode;
    const WCHAR* mode = border ? (dark ? s.borderColorModeDark : s.borderColorModeLight) : (dark ? s.bgColorModeDark : s.bgColorModeLight);
    const WCHAR* hex = border ? (dark ? s.customBorderColorDark : s.customBorderColorLight) : (dark ? s.customBgColorDark : s.customBgColorLight);
    COLORREF c = border ? RGB(255,255,255) : RGB(0,0,0);
    if (!wcscmp(mode, L"custom")) Simple::ParseHexColor(hex, &c);
    else if (!wcscmp(mode, L"accent")) { DWORD color=0; BOOL opaque=FALSE; if (SUCCEEDED(DwmGetColorizationColor(&color,&opaque))) c=RGB((color>>16)&255,(color>>8)&255,color&255); }
    return D2D1::ColorF(GetRValue(c)/255.0f,GetGValue(c)/255.0f,GetBValue(c)/255.0f,opacity);
}

void Switcher::DrawCard(const DrawEntry& entry, float t) {
    Item& item = *entry.item;
    EffectChain& chain = item.chains[entry.chain];
    if (!EnsureChain(chain)) {
        return;
    }

    ID2D1Bitmap1* bitmap =
        item.content ? item.content.get() : item.placeholder.get();
    if (chain.input != bitmap) {
        chain.transform->SetInput(0, bitmap);
        chain.input = bitmap;
    }

    const D2D1_SIZE_F size = bitmap->GetSize();
    chain.transform->SetValue(
        kTransform3DPropTransformMatrix,
        RectToQuadMatrix(size.width, size.height, entry.quad));

    const float b = entry.pose.brightness;
    const D2D1_MATRIX_5X4_F colorMatrix =
        D2D1::Matrix5x4F(b, 0, 0, 0,                   //
                         0, b, 0, 0,                   //
                         0, 0, b, 0,                   //
                         0, 0, 0, entry.pose.opacity,  //
                         0, 0, 0, 0);
    chain.color->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, colorMatrix);

    if (m_settings.shadows && t > 0.01f) {
        const float depth =
            m_focal / std::max(m_focal + entry.pose.z, m_focal * 0.05f);
        chain.shadow->SetValue(D2D1_SHADOW_PROP_BLUR_STANDARD_DEVIATION,
                               14.0f * depth);
        chain.shadow->SetValue(D2D1_SHADOW_PROP_COLOR,
                               D2D1::Vector4F(0, 0, 0, 0.55f * t));
        const D2D1_POINT_2F offset{0, 10.0f * depth * t};
        m_ctx->DrawImage(chain.shadow.get(), &offset);
    }
    m_ctx->DrawImage(chain.color.get());

    // Selection outline.
    const float highlight = entry.pose.highlight * entry.pose.opacity * t;
    if (highlight > 0.01f) {
        com_ptr<ID2D1PathGeometry> outline;
        com_ptr<ID2D1GeometrySink> sink;
        if (SUCCEEDED(m_d2dFactory->CreatePathGeometry(outline.put())) &&
            SUCCEEDED(outline->Open(sink.put()))) {
            sink->BeginFigure(entry.quad.p[0], D2D1_FIGURE_BEGIN_HOLLOW);
            sink->AddLines(&entry.quad.p[1], 3);
            sink->EndFigure(D2D1_FIGURE_END_CLOSED);
            if (SUCCEEDED(sink->Close())) {
                m_brush->SetColor(SharedColor(true, 0.9f * highlight));
                m_ctx->DrawGeometry(outline.get(), m_brush.get(),
                                    std::max(2.0f, m_height / 360));
            }
        }
    }
}

void Switcher::DrawTitle(float t) {
    if (!m_settings.showTitle || m_items.empty()) {
        return;
    }

    // Visible while settled, faded out while flipping.
    const double nearest = std::round(m_scroll);
    const float settle =
        1 - std::clamp((float)std::fabs(m_scroll - nearest) * 3, 0.0f, 1.0f);
    const float opacity = t * t * settle;
    if (opacity < 0.01f) {
        return;
    }

    const int index = PositiveMod((long long)nearest, (int)m_items.size());
    const Item& item = *m_items[index];

    const float fontSize = std::round(Simple::g_settings.fontSize * 96.0f / 72.0f * m_dpiScale);
    if (!m_titleFormat) {
        if (FAILED(m_dwriteFactory->CreateTextFormat(
                Simple::g_settings.fontFamily, nullptr,
                (wcsstr(Simple::g_settings.fontStyle,L"bold") || wcsstr(Simple::g_settings.fontStyle,L"Bold")) ? DWRITE_FONT_WEIGHT_BOLD : DWRITE_FONT_WEIGHT_NORMAL, wcsstr(Simple::g_settings.fontStyle,L"Italic") || wcsstr(Simple::g_settings.fontStyle,L"italic") ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL,
                DWRITE_FONT_STRETCH_NORMAL, fontSize, L"",
                m_titleFormat.put()))) {
            return;
        }
        m_titleFormat->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
        const DWRITE_TRIMMING trimming{DWRITE_TRIMMING_GRANULARITY_CHARACTER,
                                       0, 0};
        com_ptr<IDWriteInlineObject> ellipsis;
        m_dwriteFactory->CreateEllipsisTrimmingSign(m_titleFormat.get(),
                                                    ellipsis.put());
        m_titleFormat->SetTrimming(&trimming, ellipsis.get());
        m_titleLayout = nullptr;
    }

    if (index != m_titleIndex || !m_titleLayout) {
        m_titleLayout = nullptr;
        m_titleIndex = index;
        if (FAILED(m_dwriteFactory->CreateTextLayout(
                item.title.c_str(), (UINT32)item.title.size(),
                m_titleFormat.get(), m_width * 0.6f, fontSize * 2,
                m_titleLayout.put()))) {
            return;
        }
    }

    DWRITE_TEXT_METRICS metrics;
    m_titleLayout->GetMetrics(&metrics);
    const float iconSize = item.icon && Simple::g_settings.showIcon ? std::round(fontSize * 1.6f) : 0;
    const float gap = item.icon && Simple::g_settings.showIcon ? std::round(fontSize * 0.6f) : 0;
    const float left =
        std::round((m_width - (iconSize + gap + metrics.width)) / 2);
    const float centerY = std::round(m_height * 0.91f);

    if (item.icon && Simple::g_settings.showIcon) {
        const D2D1_RECT_F iconRect{left, centerY - iconSize / 2,
                                   left + iconSize, centerY + iconSize / 2};
        m_ctx->DrawBitmap(item.icon.get(), iconRect, opacity,
                          D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC);
    }

    const D2D1_POINT_2F origin{left + iconSize + gap - metrics.left,
                               centerY - metrics.height / 2 - metrics.top};
    m_brush->SetColor(D2D1::ColorF(0, 0, 0, 0.55f * opacity));
    m_ctx->DrawTextLayout({origin.x, origin.y + 2}, m_titleLayout.get(),
                          m_brush.get());
    m_brush->SetColor(D2D1::ColorF(1, 1, 1, opacity));
    m_ctx->DrawTextLayout(origin, m_titleLayout.get(), m_brush.get());
}

void Switcher::RenderFrame() {
    const double now = NowSeconds();
    const double dt = std::clamp(now - m_lastFrame, 0.0, 0.05);
    m_lastFrame = now;

    if (m_state == State::Open && AltReleased(now) && EndSwitching()) {
        BeginClose(true);
    }

    // Critically damped spring towards the target.
    const double omega = 15.0 * m_settings.flipSpeed;
    constexpr double kStep = 1.0 / 480;
    for (double remaining = dt; remaining > 0; remaining -= kStep) {
        const double h = std::min(remaining, kStep);
        const double acceleration =
            omega * omega * (m_target - m_scroll) - 2 * omega * m_velocity;
        m_velocity += acceleration * h;
        m_scroll += m_velocity * h;
    }
    if (std::fabs(m_target - m_scroll) < 1e-4 &&
        std::fabs(m_velocity) < 1e-3) {
        m_scroll = (double)m_target;
        m_velocity = 0;
    }
    // Keep the numbers small; only their value modulo the count matters.
    if (const int count = (int)m_items.size();
        count && std::llabs(m_target) > count * 1000LL) {
        const long long shift = m_target - PositiveMod(m_target, count);
        m_target -= shift;
        m_scroll -= (double)shift;
    }

    const float t = m_open.Value(now);

    for (auto& item : m_items) {
        PollFrames(*item);
    }
    BuildDrawList(t);

    m_ctx->SetTarget(m_targetBitmap.get());
    m_ctx->BeginDraw();
    m_ctx->Clear(D2D1::ColorF(0, 0, 0, 0));

    const D2D1_RECT_F screen{0, 0, m_width, m_height};
    if (m_background) {
        m_ctx->DrawBitmap(m_background.get(), screen, t,
                          D2D1_INTERPOLATION_MODE_LINEAR);
    }
    if (m_settings.dimOpacity > 0) {
        m_brush->SetColor(SharedColor(false, m_settings.dimOpacity * t));
        m_ctx->FillRectangle(screen, m_brush.get());
    }

    const bool panel = IsPanelStyle(m_settings.style);
    if (panel) {
        DrawPanelBack(t);
    }
    for (const DrawEntry& entry : m_drawList) {
        DrawCard(entry, t);
    }
    if (panel) {
        DrawPanelFront(t);
    } else {
        DrawTitle(t);
    }

    HRESULT hr = m_ctx->EndDraw();
    m_ctx->SetTarget(nullptr);
    if (SUCCEEDED(hr)) {
        hr = m_swapChain->Present(1, 0);
    }
    if (FAILED(hr)) {
        Wh_Log(L"Rendering failed: 0x%08X", (UINT)hr);
        HandleDeviceLost();
        return;
    }

    if (m_state == State::Closing && m_open.Done(now)) {
        FinishClose();
    }
}

// Looking an icon up can wait on the window's app (WM_GETICON) or the shell,
// which would delay even a quick Alt+Tab. So the icons are kept across
// sessions, and RefreshIcons checks them after a session.
com_ptr<ID2D1Bitmap1> Switcher::GetIconBitmap(HWND hwnd) {
    if (auto it = m_iconCache.find(hwnd); it != m_iconCache.end()) {
        return it->second.bitmap;
    }

    CachedIcon entry;
    if (HICON icon = GetWindowIcon(hwnd)) {
        entry.bitmap = CreateIconBitmap(icon);
        if (entry.bitmap) {
            entry.source = icon;
        }
    }
    if (!entry.bitmap) {
        entry.bitmap = CreateAppIconBitmap(hwnd);
    }
    m_iconCache[hwnd] = entry;
    return entry.bitmap;
}

// Forgets closed windows and picks up icons that changed.
void Switcher::RefreshIcons() {
    std::erase_if(m_iconCache,
                  [](const auto& entry) { return !IsWindow(entry.first); });

    for (auto& [hwnd, entry] : m_iconCache) {
        HICON icon = GetWindowIcon(hwnd);
        if (icon && icon != entry.source) {
            if (auto bitmap = CreateIconBitmap(icon)) {
                entry = {icon, bitmap};
            }
        } else if (!icon && !entry.bitmap) {
            // Still no window icon; the app may have finished starting.
            entry.bitmap = CreateAppIconBitmap(hwnd);
        }
    }
}

// Packaged (UWP) apps, hosted in an ApplicationFrameWindow, usually have no
// window icon. Their icon comes from the shell, by the app's AppUserModelID.
com_ptr<ID2D1Bitmap1> Switcher::CreateAppIconBitmap(HWND hwnd) {
    com_ptr<IPropertyStore> store;
    if (FAILED(SHGetPropertyStoreForWindow(hwnd, IID_PPV_ARGS(store.put())))) {
        return nullptr;
    }
    std::wstring appId;
    PROPVARIANT value;
    PropVariantInit(&value);
    if (SUCCEEDED(store->GetValue(kPKEY_AppUserModel_ID, &value)) &&
        value.vt == VT_LPWSTR && value.pwszVal) {
        appId = value.pwszVal;
    }
    PropVariantClear(&value);
    if (appId.empty()) {
        return nullptr;
    }

    com_ptr<IShellItemImageFactory> imageFactory;
    if (FAILED(SHCreateItemInKnownFolder(kFOLDERID_AppsFolder, 0,
                                         appId.c_str(),
                                         IID_PPV_ARGS(imageFactory.put())))) {
        return nullptr;
    }
    const int size = (int)std::round(64 * m_dpiScale);
    HBITMAP hbitmap = nullptr;
    if (FAILED(imageFactory->GetImage({size, size}, SIIGBF_ICONONLY,
                                      &hbitmap))) {
        return nullptr;
    }

    com_ptr<IWICBitmap> wicBitmap;
    com_ptr<IWICFormatConverter> converter;
    com_ptr<ID2D1Bitmap1> bitmap;
    const bool ok =
        SUCCEEDED(m_wicFactory->CreateBitmapFromHBITMAP(
            hbitmap, nullptr, WICBitmapUsePremultipliedAlpha,
            wicBitmap.put())) &&
        SUCCEEDED(m_wicFactory->CreateFormatConverter(converter.put())) &&
        SUCCEEDED(converter->Initialize(
            wicBitmap.get(), GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone, nullptr, 0,
            WICBitmapPaletteTypeMedianCut)) &&
        SUCCEEDED(m_ctx->CreateBitmapFromWicBitmap(converter.get(), nullptr,
                                                   bitmap.put()));
    DeleteObject(hbitmap);
    return ok ? bitmap : nullptr;
}

com_ptr<ID2D1Bitmap1> Switcher::CreateIconBitmap(HICON icon) {
    com_ptr<IWICBitmap> wicBitmap;
    com_ptr<IWICFormatConverter> converter;
    com_ptr<ID2D1Bitmap1> bitmap;
    if (FAILED(m_wicFactory->CreateBitmapFromHICON(icon, wicBitmap.put())) ||
        FAILED(m_wicFactory->CreateFormatConverter(converter.put())) ||
        FAILED(converter->Initialize(wicBitmap.get(),
                                     GUID_WICPixelFormat32bppPBGRA,
                                     WICBitmapDitherTypeNone, nullptr, 0,
                                     WICBitmapPaletteTypeMedianCut)) ||
        FAILED(m_ctx->CreateBitmapFromWicBitmap(converter.get(), nullptr,
                                                bitmap.put()))) {
        return nullptr;
    }
    return bitmap;
}

com_ptr<ID2D1Bitmap1> Switcher::CreateTargetBitmap(UINT width, UINT height) {
    com_ptr<ID2D1Bitmap1> bitmap;
    const D2D1_BITMAP_PROPERTIES1 props = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_TARGET,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                          D2D1_ALPHA_MODE_PREMULTIPLIED));
    if (FAILED(m_ctx->CreateBitmap({width, height}, nullptr, 0, &props,
                                   bitmap.put()))) {
        return nullptr;
    }
    return bitmap;
}

// Card shown until the first frame arrives, and for minimized windows.
com_ptr<ID2D1Bitmap1> Switcher::CreatePlaceholder(const Item& item) {
    const float scale =
        std::min(1.0f, 640 / std::max(item.Width(), item.Height()));
    const UINT width = (UINT)std::max(std::lround(item.Width() * scale), 1L);
    const UINT height = (UINT)std::max(std::lround(item.Height() * scale), 1L);

    com_ptr<ID2D1Bitmap1> bitmap = CreateTargetBitmap(width, height);
    if (!bitmap) {
        return nullptr;
    }

    m_ctx->SetTarget(bitmap.get());
    m_ctx->BeginDraw();
    m_ctx->Clear(D2D1::ColorF(0, 0, 0, 0));

    const D2D1_ROUNDED_RECT card{{0.5f, 0.5f, width - 0.5f, height - 0.5f},
                                 8,
                                 8};
    m_brush->SetColor(D2D1::ColorF(0.13f, 0.13f, 0.15f, 0.96f));
    m_ctx->FillRoundedRectangle(card, m_brush.get());
    m_brush->SetColor(D2D1::ColorF(1, 1, 1, 0.14f));
    m_ctx->DrawRoundedRectangle(card, m_brush.get(), 1);

    if (item.icon) {
        const float iconSize =
            std::round(std::min({width * 0.3f, height * 0.3f, 96.0f}));
        const float x = std::round((width - iconSize) / 2);
        const float y = std::round((height - iconSize) / 2);
        m_ctx->DrawBitmap(item.icon.get(), {x, y, x + iconSize, y + iconSize},
                          1, D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC);
    }

    const HRESULT hr = m_ctx->EndDraw();
    m_ctx->SetTarget(nullptr);
    return SUCCEEDED(hr) ? bitmap : nullptr;
}

void Switcher::UpdateBackground() {
    if (m_settings.background == BackgroundMode::Dim) {
        m_background = nullptr;
        m_backgroundKey.clear();
        return;
    }

    const UINT width = m_swapWidth;
    const UINT height = m_swapHeight;

    std::wstring path;
    COLORREF color = 0;
    DESKTOP_WALLPAPER_POSITION position = DWPOS_FILL;

    com_ptr<IDesktopWallpaper> wallpaper;
    if (SUCCEEDED(CoCreateInstance(kCLSID_DesktopWallpaper, nullptr,
                                   CLSCTX_ALL,
                                   IID_PPV_ARGS(wallpaper.put())))) {
        wallpaper->GetBackgroundColor(&color);
        wallpaper->GetPosition(&position);

        // Use the wallpaper of the monitor closest to ours.
        UINT count = 0;
        wallpaper->GetMonitorDevicePathCount(&count);
        const LONG centerX = (m_monitor.left + m_monitor.right) / 2;
        const LONG centerY = (m_monitor.top + m_monitor.bottom) / 2;
        long long bestDistance = LLONG_MAX;
        for (UINT i = 0; i < count; i++) {
            LPWSTR monitorId = nullptr;
            if (FAILED(wallpaper->GetMonitorDevicePathAt(i, &monitorId))) {
                continue;
            }
            RECT rect;
            LPWSTR monitorPath = nullptr;
            if (SUCCEEDED(wallpaper->GetMonitorRECT(monitorId, &rect)) &&
                SUCCEEDED(wallpaper->GetWallpaper(monitorId, &monitorPath))) {
                const long long dx = (rect.left + rect.right) / 2 - centerX;
                const long long dy = (rect.top + rect.bottom) / 2 - centerY;
                if (dx * dx + dy * dy < bestDistance) {
                    bestDistance = dx * dx + dy * dy;
                    path = monitorPath ? monitorPath : L"";
                }
            }
            CoTaskMemFree(monitorPath);
            CoTaskMemFree(monitorId);
        }
    }

    // The wallpaper file is often replaced in place, so include its time.
    WIN32_FILE_ATTRIBUTE_DATA attributes{};
    if (!path.empty() && !GetFileAttributesExW(
                             path.c_str(), GetFileExInfoStandard, &attributes)) {
        path.clear();
    }
    const ULONGLONG fileTime =
        ((ULONGLONG)attributes.ftLastWriteTime.dwHighDateTime << 32) |
        attributes.ftLastWriteTime.dwLowDateTime;
    const std::wstring key =
        path + L"|" + std::to_wstring(fileTime) + L"|" +
        std::to_wstring(width) + L"x" + std::to_wstring(height) + L"|" +
        std::to_wstring(color) + L"|" + std::to_wstring((int)position) + L"|" +
        std::to_wstring((int)m_settings.background) + L"|" +
        std::to_wstring(m_settings.blurAmount);
    if (m_background && key == m_backgroundKey) {
        return;
    }
    m_background = nullptr;
    m_backgroundKey = key;

    // Decode the image, scaled to the size it's displayed at.
    com_ptr<ID2D1Bitmap1> image;
    D2D1_RECT_F imageRect{};
    com_ptr<IWICBitmapDecoder> decoder;
    com_ptr<IWICBitmapFrameDecode> frame;
    UINT imageWidth = 0, imageHeight = 0;
    if (!path.empty() &&
        SUCCEEDED(m_wicFactory->CreateDecoderFromFilename(
            path.c_str(), nullptr, GENERIC_READ,
            WICDecodeMetadataCacheOnDemand, decoder.put())) &&
        SUCCEEDED(decoder->GetFrame(0, frame.put())) &&
        SUCCEEDED(frame->GetSize(&imageWidth, &imageHeight)) && imageWidth &&
        imageHeight) {
        float drawWidth = (float)width;
        float drawHeight = (float)height;
        const float scaleX = width / (float)imageWidth;
        const float scaleY = height / (float)imageHeight;
        switch (position) {
            case DWPOS_FIT:
                drawWidth = imageWidth * std::min(scaleX, scaleY);
                drawHeight = imageHeight * std::min(scaleX, scaleY);
                break;
            case DWPOS_STRETCH:
                break;
            case DWPOS_CENTER:
                drawWidth = (float)imageWidth;
                drawHeight = (float)imageHeight;
                break;
            default:  // Fill, span and tile.
                drawWidth = imageWidth * std::max(scaleX, scaleY);
                drawHeight = imageHeight * std::max(scaleX, scaleY);
                break;
        }
        imageRect = {(width - drawWidth) / 2, (height - drawHeight) / 2,
                     (width + drawWidth) / 2, (height + drawHeight) / 2};

        com_ptr<IWICBitmapScaler> scaler;
        com_ptr<IWICFormatConverter> converter;
        const UINT scaledWidth = (UINT)std::max(std::lround(drawWidth), 1L);
        const UINT scaledHeight = (UINT)std::max(std::lround(drawHeight), 1L);
        if (SUCCEEDED(m_wicFactory->CreateBitmapScaler(scaler.put())) &&
            SUCCEEDED(scaler->Initialize(frame.get(), scaledWidth,
                                         scaledHeight,
                                         WICBitmapInterpolationModeFant)) &&
            SUCCEEDED(m_wicFactory->CreateFormatConverter(converter.put())) &&
            SUCCEEDED(converter->Initialize(
                scaler.get(), GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone, nullptr, 0,
                WICBitmapPaletteTypeMedianCut))) {
            m_ctx->CreateBitmapFromWicBitmap(converter.get(), nullptr,
                                             image.put());
        }
    }

    com_ptr<ID2D1Bitmap1> composed = CreateTargetBitmap(width, height);
    if (!composed) {
        return;
    }
    m_ctx->SetTarget(composed.get());
    m_ctx->BeginDraw();
    m_ctx->Clear(D2D1::ColorF(GetRValue(color) / 255.0f,
                              GetGValue(color) / 255.0f,
                              GetBValue(color) / 255.0f, 1));
    if (image) {
        m_ctx->DrawBitmap(image.get(), imageRect, 1,
                          D2D1_INTERPOLATION_MODE_LINEAR);
    }
    HRESULT hr = m_ctx->EndDraw();
    m_ctx->SetTarget(nullptr);
    if (FAILED(hr)) {
        return;
    }

    if (m_settings.background != BackgroundMode::BlurredWallpaper) {
        m_background = composed;
        return;
    }

    com_ptr<ID2D1Effect> blur;
    com_ptr<ID2D1Bitmap1> blurred = CreateTargetBitmap(width, height);
    if (!blurred ||
        FAILED(m_ctx->CreateEffect(CLSID_D2D1GaussianBlur, blur.put()))) {
        m_background = composed;
        return;
    }
    blur->SetInput(0, composed.get());
    blur->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION,
                   m_settings.blurAmount);
    blur->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE,
                   (UINT32)D2D1_BORDER_MODE_HARD);
    blur->SetValue(D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION,
                   kGaussianBlurOptimizationQuality);

    m_ctx->SetTarget(blurred.get());
    m_ctx->BeginDraw();
    m_ctx->Clear(D2D1::ColorF(0, 0, 0, 1));
    m_ctx->DrawImage(blur.get());
    hr = m_ctx->EndDraw();
    m_ctx->SetTarget(nullptr);
    m_background = SUCCEEDED(hr) ? blurred : composed;
}

DWORD WINAPI UiThreadProc(LPVOID parameter) {
    // Work in physical pixels everywhere.
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    try {
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
    } catch (const winrt::hresult_error& e) {
        Wh_Log(L"init_apartment failed: 0x%08X", (UINT)e.code());
        SetEvent((HANDLE)parameter);
        return 1;
    }

    {
        Switcher switcher;
        g_switcher = &switcher;
        const bool created = switcher.CreateOverlay();
        // The creator only waits for the window.
        SetEvent((HANDLE)parameter);
        if (created) {
            switcher.Activate();
            switcher.Run();
        }
        switcher.Shutdown();
        g_switcher = nullptr;
    }

    winrt::uninit_apartment();
    return 0;
}

bool StartThread(LPTHREAD_START_ROUTINE proc, HANDLE* thread, DWORD* threadId) {
    HANDLE started = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!started) {
        return false;
    }
    *thread = CreateThread(nullptr, 0, proc, started, 0, threadId);
    if (*thread) {
        WaitForSingleObject(started, INFINITE);
    }
    CloseHandle(started);
    return *thread != nullptr;
}

void StopThread(HANDLE* thread, DWORD threadId) {
    if (!*thread) {
        return;
    }
    PostThreadMessageW(threadId, WM_QUIT, 0, 0);
    WaitForSingleObject(*thread, INFINITE);
    CloseHandle(*thread);
    *thread = nullptr;
}

void InitModuleGlobals() {
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                           GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<LPCWSTR>(&InitModuleGlobals),
                       &g_module);
    g_hotkeyMessage = RegisterWindowMessageW(kHotkeyMessageName);
}

bool IsExplorerProcess() {
    WCHAR path[MAX_PATH];
    const DWORD length = GetModuleFileNameW(nullptr, path, ARRAYSIZE(path));
    if (!length || length == ARRAYSIZE(path)) {
        return false;
    }
    PCWSTR name = wcsrchr(path, L'\\');
    name = name ? name + 1 : path;
    return _wcsicmp(name, L"explorer.exe") == 0;
}

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// The switcher runs in a dedicated windhawk.exe process (see the tool mod
// implementation below), not in explorer.

BOOL VistaToolInit() {
    Wh_Log(L">");

    InitModuleGlobals();

    if (!StartThread(UiThreadProc, &g_uiThread, &g_uiThreadId) ||
        !g_overlayWnd) {
        Wh_Log(L"Failed to start the UI thread");
        StopThread(&g_uiThread, g_uiThreadId);
        return FALSE;
    }

    if (!StartThread(HookThreadProc, &g_hookThread, &g_hookThreadId)) {
        Wh_Log(L"Failed to start the hook thread");
        StopThread(&g_uiThread, g_uiThreadId);
        return FALSE;
    }
    return TRUE;
}

void VistaToolUninit() {
    Wh_Log(L">");

    g_ready = false;
    StopThread(&g_hookThread, g_hookThreadId);
    g_switching = false;
    StopThread(&g_uiThread, g_uiThreadId);
    g_overlayWnd = nullptr;
}

void VistaToolSettingsChanged() {
    Wh_Log(L">");

    if (g_overlayWnd) {
        PostMessageW(g_overlayWnd, WM_APP_SETTINGS, 0, 0);
    }
}

////////////////////////////////////////////////////////////////////////////////
bool g_simpleRenderer = false;
bool WantsSimple() { auto value = WindhawkUtils::StringSetting::make(L"renderer"); return wcscmp(value,L"simple")==0; }
BOOL WhTool_ModInit() { g_simpleRenderer=WantsSimple(); return g_simpleRenderer ? Simple::WhTool_ModInit() : VistaToolInit(); }
void WhTool_ModUninit() { if(g_simpleRenderer) Simple::WhTool_ModUninit(); else VistaToolUninit(); }
void WhTool_ModSettingsChanged() {
    bool next=WantsSimple();
    if(next!=g_simpleRenderer) { WhTool_ModUninit(); g_simpleRenderer=next; if(!WhTool_ModInit()) Wh_Log(L"Renderer initialization failed"); }
    else if(g_simpleRenderer) Simple::WhTool_ModSettingsChanged(); else VistaToolSettingsChanged();
}

// The part loaded in explorer.exe only hands the Alt+Tab hotkey over (see
// StartExplorerPart).

bool g_isExplorer;

using GetMessageW_t = BOOL(WINAPI*)(LPMSG, HWND, UINT, UINT);
using PeekMessageW_t = BOOL(WINAPI*)(LPMSG, HWND, UINT, UINT, UINT);
GetMessageW_t OriginalGetMessageW;
PeekMessageW_t OriginalPeekMessageW;
void RelayRetrievedHotkey(MSG* msg) {
    if(msg && msg->message==WM_HOTKEY && HIWORD(msg->lParam)==VK_TAB) {
        UINT modifiers=LOWORD(msg->lParam);
        if((modifiers&MOD_ALT) && !(modifiers&(MOD_CONTROL|MOD_WIN)) && ForwardHotkey((modifiers&MOD_SHIFT)!=0)) msg->message=WM_NULL;
    }
}
BOOL WINAPI PlusGetMessageW(LPMSG msg, HWND window, UINT low, UINT high) {
    BOOL result=OriginalGetMessageW(msg,window,low,high);
    if(result>0) RelayRetrievedHotkey(msg);
    return result;
}
BOOL WINAPI PlusPeekMessageW(LPMSG msg, HWND window, UINT low, UINT high, UINT flags) {
    BOOL result=OriginalPeekMessageW(msg,window,low,high,flags);
    if(result && (flags&PM_REMOVE)) RelayRetrievedHotkey(msg);
    return result;
}

BOOL ExplorerModInit() {
    Wh_Log(L">");

    InitModuleGlobals();
    HMODULE user=GetModuleHandleW(L"user32.dll");
    void* get=(void*)GetProcAddress(user,"GetMessageW");
    void* peek=(void*)GetProcAddress(user,"PeekMessageW");
    return get && peek && Wh_SetFunctionHook(get,(void*)PlusGetMessageW,(void**)&OriginalGetMessageW) && Wh_SetFunctionHook(peek,(void*)PlusPeekMessageW,(void**)&OriginalPeekMessageW);
}

void ExplorerModUninit() {
    Wh_Log(L">");

    StopExplorerPart();
}

void ExplorerModSettingsChanged() {
    Wh_Log(L">");

    // Retrieval hooks stay installed; the renderer advertises readiness.
}

////////////////////////////////////////////////////////////////////////////////
// Windhawk tool mod implementation for mods which don't need to inject to other
// processes or hook other functions. Context:
// https://github.com/ramensoftware/windhawk/wiki/Mods-as-tools:-Running-mods-in-a-dedicated-process
//
// The mod will load and run in a dedicated windhawk.exe process.
//
// Paste the code below as part of the mod code, and use these callbacks:
// * WhTool_ModInit
// * WhTool_ModSettingsChanged
// * WhTool_ModUninit
//
// Currently, other callbacks are not supported.
//
// This mod also targets explorer.exe: there, each callback calls the explorer
// part instead (the lines marked "explorer.exe part").

bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;

void WINAPI EntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

BOOL Wh_ModInit() {
    // explorer.exe part.
    if (IsExplorerProcess()) {
        g_isExplorer = true;
        return ExplorerModInit();
    }

    DWORD sessionId;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &sessionId) &&
        sessionId == 0) {
        return FALSE;
    }

    bool isExcluded = false;
    bool isToolModProcess = false;
    bool isCurrentToolModProcess = false;
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);
    if (!argv) {
        Wh_Log(L"CommandLineToArgvW failed");
        return FALSE;
    }

    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-service") == 0 ||
            wcscmp(argv[i], L"-service-start") == 0 ||
            wcscmp(argv[i], L"-service-stop") == 0) {
            isExcluded = true;
            break;
        }
    }

    for (int i = 1; i < argc - 1; i++) {
        if (wcscmp(argv[i], L"-tool-mod") == 0) {
            isToolModProcess = true;
            if (wcscmp(argv[i + 1], WH_MOD_ID) == 0) {
                isCurrentToolModProcess = true;
            }
            break;
        }
    }

    LocalFree(argv);

    if (isExcluded) {
        return FALSE;
    }

    if (isCurrentToolModProcess) {
        g_toolModProcessMutex =
            CreateMutex(nullptr, TRUE, L"windhawk-tool-mod_" WH_MOD_ID);
        if (!g_toolModProcessMutex) {
            Wh_Log(L"CreateMutex failed");
            ExitProcess(1);
        }

        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            Wh_Log(L"Tool mod already running (%s)", WH_MOD_ID);
            ExitProcess(1);
        }

        if (!WhTool_ModInit()) {
            ExitProcess(1);
        }

        IMAGE_DOS_HEADER* dosHeader =
            (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders =
            (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);

        DWORD entryPointRVA = ntHeaders->OptionalHeader.AddressOfEntryPoint;
        void* entryPoint = (BYTE*)dosHeader + entryPointRVA;

        Wh_SetFunctionHook(entryPoint, (void*)EntryPoint_Hook, nullptr);
        return TRUE;
    }

    if (isToolModProcess) {
        return FALSE;
    }

    g_isToolModProcessLauncher = true;
    return TRUE;
}

void Wh_ModAfterInit() {
    if (!g_isToolModProcessLauncher) {
        return;
    }

    WCHAR currentProcessPath[MAX_PATH];
    switch (GetModuleFileName(nullptr, currentProcessPath,
                              ARRAYSIZE(currentProcessPath))) {
        case 0:
        case ARRAYSIZE(currentProcessPath):
            Wh_Log(L"GetModuleFileName failed");
            return;
    }

    WCHAR
    commandLine[MAX_PATH + 2 +
                (sizeof(L" -tool-mod \"" WH_MOD_ID "\"") / sizeof(WCHAR)) - 1];
    swprintf_s(commandLine, L"\"%s\" -tool-mod \"%s\"", currentProcessPath,
               WH_MOD_ID);

    HANDLE token = nullptr; TOKEN_ELEVATION elevation{}; DWORD returned=0;
    bool elevated=false;
    if(OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&token)) {
        elevated=GetTokenInformation(token,TokenElevation,&elevation,sizeof(elevation),&returned) && elevation.TokenIsElevated;
        CloseHandle(token);
    }
    if(Wh_GetIntSetting(L"elevatedHost") && !elevated) {
        std::wstring args = L"-tool-mod \"" WH_MOD_ID L"\"";
        SHELLEXECUTEINFOW execute{sizeof(execute)};
        execute.fMask=SEE_MASK_NOCLOSEPROCESS|SEE_MASK_NOASYNC;
        execute.lpVerb=L"runas"; execute.lpFile=currentProcessPath;
        execute.lpParameters=args.c_str(); execute.nShow=SW_HIDE;
        if(ShellExecuteExW(&execute)) { if(execute.hProcess) CloseHandle(execute.hProcess); return; }
        Wh_Log(L"Administrator host unavailable, using normal host: %u",GetLastError());
    }

    HMODULE kernelModule = GetModuleHandle(L"kernelbase.dll");
    if (!kernelModule) {
        kernelModule = GetModuleHandle(L"kernel32.dll");
        if (!kernelModule) {
            Wh_Log(L"No kernelbase.dll/kernel32.dll");
            return;
        }
    }

    using CreateProcessInternalW_t = BOOL(WINAPI*)(
        HANDLE hUserToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
        LPSECURITY_ATTRIBUTES lpProcessAttributes,
        LPSECURITY_ATTRIBUTES lpThreadAttributes, WINBOOL bInheritHandles,
        DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory,
        LPSTARTUPINFOW lpStartupInfo,
        LPPROCESS_INFORMATION lpProcessInformation,
        PHANDLE hRestrictedUserToken);
    CreateProcessInternalW_t pCreateProcessInternalW =
        (CreateProcessInternalW_t)GetProcAddress(kernelModule,
                                                 "CreateProcessInternalW");
    if (!pCreateProcessInternalW) {
        Wh_Log(L"No CreateProcessInternalW");
        return;
    }

    STARTUPINFO si{
        .cb = sizeof(STARTUPINFO),
        .dwFlags = STARTF_FORCEOFFFEEDBACK,
    };
    PROCESS_INFORMATION pi;
    if (!pCreateProcessInternalW(nullptr, currentProcessPath, commandLine,
                                 nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS,
                                 nullptr, nullptr, &si, &pi, nullptr)) {
        Wh_Log(L"CreateProcess failed");
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void Wh_ModSettingsChanged() {
    // explorer.exe part.
    if (g_isExplorer) {
        ExplorerModSettingsChanged();
        return;
    }

    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    // explorer.exe part.
    if (g_isExplorer) {
        ExplorerModUninit();
        return;
    }

    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModUninit();
    ExitProcess(0);
}
}

BOOL Wh_ModInit() { return Vista::Wh_ModInit(); }
void Wh_ModAfterInit() { Vista::Wh_ModAfterInit(); }
void Wh_ModSettingsChanged() { Vista::Wh_ModSettingsChanged(); }
void Wh_ModUninit() { Vista::Wh_ModUninit(); }
