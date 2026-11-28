// ==WindhawkMod==
// @id              seamless-icons
// @name            Seamless Icons
// @description     Icon themes, app icons and shortcut arrows in one mod, each part with its own switch
// @version         1.0.3
// @author          DavidHiFi, FireBlade, m417z, ferrys, Dev-StudioCode
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         GPL-3.0
// @include         *
// @exclude         dwm.exe
// @exclude         cloudflared.exe
// @exclude         ollama.exe
// @exclude         ollama app.exe
// @exclude         tailscale-ipn.exe
// @exclude         esbuild.exe
// @compilerOptions -luser32 -lshell32 -lole32 -luuid -lcrypt32 -ladvapi32 -lcomctl32 -loleaut32 -lgdiplus -lgdi32 -lshlwapi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Icons

![Seamless Icons preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-icons.png)

Every icon mod in one place. Each part has its own switch, so you can use only the parts you want. Turn a part off and Windows gives its own icons back.

## What it does

- **App icons.** Ableton Live, Yapfast, Zen Browser and Steam get blue and mauve icons on their windows, taskbar buttons, tray icons and shortcuts. The Settings window gets the Catppuccin settings icon.
- **Store app icons.** Store and system apps get new icons in the Start menu, in search and in Task Manager. A Catppuccin theme is built in.
- **Windows icon swaps.** Swap almost 100 built-in Windows icons, like folders and drives, for icons you pick.
- **Icon themes.** Pick a whole icon theme, such as Catppuccin, and Explorer and other apps show it. No Windows file is changed.
- **Shortcut arrows.** Takes the little arrows off shortcut icons on the desktop and in Explorer.

## How to use

Open the mod settings. Each part starts with a Turn on switch. Set it, then use that part's other options.

- **App icons.** One switch for each app, and three more for where the icon shows: windows, shortcuts and the tray.
- **Store app icons.** Pick a theme, or point a Store app at your own icons. Aero and Luna download the first time you pick them.
- **Windows icon swaps.** Type the path to an icon file. To use an icon inside a file, add a comma and its number, like `C:\Windows\System32\shell32.dll,32`.
- **Icon themes.** Pick a theme, or add your own theme folders. Full guide to theme files: https://windhawk.net/mods/icon-resource-redirect
- **Shortcut arrows.** Leave the path empty for no arrow at all, or give a small icon file to draw your own.

## Notes

- Icon themes can skip programs. Add a name such as `Discord*.exe` to "Programs to leave alone". A star matches any letters.
- Windows icon swaps works in programs that ask Windows for its standard icons. It does not change message boxes.
- App icons works in 64-bit programs only. For Zen Browser it leaves Zen's tab and helper processes alone and changes only the browser itself.
- This mod keeps its own files in its own folder. If you used the five separate mods before, remove them once this one is on. Keep their theme folders until your settings point somewhere new.

## What's new in 1.0.2

- The Settings window now uses the blue-to-mauve gear icon.

## What's new in 1.0.0

- First release. It joins Mocha App Icons, UWP Assets Redirect Plus, Icon Customizer, Resource Redirect and Remove Shortcut Arrow Icons. Each part keeps its own code and its own settings.
- Every part has a Turn on switch.
- Icon themes has a new "Programs to leave alone" list.

## Credits

- Mocha App Icons and the suite: [DavidHiFi](https://github.com/DavidHiFi)
- UWP Assets Redirect, by [ferrys](https://github.com/atferrys/uwp-assets-redirect), with changes by DavidHiFi
- Icon Customizer, by [FireBlade](https://github.com/FireBlade211)
- Resource Redirect, by [m417z](https://github.com/m417z)
- Remove Shortcut Arrow Icons, by [Dev-StudioCode](https://github.com/Dev-StudioCode/Hide-Desktop-Shortcut-Icon), with changes by DavidHiFi
- The Catppuccin icon theme in Icon themes is by niivu. Catppuccin is at https://github.com/catppuccin

Ableton and Live are trademarks of Ableton AG. Steam and the Steam logo are trademarks of Valve Corporation. Yapfast and Zen Browser are free software by their own authors. This mod is not made by or linked to any of them.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- appIcons:
  - enabled: true
    $name: Turn on
    $description: "Use this part. When it is off, Windows gives its own icons back"
  - ableton: true
    $name: Ableton Live
    $description: "Give Ableton Live the blue and mauve icon. When off, its own icon comes back"
  - yapfast: true
    $name: Yapfast
    $description: "Give Yapfast the blue and mauve icon. When off, its own icon comes back"
  - zen: true
    $name: Zen Browser
    $description: "Give Zen Browser the blue and mauve icon. When off, its own icon comes back"
  - steam: true
    $name: Steam
    $description: "Give Steam the blue and mauve icon, tray included. When off, its own icon comes back"
  - settings: true
    $name: Windows Settings
    $description: "Give the Settings window the Catppuccin settings icon in its title bar. When off, its own icon comes back"
  - windowIcons: true
    $name: Window icons
    $description: "Use it on the app's windows, its taskbar button and in Alt+Tab"
  - shortcutIcons: true
    $name: Shortcut icons
    $description: "Use it on the app's shortcuts in the Start menu, on the desktop and pinned to the taskbar"
  - trayIcon: true
    $name: Tray icon
    $description: "Use it on the app's icon by the clock, if it has one"
  $name: App icons
  $description: "Blue and mauve icons for Ableton Live, Yapfast, Zen Browser, Steam and the Settings window"
- storeAppIcons:
  - enabled: true
    $name: Turn on
    $description: "Use this part. When it is off, Windows gives its own icons back"
  - icon-theme: ""
    $name: Icon theme
    $description: >-
      Catppuccin is built in. Aero and Luna are downloaded the first time you
      pick them. Suggested: Catppuccin.
    $options:
    - "": None
    - "local/catppuccin": Catppuccin (by niivu)
    - "ferrys/aero": Aero (by @ferrys)
    - "ferrys/luna": Luna (by @ferrys)
  - theme-paths: [""]
    $name: Theme paths
    $description: >-
      Each path can be a folder with custom assets files and a theme.ini file,
      or the .ini theme file itself.

      Follow the guide on how to create a theme file in the details tab for more information.

  - windows-apps:
    - - bundle: ""
        $name: Bundle name
        $description: >-
          The application bundle without any version appended.

          You can get easily get this via Task Manager, follow the guide in
          the details tab for more information.
      - redirect: ""
        $name: Redirection folder or .ico file
        $description: >-
          The folder with the custom assets files or a single .ico file.

          Note: If you provide a single .ico file, only app icons will be replaced.
          You can find more information in the details tab.
    $name: WindowsApps Redirections
    $description: >-
      Redirections for the apps found in "C:\Program Files\WindowsApps".

      This is used for Microsoft Store apps and some system apps.

  - system-apps:
    - - bundle: ""
        $name: Bundle name
        $description: >-
          The application bundle without any version appended.

          You can get easily get this via Task Manager, follow the guide in
          the details tab for more information.
      - redirect: ""
        $name: Redirection folder or .ico file
        $description: >-
          The folder with the custom assets files or a single .ico file.

          Note: If you provide a single .ico file, only app icons will be replaced.
          You can find more information in the details tab.
    $name: SystemApps Redirections
    $description: >-
      Redirections for the apps found in "C:\Windows\SystemApps".

      This is used for some system apps like "Wireless Display".
  - custom:
    - - assets-path: ""
        $name: Original path
        $description: >-
          The full application assets path.

          Can be a pattern where '*' matches any number of characters.
      - redirect: ""
        $name: Redirection folder
        $description: The folder with the custom assets files.
    $name: Custom Redirections
    $description: >-
      Redirections for system apps that aren't found in any of the previous folders.

      This can be used for apps like "Settings".

      You'll have to specify the assets folder in the path this time and not
      simply the app bundle.

  - grant-permissions: true
    $name: Grant permissions
    $description: >-
      Some applications and features, such as the Start Menu search,
      require special permissions in order to access the Assets files.

      Enabling this feature will automatically grant the correct permissions
      to the redirected files while the mod is active.
  $name: Store app icons
  $description: "New icons for Store and system apps, with a Catppuccin theme built in"
- iconCustomizer:
  - enabled: true
    $name: Turn on
    $description: "Use this part. When it is off, Windows gives its own icons back"
  - DOCNOASSOC: ""
    $name: Document (No Association)
    $description: "Icon: Document of a type with no associated application."
  - DOCASSOC: ""
    $name: Document (With Association)
    $description: "Icon: Document of a type with an associated application."
  - APPLICATION: ""
    $name: Application
    $description: "Icon: Generic application with no custom icon."
  - FOLDER: ""
    $name: Folder
    $description: "Icon: Folder (generic, unspecified state)."
  - FOLDEROPEN: ""
    $name: Folder (Open)
    $description: "Icon: Folder (open)."
  - DRIVE525: ""
    $name: 5.25 drive
    $description: "Icon: 5.25-inch disk drive."
  - DRIVE35: ""
    $name: 3.5 drive
    $description: "Icon: 3.5-inch disk drive."
  - DRIVEREMOVE: ""
    $name: Removable Drive
    $description: "Icon: Removable drive."
  - DRIVEFIXED: ""
    $name: Fixed Drive
    $description: "Icon: Fixed drive (hard disk)."
  - DRIVENET: ""
    $name: Network Drive
    $description: "Icon: Network drive (connected)."
  - DRIVENETDISABLED: ""
    $name: Disconnected Network Drive
    $description: "Icon: Network drive (disconnected)."
  - DRIVECD: ""
    $name: CD Drive
    $description: "Icon: CD drive."
  - DRIVERAM: ""
    $name: RAM Disk
    $description: "Icon: RAM disk drive."
  - WORLD: ""
    $name: World
    $description: "Icon: The entire network."
  - SERVER: ""
    $name: Server
    $description: "Icon: A computer on the network."
  - PRINTER: ""
    $name: Printer
    $description: "Icon: A local printer or print destination."
  - MYNETWORK: ""
    $name: Network
    $description: "Icon: The Network virtual folder."
  - FIND: ""
    $name: Find
    $description: "Icon: The Find feature."
  - HELP: ""
    $name: Help
    $description: "Icon: The Help feature."
  - SHARE: ""
    $name: Share
    $description: "Icon: Overlay for a shared item."
  - LINK: ""
    $name: Link
    $description: "Icon: Overlay for a shortcut."
  - SLOWFILE: ""
    $name: Slow File
    $description: "Icon: Overlay for items that are expected to be slow to access."
  - RECYCLER: ""
    $name: Recycler
    $description: "Icon: The Recycle Bin (empty)."
  - RECYCLERFULL: ""
    $name: Recycler (Full)
    $description: "Icon: The Recycle Bin (not empty)."
  - MEDIACDAUDIO: ""
    $name: Audio CD
    $description: "Icon: Audio CD media."
  - LOCK: ""
    $name: Lock
    $description: "Icon: Security lock."
  - AUTOLIST: ""
    $name: Auto-List
    $description: "Icon: A virtual folder that contains the results of a search."
  - PRINTERNET: ""
    $name: Network Printer
    $description: "Icon: A network printer."
  - SERVERSHARE: ""
    $name: Server Share
    $description: "Icon: A server shared on a network."
  - PRINTERFAX: ""
    $name: Fax Printer (Local)
    $description: "Icon: A local fax printer."
  - PRINTERFAXNET: ""
    $name: Fax Printer (Network)
    $description: "Icon: A network fax printer."
  - PRINTERFILE: ""
    $name: Printer File
    $description: "Icon: A file that receives the output of a operation."
  - STACK: ""
    $name: Stack
    $description: "Icon: A category that results from a command to organize the contents of a folder."
  - MEDIASVCD: ""
    $name: SVCD Media
    $description: "Icon: Super Video CD (SVCD) media."
  - STUFFEDFOLDER: ""
    $name: Stuffed Folder
    $description: "Icon: A folder that contains only subfolders as child items."
  - DRIVEUNKNOWN: ""
    $name: Unknown Drive
    $description: "Icon: Unknown drive type."
  - DRIVEDVD: ""
    $name: DVD Drive
    $description: "Icon: DVD drive."
  - MEDIADVD: ""
    $name: DVD Media
    $description: "Icon: DVD media."
  - MEDIADVDRAM: ""
    $name: DVD-RAM Media
    $description: "Icon: DVD-RAM media."
  - MEDIADVDRW: ""
    $name: DVD-RW Media
    $description: "Icon: DVD-RW media."
  - MEDIADVDR: ""
    $name: DVD-R Media
    $description: "Icon: DVD-R media."
  - MEDIADVDROM: ""
    $name: DVD-ROM Media
    $description: "Icon: DVD-ROM media."
  - MEDIACDAUDIOPLUS: ""
    $name: CD+ Media
    $description: "Icon: CD+ (enhanced audio CD) media."
  - MEDIACDRW: ""
    $name: CD-RW Media
    $description: "Icon: CD-RW media."
  - MEDIACDR: ""
    $name: CD-R Media
    $description: "Icon: CD-R media."
  - MEDIACDBURN: ""
    $name: CD (Burning)
    $description: "Icon: A writable CD in the process of being burned."
  - MEDIABLANKCD: ""
    $name: CD (Blank)
    $description: "Icon: Blank writable CD media."
  - MEDIACDROM: ""
    $name: CD-ROM Media
    $description: "Icon: CD-ROM media."
  - AUDIOFILES: ""
    $name: Audio File
    $description: "Icon: An audio file."
  - IMAGEFILES: ""
    $name: Image File
    $description: "Icon: An image file."
  - VIDEOFILES: ""
    $name: Video File
    $description: "Icon: A video file."
  - MIXEDFILES: ""
    $name: Mixed File
    $description: "Icon: A mixed file."
  - FOLDERBACK: ""
    $name: Folder Back
    $description: "Icon: Folder back."
  - FOLDERFRONT: ""
    $name: Folder Front
    $description: "Icon: Folder front."
  - SHIELD: ""
    $name: Shield
    $description: "Icon: Security shield."
  - WARNING: ""
    $name: Warning
    $description: "Icon: Warning."
  - INFO: ""
    $name: Info
    $description: "Icon: Informational."
  - iERROR: ""
    $name: Error
    $description: "Icon: Error."
  - KEY: ""
    $name: Key
    $description: "Icon: Key."
  - SOFTWARE: ""
    $name: Software
    $description: "Icon: Software."
  - RENAME: ""
    $name: Rename
    $description: "Icon: A UI item, such as a button, that issues a rename command."
  - iDELETE: ""
    $name: Delete
    $description: "Icon: A UI item, such as a button, that issues a delete command."
  - MEDIAAUDIODVD: ""
    $name: Audio DVD Media
    $description: "Icon: Audio DVD media."
  - MEDIAMOVIEDVD: ""
    $name: Movie DVD Media
    $description: "Icon: Movie DVD media."
  - MEDIAENHANCEDCD: ""
    $name: Enhanced CD Media
    $description: "Icon: Enhanced CD media."
  - MEDIAENHANCEDDVD: ""
    $name: Enhanced DVD Media
    $description: "Icon: Enhanced DVD media."
  - MEDIAHDDVD: ""
    $name: HD-DVD Media
    $description: "Icon: High definition DVD media in the HD DVD format."
  - MEDIABLURAY: ""
    $name: Blu-Ray Media
    $description: "Icon: High definition DVD media in the Blu-ray Discâ„¢ format."
  - MEDIAVCD: ""
    $name: VCD Media
    $description: "Icon: Video CD (VCD) media."
  - MEDIADVDPLUSR: ""
    $name: DVD+R Media
    $description: "Icon: DVD+R media."
  - MEDIADVDPLUSRW: ""
    $name: DVD+RW Media
    $description: "Icon: DVD+RW media."
  - DESKTOPPC: ""
    $name: Desktop PC
    $description: "Icon: A desktop computer."
  - MOBILEPC: ""
    $name: Mobile PC
    $description: "Icon: A mobile computer (laptop)."
  - USERS: ""
    $name: Users
    $description: "Icon: The Users Control Panel item."
  - MEDIASMARTMEDIA: ""
    $name: Smart Media
    $description: "Icon: Smart media."
  - MEDIACOMPACTFLASH: ""
    $name: Compact Flash
    $description: "Icon: CompactFlash media."
  - DEVICECELLPHONE: ""
    $name: Cell Phone
    $description: "Icon: A cell phone."
  - DEVICECAMERA: ""
    $name: Device Camera
    $description: "Icon: A digital camera."
  - DEVICEVIDEOCAMERA: ""
    $name: Device Video Camera
    $description: "Icon: A digital video camera."
  - DEVICEAUDIOPLAYER: ""
    $name: Device Audio Player
    $description: "Icon: An audio player."
  - NETWORKCONNECT: ""
    $name: Network Connect
    $description: "Icon: Connect to network."
  - INTERNET: ""
    $name: Internet
    $description: "Icon: The Internet Control Panel item."
  - ZIPFILE: ""
    $name: ZIP File
    $description: "Icon: A compressed file with a .zip file name extension."
  - SETTINGS: ""
    $name: Settings
    $description: "Icon: The Control Panel item."
  - DRIVEHDDVD: ""
    $name: HD-DVD Drive
    $description: "Icon: High definition DVD drive (any type - HD DVD-ROM, HD DVD-R, HD-DVD-RAM) that uses the HD DVD format."
  - DRIVEBD: ""
    $name: Blu-ray Disc Drive
    $description: "Icon: High definition DVD drive (any type - BD-ROM, BD-R, BD-RE) that uses the Blu-ray Disc format."
  - MEDIAHDDVDROM: ""
    $name: HD DVD-ROM Media
    $description: "Icon: High definition DVD-ROM media in the HD DVD-ROM format."
  - MEDIAHDDVDR: ""
    $name: HD DVD-R Media
    $description: "Icon: High definition DVD-R media in the HD DVD-R format."
  - MEDIAHDDVDRAM: ""
    $name: HD DVD-RAM Media
    $description: "Icon: High definition DVD-RAM media in the HD DVD-RAM format."
  - MEDIABDROM: ""
    $name: Blu-ray Disc BD-ROM Media
    $description: "Icon: High definition DVD-ROM media in the Blu-ray Disc BD-ROM format."
  - MEDIABDR: ""
    $name: Blu-ray Disc BD-R Media
    $description: "Icon: High definition write-once media in the Blu-ray Disc BD-R format."
  - MEDIABDRE: ""
    $name: Blu-ray Disc BD-RE Media
    $description: "Icon: High definition read/write media in the Blu-ray Disc BD-RE format."
  - CLUSTEREDDRIVE: ""
    $name: Clustered Drive
    $description: "Icon: A cluster disk array."
  $name: Windows icon swaps
  $description: "Swap almost 100 built-in Windows icons for icons you pick"
- resourceRedirect:
  - enabled: true
    $name: Turn on
    $description: "Use this part. When it is off, Windows gives its own icons back"
  - skipPrograms: [""]
    $name: Programs to leave alone
    $description: "Names of programs this part must not touch, such as Discord*.exe. A star matches any letters. Add the full path if two programs share a name"
  - iconTheme: ""
    $name: Icon theme
    $description: >-
      The icon theme to use. For details, refer to the mod description.
    $options:
    - "": None
    - All White Icons|themes/icons/niivu/All%20White%20Icons.zip: All White Icons (by niivu)
    - Antu alt|themes/icons/niivu/antu%20alt.zip: Antu alt (by niivu)
    - Antu|themes/icons/niivu/antu.zip: Antu (by niivu)
    - Kuyen Alt|themes/icons/niivu/kuyen%20alt.zip: Kuyen Alt (by niivu)
    - Kuyen|themes/icons/niivu/kuyen.zip: Kuyen (by niivu)
    - ARC Symbolic|themes/icons/niivu/ARC%20Symbolic.zip: ARC Symbolic (by niivu)
    - ARC|themes/icons/niivu/ARC.zip: ARC (by niivu)
    - Arc Neutral Brown|themes/icons/niivu/arc-neutral%20brown.zip: Arc Neutral Brown (by niivu)
    - Arc Neutral Grey|themes/icons/niivu/arc-neutral%20grey.zip: Arc Neutral Grey (by niivu)
    - BananaOneUI|themes/icons/niivu/BANAANA%20OneUI.zip: BananaOneUI (by niivu)
    - Big Sur DarkMode|themes/icons/niivu/Big%20Sur%20DarkMode.zip: Big Sur DarkMode (by niivu)
    - Big Sur LightMode|themes/icons/niivu/Big%20Sur%20LightMode.zip: Big Sur LightMode (by niivu)
    - Blanked DarkMode|themes/icons/niivu/blanked%20dark%20mode.zip: Blanked DarkMode (by niivu)
    - Blanked LightMode|themes/icons/niivu/blanked%20light%20mode.zip: Blanked LightMode (by niivu)
    - Bonny|themes/icons/niivu/bonny%20by%20niivu.zip: Bonny (by niivu)
    - Bouquet|themes/icons/niivu/bouquet.zip: Bouquet (by niivu)
    - Buuf|themes/icons/niivu/buuf.zip: Buuf (by niivu)
    - CakeOS 2.0|themes/icons/niivu/cakeOS%202.0.zip: CakeOS 2.0 (by niivu)
    - CakeOS Blue|themes/icons/niivu/Cake%20OS%20Blue.zip: CakeOS Blue (by niivu)
    - CakeOS Green|themes/icons/niivu/Cake%20OS%20Green.zip: CakeOS Green (by niivu)
    - CakeOS Orange|themes/icons/niivu/Cake%20OS%20Orange.zip: CakeOS Orange (by niivu)
    - CakeOS Purple|themes/icons/niivu/Cake%20OS%20Purple.zip: CakeOS Purple (by niivu)
    - CakeOS Red|themes/icons/niivu/Cake%20OS%20Red.zip: CakeOS Red (by niivu)
    - Candy Original|themes/icons/niivu/candy%20original%20folders.zip: Candy Original (by niivu)
    - Candy Outlined|themes/icons/niivu/candy%20outlined%20folders.zip: Candy Outlined (by niivu)
    - Catppuccin|themes/icons/niivu/Catppuccin.zip: Catppuccin (by niivu)
    - Catppuccin Blue|themes/icons/niivu/Catppuccin%20blue.zip: Catppuccin Blue (by niivu)
    - Catppuccin Flamingo|themes/icons/niivu/Catppuccin%20flamingo.zip: Catppuccin Flamingo (by niivu)
    - Catppuccin Green|themes/icons/niivu/Catppuccin%20green.zip: Catppuccin Green (by niivu)
    - Catppuccin Latte|themes/icons/niivu/Catppuccin%20Latte.zip: Catppuccin Latte (by niivu)
    - Catppuccin Lavender|themes/icons/niivu/Catppuccin%20lavender.zip: Catppuccin Lavender (by niivu)
    - Catppuccin Maroon|themes/icons/niivu/Catppuccin%20maroon.zip: Catppuccin Maroon (by niivu)
    - Catppuccin Mauve|themes/icons/niivu/Catppuccin%20mauve.zip: Catppuccin Mauve (by niivu)
    - Catppuccin Mocha|themes/icons/niivu/Catppuccin%20Mocha.zip: Catppuccin Mocha (by niivu)
    - Catppuccin Peach|themes/icons/niivu/Catppuccin%20peach.zip: Catppuccin Peach (by niivu)
    - Catppuccin Pink|themes/icons/niivu/Catppuccin%20pink.zip: Catppuccin Pink (by niivu)
    - Catppuccin Red|themes/icons/niivu/Catppuccin%20red.zip: Catppuccin Red (by niivu)
    - Catppuccin Sky|themes/icons/niivu/Catppuccin%20sky.zip: Catppuccin Sky (by niivu)
    - Catppuccin Teal|themes/icons/niivu/Catppuccin%20teal.zip: Catppuccin Teal (by niivu)
    - Catppuccin Yellow|themes/icons/niivu/Catppuccin%20yellow.zip: Catppuccin Yellow (by niivu)
    - Deepin Blue DarkMode|themes/icons/niivu/Deepin%20Blue%20-%20for%20dark%20themes.zip: Deepin Blue DarkMode (by niivu)
    - Deepin Blue LightMode|themes/icons/niivu/Deepin%20Blue%20-%20for%20light%20themes.zip: Deepin Blue LightMode (by niivu)
    - Deepin Brown DarkMode|themes/icons/niivu/Deepin%20Brown%20-%20for%20dark%20themes.zip: Deepin Brown DarkMode (by niivu)
    - Deepin Brown LightMode|themes/icons/niivu/Deepin%20Brown%20-%20for%20light%20themes.zip: Deepin Brown LightMode (by niivu)
    - Deepin Green DarkMode|themes/icons/niivu/Deepin%20Green%20-%20for%20dark%20themes.zip: Deepin Green DarkMode (by niivu)
    - Deepin Green LightMode|themes/icons/niivu/Deepin%20Green%20-%20for%20light%20themes.zip: Deepin Green LightMode (by niivu)
    - Deepin Slate DarkMode|themes/icons/niivu/Deepin%20Slate%20-%20for%20dark%20themes.zip: Deepin Slate DarkMode (by niivu)
    - Deepin Slate LightMode|themes/icons/niivu/Deepin%20Slate%20-%20for%20light%20themes.zip: Deepin Slate LightMode (by niivu)
    - Deepo|themes/icons/niivu/Deepo%20Icon%20pack.zip: Deepo (by niivu)
    - Tango|themes/icons/niivu/Tango.zip: Tango (by niivu)
    - Tangerine|themes/icons/niivu/Tangerine.zip: Tangerine (by niivu)
    - Gnome|themes/icons/niivu/Gnome.zip: Gnome (by niivu)
    - Cheser|themes/icons/niivu/Cheser.zip: Cheser (by niivu)
    - Gnome Brave|themes/icons/niivu/Gnome%20Brave.zip: Gnome Brave (by niivu)
    - Gnome Human|themes/icons/niivu/Gnome%20Human.zip: Gnome Human (by niivu)
    - Gnome Noble|themes/icons/niivu/Gnome%20Noble.zip: Gnome Noble (by niivu)
    - Gnome Wine|themes/icons/niivu/Gnome%20Wine.zip: Gnome Wine (by niivu)
    - Gnome Wise|themes/icons/niivu/Gnome%20Wise.zip: Gnome Wise (by niivu)
    - Elementary|themes/icons/niivu/Elementary.zip: Elementary (by niivu)
    - Elementary New|themes/icons/niivu/Elementary%20NEW.zip: Elementary New (by niivu)
    - Humanity|themes/icons/niivu/Humanity.zip: Humanity (by niivu)
    - Everblush|themes/icons/niivu/Everblush.zip: Everblush (by niivu)
    - Everforest|themes/icons/niivu/everforest.zip: Everforest (by niivu)
    - Everforest Blank|themes/icons/niivu/everforest%20blank.zip: Everforest Blank (by niivu)
    - Eyecandy|themes/icons/niivu/Eyecandy.zip: Eyecandy (by niivu)
    - Faba|themes/icons/niivu/FABA.zip: Faba (by niivu)
    - Faba Symbolic|themes/icons/niivu/FABA%20Symbolic.zip: Faba Symbolic (by niivu)
    - Slate|themes/icons/niivu/SLATE.zip: Slate (by niivu)
    - Slate Symbolic|themes/icons/niivu/SLATE%20Symbolic.zip: Slate Symbolic (by niivu)
    - Fetch|themes/icons/niivu/Fetch.zip: Fetch (by niivu)
    - Fluent|themes/icons/niivu/Fluent.zip: Fluent (by niivu)
    - Fluent Keys Night|themes/icons/niivu/Fluent%20Keys%20Night.zip: Fluent Keys Night (by niivu)
    - Fluent Keys Day|themes/icons/niivu/Fluent%20Keys%20Day.zip: Fluent Keys Day (by niivu)
    - Flurry|themes/icons/niivu/FLURRY.zip: Flurry (by niivu)
    - Gruvbox|themes/icons/niivu/Gruvbox.zip: Gruvbox (by niivu)
    - Gruvbox Plus Olive|themes/icons/niivu/gruvbox%20plus%20-%20Olive.zip: Gruvbox Plus Olive (by niivu)
    - Gruvbox Numix|themes/icons/niivu/Gruvbox%20numix.zip: Gruvbox Numix (by niivu)
    - Haiku BeOS|themes/icons/niivu/Haiku%20BeOS.zip: Haiku BeOS (by niivu)
    - Janguru Blue|themes/icons/niivu/janguru%20blue.zip: Janguru Blue (by niivu)
    - Janguru BlueGrey|themes/icons/niivu/janguru%20bluegrey.zip: Janguru BlueGrey (by niivu)
    - Janguru Brown|themes/icons/niivu/janguru%20brown.zip: Janguru Brown (by niivu)
    - Janguru Green|themes/icons/niivu/janguru%20green.zip: Janguru Green (by niivu)
    - Janguru Grey|themes/icons/niivu/janguru%20grey.zip: Janguru Grey (by niivu)
    - Janguru Orange|themes/icons/niivu/janguru%20orange.zip: Janguru Orange (by niivu)
    - koZ|themes/icons/niivu/koZ.zip: koZ (by niivu)
    - Kripton Flatery|themes/icons/niivu/Kripton%20Flatery.zip: Kripton Flatery (by niivu)
    - Linuxfx 11 AIO|themes/icons/niivu/Linuxfx-11-AIO.zip: Linuxfx 11 AIO (by niivu)
    - Linuxfx 11 Lite|themes/icons/niivu/Linuxfx-11-lite.zip: Linuxfx 11 Lite (by niivu)
    - Lol|themes/icons/niivu/lol.zip: Lol (by niivu)
    - Lumicons Folders|themes/icons/niivu/Lumicons%20Folders.zip: Lumicons Folders (by niivu)
    - Lumicons Symbols|themes/icons/niivu/Lumicons%20Symbols.zip: Lumicons Symbols (by niivu)
    - macOSx|themes/icons/niivu/mac%20osx.zip: macOSx (by niivu)
    - macOS Regular|themes/icons/niivu/macOS%20Regular.zip: macOS Regular (by niivu)
    - macOS Blue|themes/icons/niivu/macOS%20blue.zip: macOS Blue (by niivu)
    - macOS Yellow|themes/icons/niivu/macOS%20Yellow%20Folders.zip: macOS Yellow (by niivu)
    - macOS DarkMode|themes/icons/niivu/macOS%20Dark%20Mode.zip: macOS DarkMode (by niivu)
    - macOS LightMode|themes/icons/niivu/macOS%20Light%20Mode.zip: macOS LightMode (by niivu)
    - macPac DarkMode|themes/icons/niivu/macpac%20darkmode.zip: macPac DarkMode (by niivu)
    - macPac LightMode|themes/icons/niivu/macpac%20lightmode.zip: macPac LightMode (by niivu)
    - Mechanical|themes/icons/niivu/mechanical.zip: Mechanical (by niivu)
    - Minium2|themes/icons/niivu/MINIUM2.zip: Minium2 (by niivu)
    - Nord Papirus|themes/icons/niivu/Nord%20Papirus.zip: Nord Papirus (by niivu)
    - Nord Papirus NovaGalactic|themes/icons/niivu/Nord-Papirus-Nova-galactic.zip: Nord Papirus NovaGalactic (by niivu)
    - Numix|themes/icons/niivu/numix.zip: Numix (by niivu)
    - Numix Blue|themes/icons/niivu/numix-remix-blue.zip: Numix Blue (by niivu)
    - Numix Green|themes/icons/niivu/numix-remix-green.zip: Numix Green (by niivu)
    - Numix macOS|themes/icons/niivu/numix-remix-macos.zip: Numix macOS (by niivu)
    - Numix Slate|themes/icons/niivu/numix-remix-slate.zip: Numix Slate (by niivu)
    - Numix Windows|themes/icons/niivu/numix-remix-windows.zip: Numix Windows (by niivu)
    - NUX|themes/icons/niivu/NUX.zip: NUX (by niivu)
    - One Dark Pro|themes/icons/niivu/One%20Dark%20Pro.zip: One Dark Pro (by niivu)
    - One Dark Pro Alt|themes/icons/niivu/One%20Dark%20Pro%20alt.zip: One Dark Pro Alt (by niivu)
    - One UI4|themes/icons/niivu/OneUI4.zip: One UI4 (by niivu)
    - OS X Minimalism|themes/icons/niivu/OS%20X%20Minimalism.zip: OS X Minimalism (by niivu)
    - OS X Minimalism Symbolic|themes/icons/niivu/OS%20X%20Minimalism%20Symbolic.zip: OS X Minimalism Symbolic (by niivu)
    - Paper|themes/icons/niivu/Paper.zip: Paper (by niivu)
    - Papirus Black|themes/icons/niivu/Papirus%20Black.zip: Papirus Black (by niivu)
    - Papirus BlueGrey|themes/icons/niivu/Papirus%20Blue%20Grey.zip: Papirus BlueGrey (by niivu)
    - Papirus Blue|themes/icons/niivu/Papirus%20Blue.zip: Papirus Blue (by niivu)
    - Papirus Brown|themes/icons/niivu/Papirus%20Brown.zip: Papirus Brown (by niivu)
    - Papirus Deep Orange|themes/icons/niivu/Papirus%20Deep%20Orange.zip: Papirus Deep Orange (by niivu)
    - Papirus Dracula|themes/icons/niivu/Papirus%20Dracula.zip: Papirus Dracula (by niivu)
    - Papirus Grey|themes/icons/niivu/Papirus%20Grey.zip: Papirus Grey (by niivu)
    - Papirus Magenta|themes/icons/niivu/Papirus%20Magenta.zip: Papirus Magenta (by niivu)
    - Papirus Pink|themes/icons/niivu/Papirus%20Pink.zip: Papirus Pink (by niivu)
    - Papirus Red|themes/icons/niivu/Papirus%20Red.zip: Papirus Red (by niivu)
    - Papirus Solarized|themes/icons/niivu/Papirus%20Solarized.zip: Papirus Solarized (by niivu)
    - Papirus Teal|themes/icons/niivu/Papirus%20Teal.zip: Papirus Teal (by niivu)
    - Papirus Violet|themes/icons/niivu/Papirus%20Violet.zip: Papirus Violet (by niivu)
    - Tokyo Night|themes/icons/niivu/Tokyo%20Night%20blank.zip: Tokyo Night (by niivu)
    - Tokyo Night Papirus|themes/icons/niivu/Tokyo%20Night%20Papirus.zip: Tokyo Night Papirus (by niivu)
    - Tokyo Night SE Papirus|themes/icons/niivu/Tokyo%20Night%20SE%20Papirus.zip: Tokyo Night SE Papirus (by niivu)
    - Pink Folders|themes/icons/niivu/pink%20folders.zip: Pink Folders (by niivu)
    - Post|themes/icons/niivu/post.zip: Post (by niivu)
    - Pure Dark|themes/icons/niivu/Pure%20for%20dark%20or%20dark%20side%20panel%20themes.zip: Pure Dark (by niivu)
    - Pure Light|themes/icons/niivu/Pure%20for%20light%20themes.zip: Pure Light (by niivu)
    - Quixotic Day|themes/icons/niivu/Quixotic-SE%20Day%20AIO.zip: Quixotic Day (by niivu)
    - Quixotic Dark|themes/icons/niivu/Quixotic-SE%20Dark%20AIO.zip: Quixotic Dark (by niivu)
    - Quixotic Night|themes/icons/niivu/Quixotic-SE%20Night%20AIO.zip: Quixotic Night (by niivu)
    - Rose Pine|themes/icons/niivu/Rose%20Pine.zip: Rose Pine (by niivu)
    - Solarized Day AIO|themes/icons/niivu/solarized%20Day%20AIO.zip: Solarized Day AIO (by niivu)
    - Solarized Night AIO|themes/icons/niivu/solarized%20Night%20AIO.zip: Solarized Night AIO (by niivu)
    - Solus|themes/icons/niivu/Solus.zip: Solus (by niivu)
    - Somatic Rebirth|themes/icons/niivu/Somatic%20Rebirth.zip: Somatic Rebirth (by niivu)
    - Spaceshrooms Blue|themes/icons/niivu/space-shrooms-blue.zip: Spaceshrooms Blue (by niivu)
    - Spaceshrooms Green|themes/icons/niivu/space-shrooms-green.zip: Spaceshrooms Green (by niivu)
    - Spaceshrooms Yellow|themes/icons/niivu/space-shrooms-yellow.zip: Spaceshrooms Yellow (by niivu)
    - Super Remix Blue|themes/icons/niivu/Super%20Remix%20Blue.zip: Super Remix Blue (by niivu)
    - Super Remix Green|themes/icons/niivu/Super%20Remix%20Green.zip: Super Remix Green (by niivu)
    - Super Remix Slate|themes/icons/niivu/Super%20Remix%20Slate.zip: Super Remix Slate (by niivu)
    - Sweet Awesomeness|themes/icons/niivu/Sweet%20Awesomeness.zip: Sweet Awesomeness (by niivu)
    - Sweetness Blue|themes/icons/niivu/Sweetness%20Blue%20folders.zip: Sweetness Blue (by niivu)
    - Sweetness Neutral|themes/icons/niivu/Sweetness%20Neutral.zip: Sweetness Neutral (by niivu)
    - Sweetness Original|themes/icons/niivu/Sweetness%20Original.zip: Sweetness Original (by niivu)
    - Sweetness Pink|themes/icons/niivu/Sweetness%20Pink%20folders.zip: Sweetness Pink (by niivu)
    - Sweetness Purple|themes/icons/niivu/Sweetness%20Purple%20folders.zip: Sweetness Purple (by niivu)
    - Sweet Rainbow|themes/icons/niivu/Sweet-Rainbow.zip: Sweet Rainbow (by niivu)
    - UOS|themes/icons/niivu/Uos%20Icon%20pack.zip: UOS (by niivu)
    - Windows 11 New (default)|themes/icons/niivu/Windows%2011%20New%20%28default%29.zip: Windows 11 New (default) (by niivu)
    - Windows 11 New Folders Blue|themes/icons/niivu/Windows%2011%20New%20Folders%20Blue.zip: Windows 11 New Folders Blue (by niivu)
    - Windows 11 New Folders Green|themes/icons/niivu/Windows%2011%20New%20Folders%20Green.zip: Windows 11 New Folders Green (by niivu)
    - Windows 11 New Folders Purple|themes/icons/niivu/Windows%2011%20New%20Folders%20Purple.zip: Windows 11 New Folders Purple (by niivu)
    - Windows 11 New Folders Slate|themes/icons/niivu/Windows%2011%20New%20Folders%20Slate.zip: Windows 11 New Folders Slate (by niivu)
    - Windows 11 New Folders Yellow|themes/icons/niivu/Windows%2011%20New%20Folders%20Yellow.zip: Windows 11 New Folders Yellow (by niivu)
    - PaneVista|themes/icons/SoftwareType/PaneVista.zip: 'PaneVista (by SoftwareType, credit: ImSwordQueen)'
    - Pane7|themes/icons/ImSwordQueen/Pane7.zip: Pane7 (by ImSwordQueen)
    - Pane8.1|themes/icons/NicSonic/Pane8.1.zip: Pane8.1 (by NicSonic)
    - Minecraft Axolotle|themes/icons/Wasiabbas4pk/Minecraft%20Axolotle.zip: 'Minecraft Axolotle (by WasiXGamer, credit: dalps/minecraft11)'
    - Minecraft Fox|themes/icons/Wasiabbas4pk/Minecraft%20Fox.zip: 'Minecraft Fox (by WasiXGamer, credit: dalps/minecraft11)'
    - Minecraft TNT|themes/icons/Wasiabbas4pk/Minecraft%20TNT.zip: 'Minecraft TNT (by WasiXGamer, credit: dalps/minecraft11)'
    - Minecraft Panda|themes/icons/Wasiabbas4pk/Minecraft%20Panda.zip: 'Minecraft Panda (by WasiXGamer, credit: dalps/minecraft11)'
    - Minecraft Creeper|themes/icons/Wasiabbas4pk/Minecraft%20Creeper.zip: 'Minecraft Creeper (by WasiXGamer, credit: dalps/minecraft11)'
    - Minecraft Ender Dragon|themes/icons/Wasiabbas4pk/Minecraft%20Ender%20Dragon.zip: 'Minecraft Ender Dragon (by WasiXGamer, credit: dalps/minecraft11)'
    - Minecraft Shulker (Blue)|themes/icons/Wasiabbas4pk/Minecraft%20Shulker%28Blue%29.zip: 'Minecraft Shulker (Blue) (by WasiXGamer, credit: dalps/minecraft11)'
    - Minecraft Shulker (Black)|themes/icons/Wasiabbas4pk/Minecraft%20Shulker%28Black%29.zip: 'Minecraft Shulker (Black) (by WasiXGamer, credit: dalps/minecraft11)'
  - disableThumbnails: false
    $name: Disable folder thumbnails
    $description: >-
      Make Explorer folders use a generic folder icon instead of showing
      thumbnails of their contents. This works better with some icon themes.
  - allResourceRedirect: false
    $name: Redirect all loaded resources (experimental)
    $description: >-
      Try to redirect all loaded resources, not only the supported resources
      that are listed in the description.
  - themePaths: [""]
    $name: Theme paths
    $description: >-
      Each path can be a folder with alternative resource files and the theme.ini
      file, or the .ini theme file itself.
  - redirectionResourcePaths:
    - - original: ""
        $name: The redirected resource file
        $description: >-
          The original file from which resources are loaded. Can be a pattern
          where '*' matches any number of characters and '?' matches any single
          character.
      - redirect: ""
        $name: The redirection resource file
        $description: The custom resource file that will be used instead.
    $name: Redirection resource paths
  - themeFolder: ""
    $name: Theme folder (deprecated)
    $description: >-
      A folder with alternative resource files and theme.ini.

      This option will be removed in the future. Please use the new "Theme paths"
      option above.
  $name: Icon themes
  $description: "Load a whole icon theme, or other files, in place of the ones inside Windows files"
- shortcutArrows:
  - enabled: true
    $name: Turn on
    $description: "Use this part. When it is off, Windows gives its own icons back"
  - custom_icon_path: ""
    $name: Custom Shortcut Icon Path (Optional)
    $description: Leave empty for fully transparent arrows. To use a custom badge, specify the path to a .ico file with artwork in the bottom-left corner and the rest transparent.
  $name: Shortcut arrows
  $description: "Takes the little arrows off shortcut icons"
*/
// ==/WindhawkModSettings==

// Generated by gen.py from the five live sources. Do not edit by hand, rerun gen.py.

#include <windhawk_utils.h>
#include <initguid.h>
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include <commctrl.h>
#include <wincrypt.h>
#include <atomic>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <cwchar>
#include <winternl.h>
#include <Aclapi.h>
#include <sddl.h>
#include <winrt/base.h>
#include <comutil.h>
#include <shldisp.h>
#include <gdiplus.h>
#include <format>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <shlwapi.h>
#include <psapi.h>
#include <filesystem>
#include <functional>
#include <optional>
#include <shared_mutex>
#include <string_view>
#include <commoncontrols.h>
#include <cwctype>
#include <initializer_list>

// ===================================================================
// Part: App icons (appIcons)
// Mocha App Icons 1.3.0 by DavidHiFi. MIT license.
// ===================================================================
#ifdef _WIN64
namespace mod_appIcons {
namespace app_icons {


enum App { kNone = -1, kAbleton = 0, kYapfast = 1, kSettings = 2, kZen = 3 };

struct AppInfo {
    PCWSTR setting;  // the app's own switch
    PCWSTR folder;   // its folder under Mocha App Icons
    PCWSTR file;     // the icon file
};

static constexpr AppInfo kApps[] = {
    {L"appIcons.ableton", L"Ableton", L"Ableton-Mocha.ico"},
    {L"appIcons.yapfast", L"Yapfast", L"Yapfast-Mocha.ico"},
    {L"appIcons.settings", L"Settings", L"Settings-Catppuccin.ico"},
    {L"appIcons.zen", L"Zen", L"Zen-Mocha.ico"},
};

static int g_app = kNone;
static std::atomic_bool g_trayOn{true};
static std::atomic_bool g_windowsOn{true};
static std::atomic_bool g_shortcutsOn{true};

static HANDLE g_stopEvent;
static HANDLE g_settingsEvent;
static HANDLE g_worker;
static UINT g_applyMsg;

static void ReadSettings() {
    bool appOn = Wh_GetIntSetting(kApps[g_app].setting) != 0;
    bool settings = g_app == kSettings;
    g_trayOn = !settings && appOn && Wh_GetIntSetting(L"appIcons.trayIcon") != 0;
    g_windowsOn = appOn && Wh_GetIntSetting(L"appIcons.windowIcons") != 0;
    g_shortcutsOn = !settings && appOn && Wh_GetIntSetting(L"appIcons.shortcutIcons") != 0;
}

// ---------------------------------------------------------------- the icon

static std::wstring IconFile() {
    wchar_t folder[MAX_PATH];
    if (FAILED(SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, folder))) return {};
    return std::wstring(folder) + L"\\Mocha App Icons\\" + kApps[g_app].folder + L"\\" + kApps[g_app].file;
}

static bool WriteIcon(const std::wstring& path) {
    static constexpr char ableton[] =
        "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"
    ;
    static constexpr char yapfast[] =
        "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"
    ;
    // Zen's own rings on the blue to mauve tile (16 to 256 px).
    static constexpr char zen[] =
        "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"
    ;
    // The Catppuccin settings icon (16 to 256 px).
    static constexpr char settings[] =
        "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"
    ;
    const char* data = g_app == kAbleton ? ableton : g_app == kYapfast ? yapfast : g_app == kZen ? zen : settings;
    DWORD size = 0;
    if (!CryptStringToBinaryA(data, 0, CRYPT_STRING_BASE64, nullptr, &size, nullptr, nullptr)) return false;
    std::vector<BYTE> bytes(size);
    if (!CryptStringToBinaryA(data, 0, CRYPT_STRING_BASE64, bytes.data(), &size, nullptr, nullptr)) return false;
    HANDLE old = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
    if (old != INVALID_HANDLE_VALUE) {
        std::vector<BYTE> have(size + 1);
        DWORD got = 0;
        BOOL ok = ReadFile(old, have.data(), size + 1, &got, nullptr);
        CloseHandle(old);
        if (ok && got == size && !memcmp(have.data(), bytes.data(), size)) return true;
    }
    std::wstring dir = path.substr(0, path.rfind(L'\\'));
    SHCreateDirectoryExW(nullptr, dir.c_str(), nullptr);
    wchar_t temp[MAX_PATH];
    if (!GetTempFileNameW(dir.c_str(), L"msi", 0, temp)) return false;
    HANDLE file = CreateFileW(temp, GENERIC_WRITE, 0, nullptr, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    DWORD written = 0;
    bool ok = file != INVALID_HANDLE_VALUE && WriteFile(file, bytes.data(), size, &written, nullptr) && written == size;
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    // Yapfast starts two copies of itself; whoever loses the race finds the
    // file already in place.
    if (ok) ok = MoveFileExW(temp, path.c_str(), MOVEFILE_REPLACE_EXISTING) ||
                 GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES;
    DeleteFileW(temp);
    return ok;
}

static std::mutex g_iconMutex;
static std::map<int, HICON> g_icons;

static HICON MochaIcon(int size) {
    if (size <= 0) size = 16;
    std::lock_guard<std::mutex> lock(g_iconMutex);
    if (auto it = g_icons.find(size); it != g_icons.end()) return it->second;
    auto path = IconFile();
    if (path.empty() || !WriteIcon(path)) return nullptr;
    auto icon = (HICON)LoadImageW(nullptr, path.c_str(), IMAGE_ICON, size, size, LR_LOADFROMFILE);
    if (icon) g_icons.emplace(size, icon);
    return icon;
}

static bool OwnWindow(HWND hwnd) {
    DWORD pid = 0;
    return hwnd && GetWindowThreadProcessId(hwnd, &pid) && pid == GetCurrentProcessId();
}

// ---------------------------------------------------------------- windows
//
// Each app window is subclassed. Its icons are swapped for the Mocha ones,
// and any icon the app sets later is remembered and swapped too, so turning
// the switch off can hand back exactly what the app last asked for.

struct WindowIcons {
    HICON big = nullptr;
    HICON small = nullptr;
    bool themed = false;
};

static std::mutex g_windowMutex;
static std::map<HWND, WindowIcons> g_windows;

static HICON WindowIcon(HWND hwnd, bool big) {
    UINT dpi = GetDpiForWindow(hwnd);
    return MochaIcon(GetSystemMetricsForDpi(big ? SM_CXICON : SM_CXSMICON, dpi ? dpi : 96));
}

static void ThemeWindow(HWND hwnd, bool on) {
    WindowIcons state;
    {
        std::lock_guard<std::mutex> lock(g_windowMutex);
        state = g_windows[hwnd];
    }
    if (on == state.themed) return;
    if (on) {
        HICON big = WindowIcon(hwnd, true), small = WindowIcon(hwnd, false);
        if (!big || !small) return;
        state.big = (HICON)DefSubclassProc(hwnd, WM_SETICON, ICON_BIG, (LPARAM)big);
        state.small = (HICON)DefSubclassProc(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)small);
        state.themed = true;
    } else {
        DefSubclassProc(hwnd, WM_SETICON, ICON_BIG, (LPARAM)state.big);
        DefSubclassProc(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)state.small);
        state = {};
    }
    Wh_Log(L"window %p: %s", hwnd, on ? L"Mocha icon" : L"app icon");
    std::lock_guard<std::mutex> lock(g_windowMutex);
    g_windows[hwnd] = state;
}

static LRESULT CALLBACK IconSubclassProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, DWORD_PTR) {
    if (message == g_applyMsg && g_applyMsg) {
        ThemeWindow(hwnd, wParam != 0);
        return 1;
    }
    if (message == WM_SETICON && (wParam == ICON_BIG || wParam == ICON_SMALL)) {
        bool themed;
        {
            std::lock_guard<std::mutex> lock(g_windowMutex);
            auto it = g_windows.find(hwnd);
            themed = it != g_windows.end() && it->second.themed;
        }
        if (themed) {
            if (HICON ours = WindowIcon(hwnd, wParam == ICON_BIG)) {
                HICON previous;
                {
                    std::lock_guard<std::mutex> lock(g_windowMutex);
                    auto& state = g_windows[hwnd];
                    HICON& slot = wParam == ICON_BIG ? state.big : state.small;
                    previous = slot;
                    slot = (HICON)lParam;
                }
                DefSubclassProc(hwnd, WM_SETICON, wParam, (LPARAM)ours);
                // The app may free what it gets back, so it gets its own icon,
                // never ours.
                return (LRESULT)previous;
            }
        }
    }
    if (message == WM_NCDESTROY) {
        std::lock_guard<std::mutex> lock(g_windowMutex);
        g_windows.erase(hwnd);
    }
    return DefSubclassProc(hwnd, message, wParam, lParam);
}

static std::mutex g_attachedMutex;
static std::set<HWND> g_attached;

// ApplicationFrameHost draws the frame of every Store app; only the one
// around Settings gets the icon. Its title says so, and while it is open
// the Settings program's own window sits inside it.
static BOOL CALLBACK HostsSettings(HWND child, LPARAM found) {
    wchar_t cls[64];
    if (!GetClassNameW(child, cls, ARRAYSIZE(cls)) || wcscmp(cls, L"Windows.UI.Core.CoreWindow")) return TRUE;
    DWORD pid = 0;
    GetWindowThreadProcessId(child, &pid);
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!process) return TRUE;
    wchar_t image[MAX_PATH];
    DWORD size = ARRAYSIZE(image);
    bool ok = QueryFullProcessImageNameW(process, 0, image, &size);
    CloseHandle(process);
    PCWSTR name = ok ? wcsrchr(image, L'\\') : nullptr;
    if (name && _wcsicmp(name + 1, L"SystemSettings.exe") == 0) {
        *reinterpret_cast<bool*>(found) = true;
        return FALSE;
    }
    return TRUE;
}

static bool SettingsFrame(HWND hwnd) {
    wchar_t cls[64], title[64];
    if (!GetClassNameW(hwnd, cls, ARRAYSIZE(cls)) || wcscmp(cls, L"ApplicationFrameWindow")) return false;
    if (GetWindowTextW(hwnd, title, ARRAYSIZE(title)) && wcscmp(title, L"Settings") == 0) return true;
    bool found = false;
    EnumChildWindows(hwnd, HostsSettings, (LPARAM)&found);
    return found;
}

static bool WantsIcon(HWND hwnd) {
    if (!IsWindow(hwnd) || !OwnWindow(hwnd)) return false;
    if (GetAncestor(hwnd, GA_PARENT) != GetDesktopWindow()) return false;
    LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);
    LONG_PTR exStyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    if (style & WS_CHILD) return false;
    if (g_app == kSettings) return SettingsFrame(hwnd);
    return !(exStyle & WS_EX_TOOLWINDOW) || (exStyle & WS_EX_APPWINDOW);
}

static void Attach(HWND hwnd) {
    {
        std::lock_guard<std::mutex> lock(g_attachedMutex);
        for (auto it = g_attached.begin(); it != g_attached.end();) {
            it = IsWindow(*it) ? std::next(it) : g_attached.erase(it);
        }
        if (g_attached.contains(hwnd)) return;
    }
    if (!WindhawkUtils::SetWindowSubclassFromAnyThread(hwnd, IconSubclassProc, 0)) return;
    {
        std::lock_guard<std::mutex> lock(g_attachedMutex);
        g_attached.insert(hwnd);
    }
    SendMessageTimeoutW(hwnd, g_applyMsg, g_windowsOn ? 1 : 0, 0, SMTO_ABORTIFHUNG, 1000, nullptr);
}

static std::vector<HWND> AttachedWindows() {
    std::lock_guard<std::mutex> lock(g_attachedMutex);
    std::vector<HWND> out;
    for (HWND hwnd : g_attached) {
        if (IsWindow(hwnd)) out.push_back(hwnd);
    }
    return out;
}

// Returns false when a window did not answer, so its icons may still point
// at ours.
static bool ThemeAllWindows(bool on) {
    bool all = true;
    for (HWND hwnd : AttachedWindows()) {
        DWORD_PTR result = 0;
        if (!SendMessageTimeoutW(hwnd, g_applyMsg, on ? 1 : 0, 0, SMTO_ABORTIFHUNG, 2000, &result)) all = false;
    }
    return all;
}

static void CALLBACK ShowEvent(HWINEVENTHOOK, DWORD, HWND hwnd, LONG idObject, LONG idChild, DWORD, DWORD) {
    if (idObject == OBJID_WINDOW && idChild == CHILDID_SELF && WantsIcon(hwnd)) Attach(hwnd);
}

static BOOL CALLBACK AttachExisting(HWND hwnd, LPARAM) {
    if (IsWindowVisible(hwnd) && WantsIcon(hwnd)) Attach(hwnd);
    return TRUE;
}

// ---------------------------------------------------------------- tray

static decltype(&Shell_NotifyIconW) g_notifyIcon;

struct TrayTarget {
    bool known = false;
    HWND hwnd = nullptr;
    UINT id = 0;
    bool byGuid = false;
    GUID guid{};
};

static std::mutex g_trayMutex;
static TrayTarget g_tray;
static HICON g_stockTray;              // copy of the last icon the app itself set
static std::atomic_int g_trayThemed{-1};  // -1 untouched, 0 the app's icon, 1 ours

static BOOL CallNotify(DWORD action, PNOTIFYICONDATAW data) {
    return g_notifyIcon ? g_notifyIcon(action, data) : Shell_NotifyIconW(action, data);
}

static int TrayIconSize() {
    HWND taskbar = FindWindowW(L"Shell_TrayWnd", nullptr);
    UINT dpi = taskbar ? GetDpiForWindow(taskbar) : 0;
    return GetSystemMetricsForDpi(SM_CXSMICON, dpi ? dpi : 96);
}

static bool SameTarget(const TrayTarget& t, const NOTIFYICONDATAW* data) {
    if (!t.known) return false;
    if (t.byGuid) return (data->uFlags & NIF_GUID) && IsEqualGUID(t.guid, data->guidItem);
    return t.hwnd == data->hWnd && t.id == data->uID;
}

static BOOL WINAPI NotifyIconHook(DWORD action, PNOTIFYICONDATAW data) {
    constexpr DWORD kMinSize = offsetof(NOTIFYICONDATAW, szTip);
    if (!data || data->cbSize < kMinSize || !OwnWindow(data->hWnd)) return CallNotify(action, data);
    bool hasGuid = data->cbSize >= offsetof(NOTIFYICONDATAW, hBalloonIcon) && (data->uFlags & NIF_GUID);
    if (action == NIM_DELETE) {
        std::lock_guard<std::mutex> lock(g_trayMutex);
        if (SameTarget(g_tray, data)) {
            g_tray = {};
            g_trayThemed = -1;
        }
        return CallNotify(action, data);
    }
    if ((action != NIM_ADD && action != NIM_MODIFY) || !(data->uFlags & NIF_ICON)) return CallNotify(action, data);
    {
        std::lock_guard<std::mutex> lock(g_trayMutex);
        g_tray.known = true;
        g_tray.hwnd = data->hWnd;
        g_tray.id = data->uID;
        g_tray.byGuid = hasGuid;
        if (hasGuid) g_tray.guid = data->guidItem;
        if (g_stockTray) DestroyIcon(g_stockTray);
        g_stockTray = data->hIcon ? CopyIcon(data->hIcon) : nullptr;
    }
    if (g_trayOn) {
        if (HICON ours = MochaIcon(TrayIconSize())) {
            NOTIFYICONDATAW copy{};
            memcpy(&copy, data, std::min<size_t>(data->cbSize, sizeof(copy)));
            copy.hIcon = ours;
            BOOL ok = CallNotify(action, &copy);
            if (ok) g_trayThemed = 1;
            Wh_Log(L"tray: the app set its icon, swapped for Mocha (%d)", ok);
            return ok;
        }
    }
    BOOL ok = CallNotify(action, data);
    if (ok) g_trayThemed = 0;
    return ok;
}

static void ProbeWindow(HWND hwnd) {
    if (g_tray.known) return;
    for (UINT id = 0; id < 8; ++id) {
        NOTIFYICONDATAW data{};
        data.cbSize = sizeof(data);
        data.hWnd = hwnd;
        data.uID = id;
        // A modify with no flags changes nothing and only says whether
        // this window owns an icon with this number.
        if (CallNotify(NIM_MODIFY, &data)) {
            g_tray.known = true;
            g_tray.hwnd = hwnd;
            g_tray.id = id;
            Wh_Log(L"tray: found the app's icon on %p, id %u", hwnd, id);
            return;
        }
    }
}

static BOOL CALLBACK ProbeTopLevel(HWND hwnd, LPARAM) {
    if (OwnWindow(hwnd)) ProbeWindow(hwnd);
    return !g_tray.known;
}

// The mod loaded into an app that already shows its tray icon: find it.
static void FindTrayIcon() {
    std::lock_guard<std::mutex> lock(g_trayMutex);
    if (g_tray.known) return;
    EnumWindows(ProbeTopLevel, 0);
    HWND hwnd = nullptr;
    while (!g_tray.known && (hwnd = FindWindowExW(HWND_MESSAGE, hwnd, nullptr, nullptr))) {
        if (OwnWindow(hwnd)) ProbeWindow(hwnd);
    }
}

static BOOL CALLBACK FirstIconGroup(HMODULE, LPCWSTR, LPWSTR name, LONG_PTR out) {
    auto* found = reinterpret_cast<std::wstring*>(out);
    *found = IS_INTRESOURCE(name) ? L"#" + std::to_wstring((UINT_PTR)name) : std::wstring(name);
    return FALSE;
}

static HICON AppExeIcon(int size) {
    std::wstring name;
    HMODULE module = GetModuleHandleW(nullptr);
    EnumResourceNamesW(module, RT_GROUP_ICON, FirstIconGroup, (LONG_PTR)&name);
    return name.empty() ? nullptr : (HICON)LoadImageW(module, name.c_str(), IMAGE_ICON, size, size, 0);
}

static void RefreshTray(bool on) {
    if (on) FindTrayIcon();
    TrayTarget target;
    {
        std::lock_guard<std::mutex> lock(g_trayMutex);
        target = g_tray;
    }
    if (!target.known) return;
    if (on ? g_trayThemed == 1 : g_trayThemed != 1) return;
    NOTIFYICONDATAW data{};
    data.cbSize = sizeof(data);
    data.hWnd = target.hwnd;
    data.uID = target.id;
    data.uFlags = NIF_ICON | (target.byGuid ? NIF_GUID : 0);
    data.guidItem = target.guid;
    HICON stock = nullptr;
    if (on) {
        data.hIcon = MochaIcon(TrayIconSize());
    } else {
        {
            std::lock_guard<std::mutex> lock(g_trayMutex);
            if (g_stockTray) stock = CopyIcon(g_stockTray);
        }
        if (!stock) stock = AppExeIcon(TrayIconSize());
        data.hIcon = stock;
    }
    BOOL done = data.hIcon && CallNotify(NIM_MODIFY, &data);
    if (done) g_trayThemed = on ? 1 : 0;
    Wh_Log(L"tray: %s icon -> %d", on ? L"Mocha" : L"app", done);
    if (stock) DestroyIcon(stock);
}

// ---------------------------------------------------------------- shortcuts
//
// Same method as the Mocha Windhawk icons: the original shortcut is copied
// beside the icon before its icon changes, and that copy is how it goes back.
// Shared shortcuts need admin rights, so their edited copies go in through
// one hidden elevated copy.

struct ShortcutCopy {
    std::wstring from, to;
};

static bool g_shortcutChanged;

// The taskbar and Start keep showing a shortcut's old picture until the shell
// hears that picture changed, so tell it about both the app's and ours.
static void RefreshShellImages(const std::wstring& icon, HANDLE stop) {
    if (stop ? WaitForSingleObject(stop, 2000) == WAIT_OBJECT_0 : (Sleep(1500), false)) return;
    wchar_t exe[MAX_PATH];
    std::vector<std::wstring> files{icon};
    if (GetModuleFileNameW(nullptr, exe, ARRAYSIZE(exe))) files.push_back(exe);
    for (const auto& path : files) {
        SHFILEINFOW info{};
        if (SHGetFileInfoW(path.c_str(), 0, &info, sizeof(info), SHGFI_SYSICONINDEX) && info.iIcon > 0) {
            SHChangeNotify(SHCNE_UPDATEIMAGE, SHCNF_DWORD, (LPCVOID)(INT_PTR)info.iIcon, nullptr);
        }
    }
    Wh_Log(L"shortcuts: asked the shell to redraw the app's icons");
}

static void UpdateShortcutIcon(IShellLinkW* link, IPersistFile* file, const std::wstring& path,
                               const std::wstring& icon, const std::wstring& backup, bool enabled,
                               std::vector<ShortcutCopy>& pending) {
    if (GetFileAttributesW(path.c_str()) == INVALID_FILE_ATTRIBUTES) return;
    if (FAILED(file->Load(path.c_str(), STGM_READ))) return;
    wchar_t target[MAX_PATH], image[MAX_PATH];
    int index = 0;
    if (FAILED(link->GetPath(target, ARRAYSIZE(target), nullptr, SLGP_RAWPATH)) ||
        FAILED(link->GetIconLocation(image, ARRAYSIZE(image), &index))) return;
    wchar_t installed[MAX_PATH];
    if (!GetModuleFileNameW(nullptr, installed, ARRAYSIZE(installed))) return;
    auto same = [&](PCWSTR raw) {
        wchar_t expanded[MAX_PATH];
        DWORD count = ExpandEnvironmentStringsW(raw, expanded, ARRAYSIZE(expanded));
        return count && count <= ARRAYSIZE(expanded) && _wcsicmp(expanded, installed) == 0;
    };
    bool themedNow = _wcsicmp(image, icon.c_str()) == 0;
    bool opensApp = same(target);
    bool borrowsIcon = index == 0 && same(image);
    // A shortcut we themed earlier is still ours: its backup says so.
    if (!opensApp && !borrowsIcon && !(themedNow && GetFileAttributesW(backup.c_str()) != INVALID_FILE_ATTRIBUTES)) return;

    if (enabled == themedNow) return;
    std::wstring next = icon;
    int nextIndex = 0;
    if (enabled) {
        if (!CopyFileW(path.c_str(), backup.c_str(), FALSE)) return;
    } else {
        if (GetFileAttributesW(backup.c_str()) == INVALID_FILE_ATTRIBUTES ||
            FAILED(file->Load(backup.c_str(), STGM_READ)) ||
            FAILED(link->GetIconLocation(image, ARRAYSIZE(image), &nextIndex)) ||
            FAILED(file->Load(path.c_str(), STGM_READ))) return;
        next = image;
    }
    if (FAILED(link->SetIconLocation(next.c_str(), nextIndex))) return;
    if (SUCCEEDED(file->Save(path.c_str(), TRUE))) {
        SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATHW, path.c_str(), nullptr);
        g_shortcutChanged = true;
        Wh_Log(L"shortcut %s: %s", enabled ? L"Mocha" : L"restored", path.c_str());
        if (!enabled) DeleteFileW(backup.c_str());
        return;
    }
    std::wstring staged = backup + L".new.lnk";
    if (SUCCEEDED(file->Save(staged.c_str(), FALSE))) pending.push_back({staged, path});
}

// The admin prompt runs in a hidden helper, so the app never sits waiting on
// it: the mod waits on the helper and gives up when the app or the mod stops.
static void CopySharedShortcuts(const std::vector<ShortcutCopy>& pending, bool enabled, HANDLE stop) {
    if (pending.empty()) return;
    // A "no" to the admin prompt is remembered, so the app does not ask on
    // every start. Turning the shortcut switch back on asks again.
    bool give = !(enabled && Wh_GetIntValue(L"sharedDeclined", 0));
    std::wstring dir = pending[0].from.substr(0, pending[0].from.rfind(L'\\'));
    std::wstring batch = dir + L"\\copy-shortcuts.cmd";
    std::string text = "@chcp 65001 >nul\r\n";
    for (const auto& item : pending) {
        std::wstring line = L"@copy /y \"" + item.from + L"\" \"" + item.to + L"\" >nul\r\n";
        int size = WideCharToMultiByte(CP_UTF8, 0, line.c_str(), -1, nullptr, 0, nullptr, nullptr);
        std::string utf8(size > 0 ? size - 1 : 0, '\0');
        if (size > 1) WideCharToMultiByte(CP_UTF8, 0, line.c_str(), -1, utf8.data(), size, nullptr, nullptr);
        text += utf8;
    }
    HANDLE file = give ? CreateFileW(batch.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr)
                       : INVALID_HANDLE_VALUE;
    DWORD written = 0;
    bool ready = file != INVALID_HANDLE_VALUE && WriteFile(file, text.data(), (DWORD)text.size(), &written, nullptr) &&
                 written == text.size();
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);

    wchar_t system[MAX_PATH];
    if (ready && GetSystemDirectoryW(system, ARRAYSIZE(system))) {
        std::wstring quoted;
        for (wchar_t c : batch) quoted += c == L'\'' ? std::wstring(L"''") : std::wstring(1, c);
        std::wstring script = L"try { Start-Process -FilePath $env:ComSpec -ArgumentList '/d /c \"" + quoted +
                              L"\"' -Verb RunAs -WindowStyle Hidden -Wait -ErrorAction Stop; exit 0 } catch { exit 5 }";
        DWORD chars = 0;
        auto bytes = reinterpret_cast<const BYTE*>(script.data());
        DWORD length = (DWORD)(script.size() * sizeof(wchar_t));
        CryptBinaryToStringW(bytes, length, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, nullptr, &chars);
        std::wstring encoded(chars, L'\0');
        if (chars && CryptBinaryToStringW(bytes, length, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, encoded.data(), &chars)) {
            encoded.resize(chars);
            std::wstring command = L"\"" + std::wstring(system) +
                                   L"\\WindowsPowerShell\\v1.0\\powershell.exe\" -NoProfile -NonInteractive "
                                   L"-WindowStyle Hidden -EncodedCommand " + encoded;
            STARTUPINFOW startup{sizeof(startup)};
            startup.dwFlags = STARTF_USESHOWWINDOW;
            startup.wShowWindow = SW_HIDE;
            PROCESS_INFORMATION process{};
            if (CreateProcessW(nullptr, command.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr,
                               &startup, &process)) {
                CloseHandle(process.hThread);
                HANDLE waits[] = {process.hProcess, stop};
                DWORD wait = WaitForMultipleObjects(stop ? 2 : 1, waits, FALSE, stop ? 120000 : 30000);
                DWORD code = STILL_ACTIVE;
                if (wait == WAIT_OBJECT_0) GetExitCodeProcess(process.hProcess, &code);
                CloseHandle(process.hProcess);
                if (code == 0) {
                    for (const auto& item : pending) {
                        SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATHW, item.to.c_str(), nullptr);
                        g_shortcutChanged = true;
                        Wh_Log(L"shortcut %s (shared): %s", enabled ? L"Mocha" : L"restored", item.to.c_str());
                    }
                } else if (code == 5) {
                    Wh_Log(L"shared shortcuts: admin prompt declined");
                    if (enabled) Wh_SetIntValue(L"sharedDeclined", 1);
                }
                // Still waiting on the prompt: leave the helper its files.
                if (code == STILL_ACTIVE) return;
            }
        }
    }
    DeleteFileW(batch.c_str());
    for (const auto& item : pending) DeleteFileW(item.from.c_str());
}

static std::wstring BackupName(const std::wstring& base, const std::wstring& path) {
    // One backup per shortcut, named by a hash of its lower-case path.
    unsigned long long hash = 1469598103934665603ull;
    for (wchar_t c : path) {
        hash ^= (unsigned long long)towlower(c);
        hash *= 1099511628211ull;
    }
    wchar_t name[32];
    swprintf_s(name, L"\\%016llx.lnk", hash);
    return base + name;
}

static void FindShortcuts(const std::wstring& dir, int depth, std::vector<std::wstring>& out) {
    WIN32_FIND_DATAW found;
    HANDLE find = FindFirstFileExW((dir + L"\\*").c_str(), FindExInfoBasic, &found, FindExSearchNameMatch, nullptr, 0);
    if (find == INVALID_HANDLE_VALUE) return;
    do {
        std::wstring name = found.cFileName;
        if (name == L"." || name == L"..") continue;
        if (found.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) continue;
        if (found.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (depth > 0) FindShortcuts(dir + L"\\" + name, depth - 1, out);
        } else if (name.size() > 4 && _wcsicmp(name.c_str() + name.size() - 4, L".lnk") == 0) {
            out.push_back(dir + L"\\" + name);
        }
    } while (FindNextFileW(find, &found));
    FindClose(find);
}

static void UpdateShortcutIcons(bool enabled, HANDLE stop) {
    auto icon = IconFile();
    if (icon.empty() || (enabled && !WriteIcon(icon))) return;
    std::wstring base = icon.substr(0, icon.rfind(L'\\'));
    // Yapfast runs two copies of itself; only one edits shortcuts at a time.
    std::wstring lockName = std::wstring(L"Local\\MochaAppIcons.Shortcuts.") + kApps[g_app].folder;
    HANDLE lock = CreateMutexW(nullptr, FALSE, lockName.c_str());
    if (lock && WaitForSingleObject(lock, 60000) == WAIT_TIMEOUT) {
        CloseHandle(lock);
        return;
    }
    HRESULT init = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (SUCCEEDED(init)) {
        IShellLinkW* link = nullptr;
        if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLinkW,
                                       reinterpret_cast<void**>(&link)))) {
            IPersistFile* file = nullptr;
            if (SUCCEEDED(link->QueryInterface(IID_IPersistFile, reinterpret_cast<void**>(&file)))) {
                static constexpr struct {
                    int folder;
                    PCWSTR suffix;
                    int depth;
                } places[] = {
                    {CSIDL_COMMON_PROGRAMS, L"", 2},
                    {CSIDL_PROGRAMS, L"", 2},
                    {CSIDL_COMMON_DESKTOPDIRECTORY, L"", 0},
                    {CSIDL_DESKTOPDIRECTORY, L"", 0},
                    {CSIDL_APPDATA, L"\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar", 0},
                };
                std::vector<std::wstring> paths;
                for (const auto& place : places) {
                    wchar_t folder[MAX_PATH];
                    if (SUCCEEDED(SHGetFolderPathW(nullptr, place.folder, nullptr, SHGFP_TYPE_CURRENT, folder))) {
                        FindShortcuts(std::wstring(folder) + place.suffix, place.depth, paths);
                    }
                }
                std::vector<ShortcutCopy> pending;
                g_shortcutChanged = false;
                for (const auto& path : paths) {
                    if (stop && WaitForSingleObject(stop, 0) == WAIT_OBJECT_0) break;
                    UpdateShortcutIcon(link, file, path, icon, BackupName(base, path), enabled, pending);
                }
                file->Release();
                CopySharedShortcuts(pending, enabled, stop);
                if (g_shortcutChanged) RefreshShellImages(icon, stop);
            }
            link->Release();
        }
        CoUninitialize();
    }
    if (lock) {
        ReleaseMutex(lock);
        CloseHandle(lock);
    }
}

// The mod was turned off or removed, not just reloaded or the app closing.
static bool ModTurnedOff() {
    if (!Wh_GetIntSetting(L"appIcons.enabled")) return true;  // this part was switched off in the suite
    std::wstring key = L"SOFTWARE\\Windhawk\\Engine\\Mods\\";
    key += WH_MOD_ID;
    HKEY handle;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, key.c_str(), 0, KEY_READ, &handle) != ERROR_SUCCESS) {
        HKEY mods;
        if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods", 0, KEY_READ, &mods) != ERROR_SUCCESS) {
            return false;  // settings live elsewhere (portable Windhawk): never guess
        }
        RegCloseKey(mods);
        return true;
    }
    DWORD disabled = 0, size = sizeof(disabled);
    bool off = RegQueryValueExW(handle, L"Disabled", nullptr, nullptr, (BYTE*)&disabled, &size) == ERROR_SUCCESS &&
               disabled;
    RegCloseKey(handle);
    return off;
}

// ---------------------------------------------------------------- worker

static void ApplyAll() {
    ThemeAllWindows(g_windowsOn);
    if (g_app == kSettings) return;
    RefreshTray(g_trayOn);
    UpdateShortcutIcons(g_shortcutsOn, g_stopEvent);
}

static DWORD WINAPI Worker(LPVOID) {
    HWINEVENTHOOK hook = SetWinEventHook(EVENT_OBJECT_SHOW, EVENT_OBJECT_SHOW, nullptr, ShowEvent,
                                         GetCurrentProcessId(), 0, WINEVENT_OUTOFCONTEXT);
    // The Settings frame often shows before it gets its title.
    HWINEVENTHOOK names = g_app == kSettings
        ? SetWinEventHook(EVENT_OBJECT_NAMECHANGE, EVENT_OBJECT_NAMECHANGE, nullptr, ShowEvent,
                          GetCurrentProcessId(), 0, WINEVENT_OUTOFCONTEXT)
        : nullptr;
    EnumWindows(AttachExisting, 0);
    if (g_app != kSettings) {
        RefreshTray(g_trayOn);
        UpdateShortcutIcons(g_shortcutsOn, g_stopEvent);
    }
    // Windows saves a taskbar pin again now and then (after an Explorer
    // restart, for one) and drops our icon, so watch the pins.
    HANDLE pins = INVALID_HANDLE_VALUE;
    wchar_t appData[MAX_PATH];
    if (g_app != kSettings && SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, appData))) {
        std::wstring dir = std::wstring(appData) + L"\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar";
        pins = FindFirstChangeNotificationW(dir.c_str(), FALSE,
                                            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE);
    }
    HANDLE events[] = {g_stopEvent, g_settingsEvent, pins};
    DWORD count = pins != INVALID_HANDLE_VALUE ? 3 : 2;
    for (;;) {
        DWORD wait = MsgWaitForMultipleObjects(count, events, FALSE, INFINITE, QS_ALLINPUT);
        if (wait == WAIT_OBJECT_0) break;
        if (wait == WAIT_OBJECT_0 + 1) {
            ApplyAll();
            continue;
        }
        if (count == 3 && wait == WAIT_OBJECT_0 + 2) {
            // Let the writer finish, and fold a burst of changes into one pass.
            if (WaitForSingleObject(g_stopEvent, 3000) == WAIT_OBJECT_0) break;
            FindNextChangeNotification(pins);
            if (g_shortcutsOn) UpdateShortcutIcons(true, g_stopEvent);
            continue;
        }
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) DispatchMessageW(&msg);
    }
    if (pins != INVALID_HANDLE_VALUE) FindCloseChangeNotification(pins);
    if (names) UnhookWinEvent(names);
    if (hook) UnhookWinEvent(hook);
    return 0;
}

// ---------------------------------------------------------------- Windhawk

BOOL ModInit() {
    wchar_t image[MAX_PATH];
    if (!GetModuleFileNameW(nullptr, image, ARRAYSIZE(image))) return FALSE;
    PCWSTR name = wcsrchr(image, L'\\');
    name = name ? name + 1 : image;
    if (_wcsnicmp(name, L"Ableton Live", 12) == 0) {
        g_app = kAbleton;
    } else if (_wcsicmp(name, L"yapfast.exe") == 0) {
        g_app = kYapfast;
    } else if (_wcsicmp(name, L"zen.exe") == 0) {
        // Zen's tabs, graphics and helpers are copies of zen.exe too; only the
        // browser itself has windows and edits shortcuts.
        if (wcsstr(GetCommandLineW(), L"-contentproc")) return FALSE;
        g_app = kZen;
    } else if (_wcsicmp(name, L"ApplicationFrameHost.exe") == 0) {
        g_app = kSettings;
    } else {
        return FALSE;
    }

    ReadSettings();
    g_applyMsg = RegisterWindowMessageW(L"MochaAppIcons.Apply");
    if (g_app != kSettings) {
        Wh_SetFunctionHook((void*)Shell_NotifyIconW, (void*)NotifyIconHook, (void**)&g_notifyIcon);
    }

    g_stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_settingsEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (g_stopEvent && g_settingsEvent) g_worker = CreateThread(nullptr, 0, Worker, nullptr, 0, nullptr);
    return TRUE;
}

void ModUninit() {
    if (g_worker) {
        SetEvent(g_stopEvent);
        WaitForSingleObject(g_worker, 30000);
        CloseHandle(g_worker);
        g_worker = nullptr;
    }
    bool restored = ThemeAllWindows(false);
    WindhawkUtils::RemoveAllWindowSubclasses();
    if (g_app != kSettings) {
        RefreshTray(false);
        if (ModTurnedOff()) UpdateShortcutIcons(false, nullptr);
    }
    {
        std::lock_guard<std::mutex> lock(g_trayMutex);
        if (g_stockTray) DestroyIcon(g_stockTray);
        g_stockTray = nullptr;
    }
    // A window that did not answer may still show our icon; keep the icons
    // alive rather than leave it pointing at freed ones.
    if (restored && g_trayThemed != 1) {
        std::lock_guard<std::mutex> lock(g_iconMutex);
        for (const auto& [size, icon] : g_icons) DestroyIcon(icon);
        g_icons.clear();
    }
    if (g_stopEvent) CloseHandle(g_stopEvent);
    if (g_settingsEvent) CloseHandle(g_settingsEvent);
    g_stopEvent = g_settingsEvent = nullptr;
}

void ModSettingsChanged() {
    bool shortcutsWere = g_shortcutsOn;
    ReadSettings();
    if (g_shortcutsOn && !shortcutsWere) Wh_SetIntValue(L"sharedDeclined", 0);
    if (g_settingsEvent) SetEvent(g_settingsEvent);
}

}  // namespace app_icons

namespace steam_icons {


static std::atomic_bool g_trayOn{true};
static std::atomic_bool g_windowsOn{true};
static std::atomic_bool g_shortcutsOn{true};
static bool g_isSteam = false;  // steam.exe owns the tray icon and the shortcuts

static HANDLE g_stopEvent;
static HANDLE g_settingsEvent;
static HANDLE g_worker;
static UINT g_applyMsg;

static void ReadSettings() {
    bool steamOn = Wh_GetIntSetting(L"appIcons.steam") != 0;
    g_trayOn = steamOn && Wh_GetIntSetting(L"appIcons.trayIcon") != 0;
    g_windowsOn = steamOn && Wh_GetIntSetting(L"appIcons.windowIcons") != 0;
    g_shortcutsOn = steamOn && Wh_GetIntSetting(L"appIcons.shortcutIcons") != 0;
}

// ---------------------------------------------------------------- the icon

static std::wstring IconFile() {
    wchar_t folder[MAX_PATH];
    if (FAILED(SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, folder))) return {};
    return std::wstring(folder) + L"\\Mocha Steam\\Steam-Mocha.ico";
}

static bool WriteIcon(const std::wstring& path) {
    static constexpr char data[] =
        "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"
    ;
    DWORD size = 0;
    if (!CryptStringToBinaryA(data, 0, CRYPT_STRING_BASE64, nullptr, &size, nullptr, nullptr)) return false;
    std::vector<BYTE> bytes(size);
    if (!CryptStringToBinaryA(data, 0, CRYPT_STRING_BASE64, bytes.data(), &size, nullptr, nullptr)) return false;
    HANDLE old = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
    if (old != INVALID_HANDLE_VALUE) {
        std::vector<BYTE> have(size + 1);
        DWORD got = 0;
        BOOL ok = ReadFile(old, have.data(), size + 1, &got, nullptr);
        CloseHandle(old);
        if (ok && got == size && !memcmp(have.data(), bytes.data(), size)) return true;
    }
    std::wstring dir = path.substr(0, path.rfind(L'\\'));
    CreateDirectoryW(dir.c_str(), nullptr);
    wchar_t temp[MAX_PATH];
    if (!GetTempFileNameW(dir.c_str(), L"msi", 0, temp)) return false;
    HANDLE file = CreateFileW(temp, GENERIC_WRITE, 0, nullptr, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    DWORD written = 0;
    bool ok = file != INVALID_HANDLE_VALUE && WriteFile(file, bytes.data(), size, &written, nullptr) && written == size;
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    // steam.exe and the web helper start together; whoever loses the race
    // finds the file already in place.
    if (ok) ok = MoveFileExW(temp, path.c_str(), MOVEFILE_REPLACE_EXISTING) ||
                 GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES;
    DeleteFileW(temp);
    return ok;
}

static std::mutex g_iconMutex;
static std::map<int, HICON> g_icons;

static HICON MochaIcon(int size) {
    if (size <= 0) size = 16;
    std::lock_guard<std::mutex> lock(g_iconMutex);
    if (auto it = g_icons.find(size); it != g_icons.end()) return it->second;
    auto path = IconFile();
    if (path.empty() || !WriteIcon(path)) return nullptr;
    auto icon = (HICON)LoadImageW(nullptr, path.c_str(), IMAGE_ICON, size, size, LR_LOADFROMFILE);
    if (icon) g_icons.emplace(size, icon);
    return icon;
}

static bool OwnWindow(HWND hwnd) {
    DWORD pid = 0;
    return hwnd && GetWindowThreadProcessId(hwnd, &pid) && pid == GetCurrentProcessId();
}

// ---------------------------------------------------------------- windows
//
// Each Steam window is subclassed. Its icons are swapped for the Mocha ones,
// and any icon Steam sets later is remembered and swapped too, so turning
// the switch off can hand back exactly what Steam last asked for.

struct WindowIcons {
    HICON big = nullptr;
    HICON small = nullptr;
    bool themed = false;
};

static std::mutex g_windowMutex;
static std::map<HWND, WindowIcons> g_windows;

static HICON WindowIcon(HWND hwnd, bool big) {
    UINT dpi = GetDpiForWindow(hwnd);
    return MochaIcon(GetSystemMetricsForDpi(big ? SM_CXICON : SM_CXSMICON, dpi ? dpi : 96));
}

static void ThemeWindow(HWND hwnd, bool on) {
    WindowIcons state;
    {
        std::lock_guard<std::mutex> lock(g_windowMutex);
        state = g_windows[hwnd];
    }
    if (on == state.themed) return;
    if (on) {
        HICON big = WindowIcon(hwnd, true), small = WindowIcon(hwnd, false);
        if (!big || !small) return;
        state.big = (HICON)DefSubclassProc(hwnd, WM_SETICON, ICON_BIG, (LPARAM)big);
        state.small = (HICON)DefSubclassProc(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)small);
        state.themed = true;
    } else {
        DefSubclassProc(hwnd, WM_SETICON, ICON_BIG, (LPARAM)state.big);
        DefSubclassProc(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)state.small);
        state = {};
    }
    Wh_Log(L"window %p: %s", hwnd, on ? L"Mocha icon" : L"Steam icon");
    std::lock_guard<std::mutex> lock(g_windowMutex);
    g_windows[hwnd] = state;
}

static LRESULT CALLBACK IconSubclassProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, DWORD_PTR) {
    if (message == g_applyMsg && g_applyMsg) {
        ThemeWindow(hwnd, wParam != 0);
        return 1;
    }
    if (message == WM_SETICON && (wParam == ICON_BIG || wParam == ICON_SMALL)) {
        bool themed;
        {
            std::lock_guard<std::mutex> lock(g_windowMutex);
            auto it = g_windows.find(hwnd);
            themed = it != g_windows.end() && it->second.themed;
        }
        if (themed) {
            if (HICON ours = WindowIcon(hwnd, wParam == ICON_BIG)) {
                HICON previous;
                {
                    std::lock_guard<std::mutex> lock(g_windowMutex);
                    auto& state = g_windows[hwnd];
                    HICON& slot = wParam == ICON_BIG ? state.big : state.small;
                    previous = slot;
                    slot = (HICON)lParam;
                }
                DefSubclassProc(hwnd, WM_SETICON, wParam, (LPARAM)ours);
                // Steam may free what it gets back, so it gets its own icon,
                // never ours.
                return (LRESULT)previous;
            }
        }
    }
    if (message == WM_NCDESTROY) {
        std::lock_guard<std::mutex> lock(g_windowMutex);
        g_windows.erase(hwnd);
    }
    return DefSubclassProc(hwnd, message, wParam, lParam);
}

static std::mutex g_attachedMutex;
static std::set<HWND> g_attached;

static bool WantsIcon(HWND hwnd) {
    if (!IsWindow(hwnd) || !OwnWindow(hwnd)) return false;
    if (GetAncestor(hwnd, GA_PARENT) != GetDesktopWindow()) return false;
    LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);
    LONG_PTR exStyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    if (style & WS_CHILD) return false;
    return !(exStyle & WS_EX_TOOLWINDOW) || (exStyle & WS_EX_APPWINDOW);
}

static void Attach(HWND hwnd) {
    {
        std::lock_guard<std::mutex> lock(g_attachedMutex);
        for (auto it = g_attached.begin(); it != g_attached.end();) {
            it = IsWindow(*it) ? std::next(it) : g_attached.erase(it);
        }
        if (g_attached.contains(hwnd)) return;
    }
    if (!WindhawkUtils::SetWindowSubclassFromAnyThread(hwnd, IconSubclassProc, 0)) return;
    {
        std::lock_guard<std::mutex> lock(g_attachedMutex);
        g_attached.insert(hwnd);
    }
    SendMessageTimeoutW(hwnd, g_applyMsg, g_windowsOn ? 1 : 0, 0, SMTO_ABORTIFHUNG, 1000, nullptr);
}

static std::vector<HWND> AttachedWindows() {
    std::lock_guard<std::mutex> lock(g_attachedMutex);
    std::vector<HWND> out;
    for (HWND hwnd : g_attached) {
        if (IsWindow(hwnd)) out.push_back(hwnd);
    }
    return out;
}

// Returns false when a window did not answer, so its icons may still point
// at ours.
static bool ThemeAllWindows(bool on) {
    bool all = true;
    for (HWND hwnd : AttachedWindows()) {
        DWORD_PTR result = 0;
        if (!SendMessageTimeoutW(hwnd, g_applyMsg, on ? 1 : 0, 0, SMTO_ABORTIFHUNG, 2000, &result)) all = false;
    }
    return all;
}

static void CALLBACK ShowEvent(HWINEVENTHOOK, DWORD, HWND hwnd, LONG idObject, LONG idChild, DWORD, DWORD) {
    if (idObject == OBJID_WINDOW && idChild == CHILDID_SELF && WantsIcon(hwnd)) Attach(hwnd);
}

static BOOL CALLBACK AttachExisting(HWND hwnd, LPARAM) {
    if (IsWindowVisible(hwnd) && WantsIcon(hwnd)) Attach(hwnd);
    return TRUE;
}

// ---------------------------------------------------------------- tray

static decltype(&Shell_NotifyIconW) g_notifyIcon;

struct TrayTarget {
    bool known = false;
    HWND hwnd = nullptr;
    UINT id = 0;
    bool byGuid = false;
    GUID guid{};
};

static std::mutex g_trayMutex;
static TrayTarget g_tray;
static HICON g_stockTray;              // copy of the last icon Steam itself set
static std::atomic_int g_trayThemed{-1};  // -1 untouched, 0 Steam's icon, 1 ours

static BOOL CallNotify(DWORD action, PNOTIFYICONDATAW data) {
    return g_notifyIcon ? g_notifyIcon(action, data) : Shell_NotifyIconW(action, data);
}

static int TrayIconSize() {
    HWND taskbar = FindWindowW(L"Shell_TrayWnd", nullptr);
    UINT dpi = taskbar ? GetDpiForWindow(taskbar) : 0;
    return GetSystemMetricsForDpi(SM_CXSMICON, dpi ? dpi : 96);
}

static bool SameTarget(const TrayTarget& t, const NOTIFYICONDATAW* data) {
    if (!t.known) return false;
    if (t.byGuid) return (data->uFlags & NIF_GUID) && IsEqualGUID(t.guid, data->guidItem);
    return t.hwnd == data->hWnd && t.id == data->uID;
}

static BOOL WINAPI NotifyIconHook(DWORD action, PNOTIFYICONDATAW data) {
    constexpr DWORD kMinSize = offsetof(NOTIFYICONDATAW, szTip);
    if (!data || data->cbSize < kMinSize || !OwnWindow(data->hWnd)) return CallNotify(action, data);
    bool hasGuid = data->cbSize >= offsetof(NOTIFYICONDATAW, hBalloonIcon) && (data->uFlags & NIF_GUID);
    if (action == NIM_DELETE) {
        std::lock_guard<std::mutex> lock(g_trayMutex);
        if (SameTarget(g_tray, data)) {
            g_tray = {};
            g_trayThemed = -1;
        }
        return CallNotify(action, data);
    }
    if ((action != NIM_ADD && action != NIM_MODIFY) || !(data->uFlags & NIF_ICON)) return CallNotify(action, data);
    {
        std::lock_guard<std::mutex> lock(g_trayMutex);
        g_tray.known = true;
        g_tray.hwnd = data->hWnd;
        g_tray.id = data->uID;
        g_tray.byGuid = hasGuid;
        if (hasGuid) g_tray.guid = data->guidItem;
        if (g_stockTray) DestroyIcon(g_stockTray);
        g_stockTray = data->hIcon ? CopyIcon(data->hIcon) : nullptr;
    }
    if (g_trayOn) {
        if (HICON ours = MochaIcon(TrayIconSize())) {
            NOTIFYICONDATAW copy{};
            memcpy(&copy, data, std::min<size_t>(data->cbSize, sizeof(copy)));
            copy.hIcon = ours;
            BOOL ok = CallNotify(action, &copy);
            if (ok) g_trayThemed = 1;
            Wh_Log(L"tray: Steam set its icon, swapped for Mocha (%d)", ok);
            return ok;
        }
    }
    BOOL ok = CallNotify(action, data);
    if (ok) g_trayThemed = 0;
    return ok;
}

static void ProbeWindow(HWND hwnd) {
    if (g_tray.known) return;
    for (UINT id = 0; id < 8; ++id) {
        NOTIFYICONDATAW data{};
        data.cbSize = sizeof(data);
        data.hWnd = hwnd;
        data.uID = id;
        // A modify with no flags changes nothing and only says whether
        // this window owns an icon with this number.
        if (CallNotify(NIM_MODIFY, &data)) {
            g_tray.known = true;
            g_tray.hwnd = hwnd;
            g_tray.id = id;
            Wh_Log(L"tray: found Steam's icon on %p, id %u", hwnd, id);
            return;
        }
    }
}

static BOOL CALLBACK ProbeTopLevel(HWND hwnd, LPARAM) {
    if (OwnWindow(hwnd)) ProbeWindow(hwnd);
    return !g_tray.known;
}

// The mod loaded into a Steam that already shows its tray icon: find it.
static void FindTrayIcon() {
    std::lock_guard<std::mutex> lock(g_trayMutex);
    if (g_tray.known) return;
    EnumWindows(ProbeTopLevel, 0);
    HWND hwnd = nullptr;
    while (!g_tray.known && (hwnd = FindWindowExW(HWND_MESSAGE, hwnd, nullptr, nullptr))) {
        if (OwnWindow(hwnd)) ProbeWindow(hwnd);
    }
}

static BOOL CALLBACK FirstIconGroup(HMODULE, LPCWSTR, LPWSTR name, LONG_PTR out) {
    auto* found = reinterpret_cast<std::wstring*>(out);
    *found = IS_INTRESOURCE(name) ? L"#" + std::to_wstring((UINT_PTR)name) : std::wstring(name);
    return FALSE;
}

static HICON SteamExeIcon(int size) {
    std::wstring name;
    HMODULE module = GetModuleHandleW(nullptr);
    EnumResourceNamesW(module, RT_GROUP_ICON, FirstIconGroup, (LONG_PTR)&name);
    return name.empty() ? nullptr : (HICON)LoadImageW(module, name.c_str(), IMAGE_ICON, size, size, 0);
}

static void RefreshTray(bool on) {
    if (on) FindTrayIcon();
    TrayTarget target;
    {
        std::lock_guard<std::mutex> lock(g_trayMutex);
        target = g_tray;
    }
    if (!target.known) return;
    if (on ? g_trayThemed == 1 : g_trayThemed != 1) return;
    NOTIFYICONDATAW data{};
    data.cbSize = sizeof(data);
    data.hWnd = target.hwnd;
    data.uID = target.id;
    data.uFlags = NIF_ICON | (target.byGuid ? NIF_GUID : 0);
    data.guidItem = target.guid;
    HICON stock = nullptr;
    if (on) {
        data.hIcon = MochaIcon(TrayIconSize());
    } else {
        {
            std::lock_guard<std::mutex> lock(g_trayMutex);
            if (g_stockTray) stock = CopyIcon(g_stockTray);
        }
        if (!stock) stock = SteamExeIcon(TrayIconSize());
        data.hIcon = stock;
    }
    BOOL done = data.hIcon && CallNotify(NIM_MODIFY, &data);
    if (done) g_trayThemed = on ? 1 : 0;
    Wh_Log(L"tray: %s icon -> %d", on ? L"Mocha" : L"Steam", done);
    if (stock) DestroyIcon(stock);
}

// ---------------------------------------------------------------- shortcuts
//
// Same method as the Mocha Windhawk icons: the original shortcut is copied
// beside the icon before its icon changes, and that copy is how it goes back.
// Shared shortcuts need admin rights, so their edited copies go in through
// one hidden elevated copy.

struct ShortcutCopy {
    std::wstring from, to;
};

static bool g_shortcutChanged;

// The taskbar and Start keep showing a shortcut's old picture until the shell
// hears that picture changed, so tell it about both Steam's and ours.
static void RefreshShellImages(const std::wstring& icon, HANDLE stop) {
    if (stop ? WaitForSingleObject(stop, 2000) == WAIT_OBJECT_0 : (Sleep(1500), false)) return;
    wchar_t exe[MAX_PATH];
    std::vector<std::wstring> files{icon};
    if (GetModuleFileNameW(nullptr, exe, ARRAYSIZE(exe))) files.push_back(exe);
    for (const auto& path : files) {
        SHFILEINFOW info{};
        if (SHGetFileInfoW(path.c_str(), 0, &info, sizeof(info), SHGFI_SYSICONINDEX) && info.iIcon > 0) {
            SHChangeNotify(SHCNE_UPDATEIMAGE, SHCNF_DWORD, (LPCVOID)(INT_PTR)info.iIcon, nullptr);
        }
    }
    Wh_Log(L"shortcuts: asked the shell to redraw Steam's icons");
}

static void UpdateShortcutIcon(IShellLinkW* link, IPersistFile* file, const std::wstring& path,
                               const std::wstring& icon, const std::wstring& backup, bool enabled,
                               std::vector<ShortcutCopy>& pending) {
    if (GetFileAttributesW(path.c_str()) == INVALID_FILE_ATTRIBUTES) return;
    if (FAILED(file->Load(path.c_str(), STGM_READ))) return;
    wchar_t target[MAX_PATH], image[MAX_PATH], args[1024];
    int index = 0;
    if (FAILED(link->GetPath(target, ARRAYSIZE(target), nullptr, SLGP_RAWPATH)) ||
        FAILED(link->GetIconLocation(image, ARRAYSIZE(image), &index))) return;
    if (FAILED(link->GetArguments(args, ARRAYSIZE(args)))) args[0] = 0;
    // A game shortcut also points at steam.exe; it carries a launch argument.
    if (wcsstr(args, L"-applaunch") || wcsstr(args, L"steam://") || wcsstr(args, L"-rungameid")) return;
    wchar_t expanded[MAX_PATH], installed[MAX_PATH];
    DWORD count = ExpandEnvironmentStringsW(target, expanded, ARRAYSIZE(expanded));
    if (!count || count > ARRAYSIZE(expanded) ||
        !GetModuleFileNameW(nullptr, installed, ARRAYSIZE(installed)) ||
        _wcsicmp(expanded, installed) != 0) return;

    bool themed = _wcsicmp(image, icon.c_str()) == 0;
    if (enabled == themed) return;
    std::wstring next = icon;
    int nextIndex = 0;
    if (enabled) {
        if (!CopyFileW(path.c_str(), backup.c_str(), FALSE)) return;
    } else {
        if (GetFileAttributesW(backup.c_str()) == INVALID_FILE_ATTRIBUTES ||
            FAILED(file->Load(backup.c_str(), STGM_READ)) ||
            FAILED(link->GetIconLocation(image, ARRAYSIZE(image), &nextIndex)) ||
            FAILED(file->Load(path.c_str(), STGM_READ))) return;
        next = image;
    }
    if (FAILED(link->SetIconLocation(next.c_str(), nextIndex))) return;
    if (SUCCEEDED(file->Save(path.c_str(), TRUE))) {
        SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATHW, path.c_str(), nullptr);
        g_shortcutChanged = true;
        Wh_Log(L"shortcut %s: %s", enabled ? L"Mocha" : L"restored", path.c_str());
        if (!enabled) DeleteFileW(backup.c_str());
        return;
    }
    std::wstring staged = backup + L".new.lnk";
    if (SUCCEEDED(file->Save(staged.c_str(), FALSE))) pending.push_back({staged, path});
}

// The admin prompt runs in a hidden helper, so Steam never sits waiting on
// it: the mod waits on the helper and gives up when Steam or the mod stops.
static void CopySharedShortcuts(const std::vector<ShortcutCopy>& pending, bool enabled, HANDLE stop) {
    if (pending.empty()) return;
    // A "no" to the admin prompt is remembered, so Steam does not ask on
    // every start. Turning the shortcut switch back on asks again.
    bool give = !(enabled && Wh_GetIntValue(L"steamSharedDeclined", 0));
    std::wstring dir = pending[0].from.substr(0, pending[0].from.rfind(L'\\'));
    std::wstring batch = dir + L"\\copy-shortcuts.cmd";
    std::string text = "@chcp 65001 >nul\r\n";
    for (const auto& item : pending) {
        std::wstring line = L"@copy /y \"" + item.from + L"\" \"" + item.to + L"\" >nul\r\n";
        int size = WideCharToMultiByte(CP_UTF8, 0, line.c_str(), -1, nullptr, 0, nullptr, nullptr);
        std::string utf8(size > 0 ? size - 1 : 0, '\0');
        if (size > 1) WideCharToMultiByte(CP_UTF8, 0, line.c_str(), -1, utf8.data(), size, nullptr, nullptr);
        text += utf8;
    }
    HANDLE file = give ? CreateFileW(batch.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr)
                       : INVALID_HANDLE_VALUE;
    DWORD written = 0;
    bool ready = file != INVALID_HANDLE_VALUE && WriteFile(file, text.data(), (DWORD)text.size(), &written, nullptr) &&
                 written == text.size();
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);

    wchar_t system[MAX_PATH];
    if (ready && GetSystemDirectoryW(system, ARRAYSIZE(system))) {
        std::wstring quoted;
        for (wchar_t c : batch) quoted += c == L'\'' ? std::wstring(L"''") : std::wstring(1, c);
        std::wstring script = L"try { Start-Process -FilePath $env:ComSpec -ArgumentList '/d /c \"" + quoted +
                              L"\"' -Verb RunAs -WindowStyle Hidden -Wait -ErrorAction Stop; exit 0 } catch { exit 5 }";
        DWORD chars = 0;
        auto bytes = reinterpret_cast<const BYTE*>(script.data());
        DWORD length = (DWORD)(script.size() * sizeof(wchar_t));
        CryptBinaryToStringW(bytes, length, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, nullptr, &chars);
        std::wstring encoded(chars, L'\0');
        if (chars && CryptBinaryToStringW(bytes, length, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, encoded.data(), &chars)) {
            encoded.resize(chars);
            std::wstring command = L"\"" + std::wstring(system) +
                                   L"\\WindowsPowerShell\\v1.0\\powershell.exe\" -NoProfile -NonInteractive "
                                   L"-WindowStyle Hidden -EncodedCommand " + encoded;
            STARTUPINFOW startup{sizeof(startup)};
            startup.dwFlags = STARTF_USESHOWWINDOW;
            startup.wShowWindow = SW_HIDE;
            PROCESS_INFORMATION process{};
            if (CreateProcessW(nullptr, command.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr,
                               &startup, &process)) {
                CloseHandle(process.hThread);
                HANDLE waits[] = {process.hProcess, stop};
                DWORD wait = WaitForMultipleObjects(stop ? 2 : 1, waits, FALSE, stop ? 120000 : 30000);
                DWORD code = STILL_ACTIVE;
                if (wait == WAIT_OBJECT_0) GetExitCodeProcess(process.hProcess, &code);
                CloseHandle(process.hProcess);
                if (code == 0) {
                    for (const auto& item : pending) {
                        SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATHW, item.to.c_str(), nullptr);
                        g_shortcutChanged = true;
                        Wh_Log(L"shortcut %s (shared): %s", enabled ? L"Mocha" : L"restored", item.to.c_str());
                    }
                } else if (code == 5) {
                    Wh_Log(L"shared shortcuts: admin prompt declined");
                    if (enabled) Wh_SetIntValue(L"steamSharedDeclined", 1);
                }
                // Still waiting on the prompt: leave the helper its files.
                if (code == STILL_ACTIVE) return;
            }
        }
    }
    DeleteFileW(batch.c_str());
    for (const auto& item : pending) DeleteFileW(item.from.c_str());
}

static void UpdateShortcutIcons(bool enabled, HANDLE stop) {
    auto icon = IconFile();
    if (icon.empty() || (enabled && !WriteIcon(icon))) return;
    std::wstring base = icon.substr(0, icon.rfind(L'\\')) + L"\\Steam";
    HRESULT init = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(init)) return;
    IShellLinkW* link = nullptr;
    if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLinkW,
                                   reinterpret_cast<void**>(&link)))) {
        IPersistFile* file = nullptr;
        if (SUCCEEDED(link->QueryInterface(IID_IPersistFile, reinterpret_cast<void**>(&file)))) {
            static constexpr struct {
                int folder;
                PCWSTR suffix;
                PCWSTR backupSuffix;
            } shortcuts[] = {
                {CSIDL_COMMON_PROGRAMS, L"\\Steam\\Steam.lnk", L".common-programs.lnk"},
                {CSIDL_PROGRAMS, L"\\Steam\\Steam.lnk", L".programs.lnk"},
                {CSIDL_COMMON_PROGRAMS, L"\\Steam.lnk", L".common-programs-top.lnk"},
                {CSIDL_PROGRAMS, L"\\Steam.lnk", L".programs-top.lnk"},
                {CSIDL_COMMON_DESKTOPDIRECTORY, L"\\Steam.lnk", L".common-desktop.lnk"},
                {CSIDL_DESKTOPDIRECTORY, L"\\Steam.lnk", L".desktop.lnk"},
                {CSIDL_APPDATA, L"\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar\\Steam.lnk", L".taskbar.lnk"},
            };
            std::vector<ShortcutCopy> pending;
            g_shortcutChanged = false;
            for (const auto& shortcut : shortcuts) {
                wchar_t folder[MAX_PATH];
                if (SUCCEEDED(SHGetFolderPathW(nullptr, shortcut.folder, nullptr, SHGFP_TYPE_CURRENT, folder))) {
                    UpdateShortcutIcon(link, file, std::wstring(folder) + shortcut.suffix, icon,
                                       base + shortcut.backupSuffix, enabled, pending);
                }
            }
            file->Release();
            CopySharedShortcuts(pending, enabled, stop);
            if (g_shortcutChanged) RefreshShellImages(icon, stop);
        }
        link->Release();
    }
    CoUninitialize();
}

// The mod was turned off or removed, not just reloaded or Steam closing.
static bool ModTurnedOff() {
    if (!Wh_GetIntSetting(L"appIcons.enabled")) return true;  // this part was switched off in the suite
    std::wstring key = L"SOFTWARE\\Windhawk\\Engine\\Mods\\";
    key += WH_MOD_ID;
    HKEY handle;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, key.c_str(), 0, KEY_READ, &handle) != ERROR_SUCCESS) {
        HKEY mods;
        if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods", 0, KEY_READ, &mods) != ERROR_SUCCESS) {
            return false;  // settings live elsewhere (portable Windhawk): never guess
        }
        RegCloseKey(mods);
        return true;
    }
    DWORD disabled = 0, size = sizeof(disabled);
    bool off = RegQueryValueExW(handle, L"Disabled", nullptr, nullptr, (BYTE*)&disabled, &size) == ERROR_SUCCESS &&
               disabled;
    RegCloseKey(handle);
    return off;
}

// ---------------------------------------------------------------- worker

static void ApplyAll() {
    ThemeAllWindows(g_windowsOn);
    if (g_isSteam) {
        RefreshTray(g_trayOn);
        UpdateShortcutIcons(g_shortcutsOn, g_stopEvent);
    }
}

static DWORD WINAPI Worker(LPVOID) {
    HWINEVENTHOOK hook = SetWinEventHook(EVENT_OBJECT_SHOW, EVENT_OBJECT_SHOW, nullptr, ShowEvent,
                                         GetCurrentProcessId(), 0, WINEVENT_OUTOFCONTEXT);
    EnumWindows(AttachExisting, 0);
    if (g_isSteam) {
        RefreshTray(g_trayOn);
        UpdateShortcutIcons(g_shortcutsOn, g_stopEvent);
    }
    // Windows saves a taskbar pin again now and then (after an Explorer
    // restart, for one) and drops our icon, so steam.exe watches the pins.
    HANDLE pins = INVALID_HANDLE_VALUE;
    wchar_t appData[MAX_PATH];
    if (g_isSteam && SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, appData))) {
        std::wstring dir = std::wstring(appData) + L"\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar";
        pins = FindFirstChangeNotificationW(dir.c_str(), FALSE,
                                            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE);
    }
    HANDLE events[] = {g_stopEvent, g_settingsEvent, pins};
    DWORD count = pins != INVALID_HANDLE_VALUE ? 3 : 2;
    for (;;) {
        DWORD wait = MsgWaitForMultipleObjects(count, events, FALSE, INFINITE, QS_ALLINPUT);
        if (wait == WAIT_OBJECT_0) break;
        if (wait == WAIT_OBJECT_0 + 1) {
            ApplyAll();
            continue;
        }
        if (count == 3 && wait == WAIT_OBJECT_0 + 2) {
            // Let the writer finish, and fold a burst of changes into one pass.
            if (WaitForSingleObject(g_stopEvent, 3000) == WAIT_OBJECT_0) break;
            FindNextChangeNotification(pins);
            if (g_shortcutsOn) UpdateShortcutIcons(true, g_stopEvent);
            continue;
        }
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) DispatchMessageW(&msg);
    }
    if (pins != INVALID_HANDLE_VALUE) FindCloseChangeNotification(pins);
    if (hook) UnhookWinEvent(hook);
    return 0;
}

// ---------------------------------------------------------------- Windhawk

BOOL ModInit() {
    wchar_t image[MAX_PATH];
    if (!GetModuleFileNameW(nullptr, image, ARRAYSIZE(image))) return FALSE;
    PCWSTR name = wcsrchr(image, L'\\');
    name = name ? name + 1 : image;
    g_isSteam = _wcsicmp(name, L"steam.exe") == 0;
    // The web helper starts many copies of itself; only the main one, with
    // no --type, owns the Steam windows.
    if (!g_isSteam && wcsstr(GetCommandLineW(), L"--type=")) return FALSE;

    ReadSettings();
    g_applyMsg = RegisterWindowMessageW(L"MochaSteamIcons.Apply");
    if (g_isSteam) Wh_SetFunctionHook((void*)Shell_NotifyIconW, (void*)NotifyIconHook, (void**)&g_notifyIcon);

    g_stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_settingsEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (g_stopEvent && g_settingsEvent) g_worker = CreateThread(nullptr, 0, Worker, nullptr, 0, nullptr);
    return TRUE;
}

void ModUninit() {
    if (g_worker) {
        SetEvent(g_stopEvent);
        WaitForSingleObject(g_worker, 30000);
        CloseHandle(g_worker);
        g_worker = nullptr;
    }
    bool restored = ThemeAllWindows(false);
    WindhawkUtils::RemoveAllWindowSubclasses();
    if (g_isSteam) {
        RefreshTray(false);
        if (ModTurnedOff()) UpdateShortcutIcons(false, nullptr);
    }
    {
        std::lock_guard<std::mutex> lock(g_trayMutex);
        if (g_stockTray) DestroyIcon(g_stockTray);
        g_stockTray = nullptr;
    }
    // A window that did not answer may still show our icon; keep the icons
    // alive rather than leave it pointing at freed ones.
    if (restored && g_trayThemed != 1) {
        std::lock_guard<std::mutex> lock(g_iconMutex);
        for (const auto& [size, icon] : g_icons) DestroyIcon(icon);
        g_icons.clear();
    }
    if (g_stopEvent) CloseHandle(g_stopEvent);
    if (g_settingsEvent) CloseHandle(g_settingsEvent);
    g_stopEvent = g_settingsEvent = nullptr;
}

void ModSettingsChanged() {
    bool shortcutsWere = g_shortcutsOn;
    ReadSettings();
    if (g_shortcutsOn && !shortcutsWere) Wh_SetIntValue(L"steamSharedDeclined", 0);
    if (g_settingsEvent) SetEvent(g_settingsEvent);
}

}  // namespace steam_icons

// ---------------------------------------------------------------- one mod, two engines
// Steam has its own engine (the web helper owns its windows, the tray icon is redrawn often);
// every other app uses the app engine. Each starts only in its own programs.

static bool g_steamSide = false;

BOOL ModInit() {
    wchar_t image[MAX_PATH];
    if (!GetModuleFileNameW(nullptr, image, ARRAYSIZE(image))) return FALSE;
    PCWSTR name = wcsrchr(image, L'\\');
    name = name ? name + 1 : image;
    g_steamSide = _wcsicmp(name, L"steam.exe") == 0 || _wcsicmp(name, L"steamwebhelper.exe") == 0;
    return g_steamSide ? steam_icons::ModInit() : app_icons::ModInit();
}

void ModUninit() {
    if (g_steamSide) steam_icons::ModUninit();
    else app_icons::ModUninit();
}

void ModSettingsChanged() {
    if (g_steamSide) steam_icons::ModSettingsChanged();
    else app_icons::ModSettingsChanged();
}
}  // namespace mod_appIcons
#endif  // _WIN64

// ===================================================================
// Part: Store app icons (storeAppIcons)
// UWP Assets Redirect Plus 1.2 by DavidHiFi and ferrys. GPL-3.0 license.
// Based on UWP Assets Redirect by ferrys: https://github.com/atferrys/uwp-assets-redirect
// ===================================================================
namespace mod_storeAppIcons {
std::unordered_map<std::wstring, std::wstring> g_redirections;
BOOL g_grant_permissions;

inline WCHAR ToLowerAscii(WCHAR c) {
    if (c >= L'A' && c <= L'Z') {
        return c + (L'a' - L'A');
    }
    return c;
}

template <typename T>
bool match(const T* pattern, size_t pattern_length, const T* str, size_t string_length, size_t& after_match_index) {
    size_t pattern_index = 0;
    size_t string_index = 0;

    // Flag used to only check first wildcard
    bool wildcard_matched = false;

    while (pattern_index < pattern_length && string_index < string_length) {
        if (!wildcard_matched && pattern[pattern_index] == '*') {
            ++pattern_index; // Skip the wildcard symbol
            wildcard_matched = true;

            // The rest of the pattern after the wildcard
            size_t rest_start = pattern_index;

            // Find the literal string after the wildcard (until the end)
            size_t literal_len = pattern_length - rest_start;

            // If the wildcard is the last thing present in the pattern
            if (literal_len == 0) {
                // Move forward until the first backslash or end of string
                while (string_index < string_length && str[string_index] != '\\') {
                    ++string_index;
                }

                after_match_index = string_index;
                return true;
            }

            // Try to match this literal in the string
            size_t match_pos = string_index;
            bool found = false;
            while (match_pos + literal_len <= string_length) {

                bool mismatch = false;
                for (size_t k = 0; k < literal_len; ++k) {
                    if (ToLowerAscii(str[match_pos + k]) != ToLowerAscii(pattern[rest_start + k])) {
                        mismatch = true;
                        break;
                    }
                }

                if (!mismatch) {
                    found = true;
                    break;
                }

                // Stop wildcard matching at '\'
                if (str[match_pos] == '\\') break;

                ++match_pos;
            }

            if (!found) return false;

            // Move past the matched literal
            string_index = match_pos + literal_len;
            pattern_index = rest_start + literal_len;

            // Make after_match_index point to the end of the matched pattern
            after_match_index = string_index;
        } else {
            if (ToLowerAscii(pattern[pattern_index]) != ToLowerAscii(str[string_index])) return false;
            ++pattern_index;
            ++string_index;
        }
    }

    // Ensure full pattern was matched
    return pattern_index == pattern_length;
}

using NtCreateFile_t = decltype(&NtCreateFile);
NtCreateFile_t NtCreateFile_Original;

NTSTATUS NTAPI NtCreateFile_Hook(
    PHANDLE FileHandle,
    ACCESS_MASK DesiredAccess,
    POBJECT_ATTRIBUTES ObjectAttributes,
    PIO_STATUS_BLOCK IoStatusBlock,
    PLARGE_INTEGER AllocationSize,
    ULONG FileAttributes,
    ULONG ShareAccess,
    ULONG CreateDisposition,
    ULONG CreateOptions,
    PVOID EaBuffer,
    ULONG EaLength
) {

    std::wstring originalPath;

    if(ObjectAttributes && ObjectAttributes->ObjectName) {
        UNICODE_STRING* ObjectName = ObjectAttributes->ObjectName;
        originalPath.assign(ObjectName->Buffer, ObjectName->Length / sizeof(WCHAR));
    }

    // Check if we should redirect
    if(!originalPath.empty()) {

        std::wstring redirectPath;

        const wchar_t* path = originalPath.c_str();
        size_t pathLength = originalPath.length();

        for(const auto& pair : g_redirections) {

            const wchar_t* pattern = pair.first.c_str();
            size_t patternLength = pair.first.length();

            // If there are no wildcards in pattern, simply
            // use the end of the pattern as the match_end_index
            size_t match_end_index = patternLength;

            if(match(pattern, patternLength, path, pathLength, match_end_index)) {
                redirectPath = pair.second + originalPath.substr(match_end_index);
                break;
            }

        }

        if(!redirectPath.empty()) {

            Wh_Log(L"[Redirect Attempt] %s -> %s", originalPath.c_str(), redirectPath.c_str());

            alignas(POBJECT_ATTRIBUTES) BYTE buffer[256];
            memcpy(buffer, ObjectAttributes, ObjectAttributes->Length);
            auto* RedirectedObjectAttributes = reinterpret_cast<POBJECT_ATTRIBUTES>(buffer);

            UNICODE_STRING ObjectName = {
                .Length = (USHORT) (redirectPath.length() * sizeof(WCHAR)),
                .MaximumLength = ObjectName.Length,
                .Buffer = (PWSTR) redirectPath.c_str()
            };

            RedirectedObjectAttributes->ObjectName = &ObjectName;

            NTSTATUS result = NtCreateFile_Original(
                FileHandle,
                DesiredAccess,
                RedirectedObjectAttributes,
                IoStatusBlock,
                AllocationSize,
                FileAttributes,
                ShareAccess,
                CreateDisposition,
                CreateOptions,
                EaBuffer,
                EaLength
            );

            if(NT_SUCCESS(result)) {
                Wh_Log(L"[Redirect Success] Redirected to: %s", redirectPath.c_str());
                return result;
            }

            Wh_Log(L"[Redirect Fail] Failed with code 0x%08X. Rolling back to original: %s", result, originalPath.c_str());

        }

    }

    return NtCreateFile_Original(
        FileHandle,
        DesiredAccess,
        ObjectAttributes,
        IoStatusBlock,
        AllocationSize,
        FileAttributes,
        ShareAccess,
        CreateDisposition,
        CreateOptions,
        EaBuffer,
        EaLength
    );
}

// Check if mod is hooked to the explorer process that owns the taskbar.
// Useful for running specific code once. Taken from:
// https://github.com/ramensoftware/windhawk-mods/blob/43fe260f5738d61ba09018c7de03863defbf40a0/mods/icon-resource-redirect.wh.cpp#L2120-L2122

bool IsExplorerProcess() {
    WCHAR path[MAX_PATH];
    if (!GetWindowsDirectory(path, ARRAYSIZE(path))) {
        Wh_Log(L"GetWindowsDirectory failed");
        return false;
    }

    wcscat_s(path, MAX_PATH, L"\\explorer.exe");

    return GetModuleHandle(path) == GetModuleHandle(nullptr);
}

HWND FindCurrentProcessTaskbarWnd() {
    HWND hTaskbarWnd = nullptr;

    EnumWindows(
        [](HWND hWnd, LPARAM lParam) WINAPI -> BOOL {
            DWORD dwProcessId;
            WCHAR className[32];
            if (GetWindowThreadProcessId(hWnd, &dwProcessId) &&
                dwProcessId == GetCurrentProcessId() &&
                GetClassName(hWnd, className, ARRAYSIZE(className)) &&
                _wcsicmp(className, L"Shell_TrayWnd") == 0) {
                *reinterpret_cast<HWND*>(lParam) = hWnd;
                return FALSE;
            }
            return TRUE;
        },
        reinterpret_cast<LPARAM>(&hTaskbarWnd));

    return hTaskbarWnd;
}

bool DoesCurrentProcessOwnTaskbar() {
    return IsExplorerProcess() && FindCurrentProcessTaskbarWnd();
}


// Plus: File Explorer is never closed. Only the Start menu host is ended (Windows
// starts it again on its own) and its cached tile icons are removed.
constexpr WCHAR g_clear_cache_command[] =
    LR"(cmd /d /c "taskkill /f /im StartMenuExperienceHost.exe >nul 2>&1)"
    LR"(& ping -n 2 127.0.0.1 >nul)"
    LR"(& rmdir /s /q "%LocalAppData%\Packages\Microsoft.Windows.StartMenuExperienceHost_cw5n1h2txyewy\TempState" >nul 2>&1")";

const std::wstring g_should_refresh_icons_key = L"should_refresh_icons";

void MarkShouldRefreshIcons() {
    if(DoesCurrentProcessOwnTaskbar()) {
        Wh_SetIntValue(g_should_refresh_icons_key.c_str(), TRUE);
    }
}

void RefreshIcons(bool check_should_refresh = false) {

    // Only run this once
    if (!DoesCurrentProcessOwnTaskbar()) {
        return;
    }

    if (check_should_refresh) {
        BOOL should_refresh = Wh_GetIntValue(g_should_refresh_icons_key.c_str(), FALSE);
        Wh_DeleteValue(g_should_refresh_icons_key.c_str());
        if (!should_refresh || g_redirections.empty()) {
            return;
        }
    }

    WCHAR commandLine[ARRAYSIZE(g_clear_cache_command)];
    memcpy(commandLine, g_clear_cache_command, sizeof(g_clear_cache_command));
    STARTUPINFO si = {
        .cb = sizeof(si),
    };
    PROCESS_INFORMATION pi{};
    if (CreateProcess(nullptr, commandLine, nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi)) {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }

    // Let other processes some time to init/uninit.
    Sleep(500);

    // Invalidate icon cache.
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);

    Wh_Log(L"Icon cache refreshed.");

}

// SID for "ALL APPLICATION PACKAGES"
constexpr LPCWSTR g_permission_sid = L"S-1-15-2-1";

// SID for "ALL RESTRICTED APPLICATION PACKAGES"
constexpr LPCWSTR g_permission_restricted_sid = L"S-1-15-2-2";

constexpr DWORD g_permission_access_mask = GENERIC_READ | GENERIC_EXECUTE;

void TogglePermissions(std::unordered_map<std::wstring, std::wstring>& redirections, bool toggle) {

    const auto apply_permission = [](const std::wstring path, PSID sid) -> BOOL {

        PACL old_permissions = nullptr;
        PSECURITY_DESCRIPTOR security_descriptor = nullptr;

        DWORD result = GetNamedSecurityInfoW(
            path.c_str(),
            SE_FILE_OBJECT,
            DACL_SECURITY_INFORMATION,
            nullptr,
            nullptr,
            &old_permissions,
            nullptr,
            &security_descriptor
        );

        if (result != ERROR_SUCCESS) {
            return false;
        }

        EXPLICIT_ACCESSW rule = {
            .grfAccessPermissions = g_permission_access_mask,
            .grfAccessMode = GRANT_ACCESS,
            .grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT,
            .Trustee = {
                .TrusteeForm = TRUSTEE_IS_SID,
                .TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP,
                .ptstrName = (LPWSTR) sid
            }
        };

        PACL new_permissions = nullptr;

        result = SetEntriesInAclW(
            1,
            &rule,
            old_permissions,
            &new_permissions
        );

        if (result != ERROR_SUCCESS) {
            if (security_descriptor) {
                LocalFree(security_descriptor);
            }
            return false;
        }

        result = SetNamedSecurityInfoW(
            (LPWSTR) path.c_str(),
            SE_FILE_OBJECT,
            DACL_SECURITY_INFORMATION,
            nullptr,
            nullptr,
            new_permissions,
            nullptr
        );

        if (security_descriptor) {
            LocalFree(security_descriptor);
        }

        if (new_permissions) {
            LocalFree(new_permissions);
        }

        return result == ERROR_SUCCESS;

    };

    const auto remove_permission = [](const std::wstring path, PSID sid) -> BOOL {

        PACL old_permissions = nullptr;
        PSECURITY_DESCRIPTOR security_descriptor = nullptr;

        DWORD result = GetNamedSecurityInfoW(
            path.c_str(),
            SE_FILE_OBJECT,
            DACL_SECURITY_INFORMATION,
            nullptr,
            nullptr,
            &old_permissions,
            nullptr,
            &security_descriptor
        );

        if (result != ERROR_SUCCESS || !old_permissions) {
            return false;
        }

        std::vector<EXPLICIT_ACCESSW> keep_rules;

        for (DWORD i = 0; i < old_permissions->AceCount; i++) {

            LPVOID ace = nullptr;

            if (!GetAce(old_permissions, i, &ace)) {
                continue;
            }

            ACE_HEADER* header = (ACE_HEADER*) ace;

            if (header->AceType != ACCESS_ALLOWED_ACE_TYPE) {
                continue;
            }

            ACCESS_ALLOWED_ACE* allowed = (ACCESS_ALLOWED_ACE*) ace;
            PSID ace_sid = &allowed->SidStart;

            // Removes the previously added permission
            if (EqualSid(ace_sid, sid)) {
                continue;
            }

            EXPLICIT_ACCESSW rule = {
                .grfAccessPermissions = allowed->Mask,
                .grfAccessMode = GRANT_ACCESS,
                .grfInheritance = header->AceFlags,
                .Trustee = {
                    .TrusteeForm = TRUSTEE_IS_SID,
                    .TrusteeType = TRUSTEE_IS_UNKNOWN,
                    .ptstrName = (LPWSTR) ace_sid
                }
            };

            keep_rules.push_back(rule);

        }

        PACL new_permissions = nullptr;

        if (!keep_rules.empty()) {
            result = SetEntriesInAclW(
                (ULONG )keep_rules.size(),
                keep_rules.data(),
                nullptr,
                &new_permissions
            );
            if (result != ERROR_SUCCESS) {
                if (security_descriptor) {
                    LocalFree(security_descriptor);
                }
                return false;
            }
        }

        result = SetNamedSecurityInfoW(
            (LPWSTR) path.c_str(),
            SE_FILE_OBJECT,
            DACL_SECURITY_INFORMATION,
            nullptr,
            nullptr,
            new_permissions,
            nullptr
        );

        if (security_descriptor) {
            LocalFree(security_descriptor);
        }

        if (new_permissions) {
            LocalFree(new_permissions);
        }

        return result == ERROR_SUCCESS;

    };

    PSID sid, restricted_sid;

    if (!ConvertStringSidToSid(g_permission_sid, &sid)) {
        sid = nullptr;
    }

    if (!ConvertStringSidToSid(g_permission_restricted_sid, &restricted_sid)) {
        restricted_sid = nullptr;
    }

    for(const auto& [_, path] : redirections) {
        if(toggle) {
            if(!apply_permission(path, sid) || !apply_permission(path, restricted_sid)) {
                Wh_Log(L"Failed to add special permissions to redirected assets path: %s", path.c_str());
            }
        } else {
            if(!remove_permission(path, sid) || !remove_permission(path, restricted_sid)) {
                Wh_Log(L"Failed to remove special permissions from redirected assets path: %s", path.c_str());
            }
        }
    }

    if(toggle) {
        Wh_Log(L"Added special permissions to redirected assets.");
    } else {
        Wh_Log(L"Removed special permissions from redirected assets.");
    }

    if(sid) {
       LocalFree(sid);
    }

    if(restricted_sid) {
        LocalFree(restricted_sid);
    }

}

const std::wstring g_redirections_cache_id_key = L"redirections_cache_id";
const std::wstring g_redirections_cache_size_key = L"redirections_cache_size";
const std::wstring g_redirections_cache_key = L"redirections_cache";

int g_redirections_cache_id = 0;

const std::wstring g_default_assets_folder = L"Assets";
const int g_max_read_tries = 20;

void write_redirections_cache(std::unordered_map<std::wstring, std::wstring>& redirections) {

    std::vector<uint8_t> buffer;

    auto write = [&](const void* data, size_t size) {
        size_t oldSize = buffer.size();
        buffer.resize(oldSize + size);
        memcpy(buffer.data() + oldSize, data, size);
    };

    // number of entries
    uint32_t count = (uint32_t) redirections.size();
    write(&count, sizeof(count));

    for (const auto& [key, value] : redirections) {
        uint32_t keyLen = (uint32_t) key.size();
        write(&keyLen, sizeof(keyLen));
        write(key.data(), keyLen * sizeof(wchar_t));

        uint32_t valueLen = (uint32_t) value.size();
        write(&valueLen, sizeof(valueLen));
        write(value.data(), valueLen * sizeof(wchar_t));
    }

    Wh_SetBinaryValue(g_redirections_cache_key.c_str(), buffer.data(), buffer.size());
    Wh_SetIntValue(g_redirections_cache_size_key.c_str(), buffer.size());

    Wh_SetIntValue(g_redirections_cache_id_key.c_str(), ++g_redirections_cache_id);

}

bool read_redirections_cache(std::unordered_map<std::wstring, std::wstring>& redirections) {

    int redirections_cache_id = Wh_GetIntValue(g_redirections_cache_id_key.c_str(), 0);

    if(redirections_cache_id <= g_redirections_cache_id) {
        return false;
    }

    g_redirections_cache_id = redirections_cache_id;

    std::vector<uint8_t> buffer;

    int buffer_size = Wh_GetIntValue(g_redirections_cache_size_key.c_str(), -1);

    if(buffer_size == -1) {
        return false;
    }

    buffer.resize(buffer_size);

    if(Wh_GetBinaryValue(g_redirections_cache_key.c_str(), buffer.data(), buffer.size()) == 0) {
        return false;
    }

    const uint8_t* ptr = buffer.data();

    auto read = [&](void* out, size_t size) {
        memcpy(out, ptr, size);
        ptr += size;
    };

    uint32_t count;
    read(&count, sizeof(count));

    for (uint32_t i = 0; i < count; i++) {
        uint32_t keyLen;
        read(&keyLen, sizeof(keyLen));

        std::wstring key(keyLen, L'\0');
        read(key.data(), keyLen * sizeof(wchar_t));

        uint32_t valueLen;
        read(&valueLen, sizeof(valueLen));

        std::wstring value(valueLen, L'\0');
        read(value.data(), valueLen * sizeof(wchar_t));

        redirections.emplace(std::move(key), std::move(value));
    }

    return true;

}

void ClearRedirectionsCache(bool check_main = true) {
    if(!check_main || DoesCurrentProcessOwnTaskbar()) {
        Wh_DeleteValue(g_redirections_cache_size_key.c_str());
        Wh_DeleteValue(g_redirections_cache_key.c_str());
        Wh_DeleteValue(g_redirections_cache_id_key.c_str());
    }
}

inline constexpr auto g_custom_redirections_blacklist = std::to_array<std::wstring_view>({
    LR"(?:\)",

    LR"(C:\Windows)",
    LR"(C:\Windows\System32)",
    LR"(C:\Windows\SysWOW64)",
    LR"(C:\Windows\WinSxS)",
    LR"(C:\Windows\servicing)",
    LR"(C:\Windows\Boot)",
    LR"(C:\Windows\CSC)",
    LR"(C:\Windows\SystemResources)",
    LR"(C:\Windows\System32\Config)",
    LR"(C:\Windows\ServiceProfiles)",

    LR"(C:\ProgramData\Microsoft\Crypto)",
    LR"(C:\ProgramData\Microsoft\Windows\SystemData)",

    LR"(?:\Program Files)",
    LR"(?:\Program Files (x86))",

    LR"(?:\Users)",
    LR"(?:\Users\*\AppData)",
    LR"(?:\Users\*\AppData\Local)",
    LR"(?:\Users\*\AppData\Roaming)",
    LR"(?:\Users\*\AppData\LocalLow)",

    LR"(C:\Program Files\WindowsApps)",
    LR"(C:\Windows\SystemApps)"
});

HANDLE g_downloading_theme_prompt_thread;
std::atomic<HWND> g_downloading_theme_prompt;

constexpr WCHAR g_downloading_theme_prompt_title[] = L"UWP Assets Redirect Plus - Windhawk";
constexpr WCHAR g_downloading_theme_prompt_header[] = L"Downloading Icon theme...";
constexpr WCHAR g_downloading_theme_prompt_body[] = L"UWP Assets Redirect Plus is downloading \"{}\", please wait...";

std::atomic<HWND> g_failed_to_download_theme_prompt;

constexpr WCHAR g_failed_to_download_theme_prompt_title[] = L"UWP Assets Redirect Plus - Windhawk";
constexpr WCHAR g_failed_to_download_theme_prompt_header[] = L"Failed to download Icon theme";

constexpr auto g_normalize_path_base_path = L"C:\\Windows\\System32\\";

void LoadRedirections(std::unordered_map<std::wstring, std::wstring>& redirections) {

    auto normalize_path = [](std::wstring path, std::wstring base_path = g_normalize_path_base_path) -> std::wstring {

        // ### Expand environment strings like %ProgramFiles%

        DWORD path_size = ExpandEnvironmentStringsW(path.c_str(), nullptr, 0);

        if (path_size == 0) {
            return L"";
        }

        std::wstring expanded_path(path_size, L'\0');
        ExpandEnvironmentStringsW(path.c_str(), &expanded_path[0], path_size);

        // Remove trailing null character
        if (!expanded_path.empty() && expanded_path.back() == L'\0') {
            expanded_path.pop_back();
        }

        // ### Make path absolute if relative path like ".\Redirection" is given

        std::filesystem::path relative_path(expanded_path);

        if (relative_path.is_absolute()) {
            return std::filesystem::weakly_canonical(relative_path).wstring();
        }

        std::filesystem::path relative_prefixed_path = std::filesystem::path(base_path) / relative_path;
        std::wstring absolute_path = std::filesystem::weakly_canonical(relative_prefixed_path).wstring();

        // ### Remove trailing slashes

        while (!absolute_path.empty() && absolute_path.back() == L'\\') {

            size_t path_size = absolute_path.size();

            // Stop if it's a drive root like "C:\"
            if (path_size == 3 && absolute_path[path_size - 2] == L':' && absolute_path[path_size - 1] == L'\\') {
                break;
            }

            absolute_path.pop_back();

        }

        return absolute_path;

    };

    auto add_bundle_redirection = [&redirections, normalize_path](std::wstring bundles_root, std::wstring bundle, std::wstring redirect, std::filesystem::path theme_folder = g_normalize_path_base_path) {

        const auto deduct_bundle = [](std::wstring bundles_root, std::wstring bundle, std::wstring& bundle_id, std::wstring& assets_folder, std::filesystem::path& assets_folder_path) {

            const auto get_assets_folder = [](const std::wstring& appx_manifest) -> std::wstring {

                std::wifstream file(appx_manifest.c_str());

                if (!file.is_open() || file.fail()) {
                    Wh_Log(L"Failed to open manifest: %s", appx_manifest.c_str());
                    return L"";
                }

                std::wstringstream buffer;
                buffer << file.rdbuf();

                std::wstring xml = buffer.str();

                const std::wstring openTag = L"<Logo>";
                const std::wstring closeTag = L"</Logo>";

                size_t start = xml.find(openTag);

                if (start == std::wstring::npos) {
                    Wh_Log(L"Failed to find opening <Logo> tag: %s", appx_manifest.c_str());
                    return L"";
                }

                start += openTag.length();
                size_t end = xml.find(closeTag, start);

                if (end == std::wstring::npos) {
                    Wh_Log(L"Failed to find closing <Logo> tag: %s", appx_manifest.c_str());
                    return L"";
                }

                std::wstring logo_content = xml.substr(start, end - start);
                size_t backslash_position = logo_content.find_last_of('\\');

                // If assets are in root directory
                if (backslash_position == std::wstring::npos) {
                    Wh_Log(L"Failed to find external assets folder, assets are in the root directory: %s", appx_manifest.c_str());
                    return L"";
                }

                return logo_content.substr(0, backslash_position);

            };

            const auto find_bundle_folder = [](const std::wstring& bundles_root, const std::wstring& app_bundle) -> std::wstring {

                std::error_code error_code;

                for (const auto& entry : std::filesystem::directory_iterator(bundles_root, error_code)) {

                    if (!entry.is_directory()) {
                        continue;
                    }

                    std::wstring path = entry.path().wstring();

                    size_t last_backslash_index = path.find_last_of('\\');
                    size_t version_index = path.find_first_of('_', last_backslash_index);

                    if (last_backslash_index == std::string::npos || version_index == std::string::npos) {
                        continue;
                    }

                    if (path.substr(last_backslash_index + 1, version_index - last_backslash_index - 1) != app_bundle) {
                        continue;
                    }

                    if (path.find(L"neutral", version_index) != std::string::npos) {
                        continue;
                    }

                    if (!std::filesystem::exists(std::filesystem::path(path) / "AppxManifest.xml", error_code)) {
                        continue;
                    }

                    return path;

                }

                return L"";
            };

            const auto trim = [](std::wstring string) -> std::wstring {

                const auto should_trim = [](wchar_t character) {
                    return std::iswspace(character) || character == L'\\';
                };

                auto start = std::find_if_not(string.begin(), string.end(), should_trim);
                auto end = std::find_if_not(string.rbegin(), string.rend(), should_trim).base();

                if (start >= end) {
                    return L"";
                }

                return std::wstring(start, end);

            };

            size_t separator_index = bundle.find('|');

            if(bundle.find('\\') < (separator_index == std::wstring::npos ? bundle.size() : separator_index)) {
                Wh_Log(L"Invalid bundle name for \"%s\".", bundle.c_str());
                return;
            }

            if(separator_index != std::wstring::npos) {

                bundle_id = trim(bundle.substr(0, separator_index));
                assets_folder = trim(bundle.substr(separator_index + 1));

                if(assets_folder.find(L".\\") != std::wstring::npos ||
                   assets_folder.find(L"\\.") != std::wstring::npos ||
                   assets_folder == L"..") {
                    assets_folder = g_default_assets_folder;
                    Wh_Log(L"Invalid assets folder for \"%s\", falling back to default.", bundle_id.c_str());
                }

                std::wstring bundle_folder = find_bundle_folder(bundles_root, bundle_id);

                if(bundle_folder.empty()) {
                    assets_folder = L"";
                    Wh_Log(L"Failed to find bundle folder for \"%s\", skipping redirection.", bundle_id.c_str());
                } else {
                    assets_folder_path = std::filesystem::path(bundle_folder) / assets_folder;
                }

                return;
            }

            bundle_id = trim(bundle);
            std::wstring bundle_folder = find_bundle_folder(bundles_root, bundle_id);

            if(bundle_folder.empty()) {
                assets_folder = L"";
                Wh_Log(L"Failed to find bundle folder for \"%s\", skipping redirection.", bundle_id.c_str());
                return;
            }

            assets_folder = get_assets_folder(std::format(L"{}\\AppxManifest.xml", bundle_folder));

            if(assets_folder.empty()) {
                assets_folder = g_default_assets_folder;
                Wh_Log(L"Failed to get assets folder for \"%s\" automatically, falling back to default.", bundle_id.c_str());
                return;
            }

            assets_folder_path = std::filesystem::path(bundle_folder) / assets_folder;

            Wh_Log(L"Automatically found assets folder for \"%s\" in \"%s\".", bundle_id.c_str(), assets_folder.c_str());

        };

        const auto get_generated_assets_path = [](std::wstring bundle_id, std::wstring assets_folder, std::filesystem::path assets_folder_path, std::wstring ico_file) -> std::wstring {

            WCHAR storage_path_buffer[MAX_PATH];
            if (!Wh_GetModStoragePath(storage_path_buffer, ARRAYSIZE(storage_path_buffer))) {
                Wh_Log(L"Failed to setup ICO redirection: Unable to get mod's storage path.");
                return L"";
            }

            std::error_code error_code;
            auto generated_assets_path = std::filesystem::path{storage_path_buffer} / "generated-assets" / bundle_id / assets_folder;

            if(std::filesystem::is_directory(generated_assets_path, error_code)) {

                WIN32_FILE_ATTRIBUTE_DATA ico_info;
                if (!GetFileAttributesEx(ico_file.c_str(), GetFileExInfoStandard, &ico_info)) {
                    Wh_Log(L"Failed to setup ICO redirection: Unable to get ICO file attributes for \"%s\".", ico_file.c_str());
                    return L"";
                }

                FILETIME ico_last_modified_time = ico_info.ftLastWriteTime;

                WIN32_FILE_ATTRIBUTE_DATA generated_assets_info;
                if (!GetFileAttributesEx(generated_assets_path.c_str(), GetFileExInfoStandard, &generated_assets_info)) {
                    Wh_Log(L"Failed to setup ICO redirection: Unable to get generated assets folder attributes for \"%s\".", bundle_id.c_str());
                    return L"";
                }

                FILETIME generated_assets_creation_time = generated_assets_info.ftCreationTime;

                if (CompareFileTime(&ico_last_modified_time, &generated_assets_creation_time) == 0) {
                    Wh_Log(L"Assets for \"%s\" already generated and source icon didn't change.", bundle_id.c_str());
                    return generated_assets_path;
                }

                for (int suffix = 0; suffix < 100; suffix++) {

                    if (suffix > 0) {
                        generated_assets_path = std::filesystem::path{storage_path_buffer} / "generated-assets" / std::format(L"{}_{}", bundle_id, suffix + 1) / assets_folder;
                    }

                    if (!std::filesystem::is_directory(generated_assets_path, error_code)) {
                        // Generated assets folder doesn't exist, we can use it.
                        break;
                    }

                    // Generated assets folder exists, try to remove it.
                    Wh_Log(L"Generated assets folder already exists, trying to remove: %s", generated_assets_path.c_str());
                    std::filesystem::remove_all(generated_assets_path, error_code);

                    if (!std::filesystem::is_directory(generated_assets_path, error_code)) {
                        // Successfully removed Generated assets folder.
                        break;
                    }

                    Wh_Log(L"Failed to remove Generated assets folder, trying next usable name...");

                }

                if (std::filesystem::is_directory(generated_assets_path, error_code)) {
                    Wh_Log(L"Failed to setup ICO redirection: Unable to find a usable Generated assets folder name.");
                    return L"";
                }

                std::filesystem::create_directories(generated_assets_path, error_code);

                HANDLE generated_assets_handle = CreateFile(
                    generated_assets_path.c_str(),
                    FILE_WRITE_ATTRIBUTES,
                    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                    nullptr,
                    OPEN_EXISTING,
                    FILE_FLAG_BACKUP_SEMANTICS,
                    nullptr
                );

                if (generated_assets_handle != INVALID_HANDLE_VALUE) {
                    SetFileTime(generated_assets_handle, &ico_last_modified_time, nullptr, nullptr);
                    CloseHandle(generated_assets_handle);
                }

            }

            Gdiplus::GdiplusStartupInput gdi_startup;
            ULONG_PTR gdi_token;

            if (GdiplusStartup(&gdi_token, &gdi_startup, nullptr) != Gdiplus::Ok) {
                Wh_Log(L"Failed to setup ICO redirection: Unable to initialize GDI+.");
                return L"";
            }

            const auto get_clsid_encoder = [](std::wstring mime_type, CLSID* clsid) -> int {

                UINT encoders_count = 0;
                UINT encoders_size = 0;

                Gdiplus::GetImageEncodersSize(&encoders_count, &encoders_size);

                if (encoders_size == 0) {
                    return -1;
                }

                std::vector<Gdiplus::ImageCodecInfo> encoders(encoders_size / sizeof(Gdiplus::ImageCodecInfo));
                Gdiplus::GetImageEncoders(encoders_count, encoders_size, encoders.data());

                for (UINT i = 0; i < encoders_count; ++i) {
                    if (wcscmp(encoders[i].MimeType, mime_type.c_str()) == 0) {
                        *clsid = encoders[i].Clsid;
                        return i;
                    }
                }

                return -1;

            };

            CLSID png_encoder_clsid;

            if (get_clsid_encoder(L"image/png", &png_encoder_clsid) == -1) {
                Wh_Log(L"Failed to setup ICO redirection: Unable to get PNG encoder.");
                return L"";
            }

            // Generate common tiles from an .ico file.
            // Same concept as TileGen: https://github.com/atferrys/TileGen
            // Partially taken and adapted from: https://stackoverflow.com/a/22885412

            const auto generate_tile = [ico_file, png_encoder_clsid](int width, int height, std::wstring output_file) {

                HICON icon = nullptr;

                UINT result = PrivateExtractIconsW(
                    ico_file.c_str(),
                    0,
                    width,
                    height,
                    &icon,
                    nullptr,
                    1,
                    0
                );

                if (result == 0 || icon == nullptr) {
                    Wh_Log(L"Failed to generate asset from ICO file: Unable to read icon.");
                    return;
                }

                ICONINFO icon_info = {};

                if (!GetIconInfo(icon, &icon_info)) {
                    DestroyIcon(icon);
                    Wh_Log(L"Failed to generate asset from ICO file: Unable to get icon info.");
                    return;
                }

                HDC hdc = GetDC(nullptr);

                const auto cleanup = [&hdc, &icon_info, &icon]() {

                    if (hdc) {
                        ReleaseDC(nullptr, hdc);
                    }

                    if (icon_info.hbmColor) {
                        DeleteObject(icon_info.hbmColor);
                    }

                    if (icon_info.hbmMask) {
                        DeleteObject(icon_info.hbmMask);
                    }

                    if (icon) {
                        DestroyIcon(icon);
                    }

                };

                BITMAP bitmap = {};

                if (!GetObject(icon_info.hbmColor, sizeof(BITMAP), &bitmap)) {
                    Wh_Log(L"Failed to generate asset from ICO file: Unable to get bitmap info.");
                    cleanup();
                    return;
                }

                BITMAPINFO bitmap_info = {
                    .bmiHeader = {
                        .biSize = sizeof(BITMAPINFOHEADER),
                        .biWidth = bitmap.bmWidth,
                        .biHeight = -bitmap.bmHeight,
                        .biPlanes = 1,
                        .biBitCount = 32,
                        .biCompression = BI_RGB
                    }
                };

                int pixel_count = bitmap.bmWidth * bitmap.bmHeight;
                std::vector<UINT32> pixels(pixel_count);

                if (!GetDIBits(
                    hdc,
                    icon_info.hbmColor,
                    0,
                    bitmap.bmHeight,
                    pixels.data(),
                    &bitmap_info,
                    DIB_RGB_COLORS
                )) {
                    Wh_Log(L"Failed to generate asset from ICO file: Unable to read bitmap pixels.");
                    cleanup();
                    return;
                }

                bool has_alpha = false;

                for (int pixel : pixels) {
                    if ((pixel & 0xFF000000) != 0) {
                        has_alpha = true;
                        break;
                    }
                }

                if (!has_alpha && icon_info.hbmMask) {

                    std::vector<UINT32> mask(pixel_count);

                    if (!GetDIBits(
                        hdc,
                        icon_info.hbmMask,
                        0,
                        bitmap.bmHeight,
                        mask.data(),
                        &bitmap_info,
                        DIB_RGB_COLORS
                    )) {
                        Wh_Log(L"Failed to generate asset from ICO file: Unable to read bitmap alpha mask.");
                        cleanup();
                        return;
                    }

                    for (int i = 0; i < pixel_count; i++) {
                        if (mask[i] == 0) {
                            pixels[i] |= 0xFF000000;
                        }
                    }

                }

                Gdiplus::Bitmap output_bitmap(
                    bitmap.bmWidth,
                    bitmap.bmHeight,
                    bitmap.bmWidth * 4,
                    PixelFormat32bppARGB,
                    (BYTE*) pixels.data()
                );

                if (output_bitmap.Save(output_file.c_str(), &png_encoder_clsid, nullptr) != Gdiplus::Ok) {
                    Wh_Log(L"Failed to generate asset from ICO file: Unable to save output bitmap: %s", output_file.c_str());
                }

                cleanup();

            };

            for (const auto& entry : std::filesystem::recursive_directory_iterator(assets_folder_path, error_code)) {

                if (!entry.is_regular_file()) {
                    continue;
                }

                std::filesystem::path path = entry.path();
                std::wstring filename = path.filename().wstring();

                if (!filename.ends_with(L".png")) {
                    continue;
                }

                if (filename.find(L"targetsize") == std::wstring::npos) {
                    continue;
                }

                if (filename.find(L"contrast") != std::wstring::npos) {
                    continue;
                }

                Gdiplus::Image tile_image = path.c_str();

                if (tile_image.GetLastStatus() != Gdiplus::Ok) {
                    Wh_Log(L"Failed to generate asset from ICO file: Unable to read Reference Tile: %s", path.c_str());
                    continue;
                }

                UINT tile_width = tile_image.GetWidth();
                UINT tile_height = tile_image.GetHeight();

                if (tile_width != tile_height) {
                    continue;
                }

                const auto generated_tile_path = generated_assets_path / path.lexically_relative(assets_folder_path);
                std::filesystem::create_directories(generated_tile_path.parent_path(), error_code);

                generate_tile(tile_width, tile_height, generated_tile_path);

            }

            Gdiplus::GdiplusShutdown(gdi_token);

            Wh_Log(L"Assets for \"%s\" generated from icon successfully.", bundle_id.c_str());

            return generated_assets_path;

        };

        std::wstring bundle_id;
        std::wstring assets_folder;
        std::filesystem::path assets_folder_path;

        deduct_bundle(bundles_root, std::wstring(bundle), bundle_id, assets_folder, assets_folder_path);

        if(bundle_id.empty() || assets_folder.empty()) {
            return;
        }

        std::filesystem::path normalized_redirect = normalize_path(redirect, theme_folder);
        std::error_code error_code;

        if(!assets_folder_path.empty() &&
            std::filesystem::exists(normalized_redirect, error_code) &&
            std::filesystem::is_regular_file(normalized_redirect, error_code) &&
            normalized_redirect.extension() == ".ico") {

            std::wstring generated_assets_path = get_generated_assets_path(
                bundle_id,
                assets_folder,
                assets_folder_path,
                normalized_redirect
            );

            if(generated_assets_path.empty()) {
                return;
            }

            normalized_redirect = generated_assets_path;

        }

        auto path = std::format(L"\\??\\{}\\{}_*\\{}", bundles_root, bundle_id, assets_folder);
        auto redirection = std::format(L"\\??\\{}", normalized_redirect.wstring());

        redirections[path] = redirection;

    };

    auto add_custom_redirection = [&redirections, normalize_path](std::wstring assets_path, std::wstring redirect, std::filesystem::path theme_folder = g_normalize_path_base_path) {

        const auto is_path_valid = [normalize_path](std::wstring path) -> BOOL {

            // Matches ? as a single character, and * as any number of characters
            const auto pattern_match = [](const wchar_t* pat, size_t plen, const wchar_t* str, size_t slen) -> BOOL {
                const wchar_t* p = pat;
                const wchar_t* s = str;
                const wchar_t* p_end = pat + plen;
                const wchar_t* s_end = str + slen;

                const wchar_t* star_pat = nullptr;
                const wchar_t* star_str = nullptr;

                while (s < s_end) {
                    if (p < p_end && (*p == L'?' || std::towlower(*p) == std::towlower(*s))) {
                        ++p;
                        ++s;
                    } else if (p < p_end && *p == L'*') {
                        star_pat = p++;
                        star_str = s;
                    } else if (star_pat) {
                        p = star_pat + 1;
                        s = ++star_str;
                    } else {
                        return false;
                    }
                }

                while (p < p_end && *p == L'*') {
                    ++p;
                }

                return p == p_end;
            };

            std::wstring normalized_path = normalize_path(path);

            for(const auto& blacklisted_path : g_custom_redirections_blacklist) {

                // Check if the path is in blacklist
                if(pattern_match(blacklisted_path.data(), blacklisted_path.size(), normalized_path.data(), normalized_path.size())) {
                    return false;
                }

                // Check if the path pattern matches one of the paths that are in blacklist.
                // Will prevent the matching of blacklisted folders with wildcards
                if(pattern_match(normalized_path.data(), normalized_path.size(), blacklisted_path.data(), blacklisted_path.size())) {
                    return false;
                }

            }

            return true;

        };

        if(!is_path_valid(assets_path)) {
            Wh_Log(L"Ignoring illegal custom redirection path: %s", assets_path.c_str());
            return;
        }

        auto path = std::format(L"\\??\\{}", normalize_path(assets_path));
        auto redirection = std::format(L"\\??\\{}", normalize_path(redirect, theme_folder));

        redirections[path] = redirection;

    };

    auto add_theme_redirections = [add_bundle_redirection, add_custom_redirection](std::filesystem::path theme_ini, std::filesystem::path theme_folder) {

        std::error_code error_code;

        if(!std::filesystem::exists(theme_ini, error_code)) {
            Wh_Log(L"Failed to read theme file, path doesn't exist: %s", theme_ini.c_str());
            return;
        }

        const auto read_section = [theme_ini, &error_code](std::wstring section_key, auto on_pair_read) {

            auto theme_ini_size = std::filesystem::file_size(theme_ini, error_code);
            std::wstring buffer(theme_ini_size + 2, L'\0');

            DWORD result = GetPrivateProfileSection(
                section_key.c_str(),
                buffer.data(), buffer.size(),
                theme_ini.c_str()
            );

            if (!result || result == buffer.size() - 2) {
                Wh_Log(L"Error reading section \"%s\" from theme file: %s - Error %u", section_key.c_str(), theme_ini.c_str(), GetLastError());
                return;
            }

            const wchar_t* ptr = buffer.data();

            while (*ptr) {

                std::wstring entry(ptr);
                size_t separator_index = entry.find(L'=');

                if (separator_index != std::wstring::npos) {

                    std::wstring key = entry.substr(0, separator_index);
                    std::wstring value = entry.substr(separator_index + 1);

                    on_pair_read(key, value);

                }

                ptr += entry.size() + 1;

            }

        };

        // Load WindowsApps redirections

        read_section(L"windows-apps", [add_bundle_redirection, theme_folder](std::wstring bundle, std::wstring redirect) {
            add_bundle_redirection(L"C:\\Program Files\\WindowsApps", bundle, redirect, theme_folder);
        });

        // Load SystemApps redirections

        read_section(L"system-apps", [add_bundle_redirection, theme_folder](std::wstring bundle, std::wstring redirect) {
            add_bundle_redirection(L"C:\\Windows\\SystemApps", bundle, redirect, theme_folder);
        });

        // Load Custom redirections

        read_section(L"custom", [add_custom_redirection, theme_folder](std::wstring assets_path, std::wstring redirect) {
            add_custom_redirection(assets_path, redirect, theme_folder);
        });

    };

    auto load_config_redirections = [add_bundle_redirection, add_custom_redirection]() {

        // Load WindowsApps redirections

        for(int i = 0;; i++) {

            PCWSTR bundle = Wh_GetStringSetting(L"storeAppIcons.windows-apps[%d].bundle", i);
            PCWSTR redirect = Wh_GetStringSetting(L"storeAppIcons.windows-apps[%d].redirect", i);

            bool hasRedirection = *bundle && *redirect;

            if(hasRedirection) {
                add_bundle_redirection(L"C:\\Program Files\\WindowsApps", bundle, redirect);
            }

            Wh_FreeStringSetting(bundle);
            Wh_FreeStringSetting(redirect);

            if(!hasRedirection) {
                break;
            }

        }

        // Load SystemApps redirections

        for(int i = 0;; i++) {

            PCWSTR bundle = Wh_GetStringSetting(L"storeAppIcons.system-apps[%d].bundle", i);
            PCWSTR redirect = Wh_GetStringSetting(L"storeAppIcons.system-apps[%d].redirect", i);

            bool hasRedirection = *bundle && *redirect;

            if(hasRedirection) {
                add_bundle_redirection(L"C:\\Windows\\SystemApps", bundle, redirect);
            }

            Wh_FreeStringSetting(bundle);
            Wh_FreeStringSetting(redirect);

            if(!hasRedirection) {
                break;
            }

        }

        // Load Custom redirections

        for(int i = 0;; i++) {

            PCWSTR assets_path = Wh_GetStringSetting(L"storeAppIcons.custom[%d].assets-path", i);
            PCWSTR redirect = Wh_GetStringSetting(L"storeAppIcons.custom[%d].redirect", i);

            bool hasRedirection = *assets_path && *redirect;

            if(hasRedirection) {
                add_custom_redirection(assets_path, redirect);
            }

            Wh_FreeStringSetting(assets_path);
            Wh_FreeStringSetting(redirect);

            if(!hasRedirection) {
                break;
            }

        }

    };

    auto load_themes_redirections = [add_theme_redirections, normalize_path]() {

        for(int i = 0;; i++) {

            PCWSTR theme_path = Wh_GetStringSetting(L"storeAppIcons.theme-paths[%d]", i);

            bool hasThemePath = *theme_path;

            if(hasThemePath) {

                std::filesystem::path normalized_theme_path = normalize_path(theme_path);

                std::filesystem::path theme_ini;
                std::filesystem::path theme_folder;

                if (std::filesystem::is_directory(normalized_theme_path)) {
                    theme_ini = normalized_theme_path / L"theme.ini";
                    theme_folder = normalized_theme_path;
                } else {
                    theme_ini = normalized_theme_path;
                    theme_folder = normalized_theme_path.parent_path();
                }

                add_theme_redirections(theme_ini, theme_folder);

            }

            Wh_FreeStringSetting(theme_path);

            if(!hasThemePath) {
                break;
            }

        }

    };

    auto load_icon_theme_redirections = [add_theme_redirections]() {

        // Download icon themes directly with mod options.
        // Mostly taken and adapted from:
        // https://github.com/ramensoftware/windhawk-mods/blob/9ee749979a3dfa668f4a16432d449f77ffb4fce9/mods/icon-resource-redirect.wh.cpp#L2150-L2453

        const auto get_icon_theme_path = [](std::wstring icon_theme) -> std::wstring {

            const auto replace = [](std::wstring string, const wchar_t old_character, const wchar_t new_character) -> std::wstring {
                std::wstring string_copy = string;
                std::replace(string_copy.begin(), string_copy.end(), old_character, new_character);
                return string_copy;
            };

            const auto create_lock = [](std::filesystem::path lock_file, DWORD timeout) {

                HANDLE hFile = CreateFile(
                    lock_file.c_str(),
                    GENERIC_READ | GENERIC_WRITE,
                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                    nullptr,
                    OPEN_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
                    nullptr
                );

                if (hFile == INVALID_HANDLE_VALUE) {
                    return INVALID_HANDLE_VALUE;
                }

                HANDLE hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);

                if (!hEvent) {
                    CloseHandle(hFile);
                    return INVALID_HANDLE_VALUE;
                }

                OVERLAPPED ov = {
                    .hEvent = hEvent
                };

                // Lock first byte only.
                BOOL locked = LockFileEx(hFile, LOCKFILE_EXCLUSIVE_LOCK, 0, 1, 0, &ov);

                if (!locked) {

                    DWORD err = GetLastError();

                    if (err != ERROR_IO_PENDING) {
                        CloseHandle(hEvent);
                        CloseHandle(hFile);
                        return INVALID_HANDLE_VALUE;
                    }

                    DWORD waitResult = WaitForSingleObject(hEvent, timeout);

                    if (waitResult != WAIT_OBJECT_0) {
                        CancelIo(hFile);
                        CloseHandle(hEvent);
                        CloseHandle(hFile);
                        return INVALID_HANDLE_VALUE;
                    }

                    DWORD bytesTransferred;

                    if (!GetOverlappedResult(hFile, &ov, &bytesTransferred, FALSE)) {
                        CloseHandle(hEvent);
                        CloseHandle(hFile);
                        return INVALID_HANDLE_VALUE;
                    }

                }

                CloseHandle(hEvent);

                return hFile;

            };

            const auto remove_lock = [](HANDLE lock_handle, std::filesystem::path lock_file) {

                OVERLAPPED ov = {};
                BOOL unlocked = UnlockFileEx(lock_handle, 0, 1, 0, &ov);
                CloseHandle(lock_handle);

                if(unlocked) {
                    DeleteFile(lock_file.c_str());
                }

                return unlocked;

            };

            const auto download_theme = [](std::wstring icon_theme, std::filesystem::path& temp_zip, std::filesystem::path& temp_extract, std::filesystem::path& icon_theme_path) {

                const auto unzip_to_folder = [](std::filesystem::path zip_file, std::filesystem::path destination_path) {

                    winrt::com_ptr<IShellDispatch> shellDispatch;
                    HRESULT result = CoCreateInstance(
                        CLSID_Shell,
                        nullptr,
                        CLSCTX_INPROC_SERVER,
                        IID_PPV_ARGS(shellDispatch.put())
                    );

                    if (FAILED(result)) {
                        return result;
                    }

                    VARIANT zipFileVariant;
                    zipFileVariant.vt = VT_BSTR;
                    zipFileVariant.bstrVal = _bstr_t(zip_file.c_str());

                    winrt::com_ptr<Folder> zipFile;
                    result = shellDispatch->NameSpace(zipFileVariant, zipFile.put());

                    if (FAILED(result)) {
                        return result;
                    }

                    if (!zipFile) {
                        return E_FAIL;
                    }

                    VARIANT destinationVariant;
                    destinationVariant.vt = VT_BSTR;
                    destinationVariant.bstrVal = _bstr_t(destination_path.c_str());

                    winrt::com_ptr<Folder> destination;
                    result = shellDispatch->NameSpace(destinationVariant, destination.put());

                    if (FAILED(result)) {
                        return result;
                    }

                    if (!destination) {
                        return E_FAIL;
                    }


                    winrt::com_ptr<FolderItems> zipFiles;
                    result = zipFile->Items(zipFiles.put());

                    if (FAILED(result)) {
                        return result;
                    }

                    if (!zipFiles) {
                        return E_FAIL;
                    }

                    LONG zipFilesCount;
                    result = zipFiles->get_Count(&zipFilesCount);

                    if (FAILED(result)) {
                        return result;
                    }

                    // If the zip contains a single folder, select it to avoid an extra nesting.
                    if (zipFilesCount == 1) {

                        VARIANT index;
                        index.vt = VT_I4;
                        index.lVal = 0;

                        winrt::com_ptr<FolderItem> zipSubFolderItem;
                        result = zipFiles->Item(index, zipSubFolderItem.put());

                        if (FAILED(result)) {
                            return result;
                        }

                        if (!zipSubFolderItem) {
                            return E_FAIL;
                        }

                        VARIANT_BOOL isFolder;
                        result = zipSubFolderItem->get_IsFolder(&isFolder);

                        if (FAILED(result)) {
                            return result;
                        }

                        if (isFolder) {

                            winrt::com_ptr<IDispatch> zipSubFolderDispatch;
                            result = zipSubFolderItem->get_GetFolder(zipSubFolderDispatch.put());

                            if (FAILED(result)) {
                                return result;
                            }

                            if (!zipSubFolderDispatch) {
                                return E_FAIL;
                            }

                            winrt::com_ptr<Folder> zipSubFolder;
                            result = zipSubFolderDispatch->QueryInterface(IID_PPV_ARGS(zipSubFolder.put()));

                            if (FAILED(result)) {
                                return result;
                            }

                            if (!zipSubFolder) {
                                return E_FAIL;
                            }

                            result = zipSubFolder->Items(zipFiles.put());

                            if (FAILED(result)) {
                                return result;
                            }

                            if (!zipFiles) {
                                return E_FAIL;
                            }

                        }

                    }

                    winrt::com_ptr<IDispatch> zipFilesDispatch;
                    result = zipFiles->QueryInterface(IID_PPV_ARGS(zipFilesDispatch.put()));

                    if (FAILED(result)) {
                        return result;
                    }

                    if (!zipFilesDispatch) {
                        return E_FAIL;
                    }

                    VARIANT itemVariant;
                    itemVariant.vt = VT_DISPATCH;
                    itemVariant.pdispVal = zipFilesDispatch.get();

                    VARIANT options;
                    options.vt = VT_I4;
                    options.lVal = FOF_NO_UI;

                    return destination->CopyHere(itemVariant, options);

                };

                if (g_downloading_theme_prompt_thread) {
                    if (WaitForSingleObject(g_downloading_theme_prompt_thread, 0) != WAIT_OBJECT_0) {
                        return false;
                    }
                    CloseHandle(g_downloading_theme_prompt_thread);
                }

                static decltype(&TaskDialogIndirect) pTaskDialogIndirect = []() {
                    HMODULE hComctl32 = LoadLibraryEx(L"comctl32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
                    if (!hComctl32) {
                        Wh_Log(L"Failed to load comctl32.dll");
                            return (decltype(&TaskDialogIndirect)) nullptr;
                        }
                    return (decltype(&TaskDialogIndirect)) GetProcAddress(hComctl32, "TaskDialogIndirect");
                }();

                g_downloading_theme_prompt_thread = CreateThread(
                    nullptr,
                    0,
                    [](LPVOID lpParameter) WINAPI -> DWORD {

                        if(!pTaskDialogIndirect) {
                            return 0;
                        }

                        const std::wstring icon_theme = *static_cast<std::wstring*>(lpParameter);
                        const std::wstring message = std::format(g_downloading_theme_prompt_body, icon_theme.c_str());

                        const TASKDIALOG_BUTTON buttons[] = {
                            {IDCLOSE, L"Hide"}
                        };

                        TASKDIALOGCONFIG promptDialogConfig {
                            .cbSize = sizeof(promptDialogConfig),
                            .dwFlags = TDF_SHOW_MARQUEE_PROGRESS_BAR,
                            .dwCommonButtons = 0,

                            .pszWindowTitle = g_downloading_theme_prompt_title,
                            .pszMainIcon = TD_INFORMATION_ICON,
                            .pszMainInstruction = g_downloading_theme_prompt_header,
                            .pszContent = message.c_str(),

                            .cButtons = ARRAYSIZE(buttons),
                            .pButtons = buttons,

                            .pfCallback = [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, LONG_PTR lpRefData) WINAPI -> HRESULT {
                                switch (msg) {
                                    case TDN_CREATED:
                                        g_downloading_theme_prompt = hwnd;
                                        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                                        SendMessage(hwnd, TDM_SET_PROGRESS_BAR_MARQUEE, TRUE, 0);
                                        break;

                                    case TDN_DESTROYED:
                                        g_downloading_theme_prompt = nullptr;
                                        break;
                                }
                                return S_OK;
                            },
                        };

                        pTaskDialogIndirect(&promptDialogConfig, nullptr, nullptr, nullptr);

                        delete static_cast<std::wstring*>(lpParameter);

                        return 0;

                    },
                    new std::wstring(icon_theme),
                    0,
                    nullptr
                );

                const auto show_error_message = [](std::wstring message) {

                    if(g_downloading_theme_prompt) {
                        SendMessage(g_downloading_theme_prompt, TDM_CLICK_BUTTON, TDCBF_CLOSE_BUTTON, 0);
                    }

                    if(!pTaskDialogIndirect) {
                        return;
                    }

                    TASKDIALOGCONFIG promptDialogConfig {
                        .cbSize = sizeof(promptDialogConfig),
                        .dwFlags = TDF_ALLOW_DIALOG_CANCELLATION,
                        .dwCommonButtons = TDCBF_CLOSE_BUTTON,

                        .pszWindowTitle = g_failed_to_download_theme_prompt_title,
                        .pszMainIcon = TD_ERROR_ICON,
                        .pszMainInstruction = g_failed_to_download_theme_prompt_header,
                        .pszContent = message.c_str(),

                        .pfCallback = [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, LONG_PTR lpRefData) WINAPI -> HRESULT {
                            switch (msg) {
                                case TDN_CREATED:
                                    g_failed_to_download_theme_prompt = hwnd;
                                    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                                    break;

                                case TDN_DESTROYED:
                                    g_failed_to_download_theme_prompt = nullptr;
                                    break;
                            }
                            return S_OK;
                        },
                    };

                    pTaskDialogIndirect(&promptDialogConfig, nullptr, nullptr, nullptr);

                };

                const std::wstring theme_url = std::format(
                    L"https://raw.githubusercontent.com/atferrys/uwp-assets-redirect/refs/heads/main/themes/{}.zip",
                    icon_theme
                );

                WH_GET_URL_CONTENT_OPTIONS options {
                    .optionsSize = sizeof(options),
                    .targetFilePath = temp_zip.c_str(),
                };

                const WH_URL_CONTENT* response = Wh_GetUrlContent(theme_url.c_str(), &options);

                if (!response) {
                    Wh_Log(L"Failed to download Icon theme: Wh_GetUrlContent returned NULL.");
                    show_error_message(L"An unknown error occurred while downloading the Icon theme.");
                    return false;
                }

                if (response->statusCode != 200) {
                    Wh_Log(L"Failed to download Icon theme: Request failed with code %d.", response->statusCode);
                    Wh_FreeUrlContent(response);
                    show_error_message(std::format(L"Icon theme download request failed with code {}.", response->statusCode));
                    return false;
                }

                Wh_FreeUrlContent(response);

                HRESULT result = CoInitialize(nullptr);

                if(FAILED(result)) {
                    Wh_Log(L"Failed to download Icon theme: CoInitialize returned 0x%08X", result);
                    show_error_message(std::format(L"COM initialization failed with code 0x{:08X}.", result));
                    return false;
                }

                std::error_code error_code;
                std::filesystem::remove_all(temp_extract, error_code);
                std::filesystem::create_directories(temp_extract, error_code);

                result = unzip_to_folder(temp_zip, temp_extract);

                if (FAILED(result)) {
                    Wh_Log(L"Failed to download Icon theme: UnzipToFolder returned 0x%08X", result);
                    show_error_message(std::format(L"Unzipping of downloaded theme file failed with code 0x{:08X}.", result));
                    return false;
                }

                std::filesystem::create_directories(icon_theme_path.parent_path());
                std::filesystem::rename(temp_extract, icon_theme_path, error_code);

                DeleteFile(temp_zip.c_str());
                CoUninitialize();

                if(g_downloading_theme_prompt) {
                    SendMessage(g_downloading_theme_prompt, TDM_CLICK_BUTTON, TDCBF_CLOSE_BUTTON, 0);
                }

                return std::filesystem::is_directory(icon_theme_path, error_code);

            };

            if(icon_theme.empty()) {
                return L"";
            }

            WCHAR storage_path_buffer[MAX_PATH];
            if (!Wh_GetModStoragePath(storage_path_buffer, ARRAYSIZE(storage_path_buffer))) {
                Wh_Log(L"Failed to setup Icon theme: Unable to get mod's storage path.");
                return L"";
            }

            const auto storage_path = std::filesystem::path{storage_path_buffer} / "icon-themes";
            std::filesystem::create_directories(storage_path);

            if (icon_theme.starts_with(L"local/")) {
                std::error_code local_error_code;
                const auto local_theme_path = storage_path / replace(icon_theme, L'/', L'\\');
                if (std::filesystem::is_regular_file(local_theme_path / "theme.ini", local_error_code)) {
                    Wh_Log(L"Using built-in Icon theme %s.", icon_theme.c_str());
                    return local_theme_path;
                }
                Wh_Log(L"Built-in Icon theme is missing: %s", local_theme_path.c_str());
                return L"";
            }

            // Workaround for: https://github.com/ramensoftware/windhawk-mods/pull/4005#discussion_r3213756330
            // Taken and adapted from: https://github.com/m417z/my-windhawk-mods/commit/cdeeca27376e98cecea2e2f8b637902c86af9699
            const std::wstring icon_theme_path_key = std::format(L"icon_theme_path_{}", icon_theme);

            WCHAR stored_icon_theme_path[MAX_PATH];
            Wh_GetStringValue(
                icon_theme_path_key.c_str(),
                stored_icon_theme_path,
                ARRAYSIZE(stored_icon_theme_path)
            );

            std::error_code error_code;
            std::filesystem::path icon_theme_path;

            if(*stored_icon_theme_path) {
                icon_theme_path = storage_path / stored_icon_theme_path;
                if (std::filesystem::is_directory(icon_theme_path, error_code)) {
                    Wh_Log(L"Theme files for %s already downloaded.", icon_theme.c_str());
                    return icon_theme_path;
                }
            }

            // Find a usable icon theme folder name.
            const std::wstring icon_theme_folder = replace(icon_theme, L'/', L'\\');

            for (int suffix = 0; suffix < 100; suffix++) {

                if (suffix == 0) {
                    icon_theme_path = storage_path / icon_theme_folder;
                } else {
                    icon_theme_path = storage_path / std::format(L"{}_{}", icon_theme_folder, suffix + 1);
                }

                if (!std::filesystem::is_directory(icon_theme_path, error_code)) {
                    // Icon theme folder doesn't exist, we can use it.
                    break;
                }

                // Icon theme folder exists, try to remove it.
                Wh_Log(L"Icon theme folder already exists, trying to remove: %s", icon_theme_path.c_str());
                std::filesystem::remove_all(icon_theme_path, error_code);

                if (!std::filesystem::is_directory(icon_theme_path, error_code)) {
                    // Successfully removed icon theme folder.
                    break;
                }

                Wh_Log(L"Failed to remove Icon theme folder, trying next usable name...");

            }

            if (std::filesystem::is_directory(icon_theme_path, error_code)) {
                Wh_Log(L"Failed to download Icon theme: Unable to find a usable theme folder name.");
                return L"";
            }

            const auto lock_file = storage_path / std::format(L"{}_lock", replace(icon_theme, L'/', L'_'));
            const HANDLE lock_handle = create_lock(lock_file, 30000);

            if (!lock_handle) {
                Wh_Log(L"Failed to download Icon theme: Unable to create temp lock file.");
                return L"";
            }

            Wh_Log(L"Downloading Icon theme for %s...", icon_theme.c_str());

            auto temp_zip = storage_path / std::format(L"{}_temp.zip", replace(icon_theme, L'/', L'_'));
            auto temp_extract = storage_path / std::format(L"{}_temp_extract", replace(icon_theme, L'/', L'_'));

            if (download_theme(icon_theme, temp_zip, temp_extract, icon_theme_path)) {
                Wh_Log(L"Theme files for %s downloaded and extracted successfully.", icon_theme.c_str());
                // Store the Icon theme folder name.
                Wh_SetStringValue(icon_theme_path_key.c_str(), icon_theme_path.c_str());
            } else {
                Wh_Log(L"Failed to download and extract icon theme.");
                icon_theme_path.clear();
            }

            remove_lock(lock_handle, lock_file);

            return icon_theme_path;

        };

        PCWSTR icon_theme = Wh_GetStringSetting(L"storeAppIcons.icon-theme");

        if(*icon_theme) {

            std::wstring icon_theme_path = get_icon_theme_path(std::wstring(icon_theme));

            if(!icon_theme_path.empty()) {
                add_theme_redirections(
                    std::filesystem::path(icon_theme_path) / "theme.ini",
                    std::filesystem::path(icon_theme_path)
                );
            }

        }

        Wh_FreeStringSetting(icon_theme);

    };

    load_icon_theme_redirections();
    load_themes_redirections();
    load_config_redirections();

}

std::atomic<HWND> g_ownership_prompt;

constexpr WCHAR g_ownership_prompt_title[] = L"UWP Assets Redirect Plus - Windhawk";
constexpr WCHAR g_ownership_prompt_header[] = L"Access required";
constexpr WCHAR g_ownership_prompt_body[] =
    L"To work properly, UWP Assets Redirect Plus requires permission to access certain system-protected locations.\n"
    L"\n"
    L"To continue, click on \"Allow\" and respond to the UAC prompt.";

constexpr WCHAR g_ownership_command[] =
    LR"(powershell -NoProfile -WindowStyle minimized Start-Process -Wait -FilePath cmd -Verb RunAs -ArgumentList ')"

    LR"(/c title "UWP Assets Redirect Plus - Windhawk")"
    LR"(& echo Updating permissions, please wait...)"
    LR"(& takeown /F \"C:\Program Files\WindowsApps\" /A)"
    LR"(& icacls \"C:\Program Files\WindowsApps\" /grant \"%COMPUTERNAME%\%USERNAME%:(R)\"')";

void CheckWindowsAppsOwner() {

    const auto is_owner_administrators = [](std::wstring folder_path) -> BOOL {

        PSECURITY_DESCRIPTOR security_descriptor = nullptr;
        PSID owner_sid = nullptr;

        DWORD result = GetNamedSecurityInfoW(
            folder_path.c_str(),
            SE_FILE_OBJECT,
            OWNER_SECURITY_INFORMATION,
            &owner_sid,
            nullptr,
            nullptr,
            nullptr,
            &security_descriptor
        );

        if (result != ERROR_SUCCESS) {
            if(security_descriptor) {
                LocalFree(security_descriptor);
            }
            return false;
        }

        SID_IDENTIFIER_AUTHORITY nt_authority_sid = SECURITY_NT_AUTHORITY;
        PSID administrators_sid = nullptr;

        WINBOOL allocation_result = AllocateAndInitializeSid(
            &nt_authority_sid,
            2,
            SECURITY_BUILTIN_DOMAIN_RID,
            DOMAIN_ALIAS_RID_ADMINS,
            0,
            0,
            0,
            0,
            0,
            0,
            &administrators_sid
        );

        if (!allocation_result) {
            LocalFree(security_descriptor);
            return false;
        }

        BOOL is_owner_adminstators = EqualSid(owner_sid, administrators_sid);

        FreeSid(administrators_sid);
        LocalFree(security_descriptor);

        return is_owner_adminstators;

    };

    if(is_owner_administrators(L"C:\\Program Files\\WindowsApps")) {
        return;
    }

    Wh_Log(L"WindowsApps folder not owned by Administrators group. This will prevent reads, asking permissions...");

    static decltype(&TaskDialogIndirect) pTaskDialogIndirect = []() {
        HMODULE hComctl32 = LoadLibraryEx(L"comctl32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (!hComctl32) {
            Wh_Log(L"Failed to load comctl32.dll");
            return (decltype(&TaskDialogIndirect)) nullptr;
        }
        return (decltype(&TaskDialogIndirect)) GetProcAddress(hComctl32, "TaskDialogIndirect");
    }();

    if(!pTaskDialogIndirect) {
        return;
    }

    TASKDIALOG_BUTTON buttons[] = {
        {IDYES, L"Allow"},
        {IDCANCEL, L"Cancel"}
    };

    TASKDIALOGCONFIG promptDialogConfig {
        .cbSize = sizeof(promptDialogConfig),
        .dwFlags = TDF_ALLOW_DIALOG_CANCELLATION,
        .dwCommonButtons = 0,

        .pszWindowTitle = g_ownership_prompt_title,
        .pszMainIcon = TD_WARNING_ICON,
        .pszMainInstruction = g_ownership_prompt_header,
        .pszContent = g_ownership_prompt_body,

        .cButtons = ARRAYSIZE(buttons),
        .pButtons = buttons,

        .pfCallback = [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, LONG_PTR lpRefData) WINAPI -> HRESULT {
            switch (msg) {
                case TDN_CREATED:
                    g_ownership_prompt = hwnd;
                    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                    SendMessage(hwnd, TDM_SET_BUTTON_ELEVATION_REQUIRED_STATE, IDYES, TRUE);
                    break;

                case TDN_DESTROYED:
                    g_ownership_prompt = nullptr;
                    break;
            }
            return S_OK;
        },
    };

    int button;
    if (SUCCEEDED(pTaskDialogIndirect(&promptDialogConfig, &button, nullptr, nullptr)) && button == IDYES) {
        WCHAR commandLine[ARRAYSIZE(g_ownership_command)];
        memcpy(commandLine, g_ownership_command, sizeof(g_ownership_command));
        STARTUPINFO si = {
            .cb = sizeof(si),
        };
        PROCESS_INFORMATION pi{};
        if (CreateProcess(nullptr, commandLine, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
        }
    }

}

void LoadSettings() {

    std::unordered_map<std::wstring, std::wstring> redirections;

    if(DoesCurrentProcessOwnTaskbar()) {

        CheckWindowsAppsOwner();

        ClearRedirectionsCache(false);
        LoadRedirections(redirections);
        write_redirections_cache(redirections);

        BOOL grant_permissions = Wh_GetIntSetting(L"storeAppIcons.grant-permissions");

        if (!grant_permissions && g_grant_permissions) {
            TogglePermissions(redirections, false);
        } else if (grant_permissions) {
            TogglePermissions(redirections, true);
        }

        g_grant_permissions = grant_permissions;

        Wh_Log(L"Loaded %i redirections and stored them to shared cache.", redirections.size());
        g_redirections = std::move(redirections);

    } else {

        int tries = 0;

        while(tries++ < g_max_read_tries && !read_redirections_cache(redirections)) {
            Wh_Log(L"Redirections haven't been cached yet, retrying... (%i/%i)", tries, g_max_read_tries);
            Sleep(250);
        }

        if(tries > g_max_read_tries) {
            Wh_Log(L"Redirections cache read tries exceeded.");
            return;
        }

        Wh_Log(L"Loaded %i redirections from shared cache.", redirections.size());
        g_redirections = std::move(redirections);

    }

}

BOOL ModInit() {

    LoadSettings();

    HMODULE ntdll = GetModuleHandle(L"ntdll.dll");

    Wh_SetFunctionHook(
        (void*)GetProcAddress(ntdll, "NtCreateFile"),
        (void*)NtCreateFile_Hook,
        (void**)&NtCreateFile_Original
    );

    RefreshIcons(true);

    Wh_Log(L"UWP Assets Redirect Plus has been initialized.");

    return TRUE;

}

void ModSettingsChanged() {

    Wh_Log(L"Reloading configuration...");

    LoadSettings();
    RefreshIcons();

}

void ModUninit() {

    ClearRedirectionsCache();

    RefreshIcons();
    MarkShouldRefreshIcons();

    if(g_grant_permissions) {
        TogglePermissions(g_redirections, false);
    }

}
}  // namespace mod_storeAppIcons

// ===================================================================
// Part: Windows icon swaps (iconCustomizer)
// Icon Customizer 0.1 by FireBlade, https://github.com/FireBlade211
// The original names no license.
// ===================================================================
namespace mod_iconCustomizer {
// The source code of the mod starts here. This sample was inspired by the great
// article of Kyle Halladay, X64 Function Hooking by Example:
// http://kylehalladay.com/blog/2020/11/13/Hooking-By-Example.html
// If you're new to terms such as code injection and function hooking, the
// article is great to get started.


struct {
    LPCWSTR DOCNOASSOC;
    LPCWSTR DOCASSOC;
    LPCWSTR APPLICATION;
    LPCWSTR FOLDER;
    LPCWSTR FOLDEROPEN;
    LPCWSTR DRIVE525;
    LPCWSTR DRIVE35;
    LPCWSTR DRIVEREMOVE;
    LPCWSTR DRIVEFIXED;
    LPCWSTR DRIVENET;
    LPCWSTR DRIVENETDISABLED;
    LPCWSTR DRIVECD;
    LPCWSTR DRIVERAM;
    LPCWSTR WORLD;
    LPCWSTR SERVER;
    LPCWSTR PRINTER;
    LPCWSTR MYNETWORK;
    LPCWSTR FIND;
    LPCWSTR HELP;
    LPCWSTR SHARE;
    LPCWSTR LINK;
    LPCWSTR SLOWFILE;
    LPCWSTR RECYCLER;
    LPCWSTR RECYCLERFULL;
    LPCWSTR MEDIACDAUDIO;
    LPCWSTR LOCK;
    LPCWSTR AUTOLIST;
    LPCWSTR PRINTERNET;
    LPCWSTR SERVERSHARE;
    LPCWSTR PRINTERFAX;
    LPCWSTR PRINTERFAXNET;
    LPCWSTR PRINTERFILE;
    LPCWSTR STACK;
    LPCWSTR MEDIASVCD;
    LPCWSTR STUFFEDFOLDER;
    LPCWSTR DRIVEUNKNOWN;
    LPCWSTR DRIVEDVD;
    LPCWSTR MEDIADVD;
    LPCWSTR MEDIADVDRAM;
    LPCWSTR MEDIADVDRW;
    LPCWSTR MEDIADVDR;
    LPCWSTR MEDIADVDROM;
    LPCWSTR MEDIACDAUDIOPLUS;
    LPCWSTR MEDIACDRW;
    LPCWSTR MEDIACDR;
    LPCWSTR MEDIACDBURN;
    LPCWSTR MEDIABLANKCD;
    LPCWSTR MEDIACDROM;
    LPCWSTR AUDIOFILES;
    LPCWSTR IMAGEFILES;
    LPCWSTR VIDEOFILES;
    LPCWSTR MIXEDFILES;
    LPCWSTR FOLDERBACK;
    LPCWSTR FOLDERFRONT;
    LPCWSTR SHIELD;
    LPCWSTR WARNING;
    LPCWSTR INFO;
    LPCWSTR iERROR;
    LPCWSTR KEY;
    LPCWSTR SOFTWARE;
    LPCWSTR RENAME;
    LPCWSTR iDELETE;
    LPCWSTR MEDIAAUDIODVD;
    LPCWSTR MEDIAMOVIEDVD;
    LPCWSTR MEDIAENHANCEDCD;
    LPCWSTR MEDIAENHANCEDDVD;
    LPCWSTR MEDIAHDDVD;
    LPCWSTR MEDIABLURAY;
    LPCWSTR MEDIAVCD;
    LPCWSTR MEDIADVDPLUSR;
    LPCWSTR MEDIADVDPLUSRW;
    LPCWSTR DESKTOPPC;
    LPCWSTR MOBILEPC;
    LPCWSTR USERS;
    LPCWSTR MEDIASMARTMEDIA;
    LPCWSTR MEDIACOMPACTFLASH;
    LPCWSTR DEVICECELLPHONE;
    LPCWSTR DEVICECAMERA;
    LPCWSTR DEVICEVIDEOCAMERA;
    LPCWSTR DEVICEAUDIOPLAYER;
    LPCWSTR NETWORKCONNECT;
    LPCWSTR INTERNET;
    LPCWSTR ZIPFILE;
    LPCWSTR SETTINGS;
    LPCWSTR DRIVEHDDVD;
    LPCWSTR DRIVEBD;
    LPCWSTR MEDIAHDDVDROM;
    LPCWSTR MEDIAHDDVDR;
    LPCWSTR MEDIAHDDVDRAM;
    LPCWSTR MEDIABDROM;
    LPCWSTR MEDIABDR;
    LPCWSTR MEDIABDRE;
    LPCWSTR CLUSTEREDDRIVE;
} settings;

using SHGetStockIconInfo_t = decltype(&SHGetStockIconInfo);
SHGetStockIconInfo_t SHGetStockIconInfo_Original;

WINAPI HRESULT SHGetStockIconInfo_Hook(
            SHSTOCKICONID   siid,
            UINT            uFlags,
            SHSTOCKICONINFO *psii
)
{
    LPCWSTR iconString = NULL;

    switch (siid)
    {
        case SIID_DOCNOASSOC:
            iconString = settings.DOCNOASSOC;
            break;
        case SIID_DOCASSOC:
            iconString = settings.DOCASSOC;
            break;
        case SIID_APPLICATION:
            iconString = settings.APPLICATION;
            break;
        case SIID_FOLDER:
            iconString = settings.FOLDER;
            break;
        case SIID_FOLDEROPEN:
            iconString = settings.FOLDEROPEN;
            break;
        case SIID_DRIVE525:
            iconString = settings.DRIVE525;
            break;
        case SIID_DRIVE35:
            iconString = settings.DRIVE35;
            break;
        case SIID_DRIVEREMOVE:
            iconString = settings.DRIVEREMOVE;
            break;
        case SIID_DRIVEFIXED:
            iconString = settings.DRIVEFIXED;
            break;
        case SIID_DRIVENET:
            iconString = settings.DRIVENET;
            break;
        case SIID_DRIVENETDISABLED:
            iconString = settings.DRIVENETDISABLED;
            break;
        case SIID_DRIVECD:
            iconString = settings.DRIVECD;
            break;
        case SIID_DRIVERAM:
            iconString = settings.DRIVERAM;
            break;
        case SIID_WORLD:
            iconString = settings.WORLD;
            break;
        case SIID_SERVER:
            iconString = settings.SERVER;
            break;
        case SIID_PRINTER:
            iconString = settings.PRINTER;
            break;
        case SIID_MYNETWORK:
            iconString = settings.MYNETWORK;
            break;
        case SIID_FIND:
            iconString = settings.FIND;
            break;
        case SIID_HELP:
            iconString = settings.HELP;
            break;
        case SIID_SHARE:
            iconString = settings.SHARE;
            break;
        case SIID_LINK:
            iconString = settings.LINK;
            break;
        case SIID_SLOWFILE:
            iconString = settings.SLOWFILE;
            break;
        case SIID_RECYCLER:
            iconString = settings.RECYCLER;
            break;
        case SIID_RECYCLERFULL:
            iconString = settings.RECYCLERFULL;
            break;
        case SIID_MEDIACDAUDIO:
            iconString = settings.MEDIACDAUDIO;
            break;
        case SIID_LOCK:
            iconString = settings.LOCK;
            break;
        case SIID_AUTOLIST:
            iconString = settings.AUTOLIST;
            break;
        case SIID_PRINTERNET:
            iconString = settings.PRINTERNET;
            break;
        case SIID_SERVERSHARE:
            iconString = settings.SERVERSHARE;
            break;
        case SIID_PRINTERFAX:
            iconString = settings.PRINTERFAX;
            break;
        case SIID_PRINTERFAXNET:
            iconString = settings.PRINTERFAXNET;
            break;
        case SIID_PRINTERFILE:
            iconString = settings.PRINTERFILE;
            break;
        case SIID_STACK:
            iconString = settings.STACK;
            break;
        case SIID_MEDIASVCD:
            iconString = settings.MEDIASVCD;
            break;
        case SIID_STUFFEDFOLDER:
            iconString = settings.STUFFEDFOLDER;
            break;
        case SIID_DRIVEUNKNOWN:
            iconString = settings.DRIVEUNKNOWN;
            break;
        case SIID_DRIVEDVD:
            iconString = settings.DRIVEDVD;
            break;
        case SIID_MEDIADVD:
            iconString = settings.MEDIADVD;
            break;
        case SIID_MEDIADVDRAM:
            iconString = settings.MEDIADVDRAM;
            break;
        case SIID_MEDIADVDRW:
            iconString = settings.MEDIADVDRW;
            break;
        case SIID_MEDIADVDR:
            iconString = settings.MEDIADVDR;
            break;
        case SIID_MEDIADVDROM:
            iconString = settings.MEDIADVDROM;
            break;
        case SIID_MEDIACDAUDIOPLUS:
            iconString = settings.MEDIACDAUDIOPLUS;
            break;
        case SIID_MEDIACDRW:
            iconString = settings.MEDIACDRW;
            break;
        case SIID_MEDIACDR:
            iconString = settings.MEDIACDR;
            break;
        case SIID_MEDIACDBURN:
            iconString = settings.MEDIACDBURN;
            break;
        case SIID_MEDIABLANKCD:
            iconString = settings.MEDIABLANKCD;
            break;
        case SIID_MEDIACDROM:
            iconString = settings.MEDIACDROM;
            break;
        case SIID_AUDIOFILES:
            iconString = settings.AUDIOFILES;
            break;
        case SIID_IMAGEFILES:
            iconString = settings.IMAGEFILES;
            break;
        case SIID_VIDEOFILES:
            iconString = settings.VIDEOFILES;
            break;
        case SIID_MIXEDFILES:
            iconString = settings.MIXEDFILES;
            break;
        case SIID_FOLDERBACK:
            iconString = settings.FOLDERBACK;
            break;
        case SIID_FOLDERFRONT:
            iconString = settings.FOLDERFRONT;
            break;
        case SIID_SHIELD:
            iconString = settings.SHIELD;
            break;
        case SIID_WARNING:
            iconString = settings.WARNING;
            break;
        case SIID_INFO:
            iconString = settings.INFO;
            break;
        case SIID_ERROR:
            iconString = settings.iERROR;
            break;
        case SIID_KEY:
            iconString = settings.KEY;
            break;
        case SIID_SOFTWARE:
            iconString = settings.SOFTWARE;
            break;
        case SIID_RENAME:
            iconString = settings.RENAME;
            break;
        case SIID_DELETE:
            iconString = settings.iDELETE;
            break;
        case SIID_MEDIAAUDIODVD:
            iconString = settings.MEDIAAUDIODVD;
            break;
        case SIID_MEDIAMOVIEDVD:
            iconString = settings.MEDIAMOVIEDVD;
            break;
        case SIID_MEDIAENHANCEDCD:
            iconString = settings.MEDIAENHANCEDCD;
            break;
        case SIID_MEDIAENHANCEDDVD:
            iconString = settings.MEDIAENHANCEDDVD;
            break;
        case SIID_MEDIAHDDVD:
            iconString = settings.MEDIAHDDVD;
            break;
        case SIID_MEDIABLURAY:
            iconString = settings.MEDIABLURAY;
            break;
        case SIID_MEDIAVCD:
            iconString = settings.MEDIAVCD;
            break;
        case SIID_MEDIADVDPLUSR:
            iconString = settings.MEDIADVDPLUSR;
            break;
        case SIID_MEDIADVDPLUSRW:
            iconString = settings.MEDIADVDPLUSRW;
            break;
        case SIID_DESKTOPPC:
            iconString = settings.DESKTOPPC;
            break;
        case SIID_MOBILEPC:
            iconString = settings.MOBILEPC;
            break;
        case SIID_USERS:
            iconString = settings.USERS;
            break;
        case SIID_MEDIASMARTMEDIA:
            iconString = settings.MEDIASMARTMEDIA;
            break;
        case SIID_MEDIACOMPACTFLASH:
            iconString = settings.MEDIACOMPACTFLASH;
            break;
        case SIID_DEVICECELLPHONE:
            iconString = settings.DEVICECELLPHONE;
            break;
        case SIID_DEVICECAMERA:
            iconString = settings.DEVICECAMERA;
            break;
        case SIID_DEVICEVIDEOCAMERA:
            iconString = settings.DEVICEVIDEOCAMERA;
            break;
        case SIID_DEVICEAUDIOPLAYER:
            iconString = settings.DEVICEAUDIOPLAYER;
            break;
        case SIID_NETWORKCONNECT:
            iconString = settings.NETWORKCONNECT;
            break;
        case SIID_INTERNET:
            iconString = settings.INTERNET;
            break;
        case SIID_ZIPFILE:
            iconString = settings.ZIPFILE;
            break;
        case SIID_SETTINGS:
            iconString = settings.SETTINGS;
            break;
        case SIID_DRIVEHDDVD:
            iconString = settings.DRIVEHDDVD;
            break;
        case SIID_DRIVEBD:
            iconString = settings.DRIVEBD;
            break;
        case SIID_MEDIAHDDVDROM:
            iconString = settings.MEDIAHDDVDROM;
            break;
        case SIID_MEDIAHDDVDR:
            iconString = settings.MEDIAHDDVDR;
            break;
        case SIID_MEDIAHDDVDRAM:
            iconString = settings.MEDIAHDDVDRAM;
            break;
        case SIID_MEDIABDROM:
            iconString = settings.MEDIABDROM;
            break;
        case SIID_MEDIABDR:
            iconString = settings.MEDIABDR;
            break;
        case SIID_MEDIABDRE:
            iconString = settings.MEDIABDRE;
            break;
        case SIID_CLUSTEREDDRIVE:
            iconString = settings.CLUSTEREDDRIVE;
            break;
        case SIID_MAX_ICONS:
            break;
    }

    if (iconString && wcscmp(iconString, L"") != 0)
    {
        WCHAR buffer[1024] = L""; // max_path is 260 but alloc space for the index
        wcscpy_s(buffer, iconString);

        int i = PathParseIconLocationW(buffer);

        wcscpy_s(psii->szPath, MAX_PATH, buffer);

        psii->iIcon = i;

        UINT flags = 0;
        if ((uFlags & SHGSI_ICON) != 0)
        {
            flags |= SHGFI_ICON;

            if ((uFlags & SHGSI_LARGEICON) != 0)
                flags |= SHGFI_LARGEICON;
            else if ((uFlags & SHGSI_SMALLICON) != 0)
                flags |= SHGFI_SMALLICON;
            else if ((uFlags & SHGSI_SHELLICONSIZE) != 0)
                flags |= SHGFI_SHELLICONSIZE;
        }

        if ((uFlags & SHGSI_SYSICONINDEX) != 0)
            flags |= SHGFI_SYSICONINDEX;
        
        SHFILEINFOW shfi = {};
        if (SHGetFileInfoW(buffer, NULL, &shfi, sizeof(shfi), flags))
        {
            psii->hIcon = shfi.hIcon;
            psii->iSysImageIndex = shfi.iIcon;

            return S_OK;
        }
    }

    return SHGetStockIconInfo_Original(siid, uFlags, psii);
}

void LoadSettings() {
    settings.DOCNOASSOC = Wh_GetStringSetting(L"iconCustomizer.DOCNOASSOC");
    settings.DOCASSOC = Wh_GetStringSetting(L"iconCustomizer.DOCASSOC");
    settings.APPLICATION = Wh_GetStringSetting(L"iconCustomizer.APPLICATION");
    settings.FOLDER = Wh_GetStringSetting(L"iconCustomizer.FOLDER");
    settings.FOLDEROPEN = Wh_GetStringSetting(L"iconCustomizer.FOLDEROPEN");
    settings.DRIVE525 = Wh_GetStringSetting(L"iconCustomizer.DRIVE525");
    settings.DRIVE35 = Wh_GetStringSetting(L"iconCustomizer.DRIVE35");
    settings.DRIVEREMOVE = Wh_GetStringSetting(L"iconCustomizer.DRIVEREMOVE");
    settings.DRIVEFIXED = Wh_GetStringSetting(L"iconCustomizer.DRIVEFIXED");
    settings.DRIVENET = Wh_GetStringSetting(L"iconCustomizer.DRIVENET");
    settings.DRIVENETDISABLED = Wh_GetStringSetting(L"iconCustomizer.DRIVENETDISABLED");
    settings.DRIVECD = Wh_GetStringSetting(L"iconCustomizer.DRIVECD");
    settings.DRIVERAM = Wh_GetStringSetting(L"iconCustomizer.DRIVERAM");
    settings.WORLD = Wh_GetStringSetting(L"iconCustomizer.WORLD");
    settings.SERVER = Wh_GetStringSetting(L"iconCustomizer.SERVER");
    settings.PRINTER = Wh_GetStringSetting(L"iconCustomizer.PRINTER");
    settings.MYNETWORK = Wh_GetStringSetting(L"iconCustomizer.MYNETWORK");
    settings.FIND = Wh_GetStringSetting(L"iconCustomizer.FIND");
    settings.HELP = Wh_GetStringSetting(L"iconCustomizer.HELP");
    settings.SHARE = Wh_GetStringSetting(L"iconCustomizer.SHARE");
    settings.LINK = Wh_GetStringSetting(L"iconCustomizer.LINK");
    settings.SLOWFILE = Wh_GetStringSetting(L"iconCustomizer.SLOWFILE");
    settings.RECYCLER = Wh_GetStringSetting(L"iconCustomizer.RECYCLER");
    settings.RECYCLERFULL = Wh_GetStringSetting(L"iconCustomizer.RECYCLERFULL");
    settings.MEDIACDAUDIO = Wh_GetStringSetting(L"iconCustomizer.MEDIACDAUDIO");
    settings.LOCK = Wh_GetStringSetting(L"iconCustomizer.LOCK");
    settings.AUTOLIST = Wh_GetStringSetting(L"iconCustomizer.AUTOLIST");
    settings.PRINTERNET = Wh_GetStringSetting(L"iconCustomizer.PRINTERNET");
    settings.SERVERSHARE = Wh_GetStringSetting(L"iconCustomizer.SERVERSHARE");
    settings.PRINTERFAX = Wh_GetStringSetting(L"iconCustomizer.PRINTERFAX");
    settings.PRINTERFAXNET = Wh_GetStringSetting(L"iconCustomizer.PRINTERFAXNET");
    settings.PRINTERFILE = Wh_GetStringSetting(L"iconCustomizer.PRINTERFILE");
    settings.STACK = Wh_GetStringSetting(L"iconCustomizer.STACK");
    settings.MEDIASVCD = Wh_GetStringSetting(L"iconCustomizer.MEDIASVCD");
    settings.STUFFEDFOLDER = Wh_GetStringSetting(L"iconCustomizer.STUFFEDFOLDER");
    settings.DRIVEUNKNOWN = Wh_GetStringSetting(L"iconCustomizer.DRIVEUNKNOWN");
    settings.DRIVEDVD = Wh_GetStringSetting(L"iconCustomizer.DRIVEDVD");
    settings.MEDIADVD = Wh_GetStringSetting(L"iconCustomizer.MEDIADVD");
    settings.MEDIADVDRAM = Wh_GetStringSetting(L"iconCustomizer.MEDIADVDRAM");
    settings.MEDIADVDRW = Wh_GetStringSetting(L"iconCustomizer.MEDIADVDRW");
    settings.MEDIADVDR = Wh_GetStringSetting(L"iconCustomizer.MEDIADVDR");
    settings.MEDIADVDROM = Wh_GetStringSetting(L"iconCustomizer.MEDIADVDROM");
    settings.MEDIACDAUDIOPLUS = Wh_GetStringSetting(L"iconCustomizer.MEDIACDAUDIOPLUS");
    settings.MEDIACDRW = Wh_GetStringSetting(L"iconCustomizer.MEDIACDRW");
    settings.MEDIACDR = Wh_GetStringSetting(L"iconCustomizer.MEDIACDR");
    settings.MEDIACDBURN = Wh_GetStringSetting(L"iconCustomizer.MEDIACDBURN");
    settings.MEDIABLANKCD = Wh_GetStringSetting(L"iconCustomizer.MEDIABLANKCD");
    settings.MEDIACDROM = Wh_GetStringSetting(L"iconCustomizer.MEDIACDROM");
    settings.AUDIOFILES = Wh_GetStringSetting(L"iconCustomizer.AUDIOFILES");
    settings.IMAGEFILES = Wh_GetStringSetting(L"iconCustomizer.IMAGEFILES");
    settings.VIDEOFILES = Wh_GetStringSetting(L"iconCustomizer.VIDEOFILES");
    settings.MIXEDFILES = Wh_GetStringSetting(L"iconCustomizer.MIXEDFILES");
    settings.FOLDERBACK = Wh_GetStringSetting(L"iconCustomizer.FOLDERBACK");
    settings.FOLDERFRONT = Wh_GetStringSetting(L"iconCustomizer.FOLDERFRONT");
    settings.SHIELD = Wh_GetStringSetting(L"iconCustomizer.SHIELD");
    settings.WARNING = Wh_GetStringSetting(L"iconCustomizer.WARNING");
    settings.INFO = Wh_GetStringSetting(L"iconCustomizer.INFO");
    settings.iERROR = Wh_GetStringSetting(L"iconCustomizer.iERROR");
    settings.KEY = Wh_GetStringSetting(L"iconCustomizer.KEY");
    settings.SOFTWARE = Wh_GetStringSetting(L"iconCustomizer.SOFTWARE");
    settings.RENAME = Wh_GetStringSetting(L"iconCustomizer.RENAME");
    settings.iDELETE = Wh_GetStringSetting(L"iconCustomizer.iDELETE");
    settings.MEDIAAUDIODVD = Wh_GetStringSetting(L"iconCustomizer.MEDIAAUDIODVD");
    settings.MEDIAMOVIEDVD = Wh_GetStringSetting(L"iconCustomizer.MEDIAMOVIEDVD");
    settings.MEDIAENHANCEDCD = Wh_GetStringSetting(L"iconCustomizer.MEDIAENHANCEDCD");
    settings.MEDIAENHANCEDDVD = Wh_GetStringSetting(L"iconCustomizer.MEDIAENHANCEDDVD");
    settings.MEDIAHDDVD = Wh_GetStringSetting(L"iconCustomizer.MEDIAHDDVD");
    settings.MEDIABLURAY = Wh_GetStringSetting(L"iconCustomizer.MEDIABLURAY");
    settings.MEDIAVCD = Wh_GetStringSetting(L"iconCustomizer.MEDIAVCD");
    settings.MEDIADVDPLUSR = Wh_GetStringSetting(L"iconCustomizer.MEDIADVDPLUSR");
    settings.MEDIADVDPLUSRW = Wh_GetStringSetting(L"iconCustomizer.MEDIADVDPLUSRW");
    settings.DESKTOPPC = Wh_GetStringSetting(L"iconCustomizer.DESKTOPPC");
    settings.MOBILEPC = Wh_GetStringSetting(L"iconCustomizer.MOBILEPC");
    settings.USERS = Wh_GetStringSetting(L"iconCustomizer.USERS");
    settings.MEDIASMARTMEDIA = Wh_GetStringSetting(L"iconCustomizer.MEDIASMARTMEDIA");
    settings.MEDIACOMPACTFLASH = Wh_GetStringSetting(L"iconCustomizer.MEDIACOMPACTFLASH");
    settings.DEVICECELLPHONE = Wh_GetStringSetting(L"iconCustomizer.DEVICECELLPHONE");
    settings.DEVICECAMERA = Wh_GetStringSetting(L"iconCustomizer.DEVICECAMERA");
    settings.DEVICEVIDEOCAMERA = Wh_GetStringSetting(L"iconCustomizer.DEVICEVIDEOCAMERA");
    settings.DEVICEAUDIOPLAYER = Wh_GetStringSetting(L"iconCustomizer.DEVICEAUDIOPLAYER");
    settings.NETWORKCONNECT = Wh_GetStringSetting(L"iconCustomizer.NETWORKCONNECT");
    settings.INTERNET = Wh_GetStringSetting(L"iconCustomizer.INTERNET");
    settings.ZIPFILE = Wh_GetStringSetting(L"iconCustomizer.ZIPFILE");
    settings.SETTINGS = Wh_GetStringSetting(L"iconCustomizer.SETTINGS");
    settings.DRIVEHDDVD = Wh_GetStringSetting(L"iconCustomizer.DRIVEHDDVD");
    settings.DRIVEBD = Wh_GetStringSetting(L"iconCustomizer.DRIVEBD");
    settings.MEDIAHDDVDROM = Wh_GetStringSetting(L"iconCustomizer.MEDIAHDDVDROM");
    settings.MEDIAHDDVDR = Wh_GetStringSetting(L"iconCustomizer.MEDIAHDDVDR");
    settings.MEDIAHDDVDRAM = Wh_GetStringSetting(L"iconCustomizer.MEDIAHDDVDRAM");
    settings.MEDIABDROM = Wh_GetStringSetting(L"iconCustomizer.MEDIABDROM");
    settings.MEDIABDR = Wh_GetStringSetting(L"iconCustomizer.MEDIABDR");
    settings.MEDIABDRE = Wh_GetStringSetting(L"iconCustomizer.MEDIABDRE");
    settings.CLUSTEREDDRIVE = Wh_GetStringSetting(L"iconCustomizer.CLUSTEREDDRIVE");
}

// The mod is being initialized, load settings, hook functions, and do other
// initialization stuff if required.
BOOL ModInit() {
    Wh_Log(L"Init");

    LoadSettings();

    HMODULE hShell32Module = LoadLibraryW(L"shell32.dll");
    SHGetStockIconInfo_t SHGetStockIconInfo =
        (SHGetStockIconInfo_t)GetProcAddress(hShell32Module,
                                                "SHGetStockIconInfo");

    Wh_SetFunctionHook((void*)SHGetStockIconInfo,
                       (void*)SHGetStockIconInfo_Hook,
                       (void**)&SHGetStockIconInfo_Original);

    return TRUE;
}

void FreeSettingStrings()
{
    if (settings.DOCNOASSOC) Wh_FreeStringSetting(settings.DOCNOASSOC);
    if (settings.DOCASSOC) Wh_FreeStringSetting(settings.DOCASSOC);
    if (settings.APPLICATION) Wh_FreeStringSetting(settings.APPLICATION);
    if (settings.FOLDER) Wh_FreeStringSetting(settings.FOLDER);
    if (settings.FOLDEROPEN) Wh_FreeStringSetting(settings.FOLDEROPEN);
    if (settings.DRIVE525) Wh_FreeStringSetting(settings.DRIVE525);
    if (settings.DRIVE35) Wh_FreeStringSetting(settings.DRIVE35);
    if (settings.DRIVEREMOVE) Wh_FreeStringSetting(settings.DRIVEREMOVE);
    if (settings.DRIVEFIXED) Wh_FreeStringSetting(settings.DRIVEFIXED);
    if (settings.DRIVENET) Wh_FreeStringSetting(settings.DRIVENET);
    if (settings.DRIVENETDISABLED) Wh_FreeStringSetting(settings.DRIVENETDISABLED);
    if (settings.DRIVECD) Wh_FreeStringSetting(settings.DRIVECD);
    if (settings.DRIVERAM) Wh_FreeStringSetting(settings.DRIVERAM);
    if (settings.WORLD) Wh_FreeStringSetting(settings.WORLD);
    if (settings.SERVER) Wh_FreeStringSetting(settings.SERVER);
    if (settings.PRINTER) Wh_FreeStringSetting(settings.PRINTER);
    if (settings.MYNETWORK) Wh_FreeStringSetting(settings.MYNETWORK);
    if (settings.FIND) Wh_FreeStringSetting(settings.FIND);
    if (settings.HELP) Wh_FreeStringSetting(settings.HELP);
    if (settings.SHARE) Wh_FreeStringSetting(settings.SHARE);
    if (settings.LINK) Wh_FreeStringSetting(settings.LINK);
    if (settings.SLOWFILE) Wh_FreeStringSetting(settings.SLOWFILE);
    if (settings.RECYCLER) Wh_FreeStringSetting(settings.RECYCLER);
    if (settings.RECYCLERFULL) Wh_FreeStringSetting(settings.RECYCLERFULL);
    if (settings.MEDIACDAUDIO) Wh_FreeStringSetting(settings.MEDIACDAUDIO);
    if (settings.LOCK) Wh_FreeStringSetting(settings.LOCK);
    if (settings.AUTOLIST) Wh_FreeStringSetting(settings.AUTOLIST);
    if (settings.PRINTERNET) Wh_FreeStringSetting(settings.PRINTERNET);
    if (settings.SERVERSHARE) Wh_FreeStringSetting(settings.SERVERSHARE);
    if (settings.PRINTERFAX) Wh_FreeStringSetting(settings.PRINTERFAX);
    if (settings.PRINTERFAXNET) Wh_FreeStringSetting(settings.PRINTERFAXNET);
    if (settings.PRINTERFILE) Wh_FreeStringSetting(settings.PRINTERFILE);
    if (settings.STACK) Wh_FreeStringSetting(settings.STACK);
    if (settings.MEDIASVCD) Wh_FreeStringSetting(settings.MEDIASVCD);
    if (settings.STUFFEDFOLDER) Wh_FreeStringSetting(settings.STUFFEDFOLDER);
    if (settings.DRIVEUNKNOWN) Wh_FreeStringSetting(settings.DRIVEUNKNOWN);
    if (settings.DRIVEDVD) Wh_FreeStringSetting(settings.DRIVEDVD);
    if (settings.MEDIADVD) Wh_FreeStringSetting(settings.MEDIADVD);
    if (settings.MEDIADVDRAM) Wh_FreeStringSetting(settings.MEDIADVDRAM);
    if (settings.MEDIADVDRW) Wh_FreeStringSetting(settings.MEDIADVDRW);
    if (settings.MEDIADVDR) Wh_FreeStringSetting(settings.MEDIADVDR);
    if (settings.MEDIADVDROM) Wh_FreeStringSetting(settings.MEDIADVDROM);
    if (settings.MEDIACDAUDIOPLUS) Wh_FreeStringSetting(settings.MEDIACDAUDIOPLUS);
    if (settings.MEDIACDRW) Wh_FreeStringSetting(settings.MEDIACDRW);
    if (settings.MEDIACDR) Wh_FreeStringSetting(settings.MEDIACDR);
    if (settings.MEDIACDBURN) Wh_FreeStringSetting(settings.MEDIACDBURN);
    if (settings.MEDIABLANKCD) Wh_FreeStringSetting(settings.MEDIABLANKCD);
    if (settings.MEDIACDROM) Wh_FreeStringSetting(settings.MEDIACDROM);
    if (settings.AUDIOFILES) Wh_FreeStringSetting(settings.AUDIOFILES);
    if (settings.IMAGEFILES) Wh_FreeStringSetting(settings.IMAGEFILES);
    if (settings.VIDEOFILES) Wh_FreeStringSetting(settings.VIDEOFILES);
    if (settings.MIXEDFILES) Wh_FreeStringSetting(settings.MIXEDFILES);
    if (settings.FOLDERBACK) Wh_FreeStringSetting(settings.FOLDERBACK);
    if (settings.FOLDERFRONT) Wh_FreeStringSetting(settings.FOLDERFRONT);
    if (settings.SHIELD) Wh_FreeStringSetting(settings.SHIELD);
    if (settings.WARNING) Wh_FreeStringSetting(settings.WARNING);
    if (settings.INFO) Wh_FreeStringSetting(settings.INFO);
    if (settings.iERROR) Wh_FreeStringSetting(settings.iERROR);
    if (settings.KEY) Wh_FreeStringSetting(settings.KEY);
    if (settings.SOFTWARE) Wh_FreeStringSetting(settings.SOFTWARE);
    if (settings.RENAME) Wh_FreeStringSetting(settings.RENAME);
    if (settings.iDELETE) Wh_FreeStringSetting(settings.iDELETE);
    if (settings.MEDIAAUDIODVD) Wh_FreeStringSetting(settings.MEDIAAUDIODVD);
    if (settings.MEDIAMOVIEDVD) Wh_FreeStringSetting(settings.MEDIAMOVIEDVD);
    if (settings.MEDIAENHANCEDCD) Wh_FreeStringSetting(settings.MEDIAENHANCEDCD);
    if (settings.MEDIAENHANCEDDVD) Wh_FreeStringSetting(settings.MEDIAENHANCEDDVD);
    if (settings.MEDIAHDDVD) Wh_FreeStringSetting(settings.MEDIAHDDVD);
    if (settings.MEDIABLURAY) Wh_FreeStringSetting(settings.MEDIABLURAY);
    if (settings.MEDIAVCD) Wh_FreeStringSetting(settings.MEDIAVCD);
    if (settings.MEDIADVDPLUSR) Wh_FreeStringSetting(settings.MEDIADVDPLUSR);
    if (settings.MEDIADVDPLUSRW) Wh_FreeStringSetting(settings.MEDIADVDPLUSRW);
    if (settings.DESKTOPPC) Wh_FreeStringSetting(settings.DESKTOPPC);
    if (settings.MOBILEPC) Wh_FreeStringSetting(settings.MOBILEPC);
    if (settings.USERS) Wh_FreeStringSetting(settings.USERS);
    if (settings.MEDIASMARTMEDIA) Wh_FreeStringSetting(settings.MEDIASMARTMEDIA);
    if (settings.MEDIACOMPACTFLASH) Wh_FreeStringSetting(settings.MEDIACOMPACTFLASH);
    if (settings.DEVICECELLPHONE) Wh_FreeStringSetting(settings.DEVICECELLPHONE);
    if (settings.DEVICECAMERA) Wh_FreeStringSetting(settings.DEVICECAMERA);
    if (settings.DEVICEVIDEOCAMERA) Wh_FreeStringSetting(settings.DEVICEVIDEOCAMERA);
    if (settings.DEVICEAUDIOPLAYER) Wh_FreeStringSetting(settings.DEVICEAUDIOPLAYER);
    if (settings.NETWORKCONNECT) Wh_FreeStringSetting(settings.NETWORKCONNECT);
    if (settings.INTERNET) Wh_FreeStringSetting(settings.INTERNET);
    if (settings.ZIPFILE) Wh_FreeStringSetting(settings.ZIPFILE);
    if (settings.SETTINGS) Wh_FreeStringSetting(settings.SETTINGS);
    if (settings.DRIVEHDDVD) Wh_FreeStringSetting(settings.DRIVEHDDVD);
    if (settings.DRIVEBD) Wh_FreeStringSetting(settings.DRIVEBD);
    if (settings.MEDIAHDDVDROM) Wh_FreeStringSetting(settings.MEDIAHDDVDROM);
    if (settings.MEDIAHDDVDR) Wh_FreeStringSetting(settings.MEDIAHDDVDR);
    if (settings.MEDIAHDDVDRAM) Wh_FreeStringSetting(settings.MEDIAHDDVDRAM);
    if (settings.MEDIABDROM) Wh_FreeStringSetting(settings.MEDIABDROM);
    if (settings.MEDIABDR) Wh_FreeStringSetting(settings.MEDIABDR);
    if (settings.MEDIABDRE) Wh_FreeStringSetting(settings.MEDIABDRE);
    if (settings.CLUSTEREDDRIVE) Wh_FreeStringSetting(settings.CLUSTEREDDRIVE);
}

// The mod is being unloaded, free all allocated resources.
void ModUninit() {
    Wh_Log(L"Uninit");
    FreeSettingStrings();
}

// The mod settings were changed, reload them.
void ModSettingsChanged() {
    Wh_Log(L"SettingsChanged");
    FreeSettingStrings();

    LoadSettings();
}
}  // namespace mod_iconCustomizer

// ===================================================================
// Part: Icon themes (resourceRedirect)
// Resource Redirect 1.3 by m417z, https://github.com/m417z
//
// // Source code is published under The GNU General Public License v3.0.
// //
// // For bug reports and feature requests, please open an issue here:
// // https://github.com/ramensoftware/windhawk-mods/issues
// //
// // For pull requests, development takes place here:
// // https://github.com/m417z/my-windhawk-mods
// ===================================================================
namespace mod_resourceRedirect {
using namespace std::string_view_literals;

#ifndef LR_EXACTSIZEONLY
#define LR_EXACTSIZEONLY 0x10000
#endif

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#endif

#ifndef STATUS_BUFFER_TOO_SMALL
#define STATUS_BUFFER_TOO_SMALL ((NTSTATUS)0xC0000023L)
#endif

struct {
    WindhawkUtils::StringSetting iconTheme;
    std::atomic<bool> disableThumbnails;
    bool allResourceRedirect;
} g_settings;

std::shared_mutex g_redirectionResourcePathsMutex;
thread_local bool g_redirectionResourcePathsMutexLocked;
std::unordered_map<std::wstring, std::vector<std::wstring>>
    g_redirectionResourcePaths;
std::unordered_map<std::string, std::vector<std::string>>
    g_redirectionResourcePathsA;
std::vector<std::pair<std::wstring, std::wstring>>
    g_redirectionResourcePathPatterns;
std::vector<std::pair<std::string, std::string>>
    g_redirectionResourcePathPatternsA;

std::shared_mutex g_redirectionResourceModulesMutex;
std::unordered_map<std::wstring, HMODULE> g_redirectionResourceModules;

std::atomic<DWORD> g_operationCounter;

HANDLE g_clearCachePromptThread;
std::atomic<HWND> g_clearCachePromptWindow;

// The resource operation count is used to mark recognized high level resource
// operations, which will then be checked in the lower level hooks:
// FindResourceExA, FindResourceExW, LoadResource, SizeofResource,
// RtlLoadString. This allows handling recognized high level calls in a more
// reliable way.
//
// Example: Consider LoadImageW for loading an icon. Internally, it reads two
// resources: the icon group resource and the actual icon resource. If the
// FindResourceExW hook runs for both resources, it might fall back for the icon
// group, but redirect the actual icon resource, causing a mismatch. By handling
// the redirection in LoadImageW, both operations are either redirected or not.
thread_local int g_resourceOperationCount;

auto resourceOperationCountScope() {
    g_resourceOperationCount++;
    return std::unique_ptr<decltype(g_resourceOperationCount),
                           void (*)(decltype(g_resourceOperationCount)*)>{
        &g_resourceOperationCount,
        [](auto resourceOperationCount) { (*resourceOperationCount)--; }};
}

constexpr WCHAR kClearCachePromptTitle[] = L"Resource Redirect - Windhawk";
constexpr WCHAR kClearCachePromptText[] =
    L"For some icons to be updated, the icon cache must be cleared. Do you "
    L"want to clear the icon cache now?\n\nIcon cache files will be deleted, "
    L"and Explorer will be restarted.";
constexpr WCHAR kClearCacheCommand[] =
    LR"(cmd /c "echo Terminating Explorer...)"
    LR"( & taskkill /f /im explorer.exe)"
    LR"( & timeout /t 1 /nobreak >nul)"
    LR"( & del /f /q /a "%LocalAppData%\IconCache.db")"
    LR"( & del /f /s /q /a "%LocalAppData%\Microsoft\Windows\Explorer\iconcache_*.db")"
    LR"( & del /f /s /q /a "%LocalAppData%\Microsoft\Windows\Explorer\thumbcache_*.db")"
    LR"( & timeout /t 1 /nobreak >nul)"
    LR"( & start explorer.exe)"
    LR"( & echo Starting Explorer...)"
    LR"( & timeout /t 3 /nobreak >nul")";

// https://github.com/tidwall/match.c
//
// match returns true if str matches pattern. This is a very
// simple wildcard match where '*' matches on any number characters
// and '?' matches on any one character.
//
// pattern:
//   { term }
// term:
// 	 '*'         matches any sequence of non-Separator characters
// 	 '?'         matches any single non-Separator character
// 	 c           matches character c (c != '*', '?')
template <typename T>
bool strmatch(const T* pat, size_t plen, const T* str, size_t slen) {
    while (plen > 0) {
        if (pat[0] == '*') {
            if (plen == 1)
                return true;
            if (pat[1] == '*') {
                pat++;
                plen--;
                continue;
            }
            if (strmatch(pat + 1, plen - 1, str, slen))
                return true;
            if (slen == 0)
                return false;
            str++;
            slen--;
            continue;
        }
        if (slen == 0)
            return false;
        if (pat[0] != '?' && str[0] != pat[0])
            return false;
        pat++;
        plen--;
        str++;
        slen--;
    }
    return slen == 0 && plen == 0;
}

// chooseAW<char> returns OptionA.
// chooseAW<WCHAR> returns OptionW.
template <typename T, auto OptionA, auto OptionW>
auto chooseAW() {
    if constexpr (std::is_same_v<T, char>) {
        return OptionA;
    } else {
        static_assert(std::is_same_v<T, WCHAR>);
        return OptionW;
    }
}

auto StrToW(PCWSTR str) {
    struct {
        PCWSTR p;
    } result;
    result.p = str;
    return result;
}

// https://stackoverflow.com/a/69410299
auto StrToW(PCSTR str) {
    struct {
        std::wstring wstr;
        PCWSTR p;
    } result;

    if (*str) {
        int strLen = static_cast<int>(strlen(str));
        int sizeNeeded =
            MultiByteToWideChar(CP_ACP, 0, str, strLen, nullptr, 0);
        if (sizeNeeded) {
            result.wstr.resize(sizeNeeded);
            MultiByteToWideChar(CP_ACP, 0, str, strLen, result.wstr.data(),
                                sizeNeeded);
        }
    }

    result.p = result.wstr.c_str();
    return result;
}

// A helper function to skip locking if the thread already holds the lock, since
// it's UB. Nested locks may happen if one hooked function is implemented with
// the help of another hooked function. We assume here that the locks are freed
// in reverse order.
auto RedirectionResourcePathsMutexSharedLock() {
    class Result {
       public:
        Result() = default;

        Result(std::shared_mutex& mutex) : lock(std::shared_lock{mutex}) {
            g_redirectionResourcePathsMutexLocked = true;
        }

        ~Result() {
            if (lock) {
                g_redirectionResourcePathsMutexLocked = false;
            }
        }

       private:
        std::optional<std::shared_lock<std::shared_mutex>> lock;
    };

    if (g_redirectionResourcePathsMutexLocked) {
        return Result{};
    }

    return Result{g_redirectionResourcePathsMutex};
}

bool DevicePathToDosPath(const WCHAR* device_path,
                         WCHAR* dos_path,
                         size_t dos_path_size) {
    WCHAR drive_strings[MAX_PATH];
    if (!GetLogicalDriveStrings(ARRAYSIZE(drive_strings), drive_strings)) {
        return false;
    }

    // Drive strings are stored as a set of null terminated strings, with an
    // extra null after the last string. Each drive string is of the form "C:\".
    // We convert it to the form "C:", which is the format expected by
    // QueryDosDevice().
    WCHAR drive_colon[3] = L" :";
    for (const WCHAR* next_drive_letter = drive_strings; *next_drive_letter;
         next_drive_letter += wcslen(next_drive_letter) + 1) {
        // Dos device of the form "C:".
        *drive_colon = *next_drive_letter;
        WCHAR device_name[MAX_PATH];
        if (!QueryDosDevice(drive_colon, device_name, ARRAYSIZE(device_name))) {
            continue;
        }

        size_t name_length = wcslen(device_name);
        if (_wcsnicmp(device_path, device_name, name_length) == 0) {
            size_t dos_path_size_required =
                2 + wcslen(device_path + name_length) + 1;
            if (dos_path_size < dos_path_size_required) {
                return false;
            }

            // Construct DOS path.
            wcscpy(dos_path, drive_colon);
            wcscat(dos_path, device_path + name_length);
            return true;
        }
    }

    return false;
}

HMODULE GetRedirectedModule(std::wstring_view fileName) {
    std::wstring fileNameUpper{fileName};
    LCMapStringEx(LOCALE_NAME_USER_DEFAULT, LCMAP_UPPERCASE, &fileNameUpper[0],
                  static_cast<int>(fileNameUpper.length()), &fileNameUpper[0],
                  static_cast<int>(fileNameUpper.length()), nullptr, nullptr,
                  0);

    {
        std::shared_lock lock{g_redirectionResourceModulesMutex};
        const auto it = g_redirectionResourceModules.find(fileNameUpper);
        if (it != g_redirectionResourceModules.end()) {
            return it->second;
        }
    }

    HINSTANCE module = LoadLibraryEx(
        fileNameUpper.c_str(), nullptr,
        LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE);
    if (!module) {
        DWORD dwError = GetLastError();
        Wh_Log(L"LoadLibraryEx failed with error %u", dwError);
        return nullptr;
    }

    {
        std::unique_lock lock{g_redirectionResourceModulesMutex};
        const auto [it, inserted] =
            g_redirectionResourceModules.try_emplace(fileNameUpper, module);
        if (!inserted) {
            FreeLibrary(module);
            return it->second;
        }
    }

    return module;
}

void FreeAndClearRedirectedModules() {
    std::unique_lock resourcePathsLock{g_redirectionResourcePathsMutex};
    std::unordered_map<std::wstring, HMODULE> modules;

    {
        std::unique_lock lock{g_redirectionResourceModulesMutex};
        modules.swap(g_redirectionResourceModules);
    }

    for (const auto& it : modules) {
        FreeLibrary(it.second);
    }
}

template <typename T>
bool RedirectFileName(DWORD c,
                      const T* fileName,
                      std::function<void()> beforeFirstRedirectionFunction,
                      std::function<bool(const T*)> redirectFunction) {
    if (!fileName) {
        Wh_Log(L"[%u] Error, nullptr file name, falling back to original", c);
        return false;
    }

    std::basic_string<T> fileNameUpper{fileName};
    (chooseAW<T, LCMapStringA, LCMapStringW>())(
        LOCALE_USER_DEFAULT, LCMAP_UPPERCASE, &fileNameUpper[0],
        static_cast<int>(fileNameUpper.length()), &fileNameUpper[0],
        static_cast<int>(fileNameUpper.length()));

    bool triedRedirection = false;

    {
        auto lock{RedirectionResourcePathsMutexSharedLock()};

        const auto& redirectionResourcePaths =
            *(chooseAW<T, &g_redirectionResourcePathsA,
                       &g_redirectionResourcePaths>());
        if (const auto it = redirectionResourcePaths.find(fileNameUpper);
            it != redirectionResourcePaths.end()) {
            const auto& redirects = it->second;
            for (const auto& redirect : redirects) {
                if (!triedRedirection) {
                    beforeFirstRedirectionFunction();
                    triedRedirection = true;
                }

                Wh_Log(L"[%u] Trying %s", c, StrToW(redirect.c_str()).p);

                if (redirectFunction(redirect.c_str())) {
                    return true;
                }
            }
        }

        const auto& redirectionResourcePathPatterns =
            *(chooseAW<T, &g_redirectionResourcePathPatternsA,
                       &g_redirectionResourcePathPatterns>());
        for (const auto& [pattern, redirect] :
             redirectionResourcePathPatterns) {
            if (!strmatch(pattern.data(), pattern.size(), fileNameUpper.data(),
                          fileNameUpper.size())) {
                continue;
            }

            if (!triedRedirection) {
                beforeFirstRedirectionFunction();
                triedRedirection = true;
            }

            Wh_Log(L"[%u] Trying %s", c, StrToW(redirect.c_str()).p);

            if (redirectFunction(redirect.c_str())) {
                return true;
            }
        }
    }

    if (triedRedirection) {
        Wh_Log(L"[%u] No redirection succeeded, falling back to original", c);
    }

    return false;
}

bool RedirectModule(DWORD c,
                    HINSTANCE hInstance,
                    std::function<void()> beforeFirstRedirectionFunction,
                    std::function<bool(HINSTANCE)> redirectFunction) {
    WCHAR szFileName[MAX_PATH];
    DWORD fileNameLen;
    if ((ULONG_PTR)hInstance & 3) {
        WCHAR szNtFileName[MAX_PATH * 2];

        if (!GetMappedFileName(GetCurrentProcess(), (void*)hInstance,
                               szNtFileName, ARRAYSIZE(szNtFileName))) {
            DWORD dwError = GetLastError();
            Wh_Log(L"[%u] GetMappedFileName(%p) failed with error %u", c,
                   hInstance, dwError);
            return false;
        }

        if (!DevicePathToDosPath(szNtFileName, szFileName,
                                 ARRAYSIZE(szFileName))) {
            Wh_Log(L"[%u] DevicePathToDosPath failed", c);
            return false;
        }

        fileNameLen = wcslen(szFileName);
    } else {
        fileNameLen =
            GetModuleFileName(hInstance, szFileName, ARRAYSIZE(szFileName));
        switch (fileNameLen) {
            case 0: {
                DWORD dwError = GetLastError();
                Wh_Log(L"[%u] GetModuleFileName(%p) failed with error %u", c,
                       hInstance, dwError);
                return false;
            }

            case ARRAYSIZE(szFileName):
                Wh_Log(L"[%u] GetModuleFileName(%p) failed, name too long", c,
                       hInstance);
                return false;
        }
    }

    Wh_Log(L"[%u] Module: %s", c, szFileName);

    LCMapStringEx(LOCALE_NAME_USER_DEFAULT, LCMAP_UPPERCASE, &szFileName[0],
                  fileNameLen, &szFileName[0], fileNameLen, nullptr, nullptr,
                  0);

    bool triedRedirection = false;

    {
        auto lock{RedirectionResourcePathsMutexSharedLock()};

        if (const auto it = g_redirectionResourcePaths.find(szFileName);
            it != g_redirectionResourcePaths.end()) {
            const auto& redirects = it->second;
            for (const auto& redirect : redirects) {
                if (!triedRedirection) {
                    beforeFirstRedirectionFunction();
                    triedRedirection = true;
                }

                Wh_Log(L"[%u] Trying %s", c, redirect.c_str());

                HINSTANCE hInstanceRedirect = GetRedirectedModule(redirect);
                if (!hInstanceRedirect) {
                    Wh_Log(L"[%u] GetRedirectedModule failed", c);
                    continue;
                }

                if (redirectFunction(hInstanceRedirect)) {
                    return true;
                }
            }
        }

        for (const auto& [pattern, redirect] :
             g_redirectionResourcePathPatterns) {
            if (!strmatch(pattern.data(), pattern.size(), szFileName,
                          fileNameLen)) {
                continue;
            }

            if (!triedRedirection) {
                beforeFirstRedirectionFunction();
                triedRedirection = true;
            }

            Wh_Log(L"[%u] Trying %s", c, redirect.c_str());

            HINSTANCE hInstanceRedirect = GetRedirectedModule(redirect);
            if (!hInstanceRedirect) {
                Wh_Log(L"[%u] GetRedirectedModule failed", c);
                continue;
            }

            if (redirectFunction(hInstanceRedirect)) {
                return true;
            }
        }
    }

    if (triedRedirection) {
        Wh_Log(L"[%u] No redirection succeeded, falling back to original", c);
    }

    return false;
}

typedef struct {
    int targetIndex;
    int currentIndex;
    LPWSTR foundName;
} ENUMICONCTX;

BOOL CALLBACK EnumIconsProc(HMODULE hModule,
                            LPCWSTR lpszType,
                            LPWSTR lpszName,
                            LONG_PTR lParam) {
    ENUMICONCTX* ctx = (ENUMICONCTX*)lParam;

    if (ctx->currentIndex == ctx->targetIndex) {
        ctx->foundName = lpszName;
        return FALSE;  // Stop enumeration.
    }

    ctx->currentIndex++;
    return TRUE;  // Continue.
}

LPWSTR GetIconGroupNameByIndex(HMODULE hModule, int index) {
    ENUMICONCTX ctx = {
        .targetIndex = index,
        .currentIndex = 0,
        .foundName = nullptr,
    };
    EnumResourceNames(hModule, RT_GROUP_ICON, EnumIconsProc, (LONG_PTR)&ctx);
    return ctx.foundName;
}

typedef struct {
    LPCWSTR targetName;
    int currentIndex;
    int foundIndex;
} ENUMICONBYNAMECTX;

BOOL CALLBACK EnumIconsByNameProc(HMODULE hModule,
                                  LPCWSTR lpszType,
                                  LPWSTR lpszName,
                                  LONG_PTR lParam) {
    ENUMICONBYNAMECTX* ctx = (ENUMICONBYNAMECTX*)lParam;

    // Only compare string names, skip integer resource IDs.
    if (!IS_INTRESOURCE(lpszName)) {
        if (wcscmp(lpszName, ctx->targetName) == 0) {
            ctx->foundIndex = ctx->currentIndex;
            return FALSE;  // Stop enumeration.
        }
    }

    ctx->currentIndex++;
    return TRUE;  // Continue.
}

int GetIconIndexByGroupName(HMODULE hModule, LPCWSTR name) {
    ENUMICONBYNAMECTX ctx = {
        .targetName = name,
        .currentIndex = 0,
        .foundIndex = -1,
    };
    EnumResourceNames(hModule, RT_GROUP_ICON, EnumIconsByNameProc,
                      (LONG_PTR)&ctx);
    return ctx.foundIndex;
}

using PrivateExtractIconsW_t = decltype(&PrivateExtractIconsW);
PrivateExtractIconsW_t PrivateExtractIconsW_Original;
UINT WINAPI PrivateExtractIconsW_Hook(LPCWSTR szFileName,
                                      int nIconIndex,
                                      int cxIcon,
                                      int cyIcon,
                                      HICON* phicon,
                                      UINT* piconid,
                                      UINT nIcons,
                                      UINT flags) {
    auto resOp = resourceOperationCountScope();
    DWORD c = ++g_operationCounter;

    Wh_Log(L"[%u] > Icon index: %d, file name: %s", c, nIconIndex, szFileName);

    UINT result;

    bool redirected = RedirectFileName<WCHAR>(
        c, szFileName,
        [&]() {
            Wh_Log(L"[%u] cxIcon: %d, %d", c, LOWORD(cxIcon), HIWORD(cxIcon));
            Wh_Log(L"[%u] cyIcon: %d, %d", c, LOWORD(cyIcon), HIWORD(cyIcon));
            Wh_Log(L"[%u] phicon: %s", c, phicon ? L"out_ptr" : L"nullptr");
            Wh_Log(L"[%u] piconid: %s", c, piconid ? L"out_ptr" : L"nullptr");
            Wh_Log(L"[%u] nIcons: %u", c, nIcons);
            Wh_Log(L"[%u] flags: 0x%08X", c, flags);
        },
        [&](PCWSTR fileNameRedirect) {
            // nIconIndex can be either:
            // * Negative: the icon id
            // * Non-negative: The icon index (0 for first icon, etc.)
            //
            // Using the non-negative value for the redirected file is
            // problematic as it might contain only part of the icons.
            // Therefore, convert it to an id before proceeding.
            int iconId = nIconIndex;
            if (iconId >= 0) {
                HMODULE module = LoadLibraryEx(szFileName, nullptr,
                                               LOAD_LIBRARY_AS_DATAFILE);
                if (module) {
                    bool resolved = false;

                    LPWSTR iconGroupName =
                        GetIconGroupNameByIndex(module, iconId);
                    if (!iconGroupName) {
                        Wh_Log(L"[%u] Failed to get icon group name", c);
                    } else if (!IS_INTRESOURCE(iconGroupName)) {
                        Wh_Log(L"[%u] Icon group name is not an id: %s", c,
                               iconGroupName);

                        // Load redirect file and find the string name's index.
                        HMODULE redirectModule =
                            LoadLibraryEx(fileNameRedirect, nullptr,
                                          LOAD_LIBRARY_AS_DATAFILE);
                        if (redirectModule) {
                            int redirectIndex = GetIconIndexByGroupName(
                                redirectModule, iconGroupName);
                            FreeLibrary(redirectModule);

                            if (redirectIndex >= 0) {
                                iconId = redirectIndex;
                                resolved = true;
                                Wh_Log(
                                    L"[%u] Found icon group name in redirect "
                                    L"file at index %d",
                                    c, redirectIndex);
                            } else {
                                Wh_Log(
                                    L"[%u] Icon group name not found in "
                                    L"redirect file",
                                    c);
                            }
                        } else {
                            Wh_Log(
                                L"[%u] Failed to load redirect file for icon "
                                L"name lookup",
                                c);
                        }
                    } else {
                        iconId = -(WORD)(ULONG_PTR)iconGroupName;
                        resolved = true;
                        Wh_Log(L"[%u] Using icon group id %d", c, -iconId);
                    }

                    FreeLibrary(module);

                    if (!resolved) {
                        if (iconId == 0) {
                            // Allow using index 0 as fallback for convenience,
                            // which likely means that the exact match isn't
                            // that important and the first icon will do.
                            Wh_Log(L"[%u] Using icon index 0 as fallback", c);
                        } else {
                            Wh_Log(
                                L"[%u] Failed to resolve icon group from "
                                L"original index",
                                c);
                            return false;
                        }
                    }
                } else {
                    // May happen e.g. for .ico files.
                    Wh_Log(L"[%u] Failed to get module handle", c);
                }
            }

            if (phicon) {
                std::fill_n(phicon, nIcons, nullptr);
            }

            result = PrivateExtractIconsW_Original(fileNameRedirect, iconId,
                                                   cxIcon, cyIcon, phicon,
                                                   piconid, nIcons, flags);
            if (result != 0xFFFFFFFF && result != 0) {
                // In case multiple icons are requested and the custom resource
                // only overrides some of them, we'd ideally like to return a
                // combined result. Unfortunately, that's not trivial to
                // implement, so return the original icons in this case.
                //
                // An example where multiple icons are requested is the Change
                // Icon dialog in shortcut file properties. If a partial result
                // is returned, only the returned icons are displayed.
                bool multipleIcons = nIcons > (HIWORD(cxIcon) ? 2 : 1);
                bool partialResult = result < nIcons;
                UINT multipleIconsOriginalCount = 0;
                if (multipleIcons && partialResult) {
                    multipleIconsOriginalCount = PrivateExtractIconsW_Original(
                        szFileName, nIconIndex, cxIcon, cyIcon, nullptr,
                        nullptr, nIcons, flags);
                }

                if (result < multipleIconsOriginalCount) {
                    Wh_Log(
                        L"[%u] Got less icons than the original file has: %u "
                        L"vs. %u, replacing redirection with the original "
                        L"icons",
                        c, result, multipleIconsOriginalCount);

                    if (phicon) {
                        for (UINT i = 0; i < nIcons; i++) {
                            if (phicon[i]) {
                                DestroyIcon(phicon[i]);
                                phicon[i] = nullptr;
                            }
                        }
                    }

                    result = PrivateExtractIconsW_Original(
                        szFileName, nIconIndex, cxIcon, cyIcon, phicon, piconid,
                        nIcons, flags);
                }

                Wh_Log(L"[%u] Redirected successfully, result: %u", c, result);
                return true;
            }

            // If `LR_EXACTSIZEONLY` is used and the exact size is missing, the
            // function will return no icons. If the replacement file doesn't
            // have this icon, we want to fall back to the original file, but if
            // it has other sizes, we prefer to return an empty result,
            // hopefully the target app will try other sizes in this case.
            if (result == 0 && phicon && (flags & LR_EXACTSIZEONLY)) {
                HICON testIcon = nullptr;
                UINT testIconId;
                UINT testResult = PrivateExtractIconsW_Original(
                    fileNameRedirect, iconId, LOWORD(cxIcon), LOWORD(cyIcon),
                    &testIcon, &testIconId, 1, flags & ~LR_EXACTSIZEONLY);

                if (testIcon) {
                    DestroyIcon(testIcon);
                    testIcon = nullptr;
                }

                if (testResult > 0) {
                    Wh_Log(
                        L"[%u] Redirected successfully with an empty result: "
                        L"%u",
                        c, result);
                    return true;
                }
            }

            // If there is no exact match the API can return 0 but phicon[0] set
            // to a valid hicon. In that case destroy the icon and reset the
            // entry.
            // https://github.com/microsoft/terminal/blob/6d0342f0bb31bf245843411c6781d6d5399ff651/src/interactivity/win32/icon.cpp#L178
            if (phicon) {
                for (UINT i = 0; i < nIcons; i++) {
                    if (phicon[i]) {
                        DestroyIcon(phicon[i]);
                        phicon[i] = nullptr;
                    }
                }
            }

            Wh_Log(L"[%u] Redirection failed, result: %u", c, result);
            return false;
        });
    if (redirected) {
        return result;
    }

    return PrivateExtractIconsW_Original(szFileName, nIconIndex, cxIcon, cyIcon,
                                         phicon, piconid, nIcons, flags);
}

template <auto* Original, typename T>
HANDLE LoadImageAW_Hook(HINSTANCE hInst,
                        const T* name,
                        UINT type,
                        int cx,
                        int cy,
                        UINT fuLoad) {
    auto resOp = resourceOperationCountScope();
    DWORD c = ++g_operationCounter;

    PCWSTR typeClarification = L"";
    switch (type) {
        case IMAGE_BITMAP:
            typeClarification = L" (bitmap)";
            break;
        case IMAGE_ICON:
            typeClarification = L" (icon)";
            break;
        case IMAGE_CURSOR:
            typeClarification = L" (cursor)";
            break;
    }

    WCHAR prefix[64];
    swprintf_s(prefix, L"[%u] > %c, type: %u%s", c, chooseAW<T, L'A', L'W'>(),
               type, typeClarification);

    if (!hInst) {
        if (fuLoad & LR_LOADFROMFILE) {
            Wh_Log(L"%s, file name: %s", prefix, StrToW(name).p);
        } else {
            Wh_Log(L"%s, resource identifier: %zu", prefix, (ULONG_PTR)name);
        }
    } else if (IS_INTRESOURCE(name)) {
        Wh_Log(L"%s, resource number: %u", prefix, (DWORD)(ULONG_PTR)name);
    } else {
        Wh_Log(L"%s, resource name: %s", prefix, StrToW(name).p);
    }

    HANDLE result;
    bool redirected;
    DWORD lastError = 0;

    auto beforeFirstRedirectionFunction = [&]() {
        Wh_Log(L"[%u] Width: %d", c, cx);
        Wh_Log(L"[%u] Height: %d", c, cy);
        Wh_Log(L"[%u] Flags: 0x%08X", c, fuLoad);
    };

    // If `LR_EXACTSIZEONLY` is used and the exact size is missing, the function
    // will return no result. If the replacement doesn't have this resource, we
    // want to fall back to the original, but if it has other sizes, we prefer
    // to return an error, hopefully the target app will try other sizes in this
    // case.
    auto handleExactSizeOnlyMiss =
        [&](DWORD dwError, std::function<HANDLE(UINT)> loadFunc) -> bool {
        if (!(fuLoad & LR_EXACTSIZEONLY) ||
            (type != IMAGE_BITMAP && type != IMAGE_ICON &&
             type != IMAGE_CURSOR)) {
            return false;
        }

        HANDLE testResult = loadFunc(fuLoad & ~LR_EXACTSIZEONLY);
        if (!testResult) {
            return false;
        }

        if (!(fuLoad & LR_SHARED)) {
            if (type == IMAGE_BITMAP) {
                DeleteObject(testResult);
            } else if (type == IMAGE_ICON) {
                DestroyIcon((HICON)testResult);
            } else {
                DestroyCursor((HCURSOR)testResult);
            }
        }

        result = nullptr;
        lastError = dwError;
        Wh_Log(L"[%u] Redirected successfully with error for exact size", c);
        return true;
    };

    if (!hInst && (fuLoad & LR_LOADFROMFILE)) {
        redirected = RedirectFileName<T>(
            c, name, std::move(beforeFirstRedirectionFunction),
            [&](const T* fileNameRedirect) {
                result =
                    (*Original)(hInst, fileNameRedirect, type, cx, cy, fuLoad);
                if (result) {
                    Wh_Log(L"[%u] Redirected successfully", c);
                    return true;
                }

                DWORD dwError = GetLastError();

                if (handleExactSizeOnlyMiss(dwError, [&](UINT flags) {
                        return (*Original)(hInst, fileNameRedirect, type, cx,
                                           cy, flags);
                    })) {
                    return true;
                }

                Wh_Log(L"[%u] LoadImage failed with error %u", c, dwError);
                return false;
            });
    } else {
        redirected = RedirectModule(
            c, hInst, std::move(beforeFirstRedirectionFunction),
            [&](HINSTANCE hInstanceRedirect) {
                result =
                    (*Original)(hInstanceRedirect, name, type, cx, cy, fuLoad);
                if (result) {
                    Wh_Log(L"[%u] Redirected successfully", c);
                    return true;
                }

                DWORD dwError = GetLastError();

                if (handleExactSizeOnlyMiss(dwError, [&](UINT flags) {
                        return (*Original)(hInstanceRedirect, name, type, cx,
                                           cy, flags);
                    })) {
                    return true;
                }

                Wh_Log(L"[%u] LoadImage failed with error %u", c, dwError);
                return false;
            });
    }

    if (redirected) {
        if (!result) {
            SetLastError(lastError);
        }
        return result;
    }

    return (*Original)(hInst, name, type, cx, cy, fuLoad);
}

using LoadImageA_t = decltype(&LoadImageA);
LoadImageA_t LoadImageA_Original;
HANDLE WINAPI LoadImageA_Hook(HINSTANCE hInst,
                              LPCSTR name,
                              UINT type,
                              int cx,
                              int cy,
                              UINT fuLoad) {
    return LoadImageAW_Hook<&LoadImageA_Original>(hInst, name, type, cx, cy,
                                                  fuLoad);
}

using LoadImageW_t = decltype(&LoadImageW);
LoadImageW_t LoadImageW_Original;
HANDLE WINAPI LoadImageW_Hook(HINSTANCE hInst,
                              LPCWSTR name,
                              UINT type,
                              int cx,
                              int cy,
                              UINT fuLoad) {
    return LoadImageAW_Hook<&LoadImageW_Original>(hInst, name, type, cx, cy,
                                                  fuLoad);
}

template <auto* Original, typename T>
HICON LoadIconAW_Hook(HINSTANCE hInstance, const T* lpIconName) {
    auto resOp = resourceOperationCountScope();
    DWORD c = ++g_operationCounter;

    WCHAR prefix[64];
    swprintf_s(prefix, L"[%u] > %c", c, chooseAW<T, L'A', L'W'>());

    if (!hInstance) {
        Wh_Log(L"%s, resource identifier: %zu", prefix, (ULONG_PTR)lpIconName);
    } else if (IS_INTRESOURCE(lpIconName)) {
        Wh_Log(L"%s, resource number: %u", prefix,
               (DWORD)(ULONG_PTR)lpIconName);
    } else {
        Wh_Log(L"%s, resource name: %s", prefix, StrToW(lpIconName).p);
    }

    HICON result;

    bool redirected = RedirectModule(
        c, hInstance, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            result = (*Original)(hInstanceRedirect, lpIconName);
            if (result) {
                Wh_Log(L"[%u] Redirected successfully", c);
                return true;
            }

            DWORD dwError = GetLastError();
            Wh_Log(L"[%u] LoadIcon failed with error %u", c, dwError);
            return false;
        });
    if (redirected) {
        return result;
    }

    return (*Original)(hInstance, lpIconName);
}

using LoadIconA_t = decltype(&LoadIconA);
LoadIconA_t LoadIconA_Original;
HICON WINAPI LoadIconA_Hook(HINSTANCE hInstance, LPCSTR lpIconName) {
    return LoadIconAW_Hook<&LoadIconA_Original>(hInstance, lpIconName);
}

using LoadIconW_t = decltype(&LoadIconW);
LoadIconW_t LoadIconW_Original;
HICON WINAPI LoadIconW_Hook(HINSTANCE hInstance, LPCWSTR lpIconName) {
    return LoadIconAW_Hook<&LoadIconW_Original>(hInstance, lpIconName);
}

template <auto* Original, typename T>
HCURSOR LoadCursorAW_Hook(HINSTANCE hInstance, const T* lpCursorName) {
    auto resOp = resourceOperationCountScope();
    DWORD c = ++g_operationCounter;

    WCHAR prefix[64];
    swprintf_s(prefix, L"[%u] > %c", c, chooseAW<T, L'A', L'W'>());

    if (!hInstance) {
        Wh_Log(L"%s, resource identifier: %zu", prefix,
               (ULONG_PTR)lpCursorName);
    } else if (IS_INTRESOURCE(lpCursorName)) {
        Wh_Log(L"%s, resource number: %u", prefix,
               (DWORD)(ULONG_PTR)lpCursorName);
    } else {
        Wh_Log(L"%s, resource name: %s", prefix, StrToW(lpCursorName).p);
    }

    HCURSOR result;

    bool redirected = RedirectModule(
        c, hInstance, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            result = (*Original)(hInstanceRedirect, lpCursorName);
            if (result) {
                Wh_Log(L"[%u] Redirected successfully", c);
                return true;
            }

            DWORD dwError = GetLastError();
            Wh_Log(L"[%u] LoadCursor failed with error %u", c, dwError);
            return false;
        });
    if (redirected) {
        return result;
    }

    return (*Original)(hInstance, lpCursorName);
}

using LoadCursorA_t = decltype(&LoadCursorA);
LoadCursorA_t LoadCursorA_Original;
HCURSOR WINAPI LoadCursorA_Hook(HINSTANCE hInstance, LPCSTR lpCursorName) {
    return LoadCursorAW_Hook<&LoadCursorA_Original>(hInstance, lpCursorName);
}

using LoadCursorW_t = decltype(&LoadCursorW);
LoadCursorW_t LoadCursorW_Original;
HCURSOR WINAPI LoadCursorW_Hook(HINSTANCE hInstance, LPCWSTR lpCursorName) {
    return LoadCursorAW_Hook<&LoadCursorW_Original>(hInstance, lpCursorName);
}

template <auto* Original, typename T>
HBITMAP LoadBitmapAW_Hook(HINSTANCE hInstance, const T* lpBitmapName) {
    auto resOp = resourceOperationCountScope();
    DWORD c = ++g_operationCounter;

    WCHAR prefix[64];
    swprintf_s(prefix, L"[%u] > %c", c, chooseAW<T, L'A', L'W'>());

    if (!hInstance) {
        Wh_Log(L"%s, resource identifier: %zu", prefix,
               (ULONG_PTR)lpBitmapName);
    } else if (IS_INTRESOURCE(lpBitmapName)) {
        Wh_Log(L"%s, resource number: %u", prefix,
               (DWORD)(ULONG_PTR)lpBitmapName);
    } else {
        Wh_Log(L"%s, resource name: %s", prefix, StrToW(lpBitmapName).p);
    }

    HBITMAP result;

    bool redirected = RedirectModule(
        c, hInstance, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            result = (*Original)(hInstanceRedirect, lpBitmapName);
            if (result) {
                Wh_Log(L"[%u] Redirected successfully", c);
                return true;
            }

            DWORD dwError = GetLastError();
            Wh_Log(L"[%u] LoadBitmap failed with error %u", c, dwError);
            return false;
        });
    if (redirected) {
        return result;
    }

    return (*Original)(hInstance, lpBitmapName);
}

using LoadBitmapA_t = decltype(&LoadBitmapA);
LoadBitmapA_t LoadBitmapA_Original;
HBITMAP WINAPI LoadBitmapA_Hook(HINSTANCE hInstance, LPCSTR lpBitmapName) {
    return LoadBitmapAW_Hook<&LoadBitmapA_Original>(hInstance, lpBitmapName);
}

using LoadBitmapW_t = decltype(&LoadBitmapW);
LoadBitmapW_t LoadBitmapW_Original;
HBITMAP WINAPI LoadBitmapW_Hook(HINSTANCE hInstance, LPCWSTR lpBitmapName) {
    return LoadBitmapAW_Hook<&LoadBitmapW_Original>(hInstance, lpBitmapName);
}

template <auto* Original, typename T>
HMENU LoadMenuAW_Hook(HINSTANCE hInstance, const T* lpMenuName) {
    auto resOp = resourceOperationCountScope();
    DWORD c = ++g_operationCounter;

    WCHAR prefix[64];
    swprintf_s(prefix, L"[%u] > %c", c, chooseAW<T, L'A', L'W'>());

    if (IS_INTRESOURCE(lpMenuName)) {
        Wh_Log(L"%s, resource number: %u", prefix,
               (DWORD)(ULONG_PTR)lpMenuName);
    } else {
        Wh_Log(L"%s, resource name: %s", prefix, StrToW(lpMenuName).p);
    }

    HMENU result;

    bool redirected = RedirectModule(
        c, hInstance, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            result = (*Original)(hInstanceRedirect, lpMenuName);
            if (result) {
                Wh_Log(L"[%u] Redirected successfully", c);
                return true;
            }

            DWORD dwError = GetLastError();
            Wh_Log(L"[%u] LoadMenu failed with error %u", c, dwError);
            return false;
        });
    if (redirected) {
        return result;
    }

    return (*Original)(hInstance, lpMenuName);
}

using LoadMenuA_t = decltype(&LoadMenuA);
LoadMenuA_t LoadMenuA_Original;
HMENU WINAPI LoadMenuA_Hook(HINSTANCE hInstance, LPCSTR lpMenuName) {
    return LoadMenuAW_Hook<&LoadMenuA_Original>(hInstance, lpMenuName);
}

using LoadMenuW_t = decltype(&LoadMenuW);
LoadMenuW_t LoadMenuW_Original;
HMENU WINAPI LoadMenuW_Hook(HINSTANCE hInstance, LPCWSTR lpMenuName) {
    return LoadMenuAW_Hook<&LoadMenuW_Original>(hInstance, lpMenuName);
}

template <auto* Original, typename T>
INT_PTR DialogBoxParamAW_Hook(HINSTANCE hInstance,
                              const T* lpTemplateName,
                              HWND hWndParent,
                              DLGPROC lpDialogFunc,
                              LPARAM dwInitParam) {
    auto resOp = resourceOperationCountScope();
    DWORD c = ++g_operationCounter;

    WCHAR prefix[64];
    swprintf_s(prefix, L"[%u] > %c", c, chooseAW<T, L'A', L'W'>());

    if (IS_INTRESOURCE(lpTemplateName)) {
        Wh_Log(L"%s, resource number: %u", prefix,
               (DWORD)(ULONG_PTR)lpTemplateName);
    } else {
        Wh_Log(L"%s, resource name: %s", prefix, StrToW(lpTemplateName).p);
    }

    INT_PTR result;

    bool redirected = RedirectModule(
        c, hInstance, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            // For other redirected functions, we check whether the function
            // succeeded. If it didn't, we try another redirection or fall back
            // to the original file.
            //
            // In this case, there's no reliable way to find out whether
            // DialogBoxParamW failed, since any value can be returned.
            // Therefore, only make sure that the dialog resource exists.
            if (!(chooseAW<T, FindResourceExA, FindResourceExW>())(
                    hInstanceRedirect, (T*)RT_DIALOG, lpTemplateName, 0)) {
                Wh_Log(L"[%u] Resource not found", c);
                return false;
            }

            Wh_Log(L"[%u] Redirected successfully", c);
            result = (*Original)(hInstanceRedirect, lpTemplateName, hWndParent,
                                 lpDialogFunc, dwInitParam);
            return true;
        });
    if (redirected) {
        return result;
    }

    return (*Original)(hInstance, lpTemplateName, hWndParent, lpDialogFunc,
                       dwInitParam);
}

using DialogBoxParamA_t = decltype(&DialogBoxParamA);
DialogBoxParamA_t DialogBoxParamA_Original;
INT_PTR WINAPI DialogBoxParamA_Hook(HINSTANCE hInstance,
                                    LPCSTR lpTemplateName,
                                    HWND hWndParent,
                                    DLGPROC lpDialogFunc,
                                    LPARAM dwInitParam) {
    return DialogBoxParamAW_Hook<&DialogBoxParamA_Original>(
        hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

using DialogBoxParamW_t = decltype(&DialogBoxParamW);
DialogBoxParamW_t DialogBoxParamW_Original;
INT_PTR WINAPI DialogBoxParamW_Hook(HINSTANCE hInstance,
                                    LPCWSTR lpTemplateName,
                                    HWND hWndParent,
                                    DLGPROC lpDialogFunc,
                                    LPARAM dwInitParam) {
    return DialogBoxParamAW_Hook<&DialogBoxParamW_Original>(
        hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

template <auto* Original, typename T>
HWND CreateDialogParamAW_Hook(HINSTANCE hInstance,
                              const T* lpTemplateName,
                              HWND hWndParent,
                              DLGPROC lpDialogFunc,
                              LPARAM dwInitParam) {
    auto resOp = resourceOperationCountScope();
    DWORD c = ++g_operationCounter;

    WCHAR prefix[64];
    swprintf_s(prefix, L"[%u] > %c", c, chooseAW<T, L'A', L'W'>());

    if (IS_INTRESOURCE(lpTemplateName)) {
        Wh_Log(L"%s, resource number: %u", prefix,
               (DWORD)(ULONG_PTR)lpTemplateName);
    } else {
        Wh_Log(L"%s, resource name: %s", prefix, StrToW(lpTemplateName).p);
    }

    HWND result;

    bool redirected = RedirectModule(
        c, hInstance, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            result = (*Original)(hInstanceRedirect, lpTemplateName, hWndParent,
                                 lpDialogFunc, dwInitParam);
            if (result) {
                Wh_Log(L"[%u] Redirected successfully", c);
                return true;
            }

            DWORD dwError = GetLastError();
            Wh_Log(L"[%u] CreateDialogParam failed with error %u", c, dwError);
            return false;
        });
    if (redirected) {
        return result;
    }

    return (*Original)(hInstance, lpTemplateName, hWndParent, lpDialogFunc,
                       dwInitParam);
}

using CreateDialogParamA_t = decltype(&CreateDialogParamA);
CreateDialogParamA_t CreateDialogParamA_Original;
HWND WINAPI CreateDialogParamA_Hook(HINSTANCE hInstance,
                                    LPCSTR lpTemplateName,
                                    HWND hWndParent,
                                    DLGPROC lpDialogFunc,
                                    LPARAM dwInitParam) {
    return CreateDialogParamAW_Hook<&CreateDialogParamA_Original>(
        hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

using CreateDialogParamW_t = decltype(&CreateDialogParamW);
CreateDialogParamW_t CreateDialogParamW_Original;
HWND WINAPI CreateDialogParamW_Hook(HINSTANCE hInstance,
                                    LPCWSTR lpTemplateName,
                                    HWND hWndParent,
                                    DLGPROC lpDialogFunc,
                                    LPARAM dwInitParam) {
    return CreateDialogParamAW_Hook<&CreateDialogParamW_Original>(
        hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

template <auto* Original, typename T>
int LoadStringAW_Hook(HINSTANCE hInstance,
                      UINT uID,
                      T* lpBuffer,
                      int cchBufferMax) {
    auto resOp = resourceOperationCountScope();
    DWORD c = ++g_operationCounter;

    WCHAR prefix[64];
    swprintf_s(prefix, L"[%u] > %c", c, chooseAW<T, L'A', L'W'>());

    Wh_Log(L"%s, string number: %u", prefix, uID);

    int result;

    bool redirected = RedirectModule(
        c, hInstance, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            result =
                (*Original)(hInstanceRedirect, uID, lpBuffer, cchBufferMax);
            if (result) {
                Wh_Log(L"[%u] Redirected successfully", c);
                return true;
            }

            DWORD dwError = GetLastError();
            Wh_Log(L"[%u] LoadString failed with error %u", c, dwError);
            return false;
        });
    if (redirected) {
        return result;
    }

    return (*Original)(hInstance, uID, lpBuffer, cchBufferMax);
}

using LoadStringA_t = decltype(&LoadStringA);
LoadStringA_t LoadStringA_u_Original;
int WINAPI LoadStringA_u_Hook(HINSTANCE hInstance,
                              UINT uID,
                              LPSTR lpBuffer,
                              int cchBufferMax) {
    return LoadStringAW_Hook<&LoadStringA_u_Original>(hInstance, uID, lpBuffer,
                                                      cchBufferMax);
}

using LoadStringW_t = decltype(&LoadStringW);
LoadStringW_t LoadStringW_u_Original;
int WINAPI LoadStringW_u_Hook(HINSTANCE hInstance,
                              UINT uID,
                              LPWSTR lpBuffer,
                              int cchBufferMax) {
    return LoadStringAW_Hook<&LoadStringW_u_Original>(hInstance, uID, lpBuffer,
                                                      cchBufferMax);
}

LoadStringA_t LoadStringA_k_Original;
int WINAPI LoadStringA_k_Hook(HINSTANCE hInstance,
                              UINT uID,
                              LPSTR lpBuffer,
                              int cchBufferMax) {
    return LoadStringAW_Hook<&LoadStringA_k_Original>(hInstance, uID, lpBuffer,
                                                      cchBufferMax);
}

LoadStringW_t LoadStringW_k_Original;
int WINAPI LoadStringW_k_Hook(HINSTANCE hInstance,
                              UINT uID,
                              LPWSTR lpBuffer,
                              int cchBufferMax) {
    return LoadStringAW_Hook<&LoadStringW_k_Original>(hInstance, uID, lpBuffer,
                                                      cchBufferMax);
}

template <auto* Original, typename T>
HRSRC FindResourceExAW_Hook(HMODULE hModule,
                            const T* lpType,
                            const T* lpName,
                            WORD wLanguage) {
    DWORD c = ++g_operationCounter;

    WCHAR prefix[64];
    swprintf_s(prefix, L"[%u] > %c", c, chooseAW<T, L'A', L'W'>());

    auto logType = [lpType]() -> std::wstring {
        if (IS_INTRESOURCE(lpType)) {
            return std::to_wstring((DWORD)(ULONG_PTR)lpType);
        } else {
            return StrToW(lpType).p;
        }
    };

    if (IS_INTRESOURCE(lpName)) {
        Wh_Log(L"%s, resource type: %s, number: %u, language: 0x%04X", prefix,
               logType().c_str(), (DWORD)(ULONG_PTR)lpName, wLanguage);
    } else {
        Wh_Log(L"%s, resource type: %s, name: %s, language: 0x%04X", prefix,
               logType().c_str(), StrToW(lpName).p, wLanguage);
    }

    HRSRC result;

    bool redirected = RedirectModule(
        c, hModule, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            result = (*Original)(hInstanceRedirect, lpType, lpName, wLanguage);
            if (result) {
                Wh_Log(L"[%u] Redirected successfully, result=%p", c, result);
                return true;
            }

            DWORD dwError = GetLastError();
            Wh_Log(L"[%u] FindResourceEx failed with error %u", c, dwError);
            return false;
        });
    if (redirected) {
        return result;
    }

    return (*Original)(hModule, lpType, lpName, wLanguage);
}

using FindResourceExA_t = decltype(&FindResourceExA);
FindResourceExA_t FindResourceExA_Original;
HRSRC WINAPI FindResourceExA_Hook(HMODULE hModule,
                                  LPCSTR lpType,
                                  LPCSTR lpName,
                                  WORD wLanguage) {
    if (g_resourceOperationCount > 0) {
        return FindResourceExA_Original(hModule, lpType, lpName, wLanguage);
    }

    return FindResourceExAW_Hook<&FindResourceExA_Original>(hModule, lpType,
                                                            lpName, wLanguage);
}

using FindResourceExW_t = decltype(&FindResourceExW);
FindResourceExW_t FindResourceExW_Original;
HRSRC WINAPI FindResourceExW_Hook(HMODULE hModule,
                                  LPCWSTR lpType,
                                  LPCWSTR lpName,
                                  WORD wLanguage) {
    if (g_resourceOperationCount > 0) {
        return FindResourceExW_Original(hModule, lpType, lpName, wLanguage);
    }

    return FindResourceExAW_Hook<&FindResourceExW_Original>(hModule, lpType,
                                                            lpName, wLanguage);
}

bool IsResourceHandlePartOfModule(HMODULE hModule, HRSRC hResInfo) {
    if ((ULONG_PTR)hModule & 3) {
        MEMORY_BASIC_INFORMATION mbi;
        if (!VirtualQuery((void*)hModule, &mbi, sizeof(mbi))) {
            DWORD dwError = GetLastError();
            Wh_Log(L"VirtualQuery failed with error %u", dwError);
            return false;
        }

        return (void*)hResInfo >= mbi.BaseAddress &&
               (void*)hResInfo <
                   (void*)((BYTE*)mbi.BaseAddress + mbi.RegionSize);
    } else {
        HMODULE module;
        return GetModuleHandleEx(
                   GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                       GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                   (PCWSTR)hResInfo, &module) &&
               module == hModule;
    }
}

using LoadResource_t = decltype(&LoadResource);
LoadResource_t LoadResource_Original;
HGLOBAL WINAPI LoadResource_Hook(HMODULE hModule, HRSRC hResInfo) {
    if (g_resourceOperationCount > 0) {
        return LoadResource_Original(hModule, hResInfo);
    }

    DWORD c = ++g_operationCounter;

    Wh_Log(L"[%u] > hModule=%p, hResInfo=%p", c, hModule, hResInfo);

    HGLOBAL result;

    bool redirected = RedirectModule(
        c, hModule, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            if (!IsResourceHandlePartOfModule(hInstanceRedirect, hResInfo)) {
                Wh_Log(
                    L"[%u] Resource handle is not part of the module, skipping",
                    c);
                return false;
            }

            result = LoadResource_Original(hInstanceRedirect, hResInfo);
            if (result) {
                Wh_Log(L"[%u] Redirected successfully", c);
                return true;
            }

            DWORD dwError = GetLastError();
            Wh_Log(L"[%u] LoadResource failed with error %u", c, dwError);
            return false;
        });
    if (redirected) {
        return result;
    }

    return LoadResource_Original(hModule, hResInfo);
}

using SizeofResource_t = decltype(&SizeofResource);
SizeofResource_t SizeofResource_Original;
DWORD WINAPI SizeofResource_Hook(HMODULE hModule, HRSRC hResInfo) {
    if (g_resourceOperationCount > 0) {
        return SizeofResource_Original(hModule, hResInfo);
    }

    DWORD c = ++g_operationCounter;

    Wh_Log(L"[%u] > hModule=%p, hResInfo=%p", c, hModule, hResInfo);

    DWORD result;

    bool redirected = RedirectModule(
        c, hModule, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            if (!IsResourceHandlePartOfModule(hInstanceRedirect, hResInfo)) {
                Wh_Log(
                    L"[%u] Resource handle is not part of the module, skipping",
                    c);
                return false;
            }

            // Zero can be an error or the actual resource size. Check last
            // error to be sure.
            SetLastError(0);
            result = SizeofResource_Original(hInstanceRedirect, hResInfo);
            DWORD dwError = GetLastError();
            if (result || dwError == 0) {
                Wh_Log(L"[%u] Redirected successfully", c);
                return true;
            }

            Wh_Log(L"[%u] SizeofResource failed with error %u", c, dwError);
            return false;
        });
    if (redirected) {
        return result;
    }

    return SizeofResource_Original(hModule, hResInfo);
}

// https://ntdoc.m417z.com/rtlloadstring
using RtlLoadString_t = NTSTATUS(NTAPI*)(_In_ PVOID DllHandle,
                                         _In_ ULONG StringId,
                                         _In_opt_ PCWSTR StringLanguage,
                                         _In_ ULONG Flags,
                                         _Out_ PCWSTR* ReturnString,
                                         _Out_opt_ PUSHORT ReturnStringLen,
                                         _Out_writes_(ReturnLanguageLen)
                                             PWSTR ReturnLanguageName,
                                         _Inout_opt_ PULONG ReturnLanguageLen);
RtlLoadString_t RtlLoadString_Original;
HRESULT NTAPI RtlLoadString_Hook(_In_ PVOID DllHandle,
                                 _In_ ULONG StringId,
                                 _In_opt_ PCWSTR StringLanguage,
                                 _In_ ULONG Flags,
                                 _Out_ PCWSTR* ReturnString,
                                 _Out_opt_ PUSHORT ReturnStringLen,
                                 _Out_writes_(ReturnLanguageLen)
                                     PWSTR ReturnLanguageName,
                                 _Inout_opt_ PULONG ReturnLanguageLen) {
    if (g_resourceOperationCount > 0) {
        return RtlLoadString_Original(DllHandle, StringId, StringLanguage,
                                      Flags, ReturnString, ReturnStringLen,
                                      ReturnLanguageName, ReturnLanguageLen);
    }

    DWORD c = ++g_operationCounter;

    Wh_Log(L"[%u] > string number: %u", c, StringId);

    NTSTATUS result;

    bool redirected = RedirectModule(
        c, (HINSTANCE)DllHandle, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            result = RtlLoadString_Original(hInstanceRedirect, StringId,
                                            StringLanguage, Flags, ReturnString,
                                            ReturnStringLen, ReturnLanguageName,
                                            ReturnLanguageLen);
            if (result != 0) {
                Wh_Log(L"[%u] RtlLoadString failed with error %08X", c, result);
                return false;
            }

            if (!*ReturnString) {
                Wh_Log(L"[%u] RtlLoadString returned an empty string", c);
                return false;
            }

            Wh_Log(L"[%u] Redirected successfully", c);
            return true;
        });
    if (redirected) {
        return result;
    }

    return RtlLoadString_Original(DllHandle, StringId, StringLanguage, Flags,
                                  ReturnString, ReturnStringLen,
                                  ReturnLanguageName, ReturnLanguageLen);
}

using SHCreateStreamOnModuleResourceW_t = HRESULT(WINAPI*)(HMODULE hModule,
                                                           LPCWSTR pwszName,
                                                           LPCWSTR pwszType,
                                                           IStream** ppStream);
SHCreateStreamOnModuleResourceW_t SHCreateStreamOnModuleResourceW_Original;
HRESULT WINAPI SHCreateStreamOnModuleResourceW_Hook(HMODULE hModule,
                                                    LPCWSTR pwszName,
                                                    LPCWSTR pwszType,
                                                    IStream** ppStream) {
    auto resOp = resourceOperationCountScope();
    DWORD c = ++g_operationCounter;

    PCWSTR logTypeStr;
    WCHAR logTypeStrBuffer[16];
    if (IS_INTRESOURCE(pwszType)) {
        swprintf_s(logTypeStrBuffer, L"%u", (DWORD)(ULONG_PTR)pwszType);
        logTypeStr = logTypeStrBuffer;
    } else {
        logTypeStr = pwszType;
    }

    if (IS_INTRESOURCE(pwszName)) {
        Wh_Log(L"[%u] > Type: %s, resource number: %u", c, logTypeStr,
               (DWORD)(ULONG_PTR)pwszName);
    } else {
        Wh_Log(L"[%u] > Type: %s, resource name: %s", c, logTypeStr, pwszName);
    }

    HRESULT result;

    bool redirected = RedirectModule(
        c, hModule, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            result = SHCreateStreamOnModuleResourceW_Original(
                hInstanceRedirect, pwszName, pwszType, ppStream);
            if (SUCCEEDED(result)) {
                Wh_Log(L"[%u] Redirected successfully", c);
                return true;
            }

            Wh_Log(
                L"[%u] SHCreateStreamOnModuleResourceW failed with error %08X",
                c, result);
            return false;
        });
    if (redirected) {
        return result;
    }

    return SHCreateStreamOnModuleResourceW_Original(hModule, pwszName, pwszType,
                                                    ppStream);
}

void DirectUI_DUIXmlParser_SetDefaultHInstance(void* pThis, HMODULE hModule) {
    using DirectUI_DUIXmlParser_SetDefaultHInstance_t =
        void(__thiscall*)(void* pThis, HMODULE hModule);
    static DirectUI_DUIXmlParser_SetDefaultHInstance_t pSetDefaultHInstance = []() {
        HMODULE duiModule =
            LoadLibraryEx(L"dui70.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (duiModule) {
            PCSTR procName =
#ifdef _WIN64
                R"(?SetDefaultHInstance@DUIXmlParser@DirectUI@@QEAAXPEAUHINSTANCE__@@@Z)";
#else
                R"(?SetDefaultHInstance@DUIXmlParser@DirectUI@@QAEXPAUHINSTANCE__@@@Z)";
#endif
            FARPROC pSetXMLFromResource = GetProcAddress(duiModule, procName);
            if (pSetXMLFromResource) {
                return (DirectUI_DUIXmlParser_SetDefaultHInstance_t)
                    pSetXMLFromResource;
            } else {
                Wh_Log(L"Couldn't find SetDefaultHInstance");
            }
        } else {
            Wh_Log(L"Couldn't load dui70.dll");
        }

        return (DirectUI_DUIXmlParser_SetDefaultHInstance_t) nullptr;
    }();

    if (pSetDefaultHInstance) {
        pSetDefaultHInstance(pThis, hModule);
    }
}

using SetXMLFromResource_t = HRESULT(__thiscall*)(void* pThis,
                                                  PCWSTR lpName,
                                                  PCWSTR lpType,
                                                  HMODULE hModule,
                                                  HINSTANCE param4,
                                                  HINSTANCE param5);
SetXMLFromResource_t SetXMLFromResource_Original;
HRESULT __thiscall SetXMLFromResource_Hook(void* pThis,
                                           PCWSTR lpName,
                                           PCWSTR lpType,
                                           HMODULE hModule,
                                           HINSTANCE param4,
                                           HINSTANCE param5) {
    auto resOp = resourceOperationCountScope();
    DWORD c = ++g_operationCounter;

    PCWSTR logTypeStr;
    WCHAR logTypeStrBuffer[16];
    if (IS_INTRESOURCE(lpType)) {
        swprintf_s(logTypeStrBuffer, L"%u", (DWORD)(ULONG_PTR)lpType);
        logTypeStr = logTypeStrBuffer;
    } else {
        logTypeStr = lpType;
    }

    if (IS_INTRESOURCE(lpName)) {
        Wh_Log(L"[%u] > Type: %s, resource number: %u", c, logTypeStr,
               (DWORD)(ULONG_PTR)lpName);
    } else {
        Wh_Log(L"[%u] > Type: %s, resource name: %s", c, logTypeStr, lpName);
    }

    HRESULT result;

    bool redirected = RedirectModule(
        c, hModule, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            result = SetXMLFromResource_Original(
                pThis, lpName, lpType, hInstanceRedirect, param4, param5);
            if (SUCCEEDED(result)) {
                Wh_Log(L"[%u] Redirected successfully", c);
                return true;
            }

            Wh_Log(L"[%u] SetXMLFromResource failed with error %08X", c,
                   result);
            return false;
        });
    if (redirected) {
        // By using a redirected module, its handle will be saved by
        // DUIXmlParser and will be used for loading additional resources, such
        // as strings. This might be undesirable, so set the original module. An
        // example for why setting the original module is sometimes preferable:
        // https://github.com/ramensoftware/windhawk-mods/issues/639
        DirectUI_DUIXmlParser_SetDefaultHInstance(pThis, hModule);
        return result;
    }

    return SetXMLFromResource_Original(pThis, lpName, lpType, hModule, param4,
                                       param5);
}

// https://devblogs.microsoft.com/oldnewthing/20040130-00/?p=40813
LPCWSTR FindStringResourceEx(HINSTANCE hinst, UINT uId, UINT langId) {
    // Convert the string ID into a bundle number
    LPCWSTR pwsz = NULL;
    HRSRC hrsrc =
        FindResourceEx(hinst, RT_STRING, MAKEINTRESOURCE(uId / 16 + 1), langId);
    if (hrsrc) {
        HGLOBAL hglob = LoadResource(hinst, hrsrc);
        if (hglob) {
            pwsz = reinterpret_cast<LPCWSTR>(LockResource(hglob));
            if (pwsz) {
                // okay now walk the string table
                for (UINT i = 0; i < (uId & 15); i++) {
                    pwsz += 1 + (UINT)*pwsz;
                }
            }
        }
    }
    return pwsz;
}

using DirectUI_CreateString_t = void*(WINAPI*)(PCWSTR name,
                                               HINSTANCE hInstance);
DirectUI_CreateString_t DirectUI_CreateString_Original;
void* WINAPI DirectUI_CreateString_Hook(PCWSTR name, HINSTANCE hInstance) {
    if (!hInstance) {
        return DirectUI_CreateString_Original(name, hInstance);
    }

    auto resOp = resourceOperationCountScope();
    DWORD c = ++g_operationCounter;

    Wh_Log(L"[%u] > DUI string number: %u", c, (DWORD)(ULONG_PTR)name);

    void* result;

    bool redirected = RedirectModule(
        c, hInstance, []() {},
        [&](HINSTANCE hInstanceRedirect) {
            // For other redirected functions, we check whether the function
            // succeeded. If it didn't, we try another redirection or fall back
            // to the original file.
            //
            // In this case, there's no reliable way to find out whether
            // the function failed, since it just uses an empty string if it's
            // missing. Therefore, only make sure that the string resource
            // exists.
            UINT uId = (DWORD)(ULONG_PTR)name;
            PCWSTR string = FindStringResourceEx(hInstanceRedirect, uId, 0);
            if (!string || !*string) {
                Wh_Log(L"[%u] Resource not found", c);
                return false;
            }

            result = DirectUI_CreateString_Original(name, hInstanceRedirect);
            Wh_Log(L"[%u] Redirected successfully", c);
            return true;
        });
    if (redirected) {
        return result;
    }

    return DirectUI_CreateString_Original(name, hInstance);
}

bool IsExplorerProcess() {
    WCHAR path[MAX_PATH];
    if (!GetWindowsDirectory(path, ARRAYSIZE(path))) {
        Wh_Log(L"GetWindowsDirectory failed");
        return false;
    }

    wcscat_s(path, MAX_PATH, L"\\explorer.exe");

    return GetModuleHandle(path) == GetModuleHandle(nullptr);
}

HWND FindCurrentProcessTaskbarWnd() {
    HWND hTaskbarWnd = nullptr;

    EnumWindows(
        [](HWND hWnd, LPARAM lParam) WINAPI -> BOOL {
            DWORD dwProcessId;
            WCHAR className[32];
            if (GetWindowThreadProcessId(hWnd, &dwProcessId) &&
                dwProcessId == GetCurrentProcessId() &&
                GetClassName(hWnd, className, ARRAYSIZE(className)) &&
                _wcsicmp(className, L"Shell_TrayWnd") == 0) {
                *reinterpret_cast<HWND*>(lParam) = hWnd;
                return FALSE;
            }
            return TRUE;
        },
        reinterpret_cast<LPARAM>(&hTaskbarWnd));

    return hTaskbarWnd;
}

bool DoesCurrentProcessOwnTaskbar() {
    return IsExplorerProcess() && FindCurrentProcessTaskbarWnd();
}

void PromptToClearCache() {
    if (g_clearCachePromptThread) {
        if (WaitForSingleObject(g_clearCachePromptThread, 0) != WAIT_OBJECT_0) {
            return;
        }

        CloseHandle(g_clearCachePromptThread);
    }

    g_clearCachePromptThread = CreateThread(
        nullptr, 0,
        [](LPVOID lpParameter) WINAPI -> DWORD {
            TASKDIALOGCONFIG taskDialogConfig{
                .cbSize = sizeof(taskDialogConfig),
                .dwFlags = TDF_ALLOW_DIALOG_CANCELLATION,
                .dwCommonButtons = TDCBF_YES_BUTTON | TDCBF_NO_BUTTON,
                .pszWindowTitle = kClearCachePromptTitle,
                .pszMainIcon = TD_INFORMATION_ICON,
                .pszContent = kClearCachePromptText,
                .pfCallback = [](HWND hwnd, UINT msg, WPARAM wParam,
                                 LPARAM lParam, LONG_PTR lpRefData)
                                  WINAPI -> HRESULT {
                    switch (msg) {
                        case TDN_CREATED:
                            g_clearCachePromptWindow = hwnd;
                            SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
                                         SWP_NOMOVE | SWP_NOSIZE);
                            break;

                        case TDN_DESTROYED:
                            g_clearCachePromptWindow = nullptr;
                            break;
                    }

                    return S_OK;
                },
            };

            static decltype(&TaskDialogIndirect) pTaskDialogIndirect = []() {
                HMODULE hComctl32 = LoadLibraryEx(L"comctl32.dll", nullptr,
                                                  LOAD_LIBRARY_SEARCH_SYSTEM32);
                if (!hComctl32) {
                    Wh_Log(L"Failed to load comctl32.dll");
                    return (decltype(&TaskDialogIndirect))nullptr;
                }

                return (decltype(&TaskDialogIndirect))GetProcAddress(
                    hComctl32, "TaskDialogIndirect");
            }();

            int button;
            if (pTaskDialogIndirect &&
                SUCCEEDED(pTaskDialogIndirect(&taskDialogConfig, &button,
                                              nullptr, nullptr)) &&
                button == IDYES) {
                WCHAR commandLine[ARRAYSIZE(kClearCacheCommand)];
                memcpy(commandLine, kClearCacheCommand,
                       sizeof(kClearCacheCommand));
                STARTUPINFO si = {
                    .cb = sizeof(si),
                };
                PROCESS_INFORMATION pi{};
                if (CreateProcess(nullptr, commandLine, nullptr, nullptr, FALSE,
                                  0, nullptr, nullptr, &si, &pi)) {
                    CloseHandle(pi.hThread);
                    CloseHandle(pi.hProcess);
                }
            }

            return 0;
        },
        nullptr, 0, nullptr);
}

HANDLE LockTempFileExclusive(PCWSTR filePath, DWORD timeoutMs) {
    HANDLE hFile =
        CreateFile(filePath, GENERIC_READ | GENERIC_WRITE,
                   FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_ALWAYS,
                   FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        return INVALID_HANDLE_VALUE;
    }

    HANDLE hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    if (!hEvent) {
        CloseHandle(hFile);
        return INVALID_HANDLE_VALUE;
    }

    OVERLAPPED ov = {
        .hEvent = hEvent,
    };

    // Lock first byte only.
    BOOL locked = LockFileEx(hFile, LOCKFILE_EXCLUSIVE_LOCK, 0, 1, 0, &ov);
    if (!locked) {
        DWORD err = GetLastError();
        if (err != ERROR_IO_PENDING) {
            CloseHandle(hEvent);
            CloseHandle(hFile);
            return INVALID_HANDLE_VALUE;
        }

        DWORD waitResult = WaitForSingleObject(hEvent, timeoutMs);
        if (waitResult != WAIT_OBJECT_0) {
            CancelIo(hFile);
            CloseHandle(hEvent);
            CloseHandle(hFile);
            return INVALID_HANDLE_VALUE;
        }

        DWORD bytesTransferred;
        if (!GetOverlappedResult(hFile, &ov, &bytesTransferred, FALSE)) {
            CloseHandle(hEvent);
            CloseHandle(hFile);
            return INVALID_HANDLE_VALUE;
        }
    }

    CloseHandle(hEvent);
    return hFile;
}

BOOL UnlockTempFileExclusive(HANDLE hFile) {
    OVERLAPPED ov = {};
    BOOL unlocked = UnlockFileEx(hFile, 0, 1, 0, &ov);
    CloseHandle(hFile);
    return unlocked;
}

HRESULT UnzipToFolder(BSTR zipFilePath, BSTR destinationPath) {
    winrt::com_ptr<IShellDispatch> shellDispatch;
    HRESULT hr = CoCreateInstance(CLSID_Shell, nullptr, CLSCTX_INPROC_SERVER,
                                  IID_PPV_ARGS(shellDispatch.put()));
    if (FAILED(hr))
        return hr;

    VARIANT zipFileVariant;
    zipFileVariant.vt = VT_BSTR;
    zipFileVariant.bstrVal = zipFilePath;

    winrt::com_ptr<Folder> zipFile;
    hr = shellDispatch->NameSpace(zipFileVariant, zipFile.put());
    if (FAILED(hr))
        return hr;
    if (!zipFile)
        return E_FAIL;

    VARIANT destinationVariant;
    destinationVariant.vt = VT_BSTR;
    destinationVariant.bstrVal = destinationPath;

    winrt::com_ptr<Folder> destination;
    hr = shellDispatch->NameSpace(destinationVariant, destination.put());
    if (FAILED(hr))
        return hr;
    if (!destination)
        return E_FAIL;

    winrt::com_ptr<FolderItems> zipFiles;
    hr = zipFile->Items(zipFiles.put());
    if (FAILED(hr))
        return hr;
    if (!zipFiles)
        return E_FAIL;

    LONG zipFilesCount;
    hr = zipFiles->get_Count(&zipFilesCount);
    if (FAILED(hr))
        return hr;

    // If the zip contains a single folder, select it to avoid an extra nesting.
    if (zipFilesCount == 1) {
        VARIANT index;
        index.vt = VT_I4;
        index.lVal = 0;

        winrt::com_ptr<FolderItem> zipSubFolderItem;
        hr = zipFiles->Item(index, zipSubFolderItem.put());
        if (FAILED(hr))
            return hr;
        if (!zipSubFolderItem)
            return E_FAIL;

        VARIANT_BOOL isFolder;
        hr = zipSubFolderItem->get_IsFolder(&isFolder);
        if (FAILED(hr))
            return hr;

        if (isFolder) {
            winrt::com_ptr<IDispatch> zipSubFolderDispatch;
            hr = zipSubFolderItem->get_GetFolder(zipSubFolderDispatch.put());
            if (FAILED(hr))
                return hr;
            if (!zipSubFolderDispatch)
                return E_FAIL;

            winrt::com_ptr<Folder> zipSubFolder;
            hr = zipSubFolderDispatch->QueryInterface(
                IID_PPV_ARGS(zipSubFolder.put()));
            if (FAILED(hr))
                return hr;
            if (!zipSubFolder)
                return E_FAIL;

            hr = zipSubFolder->Items(zipFiles.put());
            if (FAILED(hr))
                return hr;
            if (!zipFiles)
                return E_FAIL;
        }
    }

    winrt::com_ptr<IDispatch> zipFilesDispatch;
    hr = zipFiles->QueryInterface(IID_PPV_ARGS(zipFilesDispatch.put()));
    if (FAILED(hr))
        return hr;
    if (!zipFilesDispatch)
        return E_FAIL;

    VARIANT itemVariant;
    itemVariant.vt = VT_DISPATCH;
    itemVariant.pdispVal = zipFilesDispatch.get();

    VARIANT options;
    options.vt = VT_I4;
    options.lVal = FOF_NO_UI;

    return destination->CopyHere(itemVariant, options);
}

bool DownloadAndExtractIconTheme(std::wstring_view relativeUrl,
                                 const std::filesystem::path& tempFilePath,
                                 const std::filesystem::path& tempFolderPath,
                                 const std::filesystem::path& targetPath) {
    std::wstring url =
        L"https://ramensoftware.github.io/resource-redirect-themes/";
    url += relativeUrl;

    WH_GET_URL_CONTENT_OPTIONS options{
        .optionsSize = sizeof(options),
        .targetFilePath = tempFilePath.c_str(),
    };
    const WH_URL_CONTENT* urlContent = Wh_GetUrlContent(url.c_str(), &options);
    if (!urlContent) {
        Wh_Log(L"Wh_GetUrlContent failed");
        return false;
    }

    if (urlContent->statusCode != 200) {
        Wh_Log(L"Wh_GetUrlContent returned %d", urlContent->statusCode);
        return false;
    }

    Wh_FreeUrlContent(urlContent);

    HRESULT hr = CoInitialize(nullptr);
    if (SUCCEEDED(hr)) {
        std::error_code ec;
        std::filesystem::remove_all(tempFolderPath, ec);
        std::filesystem::create_directories(tempFolderPath, ec);

        hr = UnzipToFolder(_bstr_t(tempFilePath.c_str()),
                           _bstr_t(tempFolderPath.c_str()));
        if (FAILED(hr)) {
            Wh_Log(L"UnzipToFolder returned 0x%08X", hr);
        }

        std::filesystem::rename(tempFolderPath, targetPath, ec);

        CoUninitialize();
    } else {
        Wh_Log(L"CoInitialize returned 0x%08X", hr);
    }

    return SUCCEEDED(hr);
}

std::filesystem::path EnsureIconThemeAvailable(
    const std::filesystem::path& storagePath,
    std::wstring_view themeName,
    std::wstring_view relativeUrl,
    PCWSTR themeFolderKey) {
    std::error_code ec;

    // Check if we have a stored folder name for this theme.
    WCHAR storedFolderName[MAX_PATH];
    Wh_GetStringValue(themeFolderKey, storedFolderName,
                      ARRAYSIZE(storedFolderName));
    if (*storedFolderName) {
        auto storedPath = storagePath / storedFolderName;
        if (std::filesystem::is_directory(storedPath, ec)) {
            return storedPath;
        }
    }

    // Theme not available, need to find a usable folder and download.
    WCHAR lastErrorThemeName[256];
    Wh_GetStringValue(L"lastErrorThemeName", lastErrorThemeName,
                      ARRAYSIZE(lastErrorThemeName));
    if (lastErrorThemeName == themeName) {
        FILETIME filetimeNow;
        GetSystemTimeAsFileTime(&filetimeNow);
        ULARGE_INTEGER timeNow{
            .HighPart = filetimeNow.dwHighDateTime,
            .LowPart = filetimeNow.dwLowDateTime,
        };

        ULARGE_INTEGER timeLastError{
            .HighPart = (DWORD)Wh_GetIntValue(L"lastErrorTimeHigh", 0),
            .LowPart = (DWORD)Wh_GetIntValue(L"lastErrorTimeLow", 0),
        };

        ULONGLONG elapsedSec =
            (timeNow.QuadPart - timeLastError.QuadPart) / 10000000;
        if (elapsedSec < 60 * 60 * 4) {
            Wh_Log(L"Aborting due to error %u seconds ago", elapsedSec);
            return std::filesystem::path();
        }
    }

    // Find a usable folder name.
    std::filesystem::path targetPath;
    std::wstring folderName;
    for (int suffix = 0; suffix < 100; suffix++) {
        if (suffix == 0) {
            folderName = themeName;
        } else {
            folderName =
                std::wstring(themeName) + L"_" + std::to_wstring(suffix + 1);
        }

        targetPath = storagePath / folderName;

        if (!std::filesystem::is_directory(targetPath, ec)) {
            // Folder doesn't exist, we can use it.
            break;
        }

        // Folder exists, try to remove it.
        Wh_Log(L"Folder exists, trying to remove: %s", targetPath.c_str());
        std::filesystem::remove_all(targetPath, ec);

        if (!std::filesystem::is_directory(targetPath, ec)) {
            // Successfully removed.
            break;
        }

        Wh_Log(L"Failed to remove folder, trying next name");
    }

    if (std::filesystem::is_directory(targetPath, ec)) {
        Wh_Log(L"Failed to find a usable folder name");
        return std::filesystem::path();
    }

    Wh_Log(L"Downloading from %.*s", static_cast<int>(relativeUrl.length()),
           relativeUrl.data());

    bool downloaded = false;
    auto tempZip = storagePath / L"_temp.zip";
    auto tempFolder = storagePath / L"_temp_extracted";
    if (DownloadAndExtractIconTheme(relativeUrl, tempZip, tempFolder,
                                    targetPath)) {
        DeleteFile(tempZip.c_str());
        downloaded = std::filesystem::is_directory(targetPath, ec);
    }

    if (!downloaded) {
        FILETIME filetimeNow;
        GetSystemTimeAsFileTime(&filetimeNow);
        Wh_SetStringValue(L"lastErrorThemeName",
                          std::wstring(themeName).c_str());
        Wh_SetIntValue(L"lastErrorTimeHigh", (int)filetimeNow.dwHighDateTime);
        Wh_SetIntValue(L"lastErrorTimeLow", (int)filetimeNow.dwLowDateTime);
        return std::filesystem::path();
    }

    // Store the folder name on successful download and extract.
    Wh_SetStringValue(themeFolderKey, folderName.c_str());

    return targetPath;
}

std::wstring GetIconThemePath(std::wstring_view iconTheme) {
    auto iconThemeSepIt = iconTheme.find(L"|");
    if (iconThemeSepIt == iconTheme.npos) {
        return std::wstring();
    }

    auto themeName = iconTheme.substr(0, iconThemeSepIt);
    auto relativeUrl = iconTheme.substr(iconThemeSepIt + 1);

    WCHAR storagePathBuffer[MAX_PATH];
    if (!Wh_GetModStoragePath(storagePathBuffer,
                              ARRAYSIZE(storagePathBuffer))) {
        Wh_Log(L"Wh_GetModStoragePath failed");
        return std::wstring();
    }

    const auto storagePath = std::filesystem::path{storagePathBuffer};

    auto themeFolderKey = L"themeFolder_" + std::wstring(themeName);

    WCHAR storedFolderName[MAX_PATH];
    Wh_GetStringValue(themeFolderKey.c_str(), storedFolderName,
                      ARRAYSIZE(storedFolderName));
    if (*storedFolderName) {
        auto storedPath = storagePath / storedFolderName;
        std::error_code ec;
        if (std::filesystem::is_directory(storedPath, ec)) {
            return storedPath;
        }
    }

    auto lockFilePath = storagePath / L"_lock";

    HANDLE lockFile = LockTempFileExclusive(lockFilePath.c_str(), 30000);
    if (!lockFile) {
        Wh_Log(L"LockTempFileExclusive failed");
        return std::wstring();
    }

    auto targetPath = EnsureIconThemeAvailable(
        storagePath, themeName, relativeUrl, themeFolderKey.c_str());

    UnlockTempFileExclusive(lockFile);
    DeleteFile(lockFilePath.c_str());

    return targetPath;
}

bool StartsWithCaseInsensitive(std::wstring_view str,
                               std::wstring_view prefix) {
    return str.size() >= prefix.size() &&
           _wcsnicmp(str.data(), prefix.data(), prefix.size()) == 0;
}

// https://github.com/valinet/wh-mods/blob/61319815c7e018e392a08077dc364559548ade02/mods/valinet-unserver.wh.cpp#L95
// https://stackoverflow.com/questions/937044/determine-path-to-registry-key-from-hkey-handle-in-c
std::wstring GetPathFromHKEY(HKEY key) {
    if (!key) {
        return {};
    }

    using NtQueryKey_t = NTSTATUS(NTAPI*)(
        HANDLE KeyHandle, int KeyInformationClass, PVOID KeyInformation,
        ULONG Length, PULONG ResultLength);
    static NtQueryKey_t pNtQueryKey = []() {
        HMODULE hNtdll = GetModuleHandle(L"ntdll.dll");
        if (hNtdll) {
            return (NtQueryKey_t)GetProcAddress(hNtdll, "NtQueryKey");
        }
        return (NtQueryKey_t) nullptr;
    }();

    if (!pNtQueryKey) {
        return {};
    }

    constexpr int kKeyNameInformation = 3;

    ULONG size = 0;
    NTSTATUS result = pNtQueryKey(key, kKeyNameInformation, nullptr, 0, &size);
    if (result != STATUS_BUFFER_TOO_SMALL) {
        return {};
    }

    std::vector<BYTE> buffer(size);
    result = pNtQueryKey(key, kKeyNameInformation, buffer.data(), size, &size);
    if (result != STATUS_SUCCESS || size < sizeof(ULONG)) {
        return {};
    }

    // The buffer contains a KEY_NAME_INFORMATION structure:
    // ULONG NameLength (4 bytes) + WCHAR Name[1].
    ULONG nameLength = *reinterpret_cast<ULONG*>(buffer.data());
    if (size < sizeof(ULONG) + nameLength) {
        return {};
    }

    PCWSTR name = reinterpret_cast<PCWSTR>(buffer.data() + sizeof(ULONG));
    return std::wstring(name, nameLength / sizeof(WCHAR));
}

bool MatchesClassSubkey(HKEY hKey, std::wstring_view classSubKey) {
    std::wstring keyPath = GetPathFromHKEY(hKey);
    std::wstring_view keyPathSuffix = keyPath;

    constexpr std::wstring_view kRegistryMachinePrefix =
        L"\\REGISTRY\\MACHINE\\SOFTWARE\\Classes\\"sv;
    constexpr std::wstring_view kRegistryUserPrefix = L"\\REGISTRY\\USER\\"sv;

    if (StartsWithCaseInsensitive(keyPathSuffix, kRegistryMachinePrefix)) {
        // Remove "\REGISTRY\MACHINE\SOFTWARE\Classes\" prefix.
        keyPathSuffix.remove_prefix(kRegistryMachinePrefix.size());
    } else if (StartsWithCaseInsensitive(keyPathSuffix, kRegistryUserPrefix)) {
        // Remove "\REGISTRY\USER\" prefix.
        keyPathSuffix.remove_prefix(kRegistryUserPrefix.size());

        // Remove "<SID>_Classes\" prefix for non-empty SID.
        size_t firstBackslash = keyPathSuffix.find(L'\\');
        if (firstBackslash == std::wstring_view::npos) {
            return false;
        }

        constexpr std::wstring_view kClassesSuffix = L"_Classes"sv;
        if (firstBackslash > kClassesSuffix.size() &&
            _wcsnicmp(
                keyPathSuffix.data() + firstBackslash - kClassesSuffix.size(),
                kClassesSuffix.data(), kClassesSuffix.size()) == 0) {
            keyPathSuffix.remove_prefix(firstBackslash + 1);
        } else {
            return false;
        }
    } else {
        return false;
    }

    return keyPathSuffix.size() == classSubKey.size() &&
           _wcsnicmp(keyPathSuffix.data(), classSubKey.data(),
                     classSubKey.size()) == 0;
}

using RegQueryValueExW_t = decltype(&RegQueryValueExW);
RegQueryValueExW_t RegQueryValueExW_Original;
LSTATUS WINAPI RegQueryValueExW_Hook(HKEY hKey,
                                     LPCWSTR lpValueName,
                                     LPDWORD lpReserved,
                                     LPDWORD lpType,
                                     LPBYTE lpData,
                                     LPDWORD lpcbData) {
    // Disable thumbnails in Explorer folders by providing the "Logo" value for
    // the "AllFolders\Shell" key. When this value is present, Explorer uses a
    // generic folder icon instead of showing thumbnails of the folder contents.
    // This is equivalent to setting the "Logo" value below to "imageres.dll,-3"
    // (REG_SZ), but is applied dynamically by the mod:
    //
    // HKCU\Software\Classes\Local
    // Settings\Software\Microsoft\Windows\Shell\Bags\AllFolders\Shell
    if (!g_settings.disableThumbnails) {
        return RegQueryValueExW_Original(hKey, lpValueName, lpReserved, lpType,
                                         lpData, lpcbData);
    }

    constexpr WCHAR kValueName[] = L"Logo";
    constexpr std::wstring_view kClassSubkey =
        L"Local Settings\\Software\\Microsoft\\Windows\\Shell\\Bags\\AllFolders\\Shell"sv;
    constexpr std::wstring_view kReplacementData = L"imageres.dll,-3"sv;

    // Save the original buffer size before calling the original function, as
    // lpcbData is overwritten with the actual data size on output.
    DWORD dataBufferSize = (lpData && lpcbData) ? *lpcbData : 0;

    LSTATUS ret = RegQueryValueExW_Original(hKey, lpValueName, lpReserved,
                                            lpType, lpData, lpcbData);
    if (ret != ERROR_SUCCESS && ret != ERROR_MORE_DATA &&
        ret != ERROR_FILE_NOT_FOUND) {
        return ret;
    }

    if (!lpValueName || _wcsicmp(lpValueName, kValueName) != 0) {
        return ret;
    }

    if (!MatchesClassSubkey(hKey, kClassSubkey)) {
        return ret;
    }

    Wh_Log(L"Providing %s value to disable folder thumbnails", kValueName);

    DWORD requiredSize = (kReplacementData.size() + 1) * sizeof(WCHAR);

    if (lpType) {
        *lpType = REG_SZ;
    }

    if (!lpData || !lpcbData) {
        if (lpData && !lpcbData) {
            // Shouldn't happen per documentation.
            return ret;
        }
        if (lpcbData) {
            *lpcbData = requiredSize;
        }
        return ERROR_SUCCESS;
    }

    if (dataBufferSize < requiredSize) {
        Wh_Log(L"Not enough space for %s, available=%u", kValueName,
               dataBufferSize);
        *lpcbData = requiredSize;
        return ERROR_MORE_DATA;
    }

    memcpy(lpData, kReplacementData.data(),
           kReplacementData.size() * sizeof(WCHAR));
    reinterpret_cast<PWSTR>(lpData)[kReplacementData.size()] = L'\0';
    *lpcbData = requiredSize;

    return ERROR_SUCCESS;
}

void LoadSettings() {
    g_settings.iconTheme = WindhawkUtils::StringSetting::make(L"resourceRedirect.iconTheme");
    g_settings.disableThumbnails = Wh_GetIntSetting(L"resourceRedirect.disableThumbnails");
    g_settings.allResourceRedirect = Wh_GetIntSetting(L"resourceRedirect.allResourceRedirect");

    std::unordered_map<std::wstring, std::vector<std::wstring>> paths;
    std::unordered_map<std::string, std::vector<std::string>> pathsA;
    std::vector<std::pair<std::wstring, std::wstring>> pathPatterns;
    std::vector<std::pair<std::string, std::string>> pathPatternsA;

    auto addRedirectionPath = [&paths, &pathsA, &pathPatterns, &pathPatternsA](
                                  PCWSTR original, PCWSTR redirect) {
        WCHAR originalExpanded[MAX_PATH];
        DWORD originalExpandedLen = ExpandEnvironmentStrings(
            original, originalExpanded, ARRAYSIZE(originalExpanded));
        if (!originalExpandedLen ||
            originalExpandedLen > ARRAYSIZE(originalExpanded)) {
            Wh_Log(L"Failed to expand path: %s", original);
            return;
        }

        // Remove null terminator from len.
        originalExpandedLen--;

        bool isPattern = wcscspn(originalExpanded, L"*?") < originalExpandedLen;

        Wh_Log(L"Configuring%s %s->%s", isPattern ? L" pattern" : L"",
               originalExpanded, redirect);

        LCMapStringEx(LOCALE_NAME_USER_DEFAULT, LCMAP_UPPERCASE,
                      originalExpanded, originalExpandedLen, originalExpanded,
                      originalExpandedLen, nullptr, nullptr, 0);

        if (isPattern) {
            pathPatterns.push_back({originalExpanded, redirect});
        } else {
            paths[originalExpanded].push_back(redirect);
        }

        char originalExpandedA[MAX_PATH];
        char redirectA[MAX_PATH];
        size_t charsConverted = 0;
        if (wcstombs_s(&charsConverted, originalExpandedA,
                       ARRAYSIZE(originalExpandedA), originalExpanded,
                       _TRUNCATE) == 0 &&
            wcstombs_s(&charsConverted, redirectA, ARRAYSIZE(redirectA),
                       redirect, _TRUNCATE) == 0) {
            if (isPattern) {
                pathPatternsA.push_back({originalExpandedA, redirectA});
            } else {
                pathsA[originalExpandedA].push_back(redirectA);
            }
        } else {
            Wh_Log(L"Error configuring ANSI redirection");
        }
    };

    auto addRedirectionThemePath = [&addRedirectionPath](PCWSTR themePath) {
        auto initialPath = std::filesystem::path{themePath};

        std::filesystem::path themeFolder;
        std::filesystem::path themeIniFile;
        if (std::filesystem::is_directory(initialPath)) {
            themeFolder = initialPath;
            themeIniFile = themeFolder / L"theme.ini";
        } else {
            themeIniFile = initialPath;
            themeFolder = themeIniFile.parent_path();
        }

        auto fileSize = std::filesystem::file_size(themeIniFile);

        std::wstring data(fileSize + 2, L'\0');
        DWORD result = GetPrivateProfileSection(
            L"redirections", data.data(), data.size(), themeIniFile.c_str());
        if (!result || result == data.size() - 2) {
            DWORD dwError = GetLastError();
            Wh_Log(L"Error reading data from %s: %u", themeIniFile.c_str(),
                   dwError);
            return false;
        }

        for (auto* p = data.data(); *p;) {
            auto* pNext = p + wcslen(p) + 1;
            auto* pEq = wcschr(p, L'=');
            if (pEq) {
                *pEq = L'\0';

                auto redirectFile = themeFolder / (pEq + 1);
                addRedirectionPath(p, redirectFile.c_str());
            } else {
                Wh_Log(L"Skipping %s", p);
            }

            p = pNext;
        }

        return true;
    };

    if (*g_settings.iconTheme) {
        std::wstring iconThemePath =
            GetIconThemePath(g_settings.iconTheme.get());
        if (!iconThemePath.empty()) {
            try {
                addRedirectionThemePath(iconThemePath.c_str());
            } catch (const std::exception& ex) {
                Wh_Log(L"Error: %S", ex.what());
            }
        }
    }

    for (int i = 0;; i++) {
        PCWSTR themePath = Wh_GetStringSetting(L"resourceRedirect.themePaths[%d]", i);
        bool hasThemePath = *themePath;
        if (hasThemePath) {
            try {
                addRedirectionThemePath(themePath);
            } catch (const std::exception& ex) {
                Wh_Log(L"Error: %S", ex.what());
            }
        }
        Wh_FreeStringSetting(themePath);
        if (!hasThemePath) {
            break;
        }
    }

    PCWSTR themeFolder = Wh_GetStringSetting(L"resourceRedirect.themeFolder");
    if (*themeFolder) {
        try {
            addRedirectionThemePath(themeFolder);
        } catch (const std::exception& ex) {
            Wh_Log(L"Error: %S", ex.what());
        }
    }
    Wh_FreeStringSetting(themeFolder);

    for (int i = 0;; i++) {
        PCWSTR original =
            Wh_GetStringSetting(L"resourceRedirect.redirectionResourcePaths[%d].original", i);
        PCWSTR redirect =
            Wh_GetStringSetting(L"resourceRedirect.redirectionResourcePaths[%d].redirect", i);

        bool hasRedirection = *original || *redirect;

        if (hasRedirection) {
            addRedirectionPath(original, redirect);
        }

        Wh_FreeStringSetting(original);
        Wh_FreeStringSetting(redirect);

        if (!hasRedirection) {
            break;
        }
    }

    // Reverse the order to allow later entries override earlier ones.
    for (auto& [key, vec] : paths) {
        std::reverse(vec.begin(), vec.end());
    }
    for (auto& [key, vec] : pathsA) {
        std::reverse(vec.begin(), vec.end());
    }
    std::reverse(pathPatterns.begin(), pathPatterns.end());
    std::reverse(pathPatternsA.begin(), pathPatternsA.end());

    std::unique_lock lock{g_redirectionResourcePathsMutex};
    g_redirectionResourcePaths = std::move(paths);
    g_redirectionResourcePathsA = std::move(pathsA);
    g_redirectionResourcePathPatterns = std::move(pathPatterns);
    g_redirectionResourcePathPatternsA = std::move(pathPatternsA);
}

BOOL ModInit() {
    Wh_Log(L">");

    LoadSettings();

    HMODULE kernelBaseModule = GetModuleHandle(L"kernelbase.dll");
    HMODULE kernel32Module = GetModuleHandle(L"kernel32.dll");

    auto setKernelFunctionHook = [kernelBaseModule, kernel32Module](
                                     PCSTR targetName, void* hookFunction,
                                     void** originalFunction) {
        void* targetFunction =
            (void*)GetProcAddress(kernelBaseModule, targetName);
        if (!targetFunction) {
            targetFunction = (void*)GetProcAddress(kernel32Module, targetName);
            if (!targetFunction) {
                return FALSE;
            }
        }

        return Wh_SetFunctionHook(targetFunction, hookFunction,
                                  originalFunction);
    };

    Wh_SetFunctionHook((void*)PrivateExtractIconsW,
                       (void*)PrivateExtractIconsW_Hook,
                       (void**)&PrivateExtractIconsW_Original);

    // The functions below use FindResourceEx, LoadResource, SizeofResource.
    Wh_SetFunctionHook((void*)LoadImageA, (void*)LoadImageA_Hook,
                       (void**)&LoadImageA_Original);

    Wh_SetFunctionHook((void*)LoadImageW, (void*)LoadImageW_Hook,
                       (void**)&LoadImageW_Original);

    Wh_SetFunctionHook((void*)LoadIconA, (void*)LoadIconA_Hook,
                       (void**)&LoadIconA_Original);

    Wh_SetFunctionHook((void*)LoadIconW, (void*)LoadIconW_Hook,
                       (void**)&LoadIconW_Original);

    Wh_SetFunctionHook((void*)LoadCursorA, (void*)LoadCursorA_Hook,
                       (void**)&LoadCursorA_Original);

    Wh_SetFunctionHook((void*)LoadCursorW, (void*)LoadCursorW_Hook,
                       (void**)&LoadCursorW_Original);

    Wh_SetFunctionHook((void*)LoadBitmapA, (void*)LoadBitmapA_Hook,
                       (void**)&LoadBitmapA_Original);

    Wh_SetFunctionHook((void*)LoadBitmapW, (void*)LoadBitmapW_Hook,
                       (void**)&LoadBitmapW_Original);

    Wh_SetFunctionHook((void*)LoadMenuA, (void*)LoadMenuA_Hook,
                       (void**)&LoadMenuA_Original);

    Wh_SetFunctionHook((void*)LoadMenuW, (void*)LoadMenuW_Hook,
                       (void**)&LoadMenuW_Original);

    Wh_SetFunctionHook((void*)DialogBoxParamA, (void*)DialogBoxParamA_Hook,
                       (void**)&DialogBoxParamA_Original);

    Wh_SetFunctionHook((void*)DialogBoxParamW, (void*)DialogBoxParamW_Hook,
                       (void**)&DialogBoxParamW_Original);

    Wh_SetFunctionHook((void*)CreateDialogParamA,
                       (void*)CreateDialogParamA_Hook,
                       (void**)&CreateDialogParamA_Original);

    Wh_SetFunctionHook((void*)CreateDialogParamW,
                       (void*)CreateDialogParamW_Hook,
                       (void**)&CreateDialogParamW_Original);

    // The functions below use RtlLoadString.
    Wh_SetFunctionHook((void*)LoadStringA, (void*)LoadStringA_u_Hook,
                       (void**)&LoadStringA_u_Original);

    Wh_SetFunctionHook((void*)LoadStringW, (void*)LoadStringW_u_Hook,
                       (void**)&LoadStringW_u_Original);

    setKernelFunctionHook("LoadStringA", (void*)LoadStringA_k_Hook,
                          (void**)&LoadStringA_k_Original);

    setKernelFunctionHook("LoadStringW", (void*)LoadStringW_k_Hook,
                          (void**)&LoadStringW_k_Original);

    if (g_settings.allResourceRedirect) {
        setKernelFunctionHook("FindResourceExA", (void*)FindResourceExA_Hook,
                              (void**)&FindResourceExA_Original);
        setKernelFunctionHook("FindResourceExW", (void*)FindResourceExW_Hook,
                              (void**)&FindResourceExW_Original);
        setKernelFunctionHook("LoadResource", (void*)LoadResource_Hook,
                              (void**)&LoadResource_Original);
        setKernelFunctionHook("SizeofResource", (void*)SizeofResource_Hook,
                              (void**)&SizeofResource_Original);

        void* pRtlLoadString = (void*)GetProcAddress(
            GetModuleHandle(L"ntdll.dll"), "RtlLoadString");
        if (pRtlLoadString) {
            Wh_SetFunctionHook(pRtlLoadString, (void*)RtlLoadString_Hook,
                               (void**)&RtlLoadString_Original);
        }
    }

    if (kernelBaseModule) {
        auto pRegQueryValueExW = (RegQueryValueExW_t)GetProcAddress(
            kernelBaseModule, "RegQueryValueExW");
        if (pRegQueryValueExW) {
            WindhawkUtils::SetFunctionHook(pRegQueryValueExW,
                                           RegQueryValueExW_Hook,
                                           &RegQueryValueExW_Original);
        }
    }

    // The functions below use FindResourceEx, LoadResource, SizeofResource.
    HMODULE shcoreModule =
        LoadLibraryEx(L"shcore.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (shcoreModule) {
        FARPROC pSHCreateStreamOnModuleResourceW =
            GetProcAddress(shcoreModule, (PCSTR)109);
        if (pSHCreateStreamOnModuleResourceW) {
            Wh_SetFunctionHook(
                (void*)pSHCreateStreamOnModuleResourceW,
                (void*)SHCreateStreamOnModuleResourceW_Hook,
                (void**)&SHCreateStreamOnModuleResourceW_Original);
        } else {
            Wh_Log(L"Couldn't find SHCreateStreamOnModuleResourceW (#109)");
        }
    } else {
        Wh_Log(L"Couldn't load shcore.dll");
    }

    HMODULE duiModule =
        LoadLibraryEx(L"dui70.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (duiModule) {
        PCSTR SetXMLFromResource_Name =
            R"(?_SetXMLFromResource@DUIXmlParser@DirectUI@@IAEJPBG0PAUHINSTANCE__@@11@Z)";
        FARPROC pSetXMLFromResource =
            GetProcAddress(duiModule, SetXMLFromResource_Name);
        if (!pSetXMLFromResource) {
#ifdef _WIN64
            PCSTR SetXMLFromResource_Name_Win10_x64 =
                R"(?_SetXMLFromResource@DUIXmlParser@DirectUI@@IEAAJPEBG0PEAUHINSTANCE__@@11@Z)";
            pSetXMLFromResource =
                GetProcAddress(duiModule, SetXMLFromResource_Name_Win10_x64);
#endif
        }

        if (pSetXMLFromResource) {
            Wh_SetFunctionHook((void*)pSetXMLFromResource,
                               (void*)SetXMLFromResource_Hook,
                               (void**)&SetXMLFromResource_Original);
        } else {
            Wh_Log(L"Couldn't find SetXMLFromResource");
        }

        PCSTR DirectUI_CreateString_Name =
#ifdef _WIN64
            R"(?CreateString@Value@DirectUI@@SAPEAV12@PEBGPEAUHINSTANCE__@@@Z)";
#else
            R"(?CreateString@Value@DirectUI@@SGPAV12@PBGPAUHINSTANCE__@@@Z)";
#endif
        FARPROC pDirectUI_CreateString =
            GetProcAddress(duiModule, DirectUI_CreateString_Name);

        if (pDirectUI_CreateString) {
            Wh_SetFunctionHook((void*)pDirectUI_CreateString,
                               (void*)DirectUI_CreateString_Hook,
                               (void**)&DirectUI_CreateString_Original);
        } else {
            Wh_Log(L"Couldn't find DirectUI::Value::CreateString");
        }
    } else {
        Wh_Log(L"Couldn't load dui70.dll");
    }

    return TRUE;
}

void ModUninit() {
    Wh_Log(L">");

    FreeAndClearRedirectedModules();

    HWND clearCachePromptWindow = g_clearCachePromptWindow;
    if (clearCachePromptWindow) {
        PostMessage(clearCachePromptWindow, WM_CLOSE, 0, 0);
    }

    if (g_clearCachePromptThread) {
        WaitForSingleObject(g_clearCachePromptThread, INFINITE);
        CloseHandle(g_clearCachePromptThread);
        g_clearCachePromptThread = nullptr;
    }

    if (DoesCurrentProcessOwnTaskbar()) {
        // Let other processes some time to unload the mod.
        Sleep(400);

        // Invalidate icon cache.
        SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);
    }
}

BOOL ModSettingsChanged(BOOL* bReload) {
    Wh_Log(L">");

    auto prevIconTheme = std::move(g_settings.iconTheme);
    bool prevDisableThumbnails = g_settings.disableThumbnails;
    int prevAllResourceRedirect = g_settings.allResourceRedirect;

    LoadSettings();

    if (g_settings.allResourceRedirect != prevAllResourceRedirect) {
        *bReload = TRUE;
        return TRUE;
    }

    FreeAndClearRedirectedModules();

    if (DoesCurrentProcessOwnTaskbar()) {
        if (wcscmp(g_settings.iconTheme, prevIconTheme) != 0 ||
            g_settings.disableThumbnails != prevDisableThumbnails) {
            PromptToClearCache();
        }

        // Let other processes some time to load the new config.
        Sleep(400);

        // Invalidate icon cache.
        SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);
    }

    return TRUE;
}
}  // namespace mod_resourceRedirect

// ===================================================================
// Part: Shortcut arrows (shortcutArrows)
// Remove Shortcut Arrow Icons 2.0.2. Our copy of the mod by Dev-StudioCode,
// https://github.com/Dev-StudioCode/Hide-Desktop-Shortcut-Icon, kept up by DavidHiFi.
// The original names no license.
// ===================================================================
namespace mod_shortcutArrows {
// ---------------------------------------------------------------------------
// Types & State
// ---------------------------------------------------------------------------

struct OverlayBackup {
  int shil;
  int imageIndex;
  HICON originalIcon;
};

static const GUID g_iidImageList = {
    0x46eb5926,
    0x582e,
    0x4017,
    {0x9f, 0xdf, 0xe8, 0x99, 0x8d, 0xaa, 0x09, 0x50}};

static std::vector<OverlayBackup> g_backupOverlays;
static int g_overlayImageIndex = -1;
// Posted to the desktop list view so the icon refresh runs after Explorer has
// finished building the desktop. Refreshing inside CreateWindowExW crashed
// Explorer at start (CListViewHost::SetWorkAreasWithDPI on a half-built view).
static UINT g_msgDeferredRefresh =
    RegisterWindowMessageW(L"RemoveShortcutArrows_DeferredRefresh");
static WindhawkUtils::StringSetting g_customIconPath;

// ---------------------------------------------------------------------------
// Transparent Icon Synthesis (In-Memory, 32-bit ARGB)
// ---------------------------------------------------------------------------

static HICON CreateTransparentIcon(int cx, int cy) {
  if (cx <= 0 || cy <= 0)
    return nullptr;

  BITMAPV5HEADER bi = {};
  bi.bV5Size = sizeof(bi);
  bi.bV5Width = cx;
  bi.bV5Height = cy;
  bi.bV5Planes = 1;
  bi.bV5BitCount = 32;
  bi.bV5Compression = BI_BITFIELDS;
  bi.bV5RedMask = 0x00FF0000;
  bi.bV5GreenMask = 0x0000FF00;
  bi.bV5BlueMask = 0x000000FF;
  bi.bV5AlphaMask = 0xFF000000;

  HDC hdc = GetDC(nullptr);
  void *bits = nullptr;
  HBITMAP hColor = CreateDIBSection(hdc, (BITMAPINFO *)&bi, DIB_RGB_COLORS,
                                    &bits, nullptr, 0);
  ReleaseDC(nullptr, hdc);
  if (!hColor)
    return nullptr;

  if (bits) {
    memset(bits, 0, (size_t)cx * cy * 4);
  }

  // 1-bit monochrome AND mask: set all bits to 1 (transparent background for
  // Win32 icons)
  int rowBytes = ((cx + 15) / 16) * 2;
  std::vector<BYTE> maskBits((size_t)rowBytes * cy, 0xFF);
  HBITMAP hMask = CreateBitmap(cx, cy, 1, 1, maskBits.data());

  ICONINFO ii = {};
  ii.fIcon = TRUE;
  ii.hbmColor = hColor;
  ii.hbmMask = hMask;
  HICON hIcon = CreateIconIndirect(&ii);

  DeleteObject(hColor);
  if (hMask)
    DeleteObject(hMask);
  return hIcon;
}

static HICON GetReplacementIcon(int cx, int cy) {
  PCWSTR customPath = g_customIconPath.get();
  if (customPath && *customPath) {
    HICON hLoaded = (HICON)LoadImageW(nullptr, customPath, IMAGE_ICON, cx, cy,
                                      LR_LOADFROMFILE);
    if (hLoaded) {
      return hLoaded;
    }
  }
  return CreateTransparentIcon(cx, cy);
}

// ---------------------------------------------------------------------------
// Overlay Management via Shell Image List (In-Place Replacement)
// ---------------------------------------------------------------------------

static bool HideShortcutOverlay() {
  int linkOverlay = SHGetIconOverlayIndexW(nullptr, IDO_SHGIOI_LINK);
  if (linkOverlay <= 0)
    return false;

  const int sizes[] = {SHIL_LARGE, SHIL_SMALL, SHIL_EXTRALARGE, SHIL_SYSSMALL,
                       SHIL_JUMBO};
  bool anyReplaced = false;

  for (int shil : sizes) {
    IImageList *piml = nullptr;
    if (FAILED(SHGetImageList(shil, g_iidImageList, (void **)&piml)) || !piml) {
      continue;
    }

    int imageIndex = -1, cx = 0, cy = 0;
    HICON original = nullptr;
    if (SUCCEEDED(piml->GetOverlayImage(linkOverlay, &imageIndex)) &&
        imageIndex >= 0 && SUCCEEDED(piml->GetIconSize(&cx, &cy))) {
      g_overlayImageIndex = imageIndex;

      // Check if this SHIL size was already backed up
      bool alreadyBackedUp = false;
      for (const auto &b : g_backupOverlays) {
        if (b.shil == shil) {
          alreadyBackedUp = true;
          break;
        }
      }

      if (!alreadyBackedUp) {
        if (SUCCEEDED(piml->GetIcon(imageIndex, ILD_TRANSPARENT, &original))) {
          if (HICON replacement = GetReplacementIcon(cx, cy)) {
            int replaced = -1;
            if (SUCCEEDED(piml->ReplaceIcon(imageIndex, replacement, &replaced))) {
              g_backupOverlays.push_back({shil, imageIndex, original});
              original = nullptr;
              anyReplaced = true;
            }
            DestroyIcon(replacement);
          }
          if (original) {
            DestroyIcon(original);
          }
        }
      } else {
        // Re-apply replacement in case image list was swapped by Explorer
        if (HICON replacement = GetReplacementIcon(cx, cy)) {
          int replaced = -1;
          if (SUCCEEDED(piml->ReplaceIcon(imageIndex, replacement, &replaced))) {
            anyReplaced = true;
          }
          DestroyIcon(replacement);
        }
      }
    }
    piml->Release();
  }

  return anyReplaced;
}

static void RestoreShortcutOverlay() {
  // Restore in reverse order so lists returned for multiple SHIL sizes restore
  // properly
  for (auto it = g_backupOverlays.rbegin(); it != g_backupOverlays.rend();
       ++it) {
    IImageList *piml = nullptr;
    if (SUCCEEDED(SHGetImageList(it->shil, g_iidImageList, (void **)&piml)) &&
        piml) {
      int replaced = -1;
      piml->ReplaceIcon(it->imageIndex, it->originalIcon, &replaced);
      piml->Release();
    }
    DestroyIcon(it->originalIcon);
  }
  g_backupOverlays.clear();
}

// ---------------------------------------------------------------------------
// Desktop Redraw & Hook Helpers
// ---------------------------------------------------------------------------

static HWND GetDesktopListView() {
  HWND hShell = GetShellWindow();
  if (!hShell) {
    hShell = FindWindowW(L"Progman", L"Program Manager");
  }
  if (!hShell)
    return nullptr;

  HWND hDefView = FindWindowExW(hShell, nullptr, L"SHELLDLL_DefView", nullptr);
  if (!hDefView) {
    HWND hWorkerW = nullptr;
    while ((hWorkerW = FindWindowExW(nullptr, hWorkerW, L"WorkerW", nullptr)) !=
           nullptr) {
      hDefView = FindWindowExW(hWorkerW, nullptr, L"SHELLDLL_DefView", nullptr);
      if (hDefView)
        break;
    }
  }
  if (hDefView) {
    HWND hListView =
        FindWindowExW(hDefView, nullptr, L"SysListView32", L"FolderView");
    DWORD pid = 0;
    if (hListView && GetWindowThreadProcessId(hListView, &pid) &&
        pid == GetCurrentProcessId()) {
      return hListView;
    }
  }
  return nullptr;
}

static void RefreshDesktop() {
  if (HWND hListView = GetDesktopListView()) {
    InvalidateRect(hListView, nullptr, TRUE);
  }
}

static void RefreshDesktopAndExplorer() {
  if (g_overlayImageIndex >= 0) {
    SHChangeNotify(
        SHCNE_UPDATEIMAGE, SHCNF_DWORD | SHCNF_FLUSHNOWAIT, nullptr,
        reinterpret_cast<LPCVOID>(static_cast<ULONG_PTR>(g_overlayImageIndex)));
  }
  RefreshDesktop();
}

static bool EnsureShortcutOverlayHidden() {
  if (HideShortcutOverlay()) {
    RefreshDesktopAndExplorer();
    return true;
  }
  return false;
}

static bool IsDesktopFolderView(HWND hWnd) {
  WCHAR buf[32];
  if (!GetClassNameW(hWnd, buf, ARRAYSIZE(buf)) || wcscmp(buf, L"SysListView32"))
    return false;
  HWND hDefView = GetParent(hWnd);
  if (!hDefView || !GetClassNameW(hDefView, buf, ARRAYSIZE(buf)) ||
      wcscmp(buf, L"SHELLDLL_DefView"))
    return false;
  HWND hTop = GetParent(hDefView);
  if (!hTop || !GetClassNameW(hTop, buf, ARRAYSIZE(buf)) ||
      (wcscmp(buf, L"Progman") && wcscmp(buf, L"WorkerW")))
    return false;
  DWORD pid = 0;
  return GetWindowThreadProcessId(hWnd, &pid) && pid == GetCurrentProcessId();
}

static LRESULT CALLBACK DesktopSubclassProc(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
    DWORD_PTR dwRefData) {
  if (g_msgDeferredRefresh && uMsg == g_msgDeferredRefresh) {
    EnsureShortcutOverlayHidden();
    return 0;
  }
  switch (uMsg) {
    case WM_SETTINGCHANGE:
    case WM_THEMECHANGED:
      EnsureShortcutOverlayHidden();
      break;
  }
  return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

using CreateWindowExW_t = decltype(&CreateWindowExW);
static CreateWindowExW_t CreateWindowExW_Original;
static HWND WINAPI CreateWindowExW_Hook(
    DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName,
    DWORD dwStyle, int X, int Y, int nWidth, int nHeight,
    HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, PVOID lpParam) {
  HWND hWnd = CreateWindowExW_Original(dwExStyle, lpClassName, lpWindowName,
                                       dwStyle, X, Y, nWidth, nHeight,
                                       hWndParent, hMenu, hInstance, lpParam);
  if (hWnd && IsDesktopFolderView(hWnd)) {
    WindhawkUtils::SetWindowSubclassFromAnyThread(hWnd, DesktopSubclassProc, 0);
    PostMessageW(hWnd, g_msgDeferredRefresh, 0, 0);
  }
  return hWnd;
}

// ---------------------------------------------------------------------------
// Settings & Lifecycle
// ---------------------------------------------------------------------------

static void LoadSettings() {
  g_customIconPath = WindhawkUtils::StringSetting::make(L"shortcutArrows.custom_icon_path");
}

BOOL ModInit() {
  Wh_Log(L"Initializing Remove Shortcut Arrow Icons mod");
  LoadSettings();

  WindhawkUtils::SetFunctionHook(CreateWindowExW, CreateWindowExW_Hook,
                                 &CreateWindowExW_Original);

  EnsureShortcutOverlayHidden();
  return TRUE;
}

void ModAfterInit() {
  if (HWND hDesktop = GetDesktopListView()) {
    WindhawkUtils::SetWindowSubclassFromAnyThread(hDesktop, DesktopSubclassProc, 0);
  }
}

void ModUninit() {
  Wh_Log(L"Uninitializing Remove Shortcut Arrow Icons mod");

  if (HWND hDesktop = GetDesktopListView()) {
    WindhawkUtils::RemoveWindowSubclassFromAnyThread(hDesktop, DesktopSubclassProc);
  }

  RestoreShortcutOverlay();
  RefreshDesktopAndExplorer();
  g_overlayImageIndex = -1;
}

BOOL ModSettingsChanged(BOOL *bReload) {
  *bReload = TRUE;
  return TRUE;
}
}  // namespace mod_shortcutArrows


// ===================================================================
// The suite: starts only the parts that belong to the program it woke up in.
// Each part keeps its own entry points (ModInit and so on) inside its own namespace.
// ===================================================================
namespace suite {

static const int kMaxItems = 256;

static WCHAR g_exe[MAX_PATH];
static WCHAR g_path[MAX_PATH];

// A star matches any letters, a question mark one letter. Capitals do not matter.
static bool Wild(PCWSTR pat, PCWSTR text) {
    PCWSTR star = nullptr;
    PCWSTR back = nullptr;
    while (*text) {
        if (*pat == L'*') {
            star = pat++;
            back = text;
        } else if (*pat == L'?' || towlower(*pat) == towlower(*text)) {
            pat++;
            text++;
        } else if (star) {
            pat = star + 1;
            text = ++back;
        } else {
            return false;
        }
    }
    while (*pat == L'*') pat++;
    return *pat == 0;
}

// A pattern with a backslash is matched against the full path, any other against the file name.
static bool MatchProgram(PCWSTR pat) {
    return Wild(pat, wcschr(pat, L'\\') ? g_path : g_exe);
}

static bool MatchAny(std::initializer_list<PCWSTR> pats) {
    for (PCWSTR p : pats) {
        if (MatchProgram(p)) return true;
    }
    return false;
}

// Builds a text out of a part's settings, so a change to another part never touches this one.
struct Fp {
    std::wstring s;
    void I(PCWSTR key) {
        s += std::to_wstring(Wh_GetIntSetting(key));
        s += L'\x1f';
    }
    void S(PCWSTR key) {
        PCWSTR v = Wh_GetStringSetting(key);
        s += v;
        s += L'\x1f';
        Wh_FreeStringSetting(v);
    }
    void SA(PCWSTR fmt) {
        for (int i = 0; i < kMaxItems; i++) {
            PCWSTR v = Wh_GetStringSetting(fmt, i);
            bool end = !*v;
            s += v;
            s += L'\x1f';
            Wh_FreeStringSetting(v);
            if (end) break;
        }
    }
    void OA(std::initializer_list<PCWSTR> fmts) {
        for (int i = 0; i < kMaxItems; i++) {
            bool any = false;
            for (PCWSTR f : fmts) {
                PCWSTR v = Wh_GetStringSetting(f, i);
                any = any || *v;
                s += v;
                s += L'\x1f';
                Wh_FreeStringSetting(v);
            }
            if (!any) break;
        }
    }
};

// "Programs to leave alone" in Icon themes (this used to be the engine's own skip list for the old mod).
static bool SkippedByResourceRedirect() {
    for (int i = 0; i < kMaxItems; i++) {
        PCWSTR v = Wh_GetStringSetting(L"resourceRedirect.skipPrograms[%d]", i);
        bool end = !*v;
        bool hit = !end && MatchProgram(v);
        Wh_FreeStringSetting(v);
        if (end) break;
        if (hit) return true;
    }
    return false;
}


#ifdef _WIN64

// ---- App icons
static bool wants_appIcons() {
    return MatchAny({L"Ableton Live*.exe", L"yapfast.exe", L"zen.exe", L"ApplicationFrameHost.exe", L"steam.exe", L"steamwebhelper.exe"});
}
static bool allowed_appIcons() {
    return Wh_GetIntSetting(L"appIcons.enabled") != 0;
}
static BOOL init_appIcons() {
    return mod_appIcons::ModInit();
}
static void uninit_appIcons() {
    mod_appIcons::ModUninit();
}
static BOOL changed_appIcons(BOOL*) {
    mod_appIcons::ModSettingsChanged();
    return TRUE;
}
static void fp_appIcons(Fp& f) {
    f.I(L"appIcons.ableton");
    f.I(L"appIcons.yapfast");
    f.I(L"appIcons.zen");
    f.I(L"appIcons.steam");
    f.I(L"appIcons.settings");
    f.I(L"appIcons.windowIcons");
    f.I(L"appIcons.shortcutIcons");
    f.I(L"appIcons.trayIcon");
}
#else
static bool wants_appIcons() { return false; }
static bool allowed_appIcons() { return false; }
static BOOL init_appIcons() { return FALSE; }
static void uninit_appIcons() {}
static BOOL changed_appIcons(BOOL*) { return TRUE; }
static void fp_appIcons(Fp&) {}
#endif  // _WIN64

// ---- Store app icons
static bool wants_storeAppIcons() {
    return MatchAny({L"explorer.exe", L"StartMenuExperienceHost.exe", L"SearchHost.exe", L"ShellExperienceHost.exe", L"ShellHost.exe", L"RuntimeBroker.exe", L"Taskmgr.exe"});
}
static bool allowed_storeAppIcons() {
    return Wh_GetIntSetting(L"storeAppIcons.enabled") != 0;
}
static BOOL init_storeAppIcons() {
    return mod_storeAppIcons::ModInit();
}
static void uninit_storeAppIcons() {
    mod_storeAppIcons::ModUninit();
}
static BOOL changed_storeAppIcons(BOOL*) {
    mod_storeAppIcons::ModSettingsChanged();
    return TRUE;
}
static void fp_storeAppIcons(Fp& f) {
    f.S(L"storeAppIcons.icon-theme");
    f.SA(L"storeAppIcons.theme-paths[%d]");
    f.OA({L"storeAppIcons.windows-apps[%d].bundle", L"storeAppIcons.windows-apps[%d].redirect"});
    f.OA({L"storeAppIcons.system-apps[%d].bundle", L"storeAppIcons.system-apps[%d].redirect"});
    f.OA({L"storeAppIcons.custom[%d].assets-path", L"storeAppIcons.custom[%d].redirect"});
    f.I(L"storeAppIcons.grant-permissions");
}

// ---- Windows icon swaps
static bool wants_iconCustomizer() {
    return true;
}
static bool allowed_iconCustomizer() {
    return Wh_GetIntSetting(L"iconCustomizer.enabled") != 0;
}
static BOOL init_iconCustomizer() {
    return mod_iconCustomizer::ModInit();
}
static void uninit_iconCustomizer() {
    mod_iconCustomizer::ModUninit();
}
static BOOL changed_iconCustomizer(BOOL*) {
    mod_iconCustomizer::ModSettingsChanged();
    return TRUE;
}
static void fp_iconCustomizer(Fp& f) {
    f.S(L"iconCustomizer.DOCNOASSOC");
    f.S(L"iconCustomizer.DOCASSOC");
    f.S(L"iconCustomizer.APPLICATION");
    f.S(L"iconCustomizer.FOLDER");
    f.S(L"iconCustomizer.FOLDEROPEN");
    f.S(L"iconCustomizer.DRIVE525");
    f.S(L"iconCustomizer.DRIVE35");
    f.S(L"iconCustomizer.DRIVEREMOVE");
    f.S(L"iconCustomizer.DRIVEFIXED");
    f.S(L"iconCustomizer.DRIVENET");
    f.S(L"iconCustomizer.DRIVENETDISABLED");
    f.S(L"iconCustomizer.DRIVECD");
    f.S(L"iconCustomizer.DRIVERAM");
    f.S(L"iconCustomizer.WORLD");
    f.S(L"iconCustomizer.SERVER");
    f.S(L"iconCustomizer.PRINTER");
    f.S(L"iconCustomizer.MYNETWORK");
    f.S(L"iconCustomizer.FIND");
    f.S(L"iconCustomizer.HELP");
    f.S(L"iconCustomizer.SHARE");
    f.S(L"iconCustomizer.LINK");
    f.S(L"iconCustomizer.SLOWFILE");
    f.S(L"iconCustomizer.RECYCLER");
    f.S(L"iconCustomizer.RECYCLERFULL");
    f.S(L"iconCustomizer.MEDIACDAUDIO");
    f.S(L"iconCustomizer.LOCK");
    f.S(L"iconCustomizer.AUTOLIST");
    f.S(L"iconCustomizer.PRINTERNET");
    f.S(L"iconCustomizer.SERVERSHARE");
    f.S(L"iconCustomizer.PRINTERFAX");
    f.S(L"iconCustomizer.PRINTERFAXNET");
    f.S(L"iconCustomizer.PRINTERFILE");
    f.S(L"iconCustomizer.STACK");
    f.S(L"iconCustomizer.MEDIASVCD");
    f.S(L"iconCustomizer.STUFFEDFOLDER");
    f.S(L"iconCustomizer.DRIVEUNKNOWN");
    f.S(L"iconCustomizer.DRIVEDVD");
    f.S(L"iconCustomizer.MEDIADVD");
    f.S(L"iconCustomizer.MEDIADVDRAM");
    f.S(L"iconCustomizer.MEDIADVDRW");
    f.S(L"iconCustomizer.MEDIADVDR");
    f.S(L"iconCustomizer.MEDIADVDROM");
    f.S(L"iconCustomizer.MEDIACDAUDIOPLUS");
    f.S(L"iconCustomizer.MEDIACDRW");
    f.S(L"iconCustomizer.MEDIACDR");
    f.S(L"iconCustomizer.MEDIACDBURN");
    f.S(L"iconCustomizer.MEDIABLANKCD");
    f.S(L"iconCustomizer.MEDIACDROM");
    f.S(L"iconCustomizer.AUDIOFILES");
    f.S(L"iconCustomizer.IMAGEFILES");
    f.S(L"iconCustomizer.VIDEOFILES");
    f.S(L"iconCustomizer.MIXEDFILES");
    f.S(L"iconCustomizer.FOLDERBACK");
    f.S(L"iconCustomizer.FOLDERFRONT");
    f.S(L"iconCustomizer.SHIELD");
    f.S(L"iconCustomizer.WARNING");
    f.S(L"iconCustomizer.INFO");
    f.S(L"iconCustomizer.iERROR");
    f.S(L"iconCustomizer.KEY");
    f.S(L"iconCustomizer.SOFTWARE");
    f.S(L"iconCustomizer.RENAME");
    f.S(L"iconCustomizer.iDELETE");
    f.S(L"iconCustomizer.MEDIAAUDIODVD");
    f.S(L"iconCustomizer.MEDIAMOVIEDVD");
    f.S(L"iconCustomizer.MEDIAENHANCEDCD");
    f.S(L"iconCustomizer.MEDIAENHANCEDDVD");
    f.S(L"iconCustomizer.MEDIAHDDVD");
    f.S(L"iconCustomizer.MEDIABLURAY");
    f.S(L"iconCustomizer.MEDIAVCD");
    f.S(L"iconCustomizer.MEDIADVDPLUSR");
    f.S(L"iconCustomizer.MEDIADVDPLUSRW");
    f.S(L"iconCustomizer.DESKTOPPC");
    f.S(L"iconCustomizer.MOBILEPC");
    f.S(L"iconCustomizer.USERS");
    f.S(L"iconCustomizer.MEDIASMARTMEDIA");
    f.S(L"iconCustomizer.MEDIACOMPACTFLASH");
    f.S(L"iconCustomizer.DEVICECELLPHONE");
    f.S(L"iconCustomizer.DEVICECAMERA");
    f.S(L"iconCustomizer.DEVICEVIDEOCAMERA");
    f.S(L"iconCustomizer.DEVICEAUDIOPLAYER");
    f.S(L"iconCustomizer.NETWORKCONNECT");
    f.S(L"iconCustomizer.INTERNET");
    f.S(L"iconCustomizer.ZIPFILE");
    f.S(L"iconCustomizer.SETTINGS");
    f.S(L"iconCustomizer.DRIVEHDDVD");
    f.S(L"iconCustomizer.DRIVEBD");
    f.S(L"iconCustomizer.MEDIAHDDVDROM");
    f.S(L"iconCustomizer.MEDIAHDDVDR");
    f.S(L"iconCustomizer.MEDIAHDDVDRAM");
    f.S(L"iconCustomizer.MEDIABDROM");
    f.S(L"iconCustomizer.MEDIABDR");
    f.S(L"iconCustomizer.MEDIABDRE");
    f.S(L"iconCustomizer.CLUSTEREDDRIVE");
}

// ---- Icon themes
static bool wants_resourceRedirect() {
    return true;
}
static bool allowed_resourceRedirect() {
    return Wh_GetIntSetting(L"resourceRedirect.enabled") != 0 && !SkippedByResourceRedirect();
}
static BOOL init_resourceRedirect() {
    return mod_resourceRedirect::ModInit();
}
static void uninit_resourceRedirect() {
    mod_resourceRedirect::ModUninit();
}
static BOOL changed_resourceRedirect(BOOL* reload) {
    return mod_resourceRedirect::ModSettingsChanged(reload);
}
static void fp_resourceRedirect(Fp& f) {
    f.S(L"resourceRedirect.iconTheme");
    f.I(L"resourceRedirect.disableThumbnails");
    f.I(L"resourceRedirect.allResourceRedirect");
    f.SA(L"resourceRedirect.themePaths[%d]");
    f.OA({L"resourceRedirect.redirectionResourcePaths[%d].original", L"resourceRedirect.redirectionResourcePaths[%d].redirect"});
    f.S(L"resourceRedirect.themeFolder");
}

// ---- Shortcut arrows
static bool wants_shortcutArrows() {
    return MatchAny({L"explorer.exe"});
}
static bool allowed_shortcutArrows() {
    return Wh_GetIntSetting(L"shortcutArrows.enabled") != 0;
}
static BOOL init_shortcutArrows() {
    return mod_shortcutArrows::ModInit();
}
static void after_shortcutArrows() {
    mod_shortcutArrows::ModAfterInit();
}
static void uninit_shortcutArrows() {
    mod_shortcutArrows::ModUninit();
}
static BOOL changed_shortcutArrows(BOOL* reload) {
    return mod_shortcutArrows::ModSettingsChanged(reload);
}
static void fp_shortcutArrows(Fp& f) {
    f.S(L"shortcutArrows.custom_icon_path");
}

struct Part {
    PCWSTR name;
    bool (*wants)();
    bool (*allowed)();
    BOOL (*init)();
    void (*afterInit)();
    void (*uninit)();
    BOOL (*changed)(BOOL*);
    void (*fingerprint)(Fp&);
    bool wanted;       // this part belongs to this program
    bool wasAllowed;   // its switch (and skip list) when the program started
    bool running;      // ModInit ran and said yes
    std::wstring fp;   // its settings when it last looked
};

static Part g_parts[] = {
    {L"appIcons", wants_appIcons, allowed_appIcons, init_appIcons, nullptr, uninit_appIcons, changed_appIcons, fp_appIcons,
     false, false, false, {}},
    {L"storeAppIcons", wants_storeAppIcons, allowed_storeAppIcons, init_storeAppIcons, nullptr, uninit_storeAppIcons, changed_storeAppIcons, fp_storeAppIcons,
     false, false, false, {}},
    {L"iconCustomizer", wants_iconCustomizer, allowed_iconCustomizer, init_iconCustomizer, nullptr, uninit_iconCustomizer, changed_iconCustomizer, fp_iconCustomizer,
     false, false, false, {}},
    {L"resourceRedirect", wants_resourceRedirect, allowed_resourceRedirect, init_resourceRedirect, nullptr, uninit_resourceRedirect, changed_resourceRedirect, fp_resourceRedirect,
     false, false, false, {}},
    {L"shortcutArrows", wants_shortcutArrows, allowed_shortcutArrows, init_shortcutArrows, after_shortcutArrows, uninit_shortcutArrows, changed_shortcutArrows, fp_shortcutArrows,
     false, false, false, {}},
};

static BOOL Init() {
    if (!GetModuleFileNameW(nullptr, g_path, ARRAYSIZE(g_path))) return FALSE;
    PCWSTR name = wcsrchr(g_path, L'\\');
    lstrcpynW(g_exe, name ? name + 1 : g_path, ARRAYSIZE(g_exe));

    bool any = false;
    for (Part& p : g_parts) {
        p.wanted = p.wants();
        if (!p.wanted) continue;
        any = true;  // stay loaded, so switching a part on later needs no restart of the program
        p.wasAllowed = p.allowed();
        if (!p.wasAllowed) continue;
        p.running = p.init() != FALSE;
        if (p.running) {
            Fp f;
            p.fingerprint(f);
            p.fp = f.s;
        }
    }
    return any ? TRUE : FALSE;
}

static void AfterInit() {
    for (Part& p : g_parts) {
        if (p.running && p.afterInit) p.afterInit();
    }
}

static void Uninit() {
    for (int i = (int)ARRAYSIZE(g_parts) - 1; i >= 0; i--) {
        Part& p = g_parts[i];
        if (!p.running) continue;
        p.running = false;
        p.uninit();
    }
}

static BOOL SettingsChanged(BOOL* bReload) {
    // A part was switched on or off: reload everything, the clean way to start or stop hooks.
    for (Part& p : g_parts) {
        if (p.wanted && p.allowed() != p.wasAllowed) {
            *bReload = TRUE;
            return TRUE;
        }
    }
    // Otherwise only the parts whose own settings changed hear about it.
    for (Part& p : g_parts) {
        if (!p.running) continue;
        Fp f;
        p.fingerprint(f);
        if (f.s == p.fp) continue;
        p.fp = f.s;
        BOOL reload = FALSE;
        BOOL ok = p.changed(&reload);
        if (reload || !ok) {
            *bReload = TRUE;
            return TRUE;
        }
    }
    return TRUE;
}

}  // namespace suite

BOOL Wh_ModInit() {
    return suite::Init();
}

void Wh_ModAfterInit() {
    suite::AfterInit();
}

void Wh_ModUninit() {
    suite::Uninit();
}

BOOL Wh_ModSettingsChanged(BOOL* bReload) {
    return suite::SettingsChanged(bReload);
}
