// ==WindhawkMod==
// @id              seamless-media-player
// @name            Seamless Media Player
// @description     A media player with a live audio visualizer beside it, right on the taskbar
// @version 1.9.6
// @author          DavidHiFi, Salyts, USER-TOURNE, GR0UD, uMk0
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         MIT
// @include         explorer.exe
// @compilerOptions -lole32 -loleaut32 -lruntimeobject -luuid -luser32 -lwindowsapp -lshell32 -lgdi32 -lshlwapi -lwindowscodecs -ldwmapi -lshcore -lksuser -ldxgi -ld2d1 -ld3d11 -ldcomp -ldwrite -ladvapi32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Media Player

A media player and a live audio visualizer in one mod. The player shows what's
playing with album art and buttons, and the spectrum bars sit right beside it.

![Seamless Media Player preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-media-player.png)

## Features

- **Player and bars stay together.** The bars follow the player's right edge,
  so they never overlap it or drift away.
- **Lines up after your system stats.** Choose "Taskbar - After Taskbar System
  Info" and the player sits right after Taskbar System Info, moving with it
  when it changes size.
- **Album art, title and controls.** Previous, play/pause and next, plus click
  and scroll actions for volume, tracks and media sessions.
- **Live spectrum bars** with smooth falloff, six shapes, gradients and EQ
  presets. Right-click the bars to choose what they listen to.
- **Can stay visible all the time.** Turn off "Hide when no media" and it shows
  "Not Playing" between songs.
- **Stays out of the way.** Both parts hide during fullscreen games, and the
  bars follow taskbar auto-hide.
- **Bars behind the player, if you prefer.** Set Audio visualizer > Position >
  Placement to "Behind widget" and the bars fill the player's background,
  dimmed under the art, title and buttons, with no extra width.
- **Progress bar and time.** A thin progress line along the bottom edge (click
  it to seek) and an elapsed or elapsed/total clock before the buttons. Both
  are off by default.

## Notes

- Turn off Taskbar Fluent Media Player and Taskbar Audio Visualizer first, so
  you don't get two players or two sets of bars.
- The bars draw in a small helper process that Windhawk starts, so they never
  slow the taskbar down.
- The mod only listens to audio. It never changes devices, volume or routing.

## Credits

Based on [Taskbar Fluent Media Player](https://windhawk.net/mods/taskbar-fluent-media-player)
by [Salyts](https://github.com/Salyts) (MIT). The bars come from Taskbar Audio
Visualizer, built on [Tourne'Table](https://windhawk.net/mods/tourne-table-desktop-audio-visualizer)
by USER-TOURNE and [Desktop Audio Visualizer](https://windhawk.net/mods/desktop-audio-visualizer)
by Salyts (MIT). Thanks to [GR0UD](https://github.com/GR0UD) for the audio
capture code in the original player. The behind-widget bars, progress bar and
time display follow [Taskbar Media Widget](https://windhawk.net/mods/taskbar-media-widget)
by [uMk0](https://github.com/umk0) (MIT).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- MainSettings:
  - PlayerSetting:
    - position: "tray_left"
      $name: Media player position
      $name:ru-RU: Расположение медиаплеера
      $options:
      - "taskbar_after_system_info": "Taskbar - After Taskbar System Info"
      - "taskbar_left_edge": "Taskbar - Left edge (Overlay)"
      - "taskbar_center_edge": "Taskbar - Center (Overlay)"
      - "taskbar_right_edge": "Taskbar - Right edge (Overlay)"
      - "taskbar_left_start": "Taskbar - Left of Start button"
      - "taskbar_right_start": "Taskbar - Right of Start button"
      - "taskbar_after_search_left": "Taskbar - Left of Search button"
      - "taskbar_after_search_right": "Taskbar - Right of Search button"
      - "taskbar_after_taskview_left": "Taskbar - Left of Task View button"
      - "taskbar_after_taskview_right": "Taskbar - Right of Task View button"
      - "taskbar_after_widgets_left": "Taskbar - Left of Widgets button"
      - "taskbar_after_widgets_right": "Taskbar - Right of Widgets button"
      - "tray_left": "Tray - Far left"
      - "tray_right": "Tray - Far right"
      - "tray_before_clock": "Tray - Left of Clock"
      - "tray_after_clock": "Tray - Right of Clock"
      - "tray_before_omni_left": "Tray - Left of Network/Volume button"
      - "tray_before_omni_right": "Tray - Right of Network/Volume button"
      - "tray_language_left": "Tray - Left of Language button"
      - "tray_language_right": "Tray - Right of Language button"
      - "tray_icons_left": "Tray - Left of Tray Icons"
      - "tray_icons_right": "Tray - Right of Tray Icons"
      - "tray_hidden_icons_left": "Tray - Left of Hidden icons button"
      - "tray_hidden_icons_right": "Tray - Right of Hidden icons button"
      - "tray_after_showdesktop_left": "Tray - Left of Show Desktop"
      - "tray_after_showdesktop_right": "Tray - Right of Show Desktop"
      $options:ru-RU:
      - "taskbar_after_system_info": "Панель задач - После Taskbar System Info"
      - "taskbar_left_edge": "Панель задач - Левый край (оверлей)"
      - "taskbar_center_edge": "Панель задач - Центр (оверлей)"
      - "taskbar_right_edge": "Панель задач - Правый край (оверлей)"
      - "taskbar_left_start": "Панель задач - Слева от кнопки Пуск"
      - "taskbar_right_start": "Панель задач - Справа от кнопки Пуск"
      - "taskbar_after_search_left": "Панель задач - Слева от кнопки Поиск"
      - "taskbar_after_search_right": "Панель задач - Справа от кнопки Поиск"
      - "taskbar_after_taskview_left": "Панель задач - Слева от кнопки Представление задач"
      - "taskbar_after_taskview_right": "Панель задач - Справа от кнопки Представление задач"
      - "taskbar_after_widgets_left": "Панель задач - Слева от кнопки Мини-приложений"
      - "taskbar_after_widgets_right": "Панель задач - Справа от кнопки Мини-приложений"
      - "tray_left": "Трей - Край слева"
      - "tray_right": "Трей - Край справа"
      - "tray_before_clock": "Трей - Слева от часов"
      - "tray_after_clock": "Трей - Справа от часов"
      - "tray_before_omni_left": "Трей - Слева от кнопки Сеть/Громкость"
      - "tray_before_omni_right": "Трей - Справа от кнопки Сеть/Громкость"
      - "tray_language_left": "Трей - Слева от кнопки языка"
      -  "tray_language_right": "Трей - Справа от кнопки языка"
      - "tray_icons_left": "Трей - Слева от значков области уведомлений"
      - "tray_icons_right": "Трей - Справа от значков области уведомлений"
      - "tray_hidden_icons_left": "Трей - Слева от скрытых значков"
      - "tray_hidden_icons_right": "Трей - Справа от скрытых значков"
      - "tray_after_showdesktop_left": "Трей - Слева от кнопки Показать рабочий стол"
      - "tray_after_showdesktop_right": "Трей - Справа от кнопки Показать рабочий стол"
    - monitor: 1
      $name: Monitor
      $name:ru-RU: Монитор
      $description: >-
        The monitor number the player will appear on (1, 2, 3...).
        This number may differ from the monitor number shown in
        Windows Display Settings.
      $description:ru-RU: >-
        Номер монитора, на котором будет отображаться плеер (1, 2, 3...).
        Это число может отличаться от номера монитора в параметрах
        экрана Windows.
    - playerWidth: "0 0"
      $name: Media player width (min max)
      $name:ru-RU: Ширина медиаплеера (min max)
      $description: The first number is the minimum size, and the second is the maximum. You can also set it to 0, which means no limit.
      $description:ru-RU: Первая цифра — это минимальный размер, а вторая — максимальный. Также можно указать 0 — это без лимита.
    - playerHeight: "40 40"
      $name: Media player height (min max)
      $name:ru-RU: Высота медиаплеера (min max)
    - playerMargin: "4 4"
      $name: Media player margin (left right)
      $name:ru-RU: Отступ медиаплеера (left right)
      $description: The first number is the distance to the left, and the second is to the right.
      $description:ru-RU: Первая цифра — это расстояние влево, а вторая — вправо.
    - autoSwitchSession: true
      $name: Auto-switch to active media session
      $name:ru-RU: Автопереключение на активную медиасессию
      $description: When enabled, the player automatically switches to whichever media session is currently playing. If the active session pauses and another session is already playing, the player will switch to it.
      $description:ru-RU: Если включено, плеер автоматически переключается на воспроизводящую медиасессию. Если текущая сессия поставлена на паузу, а другое приложение уже играет — плеер переключится на него.
    - mirrorLayout: false
      $name: Mirror layout
      $name:ru-RU: Зеркальное расположение
      $description: Album art, text, and buttons will be displayed on the opposite side
      $description:ru-RU: Обложка альбома, текст и кнопки будут отображаться с противоположной стороны
    - fullHeightHitArea: true
      $name: Full-height invisible hit area
      $name:ru-RU: Невидимая область клика на всю высоту
      $description: Extends the clickable/hoverable area of the player to the full height of the taskbar, even if the player itself is shorter. Disable this if you don't want the player to react to clicks/hovers above or below its visible bounds.
      $description:ru-RU: Расширяет кликабельную/наводимую область плеера на всю высоту панели задач, даже если сам плеер меньше по высоте. Отключите, если не хотите, чтобы плеер реагировал на клики/наведение выше или ниже его видимых границ.
    $name: Media player
    $name:ru-RU: Медиаплеер

  - AlbumArtSetting:
    - showAlbumArt: true
      $name: Show album art
      $name:ru-RU: Отображать обложку альбома
    - albumArtWidth: "32 64"
      $name: Album art width (min max)
      $name:ru-RU: Ширина обложки альбома (min max)
    - albumArtHeight: "32 32"
      $name: Album art height (min max)
      $name:ru-RU: Высота обложки альбома (min max)
    - albumArtMargin: "0 0"
      $name: Album art margin (left right)
      $name:ru-RU: Отступ обложки альбома (left right)
    $name: Album Art
    $name:ru-RU: Обложка альбома

  - TextAreaSetting:
    - showTrackTitle: true
      $name: Show track title
      $name:ru-RU: Отображать название трека
    - showTrackArtist: true
      $name: Show artist name
      $name:ru-RU: Отображать имя исполнителя
    - textAreaWidth: "0 120"
      $name: Text area width (min max)
      $name:ru-RU: Ширина текстовой области (min max)
    - textAreaHeight: "0 0"
      $name: Text area height (min max)
      $name:ru-RU: Высота текстовой области (min max)
    - textAreaMargin: "5 5"
      $name: Text area margin (left right)
      $name:ru-RU: Отступ текстовой области (left right)
    - textSpacing: -1
      $name: Spacing between title and artist
      $name:ru-RU: Отступ между названием и исполнителем
    - enableTitleScrolling: true
      $name: Enable track title scrolling
      $name:ru-RU: Включить прокрутку названия трека
      $description: When enabled, the track title will scroll horizontally if it overflows the text area.
      $description:ru-RU: Если включено, название трека будет прокручиваться горизонтально при переполнении текстовой области.
    - enableArtistScrolling: false
      $name: Enable artist name scrolling
      $name:ru-RU: Включить прокрутку имени исполнителя
      $description: When enabled, the artist name will scroll horizontally if it overflows the text area.
      $description:ru-RU: Если включено, имя исполнителя будет прокручиваться горизонтально при переполнении текстовой области.
    - scrollSpeed: 1
      $name: Scroll speed (1-10)
      $name:ru-RU: Скорость прокрутки (1-10)
      $description: Controls how fast the text scrolls. 1 = slowest, 10 = fastest.
      $description:ru-RU: Управляет скоростью прокрутки текста. 1 = медленнее всего, 10 = быстрее всего.
    - scrollPauseDuration: 1000
      $name: Pause duration at edges (ms)
      $name:ru-RU: Пауза на краях (мс)
      $description: How long (in milliseconds) scrolling pauses at the start and end before reversing direction.
      $description:ru-RU: Сколько миллисекунд прокрутка делает паузу на начале и конце перед сменой направления.
    - scrollMode: "bounce"
      $name: Scroll mode
      $name:ru-RU: Режим прокрутки
      $options:
      - "bounce": "Bounce (back and forth)"
      - "loop":   "Loop (continuous)"
      $options:ru-RU:
      - "bounce": "Отскок (туда-обратно)"
      - "loop":   "Петля (непрерывная)"
    - loopGap: 40
      $name: Loop gap (px)
      $name:ru-RU: Отступ между повторами (пикс.)
      $description: Distance in pixels between the end of the text and the beginning of its copy in Loop mode.
      $description:ru-RU: Расстояние в пикселях между концом текста и началом его копии в режиме «Петля».
    - swapTitleArtist: false
      $name: Swap artist name and track title
      $name:ru-RU: Поменять местами название трека и имя исполнителя
    - emptyTitleText: "Untitled"
      $name: Title text when track has no name
      $name:ru-RU: Текст названия, если у трека нет имени
      $description: Shown in the title field when a track is playing but has no title. Leave empty to hide the title text in this case.
      $description:ru-RU: Отображается в поле названия, когда трек играет, но у него нет имени. Оставьте пустым, чтобы скрыть текст названия в этом случае.
    - noMediaTitleText: "Not Playing"
      $name: Title text when nothing is playing
      $name:ru-RU: Текст названия, когда ничего не воспроизводится
      $description: Shown in the title field when there is no media session at all. Leave empty to hide the title text in this case.
      $description:ru-RU: Отображается в поле названия, когда нет ни одной медиа-сессии. Оставьте пустым, чтобы скрыть текст названия в этом случае.
    - emptyArtistText: ""
      $name: Artist text when track has no artist
      $name:ru-RU: Текст исполнителя, если у трека не указан автор
      $description: Shown in the artist field when a track is playing but has no artist specified. Leave empty to hide the artist text in this case.
      $description:ru-RU: Отображается в поле исполнителя, когда трек играет, но автор не указан. Оставьте пустым, чтобы скрыть текст исполнителя в этом случае.
    - noMediaArtistText: ""
      $name: Artist text when nothing is playing
      $name:ru-RU: Текст исполнителя, когда ничего не воспроизводится
      $description: Shown in the artist field when there is no media session at all. Leave empty to hide the artist text in this case.
      $description:ru-RU: Отображается в поле исполнителя, когда нет ни одной медиа-сессии. Оставьте пустым, чтобы скрыть текст исполнителя в этом случае.
    $name: Text area
    $name:ru-RU: Текстовая область

  - MediaButtonsSettings:
    - showMediaButtons: true
      $name: Show media buttons
      $name:ru-RU: Отображать кнопки управления
    - mediaButtons: [prev, play, next]
      $name: Media buttons order
      $name:ru-RU: Расположение кнопок управления
      $description: Select which media control buttons to display and their order. Duplicates are ignored.
      $description:ru-RU: Выберите, какие кнопки управления воспроизведением отображать, а также их порядок. Дубликаты игнорируются.
      $options:
      - none: Nothing
      - prev: Previous Track
      - play: Play/Pause
      - next: Next Track
      - rewind: Rewind 5s
      - forward: Forward 5s
      - shuffle: Toggle Shuffle
      - repeat: Toggle Repeat
      - switch_sessions: Switch Sessions
      $options:ru-RU:
      - none: Ничего
      - prev: Предыдущий трек
      - play: Воспроизведение/Пауза
      - next: Следующий трек
      - rewind: Перемотка назад 5 сек
      - forward: Перемотка вперёд 5 сек
      - shuffle: Случайный порядок
      - repeat: Повтор
      - switch_sessions: Переключить сессию
    - mediaButtonsMargin: "2 2"
      $name: Media buttons margin (left right)
      $name:ru-RU: Отступ кнопок управления (left right)
    - buttonSize: 28
      $name: Button size
      $name:ru-RU: Размер кнопок управления
    - hideUnsupportedButtons: false
      $name: Hide unsupported buttons
      $name:ru-RU: Скрывать неподдерживаемые кнопки
      $description: When enabled, buttons for actions not supported by the current media session are completely hidden instead of shown as disabled.
      $description:ru-RU: Когда включено, кнопки действий, не поддерживаемых текущей медиа-сессией, полностью скрываются вместо отображения в неактивном состоянии.
    $name: Media Buttons
    $name:ru-RU: Кнопки управления
  $name: Main Settings
  $name:ru-RU: Основные настройки

- ProgressSettings:
  - showProgressBar: true
    $name: Progress bar
    $description: A thin line along the bottom edge of the player that fills as the track plays. When off,
      the player looks the same as before.
  - progressColor: artwork
    $name: Progress bar color
    $description: From album art takes the main color of the cover (Catppuccin blue when there is no cover).
      Gradient uses Catppuccin blue to mauve.
    $options:
    - artwork: From album art
    - gradient: Blue to mauve gradient
  - progressHeight: 2
    $name: Progress bar thickness
    $description: 1 to 6 logical pixels (Suggested: 2).
  - clickToSeek: true
    $name: Click the bar to seek
    $description: When on, clicking along the bottom edge jumps to that point in the track, if the app allows
      it. When off, clicks there go to the player as usual.
  - timeDisplay: elapsed_total
    $name: Playback time
    $description: Shows the track time before the media buttons.
    $options:
    - none: Hidden
    - elapsed: Elapsed (1:10)
    - elapsed_total: Elapsed and total (1:10 / 3:00)
  $name: Progress and time

- AppearanceSettings:
  - BackgroundStyleSettings:
    - backgroundType: "none"
      $name: Background type
      $name:ru-RU: Тип фона
      $options:
      - "none":           "None (transparent)"
      - "solid":          "Solid color"
      - "gradient":       "Gradient"
      - "acrylic":        "Acrylic"
      - "mica":           "Mica"
      - "mica_alt":       "Mica Alt"
      - "album_art_blur": "Blurred album cover"
      $options:ru-RU:
      - "none":           "Нет (прозрачный)"
      - "solid":          "Сплошной цвет"
      - "gradient":       "Градиент"
      - "acrylic":        "Акрил"
      - "mica":           "Mica"
      - "mica_alt":       "Mica Alt"
      - "album_art_blur": "Размытая обложка альбома"
    - solidColor: "35 35 35"
      $name: Background color (RGB)
      $name:ru-RU: Цвет фона (RGB)
      $description: "Use '-1 -1 -1' for the system contrast color and '-2 -2 -2' for the album art color. You can also specify two colors separated by a $ symbol (e.g., '0 0 0$255 255 255') where the first color is for light theme and the second for dark theme."
      $description:ru-RU: "Используйте '-1 -1 -1' для системного контрастного цвета, '-2 -2 -2' — для цвета обложки альбома. Также можно указать два цвета через символ $ (например, '0 0 0$255 255 255'), где первый цвет для светлой темы, второй для тёмной."
    - solidColor2: "35 35 35"
      $name: Gradient color 1 (RGB)
      $name:ru-RU: Цвет градиента 1 (RGB)
    - gradientColor2: "128 128 128"
      $name: Gradient color 2 (RGB)
      $name:ru-RU: Цвет градиента 2 (RGB)
    - solidOpacity: 100
      $name: Solid color opacity (0-100)
      $name:ru-RU: Прозрачность сплошного цвета (0-100)
    - gradientAngle: 50
      $name: Gradient rotation angle (0-360)
      $name:ru-RU: Угол поворота градиента (0-360)
    - gradientBalance: 50
      $name: Gradient color balance (0-100)
      $name:ru-RU: Градиентный цветовой баланс (0-100)
    - acrylicTintOpacity: 50
      $name: Acrylic tint opacity (0-100)
      $name:ru-RU: Прозрачность акрилового оттенка (0-100)
    - micaOpacity: 50
      $name: Mica/Mica Alt opacity (0-100)
      $name:ru-RU: "'Mica/Mica Alt' прозрачность (0-100)"
    - blurOpacity: 65
      $name: Album art blur opacity (0-100)
      $name:ru-RU: "'Размытая обложка альбома' прозрачность (0-100)"
    - blurRadius: 11
      $name: Album art blur strength (1-50)
      $name:ru-RU: "'Размытая обложка альбома' Сила размытия (1-50)"
    - cornerRadius: "4"
      $name: Media player corner radius
      $name:ru-RU: Радиус скругления медиаплеера
      $description: "Use single value (e.g., '4') for uniform corners, or four space-separated values (e.g., '4 2 4 2') for individual corners."
      $description:ru-RU: "Используйте одно значение (например, '4') для одинаковых углов, или четыре значения через пробел (например, '4 2 4 2') для каждого угла отдельно."
    - enablePlayerHoverEffect: "auto"
      $name: Player hover effect
      $name:ru-RU: Эффект при наведении на плеер
      $options:
      - "auto":  "Auto (theme changes automatically)"
      - "black": "Black"
      - "white": "White"
      - "off":   "Disable hover effect"
      $options:ru-RU:
      - "auto":  "Авто (тема изменяется автоматически)"
      - "black": "Чёрный"
      - "white": "Белый"
      - "off":   "Выключить эффект наведения"
    - enableMediaButtonsHoverEffect: "auto"
      $name: Media buttons hover effect
      $name:ru-RU: Эффект при наведении на кнопки управления
      $options:
      - "auto":  "Auto (theme changes automatically)"
      - "black": "Black"
      - "white": "White"
      - "off":   "Disable hover effect"
      $options:ru-RU:
      - "auto":  "Авто (тема изменяется автоматически)"
      - "black": "Чёрный"
      - "white": "Белый"
      - "off":   "Выключить эффект наведения"
    - enableHoverAnimation: true
      $name: Smooth hover animation
      $name:ru-RU: Плавная анимация наведения
      $description: >-
        Fades the hover/press background and border in and out. Disable this if you
        want an instant, non-animated hover effect, or if you're styling the player
        background with the Windows 11 Taskbar Styler mod and want it to react
        immediately.
      $description:ru-RU: >-
        Плавно проявляет/скрывает фон и рамку при наведении/нажатии. Выключите, если
        нужен мгновенный эффект наведения без анимации, или если вы стилизуете фон
        плеера модом Windows 11 Taskbar Styler и хотите, чтобы он реагировал мгновенно.
    - island: false
      $name: Island behind the player and visualizer
      $description: >-
        Draws one rounded island from just after Taskbar System Info to just past the
        visualizer bars. Works with the "After Taskbar System Info" position. Taskbar
        Styler can restyle it as Border#TaskbarIsland_Media. Set Background type to
        None so the player doesn't draw a second shape on top.
    - islandGap: 8
      $name: Gap before the island
      $description: "Space between the previous island and this one, from 0 to 40 pixels."
    - islandPadding: 8
      $name: Island padding after the bars
      $description: "Space between the last visualizer bar and the island edge, from 0 to 40 pixels."
    $name: Background Style
    $name:ru-RU: Стиль фона

  - MediaButtonsStyleSettings:
    - iconStyle: "fluent_outline"
      $name: Icon style
      $name:ru-RU: Вид иконок
      $options:
      - "fluent_outline": "Segoe Fluent Icons (Outline)"
      - "fluent_filled":  "Segoe Fluent Icons (Filled)"
      - "mdl2_outline":   "Segoe MDL2 Assets (Outline)"
      - "mdl2_filled":    "Segoe MDL2 Assets (Filled)"
      $options:ru-RU:
      - "fluent_outline": "Segoe Fluent Icons (Контур)"
      - "fluent_filled":  "Segoe Fluent Icons (Заполненный)"
      - "mdl2_outline":   "Segoe MDL2 Assets (Контур)"
      - "mdl2_filled":    "Segoe MDL2 Assets (Заполненный)"
    - buttonSpacing: 0
      $name: Spacing between media buttons
      $name:ru-RU: Расстояние между кнопками управления
    - buttonIconSize: 12
      $name: Button icon size
      $name:ru-RU: Размер иконок кнопок
    - buttonCornerRadius: "4"
      $name: Media buttons corner radius
      $name:ru-RU: Скругление кнопок управления
      $description: "Use single value (e.g., '4') for uniform corners, or four space-separated values (e.g., '4 2 4 2') for individual corners."
      $description:ru-RU: "Используйте одно значение (например, '4') для одинаковых углов, или четыре значения через пробел (например, '4 2 4 2') для каждого угла отдельно."
    - buttonColor: "0 0 0$255 255 255"
      $name: Media buttons icons color (RGB)
      $name:ru-RU: Цвет иконок для кнопок управления (RGB)
      $description: "Use '-1 -1 -1' for the system contrast color and '-2 -2 -2' for the album art color. You can also specify two colors separated by a $ symbol (e.g., '0 0 0$255 255 255') where the first color is for light theme and the second for dark theme."
      $description:ru-RU: "Используйте '-1 -1 -1' для системного контрастного цвета, '-2 -2 -2' — для цвета обложки альбома. Также можно указать два цвета через символ $ (например, '0 0 0$255 255 255'), где первый цвет для светлой темы, второй для тёмной."
    - buttonColorOpacity: 100
      $name: Media buttons icons opacity (0-100)
    - buttonGradient: true
      $name: Blue to mauve gradient across the media buttons
      $description: "Overrides the icon color with one left-to-right gradient (Catppuccin Mocha blue to mauve) across the taskbar media buttons."
      $name:ru-RU: Прозрачность иконок для кнопок управления (0-100)
    $name: Media Buttons Style
    $name:ru-RU: Стиль кнопок управления

  - TitleTextStyleSettings:
    - titleColor: "0 0 0$255 255 255"
      $name: Title color (RGB)
      $name:ru-RU: Цвет заголовка (RGB)
      $description: "Use '-1 -1 -1' for the system contrast color and '-2 -2 -2' for the album art color. You can also specify two colors separated by a $ symbol (e.g., '0 0 0$255 255 255') where the first color is for light theme and the second for dark theme."
      $description:ru-RU: "Используйте '-1 -1 -1' для системного контрастного цвета, '-2 -2 -2' — для цвета обложки альбома. Также можно указать два цвета через символ $ (например, '0 0 0$255 255 255'), где первый цвет для светлой темы, второй для тёмной."
    - titleColorOpacity: 100
      $name: Title opacity (0-100)
      $name:ru-RU: Прозрачность заголовка (0-100)
    - titleFont: segoe_ui_variable
      $name: Title font
      $name:ru-RU: Шрифт заголовка
      $options:
      - segoe_ui_variable: Segoe UI Variable Display
      - segoe_ui:          Segoe UI
      - aptos:             Aptos
      - calibri:           Calibri
      - cambria:           Cambria
      - candara:           Candara
      - consolas:          Consolas
      - corbel:            Corbel
      - arial:             Arial
      - trebuchet:         Trebuchet MS
      - verdana:           Verdana
      - tahoma:            Tahoma
      - georgia:           Georgia
      - times_new_roman:   Times New Roman
      - custom:            Custom...
      $options:ru-RU:
      - segoe_ui_variable: Segoe UI Variable Display
      - segoe_ui:          Segoe UI
      - aptos:             Aptos
      - calibri:           Calibri
      - cambria:           Cambria
      - candara:           Candara
      - consolas:          Consolas
      - corbel:            Corbel
      - arial:             Arial
      - trebuchet:         Trebuchet MS
      - verdana:           Verdana
      - tahoma:            Tahoma
      - georgia:           Georgia
      - times_new_roman:   Times New Roman
      - custom:            Другой...
    - titleFontSize: 12
      $name: Title font size
      $name:ru-RU: Размер шрифта заголовка
    - titleFontFamily: ""
      $name: Title font family (for Custom option)
      $name:ru-RU: Семейство шрифтов заголовка (для варианта «Другой»)
      $description: >-
        For a list of fonts that are shipped with Windows 11, refer to the
        following page:
        https://learn.microsoft.com/en-us/typography/fonts/windows_11_font_list
      $description:ru-RU: >-
        Список шрифтов, поставляемых с Windows 11, можно найти на следующей странице:
        https://learn.microsoft.com/en-us/typography/fonts/windows_11_font_list
    - titleFontWeight: ""
      $name: Title font weight
      $name:ru-RU: Насыщенность шрифта заголовка
      $options:
      - "":          Default
      - Thin:        Thin
      - ExtraLight:  Extra light
      - Light:       Light
      - SemiLight:   Semi light
      - Normal:      Normal
      - Medium:      Medium
      - SemiBold:    Semi bold
      - Bold:        Bold
      - ExtraBold:   Extra bold
      - Black:       Black
      - ExtraBlack:  Extra black
      $options:ru-RU:
      - "":          По умолчанию
      - Thin:        Тонкий
      - ExtraLight:  Очень тонкий
      - Light:       Тонкий
      - SemiLight:   Полутонкий
      - Normal:      Обычный
      - Medium:      Средний
      - SemiBold:    Полужирный
      - Bold:        Жирный
      - ExtraBold:   Очень жирный
      - Black:       Чёрный
      - ExtraBlack:  Сверхчёрный
    - titleFontStyle: ""
      $name: Title font style
      $name:ru-RU: Стиль шрифта заголовка
      $options:
      - "":       Default
      - Normal:   Normal
      - Oblique:  Oblique
      - Italic:   Italic
      $options:ru-RU:
      - "":       По умолчанию
      - Normal:   Обычный
      - Oblique:  Наклонный
      - Italic:   Курсив
    - titleCharacterSpacing: 0
      $name: Title character spacing
      $name:ru-RU: Межсимвольный интервал заголовка
      $description: Can be a positive or a negative number.
      $description:ru-RU: Может быть положительным или отрицательным числом.
    $name: Title Text Style
    $name:ru-RU: Стиль текста заголовка

  - ArtistTextStyleSettings:
    - artistColor: "0 0 0$255 255 255"
      $name: Artist color (RGB)
      $name:ru-RU: Цвет имени исполнителя (RGB)
      $description: "Use '-1 -1 -1' for system contrast color, '-2 -2 -2' for album art color. You can also specify two colors separated by a $ symbol (e.g., '0 0 0$255 255 255') where the first color is for light theme and the second for dark theme."
      $description:ru-RU: "Используйте '-1 -1 -1' для системного контрастного цвета, '-2 -2 -2' — для цвета обложки альбома. Также можно указать два цвета через символ $ (например, '0 0 0$255 255 255'), где первый цвет для светлой темы, второй для тёмной."
    - artistColorOpacity: 80
      $name: Artist opacity (0-100)
      $name:ru-RU: Прозрачность имени исполнителя (0-100)
    - artistFont: segoe_ui_variable
      $name: Artist font
      $name:ru-RU: Шрифт имени исполнителя
      $options:
      - segoe_ui_variable: Segoe UI Variable Display
      - segoe_ui:          Segoe UI
      - aptos:             Aptos
      - calibri:           Calibri
      - cambria:           Cambria
      - candara:           Candara
      - consolas:          Consolas
      - corbel:            Corbel
      - arial:             Arial
      - trebuchet:         Trebuchet MS
      - verdana:           Verdana
      - tahoma:            Tahoma
      - georgia:           Georgia
      - times_new_roman:   Times New Roman
      - custom:            Custom...
      $options:ru-RU:
      - segoe_ui_variable: Segoe UI Variable Display
      - segoe_ui:          Segoe UI
      - aptos:             Aptos
      - calibri:           Calibri
      - cambria:           Cambria
      - candara:           Candara
      - consolas:          Consolas
      - corbel:            Corbel
      - arial:             Arial
      - trebuchet:         Trebuchet MS
      - verdana:           Verdana
      - tahoma:            Tahoma
      - georgia:           Georgia
      - times_new_roman:   Times New Roman
      - custom:            Другой...
    - artistFontSize: 11
      $name: Artist font size
      $name:ru-RU: Размер шрифта исполнителя
    - artistFontFamily: ""
      $name: Artist font family (for Custom option)
      $name:ru-RU: Семейство шрифтов исполнителя (для варианта «Другой»)
      $description: >-
        For a list of fonts that are shipped with Windows 11, refer to the
        following page:
        https://learn.microsoft.com/en-us/typography/fonts/windows_11_font_list
      $description:ru-RU: >-
        Список шрифтов, поставляемых с Windows 11, можно найти на следующей странице:
        https://learn.microsoft.com/en-us/typography/fonts/windows_11_font_list
    - artistFontWeight: ""
      $name: Artist font weight
      $name:ru-RU: Насыщенность шрифта исполнителя
      $options:
      - "":          Default
      - Thin:        Thin
      - ExtraLight:  Extra light
      - Light:       Light
      - SemiLight:   Semi light
      - Normal:      Normal
      - Medium:      Medium
      - SemiBold:    Semi bold
      - Bold:        Bold
      - ExtraBold:   Extra bold
      - Black:       Black
      - ExtraBlack:  Extra black
      $options:ru-RU:
      - "":          По умолчанию
      - Thin:        Тонкий
      - ExtraLight:  Очень тонкий
      - Light:       Тонкий
      - SemiLight:   Полутонкий
      - Normal:      Обычный
      - Medium:      Средний
      - SemiBold:    Полужирный
      - Bold:        Жирный
      - ExtraBold:   Очень жирный
      - Black:       Чёрный
      - ExtraBlack:  Сверхчёрный
    - artistFontStyle: ""
      $name: Artist font style
      $name:ru-RU: Стиль шрифта исполнителя
      $options:
      - "":       Default
      - Normal:   Normal
      - Oblique:  Oblique
      - Italic:   Italic
      $options:ru-RU:
      - "":       По умолчанию
      - Normal:   Обычный
      - Oblique:  Наклонный
      - Italic:   Курсив
    - artistCharacterSpacing: 0
      $name: Artist character spacing
      $name:ru-RU: Межсимвольный интервал исполнителя
      $description: Can be a positive or a negative number.
      $description:ru-RU: Может быть положительным или отрицательным числом.
    $name: Artist Text Style
    $name:ru-RU: Стиль текста исполнителя

  - AlbumArtDisplaySettings:
    - albumArtEmptyBehavior: "show"
      $name: Album art behavior when no cover available
      $name:ru-RU: Поведение обложки при отсутствии изображения
      $options:
      - "show":          "Show area"
      - "hide":          "Hide area"
      - "show_icon":     "Show area with icon"
      $options:ru-RU:
      - "show":          "Показать область"
      - "hide":          "Скрыть область"
      - "show_icon":     "Показать область со значком"
    - emptyIconGlyph: "E189"
      $name: Icon glyph code (hex)
      $name:ru-RU: Код символа значка (hex)
      $description: "Hex code of the glyph to show, e.g. 'E189' for music note. See https://learn.microsoft.com/en-us/windows/apps/design/iconography/segoe-ui-symbol-font"
      $description:ru-RU: "Hex-код символа, например 'E189' для ноты. См. https://learn.microsoft.com/en-us/windows/apps/design/iconography/segoe-ui-symbol-font"
    - emptyIconSize: 16
      $name: Icon size
      $name:ru-RU: Размер значка
    - emptyIconFont: "segoe_fluent"
      $name: Icon font style
      $name:ru-RU: Стиль шрифта значка
      $options:
      - "segoe_fluent": "Segoe Fluent Icons"
      - "segoe_mdl2":   "Segoe MDL2 Assets"
      $options:ru-RU:
      - "segoe_fluent": "Segoe Fluent Icons"
      - "segoe_mdl2":   "Segoe MDL2 Assets"
    - emptyIconColor: "140 140 140"
      $name: Icon color (RGB)
      $name:ru-RU: Цвет значка (RGB)
      $description: "Use '-1 -1 -1' for the system accent color and '-2 -2 -2' for the album art color. You can also specify two colors separated by a $ symbol (e.g., '0 0 0$255 255 255') where the first color is for light theme and the second for dark theme."
      $description:ru-RU: "Используйте '-1 -1 -1' для цвета акцента системы и '-2 -2 -2' для цвета обложки альбома. Также можно указать два цвета через символ $ (например, '0 0 0$255 255 255'), где первый цвет для светлой темы, второй для тёмной."
    - emptyIconOpacity: 100
      $name: Icon opacity (0-100)
      $name:ru-RU: Прозрачность значка (0-100)
    - albumArtQuality: "medium"
      $name: Album art quality
      $name:ru-RU: Качество обложки альбома
      $options:
      - "low":    "Low (faster, less memory)"
      - "medium": "Medium (default)"
      - "high":   "High (best quality)"
      $options:ru-RU:
      - "low":    "Низкое (быстрее, меньше памяти)"
      - "medium": "Среднее (по умолчанию)"
      - "high":   "Высокое (наилучшее качество)"
    - showPauseOverlay: true
      $name: Show pause icon overlay on album art when paused
      $name:ru-RU: Показывать значок паузы на обложке при паузе
    - pauseOverlayIconSize: 16
      $name: Pause icon size
      $name:ru-RU: Размер значка паузы
    - pauseOverlayOpacity: 60
      $name: Pause overlay background opacity (0-100)
      $name:ru-RU: Прозрачность фона оверлея паузы (0-100)
    - albumArtOpacity: 100
      $name: Album art opacity (0-100)
      $name:ru-RU: Прозрачность обложки альбома (0-100)
    - albumArtCornerRadius: "4"
      $name: Album art corner radius
      $name:ru-RU: Радиус скругления обложки альбома
      $description: "Use single value (e.g., '4') for uniform corners, or four space-separated values (e.g., '4 2 4 2') for individual corners."
      $description:ru-RU: "Используйте одно значение (например, '4') для одинаковых углов, или четыре значения через пробел (например, '4 2 4 2') для каждого угла отдельно."
    - showAppIcon: false
      $name: Show media app icon overlay
      $name:ru-RU: Показывать значок медиаприложения поверх обложки
    - appIconCorner: "bottom_right"
      $name: App icon corner
      $name:ru-RU: Угол размещения значка приложения
      $options:
      - "top_left":     "Top left"
      - "top_right":    "Top right"
      - "bottom_left":  "Bottom left"
      - "bottom_right": "Bottom right"
      $options:ru-RU:
      - "top_left":     "Верхний левый"
      - "top_right":    "Верхний правый"
      - "bottom_left":  "Нижний левый"
      - "bottom_right": "Нижний правый"
    - appIconSize: 12
      $name: App icon size
      $name:ru-RU: Размер значка приложения
    $name: Album Art Display
    $name:ru-RU: Отображение обложки альбома
  $name: Appearance Settings
  $name:ru-RU: Настройки внешнего вида

- PlayerMenuSettings:
  - placementMode: screen
    $name: Placement mode
    $name:ru-RU: Режим расположения
    $description: Choose whether the player menu (mini player popup) opens directly Near the media player, or at a fixed position on the screen.
    $description:ru-RU: Выберите, где открывается меню плеера (мини-плеер) — Рядом с медиаплеером или в фиксированном месте на экране.
    $options:
    - near: Near the media player
    - screen: Placement on the screen
    $options:ru-RU:
    - near: Рядом с медиаплеером
    - screen: Расположение на экране

  - PlayerMenuSettingsNear:
    - miniPlayerHorizontalOffsetNear: 0
      $name: Menu horizontal offset (right/left)
      $name:ru-RU: Горизонтальное смещение меню (вправо/влево)
    - miniPlayerVerticalPlacementNear: top
      $name: Vertical placement
      $name:ru-RU: Вертикальное расположение
      $description: Whether the menu opens above or below the media player. Also controls the slide-in animation direction.
      $description:ru-RU: Появляется ли меню сверху или снизу от медиаплеера. Также определяет направление анимации появления.
      $options:
      - top: Top
      - bottom: Bottom 
      $options:ru-RU:
      - top: Сверху
      - bottom: Снизу
    $name: Near the media player
    $name:ru-RU: Рядом с медиаплеером

  - PlayerMenuSettingsScreen:
    - miniPlayerHorizontalPlacement: right
      $name: Horizontal placement on the screen
      $name:ru-RU: Горизонтальное расположение на экране
      $options:
      - left: Left
      - center: Center
      - right: Right
      $options:ru-RU:
      - left: Слева
      - center: По центру
      - right: Справа
    
    - horizontalDistanceFromScreenEdge: 0
      $name: Distance from the right/left side of the screen
      $name:ru-RU: Расстояние от правого/левого края экрана
    
    - miniPlayerVerticalPlacement: bottom
      $name: Vertical placement on the screen
      $name:ru-RU: Вертикальное расположение на экране
      $options:
      - top: Top
      - center: Center
      - bottom: Bottom
      $options:ru-RU:
      - top: Сверху
      - center: По центру
      - bottom: Снизу
    
    - verticalDistanceFromScreenEdge: 0
      $name: Distance from the bottom/top side of the screen
      $name:ru-RU: Расстояние от нижнего/верхнего края экрана
    
    - miniPlayerAnimation: auto
      $name: Appearance animation
      $name:ru-RU: Анимация появления
      $options:
      - auto: Automatic
      - top: From top
      - bottom: From bottom 
      - left: From left
      - right: From right
      $options:ru-RU:
      - auto: Автоматически
      - top: Сверху
      - bottom: Снизу
      - left: Слева
      - right: Справа
    $name: Placement on the screen
    $name:ru-RU: Расположение на экране

  - keepMiniPlayerOpen: false
    $name: Keep mini player menu open
    $name:ru-RU: Не закрывать мини-плеер при клике вне
  - hideMediaSessionsList: false
    $name: Hide media sessions list
    $name:ru-RU: Выключить список медиа сессий
    $description: Hide the list of other media sessions/apps in the player menu
    $description:ru-RU: Не отображать список других медиа сессий/приложений в меню плеера
  $name: Player Menu Settings
  $name:ru-RU: Настройки меню плеера

- BehaviorSettings:
  - disableAlbumArtClick: false
    $name: Disable album art click (click through to player)
    $name:ru-RU: Отключить клик по обложке (сквозной клик на плеер)
    $description: When enabled, clicks on the album art will pass through to the player area underneath
    $description:ru-RU: Когда включено, клики по обложке альбома будут передаваться в область плеера под ней
  - ClickActionSettings:
      - - object: player
          $name: Object
          $name:ru-RU: Объект
          $options:
          - none:       Nothing
          - player:     Player area
          - album_art:  Album art area
          $options:ru-RU:
          - none:       Ничего
          - player:     Область плеера
          - album_art:  Область обложки альбома
        - click: left_click
          $name: Click type
          $name:ru-RU: Тип клика
          $options:
          - none:                Nothing
          - left_click:          Left click
          - left_double_click:   Left double click
          - right_click:         Right click
          - right_double_click:  Right double click
          - middle_click:        Middle click
          - middle_double_click: Middle double click
          $options:ru-RU:
          - none:                Ничего
          - left_click:          Левый клик
          - left_double_click:   Двойной левый клик
          - right_click:         Правый клик
          - right_double_click:  Двойной правый клик
          - middle_click:        Клик средней кнопкой
          - middle_double_click: Двойной клик средней кнопкой
        - action: open_mini_player
          $name: Action
          $name:ru-RU: Действие
          $options:
          - none:            Nothing
          - switch_session:  Switch active media session
          - play_pause:      Play/Pause
          - next_track:      Next track
          - prev_track:      Previous track
          - stop:            Stop playback
          - rewind_5s:       Rewind 5s
          - forward_5s:      Forward 5s
          - toggle_shuffle:  Toggle Shuffle
          - toggle_repeat:   Toggle Repeat
          - open_app:        Open media app
          - open_context_menu: Open context menu
          - open_mini_player: Open player menu
          $options:ru-RU:
          - none:            Ничего
          - switch_session:  Переключить медиасессию
          - play_pause:      Воспроизведение/Пауза
          - next_track:      Следующий трек
          - prev_track:      Предыдущий трек
          - stop:            Остановить воспроизведение
          - rewind_5s:       Перемотка назад 5 сек
          - forward_5s:      Перемотка вперёд 5 сек
          - toggle_shuffle:  Случайный порядок
          - toggle_repeat:   Повтор
          - open_app:        Открыть медиаприложение
          - open_context_menu: Открыть контекстное меню
          - open_mini_player: Открыть меню плеера
      - - object: player
        - click: right_click
        - action: open_context_menu
      - - object: album_art
        - click: left_double_click
        - action: open_app
    $name: Click Actions
    $name:ru-RU: Действия при клике
  - MouseWheelActionSettings:
      - - object: player
          $name: Object
          $name:ru-RU: Объект
          $options:
          - none:       Nothing
          - player:     Player area
          - album_art:  Album art area
          $options:ru-RU:
          - none:       Ничего
          - player:     Область плеера
          - album_art:  Область обложки альбома
        - click: mouse_wheel
          $name: Mouse type
          $name:ru-RU: Тип мыши
          $options:
          - none:             Nothing
          - mouse_wheel:      Mouse wheel
          $options:ru-RU:
          - none:             Ничего
          - mouse_wheel:      Колесо мыши
        - action: switch_tracks
          $name: Action
          $name:ru-RU: Действие
          $options:
          - none:                      Nothing
          - "switch_tracks":           "Switch tracks"
          - "switch_tracks_inverted":  "Switch tracks (inverted)"
          - "switch_sessions":         "Switch sessions"
          - "system_sound":            "Change system sound volume"
          - "app_sound":               "Change app sound volume"
          $options:ru-RU:
          - none:                      Ничего
          - "switch_tracks":           "Переключить треки"
          - "switch_tracks_inverted":  "Переключить треки (инверсия)"
          - "switch_sessions":         "Переключить сессии"
          - "system_sound":            "Изменить громкость системы"
          - "app_sound":               "Изменить громкость приложения"
      - - object: album_art
        - click: mouse_wheel
        - action: switch_sessions
    $name: Mouse wheel Actions
    $name:ru-RU: Действия колеса мыши
  - hideWhenNoMedia: true
    $name: Hide when no media is playing
    $name:ru-RU: Скрывать, когда ничего не воспроизводится
  - hideFullscreen: true
    $name: Hide when a fullscreen app is running
    $name:ru-RU: Скрывать при запущенном полноэкранном приложении
  - idleHideSeconds: 0
    $name: Idle auto-hide timeout (seconds, 0 = disabled)
    $name:ru-RU: Таймаут автоскрытия при бездействии (секунды, 0 = отключено)
  - showFullTitleOnHover: true
    $name: Show full track title on hover (tooltip)
    $name:ru-RU: Показывать полное название трека при наведении (подсказка)
  $name: Behavior Settings
  $name:ru-RU: Настройки поведения

- AnimationSettings:
  - enableSmoothPositionAnimation: true
    $name: Enable smooth position animation
    $name:ru-RU: Включить плавную анимацию позиции
  $name: Animation Settings media player
  $name:ru-RU: Настройки анимации медиаплеера

- NotificationSettings:
  - showSuccessNotification: false
    $name: Show notification on successful mod load
    $name:ru-RU: Показывать уведомление при успешной загрузке мода
    $description: Display a Windows notification when the mod is successfully loaded or reloaded
    $description:ru-RU: Отображать уведомление Windows при успешной загрузке или перезагрузке мода
  $name: Notification Settings
  $name:ru-RU: Настройки уведомлений

- ContextMenuSettings:
  - contextMenuItems: [switch_sessions, open_app]
    $name: Context menu items
    $name:ru-RU: Пункты контекстного меню
    $description: Select which items to show in the context menu and their order. Duplicates are ignored.
    $description:ru-RU: Выберите, какие пункты отображать в контекстном меню, и их порядок. Дубликаты игнорируются.
    $options:
    - none:             Nothing
    - repeat:           Repeat
    - shuffle:          Shuffle
    - forward:          Forward 5s
    - rewind:           Rewind 5s
    - next:             Next Track
    - prev:             Previous Track
    - switch_sessions:  Switch Sessions
    - open_app:         Open media app
    $options:ru-RU:
    - none:             Ничего
    - repeat:           Повтор
    - shuffle:          Случайный порядок
    - forward:          Вперёд 5 сек
    - rewind:           Назад 5 сек
    - next:             Следующий трек
    - prev:             Предыдущий трек
    - switch_sessions:  Переключить сессию
    - open_app:         Открыть медиаприложение
  - repeatStyle: "submenu"
    $name: Repeat style
    $name:ru-RU: Стиль повтора
    $options:
    - "submenu": "Submenu (Repeat off / Repeat all / Repeat one)"
    - "toggle":  "Toggle (cycle through modes)"
    $options:ru-RU:
    - "submenu": "Подменю (Выкл / Все / Один)"
    - "toggle":  "Переключатель (цикл по режимам)"
  - shuffleStyle: "toggle"
    $name: Shuffle style
    $name:ru-RU: Стиль случайного воспроизведения
    $options:
    - "submenu": "Submenu (Shuffle off / Shuffle on)"
    - "toggle":  "Toggle (single button)"
    $options:ru-RU:
    - "submenu": "Подменю (Выкл / Вкл)"
    - "toggle":  "Переключатель (одна кнопка)"
  - showOpenWindhawk: true
    $name: Show "Open Windhawk" button
    $name:ru-RU: Показывать кнопку «Открыть Windhawk»
  - contextMenuIconStyle: "as_media_buttons"
    $name: Context menu icon style
    $name:ru-RU: Стиль иконок контекстного меню
    $options:
    - "as_media_buttons": "Same as Media Buttons"
    - "fluent_outline":   "Segoe Fluent Icons (Outline)"
    - "fluent_filled":    "Segoe Fluent Icons (Filled)"
    - "mdl2_outline":     "Segoe MDL2 Assets (Outline)"
    - "mdl2_filled":      "Segoe MDL2 Assets (Filled)"
    $options:ru-RU:
    - "as_media_buttons": "Как у кнопок управления"
    - "fluent_outline":   "Segoe Fluent Icons (Контур)"
    - "fluent_filled":    "Segoe Fluent Icons (Заполненный)"
    - "mdl2_outline":     "Segoe MDL2 Assets (Контур)"
    - "mdl2_filled":      "Segoe MDL2 Assets (Заполненный)"
  - contextMenuIconColor: "0 0 0$255 255 255"
    $name: Context menu icons color (RGB)
    $name:ru-RU: Цвет иконок контекстного меню (RGB)
    $description: "Use '-1 -1 -1' for the system contrast color and '-2 -2 -2' for the album art color. You can also specify two colors separated by a $ symbol (e.g., '0 0 0$255 255 255') where the first color is for light theme and the second for dark theme. Leave empty to use the Media Buttons color."
    $description:ru-RU: "Используйте '-1 -1 -1' для системного контрастного цвета, '-2 -2 -2' — для цвета обложки альбома. Также можно указать два цвета через $ (например, '0 0 0$255 255 255'). Оставьте пустым, чтобы использовать цвет кнопок управления."
  - contextMenuIconOpacity: 100
    $name: Context menu icons opacity (0-100)
    $name:ru-RU: Прозрачность иконок контекстного меню (0-100)
  $name: Context Menu Settings
  $name:ru-RU: Настройки контекстного меню

- DebugSettings:
  - ignoredProcesses: ""
    $name: Ignore media from processes (separate with ; )
    $name:ru-RU: Игнорировать медиа от процессов (разделять через ; )
  - enableTreeDump: false
    $name: Dump XAML element names to log on inject
    $name:ru-RU: Записывать имена XAML-элементов в лог при инъекции
  - showDebugBorders: false
    $name: Show debug borders
    $name:ru-RU: Показывать отладочные границы
  - showMiniPlayerBorder: false
    $name: Show debug mini player menu border
    $name:ru-RU: Показывать отладочные границу мини-плеера
  - showLayoutAnchors: false
    $name: Show layout anchors and centers
    $name:ru-RU: Показывать якоря и центры разметки
  - showRestartButton: false
    $name: Show Restart Player in context menu
    $name:ru-RU: Показывать кнопку перезагрузки плеера в контекстном меню
  $name: Debug Settings
  $name:ru-RU: Настройки отладки
- Visualizer:
  - position:
    - placement: overlay
      $name: Placement
      $description: Separate puts the bars in their own block right of the player. Behind widget draws them
        dimmed across the player's background, under the art, title and buttons, and takes no extra width.
      $options:
      - separate: Separate (right side)
      - overlay: Behind widget (overlay)
    - overlayOpacity: 45
      $name: Behind-widget strength
      $description: How strongly the bars show behind the player, in percent. 10 to 80 (Suggested 35). Only
        used when Placement is Behind widget.
    - taskbarOffset: 500
      $name: Horizontal offset
      $description: Where the bars go when the player is not placed after Taskbar System Info, in logical
        pixels from the taskbar's left edge. When the player sits after System Info, the bars follow it.
    - verticalOffset: 0
      $name: Vertical offset
      $description: Logical pixels from the taskbar center. Negative values move upward. The strip stays
        inside the taskbar.
    $name: Position
  - appearance:
    - shape: stereo
      $name: Shape
      $description: Choose how the spectrum is drawn.
      $options:
      - stereo: Spectrum bars
      - mountain: Mountain
      - mirror: Mirror
      - wave: Wave
      - breathe: Breathe
      - dots: Dots
    - barCount: 32
      $name: Bar count
      $description: 1 to 128 bars.
    - barWidth: 3
      $name: Bar width
      $description: 1 to 24 logical pixels.
    - barGap: 2
      $name: Bar gap
      $description: 0 to 24 logical pixels between bars.
    - barMaxSize: 26
      $name: Maximum bar height
      $description: 2 to 128 logical pixels, limited by the taskbar height.
    - barIdleSize: 2
      $name: Idle bar height
      $description: Visible height during silence. 0 removes idle bars; values cannot exceed the maximum
        bar height.
    - barCornerRadius: '1'
      $name: Bar corner radius
      $description: One radius for all corners, or four comma-separated radii in top-left, top-right, bottom-right,
        bottom-left order.
    - verticalAnchor: bottom
      $name: Bar anchor
      $description: Choose the direction in which each bar grows.
      $options:
      - bottom: Bottom
      - middle: Center
      - top: Top
    - colorMode: gradient
      $name: Color mode
      $description: Choose a fixed color, gradient, level-reactive gradient, Windows accent, or rainbow.
      $options:
      - solid: Solid
      - gradient: Gradient
      - reactive_gradient: Reactive gradient
      - accent: Windows accent
      - rainbow: Rainbow
    - color: '#FFCBA6F7'
      $name: Solid color
      $description: 'Color in #AARRGGBB or #RRGGBB format. Default is Catppuccin Mocha mauve.'
    - gradientColor1: '#FFCBA6F7'
      $name: Gradient start
      $description: First gradient color. Default is Catppuccin Mocha mauve.
    - gradientColor2: '#FF89B4FA'
      $name: Gradient end
      $description: Second gradient color. Default is Catppuccin Mocha blue.
    - rainbowSpeed: 40
      $name: Rainbow speed
      $description: 1 to 300. Used by the Rainbow color mode.
    - sensitivity: 175
      $name: Sensitivity
      $description: 0 to 300. Changes spectrum response without changing playback volume.
    - sensitivityCurve: knee
      $name: Sensitivity curve
      $description: Choose how captured levels map to bar height.
      $options:
      - knee: Soft knee
      - exponential: Exponential
      - power: Power
    - smoothing: 60
      $name: Smoothing
      $description: 0 to 100. Higher values soften bar movement.
    - eqPreset: default
      $name: Display EQ
      $description: Weights frequency bands for drawing. This does not change audio playback.
      $options:
      - default: Flat
      - bass: Bass
      - rock: Rock
      - pop: Pop
      - jazz: Jazz
      - electronic: Electronic
    - fftSize: '1024'
      $name: FFT size
      $description: Larger windows improve frequency resolution and increase analysis latency.
      $options:
      - '1024': 1024 samples
      - '2048': 2048 samples
      - '4096': 4096 samples
      - '8192': 8192 samples
    - freqScale: log
      $name: Frequency scale
      $description: Maps the analyzed frequency bands across the bar group.
      $options:
      - log: Logarithmic
      - linear: Linear
      - mel: Mel
    - peakHoldEnabled: false
      $name: Peak hold
      $description: Draw a falling cap above recent peak levels.
    - peakHoldColor: '#FF89B4FA'
      $name: Peak cap color
      $description: Color of the peak hold caps.
    $name: Appearance
  - audio:
    - captureMode: all
      $name: Output capture
      $description: All outputs follows per-app Windows routing. Default output reads only the default multimedia
        render endpoint.
      $options:
      - all: All active outputs
      - default: Default output
    - hardwareLoopbacks: true
      $name: Hardware loopbacks
      $description: Also read recording endpoints explicitly named Loopback, which can include an interface
        ASIO mix. Microphone and general recording endpoints are excluded.
    - deviceFilter: ''
      $name: Device name filter
      $description: Optional case-insensitive substring of an endpoint name. Blank includes every endpoint
        selected by the capture options above.
    - inputGain: 0
      $name: Analysis gain
      $description: -24 to +24 dB applied only to the captured analysis signal. Playback and routing stay
        unchanged.
    $name: Audio
  - background:
    - enabled: false
      $name: Background panel
      $description: Draw a panel behind the bars.
    - color: '#801E1E2E'
      $name: Panel color
      $description: Color and opacity of the panel. Default is translucent Catppuccin Mocha base.
    - padding: '4'
      $name: Panel padding
      $description: One value or four values in left, right, top, bottom order. 0 to 12 logical pixels per
        side.
    - cornerRadius: '6'
      $name: Panel corner radius
      $description: One radius or four corner radii in top-left, top-right, bottom-right, bottom-left order.
    - borderSize: 0
      $name: Panel border width
      $description: 0 to 8 logical pixels. 0 removes the border.
    - borderColor: '#FF45475A'
      $name: Panel border color
      $description: Color of the panel border.
    $name: Background
  - performance:
    - targetFps: 30
      $name: Frame rate
      $description: 10 to 120 frames per second. Default is 30.
    - pauseWhenSilentSeconds: 10
      $name: Idle delay
      $description: After this many silent seconds, draw at 5 FPS. The strip remains visible and resumes
        its normal rate when audio returns. 0 disables idle throttling.
    - hideWhenFullscreen: true
      $name: Hide when fullscreen
      $description: Hide the bars and media buttons when a fullscreen or borderless window covers the taskbar
        monitor, for example a game. The strip returns when you leave the game. The taskbar itself stays
        clickable at all times.
    - followTaskbarAutoHide: true
      $name: Follow taskbar auto-hide
      $description: Slide out of view with the taskbar whenever the Windows taskbar auto-hides, and come
        back when it is shown again, like any other taskbar widget. Keyed to the shell's live
        state. While the taskbar behaves as a permanent bar that holds its screen space (for
        example a wedged auto-hide), the strip stays visible with it.
    - pauseWhenObscured: true
      $name: Hide when covered
      $description: Hide the bars while an always-on-top window covers the strip, and bring them back
        when the space is free again. Ordinary windows sit below the taskbar and can never cover
        the strip, so this reacts to topmost surfaces such as pinned players.
    $name: Performance
  - diagnostics:
    - enabled: false
      $name: Diagnostic logging
      $description: Write endpoint status and level summaries to diagnostic.log in this mod Windhawk storage
        directory. Logs rotate at 1 MiB. Audio samples are never recorded.
    $name: Diagnostics
  $name: Audio visualizer
*/
// ==/WindhawkModSettings==

#undef GetCurrentTime
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.UI.Input.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.UI.Xaml.Media.Animation.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Automation.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.Media.Control.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Graphics.Imaging.h>
#include <robuffer.h>
#include <shcore.h>
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <shobjidl.h>
#include <commoncontrols.h>
#include <wincodec.h>
#include <propsys.h>
#include <dwmapi.h>
#include <windhawk_utils.h>
#include <audiopolicy.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>
#include <propkey.h>
#include <atomic>
#include <functional>
#include <memory>
#include <utility>
#include <mutex>
#include <string>
#include <vector>
#include <optional>
#include <set>
#include <algorithm>
#include <thread>
#include <cmath>
#include <chrono>
#include <d2d1_1.h>
#include <d2d1helper.h>
#include <d3d11.h>
#include <dcomp.h>
#include <dxgi1_3.h>
#include <shellscalingapi.h>
#include <wrl/client.h>
#include <dwrite.h>
#include <windowsx.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <cwctype>

// ===========================================================================
// Media player (runs in the taskbar process)
// ===========================================================================
namespace fmp {
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Media;
using namespace winrt::Windows::UI::Xaml::Media::Imaging;
using namespace winrt::Windows::UI::Xaml::Media::Animation;
using namespace winrt::Windows::UI::Xaml::Input;
using namespace winrt::Windows::Media::Control;
using namespace winrt::Windows::Storage::Streams;
enum class VizShape { Stereo, Mountain, Mirror, Wave, Breathe };
enum class VizColorMode { Solid, DynamicAlbum, DynamicGradient, CustomGradient, Acrylic };
enum class VizEQ { Default, Bass, Rock, Pop, Jazz, Electronic };
enum class VizAnchor { Top, Middle, Bottom };
struct ModSettings {
    int          monitor              = 1;
    std::wstring position             = L"tray_left";
    std::wstring albumArtLeftClick    = L"none";
    std::wstring albumArtRightClick   = L"none";
    std::wstring albumArtMiddleClick  = L"none";
    std::wstring albumArtLeftDoubleClick  = L"none";
    std::wstring albumArtRightDoubleClick = L"none";
    std::wstring albumArtMiddleDoubleClick = L"none";
    std::wstring albumArtWheelAction  = L"none";
    std::wstring playerLeftClick      = L"none";
    std::wstring playerRightClick     = L"none";
    std::wstring playerMiddleClick    = L"none";
    std::wstring playerLeftDoubleClick  = L"none";
    std::wstring playerRightDoubleClick = L"none";
    std::wstring playerMiddleDoubleClick = L"none";
    std::wstring playerWheelAction    = L"none";
    bool         mirrorLayout         = false;
    bool         fullHeightHitArea    = true;
    bool         autoSwitchSession    = true;
    bool         showMediaButtons     = true;
    int          playerMinWidth       = 0;
    int          playerMaxWidth       = 0;
    int          playerMinHeight      = 40;
    int          playerMaxHeight      = 40;
    bool         showAlbumArt         = true;
    std::wstring albumArtEmptyBehavior = L"show";
    std::wstring emptyIconGlyph       = L"E189";
    int          emptyIconSize        = 16;
    std::wstring emptyIconFont        = L"segoe_fluent";
    std::wstring emptyIconColor       = L"255 255 255";
    int          emptyIconOpacity     = 100;
    std::wstring albumArtQuality      = L"medium";
    bool         showPauseOverlay     = true;
    int          pauseOverlayIconSize = 16;
    int          pauseOverlayOpacity  = 60;
    int          albumArtMinWidth     = 32;
    int          albumArtMaxWidth     = 64;
    int          albumArtMinHeight    = 32;
    int          albumArtMaxHeight    = 32;
    int          albumArtOpacity      = 100;
    int          albumArtLeftMargin   = 0;
    int          albumArtRightMargin  = 0;
    bool         showTrackTitle       = true;
    bool         showFullTitleOnHover = true;
    bool         showTrackArtist      = true;
    bool         swapTitleArtist      = false;
    std::wstring emptyTitleText       = L"Untitled";
    std::wstring noMediaTitleText     = L"Not Playing";
    std::wstring emptyArtistText      = L"";
    std::wstring noMediaArtistText    = L"";
    std::wstring iconStyle            = L"fluent_outline";
    bool         showAppIcon          = false;
    std::wstring appIconCorner        = L"bottom_right";
    int          appIconSize          = 12;
    bool         hideWhenNoMedia      = true;
    std::wstring playerHoverEffectMode = L"auto";
    std::wstring mediaButtonsHoverEffectMode = L"auto";
    bool         enableHoverAnimation = true;
    bool         island               = false;
    int          islandGap            = 8;
    int          islandPadding        = 8;
    bool         enableSmoothPositionAnimation = true;
    int          playerMarginLeft     = 4;
    int          playerMarginRight    = 4;
    int          mediaButtonsLeftMargin  = 2;
    int          mediaButtonsRightMargin = 2;
    int          textAreaMinWidth     = 0;
    int          textAreaMaxWidth     = 120;
    int          textAreaMinHeight    = 0;
    int          textAreaMaxHeight    = 0;
    int          textAreaLeftMargin   = 5;
    int          textAreaRightMargin  = 5;
    bool         hideFullscreen       = true;
    int          idleHideSeconds      = 0;
    std::wstring backgroundType       = L"none";
    int          blurOpacity          = 65;
    int          blurRadius           = 11;
    double       cornerRadiusTL       = 4;
    double       cornerRadiusTR       = 4;
    double       cornerRadiusBR       = 4;
    double       cornerRadiusBL       = 4;
    double       albumArtCornerRadiusTL = 4;
    double       albumArtCornerRadiusTR = 4;
    double       albumArtCornerRadiusBR = 4;
    double       albumArtCornerRadiusBL = 4;
    int          buttonSpacing        = 0;
    int          buttonSize           = 28;
    int          buttonIconSize       = 12;
    double       buttonCornerRadiusTL = 4;
    double       buttonCornerRadiusTR = 4;
    double       buttonCornerRadiusBR = 4;
    double       buttonCornerRadiusBL = 4;
    int          titleFontSize        = 12;
    int          artistFontSize       = 11;
    std::wstring titleFont            = L"segoe_ui_variable";
    std::wstring artistFont           = L"segoe_ui_variable";
    std::wstring titleFontFamily      = L"";
    std::wstring artistFontFamily     = L"";
    std::wstring titleFontWeight      = L"";
    std::wstring artistFontWeight     = L"";
    std::wstring titleFontStyle       = L"";
    std::wstring artistFontStyle      = L"";
    int          titleCharacterSpacing  = 0;
    int          artistCharacterSpacing = 0;
    int          textSpacing          = -1;
    bool         enableArtistScrolling = false;
    bool         enableTitleScrolling = true;
    int          scrollSpeed          = 1;
    int          scrollPauseDuration  = 1000;
    std::wstring scrollMode           = L"bounce";
    int          loopGap              = 40;
    std::wstring solidColor           = L"35 35 35";
    std::wstring solidColor2          = L"35 35 35";
    std::wstring gradientColor2       = L"128 128 128";
    int          solidOpacity         = 100;
    int          gradientAngle        = 50;
    int          gradientBalance      = 50;
    int          acrylicTintOpacity   = 50;
    int          micaOpacity          = 50;
    std::wstring buttonColor          = L"255 255 255";
    int          buttonColorOpacity   = 100;
    bool         buttonGradient       = true;
    std::wstring titleColor           = L"255 255 255";
    int          titleColorOpacity    = 100;
    std::wstring artistColor          = L"255 255 255";
    int          artistColorOpacity   = 80;
    std::wstring ignoredProcesses     = L"";
    bool         enableTreeDump       = false;
    bool         showDebugBorders     = false;
    bool         showMiniPlayerBorder = false;
    bool         keepMiniPlayerOpen   = false;
    bool         hideMediaSessionsList = false;
    std::wstring miniPlayerPlacementMode = L"screen";
    int          miniPlayerHorizontalOffsetAbove = 0;
    std::wstring miniPlayerVerticalPlacementNear = L"top";
    std::wstring miniPlayerHorizontalPlacement = L"right";
    int          miniPlayerHorizontalDistanceFromScreenEdge = 0;
    std::wstring miniPlayerVerticalPlacement = L"bottom";
    int          miniPlayerVerticalDistanceFromScreenEdge = 0;
    std::wstring miniPlayerAnimation = L"auto";
    bool         showLayoutAnchors    = false;
    bool         showRestartButton    = false;
    bool         showSuccessNotification = false;
    bool         hideUnsupportedButtons  = false;
    bool         disableAlbumArtClick    = false;
    std::vector<std::wstring> contextMenuItems;
    std::wstring contextMenuRepeatStyle   = L"submenu";
    std::wstring contextMenuShuffleStyle  = L"submenu";
    bool         showOpenWindhawk         = true;
    std::wstring contextMenuIconStyle     = L"as_media_buttons";
    std::wstring contextMenuIconColor     = L"255 255 255";
    int          contextMenuIconOpacity   = 100;
    bool         vizEnabled      = false;
    std::wstring vizPosition     = L"right";
    VizShape     vizShape        = VizShape::Stereo;
    VizColorMode vizColorMode    = VizColorMode::Solid;
    VizEQ        vizEq           = VizEQ::Default;
    VizAnchor    vizAnchor       = VizAnchor::Middle;
    std::wstring vizColor        = L"255 255 255";
    std::wstring vizColor1       = L"30 215 96";
    std::wstring vizColor2       = L"0 180 255";
    int          vizBars         = 7;
    int          vizBarWidth     = 5;
    int          vizBarGap       = 5;
    int          vizIdleBarSize  = 3;
    int          vizSensitivity  = 150;
    float        vizInputGain    = 1.0f;  // linear, from Visualizer.audio.inputGain dB
    int          vizPadLeft      = 0;
    int          vizPadRight     = 0;
    // 1.9.0: behind-widget bars, progress bar, playback time.
    bool         vizOverlay        = false;
    int          vizOverlayOpacity = 35;
    bool         showProgressBar   = false;
    bool         progressArtwork   = true;
    int          progressHeight    = 2;
    bool         clickToSeek       = true;
    int          timeDisplayMode   = 0;  // 0 hidden, 1 elapsed, 2 elapsed / total
};
static ModSettings g_settings;
static void ParseTwoInts(const std::wstring& s, int& a, int& b) {
    size_t sp = s.find(L' ');
    if (sp == std::wstring::npos) return;
    try {
        a = std::stoi(s.substr(0, sp));
        b = std::stoi(s.substr(sp + 1));
    } catch (...) {}
}
enum class MediaButtonType {
    Previous = 1,
    PlayPause = 2,
    Next = 3,
    Rewind5s = 4,
    Forward5s = 5,
    Shuffle = 6,
    Repeat = 7,
    SwitchSessions = 8,
};
struct MediaButtonDefinition {
    std::wstring keyword;
    MediaButtonType type;
    int cmd;
};
static const std::vector<MediaButtonDefinition> g_mediaButtonDefinitions = {
    {L"prev", MediaButtonType::Previous, 1},
    {L"play", MediaButtonType::PlayPause, 2},
    {L"next", MediaButtonType::Next, 3},
    {L"rewind", MediaButtonType::Rewind5s, 5},
    {L"forward", MediaButtonType::Forward5s, 6},
    {L"shuffle", MediaButtonType::Shuffle, 7},
    {L"repeat", MediaButtonType::Repeat, 8},
    {L"switch_sessions", MediaButtonType::SwitchSessions, 9},
};
struct MediaButtonConfig {
    MediaButtonType type;
    int cmd;
};
static std::vector<MediaButtonConfig> g_mediaButtons;
static std::mutex g_mediaButtonsMutex;
static std::wstring MapFontName(const std::wstring& key) {
    if (key == L"custom") return L"";
    if (key == L"segoe_ui_variable") return L"Segoe UI Variable Display";
    if (key == L"segoe_ui") return L"Segoe UI";
    if (key == L"segoe_ui_semibold") return L"Segoe UI Semibold";
    if (key == L"segoe_ui_bold") return L"Segoe UI Bold";
    if (key == L"segoe_ui_light") return L"Segoe UI Light";
    if (key == L"segoe_ui_semilight") return L"Segoe UI Semilight";
    if (key == L"aptos") return L"Aptos";
    if (key == L"calibri") return L"Calibri";
    if (key == L"cambria") return L"Cambria";
    if (key == L"candara") return L"Candara";
    if (key == L"consolas") return L"Consolas";
    if (key == L"corbel") return L"Corbel";
    if (key == L"arial") return L"Arial";
    if (key == L"trebuchet") return L"Trebuchet MS";
    if (key == L"verdana") return L"Verdana";
    if (key == L"tahoma") return L"Tahoma";
    if (key == L"georgia") return L"Georgia";
    if (key == L"times_new_roman") return L"Times New Roman";
    return L"Segoe UI Variable Display";
}
static void LoadSettings() {
    auto Str = [](const wchar_t* key, const wchar_t* def) -> std::wstring {
        PCWSTR p = Wh_GetStringSetting(key);
        std::wstring r = (*p != L'\0') ? p : def;
        Wh_FreeStringSetting(p);
        return r;
    };
    auto StrAllowEmpty = [](const wchar_t* key) -> std::wstring {
        PCWSTR p = Wh_GetStringSetting(key);
        std::wstring r = p ? p : L"";
        Wh_FreeStringSetting(p);
        return r;
    };
    auto Int = [](const wchar_t* key, int lo, int hi, int /*def*/) -> int {
        return std::clamp(Wh_GetIntSetting(key), lo, hi);
    };
    auto ParseMargin = [&Str](const wchar_t* key, const wchar_t* def, int& left, int& right) {
        std::wstring val = Str(key, def);
        try {
            size_t space = val.find(L' ');
            if (space != std::wstring::npos) {
                left  = std::stoi(val.substr(0, space));
                right = std::stoi(val.substr(space + 1));
            } else if (!val.empty()) {
                left = right = std::stoi(val);
            }
        } catch (...) {
            std::wstring d(def);
            size_t space = d.find(L' ');
            try {
                if (space != std::wstring::npos) {
                    left  = std::stoi(d.substr(0, space));
                    right = std::stoi(d.substr(space + 1));
                } else {
                    left = right = std::stoi(d);
                }
            } catch (...) { left = right = 0; }
        }
    };
    auto ParseCornerRadius = [&Str](const wchar_t* key, const wchar_t* def, double& tl, double& tr, double& br, double& bl) {
        std::wstring val = Str(key, def);
        std::vector<double> values;
        try {
            size_t pos = 0;
            while (pos < val.length()) {
                size_t space = val.find(L' ', pos);
                if (space == std::wstring::npos) space = val.length();
                std::wstring part = val.substr(pos, space - pos);
                if (!part.empty()) {
                    double v = std::stod(part);
                    values.push_back(v < 0.0 ? 0.0 : v);
                }
                pos = space + 1;
            }
        } catch (...) {}
        if (values.empty()) {
            try {
                std::wstring d(def);
                double v = std::stod(d);
                values.push_back(v < 0.0 ? 0.0 : v);
            } catch (...) {
                values.push_back(4.0);
            }
        }
        if (values.size() == 1) {
            tl = tr = br = bl = values[0];
        } else if (values.size() == 4) {
            tl = values[0];
            tr = values[1];
            br = values[2];
            bl = values[3];
        } else {
            tl = tr = br = bl = values[0];
        }
    };
    auto HoverMode = [&Str](const wchar_t* key) -> std::wstring {
        std::wstring mode = Str(key, L"auto");
        if (mode == L"black") return L"black";
        if (mode == L"white") return L"white";
        if (mode == L"off")   return L"off";
        return L"auto";
    };
    g_settings.monitor               = std::max(1, Wh_GetIntSetting(L"MainSettings.PlayerSetting.monitor"));
    g_settings.position             = Str(L"MainSettings.PlayerSetting.position",    L"tray_left");
    ParseMargin(L"MainSettings.PlayerSetting.playerMargin", L"4 4", g_settings.playerMarginLeft, g_settings.playerMarginRight);
    ParseMargin(L"MainSettings.PlayerSetting.playerWidth", L"0 0", g_settings.playerMinWidth, g_settings.playerMaxWidth);
    ParseMargin(L"MainSettings.PlayerSetting.playerHeight", L"40 40", g_settings.playerMinHeight, g_settings.playerMaxHeight);
    ParseMargin(L"MainSettings.AlbumArtSetting.albumArtWidth", L"32 64", g_settings.albumArtMinWidth, g_settings.albumArtMaxWidth);
    ParseMargin(L"MainSettings.AlbumArtSetting.albumArtHeight", L"32 32", g_settings.albumArtMinHeight, g_settings.albumArtMaxHeight);
    ParseMargin(L"MainSettings.AlbumArtSetting.albumArtMargin", L"0 0", g_settings.albumArtLeftMargin, g_settings.albumArtRightMargin);
    ParseMargin(L"MainSettings.TextAreaSetting.textAreaWidth", L"0 120", g_settings.textAreaMinWidth, g_settings.textAreaMaxWidth);
    ParseMargin(L"MainSettings.TextAreaSetting.textAreaHeight", L"0 0", g_settings.textAreaMinHeight, g_settings.textAreaMaxHeight);
    ParseMargin(L"MainSettings.TextAreaSetting.textAreaMargin", L"5 5", g_settings.textAreaLeftMargin, g_settings.textAreaRightMargin);
    g_settings.mirrorLayout         = Wh_GetIntSetting(L"MainSettings.PlayerSetting.mirrorLayout") != 0;
    g_settings.fullHeightHitArea    = Wh_GetIntSetting(L"MainSettings.PlayerSetting.fullHeightHitArea") != 0;
    g_settings.autoSwitchSession    = Wh_GetIntSetting(L"MainSettings.PlayerSetting.autoSwitchSession") != 0;
    g_settings.showMediaButtons     = Wh_GetIntSetting(L"MainSettings.MediaButtonsSettings.showMediaButtons") != 0;
    ParseMargin(L"MainSettings.MediaButtonsSettings.mediaButtonsMargin", L"2 2", g_settings.mediaButtonsLeftMargin, g_settings.mediaButtonsRightMargin);
    g_settings.showTrackTitle       = Wh_GetIntSetting(L"MainSettings.TextAreaSetting.showTrackTitle")    != 0;
    g_settings.showFullTitleOnHover = Wh_GetIntSetting(L"BehaviorSettings.showFullTitleOnHover") != 0;
    g_settings.showTrackArtist      = Wh_GetIntSetting(L"MainSettings.TextAreaSetting.showTrackArtist")   != 0;
    g_settings.swapTitleArtist      = Wh_GetIntSetting(L"MainSettings.TextAreaSetting.swapTitleArtist")   != 0;
    g_settings.emptyTitleText       = StrAllowEmpty(L"MainSettings.TextAreaSetting.emptyTitleText");
    g_settings.noMediaTitleText     = StrAllowEmpty(L"MainSettings.TextAreaSetting.noMediaTitleText");
    g_settings.emptyArtistText      = StrAllowEmpty(L"MainSettings.TextAreaSetting.emptyArtistText");
    g_settings.noMediaArtistText    = StrAllowEmpty(L"MainSettings.TextAreaSetting.noMediaArtistText");
    g_settings.showAlbumArt         = Wh_GetIntSetting(L"MainSettings.AlbumArtSetting.showAlbumArt")      != 0;
    g_settings.albumArtEmptyBehavior = Str(L"AppearanceSettings.AlbumArtDisplaySettings.albumArtEmptyBehavior", L"show");
    g_settings.emptyIconGlyph       = Str(L"AppearanceSettings.AlbumArtDisplaySettings.emptyIconGlyph",       L"E189");
    g_settings.emptyIconSize        = Int(L"AppearanceSettings.AlbumArtDisplaySettings.emptyIconSize",          1, 256, 16);
    g_settings.emptyIconFont        = Str(L"AppearanceSettings.AlbumArtDisplaySettings.emptyIconFont",        L"segoe_fluent");
    g_settings.emptyIconColor       = Str(L"AppearanceSettings.AlbumArtDisplaySettings.emptyIconColor",       L"255 255 255");
    g_settings.emptyIconOpacity     = Int(L"AppearanceSettings.AlbumArtDisplaySettings.emptyIconOpacity",       0, 100, 100);
    g_settings.albumArtQuality      = Str(L"AppearanceSettings.AlbumArtDisplaySettings.albumArtQuality", L"medium");
    g_settings.showPauseOverlay     = Wh_GetIntSetting(L"AppearanceSettings.AlbumArtDisplaySettings.showPauseOverlay")  != 0;
    g_settings.pauseOverlayIconSize = Int(L"AppearanceSettings.AlbumArtDisplaySettings.pauseOverlayIconSize",     1, 256, 16);
    g_settings.pauseOverlayOpacity  = Int(L"AppearanceSettings.AlbumArtDisplaySettings.pauseOverlayOpacity",     0, 100,  60);
    g_settings.iconStyle            = Str(L"AppearanceSettings.MediaButtonsStyleSettings.iconStyle", L"fluent_outline");
    g_settings.showAppIcon          = Wh_GetIntSetting(L"AppearanceSettings.AlbumArtDisplaySettings.showAppIcon")       != 0;
    g_settings.appIconCorner        = Str(L"AppearanceSettings.AlbumArtDisplaySettings.appIconCorner",  L"bottom_right");
    g_settings.appIconSize          = Int(L"AppearanceSettings.AlbumArtDisplaySettings.appIconSize",         8,  32,  12);
    g_settings.backgroundType       = Str(L"AppearanceSettings.BackgroundStyleSettings.backgroundType", L"none");
    g_settings.blurOpacity          = Int(L"AppearanceSettings.BackgroundStyleSettings.blurOpacity",           0, 100, 65);
    g_settings.blurRadius           = Int(L"AppearanceSettings.BackgroundStyleSettings.blurRadius",            1,  50,  11);
    ParseCornerRadius(L"AppearanceSettings.BackgroundStyleSettings.cornerRadius", L"4",
                    g_settings.cornerRadiusTL, g_settings.cornerRadiusTR,
                    g_settings.cornerRadiusBR, g_settings.cornerRadiusBL);
    g_settings.albumArtOpacity      = Int(L"AppearanceSettings.AlbumArtDisplaySettings.albumArtOpacity",       0, 100, 100);
    ParseCornerRadius(L"AppearanceSettings.AlbumArtDisplaySettings.albumArtCornerRadius", L"4",
                    g_settings.albumArtCornerRadiusTL, g_settings.albumArtCornerRadiusTR,
                    g_settings.albumArtCornerRadiusBR, g_settings.albumArtCornerRadiusBL);
    g_settings.buttonSpacing        = Wh_GetIntSetting(L"AppearanceSettings.MediaButtonsStyleSettings.buttonSpacing");
    g_settings.buttonSize           = Int(L"MainSettings.MediaButtonsSettings.buttonSize",          16,  48,  28);
    g_settings.buttonIconSize       = Int(L"AppearanceSettings.MediaButtonsStyleSettings.buttonIconSize",       8,  32,  12);
    ParseCornerRadius(L"AppearanceSettings.MediaButtonsStyleSettings.buttonCornerRadius", L"4",
                    g_settings.buttonCornerRadiusTL, g_settings.buttonCornerRadiusTR,
                    g_settings.buttonCornerRadiusBR, g_settings.buttonCornerRadiusBL);
    g_settings.titleFontSize        = Int(L"AppearanceSettings.TitleTextStyleSettings.titleFontSize",         7,  24,  12);
    g_settings.titleFont            = MapFontName(Str(L"AppearanceSettings.TitleTextStyleSettings.titleFont", L"segoe_ui_variable"));
    g_settings.titleFontFamily      = Str(L"AppearanceSettings.TitleTextStyleSettings.titleFontFamily", L"");
    g_settings.titleFontWeight      = Str(L"AppearanceSettings.TitleTextStyleSettings.titleFontWeight", L"");
    g_settings.titleFontStyle       = Str(L"AppearanceSettings.TitleTextStyleSettings.titleFontStyle", L"");
    g_settings.titleCharacterSpacing = Wh_GetIntSetting(L"AppearanceSettings.TitleTextStyleSettings.titleCharacterSpacing");
    g_settings.artistFontSize       = Int(L"AppearanceSettings.ArtistTextStyleSettings.artistFontSize",        7,  24,  11);
    g_settings.artistFont           = MapFontName(Str(L"AppearanceSettings.ArtistTextStyleSettings.artistFont", L"segoe_ui_variable"));
    g_settings.artistFontFamily     = Str(L"AppearanceSettings.ArtistTextStyleSettings.artistFontFamily", L"");
    g_settings.artistFontWeight     = Str(L"AppearanceSettings.ArtistTextStyleSettings.artistFontWeight", L"");
    g_settings.artistFontStyle      = Str(L"AppearanceSettings.ArtistTextStyleSettings.artistFontStyle", L"");
    g_settings.artistCharacterSpacing = Wh_GetIntSetting(L"AppearanceSettings.ArtistTextStyleSettings.artistCharacterSpacing");
    g_settings.textSpacing          = Wh_GetIntSetting(L"MainSettings.TextAreaSetting.textSpacing");
    g_settings.enableArtistScrolling = Wh_GetIntSetting(L"MainSettings.TextAreaSetting.enableArtistScrolling") != 0;
    g_settings.enableTitleScrolling = Wh_GetIntSetting(L"MainSettings.TextAreaSetting.enableTitleScrolling") != 0;
    g_settings.scrollSpeed          = Int(L"MainSettings.TextAreaSetting.scrollSpeed", 1, 10, 1);
    g_settings.scrollPauseDuration  = Int(L"MainSettings.TextAreaSetting.scrollPauseDuration", 0, 10000, 1000);
    g_settings.scrollMode           = Str(L"MainSettings.TextAreaSetting.scrollMode", L"bounce");
    g_settings.loopGap              = Int(L"MainSettings.TextAreaSetting.loopGap", 0, 500, 40);
    g_settings.solidColor           = Str(L"AppearanceSettings.BackgroundStyleSettings.solidColor", L"35 35 35");
    g_settings.solidColor2          = Str(L"AppearanceSettings.BackgroundStyleSettings.solidColor2", L"35 35 35");
    g_settings.gradientColor2       = Str(L"AppearanceSettings.BackgroundStyleSettings.gradientColor2", L"128 128 128");
    g_settings.solidOpacity         = Int(L"AppearanceSettings.BackgroundStyleSettings.solidOpacity", 0, 100, 100);
    g_settings.gradientAngle        = Int(L"AppearanceSettings.BackgroundStyleSettings.gradientAngle", 0, 360, 50);
    g_settings.gradientBalance      = Int(L"AppearanceSettings.BackgroundStyleSettings.gradientBalance", 0, 100, 50);
    g_settings.acrylicTintOpacity   = Int(L"AppearanceSettings.BackgroundStyleSettings.acrylicTintOpacity", 0, 100, 50);
    g_settings.micaOpacity          = Int(L"AppearanceSettings.BackgroundStyleSettings.micaOpacity", 0, 100, 50);
    g_settings.buttonColor          = Str(L"AppearanceSettings.MediaButtonsStyleSettings.buttonColor", L"255 255 255");
    g_settings.buttonColorOpacity   = Int(L"AppearanceSettings.MediaButtonsStyleSettings.buttonColorOpacity", 0, 100, 100);
    g_settings.buttonGradient       = Wh_GetIntSetting(L"AppearanceSettings.MediaButtonsStyleSettings.buttonGradient") != 0;
    g_settings.titleColor           = Str(L"AppearanceSettings.TitleTextStyleSettings.titleColor", L"255 255 255");
    g_settings.titleColorOpacity    = Int(L"AppearanceSettings.TitleTextStyleSettings.titleColorOpacity", 0, 100, 100);
    g_settings.artistColor          = Str(L"AppearanceSettings.ArtistTextStyleSettings.artistColor", L"255 255 255");
    g_settings.artistColorOpacity   = Int(L"AppearanceSettings.ArtistTextStyleSettings.artistColorOpacity", 0, 100, 80);
    g_settings.vizEnabled      = false;
    g_settings.vizPosition     = Str(L"MainSettings.VisualizerFunctionsSettings.vizPosition", L"right");
    g_settings.vizColor        = Str(L"AppearanceSettings.VisualizerStyleSettings.vizColor",  L"255 255 255");
    g_settings.vizColor1       = Str(L"AppearanceSettings.VisualizerStyleSettings.vizColor1", L"30 215 96");
    g_settings.vizColor2       = Str(L"AppearanceSettings.VisualizerStyleSettings.vizColor2", L"0 180 255");
    g_settings.vizSensitivity  = Int(L"MainSettings.VisualizerFunctionsSettings.vizSensitivity", 0, 300, 150);
    {
        int n = 7, gap = 5;
        ParseTwoInts(Str(L"MainSettings.VisualizerFunctionsSettings.vizBarCountGap", L"7 5"), n, gap);
        g_settings.vizBars   = std::clamp(n, 1, 20);
        g_settings.vizBarGap = std::clamp(gap, 0, 40);
        int w = 5, h = 3;
        ParseTwoInts(Str(L"MainSettings.VisualizerFunctionsSettings.vizBarSize", L"5 3"), w, h);
        g_settings.vizBarWidth    = std::clamp(w, 0, 40);
        g_settings.vizIdleBarSize = std::clamp(h, 0, 15);
        int l = 0, r = 0;
        ParseTwoInts(Str(L"MainSettings.VisualizerFunctionsSettings.vizPadding", L"0 0"), l, r);
        g_settings.vizPadLeft  = std::clamp(l, 0, 200);
        g_settings.vizPadRight = std::clamp(r, 0, 200);
    }
    {
        std::wstring shape = Str(L"MainSettings.VisualizerFunctionsSettings.vizShape", L"stereo");
        g_settings.vizShape = (shape == L"mountain") ? VizShape::Mountain
                    : (shape == L"mirror")   ? VizShape::Mirror
                    : (shape == L"wave")     ? VizShape::Wave
                    : (shape == L"breathe")  ? VizShape::Breathe
                                            : VizShape::Stereo;
        std::wstring mode = Str(L"AppearanceSettings.VisualizerStyleSettings.vizColorMode", L"solid");
        g_settings.vizColorMode = (mode == L"dynamic_album")    ? VizColorMode::DynamicAlbum
                        : (mode == L"dynamic_gradient") ? VizColorMode::DynamicGradient
                        : (mode == L"custom_gradient")  ? VizColorMode::CustomGradient
                        : (mode == L"acrylic")          ? VizColorMode::Acrylic
                                                        : VizColorMode::Solid;
        std::wstring eq = Str(L"MainSettings.VisualizerFunctionsSettings.vizEQ", L"default");
        g_settings.vizEq = (eq == L"bass")       ? VizEQ::Bass
                : (eq == L"rock")       ? VizEQ::Rock
                : (eq == L"pop")        ? VizEQ::Pop
                : (eq == L"jazz")       ? VizEQ::Jazz
                : (eq == L"electronic") ? VizEQ::Electronic
                                        : VizEQ::Default;
        std::wstring anchor = Str(L"MainSettings.VisualizerFunctionsSettings.vizAnchor", L"middle");
        g_settings.vizAnchor = (anchor == L"top")    ? VizAnchor::Top
                    : (anchor == L"bottom") ? VizAnchor::Bottom
                                            : VizAnchor::Middle;
    }
    // 1.9.0 settings. Behind-widget bars reuse the inline XAML visualizer and
    // its in-process capture, styled from the shared Audio visualizer settings.
    g_settings.vizOverlay = Str(L"Visualizer.position.placement", L"overlay") == L"overlay";
    {
        int op = Wh_GetIntSetting(L"Visualizer.position.overlayOpacity");
        g_settings.vizOverlayOpacity = op > 0 ? std::clamp(op, 10, 80) : 45;
    }
    g_settings.showProgressBar = Wh_GetIntSetting(L"ProgressSettings.showProgressBar") != 0;
    g_settings.progressArtwork = Str(L"ProgressSettings.progressColor", L"artwork") != L"gradient";
    {
        int ph = Wh_GetIntSetting(L"ProgressSettings.progressHeight");
        g_settings.progressHeight = ph > 0 ? std::clamp(ph, 1, 6) : 2;
    }
    g_settings.clickToSeek = Wh_GetIntSetting(L"ProgressSettings.clickToSeek") != 0;
    {
        std::wstring td = Str(L"ProgressSettings.timeDisplay", L"elapsed_total");
        g_settings.timeDisplayMode = td == L"elapsed" ? 1 : td == L"elapsed_total" ? 2 : 0;
    }
    if (g_settings.vizOverlay) {
        auto HexRgb = [](std::wstring v, const wchar_t* def) -> std::wstring {
            if (!v.empty() && v[0] == L'#') v = v.substr(1);
            if (v.size() == 8) v = v.substr(2);
            if (v.size() != 6) return def;
            try {
                unsigned long c = std::stoul(v, nullptr, 16);
                return std::to_wstring((c >> 16) & 0xFF) + L" " + std::to_wstring((c >> 8) & 0xFF) +
                       L" " + std::to_wstring(c & 0xFF);
            } catch (...) { return def; }
        };
        g_settings.vizEnabled     = true;
        g_settings.vizBars        = 96;  // trimmed to the player width at layout time
        // Same geometry as Taskbar Media Widget by uMk0: 3 px bars, 2 px gaps,
        // rising from a 1 px stub to the full player height.
        g_settings.vizBarWidth    = 3;
        g_settings.vizBarGap      = 2;
        g_settings.vizIdleBarSize = 1;
        g_settings.vizAnchor      = VizAnchor::Bottom;
        g_settings.vizPadLeft     = 0;
        g_settings.vizPadRight    = 0;
        std::wstring shape = Str(L"Visualizer.appearance.shape", L"stereo");
        g_settings.vizShape = (shape == L"mountain") ? VizShape::Mountain
                            : (shape == L"mirror")   ? VizShape::Mirror
                            : (shape == L"wave")     ? VizShape::Wave
                            : (shape == L"breathe")  ? VizShape::Breathe
                                                     : VizShape::Stereo;
        g_settings.vizEq = VizEQ::Default;
        // 1.9.4: the overlay follows the shared Audio visualizer sensitivity and
        // analysis gain instead of the unused inline-visualizer slider.
        g_settings.vizSensitivity = std::clamp(Wh_GetIntSetting(L"Visualizer.appearance.sensitivity"), 0, 300);
        g_settings.vizInputGain = powf(10.f, std::clamp(Wh_GetIntSetting(L"Visualizer.audio.inputGain"), -24, 24) / 20.f);
        std::wstring cm = Str(L"Visualizer.appearance.colorMode", L"gradient");
        g_settings.vizColor  = HexRgb(Str(L"Visualizer.appearance.color", L"#FFCBA6F7"), L"203 166 247");
        g_settings.vizColor1 = HexRgb(Str(L"Visualizer.appearance.gradientColor1", L"#FFCBA6F7"), L"203 166 247");
        g_settings.vizColor2 = HexRgb(Str(L"Visualizer.appearance.gradientColor2", L"#FF89B4FA"), L"137 180 250");
        g_settings.vizColorMode = (cm == L"solid") ? VizColorMode::Solid : VizColorMode::CustomGradient;
    }
    g_settings.albumArtLeftClick         = L"none";
    g_settings.albumArtRightClick        = L"none";
    g_settings.albumArtMiddleClick       = L"none";
    g_settings.albumArtLeftDoubleClick   = L"none";
    g_settings.albumArtRightDoubleClick  = L"none";
    g_settings.albumArtMiddleDoubleClick = L"none";
    g_settings.playerLeftClick           = L"none";
    g_settings.playerRightClick          = L"none";
    g_settings.playerMiddleClick         = L"none";
    g_settings.playerLeftDoubleClick     = L"none";
    g_settings.playerRightDoubleClick    = L"none";
    g_settings.playerMiddleDoubleClick   = L"none";
    for (int i = 0; i < 20; i++) {
        PCWSTR objectStr = Wh_GetStringSetting(L"BehaviorSettings.ClickActionSettings[%d].object", i);
        PCWSTR clickStr = Wh_GetStringSetting(L"BehaviorSettings.ClickActionSettings[%d].click", i);
        PCWSTR actionStr = Wh_GetStringSetting(L"BehaviorSettings.ClickActionSettings[%d].action", i);
        if (*objectStr == L'\0' || *clickStr == L'\0' || *actionStr == L'\0') {
            Wh_FreeStringSetting(objectStr);
            Wh_FreeStringSetting(clickStr);
            Wh_FreeStringSetting(actionStr);
            break;
        }
        std::wstring object(objectStr);
        std::wstring click(clickStr);
        std::wstring action(actionStr);
        Wh_FreeStringSetting(objectStr);
        Wh_FreeStringSetting(clickStr);
        Wh_FreeStringSetting(actionStr);
        if (object.empty()) object = L"none";
        if (click.empty()) click = L"none";
        if (action.empty()) action = L"none";
        if (object == L"none" || click == L"none") {
            continue;
        }
        if (object == L"album_art") {
            if (click == L"left_click") g_settings.albumArtLeftClick = action;
            else if (click == L"right_click") g_settings.albumArtRightClick = action;
            else if (click == L"middle_click") g_settings.albumArtMiddleClick = action;
            else if (click == L"left_double_click") g_settings.albumArtLeftDoubleClick = action;
            else if (click == L"right_double_click") g_settings.albumArtRightDoubleClick = action;
            else if (click == L"middle_double_click") g_settings.albumArtMiddleDoubleClick = action;
        } else if (object == L"player") {
            if (click == L"left_click") g_settings.playerLeftClick = action;
            else if (click == L"right_click") g_settings.playerRightClick = action;
            else if (click == L"middle_click") g_settings.playerMiddleClick = action;
            else if (click == L"left_double_click") g_settings.playerLeftDoubleClick = action;
            else if (click == L"right_double_click") g_settings.playerRightDoubleClick = action;
            else if (click == L"middle_double_click") g_settings.playerMiddleDoubleClick = action;
        }
    }
    g_settings.albumArtWheelAction = L"none";
    g_settings.playerWheelAction   = L"none";
    for (int i = 0; i < 20; i++) {
        PCWSTR objectStr = Wh_GetStringSetting(L"BehaviorSettings.MouseWheelActionSettings[%d].object", i);
        PCWSTR clickStr = Wh_GetStringSetting(L"BehaviorSettings.MouseWheelActionSettings[%d].click", i);
        PCWSTR actionStr = Wh_GetStringSetting(L"BehaviorSettings.MouseWheelActionSettings[%d].action", i);
        if (*objectStr == L'\0' || *clickStr == L'\0' || *actionStr == L'\0') {
            Wh_FreeStringSetting(objectStr);
            Wh_FreeStringSetting(clickStr);
            Wh_FreeStringSetting(actionStr);
            break;
        }
        std::wstring object(objectStr);
        std::wstring click(clickStr);
        std::wstring action(actionStr);
        Wh_FreeStringSetting(objectStr);
        Wh_FreeStringSetting(clickStr);
        Wh_FreeStringSetting(actionStr);
        if (object.empty()) object = L"none";
        if (click.empty()) click = L"none";
        if (action.empty()) action = L"none";
        if (object == L"none" || click == L"none") {
            continue;
        }
        if (object == L"album_art" && click == L"mouse_wheel") {
            g_settings.albumArtWheelAction = action;
        } else if (object == L"player" && click == L"mouse_wheel") {
            g_settings.playerWheelAction = action;
        }
    }
    g_settings.hideWhenNoMedia      = Wh_GetIntSetting(L"BehaviorSettings.hideWhenNoMedia")   != 0;
    g_settings.hideFullscreen       = Wh_GetIntSetting(L"BehaviorSettings.hideFullscreen")    != 0;
    g_settings.idleHideSeconds      = std::max(Wh_GetIntSetting(L"BehaviorSettings.idleHideSeconds"), 0);
    g_settings.playerHoverEffectMode = HoverMode(L"AppearanceSettings.BackgroundStyleSettings.enablePlayerHoverEffect");
    g_settings.mediaButtonsHoverEffectMode = HoverMode(L"AppearanceSettings.BackgroundStyleSettings.enableMediaButtonsHoverEffect");
    g_settings.enableHoverAnimation = Wh_GetIntSetting(L"AppearanceSettings.BackgroundStyleSettings.enableHoverAnimation") != 0;
    g_settings.island = Wh_GetIntSetting(L"AppearanceSettings.BackgroundStyleSettings.island") != 0;
    g_settings.islandGap = std::clamp(Wh_GetIntSetting(L"AppearanceSettings.BackgroundStyleSettings.islandGap"), 0, 40);
    g_settings.islandPadding = std::clamp(Wh_GetIntSetting(L"AppearanceSettings.BackgroundStyleSettings.islandPadding"), 0, 40);
    g_settings.enableSmoothPositionAnimation = Wh_GetIntSetting(L"AnimationSettings.enableSmoothPositionAnimation") != 0;
    g_settings.showSuccessNotification = Wh_GetIntSetting(L"NotificationSettings.showSuccessNotification") != 0;
    g_settings.hideUnsupportedButtons  = Wh_GetIntSetting(L"MainSettings.MediaButtonsSettings.hideUnsupportedButtons") != 0;
    g_settings.disableAlbumArtClick    = Wh_GetIntSetting(L"BehaviorSettings.disableAlbumArtClick") != 0;
    g_settings.ignoredProcesses     = Str(L"DebugSettings.ignoredProcesses", L"");
    g_settings.enableTreeDump       = Wh_GetIntSetting(L"DebugSettings.enableTreeDump")    != 0;
    g_settings.showDebugBorders     = Wh_GetIntSetting(L"DebugSettings.showDebugBorders")  != 0;
    g_settings.showMiniPlayerBorder = Wh_GetIntSetting(L"DebugSettings.showMiniPlayerBorder") != 0;
    g_settings.showLayoutAnchors    = Wh_GetIntSetting(L"DebugSettings.showLayoutAnchors") != 0;
    g_settings.keepMiniPlayerOpen   = Wh_GetIntSetting(L"PlayerMenuSettings.keepMiniPlayerOpen") != 0;
    g_settings.hideMediaSessionsList = Wh_GetIntSetting(L"PlayerMenuSettings.hideMediaSessionsList") != 0;
    g_settings.miniPlayerPlacementMode = Str(L"PlayerMenuSettings.placementMode", L"screen");
    g_settings.miniPlayerHorizontalOffsetAbove =
        Wh_GetIntSetting(L"PlayerMenuSettings.PlayerMenuSettingsNear.miniPlayerHorizontalOffsetNear");
    g_settings.miniPlayerVerticalPlacementNear =
        Str(L"PlayerMenuSettings.PlayerMenuSettingsNear.miniPlayerVerticalPlacementNear", L"top");
    g_settings.miniPlayerHorizontalPlacement =
        Str(L"PlayerMenuSettings.PlayerMenuSettingsScreen.miniPlayerHorizontalPlacement", L"right");
    g_settings.miniPlayerHorizontalDistanceFromScreenEdge =
        Wh_GetIntSetting(L"PlayerMenuSettings.PlayerMenuSettingsScreen.horizontalDistanceFromScreenEdge");
    g_settings.miniPlayerVerticalPlacement =
        Str(L"PlayerMenuSettings.PlayerMenuSettingsScreen.miniPlayerVerticalPlacement", L"bottom");
    g_settings.miniPlayerVerticalDistanceFromScreenEdge =
        Wh_GetIntSetting(L"PlayerMenuSettings.PlayerMenuSettingsScreen.verticalDistanceFromScreenEdge");
    g_settings.miniPlayerAnimation =
        Str(L"PlayerMenuSettings.PlayerMenuSettingsScreen.miniPlayerAnimation", L"auto");
    g_settings.showRestartButton    = Wh_GetIntSetting(L"DebugSettings.showRestartButton") != 0;
    g_settings.contextMenuRepeatStyle  = Str(L"ContextMenuSettings.repeatStyle",  L"submenu");
    g_settings.contextMenuShuffleStyle = Str(L"ContextMenuSettings.shuffleStyle", L"toggle");
    g_settings.showOpenWindhawk        = Wh_GetIntSetting(L"ContextMenuSettings.showOpenWindhawk") != 0;
    g_settings.contextMenuIconStyle    = Str(L"ContextMenuSettings.contextMenuIconStyle", L"as_media_buttons");
    g_settings.contextMenuIconColor    = StrAllowEmpty(L"ContextMenuSettings.contextMenuIconColor");
    g_settings.contextMenuIconOpacity  = Int(L"ContextMenuSettings.contextMenuIconOpacity", 0, 100, 100);
    {
        g_settings.contextMenuItems.clear();
        const wchar_t* defaultItems[] = {
            L"repeat", L"shuffle", L"forward", L"rewind",
            L"next", L"prev", L"switch_sessions", L"open_app"
        };
        bool hasAny = false;
        std::set<std::wstring> seen;
        for (int i = 0; i < 20; i++) {
            PCWSTR p = Wh_GetStringSetting(L"ContextMenuSettings.contextMenuItems[%d]", i);
            if (!p || !*p) { Wh_FreeStringSetting(p); break; }
            std::wstring s(p);
            Wh_FreeStringSetting(p);
            if (seen.insert(s).second) {
                g_settings.contextMenuItems.push_back(s);
                hasAny = true;
            }
        }
        if (!hasAny) {
            for (auto& d : defaultItems)
                g_settings.contextMenuItems.push_back(d);
        }
    }
    try {
        std::lock_guard<std::mutex> lock(g_mediaButtonsMutex);
        g_mediaButtons.clear();
        std::set<MediaButtonType> seen;
        for (int i = 0; i < 10; i++) {
            try {
                PCWSTR itemStr = Wh_GetStringSetting(L"MainSettings.MediaButtonsSettings.mediaButtons[%d]", i);
                if (!itemStr || !*itemStr) {
                    Wh_FreeStringSetting(itemStr);
                    break;
                }
                std::wstring keyword(itemStr);
                Wh_FreeStringSetting(itemStr);
                for (const auto& def : g_mediaButtonDefinitions) {
                    if (def.keyword == keyword && seen.insert(def.type).second) {
                        g_mediaButtons.push_back({def.type, def.cmd});
                        break;
                    }
                }
            } catch (...) {
                Wh_Log(L"LoadSettings: Exception parsing media button at index %d", i);
            }
        }
    } catch (...) {
        Wh_Log(L"LoadSettings: Critical exception in media buttons parsing, using defaults");
        try {
            std::lock_guard<std::mutex> lock(g_mediaButtonsMutex);
            g_mediaButtons = {
                {MediaButtonType::Previous, 1},
                {MediaButtonType::PlayPause, 2},
                {MediaButtonType::Next, 3}
            };
        } catch (...) {}
    }
    if (g_settings.position == L"taskbar_left")
        g_settings.position = L"taskbar_left_start";
    else if (g_settings.position == L"taskbar_right")
        g_settings.position = L"taskbar_right_start";
    else if (g_settings.position == L"taskbar_after_start")
        g_settings.position = L"taskbar_after_search_right";
    else if (g_settings.position == L"taskbar_after_search")
        g_settings.position = L"taskbar_after_search_right";
    else if (g_settings.position == L"tray_before_omni")
        g_settings.position = L"tray_before_omni_right";
    else if (g_settings.position == L"tray_after_showdesktop")
        g_settings.position = L"tray_after_showdesktop_right";
}
static HWND FindCurrentProcessTaskbarWnd();
static void DispatchMediaUpdate();
static void RefreshMiniPlayerFlyoutUI();
static void FetchMiniSessionInfosAsync(HWND taskbarWnd);
struct MiniSessionInfo;
static void AnimateSessionPill(winrt::Windows::UI::Xaml::Shapes::Rectangle const& pill, bool isCurrent, bool animate);
static winrt::Windows::UI::Xaml::Controls::Button BuildSessionRowButton(const MiniSessionInfo& info, bool isCurrent, HWND taskbarWnd, int rowIndex);

static void ApplySettings();
static std::atomic<bool> g_unloading{false};
static std::atomic<bool> g_applyingSettings{false};
static HWND g_taskbarWnd = nullptr;

static std::atomic<int> g_activeWorkerThreads{0};
template <typename F>
static void SpawnTrackedWorker(F&& fn) {
    g_activeWorkerThreads.fetch_add(1, std::memory_order_relaxed);
    std::thread([f = std::forward<F>(fn)]() mutable {
        struct Decrementer {
            ~Decrementer() { g_activeWorkerThreads.fetch_sub(1, std::memory_order_relaxed); }
        } dec;
        f();
    }).detach();
}

static void WaitForTrackedWorkers() {
    static constexpr DWORD kTimeoutMs = 2000;
    DWORD deadline = GetTickCount() + kTimeoutMs;
    HWND hTaskbar = g_taskbarWnd;
    DWORD tid = GetCurrentThreadId();
    bool isUiThread = hTaskbar && (GetWindowThreadProcessId(hTaskbar, nullptr) == tid);
    if (isUiThread) {
        while (g_activeWorkerThreads.load(std::memory_order_relaxed) > 0 &&
               GetTickCount() < deadline) {
            MSG msg;
            while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE | PM_QS_SENDMESSAGE)) {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
            Sleep(10);
        }
    } else {
        while (g_activeWorkerThreads.load(std::memory_order_relaxed) > 0 &&
               GetTickCount() < deadline) {
            Sleep(10);
        }
    }
}

static std::atomic<bool> g_miniPlayerFlyoutOpen{false};
static int    g_miniPlayerAnimAxis = 0;
static double g_miniPlayerAnimSign = 1.0;
static std::atomic<bool> g_miniPlayerClosingAnimInProgress{false};
static std::atomic<bool> g_miniPlayerClosingAnimStarted{false};
static std::atomic<bool> g_miniPlayerExplicitCloseRequested{false};
static IMMDeviceEnumerator* g_pDeviceEnumerator = nullptr;
static const CLSID XIID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
static const IID XIID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
static const IID XIID_IAudioSessionManager2 = __uuidof(IAudioSessionManager2);
[[clang::no_destroy]] static Grid             g_playerGrid      = nullptr;
[[clang::no_destroy]] static FrameworkElement g_injectionParent = nullptr;
static int              g_playerColumn    = -1;
[[clang::no_destroy]] static std::function<void()> g_playerButtonStateUpdater;
[[clang::no_destroy]] static ToolTip          g_playerToolTip   = nullptr;
static std::atomic<bool> g_needsUiUpdate{false};
static void ShowSuccessNotification() {
    if (!g_settings.showSuccessNotification) {
        return;
    }
    std::thread([]() {
        MessageBoxW(
            nullptr,
            L"Media player successfully loaded and ready to use",
            L"Taskbar Fluent Media Player",
            MB_ICONINFORMATION | MB_OK | MB_TOPMOST | MB_SETFOREGROUND
        );
    }).detach();
}

[[clang::no_destroy]] static FrameworkElement g_trackedElement = nullptr;
static Thickness g_trackedElementOriginalMargin{};
static bool g_hasTrackedElementOriginalMargin = false;
static std::wstring g_trackPosition = L"";
static winrt::event_token g_layoutUpdateToken{};
using CTaskBand_GetTaskbarHost_t  = void*(WINAPI*)(void*, void*);
using CSecondaryTaskBand_GetTaskbarHost_t = void*(WINAPI*)(void*, void*);
using TaskbarHost_FrameHeight_t   = int  (WINAPI*)(void*);
using Std_Ref_Decref_t            = void (WINAPI*)(void*);
static CTaskBand_GetTaskbarHost_t  CTaskBand_GetTaskbarHost_Original  = nullptr;
static CSecondaryTaskBand_GetTaskbarHost_t CSecondaryTaskBand_GetTaskbarHost_Original = nullptr;
static TaskbarHost_FrameHeight_t   TaskbarHost_FrameHeight_Original   = nullptr;
static Std_Ref_Decref_t            Std_Ref_Decref_Original            = nullptr;
static void* CTaskBand_ITaskListWndSite_vftable = nullptr;
static void* CSecondaryTaskBand_ITaskListWndSite_vftable = nullptr;
using WindowThreadProc = void(*)(void*);
static bool RunFromWindowThread(HWND hWnd, WindowThreadProc proc, void* param) {
    static const UINT kMsg = RegisterWindowMessage(L"Windhawk_RunFromWindowThread_" WH_MOD_ID);
    struct Payload { WindowThreadProc proc; void* param; };
    DWORD tid = GetWindowThreadProcessId(hWnd, nullptr);
    if (!tid) return false;
    if (tid == GetCurrentThreadId()) {
        proc(param);
        return true;
    }
    HHOOK hook = SetWindowsHookExW(WH_CALLWNDPROC,
        [](int code, WPARAM w, LPARAM l) CALLBACK -> LRESULT {
            if (code == HC_ACTION) {
                auto* cwp = reinterpret_cast<const CWPSTRUCT*>(l);
                static const UINT kM = RegisterWindowMessage(L"Windhawk_RunFromWindowThread_" WH_MOD_ID);
                if (cwp->message == kM) {
                    auto* p = reinterpret_cast<Payload*>(cwp->lParam);
                    p->proc(p->param);
                }
            }
            return CallNextHookEx(nullptr, code, w, l);
        }, nullptr, tid);
    if (!hook) return false;
    Payload pay{proc, param};
    SendMessageW(hWnd, kMsg, 0, reinterpret_cast<LPARAM>(&pay));
    UnhookWindowsHookEx(hook);
    return true;
}
struct MediaState {
    std::wstring      title;
    std::wstring      artist;
    std::wstring      appUserModelId;
    bool              isPlaying     = false;
    bool              isStopped     = false;
    bool              hasMedia      = false;
    std::vector<BYTE> thumbnailBytes;
    uint64_t          thumbnailHash = 0;
    uint64_t          thumbnailStreamSize = 0;
    std::vector<BYTE> appIconBytes;
    std::wstring      appIconKey;
    bool              canSkipPrevious  = true;
    bool              canSkipNext      = true;
    bool              canShuffle       = true;
    bool              canRepeat        = true;
    bool              canSeek          = true;
};
static MediaState g_media;
static std::mutex g_mediaMtx;
static std::wstring g_lastTitleArtistKey;
static uint64_t     g_suspectArtSize   = 0;
static uint64_t     g_suspectArtHash   = 0;
static bool         g_artDelayPending  = false;
static bool         g_artNewBrowserSession = false;
enum class RepeatMode {
    Off = 0,
    All = 1,
    One = 2,
};
static std::atomic<bool> g_shuffleEnabled{false};
static std::atomic<RepeatMode> g_repeatMode{RepeatMode::Off};
static std::wstring g_cachedAlbumTitle;
static std::wstring g_cachedAlbumArtist;
static std::vector<BYTE> g_cachedThumbnailBytes;
static int g_cachedAppIconSize = -1;
static std::wstring g_scrollCachedTitle;
static std::wstring g_scrollCachedArtist;
struct BlurBgCache {
    std::vector<BYTE>  blurredPixels;
    int                width  = 0;
    int                height = 0;
    size_t             artHash = 0;
    void Invalidate() {
        blurredPixels.clear();
        width = height = 0;
        artHash = 0;
    }
} g_blurBgCache;
struct AlbumPalette {
    winrt::Windows::UI::Color primary;
    winrt::Windows::UI::Color secondary;
};
static AlbumPalette g_cachedAlbumPalette = {
    winrt::Windows::UI::Color{255, 18, 18, 18},
    winrt::Windows::UI::Color{255, 45, 45, 45}
};
static size_t g_cachedPaletteHash = 0;
static winrt::Windows::UI::Color g_cachedVizBaseColor{255, 255, 255, 255};
static bool g_vizBaseColorDirty = true;
static winrt::Windows::UI::Color g_cachedVizPal0{255, 255, 255, 255};
static winrt::Windows::UI::Color g_cachedVizPal1{255, 255, 255, 255};
static winrt::Windows::UI::Color g_cachedVizCg0{255, 255, 255, 255};
static winrt::Windows::UI::Color g_cachedVizCg1{255, 255, 255, 255};
static winrt::Windows::UI::Color g_cachedVizAcrCol{255, 255, 255, 255};
static bool g_vizPaletteColorsDirty = true;
[[clang::no_destroy]] static GlobalSystemMediaTransportControlsSessionManager g_sessionMgr     = nullptr;
[[clang::no_destroy]] static GlobalSystemMediaTransportControlsSession        g_currentSession = nullptr;
static std::mutex  g_sessionMtx;
static bool g_userSwitchedSession = false;
static std::atomic<bool> g_forceSessionRefresh{false};
static std::atomic<int> g_sessionCount{0};
static winrt::event_token g_evSessionsChanged{};
static winrt::event_token g_evCurrentChanged{};
static winrt::event_token g_evMediaProps{};
static winrt::event_token g_evPlayback{};
static HANDLE g_mediaThread    = nullptr;
static HANDLE g_mediaStopEvent = nullptr;
static bool IsSystemLightTheme() {
    DWORD v = 0, sz = sizeof(v);
    if (RegGetValueW(HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"SystemUsesLightTheme", RRF_RT_DWORD, nullptr, &v, &sz) == ERROR_SUCCESS) {
        return v != 0;
    }
    v = 0; sz = sizeof(v);
    RegGetValueW(HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"AppsUseLightTheme", RRF_RT_DWORD, nullptr, &v, &sz);
    return v != 0;
}
static SolidColorBrush MakeBrush(winrt::Windows::UI::Color c) {
    SolidColorBrush b; b.Color(c); return b;
}
static void ApplyButtonGradient();
static bool IsHoverEffectEnabled(std::wstring const& mode) {
    return mode != L"off";
}
static bool IsHoverLightTheme(std::wstring const& mode) {
    if (mode == L"white") return true;
    if (mode == L"black") return false;
    return IsSystemLightTheme();
}
static winrt::Windows::UI::Color GetSystemButtonHoverColor(std::wstring const& mode) {
    if (IsHoverLightTheme(mode)) {
        return winrt::Windows::UI::Color{0x99, 0xFF, 0xFF, 0xFF};
    }
    return winrt::Windows::UI::Color{0x0F, 0xFF, 0xFF, 0xFF};
}
static winrt::Windows::UI::Color GetSystemButtonPressedColor(std::wstring const& mode) {
    if (IsHoverLightTheme(mode)) {
        return winrt::Windows::UI::Color{0x4D, 0xFF, 0xFF, 0xFF};
    }
    return winrt::Windows::UI::Color{0x0A, 0xFF, 0xFF, 0xFF};
}
static winrt::Windows::UI::Color GetSystemButtonBorderColor(std::wstring const& mode) {
    if (IsHoverLightTheme(mode)) {
        return winrt::Windows::UI::Color{0x08, 0x00, 0x00, 0x00};
    }
    return winrt::Windows::UI::Color{0x14, 0xFF, 0xFF, 0xFF};
}
static winrt::Windows::UI::Color GetSystemButtonBorderPressedColor(std::wstring const& mode) {
    if (IsHoverLightTheme(mode)) {
        return winrt::Windows::UI::Color{0x05, 0x00, 0x00, 0x00};
    }
    return winrt::Windows::UI::Color{0x0A, 0xFF, 0xFF, 0xFF};
}
[[clang::no_destroy]] static SolidColorBrush g_mediaHoverBrush   = nullptr;
[[clang::no_destroy]] static SolidColorBrush g_mediaPressedBrush = nullptr;
[[clang::no_destroy]] static SolidColorBrush g_playerHoverBrush   = nullptr;
[[clang::no_destroy]] static SolidColorBrush g_playerPressedBrush = nullptr;
[[clang::no_destroy]] static SolidColorBrush g_playerBorderBrush  = nullptr;
[[clang::no_destroy]] static SolidColorBrush g_playerBorderPressedBrush = nullptr;
// Island mode: the player hover box inside the media island (left half).
[[clang::no_destroy]] static Border g_mediaPlayerHover = nullptr;
static void ShowPlayerHover(bool on) {
    if (!g_mediaPlayerHover) return;
    try { g_mediaPlayerHover.Opacity(on ? 1.0 : 0.0); } catch (...) {}
}
static void EnsureHoverBrushes() {
    if (!g_mediaHoverBrush) {
        g_mediaHoverBrush   = SolidColorBrush(GetSystemButtonHoverColor(g_settings.mediaButtonsHoverEffectMode));
        g_mediaPressedBrush = SolidColorBrush(GetSystemButtonPressedColor(g_settings.mediaButtonsHoverEffectMode));
    }
    if (!g_playerHoverBrush) {
        g_playerHoverBrush   = SolidColorBrush(GetSystemButtonHoverColor(g_settings.playerHoverEffectMode));
        g_playerPressedBrush = SolidColorBrush(GetSystemButtonPressedColor(g_settings.playerHoverEffectMode));
        g_playerBorderBrush  = SolidColorBrush(GetSystemButtonBorderColor(g_settings.playerHoverEffectMode));
        g_playerBorderPressedBrush = SolidColorBrush(GetSystemButtonBorderPressedColor(g_settings.playerHoverEffectMode));
    }
}
static void UpdateHoverBrushColors() {
    if (g_mediaHoverBrush) {
        try { g_mediaHoverBrush.Color(GetSystemButtonHoverColor(g_settings.mediaButtonsHoverEffectMode)); } catch (...) {}
    } else {
        try { g_mediaHoverBrush = SolidColorBrush(GetSystemButtonHoverColor(g_settings.mediaButtonsHoverEffectMode)); } catch (...) {}
    }
    if (g_mediaPressedBrush) {
        try { g_mediaPressedBrush.Color(GetSystemButtonPressedColor(g_settings.mediaButtonsHoverEffectMode)); } catch (...) {}
    } else {
        try { g_mediaPressedBrush = SolidColorBrush(GetSystemButtonPressedColor(g_settings.mediaButtonsHoverEffectMode)); } catch (...) {}
    }
    if (g_playerHoverBrush) {
        try { g_playerHoverBrush.Color(GetSystemButtonHoverColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    } else {
        try { g_playerHoverBrush = SolidColorBrush(GetSystemButtonHoverColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    }
    if (g_playerPressedBrush) {
        try { g_playerPressedBrush.Color(GetSystemButtonPressedColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    } else {
        try { g_playerPressedBrush = SolidColorBrush(GetSystemButtonPressedColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    }
    if (g_playerBorderBrush) {
        try { g_playerBorderBrush.Color(GetSystemButtonBorderColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    } else {
        try { g_playerBorderBrush = SolidColorBrush(GetSystemButtonBorderColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    }
    if (g_playerBorderPressedBrush) {
        try { g_playerBorderPressedBrush.Color(GetSystemButtonBorderPressedColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    } else {
        try { g_playerBorderPressedBrush = SolidColorBrush(GetSystemButtonBorderPressedColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    }
}
static Border GetButtonTemplateRoot(Button const& btn) {
    if (!btn) return nullptr;
    try {
        btn.ApplyTemplate();
        if (VisualTreeHelper::GetChildrenCount(btn) > 0) {
            if (auto border = VisualTreeHelper::GetChild(btn, 0).try_as<Border>())
                return border;
        }
        if (auto named = btn.FindName(L"Root")) {
            if (auto border = named.try_as<Border>()) return border;
        }
    } catch (...) {}
    return nullptr;
}

[[clang::no_destroy]] static Style g_fluentMediaButtonStyle = nullptr;
static Style GetFluentMediaButtonStyle() {
    if (!g_fluentMediaButtonStyle) {
        static const wchar_t kStyleXaml[] = LR"(<Style TargetType="Button"
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml">
<Setter Property="Background" Value="Transparent"/>
<Setter Property="BorderBrush" Value="Transparent"/>
<Setter Property="BorderThickness" Value="0"/>
<Setter Property="UseSystemFocusVisuals" Value="False"/>
<Setter Property="Template">
    <Setter.Value>
    <ControlTemplate TargetType="Button">
        <Border x:Name="Root"
                Background="{TemplateBinding Background}"
                BorderBrush="{TemplateBinding BorderBrush}"
                BorderThickness="{TemplateBinding BorderThickness}"
                CornerRadius="{TemplateBinding CornerRadius}"
                Padding="{TemplateBinding Padding}">
        <Border.BackgroundTransition>
            <BrushTransition Duration="0:0:0.083"/>
        </Border.BackgroundTransition>
        <VisualStateManager.VisualStateGroups>
            <VisualStateGroup x:Name="CommonStates">
            <VisualState x:Name="Normal">
                <VisualState.Setters>
                    <Setter Target="Root.Background" Value="Transparent"/>
                    <Setter Target="Root.BorderBrush" Value="Transparent"/>
                </VisualState.Setters>
            </VisualState>
            <VisualState x:Name="PointerOver">
                <VisualState.Setters>
                    <Setter Target="Root.Background" Value="Transparent"/>
                    <Setter Target="Root.BorderBrush" Value="Transparent"/>
                </VisualState.Setters>
            </VisualState>
            <VisualState x:Name="Pressed">
                <VisualState.Setters>
                    <Setter Target="Root.Background" Value="Transparent"/>
                    <Setter Target="Root.BorderBrush" Value="Transparent"/>
                </VisualState.Setters>
            </VisualState>
            <VisualState x:Name="Disabled">
                <VisualState.Setters>
                    <Setter Target="Root.Background" Value="Transparent"/>
                    <Setter Target="Root.BorderBrush" Value="Transparent"/>
                </VisualState.Setters>
            </VisualState>
            </VisualStateGroup>
        </VisualStateManager.VisualStateGroups>
        <ContentPresenter Content="{TemplateBinding Content}"
                            ContentTransitions="{TemplateBinding ContentTransitions}"
                            ContentTemplate="{TemplateBinding ContentTemplate}"
                            HorizontalContentAlignment="{TemplateBinding HorizontalContentAlignment}"
                            VerticalContentAlignment="{TemplateBinding VerticalContentAlignment}"/>
        </Border>
    </ControlTemplate>
    </Setter.Value>
</Setter>
</Style>)";
        try {
            g_fluentMediaButtonStyle = winrt::Windows::UI::Xaml::Markup::XamlReader::Load(
                winrt::hstring(kStyleXaml)).as<Style>();
        } catch (...) {}
    }
    return g_fluentMediaButtonStyle;
}
static void ApplyFluentMediaButtonStyle(Button const& btn) {
    if (auto style = GetFluentMediaButtonStyle()) {
        btn.Style(style);
    }
}

static VisualState FindCommonState(Border const& root, std::wstring const& stateName) {
    if (!root) return nullptr;
    try {
        auto groups = VisualStateManager::GetVisualStateGroups(root);
        for (auto const& g : groups) {
            if (g.Name() == L"CommonStates") {
                for (auto const& s : g.States()) {
                    if (s.Name() == stateName) return s;
                }
            }
        }
    } catch (...) {}
    return nullptr;
}

static void SetStateBrush(Border const& root, std::wstring const& stateName, uint32_t setterIndex, Brush const& value) {
    if (!root) return;
    try {
        auto state = FindCommonState(root, stateName);
        if (!state) return;
        auto setters = state.Setters();
        if (setterIndex >= setters.Size()) return;
        if (auto setter = setters.GetAt(setterIndex).try_as<Setter>()) {
            setter.Value(value);
        }
    } catch (...) {}
}
static void ApplyHoverTransitionSetting(Border const& root) {
    if (!root) return;
    try {
        if (g_settings.enableHoverAnimation) {
            BrushTransition bt;
            bt.Duration(winrt::Windows::Foundation::TimeSpan(std::chrono::milliseconds(83)));
            root.BackgroundTransition(bt);
        } else {
            root.BackgroundTransition(nullptr);
        }
    } catch (...) {}
}
static void SetupCommonStates(
    Button const& btn,
    Brush const& normalBackground,
    Brush const& pointerOverBackground,
    Brush const& pressedBackground,
    Brush const& disabledBackground,
    Brush const& normalBorderBrush,
    Brush const& pointerOverBorderBrush,
    Brush const& pressedBorderBrush,
    Brush const& disabledBorderBrush)
{
    auto root = GetButtonTemplateRoot(btn);
    if (!root) return;
    ApplyHoverTransitionSetting(root);
    SetStateBrush(root, L"Normal",      0, normalBackground);
    SetStateBrush(root, L"Normal",      1, normalBorderBrush);
    SetStateBrush(root, L"PointerOver", 0, pointerOverBackground);
    SetStateBrush(root, L"PointerOver", 1, pointerOverBorderBrush);
    SetStateBrush(root, L"Pressed",     0, pressedBackground);
    SetStateBrush(root, L"Pressed",     1, pressedBorderBrush);
    SetStateBrush(root, L"Disabled",    0, disabledBackground);
    SetStateBrush(root, L"Disabled",    1, disabledBorderBrush);
    try {
        root.Background(normalBackground);
        root.BorderBrush(normalBorderBrush);
    } catch (...) {}
}
static void GoToCommonState(Button const& btn, bool effectEnabled, bool pressed, bool hovered) {
    if (!btn) return;
    try {
        winrt::hstring stateName = L"Normal";
        if (effectEnabled) {
            if (pressed)      stateName = L"Pressed";
            else if (hovered) stateName = L"PointerOver";
        }
        if (pressed && g_settings.enableHoverAnimation) {
            if (auto root = GetButtonTemplateRoot(btn)) {
                auto saved = root.BackgroundTransition();
                root.BackgroundTransition(nullptr);
                VisualStateManager::GoToState(btn, stateName, true);
                root.BackgroundTransition(saved);
                return;
            }
        }
        VisualStateManager::GoToState(btn, stateName, true);
    } catch (...) {}
}
static void RunWhenButtonReady(Button const& btn, std::function<void()> const& action) {
    if (!btn || !action) return;
    auto run = std::make_shared<std::function<void()>>(action);
    auto invoke = [btn, run]() {
        try {
            btn.ApplyTemplate();
            (*run)();
        } catch (...) {}
    };
    try {
        if (btn.IsLoaded()) {
            invoke();
        } else {
            btn.Loaded([invoke](auto const&, auto const&) { invoke(); });
        }
    } catch (...) {
        invoke();
    }
}

static void SetupMediaButtonCommonStates(Button const& btn) {
    auto transparent = MakeBrush({0x00, 0xFF, 0xFF, 0xFF});
    if (!IsHoverEffectEnabled(g_settings.mediaButtonsHoverEffectMode)) {
        SetupCommonStates(
            btn,
            transparent, transparent, transparent, transparent,
            transparent, transparent, transparent, transparent);
        return;
    }
    EnsureHoverBrushes();
    SetupCommonStates(
        btn,
        transparent,
        g_mediaHoverBrush,
        g_mediaPressedBrush,
        transparent,
        transparent, transparent, transparent, transparent);
}
static Brush MakeElevationBorderBrush(std::wstring const& mode) {
    bool light = IsHoverLightTheme(mode);
    winrt::Windows::UI::Color topColor, bottomColor;
    if (light) {
        topColor    = winrt::Windows::UI::Color{0x08, 0x00, 0x00, 0x00};
        bottomColor = winrt::Windows::UI::Color{0x10, 0x00, 0x00, 0x00};
    } else {
        topColor    = winrt::Windows::UI::Color{0x28, 0xFF, 0xFF, 0xFF};
        bottomColor = winrt::Windows::UI::Color{0x0A, 0xFF, 0xFF, 0xFF};
    }
    try {
        winrt::Windows::UI::Xaml::Media::LinearGradientBrush brush;
        brush.StartPoint(winrt::Windows::Foundation::Point(0.5f, 0.0f));
        brush.EndPoint(winrt::Windows::Foundation::Point(0.5f, 1.0f));
        winrt::Windows::UI::Xaml::Media::GradientStop s1, s2;
        s1.Color(topColor);    s1.Offset(0.0);
        s2.Color(bottomColor); s2.Offset(1.0);
        brush.GradientStops().Append(s1);
        brush.GradientStops().Append(s2);
        return brush;
    } catch (...) {
        return MakeBrush(topColor);
    }
}
static void SetupPlayerCommonStates(Button const& btn, Brush const& normalBg) {
    auto transparent = MakeBrush({0x00, 0xFF, 0xFF, 0xFF});
    if (g_settings.island || !IsHoverEffectEnabled(g_settings.playerHoverEffectMode)) {
        SetupCommonStates(
            btn,
            normalBg, normalBg, normalBg, normalBg,
            transparent, transparent, transparent, transparent);
        return;
    }
    EnsureHoverBrushes();
    auto elevBorder        = MakeElevationBorderBrush(g_settings.playerHoverEffectMode);
    auto elevBorderPressed = MakeBrush(GetSystemButtonBorderPressedColor(g_settings.playerHoverEffectMode));
    SetupCommonStates(
        btn,
        normalBg,
        g_playerHoverBrush,
        g_playerPressedBrush,
        normalBg,
        transparent,
        elevBorder,
        elevBorderPressed,
        transparent);
}
static void ApplyPlayerButtonState(Button const& btn, Brush const& /*normalBg*/, bool hovered, bool pressed) {
    if (!btn) return;
    if (g_settings.island) ShowPlayerHover(hovered || pressed);
    try {
        GoToCommonState(btn, IsHoverEffectEnabled(g_settings.playerHoverEffectMode), pressed, hovered);
    } catch (...) {}
}
static bool DecodeImageToBGRA(const std::vector<BYTE>& imgBytes,
                            std::vector<BYTE>& outPixels,
                            int& outW, int& outH)
{
    if (imgBytes.empty()) return false;
    IWICImagingFactory* pFactory = nullptr;
    if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr,
                                CLSCTX_INPROC_SERVER,
                                IID_PPV_ARGS(&pFactory))) || !pFactory)
        return false;
    IStream* pStream = SHCreateMemStream(imgBytes.data(), (UINT)imgBytes.size());
    if (!pStream) { pFactory->Release(); return false; }
    bool ok = false;
    IWICBitmapDecoder* pDecoder = nullptr;
    if (SUCCEEDED(pFactory->CreateDecoderFromStream(
            pStream, nullptr, WICDecodeMetadataCacheOnDemand, &pDecoder))) {
        IWICBitmapFrameDecode* pFrame = nullptr;
        if (SUCCEEDED(pDecoder->GetFrame(0, &pFrame))) {
            IWICFormatConverter* pConv = nullptr;
            if (SUCCEEDED(pFactory->CreateFormatConverter(&pConv))) {
                if (SUCCEEDED(pConv->Initialize(
                        pFrame, GUID_WICPixelFormat32bppBGRA,
                        WICBitmapDitherTypeNone, nullptr, 0.0,
                        WICBitmapPaletteTypeMedianCut))) {
                    UINT w = 0, h = 0;
                    pConv->GetSize(&w, &h);
                    if (w > 0 && h > 0) {
                        outPixels.resize((size_t)w * h * 4);
                        if (SUCCEEDED(pConv->CopyPixels(nullptr, w * 4,
                                (UINT)outPixels.size(), outPixels.data()))) {
                            outW = (int)w; outH = (int)h; ok = true;
                        }
                    }
                }
                pConv->Release();
            }
            pFrame->Release();
        }
        pDecoder->Release();
    }
    pStream->Release();
    pFactory->Release();
    return ok;
}
static void DownsampleBGRA(const std::vector<BYTE>& src, int srcW, int srcH,
                            std::vector<BYTE>& dst, int dstW, int dstH)
{
    dst.resize((size_t)dstW * dstH * 4);
    float xr = (float)srcW / dstW, yr = (float)srcH / dstH;
    for (int dy = 0; dy < dstH; ++dy) {
        for (int dx = 0; dx < dstW; ++dx) {
            float sx = (dx + 0.5f) * xr - 0.5f;
            float sy = (dy + 0.5f) * yr - 0.5f;
            int x0 = (int)sx; if (x0 < 0) x0 = 0;
            int y0 = (int)sy; if (y0 < 0) y0 = 0;
            int x1 = x0 + 1; if (x1 >= srcW) x1 = srcW - 1;
            int y1 = y0 + 1; if (y1 >= srcH) y1 = srcH - 1;
            float fx = sx - (float)x0; if (fx < 0) fx = 0;
            float fy = sy - (float)y0; if (fy < 0) fy = 0;
            const BYTE* p00 = &src[((size_t)y0 * srcW + x0) * 4];
            const BYTE* p10 = &src[((size_t)y0 * srcW + x1) * 4];
            const BYTE* p01 = &src[((size_t)y1 * srcW + x0) * 4];
            const BYTE* p11 = &src[((size_t)y1 * srcW + x1) * 4];
            BYTE* d = &dst[((size_t)dy * dstW + dx) * 4];
            for (int c = 0; c < 4; ++c) {
                float v = p00[c]*(1-fx)*(1-fy) + p10[c]*fx*(1-fy)
                        + p01[c]*(1-fx)*fy     + p11[c]*fx*fy;
                d[c] = (BYTE)(v < 0 ? 0 : v > 255 ? 255 : (int)v);
            }
        }
    }
}
static void ApplyBoxBlurBGRA(std::vector<BYTE>& pixels, int w, int h, int radius)
{
    if (radius < 1 || w < 1 || h < 1) return;
    std::vector<BYTE> temp(pixels.size());
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int r = 0, g = 0, b = 0, a = 0, count = 0;
            for (int dx = -radius; dx <= radius; ++dx) {
                int sx = x + dx;
                if (sx >= 0 && sx < w) {
                    const BYTE* p = &pixels[((size_t)y * w + sx) * 4];
                    b += p[0]; g += p[1]; r += p[2]; a += p[3];
                    count++;
                }
            }
            BYTE* d = &temp[((size_t)y * w + x) * 4];
            d[0] = (BYTE)(b / count);
            d[1] = (BYTE)(g / count);
            d[2] = (BYTE)(r / count);
            d[3] = (BYTE)(a / count);
        }
    }
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int r = 0, g = 0, b = 0, a = 0, count = 0;
            for (int dy = -radius; dy <= radius; ++dy) {
                int sy = y + dy;
                if (sy >= 0 && sy < h) {
                    const BYTE* p = &temp[((size_t)sy * w + x) * 4];
                    b += p[0]; g += p[1]; r += p[2]; a += p[3];
                    count++;
                }
            }
            BYTE* d = &pixels[((size_t)y * w + x) * 4];
            d[0] = (BYTE)(b / count);
            d[1] = (BYTE)(g / count);
            d[2] = (BYTE)(r / count);
            d[3] = (BYTE)(a / count);
        }
    }
}
static bool UpdateAlbumBlurBgCache(const std::vector<BYTE>& thumbBytes,
                                    int targetW, int targetH)
{
    if (thumbBytes.empty() || targetW <= 0 || targetH <= 0) {
        g_blurBgCache.Invalidate(); return false;
    }
    size_t artHash = 0;
    for (size_t i = 0; i < thumbBytes.size(); i += 512)
        artHash = artHash * 31 + thumbBytes[i];
    if (g_blurBgCache.artHash == artHash && g_blurBgCache.width == targetW &&
        g_blurBgCache.height == targetH && !g_blurBgCache.blurredPixels.empty())
        return true;
    std::vector<BYTE> srcPixels; int srcW = 0, srcH = 0;
    if (!DecodeImageToBGRA(thumbBytes, srcPixels, srcW, srcH)) return false;
    int blurDiv = 8;
    int smallW = srcW / blurDiv; if (smallW < 1) smallW = 1;
    int smallH = srcH / blurDiv; if (smallH < 1) smallH = 1;
    std::vector<BYTE> small;
    DownsampleBGRA(srcPixels, srcW, srcH, small, smallW, smallH);
    int blurRadius = std::clamp(g_settings.blurRadius, 1, 50);
    for (int i = 0; i < 3; ++i) {
        ApplyBoxBlurBGRA(small, smallW, smallH, blurRadius);
    }
    std::vector<BYTE> blurred;
    DownsampleBGRA(small, smallW, smallH, blurred, targetW, targetH);
    g_blurBgCache.blurredPixels = std::move(blurred);
    g_blurBgCache.width   = targetW;
    g_blurBgCache.height  = targetH;
    g_blurBgCache.artHash = artHash;
    return true;
}
static AlbumPalette ExtractAlbumPalette(const std::vector<BYTE>& thumbBytes) {
    const winrt::Windows::UI::Color fallbackPrimary{255, 18, 18, 18};
    const winrt::Windows::UI::Color fallbackSecondary{255, 45, 45, 45};
    if (thumbBytes.empty())
        return {fallbackPrimary, fallbackSecondary};
    try {
        std::vector<BYTE> pixels;
        int w = 0, h = 0;
        if (!DecodeImageToBGRA(thumbBytes, pixels, w, h) || w <= 0 || h <= 0 ||
            pixels.size() < (size_t)w * h * 4)
            return {fallbackPrimary, fallbackSecondary};
        struct Bucket { uint32_t r=0, g=0, b=0, n=0; };
        Bucket buckets[16][16][16]{};
        for (int y = 0; y < h; y += 4) {
            for (int x = 0; x < w; x += 4) {
                size_t idx = ((size_t)y * w + x) * 4;
                if (idx + 4 > pixels.size()) continue;
                BYTE pb = pixels[idx];
                BYTE pg = pixels[idx + 1];
                BYTE pr = pixels[idx + 2];
                int luma = (pr * 299 + pg * 587 + pb * 114) / 1000;
                if (luma < 24 || luma > 235) continue;
                auto& bk = buckets[pr >> 4][pg >> 4][pb >> 4];
                bk.r += pr; bk.g += pg; bk.b += pb; bk.n++;
            }
        }
        struct Cand { float w; BYTE r, g, b; };
        std::vector<Cand> cands;
        cands.reserve(64);
        for (int R = 0; R < 16; R++)
            for (int G = 0; G < 16; G++)
                for (int B = 0; B < 16; B++) {
                    auto& bk = buckets[R][G][B];
                    if (bk.n < 8) continue;
                    float fr = bk.r / (float)bk.n / 255.f;
                    float fg = bk.g / (float)bk.n / 255.f;
                    float fb = bk.b / (float)bk.n / 255.f;
                    float mx = std::max({fr, fg, fb});
                    float mn = std::min({fr, fg, fb});
                    float sat = mx > 0 ? (mx - mn) / mx : 0;
                    cands.push_back({bk.n * (0.3f + sat),
                                    (BYTE)(fr * 255), (BYTE)(fg * 255), (BYTE)(fb * 255)});
                }
        if (cands.empty())
            return {fallbackPrimary, fallbackSecondary};
        std::sort(cands.begin(), cands.end(),
                [](const Cand& a, const Cand& b){ return a.w > b.w; });
        winrt::Windows::UI::Color primary{255, cands[0].r, cands[0].g, cands[0].b};
        winrt::Windows::UI::Color secondary = primary;
        for (auto& c : cands) {
            int dr = (int)c.r - (int)cands[0].r;
            int dg = (int)c.g - (int)cands[0].g;
            int db = (int)c.b - (int)cands[0].b;
            if (dr*dr + dg*dg + db*db > 3264) {
                secondary = winrt::Windows::UI::Color{255, c.r, c.g, c.b};
                break;
            }
        }
        return {primary, secondary};
    } catch (...) {
        return {fallbackPrimary, fallbackSecondary};
    }
}
static DWORD GetWindowsAccentColor() {
    DWORD color = 0;
    BOOL opaque = FALSE;
    if (SUCCEEDED(DwmGetColorizationColor(&color, &opaque)))
        return 0xFF000000 | (color & 0x00FFFFFF);
    return 0xFF0078D4;
}
static winrt::Windows::UI::Color ParseColorWithSpecialValues(const std::wstring& colorStr, BYTE alpha = 255) {
    int r = 255, g = 255, b = 255;
    size_t pos1 = colorStr.find(L' ');
    size_t pos2 = colorStr.find(L' ', pos1 + 1);
    if (pos1 != std::wstring::npos && pos2 != std::wstring::npos) {
        try {
            r = std::stoi(colorStr.substr(0, pos1));
            g = std::stoi(colorStr.substr(pos1 + 1, pos2 - pos1 - 1));
            b = std::stoi(colorStr.substr(pos2 + 1));
            if (r == -1 && g == -1 && b == -1) {
                DWORD accentColor = GetWindowsAccentColor();
                return winrt::Windows::UI::Color{alpha,
                    (BYTE)((accentColor >> 16) & 0xFF),
                    (BYTE)((accentColor >> 8) & 0xFF),
                    (BYTE)(accentColor & 0xFF)};
            }
            if (r == -2 && g == -2 && b == -2) {
                if (g_cachedPaletteHash == 0) {
                    return winrt::Windows::UI::Color{0, 255, 255, 255};
                }
                return winrt::Windows::UI::Color{alpha,
                    g_cachedAlbumPalette.primary.R,
                    g_cachedAlbumPalette.primary.G,
                    g_cachedAlbumPalette.primary.B};
            }
            r = std::clamp(r, 0, 255);
            g = std::clamp(g, 0, 255);
            b = std::clamp(b, 0, 255);
        } catch (...) {}
    }
    return winrt::Windows::UI::Color{alpha, (BYTE)r, (BYTE)g, (BYTE)b};
}
static winrt::Windows::UI::Color ParseColorWithThemeSupport(const std::wstring& colorStr, BYTE alpha) {
    size_t dollarPos = colorStr.find(L'$');
    if (dollarPos != std::wstring::npos) {
        std::wstring lightColorStr = colorStr.substr(0, dollarPos);
        std::wstring darkColorStr = colorStr.substr(dollarPos + 1);
        lightColorStr.erase(0, lightColorStr.find_first_not_of(L" \t"));
        lightColorStr.erase(lightColorStr.find_last_not_of(L" \t") + 1);
        darkColorStr.erase(0, darkColorStr.find_first_not_of(L" \t"));
        darkColorStr.erase(darkColorStr.find_last_not_of(L" \t") + 1);
        if (IsSystemLightTheme()) {
            return ParseColorWithSpecialValues(lightColorStr, alpha);
        } else {
            return ParseColorWithSpecialValues(darkColorStr, alpha);
        }
    } else {
        return ParseColorWithSpecialValues(colorStr, alpha);
    }
}
static winrt::Windows::UI::Color TextColor() {
    BYTE alpha = (BYTE)((g_settings.titleColorOpacity / 100.0) * 255);
    return ParseColorWithThemeSupport(g_settings.titleColor, alpha);
}
static winrt::Windows::UI::Color ArtistColor() {
    BYTE alpha = (BYTE)((g_settings.artistColorOpacity / 100.0) * 255);
    return ParseColorWithThemeSupport(g_settings.artistColor, alpha);
}
static winrt::Windows::UI::Color ButtonColor() {
    BYTE alpha = (BYTE)((g_settings.buttonColorOpacity / 100.0) * 255);
    return ParseColorWithThemeSupport(g_settings.buttonColor, alpha);
}
static winrt::Windows::UI::Color ContextMenuIconColor() {
    BYTE alpha = (BYTE)((g_settings.contextMenuIconOpacity / 100.0) * 255);
    const std::wstring& clr = g_settings.contextMenuIconColor;
    if (clr.empty()) {
        return ParseColorWithThemeSupport(g_settings.buttonColor, alpha);
    }
    return ParseColorWithThemeSupport(clr, alpha);
}
static const std::wstring& ContextMenuIconStyle() {
    if (g_settings.contextMenuIconStyle == L"as_media_buttons")
        return g_settings.iconStyle;
    return g_settings.contextMenuIconStyle;
}
static Brush MakeAlbumBlurBrush(const std::vector<BYTE>& thumbBytes,
                                int panelW, int panelH)
{
    if (!UpdateAlbumBlurBgCache(thumbBytes, panelW, panelH) ||
        g_blurBgCache.blurredPixels.empty())
        return MakeBrush({0x00, 0x00, 0x00, 0x00});
    try {
        size_t bytesNeeded = (size_t)panelW * panelH * 4;
        WriteableBitmap wb(panelW, panelH);
        auto buf = wb.PixelBuffer();
        auto byteAccess = buf.as<Windows::Storage::Streams::IBufferByteAccess>();
        BYTE* pixels = nullptr;
        byteAccess->Buffer(&pixels);
        if (pixels && g_blurBgCache.blurredPixels.size() >= bytesNeeded)
            memcpy(pixels, g_blurBgCache.blurredPixels.data(), bytesNeeded);
        buf.Length(static_cast<uint32_t>(bytesNeeded));
        wb.Invalidate();
        ImageBrush brush;
        brush.ImageSource(wb);
        brush.Stretch(Stretch::UniformToFill);
        return brush;
    } catch (...) {}
    return MakeBrush({0x00, 0x00, 0x00, 0x00});
}
static Brush MakeBackgroundBrush() {
    auto& t = g_settings.backgroundType;
    BYTE opacity = (BYTE)((g_settings.solidOpacity / 100.0) * 255);
    auto color1 = ParseColorWithThemeSupport(g_settings.solidColor, opacity);
    auto color2 = ParseColorWithSpecialValues(g_settings.solidColor2, opacity);
    auto gradientColor2 = ParseColorWithSpecialValues(g_settings.gradientColor2, opacity);
    if (t == L"gradient") {
        try {
            winrt::Windows::UI::Xaml::Media::LinearGradientBrush brush;
            double angleRad = (g_settings.gradientAngle % 360) * 3.14159265358979323846 / 180.0;
            double startX = 0.5 - 0.5 * std::cos(angleRad);
            double startY = 0.5 - 0.5 * std::sin(angleRad);
            double endX = 0.5 + 0.5 * std::cos(angleRad);
            double endY = 0.5 + 0.5 * std::sin(angleRad);
            brush.StartPoint(winrt::Windows::Foundation::Point((float)startX, (float)startY));
            brush.EndPoint(winrt::Windows::Foundation::Point((float)endX, (float)endY));
            double balancePoint = std::clamp(g_settings.gradientBalance, 0, 100) / 100.0;
            winrt::Windows::UI::Xaml::Media::GradientStop stop1;
            stop1.Color(color2);
            stop1.Offset(0.0);
            winrt::Windows::UI::Xaml::Media::GradientStop stop2;
            stop2.Color(gradientColor2);
            stop2.Offset(balancePoint);
            winrt::Windows::UI::Xaml::Media::GradientStop stop3;
            stop3.Color(gradientColor2);
            stop3.Offset(1.0);
            brush.GradientStops().Append(stop1);
            brush.GradientStops().Append(stop2);
            brush.GradientStops().Append(stop3);
            return brush;
        } catch (...) {}
    }
    if (t == L"acrylic") {
        try {
            winrt::Windows::UI::Xaml::Media::AcrylicBrush brush;
            brush.BackgroundSource(winrt::Windows::UI::Xaml::Media::AcrylicBackgroundSource::HostBackdrop);
            auto col = winrt::Windows::UI::Color{0xFF, color1.R, color1.G, color1.B};
            brush.TintColor(col);
            brush.TintOpacity(g_settings.acrylicTintOpacity / 100.0);
            brush.FallbackColor(winrt::Windows::UI::Color{0xCC, color1.R, color1.G, color1.B});
            return brush;
        } catch (...) {}
    }
    if (t == L"mica" || t == L"mica_alt") {
        BYTE micaAlpha = (BYTE)((g_settings.micaOpacity / 100.0) * 255);
        auto col = winrt::Windows::UI::Color{micaAlpha, color1.R, color1.G, color1.B};
        return MakeBrush(col);
    }
    if (t == L"solid") {
        return MakeBrush(color1);
    }
    if (t == L"album_art_blur") {
        return MakeBrush({0x00, 0xFF, 0xFF, 0xFF});
    }
    return MakeBrush({0x00, 0xFF, 0xFF, 0xFF});
}
static FrameworkElement FindChildByName(FrameworkElement const& root, std::wstring_view name, int depth = 32) {
    if (!root || depth == 0) return nullptr;
    int n = VisualTreeHelper::GetChildrenCount(root);
    for (int i = 0; i < n; ++i) {
        auto child = VisualTreeHelper::GetChild(root, i).try_as<FrameworkElement>();
        if (!child) continue;
        if (child.Name() == name) return child;
        if (auto found = FindChildByName(child, name, depth - 1)) return found;
    }
    return nullptr;
}
static void DumpXamlTree(DependencyObject const& node, int depth, int maxDepth) {
    if (!node || depth > maxDepth) return;
    std::wstring indent(depth * 2, L' ');
    auto fe = node.try_as<FrameworkElement>();
    std::wstring name  = fe ? std::wstring(fe.Name()) : L"";
    winrt::hstring typeHstr = winrt::get_class_name(node);
    std::wstring type  = std::wstring(typeHstr);
    auto dot = type.rfind(L'.');
    if (dot != std::wstring::npos) type = type.substr(dot + 1);
    int col = fe ? Grid::GetColumn(fe) : -1;
    if (!name.empty()) Wh_Log(L"%ls[%ls] name='%ls' col=%d", indent.c_str(), type.c_str(), name.c_str(), col);
    else Wh_Log(L"%ls[%ls]", indent.c_str(), type.c_str());
    int n = VisualTreeHelper::GetChildrenCount(node);
    for (int i = 0; i < n; ++i) {
        auto child = VisualTreeHelper::GetChild(node, i);
        if (child) DumpXamlTree(child, depth + 1, maxDepth);
    }
}
static constexpr wchar_t kGridName[]        = L"FluentMediaBar";
static constexpr wchar_t kArtImageName[]    = L"FluentMedia_Art";
static constexpr wchar_t kAppIconImageName[]= L"FluentMedia_AppIcon";
static constexpr wchar_t kAnchorOverlayName[]= L"FluentMedia_DebugAnchorTarget";
static constexpr wchar_t kTextStackName[]   = L"FluentMedia_TextStack";
static constexpr wchar_t kTitleBlockName[]  = L"FluentMedia_Title";
static constexpr wchar_t kArtistBlockName[] = L"FluentMedia_Artist";
static constexpr wchar_t kPlayBtnName[]     = L"FluentMedia_Play";
static constexpr wchar_t kPrevBtnName[]     = L"FluentMedia_Prev";
static constexpr wchar_t kNextBtnName[]     = L"FluentMedia_Next";
static constexpr wchar_t kRewindBtnName[]   = L"FluentMedia_Rewind";
static constexpr wchar_t kForwardBtnName[]  = L"FluentMedia_Forward";
static constexpr wchar_t kShuffleBtnName[]  = L"FluentMedia_Shuffle";
static constexpr wchar_t kRepeatBtnName[]   = L"FluentMedia_Repeat";
static constexpr wchar_t kSwitchSessionsBtnName[] = L"FluentMedia_SwitchSessions";
static int  g_idleSeconds  = 0;
static int  g_idleTicks    = 0;
static std::atomic<bool> g_hiddenByIdle{false};
static std::chrono::steady_clock::time_point g_lastMediaTime = std::chrono::steady_clock::now();
static void SwitchMediaSession();
static void SendMediaCommandAsync(int cmd) {
    SpawnTrackedWorker([cmd]() {
        if (g_unloading) return;
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
        try {
            GlobalSystemMediaTransportControlsSession session{nullptr};
            { std::lock_guard<std::mutex> lk(g_sessionMtx); session = g_currentSession; }
            if (session) {
                switch (cmd) {
                    case 1: session.TrySkipPreviousAsync().get();    break;
                    case 2: {
                        auto info = session.GetPlaybackInfo();
                        bool isPlaying = info &&
                            info.PlaybackStatus() == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing;
                        if (isPlaying)
                            session.TryPauseAsync().get();
                        else
                            session.TryPlayAsync().get();
                        break;
                    }
                    case 3: session.TrySkipNextAsync().get();        break;
                    case 4:
                        try {
                            auto result = session.TryStopAsync().get();
                            if (!result) {
                                session.TryPauseAsync().get();
                                session.TryChangePlaybackPositionAsync(0).get();
                            }
                        } catch (...) {
                            try {
                                session.TryPauseAsync().get();
                                session.TryChangePlaybackPositionAsync(0).get();
                            } catch (...) {
                                Wh_Log(L"SendMediaCommandAsync: Fallback also failed");
                            }
                        }
                        break;
                    case 5:
                        try {
                            auto timeline = session.GetTimelineProperties();
                            auto currentPos = timeline.Position();
                            auto newPos = currentPos - std::chrono::seconds(5);
                            if (newPos.count() < 0) newPos = std::chrono::seconds(0);
                            session.TryChangePlaybackPositionAsync(newPos.count()).get();
                        } catch (...) {}
                        break;
                    case 6:
                        try {
                            auto timeline = session.GetTimelineProperties();
                            auto currentPos = timeline.Position();
                            auto endTime = timeline.EndTime();
                            auto newPos = currentPos + std::chrono::seconds(5);
                            if (newPos > endTime) newPos = endTime;
                            session.TryChangePlaybackPositionAsync(newPos.count()).get();
                        } catch (...) {}
                        break;
                    case 7:
                        try {
                            bool currentShuffle = g_shuffleEnabled.load();
                            if (session.TryChangeShuffleActiveAsync(!currentShuffle).get()) {
                                g_shuffleEnabled = !currentShuffle;
                                DispatchMediaUpdate();
                            }
                        } catch (...) {}
                        break;
                    case 8:
                        try {
                            RepeatMode current = g_repeatMode.load();
                            winrt::Windows::Media::MediaPlaybackAutoRepeatMode mode;
                            RepeatMode next;
                            switch (current) {
                                case RepeatMode::Off:
                                    mode = winrt::Windows::Media::MediaPlaybackAutoRepeatMode::List;
                                    next = RepeatMode::All;
                                    break;
                                case RepeatMode::All:
                                    mode = winrt::Windows::Media::MediaPlaybackAutoRepeatMode::Track;
                                    next = RepeatMode::One;
                                    break;
                                case RepeatMode::One:
                                default:
                                    mode = winrt::Windows::Media::MediaPlaybackAutoRepeatMode::None;
                                    next = RepeatMode::Off;
                                    break;
                            }
                            if (session.TryChangeAutoRepeatModeAsync(mode).get()) {
                                g_repeatMode = next;
                                DispatchMediaUpdate();
                            }
                        } catch (...) {}
                        break;
                    case 9:
                        SwitchMediaSession();
                        break;
                    case 10:
                        try {
                            if (session.TryChangeAutoRepeatModeAsync(winrt::Windows::Media::MediaPlaybackAutoRepeatMode::None).get()) {
                                g_repeatMode = RepeatMode::Off;
                                DispatchMediaUpdate();
                            }
                        } catch (...) {}
                        break;
                    case 11:
                        try {
                            if (session.TryChangeAutoRepeatModeAsync(winrt::Windows::Media::MediaPlaybackAutoRepeatMode::List).get()) {
                                g_repeatMode = RepeatMode::All;
                                DispatchMediaUpdate();
                            }
                        } catch (...) {}
                        break;
                    case 12:
                        try {
                            if (session.TryChangeAutoRepeatModeAsync(winrt::Windows::Media::MediaPlaybackAutoRepeatMode::Track).get()) {
                                g_repeatMode = RepeatMode::One;
                                DispatchMediaUpdate();
                            }
                        } catch (...) {}
                        break;
                }
            }
        } catch (...) {}
        winrt::uninit_apartment();
    });
}
struct TextScrollState {
    double offset    = 0.0;
    double textWidth = 0.0;
    double viewWidth = 0.0;
    bool   forward   = true;
    bool   active    = false;
    bool   pausing   = false;
    int    pauseTick = 0;
    int    tickMs    = 16;
};
static TextScrollState g_titleScroll;
static TextScrollState g_artistScroll;
static void ResetScrollState(TextScrollState& s);
static void FetchMediaPropertiesAsync();
static void FetchPlaybackInfoAsync();
static void OnSessionsChanged();
static void AttachToSession(GlobalSystemMediaTransportControlsSession session);
static void SwitchMediaSession();
static void SwitchMediaSession() {
    GlobalSystemMediaTransportControlsSessionManager mgr{nullptr};
    GlobalSystemMediaTransportControlsSession curSession{nullptr};
    {
        std::lock_guard<std::mutex> lk(g_sessionMtx);
        if (!g_sessionMgr) return;
        mgr = g_sessionMgr;
        curSession = g_currentSession;
        g_userSwitchedSession = true;
    }
    if (!mgr) return;
    GlobalSystemMediaTransportControlsSession nextSession{nullptr};
    try {
        auto sessions = mgr.GetSessions();
        int count = (int)sessions.Size();
        if (count <= 1) return;
        int currentIndex = -1;
        if (curSession) {
            auto curId = curSession.SourceAppUserModelId();
            for (int i = 0; i < count; ++i) {
                if (sessions.GetAt(i).SourceAppUserModelId() == curId) {
                    currentIndex = i;
                    break;
                }
            }
        }
        int nextIndex = (currentIndex + 1) % count;
        nextSession = sessions.GetAt(nextIndex);
    } catch (...) { return; }
    if (nextSession) {
        AttachToSession(nextSession);
    }
}
static std::mutex g_deviceEnumeratorMtx;
static void InitAudioDeviceEnumerator() {
    std::lock_guard<std::mutex> lk(g_deviceEnumeratorMtx);
    if (!g_pDeviceEnumerator) {
        CoCreateInstance(
            XIID_MMDeviceEnumerator, NULL, CLSCTX_INPROC_SERVER,
            XIID_IMMDeviceEnumerator, (LPVOID*)&g_pDeviceEnumerator);
    }
}
static void CleanupAudioDeviceEnumerator() {
    std::lock_guard<std::mutex> lk(g_deviceEnumeratorMtx);
    if (g_pDeviceEnumerator) {
        g_pDeviceEnumerator->Release();
        g_pDeviceEnumerator = nullptr;
    }
}
static bool AdjustAppVolumeByAUMID(const std::wstring& aumid, float volumeDelta) {
    InitAudioDeviceEnumerator();
    std::lock_guard<std::mutex> lk(g_deviceEnumeratorMtx);
    if (!g_pDeviceEnumerator) return false;
    winrt::com_ptr<IMMDevice> defaultDevice;
    HRESULT hr = g_pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, defaultDevice.put());
    if (FAILED(hr)) return false;
    winrt::com_ptr<IAudioSessionManager2> sessionManager;
    hr = defaultDevice->Activate(XIID_IAudioSessionManager2, CLSCTX_ALL, NULL, sessionManager.put_void());
    if (FAILED(hr)) return false;
    winrt::com_ptr<IAudioSessionEnumerator> sessionEnumerator;
    hr = sessionManager->GetSessionEnumerator(sessionEnumerator.put());
    if (FAILED(hr)) return false;
    int sessionCount = 0;
    hr = sessionEnumerator->GetCount(&sessionCount);
    if (FAILED(hr)) return false;
    bool found = false;
    for (int i = 0; i < sessionCount; i++) {
        winrt::com_ptr<IAudioSessionControl> sessionControl;
        hr = sessionEnumerator->GetSession(i, sessionControl.put());
        if (FAILED(hr)) continue;
        winrt::com_ptr<IAudioSessionControl2> sessionControl2;
        hr = sessionControl->QueryInterface(__uuidof(IAudioSessionControl2), sessionControl2.put_void());
        if (FAILED(hr)) continue;
        LPWSTR sessionId = nullptr;
        hr = sessionControl2->GetSessionIdentifier(&sessionId);
        if (SUCCEEDED(hr) && sessionId) {
            std::wstring sessionIdStr(sessionId);
            CoTaskMemFree(sessionId);
            if (sessionIdStr.find(aumid) != std::wstring::npos) {
                winrt::com_ptr<ISimpleAudioVolume> vol;
                if (SUCCEEDED(sessionControl->QueryInterface(__uuidof(ISimpleAudioVolume), vol.put_void()))) {
                    float currentVolume = 0.0f;
                    if (SUCCEEDED(vol->GetMasterVolume(&currentVolume))) {
                        float newVolume = std::clamp(currentVolume + volumeDelta, 0.0f, 1.0f);
                        vol->SetMasterVolume(newVolume, NULL);
                        found = true;
                    }
                }
            }
        }
    }
    return found;
}
static void ChangeSystemVolume(bool increase) {
    InitAudioDeviceEnumerator();
    std::lock_guard<std::mutex> lk(g_deviceEnumeratorMtx);
    if (!g_pDeviceEnumerator) return;
    winrt::com_ptr<IMMDevice> defaultDevice;
    HRESULT hr = g_pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, defaultDevice.put());
    if (FAILED(hr)) return;
    winrt::com_ptr<IAudioEndpointVolume> endpointVolume;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, endpointVolume.put_void());
    if (FAILED(hr)) return;
    float currentVolume = 0.0f;
    if (SUCCEEDED(endpointVolume->GetMasterVolumeLevelScalar(&currentVolume))) {
        float newVolume = currentVolume + (increase ? 0.005f : -0.005f);
        newVolume = std::clamp(newVolume, 0.0f, 1.0f);
        endpointVolume->SetMasterVolumeLevelScalar(newVolume, NULL);
    }
    HWND hShellTrayWnd = FindWindow(L"Shell_TrayWnd", nullptr);
    if (hShellTrayWnd) {
        SHORT appCommand = increase ? APPCOMMAND_VOLUME_UP : APPCOMMAND_VOLUME_DOWN;
        PostMessage(hShellTrayWnd, WM_APPCOMMAND, (WPARAM)hShellTrayWnd,
                    MAKELPARAM(0, appCommand));
    }
}
static std::wstring ToLowerCopy(std::wstring value);
static std::wstring GetWindowAppUserModelId(HWND hWnd);
static void ShowMediaContextMenu(FrameworkElement const& target);
static void ShowMiniPlayerFlyout(FrameworkElement const& target);
[[maybe_unused]]
static void ExecuteMediaAction(const std::wstring& action, FrameworkElement const& sourceElement = nullptr) {
    if (action == L"none") {
        return;
    } else if (action == L"open_context_menu") {
        if (sourceElement) {
            ShowMediaContextMenu(sourceElement);
        }
        return;
    } else if (action == L"open_mini_player") {
        if (sourceElement) {
            ShowMiniPlayerFlyout(sourceElement);
        }
        return;
    } else if (action == L"switch_session") {
        SwitchMediaSession();
    } else if (action == L"play_pause") {
        SendMediaCommandAsync(2);
        DispatchMediaUpdate();
    } else if (action == L"next_track") {
        SendMediaCommandAsync(3);
        DispatchMediaUpdate();
    } else if (action == L"prev_track") {
        SendMediaCommandAsync(1);
        DispatchMediaUpdate();
    } else if (action == L"stop") {
        g_forceSessionRefresh = true;
        SendMediaCommandAsync(4);
        DispatchMediaUpdate();
        SpawnTrackedWorker([]() {
            for (DWORD delay : {300, 1200, 2500}) {
                Sleep(delay);
                if (g_unloading) return;
                g_forceSessionRefresh = true;
                OnSessionsChanged();
                FetchPlaybackInfoAsync();
                FetchMediaPropertiesAsync();
            }
        });
    } else if (action == L"rewind_5s") {
        SendMediaCommandAsync(5);
        DispatchMediaUpdate();
    } else if (action == L"forward_5s") {
        SendMediaCommandAsync(6);
        DispatchMediaUpdate();
    } else if (action == L"toggle_shuffle") {
        SendMediaCommandAsync(7);
        DispatchMediaUpdate();
    } else if (action == L"toggle_repeat") {
        SendMediaCommandAsync(8);
        DispatchMediaUpdate();
} else if (action == L"open_app") {
        SpawnTrackedWorker([]() {
            std::wstring title, appAumid;
            {
                std::lock_guard<std::mutex> lk(g_mediaMtx);
                title = g_media.title;
            }
            {
                GlobalSystemMediaTransportControlsSession sessionCopy{nullptr};
                {
                    std::lock_guard<std::mutex> lk(g_sessionMtx);
                    sessionCopy = g_currentSession;
                }
                if (sessionCopy) {
                    try {
                        appAumid = std::wstring(sessionCopy.SourceAppUserModelId());
                    } catch (...) {}
                }
            }
            struct WindowSearch {
                std::wstring targetTitle;
                std::wstring targetAumid;
                HWND aumidHwnd = nullptr;
                HWND processHwnd = nullptr;
                HWND titleHwnd = nullptr;
            };
            WindowSearch search;
            search.targetTitle = title;
            std::transform(search.targetTitle.begin(), search.targetTitle.end(), search.targetTitle.begin(), ::towlower);
            search.targetAumid = appAumid;
            std::transform(search.targetAumid.begin(), search.targetAumid.end(), search.targetAumid.begin(), ::towlower);
            EnumWindows([](HWND hwnd, LPARAM lParam) CALLBACK -> BOOL {
                if (!IsWindowVisible(hwnd)) return TRUE;
                WINDOWINFO wi{};
                wi.cbSize = sizeof(wi);
                GetWindowInfo(hwnd, &wi);
                if ((wi.dwStyle & WS_CHILD) != 0) return TRUE;
                auto* s = reinterpret_cast<WindowSearch*>(lParam);
                if (!s->aumidHwnd && !s->targetAumid.empty()) {
                    IPropertyStore* pps = nullptr;
                    if (SUCCEEDED(SHGetPropertyStoreForWindow(hwnd, IID_PPV_ARGS(&pps)))) {
                        PROPVARIANT var;
                        PropVariantInit(&var);
                        if (SUCCEEDED(pps->GetValue(PKEY_AppUserModel_ID, &var)) && var.vt == VT_LPWSTR) {
                            std::wstring winAumid(var.pwszVal);
                            std::transform(winAumid.begin(), winAumid.end(), winAumid.begin(), ::towlower);
                            if (winAumid == s->targetAumid ||
                                winAumid.find(s->targetAumid) != std::wstring::npos ||
                                s->targetAumid.find(winAumid) != std::wstring::npos) {
                                s->aumidHwnd = hwnd;
                            }
                        }
                        PropVariantClear(&var);
                        pps->Release();
                    }
                }
                if (!s->processHwnd && !s->targetAumid.empty()) {
                    DWORD pid = 0;
                    GetWindowThreadProcessId(hwnd, &pid);
                    if (pid) {
                        wchar_t procPath[MAX_PATH]{};
                        HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
                        if (hProc) {
                            DWORD sz = MAX_PATH;
                            QueryFullProcessImageNameW(hProc, 0, procPath, &sz);
                            CloseHandle(hProc);
                        }
                        if (procPath[0]) {
                            std::wstring stem = procPath;
                            auto slash = stem.find_last_of(L"\\/");
                            if (slash != std::wstring::npos) stem = stem.substr(slash + 1);
                            auto dot = stem.rfind(L'.');
                            if (dot != std::wstring::npos) stem = stem.substr(0, dot);
                            std::transform(stem.begin(), stem.end(), stem.begin(), ::towlower);
                            if (!stem.empty() &&
                                (s->targetAumid.find(stem) != std::wstring::npos ||
                                stem.find(s->targetAumid) != std::wstring::npos)) {
                                s->processHwnd = hwnd;
                            }
                        }
                    }
                }
                if (!s->titleHwnd && !s->targetTitle.empty()) {
                    wchar_t windowTitle[512];
                    if (GetWindowTextW(hwnd, windowTitle, 512) > 0) {
                        std::wstring wTitle(windowTitle);
                        std::transform(wTitle.begin(), wTitle.end(), wTitle.begin(), ::towlower);
                        if (wTitle.find(s->targetTitle) != std::wstring::npos) {
                            s->titleHwnd = hwnd;
                        }
                    }
                }
                return TRUE;
            }, reinterpret_cast<LPARAM>(&search));
            HWND targetWindow = search.aumidHwnd
                ? search.aumidHwnd
                : (search.processHwnd ? search.processHwnd : search.titleHwnd);
            if (targetWindow) {
                if (IsIconic(targetWindow)) {
                    ShowWindow(targetWindow, SW_RESTORE);
                }
                
                HWND hCurWnd = GetForegroundWindow();
                if (hCurWnd && hCurWnd != targetWindow) {
                    DWORD dwMyID = GetCurrentThreadId();
                    DWORD dwCurID = GetWindowThreadProcessId(hCurWnd, NULL);
                    AttachThreadInput(dwCurID, dwMyID, TRUE);
                    SetForegroundWindow(targetWindow);
                    BringWindowToTop(targetWindow);
                    AttachThreadInput(dwCurID, dwMyID, FALSE);
                } else {
                    SetForegroundWindow(targetWindow);
                    BringWindowToTop(targetWindow);
                }
                return;
            }
            if (!appAumid.empty()) {
                std::wstring shellPath = L"shell:AppsFolder\\" + appAumid;
                ShellExecuteW(nullptr, L"open", shellPath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
            }
        });
    }
}
static std::wstring ToLowerCopy(std::wstring value) {
    for (auto& c : value) c = towlower(c);
    return value;
}
static std::wstring PathFileStem(std::wstring path) {
    auto slash = path.find_last_of(L"\\/");
    if (slash != std::wstring::npos) path = path.substr(slash + 1);
    auto dot = path.rfind(L'.');
    if (dot != std::wstring::npos) path = path.substr(0, dot);
    return path;
}
static std::wstring TrimCopy(std::wstring value) {
    const wchar_t* ws = L" \t\r\n";
    size_t first = value.find_first_not_of(ws);
    if (first == std::wstring::npos) return L"";
    size_t last = value.find_last_not_of(ws);
    return value.substr(first, last - first + 1);
}
static bool IsIgnoredMediaApp(const std::wstring& appUserModelId) {
    if (g_settings.ignoredProcesses.empty() || appUserModelId.empty()) return false;
    std::wstring appLower = ToLowerCopy(appUserModelId);
    std::wstring appStemLower = ToLowerCopy(PathFileStem(appUserModelId));
    size_t start = 0;
    while (start <= g_settings.ignoredProcesses.size()) {
        size_t end = g_settings.ignoredProcesses.find(L';', start);
        std::wstring item = TrimCopy(g_settings.ignoredProcesses.substr(
            start, end == std::wstring::npos ? std::wstring::npos : end - start));
        if (!item.empty()) {
            std::wstring itemLower = ToLowerCopy(item);
            std::wstring itemStemLower = ToLowerCopy(PathFileStem(item));
            if (appLower == itemLower ||
                appStemLower == itemStemLower ||
                appLower.find(itemLower) != std::wstring::npos ||
                appLower.find(itemStemLower) != std::wstring::npos) {
                return true;
            }
        }
        if (end == std::wstring::npos) break;
        start = end + 1;
    }
    return false;
}
static bool IsBrowserAumid(const std::wstring& appUserModelId) {
    if (appUserModelId.empty()) return false;
    static const wchar_t* kBrowserSubstrings[] = {
        L"chrome", L"msedge", L"firefox", L"opera", L"brave", L"vivaldi"
    };
    std::wstring lower = ToLowerCopy(appUserModelId);
    for (auto* needle : kBrowserSubstrings) {
        if (lower.find(needle) != std::wstring::npos) return true;
    }
    return false;
}
static std::wstring GetWindowAppUserModelId(HWND hWnd) {
    static const PROPERTYKEY kAppUserModelIdKey = {
        {0x9F4C2855, 0x9F79, 0x4B39, {0xA8, 0xD0, 0xE1, 0xD4, 0x2D, 0xE1, 0xD5, 0xF3}},
        5
    };
    std::wstring result;
    IPropertyStore* store = nullptr;
    if (SUCCEEDED(SHGetPropertyStoreForWindow(hWnd, IID_PPV_ARGS(&store))) && store) {
        PROPVARIANT pv;
        PropVariantInit(&pv);
        if (SUCCEEDED(store->GetValue(kAppUserModelIdKey, &pv)) && pv.vt == VT_LPWSTR && pv.pwszVal) {
            result = pv.pwszVal;
        }
        PropVariantClear(&pv);
        store->Release();
    }
    return result;
}
static bool AppIdMatchesProcess(const std::wstring& appUserModelId, HWND hWnd, DWORD* outPid = nullptr, std::wstring* outProcPath = nullptr) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (outPid) *outPid = pid;
    if (!pid) return false;
    std::wstring windowAumid = GetWindowAppUserModelId(hWnd);
    std::wstring appLower = ToLowerCopy(appUserModelId);
    std::wstring windowAumidLower = ToLowerCopy(windowAumid);
    if (!windowAumidLower.empty() &&
        (appLower == windowAumidLower ||
        appLower.find(windowAumidLower) != std::wstring::npos ||
        windowAumidLower.find(appLower) != std::wstring::npos)) {
        return true;
    }
    wchar_t procPath[MAX_PATH] = {};
    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (hProc) {
        DWORD sz = MAX_PATH;
        QueryFullProcessImageNameW(hProc, 0, procPath, &sz);
        CloseHandle(hProc);
    }
    if (outProcPath) *outProcPath = procPath;
    std::wstring procLower = ToLowerCopy(PathFileStem(procPath));
    if (procLower.empty()) return false;
    std::wstring appStemLower = ToLowerCopy(PathFileStem(appUserModelId));
    return appLower.find(procLower) != std::wstring::npos ||
        procLower.find(appLower) != std::wstring::npos ||
        appStemLower.find(procLower) != std::wstring::npos ||
        procLower.find(appStemLower) != std::wstring::npos ||
        (!windowAumidLower.empty() &&
            (windowAumidLower.find(procLower) != std::wstring::npos ||
            procLower.find(windowAumidLower) != std::wstring::npos));
}
static std::vector<BYTE> RenderIconToBytes(HICON hIcon, int iconSize) {
    if (!hIcon || iconSize <= 0) return {};
    ICONINFO ii{};
    if (!GetIconInfo(hIcon, &ii)) return {};
    BITMAP bm{};
    GetObjectW(ii.hbmColor ? ii.hbmColor : ii.hbmMask, sizeof(bm), &bm);
    if (ii.hbmColor) DeleteObject(ii.hbmColor);
    if (ii.hbmMask)  DeleteObject(ii.hbmMask);
    int srcW = bm.bmWidth  > 0 ? bm.bmWidth  : iconSize;
    int srcH = bm.bmHeight > 0 ? bm.bmHeight : iconSize;
    HDC screenDC = GetDC(nullptr);
    HDC hdc      = CreateCompatibleDC(screenDC);
    HBITMAP hBmp = CreateCompatibleBitmap(screenDC, srcW, srcH);
    ReleaseDC(nullptr, screenDC);
    HBITMAP hOld = (HBITMAP)SelectObject(hdc, hBmp);
    RECT rc{ 0, 0, srcW, srcH };
    HBRUSH hBr = (HBRUSH)GetStockObject(BLACK_BRUSH);
    FillRect(hdc, &rc, hBr);
    DrawIconEx(hdc, 0, 0, hIcon, srcW, srcH, 0, nullptr, DI_NORMAL);
    BITMAPINFO bi{};
    bi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth       = srcW;
    bi.bmiHeader.biHeight      = -srcH;
    bi.bmiHeader.biPlanes      = 1;
    bi.bmiHeader.biBitCount    = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    std::vector<BYTE> src(srcW * srcH * 4, 0);
    GetDIBits(hdc, hBmp, 0, srcH, src.data(), &bi, DIB_RGB_COLORS);
    SelectObject(hdc, hOld);
    DeleteObject(hBmp);
    DeleteDC(hdc);
    for (int i = 0; i + 3 < (int)src.size(); i += 4)
        std::swap(src[i], src[i + 2]);
    if (srcW == iconSize && srcH == iconSize)
        return src;
    std::vector<BYTE> dst(iconSize * iconSize * 4, 0);
    float scaleX = (float)srcW / iconSize;
    float scaleY = (float)srcH / iconSize;
    for (int dy = 0; dy < iconSize; ++dy) {
        for (int dx = 0; dx < iconSize; ++dx) {
            float fx = (dx + 0.5f) * scaleX - 0.5f;
            float fy = (dy + 0.5f) * scaleY - 0.5f;
            int x0 = (int)fx; int y0 = (int)fy;
            int x1 = x0 + 1;  int y1 = y0 + 1;
            x0 = x0 < 0 ? 0 : (x0 > srcW - 1 ? srcW - 1 : x0);
            y0 = y0 < 0 ? 0 : (y0 > srcH - 1 ? srcH - 1 : y0);
            x1 = x1 < 0 ? 0 : (x1 > srcW - 1 ? srcW - 1 : x1);
            y1 = y1 < 0 ? 0 : (y1 > srcH - 1 ? srcH - 1 : y1);
            float wx = fx - (int)fx; float wy = fy - (int)fy;
            int di = (dy * iconSize + dx) * 4;
            for (int c = 0; c < 4; ++c) {
                float v = src[(y0 * srcW + x0) * 4 + c] * (1-wx)*(1-wy)
                        + src[(y0 * srcW + x1) * 4 + c] * wx    *(1-wy)
                        + src[(y1 * srcW + x0) * 4 + c] * (1-wx)* wy
                        + src[(y1 * srcW + x1) * 4 + c] * wx    * wy;
                dst[di + c] = (BYTE)(v + 0.5f);
            }
        }
    }
    return dst;
}
static std::vector<BYTE> FetchAppIconBytes(const std::wstring& appUserModelId, int iconSize) {
    std::vector<BYTE> result;
    if (appUserModelId.empty()) return result;
    auto Render = [&](HICON h, bool own) -> bool {
        if (!h) return false;
        result = RenderIconToBytes(h, iconSize);
        if (own) DestroyIcon(h);
        return !result.empty();
    };
    {
        std::wstring shellPath = L"shell:AppsFolder\\" + appUserModelId;
        PIDLIST_ABSOLUTE pidl = nullptr;
        if (SUCCEEDED(SHParseDisplayName(shellPath.c_str(), nullptr, &pidl, 0, nullptr)) && pidl) {
            SHFILEINFOW sfi{};
            DWORD flags = SHGFI_PIDL | SHGFI_ICON | SHGFI_LARGEICON;
            if (SHGetFileInfoW(reinterpret_cast<LPCWSTR>(pidl), 0, &sfi, sizeof(sfi), flags) && sfi.hIcon) {
                CoTaskMemFree(pidl);
                if (Render(sfi.hIcon, true)) return result;
            } else {
                CoTaskMemFree(pidl);
            }
        }
    }
    {
        struct EnumCtx {
            const std::wstring* aumid;
            HICON  exactIcon = nullptr;
            HICON  fuzzyIcon = nullptr;
            DWORD  exactPid  = 0;
            DWORD  fuzzyPid  = 0;
            std::wstring exactPath;
            std::wstring fuzzyPath;
        };
        EnumCtx ctx{ &appUserModelId };
        EnumWindows([](HWND hWnd, LPARAM lParam) CALLBACK -> BOOL {
            if (!IsWindowVisible(hWnd)) return TRUE;
            auto* c = reinterpret_cast<EnumCtx*>(lParam);
            if (!c->exactIcon) {
                IPropertyStore* pps = nullptr;
                if (SUCCEEDED(SHGetPropertyStoreForWindow(hWnd, IID_PPV_ARGS(&pps)))) {
                    PROPVARIANT var;
                    PropVariantInit(&var);
                    if (SUCCEEDED(pps->GetValue(PKEY_AppUserModel_ID, &var)) && var.vt == VT_LPWSTR) {
                        std::wstring winAumid  = ToLowerCopy(std::wstring(var.pwszVal));
                        std::wstring wantAumid = ToLowerCopy(*c->aumid);
                        if (winAumid == wantAumid) {
                            auto getIconTimeout = [&](HWND w, WPARAM iconType) -> HICON {
                                DWORD_PTR res = 0;
                                if (SendMessageTimeoutW(w, WM_GETICON, iconType, 0,
                                        SMTO_ABORTIFHUNG | SMTO_BLOCK, 100, &res)) {
                                    return (HICON)res;
                                }
                                return nullptr;
                            };
                            HICON icon = getIconTimeout(hWnd, ICON_BIG);
                            if (!icon) icon = getIconTimeout(hWnd, ICON_SMALL);
                            if (!icon) icon = (HICON)GetClassLongPtrW(hWnd, GCLP_HICON);
                            if (!icon) icon = (HICON)GetClassLongPtrW(hWnd, GCLP_HICONSM);
                            if (icon) {
                                c->exactIcon = icon;
                                GetWindowThreadProcessId(hWnd, &c->exactPid);
                                wchar_t path[MAX_PATH]{};
                                HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, c->exactPid);
                                if (hProc) { DWORD sz = MAX_PATH; QueryFullProcessImageNameW(hProc, 0, path, &sz); CloseHandle(hProc); }
                                c->exactPath = path;
                                PropVariantClear(&var);
                                pps->Release();
                                return FALSE;
                            }
                        }
                    }
                    PropVariantClear(&var);
                    pps->Release();
                }
            }
            if (!c->exactIcon && !c->fuzzyIcon) {
                std::wstring windowAumid = GetWindowAppUserModelId(hWnd);
                if (windowAumid.empty()) {
                    DWORD pid = 0;
                    std::wstring procPath;
                    if (AppIdMatchesProcess(*c->aumid, hWnd, &pid, &procPath)) {
                        auto getIconTimeout = [&](HWND w, WPARAM iconType) -> HICON {
                            DWORD_PTR res = 0;
                            if (SendMessageTimeoutW(w, WM_GETICON, iconType, 0,
                                    SMTO_ABORTIFHUNG | SMTO_BLOCK, 100, &res)) {
                                return (HICON)res;
                            }
                            return nullptr;
                        };
                        HICON icon = getIconTimeout(hWnd, ICON_BIG);
                        if (!icon) icon = getIconTimeout(hWnd, ICON_SMALL);
                        if (!icon) icon = (HICON)GetClassLongPtrW(hWnd, GCLP_HICON);
                        if (!icon) icon = (HICON)GetClassLongPtrW(hWnd, GCLP_HICONSM);
                        if (icon) {
                            c->fuzzyIcon = icon;
                            c->fuzzyPid  = pid;
                            c->fuzzyPath = procPath;
                        } else if (!c->fuzzyPid) {
                            c->fuzzyPid  = pid;
                            c->fuzzyPath = procPath;
                        }
                    }
                }
            }
            return TRUE;
        }, reinterpret_cast<LPARAM>(&ctx));
        if (ctx.exactIcon && Render(ctx.exactIcon, false)) return result;
        if (ctx.fuzzyIcon) {
            HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, ctx.fuzzyPid);
            if (hProc) {
                DWORD exitCode = 0;
                if (GetExitCodeProcess(hProc, &exitCode) && exitCode == STILL_ACTIVE) {
                    CloseHandle(hProc);
                    if (Render(ctx.fuzzyIcon, false)) return result;
                } else {
                    CloseHandle(hProc);
                }
            }
        }
        auto resolvePid = [](DWORD pid) -> std::wstring {
            if (!pid) return {};
            wchar_t path[MAX_PATH]{};
            HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
            if (hProc) { DWORD sz = MAX_PATH; QueryFullProcessImageNameW(hProc, 0, path, &sz); CloseHandle(hProc); }
            return path;
        };
        auto tryExePath = [&](const std::wstring& path) -> bool {
            if (path.empty()) return false;
            SHFILEINFOW sfi{};
            if (SHGetFileInfoW(path.c_str(), 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_LARGEICON) && sfi.hIcon)
                return Render(sfi.hIcon, true);
            if (SHGetFileInfoW(path.c_str(), 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_SMALLICON) && sfi.hIcon)
                return Render(sfi.hIcon, true);
            return false;
        };
        auto tryExtractIconEx = [&](const std::wstring& path) -> bool {
            if (path.empty()) return false;
            HICON hL = nullptr, hS = nullptr;
            if (ExtractIconExW(path.c_str(), 0, &hL, &hS, 1)) {
                HICON chosen = hL ? hL : hS;
                if (chosen) {
                    bool ok = Render(chosen, false);
                    if (hL) DestroyIcon(hL);
                    if (hS) DestroyIcon(hS);
                    if (ok) return true;
                }
            }
            return false;
        };
        std::wstring ep = ctx.exactPath.empty() ? resolvePid(ctx.exactPid) : ctx.exactPath;
        std::wstring fp = ctx.fuzzyPath.empty() ? resolvePid(ctx.fuzzyPid) : ctx.fuzzyPath;
        if (tryExePath(ep))        return result;
        if (tryExePath(fp))        return result;
        if (tryExtractIconEx(ep))  return result;
        if (tryExtractIconEx(fp))  return result;
    }
    if (appUserModelId.find(L".exe") != std::wstring::npos) {
        std::wstring exePath = appUserModelId;
        if (exePath.size() >= 2 && exePath.front() == L'"' && exePath.back() == L'"')
            exePath = exePath.substr(1, exePath.size() - 2);
        SHFILEINFOW sfi{};
        if (SHGetFileInfoW(exePath.c_str(), 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_LARGEICON) && sfi.hIcon)
            if (Render(sfi.hIcon, true)) return result;
        HICON hL = nullptr, hS = nullptr;
        if (ExtractIconExW(exePath.c_str(), 0, &hL, &hS, 1)) {
            HICON chosen = hL ? hL : hS;
            if (chosen) {
                Render(chosen, false);
                if (hL) DestroyIcon(hL);
                if (hS) DestroyIcon(hS);
                if (!result.empty()) return result;
            }
        }
    }
    return result;
}
static void FetchMediaPropertiesAsync() {
    SpawnTrackedWorker([]() {
        if (g_unloading) return;
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
        try {
            GlobalSystemMediaTransportControlsSession session{nullptr};
            std::wstring aumid;
            {
                std::lock_guard<std::mutex> lk(g_sessionMtx);
                session = g_currentSession;
            }
            if (!session) {
                winrt::uninit_apartment();
                return;
            }
            try {
                aumid = std::wstring(session.SourceAppUserModelId());
            } catch (...) {
                winrt::uninit_apartment();
                return;
            }
            try {
                auto props = session.TryGetMediaPropertiesAsync().get();
                if (!props) {
                    winrt::uninit_apartment();
                    return;
                }
                std::vector<BYTE> thumbBytes;
                uint64_t          thumbHash = 0;
                uint64_t          thumbStreamSize = 0;
                if (auto thumbRef = props.Thumbnail()) {
                    try {
                        auto stream = thumbRef.OpenReadAsync().get();
                        if (stream) {
                            UINT64 sz = stream.Size();
                            thumbStreamSize = sz;
                            if (sz > 0 && sz < 4 * 1024 * 1024) {
                                DataReader reader(stream);
                                reader.LoadAsync((UINT32)sz).get();
                                thumbBytes.resize((size_t)sz);
                                reader.ReadBytes(winrt::array_view<BYTE>(thumbBytes));
                                reader.DetachStream();
                                for (size_t i = 0; i < thumbBytes.size(); i += 1024)
                                    thumbHash = thumbHash * 31 + thumbBytes[i];
                            }
                        }
                    } catch (...) { thumbBytes.clear(); thumbStreamSize = 0; }
                }

                {
                    bool isBrowserSession = IsBrowserAumid(aumid);
                    std::wstring titleArtistKey =
                        std::wstring(props.Title()) + L"\x1f" + std::wstring(props.Artist());
                    bool suspectMatch = false;
                    {
                        std::lock_guard<std::mutex> lk(g_mediaMtx);
                        bool     trackChanged = (titleArtistKey != g_lastTitleArtistKey);
                        uint64_t prevArtSize  = g_media.thumbnailStreamSize;
                        uint64_t prevArtHash  = g_media.thumbnailHash;
                        g_lastTitleArtistKey = titleArtistKey;

                        if (g_artNewBrowserSession) {
                            if (thumbStreamSize > 0) {
                                g_suspectArtSize  = thumbStreamSize;
                                g_suspectArtHash  = thumbHash;
                                g_artDelayPending = true;
                                suspectMatch      = true;
                            }
                            g_artNewBrowserSession = false;
                        } else if (trackChanged) {
                            g_suspectArtSize  = isBrowserSession ? prevArtSize : 0;
                            g_suspectArtHash  = isBrowserSession ? prevArtHash : 0;
                            g_artDelayPending = isBrowserSession && prevArtSize > 0;
                        }

                        if (!suspectMatch && g_artDelayPending && isBrowserSession) {
                            bool matchesSuspect = thumbStreamSize > 0 &&
                                                  thumbStreamSize == g_suspectArtSize &&
                                                  (g_suspectArtHash == 0 || thumbHash == g_suspectArtHash);
                            if (matchesSuspect) {
                                suspectMatch = true;
                            } else {
                                g_artDelayPending = false;
                            }
                        }

                        if (!suspectMatch && isBrowserSession &&
                            thumbStreamSize == 0 && prevArtSize > 0) {
                            suspectMatch = true;
                        }
                    }
                    if (suspectMatch) {
                        thumbBytes.clear();
                        thumbHash = 0;
                        thumbStreamSize = 0;
                    }
                }
                std::vector<BYTE> appIconBytes;
                std::wstring      appIconKey;
                bool forceIconRefresh = false;
                {
                    std::lock_guard<std::mutex> lk(g_mediaMtx);
                    appIconKey = g_media.appIconKey;
                    appIconBytes = g_media.appIconBytes;
                }
                {
                    std::lock_guard<std::mutex> lk(g_sessionMtx);
                    forceIconRefresh = g_userSwitchedSession;
                }
                if (g_settings.showAppIcon && (aumid != appIconKey || appIconBytes.empty() || forceIconRefresh || g_cachedAppIconSize != g_settings.appIconSize)) {
                    try {
                        appIconBytes = FetchAppIconBytes(aumid, g_settings.appIconSize);
                        appIconKey   = aumid;
                        g_cachedAppIconSize = g_settings.appIconSize;
                    } catch (...) {
                    }
                }
                {
                    std::lock_guard<std::mutex> lk(g_mediaMtx);
                    try {
                        g_media.title          = std::wstring(props.Title());
                        g_media.artist         = std::wstring(props.Artist());
                        g_media.hasMedia       = !g_media.title.empty() || !g_media.artist.empty();
                        g_media.thumbnailBytes = std::move(thumbBytes);
                        g_media.thumbnailHash  = thumbHash;
                        g_media.thumbnailStreamSize = thumbStreamSize;
                        g_media.appUserModelId = aumid;
                        if (g_settings.showAppIcon) {
                            g_media.appIconBytes   = std::move(appIconBytes);
                            g_media.appIconKey     = appIconKey;
                        }
                    } catch (...) {
                    }
                }
                if (forceIconRefresh) {
                    std::lock_guard<std::mutex> lk(g_sessionMtx);
                    g_userSwitchedSession = false;
                }
            } catch (...) {
            }
        } catch (...) {}
        DispatchMediaUpdate();
        winrt::uninit_apartment();
    });
}
static void FetchPlaybackInfoAsync() {
    SpawnTrackedWorker([]() {
        if (g_unloading) return;
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
        try {
            GlobalSystemMediaTransportControlsSession session{nullptr};
            { std::lock_guard<std::mutex> lk(g_sessionMtx); session = g_currentSession; }
            if (session) {
                try {
                    auto info = session.GetPlaybackInfo();
                    if (!info) {
                        winrt::uninit_apartment();
                        return;
                    }
                    auto status = info.PlaybackStatus();
                    bool playing = (status == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing);
                    bool wasPlaying = false;
                    {
                        std::lock_guard<std::mutex> lk(g_mediaMtx);
                        wasPlaying = g_media.isPlaying;
                        g_media.isPlaying = playing;
                        g_media.isStopped = status == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Stopped ||
                            status == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Closed;
                    }
                    if (playing != wasPlaying) {
                        if (!playing && wasPlaying) {
                            if (!g_unloading) OnSessionsChanged();
                        }
                    }
                    try {
                        auto shuffleRef = info.IsShuffleActive();
                        if (shuffleRef) {
                            g_shuffleEnabled = shuffleRef.Value();
                        }
                    } catch (...) {}
                    try {
                        auto repeatRef = info.AutoRepeatMode();
                        if (repeatRef) {
                            using RM = winrt::Windows::Media::MediaPlaybackAutoRepeatMode;
                            auto v = repeatRef.Value();
                            if (v == RM::Track) g_repeatMode = RepeatMode::One;
                            else if (v == RM::List) g_repeatMode = RepeatMode::All;
                            else g_repeatMode = RepeatMode::Off;
                        } else {
                            g_repeatMode = RepeatMode::Off;
                        }
                    } catch (...) {
                        g_repeatMode = RepeatMode::Off;
                    }
                    try {
                        auto controls = info.Controls();
                        if (controls) {
                            bool canPrev   = controls.IsPreviousEnabled();
                            bool canNext   = controls.IsNextEnabled();
                            bool canShuf   = controls.IsShuffleEnabled();
                            bool canRep    = controls.IsRepeatEnabled();
                            bool canSeek   = controls.IsPlaybackPositionEnabled();
                            {
                                std::lock_guard<std::mutex> lk(g_mediaMtx);
                                g_media.canSkipPrevious = canPrev;
                                g_media.canSkipNext     = canNext;
                                g_media.canShuffle      = canShuf;
                                g_media.canRepeat       = canRep;
                                g_media.canSeek         = canSeek;
                            }
                        }
                    } catch (...) {}
                } catch (...) {
                }
            }
        } catch (...) {}
        DispatchMediaUpdate();
        winrt::uninit_apartment();
    });
}
static void DetachCurrentSession() {
    std::lock_guard<std::mutex> lk(g_sessionMtx);
    if (!g_currentSession) return;
    try {
        if (g_evMediaProps.value) { g_currentSession.MediaPropertiesChanged(g_evMediaProps); g_evMediaProps = {}; }
        if (g_evPlayback.value)   { g_currentSession.PlaybackInfoChanged(g_evPlayback); g_evPlayback = {}; }
    } catch (...) {}
    g_currentSession = nullptr;
    g_repeatMode = RepeatMode::Off;
    g_shuffleEnabled = false;
    {
        std::lock_guard<std::mutex> lkm(g_mediaMtx);
        g_media.canSkipPrevious = true;
        g_media.canSkipNext     = true;
        g_media.canShuffle      = true;
        g_media.canRepeat       = true;
        g_media.canSeek         = true;
    }
}
static GlobalSystemMediaTransportControlsSession PickBestSession() {
    GlobalSystemMediaTransportControlsSessionManager mgr{nullptr};
    {
        std::lock_guard<std::mutex> lkMgr(g_sessionMtx);
        mgr = g_sessionMgr;
    }
    if (!mgr) return nullptr;
    try {
        auto sessions = mgr.GetSessions();
        int sessionCount = (int)sessions.Size();
        if (sessionCount == 0) {
            return nullptr;
        }
        using S = GlobalSystemMediaTransportControlsSessionPlaybackStatus;
        GlobalSystemMediaTransportControlsSession current{nullptr};
        bool userSwitched = false;
        {
            std::lock_guard<std::mutex> lk(g_sessionMtx);
            current      = g_currentSession;
            userSwitched = g_userSwitchedSession;
        }
        GlobalSystemMediaTransportControlsSession playingFirst{nullptr};
        GlobalSystemMediaTransportControlsSession firstValid{nullptr};
        bool currentExists  = false;
        bool currentPlaying = false;
        for (auto const& s : sessions) {
            try {
                if (!s) continue;
                std::wstring appId = s.SourceAppUserModelId().c_str();
                if (IsIgnoredMediaApp(appId)) continue;
                auto pb = s.GetPlaybackInfo();
                if (!pb) continue;
                auto status = pb.PlaybackStatus();
                bool isPlaying = (status == S::Playing);
                if (!firstValid) firstValid = s;
                if (s == current) {
                    currentExists  = true;
                    currentPlaying = isPlaying;
                }
                if (isPlaying && !playingFirst) {
                    playingFirst = s;
                }
            } catch (...) {}
        }
        if (userSwitched) {
            if (currentExists) {
                return current;
            }
            { std::lock_guard<std::mutex> lk(g_sessionMtx); g_userSwitchedSession = false; }
        }
        if (!g_settings.autoSwitchSession) {
            if (currentExists) {
                return current;
            }
            return firstValid;
        }
        if (currentExists && currentPlaying) {
            return current;
        }
        if (playingFirst && playingFirst != current) {
            return playingFirst;
        }
        if (currentExists) {
            return current;
        }
        return firstValid;
    } catch (...) {
        Wh_Log(L"PickBestSession: Exception occurred");
        return nullptr;
    }
}
static void AttachToSession(GlobalSystemMediaTransportControlsSession session) {
    if (!session) {
        DetachCurrentSession();
        {
            std::lock_guard<std::mutex> lk(g_mediaMtx);
            g_media = MediaState{};
            g_lastTitleArtistKey.clear();
            g_suspectArtSize  = 0;
            g_suspectArtHash  = 0;
            g_artDelayPending = false;
            g_artNewBrowserSession = false;
        }
        DispatchMediaUpdate();
        return;
    }
    bool needsReattach = false;
    {
        std::lock_guard<std::mutex> lk(g_sessionMtx);
        if (g_currentSession == session) {
            if (!g_evMediaProps.value || !g_evPlayback.value) {
                needsReattach = true;
            } else {
                goto fetch;
            }
        }
    }
    (void)needsReattach;
    {
        std::wstring appId;
        try {
            appId = std::wstring(session.SourceAppUserModelId());
        } catch (...) {
        }
        DetachCurrentSession();
        {
            std::lock_guard<std::mutex> lk(g_mediaMtx);
            g_media.appIconKey   = L"";
            g_media.appIconBytes.clear();
            g_media.thumbnailBytes.clear();
            g_media.thumbnailHash = 0;
            g_media.thumbnailStreamSize = 0;
            g_lastTitleArtistKey.clear();
            g_suspectArtSize  = 0;
            g_suspectArtHash  = 0;
            g_artDelayPending = false;
            g_artNewBrowserSession = IsBrowserAumid(appId);
        }
    }
    g_cachedAppIconSize = -1;
    ResetScrollState(g_titleScroll);
    ResetScrollState(g_artistScroll);
    {
        std::lock_guard<std::mutex> lk(g_sessionMtx);
        g_currentSession = session;
        try {
            g_evMediaProps = g_currentSession.MediaPropertiesChanged([](auto const&, auto const&) {
                if (!g_unloading) FetchMediaPropertiesAsync();
            });
            g_evPlayback = g_currentSession.PlaybackInfoChanged([](auto const&, auto const&) {
                if (!g_unloading) FetchPlaybackInfoAsync();
            });
        } catch (...) {
            Wh_Log(L"AttachToSession: Failed to attach event handlers");
            g_currentSession = nullptr;
            return;
        }
    }
fetch:
    FetchMediaPropertiesAsync();
    FetchPlaybackInfoAsync();
}
static void OnSessionsChanged() {
    if (g_unloading) return;
    bool forceRefresh = g_forceSessionRefresh.exchange(false);
    try {
        GlobalSystemMediaTransportControlsSessionManager mgr{nullptr};
        {
            std::lock_guard<std::mutex> lk(g_sessionMtx);
            mgr = g_sessionMgr;
        }
        if (mgr) {
            auto sessions = mgr.GetSessions();
            g_sessionCount.store((int)sessions.Size());
        }
    } catch (...) {}
    if (forceRefresh) {
        std::lock_guard<std::mutex> lk(g_sessionMtx);
        g_userSwitchedSession = false;
    }
    try {
        auto newSession = PickBestSession();
        AttachToSession(newSession);
    } catch (...) {
        Wh_Log(L"OnSessionsChanged: Exception occurred");
    }
}
static DWORD WINAPI MediaThreadProc(void*) {
    try {
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
        auto op = GlobalSystemMediaTransportControlsSessionManager::RequestAsync();
        while (op.Status() == winrt::Windows::Foundation::AsyncStatus::Started) {
            if (WaitForSingleObject(g_mediaStopEvent, 50) == WAIT_OBJECT_0) goto done;
        }
        {
            std::lock_guard<std::mutex> lk(g_sessionMtx);
            g_sessionMgr = op.GetResults();
        }
        g_evSessionsChanged = g_sessionMgr.SessionsChanged([](auto const&, auto const&) {
            OnSessionsChanged();
        });
        g_evCurrentChanged  = g_sessionMgr.CurrentSessionChanged([](auto const&, auto const&) {
            OnSessionsChanged();
        });
        OnSessionsChanged();
        if (WaitForSingleObject(g_mediaStopEvent, 2000) == WAIT_TIMEOUT) {
            if (!g_unloading) {
                g_forceSessionRefresh = true;
                OnSessionsChanged();
            }
        }
        WaitForSingleObject(g_mediaStopEvent, INFINITE);
        try { if (g_evSessionsChanged.value) g_sessionMgr.SessionsChanged(g_evSessionsChanged); } catch (...) { Wh_Log(L"MediaThreadProc: Failed to unregister SessionsChanged event"); }
        try { if (g_evCurrentChanged.value)  g_sessionMgr.CurrentSessionChanged(g_evCurrentChanged); } catch (...) { Wh_Log(L"MediaThreadProc: Failed to unregister CurrentSessionChanged event"); }
        DetachCurrentSession();
        {
            std::lock_guard<std::mutex> lk(g_sessionMtx);
            g_sessionMgr = nullptr;
        }
    done:
        winrt::uninit_apartment();
    } catch (...) {
        Wh_Log(L"MediaThreadProc: Exception in media thread");
    }
    return 0;
}
static void StartMediaThread() {
    if (g_mediaThread) return;
    g_mediaStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_mediaStopEvent) return;
    g_mediaThread = CreateThread(nullptr, 0, MediaThreadProc, nullptr, 0, nullptr);
    if (!g_mediaThread) { CloseHandle(g_mediaStopEvent); g_mediaStopEvent = nullptr; }
}
static void StopMediaThread() {
    if (g_mediaStopEvent) SetEvent(g_mediaStopEvent);
    if (g_mediaThread) { WaitForSingleObject(g_mediaThread, 5000); CloseHandle(g_mediaThread); g_mediaThread = nullptr; }
    if (g_mediaStopEvent) { CloseHandle(g_mediaStopEvent); g_mediaStopEvent = nullptr; }
}
static HANDLE g_timerThread    = nullptr;
static HANDLE g_timerStopEvent = nullptr;
static HANDLE g_timerUpdateEvent = nullptr;
[[clang::no_destroy]] static winrt::Windows::UI::Xaml::DispatcherTimer g_scrollDispatcherTimer{nullptr};
static winrt::event_token                        g_scrollDispatcherTimerToken{};
static bool                                       g_scrollDispatcherTimerHasToken = false;
static void TickScrollState(TextScrollState& s, int stepPx, int pauseMs, const std::wstring& mode) {
    if (!s.active) return;
    if (s.pausing) {
        s.pauseTick -= s.tickMs;
        if (s.pauseTick <= 0) {
            s.pausing = false;
            s.pauseTick = 0;
        }
        return;
    }
    double maxOff = s.textWidth - s.viewWidth + 10.0;
    if (maxOff < 0.0) maxOff = 0.0;
    if (mode == L"loop") {
        s.offset += stepPx;
        if (s.offset >= s.textWidth + g_settings.loopGap) {
            s.offset = 0.0;
        }
    } else {
        if (s.forward) {
            s.offset += stepPx;
            if (s.offset >= maxOff) {
                s.offset = maxOff;
                s.forward = false;
                s.pausing = true;
                s.pauseTick = pauseMs;
            }
        } else {
            s.offset -= stepPx;
            if (s.offset <= 0.0) {
                s.offset = 0.0;
                s.forward = true;
                s.pausing = true;
                s.pauseTick = pauseMs;
            }
        }
    }
}
static void UpdateScrollTransforms();
static void ScrollTimerTick(winrt::Windows::Foundation::IInspectable const&,
                            winrt::Windows::Foundation::IInspectable const&) {
    if (g_unloading || g_applyingSettings) return;
    bool needsScroll = (g_titleScroll.active || g_artistScroll.active);
    if (!needsScroll) {
        if (g_scrollDispatcherTimer) {
            try { g_scrollDispatcherTimer.Stop(); } catch (...) {}
        }
        return;
    }
    int stepPx = std::max(1, g_settings.scrollSpeed);
    int pauseMs = g_settings.scrollPauseDuration;
    TickScrollState(g_titleScroll, stepPx, pauseMs, g_settings.scrollMode);
    TickScrollState(g_artistScroll, stepPx, pauseMs, g_settings.scrollMode);
    UpdateScrollTransforms();
}
static void StartScrollTimer() {
    HWND hWnd = g_taskbarWnd;
    if (!hWnd || !IsWindow(hWnd)) return;
    RunFromWindowThread(hWnd, [](void*) {
        try {
            if (!g_scrollDispatcherTimer) {
                g_scrollDispatcherTimer = winrt::Windows::UI::Xaml::DispatcherTimer();
                g_scrollDispatcherTimer.Interval(
                    winrt::Windows::Foundation::TimeSpan{std::chrono::milliseconds(16)});
                g_scrollDispatcherTimerToken = g_scrollDispatcherTimer.Tick(&ScrollTimerTick);
                g_scrollDispatcherTimerHasToken = true;
            }
            g_scrollDispatcherTimer.Start();
        } catch (...) {}
    }, nullptr);
}
static void StopScrollTimer() {
    HWND hWnd = g_taskbarWnd;
    auto stop = [](void*) {
        try {
            if (g_scrollDispatcherTimer) {
                g_scrollDispatcherTimer.Stop();
                if (g_unloading) {
                    if (g_scrollDispatcherTimerHasToken) {
                        g_scrollDispatcherTimer.Tick(g_scrollDispatcherTimerToken);
                        g_scrollDispatcherTimerHasToken = false;
                    }
                    g_scrollDispatcherTimer = nullptr;
                }
            }
        } catch (...) {}
    };
    if (hWnd && IsWindow(hWnd)) {
        RunFromWindowThread(hWnd, stop, nullptr);
    } else {
        stop(nullptr);
    }
}
static void ResetScrollState(TextScrollState& s) {
    s.offset    = 0.0;
    s.textWidth = 0.0;
    s.viewWidth = 0.0;
    s.forward   = true;
    s.active    = false;
    if (g_settings.scrollMode == L"loop") {
        s.pausing  = false;
        s.pauseTick = 0;
    } else {
        s.pausing  = true;
        s.pauseTick = g_settings.scrollPauseDuration;
    }
}
static constexpr wchar_t kTitleScrollViewName[]  = L"FluentMedia_TitleScrollView";
static constexpr wchar_t kArtistScrollViewName[] = L"FluentMedia_ArtistScrollView";
static constexpr wchar_t kTitleCloneName[]       = L"FluentMedia_TitleClone";
static constexpr wchar_t kArtistCloneName[]      = L"FluentMedia_ArtistClone";
static constexpr wchar_t kPanelGridName[]        = L"FluentMedia_PanelGrid";
static double GetAvailableScrollTextAreaWidth() {
    try {
        if (g_settings.playerMaxWidth <= 0) return 0.0;
        if (!g_playerGrid) return 0.0;
        auto panelFe = FindChildByName(g_playerGrid, kPanelGridName);
        if (!panelFe) return 0.0;
        auto panelGrid = panelFe.try_as<Grid>();
        if (!panelGrid) return 0.0;
        double total = panelGrid.ActualWidth();
        if (total <= 0.0) return 0.0;
        auto cols = panelGrid.ColumnDefinitions();
        double used = 0.0;
        for (uint32_t i = 0; i < cols.Size(); i++) {
            if (i == 1) continue;
            used += cols.GetAt(i).ActualWidth();
        }
        double leftMargin  = (double)g_settings.textAreaLeftMargin;
        double rightMargin = (double)g_settings.textAreaRightMargin;
        double available = total - used - leftMargin - rightMargin;
        if (available < 0.0) available = 0.0;
        return available;
    } catch (...) {
        return 0.0;
    }
}
static void UpdateScrollTransforms() {
    if (!g_playerGrid || (!g_settings.enableTitleScrolling && !g_settings.enableArtistScrolling)) return;
    bool isLoop = (g_settings.scrollMode == L"loop");
    if (g_settings.enableTitleScrolling) {
        try {
            if (auto fe = FindChildByName(g_playerGrid, kTitleScrollViewName)) {
                if (auto cv = fe.try_as<Canvas>()) {
                    int n = VisualTreeHelper::GetChildrenCount(cv);
                    for (int i = 0; i < n; i++) {
                        auto child = VisualTreeHelper::GetChild(cv, i);
                        if (auto tb = child.try_as<TextBlock>()) {
                            auto name = tb.Name();
                            if (name == kTitleBlockName) {
                                Canvas::SetLeft(tb, -g_titleScroll.offset);
                            } else if (isLoop && name == kTitleCloneName) {
                                double gap = g_titleScroll.textWidth + g_settings.loopGap;
                                Canvas::SetLeft(tb, gap - g_titleScroll.offset);
                            }
                        }
                    }
                }
            }
        } catch (...) {}
    }
    if (g_settings.enableArtistScrolling) {
        try {
            if (auto fe = FindChildByName(g_playerGrid, kArtistScrollViewName)) {
                if (auto cv = fe.try_as<Canvas>()) {
                    int n = VisualTreeHelper::GetChildrenCount(cv);
                    for (int i = 0; i < n; i++) {
                        auto child = VisualTreeHelper::GetChild(cv, i);
                        if (auto ab = child.try_as<TextBlock>()) {
                            auto name = ab.Name();
                            if (name == kArtistBlockName) {
                                Canvas::SetLeft(ab, -g_artistScroll.offset);
                            } else if (isLoop && name == kArtistCloneName) {
                                double gap = g_artistScroll.textWidth + g_settings.loopGap;
                                Canvas::SetLeft(ab, gap - g_artistScroll.offset);
                            }
                        }
                    }
                }
            }
        } catch (...) {}
    }
}
static void DispatchMediaUpdate() {
    bool unloading = g_unloading;
    bool applyingSettings = g_applyingSettings;
    if (unloading || applyingSettings) {
        return;
    }
    g_needsUiUpdate = true;
    if (g_timerUpdateEvent) {
        SetEvent(g_timerUpdateEvent);
    }

    if (g_miniPlayerFlyoutOpen && g_taskbarWnd) {
        if (!g_settings.hideMediaSessionsList)
            FetchMiniSessionInfosAsync(g_taskbarWnd);
        HWND tw = g_taskbarWnd;
        RunFromWindowThread(tw, [](void*) {
            if (g_miniPlayerFlyoutOpen) RefreshMiniPlayerFlyoutUI();
        }, nullptr);
    }
}
static void RefreshPlayerContents();
static void UpdateVisibility();
static void RefreshThemeColors();
static void RemovePlayerGrid();
static bool InjectPlayerGrid();
static void UpdateProgressAndTime();
static std::atomic<bool> g_themeChangePending{false};
// Track timeline for the progress bar and time display (1.9.0). Values in ms,
// guarded by g_mediaMtx. Apps report the position only now and then, so while
// playing the position is carried forward from the session's LastUpdatedTime.
// Idea from Taskbar Media Widget by uMk0 (MIT); the code uses this mod's GSMTC
// session.
struct TimelineState {
    int64_t startMs = 0;
    int64_t endMs   = 0;
    int64_t posMs   = 0;
    bool    valid   = false;
};
static TimelineState g_timeline;
static bool ProgressOrTimeEnabled() {
    return g_settings.showProgressBar || g_settings.timeDisplayMode != 0;
}
static void PollTimeline() {
    GlobalSystemMediaTransportControlsSession session{nullptr};
    { std::lock_guard<std::mutex> lk(g_sessionMtx); session = g_currentSession; }
    TimelineState t;
    if (session) {
        try {
            auto tl = session.GetTimelineProperties();
            int64_t start = tl.StartTime().count() / 10000;
            int64_t end   = tl.EndTime().count() / 10000;
            int64_t pos   = tl.Position().count() / 10000;
            bool playing = false;
            { std::lock_guard<std::mutex> lk(g_mediaMtx); playing = g_media.isPlaying; }
            if (playing) {
                auto ago = std::chrono::duration_cast<std::chrono::milliseconds>(
                    winrt::clock::now() - tl.LastUpdatedTime()).count();
                if (ago > 0 && ago < 6LL * 3600 * 1000) pos += ago;
            }
            if (end > start) {
                t.valid   = true;
                t.startMs = start;
                t.endMs   = end;
                t.posMs   = std::clamp(pos, start, end);
            }
        } catch (...) {}
    }
    std::lock_guard<std::mutex> lk(g_mediaMtx);
    g_timeline = t;
}
static DWORD WINAPI TimerThreadProc(void*) {
    static bool lastThemeWasLight = IsSystemLightTheme();
    bool comReady = SUCCEEDED(CoInitializeEx(nullptr, COINIT_MULTITHREADED));
    HKEY hKey = nullptr;
    HANDLE hEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, KEY_NOTIFY, &hKey) == ERROR_SUCCESS) {
        RegNotifyChangeKeyValue(hKey, FALSE, REG_NOTIFY_CHANGE_LAST_SET, hEvent, TRUE);
    }
    while (!g_unloading) {
        HANDLE handles[] = {g_timerStopEvent, hEvent, g_timerUpdateEvent};
        DWORD wait = WaitForMultipleObjects(3, handles, FALSE, 500);
        if (wait == WAIT_OBJECT_0) break;
        if (g_applyingSettings) continue;
        HWND hWnd = g_taskbarWnd;
        if (!hWnd || !IsWindow(hWnd)) {
            hWnd = FindCurrentProcessTaskbarWnd();
            g_taskbarWnd = hWnd;
            if (!hWnd) continue;
        }
        if (wait == WAIT_OBJECT_0 + 1) {
            if (hKey) {
                RegNotifyChangeKeyValue(hKey, FALSE, REG_NOTIFY_CHANGE_LAST_SET, hEvent, TRUE);
            }
            {
                bool currentThemeIsLight = IsSystemLightTheme();
                if (currentThemeIsLight != lastThemeWasLight) {
                    lastThemeWasLight = currentThemeIsLight;
                    g_themeChangePending = true;
                    g_needsUiUpdate = true;
                    if (g_timerUpdateEvent) SetEvent(g_timerUpdateEvent);
                }
            }
        }
        if (g_themeChangePending.exchange(false)) {
            Sleep(150);
            if (!g_unloading && !g_applyingSettings) {
                RunFromWindowThread(hWnd, [](void*) {
                    if (!g_unloading && !g_applyingSettings && g_playerGrid) {
                        RefreshThemeColors();
                    }
                }, nullptr);
            }
        }
        bool needsUpdate = g_needsUiUpdate.exchange(false);
        if (g_settings.idleHideSeconds > 0) {
            bool playing = false;
            { std::lock_guard<std::mutex> lk(g_mediaMtx); playing = g_media.isPlaying; }
            if (playing) {
                g_idleSeconds = 0;
                g_idleTicks   = 0;
                if (g_hiddenByIdle) {
                    g_hiddenByIdle = false;
                    needsUpdate = true;
                }
            } else {
                ++g_idleTicks;
                if (g_idleTicks >= 2) {
                    g_idleTicks = 0;
                    ++g_idleSeconds;
                }
                if (!g_hiddenByIdle && g_idleSeconds >= g_settings.idleHideSeconds) {
                    g_hiddenByIdle = true;
                    needsUpdate = true;
                }
            }
        } else {
            if (g_hiddenByIdle) {
                g_hiddenByIdle = false;
                g_idleSeconds  = 0;
                g_idleTicks    = 0;
                needsUpdate    = true;
            }
        }
        if (comReady && ProgressOrTimeEnabled()) {
            PollTimeline();
            RunFromWindowThread(hWnd, [](void*) {
                if (!g_unloading && !g_applyingSettings) UpdateProgressAndTime();
            }, nullptr);
        }
        if (needsUpdate) {
            RunFromWindowThread(hWnd, [](void*) {
                if (g_unloading || g_applyingSettings) return;
                if (g_playerGrid) {
                    RefreshPlayerContents();
                    UpdateVisibility();
                }
            }, nullptr);
        }
    }
    if (hKey) RegCloseKey(hKey);
    if (hEvent) CloseHandle(hEvent);
    if (comReady) CoUninitialize();
    return 0;
}
static constexpr int VIZ_BARS_MAX = 96;
static constexpr int VIZ_FFT_SIZE = 1024;
static constexpr int VIZ_NUM_BANDS = 7;
static constexpr float VIZ_PI = 3.14159265f;
static std::atomic<float> g_VizBands[VIZ_NUM_BANDS] = {};
static std::atomic<bool> g_CaptureRunning{false};
static std::atomic<bool> g_vizCurrentlyVisible{false};
[[clang::no_destroy]] static std::optional<std::thread> g_CaptureThread;
static HANDLE g_hCaptureEvent = nullptr;
static std::atomic<bool> g_VizDeviceChanged{false};
static std::mutex g_captureThreadMtx;
class VizEndpointNotificationClient : public IMMNotificationClient {
public:
    virtual ~VizEndpointNotificationClient() = default;
    ULONG STDMETHODCALLTYPE AddRef() override {
        return InterlockedIncrement(&m_ref);
    }
    ULONG STDMETHODCALLTYPE Release() override {
        ULONG ref = InterlockedDecrement(&m_ref);
        if (ref == 0)
            delete this;
        return ref;
    }
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv) override {
        if (riid == __uuidof(IUnknown) || riid == __uuidof(IMMNotificationClient)) {
            *ppv = static_cast<IMMNotificationClient*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }
    HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow flow, ERole,
                                                    LPCWSTR) override {
        if (flow == eRender)
            g_VizDeviceChanged.store(true, std::memory_order_relaxed);
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR) override {
        g_VizDeviceChanged.store(true, std::memory_order_relaxed);
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR) override {
        g_VizDeviceChanged.store(true, std::memory_order_relaxed);
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR, DWORD) override {
        g_VizDeviceChanged.store(true, std::memory_order_relaxed);
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR,
                                                    const PROPERTYKEY) override {
        return S_OK;
    }
private:
    LONG m_ref = 1;
};
static float g_HannWindow[VIZ_FFT_SIZE] = {};
static float g_TwiddleRe[VIZ_FFT_SIZE / 2] = {};
static float g_TwiddleIm[VIZ_FFT_SIZE / 2] = {};
static int g_LogBinStart[VIZ_NUM_BANDS + 1] = {};
static void BuildHannWindow() {
    for (int i = 0; i < VIZ_FFT_SIZE; i++)
        g_HannWindow[i] = 0.5f * (1.f - cosf(2.f * VIZ_PI * i / (VIZ_FFT_SIZE - 1)));
}
static void BuildTwiddleFactors() {
    for (int i = 0; i < VIZ_FFT_SIZE / 2; i++) {
        float ang = -2.0f * VIZ_PI * i / VIZ_FFT_SIZE;
        g_TwiddleRe[i] = cosf(ang);
        g_TwiddleIm[i] = sinf(ang);
    }
}
static void BuildLogBins(UINT32 sampleRate) {
    static constexpr float FREQ_EDGES[VIZ_NUM_BANDS + 1] = {
        20.f, 120.f, 300.f, 800.f, 2500.f, 6000.f, 14000.f, 20000.f};
    for (int b = 0; b <= VIZ_NUM_BANDS; b++) {
        int bin = (int)(FREQ_EDGES[b] * VIZ_FFT_SIZE / (float)sampleRate);
        g_LogBinStart[b] = std::max(1, std::min(VIZ_FFT_SIZE / 2 - 1, bin));
    }
}
static void VizFFT(std::vector<float>& re, std::vector<float>& im) {
    int n = (int)re.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j) {
            std::swap(re[i], re[j]);
            std::swap(im[i], im[j]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        int halfLen = len / 2;
        int stride = n / len;
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < halfLen; j++) {
                float wRe = g_TwiddleRe[j * stride];
                float wIm = g_TwiddleIm[j * stride];
                float uRe = re[i + j], uIm = im[i + j];
                float vRe = re[i + j + halfLen] * wRe - im[i + j + halfLen] * wIm;
                float vIm = re[i + j + halfLen] * wIm + im[i + j + halfLen] * wRe;
                re[i + j] = uRe + vRe;
                im[i + j] = uIm + vIm;
                re[i + j + halfLen] = uRe - vRe;
                im[i + j + halfLen] = uIm - vIm;
            }
        }
    }
}
struct VizEQMul { float low, mid, high; };
static VizEQMul GetVizEQMultipliers(VizEQ eq) {
    switch (eq) {
    case VizEQ::Bass: return {2.0f, 0.6f, 0.4f};
    case VizEQ::Rock: return {1.3f, 1.5f, 1.2f};
    case VizEQ::Pop: return {0.8f, 1.2f, 1.8f};
    case VizEQ::Jazz: return {1.1f, 0.8f, 0.6f};
    case VizEQ::Electronic: return {1.7f, 0.6f, 1.7f};
    default: return {1.0f, 1.0f, 1.0f};
    }
}
static bool VizInitAudioClient(IMMDeviceEnumerator* pEnum,
                                winrt::com_ptr<IAudioClient>& pClient,
                                winrt::com_ptr<IAudioCaptureClient>& pCapture,
                                UINT32& sampleRate, UINT32& channels,
                                bool& isFloat, HANDLE hEvent) {
    pClient = nullptr;
    pCapture = nullptr;
    // The device picked in the player menu's "Visualizer audio device", else the
    // default output. A render device is captured as loopback, a mic directly.
    winrt::com_ptr<IMMDevice> pDev;
    wchar_t chosen[512] = {};
    Wh_GetStringValue(L"captureEndpointId", chosen, ARRAYSIZE(chosen));
    if (chosen[0] && FAILED(pEnum->GetDevice(chosen, pDev.put()))) pDev = nullptr;
    if (!pDev && FAILED(pEnum->GetDefaultAudioEndpoint(eRender, eConsole, pDev.put())))
        return false;
    DWORD streamFlags = AUDCLNT_STREAMFLAGS_LOOPBACK | AUDCLNT_STREAMFLAGS_EVENTCALLBACK;
    if (auto endpoint = pDev.try_as<IMMEndpoint>()) {
        EDataFlow flow = eRender;
        if (SUCCEEDED(endpoint->GetDataFlow(&flow)) && flow == eCapture)
            streamFlags = AUDCLNT_STREAMFLAGS_EVENTCALLBACK;
    }
    winrt::com_ptr<IAudioClient> pC;
    if (FAILED(pDev->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr,
                            pC.put_void())))
        return false;
    WAVEFORMATEX* pwfx = nullptr;
    pC->GetMixFormat(&pwfx);
    if (!pwfx)
        return false;
    sampleRate = pwfx->nSamplesPerSec;
    channels = pwfx->nChannels;
    isFloat = (pwfx->wFormatTag == WAVE_FORMAT_IEEE_FLOAT) ||
            (pwfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE &&
            reinterpret_cast<WAVEFORMATEXTENSIBLE*>(pwfx)->SubFormat ==
                KSDATAFORMAT_SUBTYPE_IEEE_FLOAT);
    HRESULT hr = pC->Initialize(
        AUDCLNT_SHAREMODE_SHARED,
        streamFlags, 200000, 0, pwfx, nullptr);
    CoTaskMemFree(pwfx);
    if (FAILED(hr))
        return false;
    if (hEvent)
        pC->SetEventHandle(hEvent);
    winrt::com_ptr<IAudioCaptureClient> pCap;
    if (FAILED(pC->GetService(__uuidof(IAudioCaptureClient), pCap.put_void())))
        return false;
    if (FAILED(pC->Start()))
        return false;
    pClient = pC;
    pCapture = pCap;
    return true;
}
static void VizCaptureThreadProc() {
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    BuildHannWindow();
    BuildTwiddleFactors();
    winrt::com_ptr<IMMDeviceEnumerator> pEnum;
    if (FAILED(CoCreateInstance(XIID_MMDeviceEnumerator, nullptr, CLSCTX_ALL,
                                XIID_IMMDeviceEnumerator, pEnum.put_void()))) {
        g_CaptureRunning.store(false);
        CoUninitialize();
        return;
    }
    auto* notifyClient = new VizEndpointNotificationClient();
    bool notifyRegistered =
        SUCCEEDED(pEnum->RegisterEndpointNotificationCallback(notifyClient));
    winrt::com_ptr<IAudioClient> pClient;
    winrt::com_ptr<IAudioCaptureClient> pCapture;
    UINT32 sampleRate = 48000, channels = 2;
    bool isFloat = true;
    g_VizDeviceChanged.store(false, std::memory_order_relaxed);
    if (VizInitAudioClient(pEnum.get(), pClient, pCapture, sampleRate, channels,
                        isFloat, g_hCaptureEvent))
        BuildLogBins(sampleRate);
    static constexpr int RING_CAP = VIZ_FFT_SIZE * 4;
    std::vector<float> ringBuf(RING_CAP, 0.f);
    int ringHead = 0, ringCount = 0;
    std::vector<float> re(VIZ_FFT_SIZE), im(VIZ_FFT_SIZE);
    float bandEnv[VIZ_NUM_BANDS] = {};
    static constexpr float GRAVITY[VIZ_NUM_BANDS] = {0.018f, 0.020f, 0.022f, 0.025f,
                                                    0.030f, 0.036f, 0.042f};
    ULONGLONG lastReinitAttempt = GetTickCount64() - 1000;
    while (g_CaptureRunning.load(std::memory_order_relaxed)) {
        if (g_hCaptureEvent)
            WaitForSingleObject(g_hCaptureEvent, 20);
        else
            Sleep(8);
        bool needsReinit = g_VizDeviceChanged.exchange(false, std::memory_order_relaxed) ||
                            !pClient;
        if (needsReinit) {
            ULONGLONG now = GetTickCount64();
            if (now - lastReinitAttempt >= 500) {
                lastReinitAttempt = now;
                if (pClient)
                    pClient->Stop();
                ringHead = 0;
                ringCount = 0;
                for (int b = 0; b < VIZ_NUM_BANDS; b++) {
                    bandEnv[b] = 0.f;
                    g_VizBands[b].store(0.f, std::memory_order_relaxed);
                }
                if (VizInitAudioClient(pEnum.get(), pClient, pCapture, sampleRate,
                                    channels, isFloat, g_hCaptureEvent))
                    BuildLogBins(sampleRate);
            }
        }
        if (!pCapture)
            continue;
        UINT32 packetSize = 0;
        HRESULT hr = pCapture->GetNextPacketSize(&packetSize);
        if (hr == AUDCLNT_E_DEVICE_INVALIDATED) {
            g_VizDeviceChanged.store(true, std::memory_order_relaxed);
            continue;
        }
        if (FAILED(hr) || packetSize == 0) {
            for (int b = 0; b < VIZ_NUM_BANDS; b++) {
                bandEnv[b] = std::max(0.f, bandEnv[b] - GRAVITY[b]);
                g_VizBands[b].store(bandEnv[b], std::memory_order_relaxed);
            }
            continue;
        }
        while (packetSize > 0) {
            BYTE* pData = nullptr;
            UINT32 numFrames = 0;
            DWORD flags = 0;
            HRESULT hrBuf =
                pCapture->GetBuffer(&pData, &numFrames, &flags, nullptr, nullptr);
            if (hrBuf == AUDCLNT_E_DEVICE_INVALIDATED) {
                g_VizDeviceChanged.store(true, std::memory_order_relaxed);
                break;
            }
            if (FAILED(hrBuf))
                break;
            if (!(flags & AUDCLNT_BUFFERFLAGS_SILENT) && pData && numFrames > 0) {
                if (isFloat) {
                    float* src = reinterpret_cast<float*>(pData);
                    for (UINT32 f = 0; f < numFrames; f++) {
                        float mono = 0.f;
                        for (UINT32 c = 0; c < channels; c++)
                            mono += src[f * channels + c];
                        ringBuf[ringHead] = mono / (float)channels;
                        ringHead = (ringHead + 1) % RING_CAP;
                        if (ringCount < RING_CAP)
                            ringCount++;
                    }
                } else {
                    INT16* src = reinterpret_cast<INT16*>(pData);
                    for (UINT32 f = 0; f < numFrames; f++) {
                        float mono = 0.f;
                        for (UINT32 c = 0; c < channels; c++)
                            mono += src[f * channels + c] / 32768.f;
                        ringBuf[ringHead] = mono / (float)channels;
                        ringHead = (ringHead + 1) % RING_CAP;
                        if (ringCount < RING_CAP)
                            ringCount++;
                    }
                }
            }
            pCapture->ReleaseBuffer(numFrames);
            hr = pCapture->GetNextPacketSize(&packetSize);
            if (hr == AUDCLNT_E_DEVICE_INVALIDATED) {
                g_VizDeviceChanged.store(true, std::memory_order_relaxed);
                break;
            }
            if (FAILED(hr))
                break;
        }
        while (ringCount >= VIZ_FFT_SIZE) {
            int readStart = (ringHead - ringCount + RING_CAP) % RING_CAP;
            for (int i = 0; i < VIZ_FFT_SIZE; i++) {
                re[i] = ringBuf[(readStart + i) % RING_CAP] * g_HannWindow[i];
                im[i] = 0.f;
            }
            ringCount -= VIZ_FFT_SIZE / 2;
            VizFFT(re, im);
            float t_sens = g_settings.vizSensitivity / 100.0f;
            float sliderGain = (t_sens <= 1.0f)
                ? 0.25f + t_sens * t_sens * 2.75f
                : 3.0f + (t_sens - 1.0f) * 4.0f;
            auto eq = GetVizEQMultipliers(g_settings.vizEq);
            static constexpr float BAND_SENSITIVITY[VIZ_NUM_BANDS] = {
                0.30f, 0.22f, 0.12f, 0.06f, 0.030f, 0.018f, 0.010f};
            static constexpr int BAND_EQ_ZONE[VIZ_NUM_BANDS] = {0, 0, 1, 1, 2, 2, 2};
            for (int b = 0; b < VIZ_NUM_BANDS; b++) {
                int bStart = g_LogBinStart[b];
                int bEnd = g_LogBinStart[b + 1];
                if (bEnd <= bStart)
                    bEnd = bStart + 1;
                float sumSq = 0.f;
                int count = 0;
                for (int k = bStart; k < bEnd; k++) {
                    sumSq += re[k] * re[k] + im[k] * im[k];
                    count++;
                }
                float rms = (count > 0) ? sqrtf(sumSq / (float)count) : 0.f;
                float eqM = (BAND_EQ_ZONE[b] == 0)   ? eq.low
                            : (BAND_EQ_ZONE[b] == 1) ? eq.mid
                                                    : eq.high;
                // 1.9.4: map level on a 48 dB scale. The old linear map left
                // normal mic and music levels (about -20 dB) at 1-3 % height.
                float lin = (rms / (VIZ_FFT_SIZE * 0.5f)) / BAND_SENSITIVITY[b] *
                            sliderGain * eqM * g_settings.vizInputGain;
                float mag = lin > 1e-6f
                    ? std::max(0.f, std::min(1.f, 1.f + 20.f * log10f(lin) / 48.f))
                    : 0.f;
                bandEnv[b] = (mag >= bandEnv[b])
                                ? mag
                                : std::max(0.f, bandEnv[b] - GRAVITY[b]);
                g_VizBands[b].store(bandEnv[b], std::memory_order_relaxed);
            }
        }
    }
    if (pClient)
        pClient->Stop();
    if (notifyRegistered)
        pEnum->UnregisterEndpointNotificationCallback(notifyClient);
    notifyClient->Release();
    CoUninitialize();
}
static void StartVizCaptureThread() {
    std::lock_guard<std::mutex> lk(g_captureThreadMtx);
    if (g_CaptureRunning.load())
        return;
    if (g_CaptureThread && g_CaptureThread->joinable())
        g_CaptureThread->join();
    g_CaptureThread.reset();
    if (!g_hCaptureEvent)
        g_hCaptureEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    g_CaptureRunning.store(true);
    g_CaptureThread.emplace(VizCaptureThreadProc);
}
static void StopVizCaptureThread() {
    g_CaptureRunning.store(false);
    if (g_hCaptureEvent)
        SetEvent(g_hCaptureEvent);
    std::lock_guard<std::mutex> lk(g_captureThreadMtx);
    if (g_CaptureThread) {
        if (g_CaptureThread->joinable())
            g_CaptureThread->join();
        g_CaptureThread.reset();
    }
    if (g_hCaptureEvent) {
        CloseHandle(g_hCaptureEvent);
        g_hCaptureEvent = nullptr;
    }
    for (int i = 0; i < VIZ_NUM_BANDS; i++)
        g_VizBands[i].store(0.f);
}
static float g_VizPeak[VIZ_BARS_MAX] = {};
static float g_VizTarget[VIZ_BARS_MAX] = {};
static float g_VizBreatheEnv = 0.f;
static constexpr float VIZ_SEEDS[20] = {
    0.83f, 0.41f, 1.27f, 0.61f, 1.09f, 0.37f, 0.95f, 0.52f, 1.18f, 0.74f,
    0.29f, 1.03f, 0.66f, 0.88f, 0.45f, 1.21f, 0.57f, 0.93f, 0.31f, 1.15f};
static void UpdateVisualizerPeaks() {
    const int vizBars = std::max(1, std::min(g_settings.vizBars, VIZ_BARS_MAX));
    float bands[VIZ_NUM_BANDS];
    float masterPeak = 0.f;
    for (int i = 0; i < VIZ_NUM_BANDS; i++) {
        bands[i] = g_VizBands[i].load(std::memory_order_relaxed);
        masterPeak = std::max(masterPeak, bands[i]);
    }
    auto eq = GetVizEQMultipliers(g_settings.vizEq);
    auto sampleBands = [&](float t) -> float {
        float pos = t * (VIZ_NUM_BANDS - 1);
        int lo = (int)pos;
        int hi = std::min(lo + 1, VIZ_NUM_BANDS - 1);
        return bands[lo] * (1.f - (pos - (float)lo)) +
            bands[hi] * (pos - (float)lo);
    };
    auto eqForT = [&](float t) -> float {
        return (t < 0.33f) ? eq.low : (t < 0.66f) ? eq.mid : eq.high;
    };
    float t = (float)GetTickCount64() * 0.001f;
    float center = (vizBars - 1) * 0.5f;
    for (int i = 0; i < vizBars; i++) {
        float freqT = (vizBars > 1) ? (float)i / (float)(vizBars - 1) : 0.5f;
        float target = 0.f;
        switch (g_settings.vizShape) {
            case VizShape::Stereo:
                target = sampleBands(freqT) * eqForT(freqT);
                break;
            case VizShape::Mountain: {
                float dist = fabsf((float)i - center) / std::max(1.f, center);
                float energy = sampleBands(dist) * eqForT(dist);
                float taper = 1.6f - dist * 0.9f;
                target = std::max(
                    0.f, std::min(1.f, (energy + masterPeak * (0.2f - dist * 0.12f)) *
                                        taper));
                break;
            }
            case VizShape::Mirror: {
                float mirT = 1.f - fabsf((float)i - center) / std::max(1.f, center);
                float energy = sampleBands(mirT) * eqForT(mirT);
                target = std::max(
                    0.f, std::min(1.f, (energy + masterPeak * (0.1f + mirT * 0.12f)) *
                                        1.3f));
                break;
            }
            case VizShape::Wave: {
                float phase = (float)i * (2.f * VIZ_PI / (float)vizBars);
                float wave = 0.55f + 0.45f * sinf(t * 3.5f - phase);
                float energy = sampleBands(freqT) * eqForT(freqT);
                target = std::max(0.f, std::min(1.f, energy * wave + masterPeak * 0.15f));
                break;
            }
            case VizShape::Breathe: {
                if (i == 0) {
                    float k = (masterPeak > g_VizBreatheEnv) ? 0.04f : 0.015f;
                    g_VizBreatheEnv += (masterPeak - g_VizBreatheEnv) * k;
                }
                float rate = 0.55f + VIZ_SEEDS[i % 20] * 0.18f;
                float inhale =
                    0.5f + 0.5f * sinf(t * rate + VIZ_SEEDS[i % 20] * 1.2f);
                target = std::max(0.f, std::min(1.f,
                                                inhale * (0.12f + g_VizBreatheEnv * 0.88f)));
                break;
            }
        }
        g_VizTarget[i] = std::max(0.f, std::min(1.f, target));
    }
}
using VizRect = winrt::Windows::UI::Xaml::Shapes::Rectangle;
[[clang::no_destroy]] static std::optional<std::vector<VizRect>> g_vizBars{std::in_place};
[[clang::no_destroy]] static std::optional<std::vector<SolidColorBrush>> g_vizBrushes{std::in_place};
static winrt::Windows::UI::Color VizLerpColor(winrt::Windows::UI::Color a,
                                            winrt::Windows::UI::Color b, float t) {
    auto L = [](BYTE x, BYTE y, float tt) -> BYTE {
        return (BYTE)((int)x + (int)((float)((int)y - (int)x) * tt));
    };
    return winrt::Windows::UI::Color{255, L(a.R, b.R, t), L(a.G, b.G, t), L(a.B, b.B, t)};
}
static winrt::Windows::UI::Color VizEnsureContrast(winrt::Windows::UI::Color c) {
    const int kLumaThreshold = 90;
    bool light = IsSystemLightTheme();
    int luma = (c.R * 299 + c.G * 587 + c.B * 114) / 1000;
    int edgeDist = light ? (255 - luma) : luma;
    if (edgeDist >= kLumaThreshold) return c;
    winrt::Windows::UI::Color base = light
        ? winrt::Windows::UI::Color{255, 0, 0, 0}
        : winrt::Windows::UI::Color{255, 255, 255, 255};
    if (g_cachedThumbnailBytes.empty()) return base;
    float t = edgeDist / (float)kLumaThreshold;
    float tintAmount = 0.65f + t * 0.35f;
    return VizLerpColor(base, c, tintAmount);
}
static double g_overlayVizH = 0.0;
static double VizZoneHeight() {
    double h = 0.0;
    if (g_settings.showAlbumArt && g_settings.albumArtMaxHeight > 0)
        h = std::max(h, (double)g_settings.albumArtMaxHeight);
    if (g_settings.showMediaButtons)
        h = std::max(h, (double)g_settings.buttonSize);
    if (h <= 0.0)
        h = (g_settings.playerMaxHeight > 0 ? (double)g_settings.playerMaxHeight : 40.0);
    if (g_settings.playerMaxHeight > 0)
        h = std::min(h, (double)g_settings.playerMaxHeight);
    return h;
}
static void VizApplyFrame() {
    if (!g_settings.vizEnabled || g_vizBars->empty())
        return;
    UpdateVisualizerPeaks();
    float attack = 0.55f, decay = 0.18f;
    float sensBoost = std::max(0.f, (g_settings.vizSensitivity - 100) / 200.f) * 0.12f;
    switch (g_settings.vizShape) {
        case VizShape::Stereo:  attack = 0.72f; decay = 0.22f + sensBoost; break;
        case VizShape::Mirror:  attack = 0.52f; decay = 0.20f + sensBoost; break;
        case VizShape::Wave:    attack = 0.34f; decay = 0.17f + sensBoost; break;
        case VizShape::Breathe: attack = 0.20f; decay = 0.11f + sensBoost; break;
        default:                decay += sensBoost; break;
    }
    int barCount = std::min((int)g_vizBars->size(), std::max(1, g_settings.vizBars));
    double zoneH = VizZoneHeight();
    double maxBH = std::max(4.0, zoneH - 6.0);
    double minBH = (double)g_settings.vizBarWidth;
    if (g_settings.vizOverlay) {
        maxBH = g_overlayVizH > 0 ? std::max(4.0, g_overlayVizH - 2.0) : maxBH;
        minBH = 0.0;
    }
    double idlePx = std::min((double)g_settings.vizIdleBarSize, std::max(0.0, maxBH - minBH));
    double range = std::max(0.0, maxBH - minBH - idlePx);
    bool idleHidden = (g_settings.vizIdleBarSize == 0);
    winrt::Windows::UI::Color baseCol{255, 255, 255, 255};
    if (g_settings.vizColorMode == VizColorMode::DynamicAlbum) {
        if (g_vizBaseColorDirty || g_vizPaletteColorsDirty) {
            g_cachedVizBaseColor = VizEnsureContrast(g_cachedAlbumPalette.primary);
            g_cachedVizBaseColor.A = 255;
        }
        baseCol = g_cachedVizBaseColor;
    } else {
        if (g_vizBaseColorDirty) {
            g_cachedVizBaseColor = ParseColorWithThemeSupport(g_settings.vizColor, 255);
        }
        baseCol = g_cachedVizBaseColor;
    }
    if (g_vizPaletteColorsDirty || g_vizBaseColorDirty) {
        g_cachedVizPal0   = VizEnsureContrast(g_cachedAlbumPalette.primary);
        g_cachedVizPal1   = VizEnsureContrast(g_cachedAlbumPalette.secondary);
        g_cachedVizCg0    = ParseColorWithSpecialValues(g_settings.vizColor1, 255);
        g_cachedVizCg1    = ParseColorWithSpecialValues(g_settings.vizColor2, 255);
        g_cachedVizAcrCol = ParseColorWithThemeSupport(g_settings.vizColor, 255);
        g_vizPaletteColorsDirty = false;
        g_vizBaseColorDirty = false;
    }
    const auto& pal0   = g_cachedVizPal0;
    const auto& pal1   = g_cachedVizPal1;
    const auto& cg0    = g_cachedVizCg0;
    const auto& cg1    = g_cachedVizCg1;
    const auto& acrCol = g_cachedVizAcrCol;
    for (int i = 0; i < barCount; i++) {
        float tgt = g_VizTarget[i], cur = g_VizPeak[i];
        float a = attack, d = decay;
        if (g_settings.vizShape == VizShape::Mountain) {
            float dist = fabsf((float)i - ((barCount - 1) * 0.5f));
            if (dist < 0.5f)      { a = 0.85f; d = 0.26f + sensBoost; }
            else if (dist < 1.5f) { a = 0.62f; d = 0.20f + sensBoost; }
            else                  { a = 0.92f; d = 0.34f + sensBoost; }
        }
        float next = cur + (tgt - cur) * ((tgt > cur) ? a : d);
        g_VizPeak[i] = (fabsf(next - cur) > 0.0005f) ? next : tgt;
        float fac = std::max(0.f, g_VizPeak[i]);
        double bh = idleHidden
            ? (fac * maxBH)
            : (minBH + idlePx + fac * range);
        winrt::Windows::UI::Color c = baseCol;
        if (g_settings.vizColorMode == VizColorMode::DynamicGradient) {
            float t = (float)i / std::max(1, barCount - 1);
            float freqT = std::min(1.f, t * 0.6f + fac * 0.4f);
            c = VizLerpColor(pal0, pal1, freqT);
        } else if (g_settings.vizColorMode == VizColorMode::CustomGradient) {
            float t = (barCount > 1) ? (float)i / (barCount - 1) : 0.f;
            c = VizLerpColor(cg0, cg1, t);
        } else if (g_settings.vizColorMode == VizColorMode::Acrylic) {
            BYTE aa = (BYTE)std::max(30, std::min(180, (int)(150.f * fac + 30.f)));
            c = winrt::Windows::UI::Color{aa, acrCol.R, acrCol.G, acrCol.B};
        }
        try {
            (*g_vizBars)[i].Height(bh);
            if (i < (int)g_vizBrushes->size() && (*g_vizBrushes)[i])
                (*g_vizBrushes)[i].Color(c);
        } catch (...) {}
    }
}
[[clang::no_destroy]] static winrt::Windows::UI::Xaml::DispatcherTimer g_vizDispatcherTimer{nullptr};
static winrt::event_token g_vizDispatcherTimerToken{};
static bool g_vizDispatcherTimerHasToken = false;
static void DockFitTick();
static void VizTimerTick(winrt::Windows::Foundation::IInspectable const&,
                        winrt::Windows::Foundation::IInspectable const&) {
    if (g_unloading || g_applyingSettings) return;
    if (!g_settings.vizEnabled) return;
    DockFitTick();
    VizApplyFrame();
}
static void StartVizTimer() {
    HWND hWnd = g_taskbarWnd;
    if (!hWnd || !IsWindow(hWnd)) return;
    RunFromWindowThread(hWnd, [](void*) {
        try {
            if (!g_vizDispatcherTimer) {
                g_vizDispatcherTimer = winrt::Windows::UI::Xaml::DispatcherTimer();
                g_vizDispatcherTimer.Interval(
                    winrt::Windows::Foundation::TimeSpan{std::chrono::milliseconds(16)});
                g_vizDispatcherTimerToken = g_vizDispatcherTimer.Tick(&VizTimerTick);
                g_vizDispatcherTimerHasToken = true;
            }
            g_vizDispatcherTimer.Start();
        } catch (...) {}
    }, nullptr);
}
static void StopVizTimer() {
    HWND hWnd = g_taskbarWnd;
    auto stop = [](void*) {
        try {
            if (g_vizDispatcherTimer) {
                g_vizDispatcherTimer.Stop();
                if (g_unloading) {
                    if (g_vizDispatcherTimerHasToken) {
                        g_vizDispatcherTimer.Tick(g_vizDispatcherTimerToken);
                        g_vizDispatcherTimerHasToken = false;
                    }
                    g_vizDispatcherTimer = nullptr;
                }
            }
        } catch (...) {}
    };
    if (hWnd && IsWindow(hWnd)) {
        RunFromWindowThread(hWnd, stop, nullptr);
    } else {
        stop(nullptr);
    }
}
static FrameworkElement BuildVisualizerElement() {
    g_vizBars->clear();
    g_vizBrushes->clear();
    int barCount = std::clamp(g_settings.vizBars, 1, VIZ_BARS_MAX);
    double zoneH = VizZoneHeight();
    StackPanel bars;
    bars.Name(L"FluentMedia_VisualizerBars");
    bars.Orientation(Orientation::Horizontal);
    bars.Height(zoneH);
    bars.VerticalAlignment(VerticalAlignment::Center);
    bars.HorizontalAlignment(HorizontalAlignment::Center);
    bars.IsHitTestVisible(false);
    VerticalAlignment va = (g_settings.vizAnchor == VizAnchor::Top)    ? VerticalAlignment::Top
                        : (g_settings.vizAnchor == VizAnchor::Bottom) ? VerticalAlignment::Bottom
                                                            : VerticalAlignment::Center;
    double minBH = (double)g_settings.vizBarWidth;
    double maxBH = std::max(4.0, zoneH - 6.0);
    double idlePx = std::min((double)g_settings.vizIdleBarSize, std::max(0.0, maxBH - minBH));
    double corner = g_settings.vizBarWidth * 0.5;
    bool idleHidden = (g_settings.vizIdleBarSize == 0);
    for (int i = 0; i < barCount; i++) {
        VizRect r;
        r.Width((double)g_settings.vizBarWidth);
        r.Height(idleHidden ? 0.0 : (minBH + idlePx));
        r.RadiusX(corner);
        r.RadiusY(corner);
        r.VerticalAlignment(va);
        if (i > 0)
            r.Margin({(double)g_settings.vizBarGap, 0, 0, 0});
        SolidColorBrush br = MakeBrush({255, 255, 255, 255});
        r.Fill(br);
        if (g_settings.vizColorMode == VizColorMode::Acrylic) {
            r.Stroke(MakeBrush({0x40, 0xFF, 0xFF, 0xFF}));
            r.StrokeThickness(0.8);
        }
        bars.Children().Append(r);
        g_vizBars->push_back(r);
        g_vizBrushes->push_back(br);
    }
    bool vizLeft = (g_settings.vizPosition == L"left");
    if (g_settings.mirrorLayout) vizLeft = !vizLeft;
    const double kVizSectionGap = 6.0;
    double marginL = (double)g_settings.vizPadLeft  + (vizLeft ? 0.0 : kVizSectionGap);
    double marginR = (double)g_settings.vizPadRight + (vizLeft ? kVizSectionGap : 0.0);
    Grid vizContainer;
    vizContainer.Name(L"FluentMedia_Visualizer");
    vizContainer.Height(zoneH);
    vizContainer.VerticalAlignment(VerticalAlignment::Center);
    vizContainer.HorizontalAlignment(HorizontalAlignment::Center);
    vizContainer.IsHitTestVisible(false);
    vizContainer.Background(MakeBrush({0x00, 0x00, 0x00, 0x00}));
    vizContainer.Margin({marginL, 0, marginR, 0});
    if (g_settings.showDebugBorders) {
        Border vizDebugBorder;
        vizDebugBorder.BorderBrush(MakeBrush({0xFF, 0xFF, 0xFF, 0x00}));
        vizDebugBorder.BorderThickness({1, 1, 1, 1});
        vizDebugBorder.HorizontalAlignment(HorizontalAlignment::Stretch);
        vizDebugBorder.VerticalAlignment(VerticalAlignment::Stretch);
        vizContainer.Children().Append(vizDebugBorder);
    }
    vizContainer.Children().Append(bars);
    return vizContainer;
}
// Behind-widget bars (1.9.0). The same bars as the inline visualizer, laid
// across the whole player under the content and dimmed so text and buttons stay
// readable. The count follows the content width so the layer never widens the
// player. Layout idea from Taskbar Media Widget by uMk0 (MIT).
static constexpr wchar_t kOverlayVizName[]    = L"FluentMedia_OverlayVisualizer";
static constexpr wchar_t kProgressLayerName[] = L"FluentMedia_Progress";
static constexpr wchar_t kProgressTrackName[] = L"FluentMedia_ProgressTrack";
static constexpr wchar_t kProgressFillName[]  = L"FluentMedia_ProgressFill";
static constexpr wchar_t kTimeTextName[]      = L"FluentMedia_Time";
static constexpr double  kOverlayInset        = 4.0;
static bool g_vizOnly = false;
static double g_dockWidth = -1, g_dockFrom = 0, g_dockTarget = 0;
static double g_dockOpacity = 1, g_dockOpacityFrom = 1, g_dockOpacityTarget = 1;
static std::chrono::steady_clock::time_point g_dockStart;

// Bars clear the progress bar behind media; alone they rest 2 DIP above the border.
static double OverlayVizBottomInset() {
    if (g_vizOnly) return 2.0;
    return 3.0 + (g_settings.showProgressBar ? (double)g_settings.progressHeight : 0.0);
}
static FrameworkElement BuildOverlayVisualizer(Grid const& panel, double phMin, double phMax) {
    g_vizBars->clear();
    g_vizBrushes->clear();
    double zoneH = VizZoneHeight();
    Grid layer;
    layer.Name(kOverlayVizName);
    layer.HorizontalAlignment(HorizontalAlignment::Stretch);
    layer.VerticalAlignment(VerticalAlignment::Stretch);
    if (phMin > 0) layer.MinHeight(phMin);
    if (phMax > 0) layer.MaxHeight(phMax);
    layer.IsHitTestVisible(false);
    layer.Opacity(g_vizOnly ? 1.0 : g_settings.vizOverlayOpacity / 100.0);
    StackPanel bars;
    bars.Orientation(Orientation::Horizontal);
    bars.HorizontalAlignment(HorizontalAlignment::Center);
    bars.VerticalAlignment(VerticalAlignment::Stretch);
    bars.Margin({kOverlayInset, 3, kOverlayInset, OverlayVizBottomInset()});
    bars.IsHitTestVisible(false);
    double minBH = (double)g_settings.vizBarWidth;
    double maxBH = std::max(4.0, zoneH - 6.0);
    double idlePx = std::min((double)g_settings.vizIdleBarSize, std::max(0.0, maxBH - minBH));
    double corner = g_settings.vizBarWidth * 0.5;
    bool idleHidden = (g_settings.vizIdleBarSize == 0);
    for (int i = 0; i < VIZ_BARS_MAX; i++) {
        VizRect r;
        r.Width((double)g_settings.vizBarWidth);
        r.Height(idleHidden ? 0.0 : (minBH + idlePx));
        r.RadiusX(corner);
        r.RadiusY(corner);
        r.VerticalAlignment(VerticalAlignment::Bottom);
        if (i > 0) r.Margin({(double)g_settings.vizBarGap, 0, 0, 0});
        r.Visibility(Visibility::Collapsed);
        SolidColorBrush br = MakeBrush({255, 255, 255, 255});
        r.Fill(br);
        bars.Children().Append(r);
        g_vizBars->push_back(r);
        g_vizBrushes->push_back(br);
    }
    layer.Children().Append(bars);
    winrt::weak_ref<StackPanel> weakBars = winrt::make_weak(bars);
    layer.SizeChanged([weakBars](auto const&, SizeChangedEventArgs const& e) {
        auto b = weakBars.get();
        if (!b) return;
        double w = e.NewSize().Width - 2 * kOverlayInset;
        g_overlayVizH = std::max(4.0, e.NewSize().Height - 3.0 - OverlayVizBottomInset());
        double step = (double)g_settings.vizBarWidth + g_settings.vizBarGap;
        int n = std::clamp((int)((w + g_settings.vizBarGap) / std::max(1.0, step)), 1, VIZ_BARS_MAX);
        g_settings.vizBars = n;
        auto kids = b.Children();
        for (uint32_t i = 0; i < kids.Size(); i++) {
            auto vis = (int)i < n ? Visibility::Visible : Visibility::Collapsed;
            if (auto fe = kids.GetAt(i).try_as<UIElement>())
                if (fe.Visibility() != vis) fe.Visibility(vis);
        }
    });
    return layer;
}
static void SeekToFraction(double frac) {
    {
        std::lock_guard<std::mutex> lk(g_mediaMtx);
        if (!g_media.canSeek || !g_timeline.valid) return;
        g_timeline.posMs = g_timeline.startMs +
            (int64_t)((g_timeline.endMs - g_timeline.startMs) * frac);
    }
    UpdateProgressAndTime();
    SpawnTrackedWorker([frac]() {
        if (g_unloading) return;
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
        try {
            GlobalSystemMediaTransportControlsSession session{nullptr};
            { std::lock_guard<std::mutex> lk(g_sessionMtx); session = g_currentSession; }
            if (session) {
                auto tl = session.GetTimelineProperties();
                int64_t start = tl.StartTime().count(), end = tl.EndTime().count();
                if (end > start)
                    session.TryChangePlaybackPositionAsync(start + (int64_t)((end - start) * frac)).get();
            }
        } catch (...) {}
        winrt::uninit_apartment();
    });
}
// Progress line along the player's bottom edge (1.9.0), with an invisible
// strip on top that takes left clicks to seek.
static FrameworkElement BuildProgressLayer(double phMin, double phMax) {
    double h = (double)g_settings.progressHeight;
    Grid layer;
    layer.Name(kProgressLayerName);
    layer.HorizontalAlignment(HorizontalAlignment::Stretch);
    layer.VerticalAlignment(VerticalAlignment::Stretch);
    if (phMin > 0) layer.MinHeight(phMin);
    if (phMax > 0) layer.MaxHeight(phMax);
    Border track;
    track.Name(kProgressTrackName);
    track.Height(h);
    track.VerticalAlignment(VerticalAlignment::Bottom);
    track.HorizontalAlignment(HorizontalAlignment::Stretch);
    track.Margin({kOverlayInset + 2, 0, kOverlayInset + 2, 1});
    track.CornerRadius({h / 2, h / 2, h / 2, h / 2});
    track.Background(MakeBrush({0x38, 0xFF, 0xFF, 0xFF}));
    track.IsHitTestVisible(false);
    Border fill;
    fill.Name(kProgressFillName);
    fill.Height(h);
    fill.Width(0);
    fill.VerticalAlignment(VerticalAlignment::Bottom);
    fill.HorizontalAlignment(HorizontalAlignment::Left);
    fill.Margin({kOverlayInset + 2, 0, 0, 1});
    fill.CornerRadius({h / 2, h / 2, h / 2, h / 2});
    if (g_settings.progressArtwork) {
        fill.Background(MakeBrush({0xFF, 0x89, 0xB4, 0xFA}));
    } else {
        winrt::Windows::UI::Xaml::Media::LinearGradientBrush grad;
        grad.StartPoint(winrt::Windows::Foundation::Point(0.0f, 0.5f));
        grad.EndPoint(winrt::Windows::Foundation::Point(1.0f, 0.5f));
        GradientStop a; a.Color({0xFF, 0x89, 0xB4, 0xFA}); a.Offset(0.0);
        GradientStop b; b.Color({0xFF, 0xCB, 0xA6, 0xF7}); b.Offset(1.0);
        grad.GradientStops().Append(a);
        grad.GradientStops().Append(b);
        fill.Background(grad);
    }
    fill.IsHitTestVisible(false);
    layer.Children().Append(track);
    layer.Children().Append(fill);
    if (g_settings.clickToSeek) {
        Border hit;
        hit.Height(h + 5);
        hit.VerticalAlignment(VerticalAlignment::Bottom);
        hit.HorizontalAlignment(HorizontalAlignment::Stretch);
        hit.Margin({kOverlayInset + 2, 0, kOverlayInset + 2, 0});
        hit.Background(MakeBrush({0x00, 0x00, 0x00, 0x00}));
        hit.PointerPressed([](auto const& sender, PointerRoutedEventArgs const& e) {
            auto fe = sender.template try_as<FrameworkElement>();
            if (fe && e.GetCurrentPoint(fe).Properties().IsLeftButtonPressed()) e.Handled(true);
        });
        hit.PointerReleased([](auto const& sender, PointerRoutedEventArgs const& e) {
            auto fe = sender.template try_as<FrameworkElement>();
            if (!fe || g_unloading) return;
            auto pt = e.GetCurrentPoint(fe);
            if (pt.Properties().PointerUpdateKind() !=
                winrt::Windows::UI::Input::PointerUpdateKind::LeftButtonReleased) return;
            e.Handled(true);
            double w = fe.ActualWidth();
            if (w <= 0) return;
            SeekToFraction(std::clamp(pt.Position().X / w, 0.0, 1.0));
        });
        layer.Children().Append(hit);
    }
    return layer;
}
static std::wstring FormatClock(int64_t ms) {
    int64_t s = std::max<int64_t>(0, ms / 1000);
    wchar_t buf[32];
    if (s >= 3600)
        swprintf_s(buf, L"%lld:%02lld:%02lld", s / 3600, (s / 60) % 60, s % 60);
    else
        swprintf_s(buf, L"%lld:%02lld", s / 60, s % 60);
    return buf;
}
static void UpdateProgressAndTime() {
    if (!g_playerGrid) return;
    TimelineState t;
    { std::lock_guard<std::mutex> lk(g_mediaMtx); t = g_timeline; }
    try {
        if (g_settings.timeDisplayMode != 0) {
            if (auto tb = FindChildByName(g_playerGrid, kTimeTextName).try_as<TextBlock>()) {
                std::wstring text;
                if (t.valid) {
                    text = FormatClock(t.posMs - t.startMs);
                    if (g_settings.timeDisplayMode == 2)
                        text += L" / " + FormatClock(t.endMs - t.startMs);
                }
                auto vis = t.valid ? Visibility::Visible : Visibility::Collapsed;
                if (tb.Visibility() != vis) tb.Visibility(vis);
                if (std::wstring_view(tb.Text()) != text) tb.Text(text);
            }
        }
        if (g_settings.showProgressBar) {
            auto layer = FindChildByName(g_playerGrid, kProgressLayerName);
            if (!layer) return;
            if (layer.Visibility() != Visibility::Visible) layer.Visibility(Visibility::Visible);
            auto track = FindChildByName(layer, kProgressTrackName);
            auto fill = FindChildByName(layer, kProgressFillName);
            if (!track || !fill) return;
            if (!t.valid || t.endMs <= t.startMs) { if (fill.Width() != 0) fill.Width(0); return; }
            double frac = (double)(t.posMs - t.startMs) / (double)(t.endMs - t.startMs);
            double w = std::round(track.ActualWidth() * std::clamp(frac, 0.0, 1.0));
            if (std::isnan(fill.Width()) || std::abs(fill.Width() - w) > 0.5) fill.Width(w);
            if (g_settings.progressArtwork) {
                winrt::Windows::UI::Color c{0xFF, 0x89, 0xB4, 0xFA};
                if (g_cachedPaletteHash != 0 && !g_cachedThumbnailBytes.empty()) {
                    c = VizEnsureContrast(g_cachedAlbumPalette.primary);
                    c.A = 0xFF;
                }
                if (auto br = fill.try_as<Border>().Background().try_as<SolidColorBrush>())
                    if (br.Color() != c) br.Color(c);
            }
        }
    } catch (...) {}
}
static void StartTimerThread() {
    if (g_timerThread) return;
    g_timerStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_timerUpdateEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    g_timerThread    = CreateThread(nullptr, 0, TimerThreadProc, nullptr, 0, nullptr);
    if (!g_timerThread) {
        CloseHandle(g_timerStopEvent);
        g_timerStopEvent = nullptr;
        CloseHandle(g_timerUpdateEvent);
        g_timerUpdateEvent = nullptr;
    }
    if (g_settings.enableTitleScrolling || g_settings.enableArtistScrolling) {
        StartScrollTimer();
    }
}
static void StopTimerThread() {
    StopScrollTimer();
    StopVizTimer();
    StopVizCaptureThread();
    if (g_timerStopEvent) SetEvent(g_timerStopEvent);
    if (g_timerThread) {
        DWORD tid = GetCurrentThreadId();
        HWND hTaskbar = g_taskbarWnd;
        bool isUiThread = hTaskbar && (GetWindowThreadProcessId(hTaskbar, nullptr) == tid);
        if (isUiThread) {
            DWORD result = WAIT_TIMEOUT;
            DWORD deadline = GetTickCount() + 2000;
            while (result == WAIT_TIMEOUT && GetTickCount() < deadline) {
                result = MsgWaitForMultipleObjects(1, &g_timerThread, FALSE, 50, QS_SENDMESSAGE);
                if (result == WAIT_OBJECT_0 + 1) {
                    MSG msg;
                    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE | PM_QS_SENDMESSAGE)) {
                        TranslateMessage(&msg);
                        DispatchMessageW(&msg);
                    }
                    result = WAIT_TIMEOUT;
                }
            }
        } else {
            WaitForSingleObject(g_timerThread, 2000);
        }
        CloseHandle(g_timerThread);
        g_timerThread = nullptr;
    }
    if (g_timerStopEvent) { CloseHandle(g_timerStopEvent); g_timerStopEvent = nullptr; }
    if (g_timerUpdateEvent) { CloseHandle(g_timerUpdateEvent); g_timerUpdateEvent = nullptr; }
}
static void RefreshThemeColors() {
    if (!g_playerGrid || g_unloading || g_applyingSettings) return;
    g_vizBaseColorDirty = true;
    g_vizPaletteColorsDirty = true;
    try {
        UpdateHoverBrushColors();
        auto textClr = TextColor();
        auto artistClr = ArtistColor();
        auto buttonClr = ButtonColor();
        if (auto bgFe = FindChildByName(g_playerGrid, L"FluentMedia_Background")) {
            if (auto bgBorder = bgFe.try_as<Border>()) {
                auto& bgType = g_settings.backgroundType;
                if (bgType == L"album_art_blur") {
                    if (!g_cachedThumbnailBytes.empty()) {
                        int w = (int)bgBorder.ActualWidth();
                        int h = (int)bgBorder.ActualHeight();
                        if (w > 0 && h > 0) {
                            bgBorder.Background(MakeAlbumBlurBrush(g_cachedThumbnailBytes, w, h));
                        }
                    } else {
                        auto fallbackCol = IsSystemLightTheme()
                            ? winrt::Windows::UI::Color{0xCC, 0xF3, 0xF3, 0xF3}
                            : winrt::Windows::UI::Color{0xCC, 0x20, 0x20, 0x20};
                        bgBorder.Background(MakeBrush(fallbackCol));
                    }
                    bgBorder.Visibility(Visibility::Visible);
                    bgBorder.Opacity(g_settings.blurOpacity / 100.0);
                } else if (bgType == L"solid" || bgType == L"gradient" || bgType == L"acrylic" || bgType == L"mica" || bgType == L"mica_alt") {
                    bgBorder.Background(MakeBackgroundBrush());
                    bgBorder.Visibility(Visibility::Visible);
                    bgBorder.Opacity(1.0);
                } else {
                    bgBorder.Background(nullptr);
                    bgBorder.Visibility(Visibility::Collapsed);
                }
            }
        }
        if (auto fe = FindChildByName(g_playerGrid, L"FluentMedia_OuterBorder")) {
            if (auto btn = fe.try_as<Button>()) {
                try {
                    auto normalBg = MakeBackgroundBrush();
                    ApplyFluentMediaButtonStyle(btn);
                    btn.ApplyTemplate();
                    SetupPlayerCommonStates(btn, normalBg);
                    GoToCommonState(btn, IsHoverEffectEnabled(g_settings.playerHoverEffectMode), false, false);
                } catch (...) {}
            }
        }
        if (auto fe = FindChildByName(g_playerGrid, kTitleBlockName))
            if (auto tb = fe.try_as<TextBlock>()) tb.Foreground(MakeBrush(textClr));
        if (auto fe = FindChildByName(g_playerGrid, kArtistBlockName))
            if (auto ab = fe.try_as<TextBlock>()) ab.Foreground(MakeBrush(artistClr));
        for (const wchar_t* name : {kPrevBtnName, kPlayBtnName, kNextBtnName, kRewindBtnName, kForwardBtnName, kShuffleBtnName, kRepeatBtnName, kSwitchSessionsBtnName}) {
            if (auto fe = FindChildByName(g_playerGrid, name)) {
                if (auto btn = fe.try_as<Button>()) {
                    if (auto ct = btn.Content().try_as<TextBlock>()) ct.Foreground(MakeBrush(buttonClr));
                    ApplyFluentMediaButtonStyle(btn);
                    btn.ApplyTemplate();
                    SetupMediaButtonCommonStates(btn);
                    try { VisualStateManager::GoToState(btn, L"Normal", false); } catch (...) {}
                    ApplyButtonGradient();
                }
            }
        }
    } catch (...) {}
}
static HMONITOR GetMonitorByNumber(int monitorNumber) {
    HMONITOR result = nullptr;
    int current = 0;
    struct Ctx { int target; HMONITOR* result; int* current; };
    Ctx ctx{monitorNumber - 1, &result, &current};
    EnumDisplayMonitors(nullptr, nullptr,
        [](HMONITOR hMon, HDC, LPRECT, LPARAM lp) CALLBACK -> BOOL {
            auto* c = reinterpret_cast<Ctx*>(lp);
            if (*c->current == c->target) { *c->result = hMon; return FALSE; }
            (*c->current)++;
            return TRUE;
        }, reinterpret_cast<LPARAM>(&ctx));
    return result;
}
static HWND FindTaskbarWndForMonitor(HMONITOR targetMonitor) {
    struct Ctx { HMONITOR target; HWND result; };
    Ctx ctx{targetMonitor, nullptr};
    EnumWindows([](HWND hWnd, LPARAM lp) CALLBACK -> BOOL {
        auto* c = reinterpret_cast<Ctx*>(lp);
        DWORD pid = 0; wchar_t cls[64] = {};
        if (GetWindowThreadProcessId(hWnd, &pid) && pid == GetCurrentProcessId() &&
            GetClassNameW(hWnd, cls, ARRAYSIZE(cls)) &&
            (_wcsicmp(cls, L"Shell_TrayWnd") == 0 ||
             _wcsicmp(cls, L"Shell_SecondaryTrayWnd") == 0)) {
            HMONITOR hMon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
            if (hMon == c->target) {
                c->result = hWnd;
                return FALSE;
            }
        }
        return TRUE;
    }, reinterpret_cast<LPARAM>(&ctx));
    return ctx.result;
}
static HWND FindCurrentProcessTaskbarWnd() {
    if (HMONITOR mon = GetMonitorByNumber(g_settings.monitor)) {
        if (HWND hWnd = FindTaskbarWndForMonitor(mon)) {
            return hWnd;
        }
    } else {
    }
    HWND result = nullptr;
    EnumWindows([](HWND hWnd, LPARAM lp) CALLBACK -> BOOL {
        DWORD pid = 0; wchar_t cls[32] = {};
        if (GetWindowThreadProcessId(hWnd, &pid) && pid == GetCurrentProcessId() &&
            GetClassNameW(hWnd, cls, ARRAYSIZE(cls)) &&
            _wcsicmp(cls, L"Shell_TrayWnd") == 0)
        {
            *reinterpret_cast<HWND*>(lp) = hWnd;
            return FALSE;
        }
        return TRUE;
    }, reinterpret_cast<LPARAM>(&result));
    return result;
}
static bool IsReadableMemoryRange(const void* address, size_t size) {
    if (!address || size == 0) return false;
    MEMORY_BASIC_INFORMATION memory{};
    if (!VirtualQuery(address, &memory, sizeof(memory)) ||
        memory.State != MEM_COMMIT ||
        (memory.Protect & (PAGE_GUARD | PAGE_NOACCESS))) {
        return false;
    }
    const auto start = reinterpret_cast<uintptr_t>(address);
    const auto regionStart = reinterpret_cast<uintptr_t>(memory.BaseAddress);
    const auto regionEnd = regionStart + memory.RegionSize;
    return start >= regionStart && start <= regionEnd &&
           size <= regionEnd - start;
}
static XamlRoot GetTaskbarXamlRoot(HWND hTaskbarWnd) {
    wchar_t clsBuf[64] = {};
    GetClassNameW(hTaskbarWnd, clsBuf, ARRAYSIZE(clsBuf));
    bool isSecondary = _wcsicmp(clsBuf, L"Shell_SecondaryTrayWnd") == 0;
    HWND hTaskSwWnd = isSecondary
        ? FindWindowExW(hTaskbarWnd, nullptr, L"WorkerW", nullptr)
        : (HWND)GetProp(hTaskbarWnd, L"TaskbandHWND");
    if (!hTaskSwWnd && !isSecondary) {
        // After an Explorer crash restart the TaskbandHWND property can be
        // missing; the band window itself still sits under the rebar.
        HWND rebar = FindWindowExW(hTaskbarWnd, nullptr, L"ReBarWindow32", nullptr);
        if (rebar) hTaskSwWnd = FindWindowExW(rebar, nullptr, L"MSTaskSwWClass", nullptr);
    }
    if (!hTaskSwWnd) {
        Wh_Log(L"GetTaskbarXamlRoot: could not find taskband host window, aborting");
        return nullptr;
    }
    wchar_t swCls[64] = {};
    GetClassNameW(hTaskSwWnd, swCls, ARRAYSIZE(swCls));
    void* taskBand = (void*)GetWindowLongPtrW(hTaskSwWnd, 0);
    if (!taskBand) {
        Wh_Log(L"GetTaskbarXamlRoot: taskBand pointer is null, aborting");
        return nullptr;
    }
    void* expectedVftable = isSecondary
        ? CSecondaryTaskBand_ITaskListWndSite_vftable
        : CTaskBand_ITaskListWndSite_vftable;
    auto getTaskbarHost = isSecondary
        ? CSecondaryTaskBand_GetTaskbarHost_Original
        : CTaskBand_GetTaskbarHost_Original;
    if (!expectedVftable || !getTaskbarHost) {
        Wh_Log(L"GetTaskbarXamlRoot: %s symbols not resolved, aborting",
            isSecondary ? L"CSecondaryTaskBand" : L"CTaskBand");
        return nullptr;
    }
    void* taskBandForTaskListWndSite = taskBand;
    int i = 0;
    constexpr int kMaxSlotsToScan = 20;
    for (;; i++) {
        if (!IsReadableMemoryRange(taskBandForTaskListWndSite, sizeof(void*))) {
            Wh_Log(L"GetTaskbarXamlRoot: hit unreadable memory at slot %d, aborting", i);
            return nullptr;
        }
        if (*(void**)taskBandForTaskListWndSite == expectedVftable) break;
        if (i == kMaxSlotsToScan) {
            Wh_Log(L"GetTaskbarXamlRoot: ITaskListWndSite vftable not found within %d slots, aborting",
                kMaxSlotsToScan);
            return nullptr;
        }
        taskBandForTaskListWndSite = (void**)taskBandForTaskListWndSite + 1;
    }
    void* taskbarHostSharedPtr[2]{};
    getTaskbarHost(taskBandForTaskListWndSite, taskbarHostSharedPtr);
    if (!taskbarHostSharedPtr[0]) {
        Wh_Log(L"GetTaskbarXamlRoot: TaskbarHost shared_ptr is empty, aborting");
        if (taskbarHostSharedPtr[1] && Std_Ref_Decref_Original)
            Std_Ref_Decref_Original(taskbarHostSharedPtr[1]);
        return nullptr;
    }
    size_t taskbarElementIUnknownOffset = 0;
    bool frameHeightPatternRecognized = false;
#if defined(_M_X64) || defined(__x86_64__)
    {
        const BYTE* b = (const BYTE*)TaskbarHost_FrameHeight_Original;
        if (IsReadableMemoryRange(b, 8) &&
            b[0] == 0x48 && b[1] == 0x83 && b[2] == 0xEC && b[4] == 0x48 &&
            b[5] == 0x83 && b[6] == 0xC1 && b[7] <= 0x7F) {
            taskbarElementIUnknownOffset = b[7];
            frameHeightPatternRecognized = true;
        } else {
            Wh_Log(L"Unsupported TaskbarHost::FrameHeight pattern (x64)");
        }
    }
#elif defined(_M_ARM64) || defined(__aarch64__)
    {
        const DWORD* p = (const DWORD*)TaskbarHost_FrameHeight_Original;
        if (IsReadableMemoryRange(p, sizeof(DWORD) * 4) &&
            p[0] == 0xD503237F && (p[1] & 0xFFC07FFF) == 0xA9807BFD &&
            p[2] == 0x910003FD && (p[3] & 0xFFF00FE0) == 0xF8400C00) {
            taskbarElementIUnknownOffset = (p[3] >> 12) & 0xFF;
            frameHeightPatternRecognized = true;
        } else {
            Wh_Log(L"Unsupported TaskbarHost::FrameHeight pattern (arm64)");
        }
    }
#else
    Wh_Log(L"GetTaskbarXamlRoot: Unknown architecture, using default offset 0x10");
    taskbarElementIUnknownOffset = 0x10;
    frameHeightPatternRecognized = true;
#endif
    if (!frameHeightPatternRecognized ||
        !IsReadableMemoryRange(
            static_cast<BYTE*>(taskbarHostSharedPtr[0]) +
                taskbarElementIUnknownOffset,
            sizeof(IUnknown*))) {
        Wh_Log(L"GetTaskbarXamlRoot: FrameHeight pattern not recognized or offset unreadable, aborting");
        if (taskbarHostSharedPtr[1] && Std_Ref_Decref_Original)
            Std_Ref_Decref_Original(taskbarHostSharedPtr[1]);
        return nullptr;
    }
    auto* taskbarElementIUnknown =
        *(IUnknown**)((BYTE*)taskbarHostSharedPtr[0] +
                    taskbarElementIUnknownOffset);
    if (!taskbarElementIUnknown) {
        Wh_Log(L"GetTaskbarXamlRoot: taskbarElementIUnknown is null, aborting");
        if (taskbarHostSharedPtr[1] && Std_Ref_Decref_Original)
            Std_Ref_Decref_Original(taskbarHostSharedPtr[1]);
        return nullptr;
    }
    FrameworkElement taskbarElement{nullptr};
    HRESULT hr = taskbarElementIUnknown->QueryInterface(
        winrt::guid_of<FrameworkElement>(), winrt::put_abi(taskbarElement));
    auto result = taskbarElement ? taskbarElement.XamlRoot() : nullptr;
    if (taskbarHostSharedPtr[1] && Std_Ref_Decref_Original)
        Std_Ref_Decref_Original(taskbarHostSharedPtr[1]);
    return SUCCEEDED(hr) ? result : nullptr;
}
static const wchar_t* GetGlyphWithStyle(int cmd, const std::wstring& style, bool isPlaying = false) {
    bool isFluent = (style == L"fluent_outline" || style == L"fluent_filled");
    bool isFilled = (style == L"fluent_filled" || style == L"mdl2_filled");
    switch (cmd) {
        case 1:
            if (isFilled) return L"";
            return L"";
        case 2:
            if (isPlaying) {
                if (isFluent && isFilled) return L"";
                if (!isFluent && isFilled) return L"";
                return L"";
            } else {
                if (isFilled) return L"";
                return L"";
            }
        case 3:
            if (isFilled) return L"";
            return L"";
        case 5:
            if (isFilled) return L"";
            return L"";
        case 6:
            if (isFilled) return L"";
            return L"";
        case 7:
            return L"";
        case 8: {
            RepeatMode mode = g_repeatMode.load();
            switch (mode) {
                case RepeatMode::Off: return L"";
                case RepeatMode::All: return L"";
                case RepeatMode::One: return L"";
            }
        }
        case 9:
            return L"";
        case 10: return L"";
        case 11: return L"";
        case 12: return L"";
    }
    return L"";
}
static const wchar_t* GetGlyph(int cmd, bool isPlaying = false) {
    return GetGlyphWithStyle(cmd, g_settings.iconStyle, isPlaying);
}
static TextBlock MakeIconText(const wchar_t* glyph, double sz, winrt::Windows::UI::Color c) {
    TextBlock t;
    t.Text(glyph);
    t.FontSize(sz);
    t.Foreground(MakeBrush(c));
    t.VerticalAlignment(VerticalAlignment::Center);
    t.HorizontalAlignment(HorizontalAlignment::Center);
    bool useFluent = (g_settings.iconStyle == L"fluent_outline" || g_settings.iconStyle == L"fluent_filled");
    try {
        if (useFluent) {
            t.FontFamily(FontFamily(L"Segoe Fluent Icons"));
        } else {
            t.FontFamily(FontFamily(L"Segoe MDL2 Assets"));
        }
    } catch (...) {
        try {
            t.FontFamily(FontFamily(L"Segoe MDL2 Assets"));
        } catch (...) {
            try {
                t.FontFamily(FontFamily(L"Segoe UI Symbol"));
            } catch (...) {}
        }
    }
    return t;
}
static Button MakeControlButton(int cmd, bool isPlaying, winrt::Windows::UI::Color iconColor) {
    Button btn;
    try {
        if (cmd < 1 || cmd > 9) {
            Wh_Log(L"MakeControlButton: Invalid command %d, defaulting to 2 (play/pause)", cmd);
            cmd = 2;
        }
        btn.Width((double)g_settings.buttonSize);
        btn.Height((double)g_settings.buttonSize);
        btn.Padding({1,1,1,1});
        btn.CornerRadius({
            g_settings.buttonCornerRadiusTL,
            g_settings.buttonCornerRadiusTR,
            g_settings.buttonCornerRadiusBR,
            g_settings.buttonCornerRadiusBL
        });
        btn.BorderThickness({0,0,0,0});
        btn.VerticalAlignment(VerticalAlignment::Center);
        btn.HorizontalAlignment(HorizontalAlignment::Center);
        const wchar_t* glyph = GetGlyph(cmd, isPlaying);
        double opacity = 1.0;
        if (cmd == 7 && !g_shuffleEnabled.load()) {
            opacity = 0.4;
        }
        auto iconText = MakeIconText(glyph, (double)g_settings.buttonIconSize, iconColor);
        iconText.Opacity(opacity);
        btn.Content(winrt::box_value(iconText));
        btn.Click([cmd](auto const&, auto const&) {
            if (!g_unloading) {
                try {
                    SendMediaCommandAsync(cmd);
                    DispatchMediaUpdate();
                } catch (...) {
                    Wh_Log(L"MakeControlButton: Exception in Click handler for cmd %d", cmd);
                }
            }
        });
        ApplyFluentMediaButtonStyle(btn);

        auto isPressed = std::make_shared<bool>(false);
        auto isHovered = std::make_shared<bool>(false);

        auto updateBtnVisualState = [btn, isPressed, isHovered]() {
            try {
                GoToCommonState(btn, IsHoverEffectEnabled(g_settings.mediaButtonsHoverEffectMode), *isPressed, *isHovered);
            } catch (...) {

            }
        };

        RunWhenButtonReady(btn, [btn, updateBtnVisualState]() {
            try {
                SetupMediaButtonCommonStates(btn);
                updateBtnVisualState();
            } catch (...) {
                Wh_Log(L"MakeControlButton: Exception in RunWhenButtonReady");
            }
        });

        btn.PointerEntered([isHovered, updateBtnVisualState](auto const&, auto const&) {
            *isHovered = true;
            updateBtnVisualState();
        });

        btn.PointerExited([isHovered, updateBtnVisualState](auto const&, auto const&) {
            *isHovered = false;
            updateBtnVisualState();
        });

        btn.AddHandler(UIElement::PointerPressedEvent(), winrt::box_value(
            winrt::Windows::UI::Xaml::Input::PointerEventHandler(
            [isPressed, updateBtnVisualState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
            if (auto elem = sender.template try_as<UIElement>()) {
                elem.CapturePointer(e.Pointer());
            }
            *isPressed = true;
            updateBtnVisualState();
        })), true);

        btn.AddHandler(UIElement::PointerReleasedEvent(), winrt::box_value(
            winrt::Windows::UI::Xaml::Input::PointerEventHandler(
            [isPressed, isHovered, updateBtnVisualState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
            bool actuallyHovered = false;

            if (auto elem = sender.template try_as<UIElement>()) {
                elem.ReleasePointerCapture(e.Pointer());
                try {
                    auto bounds = elem.RenderSize();
                    auto pos = e.GetCurrentPoint(elem).Position();
                    actuallyHovered = (pos.X >= 0 && pos.X <= bounds.Width && pos.Y >= 0 && pos.Y <= bounds.Height);
                } catch (...) {}
            }
            *isPressed = false;
            *isHovered = actuallyHovered;
            updateBtnVisualState();
            e.Handled(true);
        })), true);

        btn.PointerCanceled([isPressed, isHovered, updateBtnVisualState](auto const&, auto const&) {
            *isPressed = false;
            *isHovered = false;
            updateBtnVisualState();
        });

        btn.PointerCaptureLost([isPressed, isHovered, updateBtnVisualState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
            if (auto elem = sender.template try_as<UIElement>()) {
                try {
                    auto bounds = elem.RenderSize();
                    auto pos = e.GetCurrentPoint(elem).Position();
                    *isHovered = (pos.X >= 0 && pos.X <= bounds.Width && pos.Y >= 0 && pos.Y <= bounds.Height);
                } catch (...) { *isHovered = false; }
            }
            updateBtnVisualState();
        });
    } catch (...) {
        Wh_Log(L"MakeControlButton: Exception while creating button");
    }
    return btn;
}
static void AddLayoutAnchorOverlay(Grid const& target, const wchar_t* name, winrt::Windows::UI::Color color) {
    if (!target || !g_settings.showLayoutAnchors) return;
    try {
        Grid overlay;
        overlay.Name(name);
        overlay.IsHitTestVisible(false);
        overlay.HorizontalAlignment(HorizontalAlignment::Stretch);
        overlay.VerticalAlignment(VerticalAlignment::Stretch);
        winrt::Windows::UI::Xaml::Shapes::Rectangle vLine;
        vLine.Width(1);
        vLine.Fill(MakeBrush(color));
        vLine.HorizontalAlignment(HorizontalAlignment::Center);
        vLine.VerticalAlignment(VerticalAlignment::Stretch);
        winrt::Windows::UI::Xaml::Shapes::Rectangle hLine;
        hLine.Height(1);
        hLine.Fill(MakeBrush(color));
        hLine.HorizontalAlignment(HorizontalAlignment::Stretch);
        hLine.VerticalAlignment(VerticalAlignment::Center);
        Border outline;
        outline.BorderBrush(MakeBrush(color));
        outline.BorderThickness({1,1,1,1});
        outline.HorizontalAlignment(HorizontalAlignment::Stretch);
        outline.VerticalAlignment(VerticalAlignment::Stretch);
        overlay.Children().Append(outline);
        overlay.Children().Append(vLine);
        overlay.Children().Append(hLine);
        Canvas::SetZIndex(overlay, 5000);
        target.Children().Append(overlay);
    } catch (...) {}
}
static MenuFlyoutItem MakeActionContextMenuItem(const wchar_t* glyph, const wchar_t* label,
                                                std::function<void()> onClick) {
    MenuFlyoutItem item;
    item.Text(label);
    item.IsEnabled(true);
    try {
        FontIcon icon;
        icon.Glyph(glyph);
        icon.FontSize((double)g_settings.buttonIconSize);
        bool useFluent = (ContextMenuIconStyle() == L"fluent_outline" || ContextMenuIconStyle() == L"fluent_filled");
        try {
            icon.FontFamily(FontFamily(useFluent ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets"));
        } catch (...) {
            try {
                icon.FontFamily(FontFamily(L"Segoe MDL2 Assets"));
            } catch (...) {}
        }
        icon.Foreground(MakeBrush(ContextMenuIconColor()));
        icon.Opacity(1.0);
        item.Icon(icon);
    } catch (...) {}
    item.Click([onClick](winrt::Windows::Foundation::IInspectable const&, RoutedEventArgs const&) {
        if (g_unloading) return;
        try {
            onClick();
        } catch (...) {}
    });
    return item;
}
static void OpenWindhawk() {
    SpawnTrackedWorker([]() {
        wchar_t expanded[MAX_PATH]{};
        ExpandEnvironmentStringsW(L"%ProgramFiles%\\Windhawk\\windhawk.exe", expanded, MAX_PATH);
        DWORD attrs = GetFileAttributesW(expanded);
        if (attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY)) {
            ShellExecuteW(nullptr, L"open", expanded, nullptr, nullptr, SW_SHOWNORMAL);
        } else {
            ShellExecuteW(nullptr, L"open", L"windhawk.exe", nullptr, nullptr, SW_SHOWNORMAL);
        }
    });
}
static MenuFlyoutItem MakeMediaContextMenuItem(int cmd, const wchar_t* label, bool enabled, double iconOpacity) {
    MenuFlyoutItem item;
    item.Text(label);
    item.IsEnabled(enabled);
    try {
        FontIcon icon;
        icon.Glyph(GetGlyphWithStyle(cmd, ContextMenuIconStyle()));
        icon.FontSize((double)g_settings.buttonIconSize);
        bool useFluent = (ContextMenuIconStyle() == L"fluent_outline" || ContextMenuIconStyle() == L"fluent_filled");
        try {
            icon.FontFamily(FontFamily(useFluent ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets"));
        } catch (...) {
            try {
                icon.FontFamily(FontFamily(L"Segoe MDL2 Assets"));
            } catch (...) {}
        }
        icon.Foreground(MakeBrush(ContextMenuIconColor()));
        icon.Opacity(iconOpacity);
        item.Icon(icon);
    } catch (...) {}
    item.Click([cmd](winrt::Windows::Foundation::IInspectable const&, RoutedEventArgs const&) {
        if (g_unloading) return;
        try {
            SendMediaCommandAsync(cmd);
            DispatchMediaUpdate();
        } catch (...) {}
    });
    return item;
}
// Keep the popup menu above the topmost taskbar.
static LRESULT CALLBACK PlayerMenuHook(int code, WPARAM wp, LPARAM lp) {
    if (code >= 0) {
        auto msg = reinterpret_cast<CWPSTRUCT*>(lp);
        if (msg->message == WM_WINDOWPOSCHANGING) {
            wchar_t cls[32] = {};
            GetClassNameW(msg->hwnd, cls, ARRAYSIZE(cls));
            if (wcscmp(cls, L"#32768") == 0) {
                auto pos = reinterpret_cast<WINDOWPOS*>(msg->lParam);
                pos->hwndInsertAfter = HWND_TOPMOST;
                pos->flags &= ~SWP_NOZORDER;
            }
        }
    }
    return CallNextHookEx(nullptr, code, wp, lp);
}
// Shared by the player menu and the visualizer's device menu, so both get the
// same placement, owner and topmost handling (and the same system menu look).
static UINT TrackNativeMenu(HMENU menu, POINT pt) {
    TPMPARAMS placement{sizeof(placement)};
    HWND taskbar = g_taskbarWnd ? g_taskbarWnd : FindWindowW(L"Shell_TrayWnd", nullptr);
    if (taskbar) GetWindowRect(taskbar, &placement.rcExclude);
    // A throwaway owner window keeps focus games away from Shell_TrayWnd.
    HWND owner = CreateWindowExW(WS_EX_TOOLWINDOW, L"Static", L"", WS_POPUP, pt.x, pt.y, 0, 0,
                                 nullptr, nullptr, nullptr, nullptr);
    if (!owner) return 0;
    SetForegroundWindow(owner);
    HHOOK hook = SetWindowsHookExW(WH_CALLWNDPROC, PlayerMenuHook, nullptr, GetCurrentThreadId());
    UINT cmd = TrackPopupMenuEx(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON | TPM_VERTICAL, pt.x, pt.y, owner,
                                taskbar ? &placement : nullptr);
    if (hook) UnhookWindowsHookEx(hook);
    PostMessageW(owner, WM_NULL, 0, 0);
    DestroyWindow(owner);
    return cmd;
}
// Active audio endpoints of one direction, with the label the device menus show
// ('&' doubled so the menu does not read it as an accelerator).
static void ForEachActiveEndpoint(EDataFlow flow, const std::function<void(const std::wstring&, const std::wstring&)>& fn) {
    Microsoft::WRL::ComPtr<IMMDeviceEnumerator> enumerator;
    if (FAILED(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, IID_PPV_ARGS(&enumerator)))) return;
    Microsoft::WRL::ComPtr<IMMDeviceCollection> devices;
    UINT count = 0;
    if (SUCCEEDED(enumerator->EnumAudioEndpoints(flow, DEVICE_STATE_ACTIVE, &devices))) devices->GetCount(&count);
    for (UINT i = 0; i < count; ++i) {
        Microsoft::WRL::ComPtr<IMMDevice> device;
        LPWSTR id = nullptr;
        if (FAILED(devices->Item(i, &device)) || FAILED(device->GetId(&id))) continue;
        std::wstring idText = id, name = id;
        CoTaskMemFree(id);
        Microsoft::WRL::ComPtr<IPropertyStore> properties;
        PROPVARIANT value{};
        // PKEY_Device_DeviceDesc, the same label the visualizer showed before.
        static const PROPERTYKEY kFriendlyName{{0xa45c254e, 0xdf1c, 0x4efd, {0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0}}, 2};
        if (SUCCEEDED(device->OpenPropertyStore(STGM_READ, &properties)) &&
            SUCCEEDED(properties->GetValue(kFriendlyName, &value)) &&
            value.vt == VT_LPWSTR && value.pwszVal)
            name = value.pwszVal;
        PropVariantClear(&value);
        std::wstring label;
        for (wchar_t c : name) { label += c; if (c == L'&') label += c; }
        fn(idText, label);
    }
}
// Stores the visualizer's capture device and tells the tool process. Its picker
// window exists in every placement; overlay mode only keeps it hidden.
static void SetCaptureEndpoint(const std::wstring& id, HWND picker = nullptr) {
    if (!Wh_SetStringValue(L"captureEndpointId", id.c_str())) return;
    g_VizDeviceChanged.store(true, std::memory_order_relaxed);  // the overlay bars capture in this process
    if (!picker || !IsWindow(picker)) picker = FindWindowW(L"TaskbarAudioVisualizerCapturePicker", nullptr);
    if (picker) PostMessageW(picker, RegisterWindowMessageW(L"WindhawkFluentPlusCaptureChanged"), 0, 0);
    else Wh_Log(L"Capture device saved; the visualizer reads it when it next loads");
}
static void ShowNativeMediaMenu() {
    if (g_unloading) return;
    bool canSkipPrevious = true, canSkipNext = true, canShuffle = true, canRepeat = true, canSeek = true;
    {
        std::lock_guard<std::mutex> lk(g_mediaMtx);
        canSkipPrevious = g_media.canSkipPrevious;
        canSkipNext     = g_media.canSkipNext;
        canShuffle      = g_media.canShuffle;
        canRepeat       = g_media.canRepeat;
        canSeek         = g_media.canSeek;
    }
    bool shuffleOn = g_shuffleEnabled.load();
    RepeatMode repeat = g_repeatMode.load();
    std::vector<std::function<void()>> actions;
    HMENU menu = CreatePopupMenu();
    auto add = [&](HMENU m, const wchar_t* label, bool enabled, bool checked, std::function<void()> fn) {
        actions.push_back(std::move(fn));
        AppendMenuW(m, MF_STRING | (enabled ? 0 : MF_GRAYED) | (checked ? MF_CHECKED : 0),
                    (UINT_PTR)actions.size(), label);
    };
    auto media = [](int cmd) -> std::function<void()> {
        return [cmd] { SendMediaCommandAsync(cmd); DispatchMediaUpdate(); };
    };
    for (const auto& item : g_settings.contextMenuItems) {
        if (item == L"repeat") {
            if (g_settings.contextMenuRepeatStyle == L"toggle") {
                add(menu, repeat == RepeatMode::One ? L"Repeat one" : L"Repeat", canRepeat,
                    repeat != RepeatMode::Off, media(8));
            } else {
                HMENU sub = CreatePopupMenu();
                add(sub, L"Off", canRepeat, repeat == RepeatMode::Off, media(10));
                add(sub, L"All", canRepeat, repeat == RepeatMode::All, media(11));
                add(sub, L"One", canRepeat, repeat == RepeatMode::One, media(12));
                AppendMenuW(menu, MF_POPUP | (canRepeat ? 0 : MF_GRAYED), (UINT_PTR)sub, L"Repeat");
            }
        } else if (item == L"shuffle") {
            if (g_settings.contextMenuShuffleStyle == L"toggle") {
                add(menu, L"Shuffle", canShuffle, shuffleOn, media(7));
            } else {
                HMENU sub = CreatePopupMenu();
                add(sub, L"Off", canShuffle, !shuffleOn, [] { if (g_shuffleEnabled.load()) { SendMediaCommandAsync(7); DispatchMediaUpdate(); } });
                add(sub, L"On", canShuffle, shuffleOn, [] { if (!g_shuffleEnabled.load()) { SendMediaCommandAsync(7); DispatchMediaUpdate(); } });
                AppendMenuW(menu, MF_POPUP | (canShuffle ? 0 : MF_GRAYED), (UINT_PTR)sub, L"Shuffle");
            }
        } else if (item == L"forward") {
            add(menu, L"Forward 5 seconds", canSeek, false, media(6));
        } else if (item == L"rewind") {
            add(menu, L"Rewind 5 seconds", canSeek, false, media(5));
        } else if (item == L"next") {
            add(menu, L"Next track", canSkipNext, false, media(3));
        } else if (item == L"prev") {
            add(menu, L"Previous track", canSkipPrevious, false, media(1));
        } else if (item == L"switch_sessions") {
            add(menu, L"Switch session", g_sessionCount.load() > 1, false, media(9));
        } else if (item == L"open_app") {
            add(menu, L"Open media app", true, false, [] { ExecuteMediaAction(L"open_app"); });
        }
    }
    {
        // The visualizer's device choice lives here too: in overlay placement the
        // bars' own right-click picker never shows, so this is the only way in.
        wchar_t current[512] = {};
        Wh_GetStringValue(L"captureEndpointId", current, ARRAYSIZE(current));
        HMENU viz = CreatePopupMenu();
        add(viz, L"All devices (default)", true, current[0] == 0, [] { SetCaptureEndpoint(L""); });
        for (EDataFlow flow : {eCapture, eRender}) {
            HMENU sub = CreatePopupMenu();
            ForEachActiveEndpoint(flow, [&](const std::wstring& id, const std::wstring& label) {
                add(sub, label.c_str(), true, id == current, [id] { SetCaptureEndpoint(id); });
            });
            if (GetMenuItemCount(sub) == 0) AppendMenuW(sub, MF_STRING | MF_GRAYED, 0, L"No active devices");
            AppendMenuW(viz, MF_POPUP, reinterpret_cast<UINT_PTR>(sub), flow == eCapture ? L"Input device" : L"Output device");
        }
        if (GetMenuItemCount(menu) > 0) AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(menu, MF_POPUP, reinterpret_cast<UINT_PTR>(viz), L"Visualizer audio device");
    }
    if (g_settings.showRestartButton || g_settings.showOpenWindhawk)
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    if (g_settings.showRestartButton) {
        add(menu, L"Restart player", true, false, [] {
            StopVizTimer();
            g_vizCurrentlyVisible = false;
            RemovePlayerGrid();
            auto dispatcher = winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread().Dispatcher();
            dispatcher.RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [] {
                try { InjectPlayerGrid(); } catch (...) { Wh_Log(L"Restart player: InjectPlayerGrid failed"); }
            });
        });
    }
    if (g_settings.showOpenWindhawk) add(menu, L"Open Windhawk", true, false, [] { OpenWindhawk(); });
    if (GetMenuItemCount(menu) == 0) { DestroyMenu(menu); return; }

    POINT pt{};
    GetCursorPos(&pt);
    UINT cmd = TrackNativeMenu(menu, pt);
    DestroyMenu(menu);
    try { if (g_playerButtonStateUpdater) g_playerButtonStateUpdater(); } catch (...) {}
    if (cmd >= 1 && cmd <= actions.size() && !g_unloading) {
        try { actions[cmd - 1](); } catch (...) { Wh_Log(L"Player menu: action failed"); }
    }
}
static void ShowMediaContextMenu(FrameworkElement const& target) {
    if (!target || g_unloading) return;
    // Run the menu's modal loop after the pointer handler has returned.
    try {
        target.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Low,
                                     [] { ShowNativeMediaMenu(); });
    } catch (...) {
        Wh_Log(L"ShowMediaContextMenu: exception");
    }
}

// The visualizer's bars run in the tool process, which the system menu styling
// does not reach. It posts kShowCaptureMenuMsg to this hidden window instead, and
// the device menu opens here through TrackNativeMenu like the player menu.
static const wchar_t kMenuHostClass[] = L"WindhawkFluentPlusMenuHost";
static HWND g_menuHostWnd = nullptr;
static void ShowNativeCaptureMenu(HWND picker) {
    if (g_unloading) return;
    wchar_t current[512] = {};
    Wh_GetStringValue(L"captureEndpointId", current, ARRAYSIZE(current));
    std::vector<std::wstring> choices;
    HMENU menu = CreatePopupMenu(), inputs = CreatePopupMenu(), outputs = CreatePopupMenu();
    AppendMenuW(menu, MF_STRING | (current[0] ? 0 : MF_CHECKED), 1, L"All devices (default)");
    for (EDataFlow flow : {eCapture, eRender}) {
        HMENU sub = flow == eCapture ? inputs : outputs;
        ForEachActiveEndpoint(flow, [&](const std::wstring& id, const std::wstring& label) {
            choices.push_back(id);
            AppendMenuW(sub, MF_STRING | (id == current ? MF_CHECKED : 0), 100 + choices.size() - 1, label.c_str());
        });
        if (GetMenuItemCount(sub) == 0) AppendMenuW(sub, MF_STRING | MF_GRAYED, 0, L"No active devices");
    }
    AppendMenuW(menu, MF_POPUP, reinterpret_cast<UINT_PTR>(inputs), L"Input device");
    AppendMenuW(menu, MF_POPUP, reinterpret_cast<UINT_PTR>(outputs), L"Output device");
    POINT pt{};
    GetCursorPos(&pt);
    RECT bars{};
    if (GetWindowRect(picker, &bars) && !PtInRect(&bars, pt))
        pt = {(bars.left + bars.right) / 2, (bars.top + bars.bottom) / 2};
    UINT cmd = TrackNativeMenu(menu, pt);
    DestroyMenu(menu);
    if (g_unloading || !(cmd == 1 || (cmd >= 100 && cmd - 100 < choices.size()))) return;
    SetCaptureEndpoint(cmd == 1 ? L"" : choices[cmd - 100], picker);
}
static LRESULT CALLBACK MenuHostWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    static const UINT kShowCaptureMenuMsg = RegisterWindowMessageW(L"WindhawkFluentPlusShowCaptureMenu");
    if (msg == kShowCaptureMenuMsg) {
        ShowNativeCaptureMenu(reinterpret_cast<HWND>(wp));
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}
static HINSTANCE ThisModule() {
    HMODULE module = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<LPCWSTR>(&MenuHostWndProc), &module);
    return module;
}
// Runs on the taskbar thread, like the player menu.
static void EnsureMenuHost() {
    if (g_menuHostWnd || g_unloading) return;
    WNDCLASSW wc{};
    wc.lpfnWndProc = MenuHostWndProc;
    wc.hInstance = ThisModule();
    wc.lpszClassName = kMenuHostClass;
    RegisterClassW(&wc);
    g_menuHostWnd = CreateWindowExW(0, kMenuHostClass, L"", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, wc.hInstance, nullptr);
    if (g_menuHostWnd)
        ChangeWindowMessageFilterEx(g_menuHostWnd, RegisterWindowMessageW(L"WindhawkFluentPlusShowCaptureMenu"),
                                    MSGFLT_ALLOW, nullptr);
    else
        Wh_Log(L"EnsureMenuHost: CreateWindowExW failed (%u)", GetLastError());
}
static void DestroyMenuHost() {
    EndMenu();
    if (g_menuHostWnd) DestroyWindow(g_menuHostWnd);
    g_menuHostWnd = nullptr;
    UnregisterClassW(kMenuHostClass, ThisModule());
}

[[clang::no_destroy]] static winrt::Windows::UI::Xaml::Controls::Flyout g_miniPlayerFlyout{nullptr};
[[clang::no_destroy]] static Controls::Image g_miniPlayerArtRef{nullptr};
[[clang::no_destroy]] static TextBlock       g_miniPlayerTitleRef{nullptr};
[[clang::no_destroy]] static TextBlock       g_miniPlayerArtistRef{nullptr};
[[clang::no_destroy]] static Button          g_miniPlayerPlayBtnRef{nullptr};
[[clang::no_destroy]] static Button          g_miniPlayerPrevBtnRef{nullptr};
[[clang::no_destroy]] static Button          g_miniPlayerNextBtnRef{nullptr};
[[clang::no_destroy]] static Button          g_miniPlayerShuffleBtnRef{nullptr};
[[clang::no_destroy]] static Button          g_miniPlayerRepeatBtnRef{nullptr};
[[clang::no_destroy]] static StackPanel      g_miniPlayerSessionListRef{nullptr};
[[clang::no_destroy]] static Border          g_miniPlayerSessionListSepRef{nullptr};

struct MiniSessionInfo {
    std::wstring id;
    std::wstring title;
    std::wstring artist;
    std::vector<BYTE> thumbBytes;
};
static std::vector<MiniSessionInfo> g_miniSessionInfos;
static std::mutex                   g_miniSessionMtx;
static std::vector<BYTE> g_miniPlayerCachedThumb;
static std::vector<size_t> g_miniSessionCachedThumbSizes;
static std::atomic<int> g_miniSessionHoveredIndex{-1};

static void LoadMiniPlayerArtBitmap(Controls::Image const& img, std::vector<BYTE> const& thumbBytes) {
    if (!img || thumbBytes.empty()) return;
    try {
        IStream* pRawStream = SHCreateMemStream(
            thumbBytes.data(), static_cast<UINT>(thumbBytes.size()));
        if (!pRawStream) return;
        winrt::com_ptr<IStream> comStream;
        comStream.attach(pRawStream);
        winrt::Windows::Storage::Streams::IRandomAccessStream rasStream{nullptr};
        ::CreateRandomAccessStreamOverStream(
            comStream.get(), BSOS_DEFAULT,
            winrt::guid_of<winrt::Windows::Storage::Streams::IRandomAccessStream>(),
            winrt::put_abi(rasStream));
        if (!rasStream) return;
        BitmapImage bmp;
        img.Source(bmp);
        bmp.SetSourceAsync(rasStream);
        img.Visibility(Visibility::Visible);
    } catch (...) {}
}

static std::vector<std::shared_ptr<std::atomic<bool>>> g_miniSessionCurrentFlags;

static void RefreshMiniPlayerFlyoutUI() {
    if (!g_miniPlayerFlyoutOpen) return;
    std::wstring title, artist;
    bool isPlaying = false;
    bool hasMedia = false;
    bool canSkipPrevious = true, canSkipNext = true;
    bool canShuffle = true, canRepeat = true;
    std::vector<BYTE> thumbBytes;
    {
        std::lock_guard<std::mutex> lk(g_mediaMtx);
        title           = g_media.title;
        artist          = g_media.artist;
        isPlaying       = g_media.isPlaying;
        hasMedia        = g_media.hasMedia;
        canSkipPrevious = g_media.canSkipPrevious;
        canSkipNext     = g_media.canSkipNext;
        canShuffle      = g_media.canShuffle;
        canRepeat       = g_media.canRepeat;
        thumbBytes      = g_media.thumbnailBytes;
    }
    std::wstring currentId;
    {
        GlobalSystemMediaTransportControlsSession sessionCopy{nullptr};
        {
            std::lock_guard<std::mutex> lk(g_sessionMtx);
            sessionCopy = g_currentSession;
        }
        if (sessionCopy) {
            try { currentId = std::wstring(sessionCopy.SourceAppUserModelId()); } catch (...) {}
        }
    }
    
    try {
        if (g_miniPlayerTitleRef) {
            std::wstring displayTitle;
            if (!hasMedia) {
                displayTitle = g_settings.noMediaTitleText;
            } else if (title.empty()) {
                displayTitle = g_settings.emptyTitleText;
            } else {
                displayTitle = title;
            }
            g_miniPlayerTitleRef.Text(winrt::hstring(displayTitle));
        }
        if (g_miniPlayerArtistRef) {
            std::wstring trimmedArtist = artist;
            trimmedArtist.erase(0, trimmedArtist.find_first_not_of(L" \t\n\r"));
            trimmedArtist.erase(trimmedArtist.find_last_not_of(L" \t\n\r") + 1);
            bool isEmpty = trimmedArtist.empty();

            winrt::hstring newArtist = isEmpty ? winrt::hstring(L"") : winrt::hstring(artist);
            g_miniPlayerArtistRef.Text(newArtist);
            g_miniPlayerArtistRef.Visibility(isEmpty ? Visibility::Collapsed : Visibility::Visible);
        }

        if (g_miniPlayerPlayBtnRef) {
            g_miniPlayerPlayBtnRef.IsEnabled(hasMedia);
            g_miniPlayerPlayBtnRef.Opacity(hasMedia ? 1.0 : 0.35);
            if (auto icon = g_miniPlayerPlayBtnRef.Content().try_as<TextBlock>()) {
                const wchar_t* glyph = isPlaying ? L"\uE62E" : L"\uF5B0";
                icon.Text(winrt::hstring(glyph));
            }
        }

        if (g_miniPlayerPrevBtnRef) {
            bool enabled = hasMedia && canSkipPrevious;
            g_miniPlayerPrevBtnRef.IsEnabled(enabled);
            g_miniPlayerPrevBtnRef.Opacity(enabled ? 1.0 : 0.35);
        }

        if (g_miniPlayerNextBtnRef) {
            bool enabled = hasMedia && canSkipNext;
            g_miniPlayerNextBtnRef.IsEnabled(enabled);
            g_miniPlayerNextBtnRef.Opacity(enabled ? 1.0 : 0.35);
        }

        if (g_miniPlayerShuffleBtnRef) {
            bool enabled = hasMedia && canShuffle;
            g_miniPlayerShuffleBtnRef.IsEnabled(enabled);
            if (auto icon = g_miniPlayerShuffleBtnRef.Content().try_as<TextBlock>()) {
                icon.Opacity(enabled && g_shuffleEnabled.load() ? 1.0 : 0.40);
            }
        }

        if (g_miniPlayerRepeatBtnRef) {
            bool enabled = hasMedia && canRepeat;
            g_miniPlayerRepeatBtnRef.IsEnabled(enabled);
            if (auto icon = g_miniPlayerRepeatBtnRef.Content().try_as<TextBlock>()) {
                RepeatMode mode = g_repeatMode.load();
                icon.Text(mode == RepeatMode::One ? L"\uE8ED" :
                          mode == RepeatMode::All ? L"\uE8EE" : L"\uF5E7");
                icon.Opacity(enabled && mode != RepeatMode::Off ? 1.0 : 0.40);
            }
        }

        if (g_miniPlayerArtRef) {
            bool sameThumb = (!thumbBytes.empty() && thumbBytes == g_miniPlayerCachedThumb);
            if (!thumbBytes.empty() && !sameThumb) {
                LoadMiniPlayerArtBitmap(g_miniPlayerArtRef, thumbBytes);
                g_miniPlayerCachedThumb = thumbBytes;
            } else if (thumbBytes.empty()) {
                try { g_miniPlayerArtRef.Source(nullptr); } catch (...) {}
                g_miniPlayerArtRef.Visibility(Visibility::Collapsed);
                g_miniPlayerCachedThumb.clear();
            }
        }
        {
            std::vector<MiniSessionInfo> infos;
            {
                std::lock_guard<std::mutex> lk(g_miniSessionMtx);
                infos = g_miniSessionInfos;
            }

            bool noMusic = (!hasMedia || title.empty()) && infos.empty();
            bool hasOtherSessions = !infos.empty();
            if (g_miniPlayerSessionListSepRef) {
                g_miniPlayerSessionListSepRef.Visibility(
                    (noMusic || !hasOtherSessions || g_settings.hideMediaSessionsList) ? Visibility::Collapsed : Visibility::Visible);
            }

            if (g_miniPlayerSessionListRef) {
                auto sessionList = g_miniPlayerSessionListRef;
                Visibility listVisibility = (noMusic || !hasOtherSessions) ? Visibility::Collapsed : Visibility::Visible;
                sessionList.Visibility(listVisibility);

                uint32_t childCount = sessionList.Children().Size();
                if (infos.empty() || childCount != infos.size()) {
                    sessionList.Children().Clear();
                    {
                        std::lock_guard<std::mutex> lk(g_miniSessionMtx);
                        g_miniSessionCurrentFlags.clear();
                    }
                    g_miniSessionCachedThumbSizes.clear();
                    g_miniSessionCachedThumbSizes.resize(infos.size(), SIZE_MAX);
                HWND tw = g_taskbarWnd;
                for (size_t i = 0; i < infos.size(); ++i) {
                    bool isCurrent = (infos[i].id == currentId);
                    auto rowBtn = BuildSessionRowButton(infos[i], isCurrent, tw, static_cast<int>(i));
                    sessionList.Children().Append(rowBtn);
                    g_miniSessionCachedThumbSizes[i] = infos[i].thumbBytes.size();
                }
            } else {
                bool isLight = IsSystemLightTheme();
                int hoveredIdx = g_miniSessionHoveredIndex.load();
                
                for (uint32_t i = 0; i < childCount && i < infos.size(); ++i) {
                    bool isCurrent = (infos[i].id == currentId);
                    bool wasCurrent = isCurrent;
                    if (i < g_miniSessionCurrentFlags.size() && g_miniSessionCurrentFlags[i]) {
                        wasCurrent = g_miniSessionCurrentFlags[i]->load();
                        g_miniSessionCurrentFlags[i]->store(isCurrent);
                    }
                    if (auto btn = sessionList.Children().GetAt(i).try_as<Button>()) {
                        if (auto hb = btn.Content().try_as<Border>()) {
                            if (hoveredIdx != static_cast<int>(i)) {
                                hb.Background(MakeBrush(isCurrent
                                    ? (isLight ? winrt::Windows::UI::Color{0x20, 0x00, 0x00, 0x00}
                                               : winrt::Windows::UI::Color{0x2C, 0xFF, 0xFF, 0xFF})
                                    : winrt::Windows::UI::Color{0x00, 0x00, 0x00, 0x00}));
                            }
                            if (auto grid = hb.Child().try_as<Grid>()) {
                                for (uint32_t j = 0; j < grid.Children().Size(); ++j) {
                                    auto child = grid.Children().GetAt(j);
                                    if (auto pillRect = child.try_as<winrt::Windows::UI::Xaml::Shapes::Rectangle>()) {
                                        if (wasCurrent != isCurrent) {
                                            AnimateSessionPill(pillRect, isCurrent, /*animate*/ true);
                                        }
                                        continue;
                                    }
                                    if (auto artBdr = child.try_as<Border>()) {
                                        size_t newSize = infos[i].thumbBytes.size();
                                        size_t cachedSize = (i < g_miniSessionCachedThumbSizes.size())
                                            ? g_miniSessionCachedThumbSizes[i] : SIZE_MAX;
                                        if (newSize != cachedSize) {
                                            if (i < g_miniSessionCachedThumbSizes.size())
                                                g_miniSessionCachedThumbSizes[i] = newSize;
                                            if (!infos[i].thumbBytes.empty()) {
                                                try {
                                                    IStream* ps = SHCreateMemStream(
                                                        infos[i].thumbBytes.data(),
                                                        (UINT)infos[i].thumbBytes.size());
                                                    if (ps) {
                                                        winrt::com_ptr<IStream> cs; cs.attach(ps);
                                                        winrt::Windows::Storage::Streams::IRandomAccessStream rs{nullptr};
                                                        ::CreateRandomAccessStreamOverStream(
                                                            cs.get(), BSOS_DEFAULT,
                                                            winrt::guid_of<winrt::Windows::Storage::Streams::IRandomAccessStream>(),
                                                            winrt::put_abi(rs));
                                                        if (rs) {
                                                            Controls::Image rowImg;
                                                            rowImg.Width(32);
                                                            rowImg.Height(32);
                                                            rowImg.Stretch(Stretch::Uniform);
                                                            BitmapImage bmp;
                                                            bmp.DecodePixelHeight(32);
                                                            rowImg.Source(bmp);
                                                            bmp.SetSourceAsync(rs);
                                                            artBdr.Child(rowImg);
                                                        }
                                                    }
                                                } catch (...) {}
                                            } else {
                                                try { artBdr.Child(nullptr); } catch (...) {}
                                            }
                                        }
                                        continue;
                                    }
                                    if (auto sp = child.try_as<StackPanel>()) {
                                        std::wstring disp = infos[i].title.empty() ? infos[i].id : infos[i].title;
                                        if (sp.Children().Size() > 0) {
                                            if (auto tb = sp.Children().GetAt(0).try_as<TextBlock>()) {
                                                tb.Text(winrt::hstring(disp));
                                            }
                                        }
                                        if (sp.Children().Size() > 1) {
                                            if (auto tb = sp.Children().GetAt(1).try_as<TextBlock>()) {
                                                tb.Text(winrt::hstring(infos[i].artist));
                                                tb.Visibility(infos[i].artist.empty()
                                                    ? Visibility::Collapsed
                                                    : Visibility::Visible);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            }
        }
    } catch (...) {}
}

static void AnimateSessionPill(winrt::Windows::UI::Xaml::Shapes::Rectangle const& pill, bool isCurrent, bool animate) {
    using namespace winrt::Windows::UI::Xaml::Media;
    using namespace winrt::Windows::UI::Xaml::Media::Animation;

    if (isCurrent) {
        try {
            auto uiSettings = winrt::Windows::UI::ViewManagement::UISettings();
            auto accentColor = uiSettings.GetColorValue(
                winrt::Windows::UI::ViewManagement::UIColorType::Accent);
            BYTE r = std::min(255, (int)accentColor.R + 60);
            BYTE g = std::min(255, (int)accentColor.G + 60);
            BYTE b = std::min(255, (int)accentColor.B + 60);
            
            pill.Fill(MakeBrush({0xFF, r, g, b}));
        } catch (...) {
            pill.Fill(MakeBrush({0xFF, 0x40, 0xA0, 0xFF}));
        }
    }

    auto st = pill.RenderTransform().try_as<ScaleTransform>();
    if (!st) {
        st = ScaleTransform();
        pill.RenderTransformOrigin({0.5, 0.5});
        pill.RenderTransform(st);
    }

    if (!animate) {
        pill.Opacity(isCurrent ? 1.0 : 0.0);
        st.ScaleX(1.0);
        st.ScaleY(isCurrent ? 1.0 : 0.0);
        return;
    }

    if (isCurrent) {
        pill.Opacity(0.0);
        st.ScaleX(1.0);
        st.ScaleY(0.0);

        try {
            Storyboard sb;

            DoubleAnimation fadeAnim;
            fadeAnim.From(0.0);
            fadeAnim.To(1.0);
            fadeAnim.Duration(DurationHelper::FromTimeSpan(std::chrono::milliseconds(100)));
            Storyboard::SetTarget(fadeAnim, pill);
            Storyboard::SetTargetProperty(fadeAnim, L"Opacity");
            sb.Children().Append(fadeAnim);
            DoubleAnimation scaleAnim;
            scaleAnim.From(0.0);
            scaleAnim.To(1.0);
            scaleAnim.Duration(DurationHelper::FromTimeSpan(std::chrono::milliseconds(350)));
            auto ease = BackEase();
            ease.EasingMode(EasingMode::EaseOut);
            ease.Amplitude(0.6);
            scaleAnim.EasingFunction(ease);
            Storyboard::SetTarget(scaleAnim, pill);
            Storyboard::SetTargetProperty(scaleAnim,
                L"(UIElement.RenderTransform).(ScaleTransform.ScaleY)");
            sb.Children().Append(scaleAnim);

            sb.Begin();
        } catch (...) {
            pill.Opacity(1.0);
            st.ScaleX(1.0);
            st.ScaleY(1.0);
        }
    } else {
        try {
            Storyboard sb;

            DoubleAnimation scaleAnim;
            scaleAnim.To(0.0);
            scaleAnim.Duration(DurationHelper::FromTimeSpan(std::chrono::milliseconds(150)));
            auto ease = CircleEase();
            ease.EasingMode(EasingMode::EaseIn);
            scaleAnim.EasingFunction(ease);
            Storyboard::SetTarget(scaleAnim, pill);
            Storyboard::SetTargetProperty(scaleAnim,
                L"(UIElement.RenderTransform).(ScaleTransform.ScaleY)");
            sb.Children().Append(scaleAnim);

            DoubleAnimation fadeAnim;
            fadeAnim.To(0.0);
            fadeAnim.BeginTime(winrt::Windows::Foundation::TimeSpan(std::chrono::milliseconds(100)));
            fadeAnim.Duration(DurationHelper::FromTimeSpan(std::chrono::milliseconds(80)));
            Storyboard::SetTarget(fadeAnim, pill);
            Storyboard::SetTargetProperty(fadeAnim, L"Opacity");
            sb.Children().Append(fadeAnim);

            sb.Begin();
        } catch (...) {
            pill.Opacity(0.0);
            st.ScaleX(1.0);
            st.ScaleY(0.0);
        }
    }
}

static Button BuildSessionRowButton(const MiniSessionInfo& info, bool isCurrent, HWND taskbarWnd, int rowIndex) {
    bool isLight = IsSystemLightTheme();

    winrt::Windows::UI::Color bgSelected    = isLight
        ? winrt::Windows::UI::Color{0x20, 0x00, 0x00, 0x00}
        : winrt::Windows::UI::Color{0x2C, 0xFF, 0xFF, 0xFF};
    winrt::Windows::UI::Color bgUnselected  = winrt::Windows::UI::Color{0x00, 0x00, 0x00, 0x00};
    winrt::Windows::UI::Color bgNormal = isCurrent ? bgSelected : bgUnselected;

    winrt::Windows::UI::Color bgHover = isLight 
        ? winrt::Windows::UI::Color{0x0E, 0x00, 0x00, 0x00}
        : winrt::Windows::UI::Color{0x14, 0xFF, 0xFF, 0xFF};
    winrt::Windows::UI::Color bgPressed = isLight 
        ? winrt::Windows::UI::Color{0x18, 0x00, 0x00, 0x00}
        : winrt::Windows::UI::Color{0x20, 0xFF, 0xFF, 0xFF};

    auto isCurrentFlag = std::make_shared<std::atomic<bool>>(isCurrent);
    {
        std::lock_guard<std::mutex> lk(g_miniSessionMtx);
        if (static_cast<size_t>(rowIndex) >= g_miniSessionCurrentFlags.size()) {
            g_miniSessionCurrentFlags.resize(rowIndex + 1);
        }
        g_miniSessionCurrentFlags[rowIndex] = isCurrentFlag;
    }

    Border hoverBorder;
    hoverBorder.CornerRadius({4, 4, 4, 4});
    hoverBorder.Background(MakeBrush(bgNormal));
    hoverBorder.Height(48);
    hoverBorder.HorizontalAlignment(HorizontalAlignment::Stretch);
    hoverBorder.Padding({0, 0, 12, 0});
    try {
        BrushTransition bt;
        bt.Duration(std::chrono::milliseconds(83));
        hoverBorder.BackgroundTransition(bt);
    } catch (...) {}

    Grid rowGrid;
    rowGrid.Height(48);
    rowGrid.HorizontalAlignment(HorizontalAlignment::Stretch);
    ColumnDefinition cPill, c0, c1;
    cPill.Width({8, GridUnitType::Pixel});
    c0.Width({34, GridUnitType::Pixel});
    c1.Width({1,  GridUnitType::Star});
    rowGrid.ColumnDefinitions().Append(cPill);
    rowGrid.ColumnDefinitions().Append(c0);
    rowGrid.ColumnDefinitions().Append(c1);

    {
        winrt::Windows::UI::Xaml::Shapes::Rectangle pill;
        pill.Width(3);
        pill.Height(20);
        pill.RadiusX(1.5);
        pill.RadiusY(1.5);
        pill.Margin({0, 0, 0, 0});
        pill.VerticalAlignment(VerticalAlignment::Center);
        pill.HorizontalAlignment(HorizontalAlignment::Left);

        AnimateSessionPill(pill, isCurrent, /*animate*/ false);
        if (isCurrent) {
            pill.Loaded([pill](auto const&, auto const&) {
                AnimateSessionPill(pill, true, /*animate*/ true);
            });
        }

        Grid::SetColumn(pill, 0);
        rowGrid.Children().Append(pill);
    }

    Border rowArt;
    rowArt.Width(32); rowArt.Height(32);
    rowArt.CornerRadius({4, 4, 4, 4});
    rowArt.Margin({2, 0, 0, 0});
    rowArt.Background(MakeBrush({0x40, 0x80, 0x80, 0x80}));
    rowArt.VerticalAlignment(VerticalAlignment::Center);
    if (!info.thumbBytes.empty()) {
        try {
            IStream* ps = SHCreateMemStream(info.thumbBytes.data(), (UINT)info.thumbBytes.size());
            if (ps) {
                winrt::com_ptr<IStream> cs; cs.attach(ps);
                winrt::Windows::Storage::Streams::IRandomAccessStream rs{nullptr};
                ::CreateRandomAccessStreamOverStream(cs.get(), BSOS_DEFAULT,
                    winrt::guid_of<winrt::Windows::Storage::Streams::IRandomAccessStream>(),
                    winrt::put_abi(rs));
                if (rs) {
                    Controls::Image rowImg;
                    rowImg.Stretch(Stretch::None);
                    rowImg.HorizontalAlignment(HorizontalAlignment::Center);
                    rowImg.VerticalAlignment(VerticalAlignment::Center);
                    BitmapImage bmp;
                    bmp.DecodePixelHeight(32);
                    rowImg.Source(bmp);
                    bmp.SetSourceAsync(rs);
                    rowArt.Child(rowImg);
                }
            }
        } catch (...) {}
    }
    Grid::SetColumn(rowArt, 1);
    rowGrid.Children().Append(rowArt);

    StackPanel rowText;
    rowText.Orientation(Orientation::Vertical);
    rowText.VerticalAlignment(VerticalAlignment::Center);
    rowText.HorizontalAlignment(HorizontalAlignment::Left);
    rowText.Margin({8, 0, 0, 0});
    rowText.MaxWidth(240);

    std::wstring displayTitle = info.title.empty() ? info.id : info.title;
    TextBlock rowTitle;
    rowTitle.Text(winrt::hstring(displayTitle));
    rowTitle.FontSize(12);
    rowTitle.FontWeight(winrt::Windows::UI::Text::FontWeights::SemiBold());
    rowTitle.TextTrimming(TextTrimming::CharacterEllipsis);
    rowTitle.TextWrapping(TextWrapping::NoWrap);
    rowTitle.HorizontalAlignment(HorizontalAlignment::Left);
    rowTitle.TextAlignment(TextAlignment::Left);
    rowTitle.Foreground(MakeBrush(isLight
        ? winrt::Windows::UI::Color{0xFF, 0x10, 0x10, 0x10}
        : winrt::Windows::UI::Color{0xFF, 0xFF, 0xFF, 0xFF}));
    rowText.Children().Append(rowTitle);

    if (!info.artist.empty()) {
        TextBlock rowArtist;
        rowArtist.Text(winrt::hstring(info.artist));
        rowArtist.FontSize(10.5);
        rowArtist.Opacity(0.65);
        rowArtist.TextTrimming(TextTrimming::CharacterEllipsis);
        rowArtist.TextWrapping(TextWrapping::NoWrap);
        rowArtist.HorizontalAlignment(HorizontalAlignment::Left);
        rowArtist.TextAlignment(TextAlignment::Left);
        rowArtist.Margin({0, 2, 0, 0});
        rowArtist.Foreground(MakeBrush(isLight
            ? winrt::Windows::UI::Color{0xFF, 0x50, 0x50, 0x50}
            : winrt::Windows::UI::Color{0xFF, 0xFF, 0xFF, 0xFF}));
        rowText.Children().Append(rowArtist);
    }

    if (g_settings.showMiniPlayerBorder) {
        rowArt.BorderBrush(MakeBrush({0xFF, 0xFF, 0x40, 0x00}));
        rowArt.BorderThickness({1, 1, 1, 1});
        rowText.BorderBrush(MakeBrush({0xFF, 0x00, 0xFF, 0xFF}));
        rowText.BorderThickness({1, 1, 1, 1});
        hoverBorder.BorderBrush(MakeBrush({0xFF, 0xFF, 0x00, 0xFF}));
        hoverBorder.BorderThickness({1, 1, 1, 1});
    }

    Grid::SetColumn(rowText, 2);
    rowGrid.Children().Append(rowText);
    hoverBorder.Child(rowGrid);

    Button rowBtn;
    rowBtn.HorizontalAlignment(HorizontalAlignment::Stretch);
    rowBtn.HorizontalContentAlignment(HorizontalAlignment::Stretch);
    rowBtn.Padding({0, 0, 0, 0});
    rowBtn.Margin({4, 2, 4, 2});
    rowBtn.CornerRadius({4, 4, 4, 4});
    rowBtn.BorderThickness({0, 0, 0, 0});
    rowBtn.Background(MakeBrush({0x00, 0x00, 0x00, 0x00}));
    rowBtn.Content(hoverBorder);

    std::wstring capturedId = info.id;
    rowBtn.Click([capturedId](auto const&, auto const&) {
        if (g_unloading) return;
        SpawnTrackedWorker([capturedId]() {
            winrt::init_apartment(winrt::apartment_type::multi_threaded);
            GlobalSystemMediaTransportControlsSession targetSession{nullptr};
            {
                GlobalSystemMediaTransportControlsSessionManager mgr{nullptr};
                {
                    std::lock_guard<std::mutex> lk(g_sessionMtx);
                    mgr = g_sessionMgr;
                }
                if (mgr) {
                    try {
                        auto sessions = mgr.GetSessions();
                        for (auto const& s : sessions) {
                            try {
                                if (std::wstring(s.SourceAppUserModelId()) == capturedId) {
                                    targetSession = s;
                                    std::lock_guard<std::mutex> lk(g_sessionMtx);
                                    g_userSwitchedSession = true;
                                    break;
                                }
                            } catch (...) {}
                        }
                    } catch (...) {}
                }
            }
            if (targetSession) {
                AttachToSession(targetSession);
            }
            winrt::uninit_apartment();
        });
    });

    ApplyFluentMediaButtonStyle(rowBtn);

    auto hBorderWeak  = winrt::make_weak(hoverBorder);
    auto brushSelected   = MakeBrush(bgSelected);
    auto brushUnselected = MakeBrush(bgUnselected);
    auto brushHover       = MakeBrush(bgHover);
    auto brushPressed     = MakeBrush(bgPressed);
    auto restingBrush = [isCurrentFlag, brushSelected, brushUnselected]() {
        return isCurrentFlag->load() ? brushSelected : brushUnselected;
    };

    rowBtn.PointerEntered([hBorderWeak, brushHover, rowIndex](auto const&, auto const&) {
        g_miniSessionHoveredIndex.store(rowIndex);
        if (auto b = hBorderWeak.get()) b.Background(brushHover);
    });
    rowBtn.PointerExited([hBorderWeak, restingBrush, rowIndex](auto const&, auto const&) {
        int expected = rowIndex;
        g_miniSessionHoveredIndex.compare_exchange_strong(expected, -1);
        if (auto b = hBorderWeak.get()) b.Background(restingBrush());
    });
    rowBtn.AddHandler(UIElement::PointerPressedEvent(), winrt::box_value(
        winrt::Windows::UI::Xaml::Input::PointerEventHandler(
        [hBorderWeak, brushPressed](auto const& sender,
        winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
        if (auto elem = sender.template try_as<UIElement>()) elem.CapturePointer(e.Pointer());
        if (auto b = hBorderWeak.get()) b.Background(brushPressed);
    })), true);
    rowBtn.AddHandler(UIElement::PointerReleasedEvent(), winrt::box_value(
        winrt::Windows::UI::Xaml::Input::PointerEventHandler(
        [hBorderWeak, brushHover](auto const& sender,
        winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
        if (auto elem = sender.template try_as<UIElement>()) elem.ReleasePointerCapture(e.Pointer());
        if (auto b = hBorderWeak.get()) b.Background(brushHover);
    })), true);
    rowBtn.PointerCanceled([hBorderWeak, restingBrush, rowIndex](auto const&, auto const&) {
        int expected = rowIndex;
        g_miniSessionHoveredIndex.compare_exchange_strong(expected, -1);
        if (auto b = hBorderWeak.get()) b.Background(restingBrush());
    });
    rowBtn.PointerCaptureLost([hBorderWeak, restingBrush, rowIndex](auto const&, auto const&) {
        int expected = rowIndex;
        g_miniSessionHoveredIndex.compare_exchange_strong(expected, -1);
        if (auto b = hBorderWeak.get()) b.Background(restingBrush());
    });

    return rowBtn;
}

static void FetchMiniSessionInfosAsync(HWND taskbarWnd) {
    SpawnTrackedWorker([taskbarWnd]() {
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
        std::vector<MiniSessionInfo> infos;
        GlobalSystemMediaTransportControlsSessionManager mgr{nullptr};
        {
            std::lock_guard<std::mutex> lk(g_sessionMtx);
            mgr = g_sessionMgr;
        }
        if (!mgr) { winrt::uninit_apartment(); return; }
        {
            try {
                auto sessions = mgr.GetSessions();
                for (auto const& s : sessions) {
                    try {
                        std::wstring sid = std::wstring(s.SourceAppUserModelId());
                        if (IsIgnoredMediaApp(sid)) continue;
                        MiniSessionInfo info;
                        info.id = sid;
                        try {
                            auto props = s.TryGetMediaPropertiesAsync().get();
                            if (props) {
                                info.title  = std::wstring(props.Title());
                                info.artist = std::wstring(props.Artist());
                                if (auto thumbRef = props.Thumbnail()) {
                                    try {
                                        auto stream = thumbRef.OpenReadAsync().get();
                                        if (stream) {
                                            UINT64 sz = stream.Size();
                                            if (sz > 0 && sz < 2 * 1024 * 1024) {
                                                DataReader reader(stream);
                                                reader.LoadAsync((UINT32)sz).get();
                                                info.thumbBytes.resize((size_t)sz);
                                                reader.ReadBytes(winrt::array_view<BYTE>(info.thumbBytes));
                                                reader.DetachStream();
                                            }
                                        }
                                    } catch (...) { info.thumbBytes.clear(); }
                                }
                            }
                        } catch (...) {}
                        if (info.title.empty() && info.artist.empty()) continue;
                        infos.push_back(std::move(info));
                    } catch (...) {}
                }
            } catch (...) {}
        }
        {
            std::lock_guard<std::mutex> lk(g_miniSessionMtx);
            g_miniSessionInfos = std::move(infos);
        }
        winrt::uninit_apartment();

        if (taskbarWnd) {
            RunFromWindowThread(taskbarWnd, [](void*) {
                if (!g_miniPlayerFlyoutOpen) return;
                RefreshMiniPlayerFlyoutUI();
            }, nullptr);
        }
    });
}

static Grid BuildMiniPlayerFlyoutContent() {
    Grid outer;
    outer.MinWidth(360);
    outer.MaxWidth(360);
    outer.MinHeight(400);

    bool isPlaying = false;
    bool hasMedia = false;
    bool canSkipPrevious = true, canSkipNext = true;
    bool canShuffle = true, canRepeat = true;
    std::wstring title, artist;
    std::vector<BYTE> thumbBytes;
    {
        std::lock_guard<std::mutex> lk(g_mediaMtx);
        isPlaying       = g_media.isPlaying;
        hasMedia        = g_media.hasMedia;
        canSkipPrevious = g_media.canSkipPrevious;
        canSkipNext     = g_media.canSkipNext;
        canShuffle      = g_media.canShuffle;
        canRepeat       = g_media.canRepeat;
        title           = g_media.title;
        artist          = g_media.artist;
        thumbBytes      = g_media.thumbnailBytes;
    }

    Border bg;
    bg.CornerRadius({6, 6, 6, 6});
    bg.Padding({16, 16, 16, 0});
    bg.Margin({13, 13, 13, 13});

    bool isLight = IsSystemLightTheme();

    if (g_settings.showMiniPlayerBorder) {
        bg.BorderThickness({2, 2, 2, 2});
        bg.BorderBrush(MakeBrush(isLight
            ? winrt::Windows::UI::Color{0xFF, 0x00, 0x00, 0x00}
            : winrt::Windows::UI::Color{0xFF, 0xFF, 0xFF, 0xFF}));
    } else {
        bg.BorderThickness({1, 1, 1, 1});
        bg.BorderBrush(MakeBrush(isLight
            ? winrt::Windows::UI::Color{0x30, 0x00, 0x00, 0x00}
            : winrt::Windows::UI::Color{0x30, 0xFF, 0xFF, 0xFF}));
    }

    try {
        using namespace winrt::Windows::UI::Xaml::Media;
        ThemeShadow shadow;
        bg.Shadow(shadow);
        bg.Translation({0.f, 0.f, 32.f});
    } catch (...) {

    }

    Brush flyoutContentBackground{nullptr};
    try {
        winrt::Windows::UI::Xaml::Media::AcrylicBrush acrylic;
        acrylic.BackgroundSource(winrt::Windows::UI::Xaml::Media::AcrylicBackgroundSource::Backdrop);
        
        winrt::Windows::UI::Color tint = isLight
            ? winrt::Windows::UI::Color{0xff, 0xf2, 0xf2, 0xf2}
            : winrt::Windows::UI::Color{0xFF, 0x24, 0x24, 0x24};
        
        acrylic.TintColor(tint);
        acrylic.TintOpacity(isLight ? 0.0 : 0.5);
        acrylic.TintLuminosityOpacity(isLight ? 0.9 : 0.96);
        winrt::Windows::UI::Color fallback = isLight
            ? winrt::Windows::UI::Color{0xff, 0xf2, 0xf2, 0xf2}
            : winrt::Windows::UI::Color{0xFF, 0x24, 0x24, 0x24};
        acrylic.FallbackColor(fallback);
        
        flyoutContentBackground = acrylic;
    } catch (...) {
        flyoutContentBackground = MakeBrush(isLight
            ? winrt::Windows::UI::Color{0xf5, 0xf2, 0xf2, 0xf2}
            : winrt::Windows::UI::Color{0xF5, 0x24, 0x24, 0x24});
    }
    bg.Background(nullptr);

    StackPanel content;
    content.Orientation(Orientation::Vertical);
    content.HorizontalAlignment(HorizontalAlignment::Stretch);

    auto wrapDebugBorder = [](FrameworkElement const& elem, winrt::Windows::UI::Color color) -> FrameworkElement {
        if (!g_settings.showMiniPlayerBorder) return elem;
        Grid wrapper;
        wrapper.Children().Append(elem);
        Border dbg;
        dbg.BorderBrush(MakeBrush(color));
        dbg.BorderThickness({1, 1, 1, 1});
        dbg.IsHitTestVisible(false);
        wrapper.Children().Append(dbg);
        return wrapper;
    };

    Border artBorder;
    artBorder.MaxWidth(300);
    artBorder.MinWidth(170);
    artBorder.Height(169);
    artBorder.HorizontalAlignment(HorizontalAlignment::Center);
    artBorder.CornerRadius({6, 6, 6, 6});
    artBorder.Background(MakeBrush({0x40, 0x80, 0x80, 0x80}));
    artBorder.Margin({0, 0, 0, 10});
    {
        bool isLight = IsSystemLightTheme();
        artBorder.BorderThickness(g_settings.showMiniPlayerBorder ? Thickness{2, 2, 2, 2} : Thickness{1, 1, 1, 1});
        if (g_settings.showMiniPlayerBorder) {
            artBorder.BorderBrush(MakeBrush({0xFF, 0xFF, 0x00, 0x00}));
        } else {
            artBorder.BorderBrush(MakeBrush(isLight
                ? winrt::Windows::UI::Color{0x30, 0x00, 0x00, 0x00}
                : winrt::Windows::UI::Color{0x30, 0xFF, 0xFF, 0xFF}));
        }
    }

    Grid artInnerGrid;
    artInnerGrid.HorizontalAlignment(HorizontalAlignment::Stretch);
    artInnerGrid.VerticalAlignment(VerticalAlignment::Stretch);
    {
        auto clipGeo = winrt::Windows::UI::Xaml::Media::RectangleGeometry();
        artInnerGrid.SizeChanged([clipGeo](
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Windows::UI::Xaml::SizeChangedEventArgs const&) mutable {
                try {
                    if (auto fe = sender.try_as<FrameworkElement>()) {
                        clipGeo.Rect({0.f, 0.f,
                            (float)fe.ActualWidth(),
                            (float)fe.ActualHeight()});
                    }
                } catch (...) {}
            });
        artInnerGrid.Clip(clipGeo);
    }

    Controls::Image artImage;
    artImage.Stretch(Stretch::Uniform );
    artImage.HorizontalAlignment(HorizontalAlignment::Center);
    artImage.VerticalAlignment(VerticalAlignment::Center);
    artImage.Visibility(Visibility::Collapsed);
    if (!thumbBytes.empty()) {
        LoadMiniPlayerArtBitmap(artImage, thumbBytes);
        g_miniPlayerCachedThumb = thumbBytes;
    }
    artInnerGrid.Children().Append(artImage);
    artBorder.Child(artInnerGrid);
    content.Children().Append(artBorder);

    TextBlock titleBlock;
    titleBlock.FontSize(16);
    titleBlock.FontWeight(winrt::Windows::UI::Text::FontWeights::SemiBold());
    titleBlock.TextTrimming(TextTrimming::CharacterEllipsis);
    titleBlock.TextWrapping(TextWrapping::NoWrap);
    titleBlock.HorizontalAlignment(HorizontalAlignment::Center);
    titleBlock.TextAlignment(TextAlignment::Center);
    titleBlock.Foreground(MakeBrush(TextColor()));
    titleBlock.Margin({0, 0, 0, 4});
    {
        std::wstring displayTitle;
        if (!hasMedia) {
            displayTitle = g_settings.noMediaTitleText;
        } else if (title.empty()) {
            displayTitle = g_settings.emptyTitleText;
        } else {
            displayTitle = title;
        }
        titleBlock.Text(winrt::hstring(displayTitle));
    }
    content.Children().Append(wrapDebugBorder(titleBlock, {0xFF, 0xFF, 0xFF, 0x00}));

    TextBlock artistBlock;
    artistBlock.FontSize(13);
    artistBlock.TextTrimming(TextTrimming::CharacterEllipsis);
    artistBlock.TextWrapping(TextWrapping::NoWrap);
    artistBlock.HorizontalAlignment(HorizontalAlignment::Center);
    artistBlock.TextAlignment(TextAlignment::Center);
    artistBlock.Opacity(0.65);
    artistBlock.Foreground(MakeBrush(ArtistColor()));
    artistBlock.Margin({0, 0, 0, 5});
    artistBlock.Text(artist.empty() ? winrt::hstring(L" ") : winrt::hstring(artist));
    content.Children().Append(wrapDebugBorder(artistBlock, {0xFF, 0x00, 0xFF, 0x00}));

    StackPanel controlsRow;
    controlsRow.Orientation(Orientation::Horizontal);
    controlsRow.HorizontalAlignment(HorizontalAlignment::Center);
    controlsRow.Spacing(4);
    controlsRow.Margin({0, 10, 0, 10});

    auto iconClr = ButtonColor();

    auto MakeBigBtn = [&](int cmd, bool playing, bool executeCommand = true) -> Button {
        Button btn;
        btn.Width(48);
        btn.Height(48);
        btn.Padding({1,1,1,1});
        btn.CornerRadius({4,4,4,4});
        btn.BorderThickness({0,0,0,0});
        btn.VerticalAlignment(VerticalAlignment::Center);
        btn.HorizontalAlignment(HorizontalAlignment::Center);

        const wchar_t* glyph = L"";
        if (cmd == 1) glyph = L"\uE622";
        else if (cmd == 2) glyph = playing ? L"\uE62E" : L"\uF5B0";
        else if (cmd == 3) glyph = L"\uE623";
        else if (cmd == 7) glyph = L"\uE8B1";
        else if (cmd == 8) {
            RepeatMode mode = g_repeatMode.load();
            glyph = mode == RepeatMode::One ? L"\uE8ED" :
                    mode == RepeatMode::All ? L"\uE8EE" : L"\uF5E7";
        }

        TextBlock iconText;
        iconText.Text(winrt::hstring(glyph));
        iconText.FontSize(16);
        iconText.FontFamily(Media::FontFamily(L"Segoe Fluent Icons"));
        iconText.Foreground(MakeBrush(iconClr));
        iconText.HorizontalAlignment(HorizontalAlignment::Center);
        iconText.VerticalAlignment(VerticalAlignment::Center);
        if (cmd == 7) iconText.Opacity(g_shuffleEnabled.load() ? 1.0 : 0.40);
        if (cmd == 8) iconText.Opacity(g_repeatMode.load() != RepeatMode::Off ? 1.0 : 0.40);
        btn.Content(winrt::box_value(iconText));

        if (executeCommand) {
            btn.Click([cmd](auto const&, auto const&) {
                if (!g_unloading) {
                    try {
                        SendMediaCommandAsync(cmd);
                        DispatchMediaUpdate();
                    } catch (...) {}
                }
            });
        }

        ApplyFluentMediaButtonStyle(btn);

        auto isHovered = std::make_shared<bool>(false);
        auto pressLocked = std::make_shared<bool>(false);
        auto applyState = [btn, isHovered, pressLocked](bool pressed) {
            try {
                GoToCommonState(btn, IsHoverEffectEnabled(g_settings.mediaButtonsHoverEffectMode), pressed, *isHovered);
            } catch (...) {}
        };
        auto updateBtnVisualState = [applyState, pressLocked]() {
            if (*pressLocked) return;
            applyState(false);
        };
        
        RunWhenButtonReady(btn, [btn, applyState]() {
            try {
                SetupMediaButtonCommonStates(btn);
                applyState(false);
            } catch (...) {}
        });
        
        btn.PointerEntered([isHovered, updateBtnVisualState](auto const&, auto const&) {
            *isHovered = true;
            updateBtnVisualState();
        });
        btn.PointerExited([isHovered, updateBtnVisualState](auto const&, auto const&) {
            *isHovered = false;
            updateBtnVisualState();
        });
        btn.AddHandler(UIElement::PointerPressedEvent(), winrt::box_value(
            winrt::Windows::UI::Xaml::Input::PointerEventHandler(
            [applyState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
            try {
                if (auto elem = sender.template try_as<UIElement>()) elem.CapturePointer(e.Pointer());
                applyState(true);
            } catch (...) {}
        })), true);
        btn.AddHandler(UIElement::PointerReleasedEvent(), winrt::box_value(
            winrt::Windows::UI::Xaml::Input::PointerEventHandler(
            [applyState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
            try {
                if (auto elem = sender.template try_as<UIElement>()) elem.ReleasePointerCapture(e.Pointer());
                applyState(false);
            } catch (...) {}
        })), true);
        
        return btn;
    };

    Button shuffleBtn = MakeBigBtn(7, false);
    Button prevBtn    = MakeBigBtn(1, false);
    Button playBtn    = MakeBigBtn(2, isPlaying);
    Button nextBtn    = MakeBigBtn(3, false);
    Button repeatBtn  = MakeBigBtn(8, false, false);

    shuffleBtn.IsEnabled(hasMedia && canShuffle);
    shuffleBtn.Opacity(hasMedia && canShuffle ? 1.0 : 0.35);
    prevBtn.IsEnabled(hasMedia && canSkipPrevious);
    prevBtn.Opacity(hasMedia && canSkipPrevious ? 1.0 : 0.35);
    playBtn.IsEnabled(hasMedia);
    playBtn.Opacity(hasMedia ? 1.0 : 0.35);
    nextBtn.IsEnabled(hasMedia && canSkipNext);
    nextBtn.Opacity(hasMedia && canSkipNext ? 1.0 : 0.35);
    repeatBtn.IsEnabled(hasMedia && canRepeat);
    repeatBtn.Opacity(hasMedia && canRepeat ? 1.0 : 0.35);

    ToolTip shuffleToolTip;
    shuffleToolTip.Content(winrt::box_value(winrt::hstring(L"Toggle Shuffle")));
    ToolTipService::SetToolTip(shuffleBtn, shuffleToolTip);
    ToolTip repeatToolTip;
    repeatToolTip.Content(winrt::box_value(winrt::hstring(L"Toggle Repeat")));
    ToolTipService::SetToolTip(repeatBtn, repeatToolTip);

    repeatBtn.Click([](auto const&, auto const&) {
        if (g_unloading) return;
        try {
            RepeatMode cur = g_repeatMode.load();
            RepeatMode next;
            int cmd;
            if (cur == RepeatMode::Off) {
                next = RepeatMode::All; cmd = 11;
            } else if (cur == RepeatMode::All) {
                next = RepeatMode::One; cmd = 12;
            } else {
                next = RepeatMode::Off; cmd = 10;
            }
            g_repeatMode.store(next);
            if (g_miniPlayerRepeatBtnRef) {
                if (auto icon = g_miniPlayerRepeatBtnRef.Content().try_as<TextBlock>()) {
                    icon.Text(next == RepeatMode::One ? L"\uE8ED" :
                              next == RepeatMode::All ? L"\uE8EE" : L"\uF5E7");
                    icon.Opacity(next != RepeatMode::Off ? 1.0 : 0.40);
                }
            }
            SendMediaCommandAsync(cmd);
            DispatchMediaUpdate();
        } catch (...) {}
    });

    controlsRow.Children().Append(shuffleBtn);
    controlsRow.Children().Append(prevBtn);
    controlsRow.Children().Append(playBtn);
    controlsRow.Children().Append(nextBtn);
    controlsRow.Children().Append(repeatBtn);

    if (g_settings.showMiniPlayerBorder) {
        prevBtn.BorderBrush(MakeBrush({0xFF, 0xFF, 0x40, 0x40}));
        prevBtn.BorderThickness({1, 1, 1, 1});
        playBtn.BorderBrush(MakeBrush({0xFF, 0x40, 0xFF, 0x40}));
        playBtn.BorderThickness({1, 1, 1, 1});
        nextBtn.BorderBrush(MakeBrush({0xFF, 0x40, 0x40, 0xFF}));
        nextBtn.BorderThickness({1, 1, 1, 1});
    }

    content.Children().Append(wrapDebugBorder(controlsRow, {0xFF, 0x00, 0x00, 0xFF}));

    {
        Border sep;
        sep.Height(1);
        sep.Margin({-16, 0, -16, 0});
        bool isLight = IsSystemLightTheme();
        sep.Background(MakeBrush(isLight
            ? winrt::Windows::UI::Color{0x20, 0x00, 0x00, 0x00}
            : winrt::Windows::UI::Color{0x20, 0xFF, 0xFF, 0xFF}));
        sep.Visibility(Visibility::Collapsed);
        g_miniPlayerSessionListSepRef = sep;
        content.Children().Append(sep);
    }

    if (!g_settings.hideMediaSessionsList) {
        StackPanel sessionList;
        sessionList.Orientation(Orientation::Vertical);
        sessionList.Spacing(0);
        sessionList.Margin({-16, 3, -16, 3});
        sessionList.Visibility(Visibility::Collapsed);
        g_miniPlayerSessionListRef = sessionList;
        content.Children().Append(wrapDebugBorder(sessionList, {0xFF, 0xFF, 0x00, 0xFF}));
    } else {
        g_miniPlayerSessionListRef = nullptr;
    }

    Grid bottomBar;
    Border bottomSep;
    {
        bool isLight = IsSystemLightTheme();

        bottomSep.Height(1);
        bottomSep.Background(MakeBrush(isLight
            ? winrt::Windows::UI::Color{0x20, 0x00, 0x00, 0x00}
            : winrt::Windows::UI::Color{0x20, 0xFF, 0xFF, 0xFF}));

        bottomBar.Margin({-16, 0, -16, -16});
        bottomBar.Padding({12, 6, 12, 6});
        bottomBar.Height(48);
        bottomBar.VerticalAlignment(VerticalAlignment::Bottom);
        bottomBar.CornerRadius({0, 0, 6, 6});

        try {
            AcrylicBrush bottomAcrylic;
            bottomAcrylic.BackgroundSource(AcrylicBackgroundSource::Backdrop);
            bottomAcrylic.TintColor(isLight
                ? winrt::Windows::UI::Color{0xFF, 0xEE, 0xEE, 0xEE}
                : winrt::Windows::UI::Color{0xFF, 0x1C, 0x1C, 0x1C});
            bottomAcrylic.TintOpacity(isLight ? 0.00 : 0.50);
            bottomAcrylic.TintLuminosityOpacity(isLight ? 0.90 : 0.96);
            bottomAcrylic.FallbackColor(isLight
                ? winrt::Windows::UI::Color{0xFF, 0xEE, 0xEE, 0xEE}
                : winrt::Windows::UI::Color{0xFF, 0x1C, 0x1C, 0x1C});
            bottomBar.Background(bottomAcrylic);
        } catch (...) {
            bottomBar.Background(MakeBrush(isLight
                ? winrt::Windows::UI::Color{0xFF, 0xEE, 0xEE, 0xEE}
                : winrt::Windows::UI::Color{0xFF, 0x1C, 0x1C, 0x1C}));
        }

        StackPanel bottomRow;
        bottomRow.Orientation(Orientation::Horizontal);
        bottomRow.HorizontalAlignment(HorizontalAlignment::Right);
        bottomRow.VerticalAlignment(VerticalAlignment::Center);
        bottomRow.Spacing(2);

        auto MakeBottomBtn = [&](const wchar_t* glyph, std::wstring tooltip) -> Button {
            Button btn;
            btn.Width(35);
            btn.Height(35);
            btn.Padding({0,0,0,0});
            btn.CornerRadius({4,4,4,4});
            btn.BorderThickness({0,0,0,0});
            btn.VerticalAlignment(VerticalAlignment::Center);

            TextBlock icon;
            icon.Text(winrt::hstring(glyph));
            icon.FontSize(14);
            icon.FontFamily(Media::FontFamily(L"Segoe Fluent Icons"));
            icon.Foreground(MakeBrush(isLight
                ? winrt::Windows::UI::Color{0xCC, 0x10, 0x10, 0x10}
                : winrt::Windows::UI::Color{0xCC, 0xFF, 0xFF, 0xFF}));
            icon.HorizontalAlignment(HorizontalAlignment::Center);
            icon.VerticalAlignment(VerticalAlignment::Center);
            btn.Content(winrt::box_value(icon));

            if (!tooltip.empty()) {
                ToolTip tt;
                tt.Content(winrt::box_value(winrt::hstring(tooltip)));
                ToolTipService::SetToolTip(btn, tt);
            }

            ApplyFluentMediaButtonStyle(btn);
            auto isHovered = std::make_shared<bool>(false);
            auto applyState = [btn, isHovered](bool pressed) {
                try {
                    GoToCommonState(btn,
                        IsHoverEffectEnabled(g_settings.mediaButtonsHoverEffectMode),
                        pressed, *isHovered);
                } catch (...) {}
            };
            RunWhenButtonReady(btn, [btn, applyState]() {
                try {
                    SetupMediaButtonCommonStates(btn);
                    applyState(false);
                } catch (...) {}
            });
            btn.PointerEntered([isHovered, applyState](auto const&, auto const&) {
                *isHovered = true; applyState(false);
            });
            btn.PointerExited([isHovered, applyState](auto const&, auto const&) {
                *isHovered = false; applyState(false);
            });
            btn.AddHandler(UIElement::PointerPressedEvent(), winrt::box_value(
                winrt::Windows::UI::Xaml::Input::PointerEventHandler(
                [applyState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
                try {
                    if (auto el = sender.template try_as<UIElement>())
                        el.CapturePointer(e.Pointer());
                    applyState(true);
                } catch (...) {}
            })), true);
            btn.AddHandler(UIElement::PointerReleasedEvent(), winrt::box_value(
                winrt::Windows::UI::Xaml::Input::PointerEventHandler(
                [applyState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
                try {
                    if (auto el = sender.template try_as<UIElement>())
                        el.ReleasePointerCapture(e.Pointer());
                    applyState(false);
                } catch (...) {}
            })), true);

            return btn;
        };

        Button settingsBtn = MakeBottomBtn(L"\uE713", L"Open Windhawk");
        settingsBtn.Click([](auto const&, auto const&) {
            OpenWindhawk();
        });

        bottomRow.Children().Append(settingsBtn);
        bottomBar.Children().Append(bottomRow);
    }

    Grid innerGrid;
    innerGrid.VerticalAlignment(VerticalAlignment::Stretch);
    RowDefinition rowContent;
    rowContent.Height(GridLengthHelper::FromValueAndType(1.0, GridUnitType::Star));
    RowDefinition rowBottom;
    rowBottom.Height(GridLengthHelper::FromValueAndType(48.0, GridUnitType::Pixel));
    innerGrid.RowDefinitions().Append(rowContent);
    innerGrid.RowDefinitions().Append(rowBottom);

    content.VerticalAlignment(VerticalAlignment::Top);
    Grid::SetRow(content, 0);

    Border contentBackground;
    contentBackground.Background(flyoutContentBackground);
    contentBackground.CornerRadius({6, 6, 0, 0});
    contentBackground.Margin({-16, -16, -16, 0});
    Grid::SetRow(contentBackground, 0);
    innerGrid.Children().Append(contentBackground);
    innerGrid.Children().Append(content);

    bottomBar.Margin({-16, 0, -16, 0});
    bottomBar.VerticalAlignment(VerticalAlignment::Stretch);
    Grid::SetRow(bottomBar, 1);
    innerGrid.Children().Append(bottomBar);

    bottomSep.Margin({-16, 0, -16, 0});
    bottomSep.VerticalAlignment(VerticalAlignment::Top);
    Grid::SetRow(bottomSep, 1);
    innerGrid.Children().Append(bottomSep);

    if (g_settings.showMiniPlayerBorder) {
        innerGrid.BorderBrush(MakeBrush({0xFF, 0x80, 0x80, 0xFF}));
        innerGrid.BorderThickness({1, 1, 1, 1});
        bottomBar.BorderBrush(MakeBrush({0xFF, 0xFF, 0x80, 0x00}));
        bottomBar.BorderThickness({1, 1, 1, 1});
    }

    bg.Child(innerGrid);
    outer.Children().Append(bg);

    outer.Opacity(0.0);
    try {
        using namespace winrt::Windows::UI::Xaml::Media;
        CompositeTransform transform;
        transform.TranslateY(0.0);
        outer.RenderTransform(transform);
    } catch (...) {}

    g_miniPlayerArtRef       = artImage;
    g_miniPlayerTitleRef     = titleBlock;
    g_miniPlayerArtistRef    = artistBlock;
    g_miniPlayerPlayBtnRef   = playBtn;
    g_miniPlayerPrevBtnRef   = prevBtn;
    g_miniPlayerNextBtnRef   = nextBtn;
    g_miniPlayerShuffleBtnRef = shuffleBtn;
    g_miniPlayerRepeatBtnRef  = repeatBtn;

    return outer;
}

struct MiniPlayerAnchor {
    winrt::Windows::Foundation::Point placementPoint{0.f, 0.f};
    Controls::Primitives::FlyoutPlacementMode placement =
        Controls::Primitives::FlyoutPlacementMode::Top;
    int    animAxis = 0;
    double animSign = 1.0;
};

static bool GetTaskbarMonitorWorkAreaInfo(FrameworkElement const& rootContent,
                                          RECT& outWorkAreaPx,
                                          POINT& outOriginPx,
                                          double& outScale) {
    if (!g_taskbarWnd || !rootContent) return false;

    HMONITOR mon = MonitorFromWindow(g_taskbarWnd, MONITOR_DEFAULTTONEAREST);
    if (!mon) return false;

    MONITORINFO mi{};
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfo(mon, &mi)) return false;
    outWorkAreaPx = mi.rcWork;

    POINT originPx{0, 0};
    if (!ClientToScreen(g_taskbarWnd, &originPx)) return false;
    outOriginPx = originPx;

    double scale = 1.0;
    try {
        auto xamlRoot = rootContent.XamlRoot();
        if (xamlRoot) scale = xamlRoot.RasterizationScale();
    } catch (...) {}
    if (scale <= 0.0) scale = 1.0;
    outScale = scale;

    return true;
}

static bool ComputeScreenPlacementAnchor(FrameworkElement const& rootContent,
                                         MiniPlayerAnchor& outAnchor) {
    RECT workPx;
    POINT originPx;
    double scale;
    if (!GetTaskbarMonitorWorkAreaInfo(rootContent, workPx, originPx, scale)) {
        return false;
    }

    double left   = (workPx.left   - originPx.x) / scale;
    double top    = (workPx.top    - originPx.y) / scale;
    double right  = (workPx.right  - originPx.x) / scale;
    double bottom = (workPx.bottom - originPx.y) / scale;

    const std::wstring& hPlace = g_settings.miniPlayerHorizontalPlacement;
    const std::wstring& vPlace = g_settings.miniPlayerVerticalPlacement;
    int hDist = g_settings.miniPlayerHorizontalDistanceFromScreenEdge;
    int vDist = g_settings.miniPlayerVerticalDistanceFromScreenEdge;

    bool hLeft  = (hPlace == L"left");
    bool hRight = (hPlace == L"right");
    bool vTop   = (vPlace == L"top");
    bool vBottom = (vPlace == L"bottom");

    double anchorX;
    if (hLeft)       anchorX = left + hDist;
    else if (hRight) anchorX = right - hDist;
    else              anchorX = (left + right) / 2.0 + hDist;

    double anchorY;
    if (vTop)         anchorY = top + vDist;
    else if (vBottom) anchorY = bottom - vDist;
    else               anchorY = (top + bottom) / 2.0 + vDist;

    using FPM = Controls::Primitives::FlyoutPlacementMode;
    FPM placement = FPM::Top;
    int animAxis = 0;
    double animSign = 1.0;

    if (vBottom) {
        placement = hLeft ? FPM::TopEdgeAlignedLeft
                  : hRight ? FPM::TopEdgeAlignedRight
                  : FPM::Top;
        animAxis = 0;
        animSign = 1.0;
    } else if (vTop) {
        placement = hLeft ? FPM::BottomEdgeAlignedLeft
                  : hRight ? FPM::BottomEdgeAlignedRight
                  : FPM::Bottom;
        animAxis = 0;
        animSign = -1.0;
    } else {
        if (hLeft) {
            placement = FPM::Right;
            animAxis = 1;
            animSign = -1.0;
        } else if (hRight) {
            placement = FPM::Left;
            animAxis = 1;
            animSign = 1.0;
        } else {
            placement = FPM::Top;
            animAxis = 0;
            animSign = 1.0;
        }
    }

    if (g_settings.miniPlayerAnimation == L"top") {
        animAxis = 0; animSign = -1.0;
    } else if (g_settings.miniPlayerAnimation == L"bottom") {
        animAxis = 0; animSign = 1.0;
    } else if (g_settings.miniPlayerAnimation == L"left") {
        animAxis = 1; animSign = -1.0;
    } else if (g_settings.miniPlayerAnimation == L"right") {
        animAxis = 1; animSign = 1.0;
    }

    outAnchor.placementPoint = {(float)anchorX, (float)anchorY};
    outAnchor.placement = placement;
    outAnchor.animAxis = animAxis;
    outAnchor.animSign = animSign;
    return true;
}

static void ShowMiniPlayerFlyout(FrameworkElement const& target) {
    if (!target || g_unloading) return;
    try {

        if (g_miniPlayerFlyoutOpen && g_miniPlayerFlyout) {
            g_miniPlayerExplicitCloseRequested.store(true);
            g_miniPlayerFlyout.Hide();
            return;
        }

        Flyout flyout;
        Grid content = BuildMiniPlayerFlyoutContent();

        Grid clipHost;
        clipHost.HorizontalAlignment(HorizontalAlignment::Stretch);
        clipHost.VerticalAlignment(VerticalAlignment::Stretch);
        clipHost.Children().Append(content);
        flyout.Content(clipHost);

        Style flyoutStyle(winrt::xaml_typename<Controls::FlyoutPresenter>());
        flyoutStyle.Setters().Append(Setter(
            Controls::Control::BackgroundProperty(),
            winrt::box_value(winrt::Windows::UI::Xaml::Media::SolidColorBrush{
                winrt::Windows::UI::Colors::Transparent()})));
        flyoutStyle.Setters().Append(Setter(
            FrameworkElement::MarginProperty(),
            winrt::box_value(Thickness{0, 0, 0, 0})));
        flyoutStyle.Setters().Append(Setter(
            Controls::Control::PaddingProperty(),
            winrt::box_value(Thickness{0, 0, 0, 0})));
        flyoutStyle.Setters().Append(Setter(
            Controls::Control::BorderThicknessProperty(),
            winrt::box_value(Thickness{0, 0, 0, 0})));
        flyoutStyle.Setters().Append(Setter(
            Controls::Control::BorderBrushProperty(),
            winrt::box_value(winrt::Windows::UI::Xaml::Media::SolidColorBrush{
                winrt::Windows::UI::Colors::Transparent()})));
        flyoutStyle.Setters().Append(Setter(
            FrameworkElement::MaxWidthProperty(),
            winrt::box_value(10000.0)));
        flyoutStyle.Setters().Append(Setter(
            FrameworkElement::MaxHeightProperty(),
            winrt::box_value(10000.0)));
        flyout.FlyoutPresenterStyle(flyoutStyle);

        flyout.Opened([content](auto const&, auto const&) {
            g_miniPlayerFlyoutOpen = true;
            g_miniPlayerClosingAnimStarted.store(false);
            if (g_playerButtonStateUpdater) g_playerButtonStateUpdater();
            g_miniSessionHoveredIndex.store(-1);
            {
                std::lock_guard<std::mutex> lk(g_miniSessionMtx);
                g_miniSessionInfos.clear();
            }
            RefreshMiniPlayerFlyoutUI();
            if (!g_settings.hideMediaSessionsList) {
                FetchMiniSessionInfosAsync(g_taskbarWnd);
            }

            try {
                Controls::FlyoutPresenter presenter{nullptr};
                {
                    auto node = content.as<winrt::Windows::UI::Xaml::DependencyObject>();
                    for (int i = 0; i < 12 && node; ++i) {
                        if (auto p = node.try_as<Controls::FlyoutPresenter>()) {
                            presenter = p;
                            break;
                        }
                        node = VisualTreeHelper::GetParent(node);
                    }
                }
                if (presenter) {
                    int childCount = VisualTreeHelper::GetChildrenCount(presenter);
                    for (int i = 0; i < childCount; ++i) {
                        auto child = VisualTreeHelper::GetChild(presenter, i);
                        if (auto border = child.try_as<Controls::Border>()) {
                            border.Shadow(nullptr);
                            break;
                        }
                    }
                }
            } catch (...) {
                Wh_Log(L"Flyout.Opened: Exception removing Shadow");
            }

            content.Opacity(0.0);
            auto transform = content.RenderTransform()
                .try_as<winrt::Windows::UI::Xaml::Media::CompositeTransform>();
            if (!transform) {
                transform = winrt::Windows::UI::Xaml::Media::CompositeTransform();
                content.RenderTransform(transform);
            }
            transform.TranslateX(0.0);
            transform.TranslateY(0.0);

            auto fired = std::make_shared<bool>(false);
            auto doReveal = [content, transform, fired]() mutable {
                if (*fired) return;
                *fired = true;
                try {
                    if (!transform) return;
                    bool horizontal = (g_miniPlayerAnimAxis == 1);
                    double size = horizontal ? content.ActualWidth() : content.ActualHeight();
                    if (size <= 0) size = 450.0;
                    double startOffset = size * g_miniPlayerAnimSign;

                    PCWSTR propertyPath = horizontal
                        ? L"(UIElement.RenderTransform).(CompositeTransform.TranslateX)"
                        : L"(UIElement.RenderTransform).(CompositeTransform.TranslateY)";

                    if (horizontal) transform.TranslateX(startOffset);
                    else            transform.TranslateY(startOffset);
                    content.Opacity(1.0);

                    using namespace winrt::Windows::UI::Xaml::Media::Animation;
                    Storyboard sb;
                    DoubleAnimation anim;
                    anim.From(startOffset);
                    anim.To(0.0);
                    anim.Duration(winrt::Windows::UI::Xaml::DurationHelper::FromTimeSpan(
                        std::chrono::milliseconds(250)));
                    auto ease = CircleEase();
                    ease.EasingMode(EasingMode::EaseOut);
                    anim.EasingFunction(ease);
                    Storyboard::SetTarget(anim, content);
                    Storyboard::SetTargetProperty(anim, propertyPath);
                    sb.Children().Append(anim);
                    sb.Begin();
                } catch (...) {}
            };

            auto token = std::make_shared<winrt::event_token>();
            *token = content.SizeChanged([content, token, doReveal](
                winrt::Windows::Foundation::IInspectable const&,
                winrt::Windows::UI::Xaml::SizeChangedEventArgs const&) mutable
            {
                try { content.SizeChanged(*token); } catch (...) {}
                doReveal();
            });

            auto fallbackTimer = DispatcherTimer();
            fallbackTimer.Interval(
                winrt::Windows::Foundation::TimeSpan{std::chrono::milliseconds(80)});
            auto fallbackToken = std::make_shared<winrt::event_token>();
            *fallbackToken = fallbackTimer.Tick([fallbackTimer, fallbackToken, doReveal](
                winrt::Windows::Foundation::IInspectable const&,
                winrt::Windows::Foundation::IInspectable const&) mutable
            {
                try { fallbackTimer.Stop(); } catch (...) {}
                doReveal();
            });
            fallbackTimer.Start();
        });

        flyout.Closing([content](
            winrt::Windows::UI::Xaml::Controls::Primitives::FlyoutBase const& sender,
            winrt::Windows::UI::Xaml::Controls::Primitives::FlyoutBaseClosingEventArgs const& e)
        {
            if (g_unloading || g_applyingSettings) return;

            if (g_miniPlayerClosingAnimInProgress.exchange(false)) return;

            bool explicitClose = g_miniPlayerExplicitCloseRequested.exchange(false);

            if (g_settings.keepMiniPlayerOpen && !explicitClose) {
                e.Cancel(true);
                return;
            }

            if (g_miniPlayerClosingAnimStarted.load()) {
                e.Cancel(true);
                return;
            }

            try {
                auto transform = content.RenderTransform()
                    .try_as<winrt::Windows::UI::Xaml::Media::CompositeTransform>();
                if (!transform) return;
                e.Cancel(true);

                bool horizontal = (g_miniPlayerAnimAxis == 1);
                double size = horizontal ? content.ActualWidth() : content.ActualHeight();
                if (size <= 0) size = 450.0;
                double endOffset = (size + 16.0) * g_miniPlayerAnimSign;

                PCWSTR propertyPath = horizontal
                    ? L"(UIElement.RenderTransform).(CompositeTransform.TranslateX)"
                    : L"(UIElement.RenderTransform).(CompositeTransform.TranslateY)";

                using namespace winrt::Windows::UI::Xaml::Media::Animation;
                Storyboard sb;
                DoubleAnimation anim;
                anim.To(endOffset);
                anim.Duration(winrt::Windows::UI::Xaml::DurationHelper::FromTimeSpan(
                    std::chrono::milliseconds(250)));
                auto ease = CircleEase();
                ease.EasingMode(EasingMode::EaseIn);
                anim.EasingFunction(ease);
                Storyboard::SetTarget(anim, content);
                Storyboard::SetTargetProperty(anim, propertyPath);
                sb.Children().Append(anim);
                g_miniPlayerClosingAnimStarted.store(true);
                auto doHide = [sender]() {
                    g_miniPlayerClosingAnimStarted.store(false);
                    try {
                        g_miniPlayerClosingAnimInProgress.store(true);
                        sender.Hide();
                    } catch (...) {
                        g_miniPlayerClosingAnimInProgress.store(false);
                    }
                };
                sb.Completed([doHide](auto const&, auto const&) { doHide(); });
                auto closingFallback = DispatcherTimer();
                closingFallback.Interval(winrt::Windows::Foundation::TimeSpan{
                    std::chrono::milliseconds(350)});
                auto closingFallbackToken = std::make_shared<winrt::event_token>();
                *closingFallbackToken = closingFallback.Tick(
                    [closingFallback, closingFallbackToken, doHide](
                        winrt::Windows::Foundation::IInspectable const&,
                        winrt::Windows::Foundation::IInspectable const&) mutable {
                        try { closingFallback.Stop(); } catch (...) {}
                        closingFallback.Tick(*closingFallbackToken);
                        if (g_miniPlayerClosingAnimStarted.load())
                            doHide();
                    });
                closingFallback.Start();
                sb.Begin();
            } catch (...) {
                g_miniPlayerClosingAnimStarted.store(false);
            }
        });

        flyout.Closed([](auto const&, auto const&) {
            g_miniPlayerFlyoutOpen = false;
            g_miniPlayerClosingAnimStarted.store(false);
            g_miniSessionHoveredIndex.store(-1);
            g_miniPlayerArtRef = nullptr;
            g_miniPlayerTitleRef = nullptr;
            g_miniPlayerArtistRef = nullptr;
            g_miniPlayerPlayBtnRef = nullptr;
            g_miniPlayerPrevBtnRef = nullptr;
            g_miniPlayerNextBtnRef = nullptr;
            g_miniPlayerShuffleBtnRef = nullptr;
            g_miniPlayerRepeatBtnRef = nullptr;
            g_miniPlayerSessionListRef = nullptr;
            g_miniPlayerSessionListSepRef = nullptr;
            g_miniSessionCachedThumbSizes.clear();
            if (g_playerButtonStateUpdater) g_playerButtonStateUpdater();
        });


        bool useScreenPlacement = (g_settings.miniPlayerPlacementMode == L"screen");
        Controls::Primitives::FlyoutPlacementMode placementMode =
            Controls::Primitives::FlyoutPlacementMode::Top;
        winrt::Windows::Foundation::Point anchorPoint{0.f, 0.f};
        FrameworkElement showAtElem = target;
        bool anchorComputed = false;

        try {
            auto xamlRoot = target.XamlRoot();
            if (xamlRoot) {
                auto rootContent = xamlRoot.Content().try_as<FrameworkElement>();
                if (rootContent) {
                    showAtElem = rootContent;

                    try {
                        flyout.OverlayInputPassThroughElement(rootContent);
                    } catch (...) {}

                    if (useScreenPlacement) {
                        MiniPlayerAnchor screenAnchor;
                        if (ComputeScreenPlacementAnchor(rootContent, screenAnchor)) {
                            anchorPoint = screenAnchor.placementPoint;
                            placementMode = screenAnchor.placement;
                            g_miniPlayerAnimAxis = screenAnchor.animAxis;
                            g_miniPlayerAnimSign = screenAnchor.animSign;
                            anchorComputed = true;
                        } else {
                            Wh_Log(L"ShowMiniPlayerFlyout: Failed to compute screen anchor, "
                                   L"falling back to 'over the player' placement");
                        }
                    }

                    if (!anchorComputed) {
                        auto xform = target.TransformToVisual(rootContent);
                        auto pt = xform.TransformPoint({0.f, 0.f});
                        float cx = pt.X + (float)target.ActualWidth() * 0.5f +
                                   (float)g_settings.miniPlayerHorizontalOffsetAbove;

                        bool placeBelow = (g_settings.miniPlayerVerticalPlacementNear == L"bottom");
                        if (placeBelow) {
                            float ty = pt.Y + (float)target.ActualHeight();
                            anchorPoint = {cx, ty};
                            placementMode = Controls::Primitives::FlyoutPlacementMode::Bottom;
                            g_miniPlayerAnimAxis = 0;
                            g_miniPlayerAnimSign = -1.0;
                        } else {
                            float ty = pt.Y;
                            anchorPoint = {cx, ty};
                            placementMode = Controls::Primitives::FlyoutPlacementMode::Top;
                            g_miniPlayerAnimAxis = 0;
                            g_miniPlayerAnimSign = 1.0;
                        }
                    }
                }
            }
        } catch (...) {
            Wh_Log(L"ShowMiniPlayerFlyout: Exception setting position");
        }

        try {
            flyout.ShouldConstrainToRootBounds(false);
            flyout.Placement(placementMode);
        } catch (...) {}

        g_miniPlayerFlyout = flyout;


        Controls::Primitives::FlyoutShowOptions opts;
        opts.Placement(placementMode);
        opts.Position(anchorPoint);

        flyout.ShowAt(showAtElem, opts);

    } catch (...) {
        Wh_Log(L"ShowMiniPlayerFlyout: Exception in main try block");
    }
}

static Grid BuildPlayerGrid() {
    try {
        g_vizBars->clear();
        g_vizBrushes->clear();
        auto textClr = TextColor();
        auto artistClr = ArtistColor();
        auto buttonClr = ButtonColor();
        auto bgBrush = MakeBackgroundBrush();
        double phMin = (double)g_settings.playerMinHeight;
        double phMax = (double)g_settings.playerMaxHeight;
        bool hasTextOrButtons = g_settings.showTrackTitle || g_settings.showTrackArtist || (g_settings.showMediaButtons && !g_mediaButtons.empty());
        Border backgroundBorder;
        backgroundBorder.Name(L"FluentMedia_Background");
        backgroundBorder.CornerRadius({
            g_settings.cornerRadiusTL,
            g_settings.cornerRadiusTR,
            g_settings.cornerRadiusBR,
            g_settings.cornerRadiusBL
        });
        backgroundBorder.HorizontalAlignment(HorizontalAlignment::Stretch);
        backgroundBorder.VerticalAlignment(VerticalAlignment::Stretch);
        backgroundBorder.IsHitTestVisible(false);
        backgroundBorder.Visibility(Visibility::Collapsed);
        if (phMin > 0) {
            backgroundBorder.MinHeight(phMin);
        }
        if (phMax > 0) {
            backgroundBorder.MaxHeight(phMax);
        }
        Button playerButton;
        playerButton.Name(L"FluentMedia_OuterBorder");
        playerButton.CornerRadius({
            g_settings.cornerRadiusTL,
            g_settings.cornerRadiusTR,
            g_settings.cornerRadiusBR,
            g_settings.cornerRadiusBL
        });
        playerButton.BorderThickness({0, 0, 0, 0});
        playerButton.UseSystemFocusVisuals(false);
        playerButton.IsHitTestVisible(false);
        playerButton.HorizontalAlignment(HorizontalAlignment::Stretch);
        playerButton.VerticalAlignment(VerticalAlignment::Stretch);
        if (phMin > 0) {
            playerButton.MinHeight(phMin);
        }
        if (phMax > 0) {
            playerButton.MaxHeight(phMax);
        }
        Grid chromeFill;
        if (phMin > 0) {
            chromeFill.MinHeight(phMin);
        }
        if (phMax > 0) {
            chromeFill.MaxHeight(phMax);
        }
        chromeFill.IsHitTestVisible(false);
        playerButton.Content(chromeFill);
        if (g_settings.showDebugBorders) {
            playerButton.BorderBrush(MakeBrush({0xFF, 0xFF, 0x00, 0x00}));
            playerButton.BorderThickness({2, 2, 2, 2});
        }
        Grid panel;
        panel.Name(kPanelGridName);
        panel.VerticalAlignment(VerticalAlignment::Center);
        panel.HorizontalAlignment(HorizontalAlignment::Stretch);
        if (hasTextOrButtons) {
            panel.Margin({4, 2, 4, 2});
        }
        AddLayoutAnchorOverlay(panel, L"FluentMedia_DebugPanelAnchors", {0xD0, 0x00, 0xFF, 0x00});
        if (g_settings.showDebugBorders) {
            Border panelDebugBorder;
            panelDebugBorder.BorderBrush(MakeBrush({0xFF, 0x00, 0xFF, 0x00}));
            panelDebugBorder.BorderThickness({1,1,1,1});
            panel.Children().Append(panelDebugBorder);
        }
        bool buttonsLeft = g_settings.mirrorLayout;
        bool albumArtLeft = !g_settings.mirrorLayout;
        bool hasText = g_settings.showTrackTitle || g_settings.showTrackArtist;
        ColumnDefinition colFirst, colText, colSpacer, colLast;
        colFirst.Width({1.0, GridUnitType::Auto});
        if (hasText) {
            colText.Width({1.0, GridUnitType::Star});
        } else {
            colText.Width({0.0, GridUnitType::Pixel});
        }
        colSpacer.Width({0.0, GridUnitType::Pixel});
        colLast.Width({1.0, GridUnitType::Auto});
        panel.ColumnDefinitions().Append(colFirst);
        panel.ColumnDefinitions().Append(colText);
        panel.ColumnDefinitions().Append(colSpacer);
        panel.ColumnDefinitions().Append(colLast);
        Grid artContainer{nullptr};
        if (g_settings.showAlbumArt) {
            int iconSz = g_settings.appIconSize;
            artContainer = Grid();
            artContainer.VerticalAlignment(VerticalAlignment::Center);
            artContainer.HorizontalAlignment(HorizontalAlignment::Center);
            if (g_settings.albumArtMinWidth > 0) {
                artContainer.MinWidth((double)g_settings.albumArtMinWidth);
            }
            if (g_settings.albumArtMaxWidth > 0) {
                artContainer.MaxWidth((double)g_settings.albumArtMaxWidth);
            }
            if (g_settings.albumArtMinHeight > 0) {
                artContainer.MinHeight((double)g_settings.albumArtMinHeight);
            }
            if (g_settings.albumArtMaxHeight > 0) {
                artContainer.MaxHeight((double)g_settings.albumArtMaxHeight);
            }
            double artLeftMargin = (double)g_settings.albumArtLeftMargin;
            double artRightMargin = (double)g_settings.albumArtRightMargin;
            artContainer.Margin({artLeftMargin, 0, artRightMargin, 0});
            artContainer.Opacity(g_settings.albumArtOpacity / 100.0);
            artContainer.Background(MakeBrush({0x00,0x00,0x00,0x00}));
            AddLayoutAnchorOverlay(artContainer, L"FluentMedia_DebugArtAnchors", {0xD0, 0xFF, 0xFF, 0x00});
            if (g_settings.showDebugBorders) {
                Border artDebugBorder;
                artDebugBorder.BorderBrush(MakeBrush({0xFF, 0xFF, 0xFF, 0x00}));
                artDebugBorder.BorderThickness({2,2,2,2});
                artContainer.Children().Append(artDebugBorder);
            }
            winrt::Windows::UI::Xaml::Shapes::Rectangle placeholder;
            placeholder.Fill(MakeBrush({0x40,0x80,0x80,0x80}));
            double maxRadius = std::max({g_settings.albumArtCornerRadiusTL, g_settings.albumArtCornerRadiusTR,
                                        g_settings.albumArtCornerRadiusBR, g_settings.albumArtCornerRadiusBL});
            placeholder.RadiusX(maxRadius);
            placeholder.RadiusY(maxRadius);
            placeholder.HorizontalAlignment(HorizontalAlignment::Stretch);
            placeholder.VerticalAlignment(VerticalAlignment::Stretch);
            artContainer.Children().Append(placeholder);
            Border artBorder;
            artBorder.CornerRadius({
                g_settings.albumArtCornerRadiusTL,
                g_settings.albumArtCornerRadiusTR,
                g_settings.albumArtCornerRadiusBR,
                g_settings.albumArtCornerRadiusBL
            });
            artBorder.HorizontalAlignment(HorizontalAlignment::Stretch);
            artBorder.VerticalAlignment(VerticalAlignment::Stretch);
            Controls::Image artImage;
            artImage.Name(kArtImageName);
            bool isSquare = (g_settings.albumArtMinWidth == g_settings.albumArtMinHeight) &&
                        (g_settings.albumArtMaxWidth == g_settings.albumArtMaxHeight);
            artImage.Stretch(isSquare ? Stretch::Uniform : Stretch::Uniform);
            artImage.HorizontalAlignment(HorizontalAlignment::Center);
            artImage.VerticalAlignment(VerticalAlignment::Center);
            Grid artInnerGrid;
            artInnerGrid.HorizontalAlignment(HorizontalAlignment::Stretch);
            artInnerGrid.VerticalAlignment(VerticalAlignment::Stretch);
            artInnerGrid.Children().Append(artImage);
            {
                auto clipGeo = winrt::Windows::UI::Xaml::Media::RectangleGeometry();
                artInnerGrid.Clip(clipGeo);
                artInnerGrid.SizeChanged([clipGeo](
                    winrt::Windows::Foundation::IInspectable const& sender,
                    winrt::Windows::UI::Xaml::SizeChangedEventArgs const&) mutable {
                        try {
                            if (auto fe = sender.try_as<FrameworkElement>()) {
                                clipGeo.Rect({0, 0,
                                    (float)fe.ActualWidth(),
                                    (float)fe.ActualHeight()});
                            }
                        } catch (...) {}
                    });
            }
            artBorder.Child(artInnerGrid);
            artContainer.Children().Append(artBorder);
            Border artRing;
            artRing.CornerRadius({
                g_settings.albumArtCornerRadiusTL,
                g_settings.albumArtCornerRadiusTR,
                g_settings.albumArtCornerRadiusBR,
                g_settings.albumArtCornerRadiusBL
            });
            artRing.BorderThickness({1,1,1,1});
            artRing.BorderBrush(MakeBrush({0x25,0x80,0x80,0x80}));
            artContainer.Children().Append(artRing);
            if (g_settings.showAppIcon) {
                Grid iconOverlay;
                iconOverlay.VerticalAlignment(VerticalAlignment::Stretch);
                iconOverlay.HorizontalAlignment(HorizontalAlignment::Stretch);
                Controls::Image appIconImage;
                appIconImage.Name(kAppIconImageName);
                appIconImage.Width(iconSz);
                appIconImage.Height(iconSz);
                appIconImage.Stretch(Stretch::UniformToFill);
                appIconImage.Visibility(Visibility::Collapsed);
                const auto& corner = g_settings.appIconCorner;
                double margin_right  = 0, margin_bottom = 0;
                double margin_left   = 0, margin_top    = 0;
                HorizontalAlignment ha = HorizontalAlignment::Right;
                VerticalAlignment   va = VerticalAlignment::Bottom;
                if (corner == L"top_left") {
                    ha = HorizontalAlignment::Left;
                    va = VerticalAlignment::Top;
                } else if (corner == L"top_right") {
                    ha = HorizontalAlignment::Right;
                    va = VerticalAlignment::Top;
                } else if (corner == L"bottom_left") {
                    ha = HorizontalAlignment::Left;
                    va = VerticalAlignment::Bottom;
                } else {
                    ha = HorizontalAlignment::Right;
                    va = VerticalAlignment::Bottom;
                }
                appIconImage.HorizontalAlignment(ha);
                appIconImage.VerticalAlignment(va);
                appIconImage.Margin({margin_left, margin_top, margin_right, margin_bottom});
                iconOverlay.Children().Append(appIconImage);
                Canvas::SetZIndex(iconOverlay, 15);
                artContainer.Children().Append(iconOverlay);
            }
            if (g_settings.showPauseOverlay) {
                Border pauseBorder;
                pauseBorder.Name(L"PauseIconOverlay");
                pauseBorder.HorizontalAlignment(HorizontalAlignment::Stretch);
                pauseBorder.VerticalAlignment(VerticalAlignment::Stretch);
                BYTE opacity = (BYTE)((g_settings.pauseOverlayOpacity * 255) / 100);
                pauseBorder.Background(MakeBrush({opacity, 0x00, 0x00, 0x00}));
                pauseBorder.Visibility(Visibility::Collapsed);
                Canvas::SetZIndex(pauseBorder, 8);
                TextBlock pauseIcon;
                pauseIcon.Text(L"");
                pauseIcon.FontFamily(Media::FontFamily(L"Segoe MDL2 Assets"));
                pauseIcon.FontSize((double)g_settings.pauseOverlayIconSize);
                pauseIcon.Foreground(MakeBrush({0xFF, 0xFF, 0xFF, 0xFF}));
                pauseIcon.HorizontalAlignment(HorizontalAlignment::Center);
                pauseIcon.VerticalAlignment(VerticalAlignment::Center);
                pauseBorder.Child(pauseIcon);
                artInnerGrid.Children().Append(pauseBorder);
            }
            if (g_settings.disableAlbumArtClick) {
                artContainer.IsHitTestVisible(false);
            } else {
                artContainer.PointerPressed([](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) mutable {
                    if (auto elem = sender.template try_as<UIElement>()) {
                        elem.CapturePointer(e.Pointer());
                    }
                    e.Handled(true);
                });
                auto artDblClickLastTime = std::make_shared<ULONGLONG>(0);
                auto artDblClickLastKind = std::make_shared<winrt::Windows::UI::Input::PointerUpdateKind>(
                    winrt::Windows::UI::Input::PointerUpdateKind::Other);
                artContainer.PointerReleased([artDblClickLastTime, artDblClickLastKind](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) mutable {
                    bool actuallyHovered = false;
                    if (auto elem = sender.template try_as<UIElement>()) {
                        elem.ReleasePointerCapture(e.Pointer());
                        try {
                            auto pointerPoint = e.GetCurrentPoint(elem);
                            auto bounds = elem.RenderSize();
                            auto pos = pointerPoint.Position();
                            actuallyHovered = (pos.X >= 0 && pos.X <= bounds.Width && pos.Y >= 0 && pos.Y <= bounds.Height);
                        } catch (...) { actuallyHovered = false; }
                    }
                    if (g_unloading) return;
                    if (actuallyHovered) {
                        auto kind = e.GetCurrentPoint(nullptr).Properties().PointerUpdateKind();
                        auto fe = sender.template try_as<FrameworkElement>();
                        ULONGLONG now = GetTickCount64();
                        UINT dblClickMs = GetDoubleClickTime();
                        bool isDouble = (kind == *artDblClickLastKind) &&
                                        (now - *artDblClickLastTime) <= dblClickMs;
                        *artDblClickLastTime = isDouble ? 0 : now;
                        *artDblClickLastKind = kind;
                        using Kind = winrt::Windows::UI::Input::PointerUpdateKind;
                        if (kind == Kind::LeftButtonReleased) {
                            if (isDouble) ExecuteMediaAction(g_settings.albumArtLeftDoubleClick, fe);
                            else          ExecuteMediaAction(g_settings.albumArtLeftClick, fe);
                        } else if (kind == Kind::RightButtonReleased) {
                            if (isDouble) ExecuteMediaAction(g_settings.albumArtRightDoubleClick, fe);
                            else          ExecuteMediaAction(g_settings.albumArtRightClick, fe);
                        } else if (kind == Kind::MiddleButtonReleased) {
                            if (isDouble) ExecuteMediaAction(g_settings.albumArtMiddleDoubleClick, fe);
                            else          ExecuteMediaAction(g_settings.albumArtMiddleClick, fe);
                        }
                    }
                    e.Handled(true);
                });
                artContainer.PointerWheelChanged([](winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
                    if (g_unloading) return;
                    auto action = g_settings.albumArtWheelAction;
                    if (action == L"none") return;
                    auto props = e.GetCurrentPoint(nullptr).Properties();
                    int delta = props.MouseWheelDelta();
                    if (action == L"switch_tracks") {
                        if (delta > 0) SendMediaCommandAsync(1);
                        else if (delta < 0) SendMediaCommandAsync(3);
                        DispatchMediaUpdate();
                    } else if (action == L"switch_tracks_inverted") {
                        if (delta > 0) SendMediaCommandAsync(3);
                        else if (delta < 0) SendMediaCommandAsync(1);
                        DispatchMediaUpdate();
                    } else if (action == L"switch_sessions") {
                        if (delta != 0) SwitchMediaSession();
                    } else if (action == L"system_sound") {
                        SpawnTrackedWorker([delta]() { ChangeSystemVolume(delta > 0); });
                    } else if (action == L"app_sound") {
                        SpawnTrackedWorker([delta]() {
                            winrt::init_apartment(winrt::apartment_type::multi_threaded);
                            std::wstring aumid;
                            {
                                GlobalSystemMediaTransportControlsSession sessionCopy{nullptr};
                                {
                                    std::lock_guard<std::mutex> lk(g_sessionMtx);
                                    sessionCopy = g_currentSession;
                                }
                                if (sessionCopy) {
                                    try {
                                        aumid = std::wstring(sessionCopy.SourceAppUserModelId());
                                    } catch (...) {}
                                }
                            }
                            if (!aumid.empty()) {
                                float volumeDelta = (delta > 0) ? 0.02f : -0.02f;
                                AdjustAppVolumeByAUMID(aumid, volumeDelta);
                            }
                            winrt::uninit_apartment();
                        });
                    }
                    e.Handled(true);
                });
            }
            artContainer.Tag(winrt::box_value(winrt::hstring(L"FluentMediaArtContainer")));
            if (albumArtLeft) {
                Grid::SetColumn(artContainer, 0);
            } else {
                Grid::SetColumn(artContainer, 3);
            }
            panel.Children().Append(artContainer);
        }
        if (g_settings.showTrackTitle || g_settings.showTrackArtist) {
            Border textContainer;
            textContainer.VerticalAlignment(VerticalAlignment::Center);
            if (albumArtLeft) {
                textContainer.HorizontalAlignment(HorizontalAlignment::Left);
            } else {
                textContainer.HorizontalAlignment(HorizontalAlignment::Right);
            }
            if (g_settings.textAreaMinWidth > 0) {
                textContainer.MinWidth((double)g_settings.textAreaMinWidth);
            }
            if (g_settings.textAreaMaxWidth > 0) {
                textContainer.MaxWidth((double)g_settings.textAreaMaxWidth);
            }
            if (g_settings.textAreaMinHeight > 0) {
                textContainer.MinHeight((double)g_settings.textAreaMinHeight);
            }
            if (g_settings.textAreaMaxHeight > 0) {
                textContainer.MaxHeight((double)g_settings.textAreaMaxHeight);
            }
            double leftMargin = (double)g_settings.textAreaLeftMargin;
            double rightMargin = (double)g_settings.textAreaRightMargin;
            textContainer.Margin({leftMargin, 0, rightMargin, 0});
            if (g_settings.showDebugBorders) {
                textContainer.BorderBrush(MakeBrush({0xFF, 0x00, 0xFF, 0xFF}));
                textContainer.BorderThickness({1,1,1,1});
            }
            StackPanel textStack;
            textStack.Name(kTextStackName);
            textStack.Orientation(Orientation::Vertical);
            textStack.VerticalAlignment(VerticalAlignment::Center);
            if (g_settings.enableTitleScrolling || g_settings.enableArtistScrolling) {
                textStack.HorizontalAlignment(HorizontalAlignment::Stretch);
            } else {
                textStack.HorizontalAlignment(g_settings.mirrorLayout ? HorizontalAlignment::Right : HorizontalAlignment::Left);
            }
            textStack.Spacing((double)g_settings.textSpacing);
            if (g_settings.showTrackTitle || g_settings.showTrackArtist) {
                TextBlock titleBlock{nullptr};
                TextBlock artistBlock{nullptr};
                if (g_settings.showTrackTitle) {
                    titleBlock = TextBlock();
                    titleBlock.Name(kTitleBlockName);
                    titleBlock.FontSize((double)g_settings.titleFontSize);
                    std::wstring titleFontName = g_settings.titleFont.empty() ? g_settings.titleFontFamily : g_settings.titleFont;
                    if (!titleFontName.empty()) {
                        try {
                            titleBlock.FontFamily(Media::FontFamily(titleFontName));
                        } catch (...) {}
                    }
                    if (!g_settings.titleFontWeight.empty()) {
                        try {
                            auto fontWeight = Markup::XamlBindingHelper::ConvertValue(
                                winrt::Windows::UI::Xaml::Interop::TypeName{
                                    winrt::hstring{L"Windows.UI.Text.FontWeight"},
                                    winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata
                                },
                                winrt::box_value(g_settings.titleFontWeight))
                                .as<winrt::Windows::UI::Text::FontWeight>();
                            titleBlock.FontWeight(fontWeight);
                        } catch (...) {}
                    }
                    if (!g_settings.titleFontStyle.empty()) {
                        try {
                            auto fontStyle = Markup::XamlBindingHelper::ConvertValue(
                                winrt::Windows::UI::Xaml::Interop::TypeName{
                                    winrt::hstring{L"Windows.UI.Text.FontStyle"},
                                    winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata
                                },
                                winrt::box_value(g_settings.titleFontStyle))
                                .as<winrt::Windows::UI::Text::FontStyle>();
                            titleBlock.FontStyle(fontStyle);
                        } catch (...) {}
                    }
                    if (g_settings.titleCharacterSpacing != 0) {
                        titleBlock.CharacterSpacing(g_settings.titleCharacterSpacing);
                    }
                    titleBlock.Foreground(MakeBrush(textClr));
                    titleBlock.TextWrapping(TextWrapping::NoWrap);
                    titleBlock.TextTrimming(TextTrimming::CharacterEllipsis);
                    titleBlock.TextAlignment(g_settings.mirrorLayout ? TextAlignment::Right : TextAlignment::Left);
                }
                if (g_settings.showTrackArtist) {
                    artistBlock = TextBlock();
                    artistBlock.Name(kArtistBlockName);
                    artistBlock.FontSize((double)g_settings.artistFontSize);
                    std::wstring artistFontName = g_settings.artistFont.empty() ? g_settings.artistFontFamily : g_settings.artistFont;
                    if (!artistFontName.empty()) {
                        try {
                            artistBlock.FontFamily(Media::FontFamily(artistFontName));
                        } catch (...) {}
                    }
                    if (!g_settings.artistFontWeight.empty()) {
                        try {
                            auto fontWeight = Markup::XamlBindingHelper::ConvertValue(
                                winrt::Windows::UI::Xaml::Interop::TypeName{
                                    winrt::hstring{L"Windows.UI.Text.FontWeight"},
                                    winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata
                                },
                                winrt::box_value(g_settings.artistFontWeight))
                                .as<winrt::Windows::UI::Text::FontWeight>();
                            artistBlock.FontWeight(fontWeight);
                        } catch (...) {}
                    }
                    if (!g_settings.artistFontStyle.empty()) {
                        try {
                            auto fontStyle = Markup::XamlBindingHelper::ConvertValue(
                                winrt::Windows::UI::Xaml::Interop::TypeName{
                                    winrt::hstring{L"Windows.UI.Text.FontStyle"},
                                    winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata
                                },
                                winrt::box_value(g_settings.artistFontStyle))
                                .as<winrt::Windows::UI::Text::FontStyle>();
                            artistBlock.FontStyle(fontStyle);
                        } catch (...) {}
                    }
                    if (g_settings.artistCharacterSpacing != 0) {
                        artistBlock.CharacterSpacing(g_settings.artistCharacterSpacing);
                    }
                    artistBlock.Foreground(MakeBrush(artistClr));
                    artistBlock.TextWrapping(TextWrapping::NoWrap);
                    artistBlock.TextTrimming(TextTrimming::CharacterEllipsis);
                    artistBlock.TextAlignment(g_settings.mirrorLayout ? TextAlignment::Right : TextAlignment::Left);
                }
                auto MakeScrollView = [&](Canvas& scrollView, TextBlock& block, const wchar_t* viewName, const wchar_t* blockName, const wchar_t* cloneName) {
                    scrollView = Canvas();
                    scrollView.Name(viewName);
                    scrollView.VerticalAlignment(VerticalAlignment::Center);
                    scrollView.HorizontalAlignment(g_settings.mirrorLayout ? HorizontalAlignment::Right : HorizontalAlignment::Left);
                    scrollView.Width(100.0);
                    block.Name(blockName);
                    block.TextTrimming(TextTrimming::None);
                    block.TextWrapping(TextWrapping::NoWrap);
                    Canvas::SetLeft(block, 0.0);
                    Canvas::SetTop(block, 0.0);
                    scrollView.Children().Append(block);
                    if (g_settings.scrollMode == L"loop") {
                        TextBlock clone;
                        clone.Name(cloneName);
                        clone.Text(block.Text());
                        clone.FontSize(block.FontSize());
                        clone.FontFamily(block.FontFamily());
                        clone.FontWeight(block.FontWeight());
                        clone.FontStyle(block.FontStyle());
                        clone.CharacterSpacing(block.CharacterSpacing());
                        clone.Foreground(block.Foreground());
                        clone.TextWrapping(TextWrapping::NoWrap);
                        clone.TextTrimming(TextTrimming::None);
                        clone.TextAlignment(block.TextAlignment());
                        Canvas::SetLeft(clone, 9999.0);
                        Canvas::SetTop(clone, 0.0);
                        scrollView.Children().Append(clone);
                    }
                    auto geo = winrt::Windows::UI::Xaml::Media::RectangleGeometry();
                    scrollView.Clip(geo);
                    block.SizeChanged([scrollView, geo](winrt::Windows::Foundation::IInspectable const&, SizeChangedEventArgs const& e) mutable {
                        try {
                            double h = e.NewSize().Height;
                            if (h < 1.0) h = 16.0;
                            double w = scrollView.Width();
                            scrollView.Height(h);
                            geo.Rect({0, 0, (float)w, (float)h});
                        } catch (...) {}
                    });
                };
                if (g_settings.swapTitleArtist) {
                    if (artistBlock) {
                        if (g_settings.enableArtistScrolling) {
                            Canvas artistScrollView;
                            MakeScrollView(artistScrollView, artistBlock, kArtistScrollViewName, kArtistBlockName, kArtistCloneName);
                            textStack.Children().Append(artistScrollView);
                        } else {
                            if (g_settings.enableTitleScrolling && g_settings.textAreaMaxWidth > 0) {
                                artistBlock.MaxWidth((double)g_settings.textAreaMaxWidth);
                            }
                            textStack.Children().Append(artistBlock);
                        }
                    }
                    if (titleBlock) {
                        if (g_settings.enableTitleScrolling) {
                            Canvas titleScrollView;
                            MakeScrollView(titleScrollView, titleBlock, kTitleScrollViewName, kTitleBlockName, kTitleCloneName);
                            textStack.Children().Append(titleScrollView);
                        } else {
                            if (g_settings.enableArtistScrolling && g_settings.textAreaMaxWidth > 0) {
                                titleBlock.MaxWidth((double)g_settings.textAreaMaxWidth);
                            }
                            textStack.Children().Append(titleBlock);
                        }
                    }
                } else {
                    if (titleBlock) {
                        if (g_settings.enableTitleScrolling) {
                            Canvas titleScrollView;
                            MakeScrollView(titleScrollView, titleBlock, kTitleScrollViewName, kTitleBlockName, kTitleCloneName);
                            textStack.Children().Append(titleScrollView);
                        } else {
                            if (g_settings.enableArtistScrolling && g_settings.textAreaMaxWidth > 0) {
                                titleBlock.MaxWidth((double)g_settings.textAreaMaxWidth);
                            }
                            textStack.Children().Append(titleBlock);
                        }
                    }
                    if (artistBlock) {
                        if (g_settings.enableArtistScrolling) {
                            Canvas artistScrollView;
                            MakeScrollView(artistScrollView, artistBlock, kArtistScrollViewName, kArtistBlockName, kArtistCloneName);
                            textStack.Children().Append(artistScrollView);
                        } else {
                            if (g_settings.enableTitleScrolling && g_settings.textAreaMaxWidth > 0) {
                                artistBlock.MaxWidth((double)g_settings.textAreaMaxWidth);
                            }
                            textStack.Children().Append(artistBlock);
                        }
                    }
                }
            }
            textContainer.Child(textStack);
            Grid::SetColumn(textContainer, 1);
            panel.Children().Append(textContainer);
        }
        if (g_settings.showMediaButtons) {
            StackPanel ctrlPanel;
            ctrlPanel.Orientation(Orientation::Horizontal);
            ctrlPanel.Spacing((double)g_settings.buttonSpacing);
            ctrlPanel.VerticalAlignment(VerticalAlignment::Center);
            ctrlPanel.HorizontalAlignment(buttonsLeft ? HorizontalAlignment::Left : HorizontalAlignment::Right);
            std::vector<MediaButtonConfig> currentButtons;
            try {
                std::lock_guard<std::mutex> lock(g_mediaButtonsMutex);
                if (!g_mediaButtons.empty()) {
                    currentButtons = g_mediaButtons;
                } else {
                    currentButtons = {
                        {MediaButtonType::Previous, 1},
                        {MediaButtonType::PlayPause, 2},
                        {MediaButtonType::Next, 3}
                    };
                }
            } catch (const std::exception& e) {
                Wh_Log(L"CreatePlayerGrid: Exception accessing media buttons (std::exception), using defaults");
                currentButtons = {
                    {MediaButtonType::Previous, 1},
                    {MediaButtonType::PlayPause, 2},
                    {MediaButtonType::Next, 3}
                };
            } catch (...) {
                Wh_Log(L"CreatePlayerGrid: Unknown exception accessing media buttons, using defaults");
                currentButtons = {
                    {MediaButtonType::Previous, 1},
                    {MediaButtonType::PlayPause, 2},
                    {MediaButtonType::Next, 3}
                };
            }
            bool hasButtons = !currentButtons.empty();
            if (hasButtons) {
                try {
                    ctrlPanel.Margin({(double)g_settings.mediaButtonsLeftMargin, 0, (double)g_settings.mediaButtonsRightMargin, 0});
                } catch (...) {
                    Wh_Log(L"CreatePlayerGrid: Exception setting control panel margin");
                }
            }
            if (g_settings.showDebugBorders) {
                try {
                    Border ctrlDebugBorder;
                    ctrlDebugBorder.BorderBrush(MakeBrush({0xFF, 0xFF, 0x00, 0xFF}));
                    ctrlDebugBorder.BorderThickness({1,1,1,1});
                    Grid::SetColumn(ctrlDebugBorder, buttonsLeft ? 0 : 3);
                    panel.Children().Append(ctrlDebugBorder);
                } catch (...) {
                    Wh_Log(L"CreatePlayerGrid: Exception creating debug border");
                }
            }
            for (size_t i = 0; i < currentButtons.size(); i++) {
                try {
                    const auto& btnCfg = currentButtons[i];
                    auto btn = MakeControlButton(btnCfg.cmd, false, buttonClr);
                    if (!btn) {
                        Wh_Log(L"CreatePlayerGrid: MakeControlButton returned null for button %zu", i);
                        continue;
                    }
                    switch (btnCfg.type) {
                        case MediaButtonType::Previous:
                            btn.Name(kPrevBtnName);
                            break;
                        case MediaButtonType::PlayPause:
                            btn.Name(kPlayBtnName);
                            break;
                        case MediaButtonType::Next:
                            btn.Name(kNextBtnName);
                            break;
                        case MediaButtonType::Rewind5s:
                            btn.Name(kRewindBtnName);
                            break;
                        case MediaButtonType::Forward5s:
                            btn.Name(kForwardBtnName);
                            break;
                        case MediaButtonType::Shuffle:
                            btn.Name(kShuffleBtnName);
                            break;
                        case MediaButtonType::Repeat:
                            btn.Name(kRepeatBtnName);
                            break;
                        case MediaButtonType::SwitchSessions:
                            btn.Name(kSwitchSessionsBtnName);
                            break;
                        default:
                            Wh_Log(L"CreatePlayerGrid: Unknown button type %d", static_cast<int>(btnCfg.type));
                            continue;
                    }
                    ctrlPanel.Children().Append(btn);
                } catch (const winrt::hresult_error& e) {
                    Wh_Log(L"CreatePlayerGrid: WinRT exception creating button %zu: 0x%08X", i, static_cast<uint32_t>(e.code()));
                } catch (const std::exception& e) {
                    Wh_Log(L"CreatePlayerGrid: std::exception creating button %zu", i);
                } catch (...) {
                    Wh_Log(L"CreatePlayerGrid: Unknown exception creating button %zu, skipping", i);
                }
            }
            if (g_settings.timeDisplayMode != 0 && hasButtons) {
                try {
                    TextBlock timeText;
                    timeText.Name(kTimeTextName);
                    timeText.FontSize((double)g_settings.artistFontSize);
                    std::wstring timeFont = g_settings.artistFont.empty() ? g_settings.artistFontFamily : g_settings.artistFont;
                    if (!timeFont.empty()) {
                        try { timeText.FontFamily(Media::FontFamily(timeFont)); } catch (...) {}
                    }
                    timeText.Foreground(MakeBrush(artistClr));
                    timeText.VerticalAlignment(VerticalAlignment::Center);
                    timeText.TextWrapping(TextWrapping::NoWrap);
                    timeText.IsHitTestVisible(false);
                    timeText.Visibility(Visibility::Collapsed);
                    timeText.Margin({0, 0, 2, 0});
                    ctrlPanel.Children().InsertAt(0, timeText);
                } catch (...) {
                    Wh_Log(L"CreatePlayerGrid: Exception creating time text");
                }
            }
            if (buttonsLeft) {
                Grid::SetColumn(ctrlPanel, 0);
            } else {
                Grid::SetColumn(ctrlPanel, 3);
            }
            if (hasButtons) {
                panel.Children().Append(ctrlPanel);
            }
        }
        if (g_settings.vizEnabled && !g_settings.vizOverlay) {
            try {
                auto vizEl = BuildVisualizerElement();
                if (vizEl) {
                    bool left = (g_settings.vizPosition == L"left");
                    if (g_settings.mirrorLayout) left = !left;
                    ColumnDefinition vcol;
                    vcol.Width({1.0, GridUnitType::Auto});
                    if (left) {
                        panel.ColumnDefinitions().InsertAt(0, vcol);
                        auto kids = panel.Children();
                        for (uint32_t k = 0; k < kids.Size(); k++) {
                            if (auto fe = kids.GetAt(k).try_as<FrameworkElement>())
                                Grid::SetColumn(fe, Grid::GetColumn(fe) + 1);
                        }
                        Grid::SetColumn(vizEl, 0);
                    } else {
                        panel.ColumnDefinitions().Append(vcol);
                        Grid::SetColumn(vizEl, (int)panel.ColumnDefinitions().Size() - 1);
                    }
                    panel.Children().Append(vizEl);
                }
            } catch (...) {
                Wh_Log(L"BuildPlayerGrid: Exception adding inline visualizer");
            }
        }
        Grid wrapper;
        wrapper.Name(kGridName);
        wrapper.VerticalAlignment(g_settings.fullHeightHitArea ? VerticalAlignment::Stretch : VerticalAlignment::Center);
        wrapper.HorizontalAlignment(HorizontalAlignment::Left);
        AddLayoutAnchorOverlay(wrapper, L"FluentMedia_DebugPlayerAnchors", {0xD0, 0xFF, 0x50, 0x50});
        try {
            if (g_settings.enableSmoothPositionAnimation) {
                TransitionCollection transitions;
                RepositionThemeTransition marginTransition;
                transitions.Append(marginTransition);
                wrapper.Transitions(transitions);
            }
        } catch (...) {}
        if (hasTextOrButtons && g_settings.playerMinWidth > 0) {
            wrapper.MinWidth((double)g_settings.playerMinWidth);
        }
        if (g_settings.playerMaxWidth > 0) {
            wrapper.MaxWidth((double)g_settings.playerMaxWidth);
        }

        wrapper.Background(MakeBrush({0x00, 0, 0, 0}));

        Canvas::SetZIndex(backgroundBorder, 0);
        Canvas::SetZIndex(playerButton, 1);    
        Canvas::SetZIndex(panel, 2);           
        wrapper.Children().Append(backgroundBorder);
        wrapper.Children().Append(playerButton);
        if (g_settings.vizOverlay) {
            try {
                auto overlayViz = BuildOverlayVisualizer(panel, phMin, phMax);
                Canvas::SetZIndex(overlayViz, 1);
                wrapper.Children().Append(overlayViz);
            } catch (...) {
                Wh_Log(L"BuildPlayerGrid: Exception adding behind-widget visualizer");
            }
        }
        wrapper.Children().Append(panel);
        if (g_settings.showProgressBar) {
            try {
                auto progress = BuildProgressLayer(phMin, phMax);
                Canvas::SetZIndex(progress, 3);
                wrapper.Children().Append(progress);
            } catch (...) {
                Wh_Log(L"BuildPlayerGrid: Exception adding progress bar");
            }
        }
        ApplyFluentMediaButtonStyle(playerButton);
        if (!g_settings.showDebugBorders) {
            playerButton.BorderThickness({1, 1, 1, 1});
        }
        auto isPressed = std::make_shared<bool>(false);
        auto isHovered = std::make_shared<bool>(false);
        auto playerNormalBg = MakeBackgroundBrush();
        auto updatePlayerVisualState = [playerButton, playerNormalBg, isPressed, isHovered]() {
            bool hovered = *isHovered || g_miniPlayerFlyoutOpen;
            ApplyPlayerButtonState(playerButton, playerNormalBg, hovered, *isPressed);
        };
        g_playerButtonStateUpdater = updatePlayerVisualState;
        RunWhenButtonReady(playerButton, [playerButton, playerNormalBg]() {
            try {
                SetupPlayerCommonStates(playerButton, playerNormalBg);
                GoToCommonState(playerButton, IsHoverEffectEnabled(g_settings.playerHoverEffectMode), false, false);
            } catch (...) {}
        });
        wrapper.Loaded([playerButton, playerNormalBg](auto const&, auto const&) {
            try {
                SetupPlayerCommonStates(playerButton, playerNormalBg);
                GoToCommonState(playerButton, IsHoverEffectEnabled(g_settings.playerHoverEffectMode), false, false);
            } catch (...) {}
        });
        panel.PointerEntered([isHovered, updatePlayerVisualState](auto const&, auto const&) {
            *isHovered = true;
            updatePlayerVisualState();
        });
        panel.PointerExited([wrapper, isHovered, updatePlayerVisualState](auto const&, PointerRoutedEventArgs const& e) {
            bool stillInside = false;
            try {
                auto pos = e.GetCurrentPoint(wrapper).Position();
                auto bounds = wrapper.RenderSize();
                stillInside = pos.X >= 0 && pos.X <= bounds.Width && pos.Y >= 0 && pos.Y <= bounds.Height;
            } catch (...) {}
            if (!stillInside) {
                *isHovered = false;
                updatePlayerVisualState();
            }
        });
    wrapper.PointerEntered([isHovered, updatePlayerVisualState](auto const&, auto const&) mutable {
        *isHovered = true;
        updatePlayerVisualState();
    });
    wrapper.PointerExited([isHovered, updatePlayerVisualState](auto const&, auto const&) mutable {
        *isHovered = false;
        updatePlayerVisualState();
    });
    wrapper.PointerPressed([isPressed, updatePlayerVisualState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) mutable {
        if (auto elem = sender.template try_as<UIElement>()) {
            elem.CapturePointer(e.Pointer());
        }
        *isPressed = true;
        updatePlayerVisualState();
    });
    auto wrapperDblClickLastTime = std::make_shared<ULONGLONG>(0);
    auto wrapperDblClickLastKind = std::make_shared<winrt::Windows::UI::Input::PointerUpdateKind>(
        winrt::Windows::UI::Input::PointerUpdateKind::Other);
    wrapper.PointerReleased([isPressed, isHovered, updatePlayerVisualState, wrapperDblClickLastTime, wrapperDblClickLastKind](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) mutable {
        *isPressed = false;
        bool actuallyHovered = false;
        if (auto elem = sender.template try_as<UIElement>()) {
            elem.ReleasePointerCapture(e.Pointer());
            try {
                auto pointerPoint = e.GetCurrentPoint(elem);
                auto bounds = elem.RenderSize();
                auto pos = pointerPoint.Position();
                actuallyHovered = (pos.X >= 0 && pos.X <= bounds.Width && pos.Y >= 0 && pos.Y <= bounds.Height);
            } catch (...) { actuallyHovered = false; }
        }
        *isHovered = actuallyHovered;
        updatePlayerVisualState();
        if (g_unloading || e.Handled()) return;
        if (actuallyHovered) {
            auto kind = e.GetCurrentPoint(nullptr).Properties().PointerUpdateKind();
            auto fe = sender.template try_as<FrameworkElement>();
            ULONGLONG now = GetTickCount64();
            UINT dblClickMs = GetDoubleClickTime();
            bool isDouble = (kind == *wrapperDblClickLastKind) &&
                            (now - *wrapperDblClickLastTime) <= dblClickMs;
            *wrapperDblClickLastTime = isDouble ? 0 : now;
            *wrapperDblClickLastKind = kind;
            using Kind = winrt::Windows::UI::Input::PointerUpdateKind;
            if (kind == Kind::LeftButtonReleased) {
                if (isDouble) ExecuteMediaAction(g_settings.playerLeftDoubleClick, fe);
                else          ExecuteMediaAction(g_settings.playerLeftClick, fe);
            } else if (kind == Kind::RightButtonReleased) {
                if (isDouble) ExecuteMediaAction(g_settings.playerRightDoubleClick, fe);
                else          ExecuteMediaAction(g_settings.playerRightClick, fe);
            } else if (kind == Kind::MiddleButtonReleased) {
                if (isDouble) ExecuteMediaAction(g_settings.playerMiddleDoubleClick, fe);
                else          ExecuteMediaAction(g_settings.playerMiddleClick, fe);
            }
        }
    });
    wrapper.PointerCanceled([isPressed, isHovered, updatePlayerVisualState](auto const&, auto const&) mutable {
        *isPressed = false;
        *isHovered = false;
        updatePlayerVisualState();
    });
    wrapper.PointerCaptureLost([isPressed, isHovered, updatePlayerVisualState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) mutable {
        *isPressed = false;
        if (auto elem = sender.template try_as<UIElement>()) {
            try {
                auto pointerPoint = e.GetCurrentPoint(elem);
                auto bounds = elem.RenderSize();
                auto pos = pointerPoint.Position();
                *isHovered = (pos.X >= 0 && pos.X <= bounds.Width && pos.Y >= 0 && pos.Y <= bounds.Height);
            } catch (...) { *isHovered = false; }
        }
        updatePlayerVisualState();
    });
        wrapper.Tag(winrt::box_value(winrt::hstring(L"FluentMediaBarWrapper")));
        wrapper.PointerWheelChanged([](auto const&, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
            if (g_unloading) return;
            auto action = g_settings.playerWheelAction;
            if (action == L"none") return;
            auto props = e.GetCurrentPoint(nullptr).Properties();
            int delta = props.MouseWheelDelta();
            if (action == L"switch_tracks") {
                if (delta > 0) SendMediaCommandAsync(1);
                else if (delta < 0) SendMediaCommandAsync(3);
                DispatchMediaUpdate();
            } else if (action == L"switch_tracks_inverted") {
                if (delta > 0) SendMediaCommandAsync(3);
                else if (delta < 0) SendMediaCommandAsync(1);
                DispatchMediaUpdate();
            } else if (action == L"switch_sessions") {
                if (delta != 0) SwitchMediaSession();
            } else if (action == L"system_sound") {
                SpawnTrackedWorker([delta]() { ChangeSystemVolume(delta > 0); });
            } else if (action == L"app_sound") {
                SpawnTrackedWorker([delta]() {
                    winrt::init_apartment(winrt::apartment_type::multi_threaded);
                    std::wstring aumid;
                    {
                        GlobalSystemMediaTransportControlsSession sessionCopy{nullptr};
                        {
                            std::lock_guard<std::mutex> lk(g_sessionMtx);
                            sessionCopy = g_currentSession;
                        }
                        if (sessionCopy) {
                            try {
                                aumid = std::wstring(sessionCopy.SourceAppUserModelId());
                            } catch (...) {}
                        }
                    }
                    if (!aumid.empty()) {
                        float volumeDelta = (delta > 0) ? 0.02f : -0.02f;
                        AdjustAppVolumeByAUMID(aumid, volumeDelta);
                    }
                    winrt::uninit_apartment();
                });
            }
            e.Handled(true);
        });
        try {
            winrt::Windows::UI::Xaml::Interop::TypeName gridType;
            gridType.Name = L"Windows.UI.Xaml.Controls.Grid";
            gridType.Kind = winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata;
            winrt::Windows::UI::Xaml::Style wrapperStyle(gridType);
            wrapper.Style(wrapperStyle);
        } catch (...) {}
        try {
            ToolTip tt;
            TextBlock ttText;
            ttText.TextWrapping(TextWrapping::Wrap);
            ttText.MaxWidth(300);
            tt.Content(ttText);
            ToolTipService::SetToolTip(wrapper, tt);
            g_playerToolTip = tt;
        } catch (...) {}
        return wrapper;
    } catch (...) {
        Wh_Log(L"BuildPlayerGrid: Exception occurred");
        return nullptr;
    }
}
struct InjectionTarget {
    Grid grid;
    int  insertCol = 0;
};
static const wchar_t kMediaIslandName[] = L"TaskbarIsland_Media";
static Border g_mediaIsland{nullptr};
static winrt::Windows::UI::Xaml::Shapes::Rectangle g_mediaDivider{nullptr};
static int RemovePlayerGridChildren(Grid const& targetGrid) {
    if (!targetGrid) return -1;
    int firstCol = -1;
    for (int i = (int)targetGrid.Children().Size() - 1; i >= 0; --i) {
        auto fe = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
        if (fe && fe.Name() == kMediaIslandName) {
            try { targetGrid.Children().RemoveAt(i); } catch (...) {}
            continue;
        }
        if (fe && fe.Name() == kGridName) {
            if (firstCol < 0) firstCol = Grid::GetColumn(fe);
            try { targetGrid.Children().RemoveAt(i); } catch (...) {}
        }
    }
    return firstCol;
}
static void RemoveAnchorDebugOverlays(Grid const& targetGrid) {
    if (!targetGrid) return;
    for (int i = (int)targetGrid.Children().Size() - 1; i >= 0; --i) {
        auto fe = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
        if (fe && fe.Name() == kAnchorOverlayName) {
            try { targetGrid.Children().RemoveAt(i); } catch (...) {}
        }
    }
}
static void UpdateAnchorDebugOverlay(Grid const& targetGrid, FrameworkElement const& targetElem) {
    if (!targetGrid) return;
    if (!g_settings.showLayoutAnchors || !targetElem) {
        RemoveAnchorDebugOverlays(targetGrid);
        return;
    }
    try {
        Border overlay{nullptr};
        for (uint32_t i = 0; i < targetGrid.Children().Size(); ++i) {
            auto fe = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
            if (fe && fe.Name() == kAnchorOverlayName) {
                overlay = fe.try_as<Border>();
                break;
            }
        }
        if (!overlay) {
            overlay = Border();
            overlay.Name(kAnchorOverlayName);
            overlay.IsHitTestVisible(false);
            overlay.BorderBrush(MakeBrush({0xE0, 0x00, 0xA2, 0xFF}));
            overlay.BorderThickness({2,2,2,2});
            overlay.Background(MakeBrush({0x20, 0x00, 0xA2, 0xFF}));
            overlay.HorizontalAlignment(HorizontalAlignment::Left);
            overlay.VerticalAlignment(VerticalAlignment::Top);
            Canvas::SetZIndex(overlay, 5001);
            targetGrid.Children().Append(overlay);
        }
        auto transform = targetElem.TransformToVisual(targetGrid);
        auto point = transform.TransformPoint({0, 0});
        overlay.Width(std::max(1.0, targetElem.ActualWidth()));
        overlay.Height(std::max(1.0, targetElem.ActualHeight()));
        overlay.Margin({point.X, point.Y, 0, 0});
        overlay.Visibility(Visibility::Visible);
    } catch (...) {
        RemoveAnchorDebugOverlays(targetGrid);
    }
}
static const wchar_t* const kStartButtonNames[] = {
    L"StartButton",
    L"StartMenuButton",
    L"StartMenuLaunchButton", 
    L"LaunchListButton",
};
static Grid FindTaskbarRootGrid(FrameworkElement const& root) {
    FrameworkElement taskbarFrame = nullptr;
    int count = VisualTreeHelper::GetChildrenCount(root);
    for (int i = 0; i < count; i++) {
        auto c = VisualTreeHelper::GetChild(root, i).try_as<FrameworkElement>();
        if (c) {
            auto className = winrt::get_class_name(c);
            if (className == L"Taskbar.TaskbarFrame") {
                taskbarFrame = c;
                break;
            }
        }
    }
    if (!taskbarFrame) {
        return nullptr;
    }
    auto rootGrid = FindChildByName(taskbarFrame, L"RootGrid");
    return rootGrid ? rootGrid.try_as<Grid>() : nullptr;
}
static FrameworkElement FindElementInRepeater(FrameworkElement const& repeater, const wchar_t* const* names, int nameCount) {
    if (!repeater) return nullptr;
    int childCount = VisualTreeHelper::GetChildrenCount(repeater);
    for (int i = 0; i < childCount; i++) {
        auto child = VisualTreeHelper::GetChild(repeater, i).try_as<FrameworkElement>();
        if (!child) continue;
        for (int j = 0; j < nameCount; j++) {
            if (child.Name() == names[j]) return child;
        }
    }
    for (int i = 0; i < childCount; i++) {
        auto child = VisualTreeHelper::GetChild(repeater, i).try_as<FrameworkElement>();
        if (!child) continue;
        int subChildCount = VisualTreeHelper::GetChildrenCount(child);
        for (int k = 0; k < subChildCount; k++) {
            auto subChild = VisualTreeHelper::GetChild(child, k).try_as<FrameworkElement>();
            if (!subChild) continue;
            for (int j = 0; j < nameCount; j++) {
                if (subChild.Name() == names[j]) return subChild;
            }
        }
    }
    return nullptr;
}
static FrameworkElement FindElementByClassName(FrameworkElement const& parent, const wchar_t* className) {
    if (!parent) return nullptr;
    int childCount = VisualTreeHelper::GetChildrenCount(parent);
    for (int i = 0; i < childCount; i++) {
        auto child = VisualTreeHelper::GetChild(parent, i).try_as<FrameworkElement>();
        if (!child) continue;
        auto childClassName = winrt::get_class_name(child);
        if (childClassName == className) return child;
    }
    return nullptr;
}
static FrameworkElement FindNthElementByClassName(FrameworkElement const& parent, const wchar_t* className, int index) {
    if (!parent) return nullptr;
    int foundCount = 0;
    int childCount = VisualTreeHelper::GetChildrenCount(parent);
    for (int i = 0; i < childCount; i++) {
        auto child = VisualTreeHelper::GetChild(parent, i).try_as<FrameworkElement>();
        if (!child) continue;
        auto childClassName = winrt::get_class_name(child);
        if (childClassName == className) {
            if (foundCount == index) return child;
            foundCount++;
        }
    }
    return nullptr;
}
static FrameworkElement FindChildByClassName(FrameworkElement const& parent, const wchar_t* className, int depth = 32) {
    if (!parent || depth <= 0) return nullptr;
    int childCount = VisualTreeHelper::GetChildrenCount(parent);
    for (int i = 0; i < childCount; i++) {
        auto child = VisualTreeHelper::GetChild(parent, i).try_as<FrameworkElement>();
        if (!child) continue;
        if (winrt::get_class_name(child) == className) return child;
        if (auto found = FindChildByClassName(child, className, depth - 1)) return found;
    }
    return nullptr;
}
static double FindLeftmostVisibleChildX(FrameworkElement const& parent, UIElement const& relativeTo, int depth = 3) {
    if (!parent || !relativeTo || depth < 0) return -1.0;
    double leftmost = -1.0;
    int childCount = VisualTreeHelper::GetChildrenCount(parent);
    for (int i = 0; i < childCount; i++) {
        auto child = VisualTreeHelper::GetChild(parent, i).try_as<FrameworkElement>();
        if (!child) continue;
        try {
            if (child.Visibility() == Visibility::Visible && child.ActualWidth() > 1.0) {
                auto transform = child.TransformToVisual(relativeTo);
                auto point = transform.TransformPoint({0, 0});
                if (point.X >= 0.0 && (leftmost < 0.0 || point.X < leftmost))
                    leftmost = point.X;
            }
        } catch (...) {}
        double nested = FindLeftmostVisibleChildX(child, relativeTo, depth - 1);
        if (nested >= 0.0 && (leftmost < 0.0 || nested < leftmost))
            leftmost = nested;
    }
    return leftmost;
}
static FrameworkElement FindTrayElement(FrameworkElement const& trayGrid, FrameworkElement const& root, const wchar_t* name) {
    auto elem = FindChildByName(trayGrid, name);
    if (!elem) elem = FindChildByName(root, name);
    return elem;
}
static bool IsStartButtonModActive(FrameworkElement const& root) {
    try {
        auto rootGrid = FindTaskbarRootGrid(root);
        if (!rootGrid) return false;
        auto repeater = FindChildByName(rootGrid, L"TaskbarFrameRepeater");
        if (!repeater) return false;
        static const wchar_t* kStartNames[] = {L"StartButton"};
        auto startButton = FindElementInRepeater(repeater, kStartNames, 1);
        if (!startButton) return false;
        auto margin = startButton.Margin();
        return margin.Right < -10.0;
    } catch (...) {
        return false;
    }
}
static double GetStartButtonAdjustment(FrameworkElement const& root) {
    try {
        auto rootGrid = FindTaskbarRootGrid(root);
        if (!rootGrid) return 0.0;
        auto repeater = FindChildByName(rootGrid, L"TaskbarFrameRepeater");
        if (!repeater) return 0.0;
        static const wchar_t* kStartNames[] = {L"StartButton"};
        auto startButton = FindElementInRepeater(repeater, kStartNames, 1);
        if (!startButton) return 0.0;
        return startButton.ActualWidth();
    } catch (...) {
        return 0.0;
    }
}
static InjectionTarget ResolveInjectionTarget(
    FrameworkElement const& root,
    std::wstring_view position)
{
    auto trayFrame = FindChildByName(root, L"SystemTrayFrameGrid");
    if (auto trayGrid = trayFrame ? trayFrame.try_as<Grid>() : nullptr) {
        int col = -1;
        if      (position == L"tray_right")
            col = (int)trayGrid.ColumnDefinitions().Size();
        else if (position == L"tray_left")
            col = 0;
        else if (position == L"tray_before_clock") {
            auto clockBtn = FindChildByName(trayGrid, L"NotificationCenterButton");
            if (!clockBtn) clockBtn = FindChildByName(root, L"NotificationCenterButton");
            col = clockBtn ? Grid::GetColumn(clockBtn) : -1;
        }
        else if (position == L"tray_after_clock") {
            auto showDesktop = FindChildByName(trayGrid, L"ShowDesktopStack");
            if (!showDesktop) showDesktop = FindChildByName(root, L"ShowDesktopStack");
            col = showDesktop ? Grid::GetColumn(showDesktop) : -1;
        }
        else if (position == L"tray_before_omni_left") {
            auto omniBtn = FindChildByName(trayGrid, L"ControlCenterButton");
            if (!omniBtn) omniBtn = FindChildByName(root, L"ControlCenterButton");
            col = omniBtn ? Grid::GetColumn(omniBtn) : -1;
        }
        else if (position == L"tray_before_omni_right") {
            auto omniBtn = FindChildByName(trayGrid, L"ControlCenterButton");
            if (!omniBtn) omniBtn = FindChildByName(root, L"ControlCenterButton");
            if (omniBtn) col = Grid::GetColumn(omniBtn) + 1;
            else col = -1;
        }
        else if (position == L"tray_language_left") {
            auto languageBtn = FindTrayElement(trayGrid, root, L"NonActivatableStack");
            col = languageBtn ? Grid::GetColumn(languageBtn) : -1;
        }
        else if (position == L"tray_language_right") {
            auto languageBtn = FindTrayElement(trayGrid, root, L"NonActivatableStack");
            col = languageBtn ? Grid::GetColumn(languageBtn) + 1 : -1;
        }
        else if (position == L"tray_hidden_icons_left") {
            auto hiddenIconsBtn = FindTrayElement(trayGrid, root, L"NotifyIconStack");
            col = hiddenIconsBtn ? Grid::GetColumn(hiddenIconsBtn) : -1;
        }
        else if (position == L"tray_hidden_icons_right") {
            auto hiddenIconsBtn = FindTrayElement(trayGrid, root, L"NotifyIconStack");
            col = hiddenIconsBtn ? Grid::GetColumn(hiddenIconsBtn) + 1 : -1;
        }
        else if (position == L"tray_icons_left") {
            auto trayIcons = FindTrayElement(trayGrid, root, L"NotificationAreaIcons");
            col = trayIcons ? Grid::GetColumn(trayIcons) : -1;
        }
        else if (position == L"tray_icons_right") {
            auto trayIcons = FindTrayElement(trayGrid, root, L"NotificationAreaIcons");
            col = trayIcons ? Grid::GetColumn(trayIcons) + 1 : -1;
        }
        else if (position == L"tray_after_showdesktop_left") {
            auto showDesktop = FindChildByName(trayGrid, L"ShowDesktopStack");
            if (!showDesktop) showDesktop = FindChildByName(root, L"ShowDesktopStack");
            col = showDesktop ? Grid::GetColumn(showDesktop) : -1;
        }
        else if (position == L"tray_after_showdesktop_right") {
            auto showDesktop = FindChildByName(trayGrid, L"ShowDesktopStack");
            if (!showDesktop) showDesktop = FindChildByName(root, L"ShowDesktopStack");
            if (showDesktop) col = Grid::GetColumn(showDesktop) + 1;
            else col = (int)trayGrid.ColumnDefinitions().Size();
        }
        if (col >= 0) {
            return {trayGrid, col};
        }
    }
    if (position == L"taskbar_left_start"  ||
        position == L"taskbar_right_start" ||
        position == L"taskbar_after_search_left"||
        position == L"taskbar_after_search_right"||
        position == L"taskbar_after_taskview_left"||
        position == L"taskbar_after_taskview_right"||
        position == L"taskbar_after_widgets_left"||
        position == L"taskbar_after_widgets_right"||
        position == L"taskbar_left_edge"   ||
        position == L"taskbar_after_system_info" ||
        position == L"taskbar_center_edge" ||
        position == L"taskbar_right_edge")
    {
        auto rootGrid = FindTaskbarRootGrid(root);
        if (!rootGrid) {
            auto tf2 = FindChildByName(root, L"SystemTrayFrameGrid");
            if (auto tg2 = tf2 ? tf2.try_as<Grid>() : nullptr)
                return {tg2, (int)tg2.ColumnDefinitions().Size()};
            return {};
        }
        return {rootGrid, -1};
    }
    return {};
}
// Taskbar System Info publishes its right edge (DIPs from the taskbar RootGrid's
// left) on Shell_TrayWnd. The player sits after it, then publishes its own right
// edge so the visualizer, which runs in another process, can sit after the player.
static const wchar_t kSystemInfoRightProp[] = L"WindhawkTaskbarSystemInfoRightDip";
static const wchar_t kPlayerRightProp[] = L"WindhawkTaskbarMediaPlayerRightDip";
static INT_PTR g_publishedPlayerRight = 0;
static HWND PrimaryTaskbarIfOurs() {
    wchar_t cls[32] = {};
    if (g_taskbarWnd && GetClassNameW(g_taskbarWnd, cls, ARRAYSIZE(cls)) &&
        _wcsicmp(cls, L"Shell_TrayWnd") == 0)
        return g_taskbarWnd;
    return nullptr;
}
static double SystemInfoRightDip() {
    HWND taskbar = PrimaryTaskbarIfOurs();
    INT_PTR edge = taskbar ? reinterpret_cast<INT_PTR>(GetPropW(taskbar, kSystemInfoRightProp)) : 0;
    return edge > 0 ? (double)edge : 0.0;
}
static void PublishVizHover(double l, double r, double t, double b) {
    static INT_PTR last[4] = {};
    INT_PTR v[4] = {(INT_PTR)std::lround(l * 4), (INT_PTR)std::lround(r * 4),
                    (INT_PTR)std::lround(t * 4), (INT_PTR)std::lround(b * 4)};
    if (!memcmp(v, last, sizeof(v))) return;
    HWND taskbar = PrimaryTaskbarIfOurs();
    if (!taskbar) taskbar = FindWindowW(L"Shell_TrayWnd", nullptr);
    if (!taskbar) return;
    static const wchar_t* names[4] = {L"WindhawkMediaVizHoverL4", L"WindhawkMediaVizHoverR4",
                                      L"WindhawkMediaVizHoverT4", L"WindhawkMediaVizHoverB4"};
    bool ok = v[1] > v[0] && v[3] > v[2] && v[0] > 0;
    for (int i = 0; i < 4; ++i) {
        if (ok) SetPropW(taskbar, names[i], reinterpret_cast<HANDLE>(v[i]));
        else RemovePropW(taskbar, names[i]);
    }
    memcpy(last, v, sizeof(v));
}
static void PublishPlayerRight(INT_PTR right) {
    if (right == g_publishedPlayerRight) return;
    HWND taskbar = PrimaryTaskbarIfOurs();
    if (!taskbar) taskbar = FindWindowW(L"Shell_TrayWnd", nullptr);
    if (!taskbar) return;
    if (right > 0) SetPropW(taskbar, kPlayerRightProp, reinterpret_cast<HANDLE>(right));
    else RemovePropW(taskbar, kPlayerRightProp);
    g_publishedPlayerRight = right;
}
// One gradient across the visible taskbar media buttons, left to right. Every
// glyph gets the slice of blue -> mauve that falls under it.
static void ApplyButtonGradient() {
    if (!g_settings.buttonGradient || !g_playerGrid) return;
    try {
        FrameworkElement anchor{nullptr};
        for (const wchar_t* name : {kPrevBtnName, kPlayBtnName, kNextBtnName}) {
            if ((anchor = FindChildByName(g_playerGrid, name))) break;
        }
        if (!anchor) return;
        auto panel = VisualTreeHelper::GetParent(anchor);
        if (!panel) return;
        std::vector<TextBlock> glyphs;
        int count = VisualTreeHelper::GetChildrenCount(panel);
        for (int i = 0; i < count; i++) {
            auto btn = VisualTreeHelper::GetChild(panel, i).try_as<Button>();
            if (!btn || btn.Visibility() != Visibility::Visible) continue;
            if (auto tb = btn.Content().try_as<TextBlock>()) glyphs.push_back(tb);
        }
        if (glyphs.empty()) return;
        BYTE alpha = (BYTE)((g_settings.buttonColorOpacity / 100.0) * 255);
        auto mix = [alpha](double t) {
            auto lerp = [t](int a, int b) { return (BYTE)std::lround(a + (b - a) * t); };
            return winrt::Windows::UI::Color{alpha, lerp(0x89, 0xCB), lerp(0xB4, 0xA6), lerp(0xFA, 0xF7)};
        };
        double n = (double)glyphs.size();
        for (size_t i = 0; i < glyphs.size(); i++) {
            winrt::Windows::UI::Xaml::Media::LinearGradientBrush brush;
            brush.StartPoint(winrt::Windows::Foundation::Point(0.0f, 0.5f));
            brush.EndPoint(winrt::Windows::Foundation::Point(1.0f, 0.5f));
            GradientStop a; a.Color(mix(i / n)); a.Offset(0.0);
            GradientStop b; b.Color(mix((i + 1) / n)); b.Offset(1.0);
            brush.GradientStops().Append(a);
            brush.GradientStops().Append(b);
            glyphs[i].Foreground(brush);
        }
    } catch (...) {}
}
// One island behind the player and the visualizer bars. The bars are drawn by
// the visualizer process starting at the published player edge, so the island
// adds their width from the shared Visualizer settings.
static Border MakeMediaIsland() {
    Border island;
    island.Name(kMediaIslandName);
    island.IsHitTestVisible(false);
    island.HorizontalAlignment(HorizontalAlignment::Left);
    island.VerticalAlignment(VerticalAlignment::Center);
    island.Height(34);
    island.CornerRadius({10, 10, 10, 10});
    Media::AcrylicBrush surface;
    surface.BackgroundSource(Media::AcrylicBackgroundSource::HostBackdrop);
    surface.TintColor({0xFF, 0x1E, 0x1E, 0x2E});
    surface.TintOpacity(0.85);
    surface.TintLuminosityOpacity(0.96);
    surface.FallbackColor({0xFF, 0x1E, 0x1E, 0x2E});
    island.Background(surface);
    island.BorderThickness({2, 2, 2, 2});
    island.BorderBrush(SolidColorBrush({0xE6, 0x45, 0x47, 0x5A}));
    island.Visibility(Visibility::Collapsed);
    // A thin line between the player and the bars, like the line that splits the
    // System Info block. Taskbar Styler can restyle it by name.
    winrt::Windows::UI::Xaml::Shapes::Rectangle divider;
    divider.Name(L"TaskbarIsland_MediaDivider");
    divider.Width(2);
    divider.HorizontalAlignment(HorizontalAlignment::Left);
    divider.VerticalAlignment(VerticalAlignment::Stretch);
    divider.Fill(SolidColorBrush(winrt::Windows::UI::Color{0xFF, 0x58, 0x5B, 0x70}));
    divider.IsHitTestVisible(false);
    if (g_settings.vizOverlay) divider.Visibility(Visibility::Collapsed);
    // Player hover: fills the inner band from the island's left edge to the
    // divider. Width is set in PlaceMediaIsland.
    Border hover;
    hover.Name(L"TaskbarIsland_MediaPlayerHover");
    hover.HorizontalAlignment(HorizontalAlignment::Left);
    hover.VerticalAlignment(VerticalAlignment::Stretch);
    hover.CornerRadius(g_settings.vizOverlay ? winrt::Windows::UI::Xaml::CornerRadius{8, 8, 8, 8}
                                             : winrt::Windows::UI::Xaml::CornerRadius{8, 0, 0, 8});
    hover.Background(SolidColorBrush(winrt::Windows::UI::Color{0xBF, 0x18, 0x18, 0x25}));
    hover.BorderBrush(SolidColorBrush(winrt::Windows::UI::Color{0xFF, 0x89, 0xB4, 0xFA}));
    hover.BorderThickness({1, 1, 1, 1});
    hover.IsHitTestVisible(false);
    hover.Opacity(0.0);
    try { hover.OpacityTransition(winrt::Windows::UI::Xaml::ScalarTransition()); } catch (...) {}
    Grid content;
    content.Children().Append(hover);
    content.Children().Append(divider);
    island.Child(content);
    g_mediaPlayerHover = hover;
    g_mediaDivider = divider;
    Grid::SetColumn(island, 0);
    Canvas::SetZIndex(island, 999);
    return island;
}
static double VisualizerBarsWidth() {
    if (g_settings.vizOverlay) return 0.0;  // bars sit behind the player
    int count = std::clamp(Wh_GetIntSetting(L"Visualizer.appearance.barCount"), 1, 128);
    int width = std::clamp(Wh_GetIntSetting(L"Visualizer.appearance.barWidth"), 1, 24);
    int gap = std::clamp(Wh_GetIntSetting(L"Visualizer.appearance.barGap"), 0, 24);
    return (double)(count * width + (count - 1) * gap);
}
static void PlaceMediaIsland(double left, INT_PTR playerRight, double playerContentRight) {
    if (!g_mediaIsland) return;
    if (playerRight <= 0) {
        PublishVizHover(0, 0, 0, 0);
        if (g_mediaIsland.Visibility() != Visibility::Collapsed)
            g_mediaIsland.Visibility(Visibility::Collapsed);
        return;
    }
    double right = (double)playerRight + VisualizerBarsWidth() +
        (g_settings.vizOverlay ? 2.0 + kOverlayInset : g_settings.islandPadding);
    double width = std::ceil(right - left);
    double parentX = 0.0, islandY = 0.0;
    try {
        auto p = g_mediaIsland.TransformToVisual(nullptr).TransformPoint({0, 0});
        parentX = p.X - g_mediaIsland.Margin().Left;
        islandY = p.Y;
    } catch (...) {}
    if (std::abs(g_mediaIsland.Margin().Left - left) > 0.5)
        g_mediaIsland.Margin({left, 0, 0, 0});
    if (std::isnan(g_mediaIsland.Width()) || std::abs(g_mediaIsland.Width() - width) > 0.5)
        g_mediaIsland.Width(width);
    if (g_mediaDivider && g_settings.vizOverlay) {
        // Behind-widget bars: no divider, the hover band covers the island and
        // the visualizer process has no hover box of its own.
        double inner = width - g_mediaIsland.BorderThickness().Left - g_mediaIsland.BorderThickness().Right;
        if (g_mediaPlayerHover && inner > 0 && (std::isnan(g_mediaPlayerHover.Width()) ||
                                                std::abs(g_mediaPlayerHover.Width() - inner) > 0.5))
            g_mediaPlayerHover.Width(inner);
        PublishVizHover(0, 0, 0, 0);
    } else if (g_mediaDivider) {
        // Midway between the player's content and the first bar, in island
        // coordinates (the island's 1 px border shifts its child by 1).
        double border = g_mediaIsland.BorderThickness().Left;
        double x = std::round((playerContentRight + (double)playerRight) / 2.0 - left - border - 1.0);
        double top = g_mediaIsland.BorderThickness().Top;
        double bottom = g_mediaIsland.BorderThickness().Bottom;
        auto m = g_mediaDivider.Margin();
        if (std::abs(m.Left - x) > 0.5 || std::abs(m.Top + top) > 0.1 || std::abs(m.Bottom + bottom) > 0.1)
            g_mediaDivider.Margin({x, -top, 0, -bottom});
        if (g_mediaPlayerHover && x > 0 && (std::isnan(g_mediaPlayerHover.Width()) ||
                                            std::abs(g_mediaPlayerHover.Width() - x) > 0.5))
            g_mediaPlayerHover.Width(x);
        // Visualizer hover box, in taskbar DIPs x4, for the tool process.
        double dw = std::isnan(g_mediaDivider.Width()) ? 2.0 : g_mediaDivider.Width();
        double h = std::isnan(g_mediaIsland.Height()) ? g_mediaIsland.ActualHeight() : g_mediaIsland.Height();
        PublishVizHover(parentX + left + border + x + dw,
                        parentX + left + width - g_mediaIsland.BorderThickness().Right,
                        islandY + top, islandY + h - bottom);
    }
    if (g_mediaIsland.Visibility() != Visibility::Visible)
        g_mediaIsland.Visibility(Visibility::Visible);
}
static bool FittedOverlay() {
    return g_settings.vizEnabled && g_settings.vizOverlay && g_settings.island &&
           g_settings.position == L"taskbar_after_system_info";
}
static void FollowSystemInfo() {
    if (!g_playerGrid || g_unloading) return;
    try {
        double systemInfoRight = SystemInfoRightDip();
        double islandLeft = systemInfoRight + g_settings.islandGap;
        double inset = FittedOverlay() ? 2.0 + kOverlayInset :
                       g_settings.playerMarginLeft - g_settings.islandGap;
        double left = islandLeft + inset;
        auto margin = g_playerGrid.Margin();
        if (std::abs(margin.Left - left) > 0.1) {
            margin.Left = left;
            g_playerGrid.Margin(margin);
        }
        INT_PTR right = 0;
        if (PrimaryTaskbarIfOurs() && g_playerGrid.Visibility() == Visibility::Visible &&
            g_playerGrid.Opacity() > 0.01 && g_playerGrid.ActualWidth() > 0.0)
            right = (INT_PTR)std::ceil(left + g_playerGrid.ActualWidth() +
                (FittedOverlay() ? 0 : g_settings.playerMarginRight));
        PublishPlayerRight(right);
        PlaceMediaIsland(islandLeft, right, left + g_playerGrid.ActualWidth());
    } catch (...) {}
}
static void DockFitTick() {
    if (!g_playerGrid || g_unloading || !FittedOverlay()) return;
    try {
        auto panel = FindChildByName(g_playerGrid, kPanelGridName);
        if (!panel) return;
        // Measure the media independently of the animated viewport. Hidden media
        // remains measured, so a track/timeline change cannot feed back into width.
        panel.HorizontalAlignment(HorizontalAlignment::Left);
        panel.ClearValue(FrameworkElement::WidthProperty());
        panel.Measure({10000.0f, 48.0f});
        double natural = panel.DesiredSize().Width;
        auto pm = panel.Margin();
        panel.Width(std::max(0.0, natural - pm.Left - pm.Right));
        double target = g_vizOnly ?
            std::clamp(Wh_GetIntSetting(L"Visualizer.appearance.barCount"), 1, VIZ_BARS_MAX) *
                (g_settings.vizBarWidth + g_settings.vizBarGap) - g_settings.vizBarGap + 2*kOverlayInset : natural;
        if (!g_vizOnly) {
            target = std::max(target, (double)g_settings.playerMinWidth);
            if (g_settings.playerMaxWidth > 0) target = std::min(target, (double)g_settings.playerMaxWidth);
        }
        target = std::max(1.0, target);
        auto now = std::chrono::steady_clock::now();
        if (g_dockWidth < 0) {
            g_dockWidth = g_dockFrom = g_dockTarget = target;
            g_dockOpacity = g_dockOpacityFrom = g_dockOpacityTarget = g_vizOnly ? 0.0 : 1.0;
            g_dockStart = now;
        }
        double opacityTarget = g_vizOnly ? 0.0 : 1.0;
        if (std::abs(target - g_dockTarget) > 0.1 || opacityTarget != g_dockOpacityTarget) {
            // Retarget from the displayed width, never from an old endpoint.
                g_dockFrom = g_dockWidth;
                g_dockOpacityFrom = g_dockOpacity;
                g_dockTarget = target;
                g_dockOpacityTarget = opacityTarget;
                g_dockStart = now;
        }
        double t = std::clamp(std::chrono::duration<double, std::milli>(now-g_dockStart).count()/180.0, 0.0, 1.0);
        bool animate = g_settings.enableSmoothPositionAnimation &&
            winrt::Windows::UI::ViewManagement::UISettings().AnimationsEnabled();
        double ease = animate ? 1-std::pow(1-t, 3) : 1;
        g_dockWidth = g_dockFrom + (g_dockTarget-g_dockFrom)*ease;
        g_dockOpacity = g_dockOpacityFrom + (g_dockOpacityTarget-g_dockOpacityFrom)*ease;
        g_playerGrid.MinWidth(0);
        g_playerGrid.ClearValue(FrameworkElement::MaxWidthProperty());
        g_playerGrid.Width(g_dockWidth);
        winrt::Windows::UI::Xaml::Media::RectangleGeometry clip;
        clip.Rect({0,0,(float)g_dockWidth,48});
        g_playerGrid.Clip(clip);
        for (auto const& child : g_playerGrid.Children()) {
            auto fe = child.try_as<FrameworkElement>();
            if (fe && (fe.Name() == kPanelGridName || fe.Name() == kProgressLayerName)) {
                fe.Opacity(g_dockOpacity);
                fe.IsHitTestVisible(!g_vizOnly);
            }
        }
        g_playerGrid.UpdateLayout();
        FollowSystemInfo();
    } catch (...) {}
}
static bool InjectPlayerGrid() {
    HWND hWnd = g_taskbarWnd ? g_taskbarWnd : FindCurrentProcessTaskbarWnd();
    if (!hWnd) {
        Wh_Log(L"InjectPlayerGrid: No taskbar window found");
        return false;
    }
    g_taskbarWnd = hWnd;
    EnsureMenuHost();
    try {
        auto xamlRoot = GetTaskbarXamlRoot(hWnd);
        if (!xamlRoot) {
            Wh_Log(L"InjectPlayerGrid: Failed to get XAML root");
            return false;
        }
        auto root = xamlRoot.Content().try_as<FrameworkElement>();
        if (!root) {
            Wh_Log(L"InjectPlayerGrid: Failed to get root FrameworkElement");
            return false;
        }
        if (g_settings.enableTreeDump) {
            DumpXamlTree(root, 0, 5);
            auto rootGrid = FindTaskbarRootGrid(root);
            if (rootGrid) {
                auto repeater = FindChildByName(rootGrid, L"TaskbarFrameRepeater");
                if (repeater) {
                    DumpXamlTree(repeater, 0, 3);
                }
            }
        }
        auto [targetGrid, insertCol] = ResolveInjectionTarget(root, g_settings.position);
        if (!targetGrid) {
            if (g_settings.enableTreeDump) {
                DumpXamlTree(root, 0, 8);
            }
            return false;
        }
        Grid playerGrid = BuildPlayerGrid();
        if (!playerGrid) return false;
        bool startButtonModActive = IsStartButtonModActive(root);
        (void)startButtonModActive;
        bool isTrayGrid = (targetGrid.Name() == L"SystemTrayFrameGrid");
        RemovePlayerGridChildren(targetGrid);
        RemoveAnchorDebugOverlays(targetGrid);
        if (isTrayGrid) {
            ColumnDefinition newCol;
            newCol.Width({1.0, GridUnitType::Auto});
            if (insertCol >= (int)targetGrid.ColumnDefinitions().Size()) {
                targetGrid.ColumnDefinitions().Append(newCol);
            } else {
                targetGrid.ColumnDefinitions().InsertAt(insertCol, newCol);
                for (uint32_t i = 0; i < targetGrid.Children().Size(); ++i) {
                    auto child = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
                    if (child) {
                        int childCol = Grid::GetColumn(child);
                        if (childCol >= insertCol)
                            Grid::SetColumn(child, childCol + 1);
                    }
                }
            }
            playerGrid.Margin({(double)g_settings.playerMarginLeft, 0,
                            (double)g_settings.playerMarginRight, 0});
            Grid::SetColumn(playerGrid, insertCol);
            targetGrid.Children().Append(playerGrid);
            g_playerColumn = insertCol;
        }
        else {
            auto repeater  = FindChildByName(targetGrid, L"TaskbarFrameRepeater");
            auto trayFrame = FindChildByName(targetGrid, L"SystemTrayFrameGrid");
            bool isEdgePosition = (g_settings.position == L"taskbar_left_edge" ||
                                g_settings.position == L"taskbar_after_system_info" ||
                                g_settings.position == L"taskbar_center_edge" ||
                                g_settings.position == L"taskbar_right_edge");
            bool isTrackingPosition = (g_settings.position == L"taskbar_left_start" ||
                                    g_settings.position == L"taskbar_right_start" ||
                                    g_settings.position == L"taskbar_after_search_left" ||
                                    g_settings.position == L"taskbar_after_search_right" ||
                                    g_settings.position == L"taskbar_after_taskview_left" ||
                                    g_settings.position == L"taskbar_after_taskview_right" ||
                                    g_settings.position == L"taskbar_after_widgets_left" ||
                                    g_settings.position == L"taskbar_after_widgets_right");
            if (isEdgePosition || isTrackingPosition) {
                double leftMargin  = (double)g_settings.playerMarginLeft;
                double rightMargin = (double)g_settings.playerMarginRight;
                playerGrid.HorizontalAlignment(HorizontalAlignment::Left);
                if (isEdgePosition) {
                    if (g_settings.position == L"taskbar_left_edge") {
                        playerGrid.Margin({leftMargin, 0, rightMargin, 0});
                    }
                    else if (g_settings.position == L"taskbar_after_system_info") {
                        playerGrid.Margin({SystemInfoRightDip() + leftMargin, 0, rightMargin, 0});
                        if (g_settings.island) {
                            g_mediaIsland = MakeMediaIsland();
                            targetGrid.Children().Append(g_mediaIsland);
                        }
                        g_layoutUpdateToken = targetGrid.LayoutUpdated(
                            [](winrt::Windows::Foundation::IInspectable const&, winrt::Windows::Foundation::IInspectable const&) {
                                FollowSystemInfo();
                            });
                    }
                    else if (g_settings.position == L"taskbar_center_edge") {
                        playerGrid.HorizontalAlignment(HorizontalAlignment::Center);
                        playerGrid.Margin({leftMargin, 0, rightMargin, 0});
                    }
                    else if (g_settings.position == L"taskbar_right_edge") {
                        playerGrid.HorizontalAlignment(HorizontalAlignment::Right);
                        if (trayFrame) rightMargin += trayFrame.ActualWidth() + 4;
                        playerGrid.Margin({leftMargin, 0, rightMargin, 0});
                    }
                } else if (isTrackingPosition) {
                    FrameworkElement targetElem = nullptr;
                    std::wstring trackSide = L"right";
                    if (repeater) {
                        if (g_settings.position == L"taskbar_left_start") {
                            targetElem = FindElementInRepeater(repeater, kStartButtonNames, ARRAYSIZE(kStartButtonNames));
                            trackSide = L"left";
                        } else if (g_settings.position == L"taskbar_right_start") {
                            targetElem = FindElementInRepeater(repeater, kStartButtonNames, ARRAYSIZE(kStartButtonNames));
                            trackSide = L"right";
                        } else if (g_settings.position == L"taskbar_after_search_left") {
                            targetElem = FindElementByClassName(repeater, L"Taskbar.TaskbarExtensionElement");
                            trackSide = L"left";
                        } else if (g_settings.position == L"taskbar_after_search_right") {
                            targetElem = FindElementByClassName(repeater, L"Taskbar.TaskbarExtensionElement");
                            trackSide = L"right";
                        } else if (g_settings.position == L"taskbar_after_taskview_left") {
                            targetElem = FindNthElementByClassName(repeater, L"Taskbar.ExperienceToggleButton", 1);
                            trackSide = L"left";
                        } else if (g_settings.position == L"taskbar_after_taskview_right") {
                            targetElem = FindNthElementByClassName(repeater, L"Taskbar.ExperienceToggleButton", 1);
                            trackSide = L"right";
                        } else if (g_settings.position == L"taskbar_after_widgets_left") {
                            targetElem = FindChildByName(repeater, L"AugmentedEntryPointButton");
                            if (!targetElem) targetElem = FindChildByClassName(repeater, L"Taskbar.AugmentedEntryPointButton");
                            trackSide = L"left";
                        } else if (g_settings.position == L"taskbar_after_widgets_right") {
                            targetElem = FindChildByName(repeater, L"AugmentedEntryPointButton");
                            if (!targetElem) targetElem = FindChildByClassName(repeater, L"Taskbar.AugmentedEntryPointButton");
                            trackSide = L"right";
                        }
                    }
                    if (targetElem) {
                        g_trackedElement = targetElem;
                        g_trackedElementOriginalMargin = targetElem.Margin();
                        g_hasTrackedElementOriginalMargin = true;
                        g_trackPosition = trackSide;
                        bool startButtonModActiveMod = IsStartButtonModActive(root);
                        double startButtonOffset = 0.0;
                        if (startButtonModActiveMod &&
                            (g_settings.position == L"taskbar_left_start" ||
                            g_settings.position == L"taskbar_right_start" ||
                            g_settings.position == L"taskbar_after_taskview_left" ||
                            g_settings.position == L"taskbar_after_taskview_right")) {
                            startButtonOffset = GetStartButtonAdjustment(root);
                        }
                        g_layoutUpdateToken = targetGrid.LayoutUpdated(
                            [targetGrid, startButtonModActiveMod, startButtonOffset](winrt::Windows::Foundation::IInspectable const&, winrt::Windows::Foundation::IInspectable const&) {
                                try {
                                    if (!g_playerGrid || !g_trackedElement || g_unloading) return;
                                    UpdateAnchorDebugOverlay(targetGrid, g_trackedElement);
                                    bool isVisible = (g_playerGrid.Visibility() == Visibility::Visible);
                                    double w = isVisible ? g_playerGrid.ActualWidth() : 0.0;
                                    double desiredGap = isVisible ? (w + g_settings.playerMarginLeft + g_settings.playerMarginRight) : 0.0;
                                    auto m = g_hasTrackedElementOriginalMargin ? g_trackedElementOriginalMargin : g_trackedElement.Margin();
                                    auto currentMargin = g_trackedElement.Margin();
                                    bool changedMargin = false;
                                    if (g_trackPosition == L"far_left") {
                                        try {
                                            double originalLeft = g_hasTrackedElementOriginalMargin ? g_trackedElementOriginalMargin.Left : 0.0;
                                            double currentLeftmost = FindLeftmostVisibleChildX(g_trackedElement, targetGrid, 4);
                                            double naturalLeft = currentLeftmost >= 0.0
                                                ? currentLeftmost - (currentMargin.Left - originalLeft)
                                                : desiredGap;
                                            double requiredExtra = std::max(0.0, desiredGap - naturalLeft);
                                            double targetLeft = originalLeft + requiredExtra;
                                            if (std::abs(currentMargin.Left - targetLeft) > 1.0 ||
                                                std::abs(currentMargin.Right - m.Right) > 1.0) {
                                                m.Left = targetLeft;
                                                changedMargin = true;
                                            }
                                        } catch (...) {
                                            if (g_hasTrackedElementOriginalMargin &&
                                                (std::abs(currentMargin.Left - m.Left) > 1.0 ||
                                                std::abs(currentMargin.Right - m.Right) > 1.0)) {
                                                changedMargin = true;
                                            }
                                        }
                                    } else if (g_trackPosition == L"left") {
                                        if (std::abs(currentMargin.Left - desiredGap) > 1.0) { m.Left = desiredGap; changedMargin = true; }
                                    } else {
                                        if (std::abs(currentMargin.Right - desiredGap) > 1.0) { m.Right = desiredGap; changedMargin = true; }
                                    }
                                    if (changedMargin) g_trackedElement.Margin(m);
                                    if (isVisible) {
                                        try {
                                            auto transform = g_trackedElement.TransformToVisual(targetGrid);
                                            auto point = transform.TransformPoint({0, 0});
                                            double leftPos = point.X;
                                            if (g_trackPosition == L"far_left") {
                                                leftPos = g_settings.playerMarginLeft;
                                            } else if (g_trackPosition == L"left") {
                                                leftPos = point.X - desiredGap + g_settings.playerMarginLeft;
                                                if (startButtonModActiveMod && startButtonOffset > 0) {
                                                    leftPos += startButtonOffset;
                                                }
                                            } else {
                                                leftPos = point.X + g_trackedElement.ActualWidth() + g_settings.playerMarginLeft;
                                            }
                                            auto pm = g_playerGrid.Margin();
                                            if (std::abs(pm.Left - leftPos) > 1.0) {
                                                g_playerGrid.Margin({leftPos, 0, 0, 0});
                                            }
                                        } catch (...) {}
                                    }
                                } catch (...) {
                                    g_trackedElement = nullptr;
                                    g_hasTrackedElementOriginalMargin = false;
                                }
                            }
                        );
                    } else {
                        playerGrid.Margin({leftMargin, 0, rightMargin, 0});
                    }
                }
                Grid::SetColumn(playerGrid, 0);
                Canvas::SetZIndex(playerGrid, 1000);
                targetGrid.Children().Append(playerGrid);
                g_playerColumn = -1;
            }
            else {
                ColumnDefinition newCol;
                newCol.Width({1.0, GridUnitType::Auto});
                if (insertCol >= (int)targetGrid.ColumnDefinitions().Size()) {
                    targetGrid.ColumnDefinitions().Append(newCol);
                } else {
                    targetGrid.ColumnDefinitions().InsertAt(insertCol, newCol);
                    for (uint32_t i = 0; i < targetGrid.Children().Size(); ++i) {
                        auto child = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
                        if (child) {
                            int childCol = Grid::GetColumn(child);
                            if (childCol >= insertCol)
                                Grid::SetColumn(child, childCol + 1);
                        }
                    }
                }
                playerGrid.Margin({(double)g_settings.playerMarginLeft, 0,
                                (double)g_settings.playerMarginRight, 0});
                Grid::SetColumn(playerGrid, insertCol);
                targetGrid.Children().Append(playerGrid);
                g_playerColumn = insertCol;
            }
        }
        g_playerGrid      = playerGrid;
        g_injectionParent = targetGrid;
        RefreshPlayerContents();
        g_playerGrid.Visibility(Visibility::Visible);
        g_playerGrid.UpdateLayout();
        if (g_injectionParent) {
            g_injectionParent.UpdateLayout();
        }
        if (g_playerGrid.ActualWidth() == 0.0 && g_playerGrid.ActualHeight() == 0.0) {
            g_needsUiUpdate = true;
            if (g_timerUpdateEvent) SetEvent(g_timerUpdateEvent);
        }
        auto dispatcher = g_playerGrid.Dispatcher();
        if (dispatcher) {
            try {
                dispatcher.RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Low, [=]() {
                    if (!g_unloading && g_playerGrid) RefreshThemeColors();
                });
            } catch (...) {
                Wh_Log(L"InjectPlayerGrid: Failed to dispatch RefreshThemeColors");
            }
        }
        Canvas::SetZIndex(g_playerGrid, 1000);
        OnSessionsChanged();
        g_needsUiUpdate = true;
        return true;
    } catch (...) {
        Wh_Log(L"InjectPlayerGrid: Exception during injection");
        return false;
    }
}
static void RemovePlayerGrid() {
    g_dockWidth = -1;
    PublishPlayerRight(0);
    PublishVizHover(0, 0, 0, 0);
    if (!g_injectionParent) return;
    try {
        if (g_miniPlayerFlyoutOpen && g_miniPlayerFlyout) {
            g_miniPlayerExplicitCloseRequested.store(true);
            try { g_miniPlayerFlyout.Hide(); } catch (...) {}
        }
        g_miniPlayerFlyout = nullptr;
        g_miniPlayerFlyoutOpen = false;
    } catch (...) {}
    try {
        if (g_layoutUpdateToken.value) {
            auto targetGrid = g_injectionParent.try_as<Grid>();
            if (targetGrid) {
                try { targetGrid.LayoutUpdated(g_layoutUpdateToken); } catch (...) {}
            }
            g_layoutUpdateToken = {};
        }
        
        if (g_trackedElement) {
            try {
                if (g_hasTrackedElementOriginalMargin) {
                    g_trackedElement.Margin(g_trackedElementOriginalMargin);
                } else {
                    auto m = g_trackedElement.Margin();
                    if (g_trackPosition == L"left" || g_trackPosition == L"far_left") m.Left = 0;
                    if (g_trackPosition == L"right") m.Right = 0;
                    g_trackedElement.Margin(m);
                }
            } catch (...) {}
            g_trackedElement = nullptr;
        }
        g_hasTrackedElementOriginalMargin = false;
        g_trackPosition = L"";
        auto targetGrid = g_injectionParent.try_as<Grid>();
        int playerCol = -1;
        RemoveAnchorDebugOverlays(targetGrid);
        playerCol = RemovePlayerGridChildren(targetGrid);
        g_mediaIsland = nullptr;
        g_mediaDivider = nullptr;
        bool isTrackingPosition = (g_settings.position == L"taskbar_left_edge" ||
                                g_settings.position == L"taskbar_after_system_info" ||
                                g_settings.position == L"taskbar_center_edge" ||
                                g_settings.position == L"taskbar_right_edge" ||
                                g_settings.position == L"taskbar_left_start" ||
                                g_settings.position == L"taskbar_right_start" ||
                                g_settings.position == L"taskbar_after_search_left" ||
                                g_settings.position == L"taskbar_after_search_right" ||
                                g_settings.position == L"taskbar_after_taskview_left" ||
                                g_settings.position == L"taskbar_after_taskview_right" ||
                                g_settings.position == L"taskbar_after_widgets_left" ||
                                g_settings.position == L"taskbar_after_widgets_right");
        if (!isTrackingPosition && playerCol >= 0 && playerCol < (int)targetGrid.ColumnDefinitions().Size()) {
            for (uint32_t i = 0; i < targetGrid.Children().Size(); ++i) {
                auto child = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
                if (child) {
                    int childCol = Grid::GetColumn(child);
                    if (childCol > playerCol)
                        Grid::SetColumn(child, childCol - 1);
                }
            }
            targetGrid.ColumnDefinitions().RemoveAt(playerCol);
        }
        g_playerGrid      = nullptr;
        g_injectionParent = nullptr;
        g_playerColumn    = -1;
        g_playerToolTip   = nullptr;
        g_playerButtonStateUpdater = nullptr;
        g_cachedAlbumTitle.clear();
        g_cachedAlbumArtist.clear();
        g_cachedThumbnailBytes.clear();
        g_cachedPaletteHash = 0;
        g_blurBgCache.Invalidate();
        g_cachedAppIconSize = -1;
        g_scrollCachedTitle.clear();
        g_scrollCachedArtist.clear();
        ResetScrollState(g_titleScroll);
        ResetScrollState(g_artistScroll);
        g_miniPlayerArtRef            = nullptr;
        g_miniPlayerTitleRef          = nullptr;
        g_miniPlayerArtistRef         = nullptr;
        g_miniPlayerPlayBtnRef        = nullptr;
        g_miniPlayerPrevBtnRef        = nullptr;
        g_miniPlayerNextBtnRef        = nullptr;
        g_miniPlayerShuffleBtnRef     = nullptr;
        g_miniPlayerRepeatBtnRef      = nullptr;
        g_miniPlayerSessionListRef    = nullptr;
        g_miniPlayerSessionListSepRef = nullptr;
    } catch (...) {
        g_playerGrid      = nullptr;
        g_injectionParent = nullptr;
        g_playerColumn    = -1;
        g_playerToolTip   = nullptr;
        g_playerButtonStateUpdater = nullptr;
        g_cachedAlbumTitle.clear();
        g_cachedAlbumArtist.clear();
        g_cachedThumbnailBytes.clear();
        g_cachedPaletteHash = 0;
        g_blurBgCache.Invalidate();
        g_cachedAppIconSize = -1;
        ResetScrollState(g_titleScroll);
        ResetScrollState(g_artistScroll);
        g_miniPlayerArtRef            = nullptr;
        g_miniPlayerTitleRef          = nullptr;
        g_miniPlayerArtistRef         = nullptr;
        g_miniPlayerPlayBtnRef        = nullptr;
        g_miniPlayerPrevBtnRef        = nullptr;
        g_miniPlayerNextBtnRef        = nullptr;
        g_miniPlayerShuffleBtnRef     = nullptr;
        g_miniPlayerRepeatBtnRef      = nullptr;
        g_miniPlayerSessionListRef    = nullptr;
        g_miniPlayerSessionListSepRef = nullptr;
    }
}
static void RefreshPlayerContents() {
    if (!g_playerGrid || g_unloading || g_applyingSettings) return;
    std::wstring      title, artist;
    bool              isPlaying = false, hasMedia = false;
    std::vector<BYTE> thumbBytes;
    std::vector<BYTE> appIconBytes;
    uint64_t          thumbHash = 0;
    bool              canSkipPrevious = true, canSkipNext = true;
    bool              canShuffle = true, canRepeat = true, canSeek = true;
    {
        std::lock_guard<std::mutex> lk(g_mediaMtx);
        title        = g_media.title;
        artist       = g_media.artist;
        isPlaying    = g_media.isPlaying;
        hasMedia     = g_media.hasMedia;
        thumbBytes   = g_media.thumbnailBytes;
        thumbHash    = g_media.thumbnailHash;
        appIconBytes = g_media.appIconBytes;
        canSkipPrevious = g_media.canSkipPrevious;
        canSkipNext     = g_media.canSkipNext;
        canShuffle      = g_media.canShuffle;
        canRepeat       = g_media.canRepeat;
        canSeek         = g_media.canSeek;
    }
    (void)hasMedia;
    bool hasSession = false;
    { std::lock_guard<std::mutex> lk(g_sessionMtx); hasSession = (g_currentSession != nullptr); }
    g_playerGrid.UpdateLayout();
    if (title != g_scrollCachedTitle || artist != g_scrollCachedArtist) {
        g_scrollCachedTitle  = title;
        g_scrollCachedArtist = artist;
        ResetScrollState(g_titleScroll);
        ResetScrollState(g_artistScroll);
        try {
            if (auto fe = FindChildByName(g_playerGrid, kTitleCloneName))
                if (auto cl = fe.try_as<TextBlock>())
                    cl.Visibility(Visibility::Collapsed);
        } catch (...) {}
        try {
            if (auto fe = FindChildByName(g_playerGrid, kArtistCloneName))
                if (auto cl = fe.try_as<TextBlock>())
                    cl.Visibility(Visibility::Collapsed);
        } catch (...) {}
        try {
            if (auto fe = FindChildByName(g_playerGrid, kTitleBlockName))
                if (auto tb = fe.try_as<TextBlock>())
                    Canvas::SetLeft(tb, 0.0);
        } catch (...) {}
        try {
            if (auto fe = FindChildByName(g_playerGrid, kArtistBlockName))
                if (auto ab = fe.try_as<TextBlock>())
                    Canvas::SetLeft(ab, 0.0);
        } catch (...) {}
    }
    bool titleVisible = false;
    bool artistVisible = false;
    if (auto fe = FindChildByName(g_playerGrid, kTitleBlockName))
        if (auto tb = fe.try_as<TextBlock>())
            try {
                std::wstring displayTitle = title;
                if (!hasSession) {
                    displayTitle = g_settings.noMediaTitleText;
                } else if (title.empty()) {
                    displayTitle = g_settings.emptyTitleText;
                }
                tb.Text(winrt::hstring(displayTitle));
                tb.Foreground(MakeBrush(TextColor()));
                bool visible = g_settings.showTrackTitle && !displayTitle.empty();
                titleVisible = visible;
                tb.Visibility(visible ? Visibility::Visible : Visibility::Collapsed);
                ToolTipService::SetToolTip(tb, nullptr);
                if (g_settings.enableTitleScrolling && visible) {
                    try {
                        if (auto viewFe = FindChildByName(g_playerGrid, kTitleScrollViewName))
                            viewFe.Visibility(Visibility::Visible);
                    } catch (...) {}
                    if (auto panelFe = FindChildByName(g_playerGrid, kPanelGridName)) {
                        panelFe.UpdateLayout();
                    }
                    tb.UpdateLayout();
                    double textW = tb.DesiredSize().Width;
                    if (auto viewFe = FindChildByName(g_playerGrid, kTitleScrollViewName)) {
                        if (auto viewCanvas = viewFe.try_as<Canvas>()) {
                            double minW = (double)g_settings.textAreaMinWidth;
                            double maxW = (double)g_settings.textAreaMaxWidth;
                            double viewW = textW;
                            if (maxW > 0 && viewW > maxW) viewW = maxW;
                            double availW = GetAvailableScrollTextAreaWidth();
                            if (availW > 0.0 && viewW > availW) {
                                viewW = (minW > 0.0) ? std::max(availW, minW) : availW;
                            }
                            if (minW > 0 && viewW < minW) viewW = minW;
                            if (std::abs(viewCanvas.Width() - viewW) > 0.5) {
                                viewCanvas.Width(viewW);
                                try {
                                    if (auto geo = viewCanvas.Clip().try_as<winrt::Windows::UI::Xaml::Media::RectangleGeometry>()) {
                                        auto r = geo.Rect();
                                        geo.Rect({0, 0, (float)viewW, r.Height});
                                    }
                                } catch (...) {}
                            }
                            bool wasActive = g_titleScroll.active;
                            g_titleScroll.textWidth = textW;
                            g_titleScroll.viewWidth = viewW;
                            g_titleScroll.active = (textW > viewW + 2.0);
                            if (!g_titleScroll.active) {
                                g_titleScroll.offset = 0.0;
                                g_titleScroll.forward = true;
                                Canvas::SetLeft(tb, 0.0);
                            } else if (!wasActive) {
                                g_titleScroll.offset = 0.0;
                                g_titleScroll.forward = true;
                                if (g_settings.scrollMode == L"loop") {
                                    g_titleScroll.pausing  = false;
                                    g_titleScroll.pauseTick = 0;
                                } else {
                                    g_titleScroll.pausing  = true;
                                    g_titleScroll.pauseTick = g_settings.scrollPauseDuration;
                                }
                            }
                            if (auto cloneFe = FindChildByName(g_playerGrid, kTitleCloneName)) {
                                if (auto clone = cloneFe.try_as<TextBlock>()) {
                                    clone.Text(tb.Text());
                                    clone.Foreground(tb.Foreground());
                                    clone.Visibility(g_settings.scrollMode == L"loop" && g_titleScroll.active
                                        ? Visibility::Visible : Visibility::Collapsed);
                                }
                            }
                        }
                    }
                } else {
                    g_titleScroll.active = false;
                    g_titleScroll.offset = 0.0;
                    if (g_settings.enableTitleScrolling) {
                        try {
                            if (auto viewFe = FindChildByName(g_playerGrid, kTitleScrollViewName))
                                viewFe.Visibility(Visibility::Collapsed);
                        } catch (...) {}
                    }
                }
            } catch (...) {}
    if (auto fe = FindChildByName(g_playerGrid, kArtistBlockName))
        if (auto ab = fe.try_as<TextBlock>())
            try {
                std::wstring displayArtist = artist;
                if (!hasSession) {
                    displayArtist = g_settings.noMediaArtistText;
                } else if (artist.empty()) {
                    displayArtist = g_settings.emptyArtistText;
                }
                ab.Text(winrt::hstring(displayArtist));
                bool visible = g_settings.showTrackArtist && !displayArtist.empty();
                artistVisible = visible;
                ab.Visibility(visible ? Visibility::Visible : Visibility::Collapsed);
                ab.Foreground(MakeBrush(ArtistColor()));
                ToolTipService::SetToolTip(ab, nullptr);
                if (g_settings.enableArtistScrolling && visible) {
                    try {
                        if (auto viewFe = FindChildByName(g_playerGrid, kArtistScrollViewName))
                            viewFe.Visibility(Visibility::Visible);
                    } catch (...) {}
                    if (auto panelFe = FindChildByName(g_playerGrid, kPanelGridName)) {
                        panelFe.UpdateLayout();
                    }
                    ab.UpdateLayout();
                    double textW = ab.DesiredSize().Width;
                    if (auto viewFe = FindChildByName(g_playerGrid, kArtistScrollViewName)) {
                        if (auto viewCanvas = viewFe.try_as<Canvas>()) {
                            double minW = (double)g_settings.textAreaMinWidth;
                            double maxW = (double)g_settings.textAreaMaxWidth;
                            double viewW = textW;
                            if (maxW > 0 && viewW > maxW) viewW = maxW;
                            double availW = GetAvailableScrollTextAreaWidth();
                            if (availW > 0.0 && viewW > availW) {
                                viewW = (minW > 0.0) ? std::max(availW, minW) : availW;
                            }
                            if (minW > 0 && viewW < minW) viewW = minW;
                            if (std::abs(viewCanvas.Width() - viewW) > 0.5) {
                                viewCanvas.Width(viewW);
                                try {
                                    if (auto geo = viewCanvas.Clip().try_as<winrt::Windows::UI::Xaml::Media::RectangleGeometry>()) {
                                        auto r = geo.Rect();
                                        geo.Rect({0, 0, (float)viewW, r.Height});
                                    }
                                } catch (...) {}
                            }
                            bool wasActive = g_artistScroll.active;
                            g_artistScroll.textWidth = textW;
                            g_artistScroll.viewWidth = viewW;
                            g_artistScroll.active = (textW > viewW + 2.0);
                            if (!g_artistScroll.active) {
                                g_artistScroll.offset = 0.0;
                                g_artistScroll.forward = true;
                                Canvas::SetLeft(ab, 0.0);
                            } else if (!wasActive) {
                                g_artistScroll.offset = 0.0;
                                g_artistScroll.forward = true;
                                if (g_settings.scrollMode == L"loop") {
                                    g_artistScroll.pausing  = false;
                                    g_artistScroll.pauseTick = 0;
                                } else {
                                    g_artistScroll.pausing  = true;
                                    g_artistScroll.pauseTick = g_settings.scrollPauseDuration;
                                }
                            }
                            if (auto cloneFe = FindChildByName(g_playerGrid, kArtistCloneName)) {
                                if (auto clone = cloneFe.try_as<TextBlock>()) {
                                    clone.Text(ab.Text());
                                    clone.Foreground(ab.Foreground());
                                    clone.Visibility(g_settings.scrollMode == L"loop" && g_artistScroll.active
                                        ? Visibility::Visible : Visibility::Collapsed);
                                }
                            }
                        }
                    }
                } else {
                    g_artistScroll.active = false;
                    g_artistScroll.offset = 0.0;
                    if (g_settings.enableArtistScrolling) {
                        try {
                            if (auto viewFe = FindChildByName(g_playerGrid, kArtistScrollViewName))
                                viewFe.Visibility(Visibility::Collapsed);
                        } catch (...) {}
                    }
                }
            } catch (...) {}
    if ((g_titleScroll.active || g_artistScroll.active) &&
        (g_settings.enableTitleScrolling || g_settings.enableArtistScrolling)) {
        if (g_scrollDispatcherTimer && !g_scrollDispatcherTimer.IsEnabled()) {
            try { g_scrollDispatcherTimer.Start(); } catch (...) {}
        }
    }
    try {
        if (auto stackFe = FindChildByName(g_playerGrid, kTextStackName)) {
            bool anyTextVisible = titleVisible || artistVisible;
            stackFe.Visibility(anyTextVisible ? Visibility::Visible : Visibility::Collapsed);
        }
    } catch (...) {}
    if (auto fe = FindChildByName(g_playerGrid, kPlayBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    const wchar_t* glyph = GetGlyph(2, isPlaying);
                    ct.Text(winrt::hstring(glyph));
                    ct.Foreground(MakeBrush(ButtonColor()));
                }
            } catch (...) {}
    if (auto fe = FindChildByName(g_playerGrid, kPrevBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = canSkipPrevious;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    const wchar_t* glyph = GetGlyph(1);
                    ct.Text(winrt::hstring(glyph));
                    if (!supported && !g_settings.hideUnsupportedButtons) {
                        ct.Opacity(0.35);
                        ct.Foreground(MakeBrush(ButtonColor()));
                    } else {
                        ct.Opacity(1.0);
                        ct.Foreground(MakeBrush(ButtonColor()));
                    }
                }
            } catch (...) {}
    if (auto fe = FindChildByName(g_playerGrid, kNextBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = canSkipNext;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    const wchar_t* glyph = GetGlyph(3);
                    ct.Text(winrt::hstring(glyph));
                    ct.Opacity(supported ? 1.0 : 0.35);
                    ct.Foreground(MakeBrush(ButtonColor()));
                }
            } catch (...) {}
    if (auto fe = FindChildByName(g_playerGrid, kRewindBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = canSeek;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    const wchar_t* glyph = GetGlyph(5);
                    ct.Text(winrt::hstring(glyph));
                    ct.Opacity(supported ? 1.0 : 0.35);
                    ct.Foreground(MakeBrush(ButtonColor()));
                }
            } catch (...) {}
    if (auto fe = FindChildByName(g_playerGrid, kForwardBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = canSeek;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    const wchar_t* glyph = GetGlyph(6);
                    ct.Text(winrt::hstring(glyph));
                    ct.Opacity(supported ? 1.0 : 0.35);
                    ct.Foreground(MakeBrush(ButtonColor()));
                }
            } catch (...) {}
    if (auto fe = FindChildByName(g_playerGrid, kShuffleBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = canShuffle;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    bool isEnabled = g_shuffleEnabled.load();
                    const wchar_t* glyph = L"";
                    ct.Text(winrt::hstring(glyph));
                    if (!supported && !g_settings.hideUnsupportedButtons) {
                        ct.Opacity(0.35);
                    } else {
                        ct.Opacity(isEnabled ? 1.0 : 0.4);
                    }
                    ct.Foreground(MakeBrush(ButtonColor()));
                }
            } catch (...) {}
    if (auto fe = FindChildByName(g_playerGrid, kRepeatBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = canRepeat;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    RepeatMode mode = g_repeatMode.load();
                    const wchar_t* glyph;
                    switch (mode) {
                        case RepeatMode::Off:
                            glyph = L"";
                            break;
                        case RepeatMode::All:
                            glyph = L"";
                            break;
                        case RepeatMode::One:
                            glyph = L"";
                            break;
                    }
                    ct.Text(winrt::hstring(glyph));
                    ct.Foreground(MakeBrush(ButtonColor()));
                    if (!supported && !g_settings.hideUnsupportedButtons) {
                        ct.Opacity(0.35);
                    } else {
                        ct.Opacity(1.0);
                    }
                }
            } catch (...) {}
    if (auto fe = FindChildByName(g_playerGrid, kSwitchSessionsBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = g_sessionCount.load() > 1;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    ct.Opacity(supported ? 1.0 : 0.35);
                    ct.Foreground(MakeBrush(ButtonColor()));
                }
            } catch (...) {}
    ApplyButtonGradient();
    if (g_settings.showPauseOverlay && g_settings.showAlbumArt) {
        if (auto fe = FindChildByName(g_playerGrid, L"PauseIconOverlay"))
            if (auto overlay = fe.try_as<Border>()) {
                try {
                    bool showPause = !isPlaying && hasMedia;
                    overlay.Visibility(showPause ? Visibility::Visible : Visibility::Collapsed);
                    if (auto pauseIcon = overlay.Child().try_as<TextBlock>()) {
                        pauseIcon.Text(GetGlyph(2, true));
                        bool useFluent = (g_settings.iconStyle == L"fluent_outline" || g_settings.iconStyle == L"fluent_filled");
                        pauseIcon.FontFamily(Media::FontFamily(useFluent ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets"));
                        pauseIcon.FontSize((double)g_settings.pauseOverlayIconSize);
                    }
                    if (showPause) {
                        if (auto artImg = FindChildByName(g_playerGrid, kArtImageName)) {
                            if (auto parent = VisualTreeHelper::GetParent(artImg)) {
                                if (auto artInnerGrid = parent.try_as<Grid>()) {
                                    for (uint32_t i = 0; i < artInnerGrid.Children().Size(); ++i) {
                                        auto child = artInnerGrid.Children().GetAt(i);
                                        if (auto border = child.try_as<Border>()) {
                                            if (border.Name() == L"EmptyIconBorder") {
                                                border.Visibility(Visibility::Collapsed);
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } catch (...) {}
            }
    }
    bool paletteChanged = false;
    if (auto fe = FindChildByName(g_playerGrid, kArtImageName))
        if (auto img = fe.try_as<Controls::Image>()) {
            if (!thumbBytes.empty() && g_settings.showAlbumArt) {
                bool isSameAlbum = (!g_cachedThumbnailBytes.empty() &&
                                title == g_cachedAlbumTitle &&
                                artist == g_cachedAlbumArtist &&
                                thumbBytes == g_cachedThumbnailBytes);
                size_t newHash = (size_t)thumbHash;
                if (newHash != g_cachedPaletteHash && newHash != 0) {
                    g_cachedAlbumPalette = ExtractAlbumPalette(thumbBytes);
                    g_cachedPaletteHash = newHash;
                    g_vizPaletteColorsDirty = true;
                    paletteChanged = true;
                }
                if (!isSameAlbum) {
                    try {
                        IStream* pRawStream = SHCreateMemStream(
                            thumbBytes.data(), static_cast<UINT>(thumbBytes.size()));
                        if (pRawStream) {
                            winrt::com_ptr<IStream> comStream;
                            comStream.attach(pRawStream);
                            winrt::Windows::Storage::Streams::IRandomAccessStream rasStream{ nullptr };
                            ::CreateRandomAccessStreamOverStream(
                                comStream.get(),
                                BSOS_DEFAULT,
                                winrt::guid_of<winrt::Windows::Storage::Streams::IRandomAccessStream>(),
                                winrt::put_abi(rasStream));
                            if (rasStream) {
                                BitmapImage bmp;
                                if (g_settings.albumArtQuality == L"low") {
                                    int baseHeight = g_settings.albumArtMaxHeight > 0 ? g_settings.albumArtMaxHeight : 64;
                                    int decodeHeight = baseHeight / 2;
                                    if (decodeHeight < 16) decodeHeight = 16;
                                    bmp.DecodePixelHeight(decodeHeight);
                                } else if (g_settings.albumArtQuality == L"medium") {
                                    if (g_settings.albumArtMaxHeight > 0) {
                                        bmp.DecodePixelHeight(g_settings.albumArtMaxHeight);
                                    }
                                }
                                bmp.ImageOpened([](auto const&, auto const&) {
                                    if (g_unloading || g_applyingSettings || !g_playerGrid) return;
                                    try {
                                        if (auto panelFe = FindChildByName(g_playerGrid, kPanelGridName)) {
                                            panelFe.UpdateLayout();
                                        }
                                        g_needsUiUpdate = true;
                                        if (g_timerUpdateEvent) SetEvent(g_timerUpdateEvent);
                                    } catch (...) {}
                                });
                                img.Source(bmp);
                                bmp.SetSourceAsync(rasStream);
                                img.Visibility(Visibility::Visible);
                                g_cachedAlbumTitle = title;
                                g_cachedAlbumArtist = artist;
                                g_cachedThumbnailBytes = thumbBytes;
                                if (auto parent = VisualTreeHelper::GetParent(img)) {
                                    if (auto artInnerGrid = parent.try_as<Grid>()) {
                                        if (auto grandParent = VisualTreeHelper::GetParent(artInnerGrid)) {
                                            if (auto container = grandParent.try_as<FrameworkElement>()) {
                                                if (auto greatGrandParent = VisualTreeHelper::GetParent(container)) {
                                                    if (auto artContainer = greatGrandParent.try_as<Grid>()) {
                                                        artContainer.Visibility(Visibility::Visible);
                                                    }
                                                }
                                            }
                                        }
                                        for (uint32_t i = 0; i < artInnerGrid.Children().Size(); ++i) {
                                            auto child = artInnerGrid.Children().GetAt(i);
                                            if (auto border = child.try_as<Border>()) {
                                                if (border.Name() == L"EmptyIconBorder") {
                                                    border.Visibility(Visibility::Collapsed);
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } catch (...) { try { img.Source(nullptr); } catch (...) {} }
                } else {
                    img.Visibility(Visibility::Visible);
                    if (auto parent = VisualTreeHelper::GetParent(img)) {
                        if (auto container = parent.try_as<FrameworkElement>()) {
                            if (auto grandParent = VisualTreeHelper::GetParent(container)) {
                                if (auto greatGrandParent = VisualTreeHelper::GetParent(grandParent)) {
                                    if (auto artContainer = greatGrandParent.try_as<Grid>()) {
                                        artContainer.Visibility(Visibility::Visible);
                                    }
                                }
                            }
                        }
                    }
                }
                if (auto bgFe = FindChildByName(g_playerGrid, L"FluentMedia_Background")) {
                    if (auto bgBorder = bgFe.try_as<Border>()) {
                        auto& bgType = g_settings.backgroundType;
                        if (bgType == L"album_art_blur") {
                            try {
                                g_blurBgCache.Invalidate();
                                bgBorder.Visibility(Visibility::Visible);
                                bgBorder.Opacity(g_settings.blurOpacity / 100.0);
                                auto applyBlur = [bgBorder, thumbBytesSnap = thumbBytes]() {
                                    try {
                                        int w = (int)bgBorder.ActualWidth();
                                        int h = (int)bgBorder.ActualHeight();
                                        if (w <= 0 || h <= 0) return;
                                        g_blurBgCache.Invalidate();
                                        bgBorder.Background(MakeAlbumBlurBrush(thumbBytesSnap, w, h));
                                        bgBorder.Opacity(g_settings.blurOpacity / 100.0);
                                        bgBorder.Visibility(Visibility::Visible);
                                    } catch (...) {}
                                };
                                if (bgBorder.ActualWidth() > 0 && bgBorder.ActualHeight() > 0) {
                                    applyBlur();
                                } else {
                                    auto tokenHolder = std::make_shared<winrt::event_token>();
                                    *tokenHolder = bgBorder.SizeChanged(
                                        [applyBlur, bgBorder, tokenHolder](auto const&, auto const&) mutable {
                                            applyBlur();
                                            try { bgBorder.SizeChanged(*tokenHolder); } catch (...) {}
                                        });
                                }
                            } catch (...) {}
                        } else if (bgType == L"solid" || bgType == L"gradient" || bgType == L"acrylic" || bgType == L"mica" || bgType == L"mica_alt") {
                            try {
                                bgBorder.Background(MakeBackgroundBrush());
                                bgBorder.Visibility(Visibility::Visible);
                                bgBorder.Opacity(1.0);
                            } catch (...) {}
                        }
                    }
                }
            } else {
                g_cachedAlbumTitle.clear();
                g_cachedAlbumArtist.clear();
                g_cachedThumbnailBytes.clear();
                g_cachedPaletteHash = 0;
                g_blurBgCache.Invalidate();
                if (auto bgFe = FindChildByName(g_playerGrid, L"FluentMedia_Background")) {
                    if (auto bgBorder = bgFe.try_as<Border>()) {
                        try {
                            auto& bgType = g_settings.backgroundType;
                            if (bgType == L"solid" || bgType == L"gradient" || bgType == L"acrylic" ||
                                bgType == L"mica" || bgType == L"mica_alt") {
                                bgBorder.Background(MakeBackgroundBrush());
                                bgBorder.Visibility(Visibility::Visible);
                                bgBorder.Opacity(1.0);
                            } else {
                                bgBorder.Background(nullptr);
                                bgBorder.Visibility(Visibility::Collapsed);
                            }
                        } catch (...) {}
                    }
                }
                try {
                    img.Source(nullptr);
                    img.Visibility(Visibility::Collapsed);
                    if (g_settings.albumArtEmptyBehavior == L"hide" && thumbBytes.empty()) {
                        if (auto parent = VisualTreeHelper::GetParent(img)) {
                            if (auto container = parent.try_as<FrameworkElement>()) {
                                if (auto grandParent = VisualTreeHelper::GetParent(container)) {
                                    if (auto greatGrandParent = VisualTreeHelper::GetParent(grandParent)) {
                                        if (auto artContainer = greatGrandParent.try_as<FrameworkElement>()) {
                                            artContainer.Visibility(Visibility::Collapsed);
                                        }
                                    }
                                }
                            }
                        }
                    } else if (g_settings.albumArtEmptyBehavior == L"show_icon" && thumbBytes.empty()) {
                        if (auto parent = VisualTreeHelper::GetParent(img)) {
                            if (auto artInnerGrid = parent.try_as<Grid>()) {
                                if (auto grandParent = VisualTreeHelper::GetParent(artInnerGrid)) {
                                    if (auto container = grandParent.try_as<FrameworkElement>()) {
                                        if (auto greatGrandParent = VisualTreeHelper::GetParent(container)) {
                                            if (auto artContainer = greatGrandParent.try_as<Grid>()) {
                                                artContainer.Visibility(Visibility::Visible);
                                            }
                                        }
                                    }
                                }
                                Border iconBorder = nullptr;
                                for (uint32_t i = 0; i < artInnerGrid.Children().Size(); ++i) {
                                    auto child = artInnerGrid.Children().GetAt(i);
                                    if (auto border = child.try_as<Border>()) {
                                        if (border.Name() == L"EmptyIconBorder") {
                                            iconBorder = border;
                                            break;
                                        }
                                    }
                                }
                                if (!iconBorder) {
                                    iconBorder = Border();
                                    iconBorder.Name(L"EmptyIconBorder");
                                    iconBorder.Background(MakeBrush({0x00, 0x00, 0x00, 0x00}));
                                    iconBorder.HorizontalAlignment(HorizontalAlignment::Stretch);
                                    iconBorder.VerticalAlignment(VerticalAlignment::Stretch);
                                    Canvas::SetZIndex(iconBorder, 5);
                                    TextBlock iconText = TextBlock();
                                    iconText.Name(L"EmptyIconText");
                                    iconText.HorizontalAlignment(HorizontalAlignment::Center);
                                    iconText.VerticalAlignment(VerticalAlignment::Center);
                                    iconBorder.Child(iconText);
                                    artInnerGrid.Children().InsertAt(0, iconBorder);
                                }
                                if (auto textBlock = iconBorder.Child().try_as<TextBlock>()) {
                                    std::wstring glyphStr;
                                    try {
                                        unsigned long cp = std::stoul(g_settings.emptyIconGlyph, nullptr, 16);
                                        if (cp <= 0xFFFF) {
                                            glyphStr = std::wstring(1, (wchar_t)cp);
                                        } else {
                                            cp -= 0x10000;
                                            glyphStr += (wchar_t)(0xD800 + (cp >> 10));
                                            glyphStr += (wchar_t)(0xDC00 + (cp & 0x3FF));
                                        }
                                    } catch (...) {
                                        glyphStr = L"\uE189";
                                    }
                                    textBlock.Text(glyphStr);
                                    bool useFluent = (g_settings.emptyIconFont == L"segoe_fluent");
                                    textBlock.FontFamily(Media::FontFamily(
                                        useFluent ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets"));
                                    textBlock.FontSize((double)g_settings.emptyIconSize);
                                    BYTE alpha = (BYTE)std::clamp((int)std::round(g_settings.emptyIconOpacity * 255.0 / 100.0), 0, 255);
                                    auto iconClr = ParseColorWithThemeSupport(g_settings.emptyIconColor, alpha);
                                    textBlock.Foreground(MakeBrush(iconClr));
                                }
                                iconBorder.Visibility(Visibility::Visible);
                            }
                        }
                    }
                } catch (...) {}
            }
        }
    if (paletteChanged) {
        try {
            if (g_settings.backgroundType == L"gradient" ||
                g_settings.backgroundType == L"solid" ||
                g_settings.backgroundType == L"acrylic" ||
                g_settings.backgroundType == L"mica" ||
                g_settings.backgroundType == L"mica_alt") {
                if (auto bgFe = FindChildByName(g_playerGrid, L"FluentMedia_Background")) {
                    if (auto bgBorder = bgFe.try_as<Border>()) {
                        bgBorder.Background(MakeBackgroundBrush());
                    }
                }
            }
            auto textClr = TextColor();
            auto artistClr = ArtistColor();
            if (auto titleFe = FindChildByName(g_playerGrid, kTitleBlockName)) {
                if (auto titleBlock = titleFe.try_as<TextBlock>()) {
                    titleBlock.Foreground(SolidColorBrush(textClr));
                }
            }
            if (auto artistFe = FindChildByName(g_playerGrid, kArtistBlockName)) {
                if (auto artistBlock = artistFe.try_as<TextBlock>()) {
                    artistBlock.Foreground(SolidColorBrush(artistClr));
                }
            }
            auto buttonClr = ButtonColor();
            for (const auto& btnName : {kPlayBtnName, kPrevBtnName, kNextBtnName,
                                        kRewindBtnName, kForwardBtnName, kShuffleBtnName, kRepeatBtnName}) {
                if (auto btnFe = FindChildByName(g_playerGrid, btnName)) {
                    if (auto btn = btnFe.try_as<Button>()) {
                        if (auto content = btn.Content()) {
                            if (auto icon = content.try_as<TextBlock>()) {
                                icon.Foreground(SolidColorBrush(buttonClr));
                            }
                        }
                    }
                }
            }
            ApplyButtonGradient();
        } catch (...) {}
    }
    if (g_settings.showAppIcon) {
        if (auto fe = FindChildByName(g_playerGrid, kAppIconImageName))
            if (auto img = fe.try_as<Controls::Image>()) {
                bool sizeChanged = (g_cachedAppIconSize != g_settings.appIconSize);
                if (sizeChanged && !appIconBytes.empty()) {
                    g_cachedAppIconSize = g_settings.appIconSize;
                    FetchMediaPropertiesAsync();
                }
                if (!appIconBytes.empty()) {
                    try {
                        int iconSz = g_settings.appIconSize;
                        size_t expectedBytes = (size_t)iconSz * iconSz * 4;
                        if (appIconBytes.size() != expectedBytes) {
                            int computed = (int)std::sqrt((double)appIconBytes.size() / 4.0);
                            if (computed > 0 && (size_t)computed * computed * 4 == appIconBytes.size())
                                iconSz = computed;
                        }
                        img.Width(iconSz);
                        img.Height(iconSz);
                        size_t bytesNeeded = (size_t)iconSz * iconSz * 4;
                        winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap wb(iconSz, iconSz);
                        auto buf = wb.PixelBuffer();
                        auto bufferByteAccess = buf.as<Windows::Storage::Streams::IBufferByteAccess>();
                        BYTE* pixels = nullptr;
                        bufferByteAccess->Buffer(&pixels);
                        if (appIconBytes.size() >= bytesNeeded && pixels) {
                            for (size_t i = 0; i + 3 < bytesNeeded; i += 4) {
                                pixels[i+0] = appIconBytes[i+2];
                                pixels[i+1] = appIconBytes[i+1];
                                pixels[i+2] = appIconBytes[i+0];
                                pixels[i+3] = appIconBytes[i+3];
                            }
                        }
                        buf.Length(static_cast<uint32_t>(bytesNeeded));
                        wb.Invalidate();
                        img.Source(wb);
                        img.Visibility(Visibility::Visible);
                    } catch (...) {
                        try { img.Source(nullptr); img.Visibility(Visibility::Collapsed); } catch (...) {}
                    }
                } else {
                    try { img.Source(nullptr); img.Visibility(Visibility::Collapsed); } catch (...) {}
                }
            }
    }
    try {
        FrameworkElement tooltipHost = g_playerGrid;
        if (g_settings.showFullTitleOnHover && hasSession && (!title.empty() || !artist.empty())) {
            std::wstring tooltipText;
            if (!title.empty())  tooltipText += title;
            if (!title.empty() && !artist.empty()) tooltipText += L"\n\n";
            if (!artist.empty()) tooltipText += artist;
            if (g_playerToolTip) {
                try {
                    auto content = g_playerToolTip.Content();
                    if (auto ttText = content.try_as<TextBlock>()) {
                        ttText.Text(winrt::hstring(tooltipText));
                    }
                    g_playerToolTip.IsEnabled(true);
                } catch (...) {}
                if (tooltipHost) {
                    try { ToolTipService::SetToolTip(tooltipHost, g_playerToolTip); } catch (...) {}
                }
            }
        } else {
            if (g_playerToolTip) {
                try {
                    auto content = g_playerToolTip.Content();
                    if (auto ttText = content.try_as<TextBlock>()) {
                        ttText.Text(L"");
                    }
                    g_playerToolTip.IsEnabled(false);
                } catch (...) {}
            }

            if (tooltipHost) {
                try { ToolTipService::SetToolTip(tooltipHost, nullptr); } catch (...) {}
            }
        }
    } catch (...) {}
    RefreshMiniPlayerFlyoutUI();
}
static bool IsFullscreenActive() {
    using Fn = HRESULT(WINAPI*)(int*);
    static Fn pfn = nullptr; static bool tried = false;
    if (!tried) {
        tried = true;
        HMODULE h = GetModuleHandleW(L"shell32.dll");
        if (!h) h = LoadLibraryW(L"shell32.dll");
        if (h) pfn = (Fn)GetProcAddress(h, (LPCSTR)2573);
    }
    if (!pfn) return false;
    int s = 0;
    return SUCCEEDED(pfn(&s)) && (s == 2 || s == 3 || s == 4);
}
// With nothing to play, the overlay visualizer keeps the dock and the player's
// own content (art, text, buttons, progress) fades out, so the bars show alone.
// Two looks (1.9.5): behind media the bars are dimmed and sit above the
// progress bar; alone they are the foreground, full strength, and drop to rest
// just above the dock border.
static void ApplyVisualizerOnly(bool on) {
    if (!g_playerGrid) return;
    g_vizOnly = on;
    try {
        auto kids = g_playerGrid.Children();
        for (uint32_t i = 0; i < kids.Size(); i++) {
            auto fe = kids.GetAt(i).try_as<FrameworkElement>();
            if (!fe) continue;
            if (fe.Name() == kOverlayVizName) {
                fe.Opacity(on ? 1.0 : g_settings.vizOverlayOpacity / 100.0);
                if (auto layer = fe.try_as<Grid>(); layer && layer.Children().Size() > 0) {
                    if (auto bars = layer.Children().GetAt(0).try_as<FrameworkElement>()) {
                        double bottom = OverlayVizBottomInset();
                        if (bars.Margin().Bottom != bottom)
                            bars.Margin({kOverlayInset, 3, kOverlayInset, bottom});
                    }
                    if (layer.ActualHeight() > 0)
                        g_overlayVizH = std::max(4.0, layer.ActualHeight() - 3.0 - OverlayVizBottomInset());
                }
                continue;
            }
            if (fe.Name() != kProgressLayerName && !fe.try_as<Grid>()) continue;  // keep the button and its fill
            if (!FittedOverlay()) fe.Opacity(on ? 0.0 : 1.0);
        }
    } catch (...) {}
}
static void UpdateVisibility() {
    if (!g_playerGrid || g_unloading || g_applyingSettings) return;
    bool hide = false, nothingPlaying = false;
    if (g_settings.hideFullscreen && IsFullscreenActive()) hide = true;
    if (!hide && g_hiddenByIdle) hide = true;
    if (!hide) {
        bool hasMedia = false, hasSession = false, stopped = false;
        { std::lock_guard<std::mutex> lk(g_mediaMtx); hasMedia = g_media.hasMedia; stopped = g_media.isStopped; }
        { std::lock_guard<std::mutex> lk(g_sessionMtx); hasSession = (g_currentSession != nullptr); }
        if (hasMedia) {
            g_lastMediaTime = std::chrono::steady_clock::now();
        }
        if (!hasSession || stopped) nothingPlaying = true;
        else if (!hasMedia) {
            auto idleMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - g_lastMediaTime).count();
            if (idleMs > 2500) nothingPlaying = true;
            else if (g_timerUpdateEvent) SetEvent(g_timerUpdateEvent);
        }

        if (g_settings.hideWhenNoMedia && !g_miniPlayerFlyoutOpen) {
            if (!hasSession) {
                hide = true;
            }
            else if (!hasMedia) {
                auto now = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - g_lastMediaTime).count();
                if (elapsed > 2500) {
                    hide = true;
                } else {
                    if (!g_unloading && g_timerUpdateEvent) SetEvent(g_timerUpdateEvent);
                }
            }
        }
    }
    try {
        if (g_playerColumn == -1) {
            if (hide) {
                g_playerGrid.Visibility(Visibility::Collapsed);
            } else {
                g_playerGrid.Visibility(Visibility::Visible);
            }
        } else {
            bool isTrackingPosition = (g_settings.position == L"taskbar_left_start" ||
                                    g_settings.position == L"taskbar_right_start" ||
                                    g_settings.position == L"taskbar_after_search_left" ||
                                    g_settings.position == L"taskbar_after_search_right" ||
                                    g_settings.position == L"taskbar_after_taskview_left" ||
                                    g_settings.position == L"taskbar_after_taskview_right" ||
                                    g_settings.position == L"taskbar_after_widgets_left" ||
                                    g_settings.position == L"taskbar_after_widgets_right" ||
                                    g_settings.position == L"taskbar_far_edge_left");
            if (hide && isTrackingPosition && g_settings.enableSmoothPositionAnimation) {
                g_playerGrid.Opacity(0.0);
                SpawnTrackedWorker([]() {
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    try {
                        RunFromWindowThread(g_taskbarWnd, [](void* param) {
                            try {
                                if (g_playerGrid) {
                                    g_playerGrid.Visibility(Visibility::Collapsed);
                                    if (g_injectionParent) {
                                        if (auto targetGrid = g_injectionParent.try_as<Grid>()) {
                                            if (g_playerColumn < (int)targetGrid.ColumnDefinitions().Size()) {
                                                auto colDef = targetGrid.ColumnDefinitions().GetAt(g_playerColumn);
                                                colDef.Width({0.0, GridUnitType::Pixel});
                                            }
                                        }
                                    }
                                    g_playerGrid.MinWidth(0);
                                    g_playerGrid.MaxWidth(0);
                                    g_playerGrid.Width(0);
                                }
                            } catch (...) {}
                        }, nullptr);
                    } catch (...) {}
                });
            } else {
                g_playerGrid.Visibility(hide ? Visibility::Collapsed : Visibility::Visible);
                g_playerGrid.Opacity(hide ? 0.0 : 1.0);
                if (g_injectionParent) {
                    if (auto targetGrid = g_injectionParent.try_as<Grid>()) {
                        if (g_playerColumn < (int)targetGrid.ColumnDefinitions().Size()) {
                            auto colDef = targetGrid.ColumnDefinitions().GetAt(g_playerColumn);
                            if (hide) {
                                colDef.Width({0.0, GridUnitType::Pixel});
                            } else {
                                colDef.Width({1.0, GridUnitType::Auto});
                            }
                        }
                    }
                } else {
                }
                if (hide) {
                    g_playerGrid.MinWidth(0);
                    g_playerGrid.MaxWidth(0);
                    g_playerGrid.Width(0);
                } else {
                    bool hasTextOrButtons = g_settings.showTrackTitle || g_settings.showTrackArtist || (g_settings.showMediaButtons && !g_mediaButtons.empty());
                    if (hasTextOrButtons && g_settings.playerMinWidth > 0) {
                        g_playerGrid.MinWidth((double)g_settings.playerMinWidth);
                    } else {
                        g_playerGrid.MinWidth(0);
                    }
                    if (g_settings.playerMaxWidth > 0) {
                        g_playerGrid.MaxWidth((double)g_settings.playerMaxWidth);
                    } else {
                        g_playerGrid.ClearValue(FrameworkElement::MaxWidthProperty());
                    }
                    g_playerGrid.ClearValue(FrameworkElement::WidthProperty());
                }
            }
        }
        ApplyVisualizerOnly(!hide && nothingPlaying && g_settings.vizEnabled && g_settings.vizOverlay &&
                            !g_miniPlayerFlyoutOpen);
        DockFitTick();
        g_playerGrid.UpdateLayout();
        if (g_settings.vizEnabled) {
            bool nowVisible = !hide;
            if (nowVisible && !g_vizCurrentlyVisible) {
                g_vizCurrentlyVisible = true;
                StartVizCaptureThread();
                StartVizTimer();
            } else if (!nowVisible && g_vizCurrentlyVisible) {
                g_vizCurrentlyVisible = false;
                StopVizTimer();
                SpawnTrackedWorker([]() { StopVizCaptureThread(); });
            }
        }
        
        if (g_settings.enableTitleScrolling || g_settings.enableArtistScrolling) {
            if (hide) StopScrollTimer();
            else      StartScrollTimer();
        }
    } catch (...) {}
}
static void ApplySettings() {
    g_idleSeconds  = 0;
    g_idleTicks    = 0;
    g_hiddenByIdle = false;
    try { RemovePlayerGrid(); } catch (...) { Wh_Log(L"ApplySettings: Exception in RemovePlayerGrid"); }
    if (!g_unloading) {
        try { InjectPlayerGrid(); } catch (...) { Wh_Log(L"ApplySettings: Exception in InjectPlayerGrid"); }
    }
}
static void ApplySettingsWithRetry(FrameworkElement xamlRootContent, int retryCount = 0) {
    static constexpr int kMaxRetries = 50;
    auto retry = [&]() {
        if (retryCount >= kMaxRetries) {
            Wh_Log(L"ApplySettingsWithRetry: giving up after %d retries, SystemTray.SystemTrayFrame not found", kMaxRetries);
            return;
        }
        auto timer = DispatcherTimer();
        timer.Interval(winrt::Windows::Foundation::TimeSpan{
            std::chrono::milliseconds(100)});
        auto tickToken = std::make_shared<winrt::event_token>();
        *tickToken = timer.Tick(
            [timer, tickToken, xamlRootContent, retryCount](
                winrt::Windows::Foundation::IInspectable const&,
                winrt::Windows::Foundation::IInspectable const&) {
                timer.Stop();
                timer.Tick(*tickToken);
                ApplySettingsWithRetry(xamlRootContent, retryCount + 1);
            });
        timer.Start();
    };
    if (g_unloading) {
        return;
    }
    auto systemTrayFrame = FindChildByClassName(xamlRootContent, L"SystemTray.SystemTrayFrame");
    if (!systemTrayFrame) {
        retry();
        return;
    }
    auto systemTrayFrameGrid = FindChildByName(systemTrayFrame, L"SystemTrayFrameGrid");
    if (!systemTrayFrameGrid) {
        retry();
        return;
    }
    ApplySettings();
}
using TrayUI_StartTaskbar_t = void(WINAPI*)(void*);
static TrayUI_StartTaskbar_t TrayUI_StartTaskbar_Original = nullptr;
static void WINAPI TrayUI_StartTaskbar_Hook(void* pThis) {
    TrayUI_StartTaskbar_Original(pThis);
    if (g_unloading) {
        return;
    }
    HWND hWnd = FindCurrentProcessTaskbarWnd();
    if (!hWnd) {
        Wh_Log(L"TrayUI_StartTaskbar_Hook: Taskbar window not found");
        return;
    }
    g_playerGrid      = nullptr;
    g_mediaIsland     = nullptr;
    g_mediaDivider    = nullptr;
    g_injectionParent = nullptr;
    g_playerColumn    = -1;
    g_trackedElement  = nullptr;
    g_hasTrackedElementOriginalMargin = false;
    g_trackPosition   = L"";
    g_layoutUpdateToken = {};
    g_taskbarWnd = hWnd;
    g_cachedAlbumTitle.clear();
    g_cachedAlbumArtist.clear();
    g_cachedThumbnailBytes.clear();
    g_cachedPaletteHash = 0;
    g_cachedAppIconSize = -1;
    g_blurBgCache.Invalidate();
    StopVizTimer();
    g_vizDispatcherTimer = nullptr;
    g_vizDispatcherTimerHasToken = false;
    StopScrollTimer();
    g_scrollDispatcherTimer = nullptr;
    g_scrollDispatcherTimerHasToken = false;
    if (g_settings.vizEnabled) {
        SpawnTrackedWorker([]() {
            StopVizCaptureThread();
            StartVizCaptureThread();
        });
        StartVizTimer();
    }
    if (g_settings.enableTitleScrolling || g_settings.enableArtistScrolling) {
        StartScrollTimer();
    }
    auto xamlRoot = GetTaskbarXamlRoot(hWnd);
    if (!xamlRoot) {
        Wh_Log(L"InjectPlayerGrid: Failed to get XAML root");
        return;
    }
    auto xamlRootContent = xamlRoot.Content().try_as<FrameworkElement>();
    if (!xamlRootContent) {
        Wh_Log(L"InjectPlayerGrid: Failed to get XAML root content");
        return;
    }
    ApplySettingsWithRetry(xamlRootContent);
}
static bool HookTaskbarDllSymbols() {
    static const wchar_t* const kCandidates[] = {
        L"taskbar.dll",
    };
    HMODULE h = nullptr;
    for (auto* name : kCandidates) {
        h = LoadLibraryExW(name, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (h) break;
    }
    if (!h) { return FALSE; }
    WindhawkUtils::SYMBOL_HOOK taskbarDllHooks[] = {
        {{LR"(const CTaskBand::`vftable'{for `ITaskListWndSite'})"},
        &CTaskBand_ITaskListWndSite_vftable},
        {{LR"(const CSecondaryTaskBand::`vftable'{for `ITaskListWndSite'})"},
        &CSecondaryTaskBand_ITaskListWndSite_vftable},
        {{LR"(public: virtual class std::shared_ptr<class TaskbarHost> __cdecl CTaskBand::GetTaskbarHost(void)const )"},
        &CTaskBand_GetTaskbarHost_Original},
        {{LR"(public: virtual class std::shared_ptr<class TaskbarHost> __cdecl CSecondaryTaskBand::GetTaskbarHost(void)const )"},
        &CSecondaryTaskBand_GetTaskbarHost_Original},
        {{LR"(public: int __cdecl TaskbarHost::FrameHeight(void)const )"},
        &TaskbarHost_FrameHeight_Original},
        {{LR"(public: void __cdecl std::_Ref_count_base::_Decref(void))"},
        &Std_Ref_Decref_Original},
        {{LR"(public: virtual void __cdecl TrayUI::StartTaskbar(void))"},
        &TrayUI_StartTaskbar_Original,
        TrayUI_StartTaskbar_Hook},
    };
    if (!WindhawkUtils::HookSymbols(h, taskbarDllHooks, ARRAYSIZE(taskbarDllHooks))) {
        return FALSE;
    }
    return TRUE;
}
BOOL ModInit() {
    g_unloading = false;
    g_applyingSettings = false;
    g_taskbarWnd = nullptr;
    g_needsUiUpdate = false;
    LoadSettings();
    if (!HookTaskbarDllSymbols()) {
        Wh_Log(L"Wh_ModInit: HookTaskbarDllSymbols failed");
        return FALSE;
    }
    return TRUE;
}
void ModAfterInit() {
    g_taskbarWnd = FindCurrentProcessTaskbarWnd();
    StartMediaThread();
    StartTimerThread();
    if (g_taskbarWnd) {
        RunFromWindowThread(g_taskbarWnd, [](void*) {
            g_cachedAlbumTitle.clear();
            g_cachedAlbumArtist.clear();
            g_cachedThumbnailBytes.clear();
            g_cachedPaletteHash = 0;
            g_cachedAppIconSize = -1;
            g_blurBgCache.Invalidate();
            ApplySettings();
            if (g_playerGrid) {
                ShowSuccessNotification();
                RefreshPlayerContents();
                UpdateVisibility();
                g_needsUiUpdate = true;
                if (g_timerUpdateEvent) {
                    SetEvent(g_timerUpdateEvent);
                }
            }
        }, nullptr);
    }
}
void ModUninit() {
    g_unloading = true;
    StopTimerThread();
    StopMediaThread();
    WaitForTrackedWorkers();
    if (g_taskbarWnd)
        RunFromWindowThread(g_taskbarWnd, [](void*) {
            DestroyMenuHost();
            RemovePlayerGrid();
            g_mediaHoverBrush   = nullptr;
            g_mediaPressedBrush = nullptr;
            g_playerHoverBrush  = nullptr;
            g_playerPressedBrush = nullptr;
            g_playerBorderBrush  = nullptr;
            g_playerBorderPressedBrush = nullptr;
            g_vizBars.reset();
            g_vizBrushes.reset();
            g_miniPlayerArtRef            = nullptr;
            g_miniPlayerTitleRef          = nullptr;
            g_miniPlayerArtistRef         = nullptr;
            g_miniPlayerPlayBtnRef        = nullptr;
            g_miniPlayerPrevBtnRef        = nullptr;
            g_miniPlayerNextBtnRef        = nullptr;
            g_miniPlayerShuffleBtnRef     = nullptr;
            g_miniPlayerRepeatBtnRef      = nullptr;
            g_miniPlayerSessionListRef    = nullptr;
            g_miniPlayerSessionListSepRef = nullptr;
            g_fluentMediaButtonStyle      = nullptr;
        }, nullptr);
    else {
        g_mediaHoverBrush   = nullptr;
        g_mediaPressedBrush = nullptr;
        g_playerHoverBrush  = nullptr;
        g_playerPressedBrush = nullptr;
        g_playerBorderBrush  = nullptr;
        g_playerBorderPressedBrush = nullptr;
        g_vizBars.reset();
        g_vizBrushes.reset();
    }
    CleanupAudioDeviceEnumerator();
}
void ModSettingsChanged() {
    g_applyingSettings = true;
    g_vizBaseColorDirty = true;
    g_vizPaletteColorsDirty = true;
    g_vizCurrentlyVisible = false;
    StopTimerThread();
    LoadSettings();
    HWND hWnd = FindCurrentProcessTaskbarWnd();
    if (!hWnd) hWnd = g_taskbarWnd;
    if (hWnd) {
        g_taskbarWnd = hWnd;
        bool ok = RunFromWindowThread(hWnd, [](void*) {
            try {
                RemovePlayerGrid();
                g_cachedAlbumTitle.clear();
                g_cachedAlbumArtist.clear();
                g_cachedThumbnailBytes.clear();
                g_cachedPaletteHash = 0;
                g_blurBgCache.Invalidate();
                if (!g_unloading) {
                    InjectPlayerGrid();
                    g_needsUiUpdate = true;
                }
            } catch (...) {
                Wh_Log(L"Wh_ModSettingsChanged: Exception during RemovePlayerGrid/InjectPlayerGrid");
                g_playerGrid = nullptr;
                g_injectionParent = nullptr;
            }
        }, nullptr);
        if (!ok) {
            Wh_Log(L"Wh_ModSettingsChanged: RunFromWindowThread failed");
        }
    }
    g_applyingSettings = false;
    StartTimerThread();
}
} // namespace fmp

// ===========================================================================
// Audio visualizer (runs in the Windhawk tool process)
// ===========================================================================
#pragma push_macro("Wh_Log")
namespace viz {
// Visualizer settings live under the "Visualizer" group.
int VizIntSetting(PCWSTR name) { return Wh_GetIntSetting(L"Visualizer.%s", name); }
// Placement "Behind widget" (1.9.0): the player draws the bars itself, so this
// process parks exactly as it does for a fullscreen app (bars hidden, capture
// stopped, source picker hidden) and the 250 ms watcher brings it back when
// the placement returns to Separate.
std::atomic<bool> g_placementOverlay{false};
PCWSTR VizStringSetting(PCWSTR name) { return Wh_GetStringSetting(L"Visualizer.%s", name); }

std::mutex g_settingsMutex;
std::atomic<bool> g_debugLogging{false};
std::atomic<int> g_frameRate{30}, g_idleDelay{10};
int g_taskbarOffset = 500, g_taskbarVerticalOffset = 0, g_mediaGap = 18;
struct AudioOptions { bool hardwareLoopbacks=true, defaultOnly=false; std::wstring filter, endpointId; };
AudioOptions g_audioOptions;
std::wstring Lowercase(std::wstring value) {
    for (auto& c : value) c = (wchar_t)towlower(c);
    return value;
}
AudioOptions ReadAudioOptions() {
    std::lock_guard<std::mutex> guard(g_settingsMutex);
    return g_audioOptions;
}
HWND g_capturePickerWnd = nullptr;
bool g_captureHover = false;
void UpdateCapturePicker();
HWND MainTaskbar() { return FindWindowW(L"Shell_TrayWnd", nullptr); }

float WidgetAwareOffset(float scale) {
    HWND taskbar = MainTaskbar();
    auto player = reinterpret_cast<INT_PTR>(GetPropW(taskbar, L"WindhawkTaskbarMediaPlayerRightDip"));
    if (player > 0) return player * scale;
    auto edge = reinterpret_cast<INT_PTR>(GetPropW(taskbar, L"WindhawkTaskbarSystemInfoRightDip"));
    if (edge <= 0) return g_taskbarOffset * scale;
    return edge > 0 ? (edge + 8) * scale : g_taskbarOffset * scale;
}

HMONITOR TaskbarMonitor() { return MonitorFromWindow(MainTaskbar(), MONITOR_DEFAULTTOPRIMARY); }
// The media island's right half (divider to the island's right edge), inner band
// only, in taskbar pixels. Published by the explorer side; false when absent.
bool VizHoverBox(float scale, D2D1_RECT_F* out) {
    HWND taskbar = MainTaskbar();
    INT_PTR v[4];
    const wchar_t* names[4] = {L"WindhawkMediaVizHoverL4", L"WindhawkMediaVizHoverR4",
                               L"WindhawkMediaVizHoverT4", L"WindhawkMediaVizHoverB4"};
    for (int i = 0; i < 4; ++i) v[i] = reinterpret_cast<INT_PTR>(GetPropW(taskbar, names[i]));
    if (v[0] <= 0 || v[1] <= v[0] || v[3] <= v[2]) return false;
    *out = D2D1::RectF(v[0] * scale / 4.f, v[2] * scale / 4.f, v[1] * scale / 4.f, v[3] * scale / 4.f);
    return true;
}
void VizDebugLog(PCWSTR format, ...) {
    if (!g_debugLogging.load(std::memory_order_relaxed)) return;
    static std::mutex mutex;
    std::lock_guard<std::mutex> guard(mutex);
    WCHAR message[2048];
    va_list args;
    va_start(args, format); vswprintf_s(message, format, args); va_end(args);
    Wh_Log(L"%s", message);
    WCHAR storage[MAX_PATH];
    if (!Wh_GetModStoragePath(storage, ARRAYSIZE(storage))) return;
    CreateDirectoryW(storage, nullptr);
    std::wstring path = std::wstring(storage) + L"\\diagnostic.log";
    WIN32_FILE_ATTRIBUTE_DATA attributes{};
    if (GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &attributes) &&
        (attributes.nFileSizeHigh || attributes.nFileSizeLow > 1024*1024)) {
        std::wstring previous = std::wstring(storage) + L"\\diagnostic.previous.log";
        MoveFileExW(path.c_str(),previous.c_str(),MOVEFILE_REPLACE_EXISTING);
    }
    FILE* file = _wfopen(path.c_str(),L"a, ccs=UTF-8");
    if(file) {
        fwprintf(file,L"%llu pid=%lu %s\n",GetTickCount64(),GetCurrentProcessId(),message);
        fclose(file);
    }
}
#undef Wh_Log
#define Wh_Log VizDebugLog


using namespace winrt::Windows::Media::Control;
using namespace winrt::Windows::Storage::Streams;

using Microsoft::WRL::ComPtr;

#ifndef DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ((DPI_AWARENESS_CONTEXT)-4)
#endif

#define TIMER_ID_MSG_DISPLAY_CHANGE 1
#define TIMER_ID_MSG_RECREATE_OVERLAY 2
#define TIMER_ID_MSG_WALLPAPER_REFRESH 3
#define TIMER_ID_MSG_FULLSCREEN_WATCH 4
#define TIMER_ID_MSG_SAVE_POSITION 5
#define TIMER_ID_MSG_FONT_RECHECK 6

#define WM_APP_CLEANUP (WM_APP + 1)
#define WM_APP_SETTINGS_CHANGED (WM_APP + 2)
#define WM_APP_RENDER_TICK (WM_APP + 3)
#define WM_APP_MEDIA_REPAINT (WM_APP + 4)
#define WM_APP_REQUEST_SAVE_POSITION (WM_APP + 5)
#define WM_APP_FORCE_REDRAW (WM_APP + 6)
#define OVERLAY_WINDOW_CLASS (L"DesktopAudioVisOverlay_" WH_MOD_ID)
#define MESSAGE_WINDOW_CLASS (L"DesktopAudioVisMessage_" WH_MOD_ID)
#define MEDIA_WINDOW_CLASS (L"DesktopAudioVisMedia_" WH_MOD_ID)

enum class VizShape { Stereo, Mountain, Mirror, Wave, Breathe, Dots, Radial, Oscilloscope };
enum class VizColorMode { Solid, Gradient, ReactiveGradient, Accent, AlbumArt, DynamicAlbum, Acrylic, RainbowCycle, Tourne };
enum class VizEQ { Default, Bass, Rock, Pop, Jazz, Electronic };
enum class VizSensitivityCurve { Exponential, Knee, Power };
enum class VizOrientation { Horizontal, Vertical };
enum class VizAnchor { Top, Middle, Bottom };
enum class VizFreqScale { Log, Linear, Mel };
enum class VizTextAlignH { Left, Center, Right };
enum class VizTextAlignV { Above, Top, Middle, Bottom, Below };
enum class VizDragModifier { None, Ctrl, Alt, Shift, Win };
enum class VizDragButton { Left, Middle, Right };
// Bit flags rather than an enum of named combos, so "is every key in the combo
// currently down" is one mask test and "does the fast key overlap the modifier"
// is one AND -- which is what the settings validator checks for.
enum VizModKeyFlags : unsigned {
    VIZ_MOD_NONE  = 0,
    VIZ_MOD_CTRL  = 1u << 0,
    VIZ_MOD_ALT   = 1u << 1,
    VIZ_MOD_SHIFT = 1u << 2,
    VIZ_MOD_WIN   = 1u << 3,
};
enum class VizKeyMoveKeys { Both, Arrows, Wasd };
// What the keyboard-move keys are currently steering. Switched live with the
// move modifier + 1/2/3, so the same combo places all three pieces without
// needing a separate shortcut per piece.
enum class VizMoveTarget { Visualizer, NowPlaying, PeakFreq, MediaControls };

struct Settings {
    VizShape shape = VizShape::Stereo;
    VizOrientation orientation = VizOrientation::Horizontal;
    int barCount = 32;
    int barWidth = 6;
    int barGap = 4;
    int barMaxSize = 140;
    int barIdleSize = 4;
    float barRadiusTL = 3.0f, barRadiusTR = 3.0f, barRadiusBR = 3.0f, barRadiusBL = 3.0f;
    VizColorMode colorMode = VizColorMode::Solid;
    BYTE colorA = 255, colorR = 255, colorG = 255, colorB = 255;
    BYTE grad1A = 255, grad1R = 30, grad1G = 215, grad1B = 96;
    BYTE grad2A = 255, grad2R = 0, grad2G = 180, grad2B = 255;
    int sensitivity = 150;
    VizSensitivityCurve sensitivityCurve = VizSensitivityCurve::Knee;
    float inputGainDb = 0.0f;
    bool autoGain = false;
    float autoGainMaxDb = 12.0f;
    int smoothing = 0;
    VizEQ eq = VizEQ::Default;

    float horizontalPosition = 50.0f;
    float verticalPosition = 88.0f;
    int monitor = 1;
    VizAnchor verticalAnchor = VizAnchor::Bottom;

    bool keyMoveEnabled = true;
    unsigned keyMoveModifier = VIZ_MOD_CTRL | VIZ_MOD_ALT;
    VizKeyMoveKeys keyMoveKeys = VizKeyMoveKeys::Both;
    int keyMoveStep = 1;
    int keyMoveFastStep = 10;
    unsigned keyMoveFastKey = VIZ_MOD_SHIFT;

    bool dragEnabled = false;
    VizDragModifier dragModifier = VizDragModifier::Ctrl;
    VizDragButton dragButton = VizDragButton::Middle;

    bool showSettingsErrors = true;

    bool backgroundEnabled = true;
    BYTE bgA = 0x60, bgR = 0, bgG = 0, bgB = 0;
    int bgPaddingL = 24, bgPaddingR = 24, bgPaddingT = 24, bgPaddingB = 24;
    float bgRadiusTL = 14.0f, bgRadiusTR = 14.0f, bgRadiusBR = 14.0f, bgRadiusBL = 14.0f;
    int bgBlur = 0;
    int bgBorderSize = 0;
    BYTE borderA = 0x40, borderR = 255, borderG = 255, borderB = 255;

    int targetFps = 60;
    bool pauseOnFullscreen = true;
    bool followTaskbarAutoHide = true;
    int pauseWhenSilentSeconds = 10;

    bool peakHoldEnabled = false;
    BYTE peakHoldA = 255, peakHoldR = 0, peakHoldG = 180, peakHoldB = 255;
    bool beatFlashEnabled = false;
    BYTE beatFlashA = 255, beatFlashR = 255, beatFlashG = 255, beatFlashB = 255;
    int beatFlashIntensity = 80;
    int rainbowSpeed = 40;

    bool nowPlayingEnabled = false;
    BYTE nowPlayingA = 255, nowPlayingR = 255, nowPlayingG = 255, nowPlayingB = 255;
    std::wstring nowPlayingFont = L"Segoe UI";
    int nowPlayingFontSize = 16;
    int nowPlayingDisplaySeconds = 6;
    int nowPlayingOffsetX = 0, nowPlayingOffsetY = 0;
    int peakFreqOffsetX = 0, peakFreqOffsetY = 0;

    // Per-overlay text panels. Alpha 0 on the fill means "no panel"; the border
    // is independent, so an outline with nothing behind it is a valid look.
    BYTE npBgA = 0, npBgR = 0, npBgG = 0, npBgB = 0;
    int npBgPadding = 6, npBgCornerRadius = 6, npBgBorderSize = 0;
    BYTE npBgBorderA = 0x40, npBgBorderR = 255, npBgBorderG = 255, npBgBorderB = 255;

    BYTE pfBgA = 0, pfBgR = 0, pfBgG = 0, pfBgB = 0;
    int pfBgPadding = 6, pfBgCornerRadius = 6, pfBgBorderSize = 0;
    BYTE pfBgBorderA = 0x40, pfBgBorderR = 255, pfBgBorderG = 255, pfBgBorderB = 255;

    bool autoHideEnabled = false;
    int autoHideDelaySeconds = 15;
    bool pauseWhenObscured = false;
    int obscuredThresholdPercent = 100;

    int fftSize = 1024;
    VizFreqScale freqScale = VizFreqScale::Log;
    bool peakFreqEnabled = false;
    VizTextAlignH peakFreqAlignH = VizTextAlignH::Right;
    VizTextAlignV peakFreqAlignV = VizTextAlignV::Top;
    bool oscilloscopeMultibandEnabled = false;

    bool mediaControlsEnabled = false;
    BYTE mediaIconColorA = 255, mediaIconColorR = 255, mediaIconColorG = 255, mediaIconColorB = 255;
    std::wstring mediaIconPrevPath;
    std::wstring mediaIconPlayPath;
    std::wstring mediaIconPausePath;
    std::wstring mediaIconNextPath;
    int mediaIconSize = 32;
    int mediaIconSpacing = 14;
    BYTE mediaPlateA = 0, mediaPlateR = 0, mediaPlateG = 0, mediaPlateB = 0;
    int mediaPlatePadding = 0;
    int mediaPlateCornerRadius = 8;
    int mediaPlateBorderSize = 0;
    BYTE mediaPlateBorderA = 0x40, mediaPlateBorderR = 255, mediaPlateBorderG = 255,
         mediaPlateBorderB = 255;
    bool mediaHideWhenCovered = false;
    int mediaCoveredThresholdPercent = 50;
    float mediaHorizontalPosition = 50.0f;
    float mediaVerticalPosition = 95.0f;
};

// A 4K display fits ~1280 bars at 2 px wide with 1 px gaps, and ultrawides more
// still, so the cap has room above that. Each bar costs a handful of floats.
constexpr int VIZ_BARS_MAX = 2048;
constexpr int VIZ_FFT_SIZE_MAX = 8192;
constexpr int VIZ_NUM_BANDS = 7;
constexpr float VIZ_PI = 3.14159265f;

// Frequency-band edges (Hz), shared between BuildLogBins (capture thread) and
// HzToBandPos (render thread) so the Log/Linear/Mel scale mapping always
// warps onto the exact same band boundaries the audio analysis actually uses.
constexpr float VIZ_FREQ_EDGES[VIZ_NUM_BANDS + 1] = {
    20.f, 120.f, 300.f, 800.f, 2500.f, 6000.f, 14000.f, 20000.f};

// Which EQ zone (0=low, 1=mid, 2=high) each band belongs to. Shared between
// the capture thread's EQ preset weighting and the multiband oscilloscope
// coloring so both agree on the same low/mid/high split.
constexpr int VIZ_BAND_EQ_ZONE[VIZ_NUM_BANDS] = {0, 0, 1, 1, 2, 2, 2};

Settings g_settings;
Settings ReadCaptureSettings() {
    std::lock_guard<std::mutex> guard(g_settingsMutex);
    return g_settings;
}

std::atomic<bool> g_initSucceeded{false};
std::atomic<ULONGLONG> g_lastInitAttempt{0};
std::atomic<bool> g_unloading{false};

ComPtr<ID3D11Device> g_d3dDevice;
ComPtr<IDXGIDevice> g_dxgiDevice;
ComPtr<IDXGIFactory2> g_dxgiFactory;
ComPtr<ID2D1Factory1> g_d2dFactory;
ComPtr<ID2D1Device> g_d2dDevice;

HWND g_messageWnd;
HWND g_mediaWnd;
std::atomic<bool> g_mediaIsPlaying{false};

// Runtime position override for the media strip, same shape as the one the
// visualizer uses: percentages of the work area, replacing the Media Controls
// Position settings once a keyboard nudge has moved it. Declared up here rather
// than with the rest of the move code because RepositionAndRepaintMediaControls
// -- which is defined well before that -- has to read it.
std::atomic<bool> g_mediaOverrideActive{false};
std::atomic<float> g_mediaOverrideH{50.0f};
std::atomic<float> g_mediaOverrideV{95.0f};

std::atomic<HWND> g_overlayWnd{nullptr};
ComPtr<IDXGISwapChain1> g_swapChain;
ComPtr<ID2D1DeviceContext> g_dc;
ComPtr<IDCompositionDevice> g_compositionDevice;
ComPtr<IDCompositionTarget> g_compositionTarget;
ComPtr<IDCompositionVisual> g_compositionVisual;
ComPtr<ID2D1SolidColorBrush> g_barBrush;
ComPtr<ID2D1SolidColorBrush> g_barBrush2;
ComPtr<ID2D1SolidColorBrush> g_backgroundBrush;
ComPtr<ID2D1SolidColorBrush> g_borderBrush;
ComPtr<ID2D1Bitmap> g_wallpaperBitmap;
ComPtr<ID2D1Effect> g_blurEffect;
// Pre-rendered result of the Gaussian blur. The blur is a full-image convolution
// and by far the most expensive Direct2D operation in the scene, but its input
// (the wallpaper) doesn't change frame to frame -- so it's evaluated once here
// and then simply blitted each frame instead of being recomputed.
ComPtr<ID2D1Bitmap1> g_blurredBitmap;

ComPtr<ID2D1PathGeometry> g_bgGeoCache;
ComPtr<ID2D1GeometryGroup> g_borderRingCache;
D2D1_RECT_F g_bgGeoCacheRect = {-1.f, -1.f, -1.f, -1.f};
float g_bgGeoCacheRadii[4] = {-1.f, -1.f, -1.f, -1.f};
int g_borderCacheBorderSize = -1;

ComPtr<ID2D1StrokeStyle> g_roundCapStrokeStyle;
ComPtr<IDWriteFactory> g_dwriteFactory;
ComPtr<IDWriteTextFormat> g_dwriteTextFormat;
ComPtr<ID2D1SolidColorBrush> g_nowPlayingBrush;
ComPtr<ID2D1SolidColorBrush> g_textPanelBrush;
int g_dwriteTextFormatFontSize = -1;
std::wstring g_dwriteTextFormatFontName;

static const IID kCLSID_D2D1GaussianBlur = {
    0x1feb6d69, 0x2fe6, 0x4ac9, {0x8c, 0x58, 0x1d, 0x7f, 0x93, 0xe7, 0xa6, 0xa5}};

float g_dpiScale = 1.0f;
FILETIME g_lastWallpaperTime = {};
std::atomic<HMONITOR> g_cachedMonitor{nullptr};

std::atomic<bool> g_captureRunning{false};
std::thread* g_captureThread = nullptr;
HANDLE g_captureEvent = nullptr;
std::atomic<bool> g_deviceChanged{false};

// Per-band energy and oscilloscope waveform are each produced as a whole array
// by the capture thread and consumed as a whole array by the render thread.
// A plain std::atomic per element only guarantees each float is torn-free on
// its own; the render thread could still read some elements from one capture
// iteration and the rest from the next, visible as a tiny inconsistency in
// the drawn trace at high refresh rates. A seqlock makes the entire array
// publish/read atomic as a unit instead, with no lock contention.
std::atomic<uint32_t> g_bandsSeq{0};
float g_bandsData[VIZ_NUM_BANDS] = {};

void PublishBands(const float (&src)[VIZ_NUM_BANDS]) {
    uint32_t seq = g_bandsSeq.load(std::memory_order_relaxed);
    g_bandsSeq.store(seq + 1, std::memory_order_release);
    memcpy(g_bandsData, src, sizeof(g_bandsData));
    g_bandsSeq.store(seq + 2, std::memory_order_release);
}

void ReadBands(float (&dst)[VIZ_NUM_BANDS]) {
    for (;;) {
        uint32_t seq1 = g_bandsSeq.load(std::memory_order_acquire);
        if (seq1 & 1) continue;
        memcpy(dst, g_bandsData, sizeof(dst));
        std::atomic_thread_fence(std::memory_order_acquire);
        if (seq1 == g_bandsSeq.load(std::memory_order_relaxed)) return;
    }
}

std::thread* g_renderThread = nullptr;
std::atomic<bool> g_renderThreadRunning{false};
std::atomic<bool> g_renderTickPending{false};

float g_hannWindow[VIZ_FFT_SIZE_MAX] = {};
float g_twiddleRe[VIZ_FFT_SIZE_MAX / 2] = {};
float g_twiddleIm[VIZ_FFT_SIZE_MAX / 2] = {};
int g_logBinStart[VIZ_NUM_BANDS + 1] = {};

float g_vizPeak[VIZ_BARS_MAX] = {};
float g_vizTarget[VIZ_BARS_MAX] = {};
float g_vizPeakHold[VIZ_BARS_MAX] = {};
float g_vizBreatheEnv = 0.f;

constexpr int VIZ_WAVE_SAMPLES = 256;

std::atomic<uint32_t> g_waveformSeq{0};
float g_waveformData[VIZ_WAVE_SAMPLES] = {};

void PublishWaveform(const float (&src)[VIZ_WAVE_SAMPLES]) {
    uint32_t seq = g_waveformSeq.load(std::memory_order_relaxed);
    g_waveformSeq.store(seq + 1, std::memory_order_release);
    memcpy(g_waveformData, src, sizeof(g_waveformData));
    g_waveformSeq.store(seq + 2, std::memory_order_release);
}

void ReadWaveform(float (&dst)[VIZ_WAVE_SAMPLES]) {
    for (;;) {
        uint32_t seq1 = g_waveformSeq.load(std::memory_order_acquire);
        if (seq1 & 1) continue;
        memcpy(dst, g_waveformData, sizeof(dst));
        std::atomic_thread_fence(std::memory_order_acquire);
        if (seq1 == g_waveformSeq.load(std::memory_order_relaxed)) return;
    }
}

std::atomic<float> g_beatPulse{0.f};
std::atomic<float> g_dominantFreqHz{0.f};

// Screen-space bounds of the last drawn frame, used by the occlusion check so
// it can test the region we actually occupy rather than the whole monitor.
std::atomic<LONG> g_drawRectL{0}, g_drawRectT{0}, g_drawRectR{0}, g_drawRectB{0};
std::atomic<bool> g_drawRectValid{false};
// Set once the auto-hide fade has reached full transparency and a single blank
// frame has been presented. While set, the render path exits immediately.
bool g_autoHideBlanked = false;

// Current swap chain dimensions and composition-visual offset. The swap chain
// covers only the widget's bounding box rather than the whole desktop, so these
// are tracked to detect when a settings/display change requires a resize.
UINT  g_swapChainWidth = 0, g_swapChainHeight = 0;
float g_visualOffsetX = 0.f, g_visualOffsetY = 0.f;

std::mutex g_nowPlayingMutex;
std::wstring g_nowPlayingDisplay;
std::atomic<ULONGLONG> g_nowPlayingChangedTick{0};

static float VIZ_SEEDS[VIZ_BARS_MAX] = {};

void BuildVizSeeds() {
    unsigned int state = 0x12345678u;
    for (int i = 0; i < VIZ_BARS_MAX; i++) {
        state = state * 1664525u + 1013904223u;
        float t = (float)(state >> 8) / (float)(1u << 24);
        VIZ_SEEDS[i] = 0.25f + t * 1.20f;
    }
}

std::atomic<bool> g_fullscreenPaused{false};
std::atomic<ULONGLONG> g_lastAudibleTickMs{0};
bool g_slowMode = false;

static std::atomic<DWORD> g_albumArtColor{0xFFFFFFFF};
static std::atomic<DWORD> g_albumArtColorSecondary{0xFFAAAAAA};
static std::atomic<bool>  g_albumArtColorReady{false};
static std::atomic<bool>  g_albumArtFetchPending{false};
static std::atomic<DWORD> g_accentColorCache{0xFF0078D4};

static HANDLE g_gsmtcStopEvent = nullptr;
// std::optional rather than a bare std::thread: there is no assignment that
// empties a std::thread (move-assigning over a joinable one calls
// std::terminate), so the optional is what gives teardown a join() + reset()
// pair. This is the documented form for a global worker thread.
[[clang::no_destroy]] static std::optional<std::thread> g_gsmtcThread;
static std::thread* g_albumArtThread = nullptr;

HMODULE GetCurrentModuleHandle() {
    HMODULE module;
    if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                               GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           L"", &module)) {
        return nullptr;
    }
    return module;
}

float GetMonitorDpiScale(HMONITOR monitor) {
    UINT dpiX = 96, dpiY = 96;
    if (SUCCEEDED(GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY))) {
        return dpiX / 96.0f;
    }
    return 1.0f;
}

HMONITOR GetMonitorById(int monitorId) {
    HMONITOR monitorResult = nullptr;
    int currentMonitorId = 0;

    auto monitorEnumProc = [&monitorResult, &currentMonitorId,
                            monitorId](HMONITOR hMonitor) -> BOOL {
        if (currentMonitorId == monitorId) {
            monitorResult = hMonitor;
            return FALSE;
        }
        currentMonitorId++;
        return TRUE;
    };

    EnumDisplayMonitors(
        nullptr, nullptr,
        // __stdcall is required: windhawk.exe is 32-bit on Windhawk 1.x, and
        // there a capture-less lambda otherwise converts to a __cdecl pointer
        // that will not bind to MONITORENUMPROC. On x86-64 there is only one
        // calling convention, so this is a no-op there.
        [](HMONITOR hMonitor, HDC, LPRECT, LPARAM dwData) __stdcall -> BOOL {
            auto& proc = *reinterpret_cast<decltype(monitorEnumProc)*>(dwData);
            return proc(hMonitor);
        },
        reinterpret_cast<LPARAM>(&monitorEnumProc));

    return monitorResult;
}

bool ParseColorHex(PCWSTR colorStr, BYTE* a, BYTE* r, BYTE* g, BYTE* b) {
    if (!colorStr || !*colorStr) {
        return false;
    }
    while (*colorStr == L' ' || *colorStr == L'\t') colorStr++;

    if (_wcsnicmp(colorStr, L"rgba", 4) == 0 || _wcsnicmp(colorStr, L"rgb", 3) == 0) {
        const WCHAR* p = wcschr(colorStr, L'(');
        if (!p) return false;
        p++;
        float v[4] = {0.f, 0.f, 0.f, 1.0f};
        int n = swscanf_s(p, L"%f , %f , %f , %f", &v[0], &v[1], &v[2], &v[3]);
        if (n < 3) return false;
        *r = (BYTE)std::clamp((int)std::lround(v[0]), 0, 255);
        *g = (BYTE)std::clamp((int)std::lround(v[1]), 0, 255);
        *b = (BYTE)std::clamp((int)std::lround(v[2]), 0, 255);
        // Alpha is CSS-style 0-1, but 0-255 is tolerated too in case someone
        // carries over an integer alpha from elsewhere.
        float alpha = (n == 4) ? v[3] : 1.0f;
        if (alpha > 1.0f) alpha /= 255.0f;
        *a = (BYTE)std::clamp((int)std::lround(alpha * 255.0f), 0, 255);
        return true;
    }

    if (*colorStr == L'#') {
        colorStr++;
    }
    size_t len = wcslen(colorStr);
    unsigned int value = 0;
    for (size_t i = 0; i < len; i++) {
        WCHAR c = colorStr[i];
        int digit;
        if (c >= L'0' && c <= L'9') digit = c - L'0';
        else if (c >= L'A' && c <= L'F') digit = c - L'A' + 10;
        else if (c >= L'a' && c <= L'f') digit = c - L'a' + 10;
        else return false;
        value = (value << 4) | digit;
    }
    if (len == 6) {
        *a = 255;
        *r = (value >> 16) & 0xFF;
        *g = (value >> 8) & 0xFF;
        *b = value & 0xFF;
    } else if (len == 8) {
        *a = (value >> 24) & 0xFF;
        *r = (value >> 16) & 0xFF;
        *g = (value >> 8) & 0xFF;
        *b = value & 0xFF;
    } else {
        return false;
    }
    return true;
}

// ---- Settings validation ---------------------------------------------------
// Windhawk's settings UI has no notion of "this field is malformed" -- it takes
// whatever you type into a free-text box and saves it. Every free-text setting
// here (colors, positions, padding, corner radii, icon paths) used to fall back
// to a default on a parse failure without saying so, which means a typo looks
// exactly like a saved setting that simply doesn't do anything. These helpers
// collect every field that failed to parse during a LoadSettings() pass so the
// mod can hand the user one summary of what it couldn't read.

std::vector<std::wstring> g_settingsIssues;

void ReportSettingIssue(PCWSTR group, PCWSTR name, PCWSTR typed, PCWSTR expected,
                        PCWSTR usedInstead) {
    // Built by concatenation rather than into a fixed buffer -- an icon path can
    // run to MAX_PATH on its own and the surrounding text is longer still.
    PCWSTR shown = (typed && *typed) ? typed : L"(blank)";
    std::wstring line = std::wstring(group) + L" \x25B8 " + name +
                        L"\r\n      you typed:  " + shown +
                        L"\r\n      expected:   " + expected +
                        L"\r\n      using:      " + usedInstead;
    g_settingsIssues.push_back(std::move(line));
    Wh_Log(L"[Settings] INVALID %s/%s value=\"%s\" expected=%s using=%s",
           group, name, shown, expected, usedInstead);
}

// Same channel as ReportSettingIssue, for a setting that parsed perfectly well
// but is going to do something you probably didn't intend. There's no "wrong
// value" to quote here, so this is free-form.
void ReportSettingWarning(PCWSTR group, PCWSTR name, const std::wstring& detail) {
    std::wstring line = std::wstring(group) + L" \x25B8 " + name + L"\r\n      " + detail;
    g_settingsIssues.push_back(std::move(line));
    Wh_Log(L"[Settings] WARNING %s/%s -- %s", group, name, line.c_str());
}

// Reads a free-text setting that must be a single number in [lo, hi]. Rejects
// trailing junk ("50px", "50 50") rather than silently taking the leading
// number, since that's exactly the kind of near-miss that looks like it worked.
float ReadNumberSetting(PCWSTR key, PCWSTR group, PCWSTR name, float def, float lo, float hi) {
    PCWSTR str = VizStringSetting(key);
    float result = def;

    WCHAR* end = nullptr;
    double parsed = (str && *str) ? wcstod(str, &end) : 0.0;
    bool parsedAnything = (str && end && end != str);
    if (parsedAnything) {
        while (*end == L' ' || *end == L'\t') end++;
    }

    if (!parsedAnything || *end) {
        WCHAR expected[128], using_[64];
        swprintf_s(expected, L"a single number from %g to %g (decimals allowed)", lo, hi);
        swprintf_s(using_, L"%g", def);
        ReportSettingIssue(group, name, str, expected, using_);
    } else if (parsed < lo || parsed > hi) {
        WCHAR expected[128], using_[64];
        swprintf_s(expected, L"a number from %g to %g", lo, hi);
        result = std::clamp((float)parsed, lo, hi);
        swprintf_s(using_, L"%g (clamped into range)", result);
        ReportSettingIssue(group, name, str, expected, using_);
    } else {
        result = (float)parsed;
    }

    Wh_FreeStringSetting(str);
    return result;
}

// Reads a color setting, reporting the exact accepted formats on failure.
void ReadColorSetting(PCWSTR key, PCWSTR group, PCWSTR name, BYTE defA, BYTE defR, BYTE defG,
                      BYTE defB, BYTE* a, BYTE* r, BYTE* g, BYTE* b) {
    PCWSTR str = VizStringSetting(key);
    if (!ParseColorHex(str, a, r, g, b)) {
        *a = defA; *r = defR; *g = defG; *b = defB;
        WCHAR using_[64];
        swprintf_s(using_, L"#%02X%02X%02X%02X", defA, defR, defG, defB);
        ReportSettingIssue(group, name, str,
                           L"#AARRGGBB, #RRGGBB, rgba(r, g, b, a) or rgb(r, g, b)", using_);
    }
    Wh_FreeStringSetting(str);
}

// Reads a "one value, or four space-separated values" box (padding, corner
// radii). Anything other than exactly 1 or 4 numbers is a mistake worth saying
// out loud -- two values in particular reads as if it might mean
// horizontal/vertical, and it doesn't.
void ReadQuadSetting(PCWSTR key, PCWSTR group, PCWSTR name, PCWSTR meaning, float def,
                     bool allowNegative, float out[4]) {
    PCWSTR str = VizStringSetting(key);
    out[0] = out[1] = out[2] = out[3] = def;

    float v[4] = {def, def, def, def};
    int n = (str && *str) ? swscanf_s(str, L"%f %f %f %f", &v[0], &v[1], &v[2], &v[3]) : 0;

    if (n == 1 || n == 4) {
        if (n == 1) v[1] = v[2] = v[3] = v[0];
        for (int k = 0; k < 4; k++) out[k] = allowNegative ? v[k] : std::max(0.0f, v[k]);
    } else {
        WCHAR expected[256], using_[64];
        swprintf_s(expected, L"one number for all sides, or four space-separated numbers for %s",
                   meaning);
        swprintf_s(using_, L"%g on all sides", def);
        ReportSettingIssue(group, name, str, expected, using_);
    }

    Wh_FreeStringSetting(str);
}

// Reads one of the "how much has to be covered" dropdowns. Stored as a string
// rather than an int because Windhawk only accepts $options on string settings
// -- same as the FFT Size dropdown. Picking from a list means it can't normally
// be wrong, but a hand-edited settings file still can be.
int ReadThresholdPercentSetting(PCWSTR key, PCWSTR group, PCWSTR name, int def) {
    PCWSTR str = VizStringSetting(key);
    int v = (str && *str) ? _wtoi(str) : 0;

    if (v < 5 || v > 100) {
        WCHAR using_[32];
        swprintf_s(using_, L"%d%%", def);
        ReportSettingIssue(group, name, str, L"a percentage from 5 to 100, in steps of 5",
                           using_);
        v = def;
    }

    Wh_FreeStringSetting(str);
    return v;
}

// Reads an optional path to an image file. Blank is valid and means "use the
// built-in glyph" -- but a path that's set and wrong is silent breakage, since
// the fallback looks identical to having left it blank.
std::wstring ReadIconPathSetting(PCWSTR key, PCWSTR group, PCWSTR name) {
    PCWSTR str = VizStringSetting(key);
    std::wstring path = str ? str : L"";

    // Users paste paths out of Explorer's address bar or "Copy as path", both of
    // which can bring quotes along; strip them rather than calling it invalid.
    while (!path.empty() && (path.front() == L'"' || path.front() == L' ')) path.erase(path.begin());
    while (!path.empty() && (path.back() == L'"' || path.back() == L' ')) path.pop_back();

    if (!path.empty()) {
        DWORD attr = GetFileAttributes(path.c_str());
        if (attr == INVALID_FILE_ATTRIBUTES) {
            ReportSettingIssue(group, name, path.c_str(),
                               L"a full path to an existing image file (PNG, JPG, BMP or ICO)",
                               L"the built-in icon");
            path.clear();
        } else if (attr & FILE_ATTRIBUTE_DIRECTORY) {
            ReportSettingIssue(group, name, path.c_str(),
                               L"a path to an image file, not to a folder",
                               L"the built-in icon");
            path.clear();
        }
    }

    Wh_FreeStringSetting(str);
    return path;
}

// A font that really is installed can still enumerate as missing right after a
// cold boot: mods start before the font service has finished registering
// everything, so the check runs against an incomplete list and warns about a
// font that works perfectly the moment anything draws with it.
//
// So a failed check does not report straight away. It arms a one-second retry
// on the message window and only reports if the font is still missing once the
// system has had time to settle. A genuinely wrong name still gets flagged,
// just ten seconds later than it used to.
static bool g_fontCheckPending = false;
static int g_fontCheckAttempts = 0;
static constexpr int FONT_CHECK_MAX_ATTEMPTS = 10;

// Checks a font family name is actually installed. A missing font falls back to
// whatever DirectWrite substitutes, which is silently not what was asked for.
bool IsFontInstalled(const std::wstring& family) {
    if (family.empty()) return false;
    HDC hdc = GetDC(nullptr);
    if (!hdc) return true;  // can't tell -- don't cry wolf

    LOGFONT lf = {};
    lf.lfCharSet = DEFAULT_CHARSET;
    lstrcpyn(lf.lfFaceName, family.c_str(), LF_FACESIZE);

    bool found = false;
    EnumFontFamiliesEx(
        hdc, &lf,
        [](const LOGFONT*, const TEXTMETRIC*, DWORD, LPARAM param) __stdcall -> int {
            *reinterpret_cast<bool*>(param) = true;
            return 0;
        },
        reinterpret_cast<LPARAM>(&found), 0);

    ReleaseDC(nullptr, hdc);
    return found;
}

PCWSTR ModKeyFlagsName(unsigned flags) {
    switch (flags) {
        case VIZ_MOD_CTRL:  return L"Ctrl";
        case VIZ_MOD_ALT:   return L"Alt";
        case VIZ_MOD_SHIFT: return L"Shift";
        case VIZ_MOD_WIN:   return L"Win";
        case VIZ_MOD_CTRL | VIZ_MOD_ALT:   return L"Ctrl + Alt";
        case VIZ_MOD_CTRL | VIZ_MOD_SHIFT: return L"Ctrl + Shift";
        case VIZ_MOD_ALT  | VIZ_MOD_SHIFT: return L"Alt + Shift";
        case VIZ_MOD_WIN  | VIZ_MOD_ALT:   return L"Win + Alt";
        case VIZ_MOD_WIN  | VIZ_MOD_SHIFT: return L"Win + Shift";
    }
    return L"None";
}

// Shown on its own thread: this runs from LoadSettings, which is called on the
// UI thread out of the settings-changed message, and a modal box there would
// wedge rendering until the user clicked OK.
HWINEVENTHOOK g_taskbarEvents = nullptr, g_foregroundEvents = nullptr;
void CALLBACK TaskbarEvent(HWINEVENTHOOK, DWORD event, HWND window, LONG object, LONG, DWORD, DWORD) {
    if(g_unloading.load()) return;
    if(event!=EVENT_SYSTEM_FOREGROUND && (window!=MainTaskbar() || object!=OBJID_WINDOW)) return;
    if(g_messageWnd) PostMessage(g_messageWnd,WM_APP+202,0,0);
}
void InstallTaskbarEvents() {
    g_taskbarEvents=SetWinEventHook(EVENT_OBJECT_CREATE,EVENT_OBJECT_LOCATIONCHANGE,nullptr,TaskbarEvent,0,0,WINEVENT_OUTOFCONTEXT|WINEVENT_SKIPOWNPROCESS);
    g_foregroundEvents=SetWinEventHook(EVENT_SYSTEM_FOREGROUND,EVENT_SYSTEM_FOREGROUND,nullptr,TaskbarEvent,0,0,WINEVENT_OUTOFCONTEXT|WINEVENT_SKIPOWNPROCESS);
}
void RemoveTaskbarEvents() {
    if(g_taskbarEvents) UnhookWinEvent(g_taskbarEvents);
    if(g_foregroundEvents) UnhookWinEvent(g_foregroundEvents);
    g_taskbarEvents=g_foregroundEvents=nullptr;
}

DWORD WINAPI SettingsIssueDialogThread(LPVOID param) {
    std::wstring* text = (std::wstring*)param;
    MessageBox(nullptr, text->c_str(), L"Seamless Media Player - Visualizer Settings",
               MB_OK | MB_ICONWARNING | MB_TOPMOST | MB_SETFOREGROUND);
    delete text;
    return 0;
}

void FlushSettingsIssues() {
    if (g_settingsIssues.empty()) return;

    std::wstring body =
        L"Seamless Media Player found something worth flagging in your settings.\r\n\r\n"
        L"Anything listed as \"you typed / expected\" couldn't be read at all, so a fallback "
        L"value is being used -- the setting is saved, it just isn't doing anything. Anything "
        L"else is a heads-up about a setting that works exactly as configured but may not do "
        L"what you expect.\r\n\r\n";
    for (const auto& issue : g_settingsIssues) {
        body += L"  \x2022  " + issue + L"\r\n\r\n";
    }
    body += L"(Turn this off under Settings Validation \x25B8 Warn About Invalid Settings.)";

    g_settingsIssues.clear();

    if (!g_settings.showSettingsErrors) return;

    HANDLE h = CreateThread(nullptr, 0, SettingsIssueDialogThread,
                            new std::wstring(std::move(body)), 0, nullptr);
    if (h) CloseHandle(h);
}

HWND GetWorkerW() {
    HWND hProgman = FindWindow(L"Progman", nullptr);
    if (!hProgman) return nullptr;

    // Progman belongs to explorer.exe, not to us -- this mod now runs as its
    // own process (see the tool-mod boilerplate at the end of this file), so
    // there's no same-process check to make here. SendMessage/FindWindowEx
    // work fine across process boundaries; this is the same technique
    // standalone desktop-overlay tools use to reach behind the icons without
    // ever injecting into explorer.
    SendMessageTimeout(hProgman, 0x052C, 0xD, 0, 100, SMTO_NORMAL, 0);
    SendMessageTimeout(hProgman, 0x052C, 0xD, 1, 100, SMTO_NORMAL, 0);

    HWND hWorkerW = nullptr;
    EnumWindows(
        [](HWND hWnd, LPARAM lParam) __stdcall -> BOOL {
            if (!FindWindowEx(hWnd, nullptr, L"SHELLDLL_DefView", nullptr)) {
                return TRUE;
            }
            HWND hWorker = FindWindowEx(nullptr, hWnd, L"WorkerW", nullptr);
            if (hWorker) {
                *(HWND*)lParam = hWorker;
                return FALSE;
            }
            return TRUE;
        },
        (LPARAM)&hWorkerW);

    if (!hWorkerW) {
        SendMessageTimeout(hProgman, 0x052C, 0, 0, 100, SMTO_NORMAL, 0);
        EnumWindows(
            [](HWND hWnd, LPARAM lParam) __stdcall -> BOOL {
                if (!FindWindowEx(hWnd, nullptr, L"SHELLDLL_DefView", nullptr)) {
                    return TRUE;
                }
                HWND hWorker = FindWindowEx(nullptr, hWnd, L"WorkerW", nullptr);
                if (hWorker) {
                    *(HWND*)lParam = hWorker;
                    return FALSE;
                }
                return TRUE;
            },
            (LPARAM)&hWorkerW);
    }

    if (!hWorkerW) {
        hWorkerW = FindWindowEx(hProgman, nullptr, L"WorkerW", nullptr);
    }
    if (!hWorkerW) {
        hWorkerW = hProgman;
    }

    return hWorkerW;
}

bool IsWindowFullscreen(HWND hwnd, HMONITOR targetMonitor = nullptr) {
    if (!hwnd || !IsWindowVisible(hwnd)) return false;

    RECT windowRect;
    if (!GetWindowRect(hwnd, &windowRect)) return false;

    HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    if (targetMonitor && monitor != targetMonitor) return false;

    MONITORINFO monitorInfo = {sizeof(MONITORINFO)};
    if (!GetMonitorInfo(monitor, &monitorInfo)) return false;

    return windowRect.left <= monitorInfo.rcMonitor.left &&
           windowRect.top <= monitorInfo.rcMonitor.top &&
           windowRect.right >= monitorInfo.rcMonitor.right &&
           windowRect.bottom >= monitorInfo.rcMonitor.bottom;
}

bool IsTaskbarCoveredBy(HWND hwnd) {
    HWND taskbar = MainTaskbar();
    if (!taskbar || !IsWindowVisible(taskbar)) return true;
    RECT tb{};
    if (!GetWindowRect(taskbar, &tb)) return true;
    if (tb.right <= tb.left || tb.bottom <= tb.top) return true;
    RECT fg{};
    if (!GetWindowRect(hwnd, &fg)) return false;
    RECT hit{};
    if (!IntersectRect(&hit, &fg, &tb)) return false;
    long long inter = (long long)(hit.right - hit.left) * (long long)(hit.bottom - hit.top);
    long long area = (long long)(tb.right - tb.left) * (long long)(tb.bottom - tb.top);
    if (area <= 0) return true;
    return inter * 100 >= area * 90;
}

// A borderless-windowed game keeps the taskbar slid off for as long as the
// game window is visible on the bar's monitor -- foreground or not. The
// foreground-only check in IsFullscreenOrGameActive goes blind in exactly
// that state: alt-tab to a window on another monitor and it answers "not
// fullscreen" while the bar stays hidden (measured live 2026-10-08). This
// asks the wider question instead: is any real application window currently
// spanning the bar's whole monitor? A maximized ordinary window cannot
// answer yes -- a resident bar's work area keeps it off the monitor's edge
// strip -- and the shell's own full-screen cloaks (Windows Input Experience
// runs 2560x1440 here, permanently, cloaked) are excluded by the same
// filters the occlusion check uses. Titled or not, topmost or not: a window
// that spans the monitor is what the shell itself reacts to, and 99% of the
// monitor's area is far past anything a snapped or maximized window reaches.
bool IsTaskbarMonitorCoveredByAnyApp() {
    HMONITOR targetMonitor = TaskbarMonitor();
    if (!targetMonitor) return false;
    MONITORINFO mi{.cbSize = sizeof(mi)};
    if (!GetMonitorInfo(targetMonitor, &mi)) return false;
    RECT mon = mi.rcMonitor;
    long long monitorArea = (long long)(mon.right - mon.left) * (mon.bottom - mon.top);
    if (monitorArea <= 0) return false;

    struct MonCoverCtx {
        const RECT* mon;
        long long monitorArea;
        DWORD ownPid;
        bool covered;
    } ctx{&mon, monitorArea, GetCurrentProcessId(), false};

    EnumWindows(
        [](HWND hWnd, LPARAM lParam) __stdcall -> BOOL {
            auto* c = reinterpret_cast<MonCoverCtx*>(lParam);

            // The mod's own windows (overlay, media strip, picker) park over
            // the taskbar, never across the monitor, but when this runs as
            // the standalone tool process they belong to us all the same.
            if (GetWindowThreadProcessId(hWnd, nullptr) == c->ownPid) return TRUE;

            if (!IsWindowVisible(hWnd) || IsIconic(hWnd)) return TRUE;
            if (hWnd != GetAncestor(hWnd, GA_ROOTOWNER)) return TRUE;

            LONG_PTR exStyle = GetWindowLongPtr(hWnd, GWL_EXSTYLE);
            if (exStyle & (WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE))
                return TRUE;
            if (GetWindowLongPtr(hWnd, GWL_STYLE) & WS_CHILD) return TRUE;

            WCHAR cls[64] = {};
            if (GetClassName(hWnd, cls, ARRAYSIZE(cls))) {
                if (_wcsicmp(cls, L"Progman") == 0 || _wcsicmp(cls, L"WorkerW") == 0 ||
                    _wcsicmp(cls, L"Shell_TrayWnd") == 0 ||
                    _wcsicmp(cls, L"Shell_SecondaryTrayWnd") == 0 ||
                    _wcsicmp(cls, L"Windows.UI.Core.CoreWindow") == 0 ||
                    _wcsicmp(cls, L"Windows.UI.Composition.DesktopWindowContentBridge") == 0 ||
                    _wcsicmp(cls, L"XamlExplorerHostIslandWindow") == 0 ||
                    _wcsicmp(cls, L"TopLevelWindowForOverflowXamlIsland") == 0 ||
                    _wcsicmp(cls, L"ForegroundStaging") == 0 ||
                    _wcsicmp(cls, L"MultitaskingViewFrame") == 0) {
                    return TRUE;
                }
            }

            int cloaked = 0;
            if (SUCCEEDED(DwmGetWindowAttribute(hWnd, DWMWA_CLOAKED, &cloaked,
                                                sizeof(cloaked))) && cloaked) {
                return TRUE;
            }

            RECT wr;
            if (!GetWindowRect(hWnd, &wr)) return TRUE;
            if (wr.right <= wr.left || wr.bottom <= wr.top) return TRUE;

            RECT clipped;
            if (!IntersectRect(&clipped, &wr, c->mon)) return TRUE;
            long long area = (long long)(clipped.right - clipped.left) *
                             (clipped.bottom - clipped.top);
            if (area * 100 >= c->monitorArea * 99) {
                c->covered = true;
                return FALSE;
            }
            return TRUE;
        },
        reinterpret_cast<LPARAM>(&ctx));

    return ctx.covered;
}

bool IsFullscreenOrGameActive() {
    HMONITOR targetMonitor = TaskbarMonitor();
    if (!targetMonitor) targetMonitor = MonitorFromPoint({0, 0}, MONITOR_DEFAULTTONEAREST);

    HWND hwndForeground = GetForegroundWindow();
    if (!hwndForeground) return false;

    WCHAR className[256];
    if (GetClassName(hwndForeground, className, ARRAYSIZE(className))) {
        if (_wcsicmp(className, L"Progman") == 0 ||
            _wcsicmp(className, L"WorkerW") == 0 ||
            _wcsicmp(className, L"Shell_TrayWnd") == 0) {
            return false;
        }
    }

    HMONITOR foregroundMonitor = MonitorFromWindow(hwndForeground, MONITOR_DEFAULTTONEAREST);
    if (foregroundMonitor != targetMonitor) return false;

    // Borderless windowed games rarely report the D3D fullscreen notification
    // state, but they do cover the taskbar rect itself. Checking the taskbar
    // rect directly catches those, while the full-monitor check below catches
    // exclusive fullscreen modes.
    if (IsTaskbarCoveredBy(hwndForeground)) return true;

    QUERY_USER_NOTIFICATION_STATE state;
    if (SUCCEEDED(SHQueryUserNotificationState(&state))) {
        if (state == QUNS_RUNNING_D3D_FULL_SCREEN || state == QUNS_PRESENTATION_MODE)
            return true;
    }

    if (IsWindowFullscreen(hwndForeground, targetMonitor))
        return true;

    return false;
}

// One answer shared by the fullscreen watcher, the overlay self-heal and the
// media repaint gate, so the three can never disagree about whether the
// hide-everything state is active. The foreground path is immediate; the
// wider borderless-cover path needs two agreeing evaluations before it may
// hide anything on its own -- a window that spans the monitor for a single
// sample (a fast alt-tab through a launcher, a transient splash) must not
// park the strip, the same visible-bias the follow model applies. Once the
// cover holds, it acts exactly like the foreground path.
bool IsFullscreenPauseConditionActive() {
    if (g_placementOverlay.load()) return true;
    if (!g_settings.pauseOnFullscreen) return false;
    if (IsFullscreenOrGameActive()) return true;

    static unsigned s_coverStreak = 0;
    if (!IsTaskbarMonitorCoveredByAnyApp()) {
        s_coverStreak = 0;
        return false;
    }
    return ++s_coverStreak >= 2;
}

// Returns true when the region the visualizer occupies is fully covered by some
// ordinary window. The widget lives on the desktop (behind icons), so any
// maximized app hides it completely -- yet without this check we'd keep running
// the full render path at the target frame rate drawing pixels nobody can see.
// Deliberately conservative: only *full* containment counts, so partial overlap
// never causes the visualizer to vanish while it's still partly visible.
// Returns how much of `target` (in virtual-screen coordinates) is underneath
// real application windows, as a percentage of its area.
//
// Coverage is accumulated into a GDI region rather than tested per window, so
// several windows that each hide part of the box add up correctly instead of
// each being judged on its own -- two windows covering opposite halves read as
// 100%, which is what you see on screen. GetRegionData hands back a set of
// non-overlapping rectangles, so summing their areas double-counts nothing.
// topmostOnly: the strip is itself a topmost window parked over the taskbar,
// so an ordinary window's rect can intersect the strip's rect without covering
// anything the user sees -- the taskbar is above normal windows and the strip
// is above the taskbar. When set, only WS_EX_TOPMOST windows count as
// coverers; fullscreen surfaces are handled by the fullscreen watcher.
int ComputeRectCoveragePercent(const RECT& targetIn, bool topmostOnly) {
    if (targetIn.right <= targetIn.left || targetIn.bottom <= targetIn.top) return 0;

    // Judge only the part that is actually on a screen.
    //
    // Area hanging off an edge can never intersect a window rect, so leaving it
    // in the denominator permanently caps the result below 100%. At the default
    // "100% covered" threshold that makes Pause When Covered unreachable for any
    // visualizer positioned partly off-screen, which is a common placement along
    // the bottom edge, and the feature simply appears to do nothing.
    RECT screen;
    screen.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
    screen.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
    screen.right = screen.left + GetSystemMetrics(SM_CXVIRTUALSCREEN);
    screen.bottom = screen.top + GetSystemMetrics(SM_CYVIRTUALSCREEN);

    RECT target;
    if (!IntersectRect(&target, &targetIn, &screen)) {
        // Nothing of it is on screen at all. Reported as uncovered rather than
        // fully covered, staying with this function's existing bias: a wrong
        // answer that keeps drawing is a far smaller problem than one that makes
        // the visualizer vanish.
        return 0;
    }

    HRGN coveredRgn = CreateRectRgn(0, 0, 0, 0);
    if (!coveredRgn) return 0;

    struct EnumCtx {
        RECT viz;
        HRGN covered;
        bool topmostOnly;
    } ctx{target, coveredRgn, topmostOnly};

    EnumWindows(
        [](HWND hWnd, LPARAM lParam) __stdcall -> BOOL {
            auto* c = reinterpret_cast<EnumCtx*>(lParam);

            if (!IsWindowVisible(hWnd) || IsIconic(hWnd)) return TRUE;

            // Only genuine application windows count as covering the desktop.
            // This is the standard "would it show up in Alt-Tab" test, and it is
            // what makes this check reliable on Windows 11: the shell is full of
            // XAML islands, composition bridges and flyout hosts (Quick Settings,
            // media popups, the taskbar's own sub-windows) that report themselves
            // as visible, often span large areas, and hide nothing at all.
            if (hWnd != GetAncestor(hWnd, GA_ROOTOWNER)) return TRUE;

            LONG_PTR exStyle = GetWindowLongPtr(hWnd, GWL_EXSTYLE);
            if (exStyle & WS_EX_TOOLWINDOW) return TRUE;
            if (c->topmostOnly && !(exStyle & WS_EX_TOPMOST)) return TRUE;
            if (exStyle & WS_EX_TRANSPARENT) return TRUE;
            if (exStyle & WS_EX_NOACTIVATE) return TRUE;

            // A real app window has a caption or is a normal overlapped window.
            LONG_PTR style = GetWindowLongPtr(hWnd, GWL_STYLE);
            if (style & WS_CHILD) return TRUE;

            WCHAR cls[64] = {};
            if (GetClassName(hWnd, cls, ARRAYSIZE(cls))) {
                if (_wcsicmp(cls, L"Progman") == 0 || _wcsicmp(cls, L"WorkerW") == 0 ||
                    _wcsicmp(cls, L"Shell_TrayWnd") == 0 ||
                    _wcsicmp(cls, L"Shell_SecondaryTrayWnd") == 0 ||
                    _wcsicmp(cls, L"Windows.UI.Core.CoreWindow") == 0 ||
                    _wcsicmp(cls, L"Windows.UI.Composition.DesktopWindowContentBridge") == 0 ||
                    _wcsicmp(cls, L"XamlExplorerHostIslandWindow") == 0 ||
                    _wcsicmp(cls, L"TopLevelWindowForOverflowXamlIsland") == 0 ||
                    _wcsicmp(cls, L"ForegroundStaging") == 0 ||
                    _wcsicmp(cls, L"MultitaskingViewFrame") == 0) {
                    return TRUE;
                }
            }

            // An untitled window is almost always infrastructure rather than a
            // real application the user is looking at.
            if (GetWindowTextLength(hWnd) == 0) return TRUE;

            // Skip DWM-cloaked windows. This is the important one: on Windows
            // 10/11 a great many UWP/XAML windows report IsWindowVisible() ==
            // TRUE while being entirely invisible (cloaked), and several of them
            // are sized to the full screen. Without this check they register as
            // covering the visualizer and hide it while nothing is really there.
            int cloaked = 0;
            if (SUCCEEDED(DwmGetWindowAttribute(hWnd, DWMWA_CLOAKED, &cloaked,
                                                sizeof(cloaked))) && cloaked) {
                return TRUE;
            }

            RECT wr;
            if (!GetWindowRect(hWnd, &wr)) return TRUE;

            // Ignore degenerate/zero-area windows.
            if (wr.right <= wr.left || wr.bottom <= wr.top) return TRUE;

            RECT hit;
            if (!IntersectRect(&hit, &wr, &c->viz)) return TRUE;

            HRGN piece = CreateRectRgn(hit.left, hit.top, hit.right, hit.bottom);
            if (piece) {
                CombineRgn(c->covered, c->covered, piece, RGN_OR);
                DeleteObject(piece);
            }
            return TRUE;
        },
        reinterpret_cast<LPARAM>(&ctx));

    long long coveredArea = 0;
    DWORD dataSize = GetRegionData(coveredRgn, 0, nullptr);
    if (dataSize) {
        std::vector<BYTE> buf(dataSize);
        RGNDATA* rd = reinterpret_cast<RGNDATA*>(buf.data());
        if (GetRegionData(coveredRgn, dataSize, rd) == dataSize) {
            const RECT* rects = reinterpret_cast<const RECT*>(rd->Buffer);
            for (DWORD i = 0; i < rd->rdh.nCount; i++) {
                coveredArea += (long long)(rects[i].right - rects[i].left) *
                               (long long)(rects[i].bottom - rects[i].top);
            }
        }
    }
    DeleteObject(coveredRgn);

    long long totalArea = (long long)(target.right - target.left) *
                          (long long)(target.bottom - target.top);
    if (totalArea <= 0) return 0;
    return (int)std::min<long long>(100, (coveredArea * 100) / totalArea);
}

bool IsVisualizerOccluded() {
    if (!g_drawRectValid.load(std::memory_order_relaxed)) return false;

    RECT viz;
    viz.left   = g_drawRectL.load(std::memory_order_relaxed);
    viz.top    = g_drawRectT.load(std::memory_order_relaxed);
    viz.right  = g_drawRectR.load(std::memory_order_relaxed);
    viz.bottom = g_drawRectB.load(std::memory_order_relaxed);

    int threshold = std::clamp(g_settings.obscuredThresholdPercent, 5, 100);
    int covered = ComputeRectCoveragePercent(viz, true);
    bool occluded = covered >= threshold;

    // Logged on the transition only -- this runs once a second, and a line per
    // second for as long as a window happens to be open would bury everything
    // else in the log.
    static bool s_lastOccluded = false;
    if (occluded != s_lastOccluded) {
        Wh_Log(L"[Viz] %s: %d%% covered (threshold %d%%)",
               occluded ? L"occluded" : L"visible again", covered, threshold);
        s_lastOccluded = occluded;
    }
    return occluded;
}

// Same measurement, aimed at the media strip's own rect. The strip is topmost,
// so nothing ever covers it on screen -- "covered" here means a real window is
// sitting underneath it, which is when it's in the way rather than useful.
bool IsMediaStripCovered() {
    if (!g_mediaWnd) return false;

    RECT strip;
    if (!GetWindowRect(g_mediaWnd, &strip)) return false;

    int threshold = std::clamp(g_settings.mediaCoveredThresholdPercent, 5, 100);
    return ComputeRectCoveragePercent(strip, true) >= threshold;
}

void RefreshAccentColorCache() {
    HKEY hKey = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER,
                      L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Accent",
                      0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD color = 0, size = sizeof(color), type = 0;
        if (RegQueryValueExW(hKey, L"AccentColorMenu", nullptr, &type,
                             (LPBYTE)&color, &size) == ERROR_SUCCESS && type == REG_DWORD) {
            RegCloseKey(hKey);
            BYTE r = (color >>  0) & 0xFF;
            BYTE g = (color >>  8) & 0xFF;
            BYTE b = (color >> 16) & 0xFF;
            g_accentColorCache.store(0xFF000000 | ((DWORD)r << 16) | ((DWORD)g << 8) | b,
                                     std::memory_order_relaxed);
            return;
        }
        if (RegQueryValueExW(hKey, L"AccentColor", nullptr, &type,
                             (LPBYTE)&color, &size) == ERROR_SUCCESS && type == REG_DWORD) {
            RegCloseKey(hKey);
            BYTE r = (color >>  0) & 0xFF;
            BYTE g = (color >>  8) & 0xFF;
            BYTE b = (color >> 16) & 0xFF;
            g_accentColorCache.store(0xFF000000 | ((DWORD)r << 16) | ((DWORD)g << 8) | b,
                                     std::memory_order_relaxed);
            return;
        }
        RegCloseKey(hKey);
    }

    DWORD color = 0; BOOL opaque = FALSE;
    if (SUCCEEDED(DwmGetColorizationColor(&color, &opaque)))
        g_accentColorCache.store(0xFF000000 | (color & 0x00FFFFFF), std::memory_order_relaxed);
}

DWORD GetWindowsAccentColor() {
    return g_accentColorCache.load(std::memory_order_relaxed);
}

void FetchAlbumArtColorAsync() {
    bool expected = false;
    if (!g_albumArtFetchPending.compare_exchange_strong(expected, true))
        return;

    if (g_albumArtThread) {
        if (g_albumArtThread->joinable())
            g_albumArtThread->join();
        delete g_albumArtThread;
        g_albumArtThread = nullptr;
    }

    g_albumArtThread = new std::thread([]() {
        try {
            winrt::init_apartment(winrt::apartment_type::multi_threaded);
            auto mgr = GlobalSystemMediaTransportControlsSessionManager::RequestAsync().get();
            if (!mgr) { winrt::uninit_apartment(); g_albumArtFetchPending.store(false); return; }
            auto session = mgr.GetCurrentSession();
            if (!session) { winrt::uninit_apartment(); g_albumArtFetchPending.store(false); return; }

            auto props = session.TryGetMediaPropertiesAsync().get();
            if (!props) { winrt::uninit_apartment(); g_albumArtFetchPending.store(false); return; }

            {
                std::wstring title(props.Title());
                std::wstring artist(props.Artist());
                std::wstring display = artist.empty() ? title
                                      : title.empty()  ? artist
                                                        : (artist + L" - " + title);
                if (!display.empty()) {
                    std::lock_guard<std::mutex> lock(g_nowPlayingMutex);
                    if (g_nowPlayingDisplay != display) {
                        g_nowPlayingDisplay = display;
                        g_nowPlayingChangedTick.store(GetTickCount64(), std::memory_order_relaxed);
                    }
                }
            }

            auto thumbRef = props.Thumbnail();
            if (!thumbRef) { winrt::uninit_apartment(); g_albumArtFetchPending.store(false); return; }

            auto stream = thumbRef.OpenReadAsync().get();
            if (!stream) { winrt::uninit_apartment(); g_albumArtFetchPending.store(false); return; }

            UINT64 sz = stream.Size();
            if (sz == 0 || sz > 4 * 1024 * 1024) { winrt::uninit_apartment(); g_albumArtFetchPending.store(false); return; }

            DataReader reader(stream);
            reader.LoadAsync((UINT32)sz).get();
            std::vector<BYTE> thumbBytes((size_t)sz);
            reader.ReadBytes(winrt::array_view<BYTE>(thumbBytes));
            reader.DetachStream();

            IWICImagingFactory* pFactory = nullptr;
            if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                        IID_PPV_ARGS(&pFactory))) || !pFactory) {
                winrt::uninit_apartment(); g_albumArtFetchPending.store(false); return;
            }
            IStream* pStream = SHCreateMemStream(thumbBytes.data(), (UINT)thumbBytes.size());
            if (!pStream) { pFactory->Release(); winrt::uninit_apartment(); g_albumArtFetchPending.store(false); return; }

            IWICBitmapDecoder* pDecoder = nullptr;
            IWICBitmapFrameDecode* pFrame = nullptr;
            IWICFormatConverter* pConv = nullptr;
            std::vector<BYTE> pixels;
            int imgW = 0, imgH = 0;

            if (SUCCEEDED(pFactory->CreateDecoderFromStream(pStream, nullptr,
                    WICDecodeMetadataCacheOnDemand, &pDecoder)) &&
                SUCCEEDED(pDecoder->GetFrame(0, &pFrame)) &&
                SUCCEEDED(pFactory->CreateFormatConverter(&pConv))) {
                if (SUCCEEDED(pConv->Initialize(pFrame, GUID_WICPixelFormat32bppBGRA,
                        WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeMedianCut))) {
                    UINT w = 0, h = 0;
                    pConv->GetSize(&w, &h);
                    if (w > 0 && h > 0) {
                        pixels.resize((size_t)w * h * 4);
                        if (SUCCEEDED(pConv->CopyPixels(nullptr, w * 4,
                                (UINT)pixels.size(), pixels.data()))) {
                            imgW = (int)w; imgH = (int)h;
                        }
                    }
                }
            }
            if (pConv)    pConv->Release();
            if (pFrame)   pFrame->Release();
            if (pDecoder) pDecoder->Release();
            pStream->Release();
            pFactory->Release();

            if (!pixels.empty()) {
                struct Bucket { uint32_t r=0,g=0,b=0,n=0; };
                Bucket buckets[16][16][16]{};
                for (int y = 0; y < imgH; y += 4) {
                    for (int x = 0; x < imgW; x += 4) {
                        size_t idx = ((size_t)y * imgW + x) * 4;
                        if (idx + 4 > pixels.size()) continue;
                        BYTE pb = pixels[idx], pg = pixels[idx+1], pr = pixels[idx+2];
                        int luma = (pr * 299 + pg * 587 + pb * 114) / 1000;
                        if (luma < 24 || luma > 235) continue;
                        auto& bk = buckets[pr >> 4][pg >> 4][pb >> 4];
                        bk.r += pr; bk.g += pg; bk.b += pb; bk.n++;
                    }
                }

                struct Cand { float w; BYTE r,g,b; };
                std::vector<Cand> cands;
                cands.reserve(64);
                for (int R = 0; R < 16; R++) for (int G = 0; G < 16; G++) for (int B = 0; B < 16; B++) {
                    auto& bk = buckets[R][G][B];
                    if (bk.n < 8) continue;
                    float fr = bk.r/(float)bk.n/255.f, fg = bk.g/(float)bk.n/255.f, fb = bk.b/(float)bk.n/255.f;
                    float mx = std::max({fr,fg,fb}), mn = std::min({fr,fg,fb});
                    float sat = mx > 0 ? (mx - mn) / mx : 0;
                    cands.push_back({ bk.n * (0.3f + sat),
                                     (BYTE)(fr*255), (BYTE)(fg*255), (BYTE)(fb*255) });
                }

                if (!cands.empty()) {
                    std::sort(cands.begin(), cands.end(),
                              [](const Cand& a, const Cand& b){ return a.w > b.w; });

                    BYTE pR = cands[0].r, pG = cands[0].g, pB = cands[0].b;

                    BYTE sR = pR, sG = pG, sB = pB;
                    for (auto& c : cands) {
                        int dr = (int)c.r - (int)pR;
                        int dg = (int)c.g - (int)pG;
                        int db = (int)c.b - (int)pB;
                        if (dr*dr + dg*dg + db*db > 3264) {
                            sR = c.r; sG = c.g; sB = c.b;
                            break;
                        }
                    }

                    DWORD col  = 0xFF000000 | ((DWORD)pR << 16) | ((DWORD)pG << 8) | pB;
                    DWORD col2 = 0xFF000000 | ((DWORD)sR << 16) | ((DWORD)sG << 8) | sB;
                    g_albumArtColor.store(col,  std::memory_order_relaxed);
                    g_albumArtColorSecondary.store(col2, std::memory_order_relaxed);
                    g_albumArtColorReady.store(true, std::memory_order_relaxed);
                }
            }
        } catch (...) {}
        try { winrt::uninit_apartment(); } catch (...) {}
        g_albumArtFetchPending.store(false);
    });
}

static winrt::event_token g_gsmtcMediaPropsToken{};
static winrt::event_token g_gsmtcPlaybackToken{};
static winrt::event_token g_gsmtcSessionToken{};
[[clang::no_destroy]] static GlobalSystemMediaTransportControlsSessionManager g_gsmtcMgr{ nullptr };
[[clang::no_destroy]] static GlobalSystemMediaTransportControlsSession        g_gsmtcSession{ nullptr };

void RefreshMediaPlaybackStatus() {
    if (!g_gsmtcSession) return;
    try {
        auto info = g_gsmtcSession.GetPlaybackInfo();
        bool playing = info && info.PlaybackStatus() ==
            GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing;
        g_mediaIsPlaying.store(playing, std::memory_order_relaxed);
    } catch (...) {}
    if (g_mediaWnd) PostMessage(g_mediaWnd, WM_APP_MEDIA_REPAINT, 0, 0);
}

void SetupGsmtcSessionListener() {
    if (!g_gsmtcMgr) return;
    try {
        if (g_gsmtcSession) {
            try { g_gsmtcSession.MediaPropertiesChanged(g_gsmtcMediaPropsToken); } catch (...) {}
            try { g_gsmtcSession.PlaybackInfoChanged(g_gsmtcPlaybackToken); } catch (...) {}
            g_gsmtcSession = nullptr;
        }
        g_gsmtcSession = g_gsmtcMgr.GetCurrentSession();
        if (!g_gsmtcSession) return;
        g_gsmtcMediaPropsToken = g_gsmtcSession.MediaPropertiesChanged(
            [](auto const&, auto const&) {
                if (g_settings.colorMode == VizColorMode::AlbumArt ||
                    g_settings.colorMode == VizColorMode::DynamicAlbum ||
                    g_settings.nowPlayingEnabled)
                    FetchAlbumArtColorAsync();
            });
        g_gsmtcPlaybackToken = g_gsmtcSession.PlaybackInfoChanged(
            [](auto const&, auto const&) { RefreshMediaPlaybackStatus(); });
        RefreshMediaPlaybackStatus();
    } catch (...) {}
}

void InitGsmtcListener() {
    if (g_gsmtcStopEvent) return;
    g_gsmtcStopEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    if (!g_gsmtcStopEvent) return;

    g_gsmtcThread.emplace([]() {
        try {
            winrt::init_apartment(winrt::apartment_type::multi_threaded);
            g_gsmtcMgr = GlobalSystemMediaTransportControlsSessionManager::RequestAsync().get();
            if (!g_gsmtcMgr) { winrt::uninit_apartment(); return; }

            g_gsmtcSessionToken = g_gsmtcMgr.CurrentSessionChanged(
                [](auto const&, auto const&) {
                    SetupGsmtcSessionListener();
                    if (g_settings.colorMode == VizColorMode::AlbumArt ||
                        g_settings.colorMode == VizColorMode::DynamicAlbum ||
                        g_settings.nowPlayingEnabled)
                        FetchAlbumArtColorAsync();
                });

            SetupGsmtcSessionListener();
            if (g_settings.colorMode == VizColorMode::AlbumArt ||
                g_settings.colorMode == VizColorMode::DynamicAlbum ||
                g_settings.nowPlayingEnabled)
                FetchAlbumArtColorAsync();
        } catch (...) {}

        if (g_gsmtcStopEvent)
            WaitForSingleObject(g_gsmtcStopEvent, INFINITE);

        try {
            if (g_gsmtcSession) {
                g_gsmtcSession.MediaPropertiesChanged(g_gsmtcMediaPropsToken);
                g_gsmtcSession.PlaybackInfoChanged(g_gsmtcPlaybackToken);
            }
            if (g_gsmtcMgr) {
                g_gsmtcMgr.CurrentSessionChanged(g_gsmtcSessionToken);
            }
            g_gsmtcSession = nullptr;
            g_gsmtcMgr     = nullptr;
            winrt::uninit_apartment();
        } catch (...) {}
    });
}

static bool g_gsmtcStarted = false;

// ---- Media control buttons -------------------------------------------------
// A small always-on-top, clickable strip (Previous / Play-Pause / Next), wired
// to whichever app is currently playing media via the same GSMTC session used
// for Now Playing. This lives in its own layered window rather than the main
// overlay's swap chain: the overlay is WS_EX_TRANSPARENT on purpose (it sits
// behind the desktop icons and must never eat clicks), so a window that needs
// to actually receive clicks has to be a separate, non-transparent surface.

std::thread* g_mediaCmdThread = nullptr;
std::atomic<bool> g_mediaCmdPending{false};
std::atomic<int> g_mediaCmdQueued{-1};

void SendMediaCommand(int cmd) {
    g_mediaCmdQueued.store(cmd, std::memory_order_relaxed);

    bool expected = false;
    if (!g_mediaCmdPending.compare_exchange_strong(expected, true))
        return;

    if (g_mediaCmdThread) {
        if (g_mediaCmdThread->joinable())
            g_mediaCmdThread->join();
        delete g_mediaCmdThread;
        g_mediaCmdThread = nullptr;
    }

    g_mediaCmdThread = new std::thread([]() {
        int cmd = g_mediaCmdQueued.load(std::memory_order_relaxed);
        try {
            winrt::init_apartment(winrt::apartment_type::multi_threaded);
            auto mgr = GlobalSystemMediaTransportControlsSessionManager::RequestAsync().get();
            if (mgr) {
                auto session = mgr.GetCurrentSession();
                if (session) {
                    if (cmd == 0)      session.TrySkipPreviousAsync().get();
                    else if (cmd == 1) session.TryTogglePlayPauseAsync().get();
                    else if (cmd == 2) session.TrySkipNextAsync().get();
                }
            }
        } catch (...) {}
        try { winrt::uninit_apartment(); } catch (...) {}
        g_mediaCmdPending.store(false, std::memory_order_relaxed);
    });
}

// icon slot order: 0=prev, 1=play, 2=pause, 3=next. An empty vector means "no
// custom icon loaded for this slot -- draw the built-in glyph instead."
std::vector<BYTE> g_mediaIconPixels[4];
int g_mediaIconLoadedSize = 0;

float GetMediaControlsDpiScale() {
    HMONITOR monitor = TaskbarMonitor();
    if (!monitor) monitor = MonitorFromPoint({0, 0}, MONITOR_DEFAULTTONEAREST);
    return GetMonitorDpiScale(monitor);
}

// Decodes a user-supplied image file to a square, premultiplied 32bpp BGRA
// buffer at targetSize -- the format UpdateLayeredWindow's AC_SRC_ALPHA blend
// expects. Returns false (and clears outPixels) on any failure, so callers can
// fall back to the built-in glyph rather than showing a blank button.
bool LoadMediaIconFromFile(const std::wstring& path, int targetSize, std::vector<BYTE>& outPixels) {
    outPixels.clear();
    if (path.empty() || targetSize <= 0) return false;

    IWICImagingFactory* pFactory = nullptr;
    if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                IID_PPV_ARGS(&pFactory))) || !pFactory) {
        return false;
    }

    bool ok = false;
    IWICBitmapDecoder* pDecoder = nullptr;
    IWICBitmapFrameDecode* pFrame = nullptr;
    IWICFormatConverter* pConv = nullptr;
    IWICBitmapScaler* pScaler = nullptr;

    if (SUCCEEDED(pFactory->CreateDecoderFromFilename(path.c_str(), nullptr, GENERIC_READ,
            WICDecodeMetadataCacheOnDemand, &pDecoder)) &&
        SUCCEEDED(pDecoder->GetFrame(0, &pFrame)) &&
        SUCCEEDED(pFactory->CreateFormatConverter(&pConv)) &&
        SUCCEEDED(pConv->Initialize(pFrame, GUID_WICPixelFormat32bppBGRA,
            WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeMedianCut)) &&
        SUCCEEDED(pFactory->CreateBitmapScaler(&pScaler)) &&
        SUCCEEDED(pScaler->Initialize(pConv, (UINT)targetSize, (UINT)targetSize,
            WICBitmapInterpolationModeFant))) {
        outPixels.resize((size_t)targetSize * targetSize * 4);
        if (SUCCEEDED(pScaler->CopyPixels(nullptr, targetSize * 4, (UINT)outPixels.size(),
                outPixels.data()))) {
            for (size_t i = 0; i + 3 < outPixels.size(); i += 4) {
                BYTE a = outPixels[i + 3];
                outPixels[i + 0] = (BYTE)(outPixels[i + 0] * a / 255);
                outPixels[i + 1] = (BYTE)(outPixels[i + 1] * a / 255);
                outPixels[i + 2] = (BYTE)(outPixels[i + 2] * a / 255);
            }
            ok = true;
        }
    }

    if (pScaler)  pScaler->Release();
    if (pConv)    pConv->Release();
    if (pFrame)   pFrame->Release();
    if (pDecoder) pDecoder->Release();
    pFactory->Release();

    if (!ok) outPixels.clear();
    return ok;
}

// LoadSettings already rejected paths that don't exist. A path that exists but
// still won't decode means the file isn't an image format WIC can read, and
// that's worth saying out loud rather than silently drawing the built-in glyph.
void LoadMediaIconSlot(const std::wstring& path, int sizePx, std::vector<BYTE>& out, PCWSTR label) {
    if (!LoadMediaIconFromFile(path, sizePx, out) && !path.empty()) {
        Wh_Log(L"[Media] %s icon could not be decoded: %s", label, path.c_str());
    }
}

void RecreateMediaControlResources() {
    float dpiScale = GetMediaControlsDpiScale();
    int sizePx = std::max(1, (int)std::lround(g_settings.mediaIconSize * dpiScale));
    g_mediaIconLoadedSize = sizePx;
    LoadMediaIconSlot(g_settings.mediaIconPrevPath, sizePx, g_mediaIconPixels[0], L"Previous");
    LoadMediaIconSlot(g_settings.mediaIconPlayPath, sizePx, g_mediaIconPixels[1], L"Play");
    LoadMediaIconSlot(g_settings.mediaIconPausePath, sizePx, g_mediaIconPixels[2], L"Pause");
    LoadMediaIconSlot(g_settings.mediaIconNextPath, sizePx, g_mediaIconPixels[3], L"Next");
}

// Source-over blend of one premultiplied BGRA pixel onto another. Everything in
// this buffer has to stay premultiplied because it goes straight to
// UpdateLayeredWindow's AC_SRC_ALPHA blend, which assumes exactly that.
inline void BlendPremultipliedOver(BYTE* dst, BYTE sb, BYTE sg, BYTE sr, BYTE sa) {
    if (sa == 255) {
        dst[0] = sb; dst[1] = sg; dst[2] = sr; dst[3] = sa;
        return;
    }
    if (sa == 0) return;
    unsigned inv = 255u - sa;
    dst[0] = (BYTE)(sb + (dst[0] * inv + 127) / 255);
    dst[1] = (BYTE)(sg + (dst[1] * inv + 127) / 255);
    dst[2] = (BYTE)(sr + (dst[2] * inv + 127) / 255);
    dst[3] = (BYTE)(sa + (dst[3] * inv + 127) / 255);
}

bool PointInTriangle(float px, float py, float ax, float ay, float bx, float by, float cx, float cy) {
    float d1 = (px - bx) * (ay - by) - (ax - bx) * (py - by);
    float d2 = (px - cx) * (by - cy) - (bx - cx) * (py - cy);
    float d3 = (px - ax) * (cy - ay) - (cx - ax) * (py - ay);
    bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);
    return !(hasNeg && hasPos);
}

// kind: 0=prev ("<<"), 1=play, 2=pause ("||"), 3=next (">>"). Rasterized
// directly (2x2 supersampled for a soft edge) rather than pulled in through a
// vector library, since it's just four simple shapes and this keeps the mod
// dependency-free for the case where the user hasn't picked their own icons.
void DrawBuiltinGlyph(BYTE* buf, int stride, int originX, int originY, int size, int kind) {
    float margin = size * 0.24f;
    float cy = size * 0.5f;
    float trisize = (size - 2 * margin) * 0.5f;
    BYTE ir = g_settings.mediaIconColorR, ig = g_settings.mediaIconColorG,
         ib = g_settings.mediaIconColorB, ia = g_settings.mediaIconColorA;

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            float cov = 0.f;
            const int SS = 2;
            for (int sy = 0; sy < SS; sy++) {
                for (int sx = 0; sx < SS; sx++) {
                    float px = x + (sx + 0.5f) / SS;
                    float py = y + (sy + 0.5f) / SS;
                    bool inside = false;
                    switch (kind) {
                        case 1:
                            inside = PointInTriangle(px, py, margin, margin, margin, size - margin,
                                                      size - margin, cy);
                            break;
                        case 2: {
                            float barW = size * 0.16f, gap = size * 0.12f;
                            float b1x0 = size * 0.5f - gap * 0.5f - barW, b1x1 = size * 0.5f - gap * 0.5f;
                            float b2x0 = size * 0.5f + gap * 0.5f, b2x1 = size * 0.5f + gap * 0.5f + barW;
                            bool inBand = (py >= margin && py <= size - margin);
                            inside = inBand && ((px >= b1x0 && px <= b1x1) || (px >= b2x0 && px <= b2x1));
                            break;
                        }
                        case 0:
                            inside = PointInTriangle(px, py, size - margin, margin, size - margin,
                                                      size - margin, size - margin - trisize, cy) ||
                                     PointInTriangle(px, py, size - margin - trisize, margin,
                                                      size - margin - trisize, size - margin,
                                                      size - margin - 2 * trisize, cy);
                            break;
                        case 3:
                        default:
                            inside = PointInTriangle(px, py, margin, margin, margin, size - margin,
                                                      margin + trisize, cy) ||
                                     PointInTriangle(px, py, margin + trisize, margin,
                                                      margin + trisize, size - margin,
                                                      margin + 2 * trisize, cy);
                            break;
                    }
                    if (inside) cov += 1.0f / (SS * SS);
                }
            }
            if (cov <= 0.f) continue;
            float a = (ia / 255.0f) * cov;
            BYTE* p = buf + (size_t)(originY + y) * stride + (size_t)(originX + x) * 4;
            BlendPremultipliedOver(p, (BYTE)std::lround(ib * a), (BYTE)std::lround(ig * a),
                                   (BYTE)std::lround(ir * a), (BYTE)std::lround(a * 255.0f));
        }
    }
}

void BlitIcon(BYTE* buf, int stride, int originX, int originY, int size,
              const std::vector<BYTE>& src) {
    if ((int)src.size() < size * size * 4) return;
    for (int y = 0; y < size; y++) {
        const BYTE* s = src.data() + (size_t)y * size * 4;
        BYTE* d = buf + (size_t)(originY + y) * stride + (size_t)originX * 4;
        for (int x = 0; x < size; x++, s += 4, d += 4) {
            // Composited rather than copied: a straight memcpy would stamp the
            // icon's fully transparent pixels over the backing plate, punching
            // an icon-shaped hole through it instead of letting the plate show
            // through where the icon has nothing.
            BlendPremultipliedOver(d, s[0], s[1], s[2], s[3]);
        }
    }
}

// x/y are the strip's screen position. They're passed in rather than left for
// UpdateLayeredWindow to infer, because its "pass NULL and I'll use the current
// values" shortcuts are only documented as valid when the position and size
// aren't changing -- and here they usually are, since the window is born 1x1
// and every settings change can resize it. Handing it both explicitly is what
// makes the strip reliably appear instead of staying an invisible stub.
// Breathing room between the icon row and the edge of the backing plate. This
// grows the strip window itself rather than shrinking the icons, so raising it
// never makes the controls smaller or harder to hit. Applied whether or not the
// plate is actually visible, so that padding, fill and border stay independent
// of one another -- with the default of 0 that costs existing setups nothing.
int GetMediaPlatePaddingPx() {
    return std::max(0, (int)std::lround(g_settings.mediaPlatePadding * GetMediaControlsDpiScale()));
}

void PaintMediaControls(int x, int y, int width, int height) {
    if (!g_mediaWnd || width <= 0 || height <= 0) return;

    HDC screenDC = GetDC(nullptr);
    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = nullptr;
    HDC memDC = CreateCompatibleDC(screenDC);
    HBITMAP dib = CreateDIBSection(screenDC, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, screenDC);
    if (!dib || !bits) {
        if (dib) DeleteObject(dib);
        DeleteDC(memDC);
        return;
    }

    memset(bits, 0, (size_t)width * height * 4);
    BYTE* buf = (BYTE*)bits;
    int stride = width * 4;

    // Optional backing plate behind the whole strip, with an optional outline.
    // v0.5.2 drew a plate unconditionally as a fix for pale icons vanishing
    // against a pale wallpaper, which meant icons that were meant to sit
    // transparently on the desktop always had a dark box behind them. Both
    // pieces are settings now and both default to nothing.
    if (g_settings.mediaPlateA > 0 ||
        (g_settings.mediaPlateBorderSize > 0 && g_settings.mediaPlateBorderA > 0)) {
        float dpiScale = GetMediaControlsDpiScale();
        float radius = std::min({(float)std::max(0, g_settings.mediaPlateCornerRadius) * dpiScale,
                                 width * 0.5f, height * 0.5f});
        // Border draws inward from the edge, so it can never be thicker than
        // half the strip without the two sides meeting in the middle.
        float bw = std::min({(float)std::max(0, g_settings.mediaPlateBorderSize) * dpiScale,
                             width * 0.5f, height * 0.5f});
        bool wantBorder = bw > 0.f && g_settings.mediaPlateBorderA > 0;

        float innerRadius = std::max(0.0f, radius - bw);
        float fillAlpha = g_settings.mediaPlateA / 255.0f;
        float borderAlpha = g_settings.mediaPlateBorderA / 255.0f;

        // Coverage of a rounded rect inset by `inset` on every side: clamp the
        // sample into the rect shrunk by its corner radius, and whatever
        // distance is left over is the distance to the nearest corner circle's
        // centre (zero anywhere along the straight-edged middle).
        auto insideRounded = [&](float px, float py, float inset, float r) {
            float l = inset, t = inset, rt = width - inset, b = height - inset;
            if (px < l || py < t || px > rt || py > b) return false;
            float nx = std::clamp(px, l + r, rt - r);
            float ny = std::clamp(py, t + r, b - r);
            float dx = px - nx, dy = py - ny;
            return dx * dx + dy * dy <= r * r;
        };

        for (int y = 0; y < height; y++) {
            BYTE* row = buf + (size_t)y * stride;
            for (int x = 0; x < width; x++) {
                // 2x2 supersampled, matching how the built-in glyphs are
                // rasterized, so rounded corners don't come out jagged.
                float outerCov = 0.f, innerCov = 0.f;
                const int SS = 2;
                for (int sy = 0; sy < SS; sy++) {
                    for (int sx = 0; sx < SS; sx++) {
                        float px = x + (sx + 0.5f) / SS;
                        float py = y + (sy + 0.5f) / SS;
                        if (insideRounded(px, py, 0.f, radius)) outerCov += 1.0f / (SS * SS);
                        if (wantBorder && insideRounded(px, py, bw, innerRadius))
                            innerCov += 1.0f / (SS * SS);
                    }
                }
                if (outerCov <= 0.f) continue;

                BYTE* p = row + (size_t)x * 4;

                // Fill covers the whole plate including under the border, so a
                // translucent border blends over the fill rather than cutting a
                // hole in it.
                if (g_settings.mediaPlateA > 0) {
                    float a = fillAlpha * outerCov;
                    p[0] = (BYTE)std::lround(g_settings.mediaPlateB * a);
                    p[1] = (BYTE)std::lround(g_settings.mediaPlateG * a);
                    p[2] = (BYTE)std::lround(g_settings.mediaPlateR * a);
                    p[3] = (BYTE)std::lround(a * 255.0f);
                }

                if (wantBorder) {
                    float ringCov = std::max(0.0f, outerCov - innerCov);
                    if (ringCov > 0.f) {
                        float a = borderAlpha * ringCov;
                        BlendPremultipliedOver(
                            p, (BYTE)std::lround(g_settings.mediaPlateBorderB * a),
                            (BYTE)std::lround(g_settings.mediaPlateBorderG * a),
                            (BYTE)std::lround(g_settings.mediaPlateBorderR * a),
                            (BYTE)std::lround(a * 255.0f));
                    }
                }
            }
        }
    }

    // The icons occupy the content box -- the window inset by the plate padding
    // -- not the whole window.
    int pad = GetMediaPlatePaddingPx();
    int contentW = std::max(1, width  - pad * 2);
    int contentH = std::max(1, height - pad * 2);

    // Custom icons are rasterized once at a fixed size, so they can only be
    // blitted at exactly that size; anything else would read the source with the
    // wrong stride and come out scrambled. If a settings change has left them
    // out of step with the box they now have to fit in, fall back to the
    // built-in glyphs for this frame -- the reload that follows will restore
    // them at the right size.
    bool iconsFit = g_mediaIconLoadedSize > 0 && g_mediaIconLoadedSize <= contentH &&
                    g_mediaIconLoadedSize * 3 <= contentW;
    int size = iconsFit ? g_mediaIconLoadedSize : contentH;
    int spacing = std::max(0, (contentW - size * 3) / 2);
    int xPrev = pad;
    int xPlay = pad + size + spacing;
    int xNext = pad + 2 * size + 2 * spacing;
    int iconY = pad + (contentH - size) / 2;

    bool playing = g_mediaIsPlaying.load(std::memory_order_relaxed);

    if (iconsFit && !g_mediaIconPixels[0].empty())
        BlitIcon(buf, stride, xPrev, iconY, size, g_mediaIconPixels[0]);
    else DrawBuiltinGlyph(buf, stride, xPrev, iconY, size, 0);

    const auto& playPauseSrc = playing ? g_mediaIconPixels[2] : g_mediaIconPixels[1];
    if (iconsFit && !playPauseSrc.empty())
        BlitIcon(buf, stride, xPlay, iconY, size, playPauseSrc);
    else DrawBuiltinGlyph(buf, stride, xPlay, iconY, size, playing ? 2 : 1);

    if (iconsFit && !g_mediaIconPixels[3].empty())
        BlitIcon(buf, stride, xNext, iconY, size, g_mediaIconPixels[3]);
    else DrawBuiltinGlyph(buf, stride, xNext, iconY, size, 3);

    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, dib);

    POINT ptSrc = {0, 0};
    POINT ptDst = {x, y};
    SIZE  szWnd = {width, height};
    BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    BOOL ulwOk = UpdateLayeredWindow(g_mediaWnd, nullptr, &ptDst, &szWnd, memDC, &ptSrc, 0,
                                     &blend, ULW_ALPHA);
    if (!ulwOk) {
        Wh_Log(L"[Media] UpdateLayeredWindow failed, error=%lu xywh=(%d,%d,%d,%d)",
               GetLastError(), x, y, width, height);
    }

    SelectObject(memDC, oldBmp);
    DeleteObject(dib);
    DeleteDC(memDC);
}

// Set while the strip is being kept out of the way by Hide When Covered, so a
// repaint triggered by something else (a track change, a playback state flip)
// doesn't pop it back on screen over the window it just got out from under.
bool g_mediaHiddenByCover = false;

// Taskbar auto-hide follow state. Declared ahead of
// RepositionAndRepaintMediaControls, which gates on it, and of the swap-chain
// code that consumes the slide. All writers run on the window (UI) thread,
// which is why the fields stay plain.
bool g_followTargetHidden = false;   // decided state: the strip should be off
bool g_prevWantHidden = false;       // the previous tick's raw model decision
bool g_followInitialized = false;    // the first evaluation snaps, no animation
float g_followSlide = 0.f;           // 0 seated on the bar .. 1 fully slid off
ULONGLONG g_followAnimStart = 0;     // GetTickCount64 when the target flipped
float g_followAnimFrom = 0.f;        // progress the current animation starts from
int g_followSlideDX = 0, g_followSlideDY = 0;  // slide vector, refreshed per tick
bool g_followAutoHideEnabled = false;
bool g_mediaHiddenByBar = false;

void RepositionAndRepaintMediaControls() {
    if (!g_mediaWnd) return;
    if (!g_settings.mediaControlsEnabled) {
        ShowWindow(g_mediaWnd, SW_HIDE);
        return;
    }
    if (g_mediaHiddenByCover && g_settings.mediaHideWhenCovered) return;
    // Never pop the strip over a fullscreen game: a repaint triggered by a
    // track change or playback flip while hidden would otherwise put it back
    // on screen over the game it just got out from under. The shared
    // predicate covers the alt-tabbed-away borderless case too.
    if (IsFullscreenPauseConditionActive()) {
        if (IsWindowVisible(g_mediaWnd)) ShowWindow(g_mediaWnd, SW_HIDE);
        return;
    }
    // Ride the taskbar: while the auto-hide has the bar away the strip stays
    // gone, whatever else repaints it -- the self-heal in the fullscreen
    // watcher included.
    if (g_followTargetHidden) return;

    float dpiScale = GetMediaControlsDpiScale();
    int size = std::max(1, (int)std::lround(g_settings.mediaIconSize * dpiScale));
    int spacing = std::max(0, (int)std::lround(g_settings.mediaIconSpacing * dpiScale));
    int pad = GetMediaPlatePaddingPx();
    int width = size * 3 + spacing * 2 + pad * 2;
    int height = size + pad * 2;

    HMONITOR monitor = TaskbarMonitor();
    if (!monitor) monitor = MonitorFromPoint({0, 0}, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = {sizeof(mi)};
    if (!GetMonitorInfo(monitor, &mi)) return;

    GetWindowRect(MainTaskbar(), &mi.rcWork);
    int workWidth = mi.rcWork.right - mi.rcWork.left;
    int workHeight = mi.rcWork.bottom - mi.rcWork.top;

    float barsWidth = (g_settings.barCount*g_settings.barWidth + (g_settings.barCount-1)*g_settings.barGap)*dpiScale;
    float inset = std::max(4.f*dpiScale, g_settings.barWidth*dpiScale);
    float panelPad = g_settings.backgroundEnabled ? (g_settings.bgPaddingL+g_settings.bgPaddingR)*dpiScale : 0.f;
    float blockX = std::clamp(WidgetAwareOffset(dpiScale), inset,
        std::max(inset, float(workWidth)-barsWidth-width-g_mediaGap*dpiScale-panelPad-inset));
    int x = mi.rcWork.left + (int)std::lround(blockX+barsWidth+g_mediaGap*dpiScale);
    int y = mi.rcWork.top + std::clamp((workHeight-height)/2+(int)std::lround(g_taskbarVerticalOffset*dpiScale),0,std::max(0,workHeight-height));

    Wh_Log(L"[Media] Reposition xywh=(%d,%d,%d,%d) work=(%ld,%ld,%ld,%ld) monitor=%d dpiScale=%.2f",
           x, y, width, height, mi.rcWork.left, mi.rcWork.top, mi.rcWork.right, mi.rcWork.bottom,
           g_settings.monitor, dpiScale);

    // Paint before showing: UpdateLayeredWindow sets the position, size and
    // content in one shot, so by the time the window is shown there's already
    // something in it. A layered window that has never been given content is
    // invisible, which is indistinguishable from "the mod isn't working."
    PaintMediaControls(x, y, width, height);

    BOOL posOk = SetWindowPos(g_mediaWnd, HWND_TOPMOST, x, y, width, height,
                              SWP_NOACTIVATE | SWP_SHOWWINDOW | SWP_NOOWNERZORDER);

    RECT actualRect{};
    GetWindowRect(g_mediaWnd, &actualRect);
    Wh_Log(L"[Media] SetWindowPos ok=%d actualRect=(%ld,%ld,%ld,%ld) visible=%d topmost=%d",
           (int)posOk, actualRect.left, actualRect.top, actualRect.right, actualRect.bottom,
           (int)IsWindowVisible(g_mediaWnd),
           (int)((GetWindowLongPtr(g_mediaWnd, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0));
}

// ---------------------------------------------------------------------------
// Taskbar auto-hide follow.
//
// The strip is a topmost window parked over the taskbar, so whenever the
// taskbar leaves the screen the strip must leave with it, and come back with
// it -- like any other taskbar widget. On Windows 11 the bar's hide is a
// composition transform on its XAML content: the window keeps its rect, stays
// "visible", reports no cloak, and the appbar API answers 0 even while the
// bar is away (all measured on 25H2, build 26200). No API exposes the moment.
//
// What the shell does publish is whether the bar currently holds screen
// space: the monitor's work area. A bar that behaves as a permanent resident
// pushes the work area in by its own thickness; a bar in auto-hide holds no
// space. Measured on this machine 2026-10-08: with the "Automatically hide
// the taskbar" switch on, the work area stayed pushed in by the full bar
// height while the bar sat parked and visible on screen for minutes at a
// time, cursor far away and an ordinary window in the foreground -- the
// StuckRects3 switch and SHAppBarMessage both claimed "auto-hide" the whole
// time. Keying the reveal model to that switch hid the strip under a bar
// that was plainly on screen. So the mode is now keyed to the reservation:
//
// - Resident bar (work area reserved): the strip never hides by model; it
//   rides only the fullscreen and occlusion rules.
// - Auto-hide bar (work area free): the reveal decision is rebuilt from the
//   same inputs the shell reacts to -- the cursor at the bar or at its
//   screen edge, and shell-owned foreground surfaces.
//
// Everything in this block runs on the window (UI) thread;
// RenderVisualizer and UpdateSwapChainForLayout consume the state on the
// same thread.
bool IsTaskbarReservingScreenSpace() {
    HWND tray = MainTaskbar();
    if (!tray) return false;

    MONITORINFO mi{.cbSize = sizeof(mi)};
    if (!GetMonitorInfo(MonitorFromWindow(tray, MONITOR_DEFAULTTONEAREST), &mi))
        return false;
    RECT bar{};
    if (!GetWindowRect(tray, &bar)) return false;

    int barH = bar.bottom - bar.top, barW = bar.right - bar.left;
    if (barH <= 0 || barW <= 0) return false;

    // The edge the bar is parked on is the one it shares with the monitor
    // bounds. Reservation means the work area is pushed in from that edge by
    // at least half the bar's thickness.
    if (bar.top <= mi.rcMonitor.top)
        return mi.rcWork.top - mi.rcMonitor.top >= (barH + 1) / 2;
    if (bar.bottom >= mi.rcMonitor.bottom)
        return mi.rcMonitor.bottom - mi.rcWork.bottom >= (barH + 1) / 2;
    if (bar.left <= mi.rcMonitor.left)
        return mi.rcWork.left - mi.rcMonitor.left >= (barW + 1) / 2;
    if (bar.right >= mi.rcMonitor.right)
        return mi.rcMonitor.right - mi.rcWork.right >= (barW + 1) / 2;
    return false;
}

// The shell reveals a hidden auto-hide bar when the cursor touches the bar's
// screen edge, and holds a revealed bar open while the cursor stays inside it.
// The bar also stays open when any taskbar-owned or explorer-hosted surface
// (Start, search, quick settings, task view) is in the foreground, which is
// how reveal-by-keyboard works. Comparing against those conditions reproduces
// the bar's state closely enough to ride it: the cursor decides the common
// cases, the foreground check covers keyboard reveals.
bool IsTaskbarCurrentlyRevealed() {
    HWND tray = MainTaskbar();
    if (!tray || !IsWindowVisible(tray)) return false;

    RECT bar{};
    if (!GetWindowRect(tray, &bar)) return false;

    MONITORINFO mi{.cbSize = sizeof(mi)};
    HMONITOR monitor = MonitorFromWindow(tray, MONITOR_DEFAULTTONEAREST);
    bool haveMonitor = GetMonitorInfo(monitor, &mi) != 0;

    // The zone depends on the state the last tick decided: from the hidden
    // state only the screen edge reveals the bar, while a revealed bar stays
    // open for the whole cursor-hold zone -- the bar itself plus a 2 px grace
    // so a cursor grazing past the edge does not snap the strip shut.
    POINT pt{};
    bool haveCursor = GetCursorPos(&pt) != FALSE;
    if (haveCursor) {
        if (g_followTargetHidden) {
            if (haveMonitor) {
                RECT edge = bar;
                if (bar.top == mi.rcMonitor.top)
                    edge = {bar.left, mi.rcMonitor.top, bar.right, bar.top + 3};
                else if (bar.bottom == mi.rcMonitor.bottom)
                    edge = {bar.left, bar.bottom - 3, bar.right, mi.rcMonitor.bottom};
                else if (bar.left == mi.rcMonitor.left)
                    edge = {mi.rcMonitor.left, bar.top, bar.left + 3, bar.bottom};
                else if (bar.right == mi.rcMonitor.right)
                    edge = {bar.right - 3, bar.top, mi.rcMonitor.right, bar.bottom};
                if (PtInRect(&edge, pt)) return true;
            }
        } else {
            RECT band = bar;
            if (haveMonitor) {
                if (bar.top == mi.rcMonitor.top)         band.top = mi.rcMonitor.top - 2;
                if (bar.bottom == mi.rcMonitor.bottom)   band.bottom = mi.rcMonitor.bottom + 2;
                if (bar.left == mi.rcMonitor.left)       band.left = mi.rcMonitor.left - 2;
                if (bar.right == mi.rcMonitor.right)     band.right = mi.rcMonitor.right + 2;
            }
            if (PtInRect(&band, pt)) return true;
        }
    }

    HWND fg = GetForegroundWindow();
    if (!fg) return false;
    if (fg == tray) return true;
    if (GetAncestor(fg, GA_ROOTOWNER) == tray) return true;

    WCHAR cls[64] = {};
    if (!GetClassNameW(fg, cls, ARRAYSIZE(cls))) return false;
    if (_wcsicmp(cls, L"Shell_TrayWnd") == 0 ||
        _wcsicmp(cls, L"Shell_SecondaryTrayWnd") == 0 ||
        _wcsicmp(cls, L"XamlExplorerHostIslandWindow") == 0 ||
        _wcsicmp(cls, L"MultitaskingViewFrame") == 0) return true;
    // Start, search and the shell flyouts are CoreWindows hosted outside
    // explorer (StartMenuExperienceHost, SearchHost, ShellExperienceHost);
    // a UWP app's CoreWindow lives in its own process, which is why the
    // image name settles it.
    if (_wcsicmp(cls, L"Windows.UI.Core.CoreWindow") == 0) {
        WCHAR path[MAX_PATH] = {};
        DWORD pid = 0;
        GetWindowThreadProcessId(fg, &pid);
        if (!pid) return false;
        HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
        DWORD size = ARRAYSIZE(path);
        if (process) {
            BOOL ok = QueryFullProcessImageNameW(process, 0, path, &size);
            CloseHandle(process);
            if (ok) {
                PCWSTR name = wcsrchr(path, L'\\');
                name = name ? name + 1 : path;
                return _wcsicmp(name, L"StartMenuExperienceHost.exe") == 0 ||
                       _wcsicmp(name, L"SearchHost.exe") == 0 ||
                       _wcsicmp(name, L"ShellExperienceHost.exe") == 0;
            }
        }
        return false;
    }
    return false;
}

// One decision per 100 ms tick, on the UI thread. Writes the follow state the
// renderer consumes and moves the companion windows with it.
void UpdateTaskbarFollow() {
    if (g_unloading.load()) return;

    // Read the shell's live mode every tick: GetMonitorInfo and GetWindowRect
    // cost far less than the registry open the StuckRects3 read needed, and
    // this is the value the whole decision hangs on.
    bool autohideMode = !IsTaskbarReservingScreenSpace();
    if (autohideMode != g_followAutoHideEnabled) {
        Wh_Log(L"[Follow] taskbar auto-hide mode %s",
               autohideMode ? L"active" : L"not in effect, bar holds its space");
        g_followAutoHideEnabled = autohideMode;
    }

    if (g_fullscreenPaused.load()) {
        // While the fullscreen pause owns the overlay it is simply gone; the
        // state is re-decided on the tick after resume.
        return;
    }

    bool wantHidden = false;
    // A child strip rides the bar's own auto-hide slide: the shell moves the bar
    // and the strip with it. The reveal model only drives a popup strip.
    bool stripIsChild = g_overlayWnd && (GetWindowLongPtr(g_overlayWnd, GWL_STYLE) & WS_CHILD);
    if (g_overlayWnd && !stripIsChild && g_settings.followTaskbarAutoHide && g_followAutoHideEnabled)
        wantHidden = !IsTaskbarCurrentlyRevealed();
    // Hide only on an agreeing second tick: a single misread (a foreground
    // event landing a frame before the shell acts on it) must not park the
    // strip away from a bar that is actually on screen. Reveals stay
    // immediate -- the visible-bias default this mod already leans on.
    bool commitHidden = !g_followInitialized ? wantHidden : (wantHidden && g_prevWantHidden);
    g_prevWantHidden = wantHidden;

    // Refresh the slide vector against the live bar geometry every tick, so a
    // taskbar moved between edges while the strip is out slides the right way
    // the moment the next decision lands.
    g_followSlideDX = 0;
    g_followSlideDY = 0;
    HWND tray = MainTaskbar();
    RECT bar{};
    if (tray && GetWindowRect(tray, &bar)) {
        MONITORINFO mi{.cbSize = sizeof(mi)};
        if (GetMonitorInfo(MonitorFromWindow(tray, MONITOR_DEFAULTTONEAREST), &mi)) {
            const RECT& mon = mi.rcMonitor;
            if (bar.top == mon.top)            g_followSlideDY = -(bar.bottom - bar.top);
            else if (bar.bottom == mon.bottom) g_followSlideDY = bar.bottom - bar.top;
            else if (bar.left == mon.left)     g_followSlideDX = -(bar.right - bar.left);
            else if (bar.right == mon.right)   g_followSlideDX = bar.right - bar.left;
        }
    }

    bool overlayVisible = g_overlayWnd && IsWindowVisible(g_overlayWnd);
    if (commitHidden != g_followTargetHidden || !g_followInitialized) {
        bool firstDecision = !g_followInitialized;
        // Snap instead of animate when nothing could have been on screen: at
        // startup into a hidden bar, or coming back from the fullscreen pause
        // while the bar is still away.
        bool snap = firstDecision || !overlayVisible;
        g_followAnimFrom = g_followSlide;
        if (snap) {
            g_followSlide = commitHidden ? 1.f : 0.f;
            g_followAnimStart = GetTickCount64() - 10000;
        } else {
            g_followAnimStart = GetTickCount64();
        }
        g_followTargetHidden = commitHidden;
        g_followInitialized = true;
        if (!firstDecision)
            Wh_Log(L"[Follow] taskbar auto-hide: strip %s",
                   commitHidden ? L"slides away with the bar" : L"returns with the bar");

        if (commitHidden) {
            if (g_mediaWnd && IsWindowVisible(g_mediaWnd)) {
                g_mediaHiddenByBar = true;
                ShowWindow(g_mediaWnd, SW_HIDE);
            }
            if (g_capturePickerWnd) ShowWindow(g_capturePickerWnd, SW_HIDE);
        } else if (g_mediaHiddenByBar) {
            g_mediaHiddenByBar = false;
            RepositionAndRepaintMediaControls();
        }
    }
}

// ---------------------------------------------------------------------------


LRESULT CALLBACK MediaWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_NCHITTEST: {
            // Click-through everywhere except the three buttons. The strip
            // floats over the taskbar, and a layered window claims clicks for
            // its whole rect, including the transparent plate and the gaps
            // between buttons. Without this, enabling media buttons makes the
            // taskbar underneath unclickable. Only the button squares keep
            // clicks; everything else falls through to the taskbar.
            RECT wr{};
            if (!GetWindowRect(hWnd, &wr)) break;
            int width = wr.right - wr.left, height = wr.bottom - wr.top;
            if (width <= 0 || height <= 0) return HTTRANSPARENT;
            POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
            if (!ScreenToClient(hWnd, &pt)) break;
            int pad = GetMediaPlatePaddingPx();
            int contentW = std::max(1, width - pad * 2);
            int contentH = std::max(1, height - pad * 2);
            bool iconsFit = g_mediaIconLoadedSize > 0 && g_mediaIconLoadedSize <= contentH &&
                            g_mediaIconLoadedSize * 3 <= contentW;
            int size = iconsFit ? g_mediaIconLoadedSize : contentH;
            int spacing = std::max(0, (contentW - size * 3) / 2);
            int xPrev = pad, xPlay = pad + size + spacing, xNext = pad + 2 * size + 2 * spacing;
            int iconY = pad + (contentH - size) / 2;
            bool onButton =
                (pt.x >= xPrev && pt.x < xPrev + size && pt.y >= iconY && pt.y < iconY + size) ||
                (pt.x >= xPlay && pt.x < xPlay + size && pt.y >= iconY && pt.y < iconY + size) ||
                (pt.x >= xNext && pt.x < xNext + size && pt.y >= iconY && pt.y < iconY + size);
            return onButton ? HTCLIENT : HTTRANSPARENT;
        }

        case WM_LBUTTONUP: {
            int x = GET_X_LPARAM(lParam);
            float dpiScale = GetMediaControlsDpiScale();
            int size = std::max(1, (int)std::lround(g_settings.mediaIconSize * dpiScale));
            int spacing = std::max(0, (int)std::lround(g_settings.mediaIconSpacing * dpiScale));
            // The icons are inset by the plate padding (see PaintMediaControls),
            // so the hit test has to start from there as well. Testing from 0
            // instead puts every button's clickable area `pad` pixels left of
            // where the button is actually drawn -- and once padding exceeds the
            // gap between icons, that lands on the wrong button entirely.
            int pad = GetMediaPlatePaddingPx();

            int cmd = -1;
            if (x >= pad && x < pad + size) cmd = 0;
            else if (x >= pad + size + spacing && x < pad + 2 * size + spacing) cmd = 1;
            else if (x >= pad + 2 * size + 2 * spacing &&
                     x < pad + 3 * size + 2 * spacing) cmd = 2;

            if (cmd >= 0) SendMediaCommand(cmd);
            return 0;
        }

        case WM_APP_MEDIA_REPAINT:
            RepositionAndRepaintMediaControls();
            return 0;

        case WM_DESTROY:
            g_mediaWnd = nullptr;
            return 0;

        case WM_APP_CLEANUP:
            DestroyWindow(hWnd);
            return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool g_mediaClassRegistered = false;

bool RegisterMediaWindowClass() {
    if (g_mediaClassRegistered) return true;
    WNDCLASS wc = {};
    wc.lpfnWndProc = MediaWndProc;
    wc.hInstance = GetCurrentModuleHandle();
    wc.lpszClassName = MEDIA_WINDOW_CLASS;
    wc.hCursor = LoadCursor(nullptr, IDC_HAND);
    if (!RegisterClass(&wc)) return false;
    g_mediaClassRegistered = true;
    return true;
}

void UnregisterMediaWindowClass() {
    if (g_mediaClassRegistered) {
        UnregisterClass(MEDIA_WINDOW_CLASS, GetCurrentModuleHandle());
        g_mediaClassRegistered = false;
    }
}

void CreateMediaControlWindow() {
    if (g_mediaWnd) return;
    if (!RegisterMediaWindowClass()) {
        Wh_Log(L"[Media] RegisterMediaWindowClass failed, error %u", GetLastError());
        return;
    }

    HINSTANCE hInstance = GetCurrentModuleHandle();
    g_mediaWnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_TOPMOST,
        MEDIA_WINDOW_CLASS, nullptr, WS_POPUP, 0, 0, 1, 1, MainTaskbar(), nullptr, hInstance, nullptr);
    if (!g_mediaWnd) {
        Wh_Log(L"[Media] CreateWindowEx failed, error %u", GetLastError());
        return;
    }
    Wh_Log(L"[Media] Window created hwnd=%p enabled=%d iconSize=%d spacing=%d pos=(%.2f,%.2f) monitor=%d",
           (void*)g_mediaWnd, (int)g_settings.mediaControlsEnabled, g_settings.mediaIconSize,
           g_settings.mediaIconSpacing, g_settings.mediaHorizontalPosition,
           g_settings.mediaVerticalPosition, g_settings.monitor);

    RecreateMediaControlResources();
    RepositionAndRepaintMediaControls();
}

void BuildHannWindow(int n) {
    for (int i = 0; i < n; i++)
        g_hannWindow[i] = 0.5f * (1.f - cosf(2.f * VIZ_PI * i / (n - 1)));
}

void BuildTwiddleFactors(int n) {
    for (int i = 0; i < n / 2; i++) {
        float ang = -2.0f * VIZ_PI * i / n;
        g_twiddleRe[i] = cosf(ang);
        g_twiddleIm[i] = sinf(ang);
    }
}

void BuildLogBins(UINT32 sampleRate, int fftSize) {
    for (int b = 0; b <= VIZ_NUM_BANDS; b++) {
        int bin = (int)(VIZ_FREQ_EDGES[b] * fftSize / (float)sampleRate);
        g_logBinStart[b] = std::max(1, std::min(fftSize / 2 - 1, bin));
    }
}

// Converts a target frequency (Hz) into an equivalent fractional band index
// (0..VIZ_NUM_BANDS-1) by inverse-interpolating against the shared band-edge
// table. This lets a warped frequency curve (log/linear/mel) still be sampled
// through the existing 7-band energy data without touching the analysis side.
float HzToBandPos(float hz) {
    for (int b = 0; b < VIZ_NUM_BANDS; b++) {
        if (hz <= VIZ_FREQ_EDGES[b + 1]) {
            float lo = VIZ_FREQ_EDGES[b], hi = VIZ_FREQ_EDGES[b + 1];
            float frac = (hi > lo) ? (hz - lo) / (hi - lo) : 0.f;
            return (float)b + std::max(0.f, std::min(1.f, frac));
        }
    }
    return (float)(VIZ_NUM_BANDS - 1);
}

void VizFFT(std::vector<float>& re, std::vector<float>& im) {
    int n = (int)re.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) {
            std::swap(re[i], re[j]);
            std::swap(im[i], im[j]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        int halfLen = len / 2;
        int stride = n / len;
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < halfLen; j++) {
                float wRe = g_twiddleRe[j * stride];
                float wIm = g_twiddleIm[j * stride];
                float uRe = re[i + j], uIm = im[i + j];
                float vRe = re[i + j + halfLen] * wRe - im[i + j + halfLen] * wIm;
                float vIm = re[i + j + halfLen] * wIm + im[i + j + halfLen] * wRe;
                re[i + j] = uRe + vRe;
                im[i + j] = uIm + vIm;
                re[i + j + halfLen] = uRe - vRe;
                im[i + j + halfLen] = uIm - vIm;
            }
        }
    }
}

struct VizEQMul { float low, mid, high; };
VizEQMul GetVizEQMultipliers(VizEQ eq) {
    switch (eq) {
    case VizEQ::Bass: return {2.0f, 0.6f, 0.4f};
    case VizEQ::Rock: return {1.3f, 1.5f, 1.2f};
    case VizEQ::Pop: return {0.8f, 1.2f, 1.8f};
    case VizEQ::Jazz: return {1.1f, 0.8f, 0.6f};
    case VizEQ::Electronic: return {1.7f, 0.6f, 1.7f};
    default: return {1.0f, 1.0f, 1.0f};
    }
}

class VizEndpointNotificationClient : public IMMNotificationClient {
   public:
    virtual ~VizEndpointNotificationClient() = default;

    ULONG STDMETHODCALLTYPE AddRef() override { return InterlockedIncrement(&m_ref); }
    ULONG STDMETHODCALLTYPE Release() override {
        ULONG ref = InterlockedDecrement(&m_ref);
        if (ref == 0) delete this;
        return ref;
    }
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv) override {
        if (riid == __uuidof(IUnknown) || riid == __uuidof(IMMNotificationClient)) {
            *ppv = static_cast<IMMNotificationClient*>(this);
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }
    HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow flow, ERole, LPCWSTR) override {
        if (flow == eRender) g_deviceChanged.store(true, std::memory_order_relaxed);
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR) override {
        g_deviceChanged.store(true, std::memory_order_relaxed);
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR) override {
        g_deviceChanged.store(true, std::memory_order_relaxed);
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR, DWORD) override {
        g_deviceChanged.store(true, std::memory_order_relaxed);
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR, const PROPERTYKEY) override {
        return S_OK;
    }

   private:
    LONG m_ref = 1;
};

bool VizInitAudioClient(IMMDeviceEnumerator* pEnum, ComPtr<IAudioClient>& pClient,
                        ComPtr<IAudioCaptureClient>& pCapture, UINT32& sampleRate,
                        UINT32& channels, bool& isFloat, HANDLE hEvent) {
    pClient.Reset();
    pCapture.Reset();

    ComPtr<IMMDevice> pDev;
    if (FAILED(pEnum->GetDefaultAudioEndpoint(eRender, eConsole, &pDev))) return false;

    ComPtr<IAudioClient> pC;
    if (FAILED(pDev->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr,
                              (void**)pC.GetAddressOf())))
        return false;

    WAVEFORMATEX* pwfx = nullptr;
    pC->GetMixFormat(&pwfx);
    if (!pwfx) return false;

    sampleRate = pwfx->nSamplesPerSec;
    channels = pwfx->nChannels;
    isFloat = (pwfx->wFormatTag == WAVE_FORMAT_IEEE_FLOAT) ||
              (pwfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE &&
               reinterpret_cast<WAVEFORMATEXTENSIBLE*>(pwfx)->SubFormat ==
                   KSDATAFORMAT_SUBTYPE_IEEE_FLOAT);

    HRESULT hr = pC->Initialize(
        AUDCLNT_SHAREMODE_SHARED,
        AUDCLNT_STREAMFLAGS_LOOPBACK | AUDCLNT_STREAMFLAGS_EVENTCALLBACK,
        200000, 0, pwfx, nullptr);
    CoTaskMemFree(pwfx);
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    if (hEvent) pC->SetEventHandle(hEvent);

    ComPtr<IAudioCaptureClient> pCap;
    if (FAILED(pC->GetService(__uuidof(IAudioCaptureClient), (void**)pCap.GetAddressOf())))
        return false;

    if (FAILED(pC->Start())) return false;

    pClient = pC;
    pCapture = pCap;
    return true;
}

// Analyze each active render endpoint separately. Combining band maxima avoids
// doubling a signal that Matrix routes through several endpoints.
// Analyze each active render endpoint separately. Combining band maxima avoids
// doubling a signal that Matrix routes through several endpoints.
void VizCaptureThreadProc() {
    HRESULT com = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(com)) { g_captureRunning.store(false); return; }
    BuildVizSeeds();
    ComPtr<IMMDeviceEnumerator> enumerator;
    if (FAILED(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
        IID_PPV_ARGS(&enumerator)))) { CoUninitialize(); return; }
    auto* notify = new VizEndpointNotificationClient();
    bool registered = SUCCEEDED(enumerator->RegisterEndpointNotificationCallback(notify));
    auto options = ReadAudioOptions();
    struct Endpoint {
        ComPtr<IAudioClient> client;
        ComPtr<IAudioCaptureClient> capture;
        UINT32 rate = 48000, channels = 2;
        WORD bits = 32, align = 8;
        bool floating = true;
        std::vector<float> ring;
        int head = 0, count = 0;
        float peak = 0;
        unsigned long long frames = 0;
    };
    constexpr int cap = VIZ_FFT_SIZE_MAX * 4;
    std::vector<Endpoint> endpoints;
    auto rebuild = [&] {
        for (auto& e : endpoints) e.client->Stop();
        endpoints.clear();
        options = ReadAudioOptions();
        for (EDataFlow flow : {eRender, eCapture}) {
        if (flow == eCapture && options.endpointId.empty() && !options.hardwareLoopbacks) continue;
        ComPtr<IMMDeviceCollection> devices;
        if (FAILED(enumerator->EnumAudioEndpoints(flow, DEVICE_STATE_ACTIVE, &devices))) continue;
        ComPtr<IMMDevice> defaultDevice;
        LPWSTR defaultId = nullptr;
        if (flow == eRender && options.defaultOnly && SUCCEEDED(enumerator->GetDefaultAudioEndpoint(eRender,eMultimedia,&defaultDevice))) defaultDevice->GetId(&defaultId);
        UINT count = 0; devices->GetCount(&count);
        for (UINT i = 0; i < count; ++i) {
            ComPtr<IMMDevice> device;
            if (FAILED(devices->Item(i, &device))) continue;
            ComPtr<IPropertyStore> properties;
            PROPVARIANT description{};
            PROPERTYKEY descKey{{0xa45c254e,0xdf1c,0x4efd,{0x80,0x20,0x67,0xd1,0x46,0xa8,0x50,0xe0}},2};
            std::wstring name;
            if (SUCCEEDED(device->OpenPropertyStore(STGM_READ, &properties)) &&
                SUCCEEDED(properties->GetValue(descKey, &description))) {
                if (description.vt == VT_LPWSTR && description.pwszVal) name = description.pwszVal;
                PropVariantClear(&description);
            }
            // Hardware loopback inputs include the interface's ASIO output.
            // Never open microphone or general recording inputs.
            if (!options.endpointId.empty()) {
                LPWSTR id = nullptr;
                device->GetId(&id);
                bool matches = id && options.endpointId == id;
                CoTaskMemFree(id);
                if (!matches) continue;
            }
            if (options.endpointId.empty() && flow == eCapture && name.find(L"Loopback") == std::wstring::npos) continue;
            if (options.endpointId.empty() && !options.filter.empty() && Lowercase(name).find(options.filter) == std::wstring::npos) continue;
            if (options.endpointId.empty() && flow == eRender && options.defaultOnly) {
                LPWSTR id = nullptr;
                device->GetId(&id);
                bool matches = id && defaultId && wcscmp(id,defaultId)==0;
                CoTaskMemFree(id);
                if (!matches) continue;
            }
            Endpoint e;
            if (FAILED(device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr,
                reinterpret_cast<void**>(e.client.GetAddressOf())))) continue;
            WAVEFORMATEX* format = nullptr;
            if (FAILED(e.client->GetMixFormat(&format)) || !format) continue;
            e.rate = format->nSamplesPerSec; e.channels = format->nChannels;
            e.bits = format->wBitsPerSample; e.align = format->nBlockAlign;
            e.floating = format->wFormatTag == WAVE_FORMAT_IEEE_FLOAT ||
                (format->wFormatTag == WAVE_FORMAT_EXTENSIBLE &&
                 reinterpret_cast<WAVEFORMATEXTENSIBLE*>(format)->SubFormat == KSDATAFORMAT_SUBTYPE_IEEE_FLOAT);
            bool supported = e.channels && ((e.floating && e.bits == 32) ||
                (!e.floating && (e.bits == 16 || e.bits == 24 || e.bits == 32)));
            HRESULT hr = supported ? e.client->Initialize(AUDCLNT_SHAREMODE_SHARED,
                flow == eRender ? AUDCLNT_STREAMFLAGS_LOOPBACK : 0, 200000, 0, format, nullptr) : E_NOTIMPL;
            CoTaskMemFree(format);
            if (SUCCEEDED(hr)) hr = e.client->GetService(IID_PPV_ARGS(&e.capture));
            if (SUCCEEDED(hr)) hr = e.client->Start();
            Wh_Log(L"Endpoint index=%u name=%s flow=%d rate=%u channels=%u bits=%u float=%d result=0x%08X",
                i, name.c_str(), flow, e.rate, e.channels, e.bits, e.floating, hr);
            if (FAILED(hr)) continue;
            e.ring.assign(cap, 0.f);
            endpoints.push_back(std::move(e));
        }
        CoTaskMemFree(defaultId);
        }
        Wh_Log(L"Loopback endpoints opened=%zu", endpoints.size());
    };
    g_deviceChanged.store(false);
    rebuild();
    int fftSize = 0;
    std::vector<float> re, im;
    float envelope[VIZ_NUM_BANDS]{};
    ULONGLONG lastRetry = GetTickCount64(), lastLog = lastRetry;
    while (g_captureRunning.load()) {
        Sleep(10);
        ULONGLONG now = GetTickCount64();
        if ((g_deviceChanged.load() || endpoints.empty()) && now-lastRetry > 1000) {
            g_deviceChanged.store(false); rebuild(); lastRetry = now;
        }
        auto settings = ReadCaptureSettings();
        int wanted = settings.fftSize;
        if (wanted != 1024 && wanted != 2048 && wanted != 4096 && wanted != 8192) wanted = 1024;
        if (wanted != fftSize) {
            fftSize = wanted; BuildHannWindow(fftSize); BuildTwiddleFactors(fftSize);
            re.resize(fftSize); im.resize(fftSize);
            for (auto& e : endpoints) e.head = e.count = 0;
        }
        float levels[VIZ_NUM_BANDS]{};
        for (auto& e : endpoints) {
            UINT32 packet = 0;
            HRESULT hr = e.capture->GetNextPacketSize(&packet);
            if (FAILED(hr)) { g_deviceChanged.store(true); continue; }
            int packets = 0;
            while (packet && ++packets < 100) {
                BYTE* data = nullptr; UINT32 frames = 0; DWORD flags = 0;
                hr = e.capture->GetBuffer(&data, &frames, &flags, nullptr, nullptr);
                if (FAILED(hr)) { g_deviceChanged.store(true); break; }
                if (flags & AUDCLNT_BUFFERFLAGS_DATA_DISCONTINUITY) e.head = e.count = 0;
                float gain = powf(10.f, settings.inputGainDb / 20.f) / e.channels;
                for (UINT32 f = 0; f < frames; ++f) {
                    float mono = 0.f;
                    if (data && !(flags & AUDCLNT_BUFFERFLAGS_SILENT)) {
                        for (UINT32 c = 0; c < e.channels; ++c) {
                            BYTE* sample = data + f * e.align + c * (e.bits/8);
                            if (e.floating) { float v; memcpy(&v, sample, 4); mono += v; }
                            else if (e.bits == 16) { INT16 v; memcpy(&v, sample, 2); mono += v/32768.f; }
                            else if (e.bits == 32) { INT32 v; memcpy(&v, sample, 4); mono += v/2147483648.f; }
                            else { INT32 v = (sample[0] | sample[1]<<8 | sample[2]<<16); if(v & 0x800000) v |= ~0xffffff; mono += v/8388608.f; }
                        }
                    }
                    mono *= gain;
                    e.peak = std::max(e.peak, fabsf(mono));
                    e.ring[e.head] = mono; e.head = (e.head+1)%cap;
                    e.count = std::min(cap, e.count+1);
                }
                e.frames += frames;
                e.capture->ReleaseBuffer(frames);
                // Process before draining the next packet to retain complete FFT windows.
                BuildLogBins(e.rate, fftSize);
                while (e.count >= fftSize) {
                    int start = (e.head-e.count+cap)%cap;
                    for (int k=0; k<fftSize; ++k) { re[k]=e.ring[(start+k)%cap]*g_hannWindow[k]; im[k]=0.f; }
                    e.count -= fftSize/2; VizFFT(re, im);
                    float sens = settings.sensitivity/100.f;
                    float gain = sens<=1.f ? 0.25f+sens*sens*2.75f : 3.f+(sens-1.f)*4.f;
                    auto eq = GetVizEQMultipliers(settings.eq);
                    constexpr float sensitivity[VIZ_NUM_BANDS] = {0.30f,0.22f,0.12f,0.06f,0.030f,0.018f,0.010f};
                    for (int b=0; b<VIZ_NUM_BANDS; ++b) {
                        int lo=g_logBinStart[b], hi=std::max(lo+1,g_logBinStart[b+1]);
                        float power=0.f;
                        for(int k=lo; k<hi; ++k) power += re[k]*re[k]+im[k]*im[k];
                        float eqGain=VIZ_BAND_EQ_ZONE[b]==0 ? eq.low : VIZ_BAND_EQ_ZONE[b]==1 ? eq.mid : eq.high;
                        float value=sqrtf(power/(hi-lo))/(fftSize*0.5f)/sensitivity[b]*gain*eqGain;
                        float mag;
                        switch(settings.sensitivityCurve) {
                            case VizSensitivityCurve::Exponential: mag=1.f-expf(-value); break;
                            case VizSensitivityCurve::Power: mag=powf(std::max(0.f,value),0.6f); break;
                            default: mag=value<=0.7f ? value : 0.7f+0.3f*tanhf((value-0.7f)/0.3f); break;
                        }
                        levels[b]=std::max(levels[b],std::clamp(mag,0.f,1.f));
                    }
                }
                hr=e.capture->GetNextPacketSize(&packet);
                if(FAILED(hr)) { g_deviceChanged.store(true); break; }
            }
        }
        float peak=0.f;
        for(int b=0; b<VIZ_NUM_BANDS; ++b) {
            envelope[b]=std::max(levels[b],std::max(0.f,envelope[b]-0.018f));
            peak=std::max(peak,levels[b]);
        }
        PublishBands(envelope);
        if(peak>0.03f) g_lastAudibleTickMs.store(now);
        if(now-lastLog>=5000) {
            for(size_t i=0; i<endpoints.size(); ++i) {
                auto& e=endpoints[i];
                Wh_Log(L"Audio index=%zu frames=%llu peak=%.5f",i,e.frames,e.peak);
                e.frames=0; e.peak=0.f;
            }
            Wh_Log(L"Published spectrum peak=%.5f",peak); lastLog=now;
        }
    }
    for(auto& e:endpoints) e.client->Stop();
    if(registered) enumerator->UnregisterEndpointNotificationCallback(notify);
    notify->Release(); endpoints.clear(); enumerator.Reset(); CoUninitialize();
}

void StartVizCaptureThread() {
    if (g_captureRunning.load()) return;
    if (g_captureThread) {
        if (g_captureThread->joinable()) g_captureThread->join();
        delete g_captureThread;
        g_captureThread = nullptr;
    }
    if (!g_captureEvent) g_captureEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    g_captureRunning.store(true);
    g_captureThread = new std::thread(VizCaptureThreadProc);
    HANDLE hCaptureThread = g_captureThread->native_handle();
    SetThreadDescription(hCaptureThread, L"TaskbarAudioVisualizer-Capture");
}

void StopVizCaptureThread() {
    g_captureRunning.store(false);
    if (g_captureEvent) SetEvent(g_captureEvent);
    if (g_captureThread) {
        if (g_captureThread->joinable()) g_captureThread->join();
        delete g_captureThread;
        g_captureThread = nullptr;
    }
    if (g_captureEvent) {
        CloseHandle(g_captureEvent);
        g_captureEvent = nullptr;
    }
    float zeroBands[VIZ_NUM_BANDS] = {};
    PublishBands(zeroBands);
}

void UpdateVisualizerTargets() {
    const int vizBars = std::max(1, std::min(g_settings.barCount, VIZ_BARS_MAX));

    float bands[VIZ_NUM_BANDS];
    ReadBands(bands);
    float masterPeak = 0.f;
    for (int i = 0; i < VIZ_NUM_BANDS; i++) {
        masterPeak = std::max(masterPeak, bands[i]);
    }

    auto eq = GetVizEQMultipliers(g_settings.eq);

    auto sampleBands = [&](float t) -> float {
        float pos = t * (VIZ_NUM_BANDS - 1);
        int lo = (int)pos;
        int hi = std::min(lo + 1, VIZ_NUM_BANDS - 1);
        return bands[lo] * (1.f - (pos - (float)lo)) + bands[hi] * (pos - (float)lo);
    };
    auto eqForT = [&](float t) -> float {
        return (t < 0.33f) ? eq.low : (t < 0.66f) ? eq.mid : eq.high;
    };

    auto warpT = [&](float pos) -> float {
        pos = std::max(0.f, std::min(1.f, pos));
        switch (g_settings.freqScale) {
            case VizFreqScale::Linear: {
                float hz = 20.f + pos * (20000.f - 20.f);
                return HzToBandPos(hz) / (float)(VIZ_NUM_BANDS - 1);
            }
            case VizFreqScale::Mel: {
                auto melOf = [](float f) { return 2595.f * log10f(1.f + f / 700.f); };
                float melMin = melOf(20.f), melMax = melOf(20000.f);
                float mel = melMin + pos * (melMax - melMin);
                float hz = 700.f * (powf(10.f, mel / 2595.f) - 1.f);
                return HzToBandPos(hz) / (float)(VIZ_NUM_BANDS - 1);
            }
            default:  // Log -- matches the original band-index-linear mapping
                return pos;
        }
    };

    float t = (float)GetTickCount64() * 0.001f;
    float center = (vizBars - 1) * 0.5f;

    for (int i = 0; i < vizBars; i++) {
        float freqT = (vizBars > 1) ? (float)i / (float)(vizBars - 1) : 0.5f;
        float target = 0.f;

        switch (g_settings.shape) {
            case VizShape::Stereo:
                target = sampleBands(warpT(freqT)) * eqForT(warpT(freqT));
                break;
            case VizShape::Mountain: {
                float dist = fabsf((float)i - center) / std::max(1.f, center);
                float energy = sampleBands(warpT(dist)) * eqForT(warpT(dist));
                float taper = 1.6f - dist * 0.9f;
                target = std::max(0.f, std::min(1.f, (energy + masterPeak * (0.2f - dist * 0.12f)) * taper));
                break;
            }
            case VizShape::Mirror: {
                float mirT = 1.f - fabsf((float)i - center) / std::max(1.f, center);
                float energy = sampleBands(warpT(mirT)) * eqForT(warpT(mirT));
                target = std::max(0.f, std::min(1.f, (energy + masterPeak * (0.1f + mirT * 0.12f)) * 1.3f));
                break;
            }
            case VizShape::Wave: {
                float phase = (float)i * (2.f * VIZ_PI / (float)vizBars);
                float wave = 0.55f + 0.45f * sinf(t * 3.5f - phase);
                float energy = sampleBands(warpT(freqT)) * eqForT(warpT(freqT));
                target = std::max(0.f, std::min(1.f, energy * wave + masterPeak * 0.15f));
                break;
            }
            case VizShape::Breathe: {
                if (i == 0) {
                    float k = (masterPeak > g_vizBreatheEnv) ? 0.04f : 0.015f;
                    g_vizBreatheEnv += (masterPeak - g_vizBreatheEnv) * k;
                }
                float rate = 0.55f + VIZ_SEEDS[i % VIZ_BARS_MAX] * 0.18f;
                float inhale = 0.5f + 0.5f * sinf(t * rate + VIZ_SEEDS[i % VIZ_BARS_MAX] * 1.2f);
                target = std::max(0.f, std::min(1.f, inhale * (0.12f + g_vizBreatheEnv * 0.88f)));
                break;
            }
            case VizShape::Dots:
                target = sampleBands(warpT(freqT)) * eqForT(warpT(freqT));
                break;
            case VizShape::Radial:
                target = sampleBands(warpT(freqT)) * eqForT(warpT(freqT));
                break;
            case VizShape::Oscilloscope:
                target = 0.f;  // drawn directly from the raw waveform buffer, not per-bar targets
                break;
        }

        g_vizTarget[i] = std::max(0.f, std::min(1.f, target));
    }
}

struct RGBA { BYTE a, r, g, b; };

RGBA LerpColor(RGBA a, RGBA b, float t) {
    auto L = [](BYTE x, BYTE y, float tt) -> BYTE {
        return (BYTE)((int)x + (int)((float)((int)y - (int)x) * tt));
    };
    return {L(a.a, b.a, t), L(a.r, b.r, t), L(a.g, b.g, t), L(a.b, b.b, t)};
}

RGBA HSVtoRGB(float h, float s, float v, BYTE alpha) {
    h = fmodf(h, 360.f);
    if (h < 0) h += 360.f;
    float c = v * s;
    float x = c * (1.f - fabsf(fmodf(h / 60.0f, 2.f) - 1.f));
    float m = v - c;
    float r, g, b;
    if (h < 60)       { r = c; g = x; b = 0; }
    else if (h < 120) { r = x; g = c; b = 0; }
    else if (h < 180) { r = 0; g = c; b = x; }
    else if (h < 240) { r = 0; g = x; b = c; }
    else if (h < 300) { r = x; g = 0; b = c; }
    else              { r = c; g = 0; b = x; }
    return {alpha, (BYTE)((r + m) * 255.f), (BYTE)((g + m) * 255.f), (BYTE)((b + m) * 255.f)};
}

bool InitDirectX() {
    HRESULT hr;

    UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, nullptr, 0,
                           D3D11_SDK_VERSION, &g_d3dDevice, nullptr, nullptr);
    if (FAILED(hr)) {
        Wh_Log(L"D3D11CreateDevice failed: 0x%08X", hr);
        return false;
    }

    hr = g_d3dDevice.As(&g_dxgiDevice);
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    {
        ComPtr<IDXGIDevice1> dxgiDevice1;
        if (SUCCEEDED(g_dxgiDevice.As(&dxgiDevice1)) && dxgiDevice1) {
            dxgiDevice1->SetMaximumFrameLatency(1);
        }
    }

    hr = CreateDXGIFactory2(0, IID_PPV_ARGS(&g_dxgiFactory));
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, IID_PPV_ARGS(&g_d2dFactory));
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    hr = g_d2dFactory->CreateDevice(g_dxgiDevice.Get(), &g_d2dDevice);
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    D2D1_STROKE_STYLE_PROPERTIES capProps = D2D1::StrokeStyleProperties(
        D2D1_CAP_STYLE_ROUND, D2D1_CAP_STYLE_ROUND, D2D1_CAP_STYLE_ROUND);
    g_d2dFactory->CreateStrokeStyle(&capProps, nullptr, 0, &g_roundCapStrokeStyle);

    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                        (IUnknown**)g_dwriteFactory.GetAddressOf());

    return true;
}

void UninitDirectX() {
    g_dwriteTextFormat.Reset();
    g_dwriteFactory.Reset();
    g_roundCapStrokeStyle.Reset();
    g_d2dDevice.Reset();
    g_d2dFactory.Reset();
    g_dxgiFactory.Reset();
    g_dxgiDevice.Reset();
    g_d3dDevice.Reset();
    g_dwriteTextFormatFontSize = -1;
    g_dwriteTextFormatFontName.clear();
}

bool RecreateVisualResources();

// Geometry of the visualizer, resolved once and used both to size the swap
// chain and to draw into it.
//
// The swap chain used to span the entire desktop even though the widget
// occupies a thin strip of it, which meant every frame cleared and presented
// millions of untouched pixels and held two full-screen buffers in VRAM. It is
// now sized to the widget's bounding box, with the composition visual offset to
// position it -- so drawing happens in local coordinates starting at the box.
struct VizLayout {
    float originX, originY;         // virtual-screen coords of the box's top-left
    UINT  width, height;            // swap chain size, in pixels
    float blockX, blockY;           // bar-group origin, in LOCAL coords
    float totalWidth, totalHeight;  // bar-group extent
    float textSide;                 // horizontal room reserved for overlay text
    float textAnchorSide;           // where text hangs off the bars; offset-independent
    float textTop;                  // vertical room reserved above the bars
    float textBottom;               // vertical room reserved below the bars
};

// ---- Drag-to-move ----------------------------------------------------------
// Ctrl (or whichever modifier/button is configured) + a click-drag over the
// visualizer repositions it. Windhawk mods can only READ settings, not write
// them back, so a dragged position can't land in the Position % fields the
// settings UI shows -- instead it's kept as a runtime override here (which
// ComputeVizLayout consults ahead of the Position settings) and persisted via
// Wh_SetStringValue so it survives restarts silently. Settings are read-only
// to a mod, but mod-owned values are not, and Windhawk removes them with the
// mod rather than leaving anything behind.
std::atomic<bool> g_dragOverrideActive{false};
std::atomic<float> g_dragOverrideH{50.0f};
std::atomic<float> g_dragOverrideV{50.0f};
// True only while a drag is actively in progress -- tells the render path to
// freeze the bars and show just the background/border box moving.
std::atomic<bool> g_dragRenderPauseActive{false};

// Live keyboard nudges for the two text overlays, in physical pixels. Unlike
// the visualizer's position -- where the override replaces the Position
// percentages outright -- these are a delta *on top of* the Offset settings, so
// a value typed into settings is never silently ignored because a nudge exists.
// A delta of zero means "no nudge", which needs no separate active flag.
std::atomic<int> g_npNudgeX{0}, g_npNudgeY{0};
std::atomic<int> g_pfNudgeX{0}, g_pfNudgeY{0};

float EffectiveNowPlayingOffsetX() {
    return (float)g_settings.nowPlayingOffsetX * g_dpiScale +
           (float)g_npNudgeX.load(std::memory_order_relaxed);
}
float EffectiveNowPlayingOffsetY() {
    return (float)g_settings.nowPlayingOffsetY * g_dpiScale +
           (float)g_npNudgeY.load(std::memory_order_relaxed);
}
float EffectivePeakFreqOffsetX() {
    return (float)g_settings.peakFreqOffsetX * g_dpiScale +
           (float)g_pfNudgeX.load(std::memory_order_relaxed);
}
float EffectivePeakFreqOffsetY() {
    return (float)g_settings.peakFreqOffsetY * g_dpiScale +
           (float)g_pfNudgeY.load(std::memory_order_relaxed);
}

// Runtime placements go through Wh_SetStringValue / Wh_GetStringValue, which
// are per-mod, work on portable Windhawk, and are removed along with the mod.
//
// v1.2.0 also carried a one-shot import of a file the pre-catalog builds kept
// under %LOCALAPPDATA%. Nothing in the catalog ever wrote that file, so it has
// been removed here as agreed during the 1.2.0 review.
void LoadPositionOverride() {
    WCHAR buf[192] = {};
    Wh_GetStringValue(L"positionOverride", buf, ARRAYSIZE(buf));
    if (!buf[0]) return;

    // Two floats is the original format; the four trailing ints carrying the
    // text nudges came later, so a value written by an older build still parses
    // and simply leaves the nudges at zero. A negative percentage is the
    // sentinel for "no position override" -- needed now that the record can
    // exist purely to hold text nudges, and an old one never contains one.
    float hPct = -1.0f, vPct = -1.0f;
    int npX = 0, npY = 0, pfX = 0, pfY = 0;
    float mediaH = -1.0f, mediaV = -1.0f;
    int n = swscanf_s(buf, L"%f %f %d %d %d %d %f %f", &hPct, &vPct, &npX, &npY, &pfX, &pfY,
                      &mediaH, &mediaV);
    if (n >= 2 && hPct >= 0.0f && vPct >= 0.0f) {
        g_dragOverrideH.store(std::clamp(hPct, 0.0f, 100.0f), std::memory_order_relaxed);
        g_dragOverrideV.store(std::clamp(vPct, 0.0f, 100.0f), std::memory_order_relaxed);
        g_dragOverrideActive.store(true, std::memory_order_relaxed);
    }
    if (n >= 6) {
        g_npNudgeX.store(npX, std::memory_order_relaxed);
        g_npNudgeY.store(npY, std::memory_order_relaxed);
        g_pfNudgeX.store(pfX, std::memory_order_relaxed);
        g_pfNudgeY.store(pfY, std::memory_order_relaxed);
    }
    if (n >= 8 && mediaH >= 0.0f && mediaV >= 0.0f) {
        g_mediaOverrideH.store(std::clamp(mediaH, 0.0f, 100.0f), std::memory_order_relaxed);
        g_mediaOverrideV.store(std::clamp(mediaV, 0.0f, 100.0f), std::memory_order_relaxed);
        g_mediaOverrideActive.store(true, std::memory_order_relaxed);
    }
}

// One value holds all three runtime placements, so any change rewrites the
// whole record rather than touching a field -- and when everything is back to
// its default the value is cleared outright, so nothing lingers to be reloaded.
void PersistOverrideState() {
    bool posActive = g_dragOverrideActive.load(std::memory_order_relaxed);
    bool mediaActive = g_mediaOverrideActive.load(std::memory_order_relaxed);
    int npX = g_npNudgeX.load(std::memory_order_relaxed);
    int npY = g_npNudgeY.load(std::memory_order_relaxed);
    int pfX = g_pfNudgeX.load(std::memory_order_relaxed);
    int pfY = g_pfNudgeY.load(std::memory_order_relaxed);

    if (!posActive && !mediaActive && !npX && !npY && !pfX && !pfY) {
        Wh_SetStringValue(L"positionOverride", L"");
        return;
    }

    WCHAR buf[192];
    int len = swprintf_s(buf, L"%.4f %.4f %d %d %d %d %.4f %.4f",
                         posActive ? g_dragOverrideH.load(std::memory_order_relaxed) : -1.0f,
                         posActive ? g_dragOverrideV.load(std::memory_order_relaxed) : -1.0f,
                         npX, npY, pfX, pfY,
                         mediaActive ? g_mediaOverrideH.load(std::memory_order_relaxed) : -1.0f,
                         mediaActive ? g_mediaOverrideV.load(std::memory_order_relaxed) : -1.0f);
    if (len > 0) Wh_SetStringValue(L"positionOverride", buf);
}

void RequestPositionOverrideSave();  // defined with the keyboard-nudge helpers

// Both callers reach this from a low-level input hook: Ctrl+Alt+Home through
// ResetMoveTarget, and the double-click-in-place path in DragMouseHookProc.
// Everything in a WH_KEYBOARD_LL / WH_MOUSE_LL callback blocks all system input
// until it returns, so the write goes through the same deferred save the nudge
// paths already use rather than calling Wh_SetStringValue inline.
void ClearPositionOverride() {
    g_dragOverrideActive.store(false, std::memory_order_relaxed);
    RequestPositionOverrideSave();
}

UINT DragButtonDownMsg() {
    switch (g_settings.dragButton) {
        case VizDragButton::Left:  return WM_LBUTTONDOWN;
        case VizDragButton::Right: return WM_RBUTTONDOWN;
        default:                   return WM_MBUTTONDOWN;
    }
}

UINT DragButtonUpMsg() {
    switch (g_settings.dragButton) {
        case VizDragButton::Left:  return WM_LBUTTONUP;
        case VizDragButton::Right: return WM_RBUTTONUP;
        default:                   return WM_MBUTTONUP;
    }
}

bool DragModifierHeld() {
    switch (g_settings.dragModifier) {
        case VizDragModifier::None:  return true;
        case VizDragModifier::Ctrl:  return (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
        case VizDragModifier::Alt:   return (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;
        case VizDragModifier::Shift: return (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
        case VizDragModifier::Win:   return (GetAsyncKeyState(VK_LWIN) & 0x8000) != 0 ||
                                            (GetAsyncKeyState(VK_RWIN) & 0x8000) != 0;
    }
    return false;
}

// Hit-tests against the bounds of the last drawn frame (already tracked for
// the occlusion check), so "over the visualizer" means the box as it's
// actually being shown right now, including mid-drag.
bool PointInVisualizerBounds(POINT pt) {
    if (!g_drawRectValid.load(std::memory_order_relaxed)) return false;
    LONG l = g_drawRectL.load(std::memory_order_relaxed);
    LONG t = g_drawRectT.load(std::memory_order_relaxed);
    LONG r = g_drawRectR.load(std::memory_order_relaxed);
    LONG b = g_drawRectB.load(std::memory_order_relaxed);
    return pt.x >= l && pt.x < r && pt.y >= t && pt.y < b;
}

bool ComputeVizLayout(VizLayout* out) {
    if (!out) return false;

    int barCount  = std::max(1, std::min(g_settings.barCount, VIZ_BARS_MAX));
    float barW    = (float)std::max(1, g_settings.barWidth) * g_dpiScale;
    float barGap  = (float)std::max(0, g_settings.barGap) * g_dpiScale;
    float maxSize = (float)std::max(2, g_settings.barMaxSize) * g_dpiScale;

    bool horizontal = (g_settings.orientation == VizOrientation::Horizontal);
    float barsThickness = barCount * barW + (barCount - 1) * barGap;

    float totalWidth, totalHeight;
    if (g_settings.shape == VizShape::Radial) {
        totalWidth = totalHeight = maxSize * 2.0f;
    } else {
        totalWidth  = horizontal ? barsThickness : maxSize;
        totalHeight = horizontal ? maxSize       : barsThickness;
    }

    HMONITOR monitor = g_cachedMonitor;
    if (!monitor) monitor = MonitorFromPoint({0, 0}, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{.cbSize = sizeof(mi)};
    if (!GetMonitorInfo(monitor, &mi)) return false;


    RECT taskbar{};
    if (!GetWindowRect(MainTaskbar(), &taskbar)) return false;
    float padX = g_settings.backgroundEnabled ? (g_settings.bgPaddingL + g_settings.bgPaddingR)*g_dpiScale : 0.f;
    float controlsWidth = g_settings.mediaControlsEnabled ? (g_mediaGap + 3*g_settings.mediaIconSize + 2*g_settings.mediaIconSpacing + 2*g_settings.mediaPlatePadding)*g_dpiScale : 0.f;
    float inset = std::max(4.f*g_dpiScale, barW);
    float available = float(taskbar.right-taskbar.left) - totalWidth - controlsWidth - padX - inset;
    float blockX = std::clamp(WidgetAwareOffset(g_dpiScale), inset, std::max(inset, available));
    float blockY = ((taskbar.bottom-taskbar.top) - totalHeight)*0.5f + g_taskbarVerticalOffset*g_dpiScale;
    float yInset = g_settings.backgroundEnabled ? std::max(g_settings.bgPaddingT,g_settings.bgPaddingB)*g_dpiScale : 0.f;
    blockY = std::clamp(blockY, yInset, std::max(yInset, float(taskbar.bottom-taskbar.top)-totalHeight-yInset));

    float padL = g_settings.backgroundEnabled ? (float)g_settings.bgPaddingL * g_dpiScale : 0.f;
    float padR = g_settings.backgroundEnabled ? (float)g_settings.bgPaddingR * g_dpiScale : 0.f;
    float padT = g_settings.backgroundEnabled ? (float)g_settings.bgPaddingT * g_dpiScale : 0.f;
    float padB = g_settings.backgroundEnabled ? (float)g_settings.bgPaddingB * g_dpiScale : 0.f;

    // Safety margin so nothing gets clipped at the edges of the smaller target:
    // stroked shapes (oscilloscope, radial) centre their line on the path and so
    // bleed half a stroke outward, and the radial shape's spokes reach further
    // than its nominal box (inner radius plus full bar length).
    float margin = std::max(14.0f * g_dpiScale, barW);
    if (g_settings.shape == VizShape::Radial) margin += maxSize * 0.15f;

    // Text overlays can sit outside the bars, so the box reserves room for them.
    // Without this they fall outside the render surface and get clipped away.
    float fontPx = (float)std::max(6, g_settings.nowPlayingFontSize) * g_dpiScale;
    float textTop = 0.f, textBottom = 0.f, textSide = 0.f;

    // textAnchorSide is where the draw code hangs the text off the bar group and
    // must not move when an offset changes -- otherwise nudging the Now Playing
    // text sideways would drag the frequency readout along with it, since both
    // anchor off the same number. textSide is the room actually reserved on the
    // render surface, which does have to grow by the offsets or offset text
    // simply walks off the surface and disappears.
    float textAnchorSide = 0.f;
    float extraSide = 0.f;

    // Reserved room is rounded up to a coarse step rather than tracking the
    // offset exactly. The swap chain is sized from this, and a keyboard nudge
    // is one pixel per press with key repeat behind it -- following every pixel
    // would mean a DXGI buffer resize dozens of times a second while someone is
    // simply holding an arrow key down.
    auto reserveFor = [](float offset) { return std::ceil(offset / 32.0f) * 32.0f; };

    // A text panel grows past the text by its padding and border, so that has to
    // be reserved too or the panel gets clipped at the edge of the surface while
    // the text inside it stays visible.
    float npPanel = (float)(g_settings.npBgPadding + g_settings.npBgBorderSize) * g_dpiScale;
    float pfPanel = (float)(g_settings.pfBgPadding + g_settings.pfBgBorderSize) * g_dpiScale;

    if (g_settings.nowPlayingEnabled) {
        float npOffX = reserveFor(std::abs(EffectiveNowPlayingOffsetX()) + npPanel);
        float npOffY = reserveFor(std::abs(EffectiveNowPlayingOffsetY()) + npPanel);
        textTop    = std::max(textTop, fontPx * 1.6f + 8.0f * g_dpiScale + npOffY);
        textBottom = std::max(textBottom, npOffY);
        textAnchorSide = std::max(textAnchorSide, 100.0f * g_dpiScale);
        extraSide  = std::max(extraSide, npOffX);
    }
    if (g_settings.peakFreqEnabled) {
        float pfOffX = reserveFor(std::abs(EffectivePeakFreqOffsetX()) + pfPanel);
        float pfOffY = reserveFor(std::abs(EffectivePeakFreqOffsetY()) + pfPanel);
        float pfH = fontPx * 1.4f + 4.0f * g_dpiScale;
        if (g_settings.peakFreqAlignV == VizTextAlignV::Above)
            textTop = std::max(textTop, pfH + pfOffY);
        else if (g_settings.peakFreqAlignV == VizTextAlignV::Below)
            textBottom = std::max(textBottom, pfH + pfOffY);
        else {
            // Inside placements still need room once an offset can push them
            // past the bars in either direction.
            textTop    = std::max(textTop, pfOffY);
            textBottom = std::max(textBottom, pfOffY);
        }
        textAnchorSide = std::max(textAnchorSide, 60.0f * g_dpiScale);
        extraSide = std::max(extraSide, pfOffX);
    }

    textSide = textAnchorSide + extraSide;

    float insetL = padL + margin + textSide;
    float insetT = padT + margin + textTop;
    float insetR = padR + margin + textSide;
    float insetB = padB + margin + textBottom;

    blockX = std::max(blockX, WidgetAwareOffset(g_dpiScale) + padL + textSide);
    float rawOriginX = blockX - insetL;
    float rawOriginY = blockY - insetT;

    // The composition visual's offset MUST land on whole pixels. A fractional
    // offset makes DirectComposition resample the entire surface bilinearly,
    // which softens every edge and reads as an unwanted blur -- even with the
    // blur effect switched off entirely.
    //
    // The offset is floored to an integer and the leftover fraction is folded
    // back into the local drawing origin, so the widget still lands exactly
    // where the position settings ask for, without resampling the surface.
    out->originX = floorf(rawOriginX);
    out->originY = floorf(rawOriginY);

    float fracX = rawOriginX - out->originX;
    float fracY = rawOriginY - out->originY;

    out->blockX      = insetL + fracX;   // local coords
    out->blockY      = insetT + fracY;
    out->totalWidth  = totalWidth;
    out->totalHeight = totalHeight;
    out->textSide       = textSide;
    out->textAnchorSide = textAnchorSide;
    out->textTop        = textTop;
    out->textBottom     = textBottom;

    // +1 px of slack absorbs the sub-pixel offset folded in above.
    out->width  = (UINT)std::max(1.0f, ceilf(totalWidth  + insetL + insetR) + 1.0f);
    out->height = (UINT)std::max(1.0f, ceilf(totalHeight + insetT + insetB) + 1.0f);
    return true;
}

bool CreateSwapChainResources() {
    HRESULT hr;

    // Monitor and DPI must be resolved before the layout, since bar sizes are
    // DPI-scaled and the box is positioned against the monitor's work area.
    HMONITOR monitor = TaskbarMonitor();
    if (!monitor) monitor = MonitorFromPoint({0, 0}, MONITOR_DEFAULTTONEAREST);
    g_cachedMonitor = monitor;
    g_dpiScale = GetMonitorDpiScale(monitor);

    VizLayout layout;
    if (!ComputeVizLayout(&layout)) return false;

    DXGI_SWAP_CHAIN_DESC1 scd = {};
    scd.Width = layout.width;
    scd.Height = layout.height;
    scd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    scd.SampleDesc.Count = 1;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 2;
    scd.Scaling = DXGI_SCALING_STRETCH;
    scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    scd.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;

    hr = g_dxgiFactory->CreateSwapChainForComposition(g_dxgiDevice.Get(), &scd, nullptr,
                                                      &g_swapChain);
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    hr = g_d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &g_dc);
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    ComPtr<IDXGISurface2> surface;
    hr = g_swapChain->GetBuffer(0, IID_PPV_ARGS(&surface));
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    D2D1_BITMAP_PROPERTIES1 bitmapProperties = {};
    bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
    bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
    bitmapProperties.bitmapOptions =
        D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;

    ComPtr<ID2D1Bitmap1> targetBitmap;
    hr = g_dc->CreateBitmapFromDxgiSurface(surface.Get(), bitmapProperties, &targetBitmap);
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    g_dc->SetTarget(targetBitmap.Get());

    hr = DCompositionCreateDevice(g_dxgiDevice.Get(), IID_PPV_ARGS(&g_compositionDevice));
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    hr = g_compositionDevice->CreateTargetForHwnd(g_overlayWnd, TRUE, &g_compositionTarget);
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    hr = g_compositionDevice->CreateVisual(&g_compositionVisual);
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    hr = g_compositionVisual->SetContent(g_swapChain.Get());
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    // Position the (now much smaller) swap chain where the widget belongs.
    // The overlay window spans the whole virtual desktop starting at its origin,
    // so window-client coordinates match the virtual-screen-relative coordinates
    // the layout produces.
    g_compositionVisual->SetOffsetX(layout.originX);
    g_compositionVisual->SetOffsetY(layout.originY);

    hr = g_compositionTarget->SetRoot(g_compositionVisual.Get());
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    hr = g_compositionDevice->Commit();
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    g_swapChainWidth  = layout.width;
    g_swapChainHeight = layout.height;
    g_visualOffsetX   = layout.originX;
    g_visualOffsetY   = layout.originY;

    return RecreateVisualResources();
}

// Re-sizes and re-positions the swap chain when the widget's bounding box
// changes (settings edits, display changes). Does nothing when the box is
// unchanged, so it is cheap to call defensively.
void UpdateSwapChainForLayout() {
    if (!g_swapChain || !g_dc || !g_compositionVisual) return;

    VizLayout layout;
    if (!ComputeVizLayout(&layout)) return;

    // The auto-hide slide rides the same visual offset: when the taskbar has
    // hidden itself, the strip travels off the screen edge the bar slid
    // across. Applied before the change checks below, so only moving ticks
    // commit.
    if (g_followSlide > 0.0001f && (g_followSlideDX || g_followSlideDY)) {
        layout.originX += g_followSlideDX * g_followSlide;
        layout.originY += g_followSlideDY * g_followSlide;
    }

    bool sizeChanged = (layout.width != g_swapChainWidth || layout.height != g_swapChainHeight);
    bool moved = (fabsf(layout.originX - g_visualOffsetX) > 0.5f ||
                  fabsf(layout.originY - g_visualOffsetY) > 0.5f);
    if (!sizeChanged && !moved) return;

    if (sizeChanged) {
        g_dc->SetTarget(nullptr);
        if (FAILED(g_swapChain->ResizeBuffers(0, layout.width, layout.height,
                                              DXGI_FORMAT_UNKNOWN, 0)))
            return;

        ComPtr<IDXGISurface2> surface;
        if (FAILED(g_swapChain->GetBuffer(0, IID_PPV_ARGS(&surface)))) return;

        D2D1_BITMAP_PROPERTIES1 bp = {};
        bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
        bp.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
        bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;

        ComPtr<ID2D1Bitmap1> targetBitmap;
        if (FAILED(g_dc->CreateBitmapFromDxgiSurface(surface.Get(), bp, &targetBitmap))) return;

        g_dc->SetTarget(targetBitmap.Get());
        g_swapChainWidth  = layout.width;
        g_swapChainHeight = layout.height;
    }

    if (moved) {
        g_compositionVisual->SetOffsetX(layout.originX);
        g_compositionVisual->SetOffsetY(layout.originY);
        g_visualOffsetX = layout.originX;
        g_visualOffsetY = layout.originY;
    }

    if (g_compositionDevice) g_compositionDevice->Commit();

    // The cached blur is baked for one specific box, so a box that has moved or
    // resized leaves it showing the wrong slice of wallpaper. Re-bake via the
    // existing wallpaper-refresh timer rather than inline, since re-capturing
    // involves a present and a DwmFlush.
    if (g_messageWnd && g_settings.backgroundEnabled && g_settings.bgBlur > 0) {
        SetTimer(g_messageWnd, TIMER_ID_MSG_WALLPAPER_REFRESH, 200, nullptr);
    }
}

// Session state for an in-progress drag. Touched only from the low-level mouse
// hook, which only ever runs on the UI thread that installed it -- no locking
// needed here, unlike the atomics above that the render thread also reads.
bool g_dragInProgress = false;
bool g_dragMoved = false;
POINT g_dragStartCursor{};
float g_dragStartH = 50.0f, g_dragStartV = 50.0f;
ULONGLONG g_dragLastClickTick = 0;
POINT g_dragLastClickPos{};

void BeginDrag(POINT pt) {
    g_dragInProgress = true;
    g_dragMoved = false;
    g_dragStartCursor = pt;
    g_dragStartH = g_dragOverrideActive.load(std::memory_order_relaxed)
                       ? g_dragOverrideH.load(std::memory_order_relaxed)
                       : g_settings.horizontalPosition;
    g_dragStartV = g_dragOverrideActive.load(std::memory_order_relaxed)
                       ? g_dragOverrideV.load(std::memory_order_relaxed)
                       : g_settings.verticalPosition;
    g_dragRenderPauseActive.store(true, std::memory_order_relaxed);

    Wh_Log(L"[Drag] BEGIN cursor=(%d,%d) startH=%.2f startV=%.2f",
           pt.x, pt.y, g_dragStartH, g_dragStartV);
}

// The distance, in physical pixels, that the visualizer's box can travel across
// the work area on each axis -- i.e. what 0%..100% of a Position setting spans.
// Mirrors the sizing math in ComputeVizLayout so a pixel delta converts to the
// same percent delta that layout will turn back into pixels.
bool GetVizTravelRange(float* travelX, float* travelY) {
    HMONITOR monitor = g_cachedMonitor;
    if (!monitor) monitor = MonitorFromPoint({0, 0}, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{.cbSize = sizeof(mi)};
    if (!GetMonitorInfo(monitor, &mi)) return false;

    int barCount = std::max(1, std::min(g_settings.barCount, VIZ_BARS_MAX));
    float barW = (float)std::max(1, g_settings.barWidth) * g_dpiScale;
    float barGap = (float)std::max(0, g_settings.barGap) * g_dpiScale;
    float maxSize = (float)std::max(2, g_settings.barMaxSize) * g_dpiScale;
    bool horizontal = (g_settings.orientation == VizOrientation::Horizontal);
    float barsThickness = barCount * barW + (barCount - 1) * barGap;
    float totalWidth, totalHeight;
    if (g_settings.shape == VizShape::Radial) {
        totalWidth = totalHeight = maxSize * 2.0f;
    } else {
        totalWidth  = horizontal ? barsThickness : maxSize;
        totalHeight = horizontal ? maxSize       : barsThickness;
    }

    *travelX = (float)(mi.rcWork.right  - mi.rcWork.left) - totalWidth;
    *travelY = (float)(mi.rcWork.bottom - mi.rcWork.top)  - totalHeight;
    return true;
}

void UpdateDrag(POINT pt) {
    if (!g_dragInProgress) return;

    if (std::abs(pt.x - g_dragStartCursor.x) > 3 || std::abs(pt.y - g_dragStartCursor.y) > 3)
        g_dragMoved = true;

    float travelX = 0.f, travelY = 0.f;
    if (!GetVizTravelRange(&travelX, &travelY)) return;

    float dxPercent = (travelX > 1.0f) ? ((float)(pt.x - g_dragStartCursor.x) / travelX) * 100.0f : 0.f;
    float dyPercent = (travelY > 1.0f) ? ((float)(pt.y - g_dragStartCursor.y) / travelY) * 100.0f : 0.f;

    g_dragOverrideH.store(std::clamp(g_dragStartH + dxPercent, 0.0f, 100.0f), std::memory_order_relaxed);
    g_dragOverrideV.store(std::clamp(g_dragStartV + dyPercent, 0.0f, 100.0f), std::memory_order_relaxed);
    g_dragOverrideActive.store(true, std::memory_order_relaxed);

    static int s_dragLogCounter = 0;
    if ((++s_dragLogCounter % 15) == 0) {
        Wh_Log(L"[Drag] MOVE cursor=(%d,%d) travel=(%.1f,%.1f) delta%%=(%.2f,%.2f) newHV=(%.2f,%.2f) monitorCached=%d",
               pt.x, pt.y, travelX, travelY, dxPercent, dyPercent,
               g_dragOverrideH.load(std::memory_order_relaxed),
               g_dragOverrideV.load(std::memory_order_relaxed),
               g_cachedMonitor != nullptr);
    }

    // Deliberately NOT calling UpdateSwapChainForLayout() here. RenderVisualizer
    // already calls it once per tick, right before drawing -- doing it again
    // here, from the hook thread, on every single mouse-move (which can fire
    // far more often than the render tick during a fast drag) is exactly what
    // let the window's on-screen position race ahead of what actually got
    // drawn inside it.
}

void EndDrag() {
    if (!g_dragInProgress) return;
    g_dragInProgress = false;
    g_dragRenderPauseActive.store(false, std::memory_order_relaxed);

    float finalH = g_dragOverrideH.load(std::memory_order_relaxed);
    float finalV = g_dragOverrideV.load(std::memory_order_relaxed);
    Wh_Log(L"[Drag] END moved=%d finalHV=(%.2f,%.2f) overrideActive=%d",
           (int)g_dragMoved, finalH, finalV, (int)g_dragOverrideActive.load(std::memory_order_relaxed));

    if (g_dragMoved) {
        PersistOverrideState();
    }
}

// ---- Keyboard move ---------------------------------------------------------
// The precise way to place the visualizer: hold a modifier, tap a direction,
// and the box steps by an exact number of pixels. Nothing here has to track a
// moving cursor or keep up with the render loop -- each keypress is one
// discrete jump, applied to the same position override the drag path writes,
// and picked up by whatever the next frame happens to be.

// Asks the message window to (re)start a short timer that saves the override.
// Key repeat can fire dozens of nudges a second, so the write is deferred until
// the user stops moving rather than run on every keystroke.
void RequestPositionOverrideSave() {
    if (g_messageWnd) PostMessage(g_messageWnd, WM_APP_REQUEST_SAVE_POSITION, 0, 0);
}

bool ModKeysHeld(unsigned flags) {
    if (flags == VIZ_MOD_NONE) return false;
    if ((flags & VIZ_MOD_CTRL)  && !(GetAsyncKeyState(VK_CONTROL) & 0x8000)) return false;
    if ((flags & VIZ_MOD_ALT)   && !(GetAsyncKeyState(VK_MENU)    & 0x8000)) return false;
    if ((flags & VIZ_MOD_SHIFT) && !(GetAsyncKeyState(VK_SHIFT)   & 0x8000)) return false;
    if ((flags & VIZ_MOD_WIN)   && !((GetAsyncKeyState(VK_LWIN) & 0x8000) ||
                                     (GetAsyncKeyState(VK_RWIN) & 0x8000))) return false;
    return true;
}

// Maps a virtual key to a direction, honouring which key set the user enabled.
// Returns false for anything that isn't a direction key we handle.
bool KeyMoveDirection(DWORD vk, int* dx, int* dy) {
    bool arrows = g_settings.keyMoveKeys != VizKeyMoveKeys::Wasd;
    bool wasd   = g_settings.keyMoveKeys != VizKeyMoveKeys::Arrows;

    *dx = *dy = 0;
    if (arrows) {
        switch (vk) {
            case VK_LEFT:  *dx = -1; return true;
            case VK_RIGHT: *dx =  1; return true;
            case VK_UP:    *dy = -1; return true;
            case VK_DOWN:  *dy =  1; return true;
        }
    }
    if (wasd) {
        switch (vk) {
            case 'A': *dx = -1; return true;
            case 'D': *dx =  1; return true;
            case 'W': *dy = -1; return true;
            case 'S': *dy =  1; return true;
        }
    }
    return false;
}

// Moves the visualizer by an exact pixel delta. The override is stored as a
// percentage (that's what ComputeVizLayout consumes), so the delta is converted
// through the same travel range layout uses -- which makes the round trip land
// on the pixel asked for rather than near it.
// Which piece the direction keys currently steer. Touched only from the input
// hook thread, and read by nothing else.
VizMoveTarget g_keyMoveTarget = VizMoveTarget::Visualizer;

void NudgeVisualizerPx(int dxPx, int dyPx) {
    float travelX = 0.f, travelY = 0.f;
    if (!GetVizTravelRange(&travelX, &travelY)) return;

    bool active = g_dragOverrideActive.load(std::memory_order_relaxed);
    float h = active ? g_dragOverrideH.load(std::memory_order_relaxed)
                     : g_settings.horizontalPosition;
    float v = active ? g_dragOverrideV.load(std::memory_order_relaxed)
                     : g_settings.verticalPosition;

    if (dxPx && travelX > 1.0f) h = std::clamp(h + (dxPx / travelX) * 100.0f, 0.0f, 100.0f);
    if (dyPx && travelY > 1.0f) v = std::clamp(v + (dyPx / travelY) * 100.0f, 0.0f, 100.0f);

    g_dragOverrideH.store(h, std::memory_order_relaxed);
    g_dragOverrideV.store(v, std::memory_order_relaxed);
    g_dragOverrideActive.store(true, std::memory_order_relaxed);

    // Rendering may well be idle right now -- repositioning is something people
    // do with nothing playing -- so ask for one frame explicitly instead of
    // waiting for a tick that isn't coming.
    if (g_overlayWnd) PostMessage(g_overlayWnd, WM_APP_FORCE_REDRAW, 0, 0);
    RequestPositionOverrideSave();
}

// The media strip's own travel range, mirroring the sizing math in
// RepositionAndRepaintMediaControls so a pixel delta converts to the same
// percent delta that repositioning will turn back into pixels.
bool GetMediaTravelRange(float* travelX, float* travelY) {
    float dpiScale = GetMediaControlsDpiScale();
    int size = std::max(1, (int)std::lround(g_settings.mediaIconSize * dpiScale));
    int spacing = std::max(0, (int)std::lround(g_settings.mediaIconSpacing * dpiScale));
    int pad = GetMediaPlatePaddingPx();
    int width = size * 3 + spacing * 2 + pad * 2;
    int height = size + pad * 2;

    HMONITOR monitor = TaskbarMonitor();
    if (!monitor) monitor = MonitorFromPoint({0, 0}, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = {sizeof(mi)};
    if (!GetMonitorInfo(monitor, &mi)) return false;

    *travelX = (float)(mi.rcWork.right - mi.rcWork.left - width);
    *travelY = (float)(mi.rcWork.bottom - mi.rcWork.top - height);
    return true;
}

// Moves the media strip by an exact pixel delta. Percentage-based like the
// visualizer rather than a pixel offset like the text overlays, because the
// strip is placed against the monitor rather than against anything else.
void NudgeMediaControlsPx(int dxPx, int dyPx) {
    float travelX = 0.f, travelY = 0.f;
    if (!GetMediaTravelRange(&travelX, &travelY)) return;

    bool active = g_mediaOverrideActive.load(std::memory_order_relaxed);
    float h = active ? g_mediaOverrideH.load(std::memory_order_relaxed)
                     : g_settings.mediaHorizontalPosition;
    float v = active ? g_mediaOverrideV.load(std::memory_order_relaxed)
                     : g_settings.mediaVerticalPosition;

    if (dxPx && travelX > 1.0f) h = std::clamp(h + (dxPx / travelX) * 100.0f, 0.0f, 100.0f);
    if (dyPx && travelY > 1.0f) v = std::clamp(v + (dyPx / travelY) * 100.0f, 0.0f, 100.0f);

    g_mediaOverrideH.store(h, std::memory_order_relaxed);
    g_mediaOverrideV.store(v, std::memory_order_relaxed);
    g_mediaOverrideActive.store(true, std::memory_order_relaxed);

    // Posted rather than called: the strip's window belongs to the UI thread
    // and repositioning it means touching UpdateLayeredWindow, which has no
    // business happening on this hook thread.
    if (g_mediaWnd) PostMessage(g_mediaWnd, WM_APP_MEDIA_REPAINT, 0, 0);
    RequestPositionOverrideSave();
}

// Nudges one of the text overlays. These move in raw pixels relative to the
// visualizer rather than as a percentage of the screen, because that's what
// "put the title just above the panel" actually means -- they're positioned
// against the box, not against the monitor.
void NudgeTextOverlayPx(VizMoveTarget target, int dxPx, int dyPx) {
    std::atomic<int>* ax = nullptr;
    std::atomic<int>* ay = nullptr;
    if (target == VizMoveTarget::NowPlaying) {
        ax = &g_npNudgeX; ay = &g_npNudgeY;
    } else if (target == VizMoveTarget::PeakFreq) {
        ax = &g_pfNudgeX; ay = &g_pfNudgeY;
    } else {
        return;
    }

    // Capped rather than unbounded: every pixel of offset widens the render
    // surface by the same amount (see ComputeVizLayout), so an accidental
    // key-repeat run shouldn't be able to inflate it without limit.
    constexpr int kMaxNudge = 4000;
    ax->store(std::clamp(ax->load(std::memory_order_relaxed) + dxPx, -kMaxNudge, kMaxNudge),
              std::memory_order_relaxed);
    ay->store(std::clamp(ay->load(std::memory_order_relaxed) + dyPx, -kMaxNudge, kMaxNudge),
              std::memory_order_relaxed);

    if (g_overlayWnd) PostMessage(g_overlayWnd, WM_APP_FORCE_REDRAW, 0, 0);
    RequestPositionOverrideSave();
}

// Zeroes the live nudge for whatever is selected. For the visualizer that means
// throwing away the whole saved position; for the text overlays it means
// dropping back to whatever their Offset settings say.
void ResetMoveTarget(VizMoveTarget target) {
    switch (target) {
        case VizMoveTarget::NowPlaying:
            g_npNudgeX.store(0, std::memory_order_relaxed);
            g_npNudgeY.store(0, std::memory_order_relaxed);
            RequestPositionOverrideSave();
            break;
        case VizMoveTarget::PeakFreq:
            g_pfNudgeX.store(0, std::memory_order_relaxed);
            g_pfNudgeY.store(0, std::memory_order_relaxed);
            RequestPositionOverrideSave();
            break;
        case VizMoveTarget::MediaControls:
            g_mediaOverrideActive.store(false, std::memory_order_relaxed);
            RequestPositionOverrideSave();
            if (g_mediaWnd) PostMessage(g_mediaWnd, WM_APP_MEDIA_REPAINT, 0, 0);
            return;  // nothing about the visualizer's own surface changed
        default:
            ClearPositionOverride();
            break;
    }
    if (g_overlayWnd) PostMessage(g_overlayWnd, WM_APP_FORCE_REDRAW, 0, 0);
}

LRESULT CALLBACK MoveKeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && !g_unloading.load(std::memory_order_relaxed) &&
        g_settings.keyMoveEnabled) {
        KBDLLHOOKSTRUCT* kb = (KBDLLHOOKSTRUCT*)lParam;
        bool isDown = (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN);
        bool isUp   = (wParam == WM_KEYUP   || wParam == WM_SYSKEYUP);

        if ((isDown || isUp) && ModKeysHeld(g_settings.keyMoveModifier)) {
            int dx = 0, dy = 0;
            if (KeyMoveDirection(kb->vkCode, &dx, &dy)) {
                if (isDown) {
                    bool fast = g_settings.keyMoveFastKey != VIZ_MOD_NONE &&
                                ModKeysHeld(g_settings.keyMoveFastKey);
                    int step = fast ? g_settings.keyMoveFastStep : g_settings.keyMoveStep;
                    if (g_keyMoveTarget == VizMoveTarget::Visualizer) {
                        NudgeVisualizerPx(dx * step, dy * step);
                    } else if (g_keyMoveTarget == VizMoveTarget::MediaControls) {
                        NudgeMediaControlsPx(dx * step, dy * step);
                    } else {
                        NudgeTextOverlayPx(g_keyMoveTarget, dx * step, dy * step);
                    }
                }
                // Swallow the key-up too, so an app underneath never sees a
                // release for a press it was never told about.
                return 1;
            }

            // Same combo + 1/2/3/4 picks what the direction keys steer. One
            // combo places every movable piece rather than needing a shortcut
            // each, and the choice sticks until it's changed again.
            if (kb->vkCode >= '1' && kb->vkCode <= '4') {
                if (isDown) {
                    g_keyMoveTarget = (kb->vkCode == '2') ? VizMoveTarget::NowPlaying
                                    : (kb->vkCode == '3') ? VizMoveTarget::PeakFreq
                                    : (kb->vkCode == '4') ? VizMoveTarget::MediaControls
                                                          : VizMoveTarget::Visualizer;
                    Wh_Log(L"[KeyMove] target = %s",
                           g_keyMoveTarget == VizMoveTarget::NowPlaying    ? L"Now Playing text"
                           : g_keyMoveTarget == VizMoveTarget::PeakFreq    ? L"frequency readout"
                           : g_keyMoveTarget == VizMoveTarget::MediaControls ? L"media controls"
                                                                            : L"visualizer");
                }
                return 1;
            }

            // Same combo + Home resets whatever is selected: the visualizer
            // hands placement back to the Position percentages, a text overlay
            // drops back to whatever its Offset settings say. There's no
            // settings-UI way to do this, since mods can't write settings back.
            if (kb->vkCode == VK_HOME) {
                if (isDown) {
                    ResetMoveTarget(g_keyMoveTarget);
                    Wh_Log(L"[KeyMove] reset target %d", (int)g_keyMoveTarget);
                }
                return 1;
            }
        }
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

LRESULT CALLBACK DragMouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && !g_unloading.load(std::memory_order_relaxed) &&
        g_settings.dragEnabled) {
        MSLLHOOKSTRUCT* info = (MSLLHOOKSTRUCT*)lParam;
        UINT downMsg = DragButtonDownMsg();
        UINT upMsg = DragButtonUpMsg();

        if (!g_dragInProgress) {
            if (wParam == downMsg && DragModifierHeld() && PointInVisualizerBounds(info->pt)) {
                BeginDrag(info->pt);
                return 1;
            }
        } else {
            if (wParam == WM_MOUSEMOVE) {
                UpdateDrag(info->pt);
                return 1;
            }
            if (wParam == upMsg) {
                POINT pt = info->pt;
                bool wasDrag = g_dragMoved;
                EndDrag();

                if (!wasDrag) {
                    // Not an actual drag -- a plain click-release of the combo.
                    // Two of those close together in place clear a saved
                    // override, since there's no settings-UI way to do it.
                    ULONGLONG now = GetTickCount64();
                    int dx = std::abs(pt.x - g_dragLastClickPos.x);
                    int dy = std::abs(pt.y - g_dragLastClickPos.y);
                    if (g_dragLastClickTick != 0 &&
                        now - g_dragLastClickTick < GetDoubleClickTime() && dx < 6 && dy < 6) {
                        // Not calling UpdateSwapChainForLayout() directly here:
                        // this hook now runs on its own dedicated thread (see
                        // InitInputHooks), so touching the swap chain from here
                        // would race with the render tick that owns it. The
                        // very next tick already re-derives layout from
                        // g_dragOverrideActive and will pick this up on its own.
                        ClearPositionOverride();
                        g_dragLastClickTick = 0;
                    } else {
                        g_dragLastClickTick = now;
                        g_dragLastClickPos = pt;
                    }
                }
                return 1;
            }
        }
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

HHOOK g_dragMouseHook = nullptr;
HHOOK g_moveKeyboardHook = nullptr;
HANDLE g_inputHookThread = nullptr;
DWORD g_inputHookThreadId = 0;

// Both low-level input hooks run on this thread, deliberately kept away from
// the UI thread that also handles WM_APP_RENDER_TICK. Direct2D's Present() can
// block that thread for real time each frame; a hook living there has its
// queued input backed up behind every present, which is what made drag feel
// like pulling the cursor through mud. Windows also silently drops a
// low-level hook whose thread doesn't service messages promptly, so this
// thread does nothing but pump.
DWORD WINAPI InputHookThreadProc(LPVOID) {
    HINSTANCE hInst = (HINSTANCE)GetCurrentModuleHandle();

    g_dragMouseHook = SetWindowsHookEx(WH_MOUSE_LL, DragMouseHookProc, hInst, 0);
    if (!g_dragMouseHook) {
        Wh_Log(L"[Drag] SetWindowsHookEx(WH_MOUSE_LL) failed, error=%lu", GetLastError());
    }

    g_moveKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, MoveKeyboardHookProc, hInst, 0);
    if (!g_moveKeyboardHook) {
        Wh_Log(L"[KeyMove] SetWindowsHookEx(WH_KEYBOARD_LL) failed, error=%lu", GetLastError());
    }

    if (!g_dragMouseHook && !g_moveKeyboardHook) return 1;

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Low-level hooks have to be removed by the thread that installed them,
    // which is why this happens here rather than in UninitInputHooks.
    if (g_dragMouseHook) {
        UnhookWindowsHookEx(g_dragMouseHook);
        g_dragMouseHook = nullptr;
    }
    if (g_moveKeyboardHook) {
        UnhookWindowsHookEx(g_moveKeyboardHook);
        g_moveKeyboardHook = nullptr;
    }
    return 0;
}

void InitInputHooks() {
    if (g_inputHookThread) return;
    g_inputHookThread = CreateThread(nullptr, 0, InputHookThreadProc, nullptr, 0,
                                     &g_inputHookThreadId);
    if (g_inputHookThread) {
        SetThreadDescription(g_inputHookThread, L"TaskbarAudioVisualizer-InputHooks");
    }
}

void UninitInputHooks() {
    if (g_inputHookThread) {
        PostThreadMessage(g_inputHookThreadId, WM_QUIT, 0, 0);
        WaitForSingleObject(g_inputHookThread, 3000);
        CloseHandle(g_inputHookThread);
        g_inputHookThread = nullptr;
        g_inputHookThreadId = 0;
    }
}

FILETIME GetWallpaperFileTime() {
    WCHAR path[MAX_PATH] = {};
    SystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, path, 0);
    FILETIME ft = {};
    HANDLE hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile != INVALID_HANDLE_VALUE) {
        GetFileTime(hFile, nullptr, nullptr, &ft);
        CloseHandle(hFile);
    }
    return ft;
}

void CaptureWallpaperBitmap() {
    g_wallpaperBitmap.Reset();
    if (!g_overlayWnd || !g_dc || !g_swapChain) return;

    g_lastWallpaperTime = GetWallpaperFileTime();

    g_dc->BeginDraw();
    g_dc->Clear(D2D1::ColorF(0, 0, 0, 0));
    g_dc->EndDraw();
    g_swapChain->Present(1, 0);
    DwmFlush();

    HWND hParent = GetParent(g_overlayWnd);
    if (!hParent) return;

    RECT rc;
    GetClientRect(hParent, &rc);
    int w = rc.right - rc.left;
    int h = rc.bottom - rc.top;
    if (w <= 0 || h <= 0) return;

    HWND hSource = FindWindow(L"Progman", nullptr);
    if (!hSource) hSource = hParent;

    HDC hdcScreen = GetDC(nullptr);
    if (!hdcScreen) return;
    HDC hdcMem = CreateCompatibleDC(hdcScreen);
    if (!hdcMem) { ReleaseDC(nullptr, hdcScreen); return; }

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* pvBits = nullptr;
    HBITMAP hBmp = CreateDIBSection(hdcMem, &bmi, DIB_RGB_COLORS, &pvBits, nullptr, 0);
    if (!hBmp) { DeleteDC(hdcMem); ReleaseDC(nullptr, hdcScreen); return; }

    HGDIOBJ hOldBmp = SelectObject(hdcMem, hBmp);

    if (!PrintWindow(hSource, hdcMem, 0x02 /*PW_RENDERFULLCONTENT*/)) {
        SelectObject(hdcMem, hOldBmp);
        DeleteObject(hBmp);
        DeleteDC(hdcMem);
        ReleaseDC(nullptr, hdcScreen);
        return;
    }
    GdiFlush();

    BYTE* pixels = static_cast<BYTE*>(pvBits);
    for (int i = 0; i < w * h; i++) pixels[i * 4 + 3] = 255;

    D2D1_BITMAP_PROPERTIES bitmapProps = D2D1::BitmapProperties(
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
    g_dc->CreateBitmap(D2D1::SizeU(w, h), pvBits, w * 4, bitmapProps, &g_wallpaperBitmap);

    SelectObject(hdcMem, hOldBmp);
    DeleteObject(hBmp);
    DeleteDC(hdcMem);
    ReleaseDC(nullptr, hdcScreen);
}

void ReleaseVisualResources() {
    g_blurEffect.Reset();
    g_blurredBitmap.Reset();
    g_wallpaperBitmap.Reset();
    g_borderBrush.Reset();
    g_backgroundBrush.Reset();
    g_barBrush.Reset();
    g_barBrush2.Reset();
    g_bgGeoCache.Reset();
    g_borderRingCache.Reset();
    g_bgGeoCacheRect = D2D1::RectF(-1, -1, -1, -1);
    g_bgGeoCacheRadii[0] = g_bgGeoCacheRadii[1] =
        g_bgGeoCacheRadii[2] = g_bgGeoCacheRadii[3] = -1.f;
    g_borderCacheBorderSize = -1;
    g_nowPlayingBrush.Reset();
    g_textPanelBrush.Reset();
}

void ReleaseSwapChainResources() {
    ReleaseVisualResources();
    g_compositionVisual.Reset();
    g_compositionTarget.Reset();
    g_compositionDevice.Reset();
    g_dc.Reset();
    g_swapChain.Reset();
}

bool RecreateVisualResources() {
    HRESULT hr;

    D2D1_COLOR_F barColor = D2D1::ColorF(g_settings.colorR / 255.0f, g_settings.colorG / 255.0f,
                                         g_settings.colorB / 255.0f, g_settings.colorA / 255.0f);
    hr = g_dc->CreateSolidColorBrush(barColor, &g_barBrush);
    if (FAILED(hr)) { Wh_Log(L"HRESULT line=%d error=0x%08X", __LINE__, hr); return false; }

    D2D1_COLOR_F peakHoldColor = D2D1::ColorF(g_settings.peakHoldR / 255.0f, g_settings.peakHoldG / 255.0f,
                                               g_settings.peakHoldB / 255.0f, g_settings.peakHoldA / 255.0f);
    g_dc->CreateSolidColorBrush(peakHoldColor, &g_barBrush2);

    if (g_settings.backgroundEnabled) {
        D2D1_COLOR_F bgColor = D2D1::ColorF(g_settings.bgR / 255.0f, g_settings.bgG / 255.0f,
                                            g_settings.bgB / 255.0f, g_settings.bgA / 255.0f);
        g_dc->CreateSolidColorBrush(bgColor, &g_backgroundBrush);

        if (g_settings.bgBlur > 0) {
            CaptureWallpaperBitmap();
            if (g_wallpaperBitmap) {
                hr = g_dc->CreateEffect(kCLSID_D2D1GaussianBlur, &g_blurEffect);
                if (SUCCEEDED(hr)) {
                    g_blurEffect->SetInput(0, g_wallpaperBitmap.Get());
                    g_blurEffect->SetValue(0, (FLOAT)g_settings.bgBlur);
                    g_blurEffect->SetValue(2, (UINT32)1);

                    // Evaluate the blur exactly once, into a bitmap covering only
                    // the widget's bounding box rather than the whole desktop.
                    //
                    // The blur still SAMPLES the full-size wallpaper (it has to --
                    // a Gaussian reads neighbouring pixels from beyond the box's
                    // edges), but only the box-sized result is kept. At 1080p that
                    // is roughly 8 MB of video memory replaced by tens of KB.
                    VizLayout blurLayout;
                    if (ComputeVizLayout(&blurLayout)) {
                        D2D1_SIZE_U blurSize = D2D1::SizeU(blurLayout.width, blurLayout.height);

                        D2D1_BITMAP_PROPERTIES1 blurProps = {};
                        blurProps.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
                        blurProps.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
                        blurProps.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;

                        if (SUCCEEDED(g_dc->CreateBitmap(blurSize, nullptr, 0, blurProps,
                                                          &g_blurredBitmap))) {
                            ComPtr<ID2D1Image> savedTarget;
                            g_dc->GetTarget(&savedTarget);
                            g_dc->SetTarget(g_blurredBitmap.Get());
                            g_dc->BeginDraw();
                            g_dc->Clear(D2D1::ColorF(0, 0, 0, 0));
                            // Shift the wallpaper so the slice under the widget
                            // lands at the origin of this small target.
                            g_dc->SetTransform(D2D1::Matrix3x2F::Translation(
                                -blurLayout.originX, -blurLayout.originY));
                            g_dc->DrawImage(g_blurEffect.Get());
                            g_dc->SetTransform(D2D1::Matrix3x2F::Identity());
                            HRESULT hrBlur = g_dc->EndDraw();
                            g_dc->SetTarget(savedTarget.Get());
                            if (FAILED(hrBlur)) g_blurredBitmap.Reset();
                        }
                    }
                }
            }
            // Once the blur is baked, neither the effect graph nor the full-size
            // source wallpaper bitmap is needed again -- releasing both frees the
            // memory they were holding for the life of the overlay.
            if (g_blurredBitmap) {
                g_blurEffect.Reset();
                g_wallpaperBitmap.Reset();
            }
        }

        if (g_settings.bgBorderSize > 0) {
            D2D1_COLOR_F borderColor =
                D2D1::ColorF(g_settings.borderR / 255.0f, g_settings.borderG / 255.0f,
                            g_settings.borderB / 255.0f, g_settings.borderA / 255.0f);
            g_dc->CreateSolidColorBrush(borderColor, &g_borderBrush);
        }
    }

    if (g_settings.nowPlayingEnabled || g_settings.peakFreqEnabled) {
        // One scratch brush shared by both text panels and both their borders.
        // Each use sets its colour first -- four separate brushes would be four
        // objects to keep in step with four settings for no benefit, since the
        // draws are strictly sequential.
        g_dc->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &g_textPanelBrush);

        D2D1_COLOR_F npColor =
            D2D1::ColorF(g_settings.nowPlayingR / 255.0f, g_settings.nowPlayingG / 255.0f,
                        g_settings.nowPlayingB / 255.0f, g_settings.nowPlayingA / 255.0f);
        g_dc->CreateSolidColorBrush(npColor, &g_nowPlayingBrush);

        int fontSize = std::max(6, g_settings.nowPlayingFontSize);
        if (g_dwriteFactory && (!g_dwriteTextFormat || g_dwriteTextFormatFontSize != fontSize ||
                                 g_dwriteTextFormatFontName != g_settings.nowPlayingFont)) {
            g_dwriteTextFormat.Reset();
            WCHAR localeName[LOCALE_NAME_MAX_LENGTH];
            if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH) == 0) {
                wcscpy_s(localeName, L"en-us");
            }
            HRESULT hrText = g_dwriteFactory->CreateTextFormat(
                g_settings.nowPlayingFont.c_str(), nullptr, DWRITE_FONT_WEIGHT_SEMI_BOLD,
                DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
                (FLOAT)fontSize * g_dpiScale, localeName, &g_dwriteTextFormat);
            if (SUCCEEDED(hrText)) {
                g_dwriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
                g_dwriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
                g_dwriteTextFormatFontSize = fontSize;
                g_dwriteTextFormatFontName = g_settings.nowPlayingFont;
            }
        }
    }

    return true;
}


void FillRoundedRectPerCorner(ID2D1DeviceContext* dc, ID2D1Factory1* factory,
                               const D2D1_RECT_F& r, ID2D1Brush* brush,
                               float rTL, float rTR, float rBR, float rBL) {
    if (rTL == rTR && rTR == rBR && rBR == rBL) {
        float clampedR = std::min(rTL, std::min(r.right - r.left, r.bottom - r.top) / 2.0f);
        dc->FillRoundedRectangle(
            D2D1::RoundedRect(r, clampedR, clampedR), brush);
        return;
    }

    float w = r.right  - r.left;
    float h = r.bottom - r.top;

    rTL = std::min(rTL, std::min(w, h) / 2.0f);
    rTR = std::min(rTR, std::min(w, h) / 2.0f);
    rBR = std::min(rBR, std::min(w, h) / 2.0f);
    rBL = std::min(rBL, std::min(w, h) / 2.0f);

    ComPtr<ID2D1PathGeometry> geo;
    if (FAILED(factory->CreatePathGeometry(&geo))) return;

    ComPtr<ID2D1GeometrySink> sink;
    if (FAILED(geo->Open(&sink))) return;

    sink->SetFillMode(D2D1_FILL_MODE_WINDING);
    sink->BeginFigure(D2D1::Point2F(r.left + rTL, r.top), D2D1_FIGURE_BEGIN_FILLED);

    sink->AddLine(D2D1::Point2F(r.right - rTR, r.top));
    if (rTR > 0)
        sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(r.right, r.top + rTR),
            D2D1::SizeF(rTR, rTR), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));

    sink->AddLine(D2D1::Point2F(r.right, r.bottom - rBR));
    if (rBR > 0)
        sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(r.right - rBR, r.bottom),
            D2D1::SizeF(rBR, rBR), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));

    sink->AddLine(D2D1::Point2F(r.left + rBL, r.bottom));
    if (rBL > 0)
        sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(r.left, r.bottom - rBL),
            D2D1::SizeF(rBL, rBL), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));

    sink->AddLine(D2D1::Point2F(r.left, r.top + rTL));
    if (rTL > 0)
        sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(r.left + rTL, r.top),
            D2D1::SizeF(rTL, rTL), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));

    sink->EndFigure(D2D1_FIGURE_END_CLOSED);
    sink->Close();

    dc->FillGeometry(geo.Get(), brush);
}

HRESULT CreateRoundedRectPath(ID2D1Factory1* factory, const D2D1_RECT_F& r,
                               float rTL, float rTR, float rBR, float rBL,
                               ID2D1PathGeometry** outGeo) {
    float w = r.right - r.left, h = r.bottom - r.top;
    float maxR = std::min(w, h) / 2.0f;
    rTL = std::min(rTL, maxR); rTR = std::min(rTR, maxR);
    rBR = std::min(rBR, maxR); rBL = std::min(rBL, maxR);

    ComPtr<ID2D1PathGeometry> geo;
    HRESULT hr = factory->CreatePathGeometry(&geo);
    if (FAILED(hr)) return hr;

    ComPtr<ID2D1GeometrySink> sink;
    hr = geo->Open(&sink);
    if (FAILED(hr)) return hr;

    sink->SetFillMode(D2D1_FILL_MODE_WINDING);
    sink->BeginFigure(D2D1::Point2F(r.left + rTL, r.top), D2D1_FIGURE_BEGIN_FILLED);

    sink->AddLine(D2D1::Point2F(r.right - rTR, r.top));
    if (rTR > 0) sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(r.right, r.top + rTR),
        D2D1::SizeF(rTR, rTR), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));

    sink->AddLine(D2D1::Point2F(r.right, r.bottom - rBR));
    if (rBR > 0) sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(r.right - rBR, r.bottom),
        D2D1::SizeF(rBR, rBR), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));

    sink->AddLine(D2D1::Point2F(r.left + rBL, r.bottom));
    if (rBL > 0) sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(r.left, r.bottom - rBL),
        D2D1::SizeF(rBL, rBL), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));

    sink->AddLine(D2D1::Point2F(r.left, r.top + rTL));
    if (rTL > 0) sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(r.left + rTL, r.top),
        D2D1::SizeF(rTL, rTL), 0.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));

    sink->EndFigure(D2D1_FIGURE_END_CLOSED);
    hr = sink->Close();
    if (FAILED(hr)) return hr;

    *outGeo = geo.Detach();
    return S_OK;
}

// The colours and geometry of one text overlay's panel, bundled so the two
// callers don't each pass a dozen loose arguments.
struct TextPanelStyle {
    BYTE fillA, fillR, fillG, fillB;
    BYTE borderA, borderR, borderG, borderB;
    int padding, cornerRadius, borderSize;
};

// Draws a text overlay, optionally on a panel fitted to the text.
//
// `box` is the layout rectangle the text is centred within, which is much wider
// than the text itself -- so the panel can't just use it, or it would stretch
// the full width of the reserved area. Measuring the text means building a text
// layout, which is exactly what DrawText does internally anyway; when a panel is
// wanted we keep that layout and draw from it, so nothing is measured twice.
//
// fadeAlpha scales the whole thing, so a panel fades in and out with the Now
// Playing text instead of popping.
void DrawOverlayText(PCWSTR text, UINT32 len, const D2D1_RECT_F& box, ID2D1Brush* textBrush,
                     const TextPanelStyle& style, float fadeAlpha) {
    bool wantFill = style.fillA > 0;
    bool wantBorder = style.borderSize > 0 && style.borderA > 0;

    ComPtr<IDWriteTextLayout> layout;
    if ((wantFill || wantBorder) && g_dwriteFactory && g_textPanelBrush) {
        float boxW = box.right - box.left;
        float boxH = box.bottom - box.top;
        DWRITE_TEXT_METRICS m{};
        if (SUCCEEDED(g_dwriteFactory->CreateTextLayout(text, len, g_dwriteTextFormat.Get(),
                                                        boxW, boxH, &layout)) &&
            layout && SUCCEEDED(layout->GetMetrics(&m)) && m.width > 0.f && m.height > 0.f) {
            float pad = (float)style.padding * g_dpiScale;
            D2D1_RECT_F r = D2D1::RectF(box.left + m.left - pad, box.top + m.top - pad,
                                        box.left + m.left + m.width + pad,
                                        box.top + m.top + m.height + pad);

            float maxRadius = std::min((r.right - r.left) * 0.5f, (r.bottom - r.top) * 0.5f);
            float rad = std::min((float)style.cornerRadius * g_dpiScale, maxRadius);

            if (wantFill) {
                g_textPanelBrush->SetColor(D2D1::ColorF(
                    style.fillR / 255.0f, style.fillG / 255.0f, style.fillB / 255.0f,
                    (style.fillA / 255.0f) * fadeAlpha));
                g_dc->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad),
                                           g_textPanelBrush.Get());
            }

            if (wantBorder) {
                // DrawRoundedRectangle strokes centred on the path, so the rect
                // is inset by half the stroke to keep the whole border inside
                // the panel rather than straddling its edge.
                float bw = std::min((float)style.borderSize * g_dpiScale, maxRadius);
                D2D1_RECT_F sr = D2D1::RectF(r.left + bw * 0.5f, r.top + bw * 0.5f,
                                             r.right - bw * 0.5f, r.bottom - bw * 0.5f);
                float srad = std::max(0.0f, rad - bw * 0.5f);
                g_textPanelBrush->SetColor(D2D1::ColorF(
                    style.borderR / 255.0f, style.borderG / 255.0f, style.borderB / 255.0f,
                    (style.borderA / 255.0f) * fadeAlpha));
                g_dc->DrawRoundedRectangle(D2D1::RoundedRect(sr, srad, srad),
                                           g_textPanelBrush.Get(), bw);
            }
        }
    }

    if (layout) {
        g_dc->DrawTextLayout(D2D1::Point2F(box.left, box.top), layout.Get(), textBrush);
    } else {
        g_dc->DrawText(text, len, g_dwriteTextFormat.Get(), box, textBrush);
    }
}

bool RectsApproxEqual(const D2D1_RECT_F& a, const D2D1_RECT_F& b) {
    auto eq = [](float x, float y) { return fabsf(x - y) < 0.01f; };
    return eq(a.left, b.left) && eq(a.top, b.top) &&
           eq(a.right, b.right) && eq(a.bottom, b.bottom);
}

void RenderVisualizer() {
    if (g_unloading || !g_dc || !g_swapChain) return;
    // The bar brushes can be gone while the device context survives (a failed
    // resource rebuild, often a graphics reset when a game starts). Drawing with a
    // null brush crashed the whole process. Rebuild them; if that fails too, close
    // the strip so its WM_DESTROY drops the swap chain and the heal rebuilds it.
    if ((!g_barBrush || !g_barBrush2) && (!RecreateVisualResources() || !g_barBrush || !g_barBrush2)) {
        HWND overlayWnd = g_overlayWnd.load(std::memory_order_relaxed);
        if (overlayWnd) PostMessage(overlayWnd, WM_CLOSE, 0, 0);
        return;
    }

    // Advance the auto-hide follow animation. The shell's own slide runs about
    // 150 ms with an ease-out; smoothstep over the same time reads the same.
    {
        ULONGLONG elapsed = GetTickCount64() - g_followAnimStart;
        float t = (float)std::min(1.0, (double)elapsed / 150.0);
        t = t * t * (3.f - 2.f * t);
        float target = g_followTargetHidden ? 1.f : 0.f;
        g_followSlide = g_followAnimFrom + (target - g_followAnimFrom) * t;
    }

    // Keeps the swap chain's on-screen position (the composition visual's
    // offset) and the content about to be drawn inside it derived from the
    // very same layout snapshot. Repositioning separately -- e.g. from the
    // drag hook on every mouse-move, independently of this tick -- let the
    // window race ahead of what got drawn inside it during a fast drag, so
    // the box and its background visibly fell out of sync until the next
    // tick caught up. Cheap to call defensively when nothing has moved.
    UpdateSwapChainForLayout();

    float sceneAlpha = 1.0f;
    if (g_settings.autoHideEnabled) {
        ULONGLONG idleMs = GetTickCount64() - g_lastAudibleTickMs.load(std::memory_order_relaxed);
        ULONGLONG delayMs = (ULONGLONG)std::max(0, g_settings.autoHideDelaySeconds) * 1000ULL;
        constexpr ULONGLONG kFadeMs = 1500;
        if (idleMs > delayMs) {
            ULONGLONG fadeElapsed = idleMs - delayMs;
            sceneAlpha = (fadeElapsed >= kFadeMs) ? 0.f : 1.0f - (float)fadeElapsed / (float)kFadeMs;
        }
    }

    bool fullyFollowedOut = g_followSlide >= 0.999f;
    if (sceneAlpha <= 0.001f || fullyFollowedOut) {
        // Fully hidden -- silent fade or the taskbar auto-hide. Keep the
        // visual offset in step with any pending slide so a reveal never
        // starts from a stale position, present one blank frame to clear
        // whatever was last shown, then skip the render path entirely until
        // audio returns or the bar comes back -- there is no point drawing a
        // scene at full detail and then making it invisible.
        UpdateSwapChainForLayout();
        if (g_autoHideBlanked) return;
        g_dc->BeginDraw();
        g_dc->Clear(D2D1::ColorF(0, 0, 0, 0));
        g_dc->EndDraw();
        g_swapChain->Present(0, 0);
        g_autoHideBlanked = true;
        return;
    }
    g_autoHideBlanked = false;

    g_dc->BeginDraw();
    g_dc->Clear(D2D1::ColorF(0, 0, 0, 0));

    UpdateVisualizerTargets();

    int barCount = std::max(1, std::min(g_settings.barCount, VIZ_BARS_MAX));
    float barW = (float)std::max(1, g_settings.barWidth) * g_dpiScale;
    float barGap = (float)std::max(0, g_settings.barGap) * g_dpiScale;
    float maxSize = (float)std::max(2, g_settings.barMaxSize) * g_dpiScale;
    float idleSize = (float)std::max(0, g_settings.barIdleSize) * g_dpiScale;
    float rTL = g_settings.barRadiusTL * g_dpiScale;
    float rTR = g_settings.barRadiusTR * g_dpiScale;
    float rBR = g_settings.barRadiusBR * g_dpiScale;
    float rBL = g_settings.barRadiusBL * g_dpiScale;

    float attack = 0.55f, decay = 0.18f;
    switch (g_settings.shape) {
        case VizShape::Stereo:  attack = 0.72f; decay = 0.22f; break;
        case VizShape::Mirror:  attack = 0.52f; decay = 0.20f; break;
        case VizShape::Wave:    attack = 0.34f; decay = 0.17f; break;
        case VizShape::Breathe: attack = 0.20f; decay = 0.11f; break;
        default: break;
    }
    if (g_settings.smoothing > 0) {
        // Scales both toward 0 (slower catch-up to the target level) without
        // ever fully freezing the bar, even at max smoothing.
        float smoothFactor = 1.0f - (g_settings.smoothing / 100.0f) * 0.9f;
        attack *= smoothFactor;
        decay *= smoothFactor;
    }
    // The rates above are per 60 fps frame. Scale them by the real frame time so
    // an uneven frame does not make the fall stutter.
    float vizFrames = 1.0f;
    {
        static LARGE_INTEGER s_qpcFreq{}, s_lastQpc{};
        LARGE_INTEGER nowQpc;
        if (!s_qpcFreq.QuadPart) QueryPerformanceFrequency(&s_qpcFreq);
        QueryPerformanceCounter(&nowQpc);
        if (s_lastQpc.QuadPart && s_qpcFreq.QuadPart) {
            double ms = (double)(nowQpc.QuadPart - s_lastQpc.QuadPart) * 1000.0 / (double)s_qpcFreq.QuadPart;
            vizFrames = (float)std::clamp(ms / (1000.0 / 60.0), 0.25, 4.0);
        }
        s_lastQpc = nowQpc;
    }
    attack = 1.0f - powf(1.0f - attack, vizFrames);
    decay  = 1.0f - powf(1.0f - decay,  vizFrames);

    bool horizontal = (g_settings.orientation == VizOrientation::Horizontal);
    
    float barsThickness = barCount * barW + (barCount - 1) * barGap;
    
    float groupThickness = barsThickness;
    float groupExtent    = maxSize;

    float totalWidth, totalHeight;
    if (g_settings.shape == VizShape::Radial) {
        totalWidth = totalHeight = maxSize * 2.0f;
    } else {
        totalWidth  = horizontal ? groupThickness : groupExtent;
        totalHeight = horizontal ? groupExtent    : groupThickness;
    }

    float animTime = (float)GetTickCount64() * 0.001f;
    {
        float pulse = g_beatPulse.load(std::memory_order_relaxed);
        if (pulse > 0.f) g_beatPulse.store(std::max(0.f, pulse - 0.08f), std::memory_order_relaxed);
    }

    bool useFadeLayer = sceneAlpha < 0.999f;

    VizLayout layout;
    if (ComputeVizLayout(&layout)) {
        if (useFadeLayer) {
            g_dc->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), nullptr,
                D2D1_ANTIALIAS_MODE_PER_PRIMITIVE, D2D1::IdentityMatrix(), sceneAlpha), nullptr);
        }

        // Drawing happens in swap-chain-local coordinates. The swap chain covers
        // only the widget's bounding box, and the composition visual carries the
        // offset that places it on screen.
        float blockX = layout.blockX;
        float blockY = layout.blockY;
        totalWidth   = layout.totalWidth;
        totalHeight  = layout.totalHeight;

        // Publish the bounds of what is actually VISIBLE, for the occlusion
        // check -- not the full render surface. The surface reserves invisible
        // insets (a safety margin, and room above/beside the bars for the Now
        // Playing label), and near a screen edge those insets push the surface
        // off-screen entirely. Testing that larger box would mean no window
        // could ever fully contain it, and the check would never fire.
        //
        // Screen coordinates: the layout is taskbar-local and the overlay is
        // parked on the taskbar, so the surface's origin on screen is the
        // overlay window's own top-left plus the layout origin. This used to
        // add the virtual-screen metrics instead; with the check shipped
        // hardcoded off it was never exercised, and on a multi-monitor
        // desktop that corner is a different monitor entirely, so the
        // occlusion check silently examined empty space.
        {
            int originScreenX = GetSystemMetrics(SM_XVIRTUALSCREEN);
            int originScreenY = GetSystemMetrics(SM_YVIRTUALSCREEN);
            RECT overlayRect{};
            if (GetWindowRect(g_overlayWnd.load(std::memory_order_relaxed), &overlayRect)) {
                originScreenX = overlayRect.left;
                originScreenY = overlayRect.top;
            }
            float padL = g_settings.backgroundEnabled ? (float)g_settings.bgPaddingL * g_dpiScale : 0.f;
            float padR = g_settings.backgroundEnabled ? (float)g_settings.bgPaddingR * g_dpiScale : 0.f;
            float padT = g_settings.backgroundEnabled ? (float)g_settings.bgPaddingT * g_dpiScale : 0.f;
            float padB = g_settings.backgroundEnabled ? (float)g_settings.bgPaddingB * g_dpiScale : 0.f;
            float visL = layout.originX + blockX - padL;
            float visT = layout.originY + blockY - padT;
            float visR = layout.originX + blockX + totalWidth + padR;
            float visB = layout.originY + blockY + totalHeight + padB;
            g_drawRectL.store((LONG)visL + originScreenX, std::memory_order_relaxed);
            g_drawRectT.store((LONG)visT + originScreenY, std::memory_order_relaxed);
            g_drawRectR.store((LONG)visR + originScreenX, std::memory_order_relaxed);
            g_drawRectB.store((LONG)visB + originScreenY, std::memory_order_relaxed);
            g_drawRectValid.store(true, std::memory_order_relaxed);
        }

        UpdateCapturePicker();
        if (g_backgroundBrush) {
            float padL = (float)g_settings.bgPaddingL * g_dpiScale;
            float padR = (float)g_settings.bgPaddingR * g_dpiScale;
            float padT = (float)g_settings.bgPaddingT * g_dpiScale;
            float padB = (float)g_settings.bgPaddingB * g_dpiScale;
            float bgWidth  = totalWidth  + padL + padR;
            float bgHeight = totalHeight + padT + padB;

            float bgTL = g_settings.bgRadiusTL * g_dpiScale;
            float bgTR = g_settings.bgRadiusTR * g_dpiScale;
            float bgBR = g_settings.bgRadiusBR * g_dpiScale;
            float bgBL = g_settings.bgRadiusBL * g_dpiScale;

            D2D1_RECT_F bgRect = D2D1::RectF(blockX - padL, blockY - padT,
                                              blockX + totalWidth + padR,
                                              blockY + totalHeight + padB);

            // Negative padding can shrink a side past the bars entirely. Once
            // opposite sides would cross over and invert the rect, D2D just
            // draws nothing -- so instead of letting that happen, hold the box
            // open to a sliver on whichever side is collapsing.
            if (bgRect.right - bgRect.left < 1.0f) {
                float mid = (bgRect.left + bgRect.right) * 0.5f;
                bgRect.left = mid - 0.5f;
                bgRect.right = mid + 0.5f;
            }
            if (bgRect.bottom - bgRect.top < 1.0f) {
                float mid = (bgRect.top + bgRect.bottom) * 0.5f;
                bgRect.top = mid - 0.5f;
                bgRect.bottom = mid + 0.5f;
            }
            bgWidth  = bgRect.right  - bgRect.left;
            bgHeight = bgRect.bottom - bgRect.top;

            bool bgDirty = !g_bgGeoCache ||
                           !RectsApproxEqual(bgRect, g_bgGeoCacheRect) ||
                           g_bgGeoCacheRadii[0] != bgTL || g_bgGeoCacheRadii[1] != bgTR ||
                           g_bgGeoCacheRadii[2] != bgBR || g_bgGeoCacheRadii[3] != bgBL;

            if (bgDirty) {
                g_bgGeoCache.Reset();
                g_borderRingCache.Reset();
                CreateRoundedRectPath(g_d2dFactory.Get(), bgRect, bgTL, bgTR, bgBR, bgBL,
                                      &g_bgGeoCache);
                g_bgGeoCacheRect = bgRect;
                g_bgGeoCacheRadii[0] = bgTL; g_bgGeoCacheRadii[1] = bgTR;
                g_bgGeoCacheRadii[2] = bgBR; g_bgGeoCacheRadii[3] = bgBL;
            }

            ID2D1PathGeometry* bgGeo = g_bgGeoCache.Get();

            if (g_blurredBitmap && bgGeo) {
                g_dc->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), bgGeo),
                                nullptr);
                // The cached blur is already box-sized and box-aligned, so this
                // is a straight 1:1 blit with no scaling or resampling.
                g_dc->DrawBitmap(g_blurredBitmap.Get());
                g_dc->PopLayer();
            }

            if (bgGeo)
                g_dc->FillGeometry(bgGeo, g_backgroundBrush.Get());

            if (g_borderBrush) {
                float bw = std::min((float)g_settings.bgBorderSize * g_dpiScale,
                                    std::min(bgWidth, bgHeight) / 2.0f);

                if (bgDirty || g_borderCacheBorderSize != g_settings.bgBorderSize) {
                    g_borderRingCache.Reset();

                    D2D1_RECT_F innerRect = D2D1::RectF(bgRect.left + bw, bgRect.top + bw,
                                                         bgRect.right - bw, bgRect.bottom - bw);
                    float iTL = std::max(0.0f, bgTL - bw);
                    float iTR = std::max(0.0f, bgTR - bw);
                    float iBR = std::max(0.0f, bgBR - bw);
                    float iBL = std::max(0.0f, bgBL - bw);

                    ComPtr<ID2D1PathGeometry> innerGeo;
                    CreateRoundedRectPath(g_d2dFactory.Get(), innerRect, iTL, iTR, iBR, iBL,
                                          &innerGeo);

                    if (bgGeo && innerGeo) {
                        ID2D1Geometry* geos[] = {bgGeo, innerGeo.Get()};
                        g_d2dFactory->CreateGeometryGroup(D2D1_FILL_MODE_ALTERNATE, geos, 2,
                                                          &g_borderRingCache);
                    }
                    g_borderCacheBorderSize = g_settings.bgBorderSize;
                }

                if (g_borderRingCache)
                    g_dc->FillGeometry(g_borderRingCache.Get(), g_borderBrush.Get());
            }
        }

        if (g_dragRenderPauseActive.load(std::memory_order_relaxed)) {
            // Mid-drag: only the background/border box (just drawn above,
            // already at its new position) should be visible while it's being
            // moved -- freeze the bars in place rather than animate them
            // under a box that's being repositioned.
            static int s_dragTickLogCounter = 0;
            if ((++s_dragTickLogCounter % 10) == 0) {
                Wh_Log(L"[Drag] TICK originXY=(%.1f,%.1f) blockXY=(%.1f,%.1f) HV=(%.2f,%.2f)",
                       layout.originX, layout.originY, layout.blockX, layout.blockY,
                       g_dragOverrideH.load(std::memory_order_relaxed),
                       g_dragOverrideV.load(std::memory_order_relaxed));
            }
            if (useFadeLayer) g_dc->PopLayer();
            g_dc->EndDraw();
            g_swapChain->Present(0, 0);
            return;
        }

        RGBA c1{g_settings.colorA, g_settings.colorR, g_settings.colorG, g_settings.colorB};
        {
            if (g_settings.colorMode == VizColorMode::Accent) {
                DWORD dw = GetWindowsAccentColor();
                c1 = {0xFF, (BYTE)((dw>>16)&0xFF), (BYTE)((dw>>8)&0xFF), (BYTE)(dw&0xFF)};
            } else if (g_settings.colorMode == VizColorMode::AlbumArt) {
                DWORD dw = g_albumArtColor.load(std::memory_order_relaxed);
                c1 = {0xFF, (BYTE)((dw>>16)&0xFF), (BYTE)((dw>>8)&0xFF), (BYTE)(dw&0xFF)};
            } else if (g_settings.colorMode == VizColorMode::DynamicAlbum) {
                DWORD dw = g_albumArtColor.load(std::memory_order_relaxed);
                c1 = {0xFF, (BYTE)((dw>>16)&0xFF), (BYTE)((dw>>8)&0xFF), (BYTE)(dw&0xFF)};
            }
        }
        RGBA c2{g_settings.grad2A, g_settings.grad2R, g_settings.grad2G, g_settings.grad2B};
        RGBA cGrad1{g_settings.grad1A, g_settings.grad1R, g_settings.grad1G, g_settings.grad1B};
        if (g_settings.colorMode == VizColorMode::Tourne) {
            cGrad1 = {255, 20, 184, 166};
            c2     = {255, 200, 29, 51};
        }
        if (g_settings.colorMode == VizColorMode::DynamicAlbum) {
            DWORD dw = g_albumArtColorSecondary.load(std::memory_order_relaxed);
            c2    = {0xFF, (BYTE)((dw>>16)&0xFF), (BYTE)((dw>>8)&0xFF), (BYTE)(dw&0xFF)};
            cGrad1 = c1;
        }

        if (g_captureHover) {
            // Same look as the player hover: Mocha crust at 75 %, 1 px blue border,
            // filling the island's right half inside its outline.
            ComPtr<ID2D1SolidColorBrush> fill, edge;
            D2D1_RECT_F box;
            if (VizHoverBox(g_dpiScale, &box)) {
                box.left -= layout.originX; box.right -= layout.originX;
                box.top -= layout.originY; box.bottom -= layout.originY;
            } else {
                box = D2D1::RectF(blockX-3*g_dpiScale, blockY-3*g_dpiScale,
                    blockX+totalWidth+3*g_dpiScale, blockY+totalHeight+3*g_dpiScale);
            }
            float r = 8*g_dpiScale;
            if (SUCCEEDED(g_dc->CreateSolidColorBrush(D2D1::ColorF(0x181825, 0.75f), &fill)) &&
                SUCCEEDED(g_dc->CreateSolidColorBrush(D2D1::ColorF(0x89b4fa, 1.f), &edge))) {
                // Square on the divider side, rounded on the island side: draw the
                // rounded box, then square off its left end.
                ComPtr<ID2D1Factory> factory; g_dc->GetFactory(&factory);
                ComPtr<ID2D1PathGeometry> path;
                ComPtr<ID2D1GeometrySink> sink;
                float h = 0.5f*g_dpiScale;
                D2D1_RECT_F b = D2D1::RectF(box.left+h, box.top+h, box.right-h, box.bottom-h);
                if (factory && SUCCEEDED(factory->CreatePathGeometry(&path)) && SUCCEEDED(path->Open(&sink))) {
                    sink->BeginFigure(D2D1::Point2F(b.left, b.top), D2D1_FIGURE_BEGIN_FILLED);
                    sink->AddLine(D2D1::Point2F(b.right-r, b.top));
                    sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(b.right, b.top+r), D2D1::SizeF(r, r), 0.f,
                        D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
                    sink->AddLine(D2D1::Point2F(b.right, b.bottom-r));
                    sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(b.right-r, b.bottom), D2D1::SizeF(r, r), 0.f,
                        D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
                    sink->AddLine(D2D1::Point2F(b.left, b.bottom));
                    sink->EndFigure(D2D1_FIGURE_END_CLOSED);
                    if (SUCCEEDED(sink->Close())) {
                        g_dc->FillGeometry(path.Get(), fill.Get());
                        g_dc->DrawGeometry(path.Get(), edge.Get(), 1.f*g_dpiScale);
                    }
                }
            }
        }
        if (g_settings.shape == VizShape::Dots) {
            float dotR  = barW * 0.5f;
            float step  = barW + barGap;
            float dTL = g_settings.barRadiusTL * g_dpiScale;
            float dTR = g_settings.barRadiusTR * g_dpiScale;
            float dBR = g_settings.barRadiusBR * g_dpiScale;
            float dBL = g_settings.barRadiusBL * g_dpiScale;

            for (int i = 0; i < barCount; i++) {
                float tgt = g_vizTarget[i], cur = g_vizPeak[i];
                float nxt = cur + (tgt - cur) * ((tgt > cur) ? attack : decay);
                g_vizPeak[i] = (fabsf(nxt - cur) > 0.0005f) ? nxt : tgt;
                float fac = std::max(0.f, g_vizPeak[i]);
                float colSize = idleSize + fac * std::max(0.f, maxSize - idleSize);

                if (colSize < 0.5f) continue;

                RGBA col = c1;
                if (g_settings.colorMode == VizColorMode::Gradient ||
                    g_settings.colorMode == VizColorMode::Tourne)
                    col = LerpColor(cGrad1, c2, (barCount > 1) ? (float)i/(barCount-1) : 0.f);
                else if (g_settings.colorMode == VizColorMode::ReactiveGradient)
                    col = LerpColor(cGrad1, c2, fac);
                else if (g_settings.colorMode == VizColorMode::DynamicAlbum) {
                    float t = (barCount > 1) ? (float)i / (barCount - 1) : 0.f;
                    float freqT = std::min(1.f, t * 0.6f + fac * 0.4f);
                    col = LerpColor(cGrad1, c2, freqT);
                } else if (g_settings.colorMode == VizColorMode::RainbowCycle) {
                    float hue = fmodf(animTime * g_settings.rainbowSpeed +
                                       (barCount > 1 ? (float)i/(barCount-1) : 0.f) * 360.f, 360.f);
                    col = HSVtoRGB(hue, 0.85f, 1.0f, c1.a);
                }
                if (g_settings.colorMode == VizColorMode::Acrylic) {
                    BYTE aa = (BYTE)std::max(0, std::min(180, (int)(180.f * fac)));
                    col = {aa, c1.r, c1.g, c1.b};
                }
                if (g_settings.beatFlashEnabled) {
                    float pulse = g_beatPulse.load(std::memory_order_relaxed);
                    if (pulse > 0.001f) {
                        float blend = std::min(1.0f, pulse * (g_settings.beatFlashIntensity / 100.0f) *
                                                      (g_settings.beatFlashA / 255.0f));
                        col.r = (BYTE)(col.r + (g_settings.beatFlashR - (int)col.r) * blend);
                        col.g = (BYTE)(col.g + (g_settings.beatFlashG - (int)col.g) * blend);
                        col.b = (BYTE)(col.b + (g_settings.beatFlashB - (int)col.b) * blend);
                    }
                }
                g_barBrush->SetColor(D2D1::ColorF(col.r/255.f, col.g/255.f, col.b/255.f, col.a/255.f));

                int numDots = (step > 0.5f) ? (int)(colSize / step) : 1;
                numDots = std::max(1, numDots);

                auto drawDot = [&](float cx2, float cy2) {
                    D2D1_RECT_F r = D2D1::RectF(cx2 - dotR, cy2 - dotR, cx2 + dotR, cy2 + dotR);
                    FillRoundedRectPerCorner(g_dc.Get(), g_d2dFactory.Get(), r,
                                             g_barBrush.Get(), dTL, dTR, dBR, dBL);
                };

                for (int d = 0; d < numDots; d++) {
                    if (horizontal) {
                        float cx2 = blockX + i * step + dotR;
                        switch (g_settings.verticalAnchor) {
                            case VizAnchor::Top: {
                                float cy2 = blockY + d * step + dotR;
                                if (cy2 - dotR > blockY + maxSize) break;
                                drawDot(cx2, cy2);
                                break;
                            }
                            case VizAnchor::Middle: {
                                float centerY = blockY + maxSize * 0.5f;
                                if (d == 0) {
                                    drawDot(cx2, centerY);
                                } else {
                                    float cy2up   = centerY - d * step;
                                    float cy2down = centerY + d * step;
                                    bool upOk   = cy2up   - dotR >= blockY;
                                    bool downOk = cy2down + dotR <= blockY + maxSize;
                                    if (upOk)   drawDot(cx2, cy2up);
                                    if (downOk) drawDot(cx2, cy2down);
                                    if (!upOk && !downOk) goto next_dot_h;
                                }
                                break;
                            }
                            default: {
                                float cy2 = blockY + maxSize - d * step - dotR;
                                if (cy2 + dotR < blockY) break;
                                drawDot(cx2, cy2);
                                break;
                            }
                        }
                        continue;
                        next_dot_h: break;
                    } else {
                        float cy2 = blockY + i * step + dotR;
                        switch (g_settings.verticalAnchor) {
                            case VizAnchor::Top: {
                                float cx2 = blockX + groupExtent - d * step - dotR;
                                if (cx2 + dotR < blockX) break;
                                drawDot(cx2, cy2);
                                break;
                            }
                            case VizAnchor::Middle: {
                                float centerX = blockX + groupExtent * 0.5f;
                                if (d == 0) {
                                    drawDot(centerX, cy2);
                                } else {
                                    float cx2r = centerX + d * step;
                                    float cx2l = centerX - d * step;
                                    bool rOk = cx2r + dotR <= blockX + groupExtent;
                                    bool lOk = cx2l - dotR >= blockX;
                                    if (rOk) drawDot(cx2r, cy2);
                                    if (lOk) drawDot(cx2l, cy2);
                                    if (!rOk && !lOk) goto next_dot_v;
                                }
                                break;
                            }
                            default: {
                                float cx2 = blockX + d * step + dotR;
                                if (cx2 - dotR > blockX + groupExtent) break;
                                drawDot(cx2, cy2);
                                break;
                            }
                        }
                        continue;
                        next_dot_v: break;
                    }
                }
            }
        } else if (g_settings.shape == VizShape::Radial) {
            float centerX = blockX + totalWidth * 0.5f;
            float centerY = blockY + totalHeight * 0.5f;
            float innerR = maxSize * 0.15f;
            float strokeW = std::max(1.0f, barW);

            for (int i = 0; i < barCount; i++) {
                float tgt = g_vizTarget[i], cur = g_vizPeak[i];
                float next = cur + (tgt - cur) * ((tgt > cur) ? attack : decay);
                g_vizPeak[i] = (fabsf(next - cur) > 0.0005f) ? next : tgt;
                float fac = std::max(0.f, g_vizPeak[i]);
                float len = idleSize + fac * std::max(0.f, maxSize - idleSize);
                if (len < 0.5f) continue;

                RGBA col = c1;
                if (g_settings.colorMode == VizColorMode::Gradient ||
                    g_settings.colorMode == VizColorMode::Tourne)
                    col = LerpColor(cGrad1, c2, (barCount > 1) ? (float)i/(barCount-1) : 0.f);
                else if (g_settings.colorMode == VizColorMode::ReactiveGradient)
                    col = LerpColor(cGrad1, c2, fac);
                else if (g_settings.colorMode == VizColorMode::RainbowCycle) {
                    float hue = fmodf(animTime * g_settings.rainbowSpeed +
                                       (float)i / std::max(1, barCount) * 360.f, 360.f);
                    col = HSVtoRGB(hue, 0.85f, 1.0f, c1.a);
                }
                if (g_settings.colorMode == VizColorMode::Acrylic) {
                    BYTE aa = (BYTE)std::max(0, std::min(180, (int)(180.f * fac)));
                    col = {aa, c1.r, c1.g, c1.b};
                }
                if (g_settings.beatFlashEnabled) {
                    float pulse = g_beatPulse.load(std::memory_order_relaxed);
                    if (pulse > 0.001f) {
                        float blend = std::min(1.0f, pulse * (g_settings.beatFlashIntensity / 100.0f) *
                                                      (g_settings.beatFlashA / 255.0f));
                        col.r = (BYTE)(col.r + (g_settings.beatFlashR - (int)col.r) * blend);
                        col.g = (BYTE)(col.g + (g_settings.beatFlashG - (int)col.g) * blend);
                        col.b = (BYTE)(col.b + (g_settings.beatFlashB - (int)col.b) * blend);
                    }
                }
                g_barBrush->SetColor(D2D1::ColorF(col.r/255.f, col.g/255.f, col.b/255.f, col.a/255.f));

                float angle = (float)i / (float)barCount * 2.0f * VIZ_PI - (VIZ_PI * 0.5f);
                float dx = cosf(angle), dy = sinf(angle);
                D2D1_POINT_2F p0 = {centerX + dx * innerR, centerY + dy * innerR};
                D2D1_POINT_2F p1 = {centerX + dx * (innerR + len), centerY + dy * (innerR + len)};
                g_dc->DrawLine(p0, p1, g_barBrush.Get(), strokeW, g_roundCapStrokeStyle.Get());
            }
        } else if (g_settings.shape == VizShape::Oscilloscope) {
            // The trace sweeps along the group's LONG axis (time) and deflects
            // across its short one (amplitude), so it has to follow the
            // orientation. Vertical is the horizontal layout rotated 90 degrees
            // clockwise: the sweep runs top-to-bottom and "up" becomes "right".
            float ampScale = maxSize * 0.5f;
            float sweepLen = horizontal ? totalWidth : totalHeight;
            float center   = horizontal ? blockY + totalHeight * 0.5f
                                        : blockX + totalWidth  * 0.5f;
            float sweepOrigin = horizontal ? blockX : blockY;
            float wstep = (VIZ_WAVE_SAMPLES > 1) ? sweepLen / (float)(VIZ_WAVE_SAMPLES - 1)
                                                 : sweepLen;

            RGBA col = c1;
            if (g_settings.colorMode == VizColorMode::Gradient ||
                g_settings.colorMode == VizColorMode::Tourne)
                col = LerpColor(cGrad1, c2, 0.5f);
            else if (g_settings.colorMode == VizColorMode::RainbowCycle) {
                float hue = fmodf(animTime * g_settings.rainbowSpeed, 360.f);
                col = HSVtoRGB(hue, 0.85f, 1.0f, c1.a);
            }
            if (g_settings.oscilloscopeMultibandEnabled) {
                // Blends 3 reference colors (low/mid/high) by how much energy is
                // currently in each EQ zone, so the trace tints toward whichever
                // part of the spectrum is dominant right now. This overrides
                // whatever the color mode above picked, matching how RainbowCycle
                // and Tourne already take priority for this shape.
                float bandsSnap[VIZ_NUM_BANDS];
                ReadBands(bandsSnap);
                float lowE = 0.f, midE = 0.f, highE = 0.f;
                for (int b = 0; b < VIZ_NUM_BANDS; b++) {
                    float e = bandsSnap[b];
                    if (VIZ_BAND_EQ_ZONE[b] == 0) lowE += e;
                    else if (VIZ_BAND_EQ_ZONE[b] == 1) midE += e;
                    else highE += e;
                }
                float total = lowE + midE + highE;
                const RGBA lowCol{255, 255, 90, 60}, midCol{255, 120, 220, 90}, highCol{255, 90, 180, 255};
                if (total > 0.001f) {
                    col.r = (BYTE)((lowCol.r * lowE + midCol.r * midE + highCol.r * highE) / total);
                    col.g = (BYTE)((lowCol.g * lowE + midCol.g * midE + highCol.g * highE) / total);
                    col.b = (BYTE)((lowCol.b * lowE + midCol.b * midE + highCol.b * highE) / total);
                } else {
                    col = midCol;
                }
            }
            if (g_settings.beatFlashEnabled) {
                float pulse = g_beatPulse.load(std::memory_order_relaxed);
                if (pulse > 0.001f) {
                    float blend = std::min(1.0f, pulse * (g_settings.beatFlashIntensity / 100.0f) *
                                                  (g_settings.beatFlashA / 255.0f));
                    col.r = (BYTE)(col.r + (g_settings.beatFlashR - (int)col.r) * blend);
                    col.g = (BYTE)(col.g + (g_settings.beatFlashG - (int)col.g) * blend);
                    col.b = (BYTE)(col.b + (g_settings.beatFlashB - (int)col.b) * blend);
                }
            }
            g_barBrush->SetColor(D2D1::ColorF(col.r/255.f, col.g/255.f, col.b/255.f, col.a/255.f));

            float strokeW = std::max(1.0f, barW * 0.5f);
            float waveSnap[VIZ_WAVE_SAMPLES];
            ReadWaveform(waveSnap);
            auto wavePoint = [&](int w) -> D2D1_POINT_2F {
                float along  = sweepOrigin + w * wstep;
                float across = center + waveSnap[w] * ampScale * (horizontal ? -1.0f : 1.0f);
                return horizontal ? D2D1::Point2F(along, across)
                                  : D2D1::Point2F(across, along);
            };
            D2D1_POINT_2F prev = wavePoint(0);
            for (int w = 1; w < VIZ_WAVE_SAMPLES; w++) {
                D2D1_POINT_2F pt = wavePoint(w);
                g_dc->DrawLine(prev, pt, g_barBrush.Get(), strokeW);
                prev = pt;
            }
        }
        else {
            for (int i = 0; i < barCount; i++) {
                // Quiet noise under 3% would keep the bar bottoms flickering;
                // treat it as silence.
                float tgt = (g_vizTarget[i] < 0.03f) ? 0.f : g_vizTarget[i];
                float cur = g_vizPeak[i];
                float next;
                if (tgt > cur) {
                    next = cur + (tgt - cur) * attack;
                } else {
                    // Fall with a minimum speed so the tail of the decay does not
                    // crawl for seconds just above zero.
                    float drop = std::max((cur - tgt) * decay, 0.006f * vizFrames);
                    next = std::max(tgt, cur - drop);
                }
                g_vizPeak[i] = (fabsf(next - cur) > 0.0005f) ? next : tgt;

                float fac = std::max(0.f, g_vizPeak[i]);
                float size = idleSize + fac * std::max(0.f, maxSize - idleSize);
                // Fade bars shorter than 2 px instead of letting a one-pixel
                // sliver blink on and off.
                float sliverAlpha = std::clamp((size - idleSize) / (2.0f * g_dpiScale), 0.f, 1.f);
                if (idleSize > 0.5f) sliverAlpha = 1.f;

                RGBA col = c1;
                if (g_settings.colorMode == VizColorMode::Gradient ||
                    g_settings.colorMode == VizColorMode::Tourne) {
                    float t = (barCount > 1) ? (float)i / (barCount - 1) : 0.f;
                    col = LerpColor(cGrad1, c2, t);
                } else if (g_settings.colorMode == VizColorMode::ReactiveGradient) {
                    col = LerpColor(cGrad1, c2, fac);
                } else if (g_settings.colorMode == VizColorMode::DynamicAlbum) {
                    float t = (barCount > 1) ? (float)i / (barCount - 1) : 0.f;
                    float freqT = std::min(1.f, t * 0.6f + fac * 0.4f);
                    col = LerpColor(cGrad1, c2, freqT);
                } else if (g_settings.colorMode == VizColorMode::RainbowCycle) {
                    float t = (barCount > 1) ? (float)i / (barCount - 1) : 0.f;
                    float hue = fmodf(animTime * g_settings.rainbowSpeed + t * 360.f, 360.f);
                    col = HSVtoRGB(hue, 0.85f, 1.0f, c1.a);
                }
                if (g_settings.colorMode == VizColorMode::Acrylic) {
                    BYTE aa = (BYTE)std::max(0, std::min(180, (int)(180.f * fac)));
                    col = {aa, c1.r, c1.g, c1.b};
                }
                if (g_settings.beatFlashEnabled) {
                    float pulse = g_beatPulse.load(std::memory_order_relaxed);
                    if (pulse > 0.001f) {
                        float blend = std::min(1.0f, pulse * (g_settings.beatFlashIntensity / 100.0f) *
                                                      (g_settings.beatFlashA / 255.0f));
                        col.r = (BYTE)(col.r + (g_settings.beatFlashR - (int)col.r) * blend);
                        col.g = (BYTE)(col.g + (g_settings.beatFlashG - (int)col.g) * blend);
                        col.b = (BYTE)(col.b + (g_settings.beatFlashB - (int)col.b) * blend);
                    }
                }

                D2D1_COLOR_F d2dCol = D2D1::ColorF(col.r / 255.0f, col.g / 255.0f, col.b / 255.0f,
                                                   col.a / 255.0f * sliverAlpha);
                g_barBrush->SetColor(d2dCol);

                float holdSize = idleSize;
                if (g_settings.peakHoldEnabled) {
                    g_vizPeakHold[i] = (fac >= g_vizPeakHold[i])
                        ? fac : std::max(0.f, g_vizPeakHold[i] - 0.012f);
                    holdSize = idleSize + g_vizPeakHold[i] * std::max(0.f, maxSize - idleSize);
                } else {
                    g_vizPeakHold[i] = 0.f;
                }
                float capThickness = std::max(1.5f, 2.0f * g_dpiScale);

                D2D1_RECT_F barRect;
                if (horizontal) {
                    float x = blockX + i * (barW + barGap);
                    float y, yBottom, capY;
                    switch (g_settings.verticalAnchor) {
                        case VizAnchor::Top:
                            y = blockY;
                            yBottom = blockY + size;
                            capY = blockY + holdSize;
                            break;
                        case VizAnchor::Middle:
                            y = blockY + (maxSize - size) / 2.0f;
                            yBottom = y + size;
                            capY = blockY + (maxSize - holdSize) / 2.0f;
                            break;
                        default:
                            y = blockY + (maxSize - size);
                            yBottom = blockY + maxSize;
                            capY = blockY + (maxSize - holdSize);
                            break;
                    }
                    barRect = D2D1::RectF(x, y, x + barW, yBottom);
                    FillRoundedRectPerCorner(g_dc.Get(), g_d2dFactory.Get(), barRect,
                                             g_barBrush.Get(), rTL, rTR, rBR, rBL);
                    if (g_settings.peakHoldEnabled && holdSize > 0.5f) {
                        g_dc->FillRectangle(D2D1::RectF(x, capY - capThickness * 0.5f,
                                                        x + barW, capY + capThickness * 0.5f),
                                            g_barBrush2.Get());
                    }
                } else {
                    float y = blockY + i * (barW + barGap);
                    float x, xRight, capX;
                    switch (g_settings.verticalAnchor) {
                        case VizAnchor::Top:
                            xRight = blockX + groupExtent;
                            x = xRight - size;
                            capX = blockX + groupExtent - holdSize;
                            break;
                        case VizAnchor::Middle: {
                            float cx = blockX + groupExtent / 2.0f;
                            x = cx - size / 2.0f;
                            xRight = cx + size / 2.0f;
                            capX = cx - holdSize / 2.0f;
                            break;
                        }
                        default:
                            x = blockX;
                            xRight = blockX + size;
                            capX = blockX + holdSize;
                            break;
                    }
                    barRect = D2D1::RectF(x, y, xRight, y + barW);
                    FillRoundedRectPerCorner(g_dc.Get(), g_d2dFactory.Get(), barRect,
                                             g_barBrush.Get(), rTL, rTR, rBR, rBL);
                    if (g_settings.peakHoldEnabled && holdSize > 0.5f) {
                        g_dc->FillRectangle(D2D1::RectF(capX - capThickness * 0.5f, y,
                                                        capX + capThickness * 0.5f, y + barW),
                                            g_barBrush2.Get());
                    }
                }
            }
        }

        if (g_settings.nowPlayingEnabled && g_dwriteTextFormat && g_nowPlayingBrush) {
            ULONGLONG changedAt = g_nowPlayingChangedTick.load(std::memory_order_relaxed);
            ULONGLONG npElapsed = GetTickCount64() - changedAt;
            ULONGLONG showMs = (ULONGLONG)std::max(0, g_settings.nowPlayingDisplaySeconds) * 1000ULL;
            constexpr ULONGLONG kNpFadeMs = 800;
            float npAlpha = 0.f;
            if (changedAt != 0 && npElapsed < showMs + kNpFadeMs) {
                npAlpha = (npElapsed < showMs) ? 1.0f
                                                : 1.0f - (float)(npElapsed - showMs) / (float)kNpFadeMs;
            }
            if (npAlpha > 0.01f) {
                std::wstring displayText;
                {
                    std::lock_guard<std::mutex> lock(g_nowPlayingMutex);
                    displayText = g_nowPlayingDisplay;
                }
                if (!displayText.empty()) {
                    g_nowPlayingBrush->SetColor(D2D1::ColorF(
                        g_settings.nowPlayingR / 255.0f, g_settings.nowPlayingG / 255.0f,
                        g_settings.nowPlayingB / 255.0f, (g_settings.nowPlayingA / 255.0f) * npAlpha));
                    float npMargin = 8.0f * g_dpiScale;
                    float npHeight = (float)std::max(6, g_settings.nowPlayingFontSize) * g_dpiScale * 1.6f;
                    float npOffX = EffectiveNowPlayingOffsetX();
                    float npOffY = EffectiveNowPlayingOffsetY();
                    D2D1_RECT_F npRect = D2D1::RectF(
                        blockX - layout.textAnchorSide + npOffX,
                        blockY - npHeight - npMargin + npOffY,
                        blockX + totalWidth + layout.textAnchorSide + npOffX,
                        blockY - npMargin + npOffY);
                    TextPanelStyle npPanel{
                        g_settings.npBgA, g_settings.npBgR, g_settings.npBgG, g_settings.npBgB,
                        g_settings.npBgBorderA, g_settings.npBgBorderR,
                        g_settings.npBgBorderG, g_settings.npBgBorderB,
                        g_settings.npBgPadding, g_settings.npBgCornerRadius,
                        g_settings.npBgBorderSize};
                    DrawOverlayText(displayText.c_str(), (UINT32)displayText.length(), npRect,
                                    g_nowPlayingBrush.Get(), npPanel, npAlpha);
                }
            }
        }

        if (g_settings.peakFreqEnabled && g_dwriteTextFormat && g_nowPlayingBrush) {
            float hz = g_dominantFreqHz.load(std::memory_order_relaxed);
            if (hz > 0.f) {
                wchar_t freqText[32];
                if (hz >= 1000.f)
                    swprintf_s(freqText, L"%.1f kHz", hz / 1000.f);
                else
                    swprintf_s(freqText, L"%.0f Hz", hz);

                g_nowPlayingBrush->SetColor(D2D1::ColorF(
                    g_settings.nowPlayingR / 255.0f, g_settings.nowPlayingG / 255.0f,
                    g_settings.nowPlayingB / 255.0f, g_settings.nowPlayingA / 255.0f));
                float pfMargin = 4.0f * g_dpiScale;
                float pfHeight = (float)std::max(6, g_settings.nowPlayingFontSize) * g_dpiScale * 1.4f;
                float pfWidth  = std::min(120.0f * g_dpiScale,
                                          totalWidth + 2.0f * layout.textAnchorSide);
                float pfOffX = EffectivePeakFreqOffsetX();
                float pfOffY = EffectivePeakFreqOffsetY();

                // Horizontal placement. Left/Right hug the bar group's edges and
                // may sit slightly outside it, which the reserved side inset covers.
                float pfX;
                switch (g_settings.peakFreqAlignH) {
                    case VizTextAlignH::Left:
                        pfX = blockX - layout.textAnchorSide;
                        break;
                    case VizTextAlignH::Center:
                        pfX = blockX + (totalWidth - pfWidth) * 0.5f;
                        break;
                    default:  // Right
                        pfX = blockX + totalWidth + layout.textAnchorSide - pfWidth;
                        break;
                }
                pfX += pfOffX;

                // Vertical placement. Above/Below sit fully clear of the bars,
                // using the room reserved for them in the layout.
                float pfY;
                switch (g_settings.peakFreqAlignV) {
                    case VizTextAlignV::Above:
                        pfY = blockY - pfHeight - pfMargin;
                        break;
                    case VizTextAlignV::Middle:
                        pfY = blockY + (totalHeight - pfHeight) * 0.5f;
                        break;
                    case VizTextAlignV::Bottom:
                        pfY = blockY + totalHeight - pfHeight - pfMargin;
                        break;
                    case VizTextAlignV::Below:
                        pfY = blockY + totalHeight + pfMargin;
                        break;
                    default:  // Top
                        pfY = blockY + pfMargin;
                        break;
                }
                pfY += pfOffY;

                D2D1_RECT_F pfRect = D2D1::RectF(pfX, pfY, pfX + pfWidth, pfY + pfHeight);
                size_t freqLen = wcslen(freqText);
                TextPanelStyle pfPanel{
                    g_settings.pfBgA, g_settings.pfBgR, g_settings.pfBgG, g_settings.pfBgB,
                    g_settings.pfBgBorderA, g_settings.pfBgBorderR,
                    g_settings.pfBgBorderG, g_settings.pfBgBorderB,
                    g_settings.pfBgPadding, g_settings.pfBgCornerRadius,
                    g_settings.pfBgBorderSize};
                DrawOverlayText(freqText, (UINT32)freqLen, pfRect, g_nowPlayingBrush.Get(),
                                pfPanel, 1.0f);
            }
        }

        if (useFadeLayer) {
            g_dc->PopLayer();
        }
    }

    g_dc->EndDraw();
    // Sync interval 0. On a DirectComposition swap chain DWM owns presentation
    // timing, and the waitable timer below already paces the loop -- asking
    // Present to block for a vblank on top of that only parks the render thread.
    // Measured across 219 five-second windows: time in Present drops by a third
    // and windows where the thread parks for >8% of wall time fall from 18% to 4%.
    g_swapChain->Present(0, 0);
}

void RenderThreadProc() {
    ULONGLONG lastSuccessfulPostTick = 0;

    // Frame pacing is measured with QueryPerformanceCounter, not GetTickCount64.
    // GetTickCount64 only advances on the system timer tick (~15.625ms), so at a
    // 144 FPS target -- a 6.944ms interval -- the elapsed time could only ever
    // read 0 or ~15-16, never 6.9. The loop rendered exactly once per tick and
    // any target above ~64 FPS was silently clamped to 1 / 15.625ms = 64.0.
    LARGE_INTEGER qpcFreq;
    QueryPerformanceFrequency(&qpcFreq);
    LONGLONG lastRenderQpc = 0;

    // A high-resolution waitable timer gives sub-millisecond wait precision,
    // unlike Sleep() which is quantized to the system timer tick (~15.6ms by
    // default). This keeps frame pacing smooth at the target FPS without
    // waking the thread on every vsync the way DwmFlush() did.
    HANDLE hTimer = CreateWaitableTimerExW(nullptr, nullptr,
        CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
    if (!hTimer) {
        hTimer = CreateWaitableTimerExW(nullptr, nullptr, 0, TIMER_ALL_ACCESS);
    }

    // Takes a double: the timer's own unit is 100ns, so rounding the wait up to
    // a whole millisecond would hand back most of that precision (a 6.944ms
    // interval rounded to 7ms caps out at 142.9 FPS).
    auto preciseWait = [hTimer](double ms) {
        if (ms <= 0.0) return;
        if (hTimer) {
            LARGE_INTEGER due;
            due.QuadPart = -(LONGLONG)(ms * 10000.0);  // 100ns units, negative = relative
            if (due.QuadPart == 0) due.QuadPart = -1;
            if (SetWaitableTimer(hTimer, &due, 0, nullptr, nullptr, FALSE)) {
                WaitForSingleObject(hTimer, INFINITE);
                return;
            }
        }
        Sleep((DWORD)std::ceil(ms));
    };

    while (g_renderThreadRunning.load(std::memory_order_relaxed)) {
        HWND overlayWnd = g_overlayWnd.load(std::memory_order_relaxed);
        bool paused = g_fullscreenPaused.load(std::memory_order_relaxed);

        if (!overlayWnd || paused) {
            lastRenderQpc = 0;
            preciseWait(150);
            continue;
        }

        int fps = g_frameRate.load();
        double intervalMs = 1000.0 / (double)fps;

        int idleSeconds = g_idleDelay.load();
        if (idleSeconds > 0) {
            ULONGLONG lastAudible = g_lastAudibleTickMs.load(std::memory_order_relaxed);
            ULONGLONG idleMs = GetTickCount64() - lastAudible;
            g_slowMode = idleMs > (ULONGLONG)idleSeconds * 1000ULL;
            if (g_slowMode) intervalMs = 200.0;
        } else {
            g_slowMode = false;
        }

        // GetTickCount64 is still fine for the stuck-tick watchdog below -- that
        // compares against 1000ms, far above the tick resolution.
        ULONGLONG now = GetTickCount64();
        LARGE_INTEGER nowQpc;
        QueryPerformanceCounter(&nowQpc);
        double elapsedMs = (lastRenderQpc == 0)
            ? intervalMs
            : (double)(nowQpc.QuadPart - lastRenderQpc) * 1000.0 / (double)qpcFreq.QuadPart;
        if (elapsedMs < intervalMs) {
            preciseWait(intervalMs - elapsedMs);
            continue;
        }
        lastRenderQpc = nowQpc.QuadPart;

        if (!g_renderThreadRunning.load(std::memory_order_relaxed) || g_unloading.load())
            break;

        bool expected = false;
        if (g_renderTickPending.compare_exchange_strong(expected, true)) {
            PostMessage(overlayWnd, WM_APP_RENDER_TICK, 0, 0);
            lastSuccessfulPostTick = now;
        } else if (now - lastSuccessfulPostTick > 1000) {
            Wh_Log(L"[Viz] Render tick flag was stuck, forced a reset");
            g_renderTickPending.store(false, std::memory_order_relaxed);
            lastSuccessfulPostTick = now;
        }
    }

    if (hTimer) CloseHandle(hTimer);
}

void StartRenderThread() {
    if (g_renderThread) return;
    g_renderThreadRunning.store(true, std::memory_order_relaxed);
    g_renderThread = new std::thread(RenderThreadProc);
    HANDLE hRenderThread = g_renderThread->native_handle();
    SetThreadDescription(hRenderThread, L"TaskbarAudioVisualizer-Render");
}

void StopRenderThread() {
    g_renderThreadRunning.store(false, std::memory_order_relaxed);
    if (g_renderThread) {
        if (g_renderThread->joinable()) g_renderThread->join();
        delete g_renderThread;
        g_renderThread = nullptr;
    }
    g_renderTickPending.store(false, std::memory_order_relaxed);
}

void PauseForFullscreen() {
    if (g_fullscreenPaused.exchange(true)) return;
    Wh_Log(L"Pausing visualizer: fullscreen, hiding strip");
    StopVizCaptureThread();
    HWND overlayWnd = g_overlayWnd.load(std::memory_order_relaxed);
    if (overlayWnd) ShowWindow(overlayWnd, SW_HIDE);
    if (g_mediaWnd) ShowWindow(g_mediaWnd, SW_HIDE);
    if (g_dc && g_swapChain) {
        g_dc->BeginDraw();
        g_dc->Clear(D2D1::ColorF(0, 0, 0, 0));
        g_dc->EndDraw();
        g_swapChain->Present(1, 0);
    }
}

void ResumeFromFullscreen() {
    if (!g_fullscreenPaused.exchange(false)) return;
    Wh_Log(L"Resuming visualizer: visible again");
    StartVizCaptureThread();
    // Re-decide the auto-hide follow state while the overlay is still hidden,
    // so a bar that is currently away never flashes seated for a frame.
    UpdateTaskbarFollow();
    HWND overlayWnd = g_overlayWnd.load(std::memory_order_relaxed);
    if (overlayWnd) {
        SetWindowPos(overlayWnd, HWND_TOP, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
        RenderVisualizer();
    }
    if (g_mediaWnd && g_settings.mediaControlsEnabled &&
        !(g_mediaHiddenByCover && g_settings.mediaHideWhenCovered)) {
        RepositionAndRepaintMediaControls();
    }
}

void HandleDisplayChange() {
    HWND taskbar = MainTaskbar();
    if (!taskbar) return;
    if (g_mediaWnd) SetWindowLongPtr(g_mediaWnd, GWLP_HWNDPARENT, (LONG_PTR)taskbar);
    if (g_mediaWnd) RepositionAndRepaintMediaControls();

    if (!g_overlayWnd) return;

    // The strip is a child of the taskbar: it only needs the bar's current
    // client size, and its position follows the bar.
    RECT rc{};
    GetClientRect(taskbar, &rc);
    SetWindowPos(g_overlayWnd, HWND_TOP, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
                 SWP_NOACTIVATE);

    HMONITOR monitor = TaskbarMonitor();
    if (!monitor) monitor = MonitorFromPoint({0, 0}, MONITOR_DEFAULTTONEAREST);
    g_cachedMonitor = monitor;
    float newDpiScale = GetMonitorDpiScale(monitor);
    if (newDpiScale != g_dpiScale) {
        ReleaseSwapChainResources();
        CreateSwapChainResources();
        RenderVisualizer();
    } else {
        // Same DPI, but the work area may have moved or resized, which shifts
        // where the widget's box belongs.
        UpdateSwapChainForLayout();
        RenderVisualizer();
    }

    if (g_messageWnd && g_settings.backgroundEnabled && g_settings.bgBlur > 0) {
        SetTimer(g_messageWnd, TIMER_ID_MSG_WALLPAPER_REFRESH, 500, nullptr);
    }
}

void CreateOverlayWindow();
void DropDeadOverlayWindow();
void ApplySettingsChanged();

LRESULT CALLBACK OverlayWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_NCHITTEST: return HTTRANSPARENT;
        case WM_APP_RENDER_TICK:
            g_renderTickPending.store(false, std::memory_order_relaxed);
            if (!g_unloading && !g_fullscreenPaused.load()) {
                RenderVisualizer();
            }
            return 0;

        case WM_WINDOWPOSCHANGED: {
            const WINDOWPOS* wp = (const WINDOWPOS*)lParam;
            if (!(wp->flags & SWP_NOSIZE) && !g_unloading) {
                // The swap chain is sized to the widget, not to this window, so
                // a window resize only matters insofar as it changes where the
                // widget's box lands.
                UpdateSwapChainForLayout();
                if (!g_fullscreenPaused.load()) RenderVisualizer();
            }
            break;
        }

        case WM_DESTROY:
            ReleaseSwapChainResources();
            g_overlayWnd = nullptr;
            if (!g_unloading && g_messageWnd) {
                SetTimer(g_messageWnd, TIMER_ID_MSG_RECREATE_OVERLAY, 200, nullptr);
            }
            return 0;

        case WM_APP_CLEANUP:
            DestroyWindow(hWnd);
            return 0;

        case WM_APP_SETTINGS_CHANGED:
            ApplySettingsChanged();
            return 0;

        // A keyboard nudge changed where the box belongs. Rendering is often
        // idle while someone is placing it (no audio playing), so the move
        // would otherwise not show up until the next time music started.
        case WM_APP_FORCE_REDRAW:
            if (!g_unloading && !g_fullscreenPaused.load()) {
                RenderVisualizer();
            }
            return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


// This small input window covers only the bars. The full taskbar overlay
// remains transparent to input outside this rectangle.
// Apply topmost ordering to this thread's native popup menus while the
// capture picker is open, including both device submenus.
void RequestCaptureDeviceMenu(HWND hwnd) {
    static const UINT kShowCaptureMenuMsg = RegisterWindowMessageW(L"WindhawkFluentPlusShowCaptureMenu");
    HWND host = FindWindowExW(HWND_MESSAGE, nullptr, L"WindhawkFluentPlusMenuHost", nullptr);
    if (!host) { Wh_Log(L"Capture menu: the player's menu host is missing"); return; }
    DWORD pid = 0;
    GetWindowThreadProcessId(host, &pid);
    AllowSetForegroundWindow(pid);
    PostMessageW(host, kShowCaptureMenuMsg, reinterpret_cast<WPARAM>(hwnd), 0);
}
void ReloadCaptureEndpoint() {
    wchar_t id[512]{};
    Wh_GetStringValue(L"captureEndpointId", id, ARRAYSIZE(id));
    { std::lock_guard<std::mutex> guard(g_settingsMutex); g_audioOptions.endpointId = id; }
    g_deviceChanged.store(true);
    Wh_Log(L"Capture source selected: %s", id[0] ? id : L"configured multi-device mode");
}
LRESULT CALLBACK CapturePickerWndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp) {
    static const UINT kCaptureChangedMsg = RegisterWindowMessageW(L"WindhawkFluentPlusCaptureChanged");
    if(msg==kCaptureChangedMsg) { ReloadCaptureEndpoint(); return 0; }
    switch(msg) {
        case WM_MOUSEACTIVATE:return MA_NOACTIVATE;
        case WM_MOUSEMOVE:
            if(!g_captureHover) {
                g_captureHover=true;
                TRACKMOUSEEVENT track{sizeof(track),TME_LEAVE,hwnd,0}; TrackMouseEvent(&track);
                if(g_overlayWnd) PostMessageW(g_overlayWnd,WM_APP_FORCE_REDRAW,0,0);
            }
            return 0;
        case WM_MOUSELEAVE:
            g_captureHover=false;
            if(g_overlayWnd) PostMessageW(g_overlayWnd,WM_APP_FORCE_REDRAW,0,0);
            return 0;
        case WM_RBUTTONUP:RequestCaptureDeviceMenu(hwnd);return 0;
        case WM_CONTEXTMENU:RequestCaptureDeviceMenu(hwnd);return 0;
        case WM_PAINT: { PAINTSTRUCT ps;HDC dc=BeginPaint(hwnd,&ps); FillRect(dc,&ps.rcPaint,(HBRUSH)GetStockObject(BLACK_BRUSH));EndPaint(hwnd,&ps);return 0; }
    }
    return DefWindowProcW(hwnd,msg,wp,lp);
}
void UpdateCapturePicker() {
    if(!g_messageWnd || !g_drawRectValid.load()) return;
    if(!g_capturePickerWnd) {
        WNDCLASSW wc{}; wc.lpfnWndProc=CapturePickerWndProc; wc.hInstance=GetCurrentModuleHandle();wc.lpszClassName=L"TaskbarAudioVisualizerCapturePicker";
        wc.hCursor=LoadCursor(nullptr,IDC_ARROW);
        RegisterClassW(&wc);
        g_capturePickerWnd=CreateWindowExW(WS_EX_LAYERED|WS_EX_TOOLWINDOW|WS_EX_NOACTIVATE|WS_EX_TOPMOST,wc.lpszClassName,L"Visualizer capture device",WS_POPUP,0,0,1,1,MainTaskbar(),nullptr,wc.hInstance,nullptr);
        if(!g_capturePickerWnd) return;
        ChangeWindowMessageFilterEx(g_capturePickerWnd,RegisterWindowMessageW(L"WindhawkFluentPlusCaptureChanged"),MSGFLT_ALLOW,nullptr);
        if(!SetLayeredWindowAttributes(g_capturePickerWnd,0,1,LWA_ALPHA)) {DestroyWindow(g_capturePickerWnd);g_capturePickerWnd=nullptr;return;}
    }
    // The picker is a topmost popup, so unlike the overlay (a taskbar child) it
    // stays above a borderless game that covers the bar. There it stole the game's
    // cursor and its hover woke the hidden taskbar. Hide it whenever a game or
    // full-screen app covers the bar, whatever hideWhenFullscreen says.
    if(g_unloading || g_fullscreenPaused.load() || g_followTargetHidden || !g_overlayWnd || !IsWindowVisible(g_overlayWnd) ||
       IsFullscreenOrGameActive()) {
        ShowWindow(g_capturePickerWnd,SW_HIDE);g_captureHover=false;return;
    }
    VizLayout layout{}; RECT overlay{};
    if(!ComputeVizLayout(&layout) || !GetWindowRect(g_overlayWnd,&overlay)) return;
    int pad=(int)(3*g_dpiScale);
    D2D1_RECT_F hb;
    if(VizHoverBox(g_dpiScale,&hb)) {
        SetWindowPos(g_capturePickerWnd,HWND_TOPMOST,overlay.left+(int)hb.left,overlay.top+(int)hb.top,
            (int)(hb.right-hb.left),(int)(hb.bottom-hb.top),SWP_NOACTIVATE|SWP_SHOWWINDOW);
    } else
    SetWindowPos(g_capturePickerWnd,HWND_TOPMOST,overlay.left+(int)(layout.originX+layout.blockX)-pad,overlay.top+(int)(layout.originY+layout.blockY)-pad,
        (int)layout.totalWidth+2*pad,(int)layout.totalHeight+2*pad,
        SWP_NOACTIVATE|SWP_SHOWWINDOW);
    RECT bounds{}; POINT cursor{}; GetWindowRect(g_capturePickerWnd,&bounds); GetCursorPos(&cursor);
    bool hovered=PtInRect(&bounds,cursor)!=FALSE;
    if(hovered!=g_captureHover) {g_captureHover=hovered;PostMessageW(g_overlayWnd,WM_APP_FORCE_REDRAW,0,0);}
}

LRESULT CALLBACK MessageWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DISPLAYCHANGE:
            if (!g_unloading) {
                SetTimer(hWnd, TIMER_ID_MSG_DISPLAY_CHANGE, 200, nullptr);
            }
            return 0;

        case WM_SETTINGCHANGE: {
            RefreshAccentColorCache();

            if (g_overlayWnd && !g_unloading && g_settings.backgroundEnabled &&
                g_settings.bgBlur > 0) {
                FILETIME ft = GetWallpaperFileTime();
                if (CompareFileTime(&ft, &g_lastWallpaperTime) != 0) {
                    SetTimer(hWnd, TIMER_ID_MSG_WALLPAPER_REFRESH, 2000, nullptr);
                }
            }
            return 0;
        }

        case WM_DWMCOLORIZATIONCOLORCHANGED:
            RefreshAccentColorCache();
            return 0;

        // Key repeat can fire dozens of nudges a second, so restart a short
        // timer instead and write once the user stops moving. SetTimer with an
        // existing id re-arms it.
        case WM_APP_REQUEST_SAVE_POSITION:
            if (!g_unloading) {
                SetTimer(hWnd, TIMER_ID_MSG_SAVE_POSITION, 700, nullptr);
            }
            return 0;

        case WM_APP + 202:
            if (!g_unloading) {
                // Foreground change or a taskbar location change: the shell
                // re-decides the auto-hide bar's state on exactly these
                // events, so the strip must too. Deciding here instead of
                // waiting for the 100 ms tick is what keeps the slide in
                // step with the bar on alt-tab and Win-key transitions.
                UpdateTaskbarFollow();
                if (!g_overlayWnd) CreateOverlayWindow();
                HandleDisplayChange();
            }
            return 0;
        case WM_TIMER:
            if(wParam==0xCA71) {
                UpdateTaskbarFollow();
                DropDeadOverlayWindow();
                // Self-heal: a lost overlay window (explorer restart killed
                // its owner, a wedged earlier unload destroyed it, a
                // transient init failure) must not leave the strip gone
                // until the user happens to click the taskbar. Recreate it
                // here, gated the same way as the fullscreen pause so the
                // strip is never flashed up just to be hidden again.
                if (!g_overlayWnd) {
                    if (g_debugLogging.load(std::memory_order_relaxed))
                        Wh_Log(L"[Heal] overlay missing: unloading=%d paused=%d fullscreenActive=%d",
                               (int)g_unloading.load(), (int)g_fullscreenPaused.load(),
                               (int)IsFullscreenPauseConditionActive());
                    if (!g_unloading && !g_fullscreenPaused.load() &&
                        !IsFullscreenPauseConditionActive())
                        CreateOverlayWindow();
                }
                UpdateCapturePicker();
                return 0;
            }
            if (g_unloading) return 0;
            if (wParam == TIMER_ID_MSG_DISPLAY_CHANGE) {
                KillTimer(hWnd, TIMER_ID_MSG_DISPLAY_CHANGE);
                HandleDisplayChange();
            } else if (wParam == TIMER_ID_MSG_RECREATE_OVERLAY) {
                KillTimer(hWnd, TIMER_ID_MSG_RECREATE_OVERLAY);
                CreateOverlayWindow();
                // Running as our own process now (see the tool-mod boilerplate at
                // the end of this file), there's no explorer-side hook to tell us
                // the moment WorkerW becomes available -- keep polling for it
                // instead of giving up after a single attempt.
                if (!g_overlayWnd && !g_unloading) {
                    SetTimer(hWnd, TIMER_ID_MSG_RECREATE_OVERLAY, 1000, nullptr);
                }
            } else if (wParam == TIMER_ID_MSG_WALLPAPER_REFRESH) {
                KillTimer(hWnd, TIMER_ID_MSG_WALLPAPER_REFRESH);
                if (g_overlayWnd && g_settings.backgroundEnabled && g_settings.bgBlur > 0) {
                    ReleaseVisualResources();
                    RecreateVisualResources();
                    if (!g_fullscreenPaused.load()) RenderVisualizer();
                }
            } else if (wParam == TIMER_ID_MSG_SAVE_POSITION) {
                KillTimer(hWnd, TIMER_ID_MSG_SAVE_POSITION);
                PersistOverrideState();
            } else if (wParam == TIMER_ID_MSG_FONT_RECHECK) {
                // Re-run the font lookup that failed during settings load. A
                // cold boot resolves this within a few seconds; a name that is
                // actually wrong never will, and gets reported once the
                // attempts run out.
                if (!g_fontCheckPending || !g_settings.nowPlayingEnabled) {
                    g_fontCheckPending = false;
                    KillTimer(hWnd, TIMER_ID_MSG_FONT_RECHECK);
                } else if (IsFontInstalled(g_settings.nowPlayingFont)) {
                    Wh_Log(L"Now Playing Font resolved after %d s, no issue to report",
                           g_fontCheckAttempts + 1);
                    g_fontCheckPending = false;
                    KillTimer(hWnd, TIMER_ID_MSG_FONT_RECHECK);
                } else if (++g_fontCheckAttempts >= FONT_CHECK_MAX_ATTEMPTS) {
                    g_fontCheckPending = false;
                    KillTimer(hWnd, TIMER_ID_MSG_FONT_RECHECK);
                    ReportSettingIssue(
                        L"Appearance", L"Now Playing Font", g_settings.nowPlayingFont.c_str(),
                        L"the name of a font installed on this PC, exactly as Windows spells it",
                        L"whatever Windows substitutes (usually Segoe UI)");
                    // ReportSettingIssue only queues the line. LoadSettings
                    // normally flushes at its end, but this report happens long
                    // after that has returned, so without flushing here the
                    // warning would sit in the vector until the next settings
                    // change cleared it unseen. Safe from this thread: the flush
                    // honours showSettingsErrors and puts the dialog on a thread
                    // of its own.
                    FlushSettingsIssues();
                }
            } else if (wParam == TIMER_ID_MSG_FULLSCREEN_WATCH) {
                // Fullscreen (or a missing taskbar, or a borderless game
                // still covering the monitor after an alt-tab away) hides
                // every piece of this mod: the bars live on the taskbar, so
                // when a borderless game covers it they must go too. The
                // shared predicate includes the wider cover signal, so the
                // strip leaves and returns with the bar in both directions.
                // Computed once per tick and shared by the media self-heal
                // below and the pause decision after it, so the heal never
                // fights the hide by re-showing the strip.
                bool fullscreenHide = IsFullscreenPauseConditionActive();
                // The media strip is a plain layered window living alongside
                // whatever else is topmost, and it's the one piece of this mod
                // that has to survive in that crowd -- another app taking
                // topmost, or the window going away with the shell, would
                // otherwise leave it gone with nothing to bring it back. This
                // quarter-second check is cheap and makes it self-healing.
                if (g_settings.mediaControlsEnabled) {
                    if (!g_mediaWnd) {
                        if (!fullscreenHide) {
                            Wh_Log(L"[Media] window missing, recreating");
                            CreateMediaControlWindow();
                        }
                    } else if (fullscreenHide) {
                        if (IsWindowVisible(g_mediaWnd)) {
                            Wh_Log(L"[Media] fullscreen, hiding strip");
                            ShowWindow(g_mediaWnd, SW_HIDE);
                        }
                    } else {
                        if (g_settings.mediaHideWhenCovered) {
                            // Measured against the strip's own rect on the same
                            // timer as the visualizer's occlusion check, for the
                            // same reason: EnumWindows is far too heavy to run
                            // any more often than this.
                            bool covered = IsMediaStripCovered();
                            if (covered && !g_mediaHiddenByCover) {
                                Wh_Log(L"[Media] covered, hiding strip");
                                g_mediaHiddenByCover = true;
                                ShowWindow(g_mediaWnd, SW_HIDE);
                            } else if (!covered && g_mediaHiddenByCover) {
                                Wh_Log(L"[Media] uncovered, showing strip");
                                g_mediaHiddenByCover = false;
                                RepositionAndRepaintMediaControls();
                            }
                        } else if (g_mediaHiddenByCover) {
                            // The setting was turned off while the strip was
                            // parked out of the way.
                            g_mediaHiddenByCover = false;
                            RepositionAndRepaintMediaControls();
                        }

                        // Still worth re-asserting even with Hide When Covered
                        // on -- that only accounts for the times we hid it
                        // ourselves, not for another app taking topmost.
                        if (!g_mediaHiddenByCover &&
                            (!IsWindowVisible(g_mediaWnd) ||
                             !(GetWindowLongPtr(g_mediaWnd, GWL_EXSTYLE) & WS_EX_TOPMOST))) {
                            Wh_Log(L"[Media] window not visible/topmost, re-asserting");
                            RepositionAndRepaintMediaControls();
                        }
                    }
                }

                // Windows created on the taskbar later land above the strip among
                // its child windows. Keep the strip on top of its siblings.
                if (g_overlayWnd && GetWindow(g_overlayWnd, GW_HWNDPREV)) {
                    SetWindowPos(g_overlayWnd, HWND_TOP, 0, 0, 0, 0,
                                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                }

                bool shouldPause = fullscreenHide;

                // Diagnostic visibility into the occlusion decision: the draw
                // rect, the measured coverage and the pause state, once a
                // second while diagnostic logging is on.
                if (g_debugLogging.load(std::memory_order_relaxed)) {
                    static unsigned s_watchLogCounter = 0;
                    if ((++s_watchLogCounter & 0x03) == 0) {
                        RECT vr{g_drawRectL.load(std::memory_order_relaxed),
                                g_drawRectT.load(std::memory_order_relaxed),
                                g_drawRectR.load(std::memory_order_relaxed),
                                g_drawRectB.load(std::memory_order_relaxed)};
                        int cov = ComputeRectCoveragePercent(vr, true);
                        Wh_Log(L"[Viz] watch: drawRect=(%ld,%ld,%ld,%ld) covered=%d%% paused=%d valid=%d",
                               vr.left, vr.top, vr.right, vr.bottom, cov,
                               (int)g_fullscreenPaused.load(),
                               (int)g_drawRectValid.load(std::memory_order_relaxed));
                    }
                }

                // Occlusion is evaluated on this same 1s timer rather than per
                // frame -- EnumWindows is far too heavy to run at frame rate,
                // and a second of latency on hide/show is imperceptible.
                if (!shouldPause && g_settings.pauseWhenObscured && IsVisualizerOccluded())
                    shouldPause = true;

                if (shouldPause) {
                    PauseForFullscreen();
                } else {
                    ResumeFromFullscreen();
                }
            }
            return 0;

        case WM_APP_SETTINGS_CHANGED:
            ApplySettingsChanged();
            return 0;

        case WM_DESTROY:
            g_messageWnd = nullptr;
            return 0;

        case WM_APP_CLEANUP:
            DestroyWindow(hWnd);
            return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool g_overlayClassRegistered = false;

bool RegisterOverlayWindowClass() {
    if (g_overlayClassRegistered) return true;
    WNDCLASS wc = {};
    wc.lpfnWndProc = OverlayWndProc;
    wc.hInstance = GetCurrentModuleHandle();
    wc.lpszClassName = OVERLAY_WINDOW_CLASS;
    if (!RegisterClass(&wc)) return false;
    g_overlayClassRegistered = true;
    return true;
}

void UnregisterOverlayWindowClass() {
    if (g_overlayClassRegistered) {
        UnregisterClass(OVERLAY_WINDOW_CLASS, GetCurrentModuleHandle());
        g_overlayClassRegistered = false;
    }
}

bool EnsureLazyInitialized() {
    if (g_initSucceeded.load(std::memory_order_relaxed)) return true;

    // A one-shot latch would make a single failure permanent: the overlay
    // could then never be created again in this process, and the strip would
    // stay gone until the next full mod reload. Retry instead, throttled to
    // one attempt per 5 s so a persistently broken device (driver reset, GPU
    // gone) does not spin device creation on every 100 ms tick.
    ULONGLONG now = GetTickCount64();
    ULONGLONG last = g_lastInitAttempt.load(std::memory_order_relaxed);
    if (last && now - last < 5000) return false;
    if (!g_lastInitAttempt.compare_exchange_strong(last, now,
            std::memory_order_relaxed)) return false;

    if (!InitDirectX()) {
        Wh_Log(L"InitDirectX failed");
        return false;
    }

    if (!IsFullscreenPauseConditionActive()) {
        StartVizCaptureThread();
    } else {
        Wh_Log(L"Fullscreen active at startup, starting paused");
        g_fullscreenPaused.store(true);
    }

    StartRenderThread();

    g_initSucceeded = true;
    return true;
}


// The strip is a child of the taskbar. When Explorer dies, the strip dies with it,
// but its WM_DESTROY does not always reach us, which left a dead handle behind and
// blocked every rebuild. Forget a handle that no longer names a window.
void DropDeadOverlayWindow() {
    HWND overlayWnd = g_overlayWnd.load(std::memory_order_relaxed);
    if (overlayWnd && !IsWindow(overlayWnd)) {
        Wh_Log(L"[Heal] overlay handle is dead, rebuilding");
        ReleaseSwapChainResources();
        g_overlayWnd = nullptr;
    }
}

void CreateOverlayWindow() {
    DropDeadOverlayWindow();
    if (g_overlayWnd || !MainTaskbar()) {
        if (g_debugLogging.load(std::memory_order_relaxed))
            Wh_Log(L"[Overlay] create skipped: present=%d taskbar=%p overlay=%p",
                   (int)(bool)g_overlayWnd, (void*)MainTaskbar(),
                   (void*)g_overlayWnd.load(std::memory_order_relaxed));
        return;
    }
    if (!EnsureLazyInitialized() || !RegisterOverlayWindowClass()) {
        Wh_Log(L"[Overlay] create skipped: init=%d class=%d",
               (int)g_initSucceeded.load(std::memory_order_relaxed),
               (int)g_overlayClassRegistered);
        return;
    }
    // A child of the taskbar, not a topmost popup. The strip then sits in the
    // taskbar's own z-order: whatever covers the taskbar (a fullscreen game, a
    // window above the bar) covers the strip too, and the bar's auto-hide
    // slide carries it along. A topmost popup stayed above those windows.
    RECT rc{};
    GetClientRect(MainTaskbar(), &rc);
    g_overlayWnd = CreateWindowExW(
        WS_EX_NOREDIRECTIONBITMAP | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE |
        WS_EX_TOOLWINDOW, OVERLAY_WINDOW_CLASS,
        nullptr, WS_CHILD, 0, 0, rc.right-rc.left, rc.bottom-rc.top,
        MainTaskbar(), nullptr, GetCurrentModuleHandle(), nullptr);
    Wh_Log(L"Taskbar overlay created=%p rect=%ld,%ld,%ld,%ld error=%lu",
           (void*)g_overlayWnd.load(), rc.left, rc.top, rc.right, rc.bottom, GetLastError());
    if (!g_overlayWnd) return;
    if (!SetLayeredWindowAttributes(g_overlayWnd, 0, 255, LWA_ALPHA)) {
        Wh_Log(L"Overlay input transparency failed, error=%lu", GetLastError());
        DestroyWindow(g_overlayWnd);
        g_overlayWnd = nullptr;
        return;
    }
    g_renderTickPending.store(false);
    if (!g_gsmtcStarted) { InitGsmtcListener(); g_gsmtcStarted = true; }
    bool ok = CreateSwapChainResources();
    Wh_Log(L"Composition initialized=%d", ok);
    if (ok) {
        // Decide the auto-hide follow state before the first paint, so a
        // strip created into a hidden bar starts slid out instead of
        // flashing seated for a frame.
        UpdateTaskbarFollow();
        RenderVisualizer();
        SetWindowPos(g_overlayWnd, HWND_TOP, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    }
}

bool g_messageClassRegistered = false;

bool RegisterMessageWindowClass() {
    if (g_messageClassRegistered) return true;
    WNDCLASS wc = {};
    wc.lpfnWndProc = MessageWndProc;
    wc.hInstance = GetCurrentModuleHandle();
    wc.lpszClassName = MESSAGE_WINDOW_CLASS;
    if (!RegisterClass(&wc)) return false;
    g_messageClassRegistered = true;
    return true;
}

void UnregisterMessageWindowClass() {
    if (g_messageClassRegistered) {
        UnregisterClass(MESSAGE_WINDOW_CLASS, GetCurrentModuleHandle());
        g_messageClassRegistered = false;
    }
}

void CreateMessageWindow() {
    if (g_messageWnd) return;
    if (!RegisterMessageWindowClass()) return;

    HINSTANCE hInstance = GetCurrentModuleHandle();
    g_messageWnd = CreateWindowEx(0, MESSAGE_WINDOW_CLASS, nullptr, 0, 0, 0, 0, 0, nullptr,
                                  nullptr, hInstance, nullptr);
    if (g_messageWnd) {
        SetTimer(g_messageWnd, TIMER_ID_MSG_FULLSCREEN_WATCH, 250, nullptr);
        SetTimer(g_messageWnd,0xCA71,100,nullptr);
        // Settings are loaded before this window exists on the init path, so a
        // font check that already failed has nowhere to arm its retry until now.
        if (g_fontCheckPending) {
            SetTimer(g_messageWnd, TIMER_ID_MSG_FONT_RECHECK, 1000, nullptr);
        }
    }
}

void LoadSettings() {
    std::lock_guard<std::mutex> guard(g_settingsMutex);
    g_settingsIssues.clear();
    g_settings = Settings{};
    g_settings.showSettingsErrors = false;
    g_settings.keyMoveEnabled = false;
    g_settings.dragEnabled = false;
    g_settings.pauseOnFullscreen = VizIntSetting(L"performance.hideWhenFullscreen") != 0;
    {
        PCWSTR placement = VizStringSetting(L"position.placement");
        g_placementOverlay = placement && wcscmp(placement, L"overlay") == 0;
        Wh_FreeStringSetting(placement);
    }
    g_settings.followTaskbarAutoHide = VizIntSetting(L"performance.followTaskbarAutoHide") != 0;
    g_settings.pauseWhenObscured = VizIntSetting(L"performance.pauseWhenObscured") != 0;
    g_settings.autoHideEnabled = false;
    g_settings.mediaHideWhenCovered = false;
    auto number=[](PCWSTR name,int lo,int hi) { return std::clamp(VizIntSetting(name),lo,hi); };
    auto text=[](PCWSTR name) { PCWSTR p=VizStringSetting(name); std::wstring result=p?p:L""; Wh_FreeStringSetting(p); return result; };
    g_taskbarOffset = number(L"position.taskbarOffset",0,16000);
    g_taskbarVerticalOffset = number(L"position.verticalOffset",-128,128);
    g_mediaGap = number(L"media_controls.gap",0,200);
    std::wstring shape=text(L"appearance.shape");
    g_settings.shape=shape==L"mountain"?VizShape::Mountain:shape==L"mirror"?VizShape::Mirror:
        shape==L"wave"?VizShape::Wave:shape==L"breathe"?VizShape::Breathe:shape==L"dots"?VizShape::Dots:VizShape::Stereo;
    g_settings.barCount=number(L"appearance.barCount",1,128);
    g_settings.barWidth=number(L"appearance.barWidth",1,24);
    g_settings.barGap=number(L"appearance.barGap",0,24);
    g_settings.barMaxSize=number(L"appearance.barMaxSize",2,128);
    g_settings.barIdleSize=number(L"appearance.barIdleSize",0,g_settings.barMaxSize);
    float quad[4];
    ReadQuadSetting(L"appearance.barCornerRadius",L"Appearance",L"Bar corner radius",L"top-left, top-right, bottom-right, bottom-left",1.f,false,quad);
    g_settings.barRadiusTL=quad[0]; g_settings.barRadiusTR=quad[1];
    g_settings.barRadiusBR=quad[2]; g_settings.barRadiusBL=quad[3];
    std::wstring anchor=text(L"appearance.verticalAnchor");
    g_settings.verticalAnchor=anchor==L"top"?VizAnchor::Top:anchor==L"middle"?VizAnchor::Middle:VizAnchor::Bottom;
    std::wstring color=text(L"appearance.colorMode");
    g_settings.colorMode=color==L"gradient"?VizColorMode::Gradient:color==L"reactive_gradient"?VizColorMode::ReactiveGradient:
        color==L"accent"?VizColorMode::Accent:color==L"rainbow"?VizColorMode::RainbowCycle:VizColorMode::Solid;
    ReadColorSetting(L"appearance.color",L"Appearance",L"Solid color",255,203,166,247,&g_settings.colorA,&g_settings.colorR,&g_settings.colorG,&g_settings.colorB);
    ReadColorSetting(L"appearance.gradientColor1",L"Appearance",L"Gradient start",255,203,166,247,&g_settings.grad1A,&g_settings.grad1R,&g_settings.grad1G,&g_settings.grad1B);
    ReadColorSetting(L"appearance.gradientColor2",L"Appearance",L"Gradient end",255,137,180,250,&g_settings.grad2A,&g_settings.grad2R,&g_settings.grad2G,&g_settings.grad2B);
    g_settings.rainbowSpeed=number(L"appearance.rainbowSpeed",1,300);
    g_settings.sensitivity=number(L"appearance.sensitivity",0,300);
    std::wstring curve=text(L"appearance.sensitivityCurve");
    g_settings.sensitivityCurve=curve==L"exponential"?VizSensitivityCurve::Exponential:curve==L"power"?VizSensitivityCurve::Power:VizSensitivityCurve::Knee;
    g_settings.smoothing=number(L"appearance.smoothing",0,100);
    std::wstring eq=text(L"appearance.eqPreset");
    g_settings.eq=eq==L"bass"?VizEQ::Bass:eq==L"rock"?VizEQ::Rock:eq==L"pop"?VizEQ::Pop:
        eq==L"jazz"?VizEQ::Jazz:eq==L"electronic"?VizEQ::Electronic:VizEQ::Default;
    int fft=_wtoi(text(L"appearance.fftSize").c_str());
    g_settings.fftSize=(fft==1024||fft==2048||fft==4096||fft==8192)?fft:1024;
    std::wstring scale=text(L"appearance.freqScale");
    g_settings.freqScale=scale==L"linear"?VizFreqScale::Linear:scale==L"mel"?VizFreqScale::Mel:VizFreqScale::Log;
    g_settings.peakHoldEnabled=VizIntSetting(L"appearance.peakHoldEnabled")!=0;
    ReadColorSetting(L"appearance.peakHoldColor",L"Appearance",L"Peak cap color",255,137,180,250,&g_settings.peakHoldA,&g_settings.peakHoldR,&g_settings.peakHoldG,&g_settings.peakHoldB);
    AudioOptions audio;
    audio.defaultOnly=text(L"audio.captureMode")==L"default";
    audio.hardwareLoopbacks=VizIntSetting(L"audio.hardwareLoopbacks")!=0;
    audio.filter=Lowercase(text(L"audio.deviceFilter"));
    wchar_t selectedEndpoint[4096]{};
    Wh_GetStringValue(L"captureEndpointId", selectedEndpoint, ARRAYSIZE(selectedEndpoint));
    audio.endpointId=selectedEndpoint;
    if(audio.defaultOnly!=g_audioOptions.defaultOnly || audio.hardwareLoopbacks!=g_audioOptions.hardwareLoopbacks || audio.filter!=g_audioOptions.filter || audio.endpointId!=g_audioOptions.endpointId) g_deviceChanged.store(true);
    g_audioOptions=audio;
    g_settings.inputGainDb=(float)number(L"audio.inputGain",-24,24);
    g_settings.backgroundEnabled=VizIntSetting(L"background.enabled")!=0;
    ReadColorSetting(L"background.color",L"Background",L"Panel color",128,30,30,46,&g_settings.bgA,&g_settings.bgR,&g_settings.bgG,&g_settings.bgB);
    ReadQuadSetting(L"background.padding",L"Background",L"Panel padding",L"left, right, top, bottom",4.f,false,quad);
    g_settings.bgPaddingL=(int)std::clamp(quad[0],0.f,12.f); g_settings.bgPaddingR=(int)std::clamp(quad[1],0.f,12.f);
    g_settings.bgPaddingT=(int)std::clamp(quad[2],0.f,12.f); g_settings.bgPaddingB=(int)std::clamp(quad[3],0.f,12.f);
    ReadQuadSetting(L"background.cornerRadius",L"Background",L"Panel corner radius",L"top-left, top-right, bottom-right, bottom-left",6.f,false,quad);
    g_settings.bgRadiusTL=quad[0]; g_settings.bgRadiusTR=quad[1]; g_settings.bgRadiusBR=quad[2]; g_settings.bgRadiusBL=quad[3];
    g_settings.bgBlur=0;
    g_settings.bgBorderSize=number(L"background.borderSize",0,8);
    ReadColorSetting(L"background.borderColor",L"Background",L"Panel border color",255,69,71,90,&g_settings.borderA,&g_settings.borderR,&g_settings.borderG,&g_settings.borderB);
    g_settings.mediaControlsEnabled=VizIntSetting(L"media_controls.enabled")!=0;
    g_settings.mediaIconSize=number(L"media_controls.iconSize",8,32);
    g_settings.mediaIconSpacing=number(L"media_controls.iconSpacing",0,64);
    ReadColorSetting(L"media_controls.iconColor",L"Media controls",L"Button color",255,205,214,244,&g_settings.mediaIconColorA,&g_settings.mediaIconColorR,&g_settings.mediaIconColorG,&g_settings.mediaIconColorB);
    g_settings.mediaIconPrevPath=ReadIconPathSetting(L"media_controls.iconPrevPath",L"Media controls",L"Previous image");
    g_settings.mediaIconPlayPath=ReadIconPathSetting(L"media_controls.iconPlayPath",L"Media controls",L"Play image");
    g_settings.mediaIconPausePath=ReadIconPathSetting(L"media_controls.iconPausePath",L"Media controls",L"Pause image");
    g_settings.mediaIconNextPath=ReadIconPathSetting(L"media_controls.iconNextPath",L"Media controls",L"Next image");
    ReadColorSetting(L"media_controls.plateColor",L"Media controls",L"Button panel color",0,0,0,0,&g_settings.mediaPlateA,&g_settings.mediaPlateR,&g_settings.mediaPlateG,&g_settings.mediaPlateB);
    g_settings.mediaPlatePadding=number(L"media_controls.platePadding",0,8);
    g_settings.mediaPlateCornerRadius=number(L"media_controls.plateCornerRadius",0,16);
    RECT rc{};
    if(GetWindowRect(MainTaskbar(),&rc)) {
        float dpi=GetMonitorDpiScale(TaskbarMonitor());
        int logicalHeight=std::max(8,(int)((rc.bottom-rc.top)/dpi));
        int padding=g_settings.backgroundEnabled?g_settings.bgPaddingT+g_settings.bgPaddingB:0;
        g_settings.barMaxSize=std::min(g_settings.barMaxSize,std::max(2,logicalHeight-padding-8));
        g_settings.barIdleSize=std::min(g_settings.barIdleSize,g_settings.barMaxSize);
        g_settings.mediaIconSize=std::min(g_settings.mediaIconSize,std::max(8,logicalHeight-2*g_settings.mediaPlatePadding));
        int mediaWidth=g_settings.mediaControlsEnabled?g_mediaGap+3*g_settings.mediaIconSize+2*g_settings.mediaIconSpacing+2*g_settings.mediaPlatePadding:0;
        int logicalWidth=(int)((rc.right-rc.left)/dpi);
        int usable=std::max(1,logicalWidth-mediaWidth-16);
        g_settings.barCount=std::min(g_settings.barCount,std::max(1,(usable+g_settings.barGap)/(g_settings.barWidth+g_settings.barGap)));
    }
    g_settings.targetFps=number(L"performance.targetFps",10,120);
    g_settings.pauseWhenSilentSeconds=number(L"performance.pauseWhenSilentSeconds",0,3600);
    g_frameRate.store(g_settings.targetFps); g_idleDelay.store(g_settings.pauseWhenSilentSeconds);
    g_debugLogging.store(VizIntSetting(L"diagnostics.enabled")!=0);
    Wh_Log(L"Settings offset=%d vertical=%d bars=%d width=%d gap=%d height=%d media=%d fps=%d hideFullscreen=%d followAutoHide=%d obscured=%d",
        g_taskbarOffset,g_taskbarVerticalOffset,g_settings.barCount,g_settings.barWidth,g_settings.barGap,g_settings.barMaxSize,g_settings.mediaControlsEnabled,g_settings.targetFps,(int)g_settings.pauseOnFullscreen,(int)g_settings.followTaskbarAutoHide,(int)g_settings.pauseWhenObscured);
    Wh_Log(L"Audio selection defaultOnly=%d hardwareLoopbacks=%d filter=%s gain=%.1f",audio.defaultOnly,audio.hardwareLoopbacks,audio.filter.c_str(),g_settings.inputGainDb);
}


HANDLE g_uiThread = nullptr;
DWORD g_uiThreadId = 0;

DWORD WINAPI UiThreadProc(LPVOID) {
    // This mod runs as its own dedicated process (see the tool-mod boilerplate
    // at the end of this file). WhTool_ModInit's own calling thread does not
    // survive -- the tool-mod launcher hooks the process's real entry point
    // and exits that thread once startup continues past mod init -- so every
    // window, and the message loop that keeps them alive, has to live on a
    // thread we spin up and own ourselves rather than whatever thread called
    // WhTool_ModInit.
    // Apartment-threaded, because this thread owns windows and pumps messages.
    // Without this, every CoCreateInstance made from here fails outright with
    // CO_E_NOTINITIALIZED -- which is why custom Media Controls icon paths
    // never loaded: WIC's imaging factory is created on this thread, silently
    // failed to activate, and fell back to the built-in glyph every time.
    HRESULT comHr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(comHr)) {
        Wh_Log(L"CoInitializeEx on UI thread failed, hr=0x%08X", comHr);
    }

    // Desktop keyboard-position overrides do not apply to the taskbar mod.

    CreateMessageWindow();
    CreateMediaControlWindow();
    CreateOverlayWindow();
    if (!g_overlayWnd && g_messageWnd) {
        SetTimer(g_messageWnd, TIMER_ID_MSG_RECREATE_OVERLAY, 1000, nullptr);
    }

    InstallTaskbarEvents();

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (SUCCEEDED(comHr)) CoUninitialize();
    return 0;
}

BOOL WhTool_ModInit() {
    Wh_Log(L">");

    // Running injected into explorer.exe, this was inherited for free -- the
    // shell process is always Per-Monitor-V2 DPI aware. Running as our own
    // standalone process now, nothing declares that for us, so without this
    // call every GetMonitorInfo/GetDpiForMonitor-based position and size
    // calculation in the mod (the visualizer's own box, and the media
    // controls window) risks running against a DPI-virtualized view of the
    // desktop instead of true physical pixels on any scaled monitor.
    if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
        Wh_Log(L"SetProcessDpiAwarenessContext failed, error %u", GetLastError());
    }

    LoadSettings();

    RefreshAccentColorCache();

    g_uiThread = CreateThread(nullptr, 0, UiThreadProc, nullptr, 0, &g_uiThreadId);
    return g_uiThread != nullptr;
}

void WhTool_ModUninit() {
    Wh_Log(L">");

    g_unloading = true;

    StopRenderThread();

    if (g_overlayWnd) SendMessage(g_overlayWnd, WM_APP_CLEANUP, 0, 0);
    if(g_capturePickerWnd) { SendMessageW(g_capturePickerWnd,WM_CLOSE,0,0);g_capturePickerWnd=nullptr; }
    if (g_messageWnd) SendMessage(g_messageWnd, WM_APP_CLEANUP, 0, 0);
    if (g_mediaWnd) SendMessage(g_mediaWnd, WM_APP_CLEANUP, 0, 0);

    UnregisterOverlayWindowClass();
    UnregisterMessageWindowClass();
    UnregisterMediaWindowClass();

    StopVizCaptureThread();
    UninitDirectX();

    if (g_gsmtcStopEvent) {
        SetEvent(g_gsmtcStopEvent);
    }
    if (g_gsmtcThread && g_gsmtcThread->joinable()) {
        g_gsmtcThread->join();
    }
    g_gsmtcThread.reset();
    if (g_gsmtcStopEvent) {
        CloseHandle(g_gsmtcStopEvent);
        g_gsmtcStopEvent = nullptr;
    }

    if (g_albumArtThread) {
        if (g_albumArtThread->joinable()) {
            HANDLE hThread = g_albumArtThread->native_handle();
            if (WaitForSingleObject(hThread, 3000) == WAIT_OBJECT_0) {
                g_albumArtThread->join();
            } else {
                g_albumArtThread->detach();
            }
        }
        delete g_albumArtThread;
        g_albumArtThread = nullptr;
    }

    if (g_mediaCmdThread) {
        if (g_mediaCmdThread->joinable()) {
            HANDLE hThread = g_mediaCmdThread->native_handle();
            if (WaitForSingleObject(hThread, 3000) == WAIT_OBJECT_0) {
                g_mediaCmdThread->join();
            } else {
                g_mediaCmdThread->detach();
            }
        }
        delete g_mediaCmdThread;
        g_mediaCmdThread = nullptr;
    }

    g_gsmtcStarted = false;

    RemoveTaskbarEvents();

    if (g_uiThreadId) {
        PostThreadMessage(g_uiThreadId, WM_QUIT, 0, 0);
    }
    if (g_uiThread) {
        WaitForSingleObject(g_uiThread, 3000);
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
    }
}

void ApplySettingsChanged() {
    Wh_Log(L">");

    int oldMonitor = g_settings.monitor;
    VizColorMode oldColorMode = g_settings.colorMode;

    LoadSettings();

    // Creation at startup can fail (or the window can have been destroyed
    // since), and until now nothing retried -- turning Media Controls on in
    // settings then looked like it did nothing at all.
    if (!g_mediaWnd) {
        CreateMediaControlWindow();
    } else {
        // Cleared unconditionally so that turning Hide When Covered off, or
        // moving the strip somewhere clear, brings it straight back instead of
        // waiting for the next watch tick to notice.
        g_mediaHiddenByCover = false;
        RecreateMediaControlResources();
        RepositionAndRepaintMediaControls();
    }

    if ((g_settings.colorMode == VizColorMode::AlbumArt ||
         g_settings.colorMode == VizColorMode::DynamicAlbum) &&
        ((oldColorMode != VizColorMode::AlbumArt &&
          oldColorMode != VizColorMode::DynamicAlbum) || !g_albumArtColorReady.load()))
        FetchAlbumArtColorAsync();
    else if (g_settings.nowPlayingEnabled)
        FetchAlbumArtColorAsync();

    if (!g_initSucceeded.load(std::memory_order_relaxed)) return;

    if (!g_fullscreenPaused.load()) {
        if (IsFullscreenPauseConditionActive()) {
            PauseForFullscreen();
        }
    } else if (!g_settings.pauseOnFullscreen && !g_placementOverlay.load()) {
        ResumeFromFullscreen();
    }

    if (!g_overlayWnd) return;

    UpdateSwapChainForLayout();

    ReleaseVisualResources();
    RecreateVisualResources();

    if (oldMonitor != g_settings.monitor) HandleDisplayChange();

    if (!g_fullscreenPaused.load()) {
        RenderVisualizer();
    }
}

void WhTool_ModSettingsChanged() {
    Wh_Log(L">");

    // Has to land on the UI thread: it can create or resize windows that thread
    // owns. The overlay is preferred, but it's the one window that legitimately
    // may not exist yet (it waits on WorkerW), so fall back to the message
    // window -- which is created first and always there -- rather than running
    // this inline on Windhawk's own settings thread.
    if (g_overlayWnd) {
        SendMessage(g_overlayWnd, WM_APP_SETTINGS_CHANGED, 0, 0);
    } else if (g_messageWnd) {
        SendMessage(g_messageWnd, WM_APP_SETTINGS_CHANGED, 0, 0);
    } else {
        ApplySettingsChanged();
    }
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

} // namespace viz
#pragma pop_macro("Wh_Log")

// ---------------------------------------------------------------------------
// Entry points. The taskbar process (plain explorer.exe) runs the player and
// starts a tool process ("explorer.exe -tool-mod <id>") that runs the bars.
// ---------------------------------------------------------------------------
bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;

void WINAPI EntryPoint_Hook() {
    ExitThread(0);
}

BOOL Wh_ModInit() {
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
        // Single instance by the mutex name. On a reload or an Explorer
        // restart the old process can still be shutting down, so wait up to
        // 30 seconds for its handle to close.
        for (int tries = 0;; tries++) {
            g_toolModProcessMutex =
                CreateMutex(nullptr, FALSE, L"windhawk-tool-mod_" WH_MOD_ID);
            if (!g_toolModProcessMutex) {
                Wh_Log(L"CreateMutex failed");
                ExitProcess(1);
            }
            if (GetLastError() != ERROR_ALREADY_EXISTS) {
                break;
            }
            CloseHandle(g_toolModProcessMutex);
            if (tries >= 60) {
                Wh_Log(L"Tool mod already running (%s)", WH_MOD_ID);
                ExitProcess(1);
            }
            Sleep(500);
        }

        if (!viz::WhTool_ModInit()) {
            ExitProcess(1);
        }

        IMAGE_DOS_HEADER* dosHeader =
            (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders =
            (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);
        void* entryPoint =
            (BYTE*)dosHeader + ntHeaders->OptionalHeader.AddressOfEntryPoint;
        Wh_SetFunctionHook(entryPoint, (void*)EntryPoint_Hook, nullptr);
        return TRUE;
    }

    if (isToolModProcess) {
        return FALSE;
    }

    // Only the taskbar process (plain explorer.exe, no arguments) hosts the
    // player and launches the tool. Folder windows run as "/factory,..."
    // processes and must not.
    if (argc > 1) {
        return FALSE;
    }

    g_isToolModProcessLauncher = true;
    return fmp::ModInit();
}

static void LaunchToolProcess() {
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

void Wh_ModAfterInit() {
    if (!g_isToolModProcessLauncher) {
        return;
    }
    fmp::ModAfterInit();
    LaunchToolProcess();
}

void Wh_ModSettingsChanged() {
    if (g_isToolModProcessLauncher) {
        fmp::ModSettingsChanged();
        return;
    }
    viz::WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isToolModProcessLauncher) {
        fmp::ModUninit();
        return;
    }
    viz::WhTool_ModUninit();
    ExitProcess(0);
}
